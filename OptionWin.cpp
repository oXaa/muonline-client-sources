//*****************************************************************************
// File: OptionWin.cpp
//
// Desc: implementation of the COptionWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"

#include "OptionWin.h"
#include "Input.h"
#include "UIMng.h"

// �ؽ�Ʈ ������ ���� #include. �̤�
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzScene.h"
#include "DSPlaySound.h"
#include "UIControls.h"
#include "NewUISystem.h"


#define	OW_BTN_GAP		25		// ��ư �� ���� ��.
#define	OW_SLD_GAP		48		// �����̴� �� ���� ��.

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptionWin::COptionWin()
{

}

COptionWin::~COptionWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �ɼ�â ����.
//*****************************************************************************
void COptionWin::Create()
{
	CInput rInput = CInput::Instance();
	// ȭ�鿡 ������ ������ ������ �⺻ ������ ����.
	CWin::Create(rInput.GetScreenWidth(), rInput.GetScreenHeight());

// ��� ������ ����.(���� �̹����θ� ����.)
	SImgInfo aiiBack[WE_BG_MAX] = 
	{
		{ BITMAP_SYS_WIN, 0, 0, 128, 128 },		// �߾�
		{ BITMAP_OPTION_WIN, 0, 0, 213, 65 },	// ��
		{ BITMAP_SYS_WIN+2, 0, 0, 213, 43 },	// ��
		{ BITMAP_SYS_WIN+3, 0, 0, 5, 8 },		// ��
		{ BITMAP_SYS_WIN+4, 0, 0, 5, 8 }		// ��
	};
	m_winBack.Create(aiiBack, 1, 30);
	m_winBack.SetLine(30);	// ���� ����.

// ��ư ����.
	// �ݱ� ��ư ������ ������ ��ư.
	for (int i = 0; i <= OW_BTN_SLIDE_HELP; ++i)
	{
		m_aBtn[i].Create(16, 16, BITMAP_CHECK_BTN, 2, 0, 0, -1, 1, 1, 1);
		CWin::RegisterButton(&m_aBtn[i]);
	}

	// �ݱ� ��ư.
	DWORD adwBtnClr[4] = { CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0 };
	m_aBtn[OW_BTN_CLOSE].Create(108, 30, BITMAP_TEXT_BTN, 4, 2, 1);
	m_aBtn[OW_BTN_CLOSE].SetText(GlobalText[388], adwBtnClr);
	CWin::RegisterButton(&m_aBtn[OW_BTN_CLOSE]);

// �����̴� ����.
	SImgInfo iiThumb = { BITMAP_SLIDER, 0, 0, 13, 13 };
	SImgInfo iiBack = { BITMAP_SLIDER+2, 0, 0, 98, 13 };
	SImgInfo iiGauge = { BITMAP_SLIDER+1, 0, 0, 4, 7 };
	RECT rcGauge = { 3, 3, 95, 10 };	// ������ ����.
#ifdef _VS2008PORTING
	for (int i = 0; i < OW_SLD_MAX; ++i)
#else // _VS2008PORTING
	for (i = 0; i < OW_SLD_MAX; ++i)
#endif // _VS2008PORTING
		m_aSlider[i].Create(&iiThumb, &iiBack, &iiGauge, &rcGauge);
	m_aSlider[OW_SLD_EFFECT_VOL].SetSlideRange(9);
	m_aSlider[OW_SLD_RENDER_LV].SetSlideRange(4);

	// ��ġ ����.
	SetPosition((rInput.GetScreenWidth() - m_winBack.GetWidth()) / 2,
		(rInput.GetScreenHeight() - m_winBack.GetHeight()) / 2);

	UpdateDisplay();	// �ɼ� ������ �ݿ�.
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void COptionWin::PreRelease()
{
	m_winBack.Release();
	for (int i = 0; i < OW_SLD_MAX; ++i)
		m_aSlider[i].Release();
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
//			   (ȭ�� �󿡴� â�� �̵��ϴ°�ó�� �������� �⺻ â�� �̵��� ����)
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void COptionWin::SetPosition(int nXCoord, int nYCoord)
{
	m_winBack.SetPosition(nXCoord, nYCoord);

	int nBtnPosX = m_winBack.GetXPos() + 52;
	int nBtnGap = OW_BTN_GAP + m_aBtn[0].GetHeight();
	int nBtnPosBaseTop = m_winBack.GetYPos() + 52;
	for (int i = 0; i <= OW_BTN_SLIDE_HELP; ++i)
		m_aBtn[i].SetPosition(nBtnPosX, nBtnPosBaseTop + i * nBtnGap);

	m_aBtn[OW_BTN_CLOSE].SetPosition(m_winBack.GetXPos()
		+ (m_winBack.GetWidth() - m_aBtn[OW_BTN_CLOSE].GetWidth()) / 2,
		m_winBack.GetYPos() + 301);

//	int nSldPosX = m_winBack.GetXPos()
//		+ (m_winBack.GetWidth() - m_aSlider[0].GetWidth()) / 2;
	int nSldGap = OW_SLD_GAP + m_aSlider[0].GetHeight();
	int nSldPosBaseTop = m_aBtn[OW_BTN_SLIDE_HELP].GetYPos()
		+ m_aBtn[0].GetHeight() + OW_SLD_GAP;
#ifdef _VS2008PORTING
	for (int i = 0; i < OW_SLD_MAX; ++i)
#else // _VS2008PORTING
	for (i = 0; i < OW_SLD_MAX; ++i)
#endif // _VS2008PORTING
		m_aSlider[i].SetPosition(nBtnPosX, nSldPosBaseTop + i * nSldGap);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void COptionWin::Show(bool bShow)
{
	CWin::Show(bShow);

	m_winBack.Show(bShow);
	for (int i = 0; i < OW_BTN_MAX; ++i)
		m_aBtn[i].Show(bShow);
#ifdef _VS2008PORTING
	for (int i = 0; i < OW_SLD_MAX; ++i)
#else // _VS2008PORTING
	for (i = 0; i < OW_SLD_MAX; ++i)
#endif // _VS2008PORTING
		m_aSlider[i].Show(bShow);
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool COptionWin::CursorInWin(int nArea)
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
// �Լ� �̸� : UpdateDisplay()
// �Լ� ���� : ������ ������ â�� �ݿ���.
//*****************************************************************************
void COptionWin::UpdateDisplay()
{
	m_aBtn[OW_BTN_AUTO_ATTACK].SetCheck(g_pOption->IsAutoAttack());
	m_aBtn[OW_BTN_WHISPER_ALARM].SetCheck(g_pOption->IsWhisperSound());
	m_aBtn[OW_BTN_SLIDE_HELP].SetCheck(g_pOption->IsSlideHelp());
	m_aSlider[OW_SLD_EFFECT_VOL].SetSlidePos(g_pOption->GetVolumeLevel());
	m_aSlider[OW_SLD_RENDER_LV].SetSlidePos(g_pOption->GetRenderLevel());
}

//*****************************************************************************
// �Լ� �̸� : UpdateWhileActive()
// �Լ� ���� : ��Ƽ���� ���� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void COptionWin::UpdateWhileActive(double dDeltaTick)
{
	for (int i = 0; i < OW_SLD_MAX; ++i)
		m_aSlider[i].Update(dDeltaTick);

	if (m_aBtn[OW_BTN_AUTO_ATTACK].IsClick())
	{
		g_pOption->SetAutoAttack(m_aBtn[OW_BTN_AUTO_ATTACK].IsCheck());
	}
	else if (m_aBtn[OW_BTN_WHISPER_ALARM].IsClick())
	{
		g_pOption->SetWhisperSound( m_aBtn[OW_BTN_WHISPER_ALARM].IsCheck() );
	}
	else if (m_aBtn[OW_BTN_SLIDE_HELP].IsClick())
	{
		g_pOption->SetSlideHelp( m_aBtn[OW_BTN_SLIDE_HELP].IsCheck() );
	}
	else if (m_aBtn[OW_BTN_CLOSE].IsClick())
	{
		CUIMng::Instance().HideWin(this);
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
	// ȿ���� �����̴��� ��ȭ�� �ִ°�?
	else if (m_aSlider[OW_SLD_EFFECT_VOL].GetState())
	{
		int nSlidePos = m_aSlider[OW_SLD_EFFECT_VOL].GetSlidePos();

		if(g_pOption->GetVolumeLevel() != nSlidePos)
		{
			g_pOption->SetVolumeLevel(nSlidePos);
			::SetEffectVolumeLevel(g_pOption->GetVolumeLevel());
		}
	}
	// �������� �����̴��� ��ȭ�� �ִ°�?
	else if (m_aSlider[OW_SLD_RENDER_LV].GetState())
	{
		int nSlidePos = m_aSlider[OW_SLD_RENDER_LV].GetSlidePos();
		if(g_pOption->GetRenderLevel() != nSlidePos)
		{
			g_pOption->SetRenderLevel(nSlidePos);
		}
	}
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE))
	{
		::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.
		CUIMng::Instance().HideWin(this);
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void COptionWin::RenderControls()
{
	m_winBack.Render();	

	// ����.
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->RenderText(int(m_winBack.GetXPos() / g_fScreenRate_x),
		int((m_winBack.GetYPos() + 10) / g_fScreenRate_y),
		GlobalText[385], m_winBack.GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);	

	// üũ ��ư �ؽ�Ʈ.
	const char* apszBtnText[3] =
	{ GlobalText[386], GlobalText[387], GlobalText[919] };
	for (int i = 0; i <= OW_BTN_SLIDE_HELP; ++i)
	{
		g_pRenderText->RenderText(int((m_aBtn[i].GetXPos() + 24) / g_fScreenRate_x),
			int((m_aBtn[i].GetYPos() + 4) / g_fScreenRate_y), apszBtnText[i]);
	}

	// �����̴�.
	int nTextPosY;
	const char* apszSldText[OW_SLD_MAX] = { GlobalText[389], GlobalText[1840] };
	int anVal[OW_SLD_MAX] = { g_pOption->GetVolumeLevel(), g_pOption->GetRenderLevel() * 2 + 5};
	
	char szVal[3];
#ifdef _VS2008PORTING
	for (int i = 0; i < OW_SLD_MAX; ++i)	
#else // _VS2008PORTING
	for (i = 0; i < OW_SLD_MAX; ++i)
#endif // _VS2008PORTING
	{
		nTextPosY = int((m_aSlider[i].GetYPos() - 18) / g_fScreenRate_y);
		g_pRenderText->RenderText(int(m_aSlider[i].GetXPos() / g_fScreenRate_x),
			nTextPosY, apszSldText[i]);

		::_itoa(anVal[i], szVal, 10);
		g_pRenderText->RenderText(int((m_aSlider[i].GetXPos() + 85)/ g_fScreenRate_x),
			nTextPosY, szVal);
		
		m_aSlider[i].Render();
	}

	CWin::RenderButtons();
}