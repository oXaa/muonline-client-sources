//*****************************************************************************
// File: Slider.h
//
// Desc: interface for the CSlider class.
//		 �����̴� ��Ʈ�� Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_SLIDER_H__51DCB080_BB6D_4486_BD3E_6A0CA739DD85__INCLUDED_)
#define AFX_SLIDER_H__51DCB080_BB6D_4486_BD3E_6A0CA739DD85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Button.h"

// m_byState����� ����Ǵ� ��.
#define SLD_STATE_IDLE				0x00	// �ƹ��͵� ����.
#define SLD_STATE_UP				0x01	// ����.
#define SLD_STATE_DN				0x02	// ������.
#define SLD_STATE_THUMB_DRG			0x10	// �� �巡��.

class CGaugeBar;

class CSlider  
{
protected:
	bool		m_bVertical;		// ���� �����̴����� ����.
	BYTE		m_byState;			// �۵� ����.

	POINT		m_ptPos;
	SIZE		m_Size;
	int			m_nSlideRange;		// �����̵� ����.
	int			m_nSlidePos;		// ���� �����̵� ��ġ.
	int			m_nThumbRange;		// Thumb�� ������ �� �ִ� ����.(�ȼ� ����.)
	CButton		m_btnThumb;			// Thumb.
	CGaugeBar*	m_pGaugeBar;		// ������ ��.(��� �̹����� ���� ��.)
	CSprite*	m_psprBack;			// ��� ��������Ʈ.(�������� ���� ��� �̹����� ���� �ִ� ���)

	double		m_dThumbMoveStartTime;	// Thumb�� �̵��ϱ� ������ �ð�.
	double		m_dThumbMoveTime;	// Thumb�� �̵����� ���� �ð�.
	int			m_nCapturePos;		// Thumb�� ������ �� ���콺 Ŀ�� ��ġ.
	int			m_nLimitPos;		// Thumb�� ���� ���� ���� �� ���콺 Ŀ�� ��ġ.

public:
	CSlider();
	virtual ~CSlider();

	void Create(SImgInfo* piiThumb, SImgInfo* piiBack, SImgInfo* piiGauge = NULL,
		RECT* prcGauge = NULL, bool bVertical = false);
	void Release();
	void SetPosition(int nXCoord, int nYCoord);
	int GetXPos() { return m_ptPos.x; }
	int GetYPos() { return m_ptPos.y; }
	int GetWidth() { return m_Size.cx; }
	int GetHeight() { return m_Size.cy; }
	void SetSlideRange(int nSlideRange);
	void Update(double dDeltaTick);
	void Render();
	void SetEnable(bool bEnable);
	bool IsEnable() { return m_btnThumb.IsEnable(); }
	void Show(bool bShow);
	bool IsShow() { return m_btnThumb.IsShow(); }
	BOOL CursorInObject();

	void SetSlidePos(int nSlidePos);
	int GetSlidePos() { return m_nSlidePos; }
	BYTE GetState() { return m_byState; }

protected:
	void SetThumbPosition();
	void LineUp();
	void LineDown();
};

#endif // !defined(AFX_SLIDER_H__51DCB080_BB6D_4486_BD3E_6A0CA739DD85__INCLUDED_)
