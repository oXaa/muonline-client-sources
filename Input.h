//*****************************************************************************
// File: Input.h
//
// Desc: interface for the CInput class.
//		 Singleton ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_INPUT_H__56D42544_2BF6_4B84_B368_F36CACDFEF1E__INCLUDED_)
#define AFX_INPUT_H__56D42544_2BF6_4B84_B368_F36CACDFEF1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE
#include "NewUICommon.h"
#endif // KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE

class CInput
{
protected:
	HWND	m_hWnd;

	POINT	m_ptCursor;			// ���콺 Ŀ�� ��ǥ.
	long	m_lDX;				// X�� ��ȭ��.
	long	m_lDY;				// Y�� ��ȭ��.
//	long	m_lDZ;				// Z�� ��ȭ��(mouse�� ��).
	bool	m_bLBtnDn;			// ���� ��ư Down.
	bool	m_bLBtnHeldDn;		// ���� ��ư Down ����.
	bool	m_bLBtnUp;			// ���� ��ư Up.
	bool	m_bLBtnDbl;			// ���� ��ư ���� Ŭ��.
	bool	m_bRBtnDn;			// ������ ��ư Down.
	bool	m_bRBtnHeldDn;		// ������ ��ư Down ����.
	bool	m_bRBtnUp;			// ������ ��ư Up.
	bool	m_bRBtnDbl;			// ������ ��ư ���� Ŭ��.
	bool	m_bMBtnDn;			// ���(��) ��ư Down.
	bool	m_bMBtnHeldDn;		// ���(��) ��ư Down ����.
	bool	m_bMBtnUp;			// ���(��) ��ư Up.
	bool	m_bMBtnDbl;			// ���(��) ��ư ���� Ŭ��.

	long	m_lScreenWidth;		// ��ũ��(BackBuffer) ���� ũ��.
	long	m_lScreenHeight;	// ��ũ��(BackBuffer) ���� ũ��.
	bool	m_bLeftHand;		// �޼������ΰ�?
	bool	m_bTextEditMode;	// ä�� ����ΰ�?(TextEdit��.)

	POINT	m_ptFormerCursor;		// ���� ���콺 Ŀ�� ��ǥ.
	double	m_dDoubleClickTime;		// ���� Ŭ�� �ð�.
	double	m_dBtn0LastClickTime;	// ��ư0�� ���������� Ŭ���� �ð�.
	double	m_dBtn1LastClickTime;	// ��ư1�� ���������� Ŭ���� �ð�.
	double	m_dBtn2LastClickTime;	// ��ư2�� ���������� Ŭ���� �ð�.
	bool	m_bFormerBtn0Dn;		// ������ ��ư0�� Down�̾���?
	bool	m_bFormerBtn1Dn;		// ������ ��ư1�� Down�̾���?
	bool	m_bFormerBtn2Dn;		// ������ ��ư2�� Down�̾���?
	
#ifdef NEW_USER_INTERFACE_UTIL
	typedef std::list< BoostWeak_Ptr(InputMessageHandler) >   HandlerList;
	
    HandlerList										m_HandlerList;
	int												m_PosValue;
#endif //NEW_USER_INTERFACE_UTIL

protected:						// �����ڸ� protected�� �����ؼ�
	CInput();					//�ܺο����� ������ ������ ����.

public:
	virtual ~CInput();

	static CInput& Instance();
	bool Create(HWND hWnd, long lScreenWidth, long lScreenHeight);
	void Update();

	// Ű�� �����°�?(������ ���� true)
	// �� �Լ��� ���� �Ҿ� ��. Ű�� ���� �� ù �����ӿ� true�� �ǰ� ���� ������
	//���Ŀ� ��а� false�� ������ �� true�� ����. �Ƹ��� �޸��� ��� Ű�� ��
	//���� ������ ��а� ���ڰ� �������ٰ� �������� ������ �Ͱ� ������ ���� ��.
	bool IsKeyDown(int nVirtualKeyCode)
	{
		if (m_bTextEditMode)
			return false;
		return SEASON3B::IsPress(nVirtualKeyCode);
	}
	// Ű�� ����� �ִ°�?
	bool IsKeyHeldDown(int nVirtualKeyCode)
	{
		if (m_bTextEditMode)
			return false;
		return SEASON3B::IsRepeat(nVirtualKeyCode);
	}

	POINT GetCursorPos(){ return m_ptCursor; }
	long GetCursorX(){ return m_ptCursor.x; }
	long GetCursorY(){ return m_ptCursor.y; }
	long GetDX(){ return m_lDX; }
	long GetDY(){ return m_lDY; }
	bool IsLBtnDn(){ return m_bLBtnDn; }
	bool IsLBtnHeldDn(){ return m_bLBtnHeldDn; }
	bool IsLBtnUp(){ return m_bLBtnUp; }
	bool IsLBtnDbl(){ return m_bLBtnDbl; }
	bool IsRBtnDn(){ return m_bRBtnDn; }
	bool IsRBtnHeldDn(){ return m_bRBtnHeldDn; }
	bool IsRBtnUp(){ return m_bRBtnUp; }
	bool IsRBtnDbl(){ return m_bRBtnDbl; }
	bool IsMBtnDn(){ return m_bMBtnDn; }
	bool IsMBtnHeldDn(){ return m_bMBtnHeldDn; }
	bool IsMBtnUp(){ return m_bMBtnUp; }
	bool IsMBtnDbl(){ return m_bMBtnDbl; }

	long GetScreenWidth(){ return m_lScreenWidth; }
	long GetScreenHeight(){ return m_lScreenHeight; }
	void SetLeftHandMode(bool bLeftHand){ m_bLeftHand = bLeftHand; }
	bool IsLeftHandMode(){ return m_bLeftHand; }
	void SetTextEditMode(bool bTextEditMode){ m_bTextEditMode = bTextEditMode; }
	bool IsTextEditMode(){ return m_bTextEditMode; }

#ifdef NEW_USER_INTERFACE_UTIL
public:
	void RegisterInputMessageHandler( BoostWeak_Ptr(InputMessageHandler) handler, bool first = false );
	
private:
	//Mouse
	void HandleMouseMessage( eKeyType key, eKeyStateType type, int value );
#endif //NEW_USER_INTERFACE_UTIL
};

#endif // !defined(AFX_INPUT_H__56D42544_2BF6_4B84_B368_F36CACDFEF1E__INCLUDED_)
