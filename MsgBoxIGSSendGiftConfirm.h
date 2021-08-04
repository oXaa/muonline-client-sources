// MsgBoxIGSSendGiftConfirm.h: interface for the CMsgBoxIGSSendGiftConfirm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGBOXIGSSENDGIFTCONFIRM_H__A3F83A3C_2746_436C_ADE2_EDDDA9ED371D__INCLUDED_)
#define AFX_MSGBOXIGSSENDGIFTCONFIRM_H__A3F83A3C_2746_436C_ADE2_EDDDA9ED371D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#include "UIControls.h"
#include "NewUIOptionWindow.h"
#include "NewUIMessageBox.h"
#include "NewUICommonMessageBox.h"

using namespace SEASON3B;

class CMsgBoxIGSSendGiftConfirm : public CNewUIMessageBoxBase
{
public:
	enum IMAGE_IGS_SEND_GIFT_CONFIRM
	{
		IMAGE_IGS_BUTTON	= BITMAP_IGS_MSGBOX_BUTTON,				// �ΰ��Ӽ� ��ư
		IMAGE_IGS_BACK		= CNewUIOptionWindow::IMAGE_OPTION_FRAME_BACK,
		IMAGE_IGS_UP		= CNewUIOptionWindow::IMAGE_OPTION_FRAME_UP,
		IMAGE_IGS_DOWN		= CNewUIOptionWindow::IMAGE_OPTION_FRAME_DOWN,
		IMAGE_IGS_LEFTLINE	= CNewUIOptionWindow::IMAGE_OPTION_FRAME_LEFT,
		IMAGE_IGS_RIGHTLINE = CNewUIOptionWindow::IMAGE_OPTION_FRAME_RIGHT,
		IMAGE_IGS_TEXTBOX	= BITMAP_IGS_MGSBOX_BUY_CONFIRM_TEXT_BOX,		// ���������� �ؽ�Ʈ �ڽ�
	};

	enum IMAGESIZE_IGS_SEND_GIFT_CONFIRM
	{
		IMAGE_IGS_WINDOW_WIDTH	= 640,	// �ΰ��Ӽ� ��� ������
		IMAGE_IGS_WINDOW_HEIGHT = 429,
		IMAGE_IGS_FRAME_WIDTH	= 190,	// �޼����ڽ� Size
		IMAGE_IGS_FRAME_HEIGHT	= 179,
		IMAGE_IGS_TEXTBOX_WIDTH = 160,	// ������ ���� Textbox
		IMAGE_IGS_TEXTBOX_HEIGHT = 41,
		IMAGE_IGS_UP_HEIGHT		= 64,
		IMAGE_IGS_DOWN_HEIGHT	= 45,
		IMAGE_IGS_LINE_WIDTH	= 21,
		IMAGE_IGS_LINE_HEIGHT	= 10,
		IMAGE_IGS_BTN_WIDTH		= 52,	// ��ư Size
		IMAGE_IGS_BTN_HEIGHT	= 26,
	};

	// �޼����ڽ����� �����ǥ
	enum IGS_SEND_GIFT_CONFIRM_POS
	{
		IGS_BTN_OK_POS_X		= 35,
		IGS_BTN_CANCEL_POS_X	= 105,
		IGS_BTN_POS_Y			= 140,
		IGS_TEXTBOX_POS_X		= 15,			// ���������� Textbox
		IGS_TEXTBOX_POS_Y		= 58,
		IGS_TEXT_TITLE_POS_Y	= 10,			// Title
		IGS_TEXT_QUESTION_POS_Y	= 42,			// ����
		IGS_TEXT_NOTICE_POS_Y	= 105,			// ���ǻ���
		IGS_TEXT_NOTICE_WIDTH	= 150,
		IGS_TEXT_ITEM_INFO_POS_X		= 25,	// ����������
		IGS_TEXT_ITEM_INFO_NAME_POS_Y	= 64,
		IGS_TEXT_ITEM_INFO_PRICE_POS_Y	= 75,
		IGS_TEXT_ITEM_INFO_PERIOD_POS_Y = 86,
		IGS_TEXT_ITEM_INFO_WIDTH		= 143,	// ���������� Text Size
	};

public:
	CMsgBoxIGSSendGiftConfirm();
	~CMsgBoxIGSSendGiftConfirm();
	
	bool Create(float fPriority = 3.f);
	void Release();
	
	bool Update();
	bool Render();

#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
		#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
		void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, DWORD wItemCode, int iCashType,
												   unicode::t_char* pszID, unicode::t_char* pszMessage, 
												   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod);
		#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
												   void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, DWORD wItemCode,
												   unicode::t_char* pszID, unicode::t_char* pszMessage, 
												   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod);
		#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

#else // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, int iCashType
											   unicode::t_char* pszID, unicode::t_char* pszMessage, 
											   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod);
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
											   void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, 
											   unicode::t_char* pszID, unicode::t_char* pszMessage, 
											   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod);
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	
	static CALLBACK_RESULT LButtonUp(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	static CALLBACK_RESULT OKButtonDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	static CALLBACK_RESULT CancelButtonDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam);
	
private:
	void SetAddCallbackFunc();
	void SetButtonInfo();
	
	void RenderFrame();
	void RenderTexts();
	void RenderButtons();

	void LoadImages();
	void UnloadImages();

private:	
	// buttons
	CNewUIMessageBoxButton m_BtnOk;
	CNewUIMessageBoxButton m_BtnCancel;

	int m_iMiddleCount;

	// Item����
	int		m_iPackageSeq;
	int		m_iDisplaySeq;
	int		m_iPriceSeq;
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	DWORD	m_wItemCode;
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	int		m_iCashType;		// ĳ��Ÿ�� (C/P) - �۷ι� ����
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

	unicode::t_char m_szID[MAX_ID_SIZE+1];				// ���� ���� ID
	unicode::t_char m_szMessage[MAX_GIFT_MESSAGE_SIZE];	// ���� Meaasge
	
	// Item���� Text
	unicode::t_char		m_szItemName[MAX_TEXT_LENGTH];
	unicode::t_char		m_szItemPrice[MAX_TEXT_LENGTH];
	unicode::t_char		m_szItemPeriod[MAX_TEXT_LENGTH];

	unicode::t_char		m_szNotice[NUM_LINE_CMB][MAX_TEXT_LENGTH];
	
	int		m_iNumNoticeLine;
};

////////////////////////////////////////////////////////////////////
// LayOut
////////////////////////////////////////////////////////////////////
class CMsgBoxIGSSendGiftConfirmLayout : public TMsgBoxLayout<CMsgBoxIGSSendGiftConfirm>
{
public:
	bool SetLayout();
};

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM


#endif // !defined(AFX_MSGBOXIGSSENDGIFTCONFIRM_H__A3F83A3C_2746_436C_ADE2_EDDDA9ED371D__INCLUDED_)
