//*****************************************************************************
// File: CreditWin.cpp
//
// Desc: implementation of the CCreditWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "CreditWin.h"
#include "Input.h"
#include "UIMng.h"

// PlayBuffer() �Լ� ����ϱ� ���� include.
#include "ZzzInfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "DSPlaySound.h"

// RenderText3() �Լ� ����ϱ� ���� include.
#include "ZzzCharacter.h"
#include "ZzzInterface.h"

#include "Local.h"
#include "./Utilities/Log/ErrorReport.h"
#include "wsclientinline.h"
#include "UIControls.h"

#define	CRW_ILLUST_FADE_TIME	2000.0	// ���� ������.
#define	CRW_ILLUST_SHOW_TIME	22000.0	// ���� �ִ� �ð�.

#define	CRW_TEXT_FADE_TIME		300.0	// �ؽ�Ʈ�� ��Ÿ���ų� ������� �ð�.
#define	CRW_NAME_SHOW_TIME		2300.0	// ���� �ִ� �ð�.

// ũ���� �ؽ�Ʈ ���� ���ϸ�.
#ifdef USE_CREDITTEST_BMD
#define	CRW_DATA_FILE		"Data\\Local\\credittest.bmd"
#else
#define	CRW_DATA_FILE		"Data\\Local\\credit.bmd"
#endif

extern float g_fScreenRate_x;
extern char* g_lpszMp3[NUM_MUSIC];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCreditWin::CCreditWin() : m_hFont(NULL)
{

}

CCreditWin::~CCreditWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ũ���� â ����.
//*****************************************************************************
void CCreditWin::Create()
{
	CInput rInput = CInput::Instance();

// �⺻ ������.
	CWin::Create(rInput.GetScreenWidth(), rInput.GetScreenHeight());
	CWin::SetBgAlpha(255);	// ��������.

// �� ��������Ʈ.
	// 800 * 600 ���� ��ũ�� ��带 ��� ��.
	float fScaleX = (float)rInput.GetScreenWidth() / 800.0f;
	float fScaleY = (float)rInput.GetScreenHeight() / 600.0f;

	m_aSpr[CRW_SPR_DECO].Create(189, 103, BITMAP_LOG_IN+6);
	m_aSpr[CRW_SPR_LOGO].Create(290, 41, BITMAP_LOG_IN+14, 0, NULL, 0, 0,
		false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);

	for (int i = CRW_SPR_TXT_HIDE0; i <= CRW_SPR_TXT_HIDE2; ++i)
	{
		m_aSpr[i].Create(800, 42, -1, 0, NULL, 0, 0, false,
			SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
		m_aSpr[i].SetColor(0, 0, 0);
	}

// �ݱ� ��ư.
	m_btnClose.Create(54, 30, BITMAP_BUTTON+2, 3, 2, 1);
	CWin::RegisterButton(&m_btnClose);

// �Ϸ���Ʈ.
	m_eIllustState = HIDE;

	m_apszIllustPath[0][0] = "Interface\\im1_1.jpg";
	m_apszIllustPath[0][1] = "Interface\\im1_2.jpg";
	m_apszIllustPath[1][0] = "Interface\\im2_1.jpg";
	m_apszIllustPath[1][1] = "Interface\\im2_2.jpg";
	m_apszIllustPath[2][0] = "Interface\\im3_1.jpg";
	m_apszIllustPath[2][1] = "Interface\\im3_2.jpg";
	m_apszIllustPath[3][0] = "Interface\\im4_1.jpg";
	m_apszIllustPath[3][1] = "Interface\\im4_2.jpg";
	m_apszIllustPath[4][0] = "Interface\\im5_1.jpg";
	m_apszIllustPath[4][1] = "Interface\\im5_2.jpg";
	m_apszIllustPath[5][0] = "Interface\\im6_1.jpg";
	m_apszIllustPath[5][1] = "Interface\\im6_2.jpg";
	m_apszIllustPath[6][0] = "Interface\\im7_1.jpg";
	m_apszIllustPath[6][1] = "Interface\\im7_2.jpg";
	m_apszIllustPath[7][0] = "Interface\\im8_1.jpg";
	m_apszIllustPath[7][1] = "Interface\\im8_2.jpg";

// �ؽ�Ʈ.
	int nFontSize = 10;
	switch(rInput.GetScreenWidth())
	{
	case 800 :	nFontSize = 14;	break;
	case 1024:	nFontSize = 18;	break;
	case 1280:	nFontSize = 24;	break;
	}
#ifdef KJH_MOD_NATION_LANGUAGE_REDEFINE
	m_hFont = ::CreateFont(nFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0,
		g_dwCharSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		GlobalText[0][0] ? GlobalText[0] : NULL);
#else // KJH_MOD_NATION_LANGUAGE_REDEFINE
	m_hFont = ::CreateFont(nFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0,
		g_dwCharSet[SELECTED_LANGUAGE], OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		GlobalText[0][0] ? GlobalText[0] : NULL);
#endif // KJH_MOD_NATION_LANGUAGE_REDEFINE

	LoadText();

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	SetPosition();	// �� ��Ʈ�� ��ġ�� ����ִ� �ǹ̿��� ȣ��.
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	SetPosition(0, 0);	// �� ��Ʈ�� ��ġ�� ����ִ� �ǹ̿��� ȣ��.
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void CCreditWin::PreRelease()
{
	for (int i = 0; i < CRW_SPR_MAX; ++i)
		m_aSpr[i].Release();

	if (m_hFont)
	{
		::DeleteObject((HGDIOBJ)m_hFont);
		m_hFont = NULL;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CCreditWin::SetPosition()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CCreditWin::SetPosition(int nXCoord, int nYCoord)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	m_aSpr[CRW_SPR_PIC_L].SetPosition(0, 126);
	m_aSpr[CRW_SPR_PIC_R].SetPosition(400, 126);
	m_aSpr[CRW_SPR_LOGO].SetPosition(241, 549);

	// ���� �ϴ� ���.
	CInput rInput = CInput::Instance();
	// 800*600 ��忡�� �Ϸ���Ʈ �عٴ� Y��ġ�� 527��.
	int nBaseY = int(527.0f / 600.0f * (float)rInput.GetScreenHeight());
	m_aSpr[CRW_SPR_DECO].SetPosition(
		rInput.GetScreenWidth() - m_aSpr[CRW_SPR_DECO].GetWidth(),
		nBaseY - m_aSpr[CRW_SPR_DECO].GetHeight());

	// �ؽ�Ʈ ������.
	for (int i = CRW_SPR_TXT_HIDE0; i <= CRW_SPR_TXT_HIDE2; ++i)
		m_aSpr[i].SetPosition(0, 42 * (i - CRW_SPR_TXT_HIDE0));

	// �ݱ� ��ư.
	m_btnClose.SetPosition(m_aSpr[CRW_SPR_DECO].GetXPos() + 122,
		m_aSpr[CRW_SPR_DECO].GetYPos() + 63);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CCreditWin::Show(bool bShow)
{
	CWin::Show(bShow);

	for (int i = 0; i < CRW_SPR_MAX; ++i)
		m_aSpr[i].Show(bShow);

	m_btnClose.Show(bShow);

	if (bShow)
		Init();
	else
		m_eIllustState = HIDE;
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool CCreditWin::CursorInWin(int nArea)
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
void CCreditWin::UpdateWhileActive(double dDeltaTick)
{
	if (m_btnClose.IsClick())
		CloseWin();
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE))
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		CloseWin();
		CUIMng::Instance().SetSysMenuWinShow(false);
	}

// �ؽ�Ʈ �� �Ϸ���Ʈ ��Ÿ���� ������� ȿ�� �ִϸ��̼�.
	for (int i = 0; i <= CRW_INDEX_NAME; ++i)
		AnimationText(i, dDeltaTick);
	AnimationIllust(dDeltaTick);
	
	/*
	if (::IsEndMp3())		// ���� �ݺ�.
	{
		::StopMp3(g_lpszMp3[MUSIC_MUTHEME]);
		::PlayMp3(g_lpszMp3[MUSIC_MUTHEME]);
	}
	*/
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void CCreditWin::RenderControls()
{
	::glDisable(GL_ALPHA_TEST);	// �Ϸ���Ʈ�� ���İ��� ������ �ƿ� �Ⱥ��̹Ƿ�.

	// ���, �ΰ� ��������Ʈ.
	for (int i = 0; i <= CRW_SPR_LOGO; ++i)
		m_aSpr[i].Render();

	long lScreenWidth = CInput::Instance().GetScreenWidth();
	int nTextBoxWidth;

	g_pRenderText->SetFont(m_hFont);
	g_pRenderText->SetTextColor(CLRDW_BR_GRAY);
	g_pRenderText->SetBgColor(0);
	
	// 1��°�� �ؽ�Ʈ.
	nTextBoxWidth = lScreenWidth / g_fScreenRate_x;

	g_pRenderText->RenderText(0, 20,
		m_aCredit[m_anTextIndex[CRW_INDEX_DEPARTMENT]].szName,
		nTextBoxWidth, 0, RT3_SORT_CENTER);
	
	// 2��°�� �ؽ�Ʈ.
	g_pRenderText->RenderText(0, 46, m_aCredit[m_anTextIndex[CRW_INDEX_TEAM]].szName,
		nTextBoxWidth, 0, RT3_SORT_CENTER);

	// 3��°�� �ؽ�Ʈ.
	g_pRenderText->SetTextColor(CLRDW_BR_YELLOW);
	
	switch (m_nNameCount)
	{
	case 1:
		g_pRenderText->RenderText(0, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME0]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		break;
	case 2:
		nTextBoxWidth = lScreenWidth / 4 / g_fScreenRate_x;
		g_pRenderText->RenderText(160, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME0]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(320, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME1]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		break;
	case 3:
		nTextBoxWidth = lScreenWidth / 3 / g_fScreenRate_x;
		g_pRenderText->RenderText(0, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME0]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(213, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME1]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(426, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME2]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		break;
	case 4:
		nTextBoxWidth = lScreenWidth / 4 / g_fScreenRate_x;
		g_pRenderText->RenderText(0, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME0]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(160, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME1]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(320, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME2]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		g_pRenderText->RenderText(480, 72, m_aCredit[m_anTextIndex[CRW_INDEX_NAME3]].szName,
			nTextBoxWidth, 0, RT3_SORT_CENTER);
		break;
	}

	// �ؽ�Ʈ ������ ��������Ʈ.
#ifdef _VS2008PORTING
	for (int i = CRW_SPR_TXT_HIDE0; i <= CRW_SPR_TXT_HIDE2; ++i)
#else // _VS2008PORTING
	for (i = CRW_SPR_TXT_HIDE0; i <= CRW_SPR_TXT_HIDE2; ++i)
#endif // _VS2008PORTING
		m_aSpr[i].Render();

	::glEnable(GL_ALPHA_TEST);	// ���� �׽�Ʈ �����·� ������.

	CWin::RenderButtons();
}

//*****************************************************************************
// �Լ� �̸� : CloseWin()
// �Լ� ���� : ũ���� â�� ����.
//*****************************************************************************
void CCreditWin::CloseWin()
{
	CUIMng::Instance().HideWin(this);

	// 5�� ���� �ƹ��� ���ϸ� �������� ��������� ������ ��������Ʈ�� ��û��.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
	SendRequestServerList2();
#else // PKD_ADD_ENHANCED_ENCRYPTION
	SendRequestServerList();
#endif // PKD_ADD_ENHANCED_ENCRYPTION

	::StopMp3(g_lpszMp3[MUSIC_MUTHEME]);
	::PlayMp3(g_lpszMp3[MUSIC_MAIN_THEME]);
}

//*****************************************************************************
// �Լ� �̸� : Init()
// �Լ� ���� : �Ϸ���Ʈ, �ؽ�Ʈ �ʱ�ȭ.
//*****************************************************************************
void CCreditWin::Init()
{
	// �Ϸ���Ʈ �ִ� �ʱ�ȭ.
	m_eIllustState = FADEIN;
	m_dIllustDeltaTickSum = 0.0;
	m_byIllust = 0;
	LoadIllust();

	// �ؽ�Ʈ �ִ� �ʱ�ȭ.
	for (int i = 0; i <= CRW_INDEX_NAME; ++i)
		m_aeTextState[i] = FADEIN;
	m_dTextDeltaTickSum = 0.0;
	m_nNowIndex = 0;
	m_nNameCount = 0;
	SetTextIndex();
}

//*****************************************************************************
// �Լ� �̸� : LoadIllust()
// �Լ� ���� : �Ϸ���Ʈ ������ �о� ��������Ʈ�� ������.
//*****************************************************************************
void CCreditWin::LoadIllust()
{
	CInput rInput = CInput::Instance();
	// 800 * 600 ���� ��ũ�� ��带 ��� ��.
	float fScaleX = (float)rInput.GetScreenWidth() / 800.0f;
	float fScaleY = (float)rInput.GetScreenHeight() / 600.0f;
	
	for (int i = 0; i < 2; ++i)
	{
		LoadBitmap(m_apszIllustPath[m_byIllust][i], BITMAP_TEMP+i, GL_LINEAR);
		
		m_aSpr[i].Create(400, 400, BITMAP_TEMP+i, 0, NULL, 0, 0,
			false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
		m_aSpr[i].SetAlpha(0);
		m_aSpr[i].Show(true);
	}

	m_aSpr[CRW_SPR_PIC_L].SetPosition(0, 126);
	m_aSpr[CRW_SPR_PIC_R].SetPosition(400, 126);
}

//*****************************************************************************
// �Լ� �̸� : AnimationIllust()
// �Լ� ���� : �Ϸ���Ʈ�� ������� ��Ÿ���� �Ϸ���Ʈ ��ü ó��.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void CCreditWin::AnimationIllust(double dDeltaTick)
{
	short nAlpha;
	switch (m_eIllustState)
	{
	case FADEIN:	// ������ ��Ÿ���� ���.
		nAlpha = short(m_aSpr[CRW_SPR_PIC_L].GetAlpha());
		nAlpha += short(255.0 * dDeltaTick / CRW_ILLUST_FADE_TIME);
		if (255 <= nAlpha)
		{
			m_eIllustState = SHOW;
			nAlpha = 255;
		}
		m_aSpr[CRW_SPR_PIC_L].SetAlpha((BYTE)nAlpha);
		m_aSpr[CRW_SPR_PIC_R].SetAlpha((BYTE)nAlpha);
		break;

	case SHOW:		// ������ ���̴� ���.
		m_dIllustDeltaTickSum += dDeltaTick;
		if (m_dIllustDeltaTickSum > CRW_ILLUST_SHOW_TIME)
		{
			m_eIllustState = FADEOUT;
			m_dIllustDeltaTickSum = 0.0;
		}
		break;

	case FADEOUT:	// ������ ������� ���.
		nAlpha = short(m_aSpr[CRW_SPR_PIC_L].GetAlpha());
		nAlpha -= short(255.0 * dDeltaTick / CRW_ILLUST_FADE_TIME);
		if (0 >= nAlpha)
		{
			m_eIllustState = FADEIN;
			nAlpha = 0;

			m_byIllust = ++m_byIllust == CRW_ILLUST_MAX ? 0 : m_byIllust;
			LoadIllust();
		}
		m_aSpr[CRW_SPR_PIC_L].SetAlpha((BYTE)nAlpha);
		m_aSpr[CRW_SPR_PIC_R].SetAlpha((BYTE)nAlpha);
		break;
	}
}

void BuxConvert(BYTE *Buffer, int Size);

//*****************************************************************************
// �Լ� �̸� : LoadText()
// �Լ� ���� : �ؽ�Ʈ ���� ������ ����.
//*****************************************************************************
void CCreditWin::LoadText()
{
	FILE *fp = ::fopen(CRW_DATA_FILE, "rb");
	if (fp == NULL)
	{
		char szMessage[256];
		::sprintf(szMessage, "%s file not found.\r\n", CRW_DATA_FILE);
		g_ErrorReport.Write(szMessage);
		::MessageBox(g_hWnd, szMessage, NULL, MB_OK);
		::PostMessage(g_hWnd, WM_DESTROY, 0, 0);
		return;
	}

	int nSize = sizeof(SCreditItem) * CRW_ITEM_MAX;
	::fread(m_aCredit, nSize, 1, fp);
	::BuxConvert((BYTE*)m_aCredit, nSize);

	::fclose(fp);
}

//*****************************************************************************
// �Լ� �̸� : SetTextIndex()
// �Լ� ���� : �ѹ��� ������ �ؽ�Ʈ�� ���� �ε����� ����.
//*****************************************************************************
void CCreditWin::SetTextIndex()
{
	if (0 == m_aCredit[m_nNowIndex].byClass)	// 0�̸� ����.
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		CloseWin();
	}

	if (1 == m_aCredit[m_nNowIndex].byClass)	// 1°�ٿ� �� �����ΰ�?
	{
		m_anTextIndex[CRW_INDEX_DEPARTMENT] = m_nNowIndex;
		++m_nNowIndex;
	}
	if (2 == m_aCredit[m_nNowIndex].byClass)	// 2°�ٿ� �� �����ΰ�?
	{
		m_anTextIndex[CRW_INDEX_TEAM] = m_nNowIndex;
		++m_nNowIndex;
	}
#ifdef _VS2008PORTING
	int iNameCnt = 0;
	for (int i = 0; i < 4; ++i)		// 3��°���� �ѹ��� �ִ� 4������ ǥ��.
	{
		iNameCnt = i;
		if (3 == m_aCredit[m_nNowIndex].byClass)// 3°�ٿ� �� �����ΰ�?
		{
			m_anTextIndex[CRW_INDEX_NAME0+i] = m_nNowIndex;
			++m_nNowIndex;
		}
		else
			break;
	}
	m_nNameCount = iNameCnt;	// 3°�ٿ� ǥ���� �׸� ����.
#else // _VS2008PORTING
	for (int i = 0; i < 4; ++i)		// 3��°���� �ѹ��� �ִ� 4������ ǥ��.
	{
		if (3 == m_aCredit[m_nNowIndex].byClass)// 3°�ٿ� �� �����ΰ�?
		{
			m_anTextIndex[CRW_INDEX_NAME0+i] = m_nNowIndex;
			++m_nNowIndex;
		}
		else
			break;
	}
	m_nNameCount = i;	// 3°�ٿ� ǥ���� �׸� ����.
#endif // _VS2008PORTING

}

//*****************************************************************************
// �Լ� �̸� : AnimationText()
// �Լ� ���� : �ؽ�Ʈ�� ������� ��Ÿ���� �ؽ�Ʈ ��ü ó��.
// �Ű� ���� : nClass		: �ִϸ��̼� ��ų �� ��ȣ(1~3)
//			   dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void CCreditWin::AnimationText(int nClass, double dDeltaTick)
{
	SHOW_STATE* peTextState = &m_aeTextState[nClass];
	short nAlpha;
	// �ؽ�Ʈ�� ������ �ִ� ��������Ʈ.
	CSprite* psprHide = &m_aSpr[CRW_SPR_TXT_HIDE0 + nClass];

	switch (*peTextState)
	{
	case FADEIN:	// ������ ��Ÿ���� ���.
		nAlpha = short(psprHide->GetAlpha());
		nAlpha -= short(255.0 * dDeltaTick / CRW_TEXT_FADE_TIME);
		if (0 >= nAlpha)
		{
			*peTextState = SHOW;
			nAlpha = 0;
		}
		psprHide->SetAlpha((BYTE)nAlpha);
		break;

	case SHOW:		// ������ ���̴� ���.
		if (nClass != CRW_INDEX_NAME)
			break;

		m_dTextDeltaTickSum += dDeltaTick;
		if (m_dTextDeltaTickSum > CRW_NAME_SHOW_TIME)
		{
			m_aeTextState[CRW_INDEX_NAME] = FADEOUT;
			m_dTextDeltaTickSum = 0.0;

			if (3 != m_aCredit[m_nNowIndex].byClass)	// 0 ~ 2��.
			{
				m_aeTextState[CRW_INDEX_TEAM] = FADEOUT;
				if (2 != m_aCredit[m_nNowIndex].byClass)// 0 ~ 1�̸�.
					m_aeTextState[CRW_INDEX_DEPARTMENT] = FADEOUT;
			}
		}
		break;

	case FADEOUT:	// ������ ������� ���.
		nAlpha = short(psprHide->GetAlpha());
		nAlpha += short(255.0 * dDeltaTick / CRW_TEXT_FADE_TIME);
		if (255 <= nAlpha)
		{
			*peTextState = FADEIN;
			nAlpha = 255;

			if (nClass == CRW_INDEX_NAME)
				SetTextIndex();
		}
		psprHide->SetAlpha((BYTE)nAlpha);
		break;
	}
}
