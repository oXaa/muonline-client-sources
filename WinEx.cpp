//*****************************************************************************
// File: WinEx.cpp
//
// Desc: implementation of the CWinEx class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "WinEx.h"

#include "Input.h"
#include "Button.h"
#include "UsefulDef.h"

//#include "ZzzMathLib.h"
//#include "ZzzOpenglUtil.h"

#define	WE_CENTER_SPR_POS		3	// ��� �߾� ��������Ʈ ��� ��ġ.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinEx::CWinEx()
{

}

CWinEx::~CWinEx()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : Ȯ�� ������ ����.
// �Ű� ���� : aImgInfo		: WE_BG_MAX ���� SImgInfo�� �迭.
//							  ���� <�迭 ����> ����.
//			   nBgSideMin	: �¿��� ��������Ʈ �ּ� ����.
//			   nBgSideMax	: �¿��� ��������Ʈ �ִ� ����.
//
// <�迭 ����>
//#define	WE_BG_CENTER	0	// �߾� ���� ��Ʈ����Ʈ.
//#define	WE_BG_TOP		1	// ��� ���� ��������Ʈ.
//#define	WE_BG_BOTTOM	2	// �ϴ� ���� ��������Ʈ.
//#define	WE_BG_LEFT		3	// ���� ���� ��������Ʈ.
//#define	WE_BG_RIGHT		4	// ���� ���� ��������Ʈ.
//*****************************************************************************
void CWinEx::Create(SImgInfo* aImgInfo, int nBgSideMin, int nBgSideMax)
{
	Release();

	// �� ��� ��������Ʈ ����.
	CWin::m_psprBg = new CSprite[WE_BG_MAX];

	CWin::m_psprBg[WE_BG_CENTER].Create(aImgInfo, 0, 0, true);
	CWin::m_psprBg[WE_BG_TOP].Create(aImgInfo + 1);
	CWin::m_psprBg[WE_BG_BOTTOM].Create(aImgInfo + 2);
	CWin::m_psprBg[WE_BG_LEFT].Create(aImgInfo + 3, 0, 0, true);
	CWin::m_psprBg[WE_BG_RIGHT].Create(aImgInfo + 4, 0, 0, true);

	// ��� �߾� ��������Ʈ�� �ʺ� �°� �ø�.
	CWin::m_psprBg[WE_BG_CENTER].SetSize(CWin::m_psprBg[WE_BG_TOP].GetWidth()
		- WE_CENTER_SPR_POS * 2, 0, X);	

	CWin::m_ptPos.x = CWin::m_ptPos.y = 0;
	CWin::m_ptHeld = CWin::m_ptTemp = CWin::m_ptPos;
	CWin::m_bDocking = CWin::m_bActive = CWin::m_bShow = false;
	CWin::m_nState = WS_NORMAL;
	CWin::m_Size.cx = CWin::m_psprBg[WE_BG_TOP].GetWidth();
	CWin::m_Size.cy = CWin::m_psprBg[WE_BG_TOP].GetHeight()
		+ CWin::m_psprBg[WE_BG_BOTTOM].GetHeight()
		+ CWin::m_psprBg[WE_BG_LEFT].GetHeight();

	m_nBgSideNow = m_nBgSideMin = nBgSideMin;
	m_nBgSideMax = nBgSideMax;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : Ȯ�� ������ �޸𸮿��� ����.
//*****************************************************************************
void CWinEx::Release()
{
	PreRelease();	// �Ļ� Ŭ���� ������ ����� Release().

	// ��ư ����Ʈ�� ��� �Ǿ� �ִ� ��ư�� ������ ����Ʈ ����.
	CButton* pBtn;
	while (CWin::m_BtnList.GetCount())
	{
		pBtn = (CButton*)CWin::m_BtnList.RemoveHead();
		pBtn->Release();
	}

	SAFE_DELETE_ARRAY(CWin::m_psprBg);
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : Ȯ�� ������ ��ġ �̵�.
// �Ű� ���� : nXCoord	: X��ǥ.
//			   nYCoord	: Y��ǥ.
//*****************************************************************************
void CWinEx::SetPosition(int nXCoord, int nYCoord)
{
	CWin::m_psprBg[WE_BG_TOP].SetPosition(nXCoord, nYCoord);

	CWin::m_psprBg[WE_BG_CENTER].SetPosition(nXCoord + WE_CENTER_SPR_POS,
		nYCoord + WE_CENTER_SPR_POS);

	CWin::m_psprBg[WE_BG_LEFT].SetPosition(nXCoord,
		nYCoord + CWin::m_psprBg[WE_BG_TOP].GetHeight());

	CWin::m_psprBg[WE_BG_RIGHT].SetPosition(
		nXCoord + CWin::m_psprBg[WE_BG_TOP].GetWidth()
		- CWin::m_psprBg[WE_BG_RIGHT].GetWidth(),
		CWin::m_psprBg[WE_BG_LEFT].GetYPos());

	CWin::m_psprBg[WE_BG_BOTTOM].SetPosition(nXCoord,
		CWin::m_psprBg[WE_BG_LEFT].GetYPos()
		+ CWin::m_psprBg[WE_BG_LEFT].GetHeight());

	m_ptPos.x = nXCoord;
	m_ptPos.y = nYCoord;
}

//*****************************************************************************
// �Լ� �̸� : SetLine()
// �Լ� ���� : ������ ũ�� ����.
// �Ű� ���� : nLine	: �¿� �׵θ� ���� ��������Ʈ Ÿ�� ����.
//*****************************************************************************
int CWinEx::SetLine(int nLine)
{
	nLine = LIMIT(nLine, m_nBgSideMin, m_nBgSideMax);

	if (m_nBgSideNow == nLine)
		return m_nBgSideNow;

	int nOldLine = m_nBgSideNow;
	m_nBgSideNow = nLine;

	int nBgSideHeight
		= CWin::m_psprBg[WE_BG_LEFT].GetTexHeight() * m_nBgSideNow;

	CWin::m_psprBg[WE_BG_LEFT].SetSize(0, nBgSideHeight, Y);
	CWin::m_psprBg[WE_BG_RIGHT].SetSize(0, nBgSideHeight, Y);

	CWin::m_psprBg[WE_BG_BOTTOM].SetPosition(0,
		CWin::m_psprBg[WE_BG_LEFT].GetYPos()
		+ CWin::m_psprBg[WE_BG_LEFT].GetHeight(), Y);

	CWin::m_Size.cy = CWin::m_psprBg[WE_BG_TOP].GetHeight()
		+ CWin::m_psprBg[WE_BG_BOTTOM].GetHeight() + nBgSideHeight;

	CWin::m_psprBg[WE_BG_CENTER].SetSize(0,
		CWin::m_Size.cy - WE_CENTER_SPR_POS * 2, Y);

	return nOldLine;
}

//*****************************************************************************
// �Լ� �̸� : SetSize()
// �Լ� ���� : ������ ũ�� ����.
// �Ű� ���� : nHeight	: ���ϴ� ������ ����.(�ȼ� ����)
//*****************************************************************************
void CWinEx::SetSize(int nHeight)
{
	int nLine = (nHeight - CWin::m_psprBg[WE_BG_TOP].GetHeight()
		- CWin::m_psprBg[WE_BG_BOTTOM].GetHeight())
		/ CWin::m_psprBg[WE_BG_LEFT].GetTexHeight();

	SetLine(nLine);
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(WA_ALL, WA_MOVE, WA_EXTEND_UP,
//						 WA_EXTEND_DN �� �ϳ�)
//*****************************************************************************
bool CWinEx::CursorInWin(int nArea)
{
	if (!CWin::m_bShow)		// ������ �ʴ´ٸ� ó������ ����.
		return false;

	CInput& rInput = CInput::Instance();
	RECT rc = { 0, 0, 0, 0 };

	switch (nArea)
	{
	case WA_EXTEND_DN:
		::SetRect(&rc, CWin::m_ptPos.x, CWin::m_ptPos.y + CWin::m_Size.cy - 5,
			CWin::m_ptPos.x + CWin::m_Size.cx,
			CWin::m_ptPos.y + CWin::m_Size.cy);
		if (::PtInRect(&rc, rInput.GetCursorPos()))
			return true;
		break;

	case WA_EXTEND_UP:
		::SetRect(&rc, CWin::m_ptPos.x, CWin::m_ptPos.y,
			CWin::m_ptPos.x + CWin::m_Size.cx, CWin::m_ptPos.y + 4);
		if (::PtInRect(&rc, rInput.GetCursorPos()))
			return true;
		break;
	}

	return CWin::CursorInWin(nArea);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : ������ ���̱�.
// �Ű� ���� : bShow	: true�̸� ����. (�⺻�� true)
//******************************************************************************/
void CWinEx::Show(bool bShow)
{
	for (int i = 0; i < WE_BG_MAX; ++i)
		CWin::m_psprBg[i].Show(bShow);

	CWin::m_bShow = bShow;
	if (!CWin::m_bShow)		// ������ �ʴ´ٸ�.
		CWin::m_bActive = false;	// �׻� ��Ȱ��ȭ.
}

//*****************************************************************************
// �Լ� �̸� : CheckAdditionalState()
// �Լ� ���� : �߰� ������ ���� üũ.
//*****************************************************************************
void CWinEx::CheckAdditionalState()
{
	CInput& rInput = CInput::Instance();

	if (rInput.IsLBtnDn())	// ���콺 ��ư�� �����°�?
	{
		// ���� �ø�.
		if (CursorInWin(WA_EXTEND_UP))
		{
			// Top�� Bottom ��������Ʈ�� ���� ����� ���� Y��ġ.
			m_nBasisY = CWin::m_ptPos.y
				+ CWin::m_psprBg[WE_BG_LEFT].GetTexHeight() * m_nBgSideNow;
			CWin::m_nState = WS_EXTEND_UP;	// ���� �ø��� ������.
		}

		// �Ϸ� �ø�.
		if (CursorInWin(WA_EXTEND_DN))
		{
			// Top�� Bottom ��������Ʈ�� ���� ����� ���� �ٴ� Y��ġ.
			m_nBasisY = CWin::m_ptPos.y + CWin::m_psprBg[WE_BG_TOP].GetHeight()
				+ CWin::m_psprBg[WE_BG_BOTTOM].GetHeight();
			CWin::m_nState = WS_EXTEND_DN;	// �Ϸ� �ø��� ������.
		}
	}

	int nBgSideHeight;
	switch (CWin::m_nState)	// ������ ���´�?
	{
	case WS_EXTEND_UP:		// ���� ũ�� ���� ��.
		nBgSideHeight = m_nBasisY - rInput.GetCursorY();
		// nBgSideHeight�� 0�� �Ǹ� �ȵǹǷ� �ּ�ũ�� ����ó���� ��.
		if (nBgSideHeight
			< CWin::m_psprBg[WE_BG_LEFT].GetTexHeight() * m_nBgSideMin)
			SetLine(m_nBgSideMin);
		else
			SetLine(nBgSideHeight / CWin::m_psprBg[WE_BG_LEFT].GetTexHeight()
				+ 1);

		SetPosition(CWin::m_ptPos.x, m_nBasisY
			- CWin::m_psprBg[WE_BG_LEFT].GetTexHeight() * m_nBgSideNow);

		break;

	case WS_EXTEND_DN:		// �Ϸ� ũ�� ���� ��.
		nBgSideHeight = rInput.GetCursorY() - m_nBasisY;
		// nBgSideHeight�� 0�� �Ǹ� �ȵǹǷ� �ּ�ũ�� ����ó���� ��.
		if (nBgSideHeight
			< CWin::m_psprBg[WE_BG_LEFT].GetTexHeight() * m_nBgSideMin)
			SetLine(m_nBgSideMin);
		else
			SetLine(nBgSideHeight / CWin::m_psprBg[WE_BG_LEFT].GetTexHeight()
				+ 1);
	
		break;
	}
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : Ȯ�� ������ �׸���.
//*****************************************************************************
void CWinEx::Render()
{
	if (CWin::m_bShow)
	{
		for (int i = 0; i < WE_BG_MAX; ++i)
			CWin::m_psprBg[i].Render();

		RenderControls();
	}
}