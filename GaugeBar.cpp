//*****************************************************************************
// File: GaugeBar.cpp
//
// Desc: implementation of the CGaugeBar class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "GaugeBar.h"
#include "UsefulDef.h"
#include "Input.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGaugeBar::CGaugeBar()
{
	m_psprBack = NULL;
	m_psizeResponse = NULL;
}

CGaugeBar::~CGaugeBar()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �������� ����.
//			   ��� ��������Ʈ ���� ���� ����.
//			   nBackTexID�� -1�ϰ�� nBackWidth�� nBackHeight�� ���� �ִٸ�
//			  nBackWidth�� nBackHeight�� �������� ������ �νĵ�. nBackWidth��
//			  nBackHeight�� 0�� ��� prcGauge�� ������������ �νĵ�.
// �Ű� ���� : nGaugeWidth	: ������ ��������Ʈ �ȼ� �ʺ�.
//			   nGaugeHeight	: ������ ��������Ʈ �ȼ� ����.
//			   nGaugeTexID	: ������ �ؽ�ó ID.
//			   prcGauge		: ������ ���� RECT ���� �ּ�.(�⺻�� NULL)
//			   nBackWidth	: ��� ��������Ʈ �ʺ� ��� ���� ����.(�⺻�� 0)
//			   nBackHeight	: ��� ��������Ʈ ���� ��� ���� ����.(�⺻�� 0)
//			   nBackTexID	: ��� �ؽ�ó ID.(�⺻�� -1)
//			   bShortenLeft	: �������� �������� �پ��°�?(�⺻�� true)
//			   fScaleX		: X Ȯ��, ��� ����.(�⺻�� 1.0f)
//			   fScaleY		: Y Ȯ��, ��� ����.(�⺻�� 1.0f)
//*****************************************************************************
void CGaugeBar::Create(int nGaugeWidth, int nGaugeHeight, int nGaugeTexID,
					   RECT* prcGauge, int nBackWidth, int nBackHeight,
					   int nBackTexID, bool bShortenLeft, float fScaleX,
					   float fScaleY)
{
	Release();

	// �������� ��������Ʈ ����.
	int nSizingDatums
		= bShortenLeft ? SPR_SIZING_DATUMS_LT : SPR_SIZING_DATUMS_RT;

	m_sprGauge.Create(nGaugeWidth, nGaugeHeight, nGaugeTexID, 0, NULL, 0, 0,
		true, nSizingDatums, fScaleX, fScaleY);

	// ������ ������ NULL �̸� ��������Ʈ ũ��� ������ ������ ����.
	if (NULL == prcGauge)
	{
		RECT rc = { 0, 0, nGaugeWidth, nGaugeHeight };
		m_rcGauge = rc;
	}
	else
	{
		m_rcGauge = *prcGauge;
		// �������� ��������Ʈ ���� ����.
		m_sprGauge.SetSize(0, m_rcGauge.bottom - m_rcGauge.top, Y);
	}

	if (-1 < nBackTexID)	// ��� �ؽ�ó�� �ִ°�?
	{
		// �̰�쿣 this->m_prcResponse�� NULL��.
		m_psprBack = new CSprite;
		m_psprBack->Create(nBackWidth, nBackHeight, nBackTexID, 0, NULL, 0, 0,
			false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
	}
	// ��� �ؽ�ó�� ���ٸ� ��� ���� ������ �ִ°�?
	else if (0 < nBackWidth && 0 < nBackHeight)
	{
		// �� ��쿣 ��� �ؽ�ó ������� m_prcResponse�� ����.
		m_psizeResponse = new SIZE;
		m_psizeResponse->cx = nBackWidth;
		m_psizeResponse->cy = nBackHeight;
	}

	m_nXPos = m_nYPos = 0;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : ������ �� Release.
//*****************************************************************************
void CGaugeBar::Release()
{
	m_sprGauge.Release();
	if (m_psprBack)
	{ delete m_psprBack;	m_psprBack = NULL; }
	else if (m_psizeResponse)
	{ delete m_psizeResponse;	m_psizeResponse = NULL; }
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : ��ġ ����.
// �Ű� ���� : nXCoord		: X��ǥ.(��ũ�� ��ǥ.)
//			   nYCoord		: Y��ǥ.(��ũ�� ��ǥ.)
//*****************************************************************************
void CGaugeBar::SetPosition(int nXCoord, int nYCoord)
{
	if (m_psprBack)
		m_psprBack->SetPosition(nXCoord, nYCoord);

	m_sprGauge.SetPosition(nXCoord + m_rcGauge.left, nYCoord + m_rcGauge.top);

	m_nXPos = nXCoord;
	m_nYPos = nYCoord;
}

//*****************************************************************************
// �Լ� �̸� : GetWidth()
// �Լ� ���� : �ʺ� ����.
//*****************************************************************************
int CGaugeBar::GetWidth()
{
	if (m_psprBack)		// ��� ��������Ʈ�� �ִٸ�.
		return m_psprBack->GetWidth();

	if (m_psizeResponse)	// ���� ������ �ִٸ�.
		return m_psizeResponse->cx;

	// �� �� ���� ���ٸ� �������� ���� �ʺ� ����.
	return m_rcGauge.right - m_rcGauge.left;
}

//*****************************************************************************
// �Լ� �̸� : GetWidth()
// �Լ� ���� : ���̸� ����.
//*****************************************************************************
int CGaugeBar::GetHeight()
{
	if (m_psprBack)		// ��� ��������Ʈ�� �ִٸ�.
		return m_psprBack->GetHeight();

	if (m_psizeResponse)	// ���� ������ �ִٸ�.
		return m_psizeResponse->cy;

	// �� �� ���� ���ٸ� �������� ���� ���� ����.
	return m_rcGauge.bottom - m_rcGauge.top;
}

//*****************************************************************************
// �Լ� �̸� : SetValue()
// �Լ� ���� : ���������� ��ġ�� ����.
// �Ű� ���� : dwNow	: ���� ��.
//			   dwTotal	: ��ü ��.
//*****************************************************************************
void CGaugeBar::SetValue(DWORD dwNow, DWORD dwTotal)
{
	dwTotal = (dwTotal < 1) ? 1 : dwTotal;
	dwNow = LIMIT(dwNow, 0, dwTotal);

	// �켱 dwNow�� ũ�⸦ �ȼ��� ���.
	int nNowSize = dwNow * (m_rcGauge.right - m_rcGauge.left) / dwTotal;

	// ���������� �پ��� Ÿ���ΰ�?
	if (IS_SIZING_DATUMS_R(m_sprGauge.GetSizingDatums()))
	{
		// ���� �׸� ���Ͽ��� �����ʿ� ������ ���� �� �����Ƿ�.
		nNowSize
			+= m_sprGauge.GetTexWidth() - (m_rcGauge.right - m_rcGauge.left);
	}

	m_sprGauge.SetSize(nNowSize, 0, X);
}

//*****************************************************************************
// �Լ� �̸� : CursorInObject()
// �Լ� ���� : �������� �ȿ� Ŀ���� ��ġ�ϸ� TRUE ����.
//*****************************************************************************
BOOL CGaugeBar::CursorInObject()
{
	if (!IsShow())
		return FALSE;

	if (m_psprBack)		// ��� ��������Ʈ�� �ִٸ�.
		return m_psprBack->CursorInObject();

	float fScaleX = m_sprGauge.GetScaleX();
	float fScaleY = m_sprGauge.GetScaleY();

	CInput& rInput = CInput::Instance();

	if (m_psizeResponse)	// ���� ������ �ִٸ�.
	{
		RECT rc = 
		{
			long(m_nXPos * fScaleX),
			long(m_nYPos * fScaleY),
			long((m_nXPos + m_psizeResponse->cx) * fScaleX),
			long((m_nYPos + m_psizeResponse->cy) * fScaleY)
		};
		return ::PtInRect(&rc, rInput.GetCursorPos());
	}

	// �� �� ���� ���ٸ� �������� �������� �Ǵ�.
	RECT rc = 
	{
		long(m_rcGauge.left * fScaleX),
		long(m_rcGauge.top * fScaleY),
		long(m_rcGauge.right * fScaleX),
		long(m_rcGauge.bottom * fScaleY)
	};
	::OffsetRect(&rc, m_nXPos, m_nYPos);
	return ::PtInRect(&rc, rInput.GetCursorPos());
}

//*****************************************************************************
// �Լ� �̸� : SetAlpha()
// �Լ� ���� : ���İ� ����.
// �Ű� ���� : byAlpha	: ���� ��.
//*****************************************************************************
void CGaugeBar::SetAlpha(BYTE byAlpha)
{
	if (m_psprBack)
		m_psprBack->SetAlpha(byAlpha);

	m_sprGauge.SetAlpha(byAlpha);
}

//*****************************************************************************
// �Լ� �̸� : SetColor()
// �Լ� ���� : �������� ��������Ʈ�� Į�� ����.
// �Ű� ���� : dwColor	: Į�� ��.
//*****************************************************************************
void CGaugeBar::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_sprGauge.SetColor(byRed, byGreen, byBlue);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : �������ٸ� ���̰� �ϰų� �Ⱥ��̰� ��.
// �Ű� ���� : bShow	: true�̸� ����.(�⺻�� true)
//*****************************************************************************
void CGaugeBar::Show(bool bShow)
{
	if (m_psprBack)
		m_psprBack->Show(bShow);
	m_sprGauge.Show(bShow);
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ����.
//*****************************************************************************
void CGaugeBar::Render()
{
	if (m_psprBack)
		m_psprBack->Render();
	m_sprGauge.Render();
}