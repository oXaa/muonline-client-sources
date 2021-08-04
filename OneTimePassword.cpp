//////////////////////////////////////////////////////////////////////
// OneTimePassword.cpp: implementation of the COneTimePassword class.
// 
// �ۼ���: ������
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef LJH_ADD_ONETIME_PASSWORD	
#include "OneTimePassword.h"
#include "Input.h"
#include "UIMng.h"

// �ؽ�Ʈ ������ ���� #include.
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"

#include "UIControls.h"
#include "ZzzScene.h"

#include "wsclientinline.h"
#include "DSPlaySound.h"

#include "Local.h"

#define LIW_OK			0	// Ȯ��(localized) ��ư.
#define LIW_CANCEL		1	// ���(localized) ��ư.

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;
extern int g_iChatInputType;
#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
extern int ServerSelectHi;
extern int ServerLocalSelect;
#endif // KJH_ADD_SERVER_LIST_SYSTEM

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COneTimePassword::COneTimePassword()
{
	
}

COneTimePassword::~COneTimePassword()
{
	SAFE_DELETE(m_pOTPInputBox);
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �α��� â ����.
//*****************************************************************************
void COneTimePassword::Create()
{
// �⺻ â ����.
	CWin::Create(329, 245, BITMAP_LOG_IN+7);

// �ؽ�Ʈ �Է� �ڽ�(OTP��) ��������Ʈ.
	m_sprInputBox.Create(156, 23, BITMAP_LOG_IN+8);

	DWORD adwBtnColor[3] = { CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE};
//	��ư ����.
	for (int i = 0; i < 2; ++i)
	{
		m_aBtn[i].Create(64, 29, SEASON3B::CNewUIMessageBoxMng::IMAGE_MSGBOX_BTN_EMPTY_SMALL, 3, 2, 1);
		//GlobalText[228]:"Ȯ��", GlobalText[3114]:"���"
		m_aBtn[i].SetText(GlobalText[228+i*2886], adwBtnColor);
		CWin::RegisterButton(&m_aBtn[i]);
		
		/*
		m_aBtn[i].Create(54, 30, BITMAP_BUTTON + i, 3, 2, 1);
		*/
	}

// �ؽ�Ʈ �Է� �ʱ�ȭ.
	m_pOTPInputBox = new CUITextInputBox;
	m_pOTPInputBox->Init(g_hWnd, 140, 14, MAX_ONETIME_PASSWORD_SIZE, TRUE);
	m_pOTPInputBox->SetBackColor(255, 0, 0, 0);
	m_pOTPInputBox->SetTextColor(255, 255, 230, 210);
	m_pOTPInputBox->SetFont(g_hFixFont);
	m_pOTPInputBox->SetState(UISTATE_NORMAL);
	m_pOTPInputBox->SetOption(UIOPTION_NUMBERONLY);
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void COneTimePassword::SetPosition(int nXCoord, int nYCoord)
{
	CWin::SetPosition(nXCoord, nYCoord);

	m_sprInputBox.SetPosition(nXCoord + 85, nYCoord + 130);
	
	if (g_iChatInputType == 1)
	{
		// ���� �Է� �ؽ�Ʈ.
		m_pOTPInputBox->SetPosition(int((m_sprInputBox.GetXPos() + 6) / g_fScreenRate_x),
			int((m_sprInputBox.GetYPos() + 6) / g_fScreenRate_y));
	}

	m_aBtn[LIW_OK].SetPosition(nXCoord + 90, nYCoord + 167);
	m_aBtn[LIW_CANCEL].SetPosition(nXCoord + 175, nYCoord + 167);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void COneTimePassword::Show(bool bShow)
{
	CWin::Show(bShow);

	m_sprInputBox.Show(bShow);
	for (int i = 0; i < 2; ++i)
	{
		m_aBtn[i].Show(bShow);
	}
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool COneTimePassword::CursorInWin(int nArea)
{
	if (!CWin::m_bShow)		// ������ �ʴ´ٸ� ó������ ����.
		return false;

	switch (nArea)
	{
	case WA_MOVE:
		return false;	// �̵� ������ ����.(�̵��� ����)
	}

	return CWin::CursorInWin(nArea);
}


//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void COneTimePassword::PreRelease()
{
	m_sprInputBox.Release();
}

//*****************************************************************************
// �Լ� �̸� : UpdateWhileActive()
// �Լ� ���� : ��Ƽ���� ���� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void COneTimePassword::UpdateWhileActive(double dDeltaTick)
{
	CInput& rInput = CInput::Instance();

	if (m_aBtn[LIW_OK].IsClick())			// OK ��ư�� Ŭ���ߴ°�?
	{
		// match user's input with one's otp in server 
		SendingOTP();
	}
	else if (m_aBtn[LIW_CANCEL].IsClick())	// Cancel ��ư�� Ŭ���ߴ°�?
	{
		// return to the login screen
		CancelInputOTP();
	}
	else if (CInput::Instance().IsKeyDown(VK_RETURN))// ����Ű�� �����°�?
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		SendingOTP();
	}
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE))// escŰ�� �����°�?
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		CancelInputOTP();
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
}

//*****************************************************************************
// �Լ� �̸� : UpdateWhileShow()
// �Լ� ���� : ���϶� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void COneTimePassword::UpdateWhileShow(double dDeltaTick)
{
	// OTP �Է� �ź�
	m_pOTPInputBox->GiveFocus();
	m_pOTPInputBox->DoAction();
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void COneTimePassword::RenderControls()
{
	CWin::RenderButtons();

	m_sprInputBox.Render();

// �ؽ�Ʈ �Է� �κ�.
	m_pOTPInputBox->Render();
	
	// '����', '��ȣ' �ؽ�Ʈ �κ�.
	// �ؽ�Ʈ ���� ����.
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->RenderText(int((CWin::GetXPos()+75) / g_fScreenRate_x),
		int((CWin::GetYPos() + 97)/ g_fScreenRate_y), GlobalText[3110]);
}


//*****************************************************************************
// �Լ� �̸� : SendingOTP()
// �Լ� ���� : ������ OneTime Password ����.
//*****************************************************************************
void COneTimePassword::SendingOTP()
{
	if (CurrentProtocolState == REQUEST_JOIN_SERVER)
		return;

	CUIMng::Instance().HideWin(this);	// �α��� â�� ����.

	char	szID[MAX_ID_SIZE+1];
	char	szPW[MAX_ID_SIZE+1];
	char	szOTP[MAX_ONETIME_PASSWORD_SIZE+1];
	memset( szID, 0, sizeof(char) * MAX_ID_SIZE+1 );
	memset( szPW, 0, sizeof(char) * MAX_ID_SIZE+1 );
	memset( szOTP, 0, sizeof(char) * MAX_ONETIME_PASSWORD_SIZE+1 );
	
	m_pOTPInputBox->GetText(szOTP, MAX_ONETIME_PASSWORD_SIZE+1);
	
	if (unicode::_strlen(szOTP) <= 0)	// OneTime Password �Է��� ���� �ʰ� OK Ŭ��.
	{
		CUIMng::Instance().PopUpMsgWin(MESSAGE_OTP_NOT_WRITTEN);
	}
	else	// ������ �α��� �� ���¿��� OTP �Է¿Ϸ�.
	{
		if (CurrentProtocolState == REQUEST_LOG_IN)
		{
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write( MCD_NORMAL, "Sending OTP to Server: (ID)%s", szID);
#endif //CONSOLE_DEBUG
			// ������ OneTime Password ����.
			g_ErrorReport.Write("> Sending OTP \"%s\"\r\n", szID);
			// SendRequestOTP() �ȿ��� LogIn = 1�� ����.
			CUIMng::Instance().m_LoginWin.GetIDInputBox()->GetText(szID, MAX_ID_SIZE+1);
			CUIMng::Instance().m_LoginWin.GetPassInputBox()->GetText(szPW, MAX_ID_SIZE+1);
	
			SendRequestOTP(szID, szPW, szOTP, 0x01);
		}
	}
}


//*****************************************************************************
// �Լ� �̸� :	CancelInputOTP()
// �Լ� ���� :	OneTime Password �Է� ���.
//				OneTime Password �Է�â�� �ݰ� 
//				���� ���� ������ ���� ���� ������ �ٽ� ����.
//*****************************************************************************
void COneTimePassword::CancelInputOTP()
{
	ConnectConnectionServer();
	// OneTime Password �Է�â�� ����.
	CUIMng::Instance().HideWin(this);

	ClearLoginInfoFromInputBox();
}

//*****************************************************************************
// �Լ� �̸� : ConnectConnectionServer()
// �Լ� ���� : ���� ������ �ٽ� ����.
//*****************************************************************************
void COneTimePassword::ConnectConnectionServer()
{
	SocketClient.Close();		// ���� ���� ������ ����.

	LogIn = 0;
	CurrentProtocolState = REQUEST_JOIN_SERVER;
	// ���� ������ �ٽ� ����.
    ::CreateSocket(szServerIpAddress, g_ServerPort);
}

//*****************************************************************************
// �Լ� �̸� : ClearLoginInfoFromInputBox()
// �Լ� ���� : for better security, remove the password and OneTime Password from the inputbox.
//*****************************************************************************
void COneTimePassword::ClearLoginInfoFromInputBox()
{
		CUIMng::Instance().m_LoginWin.GetPassInputBox()->SetText(NULL);
		CUIMng::Instance().m_OneTimePasswordWin.GetOTPInputBox()->SetText(NULL);
}
#endif //LJH_ADD_ONETIME_PASSWORD	