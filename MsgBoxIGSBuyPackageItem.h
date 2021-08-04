// MsgBoxIGSBuyPackageItem.h: interface for the CMsgBoxIGSBuyPackageItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGBOXIGSBUYPACKAGEITEM_H__42A6E746_9439_4E71_9C86_7CDF5F96AFE3__INCLUDED_)
#define AFX_MSGBOXIGSBUYPACKAGEITEM_H__42A6E746_9439_4E71_9C86_7CDF5F96AFE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#include "UIControls.h"
#include "NewUIMessageBox.h"
#include "NewUICommonMessageBox.h"
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#include "NewUIButton.h"
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
#include <ShopPackage.h>
#else // KJH_MOD_LIBRARY_LINK_EACH_NATION
#include "./InGameShopSystem/ShopListManager/ShopPackage.h"
#endif // KJH_MOD_LIBRARY_LINK_EACH_NATION


using namespace SEASON3B;

////////////////////////////////////////////////////////////////////
// ����/��Ű�� ��ǰ ����â
////////////////////////////////////////////////////////////////////
class CMsgBoxIGSBuyPackageItem : public CNewUIMessageBoxBase, public INewUI3DRenderObj
{
public:
	enum IMAGE_IGS_BUY_PACKAGE_ITEM
	{
		IMAGE_IGS_FRAME		= BITMAP_IGS_MSGBOX_BUY_PACKAGE_ITEM,	// ���
		IMAGE_IGS_BUTTON	= BITMAP_IGS_MSGBOX_BUTTON,				// �ΰ��Ӽ� ��ư
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_CASHPOINT_TYPE		= BITMAP_IGS_MSGBOX_SELECT_CASHPOINT_TYPE,	// ĳ������Ʈ ���� UI
		IMAGE_IGS_CASHPOINT_CHECK_BOX	= BITMAP_IGS_MSGBOX_SELECT_CHECK_BOX,		// ĳ������Ʈ UI üũ�ڽ�
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	};

	enum IMAGESIZE_IGS_BUY_PACKAGE_ITEM
	{
		IMAGE_IGS_WINDOW_WIDTH	= 640,	// �ΰ��Ӽ� ��� ������
		IMAGE_IGS_WINDOW_HEIGHT = 429,
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_FRAME_WIDTH	= 198,	// Back �̹��� ������
		IMAGE_IGS_FRAME_HEIGHT	= 312,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_FRAME_WIDTH	= 198,	// Back �̹��� ������
		IMAGE_IGS_FRAME_HEIGHT	= 291,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_BTN_WIDTH		= 52,	// ��ư Size
		IMAGE_IGS_BTN_HEIGHT	= 26,	
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_CASHPOINT_TYPE_WIDTH	= 56,
		IMAGE_IGS_CASHPOINT_TYPE_HEIGHT	= 29,
		IMAGE_IGS_CASHPOINT_CHECK_BOX_WIDTH = 10,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	};

	enum IGS_BUY_PACKAGE_ITEM_POS
	{	
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_BTN_BUY_POS_X		= 17,	// ���� ��ư ��ġ
		IGS_BTN_PRESENT_POS_X	= 73,	// ���� ��ư
		IGS_BTN_CANCEL_POS_X	= 129,	// ��ҹ�ư
		IGS_BTN_POS_Y			= 272,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_BTN_BUY_POS_X		= 18,	// ���� ��ư ��ġ
		IGS_BTN_PRESENT_POS_X	= 74,	// ���� ��ư
		IGS_BTN_CANCEL_POS_X	= 130,	// ��ҹ�ư
		IGS_BTN_POS_Y			= 253,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_TITLE_POS_Y	= 10,	// Title
		IGS_TEXT_NAME_POS_X		= 5,	// ��ǰ Name;
		IGS_TEXT_NAME_POS_Y		= 100,
		IGS_TEXT_NAME_WIDTH		= 196,
		IGS_TEXT_PRICE_POS_X	= 118,	// Price
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_POX_Y	= 231,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_POX_Y	= 229,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_WIDTH	= 66,
		IGS_LISTBOX_POS_X		= 14,	// ItemListBox
		IGS_LISTBOX_POS_Y		= 216,
		IGS_LISTBOX_WIDTH		= 158,
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_CASHPOINT_TYPE_POS_X	= 10,
		IGS_CASHPOINT_TYPE_POS_Y	= 239,
		IGS_CASHPOINT_CHECK_BOX_POS_X	= 68,
		IGS_CASHPOINT_CHECK_BOX_POS_Y	= 241,
		IGS_CASHPOINT_CHECK_BOX_DISTANCE_Y	= 6,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_3DITEM_POS_X = 50,		// 3D ������ ���� ���� ��ġ(BOX ����)
		IGS_3DITEM_POS_Y = 34,
		IGS_3DITEM_WIDTH = 96,		// 3D ������ ���� ��������
		IGS_3DITEM_HEIGHT = 60,
	};

#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	enum IGS_BUY_SELECT_CASHTYPE
	{
		IGS_BUY_CASHTYPE_CREDIT	= 508,
		IGS_BUY_CASHTYPE_PREPAID = 509,
		IGS_BUY_SELECT_INDEX_CASHTYPE_CREDIT = 0,
		IGS_BUY_SELECT_INDEX_CASHTYPE_PREPAID = 1,
	};
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	
public:
	CMsgBoxIGSBuyPackageItem();
	virtual ~CMsgBoxIGSBuyPackageItem();
	
	bool Create(float fPriority = 3.f);
	void Release();
	bool Update();
	bool Render();
	
	bool IsVisible() const;
	
	void Render3D();

	void Initialize(CShopPackage* pPackage);
	
	static CALLBACK_RESULT LButtonUp(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	static CALLBACK_RESULT BuyBtnDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	static CALLBACK_RESULT PresentBtnDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	static CALLBACK_RESULT CancelBtnDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);

private:
	void SetAddCallbackFunc();
	void SetButtonInfo();
	void RenderFrame();
	void RenderTexts();
	void RenderButtons();

	void CreateListBox();
	void RenderListBox();
	void ListBoxDoAction();
	void ReleaseListBox();

#ifdef LEM_FIX_WARNINGMSG_BUYITEM // Add_WarningMsgBuyItem ������� [lem.2010.7.28]
	bool Add_WarningMsgBuyItem( int _nItemIndex );
#endif	// LEM_FIX_WARNINGMSG_BUYITEM

	void LoadImages();
	void UnloadImages();
	
private:
	CNewUIMessageBoxButton m_BtnBuy;
	CNewUIMessageBoxButton m_BtnPresent;
	CNewUIMessageBoxButton m_BtnCancel;
	
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	CNewUIRadioGroupButton m_BtnSelectCashType;
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	
	//����Ʈ �ڽ� ���� �޼ҵ�
	CUIBuyingListBox	m_PackageInfo;

	int		m_iPackageSeq;
	int		m_iDisplaySeq;
	WORD	m_wItemCode;
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	int		m_iCashType;				// ĳ��Ÿ�� (C/P) - �۷ι� ����
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	int		m_iSelectedCashType;		// ���� ���õ� ĳ�� Ÿ��
	bool	m_bIsSendGift;				// ���������Ѱ�?
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	
	unicode::t_char		m_szPackageName[MAX_TEXT_LENGTH];
	unicode::t_char		m_szPrice[MAX_TEXT_LENGTH];
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char		m_szPriceUnit[MAX_TEXT_LENGTH];
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char		m_szPeriod[MAX_TEXT_LENGTH];
	unicode::t_char		m_szDescription[UIMAX_TEXT_LINE][MAX_TEXT_LENGTH];
};

////////////////////////////////////////////////////////////////////
// LayOut
////////////////////////////////////////////////////////////////////
class CMsgBoxBuyPackageItemLayout : public TMsgBoxLayout<CMsgBoxIGSBuyPackageItem>
{
public:
	bool SetLayout();
};


#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#endif // !defined(AFX_MSGBOXIGSBUYPACKAGEITEM_H__42A6E746_9439_4E71_9C86_7CDF5F96AFE3__INCLUDED_)
