//*****************************************************************************
// File: ServerSelWin.h
//
// Desc: interface for the CServerSelWin class.
//		 ���� ���� â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_SERVERSELWIN_H__E3C0BEAA_B9CF_42C4_964F_A5339999BA7B__INCLUDED_)
#define AFX_SERVERSELWIN_H__E3C0BEAA_B9CF_42C4_964F_A5339999BA7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"

#include "Button.h"
#include "GaugeBar.h"
#include "WinEx.h"

#define SSW_SERVER_G_MAX	21	// ���� �׷� �ִ� ����.
#define SSW_SERVER_MAX		16	// �׷쳻 ���� �ִ� ����.
#define SSW_DESC_LINE_MAX	2	// ���� ���� �� ��.
#define SSW_DESC_ROW_MAX	83	// ���ٿ� �ִ� ����(byte)�� + 1

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
#define SSW_LEFT_SERVER_G_MAX	10	// ���� ���� �ִ� ����
#define SSW_RIGHT_SERVER_G_MAX	10	// ���� ���� �ִ� ����
#endif // KJH_ADD_SERVER_LIST_SYSTEM

class CServerGroup;

class CServerSelWin : public CWin
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
private:
	enum SERVER_SELECT_WIN
	{
		SERVER_GROUP_BTN_WIDTH	= 108,
		SERVER_GROUP_BTN_HEIGHT = 26,
		SERVER_BTN_WIDTH		= 193,
		SERVER_BTN_HEIGHT		= 26,
	};

protected:
	CButton		m_aServerGroupBtn[SSW_SERVER_G_MAX];	// ���� �׷� ��ư.
	CButton		m_aServerBtn[SSW_SERVER_MAX];			// ���� ��ư.
	CGaugeBar	m_aServerGauge[SSW_SERVER_MAX];			// ���� ȥ�� ������.
	CSprite		m_aBtnDeco[2];					// ��� ��������Ʈ �¿�.
	CSprite		m_aArrowDeco[2];				// ȭ��ǥ ��������Ʈ �¿�.
	CWinEx		m_winDescription;				// ���� ���� ���.

	int			m_icntServerGroup;				// �����׷� ����
	int			m_icntLeftServerGroup;			// ���� ���� �׷� ����
	int			m_icntRightServerGroup;			// ������ �����׷� ����
	int			m_icntServer;					// ���� ���õ� �����׷��� ���� ����
	bool		m_bTestServerBtn;				// �׽�Ʈ ���� ��ư�� �ִ°�?
	
	int				m_iSelectServerBtnIndex;	// ���õ� ������ư �ε���
	CServerGroup*	m_pSelectServerGroup;		// ���õ� �����׷�
	
	unicode::t_char		m_szDescription[SSW_DESC_LINE_MAX][SSW_DESC_ROW_MAX];	// ���� ���� ���ڿ�.
#else // KJH_ADD_SERVER_LIST_SYSTEM
protected:
	CButton		m_abtnServerG[SSW_SERVER_G_MAX];// ���� �׷� ��ư.
	CButton		m_abtnServer[SSW_SERVER_MAX];	// ���� ��ư.
	CGaugeBar	m_agbServer[SSW_SERVER_MAX];	// ���� ȥ�� ������.
	CSprite		m_asprDeco[2];					// ��� ��������Ʈ �¿�.
	CSprite		m_asprArrow[2];					// ȭ��ǥ ��������Ʈ �¿�.
	CWinEx		m_winDescBg;					// ���� ���� ���.
	char		m_aszDesc[SSW_DESC_LINE_MAX][SSW_DESC_ROW_MAX];// ���� ���� ���ڿ�.
	int			m_nServerGCount;				// ���� �׷� ����.
	int			m_nSelServerG;	// ���õ� ���� �׷� �ε���.(-1�̸� ���� ����)
	int			m_anServerListIndex[SSW_SERVER_G_MAX];// ���� �׷� ��ư�� ServerList[] �ε���.
#endif // KJH_ADD_SERVER_LIST_SYSTEM

public:
	CServerSelWin();
	virtual ~CServerSelWin();

	void Create();
	void SetPosition(int nXCoord, int nYCoord);
	void UpdateDisplay();
	void Show(bool bShow);
	bool CursorInWin(int nArea);

protected:
	void PreRelease();
	void SetServerBtnPosition();
	void SetArrowSpritePosition();
	void ShowServerGBtns();
	void ShowDecoSprite();
	void ShowArrowSprite();
	void ShowServerBtns();

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive(double dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void RenderControls();
};

#endif // !defined(AFX_SERVERSELWIN_H__E3C0BEAA_B9CF_42C4_964F_A5339999BA7B__INCLUDED_)
