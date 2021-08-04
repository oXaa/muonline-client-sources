//*****************************************************************************
// File: GaugeBar.h
//
// Desc: interface for the CGaugeBar class.
//		 ������ �� class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_GAUGEBAR_H__FE749666_E447_4433_A5C1_B5F71F831CA0__INCLUDED_)
#define AFX_GAUGEBAR_H__FE749666_E447_4433_A5C1_B5F71F831CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sprite.h"

class CGaugeBar  
{
protected:
	CSprite		m_sprGauge;			// ������ ��������Ʈ.
	RECT		m_rcGauge;			// ������ ��ü ����.
	CSprite*	m_psprBack;			// ��� ��������Ʈ.
	SIZE*		m_psizeResponse;	// ���� ����.
	int			m_nXPos;			// X��ġ.
	int			m_nYPos;			// Y��ġ.

public:
	CGaugeBar();
	virtual ~CGaugeBar();

	void Create(int nGaugeWidth, int nGaugeHeight, int nGaugeTexID,
		RECT* prcGauge = NULL, int nBackWidth = 0, int nBackHeight = 0,
		int nBackTexID = -1, bool bShortenLeft = true, float fScaleX = 1.0f,
		float fScaleY = 1.0f);

	void Release();
	void SetPosition(int nXCoord, int nYCoord);
	int	GetXPos() { return m_nXPos; }
	int	GetYPos() { return m_nYPos; }
	int GetWidth();
	int GetHeight();
	void SetValue(DWORD dwNow, DWORD dwTotal);
	BOOL CursorInObject();
	void SetAlpha(BYTE dwAlpha);
	void SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue);
	void Show(bool bShow = true);
	bool IsShow() { return m_sprGauge.IsShow(); };
	void Render();
};

#endif // !defined(AFX_GAUGEBAR_H__FE749666_E447_4433_A5C1_B5F71F831CA0__INCLUDED_)
