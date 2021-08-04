//*****************************************************************************
// File: Win.cpp
//
// Desc: implementation of the CWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "Win.h"

#include "Input.h"
#include "Button.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWin::CWin() : m_psprBg(NULL)
{

}

// �ڽ� �Ҹ��ڿ����� �ڽ� Ŭ���� ���� ���� �Ҵ�� �͸� ó���ϸ� ��.
CWin::~CWin()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ������ ����.
// �Ű� ���� : nWidth	: �ʺ�.(�ؽ�ó�� �ִٸ� �ؽ�ó�� �̹��� �ʺ�.)
//			   nHeight	: ����.(�ؽ�ó�� �ִٸ� �ؽ�ó�� �̹��� ����.)
//			   nTexID	: ������ �ؽ�ó ID.(�⺻�� -1)
//						  -2��� �ƹ��͵� ������ ���ϴ� ������.
//						  -1�̶�� �ؽ�ó ���� �ܻ� ������.
//			   bTile	: Ÿ�ϸ� ����.(�⺻�� false)
//*****************************************************************************
void CWin::Create(int nWidth, int nHeight, int nTexID, bool bTile)
{
	Release();

	if (-2 < nTexID)
	{
		m_psprBg = new CSprite;
		m_psprBg->Create(nWidth, nHeight, nTexID, 0, NULL, 0, 0, bTile);
		// �ؽ�ó ID�� -1�̸� ������ ������.
		if (-1 == nTexID)
		{
			m_psprBg->SetAlpha(128);
			m_psprBg->SetColor(0, 0, 0);
		}
	}

	m_ptPos.x = m_ptPos.y = 0;
	m_ptHeld = m_ptTemp = m_ptPos;
	m_Size.cx = nWidth;
	m_Size.cy = nHeight;
	m_bDocking = m_bActive = m_bShow = false;
	m_nState = WS_NORMAL;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : ������ �޸𸮿��� ����.
//*****************************************************************************
void CWin::Release()
{
	PreRelease();	// �Ļ� Ŭ���� ������ ����� Release().

	// ��ư ����Ʈ�� ��� �Ǿ� �ִ� ��ư�� ������ ����Ʈ ����.
	CButton* pBtn;
	while (m_BtnList.GetCount())
	{
		pBtn = (CButton*)m_BtnList.RemoveHead();
		pBtn->Release();
	}

	SAFE_DELETE(m_psprBg);
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : ������ ��ġ �̵�.
// �Ű� ���� : nXCoord	: X��ǥ.
//			   nYCoord	: Y��ǥ.
//*****************************************************************************
void CWin::SetPosition(int nXCoord, int nYCoord)
{
	m_ptPos.x = nXCoord;
	m_ptPos.y = nYCoord;
	if (m_psprBg)
		m_psprBg->SetPosition(nXCoord, nYCoord);
}

//*****************************************************************************
// �Լ� �̸� : SetSize()
// �Լ� ���� : ũ������ �������� ������ ũ�� ����.
// �Ű� ���� : nWidth		: �ʺ�.(�ȼ� ����.)
//			   nHeight		: ����.(�ȼ� ����.)
//			   eChangedPram	: ������ �Ķ����. X�� �ʺ�, Y�� ���̸�, XY�� ��
//							 �� ����.(�⺻�� XY)
//*****************************************************************************
void CWin::SetSize(int nWidth, int nHeight, CHANGE_PRAM eChangedPram)
{
	if (eChangedPram & X)	// ���� ũ�� �����ΰ�?
		m_Size.cx = nWidth;
	if (eChangedPram & Y)	// ���� ũ�� �����ΰ�?
		m_Size.cy = nHeight;

	if (m_psprBg)
		m_psprBg->SetSize(nWidth, nHeight, eChangedPram);
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(WA_ALL, WA_MOVE �� �ϳ�)
//*****************************************************************************
bool CWin::CursorInWin(int nArea)
{
	if (!m_bShow)		// ������ �ʴ´ٸ� ó������ ����.
		return false;

	CInput& rInput = CInput::Instance();
	RECT rc = { 0, 0, 0, 0 };
	NODE* position;
	CButton* pBtn;

	switch (nArea)
	{
	case WA_ALL:
		::SetRect(&rc, m_ptPos.x, m_ptPos.y, m_ptPos.x + m_Size.cx,
			m_ptPos.y + m_Size.cy);
		if (::PtInRect(&rc, rInput.GetCursorPos()))
			return true;
		break;

	case WA_MOVE:
		::SetRect(&rc, m_ptPos.x, m_ptPos.y, m_ptPos.x + m_Size.cx,
			m_ptPos.y + 26);
		if (::PtInRect(&rc, rInput.GetCursorPos()))
			return true;
		break;
	// ��ư ���� üũ ������ ������ ��ư ���� ���콺 Ŀ�� �̹��� ���濡�� ���.
	case WA_BUTTON:
		position = m_BtnList.GetHeadPosition();	// list�� Head���� �˻�.
		while (position)	// position�� NULL�� ������ �ݺ�.
		{
			// �� position�� ���� ��� �� position�� ���� position����.
			pBtn = (CButton*)m_BtnList.GetNext(position);
			if (pBtn->CursorInObject())
				return true;
		}
		if (CursorInButtonlike())
			return true;
		break;
	}

	return false;
}

void CWin::ActiveBtns(bool bActive)
{
	CButton* pBtn;
	NODE* position = m_BtnList.GetHeadPosition();	// list�� Head���� �˻�.
	while (position)	// position�� NULL�� ������ �ݺ�.
	{
		// �� position�� ���� ��� �� position�� ���� position����.
		pBtn = (CButton*)m_BtnList.GetNext(position);
		pBtn->SetActive(bActive);
	}
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : �����츦 ���̰� �Ⱥ��̰��� ����.
// �Ű� ���� : bShow	: true�̸� ������.(�⺻�� true)
//*****************************************************************************
void CWin::Show(bool bShow)
{
	if (m_psprBg)
		m_psprBg->Show(bShow);
	m_bShow = bShow;
	if (!m_bShow)		// ������ �ʴ´ٸ�.
		m_bActive = false;	// �׻� ��Ȱ��ȭ.
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ������ ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//							  (�⺻�� 0.0)
//*****************************************************************************
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CWin::Update()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CWin::Update(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	if (!m_bShow)	// ������ ������ ����.
		return;

	CInput& rInput = CInput::Instance();

	if (rInput.IsLBtnUp())	// ���콺 ��ư�� ���Ҵ°�?
		m_nState = WS_NORMAL;		// ���� ���·� �ʱ�ȭ.

	if (m_nState == WS_NORMAL)	// ���� ���¶�� �� ��ư Update().
	{
		CButton* pBtn;
		NODE* position = m_BtnList.GetHeadPosition();	// list�� Head���� �˻�.
		while (position)	// position�� NULL�� ������ �ݺ�.
		{
			// �� position�� ���� ��� �� position�� ���� position����.
			pBtn = (CButton*)m_BtnList.GetNext(position);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
			pBtn->Update();
#else //KWAK_FIX_COMPILE_LEVEL4_WARNING
			pBtn->Update(dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
		}
	}

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	UpdateWhileShow();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	UpdateWhileShow(dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

	if (!m_bActive)	// ��Ȱ��ȭ�̸� ����.
		return;

	// �̵�.
	if (rInput.IsLBtnDn())// ���콺 ��ư�� �����°�?
	{
		if (CursorInWin(WA_MOVE))	// �̵���ų �� �ִ� ������ �����°�?
		{
			// ���� Ŀ�� ��ġ ���.
			m_ptHeld = rInput.GetCursorPos();
			m_ptTemp = m_ptPos;
			m_nState = WS_MOVE;		// �̵� ������.
		}
	}

	if (WS_MOVE == m_nState)		// �̵������ΰ�?
	{
		// ��ȭ�� ��ŭ ����.
		m_ptTemp.x += rInput.GetCursorX() - m_ptHeld.x;
		m_ptTemp.y += rInput.GetCursorY() - m_ptHeld.y;
		if (!m_bDocking)		// ��ŷ�� �ƴ϶��.
			// �����츦 ��ȭ�� ��ġ�� ��ġ��Ŵ.
			SetPosition(m_ptTemp.x, m_ptTemp.y);
		m_ptHeld = rInput.GetCursorPos();	// ���� Ŀ�� ��ġ�� ���� Ŀ�� ��ġ�� ���.
	}

	CheckAdditionalState();

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	UpdateWhileActive();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	UpdateWhileActive(dDeltaTick);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ������ ����.
//*****************************************************************************
void CWin::Render()
{
	if (m_bShow)
	{
		if (m_psprBg)
			m_psprBg->Render();

		RenderControls();
	}
}

//*****************************************************************************
// �Լ� �̸� : RegisterButton()
// �Լ� ���� : ��ư ����Ʈ�� ��ư ���.
//			 CWin�� ��� ���� ������� Create()���� �� �Լ��� ������ ��� ��ư
//			���� ����ϸ� �����쿡���� �⺻���� ��ư ���۵��� �ڵ����� ó���Ѵ�.
// �Ű� ���� : pBtn	: ����� ��ư ������.
//*****************************************************************************
void CWin::RegisterButton(CButton* pBtn)
{
	m_BtnList.AddTail(pBtn);
}

void CWin::RenderButtons()
{
	CButton* pBtn;
	NODE* position = m_BtnList.GetHeadPosition();	// list�� Head���� �˻�.
	while (position)	// position�� NULL�� ������ �ݺ�.
	{
		// �� position�� ���� ��� �� position�� ���� position����.
		pBtn = (CButton*)m_BtnList.GetNext(position);
		pBtn->Render();
	}
}