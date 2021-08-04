//*****************************************************************************
// File: Slider.cpp
//
// Desc: implementation of the CSlider class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "Slider.h"

#include "GaugeBar.h"
#include "Input.h"

// �� ���� �Ǵ� ���� ������ ����� ���� �� ���.
#define SLD_FIRST_SLIDE_DELAY_TIME	500		// ù �����̵� �����ð�.
#define SLD_SLIDE_DELAY_TIME		50		// �����̵� �����ð�.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSlider::CSlider() : m_pGaugeBar(NULL), m_psprBack(NULL)
{

}

CSlider::~CSlider()
{
	SAFE_DELETE(m_pGaugeBar);
	SAFE_DELETE(m_psprBack);
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �����̴� ����.
// �Ű� ���� : piiThumb	: �� �̹��� ����.
//			   piiBack	: ��� �̹��� ����.
//						  ��� �̹����� ���� ������� �ʴ´ٸ� piiBack->nTexID
//						�� -1�� ���� ��� �̹����� ����� �̹����� �ʺ�� ����
//						�� piiBack->nWidth, piiBack->nHeight�� ä��.
//			   piiGauge	: ������ �̹��� ����.(�⺻�� NULL)
//						  ���� �������ٴ� ���� �����̴����� ����.
//			   prcGauge	: ��� �̹��� �������� ������ ����.(�⺻�� NULL)
//			   bVertical: ���� �����̴� �����̸� true. ���θ� false.
//						(�⺻��: false)
//*****************************************************************************
void CSlider::Create(SImgInfo* piiThumb, SImgInfo* piiBack, SImgInfo* piiGauge,
					 RECT* prcGauge, bool bVertical)
{
	m_btnThumb.Create(piiThumb->nWidth, piiThumb->nHeight, piiThumb->nTexID);

	SAFE_DELETE(m_pGaugeBar);
	SAFE_DELETE(m_psprBack);

	if (piiGauge)
	{
		m_pGaugeBar = new CGaugeBar;
		m_pGaugeBar->Create(
			piiGauge->nWidth, piiGauge->nHeight, piiGauge->nTexID, prcGauge,
			piiBack->nWidth, piiBack->nHeight, piiBack->nTexID);
	}
	else if (-1 < piiBack->nTexID)
	{
		m_psprBack->Create(piiBack);
	}

	m_bVertical = bVertical;
	m_byState = SLD_STATE_IDLE;
	m_nSlidePos = 0;
	m_nSlideRange = 1;
	m_ptPos.x = 0;
	m_ptPos.y = 0;
	m_dThumbMoveTime = 0.0;

	int nThumbRange;
	if (m_bVertical)	// ���� �����̴��ΰ�?
	{
		// Thumb�� ������ �� �ִ� ���� = ��ü ���� - �� ��ư ũ��.
		nThumbRange = piiBack->nHeight - m_btnThumb.GetHeight();

		m_Size.cx = m_btnThumb.GetWidth();
		m_Size.cy = piiBack->nHeight;
	}
	else
	{
		nThumbRange = piiBack->nWidth - m_btnThumb.GetWidth();

		m_Size.cx = piiBack->nWidth;
		m_Size.cy = m_btnThumb.GetHeight();
	}
	// Thumb�� ������ �� �ִ� ������ ������ 0, �ƴϸ� �״��.
	m_nThumbRange = nThumbRange < 0 ? 0 : nThumbRange;
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �����̴��� �޸𸮿��� ����.
//*****************************************************************************
void CSlider::Release()
{
	m_btnThumb.Release();
	SAFE_DELETE(m_pGaugeBar);
	SAFE_DELETE(m_psprBack);
}

//*****************************************************************************
// �Լ� �̸� : SetThumbPosition()
// �Լ� ���� : ������ �����̵� ��ġ(m_nSlidePos)�� ���� Thumb�� ��ġ��Ŵ.
//*****************************************************************************
void CSlider::SetThumbPosition()
{
	float fThumbPos;
	if (m_bVertical)	// ���� �����̴��ΰ�?
	{
		// Thumb�� ��ġ = �����̴��� ��ġ
		//+ Thumb�� �� ĭ �̵� ���� * �����̵� ��ġ.
		fThumbPos = float(m_ptPos.y)
			+ (float)m_nThumbRange / m_nSlideRange * m_nSlidePos;

		m_btnThumb.SetPosition(m_ptPos.x, (int)fThumbPos);
	}
	else				// ���� �����̴��̸�.
	{
		fThumbPos = float(m_ptPos.x)
			+ (float)m_nThumbRange / m_nSlideRange * m_nSlidePos;

		m_btnThumb.SetPosition((int)fThumbPos, m_ptPos.y);

		m_pGaugeBar->SetValue(m_nSlidePos, m_nSlideRange);
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : �����̴� ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�ѹ��� X��ǥ.
//			   nYCoord	: ��ũ�ѹ��� Y��ǥ.
//*****************************************************************************
void CSlider::SetPosition(int nXCoord, int nYCoord)
{
	m_ptPos.x = nXCoord;
	m_ptPos.y = nYCoord;

	SetThumbPosition();

	if (m_pGaugeBar)
		m_pGaugeBar->SetPosition(nXCoord, nYCoord);
	else if (m_psprBack)
		m_psprBack->SetPosition(nXCoord, nYCoord);
}

//*****************************************************************************
// �Լ� �̸� : SetSlideRange()
// �Լ� ���� : ǥ���� ��ü ���� ����.
// �Ű� ���� : nSlideRange	: ǥ���� ��ü ����.
//*****************************************************************************
void CSlider::SetSlideRange(int nSlideRange)
{
	m_nSlideRange = MAX(nSlideRange, 1);	// 1���� �۾Ƽ��� �ȵ�.

	SetThumbPosition();
}

//*****************************************************************************
// �Լ� �̸� : LineUp()
// �Լ� ���� : �����̵� ��ġ�� �ϳ� ���ҽ�Ű�� �̿� ���� Thumb��ġ ����.
//*****************************************************************************
void CSlider::LineUp()
{
	if (m_bVertical)	// ���� �����̴��ΰ�?
	{
		// Thumb�� y��ġ = �����̴��� ��ġ
		float fThumbYPos = float(m_ptPos.y)
			// + Thumb�� �� ĭ �̵��ϴ� ����.
			+ (float)m_nThumbRange / m_nSlideRange
			* --m_nSlidePos;	// * --�����̵� ��ġ.

		m_btnThumb.SetPosition(m_ptPos.x, (int)fThumbYPos);
	}
	else				// ���� �����̴��̸�.
	{
		// Thumb�� x��ġ = �����̴��� ��ġ
		float fThumbXPos = float(m_ptPos.x)
			// + Thumb�� �� ĭ �̵��ϴ� ����.
			+ (float)m_nThumbRange / m_nSlideRange
			* --m_nSlidePos;	// * --�����̵� ��ġ.

		m_btnThumb.SetPosition((int)fThumbXPos, m_ptPos.y);
		m_pGaugeBar->SetValue(m_nSlidePos, m_nSlideRange);
	}
}

//*****************************************************************************
// �Լ� �̸� : LineDown()
// �Լ� ���� : �����̵� ��ġ�� �ϳ� ������Ű�� �̿� ���� Thumb��ġ ����.
//*****************************************************************************
void CSlider::LineDown()
{
	float fThumbPos;

	if (m_bVertical)	// ���� �����̴��ΰ�?
	{
		// �ϳ� ���� ��Ų ���� ������ ��ġ��.
		if (++m_nSlidePos == m_nSlideRange)
			fThumbPos = float(m_ptPos.y + m_nThumbRange);
		else
			// Thumb�� y��ġ = �����̴��� ��ġ
			fThumbPos = float(m_ptPos.y)
			// + Thumb�� �� ĭ �̵��ϴ� ����.
				+ (float)m_nThumbRange / m_nSlideRange
				* m_nSlidePos;	// * �����̵� ��ġ.
		// ���� ���� �ϴ� ������ ���� ������ ��ġ�� �����ϸ� ���� ����� ��
		//�� ���� ���ش�.

		m_btnThumb.SetPosition(m_ptPos.x, (int)fThumbPos);
	}
	else				// ���� �����̴��̸�.
	{
		// �ϳ� ���� ��Ų ���� ������ ��ġ��.
		if (++m_nSlidePos == m_nSlideRange)
			fThumbPos = float(m_ptPos.x + m_nThumbRange);
		else
			// Thumb�� y��ġ = �����̴��� ��ġ
			fThumbPos = float(m_ptPos.x)
			// + Thumb�� �� ĭ �̵��ϴ� ����.
				+ (float)m_nThumbRange / m_nSlideRange
				* m_nSlidePos;	// * �����̵� ��ġ.
		// ���� ���� �ϴ� ������ ���� ������ ��ġ�� �����ϸ� ���� ����� ��
		//�� ���� ���ش�.

		m_btnThumb.SetPosition((int)fThumbPos, m_ptPos.y);
		m_pGaugeBar->SetValue(m_nSlidePos, m_nSlideRange);
	}
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : �����̴��� �ڵ� ó��.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
void CSlider::Update(double dDeltaTick)
{
	if (!m_btnThumb.IsShow())	// ������ ������ ����.
		return;

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	m_btnThumb.Update();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	m_btnThumb.Update(dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

	if (!m_btnThumb.IsEnable())	// ����� �� ������ ����.
		return;

	CInput& rInput = CInput::Instance();
	if (rInput.IsLBtnUp())	// ���콺 ��ư�� ���Ҵ°�?
	{
		SetThumbPosition();
		m_byState = SLD_STATE_IDLE;
	}

// ���� ���� �Ǵ� ���� ���� ������ ���� ���� ��ƾ.
	RECT rcUpperThumb, rcUnderThumb;
	if (m_bVertical)
	{
		// Thumb ���� �簢 ����.
		::SetRect(&rcUpperThumb, m_ptPos.x, m_ptPos.y,
			m_ptPos.x + m_Size.cx, m_btnThumb.GetYPos());
		// Thumb �Ʒ��� �簢 ����.
		::SetRect(&rcUnderThumb, m_ptPos.x,
			m_btnThumb.GetYPos() + m_btnThumb.GetHeight(),
			m_ptPos.x + m_Size.cx, m_ptPos.y + m_Size.cy);
	}
	else
	{
		// Thumb ���� �簢 ����.
		::SetRect(&rcUpperThumb, m_ptPos.x, m_ptPos.y,
			m_btnThumb.GetXPos(), m_ptPos.y + m_Size.cy);
		// Thumb ������ �簢 ����.
		::SetRect(&rcUnderThumb, m_btnThumb.GetXPos() + m_btnThumb.GetWidth(),
			m_ptPos.y, m_ptPos.x + m_Size.cx, m_ptPos.y + m_Size.cy);
	}

	// ���� Ŀ���� ��ġ.
	POINT ptCursor = rInput.GetCursorPos();
	// Ŀ���� Thumb ���� �簢 ������ ��ġ�ϴ°�?
	if (::PtInRect(&rcUpperThumb, ptCursor))
	{
		m_dThumbMoveStartTime += dDeltaTick;
		if (rInput.IsLBtnHeldDn())	// ��ư�� ����� �����ߴ°�?
		{
			LineUp();
			m_byState |= SLD_STATE_UP;
			m_dThumbMoveStartTime = 0.0;
		}

		// Thumb�� �̵��ϱ� ������ �ķ� SLD_FIRST_SLIDE_DELAY_TIME ��ŭ ������
		//��?
		if (m_dThumbMoveStartTime >= SLD_FIRST_SLIDE_DELAY_TIME
			&& m_byState & SLD_STATE_UP)
		{
			m_dThumbMoveTime += dDeltaTick;

			// Up ��ư�� ����� ���� �� Thumb�� �̵��� ���� ��Ű�� ����
			//SLD_SLIDE_DELAY_TIME ��ŭ �ð��� ���� �� ���� �����̵�.
			// �� �����ð��� üũ���� ������ ���������� �ֻ�ܱ��� �̵��� ����.
			if (m_dThumbMoveTime >= SLD_SLIDE_DELAY_TIME)
			{
				LineUp();
				m_dThumbMoveTime = 0.0;
			}
		}
	}
	// Ŀ���� Thumb �Ʒ��� �簢 ������ ��ġ�ϴ°�?
	else if (::PtInRect(&rcUnderThumb, ptCursor))
	{
		m_dThumbMoveStartTime += dDeltaTick;
		if (rInput.IsLBtnHeldDn())	// ��ư�� ����� �����ߴ°�?
		{
			LineDown();	// �켱 �������� �ϳ� ������Ŵ.
			m_byState |= SLD_STATE_DN;
			m_dThumbMoveStartTime = 0.0;
		}

		// Thumb�� �̵��ϱ� ������ �ķ� SLD_FIRST_SLIDE_DELAY_TIME ��ŭ ������
		//��?
		if (m_dThumbMoveStartTime >= SLD_FIRST_SLIDE_DELAY_TIME
			&& m_byState & SLD_STATE_DN)
		{
			m_dThumbMoveTime += dDeltaTick;

			// Up ��ư�� ����� ���� �� Thumb�� �̵��� ���� ��Ű�� ����
			//SLD_SLIDE_DELAY_TIME ��ŭ �ð��� ���� �� ���� �����̵�.
			// �� �����ð��� üũ���� ������ ���������� ���ϴܱ��� �̵��� ����.
			if (m_dThumbMoveTime >= SLD_SLIDE_DELAY_TIME)
			{
				LineDown();
				m_dThumbMoveTime = 0.0;
			}
		}
	}

// Thumb �巡�� ó��.
	if (m_btnThumb.CursorInObject() && rInput.IsLBtnHeldDn())
	{
		if (m_bVertical)	// ���� �����̴��ΰ�?
		{
			// ���� Ŀ�� ��ġ ���.
			m_nCapturePos = ptCursor.y;
			// Thumb�� ���� ���� ���� ���� ���콺 Ŀ�� ��ġ.
			// ���� �ؿ� ���� ���� ��ġ�� �� ���� m_nThumbRange�� ���� ��.
			m_nLimitPos = m_ptPos.y + m_nCapturePos - m_btnThumb.GetYPos();
		}
		else				// ���� �����̴��̸�.
		{
			// ���� Ŀ�� ��ġ ���.
			m_nCapturePos = ptCursor.x;
			// Thumb�� ���� ���ʿ� ���� ���� ���콺 Ŀ�� ��ġ.
			// ���� �����ʿ� ���� ���� ��ġ�� �� ���� m_nThumbRange�� ���� ��.
			m_nLimitPos = m_ptPos.x + m_nCapturePos - m_btnThumb.GetXPos();
		}
		m_byState |= SLD_STATE_THUMB_DRG;
	}

	if (m_byState & SLD_STATE_THUMB_DRG)	// Thumb �巡�� ���ΰ�?
	{
		int nThumbPos;
		if (m_bVertical)	// ���� �����̴��ΰ�?
		{
		// Thumb�� ȭ�� ��ǥ �ٲٱ� �� Thumb�� �̵�.
			// ���� Thumb ��ġ�� Thumb �̵� ���� ���� �ֳ�?
			if (m_nLimitPos < ptCursor.y
				&& m_nLimitPos + m_nThumbRange > ptCursor.y)
			{
				// Thumb�� ��ġ�� ���콺 Ŀ���� �̵��� ��ŭ ����.
				nThumbPos = m_btnThumb.GetYPos()
					+ rInput.GetCursorY() - m_nCapturePos;
				// ���� Ŀ�� ��ġ�� ���� Ŀ�� ��ġ�� ���.
				m_nCapturePos = ptCursor.y;
			}
			// ���� Thumb ��ġ�� Thumb �̵� ���� ���� �ִ°�?
			else if (m_nLimitPos >= ptCursor.y)
			{
				// Thumb�� ��ġ�� �ֻ��.
				nThumbPos = m_ptPos.y;
				m_nCapturePos = m_nLimitPos;
			}
			else	// ���� Thumb ��ġ�� Thumb �̵� ���� �Ʒ��� �ִ°�?
			{
				nThumbPos = m_ptPos.y + m_nThumbRange;
				m_nCapturePos = m_nLimitPos + m_nThumbRange;
			}
			m_btnThumb.SetPosition(m_btnThumb.GetXPos(), nThumbPos);
			// Thumb�� ���� �̹����� �ٲ�.
//			m_btnThumb.SetAction(BTN_HIGHLIGHT_DOWN, BTN_HIGHLIGHT_DOWN);

		// m_nSlidePos ���ϱ�.
			// Thumb�� �� ĭ �̵��ϴ� ����.
			float fPixelPerPos = (float)m_nThumbRange / m_nSlideRange;
			m_nSlidePos = int((float(m_btnThumb.GetYPos() - m_ptPos.y)
				+ (fPixelPerPos / 2)) / fPixelPerPos);
		}
		else	// ���� �����̴��̸�.
		{
		// Thumb�� ȭ�� ��ǥ �ٲٱ� �� Thumb�� �̵�.
			// ���� Thumb ��ġ�� Thumb �̵� ���� ���� �ֳ�?
			if (m_nLimitPos < ptCursor.x
				&& m_nLimitPos + m_nThumbRange > ptCursor.x)
			{
				nThumbPos = m_btnThumb.GetXPos() + ptCursor.x - m_nCapturePos;
				// ���� Ŀ�� ��ġ�� ���� Ŀ�� ��ġ�� ���.
				m_nCapturePos = ptCursor.x;
			}
			// ���� Thumb ��ġ�� Thumb �̵� �������� ���� ���ʿ� �ִ°�?
			else if (m_nLimitPos >= ptCursor.x)
			{
				// Thumb�� ��ġ�� ���� ����.
				nThumbPos = m_ptPos.x;
				m_nCapturePos = m_nLimitPos;
			}
			else	// ���� Thumb ��ġ�� Thumb �̵� ���� ���� �����ʿ� �ִ°�?
			{
				nThumbPos = m_ptPos.x + m_nThumbRange;
				m_nCapturePos = m_nLimitPos + m_nThumbRange;
			}
			m_btnThumb.SetPosition(nThumbPos, m_btnThumb.GetYPos());
			// Thumb�� ���� �̹����� �ٲ�.
//			m_btnThumb.SetAction(BTN_HIGHLIGHT_DOWN, BTN_HIGHLIGHT_DOWN);

		// m_nSlidePos ���ϱ�.
			// Up�̳� Down��ư�� �� �� ���� �� Thumb�� �̵��ϴ� ����.
			float fPixelPerPos = (float)m_nThumbRange / m_nSlideRange;
			m_nSlidePos = int((float(m_btnThumb.GetXPos() - m_ptPos.x)
				+ (fPixelPerPos / 2)) / fPixelPerPos);

			m_pGaugeBar->SetValue(m_nSlidePos, m_nSlideRange);
		}	// if (m_bVertical) else�� ��.
	}
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ������.
//*****************************************************************************
void CSlider::Render()
{
	if (!m_btnThumb.IsShow())
		return;

	if (m_pGaugeBar)
		m_pGaugeBar->Render();
	else if (m_psprBack)
		m_psprBack->Render();
	m_btnThumb.Render();
}

//*****************************************************************************
// �Լ� �̸� : SetEnable()
// �Լ� ���� : �����̴� ��� ����/�Ұ��� ����.
// �Ű� ���� : bEnable	: true�̸� ��밡��.
//*****************************************************************************
void CSlider::SetEnable(bool bEnable)
{
	m_btnThumb.SetEnable(bEnable);

	if (!bEnable)
		m_byState = SLD_STATE_IDLE;
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : �����̴� ����/�Ⱥ��� ����.
// �Ű� ���� : bEnable	: true�̸� ������.
//*****************************************************************************
void CSlider::Show(bool bShow)
{
	m_btnThumb.Show(bShow);
	if (m_pGaugeBar)
		m_pGaugeBar->Show(bShow);
	else if (m_psprBack)
		m_psprBack->Show(bShow);
}

//*****************************************************************************
// �Լ� �̸� : CursorInSlider()
// �Լ� ���� : ���콺 Ŀ���� �����̴� ���� ������ TRUE ����.
//*****************************************************************************
BOOL CSlider::CursorInObject()
{
	if (m_btnThumb.IsShow())
	{
		RECT rcSlider = { m_ptPos.x, m_ptPos.y,
			m_ptPos.x + m_Size.cx, m_ptPos.y + m_Size.cy };
		return ::PtInRect(&rcSlider, CInput::Instance().GetCursorPos());
	}

	return FALSE;
}

//*****************************************************************************
// �Լ� �̸� : SetSlidePos()
// �Լ� ���� : �����̴� ���� ����.
// �Ű� ���� : nSlidePos	: �����̴� ��.
//*****************************************************************************
void CSlider::SetSlidePos(int nSlidePos)
{
	m_nSlidePos = LIMIT(nSlidePos, 0, m_nSlideRange);
	SetThumbPosition();
}