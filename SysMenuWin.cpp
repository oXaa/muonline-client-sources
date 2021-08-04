//*****************************************************************************
// File: SysMenuWin.cpp
//
// Desc: implementation of the CSysMenuWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "SysMenuWin.h"

#include "Input.h"
#include "UIMng.h"
#include "ZzzInfomation.h"
#include "ZzzScene.h"

// SendRequestLogOut() ����ϱ� ����.�̤�
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "wsclientinline.h"

#include "GMCryWolf1st.h"

#define	SMW_BTN_GAP		4		// ��ư �� ���� ��.

extern int  SceneFlag;
extern CWsctlc SocketClient;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysMenuWin::CSysMenuWin()
{

}

CSysMenuWin::~CSysMenuWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �ý��� �޴� â ����.
//*****************************************************************************
void CSysMenuWin::Create()
{
	CInput rInput = CInput::Instance();
	CWin::Create(rInput.GetScreenWidth(), rInput.GetScreenHeight());

// ��� ������ ����.
	SImgInfo aiiBack[WE_BG_MAX] = 
	{
		{ BITMAP_SYS_WIN, 0, 0, 128, 128 },	// �߾�
		{ BITMAP_SYS_WIN+1, 0, 0, 213, 64 },// ��
		{ BITMAP_SYS_WIN+2, 0, 0, 213, 43 },// ��
		{ BITMAP_SYS_WIN+3, 0, 0, 5, 8 },	// ��
		{ BITMAP_SYS_WIN+4, 0, 0, 5, 8 }	// ��
	};
	m_winBack.Create(aiiBack, 1, 10);

// ��ư ����.
	const char* apszBtnText[SMW_BTN_MAX] =
	{ GlobalText[381], GlobalText[382], GlobalText[385], GlobalText[388] };
	DWORD adwBtnClr[4] =
	{ CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0 };
	for (int i = 0; i < SMW_BTN_MAX; ++i)
	{
		m_aBtn[i].Create(108, 30, BITMAP_TEXT_BTN, 4, 2, 1);
		m_aBtn[i].SetText(apszBtnText[i], adwBtnClr);
		CWin::RegisterButton(&m_aBtn[i]);
	}

// ������ ��ư ���� ��� â ũ�Ⱑ �ٲ�Ƿ�.
	switch (SceneFlag)
	{
	case LOG_IN_SCENE:
		m_aBtn[SMW_BTN_SERVER_SEL].SetEnable(false);
		m_winBack.SetLine(6);
		break;
	case CHARACTER_SCENE:
		m_aBtn[SMW_BTN_SERVER_SEL].SetEnable(true);
		m_winBack.SetLine(10);
		break;
	}

	SetPosition((rInput.GetScreenWidth() - m_winBack.GetWidth()) / 2,
		(rInput.GetScreenHeight() - m_winBack.GetHeight()) / 2);
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void CSysMenuWin::PreRelease()
{
	m_winBack.Release();
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
//			   (ȭ�� �󿡴� â�� �̵��ϴ°�ó�� �������� �⺻ â�� �̵��� ����)
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void CSysMenuWin::SetPosition(int nXCoord, int nYCoord)
{
	m_winBack.SetPosition(nXCoord, nYCoord);

	// ��ư�� �׻� �߾�.
	int nBtnPosX = m_winBack.GetXPos()
		+ (m_winBack.GetWidth() - m_aBtn[0].GetWidth()) / 2;
	int nBtnGap = SMW_BTN_GAP + m_aBtn[0].GetHeight();
	// ���� ���� ��ư���� �ɼ� ��ư �� ��ư ������ ���� �������� ��ġ ��Ŵ.
	int nBtnPosBaseTop = m_winBack.GetYPos() + 33;
	for (int i = 0; i < SMW_BTN_OPTION; ++i)
		m_aBtn[i].SetPosition(nBtnPosX, nBtnPosBaseTop + i * nBtnGap);

	// �ɼ� ��ư�� �ݱ� ��ư�� ���� �������� ��ġ��Ŵ.
	int nCloseBtnPosY = m_winBack.GetYPos() + m_winBack.GetHeight() - 52;
	m_aBtn[SMW_BTN_CLOSE].SetPosition(nBtnPosX, nCloseBtnPosY);
	m_aBtn[SMW_BTN_OPTION].SetPosition(nBtnPosX, nCloseBtnPosY - nBtnGap);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CSysMenuWin::Show(bool bShow)
{
	CWin::Show(bShow);

	m_winBack.Show(bShow);
	for (int i = 0; i < SMW_BTN_MAX; ++i)
		m_aBtn[i].Show(bShow);
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool CSysMenuWin::CursorInWin(int nArea)
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
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CSysMenuWin::UpdateWhileActive()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CSysMenuWin::UpdateWhileActive(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	if (m_aBtn[SMW_BTN_GAME_END].IsClick())	// ���� ����.
	{
		CUIMng::Instance().PopUpMsgWin(MESSAGE_GAME_END_COUNTDOWN);
	}
	else if (m_aBtn[SMW_BTN_SERVER_SEL].IsClick())	// ���� ����(�α���) ������.
	{
		g_ErrorReport.Write("> Menu - Join another server.");
		g_ErrorReport.WriteCurrentTime();
		SendRequestLogOut(2);

		// �ڽŰ� ĳ���� ���þ� ����â�� ����.
		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.HideWin(this);
		rUIMng.HideWin(&rUIMng.m_CharSelMainWin);
	}
	else if (m_aBtn[SMW_BTN_OPTION].IsClick())
	{
		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.HideWin(this);
		rUIMng.ShowWin(&rUIMng.m_OptionWin);
	}
	else if (m_aBtn[SMW_BTN_CLOSE].IsClick())		// �ݱ�.
	{
		CUIMng::Instance().SetSysMenuWinShow(false);
		CUIMng::Instance().HideWin(this);
	}
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE)
		&& !CUIMng::Instance().IsSysMenuWinShow())// �ݱ�.
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		CUIMng::Instance().HideWin(this);
	}		
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void CSysMenuWin::RenderControls()
{
	m_winBack.Render();
	CWin::RenderButtons();
}
