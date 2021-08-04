// PCRoomPoint.h: interface for the CPCRoomPtSys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCROOMPOINT_H__6D2A3C64_DA4F_432E_86EB_A6AF35A8BFF6__INCLUDED_)
#define AFX_PCROOMPOINT_H__6D2A3C64_DA4F_432E_86EB_A6AF35A8BFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef ADD_PCROOM_POINT_SYSTEM

class CPCRoomPtSys  
{
protected:
	bool	m_bPCRoom;			// PC�� ����.
#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
	short	m_nNowPt;			// ���� ����Ʈ.
	short	m_nMaxPt;			// �ִ� ����Ʈ.
	
	bool	m_bPCRoomPtShopMode;// true�� ������ PC�� ����Ʈ ���� �����.
	BYTE	m_byBuyItemPos;		// ������ ������ ��ġ.
#endif // KJH_DEL_PC_ROOM_SYSTEM

protected:
	CPCRoomPtSys();

public:
	virtual ~CPCRoomPtSys();

	static CPCRoomPtSys& Instance();

	// PC�� ���� ����.
	void SetPCRoom(bool bPCRoom = true) { m_bPCRoom = bPCRoom; }
	bool IsPCRoom() { return m_bPCRoom; }		// PC���ΰ�?

#ifndef KJH_DEL_PC_ROOM_SYSTEM			// # ifndef
	void SetPoint(short nNowPt, short nMaxPt)	// PC�� ����Ʈ ����.
	{ m_nNowPt = nNowPt; m_nMaxPt = nMaxPt; }
	short GetNowPoint() { return m_nNowPt; }	// PC�� ���� ����Ʈ ���.
	short GetMaxPoint() { return m_nMaxPt; }	// PC�� �ִ� ����Ʈ ���.

	// PC�� ����Ʈ ���� ���� ����.
	void SetPCRoomPointShopMode(bool bMode = true)
	{ m_bPCRoomPtShopMode = bMode; }
	bool IsPCRoomPointShopMode()				// PC�� ����Ʈ �����ΰ�?
	{
#ifdef CSK_FIX_PCROOM_POINT_ZEN_BUG
		return m_bPCRoomPtShopMode;
#else // CSK_FIX_PCROOM_POINT_ZEN_BUG
		if (m_bPCRoom)
			return m_bPCRoomPtShopMode;
		return false;
#endif // CSK_FIX_PCROOM_POINT_ZEN_BUG
	}

	// PC�� ����Ʈ �������� ������ �������� ��ġ �ӽ� ����.
	void SetBuyItemPos(BYTE	byItemPos) { m_byBuyItemPos = byItemPos; }
	// PC�� ����Ʈ �������� ������ ������ ��ġ �ӽ� ���� �� ���.
	BYTE GetBuyItemPos() { return m_byBuyItemPos; }
#endif // KJH_DEL_PC_ROOM_SYSTEM
};

#endif // ADD_PCROOM_POINT_SYSTEM
#endif // !defined(AFX_PCROOMPOINT_H__6D2A3C64_DA4F_432E_86EB_A6AF35A8BFF6__INCLUDED_)
