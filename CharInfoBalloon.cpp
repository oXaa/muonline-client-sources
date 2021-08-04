//*****************************************************************************
// File: CharInfoBalloon.cpp
//
// Desc: implementation of the CCharInfoBalloon class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "CharInfoBalloon.h"
#include "ZzzOpenglUtil.h"
#include "ZzzInterface.h"
#include "UIControls.h"

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharInfoBalloon::CCharInfoBalloon() : m_pCharInfo(NULL)
{

}

CCharInfoBalloon::~CCharInfoBalloon()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ĳ���� ���� ǳ�� ����.
// �Ű� ���� : pCharInfo	: ��Ÿ�� ĳ������ ���� ������.
//*****************************************************************************
void CCharInfoBalloon::Create(CHARACTER* pCharInfo)
{
	CSprite::Create(118, 54, BITMAP_LOG_IN+7, 0, NULL, 59, 54);

	m_pCharInfo = pCharInfo;
	m_dwNameColor = 0;
	::memset(m_szName, 0, sizeof(char) * 64);
	::memset(m_szGuild, 0, sizeof(char) * 64);
	::memset(m_szClass, 0, sizeof(char) * 64);
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ĳ���� ���� ǳ�� ����.
//*****************************************************************************
void CCharInfoBalloon::Render()
{
	if (NULL == m_pCharInfo || !CSprite::m_bShow)
		return;

	CSprite::Render();

	// ĳ���� �Ӹ� �� ��ũ�� ��ǥ ���.(�� ������ ����� �� �ۿ� ����...�̤�)
	vec3_t afPos;
	VectorCopy(m_pCharInfo->Object.Position, afPos);
#ifdef PBG_ADD_NEWLOGO_IMAGECHANGE
	afPos[2] += 350.f;
#else //PBG_ADD_NEWLOGO_IMAGECHANGE
	afPos[2] += 280.f;
#endif //PBG_ADD_NEWLOGO_IMAGECHANGE
	int nPosX, nPosY;
	::Projection(afPos, &nPosX, &nPosY);

	CSprite::SetPosition(int(nPosX * g_fScreenRate_x),
		int(nPosY * g_fScreenRate_y));

	g_pRenderText->SetFont(g_hFixFont);	

	int nTextPosX = int(CSprite::GetXPos() / g_fScreenRate_x);
	// ĳ���� �̸�.
	g_pRenderText->SetBgColor(0);
	g_pRenderText->SetTextColor(m_dwNameColor);
	g_pRenderText->RenderText(nTextPosX, int((CSprite::GetYPos() + 7) / g_fScreenRate_y),
		m_szName, CSprite::GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);

	// ��� ��å.
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->RenderText(nTextPosX, int((CSprite::GetYPos() + 23) / g_fScreenRate_y),
		m_szGuild, CSprite::GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);
	
	// Ŭ����, ����.
	g_pRenderText->SetTextColor(CLRDW_BR_ORANGE);
#ifdef KJH_MOD_NATION_LANGUAGE_REDEFINE
#ifdef _LANGUAGE_KOR
	g_pRenderText->RenderText(nTextPosX, int((CSprite::GetYPos() + 39) / g_fScreenRate_y),
		m_szClass, (CSprite::GetWidth()) / g_fScreenRate_x, 0, RT3_SORT_CENTER);
#else // _LANGUAGE_KOR
	g_pRenderText->RenderText(nTextPosX-10, int((CSprite::GetYPos() + 39) / g_fScreenRate_y),
		m_szClass, (CSprite::GetWidth()+30) / g_fScreenRate_x, 0, RT3_SORT_CENTER);
#endif // _LANGUAGE_KOR
#else // KJH_MOD_NATION_LANGUAGE_REDEFINE
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	g_pRenderText->RenderText(nTextPosX, int((CSprite::GetYPos() + 39) / g_fScreenRate_y),
		m_szClass, (CSprite::GetWidth()) / g_fScreenRate_x, 0, RT3_SORT_CENTER);
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
	g_pRenderText->RenderText(nTextPosX-10, int((CSprite::GetYPos() + 39) / g_fScreenRate_y),
		m_szClass, (CSprite::GetWidth()+30) / g_fScreenRate_x, 0, RT3_SORT_CENTER);
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#endif // KJH_MOD_NATION_LANGUAGE_REDEFINE

	if (m_pCharInfo->CtlCode & CTLCODE_80MANAGER_MOVE_CHAR)
	{
		g_pRenderText->SetTextColor(255, 200, 180, 255);
 		
		for (int i = 0; i < 3; ++i)
		{
			if(i == 0)
			{
				g_pRenderText->SetFont(g_hFontBold);
			}
			else
			{
				g_pRenderText->SetFont(g_hFont);
			}
			g_pRenderText->RenderText(nTextPosX,
				int((CSprite::GetYPos() - 46 + i * 16) / g_fScreenRate_y),
				GlobalText[1241 + i], CSprite::GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : SetInfo()
// �Լ� ���� : Create()���� ���� ĳ���� ������ ����.
//*****************************************************************************
void CCharInfoBalloon::SetInfo()
{
	if (NULL == m_pCharInfo)
		return;

	// ĳ���Ͱ� ���ٸ� �������� ����.
	if (!m_pCharInfo->Object.Live)
	{
		CSprite::m_bShow = false;
		return;
	}

	CSprite::m_bShow = true;

	// ĳ���� �̸�.
	if (m_pCharInfo->CtlCode & CTLCODE_01BLOCKCHAR)		// ĳ���� ��
		m_dwNameColor = ARGB(255, 0, 255, 255);
	else if (m_pCharInfo->CtlCode
		& (CTLCODE_02BLOCKITEM | CTLCODE_10ACCOUNT_BLOCKITEM))// ������ ��
		m_dwNameColor = CLRDW_BR_ORANGE;
	else if (m_pCharInfo->CtlCode & CTLCODE_04FORTV)	// ��ۿ� ���� ĳ����
		m_dwNameColor = CLRDW_WHITE;
	else if (m_pCharInfo->CtlCode & CTLCODE_08OPERATOR)	// ��� ĳ����
		m_dwNameColor = ARGB(255, 255, 0, 0);
	else if (m_pCharInfo->CtlCode & CTLCODE_20OPERATOR)
		m_dwNameColor = ARGB(255, 255, 0, 0);
#ifdef LDK_FIX_GM_WEBZEN_NAME
	else if (FindText( m_pCharInfo->ID, "webzen" ))
		m_dwNameColor = ARGB(255, 255, 0, 0);
#endif //LDK_FIX_GM_WEBZEN_NAME
	else
		m_dwNameColor = CLRDW_WHITE;

	::strcpy(m_szName, m_pCharInfo->ID);

	// ��� ��å.
	int nText = 0;
	switch (m_pCharInfo->GuildStatus)
    {
    case 255:	nText = 488;	break;	// �Ϲ���.
    case 0:		nText = 1330;	break;	// ����.
    case 32:	nText = 1302;	break;	// ��Ʋ������.
    case 64:	nText = 1301;	break;	// �α�帶����.
    case 128:	nText = 1300;	break;	// ��帶����.	
    }
	::sprintf(m_szGuild, "(%s)", GlobalText[nText]);

	// Ŭ����.
	::sprintf(m_szClass, "%s %d", GetCharacterClassText(m_pCharInfo->Class), m_pCharInfo->Level);
}