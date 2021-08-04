// MsgBoxIGSBuySelectItem.h: interface for the CMsgBoxIGSBuySelectItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGBOXIGSBUYSELECTITEM_H__96137D00_144C_4E10_B335_383E5DAB5D50__INCLUDED_)
#define AFX_MSGBOXIGSBUYSELECTITEM_H__96137D00_144C_4E10_B335_383E5DAB5D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#include "UIControls.h"
#include "NewUICommonMessageBox.h"

#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
#include "NewUIButton.h"
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL

#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
#include <ShopPackage.h>
#else // KJH_MOD_LIBRARY_LINK_EACH_NATION
#include "./InGameShopSystem/ShopListManager/ShopPackage.h"
#endif // KJH_MOD_LIBRARY_LINK_EACH_NATION


////////////////////////////////////////////////////////////////////
// ���� ��ǰ ����â
////////////////////////////////////////////////////////////////////


using namespace SEASON3B;

class CMsgBoxIGSBuySelectItem : public CNewUIMessageBoxBase, public INewUI3DRenderObj
{
public:
	CMsgBoxIGSBuySelectItem();
	virtual ~CMsgBoxIGSBuySelectItem();	
	
private:
	enum IMAGE_IGS_BUY_SELECT_ITEM
	{
		IMAGE_IGS_MGSBOX_BACK = BITMAP_IGS_MSGBOX_BUY_SELECT_ITEM,				// �ΰ��Լ� ���
		IMAGE_IGS_BUTTON = BITMAP_IGS_MSGBOX_BUTTON,							//�ΰ��Ӽ� ��ư
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_CASHPOINT_TYPE		= BITMAP_IGS_MSGBOX_SELECT_CASHPOINT_TYPE,	// ĳ������Ʈ ���� UI
		IMAGE_IGS_CASHPOINT_CHECK_BOX	= BITMAP_IGS_MSGBOX_SELECT_CHECK_BOX,		// ĳ������Ʈ UI üũ�ڽ�
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	};

	enum IMAGESIZE_IGS_BUY_SELECT_ITEM
	{
		IMAGE_IGS_WINDOW_WIDTH			= 640,		// �ΰ��Ӽ� ��� ������
		IMAGE_IGS_WINDOW_HEIGHT			= 429,
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_FRAME_WIDTH			= 215,		// �޼����ڽ� �̹��� ������
		IMAGE_IGS_FRAME_HEIGHT			= 372,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_FRAME_WIDTH			= 215,		// �޼����ڽ� �̹��� ������
		IMAGE_IGS_FRAME_HEIGHT			= 346,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_BTN_WIDTH				= 52,		// ��ư Size
		IMAGE_IGS_BTN_HEIGHT			= 26,
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IMAGE_IGS_CASHPOINT_TYPE_WIDTH	= 56,
		IMAGE_IGS_CASHPOINT_TYPE_HEIGHT	= 29,
		IMAGE_IGS_CASHPOINT_CHECK_BOX_WIDTH = 10,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	};

	enum IGS_BUY_SELECT_ITEM
	{
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_BTN_BUY_POS_X		= 27,		// ���� ��ư ��ġ
		IGS_BTN_PRESENT_POS_X	= 83,		// ���� ��ư
		IGS_BTN_CANCEL_POS_X	= 139,		// ��ҹ�ư
		IGS_BTN_POS_Y			= 331,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_BTN_BUY_POS_X		= 26,		// ���� ��ư ��ġ
		IGS_BTN_PRESENT_POS_X	= 82,		// ���� ��ư
		IGS_BTN_CANCEL_POS_X	= 138,		// ��ҹ�ư
		IGS_BTN_POS_Y			= 309,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_TITLE_POS_Y	= 10,		// Title
		IGS_TEXT_NAME_POS_X		= 5,		// ��ǰ Name;
		IGS_TEXT_NAME_POS_Y		= 100,
		IGS_TEXT_ATTR_POS_X		= 15,		// �Ӽ�
		IGS_TEXT_ATTR_POS_Y		= 118,
		IGS_TEXT_ATTR_WIDTH		= 194,
		IGS_TEXT_PRICE_POS_X	= 129,		// Price ����
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_POX_Y	= 290,
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_POX_Y	= 288,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_TEXT_PRICE_WIDTH	= 66,
		IGS_TEXT_DISCRIPTION_WIDTH	= 185,
		IGS_LISTBOX_POS_X		= 17,		// ListBox
		IGS_LISTBOX_POS_Y		= 277,
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_CASHPOINT_TYPE_POS_X	= 16,
		IGS_CASHPOINT_TYPE_POS_Y	= 298,
		IGS_CASHPOINT_CHECK_BOX_POS_X	= 74,
		IGS_CASHPOINT_CHECK_BOX_POS_Y	= 300,
		IGS_CASHPOINT_CHECK_BOX_DISTANCE_Y	= 6,
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
		IGS_3DITEM_POS_X		= 60,		// 3D ������ ���� ���� ��ġ(BOX ����)
		IGS_3DITEM_POS_Y		= 33,
		IGS_3DITEM_WIDTH		= 96,		// 3D ������ ���� ��������
		IGS_3DITEM_HEIGHT		= 60,
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
	bool Create(float fPriority = 3.f);
	void Release();
	bool Update();
	bool Render();

	void Initialize(CShopPackage* pPackage);
	
	void Render3D();
	bool IsVisible() const;
	
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

	void LoadImages();
	void UnloadImages();

	//����Ʈ �ڽ� ���� �޼ҵ�
	void CreateListBox();
	void RenderListBox();
	void ReleaseListBox();
	void ListBoxDoAction();
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	void AddData(int iPackageSeq, int iDisplaySeq, int iPriceSeq, int iProductSeq, unicode::t_char* pszPriceUnit);
#else // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
void CMsgBoxIGSBuySelectItem::AddData(int iPackageSeq, int iDisplaySeq, int iPriceSeq, int iProductSeq, unicode::t_char* pszPriceUnit, int iCashType);
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
		void CMsgBoxIGSBuySelectItem::AddData(int iPackageSeq, int iDisplaySeq, int iPriceSeq, int iProductSeq, unicode::t_char* pszPriceUnit);
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	
private:
	// ��ư
	CNewUIMessageBoxButton m_BtnBuy;
	CNewUIMessageBoxButton m_BtnPresent;
	CNewUIMessageBoxButton m_BtnCancel;

#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	CNewUIRadioGroupButton m_BtnSelectCashType;
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	
	// ����Ʈ �ڽ�
	CUIPackCheckBuyingListBox m_SelectBuyListBox;

	int		m_iPackageSeq;
	int		m_iDisplaySeq;
	WORD	m_wItemCode;
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	int		m_iCashType;				// ĳ��Ÿ�� (C/P) - �۷ι� ����
	int		m_iSelectedCashType;		// ���� ���õ� ĳ�� Ÿ��
	bool	m_bIsSendGift;				// ���������Ѱ�?
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL

	int		m_iDescriptionLine;

	unicode::t_char		m_szPackageName[MAX_TEXT_LENGTH];
	unicode::t_char		m_szPrice[MAX_TEXT_LENGTH];
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char		m_szPriceUnit[MAX_TEXT_LENGTH];
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char		m_szDescription[UIMAX_TEXT_LINE][MAX_TEXT_LENGTH];
};

////////////////////////////////////////////////////////////////////
// LayOut
////////////////////////////////////////////////////////////////////
class CMsgBoxIGSBuySelectItemLayout : public TMsgBoxLayout<CMsgBoxIGSBuySelectItem>
{
public:
	bool SetLayout();
};

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#endif // !defined(AFX_MSGBOXIGSBUYSELECTITEM_H__96137D00_144C_4E10_B335_383E5DAB5D50__INCLUDED_)
