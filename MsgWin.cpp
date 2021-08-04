//*****************************************************************************
// File: MsgWin.cpp
//
// Desc: implementation of the CMsgWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "MsgWin.h"

#include "Input.h"
#include "UIMng.h"
#include <crtdbg.h>		// _ASSERT() ���.

// �ؽ�Ʈ ������ ���� #include. �̤�
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"

#include "GOBoid.h"
#include "ZzzScene.h"
#include "DSPlaySound.h"
#include "wsclientinline.h"
#include "UIControls.h"
#include "ZzzOpenglUtil.h"
#ifdef LJH_ADD_ONETIME_PASSWORD
// web browser�� �ѱ� ���� include
	#include "iexplorer.h"
#endif //LJH_ADD_ONETIME_PASSWORD

#define	MW_OK		0	// OK ��ư, (Localized)��,Ȯ�� ��ư
#define	MW_CANCEL	1	// Cancel ��ư, (Localized)�ƴϿ�,��� ��ư

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;
extern int g_iChatInputType;
extern CUITextInputBox* g_pSinglePasswdInputBox;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgWin::CMsgWin()
{

}

CMsgWin::~CMsgWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �޽��� â ����.
//			   (�޽����� �������� �� �ϳ��� ����) 
// ���� �� ����: YES/NO ���� ������ ��� �߰�
//				  -> p_iBtnType ���� ���ų� 0(default):					OK/CANCEL ��ư�� ���� �⺻ ��ư
//				  -> p_iBtnType ���� MWT_BTN_LOCALIZED_YESNO:			(localized)��/�ƴϿ���ư (10.01.22)
//				  -> p_iBtnType ���� MWT_BTN_LOCALIZED_CONFIRM_CANCEL:	(localized)Ȯ��/��� ��ư (10.01.27)
//*****************************************************************************
#ifdef LJH_ADD_LOCALIZED_BTNS
void CMsgWin::Create(int p_iBtnType)
#else  //LJH_ADD_LOCALIZED_BTNS
void CMsgWin::Create()
#endif //LJH_ADD_LOCALIZED_BTNS
{
#ifdef LJH_ADD_LOCALIZED_BTNS
	// YES/NO ��ư ���� ��
	DWORD adwBtnColor[3] = { CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE};
#endif //LJH_ADD_LOCALIZED_BTNS

	CInput rInput = CInput::Instance();
	// �⺻ â ����.(ȭ�� ��ü ũ��. ������ ��������.)
	CWin::Create(rInput.GetScreenWidth(), rInput.GetScreenHeight());

	// â ����� ��������Ʈ.
	m_sprBack.Create(352, 113, BITMAP_MESSAGE_WIN);
	// �ؽ�Ʈ �Է� �ڽ� ��������Ʈ.
	m_sprInput.Create(171, 23, BITMAP_MSG_WIN_INPUT);

	// Ȯ��, ��� ��ư.
	// �Ǵ� ��, �ƴϿ� ��ư.
	for (int i = 0; i < 2; ++i)
	{
#ifdef LJH_ADD_LOCALIZED_BTNS
		if (p_iBtnType == 0)
			m_aBtn[i].Create(54, 30, BITMAP_BUTTON + i, 3, 2, 1);
		else if (p_iBtnType == MWT_BTN_LOCALIZED_YESNO)
		{
			m_aBtn[i].Create(64, 29, SEASON3B::CNewUIMessageBoxMng::IMAGE_MSGBOX_BTN_EMPTY_SMALL, 3, 2, 1);
			m_aBtn[i].SetText(GlobalText[1037+i], adwBtnColor);
		}
		else if (p_iBtnType == MWT_BTN_LOCALIZED_CONFIRM_CANCEL || p_iBtnType == MWT_BTN_LOCALIZED_CONFIRM_ONLY)
		{
			m_aBtn[i].Create(64, 29, SEASON3B::CNewUIMessageBoxMng::IMAGE_MSGBOX_BTN_EMPTY_SMALL, 3, 2, 1);
			m_aBtn[i].SetText(GlobalText[228+i*2886], adwBtnColor);
		}
#else  //LJH_ADD_LOCALIZED_BTNS
		m_aBtn[i].Create(54, 30, BITMAP_BUTTON + i, 3, 2, 1);
#endif //LJH_ADD_LOCALIZED_BTNS
		CWin::RegisterButton(&m_aBtn[i]);
	}

	::memset(m_aszMsg[0], 0 ,sizeof(char) * MW_MSG_LINE_MAX * MW_MSG_ROW_MAX);

	m_eType = MWT_NON;
	m_nMsgLine = 0;
	m_nMsgCode = -1;
	m_nGameExit = -1;
	m_dDeltaTickSum = 0.0;
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void CMsgWin::PreRelease()
{
	m_sprInput.Release();
	m_sprBack.Release();
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
//			   (ȭ�� �󿡴� â�� �̵��ϴ°�ó�� �������� �⺻ â�� �̵��� ����)
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void CMsgWin::SetPosition(int nXCoord, int nYCoord)
{
	m_sprBack.SetPosition(nXCoord, nYCoord);
	SetCtrlPosition();
}

//*****************************************************************************
// �Լ� �̸� : SetCtrlPosition()
// �Լ� ���� : ��Ʈ�� ��ġ ����.
//*****************************************************************************
void CMsgWin::SetCtrlPosition()
{
	int nBaseXPos = m_sprBack.GetXPos();
	int nBtnYPos = m_sprBack.GetYPos() + 72;
// �޽��� �ڽ� Ÿ�ٿ� ���� ��Ʈ�� ��ġ�� ����.
	switch (m_eType)
	{
	case MWT_BTN_CANCEL:
		m_aBtn[MW_CANCEL].SetPosition(nBaseXPos + 149, nBtnYPos);
		break;
	case MWT_BTN_OK:
#ifdef LJH_ADD_LOCALIZED_BTNS
	case MWT_BTN_LOCALIZED_CONFIRM_ONLY:
#endif //LJH_ADD_LOCALIZED_BTNS
		m_aBtn[MW_OK].SetPosition(nBaseXPos + 149, nBtnYPos);
		break;
	case MWT_BTN_BOTH:
#ifdef LJH_ADD_LOCALIZED_BTNS
	case MWT_BTN_LOCALIZED_YESNO:
	case MWT_BTN_LOCALIZED_CONFIRM_CANCEL:
#endif //LJH_ADD_LOCALIZED_BTNS
		m_aBtn[MW_OK].SetPosition(nBaseXPos + 98, nBtnYPos);
		m_aBtn[MW_CANCEL].SetPosition(nBaseXPos + 200, nBtnYPos);
		break;
	case MWT_STR_INPUT:
		m_sprInput.SetPosition(nBaseXPos + 32, nBtnYPos + 4);
		m_aBtn[MW_OK].SetPosition(nBaseXPos + 209, nBtnYPos);
		m_aBtn[MW_CANCEL].SetPosition(nBaseXPos + 264, nBtnYPos);
		// �Է� �ؽ�Ʈ ��ġ ����.
		if (m_nMsgCode == MESSAGE_DELETE_CHARACTER_RESIDENT)
			if (g_iChatInputType == 1)
				g_pSinglePasswdInputBox->SetPosition(
					int((m_sprInput.GetXPos() + 10) / g_fScreenRate_x),
					int((m_sprInput.GetYPos() + 8) / g_fScreenRate_y));
		break;
	}
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CMsgWin::Show(bool bShow)
{
	CWin::Show(bShow);

	m_sprBack.Show(bShow);

	switch (m_eType)
	{
	case MWT_BTN_CANCEL:
		m_aBtn[MW_OK].Show(false);
		m_aBtn[MW_CANCEL].Show(bShow);
		m_sprInput.Show(false);
		break;
	case MWT_BTN_OK:
#ifdef LJH_ADD_LOCALIZED_BTNS
	case MWT_BTN_LOCALIZED_CONFIRM_ONLY:
#endif //LJH_ADD_LOCALIZED_BTNS
		m_aBtn[MW_OK].Show(bShow);
		m_aBtn[MW_CANCEL].Show(false);
		m_sprInput.Show(false);
		break;
	case MWT_BTN_BOTH:
#ifdef LJH_ADD_LOCALIZED_BTNS
	case MWT_BTN_LOCALIZED_YESNO:
	case MWT_BTN_LOCALIZED_CONFIRM_CANCEL:
#endif //LJH_ADD_LOCALIZED_BTNS
		m_aBtn[MW_OK].Show(bShow);
		m_aBtn[MW_CANCEL].Show(bShow);
		m_sprInput.Show(false);
		break;
	case MWT_STR_INPUT:
		m_aBtn[MW_OK].Show(bShow);
		m_aBtn[MW_CANCEL].Show(bShow);
		m_sprInput.Show(bShow);
		break;
	default:
		m_aBtn[MW_OK].Show(false);
		m_aBtn[MW_CANCEL].Show(false);
		m_sprInput.Show(false);
	}
		
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool CMsgWin::CursorInWin(int nArea)
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
// �Լ� �̸� : UpdateWhileActive()
// �Լ� ���� : ��Ƽ���� ���� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void CMsgWin::UpdateWhileActive(double dDeltaTick)
{
	CInput& rInput = CInput::Instance();

	if (rInput.IsKeyDown(VK_RETURN))	// ����Ű�� �����°�?
	{
		if (m_eType > MWT_BTN_CANCEL)	// OK ��ư�� ����ϰ� �ִٸ�.
		{
			::PlayBuffer(SOUND_CLICK01);// Ŭ�� ����.
			ManageOKClick();
		}
		else if (m_eType == MWT_BTN_CANCEL)	// Cancel ��ư�� �ִٸ�.
		{
			::PlayBuffer(SOUND_CLICK01);// Ŭ�� ����.
			ManageCancelClick();
		}
	}
	else if (rInput.IsKeyDown(VK_ESCAPE))// escŰ�� �����°�?
	{
#ifdef LJH_ADD_LOCALIZED_BTNS
		if (m_eType == MWT_BTN_OK  || m_eType == MWT_BTN_LOCALIZED_CONFIRM_ONLY) // OK ��ư, Ȥ�� Ȯ�ι�ư�� �ִٸ�.
#else  //LJH_ADD_LOCALIZED_BTNS
		if (m_eType == MWT_BTN_OK)		// OK ��ư�� �ִٸ�.
#endif //LJH_ADD_LOCALIZED_BTNS
		{
			::PlayBuffer(SOUND_CLICK01);// Ŭ�� ����.
			ManageOKClick();
		}
		else if (m_eType > MWT_NON)		// Cancel��ư�� ����ϰ� �ִٸ�.
		{
			::PlayBuffer(SOUND_CLICK01);// Ŭ�� ����.
			ManageCancelClick();
		}
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
	else if (m_aBtn[MW_OK].IsClick())		// OK ��ư�� Ŭ���ߴ°�?
		ManageOKClick();
	else if (m_aBtn[MW_CANCEL].IsClick())	// Cancel ��ư�� Ŭ���ߴ°�?
		ManageCancelClick();
	else if (m_nMsgCode == MESSAGE_GAME_END_COUNTDOWN)	// �������� ī��Ʈ.
	{
		if (m_nGameExit != -1) 
		{
			m_dDeltaTickSum += dDeltaTick;
			if (m_dDeltaTickSum > 1000.0)
			{
				m_dDeltaTickSum = 0.0;
				if (--m_nGameExit == 0)
				{
					g_ErrorReport.Write("> Menu - Exit game.");
					g_ErrorReport.WriteCurrentTime();
	//				SocketClient.Close();	// ������ WM_DESTROY���� ȣ�� ��.
					::PostMessage(g_hWnd, WM_CLOSE, 0, 0);
				}
				else
				{
					char szMsg[64];
					::sprintf(szMsg, GlobalText[380], m_nGameExit);
					SetMsg(m_eType, szMsg);
				}
			}
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void CMsgWin::RenderControls()
{
	m_sprBack.Render();			// â ����� ��������Ʈ.

	int nTextPosX, nTextPosY;

	// �ؽ�Ʈ ���� ����.
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->SetBgColor(0);

	if (1 == m_nMsgLine)		// �޽����� 1���϶�.
	{
		nTextPosX = int(m_sprBack.GetXPos() / g_fScreenRate_x);
		if (MWT_NON != m_eType)	// ��ư�� �ִٸ�.
			nTextPosY = int((m_sprBack.GetYPos() + 38) / g_fScreenRate_y);
		else
			nTextPosY = int((m_sprBack.GetYPos() + 54) / g_fScreenRate_y);
		g_pRenderText->RenderText(nTextPosX, nTextPosY, m_aszMsg[0],
			m_sprBack.GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);
	}
	else if (2 == m_nMsgLine)	// �޽����� 2���϶�.
	{
		nTextPosX = int((m_sprBack.GetXPos() + 25) / g_fScreenRate_x);
		if (MWT_NON != m_eType)	// ��ư�� �ִٸ�.
			nTextPosY = int((m_sprBack.GetYPos() + 32) / g_fScreenRate_y);
		else
			nTextPosY = int((m_sprBack.GetYPos() + 44) / g_fScreenRate_y);
		g_pRenderText->RenderText(nTextPosX, nTextPosY, m_aszMsg[0]);

		if (MWT_NON != m_eType)	// ��ư�� �ִٸ�.
			nTextPosY = int((m_sprBack.GetYPos() + 51) / g_fScreenRate_y);
		else
			nTextPosY = int((m_sprBack.GetYPos() + 66) / g_fScreenRate_y);
		g_pRenderText->RenderText(nTextPosX, nTextPosY, m_aszMsg[1]);
	}

	m_sprInput.Render();		// �ؽ�Ʈ �Է� �ڽ� ��������Ʈ.
	// �ؽ�Ʈ �Է� ó��.
	if (m_nMsgCode == MESSAGE_DELETE_CHARACTER_RESIDENT)
	{
		if (g_iChatInputType == 1)
			g_pSinglePasswdInputBox->Render();
		else if (g_iChatInputType == 0)
		{
			InputTextWidth = 100;
			::RenderInputText(
				int((m_sprInput.GetXPos() + 10) / g_fScreenRate_x),
				int((m_sprInput.GetYPos() + 8) / g_fScreenRate_y), 0, 0);
			InputTextWidth = 256;
		}
	}

	CWin::RenderButtons();
}

//*****************************************************************************
// �Լ� �̸� : SetMsg()
// �Լ� ���� : �޽����� ��ư ����.
// �Ű� ���� : eType	: �޽��� ������ Ÿ��.
//			   lpszMsg	: �޽��� ���ڿ�.
//			   lpszMsg2	: �޽��� ���ڿ� 2��° ����.(�⺻�� NULL)
// lpszMsg�� �ִ� ��� �ڵ����� ���� ������ �Է� �ǰ�, lpszMsg2�� ������ ù°
//�ٿ� lpszMsg�� ��° �ٿ��� lpszMsg2�� �Է� �ȴ�.
//*****************************************************************************
void CMsgWin::SetMsg(MSG_WIN_TYPE eType, LPCTSTR lpszMsg, LPCTSTR lpszMsg2)
{
	_ASSERT(lpszMsg);

	m_eType = eType;

	SetCtrlPosition();	// m_eType�� ���� ��Ʈ�� ��ġ�� ���ϹǷ�.

	if (NULL == lpszMsg2)
	{
		// �ڵ����� ���� ����.
		m_nMsgLine = ::SeparateTextIntoLines(
			(char*)lpszMsg, m_aszMsg[0], MW_MSG_LINE_MAX, MW_MSG_ROW_MAX);
	}
	else
	{
		::strcpy(m_aszMsg[0], lpszMsg);
		::strcpy(m_aszMsg[1], lpszMsg2);

		m_nMsgLine = 2;
	}
}

//*****************************************************************************
// �Լ� �̸� : PopUp()
// �Լ� ���� : �޽��� �ڵ忡 �°� â�� ���.
// �Ű� ���� : nMsgCode	: �޽��� �ڵ�.
//*****************************************************************************
void CMsgWin::PopUp(int nMsgCode, char* pszMsg)
{
	CUIMng& rUIMng = CUIMng::Instance();
	LPCTSTR lpszMsg = NULL, lpszMsg2 = NULL;
	MSG_WIN_TYPE eType = MWT_BTN_OK;
	m_nMsgCode = nMsgCode;
	char szTempMsg[128];

	switch (m_nMsgCode)
	{
	case MESSAGE_FREE_MSG_NOT_BTN:			// �����ο� �޽���, ��ư ����.(����, ĳ���� ������ ���� ������ ī��Ʈ�ٿ� �� ���)
		lpszMsg = pszMsg;
		eType = MWT_NON;
		break;
	case MESSAGE_GAME_END_COUNTDOWN:		// ���� ���� ī��Ʈ �ٿ�.
		m_nGameExit = 5;
		::sprintf(szTempMsg, GlobalText[380], m_nGameExit);
		lpszMsg = szTempMsg;
		eType = MWT_NON;
		break;
	case MESSAGE_WAIT:						// ��ø� ��ٷ� �ּ���.
		lpszMsg = GlobalText[471];
		eType = MWT_NON;
		break;
	case MESSAGE_SERVER_BUSY:				// ���� ������ ��ȭ ����.
	case RECEIVE_LOG_IN_FAIL_SERVER_BUSY:	// ���� ������ ��ȭ ����.
		lpszMsg = GlobalText[416];
		break;
	case RECEIVE_JOIN_SERVER_WAITING:		// ���������� �ٻ�.(���� ��� ����.)
		rUIMng.ShowWin(&rUIMng.m_ServerSelWin);
		lpszMsg = GlobalText[416];
		break;
	case MESSAGE_SERVER_LOST:				// ���� ���� ����.
		lpszMsg = GlobalText[402];
		break;
	case MESSAGE_VERSION:					// ������ Ʋ��.
	case RECEIVE_LOG_IN_FAIL_VERSION:		// ������ Ʋ��.
		lpszMsg = GlobalText[405];
		lpszMsg2 = GlobalText[406];
		break;
	case MESSAGE_INPUT_ID:					// ���� �Է� ����.
		lpszMsg = GlobalText[403];
		break;
	case MESSAGE_INPUT_PASSWORD:			// ��ȣ �Է� ����.
		lpszMsg = GlobalText[404];
		break;
	case RECEIVE_LOG_IN_FAIL_ID:			// ���� Ʋ��.
		lpszMsg = GlobalText[414];
		break;
	case RECEIVE_LOG_IN_FAIL_PASSWORD:		// ��ȣ Ʋ��.
		lpszMsg = GlobalText[407];
		break;
	case RECEIVE_LOG_IN_FAIL_ID_CONNECTED:	// �������� ������.
		lpszMsg = GlobalText[415];
		break;
	case RECEIVE_LOG_IN_FAIL_ID_BLOCK:		// ���� ������.
	case MESSAGE_DELETE_CHARACTER_ID_BLOCK:	// ���� ������.
		lpszMsg = GlobalText[417];
		break;
	case RECEIVE_LOG_IN_FAIL_CONNECT:		// ���� ����.
		lpszMsg = GlobalText[408];
		break;
	case RECEIVE_LOG_IN_FAIL_ERROR:			// �α��� �Է� 3�� Ʋ��.
		lpszMsg = GlobalText[409];
		break;
	case RECEIVE_LOG_IN_FAIL_NO_PAYMENT_INFO:// �������� ����.
		lpszMsg = GlobalText[433];
		break;
	case RECEIVE_LOG_IN_FAIL_USER_TIME1:	// ���� ���� �ð� ����.
		lpszMsg = GlobalText[410];
		break;
	case RECEIVE_LOG_IN_FAIL_USER_TIME2:	// ���� ���� �ð� ����.
		lpszMsg = GlobalText[411];
		break;
	case RECEIVE_LOG_IN_FAIL_PC_TIME1:		// IP ���� �ð� ����.
		lpszMsg = GlobalText[412];
		break;
	case RECEIVE_LOG_IN_FAIL_PC_TIME2:		// IP ���� �ð� ����.
		lpszMsg = GlobalText[413];
		break;
	case RECEIVE_LOG_IN_FAIL_ONLY_OVER_15:	// 15�� �̻� �̿밡 ����.
		lpszMsg = GlobalText[435];
		break;
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	case RECEIVE_LOG_IN_FAIL_CHARGED_CHANNEL:// ����ä�� ���� �Ұ�. (�۷ι� ����)
		lpszMsg = GlobalText[3118];
		break;
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
	case RECEIVE_LOG_IN_FAIL_POINT_DATE:	// ����Ʈ ��¥�� ���Ⱓ ����. (�븸 ����)
		lpszMsg = GlobalText[597];
		break;
	case RECEIVE_LOG_IN_FAIL_POINT_HOUR:	// ����Ʈ �ð��� ���Ⱓ ����. (�븸 ����)
		lpszMsg = GlobalText[598];
		break;
	case RECEIVE_LOG_IN_FAIL_INVALID_IP:	// ���� �㰡���� ���� IP. (�븸 ����)
		lpszMsg = GlobalText[599];
		break;
	case MESSAGE_DELETE_CHARACTER_GUILDWARNING:// ��忡 ���Ե� ĳ���� ���� �Ұ�.
		lpszMsg = GlobalText[1654];
		break;
	case MESSAGE_DELETE_CHARACTER_WARNING:	// ���� ���� �̻� ���� �Ұ�.
//		lpszMsg = GlobalText[1711];
		::sprintf(szTempMsg, GlobalText[1711], CHAR_DEL_LIMIT_LV);
		lpszMsg = szTempMsg;
		break;
	case MESSAGE_DELETE_CHARACTER_CONFIRM:	// ĳ���͸� �����Ͻðڽ��ϱ�?
		::sprintf(szTempMsg, GlobalText[1712], CharactersClient[SelectedHero].ID);
		lpszMsg = szTempMsg;
		eType = MWT_BTN_BOTH;
		break;
	case MESSAGE_DELETE_CHARACTER_RESIDENT:	// �ֹε�� ��ȣ ���ڸ� �Է�.
		lpszMsg = GlobalText[1713];
		eType = MWT_STR_INPUT;
		InitResidentNumInput();	// �Է� �κ� �ʱ�ȭ.		
		break;
	case MESSAGE_DELETE_CHARACTER_ITEM_BLOCK:// ������ ���� ĳ����.
		lpszMsg = GlobalText[439];
		break;
	case MESSAGE_STORAGE_RESIDENTWRONG:		// �ֹε�Ϲ�ȣ ����ġ.
		lpszMsg = GlobalText[401];
		break;
	case MESSAGE_DELETE_CHARACTER_SUCCESS:	// ĳ���� ���� ����.
		CharactersClient[SelectedHero].Object.Live = false;	// ĳ���� ����.
		DeleteBug(&CharactersClient[SelectedHero].Object);	// ���ϸ���, ����Ʈ, �渱�� ����
		SelectedHero = -1;
		rUIMng.m_CharSelMainWin.UpdateDisplay();
		rUIMng.m_CharInfoBalloonMng.UpdateDisplay();
		lpszMsg = GlobalText[1714];
		break;
	case MESSAGE_BLOCKED_CHARACTER:			// ���� ĳ����.
		lpszMsg = GlobalText[434];
		break;
	case MESSAGE_MIN_LENGTH:				// �Էµ� ���ڼ��� ����.
		lpszMsg = GlobalText[390];
		break;
	case MESSAGE_ID_SPACE_ERROR:			// ����� �� ���� �ܾ ����.
		lpszMsg = GlobalText[1715];
		break;
	case MESSAGE_SPECIAL_NAME:				// Ư������ ��� �Ұ�.
		lpszMsg = GlobalText[391];
		break;
	case RECEIVE_CREATE_CHARACTER_FAIL:		// ������ �̸� ����.
		rUIMng.ShowWin(&rUIMng.m_CharMakeWin);
#ifdef PJH_CHARACTER_RENAME
		rUIMng.m_CharMakeWin.Set_State(rUIMng.m_CharMakeWin.ReName_Inter);
#endif //PJH_CHARACTER_RENAME

		lpszMsg = GlobalText[1716];
		break;
	case RECEIVE_CREATE_CHARACTER_FAIL2:	// ĳ���͸� �� ���� �� ����.
		rUIMng.ShowWin(&rUIMng.m_CharMakeWin);
#ifdef PJH_CHARACTER_RENAME
		rUIMng.m_CharMakeWin.Set_State();
#endif //PJH_CHARACTER_RENAME

		lpszMsg = GlobalText[396];
		break;
#ifdef ADD_EXPERIENCE_SERVER
	case MESSAGE_PCROOM_POSSIBLE:			// PC�濡���� ���� ����.
		lpszMsg = GlobalText[1698];
		break;
#endif	// ADD_EXPERIENCE_SERVER
		
#ifdef LDK_ADD_GLOBAL_PORTAL_SYSTEM
	case MESSAGE_NOT_EXECUTION_WEBSTARTER:	// ������ �α������ּ���. (����Ÿ�� �̽���)
#ifdef ASG_FIX_NOT_EXECUTION_WEBSTARTER_MSG
		lpszMsg = GlobalText[3117];
#else	// ASG_FIX_NOT_EXECUTION_WEBSTARTER_MSG
		lpszMsg = GlobalText[2743];
#endif	// ASG_FIX_NOT_EXECUTION_WEBSTARTER_MSG
		break;
#endif //LDK_ADD_GLOBAL_PORTAL_SYSTEM
#ifdef LJH_ADD_ONETIME_PASSWORD
	case MESSAGE_OTP_NOT_REGISTERED:		// OneTime Password �̵��
		lpszMsg = GlobalText[3108];			// "���� ������ ��Ÿ�� �н������� �̿��� ��õ�մϴ�."
		lpszMsg2 = GlobalText[3109];		// "���� �ٷ� ��Ÿ�� �н����带 ����Ͻðڽ��ϱ�?"
		eType = MWT_BTN_LOCALIZED_YESNO;
		break;
	case MESSAGE_OTP_INCORRECT:				// OneTime Password ����ġ 
		lpszMsg = GlobalText[3111];			// "��Ÿ�� �н����尡 ��ġ���� �ʽ��ϴ�."
		lpszMsg2 = GlobalText[3112];		// "�ٽ� �ѹ� Ȯ�ιٶ��ϴ�."
		break;
	case MESSAGE_OTP_NOT_WRITTEN:			// OneTime Password�� �Է����� �ʰ� ok Ŭ��
		lpszMsg = GlobalText[3111];			// "��Ÿ�� �н����尡 ��ġ���� �ʽ��ϴ�."
		lpszMsg2 = GlobalText[3112];		// "�ٽ� �ѹ� Ȯ�ιٶ��ϴ�."
		break;
	case MESSAGE_OTP_INVALID_INFO:
		lpszMsg = GlobalText[3113];			// "�Է� ������ ���������� �ʽ��ϴ�."
		lpszMsg2 = GlobalText[3112];		// "�ٽ� �ѹ� Ȯ�ιٶ��ϴ�."
		eType = MWT_BTN_LOCALIZED_CONFIRM_ONLY;
		break;
#endif //LJH_ADD_ONETIME_PASSWORD

	default:
		m_nMsgCode = -1;
		return;
	}

	SetMsg(eType, lpszMsg, lpszMsg2);		// �޽����� ��ư ����.
	rUIMng.ShowWin(this);
}

//*****************************************************************************
// �Լ� �̸� : ManageOKClick()
// �Լ� ���� : Ȯ�� ��ư�� Ŭ������ ���� ó��.
//*****************************************************************************
void CMsgWin::ManageOKClick()
{
	CUIMng& rUIMng = CUIMng::Instance();
	rUIMng.HideWin(this);

	switch (m_nMsgCode)
	{
	case MESSAGE_SERVER_LOST:				// ���� ���� ����.
	case MESSAGE_VERSION:					// ������ Ʋ��.
	case RECEIVE_LOG_IN_FAIL_ERROR:			// ���� 3�� Ʋ��.
	case RECEIVE_LOG_IN_FAIL_VERSION:		// ������ Ʋ��.
#ifdef LDK_ADD_GLOBAL_PORTAL_SYSTEM
	case MESSAGE_NOT_EXECUTION_WEBSTARTER:	// ������ �α������ּ���. (����Ÿ�� �̽���)
#endif //LDK_ADD_GLOBAL_PORTAL_SYSTEM
		::PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		break;
	case MESSAGE_INPUT_ID:					// ���� �Է� ����.
	case RECEIVE_LOG_IN_FAIL_ID:			// ���� Ʋ��.
	case RECEIVE_LOG_IN_FAIL_ID_CONNECTED:	// ���� ���� ������.
	case RECEIVE_LOG_IN_FAIL_SERVER_BUSY:	// ���� ������ ��ȭ ����.
	case RECEIVE_LOG_IN_FAIL_ID_BLOCK:		// ���� ������.
	case RECEIVE_LOG_IN_FAIL_CONNECT:		// ���� ����.
	case RECEIVE_LOG_IN_FAIL_NO_PAYMENT_INFO:// �������� ����.
	case RECEIVE_LOG_IN_FAIL_USER_TIME1:	// ���� ���� �ð� ����.
	case RECEIVE_LOG_IN_FAIL_USER_TIME2:	// ���� ���� �ð� ����.
	case RECEIVE_LOG_IN_FAIL_PC_TIME1:		// IP ���� �ð� ����.
	case RECEIVE_LOG_IN_FAIL_PC_TIME2:		// IP ���� �ð� ����.
	case RECEIVE_LOG_IN_FAIL_ONLY_OVER_15:	// 15�� �̻� �̿밡 ����.
	case RECEIVE_LOG_IN_FAIL_POINT_DATE:	// ����Ʈ ��¥�� ���Ⱓ ����.
	case RECEIVE_LOG_IN_FAIL_POINT_HOUR:	// ����Ʈ �ð��� ���Ⱓ ����.
	case RECEIVE_LOG_IN_FAIL_INVALID_IP:	// ���� �㰡���� ���� IP.
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	case RECEIVE_LOG_IN_FAIL_CHARGED_CHANNEL:// ����ä�� ���� �Ұ�. (�۷ι� ����)
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
		rUIMng.ShowWin(&rUIMng.m_LoginWin);
		CUIMng::Instance().m_LoginWin.GetIDInputBox()->GiveFocus(TRUE);
		CurrentProtocolState = RECEIVE_JOIN_SERVER_SUCCESS;
		break;
	case MESSAGE_INPUT_PASSWORD:			// ��ȣ �Է� ����.
	case RECEIVE_LOG_IN_FAIL_PASSWORD:		// ��ȣ Ʋ��.
		rUIMng.ShowWin(&rUIMng.m_LoginWin);
		CUIMng::Instance().m_LoginWin.GetPassInputBox()->GiveFocus(TRUE);
		CurrentProtocolState = RECEIVE_JOIN_SERVER_SUCCESS;
		break;
#ifdef ADD_EXPERIENCE_SERVER
	case MESSAGE_PCROOM_POSSIBLE:			// PC�濡���� ���� ����.
		CUIMng::Instance().m_LoginWin.ConnectConnectionServer();
		break;
#endif	// ADD_EXPERIENCE_SERVER
	case MESSAGE_DELETE_CHARACTER_CONFIRM:	// ĳ���͸� �����Ͻðڽ��ϱ�?
		PopUp(MESSAGE_DELETE_CHARACTER_RESIDENT);
		break;
	case MESSAGE_DELETE_CHARACTER_RESIDENT:	// �ֹε�� ��ȣ ���ڸ� �Է�.
		RequestDeleteCharacter();
		PopUp(MESSAGE_WAIT);
		break;
#ifdef LJH_ADD_ONETIME_PASSWORD
	case MESSAGE_OTP_NOT_REGISTERED:
		// OneTime Password�� ��� �� �� �ְ� 
		// �⺻���� �����Ǿ� �ִ� web browser�� �Ѱ� 
		//ä�� ����â���� ���ư���.
		leaf::OpenExplorer("https://secure.muonline.jp/member/otk/index.asp");
		ReturnToConnServerWin();
		break;
	case MESSAGE_OTP_INCORRECT:				// OneTime Password�� Ʋ��.
	case MESSAGE_OTP_NOT_WRITTEN:			// OneTime Password�� �Է����� ����.
		rUIMng.ShowWin(&rUIMng.m_OneTimePasswordWin);
		CUIMng::Instance().m_OneTimePasswordWin.GetOTPInputBox()->SetText(NULL);
		CUIMng::Instance().m_OneTimePasswordWin.GetOTPInputBox()->GiveFocus(TRUE);
		break;
	case MESSAGE_OTP_INVALID_INFO:
		ReturnToConnServerWin();
		break;
#endif //LJH_ADD_ONETIME_PASSWORD
	}
}

//*****************************************************************************
// �Լ� �̸� : ManageCancelClick()
// �Լ� ���� : ��� ��ư�� Ŭ������ ���� ó��.
//*****************************************************************************
void CMsgWin::ManageCancelClick()
{
	CUIMng& rUIMng = CUIMng::Instance();

#ifdef LJH_ADD_ONETIME_PASSWORD
	switch (m_nMsgCode)
	{
		// ������ OneTime Password����� �����Ͽ��� ������ �׳� �α��� 
		case MESSAGE_OTP_NOT_REGISTERED:
			SendingLoginInfoWOOPT();
			break;
	}
#endif //LJH_ADD_ONETIME_PASSWORD

	m_nMsgCode = -1;
	rUIMng.HideWin(this);
}

//*****************************************************************************
// �Լ� �̸� : InitResidentNumInput()
// �Լ� ���� : �ֹε�Ϲ�ȣ �Է� �ʱ�ȭ.
//*****************************************************************************
void CMsgWin::InitResidentNumInput()
{
	::ClearInput();
	InputEnable = true;
	InputNumber = 1;
	InputTextMax[0] = g_iLengthAuthorityCode;
	InputTextHide[0] = 1;

	if (g_iChatInputType == 1)
	{
		g_pSinglePasswdInputBox->SetState(UISTATE_NORMAL);

#ifdef KJH_MOD_NATION_LANGUAGE_REDEFINE
	g_pSinglePasswdInputBox->SetBackColor(0, 0, 0, 0);
	
//----------------------------------------------------------------------------- Kor
// Kor
#ifdef _LANGUAGE_KOR
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
	g_pSinglePasswdInputBox->SetTextLimit(7);

//----------------------------------------------------------------------------- Eng
// Eng
#elif _LANGUAGE_ENG
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NULL);
#ifdef LDK_MOD_PASSWORD_LENGTH_20
	g_pSinglePasswdInputBox->SetTextLimit(10);
#else // LDK_MOD_PASSWORD_LENGTH_20
	g_pSinglePasswdInputBox->SetTextLimit(7);
#endif // LDK_MOD_PASSWORD_LENGTH_20

//----------------------------------------------------------------------------- Tai
// Tai
#elif _LANGUAGE_TAI
	g_pSinglePasswdInputBox->SetOption(UIOPTION_SERIALNUMBER);
	g_pSinglePasswdInputBox->SetTextLimit(10);

//----------------------------------------------------------------------------- Chs
// Chs
#elif _LANGUAGE_CHS
	g_pSinglePasswdInputBox->SetOption(UIOPTION_SERIALNUMBER);
	g_pSinglePasswdInputBox->SetTextLimit(7);

//----------------------------------------------------------------------------- Jpn
// Jpn
#elif _LANGUAGE_JPN
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
	g_pSinglePasswdInputBox->SetTextLimit(8);

//----------------------------------------------------------------------------- Tha
// Tha
#elif _LANGUAGE_THA
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
	g_pSinglePasswdInputBox->SetTextLimit(7);

//----------------------------------------------------------------------------- Phi
// Phi
#elif _LANGUAGE_PHI
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
	g_pSinglePasswdInputBox->SetTextLimit(7);

//----------------------------------------------------------------------------- Vie
// Vie
#elif _LANGUAGE_VIE
	g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
	g_pSinglePasswdInputBox->SetTextLimit(7);

#endif
//-----------------------------------------------------------------------------

#else // KJH_MOD_NATION_LANGUAGE_REDEFINE
#if (SELECTED_LANGUAGE == LANGUAGE_TAIWANESE) || ( SELECTED_LANGUAGE==LANGUAGE_CHINESE )
		// �븸, �߱�
		g_pSinglePasswdInputBox->SetOption(UIOPTION_SERIALNUMBER);
#elif ( SELECTED_LANGUAGE == LANGUAGE_ENGLISH )
		// �̱�
		g_pSinglePasswdInputBox->SetOption(UIOPTION_NULL);
#else // (SELECTED_LANGUAGE == LANGUAGE_TAIWANESE) || ( SELECTED_LANGUAGE==LANGUAGE_CHINESE )
		// �ѱ�
		g_pSinglePasswdInputBox->SetOption(UIOPTION_NUMBERONLY);
#endif // (SELECTED_LANGUAGE == LANGUAGE_TAIWANESE) || ( SELECTED_LANGUAGE==LANGUAGE_CHINESE )

		g_pSinglePasswdInputBox->SetBackColor(0, 0, 0, 0);

#if (SELECTED_LANGUAGE == LANGUAGE_JAPANESE)
		// �Ϻ�
		g_pSinglePasswdInputBox->SetTextLimit(8);
#elif (SELECTED_LANGUAGE == LANGUAGE_TAIWANESE)
		// �븸
		g_pSinglePasswdInputBox->SetTextLimit(10);

#elif defined( LDK_MOD_PASSWORD_LENGTH_20 ) && ( SELECTED_LANGUAGE == LANGUAGE_ENGLISH )
		// �̱�
		g_pSinglePasswdInputBox->SetTextLimit(20);
#else // (SELECTED_LANGUAGE == LANGUAGE_JAPANESE)
		// �ѱ�
		g_pSinglePasswdInputBox->SetTextLimit(7);
#endif	// (SELECTED_LANGUAGE == LANGUAGE_JAPANESE)
#endif // KJH_MOD_NATION_LANGUAGE_REDEFINE

		g_pSinglePasswdInputBox->GiveFocus();
	}
}

//*****************************************************************************
// �Լ� �̸� : RequestDeleteCharacter()
// �Լ� ���� : ĳ���� ���� ��û.
//*****************************************************************************
void CMsgWin::RequestDeleteCharacter()
{
	if (g_iChatInputType == 1)
	{
		g_pSinglePasswdInputBox->GetText(InputText[0]);
		g_pSinglePasswdInputBox->SetText(NULL);
		g_pSinglePasswdInputBox->SetState(UISTATE_HIDE);
	}
	InputEnable = false;
	SendRequestDeleteCharacter(CharactersClient[SelectedHero].ID, InputText[0]);
}

#ifdef LJH_ADD_ONETIME_PASSWORD
//*****************************************************************************
// �Լ� �̸� :	ReturnToConnServerWin()
// �Լ� ���� :	OPT �̵�� ������ ���(YES)��ư�� Ŭ��.
//				���� ���� ������ ���� ���� ������ �ٽ� ����.
//*****************************************************************************
void CMsgWin::ReturnToConnServerWin()
{
	SocketClient.Close();		// ���� ���� ������ ����.
	LogIn = 0;
	CurrentProtocolState = REQUEST_JOIN_SERVER;

	// ���� ������ �ٽ� ����.
    ::CreateSocket(szServerIpAddress, g_ServerPort);

	ClearLoginInfoFromInputBox();
}

//*****************************************************************************
// �Լ� �̸� : SendingLoginInfoWOOPT()
// �Լ� ���� : ������ �α��ο� �ʿ��� ������ ���� W/O OneTime Password.
//*****************************************************************************
void CMsgWin::SendingLoginInfoWOOPT()
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
	
		SendRequestOTP(szID, szPW, szOTP, 0x02);
	}
}

//*****************************************************************************
// �Լ� �̸� : ClearLoginInfoFromInputBox()
// �Լ� ���� : for better security, remove the password and OneTime Password from the inputbox.
//*****************************************************************************
void CMsgWin::ClearLoginInfoFromInputBox()
{
		CUIMng::Instance().m_LoginWin.GetPassInputBox()->SetText(NULL);
		CUIMng::Instance().m_OneTimePasswordWin.GetOTPInputBox()->SetText(NULL);
}
#endif //LJH_ADD_ONETIME_PASSWORD