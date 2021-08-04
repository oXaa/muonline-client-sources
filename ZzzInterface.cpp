///////////////////////////////////////////////////////////////////////////////
// �������̽� ���� �Լ�
// �ɸ��� ����, �ؽ�Ʈ ������, ä�� ������, ȭ�� �ϴ��� �������̽� ������ ���
//
// *** �Լ� ����: 3
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <imm.h>
#include "UIManager.h"
#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "ZzzLodTerrain.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzTexture.h"
#include "ZzzAI.h"
#include "ZzzInterface.h"
#include "ZzzInventory.h"
#include "ZzzOpenData.h"
#include "ZzzEffect.h"
#include "ZzzScene.h"
#include "ZzzPath.h"
#include "DSPlaySound.h"
#include "DIMouse.h"
#include "wsclientinline.h"
#include "./Utilities/Log/ErrorReport.h"
#include "MatchEvent.h"
#include "CSQuest.h"
#include "PersonalShopTitleImp.h"
#include "zzzopenglUtil.h"
#include "CSItemOption.h"
#include "npcBreeder.h"
#include "PvPSystem.h"
#ifdef PET_SYSTEM
#include "GIPetManager.h"
#endif// PET_SYSTEM
#include "CSParts.h"
#include "GMBattleCastle.h"
#include "CSMapInterface.h"
#include "GMCrywolf1st.h"
#include "UIMapName.h"	// rozy
#include "GMCrywolf1st.h"
#include "CDirection.h"
#include "GM_Kanturu_3rd.h"
#include "GM_Kanturu_2nd.h"
#ifdef ADD_MU_HOMEPAGE
#include "iexplorer.h"
#endif //ADD_MU_HOMEPAGE
#include "Event.h"
#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
#include "PCRoomPoint.h"
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
#ifdef CSK_LH_DEBUG_CONSOLE
#include "./Utilities/Log/muConsoleDebug.h"
#endif // CSK_LH_DEBUG_CONSOLE
#include "NewUISystem.h"
#include "w_CursedTemple.h"
#include "UIControls.h"
#include "GM3rdChangeUp.h"
#include "PartyManager.h"
#include "NewUICommonMessageBox.h"
#include "SummonSystem.h"
#include "GMSwampOfQuiet.h"
#ifdef PSW_ADD_MAPSYSTEM
#include "w_MapHeaders.h"
#endif // PSW_ADD_MAPSYSTEM
#ifdef DO_PROFILING
#include "Profiler.h"
#endif // DO_PROFILING
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
#include "DuelMgr.h"
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
#ifdef CSK_MOD_PROTECT_AUTO_V1
#include "ProtectAuto.h"
#endif // CSK_MOD_PROTECT_AUTO_V1
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
#include "PKSystem.h"
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#ifdef LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG
#include "ChangeRingManager.h"
#endif // LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG
#ifdef PBG_ADD_GENSRANKING
#include "NewUIGensRanking.h"
#endif //PBG_ADD_GENSRANKING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#include "MonkSystem.h"
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#ifdef LDK_ADD_SCALEFORM
#include "CGFxProcess.h"
#endif //LDK_ADD_SCALEFORM
//////////////////////////////////////////////////////////////////////////
//  EXTERN.
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////
extern CUITextInputBox * g_pSingleTextInputBox;
extern CUITextInputBox * g_pSinglePasswdInputBox;
extern int g_iChatInputType;
extern BOOL g_bUseChatListBox;
extern DWORD g_dwMouseUseUIID;
extern CUIMapName* g_pUIMapName;	// rozy
extern bool bCheckNPC;
#ifdef WINDOWMODE
extern BOOL g_bUseWindowMode;
#endif //WINDOWMODE
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
extern void SetPlayerBow(CHARACTER *c);
#endif //#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT

bool m_pc_wanted = false;

#ifdef _PVP_ADD_MOVE_SCROLL
extern CMurdererMove g_MurdererMove;
#endif	// _PVP_ADD_MOVE_SCROLL

extern float g_fScreenRate_x;	// ��
extern float g_fScreenRate_y;

extern char *g_lpszMp3[NUM_MUSIC];

extern vec3_t MousePosition, MouseTarget;

extern DWORD g_dwCharSet[NUM_LANGUAGE];//�����Ƶ����

extern void RegisterBuff( eBuffState buff, OBJECT* o, const int bufftime = 0 );
extern void UnRegisterBuff( eBuffState buff, OBJECT* o );

extern BYTE m_CrywolfState;

//////////////////////////////////////////////////////////////////////////
//  Global Variable
//////////////////////////////////////////////////////////////////////////
MovementSkill g_MovementSkill;
//                                   �ð�   ��   ��
const   float   AutoMouseLimitTime = (1.f * 60.f*60.f); //  AutoMouse ���� �ð� ( 2�ð� )
int   LoadingWorld       = 0;
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
BOOL g_bReponsedMoveMapFromServer	= TRUE;
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
int   ItemHelp           = 0;
int   MouseUpdateTime    = 0;
int   MouseUpdateTimeMax = 6;
bool  WhisperEnable      = true;
bool  ChatWindowEnable   = true;
int   InputFrame         = 0;
int   EditFlag           = EDIT_NONE;
char  ColorTable[][10]   = {"White","Black","Red","Yellow","Green","Cyan","Blue","Magenta"};

//  ����.
int   SelectMonster      = 0;
int   SelectModel        = 0;
int   SelectMapping		 = 0;
int   SelectColor		 = 0;
int   SelectWall         = 0;
float SelectMappingAngle = 0.f;
bool  DebugEnable        = true;
int   SelectedItem       = -1;      //  ������ ����.
int   SelectedNpc        = -1;      //  Npc ����.
int   SelectedCharacter  = -1;      //  ĳ���� ����.
int   SelectedOperate    = -1;      //  
int   Attacking          = -1;      //  �ڵ� ����.

//  �ڵ� ���󰡱�.
int   g_iFollowCharacter = -1;      //  ���� ��� ĳ���� �ε���.

bool g_bAutoGetItem = false;        //  ������ space�� �ڵ� �Ա�.

//  AutoMouse ����.
float LButtonPopTime     = 0.f;     //  ���� ��ư�� ������ �� �ð�.
float LButtonPressTime   = 0.f;     //  ���� ��ư�� ������ �ִ� �ð�.
float RButtonPopTime     = 0.f;     //  ������ ��ư�� ������ �� �ð�.
float RButtonPressTime   = 0.f;     //  ������ ��ư�� ������ �ִ� �ð�.

//  
int   BrushSize          = 0;
int   HeroTile;
int   TargetNpc = -1;
int   TargetType;
int TargetX;
int TargetY;
float TargetAngle;
int   FontHeight;

OBJECT *TradeNpc = NULL;

bool  DontMove       = false;
bool  ServerHide     = true;
bool  SkillEnable;
bool  MouseOnWindow;
int   KeyState[256];

int    TerrainWallType[TERRAIN_SIZE*TERRAIN_SIZE];
float  TerrainWallAngle[TERRAIN_SIZE*TERRAIN_SIZE];
OBJECT *PickObject     = NULL;
vec3_t PickObjectAngle;
float  PickObjectHeight;
bool   PickObjectLockHeight = false;
bool   EnableRandomObject = false;
float  WallAngle;

bool LockInputStatus = false;

bool GuildInputEnable = false;
bool TabInputEnable  = false;
bool GoldInputEnable = false;
bool InputEnable     = true;
#ifdef SCRATCH_TICKET
bool g_bScratchTicket = false;
#endif

int  InputGold       = 0;
int  InputNumber     = 2;
int  InputTextWidth  = 110;
int  InputIndex      = 0;
int  InputResidentNumber = 6;
int  InputTextMax[12] = {MAX_ID_SIZE,MAX_ID_SIZE,MAX_ID_SIZE,30,30,10,14,20,40};
char InputText[12][256];
char InputTextIME[12][4];
char InputTextHide[12];
int  InputLength[12];
char MacroText[10][256];
int  MacroTime = 0;
int  WhisperIDCurrent = 2;
char WhisperID[MAX_WHISPER_ID][256];
DWORD g_dwOneToOneTick = 0;

#ifdef CSK_ADD_GM_ABILITY
bool g_bGMObservation = false;
#endif // CSK_ADD_GM_ABILITY

#ifdef LEM_FIX_USER_LOGOUT
bool g_bExit = false;
#endif // LEM_FIX_USER_LOGOUT [lem_2010.8.18]

#ifdef PK_ATTACK_TESTSERVER_LOG
void PrintPKLog(CHARACTER* pCha)
{
	static DWORD dwStartTime=0;
	static SHORT sKey=0;
	
	if(pCha->Key == sKey && (timeGetTime() - dwStartTime < 1000))
	{
		return;
	}
	
	if(pCha)
	{
		if(pCha->PK >= PVP_MURDERER2 && pCha->Object.Type == KIND_PLAYER)
		{
			g_ErrorReport.Write("!!!!!!!!!!!!!!!!! PK !!!!!!!!!!!!!!!\n");
			g_ErrorReport.WriteCurrentTime();
			g_ErrorReport.Write(" ID(%s) PK(%d) GuildName(%s)\n", pCha->ID, pCha->PK, GuildMark[pCha->GuildMarkIndex].GuildName);
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_ERROR, "[!!! PK !!! : ID(%s) PK(%d) GuildName(%s)\n]", pCha->ID, pCha->PK, GuildMark[pCha->GuildMarkIndex].GuildName);		
#endif // CONSOLE_DEBUG
			
			sKey = pCha->Key;
			dwStartTime = timeGetTime();
		}
	}
}
#endif // PK_ATTACK_TESTSERVER_LOG

///////////////////////////////////////////////////////////////////////////////
// ���� ������
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Ű���� �Է� �޴� �Լ�
///////////////////////////////////////////////////////////////////////////////

bool PressKey(int Key)
{
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
	if(SEASON3B::IsPress(Key) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
   	if(HIBYTE(GetAsyncKeyState(Key))==128)
#endif
	{
		if(KeyState[Key]==false)
		{
			KeyState[Key] = true;
			return true;
		}
	}
	else KeyState[Key] = false;
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// �Է�â �ʱ�ȭ
///////////////////////////////////////////////////////////////////////////////

void ClearInput(BOOL bClearWhisperTarget)
{
	InputIndex = 0;
	InputResidentNumber = -1;
    for(int i=0;i<10;i++)
	{
		if (i == 1 && bClearWhisperTarget == FALSE) continue;
		for(int j=0;j<256;j++)
			InputText[i][j] = NULL;
		InputLength[i] = 0;
		InputTextHide[i] = 0;
	}
	
	if (g_iChatInputType == 1)
	{
		g_pSingleTextInputBox->SetText(NULL);
		g_pSinglePasswdInputBox->SetText(NULL);
	}
}
///////////////////////////////////////////////////////////////////////////////
// IME Input â ��ġ ���� �Լ�.	// IME ����                                                                                                        
///////////////////////////////////////////////////////////////////////////////
void SetPositionIME_Wnd( float x, float y )
{
    float xRatio_Input = x/640.f;
    float yRatio_Input = y/480.f;
	
    //  IME ����â�� ��ġ ����.
	COMPOSITIONFORM comForm;
    comForm.dwStyle = CFS_POINT;
    comForm.ptCurrentPos.x = (long)(WindowWidth*xRatio_Input);
    comForm.ptCurrentPos.y = (long)(WindowHeight*yRatio_Input);
    SetRect ( &comForm.rcArea, 0, 0, WindowWidth, WindowHeight );
	
    HWND hWnd = ImmGetDefaultIMEWnd(g_hWnd);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	::SendMessage(hWnd, WM_IME_CONTROL, IMC_SETCOMPOSITIONWINDOW, (LPARAM)&comForm);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    int ret = ::SendMessage(hWnd, WM_IME_CONTROL, IMC_SETCOMPOSITIONWINDOW, (LPARAM)&comForm);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}

///////////////////////////////////////////////////////////////////////////////
// IME Input ���� ����.
///////////////////////////////////////////////////////////////////////////////
DWORD   g_dwOldConv = IME_CMODE_ALPHANUMERIC;
DWORD   g_dwOldSent = IME_SMODE_AUTOMATIC;
DWORD   g_dwCurrConv= 0;

// ���� IME �Է� ���¸� �����Ѵ�.
void SaveIME_Status ()
{
    HIMC  data;
	
    data = ::ImmGetContext( g_hWnd );
	
    ::ImmGetConversionStatus( data, &g_dwOldConv, &g_dwOldSent );
    ::ImmReleaseContext( g_hWnd, data );
}

//  
void SetIME_Status (bool halfShape)
{
	if (g_iChatInputType == 1) return;
	
    HIMC  data;
    DWORD dwConv, dwSent;
	
    data = ::ImmGetContext( g_hWnd );
	
    //  �ݰ�.
    dwConv = g_dwOldConv;
    dwSent = g_dwOldSent;
    if( halfShape )
    {
        dwConv = IME_CMODE_ALPHANUMERIC;
        dwSent = IME_SMODE_NONE;
    }
    ::ImmSetConversionStatus( data, dwConv, dwSent );
    ::ImmReleaseContext( g_hWnd, data );
}

//  ���� IME ���¸� äũ�Ѵ�.
bool CheckIME_Status (bool change, int mode)
{
	if (g_iChatInputType == 1) return false;
	
    HIMC  data;
    DWORD dwConv, dwSent;
    bool  bIme = false;
	
    data = ::ImmGetContext( g_hWnd );
	
    ::ImmGetConversionStatus( data, &dwConv, &dwSent );
	
    if( dwConv!=IME_CMODE_ALPHANUMERIC || dwSent!=IME_SMODE_NONE )
    {
        bIme = true;
		
        //  ������ ����.
        if( (mode&IME_CONVERSIONMODE)==IME_CONVERSIONMODE )
        {
            g_dwOldConv = dwConv;
        }
        if( (mode&IME_SENTENCEMODE)==IME_SENTENCEMODE )
        {
            g_dwOldSent = dwSent;
        }
		
        if( change )
        {
            dwConv = IME_CMODE_ALPHANUMERIC;
            dwSent = IME_SMODE_NONE;
            ::ImmSetConversionStatus( data, dwConv, dwSent );
        }
    }
    ::ImmReleaseContext( g_hWnd, data );
	
    //  ���� IME �Է� ���.
    g_dwCurrConv = dwConv;
	
    return   bIme;
}

//  ���� IME ���¸� ȭ�鿡 ��Ÿ����.
void RenderIME_Status ()
{
    char    Text[100];
    if( (g_dwOldConv&IME_CMODE_NATIVE)==IME_CMODE_NATIVE )
    {
#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
        sprintf ( Text, "ENGLISH" );
#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
        sprintf ( Text, "TAIWANESE" );
#endif // SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
        sprintf ( Text, "CHINESE" );
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
        sprintf ( Text, "JAPANESE" );
#endif // SELECTED_LANGUAGE == LANGUAGE_JAPANESE
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
        sprintf ( Text, "KOREAN" );
#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN
#if SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
        sprintf ( Text, "VIETNAMESE" );	//! IME ����
#endif // SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
    }
    else
    {
        sprintf ( Text, "ENGLISH" );
    }
	
	g_pRenderText->SetTextColor(255, 230, 210, 255);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->RenderText(100, 100, Text);
	
    HIMC  data;
    DWORD dwConv, dwSent;
	
    data = ::ImmGetContext( g_hWnd );
	
    ::ImmGetConversionStatus( data, &dwConv, &dwSent );
    ::ImmReleaseContext( g_hWnd, data );
	
	sprintf ( Text, "Sentence Mode = %d", dwSent );
    g_pRenderText->RenderText(100, 110, Text);
	
    sprintf ( Text, "Old Sentence Mode = %d", g_dwOldSent );
    g_pRenderText->RenderText(100, 120, Text );
	
    sprintf ( Text, "LockInputStatus=%d", LockInputStatus );
    g_pRenderText->RenderText(100, 130, Text );
}


///////////////////////////////////////////////////////////////////////////////
// �Է�â ������
///////////////////////////////////////////////////////////////////////////////

void RenderInputText(int x,int y,int Index,int Gold)
{
	if (g_iChatInputType == 1) 
	{
		return;
	}
	else if (g_iChatInputType == 0)
	{
		g_pRenderText->SetTextColor(255, 230, 210, 255);
		g_pRenderText->SetBgColor(0);
		
		SIZE *Size;
		char Text[256];
		if(InputTextHide[Index]==1)
		{
#ifdef _VS2008PORTING
			int iTextSize = 0;
			for(unsigned int i=0;i<strlen(InputText[Index]);i++)
			{
				Text[i] = '*';
				iTextSize = i;
			}
			Text[iTextSize] = NULL;
#else // _VS2008PORTING
			for(unsigned int i=0;i<strlen(InputText[Index]);i++)
				Text[i] = '*';
			Text[i] = NULL;
#endif // _VS2008PORTING
		}
		else if(InputTextHide[Index]==2)
		{
#ifdef _VS2008PORTING
			int iTextSize = 0;
			for(unsigned int i=0;i<7;i++)
			{
				Text[i] = InputText[Index][i];
				iTextSize = i;
			}
			for(unsigned int i=7;i<strlen(InputText[Index]);i++)
			{
				Text[i] = '*';
				iTextSize = i;
			}
			Text[iTextSize] = NULL;
#else // _VS2008PORTING
			for(unsigned int i=0;i<7;i++)
				Text[i] = InputText[Index][i];
			for(i=7;i<strlen(InputText[Index]);i++)
				Text[i] = '*';
			Text[i] = NULL;
#endif // _VS2008PORTING
		}
		else
		{
			strcpy(Text,InputText[Index]);
		}
		SIZE TextSize;
		g_pRenderText->RenderText(x,y,Text,InputTextWidth, 0, RT3_SORT_LEFT, &TextSize);
		Size = &TextSize;
		
		// IME ����
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
		if(Index==InputIndex)
			SetPositionIME_Wnd( x+Size->cx, y );
#endif
		if(Index==InputIndex && (InputFrame++)%2==0)
		{
			EnableAlphaTest();
			if(strlen(InputTextIME[Index]) > 0)
			{
				if(InputTextHide[Index]==1)
					g_pRenderText->RenderText(x+Size->cx,y,"**");
				else
					g_pRenderText->RenderText(x+Size->cx,y,InputTextIME[Index]);
			}
			else
				g_pRenderText->RenderText(x+Size->cx,y,"_");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ �ؽ�Ʈ�� �ؽ�Ʈ �ؽ��Ŀ� �׸��� �Լ�
///////////////////////////////////////////////////////////////////////////////
extern int  AlphaBlendType;	// OpenGLUtil.cpp ���� ���� ���� Ÿ��

void RenderTipText(int sx, int sy, const char* Text)
{
	SIZE TextSize = {0, 0};
	g_pRenderText->SetFont(g_hFont);
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), Text, lstrlen(Text), &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), Text, lstrlen(Text), &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	
	int BackupAlphaBlendType = AlphaBlendType;
	EnableAlphaTest();
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	RenderColor ((float)sx - 2, (float)sy - 3, (float)TextSize.cx / g_fScreenRate_x + 4, (float)1);	// ��
	RenderColor ((float)sx - 2, (float)sy - 3, (float)1, (float)TextSize.cy / g_fScreenRate_y + 4);	// ��
	RenderColor ((float)sx - 2 + TextSize.cx / g_fScreenRate_x + 3, (float)sy - 3, (float)1, (float)TextSize.cy / g_fScreenRate_y + 4);	
	RenderColor ((float)sx - 2, (float)sy - 3 + TextSize.cy / g_fScreenRate_y + 3, (float)TextSize.cx / g_fScreenRate_x + 4, (float)1);
	
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	RenderColor ((float)sx - 1, (float)sy - 2, (float)TextSize.cx / g_fScreenRate_x + 2, (float)TextSize.cy / g_fScreenRate_y + 2);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->RenderText(sx, sy, Text);
	switch(BackupAlphaBlendType)
	{
	case 0:
		DisableAlphaBlend();
		break;
	case 1:
		EnableLightMap();
		break;
	case 2:
		EnableAlphaTest();
		break;
	case 3:
		EnableAlphaBlend();
		break;
	case 4:
		EnableAlphaBlendMinus();
		break;
	case 5:
		EnableAlphaBlend2();
		break;
	default:
		DisableAlphaBlend();
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���ӳ��� ���� ���� ó���ϴ� �Լ���
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
	char      Text[256];
	int       LifeTime;
	BYTE      Color;
} NOTICE;

#define MAX_NOTICE 6

int    NoticeCount = 0;
int    NoticeTime = 300;
NOTICE Notice[MAX_NOTICE];

void ScrollNotice()
{
	if(NoticeCount > MAX_NOTICE-1)
	{
		NoticeCount = MAX_NOTICE-1;
		for(int i=1;i<MAX_NOTICE;i++)
		{
			Notice[i-1].Color = Notice[i].Color;
			strcpy(Notice[i-1].Text,Notice[i].Text);
		}
	}
}

void ClearNotice ( void )
{
    //  ����.
    memset ( Notice, 0, sizeof( NOTICE )*MAX_NOTICE );
}

void CreateNotice(char *Text,int Color)
{
	SIZE Size;
	g_pRenderText->SetFont(g_hFontBold);
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), Text,lstrlen(Text),&Size);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), Text,lstrlen(Text),&Size);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	
	ScrollNotice();
	Notice[NoticeCount].Color = Color;
	if(Size.cx < 256)
	{
		strcpy(Notice[NoticeCount++].Text,Text);
	}
	else
	{
		char Temp1[256];
		char Temp2[256];
		CutText(Text,Temp1,Temp2,strlen(Text));
		strcpy(Notice[NoticeCount++].Text,Temp2);
		ScrollNotice();
        Notice[NoticeCount].Color = Color;
		strcpy(Notice[NoticeCount++].Text,Temp1);
	}
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	NoticeTime = 150;
#else
	NoticeTime = 300;
#endif
}

void MoveNotices()
{
	if(NoticeTime-- <= 0)
	{
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
		NoticeTime = 150;
#else
		NoticeTime = 300;
#endif
		CreateNotice("",0);
	}
}

int NoticeInverse = 0;

void RenderNotices()
{
// #ifdef LDS_ADD_EMPIRE_GUARDIAN
// 	// ���� ��ȣ�� �����߿� ���� ��¾���
// 	if(	IsEmpireGuardian1() || IsEmpireGuardian2() || IsEmpireGuardian3() || IsEmpireGuardian4() )
// 	{
// 		return;
// 	}
// #endif //LDS_ADD_EMPIRE_GUARDIAN

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == true)
		return;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

	EnableAlphaTest();
	
#ifdef SYSTEM_NOT_RENDER_TEXT
	return;
#endif // SYSTEM_NOT_RENDER_TEXT
	
	g_pRenderText->SetFont(g_hFontBold);
	
	glColor3f(1.f,1.f,1.f);
	for(int i=0;i<MAX_NOTICE;i++)
	{
		NOTICE *n = &Notice[i];
		if(n->Color==0)
		{
			g_pRenderText->SetBgColor(0, 0, 0, 128);
			if(NoticeInverse%10 < 5)
			{
				g_pRenderText->SetTextColor(255, 200, 80, 128);
			}
			else
			{
				g_pRenderText->SetTextColor(255, 200, 80, 255);
			}
		}
		else
		{
			g_pRenderText->SetTextColor(100, 255, 200, 255);
			g_pRenderText->SetBgColor(0, 0, 0, 128);
		}	
		
		if (g_bUseChatListBox == TRUE)
		{
			g_pRenderText->RenderText(320, 300+i*13, n->Text, 0, 0, RT3_WRITE_CENTER);
		}
		else
		{
			g_pRenderText->RenderText(320, 300+i*13, n->Text, 0, 0, RT3_WRITE_CENTER);
		}
	}
	NoticeInverse++;
}

///////////////////////////////////////////////////////////////////////////////
// �ؽ�Ʈ ��½� ������ �� ��� ���ٷ� �ڸ��� �Լ�
///////////////////////////////////////////////////////////////////////////////


void CutText(const char* Text,char *Text1,char *Text2,int Length)
{

// Text�� UTF-8 Ÿ���� �ƴ� ��� ������ ��Ĵ�� CutText
#ifdef	LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	if (g_pMultiLanguage->IsCharUTF8(Text))
	{
		// ���� Text�� �׳� ������ ���� ��� UTF-8 encoding�� ����� �ڸ��� �����Ƿ� 
		// UTF-16���� ��ȯ��Ų �� ������ ������. 
		wstring wstrText = L"";
		g_pMultiLanguage->ConvertCharToWideStr(wstrText, Text);
		int iClosestBlankFromCenter = g_pMultiLanguage->GetClosestBlankFromCenter(wstrText);

		// ������ ������ ������(������ �Ǵ� ��ĭ�� ���ٿ� ���Խ�Ų��).
		wstring wstrText1, wstrText2;
		wstrText1 = wstrText.substr(iClosestBlankFromCenter+1, string::npos);
		wstrText2 = wstrText.substr(0, iClosestBlankFromCenter+1);

		// �������� UTF-8 ������ Text��
		string strText1, strText2;
		g_pMultiLanguage->ConvertWideCharToStr(strText1, wstrText1.c_str(), CP_UTF8);
		g_pMultiLanguage->ConvertWideCharToStr(strText2, wstrText2.c_str(), CP_UTF8);
		
		// Text1, Text2�� ����
		strncpy(Text1, strText1.c_str(), strText1.length()+1);
		strncpy(Text2, strText2.c_str(), strText2.length()+1);
		
		return ;
	}
#endif	//LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	// �ڸ� ���� ����
	/*	int Cut = 0;
	bool Hangul = false;
	for(int j=0;j<Length;j++)
	{
	if((j>=Length/2-2 && Text[j]==' ') || j>=Length/2+2)
	{
	Cut = j;
	break;
	}
	if(Hangul)
	{
	Hangul = false;
	}
	else
	{
	if((unsigned char)Text[j] >= 128)
				Hangul = true;
				}
				}
				if(Hangul && (unsigned char)Text[Cut] >= 128)
	Cut++;*/
	
	// �ڸ� ���� ����
	int Cut = 0;
	//int Space = -10;
	for(int j=0;j<Length;)
	{
	/*if ( Text[j]==' ')
	{
	Space = j;
	}*/
		if((j>=Length/2-2 && Text[j]==' ') || j>=Length/2+2)
		{
			Cut = j;
			/*if ( Cut - Space < 4)
			{
			Cut = Space;
		}*/
			break;
		}
		
		j += _mbclen( ( unsigned char*)&( Text[j]));	// �ѱ��̸� 2, �ƴϸ� 1 �� ����
	}

// �߶� ����
#ifdef _VS2008PORTING
	int iTextSize = 0;
	for(int j=0;j<Cut;j++)
	{
		Text2[j] = Text[j];
		iTextSize = j;
	}
	Text2[iTextSize+1] = NULL;
	for(int j=Cut;j<Length;j++)
	{
		Text1[j-Cut] = Text[j];
		iTextSize = j;
	}
	Text1[iTextSize-Cut+1] = NULL;
#else // _VS2008PORTING
	for(j=0;j<Cut;j++)
		Text2[j] = Text[j];
	Text2[j] = NULL;
	for(j=Cut;j<Length;j++)
		Text1[j-Cut] = Text[j];
	Text1[j-Cut] = NULL;
#endif // _VS2008PORTING

}

///////////////////////////////////////////////////////////////////////////////
// �ӼӸ� ó���ϴ� �Լ���
///////////////////////////////////////////////////////////////////////////////

int     WhisperID_Num = 0;
char    WhisperRegistID[MAX_ID_SIZE+1][10];
//  �ӼӸ� üũ.
bool CheckWhisperLevel ( int lvl, char* text )
{
	int level = CharacterAttribute->Level;
	
    if( level>=lvl )
        return  true;
	
    //  
    for( int i=0; i<10; ++i )
    {
        if( strcmp( text, WhisperRegistID[i] )==0 )
        {
            return  true;
        }
    }
	
	//  6���� �̻� ĳ���ͺ��� �ӼӸ��� ���� ������ �ֽ��ϴ�.
	g_pChatListBox->AddText("", GlobalText[479], SEASON3B::TYPE_SYSTEM_MESSAGE);
	
    return  false;
}

//  �ӼӸ� ���̵� ���.
void RegistWhisperID ( int lvl, char* text )
{
	int level = CharacterAttribute->Level;
	
    if( level<lvl )
    {
        bool noMatch = true;
        for( int i=0; i<10; ++i )
        {
            if( strcmp( text, WhisperRegistID[i] )==0 )
            {
                noMatch = false;
                break;
            }
        }
		
        if( noMatch )
        {
            strcpy( WhisperRegistID[WhisperID_Num], text );
            WhisperID_Num++;
			
            if( WhisperID_Num>=10 )
            {
                WhisperID_Num = 0;
            }
        }
    }
}

void ClearWhisperID ( void )
{
    ZeroMemory ( WhisperRegistID, sizeof( char )*(MAX_ID_SIZE+1)*10 );
}

void RenderWhisperID_List ( void )
{
    for( int i=0; i<10; ++i )
    {
		g_pRenderText->SetTextColor(255, 255, 255 ,255);
		g_pRenderText->SetBgColor(0, 0, 0, 255);
		g_pRenderText->RenderText(100,100+(i*10),WhisperRegistID[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
// ä�� ó���ϴ� �Լ���
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char      ID[32];
#else // SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char      ID[24];
#endif // SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char      Union[30];		// ���ո� + ��������
	char      Guild[30];		// ���� + �������
	char      szShopTitle[16];
	char      Color;
	char      GuildColor;
	int       IDLifeTime;
	char      Text[2][256];
	int       LifeTime[2];
	CHARACTER *Owner;
	int       x,y;
	int       Width;
	int       Height;
    vec3_t    Position;
} CHAT;

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
#define MAX_CHAT 120
#else // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
#define MAX_CHAT 100
#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE

CHAT Chat[MAX_CHAT];

///////////////////////////////////////////////////////////////////////////////
// ��ǳ������ ĭ ���ߴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void SetBooleanPosition(CHAT *c)
{
	BOOL bResult[5];
	SIZE Size[5];
	memset(&Size[0], 0, sizeof(SIZE)*5);
	
	if ( g_isCharacterBuff((&c->Owner->Object), eBuff_GMEffect) || // GM �ϰ��
			(c->Owner->CtlCode == CTLCODE_20OPERATOR) || (c->Owner->CtlCode == CTLCODE_08OPERATOR))	
		{
			g_pRenderText->SetFont(g_hFontBold);
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			bResult[0] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->ID, lstrlen(c->ID), &Size[0]);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE 
			bResult[0] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->ID, lstrlen(c->ID), &Size[0]);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			g_pRenderText->SetFont(g_hFont);
		}
		else
		{
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			bResult[0] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->ID, lstrlen(c->ID), &Size[0]);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE 
			bResult[0] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->ID, lstrlen(c->ID), &Size[0]);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		}

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		bResult[1] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Text[0],lstrlen(c->Text[0]),&Size[1]);
		bResult[2] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Text[1],lstrlen(c->Text[1]),&Size[2]);
		bResult[3] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Union  ,lstrlen(c->Union  ),&Size[3]);
		bResult[4] = g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Guild  ,lstrlen(c->Guild  ),&Size[4]);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE 
		bResult[1] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Text[0],lstrlen(c->Text[0]),&Size[1]);
		bResult[2] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Text[1],lstrlen(c->Text[1]),&Size[2]);
		bResult[3] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Union  ,lstrlen(c->Union  ),&Size[3]);
		bResult[4] = unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->Guild  ,lstrlen(c->Guild  ),&Size[4]);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

		Size[0].cx += 3;
		// ä���� 2���̶��
		if(c->LifeTime[1] > 0)
			c->Width = max( max( max(Size[0].cx,Size[1].cx), max(Size[2].cx,Size[3].cx) ), Size[4].cx );
		// ä���� 1���̶��
		else if(c->LifeTime[0] > 0)
			c->Width = max( max(Size[0].cx,Size[1].cx), max(Size[3].cx,Size[4].cx) );
		else
			c->Width = max( max( Size[0].cx, Size[3].cx ), Size[4].cx );
		c->Height = FontHeight*(bResult[0]+bResult[1]+bResult[2]+bResult[3]+bResult[4]);
		
		if(lstrlen(c->szShopTitle) > 0) 
		{
			SIZE sizeT[2];
			g_pRenderText->SetFont(g_hFontBold);
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			if(g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->szShopTitle, lstrlen(c->szShopTitle), &sizeT[0]) 
				&& g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), GlobalText[1104], lstrlen(GlobalText[1104]), &sizeT[1]))
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE 
			if(unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), c->szShopTitle, lstrlen(c->szShopTitle), &sizeT[0]) 
				&& unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), GlobalText[1104], lstrlen(GlobalText[1104]), &sizeT[1]))
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			{
				if(c->Width < sizeT[0].cx+sizeT[1].cx)
					c->Width = sizeT[0].cx+sizeT[1].cx;
				c->Height += max(sizeT[0].cy, sizeT[1].cy);
			}
			g_pRenderText->SetFont(g_hFont);
		}
		c->Width /= g_fScreenRate_x;		//. 640*480 �������� ��ȯ
		c->Height /= g_fScreenRate_y;
}

///////////////////////////////////////////////////////////////////////////////
// ��ǳ�� �ϳ��� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void SetPlayerColor(BYTE PK)
{
	switch(PK)
	{
	case 0:g_pRenderText->SetTextColor(150, 255, 240, 255);break;//npc
	case 1:g_pRenderText->SetTextColor(100, 120, 255, 255);break;
	case 2:g_pRenderText->SetTextColor(140, 180, 255, 255);break;
	case 3:g_pRenderText->SetTextColor(200, 220, 255, 255);break;//normal
	case 4:g_pRenderText->SetTextColor(255, 150, 60, 255);break; //pk1
	case 5:g_pRenderText->SetTextColor(255, 80, 30, 255);break;  //pk2
	default:g_pRenderText->SetTextColor(255, 0, 0, 255);break;    //pk3
	}
}

extern float g_fScreenRate_x;	// ��
extern float g_fScreenRate_y;
const int ciSystemColor = 240;

void RenderBoolean(int x,int y,CHAT *c)
{
	//  ũ���̿��� MVP �϶� NPC �Ⱥ��̰�
	
	if ( g_isCharacterBuff((&c->Owner->Object), eBuff_CrywolfNPCHide ) )
	{
		return;
	}
	
	if ( c->Owner!=Hero && battleCastle::IsBattleCastleStart()==true && g_isCharacterBuff((&c->Owner->Object), eBuff_Cloaking) )	
	{
		if ( ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK ))
		{
			if(!( c->Owner->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || c->Owner->EtcPart==PARTS_ATTACK_TEAM_MARK ))
			{
				return;
			}
		}
		else if ( ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK2 ))
		{
			if(!( c->Owner->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || c->Owner->EtcPart==PARTS_ATTACK_TEAM_MARK2 ))
			{
				return;
			}
		}
		else if ( ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3 || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK3 ))
		{
			if(!( c->Owner->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3 || c->Owner->EtcPart==PARTS_ATTACK_TEAM_MARK3 ))
			{
				return;
			}
		}
		else if ( ( Hero->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || Hero->EtcPart==PARTS_DEFENSE_TEAM_MARK ))
		{
			if(!( c->Owner->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || c->Owner->EtcPart==PARTS_DEFENSE_TEAM_MARK ))
			{
				return;
			}
		}
	}
	
	EnableAlphaTest();
	glColor3f(1.f,1.f,1.f);
	
	if (FontHeight > 32) FontHeight = 32;	// ���� ����
	
	// ������ ���ù��� ��� : x, y�� ���� �ػ� ����
	POINT RenderPos = { x, y };	//. 640*480 ����
	SIZE RenderBoxSize = { c->Width, c->Height }; //. 640*480 ����
	int iLineHeight = FontHeight/g_fScreenRate_y;

	if(IsShopInViewport(c->Owner))
	{
		SIZE TextSize;	//. 640*480 ���� �ؽ�Ʈ ������(GetTextExtentPoint�� Ʋ��)
		g_pRenderText->SetFont(g_hFontBold);
		g_pRenderText->SetBgColor(GetShopBGColor(c->Owner));
		
		// [����] �κ� ���� ����ϰ�
		g_pRenderText->SetTextColor(GetShopTextColor(c->Owner));
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, GlobalText[1104], 0, iLineHeight, RT3_SORT_LEFT, &TextSize);
		RenderPos.x += TextSize.cx;	//. ���������� �̵�
		
		// [����] �޺κп� �������� ����Ѵ�.
		g_pRenderText->SetTextColor(GetShopText2Color(c->Owner));
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->szShopTitle, RenderBoxSize.cx-TextSize.cx, iLineHeight, RT3_SORT_LEFT, &TextSize);
		g_pRenderText->SetFont(g_hFont);
		
		RenderPos.x = x;
		RenderPos.y += iLineHeight;	//. ���� ����
	}
#ifdef PBG_MOD_STRIFE_GENSMARKRENDER
#ifdef ASG_MOD_GM_VIEW_NAME_IN_GENS_STRIFE_MAP
	// ������������ Ÿ�����̸� �ڽ��� GMĳ���Ͱ� �ƴϸ�.
	else if(::IsStrifeMap(World) && Hero->m_byGensInfluence != c->Owner->m_byGensInfluence
		&& !::IsGMCharacter())
#else	// ASG_MOD_GM_VIEW_NAME_IN_GENS_STRIFE_MAP
	else if(::IsStrifeMap(World) && Hero->m_byGensInfluence != c->Owner->m_byGensInfluence)
#endif	// ASG_MOD_GM_VIEW_NAME_IN_GENS_STRIFE_MAP
	{
		// �⿩�� ����Ʈ 0 �̸� ���� ���� �ʴ´�
		if(!c->Owner->m_nContributionPoint)
			return;

		// �������������� ������ �ս� ��ũ�� �����Ѵ�
		if(KIND_PLAYER == c->Owner->Object.Kind && MODEL_PLAYER == c->Owner->Object.Type)
		{
			int _TempX = (int)(c->x + c->Width*0.5f+20.0f);
			switch(c->Owner->m_byGensInfluence)
			{
			case 1:
				g_pNewUIGensRanking->RanderMark(_TempX, y, c->Owner->m_byGensInfluence, c->Owner->m_byRankIndex, SEASON3B::CNewUIGensRanking::MARK_BOOLEAN, (float)RenderPos.y);
				return;
			case 2:
				g_pNewUIGensRanking->RanderMark(_TempX, y, c->Owner->m_byGensInfluence, c->Owner->m_byRankIndex, SEASON3B::CNewUIGensRanking::MARK_BOOLEAN, (float)RenderPos.y);
				return;
			default:
				break;
			}	
		}
	}
#endif //PBG_MOD_STRIFE_GENSMARKRENDER
	
	bool bGmMode = false;
	
	if (g_isCharacterBuff((&c->Owner->Object), eBuff_GMEffect) || (c->Owner->CtlCode == CTLCODE_20OPERATOR) || (c->Owner->CtlCode == CTLCODE_08OPERATOR))	
	{
		bGmMode = true;
		//. ���� ���� ����
		g_pRenderText->SetBgColor(30, 30, 30, 200);
		g_pRenderText->SetTextColor(200, 255, 255, 255);
	}
			
	// �� �ڽ�: ���� ���� ����
	if( c->Owner == Hero )
	{
		g_pRenderText->SetBgColor(60, 100, 0, 150);
		g_pRenderText->SetTextColor(200, 255, 0, 255);
	}
	// ���� ��� (���հ� ���� ��): ���� ���� ����
	else if( c->Owner->GuildMarkIndex == Hero->GuildMarkIndex )
	{
		g_pRenderText->SetBgColor(GetGuildRelationShipBGColor(GR_UNION));
		g_pRenderText->SetTextColor(GetGuildRelationShipTextColor(GR_UNION));
	}
	else	// ���� ���� ����
	{
		g_pRenderText->SetBgColor(GetGuildRelationShipBGColor(c->Owner->GuildRelationShip));
		g_pRenderText->SetTextColor(GetGuildRelationShipTextColor(c->Owner->GuildRelationShip));
	}
	
	// ���ո� ǥ��
	if( c->Union && c->Union[0] )
	{
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->Union, RenderBoxSize.cx, iLineHeight, RT3_SORT_LEFT);
		RenderPos.y += iLineHeight;
	}
	// ���� ǥ��
	if( c->Guild && c->Guild[0] )
	{
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->Guild, RenderBoxSize.cx, iLineHeight, RT3_SORT_LEFT);
		RenderPos.y += iLineHeight;
	}
	
	// �÷��̾� �̸� �� ����
	if (bGmMode)	
	{
		g_pRenderText->SetTextColor(100, 250, 250, 255);
	}
	else
	{
		SetPlayerColor(c->Color);
	}
	
	// ���콺�� ĳ���ͳ� ��ǳ���� �÷����� �����̰� �ϱ�(����)
	if ( c->x <= MouseX && MouseX < (int)(c->x+c->Width*640/WindowWidth) &&
		c->y <= MouseY && MouseY < (int)(c->y+c->Height*480/WindowHeight) &&
		InputEnable && Hero->SafeZone && strcmp(c->ID,Hero->ID)!=NULL &&
		(DWORD)WorldTime%24 < 12)
	{
		unsigned int Temp = g_pRenderText->GetBgColor();
		g_pRenderText->SetBgColor(g_pRenderText->GetTextColor());
		g_pRenderText->SetTextColor(Temp);
	}
	
	// ���̵� ǥ��
	if (bGmMode)	
	{
		g_pRenderText->SetFont(g_hFontBold);
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->ID, RenderBoxSize.cx, iLineHeight, RT3_SORT_LEFT);
		RenderPos.y += iLineHeight;
		g_pRenderText->SetFont(g_hFont);
	}
	else
	{
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->ID, RenderBoxSize.cx, iLineHeight, RT3_SORT_LEFT);
		RenderPos.y += iLineHeight;
	}
	
	// �������
	if(c->GuildColor==0)
		g_pRenderText->SetBgColor(10, 30, 50, 150);
	else if(c->GuildColor==1)
		g_pRenderText->SetBgColor(30, 50, 0, 150);
	else if(bGmMode)
		g_pRenderText->SetBgColor(30, 30, 30, 200);
	else
		g_pRenderText->SetBgColor(50, 0, 0, 150);
	
	DWORD dwTextColor[2];
	BYTE byAlpha[2] = { 255, 255 };
	if((c->LifeTime[0] > 0 && c->LifeTime[0] < 10))
		byAlpha[0] = 128;
	if((c->LifeTime[1] > 0 && c->LifeTime[1] < 10))
		byAlpha[1] = 128;
	
	if (bGmMode)	
	{
		dwTextColor[0] = RGBA(250, 200, 50, byAlpha[0]);
		dwTextColor[1] = RGBA(250, 200, 50, byAlpha[1]);
	}
	else
	{
		dwTextColor[0] = RGBA(230, 220, 200, byAlpha[0]);
		dwTextColor[1] = RGBA(230, 220, 200, byAlpha[1]);
	}
	
	// �ؽ�Ʈ�� �����̸�
	if(c->LifeTime[1] > 0)
	{
		// �ؽ�Ʈ ���� 1�� ���
		g_pRenderText->SetTextColor(dwTextColor[1]);
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->Text[1], RenderBoxSize.cx, iLineHeight, RT3_SORT_LEFT);
		RenderPos.y += iLineHeight;
		
		// �ؽ�Ʈ ���� 0�� ���
		g_pRenderText->SetTextColor(dwTextColor[0]);
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->Text[0], RenderBoxSize.cx, iLineHeight);
	}
	// �ؽ�Ʈ�� �����̸�
	else if(c->LifeTime[0] > 0)
	{
		// �ؽ�Ʈ ���� 0�� ���
		g_pRenderText->SetTextColor(dwTextColor[0]);
		g_pRenderText->RenderText(RenderPos.x, RenderPos.y, c->Text[0], RenderBoxSize.cx, iLineHeight);
	}

#ifdef ASG_ADD_GENS_MARK
	// �ս� ��ũ ǥ��.
	if (KIND_PLAYER == c->Owner->Object.Kind && MODEL_PLAYER == c->Owner->Object.Type)
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		const int nGensMarkHeight = 18;
		int nGensMarkPosY = (RenderPos.y - y - nGensMarkHeight) / 2 + y;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

#ifdef PBG_ADD_GENSRANKING
		if(c->LifeTime[1] > 0)
			RenderPos.y -= iLineHeight;
#endif //PBG_ADD_GENSRANKING

		if (1 == c->Owner->m_byGensInfluence)		// �ս� ���������ΰ�?
#ifdef PBG_ADD_GENSRANKING
			g_pNewUIGensRanking->RanderMark(x, y, c->Owner->m_byGensInfluence, c->Owner->m_byRankIndex, SEASON3B::CNewUIGensRanking::MARK_BOOLEAN, (float)RenderPos.y);
#else //PBG_ADD_GENSRANKING
			SEASON3B::RenderImage(BITMAP_GENS_MARK_DUPRIAN, x - nGensMarkWidth - 2, nGensMarkPosY,
				nGensMarkWidth, nGensMarkHeight);
#endif //PBG_ADD_GENSRANKING
		else if (2 == c->Owner->m_byGensInfluence)	// �ս� �ٳ׸�Ʈ�ΰ�?
#ifdef PBG_ADD_GENSRANKING
			g_pNewUIGensRanking->RanderMark(x, y, c->Owner->m_byGensInfluence, c->Owner->m_byRankIndex, SEASON3B::CNewUIGensRanking::MARK_BOOLEAN, (float)RenderPos.y);
#else //PBG_ADD_GENSRANKING
			SEASON3B::RenderImage(BITMAP_GENS_MARK_BARNERT, x - nGensMarkWidth - 2, nGensMarkPosY,
				nGensMarkWidth, nGensMarkHeight);
#endif //PBG_ADD_GENSRANKING
	}
#endif	// ASG_ADD_GENS_MARK
}
void AddChat(CHAT *c,const char* Text,int Flag)
{	
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Time = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Time;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Length = (int)strlen(Text);
	switch(Flag)
	{
	case 0:
		Time = Length*2+160;
		break;
	case 1:		// #�Ἥ �� �۵� ����Ʈ�� ����
		Time = 1000;
		g_pChatListBox->AddText(c->ID, Text, SEASON3B::TYPE_CHAT_MESSAGE);
		break;
	}
	
	if(Length >= 20)
	{
		CutText(Text,c->Text[0],c->Text[1],Length);
		c->LifeTime[0] = Time;
		c->LifeTime[1] = Time;
	}
	else
	{
		strcpy(c->Text[0],Text);
		c->LifeTime[0] = Time;
	}
}

void AddGuildName(CHAT *c,CHARACTER *Owner)
{
	if(IsShopInViewport(Owner))
	{
		std::string summary;
		GetShopTitleSummary(Owner, summary);
		strcpy(c->szShopTitle, summary.c_str());
	}
	else {
		c->szShopTitle[0] = '\0';
	}
	
	if( Owner->GuildMarkIndex >= 0 && GuildMark[Owner->GuildMarkIndex].UnionName[0] )
	{
		// ��忬�հ� ���հ��� ǥ��
		if( Owner->GuildRelationShip == GR_UNION )
			wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1295] );
		if( Owner->GuildRelationShip == GR_UNIONMASTER )
		{
			if( Owner->GuildStatus == G_MASTER )
				wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1296] );
			else
				wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1295] );
		}
		else if( Owner->GuildRelationShip == GR_RIVAL )
		{
			if( Owner->GuildStatus == G_MASTER )
				wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1298] );
			else
				wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1297] );
		}
		else if( Owner->GuildRelationShip == GR_RIVALUNION )
			wsprintf( c->Union, "<%s> %s", GuildMark[Owner->GuildMarkIndex].UnionName, GlobalText[1299] );
		else
			wsprintf( c->Union, "<%s>", GuildMark[Owner->GuildMarkIndex].UnionName );
	}
	else
		c->Union[0] = NULL;
	
	// ����� �����å�����ֱ�
	if( Owner->GuildMarkIndex >= 0 )
	{
		c->GuildColor = Owner->GuildTeam;
		
		if( Owner->GuildStatus == G_PERSON )
			wsprintf( c->Guild, "[%s] %s", GuildMark[Owner->GuildMarkIndex].GuildName, GlobalText[1330] );
		else if( Owner->GuildStatus == G_MASTER )
			wsprintf( c->Guild, "[%s] %s", GuildMark[Owner->GuildMarkIndex].GuildName, GlobalText[1300] );
		else if( Owner->GuildStatus == G_SUB_MASTER )
			wsprintf( c->Guild, "[%s] %s", GuildMark[Owner->GuildMarkIndex].GuildName, GlobalText[1301] );
		else if( Owner->GuildStatus == G_BATTLE_MASTER )
			wsprintf( c->Guild, "[%s] %s", GuildMark[Owner->GuildMarkIndex].GuildName, GlobalText[1302] );
		else
			wsprintf( c->Guild, "[%s]", GuildMark[Owner->GuildMarkIndex].GuildName );
	}
	else
	{
		c->GuildColor = 0;
		c->Guild[0] = NULL;
	}
}

void CreateChat(char *ID,const char* Text,CHARACTER *Owner,int Flag, int SetColor)
{
	OBJECT *o = &Owner->Object;
	if(!o->Live || !o->Visible) return;
	
	int Color;
	if ( SetColor != -1)
	{
		Color = SetColor;
	}
	else
	{
		Color = Owner->PK;
		if(o->Kind == KIND_NPC)
			Color = 0;
	}
	
	for(int i=0;i<MAX_CHAT;i++)
	{
		CHAT *c = &Chat[i];
		if(c->Owner == Owner)
		{
			strcpy(c->ID,ID);
			c->Color = Color;
			AddGuildName(c,Owner);
			if(strlen(Text) == 0)
			{
				c->IDLifeTime = 10;
			}
			else
			{
				if(c->LifeTime[0] > 0)
				{
					strcpy(c->Text[1],c->Text[0]);
					c->LifeTime[1] = c->LifeTime[0];
				}
				c->Owner = Owner;
				AddChat(c,Text,Flag);
			}
			return;
		}
	}
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHAT;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_CHAT;i++)
#endif // _VS2008PORTING
	{
		CHAT *c = &Chat[i];
		if(c->IDLifeTime<=0 && c->LifeTime[0]<=0)
		{
			c->Owner = Owner;
			strcpy(c->ID,ID);
			c->Color = Color;
			AddGuildName(c,Owner);
			if(strlen(Text) == 0)
			{
				c->IDLifeTime = 100;
			}
			else
			{
				AddChat(c,Text,Flag);
			}
			return;
		}
	}
}

int CreateChat(char *ID,const char* Text,OBJECT* Owner,int Flag, int SetColor)
{
	OBJECT *o = Owner;
	if(!o->Live || !o->Visible) return 0;
	
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Color = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Color;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	if ( SetColor != -1)
	{
		Color = SetColor;
	}
	
	for(int i=0;i<MAX_CHAT;i++)
	{
		CHAT *c = &Chat[i];
		if(c->IDLifeTime<=0 && c->LifeTime[0]<=0)
		{
            c->Owner = NULL;
			strcpy(c->ID,ID);
			c->Color        = Color;
            c->GuildColor   = 0;
			c->Guild[0]     = NULL;
			AddChat(c,Text,0);
            c->LifeTime[0]  = Flag;
			
			Vector(o->Position[0],o->Position[1],o->Position[2]+o->BoundingBoxMax[2]+60.f,c->Position);
			return c->LifeTime[0];
		}
	}
	
    return 0;
}

void AssignChat(char *ID,const char* Text,int Flag)
{
	CHARACTER *Chater = NULL;
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
	int i;
	for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
	{
		CHARACTER *c = &CharactersClient[i];
		OBJECT *o = &c->Object;
		if(o->Live && o->Kind==KIND_PLAYER)
		{
			if(strcmp(c->ID,ID) == NULL)
			{
				Chater = c;
				CreateChat(ID,Text,Chater,Flag);
				return;
			}
		}
	}
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
	{
		CHARACTER *c = &CharactersClient[i];
		OBJECT *o = &c->Object;
		if(o->Live && o->Kind==KIND_MONSTER)
		{
			if(strcmp(c->ID,ID) == NULL)
			{
				Chater = c;
				CreateChat(ID,Text,Chater,Flag);
				return;
			}
		}
	}
}	

void MoveChat()
{
	for(int i=0;i<MAX_CHAT;i++)
	{
		CHAT *c = &Chat[i];
		if(c->IDLifeTime > 0)
			c->IDLifeTime--;
		if(c->LifeTime[0] > 0)
			c->LifeTime[0]--;
		if(c->LifeTime[1] > 0)
			c->LifeTime[1]--;
		if(c->Owner!=NULL && (!c->Owner->Object.Live || !c->Owner->Object.Visible))
		{
			c->IDLifeTime = 0;
			c->LifeTime[0] = 0;
			c->LifeTime[1] = 0;
		}
		if(c->LifeTime[0] > 0){
			DisableShopTitleDraw(c->Owner);
		}
		if(c->Owner!=NULL && c->LifeTime[0] == 0){
			EnableShopTitleDraw(c->Owner);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ��Ŷ ����� ���� ����ϴ� �Լ�(�۾��� ���� �ӽ÷� �����)
///////////////////////////////////////////////////////////////////////////////

BYTE DebugText[10][256];
int  DebugTextLength[10];
char DebugTextCount = 0;

int RenderDebugText(int y)
{
	char Text[100];
	int Width = 16;
    for(int i=0;i<min(DebugTextCount,10);i++)
	{
		int  Type  = 0;
		int  Count = 0;
		int  x     = 0;
		bool Hex   = true;
		int  SizeByte = 1;
		for(int j=0;j<DebugTextLength[i];j++)
		{
			glColor3f(0.6f,0.6f,0.6f);
			if(j==0)
			{
				if(DebugText[i][j]==0xc2) SizeByte = 2;
			}
			if(j==2)
			{
				if(SizeByte==1)
				{
					Type = DebugText[i][j];
					glColor3f(1.f,1.f,1.f);
					if(DebugText[i][j]==0x00)
					{
						x = Width*4;
					}
				}
			}
			if(j==3)
			{
				if(SizeByte==2)
				{
					Type = DebugText[i][j];
					glColor3f(1.f,1.f,1.f);
				}
			}
			
			SIZE TextSize;
			if(Hex)
			{
				sprintf(Text,"%0.2x",DebugText[i][j]);
				g_pRenderText->RenderText(x,y,Text, 0, 0, RT3_SORT_CENTER, &TextSize);
			}
			else
			{
				sprintf(Text,"%c",DebugText[i][j]);
				g_pRenderText->RenderText(x,y,Text, 0, 0, RT3_SORT_CENTER, &TextSize);
			}
			if(Hex)
			{
				x += Width;
			}
			else
			{
				x += TextSize.cx;
			}
			Count++;
		}
		y += 12;
	}
	return y;
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮���� ȭ���� ã�� �ε����� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

int SearchArrow ()
{
#ifdef ADD_SOCKET_ITEM	
	if ( GetBaseClass(CharacterAttribute->Class)==CLASS_ELF )
    {
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int Arrow = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        int Arrow;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		// ȭ���� ���
#ifdef KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		if( GetEquipedBowType( ) == BOWTYPE_BOW )
#else // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		if( GetEquipedBowType(&(CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT])) == BOWTYPE_BOW )
#endif // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		{
			Arrow = ITEM_BOW+15;
		}
		// ���� ȭ���� ���
#ifdef KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		else if( GetEquipedBowType( ) == BOWTYPE_CROSSBOW )
#else // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		else if( GetEquipedBowType(&(CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT])) == BOWTYPE_CROSSBOW )
#endif // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
		{
			Arrow = ITEM_BOW+7;
		}
		
		int iIndex = g_pMyInventory->FindItemReverseIndex(Arrow);
		return iIndex;
	}
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	
    if ( GetBaseClass(CharacterAttribute->Class)==CLASS_ELF )
    {
        int Arrow;
		
		int RightType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		int LeftType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		
		
        //  ȭ���� ���.
		if( (LeftType>=ITEM_BOW && LeftType<ITEM_BOW+7) || LeftType==ITEM_BOW+17 || LeftType==ITEM_BOW+20
			|| LeftType == ITEM_BOW+21 || LeftType == ITEM_BOW+22 )
		{
			Arrow=ITEM_BOW+15;
		}
        //  ���� ȭ���� ���.
		else if((RightType>=ITEM_BOW+8 && RightType<ITEM_BOW+15) ||
			(RightType>=ITEM_BOW+16&& RightType<ITEM_BOW+MAX_ITEM_INDEX ) )
		{
			Arrow=ITEM_BOW+7;
		}
		
		int iIndex = g_pMyInventory->FindItemReverseIndex(Arrow);
		return iIndex;
    }
    else
    {
    }
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮���� ȭ������ ���� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////
int SearchArrowCount()
{
	int Count = 0;
#ifdef ADD_SOCKET_ITEM	
	if ( GetBaseClass(CharacterAttribute->Class) == CLASS_ELF )
    {
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int Arrow = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        int Arrow;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		// ȭ���� ���
		if( GetEquipedBowType() == BOWTYPE_BOW )
		{
			Arrow = ITEM_BOW+15;
		}
		// ���� ȭ���� ���
		else if( GetEquipedBowType() == BOWTYPE_CROSSBOW )
		{
			Arrow = ITEM_BOW+7;
		}
		
		Count = g_pMyInventory->GetNumItemByType(Arrow);
	}
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	
	
    if ( GetBaseClass(CharacterAttribute->Class)==CLASS_ELF )
    {
        int Arrow;
		int RightType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		int LeftType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		
		
        //  ȭ���� ���.
		if( (LeftType>=ITEM_BOW && LeftType<ITEM_BOW+7) || LeftType==ITEM_BOW+17 || LeftType==ITEM_BOW+20
			|| LeftType == ITEM_BOW+21 || LeftType == ITEM_BOW+22 )
		{
			Arrow=ITEM_BOW+15;
		}
        //  ���� ȭ���� ���.
		else if((RightType>=ITEM_BOW+8 && RightType<ITEM_BOW+15) ||
			(RightType>=ITEM_BOW+16&& RightType<ITEM_BOW+MAX_ITEM_INDEX ) )
		{
			Arrow=ITEM_BOW+7;
		}
		
		Count = g_pMyInventory->GetNumItemByType(Arrow);
    }
    else
    {
    }
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	return Count;
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��Ϳ� Ÿ�ϰ��� �Ÿ��� �����Ÿ� ���� ������ ������ �����ϴ� �Լ�
// ���ݰŸ� ���� ����
///////////////////////////////////////////////////////////////////////////////
bool CheckTile(CHARACTER *c,OBJECT *o,float Range)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(c == NULL)	return false;
	if(o == NULL)	return false;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	float dx = o->Position[0]-(TargetX*TERRAIN_SCALE+TERRAIN_SCALE*0.5f);
	float dy = o->Position[1]-(TargetY*TERRAIN_SCALE+TERRAIN_SCALE*0.5f);
	
	float Distance = sqrtf(dx*dx+dy*dy);
	if(Distance <= TERRAIN_SCALE*Range)
	{
		return true;
	}
	
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��Ϳ� Ÿ�ϰ��� ���̿� ��ֹ��� �ִ��� Ȯ��
// ���ݽ� �߰��� ��ֹ��� �ִ� Ȯ�ν� ����
///////////////////////////////////////////////////////////////////////////////
bool CheckWall(int sx1,int sy1,int sx2,int sy2)
{
	int Index = TERRAIN_INDEX_REPEAT(sx1,sy1);
	
    int nx1,ny1,d1,d2,len1,len2;
    int px1 = sx2-sx1;
    int py1 = sy2-sy1;
    if(px1 < 0  ) {px1 = -px1;nx1 =-1           ;} else nx1 = 1;
    if(py1 < 0  ) {py1 = -py1;ny1 =-TERRAIN_SIZE;} else ny1 = TERRAIN_SIZE;
    if(px1 > py1) {len1 = px1;len2 = py1;d1 = ny1;d2 = nx1;}
    else          {len1 = py1;len2 = px1;d1 = nx1;d2 = ny1;}
	
	int error = 0,count = 0;
    do{
#ifdef LDK_ADD_EMPIRE_GUARDIAN_DOOR_ATTACK
		//���� ��ȣ�� ������ �����Ӽ� �����ϰ� ���� �����ϵ��� ����
		int _type = (SelectedCharacter >= 0 ? CharactersClient[SelectedCharacter].Object.Type : 0);
		if	( ( _type!=MODEL_MONSTER01+183 && _type!=MODEL_MONSTER01+184 && _type!=MODEL_MONSTER01+186 && _type!=MODEL_MONSTER01+187 )
			&& ( TerrainWall[Index]>=TW_NOMOVE && (TerrainWall[Index]&TW_ACTION)!=TW_ACTION && (TerrainWall[Index]&TW_HEIGHT)!=TW_HEIGHT && (TerrainWall[Index]&TW_CAMERA_UP)!=TW_CAMERA_UP ) )      //  ī�޶��� ��ġ�� ĳ������ �߽ɿ��� ���� �ø���.
#else //LDK_ADD_EMPIRE_GUARDIAN_DOOR_ATTACK
		if ( TerrainWall[Index]>=TW_NOMOVE && (TerrainWall[Index]&TW_ACTION)!=TW_ACTION 
            && (TerrainWall[Index]&TW_HEIGHT)!=TW_HEIGHT            //  
            && (TerrainWall[Index]&TW_CAMERA_UP)!=TW_CAMERA_UP      //  ī�޶��� ��ġ�� ĳ������ �߽ɿ��� ���� �ø���.
			) 
#endif //LDK_ADD_EMPIRE_GUARDIAN_DOOR_ATTACK
        {
            return false;
        }
		error += len2;
		if(error > len1/2) 
		{
			Index += d1;
			error -= len1;
		}
		Index += d2;
	} while(++count <= len1);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// ����Ʈ�� �ɸ��Ͱ� �����Ҽ� �ִ� �ɸ������� üũ�ϴ� �Լ�
// �ɸ��Ϳ� ���콺�� ������ ������ ���
///////////////////////////////////////////////////////////////////////////////
bool CheckAttack_Fenrir(CHARACTER* c)
{
	if (SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
	{
		return false;	// �������� ��� ������	
	}
		
#ifndef GUILD_WAR_EVENT
		
		if ( InChaosCastle()==true && c!=Hero ) // ī����ĳ������ ĳ���͸� �����Ҽ� �ְ��Ѵ�.
		{
			return true;
		}
#ifdef PBG_ADD_PKFIELD
#ifdef ASG_ADD_GENS_SYSTEM
		// ���������̰�, ���õ� ĳ���Ͱ� Ÿĳ�����̰�, ���� �ս��� �ƴѰ�?
		else if(::IsStrifeMap(World) && c != Hero && c->m_byGensInfluence != Hero->m_byGensInfluence)
#else	// ASG_ADD_GENS_SYSTEM
		else if(IsPKField() && c!=Hero)
#endif	// ASG_ADD_GENS_SYSTEM
		{	
			if(((strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL) ||
			(g_pPartyManager->IsPartyMember(SelectedCharacter)))
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&& SEASON3B::IsPress(VK_CONTROL) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&& (HIBYTE(GetAsyncKeyState(VK_CONTROL))==128))
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			{
				return true;
			}
			else if((strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)!=NULL) && 
			!g_pPartyManager->IsPartyMember(SelectedCharacter))
			{
				return true;
			}
		}
#endif //PBG_ADD_PKFIELD
		if( c->Object.Kind == KIND_MONSTER)
		{
			if(EnableGuildWar && EnableSoccer)
			{
				return true;
			}
			else if(EnableGuildWar)
			{
				return false;
			}
			
			return true;
		}
		else if(c->Object.Kind==KIND_PLAYER)
		{
			//  �������� �ڽ��� ������ Ʋ���ٸ� �����Ҽ� �ִ�.
			if ( battleCastle::IsBattleCastleStart() )
			{
				if ( ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK 
					|| Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2
					|| Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3
					|| Hero->EtcPart==PARTS_ATTACK_TEAM_MARK2 
					|| Hero->EtcPart==PARTS_ATTACK_TEAM_MARK3 
					) && 
					( c->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || c->EtcPart==PARTS_DEFENSE_TEAM_MARK ) )
				{
					if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking) )
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ( ( Hero->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || Hero->EtcPart==PARTS_DEFENSE_TEAM_MARK )
					&& ( c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || c->EtcPart==PARTS_ATTACK_TEAM_MARK  
					|| c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3
					|| c->EtcPart==PARTS_ATTACK_TEAM_MARK2 || c->EtcPart==PARTS_ATTACK_TEAM_MARK3 ) )
				{
					if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking) )
						{
							return true;
						}
						else
						{
							return false;
						}
				}
				else if ( g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack1) 
					|| g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack2)
					|| g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack3) )
				{
					OBJECT* o = &c->Object;
					if ( !g_isCharacterBuff(o, eBuff_CastleRegimentAttack1) 
						&& !g_isCharacterBuff(o, eBuff_CastleRegimentAttack2) 
						&& !g_isCharacterBuff(o, eBuff_CastleRegimentAttack3) )
						{
							if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking)	)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
				}
				else if ( g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentDefense) )
				{
					OBJECT* o = &c->Object;
					
					if ( !g_isCharacterBuff(o, eBuff_CastleRegimentDefense) )
					{
						if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking) )
						{
							return true;
						}
						else
						{
							return false;
						}
						
					}
					
				}
				
			}
				
			// ������Ҽ��� ���
			if( c->GuildRelationShip == GR_RIVAL || c->GuildRelationShip == GR_RIVALUNION )		//������ ǥ��
			{
				return true;
			}
			
			if ( EnableGuildWar && c->PK>=PVP_MURDERER2 && c->GuildMarkIndex!=-1 
				&& strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL)
			{
				return  false;
			}
			
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
			//	������.
			else if(g_DuelMgr.IsDuelEnabled())
			{
				if (g_DuelMgr.IsDuelPlayer(c, DUEL_ENEMY))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
#else	// YDG_ADD_NEW_DUEL_SYSTEM
#ifdef DUEL_SYSTEM
			//	������.
			else if( g_bEnableDuel )
			{
				if ( c->Key == g_iDuelPlayerIndex && strcmp(c->ID, g_szDuelPlayerID) == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
			else if ( EnableGuildWar )  // ����, ��Ʋ�౸.
			{
				if ( c->GuildTeam==2 && c!=Hero )
				{
					return true;
				}
				else 
				{
					return false;
				}
			}
			//	ī��, ���� ����.
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
			else if ( (c->PK >= PVP_MURDERER2) || (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (c != Hero) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			else if ( c->PK >= PVP_MURDERER2 || ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && c!=Hero ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			{
#ifdef PK_ATTACK_TESTSERVER_LOG
				PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG
				return true;
			}
			else if ( g_CursedTemple->IsCursedTemple() && !g_CursedTemple->IsPartyMember( SelectedCharacter ) )
			{
				return true;
			}
			else
			{
				return false;
			}
	}
#ifdef _PVP_ATTACK_GUARD
	else if (c->Object.Kind==KIND_NPC)
	{
		if ( (c->MonsterIndex == 247 || c->MonsterIndex == 249) 
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&&  (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (c != Hero) || (g_bAutoPvPSetting == TRUE) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&& ( ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && c!=Hero ) || ( g_bAutoPvPSetting == TRUE ) ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
			return true;
		}
	}
#endif	// _PVP_ATTACK_GUARD
	else
	{
		return false;
	}
	
	return false;
#endif //GUILD_WAR_EVENT
	
}

bool CheckAttack()
{
	if (SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
	{
		return false;
	}
		
	if(SelectedCharacter==-1)
	{
		return false;
	}
		
#ifdef FOR_HACKING
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
	if( (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (SEASON3B::IsPress(VK_MENU) == TRUE) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	if( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && HIBYTE(GetAsyncKeyState(VK_MENU))==128 )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	{
		if ( FindText( Hero->ID, "webzen" ) )
		{
			return false;
		}
	}
#endif //FOR_HACKING

#ifdef CSK_ADD_GM_ABILITY
	if(IsGMCharacter() && IsNonAttackGM() == true)
	{
		return false;
	}
#endif // CSK_ADD_GM_ABILITY
		
	CHARACTER *c = &CharactersClient[SelectedCharacter];
		
#ifndef GUILD_WAR_EVENT
	//  ĳ���͸� �����Ҽ� �ְ��Ѵ�.
	if ( InChaosCastle()==true && c!=Hero )
	{
		return true;
	}
#endif //GUILD_WAR_EVENT
#ifdef PBG_ADD_PKFIELD
#ifdef ASG_ADD_GENS_SYSTEM
	// ���������̰�, ���õ� ĳ���Ͱ� Ÿĳ�����̰�, ���� �ս��� �ƴѰ�?
	else if(::IsStrifeMap(World) && c != Hero && c->m_byGensInfluence != Hero->m_byGensInfluence)
#else	// ASG_ADD_GENS_SYSTEM
	else if(IsPKField() && c!=Hero)
#endif	// ASG_ADD_GENS_SYSTEM
	{	
		if(g_pCommandWindow->GetMouseCursor( ) == CURSOR_IDSELECT)	
		{
			//Ŀ��Ʈ Ű ����������..DŰ..
			return false;
		}
#ifdef PBG_FIX_PKFIELD_ATTACK
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		//===================================================================
		// ALT Ű ��������..
		//===================================================================
		if(SEASON3B::IsPress(VK_MENU) == TRUE)
		{
			return false;
		}

		if(SEASON3B::IsPress(VK_CONTROL) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		if(HIBYTE(GetAsyncKeyState(VK_MENU))==128)
		{
			//ArtŰ�� ��������..
			return false;
		}

		if(HIBYTE(GetAsyncKeyState(VK_CONTROL))==128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
#ifdef PBG_FIX_GUILDWAR_PK
			if(EnableGuildWar)
			{
				if(c->GuildTeam==2 && c!=Hero)	//��������߿� ����.
					return true;
				else							//��������� �츮�� �� �Ϲ���.
					return false;				//�Ϲ����� �Ÿ��� ����.
			}
			else
#endif //PBG_FIX_GUILDWAR_PK
				return true;	//�Ϲ� ��Ʈ�ѷ� ���� ����..
		}
		else if(strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL)
		{
			// ���� ���
			if(g_pPartyManager->IsPartyMember(SelectedCharacter))
			{
				// ��Ƽ ������
				return false;
			}
#ifdef PBG_FIX_GUILDWAR_PK
			if(EnableGuildWar)
			{
				//��� ������
				if(c->GuildTeam==2 && c!=Hero)
					return true;	//���� �ɸ��� �ȵ�.
				else
					return false;	//���� ���.
			}
#endif //PBG_FIX_GUILDWAR_PK
			if(c->GuildRelationShip == GR_NONE)
				return true;		// �Ϲ��ε鳢�� ����.
			else
				return false;		// ������ ���踦 ������ ���ձ��.
		}
		else if((c->GuildRelationShip == GR_UNION) || (c->GuildRelationShip == GR_UNIONMASTER))
		{
			return false;			//��� ���� or ��� ���� ������
		}
#ifdef PBG_FIX_GUILDWAR_PK
		else if(EnableGuildWar)
		{
			if(c->GuildTeam==2 && c!=Hero)
				return true;				// ��� �����߿� �����
			else/* if(c->GuildRelationShip == GR_NONE)*/
				return false;				// �츮�� �� �Ϲ���
		}
#endif //PBG_FIX_GUILDWAR_PK
		else if(g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
#ifdef PBG_FIX_GUILDWAR_PK
			if((c->GuildRelationShip == GR_RIVAL) || (c->GuildRelationShip == GR_RIVALUNION))
			{
				return true;			// ������ ���迡�� ��Ƽ�� �ξ
			}
			else
#endif //PBG_FIX_GUILDWAR_PK
				return false;			// �׿��� ��Ƽ ����
		}
		else
		{
			return true;
		}
#else //PBG_FIX_PKFIELD_ATTACK
		if(((strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL) ||
		(g_pPartyManager->IsPartyMember(SelectedCharacter)))
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		&& (SEASON3B::IsPress(VK_CONTROL) == TRUE) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		&& (HIBYTE(GetAsyncKeyState(VK_CONTROL))==128))
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
			return true;
		}
		else if((c->GuildRelationShip == GR_UNION || c->GuildRelationShip == GR_UNIONMASTER) && !g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
			return false;
		}
		else if((strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)!=NULL) && 
		!g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
			return true;
		}
		else if(c->GuildRelationShip == GR_NONE && !g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
			return true;
		}
#endif //PBG_FIX_PKFIELD_ATTACK
	}
#endif //PBG_ADD_PKFIELD
		
	if( c->Object.Kind == KIND_MONSTER)
	{
		if(EnableGuildWar && EnableSoccer)
		{
			return true;
		}
		else if(EnableGuildWar)
		{
			return false;
		}
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
		else if(g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch))
		{
			return false;
		}
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
		
		return true;
	}
	else if(c->Object.Kind==KIND_PLAYER)
	{
		//  �������� �ڽ��� ������ Ʋ���ٸ� �����Ҽ� �ִ�.
		if ( battleCastle::IsBattleCastleStart() )
		{
			if ( ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK 
				|| Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3
				|| Hero->EtcPart==PARTS_ATTACK_TEAM_MARK2 || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK3 ) 
				&& ( c->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || c->EtcPart==PARTS_DEFENSE_TEAM_MARK ) )
			{
				if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if ((Hero->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || Hero->EtcPart==PARTS_DEFENSE_TEAM_MARK ) 
				&& ( c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || c->EtcPart==PARTS_ATTACK_TEAM_MARK  
				|| c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3
				|| c->EtcPart==PARTS_ATTACK_TEAM_MARK2 || c->EtcPart==PARTS_ATTACK_TEAM_MARK3))
			{
				if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking ) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if( g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack1)
				|| g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack2) 
				|| g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentAttack3) )
			{
				OBJECT* o = &c->Object;
				
				if( !g_isCharacterBuff(o, eBuff_CastleRegimentAttack1) 
					&& !g_isCharacterBuff(o, eBuff_CastleRegimentAttack2) 
					&& !g_isCharacterBuff(o, eBuff_CastleRegimentAttack3) )
					{
						if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking ) )
						{
							return true;
						}
						else
						{
							return false;
						}
					}
			}
			else if( g_isCharacterBuff((&Hero->Object), eBuff_CastleRegimentDefense ) )
			{
				OBJECT* o = &c->Object;
				
				if( !g_isCharacterBuff(o, eBuff_CastleRegimentDefense) )
				{
					if( !g_isCharacterBuff((&c->Object), eBuff_Cloaking ) )
					{
						return true;
					}
					else
					{
						return false;
					}
						
				}
				
			}
			
		}
		
		// ������Ҽ��� ���
		if( c->GuildRelationShip == GR_RIVAL || c->GuildRelationShip == GR_RIVALUNION )
		{
			return true;
		}
		
		if ( EnableGuildWar && c->PK>=PVP_MURDERER2 && c->GuildMarkIndex!=-1 
			&& strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL)
		{
			return  false;
		}
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
		//	������.
		else if(g_DuelMgr.IsDuelEnabled())
		{
			if (g_DuelMgr.IsDuelPlayer(c, DUEL_ENEMY))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch))
		{
			return false;
		}
#else	// YDG_ADD_NEW_DUEL_SYSTEM
#ifdef DUEL_SYSTEM
		//	������.
		else if( g_bEnableDuel )
		{
			if ( c->Key == g_iDuelPlayerIndex && strcmp(c->ID, g_szDuelPlayerID) == 0)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
		else if ( EnableGuildWar )  // ����, ��Ʋ�౸.
		{
			if ( c->GuildTeam==2 && c!=Hero ) 
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//	ī��, ���� ����.
#ifndef LDS_MOD_PKSYSTEM_INGAMESHOP_ATTACK_PKLEVEL1	// #ifndef
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
		// ȥ������ȭ���ϰ�� ������ ���ú��� ��Ʈ�� Ű�� ������ �ʰ� ���ݰ����ϰ�
		else if(g_PKSystem->IsPKState(PVP_CAUTION, c->PK) && c != Hero)	return true;
		// �Ϲݼ��� ��� ���� else if�� ����
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#endif // LDS_MOD_PKSYSTEM_INGAMESHOP_ATTACK_PKLEVEL1
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		else if ( (c->PK >= PVP_MURDERER2) || (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (c != Hero) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		else if ( c->PK >= PVP_MURDERER2 || ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && c != Hero ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
#ifdef PK_ATTACK_TESTSERVER_LOG
			PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG
			return true;
		}
		else if ( g_CursedTemple->IsCursedTemple() && !g_CursedTemple->IsPartyMember( SelectedCharacter ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
#ifdef _PVP_ATTACK_GUARD
	else if (c->Object.Kind==KIND_NPC)
	{
		if ( (c->MonsterIndex == 247 || c->MonsterIndex == 249) 
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&& (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (c != Hero) || (g_bAutoPvPSetting == TRUE) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			&& ( ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && c!=Hero ) || ( g_bAutoPvPSetting == TRUE ) ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
			return true;
		}
	}
#endif	// _PVP_ATTACK_GUARD
	else
	{
		return false;
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////
//	������ ĳ���Ͱ� ���� ���� ĳ������ ��� �� ĳ������ Key���� �ش�.
//////////////////////////////////////////////////////////////////////////
int	getTargetCharacterKey ( CHARACTER* c, int selected )
{
	if (SEASON3B::CNewUIInventoryCtrl::GetPickedItem()) 
		return -1;

#ifdef CSK_FIX_ADD_EXEPTION
	// ĳ���Ͱ� �ڱ��ڽ��� �ƴϰų� selected �ε����� ���� ���� ���̸� ����
	if(c != Hero || selected < 0 || selected >= MAX_CHARACTERS_CLIENT)
	{
		return -1;
	}
#else // CSK_FIX_ADD_EXEPTION
	if ( selected==-1 || c!=Hero ) return -1;
#endif // CSK_FIX_ADD_EXEPTION
		
	CHARACTER *sc = &CharactersClient[selected];
	
#ifndef GUILD_WAR_EVENT
    //  ĳ���͸� �����Ҽ� �ְ��Ѵ�.
    if ( InChaosCastle()==true )
    {
        return sc->Key;
    }
#endif //GUILD_WAR_EVENT
	
	if ( EnableGuildWar && sc->PK>=PVP_MURDERER2 && sc->GuildMarkIndex!=-1 && strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[sc->GuildMarkIndex].GuildName)==NULL)
		return  -1;
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
	//	������.
	else if(g_DuelMgr.IsDuelEnabled())
	{
		if (g_DuelMgr.IsDuelPlayer(sc, DUEL_ENEMY))
			return sc->Key;
		else 
			return -1;
	}
#else	// YDG_ADD_NEW_DUEL_SYSTEM
#ifdef DUEL_SYSTEM
	//	������.
	else if( g_bEnableDuel )
	{
		if ( sc->Key == g_iDuelPlayerIndex )
			return sc->Key;
		else 
			return -1;
	}
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
	// ��������϶�..
    else if ( sc->GuildRelationShip == GR_RIVAL || sc->GuildRelationShip == GR_RIVALUNION )  
	{
		return sc->Key;
	}
	// 
	// ����, ��Ʋ�౸.
    else if ( EnableGuildWar )  
	{
		if ( sc->GuildTeam==2 && sc!=Hero ) 
			return sc->Key;
		else 
			return -1;
	}
#ifdef PBG_ADD_PKFIELD
#ifdef ASG_ADD_GENS_SYSTEM
	// ���������̰�, ���õ� ĳ���Ͱ� Ÿĳ�����̰�, ���� �ս��� �ƴѰ�?
	else if(::IsStrifeMap(World) && sc != Hero && sc->m_byGensInfluence != Hero->m_byGensInfluence
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		&& SEASON3B::IsPress(VK_MENU) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		&& HIBYTE(GetAsyncKeyState(VK_MENU))!=128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
#else	// ASG_ADD_GENS_SYSTEM
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if(IsPKField() && sc!=Hero && SEASON3B::IsPress(VK_MENU) == FALSE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if(IsPKField() && sc!=Hero && HIBYTE(GetAsyncKeyState(VK_MENU))!=128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
#endif	// ASG_ADD_GENS_SYSTEM
	{
		if(sc->GuildRelationShip == GR_NONE && !g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
			return sc->Key;
		}
		else if((strcmp(GuildMark[Hero->GuildMarkIndex].GuildName,GuildMark[c->GuildMarkIndex].GuildName)==NULL) ||
			g_pPartyManager->IsPartyMember(SelectedCharacter))
		{
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
			if(SEASON3B::IsPress(VK_CONTROL) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
			if(HIBYTE(GetAsyncKeyState(VK_CONTROL))==128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
				return sc->Key;
			else 
				return -1;
		}
	}
#endif //PBG_ADD_PKFIELD
	//	ī��, ���� ����.
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if( (sc->PK >= PVP_MURDERER2) || (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (sc != Hero) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if ( sc->PK>=PVP_MURDERER2 || ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && sc!=Hero ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	{
		return sc->Key;
	}
#ifdef _PVP_ATTACK_GUARD
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if( (sc->MonsterIndex == 249) || (SEASON3B::IsPress(VK_CONTROL) == TRUE) && (sc != Hero) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	else if ( sc->MonsterIndex == 249 || ( HIBYTE(GetAsyncKeyState(VK_CONTROL))==128 && sc!=Hero ) )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	{
		return sc->Key;
	}
#endif	// _PVP_ATTACK_GUARD
	else if ( g_CursedTemple->IsCursedTemple() )
	{
		if( g_CursedTemple->IsPartyMember( selected ) )
		{
			return -1;
		}
		else
		{
			return sc->Key;
		}
	}
	else
	{
		return -1;
	}
	
	return -1;
}


///////////////////////////////////////////////////////////////////////////////
// ��ų ���� �Ÿ��� �����α׷����� ���� ����Ǿ����� ��� �޸𸮿�
// ���Ͽ� Ȯ��
///////////////////////////////////////////////////////////////////////////////

// �� �ڸ��� ���� �Ѵ�.
void LetHeroStop( CHARACTER * c, BOOL bSetMovementFalse)
{
	BYTE PathX[1];
	BYTE PathY[1];
	PathX[0] = ( Hero->PositionX);
	PathY[0] = ( Hero->PositionY);
	SendCharacterMove(Hero->Key,Hero->Object.Angle[2],1,PathX,PathY,TargetX,TargetY);
	
	if (c != NULL && bSetMovementFalse == TRUE) 
	{
		c->Movement = false;
	}
}

//  ĳ������ ��ġ�� �����Ѵ�.
void SetCharacterPos ( CHARACTER* c, BYTE posX, BYTE posY, vec3_t position )
{
	BYTE PathX[1];
	BYTE PathY[1];
	PathX[0] = posX;
	PathY[0] = posY;
    
    c->PositionX = PathX[0];
	
    c->PositionY = PathY[0];
	
    VectorCopy( position, c->Object.Position );
	SendCharacterMove(c->Key,c->Object.Angle[2],1,PathX,PathY,PathX[0],PathY[0]);
}

///////////////////////////////////////////////////////////////////////////////
// ��� ��ų ���
///////////////////////////////////////////////////////////////////////////////

bool CastWarriorSkill( CHARACTER *c, OBJECT *o, ITEM *p, int iSkill)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(c == NULL)	return false;
	if(o == NULL)	return false;
	if(p == NULL)	return false;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	bool Success = false;
	
    if ( SelectedCharacter<=-1 ) return false;
	
	TargetX = (int)(CharactersClient[SelectedCharacter].Object.Position[0]/TERRAIN_SCALE);
	TargetY = (int)(CharactersClient[SelectedCharacter].Object.Position[1]/TERRAIN_SCALE);
	
	ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
	g_MovementSkill.m_bMagic = FALSE;
	g_MovementSkill.m_iSkill = iSkill;
	g_MovementSkill.m_iTarget = SelectedCharacter;
    float Distance = GetSkillDistance( iSkill, c )*1.2f;
    //  ����ĳ������ ���⽺ų�� �Ÿ��� �����Ѵ�.
    if ( ( InBloodCastle() == true ) && ( iSkill>=AT_SKILL_SWORD1 && iSkill<=AT_SKILL_SWORD5 ) )
    {
        Distance = 1.8f;
    }
	
	if(CheckTile(c,o,Distance))
	{	// ������ �ٷ� ���
		UseSkillWarrior( c, o);
		Success = true;
	}
	else if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
	{	
		// �ָ� �ɾ�� ���
		c->Movement = true;
		c->MovementType = MOVEMENT_SKILL;
		Success = true;
		
#ifdef CSK_FIX_SYNCHRONIZATION
		SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
	}
	
	return ( Success);
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}


bool SkillWarrior(CHARACTER *c,ITEM *p)
{
	OBJECT *o = &c->Object;
	if(o->Type == MODEL_PLAYER)
	{
		if ( o->CurrentAction==PLAYER_DEFENSE1 ) return false;
		if ( o->CurrentAction>=PLAYER_ATTACK_SKILL_SWORD1 && o->CurrentAction<=PLAYER_ATTACK_SKILL_SWORD4 
			|| o->CurrentAction==PLAYER_ATTACK_TWO_HAND_SWORD_TWO 
			) 
			return false;
	}
	else
	{
		if(o->CurrentAction>=MONSTER01_ATTACK1 && o->CurrentAction<=MONSTER01_ATTACK2) return false;
	}
	int Skill = CharacterAttribute->Skill[g_MovementSkill.m_iSkill];
	if( Skill == AT_SKILL_RIDER 
		|| Skill == AT_SKILL_ONETOONE	// ��ο�
#ifdef PJH_SEASON4_MASTER_RANK4
		|| (AT_SKILL_BLOW_UP <= Skill && Skill <= AT_SKILL_BLOW_UP+4)
#endif	//PJH_SEASON4_MASTER_RANK4
		// â��� ��ų�� �̵������� Ÿ���Ѵ�.
		|| ( Skill == AT_SKILL_SPEAR && ( Hero->Helper.Type == MODEL_HELPER+2 || Hero->Helper.Type == MODEL_HELPER+3 || Hero->Helper.Type == MODEL_HELPER+4 || Hero->Helper.Type == MODEL_HELPER+37 )) 
		|| Skill == AT_SKILL_STRONG_PIER 
		|| Skill == AT_SKILL_LONGPIER_ATTACK // ?? || ���̾����Ʈ
		|| (AT_SKILL_FIRE_BUST_UP <= Skill && Skill <= AT_SKILL_FIRE_BUST_UP+4)
		|| Skill == AT_SKILL_RUSH           //  ����.
		|| Skill == AT_SKILL_ONEFLASH       //  �ϼ�.
		|| Skill == AT_SKILL_SPACE_SPLIT    //  ���� ������.
		)
	{
		switch ( Skill)
		{
		case AT_SKILL_SPEAR:	// â���(â�� ���⸦ ��� �־�� ����)
			if( !( o->Type==MODEL_PLAYER && Hero->Weapon[0].Type != -1 && 
				( Hero->Weapon[0].Type >= MODEL_SPEAR && Hero->Weapon[0].Type < MODEL_SPEAR+MAX_ITEM_INDEX ) ) )
			{
				return false;
			}
			break;
#ifdef PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_BLOW_UP:
		case AT_SKILL_BLOW_UP+1:
		case AT_SKILL_BLOW_UP+2:
		case AT_SKILL_BLOW_UP+3:
		case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_ONETOONE:	// ��ο�
			if( !( Hero->Weapon[0].Type != -1 && ( Hero->Weapon[0].Type < MODEL_STAFF || Hero->Weapon[0].Type >= MODEL_STAFF+MAX_ITEM_INDEX )))
			{
				return false;
			}
			break;
		case AT_SKILL_ONEFLASH:	// ��������?
			if( Hero->Weapon[0].Type < MODEL_SWORD || Hero->Weapon[0].Type >= MODEL_SWORD+MAX_ITEM_INDEX )
			{
				return false;
			}
			break;
		}
		// mana üũ
		int iMana, iSkillMana;
		GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
		if(CharacterAttribute->Mana < iMana)
		{
			int Index = g_pMyInventory->FindManaItemIndex();
			
			if(Index != -1)
			{
				SendRequestUse(Index, 0);
			}
			return false;
		}
		// skillmana ����
		if(iSkillMana > CharacterAttribute->SkillMana)
		{
			return false;
		}
		
        if ( !CheckSkillDelay( g_MovementSkill.m_iSkill ) )
        {
            return false;
        }
		if(CheckAttack())
		{
			return ( CastWarriorSkill( c, o, p, Skill));
		}
	}
	
	bool Success = false;
	for(int i=0;i<p->SpecialNum;i++)
	{
		if(CharacterAttribute->Skill[Hero->CurrentSkill] == p->Special[i])
		{
			int iMana;
			GetSkillInformation( p->Special[i], 1, NULL, &iMana, NULL);
			if(CharacterAttribute->Mana < iMana)
			{
				int Index = g_pMyInventory->FindManaItemIndex();
				
				if(Index != -1)
				{
					SendRequestUse(Index, 0);
				}
				continue;
			}
            if ( !CheckSkillDelay( Hero->CurrentSkill ) )
            {
                continue;
            }
			switch(p->Special[i])
			{
			case AT_SKILL_BLOCKING:
				c->Movement = false;
				if(o->Type == MODEL_PLAYER)
					SetAction(o,PLAYER_DEFENSE1);
				else
					SetPlayerAttack(c);
				SendRequestMagic(p->Special[i],Hero->Key);
				Success = true;
				break;
			case AT_SKILL_SWORD1:
			case AT_SKILL_SWORD2:
			case AT_SKILL_SWORD3:
			case AT_SKILL_SWORD4:
			case AT_SKILL_SWORD5:
            case AT_SKILL_RIDER:
				if(CheckAttack())
					Success = CastWarriorSkill( c, o, p, p->Special[i]);
				break;
			}
		}
	}
	
	if(CharacterAttribute->Skill[Hero->CurrentSkill] == AT_SKILL_DARK_SCREAM
#ifdef PJH_SEASON4_MASTER_RANK4
		||(AT_SKILL_FIRE_SCREAM_UP <= CharacterAttribute->Skill[Hero->CurrentSkill] && AT_SKILL_FIRE_SCREAM_UP+4 >= CharacterAttribute->Skill[Hero->CurrentSkill])
#endif //PJH_SEASON4_MASTER_RANK4
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		|| Skill == AT_SKILL_GAOTIC
#endif //#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		)
	{
		int iMana;
		GetSkillInformation( CharacterAttribute->Skill[Hero->CurrentSkill], 1, NULL, &iMana, NULL);
		if(CharacterAttribute->Mana < iMana)
		{
			int Index = g_pMyInventory->FindManaItemIndex();
			
			if(Index != -1)
			{
				SendRequestUse(Index, 0);
			}
			return Success;
		}
		
		float Distance = GetSkillDistance( CharacterAttribute->Skill[Hero->CurrentSkill], c );
		if( CheckTile( c, o, Distance ) )
		{
			o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
			WORD TKey = 0xffff;
			
			if ( g_MovementSkill.m_iTarget!=-1 )
			{
				TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
			}
		}
	}
	
	return Success;
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

void UseSkillWarrior( CHARACTER *c, OBJECT *o)
{
	int Skill = g_MovementSkill.m_bMagic ? CharacterAttribute->Skill[g_MovementSkill.m_iSkill] : g_MovementSkill.m_iSkill;
	
	LetHeroStop();
	c->Movement = false;
	if(o->Type == MODEL_PLAYER)
	{
        SetAttackSpeed();
		
		switch ( Skill)
		{
		case AT_SKILL_SPEAR:
			if(c->Helper.Type == MODEL_HELPER+37)
				SetAction(o, PLAYER_FENRIR_ATTACK_SPEAR);
			else
				SetAction(o,PLAYER_ATTACK_SKILL_SPEAR);
			break;
#ifdef PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_BLOW_UP:
		case AT_SKILL_BLOW_UP+1:
		case AT_SKILL_BLOW_UP+2:
		case AT_SKILL_BLOW_UP+3:
		case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_ONETOONE:	// ��ο�
			SetAction(o,PLAYER_ATTACK_ONETOONE);
			break;
        case AT_SKILL_RIDER:    //  ����Ʈ ��ų.
			//		    SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
            if ( World==WD_8TARKAN || World==WD_10HEAVEN || g_Direction.m_CKanturu.IsMayaScene() )
                SetAction ( o, PLAYER_SKILL_RIDER_FLY );
            else 
                SetAction ( o, PLAYER_SKILL_RIDER );
            break;
#ifdef PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_FIRE_SCREAM_UP:
		case AT_SKILL_FIRE_SCREAM_UP+1:
		case AT_SKILL_FIRE_SCREAM_UP+2:
		case AT_SKILL_FIRE_SCREAM_UP+3:
		case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_DARK_SCREAM:
			break;

#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		case AT_SKILL_GAOTIC:
			break;
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
        case AT_SKILL_STRONG_PIER:      //  ��Ʈ���Ǿ�.
		case AT_SKILL_FIRE_BUST_UP:
		case AT_SKILL_FIRE_BUST_UP+1:
		case AT_SKILL_FIRE_BUST_UP+2:
		case AT_SKILL_FIRE_BUST_UP+3:
		case AT_SKILL_FIRE_BUST_UP+4:
        case AT_SKILL_LONGPIER_ATTACK:  //  ���Ǿ����.
        case AT_SKILL_SPACE_SPLIT :     //  ���� ������.
            break;
        case AT_SKILL_RUSH :			//  ��� ���� ��ų.
			SetAction ( o, PLAYER_ATTACK_RUSH );
            break;
		default:
			if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
				SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ��ų ����(ĳ���� ���ϸ��̼� ���� ����)
			else
				SetAction(o,PLAYER_ATTACK_SKILL_SWORD1+g_MovementSkill.m_iSkill-AT_SKILL_SWORD1);
			break;
		}
	}
	else
	{
		SetPlayerAttack(c);
	}
	
	vec3_t Light;
	Vector(1.f,1.f,1.f,Light);
	
    if ( Skill!=AT_SKILL_STRONG_PIER && Skill!=AT_SKILL_LONGPIER_ATTACK 
		&& Skill!=AT_SKILL_SPACE_SPLIT     //  ���� ������.
		&& Skill!=AT_SKILL_DARK_SCREAM     
#ifdef PJH_SEASON4_MASTER_RANK4
		&& !(AT_SKILL_FIRE_SCREAM_UP <= Skill && AT_SKILL_FIRE_SCREAM_UP+4 >= Skill)
#endif //PJH_SEASON4_MASTER_RANK4
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		&& Skill!=AT_SKILL_THRUST
		&& Skill!=AT_SKILL_STAMP
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		&& !(AT_SKILL_FIRE_BUST_UP <= Skill && AT_SKILL_FIRE_BUST_UP+4 >= Skill))
    {
        CreateParticle(BITMAP_SHINY+2,o->Position,o->Angle,Light,0,0.f,o);
		PlayBuffer(SOUND_BRANDISH_SWORD01+rand()%2);
    }
	
    VectorCopy(CharactersClient[g_MovementSkill.m_iTarget].Object.Position,c->TargetPosition);
	o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
	
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	if(Skill != AT_SKILL_GAOTIC)
#endif //#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
	
#ifdef LDS_FIX_SYNCRO_HEROATTACK_ACTION_WITH_SERVER
#else // LDS_FIX_SYNCRO_HEROATTACK_ACTION_WITH_SERVER
	c->AttackTime = 1;
#endif // LDS_FIX_SYNCRO_HEROATTACK_ACTION_WITH_SERVER
	
    //  ����ĳ������ ����ġ����� ������ �̵� ��ġ ����.
    if ( ((!g_isCharacterBuff(o, eDeBuff_Harden)) && c->Helper.Type!=MODEL_HELPER+4 )
			&& Skill != AT_SKILL_DARK_SCREAM 
#ifdef PJH_SEASON4_MASTER_RANK4
			&& !(AT_SKILL_FIRE_SCREAM_UP <= Skill && Skill <= AT_SKILL_FIRE_SCREAM_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
			)
		{
			BYTE positionX = (BYTE)(c->TargetPosition[0]/TERRAIN_SCALE);
			BYTE positionY = (BYTE)(c->TargetPosition[1]/TERRAIN_SCALE);
			
			if ( ( InBloodCastle() == true )
				|| Skill==AT_SKILL_STRONG_PIER 
				|| Skill==AT_SKILL_ONEFLASH
				|| Skill==AT_SKILL_RUSH 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==277 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==283 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==278 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==288
				)
			{
				int angle = abs( (int)(o->Angle[2]/45.f) );
				switch ( angle )
				{
				case 0: positionY++;break;
				case 1: positionX--; positionY++; break;
				case 2: positionX--; break;
				case 3: positionX--; positionY--; break;
				case 4: positionY--; break;
				case 5: positionX++; positionY--; break;
				case 6: positionX++; break;
				case 7: positionX++; positionY++; break;
				}
			}
			
			int TargetIndex = TERRAIN_INDEX( positionX, positionY );
			
			if ( (TerrainWall[TargetIndex]&TW_NOMOVE) != TW_NOMOVE && (TerrainWall[TargetIndex]&TW_NOGROUND) != TW_NOGROUND )
			{
				if ( Skill != AT_SKILL_SPEAR 
					&& Skill != AT_SKILL_ONETOONE 
					&& Skill != AT_SKILL_RIDER 
					&& Skill != AT_SKILL_STRONG_PIER 
					&& Skill != AT_SKILL_LONGPIER_ATTACK 
					&& Skill != AT_SKILL_SPACE_SPLIT		// ����������
#ifdef PJH_SEASON4_MASTER_RANK4
					&& !(AT_SKILL_BLOW_UP <= Skill && Skill <= AT_SKILL_BLOW_UP+4)
#endif	//PJH_SEASON4_MASTER_RANK4
					&& !(AT_SKILL_FIRE_BUST_UP <= Skill && Skill <= AT_SKILL_FIRE_BUST_UP+4)
					
					)
				{	
					// â ��ų �̲��� ����
					SendPosition( positionX, positionY );
				}
			}
		}
#ifdef USE_SELFCHECKCODE
		END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
		;
#endif
}

void UseSkillWizard( CHARACTER *c, OBJECT *o)
{
	int Skill = CharacterAttribute->Skill[g_MovementSkill.m_iSkill];
	
	switch ( Skill)
	{
	case AT_SKILL_SPEAR:
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_BLOW_UP:
	case AT_SKILL_BLOW_UP+1:
	case AT_SKILL_BLOW_UP+2:
	case AT_SKILL_BLOW_UP+3:
	case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ONETOONE:
		return;
	}
	
	if(Skill == AT_SKILL_DEATH_CANNON)	//. ������
	{
		if(Hero->Weapon[0].Type < MODEL_STAFF || Hero->Weapon[0].Type >= MODEL_STAFF+MAX_ITEM_INDEX)
			return;
	}
	
	VectorCopy(CharactersClient[g_MovementSkill.m_iTarget].Object.Position,c->TargetPosition);
	o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
	switch(Skill)
	{
	case AT_SKILL_POISON:
	case AT_SKILL_METEO:
	case AT_SKILL_THUNDER:
	case AT_SKILL_ENERGYBALL:
	case AT_SKILL_POWERWAVE:
	case AT_SKILL_SLOW:
	case AT_SKILL_FIREBALL:
    case AT_SKILL_JAVELIN:
		SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
		SetPlayerMagic(c);
		LetHeroStop();
		break;
    case AT_SKILL_DEATH_CANNON:
		SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
        SetAction ( o, PLAYER_ATTACK_DEATH_CANNON );
        SetAttackSpeed ();
		LetHeroStop();
		break;
	case AT_SKILL_BLAST_UP:
	case AT_SKILL_BLAST_UP+1:
	case AT_SKILL_BLAST_UP+2:
	case AT_SKILL_BLAST_UP+3:
	case AT_SKILL_BLAST_UP+4:
	case AT_SKILL_BLAST:
		{
			WORD TKey = 0xffff;
			if ( g_MovementSkill.m_iTarget!=-1 )
			{
				TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
			}
			SendRequestMagicContinue(Skill,(int)(c->TargetPosition[0]/100.f),(int)(c->TargetPosition[1]/100.f),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey,0);
		}
		SetPlayerMagic(c);
		LetHeroStop();
		break;
	}
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

void UseSkillElf( CHARACTER *c, OBJECT *o)
{
	LetHeroStop();
	int Skill = CharacterAttribute->Skill[g_MovementSkill.m_iSkill];
	
	VectorCopy(CharactersClient[g_MovementSkill.m_iTarget].Object.Position,c->TargetPosition);
	o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
	switch(Skill)
	{
	case AT_SKILL_HEAL_UP:
	case AT_SKILL_HEAL_UP+1:
	case AT_SKILL_HEAL_UP+2:
	case AT_SKILL_HEAL_UP+3:
	case AT_SKILL_HEAL_UP+4:
	case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	case AT_SKILL_RECOVER:
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
//#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
//	case AT_SKILL_MULTI_SHOT:
//#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEFENSE:
		SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
		SetPlayerMagic(c);
		break;
		
    case AT_SKILL_PARALYZE:
		{
#ifdef PSW_FRUIT_ITEM_CHECK_SKILL
			WORD Dexterity;
			const WORD notDexterity = 646;
			Dexterity = CharacterAttribute->Dexterity + CharacterAttribute->AddDexterity;
			if( Dexterity < notDexterity )
			{
				break;
			}
#endif //PSW_FRUIT_ITEM_CHECK_SKILL
			if(!CheckArrow()) 
				break;
			SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
			SetPlayerAttack(c);
		}
        break;
		
    case AT_SKILL_DEEPIMPACT:
		if ( !CheckArrow() ) 
			break;
		SendRequestMagic ( Skill, CharactersClient[g_MovementSkill.m_iTarget].Key );
		SetPlayerHighBowAttack ( c );
        break;
	}
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

void UseSkillSummon(CHARACTER* pCha, OBJECT* pObj)
{
	int iSkill = CharacterAttribute->Skill[g_MovementSkill.m_iSkill];
	
	switch(iSkill)
	{
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_DRAINLIFE_UP:
		case AT_SKILL_ALICE_DRAINLIFE_UP+1:
		case AT_SKILL_ALICE_DRAINLIFE_UP+2:
		case AT_SKILL_ALICE_DRAINLIFE_UP+3:
		case AT_SKILL_ALICE_DRAINLIFE_UP+4:
#endif
	case AT_SKILL_ALICE_DRAINLIFE:	
	case AT_SKILL_ALICE_LIGHTNINGORB:
		{
			LetHeroStop();
			if(iSkill == AT_SKILL_ALICE_DRAINLIFE 
#ifdef PJH_ADD_MASTERSKILL
			|| (AT_SKILL_ALICE_DRAINLIFE_UP <= iSkill && iSkill <= AT_SKILL_ALICE_DRAINLIFE_UP+4)
#endif
				)
			{
				switch(pCha->Helper.Type)
				{
				case MODEL_HELPER+2:	// ���ϸ���
					SetAction(pObj, PLAYER_SKILL_DRAIN_LIFE_UNI);
					break;
				case MODEL_HELPER+3:	// ����Ʈ
					SetAction(pObj, PLAYER_SKILL_DRAIN_LIFE_DINO);
					break;
				case MODEL_HELPER+37:	// �渱	
					SetAction(pObj, PLAYER_SKILL_DRAIN_LIFE_FENRIR);
					break;
				default:	// �⺻
					SetAction(pObj, PLAYER_SKILL_DRAIN_LIFE);
					break;
				}
			}
			else if(iSkill == AT_SKILL_ALICE_LIGHTNINGORB)
			{
				switch(pCha->Helper.Type)
				{
				case MODEL_HELPER+2:	// ���ϸ���
					SetAction(pObj, PLAYER_SKILL_LIGHTNING_ORB_UNI);
					break;
				case MODEL_HELPER+3:	// ����Ʈ
					SetAction(pObj, PLAYER_SKILL_LIGHTNING_ORB_DINO);
					break;
				case MODEL_HELPER+37:	// �渱	
					SetAction(pObj, PLAYER_SKILL_LIGHTNING_ORB_FENRIR);
					break;
				default:	// �⺻
					SetAction(pObj, PLAYER_SKILL_LIGHTNING_ORB);
					break;
				}	
			}
			
			WORD wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;			
			
			SendRequestMagicContinue( iSkill, (int)(pCha->TargetPosition[0]/100.f),
				(int)(pCha->TargetPosition[1]/100.f),
				(BYTE)(pObj->Angle[2]/360.f*256.f), 
				0, 0, wTargetKey,0);
		}
		break;
		// ChainLighting
#ifdef PJH_ADD_MASTERSKILL
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+1:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+2:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+3:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+4:
#endif
	case AT_SKILL_ALICE_CHAINLIGHTNING:
		{
			LetHeroStop();
			
			switch(pCha->Helper.Type)
			{
			case MODEL_HELPER+2:	// ���ϸ���
				SetAction(pObj, PLAYER_SKILL_CHAIN_LIGHTNING_UNI);
				break;
			case MODEL_HELPER+3:	// ����Ʈ
				SetAction(pObj, PLAYER_SKILL_CHAIN_LIGHTNING_DINO);
				break;
			case MODEL_HELPER+37:	// �渱	
				SetAction(pObj, PLAYER_SKILL_CHAIN_LIGHTNING_FENRIR);
				break;
			default:	// �⺻
				SetAction(pObj, PLAYER_SKILL_CHAIN_LIGHTNING);
				break;
			}	
			
			WORD wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			
			SendRequestMagicContinue( iSkill, (int)(pCha->TargetPosition[0]/100.f),
				(int)(pCha->TargetPosition[1]/100.f),
				(BYTE)(pObj->Angle[2]/360.f*256.f),
				0, 0, wTargetKey,0);
			
			
		}
		break;
	case AT_SKILL_ALICE_SLEEP:
	case AT_SKILL_ALICE_BLIND:
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_SLEEP_UP:
		case AT_SKILL_ALICE_SLEEP_UP+1:
		case AT_SKILL_ALICE_SLEEP_UP+2:
		case AT_SKILL_ALICE_SLEEP_UP+3:
		case AT_SKILL_ALICE_SLEEP_UP+4:
#endif
	case AT_SKILL_ALICE_THORNS:	
		{
			LetHeroStop();
			
			VectorCopy(CharactersClient[g_MovementSkill.m_iTarget].Object.Position, pCha->TargetPosition);
			pObj->Angle[2] = CreateAngle(pObj->Position[0], pObj->Position[1], pCha->TargetPosition[0], pCha->TargetPosition[1]);
			
			WORD wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			SendRequestMagic(iSkill, wTargetKey);
		}
		break;
#ifdef ASG_ADD_SKILL_BERSERKER
	case AT_SKILL_ALICE_BERSERKER:
		LetHeroStop();
		// ���� ����
		switch(pCha->Helper.Type)
		{
		case MODEL_HELPER+2:	// ���ϸ���
			SetAction(pObj, PLAYER_SKILL_SLEEP_UNI);
			break;
		case MODEL_HELPER+3:	// ����Ʈ
			SetAction(pObj, PLAYER_SKILL_SLEEP_DINO);
			break;
		case MODEL_HELPER+37:	// �渱	
			SetAction(pObj, PLAYER_SKILL_SLEEP_FENRIR);
			break;
		default:	// �⺻
			SetAction(pObj, PLAYER_SKILL_SLEEP);
			break;
		}
		SendRequestMagic(iSkill, HeroKey);
		break;
#endif	// ASG_ADD_SKILL_BERSERKER
		case AT_SKILL_ALICE_WEAKNESS:
		case AT_SKILL_ALICE_ENERVATION:
			LetHeroStop();
			SendRequestMagicContinue(iSkill, pCha->PositionX, pCha->PositionY,
				(BYTE)(pObj->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
			// ���� ����
			switch(pCha->Helper.Type)
			{
			case MODEL_HELPER+2:	// ���ϸ���
				SetAction(pObj, PLAYER_SKILL_SLEEP_UNI);
				break;
			case MODEL_HELPER+3:	// ����Ʈ
				SetAction(pObj, PLAYER_SKILL_SLEEP_DINO);
				break;
			case MODEL_HELPER+37:	// �渱	
				SetAction(pObj, PLAYER_SKILL_SLEEP_FENRIR);
				break;
			default:	// �⺻
				SetAction(pObj, PLAYER_SKILL_SLEEP);
				break;
			}
			break;
	}
}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
// ������ ������ ��ų����
void UseSkillRagefighter(CHARACTER* pCha, OBJECT* pObj)
{
	int iSkill = g_MovementSkill.m_bMagic ? CharacterAttribute->Skill[g_MovementSkill.m_iSkill] : g_MovementSkill.m_iSkill;
	
	ITEM* pLeftRing = &CharacterMachine->Equipment[EQUIPMENT_RING_LEFT];
	ITEM* pRightRing = &CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT];

	if(g_CMonkSystem.IsChangeringNotUseSkill(pLeftRing->Type, pRightRing->Type, pLeftRing->Level, pRightRing->Level))
		return;

	if(g_CMonkSystem.IsRideNotUseSkill(iSkill, pCha->Helper.Type))
		return;

	if(!g_CMonkSystem.IsSwordformGlovesUseSkill(iSkill))
		return;

	LetHeroStop();
	pCha->Movement = false;

	if(pObj->Type == MODEL_PLAYER)
	{
		g_CMonkSystem.SetRageSkillAni(iSkill, pObj);
		SetAttackSpeed();
	}

	switch(iSkill)
	{
	case AT_SKILL_THRUST:
	case AT_SKILL_OCCUPY:
		{
			WORD wTargetKey = 0;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}
			VectorCopy(CharactersClient[g_MovementSkill.m_iTarget].Object.Position, pCha->TargetPosition);
			pObj->Angle[2] = CreateAngle(pObj->Position[0], pObj->Position[1], pCha->TargetPosition[0], pCha->TargetPosition[1]);
			SendRequestMagic(iSkill, wTargetKey);
			
			BYTE TargetPosX = (BYTE)(pCha->TargetPosition[0]/TERRAIN_SCALE);
			BYTE TargetPosY = (BYTE)(pCha->TargetPosition[1]/TERRAIN_SCALE);
			
			if ((InBloodCastle()) || iSkill==AT_SKILL_OCCUPY 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==277 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==283 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==278 
				|| CharactersClient[g_MovementSkill.m_iTarget].MonsterIndex==288)
			{
				int angle = abs( (int)(pObj->Angle[2]/45.f) );
				switch(angle)
				{
				case 0: TargetPosY++;break;
				case 1: TargetPosX--; TargetPosY++; break;
				case 2: TargetPosX--; break;
				case 3: TargetPosX--; TargetPosY--; break;
				case 4: TargetPosY--; break;
				case 5: TargetPosX++; TargetPosY--; break;
				case 6: TargetPosX++; break;
				case 7: TargetPosX++; TargetPosY++; break;
				}
			}

			int TargetIndex = TERRAIN_INDEX(TargetPosX, TargetPosY);

			vec3_t vDis;
			Vector(0.0f, 0.0f, 0.0f, vDis);
			VectorSubtract(pCha->TargetPosition, pCha->Object.Position, vDis);
			VectorNormalize(vDis);
			VectorScale(vDis, TERRAIN_SCALE, vDis);
			VectorSubtract(pCha->TargetPosition, vDis, vDis);
			BYTE CharPosX = (BYTE)(vDis[0]/TERRAIN_SCALE);
			BYTE CharPosY = (BYTE)(vDis[1]/TERRAIN_SCALE);

		//	if(!InChaosCastle())
			{
				if((TerrainWall[TargetIndex]&TW_NOMOVE) != TW_NOMOVE && (TerrainWall[TargetIndex]&TW_NOGROUND) != TW_NOGROUND)
					SendPosition(CharPosX, CharPosY);
			}
			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_STAMP:
		{
			WORD wTargetKey = 0;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}

			SendRequestRageAtt(iSkill, wTargetKey);

			g_CMonkSystem.InitConsecutiveState(3.0f, 7.0f);
		}
		break;
	case AT_SKILL_GIANTSWING:
		{
			WORD wTargetKey = 0;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}
			// ĳ������ ��ų ��뿩���� �˸��� ����
			SendRequestRageAtt(iSkill, wTargetKey);

			g_CMonkSystem.InitConsecutiveState(3.0f, 12.0f);

			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_DRAGON_KICK:
		{
			// ĳ������ ��ų ��뿩���� �˸��� ����
			WORD wTargetKey = 0;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}
			SendRequestRageAtt(iSkill, wTargetKey);

			g_CMonkSystem.InitConsecutiveState(3.0f);

			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_DARKSIDE:
		{
			WORD wTargetKey = 0;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				wTargetKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}
			
			// ĳ���� pk�� target �ʿ�
			SendRequestDarkside((WORD)iSkill, wTargetKey);

			SendRequestRageAtt(iSkill, wTargetKey);

			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_DRAGON_LOWER:
		{
			BYTE angle = (BYTE)((((pObj->Angle[2]+180.f)/360.f)*255.f));
			WORD TKey = 0xffff;
			if(g_MovementSkill.m_iTarget!=-1)
			{
				TKey = CharactersClient[g_MovementSkill.m_iTarget].Key;
			}
			BYTE byValue = GetDestValue((pCha->PositionX), (pCha->PositionY), TargetX, TargetY);
			SendRequestMagicContinue(iSkill, pCha->PositionX, pCha->PositionY, ((pObj->Angle[2]/360.f)*255), byValue, angle, TKey, 0);

			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_ATT_UP_OURFORCES:
	case AT_SKILL_HP_UP_OURFORCES:
	case AT_SKILL_DEF_UP_OURFORCES:
		{
			SendRequestMagic(iSkill, HeroKey);
			if(rand()%2==0)
			{
				SetAction(pObj, PLAYER_SKILL_ATT_UP_OURFORCES);
				PlayBuffer(SOUND_RAGESKILL_BUFF_1);
			}
			else
			{
				SetAction(pObj, PLAYER_SKILL_HP_UP_OURFORCES);
				PlayBuffer(SOUND_RAGESKILL_BUFF_2);
			}
			g_CMonkSystem.RageCreateEffect(pObj, iSkill);
		}
		break;
	case AT_SKILL_PLASMA_STORM_FENRIR:
		{
			pObj->Angle[2] = CreateAngle(pObj->Position[0],pObj->Position[1],pCha->TargetPosition[0],pCha->TargetPosition[1]);
			
			CheckSkillDelay(Hero->CurrentSkill);

			BYTE pos = CalcTargetPos(pObj->Position[0], pObj->Position[1], pCha->TargetPosition[0],pCha->TargetPosition[1]);
			WORD TKey = 0xffff;
			TKey = getTargetCharacterKey(pCha, g_MovementSkill.m_iTarget);
			pCha->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
			SendRequestMagicContinue(iSkill,(pCha->PositionX), (pCha->PositionY),(BYTE)(pObj->Angle[2]/360.f*256.f), 0, pos, TKey, &pObj->m_bySkillSerialNum);
			pCha->Movement = 0;
			
			if(pObj->Type == MODEL_PLAYER)
			{
				SetAction_Fenrir_Skill(pCha, pObj);
			}
		}
		break;
	default:
		break;
	}
}

void AttackRagefighter(CHARACTER *pCha, int nSkill, float fDistance)
{
	OBJECT *pObj = &pCha->Object;

	int iMana, iSkillMana;
	GetSkillInformation(nSkill, 1, NULL, &iMana, NULL, &iSkillMana);
	
	if(CharacterAttribute->Mana < iMana)
	{
		int Index = g_pMyInventory->FindManaItemIndex();
		
		if(Index != -1)
			SendRequestUse(Index, 0);

		return;
	}

	if(iSkillMana > CharacterAttribute->SkillMana)
		return;

	if(!CheckSkillDelay(Hero->CurrentSkill))
        return;
					
	bool bSuccess = CheckTarget(pCha);
	bool bCheckAttack = CheckAttack();
	g_MovementSkill.m_bMagic = TRUE;
	g_MovementSkill.m_iSkill = Hero->CurrentSkill;
	
	if(bCheckAttack)
		g_MovementSkill.m_iTarget = SelectedCharacter;
	else
		g_MovementSkill.m_iTarget = -1;

	if(bSuccess)
	{
		switch(nSkill)
		{
		case AT_SKILL_THRUST:
		case AT_SKILL_STAMP:
		case AT_SKILL_GIANTSWING:
		case AT_SKILL_DRAGON_KICK:
		case AT_SKILL_DRAGON_LOWER:
		case AT_SKILL_OCCUPY:
			{
				if(SelectedCharacter<=-1) 
					return;

				fDistance = GetSkillDistance(nSkill, pCha)*1.2f;

				pCha->TargetCharacter = SelectedCharacter;
				if(CharactersClient[SelectedCharacter].Dead==0)
				{	
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					
					if(bCheckAttack)
					{
						if(CheckTile(pCha, pObj, fDistance) && pCha->SafeZone == false)
						{
							bool bNoneWall = CheckWall((pCha->PositionX), (pCha->PositionY), TargetX, TargetY);
							if(bNoneWall)
								UseSkillRagefighter(pCha, pObj);
						}
						else
						{	// �־������� �� �ȱ�
							if(PathFinding2(pCha->PositionX, pCha->PositionY, TargetX, TargetY, &pCha->Path, fDistance))
							{
								pCha->Movement = true;
 								pCha->MovementType = MOVEMENT_SKILL;
 								SendMove(pCha, pObj);
							}
						}
					}
				}
			}
			break;
		case AT_SKILL_DARKSIDE:
			UseSkillRagefighter(pCha, pObj);
			break;
		case AT_SKILL_ATT_UP_OURFORCES:
		case AT_SKILL_HP_UP_OURFORCES:
		case AT_SKILL_DEF_UP_OURFORCES:
			UseSkillRagefighter(pCha, pObj);
			break;
		case AT_SKILL_PLASMA_STORM_FENRIR:
			{
				if(InChaosCastle())
					break;

				int nTargetX = (int)(pCha->TargetPosition[0]/TERRAIN_SCALE);
				int nTargetY = (int)(pCha->TargetPosition[1]/TERRAIN_SCALE);
				if(CheckTile(pCha, pObj, fDistance))
				{
					if(g_MovementSkill.m_iTarget != -1)
					{
						UseSkillRagefighter(pCha, pObj);
					}
					else
					{
						pCha->m_iFenrirSkillTarget = -1;
					}
				}
				else
				{
					if(g_MovementSkill.m_iTarget != -1)
					{
						if(PathFinding2(pCha->PositionX, pCha->PositionY, nTargetX, nTargetY, &pCha->Path, fDistance*1.2f))
						{	// �ָ� �ɾ�� ���
							pCha->Movement = true;
						}
					}
					else
					{
						Attacking = -1;
					}
				}
			}
			break;
		}
	}
}

bool UseSkillRagePosition(CHARACTER* pCha)
{
	OBJECT *pObj = &pCha->Object;

	if(pObj->CurrentAction == PLAYER_SKILL_GIANTSWING || pObj->CurrentAction == PLAYER_SKILL_STAMP || pObj->CurrentAction == PLAYER_SKILL_DRAGONKICK)
	{
		if(g_CMonkSystem.IsConsecutiveAtt(pObj->AnimationFrame))
		{
			int iSkill = g_MovementSkill.m_bMagic ? CharacterAttribute->Skill[g_MovementSkill.m_iSkill] : g_MovementSkill.m_iSkill;
			return g_CMonkSystem.SendAttackPacket(pCha, g_MovementSkill.m_iTarget, iSkill);
		}

		if(pObj->CurrentAction == PLAYER_SKILL_STAMP && pObj->AnimationFrame >= 2.0f)
		{
			pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
			g_CMonkSystem.RageCreateEffect(pObj, AT_SKILL_STAMP);
		}
	}
	else if(pObj->CurrentAction == PLAYER_SKILL_DARKSIDE_READY)
	{
		int AttTime = (int)(2.5f/Models[pObj->Type].Actions[PLAYER_SKILL_DARKSIDE_READY].PlaySpeed);
		if(pCha->AttackTime	>= AttTime)
		{
			if(g_CMonkSystem.SendDarksideAtt(pObj))
			{
				pCha->AttackTime = 1;
				return true;
			}
		}
		return false;
	}
	else if(pObj->CurrentAction == PLAYER_SKILL_THRUST)
	{
		pObj->Angle[2] = CreateAngle(pObj->Position[0], pObj->Position[1], pCha->TargetPosition[0], pCha->TargetPosition[1]);
		pObj->m_sTargetIndex = g_MovementSkill.m_iTarget;
	}
	else
	{
		g_CMonkSystem.InitConsecutiveState();
		g_CMonkSystem.InitEffectOnce();
	}
	return false;
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

///////////////////////////////////////////////////////////////////////////////
// ����Ű�� ���ǵ� ������ ���.
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// ȭ�� �ڵ� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReloadArrow()
{
    int Index = SearchArrow();
	
	if ( Index!=-1 )
    {
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
		ITEM* rp = NULL;
		ITEM* lp = NULL;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
        ITEM* rp;
        ITEM* lp;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
        bool Success = false;
		
		if ( GetBaseClass(CharacterAttribute->Class)==CLASS_ELF && SEASON3B::CNewUIInventoryCtrl::GetPickedItem() == NULL )
		{
			rp = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT];
			lp = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT];
			Success = true;
		}
			
		if ( Success )
		{
			//  Ȱ.
#ifdef ADD_SOCKET_ITEM
			if( (GetEquipedBowType( lp ) == BOWTYPE_BOW) && (rp->Type == -1) )
#else //ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
				if ( ( (lp->Type >= ITEM_BOW && lp->Type < ITEM_BOW+7) 
					|| lp->Type == ITEM_BOW+17 
					|| lp->Type == ITEM_BOW+20
					|| lp->Type == ITEM_BOW+21 
					|| lp->Type == ITEM_BOW+22 ) 
					&& rp->Type == -1 )
#endif // ADD_SOCKET_ITEM			// ������ �� ������ �ϴ� �ҽ�
				{
					ITEM* pItem = g_pMyInventory->FindItem(Index);
					SEASON3B::CNewUIInventoryCtrl::CreatePickedItem(g_pMyInventory->GetInventoryCtrl(), pItem);
					if(pItem)
					{
						SendRequestEquipmentItem(REQUEST_EQUIPMENT_INVENTORY, Index+MAX_EQUIPMENT, pItem, REQUEST_EQUIPMENT_INVENTORY, EQUIPMENT_WEAPON_RIGHT);	
					}
					g_pMyInventory->DeleteItem(Index);
					
					// 250 "ȭ������ ��ü�Ͽ����ϴ�."
					g_pChatListBox->AddText("", GlobalText[250], SEASON3B::TYPE_SYSTEM_MESSAGE);	
				}
				else // ����.
#ifdef ADD_SOCKET_ITEM
					if( (GetEquipedBowType( rp ) == BOWTYPE_CROSSBOW) && (lp->Type == -1) )
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
					if ( ( rp->Type>=ITEM_BOW+8 && rp->Type<ITEM_BOW+15 ) ||                             
						( rp->Type>=ITEM_BOW+16 && rp->Type<ITEM_BOW+MAX_ITEM_INDEX ) && lp->Type==-1)
#endif // ADD_SOCKET_ITEM	
				{
					ITEM* pItem = g_pMyInventory->FindItem(Index);
					SEASON3B::CNewUIInventoryCtrl::CreatePickedItem(g_pMyInventory->GetInventoryCtrl(), pItem);
					if(pItem)
					{
						SendRequestEquipmentItem(REQUEST_EQUIPMENT_INVENTORY, Index+MAX_EQUIPMENT, pItem, REQUEST_EQUIPMENT_INVENTORY, EQUIPMENT_WEAPON_LEFT);	
					}
					g_pMyInventory->DeleteItem(Index);

					// 250 "ȭ������ ��ü�Ͽ����ϴ�."
					g_pChatListBox->AddText("", GlobalText[250], SEASON3B::TYPE_SYSTEM_MESSAGE);
				}
		}
    }
	else
	{
		if(g_pChatListBox->CheckChatRedundancy(GlobalText[251]) == FALSE)
		{
			// 251 "ȭ���� �����ϴ�."
			g_pChatListBox->AddText("", GlobalText[251], SEASON3B::TYPE_ERROR_MESSAGE);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ȭ���� �ִ��� Ȯ�� �� ������ ������
///////////////////////////////////////////////////////////////////////////////

bool CheckArrow()
{
	int Right = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
	int Left = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
	
#ifdef ADD_SOCKET_ITEM
	// ����
#ifdef KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	if( GetEquipedBowType( ) == BOWTYPE_CROSSBOW )
#else // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	if( GetEquipedBowType(&(CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT])) == BOWTYPE_CROSSBOW )
#endif // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	{
		if ( (Left!=ITEM_BOW+7) || (CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Durability <= 0) )
		{
			ReloadArrow ();
			return false;
		}
	}
	// Ȱ
#ifdef KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	else if( GetEquipedBowType( ) == BOWTYPE_BOW )
#else // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	else if( GetEquipedBowType(&(CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT])) == BOWTYPE_BOW )
#endif // KJH_FIX_RELOAD_ARROW_TO_CROSSBOW
	{
		if ( (Right!=ITEM_BOW+15) || (CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Durability <= 0) )
		{
			ReloadArrow ();
			return false;
		}
	}
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
    //  ����
	if( (Right >= ITEM_BOW+8 && Right < ITEM_BOW+15) 
		|| (Right >= ITEM_BOW+16&& Right < ITEM_BOW+17) 
		|| (Right >= ITEM_BOW+18&& Right < ITEM_BOW+MAX_ITEM_INDEX) )
	{
		if ( Left!=ITEM_BOW+7 || CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Durability<=0 )
		{
			ReloadArrow ();
			return false;
		}
	}
	
    //  Ȱ
	if ( Left>=ITEM_BOW && Left<ITEM_BOW+7 || Left==ITEM_BOW+17 || Left==ITEM_BOW+20
		|| Left == ITEM_BOW+21 || Left == ITEM_BOW+22 )
	{
		if ( Right!=ITEM_BOW+15 || CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Durability<=0 )
		{
			ReloadArrow ();
			return false;
		}
	}
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// ���� ��ų
///////////////////////////////////////////////////////////////////////////////

bool SkillElf(CHARACTER *c,ITEM *p)
{
    //  ���⿡ ������ ��ų.
	OBJECT *o = &c->Object;
	bool Success = false;
	for(int i=0;i<p->SpecialNum;i++)
	{
		int Spe_Num = p->Special[i];
		if(Spe_Num == AT_SKILL_CROSSBOW && (AT_SKILL_MANY_ARROW_UP <= CharacterAttribute->Skill[Hero->CurrentSkill] && CharacterAttribute->Skill[Hero->CurrentSkill] <= AT_SKILL_MANY_ARROW_UP+4))
			Spe_Num = CharacterAttribute->Skill[Hero->CurrentSkill];
		if(CharacterAttribute->Skill[Hero->CurrentSkill] == Spe_Num)
		{
			int iMana, iSkillMana;
			GetSkillInformation( Spe_Num, 1, NULL, &iMana, NULL, &iSkillMana);
			
			if( g_isCharacterBuff(o, eBuff_InfinityArrow) ) 
				iMana += CharacterMachine->InfinityArrowAdditionalMana;
			
			// �ٹ� ��ų �϶��� iMana�� 15�̴�.
			// ���� �ڱ��� ������ 15�� ��� 0�� �Ǵ� ���� �������� �Ծ����� ����
			// �������� �ٹ߸� ���Ĵ޶�� �䱸�Ͽ���! �ٸ� ��ų�� 15�� ��� 0�� �ǰ� 0�� ���� ���� ��� �Ծ���
			if(CharacterAttribute->Mana <= iMana)
			{
				int Index = g_pMyInventory->FindManaItemIndex();
				
				if(Index != -1)
				{
					SendRequestUse(Index, 0);
				}
				continue;
			}
			// skillmana ����
			if(iSkillMana > CharacterAttribute->SkillMana)
			{
				return ( FALSE);
			}
			if ( !CheckSkillDelay( Hero->CurrentSkill ) )
			{
				return false;
			}
			float Distance = GetSkillDistance( Spe_Num, c );
			switch(Spe_Num)
			{
			case AT_SKILL_MANY_ARROW_UP:
			case AT_SKILL_MANY_ARROW_UP+1:
			case AT_SKILL_MANY_ARROW_UP+2:
			case AT_SKILL_MANY_ARROW_UP+3:
			case AT_SKILL_MANY_ARROW_UP+4:
			case AT_SKILL_CROSSBOW:
				if(!CheckArrow())
				{
					i = p->SpecialNum;
					continue;
				}
				if( CheckTile( c, o, Distance ) )
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Spe_Num,( c->PositionX),
						( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, 0 );
					SetPlayerAttack(c);
					if(o->Type != MODEL_PLAYER && o->Kind!=KIND_PLAYER)
						CreateArrows(c,o,NULL,FindHotKey(( c->Skill)),1);
					Success = true;
				}
				break;
				
			case AT_SKILL_BLAST_CROSSBOW4:
				if(!CheckArrow())
				{
					i = p->SpecialNum;
					continue;
				}
				if( CheckTile( c, o, Distance ) )
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
					
					BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Spe_Num,( c->PositionX),
						( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
					SetPlayerAttack(c);
					if(o->Type != MODEL_PLAYER)
						CreateArrows(c,o,NULL,FindHotKey(( c->Skill)),Spe_Num-AT_SKILL_BLAST_CROSSBOW4+2);
					
					Success = true;
				}
				break;
			}
		}
	}
	return Success;
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// ������� ��ǲ�� ���� ���ΰ��� �׼��� ���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

int ItemKey = 0;
int ActionTarget = -1;

void Action(CHARACTER *c,OBJECT *o,bool Now)
{
	float Range = 1.8f;
	switch(c->MovementType)
	{
	case MOVEMENT_ATTACK:
		{
			// ���� Ÿ��
			int Right = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			int Left = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			
			// ������ ���Ⱑ â�̸�
			if(Right >= ITEM_SPEAR && Right < ITEM_SPEAR+MAX_ITEM_INDEX)
			{
				Range = 2.2f;
			}

#ifdef ADD_SOCKET_ITEM
			// Ȱ/���� �϶�
			if( GetEquipedBowType() != BOWTYPE_NONE )
			{
				Range = 6.f;
			}
#else // ADD_SOCKET_ITEM
			//����
			if( (Right>=ITEM_BOW+8  && Right<ITEM_BOW+15)	||
				(Right>=ITEM_BOW+16 && Right<ITEM_BOW+17 )	||
				(Right>=ITEM_BOW+18 && Right<ITEM_BOW+MAX_ITEM_INDEX )
				)
				Range = 6.f;
			//Ȱ
			if(Left>=ITEM_BOW && Left<ITEM_BOW+7 || Left==ITEM_BOW+17 || Left==ITEM_BOW+20
				|| Left == ITEM_BOW+21 || Left == ITEM_BOW+22 )
				Range = 6.f;
#endif // ADD_SOCKET_ITEM

#ifndef CSK_FIX_NORMALATTACK_CHECK		// ������ �� ������ �ϴ� �ҽ�	
			//�����ġ ����
			if(c->MonsterIndex == 9)
				Range = 7.f;
#endif //! CSK_FIX_NORMALATTACK_CHECK	// ������ �� ������ �ϴ� �ҽ�
			
			if(ActionTarget == -1) 
				return;

			if(o->Type == MODEL_PLAYER)
			{
				if( o->CurrentAction >= PLAYER_ATTACK_FIST && o->CurrentAction <= PLAYER_RIDE_SKILL 
#ifdef PBG_WOPS_DARKHOSE_ATTACK
					&& o->CurrentAction != PLAYER_STOP_RIDE_HORSE	// ��ũȣ��Ÿ�� ��������
					&& o->CurrentAction != PLAYER_STOP_TWO_HAND_SWORD_TWO	// ���� ������ ��հ� ���� ����
#endif	// PBG_WOPS_DARKHOSE_ATTACK
#ifdef PBG_FIX_FENRIR_GELENALATTACK
					&& o->CurrentAction == PLAYER_FENRIR_SKILL_ONE_RIGHT	// �渱Ÿ�� �Ϲݰ���
#endif //PBG_FIX_FENRIR_GELENALATTACK
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
					&& o->CurrentAction == PLAYER_RAGE_FENRIR_ONE_RIGHT
#endif //PBG_ADD_NEWCHAR_MONK_ANI
					)
					break;
			}
			else
			{
				if(o->CurrentAction>=MONSTER01_ATTACK1 && o->CurrentAction<=MONSTER01_ATTACK2) 
					break;
			}
			
			if ( ActionTarget<=-1 ) 
				break;
			
			TargetX = (int)(CharactersClient[ActionTarget].Object.Position[0]/TERRAIN_SCALE);
			TargetY = (int)(CharactersClient[ActionTarget].Object.Position[1]/TERRAIN_SCALE);

			if ( c->SafeZone)
			{
				break;
			}
			else if ( !CheckTile( c, o, Range))
			{
				if ( GetBaseClass(c->Class) == CLASS_ELF)
				{	
					// ���� Ȱ����� ��� �����Ÿ� ���̸� �ɾ�� �Ѵ�.
					if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Range))
					{
						c->Movement = true;
					}
				}
				break;
			}

#ifdef CSK_HACK_TEST
			static DWORD s_dwTime = 0;
			DWORD dwCurrentTime = timeGetTime();
			DWORD dwElpasedTime = dwCurrentTime - s_dwTime;
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_NORMAL, "gap time : %d", dwElpasedTime);
#endif // CONSOLE_DEBUG	
			s_dwTime = dwCurrentTime;
#endif // CSK_HACK_TEST
			
			MouseUpdateTime = MouseUpdateTimeMax;
			SetPlayerAttack(c);
			c->AttackTime = 1;
			VectorCopy(CharactersClient[ActionTarget].Object.Position,c->TargetPosition);
			o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
			LetHeroStop();
			c->Movement = false;
			BYTE PathX[1];
			BYTE PathY[1];
			PathX[0] = ( c->PositionX);
			PathY[0] = ( c->PositionY);
			c->TargetCharacter = ActionTarget;
			int Dir = ((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8);
			// ȸ���� ���� ���� �Ϲ� ���ݽÿ� �ܿ��� ������ �ʵ��� ��.
#ifdef LDS_FIX_WHENAFTERSKILL_WHEEL_STILLVISUAL_EFFECT		
			c->Skill = 0;
#endif //#ifdef LDS_FIX_WHENAFTERSKILL_WHEEL_STILLVISUAL_EFFECT
			SendRequestAttack(CharactersClient[ActionTarget].Key, Dir);
		}
		break;
	case MOVEMENT_SKILL:	// MOVEMENT_ATTACK �� ����ϰ� ��ų�� �� ����� (����� ����� ��쿡 ���� üũ ����!!)
		{
			int iSkill = ( g_MovementSkill.m_bMagic) ? ( CharacterAttribute->Skill[g_MovementSkill.m_iSkill]) : g_MovementSkill.m_iSkill;
			
            float Distance = GetSkillDistance ( iSkill, c );
			switch ( iSkill)
			{
			case AT_SKILL_SPEAR:
				if ( Hero->Helper.Type!=MODEL_HELPER+2 )
				{	// â ��ų�� ���ϸ� Ÿ�߸� �Ѵ�.
					break;
				}
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOW_UP:
			case AT_SKILL_BLOW_UP+1:
			case AT_SKILL_BLOW_UP+2:
			case AT_SKILL_BLOW_UP+3:
			case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ONETOONE:
			case AT_SKILL_RIDER:
			case AT_SKILL_SWORD1:	// ���� ��ų
			case AT_SKILL_SWORD2:
			case AT_SKILL_SWORD3:
			case AT_SKILL_SWORD4:
			case AT_SKILL_SWORD5:
			case AT_SKILL_STRONG_PIER:
			case AT_SKILL_FIRE_BUST_UP:
			case AT_SKILL_FIRE_BUST_UP+1:
			case AT_SKILL_FIRE_BUST_UP+2:
			case AT_SKILL_FIRE_BUST_UP+3:
			case AT_SKILL_FIRE_BUST_UP+4:
			case AT_SKILL_LONGPIER_ATTACK:
			case AT_SKILL_RUSH:
			case AT_SKILL_SPACE_SPLIT :     //  ���� ������.
			case AT_SKILL_ONEFLASH :        //  �ϼ�.
				if ( 0 == CharactersClient[g_MovementSkill.m_iTarget].Dead)
				{	// ���׾��� ���� ���
					if ( g_MovementSkill.m_iTarget<=-1 ) break;
					
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					if( CheckTile( c, o, Distance*1.2f ) && !c->SafeZone )
					{
						UseSkillWarrior( c, o);
					}
					else
					{
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance*1.2f))
						{	
							// �ָ� �ɾ�� ���
							c->Movement = true;
						}
					}
				}
				break;
			case AT_SKILL_POISON:	// ����� ��ų
			case AT_SKILL_METEO:
			case AT_SKILL_THUNDER:
			case AT_SKILL_ENERGYBALL:
			case AT_SKILL_POWERWAVE:
			case AT_SKILL_SLOW:
			case AT_SKILL_FIREBALL:
			case AT_SKILL_JAVELIN:
			case AT_SKILL_DEATH_CANNON:
				if ( 0 == CharactersClient[g_MovementSkill.m_iTarget].Dead)
				{	// ���׾��� ���� ���
					if ( g_MovementSkill.m_iTarget<=-1 ) break;
					
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					if( CheckTile( c, o, Distance ) && !c->SafeZone )
					{
						bool Wall = CheckWall(( c->PositionX),
							( c->PositionY),TargetX,TargetY);
						if(Wall)
						{
							UseSkillWizard( c, o);
						}
					}
					else
					{
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
						{	
							// �ָ� �ɾ�� ���
							c->Movement = true;
						}
					}
				}
				break;
			case AT_SKILL_DEEPIMPACT:
			case AT_SKILL_PARALYZE:
				if( 0 == CharactersClient[g_MovementSkill.m_iTarget].Dead )
				{	// ���׾��� ���� ���
					if ( g_MovementSkill.m_iTarget<=-1 ) break;
					
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					if( CheckTile( c, o, Distance ) && !c->SafeZone )
					{
						bool Wall = CheckWall(( c->PositionX),
							( c->PositionY),TargetX,TargetY);
						if(Wall)
						{
							UseSkillElf( c, o);
						}
					}
					else
					{	
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
						{	
							// �ָ� �ɾ�� ���
							c->Movement = true;
						}
					}
				}
				break;
			case AT_SKILL_HEAL_UP:
			case AT_SKILL_HEAL_UP+1:
			case AT_SKILL_HEAL_UP+2:
			case AT_SKILL_HEAL_UP+3:
			case AT_SKILL_HEAL_UP+4:
			case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ATT_POWER_UP:
			case AT_SKILL_ATT_POWER_UP+1:
			case AT_SKILL_ATT_POWER_UP+2:
			case AT_SKILL_ATT_POWER_UP+3:
			case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_DEF_POWER_UP:
			case AT_SKILL_DEF_POWER_UP+1:
			case AT_SKILL_DEF_POWER_UP+2:
			case AT_SKILL_DEF_POWER_UP+3:
			case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_DEFENSE:
				if ( 0 == CharactersClient[g_MovementSkill.m_iTarget].Dead)
				{	// ���׾��� ���� ���
					if ( g_MovementSkill.m_iTarget<=-1 ) break;
					
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					if ( CheckTile( c, o, Distance ) && !c->SafeZone)
					{
						bool Wall = CheckWall(( c->PositionX),
							( c->PositionY),TargetX,TargetY);
						if(Wall)
						{
							UseSkillElf( c, o);
						}
					}
					else
					{	
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
						{	
							// �ָ� �ɾ�� ���
							c->Movement = true;
						}
					}
				}
				break;
#ifdef CSK_FIX_DUEL_N_PK_SKILL
			case AT_SKILL_REDUCEDEFENSE:	// �������
				{
					AttackKnight(c, iSkill, Distance);
				}
				break;
#endif // CSK_FIX_DUEL_N_PK_SKILL
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			case AT_SKILL_THRUST:
			case AT_SKILL_STAMP:
			case AT_SKILL_GIANTSWING:
			case AT_SKILL_DRAGON_KICK:
			case AT_SKILL_DRAGON_LOWER:
			case AT_SKILL_OCCUPY:
				{
					if(CharactersClient[g_MovementSkill.m_iTarget].Dead == 0)
					{
						if ( g_MovementSkill.m_iTarget<=-1 ) break;

						TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
						TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
						if(CheckTile( c, o, Distance*1.2f ) && !c->SafeZone)
							UseSkillRagefighter(c, o);
						else
						{
							if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance*1.2f))
								c->Movement = true;
						}
					}
				}
				break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
			}
		}
		break;
	case MOVEMENT_GET:
        //  ������ space�� �ڵ� �Ա�.
		if ( !g_bAutoGetItem )
        {
			if(CheckTile(c,o,1.5f) == false) 
			{
				break;
			}
			MouseUpdateTimeMax = 6;
		}
		// �� �κ��丮 ��á���� üũ
		if (Items[ItemKey].Item.Type == ITEM_POTION+15)
		{
			SendRequestGetItem(ItemKey);	// ��
		}
		else if(g_pMyInventory->FindEmptySlot(&Items[ItemKey].Item) == -1)
		{
			unicode::t_char Text[256];
			// 375 "�κ��丮�� ��á���ϴ�."
			unicode::_sprintf(Text, GlobalText[375]);
			
			g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
			
			// ������ ƨ���
			OBJECT * pItem = &(Items[ItemKey].Object);
			pItem->Position[2] = RequestTerrainHeight(pItem->Position[0],pItem->Position[1]) + 3.f;
			pItem->Gravity     = 50.f;
		}
		else
		{
			SendRequestGetItem(ItemKey);
		}
		break;
	case MOVEMENT_TALK:
		MouseUpdateTimeMax = 12;
		
		if(!(
			M34CryWolf1st::Get_State_Only_Elf() == true && 
			M34CryWolf1st::IsCyrWolf1st() == true))
		{
			SetPlayerStop(c);
			c->Movement = false;
		}
		
		if(TargetNpc != -1)
		{
			int npcIndex = 229;
			
            npcIndex = 226;
			
#ifdef _PVP_MURDERER_HERO_ITEM
			npcIndex = 227;
#endif	// _PVP_MURDERER_HERO_ITEM
			
			npcIndex = 205;
			
			// LEM_TEST NPCŬ�� [lem_2010.9.7]
			if(CharactersClient[TargetNpc].MonsterIndex >= npcIndex )
			{
                //  ī���� ���.
				int level = CharacterAttribute->Level;
                if ( CharactersClient[TargetNpc].MonsterIndex==238 && level<10 )
                {
                    char Text[100];
                    sprintf ( Text, GlobalText[663], CHAOS_MIX_LEVEL );
					g_pChatListBox->AddText( "", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
                    break;
                }
                //  ������ ������ ���� ������ ( ����, ���� ����, �ѽ� )
                if(CharactersClient[TargetNpc].MonsterIndex==243 || 
					CharactersClient[TargetNpc].MonsterIndex==246 || 
					CharactersClient[TargetNpc].MonsterIndex==251 
					|| CharactersClient[TargetNpc].MonsterIndex == 416 // ����NPC ���� �������� 
#ifdef ASG_ADD_KARUTAN_NPC
					|| CharactersClient[TargetNpc].MonsterIndex == 578 // ������� ���� 
#endif	// ASG_ADD_KARUTAN_NPC
					)
                {
					g_pNPCShop->SetRepairShop(true);
                }
                else
                {
					g_pNPCShop->SetRepairShop(false);
                }
				
				if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYQUEST))
				{
					g_pNewUISystem->Hide(SEASON3B::INTERFACE_MYQUEST);
				}
				
                //  ����Ʈ ����Ʈ�� �ʱ�ȭ�ұ��?
                if ( g_csQuest.IsInit() )
                {
                    SendRequestQuestHistory ();
                }
				
				if(M34CryWolf1st::Get_State_Only_Elf() == true && M34CryWolf1st::IsCyrWolf1st() == true)
				{
					if(CharactersClient[TargetNpc].Object.Type >= MODEL_CRYWOLF_ALTAR1 && CharactersClient[TargetNpc].Object.Type <= MODEL_CRYWOLF_ALTAR5)
					{
						int Num = CharactersClient[TargetNpc].Object.Type - MODEL_CRYWOLF_ALTAR1;
						
						if ((GetBaseClass(Hero->Class)==CLASS_ELF) && M34CryWolf1st::Get_AltarState_State(Num) == false )
						{
							BYTE State = (m_AltarState[Num] & 0x0f);
							if(State > 0)
							{
								//								g_pCryWolfInterface->
								SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Get_Temple));
								//								M34CryWolf1st::Set_Message_Box(56,0,CharactersClient[TargetNpc].Key,Num);
								//								M34CryWolf1st::Set_Message_Box(57,1,CharactersClient[TargetNpc].Key);
							}
							else
								SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Destroy_Set_Temple));
							//								M34CryWolf1st::Set_Message_Box(53,0,0);	//"������ �ı��Ǿ� ���̻� ����� �Ұ����մϴ�."
						}
						else
							if ((GetBaseClass(Hero->Class)==CLASS_ELF) && M34CryWolf1st::Get_AltarState_State(Num) == true )
							{
								SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Ing_Set_Temple));
								//							M34CryWolf1st::Set_Message_Box(52,0,0);	//"����� ���� ���̹Ƿ� �ߺ� ����� �Ҽ� �����ϴ�."
							}
							else
								SendRequestTalk(CharactersClient[TargetNpc].Key);
					}
					else
						SendRequestTalk(CharactersClient[TargetNpc].Key);
				}
				else if(M34CryWolf1st::IsCyrWolf1st() == true)
				{
					if(!(CharactersClient[TargetNpc].Object.Type >= MODEL_CRYWOLF_ALTAR1 && CharactersClient[TargetNpc].Object.Type <= MODEL_CRYWOLF_ALTAR5))
					{
						if (MODEL_NPC_QUARREL == CharactersClient[TargetNpc].Object.Type)
						{
							SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CMapEnterWerwolfMsgBoxLayout));
						}
						SendRequestTalk(CharactersClient[TargetNpc].Key);
					}
				}
				else if (SEASON3A::CGM3rdChangeUp::Instance().IsBalgasBarrackMap())
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
					
					SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CMapEnterGateKeeperMsgBoxLayout));
				}
#ifdef PBG_ADD_LITTLESANTA_NPC
				else if(CharactersClient[TargetNpc].MonsterIndex >= 468 && CharactersClient[TargetNpc].MonsterIndex <= 475)
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
					
					char _Temp[32] = {0,};
					if(CharactersClient[TargetNpc].MonsterIndex == 470)
					{
						// 2596 "ü���� 100%ȸ�� �Ǿ����ϴ�."
						sprintf(_Temp, GlobalText[2596], 100);
						g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);
					}
					else if(CharactersClient[TargetNpc].MonsterIndex == 471)
					{
						// 2597 "������ 100%ȸ�� �Ǿ����ϴ�."
						sprintf(_Temp, GlobalText[2597], 100);
						g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);
					}
#ifdef CONSOLE_DEBUG
					//	g_ConsoleDebug->Write(MCD_ERROR, "Park Bo Guen TESTBUFF %d",CharactersClient[TargetNpc].Key);
#endif // CONSOLE_DEBUG
				}
#endif //PBG_ADD_LITTLESANTA_NPC
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
				else if(CharactersClient[TargetNpc].MonsterIndex == 478)
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
				}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_DOPPELGANGER_NPC
				else if(CharactersClient[TargetNpc].MonsterIndex == 540)	// �簡��
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
				}
#endif	// YDG_ADD_DOPPELGANGER_NPC
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
				else if(CharactersClient[TargetNpc].MonsterIndex == 547)	// �ٸ���
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
				}
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
				else if(CharactersClient[TargetNpc].MonsterIndex == 579)	// �ٸ���
				{
					SendRequestTalk(CharactersClient[TargetNpc].Key);
				}
				else
				{
					if(M38Kanturu2nd::Is_Kanturu2nd() == TRUE)
					{
						if(g_pKanturu2ndEnterNpc->IsNpcAnimation() == false)
						{
							SendRequestTalk(CharactersClient[TargetNpc].Key);
						}
					}
					else if( g_CursedTemple->IsCursedTemple())
					{
#ifdef YDG_FIX_CURSEDTEMPLE_GAUGEBAR_ERROR
						if (!g_CursedTemple->IsGaugebarEnabled())
						{
#ifdef LJH_FIX_CANNOT_CLICK_BASKETS_IN_CURSED_TEMPLE 
							// ������ Ŭ�� ���� ���� 
							if (CharactersClient[TargetNpc].MonsterIndex == 380 
								// ������ ������ ��� �ְ� �ڱ� ������ �������� Ŭ������  
								|| (g_pCursedTempleWindow->CheckInventoryHolyItem( Hero )
									&&   ((g_pCursedTempleWindow->GetMyTeam() == SEASON3A::eTeam_Allied	&& CharactersClient[TargetNpc].MonsterIndex == 383) 
									   || (g_pCursedTempleWindow->GetMyTeam() == SEASON3A::eTeam_Illusion && CharactersClient[TargetNpc].MonsterIndex == 384))
									 ))
#else  //LJH_FIX_CANNOT_CLICK_BASKETS_IN_CURSED_TEMPLE
							if(CharactersClient[TargetNpc].MonsterIndex == 380 ||
								((CharactersClient[TargetNpc].MonsterIndex == 383 || CharactersClient[TargetNpc].MonsterIndex == 384)
								&& g_pCursedTempleWindow->CheckInventoryHolyItem( Hero )) )
#endif //LJH_FIX_CANNOT_CLICK_BASKETS_IN_CURSED_TEMPLE
							{
								g_CursedTemple->SetGaugebarEnabled(true);
							}
#endif	// YDG_FIX_CURSEDTEMPLE_GAUGEBAR_ERROR
							// �ε��ٸ� ǥ�� �ؾ� �ϴ� ���Ǿ� �߰�.
							g_pCursedTempleWindow->CheckTalkProgressNpc(CharactersClient[TargetNpc].MonsterIndex, 
								CharactersClient[TargetNpc].Key);
#ifdef YDG_FIX_CURSEDTEMPLE_GAUGEBAR_ERROR
						}
#endif	// YDG_FIX_CURSEDTEMPLE_GAUGEBAR_ERROR

					}
					else
					{	
						SendRequestTalk(CharactersClient[TargetNpc].Key);
					}
				}
				//#else
				//				SendRequestTalk(CharactersClient[TargetNpc].Key);
				//#endif
				if(CharactersClient[TargetNpc].MonsterIndex == 229) // ���� �ɸ��� ���ý� ��(229) ��
					bCheckNPC = true;
				else
					bCheckNPC = false;
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
				if( CharactersClient[TargetNpc].MonsterIndex == 226 )	// ���û�
				{
					ITEM* pItem = NULL;
					
					// ��ũȣ���� �����Ǿ��ִٸ�
					pItem = &CharacterMachine->Equipment[EQUIPMENT_HELPER];
					if( pItem->Type == ITEM_HELPER+4 )
						SendRequestPetInfo( PET_TYPE_DARK_HORSE, 0, EQUIPMENT_HELPER );
					
					pItem = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT];
					// ��ũ���Ǹ��� �����Ǿ��ִٸ�
					if( pItem->Type == ITEM_HELPER+5 )
						SendRequestPetInfo( PET_TYPE_DARK_SPIRIT, 0, EQUIPMENT_WEAPON_LEFT );
				}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM													//## �ҽ����� �����.
#ifdef KJH_FIX_WOPS_K30120_RECORVERY_PET_LIFE
				if( CharactersClient[TargetNpc].MonsterIndex == 226 )	// ���û�
				{
					//  ��ũ���Ǹ������� ��û.
					SendRequestPetInfo ( PET_TYPE_DARK_SPIRIT, 0, EQUIPMENT_WEAPON_LEFT );
					//  ��ũȣ�� ������ ��û.
					SendRequestPetInfo ( PET_TYPE_DARK_HORSE, 0, EQUIPMENT_HELPER );
				}
#endif // KJH_FIX_WOPS_K30120_RECORVERY_PET_LIFE
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM													//## �ҽ����� �����.
				
			}
			TargetNpc = -1;
		}
		break;
	case MOVEMENT_OPERATE:
		if(max(abs(( Hero->PositionX)-TargetX),abs(( Hero->PositionY)-TargetY))<=1)
		{
			bool Healing = false;
			bool Pose = false;
			bool Sit = false;
			if(World==WD_0LORENCIA)
			{
				switch(TargetType)
				{
				case MODEL_POSE_BOX:Pose = true;Hero->Object.Angle[2] = TargetAngle;break;
				case MODEL_TREE01+6:Sit = true;break;
				case MODEL_FURNITURE01+5:Sit = true;Hero->Object.Angle[2] = TargetAngle;break;
				case MODEL_FURNITURE01+6:Sit = true;break;
					break;
				}
			}
			else if(World==WD_1DUNGEON)
			{
				switch(TargetType)
				{
				case 60:Pose = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 59:Sit = true;break;
				}
			}
			else if(World==WD_2DEVIAS)
			{
				switch(TargetType)
				{
				case 91:Pose = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 22:Sit = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 25:Sit = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 40:Sit = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 45:Sit = true;break;
				case 55:Sit = true;Hero->Object.Angle[2] = TargetAngle;break;
				case 73:Sit = true;break;
				}
			}
			else if(World==WD_3NORIA)
			{
				switch(TargetType)
				{
				case 8:Sit = true;break;
				case 38:Healing = true;Hero->Object.Angle[2] = TargetAngle;break;
				}
			}
			else if(World==WD_7ATLANSE)
			{
				switch(TargetType)
				{
				case 39:Pose = true;Hero->Object.Angle[2] = TargetAngle;break;
				}
			}
			else if(World==WD_8TARKAN)
			{
				switch(TargetType)
				{
				case 78:Sit = true;break;
				}
			}
			else if ( battleCastle::InBattleCastle() )
			{
				if ( TargetType==77 )   //  �հ����� ����.
				{
					if ( battleCastle::GetGuildMaster( Hero ) )
					{
						Sit = true;
						Hero->Object.Angle[2] = TargetAngle;
					}
				}
				else if ( TargetType==84 )
				{
					Sit = true;
					Hero->Object.Angle[2] = TargetAngle;
				}
			}
			else if(M38Kanturu2nd::Is_Kanturu2nd())
			{
				if(TargetType == 3)
				{
					Sit = true;
				}
			}
			else if(World == WD_51HOME_6TH_CHAR)
			{
				switch(TargetType)
				{
				case 103:	// ���� ����
					{
						Sit = true;
						Hero->Object.Angle[2] = TargetAngle;
					}
					break;
				}
			}
#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
			else if(World == WD_79UNITEDMARKETPLACE)
			{
				switch(TargetType)
				{
				case 67:	// ���� �ڽ�
					{
						Pose = true;
						Hero->Object.Angle[2] = TargetAngle;
					}
					break;
				}
			}
#endif // LDS_ADD_MAP_UNITEDMARKETPLACE
			if(Healing)
			{
				if(!IsFemale(c->Class))
					SetAction(o,PLAYER_HEALING1);
				else
					SetAction(o,PLAYER_HEALING_FEMALE1);
				SendRequestAction(AT_HEALING1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
			}
			else
			{
				BYTE PathX[1];
				BYTE PathY[1];
				PathX[0] = TargetX;
				PathY[0] = TargetY;
				SendCharacterMove(Hero->Key,Hero->Object.Angle[2],1,PathX,PathY,TargetX,TargetY);
				c->Path.PathNum = 0;
				if(Pose)
				{
					if(!IsFemale(c->Class))
						SetAction(o,PLAYER_POSE1);
					else
						SetAction(o,PLAYER_POSE_FEMALE1);
					SendRequestAction(AT_POSE1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				}
				if(Sit)
				{
					//������ �����ϸ� ���� Ż�͵��� ���� �� ���� ���ϰ� �Ѵ�. 
					if((!c->SafeZone) && (c->Helper.Type == MODEL_HELPER+37 || c->Helper.Type == MODEL_HELPER+2 
						|| c->Helper.Type == MODEL_HELPER+3 || c->Helper.Type == MODEL_HELPER+4))
						return;
					
					if(!IsFemale(c->Class))
						SetAction(o,PLAYER_SIT1);
					else
						SetAction(o,PLAYER_SIT_FEMALE1);
					SendRequestAction(AT_SIT1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				}
				PlayBuffer(SOUND_DROP_ITEM01,&Hero->Object);
			}
			}
			break;
	}
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// ���콺 Ŭ���� ���ΰ��� �̵��ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void CloseNPCGMWindow()
{
	if( !g_pUIManager->IsOpen(INTERFACE_NPCGUILDMASTER) )
		return;
	g_pUIManager->Close( INTERFACE_NPCGUILDMASTER );
}

void SendMove(CHARACTER *c,OBJECT *o)
{
	if(g_pNewUISystem->IsImpossibleSendMoveInterface() == true)
	{
		return;
	}
	
	if( g_isCharacterBuff(o, eDeBuff_Harden) ) 
	{
		return;
	}
	if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint) )
	{
		return;
	}
	
#ifdef _PVP_ADD_MOVE_SCROLL
	if (!g_MurdererMove.CanWalk()) return;
#endif	// _PVP_ADD_MOVE_SCROLL
	
	if(c->Path.PathNum <= 2)
	{
		MouseUpdateTimeMax = 0;
	}
	else if(c->Path.PathNum == 3)
	{
		MouseUpdateTimeMax = 5;
	}
	else
	{
		MouseUpdateTimeMax = 10+(c->Path.PathNum-2)*3;
	}
	SendCharacterMove(Hero->Key,o->Angle[2],c->Path.PathNum,&c->Path.PathX[0],&c->Path.PathY[0],TargetX,TargetY);
	
	c->Movement = true;
	
	g_pNewUISystem->UpdateSendMoveInterface();
	
	if( g_bEventChipDialogEnable )
	{
        SendRequestEventChipExit ();
		
#ifdef SCRATCH_TICKET
		if ( g_bEventChipDialogEnable==EVENT_SCRATCH_TICKET )
		{
			ClearInput(FALSE);
			InputEnable		= false;
			GoldInputEnable = false;
			InputGold		= 0;
			StorageGoldFlag = 0;
			g_bScratchTicket= false;
		}
#endif
        g_bEventChipDialogEnable  = EVENT_NONE;
		
        //  ���콺...
#ifndef FOR_WORK		// â��忡�� ���콺 ��ġ �ٲ�°� ���ҽ��ϴ�.
#ifdef WINDOWMODE
		if (g_bUseWindowMode == FALSE)
		{
#endif	// WINDOWMODE
			int x = 640*MouseX/260;
			SetCursorPos((x)*WindowWidth/640,(MouseY)*WindowHeight/480);
#ifdef WINDOWMODE
		}
#endif	// WINDOWMODE
#endif	// FOR_WORK
		MouseUpdateTimeMax = 6;
        MouseLButton = false;
	}
}

int StandTime = 0;
int HeroAngle = 0;


///////////////////////////////////////////////////////////////////////////////
// ���ѵǴ� ��ũ�� �˻�.
///////////////////////////////////////////////////////////////////////////////

bool CheckMacroLimit ( char* Text )
{
    char string[256];
    int  length;
	
    memcpy( string, Text+3, sizeof( char )*(256-2));
    //  �ŷ�.
    length = strlen(GlobalText[258]);
    if( strcmp( string, GlobalText[258] )==0 || strcmp( string, GlobalText[259] )==0 || stricmp( string, "/trade" )==0 )
    {
        return  true;
    }
    //  ��Ƽ.
    if( strcmp( string, GlobalText[256] )==0 || stricmp( string, "/party" )==0 || stricmp( string, "/pt" )==0 )
    {
        return  true;
    }
    //  ���.
	if( strcmp( string, GlobalText[254] )==0 || stricmp( string, "/guild" )==0 )
    {
        return  true;
    }
    //  ����.
	if( strcmp( string, GlobalText[248] )==0 || stricmp( string, "/GuildWar" )==0 )
    {
        return  true;
    }
    //  �����౸.
	if( strcmp( string, GlobalText[249] )==0 || stricmp( string, "/BattleSoccer" )==0 )
    {
        return  true;
    }
	
    return  false;
}

///////////////////////////////////////////////////////////////////////////////
// ��ɾ� üũ�ϴ� �Լ�(�ŷ�, ��Ƽ, ��� ���)
///////////////////////////////////////////////////////////////////////////////

bool CheckCommand(char *Text, bool bMacroText )
{
#ifdef CSK_LH_DEBUG_CONSOLE
	if(g_ConsoleDebug->CheckCommand(Text) == true)
	{
		return true;
	}
#endif // CSK_LH_DEBUG_CONSOLE

#ifdef YDG_MOD_CHECK_PROTECT_AUTO_FLAG
	if(g_pProtectAuto->CheckFlag(Text) == true)
	{
		return true;
	}
#endif // YDG_MOD_CHECK_PROTECT_AUTO_FLAG
	
#ifndef _VS2008PORTING			// #ifndef
	int i;
#endif // _VS2008PORTING
	
    if( bMacroText==false && LogOut == false )
    {
		//�ŷ�
		char Name[256];
#ifdef _VS2008PORTING
		int iTextSize=0;
		for(int i=0;i<256 && Text[i] != ' ' && Text[i] != '\0';i++)
		{
			Name[i] = Text[i];
			iTextSize = i;
		}
		Name[iTextSize] = NULL;
#else // _VS2008PORTING
		for(int i=0;i<256 && Text[i] != ' ' && Text[i] != '\0';i++)
			Name[i] = Text[i];
		Name[i] = NULL;
#endif // _VS2008PORTING

		if (!g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE))
		{
			if(strcmp(Name,GlobalText[258])==NULL || strcmp(Name,GlobalText[259])==NULL || stricmp(Name,"/trade")==NULL)
			{
				if ( InChaosCastle()==true )
				{
					g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
					
					return false;
				}
				// ������������ /�ŷ� ��� ����
#ifdef LJH_FIX_UNABLE_TO_TRADE_OR_PURCHASE_IN_TROUBLED_AREAS
				if (::IsStrifeMap(World))	// ��������?
				{
					g_pChatListBox->AddText("", GlobalText[3147], SEASON3B::TYPE_SYSTEM_MESSAGE);
					return false;
				}
#endif //LJH_FIX_UNABLE_TO_TRADE_OR_PURCHASE_IN_TROUBLED_AREAS

				int level = CharacterAttribute->Level;
				//  �ŷ� ���� ����.
				if( level < TRADELIMITLEVEL )
				{
					//  6���� �̻� ĳ���ͺ��� "/�ŷ�"�� �Ҽ� �ֽ��ϴ�.
					g_pChatListBox->AddText("", GlobalText[478], SEASON3B::TYPE_SYSTEM_MESSAGE);        	        
					return true;
				}
				if(SelectedCharacter!=-1)
				{
					CHARACTER *c = &CharactersClient[SelectedCharacter];	
					OBJECT *o = &c->Object;
					if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
						abs(( c->PositionX)-( Hero->PositionX))<=1 &&
						abs(( c->PositionY)-( Hero->PositionY))<=1)
					{
						if(IsShopInViewport(c))
						{
							g_pChatListBox->AddText("", GlobalText[493], SEASON3B::TYPE_ERROR_MESSAGE);
							return true;
						}
						SendRequestTrade(CharactersClient[SelectedCharacter].Key);
					}
				}
#ifdef _VS2008PORTING
				else for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
				else for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
				{
					CHARACTER *c = &CharactersClient[i];
					OBJECT *o = &c->Object;
					
					if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
						abs(( c->PositionX)-( Hero->PositionX))<=1 &&
						abs(( c->PositionY)-( Hero->PositionY))<=1)
					{
						if(IsShopInViewport(c))
						{
							g_pChatListBox->AddText("", GlobalText[493], SEASON3B::TYPE_SYSTEM_MESSAGE);
							return true;
						}
						
						BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
						BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
						if(abs(Dir1-Dir2)==4) {
							SendRequestTrade(c->Key);
							break;
						}
					}						
				}
				return true;
			}
		}

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
		// 260 "/�̵�"
		if(strcmp(Name, GlobalText[260]) == 0 || stricmp(Name, "/move") == 0)
		{
#ifdef CSK_FIX_GM_MOVE
			// GMĳ���ʹ� /�̵� ��ɾ� �Ծ�� �Ѵ�.
			if(IsGMCharacter() == true
#ifdef CSK_FIX_GM_WEBZEN_ID
				|| FindText2(Hero->ID, "webzen") == true	// �ڱ� ���̵� webzen�� �� ������
#endif // CSK_FIX_GM_WEBZEN_ID
				)
			{
				return false;
			}
#endif // CSK_FIX_GM_MOVE
			return true;
		}
#else // CSK_MOD_MOVE_COMMAND_WINDOW
		if(strcmp(Text,GlobalText[260])==0 || stricmp(Text, "/move")==0)
		{
		}
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
#ifdef CSK_ADD_GM_ABILITY
		// 688 "/����"
		if(strcmp(Text, GlobalText[688]) == 0)
		{
			return false;
		}
#endif // CSK_ADD_GM_ABILITY
		if(strcmp(Text,GlobalText[1117])==0 || stricmp(Text, "/personalshop")==0)
		{
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);              
				return false;
			}
			
			//. �������� ��������
			int level = CharacterAttribute->Level;
			if( level >= 6)
			{
				g_pNewUISystem->Show( SEASON3B::INTERFACE_MYSHOP_INVENTORY );		
			}
			else
			{
				char szError[48] = "";
				sprintf(szError, GlobalText[1123], 6);	//. ���� 6�̻���� �̿� �� �� �ֽ��ϴ�.
				g_pChatListBox->AddText("", szError, SEASON3B::TYPE_SYSTEM_MESSAGE);				
			}
			return true;
		}
		if(strstr(Text,GlobalText[1118])>0 || strstr(Text,"/purchase")>0)
		{
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
#ifdef LJH_FIX_UNABLE_TO_TRADE_OR_PURCHASE_IN_TROUBLED_AREAS
			if (::IsStrifeMap(World))	// ��������?
			{
				g_pChatListBox->AddText("", GlobalText[3147], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
#endif //LJH_FIX_UNABLE_TO_TRADE_OR_PURCHASE_IN_TROUBLED_AREAS
			
			//. bugfix by soyaviper 2005/03/16
			if (
				g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP)
				|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE)
				|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_TRADE)
				|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MIXINVENTORY)
#ifdef LEM_ADD_LUCKYITEM
				|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYITEMWND)
#endif // LEM_ADD_LUCKYITEM
				)
			{
				g_pChatListBox->AddText("", GlobalText[1121], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
			char szCmd[24];
			char szId[MAX_ID_SIZE];
			sscanf(Text,"%s %s", szCmd, szId);
			
			if(SelectedCharacter!=-1)
			{
				CHARACTER *c = &CharactersClient[SelectedCharacter];
				OBJECT *o = &c->Object;
				if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change))
					SendRequestOpenPersonalShop(c->Key, c->ID);
			}
			else 
			{
#ifdef _VS2008PORTING
				for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
				for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
				{
					CHARACTER *c = &CharactersClient[i];
					if(strlen(szId) > 0 && c->Object.Live)
					{
						if(strcmp(c->ID,szId)==0) 
						{
							SendRequestOpenPersonalShop(c->Key, c->ID);
						}
					}
					else
					{
						OBJECT *o = &c->Object;
						if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change)) 
						{
							BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
							BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
							if(abs(Dir1-Dir2)==4)
							{
								SendRequestOpenPersonalShop(c->Key, c->ID);
								break;
							}
						}		
					}	// end of ; strlen(szId) <= 0
				}	// end of ; for
			}	// end of ; SelectedCharcter == -1

			return true;
		}
		
		// 1136 "/�������� on"
		if(strcmp(Text,GlobalText[1136]) == 0)
		{
			ShowShopTitles();
			// 1138 "���λ��� â���� �� �� �ֽ��ϴ�."
			g_pChatListBox->AddText("", GlobalText[1138], SEASON3B::TYPE_SYSTEM_MESSAGE);
		}
		
		// 1137 "/�������� off"
		if(strcmp(Text,GlobalText[1137]) == 0)
		{
			HideShopTitles();
			// 1139 "���λ��� â���� �� �� �����ϴ�."
			g_pChatListBox->AddText("", GlobalText[1139], SEASON3B::TYPE_ERROR_MESSAGE);
		}
#ifdef DUEL_SYSTEM
		if(strcmp(Text,GlobalText[908])==0 || stricmp(Text, "/duelstart")==0)
		{
#ifndef GUILD_WAR_EVENT
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
#endif// UILD_WAR_EVENT
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
			if(!g_DuelMgr.IsDuelEnabled())	//. �ڽ��� �������� �ƴҰ�� ��������
#else	// YDG_ADD_NEW_DUEL_SYSTEM
			if(!g_bEnableDuel)	//. �ڽ��� �������� �ƴҰ�� ��������
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
			{
#ifdef YDG_ADD_NEW_DUEL_UI
				int iLevel = CharacterAttribute->Level;
				if(iLevel < 30)	// ��������
				{
					char szError[48] = "";
					sprintf(szError, GlobalText[2704], 30);	// "%d���� �̻��� ĳ���͸� ������ �����մϴ�."
					g_pChatListBox->AddText("", szError, SEASON3B::TYPE_ERROR_MESSAGE);				
					return 3;
				}
				else
#endif	// YDG_ADD_NEW_DUEL_UI
				if(SelectedCharacter!=-1)
				{
					CHARACTER *c = &CharactersClient[SelectedCharacter];
					OBJECT *o = &c->Object;
					if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
						abs(( c->PositionX)-( Hero->PositionX))<=1 &&
						abs(( c->PositionY)-( Hero->PositionY))<=1){
						
						//. �������ۿ�û ��Ŷ ������
						SendRequestDuelStart(c->Key, c->ID);
					}
				}
#ifdef _VS2008PORTING
				else for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
				else for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
				{
					CHARACTER *c = &CharactersClient[i];
					OBJECT *o = &c->Object;
					
					if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
						abs(( c->PositionX)-( Hero->PositionX))<=1 &&
						abs(( c->PositionY)-( Hero->PositionY))<=1)
					{
						BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
						BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
						if(abs(Dir1-Dir2)==4) {
							//. �������ۿ�û ��Ŷ ������
							SendRequestDuelStart(c->Key, c->ID);
							break;
						}
					}		
				}
			}
			else
			{
				//. ������ ���� �������϶�
				g_pChatListBox->AddText("", GlobalText[915], SEASON3B::TYPE_SYSTEM_MESSAGE);				
			}
		}
		if(strcmp(Text,GlobalText[909])==0 || stricmp(Text, "/duelend")==0)
		{
#ifndef GUILD_WAR_EVENT
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
#endif// GUILD_WAR_EVENT
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
			if(g_DuelMgr.IsDuelEnabled())	//. �ڽ��� �������϶��� ��������
#else	// YDG_ADD_NEW_DUEL_SYSTEM
			if(g_bEnableDuel)	//. �ڽ��� �������϶��� ��������
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
			{
				//. ����������û ��Ŷ ������
				SendRequestDuelEnd();
			}
		}
#endif // DUEL_SYSTEM
		if(strcmp(Text,GlobalText[254])==NULL || stricmp(Text,"/guild")==NULL)
		{
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
			if( Hero->GuildStatus != G_NONE )
			{
				g_pChatListBox->AddText("", GlobalText[255], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return true;
			}
			
			if(SelectedCharacter!=-1)
			{
				CHARACTER *c = &CharactersClient[SelectedCharacter];
				OBJECT *o = &c->Object;
				if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
					SendRequestGuild(CharactersClient[SelectedCharacter].Key);
			}
#ifdef _VS2008PORTING
			else for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
			else for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *o = &c->Object;
				
				if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
				{
					BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					if(abs(Dir1-Dir2)==4) 
					{
						SendRequestGuild(c->Key);
						break;
					}
				}
			}
			return true;
		}
		if( !strcmp(Text,GlobalText[1354]) || !stricmp(Text,"/union") ||
			!strcmp(Text,GlobalText[1356]) || !stricmp(Text,"/rival") ||
			!strcmp(Text,GlobalText[1357]) || !stricmp(Text,"/rivaloff") )
		{
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);              
				return false;
			}
			if( Hero->GuildStatus == G_NONE )
			{
				g_pChatListBox->AddText("", GlobalText[1355], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return true;
			}
			
			if(SelectedCharacter!=-1)
			{
				CHARACTER *c = &CharactersClient[SelectedCharacter];
				OBJECT *o = &c->Object;
				if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
				{
					if( !strcmp(Text,GlobalText[1354]) || !stricmp(Text,"/union") )
					{
						// ��忬�� ��û�ϱ�
						SendRequestGuildRelationShip( 0x01, 0x01, HIBYTE(CharactersClient[SelectedCharacter].Key), LOBYTE(CharactersClient[SelectedCharacter].Key));
					}
					else if( !strcmp(Text,GlobalText[1356]) || !stricmp(Text,"/rival") )
					{
						// ������ ��û�ϱ�
						SendRequestGuildRelationShip( 0x02, 0x01, HIBYTE(CharactersClient[SelectedCharacter].Key), LOBYTE(CharactersClient[SelectedCharacter].Key));
					}
					else
					{
						// �����ݱ�
						SetAction( &Hero->Object, PLAYER_RESPECT1 );
						SendRequestAction( AT_RESPECT1, ((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8) );
						// ������ ����
						SendRequestGuildRelationShip( 0x02, 0x02, HIBYTE(CharactersClient[SelectedCharacter].Key), LOBYTE(CharactersClient[SelectedCharacter].Key));
					}
				}
			}
#ifdef _VS2008PORTING
			else for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
			else for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *o = &c->Object;
				
				if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
				{
					BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					if(abs(Dir1-Dir2)==4) {
						if( !strcmp(Text,GlobalText[1354]) || !stricmp(Text,"/union") )
						{
							// ��忬�� ��û�ϱ�
							SendRequestGuildRelationShip( 0x01, 0x01, HIBYTE(c->Key), LOBYTE(c->Key));
						}
						else if( !strcmp(Text,GlobalText[1356]) || !stricmp(Text,"/rival") )
						{
							// ������ ��û�ϱ�
							SendRequestGuildRelationShip( 0x02, 0x01, HIBYTE(c->Key), LOBYTE(c->Key));
						}
						else
						{
							// �����ݱ�
							SetAction( &Hero->Object, PLAYER_RESPECT1 );
							SendRequestAction( AT_RESPECT1, ((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8) );
							// ������ ����
							SendRequestGuildRelationShip( 0x02, 0x02, HIBYTE(c->Key), LOBYTE(c->Key));
						}
						break;
					}
				}
			}
			return true;
		}
		if(strcmp(Text,GlobalText[256])==NULL || stricmp(Text,"/party")==NULL || stricmp(Text,"/pt")==NULL)
		{
			if ( InChaosCastle()==true )
			{
				g_pChatListBox->AddText("", GlobalText[1150], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return false;
			}
			if(PartyNumber>0 && strcmp(Party[0].Name,Hero->ID)!=NULL)
			{
				g_pChatListBox->AddText("", GlobalText[257], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return true;
			}
			
			if(SelectedCharacter!=-1)
			{
				CHARACTER *c = &CharactersClient[SelectedCharacter];
				OBJECT *o = &c->Object;
				if(o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
					SendRequestParty(CharactersClient[SelectedCharacter].Key);
			}
#ifdef _VS2008PORTING
			else for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
			else for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *o = &c->Object;	
				if(o->Live && o->Kind==KIND_PLAYER && c!=Hero && (o->Type==MODEL_PLAYER||c->Change) &&
					abs(( c->PositionX)-( Hero->PositionX))<=1 &&
					abs(( c->PositionY)-( Hero->PositionY))<=1)
				{
					BYTE Dir1 = (BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					BYTE Dir2 = (BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8;
					if(abs(Dir1-Dir2)==4) {
						SendRequestParty(c->Key);
						break;
					}
				}
			}
			return true;
		}
#ifdef CSK_ADD_GM_ABILITY
		// GMĳ���͸� ��ɾ �۵��ϰ� ��.
#ifdef PBG_MOD_GM_ABILITY
		if((stricmp(Text, "/ĳ���͸�") == NULL) || (stricmp(Text, "/charactername") == NULL))
#else //PBG_MOD_GM_ABILITY
		if(stricmp(Text, "/ĳ���͸�") == NULL)
#endif //PBG_MOD_GM_ABILITY
		{
			if(IsGMCharacter() == true)
			{
				g_bGMObservation = !g_bGMObservation;
				return true;
			}
		}
#endif // CSK_ADD_GM_ABILITY
		//��ũ�� ���
#ifdef _VS2008PORTING
		for(int i=0;i<10;i++)
#else // _VS2008PORTING
		for(i=0;i<10;i++)
#endif // _VS2008PORTING
		{
			char Name[256];
			if(i!=9)
				sprintf(Name,"/%d",i+1);
			else
				sprintf(Name,"/%d",0);
			if(Text[0]==Name[0] && Text[1]==Name[1])
			{
				//  "/��Ƽ, /�ŷ�"�� ��ũ�ΰ� ���� �ʴ´�.
				if( CheckMacroLimit( Text )==true )
				{
					return  false;
				}
#ifdef _VS2008PORTING
				int iTextSize = 0;
				for(int j=3;j<(int)strlen(Text);j++)
				{
					MacroText[i][j-3] = Text[j];
					iTextSize = j;
				}
				MacroText[i][iTextSize-3] = NULL;
#else // _VS2008PORTING
				for(int j=3;j<(int)strlen(Text);j++)
					MacroText[i][j-3] = Text[j];
				MacroText[i][j-3] = NULL;
#endif // _VS2008PORTING
				PlayBuffer(SOUND_CLICK01);
				return true;
			}
		}

		// ���� ���
		char lpszFilter[] = "/filter";
		if((strlen(GlobalText[753]) > 0 && strncmp(Text,GlobalText[753], strlen(GlobalText[753]))==NULL)
			|| (strncmp(Text,lpszFilter, strlen(lpszFilter))==NULL))
		{
			g_pChatListBox->SetFilterText(Text);
		}
    }
#ifdef CSK_FIX_MACRO_MOVEMAP
	// ��ũ�ο��� /�̵� ��ɾ� �����۾�
	else if(bMacroText == true)
	{
		// �̸� �ľ�
		char Name[256];
#ifdef _VS2008PORTING
		int iTextSize=0;
		for(int i=0;i<256 && Text[i] != ' ' && Text[i] != '\0';i++)
		{
			Name[i] = Text[i];
			iTextSize = i;
		}
		Name[iTextSize] = NULL;
#else // _VS2008PORTING
		for(int i=0;i<256 && Text[i] != ' ' && Text[i] != '\0';i++)
			Name[i] = Text[i];
		Name[i] = NULL;
#endif // _VS2008PORTING

		// 260 "/�̵�"
		if(strcmp(Name, GlobalText[260]) == 0 || stricmp(Name, "/move") == 0)
		{
			// GMĳ���ʹ� /�̵� ��ɾ� �Ծ�� �Ѵ�. // �ڱ� ���̵� webzen�� �� ������
			if(IsGMCharacter() == true || FindText2(Hero->ID, "webzen") == true)
			{
				return false;
			}
			return true;
		}
	}
#endif // CSK_FIX_MACRO_MOVEMAP
	
#ifdef LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG					
	if(IsIllegalMovementByUsingMsg(Text))
		return TRUE;
#endif //LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG

//������ ����
#ifdef _VS2008PORTING
	for(int i=0; i<16*MAX_ITEM_INDEX; ++i)	
#else // _VS2008PORTING
	for(i=0; i<16*MAX_ITEM_INDEX; ++i)
#endif // _VS2008PORTING
	{
		ITEM_ATTRIBUTE *p = &ItemAttribute[i];
		
		if(p->Width != 0)
		{
			char Name[256];
			sprintf(Name,"/%s",p->Name);
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			if(stricmp(Text,Name) == NULL)
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			if(strcmp(Text,Name) == NULL)
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			{
				g_csItemOption.ClearOptionHelper ();
				
				g_pNewUISystem->Show(SEASON3B::INTERFACE_ITEM_EXPLANATION);
				
				ItemHelp = i;
				PlayBuffer(SOUND_CLICK01);
				return true;
			}
		}
	}
	
	g_csItemOption.CheckRenderOptionHelper ( Text );

	
#ifdef LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG					
	return (IsIllegalMovementByUsingMsg(Text)) ? TRUE : FALSE;
#endif //LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// ���ڿ� ���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

bool FindText(const char* Text,const char* Token,bool First)
{
    int LengthToken = (int)strlen(Token);
	int Length = (int)strlen(Text)-LengthToken;
	if(First)
		Length = 0;
	if(Length < 0)
		return false;
	
    unsigned char* lpszCheck = (unsigned char*)Text;
	for(int i=0;i<=Length;i+=_mbclen(lpszCheck+i))
	{
		bool Success = true;
		for(int j=0;j<LengthToken;j++)
		{
			if(Text[i+j] != Token[j])
			{
				Success = false;
				break;
			}
		}
		if(Success)
			return true;
	}
	return false;
}


bool FindTextABS(const char* Text,const char* Token,bool First)
{
    int LengthToken = (int)strlen(Token);
	int Length = (int)strlen(Text)-LengthToken;
	if(First)
		Length = 0;
	if(Length < 0)
		return false;
	
    unsigned char* lpszCheck = (unsigned char*)Text;
	for(int i=0;i<=Length;i+=_mbclen(lpszCheck+i))
	{
		bool Success = true;
		for(int j=0;j<LengthToken;j++)
		{
			if( Text[i+j] != Token[j] )
			{
				Success = false;
				break;
			}
		}
		if(Success)
			return true;
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// �׼��� ���ϴ� �Լ�(�λ�, ���� ���)
///////////////////////////////////////////////////////////////////////////////

void SetActionClass(CHARACTER *c,OBJECT *o,int Action,int ActionType)
{
	if ( ( o->CurrentAction>=PLAYER_STOP_MALE && o->CurrentAction<=PLAYER_STOP_RIDE_WEAPON )
		|| o->CurrentAction==PLAYER_STOP_TWO_HAND_SWORD_TWO 
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
		|| o->CurrentAction==PLAYER_RAGE_UNI_STOP_ONE_RIGHT 
		|| o->CurrentAction==PLAYER_STOP_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK_ANI
		)
	{
		if(!IsFemale(c->Class) || (Action>=PLAYER_RESPECT1 && Action<=PLAYER_RUSH1))
			SetAction(o,Action);
		else
			SetAction(o,Action+1);
		SendRequestAction(ActionType,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
}

///////////////////////////////////////////////////////////////////////////////
// �Է� �ؽ�Ʈ�߿��� �׼��� ���Ҹ��� ���ڰ� �ִ��� üũ�ϴ� �Լ�(����, ^^ ���)
///////////////////////////////////////////////////////////////////////////////

void CheckChatText(char *Text)
{
	CHARACTER *c = Hero;
	OBJECT *o = &c->Object;
	if(FindText(Text,GlobalText[270]) || FindText(Text,GlobalText[271]) || FindText(Text,GlobalText[272]) || FindText(Text,GlobalText[273]) || FindText(Text,GlobalText[274]) || FindText(Text,GlobalText[275]) || FindText(Text,GlobalText[276]) || FindText(Text,GlobalText[277]))
	{
		SetActionClass(c,o,PLAYER_GREETING1,AT_GREETING1);
		SendRequestAction(AT_GREETING1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[278]) || FindText(Text,GlobalText[279]) || FindText(Text,GlobalText[280]))
	{
		SetActionClass(c,o,PLAYER_GOODBYE1,AT_GOODBYE1);
		SendRequestAction(AT_GOODBYE1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[281]) || FindText(Text,GlobalText[282]) || FindText(Text,GlobalText[283]) || FindText(Text,GlobalText[284]) || FindText(Text,GlobalText[285])  || FindText(Text,GlobalText[286]))
	{
		SetActionClass(c,o,PLAYER_CLAP1,AT_CLAP1);
		SendRequestAction(AT_CLAP1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[287]) || FindText(Text,GlobalText[288]) || FindText(Text,GlobalText[289]) || FindText(Text,GlobalText[290]))
	{
		SetActionClass(c,o,PLAYER_GESTURE1,AT_GESTURE1);
		SendRequestAction(AT_GESTURE1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[292]) || FindText(Text,GlobalText[293]) || FindText(Text,GlobalText[294]) || FindText(Text,GlobalText[295]))
	{
		SetActionClass(c,o,PLAYER_DIRECTION1,AT_DIRECTION1);
		SendRequestAction(AT_DIRECTION1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[296]) || FindText(Text,GlobalText[297]) || FindText(Text,GlobalText[298]) || FindText(Text,GlobalText[299]) || FindText(Text,GlobalText[300]) ||  FindText(Text,GlobalText[301]) || FindText(Text,GlobalText[302]))
	{
		SetActionClass(c,o,PLAYER_UNKNOWN1,AT_UNKNOWN1);
		SendRequestAction(AT_UNKNOWN1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,";") || FindText(Text,GlobalText[303]) || FindText(Text,GlobalText[304]) || FindText(Text,GlobalText[305]))
	{
		SetActionClass(c,o,PLAYER_AWKWARD1,AT_AWKWARD1);
		SendRequestAction(AT_AWKWARD1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,"��.��") || FindText(Text,"��.��") || FindText(Text,"T_T") || FindText(Text,GlobalText[306]) || FindText(Text,GlobalText[307]) || FindText(Text,GlobalText[308]) || FindText(Text,GlobalText[309]))
	{
		SetActionClass(c,o,PLAYER_CRY1,AT_CRY1);
		SendRequestAction(AT_CRY1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,"��.��") || FindText(Text,"��.,��") || FindText(Text,"��,.��") || FindText(Text,"-.-") || FindText(Text,"-_-") || FindText(Text,GlobalText[310]) || FindText(Text,GlobalText[311]))
	{
		SetActionClass(c,o,PLAYER_SEE1,AT_SEE1);
		SendRequestAction(AT_SEE1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,"^^") || FindText(Text,"^.^") || FindText(Text,"^_^") || FindText(Text,GlobalText[312]) || FindText(Text,GlobalText[313]) || FindText(Text,GlobalText[314]) || FindText(Text,GlobalText[315]) || FindText(Text,GlobalText[316]))
	{
		SetActionClass(c,o,PLAYER_SMILE1,AT_SMILE1);
		SendRequestAction(AT_SMILE1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[318]) || FindText(Text,GlobalText[319]) || FindText(Text,GlobalText[320]) || FindText(Text,GlobalText[321]))
	{
		SetActionClass(c,o,PLAYER_CHEER1,AT_CHEER1);
		SendRequestAction(AT_CHEER1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[322]) || FindText(Text,GlobalText[323]) || FindText(Text,GlobalText[324]) || FindText(Text,GlobalText[325]))
	{
		SetActionClass(c,o,PLAYER_WIN1,AT_WIN1);
		SendRequestAction(AT_WIN1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[326]) || FindText(Text,GlobalText[327]) || FindText(Text,GlobalText[328]) || FindText(Text,GlobalText[329]))
	{
		SetActionClass(c,o,PLAYER_SLEEP1,AT_SLEEP1);
		SendRequestAction(AT_SLEEP1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[330]) || FindText(Text,GlobalText[331]) || FindText(Text,GlobalText[332]) || FindText(Text,GlobalText[333]) || FindText(Text,GlobalText[334]))
	{
		SetActionClass(c,o,PLAYER_COLD1,AT_COLD1);
		SendRequestAction(AT_COLD1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[335]) || FindText(Text,GlobalText[336]) || FindText(Text,GlobalText[337]) || FindText(Text,GlobalText[338]))
	{
		SetActionClass(c,o,PLAYER_AGAIN1,AT_AGAIN1);
		SendRequestAction(AT_AGAIN1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[339]) || FindText(Text,GlobalText[340]) || FindText(Text,GlobalText[341]))
	{
		SetActionClass(c,o,PLAYER_RESPECT1,AT_RESPECT1);
		SendRequestAction(AT_RESPECT1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[342]) || FindText(Text,GlobalText[343]) || FindText(Text,"/��") || FindText(Text,"��^"))
	{
		SetActionClass(c,o,PLAYER_SALUTE1,AT_SALUTE1);
		SendRequestAction(AT_SALUTE1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[344]) || FindText(Text,GlobalText[345]) || FindText(Text,GlobalText[346]) || FindText(Text,GlobalText[347]))
	{
		SetActionClass(c,o,PLAYER_RUSH1,AT_RUSH1);
		SendRequestAction(AT_RUSH1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	else if(strcmp(Text,GlobalText[780]) == 0)// FindText(Text,GlobalText[780]))	// ����
	{
		SetActionClass(c,o,PLAYER_SCISSORS,AT_SCISSORS);
		SendRequestAction(AT_SCISSORS,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(strcmp(Text,GlobalText[781]) == 0)// FindText(Text,GlobalText[781]))	// ����
	{
		SetActionClass(c,o,PLAYER_ROCK,AT_ROCK);
		SendRequestAction(AT_ROCK,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(strcmp(Text,GlobalText[782]) == 0)// FindText(Text,GlobalText[782]))	// ��
	{
		SetActionClass(c,o,PLAYER_PAPER,AT_PAPER);
		SendRequestAction(AT_PAPER,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
#endif
	else if(FindText(Text,GlobalText[783]) || FindText(Text,"hustle"))	// �Ϻ� ������ ����
	{
		SetActionClass(c,o,PLAYER_HUSTLE,AT_HUSTLE);
		SendRequestAction(AT_HUSTLE,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[291]))	// ���� ���� �߰� �Ȱ�
	{
		SetActionClass(c,o,PLAYER_PROVOCATION,AT_PROVOCATION);
		SendRequestAction(AT_PROVOCATION,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[317]))	// ���� ���� �߰� �Ȱ�
	{
		SetActionClass(c,o,PLAYER_CHEERS,AT_CHEERS);
		SendRequestAction(AT_CHEERS,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[348]))	// �θ��� ���� �߰� �Ȱ�
	{
		SetActionClass(c,o,PLAYER_LOOK_AROUND,AT_LOOK_AROUND);
		SendRequestAction(AT_LOOK_AROUND,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
#ifdef WORLDCUP_ADD
#ifdef WINDOWMODE
#ifdef ADD_MU_HOMEPAGE
	else if(FindText(Text, GlobalText[349])) // LHJ - "/��" ġ�� Ȩ������ ���
	{
		
		if(g_bUseWindowMode)	// LHJ - â��� �϶��� ����
#ifdef KJH_FIX_MU_HOMEPAGE_ADDRESS
#ifdef PBG_FIX_BLUEHOMEPAGE_LINK
			leaf::OpenExplorer("http://blue.muonline.co.kr/sitemain.aspx");
#else //PBG_FIX_BLUEHOMEPAGE_LINK
			leaf::OpenExplorer("www.muonline.co.kr/sitemain.aspx");
#endif //PBG_FIX_BLUEHOMEPAGE_LINK
#else // KJH_FIX_MU_HOMEPAGE_ADDRESS
			leaf::OpenExplorer("www.muonline.co.kr/GameMain.asp");
#endif // KJH_FIX_MU_HOMEPAGE_ADDRESS
	}
#endif //ADD_MU_HOMEPAGE
#endif //#ifdef WINDOWMODE
#ifndef NO_MORE_DANCING
	else if(FindText(Text,GlobalText[2041]))	// 2041 "����"
	{
		SetActionClass(c,o,PLAYER_KOREA_HANDCLAP,AT_HANDCLAP);
		SendRequestAction(AT_HANDCLAP,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
	else if(FindText(Text,GlobalText[2042]))	// 2042 "��"
	{
		SetActionClass(c,o,PLAYER_POINT_DANCE,AT_POINTDANCE);
		SendRequestAction(AT_POINTDANCE,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
#endif // NO_MORE_DANCING
#endif // WORLDCUP_ADD
	else if(FindText(Text, GlobalText[2228]))	// 2228 "�̸�"
	{
		ITEM* pItem_rr = &CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT];
		ITEM* pItem_rl = &CharacterMachine->Equipment[EQUIPMENT_RING_LEFT];
		
		if(pItem_rr->Type == ITEM_HELPER+40 || pItem_rl->Type == ITEM_HELPER+40)
		{
			if(rand()%2 == 0)
			{
				SetAction(o, PLAYER_JACK_1);
				SendRequestAction(AT_JACK1,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
			}
			else
			{
				SetAction(o, PLAYER_JACK_2);
				SendRequestAction(AT_JACK2,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
			}
			
			o->m_iAnimation = 0;
		}
		
	}
	else if(FindText(Text, GlobalText[2243]))	// 2243 "ũ��������"
	{
		ITEM* pItem_rr = &CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT];
		ITEM* pItem_rl = &CharacterMachine->Equipment[EQUIPMENT_RING_LEFT];
		
		if(pItem_rr->Type == ITEM_HELPER+41 || pItem_rl->Type == ITEM_HELPER+41)
		{
			if(o->CurrentAction != PLAYER_SANTA_1 && o->CurrentAction != PLAYER_SANTA_2)
			{
				int i = rand()%3;
				if(rand()%2)
				{
					SetAction(o, PLAYER_SANTA_1);
					SendRequestAction(AT_SANTA1_1+i,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
					PlayBuffer(SOUND_XMAS_JUMP_SANTA + i);
				}
				else
				{
					SetAction(o, PLAYER_SANTA_2);
					SendRequestAction(AT_SANTA2_1+i,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
					PlayBuffer(SOUND_XMAS_TURN);
				}
				
				g_XmasEvent->CreateXmasEventEffect(c, o, i);
			}
			
			o->m_iAnimation = 0;
		}
	}
}

#if defined FOR_WORK && defined ENABLE_CHAT_IN_CHAOS
bool IsManagerID(char* szID)
{
	return FindText(szID, "webzen");
}
#endif // FOR_WORK && ENABLE_CHAT_IN_CHAOS

///////////////////////////////////////////////////////////////////////////////
// ���콺 Ŭ���� Ÿ������ ���س�
///////////////////////////////////////////////////////////////////////////////

bool CheckTarget(CHARACTER *c)
{
	if(SelectedCharacter != -1)
	{
		TargetX = (int)(CharactersClient[SelectedCharacter].Object.Position[0]/TERRAIN_SCALE);
		TargetY = (int)(CharactersClient[SelectedCharacter].Object.Position[1]/TERRAIN_SCALE);
		VectorCopy(CharactersClient[SelectedCharacter].Object.Position,c->TargetPosition);
		return true;
	}
	else
	{
		RenderTerrain(true);
		if(RenderTerrainTile(SelectXF,SelectYF,(int)SelectXF,(int)SelectYF,1.f,1,true))
		{
			VectorCopy(CollisionPosition,c->TargetPosition);
			TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
			TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// ���콺 ������ ��ư Ŭ���� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////
bool EnableFastInput = false;

WORD g_byLastSkillSerialNumber = 0;

BYTE MakeSkillSerialNumber(BYTE * pSerialNumber)
{
	if (pSerialNumber == NULL) return 0;
	
	++g_byLastSkillSerialNumber;
//#ifdef PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	// ������ ���� Ŭ��� (100-4)* 3��°�� Ŭ��� �Ѵܴ�
	// �ѹ��� 96ȸ �̻��� ������ �ȴ�
//	if (g_byLastSkillSerialNumber > 100) g_byLastSkillSerialNumber = 1;
//#else //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	if (g_byLastSkillSerialNumber > 50) g_byLastSkillSerialNumber = 1;
//#endif //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	
	*pSerialNumber = g_byLastSkillSerialNumber;
	return g_byLastSkillSerialNumber;
}

#ifdef YDG_FIX_SPLIT_ATTACK_FUNC
void AttackElf(CHARACTER *c, int Skill, float Distance)
{
	OBJECT *o = &c->Object;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    int ClassIndex = GetBaseClass ( c->Class );
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	int iMana, iSkillMana;
	GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
	if( g_isCharacterBuff(o, eBuff_InfinityArrow) ) 
		iMana += CharacterMachine->InfinityArrowAdditionalMana;
	if(iMana > CharacterAttribute->Mana)
	{
		int Index = g_pMyInventory->FindManaItemIndex();

		if(Index != -1)
		{
			SendRequestUse(Index, 0);
		}
		return;
	}
	// skillmana ����
	if(iSkillMana > CharacterAttribute->SkillMana)
	{
		return;
	}
    if ( !CheckSkillDelay( Hero->CurrentSkill ) )
    {
        return;
    }
	
	int iEnergy;
	GetSkillInformation_Energy(Skill, &iEnergy);
	if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy) )
	{
		return;
	}
	
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	CheckTarget(c);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    bool Success = CheckTarget(c);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	switch(Skill)
	{
	case AT_SKILL_SUMMON:
	case AT_SKILL_SUMMON+1:
	case AT_SKILL_SUMMON+2:
	case AT_SKILL_SUMMON+3:
	case AT_SKILL_SUMMON+4:
	case AT_SKILL_SUMMON+5:
	case AT_SKILL_SUMMON+6:
#ifdef ADD_ELF_SUMMON
	case AT_SKILL_SUMMON+7:
#endif // ADD_ELF_SUMMON
        if ( World!=WD_10HEAVEN && InChaosCastle()==false )
			if(!g_Direction.m_CKanturu.IsMayaScene())
			{
				SendRequestMagic(Skill,HeroKey);
				SetPlayerMagic(c);
			}
			return;
			
    case AT_SKILL_PIERCING:
#ifdef ADD_SOCKET_ITEM
		// �÷��̾ Ȱ�̳� ������ �������� ��
		if( (o->Type == MODEL_PLAYER) && (GetEquipedBowType( Hero ) != BOWTYPE_NONE) )
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
			if( o->Type==MODEL_PLAYER &&
				(( Hero->Weapon[0].Type>=MODEL_BOW+8  && Hero->Weapon[0].Type<MODEL_BOW+15 ) ||
				(( Hero->Weapon[1].Type>=MODEL_BOW    && Hero->Weapon[1].Type<MODEL_BOW+7 ) 
				|| Hero->Weapon[1].Type==MODEL_BOW+17 
				|| Hero->Weapon[1].Type==MODEL_BOW+20
				|| Hero->Weapon[1].Type==MODEL_BOW+21
				|| Hero->Weapon[1].Type==MODEL_BOW+22
				) ||
				(  Hero->Weapon[0].Type>=MODEL_BOW+16 && Hero->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX ) ) )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
			{
				if(!CheckArrow())
					break;
				if ( CheckTile( c, o, Distance ) )
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0,TKey,0);
					SetPlayerAttack(c);
					if(o->Type != MODEL_PLAYER)
					{
						CreateArrows(c,o,NULL,FindHotKey(( c->Skill)),0,( c->Skill));
					}
				}
			}
			break;
			
	}
	if(SelectedCharacter != -1)
	{
		ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
		g_MovementSkill.m_bMagic = TRUE;
		g_MovementSkill.m_iSkill = Hero->CurrentSkill;
		g_MovementSkill.m_iTarget = SelectedCharacter;
	}
	if ( !CheckTile( c, o, Distance ) )
	{
		if ( SelectedCharacter!=-1 && ( Skill==AT_SKILL_HEALING || Skill==AT_SKILL_ATTACK || Skill==AT_SKILL_DEFENSE || CheckAttack() 
			|| (AT_SKILL_HEAL_UP <= Skill && Skill <= AT_SKILL_HEAL_UP+4)
			|| Skill==AT_SKILL_DARK_SCREAM
#ifdef PJH_SEASON4_MASTER_RANK4
			|| (AT_SKILL_FIRE_SCREAM_UP <= Skill && Skill <= AT_SKILL_FIRE_SCREAM_UP+4)
			|| (AT_SKILL_DEF_POWER_UP <= Skill && Skill <= AT_SKILL_DEF_POWER_UP+4)
			|| (AT_SKILL_ATT_POWER_UP <= Skill && Skill <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
			)
			)
		{
			if(CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
			{
				if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
				{
					c->Movement = true;
					c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
					SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
				}
			}
		}
		
		if(Skill != AT_SKILL_STUN && Skill != AT_SKILL_REMOVAL_STUN && Skill != AT_SKILL_MANA && Skill != AT_SKILL_INVISIBLE && Skill != AT_SKILL_REMOVAL_INVISIBLE
			&& Skill != AT_SKILL_PLASMA_STORM_FENRIR
			)
			return;
	}
	bool Wall = CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY);
	if(Wall)
	{
		if(SelectedCharacter != -1)
		{
			if(CharactersClient[SelectedCharacter].Object.Kind==KIND_PLAYER)
			{
				switch(Skill)
				{
				case AT_SKILL_HEAL_UP:
				case AT_SKILL_HEAL_UP+1:
				case AT_SKILL_HEAL_UP+2:
				case AT_SKILL_HEAL_UP+3:
				case AT_SKILL_HEAL_UP+4:
				case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_ATT_POWER_UP:
				case AT_SKILL_ATT_POWER_UP+1:
				case AT_SKILL_ATT_POWER_UP+2:
				case AT_SKILL_ATT_POWER_UP+3:
				case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_DEF_POWER_UP:
				case AT_SKILL_DEF_POWER_UP+1:
				case AT_SKILL_DEF_POWER_UP+2:
				case AT_SKILL_DEF_POWER_UP+3:
				case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_DEFENSE:
					UseSkillElf( c, o);
					return;
				}
			}
            if(CheckAttack())
            {
#ifdef ADD_SOCKET_ITEM
				// �÷��̾ Ȱ/������ �����Ͽ���, �ش� ��ų����
				if( ((Skill==AT_SKILL_PARALYZE) || (Skill==AT_SKILL_DEEPIMPACT))
					&& ((o->Type == MODEL_PLAYER) && (GetEquipedBowType( Hero ) != BOWTYPE_NONE ))
					)
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
					if( ( Skill==AT_SKILL_PARALYZE 
						|| Skill==AT_SKILL_DEEPIMPACT
						)
						&& o->Type==MODEL_PLAYER && 
						(( Hero->Weapon[0].Type>=MODEL_BOW+8  && Hero->Weapon[0].Type<MODEL_BOW+15 ) ||
						(( Hero->Weapon[1].Type>=MODEL_BOW    && Hero->Weapon[1].Type<MODEL_BOW+7 ) 
						|| Hero->Weapon[1].Type==MODEL_BOW+17 
						|| Hero->Weapon[1].Type==MODEL_BOW+20
						|| Hero->Weapon[1].Type == MODEL_BOW+21
						|| Hero->Weapon[1].Type == MODEL_BOW+22
						) ||
						(  Hero->Weapon[0].Type>=MODEL_BOW+16 && Hero->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX ) ) )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
					{
						UseSkillElf ( c, o );
					}
            }
		}
	}
	
	switch(Skill)
	{
	case AT_SKILL_INFINITY_ARROW:
		{
			//����ȭ�� ���°� �ƴ� ��츸 �� �� �ִ�. 
			if(g_isCharacterBuff((&Hero->Object), eBuff_InfinityArrow)==false)
			{
				SendRequestMagic(Skill,HeroKey);
				if((c->Helper.Type == MODEL_HELPER+37) 
					|| (c->Helper.Type == MODEL_HELPER+2)
					|| (c->Helper.Type == MODEL_HELPER+3)
					|| (c->Helper.Type == MODEL_HELPER+4))
					SetPlayerMagic(c);
				else
					SetAction(o,PLAYER_RUSH1);
				
				c->Movement = 0;
			}
		}
		break;
		
#ifdef HELLOWIN_EVENT
	case AT_SKILL_HELLOWIN_EVENT_1:
	case AT_SKILL_HELLOWIN_EVENT_2:
	case AT_SKILL_HELLOWIN_EVENT_3:
	case AT_SKILL_HELLOWIN_EVENT_4:
	case AT_SKILL_HELLOWIN_EVENT_5:
        SendRequestMagic ( Skill, HeroKey );
		//					SetPlayerMagic(c);
        c->Movement = 0;
		break;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	case AT_SKILL_RECOVER:
		{
			vec3_t Light,Position,P,dp;
									
			float Matrix[3][4];
			
			Vector(0.f,-220.f,130.f,P);
			AngleMatrix(o->Angle,Matrix);
			VectorRotate(P,Matrix,dp);
			VectorAdd(dp,o->Position,Position);
			Vector(0.7f, 0.6f, 0.f, Light);
			CreateEffect(BITMAP_IMPACT, Position, o->Angle, Light, 0,o);
			SetAction(o,PLAYER_RECOVER_SKILL);

#ifdef LDK_FIX_USE_RECOVER_TARGET_MONSTER
			// ȸ�� ��ų Ÿ�� ���� ���� : ���Ϳ��Դ� ��� ����
			if(SelectedCharacter > -1 && CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
#else //LDK_FIX_USE_RECOVER_TARGET_MONSTER
			if(SelectedCharacter > -1)
#endif //LDK_FIX_USE_RECOVER_TARGET_MONSTER
			{
				SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
			}
			else
			{
				SendRequestMagic(Skill,HeroKey);
			}
			//			UseSkillElf( c, o);
		}
		break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
		
#endif//HELLOWIN_EVENT
	case AT_SKILL_HEAL_UP:
	case AT_SKILL_HEAL_UP+1:
	case AT_SKILL_HEAL_UP+2:
	case AT_SKILL_HEAL_UP+3:
	case AT_SKILL_HEAL_UP+4:
	case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
		//#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
		//	case AT_SKILL_RECOVER:
		//#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	case AT_SKILL_DEFENSE:
		SendRequestMagic(Skill,HeroKey);
		SetPlayerMagic(c);
		return;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	case AT_SKILL_MULTI_SHOT:
		{
#ifdef KJH_FIX_MULTISHOT_RELOAD_ARROW
			// ȭ���ڵ�����
			if(!CheckArrow()) 
				break;
#endif // KJH_FIX_MULTISHOT_RELOAD_ARROW

			if (GetEquipedBowType_Skill() == BOWTYPE_NONE)	// Ȱ�� ���� Ȱ��ȭ
				return;
			o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
			
#ifdef PJH_SEASON4_FIX_MULTI_SHOT
			if( CheckTile( c, o, Distance ) )
			{
				BYTE PathX[1];
				BYTE PathY[1];
				PathX[0] = ( c->PositionX);
				PathY[0] = ( c->PositionY);
				SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
				
				BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
				
				BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
				WORD TKey = 0xffff;
				if ( g_MovementSkill.m_iTarget!=-1 )
				{
					TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
				}

				SendRequestMagicContinue(Skill,( c->PositionX),
					( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
				SetAttackSpeed();
				//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
				c->Movement = 0;
				//c->AttackTime = 15;
		
				
				SetPlayerBow(c);
				vec3_t Light,Position,P,dp;
				
				float Matrix[3][4];
				Vector(0.f,20.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				Vector(0.8f, 0.9f, 1.6f, Light);
				CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
				
				Vector(0.f,-20.f,0.f,P);
				Vector(0.f,0.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				
				Vector(0.f,20.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
				
				Vector(0.f,-120.f,145.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);

				short Key = -1;
                for( int i=0;i<MAX_CHARACTERS_CLIENT;i++ )
                {
                    CHARACTER *tc = &CharactersClient[i];
					if(tc == c)
					{
						Key = i;
						break;
					}
				}

				CreateEffect(MODEL_BLADE_SKILL, Position, o->Angle, Light, 1, o, Key);
				PlayBuffer(SOUND_SKILL_MULTI_SHOT);
			}
#else	// PJH_SEASON4_FIX_MULTI_SHOT

//������ �۾���

				if( CheckTile( c, o, Distance ) )
				{
					BYTE PathX[1];
					BYTE PathY[1];
					PathX[0] = ( c->PositionX);
					PathY[0] = ( c->PositionY);
					SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
							
					BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
							
					BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
					SetAttackSpeed();
					//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
					c->Movement = 0;
					//c->AttackTime = 15;
					
							
					SetPlayerBow(c);
					vec3_t Light,Position,P,dp,Angle;
							
					float Matrix[3][4];
					Vector(0.f,20.f,0.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					Vector(0.4f, 0.6f, 1.f, Light);
					CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
					CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
							
					Vector(0.f,-20.f,0.f,P);
					Vector(0.f,0.f,0.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
							
					CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
					CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
					CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
							
					Vector(0.f,20.f,0.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
					CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
							
					Vector(0.f,-120.f,130.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					CreateEffect(MODEL_BLADE_SKILL, Position, o->Angle, Light, 1);
							
					BYTE Skill = 0;
					//			CHARACTER *tc;
					OBJECT *to = NULL;
							
					VectorCopy(o->Angle,Angle);
					CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] + 8.f;
					CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] + 16.f;
					CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] - 8.f;
					CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] - 16.f;
					CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2];
					PlayBuffer(SOUND_SKILL_MULTI_SHOT);
				}
#endif //#ifdef PJH_SEASON4_FIX_MULTI_SHOT
		}
		break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
		
    case AT_SKILL_IMPROVE_AG:
		SendRequestMagic(Skill,HeroKey);
		SetPlayerMagic(c);
		c->Movement = 0;
        break;
		
		//^ �渱 ��ų ����
	case AT_SKILL_PLASMA_STORM_FENRIR:	// (����)
		{
			if ( CheckAttack() )
			{
				g_MovementSkill.m_iTarget = SelectedCharacter;
			}
			else
			{
				g_MovementSkill.m_iTarget = -1;
			}
			
			// ��� ���� ��� ��ǥ ���
			int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
			int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
			if( CheckTile( c, o, Distance ) )
			{
				BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
				WORD TKey = 0xffff;
				if(g_MovementSkill.m_iTarget != -1)
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					
					CheckSkillDelay(Hero->CurrentSkill);
					
					TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
					c->Movement = 0;
					
					if(o->Type == MODEL_PLAYER)
					{
						SetAction_Fenrir_Skill(c, o);
					}
				}
				else
				{
					c->m_iFenrirSkillTarget = -1;
				}
			}
			else
			{
				if(g_MovementSkill.m_iTarget != -1)
				{
					if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance*1.2f))
					{	// �ָ� �ɾ�� ���
						c->Movement = true;
					}
				}
				else
				{
					Attacking = -1;
				}
			}
		}	// case 
		break;
	}	// switch
}

void AttackKnight(CHARACTER *c, int Skill, float Distance)
{
	OBJECT *o = &c->Object;
    int ClassIndex = GetBaseClass ( c->Class );

	
	// ������ ��ų���� ���س��´�.
	int iMana, iSkillMana;
	GetSkillInformation( Skill, 1, NULL, &iMana, 
		NULL, &iSkillMana );

#ifdef YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE
	int iTypeL = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
	int iTypeR = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
#endif	// YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE
	
    // ��� ��ų�� ��� Į�� ���ϰ� �־���Ѵ�.
    // ��� ���������� Į�� ��� ����.
    if(
#ifdef YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE
		( ( iTypeR!=-1 && 
		( iTypeR<ITEM_STAFF || iTypeR>=ITEM_STAFF+MAX_ITEM_INDEX ) &&
		( iTypeL<ITEM_STAFF || iTypeL>=ITEM_STAFF+MAX_ITEM_INDEX ) ) 
#else	// YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE
		( ( Hero->Weapon[0].Type!=-1 && 
		( Hero->Weapon[0].Type<MODEL_STAFF || Hero->Weapon[0].Type>=MODEL_STAFF+MAX_ITEM_INDEX ) &&
		( Hero->Weapon[1].Type<MODEL_STAFF || Hero->Weapon[1].Type>=MODEL_STAFF+MAX_ITEM_INDEX ) ) 
#endif	// YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE
		|| Skill == AT_SKILL_VITALITY 
		|| Skill == AT_SKILL_ADD_CRITICAL 
		|| Skill == AT_SKILL_PARTY_TELEPORT 
		|| Skill == AT_SKILL_THUNDER_STRIKE 
		|| Skill == AT_SKILL_DARK_HORSE
		|| (AT_SKILL_LIFE_UP <= Skill && Skill <= AT_SKILL_LIFE_UP+4)
		|| (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4)
		|| Skill == AT_SKILL_BRAND_OF_SKILL
		|| Skill == AT_SKILL_PLASMA_STORM_FENRIR	// (���, ��ũ�ε�, ���˻�) �渱 ��ų
		|| Skill == AT_SKILL_DARK_SCREAM
#ifdef PJH_SEASON4_MASTER_RANK4
		|| (AT_SKILL_FIRE_SCREAM_UP <= Skill && Skill <= AT_SKILL_FIRE_SCREAM_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
#ifndef YDG_FIX_BLOCK_STAFF_WHEEL		// �����Ҷ� ������ �κ�
		|| Skill == AT_SKILL_WHEEL
		|| (AT_SKILL_TORNADO_SWORDA_UP <= Skill && Skill <= AT_SKILL_TORNADO_SWORDA_UP+4)
		|| (AT_SKILL_TORNADO_SWORDB_UP <= Skill && Skill <= AT_SKILL_TORNADO_SWORDB_UP+4)
#endif	// YDG_FIX_BLOCK_STAFF_WHEEL	// �����Ҷ� ������ �κ�
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
		|| Skill == AT_SKILL_GIGANTIC_STORM
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		|| Skill == AT_SKILL_GAOTIC
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		) )
    {
		bool Success = true;
		
        if ( Skill==AT_SKILL_PARTY_TELEPORT && PartyNumber<=0 )
        {
            Success = false;
        }
#ifdef PJH_FIX_4_BUGFIX_33
		if(g_csItemOption.Special_Option_Check() == false && (Skill == AT_SKILL_ICE_BLADE || (AT_SKILL_POWER_SLASH_UP<= Skill && AT_SKILL_POWER_SLASH_UP + 5 > Skill)))
			Success = false;
#endif //PJH_FIX_4_BUGFIX_33

#ifdef YDG_ADD_NEW_DUEL_UI
		if (Skill==AT_SKILL_PARTY_TELEPORT && g_DuelMgr.IsDuelEnabled())
		{
			Success = false;	// �����߿��� �Ÿս�ų�� ����Ҽ� ����
		}
#endif	// YDG_ADD_NEW_DUEL_UI
		
#ifdef YDG_ADD_DOPPELGANGER_UI
		if (Skill==AT_SKILL_PARTY_TELEPORT && (IsDoppelGanger1() || IsDoppelGanger2() || IsDoppelGanger3() || IsDoppelGanger4()))
		{
			Success = false;	// ���ð��� �̺�Ʈ������ �Ÿս�ų�� ����Ҽ� ����
		}
#endif	// YDG_ADD_DOPPELGANGER_UI
		
		if( Skill == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
		{
			BYTE t_DarkLife = 0;
			t_DarkLife  = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
			if(t_DarkLife == 0) Success = false;
		}
		
		if( InChaosCastle() )
		{
			//ī���� ĳ�������� ��ũ���Ǹ�, ��ũȣ��, ����Ʈ ��ų ���� ��� �Ұ���
			if( Skill == AT_SKILL_DARK_HORSE 
				|| (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4)
				|| Skill == AT_SKILL_RIDER
				|| ( Skill >= AT_PET_COMMAND_DEFAULT && Skill <= AT_PET_COMMAND_TARGET )
				|| Skill == AT_SKILL_PLASMA_STORM_FENRIR // (���, ��ũ�ε�, ���˻�)
				)
			{
				Success = false;
			}
		}
		else
		{
			//ī���� ĳ���� �ƴϴ��� �׾����� ��ų ��� �Ұ���
			if( Skill == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
			{
				BYTE t_DarkLife = 0;
				t_DarkLife  = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
				if(t_DarkLife == 0) Success = false;
			}
		}
		
		if ( iMana>CharacterAttribute->Mana )
		{
			int Index = g_pMyInventory->FindManaItemIndex();
			if(Index != -1)
			{
				SendRequestUse(Index, 0);
			}
			Success = false;
		}
		if ( Success && iSkillMana>CharacterAttribute->SkillMana )
		{
			Success = false;
		}
        if ( Success && !CheckSkillDelay( Hero->CurrentSkill ) )
        {
            Success = false;
        }
		
		int iEnergy;	// ���̳ʽ� ���� �۾�
		GetSkillInformation_Energy(Skill, &iEnergy);
		if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
		{
			Success = false;
		}
		if(ClassIndex == CLASS_DARK_LORD)	// ��ũ�ε��̸�
		{
			int iCharisma;
			GetSkillInformation_Charisma(Skill, &iCharisma);	// �������Ʈ 
			if(iCharisma > (CharacterAttribute->Charisma + CharacterAttribute->AddCharisma) )
			{
				Success = false;
			}
		}
		
        if ( Success )
        {
            //  ��ų.
            switch(Skill)
            {
			case AT_SKILL_TORNADO_SWORDA_UP:
			case AT_SKILL_TORNADO_SWORDA_UP+1:
			case AT_SKILL_TORNADO_SWORDA_UP+2:
			case AT_SKILL_TORNADO_SWORDA_UP+3:
			case AT_SKILL_TORNADO_SWORDA_UP+4:
				
			case AT_SKILL_TORNADO_SWORDB_UP:
			case AT_SKILL_TORNADO_SWORDB_UP+1:
			case AT_SKILL_TORNADO_SWORDB_UP+2:
			case AT_SKILL_TORNADO_SWORDB_UP+3:
			case AT_SKILL_TORNADO_SWORDB_UP+4:
            case AT_SKILL_WHEEL:    //  ȸ���� ����.
                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
				{
					BYTE PathX[1];
					BYTE PathY[1];
					PathX[0] = ( c->PositionX);
					PathY[0] = ( c->PositionY);
					SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);

                    WORD TKey = 0xffff;
                    if ( g_MovementSkill.m_iTarget!=-1 )
                    {
                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                    }
                    SendRequestMagicContinue(Skill,( c->PositionX),
                        ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, 0);
                    SetAttackSpeed();
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
					switch(c->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
						break;
					default:	// �⺻
						SetAction(o, PLAYER_ATTACK_SKILL_WHEEL);
						break;
					}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
					SetAction(o,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                    c->Movement = 0;
                }
                break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOOD_ATT_UP:		// ������ð�ȭ
			case AT_SKILL_BLOOD_ATT_UP+1:
			case AT_SKILL_BLOOD_ATT_UP+2:
			case AT_SKILL_BLOOD_ATT_UP+3:
			case AT_SKILL_BLOOD_ATT_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
            case AT_SKILL_REDUCEDEFENSE:	// �������	
                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                {
#ifdef PSW_FRUIT_ITEM_CHECK_SKILL
					WORD Strength;
					const WORD notStrength = 596;
					Strength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
					if(Strength < notStrength)
					{
						break;
					}
#endif //PSW_FRUIT_ITEM_CHECK_SKILL
					
#ifdef PJH_FIX_BLOOD_ATTCK
					if( CheckTile( c, o, Distance ) )
#endif //PJH_FIX_BLOOD_ATTCK
                    {
                        BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
						
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), byValue, 0, TKey, 0);
                        SetAttackSpeed();
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
						switch(c->Helper.Type)
						{
						case MODEL_HELPER+2:	// ���ϸ���
							SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_UNI);
							break;
						case MODEL_HELPER+3:	// ����Ʈ
							SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_DINO);
							break;
						case MODEL_HELPER+37:	// �渱	
							SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
							break;
						default:	// �⺻
							SetAction(o, PLAYER_ATTACK_SKILL_WHEEL);
							break;
						}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
						SetAction(o,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                        c->Movement = 0;
                    }
                }
                break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_POWER_SLASH_UP:
			case AT_SKILL_POWER_SLASH_UP+1:
			case AT_SKILL_POWER_SLASH_UP+2:
			case AT_SKILL_POWER_SLASH_UP+3:
			case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4                            
            case AT_SKILL_ICE_BLADE:
                if ( c->Helper.Type<MODEL_HELPER+2 || c->Helper.Type>MODEL_HELPER+4
					&& c->Helper.Type != MODEL_HELPER+37
					)
                {
					/*
#ifdef PJH_SEASON4_MASTER_RANK4
								bool jd = true;
								for(int j=0;j<2;j++)
								{
									if(Hero->Weapon[j].Type==MODEL_SWORD+21||Hero->Weapon[j].Type==MODEL_SWORD+23||Hero->Weapon[j].Type==MODEL_SWORD+28||
										Hero->Weapon[j].Type==MODEL_SWORD+25||Hero->Weapon[j].Type==MODEL_SWORD+31
										)	//21 = �������̵�,23 = �ͽ��÷������̵�,25 = �ҵ��,28 = ��ٽ�Ÿ��,31 = ������ε�
									{
										jd = false;
									}
								}
								if(jd == true)
									return;
#endif //PJH_SEASON4_MASTER_RANK4                        
									*/
                    o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                    
                    if( CheckTile( c, o, Distance ) )
                    {
						BYTE PathX[1];
						BYTE PathY[1];
						PathX[0] = ( c->PositionX);
						PathY[0] = ( c->PositionY);
						SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
						
                        BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
						
                        BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                        SetAttackSpeed();
						if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
						{
							SetAction(o,PLAYER_ATTACK_TWO_HAND_SWORD_TWO);
						}
                        c->Movement = 0;
                    }
                }
                break;
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
			case AT_SKILL_GAOTIC:
                {
                    o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                    
                    if( CheckTile( c, o, Distance ) )
                    {
						BYTE PathX[1];
						BYTE PathY[1];
						PathX[0] = ( c->PositionX);
						PathY[0] = ( c->PositionY);
						SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
						
                        BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
						
                        BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
#ifdef PJH_FIX_CAOTIC
							if(TKey == 0xffff)
							{
								CHARACTER *st = &CharactersClient[g_MovementSkill.m_iTarget];
								TKey = st->Key;
							}
#endif //#ifdef PJH_FIX_CAOTIC		
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                        SetAttackSpeed();
						//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
                        c->Movement = 0;
						
//									SetPlayerMagic(c);
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
						if( c->Helper.Type == MODEL_HELPER+37 )				
						{
							SetAction( o, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
						}
#ifdef PBG_FIX_CHAOTIC_ANIMATION
						else if((c->Helper.Type>=MODEL_HELPER+2) && (c->Helper.Type<=MODEL_HELPER+4))
#else //PBG_FIX_CHAOTIC_ANIMATION
						else if((c->Helper.Type>=MODEL_HELPER+2) || (c->Helper.Type<=MODEL_HELPER+4))
#endif //PBG_FIX_CHAOTIC_ANIMATION
						{
							SetAction( o, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
						}
						else
						{
							SetAction( o, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
						}
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
						if(c->Helper.Type == MODEL_HELPER+37)
							SetAction(o,PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	//^ �渱
						else
							SetAction ( o, PLAYER_ATTACK_STRIKE );
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
						vec3_t Light,Position,P,dp;
						
						float Matrix[3][4];
						Vector(0.f,-20.f,0.f,P);
						Vector(0.f,0.f,0.f,P);
						AngleMatrix(o->Angle,Matrix);
						VectorRotate(P,Matrix,dp);
						VectorAdd(dp,o->Position,Position);
						
						Vector(0.5f, 0.5f, 0.5f, Light);
						for (int i = 0; i < 5; ++i)
						{
							CreateEffect(BITMAP_SHINY+6, Position, o->Angle, Light, 3, o, -1, 0, 0, 0, 0.5f);
						}
						
						VectorCopy(o->Position,Position);
#ifdef _VS2008PORTING
						for(int i=0;i<8;i++)
#else // _VS2008PORTING
						for(i=0;i<8;i++)
#endif // _VS2008PORTING
						{
							Position[0] = (o->Position[0] - 119.f) + (float)(rand()%240); 
							Position[2] = (o->Position[2] + 49.f) + (float)(rand()%60); 
							CreateJoint(BITMAP_2LINE_GHOST,Position,o->Position,o->Angle,0,o,20.f,o->PKKey,0,o->m_bySkillSerialNum);//Ŭ���̾�Ʈ����ó��
						}
#ifdef PJH_FIX_CAOTIC
						if(c==Hero && SelectedCharacter!=-1)
						{
							vec3_t Pos;
							CHARACTER *sc = &CharactersClient[SelectedCharacter];
							VectorCopy(sc->Object.Position,Pos);
							CreateBomb(Pos,true,6);
						}
#endif //PJH_FIX_CAOTIC
#ifdef YDG_FIX_CAOTIC_SOUND_MISSING
						PlayBuffer(SOUND_SKILL_CAOTIC);
#endif	// YDG_FIX_CAOTIC_SOUND_MISSING
                    }
					else
					{	// �־������� �� �ȱ�
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
						{	
							c->Movement = true;		// �ָ� �ɾ�� ���
						}
					}
                }
				break;
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
            case AT_SKILL_FLAME_STRIKE:
                {
                    o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                    
                    if( CheckTile( c, o, Distance ) )
                    {
						BYTE PathX[1];
						BYTE PathY[1];
						PathX[0] = ( c->PositionX);
						PathY[0] = ( c->PositionY);
						SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
						
                        BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
						
                        BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                        SetAttackSpeed();
						SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
                        c->Movement = 0;
                        //c->AttackTime = 15;
                    }
                }
                break;
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
            case AT_SKILL_GIGANTIC_STORM:
                {
                    o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                    
                    if( CheckTile( c, o, Distance ) )
                    {
						BYTE PathX[1];
						BYTE PathY[1];
						PathX[0] = ( c->PositionX);
						PathY[0] = ( c->PositionY);
						SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
						
                        BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
						
                        BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                        SetAttackSpeed();
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
						switch(c->Helper.Type)
						{
						case MODEL_HELPER+2:	// ���ϸ���
							SetAction(o, PLAYER_SKILL_GIGANTICSTORM_UNI);
							break;
						case MODEL_HELPER+3:	// ����Ʈ
							SetAction(o, PLAYER_SKILL_GIGANTICSTORM_DINO);
							break;
						case MODEL_HELPER+37:	// �渱	
							SetAction(o, PLAYER_SKILL_GIGANTICSTORM_FENRIR);
							break;
						default:	// �⺻
							SetAction(o, PLAYER_SKILL_GIGANTICSTORM);
							break;
						}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
						SetAction(o, PLAYER_SKILL_GIGANTICSTORM);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                        c->Movement = 0;
                    }
                }
                break;
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
				
            case AT_SKILL_PARTY_TELEPORT:
				if( g_CursedTemple->IsCursedTemple() 
					&& !g_pMyInventory->IsItem( ITEM_POTION+64, true ) )
				{
					return;
				}
                SendRequestMagic ( Skill, HeroKey );
                c->Movement = 0;
                break;
                
            case AT_SKILL_ADD_CRITICAL:
                SendRequestMagic ( Skill, HeroKey );
				c->Movement = 0;
                break;
            case AT_SKILL_BRAND_OF_SKILL:
                SendRequestMagic ( Skill, HeroKey );
                c->Movement = 0;
                break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_FIRE_SCREAM_UP:
			case AT_SKILL_FIRE_SCREAM_UP+1:
			case AT_SKILL_FIRE_SCREAM_UP+2:
			case AT_SKILL_FIRE_SCREAM_UP+3:
			case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_DARK_SCREAM:
                if ( CheckTile( c, o, Distance ) )
                {
                    int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                    int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                    
                    BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                    WORD TKey = 0xffff;
                    if ( g_MovementSkill.m_iTarget!=-1 )
                    {
                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                    }
                    o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
					CheckClientArrow(o);
                    SendRequestMagicContinue ( Skill, ( c->PositionX),
                        ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
					
                    SetAttackSpeed();
                    //  �ִϸ��̼� ����.
                    {
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
						if ( (c->Helper.Type>=MODEL_HELPER+2 && c->Helper.Type<=MODEL_HELPER+4) && !c->SafeZone )
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
                        if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )   
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
                        {
                            SetAction ( o, PLAYER_ATTACK_RIDE_STRIKE );
                        }
						else if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
						{
							SetAction ( o, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );
						}
                        else
                        {
                            SetAction ( o, PLAYER_ATTACK_STRIKE );
                        }
                    }
                    c->Movement = 0;
                }
                else
                {
                    Attacking = -1;
                }
				break;
			case AT_SKILL_ASHAKE_UP:
			case AT_SKILL_ASHAKE_UP+1:
			case AT_SKILL_ASHAKE_UP+2:
			case AT_SKILL_ASHAKE_UP+3:
			case AT_SKILL_ASHAKE_UP+4:
            case AT_SKILL_DARK_HORSE:
                if ( c->Helper.Type!=MODEL_HELPER+4 || c->SafeZone ) break;
				
            case AT_SKILL_THUNDER_STRIKE:
                // ��� ���� ��� ��ǥ ���
                // ��� ���� ��� ��ǥ ���
                if ( CheckTile( c, o, Distance ) )
                {
                    int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                    int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                    
                    BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                    WORD TKey = 0xffff;
                    if ( g_MovementSkill.m_iTarget!=-1 )
                    {
                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                    }
                    o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                    SendRequestMagicContinue ( Skill, ( c->PositionX),
                        ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
                    SetAttackSpeed();
                    
                    //  �ִϸ��̼� ����.
                    if ( Skill==AT_SKILL_THUNDER_STRIKE )
                    {
                        if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )   
                        {
                            SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_FLASH );
                        }
						else if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
						{
							SetAction ( o, PLAYER_FENRIR_ATTACK_DARKLORD_FLASH );
						}
                        else
                        {
                            SetAction ( o, PLAYER_SKILL_FLASH );
                        }
                    }
                    else if ( Skill==AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
                    {
                        SetAction ( o, PLAYER_ATTACK_DARKHORSE );
                        PlayBuffer ( SOUND_EARTH_QUAKE );
                    }
                    c->Movement = 0;
                }
                else
                {
                    Attacking = -1;
                }
                break;
			case AT_SKILL_LIFE_UP:
			case AT_SKILL_LIFE_UP+1:
			case AT_SKILL_LIFE_UP+2:
			case AT_SKILL_LIFE_UP+3:
			case AT_SKILL_LIFE_UP+4:
            case AT_SKILL_VITALITY:	// ����������
                SendRequestMagic(Skill,HeroKey);
				SetAction(o,PLAYER_SKILL_VITALITY);
                c->Movement = 0;
                break;
				
				//--------------------------------------------------------------------------------------------------------------------
				
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ANGER_SWORD_UP:
			case AT_SKILL_ANGER_SWORD_UP+1:
			case AT_SKILL_ANGER_SWORD_UP+2:
			case AT_SKILL_ANGER_SWORD_UP+3:
			case AT_SKILL_ANGER_SWORD_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4                            
            case AT_SKILL_FURY_STRIKE:  //  ���� - �г��� �ϰ�
                {
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					
                    // ��� ���� ��� ��ǥ ���
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
                    int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                    int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
                    if( CheckTile( c, o, Distance ) )
                    {
                        BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill,( c->PositionX),
                            ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, 0);
						SetAction(o,PLAYER_ATTACK_SKILL_FURY_STRIKE);
                        c->Movement = 0;
                    }
                    else
                    {
                        Attacking = -1;
                    }
                }
                break;
				
				//--------------------------------------------------------------------------------------------------------------------
				
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
				// ���� - �ı��� �ϰ�
			case AT_SKILL_BLOW_OF_DESTRUCTION:
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					
                    // ��� ���� ��� ��ǥ ���
                    int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                    int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                    if( CheckTile( c, o, Distance ) )
                    {
                        BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
                        WORD TKey = 0xffff;
                        if ( g_MovementSkill.m_iTarget!=-1 )
                        {
                            TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                        }
                        SendRequestMagicContinue(Skill, TargetX, TargetY, (BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, 0);
						SetAction(o,PLAYER_SKILL_BLOW_OF_DESTRUCTION);
                        c->Movement = 0;
                    }
                    else
                    {
                        Attacking = -1;
                    }
				}
				break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
				
				//--------------------------------------------------------------------------------------------------------------------
				
				//^ �渱 ��ų ����
			case AT_SKILL_PLASMA_STORM_FENRIR: // (���, ��ũ�ε�, ���˻�)
				{
					// ��� ���� ��� ��ǥ ���
					int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
					int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
					if( CheckTile( c, o, Distance ) )
					{
						
						BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
						WORD TKey = 0xffff;
						if(g_MovementSkill.m_iTarget!=-1)
						{
							o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
							
							CheckSkillDelay(Hero->CurrentSkill);
							
							TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
							c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
							SendRequestMagicContinue(Skill,( c->PositionX),
								( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
							c->Movement = 0;
							
							if(o->Type == MODEL_PLAYER)
							{
								SetAction_Fenrir_Skill(c, o);
							}
						}
						else
						{
							c->m_iFenrirSkillTarget = -1;
						}
					}
					else
					{
						if(g_MovementSkill.m_iTarget != -1)
						{
							if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance*1.2f))
							{	// �ָ� �ɾ�� ���
								c->Movement = true;
							}
						}
						else
						{
							Attacking = -1;
						}
					}
				}	// case
				break;
            } // switch
        }
    }
}

void AttackWizard(CHARACTER *c, int Skill, float Distance)
{
	OBJECT *o = &c->Object;
    int ClassIndex = GetBaseClass ( c->Class );

	int iMana, iSkillMana;
	if( Skill == AT_SKILL_BLAST_HELL_BEGIN || Skill == AT_SKILL_BLAST_HELL )
	{
		GetSkillInformation( AT_SKILL_BLAST_HELL, 1, NULL, &iMana, NULL, &iSkillMana);
		
        if ( Skill==AT_SKILL_BLAST_HELL )
        {
			iSkillMana = 0;
        }
	}
	else
	{
		GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
	}
	
	int iEnergy;	// ���̳ʽ� ���� �۾�
	GetSkillInformation_Energy(Skill, &iEnergy);
	if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
	{
		return;
	}
	
	if(iMana > CharacterAttribute->Mana)
	{
		int Index = g_pMyInventory->FindManaItemIndex();
		if(Index != -1)
		{
			SendRequestUse(Index, 0);
		}
		return;
	}

	// skillmana ����
	if(iSkillMana > CharacterAttribute->SkillMana)
	{
		if ( Skill==AT_SKILL_BLAST_HELL_BEGIN || Skill==AT_SKILL_BLAST_HELL )
        {
			MouseRButtonPop = false;
			MouseRButtonPush= false;
			MouseRButton	= false;
			
			MouseRButtonPress = 0;
        }
		return;
	}
	
    if ( CheckSkillDelay( Hero->CurrentSkill ) == false)
    {
        return;
    }
    bool Success = CheckTarget(c);

	switch(Skill)
	{
		//	����2 �غ��ڼ�.
	case AT_SKILL_BLAST_HELL_BEGIN:
		{
			SendRequestMagic ( Skill, HeroKey );
			
			SetAttackSpeed();
			SetAction(o,PLAYER_SKILL_HELL_BEGIN);
			c->Movement = 0;
		}
		return;
		
		//	����2 �߻�.
	case AT_SKILL_BLAST_HELL:
		{
			int iTargetKey = getTargetCharacterKey(c, SelectedCharacter);
			if(iTargetKey == -1) {
				iTargetKey = HeroKey;
			}
			SendRequestMagic(Skill,iTargetKey);
			
			SetAttackSpeed();
			SetAction(o,PLAYER_SKILL_HELL_START);
			c->Movement = 0;
		}
		return;
	case AT_SKILL_SOUL_UP:
	case AT_SKILL_SOUL_UP+1:
	case AT_SKILL_SOUL_UP+2:
	case AT_SKILL_SOUL_UP+3:
	case AT_SKILL_SOUL_UP+4:
	case AT_SKILL_WIZARDDEFENSE:
		if( SelectedCharacter != -1)
		{
			if ( CharactersClient[SelectedCharacter].Object.Kind!=KIND_PLAYER)
			{
				Attacking = -1;
				return;
			}
			else
			{
                //  ��Ƽ���ΰ�.
				if ( !g_pPartyManager->IsPartyMember( SelectedCharacter ) ) 
						return;
					
					c->TargetCharacter = SelectedCharacter;
					
					if ( SelectedCharacter != -1)
					{
						ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
						g_MovementSkill.m_bMagic = TRUE;
						g_MovementSkill.m_iSkill = Hero->CurrentSkill;
						g_MovementSkill.m_iTarget = SelectedCharacter;
					}
					
					if(!CheckTile(c,o, Distance))
					{
						if(SelectedCharacter != -1)
						{
							if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
							{
								c->Movement = true;
								c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
								SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
							}
						}
						
						return;
					}
					
					SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
			}
		}
		else
		{
			SendRequestMagic(Skill,HeroKey);
		}
		SetPlayerMagic(c);
		break;
	case AT_SKILL_HELL_FIRE_UP:
	case AT_SKILL_HELL_FIRE_UP+1:
	case AT_SKILL_HELL_FIRE_UP+2:
	case AT_SKILL_HELL_FIRE_UP+3:
	case AT_SKILL_HELL_FIRE_UP+4:
	case AT_SKILL_HELL:
		{
			SendRequestMagicContinue(Skill,( c->PositionX),
				( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
			SetAttackSpeed();
			SetAction(o,PLAYER_SKILL_HELL);
			c->Movement = 0;
		}
		return;
	case AT_SKILL_INFERNO:
		{
			SendRequestMagicContinue(Skill,( c->PositionX),
				( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
			SetAttackSpeed();
			SetAction(o,PLAYER_SKILL_INFERNO);
			c->Movement = 0;
		}
		return;
		//^ �渱 ��ų ����
	case AT_SKILL_PLASMA_STORM_FENRIR:	// (������)
		{
			if ( CheckAttack() )
			{
				g_MovementSkill.m_iTarget = SelectedCharacter;
			}
			else
			{
				g_MovementSkill.m_iTarget = -1;
			}
			
			// ��� ���� ��� ��ǥ ���
			int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
			int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
			if( CheckTile( c, o, Distance ) )//&& CheckAttack())
			{
				BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
				WORD TKey = 0xffff;
				if ( g_MovementSkill.m_iTarget != -1 )
				{
					o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
					
					CheckSkillDelay(Hero->CurrentSkill);
					
					TKey = getTargetCharacterKey(c, g_MovementSkill.m_iTarget);
					c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
					c->Movement = 0;
					
					if(o->Type == MODEL_PLAYER)
					{
						SetAction_Fenrir_Skill(c, o);
					}
				}
				else
				{
					c->m_iFenrirSkillTarget = -1;
				}
			}
			else
			{
				if(g_MovementSkill.m_iTarget != -1)
				{
					if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance*1.2f ) )
					{	// �ָ� �ɾ�� ���
						c->Movement = true;
					}
				}
				else
				{
					Attacking = -1;
				}
			}
		}
		return;
		
        //  ���� ��ų�� ����.
    case AT_SKILL_BLOCKING :
    case AT_SKILL_SWORD1 :
    case AT_SKILL_SWORD2 :
    case AT_SKILL_SWORD3 :
    case AT_SKILL_SWORD4 :
    case AT_SKILL_SWORD5 :
    case AT_SKILL_SPEAR:
		return;
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	case AT_SKILL_SWELL_OF_MAGICPOWER:		// ��������
		{
			// �������� ��ų������ �ȵǾ� �������� ��������
			if(g_isCharacterBuff((&Hero->Object), eBuff_SwellOfMagicPower) == false)
			{
				SendRequestMagic(Skill, HeroKey);
				
				c->Movement = 0;
			}
		}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	}
	
	if ( SelectedCharacter != -1)
	{
		ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
		g_MovementSkill.m_bMagic = TRUE;
		g_MovementSkill.m_iSkill = Hero->CurrentSkill;
		if ( CheckAttack() )
		{
			g_MovementSkill.m_iTarget = SelectedCharacter;
		}
		else
		{
			g_MovementSkill.m_iTarget = -1;
		}
	}
	
	if(!CheckTile(c,o, Distance ))
	{
		if(SelectedCharacter != -1 && CheckAttack())
		{
			if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
			{
				c->Movement = true;
				c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
				SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
			}
		}

		// �Ʒ� ��ų���� Ŭ�� �� ��ų ���� üũ ����.(�� ���⼭ �ϴ���...�Ѥ�;)
		if (Skill != AT_SKILL_STUN && Skill != AT_SKILL_REMOVAL_STUN
			&& Skill != AT_SKILL_MANA && Skill != AT_SKILL_INVISIBLE
			&& Skill != AT_SKILL_REMOVAL_INVISIBLE && Skill != AT_SKILL_PLASMA_STORM_FENRIR	// (������)
#ifdef ASG_ADD_SKILL_BERSERKER
			&& Skill != AT_SKILL_ALICE_BERSERKER
#endif	// ASG_ADD_SKILL_BERSERKER
			&& Skill != AT_SKILL_ALICE_WEAKNESS && Skill != AT_SKILL_ALICE_ENERVATION
			)
			return;
	}
	
	bool Wall = CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY);
	if(Wall)
	{
		if(SelectedCharacter != -1)
		{
			if(CheckAttack())
			{
				UseSkillWizard( c, o);
			}
		}
		if(Success)
		{
			o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
			switch(Skill)
			{
			case AT_SKILL_STORM:
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_EVIL_SPIRIT_UP:	//�Ƿɰ�ȭ(�渶�����)
			case AT_SKILL_EVIL_SPIRIT_UP+1:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP+2:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP+3:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP+4:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP_M:		//�Ƿɰ�ȭ(���˻��)
			case AT_SKILL_EVIL_SPIRIT_UP_M+1:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP_M+2:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP_M+3:	//�Ƿɰ�ȭ
			case AT_SKILL_EVIL_SPIRIT_UP_M+4:	//�Ƿɰ�ȭ
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_EVIL:
				{
#ifdef CSK_EVIL_SKILL
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, &o->m_bySkillSerialNum );
#else // CSK_EVIL_SKILL
					SendRequestMagicContinue(Skill,( c->PositionX), ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, &o->m_bySkillSerialNum);
#endif // CSK_EVIL_SKILL
					
					SetPlayerMagic(c);
				}
				return;
			case AT_SKILL_FLASH:
				{
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
					SetAttackSpeed();
					
					if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)	//^ �渱 ĳ���� ���ϸ��̼� ����(������÷���)
						SetAction(o,PLAYER_SKILL_FLASH);
					else
						SetAction(o,PLAYER_SKILL_FLASH);
					
					c->Movement = 0;
					StandTime = 0;
				}
				return;
			case AT_SKILL_FLAME:
				SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
				SetPlayerMagic(c);
				return;
			case AT_SKILL_BLAST_POISON:
			case AT_SKILL_ICE_UP:
			case AT_SKILL_ICE_UP+1:
			case AT_SKILL_ICE_UP+2:
			case AT_SKILL_ICE_UP+3:
			case AT_SKILL_ICE_UP+4:
			case AT_SKILL_BLAST_FREEZE:
				{
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, 0 );
					SetPlayerMagic(c);
					c->Movement = 0;
				}
				return;
			}
		}
	}
	if ( ClassIndex==CLASS_WIZARD && Success)
	{
		switch(Skill)
		{
        case AT_SKILL_TELEPORT_B:
			if( g_CursedTemple->IsCursedTemple() 
				&& !g_pMyInventory->IsItem( ITEM_POTION+64, true ) )
			{
				return;
			}
            if ( SelectedCharacter!=-1 )
            {			
				//  ��Ƽ���ΰ�.
				if ( !g_pPartyManager->IsPartyMember( SelectedCharacter ) ) 
					return;
				
				if (SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
				{	// �������� ��� ������ �ڷ���Ʈ���� ���Ѵ�.
					return;
				}
				
				CHARACTER* tc = &CharactersClient[SelectedCharacter];
				OBJECT*    to = &tc->Object;
				bool Success = false;
				if(to->Type == MODEL_PLAYER)
				{
					if(to->CurrentAction != PLAYER_SKILL_TELEPORT)
						Success = true;
				}
				else
				{
					if(to->CurrentAction != MONSTER01_SHOCK)
						Success = true;
				}
				if(Success && to->Teleport!=TELEPORT_BEGIN && to->Teleport!=TELEPORT && to->Alpha>=0.7f)
				{
					int Wall, indexX, indexY, TargetIndex, count=0;
					int PositionX = (int)(c->Object.Position[0]/TERRAIN_SCALE);
					int PositionY = (int)(c->Object.Position[1]/TERRAIN_SCALE);
					
					while ( 1 )
					{
						indexX = rand()%3;
						indexY = rand()%3;
						
						if ( indexX!=1 || indexY!=1 )
						{
							TargetX = (PositionX-1)+indexX;
							TargetY = (PositionY-1)+indexY;
							
							TargetIndex = TERRAIN_INDEX( TargetX, TargetY );
							
							Wall = TerrainWall[TargetIndex];
							//  
							if ( (Wall&TW_ACTION)==TW_ACTION )
							{
								Wall -= TW_ACTION;
							}
							if(World == WD_30BATTLECASTLE)
							{
								int ax = (Hero->PositionX);
								int ay = (Hero->PositionY);
								if ( (ax>=150 && ax<=200) && (ay>=180&& ay<=230))  
									Wall = 0;
							}
							if(Wall == 0) break;
							
							count++;
						}
						
						if ( count>10 ) return;
					}
					to->Angle[2] = CreateAngle(to->Position[0],to->Position[1],tc->TargetPosition[0],tc->TargetPosition[1]);
					bool bResult;
					SendRequestMagicTeleportB(&bResult,tc->Key,TargetX,TargetY);
					if ( bResult )
					{
						SetPlayerTeleport(tc);
					}
				}
            }
            return;
			
		case AT_SKILL_TELEPORT:	//�渶��������̵�
            {
				if ( SEASON3B::CNewUIInventoryCtrl::GetPickedItem()			// �������� ��� ������ �ڷ���Ʈ���� ���Ѵ�.				
					|| g_isCharacterBuff(o, eDeBuff_Stun)
					|| g_isCharacterBuff(o, eDeBuff_Sleep)
					)
				{	
					return;
				}

#ifdef CSK_FIX_WOPS_K29010_HELLBUST
#ifdef PBG_ADD_NEWCHAR_MONK
				WORD byHeroPriorSkill = g_pSkillList->GetHeroPriorSkill();
#else //PBG_ADD_NEWCHAR_MONK
				BYTE byHeroPriorSkill = g_pSkillList->GetHeroPriorSkill();
#endif //PBG_ADD_NEWCHAR_MONK
				if(c == Hero && byHeroPriorSkill == AT_SKILL_BLAST_HELL)
				{
					g_pSkillList->SetHeroPriorSkill(AT_SKILL_TELEPORT);
					SendRequestMagic ( byHeroPriorSkill, HeroKey );
					SetAttackSpeed();
					SetAction(&Hero->Object, PLAYER_SKILL_HELL_BEGIN);
					Hero->Movement = 0;
					return;
				}
#endif // CSK_FIX_WOPS_K29010_HELLBUST

				bool Success = false;
				if(o->Type == MODEL_PLAYER)
				{
					if(o->CurrentAction != PLAYER_SKILL_TELEPORT)
						Success = true;
				}
				else
				{
					if(o->CurrentAction != MONSTER01_SHOCK)
						Success = true;
				}
				if(Success && o->Teleport!=TELEPORT_BEGIN && o->Teleport!=TELEPORT && o->Alpha>=0.7f)
				{
					int TargetIndex = TERRAIN_INDEX_REPEAT(TargetX,TargetY);
                    int Wall = TerrainWall[TargetIndex];
                    if ( (Wall&TW_ACTION)==TW_ACTION ) Wall -= TW_ACTION;
                    if ( (Wall&TW_HEIGHT)==TW_HEIGHT ) Wall -= TW_HEIGHT;
					if(Wall == 0)
					{
						o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
						bool bResult;
						SendRequestMagicTeleport(&bResult,0,TargetX,TargetY);
						if ( bResult)
						{
							if(g_isCharacterBuff(o, eDeBuff_Stun))
							{
								UnRegisterBuff( eDeBuff_Stun, o );
							}
							
							if(g_isCharacterBuff(o, eDeBuff_Sleep))
							{
								UnRegisterBuff( eDeBuff_Sleep, o );
							}
							
							SetPlayerTeleport(c);
						}
					}
				}
            }
			return;
		}
	}
	else if ( ClassIndex==CLASS_SUMMONER && Success)
	{
		if (g_SummonSystem.SendRequestSummonSkill(Skill, c, o) == TRUE)
		{
			return;
		}
		
		int iEnergy;
		GetSkillInformation_Energy(Skill, &iEnergy);
		if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy) )
		{
			return;
		}
		
		g_MovementSkill.m_bMagic = TRUE;
		g_MovementSkill.m_iSkill = Hero->CurrentSkill;
		g_MovementSkill.m_iTarget = SelectedCharacter;
		
		switch(Skill)
		{
		case AT_SKILL_ALICE_THORNS:		// ������ �ݻ�(���� �迭) �������Ը� ���
			{
				// �ƹ��͵� ������ �ȵǾ����� �ڱ� �ڽſ��� ���
				if(SelectedCharacter == -1 || CharactersClient[SelectedCharacter].Object.Kind != KIND_PLAYER)
				{
					LetHeroStop();
					// ���� ����
					switch(c->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(o, PLAYER_SKILL_SLEEP_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(o, PLAYER_SKILL_SLEEP_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(o, PLAYER_SKILL_SLEEP_FENRIR);
						break;
					default:	// �⺻
						SetAction(o, PLAYER_SKILL_SLEEP);
						break;
					}
					SendRequestMagic(Skill, HeroKey);
				}
				// ���� �ʾҰų� �÷��̾��� ���
				else if(0 == CharactersClient[SelectedCharacter].Dead && CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
				{	
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					
					if(CheckTile( c, o, Distance ) && c->SafeZone == false)
					{
						bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
						if(bNoneWall)
						{
							UseSkillSummon(c, o);
						}
					}
					else
					{	// �־������� �� �ȱ�
						if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
						{	
							c->Movement = true;		// �ָ� �ɾ�� ���
						}
					}
				}
			}
			break;
#ifdef ASG_ADD_SKILL_BERSERKER
		case AT_SKILL_ALICE_BERSERKER:
#endif	// ASG_ADD_SKILL_BERSERKER
		case AT_SKILL_ALICE_WEAKNESS:
		case AT_SKILL_ALICE_ENERVATION:
			UseSkillSummon(c, o);
			break;
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_LIGHTNING_SHOCK_UP:
		case AT_SKILL_LIGHTNING_SHOCK_UP+1:
		case AT_SKILL_LIGHTNING_SHOCK_UP+2:
		case AT_SKILL_LIGHTNING_SHOCK_UP+3:
		case AT_SKILL_LIGHTNING_SHOCK_UP+4:
#endif
		case AT_SKILL_LIGHTNING_SHOCK:
			{
				o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
				
				if( CheckTile( c, o, Distance ) )
				{
					BYTE PathX[1];
					BYTE PathY[1];
					PathX[0] = ( c->PositionX);
					PathY[0] = ( c->PositionY);
					SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
					
					BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
					
					BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
					WORD TKey = 0xffff;
					if ( g_MovementSkill.m_iTarget!=-1 )
					{
						TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
					}
					SendRequestMagicContinue(Skill,( c->PositionX),
						( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
					SetAttackSpeed();
					SetAction(o, PLAYER_SKILL_LIGHTNING_SHOCK);
					c->Movement = 0;
				}
			}
			break;
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
		}
		
		if(SelectedCharacter == -1)
		{
			return;
		}
		
		switch(Skill)
		{
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_DRAINLIFE_UP:
		case AT_SKILL_ALICE_DRAINLIFE_UP+1:
		case AT_SKILL_ALICE_DRAINLIFE_UP+2:
		case AT_SKILL_ALICE_DRAINLIFE_UP+3:
		case AT_SKILL_ALICE_DRAINLIFE_UP+4:
#endif
		case AT_SKILL_ALICE_DRAINLIFE:
		case AT_SKILL_ALICE_LIGHTNINGORB:
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+1:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+2:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+3:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+4:
#endif
		case AT_SKILL_ALICE_CHAINLIGHTNING:
			{
				c->TargetCharacter = SelectedCharacter;
				// ���׾��� ���� ���
				if(0 == CharactersClient[SelectedCharacter].Dead )
				{	
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					
					if(CheckAttack() == true)
					{
						if(CheckTile( c, o, Distance ) && c->SafeZone == false)
						{
							bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
							if(bNoneWall)
							{
								UseSkillSummon(c, o);
							}
						}
						else
						{	// �־������� �� �ȱ�
							if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
							{	
								c->Movement = true;		// �ָ� �ɾ�� ���
							}
						}
					}
				}
			}
			break;
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_SLEEP_UP:
		case AT_SKILL_ALICE_SLEEP_UP+1:
		case AT_SKILL_ALICE_SLEEP_UP+2:
		case AT_SKILL_ALICE_SLEEP_UP+3:
		case AT_SKILL_ALICE_SLEEP_UP+4:
#endif
		case AT_SKILL_ALICE_SLEEP:
		case AT_SKILL_ALICE_BLIND:		
			{
				if(CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
				{
					if(
						InChaosCastle() == true							// ī����ĳ��
						|| g_CursedTemple->IsCursedTemple() == true		// ȯ�����
						|| (battleCastle::InBattleCastle() == true && battleCastle::IsBattleCastleStart() == true) // �������̰� ��������
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
						|| g_DuelMgr.IsDuelEnabled()	// ������
#else	// YDG_ADD_NEW_DUEL_SYSTEM
						|| g_bEnableDuel == true	// ������
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
						)
					{
						// ī����ĳ���̰ų� ȯ������̰ų� �������̰ų� �������̸� �Ϲݻ���ڵ� ����� ��ų�� ����� �� �ִ�.
					}
					else
					{
						break;
					}
				}
				
				// ���׾��� ���� ���
				if(0 == CharactersClient[SelectedCharacter].Dead )
				{	
					TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
					TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
					
					if(CheckAttack() == true)
					{
						if(CheckTile( c, o, Distance ) && c->SafeZone == false)
						{
							bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
							if(bNoneWall)
							{
								UseSkillSummon(c, o);
							}
						}
						else
						{	// �־������� �� �ȱ�
							if(PathFinding2(c->PositionX, c->PositionY, TargetX, TargetY, &c->Path, Distance))
							{	
								c->Movement = true;		// �ָ� �ɾ�� ���
							}
						}
					}
				}
			}
			break;
		}
	}
}

void AttackCommon(CHARACTER *c, int Skill, float Distance)
{
	OBJECT *o = &c->Object;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    int ClassIndex = GetBaseClass ( c->Class );
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	int iMana, iSkillMana;
	GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
	
    if ( o->Type==MODEL_PLAYER )
    {
		bool Success = true;
		
		if ( iMana>CharacterAttribute->Mana )
		{
			int Index = g_pMyInventory->FindManaItemIndex();
			if(Index != -1)
			{
				SendRequestUse(Index, 0);
			}
			Success = false;
		}
		if ( Success && iSkillMana>CharacterAttribute->SkillMana )
		{
			Success = false;
		}
        if ( Success && !CheckSkillDelay( Hero->CurrentSkill ) )
        {
            Success = false;
        }
		
		int iEnergy;	// ���̳ʽ� ���� �۾�
		GetSkillInformation_Energy(Skill, &iEnergy);
		if(Success && iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
		{
			Success = false;
		}
		
        switch ( Skill )
        {
        case    AT_SKILL_STUN:
			{
				//	                        if ( CheckTile( c, o, Distance ) )
                {
                    o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
					
                    int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                    int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                    
                    BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                    WORD TKey = 0xffff;
                    if ( g_MovementSkill.m_iTarget!=-1 )
                    {
                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                    }
                    SendRequestMagicContinue ( Skill, ( c->PositionX),
                        ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
					SetAttackSpeed();
					
					if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
					{
						SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
					} 
					else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(o,PLAYER_SKILL_RIDER);
					}
					else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
					{
						SetAction(o,PLAYER_SKILL_RIDER_FLY);
					}
					else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
					{
						SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
					}
					else
					{
						SetAction ( o, PLAYER_SKILL_VITALITY );
					}
					c->Movement = 0;
				}
			}
            break;
			
        case    AT_SKILL_REMOVAL_STUN:
			{
				if(SelectedCharacter == -1)
				{
					SendRequestMagic ( Skill, HeroKey );
				}
				else
				{
					SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
				}
				
				
				if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
				{
					SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(o,PLAYER_SKILL_RIDER);
					}
					else
						if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER_FLY);
						}
						else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
						{
							SetAction ( o, PLAYER_ATTACK_REMOVAL );
						}
						c->Movement = 0;
			}
            break;
			
        case    AT_SKILL_MANA:
            if(SelectedCharacter == -1)
			{
				SendRequestMagic ( Skill, HeroKey );
			}
			else
			{
				SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
			}
			
			if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
			{
				SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
			} 
			else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER);
			}
			else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER_FLY);
			}
			else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
			{
				SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
			}
			else
				SetAction ( o, PLAYER_SKILL_VITALITY );
            c->Movement = 0;
            break;
			
        case    AT_SKILL_INVISIBLE:
			
			if(SelectedCharacter == -1)
			{
				SendRequestMagic ( Skill, HeroKey );
			}
			else
			{
				if(CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
					SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
			}
			
			if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
			{
				SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
			} 
			else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER);
			}
			else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER_FLY);
			}
			else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
			{
				SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
			}
			else
				SetAction ( o, PLAYER_SKILL_VITALITY );
            c->Movement = 0;
            break;
			
        case    AT_SKILL_REMOVAL_INVISIBLE:
            //SendRequestMagic ( Skill, HeroKey );
			
			if(SelectedCharacter == -1)
			{
				SendRequestMagic ( Skill, HeroKey );
			}
			else
			{
				SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
			}
			
			if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
			{
				SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
			} 
			else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER);
			}
			else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER_FLY);
			}
			else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
			{
				SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
			}
			else
				SetAction ( o, PLAYER_ATTACK_REMOVAL );
            c->Movement = 0;
            break;
			
        case    AT_SKILL_REMOVAL_BUFF:
			
            if(SelectedCharacter == -1)
			{
				SendRequestMagic ( Skill, HeroKey );
			}
			else
			{
				SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
			}
			
			if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
			{
				SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
			} 
			else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER);
			}
			else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
			{
				SetAction(o,PLAYER_SKILL_RIDER_FLY);
			}
			else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
			{
				SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
			}
			else
				SetAction ( o, PLAYER_SKILL_VITALITY );
            c->Movement = 0;
            break;
        }
    }
}
#endif	// YDG_FIX_SPLIT_ATTACK_FUNC

#ifdef PBG_WOPS_HELBUST
//�����Ʈ �����߿� ��Ʈ�������� �����Ͽ� �䱸������ ��ġ�� ���
bool SkillKeyPush(int Skill)
{
	if(Skill == AT_SKILL_BLAST_HELL && MouseLButtonPush)
	{
		return true;
	}
	return false;
}
#endif //PBG_WOPS_HELBUST

void Attack(CHARACTER *c)
{
// ���콺 ������ ��ư Ŭ�� �� Ŀ���� ���Ӻ���Ʈ�� ��� �κ�â� �������� ����� ��� ���� �ִ� ���� ����
#ifdef LJH_FIX_BUG_CASTING_SKILLS_W_CURSOR_OUT_OF_VIEWPORT
	if((MouseOnWindow || !SEASON3B::CheckMouseIn(0, 0, GetScreenWidth(), 429)) && MouseLButtonPush) 
	{
 		MouseRButtonPop = false;
 		MouseRButtonPush= false;
 		MouseRButton	= false;
 		MouseRButtonPress = 0;

		return;
	}
#else	//LJH_FIX_BUG_CASTING_SKILLS_W_CURSOR_OUT_OF_VIEWPORT
	if(MouseOnWindow) 
		return;
#endif	//LJH_FIX_BUG_CASTING_SKILLS_W_CURSOR_OUT_OF_VIEWPORT
	
	if( g_isCharacterBuff((&c->Object), eDeBuff_Stun)
		|| g_isCharacterBuff((&c->Object), eDeBuff_Sleep)	
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
		|| g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch)
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
		) 
	{
		return;
	}
	
	OBJECT *o = &c->Object;
    int ClassIndex = GetBaseClass ( c->Class );
	
	if(o->Teleport == TELEPORT_BEGIN)
	{
		o->Alpha -= 0.1f;
		if(o->Alpha < 0.1f)
		{
			o->Teleport = TELEPORT;
		}
	}
	
	bool Success = false;
	bool CursedTempleSkillSuccess = false;
	
	// ���� ��ų
	int Skill = CharacterAttribute->Skill[Hero->CurrentSkill]; 

	// ��ų ��� �Ÿ�
    float Distance = GetSkillDistance( Skill, c );	

	if(!EnableFastInput)
	{
		//	������ ���콺 ������.
		if ( MouseRButtonPress!=0 )
		{
#ifdef PBG_WOPS_HELBUST
			if ( MouseRButtonPop || SkillKeyPush(Skill))
#else //PBG_WOPS_HELBUST
			if ( MouseRButtonPop )
#endif//PBG_WOPS_HELBUST
			{
				MouseRButtonPop = false;
				MouseRButtonPush= false;
				MouseRButton	= false;
				
				MouseRButtonPress = 0;
				Success = true;
			}
			else
			{
				MouseRButtonPress++;
			}
		}
		else if((MouseRButtonPush || MouseRButton) && !(MouseLButtonPush || MouseLButton) && !c->Movement)
		{
			//	����2.
			if ( Skill==AT_SKILL_BLAST_HELL )
			{
				if ( o->Teleport!=TELEPORT_END && o->Teleport!=TELEPORT_NONE) return;
#ifdef YDG_FIX_HELLBUST_SET_ENERGY_BONUS_BUG
				int iReqEng = 0;
				GetSkillInformation_Energy(Skill, &iReqEng);
				if (CharacterAttribute->Energy + CharacterAttribute->AddEnergy < iReqEng) return;	// �����Ʈ �䱸 ������ �˻�
#endif	// YDG_FIX_HELLBUST_SET_ENERGY_BONUS_BUG
				
				MouseRButtonPress = 1;
				Hero->Object.m_bySkillCount = 0;
				Skill = AT_SKILL_BLAST_HELL_BEGIN;
			}
#ifdef KJH_FIX_WOPS_K29690_PICKED_ITEM_BACKUP
			// â�� ������ �������� Picked�Ǿ������� �ǵ�����.
			SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
#endif // KJH_FIX_WOPS_K29690_PICKED_ITEM_BACKUP
			MouseRButtonPush = false;
			Success = true;
		}
        //  �ڵ�����.   ( ��Ʋ��Ŀ������ �ȵ� )
        if( 
			g_pOption->IsAutoAttack()
			&& World != WD_6STADIUM 
			&& InChaosCastle() == false
			&& Attacking == 2 
			&& SelectedCharacter != -1 )
        {
            Success = true;
        }
		
        //  ���� ������ �Ǿ�����.
        if( Success )
        {
			RButtonPressTime = ((WorldTime - RButtonPopTime)/CLOCKS_PER_SEC);
			
			if ( RButtonPressTime>=AutoMouseLimitTime )
			{
				MouseRButtonPush = false;
				MouseRButton = false;
				Success = FALSE;
			}
        }
        else
        {
            RButtonPopTime = WorldTime;
            RButtonPressTime = 0.f;
        }
	}
	else
	{
		if(MouseLButtonPush || MouseLButton)
		{
			MouseLButtonPush = false;
			Success = true;
        }
	}
	
    if( Success )
    {
        g_iFollowCharacter = -1;
		
#ifdef PET_SYSTEM
        //  �� Ŀ�ǵ� ������ ���.
		
		if( !g_isCharacterBuff((&Hero->Object), eBuff_Cloaking ) )
			{
				if( giPetManager::SendPetCommand( c, Hero->CurrentSkill )  == true )
				{
					return;
				}
			}
#endif// PET_SYSTEM
			
			//  ��ų ����� ���� ������ �˻��Ѵ�.
			if( g_CursedTemple->IsCursedTemple() )	// ȯ������ΰ�?
			{
				if(g_pCursedTempleWindow->IsCursedTempleSkillKey( SelectedCharacter ))
				{
					CursedTempleSkillSuccess = true;
				}
				else
				{
#ifdef LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER
					// ��Ƽ������ �Ϲ� �����̸� Attack�� �������� �ʴ´�. 
					if ( g_CursedTemple->IsPartyMember( SelectedCharacter ) == true )
					{
						if ( !IsCorrectSkillType_FrendlySkill( Skill ) && !IsCorrectSkillType_Buff( Skill ) )
						{
							return;
						}
					}
					else
					{
						// ����Ƽ���� ��� ģȭ�� ��ų�� ��� �� ������ ó������.
						if( IsCorrectSkillType_FrendlySkill(Skill) || IsCorrectSkillType_Buff(Skill) )
						{
							// �ڱ��ڽ��� �ƴϸ� ���� ���� �ʴ´�.
							if ( -1 != SelectedCharacter )
							{
								return;
							}
						}
					}
#endif // LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER
					
					if ( CheckSkillUseCondition( o, Skill )==false ) return;
				}
			}
			else
			{
				if ( CheckSkillUseCondition( o, Skill ) == false ) 
				{
					return;
				}
			}
			
			if (Skill == AT_SKILL_SUMMON_EXPLOSION || Skill == AT_SKILL_SUMMON_REQUIEM
#ifdef ASG_ADD_SUMMON_RARGLE
				|| Skill == AT_SKILL_SUMMON_POLLUTION
#endif	// ASG_ADD_SUMMON_RARGLE
				)
			{
				CheckTarget(c);
				if ( !CheckTile( c, o, Distance ) )	// �Ÿ� ����
					return;
			}
    }
	
#ifdef USE_SELFCHECKCODE
	SendCrcOfFunction( 2, 14, WinMain, 0xE910);
#endif


	//
	if( Success ) 
	{
#ifdef PBG_FIX_SKILL_DEMENDCONDITION
		//��ų����� �Ȱ�� ��ų�� ���ݰ˻�.
 		if( !SKILLCONDITION::DemendConditionCheckSkill( Skill ) )
 		{
 			//��ų�� ���ݿ䱸���� �������Ѵٸ�.���Ұ�.
			return;
 		}
#endif //PBG_FIX_SKILL_DEMENDCONDITION
	}
    if(Success && c->Dead == 0)
	{
		if( !c->SafeZone && CursedTempleSkillSuccess )
		{
			g_pCursedTempleWindow->SetCursedTempleSkill( c, o, SelectedCharacter );
		}
		else if( !c->SafeZone || ( InBloodCastle() == true ) || InChaosCastle() == true )
		{
			// ī����ĳ������ �����ִ� ����(����)�� ���⿡ ����ó���Ѵ�.( '!=' ���� )
			// �ڵ� ������. ( ���� ������ ������� �ʴ´�. )
			if ( c->SafeZone && Skill!=AT_SKILL_HEALING && Skill!=AT_SKILL_DEFENSE && Skill!=AT_SKILL_ATTACK 
				&& Skill!=AT_SKILL_WIZARDDEFENSE && Skill!=AT_SKILL_VITALITY 
#ifdef KJH_FIX_20080910_SPELL_MAGIC_IN_CHAOSCASTLE
				&& Skill!=AT_SKILL_INFINITY_ARROW					// ���Ǵ�Ƽ�ַο�
				&& Skill!=AT_SKILL_SWELL_OF_MAGICPOWER				// ��������
				&& Skill!=AT_SKILL_RECOVER							// ȸ��
				&& Skill!=AT_SKILL_ALICE_BERSERKER					// ����Ŀ
#endif // KJH_FIX_20080910_SPELL_MAGIC_IN_CHAOSCASTLE
#ifdef PJH_SEASON4_MASTER_RANK4
				&& !(AT_SKILL_DEF_POWER_UP <= Skill && Skill <= AT_SKILL_DEF_POWER_UP+4)
				&& !(AT_SKILL_ATT_POWER_UP <= Skill && Skill <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
				&& !(AT_SKILL_SOUL_UP <= Skill && Skill <= AT_SKILL_SOUL_UP+4)
				&& !(AT_SKILL_HEAL_UP <= Skill && Skill <= AT_SKILL_HEAL_UP+4)
				&& !(AT_SKILL_LIFE_UP <= Skill && Skill <= AT_SKILL_LIFE_UP+4)
				&& Skill!=AT_SKILL_IMPROVE_AG && Skill!=AT_SKILL_ADD_CRITICAL 
				&& Skill!=AT_SKILL_PARTY_TELEPORT
				&& ( Skill<AT_SKILL_STUN || Skill>AT_SKILL_REMOVAL_BUFF )
				&& Skill!=AT_SKILL_BRAND_OF_SKILL 
#ifdef PBG_FIX_BUFFSKILLCHAOS
				&& !(AT_SKILL_ATT_UP_OURFORCES <= Skill && Skill <= AT_SKILL_DEF_UP_OURFORCES+4)
#endif //PBG_FIX_BUFFSKILLCHAOS
				)
				return;
			
			//  �ڵ� ���� �����.   ( ��Ʋ ��Ŀ������ �ȵ� )
			if (
				g_pOption->IsAutoAttack()
				&& World != WD_6STADIUM 
				&& InChaosCastle()==false )
			{
				if( ClassIndex==CLASS_ELF 
					&& (Skill != AT_SKILL_CROSSBOW 
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
					&& Skill != AT_SKILL_MULTI_SHOT
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
					&& !(AT_SKILL_MANY_ARROW_UP <= Skill && Skill <= AT_SKILL_MANY_ARROW_UP+4)
					&& Skill != AT_SKILL_BOW 
					&& Skill != AT_SKILL_PIERCING 
					&& Skill != AT_SKILL_BLAST_CROSSBOW4 
					&& Skill != AT_SKILL_PLASMA_STORM_FENRIR	//^ �渱 ��ų ����(�ڵ�����)
					) )
				{
					Attacking = -1;
				}
				else if( ClassIndex == CLASS_KNIGHT && (Skill == AT_SKILL_VITALITY || (AT_SKILL_LIFE_UP <= Skill && Skill <= AT_SKILL_LIFE_UP+4)))
				{
					Attacking = -1;
				}
				else if(ClassIndex == CLASS_DARK_LORD 
					&& ( Skill==AT_SKILL_ADD_CRITICAL || Skill==AT_SKILL_PARTY_TELEPORT ) )
				{
					Attacking = -1;
				}
				else if(ClassIndex == CLASS_WIZARD 
					&& ( Skill==AT_SKILL_BLAST_HELL_BEGIN || Skill==AT_SKILL_BLAST_HELL ) )
				{
					Attacking = -1;
				}
				else if(Skill >= AT_SKILL_STUN && Skill <= AT_SKILL_REMOVAL_BUFF )
				{
					Attacking = -1;
				}
				else if(Skill == AT_SKILL_BRAND_OF_SKILL )
				{
					Attacking = -1;
				}
#ifdef LDK_FIX_BUFFSKILL_AUTOATTACK_CANCLE
				else if( Skill == AT_SKILL_ALICE_THORNS 
#ifdef PJH_ADD_MASTERSKILL
						|| (AT_SKILL_ALICE_SLEEP_UP <= Skill && Skill <= AT_SKILL_ALICE_SLEEP_UP+4)
#endif
					|| Skill == AT_SKILL_ALICE_BERSERKER || Skill == AT_SKILL_ALICE_SLEEP 
					|| Skill == AT_SKILL_ALICE_BLIND || Skill == AT_SKILL_ALICE_WEAKNESS || Skill == AT_SKILL_ALICE_ENERVATION )
#else //LDK_FIX_BUFFSKILL_AUTOATTACK_CANCLE
				else if(Skill == AT_SKILL_ALICE_SLEEP || Skill == AT_SKILL_ALICE_BLIND || Skill == AT_SKILL_ALICE_BLIND
#ifdef PJH_ADD_MASTERSKILL
						|| (AT_SKILL_ALICE_SLEEP_UP <= Skill && Skill <= AT_SKILL_ALICE_SLEEP_UP+4)
#endif
				)
#endif //LDK_FIX_BUFFSKILL_AUTOATTACK_CANCLE
				{
					Attacking = -1;
				}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
				else if(AT_SKILL_ATT_UP_OURFORCES <= Skill && Skill <= AT_SKILL_DEF_UP_OURFORCES)
				{
					Attacking = -1;
				}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
				else
				{
					Attacking = 2;
				}
			}
			
			if(o->Type == MODEL_PLAYER)
			{
				if( o->CurrentAction < PLAYER_STOP_MALE 
					|| o->CurrentAction > PLAYER_STOP_RIDE_WEAPON
					&& o->CurrentAction!=PLAYER_STOP_TWO_HAND_SWORD_TWO
					&& o->CurrentAction!=PLAYER_SKILL_HELL_BEGIN
					&& o->CurrentAction!=PLAYER_DARKLORD_STAND
					&& o->CurrentAction!=PLAYER_STOP_RIDE_HORSE 
					&& o->CurrentAction!=PLAYER_FENRIR_STAND
					&& o->CurrentAction!=PLAYER_FENRIR_STAND_TWO_SWORD
					&& o->CurrentAction!=PLAYER_FENRIR_STAND_ONE_RIGHT
					&& o->CurrentAction!=PLAYER_FENRIR_STAND_ONE_LEFT
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
					&& !(o->CurrentAction>=PLAYER_RAGE_FENRIR_STAND && o->CurrentAction<=PLAYER_RAGE_FENRIR_STAND_ONE_LEFT)
					&& o->CurrentAction!=PLAYER_RAGE_UNI_STOP_ONE_RIGHT
					&& o->CurrentAction!=PLAYER_STOP_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK_ANI
					)
				{
					MouseRButtonPress	= 0;
					return;
				}
			}
			else
			{
				if(o->CurrentAction < MONSTER01_STOP1 || o->CurrentAction > MONSTER01_STOP2) 
				{
					return;
				}
			}
			
			// �渶���簡 �ƴ϶��
			if ( ClassIndex != CLASS_WIZARD )
			{
				CheckTarget(c);

				if(CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY))
				{
					for(int i=EQUIPMENT_WEAPON_RIGHT; i<=EQUIPMENT_WEAPON_LEFT; i++)
					{
						if ( ClassIndex==CLASS_KNIGHT || ClassIndex==CLASS_DARK || ClassIndex==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
							|| ClassIndex==CLASS_RAGEFIGHTER	//�⺻ ���� ��ų����
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
							)
						{
							//  �̵����ܸ� Ÿ�� ���� �ʰų�, â��ų�� ���� ��ų�� �� �� �ְ� �Ѵ�.
							bool bOk = false;
							if ( c->Helper.Type != MODEL_HELPER+2		// ���ϸ���
								&& c->Helper.Type != MODEL_HELPER+3		// ����Ʈ
								&& c->Helper.Type != MODEL_HELPER+4		// ��ũȣ��
								&& c->Helper.Type != MODEL_HELPER+37	// �渱
								)
							{
								bOk = true;
							}
							else
							{
								// �̵����� ������ �� �� �ִ� ��ų
								switch ( Skill)
								{	
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
								case AT_SKILL_GAOTIC:
#ifndef PBG_FIX_PKFIELD_CAOTIC
									break;
#endif //PBG_FIX_PKFIELD_CAOTIC
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
								case AT_SKILL_SPEAR:	// â���											  
								case AT_SKILL_RIDER:
#ifdef PJH_SEASON4_MASTER_RANK4
								case AT_SKILL_BLOW_UP:
								case AT_SKILL_BLOW_UP+1:
								case AT_SKILL_BLOW_UP+2:
								case AT_SKILL_BLOW_UP+3:
								case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
								case AT_SKILL_ONETOONE:	// ��ο�
								case AT_SKILL_STRONG_PIER:
								case AT_SKILL_FIRE_BUST_UP:
								case AT_SKILL_FIRE_BUST_UP+1:
								case AT_SKILL_FIRE_BUST_UP+2:
								case AT_SKILL_FIRE_BUST_UP+3:
								case AT_SKILL_FIRE_BUST_UP+4:
								case AT_SKILL_LONGPIER_ATTACK:
								case AT_SKILL_ASHAKE_UP:
								case AT_SKILL_ASHAKE_UP+1:
								case AT_SKILL_ASHAKE_UP+2:
								case AT_SKILL_ASHAKE_UP+3:
								case AT_SKILL_ASHAKE_UP+4:
								case AT_SKILL_DARK_HORSE:
								case AT_SKILL_THUNDER_STRIKE:
								case AT_SKILL_SPACE_SPLIT :      //  ���� ������.
								case AT_SKILL_PLASMA_STORM_FENRIR:	// (���, ��ũ�ε�, ���˻�)
#ifdef PJH_SEASON4_MASTER_RANK4
								case AT_SKILL_FIRE_SCREAM_UP:
								case AT_SKILL_FIRE_SCREAM_UP+1:
								case AT_SKILL_FIRE_SCREAM_UP+2:
								case AT_SKILL_FIRE_SCREAM_UP+3:
								case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
								case AT_SKILL_DARK_SCREAM:
									bOk = true;
									break;
								}
							}
							
							if ( bOk)
							{
								g_MovementSkill.m_bMagic = TRUE;
								g_MovementSkill.m_iSkill = Hero->CurrentSkill;
								
								if ( CheckAttack() )
								{
									g_MovementSkill.m_iTarget = SelectedCharacter;
								}
								else
								{
									g_MovementSkill.m_iTarget = -1;
								}
								if(SkillWarrior(c,&CharacterMachine->Equipment[i]))
								{
									return;
								}
							}
						}
						if ( ClassIndex==CLASS_ELF )
						{
							if(SkillElf(c,&CharacterMachine->Equipment[i]))
							{
								return;
							}
						}
					}
				}
				else
				{
					ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
					g_MovementSkill.m_iTarget = -1;
				}
			}
#ifdef YDG_FIX_SPLIT_ATTACK_FUNC
			if ( ClassIndex==CLASS_ELF )	// ������ų
			{
				AttackElf(c,Skill,Distance);
			}
			//  ���� ��ų.
			if( ClassIndex == CLASS_KNIGHT // ����
				|| ClassIndex == CLASS_DARK	// ���˻�
				|| ClassIndex == CLASS_DARK_LORD)	// ��ũ�ε�			
			{
				AttackKnight(c,Skill,Distance);
			}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			if(ClassIndex == CLASS_RAGEFIGHTER) //������������
			{
				AttackRagefighter(c,Skill,Distance);
			}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

			if ( ClassIndex==CLASS_WIZARD		// �渶���� �̰ų�
				|| ClassIndex==CLASS_DARK		// ���˻� �̰ų�
				|| ClassIndex==CLASS_SUMMONER	// ��ȯ���� �̰ų� : �渶����� ���� ��ų(�, ���̾, ����, �Ŀ����̺�)�� ���� �߰�.
				)
			{
				AttackWizard(c,Skill,Distance);
			}
			//  �������� ���Ǵ� ��ų.
			if ( (Skill>= AT_SKILL_STUN && Skill<=AT_SKILL_REMOVAL_BUFF ))
			{
				AttackCommon(c,Skill,Distance);
			}
#else	// YDG_FIX_SPLIT_ATTACK_FUNC
			if ( ClassIndex==CLASS_ELF )	// ������ų
			{
				int iMana, iSkillMana;
				GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
				if( g_isCharacterBuff(o, eBuff_InfinityArrow) ) 
					iMana += CharacterMachine->InfinityArrowAdditionalMana;
				if(iMana > CharacterAttribute->Mana)
				{
					int Index = g_pMyInventory->FindManaItemIndex();
					if(Index != -1)
					{
						SendRequestUse(Index, 0);
					}
					return;
				}
				// skillmana ����
				if(iSkillMana > CharacterAttribute->SkillMana)
				{
					return;
				}
                if ( !CheckSkillDelay( Hero->CurrentSkill ) )
                {
                    return;
                }
				
				int iEnergy;
				GetSkillInformation_Energy(Skill, &iEnergy);
				if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy) )
				{
					return;
				}
				
                bool Success = CheckTarget(c);
				switch(Skill)
				{
				case AT_SKILL_SUMMON:
				case AT_SKILL_SUMMON+1:
				case AT_SKILL_SUMMON+2:
				case AT_SKILL_SUMMON+3:
				case AT_SKILL_SUMMON+4:
				case AT_SKILL_SUMMON+5:
				case AT_SKILL_SUMMON+6:
#ifdef ADD_ELF_SUMMON
				case AT_SKILL_SUMMON+7:
#endif // ADD_ELF_SUMMON
                    if ( World!=WD_10HEAVEN && InChaosCastle()==false )
						if(!g_Direction.m_CKanturu.IsMayaScene())
						{
							SendRequestMagic(Skill,HeroKey);
							SetPlayerMagic(c);
						}
						return;
						
                case AT_SKILL_PIERCING:
#ifdef ADD_SOCKET_ITEM
					// �÷��̾ Ȱ�̳� ������ �������� ��
					if( (o->Type == MODEL_PLAYER) && (GetEquipedBowType( Hero ) != BOWTYPE_NONE) )
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
						if( o->Type==MODEL_PLAYER &&
							(( Hero->Weapon[0].Type>=MODEL_BOW+8  && Hero->Weapon[0].Type<MODEL_BOW+15 ) ||
							(( Hero->Weapon[1].Type>=MODEL_BOW    && Hero->Weapon[1].Type<MODEL_BOW+7 ) 
							|| Hero->Weapon[1].Type==MODEL_BOW+17 
							|| Hero->Weapon[1].Type==MODEL_BOW+20
							|| Hero->Weapon[1].Type==MODEL_BOW+21
							|| Hero->Weapon[1].Type==MODEL_BOW+22
							) ||
							(  Hero->Weapon[0].Type>=MODEL_BOW+16 && Hero->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX ) ) )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
						{
							if(!CheckArrow())
								break;
							if ( CheckTile( c, o, Distance ) )
							{
								o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
								
								WORD TKey = 0xffff;
								if ( g_MovementSkill.m_iTarget!=-1 )
								{
									TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
								}
								SendRequestMagicContinue(Skill,( c->PositionX),
									( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0,TKey,0);
								SetPlayerAttack(c);
								if(o->Type != MODEL_PLAYER)
								{
									CreateArrows(c,o,NULL,FindHotKey(( c->Skill)),0,( c->Skill));
								}
							}
						}
						break;
						
				}
				if(SelectedCharacter != -1)
				{
					ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
					g_MovementSkill.m_bMagic = TRUE;
					g_MovementSkill.m_iSkill = Hero->CurrentSkill;
					g_MovementSkill.m_iTarget = SelectedCharacter;
				}
				if ( !CheckTile( c, o, Distance ) )
				{
					if ( SelectedCharacter!=-1 && ( Skill==AT_SKILL_HEALING || Skill==AT_SKILL_ATTACK || Skill==AT_SKILL_DEFENSE || CheckAttack() 
						|| (AT_SKILL_HEAL_UP <= Skill && Skill <= AT_SKILL_HEAL_UP+4)
						|| Skill==AT_SKILL_DARK_SCREAM
#ifdef PJH_SEASON4_MASTER_RANK4
						|| (AT_SKILL_FIRE_SCREAM_UP <= Skill && Skill <= AT_SKILL_FIRE_SCREAM_UP+4)
						|| (AT_SKILL_DEF_POWER_UP <= Skill && Skill <= AT_SKILL_DEF_POWER_UP+4)
						|| (AT_SKILL_ATT_POWER_UP <= Skill && Skill <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
						)
						)
					{
						if(CharactersClient[SelectedCharacter].Object.Kind==KIND_PLAYER)
						{
							if(PathFinding2(( c->PositionX),( c->PositionY),
								TargetX,TargetY,&c->Path, Distance ) )
							{
								c->Movement = true;
								c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
								SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
							}
						}
					}
					
					if(Skill != AT_SKILL_STUN && Skill != AT_SKILL_REMOVAL_STUN && Skill != AT_SKILL_MANA && Skill != AT_SKILL_INVISIBLE && Skill != AT_SKILL_REMOVAL_INVISIBLE
						&& Skill != AT_SKILL_PLASMA_STORM_FENRIR
						)
						return;
				}
				bool Wall = CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY);
				if(Wall)
				{
					if(SelectedCharacter != -1)
					{
						if(CharactersClient[SelectedCharacter].Object.Kind==KIND_PLAYER)
						{
							switch(Skill)
							{
							case AT_SKILL_HEAL_UP:
							case AT_SKILL_HEAL_UP+1:
							case AT_SKILL_HEAL_UP+2:
							case AT_SKILL_HEAL_UP+3:
							case AT_SKILL_HEAL_UP+4:
							case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
							case AT_SKILL_ATT_POWER_UP:
							case AT_SKILL_ATT_POWER_UP+1:
							case AT_SKILL_ATT_POWER_UP+2:
							case AT_SKILL_ATT_POWER_UP+3:
							case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
							case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_MASTER_RANK4
							case AT_SKILL_DEF_POWER_UP:
							case AT_SKILL_DEF_POWER_UP+1:
							case AT_SKILL_DEF_POWER_UP+2:
							case AT_SKILL_DEF_POWER_UP+3:
							case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
							case AT_SKILL_DEFENSE:
								UseSkillElf( c, o);
								return;
							}
						}
                        if(CheckAttack())
                        {
#ifdef ADD_SOCKET_ITEM
							// �÷��̾ Ȱ/������ �����Ͽ���, �ش� ��ų����
							if( ((Skill==AT_SKILL_PARALYZE) || (Skill==AT_SKILL_DEEPIMPACT))
								&& ((o->Type == MODEL_PLAYER) && (GetEquipedBowType( Hero ) != BOWTYPE_NONE ))
								)
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
								if( ( Skill==AT_SKILL_PARALYZE 
									|| Skill==AT_SKILL_DEEPIMPACT
									)
									&& o->Type==MODEL_PLAYER && 
									(( Hero->Weapon[0].Type>=MODEL_BOW+8  && Hero->Weapon[0].Type<MODEL_BOW+15 ) ||
									(( Hero->Weapon[1].Type>=MODEL_BOW    && Hero->Weapon[1].Type<MODEL_BOW+7 ) 
									|| Hero->Weapon[1].Type==MODEL_BOW+17 
									|| Hero->Weapon[1].Type==MODEL_BOW+20
									|| Hero->Weapon[1].Type == MODEL_BOW+21
									|| Hero->Weapon[1].Type == MODEL_BOW+22
									) ||
									(  Hero->Weapon[0].Type>=MODEL_BOW+16 && Hero->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX ) ) )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
								{
									UseSkillElf ( c, o );
								}
                        }
					}
				}
				
				switch(Skill)
				{
				case AT_SKILL_INFINITY_ARROW:
					{
						//����ȭ�� ���°� �ƴ� ��츸 �� �� �ִ�. 
						if(g_isCharacterBuff((&Hero->Object), eBuff_InfinityArrow)==false)
						{
							SendRequestMagic(Skill,HeroKey);
							if((c->Helper.Type == MODEL_HELPER+37) 
								|| (c->Helper.Type == MODEL_HELPER+2)
								|| (c->Helper.Type == MODEL_HELPER+3)
								|| (c->Helper.Type == MODEL_HELPER+4))
								SetPlayerMagic(c);
							else
								SetAction(o,PLAYER_RUSH1);
							
							c->Movement = 0;
						}
					}
					break;
					
#ifdef HELLOWIN_EVENT
				case AT_SKILL_HELLOWIN_EVENT_1:
				case AT_SKILL_HELLOWIN_EVENT_2:
				case AT_SKILL_HELLOWIN_EVENT_3:
				case AT_SKILL_HELLOWIN_EVENT_4:
				case AT_SKILL_HELLOWIN_EVENT_5:
                    SendRequestMagic ( Skill, HeroKey );
					//					SetPlayerMagic(c);
                    c->Movement = 0;
					break;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
				case AT_SKILL_RECOVER:
					{
						vec3_t Light,Position,P,dp;
												
						float Matrix[3][4];
						
						Vector(0.f,-220.f,130.f,P);
						AngleMatrix(o->Angle,Matrix);
						VectorRotate(P,Matrix,dp);
						VectorAdd(dp,o->Position,Position);
						Vector(0.7f, 0.6f, 0.f, Light);
						CreateEffect(BITMAP_IMPACT, Position, o->Angle, Light, 0,o);
						SetAction(o,PLAYER_RECOVER_SKILL);
						if(SelectedCharacter > -1)
						{
							SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
						}
						else
						{
							SendRequestMagic(Skill,HeroKey);
						}
						//			UseSkillElf( c, o);
					}
					break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
					
#endif//HELLOWIN_EVENT
				case AT_SKILL_HEAL_UP:
				case AT_SKILL_HEAL_UP+1:
				case AT_SKILL_HEAL_UP+2:
				case AT_SKILL_HEAL_UP+3:
				case AT_SKILL_HEAL_UP+4:
				case AT_SKILL_HEALING:
#ifdef PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_ATT_POWER_UP:
				case AT_SKILL_ATT_POWER_UP+1:
				case AT_SKILL_ATT_POWER_UP+2:
				case AT_SKILL_ATT_POWER_UP+3:
				case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_ATTACK:
#ifdef PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_DEF_POWER_UP:
				case AT_SKILL_DEF_POWER_UP+1:
				case AT_SKILL_DEF_POWER_UP+2:
				case AT_SKILL_DEF_POWER_UP+3:
				case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
					//#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
					//	case AT_SKILL_RECOVER:
					//#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
				case AT_SKILL_DEFENSE:
					SendRequestMagic(Skill,HeroKey);
					SetPlayerMagic(c);
					return;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
				case AT_SKILL_MULTI_SHOT:
					{
						if (GetEquipedBowType_Skill() == BOWTYPE_NONE)	// Ȱ�� ���� Ȱ��ȭ
							return;
						o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
#ifdef PJH_SEASON4_FIX_MULTI_SHOT
			if( CheckTile( c, o, Distance ) )
			{
				BYTE PathX[1];
				BYTE PathY[1];
				PathX[0] = ( c->PositionX);
				PathY[0] = ( c->PositionY);
				SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
				
				BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
				
				BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
				WORD TKey = 0xffff;
				if ( g_MovementSkill.m_iTarget!=-1 )
				{
					TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
				}

				SendRequestMagicContinue(Skill,( c->PositionX),
					( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
				SetAttackSpeed();
				//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
				c->Movement = 0;
				//c->AttackTime = 15;
		
				
				SetPlayerBow(c);
				vec3_t Light,Position,P,dp,Angle;
				
				float Matrix[3][4];
				Vector(0.f,20.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				Vector(0.8f, 0.9f, 1.6f, Light);
				CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
				
				Vector(0.f,-20.f,0.f,P);
				Vector(0.f,0.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
				
				Vector(0.f,20.f,0.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);
				CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
				CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
				
				Vector(0.f,-120.f,145.f,P);
				AngleMatrix(o->Angle,Matrix);
				VectorRotate(P,Matrix,dp);
				VectorAdd(dp,o->Position,Position);

				short Key = -1;
                for( int i=0;i<MAX_CHARACTERS_CLIENT;i++ )
                {
                    CHARACTER *tc = &CharactersClient[i];
					if(tc == c)
					{
						Key = i;
						break;
					}
				}

				CreateEffect(MODEL_BLADE_SKILL, Position, o->Angle, Light, 1, o, Key);
				PlayBuffer(SOUND_SKILL_MULTI_SHOT);
			}
#else				//PJH_SEASON4_FIX_MULTI_SHOT		


						if( CheckTile( c, o, Distance ) )
						{
							BYTE PathX[1];
							BYTE PathY[1];
							PathX[0] = ( c->PositionX);
							PathY[0] = ( c->PositionY);
							SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
							
							BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
							
							BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
							WORD TKey = 0xffff;
							if ( g_MovementSkill.m_iTarget!=-1 )
							{
								TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
							}
							SendRequestMagicContinue(Skill,( c->PositionX),
								( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
							SetAttackSpeed();
							//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
							c->Movement = 0;
							//c->AttackTime = 15;
					
							
							SetPlayerBow(c);
							vec3_t Light,Position,P,dp,Angle;
							
							float Matrix[3][4];
							Vector(0.f,20.f,0.f,P);
							AngleMatrix(o->Angle,Matrix);
							VectorRotate(P,Matrix,dp);
							VectorAdd(dp,o->Position,Position);
							Vector(0.4f, 0.6f, 1.f, Light);
							CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
							CreateEffect ( MODEL_MULTI_SHOT3, Position, o->Angle, Light, 0);
							
							Vector(0.f,-20.f,0.f,P);
							Vector(0.f,0.f,0.f,P);
							AngleMatrix(o->Angle,Matrix);
							VectorRotate(P,Matrix,dp);
							VectorAdd(dp,o->Position,Position);
							
							CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
							CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
							CreateEffect ( MODEL_MULTI_SHOT1, Position, o->Angle, Light, 0);
							
							Vector(0.f,20.f,0.f,P);
							AngleMatrix(o->Angle,Matrix);
							VectorRotate(P,Matrix,dp);
							VectorAdd(dp,o->Position,Position);
							CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
							CreateEffect ( MODEL_MULTI_SHOT2, Position, o->Angle, Light, 0);
							
							Vector(0.f,-120.f,130.f,P);
							AngleMatrix(o->Angle,Matrix);
							VectorRotate(P,Matrix,dp);
							VectorAdd(dp,o->Position,Position);
							CreateEffect(MODEL_BLADE_SKILL, Position, o->Angle, Light, 1);
							
							BYTE Skill = 0;
							//			CHARACTER *tc;
							OBJECT *to = NULL;
							
							VectorCopy(o->Angle,Angle);
							CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
							o->Angle[2] = Angle[2] + 8.f;
							CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
							o->Angle[2] = Angle[2] + 16.f;
							CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
							o->Angle[2] = Angle[2] - 8.f;
							CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
							o->Angle[2] = Angle[2] - 16.f;
							CreateArrow(c,o,to,FindHotKey(( o->Skill)),1,0);
							o->Angle[2] = Angle[2];
							PlayBuffer(SOUND_SKILL_MULTI_SHOT);
						}
#endif //PJH_SEASON4_FIX_MULTI_SHOT
					}
					break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
					
                case AT_SKILL_IMPROVE_AG:
					SendRequestMagic(Skill,HeroKey);
					SetPlayerMagic(c);
					c->Movement = 0;
                    break;
					
					//^ �渱 ��ų ����
				case AT_SKILL_PLASMA_STORM_FENRIR:	// (����)
					{
						if ( CheckAttack() )
						{
							g_MovementSkill.m_iTarget = SelectedCharacter;
						}
						else
						{
							g_MovementSkill.m_iTarget = -1;
						}
						
						// ��� ���� ��� ��ǥ ���
						int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
						int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
						if( CheckTile( c, o, Distance ) )
						{
							BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
							WORD TKey = 0xffff;
							if(g_MovementSkill.m_iTarget != -1)
							{
								o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
								
								CheckSkillDelay(Hero->CurrentSkill);
								
								TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
								c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
								SendRequestMagicContinue(Skill,( c->PositionX),
									( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
								c->Movement = 0;
								
								if(o->Type == MODEL_PLAYER)
								{
									SetAction_Fenrir_Skill(c, o);
								}
							}
							else
							{
								c->m_iFenrirSkillTarget = -1;
							}
						}
						else
						{
							if(g_MovementSkill.m_iTarget != -1)
							{
								if(PathFinding2(( c->PositionX),( c->PositionY),
									TargetX,TargetY,&c->Path, Distance*1.2f ) )
								{	// �ָ� �ɾ�� ���
									c->Movement = true;
								}
							}
							else
							{
								Attacking = -1;
							}
						}
					}	// case 
					break;
				}	// switch
			} // if
			
            //  ���� ��ų.
			if( ClassIndex == CLASS_KNIGHT // ����
				|| ClassIndex == CLASS_DARK	// ���˻�
				|| ClassIndex == CLASS_DARK_LORD )	// ��ũ�ε�
			{
				
				// ������ ��ų���� ���س��´�.
				int iMana, iSkillMana;
				GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana );
				
                // ��� ��ų�� ��� Į�� ���ϰ� �־���Ѵ�.
                // ��� ���������� Į�� ��� ����.
                if(
					( ( Hero->Weapon[0].Type!=-1 && 
					( Hero->Weapon[0].Type<MODEL_STAFF || Hero->Weapon[0].Type>=MODEL_STAFF+MAX_ITEM_INDEX ) &&
					( Hero->Weapon[1].Type<MODEL_STAFF || Hero->Weapon[1].Type>=MODEL_STAFF+MAX_ITEM_INDEX ) ) 
					|| Skill == AT_SKILL_VITALITY 
					|| Skill == AT_SKILL_ADD_CRITICAL 
					|| Skill == AT_SKILL_PARTY_TELEPORT 
					|| Skill == AT_SKILL_THUNDER_STRIKE 
					|| Skill == AT_SKILL_DARK_HORSE
					|| (AT_SKILL_LIFE_UP <= Skill && Skill <= AT_SKILL_LIFE_UP+4)
					|| (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4)
					|| Skill == AT_SKILL_BRAND_OF_SKILL
					|| Skill == AT_SKILL_PLASMA_STORM_FENRIR	// (���, ��ũ�ε�, ���˻�) �渱 ��ų
					|| Skill == AT_SKILL_DARK_SCREAM
#ifdef PJH_SEASON4_MASTER_RANK4
					|| (AT_SKILL_FIRE_SCREAM_UP <= Skill && Skill <= AT_SKILL_FIRE_SCREAM_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
					|| Skill == AT_SKILL_WHEEL
					|| (AT_SKILL_TORNADO_SWORDA_UP <= Skill && Skill <= AT_SKILL_TORNADO_SWORDA_UP+4)
					|| (AT_SKILL_TORNADO_SWORDB_UP <= Skill && Skill <= AT_SKILL_TORNADO_SWORDB_UP+4)
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
					|| Skill == AT_SKILL_GIGANTIC_STORM
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
					|| Skill == AT_SKILL_GAOTIC
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
					) )
                {
					bool Success = true;
					
                    if ( Skill==AT_SKILL_PARTY_TELEPORT && PartyNumber<=0 )
                    {
                        Success = false;
                    }
					
					if( Skill == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
					{
						BYTE t_DarkLife = 0;
						t_DarkLife  = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
						if(t_DarkLife == 0) Success = false;
					}
					
					if( InChaosCastle() )
					{
						//ī���� ĳ�������� ��ũ���Ǹ�, ��ũȣ��, ����Ʈ ��ų ���� ��� �Ұ���
						if( Skill == AT_SKILL_DARK_HORSE 
							|| (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4)
							|| Skill == AT_SKILL_RIDER
							|| ( Skill >= AT_PET_COMMAND_DEFAULT && Skill <= AT_PET_COMMAND_TARGET )
							|| Skill == AT_SKILL_PLASMA_STORM_FENRIR // (���, ��ũ�ε�, ���˻�)
							)
						{
							Success = false;
						}
					}
					else
					{
						//ī���� ĳ���� �ƴϴ��� �׾����� ��ų ��� �Ұ���
						if( Skill == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
						{
							BYTE t_DarkLife = 0;
							t_DarkLife  = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
							if(t_DarkLife == 0) Success = false;
						}
					}
					
					if ( iMana>CharacterAttribute->Mana )
					{
						int Index = g_pMyInventory->FindManaItemIndex();
						if(Index != -1)
						{
							SendRequestUse(Index, 0);
						}
						Success = false;
					}
					if ( Success && iSkillMana>CharacterAttribute->SkillMana )
					{
						Success = false;
					}
                    if ( Success && !CheckSkillDelay( Hero->CurrentSkill ) )
                    {
                        Success = false;
                    }
					
					int iEnergy;	// ���̳ʽ� ���� �۾�
					GetSkillInformation_Energy(Skill, &iEnergy);
					if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
					{
						Success = false;
					}
					if(ClassIndex == CLASS_DARK_LORD)	// ��ũ�ε��̸�
					{
						int iCharisma;
						GetSkillInformation_Charisma(Skill, &iCharisma);	// �������Ʈ 
						if(iCharisma > (CharacterAttribute->Charisma + CharacterAttribute->AddCharisma) )
						{
							Success = false;
						}
					}
					
                    if ( Success )
                    {
                        //  ��ų.
                        switch(Skill)
                        {
						case AT_SKILL_TORNADO_SWORDA_UP:
						case AT_SKILL_TORNADO_SWORDA_UP+1:
						case AT_SKILL_TORNADO_SWORDA_UP+2:
						case AT_SKILL_TORNADO_SWORDA_UP+3:
						case AT_SKILL_TORNADO_SWORDA_UP+4:
							
						case AT_SKILL_TORNADO_SWORDB_UP:
						case AT_SKILL_TORNADO_SWORDB_UP+1:
						case AT_SKILL_TORNADO_SWORDB_UP+2:
						case AT_SKILL_TORNADO_SWORDB_UP+3:
						case AT_SKILL_TORNADO_SWORDB_UP+4:
                        case AT_SKILL_WHEEL:    //  ȸ���� ����.
                            o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
							{
								BYTE PathX[1];
								BYTE PathY[1];
								PathX[0] = ( c->PositionX);
								PathY[0] = ( c->PositionY);
								SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
                                WORD TKey = 0xffff;
                                if ( g_MovementSkill.m_iTarget!=-1 )
                                {
                                    TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                }
                                SendRequestMagicContinue(Skill,( c->PositionX),
                                    ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, 0);
                                SetAttackSpeed();
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
								switch(c->Helper.Type)
								{
								case MODEL_HELPER+2:	// ���ϸ���
									SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_UNI);
									break;
								case MODEL_HELPER+3:	// ����Ʈ
									SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_DINO);
									break;
								case MODEL_HELPER+37:	// �渱	
									SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
									break;
								default:	// �⺻
									SetAction(o, PLAYER_ATTACK_SKILL_WHEEL);
									break;
								}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
								SetAction(o,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                                c->Movement = 0;
                            }
                            break;
#ifdef PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_BLOOD_ATT_UP:
						case AT_SKILL_BLOOD_ATT_UP+1:
						case AT_SKILL_BLOOD_ATT_UP+2:
						case AT_SKILL_BLOOD_ATT_UP+3:
						case AT_SKILL_BLOOD_ATT_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
                        case AT_SKILL_REDUCEDEFENSE:    
                            o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                            {
#ifdef PSW_FRUIT_ITEM_CHECK_SKILL
								WORD Strength;
								const WORD notStrength = 596;
								Strength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
								if(Strength < notStrength)
								{
									break;
								}
#endif //PSW_FRUIT_ITEM_CHECK_SKILL
								if( CheckTile( c, o, Distance ) )
                                {
                                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
									
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), byValue, 0, TKey, 0);
                                    SetAttackSpeed();
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
									switch(c->Helper.Type)
									{
									case MODEL_HELPER+2:	// ���ϸ���
										SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_UNI);
										break;
									case MODEL_HELPER+3:	// ����Ʈ
										SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_DINO);
										break;
									case MODEL_HELPER+37:	// �渱	
										SetAction(o, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
										break;
									default:	// �⺻
										SetAction(o, PLAYER_ATTACK_SKILL_WHEEL);
										break;
									}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
									SetAction(o,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                                    c->Movement = 0;
                                }
                            }
                            break;
#ifdef PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_POWER_SLASH_UP:
						case AT_SKILL_POWER_SLASH_UP+1:
						case AT_SKILL_POWER_SLASH_UP+2:
						case AT_SKILL_POWER_SLASH_UP+3:
						case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4                            
                        case AT_SKILL_ICE_BLADE:
                            if ( c->Helper.Type<MODEL_HELPER+2 || c->Helper.Type>MODEL_HELPER+4
								&& c->Helper.Type != MODEL_HELPER+37
								)
                            {
								/*
#ifdef PJH_SEASON4_MASTER_RANK4
								bool jd = true;
								for(int j=0;j<2;j++)
								{
									if(Hero->Weapon[j].Type==MODEL_SWORD+21||Hero->Weapon[j].Type==MODEL_SWORD+23||Hero->Weapon[j].Type==MODEL_SWORD+28||
										Hero->Weapon[j].Type==MODEL_SWORD+25||Hero->Weapon[j].Type==MODEL_SWORD+31
										)	//21 = �������̵�,23 = �ͽ��÷������̵�,25 = �ҵ��,28 = ��ٽ�Ÿ��,31 = ������ε�
									{
										jd = false;
									}
								}
								if(jd == true)
									return;
#endif //PJH_SEASON4_MASTER_RANK4                            
*/
                                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                                
                                if( CheckTile( c, o, Distance ) )
                                {
									BYTE PathX[1];
									BYTE PathY[1];
									PathX[0] = ( c->PositionX);
									PathY[0] = ( c->PositionY);
									SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
									
                                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
									
                                    BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                                    SetAttackSpeed();
									if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
									{
										SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
									}
									else
									{
										SetAction(o,PLAYER_ATTACK_TWO_HAND_SWORD_TWO);
									}
                                    c->Movement = 0;
                                }
                            }
                            break;
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
						case AT_SKILL_GAOTIC:
                            {
                                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                                
                                if( CheckTile( c, o, Distance ) )
                                {
									BYTE PathX[1];
									BYTE PathY[1];
									PathX[0] = ( c->PositionX);
									PathY[0] = ( c->PositionY);
									SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
									
                                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
									
                                    BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                                    SetAttackSpeed();
									//									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
                                    c->Movement = 0;
									
//									SetPlayerMagic(c);
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
									if( c->Helper.Type == MODEL_HELPER+37 )				
									{
										SetAction( o, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
									}
#ifdef PBG_FIX_CHAOTIC_ANIMATION
									else if((c->Helper.Type>=MODEL_HELPER+2) && (c->Helper.Type<=MODEL_HELPER+4))
#else //PBG_FIX_CHAOTIC_ANIMATION
									else if((c->Helper.Type>=MODEL_HELPER+2) || (c->Helper.Type<=MODEL_HELPER+4))
#endif //PBG_FIX_CHAOTIC_ANIMATION
									{
										SetAction( o, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
									}
									else
									{
										SetAction( o, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
									}
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
									if(c->Helper.Type == MODEL_HELPER+37)
										SetAction(o,PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	//^ �渱
									else
										SetAction ( o, PLAYER_ATTACK_STRIKE );
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
									vec3_t Light,Position,P,dp;
									
									float Matrix[3][4];
									Vector(0.f,-20.f,0.f,P);
									Vector(0.f,0.f,0.f,P);
									AngleMatrix(o->Angle,Matrix);
									VectorRotate(P,Matrix,dp);
									VectorAdd(dp,o->Position,Position);
									
									Vector(0.5f, 0.5f, 0.5f, Light);
									for (int i = 0; i < 5; ++i)
									{
										CreateEffect(BITMAP_SHINY+6, Position, o->Angle, Light, 3, o, -1, 0, 0, 0, 0.5f);
									}
									
									VectorCopy(o->Position,Position);
									for(i=0;i<8;i++)
									{
										Position[0] = (o->Position[0] - 119.f) + (float)(rand()%240); 
										Position[2] = (o->Position[2] + 49.f) + (float)(rand()%60); 
										CreateJoint(BITMAP_2LINE_GHOST,Position,o->Position,o->Angle,0,o,20.f,o->PKKey,0,o->m_bySkillSerialNum);//Ŭ���̾�Ʈ����ó��
									}
#ifdef PJH_FIX_CAOTIC
					if(c==Hero && SelectedCharacter!=-1)
					{
						vec3_t Pos;
						CHARACTER *st = &CharactersClient[SelectedCharacter];
						VectorCopy(st->Object.Position,Pos);
						CreateBomb(Pos,true);
					}
#endif //PJH_FIX_CAOTIC
#ifdef YDG_FIX_CAOTIC_SOUND_MISSING
									PlayBuffer(SOUND_SKILL_CAOTIC);
#endif	// YDG_FIX_CAOTIC_SOUND_MISSING
                                }
								else
								{	// �־������� �� �ȱ�
									if(PathFinding2(( c->PositionX), ( c->PositionY),TargetX,TargetY,&c->Path, Distance ) )
									{	
										c->Movement = true;		// �ָ� �ɾ�� ���
									}
								}
                            }
							break;
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
                        case AT_SKILL_FLAME_STRIKE:
                            {
                                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                                
                                if( CheckTile( c, o, Distance ) )
                                {
									BYTE PathX[1];
									BYTE PathY[1];
									PathX[0] = ( c->PositionX);
									PathY[0] = ( c->PositionY);
									SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
									
                                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
									
                                    BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                                    SetAttackSpeed();
									SetAction(o, PLAYER_SKILL_FLAMESTRIKE);
                                    c->Movement = 0;
                                    //c->AttackTime = 15;
                                }
                            }
                            break;
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
                        case AT_SKILL_GIGANTIC_STORM:
                            {
                                o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
                                
                                if( CheckTile( c, o, Distance ) )
                                {
									BYTE PathX[1];
									BYTE PathY[1];
									PathX[0] = ( c->PositionX);
									PathY[0] = ( c->PositionY);
									SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
									
                                    BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
									
                                    BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
                                    SetAttackSpeed();
									SetAction(o, PLAYER_SKILL_GIGANTICSTORM);
                                    c->Movement = 0;
                                }
                            }
                            break;
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
							
                        case AT_SKILL_PARTY_TELEPORT:
							if( g_CursedTemple->IsCursedTemple() 
								&& !g_pMyInventory->IsItem( ITEM_POTION+64, true ) )
							{
								return;
							}
                            SendRequestMagic ( Skill, HeroKey );
                            c->Movement = 0;
                            break;
                            
                        case AT_SKILL_ADD_CRITICAL:
                            SendRequestMagic ( Skill, HeroKey );
							c->Movement = 0;
                            break;
                        case AT_SKILL_BRAND_OF_SKILL:
                            SendRequestMagic ( Skill, HeroKey );
                            c->Movement = 0;
                            break;
#ifdef PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_FIRE_SCREAM_UP:
						case AT_SKILL_FIRE_SCREAM_UP+1:
						case AT_SKILL_FIRE_SCREAM_UP+2:
						case AT_SKILL_FIRE_SCREAM_UP+3:
						case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_DARK_SCREAM:
                            if ( CheckTile( c, o, Distance ) )
                            {
                                int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                                int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                                BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                                
                                BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                                WORD TKey = 0xffff;
                                if ( g_MovementSkill.m_iTarget!=-1 )
                                {
                                    TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                }
                                o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
								CheckClientArrow(o);
                                SendRequestMagicContinue ( Skill, ( c->PositionX),
                                    ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
								
                                SetAttackSpeed();
                                //  �ִϸ��̼� ����.
                                {
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
									if ( (c->Helper.Type>=MODEL_HELPER+2 && c->Helper.Type<=MODEL_HELPER+4) && !c->SafeZone )
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
                                    if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )   
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
                                    {
                                        SetAction ( o, PLAYER_ATTACK_RIDE_STRIKE );
                                    }
									else if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
									{
										SetAction ( o, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );
									}
                                    else
                                    {
                                        SetAction ( o, PLAYER_ATTACK_STRIKE );
                                    }
                                }
                                c->Movement = 0;
                            }
                            else
                            {
                                Attacking = -1;
                            }
							break;
						case AT_SKILL_ASHAKE_UP:
						case AT_SKILL_ASHAKE_UP+1:
						case AT_SKILL_ASHAKE_UP+2:
						case AT_SKILL_ASHAKE_UP+3:
						case AT_SKILL_ASHAKE_UP+4:
                        case AT_SKILL_DARK_HORSE:
                            if ( c->Helper.Type!=MODEL_HELPER+4 || c->SafeZone ) break;
							
                        case AT_SKILL_THUNDER_STRIKE:
                            // ��� ���� ��� ��ǥ ���
                            // ��� ���� ��� ��ǥ ���
                            if ( CheckTile( c, o, Distance ) )
                            {
                                int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                                int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                                BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                                
                                BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                                WORD TKey = 0xffff;
                                if ( g_MovementSkill.m_iTarget!=-1 )
                                {
                                    TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                }
                                o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                                SendRequestMagicContinue ( Skill, ( c->PositionX),
                                    ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
                                SetAttackSpeed();
                                
                                //  �ִϸ��̼� ����.
                                if ( Skill==AT_SKILL_THUNDER_STRIKE )
                                {
                                    if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )   
                                    {
                                        SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_FLASH );
                                    }
									else if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)
									{
										SetAction ( o, PLAYER_FENRIR_ATTACK_DARKLORD_FLASH );
									}
                                    else
                                    {
                                        SetAction ( o, PLAYER_SKILL_FLASH );
                                    }
                                }
                                else if ( Skill==AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= Skill && Skill <= AT_SKILL_ASHAKE_UP+4))
                                {
                                    SetAction ( o, PLAYER_ATTACK_DARKHORSE );
                                    PlayBuffer ( SOUND_EARTH_QUAKE );
                                }
                                c->Movement = 0;
                            }
                            else
                            {
                                Attacking = -1;
                            }
                            break;
						case AT_SKILL_LIFE_UP:
						case AT_SKILL_LIFE_UP+1:
						case AT_SKILL_LIFE_UP+2:
						case AT_SKILL_LIFE_UP+3:
						case AT_SKILL_LIFE_UP+4:
                        case AT_SKILL_VITALITY:	// ����������
                            SendRequestMagic(Skill,HeroKey);
							SetAction(o,PLAYER_SKILL_VITALITY);
                            c->Movement = 0;
                            break;
							
							//--------------------------------------------------------------------------------------------------------------------
							
#ifdef PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_ANGER_SWORD_UP:
						case AT_SKILL_ANGER_SWORD_UP+1:
						case AT_SKILL_ANGER_SWORD_UP+2:
						case AT_SKILL_ANGER_SWORD_UP+3:
						case AT_SKILL_ANGER_SWORD_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4                            
                        case AT_SKILL_FURY_STRIKE:  //  ���� - �г��� �ϰ�
                            {
								o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
								
                                // ��� ���� ��� ��ǥ ���
                                int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                                int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                                if( CheckTile( c, o, Distance ) )
                                {
                                    BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill,( c->PositionX),
                                        ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, 0);
									SetAction(o,PLAYER_ATTACK_SKILL_FURY_STRIKE);
                                    c->Movement = 0;
                                }
                                else
                                {
                                    Attacking = -1;
                                }
                            }
                            break;
							
							//--------------------------------------------------------------------------------------------------------------------
							
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
							// ���� - �ı��� �ϰ�
						case AT_SKILL_BLOW_OF_DESTRUCTION:
							{
								o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
								
                                // ��� ���� ��� ��ǥ ���
                                int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                                int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                                if( CheckTile( c, o, Distance ) )
                                {
                                    BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
                                    WORD TKey = 0xffff;
                                    if ( g_MovementSkill.m_iTarget!=-1 )
                                    {
                                        TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                    }
                                    SendRequestMagicContinue(Skill, TargetX, TargetY, (BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, 0);
									SetAction(o,PLAYER_SKILL_BLOW_OF_DESTRUCTION);
                                    c->Movement = 0;
                                }
                                else
                                {
                                    Attacking = -1;
                                }
							}
							break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
							
							//--------------------------------------------------------------------------------------------------------------------
							
							//^ �渱 ��ų ����
						case AT_SKILL_PLASMA_STORM_FENRIR: // (���, ��ũ�ε�, ���˻�)
							{
								// ��� ���� ��� ��ǥ ���
								int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
								int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
								if( CheckTile( c, o, Distance ) )
								{
									
									BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
									WORD TKey = 0xffff;
									if(g_MovementSkill.m_iTarget!=-1)
									{
										o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
										
										CheckSkillDelay(Hero->CurrentSkill);
										
										TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
										c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
										SendRequestMagicContinue(Skill,( c->PositionX),
											( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
										c->Movement = 0;
										
										if(o->Type == MODEL_PLAYER)
										{
											SetAction_Fenrir_Skill(c, o);
										}
									}
									else
									{
										c->m_iFenrirSkillTarget = -1;
									}
								}
								else
								{
									if(g_MovementSkill.m_iTarget!=-1)
									{
										if(PathFinding2(( c->PositionX),( c->PositionY),
											TargetX,TargetY,&c->Path, Distance*1.2f ) )
										{	// �ָ� �ɾ�� ���
											c->Movement = true;
										}
									}
									else
									{
										Attacking = -1;
									}
								}
							}	// case
							break;
                        } // switch
                    }
                }
			}
			if ( ClassIndex==CLASS_WIZARD		// �渶���� �̰ų�
				|| ClassIndex==CLASS_DARK		// ���˻� �̰ų�
				|| ClassIndex==CLASS_SUMMONER	// ��ȯ���� �̰ų� : �渶����� ���� ��ų(�, ���̾, ����, �Ŀ����̺�)�� ���� �߰�.
				)
			{
				
				int iMana, iSkillMana;
				if( Skill == AT_SKILL_BLAST_HELL_BEGIN || Skill == AT_SKILL_BLAST_HELL )
				{
					GetSkillInformation( AT_SKILL_BLAST_HELL, 1, NULL, &iMana, NULL, &iSkillMana);
					
                    if ( Skill==AT_SKILL_BLAST_HELL )
                    {
						iSkillMana = 0;
                    }
				}
				else
				{
					GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
				}
				
				int iEnergy;	// ���̳ʽ� ���� �۾�
				GetSkillInformation_Energy(Skill, &iEnergy);
				if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
				{
					return;
				}
				
				if(iMana > CharacterAttribute->Mana)
				{
					int Index = g_pMyInventory->FindManaItemIndex();
					if(Index != -1)
					{
						SendRequestUse(Index, 0);
					}
					return;
				}
				// skillmana ����
				if(iSkillMana > CharacterAttribute->SkillMana)
				{
					if ( Skill==AT_SKILL_BLAST_HELL_BEGIN || Skill==AT_SKILL_BLAST_HELL )
                    {
						MouseRButtonPop = false;
						MouseRButtonPush= false;
						MouseRButton	= false;
						
						MouseRButtonPress = 0;
                    }
					return;
				}

                if ( CheckSkillDelay( Hero->CurrentSkill ) == false)
                {
                    return;
                }
                bool Success = CheckTarget(c);
				switch(Skill)
				{
					//	����2 �غ��ڼ�.
				case AT_SKILL_BLAST_HELL_BEGIN:
					{
						SendRequestMagic ( Skill, HeroKey );
						
						SetAttackSpeed();
						SetAction(o,PLAYER_SKILL_HELL_BEGIN);
						c->Movement = 0;
					}
					return;
					
					//	����2 �߻�.
				case AT_SKILL_BLAST_HELL:
					{
						int iTargetKey = getTargetCharacterKey(c, SelectedCharacter);
						if(iTargetKey == -1) {
							iTargetKey = HeroKey;
						}
						SendRequestMagic(Skill,iTargetKey);
						
						SetAttackSpeed();
						SetAction(o,PLAYER_SKILL_HELL_START);
						c->Movement = 0;
					}
					return;
				case AT_SKILL_SOUL_UP:
				case AT_SKILL_SOUL_UP+1:
				case AT_SKILL_SOUL_UP+2:
				case AT_SKILL_SOUL_UP+3:
				case AT_SKILL_SOUL_UP+4:
				case AT_SKILL_WIZARDDEFENSE:
					if( SelectedCharacter != -1)
					{
						if ( CharactersClient[SelectedCharacter].Object.Kind!=KIND_PLAYER)
						{
							Attacking = -1;
							return;
						}
						else
						{
                            //  ��Ƽ���ΰ�.
							if ( !g_pPartyManager->IsPartyMember( SelectedCharacter ) ) 
									return;
								
								c->TargetCharacter = SelectedCharacter;
								
								if ( SelectedCharacter != -1)
								{
									ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
									g_MovementSkill.m_bMagic = TRUE;
									g_MovementSkill.m_iSkill = Hero->CurrentSkill;
									g_MovementSkill.m_iTarget = SelectedCharacter;
								}
								
								if(!CheckTile(c,o, Distance))
								{
									if(SelectedCharacter != -1)
									{
										if(PathFinding2(( c->PositionX),( c->PositionY),
											TargetX,TargetY,&c->Path, Distance))
										{
											c->Movement = true;
											c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
											SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
										}
									}
									
									return;
								}
								
								SendRequestMagic(Skill,CharactersClient[g_MovementSkill.m_iTarget].Key);
						}
					}
					else
					{
						SendRequestMagic(Skill,HeroKey);
					}
					SetPlayerMagic(c);
					break;
				case AT_SKILL_HELL_FIRE_UP:
				case AT_SKILL_HELL_FIRE_UP+1:
				case AT_SKILL_HELL_FIRE_UP+2:
				case AT_SKILL_HELL_FIRE_UP+3:
				case AT_SKILL_HELL_FIRE_UP+4:
				case AT_SKILL_HELL:
					{
						SendRequestMagicContinue(Skill,( c->PositionX),
							( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
						SetAttackSpeed();
						SetAction(o,PLAYER_SKILL_HELL);
						c->Movement = 0;
					}
					return;
				case AT_SKILL_INFERNO:
					{
						SendRequestMagicContinue(Skill,( c->PositionX),
							( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
						SetAttackSpeed();
						SetAction(o,PLAYER_SKILL_INFERNO);
						c->Movement = 0;
					}
					return;
					//^ �渱 ��ų ����
				case AT_SKILL_PLASMA_STORM_FENRIR:	// (������)
					{
						if ( CheckAttack() )
						{
							g_MovementSkill.m_iTarget = SelectedCharacter;
						}
						else
						{
							g_MovementSkill.m_iTarget = -1;
						}
						
						// ��� ���� ��� ��ǥ ���
						int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
						int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
						if( CheckTile( c, o, Distance ) )//&& CheckAttack())
						{
							BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0],c->TargetPosition[1]);
							WORD TKey = 0xffff;
							if ( g_MovementSkill.m_iTarget != -1 )
							{
								o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
								
								CheckSkillDelay(Hero->CurrentSkill);
								
								TKey = getTargetCharacterKey(c, g_MovementSkill.m_iTarget);
								c->m_iFenrirSkillTarget = g_MovementSkill.m_iTarget;
								SendRequestMagicContinue(Skill,( c->PositionX),
									( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, pos, TKey, &o->m_bySkillSerialNum);
								c->Movement = 0;
								
								if(o->Type == MODEL_PLAYER)
								{
									SetAction_Fenrir_Skill(c, o);
								}
							}
							else
							{
								c->m_iFenrirSkillTarget = -1;
							}
						}
						else
						{
							if(g_MovementSkill.m_iTarget != -1)
							{
								if(PathFinding2(( c->PositionX),( c->PositionY),
									TargetX,TargetY,&c->Path, Distance*1.2f ) )
								{	// �ָ� �ɾ�� ���
									c->Movement = true;
								}
							}
							else
							{
								Attacking = -1;
							}
						}
					}
					return;
					
                    //  ���� ��ų�� ����.
                case AT_SKILL_BLOCKING :
                case AT_SKILL_SWORD1 :
                case AT_SKILL_SWORD2 :
                case AT_SKILL_SWORD3 :
                case AT_SKILL_SWORD4 :
                case AT_SKILL_SWORD5 :
                case AT_SKILL_SPEAR:
					return;
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
				case AT_SKILL_SWELL_OF_MAGICPOWER:		// ��������
					{
						// �������� ��ų������ �ȵǾ� �������� ��������
						if(g_isCharacterBuff((&Hero->Object), eBuff_SwellOfMagicPower) == false)
						{
							SendRequestMagic(Skill, HeroKey);
							
							c->Movement = 0;
						}
					}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
				}
				
				if ( SelectedCharacter != -1)
				{
					ZeroMemory( &g_MovementSkill, sizeof ( g_MovementSkill));
					g_MovementSkill.m_bMagic = TRUE;
					g_MovementSkill.m_iSkill = Hero->CurrentSkill;
					if ( CheckAttack() )
					{
						g_MovementSkill.m_iTarget = SelectedCharacter;
					}
					else
					{
						g_MovementSkill.m_iTarget = -1;
					}
				}
				
				if(!CheckTile(c,o, Distance ))
				{
					if(SelectedCharacter != -1 && CheckAttack())
					{
						if(PathFinding2(( c->PositionX),( c->PositionY),
							TargetX,TargetY,&c->Path, Distance ))
						{
							c->Movement = true;
							c->MovementType = MOVEMENT_SKILL;
#ifdef CSK_FIX_SYNCHRONIZATION
							SendMove(c, o);
#endif // CSK_FIX_SYNCHRONIZATION
						}
					}

					// �Ʒ� ��ų���� Ŭ�� �� ��ų ���� üũ ����.(�� ���⼭ �ϴ���...�Ѥ�;)
					if (Skill != AT_SKILL_STUN && Skill != AT_SKILL_REMOVAL_STUN
						&& Skill != AT_SKILL_MANA && Skill != AT_SKILL_INVISIBLE
						&& Skill != AT_SKILL_REMOVAL_INVISIBLE && Skill != AT_SKILL_PLASMA_STORM_FENRIR	// (������)
#ifdef ASG_ADD_SKILL_BERSERKER
						&& Skill != AT_SKILL_ALICE_BERSERKER
#endif	// ASG_ADD_SKILL_BERSERKER
						&& Skill != AT_SKILL_ALICE_WEAKNESS && Skill != AT_SKILL_ALICE_ENERVATION
						)
						return;
				}
				
				bool Wall = CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY);
				if(Wall)
				{
					if(SelectedCharacter != -1)
					{
						if(CheckAttack())
						{
							UseSkillWizard( c, o);
						}
					}
					if(Success)
					{
						o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
						switch(Skill)
						{
						case AT_SKILL_STORM:
#ifdef PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_EVIL_SPIRIT_UP:	//�Ƿɰ�ȭ(�渶�����)
						case AT_SKILL_EVIL_SPIRIT_UP+1:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP+2:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP+3:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP+4:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP_M:		//�Ƿɰ�ȭ(���˻��)
						case AT_SKILL_EVIL_SPIRIT_UP_M+1:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP_M+2:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP_M+3:	//�Ƿɰ�ȭ
						case AT_SKILL_EVIL_SPIRIT_UP_M+4:	//�Ƿɰ�ȭ
#endif //PJH_SEASON4_MASTER_RANK4
						case AT_SKILL_EVIL:
							{
#ifdef CSK_EVIL_SKILL
								WORD TKey = 0xffff;
								if ( g_MovementSkill.m_iTarget!=-1 )
								{
									TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
								}
								SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, &o->m_bySkillSerialNum );
#else // CSK_EVIL_SKILL
								SendRequestMagicContinue(Skill,( c->PositionX), ( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, &o->m_bySkillSerialNum);
#endif // CSK_EVIL_SKILL
								
								SetPlayerMagic(c);
							}
							return;
						case AT_SKILL_FLASH:
							{
								SendRequestMagicContinue(Skill,( c->PositionX),
									( c->PositionY),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
								SetAttackSpeed();
								
								if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)	//^ �渱 ĳ���� ���ϸ��̼� ����(������÷���)
									SetAction(o,PLAYER_SKILL_FLASH);
								else
									SetAction(o,PLAYER_SKILL_FLASH);
								
								c->Movement = 0;
								StandTime = 0;
							}
							return;
						case AT_SKILL_FLAME:
							SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, 0xffff, 0);
							SetPlayerMagic(c);
							return;
						case AT_SKILL_BLAST_POISON:
						case AT_SKILL_ICE_UP:
						case AT_SKILL_ICE_UP+1:
						case AT_SKILL_ICE_UP+2:
						case AT_SKILL_ICE_UP+3:
						case AT_SKILL_ICE_UP+4:
						case AT_SKILL_BLAST_FREEZE:
							{
								WORD TKey = 0xffff;
								if ( g_MovementSkill.m_iTarget!=-1 )
								{
									TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
								}
								SendRequestMagicContinue(Skill,(BYTE)(c->TargetPosition[0]/TERRAIN_SCALE),(BYTE)(c->TargetPosition[1]/TERRAIN_SCALE),(BYTE)(o->Angle[2]/360.f*256.f), 0, 0, TKey, 0 );
								SetPlayerMagic(c);
								c->Movement = 0;
							}
							return;
						}
					}
				}
				if ( ClassIndex==CLASS_WIZARD && Success)
				{
					switch(Skill)
					{
                    case AT_SKILL_TELEPORT_B:
						if( g_CursedTemple->IsCursedTemple() 
							&& !g_pMyInventory->IsItem( ITEM_POTION+64, true ) )
						{
							return;
						}
                        if ( SelectedCharacter!=-1 )
                        {
							//  ��Ƽ���ΰ�.
							if ( !g_pPartyManager->IsPartyMember( SelectedCharacter ) ) 
								return;
							
							if (SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
							{	// �������� ��� ������ �ڷ���Ʈ���� ���Ѵ�.
								return;
							}
							
							CHARACTER* tc = &CharactersClient[SelectedCharacter];
							OBJECT*    to = &tc->Object;
							bool Success = false;
							if(to->Type == MODEL_PLAYER)
							{
								if(to->CurrentAction != PLAYER_SKILL_TELEPORT)
									Success = true;
							}
							else
							{
								if(to->CurrentAction != MONSTER01_SHOCK)
									Success = true;
							}
							if(Success && to->Teleport!=TELEPORT_BEGIN && to->Teleport!=TELEPORT && to->Alpha>=0.7f)
							{
								int Wall, indexX, indexY, TargetIndex, count=0;
								int PositionX = (int)(c->Object.Position[0]/TERRAIN_SCALE);
								int PositionY = (int)(c->Object.Position[1]/TERRAIN_SCALE);
								
								while ( 1 )
								{
									indexX = rand()%3;
									indexY = rand()%3;
									
									if ( indexX!=1 || indexY!=1 )
									{
										TargetX = (PositionX-1)+indexX;
										TargetY = (PositionY-1)+indexY;
										
										TargetIndex = TERRAIN_INDEX( TargetX, TargetY );
										
										Wall = TerrainWall[TargetIndex];
										//  
										if ( (Wall&TW_ACTION)==TW_ACTION )
										{
											Wall -= TW_ACTION;
										}
										if(World == WD_30BATTLECASTLE)
										{
											int ax = (Hero->PositionX);
											int ay = (Hero->PositionY);
											if ( (ax>=150 && ax<=200) && (ay>=180&& ay<=230))  
												Wall = 0;
										}
										if(Wall == 0) break;
										
										count++;
									}
									
									if ( count>10 ) return;
								}
								to->Angle[2] = CreateAngle(to->Position[0],to->Position[1],tc->TargetPosition[0],tc->TargetPosition[1]);
								bool bResult;
								SendRequestMagicTeleportB(&bResult,tc->Key,TargetX,TargetY);
								if ( bResult )
								{
									SetPlayerTeleport(tc);
								}
							}
                        }
                        return;
						
					case AT_SKILL_TELEPORT:	//�渶��������̵�
                        {
							if ( SEASON3B::CNewUIInventoryCtrl::GetPickedItem()		// �������� ��� ������ �ڷ���Ʈ���� ���Ѵ�.
								|| g_isCharacterBuff(o, eDeBuff_Stun)
								|| g_isCharacterBuff(o, eDeBuff_Sleep)
								)
							{	
								return;
							}
							bool Success = false;
							if(o->Type == MODEL_PLAYER)
							{
								if(o->CurrentAction != PLAYER_SKILL_TELEPORT)
									Success = true;
							}
							else
							{
								if(o->CurrentAction != MONSTER01_SHOCK)
									Success = true;
							}
							if(Success && o->Teleport!=TELEPORT_BEGIN && o->Teleport!=TELEPORT && o->Alpha>=0.7f)
							{
								int TargetIndex = TERRAIN_INDEX_REPEAT(TargetX,TargetY);
                                int Wall = TerrainWall[TargetIndex];
                                if ( (Wall&TW_ACTION)==TW_ACTION ) Wall -= TW_ACTION;
                                if ( (Wall&TW_HEIGHT)==TW_HEIGHT ) Wall -= TW_HEIGHT;
								if(Wall == 0)
								{
									o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
									bool bResult;
									SendRequestMagicTeleport(&bResult,0,TargetX,TargetY);
									if ( bResult)
									{
										if(g_isCharacterBuff(o, eDeBuff_Stun))
										{
											UnRegisterBuff( eDeBuff_Stun, o );
										}
										
										if(g_isCharacterBuff(o, eDeBuff_Sleep))
										{
											UnRegisterBuff( eDeBuff_Sleep, o );
										}
										
										SetPlayerTeleport(c);
									}
								}
							}
                        }
						return;
					}
				}
				else if ( ClassIndex==CLASS_SUMMONER && Success)
				{
					if (g_SummonSystem.SendRequestSummonSkill(Skill, c, o) == TRUE)
					{
						return;
					}
					
					int iEnergy;
					GetSkillInformation_Energy(Skill, &iEnergy);
					if(iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy) )
					{
						return;
					}
					
					g_MovementSkill.m_bMagic = TRUE;
					g_MovementSkill.m_iSkill = Hero->CurrentSkill;
					g_MovementSkill.m_iTarget = SelectedCharacter;
					
					switch(Skill)
					{
					case AT_SKILL_ALICE_THORNS:		// ������ �ݻ�(���� �迭) �������Ը� ���
						{
							// �ƹ��͵� ������ �ȵǾ����� �ڱ� �ڽſ��� ���
							if(SelectedCharacter == -1 || CharactersClient[SelectedCharacter].Object.Kind != KIND_PLAYER)
							{
								LetHeroStop();
								// ���� ����
								switch(c->Helper.Type)
								{
								case MODEL_HELPER+2:	// ���ϸ���
									SetAction(o, PLAYER_SKILL_SLEEP_UNI);
									break;
								case MODEL_HELPER+3:	// ����Ʈ
									SetAction(o, PLAYER_SKILL_SLEEP_DINO);
									break;
								case MODEL_HELPER+37:	// �渱	
									SetAction(o, PLAYER_SKILL_SLEEP_FENRIR);
									break;
								default:	// �⺻
									SetAction(o, PLAYER_SKILL_SLEEP);
									break;
								}
								SendRequestMagic(Skill, HeroKey);
							}
							// ���� �ʾҰų� �÷��̾��� ���
							else if(0 == CharactersClient[SelectedCharacter].Dead && CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
							{	
								TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
								TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
								
								if(CheckTile( c, o, Distance ) && c->SafeZone == false)
								{
									bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
									if(bNoneWall)
									{
										UseSkillSummon(c, o);
									}
								}
								else
								{	// �־������� �� �ȱ�
									if(PathFinding2(( c->PositionX), ( c->PositionY),TargetX,TargetY,&c->Path, Distance ) )
									{	
										c->Movement = true;		// �ָ� �ɾ�� ���
									}
								}
							}
						}
						break;
#ifdef ASG_ADD_SKILL_BERSERKER
					case AT_SKILL_ALICE_BERSERKER:
#endif	// ASG_ADD_SKILL_BERSERKER
					case AT_SKILL_ALICE_WEAKNESS:
					case AT_SKILL_ALICE_ENERVATION:
						UseSkillSummon(c, o);
						break;
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_LIGHTNING_SHOCK_UP:
		case AT_SKILL_LIGHTNING_SHOCK_UP+1:
		case AT_SKILL_LIGHTNING_SHOCK_UP+2:
		case AT_SKILL_LIGHTNING_SHOCK_UP+3:
		case AT_SKILL_LIGHTNING_SHOCK_UP+4:
#endif
					case AT_SKILL_LIGHTNING_SHOCK:
						{
							o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->TargetPosition[0],c->TargetPosition[1]);
							
							if( CheckTile( c, o, Distance ) )
							{
								BYTE PathX[1];
								BYTE PathY[1];
								PathX[0] = ( c->PositionX);
								PathY[0] = ( c->PositionY);
								SendCharacterMove(c->Key,o->Angle[2],1,&PathX[0],&PathY[0],TargetX,TargetY);
								
								BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
								
								BYTE angle = (BYTE)((((o->Angle[2]+180.f)/360.f)*255.f));
								WORD TKey = 0xffff;
								if ( g_MovementSkill.m_iTarget!=-1 )
								{
									TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
								}
								SendRequestMagicContinue(Skill,( c->PositionX),
									( c->PositionY),((o->Angle[2]/360.f)*255), byValue, angle, TKey, 0 );
								SetAttackSpeed();
								SetAction(o, PLAYER_SKILL_LIGHTNING_SHOCK);
								c->Movement = 0;
							}
						}
						break;
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
					}
					
					if(SelectedCharacter == -1)
					{
						return;
					}
					
					switch(Skill)
					{
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_DRAINLIFE_UP:
		case AT_SKILL_ALICE_DRAINLIFE_UP+1:
		case AT_SKILL_ALICE_DRAINLIFE_UP+2:
		case AT_SKILL_ALICE_DRAINLIFE_UP+3:
		case AT_SKILL_ALICE_DRAINLIFE_UP+4:
#endif
					case AT_SKILL_ALICE_DRAINLIFE:
					case AT_SKILL_ALICE_LIGHTNINGORB:
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+1:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+2:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+3:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+4:
#endif
					case AT_SKILL_ALICE_CHAINLIGHTNING:
						{
							c->TargetCharacter = SelectedCharacter;
							// ���׾��� ���� ���
							if(0 == CharactersClient[SelectedCharacter].Dead )
							{	
								TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
								TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
								
								if(CheckAttack() == true)
								{
									if(CheckTile( c, o, Distance ) && c->SafeZone == false)
									{
										bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
										if(bNoneWall)
										{
											UseSkillSummon(c, o);
										}
									}
									else
									{	// �־������� �� �ȱ�
										if(PathFinding2(( c->PositionX), ( c->PositionY),TargetX,TargetY,&c->Path, Distance ) )
										{	
											c->Movement = true;		// �ָ� �ɾ�� ���
										}
									}
								}
							}
						}
						break;
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_SLEEP_UP:
		case AT_SKILL_ALICE_SLEEP_UP+1:
		case AT_SKILL_ALICE_SLEEP_UP+2:
		case AT_SKILL_ALICE_SLEEP_UP+3:
		case AT_SKILL_ALICE_SLEEP_UP+4:
#endif
					case AT_SKILL_ALICE_SLEEP:
					case AT_SKILL_ALICE_BLIND:		
						{
							if(CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
							{
								if(
									InChaosCastle() == true							// ī����ĳ��
									|| g_CursedTemple->IsCursedTemple() == true		// ȯ�����
									|| (battleCastle::InBattleCastle() == true && battleCastle::IsBattleCastleStart() == true) // �������̰� ��������
									|| g_bEnableDuel == true	// ������
									)
								{
									// ī����ĳ���̰ų� ȯ������̰ų� �������̰ų� �������̸� �Ϲݻ���ڵ� ����� ��ų�� ����� �� �ִ�.
								}
								else
								{
									break;
								}
							}
							
							// ���׾��� ���� ���
							if(0 == CharactersClient[SelectedCharacter].Dead )
							{	
								TargetX = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[0]/TERRAIN_SCALE);
								TargetY = (int)(CharactersClient[g_MovementSkill.m_iTarget].Object.Position[1]/TERRAIN_SCALE);
								
								if(CheckAttack() == true)
								{
									if(CheckTile( c, o, Distance ) && c->SafeZone == false)
									{
										bool bNoneWall = CheckWall(( c->PositionX), ( c->PositionY),TargetX,TargetY);
										if(bNoneWall)
										{
											UseSkillSummon(c, o);
										}
									}
									else
									{	// �־������� �� �ȱ�
										if(PathFinding2(( c->PositionX), ( c->PositionY),TargetX,TargetY,&c->Path, Distance ) )
										{	
											c->Movement = true;		// �ָ� �ɾ�� ���
										}
									}
								}
							}
						}
						break;
					}
				}
			}
			
            //  �������� ���Ǵ� ��ų.
            if ( (Skill>= AT_SKILL_STUN && Skill<=AT_SKILL_REMOVAL_BUFF ))
            {
				int iMana, iSkillMana;
				GetSkillInformation( Skill, 1, NULL, &iMana, NULL, &iSkillMana);
				
                if ( o->Type==MODEL_PLAYER )
                {
					bool Success = true;
					
					if ( iMana>CharacterAttribute->Mana )
					{
						int Index = g_pMyInventory->FindManaItemIndex();
						if(Index != -1)
						{
							SendRequestUse(Index, 0);
						}
						Success = false;
					}
					if ( Success && iSkillMana>CharacterAttribute->SkillMana )
					{
						Success = false;
					}
                    if ( Success && !CheckSkillDelay( Hero->CurrentSkill ) )
                    {
                        Success = false;
                    }
					
					int iEnergy;	// ���̳ʽ� ���� �۾�
					GetSkillInformation_Energy(Skill, &iEnergy);
					if(Success && iEnergy > (CharacterAttribute->Energy + CharacterAttribute->AddEnergy))
					{
						Success = false;
					}
					
                    switch ( Skill )
                    {
                    case    AT_SKILL_STUN:
						{
							//	                        if ( CheckTile( c, o, Distance ) )
                            {
                                o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
								
                                int TargetX = (int)(c->TargetPosition[0]/TERRAIN_SCALE);
                                int TargetY = (int)(c->TargetPosition[1]/TERRAIN_SCALE);
                                BYTE byValue = GetDestValue( ( c->PositionX), ( c->PositionY), TargetX, TargetY);
                                
                                BYTE pos = CalcTargetPos ( o->Position[0], o->Position[1], c->TargetPosition[0], c->TargetPosition[1] );
                                WORD TKey = 0xffff;
                                if ( g_MovementSkill.m_iTarget!=-1 )
                                {
                                    TKey = getTargetCharacterKey ( c, g_MovementSkill.m_iTarget );
                                }
                                SendRequestMagicContinue ( Skill, ( c->PositionX),
                                    ( c->PositionY), (BYTE)(o->Angle[2]/360.f*256.f), byValue, pos, TKey, 0);
								SetAttackSpeed();
								
								if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
								{
									SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
								} 
								else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
								{
									SetAction(o,PLAYER_SKILL_RIDER);
								}
								else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
								{
									SetAction(o,PLAYER_SKILL_RIDER_FLY);
								}
								else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
								{
									SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
								}
								else
								{
									SetAction ( o, PLAYER_SKILL_VITALITY );
								}
								c->Movement = 0;
							}
						}
                        break;
						
                    case    AT_SKILL_REMOVAL_STUN:
						{
							if(SelectedCharacter == -1)
							{
								SendRequestMagic ( Skill, HeroKey );
							}
							else
							{
								SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
							}
							
							
							if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
							{
								SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
							} 
							else
								if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
								{
									SetAction(o,PLAYER_SKILL_RIDER);
								}
								else
									if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
									{
										SetAction(o,PLAYER_SKILL_RIDER_FLY);
									}
									else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
									{
										SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
									}
									else
									{
										SetAction ( o, PLAYER_ATTACK_REMOVAL );
									}
									c->Movement = 0;
						}
                        break;
						
                    case    AT_SKILL_MANA:
                        if(SelectedCharacter == -1)
						{
							SendRequestMagic ( Skill, HeroKey );
						}
						else
						{
							SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
						}
						
						if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
						{
							SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
						} 
						else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER);
						}
						else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER_FLY);
						}
						else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
							SetAction ( o, PLAYER_SKILL_VITALITY );
                        c->Movement = 0;
                        break;
						
                    case    AT_SKILL_INVISIBLE:
						
						if(SelectedCharacter == -1)
						{
							SendRequestMagic ( Skill, HeroKey );
						}
						else
						{
#ifdef REPAIR_BUG_MAY1
							if(CharactersClient[SelectedCharacter].Object.Kind == KIND_PLAYER)
#endif
								SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
						}
						
						if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
						{
							SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
						} 
						else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER);
						}
						else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER_FLY);
						}
						else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
							SetAction ( o, PLAYER_SKILL_VITALITY );
                        c->Movement = 0;
                        break;
						
                    case    AT_SKILL_REMOVAL_INVISIBLE:
                        //SendRequestMagic ( Skill, HeroKey );
						
						if(SelectedCharacter == -1)
						{
							SendRequestMagic ( Skill, HeroKey );
						}
						else
						{
							SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
						}
						
						if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
						{
							SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
						} 
						else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER);
						}
						else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER_FLY);
						}
						else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
							SetAction ( o, PLAYER_ATTACK_REMOVAL );
                        c->Movement = 0;
                        break;
						
                    case    AT_SKILL_REMOVAL_BUFF:
						
                        if(SelectedCharacter == -1)
						{
							SendRequestMagic ( Skill, HeroKey );
						}
						else
						{
							SendRequestMagic(Skill,CharactersClient[SelectedCharacter].Key);
						}
						
						if ( c->Helper.Type==MODEL_HELPER+4 && !c->SafeZone )
						{
							SetAction ( o, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
						} 
						else if( c->Helper.Type==MODEL_HELPER+2 && !c->SafeZone)         //  ���ϸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER);
						}
						else if( c->Helper.Type==MODEL_HELPER+3 && !c->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(o,PLAYER_SKILL_RIDER_FLY);
						}
						else if(c->Helper.Type==MODEL_HELPER+37 && !c->SafeZone)	// �渱 Ÿ�� ������
						{
							SetAction(o, PLAYER_FENRIR_ATTACK_MAGIC);
						}
						else
							SetAction ( o, PLAYER_SKILL_VITALITY );
                        c->Movement = 0;
                        break;
                    }
                }
            }
#endif	// YDG_FIX_SPLIT_ATTACK_FUNC
		}
	}
	
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}


BOOL g_bWhileMovingZone = FALSE;	// �� ���̸� ������ ���̴�.
DWORD g_dwLatestZoneMoving = 0;	// ���� �ֱٿ� �� ���̸� ���� ����


///////////////////////////////////////////////////////////////////////////////
// ���� ��ǥ�� ����Ʈ�� ���� üũ�ؼ� ����Ʈ���� ��� �̵��ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void CheckGate()
{
	// ������ ����ְų�, ȯ��������� ������ �κ��� ������ ������ ���̵��� ���� ���Ѵ�.
	if( ( g_pMyInventory->IsItem( ITEM_POTION+64, true ) ) || 
		( g_CursedTemple->IsCursedTemple() && g_pMyInventory->IsItem( ITEM_POTION+64, false ) ) )
	{
		return;
	}
	
	for(int i=0;i<MAX_GATES;i++)
	{
		GATE_ATTRIBUTE *gs = &GateAttribute[i];
		if(gs->Flag==1 && gs->Map==World)
		{
			if(( Hero->PositionX)>=gs->x1 && ( Hero->PositionY)>=gs->y1 &&
				( Hero->PositionX)<=gs->x2 && ( Hero->PositionY)<=gs->y2)
			{
				GATE_ATTRIBUTE *gt = &GateAttribute[gs->Target];
				if(( LoadingWorld)==0 && Hero->JumpTime==0)
				{
					bool Success = false;
					int Level;
					
					if ( GetBaseClass(Hero->Class)==CLASS_DARK || GetBaseClass(Hero->Class)==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK
						|| GetBaseClass(Hero->Class)==CLASS_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK
						)
						Level = gs->Level*2/3;
					else
						Level = gs->Level;
					
					if(i == 28)//��Ÿ�Ա�
					{
						if(CharacterAttribute->Level>=Level)
							Success = true;
					}
					else
						Success = true;
					if(Success)
					{
						if( ( (i>=45 && i<=49) ||(i>=55 && i<=56) ) && 
                            ( ( CharacterMachine->Equipment[EQUIPMENT_HELPER].Type>=ITEM_HELPER+2  && CharacterMachine->Equipment[EQUIPMENT_HELPER].Type<=ITEM_HELPER+3 ) ) )
						{
							// 261 "�̵� ������ Ÿ��� ��Ʋ������ ���� �� �����ϴ�."
							g_pChatListBox->AddText("", GlobalText[261], SEASON3B::TYPE_ERROR_MESSAGE);
						}
						else if( ( 62<=i && i<=65) &&
							!( ( CharacterMachine->Equipment[EQUIPMENT_WING].Type>=ITEM_WING && CharacterMachine->Equipment[EQUIPMENT_WING].Type<=ITEM_WING+6 
							|| CharacterMachine->Equipment[EQUIPMENT_HELPER].Type==ITEM_HELPER+4 
							|| CharacterMachine->Equipment[EQUIPMENT_WING].Type==ITEM_HELPER+30 
							) || CharacterMachine->Equipment[EQUIPMENT_HELPER].Type==ITEM_HELPER+3 
							|| CharacterMachine->Equipment[EQUIPMENT_HELPER].Type==ITEM_HELPER+37
#ifdef ADD_ALICE_WINGS_1
							|| (CharacterMachine->Equipment[EQUIPMENT_WING].Type>=ITEM_WING+36 && CharacterMachine->Equipment[EQUIPMENT_WING].Type<=ITEM_WING+43)
#else	// ADD_ALICE_WINGS_1
							|| ( CharacterMachine->Equipment[EQUIPMENT_WING].Type>=ITEM_WING+36 && CharacterMachine->Equipment[EQUIPMENT_WING].Type<=ITEM_WING+40 )
#endif	// ADD_ALICE_WINGS_1
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
							|| ( ITEM_WING+130 <= CharacterMachine->Equipment[EQUIPMENT_WING].Type && CharacterMachine->Equipment[EQUIPMENT_WING].Type <= ITEM_WING+134 )
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
							|| (CharacterMachine->Equipment[EQUIPMENT_WING].Type>=ITEM_WING+49 && CharacterMachine->Equipment[EQUIPMENT_WING].Type<=ITEM_WING+50)
							|| (CharacterMachine->Equipment[EQUIPMENT_WING].Type==ITEM_WING+135)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
							))
						{	// ������ �䰡�þƸ� ���� �ؾ� ��
							g_pChatListBox->AddText("", GlobalText[263], SEASON3B::TYPE_ERROR_MESSAGE);
                            //  ���� ���ѿ� �ɸ����� ���������� ǥ���Ѵ�.
							if(CharacterAttribute->Level < Level)
							{
								char Text[100];
								sprintf(Text,GlobalText[350],Level);
								g_pChatListBox->AddText("", Text, SEASON3B::TYPE_ERROR_MESSAGE);
							}
						}
                        //  ��ī�罺 ���ϸ� ������ �̵��Ҽ� �����ϴ�.
                        else if ( ( 62<=i && i<=65) && ( CharacterMachine->Equipment[EQUIPMENT_HELPER].Type==ITEM_HELPER+2) )
                        {
							g_pChatListBox->AddText("", GlobalText[569], SEASON3B::TYPE_ERROR_MESSAGE);
                        }
						/*
						#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
						else if(i>=45 && i<=49 && PartyNumber==0)
						{
						CreateWhisper("",GlobalText[262],2);
						}
						#endif
						*/
						else if(CharacterAttribute->Level < Level)
						{
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
							g_bReponsedMoveMapFromServer = TRUE;		// RenderLock
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
							LoadingWorld = 50;
							char Text[100];
							sprintf(Text,GlobalText[350],Level);
							g_pChatListBox->AddText("", Text, SEASON3B::TYPE_ERROR_MESSAGE);							
							//							return;
						}
						else
						{
							bool bResult;
							if((LoadingWorld) <= 30)
							{
								SendRequestMagicTeleport(&bResult,i, 0, 0);
							}
							
							if ( !bResult)
							{
								g_bWhileMovingZone = FALSE;
							}
							else
							{
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
								g_bReponsedMoveMapFromServer = FALSE;	// ����Ʈ�� �̵��� ���
								LoadingWorld = 200;
#else // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
								LoadingWorld = 9999999;
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
								
								// ���������� �̵��� ������ �ٲ�� �����Ƿ�..
								if( gt->Map == WD_30BATTLECASTLE || gt->Map == WD_31HUNTING_GROUND )
								{
									//  ���ӳ����� ������ ������ ����.
									SaveOptions();
									SaveMacro("Data\\Macro.txt");
								}
                                //  �ʱ�ȭ.
                                SelectedItem      = -1;
                                SelectedNpc       = -1;
                                SelectedCharacter = -1;
                                SelectedOperate   = -1;
                                Attacking         = -1;
								
								if((gs->Map == WD_0LORENCIA && gt->Map == WD_30BATTLECASTLE) || (gs->Map == WD_30BATTLECASTLE && gt->Map == WD_0LORENCIA))
								{
									g_dwLatestZoneMoving = GetTickCount();
									g_bWhileMovingZone = FALSE;
								}
								else
								{
									g_bWhileMovingZone = TRUE;
								}
								
								StandTime = 0;
							}
						}						
					}
				}
			}
		}
	}
}

LONG FAR PASCAL WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void MoveEffect( OBJECT *o, int iIndex);

///////////////////////////////////////////////////////////////////////////////
// ���콺 ���� ��ư Ŭ���� �̵��ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void MoveHero()
{
	CHARACTER *c = Hero;
	OBJECT *o = &c->Object;
	
	// 3�� ���� �������̸� ����
	if(o->CurrentAction == PLAYER_CHANGE_UP)
	{
		return;
	}
	
	// ũ���̿����� ĭ����3�� �������̸� �÷��̾� ���߰� �����ϰ� ����
	if(g_Direction.IsDirection())
	{
		SetPlayerStop(c);
		return;
	}
	
	// ������ �����߰�, ũ���̿��� ����� �������̸� ����
	if(SelectedCharacter != -1 && g_isCharacterBuff((&Hero->Object), eBuff_CrywolfHeroContracted))
	{
		return;
	}
	
	// ĳ���Ͱ� �׾��ų� ���Ͻ�ų�̳� ������ų�� �ɷ����� ����
	if(c->Dead > 0
		|| g_isCharacterBuff(o, eDeBuff_Stun)
		|| g_isCharacterBuff(o, eDeBuff_Sleep) ) 
	{
		return;
	}
	
#ifdef LJH_FIX_HERO_MOVES_EVEN_NOT_PRESENT	
	// ĳ���Ͱ� ȭ�鿡�� �������� ���� ��� (�׷����� ���� ��) �������� ���´�.
	if (c->Object.Live == 0)
		return;
#endif	//LJH_FIX_HERO_MOVES_EVEN_NOT_PRESENT	

	// ���� �ε����̸� ����
	if(LoadingWorld > 0) 
	{
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		// �̺κ� ����ڵ� ����..
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01

		LoadingWorld--;
#ifdef PBG_FIX_LODING_ACTION
		// �ʼ���LoadingWorld == 9999998 / ���̵�LoadingWorld == 29�� ����ʱ�ȭ�� �ѹ��� ȣ��
		if(LoadingWorld == 9999998 || LoadingWorld == 29)
#endif //PBG_FIX_LODING_ACTION
#ifdef LDK_FIX_MOTION_INTI_AT_THE_LOADINGWORLD
		// wops 34113 - ����ε��� ��� �ʱ�ȭ(09.04.14)
		SetPlayerStop(c);
#endif //LDK_FIX_MOTION_INTI_AT_THE_LOADINGWORLD
	}
	if(LoadingWorld > 30) 
	{
		return;
	}
	
	// ģ���߰�â�� �����ְ� ���콺������ ��ư�� Ŭ���ϸ� ���õ� ĳ���� ID�� ģ���߰�â�� �ڵ� �Էµǰ� ��
	if (g_pWindowMgr->GetAddFriendWindow() > 0)
	{
		if(MouseRButtonPush)
		{
#ifdef ASG_FIX_GENS_STRIFE_FRIEND_NAME_BLOCK
			if (!::IsStrifeMap(World))	// ���������� �ƴѰ�?
			{
#endif	// ASG_FIX_GENS_STRIFE_FRIEND_NAME_BLOCK
				CUITextInputWindow * pWindow = (CUITextInputWindow *)g_pWindowMgr->GetWindow(g_pWindowMgr->GetAddFriendWindow());
				if (pWindow != NULL)
				{
					pWindow->SetText(CharactersClient[SelectedCharacter].ID);
				}
#ifdef ASG_FIX_GENS_STRIFE_FRIEND_NAME_BLOCK
			}
#endif	// ASG_FIX_GENS_STRIFE_FRIEND_NAME_BLOCK
		}
	}
	
	// �ڱ��ڽ��� X, Y ��ġ�� ����
	int HeroX = GetScreenWidth() / 2;
	int HeroY = 180;

	int Angle;
	bool bLookAtMouse = true;        //  ! ���쿡 ���� ĳ���� ȸ�� ����.
	bool NoAutoAttacking = false;    //  ! �ڵ� ����.
	
	//  ! ���콺 ���� ĳ������ ȸ�� ������ �����Ѵ�.
	if( g_isCharacterBuff(o, eDeBuff_Stun)
		|| g_isCharacterBuff(o, eDeBuff_Sleep)
#ifdef WORLDCUP_ADD
		|| o->CurrentAction == PLAYER_POINT_DANCE
#endif //WORLDCUP_ADD
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		|| o->CurrentAction == PLAYER_SKILL_GIANTSWING
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
			)
	{
		Angle = (int)Hero->Object.Angle[2];
		bLookAtMouse = false;
	}
	else
	{
		Angle = (int)(Hero->Object.Angle[2]+CreateAngle((float)HeroX,(float)HeroY,(float)MouseX,(float)MouseY)) + 360 - 45;
		Angle %= 360;
		if(Angle < 120) Angle = 120;
		if(Angle > 240) Angle = 240;
		Angle += 180;
		Angle %= 360;
	}
		
	Hero->Object.HeadTargetAngle[2] = 0.f;
	
	//  ��� ��ų2 ������ ���콺 ��ġ�� �ٶ��� �ʴ´�.
	if ( ( 
		g_pOption->IsAutoAttack()
		&& Attacking!=-1 
		&& World!=WD_6STADIUM 
		&& InChaosCastle()==false ) 
		|| o->CurrentAction == PLAYER_ATTACK_SKILL_FURY_STRIKE 
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		|| o->CurrentAction == PLAYER_SKILL_GIANTSWING
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		)
	{
		bLookAtMouse = false;
	}
	if ( bLookAtMouse )
	{
		int mousePosY = MouseY;
		//ĳ���� �Ӹ� ȸ��
		if( mousePosY > 480 ) 
		{
			mousePosY = 480;
		}
		Hero->Object.HeadTargetAngle[0] = (float)Angle;
		Hero->Object.HeadTargetAngle[1] = (HeroY-mousePosY)*0.05f;
		
		NoAutoAttacking = true;
	}
	else
	{
		Hero->Object.HeadTargetAngle[0] = 0;
		Hero->Object.HeadTargetAngle[1] = 0;
	}
		
	if(c->Movement)
	{
		if ( g_isCharacterBuff(o, eDeBuff_Harden) 
			|| g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint))
		{
			SetPlayerStop(c);
		}
		else
		{
			SetPlayerWalk(c);
			if(MovePath(c))
			{
				c->Movement = false;
				SetPlayerStop(c);
				HeroAngle = (int)c->Object.Angle[2];
				StandTime = 0;
				
#ifdef YDG_FIX_LEAN_AGAINST_WALL_WITHOUT_ARROWS
				if (c->MovementType == MOVEMENT_OPERATE)
					Action(c,o,false);
				else
#endif	// YDG_FIX_LEAN_AGAINST_WALL_WITHOUT_ARROWS
				if(!CheckArrow() && GetBaseClass(Hero->Class) == CLASS_ELF )
					SetPlayerStop(Hero);
				else
					Action(c,o,false);
			}
			else
			{
				// ũ���� ���� MVP�� ���� ���� ���¿��� �����̸� ��� �ȵ� ���·� ���� ��
				g_CharacterUnRegisterBuff( (&Hero->Object), eBuff_CrywolfHeroContracted );
				MoveCharacterPosition(c);
			}
		}
	}
	else
	{
		StandTime++;

		if(StandTime >= 40 && !MouseOnWindow && !Hero->Dead &&
			o->CurrentAction!=PLAYER_POSE1 && o->CurrentAction!=PLAYER_POSE_FEMALE1 &&
			o->CurrentAction!=PLAYER_SIT1  && o->CurrentAction!=PLAYER_SIT_FEMALE1 && NoAutoAttacking &&
			o->CurrentAction!=PLAYER_ATTACK_TELEPORT &&
			o->CurrentAction!=PLAYER_ATTACK_RIDE_TELEPORT &&
			o->CurrentAction != PLAYER_FENRIR_ATTACK_DARKLORD_TELEPORT &&
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			o->CurrentAction != PLAYER_SKILL_ATT_UP_OURFORCES &&
			o->CurrentAction != PLAYER_SKILL_HP_UP_OURFORCES &&
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
			Hero->AttackTime == 0)
		{
			StandTime = 0;
			HeroAngle = -(int)(CreateAngle((float)MouseX,(float)MouseY,(float)HeroX,(float)HeroY)) + 360 + 45;
			HeroAngle %= 360;
			BYTE Angle1 = ((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8);
			BYTE Angle2 = ((BYTE)(((float)HeroAngle+22.5f)/360.f*8.f+1.f)%8);
			if(Angle1 != Angle2)
			{
				if ( o->CurrentAction!=PLAYER_ATTACK_SKILL_SWORD2 )
				{
					Hero->Object.Angle[2] = (float)HeroAngle;
				}
				SendRequestAction(AT_STAND1,((BYTE)((HeroAngle+22.5f)/360.f*8.f+1.f)%8));
			}
		}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	UseSkillRagePosition(c);
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}
		
	// �� �̵����� üũ
	CheckGate();
		
#ifdef USE_SELFCHECKCODE
		SendCrcOfFunction( 1, 12, WndProc, 0xBB7E);
#endif
		
		if(!MouseOnWindow && false == g_pNewUISystem->CheckMouseUse())
		{
			bool Success = false;
			if(MouseUpdateTime >= MouseUpdateTimeMax)
			{
				if(!EnableFastInput)
				{
#ifdef FOR_HACKING
					//  �ڵ� ���󰡱�.
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
					if( (SEASON3B::IsRepeat(VK_CONTROL) == TRUE) && (SEASON3B::IsRepeat(VK_MENU) == TRUE) )
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
					if( HIBYTE(GetAsyncKeyState(VK_CONTROL)) && HIBYTE(GetAsyncKeyState(VK_MENU)) )//&& PartyNumber>0 )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
					{
						if ( FindText( Hero->ID, "webzen" ) )
						{
							if(SelectedCharacter!=-1 && MouseLButtonPush )
							{
								g_iFollowCharacter = SelectedCharacter;
								MouseLButtonPush = false;
								Success = false;
							}
						}
					}
					else
#endif
					{
						if(MouseLButtonPush)
						{
							MouseLButtonPush = false;
							Success = true;
						}
						if(MouseLButton)
						{
							Success = true;
						}
						
						//  �ڵ�����.   ( ��Ʋ��Ŀ������ �ڵ� ���� �ȵ� )
						if( ( 
							g_pOption->IsAutoAttack()
							&& World!=WD_6STADIUM 
							&& InChaosCastle()==false ) 
							&& ( Attacking==1 && SelectedCharacter!=-1 ) )
						{
							Success = true;
						}
					}
					
					//  ���� ������ �Ǿ�����.
					if( Success 
						&& !g_isCharacterBuff(o, eDeBuff_Stun) 
						&& !g_isCharacterBuff(o, eDeBuff_Sleep) )
						{
							g_iFollowCharacter = -1;
							
							LButtonPressTime = ((WorldTime - LButtonPopTime)/CLOCKS_PER_SEC);
							
							if ( LButtonPressTime>=AutoMouseLimitTime )
							{
								MouseLButtonPush = false;
								MouseLButton = false;
								Success = FALSE;
							}
						}
						else
						{
							LButtonPopTime = WorldTime;
							LButtonPressTime = 0.f;
						}
				}
			}
			if( g_iFollowCharacter!=-1 )
			{
				//if ( FindText( Hero->ID, "webzen" ) )
				{
					CHARACTER* followCharacter = &CharactersClient[g_iFollowCharacter];
					if( followCharacter->Object.Live==0 )
					{
						g_iFollowCharacter = -1;
					}
					else
					{
						//
						c->MovementType = MOVEMENT_MOVE;
						ActionTarget = g_iFollowCharacter;
						TargetX = (int)(followCharacter->Object.Position[0]/TERRAIN_SCALE);
						TargetY = (int)(followCharacter->Object.Position[1]/TERRAIN_SCALE);
						if(PathFinding2(( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path))
							SendMove(c,o);
					}
				}
			}
			else if ( Success && 
				( ( o->CurrentAction!=PLAYER_SHOCK && ( o->Teleport!=TELEPORT_BEGIN && o->Teleport!=TELEPORT && o->Alpha>=0.7f ) &&
				( o->CurrentAction<PLAYER_ATTACK_FIST || o->CurrentAction>PLAYER_RIDE_SKILL )
#ifdef YDG_FIX_BLOCK_SKILL_MOVE
				&& ( o->CurrentAction<PLAYER_SKILL_SLEEP || o->CurrentAction>PLAYER_SKILL_LIGHTNING_SHOCK )
				&& o->CurrentAction!=PLAYER_RECOVER_SKILL
#endif	// YDG_FIX_BLOCK_SKILL_MOVE
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
				&& (o->CurrentAction<PLAYER_SKILL_THRUST || 
#ifdef PBG_FIX_NEWCHAR_MONK_UNIANI
				o->CurrentAction>PLAYER_RAGE_UNI_ATTACK_ONE_RIGHT
#else //PBG_FIX_NEWCHAR_MONK_UNIANI
				o->CurrentAction>PLAYER_SKILL_HP_UP_OURFORCES
#endif //PBG_FIX_NEWCHAR_MONK_UNIANI
				)
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
				)
				||( o->CurrentAction>=PLAYER_STOP_TWO_HAND_SWORD_TWO && o->CurrentAction<=PLAYER_RUN_TWO_HAND_SWORD_TWO )
				||( o->CurrentAction>=PLAYER_DARKLORD_STAND && o->CurrentAction<=PLAYER_RUN_RIDE_HORSE )
				|| (o->CurrentAction >= PLAYER_FENRIR_RUN && o->CurrentAction <= PLAYER_FENRIR_WALK_ONE_LEFT)
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
				|| (o->CurrentAction >= PLAYER_RAGE_FENRIR_WALK && o->CurrentAction <= PLAYER_RAGE_FENRIR_STAND_ONE_LEFT)
#endif //PBG_ADD_NEWCHAR_MONK_ANI
				) )
			{
				//������ ���Ⱑ ������ �޼չ��Ⱑ ���������� ��
				int RightType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
				int LeftType = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
				
				SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
				// �κ��丮���� �� ���ΰ�?
				if ( !pPickedItem && RightType==-1 &&
					((LeftType>=ITEM_SWORD && LeftType<ITEM_MACE+MAX_ITEM_INDEX)
					|| (LeftType>=ITEM_STAFF && LeftType<ITEM_STAFF+MAX_ITEM_INDEX
					&& !(LeftType >= ITEM_STAFF+21 && LeftType <= ITEM_STAFF+29)	// ��ȯ���� ���� �̵����� �ʴ´�.
					)))	
					{
#ifdef PSW_BUGFIX_LEFTWEAPON_MOVE
						if( g_pMyInventory->IsEquipable(EQUIPMENT_WEAPON_LEFT, &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT]) )
#endif //PSW_BUGFIX_LEFTWEAPON_MOVE
						{
							memcpy(&PickItem,&CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT],sizeof(ITEM));
							CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type  = -1;
							CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Level = 0;
							SetCharacterClass(Hero);
							SrcInventory = Inventory;
							SrcInventoryIndex = EQUIPMENT_WEAPON_LEFT;
							DstInventoryIndex = EQUIPMENT_WEAPON_RIGHT;
							SendRequestEquipmentItem(0,SrcInventoryIndex,0,DstInventoryIndex);
						}
					}
					MouseUpdateTime = 0;
					Success = false;
#ifdef ENABLE_EDIT
					Success = CheckAttack();
#else
					if(!c->SafeZone)//||EnableEdit)
					{
						Success = CheckAttack();
					}
#endif //ENABLE_EDIT
					if(Success)
					{
						//  ������ ���.
						if ( c->Movement && c->MovementType==MOVEMENT_MOVE && GetBaseClass(c->Class)==CLASS_ELF )
						{
#ifdef ADD_SOCKET_ITEM
							
							//  ������ Ȱ, ���� �����ϰ��.
							if( GetEquipedBowType(CharacterMachine->Equipment) != BOWTYPE_NONE )
							{
								SendPosition( (c->PositionX), (c->PositionY) );
							}
							
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
							int Right = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
							int Left = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
							
							//  ������ Ȱ, ���� �����ϰ��.
							if((Right>=ITEM_BOW+8 && Right<ITEM_BOW+15) || (Right>=ITEM_BOW+16 && Right<ITEM_BOW+MAX_ITEM_INDEX) || 
								(Left>=ITEM_BOW && Left<ITEM_BOW+7 || Left==ITEM_BOW+17 ) )
							{
								SendPosition (( c->PositionX),( c->PositionY));
							}
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
						}
						
						//  ���, ����, ������, ���˻�. �⺻ ���ݸ� ����.
						if ( SelectedCharacter >= -1 )
						{
							//  �ڵ� ���� ����.
							Attacking = 1;
							
							c->MovementType = MOVEMENT_ATTACK;
							ActionTarget = SelectedCharacter;
							TargetX = (int)(CharactersClient[ActionTarget].Object.Position[0]/TERRAIN_SCALE);
							TargetY = (int)(CharactersClient[ActionTarget].Object.Position[1]/TERRAIN_SCALE);

							if(CheckWall(( c->PositionX),( c->PositionY),TargetX,TargetY))
							{
								if(!PathFinding2(( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path))
								{
									if(CheckArrow() == false) 
									{
										return;
									}
									Action(c,o,true);
								}
								else
								{
#ifdef ADD_SOCKET_ITEM
									
									// Ȱ�̳� ������ �����ϰ� ������
									if( (GetEquipedBowType() != BOWTYPE_NONE) || (c->MonsterIndex == 9) )
									{
										if(CheckArrow() == false)
										{
											return;
										}
										Action(c,o,true);
									}
									else
									{
										SendMove(c,o);
									}
									
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
									int Right = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
									int Left = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
									if ( ( Right>=ITEM_BOW+8 && Right<ITEM_BOW+15 ) || ( Right>=ITEM_BOW+16 && Right<ITEM_BOW+MAX_ITEM_INDEX ) || 
										( Left>=ITEM_BOW && Left<ITEM_BOW+7 || Left==ITEM_BOW+17 || Left==ITEM_BOW+20
										|| Left == ITEM_BOW+21 || Left == ITEM_BOW+22 ) || c->MonsterIndex==9 )
										
									{
										if(CheckArrow() == false)
										{
											return;
										}
										Action(c,o,true);
									}
									else
										SendMove(c,o);
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
								}
							}
						}
					}
					else if ( SelectedOperate != -1 && ( c->SafeZone || ( c->Helper.Type<MODEL_HELPER+2 || c->Helper.Type>MODEL_HELPER+4 
						|| c->Helper.Type != MODEL_HELPER+37
						) ) )
					{
						TargetX = (int)(Operates[SelectedOperate].Owner->Position[0]/TERRAIN_SCALE);
						TargetY = (int)(Operates[SelectedOperate].Owner->Position[1]/TERRAIN_SCALE);
						int wall = TerrainWall[TERRAIN_INDEX(TargetX,TargetY)];
						
						if ( wall==TW_HEIGHT || wall<TW_CHARACTER )
							if(!c->Movement)
							{
								c->MovementType = MOVEMENT_OPERATE;
								TargetType = Operates[SelectedOperate].Owner->Type;
								TargetAngle = Operates[SelectedOperate].Owner->Angle[2];
								if(PathFinding2(( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path))
									SendMove(c,o);
								else
									Action(c,o,true);
							}
					}
					else if(SelectedNpc!=-1 
						&& !g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP)
						&& !g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE)
						)
					{
						if(g_isCharacterBuff(o, eBuff_CrywolfNPCHide)==false)
							c->MovementType = MOVEMENT_TALK;
						
						ActionTarget = SelectedNpc;
						TargetX = (int)(CharactersClient[ActionTarget].Object.Position[0]/TERRAIN_SCALE);
						TargetY = (int)(CharactersClient[ActionTarget].Object.Position[1]/TERRAIN_SCALE);
						TargetNpc = ActionTarget;
						TargetType = CharactersClient[ActionTarget].Object.Type;
						TargetAngle = CharactersClient[ActionTarget].Object.Angle[2];
						// ĭ���� ���� NPC �ָ����� Ŭ���ϸ� UIâ�� ������ ����
						if(TargetType == MODEL_KANTURU2ND_ENTER_NPC)
						{
							vec3_t vHero, vTarget, vSubstract;
							VectorCopy(o->Position, vHero);
							vHero[2] = 0.f;
							VectorCopy(CharactersClient[ActionTarget].Object.Position, vTarget);
							vTarget[2] = 0.f;
							VectorSubtract(vHero, vTarget, vSubstract);
							float fLength = VectorLength(vSubstract);
							if(fLength <= 550.f)
							{
								Action(c, o, true);
							}
							else
							{
								if(PathFinding2((c->PositionX), (c->PositionY), TargetX, TargetY, &c->Path))
									SendMove(c, o);
								else
									Action(c, o, true);
							}
						}
						else
						{
							if(PathFinding2(( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path))
								SendMove(c,o);
							else
								Action(c,o,true);
						}
					}
					else if(SelectedItem!=-1)
					{
						c->MovementType = MOVEMENT_GET;
						ItemKey = SelectedItem;
						TargetX = (int)(Items[SelectedItem].Object.Position[0]/TERRAIN_SCALE);
						TargetY = (int)(Items[SelectedItem].Object.Position[1]/TERRAIN_SCALE);
						if(PathFinding2(( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path))
							SendMove(c,o);
						else
						{
							Action(c,o,true);
							c->MovementType = MOVEMENT_MOVE;	// �� ���� 2�� �߻� ���ϵ��� ó��
						}
					}
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
					else if(SEASON3B::IsPress(VK_SHIFT) == FALSE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
					else if(HIBYTE(GetAsyncKeyState(VK_SHIFT)) != 128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
					{
						RenderTerrain ( true );
						bool Success = RenderTerrainTile(SelectXF,SelectYF,(int)SelectXF,(int)SelectYF,1.f,1,true);
#ifdef LDK_FIX_CHARACTER_UNLIVE_MOUSE_LOCK
						if(Success && c->Object.Live)
#else //LDK_FIX_CHARACTER_UNLIVE_MOUSE_LOCK
						if(Success)
#endif //LDK_FIX_CHARACTER_UNLIVE_MOUSE_LOCK
						{
							TargetX = (BYTE)(CollisionPosition[0]/TERRAIN_SCALE);
							TargetY = (BYTE)(CollisionPosition[1]/TERRAIN_SCALE);
							int Wall;
							//if(CharacterMachine->Equipment[EQUIPMENT_WING].Type!=-1)
							//	Wall = TW_NOMOVE;
							//else
							Wall = TW_NOGROUND;
							WORD CurrAtt = TerrainWall[TargetY*256+TargetX];
							if ( CurrAtt>=Wall && (CurrAtt&TW_ACTION)!=TW_ACTION
								&& (CurrAtt&TW_HEIGHT)!=TW_HEIGHT
								)
								DontMove = true;
							else
								DontMove = false;
							int xPos = ( int)( 0.01f * o->Position[0] );
							int yPos = ( int)( 0.01f * o->Position[1] );

							if ( !c->Movement || ( abs( ( c->PositionX) - xPos) < 2 && abs( ( c->PositionY) - yPos) < 2))
							{	
								// ���� ��ġ�� ���̴� ��ġ�� ũ�� ���̳��� ���� ���� �̵��ϰ� �Ѵ�.
								if ( ( ( c->PositionX)!=TargetX || ( c->PositionY)!=TargetY || !c->Movement) &&
									PathFinding2( ( c->PositionX),( c->PositionY),TargetX,TargetY,&c->Path ) )
								{
									c->MovementType = MOVEMENT_MOVE;
									SendMove ( c, o );
									// �̵� �� ��ġ ���콺 Ŭ���� ����
									OBJECT* pHeroObj = &Hero->Object;
									vec3_t vLight, vPos;
									Vector( 1.f, 1.f, 0.f, vLight );
									VectorCopy( CollisionPosition, vPos );
									DeleteEffect( MODEL_MOVE_TARGETPOSITION_EFFECT );		// ���� ����Ʈ ����. (���콺 Ŭ���Ѱ� ���� ��� ����Ʈ �Ѹ��� �Ϸ��� �ּ�ó��)

									// ������ Ÿ�� �ε��� ���ؼ� ����Ʈ�� �Ѹ��� �ʴ´�.
									// ( �׷��� ����Ʈ�� ��� �ɸ��ʹ� �̵��� �ϱ⶧���� ���� )
#ifdef KJH_FIX_MOVE_HERO_MOUSE_CLICK_EFFECT
									int iTerrainIndex = TERRAIN_INDEX( (int)SelectXF, (int)SelectYF );
									if( (TerrainWall[iTerrainIndex]&TW_NOMOVE) != TW_NOMOVE )
									{
										CreateEffect( MODEL_MOVE_TARGETPOSITION_EFFECT, vPos, pHeroObj->Angle, vLight, 0, pHeroObj, -1, 0, 0, 0, 0.6f);
									}
#else // KJH_FIX_MOVE_HERO_MOUSE_CLICK_EFFECT
									// 							int iTerrainIndex = TERRAIN_INDEX( (int)SelectXF, (int)SelectYF );
									// 							if( (TerrainWall[iTerrainIndex]&TW_NOMOVE) != TW_NOMOVE )
									// 							{
									CreateEffect( MODEL_MOVE_TARGETPOSITION_EFFECT, vPos, pHeroObj->Angle, vLight, 0, pHeroObj, -1, 0, 0, 0, 0.6f);														
									// 							}
#endif // KJH_FIX_MOVE_HERO_MOUSE_CLICK_EFFECT
								}
								else
								{
									MouseUpdateTime = MouseUpdateTimeMax;
									MouseUpdateTime = 0;
								}
							}
						}
					}
		}
		MouseUpdateTime++;
	}
	
#ifdef USE_SELFCHECKCODE
	SendCrcOfFunction( 10, 0, MoveEffect, 0x2545);
#endif
	
	Attack(Hero);
	int Index = ((int)Hero->Object.Position[1]/(int)TERRAIN_SCALE)*256 + ((int)Hero->Object.Position[0]/(int)TERRAIN_SCALE);
	if(Index < 0) Index = 0;
	else if(Index > 65535) Index = 65535;
	HeroTile = TerrainMappingLayer1[Index];
	
#ifdef USE_SELFCHECKCODE
	SendCrcOfFunction( 20, 5, UseSkillElf, 0x8AC3);
#endif
	
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// ���� ���� ������ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

int SelectItem()
{
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_ITEMS;i++)
#else // _VS2008PORTING
	int i;
	for(i=0;i<MAX_ITEMS;i++)
#endif // _VS2008PORTING
	{
		OBJECT *o = &Items[i].Object;
		if(o->Live && o->Visible)
		{
			o->LightEnable = true;
			Vector(0.2f,0.2f,0.2f,o->Light);
		}
	}
	//InitCollisionDetectLineToFace();
	float Luminosity = 1.5f;
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_ITEMS;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_ITEMS;i++)
#endif // _VS2008PORTING
	{
		OBJECT *o = &Items[i].Object;
		if(o->Live && o->Visible)
		{
			if(CollisionDetectLineToOBB(MousePosition,MouseTarget,o->OBB))
			{
				//BMD *b = &Models[o->Type];
				//b->Animation(o->AnimationFrame,o->Position,o->Angle,&o->OBB);
				//if(b->CollisionDetectLineToMesh(MousePosition,MouseTarget))
				{
					o->LightEnable = false;
					Vector(Luminosity,Luminosity,Luminosity,o->Light);
					return i;
				}
			}
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

int SelectCharacter(BYTE Kind)
{
	bool Main = true;
	if(SceneFlag == CHARACTER_SCENE)
		Main = false;
	
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
	int i;
	for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
	{
		CHARACTER *c = &CharactersClient[i];
		OBJECT *o = &c->Object;
		if ( (Kind&o->Kind)==o->Kind && o->Live && o->Visible && o->Alpha>0.f )
		{
			o->LightEnable = true;
			//�ɸ��� Į��
			switch ( c->Level )
			{
			case 0:Vector(0.2f,0.2f,0.2f,o->Light);break;   //����
			case 1:Vector(-0.4f,-0.4f,-0.4f,o->Light);break;//��ο�
			case 2:Vector(0.2f,-0.6f,-0.6f,o->Light);break; //������
			case 3:Vector(1.5f,1.5f,1.5f,o->Light);break;   //������
			case 4:Vector(0.3f,0.2f,-0.5f,o->Light);break;  //��ȯ
			}
            if ( c->PK>=PVP_MURDERER2 )
			{
#ifdef _PVP_MURDERER_HERO_ITEM
				if(c->MonsterIndex == 227)
				{
					Vector(-0.0f,-0.0f,-0.0f,o->Light);	// ī������
				}
				else
#endif	// _PVP_MURDERER_HERO_ITEM
				{
					Vector(-0.4f,-0.4f,-0.4f,o->Light);
				}
			}
		}
	}
	vec3_t Light;
	Vector(0.8f,0.8f,0.8f,Light);
	int iSelected = -1;
	float fNearestDist = 1000000000000.0f;
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
	{
		CHARACTER *c = &CharactersClient[i];
		OBJECT *o = &c->Object;
		
		if(o->Live && o->Visible && o->Alpha>0.f && c->Dead==0 && !g_isCharacterBuff(o, eBuff_CrywolfNPCHide))
			{
				//  ��Ƽ ������ ���� �����Ѵ�.
				if ( o->Kind==KIND_PLAYER )		//. bug fixed by soyaviper
				{
					for ( int j=0; j<PartyNumber; ++j )
					{
						PARTY_t *p = &Party[j];
						
						if ( p->index!=-2 ) continue;
						if ( p->index>-1 ) continue;
						
						int length = max(strlen(p->Name), max(1,strlen(c->ID)) );

						if ( !strncmp( p->Name, c->ID, length ) )
						{
							p->index = i;
							break;
						}
					}
				}
#ifndef HERO_SELECT
				if ( Main && c==Hero ) continue;
#endif// HERO_SELECT
				
				//  ������ ��� ���� ���¿����� ������ �Ǹ� �ȵȴ�.
				if ( c->m_bIsSelected==false ) 
				{
#ifdef REPAIR_BUG_MAY1
					if((c->MonsterIndex == 283) && (IsBattleCastleStart()==true) && (o->CurrentAction!=MONSTER01_DIE))//��ȣ����.
						c->m_bIsSelected = true;
					else
#endif
						continue;
				}
				
				if ( (Kind&o->Kind)==o->Kind )
				{
					// ������Ʈ ũ�� ������ Ÿ�� �Ǵ� ������ �ʹ� �Ʒ� �϶� ���� ó��  			
					if(o->Type == MODEL_SMELTING_NPC)
					{
						o->OBB.StartPos[2] += 300.0f;
					}
					else if(o->Type == MODEL_MONSTER01+118 || o->Type == MODEL_MONSTER01+119)
					{
						o->OBB.StartPos[2] += 200.0f;
					}		
					else if(o->Type == MODEL_KANTURU2ND_ENTER_NPC)
					{
						// NPC ��ŷ �Ǵ� ������ �� ũ�� ����� ���� ���� ó��
						o->OBB.StartPos[0] -= 100.f;
						o->OBB.StartPos[2] += 100.0f;
						o->OBB.XAxis[0] += 100.f;
						o->OBB.ZAxis[2] += 100.f;
					}
					
					if(CollisionDetectLineToOBB(MousePosition,MouseTarget,o->OBB))
					{
						// �Ÿ� ���
						vec3_t vSub;
						VectorSubtract( o->Position, CameraPosition, vSub);
						
						float fNewDist = DotProduct( vSub, vSub);
						// ��
						if ( fNewDist < fNearestDist)
						{
							// �� ���ȿ� �ִ� ��� �ۿ��� �� ���ɰ� �ϱ�
							BOOL bCanTalk = TRUE;
							if (World == WD_0LORENCIA || World == WD_2DEVIAS)
							{
								int Index = ((int)o->Position[1]/(int)TERRAIN_SCALE)*256 + ((int)o->Position[0]/(int)TERRAIN_SCALE);
								if ((World == WD_0LORENCIA && TerrainMappingLayer1[Index] == 4) ||
									(World == WD_2DEVIAS && TerrainMappingLayer1[Index] == 3))
								{
									if (TerrainMappingLayer1[Index] != HeroTile
#ifdef CSK_FIX_DEVIAS_REDCARPET
										&& (World == WD_2DEVIAS && HeroTile != 11)		// ����ƽ��̰� ����ī���� �ƴϸ�
#endif // CSK_FIX_DEVIAS_REDCARPET
										)
										bCanTalk = FALSE;
								}
							}
							if (bCanTalk == TRUE)
							{
								iSelected = i;
								fNearestDist = fNewDist;
							}
						}
					}
				}
			}
	}
	
    //  ��Ƽ ����.
    for ( int j=0; j<PartyNumber; ++j )
    {
		PARTY_t *p = &Party[j];
		
        if ( p->index>=0 ) continue;
		
        int length = max(strlen(p->Name), max(1,strlen(Hero->ID)) );
		
        if ( !strncmp( p->Name, Hero->ID, length ) )
        {
            p->index = -3;
        }
        else
        {
            p->index = -1;
        }
    }
	
	return iSelected;
}

///////////////////////////////////////////////////////////////////////////////
// ��� ������Ʈ �߿� �۵��ϴ� ������Ʈ �����ϴ� �Լ�(���� ���)
///////////////////////////////////////////////////////////////////////////////

int SelectOperate()
{
	for(int i=0;i<MAX_OPERATES;i++)
	{
		OPERATE *n = &Operates[i];
		OBJECT *o = n->Owner;
		if(n->Live && o->Visible && o->HiddenMesh==-1 )
		{
			float *Light = &o->Light[0];
			Vector(0.2f,0.2f,0.2f,Light);
		}
	}
	// �����ʿ��� �����߿��� �Ұ���
	if( IsBattleCastleStart() && World == WD_30BATTLECASTLE )
		return -1;
	
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_OPERATES;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_OPERATES;i++)
#endif // _VS2008PORTING
	{
		OPERATE *n = &Operates[i];
		OBJECT *o = n->Owner;
		if(n->Live && o->Visible )
		{
			float *Light = &o->Light[0];
			if(CollisionDetectLineToOBB(MousePosition,MouseTarget,o->OBB))
			{
				Vector(1.5f,1.5f,1.5f,Light);
				return i;
			}
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// ������� ��� �ɸ���, ������, ������Ʈ �߿� �ϳ��� ����Ʈ�ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void SelectObjects()
{
    BYTE CKind_1, CKind_2;
	//  �ڵ� ���� ������.   ( ��Ʋ ��Ŀ������ �ȵ� ).
    if (
		g_pOption->IsAutoAttack()
		&& World != WD_6STADIUM 
		&& InChaosCastle()==false )
    {
		if ( SelectedCharacter<0 || SelectedCharacter>=MAX_CHARACTERS_CLIENT+1 )
		{
            SelectedCharacter = -1;
            Attacking = -1;
		}
		else
		{
			CHARACTER* sc = &CharactersClient[SelectedCharacter];
			 
			// �̰�쿡�� ��� ������ ĳ���͸� �ʱ�ȭ�Ѵ�.
			// ������ ĳ���Ͱ� �״´�
			// ������ ĳ���Ͱ� ���Ͱ� �ƴϴ�
			if(sc->Dead > 0	|| sc->Object.Kind != KIND_MONSTER)
			{
				SelectedCharacter = -1;
				Attacking = -1;
			}
			
			//  �ڵ� ������.
			if ( Attacking!=-1 )
			{
				if ( MouseLButton || MouseLButtonPush || MouseRButton || MouseRButtonPush || Hero->Dead>0 )
				{
					SelectedCharacter = -1;
				}
			}
			else
			{
				SelectedCharacter = -1;
			}
		}
    }
    else
    {
        SelectedCharacter = -1;
        Attacking = -1;
    }
	
	SelectedItem      = -1;
	SelectedNpc       = -1;
	SelectedOperate   = -1;
	if(!MouseOnWindow
		&& false == g_pNewUISystem->CheckMouseUse()	/* NewUI�� ���콺 üũ */
		&& SEASON3B::CheckMouseIn(0, 0, GetScreenWidth(), 429)
		)
	{
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		if(SEASON3B::IsPress(VK_MENU) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		if(HIBYTE(GetAsyncKeyState(VK_MENU))==128)
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
		{
			if(SEASON3B::CNewUIInventoryCtrl::GetPickedItem() == NULL)
				SelectedItem = SelectItem();

			if(SelectedItem == -1)
			{
				SelectedNpc = SelectCharacter(KIND_NPC);
				if(SelectedNpc == -1)
				{
					SelectedCharacter = SelectCharacter(KIND_MONSTER|KIND_EDIT);
					if(SelectedCharacter == -1)
					{
						SelectedCharacter = SelectCharacter(KIND_PLAYER);
						if(SelectedCharacter == -1)
						{
							SelectedOperate = SelectOperate();
						}
					}
				}
			}
            else
            {
				g_pPartyManager->SearchPartyMember( );
            }
		}
		else
		{
            //  �⺻.
            CKind_1 = KIND_MONSTER | KIND_EDIT;
            CKind_2 = KIND_PLAYER;
			
            //  ������ ��쿡�� ��ų�� �˻��Ѵ�.
            if ( GetBaseClass(Hero->Class) == CLASS_ELF || GetBaseClass(Hero->Class)==CLASS_WIZARD )
            {
                //  ��ų ������ ���´�.
				int Skill = CharacterAttribute->Skill[Hero->CurrentSkill];
				
                //  ġ��/��������/���ݷ�����.
#ifdef KJH_FIX_WOPS_K33479_SELECT_CHARACTER_TO_HEAL
                if ( ((Skill>=AT_SKILL_HEALING) && (Skill<=AT_SKILL_ATTACK))
					|| ((AT_SKILL_HEAL_UP <= Skill) && (Skill <= AT_SKILL_HEAL_UP+4))
#ifdef PJH_SEASON4_MASTER_RANK4
					|| ((AT_SKILL_ATT_POWER_UP <= Skill) && (Skill <= AT_SKILL_ATT_POWER_UP+4))
					|| ((AT_SKILL_DEF_POWER_UP <= Skill) && (Skill <= AT_SKILL_DEF_POWER_UP+4))
#endif //PJH_SEASON4_MASTER_RANK4
					|| (Skill==AT_SKILL_TELEPORT_B)
					|| (Skill==AT_SKILL_WIZARDDEFENSE)
					|| ((AT_SKILL_SOUL_UP <= Skill) && (Skill <= AT_SKILL_SOUL_UP+4))
					)
#else // KJH_FIX_WOPS_K33479_SELECT_CHARACTER_TO_HEAL
                if ( (Skill>=AT_SKILL_HEALING
					|| (AT_SKILL_HEAL_UP <= Skill && Skill <= AT_SKILL_HEAL_UP+4)
					) && (Skill<=AT_SKILL_ATTACK
#ifdef PJH_SEASON4_MASTER_RANK4
					|| (AT_SKILL_ATT_POWER_UP <= Skill && Skill <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
					)
					|| Skill==AT_SKILL_TELEPORT_B
					&& (Skill==AT_SKILL_WIZARDDEFENSE
					|| (AT_SKILL_SOUL_UP <= Skill && Skill <= AT_SKILL_SOUL_UP+4)
					)
					)
#endif // KJH_FIX_WOPS_K33479_SELECT_CHARACTER_TO_HEAL
                {
                    CKind_1 = KIND_PLAYER;
                    CKind_2 = KIND_MONSTER | KIND_EDIT;
                }
            }
			// ��Ƽ����Ʈ���� ĳ���� ������ �ƴ°�?			
			if( g_pPartyListWindow && g_pPartyListWindow->GetSelectedCharacter() != -1)
			{
				g_pPartyManager->SearchPartyMember( );
			}
			else
			{
				//  �ڵ� ������ ����.
				if ( SelectedCharacter==-1 )
				{
					SelectedCharacter = SelectCharacter( CKind_1 );
				}
				if(SelectedCharacter == -1)
				{
					SelectedCharacter = SelectCharacter( CKind_2 );
					if(SelectedCharacter == -1)
					{
						SelectedNpc = SelectCharacter(KIND_NPC);
						if(SelectedNpc == -1)
						{
							if(SEASON3B::CNewUIInventoryCtrl::GetPickedItem() == NULL)
							{
								SelectedItem = SelectItem();
							}
							if(SelectedItem == -1)
							{
								SelectedOperate = SelectOperate();
							}
						}
					}
				}
				else if ( Attacking!=-1 )
				{
					g_pPartyManager->SearchPartyMember( );
				}
			}
			
		}
	}
    else
    {
		g_pPartyManager->SearchPartyMember( );
    }
	
    if(SelectedCharacter == -1)
    {
        Attacking = -1;
    }
	
	if( g_pPartyListWindow )
	{
		g_pPartyListWindow->SetListBGColor( );
	}
}

//////////////////////////////////////////////////////////////////////////
//  ��ų�� ��ų��Ű�� ã�� �Լ�.
//////////////////////////////////////////////////////////////////////////
int FindHotKey(int Skill)
{
    int SkillIndex = 0;
	
	for(int i=0;i<MAX_MAGIC;i++)
	{
		if(CharacterAttribute->Skill[i]==Skill )
		{
			SkillIndex = i;
			break;
		}
	}
	
    return SkillIndex;
}


///////////////////////////////////////////////////////////////////////////////
// ȭ����� ��� �������̽� �۵���Ű�� �Լ�
///////////////////////////////////////////////////////////////////////////////

extern int   CheckX;
extern int   CheckY;
extern int   CheckSkill;

void SendMacroChat(char *Text)
{
	if(!CheckCommand(Text, true))
	{
		if( ( Hero->Helper.Type<MODEL_HELPER+2 || Hero->Helper.Type>MODEL_HELPER+4 ) || Hero->SafeZone)	// Ÿ�� �ִ� ���¿����� �ൿ���ϴ� ���� �� �� ����.
			CheckChatText(Text);
		if(CheckAbuseFilter(Text))
			SendChat(GlobalText[570]);
		else
			SendChat(Text);
#ifdef _DEBUG
		MacroTime = 10;
#else
		MacroTime = 100;
#endif
	}
}

#ifdef DO_PROCESS_DEBUGCAMERA
void MoveInterface_DebugCamera()
{
	CameraAngle[0] = fmod( CameraAngle[0], 360.0f );
	CameraAngle[1] = fmod( CameraAngle[1], 360.0f );
	CameraAngle[2] = fmod( CameraAngle[2], 360.0f );

	if( true == MouseRButtonPush )
	{
		MouseRButtonClicking = true;
	}

	if( true == MouseRButtonPop )
	{
		MouseRButtonClicking = false;
	}

	if( true == MouseRButtonClicking )
	{
		g_pDebugCameraManager->RequestRotateEventPointXY();
	}

	if( SEASON3B::IsRepeat( VK_SHIFT ) )
	{
		if( SEASON3B::IsPress( VK_F10 ) )
		{
			g_pDebugCameraManager = g_pDebugCameraManager->GetThis_();
			g_pDebugCameraManager->SetActiveCameraMode_Sequencial( CameraPosition, CameraAngle );
		}
		
		if( SEASON3B::IsPress( VK_F9 ) )
		{
			vec3_t v3Angle_, v3Pos_;
			
			VectorCopy( CameraAngle, v3Angle_ );
			VectorCopy( CameraPosition, v3Pos_ );
			g_pDebugCameraManager = g_pDebugCameraManager->GetThis_();
			g_pDebugCameraManager->RequestCameraReset( &v3Angle_, &v3Pos_ );
		}

		float fMultipleVelocity = 1.0f, fMultipleAngularVeolocity = 1.0f;
		
		const float fMultiple_ = 0.2f;

		if( SEASON3B::IsRepeat( VK_CONTROL ) )
		{
			fMultipleVelocity = fMultipleVelocity * fMultiple_;
			fMultipleAngularVeolocity = fMultipleAngularVeolocity * fMultiple_;
		}

		g_pDebugCameraManager->RequestSetValueMultipleVelocity( fMultipleVelocity );
		g_pDebugCameraManager->RequestSetValueMultipleAngularVelocity( fMultipleAngularVeolocity );
		
		if( SEASON3B::IsRepeat( 'W' ) )
		{
			g_pDebugCameraManager->RequestMoveEventStraightFront();
		}
		if( SEASON3B::IsRepeat( 'S' ) )
		{
			g_pDebugCameraManager->RequestMoveEventStraightBack();
		}
		if( SEASON3B::IsRepeat( 'A' ) )
		{
			g_pDebugCameraManager->RequestMoveEventHorizontalLeft();	
		}
		if( SEASON3B::IsRepeat( 'D' ) )
		{
			g_pDebugCameraManager->RequestMoveEventHorizontalRight();
		}
	}
	
	if( MouseWheel > 0 )
	{
		g_pDebugCameraManager->RequestMoveEventStraightFront();
		MouseWheel = 0;
	}
	else if( MouseWheel < 0 )
	{
		g_pDebugCameraManager->RequestMoveEventStraightBack();
		MouseWheel = 0;
	}
	
};
#else // DO_PROCESS_DEBUGCAMERA
void MoveInterface_DebugCamera()
{
	return;
}
#endif // DO_PROCESS_DEBUGCAMERA

#ifdef DO_PROFILING

// Profiling Key Processing
void MoveInterface_ForProfiling()
{
	if( SEASON3B::IsPress(VK_F11) )
	{
		g_pProfiler = g_pProfiler->GetThis_();
		
		if( TRUE == g_pProfiler->IsProflingNow() )
		{
			g_pProfiler->RequestKillProfiling();
			g_pProfiler->RequestGenerateResult();
		}
		else
		{
			g_pProfiler->RequestLiveProfiling();
		}
	}
}
#else // DO_PROFILING
void MoveInterface_ForProfiling()
{
	return;
}
#endif // DO_PROFILING

#ifdef ANTIHACKING_ENABLE
extern BOOL g_bNewFrame;
#endif //ANTIHACKING_ENABLE

void MoveInterface()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_MOVE_INTERFACE, PROFILING_MOVE_INTERFACE );
#endif // DO_PROFILING
	if(g_Direction.IsDirection())
	{
#ifdef DO_PROFILING
		g_pProfiler->EndUnit( EPROFILING_MOVE_INTERFACE );
#endif // DO_PROFILING
		return;
	}
	
	//    ����, ������ �ÿ���.
	if ( battleCastle::IsBattleCastleStart() == true )
	{
		if(CharacterAttribute->SkillNumber > 0)
		{
			UseBattleMasterSkill();
		}
	}	

#ifdef ANTIHACKING_ENABLE
	// üũ �ڵ�
	if ( g_bNewFrame)
	{
		switch ( GetTickCount() % 20000)
		{
		case 3127:
			hanguo_check5();
			break;
		case 17321:
			hanguo_check1();
			break;
		case 7992:
			hanguo_check3();
			break;
		}
	}
#endif //ANTIHACKING_ENABLE
	
	int x,y,Width,Height;
	
#ifdef USE_SELFCHECKCODE
	SendCrcOfFunction( 16, 18, CastWarriorSkill, 0xC3C9);
#endif
	
	//��ũ�� ���
	if(MacroTime == 0)
	{
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		if(InChaosCastle() == FALSE)
		{
			//===================================================================
			// ALT Ű�� ���� �����̸�
			//===================================================================
			if(SEASON3B::IsRepeat(VK_MENU) == TRUE)
			{
				for(int i = 0; i < 9; i++)
				{
					//===================================================================
					// 1~9���� ���� �����̸�..
					//===================================================================
					if(SEASON3B::IsPress('1' + i) == TRUE)
					{
						SendMacroChat(MacroText[i]);
					}
				}
				//===================================================================
				// 0�� ������..
				//===================================================================
				if(SEASON3B::IsPress('0') == TRUE)
				{
					SendMacroChat(MacroText[9]);
				}
			}
		}
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
        if ( InChaosCastle()==false )
        {
			if(HIBYTE(GetAsyncKeyState(VK_MENU)))	// ALT Ű�� ������
			{
				for(int i=0;i<9;i++)
				{
					if(HIBYTE(GetAsyncKeyState('1'+i)))	// 1~9����
					{
						SendMacroChat(MacroText[i]);
					}
				}
				if(HIBYTE(GetAsyncKeyState('0'))) // 0�̸� 
				{
					SendMacroChat(MacroText[9]);
				}
			}
        }
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
	}
	
	//potion
	if(Hero->Dead == 0)
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			g_pMainFrame->UseHotKeyItemRButton();
		}
#else //LDK_ADD_SCALEFORM
		g_pMainFrame->UseHotKeyItemRButton();
#endif //LDK_ADD_SCALEFORM
	}
	
#ifdef USE_SELFCHECKCODE
	SendCrcOfFunction( 2, 14, WinMain, 0xE910);
#endif
	if( g_pUIManager->IsInputEnable() )
	{
			if (g_iChatInputType == 0)
			{
				//ä��â
				Width=190;Height=29;x=186;y=415;
				if(MouseX>=x && MouseX<x+Width && MouseY>=
					y && MouseY<y+Height)
				{
					if(MouseLButtonPush)
					{
						MouseLButtonPush = false;
						InputIndex = 0;
						MouseUpdateTime = 0;
						MouseUpdateTimeMax = 6;
						PlayBuffer(SOUND_CLICK01);
					}
				}
				Width=58;Height=29;x=186+190;y=415;
				if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height)
				{
					if(MouseLButtonPush)
					{
						MouseLButtonPush = false;
						InputIndex = 1;
						MouseUpdateTime = 0;
						MouseUpdateTimeMax = 6;
						PlayBuffer(SOUND_CLICK01);
					}
				}
			}
			Width=20;Height=29;x=186+190+58;y=415;
			if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height)
			{
				if(MouseLButtonPush)
				{
					MouseLButtonPush = false;
					if(WhisperEnable)
						WhisperEnable = false;
					else
						WhisperEnable = true;
					MouseUpdateTime = 0;
					MouseUpdateTimeMax = 6;
					PlayBuffer(SOUND_CLICK01);
				}
			}
	}
	
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_MOVE_INTERFACE );
#endif // DO_PROFILING
}


//////////////////////////////////////////////////////////////////////////
//  ��ų ����� ���� ������ �˻��Ѵ�.
//////////////////////////////////////////////////////////////////////////
bool IsCanBCSkill(int Type)
{
	// ������ų�� ������ �Ǵ�.
	if( Type==44 || Type==45 || Type==46 || Type==57 || Type==73 || Type==74 
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		|| Type == AT_SKILL_OCCUPY
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		)
	{
		// �������� �ƴϰų� ���������� �ƴϸ� ��Ȱ��ȭ
		if( !InBattleCastle() || !battleCastle::IsBattleCastleStart() )
		{
			return false;
		}
	}
	
	return true;
}

bool CheckSkillUseCondition ( OBJECT* o, int Type )
{
#ifdef LEM_FIX_USER_LOGOUT_SKILL_ENABLE
	if( g_bExit )		return false;
#endif	// LEM_FIX_USER_LOGOUT_SKILL_ENABLE [lem_2010.8.18]
	// ���� ��ų �˻�
	if( IsCanBCSkill(Type) == false )
	{
		return false;
	}
	
    BYTE SkillUseType = SkillAttribute[Type].SkillUseType;
	
	if ( SkillUseType == SKILL_USE_TYPE_BRAND && g_isCharacterBuff(o, eBuff_AddSkill) == false )
		{
			return false;
		}
		
		return true;
}

//////////////////////////////////////////////////////////////////////////
//  ��ų �������� ����.
//////////////////////////////////////////////////////////////////////////
extern char TextList[30][100];
extern int  TextListColor[30];
extern int  TextBold[30];

#ifdef CSK_LUCKY_SEAL
void GetTime( DWORD time, string& timeText, bool isSecond )
{
	if( isSecond )
	{
		DWORD day     = time/(1440*60);
		DWORD oClock  = (time-(day*(1440*60)))/3600;
		DWORD minutes = (time-((oClock*3600)+(day*(1440*60))))/60;
		DWORD second  = time%60;
		
		if( day != 0 )
		{
			timeText = ( format( "%1% %2% %3% %4% %5% %6% %7% %8%" ) 
				% day 
				% GlobalText[2298] 
				% oClock
				% GlobalText[2299]
				% minutes
				% GlobalText[2300] 
				% second
				% GlobalText[2301] ).str();
		}
		else if( day == 0 && oClock != 0 )
		{
			timeText = ( format( "%1% %2% %3% %4% %5% %6%" ) 
				% oClock
				% GlobalText[2299]
				% minutes
				% GlobalText[2300]
				% second
				% GlobalText[2301] ).str();
		}
		else if( day == 0 && oClock == 0 && minutes != 0 )
		{
			timeText = ( format( "%1% %2% %3% %4%" ) 
				% minutes
				% GlobalText[2300]
				% second
				% GlobalText[2301] ).str();
		}
		else if( day == 0 && oClock == 0 && minutes == 0 )
		{
		/*
		timeText = ( format( "%1% %2%" ) % second
								% GlobalText[2301] ).str();
			*/
			timeText = ( format( "%1%" ) % GlobalText[2308] ).str();			
		}
	}
	else
	{
		DWORD day     = time/1440;
		DWORD oClock  = (time-(day*1440))/60;
		DWORD minutes = time%60;
		
		if( day != 0 )
		{
			timeText = ( format( "%1% %2% %3% %4% %5% %6%" ) 
				% day 
				% GlobalText[2298] 
				% oClock
				% GlobalText[2299]
				% minutes
				% GlobalText[2300] ).str();
		}
		else if( day == 0 && oClock != 0 )
		{
			timeText = ( format( "%1% %2% %3% %4%" ) 
				% oClock
				% GlobalText[2299]
				% minutes
				% GlobalText[2300] ).str();
		}
		else if( day == 0 && oClock == 0 && minutes != 0 )
		{
			timeText = ( format( "%1% %2%" ) 
				% minutes
				% GlobalText[2300] ).str();
		}
	}
}
#endif //CSK_LUCKY_SEAL


///////////////////////////////////////////////////////////////////////////////
// ȭ��� ������ ��� �������̽��� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderBar(float x,float y,float Width,float Height,float Bar,bool Disabled,bool clipping)
{
    if(clipping)
    {
		if(x < 0) x = 0;
		if(y < 0) y = 0;
		if(x+Width+4  > 640   ) x = 640   -(Width +1+4);
		if(y+Height+4 > 480-47) y = 480-47-(Height+1+4);
    }
	
	EnableAlphaTest();
   	glColor4f(0.f,0.f,0.f,0.5f);
	RenderColor(x+1,y+1,Width+4,Height+4);
	
	EnableAlphaBlend();
	if ( Disabled)
		glColor3f(0.2f,0.0f,0.0f);
	else
		glColor3f(0.f,0.2f,0.2f);
	RenderColor(x,y,Width+4,Height+4);
	if ( Disabled)
		glColor3f(50.f/255.f,10/255.f,0.f);
	else
		glColor3f(0.f/255.f,50/255.f,50.f/255.f);
	RenderColor(x+2,y+2,Width,Height);
	if ( Disabled)
		glColor3f(200.f/255.f,50/255.f,0.f);
	else
		glColor3f(0.f/255.f,200/255.f,50.f/255.f);
	RenderColor(x+2,y+2,Bar,Height);
	
	DisableAlphaBlend();
}

void RenderSwichState()
{
	char Buff[300];
	
	if(Switch_Info == NULL)
		return;
	
	int ax = (Hero->PositionX);
	int ay = (Hero->PositionY);
	
	if( !(ax>=150 && ax<=200 && ay>=180&& ay<=230)  ) 
	{
		Delete_Switch();
		return;
	}
	
	
	for(int i = 0; i < 2; i++)
	{
		if(Switch_Info[i].m_bySwitchState > 0)
		{
			// 1981 "�հ�����ġ"
			sprintf(Buff,"%s%d / %s / %s",GlobalText[1981],i+1,Switch_Info[i].m_szGuildName,Switch_Info[i].m_szUserName);
					
					g_pRenderText->SetFont(g_hFont);
					g_pRenderText->SetTextColor(255, 255, 255, 255);
					g_pRenderText->SetBgColor(0);
					g_pRenderText->RenderText(0, 480-85+(i*15), Buff, 640, 0, RT3_SORT_CENTER);
		}
	}
}



void RenderInterface(bool Render)
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_RENDER_INTERFACE, PROFILING_RENDER_INTERFACE );
#endif // DO_PROFILING

	g_pRenderText->SetTextColor(255, 255, 255, 255);
	
	//ȭ�� ������ܿ� ���ϸ���,��ũ�ε�,��� ���� ������ �ؽ�Ʈ�� �����̴°��� ����.
	
    //  ���� ȭ�� �� �տ� ��Ÿ���� ȿ��.
    RenderOutSides();
	
    //  ��Ƽ���� HP.
    RenderPartyHP ();
	
	RenderSwichState();
    battleCastle::RenderBuildTimes ();
	
	g_pUIMapName->Render();		// rozy
    
//	M34CryWolf1st::Render_Mvp_Interface();
	M39Kanturu3rd::RenderKanturu3rdinterface();
//	M34CryWolf1st::Sub_Interface();
	
#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_RENDER_INTERFACE );
#endif // DO_PROFILING
}


///////////////////////////////////////////////////////////////////////////////
//  ���� ȭ�� �տ� ������ ȿ��. ( ����, ���. )
///////////////////////////////////////////////////////////////////////////////
void RenderOutSides()
{
	if(World == WD_8TARKAN)
	{
		EnableAlphaTest();
       	glColor4f(1.f,1.f,1.f,0.5f);
		EnableAlphaBlend();
       	glColor3f(0.3f,0.3f,0.25f);
		float WindX = (float)((int)WorldTime%100000)*0.0002f; 
		RenderBitmapUV(BITMAP_CHROME+2,0.f,0.f,640.f,480.f-45.f,WindX,0.f,0.3f,0.3f);
		float WindX2 = (float)((int)WorldTime%100000)*0.001f; 
		RenderBitmapUV(BITMAP_CHROME+3,0.f,0.f,640.f,480.f-45.f,WindX2,0.f,3.f,2.f);
	}
#ifdef ASG_ADD_MAP_KARUTAN
	else if (IsKarutanMap())
	{
		EnableAlphaTest();
		EnableAlphaBlend();
		glColor3f(0.3f,0.3f,0.25f);
		float fWindX = (float)((int)WorldTime%100000)*0.004f; 
		RenderBitmapUV(BITMAP_CHROME+3, 0.f, 0.f, 640.f, 480.f-45.f, fWindX, 0.f, 3.f, 2.f);
	}
#endif	// ASG_ADD_MAP_KARUTAN
    else if(WD_34CRYWOLF_1ST == World)
	{
		if(ashies == true)
		{
			M34CryWolf1st::RenderBaseSmoke ();
			ashies = false;
		}
	}
	else if (World == WD_56MAP_SWAMP_OF_QUIET)
	{
		SEASON3C::GMSwampOfQuiet::RenderBaseSmoke();
	}
#ifdef CSK_ADD_MAP_ICECITY
	else if(IsIceCity())
	{
		g_Raklion.RenderBaseSmoke();
	}
#endif // CSK_ADD_MAP_ICECITY
	else
    {
        battleCastle::RenderBaseSmoke ();
    }

#ifdef LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC
	// �Ȱ�, õ�� ó��
	TheMapProcess().RenderFrontSideVisual();
#endif //LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC

	glColor3f(1.f,1.f,1.f);
}

void MoveTournamentInterface()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_MOVE_TOURNAMENTINTERFACE, PROFILING_MOVE_TOURNAMENTINTERFACE );
#endif // DO_PROFILING
	//����� ����
	//Ŭ���ϸ� �ݴ´�.
	static unsigned int s_effectCount = 0;
	int Width = 70, Height = 20;
	int WindowX = (640-Width)/2;
	int WindowY = (480-Height)/2 + 50;
	if(MouseLButtonPush)
	{
		//������ ��ġ�� ���� �� ����.
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float wRight = WindowX + Width;
		float wBottom = WindowY + Height;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		if( WindowY <= MouseY && MouseY <= WindowY + Height &&
			WindowX <= MouseX && MouseX <= WindowX + Width)
		{	
			g_wtMatchResult.Clear();
			g_wtMatchTimeLeft.m_Time = 0;
		}
	}
	
	if(g_iGoalEffect)
	{
		for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
			MoveBattleSoccerEffect(&CharactersClient[i]);
		g_iGoalEffect = 0;
	}
#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_MOVE_TOURNAMENTINTERFACE );
#endif // DO_PROFILING
}

void MoveBattleSoccerEffect(CHARACTER* c)
{
	OBJECT* o = &c->Object;
	if(o->Live)
	{
		//�츮 �����鿡�� ����Ʈ ���
		if(g_iGoalEffect == 1)
		{
			if(c->GuildTeam == 1)
			{
				//�κ� ����Ʈ
				vec3_t Position, Angle;
				for(int i = 0; i < 36; ++i)
				{
					Angle[0] = -10.f;
					Angle[1] = 0.f;
					Angle[2] = 45.f;
					float x_bias = cosf(Q_PI / 180.f * 10.0f * i);
					float y_bias = sinf(Q_PI / 180.f * 10.0f * i);
					Position[0] = c->Object.Position[0] + x_bias*TERRAIN_SCALE;
					Position[1] = c->Object.Position[1] + y_bias*TERRAIN_SCALE;
					Position[2] = c->Object.Position[2];
					CreateJoint(BITMAP_FLARE,Position, Position, Angle, 22, &c->Object,35);
				}
			}
		}
		//��������� ����Ʈ ���
		else if(g_iGoalEffect == 2)
		{
			if(c->GuildTeam == 2)
			{
				//�κ� ����Ʈ
				vec3_t Position, Angle;
				for(int i = 0; i < 36; ++i)
				{
					Angle[0] = -10.f;
					Angle[1] = 0.f;
					Angle[2] = 45.f;
					float x_bias = cosf(Q_PI / 180.f * 10.0f * i);
					float y_bias = sinf(Q_PI / 180.f * 10.0f * i);
					Position[0] = c->Object.Position[0] + x_bias*TERRAIN_SCALE;
					Position[1] = c->Object.Position[1] + y_bias*TERRAIN_SCALE;
					Position[2] = c->Object.Position[2];
					CreateJoint(BITMAP_FLARE,Position, Position, Angle, 22, &c->Object,35);
				}
			}			
		}
	}
}

void RenderTournamentInterface()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_RENDER_TOURNAMENTINTERFACE, PROFILING_RENDER_TOURNAMENTINTERFACE );
#endif // DO_PROFILING
	int Width = 300, Height = 2*5+6*30;
	int WindowX = (640-Width)/2;
	int WindowY = 120+0;
	float x = 0.0f,y = 0.0f;
	char t_Str[20];
	strcpy(t_Str, "");
#ifndef _VS2008PORTING			// #ifndef
	int i;
#endif // _VS2008PORTING
	
	//�ð� ������
	if( g_wtMatchTimeLeft.m_Time)
	{
		int t_valueSec = g_wtMatchTimeLeft.m_Time % 60;
		int t_valueMin = g_wtMatchTimeLeft.m_Time / 60;
		if(t_valueMin <= 10)
		{		
			g_pRenderText->SetFont(g_hFontBig);
			g_pRenderText->SetTextColor(255, 10, 10, 255);
			g_pRenderText->SetBgColor(0);
			
			if(g_wtMatchTimeLeft.m_Type == 3)
			{
				g_pRenderText->SetTextColor(255, 255, 10, 255);
				sprintf(t_Str, GlobalText[1392], t_valueSec);
			}
			else
			{
				if(g_wtMatchTimeLeft.m_Time < 60)
				{
					g_pRenderText->SetTextColor(255, 255, 10, 255);
				}
				if(t_valueSec < 10)
				{
					sprintf(t_Str,GlobalText[1390],t_valueMin,t_valueSec);
				}
				else
				{
					sprintf(t_Str,GlobalText[1391],t_valueMin,t_valueSec);
				}
			}
			x += (float)GetScreenWidth()/2; y += 350;
			g_pRenderText->RenderText((int)x,(int)y, t_Str, 0 ,0, RT3_WRITE_CENTER); x++; y++;
			
			g_pRenderText->SetTextColor(0xffffffff);
			g_pRenderText->RenderText((int)x,(int)y, t_Str, 0 ,0, RT3_WRITE_CENTER);
			
			g_pRenderText->SetFont(g_hFont);
			g_pRenderText->SetTextColor(255, 255, 255, 255);
		}
	}
	
	//��� ������
	if(!strcmp(g_wtMatchResult.m_MatchTeamName1, ""))
	{
#ifdef DO_PROFILING
		g_pProfiler->EndUnit( EPROFILING_RENDER_TOURNAMENTINTERFACE );
#endif // DO_PROFILING
		return;
	}
	
	//��Ʈ�� ���÷���
    Width = 300;Height = 2*5+5*40;WindowX = (640-Width)/2;WindowY = 120+0;
	int yPos = WindowY;
	RenderBitmap(BITMAP_INTERFACE+22,(float)WindowX,(float)yPos,(float)Width,(float)5,0.f,0.f,Width/512.f,5.f/8.f);
	yPos += 5;
#ifdef _VS2008PORTING
	for(int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for(i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		RenderBitmap(BITMAP_INTERFACE+21, WindowX, (float)yPos, 
			Width, 40.f, 0.f, 0.0f, 213.f/256.f, 40.f/64.f);
		yPos+=40.f;
	}
	RenderBitmap(BITMAP_INTERFACE+22,(float)WindowX,(float)yPos,(float)Width,(float)5,0.f,0.f,Width/512.f,5.f/8.f);
	
	//���� ���÷���
	EnableAlphaBlend();
	glColor4f ( 1.f, 1.f, 1.f, 1.f );
	g_pRenderText->SetFont(g_hFontBig);
	g_pRenderText->SetTextColor(200, 240, 255, 255);
	sprintf(t_Str, GlobalText[1393]);
	g_pRenderText->RenderText( WindowX+Width/2-50, WindowY+20, t_Str);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	
	//���߰��� VS�� ��� �� ���̿� ��� �̸� �Ǵ� �������� �̸��� ���´�. 
	sprintf(t_Str, GlobalText[1394]);
	g_pRenderText->SetTextColor(255, 255, 10, 255);
	g_pRenderText->RenderText( WindowX+Width/2-13, WindowY+50, t_Str);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	
	//�̸� ���÷��� ����
	float t_temp = 0.0f; //���� ��ġ ����
	sprintf(t_Str, "%s", g_wtMatchResult.m_MatchTeamName1);
	t_temp = (MAX_ID_SIZE - strlen(t_Str)) * 5;
	g_pRenderText->RenderText( WindowX+10 + t_temp, WindowY+50, t_Str);
	sprintf(t_Str, "%s", g_wtMatchResult.m_MatchTeamName2);
	t_temp = (MAX_ID_SIZE - strlen(t_Str)) * 5;
	g_pRenderText->RenderText( WindowX+Width-120 + t_temp, WindowY+50, t_Str);
	
	//���ھ� ǥ��
	sprintf(t_Str, "(%d)", g_wtMatchResult.m_Score1);
	g_pRenderText->RenderText( WindowX+45, WindowY+75, t_Str);
	sprintf(t_Str, "(%d)", g_wtMatchResult.m_Score2);
	g_pRenderText->RenderText( WindowX+Width-85, WindowY+75, t_Str);
	
	//���� ǥ��
	if(g_wtMatchResult.m_Score1 == g_wtMatchResult.m_Score2)
	{
		g_pRenderText->SetFont(g_hFontBig);
		g_pRenderText->SetTextColor(255, 255, 10, 255);
		sprintf(t_Str, GlobalText[1395]);
		g_pRenderText->RenderText( WindowX+Width/2-35, WindowY+115, t_Str);
		g_pRenderText->SetFont(g_hFont);
		g_pRenderText->SetTextColor(255, 255, 255, 255);
	}
	else if(g_wtMatchResult.m_Score1 > g_wtMatchResult.m_Score2)
	{
		g_pRenderText->SetFont(g_hFontBig);
		g_pRenderText->SetTextColor(255, 255, 10, 10);
		sprintf(t_Str, GlobalText[1396]);
		g_pRenderText->RenderText( WindowX+47, WindowY+115, t_Str);
		g_pRenderText->SetTextColor(255, 10, 10, 255);
		sprintf(t_Str, GlobalText[1397]);
		g_pRenderText->RenderText( WindowX+Width-82, WindowY+115, t_Str);
		g_pRenderText->SetFont(g_hFont);
	}
	else
	{
		g_pRenderText->SetFont(g_hFontBig);
		g_pRenderText->SetTextColor(255, 255, 10, 10);
		sprintf(t_Str, GlobalText[1397]);
		g_pRenderText->RenderText( WindowX+47, WindowY+115, t_Str);
		g_pRenderText->SetTextColor(255, 10, 10, 255);
		sprintf(t_Str, GlobalText[1396]);
		g_pRenderText->RenderText( WindowX+Width-82, WindowY+115, t_Str);
		g_pRenderText->SetFont(g_hFont);
	}
	g_pRenderText->SetFont(g_hFont);
	
	// ��ư
	Width = 70;Height = 20;x = (640-Width)/2;y = (480-Height)/2 + 50;
	if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height)
	{
		RenderBitmap(BITMAP_INTERFACE+12,(float)x,(float)y,(float)Width,(float)Height,0.f,0.f,Width/128.f,Height/32.f);
	}
	else
	{
		RenderBitmap(BITMAP_INTERFACE+11,(float)x,(float)y,(float)Width,(float)Height,0.f,0.f,Width/128.f,Height/32.f);
	}
	
	glColor3f ( 1.f, 1.f, 1.f);
	DisableAlphaBlend();

#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_RENDER_TOURNAMENTINTERFACE );
#endif // DO_PROFILING
}


///////////////////////////////////////////////////////////////////////////////
//  ��Ƽ���� HP �� ȭ�鿡 �����ش�.
///////////////////////////////////////////////////////////////////////////////
void RenderPartyHP ()
{
    if ( PartyNumber<=0 ) return;
	
    float   Width = 38.f;
    char    Text[100];
	
    //  ����� �̸����� ã�´�.
    //  �������� index�� ã�´�.
    for ( int j=0; j<PartyNumber; ++j )
    {
		PARTY_t *p = &Party[j];
		
        if (p->index<=-1) continue;  //  ȭ�鿡 ������ �ʴ� ĳ����.
		
        CHARACTER*  c = &CharactersClient[p->index];
		OBJECT*     o = &c->Object;
		vec3_t      Position;
		int         ScreenX, ScreenY;
		
		Vector ( o->Position[0], o->Position[1], o->Position[2]+o->BoundingBoxMax[2]+100.f, Position );
		Projection ( Position, &ScreenX, &ScreenY );
        ScreenX -= (int)(Width/2);
		
        //  ���콺�� �˻縦 �Ѵ�.
		if((MouseX>=ScreenX && MouseX<ScreenX+Width && MouseY>=ScreenY-2 && MouseY<ScreenY+6))
		{
			sprintf ( Text,"HP : %d0%%", p->stepHP );
			g_pRenderText->SetTextColor(255, 230, 210, 255);
			g_pRenderText->RenderText(ScreenX, ScreenY-6, Text);
		}
        //  10�ܰ�� ǥ���Ѵ�. 
		EnableAlphaTest ();
   	    glColor4f ( 0.f, 0.f, 0.f, 0.5f );
		RenderColor ( (float)(ScreenX+1), (float)(ScreenY+1), Width+4.f, 5.f );
		
		EnableAlphaBlend ();
		glColor3f ( 0.2f, 0.0f, 0.0f );
		RenderColor ( (float)ScreenX, (float)ScreenY, Width+4.f, 5.f );
		
        glColor3f ( 50.f/255.f, 10/255.f, 0.f );
		RenderColor ( (float)(ScreenX+2), (float)(ScreenY+2), Width, 1.f );
		
        int stepHP = min ( 10, p->stepHP );
		
        glColor3f ( 250.f/255.f, 10/255.f, 0.f );
        for ( int k=0; k<stepHP; ++k )   //  HP�� ǥ���Ѵ�.
        {
			RenderColor ( (float)(ScreenX+2+(k*4)), (float)(ScreenY+2), 3.f, 2.f );
        }
		DisableAlphaBlend();
    }
	DisableAlphaBlend();
	glColor3f(1.f,1.f,1.f);
}

///////////////////////////////////////////////////////////////////////////////
// ��ǳ������ �ڵ� �����Ͽ� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderBooleans()
{
	g_pRenderText->SetFont(g_hFont);
	
	for(int i=0;i<MAX_CHAT;i++)
	{
		CHAT *ci = &Chat[i];
		if(ci->IDLifeTime>0 || ci->LifeTime[0]>0)
		{
			vec3_t Position;
			int ScreenX,ScreenY;
            if( ci->Owner!=NULL )
            {
				OBJECT *o = &ci->Owner->Object;
				Vector(o->Position[0],o->Position[1],o->Position[2]+o->BoundingBoxMax[2]+60.f,Position);
#ifdef PBG_ADD_LITTLESANTA_NPC
				//npc�� �������� �����Ǹ鼭 �⺻���� 60.f�� ���̰� �ʹ� ũ��.�����Ͽ� ���� �⺻���� ��������.
				// float i=60.f;	o->Scale * i�� �⺻������ ���� ����������??
				if(o->Type >= MODEL_LITTLESANTA && o->Type <= MODEL_LITTLESANTA_END)
				{
					Vector(o->Position[0],o->Position[1],o->Position[2]+o->BoundingBoxMax[2]+20.f,Position);
				}
#endif //PBG_ADD_LITTLESANTA_NPC
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
				if(o->Type==MODEL_MERCHANT_MAN)
				{
					Vector(o->Position[0],o->Position[1],o->Position[2]+o->BoundingBoxMax[2]+20.f,Position);
				}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
				Projection(Position,&ScreenX,&ScreenY);		//. ScreenX, ScreenY: 640*480 ����
            }
            else
            {
				Projection(ci->Position,&ScreenX,&ScreenY);	//. ScreenX, ScreenY: 640*480 ����
            }
			SetBooleanPosition(ci);	//. BoxSize ����(���� �ػ� ����)
			ci->x = ScreenX-(ci->Width/2);	//. ci->x, ci->y: 640*480 ����
			ci->y = ScreenY-ci->Height;
		}
	}
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHAT;i++)		//. Bubble sorting
#else // _VS2008PORTING
	for(i=0;i<MAX_CHAT;i++)		//. Bubble sorting
#endif // _VS2008PORTING
	{
		CHAT *ci = &Chat[i];
		if(ci->IDLifeTime>0 || ci->LifeTime[0]>0)
		{
			for(int j=0;j<MAX_CHAT;j++)
			{
				CHAT *cj = &Chat[j];
				if(i!=j && (cj->IDLifeTime>0 || cj->LifeTime[0]>0))
				{
					if(ci->x+ci->Width>cj->x && ci->x<cj->x+cj->Width &&
						ci->y+ci->Height>cj->y && ci->y<cj->y+cj->Height)
					{
						if(ci->y < cj->y+cj->Height/2)
							ci->y = cj->y-ci->Height;
						else
							ci->y = cj->y+cj->Height;
					}
				}
			}
		}
	}
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CHAT;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_CHAT;i++)
#endif // _VS2008PORTING
	{
		CHAT *ci = &Chat[i];
		if(ci->IDLifeTime>0 || ci->LifeTime[0]>0)
		{
			//. Fit to screen
#ifdef _VS2008PORTING
			if(ci->x < 0) ci->x = 0;
			if(ci->x >= (int)WindowWidth-ci->Width) ci->x = WindowWidth-ci->Width;
			if(ci->y < 0) ci->y = 0;
			if(ci->y >= (int)WindowHeight-ci->Height) ci->y = WindowHeight-ci->Height;
#else // _VS2008PORTING
			if(ci->x < 0) ci->x = 0;
			if(ci->x >= WindowWidth-ci->Width) ci->x = WindowWidth-ci->Width;
			if(ci->y < 0) ci->y = 0;
			if(ci->y >= WindowHeight-ci->Height) ci->y = WindowHeight-ci->Height;
#endif // _VS2008PORTING
			
			RenderBoolean(ci->x,ci->y,ci);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//  �������̽� �����.
///////////////////////////////////////////////////////////////////////////////
extern int TextNum;
extern char TextList[30][100];
extern int  TextListColor[30];
extern int  TextBold[30];
extern SIZE Size[30];


///////////////////////////////////////////////////////////////////////////////
// 	�ð� ���� ������ �������Ѵ�. ( ��ũ��, ī��Ʈ �ٿ�. ��� )
///////////////////////////////////////////////////////////////////////////////
void RenderTimes ()
{
	float x,y,Width,Height;
	
	//��ũ�� �Է� �ð�
    if(MacroTime > 0)
	{
		Width=50;Height=2;x=(GetScreenWidth()-Width)/2;y=480-48-40;
		
		int Time = MacroTime*(int)Width/100;
       	EnableAlphaTest();
		g_pRenderText->RenderText((int)x,(int)y,"Macro Time");
		RenderBar(x,y+12,Width,Height,(float)Time);
	}
	glColor3f(1.f,1.f,1.f);
	
    matchEvent::RenderTime ();
}

extern int g_iKeyPadEnable;

void RenderCursor()
{
   	EnableAlphaTest();
	glColor3f(1.f,1.f,1.f);
	
	float u = 0.f;
	float v = 0.f;
	int Frame = (int)(WorldTime*0.01f)%6;
	if(Frame==1 || Frame==3 || Frame==5) u = 0.5f;
	if(Frame==2 || Frame==3 || Frame==4) v = 0.5f;
	if(g_iKeyPadEnable || ErrorMessage)
	{
		RenderBitmap(BITMAP_CURSOR,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
	}
	else if(SelectedItem!=-1)
	{
		RenderBitmap(BITMAP_CURSOR+3,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
	}
	else if(SelectedNpc!=-1)
	{
#ifdef _PVP_ATTACK_GUARD
		if (SelectedCharacter == -1 && SelectedNpc != -1)
			SelectedCharacter = SelectedNpc;
		
		if(CheckAttack() && !MouseOnWindow)
		{
#ifdef PK_ATTACK_TESTSERVER_LOG
			CHARACTER *c = &CharactersClient[SelectedCharacter];
			g_ErrorReport.Write( "!!!!!!!!!!!!!!!!! PK !!!!!!!!!!!!!!! : ID(%s) PK(%d)  \n", c->ID, c->PK);
			g_ConsoleDebug->Write(MCD_ERROR, "[CheckAttack1() : ID(%s) PK(%d)\n]", c->ID, c->PK);
#endif // PK_ATTACK_TESTSERVER_LOG
			RenderBitmap(BITMAP_CURSOR+2,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		}
        else
#endif	// _PVP_ATTACK_GUARD
			if(M38Kanturu2nd::Is_Kanturu2nd())
			{
				RenderBitmap(BITMAP_CURSOR2,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
			}
			else
			{
				RenderBitmap(BITMAP_CURSOR+4,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f,u,v,0.5f,0.5f);
			}
	}
	else if(SelectedOperate!=-1)
	{
		if((World==WD_0LORENCIA && Operates[SelectedOperate].Owner->Type==MODEL_POSE_BOX) ||
			(World==WD_1DUNGEON && Operates[SelectedOperate].Owner->Type==60) ||
			(World==WD_2DEVIAS && Operates[SelectedOperate].Owner->Type==91) ||
			(World==WD_3NORIA && Operates[SelectedOperate].Owner->Type==38)
			)
			RenderBitmap(BITMAP_CURSOR+6,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		else
			RenderBitmap(BITMAP_CURSOR+7,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
	}
	else if((!Hero->SafeZone/*||EnableEdit*/) && SelectedCharacter!=-1)
	{
		if(CheckAttack() && !MouseOnWindow)
        {
            if ( battleCastle::InBattleCastle() )
            {
				RenderBitmap(BITMAP_CURSOR2,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
            }
            else
            {
				RenderBitmap(BITMAP_CURSOR+2,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
            }
        }
		else
			RenderBitmap(BITMAP_CURSOR,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
	}							
	else if( g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_COMMAND ) )
	{
		if( g_pCommandWindow->GetMouseCursor( ) == CURSOR_IDSELECT )
		{
			RenderBitmap(BITMAP_INTERFACE_EX+29,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		}
		else if( g_pCommandWindow->GetMouseCursor( ) == CURSOR_NORMAL )
		{
			RenderBitmap(BITMAP_CURSOR,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);	
		}
		else if( g_pCommandWindow->GetMouseCursor( ) == CURSOR_PUSH )
		{
			RenderBitmap(BITMAP_CURSOR+1,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		}
	}
	else if( (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INVENTORY)
		&& g_pMyInventory->GetRepairMode() == SEASON3B::CNewUIMyInventory::REPAIR_MODE_ON)
		|| (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) 
		&& g_pNPCShop->GetShopState() == SEASON3B::CNewUINPCShop::SHOP_STATE_REPAIR)
		)
    {
		if(MouseLButton == false)
		{
			//  ���� Ŀ��.
			RenderBitmap(BITMAP_CURSOR+5,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		}
		else
		{
			RenderBitmapRotate(BITMAP_CURSOR+5,(float)MouseX+5.f,(float)MouseY+18.f,24.f,24.f,45.f);
		}
		
		
    }
    else if(RepairEnable==2)    //  ����������.
    {   
        if(sin(WorldTime*0.02f)>0)
        {
            RenderBitmapRotate(BITMAP_CURSOR+5,(float)MouseX+10.f,(float)MouseY+10.f,24.f,24.f,0.f);
        }
        else
        {
            RenderBitmapRotate(BITMAP_CURSOR+5,(float)MouseX+5.f,(float)MouseY+18.f,24.f,24.f,45.f);
        }
    }
	else
	{
		if(!MouseLButton)
			RenderBitmap(BITMAP_CURSOR,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		else
		{
			if(DontMove)
				RenderBitmap(BITMAP_CURSOR+8,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
			else
				RenderBitmap(BITMAP_CURSOR+1,(float)MouseX-2.f,(float)MouseY-2.f,24.f,24.f);
		}
	}
}











///////////////////////////////////////////////////////////////////////////////
// ������ �󿡼� ����ϴ� �Լ���
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ �󿡼� �� ������Ʈ ã�� �Լ�
///////////////////////////////////////////////////////////////////////////////

void BackSelectModel()
{
#ifdef _VS2008PORTING
	for(int i=1;i<20;i++)
	{
		if(SelectModel-i < 0)
			break;
		if(Models[SelectModel-i].NumMeshs > 0)
		{
			SelectModel -= i;
			break;
		}
	}
#else // _VS2008PORTING
	bool Success = false;
	for(int i=1;i<20;i++)
	{
		if(SelectModel-i < 0)
			break;
		if(Models[SelectModel-i].NumMeshs > 0)
		{
			Success = true;
			break;
		}
	}
	if(Success)
		SelectModel -= i;
#endif // _VS2008PORTING
}

///////////////////////////////////////////////////////////////////////////////
// ������ �󿡼� ���� ������Ʈ ã�� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ForwardSelectModel()
{
#ifdef _VS2008PORTING
	for(int i=1;i<20;i++)
	{
		if(Models[SelectModel+i].NumMeshs > 0)
		{
			SelectModel += i;
			break;
		}
	}
#else // _VS2008PORTING
	bool Success = false;
	for(int i=1;i<20;i++)
	{
		if(Models[SelectModel+i].NumMeshs > 0)
		{
			Success = true;
			break;
		}
	}
	if(Success)
		SelectModel += i;
#endif // _VS2008PORTING
}

///////////////////////////////////////////////////////////////////////////////
// ������ �󿡼� Ű�Է� �޴� �Լ�
///////////////////////////////////////////////////////////////////////////////

extern int  EditMonsterNumber;

///////////////////////////////////////////////////////////////////////////////
// ������ ��ɵ�
///////////////////////////////////////////////////////////////////////////////

extern int MonsterKey;

void EditObjects()
{
	if(EditFlag == EDIT_MONSTER)
	{
		if(MouseLButtonPush) 
		{
			MouseLButtonPush = false;
			bool Success = RenderTerrainTile(SelectXF,SelectYF,(int)SelectXF,(int)SelectYF,1.f,1,true);
			if(Success)
			{
				CHARACTER *c = CreateMonster(MonsterScript[SelectMonster].Type,(BYTE)(CollisionPosition[0]/TERRAIN_SCALE),(BYTE)(CollisionPosition[1]/TERRAIN_SCALE),MonsterKey++);
				c->Object.Kind = KIND_EDIT;
			}
		}
		if(MouseRButtonPush) 
		{
			MouseRButtonPush = false;
			if(SelectedCharacter != -1)
			{
				CharactersClient[SelectedCharacter].Object.Live = false;
			}
		}
	}
	if(EditFlag == EDIT_OBJECT)
	{
		if(MouseRButtonPush) 
		{
			MouseRButtonPush = false;
			bool Success = RenderTerrainTile(SelectXF,SelectYF,(int)SelectXF,(int)SelectYF,1.f,1,true);
			if(Success)
			{
				OBJECT *o = CreateObject(SelectModel,CollisionPosition,PickObjectAngle);
				int Scale = (int)TERRAIN_SCALE;
				o->Position[0] = (float)((int)o->Position[0]/Scale+0.5f)*Scale;
				o->Position[1] = (float)((int)o->Position[1]/Scale+0.5f)*Scale;
			}
		}
		if(MouseLButtonPush) 
		{
			MouseLButtonPush = false;
			if(!PickObject)
			{
				if(MouseX < 100 && MouseY < 100)
				{
					PickObject = CreateObject(SelectModel,MouseTarget,PickObjectAngle);
				}
				else
				{
					PickObject = CollisionDetectObjects(PickObject);
					if(PickObject)
						PickObjectHeight = PickObject->Position[2] - RequestTerrainHeight(PickObject->Position[0],PickObject->Position[1]);
				}
			}
		}
		if(PickObject)
		{
			if(MouseLButton) 
			{
				bool Success = RenderTerrainTile(SelectXF,SelectYF,(int)SelectXF,(int)SelectYF,1.f,1,true);
				if(Success)
				{
					VectorCopy(CollisionPosition,PickObject->Position);
					if(PickObjectLockHeight)
					{
						int Scale = (int)TERRAIN_SCALE/2;
						PickObject->Position[0] = (float)((int)PickObject->Position[0]/Scale*Scale);
						PickObject->Position[1] = (float)((int)PickObject->Position[1]/Scale*Scale);
					}
					else
						PickObject->Position[2] += PickObjectHeight;
				}
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
				if(SEASON3B::IsPress('Q') == TRUE)
					PickObject->Angle[0] -= 5.f;
				if(SEASON3B::IsPress('E') == TRUE)
					PickObject->Angle[0] += 5.f;
				if(SEASON3B::IsPress('A') == TRUE)
					PickObject->Angle[2] += 30.f;
				if(SEASON3B::IsPress('D') == TRUE)
					PickObject->Angle[2] -= 30.f;
				if(SEASON3B::IsPress('W') == TRUE)
					PickObjectHeight += 5.f;
				if(SEASON3B::IsPress('S') == TRUE)
					PickObjectHeight -= 5.f;
				if(SEASON3B::IsPress('R') == TRUE)
					PickObject->Scale += 0.02f;
				if(SEASON3B::IsPress('F') == TRUE)
					PickObject->Scale -= 0.02f;
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
				if(HIBYTE(GetAsyncKeyState('Q'))==128)
					PickObject->Angle[0] -= 5.f;
				if(HIBYTE(GetAsyncKeyState('E'))==128)
					PickObject->Angle[0] += 5.f;
				if(HIBYTE(GetAsyncKeyState('A'))==128)
					PickObject->Angle[2] += 30.f;
				if(HIBYTE(GetAsyncKeyState('D'))==128)
					PickObject->Angle[2] -= 30.f;
				if(HIBYTE(GetAsyncKeyState('W'))==128)
					PickObjectHeight += 5.f;
				if(HIBYTE(GetAsyncKeyState('S'))==128)
					PickObjectHeight -= 5.f;
				if(HIBYTE(GetAsyncKeyState('R'))==128)
					PickObject->Scale += 0.02f;
				if(HIBYTE(GetAsyncKeyState('F'))==128)
					PickObject->Scale -= 0.02f;
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
				if(MouseX >= 640-100 && MouseY < 100)
				{
					DeleteObject(PickObject,&ObjectBlock[PickObject->Block]);
					PickObject = NULL;
				}
			}
			else
			{
				VectorCopy(PickObject->Angle,PickObjectAngle);
				CreateObject(PickObject->Type,PickObject->Position,PickObject->Angle,PickObject->Scale);
				if(EnableRandomObject)
				{
					vec3_t Position,Angle;
					for(int i=0;i<9;i++)
					{
						VectorCopy(PickObject->Position,Position);
						VectorCopy(PickObject->Angle,Angle);
						Position[0] += (float)(rand()%2000-1000);
						Position[1] += (float)(rand()%2000-1000);
						Position[2]  = RequestTerrainHeight(Position[0],Position[1]);
						Angle[2] = (float)(rand()%360);
						CreateObject(PickObject->Type,Position,Angle,PickObject->Scale+(float)(rand()%16-8)*0.01f);
					}
				}
				DeleteObject(PickObject,&ObjectBlock[PickObject->Block]);
				PickObject = NULL;
			}
		}
	}
	
	if(EditFlag == EDIT_HEIGHT)
	{
		if(MouseLButton)
		{
			AddTerrainHeight(CollisionPosition[0],CollisionPosition[1],-10.f,BrushSize+1,BackTerrainHeight);
			CreateTerrainNormal();
            CreateTerrainLight();
		}
		if(MouseRButton)
		{
			AddTerrainHeight(CollisionPosition[0],CollisionPosition[1],10.f,BrushSize+1,BackTerrainHeight);
			CreateTerrainNormal();
            CreateTerrainLight();
		}
	}
	if(EditFlag == EDIT_LIGHT)
	{
		vec3_t Light;
		if(MouseLButton)
		{
			switch(SelectColor)
			{
			case 0:
				Vector(0.1f,0.1f,0.1f,Light);
				break;
			case 1:
				Vector(-0.1f,-0.1f,-0.1f,Light);
				break;
			case 2:
				Vector(0.05f,-0.05f,-0.05f,Light);
				break;
			case 3:
				Vector(0.05f,0.05f,-0.05f,Light);
				break;
			case 4:
				Vector(-0.05f,0.05f,-0.05f,Light);
				break;
			case 5:
				Vector(-0.05f,0.05f,0.05f,Light);
				break;
			case 6:
				Vector(-0.05f,-0.05f,0.05f,Light);
				break;
			case 7:
				Vector(0.05f,-0.05f,0.05f,Light);
				break;
			}
			AddTerrainLightClip(CollisionPosition[0],CollisionPosition[1],Light,BrushSize+1,TerrainLight);
            CreateTerrainLight();
		}
		if(MouseRButton)
		{
			int mx = (int)(CollisionPosition[0]/TERRAIN_SCALE);
			int my = (int)(CollisionPosition[1]/TERRAIN_SCALE);
			for(int y=my-2;y<=my+2;y++)
			{
				for(int x=mx-2;x<=mx+2;x++)
				{
					int Index1 = TERRAIN_INDEX_REPEAT(x  ,y  );
					int Index2 = TERRAIN_INDEX_REPEAT(x-1,y  );
					int Index3 = TERRAIN_INDEX_REPEAT(x+1,y  );
					int Index4 = TERRAIN_INDEX_REPEAT(x  ,y-1);
					int Index5 = TERRAIN_INDEX_REPEAT(x  ,y+1);
					for(int i=0;i<3;i++)
					{
						TerrainLight[Index1][i] = (TerrainLight[Index1][i]+TerrainLight[Index2][i]+TerrainLight[Index3][i]+TerrainLight[Index4][i]+TerrainLight[Index5][i])*0.2f;
					}
				}
			}
            CreateTerrainLight();
		}
	}
	if(EditFlag == EDIT_MAPPING)
	{
		int sx = 640-30;
		int sy = 0;
		for(int i=0;i<14;i++)
		{
			if(MouseX>=sx && MouseY>=sy+i*30 && MouseX<sx+30 && MouseY<sy+i*30+30)
			{
				if(MouseLButton)
				{
					SelectMapping = i;
					return;
				}
			}
		}
		int x = (int)SelectXF;
		int y = (int)SelectYF;
		int Index1 = TERRAIN_INDEX_REPEAT(x  ,y  );
		int Index2 = TERRAIN_INDEX_REPEAT(x+1,y  );
		int Index3 = TERRAIN_INDEX_REPEAT(x+1,y+1);
		int Index4 = TERRAIN_INDEX_REPEAT(x  ,y+1);
		if(Bitmaps[BITMAP_MAPTILE+SelectMapping].Components != 4)
		{
			if(MouseLButton)
			{
				if(CurrentLayer == 0)
				{
					for(int i=y-BrushSize;i<=y+BrushSize;i++)
					{
						for(int j=x-BrushSize;j<=x+BrushSize;j++)
						{
							TerrainMappingLayer1[TERRAIN_INDEX_REPEAT(j,i)] = SelectMapping;
						}
					}
				}
				if(CurrentLayer == 1)
				{
					for(int i=y-1;i<=y+1;i++)
					{
						for(int j=x-1;j<=x+1;j++)
						{
							TerrainMappingLayer2[TERRAIN_INDEX_REPEAT(j,i)] = SelectMapping;
						}
					}
					TerrainMappingAlpha[Index1] += 0.1f;
					TerrainMappingAlpha[Index2] += 0.1f;
					TerrainMappingAlpha[Index3] += 0.1f;
					TerrainMappingAlpha[Index4] += 0.1f;
					if(TerrainMappingAlpha[Index1] > 1.f) TerrainMappingAlpha[Index1] = 1.f;
					if(TerrainMappingAlpha[Index2] > 1.f) TerrainMappingAlpha[Index2] = 1.f;
					if(TerrainMappingAlpha[Index3] > 1.f) TerrainMappingAlpha[Index3] = 1.f;
					if(TerrainMappingAlpha[Index4] > 1.f) TerrainMappingAlpha[Index4] = 1.f;
				}
			}
			if(MouseRButton)
			{
				if(CurrentLayer == 1)
				{
					for(int i=y-1;i<=y+1;i++)
					{
						for(int j=x-1;j<=x+1;j++)
						{
							TerrainMappingLayer2[TERRAIN_INDEX_REPEAT(j,i)] = 255;
						}
					}
					TerrainMappingAlpha[Index1] = 0.f;
					TerrainMappingAlpha[Index2] = 0.f;
					TerrainMappingAlpha[Index3] = 0.f;
					TerrainMappingAlpha[Index4] = 0.f;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ �Ǵ� ������� ���� ����ϴ� ������
///////////////////////////////////////////////////////////////////////////////

int TotalPacketSize = 0;
int OldTime = timeGetTime();
extern int MixItemValue;
extern int MixItemValueOld;

void RenderDebugWindow()
{
	g_pRenderText->SetFont(g_hFont);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 255);
   	
	if(timeGetTime()-OldTime >= 1000)
	{
		OldTime = timeGetTime();
		TotalPacketSize = 0;
	}
	
#ifdef ACC_PACKETSIZE
	
	DWORD dwTick = GetTickCount() - g_dwPacketInitialTick;
	sprintf(Text,"Send - %d Byte/s, Recv - %d Byte/s", g_iTotalPacketSend*1000/dwTick, g_iTotalPacketRecv*1000/dwTick);
	RenderText(0,50,Text);
#endif //ACC_PACKETSIZE
	
#ifdef ENABLE_EDIT
	char Text[256];
	if(EditFlag == EDIT_MAPPING)
	{
		int sx = 640-30;
		int sy = 0;
		for(int i=0;i<14;i++)
		{
			if(i == SelectMapping)
				glColor3f(1.f,1.f,1.f);
			else
				glColor3f(0.8f,0.8f,0.8f);
			RenderBitmap(BITMAP_MAPTILE+i,(float)(sx),(float)(sy+i*30),30.f,30.f);
		}
		if(CurrentLayer == 0)
			g_pRenderText->RenderText(640-100,sy,"Background");
		else
			g_pRenderText->RenderText(640-100,sy,"Layer1");
		sprintf(Text,"Brush Size: %d",BrushSize*2+1);
		g_pRenderText->RenderText(640-100,sy+11,Text);
	}
	glColor3f(1.f,1.f,1.f);
	if(EditFlag == EDIT_OBJECT)
	{
		g_pRenderText->RenderText(640-100,0,"Garbage");
		g_pRenderText->RenderText(0,0,Models[SelectModel].Name);
	}
	if(EditFlag == EDIT_MONSTER)
	{
		for(int i=0;i<EditMonsterNumber;i++)
		{
			if(i == SelectMonster)
				glColor3f(1.f,0.8f,0.f);
			else
				glColor3f(1.f,1.f,1.f);
			sprintf(Text,"%2d: %s",MonsterScript[i].Type,MonsterScript[i].Name);
			g_pRenderText->RenderText(640-100,i*10,Text);
		}
	}
	if(EditFlag == EDIT_LIGHT)
	{
		for(int i=0;i<8;i++)
		{
			if(i == SelectColor)
				glColor3f(1.f,0.8f,0.f);
			else
				glColor3f(1.f,1.f,1.f);

			g_pRenderText->RenderText(640-64,i*10,ColorTable[i]);
		}
	}
#endif //ENABLE_EDIT
}


/*
void RenderRadar()
{
BeginBitmap();
glDisable(GL_TEXTURE_2D);
glColor3f(0.5f,1.f,0.5f);
vec3_t Angle;
float Matrix[3][4];
Vector(0.f,0.f,CameraAngle[2],Angle);
AngleMatrix(Angle,Matrix);
vec3_t p,p1[4],p2;
p1[0][0] = -128;p1[0][1] = -128;
p1[1][0] =  128;p1[1][1] = -128;
p1[2][0] =  128;p1[2][1] =  128;
p1[3][0] = -128;p1[3][1] =  128;
glBegin(GL_LINE_LOOP);
for(int i=0;i<4;i++)
{
VectorRotate(p1[i],Matrix,p2);
glVertex2f(p2[0]+181,WindowHeight+p2[1]-181);
}
glEnd();
Vector(Hero->Object.Position[0]/TERRAIN_SCALE-128.f,Hero->Object.Position[1]/TERRAIN_SCALE-128.f,0.f,p);
VectorRotate(p,Matrix,p2);
float x,y;
x=p2[0]+181;y=WindowHeight+p2[1]-181;
p1[0][0] = x-14;p1[0][1] = y-10;
p1[1][0] = x+14;p1[1][1] = y-10;
p1[2][0] = x+14;p1[2][1] = y+10;
p1[3][0] = x-14;p1[3][1] = y+10;
glBegin(GL_LINE_LOOP);
for(i=0;i<4;i++)
glVertex2f(p1[i][0],p1[i][1]);
glEnd();
glEnable(GL_TEXTURE_2D);
EndBitmap();
}
*/

void MouseRButtonReset()
{
	MouseRButtonPop = false;
	MouseRButtonPush= false;
	MouseRButton = false;
	MouseRButtonPress = 0;
}

bool IsGMCharacter()
{
	if( ( Hero->Object.Kind == KIND_PLAYER && Hero->Object.Type == MODEL_PLAYER && Hero->Object.SubType == MODEL_GM_CHARACTER )
		|| ( g_isCharacterBuff((&Hero->Object), eBuff_GMEffect) ) 
		|| ( Hero->CtlCode & CTLCODE_08OPERATOR )
#ifdef CSK_FIX_GM_FORTV
		|| (Hero->CtlCode & CTLCODE_04FORTV)
#endif // CSK_FIX_GM_FORTV
#ifdef LDK_FIX_GM_WEBZEN_NAME
		|| FindText( Hero->ID, "webzen" )
#endif //LDK_FIX_GM_WEBZEN_NAME
		|| ( Hero->CtlCode & CTLCODE_20OPERATOR ) )
	{
		return true;
	}

	return false;
}

bool IsNonAttackGM()
{
	if( Hero->CtlCode & CTLCODE_04FORTV || Hero->CtlCode & CTLCODE_08OPERATOR)
	{
		return true;
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////
// ������ ä�ø޼����� �̿� �̵��Ҽ� ���� �ʿ� �̵��Ϸ� �ϴ��� ����
// parameter: 
//		char *szChatText - ������ ���� �Էµ� �޼���
// return value:
//		true - ������ ä�ø޼����� �̿� �̵��Ҽ� ���� �ʿ� �̵��Ϸ��� ��
//		false - ���� ����
///////////////////////////////////////////////////////////////////////////////
#ifdef LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG
bool IsIllegalMovementByUsingMsg(const char *szChatText)
{
	bool bCantFly			= false;
	bool bCantSwim			= false;
	bool bEquipChangeRing	= false;
	
	bool bMoveAtlans		= false;
	bool bMoveIcarus		= false;

	char szChatTextUpperChars[256];
	strcpy(szChatTextUpperChars, szChatText);
	_strupr(szChatTextUpperChars);
	
	short pEquipedRightRingType = (&CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT])->Type;
	short pEquipedLeftRingType	= (&CharacterMachine->Equipment[EQUIPMENT_RING_LEFT])->Type;
	short pEquipedHelperType	= (&CharacterMachine->Equipment[EQUIPMENT_HELPER])->Type;
	short pEquipedWingType		= (&CharacterMachine->Equipment[EQUIPMENT_WING])->Type;
					

	// ���� ���� (���� ����) (Ÿũȣ��, ����Ʈ, �渱�� �� �� �ִ� ����)
	if ((pEquipedWingType	== -1				&& pEquipedHelperType != ITEM_HELPER+3 && 
		 pEquipedHelperType != ITEM_HELPER+37	&& pEquipedHelperType != ITEM_HELPER+4) || 
		pEquipedHelperType == ITEM_HELPER+2)
	{
		bCantFly = true;
	}
	// �������� ���ϴ� ����ž�� (���ϸ���, ����Ʈ) 
	if (pEquipedHelperType == ITEM_HELPER+2 || pEquipedHelperType == ITEM_HELPER+3)
	{
		bCantSwim = true;
	}
	// ���Ź��� ����
	if (g_ChangeRingMgr->CheckMoveMap(pEquipedLeftRingType, pEquipedRightRingType))
	{
		bEquipChangeRing = true;
	}

	
	// /�̵� ��ɾ� ����
	if ((strstr(szChatTextUpperChars, "/MOVE") != NULL) || 
		(strlen(GlobalText[260]) > 0 && strstr(szChatTextUpperChars, GlobalText[260]) != NULL))
	{
		// list 'm_listMoveInfoData'�� �������� ����� �� �� �̸��� ������ ����
		// szMainMapName -> ���� ���, szSubMapName -> ����
		std::list<SEASON3B::CMoveCommandData::MOVEINFODATA*> m_listMoveInfoData;
		m_listMoveInfoData = SEASON3B::CMoveCommandData::GetInstance()->GetMoveCommandDatalist();
		
		std::list<SEASON3B::CMoveCommandData::MOVEINFODATA*>::iterator li = m_listMoveInfoData.begin();
		

		// user�� �̵��Ϸ��� ���� �¿��� �����ϴ� �� ���� search
		while (li != m_listMoveInfoData.end())
		{
			char cMapNameUpperChars[256];
			strcpy(cMapNameUpperChars, (*li)->_ReqInfo.szSubMapName);
			_strupr(cMapNameUpperChars);
			
			if (strstr(szChatText, ((*li)->_ReqInfo.szMainMapName)) != NULL || 
				strstr(szChatTextUpperChars, cMapNameUpperChars) != NULL)
				break;

			li++;
		}

		// user�� �̵��Ϸ��� ���� �¿��� �����ϴ� ��
		if (li != m_listMoveInfoData.end())
		{
			// ��Ʋ������ �̵��Ϸ��� ��	
			if(stricmp((*li)->_ReqInfo.szMainMapName, GlobalText[37]) == 0)
			{
				bMoveAtlans = true;
			}
			// ��ī�罺�� �̵��Ϸ��� ��
			else if (stricmp((*li)->_ReqInfo.szMainMapName, GlobalText[55]) == 0)
			{
				bMoveIcarus = true;
			}
		}
	}
	
	// �����Ҽ� ���µ� ��Ʋ�󽺷� �̵��Ϸ��� ��ɾ ä��â�� ����
	if (bCantSwim && bMoveAtlans)
	{
		g_pChatListBox->AddText("", GlobalText[261], SEASON3B::TYPE_SYSTEM_MESSAGE);
		return true;
	}
	// ������ ���µ� ��ī�罺�� �̵��Ϸ��� ��ɾ ä��â�� ����
	// (���� ���� ����� ��ī�罺�� �̵��� �� ����)
	if ((bCantFly || bEquipChangeRing) && bMoveIcarus)
	{
		g_pChatListBox->AddText("", GlobalText[263], SEASON3B::TYPE_SYSTEM_MESSAGE);
		return true;
	}
	
	return false;	
}
#endif // LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG