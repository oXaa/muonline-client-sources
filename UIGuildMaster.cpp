//////////////////////////////////////////////////////////////////////////
//  
//  UIGuildMaster.cpp
//  
//  내  용 : NPC 길드마스터 클릭시 보여주는 인터페이스
//  
//  날  짜 : 2004년 11월 09일
//  
//  작성자 : 강 병 국
//  
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIGuildInfo.h"
#include "ZzzInventory.h"
#include "ZzzOpenglUtil.h"
#include "ZzzTexture.h"
#include "UIManager.h"
#include "UIGuildMaster.h"
#include "DSPlaySound.h"
#include "wsclientinline.h"
#include "NewUICommonMessageBox.h"

extern CUITextInputBox*	g_pSingleTextInputBox;
extern int				g_iChatInputType;
extern float			g_fScreenRate_x;
extern float			g_fScreenRate_y;

static eCurrentMode		m_nCurrMode;
static eCurrentStep		m_eCurrStep;
static BYTE				m_byRelationShipType;
static BYTE				m_byRelationShipRequestType;
static BYTE				m_byTargetUserIndexH;
static BYTE				m_byTargetUserIndexL;

void RenderGoldRect( float fPos_x, float fPos_y, float fWidth, float fHeight, int iFillType = 0 );

void EditGuildMarkMouseAction( int iPos_x, int iPos_y )
{
	int i, j;
	float x, y;
	Hero->Object.Angle[2] = 90.f + 22.5f;
	for( i=0 ; i<8 ; ++i )
	{
		for( j=0; j<8 ; ++j )
		{
			x = iPos_x + j*15 + 50;
			y = iPos_y + i*15 + 100;
			if( MouseX>=x && MouseX<x+15 && MouseY>=y && MouseY<y+15 )
			{
				if( MouseLButton )
					GuildMark[MARK_EDIT].Mark[i*8+j] = SelectMarkColor;
				if( MouseRButton )
					GuildMark[MARK_EDIT].Mark[i*8+j] = 0;
			}
		}
	}
	for( i=0 ; i<2 ; ++i )
	{
		for( j=0 ; j<8 ; ++j )
		{
			x = iPos_x + j*20 + 15;
			y = iPos_y + i*20 + 260;
			if( MouseX>=x && MouseX<x+20 && MouseY>=y && MouseY<y+20 )
			{
				if( MouseLButtonPush )
				{
					MouseLButtonPush = FALSE;
					PlayBuffer( SOUND_CLICK01 );
					SelectMarkColor = i*8 + j;
				}
			}
		}
	}
}

void RenderGuildMark( int iPos_x, int iPos_y )
{
	int i, j;
	float x, y;
	for( i=0 ; i<8 ; ++i )
	{
		for( j=0 ; j<8 ; ++j )
		{
			x = (float)iPos_x + j*15 + 50;
			y = (float)iPos_y + i*15 + 100;
			RenderGuildColor( x+1, y+1, 13, 13, GuildMark[MARK_EDIT].Mark[i*8+j] );
		}
	}
	for( i=0 ; i<2 ; ++i )
	{
		for( j=0 ; j<8 ; ++j )
		{
			x = (float)iPos_x + j*20 + 15;
			y = (float)iPos_y + i*20 + 260;
			RenderGuildColor( x+1, y+1, 18, 18, i*8+j );
		}
	}
    x = (float)iPos_x + 15;
	y = (float)iPos_y + 230;
    RenderGuildColor( x+1, y+1, 23, 23, SelectMarkColor );

	g_pRenderText->SetFont(g_hFont);
	g_pRenderText->SetTextColor(230, 230, 230, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 0);
	g_pRenderText->RenderText(iPos_x+50, iPos_y+230, GlobalText[183]);
	g_pRenderText->RenderText(iPos_x+50, iPos_y+245, GlobalText[184]);	
}

int DoEditGuildMarkConfirmAction( POPUP_RESULT Result )
{
	if( Result == POPUP_RESULT_YES )
	{
		m_nCurrMode = MODE_EDIT_GUILDMARK;
		m_eCurrStep = STEP_EDIT_GUILD_MARK;
		SendRequestGuildMaster( TRUE );

		// 기존 길드 마크 표시
		if( Hero->GuildStatus != G_NONE )
			memcpy( &GuildMark[MARK_EDIT], &GuildMark[Hero->GuildMarkIndex], sizeof(MARK_t) );
	}
	return 1;
}

int DoGuildRelationReplyAction( POPUP_RESULT Result )
{
	if( Result == POPUP_RESULT_YES )
	{
		SendRequestGuildRelationShipResult( m_byRelationShipType, m_byRelationShipRequestType, 0x01, m_byTargetUserIndexH, m_byTargetUserIndexL );
	}
	else if( (Result & POPUP_RESULT_NO) == POPUP_RESULT_NO )
	{
		SendRequestGuildRelationShipResult( m_byRelationShipType, m_byRelationShipRequestType, 0x00, m_byTargetUserIndexH, m_byTargetUserIndexL );
	}
	return 1;
}

CUIGuildMaster::CUIGuildMaster()
{
	m_bOpened = false;
	SetPosition( 640-190, 0 );
	SetSize( 190, 90 );
	m_nCurrMode		= MODE_NONE;
	m_eCurrStep		= STEP_MAIN;

	// 길드 만들기 버튼
	m_CreateGuildButton.Init( 1, GlobalText[1303] );
	m_CreateGuildButton.SetParentUIID( GetUIID() );
	m_CreateGuildButton.SetSize( 100, 20 );

	// 길드마크 변경 버튼
	m_EditGuildMarkButton.Init( 2, GlobalText[1304] );
	m_EditGuildMarkButton.SetParentUIID( GetUIID() );
	m_EditGuildMarkButton.SetSize( 100, 20 );
	m_dwEditGuildMarkConfirmPopup = 0;

	// 이전, 다음 버튼
	m_PreviousButton.Init( 4, GlobalText[1306] );
	m_PreviousButton.SetParentUIID( GetUIID() );
	m_PreviousButton.SetPosition( GetPosition_x()+15+30, GetPosition_y()+360 );
	m_PreviousButton.SetSize( 50, 18 );
	m_NextButton.Init( 5, GlobalText[1305] );
	m_NextButton.SetParentUIID( GetUIID() );
	m_NextButton.SetPosition( GetPosition_x()+15+82, GetPosition_y()+360 );
	m_NextButton.SetSize( 50, 18 );

	m_dwGuildRelationShipReplyPopup = 0;
	m_byRelationShipType = 0;
	m_byRelationShipRequestType = 0;
	m_byTargetUserIndexH = 0;
	m_byTargetUserIndexL = 0;
}

CUIGuildMaster::~CUIGuildMaster()
{
}

BOOL CUIGuildMaster::IsValidGuildName( const char* szName )
{
	if( strlen( szName ) >= 4 )
		return TRUE;
	else
		return FALSE;
}

BOOL CUIGuildMaster::IsValidGuildMark()
{
	// 길드마크를 그렸는지 검사
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	BOOL bDraw = FALSE;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	for( int i=0;i<64;i++ )
	{
		if( GuildMark[MARK_EDIT].Mark[i] != 0 )
			return TRUE;
	}

	return FALSE;
}

void CUIGuildMaster::StepPrev()
{
	switch( m_nCurrMode )
	{
	case MODE_CREATE_GUILD:
		switch( m_eCurrStep )
		{
			case STEP_CREATE_GUILDINFO:		m_nCurrMode = MODE_NONE;	m_eCurrStep = STEP_MAIN;	break;
			case STEP_CONFIRM_GUILDINFO:	m_eCurrStep = STEP_CREATE_GUILDINFO;					break;
			default:						assert( !"잘못된 m_eCurrStep" );		break;
		}
		break;
	case MODE_EDIT_GUILDMARK:
		switch( m_eCurrStep )
		{
			case STEP_EDIT_GUILD_MARK:		m_nCurrMode = MODE_NONE;	m_eCurrStep = STEP_MAIN;	break;
			case STEP_CONFIRM_GUILDINFO:	m_eCurrStep = STEP_EDIT_GUILD_MARK;		break;
			default:						assert( !"잘못된 m_eCurrStep" );		break;
		}
		break;
	default:
		assert( !"잘못된 m_nCurrMode" );
		break;
	}
}

void CUIGuildMaster::StepNext()
{
	switch( m_nCurrMode )
	{
	case MODE_CREATE_GUILD:
		switch( m_eCurrStep )
		{
			case STEP_MAIN:					m_eCurrStep = STEP_CREATE_GUILDINFO;	break;
			case STEP_CREATE_GUILDINFO:		m_eCurrStep = STEP_CONFIRM_GUILDINFO;	break;
			default:						assert( !"잘못된 m_eCurrStep" );		break;
		}
		break;
	case MODE_EDIT_GUILDMARK:
		switch( m_eCurrStep )
		{
			case STEP_MAIN:					m_eCurrStep = STEP_EDIT_GUILD_MARK;		break;
			case STEP_EDIT_GUILD_MARK:		m_eCurrStep = STEP_CONFIRM_GUILDINFO;	break;
			default:						assert( !"잘못된 m_eCurrStep" );		break;
		}
		break;
	default:
		assert( !"잘못된 m_nCurrMode" );
		break;
	}
}

void CUIGuildMaster::CloseMyPopup()
{
	DWORD dwCurrPopupID = g_pUIPopup->GetPopupID();
	if( dwCurrPopupID == m_dwEditGuildMarkConfirmPopup || dwCurrPopupID == m_dwGuildRelationShipReplyPopup )
		g_pUIPopup->CancelPopup();
}

void CUIGuildMaster::DoCreateGuildAction()
{
	// 길드마크 편집창 입력처리
	EditGuildMarkMouseAction( GetPosition_x(), GetPosition_y() );

	// 길드명과 마크 검사하고 다음 단계로..
	if( m_NextButton.DoMouseAction() )
	{
		if( g_iChatInputType == 1 )
		{
			g_pSingleTextInputBox->GetText( GuildMark[MARK_EDIT].GuildName );
			g_pSingleTextInputBox->GetText( InputText[0] );
		}
		if( CheckName() )
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCanNotUseWordMsgBoxLayout));
		}
		else if( CheckSpecialText( InputText[0] ) )
		{
			// 391 "특수문자는 사용하실 수 없습니다."
			SEASON3B::CreateOkMessageBox(GlobalText[391]);
		}
		else
		{
			// 길드명 검사
			if( IsValidGuildName( InputText[0] ) )
			{
				// 길드마크 검사
				if( IsValidGuildMark() )
				{
					if( g_iChatInputType == 1 )
					{
						g_pSingleTextInputBox->SetText( NULL );
						g_pSingleTextInputBox->SetState( UISTATE_HIDE );
					}
					else if( g_iChatInputType == 0 )
					{
						strcpy( GuildMark[MARK_EDIT].GuildName, InputText[0] );
					}
					StepNext();
				}
				else
				{
					// 426 "길드 마크를 그려주세요."
					SEASON3B::CreateOkMessageBox(GlobalText[426]);
				}
			}
			else
			{
				// 390 "2글자이상 입력해주세요."
				SEASON3B::CreateOkMessageBox(GlobalText[390]);
			}
		}
		if( g_iChatInputType == 1 )
		{
			g_pSingleTextInputBox->SetText( NULL );
			SaveIMEStatus();
			g_pSingleTextInputBox->SetState( UISTATE_HIDE );	// 길드 입력창 숨김
		}
	}

	// 이전 단계로..
	if( m_PreviousButton.DoMouseAction() )
	{
		Hero->GuildMarkIndex = -1;
		if( g_iChatInputType == 1 )
		{
			g_pSingleTextInputBox->SetText( NULL );
			SaveIMEStatus();
			g_pSingleTextInputBox->SetState( UISTATE_HIDE );	// 길드 입력창 숨김
		}
		memset( InputText[0], 0, MAX_ID_SIZE );
		InputLength[0] = 0;
		InputTextMax[0] = MAX_ID_SIZE;
		StepPrev();
	}
}

void CUIGuildMaster::RenderCreateGuild()
{
	POINT ptOrigin = { GetPosition_x()+25, GetPosition_y()+60 };

	// 입력창바탕 출력
	RenderBitmap( BITMAP_INVENTORY+11, ptOrigin.x+33, ptOrigin.y-4, 110, 18, 0.f, 0.f, 110.f/128.f, 18.f/32.f );

	// 길드명 출력
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor(230, 230, 230, 255);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[182]);

	// 입력창 출력
	if( g_iChatInputType == 1 )
	{
		g_pSingleTextInputBox->SetState( UISTATE_NORMAL );
		g_pSingleTextInputBox->SetOption( UIOPTION_NULL );
		g_pSingleTextInputBox->SetBackColor( 0, 0, 0, 0 );
		g_pSingleTextInputBox->SetTextLimit( 8 );
		g_pSingleTextInputBox->SetSize( 70, 14 );
#if SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
		g_pSingleTextInputBox->SetPosition( ptOrigin.x+38+5, ptOrigin.y );
#else
		g_pSingleTextInputBox->SetPosition( ptOrigin.x+38, ptOrigin.y );
#endif
		g_pSingleTextInputBox->GiveFocus();
		g_pSingleTextInputBox->Render();	// 길드명 짓기※
	}
	else if( g_iChatInputType == 0 )
	{
		InputTextWidth = 100;
		RenderInputText( ptOrigin.x+38, ptOrigin.y, 0 );
		InputTextWidth = 255;
	}

	// 길드마크 편집창 출력
	CreateGuildMark( MARK_EDIT );
	RenderGuildMark( GetPosition_x(), GetPosition_y() );

	// 이전, 다음 버튼 출력
	m_PreviousButton.Render();
	m_NextButton.Render();
}

void CUIGuildMaster::DoCreateInfoAction()
{
	if( m_NextButton.DoMouseAction() )
	{
		// 길드마크 얻기
		BYTE Mark[32];
		for( int i=0 ; i<64; i++ )
		{
			if( i % 2 == 0 )
      			Mark[i / 2] = GuildMark[MARK_EDIT].Mark[i] << 4;
			else
     			Mark[i / 2] += GuildMark[MARK_EDIT].Mark[i];
		}

		// 길드 생성시
		if( m_nCurrMode == MODE_CREATE_GUILD )
		{
			SendRequestCreateGuild( 0, (BYTE*)GuildMark[MARK_EDIT].GuildName, Mark );
		}
		// 길드마크 변경시
//		else if( m_nCurrMode == MODE_EDIT_GUILDMARK )
//		{
//			SendRequestEditGuildMark( (BYTE*)GuildMark[MARK_EDIT].GuildName, Mark );
//		}

		// UI 닫기
		SendRequestGuildMaster( FALSE );
		Close();

		g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPCGUILDMASTER);
	}

	if( m_PreviousButton.DoMouseAction() )
	{
		StepPrev();
	}
}

void CUIGuildMaster::RenderCreateInfo()
{
	POINT ptOrigin = { GetPosition_x()+25, GetPosition_y()+65 };
	
	g_pRenderText->SetFont(g_hFont);
	
	// 길드 이름
	char szTemp[128];
	g_pRenderText->SetBgColor(0);
	
	RenderGoldRect( ptOrigin.x, ptOrigin.y, 140, 20.f );
	sprintf( szTemp, "%s : %s", GlobalText[182], GuildMark[MARK_EDIT].GuildName );
	ptOrigin.y += 6;
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, szTemp, 140, 0, RT3_SORT_CENTER);

	// 길드마크
	ptOrigin.x += 44;
	ptOrigin.y += 33;
	RenderGoldRect( ptOrigin.x, ptOrigin.y, 53.f, 53.f );
	CreateGuildMark( MARK_EDIT );
	RenderBitmap( BITMAP_GUILD, ptOrigin.x+3, ptOrigin.y+3, 48, 48 );

	// 이전, 다음 버튼
	m_PreviousButton.Render();
	m_NextButton.Render();
}

void CUIGuildMaster::DoEditGuildMarkAction()
{
	EditGuildMarkMouseAction( GetPosition_x(), GetPosition_y() );

	if( m_NextButton.DoMouseAction() )
	{
		if( IsValidGuildMark() )
		{
			StepNext();
		}
		else
		{
			SEASON3B::CreateOkMessageBox(GlobalText[426]);
		}
	}

	if( m_PreviousButton.DoMouseAction() )
	{
		StepPrev();
	}
}

void CUIGuildMaster::RenderEditGuildMark()
{
	POINT ptOrigin = { GetPosition_x()+25, GetPosition_y()+60 };

	// 길드 이름
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor(230, 230, 230, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 0);
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[182]);

	// 길드명 표시
	char Text[100];
	sprintf( Text, "%s ( Score:%d )", GuildMark[Hero->GuildMarkIndex].GuildName, GuildTotalScore );
	g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, Text, 140*g_fScreenRate_x, 0, RT3_SORT_CENTER);
	g_pRenderText->SetFont(g_hFont);
	
	// 길드마크 편집창 출력
	CreateGuildMark( MARK_EDIT );
	RenderGuildMark( GetPosition_x(), GetPosition_y() );

	// 이전, 다음 버튼
	m_PreviousButton.Render();
	m_NextButton.Render();
}

void CUIGuildMaster::DoGuildMasterMainAction()
{
	// 길드 만들기 눌렀을때..
	if( m_CreateGuildButton.DoMouseAction() )
	{
		m_nCurrMode = MODE_CREATE_GUILD;
		m_eCurrStep = STEP_CREATE_GUILDINFO;
		GuildInputEnable = TRUE;
		SendRequestGuildMaster( TRUE );
	}
	// 길드마크 변경 눌렀을때..
	if( m_EditGuildMarkButton.DoMouseAction() )
	{
		// 1269 "아직 지원하지 않는 기능입니다."
		char szText[50];
		strcpy( szText, GlobalText[1269] );
		m_dwEditGuildMarkConfirmPopup = g_pUIPopup->SetPopup( szText, 1, 50, POPUP_OK, NULL );
/*		char szText[4][50];
		strcpy( szText[0], GlobalText[1370] );
		strcpy( szText[1], GlobalText[1371] );
		strcpy( szText[2], GlobalText[1372] );
		strcpy( szText[3], GlobalText[1373] );
		m_dwEditGuildMarkConfirmPopup = g_pUIPopup->SetPopup( &szText[0][0], 4, 50, POPUP_YESNO, ::DoEditGuildMarkConfirmAction );*/
	}

	// 닫기 눌렀을때..
	if( MouseLButtonPush && CheckMouseIn( GetPosition_x()+25, GetPosition_y()+395, 24, 24 ) )
	{
		MouseLButtonPush = FALSE;
		MouseUpdateTime = 0;
		MouseUpdateTimeMax = 6;
		SendRequestGuildMaster( FALSE );
       	PlayBuffer( SOUND_CLICK01 );
		Close();
		g_pNewUIMng->ShowInterface(SEASON3B::INTERFACE_NPCGUILDMASTER, false);
		g_pNewUIMng->EnableInterface(SEASON3B::INTERFACE_NPCGUILDMASTER, false);
	}
}

void CUIGuildMaster::RenderGuildMasterMain()
{
	POINT ptOrigin = { GetPosition_x()+25, GetPosition_y()+60 };

	g_pRenderText->SetTextColor(230, 230, 230, 255);
	g_pRenderText->SetBgColor(0);

	if( Hero->GuildStatus != G_NONE )
	{
		char Text[100];
		// 길드명 표시
		sprintf( Text, "%s ( Score:%d )", GuildMark[Hero->GuildMarkIndex].GuildName, GuildTotalScore );
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, Text, 140*g_fScreenRate_x, 0, RT3_SORT_CENTER);

		// 버튼활성화
		m_CreateGuildButton.SetState( UISTATE_DISABLE );
		m_EditGuildMarkButton.SetState( UISTATE_NORMAL );
	}
	else
	{
		g_pRenderText->RenderText(ptOrigin.x, ptOrigin.y, GlobalText[181] );
		// 길드 마스터가 되시겠습니까? 표시

		// 버튼활성화
		m_CreateGuildButton.SetState( UISTATE_NORMAL );
		m_EditGuildMarkButton.SetState( UISTATE_DISABLE );
	}

	// 길드 만들기, 길드마크 변경, 클랜 만들기 버튼 출력
	ptOrigin.x = GetPosition_x()+45;
	ptOrigin.y += 30;
	m_CreateGuildButton.SetPosition( ptOrigin.x, ptOrigin.y );
	m_CreateGuildButton.Render();
	ptOrigin.y += 24;
	m_EditGuildMarkButton.SetPosition( ptOrigin.x, ptOrigin.y );
	m_EditGuildMarkButton.Render();

	// 닫기( X ) 버튼
	glColor3f( 1.f, 1.f, 1.f );
	float Width=24.f;float Height=24.f;float x=(float)GetPosition_x()+25;float y=(float)GetPosition_y()+395;
	RenderBitmap( BITMAP_INVENTORY_BUTTON, x, y, Width, Height, 0.f, 0.f, Width/32.f, Height/32.f );
	if( CheckMouseIn( x, y, Width, Height ) )
	{
		g_pRenderText->SetFont(g_hFont);
		g_pRenderText->SetTextColor(255, 255, 255, 255);
		g_pRenderText->SetBgColor(0, 0, 0, 255);
		
		RenderTipText( x, y-13, GlobalText[1002] );
	}
}

void CUIGuildMaster::ReceiveGuildRelationShip( BYTE byRelationShipType, BYTE byRequestType, BYTE  byTargetUserIndexH, BYTE byTargetUserIndexL )
{
	if( g_pUIPopup->GetPopupID() != 0 )
	{
		SendRequestGuildRelationShipResult( byRelationShipType, byRequestType, 0x00, byTargetUserIndexH, byTargetUserIndexL );
		return;
	}

	m_byRelationShipType = byRelationShipType;
	m_byRelationShipRequestType = byRequestType;
	m_byTargetUserIndexH = byTargetUserIndexH;
	m_byTargetUserIndexL = byTargetUserIndexL;

	int nCharKey = MAKEWORD(m_byTargetUserIndexL,m_byTargetUserIndexH);
	int nIndex = FindCharacterIndex(nCharKey);
	if( nIndex < 0 || nIndex >= MAX_CHARACTERS_CLIENT )
		return;
	CHARACTER* pPlayer = &CharactersClient[nIndex];

	char szText[3][64];
	if( m_byRelationShipType == 0x01 )			// Union
	{
		if( m_byRelationShipRequestType == 0x01 )	// Join
		{
#if SELECTED_LANGUAGE==LANGUAGE_ENGLISH || SELECTED_LANGUAGE==LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			sprintf( szText[0], GlobalText[1280] );					// 1280 "%s 님으로부터 길드연합"
			sprintf( szText[1], GlobalText[1281], pPlayer->ID );	// 1281 "가입 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );					// 1283 "수락하시겠습니까?"
#else
			sprintf( szText[0], GlobalText[1280], pPlayer->ID );	// 1280 "%s 님으로부터 길드연합"
			sprintf( szText[1], GlobalText[1281] );					// 1281 "가입 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );					// 1283 "수락하시겠습니까?"
#endif //SELECTED_LANGUAGE==LANGUAGE_ENGLISH || SELECTED_LANGUAGE==LANGUAGE_PHILIPPINES
		}
		else										// Break Off
		{
#if SELECTED_LANGUAGE==LANGUAGE_ENGLISH || SELECTED_LANGUAGE==LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			sprintf( szText[0], GlobalText[1280] );					// 1280 "%s 님으로부터 길드연합"
			sprintf( szText[1], GlobalText[1282], pPlayer->ID );	// 1282 "탈퇴 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );					// 1283 "수락하시겠습니까?"
#else
			sprintf( szText[0], GlobalText[1280], pPlayer->ID );	// 1280 "%s 님으로부터 길드연합"
			sprintf( szText[1], GlobalText[1282] );					// 1282 "탈퇴 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );					// 1283 "수락하시겠습니까?"
#endif //SELECTED_LANGUAGE==LANGUAGE_ENGLISH || SELECTED_LANGUAGE==LANGUAGE_PHILIPPINES
		}
	}
	else if( m_byRelationShipType == 0x02 )		// Rival
	{
		if( m_byRelationShipRequestType == 0x01 )	// Join
		{
			sprintf( szText[0], GlobalText[1284], pPlayer->ID );	// 1284 "%s 님으로부터 적대길드"
			sprintf( szText[1], GlobalText[1286] );				// 1286 "수락 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );				// 1283 "수락하시겠습니까?"
		}
		else										// Break Off
		{
			sprintf( szText[0], GlobalText[1284], pPlayer->ID );	// 1284 "%s 님으로부터 적대길드"
			sprintf( szText[1], GlobalText[1285] );				// 1285 "해제 요청이 들어왔습니다."
			sprintf( szText[2], GlobalText[1283] );				// 1283 "수락하시겠습니까?"
		}
	}

	m_dwGuildRelationShipReplyPopup = g_pUIPopup->SetPopup( &szText[0][0], 3, 64, POPUP_YESNO, ::DoGuildRelationReplyAction );
}

BOOL CUIGuildMaster::DoMouseAction()
{
	if( CheckMouseIn( GetPosition_x(), GetPosition_y(), GetWidth(), 256+177 ) )
		MouseOnWindow = TRUE;

	switch( m_eCurrStep )
	{
	case STEP_MAIN:
		DoGuildMasterMainAction();
		break;
	case STEP_CREATE_GUILDINFO:
		DoCreateGuildAction();
		break;
	case STEP_EDIT_GUILD_MARK:
		DoEditGuildMarkAction();
		break;
	case STEP_CONFIRM_GUILDINFO:
		DoCreateInfoAction();
		break;
	default:
		break;
	};

	return FALSE;
}

void CUIGuildMaster::Render()
{
	glColor3f( 1.f, 1.f, 1.f );

	POINT ptOrigin = { GetPosition_x(), GetPosition_y() };

	DisableAlphaBlend();
    RenderBitmap( BITMAP_INVENTORY, ptOrigin.x, ptOrigin.y, 190.f, 256.f, 0.f, 0.f, 190.f/256.f, 256.f/256.f );
    RenderBitmap( BITMAP_INVENTORY+1, ptOrigin.x, ptOrigin.y+256, 190.f, 177.f, 0.f, 0.f, 190.f/256.f, 177.f/256.f );

	EnableAlphaTest();
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor(220, 220, 220, 255);
	g_pRenderText->SetBgColor(20, 20, 20, 255);
    
	ptOrigin.x += 35;	ptOrigin.y += 12;
	switch( m_eCurrStep )
	{
	case STEP_MAIN:
		g_pRenderText->RenderText( ptOrigin.x, ptOrigin.y, GlobalText[180], 120, 0, RT3_SORT_CENTER);
		RenderGuildMasterMain();
		break;
	case STEP_CREATE_GUILDINFO:
		g_pRenderText->RenderText( ptOrigin.x, ptOrigin.y, GlobalText[1303], 120, 0, RT3_SORT_CENTER);
		RenderCreateGuild();
		break;
	case STEP_EDIT_GUILD_MARK:
		g_pRenderText->RenderText( ptOrigin.x, ptOrigin.y, GlobalText[1304], 120, 0, RT3_SORT_CENTER);
		RenderEditGuildMark();
		break;
	case STEP_CONFIRM_GUILDINFO:
		g_pRenderText->RenderText( ptOrigin.x, ptOrigin.y, GlobalText[228], 120, 0, RT3_SORT_CENTER);
		RenderCreateInfo();
		break;
	default:
		g_pRenderText->RenderText( ptOrigin.x, ptOrigin.y, GlobalText[180], 120, 0, RT3_SORT_CENTER);
		break;
	};
}

void CUIGuildMaster::Open()
{
	if( m_bOpened )	return;

	m_bOpened = TRUE;
}

bool CUIGuildMaster::IsOpen()
{
	return m_bOpened;
}

void CUIGuildMaster::Close()
{
	if( !m_bOpened )	return;

	m_bOpened = FALSE;

	if( Hero->GuildMarkIndex == MARK_EDIT )
		Hero->GuildMarkIndex = -1;
	PlayBuffer( SOUND_INTERFACE01 );
	m_nCurrMode = MODE_NONE;
	m_eCurrStep = STEP_MAIN;
	GuildInputEnable = FALSE;
	CloseMyPopup();

	SendRequestGuildMaster(false);

	if( g_pSingleTextInputBox )
	{
		g_pSingleTextInputBox->SetText( NULL );
		SaveIMEStatus();
		g_pSingleTextInputBox->SetState( UISTATE_HIDE );	// 길드 입력창 숨김
	}
}
