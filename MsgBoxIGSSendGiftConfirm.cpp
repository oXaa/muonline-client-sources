// MsgBoxIGSSendGiftConfirm.cpp: implementation of the CMsgBoxIGSSendGiftConfirm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#include "MsgBoxIGSSendGiftConfirm.h"

#include "DSPlaySound.h"
#include "wsclientinline.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgBoxIGSSendGiftConfirm::CMsgBoxIGSSendGiftConfirm()
{
	m_iMiddleCount = 7;

	m_iPackageSeq	= 0;
	m_iDisplaySeq	= 0;
	m_iPriceSeq		= 0;
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	m_wItemCode		= -1;
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	m_iCashType		= 0;
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	
	m_szItemName[0] = '\0';
	m_szItemPrice[0] = '\0';
	m_szItemPeriod[0] = '\0';

	for(int i=0 ; i<NUM_LINE_CMB ; i++)
	{
		m_szNotice[i][0] = '\0';
	}
	
	m_iNumNoticeLine = 0;
}

CMsgBoxIGSSendGiftConfirm::~CMsgBoxIGSSendGiftConfirm()
{
	Release();
}

//--------------------------------------------
// Create
bool CMsgBoxIGSSendGiftConfirm::Create(float fPriority)
{
	LoadImages();
	SetAddCallbackFunc();
	
	CNewUIMessageBoxBase::Create((IMAGE_IGS_WINDOW_WIDTH/2)-(IMAGE_IGS_FRAME_WIDTH/2), 
		(IMAGE_IGS_WINDOW_HEIGHT/2)-(IMAGE_IGS_FRAME_HEIGHT/2), 
		IMAGE_IGS_FRAME_WIDTH, IMAGE_IGS_FRAME_HEIGHT, fPriority);
	
	SetButtonInfo();

	SetMsgBackOpacity();
	
	return true;
}

//--------------------------------------------
// Initialize
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
		void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, DWORD wItemCode, int iCashType,
												   unicode::t_char* pszID, unicode::t_char* pszMessage, 
												   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod)
	#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
												   void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, DWORD wItemCode,
												   unicode::t_char* pszID, unicode::t_char* pszMessage, 
												   unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod)
		#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

#else // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, int iCashType
											   unicode::t_char* pszID, unicode::t_char* pszMessage, 
												unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod)
	#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	void CMsgBoxIGSSendGiftConfirm::Initialize(int iPackageSeq, int iDisplaySeq, int iPriceSeq, 
												unicode::t_char* pszID, unicode::t_char* pszMessage, 
												unicode::t_char* pszName, unicode::t_char* pszPrice, unicode::t_char* pszPeriod)
	#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
{
	m_iPackageSeq	= iPackageSeq;
	m_iDisplaySeq	= iDisplaySeq;
	m_iPriceSeq		= iPriceSeq;
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	m_wItemCode	= wItemCode;
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	m_iCashType		= iCashType;
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

	strcpy(m_szID, pszID);
	strcpy(m_szMessage, pszMessage);

	strcpy(m_szItemName, pszName);
	strcpy(m_szItemPrice, pszPrice);
	strcpy(m_szItemPeriod, pszPeriod);

	//int m_iNumNoticeLine = SeparateTextIntoLines( GlobalText[2898], txtline[0], NUM_LINE_CMB, MAX_LENGTH_CMB);
	m_iNumNoticeLine = ::DivideStringByPixel(&m_szNotice[0][0], NUM_LINE_CMB, MAX_TEXT_LENGTH, GlobalText[2898], IGS_TEXT_NOTICE_WIDTH);
}

//--------------------------------------------
// Release
void CMsgBoxIGSSendGiftConfirm::Release()
{
	CNewUIMessageBoxBase::Release();

	UnloadImages();
}

//--------------------------------------------
// Update
bool CMsgBoxIGSSendGiftConfirm::Update()
{
	m_BtnOk.Update();
	m_BtnCancel.Update();

	return true;
}

//--------------------------------------------
// Render
bool CMsgBoxIGSSendGiftConfirm::Render()
{
	EnableAlphaTest();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderMsgBackColor(true);

	RenderFrame();
	RenderTexts();
	RenderButtons();
	DisableAlphaBlend();

	return true;
}

//--------------------------------------------
// SetAddCallbackFunc
void CMsgBoxIGSSendGiftConfirm::SetAddCallbackFunc()
{
	AddCallbackFunc(CMsgBoxIGSSendGiftConfirm::LButtonUp, MSGBOX_EVENT_MOUSE_LBUTTON_UP);
	AddCallbackFunc(CMsgBoxIGSSendGiftConfirm::OKButtonDown, MSGBOX_EVENT_USER_COMMON_OK);
	AddCallbackFunc(CMsgBoxIGSSendGiftConfirm::CancelButtonDown, MSGBOX_EVENT_USER_COMMON_CANCEL);
}

//--------------------------------------------
// LButtonUp
CALLBACK_RESULT CMsgBoxIGSSendGiftConfirm::LButtonUp(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam)
{
	CMsgBoxIGSSendGiftConfirm* pOwnMsgBox = dynamic_cast<CMsgBoxIGSSendGiftConfirm*>(pOwner);
	if(pOwnMsgBox)
	{
		if(pOwnMsgBox->m_BtnOk.IsMouseIn() == true)
		{
			g_MessageBox->SendEvent(pOwner, MSGBOX_EVENT_USER_COMMON_OK);
			return CALLBACK_BREAK;
		}

		if(pOwnMsgBox->m_BtnCancel.IsMouseIn() == true)
		{
			g_MessageBox->SendEvent(pOwner, MSGBOX_EVENT_USER_COMMON_CANCEL);
			return CALLBACK_BREAK;
		}
	}

	return CALLBACK_CONTINUE;
}


//--------------------------------------------
// OKButtonDown
CALLBACK_RESULT CMsgBoxIGSSendGiftConfirm::OKButtonDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam)
{
	CMsgBoxIGSSendGiftConfirm* pOwnMsgBox = dynamic_cast<CMsgBoxIGSSendGiftConfirm*>(pOwner);

#ifdef LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT
	// 포인트로 구매 
	BOOL bBuyingWithGP = (	strstr(pOwnMsgBox->m_szItemPrice, GlobalText[2326]) != NULL || 
		strstr(pOwnMsgBox->m_szItemPrice, "Point") != NULL || 
							strstr(pOwnMsgBox->m_szItemPrice, "포인트") != NULL ) ?  TRUE : FALSE;
#endif // LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT

#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
			SendRequestIGS_SendItemGift(pOwnMsgBox->m_iPackageSeq, pOwnMsgBox->m_iDisplaySeq, pOwnMsgBox->m_iPriceSeq, 0,
				pOwnMsgBox->m_wItemCode, pOwnMsgBox->m_iCashType, pOwnMsgBox->m_szID, pOwnMsgBox->m_szMessage);
	#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
			# ifdef LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT
			SendRequestIGS_SendItemGift(pOwnMsgBox->m_iPackageSeq, pOwnMsgBox->m_iDisplaySeq, pOwnMsgBox->m_iPriceSeq, 0, 
				pOwnMsgBox->m_wItemCode, bBuyingWithGP, pOwnMsgBox->m_szID, pOwnMsgBox->m_szMessage);
			#else
			SendRequestIGS_SendItemGift(pOwnMsgBox->m_iPackageSeq, pOwnMsgBox->m_iDisplaySeq, pOwnMsgBox->m_iPriceSeq, 0, 
				pOwnMsgBox->m_wItemCode, pOwnMsgBox->m_szID, pOwnMsgBox->m_szMessage);
			#endif	// LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT [lem_2010.9.2]
	#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#else // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
		SendRequestIGS_SendItemGift(pOwnMsgBox->m_iPackageSeq, pOwnMsgBox->m_iDisplaySeq, pOwnMsgBox->m_iPriceSeq, 0,
									pOwnMsgBox->m_iCashType, pOwnMsgBox->m_szID, pOwnMsgBox->m_szMessage);
	#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
		SendRequestIGS_SendItemGift(pOwnMsgBox->m_iPackageSeq, pOwnMsgBox->m_iDisplaySeq, pOwnMsgBox->m_iPriceSeq, 0, 
									pOwnMsgBox->m_szID, pOwnMsgBox->m_szMessage);
	#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL

	PlayBuffer(SOUND_CLICK01);
	g_MessageBox->SendEvent(pOwner, MSGBOX_EVENT_DESTROY);

	return CALLBACK_BREAK;
}

//--------------------------------------------
// CancelButtonDown
CALLBACK_RESULT CMsgBoxIGSSendGiftConfirm::CancelButtonDown(class CNewUIMessageBoxBase* pOwner, const leaf::xstreambuf& xParam)
{
	PlayBuffer(SOUND_CLICK01);
	g_MessageBox->SendEvent(pOwner, MSGBOX_EVENT_DESTROY);

	return CALLBACK_BREAK;
}

//--------------------------------------------
// SetButtonInfo
void CMsgBoxIGSSendGiftConfirm::SetButtonInfo()
{
	// 확인 버튼
	m_BtnOk.SetInfo(IMAGE_IGS_BUTTON, GetPos().x+IGS_BTN_OK_POS_X, GetPos().y+IGS_BTN_POS_Y, 
						IMAGE_IGS_BTN_WIDTH, IMAGE_IGS_BTN_HEIGHT, CNewUIMessageBoxButton::MSGBOX_BTN_CUSTOM, true);
	m_BtnOk.MoveTextPos(0, -1);
	m_BtnOk.SetText(GlobalText[228]);	
	
	// 취소 버튼
	m_BtnCancel.SetInfo(IMAGE_IGS_BUTTON, GetPos().x+IGS_BTN_CANCEL_POS_X, GetPos().y+IGS_BTN_POS_Y, 
						IMAGE_IGS_BTN_WIDTH, IMAGE_IGS_BTN_HEIGHT, CNewUIMessageBoxButton::MSGBOX_BTN_CUSTOM, true);
	m_BtnCancel.MoveTextPos(0, -1);
	m_BtnCancel.SetText(GlobalText[229]);	
}

//--------------------------------------------
// RenderFrame
void CMsgBoxIGSSendGiftConfirm::RenderFrame()
{
	int iY = GetPos().y;

	RenderImage(IMAGE_IGS_BACK, GetPos().x, iY, IMAGE_IGS_FRAME_WIDTH, IMAGE_IGS_FRAME_HEIGHT);
	RenderImage(IMAGE_IGS_UP, GetPos().x, iY, IMAGE_IGS_FRAME_WIDTH, IMAGE_IGS_UP_HEIGHT);
	iY += IMAGE_IGS_UP_HEIGHT;
	for(int i=0; i<m_iMiddleCount; ++i)
	{
		RenderImage(IMAGE_IGS_LEFTLINE, GetPos().x, iY, IMAGE_IGS_LINE_WIDTH, IMAGE_IGS_LINE_HEIGHT);
		RenderImage(IMAGE_IGS_RIGHTLINE, GetPos().x+IMAGE_IGS_FRAME_WIDTH-IMAGE_IGS_LINE_WIDTH, iY, 
						IMAGE_IGS_LINE_WIDTH, IMAGE_IGS_LINE_HEIGHT);
		iY += IMAGE_IGS_LINE_HEIGHT;
	}
	RenderImage(IMAGE_IGS_DOWN, GetPos().x, iY, IMAGE_IGS_FRAME_WIDTH, IMAGE_IGS_DOWN_HEIGHT);

	// 아이템정보 Textbox
	RenderImage(IMAGE_IGS_TEXTBOX, GetPos().x+IGS_TEXTBOX_POS_X, GetPos().y+IGS_TEXTBOX_POS_Y, 
					IMAGE_IGS_TEXTBOX_WIDTH, IMAGE_IGS_TEXTBOX_HEIGHT);

}

//--------------------------------------------
// RenderTexts
void CMsgBoxIGSSendGiftConfirm::RenderTexts()
{
	g_pRenderText->SetBgColor(0, 0, 0, 0);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetFont(g_hFontBold);

	// Title
	g_pRenderText->RenderText(GetPos().x, GetPos().y+IGS_TEXT_TITLE_POS_Y, GlobalText[2907], IMAGE_IGS_FRAME_WIDTH, 0, RT3_SORT_CENTER);

	g_pRenderText->SetFont(g_hFont);

	// 질문
	g_pRenderText->RenderText(GetPos().x, GetPos().y+IGS_TEXT_QUESTION_POS_Y, GlobalText[2908], IMAGE_IGS_FRAME_WIDTH, 0, RT3_SORT_CENTER);

	// 아이템 정보
	g_pRenderText->SetTextColor(247, 186, 0, 255);
	g_pRenderText->RenderText(GetPos().x+IGS_TEXT_ITEM_INFO_POS_X, GetPos().y+IGS_TEXT_ITEM_INFO_NAME_POS_Y, 
								m_szItemName, IGS_TEXT_ITEM_INFO_WIDTH, 0, RT3_SORT_LEFT);
	g_pRenderText->RenderText(GetPos().x+IGS_TEXT_ITEM_INFO_POS_X, GetPos().y+IGS_TEXT_ITEM_INFO_PRICE_POS_Y, 
								m_szItemPrice, IGS_TEXT_ITEM_INFO_WIDTH, 0, RT3_SORT_LEFT);
	g_pRenderText->RenderText(GetPos().x+IGS_TEXT_ITEM_INFO_POS_X, GetPos().y+IGS_TEXT_ITEM_INFO_PERIOD_POS_Y, 
								m_szItemPeriod, IGS_TEXT_ITEM_INFO_WIDTH, 0, RT3_SORT_LEFT);

	// 주의사항
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	for (int i=0; i<m_iNumNoticeLine; i++)
	{
		g_pRenderText->RenderText(GetPos().x, GetPos().y+IGS_TEXT_NOTICE_POS_Y+(i*10), m_szNotice[i], IMAGE_IGS_FRAME_WIDTH, 0, RT3_SORT_CENTER);
	}
	
#ifdef FOR_WORK
	unicode::t_char szText[256] = { 0, };
	g_pRenderText->SetTextColor(255, 0, 0, 255);
	sprintf(szText, "Package Seq : %d", m_iPackageSeq);
	g_pRenderText->RenderText(GetPos().x+IMAGE_IGS_FRAME_WIDTH, GetPos().y+10, szText, 200, 0, RT3_SORT_LEFT);
	sprintf(szText, "Display Seq : %d", m_iDisplaySeq);
	g_pRenderText->RenderText(GetPos().x+IMAGE_IGS_FRAME_WIDTH, GetPos().y+20, szText, 200, 0, RT3_SORT_LEFT);
	sprintf(szText, "Price Seq : %d", m_iPriceSeq);
	g_pRenderText->RenderText(GetPos().x+IMAGE_IGS_FRAME_WIDTH, GetPos().y+30, szText, 200, 0, RT3_SORT_LEFT);
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
	sprintf(szText, "ItemCode : %d", m_wItemCode);
	g_pRenderText->RenderText(GetPos().x+IMAGE_IGS_FRAME_WIDTH, GetPos().y+40, szText, 200, 0, RT3_SORT_LEFT);
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	sprintf(szText, "CashType : %d", m_iCashType);
	g_pRenderText->RenderText(GetPos().x+IMAGE_IGS_FRAME_WIDTH, GetPos().y+50, szText, 200, 0, RT3_SORT_LEFT);
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // FOR_WORK
}

//--------------------------------------------
// RenderButtons
void CMsgBoxIGSSendGiftConfirm::RenderButtons()
{
	m_BtnOk.Render();
	m_BtnCancel.Render();
}

//--------------------------------------------
// LoadImages
void CMsgBoxIGSSendGiftConfirm::LoadImages()
{
	LoadBitmap("Interface\\InGameShop\\Ingame_Bt03.tga",	IMAGE_IGS_BUTTON, GL_LINEAR);
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_IGS_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_IGS_DOWN, GL_LINEAR);	
	LoadBitmap("Interface\\newui_option_top.tga", IMAGE_IGS_UP, GL_LINEAR);	
	LoadBitmap("Interface\\newui_option_back06(L).tga", IMAGE_IGS_LEFTLINE, GL_LINEAR);	
	LoadBitmap("Interface\\newui_option_back06(R).tga", IMAGE_IGS_RIGHTLINE, GL_LINEAR);
	LoadBitmap("Interface\\InGameShop\\ingame_box.tga", IMAGE_IGS_TEXTBOX, GL_LINEAR);
}

//--------------------------------------------
// UnloadImages
void CMsgBoxIGSSendGiftConfirm::UnloadImages()
{
	DeleteBitmap(IMAGE_IGS_BUTTON);
	DeleteBitmap(IMAGE_IGS_BACK);
	DeleteBitmap(IMAGE_IGS_DOWN);	
	DeleteBitmap(IMAGE_IGS_UP);	
	DeleteBitmap(IMAGE_IGS_LEFTLINE);	
	DeleteBitmap(IMAGE_IGS_RIGHTLINE);
	DeleteBitmap(IMAGE_IGS_TEXTBOX);
}

////////////////////////////////////////////////////////////////////
// LayOut
////////////////////////////////////////////////////////////////////
bool CMsgBoxIGSSendGiftConfirmLayout::SetLayout()
{
	CMsgBoxIGSSendGiftConfirm* pMsgBox = GetMsgBox();
	if(false == pMsgBox)
		return false;
	
	if(false == pMsgBox->Create())
		return false;
	
	return true;
}

#endif KJH_ADD_INGAMESHOP_UI_SYSTEM
