//*****************************************************************************
// File: NewUIStorageInventory.cpp
//
// Desc: implementation of the CNewUIStorageInventory class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "NewUIStorageInventory.h"
#include "NewUISystem.h"
#include "NewUICustomMessageBox.h"
#include "ZzzInventory.h"
#include "wsclientinline.h"
#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
#include "MsgBoxIGSCommon.h"
#endif // KJH_PBG_ADD_INGAMESHOP_SYSTEM

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNewUIStorageInventory::CNewUIStorageInventory() 
{
	m_pNewUIMng = NULL;
	m_pNewInventoryCtrl = NULL;
	m_Pos.x = m_Pos.y = 0;
}

CNewUIStorageInventory::~CNewUIStorageInventory()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : â�� â ����.
// �Ű� ���� : pNewUIMng	: CNewUIManager ������Ʈ �ּ�.
//			   x			: x ��ǥ.
//			   y			: y ��ǥ.
//*****************************************************************************
bool CNewUIStorageInventory::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if (NULL == pNewUIMng || NULL == g_pNewUI3DRenderMng
		|| NULL == g_pNewItemMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_STORAGE, this);

	m_pNewInventoryCtrl = new CNewUIInventoryCtrl;
	if (false == m_pNewInventoryCtrl->Create(
		g_pNewUI3DRenderMng, g_pNewItemMng, this, x + 15, y + 36, 8, 15))
	{
		SAFE_DELETE(m_pNewInventoryCtrl);
		return false;
	}

	SetPos(x, y);

	LoadImages();

// ��ư�� ����.
	int anBtnPosX[MAX_BTN] = { 38, 78, 118 };
	int anToolTipText[MAX_BTN] = { 235, 236, 242 };
	for (int i = BTN_INSERT_ZEN; i < MAX_BTN; ++i)
	{
		m_abtn[i].ChangeButtonImgState(true, IMAGE_STORAGE_BTN_INSERT_ZEN + i);
		m_abtn[i].ChangeButtonInfo(x + anBtnPosX[i], y + 390, 36, 29);
		m_abtn[i].ChangeToolTipText(GlobalText[anToolTipText[i]], true);
	}

	m_bLock = false;
	SetItemAutoMove(false);
	InitBackupItemInfo();

	Show(false);	

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : â Release.
//*****************************************************************************
void CNewUIStorageInventory::Release()
{
	UnloadImages();

	SAFE_DELETE(m_pNewInventoryCtrl);

	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPos()
// �Լ� ���� : â ��ġ ����.
//*****************************************************************************
void CNewUIStorageInventory::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

//*****************************************************************************
// �Լ� �̸� : UpdateMouseEvent()
// �Լ� ���� : ���콺 �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUIStorageInventory::UpdateMouseEvent()
{
	if (m_pNewInventoryCtrl && false == m_pNewInventoryCtrl->UpdateMouseEvent())
		return false;

	ProcessInventoryCtrl();

	if (ProcessBtns())
		return false;

	// â ���� Ŭ���� ���� UIó�� �� �̵� �Ұ�
	if(CheckMouseIn(m_Pos.x, m_Pos.y, STORAGE_WIDTH, STORAGE_HEIGHT))
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
bool CNewUIStorageInventory::UpdateKeyEvent()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE) == true)
	{
		if(SEASON3B::IsPress(VK_ESCAPE) == true)
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_STORAGE);
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
bool CNewUIStorageInventory::Update()
{
	if(m_pNewInventoryCtrl && false == m_pNewInventoryCtrl->Update())
		return false;

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : â ����.
// ��ȯ ��	 : true�� ����.
//*****************************************************************************
bool CNewUIStorageInventory::Render()
{
	::EnableAlphaTest();

	::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderBackImage();
	RenderText();

	if (m_pNewInventoryCtrl)
		m_pNewInventoryCtrl->Render();

	for (int i = BTN_INSERT_ZEN; i < MAX_BTN; ++i)
		m_abtn[i].Render();

	::DisableAlphaBlend();
	
	return true;
}

//*****************************************************************************
// �Լ� �̸� : RenderBackImage()
// �Լ� ���� : â ���� �̹��� ����.
//*****************************************************************************
void CNewUIStorageInventory::RenderBackImage()
{
	RenderImage(IMAGE_STORAGE_BACK,
		m_Pos.x, m_Pos.y, float(STORAGE_WIDTH), float(STORAGE_HEIGHT));
	RenderImage(IMAGE_STORAGE_TOP,
		m_Pos.x, m_Pos.y, float(STORAGE_WIDTH), 64.f);
	RenderImage(IMAGE_STORAGE_LEFT,
		m_Pos.x, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_STORAGE_RIGHT,
		m_Pos.x+STORAGE_WIDTH-21, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_STORAGE_BOTTOM,
		m_Pos.x, m_Pos.y+STORAGE_HEIGHT-45, float(STORAGE_WIDTH), 45.f);

	RenderImage(IMAGE_STORAGE_MONEY,
		m_Pos.x+10, m_Pos.y+342, 170.f, 46.f);
}

//*****************************************************************************
// �Լ� �̸� : RenderText()
// �Լ� ���� : �ؽ�Ʈ ����.
//*****************************************************************************
void CNewUIStorageInventory::RenderText()
{
	unicode::t_char szTemp[128];
	int nTempZen;

	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetBgColor(0);

// ����.
	unicode::_sprintf(
		szTemp, "%s (%s)", GlobalText[234], GlobalText[m_bLock ? 241 : 240]);
	if (m_bLock)
		g_pRenderText->SetTextColor(240, 32, 32, 255);
	else
		g_pRenderText->SetTextColor(216, 216, 216, 255);
	g_pRenderText->RenderText(
		m_Pos.x, m_Pos.y+11, szTemp, STORAGE_WIDTH, 0, RT3_SORT_CENTER);

// ��.
	nTempZen = CharacterMachine->StorageGold;
    ::ConvertGold(nTempZen, szTemp);
	// ���� �� ������ ��ȭ. (��� -> ��Ȳ�� -> ������).
	g_pRenderText->SetTextColor(::getGoldColor(nTempZen));
	g_pRenderText->RenderText(
		m_Pos.x+168, m_Pos.y+342+8, szTemp, 0, 0, RT3_WRITE_RIGHT_TO_LEFT);

//  â�����.
	g_pRenderText->SetTextColor(240, 64, 64, 255);
	// 266 "â�����"
    g_pRenderText->RenderText(m_Pos.x+10+15, m_Pos.y+342+29, GlobalText[266]);

	// �Ʒ� ����� double�� ����ؾ� ������ ����.
#ifdef CSK_FIX_WOPS_K30648_STORAGEVALUE
	
#ifdef LDK_FIX_STORAGE_CHARGE
	__int64 iTotalLevel = CharacterAttribute->Level + Master_Level_Data.nMLevel;	// ���շ���
#else // LDK_FIX_STORAGE_CHARGE
	__int64 iTotalLevel = CharacterAttribute->Level + Master_Level_Data.nMLevel + 1;	// ���շ���
#endif // LDK_FIX_STORAGE_CHARGE

	nTempZen = int(double(iTotalLevel) * double(iTotalLevel) * 0.04);
	nTempZen += m_bLock ? int(CharacterAttribute->Level) * 2 : 0;
#else // CSK_FIX_WOPS_K30648_STORAGEVALUE 
	nTempZen = int(double(CharacterAttribute->Level)
		* double(CharacterAttribute->Level) * 0.04);
	nTempZen += m_bLock ? int(CharacterAttribute->Level) * 2 : 0;
#endif // CSK_FIX_WOPS_K30648_STORAGEVALUE
    nTempZen = max(1, nTempZen);
    if (nTempZen >= 1000)
		nTempZen = nTempZen / 100 * 100;	// 10�� �ڸ� 00���� �����.
	else if (nTempZen >= 100)
		nTempZen = nTempZen / 10 * 10;		// 1�� �ڸ� 0���� �����.
    ::ConvertGold(nTempZen, szTemp);
	g_pRenderText->SetTextColor(255, 220, 150, 255);
	g_pRenderText->RenderText(
		m_Pos.x+168, m_Pos.y+342+29, szTemp, 0, 0, RT3_WRITE_RIGHT_TO_LEFT);
}

//*****************************************************************************
// �Լ� �̸� : GetLayerDepth()
// �Լ� ���� : â�� ���̾�� ����.
//*****************************************************************************
float CNewUIStorageInventory::GetLayerDepth()
{
	return 2.2f;
}

//*****************************************************************************
// �Լ� �̸� : GetInventoryCtrl()
// �Լ� ���� : (���� �����) ����ǰ ��Ʈ���� ����.
//*****************************************************************************
CNewUIInventoryCtrl* CNewUIStorageInventory::GetInventoryCtrl() const
{
	return m_pNewInventoryCtrl;
}

//*****************************************************************************
// �Լ� �̸� : LoadImages()
// �Լ� ���� : �̹��� ���ҽ� �ε�.
//*****************************************************************************
void CNewUIStorageInventory::LoadImages()
{
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_STORAGE_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back01.tga", IMAGE_STORAGE_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-L.tga", IMAGE_STORAGE_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-R.tga", IMAGE_STORAGE_RIGHT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_STORAGE_BOTTOM, GL_LINEAR);
	
	LoadBitmap("Interface\\newui_Bt_money01.tga", IMAGE_STORAGE_BTN_INSERT_ZEN, GL_LINEAR);
	LoadBitmap("Interface\\newui_Bt_money02.tga", IMAGE_STORAGE_BTN_TAKE_ZEN, GL_LINEAR);
	LoadBitmap("Interface\\newui_Bt_lock02.tga", IMAGE_STORAGE_BTN_UNLOCK, GL_LINEAR);
	LoadBitmap("Interface\\newui_Bt_lock.tga", IMAGE_STORAGE_BTN_LOCK, GL_LINEAR);

	LoadBitmap("Interface\\newui_item_money3.tga", IMAGE_STORAGE_MONEY, GL_LINEAR);
}

//*****************************************************************************
// �Լ� �̸� : LoadImages()
// �Լ� ���� : �̹��� ���ҽ� ����.
//*****************************************************************************
void CNewUIStorageInventory::UnloadImages()
{
	DeleteBitmap(IMAGE_STORAGE_MONEY);

	DeleteBitmap(IMAGE_STORAGE_BTN_LOCK);
	DeleteBitmap(IMAGE_STORAGE_BTN_UNLOCK);
	DeleteBitmap(IMAGE_STORAGE_BTN_TAKE_ZEN);
	DeleteBitmap(IMAGE_STORAGE_BTN_INSERT_ZEN);

	DeleteBitmap(IMAGE_STORAGE_BOTTOM);
	DeleteBitmap(IMAGE_STORAGE_RIGHT);
	DeleteBitmap(IMAGE_STORAGE_LEFT);
	DeleteBitmap(IMAGE_STORAGE_TOP);
	DeleteBitmap(IMAGE_STORAGE_BACK);
}

//*****************************************************************************
// �Լ� �̸� : LockStorage()
// �Լ� ���� : â�� ���.
// �Ű� ���� : bLock	: true�� ���.
//*****************************************************************************
void CNewUIStorageInventory::LockStorage(bool bLock)
{
	m_bLock = bLock;
	ChangeLockBtnImage();
}

//*****************************************************************************
// �Լ� �̸� : ChangeLockBtnImage()
// �Լ� ���� : m_bLock�� ���� ���� ��� ��ư �̹����� ��ü.
//*****************************************************************************
void CNewUIStorageInventory::ChangeLockBtnImage()
{
	m_abtn[BTN_LOCK].UnRegisterButtonState();
	if (m_bLock)
		m_abtn[BTN_LOCK].ChangeButtonImgState(true, IMAGE_STORAGE_BTN_LOCK);
	else
		m_abtn[BTN_LOCK].ChangeButtonImgState(true, IMAGE_STORAGE_BTN_UNLOCK);
}

//*****************************************************************************
// �Լ� �̸� : ProcessClosing()
// �Լ� ���� : â�� ���� �� ó��.
// ��ȯ ��	 : true �� �ݱ� ����.
//*****************************************************************************
bool CNewUIStorageInventory::ProcessClosing()
{
	// SendRequestEquipmentItem()�� ������ ���� ReceiveEquipmentItem()�� ����
	//�ʾҴٸ� â�� ���� ����.
	if (EquipmentItem)
		return false;

	SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	DeleteAllItems();
	SendRequestStorageExit();
	return true;
}

//*****************************************************************************
// �Լ� �̸� : InsertItem()
// �Լ� ���� :â�� �������� ����.
// ��ȯ ��	 : true�� ����.
// �Ű� ���� : nIndex		: m_pNewInventoryCtrl���� ������ ���� �ڸ�.
//			   pbyItemPacket: �������� �޴� ������ ����.
//*****************************************************************************
bool CNewUIStorageInventory::InsertItem(int nIndex, BYTE* pbyItemPacket)
{
	if (m_pNewInventoryCtrl)
		return m_pNewInventoryCtrl->AddItem(nIndex, pbyItemPacket);
	
	return false;
}

//*****************************************************************************
// �Լ� �̸� : DeleteAllItems()
// �Լ� ���� : â���� ��� ������ ����.
//*****************************************************************************
void CNewUIStorageInventory::DeleteAllItems()
{
	if (m_pNewInventoryCtrl)
		m_pNewInventoryCtrl->RemoveAllItems();
}

//*****************************************************************************
// �Լ� �̸� : ProcessInventoryCtrl()
// �Լ� ���� : â�� �κ��丮 ��Ʈ�� ���콺 �̺�Ʈ ó��.
//*****************************************************************************
void CNewUIStorageInventory::ProcessInventoryCtrl()
{
	if (NULL == m_pNewInventoryCtrl)
		return;
	CNewUIPickedItem* pPickedItem = CNewUIInventoryCtrl::GetPickedItem();

	if( pPickedItem )
	{
		ITEM* pItemObj = pPickedItem->GetItem();
		if (NULL == pItemObj)	return;
		if (SEASON3B::IsPress(VK_LBUTTON))
		{
			// �κ��丮���� �� ���ΰ�?
			if (pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())
			{
				int nSrcIndex = pPickedItem->GetSourceLinealPos();
				int nDstIndex = pPickedItem->GetTargetLinealPos(m_pNewInventoryCtrl);
				if (nDstIndex != -1 && m_pNewInventoryCtrl->CanMove(nDstIndex, pItemObj))
					SendRequestItemToStorage(pItemObj, MAX_EQUIPMENT_INDEX+nSrcIndex, nDstIndex);
			}
			// â���� �� ���ΰ�?(�ڽ� ��)
			else if (pPickedItem->GetOwnerInventory() == m_pNewInventoryCtrl)
			{
				int nSrcIndex = pPickedItem->GetSourceLinealPos();
				int nDstIndex = pPickedItem->GetTargetLinealPos(m_pNewInventoryCtrl);
				if (nDstIndex != -1 && m_pNewInventoryCtrl->CanMove(nDstIndex, pItemObj))
				{
					SendRequestEquipmentItem(REQUEST_EQUIPMENT_STORAGE, nSrcIndex,
						pItemObj, REQUEST_EQUIPMENT_STORAGE, nDstIndex);
				}
			}
			// ��񿡼� �� ���ΰ�?(���� CNewUIInventoryCtrl�� ������� �����Ƿ�)
			else if (pItemObj->ex_src_type == ITEM_EX_SRC_EQUIPMENT)
			{
				int nSrcIndex = pPickedItem->GetSourceLinealPos();
				int nDstIndex = pPickedItem->GetTargetLinealPos(m_pNewInventoryCtrl);
				if (nDstIndex != -1 && m_pNewInventoryCtrl->CanMove(nDstIndex, pItemObj))
					SendRequestItemToStorage(pItemObj, nSrcIndex, nDstIndex);
			}
		}
		else
		{
		#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ â�� ��ǰ ��Ͻ� �κ� WarningĮ�� [lem_2010.9.8]
			if( ::IsStoreBan( pItemObj ) )	m_pNewInventoryCtrl->SetSquareColorNormal(1.0f, 0.0f, 0.0f );	
			else							m_pNewInventoryCtrl->SetSquareColorNormal(0.1f, 0.4f, 0.8f );
		#endif // LEM_ADD_LUCKYITEM
		}	
	}
	else if (SEASON3B::IsPress(VK_RBUTTON))
	{
		ProcessStorageItemAutoMove();
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessStorageItemAutoMove()
// �Լ� ���� : â�� ������ �ڵ� �̵� ó��.
//*****************************************************************************
void CNewUIStorageInventory::ProcessStorageItemAutoMove()
{
	// Ŀ���� �������� �پ� ������ ó������ ����.
	if (g_pPickedItem)
		if (g_pPickedItem->GetItem())
			return;

	// ������ �ڵ� �̵� ���� �� �� ������ �ڵ� �̵��� ���� ����.
	if (IsItemAutoMove())
		return;
	
	ITEM* pItemObj = m_pNewInventoryCtrl->FindItemAtPt(MouseX, MouseY);
	if (pItemObj)
	{
		int nDstIndex = g_pMyInventory->FindEmptySlot(pItemObj);
		if (-1 != nDstIndex)
		{
			SetItemAutoMove(true);
			
			int nSrcIndex
				= pItemObj->y * m_pNewInventoryCtrl->GetNumberOfColumn()
					+ pItemObj->x;
			SendRequestItemToMyInven(pItemObj, nSrcIndex, MAX_EQUIPMENT_INDEX+nDstIndex);

			::PlayBuffer(SOUND_GET_ITEM01);
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessMyInvenItemAutoMove()
// �Լ� ���� : �κ��丮â���� â��â���� ������ �ڵ� �̵� ó��.
//*****************************************************************************
void CNewUIStorageInventory::ProcessMyInvenItemAutoMove()
{
	if (g_pPickedItem)
		if (g_pPickedItem->GetItem())
			return;
		
	// ������ �ڵ� �̵� ���� �� �� ������ �ڵ� �̵��� ���� ����.
	if (IsItemAutoMove())
		return;
		
	CNewUIInventoryCtrl* pMyInvenCtrl = g_pMyInventory->GetInventoryCtrl();
	ITEM* pItemObj = pMyInvenCtrl->FindItemAtPt(MouseX, MouseY);
	if (pItemObj)
	{
		if (pItemObj->Type == ITEM_HELPER+20)	// �������� ����, ����� ����, ������ ����
			return;

		int nDstIndex = FindEmptySlot(pItemObj);
		if (-1 != nDstIndex)
		{
			SetItemAutoMove(true);
			
			int nSrcIndex
				= pItemObj->y * pMyInvenCtrl->GetNumberOfColumn()
				+ pItemObj->x;
			SendRequestItemToStorage(pItemObj, MAX_EQUIPMENT_INDEX+nSrcIndex, nDstIndex);
			
			::PlayBuffer(SOUND_GET_ITEM01);
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : SendRequestItemToMyInven()
// �Լ� ���� : �������� �κ��丮â���� �̵��� ������ �䱸.
// �Ű� ���� : pItemObj		: ������ ������Ʈ �ּ�.
//			   nStorageIndex: â������ ������ ��ġ.
//			   nInvenIndex	: �̵� ��ų �κ��丮â ������ ��ġ.
//*****************************************************************************
void CNewUIStorageInventory::SendRequestItemToMyInven(ITEM* pItemObj, int nStorageIndex, int nInvenIndex)
{
	if (!IsStorageLocked() || IsCorrectPassword())	// ������� �ʰ� �н����� ����Ǿ� �ִ� ���.
	{
		SendRequestEquipmentItem(REQUEST_EQUIPMENT_STORAGE, nStorageIndex,
			pItemObj, REQUEST_EQUIPMENT_INVENTORY, nInvenIndex);

	}
	else
	{
		SetBackupInvenIndex(nInvenIndex);
		if (!IsItemAutoMove())
			g_pPickedItem->HidePickedItem();

		SEASON3B::CreateMessageBox(
			MSGBOX_LAYOUT_CLASS(SEASON3B::CPasswordKeyPadMsgBoxLayout));
	}
}

//*****************************************************************************
// �Լ� �̸� : SendRequestItemToStorage()
// �Լ� ���� : �������� â��â���� �̵��� ������ �䱸.
// �Ű� ���� : pItemObj		: ������ ������Ʈ �ּ�.
//			   nStorageIndex: �κ��丮â������ ������ ��ġ.
//			   nInvenIndex	: �̵� ��ų â��â ������ ��ġ.
//*****************************************************************************
void CNewUIStorageInventory::SendRequestItemToStorage(ITEM* pItemObj, int nInvenIndex, int nStorageIndex)
{
	if (::IsStoreBan(pItemObj))	// â�� ���� �� ���� �������ΰ�?
	{
#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
		// MessageBox
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
 		pMsgBox->Initialize(GlobalText[3028], GlobalText[667]);
#endif // KJH_PBG_ADD_INGAMESHOP_SYSTEM

		g_pChatListBox->AddText(
			"", GlobalText[667], SEASON3B::TYPE_ERROR_MESSAGE);
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();

		if (IsItemAutoMove())
			SetItemAutoMove(false);
	}
	else
	{
		// ������ ����.
     	SendRequestEquipmentItem(REQUEST_EQUIPMENT_INVENTORY, nInvenIndex,
			pItemObj, REQUEST_EQUIPMENT_STORAGE, nStorageIndex);
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessBtns()
// �Լ� ���� : ��ư ������ �̺�Ʈ ó��.
// ��ȯ ��	 : ó�� ������ true.
//*****************************************************************************
bool CNewUIStorageInventory::ProcessBtns()
{
	if (m_abtn[BTN_INSERT_ZEN].UpdateMouseEvent())
	{
		SEASON3B::CreateMessageBox(
			MSGBOX_LAYOUT_CLASS(SEASON3B::CZenReceiptMsgBoxLayout));
		return true;
	}
	else if (m_abtn[BTN_TAKE_ZEN].UpdateMouseEvent())
	{
		SEASON3B::CreateMessageBox(
			MSGBOX_LAYOUT_CLASS(SEASON3B::CZenPaymentMsgBoxLayout));
		return true;
	}
	else if (m_abtn[BTN_LOCK].UpdateMouseEvent())
	{
		if (m_bLock)
#ifdef LDK_MOD_GLOBAL_STORAGELOCK_CHANGE
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CStorageUnlockMsgBoxLayout));
		}
#else //LDK_MOD_GLOBAL_STORAGELOCK_CHANGE
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CStorageUnlockKeyPadMsgBoxLayout));
		}
#endif //LDK_MOD_GLOBAL_STORAGELOCK_CHANGE
		else
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CStorageLockKeyPadMsgBoxLayout));
		}
		return true;
	}
	else if (SEASON3B::IsPress(VK_LBUTTON) && CheckMouseIn(m_Pos.x+169, m_Pos.y+7, 13, 12))
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_STORAGE);
		return true;
	}

	return false;
}

//*****************************************************************************
// �Լ� �̸� : SetItemAutoMove()
// �Լ� ���� : ������ �ڵ� �̵� ����.
//*****************************************************************************
void CNewUIStorageInventory::SetItemAutoMove(bool bItemAutoMove)
{
	m_bItemAutoMove = bItemAutoMove;

	if (bItemAutoMove)
	{
		m_nBackupMouseX = MouseX;
		m_nBackupMouseY = MouseY;
	}
	else
		m_nBackupMouseX = m_nBackupMouseY = 0;
}

//*****************************************************************************
// �Լ� �̸� : InitBackupItemInfo()
// �Լ� ���� : ��� ������ ���� �ʱ�ȭ.
//*****************************************************************************
void CNewUIStorageInventory::InitBackupItemInfo()
{
	m_bTakeZen = false;
	m_nBackupTakeZen = 0;
	m_nBackupInvenIndex = -1;
}

//*****************************************************************************
// �Լ� �̸� : SetBackupTakeZen()
// �Լ� ���� : ��ݵ� �� ���.
// �Ű� ���� : nZen	: ��ݵ� �� �׼�.
//*****************************************************************************
void CNewUIStorageInventory::SetBackupTakeZen(int nZen)
{
	m_bTakeZen = true;
	m_nBackupTakeZen = nZen;
}

//*****************************************************************************
// �Լ� �̸� : SetBackupInvenIndex()
// �Լ� ���� : �κ��丮â ������ ��ġ ���.
// �Ű� ���� : nInvenIndex	: �κ��丮â ������ ��ġ.
//*****************************************************************************
void CNewUIStorageInventory::SetBackupInvenIndex(int nInvenIndex)
{
	m_bTakeZen = false;
	m_nBackupInvenIndex = nInvenIndex;
}

//*****************************************************************************
// �Լ� �̸� : LockStorage()
// �Լ� ���� : pItemObj �������� â�� ��� �� �� �ִ� ��ġ ã��.
// ��ȯ ��	 : â�� ��� �� �� �ִ� ��ġ.
//			�������� ���� ������ ������ -1.
// �Ű� ���� : pItemObj	: üũ�� ������ ������Ʈ.
//*****************************************************************************
int CNewUIStorageInventory::FindEmptySlot(ITEM* pItemObj)
{
	if (pItemObj == NULL)
		return -1;

	ITEM_ATTRIBUTE* pItemAttr = &ItemAttribute[pItemObj->Type];
	if(m_pNewInventoryCtrl)
		return m_pNewInventoryCtrl->FindEmptySlot(
			pItemAttr->Width, pItemAttr->Height);

	return -1;
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveStorageStatus()
// �Լ� ���� : �������� â�� ���� �޾��� �� ó��.
//			ReceiveStorageStatus() �Լ� ���� �� ȣ��.
// �Ű� ���� : byStatus	: â�� ����.
//*****************************************************************************
void CNewUIStorageInventory::ProcessToReceiveStorageStatus(BYTE byStatus)
{
	switch (byStatus)
	{
	case 0:	// ����
		LockStorage(false);
		SetCorrectPassword(false);
		break;

	case 1: // ���
		LockStorage(true);
		SetCorrectPassword(false);
		break;

	case 10: // ��� ����ġ
		SEASON3B::CreateOkMessageBox(GlobalText[440]);
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
		ProcessStorageItemAutoMoveFailure();
		break;

	case 11: // â�� ����� �ִµ� �� ��׷� ��
		SEASON3B::CreateOkMessageBox(GlobalText[441]);
		break;

	case 12: // ��� �������� ����� �°� �Է��ߴ�.
		if (IsStorageLocked() && !IsCorrectPassword())
		{
			if (m_bTakeZen)	// ����ΰ�?
			{
				SendRequestStorageGold(1, GetBackupTakeZen());
				InitBackupItemInfo();
			}
			else
			{
				ITEM* pItemObj;
				int nStorageIndex;

				if (IsItemAutoMove())
				{
					pItemObj = m_pNewInventoryCtrl->FindItemAtPt(
						m_nBackupMouseX, m_nBackupMouseY);
					nStorageIndex
						= pItemObj->y * m_pNewInventoryCtrl->GetNumberOfColumn()
							+ pItemObj->x;
				}
				else
				{
					nStorageIndex = g_pPickedItem->GetSourceLinealPos();
					pItemObj = g_pPickedItem->GetItem();
				}

				SendRequestEquipmentItem(
					REQUEST_EQUIPMENT_STORAGE, nStorageIndex,
					pItemObj, REQUEST_EQUIPMENT_INVENTORY, GetBackupInvenIndex());

				InitBackupItemInfo();
			}
		}
		LockStorage(true);
		SetCorrectPassword(true);
		break;

	case 13: // ��۶� �ֹι�ȣ �߸���
		SEASON3B::CreateOkMessageBox(GlobalText[401]);
		break;
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessToReceiveStorageItems()
// �Լ� ���� : �������� â�� �������� ������� ���� �޾��� �� ó��.
// �Ű� ���� : nIndex		: â�� ���� ������ ��ġ ����.
//			   pbyItemPacket: �������� �޴� ������ ����.
//*****************************************************************************
void CNewUIStorageInventory::ProcessToReceiveStorageItems(int nIndex, BYTE* pbyItemPacket)
{
	SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();

	if (nIndex >= 0 && nIndex < (m_pNewInventoryCtrl->GetNumberOfColumn()
		* m_pNewInventoryCtrl->GetNumberOfRow()))
	{
		if (IsItemAutoMove())
		{
			CNewUIInventoryCtrl* pMyInvenCtrl = g_pMyInventory->GetInventoryCtrl();
			ITEM* pItemObj = pMyInvenCtrl->FindItemAtPt(m_nBackupMouseX, m_nBackupMouseY);
			g_pMyInventory->GetInventoryCtrl()->RemoveItem(pItemObj);

			SetItemAutoMove(false);
		}

		InsertItem(nIndex, pbyItemPacket);
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessStorageItemAutoMoveSuccess()
// �Լ� ���� : â���� ��Ŭ������ �κ��丮�� ������ �ڵ� �̵��� ������ �� ����
//			  ���� �����ߴٰ� �˷��� �� ó��.
//*****************************************************************************
void CNewUIStorageInventory::ProcessStorageItemAutoMoveSuccess()
{
	if (!IsVisible())
		return;

	if (IsItemAutoMove())
	{
		ITEM* pItemObj = m_pNewInventoryCtrl->FindItemAtPt(m_nBackupMouseX, m_nBackupMouseY);
		m_pNewInventoryCtrl->RemoveItem(pItemObj);

		SetItemAutoMove(false);
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessStorageItemAutoMoveFailure()
// �Լ� ���� : â���� ��Ŭ������ �κ��丮�� ������ �ڵ� �̵��� ������ �� ����
//			  ���� �����ߴٰ� �˷��� �� ó��.
//*****************************************************************************
void CNewUIStorageInventory::ProcessStorageItemAutoMoveFailure()
{
	if (!IsVisible())
		return;

	InitBackupItemInfo();

	// �������� 0.3���̳� ������ �̵� ��Ŷ�� �� ������ ���� ó��.
	SetItemAutoMove(false);
}

int SEASON3B::CNewUIStorageInventory::GetPointedItemIndex()
{
	return m_pNewInventoryCtrl->GetPointedSquareIndex();
}
