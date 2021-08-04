//*****************************************************************************
// File: WinEx.h
//
// Desc: interface for the CWinEx class.
//		 Ȯ��(���Ϸ� �þ��) ������ class.(CWin���� ���)
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_WINEX_H__9E5A6837_4907_4DD0_95E8_14FFD2BF57DC__INCLUDED_)
#define AFX_WINEX_H__9E5A6837_4907_4DD0_95E8_14FFD2BF57DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"

#define	WINEX_BGSIDE_HEIGHT		8

#define	WE_BG_CENTER	0	// �߾� ���� ��Ʈ����Ʈ.
#define WE_BG_TOP		1	// ��� ���� ��������Ʈ.
#define	WE_BG_BOTTOM	2	// �ϴ� ���� ��������Ʈ.
#define	WE_BG_LEFT		3	// ���� ���� ��������Ʈ.
#define	WE_BG_RIGHT		4	// ���� ���� ��������Ʈ.
#define	WE_BG_MAX		5	// WinEx ���� ��������Ʈ �ִ� ����.

class CWinEx : public CWin  
{
protected:
	int			m_nBgSideMax;	// �¿��� ��������Ʈ�� �ִ� ����.
	int			m_nBgSideMin;	// �¿��� ��������Ʈ�� �ּ� ����.
	int			m_nBgSideNow;	// �¿��� ��������Ʈ�� ���� ����.

	int			m_nBasisY;		// ���� Y��ġ.

public:
	CWinEx();
	virtual ~CWinEx();
	
	void Create(SImgInfo* aImgInfo, int nBgSideMin, int nBgSideMax);
	void Release();
	void SetPosition(int nXCoord, int nYCoord);
	int SetLine(int nLine);
	void SetSize(int nHeight);
	bool CursorInWin(int nArea);
	void Show(bool bShow);
	void Render();

protected:
	void CheckAdditionalState();
};

#endif // !defined(AFX_WINEX_H__9E5A6837_4907_4DD0_95E8_14FFD2BF57DC__INCLUDED_)
