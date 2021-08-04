//=============================================================================
//
//	NewUITextBox.h
//
//	Copyright 2010 Webzen Mu-Studio
//
//=============================================================================
#ifndef _NEWUITEXTBOX_H_
#define _NEWUITEXTBOX_H_

#ifdef KJW_ADD_NEWUI_TEXTBOX
#pragma once
#include "NewUIBase.h"

namespace SEASON3B
{
	//=============================================================================
	//	CLASS   CNewUITextBox 
	//  @brief  �ؽ�Ʈ�ڽ� UI
	//=============================================================================
	class CNewUITextBox : public CNewUIObj
	{
		typedef std::vector<unicode::t_string>		type_vector_textbase;
		type_vector_textbase	m_vecText;		
		
	protected:
		int							m_iWidth;						// �ؽ�Ʈ �ڽ��� ����
		int							m_iHeight;						// �׽�Ʈ �ڽ��� ����
		POINT						m_ptPos;						// �ؽ�Ʈ �ڽ��� ��ġ
		
		int							m_iTextHeight;					// ������ ũ��
		int							m_iTextLineHeight;				// ������ ũ�� + ����
		int							m_iLimitLine;					// �ѹ��� ǥ�õ� �� �ִ� ���μ�
			
		int							m_iMaxLine;						// ��ü ���μ�
		int							m_iCurLine;						// ���� ����

	public:
		CNewUITextBox();
		virtual ~CNewUITextBox();
		
		bool Create( int iX, int iY, int iWidth ,int iHeight );
		void SetPos( int iX, int iY, int iWidth ,int iHeight );
		void Release();
		
		float GetLayerDepth();
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		
		bool Update();
		bool Render();
		
		void ClearText(){ m_vecText.clear(); }							// �ؽ�Ʈ �ڽ��� ������ �����ش�.
		void AddText( unicode::t_char* strText );						// �ؽ�Ʈ �ڽ��� ������ �߰��Ѵ�.
		void AddText( const unicode::t_char* strText );					// �ؽ�Ʈ �ڽ��� ������ �߰��Ѵ�.
		
		unicode::t_string GetFullText();								// �ؽ�Ʈ �ڽ��� ��ü ���ڿ��� �����´�.
		unicode::t_string GetLineText( int iLineIndex );				// �ؽ�Ʈ �ڽ��� Ư�� ������ ���ڿ��� �����´�.
		
		int GetMoveableLine();											// ������ �� �ִ� ���μ�
		int GetLimitLine(){ return m_iLimitLine; }						// �ѹ��� ǥ�õ� �� �ִ� ���μ��� �����´�.
		int GetMaxLine(){ return m_vecText.size(); }					// �ؽ�Ʈ �ڽ��� ��ü ���μ��� �����´�.
		int GetCurLine(){ return m_iCurLine; }							// ���� �ؽ�Ʈ �ڽ��� ǥ�õǰ� �ִ� �������� �����´�.
		void SetCurLine( int iLine ){ m_iCurLine = iLine; }				// ���� �ؽ�Ʈ �ڽ��� ǥ�õǰ� �ִ� �������� �����Ѵ�.
	};
}

#endif // KJW_ADD_NEWUI_TEXTBOX
#endif _NEWUITEXTBOX_H_

