//*****************************************************************************
// File: CharMakeWin.h
//
// Desc: interface for the CCharMakeWin class.
//		 ĳ���� ����â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_CHARMAKEWIN_H__7740CE2F_2BE7_4705_91DD_CCF55256B1D3__INCLUDED_)
#define AFX_CHARMAKEWIN_H__7740CE2F_2BE7_4705_91DD_CCF55256B1D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"
#include "Button.h"

#define	CMW_SPR_INPUT		0	// �̸� �Է� ��� ��������Ʈ.
#define	CMW_SPR_STAT		1	// �ɷ�ġ ��� ��������Ʈ.
#define	CMW_SPR_DESC		2	// ���� ���� ��� ��������Ʈ.
#define	CMW_SPR_MAX			3	// ��������Ʈ ����.

#define	CMW_DESC_LINE_MAX	2	// ���� ���� �� ��.
#define	CMW_DESC_ROW_MAX	75	// ���� ���� �� �� ���� ��.

class CCharMakeWin : public CWin  
{
protected:
	CWin	m_winBack;				// �ƹ��͵� �Ⱥ��̴� ��� ������.
	CSprite	m_asprBack[CMW_SPR_MAX];// ��������Ʈ.
	CButton	m_abtnJob[MAX_CLASS];	// ���� ��ư.
	CButton	m_aBtn[2];				// OK, Cancel ��ư.

	int		m_nSelJob;				// ���õ� ����.
	char	m_aszJobDesc[CMW_DESC_LINE_MAX][CMW_DESC_ROW_MAX];// ���� ����.
	int		m_nDescLine;			// ���� ���� ���� �� ��.

public:
	CCharMakeWin();
	virtual ~CCharMakeWin();

	void Create();
	void SetPosition(int nXCoord, int nYCoord);
	void Show(bool bShow);
	bool CursorInWin(int nArea);
	void UpdateDisplay();
#ifdef PJH_CHARACTER_RENAME
	bool ReName_Inter;
	void Set_State(bool Set = false);
#endif //PJH_CHARACTER_RENAME

protected:
	void PreRelease();
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive(double dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void RenderControls();

	void RequestCreateCharacter();

	void SelectCreateCharacter();
	void UpdateCreateCharacter();
	void RenderCreateCharacter();
};

#endif // !defined(AFX_CHARMAKEWIN_H__7740CE2F_2BE7_4705_91DD_CCF55256B1D3__INCLUDED_)
