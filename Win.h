//*****************************************************************************
// File: Win.h
//
// Desc: interface for the CWin class.
//		 ������ ���� class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_WIN_H__A06C4911_F775_4A87_97B9_42FE76BC1DEB__INCLUDED_)
#define AFX_WIN_H__A06C4911_F775_4A87_97B9_42FE76BC1DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIBaseDef.h"
#include "PList.h"
#include "Sprite.h"

// ������ ����.
#define	WS_NORMAL				0
#define	WS_ETC					1
#define	WS_MOVE					2
#define	WS_EXTEND_DN			3	// CWinEx��.
#define	WS_EXTEND_UP			4	// CWinEx��.

// ������ ���� ����
#define	WA_ALL					0
#define	WA_TOOLTIP				1
#define	WA_MOVE					2
#define	WA_BUTTON				3
#define	WA_EXTEND_DN			4	// CWinEx��.
#define	WA_EXTEND_UP			5	// CWinEx��.

class CSprite;
class CButton;

class CWin  
{
protected:
	POINT		m_ptHeld;			// Ŀ���� ���� ��� Ŀ�� ��ǥ.

	bool		m_bShow;			// ���̴��� ����.
	bool		m_bActive;			// Ȱ��ȭ ����.
	bool		m_bDocking;			// ��ŷ ����.
	int			m_nState;			// ������ ����.

	CSprite*	m_psprBg;			// ���� ��������Ʈ.
	POINT		m_ptPos;			// ������ ��ġ.
	SIZE		m_Size;				// ������ ũ��.
	POINT		m_ptTemp;			// �ӽ� ��ġ.(��ŷ �� ���)

	CPList		m_BtnList;			// �ڵ�ȭ�� ���� ��ư ������ ����Ʈ.

public:
	CWin();
	virtual ~CWin();

	void Create(int nWidth, int nHeight, int nTexID = -1, bool bTile = false);
	virtual void Release();
	virtual void SetPosition(int nXCoord, int nYCoord);
	int GetXPos(){ return m_ptPos.x; }
	int GetYPos(){ return m_ptPos.y; }
	void SetSize(int nWidth, int nHeight, CHANGE_PRAM eChangedPram = XY);
	int GetWidth(){ return m_Size.cx; }
	int GetHeight(){ return m_Size.cy; }
	int GetTempXPos(){ return m_ptTemp.x; }
	int GetTempYPos(){ return m_ptTemp.y; }
	virtual bool CursorInWin(int nArea);
	virtual void Show(bool bShow);
	bool IsShow(){ return m_bShow; }
	virtual void Active(bool bActive) { m_bActive = bActive; }
	bool IsActive(){ return m_bActive; }
	void SetDocking(bool bDocking) { m_bDocking = bDocking; }
//	bool IsDocking(){ return m_bDocking; }
	int GetState(){ return m_nState; }
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Update();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Update(double dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void Render();

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual int SetLine()			{ return 0; }
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual int SetLine(int nLine)	{ return 0; }
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void ActiveBtns(bool bActive);	// �Ļ� Ŭ�������� ������ �� �ʿ� ����. CUIMng������ ����.


	BYTE GetBgAlpha() {return m_psprBg->GetAlpha(); }
	void SetBgAlpha(BYTE byAlpha) { m_psprBg->SetAlpha(byAlpha); }
	void SetBgColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
	{ m_psprBg->SetColor(byRed, byGreen, byBlue); }

protected:
// �ʿ�� �Ļ� Ŭ�������� ������ �Լ�.(CCharSelMainWin�� �� �Լ� �ּ� ����)
	// �Ļ� Ŭ���� ������ ����� Release().
	virtual void PreRelease() {};
	// ��ư ���� üũ�� ��ư �� ���콺 Ŀ�� ��ȭ�� ������ ȿ���� �ֱ����� �� �Լ��� ������ ��.
	virtual bool CursorInButtonlike() { return false; }
	// ���� ���� ������Ʈ.(��Ƽ�� ���� ���ο� ���� ���� �κ� ó��.)
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void UpdateWhileShow()					{};
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void UpdateWhileShow(double dDeltaTick)	{};
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	// �߰� ������ ���� üũ.
	virtual void CheckAdditionalState() {};
	// ��Ƽ���� ���� ������Ʈ.
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void UpdateWhileActive()					{};
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void UpdateWhileActive(double dDeltaTick)	{};
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void RenderControls() {};

	void RegisterButton(CButton* pBtn);
	void RenderButtons();
};

#endif // !defined(AFX_WIN_H__A06C4911_F775_4A87_97B9_42FE76BC1DEB__INCLUDED_)
