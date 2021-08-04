// NewUIInGameShop.cpp: implementation of the NewUIInGameShop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef PBG_ADD_INGAMESHOP_UI_ITEMSHOP

#include "wsclientinline.h"
#include "iexplorer.h"
#include "NewUISystem.h"
#include "NewUIInGameShop.h"
#include "MsgBoxIGSBuyPackageItem.h"
#include "MsgBoxIGSBuySelectItem.h"
#include "MsgBoxIGSCommon.h"
#include "MsgBoxIGSStorageItemInfo.h"
#include "MsgBoxIGSGiftStorageItemInfo.h"
#include "MsgBoxIGSDeleteItemConfirm.h"

#ifdef FOR_WORK
	#include "./Utilities/Log/DebugAngel.h"
#endif // FOR_WORK

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace SEASON3B;

CNewUIInGameShop::CNewUIInGameShop()
{
	Init();
}

CNewUIInGameShop::~CNewUIInGameShop()
{
	Release();
}

void CNewUIInGameShop::Init()
{
	m_ItemAngle = false;
	m_bLoadBanner = false;		// ��� �ε�
	m_bBannerLink = false;		// ��� ��ũ �����Ѱ�

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_iStorageTotalItemCnt			= 0;
	m_iStorageCurrentPageItemCnt	= 0;
	m_iStorageTotalPage				= 0;
	m_iStorageCurrentPage			= 0;
	m_iSelectedStorageItemIndex		= 0;
	m_iStorageCurrentPageReceiveItemCnt = 0;
	m_bRequestCurrentPage			= false;
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

void CNewUIInGameShop::Release()
{
	UnloadImages();

	ReleaseBanner();
	
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}

	ClearAllStorageItem();
}

bool CNewUIInGameShop::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if(pNewUIMng  == NULL)
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_INGAMESHOP, this);
	
	SetPos(x, y);
	LoadImages();
	SetBtnInfo();
	Show(false);	//visible()�� flase��

	return true;
}

void CNewUIInGameShop::SetPos( int x, int y )
{
	m_Pos.x = x; 
	m_Pos.y = y;
}

////////////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////////////

//----------------------------------------------------------
// Render Main
bool CNewUIInGameShop::Render()
{
	EnableAlphaTest();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	RenderFrame();
	RenderButtons();	
	RenderTexts();
	RenderBanner();
	RenderListBox();
	RenderDisplayItems();

	DisableAlphaBlend();
	return true;
}

//----------------------------------------------------------
// Render Frame
void CNewUIInGameShop::RenderFrame()
{
	// �ΰ��Ӽ� ���
	RenderImage(IMAGE_IGS_BACK, m_Pos.x, m_Pos.y, IMAGE_IGS_BACK_WIDTH, IMAGE_IGS_BACK_HEIGHT);
	
	int iSizeCategory = g_InGameShopSystem->GetSizeCategoriesAsSelectedZone();

	if( iSizeCategory < 0 )
		return;
		
	// Category Deco Middle Render
	POINT CategoryDecoMiddlePos;
	CategoryDecoMiddlePos.x = m_CategoryButton.GetPos(0).x
								+(IMAGE_IGS_CATEGORY_BTN_WIDTH/2)
								-(IMAGE_IGS_CATEGORY_DECO_MIDDLE_WIDTH/2);
	
	for(int i=0 ; i<iSizeCategory-1 ; i++)
	{
		CategoryDecoMiddlePos.y = m_CategoryButton.GetPos(i).y+IMAGE_IGS_CATEGORY_BTN_HEIGHT-1;

		RenderImage(IMAGE_IGS_CATEGORY_DECO_MIDDLE,
					CategoryDecoMiddlePos.x, CategoryDecoMiddlePos.y, 
					IMAGE_IGS_CATEGORY_DECO_MIDDLE_WIDTH, IMAGE_IGS_CATEGORY_DECO_MIDDLE_HEIGHT);
	}

	// Category Deco Down Render
	RenderImage(IMAGE_IGS_CATEGORY_DECO_DOWN,
					m_Pos.x, m_CategoryButton.GetPos(iSizeCategory-1).y-10, 
					IMAGE_IGS_CATEGORY_DECO_DOWN_WIDTH, IMAGE_IGS_CATEGORY_DECO_DOWN_HEIGHT);

	// �����۹ڽ� �ΰ�
	for(int cnt=g_InGameShopSystem->GetSizePackageAsDisplayPackage() ; cnt<INGAMESHOP_DISPLAY_ITEMLIST_SIZE ; cnt++)
	{
		RenderImage(IMAGE_IGS_ITEMBOX_LOGO,
					m_Pos.x+IMAGE_IGS_ITEMBOX_LOGO_POS_X+((cnt%IGS_NUM_ITEMS_WIDTH)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_X), 
					m_Pos.y+IMAGE_IGS_ITEMBOX_LOGO_POS_Y+((cnt/IGS_NUM_ITEMS_HEIGHT)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_Y), 
					IMAGE_IGS_ITEMBOX_LOGO_SIZE, IMAGE_IGS_ITEMBOX_LOGO_SIZE);
	}


#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	// ������ ������ ������
	RenderImage(IMAGE_IGS_STORAGE_PAGE, m_Pos.x+IMAGE_IGS_STORAGE_PAGE_POS_X, m_Pos.y+IMAGE_IGS_STORAGE_PAGE_POS_Y, 
					IMGAE_IGS_STORAGE_PAGE_WIDTH, IMGAE_IGS_STORAGE_PAGE_HEIGHT);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

}

void CNewUIInGameShop::RenderTexts()	
{
	unicode::t_char szText[256] = {0,};
	unicode::t_char szValue[256] = {0,};

	g_pRenderText->SetBgColor(0, 0, 0, 0);

	// ��������(ĳ���� �̸�)
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetFont(g_hFontBold);
	sprintf(szText, Hero->ID);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CHAR_NAME_POS_X, m_Pos.y+TEXT_IGS_CHAR_NAME_POS_Y, 
								szText, TEXT_IGS_CHAR_NAME_WIDTH, 0, RT3_SORT_CENTER);

	g_pRenderText->SetFont(g_hFont);

	// Display Item ����
	for(int i=0 ; i<g_InGameShopSystem->GetSizePackageAsDisplayPackage() ; i++)
	{
		CShopPackage* pPackage = g_InGameShopSystem->GetDisplayPackage(i);
		// Package �̸�
		g_pRenderText->SetTextColor(255, 255, 255, 255);
		g_pRenderText->RenderText(m_Pos.x+IGS_PACKAGE_NAME_POS_X+((i%IGS_NUM_ITEMS_WIDTH)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_X), 
									m_Pos.y+IGS_PACKAGE_NAME_POS_Y+((i/IGS_NUM_ITEMS_HEIGHT)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_Y),
									pPackage->PackageProductName, IGS_PACKAGE_NAME_WIDTH, 0, RT3_SORT_CENTER);
		// Package ����
		ConvertGold(pPackage->Price, szValue);
		sprintf(szText, "%s %s", szValue, pPackage->PricUnitName);
		g_pRenderText->SetTextColor(255, 238, 161, 255);
		g_pRenderText->RenderText(m_Pos.x+IGS_PACKAGE_NAME_POS_X+((i%IGS_NUM_ITEMS_WIDTH)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_X), 
									m_Pos.y+IGS_PACKAGE_PRICE_POS_Y+53+((i/IGS_NUM_ITEMS_HEIGHT)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_Y),
									szText, IGS_PACKAGE_NAME_WIDTH, 0, RT3_SORT_CENTER);
	}

	g_pRenderText->SetTextColor(255, 238, 161, 255);

#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	// ĳ�� ���� CreditCard
	ConvertGold(g_InGameShopSystem->GetCashCreditCard(), szValue);
	sprintf( szText, GlobalText[2883], "");
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_CASH_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X+50, m_Pos.y+TEXT_IGS_CASH_POS_Y, szValue, TEXT_IGS_CASH_WIDTH-56, 0, RT3_SORT_RIGHT);
	
	// ĳ�� ���� Prepaid 
	ConvertGold(g_InGameShopSystem->GetCashPrepaid(), szValue);
	sprintf( szText, GlobalText[3145], "");
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_MILEAGE_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X+50, m_Pos.y+TEXT_IGS_MILEAGE_POS_Y, szValue, TEXT_IGS_CASH_WIDTH-56, 0, RT3_SORT_RIGHT);
	
	// ���ϸ��� ���� (�������Ʈ)
	ConvertGold(g_InGameShopSystem->GetTotalMileage(), szValue, 1);
	sprintf( szText, GlobalText[2884], "");
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_POINT_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X+50, m_Pos.y+TEXT_IGS_POINT_POS_Y, szValue, TEXT_IGS_CASH_WIDTH-56, 0, RT3_SORT_RIGHT);
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	
	// ĳ�� ����
	ConvertGold(g_InGameShopSystem->GetTotalCash(), szValue);
	sprintf( szText, GlobalText[2883], szValue);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_CASH_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);
	
	// ���ϸ��� ���� (�������Ʈ)
	ConvertGold(g_InGameShopSystem->GetTotalMileage(), szValue);
	sprintf( szText, GlobalText[2884], szValue);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_MILEAGE_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);

	/* ������
	// ����Ʈ ����
	ConvertGold(g_InGameShopSystem->GetTotalPoint(), szValue);
	sprintf( szText, GlobalText[2885], szValue);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_CASH_POS_X, m_Pos.y+TEXT_IGS_POINT_POS_Y, szText, TEXT_IGS_CASH_WIDTH, 0, RT3_SORT_LEFT);
	*/
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetFont(g_hFontBold);
	
	// ������ ����
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_NAME_POS_X, m_Pos.y+TEXT_IGS_STORAGE_NAME_POS_Y,
								GlobalText[2951], TEXT_IGS_STORAGE_NAME_WIDTH, 0, RT3_SORT_CENTER);			// "�����۸�"

	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_TIME_POS_X, m_Pos.y+TEXT_IGS_STORAGE_NAME_POS_Y,		// "�Ⱓ"
								GlobalText[2952], TEXT_IGS_STORAGE_TIME_WIDTH, 0, RT3_SORT_CENTER);


#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	// Page Info
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_PAGE_POS_X+23, m_Pos.y+TEXT_IGS_PAGE_POS_Y, 
								"/", 10, 0, RT3_SORT_CENTER);

	sprintf( szText, "%d", g_InGameShopSystem->GetSelectPage());
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_PAGE_POS_X+5, m_Pos.y+TEXT_IGS_PAGE_POS_Y, 
								szText, 15, 0, RT3_SORT_RIGHT);

	sprintf( szText, "%d", g_InGameShopSystem->GetTotalPages());
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_PAGE_POS_X+36, m_Pos.y+TEXT_IGS_PAGE_POS_Y, 
								szText, 15, 0, RT3_SORT_LEFT);

	// Storage Page Info
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_PAGE_INFO_POS_X+35, m_Pos.y+TEXT_IGS_STORAGE_PAGE_INFO_POS_Y, 
								"/", 10, 0, RT3_SORT_CENTER);
#ifdef KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE
	sprintf( szText, "%d", m_iStorageCurrentPage);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_PAGE_INFO_POS_X+12, m_Pos.y+TEXT_IGS_STORAGE_PAGE_INFO_POS_Y, 
		szText, 20, 0, RT3_SORT_RIGHT);
	sprintf( szText, "%d", m_iStorageTotalPage);
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_PAGE_INFO_POS_X+48, m_Pos.y+TEXT_IGS_STORAGE_PAGE_INFO_POS_Y, 
			szText, 20, 0, RT3_SORT_LEFT);
#else // KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE
	if( m_iStorageTotalItemCnt > 0 )
	{
		sprintf( szText, "%d", m_iStorageCurrentPage);
		g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_PAGE_INFO_POS_X+12, m_Pos.y+TEXT_IGS_STORAGE_PAGE_INFO_POS_Y, 
			szText, 20, 0, RT3_SORT_RIGHT);
		sprintf( szText, "%d", m_iStorageTotalPage);
		g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_STORAGE_PAGE_INFO_POS_X+48, m_Pos.y+TEXT_IGS_STORAGE_PAGE_INFO_POS_Y, 
			szText, 20, 0, RT3_SORT_LEFT);
	}
#endif // KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	// Page Info
	sprintf( szText, "%d / %d", g_InGameShopSystem->GetSelectPage(), g_InGameShopSystem->GetTotalPages());
	g_pRenderText->RenderText(m_Pos.x+TEXT_IGS_PAGE_POS_X, m_Pos.y+TEXT_IGS_PAGE_POS_Y, 
								szText, TEXT_IGS_PAGE_WIDTH, 0, RT3_SORT_CENTER);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

#ifdef FOR_WORK		// �系�۾��� ��ũ��Ʈ �������� ����
	g_pRenderText->SetTextColor(210, 180, 230, 255);
	g_pRenderText->SetFont(g_hFont);

	// Script Version Info
	CListVersionInfo ScriptVer; 
	ScriptVer = g_InGameShopSystem->GetCurrentScriptVer();
	sprintf( szText, "Script Ver. %d.%d.%d", ScriptVer.Zone, ScriptVer.year, ScriptVer.yearId);
	g_pRenderText->RenderText(m_Pos.x+12, m_Pos.y+396, 
								szText, 150, 0, RT3_SORT_LEFT);

	ScriptVer = g_InGameShopSystem->GetCurrentBannerVer();
	sprintf( szText, "Banner Ver. %d.%d.%d", ScriptVer.Zone, ScriptVer.year, ScriptVer.yearId);
	g_pRenderText->RenderText(m_Pos.x+12, m_Pos.y+408, 
								szText, 150, 0, RT3_SORT_LEFT);
#endif // FOR_WORK
}

void CNewUIInGameShop::RenderButtons()
{
	m_ZoneButton.Render();			// ���� ī�װ�(Zone) ��ư
	m_CategoryButton.Render();		// ���� ī�װ�(Category) ��ư
 	m_ListBoxTabButton.Render();	// List Box Tab ��ư

	// �󼼺��� ��ư
	for(int i=0 ; i<g_InGameShopSystem->GetSizePackageAsDisplayPackage() ; i++)
	{
		m_ViewDetailButton[i].Render();	
	}

	m_CashGiftButton.Render();		// ĳ�� �����ϱ� ��ư
	m_CashChargeButton.Render();		// ĳ�� �����ϱ� ��ư
	m_CashRefreshButton.Render();	// ĳ�� Refresh ��ư
	m_UseButton.Render();			// ����ϱ� ��ư
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT			// #ifndef
	m_DeleteButton.Render();		// ������ ������ ����� ��ư
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_PrevButton.Render();
	m_NextButton.Render();
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_StoragePrevButton.Render();
	m_StorageNextButton.Render();
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_CloseButton.Render();


}

void CNewUIInGameShop::RenderListBox()
{	
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_StorageItemListBox.Render();
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	if(m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].GetLineNum() != 0)
		m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].Render();
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

#ifdef PBG_ADD_ITEMRESIZE
bool CNewUIInGameShop::IsInGameShopRect(float _x,float _y)
{
	if(!g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP))
		return false;

	// �ΰ��Ӽ� ������ �����۸��� �����ϱ� ����
	// �ܺ� ���������� ��Ű�κ� ������ ������ ���ϱ� ����
	RECT _TempRT;

	_TempRT.top = 0;
	_TempRT.bottom = IMAGE_IGS_BACK_HEIGHT;
	_TempRT.left = 0;
	_TempRT.right = IMAGE_IGS_BACK_WIDTH;

	if(_x >= _TempRT.left && _x < _TempRT.right && _y < _TempRT.bottom && _y >= _TempRT.top)
		return true;
	else
		return false;

	return false;
}
// ���� ��ġ������ �κ��� �Ͱ� �����ϰ� �� �����Ѵ�
// ������ �߰��� �κ��� �µ��� �����ϰ� ���κ��� ������ ��ġ�ϵ��� �Ѵ�
// �ΰ��Ӽ����� ����ϴ� ����,�޽����ڽ����� ������ ���� ����
void CNewUIInGameShop::SetConvertInvenCoord(WORD _ItemType, float _Width, float _Height)
{
	ITEM_ATTRIBUTE* pItemAttr = &ItemAttribute[_ItemType];
	// �������� �κ������� ũ�� ����
	float _TempWidth = pItemAttr->Width*20.0f;
	float _TempHeight = pItemAttr->Height*20.0f;
	// �����۹ڽ��� �߽ɿ��� �κ��� ���� ũ���� ��ġ�� ���
	float _fCoodX=0,_fCoodY=0;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	float _fWidth=0,_fHeight=0;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	// ����ó�� ��ġ ����ÿ� �Ʒ��� �߰��ϼ���
	// ������ �߰��� zzzInventory.cpp->RenderItem3D()���� ������ ��ġ �����ϴ°�����
	// �����ؼ� �����ϴٸ� �װ����� ������ �ϼ���
	if(_ItemType == ITEM_WING+36)
	{
		_fCoodY = 5.0f;							//��ǳ�ǳ���
	}
///////////////////////////////////////////////////////////////////////�⺻ ����(����)
	else if(pItemAttr->Height >= 4)
	{
		// �κ����� ���� 4ĭ�̻� ������ ���۹ڽ��� �Ѿ�� �ڽ��� ���� ����
		_fCoodY = -10.0f;
	}

	// �ΰ��Ӽ��� ������ �׸��� �ڽ��� ���� �߰��� ��ġ�ϵ��� ����
	m_fRePos.x = (_Width/2) - (_TempWidth/2) + _fCoodX;
	m_fRePos.y = (_Height/2) - (_TempHeight/2) + _fCoodY;
	m_fReSize.x = _TempWidth;
	m_fReSize.y = _TempHeight;
}
void CNewUIInGameShop::SetRateScale(int _ItemType)
{
	// �κ��� ���� ������ ��� ��
	const float _fRate_Value = 0.703f;
	ITEM_ATTRIBUTE* pItemAttr = &ItemAttribute[_ItemType];

	// ����ó�� ������ ����ÿ� �Ʒ��� �߰��ϼ���(�κ������� ����� ����ؼ� ������)
	// ������ �߰��� zzzInventory.cpp->RenderObjectScreen()���� ������ ���� �����ϴ°�����
	// �����ؼ� �����ϴٸ� �װ����� ������ �ϼ��� �κ������� ������ �ٸ��ٸ� ���⼭ ����
	if(_ItemType == ITEM_WING+36)
	{
		m_fRate_Scale = _fRate_Value*0.7f;			//��ǳ�� ����
	}
	else if(_ItemType == ITEM_STAFF+10)
	{
		m_fRate_Scale = _fRate_Value*0.7f;
	}
#ifdef PBG_MOD_SECRETITEM
	else if(_ItemType >= ITEM_HELPER+117 && _ItemType <= ITEM_HELPER+120)
	{
		m_fRate_Scale = _fRate_Value*1.6f;
	}
#endif //PBG_MOD_SECRETITEM
///////////////////////////////////////////////////////////////////////�⺻ ����(����)
	else if(pItemAttr->Height >= 4)
	{
		// �κ����� ���� 4ĭ�̻� ������ ���۹ڽ��� �Ѿ�� ���� ����
		// �κ� 4*20=80 > �ڽ����� 58 ===> 30% �ٿ��� 56
		m_fRate_Scale = _fRate_Value*0.7f;
	}
	else
	{
		// �κ����� �����ִ� ������� ���� ������
		m_fRate_Scale = _fRate_Value;
	}
}
#endif //PBG_ADD_ITEMRESIZE

//--------------------------------------------
// Display�Ǵ� Item�� Render
void CNewUIInGameShop::RenderDisplayItems()
{		
	EndBitmap();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glViewport2(0,0,WindowWidth,WindowHeight);
	gluPerspective2(1.f, (float)(WindowWidth)/(float)(WindowHeight), RENDER_ITEMVIEW_NEAR, RENDER_ITEMVIEW_FAR);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	GetOpenGLMatrix(CameraMatrix);
	EnableDepthTest();
	EnableDepthMask();
	
	glClear(GL_DEPTH_BUFFER_BIT);

	//-------------------------------------------
	// ������ Items Render

	for(int i=0 ; i<g_InGameShopSystem->GetSizePackageAsDisplayPackage() ; i++ )
	{
		// �⺻ ��ǥ+ (�ڽ�+����)*ù��°(0)++
 		int iPosX = IGS_ITEMRENDER_POS_X_STANDAD+(IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_X*(i%IGS_NUM_ITEMS_WIDTH));
  		int iPosY = IGS_ITEMRENDER_POS_Y_STANDAD+(IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_Y*(i/IGS_NUM_ITEMS_HEIGHT));

		// Render �׷��� ������ ���� ������ ��ġ �������� �ʿ��Ѱ��� ����ó��SetItemRePosition()�Ѵ�
		//RenderItem3D(iPosX, iPosY, IGS_ITEMRENDER_POS_WIDTH, IGS_ITEMRENDER_POS_HEIGHT, wItemCode[i], 0, 0, 0, true);
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		CShopPackage* pPackage = g_InGameShopSystem->GetDisplayPackage(i);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

		RenderItem3D(iPosX, iPosY, IGS_ITEMRENDER_POS_WIDTH, IGS_ITEMRENDER_POS_HEIGHT, g_InGameShopSystem->GetPackageItemCode(i), 0, 0, 0, true);
	}

	//-------------------------------------------
	
	UpdateMousePositionn();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	BeginBitmap();
}
	
bool CNewUIInGameShop::BtnProcess()
{	
	if( g_InGameShopSystem->IsRequestEventPackge() == true )
	{
		// ���� ī�װ�(Zone) ��ư
		if( m_ZoneButton.UpdateMouseEvent() != -1 )
		{
			g_InGameShopSystem->SelectZone(m_ZoneButton.GetCurButtonIndex());
			InitCategoryBtn();
			g_InGameShopSystem->SelectCategory(m_CategoryButton.GetCurButtonIndex());
			return true;
		}
		
		// ���� ī�װ�(Category) ��ư
		if( m_CategoryButton.UpdateMouseEvent() != -1 )
		{
			g_InGameShopSystem->SelectCategory(m_CategoryButton.GetCurButtonIndex());
			return true;
		}
	}
	
	// ListBox Tab ��ư
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	if( m_ListBoxTabButton.UpdateMouseEvent() != -1 )
	{
		
		char szCode = GetCurrentStorageCode();
		m_iSelectedStorageItemIndex = 0;
		m_bRequestCurrentPage = true;
		SendRequestIGS_ItemStorageList(1, &szCode);		// ������ ����Ʈ ��û
		return true;
	}
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	if( m_ListBoxTabButton.UpdateMouseEvent() != -1 )
		return true;
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// �󼼺��� ��ư
	for(int i=0 ; i<g_InGameShopSystem->GetSizePackageAsDisplayPackage() ; i++)
	{
		if( m_ViewDetailButton[i].UpdateMouseEvent() )
		{
			CShopPackage* pPackage = g_InGameShopSystem->GetDisplayPackage(i);
			
			// ����/��Ű�� ������
			if( pPackage->PriceCount == 1 )
			{
				// ����/��Ű�� ������ ����â ���
				CMsgBoxIGSBuyPackageItem* pMsgBox = NULL;
				CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxBuyPackageItemLayout), &pMsgBox);
				pMsgBox->Initialize(pPackage);
			}
			else if(pPackage->PriceCount > 1)
			{
				// ���þ����� ����â ���
				CMsgBoxIGSBuySelectItem* pMsgBox = NULL;
				CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSBuySelectItemLayout), &pMsgBox);
				pMsgBox->Initialize(pPackage);
			}

			return true;
		}
	}

	// ĳ�� �����ϱ� ��ư
	if( m_CashGiftButton.UpdateMouseEvent() == true )
	{
		// ����� '�������� �ʴ±��' MessageBox ����
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
		pMsgBox->Initialize(GlobalText[2937], GlobalText[2938]);
		return true;
	}

	// ĳ�� �����ϱ� ��ư
	if( m_CashChargeButton.UpdateMouseEvent() == true )
	{
		// ����� '�������� �ʴ±��' MessageBox ����
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
		pMsgBox->Initialize(GlobalText[2937], GlobalText[2938]);
		return true;
	}

	// ĳ�� Refresh ��ư
	if( m_CashRefreshButton.UpdateMouseEvent() == true )
	{
		SendRequestIGS_CashPointInfo();

		return true;
	}

	// ����ϱ� ��ư
	if( m_UseButton.UpdateMouseEvent() == true )
	{
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		if( m_StorageItemListBox.GetLineNum() <= 0 )
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		if( m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].GetLineNum() <= 0 )
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "����", "����� �� �ִ� �������� �����ϴ�."
			pMsgBox->Initialize(GlobalText[3028], GlobalText[3033]);
			return true;
		}

		int iStorageIndex = m_ListBoxTabButton.GetCurButtonIndex();

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		IGS_StorageItem* pSelectItem = m_StorageItemListBox.GetSelectedText();
		
		if( iStorageIndex == IGS_SAFEKEEPING_LISTBOX )					// ������
		{
			CMsgBoxIGSStorageItemInfo* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSStorageItemInfoLayout), &pMsgBox);
			pMsgBox->Initialize(pSelectItem->m_iStorageSeq, pSelectItem->m_iStorageItemSeq, pSelectItem->m_wItemCode, pSelectItem->m_szType, 
				pSelectItem->m_szName, pSelectItem->m_szNum, pSelectItem->m_szPeriod);
		}
		else if( iStorageIndex == IGS_PRESENTBOX_LISTBOX )				// ���� ������
		{
			CMsgBoxIGSGiftStorageItemInfo* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSGiftStorageItemInfoLayout), &pMsgBox);
			pMsgBox->Initialize(pSelectItem->m_iStorageSeq, pSelectItem->m_iStorageItemSeq, pSelectItem->m_wItemCode, 
				pSelectItem->m_szType, pSelectItem->m_szSendUserName, pSelectItem->m_szMessage, 
				pSelectItem->m_szName, pSelectItem->m_szNum, pSelectItem->m_szPeriod);
		}
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		IGS_StorageItem* pSelectItem = m_InGameShopListBox[iStorageIndex].GetSelectedText();

		if( iStorageIndex == CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX )					// ������
		{
			CMsgBoxIGSStorageItemInfo* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSStorageItemInfoLayout), &pMsgBox);
			pMsgBox->Initialize(pSelectItem->m_iStorageSeq, pSelectItem->m_iStorageItemSeq, pSelectItem->m_wItemCode, pSelectItem->m_szType, 
				pSelectItem->m_szName, pSelectItem->m_szNum, pSelectItem->m_szPeriod);
		}
		else if( iStorageIndex == CInGameShopSystem::IGS_PRESENTBOX_LISTBOX )				// ���� ������
		{
			CMsgBoxIGSGiftStorageItemInfo* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSGiftStorageItemInfoLayout), &pMsgBox);
			pMsgBox->Initialize(pSelectItem->m_iStorageSeq, pSelectItem->m_iStorageItemSeq, pSelectItem->m_wItemCode, 
				pSelectItem->m_szType, pSelectItem->m_szSendUserName, pSelectItem->m_szMessage, 
				pSelectItem->m_szName, pSelectItem->m_szNum, pSelectItem->m_szPeriod);
		}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

		return true;
	}

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	// ������ ������ ����� ��ư
	if( m_DeleteButton.UpdateMouseEvent() == true )
	{
		if( m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].GetLineNum() <= 0 )
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "����", "������ �� �ִ� �������� �����ϴ�."
			pMsgBox->Initialize(GlobalText[3028], GlobalText[3034]);
			return true;
		}

		IGS_StorageItem* pSelectItem = m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].GetSelectedText();
		CMsgBoxIGSDeleteItemConfirm* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSDeleteItemConfirmLayout), &pMsgBox);
		pMsgBox->Initialize(pSelectItem->m_iStorageSeq, pSelectItem->m_iStorageItemSeq, pSelectItem->m_szType);

		return true;
	}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// Prev Button
	if(m_PrevButton.UpdateMouseEvent())
	{
		g_InGameShopSystem->PrePage();
	 	return true;
	}
	
	// Next Button
	if(m_NextButton.UpdateMouseEvent())
	{
		g_InGameShopSystem->NextPage();
		return true;
 	}

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	// Storage Prev Button
	if(m_StoragePrevButton.UpdateMouseEvent())
	{
		StoragePrevPage();
		return true;
	}
	
	// Next Button
	if(m_StorageNextButton.UpdateMouseEvent())
	{
		StorageNextPage();
		return true;
 	}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	if(m_CloseButton.UpdateMouseEvent() == true)
	{	
		//�ݱ� ��ư�� ���ȴٸ�
		if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == true)
		{	
			SendRequestIGS_CashShopOpen(1);		// �� Close��û
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_INGAMESHOP);

			return true;
		}
		return false;
	}

	return false;
}

void CNewUIInGameShop::SetBtnInfo()
{
	//�ݱ� ��ư
	m_CloseButton.ChangeButtonImgState(true, IMAGE_IGS_EXIT_BTN, false);
	m_CloseButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_EXIT_BTN_POS_X, m_Pos.y+IMAGE_IGS_EXIT_BTN_POS_Y, 
									IMAGE_IGS_EXIT_BTN_WIDTH, IMAGE_IGS_EXIT_BTN_HEIGHT);
	m_CloseButton.ChangeToolTipText(GlobalText[1002], true);

	// ListBox Tab ��ư
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_ListBoxTabButton.CreateRadioGroup(IGS_TOTAL_LISTBOX, IMAGE_IGS_LEFT_TAB);
	m_ListBoxTabButton.ChangeRadioButtonInfo(true, m_Pos.x+IMAGE_IGS_TAB_BTN_POS_X, m_Pos.y+IMAGE_IGS_TAB_BTN_POS_Y
		,IMAGE_IGS_TAB_BTN_WIDTH, IMAGE_IGS_TAB_BTN_HEIGHT, IMAGE_IGS_TAB_BTN_DISTANCE);
	m_ListBoxTabButton.ChangeButtonState( SEASON3B::BUTTON_STATE_DOWN, 0 );
	m_ListBoxTabButton.ChangeButtonState( IGS_SAFEKEEPING_LISTBOX, BITMAP_UNKNOWN, SEASON3B::BUTTON_STATE_UP, 0 );
	m_ListBoxTabButton.ChangeButtonState( IGS_PRESENTBOX_LISTBOX, BITMAP_UNKNOWN, SEASON3B::BUTTON_STATE_UP, 0 );
	m_ListBoxTabButton.ChangeButtonState( IGS_PRESENTBOX_LISTBOX, IMAGE_IGS_RIGHT_TAB, SEASON3B::BUTTON_STATE_DOWN, 0 );
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_ListBoxTabButton.CreateRadioGroup(CInGameShopSystem::IGS_TOTAL_LISTBOX, IMAGE_IGS_LEFT_TAB);
	m_ListBoxTabButton.ChangeRadioButtonInfo(true, m_Pos.x+IMAGE_IGS_TAB_BTN_POS_X, m_Pos.y+IMAGE_IGS_TAB_BTN_POS_Y
											,IMAGE_IGS_TAB_BTN_WIDTH, IMAGE_IGS_TAB_BTN_HEIGHT, IMAGE_IGS_TAB_BTN_DISTANCE);
	m_ListBoxTabButton.ChangeButtonState( SEASON3B::BUTTON_STATE_DOWN, 0 );
	m_ListBoxTabButton.ChangeButtonState( CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX, BITMAP_UNKNOWN, SEASON3B::BUTTON_STATE_UP, 0 );
	m_ListBoxTabButton.ChangeButtonState( CInGameShopSystem::IGS_PRESENTBOX_LISTBOX, BITMAP_UNKNOWN, SEASON3B::BUTTON_STATE_UP, 0 );
	m_ListBoxTabButton.ChangeButtonState( CInGameShopSystem::IGS_PRESENTBOX_LISTBOX, IMAGE_IGS_RIGHT_TAB, SEASON3B::BUTTON_STATE_DOWN, 0 );
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	unicode::t_string strText;
	std::list<unicode::t_string> TextList;
	strText = GlobalText[2888];		// "������"
	TextList.push_back(strText);
	strText = GlobalText[2889];		// "������"
	TextList.push_back(strText);
	
	m_ListBoxTabButton.ChangeRadioText(TextList);
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_ListBoxTabButton.ChangeFrame(IGS_SAFEKEEPING_LISTBOX);
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_ListBoxTabButton.ChangeFrame(CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// �󼼺��� ��ư
	for(int i=0 ; i<INGAMESHOP_DISPLAY_ITEMLIST_SIZE ; i++)
	{
		m_ViewDetailButton[i].ChangeButtonImgState(true, IMAGE_IGS_VIEWDETAIL_BTN, true, false, true);
		m_ViewDetailButton[i].ChangeButtonInfo(IMAGE_IGS_VIEWDETAIL_BTN_POS_X+((i%IGS_NUM_ITEMS_WIDTH)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_X),
												IMAGE_IGS_VIEWDETAIL_BTN_POS_Y+((i/IGS_NUM_ITEMS_HEIGHT)*IMAGE_IGS_VIEWDETAIL_BTN_DISTANCE_Y),
												IMAGE_IGS_VIEWDETAIL_BTN_WIDTH, IMAGE_IGS_VIEWDETAIL_BTN_HEIGHT);
		m_ViewDetailButton[i].MoveTextPos(0, -1);
		m_ViewDetailButton[i].ChangeText(GlobalText[2886]);
	}

	// ĳ�� �����ϱ� ��ư
	m_CashGiftButton.ChangeButtonImgState(true, IMAGE_IGS_ITEMGIFT_BTN, true);
	m_CashGiftButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_ITEMGIFT_BTN_POS_X, m_Pos.y+IMAGE_IGS_ICON_BTN_POS_Y, 
										IMAGE_IGS_ICON_BTN_WIDTH, IMAGE_IGS_ICON_BTN_HEIGHT);
	m_CashGiftButton.ChangeToolTipText(GlobalText[2939]);

	// ĳ�� �����ϱ� ��ư
	m_CashChargeButton.ChangeButtonImgState(true, IMAGE_IGS_CASHGIFT_BTN, true);
	m_CashChargeButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_CASHGIFT_BTN_POS_X, m_Pos.y+IMAGE_IGS_ICON_BTN_POS_Y, 
										IMAGE_IGS_ICON_BTN_WIDTH, IMAGE_IGS_ICON_BTN_HEIGHT);
	m_CashChargeButton.ChangeToolTipText(GlobalText[2940]);

	// ĳ�� Refresh ��ư
	m_CashRefreshButton.ChangeButtonImgState(true, IMAGE_IGS_REFRESH_BTN, true);
	m_CashRefreshButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_REFRESH_BTN_POS_X, m_Pos.y+IMAGE_IGS_ICON_BTN_POS_Y, 
										IMAGE_IGS_ICON_BTN_WIDTH, IMAGE_IGS_ICON_BTN_HEIGHT);
	m_CashRefreshButton.ChangeToolTipText(GlobalText[2941]);

	// ����ϱ� ��ư
	m_UseButton.ChangeButtonImgState(true, IMAGE_IGS_VIEWDETAIL_BTN, true, false, true);
	m_UseButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_USE_BTN_POS_X, m_Pos.y+IMAGE_IGS_USE_BTN_POS_Y, 
									IMAGE_IGS_VIEWDETAIL_BTN_WIDTH, IMAGE_IGS_VIEWDETAIL_BTN_HEIGHT);
	m_UseButton.MoveTextPos(0, -1);
	m_UseButton.ChangeText(GlobalText[2887]);

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	// ������ ������ �����ϱ� ��ư
	m_DeleteButton.ChangeButtonImgState(true, IMAGE_IGS_DELETE_BTN, true);
	m_DeleteButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_DELETE_BTN_POS_X, m_Pos.y+IMAGE_IGS_DELETE_BTN_POS_Y, 
									IMAGE_IGS_ICON_BTN_WIDTH, IMAGE_IGS_ICON_BTN_HEIGHT);
	m_DeleteButton.ChangeToolTipText(GlobalText[2942]);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// prev ��ư
	m_PrevButton.ChangeButtonImgState(true, IMAGE_IGS_PAGE_LEFT, true);
	m_PrevButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_PAGE_LEFT_POS_X, m_Pos.y+IMAGE_IGS_PAGE_BUTTON_POS_Y, 
									IMAGE_IGS_PAGE_BTN_WIDTH, IMAGE_IGS_PAGE_BTN_HEIGHT);
	
	// next ��ư
	m_NextButton.ChangeButtonImgState(true, IMAGE_IGS_PAGE_RIGHT, true);
	m_NextButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_PAGE_RIGHT_POS_X, m_Pos.y+IMAGE_IGS_PAGE_BUTTON_POS_Y, 
									IMAGE_IGS_PAGE_BTN_WIDTH, IMAGE_IGS_PAGE_BTN_HEIGHT);

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	// Storage Page prev ��ư
	m_StoragePrevButton.ChangeButtonImgState(true, IMAGE_IGS_STORAGE_PAGE_LEFT, true);
	m_StoragePrevButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_STORAGE_PAGE_LEFT_POS_X-12, m_Pos.y+IMAGE_IGS_STORAGE_PAGE_BTN_POS_Y-3, 
										IMGAE_IGS_STORAGE_PAGE_BTN_WIDTH, IMGAE_IGS_STORAGE_PAGE_BTN_HEIGHT);
	
	// Storage Page next ��ư
	m_StorageNextButton.ChangeButtonImgState(true, IMAGE_IGS_STORAGE_PAGE_RIGHT, true);
	m_StorageNextButton.ChangeButtonInfo(m_Pos.x+IMAGE_IGS_STORAGE_PAGE_RIGHT_POS_X+10, m_Pos.y+IMAGE_IGS_STORAGE_PAGE_BTN_POS_Y-3, 
										IMGAE_IGS_STORAGE_PAGE_BTN_WIDTH, IMGAE_IGS_STORAGE_PAGE_BTN_HEIGHT);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

bool CNewUIInGameShop::Update()
{
	if( IsVisible() == false )
		return true;

	return true;
}

bool CNewUIInGameShop::UpdateMouseEvent()
{
	if(IsVisible() == false)
		return true;

	if( BtnProcess() )
		return false;

	if( UpdateBanner() )
		return false;
		
	if(SEASON3B::CheckMouseIn(m_Pos.x, m_Pos.y, IMAGE_IGS_BACK_WIDTH, IMAGE_IGS_BACK_HEIGHT))
	{
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		m_StorageItemListBox.DoAction();
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		m_InGameShopListBox[m_ListBoxTabButton.GetCurButtonIndex()].DoAction();
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

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

		return false;
	}

	return true;
}

bool CNewUIInGameShop::UpdateKeyEvent()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == true)
	{
		//escŰ�� ����Ͽ� ����ϴ� ���
		if(SEASON3B::IsPress(VK_ESCAPE) == true)
		{
			SendRequestIGS_CashShopOpen(1);		// �� Close��û
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_INGAMESHOP);

			return false;
		}
	}
	return true;
}

bool CNewUIInGameShop::IsInGameShopOpen()
{
#ifdef FOR_WORK
	DebugAngel_Write("InGameShopStatue.Txt", "CallStack - CNewUIInGameShop::IsInGameShopOpen()\r\n");
#endif // FOR_WORK
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
	// ĳ���Ͱ� �����̰� �ִ� �����̸� return
	if( Hero->Movement )
		return false;

#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
	// ���������̰ų� �����϶��� ������ ���� ����.
	if( !(Hero->SafeZone) &&				// ���������϶� 
		!(WD_0LORENCIA == World				// �η��þ�
		&& WD_3NORIA == World				// �븮��
		&& WD_2DEVIAS == World				// ����ƽ�
		&& WD_51HOME_6TH_CHAR == World))	// ��������
#else // KJH_MOD_INGAMESHOP_PATCH_091028
	// ���������̰ų� �����϶��� ������ ���� ����.
	if( !(Hero->SafeZone) ||				// ���������϶� 
		!(WD_0LORENCIA == World				// �η��þ�
		|| WD_3NORIA == World				// �븮��
		|| WD_2DEVIAS == World				// ����ƽ�
		|| WD_51HOME_6TH_CHAR == World))	// ��������
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
	{
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
		// "����", "�����̳� �������뿡���� ĳ�û����� �� �� �ֽ��ϴ�."
		pMsgBox->Initialize(GlobalText[3028], GlobalText[3051]);
#ifdef FOR_WORK
		DebugAngel_Write("InGameShopStatue.Txt", " Return - false <%s>\r\n", GlobalText[3051]);
#endif // FOR_WORK

		return false;
	}

	if( g_InGameShopSystem->IsShopOpen() == false)
	{
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
		// "����", "ĳ�û����� ���� �����ϴ�.#������ ������ ���ֽñ� �ٶ��ϴ�."
		pMsgBox->Initialize(GlobalText[3028], GlobalText[3035]);

#ifdef FOR_WORK
		DebugAngel_Write("InGameShopStatue.Txt", " Return - false <%s>\r\n", GlobalText[3035]);
#endif // FOR_WORK
		return false;
	}
	
#ifdef FOR_WORK
	DebugAngel_Write("InGameShopStatue.Txt", " Return - true\r\n");
#endif // FOR_WORK
	return true;
#else // KJH_MOD_INGAMESHOP_PATCH_091028
	if( g_InGameShopSystem->IsShopOpen() == false)
	{
		CMsgBoxIGSCommon* pMsgBox = NULL;
		CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
		// "����", "ĳ�û����� ���� �����ϴ�.#������ ������ ���ֽñ� �ٶ��ϴ�."
		pMsgBox->Initialize(GlobalText[3028], GlobalText[3035]);
		return false;
	}

	if( !Hero->Movement && Hero->SafeZone &&// �������� �ʰ� ���������϶� 
		(WD_0LORENCIA == World				// �η��þ�
		|| WD_3NORIA == World				// �븮��
		|| WD_2DEVIAS == World				// ����ƽ�
		|| WD_51HOME_6TH_CHAR == World))	// ��������
	{
		return true;
	}

	return false;
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
}

bool CNewUIInGameShop::IsInGameShop()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP))
		return true;
	else
		return false;
}

//--------------------------------------------
// InitBanner
void CNewUIInGameShop::InitBanner(unicode::t_char* pszFileName, unicode::t_char* pszBannerURL)
{
	ReleaseBanner();

	if(pszFileName == NULL) 
		return;

	if(pszBannerURL[0] != '#')
	{
		m_bBannerLink = true;
	}

	// ��ʸ� �ٿ�ε� ������ �̹��� ����Ʈ
	if( Bitmaps.Convert_Format(pszFileName) == false)
		return;

	// ��ʴ� LoadBitmap FullPath ���
	if( LoadBitmap(pszFileName, IMAGE_IGS_BANNER, GL_LINEAR, GL_CLAMP, true, true) == true)
	{
		m_bLoadBanner = true;

		strcpy(m_szBannerURL, pszBannerURL);
	}
}

//--------------------------------------------
// RenderBanner
void CNewUIInGameShop::RenderBanner()
{
	if( m_bLoadBanner == false )
		return;

	RenderImage(IMAGE_IGS_BANNER, IMAGE_IGS_BANNER_POS_X, IMAGE_IGS_BANNER_POS_Y, IMAGE_IGS_BANNER_WIDTH, IMAGE_IGS_BANNER_HEIGHT);
}

//--------------------------------------------
// UpdateBanner
bool CNewUIInGameShop::UpdateBanner()
{
	if( m_bLoadBanner == false || m_bBannerLink == false )
		return false;

	if( (SEASON3B::IsPress(VK_LBUTTON))
		&& (SEASON3B::CheckMouseIn(IMAGE_IGS_BANNER_POS_X, IMAGE_IGS_BANNER_POS_Y, IMAGE_IGS_BANNER_WIDTH, IMAGE_IGS_BANNER_HEIGHT)))
	{
		// ����Ʈ ����
		leaf::OpenExplorer(m_szBannerURL);
		return true; 
	}
	return false;
}

//--------------------------------------------
// ReleaseBanner
void CNewUIInGameShop::ReleaseBanner()
{
	if( m_bLoadBanner == false )
		return;

	DeleteBitmap(IMAGE_IGS_BANNER);

	m_bLoadBanner = false;
}

//--------------------------------------------
// OpeningProcess
void CNewUIInGameShop::OpeningProcess()
{
#ifdef FOR_WORK
	DebugAngel_Write("InGameShopStatue.Txt", "CallStack - CNewUIInGameShop::OpeningProcess()\r\n");
#endif // FOR_WORK
	PlayBuffer(SOUND_CLICK01);

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	// ListBox State �ʱ�ȭ
	m_ListBoxTabButton.ChangeFrame(CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	g_InGameShopSystem->Initalize();
	g_InGameShopSystem->SelectZone(0);
	InitZoneBtn();
	g_InGameShopSystem->SelectCategory(0);
	InitCategoryBtn();

	g_InGameShopSystem->SetRequestEventPackge();
} 

//--------------------------------------------
// ClosingProcess
void CNewUIInGameShop::ClosingProcess()
{
	PlayBuffer(SOUND_CLICK01);

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_ListBoxTabButton.ChangeFrame(IGS_SAFEKEEPING_LISTBOX);		// ListBox State �ʱ�ȭ
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	ClearAllStorageItem();
}


//--------------------------------------------
// ���� ī�װ�(Zone)��ư �ʱ�ȭ
void CNewUIInGameShop::InitZoneBtn()
{
	m_ZoneButton.UnRegisterRadioButton();

	if (g_InGameShopSystem->GetSizeZones() == 0)
		return;

	m_ZoneButton.UnRegisterRadioButton();
	m_ZoneButton.CreateRadioGroup(g_InGameShopSystem->GetSizeZones(), IMAGE_IGS_ZONE_BTN);
	m_ZoneButton.ChangeRadioButtonInfo(true, m_Pos.x+IMAGE_IGS_ZONE_BTN_POS_X, m_Pos.y+IMAGE_IGS_ZONE_BTN_POS_Y
										,IMAGE_IGS_ZONE_BTN_WIDTH, IMAGE_IGS_ZONE_BTN_HEIGHT);
	m_ZoneButton.SetFont(g_hFontBold);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	type_listName listZoneName = g_InGameShopSystem->GetZoneName();
	m_ZoneButton.ChangeRadioText(listZoneName);	// Text ����
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	m_ZoneButton.ChangeRadioText(g_InGameShopSystem->GetZoneName());	// Text ����
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	m_ZoneButton.ChangeFrame(0);
}

//--------------------------------------------
// ���� ī�װ�(Category)��ư �ʱ�ȭ
void CNewUIInGameShop::InitCategoryBtn()
{
	m_CategoryButton.UnRegisterRadioButton();

	if( g_InGameShopSystem->GetSizeCategoriesAsSelectedZone() == 0 )
		return;

	m_CategoryButton.UnRegisterRadioButton();
#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	m_CategoryButton.CreateRadioGroup(g_InGameShopSystem->GetSizeCategoriesAsSelectedZone(), IMAGE_IGS_CATEGORY_BTN, true, true);
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	m_CategoryButton.CreateRadioGroup(g_InGameShopSystem->GetSizeCategoriesAsSelectedZone(), IMAGE_IGS_CATEGORY_BTN, true);
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	m_CategoryButton.ChangeRadioButtonInfo(false, m_Pos.x+IMAGE_IGS_CATEGORY_BTN_POS_X, m_Pos.y+IMAGE_IGS_CATEGORY_BTN_POS_Y
											,IMAGE_IGS_CATEGORY_BTN_WIDTH, IMAGE_IGS_CATEGORY_BTN_HEIGHT, IMAGE_IGS_CATEGORY_BTN_DISTANCE);
	m_CategoryButton.ChangeButtonState( SEASON3B::BUTTON_STATE_DOWN, 2 );
	m_CategoryButton.SetFont(g_hFontBold);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	type_listName listCategoryName = g_InGameShopSystem->GetCategoryName(); 
	m_CategoryButton.ChangeRadioText(listCategoryName);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	m_CategoryButton.ChangeRadioText(g_InGameShopSystem->GetCategoryName());
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	m_CategoryButton.ChangeFrame(0);
}

//--------------------------------------------
// ������ Data Add
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
void CNewUIInGameShop::AddStorageItem(int iStorageSeq, int iStorageItemSeq, int iStorageGroupCode, int iProductSeq, int iPriceSeq, int iCashPoint,
									   unicode::t_char chItemType, unicode::t_char* pszUserName /* = NULL */, unicode::t_char* pszMessage /* = NULL */)
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
void CNewUIInGameShop::AddStorageItem(int iListBoxIndex, int iStorageSeq, int iStorageItemSeq, int iStorageGroupCode, int iProductSeq, int iPriceSeq, 
									   int iCashPoint, unicode::t_char chItemType, unicode::t_char* pszUserName /* = NULL */, unicode::t_char* pszMessage /* = NULL */)
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
{
	int iValue = -1;
	unicode::t_char szText[MAX_TEXT_LENGTH] = {'\0', };
	IGS_StorageItem Item;

	Item.m_bIsSelected = FALSE;
	Item.m_iStorageSeq = iStorageSeq;
	Item.m_iStorageItemSeq = iStorageItemSeq;
	Item.m_iStorageGroupCode = iStorageGroupCode;
	Item.m_iProductSeq = iProductSeq;
	Item.m_iPriceSeq = iPriceSeq;
	Item.m_iCashPoint = iCashPoint;
	Item.m_iNum = 1;
	Item.m_szType = chItemType;
	Item.m_wItemCode = -1;

	// ������ ���� ID
	if( pszUserName == NULL )
	{
		Item.m_szSendUserName[0] = '\0';
	}
	else 
	{
		strcpy(Item.m_szSendUserName, pszUserName);
	}

	// ���� �޼���
	if( pszMessage == NULL )
	{
		Item.m_szMessage[0] = '\0';
	}
	else
	{
		strcpy(Item.m_szMessage, pszMessage);
	}
	
	if( chItemType == 'C' || chItemType == 'c')		// ĳ���϶�
	{
		unicode::t_char szValue[MAX_TEXT_LENGTH] = {'\0', };
		ConvertGold(iCashPoint, szValue);
		// Name		"���� ĳ�� %sĳ��"
		sprintf(Item.m_szName, GlobalText[3050], szValue);
		
		// Num
		sprintf(Item.m_szNum, GlobalText[3043], szValue);	// "%s ĳ��
		Item.m_iNum = iCashPoint;
		
		// Period
		sprintf(Item.m_szPeriod, "-");
	}
	else if(chItemType == 'P' || chItemType == 'p')		// ��ǰ�϶�
	{
		if( iPriceSeq > 0)
		{
			// Name
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
			if( g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMNAME, iValue, Item.m_szName) == false)
			{
				//sprintf(Item.m_szName, "�˼����� ������");
				sprintf(Item.m_szName, "aaa");
				// �ش��ϴ� Product�� ����.
			}
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
			if( g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMNAME, iValue, Item.m_szName) == false)
				return;		// �ش��ϴ� Product�� ����.
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
#else // KJH_MOD_INGAMESHOP_PATCH_091028
			g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMNAME, iValue, Item.m_szName);
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
			
			g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_NUM, iValue, szText);
			if( iValue > 0 )
			{
				sprintf(Item.m_szNum, "%d %s", iValue, szText);
				Item.m_iNum = iValue;
			}
			else
			{
				sprintf(Item.m_szNum, "-");
			}
			
			// Period
			g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_USE_LIMIT_PERIOD, iValue, szText);
			if( iValue > 0 )
			{
				sprintf(Item.m_szPeriod, "%d %s", iValue, szText);
			}
			else
			{
				sprintf(Item.m_szPeriod, "-");
			}
			
			g_InGameShopSystem->GetProductInfoFromPriceSeq(iProductSeq, iPriceSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMCODE, iValue, szText);
			Item.m_wItemCode = iValue;	
		}
		else
		{
			// Name
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
			if( g_InGameShopSystem->GetProductInfoFromProductSeq(iProductSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMNAME, iValue, Item.m_szName) == false	)
				return;		// �ش��ϴ� Product�� ����.
#else // KJH_MOD_INGAMESHOP_PATCH_091028
			g_InGameShopSystem->GetProductInfoFromProductSeq(iProductSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMNAME, iValue, Item.m_szName);	
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
			
			// Num
			g_InGameShopSystem->GetProductInfoFromProductSeq(iProductSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_NUM, iValue, szText);
			if( iValue > 0 )
			{
				sprintf(Item.m_szNum, "%d %s", iValue, szText);
				Item.m_iNum = iValue;
			}
			else
			{
				sprintf(Item.m_szNum, "-");
			}
			
			// Period
			g_InGameShopSystem->GetProductInfoFromProductSeq(iProductSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_USE_LIMIT_PERIOD, iValue, szText);
			if( iValue > 0 )
			{
				sprintf(Item.m_szPeriod, "%d %s", iValue, szText);
			}
			else
			{
				sprintf(Item.m_szPeriod, "-");
			}
			
			g_InGameShopSystem->GetProductInfoFromProductSeq(iProductSeq, CInGameShopSystem::IGS_PRODUCT_ATT_TYPE_ITEMCODE, iValue, szText);
			Item.m_wItemCode = iValue;
		}
	}
	else 
	{
		return;
	}

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_iStorageCurrentPageReceiveItemCnt++;

	m_StorageItemListBox.AddText(Item);

	if( m_iStorageCurrentPageReceiveItemCnt >= m_iStorageCurrentPageItemCnt )
	{
		if( m_iSelectedStorageItemIndex > m_iStorageCurrentPageItemCnt )
		{
			m_StorageItemListBox.SLSetSelectLine(m_iStorageCurrentPageItemCnt);
		}
		else
		{
			m_StorageItemListBox.SLSetSelectLine(m_iSelectedStorageItemIndex);
		}
	}
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_InGameShopListBox[iListBoxIndex].AddText(Item);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT		// #ifndef
//--------------------------------------------
// ������ Data Del
void CNewUIInGameShop::DelStorageItem(int iStorageIndex, int iIndex)
{
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_StorageItemListBox.DelData(iIndex);
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_InGameShopListBox[iStorageIndex].DelData(iIndex);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

//--------------------------------------------
// �������� ���� ���õ� ������ �����
void CNewUIInGameShop::DelStorageSelectedItem()
{
	int iStorageIndex = m_ListBoxTabButton.GetCurButtonIndex();
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	int iListIndex = m_StorageItemListBox.SLGetSelectLineNum()-1;
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	int iListIndex = /*m_InGameShopListBox[iStorageIndex].GetLineNum()-*/m_InGameShopListBox[iStorageIndex].SLGetSelectLineNum()-1;
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	DelStorageItem(iStorageIndex, iListIndex);
}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

//--------------------------------------------
// �������� ��ü ������ �����
void CNewUIInGameShop::ClearAllStorageItem()
{
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	m_iStorageTotalItemCnt			= 0;
	m_iStorageCurrentPageItemCnt	= 0;
	m_iStorageTotalPage				= 0;
	m_iStorageCurrentPage			= 0;
	m_iStorageCurrentPageReceiveItemCnt = 0;

	m_StorageItemListBox.Clear();
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	for( int i=CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX ; i<CInGameShopSystem::IGS_TOTAL_LISTBOX ; i++ )
	{
		m_InGameShopListBox[i].Clear();
 	}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
void CNewUIInGameShop::InitStorage( int iTotalItemCnt, int iCurrentPageItemCnt, int iTotalPage, int iCurrentPage )
{
	ClearAllStorageItem();
	
	m_iStorageTotalItemCnt			= iTotalItemCnt;
	m_iStorageCurrentPageItemCnt	= iCurrentPageItemCnt;
	m_iStorageTotalPage				= iTotalPage;
#ifdef KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE
	if( m_iStorageTotalPage > 0 )
	{
		m_iStorageCurrentPage		= iCurrentPage;
	}
	else
	{
		m_iStorageCurrentPage		= 0;
	}
#else // KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE
	m_iStorageCurrentPage			= iCurrentPage;
#endif // KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE

	if( m_iSelectedStorageItemIndex == 0 || m_bRequestCurrentPage == false)
	{
		m_iSelectedStorageItemIndex = iCurrentPageItemCnt;
	}

	m_bRequestCurrentPage = false;
}

char CNewUIInGameShop::GetCurrentStorageCode()
{
	char szCode;
	switch(m_ListBoxTabButton.GetCurButtonIndex())
	{
	case IGS_SAFEKEEPING_LISTBOX:		// ������
		szCode = 'S';
		break;
	case IGS_PRESENTBOX_LISTBOX:		// ������
		szCode = 'G';
		break;
	default:
		szCode = 'Z';
		break;
	}
	return szCode;
}

void CNewUIInGameShop::StoragePrevPage()
{
	if( m_iStorageCurrentPage > 1 )
	{
		char szCode = GetCurrentStorageCode();
		m_iSelectedStorageItemIndex = 0;
		m_bRequestCurrentPage = true;
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage-1, &szCode);		// ������ ����Ʈ ��û
	}
}

void CNewUIInGameShop::StorageNextPage()
{
	if( m_iStorageCurrentPage < m_iStorageTotalPage )
	{
		char szCode = GetCurrentStorageCode();
		m_iSelectedStorageItemIndex = 0;
		m_bRequestCurrentPage = true;
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage+1, &szCode);		// ������ ����Ʈ ��û
	}
}

void CNewUIInGameShop::UpdateStorageItemList()
{
	char szCode = GetCurrentStorageCode();
	int iSelectLineIndex = m_StorageItemListBox.SLGetSelectLineNum();
	m_bRequestCurrentPage = true;

	if( (m_iStorageCurrentPageItemCnt == 1) && (m_iStorageTotalPage > 1))		// ���� ���������� 1������ ������
	{
		m_iSelectedStorageItemIndex = 1;
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage-1, &szCode);			// ������ ����Ʈ ��û
	}
	else if(iSelectLineIndex == 1)
	{
		m_iSelectedStorageItemIndex = iSelectLineIndex;							// ���� ���������� ���������õ� ������
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage, &szCode);				// ������ ����Ʈ ��û
	}
#ifdef KJH_FIX_BTS204_INGAMESHOP_ITEM_STORAGE_SELECT_LINE
	else if( m_iStorageCurrentPageItemCnt < IGS_STORAGE_TOTAL_ITEM_PER_PAGE )
	{
		m_iSelectedStorageItemIndex = (iSelectLineIndex-1);
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage, &szCode);				// ������ ����Ʈ ��û
	}
	else 
	{
		m_iSelectedStorageItemIndex = iSelectLineIndex;
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage, &szCode);				// ������ ����Ʈ ��û
	}
#else // KJH_FIX_BTS204_INGAMESHOP_ITEM_STORAGE_SELECT_LINE
	else 
	{
		m_iSelectedStorageItemIndex = (iSelectLineIndex-1);
		SendRequestIGS_ItemStorageList(m_iStorageCurrentPage, &szCode);				// ������ ����Ʈ ��û
	}
#endif // KJH_FIX_BTS204_INGAMESHOP_ITEM_STORAGE_SELECT_LINE
}

#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

//--------------------------------------------
// LoadImages
void CNewUIInGameShop::LoadImages()
{
	LoadBitmap("Interface\\newui_exit_00.tga", IMAGE_IGS_EXIT_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_shopback.jpg", IMAGE_IGS_BACK, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt01.tga", IMAGE_IGS_CATEGORY_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Deco_Center.tga", IMAGE_IGS_CATEGORY_DECO_MIDDLE, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Deco_Dn.tga", IMAGE_IGS_CATEGORY_DECO_DOWN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\ingame_Tab01.tga", IMAGE_IGS_LEFT_TAB, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\ingame_Tab02.tga", IMAGE_IGS_RIGHT_TAB, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Tab_Up.tga", IMAGE_IGS_ZONE_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt_Gift.tga", IMAGE_IGS_ITEMGIFT_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt_Cash.tga", IMAGE_IGS_CASHGIFT_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt_Reset.tga", IMAGE_IGS_REFRESH_BTN, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt03.tga", IMAGE_IGS_VIEWDETAIL_BTN, GL_LINEAR);
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT												// #ifndef
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt_Delete.tga", IMAGE_IGS_DELETE_BTN, GL_LINEAR);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	LoadBitmap("Interface\\InGameShop\\Ingame_Itembox_logo.tga", IMAGE_IGS_ITEMBOX_LOGO, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\ingame_Bt_page_L.tga", IMAGE_IGS_PAGE_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\ingame_Bt_page_R.tga", IMAGE_IGS_PAGE_RIGHT, GL_LINEAR);
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	LoadBitmap("Interface\\InGameShop\\IGS_Storage_Page.tga", IMAGE_IGS_STORAGE_PAGE, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\IGS_Storage_Page_Left.tga", IMAGE_IGS_STORAGE_PAGE_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\IGS_Storage_Page_Right.tga", IMAGE_IGS_STORAGE_PAGE_RIGHT, GL_LINEAR);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT


}


//--------------------------------------------
// UnloadImages
void CNewUIInGameShop::UnloadImages()
{
	DeleteBitmap(IMAGE_IGS_EXIT_BTN);
	DeleteBitmap(IMAGE_IGS_BACK);
	DeleteBitmap(IMAGE_IGS_CATEGORY_BTN);
	DeleteBitmap(IMAGE_IGS_CATEGORY_DECO_MIDDLE);
	DeleteBitmap(IMAGE_IGS_CATEGORY_DECO_DOWN);
	DeleteBitmap(IMAGE_IGS_LEFT_TAB);
	DeleteBitmap(IMAGE_IGS_RIGHT_TAB);
	DeleteBitmap(IMAGE_IGS_ZONE_BTN);
	DeleteBitmap(IMAGE_IGS_ITEMGIFT_BTN);
	DeleteBitmap(IMAGE_IGS_CASHGIFT_BTN);
	DeleteBitmap(IMAGE_IGS_REFRESH_BTN);
	DeleteBitmap(IMAGE_IGS_VIEWDETAIL_BTN);
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	DeleteBitmap(IMAGE_IGS_DELETE_BTN);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	DeleteBitmap(IMAGE_IGS_ITEMBOX_LOGO);
	DeleteBitmap(IMAGE_IGS_PAGE_LEFT);
	DeleteBitmap(IMAGE_IGS_PAGE_RIGHT);
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	DeleteBitmap(IMAGE_IGS_STORAGE_PAGE);
	DeleteBitmap(IMAGE_IGS_STORAGE_PAGE_LEFT);
	DeleteBitmap(IMAGE_IGS_STORAGE_PAGE_RIGHT);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}

#endif //PBG_ADD_INGAMESHOP_UI_ITEMSHOP