// PortalMgr.cpp: implementation of the CPortalMgr class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PortalMgr.h"

#ifdef YDG_ADD_CS5_PORTAL_CHARM

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int World;
const char* GetMapName( int iMap);
bool InChaosCastle(int iMap = World);
bool InBloodCastle(int iMap = World);
bool InDevilSquare();

#include "ZzzBMD.h"
#include "ZzzCharacter.h"

CPortalMgr g_PortalMgr;

CPortalMgr::CPortalMgr()
{
	Reset();
}

CPortalMgr::~CPortalMgr()
{
	Reset();
}

void CPortalMgr::Reset()
{
	ResetPortalPosition();
	ResetRevivePosition();
}

void CPortalMgr::ResetPortalPosition()
{
	m_iPortalWorld = -1;
	m_iPortalPosition_x = 0;
	m_iPortalPosition_y = 0;
}

void CPortalMgr::ResetRevivePosition()
{
	m_iReviveWorld = -1;
	m_iRevivePosition_x = 0;
	m_iRevivePosition_y = 0;
}

BOOL CPortalMgr::IsPortalUsable()
{
	// �̵� ������� �̵� ������ ���������� �̵��� ������ ����� �� �ִ�.
	switch(World)
	{
	case WD_6STADIUM:				// 6 �����
	case WD_0LORENCIA:				// 0 �η��þ�
	case WD_3NORIA:					// 3 �븮��
	case WD_51HOME_6TH_CHAR:		// 51 ��������
	case WD_2DEVIAS:				// 2 ����ƽ�
	case WD_1DUNGEON:				// 1 ����
	case WD_7ATLANSE:				// 7 ��Ʋ����
	case WD_4LOSTTOWER:				// 4 �ν�ƮŸ��
	case WD_8TARKAN:				// 8 Ÿ��ĭ.
	case WD_33AIDA:					// 33 ���̴�
	case WD_10HEAVEN:				// 10 ��ī�罺
	case WD_37KANTURU_1ST:			// 37 ĭ���� ����
	case WD_38KANTURU_2ND:			// 38 ĭ���� ����
#ifdef CSK_ADD_MAP_ICECITY
	case WD_57ICECITY:				// 57 ��Ŭ����
#endif // CSK_ADD_MAP_ICECITY
	case WD_56MAP_SWAMP_OF_QUIET:	// 56 ����� ��
		return TRUE;
	}
	return FALSE;
}

void CPortalMgr::SavePortalPosition()
{
	m_iPortalWorld = World;
	m_iPortalPosition_x = Hero->PositionX;
	m_iPortalPosition_y = Hero->PositionY;
}

void CPortalMgr::SaveRevivePosition()
{
	m_iReviveWorld = World;
	m_iRevivePosition_x = Hero->PositionX;
	m_iRevivePosition_y = Hero->PositionY;
}

BOOL CPortalMgr::IsPortalPositionSaved()
{
	return (m_iPortalWorld != -1);
}

BOOL CPortalMgr::IsRevivePositionSaved()
{
	return (m_iReviveWorld != -1);
}

void CPortalMgr::GetPortalPositionText(char * pszOut)
{
	if (pszOut == NULL) return;

	if (m_iPortalWorld == -1)
	{
		assert(!"�̵� ��ġ�� �������� ���� ������");
	}
	else
	{
		sprintf(pszOut, "%s (%d, %d)", GetMapName(m_iPortalWorld), m_iPortalPosition_x, m_iPortalPosition_y);
	}
}

void CPortalMgr::GetRevivePositionText(char * pszOut)
{
	if (pszOut == NULL) return;

	if (m_iReviveWorld == -1)
	{
		assert(!"�̵� ��ġ�� �������� ���� ������");
	}
	else
	{
		sprintf(pszOut, "%s (%d, %d)", GetMapName(m_iReviveWorld), m_iRevivePosition_x, m_iRevivePosition_y);
	}
}

#endif	// YDG_ADD_CS5_PORTAL_CHARM