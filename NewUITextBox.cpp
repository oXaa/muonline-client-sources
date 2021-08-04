//=============================================================================
//
//	NewUITextBox.cpp
//
//	Copyright 2010 Webzen Mu-Studio
//
//=============================================================================
#pragma once
#include "StdAfx.h"

#ifdef KJW_ADD_NEWUI_TEXTBOX

#include "NewUITextBox.h"
#include "UIControls.h"
#include "wsclientinline.h"

using namespace SEASON3B;

const int iMAX_TEXT_LINE = 512;
const int iLINE_INTERVAL = 2;

//=============================================================================
//  @Name   CNewUITextBox()
//  @author Kim Jae Woo
//  @date   2010-10-22
//  @brief  ������
//=============================================================================
CNewUITextBox::CNewUITextBox()
{
	m_iWidth = 0;
	m_iHeight = 0;
	memset( &m_ptPos, 0, sizeof(POINT) );
	
	m_iTextHeight = 0;
	m_iTextLineHeight = 1;
	m_iLimitLine = 0;
		
	m_iMaxLine = 0;
	m_iCurLine = 0;
}

//=============================================================================
//  @Name   ~CNewUITextBox()
//  @author Kim Jae Woo
//  @date   2010-10-22
//  @brief  �Ҹ���
//=============================================================================
CNewUITextBox::~CNewUITextBox()
{
	Release();
}

//=============================================================================
//  @Name   Create( int iX, int iY, int iWidth ,int iHeight )
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ��ǥ���� �� �ʱ�ȭ
//=============================================================================
bool CNewUITextBox::Create( int iX, int iY, int iWidth ,int iHeight )
{
	SetPos( iX, iY, iWidth, iHeight );
	Show( true );
	
	return true;
}

//=============================================================================
//  @Name   SetPos( int iX, int iY, int iWidth ,int iHeight )
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ��ǥ���� ����
//=============================================================================
void CNewUITextBox::SetPos( int iX, int iY, int iWidth ,int iHeight )
{
	m_ptPos.x = iX;
	m_ptPos.y = iY;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	SIZE Fontsize;
	g_pRenderText->SetFont(g_hFont);

	unicode::t_string strTemp = _T("A");

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32( g_pRenderText->GetFontDC(), strTemp.c_str(), strTemp.size(), &Fontsize );
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint( g_pRenderText->GetFontDC(), strTemp.c_str(), strTemp.size(), &Fontsize );
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	m_iTextHeight = Fontsize.cy;
	m_iTextLineHeight = m_iTextHeight + iLINE_INTERVAL;

	m_iLimitLine = m_iHeight / m_iTextLineHeight;

	m_iMaxLine = 0;
	m_iCurLine = 0;
}

//=============================================================================
//  @Name   Release()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ����
//=============================================================================
void CNewUITextBox::Release()
{

}

//=============================================================================
//  @Name   GetLayerDepth()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  UI����(Z-Buffer)
//=============================================================================
float CNewUITextBox::GetLayerDepth()
{
	return 4.4f;
}

//=============================================================================
//  @Name   UpdateMouseEvent()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ���콺 �̺�Ʈ ó��
//=============================================================================
bool CNewUITextBox::UpdateMouseEvent()
{
	return true;
}

//=============================================================================
//  @Name   UpdateKeyEvent()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  Ű�Է� �̺�Ʈ ó��
//=============================================================================
bool CNewUITextBox::UpdateKeyEvent()
{
	return true;
}

//=============================================================================
//  @Name   Update()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ������Ʈ
//=============================================================================
bool CNewUITextBox::Update()
{
 	return true;
}

//=============================================================================
//  @Name   Render()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ������
//=============================================================================
bool CNewUITextBox::Render()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	for( int iIndex = 0; iIndex < m_iLimitLine; iIndex++ )
	{
		int iLineIndex = m_iCurLine + iIndex;
		
		if( GetLineText( iLineIndex ).empty() == false  )
		{
			g_pRenderText->SetFont( g_hFont );
			//g_pRenderText->SetBgColor( 0, 0, 0, 0 );
			g_pRenderText->SetTextColor( 255, 255, 255, 255 );
			g_pRenderText->RenderText(	m_ptPos.x,	m_ptPos.y + iIndex * m_iTextLineHeight,	GetLineText( iLineIndex ).c_str(),
										m_iWidth,	0,		RT3_SORT_LEFT );
		}
	}

	return true;
}

//=============================================================================
//  @Name   AddText( unicode::t_char* strText )
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ���ڿ��� �߰������ش�. ���� �ؽ�Ʈ�ڽ����� ��ٸ� �ڽ�ũ�⿡ �°� �߶��ش�.
//=============================================================================
void CNewUITextBox::AddText( unicode::t_char* strText )
{
	unicode::t_char strTemp[ iMAX_TEXT_LINE ][ iMAX_TEXT_LINE ];
	::memset( strTemp[0], 0, sizeof( char ) * iMAX_TEXT_LINE * iMAX_TEXT_LINE );

	// strText�� m_iWidth���̿� �°� �߶� strTemp�� ����� ���� �ִ´�. �߷��� ������ ���̴� iTextLine�̴�.
	int iTextLine = ::DivideStringByPixel( &strTemp[0][0], iMAX_TEXT_LINE, iMAX_TEXT_LINE, strText, m_iWidth, true, '#' );
	
	// ������� ���� ����ŭ �ؽ�Ʈ �߰�
	for( int iIndex=0;iIndex<iTextLine;iIndex++ )
	{
		m_vecText.push_back( strTemp[ iIndex ] );
	}
}	

//=============================================================================
//  @Name   AddText( const unicode::t_char* strText )
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ���� ���ڿ��� �ޱ� ���� �Լ� AddText( unicode::t_char* strText )�� ������ �۵�
//=============================================================================
void CNewUITextBox::AddText( const unicode::t_char* strText )
{
	unicode::t_char strTempText[iMAX_TEXT_LINE] = {0,};
	sprintf( strTempText, strText );

	AddText( strTempText );
}

//=============================================================================
//  @Name   GetFullText()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ���� �ؽ�Ʈ�ڽ��� �ԷµǾ��ִ� ��ü ���ڿ��� �����´�.
//=============================================================================
unicode::t_string CNewUITextBox::GetFullText()
{
	unicode::t_string strTemp;
	
	type_vector_textbase::iterator vi = m_vecText.begin();
	for(; vi != m_vecText.end(); vi++)
	{
		strTemp += (*vi);
	}

	return strTemp;
}

//=============================================================================
//  @Name   GetLineText( int iLineIndex )
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  iLineIndex�� �ش��ϴ� �ε���(����)�� �ִ� ���ڿ��� �о�´�.
//=============================================================================
unicode::t_string CNewUITextBox::GetLineText( int iLineIndex )
{
	if( 0 > iLineIndex || m_vecText.size() <= iLineIndex )
		return "";

	return m_vecText[ iLineIndex ];
}

//=============================================================================
//  @Name   GetMoveableLine()
//  @author Kim Jae Woo
//  @date   2010-10-25
//  @brief  ������ �� �ִ� ���μ� ��ũ�ѹ� �� �ؽ�Ʈ �ڽ� ������ġ ������ ���
//=============================================================================
int CNewUITextBox::GetMoveableLine()		
{
	int iMoveableLine = m_vecText.size() - m_iLimitLine;
	if( iMoveableLine <= 0 )
		iMoveableLine = 0;

	return iMoveableLine;
}

#endif // KJW_ADD_NEWUI_TEXTBOX