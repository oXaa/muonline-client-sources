// PCRoomPoint.cpp: implementation of the CPCRoomPtSys class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PCRoomPoint.h"
#include "ZzzInterface.h"	// RenderText3() �Լ� ���.
#include "UsefulDef.h"		// ARGB() ���.
#include "UIManager.h"		// g_pUIManager ���.
#include "NewUISystem.h"	// g_pPartyInfoWindow

#ifdef ADD_PCROOM_POINT_SYSTEM

extern int GetScreenWidth();
extern int PartyNumber;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPCRoomPtSys::CPCRoomPtSys()
	: m_bPCRoom(false)
#ifndef KJH_DEL_PC_ROOM_SYSTEM		// #ifndef
		, m_nNowPt(0), m_nMaxPt(0), m_bPCRoomPtShopMode(false),
		m_byBuyItemPos(0xff)
#endif // KJH_DEL_PC_ROOM_SYSTEM
{

}

CPCRoomPtSys::~CPCRoomPtSys()
{

}

//*****************************************************************************
// �Լ� �̸� : Instance()
// �Լ� ���� : ��ü�� �� �ϳ��� ����.
//			  �� Ŭ������ �����ϱ� ���� �������̽���
//*****************************************************************************
CPCRoomPtSys& CPCRoomPtSys::Instance()
{
	static CPCRoomPtSys s_PCRoomPtSys;                  
    return s_PCRoomPtSys;
}

#endif //ADD_PCROOM_POINT_SYSTEM

