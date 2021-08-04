// NewUIPetInformation.cpp: imp0lementation of the CNewUIPetInfoWindow class.
//
//
// ��  �� : �� ����â �������̽�
//
// �ۼ��� : Pruarin
//
// ������¥ : 2007.7.11(��)
//
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NewUIPetInfoWindow.h"
#include "NewUISystem.h"
#include "wsclientinline.h"
#include "GIPetManager.h"

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNewUIPetInfoWindow::CNewUIPetInfoWindow() 
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
	m_iNumCurOpenTab = TAB_TYPE_DARKHORSE;
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	CalcDamage(m_iNumCurOpenTab);
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
	m_EventState = EVENT_NONE;
#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
	m_bEquipedDarkHorse = false;
	m_bEquipedDarkSpirit = false;
	memset( &m_sPetInfo, 0, sizeof(PET_INFO) );
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM									//## �ҽ����� �����.
}

CNewUIPetInfoWindow::~CNewUIPetInfoWindow() 
{ 
	Release(); 
}

//---------------------------------------------------------------------------------------------
// Create
bool CNewUIPetInfoWindow::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if( NULL == pNewUIMng )
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj( SEASON3B::INTERFACE_PET, this );		// �������̽� ������Ʈ ���
	
	SetPos(x, y);
	
	LoadImages();
	
	InitButtons( );
	
	Show(false);
	
	return true;
}

//---------------------------------------------------------------------------------------------
// Release
void CNewUIPetInfoWindow::Release()
{
	UnloadImages();
	
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

//---------------------------------------------------------------------------------------------
// InitButtons
void CNewUIPetInfoWindow::InitButtons( )
{
	// �ǹ�ư Text����
	list<unicode::t_string> ltext;
	
	ltext.push_back( GlobalText[1187] );		// "��ũȣ��"
	ltext.push_back( GlobalText[1214] );		// "��ũ���Ǹ�"

	// Tab Button	
	m_BtnTab.CreateRadioGroup( 2, IMAGE_PETINFO_TAB_BUTTON );
	m_BtnTab.ChangeRadioText( ltext );
	m_BtnTab.ChangeRadioButtonInfo( true, m_Pos.x+12.f, m_Pos.y+48.f, 56, 22 );
	m_BtnTab.ChangeFrame( m_iNumCurOpenTab );
	
	// Exit Button
	m_BtnExit.ChangeButtonImgState(true, IMAGE_PETINFO_BTN_EXIT, false);
	m_BtnExit.ChangeButtonInfo( m_Pos.x+13, m_Pos.y+392, 36, 29 );		
	m_BtnExit.ChangeToolTipText(GlobalText[1002], true);	// 1002 "�ݱ�"
}

//---------------------------------------------------------------------------------------------
// SetPos
void CNewUIPetInfoWindow::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_BtnTab.ChangeRadioButtonInfo( true, m_Pos.x+12.f, m_Pos.y+48.f, 56, 22 );
	m_BtnExit.ChangeButtonInfo( m_Pos.x+13, m_Pos.y+392, 36, 29 );
}

//---------------------------------------------------------------------------------------------
// UpdateMouseEvent
bool CNewUIPetInfoWindow::UpdateMouseEvent()
{
	// ��ư ó��
	if( true == BtnProcess() )	// ó���� �Ϸ� �Ǿ��ٸ�
		return false;
	
	//. �κ��丮 ���� ���� Ŭ���� ���� UIó�� �� �̵� �Ұ�
	if(CheckMouseIn(m_Pos.x, m_Pos.y, PETINFOWINDOW_WIDTH, PETINFOWINDOW_HEIGHT))
		return false;
	
	return true;
}

//---------------------------------------------------------------------------------------------
// UpdateKeyEvent
bool CNewUIPetInfoWindow::UpdateKeyEvent()
{
	return true;
}

//---------------------------------------------------------------------------------------------
// Update()
bool CNewUIPetInfoWindow::Update()
{		
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
		// Visible ���� �϶� �� Update
	if( IsVisible() == false )
		return true;

	int iNumCurOpenTab = m_BtnTab.UpdateMouseEvent();

	if( (iNumCurOpenTab != RADIOGROUPEVENT_NONE) && (m_iNumCurOpenTab != iNumCurOpenTab) )
	{
		CalcDamage(iNumCurOpenTab);	
		m_iNumCurOpenTab = iNumCurOpenTab;
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
	int iNumCurOpenTab = m_BtnTab.UpdateMouseEvent();

	if( iNumCurOpenTab != RADIOGROUPEVENT_NONE )
	{
		m_iNumCurOpenTab = iNumCurOpenTab;
		RequestPetInfo();
	}

	// Visible ���� �϶� �� Update
	if( IsVisible() )
	{
		UpdatePetInfo();
	}

	UpdatePetInfo();
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
	
	return true;
}

//---------------------------------------------------------------------------------------------
// Render()
bool CNewUIPetInfoWindow::Render()
{
	EnableAlphaTest();
	glColor4f(1.f, 1.f, 1.f, 1.f);

	g_pRenderText->SetFont( g_hFont );
	g_pRenderText->SetTextColor(0xFFFFFFFF);
	
	// �⺻â
	RenderImage(IMAGE_PETINFO_BACK, m_Pos.x, m_Pos.y, float(PETINFOWINDOW_WIDTH), float(PETINFOWINDOW_HEIGHT));
	RenderImage(IMAGE_PETINFO_TOP, m_Pos.x, m_Pos.y, float(PETINFOWINDOW_WIDTH), 64.f);
	RenderImage(IMAGE_PETINFO_LEFT, m_Pos.x, m_Pos.y+64.f, 21.f, float(PETINFOWINDOW_HEIGHT)-64.f-45.f);
	RenderImage(IMAGE_PETINFO_RIGHT, m_Pos.x+float(PETINFOWINDOW_WIDTH)-21.f, m_Pos.y+64.f, 21.f, float(PETINFOWINDOW_HEIGHT)-64.f-45.f);
	RenderImage(IMAGE_PETINFO_BOTTOM, m_Pos.x, m_Pos.y+float(PETINFOWINDOW_HEIGHT)-45.f, float(PETINFOWINDOW_WIDTH), 45.f);
	
	// UI����
	g_pRenderText->SetFont( g_hFontBold );
	g_pRenderText->RenderText(m_Pos.x+60, m_Pos.y+13, GlobalText[1217], 70, 0, RT3_SORT_CENTER);		// "Pet"

	g_pRenderText->SetFont( g_hFont );
	
	// �ǹ�ư
	m_BtnTab.Render( );
		
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	PET_INFO* pPetInfo = NULL;

	switch( m_iNumCurOpenTab )
	{	
	case TAB_TYPE_DARKHORSE:		
		{
			pPetInfo = Hero->GetEquipedPetInfo(PET_TYPE_DARK_HORSE);

			if( pPetInfo->m_dwPetType == PET_TYPE_NONE)
			{
				g_pRenderText->SetTextColor( 0xFF0000FF );
				g_pRenderText->SetFont( g_hFontBold );
				unicode::t_char szText[256] = { 0, };
				unicode::_sprintf( szText, GlobalText[1233], GlobalText[1187]);		// 1233 "�� �����ϴ�"	// 1187 "��ũȣ��"
				g_pRenderText->RenderText( m_Pos.x+15, m_Pos.y+100, szText, 160, 30, RT3_SORT_CENTER );
			}
			else
			{
				RenderDarkHorseInfo( pPetInfo );
			}
		}
		break;
	case TAB_TYPE_DARKSPIRIT:
		{
			pPetInfo = Hero->GetEquipedPetInfo(PET_TYPE_DARK_SPIRIT);

			if( pPetInfo->m_dwPetType == PET_TYPE_NONE )
			{
				g_pRenderText->SetTextColor( 0xFF0000FF );
				g_pRenderText->SetFont( g_hFontBold );
				g_pRenderText->RenderText( m_Pos.x+15, m_Pos.y+100, GlobalText[1169], 160, 30, RT3_SORT_CENTER );	// ���� �����ϴ�.
			}
			else
			{
				RenderDarkSpiritInfo(pPetInfo );
			}
		}
		break;			
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
	// �ǹ�ư ���¿� ���� ó��
	switch( m_iNumCurOpenTab )
	{	
	case TAB_TYPE_DARKHORSE:		
		{
			if( m_bEquipedDarkHorse )
			{
				RenderDarkHorseInfo();
			}
			else
			{
				g_pRenderText->SetTextColor( 0xFF0000FF );
				g_pRenderText->SetFont( g_hFontBold );
				unicode::t_char szText[256] = { 0, };
				unicode::_sprintf( szText, GlobalText[1233], GlobalText[1187]);		// 1233 "�� �����ϴ�"	// 1187 "��ũȣ��"
				g_pRenderText->RenderText( m_Pos.x+15, m_Pos.y+100, szText, 160, 30, RT3_SORT_CENTER );
			}
		}
		break;
	case TAB_TYPE_DARKSPIRIT:
		{
			if( m_bEquipedDarkSpirit )
			{
				RenderDarkSpiritInfo();
			}
			else
			{
				g_pRenderText->SetTextColor( 0xFF0000FF );
				g_pRenderText->SetFont( g_hFontBold );
				g_pRenderText->RenderText( m_Pos.x+15, m_Pos.y+100, GlobalText[1169], 160, 30, RT3_SORT_CENTER );	// ���� �����ϴ�.
			}
		}
		break;			
	default:
		break;
	}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM

	// Exit Button
	m_BtnExit.Render();

	DisableAlphaBlend();
	
	return true;
}

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
//---------------------------------------------------------------------------------------------
// RenderDarkHorseInfo()
bool CNewUIPetInfoWindow::RenderDarkHorseInfo(PET_INFO* pPetInfo)
{
	unicode::t_char szText[256] = { 0, };	

	// â ������ Text		
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );								
	g_pRenderText->RenderText(m_Pos.x+60, m_Pos.y+25, GlobalText[1187], 70, 0, RT3_SORT_CENTER);		// "��ũȣ��"

	int iPosX = m_Pos.x + 12;
	int iPosY = m_Pos.y + 75;

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	RenderGroupBox( iPosX, iPosY, 168, 105 );
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	RenderGroupBox( iPosX, iPosY, 168, 135 );
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	
	// �׷�ڽ� Title
	g_pRenderText->SetTextColor( 255, 255, 0, 255 );
	g_pRenderText->SetFont(g_hFontBold);	

	unicode::_sprintf(szText, GlobalText[200], pPetInfo->m_wLevel);			// 200 "��  ��: %d"
	g_pRenderText->RenderText(iPosX+2, iPosY+8, szText, 70-14, 0, RT3_SORT_CENTER);
	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );


#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], pPetInfo->m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+28, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iPosX+7, iPosY+40, 151, 12);								// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(pPetInfo->m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iPosX+9, iPosY+42, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], pPetInfo->m_dwExp1, pPetInfo->m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+59, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															pPetInfo->m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iPosX+10, iPosY+72, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], pPetInfo->m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+85, szText, 0, 0, RT3_SORT_CENTER);	


#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], pPetInfo->m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+34, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iPosX+7, iPosY+46, 151, 12);								// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(pPetInfo->m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iPosX+9, iPosY+48, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], pPetInfo->m_dwExp1, pPetInfo->m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+67, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															pPetInfo->m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iPosX+10, iPosY+82, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], pPetInfo->m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+97, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[698], (185+(pPetInfo->m_wLevel*15)));					// "��� ������ ���: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+112, szText, 0, 0, RT3_SORT_CENTER);

#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	return true;
}



//---------------------------------------------------------------------------------------------
// RenderDarkSpiritInfo()
bool CNewUIPetInfoWindow::RenderDarkSpiritInfo(PET_INFO* pPetInfo)
{
	unicode::t_char szText[256] = { 0, };
	
	// â ������ Text	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );
	g_pRenderText->RenderText(m_Pos.x+60, m_Pos.y+25, GlobalText[1214], 70, 0, RT3_SORT_CENTER);	// "��ũ���Ǹ�"

	int iGBox1PosX = m_Pos.x + 12;
	int iGBox1PosY = m_Pos.y + 75;
	int iGBox2PosX = m_Pos.x + 12;

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	int iGBox2PosY = m_Pos.y + 196;	
	RenderGroupBox( iGBox1PosX, iGBox1PosY, 168, 121 );
	RenderGroupBox( iGBox2PosX, iGBox2PosY, 168, 195 );
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	int iGBox2PosY = m_Pos.y + 195;	
	RenderGroupBox( iGBox1PosX, iGBox1PosY, 168, 120 );
	RenderGroupBox( iGBox2PosX, iGBox2PosY, 168, 195 );
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
														
	// �׷�ڽ� Title
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor( 255, 255, 0, 255 );
		
	unicode::_sprintf(szText, GlobalText[200], pPetInfo->m_wLevel);			// 200 "��  ��: %d"
	g_pRenderText->RenderText(iGBox1PosX+2, iGBox1PosY+8, szText, 70-14, 0, RT3_SORT_CENTER);
	g_pRenderText->RenderText(iGBox2PosX+2, iGBox2PosY+8, GlobalText[1218], 70-14, 0, RT3_SORT_CENTER);	// "��ɼ���"
	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], pPetInfo->m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+28, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iGBox1PosX+7, iGBox1PosY+40, 151, 12);					// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(pPetInfo->m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iGBox1PosX+9, iGBox1PosY+42, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], pPetInfo->m_dwExp1, pPetInfo->m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+59, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															pPetInfo->m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+72, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], pPetInfo->m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+85, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[698], (185+(pPetInfo->m_wLevel*15)));					// "��� ������ ���: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+98, szText, 0, 0, RT3_SORT_CENTER);

#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], pPetInfo->m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+34, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iGBox1PosX+7, iGBox1PosY+46, 151, 12);					// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(pPetInfo->m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iGBox1PosX+9, iGBox1PosY+48, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], pPetInfo->m_dwExp1, pPetInfo->m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+67, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															pPetInfo->m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+82, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], pPetInfo->m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+97, szText, 0, 0, RT3_SORT_CENTER);	
		
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// SkillBox
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+28, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+68, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+108, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+148, 32.f, 38.f);
	// Skill	(x = SKillbox.x + 7, y = SkillBox.y + 6)
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+34, 19.f, 27.f, 1.f, 0.f);		
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+74, 19.f, 27.f, 21.f, 0.f);
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+114, 19.f, 27.f, 41.f, 0.f);
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+154, 19.f, 27.f, 61.f, 0.f);
	
#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+45, GlobalText[1219], 0, 0, RT3_SORT_CENTER);	// "�⺻ �ൿ"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+85, GlobalText[1220], 0, 0, RT3_SORT_CENTER);	// "���� �ڵ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+125, GlobalText[1221], 0, 0, RT3_SORT_CENTER);	// "���ΰ� �Բ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+165, GlobalText[1222], 0, 0, RT3_SORT_CENTER);	// "Ÿ�� ����"
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+41, GlobalText[1219], 0, 0, RT3_SORT_CENTER);	// "�⺻ �ൿ"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+81, GlobalText[1220], 0, 0, RT3_SORT_CENTER);	// "���� �ڵ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+121, GlobalText[1221], 0, 0, RT3_SORT_CENTER);	// "���ΰ� �Բ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+161, GlobalText[1222], 0, 0, RT3_SORT_CENTER);	// "Ÿ�� ����"
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	
	return true;
}

#else // KJH_FIX_DARKLOAD_PET_SYSTEM																		//## �ҽ����� �����.
//---------------------------------------------------------------------------------------------
// RenderDarkHorseInfo()
bool CNewUIPetInfoWindow::RenderDarkHorseInfo()
{
	unicode::t_char szText[256] = { 0, };	

	// â ������ Text		
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );								
	g_pRenderText->RenderText(m_Pos.x+60, m_Pos.y+25, GlobalText[1187], 70, 0, RT3_SORT_CENTER);		// "��ũȣ��"

	int iPosX = m_Pos.x + 12;
	int iPosY = m_Pos.y + 75;

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	RenderGroupBox( iPosX, iPosY, 168, 105 );
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	RenderGroupBox( iPosX, iPosY, 168, 135 );
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	
	// �׷�ڽ� Title
	g_pRenderText->SetTextColor( 255, 255, 0, 255 );
	g_pRenderText->SetFont(g_hFontBold);	

	unicode::_sprintf(szText, GlobalText[200], m_sPetInfo.m_wLevel);			// 200 "��  ��: %d"
	g_pRenderText->RenderText(iPosX+2, iPosY+8, szText, 70-14, 0, RT3_SORT_CENTER);
	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );


#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], m_sPetInfo.m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+28, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iPosX+7, iPosY+40, 151, 12);								// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(m_sPetInfo.m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iPosX+9, iPosY+42, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], m_sPetInfo.m_dwExp1, m_sPetInfo.m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+59, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															m_sPetInfo.m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iPosX+10, iPosY+72, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], m_sPetInfo.m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+85, szText, 0, 0, RT3_SORT_CENTER);	


#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], m_sPetInfo.m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+34, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iPosX+7, iPosY+46, 151, 12);								// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(m_sPetInfo.m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iPosX+9, iPosY+48, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], m_sPetInfo.m_dwExp1, m_sPetInfo.m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iPosX+10, iPosY+67, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															m_sPetInfo.m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iPosX+10, iPosY+82, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], m_sPetInfo.m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+97, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[698], (185+(m_sPetInfo.m_wLevel*15)));					// "��� ������ ���: %d"
	g_pRenderText->RenderText(iPosX+10, iPosY+112, szText, 0, 0, RT3_SORT_CENTER);

#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	return true;
}



//---------------------------------------------------------------------------------------------
// RenderDarkSpiritInfo()
bool CNewUIPetInfoWindow::RenderDarkSpiritInfo()
{
	unicode::t_char szText[256] = { 0, };
	
	// â ������ Text	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );
	g_pRenderText->RenderText(m_Pos.x+60, m_Pos.y+25, GlobalText[1214], 70, 0, RT3_SORT_CENTER);	// "��ũ���Ǹ�"

	int iGBox1PosX = m_Pos.x + 12;
	int iGBox1PosY = m_Pos.y + 75;
	int iGBox2PosX = m_Pos.x + 12;

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	int iGBox2PosY = m_Pos.y + 196;	
	RenderGroupBox( iGBox1PosX, iGBox1PosY, 168, 121 );
	RenderGroupBox( iGBox2PosX, iGBox2PosY, 168, 195 );
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	int iGBox2PosY = m_Pos.y + 195;	
	RenderGroupBox( iGBox1PosX, iGBox1PosY, 168, 120 );
	RenderGroupBox( iGBox2PosX, iGBox2PosY, 168, 195 );
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
														
	// �׷�ڽ� Title
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor( 255, 255, 0, 255 );
		
	unicode::_sprintf(szText, GlobalText[200], m_sPetInfo.m_wLevel);			// 200 "��  ��: %d"
	g_pRenderText->RenderText(iGBox1PosX+2, iGBox1PosY+8, szText, 70-14, 0, RT3_SORT_CENTER);
	g_pRenderText->RenderText(iGBox2PosX+2, iGBox2PosY+8, GlobalText[1218], 70-14, 0, RT3_SORT_CENTER);	// "��ɼ���"
	
	g_pRenderText->SetFont(g_hFont);	
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );

#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], m_sPetInfo.m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+28, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iGBox1PosX+7, iGBox1PosY+40, 151, 12);					// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(m_sPetInfo.m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iGBox1PosX+9, iGBox1PosY+42, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], m_sPetInfo.m_dwExp1, m_sPetInfo.m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+59, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															m_sPetInfo.m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+72, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], m_sPetInfo.m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+85, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[698], (185+(m_sPetInfo.m_wLevel*15)));					// "��� ������ ���: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+98, szText, 0, 0, RT3_SORT_CENTER);

#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// �� ����
	unicode::_sprintf(szText, GlobalText[358], m_sPetInfo.m_wLife, 255);						// "����:%d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+34, szText, 0, 0, RT3_SORT_CENTER);
	RenderImage(IMAGE_PETINFO_LIFEBAR, iGBox1PosX+7, iGBox1PosY+46, 151, 12);					// LifeBar
	// HPBar length = (�����ִ�HP * ��ü����(151-4) / �ִ�HP(255)
	int iHP = (min(m_sPetInfo.m_wLife,255)*147)/255;		
	RenderImage(IMAGE_PETINFO_LIFE, iGBox1PosX+9, iGBox1PosY+48, iHP, 8);	
	unicode::_sprintf(szText, GlobalText[357], m_sPetInfo.m_dwExp1, m_sPetInfo.m_dwExp2);		// "����ġ: %d/%d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+67, szText, 0, 0, RT3_SORT_CENTER);
	unicode::_sprintf(szText, GlobalText[203], m_aiDamage[0], m_aiDamage[1], 
															m_sPetInfo.m_wAttackSuccess);		// "���ݷ�(��): %d~%d (%d)"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+82, szText, 0, 0, RT3_SORT_CENTER);	
	unicode::_sprintf(szText, GlobalText[64], m_sPetInfo.m_wAttackSpeed);						// "���ݼӵ�: %d"
	g_pRenderText->RenderText(iGBox1PosX+10, iGBox1PosY+97, szText, 0, 0, RT3_SORT_CENTER);	
		
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION

	// SkillBox
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+28, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+68, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+108, 32.f, 38.f);
	RenderImage(IMAGE_PETINFO_SKILLBOX, iGBox2PosX+10, iGBox2PosY+148, 32.f, 38.f);
	// Skill	(x = SKillbox.x + 7, y = SkillBox.y + 6)
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+34, 19.f, 27.f, 1.f, 0.f);		
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+74, 19.f, 27.f, 21.f, 0.f);
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+114, 19.f, 27.f, 41.f, 0.f);
	RenderImage(IMAGE_PETINFO_SKILL, iGBox2PosX+17, iGBox2PosY+154, 19.f, 27.f, 61.f, 0.f);
	
#ifdef KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+45, GlobalText[1219], 0, 0, RT3_SORT_CENTER);	// "�⺻ �ൿ"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+85, GlobalText[1220], 0, 0, RT3_SORT_CENTER);	// "���� �ڵ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+125, GlobalText[1221], 0, 0, RT3_SORT_CENTER);	// "���ΰ� �Բ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+165, GlobalText[1222], 0, 0, RT3_SORT_CENTER);	// "Ÿ�� ����"
#else // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+41, GlobalText[1219], 0, 0, RT3_SORT_CENTER);	// "�⺻ �ൿ"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+81, GlobalText[1220], 0, 0, RT3_SORT_CENTER);	// "���� �ڵ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+121, GlobalText[1221], 0, 0, RT3_SORT_CENTER);	// "���ΰ� �Բ� ����"
	g_pRenderText->RenderText(iGBox2PosX+52, iGBox2PosY+161, GlobalText[1222], 0, 0, RT3_SORT_CENTER);	// "Ÿ�� ����"
#endif // KJH_FIX_WOPS_K27950_REQUIRE_CHARISMA_PETINFORMATION
	
	return true;
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM																			//## �ҽ����� �����.

//---------------------------------------------------------------------------------------------
// RenderGroupBox()
void CNewUIPetInfoWindow::RenderGroupBox( int iPosX, int iPosY, int iWidth, int iHeight, int iTitleWidth/* =60 */, int iTitleHeight/* =20  */ )
{
	// ���
	EnableAlphaTest();

	glColor4f ( 0.f, 0.f, 0.f, 0.9f );
	RenderColor( float(iPosX+3), float(iPosY+2), float(iTitleWidth-8), float(iTitleHeight) );
 	glColor4f ( 0.f, 0.f, 0.f, 0.6f );							
 	RenderColor( float(iPosX+3), float(iPosY+2+iTitleHeight), float(iWidth-7), float(iHeight-iTitleHeight-7) );

	EndRenderColor();
	
	// �𼭸�
	RenderImage(IMAGE_PETINFO_TABLE_TOP_LEFT, iPosX, iPosY, 14, 14);
	RenderImage(IMAGE_PETINFO_TABLE_TOP_RIGHT, iPosX+iTitleWidth-14, iPosY, 14, 14);
	RenderImage(IMAGE_PETINFO_TABLE_TOP_RIGHT, iPosX+iWidth-14, iPosY+iTitleHeight, 14, 14);
	RenderImage(IMAGE_PETINFO_TABLE_BOTTOM_LEFT, iPosX, iPosY+iHeight-14, 14, 14);
	RenderImage(IMAGE_PETINFO_TABLE_BOTTOM_RIGHT, iPosX+iWidth-14, iPosY+iHeight-14, 14, 14);

	// ��
	RenderImage(IMAGE_PETINFO_TABLE_TOP_PIXEL, iPosX+6, iPosY, iTitleWidth-12, 14);
	RenderImage(IMAGE_PETINFO_TABLE_RIGHT_PIXEL, iPosX+iTitleWidth-14, iPosY+6, 14, iTitleHeight-6);
	RenderImage(IMAGE_PETINFO_TABLE_TOP_PIXEL, iPosX+iTitleWidth-5, iPosY+iTitleHeight, iWidth-iTitleWidth-6, 14);
	RenderImage(IMAGE_PETINFO_TABLE_RIGHT_PIXEL, iPosX+iWidth-14, iPosY+iTitleHeight+6, 14, iHeight-iTitleHeight-14);
	RenderImage(IMAGE_PETINFO_TABLE_BOTTOM_PIXEL, iPosX+6, iPosY+iHeight-14, iWidth-12, 14);
	RenderImage(IMAGE_PETINFO_TABLE_LEFT_PIXEL, iPosX, iPosY+6, 14, iHeight-14);
}



//---------------------------------------------------------------------------------------------
// GetLayerDepth()
float CNewUIPetInfoWindow::GetLayerDepth()
{ return 2.3f; }


//---------------------------------------------------------------------------------------------
// BtnProcess()
bool CNewUIPetInfoWindow::BtnProcess()
{
	POINT ptExitBtn1 = { m_Pos.x+169, m_Pos.y+7 };
	
	// Exit1 ��ư (�⺻ó��)
	if(SEASON3B::IsPress(VK_LBUTTON) && CheckMouseIn(ptExitBtn1.x, ptExitBtn1.y, 13, 12))
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_PET);
		return true;
	}

	// Exit2 ��ư 
	if(m_BtnExit.UpdateMouseEvent() == true)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_PET);
		return true;
	}
	
	return false;
}

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
//---------------------------------------------------------------------------------------------
// UpdatePetInfo()
bool CNewUIPetInfoWindow::UpdatePetInfo()
{
	if( GetBaseClass(Hero->Class) != CLASS_DARK_LORD )
		return true;
	
	// �ǹ�ư ���¿� ���� ó��
	switch( m_iNumCurOpenTab )
	{
	case TAB_TYPE_DARKHORSE:		
		{
			// ��ũȣ�� ���� üũ		ITEM_HELPER+4 : ��ũȣ�� 
			if( GetPetInfo( m_sPetInfo, PET_TYPE_DARK_HORSE, EQUIPMENT_HELPER, ITEM_HELPER+4 ) )
			{
				m_bEquipedDarkHorse = true;
			}
			else
			{
				// ��ũȣ���� �����ϴ�.
				memset( &m_sPetInfo, 0, sizeof(PET_INFO) );
				m_bEquipedDarkHorse = false;
			}
		}
		break;
	case TAB_TYPE_DARKSPIRIT:
		{
			// ��ũ���Ǹ� ���� üũ		ITEM_HELPER+5 : ��ũ���Ǹ� 
			if( GetPetInfo( m_sPetInfo, PET_TYPE_DARK_SPIRIT, EQUIPMENT_WEAPON_LEFT, ITEM_HELPER+5 ) )
			{
				m_bEquipedDarkSpirit = true;
			}
			else
			{
				// ��ũ���Ǹ��� �����ϴ�.
				memset( &m_sPetInfo, 0, sizeof(PET_INFO) );
				m_bEquipedDarkSpirit = false;
			}
		}
		break;
	default:
		break;
	}
	
	return true;
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.

//---------------------------------------------------------------------------------------------
// CalcPetType
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
void CNewUIPetInfoWindow::CalcDamage( int iNumTapButton )
{
	PET_INFO* pPetInfo = NULL;

	switch( iNumTapButton )
	{
	case TAB_TYPE_DARKHORSE:
		{
			int iSkillDamage[2];
			CharacterMachine->GetSkillDamage( AT_SKILL_DARK_HORSE, &iSkillDamage[0], &iSkillDamage[1] );

			pPetInfo = Hero->GetEquipedPetInfo(PET_TYPE_DARK_HORSE);
		    m_aiDamage[0] = pPetInfo->m_wDamageMin+iSkillDamage[0];
			m_aiDamage[1] = pPetInfo->m_wDamageMax+iSkillDamage[1];
		}
		break;
	case TAB_TYPE_DARKSPIRIT: 
		{
			m_fAddDamagePercent = 0.f;
			m_aiDamage[0] = 0;
			m_aiDamage[1] = 0;

			if ( CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type!=-1 )
			{
				m_fAddDamagePercent = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].MagicPower;
			}
			
			pPetInfo = Hero->GetEquipedPetInfo(PET_TYPE_DARK_SPIRIT);

			m_fAddDamagePercent /= 100.f;
			m_aiDamage[0] = pPetInfo->m_wDamageMin+(int)(pPetInfo->m_wDamageMin*m_fAddDamagePercent);
			m_aiDamage[1] = pPetInfo->m_wDamageMax+(int)(pPetInfo->m_wDamageMax*m_fAddDamagePercent);
		}
		break;
	}
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM														//## �ҽ����� �����.
//---------------------------------------------------------------------------------------------
// GetPetInfo()
bool CNewUIPetInfoWindow::GetPetInfo( PET_INFO& sPetinfo, int iPetType, int iEquipmentIndex, int iItemType )
{
	ITEM* pItem = NULL;	

	/* 
	. �����Ӹ��� ������û�� ����.
	. �ǽð����� �������� �Ϸ���, �������� ���� (������� ���ʴ� �ѹ� ������û �ϴ¹��)
	. ����� ��â�� �� ������ ������û
	*/
	//SendRequestPetInfo( iPetType, 0, iEquipmentIndex );
	
	giPetManager::GetPetInfo(m_sPetInfo, 421-iPetType);

	// Lock
	
	pItem = &CharacterMachine->Equipment[iEquipmentIndex];

	if( pItem->Type != iItemType )
	{
		return false;
	}

	switch( iPetType )
	{
	case PET_TYPE_DARK_HORSE:
		{
			int iSkillDamage[2];
			CharacterMachine->GetSkillDamage( AT_SKILL_DARK_HORSE, &iSkillDamage[0], &iSkillDamage[1] );
		    m_aiDamage[0] = m_sPetInfo.m_wDamageMin+iSkillDamage[0];
			m_aiDamage[1] = m_sPetInfo.m_wDamageMax+iSkillDamage[1];
		}
		break;
	case PET_TYPE_DARK_SPIRIT: 
		{
			m_fAddDamagePercent = 0.f;
			m_aiDamage[0] = 0;
			m_aiDamage[1] = 0;
			
			if ( CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type!=-1 )
			{
				m_fAddDamagePercent = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].MagicPower;
			}
			
			m_fAddDamagePercent /= 100.f;
			m_aiDamage[0] = m_sPetInfo.m_wDamageMin+(int)(m_sPetInfo.m_wDamageMin*m_fAddDamagePercent);
			m_aiDamage[1] = m_sPetInfo.m_wDamageMax+(int)(m_sPetInfo.m_wDamageMax*m_fAddDamagePercent);
		}
		break;
	default:
		break;
	}
	// Unlock
	
	return true;
	
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM													//## �ҽ����� �����.

	
//---------------------------------------------------------------------------------------------
// LoadImages()
void CNewUIPetInfoWindow::LoadImages()
{
	// �⺻â
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_PETINFO_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back04.tga", IMAGE_PETINFO_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-L.tga", IMAGE_PETINFO_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-R.tga", IMAGE_PETINFO_RIGHT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_PETINFO_BOTTOM, GL_LINEAR);
	LoadBitmap("Interface\\newui_exit_00.tga", IMAGE_PETINFO_BTN_EXIT, GL_LINEAR);
	// �� ��ư
	LoadBitmap("Interface\\newui_guild_tab04.tga", IMAGE_PETINFO_TAB_BUTTON, GL_LINEAR);

	// GroupBox
	LoadBitmap("Interface\\newui_item_table01(L).tga", IMAGE_PETINFO_TABLE_TOP_LEFT);
	LoadBitmap("Interface\\newui_item_table01(R).tga", IMAGE_PETINFO_TABLE_TOP_RIGHT);
	LoadBitmap("Interface\\newui_item_table02(L).tga", IMAGE_PETINFO_TABLE_BOTTOM_LEFT);
	LoadBitmap("Interface\\newui_item_table02(R).tga", IMAGE_PETINFO_TABLE_BOTTOM_RIGHT);
	LoadBitmap("Interface\\newui_item_table03(Up).tga", IMAGE_PETINFO_TABLE_TOP_PIXEL);
	LoadBitmap("Interface\\newui_item_table03(Dw).tga", IMAGE_PETINFO_TABLE_BOTTOM_PIXEL);
	LoadBitmap("Interface\\newui_item_table03(L).tga", IMAGE_PETINFO_TABLE_LEFT_PIXEL);
	LoadBitmap("Interface\\newui_item_table03(R).tga", IMAGE_PETINFO_TABLE_RIGHT_PIXEL);

	// Skill
	LoadBitmap("Interface\\newui_command.jpg", IMAGE_PETINFO_SKILL, GL_LINEAR);
	LoadBitmap("Interface\\newui_skillbox.jpg", IMAGE_PETINFO_SKILLBOX, GL_LINEAR);
	// LifeBar
	LoadBitmap("Interface\\newui_pet_lifebar01.jpg", IMAGE_PETINFO_LIFEBAR, GL_LINEAR);
	LoadBitmap("Interface\\newui_pet_lifebar02.jpg", IMAGE_PETINFO_LIFE, GL_LINEAR);
}

//---------------------------------------------------------------------------------------------
// UnLoadImage()
void CNewUIPetInfoWindow::UnloadImages()
{
	// �⺻â
	DeleteBitmap(IMAGE_PETINFO_BACK);
	DeleteBitmap(IMAGE_PETINFO_TOP);
	DeleteBitmap(IMAGE_PETINFO_LEFT);
	DeleteBitmap(IMAGE_PETINFO_RIGHT);
	DeleteBitmap(IMAGE_PETINFO_BOTTOM);
	DeleteBitmap(IMAGE_PETINFO_BTN_EXIT);

	// �� ��ư
	DeleteBitmap(IMAGE_PETINFO_TAB_BUTTON);

	// GroupBox
	DeleteBitmap(IMAGE_PETINFO_TABLE_RIGHT_PIXEL);
	DeleteBitmap(IMAGE_PETINFO_TABLE_LEFT_PIXEL);
	DeleteBitmap(IMAGE_PETINFO_TABLE_BOTTOM_PIXEL);
	DeleteBitmap(IMAGE_PETINFO_TABLE_TOP_PIXEL);
	DeleteBitmap(IMAGE_PETINFO_TABLE_BOTTOM_RIGHT);
	DeleteBitmap(IMAGE_PETINFO_TABLE_BOTTOM_LEFT);
	DeleteBitmap(IMAGE_PETINFO_TABLE_TOP_RIGHT);
	DeleteBitmap(IMAGE_PETINFO_TABLE_TOP_LEFT);

	// Skill
	DeleteBitmap(IMAGE_PETINFO_SKILL);
	DeleteBitmap(IMAGE_PETINFO_SKILLBOX);

	// LifeBar
	DeleteBitmap(IMAGE_PETINFO_LIFEBAR);
	DeleteBitmap(IMAGE_PETINFO_LIFE);
}

void CNewUIPetInfoWindow::OpenningProcess()
{
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM								
	CalcDamage(m_iNumCurOpenTab);	
#else // KJH_FIX_DARKLOAD_PET_SYSTEM							//## �ҽ����� �����.
	RequestPetInfo();
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM							//## �ҽ����� �����.
}

void CNewUIPetInfoWindow::ClosingProcess()
{

}

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM								//## �ҽ����� �����.
void CNewUIPetInfoWindow::RequestPetInfo()
{
	switch( m_iNumCurOpenTab )
	{
	case TAB_TYPE_DARKHORSE:
		{
			SendRequestPetInfo( PET_TYPE_DARK_HORSE, 0, EQUIPMENT_HELPER );
		}
		break;
	case TAB_TYPE_DARKSPIRIT: 
		{
			SendRequestPetInfo( PET_TYPE_DARK_SPIRIT, 0, EQUIPMENT_WEAPON_LEFT );
		}
		break;
	default:
		break;
	}
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM							//## �ҽ����� �����.
