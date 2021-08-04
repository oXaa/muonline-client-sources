//=============================================================================
//
//	NewUIScrollBar.h
//
//	Copyright 2010 Webzen Mu-Studio
//
//=============================================================================
#ifndef _NEWUISCROLLBAR_H_
#define _NEWUISCROLLBAR_H_

#ifdef KJW_ADD_NEWUI_SCROLLBAR

#include "NewUIBase.h"
#include "NewUIManager.h"
#include "NewUIChatLogWindow.h"

namespace SEASON3B
{
	class CNewUIScrollBar : public CNewUIObj
	{
		//===================================================================
		// ENUM IMAGE_LIST TYPE
		//===================================================================
		enum KEnumTypeIMAGE_LIST										// ��ũ�ѹ� �ؽ��� ���� enum
		{
			IMAGE_SCROLL_TOP	= CNewUIChatLogWindow::IMAGE_SCROLL_TOP,			// newui_scrollbar_up.tga (7,3)
			IMAGE_SCROLL_MIDDLE	= CNewUIChatLogWindow::IMAGE_SCROLL_MIDDLE,			// newui_scrollbar_m.tga (7,15)
			IMAGE_SCROLL_BOTTOM	= CNewUIChatLogWindow::IMAGE_SCROLL_BOTTOM,			// newui_scrollbar_down.tga (7,3)
			IMAGE_SCROLLBAR_ON	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_ON,			// newui_scroll_On.tga (15,30)	
			IMAGE_SCROLLBAR_OFF	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_OFF,			// newui_scroll_Off.tga (15,30)
		};
		
		//===================================================================
		// ENUM SCROLLBTN TYPE
		//===================================================================
		enum KEnumTypeSCROLLBTN											// ��ũ�ѹ� ũ�� ���� enum
		{
			SCROLLBTN_WIDTH = 15,
			SCROLLBTN_HEIGHT = 30,
			SCROLLBAR_TOP_WIDTH = 7,
			SCROLLBAR_TOP_HEIGHT = 3,
			SCROLLBAR_MIDDLE_WIDTH = 7,
			SCROLLBAR_MIDDLE_HEIGHT = 15
		};

		//===================================================================
		// ENUM SCROLLBAR_MOUSEBTN TYPE
		//===================================================================
		enum KEnumTypeSCROLLBAR_MOUSEBTN								// ��ũ�ѹ� ���콺 �̺�Ʈ ���� enum
		{
			SCROLLBAR_MOUSEBTN_INVALID	 = -1,
			SCROLLBAR_MOUSEBTN_FIRST,
			SCROLLBAR_MOUSEBTN_NORMAL = SCROLLBAR_MOUSEBTN_FIRST,		// ��ũ�ѹ� �������
			SCROLLBAR_MOUSEBTN_OVER,									// ��ũ�ѹ� ��ư ���� ���콺�� ���� ����
			SCROLLBAR_MOUSEBTN_CLICKED,									// ��ũ�ѹ� ��ư Ŭ�� ����
			SCROLLBAR_MOUSEBTN_TOTAL,						
			SCROLLBAR_MOUSEBTN_LAST		= SCROLLBAR_MOUSEBTN_TOTAL - 1,
		};

	protected:
		int							m_iHeight;							// ��ũ�ѹ��� ����
		POINT						m_ptPos;							// ��ũ�ѹ��� ��ġ
		
		POINT						m_ptScrollBtnStartPos;				// ��ũ�ѹ� ��ư�� ���� ��ġ
		POINT						m_ptScrollBtnPos;					// ��ũ�ѹ� ��ư�� ��ġ
		
		int							m_iScrollBarPickGap;				// ��ũ�ѹ��� Ŭ�� ������ ���� ����
		
		int							m_iScrollBarMovePixel;				
		int							m_iScrollBarHeightPixel;			// ��ũ�ѹ��� ���� �ȼ� ��
		int							m_iScrollBarMiddleNum;				// ��ũ�ѹ��� �߰��������� ��
		int							m_iScrollBarMiddleRemainderPixel;	// ��ũ�ѹ��� �߰� �������� �׸��� ���� �ȼ� ��
		
		int							m_iScrollBtnMouseEvent;				// ��ũ�� ��ư ���콺 Ŭ�� �̺�Ʈ
		bool						m_bScrollBtnActive;					// ��ũ�ѹ�ư Ȱ��ȭ
		
		float						m_fPercentOfSize;					// ��ũ�ѹ� ��ư�� ��ġ( 0.0f ~ 1.0f )
		
		int							m_iBeginPos;						// ��������
		int							m_iCurPos;							// ���� ��ġ
		int							m_iMaxPos;							// �ִ� �̵������� ��ġ

	public:
		CNewUIScrollBar();
		virtual ~CNewUIScrollBar();
		
		bool Create( int iX, int iY, int iHeight );					
		void Release();
		
		float GetLayerDepth();
		
		void LoadImages();
		void UnloadImages();
		
		void SetPos(int x, int y);
		
		bool UpdateBtnEvent();
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		
		bool Update();
		bool Render();
		
		void UpdateScrolling();
		void ScrollUp( int iMoveValue );
		void ScrollDown( int iMoveValue );
		
		float GetPercent() { return m_fPercentOfSize; }
		void SetPercent( float fPercent );
		
		int GetMaxPos() { return m_iMaxPos; }
		void SetMaxPos( int iMaxPos );
		
		int GetCurPos() { return m_iCurPos; }
		void SetCurPos( int iMoveValue );
	};
}

#endif // KJW_ADD_NEWUI_SCROLLBAR

#endif // _NEWUISCROLLBAR_H_