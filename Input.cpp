//*****************************************************************************
// File: Input.cpp
//
// Desc: implementation of the CInput class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "Input.h"
#include "UsefulDef.h"
#include "./Time/Timer.h"
#if	defined WINDOWMODE
#include "UIManager.h"
extern bool g_bWndActive;
#endif
extern CTimer*	g_pTimer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInput::CInput()
#ifdef NEW_USER_INTERFACE_UTIL
: m_PosValue( 0 )
#endif //NEW_USER_INTERFACE_UTIL
{

}

CInput::~CInput()
{

}

//*****************************************************************************
// �Լ� �̸� : Instance()
// �Լ� ���� : ��ü�� �� �ϳ��� ����.
//			  �� Ŭ������ �����ϱ� ���� �������̽���
//*****************************************************************************
CInput& CInput::Instance()
{
	static CInput s_Input;                  
    return s_Input;
}

//****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� :
// �Ű� ���� : hWnd			: ������ �ڵ�.
//			   lScreenWidth	: ��ũ��(Back Buffer) �ʺ�.
//			   lScreenHeight: ��ũ��(Back Buffer) ����.
//*****************************************************************************
bool CInput::Create(HWND hWnd, long lScreenWidth, long lScreenHeight)
{
	if (NULL == hWnd)
		return false;

	m_hWnd = hWnd;

	// ��ũ��(Back Buffer) ũ�� ����.
	m_lScreenWidth = lScreenWidth;
	m_lScreenHeight = lScreenHeight;

	// X, Y��ǥ �ʱ�ȭ.
	::GetCursorPos(&m_ptCursor);
	::ScreenToClient(m_hWnd, &m_ptCursor);
	m_ptFormerCursor = m_ptCursor;

	m_bLeftHand = false;			// �޼����� ���� ����.

	// ���� Ŭ�� �ð��� ����.
	m_dDoubleClickTime = (double)::GetDoubleClickTime();
	// �� ��ư�� ���������� Ŭ���� �ð� �ʱ�ȭ.
	m_dBtn0LastClickTime = m_dBtn1LastClickTime = m_dBtn2LastClickTime = 0.0;
	// ������ Down���� ���°� �ʱ�ȭ.
	m_bFormerBtn0Dn = m_bFormerBtn1Dn = m_bFormerBtn2Dn = false;

	m_bLBtnHeldDn = m_bRBtnHeldDn = m_bMBtnHeldDn = false;

	m_bTextEditMode	= false;

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : Input ���¸� ó��. Main ���ѷ������� �� ���� ȣ��.
//*****************************************************************************
void CInput::Update()
{
	// �� ���� ��ȭ�� �ʱ�ȭ.
	m_lDX = m_lDY = 0L;
	// Down, Up, Double Click�� �������� true�� �ǾߵǹǷ� false�� �ʱ�ȭ ��.
	m_bLBtnUp = m_bRBtnUp = m_bMBtnUp
		= m_bLBtnDn = m_bRBtnDn = m_bMBtnDn
		= m_bLBtnDbl = m_bRBtnDbl = m_bMBtnDbl = false;

// ���콺 Ŀ�� ��ġ ó��.
	// ���콺 Ŀ�� ��ġ ���.
	::GetCursorPos(&m_ptCursor);
	::ScreenToClient(m_hWnd, &m_ptCursor);

	// X, Y��ǥ���� ������.
	m_ptCursor.x = LIMIT(m_ptCursor.x, 0, m_lScreenWidth - 1);
	m_ptCursor.y = LIMIT(m_ptCursor.y, 0, m_lScreenHeight - 1);

	// �� ���� ��ȭ�� Data�� ���.
	m_lDX = m_ptCursor.x - m_ptFormerCursor.x;
	m_lDY = m_ptCursor.y - m_ptFormerCursor.y;

	if (m_lDX || m_lDY)	// �������� �־��ٸ� ����Ŭ���� �ƴϹǷ�.
		m_bFormerBtn0Dn = m_bFormerBtn1Dn = m_bFormerBtn2Dn = false;

	m_ptFormerCursor = m_ptCursor;

#ifdef NEW_USER_INTERFACE_UTIL
	m_PosValue = m_ptCursor.y | ( m_ptCursor.x << 16 );
#endif //NEW_USER_INTERFACE_UTIL	

	// ���콺 �� ��ư ó��.
	double dAbsTime;

	// ���콺 ���� ��ư.
	if (SEASON3B::IsPress(VK_LBUTTON))	// ���� ��ư�� ���ȴٸ�.
	{
		dAbsTime = g_pTimer->GetAbsTime();	// ���� �ð�.
		// ���� Ŭ���̰� ������ �� Ŭ���̾���.
		// 'm_bFormerBtn1Dn'�� ��ư�� ��Ÿ���� �� Dbl�� �����
		//�������ϱ� ���ؼ�.
		if (dAbsTime - m_dBtn0LastClickTime <= m_dDoubleClickTime
			&& m_bFormerBtn0Dn)
		{
			if (m_bLeftHand)	// �޼����̸�.
			{
				m_bRBtnDn =	m_bRBtnHeldDn = m_bRBtnDbl = true;
				m_bRBtnUp = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_DblClk, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			else				// ���������̸�.
			{
				m_bLBtnDn = m_bLBtnHeldDn = m_bLBtnDbl = true;
				m_bLBtnUp = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_DblClk, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			m_bFormerBtn0Dn = false;
		}
		else	// �� Ŭ���̸�.
		{
			if (m_bLeftHand)	// �޼����̸�.
			{
				m_bRBtnDn =	m_bRBtnHeldDn =	true;
				m_bRBtnUp = m_bRBtnDbl = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_Down, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			else				// ���������̸�.
			{
				m_bLBtnDn = m_bLBtnHeldDn = true;
				m_bLBtnUp = m_bLBtnDbl = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_Down, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			m_bFormerBtn0Dn = true;
		}
		m_dBtn0LastClickTime = dAbsTime;
	}
	else if (SEASON3B::IsNone(VK_LBUTTON))	// ���� ��ư�� �ȴ��� ���¶��.
	{
		if (m_bLeftHand)		// �޼����̸�.
		{
			if (m_bRBtnHeldDn)	// ���� �����ӿ��� ���� ���¿��ٸ�.
			{
				m_bRBtnDn = m_bRBtnHeldDn = m_bRBtnDbl = false;
				m_bRBtnUp = true;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_Up, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
		}
		else					// ���������̸�.
		{
			if (m_bLBtnHeldDn)	// ���� �����ӿ��� ���� ���¿��ٸ�.
			{
				m_bLBtnDn = m_bLBtnHeldDn = m_bLBtnDbl = false;
				m_bLBtnUp = true;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_Up, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
		}
	}

	// ���콺 ������ ��ư.
	if (SEASON3B::IsPress(VK_RBUTTON))	// ������ ��ư�� ���ȴٸ�.
	{
		dAbsTime = g_pTimer->GetAbsTime();	// ���� �ð�.
		// ���� Ŭ���̰� ������ �� Ŭ���̾���.
		// 'm_bFormerBtn1Dn'�� ��ư�� ��Ÿ���� �� Dbl�� �����
		//�������ϱ� ���ؼ�.
		if (dAbsTime - m_dBtn1LastClickTime <= m_dDoubleClickTime
			&& m_bFormerBtn1Dn)
		{
			if (m_bLeftHand)	// �޼����̸�.
			{
				m_bLBtnDn =	m_bLBtnHeldDn = m_bLBtnDbl = true;
				m_bLBtnUp = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_DblClk, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			else				// ���������̸�.
			{
				m_bRBtnDn = m_bRBtnHeldDn = m_bRBtnDbl = true;
				m_bRBtnUp = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_DblClk, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			m_bFormerBtn1Dn = false;
		}
		else	// �� Ŭ���̸�.
		{
			if (m_bLeftHand)	// �޼����̸�.
			{
				m_bLBtnDn =	m_bLBtnHeldDn = true;
				m_bLBtnUp = m_bLBtnDbl = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_Down, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			else				// ���������̸�.
			{
				m_bRBtnDn = m_bRBtnHeldDn = true;
				m_bRBtnUp = m_bRBtnDbl = false;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_Down, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
			m_bFormerBtn1Dn = true;
		}
		m_dBtn1LastClickTime = dAbsTime;
	}
	else if (SEASON3B::IsNone(VK_RBUTTON))	// ������ ��ư�� �ȴ��� ���¶��.
	{
		if (m_bLeftHand)		// �޼����̸�.
		{
			if (m_bLBtnHeldDn)	// ���� �����ӿ��� ���� ���¿��ٸ�.
			{
				m_bLBtnDn = m_bLBtnHeldDn = m_bLBtnDbl = false;
				m_bLBtnUp = true;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_LButton, eKeyState_Up, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
		}
		else					// ���������̸�.
		{
			if (m_bRBtnHeldDn)	// ���� �����ӿ��� ���� ���¿��ٸ�.
			{
				m_bRBtnDn = m_bRBtnHeldDn = m_bRBtnDbl = false;
				m_bRBtnUp = true;
#ifdef NEW_USER_INTERFACE_UTIL
				HandleMouseMessage( eKey_RButton, eKeyState_Up, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
			}
		}
	}

	// ���콺 ��(���) ��ư.
	if (SEASON3B::IsPress(VK_MBUTTON))	// �� ��ư�� ���ȴٸ�.
	{
		dAbsTime = g_pTimer->GetAbsTime();	// ���� �ð�.
		// ���� Ŭ���̰� ������ �� Ŭ���̾���.
		// 'm_bFormerBtn2Dn'�� ��ư�� ��Ÿ���� �� Dbl�� �����
		//�������ϱ� ���ؼ�.
		if (dAbsTime - m_dBtn2LastClickTime <= m_dDoubleClickTime
			&& m_bFormerBtn2Dn)
		{
			m_bMBtnDbl = true;
			m_bFormerBtn2Dn = false;
#ifdef NEW_USER_INTERFACE_UTIL
			HandleMouseMessage( eKey_Wheel, eKeyState_DblClk, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
		}
		else	// �� Ŭ���̸�.
		{
			m_bFormerBtn2Dn = true;
			m_bMBtnDbl = false;
#ifdef NEW_USER_INTERFACE_UTIL
			HandleMouseMessage( eKey_Wheel, eKeyState_Down, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
		}
		m_bMBtnDn = m_bMBtnHeldDn = true;
		m_bMBtnUp = false;
		m_dBtn2LastClickTime = dAbsTime;
	}
	else if (SEASON3B::IsNone(VK_MBUTTON))	// ������ ��ư�� �ȴ��� ���¶��.
	{
		if (m_bMBtnHeldDn)	// ���� �����ӿ��� ���� ���¿��ٸ�.
		{
			m_bMBtnDn = m_bMBtnHeldDn = m_bMBtnDbl = false;
			m_bMBtnUp = true;
#ifdef NEW_USER_INTERFACE_UTIL
			HandleMouseMessage( eKey_Wheel, eKeyState_Up, m_PosValue );
#endif //NEW_USER_INTERFACE_UTIL
		}
	}
#if	defined WINDOWMODE
	if(GetActiveWindow() == NULL)
	{
		m_lDX = m_lDY = 0L;
		// Down, Up, Double Click�� �������� true�� �ǾߵǹǷ� false�� �ʱ�ȭ ��.
		m_bLBtnUp = m_bRBtnUp = m_bMBtnUp
			= m_bLBtnDn = m_bRBtnDn = m_bMBtnDn
			= m_bLBtnDbl = m_bRBtnDbl = m_bMBtnDbl = false;

		m_ptCursor.x = m_ptCursor.y = 0;
		return;
	}
#endif
}

#ifdef NEW_USER_INTERFACE_UTIL

void CInput::RegisterInputMessageHandler( BoostWeak_Ptr(InputMessageHandler) handler, bool first )
{
	if( first )
		m_HandlerList.push_front( handler );
	else
		m_HandlerList.push_back( handler );
}


void CInput::HandleMouseMessage( eKeyType key, eKeyStateType type, int value )
{
    for( HandlerList::iterator iter = m_HandlerList.begin()
        ; iter != m_HandlerList.end(); )
    {
        HandlerList::iterator curIter = iter;
        ++iter;
        BoostWeak_Ptr(InputMessageHandler) handler = *curIter;
        if( handler.expired() == false )
        {
            if( handler.lock()->HandleInputMessage( key, type, value ) == true )
            {
                return;
            }
        }
        else
        {
            m_HandlerList.erase( curIter );
        }
    }
}

#endif //NEW_USER_INTERFACE_UTIL