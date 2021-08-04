//*****************************************************************************
// File: CharSelMainWin.h
//
// Desc: interface for the CCharSelMainWin class.
//		 ĳ���� ���þ� ���� â Ŭ����.(ȭ�� �ϴ��� �޴�)
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_CHARSELMAINWIN_H__50FDE1CA_28E7_4709_A90A_726EDD2517C2__INCLUDED_)
#define AFX_CHARSELMAINWIN_H__50FDE1CA_28E7_4709_A90A_726EDD2517C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"
#include "Button.h"

#define	CSMW_SPR_DECO			0	// ���� ���.
#define	CSMW_SPR_INFO			1	// �ϴ� ���� ����.
#define	CSMW_SPR_MAX			2	// ��������Ʈ ����.

#define	CSMW_BTN_CREATE			0	// ĳ���� ���� ��ư.
#define	CSMW_BTN_MENU			1	// �޴� ��ư.
#define	CSMW_BTN_CONNECT		2	// ���� ���� ��ư.
#define	CSMW_BTN_DELETE			3	// ĳ���� ���� ��ư.
#define	CSMW_BTN_MAX			4	// ��ư ����.

class CCharSelMainWin : public CWin  
{
protected:
	CSprite	m_asprBack[CSMW_SPR_MAX];	// ��������Ʈ.
	CButton	m_aBtn[CSMW_BTN_MAX];		// ��ư.
	bool	m_bAccountBlockItem;		// ���� �� ������?
#ifdef KJH_MOD_NATION_LANGUAGE_REDEFINE
#ifdef TEENAGER_REGULATION
	short	m_nWarningText;				// ��� ���� ��ȣ.
#endif // TEENAGER_REGULATION
#else // KJH_MOD_NATION_LANGUAGE_REDEFINE
#if (SELECTED_LANGUAGE == LANGUAGE_KOREAN) && defined TEENAGER_REGULATION
	short	m_nWarningText;				// ��� ���� ��ȣ.
#endif	// (SELECTED_LANGUAGE == LANGUAGE_KOREAN) && defined TEENAGER_REGULATION
#endif // KJH_MOD_NATION_LANGUAGE_REDEFINE

public:
	CCharSelMainWin();
	virtual ~CCharSelMainWin();
	
	void Create();
	void SetPosition(int nXCoord, int nYCoord);
	void Show(bool bShow);
	bool CursorInWin(int nArea);
	void UpdateDisplay();

protected:
	void PreRelease();
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive(double dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void RenderControls();

	void DeleteCharacter();
};

#endif // !defined(AFX_CHARSELMAINWIN_H__50FDE1CA_28E7_4709_A90A_726EDD2517C2__INCLUDED_)
