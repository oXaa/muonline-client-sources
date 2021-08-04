//*****************************************************************************
// File: Button.h
//
// Desc: interface for the CButton class.
//		 ��ư Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_BUTTON_H__7A986F2A_91A7_4525_8790_AC6C2E95AE63__INCLUDED_)
#define AFX_BUTTON_H__7A986F2A_91A7_4525_8790_AC6C2E95AE63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sprite.h"

// ��ư �̹��� ����.
#define	BTN_UP				0	// ���� ����.
#define	BTN_DOWN			1	// ���� ����.
#define	BTN_ACTIVE			2	// ���콺 Ŀ���� ��ư ���� �ִ� ����.
#define	BTN_DISABLE			3	// ��� �Ұ��� ����.
#define	BTN_UP_CHECK		4	// ���� �� ���� + üũ �� ����.
#define	BTN_DOWN_CHECK		5
#define	BTN_ACTIVE_CHECK	6
#define	BTN_DISABLE_CHECK	7
#define	BTN_IMG_MAX			8

class CButton : public CSprite  
{
protected:
	static	CButton*	m_pBtnHeld;		// ������ ��ư�� ������.

	bool	m_bEnable;					// ��밡������ ����.(���ο� ���� �ؽ�ó ��ȭ)
	bool	m_bActive;					// Ȱ��ȭ ����.(Ÿ �����쿡 ���� �κ��� ���콺 ��ǥ�� ��ģ�ٸ� �����ϸ� �ȵǹǷ� false���� ��.)
	bool	m_bClick;					// Ŭ���ΰ�?
	bool	m_bCheck;					// üũ�ΰ�?(üũ ��ư��)

	int		m_anImgMap[BTN_IMG_MAX];	// ��ư �̹��� ��.
	// üũ��ư ���δ� m_anImgMap[BTN_UP_CHECK]�� 0 �̻��̸� üũ ��ư��.

	char*	m_szText;					// ��ư���� ������ �ؽ�Ʈ ���ڿ�.
	DWORD*	m_adwTextColorMap;			// �ؽ�Ʈ �� ��.
	DWORD	m_dwTextColor;				// ���� �ؽ�Ʈ ��.
	float	m_fTextAddYPos;				// �ؽ�Ʈ Y ��ġ ���� ��.

public:
	CButton();
	virtual ~CButton();

	void Release();
	void Create(int nWidth, int nHeight, int nTexID, int nMaxFrame = 1,
		int nDownFrame = -1, int nActiveFrame = -1, int nDisableFrame = -1,
		int nCheckUpFrame = -1, int nCheckDownFrame = -1,
		int nCheckActiveFrame = -1, int nCheckDisableFrame = -1);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Update();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Update(double dDeltaTick = 0.0);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Render();
	void Show(bool bShow = true);
	BOOL CursorInObject();
	void SetEnable(bool bEnable = true) { m_bEnable = bEnable; }
	bool IsEnable(){ return m_bEnable; }
	void SetActive(bool bActive = true) { m_bActive = bActive; }
//	bool IsActive(){ return m_bActive; }
	bool IsClick(){ return m_bClick; }
	void SetCheck(bool bCheck = true) { m_bCheck = bCheck; }
	bool IsCheck(){ return m_bCheck; }
	void SetText(const char* pszText, DWORD* adwColor);
	char* GetText() const { return m_szText; }

protected:
	void ReleaseText();
};

#endif // !defined(AFX_BUTTON_H__7A986F2A_91A7_4525_8790_AC6C2E95AE63__INCLUDED_)
