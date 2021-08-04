//*****************************************************************************
// File: LoginMainWin.cpp
//
// Desc: implementation of the CLoginMainWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "LoginMainWin.h"

#include "Input.h"
#include "UIMng.h"

// ::PlayBuffer(SOUND_CLICK01) Ŭ�� ���� ������ �Ʒ� Include �̤�.
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "DSPlaySound.h"

// SendRequestServerList() ������ Include.
#include "ZzzCharacter.h"
#include "wsclientinline.h"

#ifdef MOVIE_DIRECTSHOW
#include <dshow.h>
#include "MovieScene.h"

extern CMovieScene* g_pMovieScene;
#endif // MOVIE_DIRECTSHOW

extern char* g_lpszMp3[NUM_MUSIC];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginMainWin::CLoginMainWin()
{

}

CLoginMainWin::~CLoginMainWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �α��ξ� ���� â ����.
//*****************************************************************************
// ��ư�� ����� ��.
void CLoginMainWin::Create()
{
	// ��ư ����.
	for (int i = 0; i <= LMW_BTN_CREDIT; ++i)
		m_aBtn[i].Create(54, 30, BITMAP_LOG_IN+4 + i, 3, 2, 1);
#ifdef MOVIE_DIRECTSHOW
	m_aBtn[LMW_BTN_MOVIE].Create(54, 30, BITMAP_LOG_IN+15, 3, 2, 1);
#endif	// MOVIE_DIRECTSHOW

	// ���� ������ ����.
	CWin::Create(CInput::Instance().GetScreenWidth() - 30 * 2,
		m_aBtn[0].GetHeight(), -2);

	// ��ư ���.(���� ������ �����Ǿ�� ��ư ��� ����)
#ifdef _VS2008PORTING
	for (int i = 0; i < LMW_BTN_MAX; ++i)
#else // _VS2008PORTING
	for (i = 0; i < LMW_BTN_MAX; ++i)
#endif // _VS2008PORTING
		CWin::RegisterButton(&m_aBtn[i]);

	// ���� �ϴ� ��� ��������Ʈ ����.
	m_sprDeco.Create(189, 103, BITMAP_LOG_IN+6, 0, NULL, 105, 59);
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
// ��ϵ� ��ư�� ���� �����츦 ������ ������ Release() �� �޸� ����.
void CLoginMainWin::PreRelease()
{
	m_sprDeco.Release();
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void CLoginMainWin::SetPosition(int nXCoord, int nYCoord)
{
	CWin::SetPosition(nXCoord, nYCoord);

	m_aBtn[LMW_BTN_MENU].SetPosition(nXCoord, nYCoord);
	m_aBtn[LMW_BTN_CREDIT].SetPosition(
		nXCoord + CWin::GetWidth() - m_aBtn[LMW_BTN_CREDIT].GetWidth(),
		nYCoord);
#ifdef MOVIE_DIRECTSHOW
	m_aBtn[LMW_BTN_MOVIE].SetPosition(m_aBtn[LMW_BTN_CREDIT].GetXPos()
		- 10 - m_aBtn[LMW_BTN_MOVIE].GetWidth(), nYCoord);
#endif	// MOVIE_DIRECTSHOW
	m_sprDeco.SetPosition(
		m_aBtn[LMW_BTN_CREDIT].GetXPos(), m_aBtn[LMW_BTN_CREDIT].GetYPos());
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CLoginMainWin::Show(bool bShow)
{
	CWin::Show(bShow);

	for (int i = 0; i < LMW_BTN_MAX; ++i)
		m_aBtn[i].Show(bShow);
	m_sprDeco.Show(bShow);
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
// ��ϵ� ��ư ������ ������ �ʿ� ����.
// ��, �ٸ� ��Ʈ���̳� ������ ��ư�� ���� ȿ���� ó���Ϸ��� ���� Ŭ������
//CursorInButtonlike() �Լ��� �����Ǹ� �ϸ� �ȴ�.
bool CLoginMainWin::CursorInWin(int nArea)
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
void CLoginMainWin::UpdateWhileActive()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CLoginMainWin::UpdateWhileActive(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	if (m_aBtn[LMW_BTN_MENU].IsClick())			// �޴� ��ư Ŭ��.
	{
		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.ShowWin(&rUIMng.m_SysMenuWin);
		rUIMng.SetSysMenuWinShow(true);
	}
	else if (m_aBtn[LMW_BTN_CREDIT].IsClick())	// ũ���� ��ư Ŭ��.
	{
		// 5�� ���� �ƹ��� ���ϸ� �������� ��������� ����.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
		SendRequestServerList2();
#else
		SendRequestServerList();
#endif // PKD_ADD_ENHANCED_ENCRYPTION

		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.ShowWin(&rUIMng.m_CreditWin);

		::StopMp3(g_lpszMp3[MUSIC_MAIN_THEME]);
		::PlayMp3(g_lpszMp3[MUSIC_MUTHEME]);
	}
#ifdef MOVIE_DIRECTSHOW
	else if (m_aBtn[LMW_BTN_MOVIE].IsClick())	// ������ ��ư Ŭ��.
	{
		g_pMovieScene = new CMovieScene;
		g_pMovieScene->Initialize_DirectShow(g_hWnd, MOVIE_FILE_WMV);
		if(g_pMovieScene->IsFile() == FALSE || g_pMovieScene->IsFailDirectShow() == TRUE)
		{
			g_pMovieScene->Destroy();
			SAFE_DELETE(g_pMovieScene);
			return;	
		}
		::StopMp3(g_lpszMp3[MUSIC_MAIN_THEME]);
		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.SetMoving(true);
	}
#endif	// MOVIE_DIRECTSHOW
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
// CWin::RenderButtons()�� ����ؼ� ��ư ���� ������ ���� �� �ִ�.
// ������ ����� ������ �ʿ� ����.
void CLoginMainWin::RenderControls()
{
	m_sprDeco.Render();
	CWin::RenderButtons();
}