//*****************************************************************************
// File: NewUIBattleSoccerScore.cpp
//
// Desc: implementation of the CNewUIBattleSoccerScore class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "NewUIBattleSoccerScore.h"
#include "UIControls.h"
#include "WSclient.h"
#include "ZzzBMD.h"
#include "ZzzCharacter.h"
#include "ZzzInventory.h"
#include "ZzzTexture.h"

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SEASON3B::CNewUIBattleSoccerScore::CNewUIBattleSoccerScore()
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
}

SEASON3B::CNewUIBattleSoccerScore::~CNewUIBattleSoccerScore()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : â ����.
// �Ű� ���� : pNewUIMng	: CNewUIManager ������Ʈ �ּ�.
//			   x			: x ��ǥ.
//			   y			: y ��ǥ.
//*****************************************************************************
bool SEASON3B::CNewUIBattleSoccerScore::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if (NULL == pNewUIMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_BATTLE_SOCCER_SCORE, this);

	SetPos(x, y);

	LoadImages();

	Show(false);	

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : â Release.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::Release()
{
	UnloadImages();

	if (m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPos()
// �Լ� ���� : â ��ġ ����.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

//*****************************************************************************
// �Լ� �̸� : UpdateMouseEvent()
// �Լ� ���� : ���콺 �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool SEASON3B::CNewUIBattleSoccerScore::UpdateMouseEvent()
{
	return true;
}

//*****************************************************************************
// �Լ� �̸� : UpdateKeyEvent()
// �Լ� ���� : Ű���� �Է� ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool SEASON3B::CNewUIBattleSoccerScore::UpdateKeyEvent()
{
	return true;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ��Ÿ �� ������ �Ͼ�� �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool SEASON3B::CNewUIBattleSoccerScore::Update()
{
	return true;
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : â ����.
// ��ȯ ��	 : true�� ����.
//*****************************************************************************
bool SEASON3B::CNewUIBattleSoccerScore::Render()
{
	::EnableAlphaTest();

	::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderBackImage();
	RenderContents();

	::DisableAlphaBlend();
	
	return true;
}

//*****************************************************************************
// �Լ� �̸� : RenderBackImage()
// �Լ� ���� : â ���� �̹��� ����.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::RenderBackImage()
{
	RenderImage(IMAGE_BSS_BACK,
		m_Pos.x, m_Pos.y, float(BSS_WIDTH), float(BSS_HEIGHT));
}

//*****************************************************************************
// �Լ� �̸� : RenderContents()
// �Լ� ���� : ���� ����.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::RenderContents()
{
	unicode::t_char szTemp[128];
	int nX = m_Pos.x + 30;
	int nY = m_Pos.y + 33;

	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetBgColor(0, 0, 0, 128);

	if (EnableGuildWar && Hero->GuildMarkIndex!=-1)
	{
		if (HeroSoccerTeam == 0)
			g_pRenderText->SetTextColor(255, 60, 0, 255);
		else
			g_pRenderText->SetTextColor(0, 150, 255, 255);

		unicode::_sprintf(szTemp, "%d", GuildWarScore[0]);
		g_pRenderText->RenderText(nX, nY, szTemp);				// ����
        ::CreateGuildMark(Hero->GuildMarkIndex);
        ::RenderBitmap(BITMAP_GUILD, float(nX+21), float(nY), 8, 8);// ��� ��ũ
		g_pRenderText->RenderText(nX+33, nY, GuildMark[Hero->GuildMarkIndex].GuildName);// ����

		if (HeroSoccerTeam == 0)
			g_pRenderText->SetTextColor(0, 150, 255, 255);
		else
			g_pRenderText->SetTextColor(255, 60, 0, 255);

		unicode::_sprintf(szTemp, "%d", GuildWarScore[1]);
		g_pRenderText->RenderText(nX, nY+22, szTemp);			// ����
        ::CreateGuildMark(FindGuildMark(GuildWarName));
        ::RenderBitmap(BITMAP_GUILD, float(nX+21), float(nY+22), 8, 8);// ��� ��ũ
		g_pRenderText->RenderText(nX+33, nY+22, GuildWarName);	// ����
	}
	else if (SoccerObserver)
	{
		g_pRenderText->SetTextColor(255, 60, 0, 255);
		unicode::_sprintf(szTemp, "%d", GuildWarScore[0]);
		g_pRenderText->RenderText(nX, nY, szTemp);
        ::CreateGuildMark(FindGuildMark(SoccerTeamName[0]));
        ::RenderBitmap(BITMAP_GUILD, float(nX+21), float(nY), 8, 8);
		g_pRenderText->RenderText(nX+33, nY, SoccerTeamName[0]);

		g_pRenderText->SetTextColor(0, 150, 255, 255);
		unicode::_sprintf(szTemp,"%d",GuildWarScore[1]);
		g_pRenderText->RenderText(nX, nY+22, szTemp);
        ::CreateGuildMark(FindGuildMark(SoccerTeamName[1]));
        ::RenderBitmap(BITMAP_GUILD, float(nX+21), float(nY+22), 8, 8);
		g_pRenderText->RenderText(nX+33, nY+22, SoccerTeamName[1]);
	}
}

//*****************************************************************************
// �Լ� �̸� : FindGuildMark()
// �Լ� ���� : �������� ��� ��ũ�� ã��.
// ��ȯ ��	 : ��帶ũ �ε���.
// �Ű� ���� : pszGuildName	: ����.
//*****************************************************************************
int SEASON3B::CNewUIBattleSoccerScore::FindGuildMark(char* pszGuildName)
{
	for (int i = 0; i < MARK_EDIT; ++i)
	{
		MARK_t *p = &GuildMark[i];
		if (strcmp(p->GuildName, pszGuildName) == NULL)
		{
			return i;
		}
	}
	return 0;
}

//*****************************************************************************
// �Լ� �̸� : GetLayerDepth()
// �Լ� ���� : â�� ���̾�� ����.
//*****************************************************************************
float SEASON3B::CNewUIBattleSoccerScore::GetLayerDepth()
{
	return 1.8f;
}

//*****************************************************************************
// �Լ� �̸� : LoadImages()
// �Լ� ���� : �̹��� ���ҽ� �ε�.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::LoadImages()
{
	LoadBitmap("Interface\\newui_Figure_ground.tga", IMAGE_BSS_BACK, GL_LINEAR);
}

//*****************************************************************************
// �Լ� �̸� : UnloadImages()
// �Լ� ���� : �̹��� ���ҽ� ����.
//*****************************************************************************
void SEASON3B::CNewUIBattleSoccerScore::UnloadImages()
{
	DeleteBitmap(IMAGE_BSS_BACK);
}
