//*****************************************************************************
// File: NewUITrade.cpp
//
// Desc: implementation of the CNewUITrade class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"

#include "NewUITrade.h"
#include "NewUISystem.h"
#include "NewUICustomMessageBox.h"
#include "wsclientinline.h"
#include "CComGem.h"

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewUITrade::CNewUITrade()
{
	m_pNewUIMng = NULL;
	m_pYourInvenCtrl = m_pMyInvenCtrl = NULL;
	m_Pos.x = m_Pos.y = 0;
}

CNewUITrade::~CNewUITrade()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : â ����.
// �Ű� ���� : pNewUIMng	: CNewUIManager ������Ʈ �ּ�.
//			   x			: x ��ǥ.
//			   y			: y ��ǥ.
//*****************************************************************************
bool CNewUITrade::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if (NULL == pNewUIMng || NULL == g_pNewUI3DRenderMng
		|| NULL == g_pNewItemMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_TRADE, this);

	m_pYourInvenCtrl = new CNewUIInventoryCtrl;
	if (false == m_pYourInvenCtrl->Create(g_pNewUI3DRenderMng, g_pNewItemMng,
		this, x + 16, y + 68, COLUMN_TRADE_INVEN, ROW_TRADE_INVEN))
	{
		SAFE_DELETE(m_pYourInvenCtrl);
		return false;
	}
	m_pYourInvenCtrl->LockInventory();	// ���� ��ǰ�� Ŭ�� �ȵǰ� ��.

	m_pMyInvenCtrl = new CNewUIInventoryCtrl;
	if (false == m_pMyInvenCtrl->Create(g_pNewUI3DRenderMng, g_pNewItemMng,
		this, x + 16, y + 274, COLUMN_TRADE_INVEN, ROW_TRADE_INVEN))
	{
		SAFE_DELETE(m_pMyInvenCtrl);
		return false;
	}

	SetPos(x, y);

	LoadImages();

// ��ư�� ����.
	m_abtn[BTN_CLOSE].ChangeButtonImgState(true, IMAGE_TRADE_BTN_CLOSE);
	m_abtn[BTN_CLOSE].ChangeButtonInfo(x + 13, y + 390, 36, 29);
	m_abtn[BTN_CLOSE].ChangeToolTipText(GlobalText[1002], true);

	m_abtn[BTN_ZEN_INPUT].ChangeButtonImgState(true, IMAGE_TRADE_BTN_ZEN_INPUT);
	m_abtn[BTN_ZEN_INPUT].ChangeButtonInfo(x + 104, y + 390, 36, 29);
	m_abtn[BTN_ZEN_INPUT].ChangeToolTipText(GlobalText[227], true);

	::memset(m_szYourID, 0, MAX_ID_SIZE+1);
	m_bTradeAlert = false;

	InitTradeInfo();
	InitYourInvenBackUp();

	Show(false);	

	return true;
}

//*****************************************************************************
// �Լ� �̸� : InitTradeInfo()
// �Լ� ���� : ���� �ŷ� ���� ���� �ʱ�ȭ.
//*****************************************************************************
void CNewUITrade::InitTradeInfo()
{
	m_nYourLevel = 0;
	m_nYourGuildType = -1;
	m_nYourTradeGold = 0;
	m_nMyTradeGold = 0;
	m_nMyTradeWait = 0;
	m_bYourConfirm = m_bMyConfirm = false;
}

//*****************************************************************************
// �Լ� �̸� : InitYourInvenBackUp()
// �Լ� ���� : ���� �ŷ� ������ ��� �ʱ�ȭ.
//*****************************************************************************
void CNewUITrade::InitYourInvenBackUp()
{
	for (int i = 0; i < MAX_TRADE_INVEN; ++i)
		m_aYourInvenBackUp[i].Type = -1;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : â Release.
//*****************************************************************************
void CNewUITrade::Release()
{
	UnloadImages();

	SAFE_DELETE(m_pMyInvenCtrl);
	SAFE_DELETE(m_pYourInvenCtrl);

	if (m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}

	if (g_pNewUI3DRenderMng)
		g_pNewUI3DRenderMng->DeleteUI2DEffectObject(UI2DEffectCallback);
}

//*****************************************************************************
// �Լ� �̸� : SetPos()
// �Լ� ���� : â ��ġ ����.
//*****************************************************************************
void CNewUITrade::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;

	m_posMyConfirm.x = m_Pos.x + 144;
	m_posMyConfirm.y = m_Pos.y + 390;
}

//*****************************************************************************
// �Լ� �̸� : UpdateMouseEvent()
// �Լ� ���� : ���콺 �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUITrade::UpdateMouseEvent()
{
	if ((m_pYourInvenCtrl && false == m_pYourInvenCtrl->UpdateMouseEvent())
		|| (m_pMyInvenCtrl && false == m_pMyInvenCtrl->UpdateMouseEvent()))
	{
		// �ڽ� �ŷ� ��ǰ�� ������ �� Ȯ���̾��ٸ� ��Ȯ������.
		if (SEASON3B::IsPress(VK_LBUTTON)
			&& CNewUIInventoryCtrl::GetPickedItem()->GetOwnerInventory() == m_pMyInvenCtrl
			&& m_bMyConfirm)
		{
				m_bMyConfirm = false;
				SendRequestTradeResult(m_bMyConfirm);
		}

		return false;
	}

	ProcessMyInvenCtrl();

	if (ProcessBtns())
		return false;

	// â ���� Ŭ���� ���� UIó�� �� �̵� �Ұ�
	if(CheckMouseIn(m_Pos.x, m_Pos.y, TRADE_WIDTH, TRADE_HEIGHT))
	{
		if(SEASON3B::IsPress(VK_RBUTTON))
		{
			MouseRButton = false;
			MouseRButtonPop = false;
			MouseRButtonPush = false;
			return false;
		}

		if(SEASON3B::IsNone(VK_LBUTTON) == false)
		{
			return false;
		}
	}

	return true;
}

//*****************************************************************************
// �Լ� �̸� : UpdateKeyEvent()
// �Լ� ���� : Ű���� �Է� ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUITrade::UpdateKeyEvent()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_TRADE) == true)
	{
		if(SEASON3B::IsPress(VK_ESCAPE) == true)
		{
			SendRequestTradeExit();
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_TRADE);
			PlayBuffer(SOUND_CLICK01);

			return false;
		}
	}
	return true;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ��Ÿ �� ������ �Ͼ�� �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUITrade::Update()
{
	if ((m_pYourInvenCtrl && false == m_pYourInvenCtrl->Update())
		|| (m_pMyInvenCtrl && false == m_pMyInvenCtrl->Update()))
		return false;

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : â ����.
// ��ȯ ��	 : true�� ����.
//*****************************************************************************
bool CNewUITrade::Render()
{
	::EnableAlphaTest();

	::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderBackImage();
	RenderText();

	if (m_pYourInvenCtrl)
		m_pYourInvenCtrl->Render();
	if (m_pMyInvenCtrl)
		m_pMyInvenCtrl->Render();

	for (int i = BTN_CLOSE; i < MAX_BTN; ++i)
		m_abtn[i].Render();

	if (g_pNewUI3DRenderMng)
		g_pNewUI3DRenderMng->RenderUI2DEffect(INVENTORY_CAMERA_Z_ORDER,
			UI2DEffectCallback, this, 0, 0);

	::DisableAlphaBlend();
	
	return true;
}

//*****************************************************************************
// �Լ� �̸� : UI2DEffectCallback()
// �Լ� ���� : �����ۿ� ���� ǥ�� �����ϱ� ���� Callback �Լ�.
//			   (3D ������ ���� ���� �Ǿ� �ϹǷ�.)
//*****************************************************************************
void CNewUITrade::UI2DEffectCallback(LPVOID pClass, DWORD dwParamA, DWORD dwParamB)
{
	if (pClass)
	{
		CNewUITrade* pNewUITrade = (CNewUITrade*)pClass;
		pNewUITrade->RenderWarningArrow();
	}
}

//*****************************************************************************
// �Լ� �̸� : RenderBackImage()
// �Լ� ���� : â ���� �̹��� ����.
//*****************************************************************************
void CNewUITrade::RenderBackImage()
{
	RenderImage(IMAGE_TRADE_BACK,
		m_Pos.x, m_Pos.y, float(TRADE_WIDTH), float(TRADE_HEIGHT));
	RenderImage(IMAGE_TRADE_TOP,
		m_Pos.x, m_Pos.y, float(TRADE_WIDTH), 64.f);
	RenderImage(IMAGE_TRADE_LEFT, m_Pos.x, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_TRADE_RIGHT,
		m_Pos.x+TRADE_WIDTH-21, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_TRADE_BOTTOM,
		m_Pos.x, m_Pos.y+TRADE_HEIGHT-45, float(TRADE_WIDTH), 45.f);

	RenderImage(IMAGE_TRADE_LINE, m_Pos.x+1, m_Pos.y+220, 188.f, 21.f);
	RenderImage(IMAGE_TRADE_NICK_BACK, m_Pos.x+11, m_Pos.y+37, 171.f, 26.f);
	RenderImage(IMAGE_TRADE_MONEY, m_Pos.x+11, m_Pos.y+150, 170.f, 26.f);
	RenderImage(IMAGE_TRADE_NICK_BACK, m_Pos.x+11, m_Pos.y+243, 171.f, 26.f);
	RenderImage(IMAGE_TRADE_MONEY, m_Pos.x+11, m_Pos.y+356, 170.f, 26.f);

// ���� ���� ��ư �̹���.
	float fSrcY = m_bYourConfirm ? 29.f : 0.f;
	RenderImage(IMAGE_TRADE_CONFIRM, m_Pos.x+146, m_Pos.y+186, CONFIRM_WIDTH, CONFIRM_HEIGHT, 0.f, fSrcY);

// �ڽ��� ���� ��ư.
	DWORD dwColor = m_nMyTradeWait > 0
		? RGBA(255, 0, 0, 255) : RGBA(255, 255, 255, 255);
	fSrcY = m_bMyConfirm ? 29.f : 0.f;
	RenderImage(IMAGE_TRADE_CONFIRM, m_Pos.x+144, m_Pos.y+390, CONFIRM_WIDTH, CONFIRM_HEIGHT, 0.f, fSrcY, dwColor);
}

//*****************************************************************************
// �Լ� �̸� : RenderText()
// �Լ� ���� : �ؽ�Ʈ ����.
//*****************************************************************************
void CNewUITrade::RenderText()
{
	unicode::t_char szTemp[128];

	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetBgColor(0);

// ����.
	g_pRenderText->SetTextColor(216, 216, 216, 255);
	g_pRenderText->RenderText(
		m_Pos.x, m_Pos.y+11, GlobalText[226], TRADE_WIDTH, 0, RT3_SORT_CENTER);

// ���� ���.
	for (int i = 0; i < MAX_MARKS; ++i)
    {
        if (GuildMark[i].Key != -1 && GuildMark[i].Key == m_nYourGuildType)
        {
			::CreateGuildMark(i, false);
			::RenderBitmap(BITMAP_GUILD, (float)m_Pos.x+15, (float)m_Pos.y+42, 16, 16);
			g_pRenderText->RenderText(m_Pos.x+16, m_Pos.y+30, GuildMark[i].GuildName);
			break;
        }
    }

// ���� ���̵�.
	g_pRenderText->SetFont(g_hFontBig);

	g_pRenderText->SetTextColor(210, 230, 255, 255);
	g_pRenderText->RenderText(m_Pos.x+32, m_Pos.y+43, m_szYourID);

// ���� ����.
	g_pRenderText->SetFont(g_hFontBold);

    int nLevel;
	DWORD dwColor;
	ConvertYourLevel(nLevel, dwColor);
	// 369 "%d��"
	if(nLevel == 400)
	{
		unicode::_sprintf(szTemp, "%d", nLevel);
	}
	else
	{
		unicode::_sprintf(szTemp, GlobalText[369], nLevel);
	}
	g_pRenderText->SetTextColor(dwColor);
	g_pRenderText->RenderText(m_Pos.x+134, m_Pos.y+48, "Lv.");
    g_pRenderText->RenderText(m_Pos.x+148, m_Pos.y+48, szTemp);

// ���� ��.
    ::ConvertGold(m_nYourTradeGold, szTemp);
	// ���� �� ������ ��ȭ. (��� -> ��Ȳ�� -> ������).
	g_pRenderText->SetTextColor(::getGoldColor(m_nYourTradeGold));
	g_pRenderText->RenderText(
		m_Pos.x+170, m_Pos.y+150+8, szTemp, 0, 0, RT3_WRITE_RIGHT_TO_LEFT);

// �ڽ��� ��.
	::ConvertGold(m_nMyTradeGold, szTemp);
	// ���� �� ������ ��ȭ. (��� -> ��Ȳ�� -> ������).
	g_pRenderText->SetTextColor(::getGoldColor(m_nMyTradeGold));
	g_pRenderText->RenderText(
		m_Pos.x+170, m_Pos.y+356+8, szTemp, 0, 0, RT3_WRITE_RIGHT_TO_LEFT);

// �ڽ��� ���̵�.
	g_pRenderText->SetTextColor(210, 230, 255, 255);
	g_pRenderText->RenderText(m_Pos.x+20, m_Pos.y+253, Hero->ID);

//  ��� ������ ��Ÿ����.
    int nAlpha = int(min(255, sin(WorldTime/200)*200+275));
	g_pRenderText->SetTextColor(210, 0, 0, nAlpha);
    g_pRenderText->RenderText(m_Pos.x+20,m_Pos.y+185,GlobalText[370]);
	g_pRenderText->SetTextColor(255, 220, 150, 255);
    g_pRenderText->RenderText(m_Pos.x+45,m_Pos.y+185,GlobalText[365]);
    g_pRenderText->RenderText(m_Pos.x+20,m_Pos.y+200,GlobalText[366]);
    g_pRenderText->RenderText(m_Pos.x+20,m_Pos.y+215,GlobalText[367]);
}

//*****************************************************************************
// �Լ� �̸� : RenderWarningArrow()
// �Լ� ���� : ������ ������ ������ ������ ���� ���� ���� �� ���� ǥ�� ����.
//			  (� �������� ����ǥ�ø� �ϴ��� �� �𸣰���. ��ȹ���� �� ��)
//			  (�� ������ ���� �ҽ� �״�� �ű�.)
//*****************************************************************************
void CNewUITrade::RenderWarningArrow()
{
	::EnableAlphaTest();

	int nYourItems = m_pYourInvenCtrl->GetNumberOfItems();
	ITEM* pYourItemObj;
	int nWidth;
	float fX, fY;
	POINT ptYourInvenCtrl = m_pYourInvenCtrl->GetPos();

	for (int i = 0; i < nYourItems; ++i)
	{
		pYourItemObj = m_pYourInvenCtrl->GetItem(i);
		if (ITEM_COLOR_TRADE_WARNING == pYourItemObj->byColorState)
		{
            fX = (float)ptYourInvenCtrl.x
				+(pYourItemObj->x*INVENTORY_SQUARE_WIDTH);
            fY = (float)ptYourInvenCtrl.y
				+(pYourItemObj->y*INVENTORY_SQUARE_WIDTH)
				+sinf(WorldTime*0.015f);

			::glColor3f(0.f,1.f,1.f);
            ::RenderBitmap(IMAGE_TRADE_WARNING_ARROW, fX, fY+5, 24.f, 24.f,
				0.f, 0.4f);
            ::glColor3f(1.f,1.f,1.f);

			g_pRenderText->SetFont(g_hFontBold);
			g_pRenderText->SetTextColor(255, 255, 255, 255);
			g_pRenderText->SetBgColor(210, 0, 0, 255);
			nWidth = (int)ItemAttribute[pYourItemObj->Type].Width
				* INVENTORY_SQUARE_WIDTH;
			g_pRenderText->RenderText((int)fX, (int)fY, GlobalText[370],
				nWidth, 0, RT3_SORT_CENTER);
		}
	}

	::DisableAlphaBlend();
}

//*****************************************************************************
// �Լ� �̸� : ConvertYourLevel()
// �Լ� ���� : ���� ��Ȯ�� ������ �����Ű�� �ʱ� ���� ������� ��ȯ.
// �Ű� ���� : rnLevel	: �����븦 �����ϱ����� �޸� ���۷���.
//			   rdwColor	: ������ �ؽ�Ʈ�� ������ �����ϱ����� �޸� ���۷���.
//*****************************************************************************
void CNewUITrade::ConvertYourLevel(int& rnLevel, DWORD& rdwColor)
{
	if(m_nYourLevel >= 400)
	{
		rnLevel = 400;
		rdwColor = (255<<24)+(153<<16)+(153<<8)+(255);
	}
	else if (m_nYourLevel >= 300)
    {
        rnLevel = 300;
	    rdwColor = (255<<24)+(255<<16)+(153<<8)+(255);
    }
    else if (m_nYourLevel >= 200)	//  ���.
    {
        rnLevel = 200;
	    rdwColor = (255<<24)+(255<<16)+(230<<8)+(210);
    }
    else if (m_nYourLevel >= 100)	//  ���.
    {
        rnLevel = 100;
        rdwColor = (255<<24)+(24<<16)+(201<<8)+(0);
    }
    else if (m_nYourLevel >= 50)	//  ��Ȳ��.
    {
        rnLevel = 50;
        rdwColor = (255<<24)+(0<<16)+(150<<8)+(255);
    }
    else							//  ������.
    {
        rnLevel = 10;
        rdwColor = (255<<24)+(0<<16)+(0<<8)+(255);
    }
}

//*****************************************************************************
// �Լ� �̸� : GetLayerDepth()
// �Լ� ���� : â�� ���̾�� ����.
//*****************************************************************************
float CNewUITrade::GetLayerDepth()
{
	return 2.1f;
}

//*****************************************************************************
// �Լ� �̸� : LoadImages()
// �Լ� ���� : �̹��� ���ҽ� �ε�.
//*****************************************************************************
void CNewUITrade::LoadImages()
{
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_TRADE_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back01.tga", IMAGE_TRADE_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-L.tga", IMAGE_TRADE_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-R.tga", IMAGE_TRADE_RIGHT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_TRADE_BOTTOM, GL_LINEAR);

	LoadBitmap("Interface\\newui_myquest_Line.tga", IMAGE_TRADE_LINE, GL_LINEAR);
	LoadBitmap("Interface\\newui_Account_title.tga", IMAGE_TRADE_NICK_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_money.tga", IMAGE_TRADE_MONEY, GL_LINEAR);
	LoadBitmap("Interface\\newui_Bt_accept.tga", IMAGE_TRADE_CONFIRM, GL_LINEAR);
	LoadBitmap("Interface\\CursorSitDown.tga", IMAGE_TRADE_WARNING_ARROW, GL_LINEAR, GL_CLAMP);
	
	LoadBitmap("Interface\\newui_exit_00.tga", IMAGE_TRADE_BTN_CLOSE, GL_LINEAR);
	LoadBitmap("Interface\\newui_Bt_money01.tga", IMAGE_TRADE_BTN_ZEN_INPUT, GL_LINEAR);
}

//*****************************************************************************
// �Լ� �̸� : UnloadImages()
// �Լ� ���� : �̹��� ���ҽ� ����.
//*****************************************************************************
void CNewUITrade::UnloadImages()
{
	DeleteBitmap(IMAGE_TRADE_BTN_ZEN_INPUT);
	DeleteBitmap(IMAGE_TRADE_BTN_CLOSE);

	DeleteBitmap(IMAGE_TRADE_WARNING_ARROW);
	DeleteBitmap(IMAGE_TRADE_CONFIRM);
	DeleteBitmap(IMAGE_TRADE_MONEY);
	DeleteBitmap(IMAGE_TRADE_NICK_BACK);
	DeleteBitmap(IMAGE_TRADE_LINE);

	DeleteBitmap(IMAGE_TRADE_BOTTOM);
	DeleteBitmap(IMAGE_TRADE_RIGHT);
	DeleteBitmap(IMAGE_TRADE_LEFT);
	DeleteBitmap(IMAGE_TRADE_TOP);
	DeleteBitmap(IMAGE_TRADE_BACK);
}

//*****************************************************************************
// �Լ� �̸� : ProcessClosing()
// �Լ� ���� : â�� ���� �� ó��.
//*****************************************************************************
void CNewUITrade::ProcessClosing()
{
	m_pYourInvenCtrl->RemoveAllItems();
	m_pMyInvenCtrl->RemoveAllItems();

	// �ŷ��� �����Ǿ���.
	if (m_bTradeAlert)
		InitYourInvenBackUp();	// ���� ��� ��ǰ ����.
}

//*****************************************************************************
// �Լ� �̸� : ProcessMyInvenCtrl()
// �Լ� ���� : �ڽ��� �ŷ� �κ��丮 ��Ʈ�� ���콺 �̺�Ʈ ó��.
//*****************************************************************************
void CNewUITrade::ProcessMyInvenCtrl()
{
	if (NULL == m_pMyInvenCtrl)
		return;

	if (SEASON3B::IsPress(VK_LBUTTON))
	{
		CNewUIPickedItem* pPickedItem = CNewUIInventoryCtrl::GetPickedItem();
		if (NULL == pPickedItem)
			return;

		ITEM* pItemObj = pPickedItem->GetItem();
		// �κ��丮���� �� ���ΰ�?
		if (pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())
		{
			int nSrcIndex = pPickedItem->GetSourceLinealPos();
			int nDstIndex = pPickedItem->GetTargetLinealPos(m_pMyInvenCtrl);
			if (nDstIndex != -1 && m_pMyInvenCtrl->CanMove(nDstIndex, pItemObj))
				SendRequestItemToTrade(pItemObj, MAX_EQUIPMENT_INDEX+nSrcIndex, nDstIndex);
		}
		// �ŷ�â���� �� ���ΰ�?(�ڽ� ��)
		else if (pPickedItem->GetOwnerInventory() == m_pMyInvenCtrl)
		{
			int nSrcIndex = pPickedItem->GetSourceLinealPos();
			int nDstIndex = pPickedItem->GetTargetLinealPos(m_pMyInvenCtrl);
			if (nDstIndex != -1 && m_pMyInvenCtrl->CanMove(nDstIndex, pItemObj))
			{
				SendRequestEquipmentItem(REQUEST_EQUIPMENT_TRADE, nSrcIndex,
					pItemObj, REQUEST_EQUIPMENT_TRADE, nDstIndex);
			}
		}
		// ��񿡼� �� ���ΰ�?(���� CNewUIInventoryCtrl�� ������� �����Ƿ�)
		else if (pItemObj->ex_src_type == ITEM_EX_SRC_EQUIPMENT)
		{
			int nSrcIndex = pPickedItem->GetSourceLinealPos();
			int nDstIndex = pPickedItem->GetTargetLinealPos(m_pMyInvenCtrl);
			if (nDstIndex != -1 && m_pMyInvenCtrl->CanMove(nDstIndex, pItemObj))
				SendRequestItemToTrade(pItemObj, nSrcIndex, nDstIndex);
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : SendRequestItemToTrade()
// �Լ� ���� : �������� �ŷ�â���� �̵��� ������ �䱸.
// �Ű� ���� : pItemObj		: ������ ������Ʈ �ּ�.
//			   nStorageIndex: �κ��丮â������ ������ ��ġ.
//			   nTradeIndex	: �̵� ��ų �ŷ�â ������ ��ġ.
//*****************************************************************************
void CNewUITrade::SendRequestItemToTrade(ITEM* pItemObj, int nInvenIndex,
										 int nTradeIndex)
{
	if (::IsTradeBan(pItemObj))
	{
		g_pChatListBox->AddText(
			"", GlobalText[494], SEASON3B::TYPE_ERROR_MESSAGE);							
	}
	else
	{
		m_bMyConfirm = false;
		SendRequestTradeResult(m_bMyConfirm);

		SendRequestEquipmentItem(REQUEST_EQUIPMENT_INVENTORY, nInvenIndex,
			pItemObj, REQUEST_EQUIPMENT_TRADE, nTradeIndex);
	}
}

//*****************************************************************************
// �Լ� �̸� : SendRequestItemToMyInven()
// �Լ� ���� : �������� �κ��丮â���� �̵��� ������ �䱸.
// �Ű� ���� : pItemObj		: ������ ������Ʈ �ּ�.
//			   nTradeIndex	: �ŷ�â������ ������ ��ġ.
//			   nInvenIndex	: �̵� ��ų �κ��丮â ������ ��ġ.
//*****************************************************************************
void CNewUITrade::SendRequestItemToMyInven(ITEM* pItemObj, int nTradeIndex,
										   int nInvenIndex)
{
	SendRequestEquipmentItem(REQUEST_EQUIPMENT_TRADE, nTradeIndex,
		pItemObj, REQUEST_EQUIPMENT_INVENTORY, nInvenIndex);

#ifdef YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED
	if (m_bMyConfirm)
	{
		AlertTrade();
	}
	m_nMyTradeWait = 150;
#else	// YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED
	if (!m_bMyConfirm)
        m_nMyTradeWait = 150;
#endif	// YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED
}

//*****************************************************************************
// �Լ� �̸� : SendRequestMyGoldInput()
// �Լ� ���� : �� �Է� â���� �ڽ��� ���� �ŷ�â�� �ø� �� ������ ������ ó��.
// �Ű� ���� : nInputGold	: �Է��� ��.
//*****************************************************************************
void CNewUITrade::SendRequestMyGoldInput(int nInputGold)
{

#ifdef _VS2008PORTING
	if (nInputGold <= (int)CharacterMachine->Gold+m_nMyTradeGold)
#else // _VS2008PORTING
	if (nInputGold <= CharacterMachine->Gold+m_nMyTradeGold)
#endif // _VS2008PORTING
	{
		if (m_bMyConfirm)
		{
			m_bMyConfirm = false;
			SendRequestTradeResult(m_bMyConfirm);
		}

		if (m_nMyTradeGold > 0)
			m_nMyTradeWait = 150;

		m_nTempMyTradeGold = nInputGold;
		SendRequestTradeGold(nInputGold);
	}
	else
	{
		// 423 "���� �����մϴ�."
		SEASON3B::CreateOkMessageBox(GlobalText[423]);
	}

}

//*****************************************************************************
// �Լ� �̸� : ProcessCloseBtn()
// �Լ� ���� : �ݱ� ��ư ó��.
//*****************************************************************************
void CNewUITrade::ProcessCloseBtn()
{
	if (CNewUIInventoryCtrl::GetPickedItem() == NULL)
	{
		m_bTradeAlert = false;
		SendRequestTradeExit();
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessBtns()
// �Լ� ���� : ��ư ������ �̺�Ʈ ó��.
// ��ȯ ��	 : ó�� ������ true.
//*****************************************************************************
bool CNewUITrade::ProcessBtns()
{
	if (m_nMyTradeWait > 0)
		--m_nMyTradeWait;

	if (m_abtn[BTN_CLOSE].UpdateMouseEvent())
	{
		::PlayBuffer(SOUND_CLICK01);	// ��ư ��⿡�� ���� ���� ���� ��.
		ProcessCloseBtn();
		return true;
	}
	else if (SEASON3B::IsPress(VK_LBUTTON)
		&& CheckMouseIn(m_Pos.x+169, m_Pos.y+7, 13, 12))
	{
		::PlayBuffer(SOUND_CLICK01);
		ProcessCloseBtn();
		return true;
	}
	else if (m_abtn[BTN_ZEN_INPUT].UpdateMouseEvent())
	{
		SEASON3B::CreateMessageBox(
			MSGBOX_LAYOUT_CLASS(SEASON3B::CTradeZenMsgBoxLayout));
		::PlayBuffer(SOUND_CLICK01);	// ��ư ��⿡�� ���� ���� ���� ��.
		return true;
	}
	else if (SEASON3B::IsRelease(VK_LBUTTON)
		&& CheckMouseIn(m_posMyConfirm.x, m_posMyConfirm.y, CONFIRM_WIDTH, CONFIRM_HEIGHT))
	{
		if (0 == m_nMyTradeWait && CNewUIInventoryCtrl::GetPickedItem() == NULL)
		{
			::PlayBuffer(SOUND_CLICK01);
			//  ��� �߻�.
			if (m_bTradeAlert && !m_bMyConfirm)
			{
				SEASON3B::CreateMessageBox(
					MSGBOX_LAYOUT_CLASS(SEASON3B::CTradeAlertMsgBoxLayout));
			}
			else
			{
				AlertTrade();
			}
		}
		return true;
	}

	return false;
}

//*****************************************************************************
// �Լ� �̸� : AlertTrade()
// �Լ� ���� : �ŷ� ��� �߻� ��Ŵ.
//*****************************************************************************
void CNewUITrade::AlertTrade()
{
	m_bMyConfirm = !m_bMyConfirm;

	m_bTradeAlert = true;
	SendRequestTradeResult(m_bMyConfirm);
}

//*****************************************************************************
// �Լ� �̸� : GetYourID()
// �Լ� ���� : ���� ID�� ����.
// �Ű� ���� : pszYourID	: ���� ID�� ���� �޸� �ּ�.
//*****************************************************************************
void CNewUITrade::GetYourID(char* pszYourID)
{
	::strcpy(pszYourID, m_szYourID);
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveTradeRequest()
// �Լ� ���� : ���濡�Լ� �ŷ� ��û�� �Դٰ� �������� �˷��� �� ó��.
// �Ű� ���� : pbyYourID	: ���� ID.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveTradeRequest(BYTE* pbyYourID)
{
	if (g_pNewUISystem->IsImpossibleTradeInterface())
	{
		SendRequestTradeAnswer(false);
		return;
	}

	::memcpy(m_szYourID, pbyYourID, MAX_ID_SIZE);
	m_szYourID[MAX_ID_SIZE] = NULL;

	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CTradeMsgBoxLayout));

	SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveTradeResult()
// �Լ� ���� : ���濡�� �ŷ� ��û �� �� ����� �������� �˷��� �� ó��.
// �Ű� ���� : pTradeData	: �ŷ� ����ü �ּ�.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveTradeResult(LPPTRADE pTradeData)
{
	switch(pTradeData->SubCode)
	{
	case 0:		// 492 "�ŷ��� ����߽��ϴ�."
		g_pChatListBox->AddText("", GlobalText[492], SEASON3B::TYPE_ERROR_MESSAGE);
		break;

	case 2:		// 493 "�ŷ��� �� ���� ��Ȳ�Դϴ�."
		g_pChatListBox->AddText("", GlobalText[493], SEASON3B::TYPE_ERROR_MESSAGE);
		break;

	case 1:		// ������ �ŷ��� ����.
		g_pNewUISystem->Show(SEASON3B::INTERFACE_TRADE);

		InitTradeInfo();

		int x = 260*MouseX/640;
		::SetCursorPos(x*WindowWidth/640, MouseY*WindowHeight/480);

		// �ٷ� ���� �ŷ� ������ ĳ���Ϳ� ���� ĳ���Ͱ� �ƴϸ� ����� �ŷ�
		//������ ������ Ŭ���� �Ѵ�.
		char szTempID[MAX_ID_SIZE+1];
		::memcpy(szTempID, pTradeData->ID, MAX_ID_SIZE);
		szTempID[MAX_ID_SIZE] = NULL;
		
		if (!m_bTradeAlert && ::strcmp(m_szYourID, szTempID))
			InitYourInvenBackUp();

        m_bTradeAlert = false;
        m_nYourGuildType = pTradeData->GuildKey;
        ::memcpy(m_szYourID, pTradeData->ID, MAX_ID_SIZE);
		m_szYourID[MAX_ID_SIZE] = NULL;
        m_nYourLevel = pTradeData->Level;   //  ���� ����.
		break;
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveYourItemDelete()
// �Լ� ���� : �������� ������ �������� ���� �Ǿ��ٰ� �˷��� �� ó��.
// �Ű� ���� : byYourInvenIndex	: ������ ���� ������ ��ġ ����.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveYourItemDelete(BYTE byYourInvenIndex)
{
	BackUpYourInven(int(byYourInvenIndex));
	ITEM* pYourItemObj = m_pYourInvenCtrl->FindItem(int(byYourInvenIndex));
	m_pYourInvenCtrl->RemoveItem(pYourItemObj);
	AlertYourTradeInven();
   	::PlayBuffer(SOUND_GET_ITEM01);
}

//*****************************************************************************
// �Լ� �̸� : BackUpYourInven()
// �Լ� ���� : ���� �߿� ������ ���.
//			   (����� �������� ���ų�, ����� �����۰� ���Ͽ� �ٸ��ų�, ����
//			  Ÿ���� �������� ��� �Ű� ������ �������� �� ���� ��쿡�� ���.)
// �Ű� ���� : nYourInvenIndex	: ���� �ŷ� ������ ��ġ.
//*****************************************************************************
void CNewUITrade::BackUpYourInven(int nYourInvenIndex)
{
	ITEM* pYourItemObj = m_pYourInvenCtrl->FindItem(nYourInvenIndex);
	BackUpYourInven(pYourItemObj);
}

//*****************************************************************************
// �Լ� �̸� : BackUpYourInven()
// �Լ� ���� : ���� �߿� ������ ���.
//			   (����� �������� ���ų�, ����� �����۰� ���Ͽ� �ٸ��ų�, ����
//			  Ÿ���� �������� ��� �Ű� ������ �������� �� ���� ��쿡�� ���.)
// �Ű� ���� : pYourItemObj	: ����� ���� �ŷ� ������.
//*****************************************************************************
void CNewUITrade::BackUpYourInven(ITEM* pYourItemObj)
{
    if ((pYourItemObj->Type>=ITEM_HELPER && pYourItemObj->Type<=ITEM_HELPER+4)	//  ��ȣ, ��ź.
		|| (pYourItemObj->Type==ITEM_POTION+13 || pYourItemObj->Type==ITEM_POTION+14 || pYourItemObj->Type==ITEM_POTION+16)	//  �༮, ����, ����.
		|| (pYourItemObj->Type>=ITEM_POTION+31)									//  ��ȣ�� ����
		|| (COMGEM::isCompiledGem(pYourItemObj))
		|| (pYourItemObj->Type>=ITEM_WING && pYourItemObj->Type<=ITEM_WING+6)	//  ����.
		|| (pYourItemObj->Type>=ITEM_HELPER+30)									//  ������ ����.
#ifdef ADD_ALICE_WINGS_1
		|| (pYourItemObj->Type>=ITEM_WING+36 && pYourItemObj->Type<=ITEM_WING+43)// ��ǳ�� ���� ~ ������ ����, ��ȯ���� ����.
#else	// ADD_ALICE_WINGS_1
		|| (pYourItemObj->Type>=ITEM_WING+36 && pYourItemObj->Type<=ITEM_WING+40 )// ��ǳ�� ���� ~ ������ ����
#endif	// ADD_ALICE_WINGS_1
        || (pYourItemObj->Type==ITEM_WING+15 )									//  ȥ���� ����.
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (pYourItemObj->Type>=ITEM_WING+49 && pYourItemObj->Type<=ITEM_WING+50)// ������������ ����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		|| ((((pYourItemObj->Level>>3)&15)>4 && pYourItemObj->Type<ITEM_WING) || (pYourItemObj->Option1&63)>0))	//  ���� 4�̻��� ������.
    {
		int nCompareValue;
        bool bSameItem = false;

		for (int i = 0; i < MAX_TRADE_INVEN; ++i)
		{
			if (-1 == m_aYourInvenBackUp[i].Type)
				continue;
			
			nCompareValue = ::CompareItem(m_aYourInvenBackUp[i], *pYourItemObj);
			if (0 == nCompareValue)			// ���� ������.
			{
				bSameItem = true;
				break;
			}
			else if (-1 == nCompareValue)	// pYourItemObj�� �� ���� ������.
			{
				bSameItem = true;
				m_aYourInvenBackUp[i] = *pYourItemObj;
				break;
			}
			else if (2 != nCompareValue)	// pYourBackUpItemObj�� �� ���� ������.
			{
				bSameItem = true;
			}
		}

        if (!bSameItem)		// �ٸ� �������� ���.
        {
			// ����ִ� ���� ������ ����.
#ifdef _VS2008PORTING
            for (int i = 0; i < MAX_TRADE_INVEN; ++i)
#else // _VS2008PORTING
			for(i = 0; i < MAX_TRADE_INVEN; ++i)
#endif // _VS2008PORTING
            {
                if (-1 == m_aYourInvenBackUp[i].Type)
                {
                    m_aYourInvenBackUp[i] = *pYourItemObj;
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveYourItemAdd()
// �Լ� ���� : �������� ������ �������� �߰��Ǿ��ٰ� �˷��� �� ó��.
// �Ű� ���� : byYourInvenIndex	: ���� �ŷ� ������ ��ġ ����.
//			   pbyItemPacket	: ���� �ŷ� ������ ����.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveYourItemAdd(BYTE byYourInvenIndex,
											  BYTE* pbyItemPacket)
{
	m_pYourInvenCtrl->AddItem(byYourInvenIndex, pbyItemPacket);
	AlertYourTradeInven();
	::PlayBuffer(SOUND_GET_ITEM01);
}

//*****************************************************************************
// �Լ� �̸� : AlertYourTradeInven()
// �Լ� ���� : ������ ����� �������� ���Ͽ� �����϶�� �Ǵ��� �ϴ� �Լ�.
//*****************************************************************************
void CNewUITrade::AlertYourTradeInven()
{
#ifndef _VS2008PORTING		// #ifndef
	int i, j;
#endif // _VS2008PORTING
    int nCount = 0;
    int nCompareItemType[10];

    m_bTradeAlert = false;

    // ����� �������� �������� �˻��Ѵ�.
	int nYourItems = m_pYourInvenCtrl->GetNumberOfItems();
	ITEM* pYourItemObj;
	int nCompareValue;

#ifdef _VS2008PORTING
	for (int i = 0; i < nYourItems; ++i)
#else // _VS2008PORTING
	for (i = 0; i < nYourItems; ++i)
#endif // _VS2008PORTING
	{
		pYourItemObj = m_pYourInvenCtrl->GetItem(i);
#ifdef _VS2008PORTING
		for (int j = 0; j < MAX_TRADE_INVEN; ++j)
#else // _VS2008PORTING
		for (j = 0; j < MAX_TRADE_INVEN; ++j)
#endif // _VS2008PORTING
		{
			if (m_aYourInvenBackUp[j].Type == pYourItemObj->Type)
			{
				nCompareValue = ::CompareItem(m_aYourInvenBackUp[j], *pYourItemObj);
				if (1 == nCompareValue)		// m_aYourInvenBackUp[j]�� �� ���� ���.
                {
                    m_bTradeAlert = true;
					pYourItemObj->byColorState = ITEM_COLOR_TRADE_WARNING;
				}
				else
				{
					if (0 == nCompareValue)	// ���� ���.
						nCompareItemType[nCount++] = m_aYourInvenBackUp[j].Type;

					pYourItemObj->byColorState = ITEM_COLOR_NORMAL;
					break;
				}
			}
		}
	}

    // �̹� ���� �������� ��ϵǾ��� ��.
    if (nCount > 0)
    {
        m_bTradeAlert = false;
#ifdef _VS2008PORTING
        for (int i = 0; i < nCount; ++i)
#else // _VS2008PORTING
        for (i = 0; i < nCount; ++i)
#endif // _VS2008PORTING
        {
#ifdef _VS2008PORTING
			for (int j= 0; j < nYourItems; ++j)
#else // _VS2008PORTING
			for (j= 0; j < nYourItems; ++j)
#endif // _VS2008PORTING
			{
				pYourItemObj = m_pYourInvenCtrl->GetItem(j);
				if (nCompareItemType[i] == pYourItemObj->Type)
					pYourItemObj->byColorState = ITEM_COLOR_NORMAL;
			}
        }
    }
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveMyTradeGold()
// �Լ� ���� : �������� �ڽ��� ���� �ŷ�â�� ���� ����� �˷��� �� ó��.
// �Ű� ���� : bySuccess	: �����̸� 1, ���и� 0.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveMyTradeGold(BYTE bySuccess)
{
	m_nMyTradeGold = bySuccess ? m_nTempMyTradeGold : 0;
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveYourConfirm()
// �Լ� ���� : �������� ������ �ŷ� Ȯ��(����) ��ư�� �����ٰ� �˷��� �� ó��.
// �Ű� ���� : byState	: �ŷ� Ȯ��(����) ���� ��.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveYourConfirm(BYTE byState)
{
	switch (byState)
	{
	case 0:	m_bYourConfirm = false;	break;	// �ŷ� ���� ��ư�� ���ȴ�.
	case 1:	m_bYourConfirm = true;	break;	// �ŷ� ���� ���.
	case 2:	m_bMyConfirm = false;
#ifdef YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED
		m_bYourConfirm = false;
        m_nMyTradeWait = 150;
#endif	// YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED
		break;	// ��� ��ȯ �Ұ�(��밡 �ŷ�â���� �̵��� ���ߴٴ� ���)
	case 3:	break;							// ��� ��ȯ �Ұ� ���� Ǯ��.
	}

	PlayBuffer(SOUND_CLICK01);
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveTradeExit()
// �Լ� ���� : �������� �ŷ� ������ ���� �޾��� �� ó��.
// �Ű� ���� : byState	: �ŷ� ���� ���� ��.
//						  ������ �ŷ� ������ ���� 1.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveTradeExit(BYTE byState)
{
	switch (byState)
	{
	case 0:		// 492 "�ŷ��� ����߽��ϴ�."(��밡 �ŷ� ���)
		{
			g_pChatListBox->AddText("", GlobalText[492], SEASON3B::TYPE_ERROR_MESSAGE);
     
			// �ŷ� â�� ��ϵ� �������� ����Ѵ�.
			m_bTradeAlert = false;

			int nYourItems = m_pYourInvenCtrl->GetNumberOfItems();
			for (int i = 0; i < nYourItems; ++i)
				BackUpYourInven(m_pYourInvenCtrl->GetItem(i));

		}
		break;

	case 2:		// 495 "���â�� �������� �ŷ��� ��ҵǾ����ϴ�."
		g_pChatListBox->AddText("", GlobalText[495], SEASON3B::TYPE_ERROR_MESSAGE);
		break;

	case 3:		// 496 "�ŷ� ��û�� ��ҵǾ����ϴ�."
		g_pChatListBox->AddText("", GlobalText[496], SEASON3B::TYPE_ERROR_MESSAGE);
		break;

	case 4:		// 2108 "��ȭ �������� �ŷ� �Ͻ� �� �����ϴ�."
		g_pChatListBox->AddText("", GlobalText[2108], SEASON3B::TYPE_ERROR_MESSAGE);
		break;
	}

   	SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();

	g_MessageBox->PopMessageBox();	// ���� �� �ִ� �޽��� �ڽ� ����.

	g_pNewUISystem->Hide(SEASON3B::INTERFACE_TRADE);
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveTradeItems()
// �Լ� ���� : �������� �ŷ� �������� ������� ���� �޾��� �� ó��.
// �Ű� ���� : nIndex		: �ŷ�â�� ���� ������ ��ġ ����.
//			   pbyItemPacket: �������� �޴� ������ ����.
//*****************************************************************************
void CNewUITrade::ProcessToReceiveTradeItems(int nIndex, BYTE* pbyItemPacket)
{
	SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();

	if (nIndex >= 0 && nIndex < (m_pMyInvenCtrl->GetNumberOfColumn()
		* m_pMyInvenCtrl->GetNumberOfRow()))
		m_pMyInvenCtrl->AddItem(nIndex, pbyItemPacket);
}

int SEASON3B::CNewUITrade::GetPointedItemIndexMyInven()
{
	return m_pMyInvenCtrl->GetPointedSquareIndex();
}

int SEASON3B::CNewUITrade::GetPointedItemIndexYourInven()
{
	return m_pYourInvenCtrl->GetPointedSquareIndex();
}
