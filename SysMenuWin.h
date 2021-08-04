//*****************************************************************************
// File: SysMenuWin.h
//
// Desc: interface for the CSysMenuWin class.
//		 �ý��� �޴� â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_SYSMENUWIN_H__66B83E6D_1A2F_43FB_812F_78F24BB0EF6C__INCLUDED_)
#define AFX_SYSMENUWIN_H__66B83E6D_1A2F_43FB_812F_78F24BB0EF6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinEx.h"
#include "Button.h"

#define	SMW_BTN_GAME_END	0	// ���� ����.
#define	SMW_BTN_SERVER_SEL	1	// ���� ���� ������.
#define	SMW_BTN_OPTION		2	// �ɼ� â.
#define	SMW_BTN_CLOSE		3	// �ݱ�.
#define	SMW_BTN_MAX			4	// ��ư ����.

class CSysMenuWin : public CWin  
{
protected:
	CWinEx		m_winBack;			// ���.(��� �̹����θ� ���)
	CButton		m_aBtn[SMW_BTN_MAX];// ��ư��.

public:
	CSysMenuWin();
	virtual ~CSysMenuWin();

	void Create();
	void SetPosition(int nXCoord, int nYCoord);
	void Show(bool bShow);
	bool CursorInWin(int nArea);

protected:
	void PreRelease();
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void UpdateWhileActive(double dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void RenderControls();
};

#endif // !defined(AFX_SYSMENUWIN_H__66B83E6D_1A2F_43FB_812F_78F24BB0EF6C__INCLUDED_)
