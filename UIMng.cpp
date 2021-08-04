//*****************************************************************************
// File: UIMng.cpp
//
// Desc: implementation of the CUIMng class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "UIMng.h"
#include "Input.h"
#include "Sprite.h"
#include "GaugeBar.h"
#include "ZzzOpenglUtil.h"
#include "Zzzinfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "GameCensorship.h"
#include "UIControls.h"

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
#include "ServerListManager.h"
#endif // KJH_ADD_SERVER_LIST_SYSTEM

#define	DOCK_EXTENT		10		///< ��ŷ ����.

// Ÿ��Ʋ �� ��������Ʈ(TS)
//#define	UIM_TS_BG_BLACK		0	// ���� ����.
#define	UIM_TS_BACK0		0	// ���0
#define	UIM_TS_BACK1		1	// ���1
#define	UIM_TS_MU			2	// �� �ΰ�
#define	UIM_TS_121518		3	// ��ü �̿밡 ��ũ
#define	UIM_TS_WEBZEN		4	// ���� �ΰ�
#ifdef PBG_ENGLISHLOGO_CHANGE
	#define UIM_TS_WEBZEN_WITH	5	//�۷ι� �߰� �ΰ�
	#define	UIM_TS_MAX			6	// ��������Ʈ �ִ� ����
#else //PBG_ENGLISHLOGO_CHANGE
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	#define UIM_TS_BACK2		5	// ���2
	#define UIM_TS_BACK3		6	// ���3
	#define UIM_TS_BACK4		7	// ���4
	#define UIM_TS_BACK5		8	// ���5
	#define UIM_TS_BACK6		9	// ���6
	#define UIM_TS_BACK7		10	// ���7
	#define UIM_TS_BACK8		11	// ���8
	#define UIM_TS_BACK9		12	// ���9
	#define	UIM_TS_MAX			13	// ��������Ʈ �ִ� ����
#else //PBG_ADD_NEWLOGO_IMAGECHANGE
	#define	UIM_TS_MAX			5	// ��������Ʈ �ִ� ����
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
#endif //PBG_ENGLISHLOGO_CHANGE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUIMng::CUIMng()
{
	m_asprTitle = NULL;
	m_pgbLoding = NULL;
	m_pLoadingScene = NULL;
	
#ifdef MOVIE_DIRECTSHOW
	m_bMoving = false;
#endif // MOVIE_DIRECTSHOW
}

CUIMng::~CUIMng()
{

}

//*****************************************************************************
// �Լ� �̸� : Instance()
// �Լ� ���� : ��ü�� �� �ϳ��� ����.
//			  �� Ŭ������ �����ϱ� ���� �������̽���
//*****************************************************************************
CUIMng& CUIMng::Instance()
{
	static CUIMng s_UIMng;
    return s_UIMng;
}

//*****************************************************************************
// �Լ� �̸� : CreateTitleSceneUI()
// �Լ� ���� : Ÿ��Ʋ �� UI ����.
//*****************************************************************************
void CUIMng::CreateTitleSceneUI()
{
// Ÿ��Ʋ �� UI�� �ִٸ� ����.
	ReleaseTitleSceneUI();

	g_GameCensorship->SetVisible(true);
	g_GameCensorship->SetState(SEASON3A::CGameCensorship::STATE_LOADING);

	CInput& rInput = CInput::Instance();
// Ÿ��Ʋ ���� 800 * 600 ���� ��ũ�� ��带 ��� ��.
	float fScaleX = (float)rInput.GetScreenWidth() / 800.0f;
	float fScaleY = (float)rInput.GetScreenHeight() / 600.0f;

// ��� ��������Ʈ ���� �� ��ġ.
	m_asprTitle = new CSprite[UIM_TS_MAX];

#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	float _fScaleXTemp = (float)rInput.GetScreenWidth()/1280.0f;
	float _fScaleYTemp = (float)rInput.GetScreenHeight()/1024.0f;

	m_asprTitle[UIM_TS_BACK0].Create(400, 69, BITMAP_TITLE, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK0].SetPosition(0, 0);

	m_asprTitle[UIM_TS_BACK1].Create(400, 69, BITMAP_TITLE+1, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK1].SetPosition(400, 0);

	m_asprTitle[UIM_TS_BACK2].Create(400, 100, BITMAP_TITLE+6, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK2].SetPosition(0, 500);

	m_asprTitle[UIM_TS_BACK3].Create(400, 100, BITMAP_TITLE+7, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK3].SetPosition(400, 500);

	m_asprTitle[UIM_TS_BACK4].Create(512, 512, BITMAP_TITLE+8, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK4].SetPosition(0, 119);

	m_asprTitle[UIM_TS_BACK5].Create(512, 512, BITMAP_TITLE+9, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK5].SetPosition(512, 119);

	m_asprTitle[UIM_TS_BACK6].Create(256, 512, BITMAP_TITLE+10, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK6].SetPosition(1024, 119);

	m_asprTitle[UIM_TS_BACK7].Create(512, 223, BITMAP_TITLE+11, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK7].SetPosition(0, 512+119);

	m_asprTitle[UIM_TS_BACK8].Create(512, 223, BITMAP_TITLE+12, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK8].SetPosition(512, 512+119);

	m_asprTitle[UIM_TS_BACK9].Create(256, 223, BITMAP_TITLE+13, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleYTemp);
	m_asprTitle[UIM_TS_BACK9].SetPosition(1024, 512+119);

#ifdef PBG_ADD_MU_LOGO
#ifdef PBG_ADD_MUBLUE_LOGO
	// ��� ��
	m_asprTitle[UIM_TS_MU].Create(167, 168, BITMAP_TITLE+2, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleXTemp);
#else //PBG_ADD_MUBLUE_LOGO
 	m_asprTitle[UIM_TS_MU].Create(216, 138, BITMAP_TITLE+2, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleXTemp);
#endif //PBG_ADD_MUBLUE_LOGO
#else //PBG_ADD_MU_LOGO
	m_asprTitle[UIM_TS_MU].Create(106, 49, BITMAP_TITLE+2, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp, _fScaleXTemp);
#endif //PBG_ADD_MU_LOGO
	if((float)rInput.GetScreenWidth() == 1280)
#ifdef PBG_ADD_MU_LOGO
#ifdef PBG_ADD_MUBLUE_LOGO
		//��� ��
		m_asprTitle[UIM_TS_MU].SetPosition(640-108, 633+53);
#else //PBG_ADD_MUBLUE_LOGO
		m_asprTitle[UIM_TS_MU].SetPosition(640-108, 663+53);
#endif //PBG_ADD_MUBLUE_LOGO
#else //PBG_ADD_MU_LOGO
		m_asprTitle[UIM_TS_MU].SetPosition(1150, 775);
#endif //PBG_ADD_MU_LOGO
	else
#ifdef PBG_ADD_MU_LOGO
#ifdef PBG_ADD_MUBLUE_LOGO
		m_asprTitle[UIM_TS_MU].SetPosition(640-83, 633);
#else //PBG_ADD_MUBLUE_LOGO
		m_asprTitle[UIM_TS_MU].SetPosition(640-108, 663);
#endif //PBG_ADD_MUBLUE_LOGO
#else //PBG_ADD_MU_LOGO
		m_asprTitle[UIM_TS_MU].SetPosition(1150, 725);
#endif //PBG_ADD_MU_LOGO
	
#else //PBG_ADD_NEWLOGO_IMAGECHANGE
	m_asprTitle[UIM_TS_BACK0].Create(512, 478, BITMAP_TITLE, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK0].SetPosition(0, 60);

	m_asprTitle[UIM_TS_BACK1].Create(288, 478, BITMAP_TITLE+1, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_BACK1].SetPosition(512, 60);

	m_asprTitle[UIM_TS_MU].Create(93, 48, BITMAP_TITLE+2, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_MU].SetPosition(3, 80);
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE

	m_asprTitle[UIM_TS_121518].Create(256, 206, BITMAP_TITLE+3, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_121518].SetPosition(544, 60);

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
#ifdef PBG_ENGLISHLOGO_CHANGE
/*
	//�ΰ� ���Ʒ��� ������
	//Webzen �ΰ�
	m_asprTitle[UIM_TS_WEBZEN_WITH].Create(187, 151, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN_WITH].SetPosition(307, 125);

	//�۷ι� �ΰ�
	m_asprTitle[UIM_TS_WEBZEN].Create(512, 122, BITMAP_TITLE+6, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(144, 255);
*/
	//�ΰ� �¿�� ������..
	//Webzen �ΰ�
	m_asprTitle[UIM_TS_WEBZEN_WITH].Create(187, 151, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN_WITH].SetPosition(570, 205);
	
	//�۷ι� �ΰ�
	m_asprTitle[UIM_TS_WEBZEN].Create(512, 122, BITMAP_TITLE+6, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(44, 225);

#else //PBG_ENGLISHLOGO_CHANGE

#ifdef LDK_MOD_GLOBAL_PORTAL_LOGO
	//�⺻ �ΰ�� �����.
	m_asprTitle[UIM_TS_WEBZEN].Create(187, 151, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(307, 225);
#else //LDK_MOD_GLOBAL_PORTAL_LOGO
	m_asprTitle[UIM_TS_WEBZEN].Create(342, 152, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(307-77, 225);
#endif //LDK_MOD_GLOBAL_PORTAL_LOGO

#endif //PBG_ENGLISHLOGO_CHANGE
#else //SELECTED_LANGUAGE == LANGUAGE_ENGLISH
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	m_asprTitle[UIM_TS_WEBZEN].Create(53, 46, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, _fScaleXTemp*1.2f, _fScaleYTemp*1.2f);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(16, 8);
#else //PBG_ADD_NEWLOGO_IMAGECHANGE
	m_asprTitle[UIM_TS_WEBZEN].Create(187, 151, BITMAP_TITLE+4, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	m_asprTitle[UIM_TS_WEBZEN].SetPosition(307, 225);
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
#endif //SELECTED_LANGUAGE == LANGUAGE_ENGLISH

// �⺻ ����Ÿ �ε� ����� ���� �� ��ġ.
	m_pgbLoding = new CGaugeBar;
	
	RECT rc = { 0, 0, 656, 15 };
	m_pgbLoding->Create(4, 15, BITMAP_TITLE+5, &rc, 0, 0, -1, true, fScaleX,
		fScaleY);
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	m_pgbLoding->SetPosition(72, 540);
#else //PBG_ADD_NEWLOGO_IMAGECHANGE
	m_pgbLoding->SetPosition(72, 482);
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
// ��� �� ȭ�鿡 ���� ��.
	for (int i = 0; i < UIM_TS_MAX; ++i)
	{
		m_asprTitle[i].Show();
	}
	m_pgbLoding->Show();

	// �ؿܴ� ���� ����� �ȻѸ���, �ѱ��� ���ο� ������� ������ �ϰ� �����ϱ� ������ false�� �ӽ÷� �Ѵ�.	
	m_asprTitle[UIM_TS_121518].Show(false);

	m_nScene = UIM_SCENE_TITLE;
}

//*****************************************************************************
// �Լ� �̸� : ReleaseTitleSceneUI()
// �Լ� ���� : Ÿ��Ʋ �� UI Release.
//*****************************************************************************
void CUIMng::ReleaseTitleSceneUI()
{
	g_GameCensorship->SetVisible(false);

	SAFE_DELETE_ARRAY(m_asprTitle);
	SAFE_DELETE(m_pgbLoding);

	m_nScene = UIM_SCENE_NONE;
}

//*****************************************************************************
// �Լ� �̸� : RenderTitleSceneUI()
// �Լ� ���� : Ÿ��Ʋ �� ����.
// �Ű� ���� : hDC		: DC �ڵ�.
//			   dwNow	: ���� �ε� �� ������ ��.
//			   dwTotal	: �ִ� �ε� ������ ��.
//*****************************************************************************
void CUIMng::RenderTitleSceneUI(HDC hDC, DWORD dwNow, DWORD dwTotal)
{
	::BeginOpengl();
/*
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
	::glClearColor( 1.f, 1.f, 1.f, 1.f);
#endif
*/
#ifdef USE_SHADOWVOLUME
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#else
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
/*
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
	::glClearColor( 0.f, 0.f, 0.f, 1.f);
#endif
*/
	::BeginBitmap();

	for (int i = 0; i < UIM_TS_MAX; ++i)
	{
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
		if(i==2)
			continue;
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
		m_asprTitle[i].Render();
	}
#ifndef KJH_ADD_EVENT_LOADING_SCENE				// #ifndef
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	m_asprTitle[UIM_TS_MU].Render();
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
#endif // KJH_ADD_EVENT_LOADING_SCENE

	m_pgbLoding->SetValue(dwNow, dwTotal);
	m_pgbLoding->Render();

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN	
	g_GameCensorship->Render();
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
	
#ifdef FOR_WORK
	g_pRenderText->SetFont(g_hFontBig);

#ifdef FOR_HACKING
	g_pRenderText->RenderText(0,0,"��Ƽ �α� ����");
#else // FOR_HACKING
	g_pRenderText->RenderText(0,0,"�系 �۾��� ����");
#endif // FOR_HACKING
#endif // FOR_WORK

	::EndBitmap();
	::EndOpengl();
	::glFlush();
	::SwapBuffers(hDC);
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ���� ������Ʈ ����.
//*****************************************************************************
void CUIMng::Create()
{
	m_bCursorOnUI = false;
	m_bBlockCharMove = false;
	m_bWinActive = false;
	m_nScene = UIM_SCENE_NONE;

	return;
}

//*****************************************************************************
// �Լ� �̸� : RemoveWinList()
// �Լ� ���� : ������� Release�� ������ ����Ʈ ���.
//*****************************************************************************
void CUIMng::RemoveWinList()
{
	CWin* pWin;
	while (m_WinList.GetCount())
	{
		pWin = (CWin*)m_WinList.RemoveHead();
		pWin->Release();
	}
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : ������ �Ŵ��� Release.
//*****************************************************************************
void CUIMng::Release()
{
	RemoveWinList();

	// ĳ���� ������ ���Ǵ� ĳ���� ���� ��ǳ���� ����.
	m_CharInfoBalloonMng.Release();

//	m_ToolTip.Release();

	m_nScene = UIM_SCENE_NONE;
}

//*****************************************************************************
// �Լ� �̸� : CreateLoginScene()
// �Լ� ���� : �α��� �������� ������ ����.
//*****************************************************************************
void CUIMng::CreateLoginScene()
{
	g_GameCensorship->SetVisible(false);
	
	RemoveWinList();

	// ĳ���� ������ ���Ǵ� ĳ���� ���� ��ǳ���� ����.
	m_CharInfoBalloonMng.Release();

	CInput& rInput = CInput::Instance();
	
	// �޽��� â.
	m_MsgWin.Create();
	m_WinList.AddHead(&m_MsgWin);
	m_MsgWin.SetPosition((rInput.GetScreenWidth() - 352) / 2,
		(rInput.GetScreenHeight() - 113) / 2);

	// �ý��� �޴� â.
	m_SysMenuWin.Create();
	m_WinList.AddHead(&m_SysMenuWin);

	// �ɼ�â.
	m_OptionWin.Create();
	m_WinList.AddHead(&m_OptionWin);

	// ���� ������.
	m_LoginMainWin.Create();
	m_WinList.AddHead(&m_LoginMainWin);
	// 800*600 ��忡�� 3Dȭ�� �عٴ� Y��ġ�� 567��.
	int nBaseY = int(567.0f / 600.0f * (float)rInput.GetScreenHeight());
	m_LoginMainWin.SetPosition(30,  nBaseY - m_LoginMainWin.GetHeight() - 11);

	// ���� ���� â.
	m_ServerSelWin.Create();
	m_WinList.AddHead(&m_ServerSelWin);
	m_ServerSelWin.SetPosition(
		(rInput.GetScreenWidth() - m_ServerSelWin.GetWidth()) / 2,
		(rInput.GetScreenHeight() - m_ServerSelWin.GetHeight()) / 2);

	// �α��� â.
	m_LoginWin.Create();
	m_WinList.AddHead(&m_LoginWin);
	m_LoginWin.SetPosition(
		(rInput.GetScreenWidth() - m_LoginWin.GetWidth()) / 2,
		(rInput.GetScreenHeight() - m_LoginWin.GetHeight()) * 2 / 3);

	// ũ���� â.
	m_CreditWin.Create();
	m_WinList.AddHead(&m_CreditWin);

#ifdef LJH_ADD_LOCALIZED_BTNS
	// ��, �ƴϿ�(localized) ��ư �޽��� â.
	m_LocalizedYESNOMsgWin.Create(MWT_BTN_LOCALIZED_YESNO);
	m_WinList.AddHead(&m_LocalizedYESNOMsgWin);
	m_LocalizedYESNOMsgWin.SetPosition((rInput.GetScreenWidth() - 352) / 2,
		(rInput.GetScreenHeight() - 113) / 2);

	// ��, �ƴϿ�(localized) ��ư �޽��� â.
	m_LocalizedConfirmCancelMsgWin.Create(MWT_BTN_LOCALIZED_CONFIRM_CANCEL);
	m_WinList.AddHead(&m_LocalizedConfirmCancelMsgWin);
	m_LocalizedConfirmCancelMsgWin.SetPosition((rInput.GetScreenWidth() - 352) / 2,
		(rInput.GetScreenHeight() - 113) / 2);

#endif //LJH_ADD_LOCALIZED_BTNS

#ifdef LJH_ADD_ONETIME_PASSWORD
	// ��Ÿ���н����� â.
	m_OneTimePasswordWin.Create();
	m_WinList.AddHead(&m_OneTimePasswordWin);
	m_OneTimePasswordWin.SetPosition(
		(rInput.GetScreenWidth() - m_OneTimePasswordWin.GetWidth()) / 2,
		(rInput.GetScreenHeight() - m_OneTimePasswordWin.GetHeight()) * 2 / 3);
#endif //LJH_ADD_ONETIME_PASSWORD

	
	
	m_bSysMenuWinShow = false;
	m_nScene = UIM_SCENE_LOGIN;
}

//*****************************************************************************
// �Լ� �̸� : CreateCharacterScene()
// �Լ� ���� : ĳ���� ���� �������� ������ ����.
//*****************************************************************************
void CUIMng::CreateCharacterScene()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	g_GameCensorship->SetState( g_ServerListManager->GetCensorshipIndex() );
#else // KJH_ADD_SERVER_LIST_SYSTEM
	g_GameCensorship->SetGameState();
#endif // KJH_ADD_SERVER_LIST_SYSTEM

	RemoveWinList();

	m_CharInfoBalloonMng.Create();

	CInput& rInput = CInput::Instance();

	// �޽��� â.
	m_MsgWin.Create();
	m_WinList.AddHead(&m_MsgWin);
	m_MsgWin.SetPosition((rInput.GetScreenWidth() - 352) / 2,
		(rInput.GetScreenHeight() - 113) / 2);

	// ���� �޽��� â.
	m_ServerMsgWin.Create();
	m_WinList.AddHead(&m_ServerMsgWin);
	// 800*600 ��忡�� 3Dȭ�� Y��ġ�� 31��.
	int nBaseY = int(31.0f / 600.0f * (float)rInput.GetScreenHeight());
	m_ServerMsgWin.SetPosition(10, nBaseY + 10);

	// �ý��� �޴� â.
	m_SysMenuWin.Create();
	m_WinList.AddHead(&m_SysMenuWin);

	m_OptionWin.Create();
	m_WinList.AddHead(&m_OptionWin);

	// ���� ������.
	m_CharSelMainWin.Create();
	m_WinList.AddHead(&m_CharSelMainWin);
	// 800*600 ��忡�� 3Dȭ�� �عٴ� Y��ġ�� 567��.
	nBaseY = int(567.0f / 600.0f * (float)rInput.GetScreenHeight());
	m_CharSelMainWin.SetPosition(22,  nBaseY - m_CharSelMainWin.GetHeight() - 11);

	// ĳ���� ����� â.
	m_CharMakeWin.Create();
	m_WinList.AddHead(&m_CharMakeWin);
#ifdef PJH_CHARACTER_RENAME
	m_CharMakeWin.Set_State();
#endif //PJH_CHARACTER_RENAME

	m_CharMakeWin.SetPosition((rInput.GetScreenWidth() - 454) / 2,
		(rInput.GetScreenHeight() - 406) / 2);

	m_CharSelMainWin.UpdateDisplay();
	m_CharInfoBalloonMng.UpdateDisplay();

	ShowWin(&m_CharSelMainWin);

	m_bSysMenuWinShow = false;
	m_nScene = UIM_SCENE_CHARACTER;
}

//*****************************************************************************
// �Լ� �̸� : CreateCharacterScene()
// �Լ� ���� : ���� �������� ������ ����.
//*****************************************************************************
void CUIMng::CreateMainScene()
{
	RemoveWinList();

	// ĳ���� ������ ���Ǵ� ĳ���� ���� ��ǳ���� ����.
	m_CharInfoBalloonMng.Release();

	m_nScene = UIM_SCENE_MAIN;
}

//*****************************************************************************
// �Լ� �̸� : SetActiveWin()
// �Լ� ���� : �������� Ȱ��ȭ. ������ Active���� window �ּ� ����.
//			   (list�� head�� ��Ȱ��ȭ ��, Ȱ��ȭ��ų window�� Ȱ��ȭ ��Ű��
//			  list�� head�� �ű�.)
// �Ű� ���� : pWin	: Ȱ��ȭ��ų �������� �ּ�. (list�� ��ϵ� ������)
//*****************************************************************************
CWin* CUIMng::SetActiveWin(CWin* pWin)
{
// Active���� window ó�� �κ�.
	// Active���� window�� �ִٸ� �� window�� list�� head�� ����Ű�� window�̹�
	//�� �ϴ� list�� head ���� ����.
	CWin* pBeforeActWin = (CWin*)m_WinList.GetHead();
	// list�� head�� ������(list�� ��� �ִٸ�) NULL ����.
	if (pBeforeActWin == NULL)
		return NULL;

	if (pBeforeActWin->IsActive())	// list�� head�� window�� Active�ΰ�?
		pBeforeActWin->Active(FALSE);	// ��Ȱ��ȭ.
	else							// list�� head�� window�� Active�� �ƴ϶��.
		pBeforeActWin = NULL;		// ������ Active���� window�� ����.

// Active��ų Window ó�� �κ�.
	// Active��ų Window�� ���̴°�? (Update()���� �˻��������� �� �Լ��� �ܵ�
	//���� ȣ��� ��츦 ���� �ٽ� �˻���.)
	if (pWin->IsShow())
	{
	// Active��ų Window�� list�� head�� �̵�.
		// �켱 list���� ã�Ƽ� ����.
		if (!m_WinList.RemoveAt(m_WinList.Find(pWin)))
			return NULL;			// ���н� NULL ����.

		m_bWinActive = true;
		m_WinList.AddHead(pWin);	// list�� head�� �߰�.
	}

	return pBeforeActWin;			// ������ Active���� window ������ ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : ShowWin()\n
// �Լ� ���� : �����츦 ���̰��ϰ� Ȱ��ȭ ��Ŵ.\n
// �Ű� ���� : pWin	: ���̰��� �������� �ּ�. (list�� ��ϵ� ������)
//*****************************************************************************/
void CUIMng::ShowWin(CWin* pWin)
{
	pWin->Show(TRUE);
	SetActiveWin(pWin);
}
/**
//*****************************************************************************
// �Լ� �̸� : HideWin()\n
// �Լ� ���� : �����츦 ����.\n
// �Ű� ���� : pWin	: ���� �������� �ּ�. (list�� ��ϵ� ������)
//*****************************************************************************/
void CUIMng::HideWin(CWin* pWin)
{
	// �� �����츦 ����Ʈ���� ����.
	if (!m_WinList.RemoveAt(m_WinList.Find(pWin)))
		return;					// ���н� ����.

	pWin->Show(FALSE);		// ������ �ʰ� �Ѵ�.
	pWin->Active(FALSE);	// ��Ȱ��ȭ.
	m_WinList.AddTail(pWin);	// list�� tail�� �߰�.

	// list�� head�� ���δٸ� Ȱ��ȭ.
	pWin = (CWin*)m_WinList.GetHead();
	if (pWin->IsShow())
		m_bWinActive = true;
}

//*****************************************************************************
// �Լ� �̸� : CheckDockWin()\n
// �Լ� ���� : ������ ��ŷ ó��.
//*****************************************************************************/
void CUIMng::CheckDockWin()
{
	NODE* position = m_WinList.GetHeadPosition();
	if (NULL == position)
		return;

	// list�� head�� �����͸� ��� position�� ��������.
	// pMovWin: �̵� ���� ������.
	CWin* pMovWin = (CWin*)m_WinList.GetNext(position);

	if (pMovWin->GetState() != WS_MOVE)	// �̵� ���� �ƴѰ�?
		return;

	pMovWin->SetDocking(false);

	// �̵� ���� �������� ����.
	RECT rcMovWin = { pMovWin->GetTempXPos(), pMovWin->GetTempYPos(),
		pMovWin->GetTempXPos() + pMovWin->GetWidth(),
		pMovWin->GetTempYPos() + pMovWin->GetHeight() };
	
	// �̵� ���� �������� �𼭸� ��ŷ ����. ������� ������ �𼭸��� �߽���
	//�� �� �»�, ���, ����, ���� �簢�� ����.
	RECT rcDock[4] =
	{
		{ rcMovWin.left - DOCK_EXTENT, rcMovWin.top - DOCK_EXTENT,
			rcMovWin.left + DOCK_EXTENT, rcMovWin.top + DOCK_EXTENT },
		{ rcMovWin.right - DOCK_EXTENT, rcMovWin.top - DOCK_EXTENT,
			rcMovWin.right + DOCK_EXTENT, rcMovWin.top + DOCK_EXTENT },
		{ rcMovWin.left - DOCK_EXTENT, rcMovWin.bottom - DOCK_EXTENT,
			rcMovWin.left + DOCK_EXTENT, rcMovWin.bottom + DOCK_EXTENT },
		{ rcMovWin.right - DOCK_EXTENT, rcMovWin.bottom - DOCK_EXTENT,
			rcMovWin.right + DOCK_EXTENT, rcMovWin.bottom + DOCK_EXTENT }
	};

// ȭ�� �����ڸ� ��ŷ �˻� �� �̵�.
	CInput& rInput = CInput::Instance();
	// ȭ���� �𼭸� 4��.
	POINT pt[4] = { { 0, 0 }, { rInput.GetScreenWidth(), 0 },
		{ 0, rInput.GetScreenHeight() },
		{ rInput.GetScreenWidth(), rInput.GetScreenHeight() } };

	if (::PtInRect(&rcDock[0], pt[0]))		// ȭ���� �»� �𼭸�.
	{
		pMovWin->SetPosition(pt[0].x, pt[0].y);
		pMovWin->SetDocking(true);
	}
	else if (::PtInRect(&rcDock[1], pt[1]))	// ȭ���� ��� �𼭸�.
	{
		pMovWin->SetPosition(pt[1].x - pMovWin->GetWidth(), pt[1].y);
		pMovWin->SetDocking(true);
	}
	else if (::PtInRect(&rcDock[2], pt[2]))	// ȭ���� ���� �𼭸�.
	{
		pMovWin->SetPosition(pt[2].x, pt[2].y - pMovWin->GetHeight());
		pMovWin->SetDocking(true);
	}
	else if (::PtInRect(&rcDock[3], pt[3]))	// ȭ���� ���� �𼭸�.
	{
		pMovWin->SetPosition(pt[3].x - pMovWin->GetWidth(),
			pt[3].y - pMovWin->GetHeight());
		pMovWin->SetDocking(true);
	}
	// ȭ���� ���.
	else if (rcDock[0].top < 0 && rcDock[0].bottom > 0)
	{
		pMovWin->SetPosition(rcMovWin.left, 0);
		pMovWin->SetDocking(true);
	}
	// ȭ���� �ϴ�.
	else if (rcDock[2].top < pt[2].y && rcDock[2].bottom > pt[2].y)
	{
		pMovWin->SetPosition(rcMovWin.left, pt[2].y - pMovWin->GetHeight());
		pMovWin->SetDocking(true);
	}
	// ȭ���� ����.
	else if (rcDock[0].left < 0 && rcDock[0].right > 0)
	{
		pMovWin->SetPosition(0, rcMovWin.top);
		pMovWin->SetDocking(true);
	}
	// ȭ���� ����.
	else if (rcDock[1].left < pt[1].x && rcDock[1].right > pt[1].x)
	{
		pMovWin->SetPosition(pt[1].x - pMovWin->GetWidth(), rcMovWin.top);
		pMovWin->SetDocking(true);
	}

// Ÿ ��������� ��ŷ.
	BOOL bEdgeDocking = FALSE;
	int i, j, nXCoord, nYCoord;
	CWin* pWin;

	while (position)	// 2��° ��������� ������ üũ.
	{
		// üũ�� ������ ���.
		pWin = (CWin*)m_WinList.GetNext(position);
		if (!pWin->IsShow())	// ������ ������ ���� Ż��.
			continue;

		// üũ�� �������� �»�, ���, ����, ���� ����.
		pt[0].x = pWin->GetXPos();
		pt[0].y = pWin->GetYPos();
		pt[1].x = pWin->GetXPos() + pWin->GetWidth();
		pt[1].y = pt[0].y;
		pt[2].x = pt[0].x;
		pt[2].y = pWin->GetYPos() + pWin->GetHeight();
		pt[3].x = pt[1].x;
		pt[3].y = pt[2].y;

		// �𼭸� ��ŷ �˻�.
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (i != j && ::PtInRect(&rcDock[i], pt[j]))
				{
					bEdgeDocking = TRUE;
					goto DOCKING;
				}
			}
		}

		// �� �� ��ŷ �˻� �� �̵�.
		// ��, �Ʒ��� �˻�.
		if (pt[0].x < rcDock[1].left && pt[1].x > rcDock[0].right)
		{
			nXCoord = rcMovWin.left;
			if (pt[2].y > rcDock[0].top && pt[2].y < rcDock[0].bottom)
			{
				if (SetDockWinPosition(pMovWin, nXCoord, pt[2].y))
					continue;
			}
			else if (pt[0].y > rcDock[2].top && pt[0].y < rcDock[2].bottom)
			{
				if (SetDockWinPosition(pMovWin,
					nXCoord, pt[0].y - pMovWin->GetHeight()))
					continue;
			}
		}
		// ��,�캯 �˻�.
		else if (pt[0].y < rcDock[2].top && pt[2].y > rcDock[0].bottom)
		{
			nYCoord = rcMovWin.top;
			if (pt[1].x > rcDock[0].left && pt[1].x < rcDock[0].right)
			{
				if (SetDockWinPosition(pMovWin, pt[1].x, nYCoord))
					continue;
			}
			else if (pt[0].x > rcDock[1].left && pt[0].x < rcDock[1].right)
			{
				if (SetDockWinPosition(pMovWin,
					pt[0].x - pMovWin->GetWidth(), nYCoord))
					continue;
			}
		}
	}	// while (position)�� ��.

DOCKING:	// �𼭸� ��ŷ �� �̵�.
	if (bEdgeDocking)	//  �𼭸� ��ŷ�ΰ�?
	{
		switch (j)		// j�� üũ�� ������(pWin)�� �𼭸� ����.
		{
		case 0:
			switch (i)	// i�� ��ŷ ��ų ������(pMovWin)�� ��ŷ ����.
			{
			case 1:
				nXCoord = pWin->GetXPos() - pMovWin->GetWidth();
				nYCoord = pWin->GetYPos();
				break;
			case 2:
				nXCoord = pWin->GetXPos();
				nYCoord = pWin->GetYPos() - pMovWin->GetHeight();
				break;
			case 3:
				nXCoord = pWin->GetXPos() - pMovWin->GetWidth();
				nYCoord = pWin->GetYPos() - pMovWin->GetHeight();
			}
			break;
		
		case 1:
			switch (i)
			{
			case 0:
				nXCoord = pWin->GetXPos() + pWin->GetWidth();
				nYCoord = pWin->GetYPos();
				break;
			case 2:
				nXCoord = pWin->GetXPos() + pWin->GetWidth();
				nYCoord = pWin->GetYPos() - pMovWin->GetHeight();
				break;
			case 3:
				nXCoord = pWin->GetXPos() + pWin->GetWidth()
					- pMovWin->GetWidth();
				nYCoord = pWin->GetYPos() - pMovWin->GetHeight();
			}
			break;
		
		case 2:
			switch (i)
			{
			case 0:
				nXCoord = pWin->GetXPos();
				nYCoord = pWin->GetYPos() + pWin->GetHeight();
				break;
			case 1:
				nXCoord = pWin->GetXPos() - pMovWin->GetWidth();
				nYCoord = pWin->GetYPos() + pWin->GetHeight();
				break;
			case 3:
				nXCoord = pWin->GetXPos() - pMovWin->GetWidth();
				nYCoord = pWin->GetYPos() + pWin->GetHeight()
					- pMovWin->GetHeight();
			}
			break;
		
		case 3:
			switch (i)
			{
			case 0:
				nXCoord = pWin->GetXPos() + pWin->GetWidth();
				nYCoord = pWin->GetYPos() + pWin->GetHeight();
				break;
			case 1:
				nXCoord = pWin->GetXPos() + pWin->GetWidth()
					- pMovWin->GetWidth();
				nYCoord = pWin->GetYPos() + pWin->GetHeight();
				break;
			case 2:
				nXCoord = pWin->GetXPos() + pWin->GetWidth();
				nYCoord = pWin->GetYPos() + pWin->GetHeight()
					- pMovWin->GetHeight();
			} 
		}
		SetDockWinPosition(pMovWin, nXCoord, nYCoord);
	}	// if (bEdgeDocking)�� ��.
}

//*****************************************************************************
// �Լ� �̸� : SetDockWinPosition()
// �Լ� ���� : ��ŷ �� ������ ��ġ�� ȭ�鿡�� ���δٸ� �� ��ġ�� �̵� �� TRUE
//			  ����.(��ŷ�� �����찡 ȭ�� ������ ������ ���� ����.)
// �Ű� ���� : pMoveWin	: �̵� ���� ������ �ּ�.
//			   nDockX	: ��ŷ �� �������� X ��ǥ.
//			   nDockY	: ��ŷ �� �������� Y ��ǥ.
//*****************************************************************************
bool CUIMng::SetDockWinPosition(CWin* pMoveWin, int nDockX, int nDockY)
{
	CInput& rInput = CInput::Instance();
	RECT rcDummy;
	RECT rcScreen = { 0, 0, rInput.GetScreenWidth(), rInput.GetScreenHeight() };
	RECT rcMoveWin = { nDockX, nDockY,
		nDockX + pMoveWin->GetWidth(), nDockY + pMoveWin->GetHeight() };

	if (::IntersectRect(&rcDummy, &rcScreen, &rcMoveWin))
	{
		pMoveWin->SetPosition(nDockX, nDockY);
		pMoveWin->SetDocking(true);
		return true;
	}

	return false;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ��������� �ڵ� ó��.(������ Ŭ���� Ȱ��ȭ, ������ Update()����,
//			  ��ŷ, ���콺 Ŀ�� ��� �ٲٱ�, ������ �ݾ��� ���� ó��, ������ ��
//			  ��ư ó��, ������ �����ֱ� ��ư ó��.)
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void CUIMng::Update(double dDeltaTick)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(dDeltaTick < 0)		return;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	// �����Ǿ� ���� �ʴٸ� ó������ ����.
	if (UIM_SCENE_NONE == m_nScene || m_WinList.IsEmpty())
		return;

	if (m_bWinActive)
	{
		CWin* pWin = (CWin*)m_WinList.GetHead();
		if (pWin->IsShow())
		{
			pWin->Active(true);
			m_bWinActive = false;
		}
	}

	CInput& rInput = CInput::Instance();
	if (rInput.IsKeyDown(VK_ESCAPE))
	{
		m_bSysMenuWinShow = !m_bSysMenuWinShow;
	}
	
	CWin* pWin;
	NODE* position;

	m_bCursorOnUI = false;	// ������ ���� Ŀ���� �ִ��� ���� �ʱ�ȭ.

// 1. Ŭ�� �� �����츦 �������� ���ο� ���� ������ Ȱ��ȭ ó��.
	if (rInput.IsLBtnDn())	// ���콺 ���� ��ư�� �����°�?
	{
		bool bWinClick = false;
		position = m_WinList.GetHeadPosition();	// list�� Head���� �˻�.
		while (position)	// position�� NULL�� ������ �ݺ�.
		{
			// �� position�� ���� ��� �� position�� ���� position����.
			pWin = (CWin*)m_WinList.GetNext(position);
			// �� window�� ���̴� ���¿��� �� window�� Ŭ���� �ߴ°�?
			if (pWin->CursorInWin(WA_ALL))
			{
				SetActiveWin(pWin);		// �� window�� Active.
				bWinClick = true;		// window�� Ŭ�� ����.
				break;		// while ������ ��������.
			}
		}

		if (!bWinClick)		// window�� Ŭ������ �ʾҴ°�?
		{
			// �켱 ������ Active���� window�� ��Ȱ��ȭ ��Ŵ.
			// Active���� window�� �־��ٸ� list�� head�̹Ƿ� ������ ��Ȱ��ȭ.
			pWin = (CWin*)m_WinList.GetHead();
			pWin->Active(false);
		}
	}
	// ���콺 �� ��ư ���� ��츸 Ǯ����.
	else if (rInput.IsLBtnUp())
	{
		m_bBlockCharMove = false;
	}
// 2. ������ Update() �� ������ ���� ��ư Ȱ��ȭ �ʱ�ȭ.
	// ����Ʈ ������� �迭�� ���� �� ������Ʈ �� ��ư Ȱ��ȭ �ʱ�ȭ�� ��.
	// ����Ʈ ������� ������Ʈ�� ��� ������Ʈ ���� �ٸ� â�� ������ Ȱ��ȭ ��
	//�� ����Ʈ ������ �ٲ�� �Ǿ� ġ������ ���� �߻�.
	int nlist = m_WinList.GetCount();
	CWin** apTempWin = new (CWin*[nlist]);
 
	position = m_WinList.GetHeadPosition();
	for (int i = 0; i < nlist; ++i)
	{
		 apTempWin[i] = (CWin*)m_WinList.GetNext(position);
		 apTempWin[i]->ActiveBtns(false);
	}

	position = m_WinList.GetHeadPosition();
	while (position)	// position�� NULL�� ������ �ݺ�.
	{
		// �� position�� ���� ��� �� position�� ���� position����.
		pWin = (CWin*)m_WinList.GetNext(position);
		if (pWin->CursorInWin(WA_ALL))	// Ŀ���� �� ������ ���� �ִ°�?
		{
			// �� �������� ��ư���� Ȱ��ȭ.
			pWin->ActiveBtns(true);
			break;	// Ŀ���� ������ ���� ���� ��� �ٸ� ������� �˻����� ����.
		}
	}
 
#ifdef _VS2008PORTING
	for(int i = 0; i < nlist; ++i)
#else // _VS2008PORTING
	for(i = 0; i < nlist; ++i)
#endif // _VS2008PORTING
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
		apTempWin[i]->Update();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
		apTempWin[i]->Update(dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	}
 
#ifdef KJH_FIX_ARRAY_DELETE
	SAFE_DELETE_ARRAY(apTempWin);
#else // KJH_FIX_ARRAY_DELETE
	delete apTempWin;
#endif // KJH_FIX_ARRAY_DELETE

//	CheckKey();
	CheckDockWin();		// ������ ��ŷ üũ.

// 3. ������ ������Ʈ ���� ó��.(Ŀ�� ��� �ٲٱ�, ������ �� ��ư ó��.)
	position = m_WinList.GetHeadPosition();
	while (position)	// position�� NULL�� ������ �ݺ�.
	{
		// �� position�� ���� ��� �� position�� ���� position����.
		pWin = (CWin*)m_WinList.GetNext(position);

		switch (pWin->GetState())	// �� �������� ���´�?
		{
		case WS_ETC:			// ��Ÿ �۵� ��.
			m_bCursorOnUI = true;	// while (position)���� Ż��.
			break;

		case WS_MOVE:			// �̵� ��.
//			eCursorActType = CURSOR_M;
			m_bCursorOnUI = true;	// while (position)���� Ż��.
			break;

		case WS_EXTEND_UP:		// ��� ũ�� ���� ��.
//			eCursorActType = CURSOR_V;
			m_bCursorOnUI = true;	// while (position)���� Ż��.
			break;

		case WS_EXTEND_DN:		// �ϴ� ũ�� ���� ��.
//			eCursorActType = CURSOR_V;
			m_bCursorOnUI = true;	// while (position)���� Ż��.
			break;
		}

		if (m_bCursorOnUI)
			break;

		if (pWin->CursorInWin(WA_ALL))	// Ŀ���� �� ������ ���� �ִ°�?
		{
			m_bCursorOnUI = true;
			break;	// Ŀ���� ������ ���� ���� ��� �ٸ� ������� �˻����� ����.
		}	// if (pWin->CursorInWin()) ��.
	}	// while (position)	��.
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ������ �����ֱ� ��ư �� ������ ������.
//*****************************************************************************
void CUIMng::Render()
{
	if (UIM_SCENE_NONE == m_nScene)	// �����Ǿ� ���� �ʴٸ� ó������ ����.
		return;

	m_CharInfoBalloonMng.Render();

	CWin* pWin;
	// ���� ������ list ������ ����. ���� tail ���� ����.
	NODE* position = m_WinList.GetTailPosition();
	while (position)	// position�� NULL�� ������ �ݺ�.
	{
		// �� position�� ���� ��� �� position�� ���� position����.
		pWin = (CWin*)m_WinList.GetPrev(position);
		pWin->Render();
	}
}

//*****************************************************************************
// �Լ� �̸� : PopUpMsgWin()
// �Լ� ���� : �޽��� �����츦 ������.
// �Ű� ���� : nMsgCode	: �޽��� �ڵ�.
//*****************************************************************************
void CUIMng::PopUpMsgWin(int nMsgCode, char* pszMsg)
{
	if (UIM_SCENE_NONE == m_nScene || UIM_SCENE_TITLE == m_nScene
		|| UIM_SCENE_LOADING == m_nScene)
		return;

	if (UIM_SCENE_MAIN == m_nScene)	return;	// ���� ���ξ������� ������� ����.

#ifdef LJH_ADD_LOCALIZED_BTNS
	if (nMsgCode == MESSAGE_OTP_NOT_REGISTERED)	{
		m_LocalizedYESNOMsgWin.PopUp(nMsgCode, pszMsg);
	}
	else if (nMsgCode == MESSAGE_OTP_INCORRECT || nMsgCode == MESSAGE_OTP_INVALID_INFO) {
		m_LocalizedConfirmCancelMsgWin.PopUp(nMsgCode, pszMsg);
	}
	else {
		m_MsgWin.PopUp(nMsgCode, pszMsg);
	}
#else  //LJH_ADD_LOCALIZED_BTNS
	m_MsgWin.PopUp(nMsgCode, pszMsg);
#endif //LJH_ADD_LOCALIZED_BTNS
	
	
}

//*****************************************************************************
// �Լ� �̸� : PopUpMsgWin()
// �Լ� ���� : �޽��� �����츦 ������.
// �Ű� ���� : nMsgCode	: �޽��� �ڵ�.
//*****************************************************************************
void CUIMng::AddServerMsg(char* pszMsg)
{
	if (UIM_SCENE_CHARACTER != m_nScene)	// ĳ���� �������� ����.
		return;

	m_ServerMsgWin.AddMsg(pszMsg);
}
