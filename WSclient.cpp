///////////////////////////////////////////////////////////////////////////////
// ��Ŷ �ְų� �޴� �Լ��� ��Ƴ��� ��
// ������Ʈ�� �̰��� ���� �߰���
//
// *** �Լ� ����: 2
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIManager.h"
#include "GuildCache.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzInventory.h"
#include "ZzzLodTerrain.h"
#include "ZzzAI.h"
#include "ZzzTexture.h"
#include "ZzzEffect.h"
#include "ZzzOpenglUtil.h"
#include "ZzzOpenData.h"
#include "ZzzScene.h"
#include "wsclientinline.h"
#include "DSPlaySound.h"
#include "./Utilities/Log/DebugAngel.h"
#include "./Utilities/Log/ErrorReport.h"
#include "./Utilities/Memory/MemoryLock.h"
#include "MatchEvent.h"
#include "GOBoid.h"
#ifdef NP_GAME_GUARD
	#include "ExternalObject/Nprotect/npGameGuard.h"
#endif // NP_GAME_GUARD
#ifdef SAVE_PACKET
#include "./ExternalObject/leaf/stdleaf.h"
#endif // SAVE_PACKET
#include "CSQuest.h"
#include "PersonalShopTitleImp.h"
#include "PvPSystem.h"
#include "GMHellas.h"
#include "npcBreeder.h"
#ifdef PET_SYSTEM
#include "GIPetManager.h"
#endif// PET_SYSTEM
#include "CSMapServer.h"
#include "GMBattleCastle.h"
#include "npcGateSwitch.h"
#include "CSMapInterface.h"
#include "CComGem.h"
#include "UIMapName.h" // rozy
#include "UIMng.h"
#include "GMCrywolf1st.h"
#include "CDirection.h"
#include "GM_Kanturu_3rd.h"
#include "CSParts.h"
#include "PhysicsManager.h"
#include "Event.h"
#ifdef ADD_PCROOM_POINT_SYSTEM
#include "PCRoomPoint.h"
#endif	// ADD_PCROOM_POINT_SYSTEM
#include "MixMgr.h"

#ifdef RESOURCE_GUARD
#include "./ExternalObject/ResourceGuard/MuRGReport.h"
#include "./ExternalObject/ResourceGuard/ResourceGuard.h"
#endif // RESOURCE_GUARD
#include "UIGuardsMan.h"
#include "NewUISystem.h"
#include "NewUICommonMessageBox.h"
#include "NewUICustomMessageBox.h"
#include "NewUIInventoryCtrl.h"
#include "w_CursedTemple.h"
#include "SummonSystem.h"

#ifdef PSW_ADD_MAPSYSTEM
#include "w_MapHeaders.h"
#endif // PSW_ADD_MAPSYSTEM

#ifdef LDK_ADD_NEW_PETPROCESS
#include "w_PetProcess.h"
#endif //LDK_ADD_NEW_PETPROCESS
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
#include "PortalMgr.h"
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef CSK_HACK_TEST
#include "HackTest.h"
#endif // CSK_HACK_TEST
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
#include "DuelMgr.h"
#endif	// YDG_ADD_NEW_DUEL_SYSTEM

#ifdef LDK_ADD_GAMBLE_SYSTEM
#include "GambleSystem.h"
#endif //LDK_ADD_GAMBLE_SYSTEM
#ifdef YDG_MOD_PROTECT_AUTO_V5
#include "ProtectAuto.h"
#endif	// YDG_MOD_PROTECT_AUTO_V5
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
#include "QuestMng.h"
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
#ifdef PBG_ADD_SECRETBUFF
#include "FatigueTimeSystem.h"
#endif //PBG_ADD_SECRETBUFF
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
#include "PKSystem.h"
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM			// �ΰ��Ӽ� �ý���
#include "InGameShopSystem.h"
#include "MsgBoxIGSCommon.h"
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef PBG_ADD_CHARACTERSLOT
#include "Slotlimit.h"
#endif //PBG_ADD_CHARACTERSLOT
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
#include "ServerListManager.h"
#endif // KJH_ADD_SERVER_LIST_SYSTEM
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#include "DummyAttackProtocol.h"
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#include "MonkSystem.h"
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#ifdef LDK_ADD_SCALEFORM
#include "CGFxProcess.h"
#endif //LDK_ADD_SCALEFORM
#ifdef LEM_ADD_GAMECHU
#include "GCCertification.h"
#endif // LEM_ADD_GAMECHU

//////////////////////////////////////////////////////////////////////////
//  DEFINE.
//////////////////////////////////////////////////////////////////////////
#define MAX_DEBUG_MAX 10


//////////////////////////////////////////////////////////////////////////
//  EXTERN.
//////////////////////////////////////////////////////////////////////////

extern BYTE m_AltarState[];

///////////////////////////////////////////
extern int g_iChatInputType;
extern BOOL g_bUseChatListBox;

#ifdef WINDOWMODE
extern BOOL g_bUseWindowMode;
#endif //WINDOWMODE
#ifdef SCRATCH_TICKET
extern CUITextInputBox * g_pSingleTextInputBox;
#endif // SCRATCH_TICKET

extern CChatRoomSocketList * g_pChatRoomSocketList;
extern CGuildCache g_GuildCache;
///////////////////////////////////////////

#ifdef _PVP_ADD_MOVE_SCROLL
extern CMurdererMove g_MurdererMove;
#endif	// _PVP_ADD_MOVE_SCROLL

#ifdef _PVP_DYNAMIC_SERVER_TYPE
extern BOOL g_bIsCurrentServerPvP;
#endif	// _PVP_DYNAMIC_SERVER_TYPE

extern  short   g_shCameraLevel;

extern BYTE DebugText[MAX_DEBUG_MAX][256];
extern int  DebugTextLength[MAX_DEBUG_MAX];
extern char DebugTextCount;
extern int  TotalPacketSize;
extern int g_iKeyPadEnable;

extern CUIMapName* g_pUIMapName; // rozy

#ifndef YDG_ADD_NEW_DUEL_SYSTEM		// �����Ҷ� �����ؾ� ��
extern bool g_PetEnableDuel;	// LHJ - �����߿� ��ũ�ε��� ��ũ���Ǹ��� ������ ���� �Ǵ��ϴ� ����
#endif	// YDG_ADD_NEW_DUEL_SYSTEM	// �����Ҷ� �����ؾ� ��

MASTER_LEVEL_VALUE	Master_Level_Data;
//////////////////////////////////////////////////////////////////////////
//!! ������ �ø���
//////////////////////////////////////////////////////////////////////////

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN		// �ѱ�
#ifdef _ORIGINAL_SERVER
//********************��� ���� �ƴ� ������ ��� �ش� �Ѵ�********************//

//-----------------------------------> �系 ���� ����
//2007.12.07 �׼� (�Ȼ��)
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '4'+3, '1'+4, '2'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"wpqkf3rcsgkma2vo"};
//-----------------------------------------------------------------------------------
//2010.11.04 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '8'+3, '0'+4, '4'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"ddf09j3ohDgLr7lS"};
//-----------------------------------------------------------------------------------
//2010.11.03 �׼� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '8'+3, '0'+4, '3'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"llRkkdc0mFw2V79l"};
//-----------------------------------------------------------------------------------
//2010.11.02 �׼� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '8'+3, '0'+4, '2'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"ms8Tglat7ddsFkH2"};
//-----------------------------------------------------------------------------------
//2010.10.29 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '8'+3, '0'+4, '1'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"l1SwdpfTH9rWh2pn"};
//-----------------------------------------------------------------------------------
//2010.10.28 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '8'+3, '0'+4, '0'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"jklf3qbw5flfQjs6"};
//-----------------------------------------------------------------------------------
//2010.10.27 �׼� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '7'+3, '5'+4, '2'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"1dfclvlSo2aOJ7ik"};
//-----------------------------------------------------------------------------------
//2010.10.21 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '7'+3, '5'+4, '1'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"0sa6f5sJkshflEAn"};
//-----------------------------------------------------------------------------------
//2010.10.15 �׼� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '7'+3, '5'+4, '0'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"a5sc0dTmtuk1tslq"};
//-----------------------------------------------------------------------------------
//2010.10.05 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '7'+3, '4'+4, '8'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"sI8rk9srd4Klakgh"};
//-----------------------------------------------------------------------------------
//2010.10.05 �׼� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '7'+3, '4'+4, '7'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"7C5fS3mklm8eKtvF"};
//-----------------------------------------------------------------------------------
#else //_ORIGINAL_SERVER
//********************��� ���� ��� �ش� �Ѵ�********************//
//���� ��ġ�� ���� ������ ���� ������ ��ġ�Ѵ�
//������ LANGUAGE_KOREAN �� �ȴ�
//===================================> ��� �系 ���� ����
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '4'+3, '1'+4, '2'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"wpqkf3rcsgkma2vo"};
//-----------------------------------------------------------------------------------
//2010.11.04 ��� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '0'+3, '4'+4, '3'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"skfswk7Lflk12QVE"};
//-----------------------------------------------------------------------------------
//2010.10.28 ��� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '0'+3, '4'+4, '2'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"ul7AA3gakAkkAak7"};
//-----------------------------------------------------------------------------------
//2010.10.28 ��� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '0'+3, '4'+4, '1'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"gshfkHs29kds4KeA"};
//-----------------------------------------------------------------------------------
//2010.10.21 ��� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '0'+3, '4'+4, '0'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"8Rs9Kfqlfseso2kL"};
//-----------------------------------------------------------------------------------
//2010.10.07 ��� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '0'+3, '3'+4, '8'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"w0sfeH3okd5ahgr6"};
//-----------------------------------------------------------------------------------
#endif //_ORIGINAL_SERVER
//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_TAIWANESE	// �븸

//-----------------------------------> �系 ���� ����
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'2'+3, '1'+4, '8'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"pmdprdwjs0Pwh3wl"};
//-----------------------------------------------------------------------------------
//2009.07.22 ���� (�̵���)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '0'+4, '5'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"26NwYW4BIQvIZUEr"};
 //-----------------------------------------------------------------------------------
//2010.10.11 ���� (�����)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '1'+4, '0'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"26NwYwklIQvI23Er"};
//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_JAPANESE	// �Ϻ�

//-----------------------------------> �系 ���� ����
//2008.09.09 ���� (�̵���)
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '2'+3, '2'+4, '6'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"DeL7QLE08KXTySe7"};
//-----------------------------------------------------------------------------------
//2009.07.08 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '0'+4, '9'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"jDivfh58dhQi2Vo8"};
//-----------------------------------------------------------------------------------
//2010.08.24 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '8'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"efElef2ERa2eioek"};
//-----------------------------------------------------------------------------------
//2010.09.09 ���� (������)
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '9'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"efieef3Eaefeioek"};
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES	// �ʸ���

//-----------------------------------> �系 ���� ����
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'2'+3, '0'+4, '8'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"CCoosSCKNyaalvMD"};
//-----------------------------------------------------------------------------------
// BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'3'+3, '0'+4, '2'+5};
// BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"Dhkswjstofh1rka4"};
//-----------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_CHINESE		// �߱�

//-----------------------------------> �系 ���� ����
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '0'+4, '6'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"hFUPBTbYehR2KgZj"};
//-----------------------------------------------------------------------------------
//2010.11.23 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'3'+3, '3'+4, '4'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"fdUiqE28nKN324vH"};
//-----------------------------------------------------------------------------------
//2010.09.30 ���� (�����)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'3'+3, '1'+4, '6'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"sDjh2908ds2jnvsL"};
//-----------------------------------------------------------------------------------
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1,'0'+2,'2'+3, '3'+4, '0'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"k5lEopal83udns8h"};
//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_ENGLISH		// �۷ι�
//-----------------------------------> �系 ���� ����
//2010.01.20 ���� (�Ȼ��)
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '1'+4, '3'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"FtpGR9XLWaiwEmho"};
//-----------------------------------------------------------------------------------
//2010.10.28 ���� (�����)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '3'+4, '4'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"55Hhqervsybr23fM"};
//-----------------------------------------------------------------------------------
//2010.10.13 ���� (�����)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '3'+4, '2'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"QDjhqwrgd5b7n6s5"};
//-----------------------------------------------------------------------------------
//2010.09.30 ���� (�����)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '9'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"sDjhqweklr2jnvsL"};
//-----------------------------------------------------------------------------------
//2010.09.20 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '8'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"sDjh2908ds2jnvsL"};
//-----------------------------------------------------------------------------------
//2010.06.23 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '7'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"shF904usjfa9saCS"};
//-----------------------------------------------------------------------------------
//2010.06.10 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '2'+4, '6'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"0skjSAD94sdfjklC"};
//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
#elif SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE	// ��Ʈ��

//-----------------------------------> �系 ���� ����
//2009.06.05 ���� (������)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '0'+4, '2'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"uv5VsdivR29GVskQ"};
//-----------------------------------------------------------------------------------
//2010.10.15 ���� (�����)
BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '1'+4, '3'+5};
BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"zoWm4DFgtl3q3th9"};
//-----------------------------------------------------------------------------------
//2010.08.31 ���� (�ں���)
//BYTE Version[SIZE_PROTOCOLVERSION] = {'1'+1, '0'+2, '3'+3, '1'+4, '2'+5};
//BYTE Serial[SIZE_PROTOCOLSERIAL+1] = {"tlWms5ektl3qhstj"};
//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
#endif //SELECTED_LANGUAGE


//////////////////////////////////////////////////////////////////////////
//  Global Variable.
//////////////////////////////////////////////////////////////////////////
CWsctlc     SocketClient;
CWsctlc*    g_pSocketClient = &SocketClient;
CSimpleModulus g_SimpleModulusCS;
CSimpleModulus g_SimpleModulusSC;

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
CSessionCryptor g_SessionCryptorCS;
CSessionCryptor g_SessionCryptorSC;
#endif // PKD_ADD_ENHANCED_ENCRYPTION

BYTE    g_byPacketSerialSend = 0;
BYTE    g_byPacketSerialRecv = 0;

BOOL    g_bGameServerConnected = FALSE;
DWORD   g_dwLatestMagicTick = 0;

#ifdef USE_SELFCHECKCODE
BYTE g_byNextFuncCrcCheck = 1;
DWORD g_dwLatestFuncCrcCheck = 0;
#endif

#ifdef ACC_PACKETSIZE
int g_iTotalPacketRecv = 0;
int g_iTotalPacketSend = 0;
DWORD g_dwPacketInitialTick;
#endif //ACC_PACKETSIZE

PMSG_MATCH_RESULT	g_wtMatchResult;
PMSG_MATCH_TIMEVIEW	g_wtMatchTimeLeft;
int g_iGoalEffect = 0;

CROWN_SWITCH_INFO *Switch_Info = NULL;

int     HeroKey;
int     CurrentProtocolState;

int DirTable[16] = {-1,-1,  0,-1,  1,-1,  1,0,  1,1,  0,1,  -1,1,  -1,0};

#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD // ��й�ȣ �ڸ��� 10->12�� ���� ����
char    Password[MAX_PASSWORD_SIZE+1];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
char    Password[MAX_ID_SIZE+1];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 

char    QuestionID[MAX_ID_SIZE+1];
char    Question[31];

//////////////////////////////////////////////////////////////////////////
//  Function
//////////////////////////////////////////////////////////////////////////

#define FIRST_CROWN_SWITCH_NUMBER	322


void AddDebugText(unsigned char *Buffer,int Size)
{
	if(DebugTextCount > MAX_DEBUG_MAX-1)
	{
		DebugTextCount = MAX_DEBUG_MAX-1;
		for(int i=1;i<MAX_DEBUG_MAX;i++)
		{
			memcpy(DebugText[i-1],DebugText[i],DebugTextLength[i]);
			DebugTextLength[i-1] = DebugTextLength[i];
		}
	}
	if(Size <= 256)
	{
		memcpy(DebugText[DebugTextCount],Buffer,Size);
		DebugTextLength[DebugTextCount] = Size;
		DebugTextCount++;
	}
}

BOOL CreateSocket(char *IpAddr, unsigned short Port)
{
	BOOL bResult = TRUE;
	
	static bool First;
	if(!First)
	{
		First = true;
		SocketClient.Startup();
#ifdef _DEBUG
		SocketClient.LogPrintOn();
#endif
	}
	g_ErrorReport.Write("[Connect to Server] ip address = %s, port = %d\r\n", IpAddr, Port);
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_NORMAL, "[Connect to Server] ip address = %s, port = %d", IpAddr, Port);
#endif // CONSOLE_DEBUG
	
	SocketClient.Create(g_hWnd, TRUE);
	if( SocketClient.Connect(IpAddr,Port,WM_ASYNCSELECTMSG) == FALSE )
	{
		g_ErrorReport.Write( "Failed to connect. ");
		g_ErrorReport.WriteCurrentTime();
		
		CUIMng::Instance().PopUpMsgWin(MESSAGE_SERVER_LOST);
		
		bResult = FALSE;
	}
	g_byPacketSerialSend = 0;
	g_byPacketSerialRecv = 0;
	
	return ( bResult);
}

void DeleteSocket()
{
	SocketClient.Close();
}

static BYTE bBuxCode[3] = {0xfc,0xcf,0xab};

void BuxConvert(BYTE *Buffer,int Size)
{
	for(int i=0;i<Size;i++)
		Buffer[i] ^= bBuxCode[i%3];
}


int  LogIn = 0;
char LogInID[MAX_ID_SIZE+1] = {0, };

bool First = false;
int FirstTime = 0;

bool LogOut = false;

int  ChatTime = 0;
char ChatText[256];

char ChatWhisperID[MAX_ID_SIZE+1];

int MoveCount = 0;

int CurrentSkill = 0;

bool Teleport = false;

int BuyCost = 0;

int  EnableUse = 0;
//�������̽������� ��Ÿ ����(10���� �����ϰ� ��Ŷ������ ������Ʈ�� �޴���ġ���� 0���� �ٽ� ����-0�̸� �����ִ�.)

int SendGetItem = -1;
int SendDropItem = -1;

///////////////////////////////////////////////////////////////////////////////
// ���
///////////////////////////////////////////////////////////////////////////////

int FindGuildName(char *Name)
{
	for(int i=0;i<MARK_EDIT;i++)
	{
		MARK_t *p = &GuildMark[i];
		if(strcmp(p->GuildName,Name)==NULL)
		{
			return i;
		}
	}
	return -1;
}

void GuildTeam( CHARACTER *c )
{
	OBJECT *o = &c->Object;
	if(o->Live)
	{
		c->GuildTeam = 0;
		
		// ��������϶� �ʷϻ����� ����
		if( Hero->GuildMarkIndex!=-1 && c->GuildMarkIndex==Hero->GuildMarkIndex )
			c->GuildTeam = 1;
		
		// �������̶��..
		if( EnableGuildWar )
		{
			if( GuildWarIndex==-1 && GuildWarName[0] )
			{
				GuildWarIndex = FindGuildName( GuildWarName );
			}
			if( GuildWarIndex >= 0 && c->GuildMarkIndex == GuildWarIndex )
            {
				c->GuildTeam = 2;
            }
		}
	}
}

void InitGuildWar()
{
	EnableGuildWar = false;
	GuildWarIndex = -1;
	GuildWarName[0] = NULL;
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
	{
		CHARACTER *c = &CharactersClient[i];
		GuildTeam(c);
	}
}


BOOL Util_CheckOption( char *lpszCommandLine, unsigned char cOption, char *lpszString);


///////////////////////////////////////////////////////////////////////////////
// �Ʒ����ʹ� ��Ŷ �޴� �Լ�����
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���� ����Ʈ �ޱ�
///////////////////////////////////////////////////////////////////////////////
#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
extern int  ServerLocalSelect;
#endif // KJH_ADD_SERVER_LIST_SYSTEM

void ReceiveServerList( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
	int Offset = sizeof(PHEADER_DEFAULT_SUBCODE_WORD);
	
	BYTE Value2 = *(ReceiveBuffer+Offset++);

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	g_ServerListManager->Release();

	g_ServerListManager->SetTotalServer(MAKEWORD(Value2, Data->Value));		// ��ü ���� ����.(������ ������ �ƴ�)
	
	for(int i=0 ; i<g_ServerListManager->GetTotalServer() ; i++)
	{
		LPPRECEIVE_SERVER_LIST Data2 = (LPPRECEIVE_SERVER_LIST)(ReceiveBuffer+Offset);
		
		g_ServerListManager->InsertServerGroup(Data2->Index, Data2->Percent);
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_RECEIVE, "0xF4����[ReceiveServerList(%d %d %d)]", i, Data2->Index, Data2->Percent);
#endif // CONSOLE_DEBUG		
		Offset += sizeof(PRECEIVE_SERVER_LIST);
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM

	ServerNumber = MAKEWORD(Value2, Data->Value);	// ���� ����.(������ ������ �ƴ�)
	
	for(int i=0;i<MAX_SERVER_HI;i++)
	{
        ServerList[i].Number = 0;
	}
	
#ifdef PJH_USER_VERSION_SERVER_LIST
//	ServerNumber = 2;
#endif //#ifdef PJH_USER_VERSION_SERVER_LIST//�׽�Ʈ ��������

#ifdef PJH_NEW_SERVER_ADD
//#ifdef PJH_FINAL_VIEW_SERVER_LIST2	
//		ServerNumber = 26;//������
#endif //#ifdef PJH_NEW_SERVER_ADD	


//$$$$$$$$$$$$$$$$$$$$$$4
//	DebugAngel_Write( PACKET_SAVE_FILE, "�������� : %d\r\n", ServerNumber);//������
//$$$$$$$$$$$$$$$$$$$$$$4

#ifdef _VS2008PORTING
	for(int i=0;i<ServerNumber;i++)
#else // _VS2008PORTING
	for(i=0;i<ServerNumber;i++)
#endif // _VS2008PORTING
	{
		LPPRECEIVE_SERVER_LIST Data2 = (LPPRECEIVE_SERVER_LIST)(ReceiveBuffer+Offset);

		int Server = Data2->Index/20;	// ������ ��ȣ. �������� 20���� ������ ���� �� ����.

/*
		if(i%5 == 0)
			DebugAngel_Write( PACKET_SAVE_FILE, "          ��ȣ : %d\r\n", Data2->Index);//������
		else
			DebugAngel_Write( PACKET_SAVE_FILE, "          ��ȣ : %d", Data2->Index);//������
*/			
#ifdef PJH_NEW_SERVER_ADD
//		Server = i;//������
#endif //#ifdef PJH_NEW_SERVER_ADD	
#ifdef PJH_USER_VERSION_SERVER_LIST
//		Server = 30 + i;
#endif //#ifdef PJH_USER_VERSION_SERVER_LIST//�׽�Ʈ ��������
#ifdef CONNECT_LIST_FIX
#ifndef PJH_FINAL_VIEW_SERVER_LIST
//#ifdef PJH_NEW_SERVER_ADD
//			if(Server == 13)
//#else
			if(Server == 12)
//#endif //PJH_NEW_SERVER_ADD
			{
#ifdef PJH_NEW_SERVER_ADD
				Server = 29;
#else
				Server = 24;
#endif //#ifdef PJH_NEW_SERVER_ADD
			strcpy(ServerList[Server].Name,GlobalText[559]);
			
			ServerList[Server].Server[ServerList[Server].Number].Index   = Data2->Index;
			ServerList[Server].Server[ServerList[Server].Number].Percent = Data2->Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
			ServerList[Server].Server[ServerList[Server].Number].IsPvPServer = Data2->IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
			ServerList[Server].Number++;
		}
		else
#endif //PJH_FINAL_VIEW_SERVER_LIST
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//��������Ʈ�� ������ ���� ���� ��ȣ�� �ް� ��ȣ�� �ٷ� ������ �����ѹ��� �ȴ�.
			//���� ��� 0 �� ������ ���߸� ����Ű�� �Ű� 1 �� ������ ������ �ްԉ´�.
			//���� iServerListMap ��ǥ�ø� �ϰ�ʹٸ� (23 - ���� ���� ��ġ�� ��) �� ���������ѹ� ��ȣ�� �־��ָ�´�.
			//������ ������ȣ�� enum���� 0���� �����Ѵ�.(@)�� ����� �Ⱦ��̰� �ִ� �����̴�.
			//����	  = 0		
			//����	  = 1		
			//�ٸ�	  = 2		
			//ī��	  = 3	
			//��	  = 4
			//��Į	  = 5
			//���	  = 6
			//����	  = 7
			//Ÿ��	  = 8
			//����(@) = 9
			//���(@) = 10
			//���    = 11
			//�׽�Ʈ  = 12
			//�̿�	  = 13
			//�з�	  = 14
			//�·�(@) = 15
			//�簡(@) = 16
			//Ƽź(@) = 17
			//��ī(@) = 18
			//�÷�(@) = 19
			//����	  = 20
			//�ű�1   = 21
			//�ű�2   = 22
			//�ű�3(@)  = 23
			//Server_Position = 23 - ���� ���� ��ġ�ǰ�;
			//switch(Server_Position)
			//case 4 ~ 10 == ����������1��° ~ ����������7��°.
			//case 14 ~ 21 == ������������1��° ~ ������������8��°
			//text.txt ���Ͽ� 540������ 559�������� ���� �̸� �̴�. 
			//���˼����� 560���� �����ֱ⶧���� 1829������ ������ �����ִ�.
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
			int iServerListMap[] = { 1, 3, 4, 2, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
#elif SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			//������ - �Ϻ� ��û���� ���� ���� ���� ���� 2005.2.4
			//int iServerListMap[] = { 1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
			//			int iServerListMap[] = { 1, 3, 2, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
			// �Ȼ�� - �ż��� �߰� �� ��ġ ����. 2007.2.14
			int iServerListMap[] = { 2, 4, 3, 1, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
#elif defined PJH_FINAL_VIEW_SERVER_LIST
			int iServerListMap[] = { 2, 3, 4, 5, 6, 7, 8, 9, 14, 0, 0, 15, 1, 16, 17, 0, 0, 0, 0, 0, 20, 18, 19, 0, 24};
#elif defined PJH_SEMI_FINAL_VIEW_SERVER_LIST	
			int iServerListMap[] = {  4 ,  5 ,  6 ,  7 ,  8 ,  9 ,  16 , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 20, 18, 19, 0, 24};
#elif defined PJH_USER_VERSION_SERVER_LIST
			int iServerListMap[] = { 2, 3, 4, 5, 6, 7, 8, 9, 14, 0, 0, 15, 1, 16, 17, 0, 0, 0, 0, 0, 20, 18, 19, 0, 24, 30, 31};
#elif defined PJH_FINAL_VIEW_SERVER_LIST2
			int iServerListMap[] = {  4 ,  5 ,  6 ,  7 ,  8 ,  9 ,  15 , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 20, 18, 19, 17, 16};
//			int iServerListMap[] = { 2, 3, 4, 5, 6, 7, 8, 9, 12, 0, 0, 13, 1, 14, 15, 0, 0, 0, 0, 0, 20, 18, 19, 0, 24, 17, 16};
#elif defined PJH_NEW_SERVER_ADD
			int iServerListMap[] = {  4 ,  5 ,  6 ,  7 ,  8 ,  9 ,  15 , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 20, 18, 19, 17, 16,25};
#else
			int iServerListMap[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 20, 15, 16, 17, 18, 11, 12, 13, 19, 21, 22, 23, 24};
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			
			int iServerPos = iServerListMap[Server];
#ifdef PJH_NEW_SERVER_ADD
			int iServerIndex = 28-iServerPos;
#elif SELECTED_LANGUAGE == LANGUAGE_ENGLISH
			int iServerIndex = iServerPos;
#else
			int iServerIndex = 23-iServerPos;
#endif //PJH_NEW_SERVER_ADD
			
#if defined PJH_FINAL_VIEW_SERVER_LIST || defined PJH_SEMI_FINAL_VIEW_SERVER_LIST || defined PJH_FINAL_VIEW_SERVER_LIST2 || defined PJH_NEW_SERVER_ADD
			if(iServerPos == 0)
			{
				Offset += sizeof(PRECEIVE_SERVER_LIST);
				continue;
			}
			
//#ifdef PJH_NEW_SERVER_ADD
//			if(Server == 13)
//#else
			if(Server == 12)
//#endif //PJH_NEW_SERVER_ADD
			{
#ifdef PJH_NEW_SERVER_ADD
				iServerIndex = 29;
#else
				iServerIndex = 24;
#endif //#ifdef PJH_NEW_SERVER_ADD
				strcpy(ServerList[iServerIndex].Name,GlobalText[559]);
			}
			else
				if(Server == 21)
				{
					strcpy ( ServerList[iServerIndex].Name, GlobalText[1873] );	    //  ���ο� ���� ����. ( ��ũ ).
				}
				else
					if(Server == 22)
					{
						strcpy ( ServerList[iServerIndex].Name, GlobalText[1874] );	    //  ���ο� ���� ����. ( ���� ).
					}
					else
						if ( Server == 20 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1829] );	    //  ���ο� ���� ����. ( ���� ).
#else	//PJH_FINAL_VIEW_SERVER_LIST
						if ( Server==19 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[552] );	    //  ���ο� ���� ����. ( �÷� ).
						else if ( Server==20 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1829] );	    //  ���ο� ���� ����. ( ���� ).
#endif	//PJH_FINAL_VIEW_SERVER_LIST
#if defined PJH_FINAL_VIEW_SERVER_LIST2 || defined PJH_NEW_SERVER_ADD
						else if ( Server==23 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1272] );	    //  ���ο� ���� ����. ( �ǹ� ).
						else if ( Server==24 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1273] );	    //  ���ο� ���� ����. ( ���� ).
#endif //PJH_FINAL_VIEW_SERVER_LIST2
#ifdef PJH_NEW_SERVER_ADD
						else if ( Server==25 )
							strcpy ( ServerList[iServerIndex].Name, GlobalText[728] );	    //  ���ο� ���� ����. ( �η� ).
#endif //PJH_NEW_SERVER_ADD
#ifdef PJH_USER_VERSION_SERVER_LIST
						else
						if( Server == 30)
						{
							iServerIndex = 21;
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1879] );	    //  ���� 4ü�� ����
						}
						else
						if( Server == 31)
						{
							iServerIndex = 20;
							strcpy ( ServerList[iServerIndex].Name, GlobalText[1881] );	    //  �系�׽�Ʈ ����
						}
#endif //PJH_USER_VERSION_SERVER_LIST
						else
							strcpy(ServerList[iServerIndex].Name,GlobalText[540+Server]);	// ���� ���� �þ�鼭 �ٲ�
						
						// ServerList[Server].Number�� ���� count.
						ServerList[iServerIndex].Server[ServerList[iServerIndex].Number].Index   = Data2->Index;
						ServerList[iServerIndex].Server[ServerList[iServerIndex].Number].Percent = Data2->Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
						ServerList[iServerIndex].Server[ServerList[iServerIndex].Number].IsPvPServer = Data2->IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
						ServerList[iServerIndex].Number++;
		}
#else	// CONNECT_LIST_FIX
		if ( Server==12 )
		{
			Server = 24;	// ���� ���� �þ�鼭 �ٲ�
			strcpy(ServerList[Server].Name,GlobalText[559]);
			
			ServerList[Server].Server[ServerList[Server].Number].Index   = Data2->Index;
			ServerList[Server].Server[ServerList[Server].Number].Percent = Data2->Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
			ServerList[Server].Server[ServerList[Server].Number].IsPvPServer = Data2->IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
			ServerList[Server].Number++;
		}
		/*
		else if(Server == 12)
		{
		Server = 24;	// ���� ���� �þ�鼭 �ٲ�
		strcpy(ServerList[Server].Name,GlobalText[559]);
		}
		*/
		else
		{
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
			int iServerListMap[] = { 1, 3, 4, 2, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
			if ( Server < sizeof ( iServerListMap) / sizeof ( int))
			{
				Server = iServerListMap[Server];
			}
#endif //SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			int iServerListMap[] = { 2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			
            if ( Server==19 )
            {
				strcpy ( ServerList[23-Server].Name, GlobalText[552] );	    //  ���ο� ���� ����. ( �÷� ).
            }
            else
            {
                strcpy(ServerList[23-Server].Name,GlobalText[540+Server] );	//  ���� ���� �þ�鼭 �ٲ�
            }
			Server = 23-Server;	// ���� ���� �þ�鼭 �ٲ�
		}
		ServerList[Server].Server[ServerList[Server].Number].Index   = Data2->Index;
		ServerList[Server].Server[ServerList[Server].Number].Percent = Data2->Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
		ServerList[Server].Server[ServerList[Server].Number].IsPvPServer = Data2->IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
        ServerList[Server].Number++;
#endif	// CONNECT_LIST_FIX
		
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_RECEIVE, "0xF4����[ReceiveServerList(%d %d %d)]", i, Data2->Index, Data2->Percent);
#endif // CONSOLE_DEBUG
		
		Offset += sizeof(PRECEIVE_SERVER_LIST);
	}
/*
//$$$$$$$$$$$$$$$$$$$$$$4	
fclose(fp);
//$$$$$$$$$$$$$$$$$$$$$$4	
*/	
#ifdef PJH_DEBUG_SERVER_ADD
#ifdef PJH_VIEW_MAIN_SERVER_LIST
	//	int iServerListMap[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 20, 15, 16, 17, 18, 11, 12, 13, 19, 21, 22, 23, 24};
	int iServerListMap[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
	
	for(i=0;i<MAX_SERVER_HI;i++)
	{
        ServerList[i].Number = 0;
	}
	
	for(i = 0; i < 21; i++)
	{
		int Server_Num = 23 - iServerListMap[i];
		
		
		if ( i==12 )
		{
			Server_Num = 24;	// ���� ���� �þ�鼭 �ٲ�
			strcpy(ServerList[Server_Num].Name,GlobalText[559]);
			
			ServerList[Server_Num].Server[ServerList[Server_Num].Number].Index   = i;
			ServerList[Server_Num].Server[ServerList[Server_Num].Number].Percent = 1;
			ServerList[Server_Num].Number++;
		}
		else
		{
			if ( i==19 )
			{
				strcpy ( ServerList[Server_Num].Name, GlobalText[552] );	    //  ���ο� ���� ����. ( �÷� ).
			}
			else if ( i==20 )
				strcpy ( ServerList[Server_Num].Name, GlobalText[1829] );	    //  ���ο� ���� ����. ( ���� ).
			else
			{
				strcpy(ServerList[Server_Num].Name,GlobalText[540+i] );	//  ���� ���� �þ�鼭 �ٲ�
			}
			ServerList[Server_Num].Server[ServerList[Server_Num].Number].Index   = i;
			ServerList[Server_Num].Server[ServerList[Server_Num].Number].Percent = 1;
			ServerList[Server_Num].Number++;
		}
	}
#endif //PJH_VIEW_MAIN_SERVER_LIST
#endif //PJH_DEBUG_SERVER_ADD
#endif // KJH_ADD_SERVER_LIST_SYSTEM
	
	
	CUIMng& rUIMng = CUIMng::Instance();
	if (!rUIMng.m_CreditWin.IsShow())	// ũ������ �Ⱥ��϶��� �ٽ� ������.
	{
		rUIMng.ShowWin(&rUIMng.m_ServerSelWin);
		rUIMng.m_ServerSelWin.UpdateDisplay();
		rUIMng.ShowWin(&rUIMng.m_LoginMainWin);
	}
	
	g_ErrorReport.Write ( "Success Receive Server List.\r\n");
	
#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
#if defined _DEBUG || defined FOR_WORK
	char lpszTemp[256];
	if ( Util_CheckOption( GetCommandLine(), 'a', lpszTemp))
	{
		int iServer = atoi( lpszTemp);
		for ( int i = 0; i < ServerList[24].Number; ++i)
		{
			if ( ( ServerList[24].Server[i].Index % 20) + 1 == iServer)
			{
#ifdef _PVP_DYNAMIC_SERVER_TYPE
				g_bIsCurrentServerPvP = ServerList[24].Server[i].IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
				SendRequestServerAddress2( ServerList[24].Server[i].Index);
#else
				SendRequestServerAddress( ServerList[24].Server[i].Index);
#endif // PKD_ADD_ENHANCED_ENCRYPTION
				ServerLocalSelect = ( ServerList[24].Server[i].Index) % 20 + 1;
			}
		}
	}
#endif
#endif // KJH_ADD_SERVER_LIST_SYSTEM
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0xF4����[ReceiveServerList]");
#endif // CONSOLE_DEBUG
}
void ReceiveServerConnect( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_SERVER_ADDRESS Data = (LPPRECEIVE_SERVER_ADDRESS)ReceiveBuffer;
	char IP[16];
	memset(IP,0,16);
	memcpy(IP,(char*)Data->IP,15);
	g_ErrorReport.Write("[ReceiveServerConnect]");
	SocketClient.Close();
	// ������ü ó�� ���⼭
	if ( CreateSocket(IP,Data->Port))	// �������� ���� �� ReceiveJoinServer()��.
	{	// ���Ӽ����� ���������� �� �� �ְ� �Ѵ�.
		g_bGameServerConnected = TRUE;
#ifdef USE_SELFCHECKCODE
		g_byNextFuncCrcCheck = 1;
#endif
	}
	
	char Text[100];
	sprintf(Text,GlobalText[481],IP,Data->Port);
	g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);	
}

void ReceiveServerConnectBusy( BYTE *ReceiveBuffer )
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPRECEIVE_SERVER_BUSY Data = ( LPPRECEIVE_SERVER_BUSY)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	// ������� �������� �����츦 ���� �޽��� �����츦 �ֻ�ܿ� ���.
	//	CUIMng::Instance().PopUpMsgWin(RECEIVE_JOIN_SERVER_WAITING);
	
	// �׳� �ٽ� ��������Ʈ�� �䱸��.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
		SendRequestServerList2();
#else
		SendRequestServerList();
#endif // PKD_ADD_ENHANCED_ENCRYPTION
}


///////////////////////////////////////////////////////////////////////////////
// ����, ����
///////////////////////////////////////////////////////////////////////////////

void ReceiveJoinServer( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_JOIN_SERVER Data2 = (LPPRECEIVE_JOIN_SERVER)ReceiveBuffer;
	
    if ( LogIn!=0 )
    {
        HeroKey = ((int)(Data2->NumberH)<<8) + Data2->NumberL;
        g_csMapServer.SendChangeMapServer ();
    }
    else
    {
		CUIMng& rUIMng = CUIMng::Instance();
		
        switch(Data2->Result)
        {
        case 0x01:	// ���� ���� ���� ����.
			rUIMng.ShowWin(&rUIMng.m_LoginWin);		// �α��� â�� ������.
            HeroKey = ((int)(Data2->NumberH)<<8) + Data2->NumberL;
            CurrentProtocolState = RECEIVE_JOIN_SERVER_SUCCESS;
            break;
			
        default:		// ���� ���� ���� ����.
            g_ErrorReport.Write( "Connectting error. ");
            g_ErrorReport.WriteCurrentTime();
			rUIMng.PopUpMsgWin(MESSAGE_SERVER_LOST);
            break;
        }
        for(int i=0;i<SIZE_PROTOCOLVERSION;i++)
        {
            if(Version[i]-(i+1) != Data2->Version[i])
            {
				rUIMng.HideWin(&rUIMng.m_LoginWin);		// �α��� â�� ����.
				rUIMng.PopUpMsgWin(MESSAGE_VERSION);
                g_ErrorReport.Write( "Version dismatch - Join server.\r\n");
			}
		}
	}
	
	g_GuildCache.Reset();
	
#if defined _DEBUG || defined FOR_WORK
	if ( Data2->Result == 0x01)
	{
		char lpszTemp[256];
		if ( Util_CheckOption( GetCommandLine(), 'i', lpszTemp))
		{
			g_ErrorReport.Write( "> Try to Login \"%s\"\r\n", m_ID);
			SendRequestLogIn( m_ID, lpszTemp);			
		}
	}
#endif
}

void ReceiveConfirmPassword( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_CONFIRM_PASSWORD Data = (LPPRECEIVE_CONFIRM_PASSWORD)ReceiveBuffer;
	switch(Data->Result)
	{
    case 0:
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD_FAIL_ID;
		break;
    case 1:
		BuxConvert(Data->Question,sizeof(Data->Question));
		strcpy(Question,(char *)Data->Question);
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD_SUCCESS;
		break;
	}
}

void ReceiveConfirmPassword2( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_CONFIRM_PASSWORD2 Data = (LPPRECEIVE_CONFIRM_PASSWORD2)ReceiveBuffer;
	switch(Data->Result)
	{
    case 1:
		BuxConvert(Data->Password,sizeof(Data->Password));
		strcpy(Password,(char *)Data->Password);
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD2_SUCCESS;
		break;
    case 0:
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD2_FAIL_ID;
		break;
    case 2:
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD2_FAIL_ANSWER;
		break;
    case 3:
		CurrentProtocolState = RECEIVE_CONFIRM_PASSWORD2_FAIL_RESIDENT;
		break;
	}
}

void ReceiveChangePassword( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
	switch(Data->Value)
	{
    case 1:
		CurrentProtocolState = RECEIVE_CHANGE_PASSWORD_SUCCESS;
		break;
    case 0:
		CurrentProtocolState = RECEIVE_CHANGE_PASSWORD_FAIL_ID;
		break;
    case 2:
		CurrentProtocolState = RECEIVE_CHANGE_PASSWORD_FAIL_RESIDENT;
		break;
    case 3:
		CurrentProtocolState = RECEIVE_CHANGE_PASSWORD_FAIL_PASSWORD;
		break;
	}
}
// ĳ���� ������ ���� ������ ĳ���͵� ������ �޴´�.(������)
void ReceiveCharacterList( BYTE *ReceiveBuffer )
{
	InitGuildWar();
	
	LPPHEADER_DEFAULT_CHARACTER_LIST Data = (LPPHEADER_DEFAULT_CHARACTER_LIST)ReceiveBuffer;
    
    SetCreateMaxClass ( Data->MaxClass );
#ifdef PBG_FIX_CHAOSMAPMOVE
	// ReceiveTeleport�� ���� �ʴ� ���̵��� ���ε��� ������ �ȵ�
	if(SceneFlag == CHARACTER_SCENE)
	{
		World = WD_74NEW_CHARACTER_SCENE;
	}
#endif //PBG_FIX_CHAOSMAPMOVE
    int Offset = sizeof(PHEADER_DEFAULT_CHARACTER_LIST);
	
	for(int i=0;i<Data->Value;i++)
	{
		LPPRECEIVE_CHARACTER_LIST Data2 = (LPPRECEIVE_CHARACTER_LIST)(ReceiveBuffer+Offset);
		
		int iClass = ChangeServerClassTypeToClientClassType(Data2->Class);
		
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fPos[2], fAngle = 0.0f;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fPos[2], fAngle;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		switch(Data2->Index)
		{
#ifdef PJH_NEW_SERVER_SELECT_MAP
 		case 0:	fPos[0] = 8008.0f;	fPos[1] = 18885.0f;	fAngle = 115.0f; break;
 		case 1:	fPos[0] = 7986.0f;	fPos[1] = 19145.0f;	fAngle = 90.0f; break;
 		case 2:	fPos[0] = 8046.0f;	fPos[1] = 19400.0f;	fAngle = 75.0f; break;
 		case 3:	fPos[0] = 8133.0f;	fPos[1] = 19645.0f;	fAngle = 60.0f; break;
 		case 4:	fPos[0] = 8282.0f;	fPos[1] = 19845.0f;	fAngle = 35.0f; break;
#else //PJH_NEW_SERVER_SELECT_MAP
		case 0:	fPos[0] = 22628.0f;	fPos[1] = 15012.0f;	fAngle = 100.0f; break;
		case 1:	fPos[0] = 22700.0f;	fPos[1] = 15201.0f;	fAngle = 75.0f; break;
		case 2:	fPos[0] = 22840.0f;	fPos[1] = 15355.0f;	fAngle = 50.0f; break;
		case 3:	fPos[0] = 23019.0f;	fPos[1] = 15443.0f;	fAngle = 25.0f; break;
		case 4:	fPos[0] = 23211.6f;	fPos[1] = 15467.0f;	fAngle = 0.0f; break;
#endif //PJH_NEW_SERVER_SELECT_MAP
		}
		
		CHARACTER *c = CreateHero(Data2->Index,iClass,0,fPos[0],fPos[1],fAngle);
		
		c->Level = Data2->Level;
		c->CtlCode = Data2->CtlCode;
		
		memcpy(c->ID,(char *)Data2->ID,MAX_ID_SIZE);
		c->ID[MAX_ID_SIZE] = NULL;
		
		ChangeCharacterExt(Data2->Index,Data2->Equipment);
		
#ifdef _PVP_BLOCK_PVP_CHAR
		c->PK = Data2->PvPState;
#endif	// _PVP_BLOCK_PVP_CHAR
		c->GuildStatus = Data2->byGuildStatus;
		Offset += sizeof(PRECEIVE_CHARACTER_LIST);
	}
#ifdef PBG_ADD_CHARACTERSLOT
	// ���� ������ ��츸 CharacterSlotCount���� ����Ѵ�
	if(BLUE_MU::IsBlueMuServer())
	{
		//ĳ���� �ڸ��� �������� �ʴ´�
		g_SlotLimit->Init();
		g_SlotLimit->SetCharacterCnt(Data->CharacterSlotCount);
		g_SlotLimit->SetSlotPosition();
	}
#endif //PBG_ADD_CHARACTERSLOT
	CurrentProtocolState = RECEIVE_CHARACTERS_LIST;
}
#ifdef PBG_ADD_CHARACTERCARD
CHARACTER_ENABLE g_CharCardEnable;
// ���� ���� ĳ���� ī��(��ȯ����01/��ũ02/����04)
void ReceiveCharacterCard_New(BYTE* ReceiveBuffer)
{
	LPPHEADER_CHARACTERCARD Data = (LPPHEADER_CHARACTERCARD)ReceiveBuffer;
	g_CharCardEnable.bCharacterEnable[0] = false;	//���˻�
	g_CharCardEnable.bCharacterEnable[1] = false;	//��ũ�ε�
#ifdef PBG_MOD_BLUE_SUMMONER_ENABLE
	// ��ȯ���� ĳ���� ī�带 ��翡���� ������� �ʴ°����� ��ȹ����
	g_CharCardEnable.bCharacterEnable[2] = true;	//��ȯ����
#else //PBG_MOD_BLUE_SUMMONER_ENABLE
	g_CharCardEnable.bCharacterEnable[2] = false;	//��ȯ����
#endif //PBG_MOD_BLUE_SUMMONER_ENABLE

	// ���˻� ī�尡 Ȱ��ȭ �Ǿ��ִٸ�
	if((Data->CharacterCard & CLASS_DARK_CARD) == CLASS_DARK_CARD)
		g_CharCardEnable.bCharacterEnable[0] = true;
	// ��ũ�ε� ī�尡 Ȱ��ȭ�Ǿ��ִٸ�
	if((Data->CharacterCard & CLASS_DARK_LORD_CARD) == CLASS_DARK_LORD_CARD)
		g_CharCardEnable.bCharacterEnable[1] = true;
	// ��ȯ���� ī�尡 Ȱ��ȭ �Ǿ��ִٸ�
	if((Data->CharacterCard & CLASS_SUMMONER_CARD) == CLASS_SUMMONER_CARD)
		g_CharCardEnable.bCharacterEnable[2] = true;
}
#endif //PBG_ADD_CHARACTERCARD
// ĳ���;����� ĳ���� ���� ��û�� ���� ����.
void ReceiveCreateCharacter( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_CREATE_CHARACTER Data = (LPPRECEIVE_CREATE_CHARACTER)ReceiveBuffer;
	if(Data->Result==1)
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fPos[2], fAngle = 0.0f;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fPos[2], fAngle;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		switch(Data->Index)
		{
#ifdef PJH_NEW_SERVER_SELECT_MAP
	 	case 0:	fPos[0] = 8008.0f;	fPos[1] = 18885.0f;	fAngle = 115.0f; break;
 		case 1:	fPos[0] = 7986.0f;	fPos[1] = 19145.0f;	fAngle = 90.0f; break;
 		case 2:	fPos[0] = 8046.0f;	fPos[1] = 19400.0f;	fAngle = 75.0f; break;
 		case 3:	fPos[0] = 8133.0f;	fPos[1] = 19645.0f;	fAngle = 60.0f; break;
 		case 4:	fPos[0] = 8282.0f;	fPos[1] = 19845.0f;	fAngle = 35.0f; break;
#else //PJH_NEW_SERVER_SELECT_MAP
		case 0:	fPos[0] = 22628.0f;	fPos[1] = 15012.0f;	fAngle = 100.0f; break;
		case 1:	fPos[0] = 22700.0f;	fPos[1] = 15201.0f;	fAngle = 75.0f; break;
		case 2:	fPos[0] = 22840.0f;	fPos[1] = 15355.0f;	fAngle = 50.0f; break;
		case 3:	fPos[0] = 23019.0f;	fPos[1] = 15443.0f;	fAngle = 25.0f; break;
		case 4:	fPos[0] = 23211.6f;	fPos[1] = 15467.0f;	fAngle = 0.0f; break;
#endif //PJH_NEW_SERVER_SELECT_MAP
		}
		
#ifdef LDS_FIX_RESET_CHARACTERDELETED
		INT		iCharacterKey;
		iCharacterKey = Data->Index;
		DeleteCharacter( iCharacterKey );
#endif
		
		CreateHero(Data->Index,CharacterView.Class,CharacterView.Skin,fPos[0],fPos[1],fAngle);
		CharactersClient[Data->Index].Level = Data->Level;
		
		int iClass = ChangeServerClassTypeToClientClassType(Data->Class);
		
		CharactersClient[Data->Index].Class = iClass;
		memcpy(CharactersClient[Data->Index].ID,Data->ID,MAX_ID_SIZE);
		CharactersClient[Data->Index].ID[MAX_ID_SIZE] = NULL;
		CurrentProtocolState = RECEIVE_CREATE_CHARACTER_SUCCESS;
		CUIMng& rUIMng = CUIMng::Instance();
		rUIMng.CloseMsgWin();
		rUIMng.m_CharSelMainWin.UpdateDisplay();
		rUIMng.m_CharInfoBalloonMng.UpdateDisplay();
	}
	else if(Data->Result==0)	
		CUIMng::Instance().PopUpMsgWin(RECEIVE_CREATE_CHARACTER_FAIL);
	else if(Data->Result==2)
		CUIMng::Instance().PopUpMsgWin(RECEIVE_CREATE_CHARACTER_FAIL2);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x01����[ReceiveCreateCharacter]");
#endif // CONSOLE_DEBUG
}

// ĳ���;����� ĳ���� ���� ��û�� ���� ����.
void ReceiveDeleteCharacter( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
	switch (Data->Value)
	{
	case 1:	// ���� ����.
#ifdef LDS_FIX_RESET_CHARACTERDELETED		// ���� �ɸ��� �����ÿ� ���� Ŭ���̾�Ʈ �� �ش� �ɸ��� ���� �ʱ�ȭ�� ���ݴϴ�.
		INT		iKey;
		iKey = CharactersClient[SelectedHero].Key;
		DeleteCharacter( iKey );
#endif
		CUIMng::Instance().PopUpMsgWin(MESSAGE_DELETE_CHARACTER_SUCCESS);
		break;
	case 0:	// ��� ���� �Ұ��� ����
		CUIMng::Instance().PopUpMsgWin(MESSAGE_DELETE_CHARACTER_GUILDWARNING);
		break;
	case 3:	// ������ ���� ĳ����
		CUIMng::Instance().PopUpMsgWin(MESSAGE_DELETE_CHARACTER_ITEM_BLOCK);
		break;
	case 2:	// �ֹι�ȣ Ʋ��
	default:
		CUIMng::Instance().PopUpMsgWin(MESSAGE_STORAGE_RESIDENTWRONG);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// �α׾ƿ�
///////////////////////////////////////////////////////////////////////////////

int SummonLife = 0;

extern void StopMusic();

void InitGame()
{
	
	EnableUse = 0;
	SendGetItem = -1;
	SummonLife = 0;
	SoccerTime = 0;
	SoccerObserver = false;

	g_wtMatchResult.Clear();
	g_wtMatchTimeLeft.m_Time = 0;
	g_iGoalEffect = 0;
	
    g_shCameraLevel = 0;
	
	SelectedNpc = -1;
	SelectedOperate = -1;
	SelectedCharacter = -1;
	SelectedItem = -1;
	
	Attacking = -1;
	g_pOption->SetAutoAttack(true);
	g_pOption->SetWhisperSound(false);
	
	CheckInventory = NULL;
	
	//World = -1;
	
	SendExitInventory ();		// �� �̰� ������ �������� Ȯ���� ��.
	
	g_iFollowCharacter = -1;
	
	LockInputStatus = false;
	
	//  ����.
	RepairEnable = 0;
	CheckSkill = -1;
	
	//  ���� �ʱ�ȭ.
	ClearNotice ();
	
	//  �� ȿ�� �ʱ�ȭ.

	CharacterAttribute->Ability = 0;
	CharacterAttribute->AbilityTime[0] = 0;
	CharacterAttribute->AbilityTime[1] = 0;
	CharacterAttribute->AbilityTime[2] = 0;
	
#ifdef KJH_FIX_WOPS_K27340_INIT_STORAGE_GOLD
	// â��/���� �ݾ� �ʱ�ȭ
	CharacterMachine->StorageGold	= 0;
	CharacterMachine->Gold			= 0;
#endif // KJH_FIX_WOPS_K27340_INIT_STORAGE_GOLD

	
	g_shEventChipCount = 0;          //  ��������.
	g_shMutoNumber[0]  = -1;
	g_shMutoNumber[1]  = -1;
	g_shMutoNumber[2]  = -1;
	
	ClearWhisperID ();
	
    matchEvent::ClearMatchInfo();
	
	//  ��Ƽ ���� �ʱ�ȭ.
	InitPartyList();
	
	g_csQuest.clearQuest ();

#ifdef YDG_ADD_NEW_DUEL_SYSTEM
	g_DuelMgr.Reset();
#else	// YDG_ADD_NEW_DUEL_SYSTEM
	ClearDuelWindow();
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
	g_pNewUISystem->Hide( SEASON3B::INTERFACE_DUEL_WINDOW );
	
	// UI �Ŵ��� �ʱ�ȭ
	if( g_pUIManager )
		g_pUIManager->Init();
	
	if( g_pSiegeWarfare )
		g_pSiegeWarfare->InitMiniMapUI();
	
	g_Direction.Init();
	g_Direction.DeleteMonster();
	
	RemoveAllPerosnalItemPrice(PSHOPWNDTYPE_SALE);
	RemoveAllPerosnalItemPrice(PSHOPWNDTYPE_PURCHASE);
	
	g_pNewUIHotKey->SetStateGameOver(false);	
	
	// ���λ��� ���� �ʱ�ȭ
	g_pMyShopInventory->ResetSubject();
	g_pChatListBox->ResetFilter();

#ifdef CSK_FIX_WOPS_K30866_GUILDNOTICE
	g_pGuildInfoWindow->NoticeClear();
#endif // CSK_FIX_WOPS_K30866_GUILDNOTICE
}

BOOL ReceiveLogOut(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	LogOut = false;
	LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:
		SendMessage(g_hWnd, WM_DESTROY, 0, 0);
		break;
	case 1://�ɸ�â
		if ( !bEncrypted)
		{
			GO_DEBUG;
			SendHackingChecked( 0x00, 0xF1);
			return ( FALSE);
		}
		StopMusic();
        AllStopSound();
		
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
		
		ReleaseMainData();
		CryWolfMVPInit();
		
		SceneFlag = CHARACTER_SCENE;
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		SendRequestCharactersList(g_pMultiLanguage->GetLanguage());
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		SendRequestCharactersList();
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
								
		InitCharacterScene = false;
        InitMainScene = false;
        EnableMainRender = false;
		CurrentProtocolState = REQUEST_JOIN_SERVER;
		InitGame();
		break;
	case 2://���� ����â
		if(SceneFlag == MAIN_SCENE)
		{
			CryWolfMVPInit();
			StopMusic();
            AllStopSound();
			SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
			ReleaseMainData();
		}
		
		if ( !bEncrypted)
		{
			GO_DEBUG;
			SendHackingChecked( 0x00, 0xF1);
			return ( FALSE);
		}
		g_ErrorReport.Write("[ReceiveLogOut]");
		SocketClient.Close();
		ReleaseCharacterSceneData();
		SceneFlag = LOG_IN_SCENE;
								
		InitLogIn = false;
		InitCharacterScene = false;
        InitMainScene = false;
        EnableMainRender = false;
		CurrentProtocolState = REQUEST_JOIN_SERVER;
		
        LogIn = 0;
        g_csMapServer.Init ();
		InitGame();
		break;
	}
	
#ifdef PSW_BUGFIX_FRIEND_LIST_CLEAR
	g_pWindowMgr->Reset();
	g_pFriendList->ClearFriendList();
	g_pLetterList->ClearLetterList();
#endif //PSW_BUGFIX_FRIEND_LIST_CLEAR
	
#ifdef NEW_USER_INTERFACE_SHELL
	TheShopServerProxy().ShopReset( true );
#endif //NEW_USER_INTERFACE_SHELL
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x02����[ReceiveServerList(%d)]", Data->Value);
#endif // CONSOLE_DEBUG
	
	return ( TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// ����, �ٽ� ��Ƴ���
///////////////////////////////////////////////////////////////////////////////

int HeroIndex;

BOOL ReceiveJoinMapServer(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0xF3);
		return ( FALSE);
	}
	MouseLButton = false;
	
#ifdef PJH_DEBUG
	char Text[300];
	wsprintf(Text,"���̵�����(join)[time : %d]", GetTickCount());
	g_pChatListBox->AddText("DEBUG",Text, SEASON3B::TYPE_GM_MESSAGE);
#endif

	LPPRECEIVE_JOIN_MAP_SERVER Data = (LPPRECEIVE_JOIN_MAP_SERVER)ReceiveBuffer;
	

	__int64 Data_Exp = 0x0000000000000000;
	Master_Level_Data.lMasterLevel_Experince = 0x0000000000000000;
	Data_Exp |= Data->btMExp1;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp2;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp3;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp4;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp5;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp6;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp7;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp8;
	
	if(IsMasterLevel(CharacterAttribute->Class) == true)
	{
		Master_Level_Data.lMasterLevel_Experince = Data_Exp;
	}
	else
	{
		CharacterAttribute->Experience = (int)Data_Exp;
	}
	
	// ���� ���� ����ġ
	Data_Exp = 0x0000000000000000;
	Master_Level_Data.lNext_MasterLevel_Experince = 0x0000000000000000;
	
	Data_Exp |= Data->btMNextExp1;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp2;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp3;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp4;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp5;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp6;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp7;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMNextExp8;
	
	if(IsMasterLevel(CharacterAttribute->Class) == true)
	{
		Master_Level_Data.lNext_MasterLevel_Experince = Data_Exp;
	}
	else
	{
		CharacterAttribute->NextExperince = (int)Data_Exp;
	}
	
	//	Master_Level_Data.wMaxLife			= Data->LifeMax;
	//	Master_Level_Data.wMaxMana			= Data->ManaMax;
	//	Master_Level_Data.wMaxShield		= Data->ShieldMax;

	CharacterAttribute->LevelUpPoint  = Data->LevelUpPoint;
	CharacterAttribute->Strength      = Data->Strength;
	CharacterAttribute->Dexterity     = Data->Dexterity;
	CharacterAttribute->Vitality      = Data->Vitality;
	CharacterAttribute->Energy        = Data->Energy;
    CharacterAttribute->Charisma      = Data->Charisma;
	CharacterAttribute->Life          = Data->Life;
	CharacterAttribute->LifeMax       = Data->LifeMax;
	CharacterAttribute->Mana          = Data->Mana;
	CharacterAttribute->ManaMax       = Data->ManaMax;
	CharacterAttribute->SkillMana     = Data->SkillMana;
	CharacterAttribute->SkillManaMax  = Data->SkillManaMax;
	CharacterAttribute->Ability		  = 0;
	CharacterAttribute->AbilityTime[0]= 0;
	CharacterAttribute->AbilityTime[1]= 0;
	CharacterAttribute->AbilityTime[2]= 0;
	CharacterAttribute->Shield		  = Data->Shield;
	CharacterAttribute->ShieldMax	  = Data->ShieldMax;
	
    //  �߰��Ǵ� ���� ����.
    CharacterAttribute->AddPoint		= Data->AddPoint;
    CharacterAttribute->MaxAddPoint		= Data->MaxAddPoint;
	// ���̳ʽ� ���� ����
	CharacterAttribute->wMinusPoint     = Data->wMinusPoint;
    CharacterAttribute->wMaxMinusPoint  = Data->wMaxMinusPoint;
	
	CharacterMachine->Gold            = Data->Gold;
	//CharacterAttribute->SkillMana     = CharacterAttribute->Energy*10+CharacterAttribute->ManaMax*10/6;

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int iPreWorld = World;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	World = Data->Map;
	OpenWorld(World);

#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
	g_bReponsedMoveMapFromServer = TRUE;		// ���̵� ���� ����ε�OK
	LoadingWorld = 30;
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
	
	if(World == WD_34CRYWOLF_1ST)
	{
		SendRequestCrywolfInfo();
	}
	
    matchEvent::CreateEventMatch ( World );
	
	HeroIndex = rand()%MAX_CHARACTERS_CLIENT;
	CHARACTER *c = &CharactersClient[HeroIndex];
	CreateCharacterPointer(c,MODEL_PLAYER,Data->PositionX,Data->PositionY,((float)Data->Angle-1.f)*45.f);
	c->Key = HeroKey;
	
    OBJECT *o = &c->Object;
	c->Class = CharacterAttribute->Class;
	c->Skin = 0;
	c->PK    = Data->PK;
	c->CtlCode	= Data->CtlCode;
	o->Kind  = KIND_PLAYER;
   	SetCharacterClass(c);
#ifdef PK_ATTACK_TESTSERVER_LOG
	PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG

#ifdef LEM_FIX_AUTOSKILLBAR_SAVE
	if( !g_bExit )	c->CurrentSkill = Hero->CurrentSkill;
	else	g_bExit = false;
#endif	//  [lem_2010.8.18]
	Hero = c;

#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
	g_PKSystem->SetHeroPKState(Hero->PK);
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
	g_PKSystem->SetHeroPartyPKState(Hero->PKPartyLevel);
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER

	memcpy(c->ID,(char *)CharacterAttribute->Name,MAX_ID_SIZE);
    //  �ʱ�ȭ.
    for ( int i=0; i<MAX_EQUIPMENT; ++i )
    {
        CharacterMachine->Equipment[i].Type = -1;
        CharacterMachine->Equipment[i].Level = 0;
        CharacterMachine->Equipment[i].Option1 = 0;
    }
	c->ID[MAX_ID_SIZE] = NULL;
	CreateEffect(BITMAP_MAGIC+2,o->Position,o->Angle,o->Light,0,o);
	CurrentProtocolState = RECEIVE_JOIN_MAP_SERVER;
	
    LockInputStatus = false;
    CheckIME_Status(true,0);
	
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
	g_bReponsedMoveMapFromServer = TRUE;		// ���̵� ���� ����ε�OK
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
    LoadingWorld = 30;
    MouseUpdateTime = 0;
    MouseUpdateTimeMax = 6;
#ifdef PET_SYSTEM
    CreatePetDarkSpirit_Now ( Hero );
#endif// PET_SYSTEM
    CreateEffect(BITMAP_MAGIC+2,o->Position,o->Angle,o->Light,0,o);
    o->Alpha = 0.f;
	
	g_pNewUISystem->HideAll();
    
    //  �ʱ�ȭ.
    SelectedItem      = -1;
    SelectedNpc       = -1;
    SelectedCharacter = -1;
    SelectedOperate   = -1;
    Attacking         = -1;
    
    //  ����.
    RepairEnable = 0;
   
    Hero->Movement = false;
    SetPlayerStop(Hero);
	
    //  ���� ĳ���� ������ �����Ѵ�.
    if ( InBloodCastle() == false )
    {
        StopBuffer ( SOUND_BLOODCASTLE, true );
    }
	
    if ( InChaosCastle() == false )
    {
        StopBuffer ( SOUND_CHAOSCASTLE, true );
        StopBuffer ( SOUND_CHAOS_ENVIR, true );
    }
	
#ifdef LDS_ADD_EMPIRE_GUARDIAN
	if( IsEmpireGuardian1() == false &&
		IsEmpireGuardian2() == false &&
		IsEmpireGuardian3() == false &&
		IsEmpireGuardian4() == false )
	{
		StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_RAIN, true);
		StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_FOG, true);
		StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_STORM, true);
		StopBuffer(SOUND_EMPIREGUARDIAN_INDOOR_SOUND, true);
	}
#endif //LDS_ADD_EMPIRE_GUARDIAN

#if defined RESOURCE_GUARD && !defined FOR_WORK

#ifdef KJH_MOD_RESOURCE_GUARD
	char szModuleFileName[256];
	ResourceGuard::CResourceGuard RG101;
	CMuRGReport MuRGReport;
	RG101.AddReportObj(&MuRGReport);
#ifdef _TEST_SERVER
	sprintf(szModuleFileName, "data\\local\\Gameguardtest.csr");
#else  // _TEST_SERVER
	sprintf(szModuleFileName, "data\\local\\Gameguard.csr");
#endif // _TEST_SERVER
	if(!RG101.CheckIntegrityResourceChecksumFile(szModuleFileName))
	{
		SocketClient.Close();
		g_ErrorReport.Write("> ResourceGuard Error!!\r\n");
		return FALSE;
	}
#else // KJH_MOD_RESOURCE_GUARD
	char szModuleFileName[256];
	GetModuleFileName(NULL, szModuleFileName, 256);
	ResourceGuard::CResourceGuard RG101;
	CMuRGReport MuRGReport;
	RG101.AddReportObj(&MuRGReport);
	if(!RG101.CheckIntegrityPEFile(szModuleFileName))
	//if(!RG101.CheckIntegrity(szModuleFileName))			// CheckIntegrityPEFile()�� ����
	{
		SocketClient.Close();
		g_ErrorReport.Write("> ResourceGuard Error!!(%s)\r\n", szModuleFileName);
		return FALSE;
	}
#endif // KJH_MOD_RESOURCE_GUARD
#endif // RESOURCE_GUARD && FOR_WORK

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
#ifndef ASG_FIX_QUEST_PROTOCOL_ADD
	g_QuestMng.SetQuestIndexByEtcList(NULL, 0);	// ��Ÿ ��Ȳ�� ���� ����Ʈ ����Ʈ �ʱ�ȭ.
	SendRequestProgressQuestList();	// �������� ����Ʈ ����Ʈ ��û.
#endif	// ASG_FIX_QUEST_PROTOCOL_ADD
#endif	// ASG_ADD_NEW_QUEST_SYSTEM

	g_pUIMapName->ShowMapName();

#ifdef ASG_ADD_INFLUENCE_GROUND_EFFECT
	CreateMyGensInfluenceGroundEffect();
#endif	// ASG_ADD_INFLUENCE_GROUND_EFFECT
		
#ifdef YDG_ADD_DOPPELGANGER_EVENT
		if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4);
	else
#endif	// YDG_ADD_DOPPELGANGER_EVENT
	{
		//�ؽ�Ʈ ǥ�úκ� �߰�
		char Text[256];
		// 484 "�� ���Ű��� ȯ���մϴ�."
		
#ifndef GRAMMAR_VERB
		sprintf(Text,"%s%s",GetMapName( World),GlobalText[484]);
#else //GRAMMAR_VERB
		sprintf(Text,"%s%s",GlobalText[484],GetMapName( World));
#endif //GRAMMAR_VERB
		
		g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
	}
	
	if( World == WD_30BATTLECASTLE )
	{
		if( g_pSiegeWarfare )
			g_pSiegeWarfare->CreateMiniMapUI();
	}
	
#ifdef YDG_ADD_DOPPELGANGER_EVENT
	if( World < WD_65DOPPLEGANGER1 || World > WD_68DOPPLEGANGER4 )
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_DOPPELGANGER_FRAME);
	}
#endif	// YDG_ADD_DOPPELGANGER_EVENT

#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
	if( World < WD_69EMPIREGUARDIAN1 || WD_72EMPIREGUARDIAN4 < World)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER);
	}
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x03����[ReceiveJoinMapServer]");
#endif // CONSOLE_DEBUG
	
#ifdef PJH_DEBUG
	wsprintf(Text,"�ʷε��Ϸ�(join)[time : %d]", GetTickCount());
	g_pChatListBox->AddText("DEBUG",Text, SEASON3B::TYPE_GM_MESSAGE);
#endif
	return ( TRUE);
}

void ReceiveRevival( BYTE *ReceiveBuffer )
{
	MouseLButton = false;
	Teleport = false;
	Hero->Object.Live = false;
	LPPRECEIVE_REVIVAL Data = (LPPRECEIVE_REVIVAL)ReceiveBuffer;
	
	CharacterAttribute->Life       = Data->Life;
	CharacterAttribute->Mana       = Data->Mana;
	CharacterAttribute->Shield	   = Data->Shield;
	CharacterAttribute->SkillMana  = Data->SkillMana;

	__int64 Data_Exp = 0x0000000000000000;
	Master_Level_Data.lMasterLevel_Experince = 0x0000000000000000;
	Data_Exp |= Data->btMExp1;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp2;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp3;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp4;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp5;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp6;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp7;	
	Data_Exp <<= 8;
	Data_Exp |= Data->btMExp8;
	
	
	if(IsMasterLevel(Hero->Class) == true)
	{
		Master_Level_Data.lMasterLevel_Experince = Data_Exp;
	}
	else
	{
		CharacterAttribute->Experience = (int)Data_Exp;
	}
	
	CharacterMachine->Gold         = Data->Gold;
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
	{
		CHARACTER *c = &CharactersClient[i];
		c->Object.Live = false;
	}
	
	BYTE Temp = Hero->PK;
	int TempGuild = Hero->GuildMarkIndex;
	
	CHARACTER *c = &CharactersClient[HeroIndex];
	// ������� ���
	BYTE BackUpGuildStatus = c->GuildStatus;
	BYTE BackUpGuildType = c->GuildType;
	BYTE BackUpGuildRelationShip = c->GuildRelationShip;
	BYTE byBackupEtcPart = c->EtcPart;
	
	CreateCharacterPointer(c,MODEL_PLAYER,Data->PositionX,Data->PositionY,((float)Data->Angle-1.f)*45.f);
	c->Key = HeroKey;
	c->GuildStatus = BackUpGuildStatus;
	c->GuildType = BackUpGuildType;
	c->GuildRelationShip = BackUpGuildRelationShip;
	c->EtcPart = byBackupEtcPart;
	
	OBJECT *o = &c->Object;
	c->Class    = CharacterAttribute->Class;
	c->Skin = 0;
	c->PK       = Temp;
	o->Kind     = KIND_PLAYER;
	c->GuildMarkIndex = TempGuild;
	c->SafeZone = true;
	SetCharacterClass(c);
	
#ifdef PK_ATTACK_TESTSERVER_LOG
	PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG
	
	SetPlayerStop(c);
	CreateEffect(BITMAP_MAGIC+2,o->Position,o->Angle,o->Light,0,o);
    ClearItems();
	ClearCharacters(HeroKey);
	RemoveAllShopTitleExceptHero();
	
	if( World >= WD_45CURSEDTEMPLE_LV1 && World <= WD_45CURSEDTEMPLE_LV6 )
	{
		if( !(Data->Map >= WD_45CURSEDTEMPLE_LV1 && Data->Map <= WD_45CURSEDTEMPLE_LV6) )
		{
			g_CursedTemple->ResetCursedTemple();
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_CURSEDTEMPLE_GAMESYSTEM);
		}
	}
	
    if(World != Data->Map)
	{
        int OldWorld = World;
		
		World = Data->Map;
		OpenWorld(World);

#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		g_bReponsedMoveMapFromServer = TRUE;		// ��Ȱ �Ѱ�� ����ε�OK
		LoadingWorld = 30;
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		
        if ( ( InChaosCastle( OldWorld ) == true && OldWorld!=World ) 
			|| InChaosCastle() == true )
        {
            SetCharacterClass ( Hero );
        }
		
        if ( InChaosCastle() == false )
        {
            StopBuffer ( SOUND_CHAOSCASTLE, true );
            StopBuffer ( SOUND_CHAOS_ENVIR, true );
		}

#ifdef LDS_ADD_EMPIRE_GUARDIAN
		if( IsEmpireGuardian1() == false &&
			IsEmpireGuardian2() == false &&
			IsEmpireGuardian3() == false &&
			IsEmpireGuardian4() == false )
		{
			StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_RAIN, true);
			StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_FOG, true);
			StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_STORM, true);
			StopBuffer(SOUND_EMPIREGUARDIAN_INDOOR_SOUND, true);
		}
#endif //LDS_ADD_EMPIRE_GUARDIAN
		
        if ( World==-1 || c->Helper.Type!=MODEL_HELPER+3 || c->SafeZone )
        {
            o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
        }
        else
        {
            if ( World==WD_8TARKAN || World==WD_10HEAVEN )
                o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+90.f;
            else
                o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+30.f;
        }
	}
#ifdef PET_SYSTEM
    CreatePetDarkSpirit_Now ( c );
#endif// PET_SYSTEM
    SummonLife = 0;
	GuildTeam(c);
	
	g_pUIMapName->ShowMapName();	// rozy

#ifdef ASG_ADD_INFLUENCE_GROUND_EFFECT
	CreateMyGensInfluenceGroundEffect();
#endif	// ASG_ADD_INFLUENCE_GROUND_EFFECT
	
#ifdef YDG_ADD_DOPPELGANGER_EVENT
	if( World < WD_65DOPPLEGANGER1 || World > WD_68DOPPLEGANGER4 )
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_DOPPELGANGER_FRAME);
	}
#endif	// YDG_ADD_DOPPELGANGER_EVENT
#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
	if( World < WD_69EMPIREGUARDIAN1 || WD_72EMPIREGUARDIAN4 < World)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER);
	}
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS

	g_pNewUISystem->HideAll();
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x04����[ReceiveRevival]");
#endif // CONSOLE_DEBUG
	
}

///////////////////////////////////////////////////////////////////////////////
// ��������Ʈ, �ι��丮
///////////////////////////////////////////////////////////////////////////////

void ReceiveMagicList( BYTE *ReceiveBuffer )
{
#ifdef PJH_FIX_4_BUGFIX_33
	int Master_Skill_Bool = -1;
	int Skill_Bool = -1;
#endif //PJH_FIX_4_BUGFIX_33
	LPPHEADER_MAGIC_LIST_COUNT Data = (LPPHEADER_MAGIC_LIST_COUNT)ReceiveBuffer;
	int Offset = sizeof(PHEADER_MAGIC_LIST_COUNT);
	if(Data->Value == 0xFF)         //  �ϳ� ����.
	{	
		LPPRECEIVE_MAGIC_LIST Data2 = (LPPRECEIVE_MAGIC_LIST)(ReceiveBuffer+Offset);
		CharacterAttribute->Skill[Data2->Index] = 0;
	}
	else if(Data->Value == 0xFE)    //  �ϳ� �߰�.
	{
		LPPRECEIVE_MAGIC_LIST Data2 = (LPPRECEIVE_MAGIC_LIST)(ReceiveBuffer+Offset);
		CharacterAttribute->Skill[Data2->Index] = Data2->Type;
#ifdef USE_SKILL_LEVEL
		CharacterAttribute->SkillLevel[Data2->Index] = Data2->Level;
#endif
	}
    else if ( Data->ListType==0x02 )//  ���� ����Ʈ.
    {
        for ( int i=0; i<Data->Value; ++i )
        {
			LPPRECEIVE_MAGIC_LIST Data2 = (LPPRECEIVE_MAGIC_LIST)(ReceiveBuffer+Offset);
			CharacterAttribute->Skill[Data2->Index] = 0;
#ifdef USE_SKILL_LEVEL
			CharacterAttribute->SkillLevel[Data2->Index] = 0;
#endif
        }
    }
	else
	{	// ��ü ����Ʈ
#ifndef _VS2008PORTING			// #ifndef
		int i;
#endif // _VS2008PORTING
        if ( Data->ListType == 0x00 ) //  �߰����� ����Ʈ.
        {
			ZeroMemory( CharacterAttribute->Skill,  MAX_SKILLS * sizeof ( WORD));
        }
#ifdef _VS2008PORTING
		for(int i=0; i<Data->Value; i++)
#else // _VS2008PORTING
		for(i=0; i<Data->Value; i++)
#endif // _VS2008PORTING
		{
			LPPRECEIVE_MAGIC_LIST Data2 = (LPPRECEIVE_MAGIC_LIST)(ReceiveBuffer+Offset);
			CharacterAttribute->Skill[Data2->Index] = Data2->Type;
#ifdef USE_SKILL_LEVEL
			CharacterAttribute->SkillLevel[Data2->Index] = Data2->Level;
#endif
			Offset += sizeof(PRECEIVE_MAGIC_LIST);
		}
        if ( GetBaseClass( Hero->Class )==CLASS_DARK_LORD )
        {
#ifdef _VS2008PORTING
            for ( int i=0; i<PET_CMD_END; ++i )
#else // _VS2008PORTING
            for ( i=0; i<PET_CMD_END; ++i )
#endif // _VS2008PORTING
            {
                CharacterAttribute->Skill[AT_PET_COMMAND_DEFAULT+i] = AT_PET_COMMAND_DEFAULT+i;
#ifdef USE_SKILL_LEVEL
                CharacterAttribute->SkillLevel[AT_PET_COMMAND_DEFAULT+i] = Data2->Level;
#endif
            }
        }
	}
	
	CharacterAttribute->SkillNumber = 0;
	CharacterAttribute->SkillMasterNumber = 0;
	
    int SkillType = 0;
	for(int i=0;i<MAX_SKILLS;i++)
	{
		SkillType = CharacterAttribute->Skill[i];
		if ( SkillType!=0 )
		{
			CharacterAttribute->SkillNumber++;
            BYTE SkillUseType = SkillAttribute[SkillType].SkillUseType;
            if ( SkillUseType==SKILL_USE_TYPE_MASTER )
            {
				CharacterAttribute->SkillMasterNumber++;
            }
		}
	}
	if(Hero->CurrentSkill >= CharacterAttribute->SkillNumber)
		Hero->CurrentSkill = 0;
    if(CharacterAttribute->SkillNumber == 1)
		Hero->CurrentSkill = 0;
    if(Hero->CurrentSkill>=0 && CharacterAttribute->Skill[Hero->CurrentSkill]==0)
		Hero->CurrentSkill = 0;
	int Skill = 0;
#ifdef _VS2008PORTING
	for(int i = 0; i < MAX_SKILLS; i++)
#else // _VS2008PORTING
	for(i = 0; i < MAX_SKILLS; i++)
#endif // _VS2008PORTING
	{
		Skill = CharacterAttribute->Skill[Hero->CurrentSkill];
		if ( Skill>= AT_SKILL_STUN && Skill<=AT_SKILL_REMOVAL_BUFF )
			Hero->CurrentSkill++;
		else
			break;
	}
#ifdef PJH_FIX_4_BUGFIX_33	
#ifdef _VS2008PORTING
	for(int i = 0; i < MAX_SKILLS; i++)
#else // _VS2008PORTING
	for(i = 0; i < MAX_SKILLS; i++)
#endif // _VS2008PORTING
	{
		Skill = CharacterAttribute->Skill[i];
		if((AT_SKILL_POWER_SLASH_UP <= Skill && AT_SKILL_POWER_SLASH_UP+4 >= Skill) || (AT_SKILL_MANY_ARROW_UP <= Skill && AT_SKILL_MANY_ARROW_UP+4 >= Skill))
		{
			Master_Skill_Bool = i;
		}
		if (AT_SKILL_ICE_BLADE == Skill || Skill == AT_SKILL_CROSSBOW)
		{
			Skill_Bool  = i;
		}
	}
	if(Master_Skill_Bool > -1 && Skill_Bool > -1)
		CharacterAttribute->Skill[Skill_Bool] = 0;
#endif //#ifdef PJH_FIX_4_BUGFIX_33
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x11����[ReceiveMagicList]");
#endif // CONSOLE_DEBUG
}

//-----------------------------------------------------------------------------------------------
// ReceiveInventory
BOOL ReceiveInventory(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_EQUIPMENT;i++)
#else // _VS2008PORTING
	int i;
	for(i=0;i<MAX_EQUIPMENT;i++)
#endif // _VS2008PORTING
	{
		CharacterMachine->Equipment[i].Type = -1;
		CharacterMachine->Equipment[i].Number = 0;
        CharacterMachine->Equipment[i].Option1 = 0; //  �߰� �ɼ�. ( �׼���Ʈ )
	}

	g_pMyInventory->UnequipAllItems();
	g_pMyInventory->DeleteAllItems();
	g_pMyShopInventory->DeleteAllItems();

	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0xF3);
		return ( FALSE);
	}
	
	LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer; //LPPHEADER_DEFAULT_SUBCODE_WORD 6byte
	int Offset = sizeof(PHEADER_DEFAULT_SUBCODE_WORD);
	DeleteBug(&Hero->Object);
#ifdef PET_SYSTEM
    giPetManager::DeletePet ( Hero );            
#endif// PET_SYSTEM
#ifdef LDK_ADD_NEW_PETPROCESS
	ThePetProcess().DeletePet( Hero );
#endif //LDK_ADD_NEW_PETPROCESS
#ifdef _VS2008PORTING
	for(int i=0;i<Data->Value;i++)
#else // _VS2008PORTING
	for(i=0;i<Data->Value;i++)
#endif // _VS2008PORTING
	{
		LPPRECEIVE_INVENTORY Data2 = (LPPRECEIVE_INVENTORY)(ReceiveBuffer+Offset); //LPPRECEIVE_INVENTORY 8byte
		
		SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
		int itemindex = Data2->Index;
		if(itemindex >= 0 && itemindex < MAX_EQUIPMENT_INDEX)
		{
			g_pMyInventory->EquipItem(itemindex, Data2->Item);
		}
		else if(itemindex >= MAX_EQUIPMENT_INDEX && itemindex < MAX_MY_INVENTORY_INDEX)
		{
			itemindex = itemindex - MAX_EQUIPMENT_INDEX;
			g_pMyInventory->InsertItem(itemindex, Data2->Item);
		}
		else if(itemindex >= (MAX_EQUIPMENT_INDEX + MAX_INVENTORY) && itemindex < MAX_MY_SHOP_INVENTORY_INDEX)
		{
			itemindex = itemindex - (MAX_EQUIPMENT_INDEX + MAX_INVENTORY);
			g_pMyShopInventory->InsertItem(itemindex, Data2->Item);
		}

		Offset += sizeof(PRECEIVE_INVENTORY);
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x10����[ReceiveInventory]");
#endif // CONSOLE_DEBUG
	
	return ( TRUE);
}

void ReceiveDeleteInventory( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
	if(Data->SubCode != 0xff)
	{
		int itemindex = Data->SubCode;
		if(itemindex >= 0 && itemindex < MAX_EQUIPMENT_INDEX)
		{
#ifdef LJH_FIX_BUG_NOT_REMOVED_PET_WITH_1_DUR_WHEN_PLAYER_KILLED
			SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
			ITEM* pEquippedItem = &CharacterMachine->Equipment[itemindex];

			if (pPickedItem && pPickedItem->GetItem()->lineal_pos == pEquippedItem->lineal_pos)
				SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
#endif //LJH_FIX_BUG_NOT_REMOVED_PET_WITH_1_DUR_WHEN_PLAYER_KILLED
			

			g_pMyInventory->UnequipItem(itemindex);
		}
		else if(itemindex >= MAX_EQUIPMENT_INDEX && itemindex < MAX_MY_INVENTORY_INDEX)
		{
			itemindex = itemindex - MAX_EQUIPMENT_INDEX;
			g_pMyInventory->DeleteItem(itemindex);
		}
		else if(itemindex >= (MAX_EQUIPMENT_INDEX + MAX_INVENTORY) && itemindex < MAX_MY_SHOP_INVENTORY_INDEX)
		{
			itemindex = itemindex - (MAX_EQUIPMENT_INDEX + MAX_INVENTORY);
			g_pMyShopInventory->DeleteItem(itemindex);
		}
	}
	
	if(Data->Value)
	{
		EnableUse = 0;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x28����[ReceiveDeleteInventory(%d %d)]", Data->SubCode, Data->Value);
#endif // CONSOLE_DEBUG
}

void ReceiveTradeInventory( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
	int Offset = sizeof(PHEADER_DEFAULT_SUBCODE_WORD);
#ifndef _VS2008PORTING			// #ifndef
	int i;
#endif // _VS2008PORTING
	if(Data->SubCode == 3)//�ͽ�â ���� ����
	{
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		PlayBuffer(SOUND_MIX01);
		PlayBuffer(SOUND_BREAK01);
		g_pMixInventory->DeleteAllItems();
	}
    else if ( Data->SubCode==5 )    //  ���û� ���� ����
    {
		g_pChatListBox->AddText( "", GlobalText[1208], SEASON3B::TYPE_ERROR_MESSAGE);
		PlayBuffer ( SOUND_MIX01 );
		PlayBuffer ( SOUND_BREAK01 );
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		g_pMixInventory->DeleteAllItems();
    }
	else
	{
#ifdef _VS2008PORTING
		for(int i=0;i<MAX_SHOP_INVENTORY;i++)
#else // _VS2008PORTING
		for(i=0;i<MAX_SHOP_INVENTORY;i++)
#endif // _VS2008PORTING
		{
			ShopInventory[i].Type = -1;
			ShopInventory[i].Number = 0;
		}
	}
#ifdef _VS2008PORTING
	for(int i=0;i<Data->Value;i++)
#else // _VS2008PORTING
	for(i=0;i<Data->Value;i++)
#endif // _VS2008PORTING
	{
		LPPRECEIVE_INVENTORY Data2 = (LPPRECEIVE_INVENTORY)(ReceiveBuffer+Offset);
		
		if(Data->SubCode == 3)//�ͽ�â
		{
			g_pMixInventory->InsertItem(Data2->Index, Data2->Item);
		}
        else if ( Data->SubCode==5 )
        {
			g_pMixInventory->InsertItem(Data2->Index, Data2->Item);
        }
		else//â��,����
		{
			// ����, â��� Data->SubCode == 0 �̴�.
			if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) == true)
			{
				g_pNPCShop->InsertItem(Data2->Index, Data2->Item);
			}
			else if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE))
			{
				g_pStorageInventory->InsertItem(Data2->Index, Data2->Item);
			}
		}
		
		Offset += sizeof(PRECEIVE_INVENTORY);
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x31����[ReceiveTradeInventory]");
#endif // CONSOLE_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
// ä��
///////////////////////////////////////////////////////////////////////////////

//int TestOld = 0;
//int TestNew = 0;

void ReceiveChat( BYTE *ReceiveBuffer )
{
	if(SceneFlag == LOG_IN_SCENE)
	{
		g_ErrorReport.Write ( "Send Request Server List.\r\n");
		// �α��� ������ ó������ ���� ������ ���� ����Ʈ �䱸.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
		SendRequestServerList2();
#else
		SendRequestServerList();
#endif // PKD_ADD_ENHANCED_ENCRYPTION
	}
	else
	{
		LPPCHATING Data = (LPPCHATING)ReceiveBuffer;
		
		char ID[MAX_ID_SIZE+1];
		memset(ID, 0, MAX_ID_SIZE+1);
		memcpy(ID,(char *)Data->ID,MAX_ID_SIZE);
		
		char Text[MAX_CHAT_SIZE+1];
		memset(Text, 0, MAX_CHAT_SIZE+1);
		
		if(Data->ChatText[0]=='~'
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			|| Data->ChatText[0]==']'
#endif	// SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			)
		{
			for(int i=0;i<MAX_CHAT_SIZE-1;i++)
				Text[i] = Data->ChatText[i+1];
			g_pChatListBox->AddText(ID, Text, SEASON3B::TYPE_PARTY_MESSAGE);
		}
		else if(Data->ChatText[0]=='@' && Data->ChatText[1]=='@')
		{
			for(int i=0;i<MAX_CHAT_SIZE-2;i++)
				Text[i] = Data->ChatText[i+2];
			g_pChatListBox->AddText(ID, Text, SEASON3B::TYPE_UNION_MESSAGE);
		}
		else if(Data->ChatText[0]=='@')
		{
			for(int i=0;i<MAX_CHAT_SIZE-1;i++)
				Text[i] = Data->ChatText[i+1];
			g_pChatListBox->AddText(ID, Text, SEASON3B::TYPE_GUILD_MESSAGE);	
		}
		else if(Data->ChatText[0]=='#')
		{
			for(int i=0;i<MAX_CHAT_SIZE-1;i++)
				Text[i] = Data->ChatText[i+1];
		
			CHARACTER* pFindGm = NULL;
#ifdef _VS2008PORTING
			for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
			for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *o = &c->Object;
				if( o->Live && o->Kind==KIND_PLAYER && ( g_isCharacterBuff( (&c->Object), eBuff_GMEffect)
					|| (c->CtlCode == CTLCODE_20OPERATOR) || (c->CtlCode == CTLCODE_08OPERATOR) ) )
				{
					if(strcmp(c->ID,ID) == NULL)
					{
						pFindGm = c;
						break;
					}	
				}
			}
			if(pFindGm)
			{
				AssignChat(ID,Text);
				g_pChatListBox->AddText(ID,Text, SEASON3B::TYPE_GM_MESSAGE);
			}
			else
			{
				AssignChat(ID,Text,1);
			}
		}
        else
		{
			memcpy(Text,(char *)Data->ChatText,MAX_CHAT_SIZE);
			CHARACTER* pFindGm = NULL;
			for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *o = &c->Object;
				if( o->Live && o->Kind==KIND_PLAYER && g_isCharacterBuff((&c->Object), eBuff_GMEffect)
					|| (c->CtlCode == CTLCODE_20OPERATOR) || (c->CtlCode == CTLCODE_08OPERATOR) )
				{
					if(strcmp(c->ID,ID) == NULL)
					{
						pFindGm = c;
						break;
					}	
				}
			}
			if(pFindGm)
			{
				AssignChat(ID,Text);
				g_pChatListBox->AddText(ID, Text, SEASON3B::TYPE_GM_MESSAGE);
			}
			else
			{
				AssignChat(ID,Text);
				g_pChatListBox->AddText(ID, Text, SEASON3B::TYPE_CHAT_MESSAGE);	
			}
		}
	}
}

void ReceiveChatWhisper( BYTE *ReceiveBuffer )
{
	if(g_pChatInputBox->IsBlockWhisper() == true)
	{
		return;
	}
    
	LPPCHATING Data = (LPPCHATING)ReceiveBuffer;
	
	char ID[MAX_ID_SIZE+1];
	memset(ID, 0, MAX_ID_SIZE+1);
	memcpy(ID,(char *)Data->ID,MAX_ID_SIZE);
	
	char Text[MAX_CHAT_SIZE+1];
	memset(Text, 0, MAX_CHAT_SIZE+1);
	memcpy(Text,(char *)Data->ChatText,MAX_CHAT_SIZE);
	
    RegistWhisperID ( 10, ID );
	
	if(g_pOption->IsWhisperSound())
	{
		PlayBuffer(SOUND_WHISPER);
	}
	
	g_pChatListBox->AddText(ID,Text, SEASON3B::TYPE_WHISPER_MESSAGE);
}

void ReceiveChatWhisperResult( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:
        { 
#ifdef KJH_FIX_UI_CHAT_MESSAGE
			g_pChatListBox->AddText(ChatWhisperID,GlobalText[482], SEASON3B::TYPE_ERROR_MESSAGE, SEASON3B::TYPE_WHISPER_MESSAGE);
#else //KJH_FIX_UI_CHAT_MESSAGE	
			g_pChatListBox->AddText(ChatWhisperID,GlobalText[482], SEASON3B::TYPE_ERROR_MESSAGE);	 
#endif // KJH_FIX_UI_CHAT_MESSAGE
        }
	}
}

void ReceiveChatKey( BYTE *ReceiveBuffer )
{
	LPPCHATING_KEY Data = (LPPCHATING_KEY)ReceiveBuffer;
	int Key = ((int)(Data->KeyH)<<8) + Data->KeyL;
	int Index = FindCharacterIndex(Key);
	
	// for test
	if( Hero->GuildStatus == G_MASTER && !strcmp( CharactersClient[Index].ID, "��� ������" ) )
	{
		g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCGUILDMASTER);
		
		GuildInputEnable = true;
		InputEnable = false;
		ClearInput(FALSE);
		InputTextMax[0] = 8;
		InputNumber = 0;
		
		if( Hero->GuildMarkIndex == -1 )
			Hero->GuildMarkIndex = MARK_EDIT;
		return;
	}
	
	CreateChat(CharactersClient[Index].ID,(char *)Data->ChatText,&CharactersClient[Index]);
}

void ReceiveNotice( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_NOTICE Data = (LPPRECEIVE_NOTICE)ReceiveBuffer;
	if(Data->Result==0)
	{
		CreateNotice((char *)Data->Notice,0);
	}
	else if(Data->Result==1)
	{
		if(CHARACTER_SCENE != SceneFlag)
		{
			g_pChatListBox->AddText("", (char*)Data->Notice, SEASON3B::TYPE_SYSTEM_MESSAGE);
#ifdef CSK_FREE_TICKET
			// Į���� ���� ���� ���¿��� �� ����ϸ� �ƹ��͵� �ȵǴ� ���׶����� ó��
			EnableUse = 0;
#endif // CSK_FREE_TICKET
		}
		else
		{
			CUIMng& rUIMng = CUIMng::Instance();
			rUIMng.AddServerMsg((char*)Data->Notice);
		}
	}
	// ������
	else if(Data->Result==2)
	{
		char Text[100];
		sprintf(Text,GlobalText[483],(char *)Data->Notice);
		CreateNotice(Text,1);
		// ������ ���
		g_pGuildInfoWindow->AddGuildNotice((char*)Data->Notice);
	}
	else if (Data->Result >= 10 && Data->Result <= 15)
	{
		if (Data->Notice != NULL && Data->Notice[0] != '\0')
		{
			g_pSlideHelpMgr->AddSlide(Data->Count, Data->Delay, (char *)Data->Notice, Data->Result - 10, Data->Speed / 10.0f, Data->Color);
		}
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x0D����[ReceiveNotice(%s)]", Data->Notice);
#endif // CONSOLE_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
// �̵�
///////////////////////////////////////////////////////////////////////////////

void ReceiveMoveCharacter(BYTE *ReceiveBuffer,int Size)
{
	LPPMOVE_CHARACTER Data = (LPPMOVE_CHARACTER)ReceiveBuffer;
	int  Key = ((int)(Data->KeyH)<<8) + Data->KeyL;
    CHARACTER *c = &CharactersClient[FindCharacterIndex(Key)];

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	OBJECT *o = &c->Object;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	if(c->Dead==0)
	{
		OBJECT *o = &c->Object;
		c->TargetAngle = Data->Path[0]>>4;
		if(Key == HeroKey)
		{
			if(!c->Movement)
			{
				c->PositionX = Data->PositionX;
				c->PositionY = Data->PositionY;
			}
		}
		else
		{
			c->TargetX = Data->PositionX;
			c->TargetY = Data->PositionY;
			if(o->Type == MODEL_MONSTER01+52)	// �ߴ���
			{
				c->PositionX = Data->PositionX;
				c->PositionY = Data->PositionY;
				o->Angle[2] = CreateAngle(o->Position[0],o->Position[1],c->PositionX*100.f,c->PositionY*100.f);
				SetPlayerWalk( c);
				c->JumpTime = 1;
			}
			else if(c->Appear == 0)
			{
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
				int iDefaultWall = TW_CHARACTER;	//�����϶��� 2�̻��̸� ������ üũ

				if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4
					&& Key != HeroKey)
				{
					iDefaultWall = TW_NOMOVE;	// ���ð��� ���ʹ� ������ �հ���������
				}

				if(PathFinding2(c->PositionX, c->PositionY, c->TargetX, c->TargetY, &c->Path, 0.0f, iDefaultWall))
#else	// YDG_ADD_DOPPELGANGER_MONSTER
				if(PathFinding2(c->PositionX, c->PositionY, c->TargetX, c->TargetY, &c->Path))
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
				{
					c->Movement = true;
				}
				else
				{
					c->Movement = false;
					SetPlayerStop(c);
				}
			}

#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "ID : %s | sX : %d | sY : %d | tX : %d | tY : %d", c->ID, c->PositionX, c->PositionY, c->TargetX, c->TargetY);
#endif // CONSOLE_DEBUG
		}
	}
}

void ReceiveMovePosition( BYTE *ReceiveBuffer )
{
    LPPRECEIVE_MOVE_POSITION Data = (LPPRECEIVE_MOVE_POSITION)ReceiveBuffer;
	int Key = ((int)(Data->KeyH)<<8) + Data->KeyL;
	CHARACTER *c = &CharactersClient[FindCharacterIndex(Key)];
	
	OBJECT *o = &c->Object;
	if(o->Type == MODEL_BALL)
	{
		o->Gravity = 20.f;
		o->Direction[1] = (Data->PositionX-( c->PositionX))*400.f;
		o->Direction[0] = -(Data->PositionY-( c->PositionY))*400.f;
		PlayBuffer(SOUND_MENU01);
		CreateBomb(o->Position,false);
	}
	
	c->PositionX = Data->PositionX;
	c->PositionY = Data->PositionY;
	c->TargetX = Data->PositionX;
	c->TargetY = Data->PositionY;
	c->JumpTime = 1;
}

#ifdef USE_EVENT_ELDORADO
extern int EnableEvent;
#endif

BOOL ReceiveTeleport(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x1C);
		return ( FALSE);
	}
	
#ifdef PJH_DEBUG
	char Text[300];
	wsprintf(Text,"���̵�����(tel)[time : %d]", GetTickCount());
	g_pChatListBox->AddText("DEBUG",Text, SEASON3B::TYPE_GM_MESSAGE);
#endif
    //  ������ ���.
	SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	
	LPPRECEIVE_TELEPORT_POSITION Data = (LPPRECEIVE_TELEPORT_POSITION)ReceiveBuffer;
	Hero->PositionX = Data->PositionX;
	Hero->PositionY = Data->PositionY;
	
	// �и��� ����
	Hero->JumpTime = 0;
	
	OBJECT *o = &Hero->Object;
	o->Position[0] = ((float)(Hero->PositionX)+0.5f)*TERRAIN_SCALE;
	o->Position[1] = ((float)(Hero->PositionY)+0.5f)*TERRAIN_SCALE;
	
    if ( World==-1 || Hero->Helper.Type!=MODEL_HELPER+3 || Hero->SafeZone )
    {
        o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
    }
    else
    {
        if ( World==WD_8TARKAN || World==WD_10HEAVEN )
            o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+90.f;
        else
            o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+30.f;
    }
	
	if( World >= WD_45CURSEDTEMPLE_LV1 && World <= WD_45CURSEDTEMPLE_LV6 )
	{
		if( !(Data->Map >= WD_45CURSEDTEMPLE_LV1 && Data->Map <= WD_45CURSEDTEMPLE_LV6) )
		{
			g_CursedTemple->ResetCursedTemple();
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_CURSEDTEMPLE_GAMESYSTEM);
		}
	}
	
	int iEtcPart = Hero->EtcPart;
	
	o->Angle[2]    = ((float)(Data->Angle)-1.f)*45.f;
	if(Data->Flag == 0)
	{
        CreateTeleportEnd(o);
		Teleport = false;
	}
	else
	{
        ClearItems();
		ClearCharacters(HeroKey);
		RemoveAllShopTitleExceptHero();
		if(World != Data->Map)
		{
            int OldWorld = World;
			
			World = Data->Map;
			OpenWorld(World);
			
			if(World == WD_34CRYWOLF_1ST)
				SendRequestCrywolfInfo();
			
            if ( ( InChaosCastle(OldWorld) == true && OldWorld!=World ) || InChaosCastle()==true )
            {
                PlayBuffer( SOUND_CHAOS_ENVIR, NULL, true );
				
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_FRIEND);
				
                SetCharacterClass ( Hero );
				//ī���� ĳ�������� ���� ǥ�� ����
				DeleteBug(&Hero->Object);
            }
            if ( InChaosCastle()==false )
            {
                StopBuffer ( SOUND_CHAOSCASTLE, true );
                StopBuffer ( SOUND_CHAOS_ENVIR, true );
            }

#ifdef LDS_ADD_EMPIRE_GUARDIAN
			if( IsEmpireGuardian1() == false &&
				IsEmpireGuardian2() == false &&
				IsEmpireGuardian3() == false &&
				IsEmpireGuardian4() == false )
			{
				StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_RAIN, true);
				StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_FOG, true);
				StopBuffer(SOUND_EMPIREGUARDIAN_WEATHER_STORM, true);
				StopBuffer(SOUND_EMPIREGUARDIAN_INDOOR_SOUND, true);
			}
#endif //LDS_ADD_EMPIRE_GUARDIAN

            matchEvent::CreateEventMatch ( World );
			
            if ( World==-1 || Hero->Helper.Type!=MODEL_HELPER+3 || Hero->SafeZone )
            {
                o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
            }
            else
            {
                if ( World==WD_8TARKAN || World==WD_10HEAVEN )
                    o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+90.f;
                else
                    o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1])+30.f;
            }
			
#ifdef YDG_ADD_DOPPELGANGER_EVENT
			if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4);
			else
#endif	// YDG_ADD_DOPPELGANGER_EVENT
			{
				char Text[256];
#ifndef GRAMMAR_VERB
				sprintf(Text,"%s%s",GetMapName( World),GlobalText[484]);
#else //GRAMMAR_VERB
				sprintf(Text,"%s%s",GlobalText[484],GetMapName( World));
#endif //GRAMMAR_VERB
			
				g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
			}
		}
		SendRequestFinishLoading();

#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		g_bReponsedMoveMapFromServer = TRUE;			// �ڷ���Ʈ�� ���̵� �����̵�OK
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		LoadingWorld = 30;

		MouseUpdateTime = 0;
		MouseUpdateTimeMax = 6;
		
#ifdef YDG_ADD_DOPPELGANGER_EVENT
		if( World < WD_65DOPPLEGANGER1 || World > WD_68DOPPLEGANGER4 )
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_DOPPELGANGER_FRAME);
		}
#endif	// YDG_ADD_DOPPELGANGER_EVENT
#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
		if( World < WD_69EMPIREGUARDIAN1 || WD_72EMPIREGUARDIAN4 < World)
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER);
		}
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS

		g_pNewUISystem->HideAll();
		
#ifdef PET_SYSTEM
        CreatePetDarkSpirit_Now ( Hero );
#endif// PET_SYSTEM
		CreateEffect(BITMAP_MAGIC+2,o->Position,o->Angle,o->Light,0,o);
		o->Alpha = 0.f;
        EnableEvent = 0; //USE_EVENT_ELDORADO
		
        //  �ʱ�ȭ.
        SelectedItem      = -1;
        SelectedNpc       = -1;
        SelectedCharacter = -1;
        SelectedOperate   = -1;
        Attacking         = -1;
		
        //  ����.
        RepairEnable = 0;
    }
	
    Hero->Movement = false;
    SetPlayerStop(Hero);
	
	if(Data->Flag) 
		g_pUIMapName->ShowMapName();	// rozy

#ifdef ASG_ADD_INFLUENCE_GROUND_EFFECT
	CreateMyGensInfluenceGroundEffect();
#endif	// ASG_ADD_INFLUENCE_GROUND_EFFECT
	
	if( battleCastle::InBattleCastle() && battleCastle::IsBattleCastleStart() )
	{
		Hero->EtcPart = iEtcPart;
	}
	
#ifdef LJH_FIX_NOT_INITIALIZING_BATTLECASTLE_UI	
	if( World == WD_30BATTLECASTLE )
	{
		if( g_pSiegeWarfare )
			g_pSiegeWarfare->CreateMiniMapUI();
	} else 
	{
		g_pSiegeWarfare->InitMiniMapUI();
	}
#endif //LJH_FIX_NOT_INITIALIZING_BATTLECASTLE_UI

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x1C����[ReceiveTeleport(%d)]", Data->Flag);
#endif // CONSOLE_DEBUG
	
#ifdef PJH_DEBUG
	wsprintf(Text,"�ʷε��Ϸ�(tel)[time : %d]", GetTickCount());
	g_pChatListBox->AddText("DEBUG",Text, SEASON3B::TYPE_GM_MESSAGE);
#endif
	return ( TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ���, ����Ʈ
///////////////////////////////////////////////////////////////////////////////

void ReceiveEquipment( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_EQUIPMENT Data = (LPPRECEIVE_EQUIPMENT)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
	ChangeCharacterExt(FindCharacterIndex(Key),Data->Equipment);
}

//  ȭ����� ĳ���Ͱ� ��� ��ü������ ����� �ٲ�� ó��.
void ReceiveChangePlayer( BYTE *ReceiveBuffer )
{	
	LPPCHANGE_CHARACTER Data = (LPPCHANGE_CHARACTER)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
    CHARACTER *c = &CharactersClient[FindCharacterIndex(Key)];
	OBJECT *o = &c->Object;
	
	int Type = ConvertItemType(Data->Item); //  ������ ����.
	BYTE Level = Data->Item[1]&0xf;         //  ����.
    BYTE Option= Data->Item[3]&63;          //  �׼���Ʈ ������.
    BYTE ExtOption = Data->Item[4];         //  ��Ʈ �ɼ�.
	
    //  ��� ����.
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    int maxClass = MAX_CLASS;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	switch(Data->Item[1]>>4)
	{
	case 0:
		if(Type==0x1FFF)
        {
            c->Weapon[0].Type = -1;
            c->Weapon[0].Option1 = 0;
        }
		else
		{
			c->Weapon[0].Type = MODEL_ITEM + Type;
			c->Weapon[0].Level = LevelConvert(Level);
            c->Weapon[0].Option1 = Option;
		}
		break;
	case 1:
		if(Type==0x1FFF)
        {
            c->Weapon[1].Type = -1;
            c->Weapon[1].Option1 = 0;
#ifdef PET_SYSTEM
#ifdef KJH_FIX_JP0467_RENDER_DARKLOAD_PET_OTHER_CHARATER
            DeletePet ( c );            
#else // KJH_FIX_JP0467_RENDER_DARKLOAD_PET_OTHER_CHARATER
            DeletePet ( Hero );            
#endif // KJH_FIX_JP0467_RENDER_DARKLOAD_PET_OTHER_CHARATER
#endif// PET_SYSTEM
        }
		else
		{
			c->Weapon[1].Type = MODEL_ITEM + Type;
			c->Weapon[1].Level = LevelConvert(Level);
            c->Weapon[1].Option1 = Option;
#ifdef PET_SYSTEM
            CreatePetDarkSpirit_Now ( c );
#endif// PET_SYSTEM
			g_SummonSystem.RemoveEquipEffects( c );
		}
		break;
	case 2:
		if(Type==0x1FFF)
		{
			c->BodyPart[BODYPART_HELM].Type = MODEL_BODY_HELM+GetSkinModelIndex(c->Class);
			c->BodyPart[BODYPART_HELM].Level = 0;
			c->BodyPart[BODYPART_HELM].Option1 = 0;
			c->BodyPart[BODYPART_HELM].ExtOption = 0;
		}
		else
		{
			c->BodyPart[BODYPART_HELM].Type = MODEL_ITEM+Type;
			c->BodyPart[BODYPART_HELM].Level = LevelConvert(Level);
			c->BodyPart[BODYPART_HELM].Option1 = Option;
			c->BodyPart[BODYPART_HELM].ExtOption = ExtOption;
		}
		break;
	case 3:
		if(Type==0x1FFF)
		{
			c->BodyPart[BODYPART_ARMOR].Type = MODEL_BODY_ARMOR+GetSkinModelIndex(c->Class);
			c->BodyPart[BODYPART_ARMOR].Level = 0;
			c->BodyPart[BODYPART_ARMOR].Option1 = 0;
			c->BodyPart[BODYPART_ARMOR].ExtOption= 0;
		}
		else
		{
			c->BodyPart[BODYPART_ARMOR].Type = MODEL_ITEM+Type;
			c->BodyPart[BODYPART_ARMOR].Level = LevelConvert(Level);
			c->BodyPart[BODYPART_ARMOR].Option1 = Option;
			c->BodyPart[BODYPART_ARMOR].ExtOption= ExtOption;
		}
		break;
	case 4:
		if(Type==0x1FFF)
		{
			c->BodyPart[BODYPART_PANTS].Type = MODEL_BODY_PANTS+GetSkinModelIndex(c->Class);
			c->BodyPart[BODYPART_PANTS].Level = 0;
			c->BodyPart[BODYPART_PANTS].Option1 = 0;
			c->BodyPart[BODYPART_PANTS].ExtOption = 0;
		}
		else
		{
			c->BodyPart[BODYPART_PANTS].Type = MODEL_ITEM+Type;
			c->BodyPart[BODYPART_PANTS].Level = LevelConvert(Level);
			c->BodyPart[BODYPART_PANTS].Option1 = Option;
			c->BodyPart[BODYPART_PANTS].ExtOption = ExtOption;
		}
		break;
	case 5:
		if(Type==0x1FFF)
		{
			c->BodyPart[BODYPART_GLOVES].Type = MODEL_BODY_GLOVES+GetSkinModelIndex(c->Class);
			c->BodyPart[BODYPART_GLOVES].Level = 0;
			c->BodyPart[BODYPART_GLOVES].Option1 = 0;
			c->BodyPart[BODYPART_GLOVES].ExtOption = 0;
		}
		else
		{
			c->BodyPart[BODYPART_GLOVES].Type = MODEL_ITEM+Type;
			c->BodyPart[BODYPART_GLOVES].Level = LevelConvert(Level);
			c->BodyPart[BODYPART_GLOVES].Option1 = Option;
			c->BodyPart[BODYPART_GLOVES].ExtOption = ExtOption;
		}
		break;
	case 6:
		if(Type==0x1FFF)
		{
			c->BodyPart[BODYPART_BOOTS].Type = MODEL_BODY_BOOTS+GetSkinModelIndex(c->Class);
			c->BodyPart[BODYPART_BOOTS].Level = 0;
			c->BodyPart[BODYPART_BOOTS].Option1 = 0;
			c->BodyPart[BODYPART_BOOTS].ExtOption = 0;
		}
		else
		{
			c->BodyPart[BODYPART_BOOTS].Type = MODEL_ITEM+Type;
			c->BodyPart[BODYPART_BOOTS].Level = LevelConvert(Level);
			c->BodyPart[BODYPART_BOOTS].Option1 = Option;
			c->BodyPart[BODYPART_BOOTS].ExtOption = ExtOption;
		}
		break;
	case 7:
		if(Type==0x1FFF)
		{
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING
			if (c->Wing.Type == MODEL_WING+39 ||
				c->Wing.Type==MODEL_HELPER+30 ||
				c->Wing.Type==MODEL_WING+130 ||   // �߰�
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				c->Wing.Type == MODEL_WING+49 ||
				c->Wing.Type == MODEL_WING+50 ||
				c->Wing.Type == MODEL_WING+135||
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				c->Wing.Type==MODEL_WING+40)
#else //LDK_ADD_INGAMESHOP_SMALL_WING
			if (c->Wing.Type == MODEL_WING+39 || c->Wing.Type==MODEL_HELPER+30 || c->Wing.Type==MODEL_WING+40)
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
			{
				DeleteCloth(c, o);
			}
			c->Wing.Type = -1;
		}
		else
		{
			c->Wing.Type = MODEL_ITEM + Type;
			c->Wing.Level = 0;
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING
			if (c->Wing.Type == MODEL_WING+39 ||
				c->Wing.Type==MODEL_HELPER+30 ||
				c->Wing.Type==MODEL_WING+130 ||   // �߰�
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				c->Wing.Type == MODEL_WING+49 ||
				c->Wing.Type == MODEL_WING+50 ||
				c->Wing.Type == MODEL_WING+135||
#endif //PBG_ADD_NEWCHAR_MONK_ITEM				
				c->Wing.Type==MODEL_WING+40)
#else //LDK_ADD_INGAMESHOP_SMALL_WING
			if (c->Wing.Type == MODEL_WING+39 || c->Wing.Type==MODEL_HELPER+30 || c->Wing.Type==MODEL_WING+40)
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
			{
				DeleteCloth(c, o);
			}
		}
		break;
	case 8:
		if(Type==0x1FFF)
		{
			c->Helper.Type = -1;
			DeleteBug(o);
#ifdef LDK_ADD_NEW_PETPROCESS
			ThePetProcess().DeletePet(c, c->Helper.Type, true);
#endif //LDK_ADD_NEW_PETPROCESS

		}
		else
		{
			c->Helper.Type = MODEL_ITEM + Type;
			//c->Helper.Level = LevelConvert(Level);
			c->Helper.Level = 0;
			switch(Type)
			{
			case ITEM_HELPER  :CreateBug(MODEL_HELPER  ,o->Position,o);break;
			case ITEM_HELPER+2:CreateBug(MODEL_UNICON  ,o->Position,o);break;
			case ITEM_HELPER+3:CreateBug(MODEL_PEGASUS, o->Position,o);break;
			case ITEM_HELPER+4:CreateBug(MODEL_DARK_HORSE ,o->Position,o);break;
			case ITEM_HELPER+37:	// �渱 ����	//^ �渱 �� ����
				c->Helper.Option1 = Option;
				if(Option == 0x01)
				{
					CreateBug(MODEL_FENRIR_BLACK, o->Position, o);
				}
				else if(Option == 0x02)
				{
					CreateBug(MODEL_FENRIR_BLUE, o->Position, o);
				}
				else if(Option == 0x04)
				{
					CreateBug(MODEL_FENRIR_GOLD, o->Position, o);
				}
				else
				{
					CreateBug(MODEL_FENRIR_RED, o->Position, o);
				}
				break;
#if defined(LDK_ADD_NEW_PETPROCESS) && defined(LDK_ADD_PC4_GUARDIAN)
			case ITEM_HELPER+64:
			case ITEM_HELPER+65:
				{
#if	SELECTED_LANGUAGE == LANGUAGE_JAPANESE
					if( CHARACTER_SCENE == SceneFlag || c == Hero )
#endif	//SELECTED_LANGUAGE == LANGUAGE_JAPANESE
					{
						ThePetProcess().CreatePet( Type, c->Helper.Type, o->Position, c );
					}
				}
				break;
#endif //defined(LDK_ADD_NEW_PETPROCESS) && defined(LDK_ADD_PC4_GUARDIAN) && (SELECTED_LANGUAGE != LANGUAGE_JAPANESE)
#if defined LDK_ADD_NEW_PETPROCESS && defined LDK_ADD_RUDOLPH_PET
			case ITEM_HELPER+67:ThePetProcess().CreatePet( Type, c->Helper.Type, o->Position, c );break;
#endif //defined LDK_ADD_NEW_PETPROCESS && defined LDK_ADD_RUDOLPH_PET
#if defined LDK_ADD_NEW_PETPROCESS && defined PJH_ADD_PANDA_PET
			case ITEM_HELPER+80:ThePetProcess().CreatePet( Type, c->Helper.Type, o->Position, c );break;
#endif //LDK_ADD_NEW_PETPROCESS && defined PJH_ADD_PANDA_PET
#if defined LDK_ADD_NEW_PETPROCESS && defined LDK_ADD_CS7_UNICORN_PET
			case ITEM_HELPER+106:ThePetProcess().CreatePet( Type, c->Helper.Type, o->Position, c );break;
#endif //defined LDK_ADD_NEW_PETPROCESS && defined LDK_ADD_CS7_UNICORN_PET
#if defined LDK_ADD_NEW_PETPROCESS && defined YDG_ADD_SKELETON_PET
			case ITEM_HELPER+123:ThePetProcess().CreatePet( Type, c->Helper.Type, o->Position, c );break;
#endif //defined LDK_ADD_NEW_PETPROCESS && defined YDG_ADD_SKELETON_PET
			}
		}
		break;
	}

    ChangeChaosCastleUnit ( c );
	
	SetCharacterScale(c);
}

void RegisterBuff( eBuffState buff, OBJECT* o, const int bufftime = 0 );

void UnRegisterBuff( eBuffState buff, OBJECT* o );

//  ȭ�鿡 ���� ĳ���͸� �����Ѵ�.
void ReceiveCreatePlayerViewport(BYTE *ReceiveBuffer,int Size)
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	
	for(int i=0;i<Data->Value;i++)
	{
		LPPCREATE_CHARACTER Data2 = (LPPCREATE_CHARACTER)(ReceiveBuffer+Offset);
		WORD Key = ((WORD)(Data2->KeyH)<<8) + Data2->KeyL;
		int CreateFlag = (Key>>15);
		Key &= 0x7FFF;
		
		char Temp[MAX_ID_SIZE+1];
		::memcpy(Temp, (char*)Data2->ID, MAX_ID_SIZE);
		Temp[MAX_ID_SIZE] = NULL;
        if(FindText(Temp, "webzen") == false)
		{
			// �ڷ���Ʈ�� ���� ĳ��������� ��� ������ ������ ���
			int Index;
			short BackUpGuildMarkIndex = -1; 
			BYTE BackUpGuildStatus = 0;
			BYTE BackUpGuildType = 0;
			BYTE BackUpGuildRelationShip = 0;
			BYTE BackUpGuildMasterKillCount = 0;
            BYTE  EtcPart = 0;
			// ctlcode ���
			BYTE BackupCtlcode = 0;
			
			if( (Data2->Class&0x07) == 1 )	// �����̵��̶��.
			{
				Index = FindCharacterIndex(Key);		// �ε����� ã�Ƽ� ����
				if( Index != MAX_CHARACTERS_CLIENT )	// �ε����� 400�� �ƴ϶��
				{
					BackUpGuildMarkIndex = CharactersClient[Index].GuildMarkIndex;
					BackUpGuildStatus = CharactersClient[Index].GuildStatus;
					BackUpGuildType = CharactersClient[Index].GuildType;
					BackUpGuildRelationShip = CharactersClient[Index].GuildRelationShip;
					EtcPart = CharactersClient[Index].EtcPart;
					BackUpGuildMasterKillCount = CharactersClient[Index].GuildMasterKillCount;
				}

				if(&CharactersClient[Index] == Hero)	// �ڱ� �ڽ��̸�
				{
					BackupCtlcode	= CharactersClient[Index].CtlCode;
				}
			}
			else	// �ٸ� Ŭ�������
			{
				Index = FindCharacterIndex(Key);
				if( Index != MAX_CHARACTERS_CLIENT )	// �ε����� 400�� �ƴ϶��
				{
					BackUpGuildMarkIndex = CharactersClient[Index].GuildMarkIndex;
					BackUpGuildStatus = CharactersClient[Index].GuildStatus;
					BackUpGuildType = CharactersClient[Index].GuildType;
					BackUpGuildRelationShip = CharactersClient[Index].GuildRelationShip;
					BackUpGuildMasterKillCount = CharactersClient[Index].GuildMasterKillCount;
					EtcPart = CharactersClient[Index].EtcPart;
				}
					
				if(&CharactersClient[Index] == Hero)	// �ڱ� �ڽ��̸�
				{
					BackupCtlcode	= CharactersClient[Index].CtlCode;
				}
			}
			
			// ĳ���� ���� ����
			CHARACTER *c = CreateCharacter(Key,MODEL_PLAYER,Data2->PositionX,Data2->PositionY,0);
			DeleteCloth(c, &c->Object);	// �ʰ� ���� ����
			
			OBJECT *o = &c->Object;
			c->Class = ChangeServerClassTypeToClientClassType(Data2->Class);
			c->Skin = 0;
			c->PK    = Data2->Path&0xf;		// Data2->Path���� 4����Ʈ�� PK����
			o->Kind  = KIND_PLAYER;
				
#ifdef PK_ATTACK_TESTSERVER_LOG
			PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG	
				
			switch (Data2->Class&0x07)
			{
			case 1:
				CreateTeleportEnd(o);
				AddDebugText(ReceiveBuffer,Size);
				break;
			case 2:
				if(!IsFemale(c->Class))
					SetAction(o,PLAYER_SIT1);
				else
					SetAction(o,PLAYER_SIT_FEMALE1);
				break;
			case 3:
				if(!IsFemale(c->Class))
					SetAction(o,PLAYER_POSE1);
				else
					SetAction(o,PLAYER_POSE_FEMALE1);
				break;
			case 4:
				if(!IsFemale(c->Class))
					SetAction(o,PLAYER_HEALING1);
				else
					SetAction(o,PLAYER_HEALING_FEMALE1);
				break;
			}

			// ��ġ, Ÿ��, ���� �Է�
			c->PositionX = Data2->PositionX;
			c->PositionY = Data2->PositionY;
#ifdef CSK_FIX_SYNCHRONIZATION
			c->TargetX = Data2->TargetX;
			c->TargetY = Data2->TargetY;
#else // CSK_FIX_SYNCHRONIZATION
			c->TargetX = Data2->PositionX;
			c->TargetY = Data2->PositionY;
#endif // CSK_FIX_SYNCHRONIZATION	
			
			c->Object.Angle[2] = ((float)(Data2->Path>>4)-1.f)*45.f;
			
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "(RCPV)ID : %s | sX : %d | sY : %d | tX : %d | tY : %d", c->ID, c->PositionX, c->PositionY, c->TargetX, c->TargetY);
#endif // CONSOLE_DEBUG
				
			if(CreateFlag)
			{
				c->Object.Position[0] = (( c->PositionX)+0.5f)*TERRAIN_SCALE;
				c->Object.Position[1] = (( c->PositionY)+0.5f)*TERRAIN_SCALE;
				CreateEffect(BITMAP_MAGIC+2,o->Position,o->Angle,o->Light,0,o);
				c->Object.Alpha = 0.f;
			}
			else if(PathFinding2(c->PositionX, c->PositionY, Data2->TargetX, Data2->TargetY, &c->Path))
			{
				c->Movement = true;
			}
			
			if ( InHellas() )
			{
				CreateJoint ( BITMAP_FLARE+1, o->Position, o->Position, o->Angle, 8, o, 20.f );
			}
#ifdef LJW_FIX_MANY_FLAG_DISAPPEARED_PROBREM // �����ϴ� ������ �ٲ�
			// �ڷ���Ʈ�� ���� ĳ��������� ��� ������ ������ ����
			if( (Data2->Class&0x07) == 1 && Index != MAX_CHARACTERS_CLIENT )
			{	
				c->GuildMarkIndex = BackUpGuildMarkIndex;
				c->GuildStatus = BackUpGuildStatus;
				c->GuildType = BackUpGuildType;
				c->GuildRelationShip = BackUpGuildRelationShip;
				c->EtcPart = EtcPart;
				c->GuildMasterKillCount = BackUpGuildMasterKillCount;
				
				if(&CharactersClient[Index] == Hero)
				{
					c->CtlCode = BackupCtlcode;
				}
			}
			else
			{
				c->GuildMarkIndex = BackUpGuildMarkIndex;
				c->GuildStatus = BackUpGuildStatus;
				c->GuildType = BackUpGuildType;
				c->GuildRelationShip = BackUpGuildRelationShip;
				c->GuildMasterKillCount = BackUpGuildMasterKillCount;
				c->EtcPart = EtcPart;						
				if(&CharactersClient[Index] == Hero)
				{
					c->CtlCode = BackupCtlcode;
				}
			}

			ChangeCharacterExt(FindCharacterIndex(Key),Data2->Equipment);
#else
			ChangeCharacterExt(FindCharacterIndex(Key),Data2->Equipment);
				
			// �ڷ���Ʈ�� ���� ĳ��������� ��� ������ ������ ����
			if( (Data2->Class&0x07) == 1 && Index != MAX_CHARACTERS_CLIENT )
			{	
				c->GuildMarkIndex = BackUpGuildMarkIndex;
				c->GuildStatus = BackUpGuildStatus;
				c->GuildType = BackUpGuildType;
				c->GuildRelationShip = BackUpGuildRelationShip;
				c->EtcPart = EtcPart;
				c->GuildMasterKillCount = BackUpGuildMasterKillCount;
						
				if(&CharactersClient[Index] == Hero)
				{
					c->CtlCode = BackupCtlcode;
				}
			}
			else
			{
				c->GuildMarkIndex = BackUpGuildMarkIndex;
				c->GuildStatus = BackUpGuildStatus;
				c->GuildType = BackUpGuildType;
				c->GuildRelationShip = BackUpGuildRelationShip;
				c->GuildMasterKillCount = BackUpGuildMasterKillCount;
				c->EtcPart = EtcPart;						
				if(&CharactersClient[Index] == Hero)
				{
					c->CtlCode = BackupCtlcode;
				}
			}
#endif
			
			memcpy(c->ID,(char *)Data2->ID,MAX_ID_SIZE);
			c->ID[MAX_ID_SIZE] = NULL;
					
			if ((Data2->Class&0x07) == 1 && Index != MAX_CHARACTERS_CLIENT)
			{
				c->EtcPart = EtcPart;
			}
						
			// ���� ���� ����
			for( int j = 0; j < Data2->s_BuffCount; ++j )
			{
				RegisterBuff(static_cast<eBuffState>(Data2->s_BuffEffectState[j]), o);

				battleCastle::SettingBattleFormation ( c, static_cast<eBuffState>(Data2->s_BuffEffectState[j]) );
#ifdef CONSOLE_DEBUG
				g_ConsoleDebug->Write(MCD_RECEIVE, "ID : %s, Buff : %d", c->ID, static_cast<int>(Data2->s_BuffEffectState[j]));
#endif // CONSOLE_DEBUG				
			}

			if( battleCastle::InBattleCastle() && battleCastle::IsBattleCastleStart() )
			{
				//g_pSiegeWarfare->InitSkillUI();
			}
        }
		
		Offset += (sizeof(PCREATE_CHARACTER)-(sizeof(BYTE)*(MAX_BUFF_SLOT_INDEX-Data2->s_BuffCount)));
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x12����[ReceiveCreatePlayerViewport(%d)]", Data->Value);
#endif // CONSOLE_DEBUG
}

// ���� ���� �����ϸ� �޴� ����
void ReceiveCreateTransformViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	
	for(int i=0;i<Data->Value;i++)
	{
		LPPCREATE_TRANSFORM Data2 = (LPPCREATE_TRANSFORM)(ReceiveBuffer+Offset);
		WORD Key = ((WORD)(Data2->KeyH)<<8) + Data2->KeyL;
		int CreateFlag = (Key>>15);
		Key &= 0x7FFF;
		
		char Temp[MAX_ID_SIZE+1];
		memcpy(Temp,(char *)Data2->ID,MAX_ID_SIZE);
		Temp[MAX_ID_SIZE] = NULL;
		
		CHARACTER *pCha;
		int iIndex = FindCharacterIndex(Key);
		pCha = &CharactersClient[iIndex];
		
		// ������ ���� ���
		short sBackUpGuildMarkIndex = -1; 
		BYTE byBackUpGuildStatus = 0;
		BYTE byBackUpGuildType = 0;
		BYTE byBackUpGuildRelationShip = 0;
		BYTE byBackUpGuildMasterKillCount = 0;
		BYTE byEtcPart = 0;
		BYTE byBackupCtlcode = 0;
		
		if(iIndex != MAX_CHARACTERS_CLIENT)
		{
			sBackUpGuildMarkIndex = pCha->GuildMarkIndex;
			byBackUpGuildStatus = pCha->GuildStatus;
			byBackUpGuildType = pCha->GuildType;
			byBackUpGuildRelationShip = pCha->GuildRelationShip;
			byBackUpGuildMasterKillCount = pCha->GuildMasterKillCount;
			byEtcPart = pCha->EtcPart;
			byBackupCtlcode = pCha->CtlCode;	
		}
		
        if(FindText(Temp, "webzen") == false)
		{
			// Ŭ���� �Է�
			int Class = ChangeServerClassTypeToClientClassType(Data2->Class);
            
			// ������ Ÿ��
            WORD Type = ((WORD)(Data2->TypeH)<<8) + Data2->TypeL;
			
			// ���� ����
			CHARACTER *c = CreateMonster(Type,Data2->PositionX,Data2->PositionY,Key);
			OBJECT *o = &c->Object;
			
			if(c->MonsterIndex == 7)	// ���̾�Ʈ
			{
				// ���� ���̾�Ʈ ���ʹ� �������� ū�� �� ���̾�Ʈ�� �����ϸ� ��������
				// �۰� ���������?
				o->Scale = 0.8f;
			}
			
			if(Type == 373)
			{
				DeleteCloth(c, o);
			}
			
			if( Type == 404 || Type == 405 )
			{
				DeleteCloth(c, o);
			}
			
			DeleteCloth(c, o);
			
			// ������ ���� ����
			c->GuildMarkIndex = sBackUpGuildMarkIndex;
			c->GuildStatus = byBackUpGuildStatus;
			c->GuildType = byBackUpGuildType;
			c->GuildRelationShip = byBackUpGuildRelationShip;
			c->GuildMasterKillCount = byBackUpGuildMasterKillCount;
			c->EtcPart = byEtcPart;
			c->CtlCode = byBackupCtlcode;
			c->Class  = Class;
			c->PK     = Data2->Path&0xf;
			o->Kind   = KIND_PLAYER;	// ������ �÷��̾�� ����
			c->Change = true;			// ���Ż��� true ����
			
#ifdef PK_ATTACK_TESTSERVER_LOG
			PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG	

			for( int j = 0; j < Data2->s_BuffCount; ++j )
			{
				RegisterBuff(static_cast<eBuffState>(Data2->s_BuffEffectState[j]), o);
				battleCastle::SettingBattleFormation ( c, static_cast<eBuffState>(Data2->s_BuffEffectState[j]) );
#ifdef CONSOLE_DEBUG
				g_ConsoleDebug->Write(MCD_RECEIVE, "ID : %s, Buff : %d", c->ID, static_cast<int>(Data2->s_BuffEffectState[j]));
#endif // CONSOLE_DEBUG	
			}
	
			c->PositionX = Data2->PositionX;
			c->PositionY = Data2->PositionY;
			c->TargetX = Data2->PositionX;
			c->TargetY = Data2->PositionY;
			c->Object.Angle[2] = ((float)(Data2->Path>>4)-1.f)*45.f;
			
			if(CreateFlag)
			{
				c->Object.Position[0] = (( c->PositionX)+0.5f)*TERRAIN_SCALE;
				c->Object.Position[1] = (( c->PositionY)+0.5f)*TERRAIN_SCALE;
				c->Object.Alpha = 0.f;
				CreateEffect(MODEL_MAGIC_CIRCLE1,o->Position,o->Angle,o->Light,0,o);
				CreateParticle(BITMAP_LIGHTNING+1,o->Position,o->Angle,o->Light,2,1.f,o);
			}
			else if(PathFinding2(( c->PositionX),( c->PositionY),Data2->TargetX,Data2->TargetY,&c->Path))
			{
				c->Movement = true;
			}
			
			// ���̵� �Է�
			memcpy(c->ID,(char *)Data2->ID,MAX_ID_SIZE);
			c->ID[MAX_ID_SIZE] = NULL;
			
			ChangeCharacterExt(FindCharacterIndex(Key), Data2->Equipment);
		}

		Offset += (sizeof(PCREATE_TRANSFORM)-(sizeof(BYTE)*(MAX_BUFF_SLOT_INDEX-Data2->s_BuffCount)));
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x45����[ReceiveCreateTransformViewport(%d)]", Data->Value);
#endif // CONSOLE_DEBUG
}

void AppearMonster(CHARACTER *c)
{
	OBJECT *o = &c->Object;
	switch(c->MonsterIndex)
	{
	case 44://�巡��
		SetAction(o,MONSTER01_STOP2);
		o->PriorAction = MONSTER01_STOP2;
		c->Object.Alpha = 1.f;
		PlayBuffer(SOUND_MONSTER+124);
		break;
	case 21://�ϻ���
		SetAction(o,MONSTER01_STOP2);
		o->PriorAction = MONSTER01_STOP2;
		c->Object.Alpha = 1.f;
		PlayBuffer(SOUND_ASSASSIN);
		break;
	case 53://���ϱ���
	case 54://���ϱ���
		c->Appear = 60;
		SetAction(o,MONSTER01_STOP2);
		o->PriorAction = MONSTER01_STOP2;
		c->Object.Alpha = 1.f;
		//PlayBuffer(SOUND_ASSASSIN);
		break;
	case 85 :	//. ��ũ�ü�����1
	case 91 :	//. ��ũ�ü�����2
	case 97 :	//. ��ũ�ü�����3
	case 114 :	//. ��ũ�ü�����4
	case 120 :	//. ��ũ�ü�����5
	case 126 :	//. ��ũ�ü�����6
		PlayBuffer(SOUND_MONSTER+161);
        break;
		// MVP �� ��ȯ �ɶ� ȿ��
	case 440:
	case 340:	// ��ũ����
	case 341:	// �Ҷ�
	case 344:	// �߶�
	case 345:	// ���� ���Ǹ�
		{
			if(g_Direction.m_CMVP.m_iCryWolfState == CRYWOLF_STATE_READY)
				c->Object.Alpha = 1.0f;
			else
			{
				c->Object.Alpha = 0.f;
				
				vec3_t vPos;
				Vector(c->Object.Position[0]+20.0f, c->Object.Position[1]+20.0f, c->Object.Position[2], vPos);
				
				// ���� ��ȯ ȿ�� - �ϴÿ��� ���� ��������
				CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 60.f+rand()%10 );
				CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 50.f+rand()%10 );
				CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 50.f+rand()%10 );
				CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 60.f+rand()%10 );
				
				// ���� ��ȯ ȿ�� - ���� ������ ������ ���� ����
				CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);
				CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);
				CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);
				
				// ���� ��ȯ ȿ�� - �� ��Ÿ ���鼭 ������ ���� ȿ��
				Vector(c->Object.Position[0], c->Object.Position[1], c->Object.Position[2]+120.0f, vPos);
				CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
				CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
				CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
				CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
			}
		}
		break;
	case 362:
	case 363:
		{
			SetAction(o,MONSTER01_APEAR);
			c->Object.Alpha = 0.f;
		}
		break;
	default:
		if(o->Type == MODEL_PLAYER)
		{
			SetAction(o,PLAYER_COME_UP);
			o->PriorAction = PLAYER_COME_UP;
			c->Object.Alpha = 1.f;
		}
		else
		{
			c->Object.Alpha = 0.f;
		}
		break;
	}
}

// ȭ�鿡 ���� ���͸� �����Ѵ�.
void ReceiveCreateMonsterViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for(int i=0;i<Data->Value;i++)
	{
		LPPCREATE_MONSTER Data2 = (LPPCREATE_MONSTER)(ReceiveBuffer+Offset);
		WORD Key       = ((WORD)(Data2->KeyH)<<8) + Data2->KeyL;
		
		
        BYTE bMyMob     = (Data2->TypeH)&0x80;
        BYTE byBuildTime= (Data2->TypeH&0x70)>>4;
        WORD Type       = ((WORD)(Data2->TypeH&0x03)<<8) + Data2->TypeL;

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		if(Type != 106)
			int a= 0;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		int CreateFlag = (Key>>15);
		// ���Ͱ� �����̵� �� ���ö� ȿ���� �ִ��� ������
		int TeleportFlag = (Data2->KeyH&0x40)>>6;
		
		Key &= 0x7FFF;
		CHARACTER *c = CreateMonster(Type,Data2->PositionX,Data2->PositionY,Key);
		
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_RECEIVE, "0x13����[ReceiveCreateMonsterViewport(Type : %d | Key : %d)]", Type, Key);
#endif // CONSOLE_DEBUG	
		
		if(c == NULL) break;

		OBJECT *o = &c->Object;

		for( int j = 0; j < Data2->s_BuffCount; ++j )
		{
			RegisterBuff(static_cast<eBuffState>(Data2->s_BuffEffectState[j]), o);

#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "ID : %s, Buff : %d", c->ID, static_cast<int>(Data2->s_BuffEffectState[j]));
#endif // CONSOLE_DEBUG	
		}
		
		float fAngle = 45.0f;
		if(o->Type == MODEL_MONSTER01+99)
		{
			if(c->PositionY == 90)
				fAngle = 0.0f;
			if(c->PositionX == 62)
				fAngle = -135.0f;
			if(c->PositionX == 183)
				fAngle = 90.0f;
		}
		else if(o->Type == MODEL_KANTURU2ND_ENTER_NPC)
		{
			o->m_fEdgeScale = 1.0f;
			fAngle = 90.f;
		}

		c->Object.Angle[2] = ((float)(Data2->Path>>4)-1.f)*fAngle;
#ifdef PBG_ADD_LITTLESANTA_NPC
		// ��Ʋ��Ÿ�� �ٶ󺸴� ������ Z�� 90.
		if(o->Type >= MODEL_LITTLESANTA+1 && o->Type <= MODEL_LITTLESANTA+4)
		{
			c->Object.Angle[2] = 90.f;
		}
		else if(o->Type >= MODEL_LITTLESANTA+6 && o->Type <= MODEL_LITTLESANTA+7)
		{
			c->Object.Angle[2] = 90.f;
		}
#endif //PBG_ADD_LITTLESANTA_NPC
#ifdef LDK_ADD_SANTA_NPC
		else if(o->Type == MODEL_XMAS2008_SANTA_NPC)
		{
			c->Object.Angle[2] = 20.f;
		}
#endif //LDK_ADD_SANTA_NPC		
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
		else if(o->Type == MODEL_UNITEDMARKETPLACE_JULIA)
		{
			//c->Object.Angle[2] = 44.0f;
			c->Object.Angle[2] = 49.0f;
			//c->Object.Angle[2] = 90.0f;
		}
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE

		c->PositionX = Data2->PositionX;
		c->PositionY = Data2->PositionY;
		c->TargetX = Data2->PositionX;
		c->TargetY = Data2->PositionY;
		
        c->m_byFriend = bMyMob;
        o->m_byBuildTime = byBuildTime;
		
        if ( battleCastle::InBattleCastle() && c->MonsterIndex==277 )        
        {
            //  State���� ���� �ൿ�� �����Ѵ�.
			if( g_isCharacterBuff((&c->Object), eBuff_CastleGateIsOpen) )	//  ������ �����ִ� ����.
			{
				SetAction ( &c->Object, 1 );
				battleCastle::SetCastleGate_Attribute ( Data2->PositionX, Data2->PositionY, 0 );
			}
			else														 //  ������ �����ִ� ����.
			{
				SetAction ( &c->Object, 0 );
				battleCastle::SetCastleGate_Attribute ( Data2->PositionX, Data2->PositionY, 1 );
			}
        }
		if(CreateFlag)
		{
            AppearMonster(c);
		}
		// ĭ����3�� ����Ʈ�޾������� ����Ʈ�޾� �����̵� �� ���ö� ȿ��
		else if(World == WD_39KANTURU_3RD && o->Type == MODEL_MONSTER01+121 && TeleportFlag)
		{
			vec3_t Light;
			Vector ( 1.0f, 1.0f, 1.0f, Light );
			o->AlphaTarget = 1.f;
			CreateEffect(BITMAP_SPARK+1,o->Position,o->Angle,Light);
			CreateEffect(BITMAP_SPARK+1,o->Position,o->Angle,Light);
			PlayBuffer(SOUND_KANTURU_3RD_NIGHTMARE_TELE);
		}
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		int iDefaultWall = TW_CHARACTER;	//�����϶��� 2�̻��̸� ������ üũ

		if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4
			&& Key != HeroKey)
		{
			iDefaultWall = TW_NOMOVE;	// ���ð��� ���ʹ� ������ �հ���������
		}

		else if(PathFinding2(c->PositionX, c->PositionY, Data2->TargetX, Data2->TargetY, &c->Path, 0.0f, iDefaultWall))
#else	// YDG_ADD_DOPPELGANGER_MONSTER
		else if(PathFinding2(c->PositionX, c->PositionY, Data2->TargetX, Data2->TargetY, &c->Path))
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		{
			c->Movement = true;
		}
#ifdef KJH_FIX_BTS167_MOVE_NPC_IN_VIEWPORT
		else
		{
			c->Movement = false;			// �ʱⰪ
		}
#endif // KJH_FIX_BTS167_MOVE_NPC_IN_VIEWPORT

		Offset += (sizeof(PCREATE_MONSTER)-(sizeof(BYTE)*(MAX_BUFF_SLOT_INDEX-Data2->s_BuffCount)));
	}
}

void ReceiveCreateSummonViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for(int i=0;i<Data->Value;i++)
	{
		LPPCREATE_SUMMON Data2 = (LPPCREATE_SUMMON)(ReceiveBuffer+Offset);
		WORD Key       = ((WORD)(Data2->KeyH)<<8) + Data2->KeyL;
        WORD Type      = ((WORD)(Data2->TypeH)<<8) + Data2->TypeL;
		int CreateFlag = (Key>>15);
		Key &= 0x7FFF;
		
        CHARACTER* c;
#ifdef ADD_ELF_SUMMON
		// for test
#endif // ADD_ELF_SUMMON
        //  Į������ ���ϴ� ������ ���.
		if ( Type>=152 && Type<=158 )
        {
            c = CreateHellGate ( &Data2->ID[0], Key, Type, Data2->PositionX,Data2->PositionY, CreateFlag );
        }
        else
        {
			c = CreateMonster(Type,Data2->PositionX,Data2->PositionY,Key);
        }

		if(c == NULL) break;

		OBJECT *o = &c->Object;
		
		for( int j = 0; j < Data2->s_BuffCount; ++j )
		{
			RegisterBuff(static_cast<eBuffState>(Data2->s_BuffEffectState[j]), o);

#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "ID : %s, Buff : %d", c->ID, static_cast<int>(Data2->s_BuffEffectState[j]));
#endif // CONSOLE_DEBUG	
		}
		
		c->Object.Angle[2] = ((float)(Data2->Path>>4)-1.f)*45.f;
		c->PositionX = Data2->PositionX;
		c->PositionY = Data2->PositionY;
		c->TargetX = Data2->PositionX;
		c->TargetY = Data2->PositionY;
		o->Kind = KIND_PLAYER;
		c->PK   = Data2->Path&0xf;
		
#ifdef PK_ATTACK_TESTSERVER_LOG
		PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG
		
		if(c->PK >= PVP_MURDERER2)
			c->Level = 1;
		
        if ( Type<152 || Type>158 )
        {
            char Temp[100];
#ifdef GRAMMAR_OF
			// �۷ι�
            strcat(c->ID,GlobalText[485]);
            memcpy(Temp,Data2->ID,MAX_ID_SIZE);
            Temp[MAX_ID_SIZE] = NULL;
            strcat(c->ID,Temp);
#else // GRAMMAR_OF
			// �ѱ�
            strcpy(Temp,c->ID);
            memcpy(c->ID,Data2->ID,MAX_ID_SIZE);
            c->ID[MAX_ID_SIZE] = NULL;
            strcat(c->ID,GlobalText[485]);
            strcat(c->ID,Temp);
#endif // GRAMMAR_OF
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
			// ���� ���� ID ����
            memcpy(c->OwnerID,Data2->ID,MAX_ID_SIZE);
            c->OwnerID[MAX_ID_SIZE] = NULL;
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
        }
		
		if(CreateFlag)
		{
			AppearMonster(c);
			CreateEffect(MODEL_MAGIC_CIRCLE1,o->Position,o->Angle,o->Light,0,o);
			CreateParticle(BITMAP_LIGHTNING+1,o->Position,o->Angle,o->Light,2,1.f,o);
			if ( Type>=152 && Type<=158 )
            {
                o->PriorAnimationFrame = 0.f;
                o->AnimationFrame = 0.f;
                PlayBuffer ( SOUND_CHAOS_FALLING_STONE );
            }
		}
		else if(PathFinding2(c->PositionX, c->PositionY, Data2->TargetX,Data2->TargetY,&c->Path))
		{
			c->Movement = true;
		}

		Offset += (sizeof(PCREATE_SUMMON)-(sizeof(BYTE)*(MAX_BUFF_SLOT_INDEX-Data2->s_BuffCount)));
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x1F����[ReceiveCreateSummonViewport(%d)]", Data->Value);
#endif // CONSOLE_DEBUG
}

void ReceiveDeleteCharacterViewport( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	int Offset = sizeof(PHEADER_DEFAULT);
	for(int i=0; i<Data->Value; i++)
	{
		LPPDELETE_CHARACTER Data2 = (LPPDELETE_CHARACTER)(ReceiveBuffer+Offset);
		
		if(Switch_Info != NULL)
		{
			WORD Key = ((WORD)(Data2->KeyH)<<8) + Data2->KeyL;
			if(Key == FIRST_CROWN_SWITCH_NUMBER)
				{
					Switch_Info[0].Reset();
				}
				else
				{
					Switch_Info[1].Reset();
				}
		}
		
		int Key = ((int)(Data2->KeyH)<<8) + Data2->KeyL;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int DeleteFlag = (Key>>15);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		Key &= 0x7FFF;
		
		// ���� �� ĳ���Ͱ� �ٸ� ������ �̵��ϸ� ����â �ݴ� ó�� 
		int iIndex = g_pPurchaseShopInventory->GetShopCharacterIndex();
		if(iIndex >=0 && iIndex < MAX_CHARACTERS_CLIENT)
		{
			CHARACTER* pCha = &CharactersClient[iIndex];
			if(pCha && pCha->Key == Key)
			{
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY);
			}
		}
		
		iIndex = FindCharacterIndex(Key);
		CHARACTER* pCha = &CharactersClient[iIndex];
		
		int buffSize = g_CharacterBuffSize( (&pCha->Object) );
		
		for( int k = 0; k < buffSize; k++ )
		{
			UnRegisterBuff( g_CharacterBuff( (&pCha->Object), k ), &pCha->Object );
		}

		DeleteCharacter(Key);
		CHARACTER* pPlayer = FindCharacterTagShopTitle(Key);
		if(pPlayer) 
		{
			RemoveShopTitle(pPlayer);
		}
		
		Offset += sizeof(PDELETE_CHARACTER);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ����
///////////////////////////////////////////////////////////////////////////////

int AttackPlayer = 0;

void ReceiveDamage( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_DAMAGE Data = (LPPRECEIVE_DAMAGE)ReceiveBuffer;
	int Damage = ((int)(Data->DamageH)<<8) + Data->DamageL;
	if(CharacterAttribute->Life >= Damage)
		CharacterAttribute->Life -= Damage;
	else
		CharacterAttribute->Life = 0;
	
	int ShieldDamage = ((int)(Data->ShieldDamageH)<<8) + Data->ShieldDamageL;
	if(CharacterAttribute->Shield >= ShieldDamage)
		CharacterAttribute->Shield = ShieldDamage;
	else
		CharacterAttribute->Shield = 0;
}

void ProcessDamageCastle( LPPRECEIVE_ATTACK Data)
{
	int Key    = ((int)(Data->KeyH   )<<8) + Data->KeyL;
	int Success = (Key>>15);
	Key &= 0x7FFF;
	
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	vec3_t Light;
	WORD Damage			= (((WORD)(Data->DamageH)<<8) + Data->DamageL);
	int	 DamageType		= (Data->DamageType)&0x3f;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    bool bDoubleEnable  = (Data->DamageType>>6)&0x01;
	bool bComboEnable	= (Data->DamageType>>7)&0x01;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	WORD ShieldDamage	= (((WORD)(Data->ShieldDamageH)<<8) + Data->ShieldDamageL);
	
	//�������� ������ ǥ�� ���¸� ����
	int accumDamage = ShieldDamage + Damage;
	int	rstDamage = -1;
	float rstScale = 0.8f;
	Vector(0.5f, 0.5f, 0.5f, Light);
	if(accumDamage > 0)
	{
		rstDamage = -2;
		if(accumDamage > 0 && accumDamage < 1000)
		{
			Vector(1.f,0.f,0.f,Light);
		}
		else if(accumDamage >= 1000 && accumDamage < 3000)
		{
			Vector(0.95f, 0.7f, 0.15f, Light);
		}
		else if(accumDamage >= 3000)
		{
			Vector(0.95f, 0.7f, 0.15f, Light);
			rstScale = 1.5f;
		}
	}
	else
	{
       	if(Key == HeroKey)
		{
			Vector(1.f,1.f,1.f,Light);
		}
		else
		{
			Vector(0.5f,0.5f,0.5f,Light);
		}
	}
	
	if(Success)
	{
		SetPlayerShock(c,Damage);
		Vector(1.f,0.f,0.f,Light);
		if(Key == HeroKey)
		{
			if(Damage >= CharacterAttribute->Life)
				CharacterAttribute->Life = 0;
			else
				CharacterAttribute->Life -= Damage;
			
			if(ShieldDamage >= CharacterAttribute->Shield)
				CharacterAttribute->Shield = 0;
			else
				CharacterAttribute->Shield -= ShieldDamage;
			
		}
		
		CreatePoint(o->Position,rstDamage,Light,rstScale);
	}
	else
	{
		if(Key == HeroKey)
		{
			if(Damage >= CharacterAttribute->Life)
				CharacterAttribute->Life = 0;
			else
				CharacterAttribute->Life -= Damage;
			
			if(ShieldDamage >= CharacterAttribute->Shield)
				CharacterAttribute->Shield = 0;
			else
				CharacterAttribute->Shield -= ShieldDamage;
			
			
			if( g_isCharacterBuff(o, eBuff_PhysDefense) && o->Type==MODEL_PLAYER )			
			{
				CHARACTER *cm = &CharactersClient[AttackPlayer];
				OBJECT *om = &cm->Object;
				float fAngle = CreateAngle( om->Position[0], om->Position[1], o->Position[0], o->Position[1]);
				if ( fabs( fAngle - om->Angle[2]) < 10.f)
				{
					vec3_t Angle = { 0.0f, 0.0f, fAngle+180.f};
					CreateEffect( MODEL_MAGIC_CAPSULE2, o->Position, Angle, o->Light, 0, o);
				}
			}
#ifdef _PVP_ADD_MOVE_SCROLL
			if (Damage > 0)
				g_MurdererMove.CancelMove();
#endif	// _PVP_ADD_MOVE_SCROLL
		}
		else
		{
			if (c->MonsterIndex == 275);	// ����� ��� �ǰ� ó�� ����
			else if(rand()%2==0)
				SetPlayerShock(c,Damage);
		}
		
		if(DamageType == 4)
		{
			Vector(1.f,0.f,1.f,Light);
		}
		
		CreatePoint(o->Position,rstDamage,Light,rstScale);
	}
	c->Hit = Damage;
}

//������ ������
void ReceiveAttackDamage( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_ATTACK Data = (LPPRECEIVE_ATTACK)ReceiveBuffer;

	//ī���� ĳ�������� ������ ü�� �ٸ��� ó��
	if(InChaosCastle())
	{
		ProcessDamageCastle(Data);
		return;
	}
	
	int Key    = ((int)(Data->KeyH   )<<8) + Data->KeyL;
	int Success = (Key>>15);
	Key &= 0x7FFF;
	
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	vec3_t Light;
	WORD Damage			= (((WORD)(Data->DamageH)<<8) + Data->DamageL);
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	// DamageType ���� 0~7������ ������� 0x20 0x10��Ʈ ���
	int	 DamageType		= (Data->DamageType)&0x0f;
	bool bRepeatedly = (Data->DamageType>>4)&0x01;
	bool bEndRepeatedly = (Data->DamageType>>5)&0x01;
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	int	 DamageType		= (Data->DamageType)&0x3f;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
    bool bDoubleEnable  = (Data->DamageType>>6)&0x01;
	bool bComboEnable	= (Data->DamageType>>7)&0x01;
	WORD ShieldDamage	= (((WORD)(Data->ShieldDamageH)<<8) + Data->ShieldDamageL);

#ifdef CSK_HACK_TEST
	g_pHackTest->ReceiveDamage(c, o, Success, Damage, DamageType, bDoubleEnable, bComboEnable, ShieldDamage, Key);
#endif // CSK_HACK_TEST
	
	if(Success)
	{
		SetPlayerShock(c,Damage);
		Vector(1.f,0.f,0.f,Light);
		
		CreatePoint(o->Position,Damage,Light);
		
		if(ShieldDamage > 0)
		{
			vec3_t nPosShieldDamage;
			Vector(0.8f,1.f,0.f,Light);
			nPosShieldDamage[0] = o->Position[0]; nPosShieldDamage[1] = o->Position[1];
			nPosShieldDamage[2] = o->Position[2] + 25.f;
			CreatePoint(nPosShieldDamage, ShieldDamage, Light);
		}
		
		if(Key == HeroKey)
		{
			if(Damage >= CharacterAttribute->Life)
				CharacterAttribute->Life = 0;
			else
				CharacterAttribute->Life -= Damage;
			
			if(ShieldDamage >= CharacterAttribute->Shield)
				CharacterAttribute->Shield = 0;
			else
				CharacterAttribute->Shield -= ShieldDamage;
		}
	}
	else
	{
		if(Key == HeroKey)
		{
			if(Damage >= CharacterAttribute->Life)
				CharacterAttribute->Life = 0;
			else
				CharacterAttribute->Life -= Damage;
			
			if(ShieldDamage >= CharacterAttribute->Shield)
				CharacterAttribute->Shield = 0;
			else
				CharacterAttribute->Shield -= ShieldDamage;
			
			// �� ���� �κ�
			if( g_isCharacterBuff( o, eBuff_PhysDefense ) && o->Type==MODEL_PLAYER )			
			{
				CHARACTER *cm = &CharactersClient[AttackPlayer];
				OBJECT *om = &cm->Object;
				float fAngle = CreateAngle( om->Position[0], om->Position[1], o->Position[0], o->Position[1]);
				if ( fabs( fAngle - om->Angle[2]) < 10.f)
				{
					vec3_t Angle = { 0.0f, 0.0f, fAngle+180.f};
					CreateEffect( MODEL_MAGIC_CAPSULE2, o->Position, Angle, o->Light, 0, o);
				}
			}
			
#ifdef _PVP_ADD_MOVE_SCROLL
			if (Damage > 0)
				g_MurdererMove.CancelMove();
#endif	// _PVP_ADD_MOVE_SCROLL
		}
		else
		{
			if (c->MonsterIndex == 275)	// ����� ��� �ǰ� ó�� ����
			{
				// �ƹ�ó�� ����
			}
			else if(rand()%2==0)
			{
				SetPlayerShock(c,Damage);
			}
		}
        float scale = 15.f;
		if(Damage == 0)
		{
			if(Key == HeroKey)
			{
				Vector(1.f,1.f,1.f,Light);
			}
			else
			{
				Vector(0.5f,0.5f,0.5f,Light);
			}
		}
		else
		{
			switch ( DamageType )
			{
			case 0:	//	DT_NONE
				if(Key == HeroKey)
				{
					Vector(1.f,0.f,0.f,Light);
				}
				else
				{
					Vector(1.f,0.6f,0.f,Light);
				}
				break;
			case 1:	//	DT_PERFECT
				scale = 50.f;
				Vector(0.0f,1.f,1.f,Light);
				break;
			case 2:	//	DT_EXCELLENT
				scale = 50.f;
				Vector(0.f,1.f,0.6f,Light);
				break;
			case 3:	//	DT_CRITICAL
				scale = 50.f;
				Vector(0.f,0.6f,1.f,Light);
				break;
			case 4:	//	DT_MIRROR
				Vector(1.f,0.f,1.f,Light);
				break;
			case 5: //	DT_POSION
				Vector(0.f,1.f,0.f,Light);
				break;
			case 6:	//	DT_DOT
				Vector(0.7f,0.4f,1.0f,Light);
				break;
			default :
				Vector ( 1.f, 1.f, 1.f, Light );
				break;
			}
			
			if ( bComboEnable )
			{
				scale = 50.f;
			}
		}
		
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		if(bRepeatedly || bEndRepeatedly)
		{
			g_CMonkSystem.SetRepeatedly(Damage, DamageType, bDoubleEnable, bEndRepeatedly);
			if(bEndRepeatedly)
			{
				g_CMonkSystem.RenderRepeatedly(Key, o);
			}
		}
		else
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		if(Damage == 0)
			CreatePoint(o->Position,-1,Light);
		else
        {
			if ( bComboEnable )
			{
				vec3_t Position, Light2;
				VectorCopy ( o->Position, Position);
				Vector(Light[0]-0.4f,Light[1]-0.4f,Light[2]-0.4f,Light2);
				CreatePoint( Position,Damage,Light2, scale);
				Position[2] += 10.f;
				Vector(Light[0]-0.2f,Light[1]-0.2f,Light[2]-0.2f,Light2);
				CreatePoint( Position,Damage,Light2, scale+5.f);
				Position[2] += 10.f;
				CreatePoint( Position,Damage,Light, scale+10.f);
			}
			else if ( bDoubleEnable  )    //  Double Damage
            {
				vec3_t Position, Light2;
				VectorCopy ( o->Position, Position);
				Vector(Light[0]-0.4f,Light[1]-0.4f,Light[2]-0.4f,Light2);
				CreatePoint( Position,Damage,Light2, scale);
				Position[2] += 10.f;
				Vector(Light[0]-0.2f,Light[1]-0.2f,Light[2]-0.2f,Light2);
				CreatePoint( Position,Damage,Light2, scale+5.f);
            }
			
			CreatePoint(o->Position,Damage,Light, scale);
        }
		
		if(ShieldDamage > 0)
		{
			vec3_t nPosShieldDamage;
			Vector(0.8f,1.f,0.f,Light);
			nPosShieldDamage[0] = o->Position[0]; nPosShieldDamage[1] = o->Position[1];
			nPosShieldDamage[2] = o->Position[2] + 25.f;
			CreatePoint(nPosShieldDamage, ShieldDamage, Light);
		}
	}
	c->Hit = Damage;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x15����[ReceiveAttackDamage(%d %d)]", AttackPlayer, Damage);
#endif // CONSOLE_DEBUG
}

void ReceiveAction(BYTE *ReceiveBuffer,int Size)
{
	LPPRECEIVE_ACTION Data = (LPPRECEIVE_ACTION)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
	
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	
	int iTargetKey, iTargetIndex;
	
	iTargetKey = ((int)(Data->TargetKeyH )<<8) + Data->TargetKeyL;	
	iTargetIndex = FindCharacterIndex(iTargetKey);
	
    if ( c->Helper.Type==MODEL_HELPER+4 ) return;
	//if(c->Helper.Type == MODEL_HELPER+37) return;	//^ �渱 ĳ���� ���ϸ��̼� ����(�渱 Ÿ�� �������� �� �ɾ�����)
	
	c->Object.Angle[2] = ((float)(Data->Angle)-1.f)*45.f;
	c->Movement = false;
	
	c->Object.Position[0] = c->TargetX*TERRAIN_SCALE+TERRAIN_SCALE*0.5f;
	c->Object.Position[1] = c->TargetY*TERRAIN_SCALE+TERRAIN_SCALE*0.5f;
	switch(Data->Action)
	{
	case AT_STAND1:
	case AT_STAND2:
		SetPlayerStop(c);
		break;
	case AT_ATTACK1:
	case AT_ATTACK2:
		SetPlayerAttack(c);
		c->AttackTime = 1;
		c->Object.AnimationFrame = 0;
		
		c->TargetCharacter = HeroIndex;
		
		AttackPlayer = Index;
		break;
	case AT_SKILL_BLOCKING:
		SetAction(o,PLAYER_DEFENSE1);
		PlayBuffer(SOUND_SKILL_DEFENSE);
		break;
	case AT_SIT1:
		if(!IsFemale(c->Class))
			SetAction(&c->Object,PLAYER_SIT1);
		else
			SetAction(&c->Object,PLAYER_SIT_FEMALE1);
		break;
	case AT_POSE1:
		if(!IsFemale(c->Class))
			SetAction(&c->Object,PLAYER_POSE1);
		else
			SetAction(&c->Object,PLAYER_POSE_FEMALE1);
		break;
	case AT_HEALING1:
		if(!IsFemale(c->Class))
			SetAction(&c->Object,PLAYER_HEALING1);
		else
			SetAction(&c->Object,PLAYER_HEALING_FEMALE1);
		break;
	case AT_GREETING1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_GREETING1);
		else
			SetAction(o,PLAYER_GREETING_FEMALE1);
		break;
	case AT_GOODBYE1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_GOODBYE1);
		else
			SetAction(o,PLAYER_GOODBYE_FEMALE1);
		break;
	case AT_CLAP1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_CLAP1);
		else
			SetAction(o,PLAYER_CLAP_FEMALE1);
		break;
	case AT_GESTURE1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_GESTURE1);
		else
			SetAction(o,PLAYER_GESTURE_FEMALE1);
		break;
	case AT_DIRECTION1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_DIRECTION1);
		else
			SetAction(o,PLAYER_DIRECTION_FEMALE1);
		break;
	case AT_UNKNOWN1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_UNKNOWN1);
		else
			SetAction(o,PLAYER_UNKNOWN_FEMALE1);
		break;
	case AT_CRY1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_CRY1);
		else
			SetAction(o,PLAYER_CRY_FEMALE1);
		break;
	case AT_AWKWARD1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_AWKWARD1);
		else
			SetAction(o,PLAYER_AWKWARD_FEMALE1);
		break;
	case AT_SEE1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_SEE1);
		else
			SetAction(o,PLAYER_SEE_FEMALE1);
		break;
	case AT_CHEER1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_CHEER1);
		else
			SetAction(o,PLAYER_CHEER_FEMALE1);
		break;
	case AT_WIN1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_WIN1);
		else
			SetAction(o,PLAYER_WIN_FEMALE1);
		break;
	case AT_SMILE1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_SMILE1);
		else
			SetAction(o,PLAYER_SMILE_FEMALE1);
		break;
	case AT_SLEEP1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_SLEEP1);
		else
			SetAction(o,PLAYER_SLEEP_FEMALE1);
		break;
	case AT_COLD1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_COLD1);
		else
			SetAction(o,PLAYER_COLD_FEMALE1);
		break;
	case AT_AGAIN1:
		if(!IsFemale(c->Class))
			SetAction(o,PLAYER_AGAIN1);
		else
			SetAction(o,PLAYER_AGAIN_FEMALE1);
		break;
	case AT_RESPECT1:
		SetAction(o,PLAYER_RESPECT1);
		break;
	case AT_SALUTE1:
		SetAction(o,PLAYER_SALUTE1);
		break;
	case AT_RUSH1:
		SetAction(o,PLAYER_RUSH1);
		break;
	case AT_SCISSORS:	// ����
		SetAction(o,PLAYER_SCISSORS);
		break;
	case AT_ROCK:		// ����
		SetAction(o,PLAYER_ROCK);
		break;
	case AT_PAPER:		// ��
		SetAction(o,PLAYER_PAPER);
		break;
	case AT_HUSTLE:	// �Ϻ� ������ ���� -_-
		SetAction(o,PLAYER_HUSTLE);
		break;
	case AT_DAMAGE1:	// ���Ȥ�� �ǰݵ��� (�����ȿ��)
		SetAction(&c->Object,MONSTER01_SHOCK);
		break;
	case AT_PROVOCATION:	// ���� ���� �߰�
		SetAction(o,PLAYER_PROVOCATION);
		break;
	case AT_LOOK_AROUND:	// �θ��� ���� �߰�
		SetAction(o,PLAYER_LOOK_AROUND);
		break;
	case AT_CHEERS:			// ���� ���� �߰�
		SetAction(o,PLAYER_CHEERS);
		break;
	case AT_JACK1:
		SetAction(o, PLAYER_JACK_1);
		o->m_iAnimation = 0;
		break;
	case AT_JACK2:
		SetAction(o, PLAYER_JACK_2);
		o->m_iAnimation = 0;
		break;
	case AT_SANTA1_1:
	case AT_SANTA1_2:
	case AT_SANTA1_3:
		{
			SetAction(o, PLAYER_SANTA_1);
			int i = Data->Action % AT_SANTA1_1;
			g_XmasEvent->CreateXmasEventEffect(c, o, i);
			o->m_iAnimation = 0;
			PlayBuffer(SOUND_XMAS_JUMP_SANTA + i);
		}
		break;
	case AT_SANTA2_1:
	case AT_SANTA2_2:
	case AT_SANTA2_3:
		{
			SetAction(o, PLAYER_SANTA_2);
			int i = Data->Action % AT_SANTA2_1;
			g_XmasEvent->CreateXmasEventEffect(c, o, i);
			o->m_iAnimation = 0;
			PlayBuffer(SOUND_XMAS_TURN);
		}
		break;
		
#ifdef WORLDCUP_ADD
#ifndef NO_MORE_DANCING
	case AT_HANDCLAP:
		{
			int Rnd = (int)(rand()%6);
			SetAction(o,PLAYER_KOREA_HANDCLAP);
			PlayBuffer(SOUND_WORLDCUP_RND1 + Rnd);
		}
		break;
	case AT_POINTDANCE:
		SetAction(o,PLAYER_POINT_DANCE);
		break;
#endif
#endif
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case AT_RAGEBUFF_1:
		{
			SetAction(o, PLAYER_SKILL_ATT_UP_OURFORCES);
			PlayBuffer(SOUND_RAGESKILL_BUFF_1);
		}
		break;
	case AT_RAGEBUFF_2:
		{
			SetAction(o, PLAYER_SKILL_HP_UP_OURFORCES);
			PlayBuffer(SOUND_RAGESKILL_BUFF_2);
		}
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	default:
		SetAction(&c->Object,Data->Action);
		break;
	}

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x18����[ReceiveAction(%d)]", Data->Angle);
#endif // CONSOLE_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
// ����
///////////////////////////////////////////////////////////////////////////////

// ��ų�� ��� ������ ���� �Ǿ�� �� ����
void ReceiveSkillStatus( BYTE *ReceiveBuffer )
{
	LPPMSG_VIEWSKILLSTATE Data = (LPPMSG_VIEWSKILLSTATE)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
    CHARACTER* c = &CharactersClient[FindCharacterIndex(Key)];
	OBJECT *o = &c->Object;
	
	if ( Data->State == 1) // add
	{
		eBuffState bufftype = static_cast<eBuffState>(Data->BuffIndex);
		
		if( bufftype == eBuffNone || bufftype >= eBuff_Count ) return;
		
		if( g_isCharacterBuff( o, bufftype ) )
		{
			// �̰� ������ �𸣰ڴ�.
			if((o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				|| MODEL_SMITH || MODEL_NPC_SERBIS || MODEL_MERCHANT_MAN
				|| MODEL_STORAGE || MODEL_NPC_BREEDER )
			{
				if( g_isCharacterBuff( o, eBuff_CrywolfHeroContracted ) )
				{
					g_TokenCharacterBuff( o, eBuff_CrywolfHeroContracted );
				}
				else
				{
					g_TokenCharacterBuff( o, eBuff_CrywolfHeroContracted );
					g_CharacterUnRegisterBuff( o, eBuff_CrywolfHeroContracted );
				}
			}
		}
		else
		{
			
			RegisterBuff( bufftype, o );
			if( bufftype == eBuff_CastleRegimentDefense || bufftype == eBuff_CastleRegimentAttack1
				|| bufftype == eBuff_CastleRegimentAttack2 || bufftype == eBuff_CastleRegimentAttack3 )
			{
				battleCastle::SettingBattleFormation ( c, bufftype );
			}
			else if( bufftype == eBuff_GMEffect )
			{
				if ( c->m_pParts != NULL )
				{
					DeleteParts ( c );
				}
				c->EtcPart = PARTS_WEBZEN;
			}
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "RegisterBuff ID : %s, Buff : %d", c->ID, static_cast<int>(bufftype));
#endif // CONSOLE_DEBUG
		}
	}
	else // clear
	{
		eBuffState bufftype = static_cast<eBuffState>(Data->BuffIndex);
		
		if( bufftype == eBuffNone || bufftype >= eBuff_Count ) return;
		
		UnRegisterBuff( bufftype, o );
		if( bufftype == eBuff_CastleRegimentDefense || bufftype == eBuff_CastleRegimentAttack1
			|| bufftype == eBuff_CastleRegimentAttack2 || bufftype == eBuff_CastleRegimentAttack3 )
		{
			battleCastle::DeleteBattleFormation( c, bufftype );
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "UnRegisterBuff ID : %s, Buff : %d", c->ID, static_cast<int>(bufftype));
#endif // CONSOLE_DEBUG	
		}
		else if( bufftype == eBuff_GMEffect )
		{
			DeleteParts ( c );
		}
	}
	
}

// ��ų�� ���� ���� ��� ������ �� ����
void ReceiveMagicFinish( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_VALUE_KEY Data = (LPPHEADER_DEFAULT_VALUE_KEY)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
	OBJECT *o = &CharactersClient[FindCharacterIndex(Key)].Object;
	
	switch(Data->Value)
	{
	case AT_SKILL_POISON:
		UnRegisterBuff( eDeBuff_Poison, o );
		break;
	case AT_SKILL_SLOW:
		UnRegisterBuff( eDeBuff_Freeze, o);
		break;
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	case AT_SKILL_BLOW_OF_DESTRUCTION:
		UnRegisterBuff( eDeBuff_BlowOfDestruction, o);
		break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION

#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATTACK:
		UnRegisterBuff( eBuff_Attack, o);
		break;
		//#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
		//	case AT_SKILL_RECOVER:
		//#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
		
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEFENSE:
		UnRegisterBuff( eBuff_Defense, o);
		break;
	case AT_SKILL_STUN:
		UnRegisterBuff( eDeBuff_Stun, o);
		break;
    case AT_SKILL_INVISIBLE:
		UnRegisterBuff( eBuff_Cloaking, o);
        break;
    case AT_SKILL_MANA:
        UnRegisterBuff( eBuff_AddMana, o );
        break;
    case AT_SKILL_BRAND_OF_SKILL: 
		UnRegisterBuff( eBuff_AddSkill, o );
        break;
    case AT_SKILL_IMPROVE_AG:
		UnRegisterBuff( eBuff_AddAG, o);
        break;
    case AT_SKILL_ADD_CRITICAL:
        UnRegisterBuff( eBuff_AddCriticalDamage, o );
        break;
	case AT_SKILL_LIFE_UP:
	case AT_SKILL_LIFE_UP+1:
	case AT_SKILL_LIFE_UP+2:
	case AT_SKILL_LIFE_UP+3:
	case AT_SKILL_LIFE_UP+4:
    case AT_SKILL_VITALITY:
		UnRegisterBuff( eBuff_HpRecovery, o); //eBuff_Life
        break;
    case AT_SKILL_PARALYZE:
		UnRegisterBuff( eDeBuff_Harden, o);
        break;
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_BLOOD_ATT_UP:
	case AT_SKILL_BLOOD_ATT_UP+1:
	case AT_SKILL_BLOOD_ATT_UP+2:
	case AT_SKILL_BLOOD_ATT_UP+3:
	case AT_SKILL_BLOOD_ATT_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_REDUCEDEFENSE:
		UnRegisterBuff( eDeBuff_Defense, o);
		break;
	case AT_SKILL_SOUL_UP:
	case AT_SKILL_SOUL_UP+1:
	case AT_SKILL_SOUL_UP+2:
	case AT_SKILL_SOUL_UP+3:
	case AT_SKILL_SOUL_UP+4:
	case AT_SKILL_WIZARDDEFENSE:
		UnRegisterBuff( eBuff_PhysDefense, o);
		break;
	case AT_SKILL_BLAST_POISON:
		UnRegisterBuff( eDeBuff_Poison, o);
		break;
//AT_SKILL_ICE_UP
	case AT_SKILL_ICE_UP:
	case AT_SKILL_ICE_UP+1:
	case AT_SKILL_ICE_UP+2:
	case AT_SKILL_ICE_UP+3:
	case AT_SKILL_ICE_UP+4:
	case AT_SKILL_BLAST_FREEZE:
		UnRegisterBuff( eDeBuff_Freeze, o);
		break;
        //  ����.
    case AT_SKILL_MONSTER_MAGIC_DEF:
        SetActionDestroy_Def ( o );
		UnRegisterBuff( eBuff_Defense, o);
        break;
    case AT_SKILL_MONSTER_PHY_DEF:
        SetActionDestroy_Def ( o );
		UnRegisterBuff( eBuff_PhysDefense, o);
        break;
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case AT_SKILL_ATT_UP_OURFORCES:
		UnRegisterBuff( eBuff_Att_up_Ourforces, o);
		break;
	case AT_SKILL_HP_UP_OURFORCES:
		UnRegisterBuff( eBuff_Hp_up_Ourforces, o);
		break;
	case AT_SKILL_DEF_UP_OURFORCES:
		UnRegisterBuff( eBuff_Def_up_Ourforces, o);
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}
}

// ���� �÷��̾��� �ִϸ��̼� ���� (������ ���)
void SetPlayerBow(CHARACTER *c)
{
#ifdef KJH_FIX_BOW_ANIMATION_ON_RIDE_PET
	OBJECT *o = &c->Object;

	// �÷��̾�, ����, �������밡 �ƴϸ� return
	if(o->Type!=MODEL_PLAYER || GetBaseClass(c->Class) != CLASS_ELF || c->SafeZone)
		return;
	
	// ���Ӱ�� ����
	SetAttackSpeed();
	
	switch( GetEquipedBowType( c ))
	{
	case BOWTYPE_BOW:		// Ȱ
		{
			if( c->Helper.Type == MODEL_HELPER+37 )				
			{
				SetAction( &c->Object, PLAYER_FENRIR_ATTACK_BOW );		// �Ҹ�����
			}
			else if((c->Helper.Type==MODEL_HELPER+2) || (c->Helper.Type==MODEL_HELPER+3))
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_BOW );		// Ż������
			}
			else if( c->Wing.Type!=-1 )										
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_BOW );			// ��������
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_BOW );				// �Ϲ�Ȱ����
			}
		}break;
	case BOWTYPE_CROSSBOW:	// ����
		{
			if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)	// �Ҹ�����
			{
				SetAction( &c->Object, PLAYER_FENRIR_ATTACK_CROSSBOW );
			}
			else if(( c->Helper.Type==MODEL_HELPER+2) || (c->Helper.Type==MODEL_HELPER+3))
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_CROSSBOW );	// Ż������
			}
			else if( c->Wing.Type!=-1 )										// ��������
			{	
				SetAction( &c->Object, PLAYER_ATTACK_FLY_CROSSBOW );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_CROSSBOW );		// �Ϲ�Ȱ����
			}
		}break;
	}
#else // KJH_FIX_BOW_ANIMATION_ON_RIDE_PET		// ������ �� ������ �ϴ� �ҽ�
#ifdef ADD_SOCKET_ITEM
	// Ȱ
	switch( GetEquipedBowType( c ))
	{
	case BOWTYPE_BOW:
		{
			if( (GetBaseClass(c->Class) == CLASS_ELF) && (c->Wing.Type!=-1) )
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_BOW );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_BOW );
			}
		}break;
		// ����
	case BOWTYPE_CROSSBOW:
		{
			if( (GetBaseClass(c->Class) == CLASS_ELF) && (c->Wing.Type!=-1) )
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_CROSSBOW );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_CROSSBOW );
			}
		}break;
	}
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
    if((c->Weapon[1].Type>=MODEL_BOW && c->Weapon[1].Type<MODEL_BOW+7) 
		|| c->Weapon[1].Type==MODEL_BOW+17 
        || c->Weapon[1].Type==MODEL_BOW+20 
		|| c->Weapon[1].Type==MODEL_BOW+21
		|| c->Weapon[1].Type==MODEL_BOW+22
        )	//. Ȱ
    {
        if(GetBaseClass(c->Class)==CLASS_ELF && c->Wing.Type!=-1)
            SetAction(&c->Object,PLAYER_ATTACK_FLY_BOW);
        else
            SetAction(&c->Object,PLAYER_ATTACK_BOW);
    }
    else if((c->Weapon[0].Type>=MODEL_BOW+8 && c->Weapon[0].Type<MODEL_BOW+15) || c->Weapon[0].Type==MODEL_BOW+16 || 
        (c->Weapon[0].Type>=MODEL_BOW+18 && c->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX) )	//. ����
    {
        if(GetBaseClass(c->Class)==CLASS_ELF && c->Wing.Type!=-1)
            SetAction(&c->Object,PLAYER_ATTACK_FLY_CROSSBOW);
        else
            SetAction(&c->Object,PLAYER_ATTACK_CROSSBOW);
    }
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
#endif // KJH_FIX_BOW_ANIMATION_ON_RIDE_PET	// ������ �� ������ �ϴ� �ҽ�
}

void SetPlayerHighBow ( CHARACTER* c )
{
#ifdef ADD_SOCKET_ITEM
#ifdef KJH_FIX_BOW_ANIMATION_ON_RIDE_PET
		switch( GetEquipedBowType( c ))
	{
	case BOWTYPE_BOW:		// Ȱ
		{
			if( c->Helper.Type == MODEL_HELPER+37 )				
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_BOW_UP );		// �Ҹ�����
			}
			else if((c->Helper.Type==MODEL_HELPER+2) || (c->Helper.Type==MODEL_HELPER+3))
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_BOW_UP );		// Ż������
			}
			else if( c->Wing.Type!=-1 )										
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_BOW_UP );			// ��������
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_BOW_UP );				// �Ϲ�Ȱ����
			}
		}break;
	case BOWTYPE_CROSSBOW:	// ����
		{
			if(c->Helper.Type == MODEL_HELPER+37 && !c->SafeZone)	// �Ҹ�����
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_CROSSBOW_UP );
			}
			else if(( c->Helper.Type==MODEL_HELPER+2) || (c->Helper.Type==MODEL_HELPER+3))
			{
				SetAction( &c->Object, PLAYER_ATTACK_RIDE_CROSSBOW_UP );	// Ż������
			}
			else if( c->Wing.Type!=-1 )										// ��������
			{	
				SetAction( &c->Object, PLAYER_ATTACK_FLY_CROSSBOW_UP );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_CROSSBOW_UP );		// �Ϲ�Ȱ����
			}
		}break;
	}
#else KJH_FIX_BOW_ANIMATION_ON_RIDE_PET
	// Ȱ
	switch( GetEquipedBowType( c ) )
	{
	case BOWTYPE_BOW:
		{
			if( (GetBaseClass(c->Class) == CLASS_ELF) && (c->Wing.Type!=-1) )
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_BOW_UP );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_BOW_UP );
			}
		}break;
		// ����
	case BOWTYPE_CROSSBOW:
		{
			if( (GetBaseClass(c->Class) == CLASS_ELF) && (c->Wing.Type!=-1) )
			{
				SetAction( &c->Object, PLAYER_ATTACK_FLY_CROSSBOW_UP );
			}
			else
			{
				SetAction( &c->Object, PLAYER_ATTACK_CROSSBOW_UP );
			}
		}break;
	}
#endif // KJH_FIX_BOW_ANIMATION_ON_RIDE_PET
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
    if((c->Weapon[1].Type>=MODEL_BOW && c->Weapon[1].Type<MODEL_BOW+7) || c->Weapon[1].Type==MODEL_BOW+17 
        || c->Weapon[1].Type==MODEL_BOW+20 
		|| c->Weapon[1].Type==MODEL_BOW+21
		|| c->Weapon[1].Type==MODEL_BOW+22
        )	//. Ȱ
    {
        if(GetBaseClass(c->Class)==CLASS_ELF && c->Wing.Type!=-1)
            SetAction(&c->Object,PLAYER_ATTACK_FLY_BOW_UP);
        else
            SetAction(&c->Object,PLAYER_ATTACK_BOW_UP);
    }
    else if((c->Weapon[0].Type>=MODEL_BOW+8 && c->Weapon[0].Type<MODEL_BOW+15) || c->Weapon[0].Type==MODEL_BOW+16 || 
        (c->Weapon[0].Type>=MODEL_BOW+18 && c->Weapon[0].Type<MODEL_BOW+MAX_ITEM_INDEX) )	//. ����
    {
        if(GetBaseClass(c->Class)==CLASS_ELF && c->Wing.Type!=-1)
            SetAction(&c->Object,PLAYER_ATTACK_FLY_CROSSBOW_UP);
        else
            SetAction(&c->Object,PLAYER_ATTACK_CROSSBOW_UP);
    }
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
}

BOOL ReceiveMonsterSkill(BYTE *ReceiveBuffer,int Size, BOOL bEncrypted)
{
	LPPRECEIVE_MONSTERSKILL Data = (LPPRECEIVE_MONSTERSKILL)ReceiveBuffer;
	
	int SourceKey = Data->SourceKey;
	int TargetKey = Data->TargetKey;
	int Success = (TargetKey>>15);
	
	WORD SkillNumber = ((WORD)(Data->MagicH )<<8) + Data->MagicL;
	
	int Index       = FindCharacterIndex(SourceKey);
	int TargetIndex = FindCharacterIndex(TargetKey);
	if(TargetIndex == MAX_CHARACTERS_CLIENT)
		return ( TRUE);
	AttackPlayer = Index;
	
	CHARACTER *sc = &CharactersClient[Index];
	CHARACTER *tc = &CharactersClient[TargetIndex];
	OBJECT *so = &sc->Object;
	OBJECT *to = &tc->Object;
	

	sc->MonsterSkill = SkillNumber;

	sc->SkillSuccess = (Success != 0);
	sc->TargetCharacter = TargetIndex;
	
	if(SkillNumber > ATMON_SKILL_BIGIN && SkillNumber < ATMON_SKILL_END)
	{
		sc->Object.Angle[2] = CreateAngle(so->Position[0],so->Position[1],to->Position[0],to->Position[1]);
		SetPlayerAttack(sc);
		so->AnimationFrame = 0;
		sc->AttackTime = 1;
	}
		
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_RECEIVE, "0x69����[ReceiveMonsterSkill(Skill : %d | SKey : %d |TKey : %d)]", SkillNumber, SourceKey, TargetKey);
#endif // CONSOLE_DEBUG
		
		return ( TRUE);
}

BOOL ReceiveMagic(BYTE *ReceiveBuffer,int Size, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x19);
		return ( FALSE);
	}
	
	LPPRECEIVE_MAGIC Data = (LPPRECEIVE_MAGIC)ReceiveBuffer;
	int SourceKey = ((int)(Data->SourceKeyH )<<8) + Data->SourceKeyL;
	int TargetKey = ((int)(Data->TargetKeyH )<<8) + Data->TargetKeyL;
	int Success = (TargetKey>>15);
	
	WORD MagicNumber = ((WORD)(Data->MagicH )<<8) + Data->MagicL;
	
	if(MagicNumber == AT_SKILL_ATTACK || MagicNumber == AT_SKILL_DEFENSE
#ifdef PJH_SEASON4_MASTER_RANK4
		|| (AT_SKILL_DEF_POWER_UP <= MagicNumber && MagicNumber <= AT_SKILL_DEF_POWER_UP+4)
		|| (AT_SKILL_ATT_POWER_UP <= MagicNumber && MagicNumber <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
		)
		{
			if(Success == false)
			{
				g_pChatListBox->AddText("", GlobalText[2249], SEASON3B::TYPE_SYSTEM_MESSAGE);
				return FALSE;
			}
		}
		
		TargetKey &= 0x7FFF;
		
		int Index       = FindCharacterIndex(SourceKey);
		int TargetIndex = FindCharacterIndex(TargetKey);
		if(TargetIndex == MAX_CHARACTERS_CLIENT)
			return ( TRUE);
		
		AttackPlayer = Index;
		CHARACTER *sc = &CharactersClient[Index];
		CHARACTER *tc = &CharactersClient[TargetIndex];
		OBJECT *so = &sc->Object;
		OBJECT *to = &tc->Object;

		if ( MagicNumber!=AT_SKILL_COMBO )
		{
			if(sc!=Hero && MagicNumber!=AT_SKILL_TELEPORT && MagicNumber!=AT_SKILL_TELEPORT_B && to->Visible)
					so->Angle[2] = CreateAngle(so->Position[0],so->Position[1],to->Position[0],to->Position[1]);
				sc->TargetCharacter = TargetIndex;
				
				// �渱 ��ų �ö�� ����ϸ� Ÿ���ε����� ���� �����Ѵ�.
			if(MagicNumber == AT_SKILL_PLASMA_STORM_FENRIR)
				sc->m_iFenrirSkillTarget = TargetIndex;
					
			sc->SkillSuccess = (Success != 0);
			sc->Skill = MagicNumber;
		}
		switch(MagicNumber)
		{
			case AT_SKILL_MONSTER_SUMMON:
				SetPlayerAttack ( sc );
				break;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			case AT_SKILL_RECOVER:
				{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
					OBJECT* oh = &Hero->Object;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
					OBJECT* o = so;
					vec3_t Light,Position,P,dp;
					vec3_t vFirePosition;
					
					float Matrix[3][4];
					
					if(sc != Hero)
					{
						Vector(0.f,-220.f,130.f,P);
						AngleMatrix(o->Angle,Matrix);
						VectorRotate(P,Matrix,dp);
						VectorAdd(dp,o->Position,Position);
						Vector(0.7f, 0.6f, 0.f, Light);
						CreateEffect(BITMAP_IMPACT, Position, o->Angle, Light, 0,o);
						SetAction(o,PLAYER_RECOVER_SKILL);
						sc->AttackTime = 1;
					}
					
					o = to;
					
					Vector(0.4f, 0.6f, 1.f, Light);
					Vector(0.f,0.f,0.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					Position[2] += 130;
					VectorCopy( o->Position, Position);
					for ( int i=0; i<19; ++i )
					{
						CreateJoint(BITMAP_FLARE,Position,Position,o->Angle,47,o,40,2);
					}
					Vector ( 0.3f, 0.2f, 0.1f, Light );
					CreateEffect(MODEL_SUMMON,Position,o->Angle,Light, 0);
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 0 );
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 1 );
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 2 );
					
					
#ifdef _VS2008PORTING
					for (int i = 0; i < 2; ++i)
#else // _VS2008PORTING
					for (i = 0; i < 2; ++i)
#endif // _VS2008PORTING
					{
						int iNumBones = Models[o->Type].NumBones;
						Models[o->Type].TransformByObjectBone(vFirePosition, o, rand()%iNumBones);	
						CreateEffect(BITMAP_FLARE, vFirePosition, o->Angle, Light,3);
					}
				}
				
				break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			case AT_SKILL_MONSTER_MAGIC_DEF:
				sc->AttackTime = 1;
				g_CharacterRegisterBuff(so, eBuff_PhysDefense);
				SetPlayerAttack ( sc );
				break;
				
			case AT_SKILL_MONSTER_PHY_DEF:
				sc->AttackTime = 1;
				g_CharacterRegisterBuff(so, eBuff_Defense);
				SetPlayerAttack ( sc );
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
				if ( sc->MonsterIndex != 77)
				{
					PlayBuffer(SOUND_SKILL_DEFENSE);
				}
			case AT_SKILL_SOUL_UP:
			case AT_SKILL_SOUL_UP+1:
			case AT_SKILL_SOUL_UP+2:
			case AT_SKILL_SOUL_UP+3:
			case AT_SKILL_SOUL_UP+4:
			case AT_SKILL_WIZARDDEFENSE:
				if(sc != Hero)
				{
					SetPlayerMagic(sc);
					so->AnimationFrame = 0;
				}
				sc->AttackTime = 1;
				break;
			case AT_SKILL_THUNDER:
				if(so->Type != MODEL_MONSTER01+83)
					PlayBuffer(SOUND_THUNDER01);
				if(to->CurrentAction==PLAYER_POSE1 || to->CurrentAction==PLAYER_POSE_FEMALE1 ||
					to->CurrentAction==PLAYER_SIT1 || to->CurrentAction==PLAYER_SIT_FEMALE1)
					SetPlayerStop(tc);
			case AT_SKILL_FIREBALL:
			case AT_SKILL_METEO:
			case AT_SKILL_SLOW:
			case AT_SKILL_ENERGYBALL:
			case AT_SKILL_POWERWAVE:
			case AT_SKILL_POISON:
			case AT_SKILL_FLAME:
				if(sc != Hero)
				{
					if(so->Type == MODEL_PLAYER)
					{
						SetPlayerMagic(sc);
						so->AnimationFrame = 0;
					}
					else
					{
						SetPlayerAttack(sc);
						so->AnimationFrame = 0;
					}
				}
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_TELEPORT_B :
				CreateTeleportBegin(to);
				
				CreateTeleportEnd(so);
				if ( sc==Hero )
					Teleport = false;
				
				PlayBuffer(SOUND_TELEKINESIS,so);
				break;
				
			case AT_SKILL_TELEPORT:
				// ĭ����3�� ����Ʈ�޾������� ����Ʈ�޾� �����̵� �� �� ȿ��
				if(World == WD_39KANTURU_3RD && so->Type == MODEL_MONSTER01+121)
				{
					vec3_t Light;
					Vector ( 1.0f, 1.0f, 1.0f, Light );
					so->AlphaTarget = 0.f;
					CreateEffect(BITMAP_SPARK+1,so->Position,so->Angle,Light);
					CreateEffect(BITMAP_SPARK+1,so->Position,so->Angle,Light);
					PlayBuffer(SOUND_KANTURU_3RD_NIGHTMARE_TELE);
				}
				else
					CreateTeleportBegin(so);
				break;
				
			case AT_SKILL_STRONG_PIER:      //  ��Ʈ���Ǿ�.
				if ( (sc->Helper.Type>=MODEL_HELPER+2 && sc->Helper.Type<=MODEL_HELPER+4) && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_STRIKE );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction(so, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	// �渱 Ÿ�� ������ �渱�� �´� �׼�����
				}
				else
				{
					SetAction ( so, PLAYER_ATTACK_STRIKE );
				}
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD1);
				break;
			case AT_SKILL_FIRE_BUST_UP:
			case AT_SKILL_FIRE_BUST_UP+1:
			case AT_SKILL_FIRE_BUST_UP+2:
			case AT_SKILL_FIRE_BUST_UP+3:
			case AT_SKILL_FIRE_BUST_UP+4:
			case AT_SKILL_LONGPIER_ATTACK:  //  ���̾����Ʈ
				if ( (sc->Helper.Type>=MODEL_HELPER+2 && sc->Helper.Type<=MODEL_HELPER+4) && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_STRIKE );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction(so, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	// �渱 Ÿ�� ������ �渱�� �´� �׼�����
				}
				else
				{
					SetAction ( so, PLAYER_ATTACK_STRIKE );
				}
				sc->AttackTime = 1;
				PlayBuffer ( SOUND_ATTACK_FIRE_BUST );
				break;
				
			case AT_SKILL_SWORD1:
				SetAction(so,PLAYER_ATTACK_SKILL_SWORD1+MagicNumber-AT_SKILL_SWORD1);
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD1);
				break;
				
			case AT_SKILL_SWORD2:
				SetAction(so,PLAYER_ATTACK_SKILL_SWORD1+MagicNumber-AT_SKILL_SWORD1);
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD2);
				break;
				
			case AT_SKILL_SWORD3:
				SetAction(so,PLAYER_ATTACK_SKILL_SWORD1+MagicNumber-AT_SKILL_SWORD1);
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD3);
				break;
				
			case AT_SKILL_SWORD4:
				SetAction(so,PLAYER_ATTACK_SKILL_SWORD1+MagicNumber-AT_SKILL_SWORD1);
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD4);
				break;
				
			case AT_SKILL_SWORD5://����
				if(sc->SwordCount%2==0)
				{
					SetAction(so,PLAYER_ATTACK_SKILL_SWORD1+MagicNumber-AT_SKILL_SWORD1);
				}
				else
				{
					SetAction(so,PLAYER_ATTACK_TWO_HAND_SWORD1+2);
					//SetAction(so,PLAYER_ATTACK_TWO_HAND_SWORD1+sc->SwordCount%3);
				}
				sc->SwordCount++;
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD4);
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_POWER_SLASH_UP:
			case AT_SKILL_POWER_SLASH_UP+1:
			case AT_SKILL_POWER_SLASH_UP+2:
			case AT_SKILL_POWER_SLASH_UP+3:
			case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ICE_BLADE:
				SetAction ( so, PLAYER_ATTACK_TWO_HAND_SWORD_TWO );
				sc->AttackTime = 1;
				PlayBuffer( SOUND_SKILL_SWORD4 );
				break;
				
			case AT_SKILL_SPEAR:	// â���
				if(sc->Helper.Type == MODEL_HELPER+37)
					SetAction(so, PLAYER_FENRIR_ATTACK_SPEAR);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����(��ų)
				else
					SetAction(so,PLAYER_ATTACK_SKILL_SPEAR);
				sc->AttackTime = 1;
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOW_UP:
			case AT_SKILL_BLOW_UP+1:
			case AT_SKILL_BLOW_UP+2:
			case AT_SKILL_BLOW_UP+3:
			case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ONETOONE:	// ��ο�
				SetAction(so,PLAYER_ATTACK_ONETOONE);
				if( sc != Hero && so->Type == MODEL_PLAYER)
				{
					so->AnimationFrame = 0;
				}
				sc->AttackTime = 1;
				//PlayBuffer(SOUND_FLASH);
				break;
			case AT_SKILL_MANY_ARROW_UP:
			case AT_SKILL_MANY_ARROW_UP+1:
			case AT_SKILL_MANY_ARROW_UP+2:
			case AT_SKILL_MANY_ARROW_UP+3:
			case AT_SKILL_MANY_ARROW_UP+4:
			case AT_SKILL_CROSSBOW:
				SetPlayerBow(sc);
				sc->AttackTime = 1;
				break;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
			case AT_SKILL_MULTI_SHOT:
				SetPlayerBow(sc);
				if( sc != Hero && so->Type == MODEL_PLAYER)
				{
					so->AnimationFrame = 0;
				}
				sc->AttackTime = 1;
				break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC	
//			case AT_SKILL_GAOTIC:
//				SetPlayerMagic(sc);
//				break;
#endif //
			case AT_SKILL_BLAST_CROSSBOW4:
				SetPlayerBow(sc);
				sc->AttackTime = 1;
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOOD_ATT_UP:
			case AT_SKILL_BLOOD_ATT_UP+1:
			case AT_SKILL_BLOOD_ATT_UP+2:
			case AT_SKILL_BLOOD_ATT_UP+3:
			case AT_SKILL_BLOOD_ATT_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_REDUCEDEFENSE:
				if ( sc->SkillSuccess )
				{
					DeleteEffect(BITMAP_SKULL,to,0);
					vec3_t Light = { 1.0f, 1.f, 1.f};
					CreateEffect(BITMAP_SKULL,to->Position,to->Angle,Light,0,to);

					PlayBuffer(SOUND_BLOODATTACK,to);
					g_CharacterRegisterBuff(to, eDeBuff_Defense);
				}
				if ( so->Type != MODEL_PLAYER )
				{
					SetPlayerAttack(sc);
					so->AnimationFrame = 0;
					sc->AttackTime = 1;
				}
				break;
				
			case AT_SKILL_PIERCING:
				SetPlayerBow(sc);
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_PARALYZE:
				SetPlayerBow(sc);
				if( sc->SkillSuccess )
				{
					DeleteEffect(MODEL_ICE,to,1);
					
					vec3_t Angle;
					VectorCopy ( to->Angle, Angle );
					
					CreateEffect(MODEL_ICE,to->Position,Angle,to->Light,1,to);
					
					Angle[2] += 180.f;
					CreateEffect(MODEL_ICE,to->Position,Angle,to->Light,2,to);
					
					//  ����� ĳ���ʹ� ������ ����.
					tc->Movement = false;
					SetPlayerStop(tc);

					g_CharacterRegisterBuff(to, eDeBuff_Harden);
				}
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_RUSH:
				SetAction ( so, PLAYER_ATTACK_RUSH );
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD2);
				break;
				
			case AT_SKILL_JAVELIN:
				if(sc != Hero)
				{
					if(so->Type == MODEL_PLAYER)
					{
						SetPlayerMagic(sc);
						so->AnimationFrame = 0;
					}
				}
				//        SetPlayerMagic(sc);
				so->AnimationFrame = 0;
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_DEATH_CANNON:
				//SetPlayerMagic(sc);
				SetAction ( so, PLAYER_ATTACK_DEATH_CANNON );
				so->AnimationFrame = 0;
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_DEEPIMPACT:
				SetPlayerHighBow ( sc );
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_SPACE_SPLIT :     //  ���� ������.
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
				if ( (sc->Helper.Type>=MODEL_HELPER+2 && sc->Helper.Type<=MODEL_HELPER+4) && !sc->SafeZone )
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_STRIKE );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction(so, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	//^ �渱 ĳ���� ���ϸ��̼� ����
				}
				else
				{
					SetAction ( so, PLAYER_ATTACK_STRIKE );
				}
				sc->AttackTime = 1;
				PlayBuffer ( SOUND_ATTACK_FIRE_BUST );
				break;
				
			case AT_SKILL_BRAND_OF_SKILL:

				g_CharacterRegisterBuff(to, eBuff_AddSkill);	

				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ����
				}
				else
				{
					SetAction ( so, PLAYER_SKILL_HAND1 );
				}
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_ONEFLASH:
				SetAction ( so, PLAYER_ATTACK_ONE_FLASH );
				sc->AttackTime = 1;
				PlayBuffer(SOUND_SKILL_SWORD2);
				break;
				
			case AT_SKILL_STUN:
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
						{
							SetAction ( so, PLAYER_SKILL_VITALITY );
						}
						sc->AttackTime = 1;
						break;
						
			case AT_SKILL_REMOVAL_STUN:
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
						{
							SetAction ( so, PLAYER_ATTACK_REMOVAL );
						}
						
						if ( sc->SkillSuccess )
						{
							UnRegisterBuff( eDeBuff_Stun, to );
						}
						sc->AttackTime = 1;
						break;
						
			case AT_SKILL_INVISIBLE:
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
							SetAction ( so, PLAYER_SKILL_VITALITY );
						//		if ( sc->SkillSuccess )
						//		{
						//		    to->State |= STATE_INVISIBLE;
						//		}
						//		to->State |= STATE_INVISIBLE;
						if ( sc->SkillSuccess )
						{
							if( !g_isCharacterBuff(to, eBuff_Cloaking) )
								{
									if(so != to)
									{
										g_CharacterRegisterBuff(to, eBuff_Cloaking);
									}
								}
						}
						sc->AttackTime = 1;
						break;
						
			case AT_SKILL_REMOVAL_INVISIBLE:
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
							SetAction ( so, PLAYER_ATTACK_REMOVAL );
						if ( sc->SkillSuccess )
						{
							UnRegisterBuff( eBuff_Cloaking, to );
						}
						sc->AttackTime = 1;
						break;
						
			case AT_SKILL_MANA:
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
							SetAction ( so, PLAYER_SKILL_VITALITY );
						if ( sc->SkillSuccess )
						{
							g_CharacterRegisterBuff(so, eBuff_AddMana);

							CreateEffect ( MODEL_MANA_RUNE, so->Position, so->Angle, so->Light );
						}
						sc->AttackTime = 1;
						break;
						
			case AT_SKILL_REMOVAL_BUFF:
				if ( sc->SkillSuccess )
				{
					UnRegisterBuff( eBuff_Attack, to );
					UnRegisterBuff( eBuff_Defense, to );
					UnRegisterBuff( eBuff_HpRecovery, to ); //eBuff_Life
					UnRegisterBuff( eBuff_PhysDefense, to );
					UnRegisterBuff( eBuff_AddCriticalDamage, to );
					UnRegisterBuff( eBuff_AddMana, to );
				}
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				} 
				else
					if( sc->Helper.Type==MODEL_HELPER+2 && !sc->SafeZone)         //  ���ϸ� Ÿ������.
					{
						SetAction(so,PLAYER_SKILL_RIDER);
					}
					else
						if( sc->Helper.Type==MODEL_HELPER+3 && !sc->SafeZone )   //  �䰡�þƸ� Ÿ������.
						{
							SetAction(so,PLAYER_SKILL_RIDER_FLY);
						}
						else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)	// �渱
						{
							SetAction(so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ĳ���� ���ϸ��̼� ���� ����
						}
						else
							SetAction ( so, PLAYER_SKILL_VITALITY );
						sc->AttackTime = 1;
						break;
			case AT_SKILL_IMPROVE_AG:
				if( !g_isCharacterBuff(to, eBuff_AddAG) )
					{
						DeleteEffect ( BITMAP_LIGHT, to, 2 );
						DeleteJoint ( BITMAP_JOINT_HEALING, to, 9 );
						
						CreateEffect ( BITMAP_LIGHT, to->Position, to->Angle, to->Light, 2, to );
					}

					g_CharacterRegisterBuff(to, eBuff_AddAG);		
					
					if(sc != Hero)
					{
						SetPlayerMagic(sc);
						so->AnimationFrame = 0;
					}
					sc->AttackTime = 1;
					break;
			case AT_SKILL_ADD_CRITICAL:
				SetAttackSpeed();

				g_CharacterRegisterBuff(to, eBuff_AddCriticalDamage);  
				
				if ( sc->Helper.Type==MODEL_HELPER+4 && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_ATTACK_MAGIC );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction( so, PLAYER_FENRIR_ATTACK_MAGIC);	//^ �渱 ��ų ����(ĳ���� ���ϸ��̼� ����)
				}
				else
				{
					SetAction ( so, PLAYER_SKILL_HAND1 );
				}
				sc->AttackTime = 1;
				break;
			case AT_SKILL_PARTY_TELEPORT:
				if ( (sc->Helper.Type>=MODEL_HELPER+2 && sc->Helper.Type<=MODEL_HELPER+4) && !sc->SafeZone )
				{
					SetAction ( so, PLAYER_ATTACK_RIDE_TELEPORT );
				}
				else if(sc->Helper.Type == MODEL_HELPER+37 && !sc->SafeZone)
				{
					SetAction(so, PLAYER_FENRIR_ATTACK_DARKLORD_TELEPORT);	//^ �渱 ĳ���� ���ϸ��̼�
				}
				else
				{
					SetAction ( so, PLAYER_ATTACK_TELEPORT );
				}
				if ( so->Type!=MODEL_PLAYER )
				{
					SetPlayerAttack(sc);
					so->AnimationFrame = 0;
				}
				sc->AttackTime = 1;
				break;
			case AT_SKILL_LIFE_UP:
			case AT_SKILL_LIFE_UP+1:
			case AT_SKILL_LIFE_UP+2:
			case AT_SKILL_LIFE_UP+3:
			case AT_SKILL_LIFE_UP+4:
			case AT_SKILL_VITALITY:	// ����������
				if( !g_isCharacterBuff(to, eBuff_HpRecovery) ) //eBuff_Life
				{
					DeleteEffect ( BITMAP_LIGHT, to, 1 );
					
					CreateEffect ( BITMAP_LIGHT, to->Position, to->Angle, to->Light, 1, to );
				}
				
				g_CharacterRegisterBuff(to, eBuff_HpRecovery); //eBuff_Life
				
				SetAction(so,PLAYER_SKILL_VITALITY);
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_RIDER:
				if ( World==WD_8TARKAN || World==WD_10HEAVEN || g_Direction.m_CKanturu.IsMayaScene() )
					SetAction ( so, PLAYER_SKILL_RIDER_FLY );
				else 
					SetAction ( so, PLAYER_SKILL_RIDER );
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_BOSS:
				sc->AttackTime = 1;
				break;
				
			case AT_SKILL_COMBO :
				CreateEffect ( MODEL_COMBO, so->Position, so->Angle, so->Light );
				PlayBuffer(SOUND_COMBO);
				break;
			case AT_SKILL_BLAST_HELL_BEGIN:
				SetAction(so,PLAYER_SKILL_HELL_BEGIN);
				PlayBuffer(SOUND_NUKE1);
				so->m_bySkillCount = 0;
				break;
			case AT_SKILL_BLAST_HELL:
				SetAction(so,PLAYER_SKILL_HELL_START);
				if ( sc==Hero )
				{
					MouseRButtonPop = false;
					MouseRButtonPush= false;
					MouseRButton	= false;
					
					MouseRButtonPress = 0;
				}
				sc->AttackTime = 1;
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_FIRE_SCREAM_UP:
			case AT_SKILL_FIRE_SCREAM_UP+1:
			case AT_SKILL_FIRE_SCREAM_UP+2:
			case AT_SKILL_FIRE_SCREAM_UP+3:
			case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_DARK_SCREAM:		//  ��ũ�ε� ���οų
				{
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if( sc->Helper.Type == MODEL_HELPER+37 )				
					{
						SetAction( so, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
					}
#ifdef PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) && (sc->Helper.Type<=MODEL_HELPER+4))
#else //PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) || (sc->Helper.Type<=MODEL_HELPER+4))
#endif //PBG_FIX_CHAOTIC_ANIMATION
					{
						SetAction( so, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
					}
					else
					{
						SetAction( so, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
					}
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if(sc->Helper.Type == MODEL_HELPER+37)
						SetAction(so,PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	//^ �渱
					else
						SetAction ( so, PLAYER_ATTACK_STRIKE );
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					PlayBuffer(SOUND_FIRE_SCREAM);
				}
				break;
			case AT_SKILL_EXPLODE:
				{
					vec3_t Pos;
					float addx,addz;
					for(int iaa = 0; iaa < 3; iaa++)
					{
						addx = rand()%160;
						addz = rand()%160;
						Vector(to->Position[0]+addx,to->Position[1]+addz,to->Position[2], Pos);
						
						CreateBomb(Pos,true);
					}
				}
				break;
			case AT_SKILL_INFINITY_ARROW:
				{
					CharacterMachine->InfinityArrowAdditionalMana = 10;
					CreateEffect(MODEL_INFINITY_ARROW, so->Position, so->Angle, so->Light, 0, so);
					PlayBuffer(SOUND_INFINITYARROW);
				}	
				break;
#ifdef PJH_ADD_MASTERSKILL
			case AT_SKILL_ALICE_CHAINLIGHTNING_UP:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+1:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+2:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+3:
		case AT_SKILL_ALICE_CHAINLIGHTNING_UP+4:
#endif
			case AT_SKILL_ALICE_CHAINLIGHTNING:
				{
					sc->AttackTime = 1;
					PlayBuffer(SOUND_SKILL_CHAIN_LIGHTNING);
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
			case AT_SKILL_ALICE_THORNS:
#ifdef ASG_ADD_SKILL_BERSERKER
			case AT_SKILL_ALICE_BERSERKER:
#endif	// ASG_ADD_SKILL_BERSERKER
				{
					sc->AttackTime = 1;
					
					// ���� ����
					switch(sc->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(so, PLAYER_SKILL_SLEEP_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(so, PLAYER_SKILL_SLEEP_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(so, PLAYER_SKILL_SLEEP_FENRIR);
						break;
					default:	// �⺻
						SetAction(so, PLAYER_SKILL_SLEEP);
						break;
					}
					
					// ����
					if(MagicNumber == AT_SKILL_ALICE_SLEEP
#ifdef PJH_ADD_MASTERSKILL
						|| (AT_SKILL_ALICE_SLEEP_UP <= MagicNumber && MagicNumber <= AT_SKILL_ALICE_SLEEP_UP+4)
#endif
						) 
					{
							PlayBuffer(SOUND_SUMMON_SKILL_SLEEP);
					}
					else
					if(MagicNumber == AT_SKILL_ALICE_BLIND) 
					{
						PlayBuffer(SOUND_SUMMON_SKILL_BLIND);
					}
					else
					{
						PlayBuffer(SOUND_SUMMON_SKILL_THORNS);
					}
				}
				break;

#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER		// ��������
			case AT_SKILL_SWELL_OF_MAGICPOWER:
				{
					SetAttackSpeed();
					SetAction( so, PLAYER_SKILL_SWELL_OF_MP );
								
					vec3_t vLight;
					Vector( 0.3f, 0.2f, 0.9f, vLight );
					CreateEffect( MODEL_SWELL_OF_MAGICPOWER, so->Position, so->Angle, vLight, 0, so );
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
					PlayBuffer(SOUND_SKILL_SWELL_OF_MAGICPOWER);
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
				}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
			case AT_SKILL_DOPPELGANGER_SELFDESTRUCTION:
				{
					SetAction(so, MONSTER01_APEAR);
					so->m_bActionStart = FALSE;
				}
				break;
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef LDK_MOD_EVERY_USE_SKILL_CAOTIC
			case AT_SKILL_GAOTIC:
				{
					if(so->Type == MODEL_PLAYER)
					{
						if( sc->Helper.Type == MODEL_HELPER+37 )				
						{
							SetAction( &sc->Object, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
						}
						else if((sc->Helper.Type>=MODEL_HELPER+2) && (sc->Helper.Type<=MODEL_HELPER+4))
						{
							SetAction( &sc->Object, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
						}
						else
						{
							SetAction( &sc->Object, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
						}
					}
					else
					{
						SetPlayerAttack ( sc );
					}
					
					OBJECT* o = so;
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
					if(sc==Hero && SelectedCharacter!=-1)
					{
						vec3_t Pos;
						CHARACTER *st = &CharactersClient[SelectedCharacter];
						VectorCopy(st->Object.Position,Pos);
						CreateBomb(Pos,true);
					}
					PlayBuffer(SOUND_SKILL_CAOTIC);
				}
				break;
#endif //LDK_MOD_EVERY_USE_SKILL_CAOTIC
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case AT_SKILL_THRUST:
		{
			g_CMonkSystem.SetRageSkillAni(MagicNumber, so);
			so->m_sTargetIndex = TargetIndex;
			sc->AttackTime = 1;

			if(sc != Hero)
			{
				g_CMonkSystem.RageCreateEffect(so, MagicNumber);
			}
		}
		break;
	case AT_SKILL_ATT_UP_OURFORCES:
	case AT_SKILL_HP_UP_OURFORCES:
	case AT_SKILL_DEF_UP_OURFORCES:
		{
			if(sc == Hero)
			{
				if(so->CurrentAction == PLAYER_SKILL_ATT_UP_OURFORCES)
				{
					SendRequestAction(AT_RAGEBUFF_1, ((BYTE)((so->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				}
				else
				{
					SendRequestAction(AT_RAGEBUFF_2, ((BYTE)((so->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				}
			}
			OBJECT *_pObj = to;
			if(sc != Hero)
			{
				_pObj = so;
				g_CMonkSystem.RageCreateEffect(_pObj, MagicNumber);
			}

			if(MagicNumber==AT_SKILL_HP_UP_OURFORCES)
			{
				DeleteEffect(BITMAP_LIGHT_RED, _pObj, 0);
				CreateEffect(BITMAP_LIGHT_RED, _pObj->Position, _pObj->Angle, _pObj->Light, 0, _pObj,-1,0,0,0,1.5f);
			}
			else if(MagicNumber==AT_SKILL_DEF_UP_OURFORCES)
			{
				DeleteEffect(BITMAP_LIGHT_RED, _pObj, 2);
				CreateEffect(BITMAP_LIGHT_RED, _pObj->Position, _pObj->Angle, _pObj->Light, 2, _pObj,-1,0,0,0,1.5f);

				vec3_t vLight;
				Vector(0.7f, 0.7f,1.0f,vLight);
				DeleteEffect(MODEL_WINDFOCE, _pObj, 1);
				CreateEffect(MODEL_WINDFOCE, _pObj->Position, _pObj->Angle, vLight, 1, _pObj, -1, 0, 0, 0, 1.0f);
			}
			else if(MagicNumber==AT_SKILL_ATT_UP_OURFORCES)
			{
				DeleteEffect(BITMAP_LIGHT_RED, _pObj, 1);
				CreateEffect(BITMAP_LIGHT_RED, _pObj->Position, _pObj->Angle, _pObj->Light, 1, _pObj,-1,0,0,0,1.5f);
			}

			switch(MagicNumber)
			{
			case AT_SKILL_ATT_UP_OURFORCES:
				g_CharacterRegisterBuff(_pObj, eBuff_Att_up_Ourforces);
				break;
			case AT_SKILL_HP_UP_OURFORCES:
				g_CharacterRegisterBuff(_pObj, eBuff_Hp_up_Ourforces);
				break;
			case AT_SKILL_DEF_UP_OURFORCES:
				g_CharacterRegisterBuff(_pObj, eBuff_Def_up_Ourforces);
				break;
			}
			sc->AttackTime = 1;
		}
		break;
	case AT_SKILL_STAMP:
		{
			sc->AttackTime = 1;
		}
		break;
	case AT_SKILL_GIANTSWING:
	case AT_SKILL_DRAGON_KICK:
		{
			sc->AttackTime = 1;
			if(sc != Hero)
				g_CMonkSystem.RageCreateEffect(so, MagicNumber);
		}
		break;
	case AT_SKILL_OCCUPY:
		{
			SetAction(so, PLAYER_ATTACK_RUSH);
			sc->AttackTime = 1;
			PlayBuffer(SOUND_SKILL_SWORD2);
		}
		break;
	case AT_SKILL_DRAGON_LOWER:
		{
			vec3_t vLight;
			Vector(1.0f, 1.0f, 1.0f, vLight);
			if(g_CMonkSystem.SetLowerEffEct())
			{
				CreateEffect(MODEL_VOLCANO_OF_MONK, to->Position, to->Angle, vLight, g_CMonkSystem.GetLowerEffCnt(), to, -1, 0, 0, 0, 0.8f);
			}

			CreateEffect(MODEL_TARGETMON_EFFECT, to->Position, to->Angle, vLight, 0, to, -1, 0, 0, 0, 1.0f);
#ifdef PBG_MOD_RAGEFIGHTERSOUND
			StopBuffer(SOUND_RAGESKILL_DRAGONLOWER_ATTACK, true);
#endif //PBG_MOD_RAGEFIGHTERSOUND
			PlayBuffer(SOUND_RAGESKILL_DRAGONLOWER_ATTACK);
		}
		break;
	case AT_SKILL_DARKSIDE:
		{
			if(sc != Hero)
				g_CMonkSystem.SetDarksideCnt();
		}
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x19����[ReceiveMagic(%d)]", MagicNumber);
#endif // CONSOLE_DEBUG
	
	return ( TRUE);
}

BOOL ReceiveMagicContinue(BYTE *ReceiveBuffer,int Size, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x1E);
		return ( FALSE);
	}
	
	LPPRECEIVE_MAGIC_CONTINUE Data = (LPPRECEIVE_MAGIC_CONTINUE)ReceiveBuffer;
	int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
	WORD MagicNumber = ((WORD)(Data->MagicH )<<8) + Data->MagicL;
	
	CHARACTER *sc = &CharactersClient[FindCharacterIndex(Key)];
	OBJECT *so = &sc->Object;
	
	sc->Skill = MagicNumber;

	
	so->Angle[2] = (Data->Angle/255.f)*360.f;
	
	if(so->Type == MODEL_PLAYER)
	{
		if(sc != Hero)
		{
			switch(MagicNumber)
			{
			case AT_SKILL_MANY_ARROW_UP:
			case AT_SKILL_MANY_ARROW_UP+1:
			case AT_SKILL_MANY_ARROW_UP+2:
			case AT_SKILL_MANY_ARROW_UP+3:
			case AT_SKILL_MANY_ARROW_UP+4:
			case AT_SKILL_CROSSBOW:
				SetPlayerAttack(sc);
				break;
			case AT_SKILL_BLAST_CROSSBOW4:
				SetPlayerAttack(sc);
				break;
			case AT_SKILL_BLAST_POISON:
			case AT_SKILL_ICE_UP:
			case AT_SKILL_ICE_UP+1:
			case AT_SKILL_ICE_UP+2:
			case AT_SKILL_ICE_UP+3:
			case AT_SKILL_ICE_UP+4:
			case AT_SKILL_BLAST_FREEZE:
				SetPlayerMagic(sc);
				break;
				
            case AT_SKILL_PIERCING:
                SetPlayerAttack(sc);
                break;
				
			case AT_SKILL_FLASH:
				SetAction(so,PLAYER_SKILL_FLASH);
				break;
				
			case AT_SKILL_HELL_FIRE_UP:
			case AT_SKILL_HELL_FIRE_UP+1:
			case AT_SKILL_HELL_FIRE_UP+2:
			case AT_SKILL_HELL_FIRE_UP+3:
			case AT_SKILL_HELL_FIRE_UP+4:
			case AT_SKILL_HELL:
				SetAction(so,PLAYER_SKILL_HELL);
				break;
				
			case AT_SKILL_INFERNO:
				SetAction(so,PLAYER_SKILL_INFERNO);
				break;
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
			case AT_SKILL_WHEEL:
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
				switch(sc->Helper.Type)
				{
				case MODEL_HELPER+2:	// ���ϸ���
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_UNI);
					break;
				case MODEL_HELPER+3:	// ����Ʈ
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_DINO);
					break;
				case MODEL_HELPER+37:	// �渱	
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
					break;
				default:	// �⺻
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL);
					break;
				}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
				SetAction(so,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
                break;
				
				// ��ũ�ε� ��ų ���̾� ��ũ��
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_FIRE_SCREAM_UP:
			case AT_SKILL_FIRE_SCREAM_UP+1:
			case AT_SKILL_FIRE_SCREAM_UP+2:
			case AT_SKILL_FIRE_SCREAM_UP+3:
			case AT_SKILL_FIRE_SCREAM_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_DARK_SCREAM:
				{
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if( sc->Helper.Type == MODEL_HELPER+37 )				
					{
						SetAction( so, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
					}
#ifdef PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) && (sc->Helper.Type<=MODEL_HELPER+4))
#else //PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) || (sc->Helper.Type<=MODEL_HELPER+4))
#endif //PBG_FIX_CHAOTIC_ANIMATION
					{
						SetAction( so, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
					}
					else
					{
						SetAction( so, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
					}
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if(sc->Helper.Type == MODEL_HELPER+37)
						SetAction(so,PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	
					else
						SetAction ( so, PLAYER_ATTACK_STRIKE );
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					// ����
					PlayBuffer(SOUND_FIRE_SCREAM);
				}
				break;
				
            case AT_SKILL_THUNDER_STRIKE:
				if(sc->Helper.Type == MODEL_HELPER+37)	//^ �渱
					SetAction(so,PLAYER_FENRIR_ATTACK_DARKLORD_FLASH);	
				else
					SetAction ( so, PLAYER_SKILL_FLASH );
                break;
			case AT_SKILL_ASHAKE_UP:
			case AT_SKILL_ASHAKE_UP+1:
			case AT_SKILL_ASHAKE_UP+2:
			case AT_SKILL_ASHAKE_UP+3:
			case AT_SKILL_ASHAKE_UP+4:
            case AT_SKILL_DARK_HORSE:       //  ��ũȦ�� ��ų.
                SetAction ( so, PLAYER_ATTACK_DARKHORSE );
                PlayBuffer ( SOUND_EARTH_QUAKE );
                break;
				
				//----------------------------------------------------------------------------------------------------
				
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ANGER_SWORD_UP:
			case AT_SKILL_ANGER_SWORD_UP+1:
			case AT_SKILL_ANGER_SWORD_UP+2:
			case AT_SKILL_ANGER_SWORD_UP+3:
			case AT_SKILL_ANGER_SWORD_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
            case AT_SKILL_FURY_STRIKE:	// �г��� �ϰ�
				SetAction(so,PLAYER_ATTACK_SKILL_FURY_STRIKE);
                break;
				
				//----------------------------------------------------------------------------------------------------
				
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
				// ���� - �ı��� �ϰ�
			case AT_SKILL_BLOW_OF_DESTRUCTION:
				SetAction(so,PLAYER_SKILL_BLOW_OF_DESTRUCTION);
				break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
				
				//----------------------------------------------------------------------------------------------------
				
				
				//----------------------------------------------------------------------------------------------------
				
			case AT_SKILL_SPEAR:	// â���
				if(sc->Helper.Type == MODEL_HELPER+37)
					SetAction(so, PLAYER_FENRIR_ATTACK_SPEAR);	//^ �渱 ��ų ����
				else
					SetAction(so,PLAYER_ATTACK_SKILL_SPEAR);
				break;
				
				//----------------------------------------------------------------------------------------------------
				
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOOD_ATT_UP:
			case AT_SKILL_BLOOD_ATT_UP+1:
			case AT_SKILL_BLOOD_ATT_UP+2:
			case AT_SKILL_BLOOD_ATT_UP+3:
			case AT_SKILL_BLOOD_ATT_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_REDUCEDEFENSE:
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
				switch(sc->Helper.Type)
				{
				case MODEL_HELPER+2:	// ���ϸ���
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_UNI);
					break;
				case MODEL_HELPER+3:	// ����Ʈ
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_DINO);
					break;
				case MODEL_HELPER+37:	// �渱	
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL_FENRIR);
					break;
				default:	// �⺻
					SetAction(so, PLAYER_ATTACK_SKILL_WHEEL);
					break;
				}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
				SetAction(so,PLAYER_ATTACK_SKILL_WHEEL);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_POWER_SLASH_UP:
			case AT_SKILL_POWER_SLASH_UP+1:
			case AT_SKILL_POWER_SLASH_UP+2:
			case AT_SKILL_POWER_SLASH_UP+3:
			case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
            case AT_SKILL_ICE_BLADE:
				SetAction(so,PLAYER_ATTACK_TWO_HAND_SWORD_TWO);
				break;
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_BLOW_UP:
			case AT_SKILL_BLOW_UP+1:
			case AT_SKILL_BLOW_UP+2:
			case AT_SKILL_BLOW_UP+3:
			case AT_SKILL_BLOW_UP+4:
#endif	//PJH_SEASON4_MASTER_RANK4
            case AT_SKILL_ONETOONE:	// ��ο�
				SetAction(so,PLAYER_ATTACK_ONETOONE);
                break;
				
            case AT_SKILL_STUN:
                SetAction ( so, PLAYER_SKILL_VITALITY );
                break;
                
            case AT_SKILL_INVISIBLE:
                SetAction ( so, PLAYER_SKILL_VITALITY );
                break;
				
			case AT_SKILL_PLASMA_STORM_FENRIR:
				SetAction_Fenrir_Skill(sc, so);	//^ �渱 ��ų ����
				break;
				
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
			case AT_SKILL_GAOTIC:
				{
#ifdef KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if( sc->Helper.Type == MODEL_HELPER+37 )				
					{
						SetAction( &sc->Object, PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE );		// �Ҹ�����
					}
#ifdef PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) && (sc->Helper.Type<=MODEL_HELPER+4))
#else //PBG_FIX_CHAOTIC_ANIMATION
					else if((sc->Helper.Type>=MODEL_HELPER+2) || (sc->Helper.Type<=MODEL_HELPER+4))
#endif //PBG_FIX_CHAOTIC_ANIMATION
					{
						SetAction( &sc->Object, PLAYER_ATTACK_RIDE_STRIKE );		// Ż������ (��ũȣ������)
					}
					else
					{
						SetAction( &sc->Object, PLAYER_ATTACK_STRIKE );				// �Ϲݰ���
					}
#else // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET
					if(sc->Helper.Type == MODEL_HELPER+37)
						SetAction(so,PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE);	//^ �渱
					else
						SetAction ( so, PLAYER_ATTACK_STRIKE );
#endif // KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET

					OBJECT* o = so;
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
					if(sc==Hero && SelectedCharacter!=-1)
					{
						vec3_t Pos;
						CHARACTER *st = &CharactersClient[SelectedCharacter];
						VectorCopy(st->Object.Position,Pos);
						CreateBomb(Pos,true);
					}
#endif //PJH_FIX_CAOTIC
					PlayBuffer(SOUND_SKILL_CAOTIC);
				}
				break;
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
			case AT_SKILL_MULTI_SHOT:
				{
					SetPlayerBow(sc);
					OBJECT* o = so;
					vec3_t Light,Position,P,dp;

					
#ifdef PJH_SEASON4_FIX_MULTI_SHOT
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
						if(tc == sc)
						{
							Key = i;
							break;
						}
					}

					CreateEffect(MODEL_BLADE_SKILL, Position, o->Angle, Light, 1, o, Key);
#else	//PJH_SEASON4_FIX_MULTI_SHOT

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
					vec3_t Angle;

					VectorCopy(o->Angle,Angle);
					CreateArrow(sc,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] + 8.f;
					CreateArrow(sc,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] + 16.f;
					CreateArrow(sc,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] - 8.f;
					CreateArrow(sc,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2] - 16.f;
					CreateArrow(sc,o,to,FindHotKey(( o->Skill)),1,0);
					o->Angle[2] = Angle[2];
					PlayBuffer(SOUND_SKILL_MULTI_SHOT);
#endif //PJH_SEASON4_FIX_MULTI_SHOT
				}
				break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			case AT_SKILL_RECOVER:
				{
					//			OBJECT* o = so;
					vec3_t Light,Position,P,dp;
					vec3_t vFirePosition;
					
					float Matrix[3][4];
					/*
					Vector(0.f,-220.f,130.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					Vector(0.7f, 0.6f, 0.f, Light);
					CreateEffect(BITMAP_IMPACT, Position, o->Angle, Light, 0,o);
					SetAction(o,PLAYER_RECOVER_SKILL);
					
					  
					*/
					OBJECT* o = so;
					
					Vector(0.4f, 0.6f, 1.f, Light);
					Vector(0.f,0.f,0.f,P);
					AngleMatrix(o->Angle,Matrix);
					VectorRotate(P,Matrix,dp);
					VectorAdd(dp,o->Position,Position);
					Position[2] += 130;
					VectorCopy( o->Position, Position);
					for ( int i=0; i<19; ++i )
					{
						CreateJoint(BITMAP_FLARE,Position,Position,o->Angle,47,o,40,2);
					}
					Vector ( 0.3f, 0.2f, 0.1f, Light );
					CreateEffect(MODEL_SUMMON,Position,o->Angle,Light, 0);
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 0 );
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 1 );
					CreateEffect ( BITMAP_TWLIGHT, Position, o->Angle, Light, 2 );
					
					
#ifdef _VS2008PORTING
					for (int i = 0; i < 2; ++i)
#else // _VS2008PORTING
					for (i = 0; i < 2; ++i)
#endif // _VS2008PORTING
					{
						int iNumBones = Models[o->Type].NumBones;
						Models[o->Type].TransformByObjectBone(vFirePosition, o, rand()%iNumBones);	
						CreateEffect(BITMAP_FLARE, vFirePosition, o->Angle, Light,3);
					}
					PlayBuffer(SOUND_SKILL_RECOVER);
				}
				break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
				
				
			case AT_SKILL_ALICE_LIGHTNINGORB:
				{
					switch(sc->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(so, PLAYER_SKILL_LIGHTNING_ORB_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(so, PLAYER_SKILL_LIGHTNING_ORB_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(so, PLAYER_SKILL_LIGHTNING_ORB_FENRIR);
						break;
					default:	// �⺻
						SetAction(so, PLAYER_SKILL_LIGHTNING_ORB);
						break;
					}
				}
				break;
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_ALICE_DRAINLIFE_UP:
		case AT_SKILL_ALICE_DRAINLIFE_UP+1:
		case AT_SKILL_ALICE_DRAINLIFE_UP+2:
		case AT_SKILL_ALICE_DRAINLIFE_UP+3:
		case AT_SKILL_ALICE_DRAINLIFE_UP+4:
#endif				
			case AT_SKILL_ALICE_DRAINLIFE:		// Drain Life (�巹�� ������)
				{
					switch(sc->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(so, PLAYER_SKILL_DRAIN_LIFE_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(so, PLAYER_SKILL_DRAIN_LIFE_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(so, PLAYER_SKILL_DRAIN_LIFE_FENRIR);
						break;
					default:	// �⺻
						SetAction(so, PLAYER_SKILL_DRAIN_LIFE);
						break;
					}
				}
				break;
				
				// ReceiveChainMagic() ���� SetAction���־����Ƿ� �����־ ��.
				// 			case AT_SKILL_ALICE_CHAINLIGHTNING:
				// 				SetAction(so, PLAYER_SKILL_CHAIN_LIGHTNING);
				// 				break;
				
			case AT_SKILL_ALICE_WEAKNESS:
			case AT_SKILL_ALICE_ENERVATION:
				// ���� ����
				switch(sc->Helper.Type)
				{
				case MODEL_HELPER+2:	// ���ϸ���
					SetAction(so, PLAYER_SKILL_SLEEP_UNI);
					break;
				case MODEL_HELPER+3:	// ����Ʈ
					SetAction(so, PLAYER_SKILL_SLEEP_DINO);
					break;
				case MODEL_HELPER+37:	// �渱	
					SetAction(so, PLAYER_SKILL_SLEEP_FENRIR);
					break;
				default:	// �⺻
					SetAction(so, PLAYER_SKILL_SLEEP);
					break;
				}
				break;
					
			case AT_SKILL_SUMMON_EXPLOSION:
			case AT_SKILL_SUMMON_REQUIEM:
#ifdef ASG_ADD_SUMMON_RARGLE
			case AT_SKILL_SUMMON_POLLUTION:
#endif	// ASG_ADD_SUMMON_RARGLE
				{
					g_SummonSystem.CastSummonSkill(MagicNumber, sc, so, Data->PositionX, Data->PositionY);
				}
				break;
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
				case AT_SKILL_FLAME_STRIKE:
					SetAction(so, PLAYER_SKILL_FLAMESTRIKE);
					break;
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
				case AT_SKILL_GIGANTIC_STORM:
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
					switch(sc->Helper.Type)
					{
					case MODEL_HELPER+2:	// ���ϸ���
						SetAction(so, PLAYER_SKILL_GIGANTICSTORM_UNI);
						break;
					case MODEL_HELPER+3:	// ����Ʈ
						SetAction(so, PLAYER_SKILL_GIGANTICSTORM_DINO);
						break;
					case MODEL_HELPER+37:	// �渱	
						SetAction(so, PLAYER_SKILL_GIGANTICSTORM_FENRIR);
						break;
					default:	// �⺻
						SetAction(so, PLAYER_SKILL_GIGANTICSTORM);
						break;
					}
#else	// YDG_ADD_SKILL_RIDING_ANIMATIONS
					SetAction(so, PLAYER_SKILL_GIGANTICSTORM);
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
					break;
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef PJH_ADD_MASTERSKILL
		case AT_SKILL_LIGHTNING_SHOCK_UP:
		case AT_SKILL_LIGHTNING_SHOCK_UP+1:
		case AT_SKILL_LIGHTNING_SHOCK_UP+2:
		case AT_SKILL_LIGHTNING_SHOCK_UP+3:
		case AT_SKILL_LIGHTNING_SHOCK_UP+4:
#endif
				case AT_SKILL_LIGHTNING_SHOCK:
					SetAction(so, PLAYER_SKILL_LIGHTNING_SHOCK);
					break;
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
				case AT_SKILL_DRAGON_LOWER:
				{
					if(sc != Hero)
						g_CMonkSystem.RageCreateEffect(so, MagicNumber);

					g_CMonkSystem.SetRageSkillAni(MagicNumber, so);
				}
				break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
				default:
					SetPlayerMagic(sc);
					break;
			}
			so->AnimationFrame = 0;
		}
	}
	else
	{
		SetPlayerAttack(sc);
		so->AnimationFrame = 0;
	}
	sc->AttackTime = 1;
	sc->TargetCharacter = -1;
	sc->AttackFlag = ATTACK_FAIL;
	sc->SkillX = Data->PositionX;
	sc->SkillY = Data->PositionY;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x1E����[ReceiveMagicContinue(%d)]", MagicNumber);
#endif // CONSOLE_DEBUG
	
	return ( TRUE);
}

// ChainLightning (ü�� ����Ʈ��)
// ������ ü�ζ���Ʈ�� ��ų ������ ������ ���� �޴� ��Ŷ
void ReceiveChainMagic( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_CHAIN_MAGIC pPacketData = (LPPRECEIVE_CHAIN_MAGIC)ReceiveBuffer;
	
	// ���ΰ� ĳ����
	CHARACTER* pSourceChar = &CharactersClient[FindCharacterIndex(pPacketData->wUserIndex)];
	OBJECT* pSourceObject = &pSourceChar->Object;
	OBJECT* pTempObject = NULL;
	
	//SetAction(pSourceObject, PLAYER_SKILL_CHAIN_LIGHTNING);
	
	switch(pSourceChar->Helper.Type)
	{
	case MODEL_HELPER+2:	// ���ϸ���
		SetAction(pSourceObject, PLAYER_SKILL_CHAIN_LIGHTNING_UNI);
		break;
	case MODEL_HELPER+3:	// ����Ʈ
		SetAction(pSourceObject, PLAYER_SKILL_CHAIN_LIGHTNING_DINO);
		break;
	case MODEL_HELPER+37:	// �渱	
		SetAction(pSourceObject, PLAYER_SKILL_CHAIN_LIGHTNING_FENRIR);
		break;
	default:	// �⺻
		SetAction(pSourceObject, PLAYER_SKILL_CHAIN_LIGHTNING);
		break;
	}	
	
	pSourceChar->Skill = ((WORD)(pPacketData->MagicH)<<8) + pPacketData->MagicL;
	
	pTempObject = pSourceObject; 
	
	int iOffset = sizeof( PRECEIVE_CHAIN_MAGIC );
	for(int i=0 ; i<(int)(pPacketData->byCount) ; i++)
	{
		LPPRECEIVE_CHAIN_MAGIC_OBJECT pPacketData2 = (LPPRECEIVE_CHAIN_MAGIC_OBJECT)(ReceiveBuffer+iOffset);
		// Ÿ�� �ε��� ����
		CHARACTER *pTargetChar = &CharactersClient[FindCharacterIndex(pPacketData2->wTargetIndex)];
		OBJECT *pTargetObject = &pTargetChar->Object;
		
		if( pTempObject != pTargetObject && pTargetObject != NULL && pTargetObject->Live == true)
		{	
			// ����Ʈ �ٷ� ����
			// ����Ʈ�� (���������� ���� �ʿ�)
			vec3_t vAngle;
			Vector( -60.f, 0.f, pSourceObject->Angle[2], vAngle);
			
			//SetPlayerStop(pTargetChar);
			
			// ����Ʈ��
			CreateEffect( MODEL_CHAIN_LIGHTNING, pSourceObject->Position, vAngle, pSourceObject->Light, i, 
				pTempObject, -1, 0, 0, 0, 0.f, pPacketData2->wTargetIndex );
		}
		
		pTempObject = pTargetObject;
		
		iOffset += sizeof( PRECEIVE_CHAIN_MAGIC_OBJECT );
	}
}

void ReceiveMagicPosition(BYTE *ReceiveBuffer,int Size)
{
	LPPRECEIVE_MAGIC_POSITIONS Data = (LPPRECEIVE_MAGIC_POSITIONS)ReceiveBuffer;
	int SourceKey = ((int)(Data->KeyH )<<8) + Data->KeyL;
	WORD MagicNumber = ((WORD)(Data->MagicH)<<8) + Data->MagicL;
	int Index = FindCharacterIndex(SourceKey);
	AttackPlayer = Index;
	
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	CreateMagicShiny(c);
	PlayBuffer(SOUND_MAGIC);
	SetAction(o,PLAYER_SKILL_HELL);
	c->Skill = MagicNumber;
	c->AttackTime = 1;
	
	int Offset = sizeof(PRECEIVE_MAGIC_POSITIONS);
	for(int i=0;i<Data->Count;i++)
	{
		LPPRECEIVE_MAGIC_POSITION Data2 = (LPPRECEIVE_MAGIC_POSITION)(ReceiveBuffer+Offset);
		int TargetKey = ((int)(Data2->KeyH)<<8) + Data2->KeyL;
		CHARACTER *tc = &CharactersClient[FindCharacterIndex(TargetKey)];
		OBJECT *to = &tc->Object;
		if(rand()%2==0)
			SetPlayerShock(tc,tc->Hit);
		if(tc->Hit > 0)
		{
			vec3_t Light;
			Vector(1.f,0.6f,0.f,Light);
			CreatePoint(to->Position,tc->Hit,Light);
			if(TargetKey==HeroKey)
			{
				if(tc->Hit >= CharacterAttribute->Life)
					CharacterAttribute->Life = 0;
				else
					CharacterAttribute->Life -= tc->Hit;
			}
		}
		Offset += sizeof(PRECEIVE_MAGIC_POSITION);
	}
}


//////////////////////////////////////////////////////////////////////////
//	��ų Count.
//////////////////////////////////////////////////////////////////////////
void ReceiveSkillCount ( BYTE* ReceiveBuffer )
{
	LPPRECEIVE_EX_SKILL_COUNT Data = (LPPRECEIVE_EX_SKILL_COUNT)ReceiveBuffer;
	int TargetKey = ((int)(Data->KeyH)<<8) + Data->KeyL;
	CHARACTER *tc = &CharactersClient[FindCharacterIndex(TargetKey)];
	OBJECT *to = &tc->Object;
	
	switch ( Data->m_byType )
	{
	case AT_SKILL_BLAST_HELL_BEGIN:
		break;
		
	case AT_SKILL_BLAST_HELL:
		to->m_bySkillCount = Data->m_byCount;
		break;
	}
}


///////////////////////////////////////////////////////////////////////////////
// �ױ�
///////////////////////////////////////////////////////////////////////////////

// ���� ����
// �Ϲݰ���ġ
BOOL ReceiveDieExp(BYTE *ReceiveBuffer,BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x16);
		return ( FALSE);
	}
	
	LPPRECEIVE_DIE Data = (LPPRECEIVE_DIE)ReceiveBuffer;
	int     Key    = ((int)(Data->KeyH   )<<8) + Data->KeyL;
	DWORD   Exp    = ((DWORD)(Data->ExpH   )<<8) + Data->ExpL;
	int     Damage = ((int)(Data->DamageH)<<8) + Data->DamageL;
	int     Success = (Key>>15);
	Key &= 0x7FFF;
	
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	vec3_t Light;
	Vector(1.f,0.6f,0.f,Light);
	if(Success)
	{
		SetPlayerDie(c);
		CreatePoint(o->Position,Damage,Light);
	}
	else
	{
		Hero->AttackFlag = ATTACK_DIE;
		Hero->Damage = Damage;
		Hero->TargetCharacter = Index;
		CreatePoint(o->Position,Damage,Light);
	}
	c->Dead = true;
	c->Movement = false;
	

	if(IsMasterLevel(Hero->Class) == true)
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			g_pMainFrame->SetPreExp_Wide(Master_Level_Data.lMasterLevel_Experince);
			g_pMainFrame->SetGetExp_Wide(Exp);	
		}
#else //LDK_ADD_SCALEFORM
		g_pMainFrame->SetPreExp_Wide(Master_Level_Data.lMasterLevel_Experince);
		g_pMainFrame->SetGetExp_Wide(Exp);	
#endif //LDK_ADD_SCALEFORM

		// ����ġ ���� (�������ÿ��� ������ ��Ŷ���� ����ġ�� �����ϰ�, ���⼭�� ����ġ�� 0�� ���´�.)
		Master_Level_Data.lMasterLevel_Experince += Exp;
	}
	else
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			g_pMainFrame->SetPreExp(CharacterAttribute->Experience);
			g_pMainFrame->SetGetExp(Exp);
		}
#else //LDK_ADD_SCALEFORM
		g_pMainFrame->SetPreExp(CharacterAttribute->Experience);
		g_pMainFrame->SetGetExp(Exp);
#endif //LDK_ADD_SCALEFORM

		// ����ġ ���� (�������ÿ��� ������ ��Ŷ���� ����ġ�� �����ϰ�, ���⼭�� ����ġ�� 0�� ���´�.)
		CharacterAttribute->Experience += Exp;	
	}
	
	if(Exp > 0)
	{
		
		char Text[100];
		if(IsMasterLevel(Hero->Class) == true)
		{
			sprintf(Text,GlobalText[1750],Exp);
		}
		else
			sprintf(Text,GlobalText[486],Exp);
		g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);	
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x16����[ReceiveDieExp : %d]", Exp);
#endif // CONSOLE_DEBUG	
	
	return ( TRUE);
}

// ������ �����϶�
BOOL ReceiveDieExpLarge(BYTE *ReceiveBuffer,BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x9C);
		return ( FALSE);
	}
	
	LPPRECEIVE_DIE2 Data = (LPPRECEIVE_DIE2)ReceiveBuffer;
	int     Key    = ((int)(Data->KeyH   )<<8) + Data->KeyL;
	DWORD   Exp    = ((DWORD)(Data->ExpH   )<<16) + Data->ExpL;
	int     Damage = ((int)(Data->DamageH)<<8) + Data->DamageL;
	int     Success = (Key>>15);
	Key &= 0x7FFF;
	
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	vec3_t Light;
	Vector(1.f,0.6f,0.f,Light);
	if(Success)
	{
		SetPlayerDie(c);
		CreatePoint(o->Position,Damage,Light);
	}
	else
	{
		Hero->AttackFlag = ATTACK_DIE;
		Hero->Damage = Damage;
		Hero->TargetCharacter = Index;
		CreatePoint(o->Position,Damage,Light);
	}
	c->Dead = true;
	c->Movement = false;

	if(IsMasterLevel(Hero->Class) == true)
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			g_pMainFrame->SetPreExp_Wide(Master_Level_Data.lMasterLevel_Experince);
			g_pMainFrame->SetGetExp_Wide(Exp);	
		}
#else //LDK_ADD_SCALEFORM
		g_pMainFrame->SetPreExp_Wide(Master_Level_Data.lMasterLevel_Experince);
		g_pMainFrame->SetGetExp_Wide(Exp);	
#endif //LDK_ADD_SCALEFORM

		// ����ġ ���� (�������ÿ��� ������ ��Ŷ���� ����ġ�� �����ϰ�, ���⼭�� ����ġ�� 0�� ���´�.)
		Master_Level_Data.lMasterLevel_Experince += Exp;
	}
	else
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			g_pMainFrame->SetPreExp(CharacterAttribute->Experience);
			g_pMainFrame->SetGetExp(Exp);	
		}
#else //LDK_ADD_SCALEFORM
		g_pMainFrame->SetPreExp(CharacterAttribute->Experience);
		g_pMainFrame->SetGetExp(Exp);	
#endif //LDK_ADD_SCALEFORM

		// ����ġ ���� (�������ÿ��� ������ ��Ŷ���� ����ġ�� �����ϰ�, ���⼭�� ����ġ�� 0�� ���´�.)
		CharacterAttribute->Experience += Exp;	
	}
	
	if(Exp > 0)
	{
		char Text[100];

		if(IsMasterLevel(Hero->Class) == true)
		{
			sprintf(Text,GlobalText[1750],Exp);
		}
		else
			sprintf(Text,GlobalText[486],Exp);
		g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
	}
	
	return ( TRUE);
}


void FallingStartCharacter ( CHARACTER* c, OBJECT* o )
{
    //  ƨ�ܼ� ����߸���.
    BYTE positionX = (BYTE)(o->Position[0]/TERRAIN_SCALE);
    BYTE positionY = (BYTE)(o->Position[1]/TERRAIN_SCALE);
    int WallIndex = TERRAIN_INDEX_REPEAT( positionX, positionY );
    int Wall = TerrainWall[WallIndex]&TW_ACTION;
	
    o->m_bActionStart = false;
	
    if ( InChaosCastle()==true && (TerrainWall[WallIndex]&TW_NOGROUND)==TW_NOGROUND )
    {
        c->StormTime = 0;
        o->m_bActionStart = true;
        o->Gravity  = rand()%10+10.f;
        o->Velocity-= rand()%3+3.f;
		
        Vector ( 0.f, 0.f, 1.f, o->Direction );
        VectorCopy ( o->Position, o->m_vDeadPosition );
		
        PlayBuffer ( SOUND_CHAOS_FALLING );
    }
    else if ( Wall==TW_ACTION )
    {
        c->StormTime = 0;
        o->m_bActionStart = true;
        o->Gravity = rand()%10+10.f;
        o->Velocity= rand()%20+20.f;
        float angle = rand()%10+85.f;
		
        if ( (TerrainWall[WallIndex+1]&TW_NOGROUND)==TW_NOGROUND )
        {
            Vector ( 0.f, 0.f, -angle, o->m_vDownAngle );
        }
        else if ( (TerrainWall[WallIndex-1]&TW_NOGROUND)==TW_NOGROUND )
        {
            Vector ( 0.f, 0.f, angle, o->m_vDownAngle );
        }
		
        o->Angle[2] = o->m_vDownAngle[2];
        Vector ( rand()%6+8.f, -rand()%2+13.f, 5.f, o->Direction );
        VectorCopy ( o->Position, o->m_vDeadPosition );
    }
	
    if ( c==Hero )
    {
        matchEvent::ClearMatchInfo();
    }
}

//�ٸ��÷��̾ �����ؼ� �ɸ��ͳ� ���� ����
void ReceiveDie(BYTE *ReceiveBuffer,int Size)
{
	LPPHEADER_DEFAULT_DIE Data = (LPPHEADER_DEFAULT_DIE)ReceiveBuffer;
	
    int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
	
	int Index = FindCharacterIndex(Key);
	
	CHARACTER *c = &CharactersClient[Index];
	OBJECT *o = &c->Object;
	c->Dead = true;
	c->Movement = false;

	WORD SkillType = ((int)(Data->MagicH )<<8) + Data->MagicL;

#ifdef CSK_HACK_TEST
	g_pHackTest->ReceiveDie(c, o, SkillType, Key);
#endif // CSK_HACK_TEST
	
	//	���� ��ų.
	c->m_byDieType = SkillType;	//	( 0:�⺻, n:��ų��ȣ ).
	
    //  ���� ĳ������ �״� ���͵��� ����߸���.
    if ( InBloodCastle() == true )
    {
        //  ƨ�ܼ� ����߸���.
        FallingStartCharacter ( c, o );
    }
    else if ( InChaosCastle()==true )
    {
        //  ƨ�ܼ� ����߸���.
        FallingStartCharacter ( c, o );
    }
    else
    {
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
		if (c == Hero && g_PortalMgr.IsPortalUsable())
		{
			g_PortalMgr.SaveRevivePosition();	// ������ ��ġ ����
		}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM

        o->m_bActionStart = false;
		
		//	���� ���� ��ų.
		switch ( SkillType )
		{
		case AT_SKILL_BLAST_HELL:
		case AT_SKILL_COMBO:
			o->m_bActionStart = true;
			c->StormTime= 0;
			o->Velocity	= (rand()%5+10.f)*0.1f;
			o->m_bySkillCount = 0;
			
			Vector ( 0.f, rand()%15+40.f, 0.f, o->Direction );
			VectorCopy ( o->Position, o->m_vDeadPosition );
			break;
		}
		
		if ( SkillType==AT_SKILL_BLAST_HELL || SkillType==AT_SKILL_COMBO )
			{
				int TKey   = ((int)(Data->TKeyH)<<8) + Data->TKeyL;
				int TIndex = FindCharacterIndex ( TKey );
				CHARACTER* tc = &CharactersClient[TIndex];
				OBJECT*    to = &tc->Object;
				
				o->Angle[2] = CreateAngle ( o->Position[0], o->Position[1], to->Position[0], to->Position[1] );
				
				VectorCopy ( o->Angle, o->HeadAngle );
			}
    }
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x17����[ReceiveDie(%d)]", Key);
#endif // CONSOLE_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
// ������
///////////////////////////////////////////////////////////////////////////////

void ReceiveCreateItemViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for(int i=0;i<Data->Value;i++)
	{
		LPPCREATE_ITEM Data2 = (LPPCREATE_ITEM)(ReceiveBuffer+Offset);
		vec3_t Position;
		Position[0]  = (float)(Data2->PositionX+0.5f)*TERRAIN_SCALE;
		Position[1]  = (float)(Data2->PositionY+0.5f)*TERRAIN_SCALE;
		int Key      = ((int)(Data2->KeyH )<<8) + Data2->KeyL;
		int CreateFlag = (Key>>15);
		Key &= 0x7FFF;
		if(Key<0 || Key>=MAX_ITEMS)
			Key = 0;
		CreateItem(&Items[Key],Data2->Item,Position,CreateFlag);
		int Type = ConvertItemType(Data2->Item);
		if(Type==ITEM_POTION+15)//��
		{
			Offset += sizeof(PCREATE_ITEM);
		}
		else//������
		{
			Offset += sizeof(PCREATE_ITEM);
		}
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x20����[ReceiveCreateItemViewport]");
#endif // CONSOLE_DEBUG
}

void ReceiveDeleteItemViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for(int i=0;i<Data->Value;i++)
	{
		LPPDELETE_CHARACTER Data2 = (LPPDELETE_CHARACTER)(ReceiveBuffer+Offset);
		int Key = ((int)(Data2->KeyH)<<8) + Data2->KeyL;
		if(Key<0 || Key>=MAX_ITEMS)
			Key = 0;
		Items[Key].Object.Live = false;
		Offset += sizeof(PDELETE_CHARACTER);
	}
}

static  const   BYTE    NOT_GET_ITEM = 0xff;    //  ������ ����.
static  const   BYTE    GET_ITEM_ZEN = 0xfe;    //  ���� �޴´�.
static  const   BYTE    GET_ITEM_MULTI=0xfd;    //  �ߺ��Ǵ� �������� �޴´�.
extern int ItemKey;		// �� ������ ����⿡�� ����� ����
void ReceiveGetItem( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_GET_ITEM Data = (LPPRECEIVE_GET_ITEM)ReceiveBuffer;
	if ( Data->Result==NOT_GET_ITEM )
	{	// ���� �� ���� �޽��� ǥ�� �ʿ�
	}
	else
	{
		if ( Data->Result==GET_ITEM_ZEN )
		{
			char szMessage[128];
			int backupGold = CharacterMachine->Gold;
			CharacterMachine->Gold = (Data->Item[0]<<24) + (Data->Item[1]<<16) + (Data->Item[2]<<8) + (Data->Item[3]);
#ifdef KJH_FIX_GET_ZEN_SYSTEM_TEXT
			int getGold = CharacterMachine->Gold - backupGold;
			
			if( getGold > 0 )
			{
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
				sprintf(szMessage, "%s %d %s", GlobalText[918], getGold, GlobalText[224]);
#else //SELECTED_LANGUAGE == LANGUAGE_CHINESE
				sprintf(szMessage, "%d %s %s", getGold, GlobalText[224], GlobalText[918]);
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
				g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_SYSTEM_MESSAGE);
			}
#else // KJH_FIX_GET_ZEN_SYSTEM_TEXT
            //  ������ space�� �ڵ� �Ա�
            if ( Items[ItemKey].Object.Live )
            {
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
				sprintf(szMessage, "%s %d %s", GlobalText[918], Items[ItemKey].Item.Level, GlobalText[224]);
#else //SELECTED_LANGUAGE == LANGUAGE_CHINESE
				sprintf(szMessage, "%d %s %s", Items[ItemKey].Item.Level, GlobalText[224], GlobalText[918]);
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
				g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_SYSTEM_MESSAGE);
			}
#ifdef CSK_EVENT_CHERRYBLOSSOM
			else
			{
				int getGold = CharacterMachine->Gold - backupGold;
				
				if( getGold > 0 )
				{
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
					sprintf(szMessage, "%s %d %s", GlobalText[918], getGold, GlobalText[224]);
#else //SELECTED_LANGUAGE == LANGUAGE_CHINESE
					sprintf(szMessage, "%d %s %s", getGold, GlobalText[224], GlobalText[918]);
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
					g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_SYSTEM_MESSAGE);
				}
			}
#endif //CSK_EVENT_CHERRYBLOSSOM
#endif // KJH_FIX_GET_ZEN_SYSTEM_TEXT
		}
		else
		{
            //  �ߺ��Ǵ� ������. �κ��� �������� ���� �ʰ�, �ʵ忡 �ִ� �������� �����Ѵ�.
            if ( Data->Result!=GET_ITEM_MULTI )
            {
				if(Data->Result >= MAX_EQUIPMENT_INDEX && Data->Result < MAX_MY_INVENTORY_INDEX)
					g_pMyInventory->InsertItem(Data->Result-MAX_EQUIPMENT_INDEX, Data->Item);
            }
			
            //  ������ space�� �ڵ� �Ա�.
            char szItem[64] = {0, };
			int level = (Items[ItemKey].Item.Level>>3)&15;
			GetItemName(Items[ItemKey].Item.Type, level, szItem);
			
			char szMessage[128];
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
			sprintf(szMessage, "%s %s", GlobalText[918], szItem);
#else
			sprintf(szMessage, "%s %s", szItem, GlobalText[918]);
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
			g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_SYSTEM_MESSAGE);			
        }
#ifdef FOR_WORK
		// �� ������ ����� -_-
		Items[ItemKey].Object.Live = false;
#endif
		// ������ �ֿﶧ ������ �Ҹ�
		int Type = ConvertItemType(Data->Item);
		if(Type==ITEM_POTION+13 || Type==ITEM_POTION+14 || Type==ITEM_POTION+16 || Type==ITEM_WING+15 || Type==ITEM_POTION+22 
			|| Type==INDEX_COMPILED_CELE || Type==INDEX_COMPILED_SOUL || Type==ITEM_POTION+31)
			PlayBuffer(SOUND_JEWEL01,&Hero->Object);
		else if(Type == ITEM_POTION+41)
			PlayBuffer(SOUND_JEWEL02,&Hero->Object);
		else
			PlayBuffer(SOUND_GET_ITEM01,&Hero->Object);
	}
    SendGetItem = -1;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x22����[ReceiveGetItem(%d)]", Data->Result);
#endif // CONSOLE_DEBUG
}

void ReceiveDropItem( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_KEY Data = (LPPHEADER_DEFAULT_KEY)ReceiveBuffer;
	if(Data->KeyH)
	{
		if(Data->KeyL < 12)
		{
			g_pMyInventory->UnequipItem(Data->KeyL);
		}
		else
		{
			g_pMyInventory->DeleteItem( Data->KeyL-MAX_EQUIPMENT_INDEX );
		}

		SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
	}
	else
	{
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	}

    SendDropItem = -1;
}


BOOL g_bPacketAfter_EquipmentItem = FALSE;
BYTE g_byPacketAfter_EquipmentItem[256];

void ReceiveTradeExit( BYTE *ReceiveBuffer );

BOOL ReceiveEquipmentItem(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
 	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x16);
		return ( FALSE);
	}
	
	EquipmentItem = false;
	LPPHEADER_DEFAULT_SUBCODE_ITEM Data = (LPPHEADER_DEFAULT_SUBCODE_ITEM)ReceiveBuffer;
	if(Data->SubCode != 255)
	{
		SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
		int iSourceIndex = g_pMyShopInventory->GetSourceIndex();
		if(pPickedItem)
		{
			if(pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())
			{	
				iSourceIndex += MAX_EQUIPMENT_INDEX;
			}
			else if(pPickedItem->GetOwnerInventory() == g_pMyShopInventory->GetInventoryCtrl())
			{
				iSourceIndex += MAX_MY_INVENTORY_INDEX;
			}
		}
		
		if(iSourceIndex >= MAX_MY_INVENTORY_INDEX)
		{
			int price = 0;
			if(GetPersonalItemPrice(iSourceIndex, price, g_IsPurchaseShop))
			{
				RemovePersonalItemPrice(iSourceIndex, g_IsPurchaseShop);
				if(Data->Index >= MAX_MY_INVENTORY_INDEX)
				{
					AddPersonalItemPrice(Data->Index, price, g_IsPurchaseShop);
				}
			}
		}
		
		if(Data->SubCode == 0)
		{
			SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
			
			int itemindex = Data->Index;
			
			if(itemindex >= 0 && itemindex < MAX_EQUIPMENT_INDEX)
			{
				g_pMyInventory->EquipItem(itemindex, Data->Item);
			}
			else if(itemindex >= MAX_EQUIPMENT_INDEX && itemindex < MAX_MY_INVENTORY_INDEX)
			{
				g_pStorageInventory->ProcessStorageItemAutoMoveSuccess();
				itemindex = itemindex - MAX_EQUIPMENT_INDEX;
				g_pMyInventory->InsertItem(itemindex, Data->Item);
			}
			else if(itemindex >= (MAX_EQUIPMENT_INDEX + MAX_INVENTORY) && itemindex < MAX_MY_SHOP_INVENTORY_INDEX)
			{
				itemindex = itemindex - (MAX_EQUIPMENT_INDEX + MAX_INVENTORY);
				g_pMyShopInventory->InsertItem(itemindex, Data->Item);
			}
		}
		else if (1 == Data->SubCode)
		{
			g_pTrade->ProcessToReceiveTradeItems(Data->Index, Data->Item);
		}
		else if (2 == Data->SubCode)
		{
			g_pStorageInventory->ProcessToReceiveStorageItems(Data->Index, Data->Item);
		}
		if(Data->SubCode == 3 || (Data->SubCode >= 5 && Data->SubCode <= 8)
#ifdef CSK_CHAOS_CARD
			|| (Data->SubCode == 9) 
#endif //CSK_CHAOS_CARD
#ifdef CSK_EVENT_CHERRYBLOSSOM
			|| (Data->SubCode == 10)
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef ADD_SOCKET_MIX
			|| (Data->SubCode >= REQUEST_EQUIPMENT_EXTRACT_SEED_MIX && Data->SubCode <= REQUEST_EQUIPMENT_DETACH_SOCKET_MIX)
#endif	// ADD_SOCKET_MIX
			)	// ��� ����
		{
			SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
			if(Data->Index >= 0 && Data->Index < MAX_MIX_INVENTORY)
				g_pMixInventory->InsertItem(Data->Index, Data->Item);
		}
#ifdef LEM_ADD_LUCKYITEM
		else if ( 15 == Data->SubCode || 16 == Data->SubCode )
		{
			g_pLuckyItemWnd->GetResult(1, Data->Index, Data->Item);
		}
#endif // LEM_ADD_LUCKYITEM
		
		PlayBuffer(SOUND_GET_ITEM01);
	}
	else
	{
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
		g_pStorageInventory->ProcessStorageItemAutoMoveFailure();
	}
	
	if ( g_bPacketAfter_EquipmentItem)
	{
		ReceiveTradeExit( g_byPacketAfter_EquipmentItem);
		g_bPacketAfter_EquipmentItem = FALSE;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x24����[ReceiveEquipmentItem(%d %d)]", Data->SubCode, Data->Index);
#endif // CONSOLE_DEBUG
	
	return ( TRUE);
}

void ReceiveModifyItem( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE_ITEM Data = (LPPHEADER_DEFAULT_SUBCODE_ITEM)ReceiveBuffer;
	
	if(SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
		SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
	
	int itemindex = Data->Index - MAX_EQUIPMENT_INDEX;
	if(g_pMyInventory->FindItem(itemindex))
		g_pMyInventory->DeleteItem(itemindex);
	
	g_pMyInventory->InsertItem(itemindex, Data->Item);
	
	int iType = ConvertItemType(Data->Item);
	if(iType == ITEM_POTION+28
#ifdef YDG_ADD_DOPPELGANGER_ITEM
		|| iType == ITEM_POTION+111	// ������ ����
#endif	// YDG_ADD_DOPPELGANGER_ITEM
		)
	{
		PlayBuffer(SOUND_KUNDUN_ITEM_SOUND);
	}
#ifdef LDK_ADD_GAMBLE_SYSTEM
#ifdef LEM_FIX_JP0714_JEWELMIXSOUND_INGAMBLESYSTEM
	else if( iType == ITEM_POTION+11 )
	{
		PlayBuffer(SOUND_JEWEL01);
	}
#endif // LEM_FIX_JP0714_JEWELMIXSOUND_INGAMBLESYSTEM
	// ���� �ʿ�� �߰�����.
	else if(GambleSystem::Instance().IsGambleShop())
	{

	}
#endif //LDK_ADD_GAMBLE_SYSTEM
	else
	{
		PlayBuffer(SOUND_JEWEL01);
	}
}

///////////////////////////////////////////////////////////////////////////////
// NPC�� ��ȭ, ���, �ȱ�
///////////////////////////////////////////////////////////////////////////////

//��ȭ ����
BOOL ReceiveTalk(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x30);
		return ( FALSE);
	}
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	
	g_pNewUISystem->HideAll();
	
	switch(Data->Value)
	{
	case 2: //  â��.
		g_pNewUISystem->Show(SEASON3B::INTERFACE_STORAGE);
		break;
		
	case 3: // ī����?
		g_MixRecipeMgr.SetMixType(SEASON3A::MIXTYPE_GOBLIN_NORMAL);
		g_pNewUISystem->Show(SEASON3B::INTERFACE_MIXINVENTORY);
		//BYTE *pbyChaosRate = ( &Data->Value) + 1;
		//int iDummyRate[6];	// ����ǥ Ȯ���� �������� ������ ������� �ʰ� ����
		//for ( int i = 0; i < 6; ++i)
		//	iDummyRate[i] = ( int)pbyChaosRate[i];	// ����ǥ Ȯ���� �������� ������ ������� �ʰ� ����(��ũ��Ʈ���)
		break;
		
	case 4: // �Ǹ��� ���� ���� â
		g_pNewUISystem->Show( SEASON3B::INTERFACE_DEVILSQUARE );
		break;
		
    case 5: // ���� ����â.
		g_pUIManager->Open( ::INTERFACE_SERVERDIVISION );
		break;
		
	case 6:	// ���� ĳ�� ���� â	
		g_pNewUISystem->Show( SEASON3B::INTERFACE_BLOODCASTLE );
		break;
		
    case 7: //  ���û� NPC ����.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CTrainerMenuMsgBoxLayout));
		break;
		
	case INDEX_NPC_LAHAP:
		{
			if(COMGEM::isAble())
			{
				g_pNewUISystem->HideAll();
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGemIntegrationMsgBoxLayout));
			}
		}
		break;
		
    case 0x0C : //  ���ο�.
		g_pNewUISystem->Show(SEASON3B::INTERFACE_SENATUS);
        break;
		
    case 0x0D : //  ������.
		SendRequestBCStatus();	// �������� ��û
        break;
	case 0x11:	// ���ǽ�
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CElpisMsgBoxLayout));
			// Ȯ���� �������� ������ ������� �ʰ� ����(��ũ��Ʈ���)
			// 			BYTE *pbyChaosRate = ( &Data->Value) + 1;
			// 			g_pUIJewelHarmony->SetMixSuccessRate(pbyChaosRate);
		}
		break;
	case 0x12:	// ������
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::COsbourneMsgBoxLayout));
			// Ȯ���� �������� ������ ������� �ʰ� ����(��ũ��Ʈ���)
			// 			BYTE *pbyChaosRate = ( &Data->Value) + 1;
			// 			g_pUIJewelHarmony->SetMixSuccessRate(pbyChaosRate);
		}
		break;
	case 0x13:	// ������
		{
			g_MixRecipeMgr.SetMixType(SEASON3A::MIXTYPE_JERRIDON);
			g_pNewUISystem->Show(SEASON3B::INTERFACE_MIXINVENTORY);
			// Ȯ���� �������� ������ ������� �ʰ� ����(��ũ��Ʈ���)
			// 			BYTE *pbyChaosRate = ( &Data->Value) + 1;
			// 			g_pUIJewelHarmony->SetMixSuccessRate(pbyChaosRate);
		}
		break;
	case 0x14:
		{
			g_pNewUISystem->Show(SEASON3B::INTERFACE_CURSEDTEMPLE_NPC);
			
			BYTE *cursedtempleenterinfo = ( &Data->Value) + 1;
			g_pCursedTempleEnterWindow->SetCursedTempleEnterInfo(cursedtempleenterinfo);
		}
		break;
#ifdef CSK_CHAOS_CARD
	case 0x15:	// ī���� ī�� �ͽ�â
		{
			g_MixRecipeMgr.SetMixType(SEASON3A::MIXTYPE_CHAOS_CARD);
			g_pNewUISystem->Show(SEASON3B::INTERFACE_MIXINVENTORY);
		}
		break;
#endif //CSK_CHAOS_CARD
#ifdef CSK_EVENT_CHERRYBLOSSOM
	case 0x16:	// ���� �̺�Ʈ �ͽ�â
		{
			g_MixRecipeMgr.SetMixType(SEASON3A::MIXTYPE_CHERRYBLOSSOM);
			g_pNewUISystem->Show(SEASON3B::INTERFACE_MIXINVENTORY);
		}
		break;
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef ADD_SOCKET_MIX
	case 0x17:	// �õ帶����
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSeedMasterMenuMsgBoxLayout));
		}
		break;
	case 0x18:	// �õ忬����
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSeedInvestigatorMenuMsgBoxLayout));
		}
		break;
#endif	// ADD_SOCKET_MIX
#ifdef PSW_ADD_RESET_CHARACTER_POINT
	case 0x19:	// ���� �ʱ�ȭ
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CResetCharacterPointMsgBoxLayout));
		}
		break;
#endif //PSW_ADD_RESET_CHARACTER_POINT
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	case 0x20:	// 7�ֳ��̺�Ʈ ������NPC
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDelgardoMainMenuMsgBoxLayout));
		}
		break;
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_NEW_DUEL_NPC
	case 0x21:	// ������ ������ NPC Ÿ������
		{
			g_pNewUISystem->Show(SEASON3B::INTERFACE_DUELWATCH);
		}
		break;
#endif	// YDG_ADD_NEW_DUEL_NPC
#ifdef LDK_ADD_GAMBLE_SYSTEM
	case 0x22:
		{
			GambleSystem::Instance().SetGambleShop();
			g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCSHOP);
		}
		break;
#endif //LDK_ADD_GAMBLE_SYSTEM
#ifdef YDG_ADD_DOPPELGANGER_PROTOCOLS
	case 0x23:	// ���ð��� NPC �簡��
		{
			g_pNewUISystem->Show(SEASON3B::INTERFACE_DOPPELGANGER_NPC);
			BYTE * pbtRemainTime = (&Data->Value) + 1;	// ���� �ð�
			g_pDoppelGangerWindow->SetRemainTime(*pbtRemainTime);
		}
		break;
#endif	// YDG_ADD_DOPPELGANGER_PROTOCOLS
#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
	case 0x24:	// ����Ʈ npc - �ӽ� ��ȣ
		{
			g_pNewUISystem->Show(SEASON3B::INTERFACE_EMPIREGUARDIAN_NPC);
		}
		break;
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
#ifdef LDS_ADD_SERVERPROCESSING_UNITEDMARKETPLACE
	case 0x25:	// ���ս��� NPC �ٸ���
		{
			g_pNewUISystem->Show(SEASON3B::INTERFACE_UNITEDMARKETPLACE_NPC_JULIA);
		}
		break;
#endif // LDS_ADD_SERVERPROCESSING_UNITEDMARKETPLACE
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ NPC ������
	case 0x26:	
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CLuckyTradeMenuMsgBoxLayout));
		}
		break;
#endif // LEM_ADD_LUCKYITEM
	default:
		{
			// Data->Value ���� 0�̸� NPCSHOP ����
			g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCSHOP);
		}
		break;
	}
    PlayBuffer(SOUND_CLICK01);
    PlayBuffer(SOUND_INTERFACE01);
#ifndef FOR_WORK		// â��忡�� ���콺 ��ġ �ٲ�°� ���ҽ��ϴ�.
#ifdef WINDOWMODE
	if (g_bUseWindowMode == FALSE)
	{
#endif	// WINDOWMODE
		int x = 260*MouseX/640;
		SetCursorPos((x)*WindowWidth/640,(MouseY)*WindowHeight/480);
#ifdef WINDOWMODE
	}
#endif	// WINDOWMODE
#endif	// FOR_WORK
	
	return ( TRUE);
}

void ReceiveBuy( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_ITEM Data = (LPPHEADER_DEFAULT_ITEM)ReceiveBuffer;
	if(Data->Index != 255)
	{
		if(Data->Index >= MAX_EQUIPMENT_INDEX && Data->Index < MAX_MY_INVENTORY_INDEX)
		{
			g_pMyInventory->InsertItem(Data->Index-MAX_EQUIPMENT_INDEX, Data->Item);
		}
		else
		{
			// �߸��� �ε����� �Ѿ�� ����. �������� �����ϼ���.!
#ifdef _DEBUG
			__asm { int 3 };
#endif // _DEBUG
		}
		
		PlayBuffer(SOUND_GET_ITEM01);
	}
#ifdef LDK_FIX_RECEIVEBUYSELL_RESULT_254
	//���� Ƚ�� �̻� ���� .. receivebuy result���� 254�� hideAll(2008.08.11)
	if( Data->Index == 0xfe )
	{
		g_pNewUISystem->HideAll();

		g_pChatListBox->AddText(Hero->ID,GlobalText[732], SEASON3B::TYPE_ERROR_MESSAGE);
	}
#endif //LDK_FIX_RECEIVEBUYSELL_RESULT_254
	BuyCost = 0;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x32����[ReceiveBuy(%d)]", Data->Index);
#endif // CONSOLE_DEBUG
}

void ReceiveSell( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_GOLD Data = (LPPRECEIVE_GOLD)ReceiveBuffer;
	if(Data->Flag != 0)
	{
#ifdef PSW_FIX_EQUIREEQUIPITEMBUY
		if( Data->Flag == 0xff )
		{
			SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();

			g_pChatListBox->AddText(Hero->ID,GlobalText[733], SEASON3B::TYPE_ERROR_MESSAGE);
		}
#ifdef LDK_FIX_RECEIVEBUYSELL_RESULT_254
		//���� Ƚ�� �̻� ���� .. receivebuy result���� 254�� hideAll(2008.08.11)
		else if( Data->Flag == 0xfe )
		{
			g_pNewUISystem->HideAll();

			g_pChatListBox->AddText(Hero->ID,GlobalText[733], SEASON3B::TYPE_ERROR_MESSAGE);
		}
#endif //LDK_FIX_RECEIVEBUYSELL_RESULT_254
		else 
#endif //PSW_FIX_EQUIREEQUIPITEMBUY
		{
			SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
			
			CharacterMachine->Gold = Data->Gold;
			
			PlayBuffer(SOUND_GET_ITEM01);

#ifdef CSK_FIX_HIGHVALUE_MESSAGEBOX
			g_pNPCShop->SetSellingItem(false);
#endif // CSK_FIX_HIGHVALUE_MESSAGEBOX
		}
	}
	else
	{
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	}
}

void ReceiveRepair( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_REPAIR_GOLD Data = (LPPRECEIVE_REPAIR_GOLD)ReceiveBuffer;
	
    if(Data->Gold != 0)
	{
		CharacterMachine->Gold = Data->Gold;
        CharacterMachine->CalculateAll();
        PlayBuffer(SOUND_REPAIR);
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x34����[ReceiveRepair(%d)]", Data->Gold);
#endif // CONSOLE_DEBUG
}


///////////////////////////////////////////////////////////////////////////////
// ������
///////////////////////////////////////////////////////////////////////////////

void ReceiveLevelUp( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_LEVEL_UP Data = (LPPRECEIVE_LEVEL_UP)ReceiveBuffer;
	CharacterAttribute->Level = Data->Level;
	CharacterAttribute->LevelUpPoint = Data->LevelUpPoint;
	CharacterAttribute->LifeMax = Data->MaxLife;
	CharacterAttribute->ManaMax = Data->MaxMana;
	CharacterAttribute->Life    = Data->MaxLife;
	CharacterAttribute->Mana    = Data->MaxMana;
	CharacterAttribute->ShieldMax = Data->MaxShield;
	CharacterAttribute->SkillManaMax = Data->SkillManaMax;
    
    //  �߰��Ǵ� ���� ����.
    CharacterAttribute->AddPoint		= Data->AddPoint;
    CharacterAttribute->MaxAddPoint		= Data->MaxAddPoint;
	//	���� ���� ����Ʈ ����
	CharacterAttribute->wMinusPoint		= Data->wMinusPoint;		// ���� ���� ����Ʈ
    CharacterAttribute->wMaxMinusPoint	= Data->wMaxMinusPoint;		// �ִ� ���� ����Ʈ
	
	unicode::t_char szText[256] = {NULL, };
	WORD iExp = CharacterAttribute->NextExperince - CharacterAttribute->Experience;
	sprintf(szText,GlobalText[486], iExp);
	g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);

    CharacterMachine->CalculateNextExperince();
	
	OBJECT *o = &Hero->Object;

	if(IsMasterLevel(Hero->Class) == true)
	{
		//		OBJECT *o = &Hero->Object;
		
		CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,45,o,80,2);
		for ( int i=0; i<19; ++i )
		{
			CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,46,o,80,2);
		}
	}
	else
	{
		for ( int i=0; i<15; ++i )
		{
			CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
		}
		CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
	}
    PlayBuffer(SOUND_LEVEL_UP);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x05����[ReceiveLevelUp]");
#endif // CONSOLE_DEBUG
}

void ReceiveAddPoint( BYTE *ReceiveBuffer )
{
    LPPRECEIVE_ADD_POINT Data = (LPPRECEIVE_ADD_POINT)ReceiveBuffer;
	if(Data->Result>>4)
	{
		CharacterAttribute->LevelUpPoint --;
		switch(Data->Result&0xf)
		{
		case 0:
			CharacterAttribute->Strength ++;
			break;
		case 1:
			CharacterAttribute->Dexterity ++;
			break;
		case 2:
			CharacterAttribute->Vitality ++;
			CharacterAttribute->LifeMax = Data->Max;
			break;
		case 3:
			CharacterAttribute->Energy ++;
			CharacterAttribute->ManaMax = Data->Max;
			break;
        case 4:
			CharacterAttribute->Charisma ++;
            break;
		}
		CharacterAttribute->SkillManaMax = Data->SkillManaMax;
		CharacterAttribute->ShieldMax = Data->ShieldMax;
	}
    CharacterMachine->CalculateAll();
}

///////////////////////////////////////////////////////////////////////////////
// ����, ����
///////////////////////////////////////////////////////////////////////////////

void ReceiveLife( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_LIFE Data = (LPPRECEIVE_LIFE)ReceiveBuffer;
	switch(Data->Index)
	{
	case 0xff:
		CharacterAttribute->Life = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
		CharacterAttribute->Shield = ((WORD)(Data->Life[3])<<8) + Data->Life[4];
		break;
	case 0xfe:
		if(IsMasterLevel(Hero->Class) == true)
		{
			//	Master_Level_Data.wMaxLife			= Data->LifeMax;
			//	Master_Level_Data.wMaxMana			= Data->ManaMax;
			//	Master_Level_Data.wMaxShield		= Data->ShieldMax;
			Master_Level_Data.wMaxLife = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
			Master_Level_Data.wMaxShield = ((WORD)(Data->Life[3])<<8) + Data->Life[4];
		}
		else
		{
			CharacterAttribute->LifeMax = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
			CharacterAttribute->ShieldMax = ((WORD)(Data->Life[3])<<8) + Data->Life[4];
		}
		break;
	case 0xfd:
		EnableUse = 0;
		break;
	default:
		{
			int itemindex = Data->Index-MAX_EQUIPMENT_INDEX;
			ITEM* pItem = g_pMyInventory->FindItem(itemindex);
			if(pItem)
			{
				if(pItem->Durability > 0)
					pItem->Durability--;
				if(pItem->Durability <= 0)
					g_pMyInventory->DeleteItem(itemindex);
			}
		}
		break;
	}
	
#ifdef CONSOLE_DEBUG
	//g_ConsoleDebug->Write(MCD_RECEIVE, "0x26����[ReceiveLife]");
#endif // CONSOLE_DEBUG
}

void ReceiveMana( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_LIFE Data = (LPPRECEIVE_LIFE)ReceiveBuffer;
	switch(Data->Index)
	{
	case 0xff:
		CharacterAttribute->Mana = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
		CharacterAttribute->SkillMana = ((WORD)(Data->Life[2])<<8) + Data->Life[3];
		break;
	case 0xfe:
		if(IsMasterLevel(Hero->Class) == true)
		{
			//	Master_Level_Data.wMaxLife			= Data->LifeMax;
			//	Master_Level_Data.wMaxMana			= Data->ManaMax;
			//	Master_Level_Data.wMaxShield		= Data->ShieldMax;
			Master_Level_Data.wMaxMana = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
			Master_Level_Data.wMaxBP = ((WORD)(Data->Life[2])<<8) + Data->Life[3];
		}
		else
		{
			CharacterAttribute->ManaMax = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
			CharacterAttribute->SkillManaMax = ((WORD)(Data->Life[2])<<8) + Data->Life[3];
		}
		break;
	default:
		CharacterAttribute->Mana = ((WORD)(Data->Life[0])<<8) + Data->Life[1];
		if(Inventory[Data->Index-12].Durability > 0)
			Inventory[Data->Index-12].Durability --;
		if(Inventory[Data->Index-12].Durability <= 0)
		{
			Inventory[Data->Index-12].Type = -1;
			Inventory[Data->Index-12].Number = 0;
		}
		break;
	}
	
#ifdef CONSOLE_DEBUG
	//g_ConsoleDebug->Write(MCD_RECEIVE, "0x27����[ReceiveMana]");
#endif // CONSOLE_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
// pk ,������, ������, ����, �̹�Ʈ �߻�, ��ȯ������
///////////////////////////////////////////////////////////////////////////////

void ReceivePK( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_PK Data = (LPPRECEIVE_PK)ReceiveBuffer;
	int Key = ((int)(Data->KeyH   )<<8) + Data->KeyL;
	CHARACTER *c = &CharactersClient[FindCharacterIndex(Key)];
    c->PK = Data->PK;

#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
	g_PKSystem->SetHeroPKState(Hero->PK);
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP	
#ifdef PK_ATTACK_TESTSERVER_LOG
	PrintPKLog(c);
#endif // PK_ATTACK_TESTSERVER_LOG
	
	if(c->PK >= PVP_MURDERER2)
        c->Level = 1;
	else
        c->Level = 0;
	switch(Data->PK)
	{
	case 1: case 2:
		{
			g_pChatListBox->AddText(CharactersClient[FindCharacterIndex(Key)].ID,GlobalText[487], SEASON3B::TYPE_SYSTEM_MESSAGE);
		}
		break;
	case 3:
		{
			g_pChatListBox->AddText(CharactersClient[FindCharacterIndex(Key)].ID,GlobalText[488], SEASON3B::TYPE_ERROR_MESSAGE);			
		}
		break;
	case 4:
		{
			g_pChatListBox->AddText(CharactersClient[FindCharacterIndex(Key)].ID,GlobalText[489], SEASON3B::TYPE_SYSTEM_MESSAGE);
		}
		break;
	case 5:
		{
#if SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			char szTemp[100];
#else // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			char szTemp[32];
#endif // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			
			sprintf(szTemp, "%s %d%s", GlobalText[490], 1, GlobalText[491]);
			
			g_pChatListBox->AddText(CharactersClient[FindCharacterIndex(Key)].ID,szTemp, SEASON3B::TYPE_ERROR_MESSAGE);	
		}
		break;
	case 6:
		{
#if SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			char szTemp[100];
#else // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			char szTemp[32];
#endif // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
			
			sprintf(szTemp, "%s %d%s", GlobalText[490], 2, GlobalText[491]);
			
			g_pChatListBox->AddText(CharactersClient[FindCharacterIndex(Key)].ID,szTemp, SEASON3B::TYPE_ERROR_MESSAGE);
		}
		break;
	}
}

// �������� ������ ���� �޴� �Լ�
void ReceiveDurability( BYTE *ReceiveBuffer )
{
    LPPHEADER_DEFAULT_VALUE_KEY Data = (LPPHEADER_DEFAULT_VALUE_KEY)ReceiveBuffer;
	
	if(Data->Value < 12)		//. ����
	{
		CharacterMachine->Equipment[Data->Value].Durability = Data->KeyH;
	}
	else						//. ����
	{
		int iItemIndex = Data->Value-MAX_EQUIPMENT_INDEX;
		ITEM* pItem = g_pMyInventory->FindItem(iItemIndex);
		
		if(pItem)
		{
			pItem->Durability = Data->KeyH;
		}
	}
	
	if(Data->KeyL)
	{
		EnableUse = 0;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x2A����[ReceiveDurability(%d %d)]", Data->Value, Data->KeyL);
#endif // CONSOLE_DEBUG
}

//  �� ����.
BOOL ReceiveHelperItem(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x29);
		return ( FALSE);
	}
	
    LPPRECEIVE_HELPER_ITEM Data = (LPPRECEIVE_HELPER_ITEM)ReceiveBuffer;
   	CharacterAttribute->AbilityTime[Data->Index] = Data->Time*24;
	switch (Data->Index)
	{
	case 0:	// ��
		CharacterAttribute->Ability |= ABILITY_FAST_ATTACK_SPEED;
		
        //  ���ݼӵ� ���.
        CharacterMachine->CalculateAttackSpeed();
		break;
	case 1: // ����� ����
		CharacterAttribute->Ability |= ABILITY_PLUS_DAMAGE;
		
        //  ���ݼӵ� ���.
        CharacterMachine->CalculateDamage();
		CharacterMachine->CalculateMagicDamage();
		break;
		
    case 2: //  ��ȥ�� ����.
        CharacterAttribute->Ability |= ABILITY_FAST_ATTACK_SPEED2;
		
        //  ���ݼӵ� ���.
        CharacterMachine->CalculateAttackSpeed();
        break;
	}
	EnableUse = 0;
	
	return ( TRUE);
}

void ReceiveWeather( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	int Weather = (Data->Value>>4);
	if(Weather==0)
		RainTarget = 0;
	else if(Weather==1)
		RainTarget = (Data->Value&15)*6;
}

void ReceiveEvent( BYTE *ReceiveBuffer )
{
	LPPHEADER_EVENT Data = (LPPHEADER_EVENT)ReceiveBuffer;
	
    switch ( Data->m_byNumber )
    {
    case 1: //  ȯ�� �巡��.
		if ( Data->m_byValue ) EnableEvent = 1;
        else               EnableEvent = 0; 
        break;
#ifdef USE_EVENT_ELDORADO
    case 3: //  Ȳ�� �巡��.
		if ( Data->m_byValue ) EnableEvent = 3;
        else               EnableEvent = 0; 
        break;
#endif
    case 2: //  Ÿ��¯.
#ifdef TAMAJJANG
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
        if ( Data->m_byValue )
        {
            DeleteTamaJjang (); //  Ÿ��¯ ����.
            CreateTamaJjang ();
        }
        else
        {
            HideTamaJjang();
        }
#endif
#endif
        break;
    }
    DeleteBoids();
}

void ReceiveSummonLife( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
	SummonLife = Data->Value;
}

///////////////////////////////////////////////////////////////////////////////
// ��ȯ
///////////////////////////////////////////////////////////////////////////////

BOOL ReceiveTrade(BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0x36);
		return ( FALSE);
	}
	
	LPPCHATING Data = (LPPCHATING)ReceiveBuffer;
	g_pTrade->ProcessToReceiveTradeRequest(Data->ID);
	
	return ( TRUE);
}

void ReceiveTradeResult( BYTE *ReceiveBuffer )
{
	LPPTRADE Data = (LPPTRADE)ReceiveBuffer;
	g_pTrade->ProcessToReceiveTradeResult(Data);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x37����[ReceiveTradeResult(%d)]", Data->ID);
#endif // CONSOLE_DEBUG
}

void ReceiveTradeYourInventoryDelete( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	g_pTrade->ProcessToReceiveYourItemDelete(Data->Value);
}

void ReceiveTradeYourInventory( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_ITEM Data = (LPPHEADER_DEFAULT_ITEM)ReceiveBuffer;
	g_pTrade->ProcessToReceiveYourItemAdd(Data->Index, Data->Item);
}

void ReceiveTradeMyGold( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	g_pTrade->ProcessToReceiveMyTradeGold(Data->Value);
}

void ReceiveTradeYourGold( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_DWORD Data = (LPPHEADER_DEFAULT_DWORD)ReceiveBuffer;
	g_pTrade->SetYourTradeGold(int(Data->Value));
}

void ReceiveTradeYourResult( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	g_pTrade->ProcessToReceiveYourConfirm(Data->Value);
}


void ReceiveTradeExit( BYTE *ReceiveBuffer )
{
	if(EquipmentItem)
	{	// ���� �� ó���� �� �ְ� �Ѵ�.
		if ( !g_bPacketAfter_EquipmentItem)
		{
			memcpy( g_byPacketAfter_EquipmentItem, ReceiveBuffer, sizeof ( PHEADER_DEFAULT));
			g_bPacketAfter_EquipmentItem = TRUE;
		}
		return;
	}

	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	g_pTrade->ProcessToReceiveTradeExit(Data->Value);
}

void ReceivePing( BYTE *ReceiveBuffer)
{
	SendPing();
}

#ifdef NP_GAME_GUARD
#ifdef GG_SERVER_AUTH
extern  CNPGameLib*  g_pnpGL;     //  nProtect Game Guard Lib.
BOOL ReceiveGGAuth( BYTE *ReceiveBuffer, BOOL bEncrypted)
{
	if ( !bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked( 0x00, 0xF1);
		return ( FALSE);
	}
	LPPHEADER_DEFAULT_DWORD Data = (LPPHEADER_DEFAULT_DWORD)ReceiveBuffer;
	if(g_pnpGL) 
	{
#ifdef NPROTECT_AUTH2
		GG_AUTH_DATA* pAuthData = (GG_AUTH_DATA*)(ReceiveBuffer+sizeof(PBMSG_HEADER)+1);
		g_pnpGL->Auth2(pAuthData);
#ifdef NP_LOG
		g_ErrorReport.Write("ReceiveGGAuth() g_pnpGL->Auth2(%x %x %x %x)\r\n",
			pAuthData->dwIndex, pAuthData->dwValue1, pAuthData->dwValue2, pAuthData->dwValue3);	
#endif	// NP_LOG

#else // NPROTECT_AUTH2
		
#ifdef NP_LOG
		g_ErrorReport.Write("ReceiveGGAuth() g_pnpGL->Auth(%x)\r\n", Data->Value);	
#endif	// NP_LOG
		g_pnpGL->Auth( Data->Value);
#endif // NPROTECT_AUTH2
	}
#ifdef CSK_FIX_GAMEGUARD_CHECK
	else
	{
#ifdef PBG_MOD_GAMEGUARD_HANDLE
		// �����α׷� �߻��� Ŭ���̾�Ʈ �ٷ� �������� �ʴ´�
		if(BLUE_MU::IsBlueMuServer())
		{
			if(!g_NPGameGuardHandle->IsNPHack())
				g_NPGameGuardHandle->SetNPHack(true);
			//g_NPGameGuardHandle->SetCharacterInfo(LogInID,);
		}
		else
#endif //PBG_MOD_GAMEGUARD_HANDLE
		CloseHack(g_hWnd, true);
	}
#endif // CSK_FIX_GAMEGUARD_CHECK
	
#ifdef _DEBUG
	char str[256];
#ifdef NPROTECT_AUTH2
	GG_AUTH_DATA* pAuthData = (GG_AUTH_DATA*)(ReceiveBuffer+sizeof(PBMSG_HEADER)+1);
	wsprintf( str, "ReceiveGGAuth - ��û ���� %X %X %X %X", pAuthData->dwIndex, pAuthData->dwValue1, pAuthData->dwValue2, pAuthData->dwValue3);
#else	// NPROTECT_AUTH2
	wsprintf( str, "ReceiveGGAuth - ��û ���� %X", Data->Value);
#endif // NPROTECT_AUTH2
	g_pChatListBox->AddText("", str, SEASON3B::TYPE_SYSTEM_MESSAGE);
#endif // _DEBUG
	
	return ( TRUE);
}
#endif	// GG_SERVER_AUTH
#endif	// NP_GAME_GUARD

///////////////////////////////////////////////////////////////////////////////
// â��
///////////////////////////////////////////////////////////////////////////////

void ReceiveStorageGold( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_STORAGE_GOLD Data = (LPPRECEIVE_STORAGE_GOLD)ReceiveBuffer;
	if(Data->Result)
	{
		CharacterMachine->StorageGold = Data->StorageGold;
		CharacterMachine->Gold        = Data->Gold;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x81����[ReceiveStorageGold(%d %d %d)]", Data->Result, Data->StorageGold, Data->Gold);
#endif // CONSOLE_DEBUG
}

void ReceiveStorageExit( BYTE *ReceiveBuffer )
{
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x82����[ReceiveStorageExit]");
#endif // CONSOLE_DEBUG
}

void ReceiveStorageStatus( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = ( LPPHEADER_DEFAULT)ReceiveBuffer;
	
	g_pStorageInventory->ProcessToReceiveStorageStatus(Data->Value);
}

///////////////////////////////////////////////////////////////////////////////
// ��Ƽ
///////////////////////////////////////////////////////////////////////////////

void ReceiveParty( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_KEY Data = (LPPHEADER_DEFAULT_KEY)ReceiveBuffer;
	PartyKey = ((int)(Data->KeyH )<<8) + Data->KeyL;
	
	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CPartyMsgBoxLayout));
}

void ReceivePartyResult( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:g_pChatListBox->AddText("", GlobalText[497], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 1:g_pChatListBox->AddText("", GlobalText[498], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 2:g_pChatListBox->AddText("", GlobalText[499], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 3:g_pChatListBox->AddText("", GlobalText[500], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 4:g_pChatListBox->AddText("", GlobalText[501], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 5:g_pChatListBox->AddText("", GlobalText[502], SEASON3B::TYPE_ERROR_MESSAGE);break;
#ifdef ASG_ADD_GENS_SYSTEM
	case 6:g_pChatListBox->AddText("", GlobalText[2990], SEASON3B::TYPE_ERROR_MESSAGE);break;
#endif	// ASG_ADD_GENS_SYSTEM
#ifdef ASG_MOD_GENS_STRIFE_ADD_PARTY_MSG
	case 7:g_pChatListBox->AddText("", GlobalText[2997], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 8:g_pChatListBox->AddText("", GlobalText[2998], SEASON3B::TYPE_ERROR_MESSAGE);break;
#endif	// ASG_MOD_GENS_STRIFE_ADD_PARTY_MSG
	}
}

//��Ƽ �����̳� Ż��ÿ� ������ ��Ŷ
void ReceivePartyList( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_PARTY_LISTS Data = (LPPRECEIVE_PARTY_LISTS)ReceiveBuffer;
	int Offset = sizeof(PRECEIVE_PARTY_LISTS);
	PartyNumber = Data->Count;
	for(int i=0;i<Data->Count;i++)
	{
		LPPRECEIVE_PARTY_LIST Data2 = (LPPRECEIVE_PARTY_LIST)(ReceiveBuffer+Offset);
		PARTY_t *p = &Party[i];
		memcpy(p->Name,Data2->ID,MAX_ID_SIZE);
		p->Name[MAX_ID_SIZE] = NULL;
		p->Number = Data2->Number;
		p->Map = Data2->Map;
		p->x = Data2->x;
		p->y = Data2->y;
        p->currHP = Data2->currHP;
        p->maxHP = Data2->maxHP;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
		g_PKSystem->SetHeroPartyPKState(Data2->PKPartyLevel);
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
		Offset += sizeof(PRECEIVE_PARTY_LIST);
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x42����[ReceivePartyList(partynum : %d)]", Data->Count);
#endif // CONSOLE_DEBUG
}

// ��Ƽ�� �Ǿ������� �׻������ ��Ŷ
void ReceivePartyInfo( BYTE *ReceiveBuffer )
{
    LPPRECEIVE_PARTY_INFOS Data = (LPPRECEIVE_PARTY_INFOS)ReceiveBuffer;
    int Offset = sizeof( PRECEIVE_PARTY_INFOS);
    for( int i=0; i<Data->Count; i++ )
    {
        LPPRECEIVE_PARTY_INFO Data2 = (LPPRECEIVE_PARTY_INFO)(ReceiveBuffer+Offset);
        char stepHP= Data2->value&0xf;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		char number= (Data2->value>>4)&0xf;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
#ifdef KJH_FIX_WOPS_K27187_STEPHP_INFO_IN_PARTY
		PARTY_t* p = &Party[i];
#else // KJH_FIX_WOPS_K27187_STEPHP_INFO_IN_PARTY
		PARTY_t* p = &Party[number];
#endif // KJH_FIX_WOPS_K27187_STEPHP_INFO_IN_PARTY
		
        p->stepHP = min ( 10, max ( 0, stepHP ) );
		
        Offset += sizeof( PRECEIVE_PARTY_INFO );
    }
}


// �����ϴ� ��Ŷ
void ReceivePartyLeave( BYTE *ReceiveBuffer )
{
	PartyNumber = 0;
	g_pChatListBox->AddText("", GlobalText[502], SEASON3B::TYPE_ERROR_MESSAGE);

#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
	// ��Ƽ�� ���������� �÷��̾��� ��Ƽ PK���� ������ �÷��̾��� PK���� �������� �����.
	g_PKSystem->SetHeroPartyPKState(Hero->PK);
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	

    //  ���󰡰� ������ ���� ��Ƽ�� �ƴϸ��� X.
    if ( g_iFollowCharacter>=0 )
    {
        bool IsParty = false;
        CHARACTER* c = &CharactersClient[g_iFollowCharacter];
        for ( int i=0; i<PartyNumber; ++i )
        {
            if ( strcmp( Party[i].Name, c->ID )==NULL && strlen( Party[i].Name )==strlen( c->ID ) )
            {
                IsParty = true;
            }
        }
		
        if ( IsParty==false )
        {
            g_iFollowCharacter = -1;
        }
    }
}

void ReceivePartyGetItem ( BYTE* ReceiveBuffer )
{
	//9Bit(Ÿ��), ��ų, ���, �ɼ�, �׼���Ʈ, ��Ʈ (���ʷ�)
    LPPRECEIVE_GETITEMINFO_FOR_PARTY Data = (LPPRECEIVE_GETITEMINFO_FOR_PARTY)ReceiveBuffer;
    int Key = ((int)(Data->KeyH )<<8) + Data->KeyL;
    int Index = FindCharacterIndex ( Key );
    CHARACTER* c = &CharactersClient[Index];
    if ( Hero==c ) return;
	
    int itemType = Data->ItemInfo&0x01fff;   //  ������ Ÿ��.
    char itemName[100] = { 0, };
    char Text[100] = { 0, };
	
    if ( (Data->ItemInfo&0x10000) )      sprintf ( itemName, "%s ", GlobalText[620] );   //  �׼���Ʈ.
    else if ( (Data->ItemInfo&0x20000) ) sprintf ( itemName, "%s ", GlobalText[1089] );  //  ��Ʈ.
	
	int itemLevel = Data->ItemLevel;
    GetItemName ( itemType, itemLevel, Text );
    strcat ( itemName, Text );
    if ( (Data->ItemInfo&0x02000) ) strcat ( itemName, GlobalText[176] );    //  ��ų.
    if ( (Data->ItemInfo&0x08000) ) strcat ( itemName, GlobalText[177] );    //  �ɼ�.
    if ( (Data->ItemInfo&0x04000) ) strcat ( itemName, GlobalText[178] );    //  ���.
	
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
    sprintf ( Text, "%s %s", GlobalText[918], itemName );   //  ȹ��.
#else
    sprintf ( Text, "%s %s", itemName, GlobalText[918] );   //  ȹ��.
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE
	
	g_pChatListBox->AddText(c->ID, Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
}

///////////////////////////////////////////////////////////////////////////////
// ���
///////////////////////////////////////////////////////////////////////////////

extern int ErrorMessage;

//  ��� ����.
void ReceiveGuild( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_KEY Data = (LPPHEADER_DEFAULT_KEY)ReceiveBuffer;
	GuildPlayerKey = ((int)(Data->KeyH )<<8) + Data->KeyL;
	
	SEASON3B::CNewUICommonMessageBox* pMsgBox;
	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGuildRequestMsgBoxLayout), &pMsgBox);
	pMsgBox->AddMsg(CharactersClient[FindCharacterIndex(GuildPlayerKey)].ID);
	// 429 "��� ���� ��û�� �Խ��ϴ�."
	pMsgBox->AddMsg(GlobalText[429]);
}

void ReceiveGuildResult( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:g_pChatListBox->AddText("", GlobalText[503], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 1:g_pChatListBox->AddText("", GlobalText[504], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 2:g_pChatListBox->AddText("", GlobalText[505], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 3:g_pChatListBox->AddText("", GlobalText[506], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 4:g_pChatListBox->AddText("", GlobalText[507], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 5:g_pChatListBox->AddText("", GlobalText[508], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 6:g_pChatListBox->AddText("", GlobalText[509], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 7:g_pChatListBox->AddText("", GlobalText[510], SEASON3B::TYPE_ERROR_MESSAGE);break;
#ifdef ASG_ADD_GENS_SYSTEM
	case 0xA1:g_pChatListBox->AddText("", GlobalText[2992], SEASON3B::TYPE_ERROR_MESSAGE);break;// 2992	"��� �����Ͱ� �ս��� ������ �ȵǾ� �ֽ��ϴ�."
	case 0xA2:g_pChatListBox->AddText("", GlobalText[2995], SEASON3B::TYPE_ERROR_MESSAGE);break;// 2995 "��� �����Ͱ� �ٸ� �ս��� ���ԵǾ� �ֽ��ϴ�."
#ifdef ASG_MOD_GUILD_RESULT_GENS_MSG
	case 0xA3:g_pChatListBox->AddText("", GlobalText[2996], SEASON3B::TYPE_ERROR_MESSAGE);break;
#endif	// ASG_MOD_GUILD_RESULT_GENS_MSG
#endif	// ASG_ADD_GENS_SYSTEM
	}
}

void ReceiveGuildList( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_GUILD_LISTS Data = (LPPRECEIVE_GUILD_LISTS)ReceiveBuffer;
	int Offset = sizeof(PRECEIVE_GUILD_LISTS);
	
	g_nGuildMemberCount = Data->Count;
	GuildTotalScore = Data->TotalScore;
    GuildTotalScore = max( 0, GuildTotalScore );
	
	g_pGuildInfoWindow->GuildClear();
	g_pGuildInfoWindow->UnionGuildClear();
	g_pGuildInfoWindow->SetRivalGuildName(Data->szRivalGuildName);
	for(int i=0;i<Data->Count;i++)
	{
		LPPRECEIVE_GUILD_LIST Data2 = (LPPRECEIVE_GUILD_LIST)(ReceiveBuffer+Offset);
		GUILD_LIST_t *p = &GuildList[i];
		memcpy(p->Name,Data2->ID,MAX_ID_SIZE);
		p->Name[MAX_ID_SIZE] = NULL;
		p->Number = Data2->Number;
		p->Server = ( 0x80 & Data2->CurrentServer) ? ( 0x7F & Data2->CurrentServer) : -1;	// ������ �������� -1
		p->GuildStatus = Data2->GuildStatus;
		Offset += sizeof(PRECEIVE_GUILD_LIST);
		g_pGuildInfoWindow->AddGuildMember(p);
	}
}

void ReceiveGuildLeave( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:g_pChatListBox->AddText("", GlobalText[511], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 1:g_pChatListBox->AddText("", GlobalText[512], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 2:g_pChatListBox->AddText("", GlobalText[513], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 3:g_pChatListBox->AddText("", GlobalText[514], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 4:g_pChatListBox->AddText("", GlobalText[515], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 5:g_pChatListBox->AddText("", GlobalText[568], SEASON3B::TYPE_ERROR_MESSAGE);break;
	}
    if(Data->Value==1 || Data->Value==4)
	{
		if(Data->Value==4 && Hero->GuildMarkIndex!=-1)
		{
			GuildMark[Hero->GuildMarkIndex].Key = -1;
			GuildMark[Hero->GuildMarkIndex].UnionName[0] = NULL;
			GuildMark[Hero->GuildMarkIndex].GuildName[0] = NULL;
			Hero->GuildMarkIndex = -1;
		}
		
		// ��������̿��� ��� ���..
		EnableGuildWar = false;
		
		g_nGuildMemberCount = -1;
		Hero->GuildStatus = G_NONE;
		Hero->GuildRelationShip = GR_NONE;
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_GUILDINFO);
		
#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
		g_pMoveCommandWindow->SetCastleOwner(false);
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
	}
	// ���� Ż��������� ��� ���� (�ֹι�ȣ���°��������� Ż�𴩸��� �ٷ� ��û�ϸ� �ȵǹǷ� ���⼭ �簻��)
	else if( Data->Value == 5 )
	{
		SendRequestGuildList();
	}
}

void ReceiveCreateGuildInterface( BYTE *ReceiveBuffer )
{
	g_pNewUISystem->Show( SEASON3B::INTERFACE_NPCGUILDMASTER );
}

void ReceiveCreateGuildMasterInterface( BYTE *ReceiveBuffer )
{
}

void ReceiveDeleteGuildViewport( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_KEY Data = (LPPHEADER_DEFAULT_KEY)ReceiveBuffer;
    int Key = ((int)(Data->KeyH&0x7f)<<8) + Data->KeyL;
	int Index = FindCharacterIndex(Key);
	CHARACTER *c = &CharactersClient[Index];
	
	c->GuildStatus		= -1;		// ��峻������ ��å
	c->GuildType		= 0;		// ���Ÿ��
	c->ProtectGuildMarkWorldTime = 0.0f;
	c->GuildRelationShip	= 0;	// ������
	c->GuildMarkIndex = -1;
	
	g_nGuildMemberCount = -1;
	
	g_pNewUISystem->Hide(SEASON3B::INTERFACE_GUILDINFO);
}

void ReceiveCreateGuildResult( BYTE *ReceiveBuffer )
{
	LPPMSG_GUILD_CREATE_RESULT Data = (LPPMSG_GUILD_CREATE_RESULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:g_pChatListBox->AddText("", GlobalText[516], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 2:g_pChatListBox->AddText("", GlobalText[517], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 3:g_pChatListBox->AddText("", GlobalText[518], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 4:g_pChatListBox->AddText("", GlobalText[940], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 5:g_pChatListBox->AddText("", GlobalText[941], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 6:g_pChatListBox->AddText("", GlobalText[942], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 1:
		memset(InputText[0],0,MAX_ID_SIZE);
		InputLength[0] = 0;
		InputTextMax[0] = MAX_ID_SIZE;
		
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPCGUILDMASTER);
		
		MouseUpdateTime = 0;
		MouseUpdateTimeMax = 6;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// �����
///////////////////////////////////////////////////////////////////////////////

bool EnableGuildWar = false;
int  GuildWarIndex = -1;
char GuildWarName[8+1];
int  GuildWarScore[2];

bool EnableSoccer = false;
BYTE HeroSoccerTeam = 0;
int  SoccerTime;
char SoccerTeamName[2][8+1];
bool SoccerObserver = false;

//���� ���� �޼���
void ReceiveDeclareWar( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_WAR Data = (LPPRECEIVE_WAR)ReceiveBuffer;
	memset(GuildWarName,0,8);
	memcpy(GuildWarName,Data->Name,8);
	GuildWarName[8] = NULL;
	
	// ��Ʋ��Ŀ�� ��û
	if(Data->Type == 1)
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CBattleSoccerMsgBoxLayout));
	}
	else	// ����� ��û
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGuildWarMsgBoxLayout));
	}
}

//���� ���� ���
void ReceiveDeclareWarResult( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	switch(Data->Value)
	{
	case 0:g_pChatListBox->AddText("", GlobalText[519], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 1:g_pChatListBox->AddText("", GlobalText[520], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 2:g_pChatListBox->AddText("", GlobalText[521], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 3:g_pChatListBox->AddText("", GlobalText[522], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 4:g_pChatListBox->AddText("", GlobalText[523], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 5:g_pChatListBox->AddText("", GlobalText[524], SEASON3B::TYPE_ERROR_MESSAGE);break;
	case 6:g_pChatListBox->AddText("", GlobalText[525], SEASON3B::TYPE_ERROR_MESSAGE);break;
	}
	if(Data->Value != 1 && !EnableGuildWar)
	{
        InitGuildWar();
	}
}

void ReceiveGuildBeginWar( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_WAR Data = (LPPRECEIVE_WAR)ReceiveBuffer;
	EnableGuildWar = true;
	
	char Text[100];
	memset(GuildWarName,0,8);
	memcpy(GuildWarName,Data->Name,8);
	GuildWarName[8] = NULL;
	
	if(Data->Type==0)
	{
		sprintf(Text,GlobalText[526],GuildWarName);
	}
	else
	{
		sprintf(Text,GlobalText[533],GuildWarName);
		EnableSoccer = true;
	}
   	
	CreateNotice(Text,1);
	HeroSoccerTeam = Data->Team;
	
#ifdef _VS2008PORTING
	for(int i=0;i<MARK_EDIT;i++)
#else // _VS2008PORTING
	int i;
	for(i=0;i<MARK_EDIT;i++)
#endif // _VS2008PORTING
	{
		MARK_t *p = &GuildMark[i];
		char Temp[8+1];
		memset(Temp,0,8);
		memcpy(Temp,(char *)Data->Name,8);
		Temp[8] = NULL;
		if(strcmp(p->GuildName,Temp)==NULL)
		{
			GuildWarIndex = i;
			break;
		}
	}
	if(GuildWarIndex >= 0)
	{
#ifdef _VS2008PORTING
		for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
#else // _VS2008PORTING
		for(i=0;i<MAX_CHARACTERS_CLIENT;i++)
#endif // _VS2008PORTING
		{
			CHARACTER *c = &CharactersClient[i];
			GuildTeam(c);
		}
	}
	SetActionClass(Hero,&Hero->Object,PLAYER_RUSH1,AT_RUSH1);
   	SendRequestAction(AT_RUSH1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	
	g_pNewUISystem->Show(SEASON3B::INTERFACE_BATTLE_SOCCER_SCORE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x62����[ReceiveGuildBeginWar(%d)]", Data->Team);
#endif // CONSOLE_DEBUG
}

void ReceiveGuildEndWar( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	char Text[100];
	int Win = 0;
	switch(Data->Value)
	{
	case 0:sprintf(Text,GlobalText[527]);break;
	case 1:sprintf(Text,GlobalText[528]);Win = 2;break;
	case 2:sprintf(Text,GlobalText[529]);Win = 2;break;
	case 3:sprintf(Text,GlobalText[530]);break;
	case 4:sprintf(Text,GlobalText[531]);Win = 2;break;
	case 5:sprintf(Text,GlobalText[532]);break;
	case 6:sprintf(Text,GlobalText[480]);Win = 1;break;
#ifdef LJH_FIX_NO_MSG_FOR_FORCED_MOVEOUT_FROM_BATTLESOCCER
	default:sprintf(Text,"");break;	
#endif	//LJH_FIX_NO_MSG_FOR_FORCED_MOVEOUT_FROM_BATTLESOCCER
	}
	
	//����� ����� ���� ��, �ʱ�ȭ�Ѵ�. 
	g_wtMatchTimeLeft.m_Time = 0;
	
#ifndef GUILD_WAR_EVENT
   	CreateNotice(Text,1);
#endif
	
	EnableGuildWar = false;
	EnableSoccer = false;
	
	GuildWarIndex = -1;
	GuildWarName[0] = NULL;
	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)
	{
		CHARACTER *c = &CharactersClient[i];
       	GuildTeam(c);
	}
	switch(Win)
	{
	case 2:
		SetActionClass(Hero,&Hero->Object,PLAYER_WIN1,AT_WIN1);
		SendRequestAction(AT_WIN1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
		break;
	case 0:
		SetActionClass(Hero,&Hero->Object,PLAYER_CRY1,AT_CRY1);
		SendRequestAction(AT_CRY1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
		break;
	}
	
	g_pNewUISystem->Hide(SEASON3B::INTERFACE_BATTLE_SOCCER_SCORE);
}

void ReceiveGuildWarScore( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_WAR_SCORE Data = (LPPRECEIVE_WAR_SCORE)ReceiveBuffer;
	EnableGuildWar = true;
	
#ifdef GUILD_WAR_EVENT
	//���߿� �� ���ľ� ��.
	int t1 = Data->Score1 - GuildWarScore[0];
	int t2 = Data->Score2 - GuildWarScore[1];
	if(t1 == 20 || t2 == 20)
	{
		//�츮 �����鿡�� ����Ʈ ���
		if(t1 > t2) g_iGoalEffect = 1;
		//��� �����鿡�� ����Ʈ ���
		else g_iGoalEffect = 2;
	}
#endif
	
	GuildWarScore[0] = Data->Score1;
	GuildWarScore[1] = Data->Score2;
}

void ReceiveGuildIDViewport( BYTE *ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD Data = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for( int i=0 ; i<Data->Value ; ++i )
	{
		LPPRECEIVE_GUILD_ID Data2 = (LPPRECEIVE_GUILD_ID)(ReceiveBuffer+Offset);
		int GuildKey = Data2->GuildKey;
		int Key = ((int)(Data2->KeyH&0x7f)<<8) + Data2->KeyL;
		int Index = FindCharacterIndex(Key);
		CHARACTER *c = &CharactersClient[Index];
		
		c->GuildStatus = Data2->GuildStatus;				// �������
		c->GuildType = Data2->GuildType;					// ���Ÿ��
		c->GuildRelationShip = Data2->GuildRelationShip;	// ������

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
		g_pMoveCommandWindow->SetCastleOwner((bool)Data2->btCastleOwner);
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
		
		// ��帶ũ ���� Ȯ��
		if( g_GuildCache.IsExistGuildMark(GuildKey) )
			c->GuildMarkIndex = g_GuildCache.GetGuildMarkIndex( GuildKey );
		else
		{
			// ������ ��û
			SendRequestGuildInfo(GuildKey);
			c->GuildMarkIndex = g_GuildCache.MakeGuildMarkIndex( GuildKey );
		}
        
		// ����� ����
		GuildTeam(c);
		
		// ������̳� �����϶� �̴ϸ��� �ٽ� �����Ѵ�.
		if( World == WD_30BATTLECASTLE )
		{
			if( g_pSiegeWarfare )
			{
				if( g_pSiegeWarfare->IsCreated() == false )
				{
					g_pSiegeWarfare->InitMiniMapUI();
					g_pSiegeWarfare->SetGuildData( Hero );
					g_pSiegeWarfare->CreateMiniMapUI();
				}
			}
		}
		
		Offset += sizeof(PRECEIVE_GUILD_ID);
	}
}

void ReceiveGuildInfo( BYTE *ReceiveBuffer )
{
	LPPPRECEIVE_GUILDINFO Data = (LPPPRECEIVE_GUILDINFO)ReceiveBuffer;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	g_GuildCache.SetGuildMark( Data->GuildKey, Data->UnionName, Data->GuildName, Data->Mark );
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Index = g_GuildCache.SetGuildMark( Data->GuildKey, Data->UnionName, Data->GuildName, Data->Mark );
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}

// �����å�� �Ӹ�/����/���� ���
void ReceiveGuildAssign( BYTE *ReceiveBuffer )
{
	char szTemp[MAX_GLOBAL_TEXT_STRING] = "Invalid GuildAssign";
	LPPRECEIVE_GUILD_ASSIGN pData = (LPPRECEIVE_GUILD_ASSIGN)ReceiveBuffer;
	if( pData->byResult == 0x01 )
	{
		switch( pData->byType )
		{
		case 0x01:		// �Ӹ�
			strcpy( szTemp, GlobalText[1374] );
			break;
		case 0x02:		// ����
			strcpy( szTemp, GlobalText[1375] );
			break;
		case 0x03:		// ����
			strcpy( szTemp, GlobalText[1376] );
			break;
		default:
			assert( !"�߸��� �����å ��Ŷ(0xE1)" );
			break;
		}
	}
	else
	{
		switch( pData->byResult )
		{
		case GUILD_ANS_NOTEXIST_GUILD:
			strcpy( szTemp, GlobalText[522] );
			break;
		case GUILD_ANS_NOTEXIST_PERMISSION:
			strcpy( szTemp, GlobalText[1386] );
			break;
		case GUILD_ANS_NOTEXIST_EXTRA_STATUS:
			strcpy( szTemp, GlobalText[1326] );
			break;
		case GUILD_ANS_NOTEXIST_EXTRA_TYPE:
			strcpy( szTemp, GlobalText[1327] );
			break;
		default:
			assert( !"�߸��� �����å ��Ŷ(0xE1)" );
			break;
		}
	}
	g_pChatListBox->AddText("", szTemp, SEASON3B::TYPE_SYSTEM_MESSAGE);
}

void ReceiveGuildRelationShip( BYTE *ReceiveBuffer )
{
	LPPMSG_GUILD_RELATIONSHIP pData = (LPPMSG_GUILD_RELATIONSHIP)ReceiveBuffer;

	g_pGuildInfoWindow->ReceiveGuildRelationShip( pData->byRelationShipType, pData->byRequestType, pData->byTargetUserIndexH, pData->byTargetUserIndexL );
}

void ReceiveGuildRelationShipResult( BYTE *ReceiveBuffer )
{
	char szTemp[MAX_GLOBAL_TEXT_STRING] = "Invalid GuildRelationShipResult";
	LPPMSG_GUILD_RELATIONSHIP_RESULT pData = (LPPMSG_GUILD_RELATIONSHIP_RESULT)ReceiveBuffer;
	if( pData->byResult == 0x01 )
	{
		if( pData->byRelationShipType == 0x01 )	// ��忬��
		{
			if ( pData->byRequestType == 0x01 )	
            {
                strcpy( szTemp, GlobalText[1381] );	// ����
            }
			else if ( pData->byRequestType == 0x02 )
            {
                strcpy( szTemp, GlobalText[1382] );	// Ż��
            }
            else if ( pData->byRequestType == 0x10 )
            {
                strcpy( szTemp, GlobalText[1635] ); //  �������� ����(���)����,��ü����.
            }
		}
		else									// ������
		{
			if( pData->byRequestType == 0x01 )	strcpy( szTemp, GlobalText[1383] );	// �α�
			else								strcpy( szTemp, GlobalText[1384] );	// ����
		}
	}
	else if( pData->byResult == 0 )
	{
		// 1328 "�����߽��ϴ�."
		strcpy( szTemp, GlobalText[1328] );
	}
	else
	{
		switch( pData->byResult )
		{
		case GUILD_ANS_UNIONFAIL_BY_CASTLE:
			strcpy( szTemp, GlobalText[1637] );			// 1637 "���������� ���Ͽ� ���ձ���� ���ѵ˴ϴ�."
			break;
		case GUILD_ANS_NOTEXIST_PERMISSION:
			strcpy( szTemp, GlobalText[1386] );			// 1386 "������ �����ϴ�."
			break;
		case GUILD_ANS_EXIST_RELATIONSHIP_UNION:
			strcpy( szTemp, GlobalText[1250] );			// 1250 "���� ���� �Դϴ�."
			break;
		case GUILD_ANS_EXIST_RELATIONSHIP_RIVAL:
			strcpy( szTemp, GlobalText[1251] );			// 1251 "���� ���� �Դϴ�."
			break;
		case GUILD_ANS_EXIST_UNION:
			strcpy( szTemp, GlobalText[1252] );			// 1252 "��忬���� ���� �մϴ�."
			break;
		case GUILD_ANS_EXIST_RIVAL:
			strcpy( szTemp, GlobalText[1253] );			// 1253 "�����尡 ���� �մϴ�."
			break;
		case GUILD_ANS_NOTEXIST_UNION:
			strcpy( szTemp, GlobalText[1254] );			// 1254 "��忬���� �������� �ʽ��ϴ�."
			break;
		case GUILD_ANS_NOTEXIST_RIVAL:
			strcpy( szTemp, GlobalText[1255] );			// 1255 "�����尡 �������� �ʽ��ϴ�."
			break;
		case GUILD_ANS_NOT_UNION_MASTER:
			strcpy( szTemp, GlobalText[1333] );			// 1333 "��忬�� �����Ͱ� �ƴմϴ�."
			break;
		case GUILD_ANS_NOT_GUILD_RIVAL:
			strcpy( szTemp, GlobalText[1329] );			// 1329 "�����尡 �ƴմϴ�."
			break;
		case GUILD_ANS_CANNOT_BE_UNION_MASTER_GUILD:
			strcpy( szTemp, GlobalText[1331] );			// 1331 "���ձ��������ǹ̴�"
			break;
		case GUILD_ANS_EXCEED_MAX_UNION_MEMBER:
			strcpy( szTemp, GlobalText[1287] );			// 1287 "�ִ� ��� ���� ������ 7���Դϴ�."
			break;
		case GUILD_ANS_CANCEL_REQUEST:
			strcpy( szTemp, GlobalText[1268] );			// 1268 "��û�� ��ҵǾ����ϴ�."
			break;
#ifdef ASG_ADD_GENS_SYSTEM
		case GUILD_ANS_UNION_MASTER_NOT_GENS:
			strcpy( szTemp, GlobalText[2991] );			// 2991	"���� ��� �����Ͱ� �ս� ������ �ȵǾ� �ֽ��ϴ�."
			break;
		case GUILD_ANS_GUILD_MASTER_NOT_GENS:
			strcpy( szTemp, GlobalText[2992] );			// 2992	"��� �����Ͱ� �ս��� ������ �ȵǾ� �ֽ��ϴ�."
			break;
		case GUILD_ANS_UNION_MASTER_DISAGREE_GENS:
			strcpy( szTemp, GlobalText[2993] );			// 2993	"���� ��� �����Ϳ� �ٸ� �ս��� ���ԵǾ� �ֽ��ϴ�."
			break;
#endif	// ASG_ADD_GENS_SYSTEM
		default:
			assert( !"�߸��� �������� ��Ŷ(0xE6)" );
			break;
		}
	}
	g_pChatListBox->AddText("", szTemp, SEASON3B::TYPE_SYSTEM_MESSAGE);	
	
	// ���� ��忬�տ��� Ż�𼺰��ߴٸ� ���Ͽ� ���� �ʱ�ȭ
	int nCharKey = MAKEWORD( pData->byTargetUserIndexL, pData->byTargetUserIndexH );
	if( nCharKey == HeroKey && pData->byResult == 0x01 && pData->byRelationShipType == 0x01 && pData->byRequestType == 0x02 )
		GuildMark[Hero->GuildMarkIndex].UnionName[0] = NULL;
}

void ReceiveBanUnionGuildResult( BYTE *ReceiveBuffer )
{
	LPPMSG_BAN_UNIONGUILD pData = (LPPMSG_BAN_UNIONGUILD)ReceiveBuffer;
	if( pData->byResult == 0x01 )
	{
		if(g_pGuildInfoWindow->GetUnionCount() > 2)
		{
			Sleep(500);
			SendRequestUnionList();
		}
		// �ٲ� ���ո���Ʈ ��û
		g_pGuildInfoWindow->UnionGuildClear();
	}
	else if( pData->byResult == 0 )
	{
		// 1328 "�����߽��ϴ�."
		g_pChatListBox->AddText("", GlobalText[1328], SEASON3B::TYPE_SYSTEM_MESSAGE);	
	}
}

void ReceiveUnionViewportNotify( BYTE *ReceiveBuffer )
{
	LPPMSG_UNION_VIEWPORT_NOTIFY_COUNT pData = (LPPMSG_UNION_VIEWPORT_NOTIFY_COUNT)ReceiveBuffer;
	int Offset = sizeof(PMSG_UNION_VIEWPORT_NOTIFY_COUNT);
	for( int i=0 ; i<pData->byCount ; ++i )
	{
		LPPMSG_UNION_VIEWPORT_NOTIFY pData2 = (LPPMSG_UNION_VIEWPORT_NOTIFY)(ReceiveBuffer+Offset);
		
		// ������� ����
		int nGuildMarkIndex = g_GuildCache.GetGuildMarkIndex( pData2->nGuildKey );
		memcpy( GuildMark[nGuildMarkIndex].UnionName, pData2->szUnionName, sizeof(char)*MAX_GUILDNAME );
		GuildMark[nGuildMarkIndex].UnionName[MAX_GUILDNAME] = NULL;
		
		// ĳ������ ����
		int nCharKey = MAKEWORD( pData2->byKeyL, pData2->byKeyH );
		
		int nCharIndex = FindCharacterIndex(nCharKey);
		CharactersClient[nCharIndex].GuildRelationShip = pData2->byGuildRelationShip;
		
		Offset += sizeof(PMSG_UNION_VIEWPORT_NOTIFY);
	}
}

void ReceiveUnionList( BYTE *ReceiveBuffer )
{
	LPPMSG_UNIONLIST_COUNT pData = (LPPMSG_UNIONLIST_COUNT)ReceiveBuffer;
	g_pGuildInfoWindow->UnionGuildClear();
	if( pData->byResult == 1 )
	{
		int Offset = sizeof(PMSG_UNIONLIST_COUNT);
		for( int i=0 ; i<pData->byCount ; ++i )
		{
			LPPMSG_UNIONLIST pData2 = (LPPMSG_UNIONLIST)(ReceiveBuffer+Offset);
			
			BYTE tmp[64];
			for( int j=0 ; j<64 ; ++j )
			{
				if( j%2 == 0 )
					tmp[j] = ( pData2->GuildMark[j/2]>>4 )&0x0f;
				else
					tmp[j] = pData2->GuildMark[j/2]&0x0f;
			}
			
			g_pGuildInfoWindow->AddUnionList(tmp, pData2->szGuildName, pData2->byMemberCount);
			
			Offset += sizeof(PMSG_UNIONLIST);
		}
	}
}

void ReceiveSoccerTime( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_SOCCER_TIME Data = (LPPRECEIVE_SOCCER_TIME)ReceiveBuffer;
	SoccerTime = Data->Time;
}

void ReceiveSoccerScore( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_SOCCER_SCORE Data = (LPPRECEIVE_SOCCER_SCORE)ReceiveBuffer;
	memcpy(SoccerTeamName[0],Data->Name1,8);
	memcpy(SoccerTeamName[1],Data->Name2,8);
	SoccerTeamName[0][8] = NULL;
	SoccerTeamName[1][8] = NULL;
	GuildWarScore[0] = Data->Score1;
	GuildWarScore[1] = Data->Score2;

	if(GuildWarScore[0] != 255)
	{
		SoccerObserver = true;
		g_pNewUISystem->Show(SEASON3B::INTERFACE_BATTLE_SOCCER_SCORE);
	}
	else
	{
		SoccerObserver = false;
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_BATTLE_SOCCER_SCORE);
	}
	
	vec3_t Position, Angle, Light;
	Position[0]  = (float)(Hero->PositionX+0.5f)*TERRAIN_SCALE;
	Position[1]  = (float)(Hero->PositionY+0.5f)*TERRAIN_SCALE;
	Position[2] = RequestTerrainHeight(Position[0],Position[1]);
	ZeroMemory( Angle, sizeof ( Angle));
	Light[0] = Light[1] = Light[2] = 1.0f;
	CreateEffect(BITMAP_FIRECRACKERRISE,Position,Angle,Light);
}

void ReceiveSoccerGoal( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	char Text[100];
	if(Data->Value == HeroSoccerTeam)
		sprintf(Text,GlobalText[534],GuildMark[Hero->GuildMarkIndex].GuildName);
	else
		sprintf(Text,GlobalText[534],GuildWarName);
	g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
}

void Receive_Master_LevelUp( BYTE *ReceiveBuffer )
{
	LPPMSG_MASTERLEVEL_UP Data = (LPPMSG_MASTERLEVEL_UP)ReceiveBuffer;
	Master_Level_Data.nMLevel			= Data->nMLevel;
	Master_Level_Data.nAddMPoint		= Data->nAddMPoint;
	Master_Level_Data.nMLevelUpMPoint	= Data->nMLevelUpMPoint;
	//	Master_Level_Data.nTotalMPoint		= Data->nTotalMPoint;
	Master_Level_Data.nMaxPoint			= Data->nMaxPoint;
	Master_Level_Data.wMaxLife			= Data->wMaxLife;
	Master_Level_Data.wMaxMana			= Data->wMaxMana;
	Master_Level_Data.wMaxShield		= Data->wMaxShield;
	Master_Level_Data.wMaxBP			= Data->wMaxBP;
	
	unicode::t_char szText[256] = {NULL, };
	WORD iExp = Master_Level_Data.lNext_MasterLevel_Experince - Master_Level_Data.lMasterLevel_Experince;
	sprintf(szText, GlobalText[1750], iExp);
	g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
	
	CharacterMachine->CalulateMasterLevelNextExperience();
	
	OBJECT *o = &Hero->Object;
	
	if(IsMasterLevel(Hero->Class) == true)
	{
		CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,45,o,80,2);
		for ( int i=0; i<19; ++i )
		{
			CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,46,o,80,2);
		}
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x51����[Receive_Master_LevelUp]");
#endif // CONSOLE_DEBUG
}

void Receive_Master_Level_Exp( BYTE *ReceiveBuffer )
{
	LPPMSG_MASTERLEVEL_INFO Data = (LPPMSG_MASTERLEVEL_INFO)ReceiveBuffer;
	Master_Level_Data.nMLevel = Data->nMLevel;
	Master_Level_Data.lMasterLevel_Experince = 0x0000000000000000;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp1;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp2;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp3;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp4;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp5;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp6;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp7;	
	Master_Level_Data.lMasterLevel_Experince <<= 8;
	Master_Level_Data.lMasterLevel_Experince |= Data->btMExp8;
	Master_Level_Data.lNext_MasterLevel_Experince = 0x0000000000000000;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp1;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp2;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp3;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp4;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp5;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp6;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp7;	
	Master_Level_Data.lNext_MasterLevel_Experince <<= 8;
	Master_Level_Data.lNext_MasterLevel_Experince |= Data->btMNextExp8;
	Master_Level_Data.nMLevelUpMPoint			   = Data->nMLPoint;
	
	Master_Level_Data.wMaxLife			= Data->wMaxLife;
	Master_Level_Data.wMaxMana			= Data->wMaxMana;
	Master_Level_Data.wMaxShield		= Data->wMaxShield;
	Master_Level_Data.wMaxBP			= Data->wMaxSkillMana;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x50����[Receive_Master_Level_Exp]");
#endif // CONSOLE_DEBUG
}

void Receive_Master_LevelGetSkill( BYTE *ReceiveBuffer )
{
	LPPMSG_ANS_MASTERLEVEL_SKILL Data = (LPPMSG_ANS_MASTERLEVEL_SKILL)ReceiveBuffer;
	
	if(Data->btResult == 1)
	{
		//�����ߴ�.
		if(Data->nSkillNum > -1)
		{
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			
#ifdef _VS2008PORTING
			for(int i=0; i<MAX_MAGIC; ++i)
#else // _VS2008PORTING
			int i = 0;
			for(i=0; i<MAX_MAGIC; ++i)
#endif // _VS2008PORTING
			{
				switch(Data->nSkillNum)
				{
				case AT_SKILL_ASHAKE_UP:
					if(AT_SKILL_DARK_HORSE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_BLAST_UP:
					if(AT_SKILL_BLAST == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_MANY_ARROW_UP:
					if(AT_SKILL_CROSSBOW == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_TORNADO_SWORDA_UP:
				case AT_SKILL_TORNADO_SWORDB_UP:
					if(AT_SKILL_WHEEL == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_HEAL_UP:
					if(AT_SKILL_HEALING == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_LIFE_UP:
					if(AT_SKILL_VITALITY == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_SOUL_UP:
					if(AT_SKILL_WIZARDDEFENSE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_FIRE_BUST_UP:
					if(AT_SKILL_LONGPIER_ATTACK == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_HELL_FIRE_UP:
					if(AT_SKILL_HELL == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
#ifdef PJH_SEASON4_MASTER_RANK4
				case AT_SKILL_EVIL_SPIRIT_UP:
				case AT_SKILL_EVIL_SPIRIT_UP_M:
					if(AT_SKILL_EVIL == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_BLOW_UP:
					if(AT_SKILL_ONETOONE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_ANGER_SWORD_UP:
					if(AT_SKILL_FURY_STRIKE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_BLOOD_ATT_UP:
					if(AT_SKILL_REDUCEDEFENSE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_POWER_SLASH_UP:
					if(AT_SKILL_ICE_BLADE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_FIRE_SCREAM_UP:
					if(AT_SKILL_DARK_SCREAM == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_DEF_POWER_UP:
					if(AT_SKILL_DEFENSE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_ATT_POWER_UP:
					if(AT_SKILL_ATTACK == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_ICE_UP:
					if(AT_SKILL_BLAST_FREEZE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
#endif //PJH_SEASON4_MASTER_RANK4
#ifdef PJH_ADD_MASTERSKILL
				case AT_SKILL_ALICE_SLEEP_UP:
					if(AT_SKILL_ALICE_SLEEP == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_ALICE_CHAINLIGHTNING_UP:
					if(AT_SKILL_ALICE_CHAINLIGHTNING == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_LIGHTNING_SHOCK_UP:
					if(AT_SKILL_LIGHTNING_SHOCK == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
				case AT_SKILL_ALICE_DRAINLIFE_UP:
					if(AT_SKILL_ALICE_DRAINLIFE == CharacterAttribute->Skill[i])
						CharacterAttribute->Skill[i] = 0;
					break;
#endif
				}
			}
			bool Check_Add = false;
#ifdef _VS2008PORTING
			for(int i=0; i<MAX_MAGIC; ++i)
#else // _VS2008PORTING
			for(i=0; i<MAX_MAGIC; ++i)
#endif // _VS2008PORTING
			{
				if(Data->nSkillNum%5 != 0)
				{
					if(CharacterAttribute->Skill[i] == (Data->nSkillNum - 1))
					{
						CharacterAttribute->Skill[i] = Data->nSkillNum;
						Check_Add = true;
						break;
					}
				}
			}
			if(Check_Add == false)
			{
#ifdef _VS2008PORTING
				for(int i=0; i<MAX_MAGIC; ++i)
#else // _VS2008PORTING
				for(i=0; i<MAX_MAGIC; ++i)
#endif // _VS2008PORTING
				{
					if(CharacterAttribute->Skill[i] == 0)
					{
						CharacterAttribute->Skill[i] = Data->nSkillNum;
						break;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
		}
	}
	Master_Level_Data.nMLevelUpMPoint			   = Data->nMLPoint;
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x52����[Receive_Master_LevelGetSkill]");
#endif // CONSOLE_DEBUG
}

void ReceiveServerCommand( BYTE *ReceiveBuffer )
{
	LPPRECEIVE_SERVER_COMMAND Data = (LPPRECEIVE_SERVER_COMMAND)ReceiveBuffer;
	switch( Data->Cmd1)
	{
	case 2:	// ���ķ� + ����
		PlayBuffer(SOUND_MEDAL);
		break;
	case 0:	// ����
		{
			vec3_t Position, Angle, Light;
			Position[0]  = (float)(Data->Cmd2+0.5f)*TERRAIN_SCALE;
			Position[1]  = (float)(Data->Cmd3+0.5f)*TERRAIN_SCALE;
			Position[2] = RequestTerrainHeight(Position[0],Position[1]);
			ZeroMemory( Angle, sizeof ( Angle));
			Light[0] = Light[1] = Light[2] = 1.0f;
#ifdef YDG_ADD_FIRECRACKER_ITEM
			CreateEffect(BITMAP_FIRECRACKER0001,Position,Angle,Light,0);
#else	// YDG_ADD_FIRECRACKER_ITEM
			CreateEffect(BITMAP_FIRECRACKERRISE,Position,Angle,Light);
#endif	// YDG_ADD_FIRECRACKER_ITEM
		}
		break;
	case 1:	// �޽��� �ڽ�
        // Data->Cmd2 : 46�� ���� ��� (�߰� ���ڴ� �� �ڷ� ���ּ���)
#ifndef LIMIT_CHAOS_MIX
		if(Data->Cmd2 >= 20)
		{
			SEASON3B::CreateOkMessageBox(GlobalText[830 + Data->Cmd2 - 20]);
		}
		else
		{
			SEASON3B::CreateOkMessageBox(GlobalText[650 + Data->Cmd2]);	
		}
#endif //LIMIT_CHAOS_MIX
		break;
		
	case 3:	// (����)�̺�Ʈ �޽��� �ڽ�
		SEASON3B::CreateOkMessageBox(GlobalText[710+Data->Cmd2]);
		break;
		
#ifdef LENA_EXCHANGE_ZEN
    case 4:	// (����)�̺�Ʈ ȯ�� �޽��� �ڽ�
		SEASON3B::CreateOkMessageBox(GlobalText[725+Data->Cmd2]);
        break;
#endif // LENA_EXCHANGE_ZEN
		
	case 5:	// NPC ���� ��ȭ
		{
			SEASON3B::CDialogMsgBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDialogMsgBoxLayout), &pMsgBox);
			if(pMsgBox)
			{
				pMsgBox->AddMsg(g_DialogScript[Data->Cmd2].m_lpszText);
			}
		}
		break;
		
    case 6: //  ���� ����. ( 0: ��� �����ϰ� �Ͷ�. )
		SEASON3B::CreateOkMessageBox(GlobalText[449]);
        break;
		
#ifdef PCROOM_EVENT
	case 7:
#ifdef KJH_ADD_NPC_ROURKE_PCROOM_EVENT_MESSAGEBOX
		switch(Data->Cmd2) 
		{
		case 0:				// 0. �������� ���޹����ðڽ��ϱ�?
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CPCRoomItemGiveLayout));
			break;
		case 1:				// 1. �̺�Ʈ �Ⱓ�� �ƴ�. 
			SEASON3B::CreateOkMessageBox(GlobalText[2021]);
			break;
		case 2:				// 2. �̹� ������ ���� ����.
			SEASON3B::CreateOkMessageBox(GlobalText[2022]);
			break;
		case 3:				// 3. ���� 
			SEASON3B::CreateOkMessageBox(GlobalText[2023]);
			break;
		case 4:				// 4. ���� �ڰ� ����.
			SEASON3B::CreateOkMessageBox(GlobalText[2024]);
			break;
		}
#else // KJH_ADD_NPC_ROURKE_PCROOM_EVENT_MESSAGEBOX
		if (0 == Data->Cmd2)	// 0 ������ ���� ����.
		{
			ShowCheckBox(1, 2020, MESSAGE_PCROOM_EVENT);
		}
		else					
		{
			// 1 �̺�Ʈ �Ⱓ�� �ƴ�. 2  �̹� ������ ���� ����.
			// 3 ����. 4 ���� �ڰ� ����.
			SEASON3B::CreateOkMessageBox(GlobalText[2020 + Data->Cmd2]);
		}
#endif // KJH_ADD_NPC_ROURKE_PCROOM_EVENT_MESSAGEBOX
		break;
		
#endif	// PCROOM_EVENT
	case 13:
		SEASON3B::CreateOkMessageBox(GlobalText[1826]);
		break;
		
	case 14:	// ȭ��Ʈ ���� �̺�Ʈ
		{
			switch(Data->Cmd2) 
			{
			case 0:	// ������ ���� ����ڰ� ����
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CWhiteAngelEventLayout));
				break;
				
			case 1:	// ������ ���� ����ڰ� �ƴ�
				SEASON3B::CreateOkMessageBox(GlobalText[2024]);
				break;
				
			case 2:	// �������� �̹� ���޵Ǿ���.
				SEASON3B::CreateOkMessageBox(GlobalText[2022]);
				break;
				
			case 3:	// ����
				SEASON3B::CreateOkMessageBox(GlobalText[2023]);
				break;
				
			case 4:	// ������ ���� ����
				//ShowCustomMessageBox(GlobalText[858]);
				break;
				
			case 5:	// ������ ���� ����
				SEASON3B::CreateOkMessageBox(GlobalText[2023]);
				break;
			}
		}
		break;
		
#ifdef PRUARIN_EVENT07_3COLORHARVEST		// 07�⵵ 3COLOR & �߼� �̺�Ʈ
	case 15:
		{
			switch(Data->Cmd2) 
			{
			case 0:				// �̹� ���޵Ǿ����ϴ�.
				SEASON3B::CreateOkMessageBox(GlobalText[2022]);
				break;
			case 1:				// �������� ���޹����ðڽ��ϱ�?
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CHarvestEventLayout));
				break;
			case 2:				// ������ ���޽���
				SEASON3B::CreateOkMessageBox(GlobalText[2023]);
				break;
			}
		}
		break;
#endif // PRUARIN_EVENT07_3COLORHARVEST
		
#ifdef LDK_ADD_SANTA_NPC
	case 16:
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox = NULL;

			switch(Data->Cmd2)
			{
			case 0: //���ʹ湮 2588
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSantaTownSantaMsgBoxLayout), &pMsgBox);
				pMsgBox->AddMsg(GlobalText[2588]);	// 2588 "��Ÿ������ �������, �����ֽ� �������� ������.... "
				break;
			case 1: //�Ϲݹ湮 2585
				SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSantaTownSantaMsgBoxLayout), &pMsgBox);
				pMsgBox->AddMsg(GlobalText[2585]);	// 2585 "��Ÿ������ �������. ������ �޾ư�����"
				break;
			case 2: //�̹� �������� �޾ư���
				SEASON3B::CreateOkMessageBox(GlobalText[2587]);
				break;
			case 3: //����(���ο���)
				SEASON3B::CreateOkMessageBox(GlobalText[2023]);
				break;
			}
		}
		break;
#endif //LDK_ADD_SANTA_NPC
		
#ifdef LDK_ADD_SNOWMAN_NPC
	case 17: //����ƽ��� �̵� �Ͻðڽ��ϱ�?
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSantaTownLeaveMsgBoxLayout));
		break;
#endif //LDK_ADD_SNOWMAN_NPC
		
		//����ĳ�� �ؽ�Ʈ Ȯ��
	case 47:
	case 48:
	case 49:
		SEASON3B::CreateOkMessageBox(GlobalText[1823+Data->Cmd1-47]);
		break;
		
	case 55:
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[39]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
	case 56:
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[56]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
	case 57:
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[57]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
#ifdef CSK_EVENT_CHERRYBLOSSOM
	case 58: 
		{
			WORD Key = ((WORD)(Data->Cmd2)<<8)+Data->Cmd3;
			Key &= 0x7FFF;
			int Index = FindCharacterIndex(Key);					// �ε����� ã�Ƽ� ����
			if( Index >= 0 && Index != MAX_CHARACTERS_CLIENT ) {
				OBJECT* to = &CharactersClient[Index].Object;
				if( to != NULL ) {
					CreateEffect( MODEL_EFFECT_SKURA_ITEM, to->Position, to->Angle, to->Light, 0, to );
					PlayBuffer(SOUND_CHERRYBLOSSOM_EFFECT0, to);
				}
			}
		}
		break;
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef YDG_ADD_FIRECRACKER_ITEM
	case 59:	// ũ�������� ����
		{
			vec3_t Position, Angle, Light;
			Position[0]  = (float)(Data->Cmd2+0.5f)*TERRAIN_SCALE;
			Position[1]  = (float)(Data->Cmd3+0.5f)*TERRAIN_SCALE;
			Position[2] = RequestTerrainHeight(Position[0],Position[1]);
			ZeroMemory( Angle, sizeof ( Angle));
			Light[0] = Light[1] = Light[2] = 1.0f;
			CreateEffect(BITMAP_FIRECRACKER0001,Position,Angle,Light,1);
		}
#endif	// YDG_ADD_FIRECRACKER_ITEM
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	case 60:	// ��Ȱ�� ���� ��� ����
		g_PortalMgr.ResetRevivePosition();
		break;
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	case 61:	// �̵��� ���� ��� ����
		g_PortalMgr.ResetPortalPosition();
		break;
#endif	// YDG_ADD_CS5_PORTAL_CHARM
	}
}

///////////////////////////////////////////////////////////////////////////////
// �ͽ� ����
///////////////////////////////////////////////////////////////////////////////

void ReceiveMix( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT_ITEM Data = (LPPHEADER_DEFAULT_ITEM)ReceiveBuffer;
	
	switch(Data->Index)
	{
    case 0:	// ����
		{
#ifdef LEM_ADD_LUCKYITEM
			if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYITEMWND) && g_pLuckyItemWnd->GetAct() )
			{
				g_pLuckyItemWnd->GetResult( 0, Data->Index );
				break;
			}
#endif // LEM_ADD_LUCKYITEM
			g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
			unicode::t_char szText[256] = { 0, };
			switch (g_MixRecipeMgr.GetMixInventoryType())
			{
			case SEASON3A::MIXTYPE_GOBLIN_NORMAL:
			case SEASON3A::MIXTYPE_GOBLIN_CHAOSITEM:
			case SEASON3A::MIXTYPE_GOBLIN_ADD380:
#ifdef ADD_SOCKET_MIX
			case SEASON3A::MIXTYPE_EXTRACT_SEED:
			case SEASON3A::MIXTYPE_SEED_SPHERE:
#endif	// ADD_SOCKET_MIX
				unicode::_sprintf(szText, GlobalText[594]);		// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
				// 			case SEASON3A::MIXTYPE_TRAINER:
				// 				unicode::_sprintf(szText, GlobalText[1208]);	// ��Ȱ ����
				// 				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				// 				break;
			case SEASON3A::MIXTYPE_OSBOURNE:
				unicode::_sprintf(szText, GlobalText[2105], GlobalText[2061]);	// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
			case SEASON3A::MIXTYPE_JERRIDON:
				unicode::_sprintf(szText, GlobalText[2105], GlobalText[2062]);	// ȯ�� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
			case SEASON3A::MIXTYPE_ELPIS:
				unicode::_sprintf(szText, GlobalText[2112], GlobalText[2063]);	// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
#ifdef PSW_NEW_CHAOS_CARD
			case SEASON3A::MIXTYPE_CHAOS_CARD:
				unicode::_sprintf(szText, GlobalText[2112], GlobalText[2265]);	// ī���� ī�� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
#endif	// PSW_NEW_CHAOS_CARD
#ifdef CSK_EVENT_CHERRYBLOSSOM
			case SEASON3A::MIXTYPE_CHERRYBLOSSOM:
				unicode::_sprintf(szText, GlobalText[2112], GlobalText[2560]);	// ���� ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
				break;
#endif	// CSK_EVENT_CHERRYBLOSSOM
			}
		}
		break;
    case 1:	// ����
		{
#ifdef LEM_ADD_LUCKYITEM
			if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYITEMWND) && g_pLuckyItemWnd->GetAct() )	
			{
				g_pLuckyItemWnd->GetResult(1, 0, Data->Item);
				break;
			}
#endif // LEM_ADD_LUCKYITEM
			g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
			unicode::t_char szText[256] = { 0, };
			switch (g_MixRecipeMgr.GetMixInventoryType())
			{
			case SEASON3A::MIXTYPE_GOBLIN_NORMAL:
			case SEASON3A::MIXTYPE_GOBLIN_CHAOSITEM:
			case SEASON3A::MIXTYPE_GOBLIN_ADD380:
#ifdef ADD_SOCKET_MIX
			case SEASON3A::MIXTYPE_EXTRACT_SEED:
			case SEASON3A::MIXTYPE_SEED_SPHERE:
#endif	// ADD_SOCKET_MIX
				unicode::_sprintf(szText, GlobalText[595]);		// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
				// 			case SEASON3A::MIXTYPE_TRAINER:
				// 				unicode::_sprintf(szText, GlobalText[1209]);	// ��Ȱ ����
				// 				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				// 				break;
			case SEASON3A::MIXTYPE_OSBOURNE:
				unicode::_sprintf(szText, GlobalText[2106], GlobalText[2061]);	// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
			case SEASON3A::MIXTYPE_JERRIDON:
				unicode::_sprintf(szText, GlobalText[2106], GlobalText[2062]);	// ȯ�� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
			case SEASON3A::MIXTYPE_ELPIS:
				unicode::_sprintf(szText, GlobalText[2113], GlobalText[2063]);	// ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
#ifdef PSW_NEW_CHAOS_CARD
			case SEASON3A::MIXTYPE_CHAOS_CARD:
				unicode::_sprintf(szText, GlobalText[2113], GlobalText[2265]);	// ī���� ī�� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
#endif	// PSW_NEW_CHAOS_CARD
#ifdef CSK_EVENT_CHERRYBLOSSOM
			case SEASON3A::MIXTYPE_CHERRYBLOSSOM:
				unicode::_sprintf(szText, GlobalText[2113], GlobalText[2560]);	// ���� ���� ����
				g_pChatListBox->AddText("", szText, SEASON3B::TYPE_SYSTEM_MESSAGE);
				break;
#endif	// CSK_EVENT_CHERRYBLOSSOM
			}
			
			g_pMixInventory->DeleteAllItems();
			g_pMixInventory->InsertItem(0, Data->Item);
			
			PlayBuffer(SOUND_MIX01);
			PlayBuffer(SOUND_JEWEL01);
		}
		break;
    case 2:	// ������
	case 0x0B:
		{
			g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_READY);
			g_pChatListBox->AddText("", GlobalText[596], SEASON3B::TYPE_ERROR_MESSAGE);
		}
		break;
	case 4:	// �ʴ���� ���� 10�̻�
		SEASON3B::CreateOkMessageBox(GlobalText[649]);
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		break;
		
	case 9:	// ����� ���� 10 �̻�
		SEASON3B::CreateOkMessageBox(GlobalText[689]);
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		break;
		
    case 100:    //  ���û� ���� ����.
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		g_pMixInventory->DeleteAllItems();
		g_pMixInventory->InsertItem(0, Data->Item);
        break;
	case 3:	// �Ǹ��� ����,�� ���� ����
	case 5:	// ��ǰ
	case 7:
	case 8:
	case 0x0A:

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ Ƽ�� ��ȯ ���н� �޼��� [lem_2010.9.8]
	case 0x20:
		if( g_pLuckyItemWnd->GetAct() )	
		{
			g_pLuckyItemWnd->GetResult(0, Data->Index, Data->Item);
		}
	break;
#endif // LEM_ADD_LUCKYITEM
	default:
		g_pMixInventory->SetMixState(SEASON3B::CNewUIMixInventory::MIX_FINISHED);
		break;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x86����[ReceiveMix(%d)]", Data->Index);
#endif // CONSOLE_DEBUG
}

void ReceiveMixExit( BYTE *ReceiveBuffer )
{
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x87����[ReceiveMixExit]");
#endif // CONSOLE_DEBUG
}

//////////////////////////////////////////////////////////////////////////
//���� ���� ���� �Լ�
//////////////////////////////////////////////////////////////////////////
void ReceiveGemMixResult(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_JEWEL_MIX Data = (LPPMSG_ANS_JEWEL_MIX)ReceiveBuffer;
	char sBuf[256];
	memset(sBuf, 0, 256);
	switch(Data->m_iResult)
	{
	case 0:
	case 2:
	case 3:
		{
			sprintf(sBuf, "%s%s %s", GlobalText[1801], GlobalText[1816], GlobalText[868]);
			g_pChatListBox->AddText("", sBuf, SEASON3B::TYPE_SYSTEM_MESSAGE);
			COMGEM::GetBack();
		}
		break;
	case 1:
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGemIntegrationUnityResultMsgBoxLayout));
		}
		break;
	case 4:
		{
			g_pChatListBox->AddText("", GlobalText[1817], SEASON3B::TYPE_SYSTEM_MESSAGE);
			COMGEM::GetBack();
		}
		break;
	case 5:
		{
			g_pChatListBox->AddText("", GlobalText[1811], SEASON3B::TYPE_SYSTEM_MESSAGE);
			COMGEM::GetBack();
		}
		break;
	}
}

void ReceiveGemUnMixResult(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_JEWEL_UNMIX Data = (LPPMSG_ANS_JEWEL_UNMIX)ReceiveBuffer;
	char sBuf[256];
	memset(sBuf, 0, 256);
	
	switch(Data->m_iResult)
	{
	case 0:
	case 5:
		{
			sprintf(sBuf, "%s%s %s", GlobalText[1800], GlobalText[1816], GlobalText[868]);
			g_pChatListBox->AddText("", sBuf, SEASON3B::TYPE_SYSTEM_MESSAGE);
			COMGEM::GetBack();
		}
		break;
	case 1:
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGemIntegrationDisjointResultMsgBoxLayout));
		}
		break;
	case 2:
	case 3:
	case 4:
	case 6:
		{
			g_pChatListBox->AddText("", GlobalText[1812], SEASON3B::TYPE_SYSTEM_MESSAGE);	
			COMGEM::GetBack();
		}
		break;
	case 7:
		{
			g_pChatListBox->AddText("", GlobalText[1815], SEASON3B::TYPE_SYSTEM_MESSAGE);
			COMGEM::GetBack();
		}
		break;
	case 8:
		{
			g_pChatListBox->AddText("", GlobalText[1811], SEASON3B::TYPE_SYSTEM_MESSAGE);	
			COMGEM::GetBack();
		}
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////
// �Ǹ��� ���� ���� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReceiveMoveToDevilSquareResult( BYTE *ReceiveBuffer )
{
	g_pNewUISystem->Hide( SEASON3B::INTERFACE_DEVILSQUARE );
	
	LPPHEADER_DEFAULT Data = ( LPPHEADER_DEFAULT)ReceiveBuffer;
	switch ( Data->Value)
	{
	case 0:	// ����
		break;
	case 1: // �ʴ���� ����
		SEASON3B::CreateOkMessageBox(GlobalText[677]);
		break;
		
	case 2: // �������� �ð��� ������.
		SEASON3B::CreateOkMessageBox(GlobalText[678]);
		break;
		
	case 3: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[686]);
		break;
		
	case 4: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[687]);
		break;
		
	case 5: // �ο��� �� ���� ������.
		SEASON3B::CreateOkMessageBox(GlobalText[679]);
		break;
		
	case 6:	// "���� ���¿����� �Ǹ��� ���忡 ������ �Ұ����մϴ�."
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[39]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
	}
}

void ReceiveDevilSquareOpenTime( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = ( LPPHEADER_DEFAULT)ReceiveBuffer;
	if ( 0 == Data->Value)	// ���� �ð�(��)
	{
		SEASON3B::CreateOkMessageBox(GlobalText[643]);
	}
	else
	{
		unicode::t_char strText[128];
		unicode::_sprintf(strText, GlobalText[644], ( int)Data->Value);
		SEASON3B::CreateOkMessageBox(strText);
	}
}

void ReceiveDevilSquareCountDown( BYTE *ReceiveBuffer )
{
	LPPHEADER_DEFAULT Data = ( LPPHEADER_DEFAULT)ReceiveBuffer;
	
	if( g_CursedTemple->IsCursedTemple() )
	{
		if( Data->Value == TYPE_MATCH_CURSEDTEMPLE_ENTER_CLOSE
			|| Data->Value == TYPE_MATCH_CURSEDTEMPLE_GAME_START )
		{
			g_CursedTemple->SetInterfaceState(false, 0);
			matchEvent::StartMatchCountDown( Data->Value + 1);
		}
	}
#ifdef YDG_ADD_DOPPELGANGER_EVENT
	else if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4)
	{
		if( ((BYTE)(Data->Value + 1) >= TYPE_MATCH_DOPPELGANGER_ENTER_CLOSE && (BYTE)(Data->Value + 1) <= TYPE_MATCH_DOPPELGANGER_CLOSE) || (BYTE)(Data->Value + 1) == TYPE_MATCH_NONE )
		{
			matchEvent::StartMatchCountDown((BYTE)(Data->Value + 1));
		}
	}
#endif	// YDG_ADD_DOPPELGANGER_EVENT
	else
	{
		matchEvent::StartMatchCountDown( Data->Value + 1);
	}
}

void ReceiveDevilSquareRank( BYTE *ReceiveBuffer )
{
	LPPDEVILRANK Data = ( LPPDEVILRANK)ReceiveBuffer;
    matchEvent::SetMatchResult ( Data->m_Count, Data->m_MyRank, ( MatchResult*)&Data->m_byRank, Data->m_MyRank );
}


///////////////////////////////////////////////////////////////////////////////
// ���� ĳ�� ���� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReceiveMoveToEventMatchResult( BYTE *ReceiveBuffer )
{
	g_pNewUISystem->HideAll();
	
	LPPHEADER_DEFAULT Data = ( LPPHEADER_DEFAULT)ReceiveBuffer;
	switch ( Data->Value)
	{
	case 0:	// ����
		break;
	case 1: // ������䰡 ����
		SEASON3B::CreateOkMessageBox(GlobalText[854]);
		break;
		
	case 2: // �������� �ð��� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[852], GlobalText[1146]);
			SEASON3B::CreateOkMessageBox(strText);
        }
		break;
		
	case 3: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[686]);
		break;
		
	case 4: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[687]);
		break;
		
	case 5: // �ο��� �� ���� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[853], GlobalText[1146], MAX_BLOOD_CASTLE_MEN);
			SEASON3B::CreateOkMessageBox(strText);
        }
		break;
		
	case 6:	// �Ϸ翡 6���� ���尡���մϴ�
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[867], 6);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
    case 7: //  "���� ���¿����� ����ĳ���� ������ �Ұ����մϴ�."
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[56]);
			SEASON3B::CreateOkMessageBox(strText);	
		}
        break;
    case 8: //  �������� �ð��� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[852], GlobalText[1147]);
			SEASON3B::CreateOkMessageBox(strText);
        }
        break;
		
    case 9: //  �ο��� �� ���� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[853], GlobalText[1147], MAX_CHAOS_CASTLE_MEN);
			SEASON3B::CreateOkMessageBox(strText);
        }
        break;
	}
}

void ReceiveEventZoneOpenTime( BYTE *ReceiveBuffer )
{
	LPPHEADER_MATCH_OPEN_VALUE Data = (LPPHEADER_MATCH_OPEN_VALUE)ReceiveBuffer;
	if (Data->Value == 1)			// �Ǹ��Ǳ��� �����ð�
	{
		if ( 0 == Data->KeyH)	// ���� �ð�(��)
		{
			SEASON3B::CreateOkMessageBox(GlobalText[643]);
		}
		else
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[644], (int)Data->KeyH);
			SEASON3B::CreateOkMessageBox(strText);
		}
	}
	else if (Data->Value == 2)	// ����ĳ�� �����ð�
	{
		unicode::t_char strText[256];
		if(0 == Data->KeyH)
		{
			unicode::_sprintf(strText, GlobalText[850], GlobalText[1146]);
		}
		else
		{
			unicode::_sprintf(strText, GlobalText[851], ( int)Data->KeyH, GlobalText[1146]);
		}
		SEASON3B::CreateOkMessageBox(strText);
	}
    else if ( Data->Value==4 )    //  ī����ĳ�� ���� �ð�.
    {
#ifdef KJW_FIX_CHAOSCASTLE_MESSAGE
#endif // KJW_FIX_CHAOSCASTLE_MESSAGE
		WORD time = MAKEWORD ( Data->KeyL, Data->KeyH );
        
        if ( 0 == time )	// ���� �ð�(��)
		{
			char szOpenTime1[256] = {0, };
			char szOpenTime2[256] = {0, };
			
			sprintf( szOpenTime1, GlobalText[850], GlobalText[1147] );
			sprintf( szOpenTime2, GlobalText[1156], GlobalText[1147], Data->KeyM, 100 );
			
			GlobalText.Remove(1154);
			GlobalText.Remove(1155);
			GlobalText.Add(1154, szOpenTime1);
			GlobalText.Add(1155, szOpenTime2);
			
			SEASON3B::CNewUICommonMessageBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CChaosCastleTimeCheckMsgBoxLayout), &pMsgBox);
			if(pMsgBox)
			{
				pMsgBox->AddMsg(GlobalText[1154]);
				pMsgBox->AddMsg(GlobalText[1155]);
			}
		}
		else
		{
		/* ������ - Ȯ�� ���
		#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
		wsprintf ( GlobalText[1154], GlobalText[851], time, GlobalText[1147] );
		
		  #else
			*/
            char Text[256];
            int Hour = (int)(time/60);
            int Mini = (int)(time)-(Hour*60);
			
			char szOpenTime[256] = {0, };
			
			/*
			#ifdef PHIL_LANGUAGE_PROBLEM
			if(Hour != 0) wsprintf ( Text, GlobalText[1167], GlobalText[1147], Hour, Mini );
			else wsprintf ( Text, GlobalText[851], Mini, GlobalText[1147] );
			strcpy( GlobalText[1154], Text);
			#else
			wsprintf ( GlobalText[1154], GlobalText[1164], Hour );
			wsprintf ( Text, GlobalText[851], Mini, GlobalText[1147] );
			strcat ( GlobalText[1154], Text );
			#endif //PHIL_LANGUAGE_PROBLEM
			*///??
			
			wsprintf ( szOpenTime, GlobalText[1164], Hour );
			wsprintf ( Text, GlobalText[851], Mini, GlobalText[1147] );
			strcat ( szOpenTime, Text );
			
			GlobalText.Remove(1154);
			GlobalText.Add(1154, szOpenTime);
			
			//#endif// SELECTED_LANGUAGE == LANGUAGE_JAPANESE
			
			SEASON3B::CNewUICommonMessageBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CChaosCastleTimeCheckMsgBoxLayout), &pMsgBox);
			if(pMsgBox)
			{
				// 1154 ""
				pMsgBox->AddMsg(GlobalText[1154]);
			}
		}
    }
	else if( Data->Value==5 )
	{
		unicode::t_char strText[256];
		if(0 == Data->KeyH)
		{
			unicode::_sprintf(strText, GlobalText[850], GlobalText[2369]);
		}
		else
		{
			unicode::_sprintf(strText, GlobalText[851], ( int)Data->KeyH, GlobalText[2369]);
		}
		SEASON3B::CreateOkMessageBox(strText);
	}
}

//////////////////////////////////////////////////////////////////////////
//  ����� �̵� ��û ���.
//////////////////////////////////////////////////////////////////////////
void ReceiveMoveToEventMatchResult2( BYTE *ReceiveBuffer )
{
	g_pNewUISystem->HideAll();
	
	LPPWHEADER_DEFAULT_WORD Data = ( LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	switch ( Data->Value)
	{
	case 0:	// ����
		break;
	case 1: // �˸´� �𵥵� ����ũ ����.
		SEASON3B::CreateOkMessageBox(GlobalText[854]);
		break;
		
	case 2: // �������� �ð��� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[852], GlobalText[1147]);
			SEASON3B::CreateOkMessageBox(strText);
        }
		break;
		
	case 3: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[686]);
		break;
		
	case 4: // ���� ���� ������ ������. ( �� ������ ����. )
		SEASON3B::CreateOkMessageBox(GlobalText[687]);
		break;
		
	case 5: // �ο��� �� ���� ������.
        {
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[853], GlobalText[1147], MAX_CHAOS_CASTLE_MEN);
			SEASON3B::CreateOkMessageBox(strText);
        }
		break;
		
	case 6:	// �Ϸ翡 6���� ���尡���մϴ�
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[867], 6);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
		
    case 7: //  Zen�� �����Ͽ� ������ �� �����ϴ�.
		SEASON3B::CreateOkMessageBox(GlobalText[423]);
        break;
		
	case 8: //"���� ���¿����� ī���� ĳ���� ������ �Ұ����մϴ�."
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[2043], GlobalText[57]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
//  ����Ǵ� �Ӽ����� �޴´�.
//////////////////////////////////////////////////////////////////////////
void ReceiveSetAttribute ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_SET_MAPATTRIBUTE Data = (LPPRECEIVE_SET_MAPATTRIBUTE)ReceiveBuffer;

	g_ErrorReport.Write("Type:%d \r\n", Data->m_byType);
	
    //  �Ӽ��� ä���.
    switch ( Data->m_byType )
    {
    case 0: //  ���� �Ӽ�.
        {
            if ( InBloodCastle() && Data->m_byMapAttr==TW_NOGROUND )
            {
                SetActionObject ( World, 36, 0, 1.f );
            }
			
            for ( int k=0; k<Data->m_byCount; k++ )
            {
				int dx = Data->m_vAttribute[(k*2)+1].m_byX - Data->m_vAttribute[(k*2)].m_byX + 1;
                int dy = Data->m_vAttribute[(k*2)+1].m_byY - Data->m_vAttribute[(k*2)].m_byY + 1;
				
				g_ErrorReport.Write("count:%d, x:%d, y:%d \r\n", Data->m_byCount, dx, dy);
				
                AddTerrainAttributeRange ( Data->m_vAttribute[(k*2)].m_byX, Data->m_vAttribute[(k*2)].m_byY, dx, dy, Data->m_byMapAttr, 1-Data->m_byMapSetType );
            }
        }
        break;
		
    case 1: //  Ư�� ��ġ �Ӽ�.
        for ( int i=0; i<Data->m_byCount; ++i )
        {
            if ( Data->m_byMapSetType )   //  ����.
            {
				g_ErrorReport.Write("SubTerrainAttribute - count:%d, x:%d, y:%d \r\n", Data->m_byCount, Data->m_vAttribute[i].m_byX, Data->m_vAttribute[i].m_byY);
				SubTerrainAttribute ( Data->m_vAttribute[i].m_byX, Data->m_vAttribute[i].m_byY, Data->m_byMapAttr );
            }
            else                    //  �߰�.
            {
				g_ErrorReport.Write("AddTerrainAttribute - count:%d, x:%d, y:%d \r\n", Data->m_byCount, Data->m_vAttribute[i].m_byX, Data->m_vAttribute[i].m_byY);
				AddTerrainAttribute ( Data->m_vAttribute[i].m_byX, Data->m_vAttribute[i].m_byY, Data->m_byMapAttr );
            }
        }
        break;
    }
}

//////////////////////////////////////////////////////////////////////////
//  ���� ���� �޽���.
//////////////////////////////////////////////////////////////////////////
void ReceiveMatchGameCommand ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_MATCH_GAME_STATE Data = (LPPRECEIVE_MATCH_GAME_STATE)ReceiveBuffer;
	
    matchEvent::SetMatchGameCommand ( Data );
}

#ifdef YDG_ADD_NEW_DUEL_PROTOCOL
void ReceiveDuelRequest(BYTE* ReceiveBuffer)	// ������û
{
	if(g_MessageBox->IsEmpty() == false)
	{
		return;
	}

	LPPMSG_REQ_DUEL_ANSWER Data = (LPPMSG_REQ_DUEL_ANSWER)ReceiveBuffer;
	// �ƹ������� ������ ��û�߽��ϴ� ���ϰڽ��ϱ� â ���
	g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
	
	if(g_pNewUISystem->IsImpossibleDuelInterface() == true)
	{
		g_DuelMgr.SendDuelRequestAnswer(DUEL_ENEMY, FALSE);
		return;
	}
	
	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelMsgBoxLayout));
	PlayBuffer(SOUND_OPEN_DUELWINDOW);
}

void ReceiveDuelStart(BYTE* ReceiveBuffer)	// ������û ���
{
	LPPMSG_ANS_DUEL_INVITE Data = (LPPMSG_ANS_DUEL_INVITE)ReceiveBuffer;
	char szMessage[256];
	if(Data->nResult == 0)
	{
		g_DuelMgr.EnableDuel(TRUE);
		g_DuelMgr.SetHeroAsDuelPlayer(DUEL_HERO);
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
		// 912 "%s ���� ������ ���߽��ϴ�."
		sprintf(szMessage, GlobalText[912], g_DuelMgr.GetDuelPlayerID(DUEL_ENEMY));
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
		
		g_pNewUISystem->Show(SEASON3B::INTERFACE_DUEL_WINDOW);
		PlayBuffer(SOUND_START_DUEL);
	}
	else if (Data->nResult == 15)	// �ź�
	{
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
		// 913 "%s ���� ������û�� �ź��߽��ϴ�."
		sprintf(szMessage, GlobalText[913], g_DuelMgr.GetDuelPlayerID(DUEL_ENEMY));
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
	}
	else if (Data->nResult == 16)	// �� ���̻� ���� ����
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelCreateErrorMsgBoxLayout));
	}
	else if (Data->nResult == 28)	// ������ ���� 30����
	{
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
		// 2704 "%d���� �̻��� ĳ���͸� ������ �����մϴ�."
		sprintf(szMessage, GlobalText[2704], 30);
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
	}
	else if (Data->nResult == 30)	// ������
	{
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
		// 1811 "���� �����մϴ�."
		sprintf(szMessage, GlobalText[1811]);
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
	}
}

void ReceiveDuelEnd(BYTE* ReceiveBuffer)	// ��������
{
	LPPMSG_ANS_DUEL_EXIT Data = (LPPMSG_ANS_DUEL_EXIT)ReceiveBuffer;

	if (Data->nResult == 0)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_DUEL_WINDOW);
		g_DuelMgr.EnableDuel(FALSE);
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL,Data->bIndexH), Data->szID);
		
		g_pChatListBox->AddText("", GlobalText[914], SEASON3B::TYPE_ERROR_MESSAGE);
		
		if(g_wtMatchTimeLeft.m_Type == 2)
			g_wtMatchTimeLeft.m_Time = 0;
		g_DuelMgr.EnablePetDuel(FALSE);	// LHJ - ���� ������ ��ũ ���Ǹ��� ���� ���ϰ� �ϴ� ����
	}
	else
	{
	}
}

void ReceiveDuelScore(BYTE* ReceiveBuffer)	// ������ ���� ����
{
	LPPMSG_DUEL_SCORE_BROADCAST Data = (LPPMSG_DUEL_SCORE_BROADCAST)ReceiveBuffer;

	if(g_DuelMgr.IsDuelPlayer(MAKEWORD(Data->bIndexL1, Data->bIndexH1), DUEL_HERO))
	{
		g_DuelMgr.SetScore(DUEL_HERO, Data->btDuelScore1);
		g_DuelMgr.SetScore(DUEL_ENEMY, Data->btDuelScore2);
	}
	else if(g_DuelMgr.IsDuelPlayer(MAKEWORD(Data->bIndexL2, Data->bIndexH2), DUEL_HERO))
	{
		g_DuelMgr.SetScore(DUEL_HERO, Data->btDuelScore2);
		g_DuelMgr.SetScore(DUEL_ENEMY, Data->btDuelScore1);
	}
	else
	{
		//. �հ� ����Ÿ�� �߸��°��
	}
}

void ReceiveDuelHP(BYTE* ReceiveBuffer)	// ������ ���� ����
{
	LPPMSG_DUEL_HP_BROADCAST Data = (LPPMSG_DUEL_HP_BROADCAST)ReceiveBuffer;

	if(g_DuelMgr.IsDuelPlayer(MAKEWORD(Data->bIndexL1, Data->bIndexH1), DUEL_HERO))
	{
		g_DuelMgr.SetHP(DUEL_HERO, Data->btHP1);
		g_DuelMgr.SetHP(DUEL_ENEMY, Data->btHP2);
		g_DuelMgr.SetSD(DUEL_HERO, Data->btShield1);
		g_DuelMgr.SetSD(DUEL_ENEMY, Data->btShield2);
	}
	else if(g_DuelMgr.IsDuelPlayer(MAKEWORD(Data->bIndexL2, Data->bIndexH2), DUEL_HERO))
	{
		g_DuelMgr.SetHP(DUEL_HERO, Data->btHP2);
		g_DuelMgr.SetHP(DUEL_ENEMY, Data->btHP1);
		g_DuelMgr.SetSD(DUEL_HERO, Data->btShield2);
		g_DuelMgr.SetSD(DUEL_ENEMY, Data->btShield1);
	}
	else
	{
		//. �հ� ����Ÿ�� �߸��°��
	}
}

void ReceiveDuelChannelList(BYTE* ReceiveBuffer)	// ���� ä��(����) ����Ʈ
{
	LPPMSG_ANS_DUEL_CHANNELLIST Data = (LPPMSG_ANS_DUEL_CHANNELLIST)ReceiveBuffer;
	for (int i = 0; i < 4; ++i)
	{
		g_DuelMgr.SetDuelChannel(i, Data->channel[i].bStart, Data->channel[i].bWatch, Data->channel[i].szID1, Data->channel[i].szID2);
	}
}

void ReceiveDuelWatchRequestReply(BYTE* ReceiveBuffer)	// ä��(����) ��û
{
	LPPMSG_ANS_DUEL_JOINCNANNEL Data = (LPPMSG_ANS_DUEL_JOINCNANNEL)ReceiveBuffer;
	if (Data->nResult == 0)
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_DUELWATCH);

		g_DuelMgr.SetCurrentChannel(Data->nChannelId);
		g_DuelMgr.SetDuelPlayer(DUEL_HERO, MAKEWORD(Data->bIndexL1, Data->bIndexH1), Data->szID1);
		g_DuelMgr.SetDuelPlayer(DUEL_ENEMY, MAKEWORD(Data->bIndexL2, Data->bIndexH2), Data->szID2);
	}
	else if (Data->nResult == 16)	// �� ���̻� ���� ����
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelCreateErrorMsgBoxLayout));
	}
	else if (Data->nResult == 27)
	{
		// �� ��á��
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelWatchErrorMsgBoxLayout));
	}
	else
	{
	}
}

void ReceiveDuelWatcherJoin(BYTE* ReceiveBuffer)	// ä��(����) ������ ������
{
	LPPMSG_DUEL_JOINCNANNEL_BROADCAST Data = (LPPMSG_DUEL_JOINCNANNEL_BROADCAST)ReceiveBuffer;
	g_DuelMgr.AddDuelWatchUser(Data->szID);
}

void ReceiveDuelWatchEnd(BYTE* ReceiveBuffer)	// ä��(����) ����
{
	LPPMSG_ANS_DUEL_LEAVECNANNEL Data = (LPPMSG_ANS_DUEL_LEAVECNANNEL)ReceiveBuffer;
	if (Data->nResult == 0)
	{
		g_DuelMgr.RemoveAllDuelWatchUser();
	}
	else
	{
	}
}

void ReceiveDuelWatcherQuit(BYTE* ReceiveBuffer)	// ä��(����) ���� ������
{
	LPPMSG_DUEL_LEAVECNANNEL_BROADCAST Data = (LPPMSG_DUEL_LEAVECNANNEL_BROADCAST)ReceiveBuffer;
	g_DuelMgr.RemoveDuelWatchUser(Data->szID);
}

void ReceiveDuelWatcherList(BYTE* ReceiveBuffer)	// ������ ����Ʈ(All)
{
	g_DuelMgr.RemoveAllDuelWatchUser();
	
	LPPMSG_DUEL_OBSERVERLIST_BROADCAST Data = (LPPMSG_DUEL_OBSERVERLIST_BROADCAST)ReceiveBuffer;
	for (int i = 0; i < Data->nCount; ++i)
	{
		g_DuelMgr.AddDuelWatchUser(Data->user[i].szID);
	}
}

void ReceiveDuelResult(BYTE* ReceiveBuffer)	// ������� ����
{
	LPPMSG_DUEL_RESULT_BROADCAST Data = (LPPMSG_DUEL_RESULT_BROADCAST)ReceiveBuffer;

	char szMessage[256];
	sprintf(szMessage, GlobalText[2689], 10);	// "������ ����Ǿ����ϴ�. %d�� �Ŀ� ������ �̵��˴ϴ�."
	g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_SYSTEM_MESSAGE);

	SEASON3B::CDuelResultMsgBox* lpMsgBox = NULL;
	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelResultMsgBoxLayout), &lpMsgBox);
	if(lpMsgBox)
	{
		lpMsgBox->SetIDs(Data->szWinner, Data->szLoser);
	}
	PlayBuffer(SOUND_OPEN_DUELWINDOW);
}

void ReceiveDuelRound(BYTE* ReceiveBuffer)	// ���� ����/�� �˸�
{
	LPPMSG_DUEL_ROUNDSTART_BROADCAST Data = (LPPMSG_DUEL_ROUNDSTART_BROADCAST)ReceiveBuffer;

	if (Data->nFlag == 0)	// ���� ����
	{
		g_DuelMgr.SetHP(DUEL_HERO, 100);
		g_DuelMgr.SetHP(DUEL_ENEMY, 100);
		g_DuelMgr.SetSD(DUEL_HERO, 100);
		g_DuelMgr.SetSD(DUEL_ENEMY, 100);
		g_DuelMgr.SetFighterRegenerated(TRUE);
	}
	else if (Data->nFlag == 1)	// ���� ����
	{
	}
}

#else	// YDG_ADD_NEW_DUEL_PROTOCOL
#ifdef DUEL_SYSTEM

void ReplyDuelStart(BYTE* ReceiveBuffer)
{
	LPPRECEIVE_DUELSTART Data = (LPPRECEIVE_DUELSTART)ReceiveBuffer;
	
	if(Data->bStart)
	{
		g_bEnableDuel = true;
		g_iDuelPlayerIndex = MAKEWORD(Data->bIndexL,Data->bIndexH);
		strncpy(g_szDuelPlayerID, (const char*)Data->ID, MAX_ID_SIZE);
		g_szDuelPlayerID[10] = NULL;
		
		char szMessage[256];
		// 912 "%s ���� ������ ���߽��ϴ�."
		sprintf(szMessage, GlobalText[912], g_szDuelPlayerID);
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
		
		g_pNewUISystem->Show(SEASON3B::INTERFACE_DUEL_WINDOW);
		PlayBuffer(SOUND_START_DUEL);
	}
	else
	{
		char szMessage[256];
		strncpy(g_szDuelPlayerID, (const char*)Data->ID, MAX_ID_SIZE);
		g_szDuelPlayerID[10] = NULL;
		// 913 "%s ���� ������û�� �ź��߽��ϴ�."
		sprintf(szMessage, GlobalText[913], g_szDuelPlayerID);
		g_pChatListBox->AddText("", szMessage, SEASON3B::TYPE_ERROR_MESSAGE);
	}
}

void NotifyDuelStart(BYTE* ReceiveBuffer)
{
	if(g_MessageBox->IsEmpty() == false)
	{
		return;
	}
	
	LPPNOTIFY_DUELSTART Data = (LPPNOTIFY_DUELSTART)ReceiveBuffer;
	
	g_iDuelPlayerIndex = MAKEWORD(Data->bIndexL,Data->bIndexH);
	strncpy(g_szDuelPlayerID, (const char*)Data->ID, MAX_ID_SIZE);
	g_szDuelPlayerID[10] = NULL;
	
	if(g_pNewUISystem->IsImpossibleDuelInterface() == true)
	{
		SendRequestDuelOk(0, g_iDuelPlayerIndex, g_szDuelPlayerID);
		return;
	}
	
	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDuelMsgBoxLayout));
	PlayBuffer(SOUND_OPEN_DUELWINDOW);
}

void ReplyDuelEnd(BYTE* ReceiveBuffer)
{
	LPPRECEIVE_DUELEND Data = (LPPRECEIVE_DUELEND)ReceiveBuffer;
	
	g_pNewUISystem->Hide(SEASON3B::INTERFACE_DUEL_WINDOW);
	g_bEnableDuel = false;
	
	g_iDuelPlayerIndex = MAKEWORD(Data->bIndexL,Data->bIndexH);
	strncpy(g_szDuelPlayerID, (const char*)Data->ID, MAX_ID_SIZE);
	g_szDuelPlayerID[10] = NULL;
	
	g_pChatListBox->AddText("", GlobalText[914], SEASON3B::TYPE_ERROR_MESSAGE);
	
	if(g_wtMatchTimeLeft.m_Type == 2)
		g_wtMatchTimeLeft.m_Time = 0;
	g_PetEnableDuel = false;	// LHJ - ���� ������ ��ũ ���Ǹ��� ���� ���ϰ� �ϴ� ����
}

void NotifyDuelScore(BYTE* ReceiveBuffer)
{
	LPPNOTIFY_DUELSCORE Data = (LPPNOTIFY_DUELSCORE)ReceiveBuffer;
	
	if(g_iDuelPlayerIndex == MAKEWORD(Data->NumberL1, Data->NumberH1))
	{
		g_iDuelPlayerScore = Data->btDuelScore1;
		g_iMyPlayerScore = Data->btDuelScore2;
	}
	else if(g_iDuelPlayerIndex == MAKEWORD(Data->NumberL2, Data->NumberH2))
	{
		g_iDuelPlayerScore = Data->btDuelScore2;
		g_iMyPlayerScore = Data->btDuelScore1;
	}
	else
	{
		//. �հ� ����Ÿ�� �߸��°��
	}
}

#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_PROTOCOL

void ReceiveCreateShopTitleViewport(BYTE* ReceiveBuffer)
{
	LPPSHOPTITLE_HEADERINFO Header = (LPPSHOPTITLE_HEADERINFO)ReceiveBuffer;
	
	PSHOPTITLE_DATAINFO* pShopTitle = (PSHOPTITLE_DATAINFO*)(ReceiveBuffer+sizeof(PSHOPTITLE_HEADERINFO));
	for(int i=0; i<Header->byCount; i++, pShopTitle++){
		int key = MAKEWORD(pShopTitle->byIndexL, pShopTitle->byIndexH);
		int index = FindCharacterIndex(key);
		if(index >= 0 && index < MAX_CHARACTERS_CLIENT){
			CHARACTER* pPlayer = &CharactersClient[index];
			char szShopTitle[40];
			memcpy(szShopTitle, pShopTitle->szTitle, MAX_SHOPTITLE);
			szShopTitle[MAX_SHOPTITLE] = '\0';
			
			AddShopTitle(key, pPlayer, (const char*)szShopTitle);		//. ���Ŵ� Update���� �ڵ����� �̷�� ����
		}
	}
}

void ReceiveShopTitleChange(BYTE* ReceiveBuffer)
{
	LPPSHOPTITLE_CHANGEINFO Header = (LPPSHOPTITLE_CHANGEINFO)ReceiveBuffer;
	
	int key = MAKEWORD(Header->byIndexL, Header->byIndexH);
	int index = FindCharacterIndex(key);
	if(index >= 0 && index < MAX_CHARACTERS_CLIENT) {
		CHARACTER* pPlayer = &CharactersClient[index];
		char szShopTitle[40];
		memcpy(szShopTitle, Header->szTitle, MAX_SHOPTITLE);
		szShopTitle[MAX_SHOPTITLE] = '\0';
		
		if(strncmp(pPlayer->ID, (const char*)Header->szId, MAX_ID_SIZE) == 0)
			AddShopTitle(key, pPlayer, (const char*)szShopTitle);		//. ���Ŵ� Update���� �ڵ����� �̷�� ����
	}
}

void ReceiveSetPriceResult(BYTE* ReceiveBuffer)
{
	LPPSHOPSETPRICE_RESULTINFO Header = (LPPSHOPSETPRICE_RESULTINFO)ReceiveBuffer;
	
	if(Header->byResult != 0x01 && g_IsPurchaseShop == PSHOPWNDTYPE_SALE) 
	{
		// Header->byResult == 0x06 : ������ ������
		if(SEASON3B::CNewUIInventoryCtrl::GetPickedItem())
		{
			SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();
		}
		RemovePersonalItemPrice(MAX_MY_INVENTORY_INDEX+g_pMyShopInventory->GetTargetIndex(), PSHOPWNDTYPE_SALE);		//. ��� ���
		
		SendRequestInventory();		//. Ȥ�� ���������� �𸣴� �κ��� ���� �޾ƿ´�
		
		g_ErrorReport.Write("@ [Fault] ReceiveSetPriceResult (result : %d)\n", Header->byResult);
	}
}

void ReceiveCreatePersonalShop(BYTE* ReceiveBuffer)
{
	LPCREATEPSHOP_RESULSTINFO Header = (LPCREATEPSHOP_RESULSTINFO)ReceiveBuffer;
	if(Header->byResult == 0x01) 
	{
		g_pMyShopInventory->ChangePersonal( true );
		unicode::t_string title;
		g_pMyShopInventory->GetTitle( title );
		AddShopTitle(Hero->Key, Hero, title.c_str());
	}
	else 
	{
		// Header->btResult == 0x03 : ������ ������
		g_ErrorReport.Write("@ [Fault] ReceiveCreatePersonalShop (result : %d)\n", Header->byResult);
	}
}
void ReceiveDestroyPersonalShop(BYTE* ReceiveBuffer)
{
	LPDESTROYPSHOP_RESULTINFO Header = (LPDESTROYPSHOP_RESULTINFO)ReceiveBuffer;
	if(Header->byResult == 0x01) 
	{
		int key = MAKEWORD(Header->byIndexL, Header->byIndexH);
		int index = FindCharacterIndex(key);
		if(index >= 0 && index < MAX_CHARACTERS_CLIENT) 
		{
			CHARACTER* pPlayer = &CharactersClient[index];
			if(pPlayer == Hero)
			{	//. ������ ���
				g_pMyShopInventory->ChangePersonal( false );
			}
			RemoveShopTitle(pPlayer);
		}
	}
	else 
	{
		g_ErrorReport.Write("@ [Fault] ReceiveDestroyPersonalShop (result : %d)\n", Header->byResult);
	}
}

void ReceivePersonalShopItemList(BYTE* ReceiveBuffer)
{
	LPGETPSHOPITEMLIST_HEADERINFO Header = (LPGETPSHOPITEMLIST_HEADERINFO)ReceiveBuffer;
	if(Header->byResult == 0x01) 
	{	//. ����Ʈ �޾ƿ��� ����
		// â�� ��������� �ݴ´�.
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE))
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_STORAGE);
		}
		//. bugfix by soyaviper 2005/03/16
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INVENTORY))
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_INVENTORY);
		}
		
		//. Seller �ʱ�ȭ
		g_PersonalShopSeller.Initialize();

#ifndef _VS2008PORTING		// #ifndef
		int i;
#endif // _VS2008PORTING
		unicode::t_string temp = (char*)Header->szShopTitle;
		g_pPurchaseShopInventory->ChangeTitleText( temp );
		g_pPurchaseShopInventory->GetInventoryCtrl()->RemoveAllItems();
		
		g_pNewUISystem->Show( SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY );		
		g_pNewUISystem->Show( SEASON3B::INTERFACE_INVENTORY );
		g_pMyInventory->ChangeMyShopButtonStateOpen();
		
		RemoveAllPerosnalItemPrice(PSHOPWNDTYPE_PURCHASE);	//. clear item price table
		LPGETPSHOPITEM_DATAINFO pShopItem = (LPGETPSHOPITEM_DATAINFO)(ReceiveBuffer+sizeof(GETPSHOPITEMLIST_HEADERINFO));
#ifdef _VS2008PORTING
		for(int i=0; i<Header->byCount; i++, pShopItem++) 
#else // _VS2008PORTING
		for(i=0; i<Header->byCount; i++, pShopItem++) 
#endif // _VS2008PORTING
		{
			if(pShopItem->iItemPrice > 0) 
			{
				int itemindex = pShopItem->byPos - (MAX_EQUIPMENT_INDEX + MAX_INVENTORY);
				g_pPurchaseShopInventory->InsertItem( itemindex, pShopItem->byItemInfo );
				AddPersonalItemPrice(pShopItem->byPos, pShopItem->iItemPrice, PSHOPWNDTYPE_PURCHASE);	//. ������ ����Ѵ�.
			}
			else 
			{	
#ifdef CONSOLE_DEBUG
				g_ConsoleDebug->Write(MCD_ERROR, "[ReceivePersonalShopItemList]Item Cound : %d, Item Index : %d, Item Price : %d", Header->byCount, i, pShopItem->iItemPrice);
#endif // CONSOLE_DEBUG	
				//. ������ �̻��ϸ� â�� �ݾƹ�����
				g_ErrorReport.Write("@ ReceivePersonalShopItemList - item price less than zero(%d)\n", pShopItem->iItemPrice);
				
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_INVENTORY);
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_MYSHOP_INVENTORY);		
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY);		
				
				return;
			}
		}
		
		//. Seller ����
		int key = MAKEWORD(Header->byIndexL, Header->byIndexH);
		int index = FindCharacterIndex(key);
		
		g_pPurchaseShopInventory->ChangeShopCharacterIndex( index );
	}
	else 
	{
		switch(Header->byResult)
		{
		case 0x03:
			{
				g_pChatListBox->AddText("", GlobalText[1120], SEASON3B::TYPE_ERROR_MESSAGE);
			}	
			break;
		case 0x04:	//. ������ ������
		default:
			g_ErrorReport.Write("@ [Fault] ReceivePersonalShopItemList (result : %d)\n", Header->byResult);
		}
		
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x05����[ReceivePersonalShopItemList]");
#endif // CONSOLE_DEBUG	
}

void ReceiveRefreshItemList(BYTE* ReceiveBuffer)
{
	LPGETPSHOPITEMLIST_HEADERINFO Header = (LPGETPSHOPITEMLIST_HEADERINFO)ReceiveBuffer;
	
	if (Header->byResult == 0x01 && g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE)
	{
		g_pPurchaseShopInventory->GetInventoryCtrl()->RemoveAllItems();
		
		LPGETPSHOPITEM_DATAINFO pShopItem = (LPGETPSHOPITEM_DATAINFO)(ReceiveBuffer+sizeof(GETPSHOPITEMLIST_HEADERINFO));
		for(int i=0; i<Header->byCount; i++, pShopItem++) 
		{
			int itemindex = pShopItem->byPos - (MAX_EQUIPMENT_INDEX + MAX_INVENTORY);
			g_pPurchaseShopInventory->InsertItem( itemindex, pShopItem->byItemInfo );
			AddPersonalItemPrice(pShopItem->byPos, pShopItem->iItemPrice, PSHOPWNDTYPE_PURCHASE);	//. ������ ����Ѵ�.
		}
	}
	else
	{
#ifdef LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM
		if( Header->byResult == 0x01 )
		{
			CNewUIInventoryCtrl* pCurrentInvenCtrl = g_pPurchaseShopInventory->GetInventoryCtrl();
			
			size_t uiCntInvenCtrl = pCurrentInvenCtrl->GetNumberOfItems();
			g_ErrorReport.Write("@ [Notice] ReceiveRefreshItemList (InventoryCtrl Count Items(%d))\n", uiCntInvenCtrl );
		}
		else
		{
			g_ErrorReport.Write("@ [Fault] ReceiveRefreshItemList (result : %d)\n", Header->byResult);
		}
#else // LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM
		g_ErrorReport.Write("@ [Fault] ReceiveRefreshItemList (result : %d)\n", Header->byResult);
#endif // LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM
	}
}


void ReceivePurchaseItem(BYTE* ReceiveBuffer)
{
	LPPURCHASEITEM_RESULTINFO Header = (LPPURCHASEITEM_RESULTINFO)ReceiveBuffer;
	
	if(Header->byResult == 0x01)
	{
		if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY) )
		{			
			RemovePersonalItemPrice(g_pPurchaseShopInventory->GetSourceIndex(), PSHOPWNDTYPE_PURCHASE);
			g_pPurchaseShopInventory->DeleteItem(g_pPurchaseShopInventory->GetSourceIndex());
			
			int myinvenitemindex = Header->byPos - MAX_EQUIPMENT_INDEX;
			g_pMyInventory->InsertItem( myinvenitemindex, Header->byItemInfo );
		}
		else 
		{	//. �׿��� ��Ȳ�϶�
			RemoveAllPerosnalItemPrice(PSHOPWNDTYPE_PURCHASE);
			int myinvenitemindex = Header->byPos - MAX_EQUIPMENT_INDEX;
			g_pMyInventory->InsertItem( myinvenitemindex, Header->byItemInfo );
		}
	}
	else if(Header->byResult == 0x06)
	{
		g_pChatListBox->AddText("", GlobalText[1166], SEASON3B::TYPE_ERROR_MESSAGE);
		g_pNewUISystem->Hide( SEASON3B::INTERFACE_MYSHOP_INVENTORY );		
		g_pNewUISystem->Hide( SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY );	
	}
	else
	{
		switch(Header->byResult)
		{
		case 0x07:
			{
				// 423 "���� �����մϴ�."
				g_pChatListBox->AddText("", GlobalText[423], SEASON3B::TYPE_ERROR_MESSAGE);
			}
			break;
		case 0x08:
			{
				// 375 "�κ��丮�� ��á���ϴ�."
				g_pChatListBox->AddText("", GlobalText[375], SEASON3B::TYPE_ERROR_MESSAGE);
				
			}
			break;
		case 0x09:	//. ������ ������
		default:
			g_ErrorReport.Write("@ [Fault] ReceivePurchaseItem (result : %d)\n", Header->byResult);
		}
		//. ���Խ���
		SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	}
}

void NotifySoldItem(BYTE* ReceiveBuffer)
{
	LPSOLDITEM_RESULTINFO Header = (LPSOLDITEM_RESULTINFO)ReceiveBuffer;
	char szId[MAX_ID_SIZE+2]= {0,};
	strncpy(szId, (char*)Header->szId, MAX_ID_SIZE);
	szId[MAX_ID_SIZE]= '\0';
	
	//. ȭ�鿡 �ȷ����� �˷��ش�.
	char Text[100];
	sprintf(Text, GlobalText[1122], szId);
	g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);
}

void NotifyClosePersonalShop(BYTE* ReceiveBuffer)
{
	//. ������ ������ ����������� �˷��ش�
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPCLOSEPSHOP_RESULTINFO Header = (LPCLOSEPSHOP_RESULTINFO)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	if( g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE )
	{
		g_pNewUISystem->Hide( SEASON3B::INTERFACE_MYSHOP_INVENTORY );		
		g_pNewUISystem->Hide( SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY );	
		
		g_pChatListBox->AddText("", GlobalText[1126], SEASON3B::TYPE_ERROR_MESSAGE);
	}
}

void ReceiveDisplayEffectViewport(BYTE* ReceiveBuffer)
{
	LPDISPLAYEREFFECT_NOTIFYINFO Header = (LPDISPLAYEREFFECT_NOTIFYINFO)ReceiveBuffer;
	
	int key = MAKEWORD(Header->byIndexL, Header->byIndexH);
	int index = FindCharacterIndex(key);
	if(index >= 0 && index < MAX_CHARACTERS_CLIENT){
		CHARACTER* pPlayer = &CharactersClient[index];
		OBJECT* o = &pPlayer->Object;
		if(o->Kind == KIND_PLAYER) {
			switch(Header->byType) {
			case 0x01:	//. HP up
				{
#ifdef ENABLE_POTION_EFFECT
					CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,5,o);
#endif // ENABLE_POTION_EFFECT
				}
				break;
			case 0x02:	//. MP up
				{
				}
				break;
			case 0x10:	//. Level up
				{
					if(IsMasterLevel(pPlayer->Class) == true)
					{
						CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,45,o,80,2);
						for ( int i=0; i<19; ++i )
						{
							CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,46,o,80,2);
						}
					}
					else
					{
						for ( int i=0; i<15; ++i )
						{
							CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
						}
						CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
					}
					PlayBuffer(SOUND_LEVEL_UP);
				}
				break;
			case 0x03:
				{
					CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,5,o);
				}
				break;
				
			case 0x11:
				{
					if(!InChaosCastle())
					{
						CreateEffect(MODEL_SHIELD_CRASH, o->Position, o->Angle, o->Light, 0, o);
						PlayBuffer(SOUND_SHIELDCLASH);
					}
				}
				break;
#ifdef _PVP_ADD_MOVE_SCROLL
			case 0x20:	// move
				{
					CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,6,o);
				}
				break;
#endif	// _PVP_ADD_MOVE_SCROLL
			}	//. end of switch
		}	//. end of (o->Kind == KIND_PLAYER)
	}
}

int g_iMaxLetterCount = 0;	// �ִ� ���� ��

// ĳ���ͼ��þ����� ĳ���͸� ���ýÿ� ȣ��
void ReceiveFriendList(BYTE* ReceiveBuffer)				// ģ�� ����Ʈ �ޱ�
{
#ifdef KJH_FIX_WOPS_K29708_SHARE_LETTER
	g_pWindowMgr->Reset();						// ģ��â,â���,��������Ʈ �ʱ�ȭ
#else KJH_FIX_WOPS_K29708_SHARE_LETTER
	g_pFriendList->ClearFriendList();
	
#ifdef KJH_FIX_WOPS_K22448_SHARED_CHARACTER_MEMOLIST
	g_pLetterList->ClearLetterList();			// ��������Ʈ �ʱ�ȭ
	g_pWindowMgr->RefreshMainWndLetterList();	// ��������Ʈ ����
#endif // KJH_FIX_WOPS_K22448_SHARED_CHARACTER_MEMOLIST
#endif // KJH_FIX_WOPS_K29708_SHARE_LETTER
	
	LPFS_FRIEND_LIST_HEADER Header = (LPFS_FRIEND_LIST_HEADER)ReceiveBuffer;
	int iMoveOffset = sizeof(FS_FRIEND_LIST_HEADER);
	char szName[MAX_ID_SIZE + 1] = {0};
	for (int i = 0; i < Header->Count; ++i)
	{
		LPFS_FRIEND_LIST_DATA Data = (LPFS_FRIEND_LIST_DATA)(ReceiveBuffer+iMoveOffset);
		strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
		szName[MAX_ID_SIZE] = '\0';
		g_pFriendList->AddFriend(szName, 0, Data->Server);
		iMoveOffset += sizeof(FS_FRIEND_LIST_DATA);
	}
	g_pFriendList->Sort(0);
	g_pFriendList->Sort(1);
	g_pWindowMgr->RefreshMainWndPalList();
	
	// ä�� ���� ��Ƴ�
	g_pWindowMgr->SetServerEnable(TRUE);
	if (g_iChatInputType == 0) SendRequestChangeState(2);	// ������ ä�� ��� �˸�
	
	g_iMaxLetterCount = Header->MaxMemo;
	
	if (Header->MemoCount > 0)
	{
		char temp[MAX_TEXT_LENGTH + 1];
		sprintf(temp, GlobalText[1072], Header->MemoCount, Header->MaxMemo);
		g_pChatListBox->AddText("", temp, SEASON3B::TYPE_SYSTEM_MESSAGE);	// "�����Կ� ������ %d/%d�� �ֽ��ϴ�."
	}
}

void ReceiveAddFriendResult(BYTE* ReceiveBuffer)		// ģ�� ��� ��û ���
{
	LPFS_FRIEND_RESULT Data = (LPFS_FRIEND_RESULT)ReceiveBuffer;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	char szText[MAX_TEXT_LENGTH + 1] = {0};
	strncpy(szText, (const char *)Data->Name, MAX_ID_SIZE);
	szText[MAX_ID_SIZE] = '\0';
	switch(Data->Result)
	{
	case 0x00:	// ĳ���Ͱ� ����
		strcat(szText, GlobalText[1047]);	// "�� �������� �ʴ� ID�Դϴ�."
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText);
		break;
	case 0x01:	// ĳ���� ��� ����
		{
			// "���� ��� ����� �Ǿ����� ���� ��� [��������]���� ǥ�õ˴ϴ�."
			g_pChatListBox->AddText("", GlobalText[1075], SEASON3B::TYPE_SYSTEM_MESSAGE);
			g_pFriendList->AddFriend(szName, 0, Data->Server);
			g_pFriendList->Sort();
			g_pWindowMgr->RefreshMainWndPalList();
			g_pFriendMenu->UpdateAllChatWindowInviteList();
		}
		break;
	case 0x03:	// ģ�� �ִ�� �ʰ�
		strcpy(szText, GlobalText[1048]);	// "���̻� �߰��� �� �����ϴ�. �����ϰ� �߰��ϼ���."
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText);
		break;
	case 0x04:	// �̹� ��ϵ� ģ��
		strcat(szText, GlobalText[1049]);	// "���� �̹� ��ϵǾ� �ֽ��ϴ�."
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText);
		break;
	case 0x05:	// �ڽ��� ����Ҽ� ����
		strcpy(szText, GlobalText[1050]);	// "�ڽ��� ���̵�� ����� �� �����ϴ�."
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText);
		break;
	case 0x06:	// 6���� �̻� ��� ����
		strcpy(szText, GlobalText[1068]);	// "������ ������ 6 �̻��̾�� �����մϴ�."
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText);
		break;
	default:
		break;
	};
}

void ReceiveRequestAcceptAddFriend(BYTE* ReceiveBuffer)	// ģ�� ��� ��û
{
	LPFS_ACCEPT_ADD_FRIEND_RESULT Data = (LPFS_ACCEPT_ADD_FRIEND_RESULT)ReceiveBuffer;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	char szText[MAX_TEXT_LENGTH + 1] = {0};
	strncpy(szText, (const char *)Data->Name, MAX_ID_SIZE);
	szText[MAX_ID_SIZE] = '\0';
	strcat(szText, GlobalText[1051]);	// "������ ���� ģ�� ��û�� ���Խ��ϴ�."
	
#ifdef CSK_BUGFIX_NEWFRIEND_ADD
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_FRIEND) == false)
	{
		g_pNewUISystem->Show(SEASON3B::INTERFACE_FRIEND);
	}
#endif // CSK_BUGFIX_NEWFRIEND_ADD
	
	DWORD dwWindowID = g_pWindowMgr->AddWindow(UIWNDTYPE_QUESTION_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, szText, -1);
	if (dwWindowID != 0)
	{
		((CUIQuestionWindow *)g_pWindowMgr->GetWindow(dwWindowID))->SaveID(szName);
	}
	PlayBuffer(SOUND_FRIEND_LOGIN_ALERT);
}

void ReceiveDeleteFriendResult(BYTE* ReceiveBuffer)		// ģ�� ���� ��û ���
{
	LPFS_FRIEND_RESULT Data = (LPFS_FRIEND_RESULT)ReceiveBuffer;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	switch(Data->Result)
	{
	case 0x00:	// ���� ����
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1052]);	// "�������� ���߽��ϴ�."
		break;
	case 0x01:	// ���� ����
		g_pFriendList->RemoveFriend(szName);
		g_pWindowMgr->RefreshMainWndPalList();
		break;
	default:
		break;
	};
}

void ReceiveFriendStateChange(BYTE* ReceiveBuffer)		// ģ�� ���� ��ȭ
{
	LPFS_FRIEND_STATE_CHANGE Data = (LPFS_FRIEND_STATE_CHANGE)ReceiveBuffer;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	if (Data->Server == 0xFC)
	{
		// ä�� ���� ����
		g_pFriendList->UpdateAllFriendState(0, Data->Server);
		g_pFriendList->Sort();
		g_pWindowMgr->RefreshMainWndPalList();
		g_pFriendMenu->LockAllChatWindow();
		g_pWindowMgr->SetServerEnable(FALSE);
		return;
	}
	g_pFriendList->UpdateFriendState(szName, 0, Data->Server);
	g_pFriendList->Sort();
	g_pWindowMgr->RefreshMainWndPalList();
	g_pFriendMenu->UpdateAllChatWindowInviteList();
	
	// ä�� ���ΰ� ó��
	DWORD dwChatRoomUIID = g_pFriendMenu->CheckChatRoomDuplication(szName);
	if (dwChatRoomUIID > 0)
	{
		CUIChatWindow * pWindow = (CUIChatWindow *)g_pWindowMgr->GetWindow(dwChatRoomUIID);
		if (pWindow == NULL);
		else if (Data->Server >= 0xFD/* || Data->Server == 0xFB*/)
		{
			// ä�� �濡 ������ �������� ǥ��
			pWindow->Lock(TRUE);
		}
		else
		{
			// ä�ù濡 ������ �¶������� ��ȯ
			pWindow->Lock(FALSE);
		}
	}
}

void ReceiveLetterSendResult(BYTE* ReceiveBuffer)		// ���� ���� ��� �ޱ�
{
	LPFS_SEND_LETTER_RESULT Data = (LPFS_SEND_LETTER_RESULT)ReceiveBuffer;
	switch(Data->Result)
	{
	case 0x00:	// ������ ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1053]);	// "������ ������ ���߽��ϴ�. �ٽ� �õ��� �ֽʽÿ�."
		break;
	case 0x01:	// ������ ����
		{
			if (Data->WindowGuid != 0)
				g_pWindowMgr->SendUIMessage(UI_MESSAGE_CLOSE, Data->WindowGuid, 0);
			char temp[MAX_TEXT_LENGTH + 1];
			sprintf(temp, GlobalText[1046], g_cdwLetterCost);
			g_pChatListBox->AddText("", temp, SEASON3B::TYPE_SYSTEM_MESSAGE);	// "������ ���½��ϴ�."
		}
		break;
	case 0x02:	// ���� ������ ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1061]);	// "�޴º��� �������� �� �� ������ ������ �����ϴ�."
		break;
	case 0x03:	// ���̵� �߸� ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1064]);	// "���� ��밡 ���ų� �������� �������� �ʽ��ϴ�."
		break;
	case 0x04:	// �ڱ� �ڽſ��Դ� ������ ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1065]);	// "�ڱ� �ڽſ��Դ� ������ ���� �� �����ϴ�."
		break;
	case 0x06:	// 6���� �̻� ��� ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1068]);	// "������ ������ 6 �̻��̾�� �����մϴ�."
		break;
	case 0x07:	// �� ����
		if (Data->WindowGuid != 0)
			((CUILetterWriteWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid))->SetSendState(FALSE);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[423]);	// "���� �����մϴ�."
		break;
	default:
		break;
	};
}

void ReceiveLetter(BYTE* ReceiveBuffer)					// ���� �ޱ�
{
	//g_pLetterList->ClearLetterList();
	
	LPFS_LETTER_ALERT Data = (LPFS_LETTER_ALERT)ReceiveBuffer;
	char szDate[16] = {0};
	strncpy(szDate, (char *)Data->Date, 10);
	szDate[10] = '\0';
	char szTime[16] = {0};
	strncpy(szTime, (char *)Data->Date + 11, 8);
	szTime[8] = '\0';
	
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	char szSubject[32 + 1] = {0};
	strncpy(szSubject, (const char *)Data->Subject, 32);
	szSubject[32] = '\0';
	
	switch (Data->Read)
	{
	case 0x02:	// �������� �� ���� ����
		PlayBuffer(SOUND_FRIEND_MAIL_ALERT);
		g_pFriendMenu->SetNewMailAlert(TRUE);
		g_pChatListBox->AddText("", GlobalText[1062], SEASON3B::TYPE_SYSTEM_MESSAGE);		// "�� ������ �����߽��ϴ�."
		g_pLetterList->AddLetter(Data->Index, szName, szSubject, szDate, szTime, 0x00);
		g_pLetterList->Sort();
		break;
	case 0x00:	// ���� ���� ����
	case 0x01:	// ���� ����
		g_pLetterList->AddLetter(Data->Index, szName, szSubject, szDate, szTime, Data->Read);
		g_pLetterList->Sort(2);
		break;
	default:
		break;
	};
	
	g_pWindowMgr->RefreshMainWndLetterList();
	
	if (g_pLetterList->GetLetterCount() >= g_iMaxLetterCount)
	{
		g_pChatListBox->AddText("", GlobalText[1073], SEASON3B::TYPE_SYSTEM_MESSAGE);		// "�����Կ� ������ �� á���ϴ�. �������ּ���."		
	}
}

extern int g_iLetterReadNextPos_x, g_iLetterReadNextPos_y;

void ReceiveLetterText(BYTE* ReceiveBuffer)				// ���� ���� �ޱ�
{
	LPFS_LETTER_TEXT Data = (LPFS_LETTER_TEXT)ReceiveBuffer;
	Data->Memo[Data->MemoSize] = '\0';
	
	g_pLetterList->CacheLetterText(Data->Index, Data);
	
	LETTERLIST_TEXT * pLetter = g_pLetterList->GetLetter(Data->Index);
	if (pLetter == NULL) return;
	pLetter->m_bIsRead = TRUE;
	g_pWindowMgr->RefreshMainWndLetterList();
	
	char tempTxt[MAX_TEXT_LENGTH + 1];
	sprintf(tempTxt, GlobalText[1054], pLetter->m_szText);	// "�����б�: %s"
	DWORD dwUIID = 0;
	if (g_iLetterReadNextPos_x == UIWND_DEFAULT)
	{
		dwUIID = g_pWindowMgr->AddWindow(UIWNDTYPE_READLETTER, 100, 100, tempTxt);
	}
	else
	{
		dwUIID = g_pWindowMgr->AddWindow(UIWNDTYPE_READLETTER, g_iLetterReadNextPos_x, g_iLetterReadNextPos_y, tempTxt, 0, UIADDWND_FORCEPOSITION);
		g_iLetterReadNextPos_x = UIWND_DEFAULT;
	}
	
	CUILetterReadWindow * pWindow = (CUILetterReadWindow *)g_pWindowMgr->GetWindow(dwUIID);
	char szText[1000 + 1] = {0};
	strncpy(szText, (const char *)Data->Memo, 1000);
	szText[1000] = '\0';
	pWindow->SetLetter(pLetter, szText);
	g_pWindowMgr->SetLetterReadWindow(pLetter->m_dwLetterID, dwUIID);
	
	if (strnicmp(pLetter->m_szID, "webzen", MAX_ID_SIZE) == 0)
	{
		pWindow->m_Photo.SetWebzenMail(TRUE);
	}
	else
	{
		pWindow->m_Photo.SetClass(ChangeServerClassTypeToClientClassType(Data->Class));
		pWindow->m_Photo.SetEquipmentPacket(Data->Equipment);
		pWindow->m_Photo.SetAnimation(Data->PhotoAction + AT_ATTACK1);
		int iAngle = Data->PhotoDir & 0x3F;
		int iZoom = (Data->PhotoDir & 0xC0) >> 6;
		pWindow->m_Photo.SetAngle(iAngle * 6);
		pWindow->m_Photo.SetZoom((iZoom * 10 + 80) / 100.0f);
	}
	pWindow->SendUIMessageDirect(UI_MESSAGE_LISTSCRLTOP, 0, 0);
}

void ReceiveLetterDeleteResult(BYTE* ReceiveBuffer)		// ���� ���� ��� �ޱ�
{
	LPFS_LETTER_RESULT Data = (LPFS_LETTER_RESULT)ReceiveBuffer;
	switch(Data->Result)
	{
	case 0x00:	// ���� ����
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1055]);	// "������ �������� ���߽��ϴ�."
		break;
	case 0x01:	// ���� ����
		g_pLetterList->RemoveLetter(Data->Index);
		g_pLetterList->RemoveLetterTextCache(Data->Index);
		break;
	default:
		break;
	};
	
	g_pWindowMgr->RefreshMainWndLetterList();
}

void ReceiveCreateChatRoomResult(BYTE* ReceiveBuffer)		// ��ȭ�� ���� ��û ���
{
	LPFS_CHAT_CREATE_RESULT Data = (LPFS_CHAT_CREATE_RESULT)ReceiveBuffer;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->ID, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	char szIP[16];
	memset(szIP, 0, 16);
	memcpy(szIP, Data->IP, 15);
	switch(Data->Result)
	{
	case 0x00:	// ģ���� ���̻� ��ȭ�� �� �� �����ϴ�.
		g_pFriendMenu->RemoveRequestWindow(szName);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1069]);	// "�� �̻� ��ȭ�� �� �� �����ϴ�."
		break;
	case 0x01:	// ��ȭ�� ���� ����
		if (Data->Type == 0)	// �� ���� ���
		{
			g_pFriendMenu->RemoveRequestWindow(szName);
			DWORD dwUIID = g_pWindowMgr->AddWindow(UIWNDTYPE_CHAT, 100, 100, GlobalText[994]);	// "��ȭ��: "
			((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->ConnectToChatServer((char *)szIP, Data->RoomNumber, Data->Ticket);
		}
		else if (Data->Type == 1)	// �濡 ���� ��� (1:1 ��ȭ ����)
		{
			// �ߺ� ä�� üũ
			DWORD dwUIID = g_pFriendMenu->CheckChatRoomDuplication(szName);
			if (dwUIID == 0)
			{
				dwUIID = g_pWindowMgr->AddWindow(UIWNDTYPE_CHAT_READY, 100, 100, GlobalText[994]);	// "��ȭ��: "
				((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->ConnectToChatServer((char *)szIP, Data->RoomNumber, Data->Ticket);
				g_pWindowMgr->GetWindow(dwUIID)->SetState(UISTATE_READY);
				g_pWindowMgr->SendUIMessage(UI_MESSAGE_BOTTOM, dwUIID, 0);
				if (g_pWindowMgr->GetFriendMainWindow() != NULL)
					g_pWindowMgr->GetFriendMainWindow()->RemoveWindow(dwUIID);
			}
			else if (dwUIID == -1);
			else
			{
				((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->DisconnectToChatServer();
				((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->ConnectToChatServer((char *)szIP, Data->RoomNumber, Data->Ticket);
				
				//				SendRequestCRDisconnectRoom(((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->GetCurrentSocket());
				//				DWORD dwOldRoomNumber = ((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->GetRoomNumber();
				//				((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->ConnectToChatServer((char *)szIP, Data->RoomNumber, Data->Ticket);
				//				g_pChatRoomSocketList->RemoveChatRoomSocket(dwOldRoomNumber);
			}
		}
		else if (Data->Type == 2)	// �濡 ���� ��� (�ʴ� ����)
		{
			DWORD dwUIID = g_pWindowMgr->AddWindow(UIWNDTYPE_CHAT_READY, 100, 100, GlobalText[994]);	// "��ȭ��: "
			((CUIChatWindow *)g_pWindowMgr->GetWindow(dwUIID))->ConnectToChatServer((char *)szIP, Data->RoomNumber, Data->Ticket);
			g_pWindowMgr->GetWindow(dwUIID)->SetState(UISTATE_READY);
			g_pWindowMgr->SendUIMessage(UI_MESSAGE_BOTTOM, dwUIID, 0);
			if (g_pWindowMgr->GetFriendMainWindow() != NULL)
				g_pWindowMgr->GetFriendMainWindow()->RemoveWindow(dwUIID);
		}
		break;
	case 0x02:	// ģ���� ��ȭ�� �� �� �ִ� ������ ����Ǿ����ϴ�.
		g_pFriendMenu->RemoveRequestWindow(szName);
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1070]);	// "��ȭ �� �� �ִ� ������ ����Ǿ����ϴ�."
		break;
	default:
		break;
	};
}

void ReceiveChatRoomInviteResult(BYTE* ReceiveBuffer)		// �ʴ� ��� �ޱ�
{
	LPFS_CHAT_INVITE_RESULT Data = (LPFS_CHAT_INVITE_RESULT)ReceiveBuffer;
	CUIChatWindow * pChatWindow = (CUIChatWindow *)g_pWindowMgr->GetWindow(Data->WindowGuid);
	if (pChatWindow == NULL) return;
	
	switch(Data->Result)
	{
	case 0x00:	// ��밡 �������� ����
		//g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, "�ʴ� ����� �������� �����Դϴ�.");
		pChatWindow->AddChatText(255, GlobalText[1056], 1, 0);	// "�������� �����Դϴ�."
		break;
	case 0x01:	// �ʴ� ����
		if (pChatWindow->GetCurrentInvitePal() != NULL)
		{
			char szText[MAX_TEXT_LENGTH + 1] = {0};
			strncpy(szText, pChatWindow->GetCurrentInvitePal()->m_szID, MAX_ID_SIZE);
			szText[MAX_ID_SIZE] = '\0';
			strcat(szText, GlobalText[1057]);	// "���� �ʴ��Ͽ����ϴ�."
			pChatWindow->AddChatText(255, szText, 1, 0);
		}
		else
		{
			assert(!"�ʴ� ID�� ����");
		}
		break;
	case 0x03:	// ������ �ʴ� �Ұ�
		pChatWindow->AddChatText(255, GlobalText[1074], 1, 0);	// "�ʴ� ���� �ο��� �ʰ��Ͽ����ϴ�."
		break;
	default:
		break;
	};
}

void ReceiveChatRoomConnectResult(DWORD dwWindowUIID, BYTE* ReceiveBuffer)		// �� ���� ��� �ޱ�
{
	LPFS_CHAT_JOIN_RESULT Data = (LPFS_CHAT_JOIN_RESULT)ReceiveBuffer;
	switch(Data->Result)
	{
	case 0x00:	// �ο� ����
		g_pWindowMgr->AddWindow(UIWNDTYPE_OK_FORCE, UIWND_DEFAULT, UIWND_DEFAULT, GlobalText[1058]);	// "��ȭ�濡 ����� �� ���� �� �� �����ϴ�."
		break;
	case 0x01:	// �� ���� ����
		//((CUIChatWindow *)g_pWindowMgr->GetWindow(dwWindowUIID))->AddChatText("", "��ȭ�濡 �����Ͽ����ϴ�.", 3, 0);
		break;
	default:
		break;
	};
}

void ReceiveChatRoomUserStateChange(DWORD dwWindowUIID, BYTE* ReceiveBuffer)	// �ٸ� ��� ���� ��ȭ
{
	LPFS_CHAT_CHANGE_STATE Data = (LPFS_CHAT_CHANGE_STATE)ReceiveBuffer;
	CUIChatWindow * pChatWindow = (CUIChatWindow *)g_pWindowMgr->GetWindow(dwWindowUIID);
	if (pChatWindow == NULL) return;
	char szName[MAX_ID_SIZE + 1] = {0};
	strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
	szName[MAX_ID_SIZE] = '\0';
	char szText[MAX_TEXT_LENGTH + 1] = {0};
	strncpy(szText, (const char *)Data->Name, MAX_ID_SIZE);
	szText[MAX_ID_SIZE] = '\0';
	switch(Data->Type)
	{
	case 0x00:	// �ٸ� ����ڰ� �����ߴ�
		if (pChatWindow->AddChatPal(szName, Data->Index, 0) >= 3)
		{
			strcat(szText, GlobalText[1059]);	// "���� �����ϼ̽��ϴ�."
			pChatWindow->AddChatText(255, szText, 1, 0);
		}
		break;
	case 0x01:	// �ٸ� ����ڰ� ���� ���� ������.
		if (pChatWindow->GetUserCount() >= 3)
		{
			strcat(szText, GlobalText[1060]);	// "���� �����ϼ̽��ϴ�."
			pChatWindow->AddChatText(255, szText, 1, 0);
		}
		pChatWindow->RemoveChatPal(szName);
		break;
	default:
		return;
		break;
	};
	if (pChatWindow->GetShowType() == 2)
		pChatWindow->UpdateInvitePalList();
}

void ReceiveChatRoomUserList(DWORD dwWindowUIID, BYTE* ReceiveBuffer)			// ��������Ʈ �ޱ�
{
	LPFS_CHAT_USERLIST_HEADER Header = (LPFS_CHAT_USERLIST_HEADER)ReceiveBuffer;
	int iMoveOffset = sizeof(FS_CHAT_USERLIST_HEADER);
	char szName[MAX_ID_SIZE + 1] = {0};
	for (int i = 0; i < Header->Count; ++i)
	{
		LPFS_CHAT_USERLIST_DATA Data = (LPFS_CHAT_USERLIST_DATA)(ReceiveBuffer+iMoveOffset);
		strncpy(szName, (const char *)Data->Name, MAX_ID_SIZE);
		szName[MAX_ID_SIZE] = '\0';
		((CUIChatWindow *)g_pWindowMgr->GetWindow(dwWindowUIID))->AddChatPal(szName, Data->Index, 0);
		iMoveOffset += sizeof(FS_CHAT_USERLIST_DATA);
	}
}

void ReceiveChatRoomChatText(DWORD dwWindowUIID, BYTE* ReceiveBuffer)			// ä�� ��ȭ �� �ޱ�
{
	LPFS_CHAT_TEXT Data = (LPFS_CHAT_TEXT)ReceiveBuffer;
	CUIChatWindow * pChatWindow = (CUIChatWindow *)g_pWindowMgr->GetWindow(dwWindowUIID);
	if (pChatWindow == NULL) return;
	
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	char ChatMsg[MAX_CHATROOM_TEXT_LENGTH] = {'\0'};
	if (Data->MsgSize >= MAX_CHATROOM_TEXT_LENGTH) return;
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	char ChatMsg[101] = {0};
	if (Data->MsgSize > 100) return;
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	memcpy(ChatMsg, Data->Msg, Data->MsgSize);
	BuxConvert((LPBYTE)ChatMsg, Data->MsgSize);
	
	if (pChatWindow->GetState() == UISTATE_READY)
	{
		g_pFriendMenu->SetNewChatAlert(dwWindowUIID);
		g_pChatListBox->AddText("", GlobalText[1063], SEASON3B::TYPE_SYSTEM_MESSAGE);	// "�޽����� �Խ��ϴ�."
		pChatWindow->SetState(UISTATE_HIDE);
		if (g_pWindowMgr->GetFriendMainWindow() != NULL)
		{
			g_pWindowMgr->GetFriendMainWindow()->AddWindow(dwWindowUIID, g_pWindowMgr->GetWindow(dwWindowUIID)->GetTitle());
		}
	}
	else if (pChatWindow->GetState() == UISTATE_HIDE || g_pWindowMgr->GetTopWindowUIID() != dwWindowUIID)
	{
		g_pFriendMenu->SetNewChatAlert(dwWindowUIID);
	}
	pChatWindow->AddChatText(Data->Index, (char *)ChatMsg, 3, 0);
}

void ReceiveChatRoomNoticeText(DWORD dwWindowUIID, BYTE* ReceiveBuffer)			// �������� �� �ޱ�
{
	LPFS_CHAT_TEXT Data = (LPFS_CHAT_TEXT)ReceiveBuffer;
	Data->Msg[99] = '\0';
	if (Data->Msg[0] == '\0')
	{
		return;
	}
	
	g_pChatListBox->AddText("", (char *)Data->Msg, SEASON3B::TYPE_SYSTEM_MESSAGE);
}

///////////////////////////////////////////////////////////////////////////////
// �ɼ�.
///////////////////////////////////////////////////////////////////////////////
void ReceiveOption(BYTE* ReceiveBuffer)
{
    LPPRECEIVE_OPTION Data = (LPPRECEIVE_OPTION)ReceiveBuffer;
	
#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		g_pMainFrame->ResetSkillHotKey();
	}
	else
	{
		GFxProcess::GetInstancePtr()->SetSkillClearHotKey();
	}
#else //LDK_ADD_SCALEFORM
	g_pMainFrame->ResetSkillHotKey();
#endif //LDK_ADD_SCALEFORM

#ifdef _VS2008PORTING
	int iHotKey;
	for(int i=0; i<10; ++i)
#else // _VS2008PORTING
	int iHotKey, i, j;
	for(i=0; i<10; ++i)
#endif // _VS2008PORTING
	{
#ifdef CSK_FIX_SKILLHOTKEY_PACKET
		int iIndex = i * 2;
		iHotKey = MAKEWORD(Data->HotKey[iIndex+1], Data->HotKey[iIndex]);
#else // CSK_FIX_SKILLHOTKEY_PACKET
		iHotKey = Data->HotKey[i];
#endif // CSK_FIX_SKILLHOTKEY_PACKET
				
#ifdef CSK_FIX_SKILLHOTKEY_PACKET
		if(iHotKey != 0xffff)
#else // CSK_FIX_SKILLHOTKEY_PACKET
		if(iHotKey != 0xff)
#endif // CSK_FIX_SKILLHOTKEY_PACKET
		{
#ifdef _VS2008PORTING
			for(int j=0; j<MAX_SKILLS; ++j)
#else // _VS2008PORTING
			for(j=0; j<MAX_SKILLS; ++j)
#endif // _VS2008PORTING
			{
				if(iHotKey == CharacterAttribute->Skill[j])
				{
#ifdef LDK_ADD_SCALEFORM
					//gfxui ���� ���� ui ��� ����
					if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
					{
						g_pMainFrame->SetSkillHotKey(i, j);
					}
					else
					{
						GFxProcess::GetInstancePtr()->SetSkillHotKey(i == 0 ? 10 : i, j);
					}
#else //LDK_ADD_SCALEFORM
					g_pMainFrame->SetSkillHotKey(i, j);
#endif //LDK_ADD_SCALEFORM
					break;
				}
			}	
		}
	}
	
    //  �ڵ����� ������.
    if ( (Data->GameOption&AUTOATTACK_ON)==AUTOATTACK_ON )
    {
		g_pOption->SetAutoAttack(true);
    }
    else
    {
		g_pOption->SetAutoAttack(false);
    }
	
    if ( (Data->GameOption&WHISPER_SOUND_ON)==WHISPER_SOUND_ON )
    {
		g_pOption->SetWhisperSound(true);
    }
    else
    {
		g_pOption->SetWhisperSound(false);
    }
	
    //  ������ �ɼ�.
    if ( (Data->GameOption&SLIDE_HELP_OFF)==SLIDE_HELP_OFF )
    {
		g_pOption->SetSlideHelp(false);
    }
    else
    {
		g_pOption->SetSlideHelp(true);
    }
	
	BYTE byQLevel, byWLevel, byELevel, byRLevel;
	byQLevel = (Data->QWERLevel & 0xFF000000) >> 24;
	byWLevel = (Data->QWERLevel & 0x00FF0000) >> 16;
	byELevel = (Data->QWERLevel & 0x0000FF00) >> 8;
	byRLevel = Data->QWERLevel & 0x000000FF;


#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
		if( Data->KeyQWE[0] != 0xFF ) {
			g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_Q, Data->KeyQWE[0]+ITEM_POTION, byQLevel);
		}

		if( Data->KeyQWE[1] != 0xFF ) {
			g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_W, Data->KeyQWE[1]+ITEM_POTION, byWLevel);
		}

		if( Data->KeyQWE[2] != 0xFF ) {
			g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_E, Data->KeyQWE[2]+ITEM_POTION, byELevel);
		}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_Q, Data->KeyQWE[0]+ITEM_POTION, byQLevel);
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_W, Data->KeyQWE[1]+ITEM_POTION, byWLevel);
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_E, Data->KeyQWE[2]+ITEM_POTION, byELevel);
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING
	}
	else
	{
		if( Data->KeyQWE[0] != 0xFF )	GFxProcess::GetInstancePtr()->SetItemHotKey(SEASON3B::HOTKEY_Q, Data->KeyQWE[0]+ITEM_POTION, byQLevel);
		if( Data->KeyQWE[1] != 0xFF )	GFxProcess::GetInstancePtr()->SetItemHotKey(SEASON3B::HOTKEY_W, Data->KeyQWE[1]+ITEM_POTION, byWLevel);
		if( Data->KeyQWE[2] != 0xFF )	GFxProcess::GetInstancePtr()->SetItemHotKey(SEASON3B::HOTKEY_E, Data->KeyQWE[2]+ITEM_POTION, byELevel);
	}
#else //LDK_ADD_SCALEFORM
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
	if( Data->KeyQWE[0] != 0xFF ) {
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_Q, Data->KeyQWE[0]+ITEM_POTION, byQLevel);
	}

	if( Data->KeyQWE[1] != 0xFF ) {
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_W, Data->KeyQWE[1]+ITEM_POTION, byWLevel);
	}

	if( Data->KeyQWE[2] != 0xFF ) {
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_E, Data->KeyQWE[2]+ITEM_POTION, byELevel);
	}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
	g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_Q, Data->KeyQWE[0]+ITEM_POTION, byQLevel);
	g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_W, Data->KeyQWE[1]+ITEM_POTION, byWLevel);
	g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_E, Data->KeyQWE[2]+ITEM_POTION, byELevel);
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING
#endif //LDK_ADD_SCALEFORM
	
	//  ä��â ����
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	BYTE wChatListBoxSize = (Data->ChatLogBox >> 4) * 3;
	BYTE wChatListBoxBackAlpha = Data->ChatLogBox & 0x0F;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
		if( Data->KeyR != 0xFF ) {
			g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_R, Data->KeyR+ITEM_POTION, byRLevel);
		}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_R, Data->KeyR+ITEM_POTION, byRLevel);
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING
	}
	else
	{
		if( Data->KeyR != 0xFF ) GFxProcess::GetInstancePtr()->SetItemHotKey(SEASON3B::HOTKEY_R, Data->KeyR+ITEM_POTION, byRLevel);
	}
#else //LDK_ADD_SCALEFORM
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
	if( Data->KeyR != 0xFF ) {
		g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_R, Data->KeyR+ITEM_POTION, byRLevel);
	}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
	g_pMainFrame->SetItemHotKey(SEASON3B::HOTKEY_R, Data->KeyR+ITEM_POTION, byRLevel);
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING
#endif //LDK_ADD_SCALEFORM
}


///////////////////////////////////////////////////////////////////////////////
// �̺�ƮĨ ���� ��������( ����Ĩ )
///////////////////////////////////////////////////////////////////////////////
void ReceiveEventChipInfomation( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_EVENT_CHIP_INFO Data = (LPPRECEIVE_EVENT_CHIP_INFO)ReceiveBuffer;
	
	g_pNewUISystem->HideAll();

	g_bEventChipDialogEnable = Data->m_byType+1;
#ifdef ASG_FIX_LENA_REGISTRATION
	g_shEventChipCount       = Data->m_nChipCount;
#else	// ASG_FIX_LENA_REGISTRATION
	g_shEventChipCount       = Data->m_shChipCount;
#endif	// ASG_FIX_LENA_REGISTRATION
	
#ifdef PSW_GOLDBOWMAN		
	if( g_bEventChipDialogEnable == EVENT_SCRATCH_TICKET )
	{
		g_pNewUISystem->Show(SEASON3B::INTERFACE_GOLD_BOWMAN);
		g_bEventChipDialogEnable = 0;
	}	
#endif //PSW_GOLDBOWMAN
	
#ifdef PSW_EVENT_LENA		
	if( g_bEventChipDialogEnable == EVENT_LENA )
	{
		g_pNewUISystem->Show(SEASON3B::INTERFACE_GOLD_BOWMAN_LENA);
		g_bEventChipDialogEnable = 0;

		if( Data->m_shMutoNum[0]!=-1 && Data->m_shMutoNum[1]!=-1 && Data->m_shMutoNum[2]!=-1 ) {
			memcpy( g_shMutoNumber, Data->m_shMutoNum, sizeof( short )*3 );
		}
	}	
#endif //PSW_EVENT_LENA

	///////////////////////////////���� �ʼ�///////////////////////////////////
	
#ifdef FRIEND_EVENT
    g_bEventChipDialogEnable = EVENT_FRIEND;
#endif// EVENT_FRIEND   �ӽ� �ڵ�.
	
#ifdef BLOODCASTLE_2ND_PATCH
	if ( g_bEventChipDialogEnable==EVENT_SCRATCH_TICKET )
#endif
		
#ifdef SCRATCH_TICKET
		if ( g_bEventChipDialogEnable==EVENT_SCRATCH_TICKET )
		{
			ZeroMemory ( g_strGiftName, sizeof( char )*64 );
			
			ClearInput(FALSE);
			InputTextMax[0] = 12;
			InputNumber = 1;
			InputEnable		= false;
			GoldInputEnable = false;
			InputGold		= 0;
			StorageGoldFlag = 0;
			g_bScratchTicket= true;
		}
#endif

		///////////////////////////////���� �ʼ�////////////////////////////////////
}

void ReceiveEventChip( BYTE* ReceiveBuffer)
{
    LPPRECEIVE_EVENT_CHIP Data = (LPPRECEIVE_EVENT_CHIP)ReceiveBuffer;
#ifdef ASG_FIX_LENA_REGISTRATION
	if( Data->m_unChipCount != 0xFFFFFFFF )
        g_shEventChipCount = Data->m_unChipCount;
#else	// ASG_FIX_LENA_REGISTRATION
    if( Data->m_shChipCount != 0xFFFF )
        g_shEventChipCount = Data->m_shChipCount;
#endif	// ASG_FIX_LENA_REGISTRATION
}

void ReceiveBuffState( BYTE* ReceiveBuffer )
{
	LPPMSG_ITEMEFFECTCANCEL Data = (LPPMSG_ITEMEFFECTCANCEL)ReceiveBuffer;
	
	eBuffState bufftype = static_cast<eBuffState>(Data->byBuffType);

	if( bufftype == eBuffNone || bufftype >= eBuff_Count ) return;
	
	// ��ū ���������� �������� ���� �޼����� �ޱ� ������ 
	// ���� �߰� �޼������� ����� ��ū ������ ���� ���� �ʴ´�.
	
	if(Data->byEffectOption == 0) // ���� ����
	{
		RegisterBuff( bufftype, (&Hero->Object), Data->wEffectTime );
		
		if( bufftype == eBuff_HelpNpc )
		{
			g_pChatListBox->AddText("", GlobalText[1828], SEASON3B::TYPE_SYSTEM_MESSAGE);
		}
	}
	else // ���� ����
	{
		UnRegisterBuff( bufftype, (&Hero->Object) );
	}
}

void ReceiveMutoNumber( BYTE* ReceiveBuffer)
{
    LPPRECEIVE_MUTONUMBER Data = (LPPRECEIVE_MUTONUMBER)ReceiveBuffer;
	
    if( Data->m_shMutoNum[0]!=-1 && Data->m_shMutoNum[1]!=-1 && Data->m_shMutoNum[2]!=-1 )
    {
        memcpy ( g_shMutoNumber, Data->m_shMutoNum, sizeof( short )*3 );
    }
}


void ReceiveServerImmigration( BYTE *ReceiveBuffer)
{
	LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
	
	switch ( Data->Value)
	{
	case 0:	// �ֹι�ȣ �߸���
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CServerImmigrationErrorMsgBoxLayout));
		break;
	case 1:	// ���� ���� ����
		SEASON3B::CreateOkMessageBox("���� ������ ���� �߻� : ���� �ٶ�");
		break;
	}
}


#ifdef SCRATCH_TICKET
void ReceiveScratchResult ( BYTE* ReceiveBuffer )
{
	LPPRECEIVE_SCRATCH_TICKET_EVENT Data = (LPPRECEIVE_SCRATCH_TICKET_EVENT)ReceiveBuffer;
	
	switch ( Data->m_byIsRegistered)
	{
	case 0: //	���� ���.
	case 1: //	�̹� ��ϵ� �ø����ȣ.
	case 2: //	��� Ƚ�� �ʰ�.
	case 3: //	�߸��� �ø��� ��ȣ.	
	case 4:	//	�˼� ���� ����. 
		SEASON3B::CreateOkMessageBox(GlobalText[886+Data->m_byIsRegistered]);
		break;
		
	case 5:	//	�̹� ����� �߽��ϴ�.
		SEASON3B::CreateOkMessageBox(GlobalText[899]);
		break;
	}
	
	memcpy ( g_strGiftName, Data->m_strGiftName, sizeof( char )*64 );
}
#endif

void ReceivePlaySoundEffect(BYTE* ReceiveBuffer)	// ȿ���� ���
{
	LPPRECEIVE_PLAY_SOUND_EFFECT Data = (LPPRECEIVE_PLAY_SOUND_EFFECT)ReceiveBuffer;
	
	switch(Data->wEffectNum)
	{
	case 0:
		PlayBuffer(SOUND_RING_EVENT_READY);
		break;
	case 1:
		PlayBuffer(SOUND_RING_EVENT_START);
		break;
	case 2:
		PlayBuffer(SOUND_RING_EVENT_END);
		break;
	default:
		break;
	}
}

void ReceiveEventCount ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_EVENT_COUNT Data = (LPPRECEIVE_EVENT_COUNT)ReceiveBuffer;
	
    g_csQuest.SetEventCount ( Data->m_wEventType, Data->m_wLeftEnterCount );
}


//////////////////////////////////////////////////////////////////////////
//  ����Ʈ ����.
//////////////////////////////////////////////////////////////////////////
//  ����Ʈ ����Ʈ�� �޴´�.
void ReceiveQuestHistory ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_QUEST_HISTORY Data = (LPPRECEIVE_QUEST_HISTORY)ReceiveBuffer;
	
    //  ����Ʈ ����Ʈ�� �����Ѵ� 
    g_csQuest.setQuestLists ( Data->m_byQuest, Data->m_byCount, Hero->Class );
}

//  Ư�� ����Ʈ ���� ���� ����.
void ReceiveQuestState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_QUEST_STATE Data = (LPPRECEIVE_QUEST_STATE)ReceiveBuffer;
	
    //  ����Ʈ ���� ����.
    g_csQuest.setQuestList ( Data->m_byQuestIndex, Data->m_byState );
	g_pNewUISystem->HideAll();
	g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCQUEST);
}

//  Ư�� ����Ʈ�� ����� �޴´�.
void ReceiveQuestResult ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_QUEST_RESULT Data = (LPPRECEIVE_QUEST_RESULT)ReceiveBuffer;
	
    if ( Data->m_byResult==0 )
    {
        g_csQuest.setQuestList ( Data->m_byQuestIndex, Data->m_byState );
		g_pNewUISystem->HideAll();
		g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCQUEST);
    }
}

//  ����Ʈ�� ���� ������ �޴´�.
void ReceiveQuestPrize ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_QUEST_REPARATION Data = (LPPRECEIVE_QUEST_REPARATION)ReceiveBuffer;
	
	WORD Key = ((WORD)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
	Key &= 0x7FFF;
    int Index = FindCharacterIndex ( Key );

    switch ( Data->m_byReparation )
    {
    case 200 :  //  ��������Ʈ.
        {
			CHARACTER *c = &CharactersClient[Index];
			
            //  �ڱ� �ڽŸ�..
            if ( c==Hero )
            {
                CharacterAttribute->LevelUpPoint += Data->m_byNumber;
            }
			
			OBJECT *o = &c->Object;
			
            vec3_t      Position;
            VectorCopy ( o->Position, Position );
            for ( int i=0; i<15; ++i )
            {
                CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
            }
            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
			PlayBuffer( SOUND_CHANGE_UP );
        }
        break;
		
    case 201 :  //  2�� Ŭ������ ����.
        {
			CHARACTER*  c = &CharactersClient[Index];
			OBJECT*     o = &c->Object;
            vec3_t      Position;
			
			BYTE byClass = ChangeServerClassTypeToClientClassType(Data->m_byNumber);
			if (2 != GetStepClass(byClass))	// 2�� Ŭ���� ������ �ƴϸ� ó������ ����.
				break;
			
			c->Class = byClass;
			
            if ( Hero==c )
            {
                CharacterAttribute->Class = c->Class;
            }
			
			VectorCopy ( o->Position, Position );
			Position[2] += 200.f;
			for ( int i=0; i<15; ++i )
			{
				CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
				CreateJoint(BITMAP_FLARE,Position,Position,o->Angle,10,o,40,2);
			}
			CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
			
			SetChangeClass( c );
			SetAction ( o, PLAYER_SALUTE1 );
			
			PlayBuffer ( SOUND_CHANGE_UP );
        }
        break;
		
	case 202 :	//	����  ����Ʈ ��� 5 --> 6.	���� �߰�.
		{
			CHARACTER*  c = &CharactersClient[Index];
			OBJECT*     o = &c->Object;
            vec3_t      Position;
			
            if ( Hero==c )
            {
                CharacterAttribute->LevelUpPoint += Data->m_byNumber;
            }
			
            VectorCopy ( o->Position, Position );
            Position[2] += 200.f;
            for ( int i=0; i<15; ++i )
            {
                CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
                CreateJoint(BITMAP_FLARE,Position,Position,o->Angle,10,o,40,2);
            }
            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
			
            SetChangeClass( c );
            SetAction ( o, PLAYER_SALUTE1 );
			PlayBuffer ( SOUND_CHANGE_UP );
		}
		break;
		
	case 203 :	//	�޺� ��ų.
		{
			CHARACTER*  c = &CharactersClient[Index];
			OBJECT*     o = &c->Object;
            vec3_t      Position;
			
            VectorCopy ( o->Position, Position );
            Position[2] += 200.f;
            for ( int i=0; i<15; ++i )
            {
                CreateJoint(BITMAP_FLARE,o->Position,o->Position,o->Angle,0,o,40,2);
                CreateJoint(BITMAP_FLARE,Position,Position,o->Angle,10,o,40,2);
            }
            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,0,o);
			
            SetChangeClass( c );
            SetAction ( o, PLAYER_SALUTE1 );
			
            PlayBuffer ( SOUND_CHANGE_UP );
		}
		break;
		
	case 204:	// 3�� Ŭ������ ����.
		{
			CHARACTER* c = &CharactersClient[Index];
			
			BYTE byClass = ChangeServerClassTypeToClientClassType(Data->m_byNumber);
			if (3 != GetStepClass(byClass))	// 3�� Ŭ������ �ƴϸ� ó������ ����.
				break;
			
			c->Class = byClass;
			
            if (Hero == c)
            {
                CharacterAttribute->Class = c->Class;
            }
			
			//3������ ȿ�� ���
			CreateEffect(MODEL_CHANGE_UP_EFF,c->Object.Position,c->Object.Angle,c->Object.Light,0,&c->Object);
			CreateEffect(MODEL_CHANGE_UP_NASA,c->Object.Position,c->Object.Angle,c->Object.Light,0,&c->Object);
			CreateEffect(MODEL_CHANGE_UP_CYLINDER,c->Object.Position,c->Object.Angle,c->Object.Light,0,&c->Object);
			CreateEffect(MODEL_INFINITY_ARROW3, c->Object.Position, c->Object.Angle, c->Object.Light, 1, &c->Object);
			
			SetChangeClass( c );
			SetAction(&c->Object,PLAYER_CHANGE_UP);
			PlayBuffer(SOUND_CHANGE_UP);
        }
        break;
		
    default :   //  ��Ÿ.
        break;
    }
}

void ReceiveQuestMonKillInfo(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_QUEST_MONKILL_INFO pData = (LPPMSG_ANS_QUEST_MONKILL_INFO)ReceiveBuffer;
	
	/*BYTE	byResult;		// ��� 0x00:����(����)
	//		0x01:���� 
	//		0x02:�̹� �Ϸ��� ����Ʈ
	//		0x03:�������� ����Ʈ �ƴ�
	//		0x04:����Ʈ�� ����(����Ʈ ��ȣ�� �߸�����)
	//		0x05:�Ϸ������� ųī��Ʈ�� �ƴ�(Ŭ���̾�Ʈ���� ��û�ϸ� �ȵ�)
	
	  BYTE	byQuestIndex;		// ����Ʈ �ε���
	  int		anKillCountInfo[10];// ���� ųī��Ʈ ����
	*/
	//	if (0x01 == pData->byResult || 0x02 == pData->byResult)
	//	{
	g_csQuest.SetKillMobInfo(pData->anKillCountInfo);
	//	}
}

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
#ifdef ASG_ADD_TIME_LIMIT_QUEST
// ������ ���� ����Ʈ ���� �� ����.(0xF6 0x00)
void ReceiveQuestLimitResult(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_QUESTEXP_RESULT pData = (LPPMSG_ANS_QUESTEXP_RESULT)ReceiveBuffer;

	g_pNewUISystem->HideAll();

	switch (pData->m_byResult)
	{
	case QUEST_RESULT_CNT_LIMIT:	// ����Ʈ ���� ����.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CQuestCountLimitMsgBoxLayout));
		break;
	}
}

// ����Ʈ ������ ��뿡 ���� EP(���Ǽҵ�)�� ����.(0xF6 0x04)
void ReceiveQuestByItemUseEP(BYTE* ReceiveBuffer)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_NPCTALK_QUESTLIST pData = (LPPMSG_NPCTALK_QUESTLIST)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	DWORD* pdwQuestIndex = (DWORD*)(ReceiveBuffer + sizeof(PMSG_NPCTALK_QUESTLIST));
	SendQuestSelection(*pdwQuestIndex, 0);
}
#endif	// ASG_ADD_TIME_LIMIT_QUEST

// ��Ÿ ��Ȳ�� ����Ʈ EP(���Ǽҵ�)����Ʈ�� ����.(0xF6 0x03)
void ReceiveQuestByEtcEPList(BYTE* ReceiveBuffer)
{
	LPPMSG_NPCTALK_QUESTLIST pData = (LPPMSG_NPCTALK_QUESTLIST)ReceiveBuffer;
	g_QuestMng.SetQuestIndexByEtcList((DWORD*)(ReceiveBuffer + sizeof(PMSG_NPCTALK_QUESTLIST)),
		pData->m_wQuestCount);
}

// NPC�� ���� EP(���Ǽҵ�)����Ʈ�� ����.(0xF6 0x0A)
void ReceiveQuestByNPCEPList(BYTE* ReceiveBuffer)
{
	LPPMSG_NPCTALK_QUESTLIST pData = (LPPMSG_NPCTALK_QUESTLIST)ReceiveBuffer;
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
		g_pNPCDialogue->ProcessQuestListReceive(
			(DWORD*)(ReceiveBuffer + sizeof(PMSG_NPCTALK_QUESTLIST)), pData->m_wQuestCount);
#else	// ASG_ADD_UI_NPC_DIALOGUE
	g_QuestMng.SetNPC(int(pData->m_wNPCIndex)); // NPC �̸� ����.
#ifdef ASG_ADD_UI_NPC_MENU
	g_pNPCMenu->SetContents((DWORD*)(ReceiveBuffer + sizeof(PMSG_NPCTALK_QUESTLIST)),
		pData->m_wQuestCount);
#endif	// ASG_ADD_UI_NPC_MENU
#endif	// ASG_ADD_UI_NPC_DIALOGUE
}

// ���ù��� �ִ� QS(����Ʈ ����)�� ����.(0xF6 0x0B)
void ReceiveQuestQSSelSentence(BYTE* ReceiveBuffer)
{
	LPPMSG_NPC_QUESTEXP_INFO pData = (LPPMSG_NPC_QUESTEXP_INFO)ReceiveBuffer;

	g_QuestMng.SetCurQuestProgress(pData->m_dwQuestIndex);
}

// �䱸, ������ �ִ� QS(����Ʈ ����)�� ����.(0xF6 0x0C)
void ReceiveQuestQSRequestReward(BYTE* ReceiveBuffer)
{
	LPPMSG_NPC_QUESTEXP_INFO pData = (LPPMSG_NPC_QUESTEXP_INFO)ReceiveBuffer;
	g_QuestMng.SetQuestRequestReward(ReceiveBuffer);
	g_QuestMng.SetCurQuestProgress(pData->m_dwQuestIndex);
	// �䱸, ������ �ִ� QS(����Ʈ ����)�̹Ƿ� true.
	g_QuestMng.SetEPRequestRewardState(pData->m_dwQuestIndex, true);
}

// ����Ʈ ����â���� Ȯ�� ��ư�� ������ ��� �������� ���� ����.(0xF6 0x0D)
// ���Ǽҵ尡 ������ ���(QS�� 0xff)�� �������� (0xF6 0x0B)�� ����.
void ReceiveQuestCompleteResult(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_QUESTEXP_COMPLETE pData = (LPPMSG_ANS_QUESTEXP_COMPLETE)ReceiveBuffer;

	switch (pData->m_byResult)
	{
	case 0:
		break;
	case 1:
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_QUEST_PROGRESS);
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC);
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC

		// ����Ʈ ������ �ϴܶ� �Ǿ����Ƿ� EPProgress�� false�� �ʱ�ȭ.
		g_QuestMng.SetEPRequestRewardState(pData->m_dwQuestIndex, false);
		// �������� ����Ʈ ����Ʈ���� ���� ���Ǽҵ��� ����Ʈ �ε��� ����.
		g_QuestMng.RemoveCurQuestIndexList(pData->m_dwQuestIndex);
		break;

	case 2:
#ifdef ASG_MOD_QUEST_OK_BTN_DISABLE
		// ����Ʈ ����â�� Ȯ�� ��ư�� ��Ȱ��ȭ.
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
			g_pQuestProgress->EnableCompleteBtn(false);
		else if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
			g_pQuestProgressByEtc->EnableCompleteBtn(false);
#endif	// ASG_MOD_QUEST_OK_BTN_DISABLE
		// 2816	"�����ݾ��� �� á���ϴ�"
		g_pChatListBox->AddText("", GlobalText[2816], SEASON3B::TYPE_ERROR_MESSAGE);
		break;

	case 3:
#ifdef ASG_MOD_QUEST_OK_BTN_DISABLE
		// ����Ʈ ����â�� Ȯ�� ��ư�� ��Ȱ��ȭ.
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
			g_pQuestProgress->EnableCompleteBtn(false);
		else if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
			g_pQuestProgressByEtc->EnableCompleteBtn(false);
#endif	// ASG_MOD_QUEST_OK_BTN_DISABLE
		// 375 "�κ��丮�� ��á���ϴ�."
		g_pChatListBox->AddText("", GlobalText[375], SEASON3B::TYPE_ERROR_MESSAGE);
		// 374 "Ȯ���� �ֽʽÿ�!"
		g_pChatListBox->AddText("", GlobalText[374], SEASON3B::TYPE_ERROR_MESSAGE);
		break;
	}
}

// ����Ʈ ���������� ���� ����.(0xF6 0x0F)
void ReceiveQuestGiveUp(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_QUESTEXP_GIVEUP pData = (LPPMSG_ANS_QUESTEXP_GIVEUP)ReceiveBuffer;
#ifdef ASG_FIX_QUEST_GIVE_UP
	// �������� ����Ʈ ����Ʈ���� �ش� ����Ʈ ����.
	g_QuestMng.RemoveCurQuestIndexList(pData->m_dwQuestGiveUpIndex);
#else	// ASG_FIX_QUEST_GIVE_UP
	// ������ ����Ʈ�� �ε���(QS�� 0xfe)�� �߰��Ͽ� �������� ����Ʈ ����Ʈ���� �ش� ����Ʈ ����.
	g_QuestMng.AddCurQuestIndexList(pData->m_dwQuestGiveUpIndex);
#endif	// ASG_FIX_QUEST_GIVE_UP
}

// ���� ���� ����Ʈ ����Ʈ�� ����.(0xF6 0x1A)
void ReceiveProgressQuestList(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_QUESTEXP_PROGRESS_LIST pData = (LPPMSG_ANS_QUESTEXP_PROGRESS_LIST)ReceiveBuffer;
	g_QuestMng.SetCurQuestIndexList((DWORD*)(ReceiveBuffer + sizeof(PMSG_ANS_QUESTEXP_PROGRESS_LIST)),
		int(pData->m_byQuestCount));
}

// �������� ����Ʈ ����Ʈ���� Ư�� ����Ʈ�� �䱸, ���� ������ ����.(0xF6 0x1B)
void ReceiveProgressQuestRequestReward(BYTE* ReceiveBuffer)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_NPC_QUESTEXP_INFO pData = (LPPMSG_NPC_QUESTEXP_INFO)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	g_QuestMng.SetQuestRequestReward(ReceiveBuffer);
#ifdef ASG_MOD_UI_QUEST_INFO
	g_pMyQuestInfoWindow->SetSelQuestRequestReward();
#endif	// ASG_MOD_UI_QUEST_INFO
}

#ifdef ASG_FIX_QUEST_PROTOCOL_ADD
// ���� ���� ����Ʈ ����Ʈ�� �� �غ� ��.(0xF6 0x20)
void ReceiveProgressQuestListReady(BYTE* ReceiveBuffer)
{
	g_QuestMng.SetQuestIndexByEtcList(NULL, 0);	// ��Ÿ ��Ȳ�� ���� ����Ʈ ����Ʈ �ʱ�ȭ.
	SendRequestProgressQuestList();	// �������� ����Ʈ ����Ʈ ��û.
	SendRequestQuestByEtcEPList();	// ��Ÿ ��Ȳ�� ���� ����Ʈ ����Ʈ ��û.
}
#endif	// ASG_FIX_QUEST_PROTOCOL_ADD
#endif	// ASG_ADD_NEW_QUEST_SYSTEM

#ifdef ASG_ADD_GENS_SYSTEM
// �ս� ���� ��û ���� ����.(0xF8 0x02)
void ReceiveGensJoining(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_REG_GENS_MEMBER pData = (LPPMSG_ANS_REG_GENS_MEMBER)ReceiveBuffer;
	if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
		g_pNPCDialogue->ProcessGensJoiningReceive(pData->m_byResult, pData->m_byInfluence);
}

// �ս� Ż�� ��û ���� ����.(0xF8 0x04)
void ReceiveGensSecession(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_SECEDE_GENS_MEMBER pData = (LPPMSG_ANS_SECEDE_GENS_MEMBER)ReceiveBuffer;
	if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
		g_pNPCDialogue->ProcessGensSecessionReceive(pData->m_byResult);
}

// �ս� ���� ���� ����.(0xF8 0x07)
void ReceivePlayerGensInfluence(BYTE* ReceiveBuffer)
{
	LPPMSG_MSG_SEND_GENS_INFO pData = (LPPMSG_MSG_SEND_GENS_INFO)ReceiveBuffer;
	Hero->m_byGensInfluence = pData->m_byInfluence;
#ifdef PBG_ADD_GENSRANKING
	Hero->m_byRankIndex = pData->m_nGensClass;
	g_pNewUIGensRanking->SetContribution(pData->m_nContributionPoint);
	g_pNewUIGensRanking->SetRanking(pData->m_nRanking);
	g_pNewUIGensRanking->SetNextContribution(pData->m_nNextContributionPoint);
#endif //PBG_ADD_GENSRANKING
}

// ����Ʈ ���� �ٸ� �÷��̾��� �ս� ���� ���� ����.(0xF8, 0x05)
void ReceiveOtherPlayerGensInfluenceViewport(BYTE* ReceiveBuffer)
{
	LPPMSG_SEND_GENS_MEMBER_VIEWPORT Data = (LPPMSG_SEND_GENS_MEMBER_VIEWPORT)ReceiveBuffer;
	int nOffset = sizeof(PMSG_SEND_GENS_MEMBER_VIEWPORT);
	int i;
	for (i = 0 ; i < Data->m_byCount ; ++i)
	{
		LPPMSG_GENS_MEMBER_VIEWPORT_INFO Data2 = (LPPMSG_GENS_MEMBER_VIEWPORT_INFO)(ReceiveBuffer+nOffset);
		int nKey = ((int)(Data2->m_byNumberH&0x7f)<<8) + Data2->m_byNumberL;
		int nIndex = FindCharacterIndex(nKey);
		CHARACTER *c = &CharactersClient[nIndex];
		
		c->m_byGensInfluence = Data2->m_byInfluence;
#ifdef PBG_ADD_GENSRANKING
		c->m_byRankIndex = Data2->m_nGensClass;
#endif //PBG_ADD_GENSRANKING
#ifdef PBG_MOD_STRIFE_GENSMARKRENDER
		// ������ �⿩�� ����Ʈ�� �ʿ�� �ϰԵ�
		c->m_nContributionPoint = Data2->m_nContributionPoint;
#endif //PBG_MOD_STRIFE_GENSMARKRENDER
#ifdef ASG_ADD_INFLUENCE_GROUND_EFFECT
		if (::IsStrifeMap(World))	// ���������ΰ�?
		{
			vec3_t vTemp = {0.f, 0.f, 0.f};
			if (Hero->m_byGensInfluence == c->m_byGensInfluence)	// ���� ���� �����ΰ�?
				CreateEffect(BITMAP_OUR_INFLUENCE_GROUND, c->Object.Position, vTemp, vTemp, 0, &c->Object);
			else
				CreateEffect(BITMAP_ENEMY_INFLUENCE_GROUND, c->Object.Position, vTemp, vTemp, 0, &c->Object);
		}
#endif	// ASG_ADD_INFLUENCE_GROUND_EFFECT
		
		nOffset += sizeof(PMSG_GENS_MEMBER_VIEWPORT_INFO);
	}
}
#endif	// ASG_ADD_GENS_SYSTEM

#ifdef ASG_ADD_UI_NPC_DIALOGUE
// NPC UI�� ��ȭ�� ����Ǵ� NPC Ŭ�� �� ���� ����.(0xF9 0x01)
void ReceiveNPCDlgUIStart(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_NPC_CLICK pData = (LPPMSG_ANS_NPC_CLICK)ReceiveBuffer;
	if (!g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
	{
		g_QuestMng.SetNPC(pData->m_wNPCIndex); // NPC �̸� ����.
		g_pNPCDialogue->SetContributePoint(pData->m_dwContributePoint);	// �⿩�� ����.
		g_pNewUISystem->Show(SEASON3B::INTERFACE_NPC_DIALOGUE);
	}
}
#endif	// ASG_ADD_UI_NPC_DIALOGUE

#ifdef PBG_ADD_GENSRANKING
// ����ޱ� Ŭ���ÿ� ó��(0xF8 0x08)
void ReceiveReward(BYTE* ReceiveBuffer)
{
	LPPMSG_GENS_REWARD_CODE pData = (LPPMSG_GENS_REWARD_CODE)ReceiveBuffer;
	
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
		g_pNPCDialogue->ProcessGensRewardReceive(pData->m_byRewardResult);
}
#endif //PBG_ADD_GENSRANKING
//////////////////////////////////////////////////////////////////////////
//  ������Ʈ ����.
//////////////////////////////////////////////////////////////////////////
void ReceiveUseStateItem ( BYTE* ReceiveBuffer )
{
	LPPMSG_USE_STAT_FRUIT Data = (LPPMSG_USE_STAT_FRUIT)ReceiveBuffer;
	
	BYTE result	= Data->result;			// ���
	BYTE fruit	= Data->btFruitType;	// ��������
#ifdef PSW_FRUIT_ITEM
	WORD point	= Data->btStatValue;	// ���Ȱ�
#else //PSW_FRUIT_ITEM
	BYTE point	= Data->btStatValue;	// ���Ȱ�
#endif //PSW_FRUIT_ITEM
	
	unicode::t_char strText[MAX_GLOBAL_TEXT_STRING];
	
	switch(result) {
	case 0x00:	// ���Ȼ��� ����
		if(fruit >=0 && fruit <= 4)
		{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			int index = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
            int  index;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			
            switch ( fruit )
            {
            case 0: //  ������.
				CharacterAttribute->Energy      += point;
                index = 168;
                break;
				
            case 1: //  ü��.
				CharacterAttribute->Vitality    += point;
                index = 169;
                break;
				
            case 2: //  ��ø.
				CharacterAttribute->Dexterity   += point;
                index = 167;
                break;
                
            case 3: //  ��.
				CharacterAttribute->Strength    += point;
                index = 166;
                break;
			case 4:	//: ���
				CharacterAttribute->Charisma    += point;
                index = 1900;
				break;
            }
			
            //  ���� ������ �߰��� ���� ������.
            CharacterAttribute->AddPoint += point;
			
			unicode::_sprintf(strText, GlobalText[379], GlobalText[index], point, GlobalText[1412]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
		
	case 0x01:	// ���Ȼ��� ����
		SEASON3B::CreateOkMessageBox(GlobalText[378]);
		break;
		
	case 0x02:	// ���Ÿ� Stat Plus�� ��� �Ұ�
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[1904], GlobalText[1412]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
	case 0x03:	// ���Ȱ��� ����
		if(fruit >=0 && fruit <= 4)
		{
            int  index;
			
            switch ( fruit )
            {
            case 0: //  ������.
				CharacterAttribute->Energy      -= point;
                index = 168;
                break;
				
            case 1: //  ü��.
				CharacterAttribute->Vitality    -= point;
                index = 169;
                break;
				
            case 2: //  ��ø.
				CharacterAttribute->Dexterity   -= point;
                index = 167;
                break;
                
            case 3: //  ��.
				CharacterAttribute->Strength    -= point;
                index = 166;
                break;
			case 4:	//: ���
				CharacterAttribute->Charisma    -= point;
                index = 1900;
				break;
            }
			
            CharacterAttribute->LevelUpPoint += point;
            CharacterAttribute->wMinusPoint += point;
			
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[379], GlobalText[index], point, GlobalText[1903]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
		
	case 0x04:	// ���Ȱ��� ����
		SEASON3B::CreateOkMessageBox(GlobalText[1906]);
		break;
		
	case 0x05:	// ���Ÿ� Stat Minus�� ��� �Ұ�
		{
			unicode::t_char strText[128];
			unicode::_sprintf(strText, GlobalText[1904], GlobalText[1903]);
			SEASON3B::CreateOkMessageBox(strText);
		}
		break;
		
#ifdef PSW_FRUIT_ITEM
	case 0x06:
		if(fruit >=0 && fruit <= 4)
		{
			char Text[MAX_GLOBAL_TEXT_STRING];
            int  index;
			
            switch ( fruit )
            {
            case 0: //  ������.
				CharacterAttribute->Energy      -= point;
                index = 168;
                break;
				
            case 1: //  ü��.
				CharacterAttribute->Vitality    -= point;
                index = 169;
                break;
				
            case 2: //  ��ø.
				CharacterAttribute->Dexterity   -= point;
                index = 167;
                break;
                
            case 3: //  ��.
				CharacterAttribute->Strength    -= point;
                index = 166;
                break;
			case 4:	//: ���
				CharacterAttribute->Charisma    -= point;
                index = 1900;
				break;
            }
			
            CharacterAttribute->LevelUpPoint += point;
			//����� ���� ��Ű�� �ʴ´�.
			//���̳ʽ� ���� ���ſʹ� ������.
            //CharacterAttribute->wMinusPoint += point;
			
			sprintf ( Text, GlobalText[379], GlobalText[index], point, GlobalText[1903] );
			SEASON3B::CreateOkMessageBox( Text );
		}
		break;
	case 0x07:	// ���Ȱ��� ����	
		SEASON3B::CreateOkMessageBox( GlobalText[1906] ); // "���ҵ� ����Ʈ�� �����ϴ�."	
		break;
	case 0x08:	// ���Ÿ� Stat Minus�� ��� �Ұ�
		char Text[MAX_GLOBAL_TEXT_STRING];
		sprintf ( Text, GlobalText[1904], GlobalText[1903]);
		SEASON3B::CreateOkMessageBox( Text ); // 1904 "�ش� ������Ʈ�� �� �̻� %s ��ų �� �����ϴ�."
		break;
#endif //PSW_FRUIT_ITEM
		
	case 0x10:	// �������� �����ؼ� ��� �Ұ���
		{
			SEASON3B::CreateOkMessageBox(GlobalText[1909]);
		}
		break;
		
	case 0x21:	// ���� �ִ�ġ���� ��� ����
		SEASON3B::CreateOkMessageBox(GlobalText[1911]);
		break;
		
	case 0x25:	// ���� �ִ�ġ���� ��� ����
		SEASON3B::CreateOkMessageBox(GlobalText[1911]);
		break;
		
	case 0x26:	// �⺻�� ���Ϸδ� ���� �� �� ����
		SEASON3B::CreateOkMessageBox(GlobalText[1912]);
		break;
	}
	
    EnableUse = 0;
}

#ifdef PET_SYSTEM
//////////////////////////////////////////////////////////////////////////
//  Pet ����.
//////////////////////////////////////////////////////////////////////////
//  �������� �� ����� �޴´�.
//////////////////////////////////////////////////////////////////////////
void ReceivePetCommand ( BYTE* ReceiveBuffer )
{
	LPPRECEIVE_PET_COMMAND Data = ( LPPRECEIVE_PET_COMMAND )ReceiveBuffer;
	WORD Key = ((WORD)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
	
    //  ����� ����.
    giPetManager::SetPetCommand ( Hero, Key, Data->m_byCommand );
}


//  �������� ���� ����� �޴´�.
//////////////////////////////////////////////////////////////////////////
void ReceivePetAttack ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_PET_ATTACK Data = ( LPPRECEIVE_PET_ATTACK )ReceiveBuffer;
    WORD Key = ((WORD)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
    int  index = FindCharacterIndex ( Key );
    CHARACTER* sc = &CharactersClient[index];
	
    Key = ((WORD)(Data->m_byTKeyH)<<8) + Data->m_byTKeyL;
	
    //  ����.
    giPetManager::SetAttack ( sc, Key, Data->m_bySkillType );
}


//  ���� ������ �޴´�.
//////////////////////////////////////////////////////////////////////////
void ReceivePetInfo ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_PET_INFO Data = ( LPPRECEIVE_PET_INFO )ReceiveBuffer;
	
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	PET_INFO Petinfo;
	ZeroMemory( &Petinfo, sizeof(PET_INFO) );

	Petinfo.m_dwPetType = Data->m_byPetType;
	Petinfo.m_wLevel	= Data->m_byLevel;
	Petinfo.m_wLife		= Data->m_byLife;
	Petinfo.m_dwExp1	= Data->m_iExp;

	giPetManager::SetPetInfo( Data->m_byInvType, Data->m_byPos, &Petinfo );

#else // KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER

	PET_INFO Petinfo;
	ZeroMemory( &Petinfo, sizeof(PET_INFO) );

	Petinfo.m_dwPetType = Data->m_byPetType;
	Petinfo.m_wLevel	= Data->m_byLevel;
	Petinfo.m_wLife		= Data->m_byLife;
	Petinfo.m_dwExp1	= Data->m_iExp;
	
	giPetManager::SetPetInfo ( Data->m_byInvType, Data->m_byPos, Petinfo );

#else // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    giPetManager::SetPetInfo ( Data->m_byPetType, Data->m_byInvType, Data->m_byPos, Data->m_byLevel, Data->m_iExp );
#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER

    CharacterMachine->CalculateAll();

#endif // KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
}

#endif// PET_SYSTEM

void ReceiveWTTimeLeft(BYTE* ReceiveBuffer) // ���� ��� ����� ���� �ð� ǥ��
{
	LPPMSG_MATCH_TIMEVIEW Data = (LPPMSG_MATCH_TIMEVIEW)ReceiveBuffer;
	g_wtMatchTimeLeft.m_Time = Data->m_Time;
	g_wtMatchTimeLeft.m_Type = Data->m_Type;
}

void ReceiveWTMatchResult(BYTE* ReceiveBuffer)
{
	LPPMSG_MATCH_RESULT	Data = (LPPMSG_MATCH_RESULT)ReceiveBuffer;
	if(Data->m_Type >= 0 && Data->m_Type < 3)
	{
		g_wtMatchResult.m_Type = Data->m_Type;
		memset(g_wtMatchResult.m_MatchTeamName1, 0, MAX_ID_SIZE);
		memcpy(g_wtMatchResult.m_MatchTeamName1, Data->m_MatchTeamName1, MAX_ID_SIZE);
		g_wtMatchResult.m_Score1 = Data->m_Score1;
		memset(g_wtMatchResult.m_MatchTeamName2, 0, MAX_ID_SIZE);
		memcpy(g_wtMatchResult.m_MatchTeamName2, Data->m_MatchTeamName2, MAX_ID_SIZE);
		g_wtMatchResult.m_Score2 = Data->m_Score2;
	}
}

void ReceiveWTBattleSoccerGoalIn(BYTE* ReceiveBuffer)
{
/*	LPPMSG_SOCCER_GOALIN Data = (LPPMSG_SOCCER_GOALIN)ReceiveBuffer;

  //������ ��ġ�� ����Ʈ �߻�
  vec3_t Position, Angle, Light;
  Position[0]  = (float)(Data->m_x+0.5f)*TERRAIN_SCALE;
  Position[1]  = (float)(Data->m_y+0.5f)*TERRAIN_SCALE;
  Position[2] = RequestTerrainHeight(Position[0],Position[1]);
  ZeroMemory( Angle, sizeof ( Angle));
  Light[0] = Light[1] = Light[2] = 1.0f;
	CreateEffect(BITMAP_FIRECRACKERRISE,Position,Angle,Light);*/
} //���� ��ʸ�Ʈ�� ��� ���÷���


//////////////////////////////////////////////////////////////////////////
//  �л� ������ ���� �� ���� �̵� ��Ŷ.
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  ���̵��� ���� ���� ���� �ޱ�.
void ReceiveChangeMapServerInfo ( BYTE* ReceiveBuffer )
{
    LPPHEADER_MAP_CHANGESERVER_INFO Data = (LPPHEADER_MAP_CHANGESERVER_INFO)ReceiveBuffer;

#ifdef LDK_FIX_FULLSERVER_CONNECT_ERROR
	// Ǯ���� ���̵��� Ŭ���̾�Ʈ ���ɸ�.
	if( 0 == Data->m_vSvrInfo.m_wMapSvrPort	)
	{
#ifdef LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		g_bReponsedMoveMapFromServer = TRUE;			// ���̵����μ��������ޱ� �����̵�OK
#endif // LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT_EX01
		LoadingWorld = 0;

		Teleport = false;
		return;
	}
#endif //LDK_FIX_FULLSERVER_CONNECT_ERROR

#ifdef YDG_ADD_CS5_PORTAL_CHARM
	g_PortalMgr.Reset();
#endif	// YDG_ADD_CS5_PORTAL_CHARM

    g_csMapServer.ConnectChangeMapServer( Data->m_vSvrInfo );
}


//////////////////////////////////////////////////////////////////////////
//  �ʼ��� �̵� ��û ���.
void ReceiveChangeMapServerResult ( BYTE* ReceiveBuffer )
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    LPPHEADER_DEFAULT Data = (LPPHEADER_DEFAULT)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0xB1����[ReceiveChangeMapServerResult]");
#endif // CONSOLE_DEBUG	
}


void ReceiveBCStatus( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CASTLESIEGESTATE Data = (LPPMSG_ANS_CASTLESIEGESTATE)ReceiveBuffer;
	
	switch( Data->btResult )
	{
	case 0x00:	// ����
		g_pChatListBox->AddText("", GlobalText[1500], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1500 "����������"
		break;
	case 0x01:	// ����
	case 0x02:	// �����ξ���
		// ������ �������̽� ����
		g_pNewUISystem->Show(SEASON3B::INTERFACE_GUARDSMAN);
		g_pGuardWindow->SetData( Data );
		break;
	case 0x03:	// ������������
		g_pChatListBox->AddText("", GlobalText[1501], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1501 "������������"	
		break;
	case 0x04:	// ����������
		g_pChatListBox->AddText("", GlobalText[1502], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1502 "����������"
		break;
	}
}

void ReceiveBCReg( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_REGCASTLESIEGE Data = (LPPMSG_ANS_REGCASTLESIEGE)ReceiveBuffer;
	
	switch( Data->btResult )
	{
	case 0x00:
		g_pChatListBox->AddText("", GlobalText[1503], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1503 "������ ��� ����"
		break;
	case 0x01:
		g_GuardsMan.SetRegStatus( 1 );
		g_pChatListBox->AddText("", GlobalText[1504], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1504 "������ ��� ����"
		break;
	case 0x02:
		g_pChatListBox->AddText("", GlobalText[1505], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1505 "�������� �̹� ��ϵǾ� �ֽ��ϴ�."
		break;
	case 0x03:
		g_pChatListBox->AddText("", GlobalText[1506], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1506 "����� ������ ����Դϴ�."
		break;
	case 0x04:
		g_pChatListBox->AddText("", GlobalText[1507], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1507 "�߸��� ����Դϴ�."
		break;
	case 0x05:
		g_pChatListBox->AddText("", GlobalText[1508], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1508 "��帶������ ������ �����մϴ�."
		break;
	case 0x06:
		g_pChatListBox->AddText("", GlobalText[1509], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1509 "�Ҽӵ� ��尡 �����ϴ�."
		break;
	case 0x07:
		g_pChatListBox->AddText("", GlobalText[1510], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1510 "������ ��ϱⰣ�� �ƴմϴ�."
		break;
	case 0x08:
		g_pChatListBox->AddText("", GlobalText[1511], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1511 "���� ���� �����մϴ�."
		break;
	default:
		assert( !"�߸��� ReceiveBCReg(0xB2,0x01)" );
		break;
	}
}

void ReceiveBCGiveUp( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_GIVEUPCASTLESIEGE Data = (LPPMSG_ANS_GIVEUPCASTLESIEGE)ReceiveBuffer;
	
	switch( Data->btResult )
	{
	case 0x00:	// ����
		g_pChatListBox->AddText("", GlobalText[1512], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1512 "������ ���Ⱑ �����߽��ϴ�."
		break;
	case 0x01:	// ����
		SendRequestBCRegInfo();
		SendRequestBCDeclareGuildList();
		g_GuardsMan.SetRegStatus( 0 );
		g_pChatListBox->AddText("", GlobalText[1513], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1513 "������ ���Ⱑ �����߽��ϴ�."
		break;
	case 0x02:	// ��ϵȱ��ƴ�
		g_pChatListBox->AddText("", GlobalText[1514], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1514 "�������� ��ϵ� ��尡 �ƴմϴ�."
		break;
	case 0x03:	// �ð���������
		g_pChatListBox->AddText("", GlobalText[1515], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1515 "������ ���� �Ⱓ�� �ƴմϴ�."
		break;
	default:
		assert( !"�߸��� ReceiveBCGiveUp(0xB2,0x02)" );
		break;
	}
}

void ReceiveBCRegInfo( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_GUILDREGINFO Data = (LPPMSG_ANS_GUILDREGINFO)ReceiveBuffer;
	
	switch( Data->btResult )
	{
	case 0x00:	// ����
		g_GuardsMan.SetRegStatus( 0 );
		break;
	case 0x01:	// ����
		{
			g_GuardsMan.SetRegStatus( !Data->btIsGiveUp );
			DWORD dwMarkCount;
			BYTE* pMarkCount = (BYTE*)&dwMarkCount;
			*pMarkCount++ = Data->btGuildMark4;
			*pMarkCount++ = Data->btGuildMark3;
			*pMarkCount++ = Data->btGuildMark2;
			*pMarkCount++ = Data->btGuildMark1;
			g_GuardsMan.SetMarkCount( dwMarkCount );
		}
		break;
	case 0x02:	// ��ϵ� ��� �ƴ�
		g_GuardsMan.SetRegStatus( 0 );
		break;
	}
}

void ReceiveBCRegMark( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_REGGUILDMARK Data = (LPPMSG_ANS_REGGUILDMARK)ReceiveBuffer;
	
	switch( Data->btResult )
	{
	case 0x00:	// ����
		g_pChatListBox->AddText("", GlobalText[1516], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1516 "ǥ���� ����� �����߽��ϴ�."
		break;
	case 0x01:	// ����
		{
			DWORD dwMarkCount;
			BYTE* pMarkCount = (BYTE*)&dwMarkCount;
			*pMarkCount++ = Data->btGuildMark4;
			*pMarkCount++ = Data->btGuildMark3;
			*pMarkCount++ = Data->btGuildMark2;
			*pMarkCount++ = Data->btGuildMark1;
			g_GuardsMan.SetMarkCount( dwMarkCount );
		}
		break;
	case 0x02:	// ��ϵȱ��ƴ�
		g_pChatListBox->AddText("", GlobalText[1517], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1517 "�������� ������ ��尡 �ƴմϴ�."
		break;
	case 0x03:	// �߸��Ⱦ����۵��
		g_pChatListBox->AddText("", GlobalText[1518], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1518 "�߸��� �������� ����߽��ϴ�."
		break;
	}
}

void ReceiveBCNPCBuy( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_NPCBUY Data = (LPPMSG_ANS_NPCBUY)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		g_pChatListBox->AddText("", GlobalText[1519], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1519 "������ �����߽��ϴ�."	
		break;
	case 1:
		g_SenatusInfo.BuyNewNPC(Data->iNpcNumber, Data->iNpcIndex);
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	case 3:
		g_pChatListBox->AddText("", GlobalText[1520], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1520 "���Ժ���� ���ڶ��ϴ�."
		break;
	case 4:
		g_pChatListBox->AddText("", GlobalText[1616], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1616 "�̹� �����մϴ�."
		break;
	}
}

void ReceiveBCNPCRepair( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_NPCREPAIR Data = (LPPMSG_ANS_NPCREPAIR)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		{
			g_pChatListBox->AddText("", GlobalText[1519], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1519 "������ �����߽��ϴ�."
		}
		
		break;
	case 1:
		{
			LPPMSG_NPCDBLIST pNPCInfo = NULL;
			pNPCInfo = g_SenatusInfo.GetNPCInfo( Data->iNpcNumber, Data->iNpcIndex );
			pNPCInfo->iNpcHp = Data->iNpcHP;
			pNPCInfo->iNpcMaxHp = Data->iNpcMaxHP;
		}
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	case 3:
		g_pChatListBox->AddText("", GlobalText[1520], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1520 "���Ժ���� ���ڶ��ϴ�."
		break;
	}
}

void ReceiveBCNPCUpgrade( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_NPCUPGRADE Data = (LPPMSG_ANS_NPCUPGRADE)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		g_pChatListBox->AddText("", GlobalText[1519], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1519 "������ �����߽��ϴ�."	
		break;
	case 1:
		{
			LPPMSG_NPCDBLIST pNPCInfo = NULL;
			pNPCInfo = g_SenatusInfo.GetNPCInfo( Data->iNpcNumber, Data->iNpcIndex );
			if( Data->iNpcUpType == 1 )			// ����
				pNPCInfo->iNpcDfLevel = Data->iNpcUpValue;
			else if( Data->iNpcUpType == 2 )	// ȸ����
				pNPCInfo->iNpcRgLevel = Data->iNpcUpValue;
			else if( Data->iNpcUpType == 3 )	// ������
				pNPCInfo->iNpcHp = pNPCInfo->iNpcMaxHp = Data->iNpcUpValue;
		}
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	case 3:
		g_pChatListBox->AddText("", GlobalText[1520], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1520 "���Ժ���� ���ڶ��ϴ�."
		break;
	case 4:
		g_pChatListBox->AddText("", GlobalText[1521], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1521 "������ ���ڶ��ϴ�."
		break;
	case 5:
		g_pChatListBox->AddText("", GlobalText[1522], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1522 "Ÿ���� �߸��Ǿ����ϴ�."
		break;
	case 6:
		g_pChatListBox->AddText("", GlobalText[1523], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1523 "��û���� �߸��Ǿ����ϴ�."
		break;
	case 7:
		g_pChatListBox->AddText("", GlobalText[1524], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1524 "NPC�� �������� �ʽ��ϴ�."
		break;
	}
}

void ReceiveBCGetTaxInfo( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_TAXMONEYINFO Data = (LPPMSG_ANS_TAXMONEYINFO)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		g_pChatListBox->AddText("", GlobalText[1525], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1525 "����������� ����"
		break;
	case 1:
		g_SenatusInfo.SetTaxInfo( Data );
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	}
}

void ReceiveBCChangeTaxRate( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_TAXRATECHANGE Data = (LPPMSG_ANS_TAXRATECHANGE)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		g_pChatListBox->AddText("", GlobalText[1526], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1526 "������������ ����"		
		break;
	case 1:
        if ( Data->btTaxType==3 )   //  ����� �����.
        {
			g_pUIGateKeeper->SetEntranceFee ( (Data->btTaxRate1<<24) | (Data->btTaxRate2<<16) | (Data->btTaxRate3<<8) | (Data->btTaxRate4) );
        }
        else
        {
			g_SenatusInfo.ChangeTaxInfo( Data );
        }
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	}
}

void ReceiveBCWithdraw( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_MONEYDRAWOUT Data = (LPPMSG_ANS_MONEYDRAWOUT)ReceiveBuffer;
	switch( Data->btResult )
	{
	case 0:
		g_pChatListBox->AddText("", GlobalText[1527], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1527 "��� ����"
		break;
	case 1:
		g_SenatusInfo.ChangeCastleMoney( Data );
		break;
	case 2:
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	}
}

void ReceiveTaxInfo( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_MAPSVRTAXINFO Data = (LPPMSG_ANS_MAPSVRTAXINFO)ReceiveBuffer;
	// ī�������� ���� ����
	if( Data->btTaxType == 1 )
	{
		g_nChaosTaxRate = Data->btTaxRate;
	}
	// ���� ���� ����
	else if( Data->btTaxType == 2 )
	{
		g_pNPCShop->SetTaxRate(Data->btTaxRate);
		g_nTaxRate = Data->btTaxRate;
	}
	else
	{
		assert( !"�߸��� �������� ��Ŷ(0xB2(0x1A))" );
	}
}

void ReceiveHuntZoneEnter ( BYTE* ReceiveBuffer )
{
    LPPMSG_CSHUNTZONEENTER pData = (LPPMSG_CSHUNTZONEENTER)ReceiveBuffer;
	
    switch ( pData->m_byResult )
    {
    case 0: //  ����.
        {
            g_pUIPopup->CancelPopup ();
            g_pUIPopup->SetPopup ( GlobalText[860], 1, 50, POPUP_OK, NULL );
        }
        break;
		
    case 1: //  ����.
        g_pUIGateKeeper->SetPublic ( pData->m_byHuntZoneEnter );
        break;
		
    case 2: //  ������ �����ϴ�.
        {
            g_pUIPopup->CancelPopup ();
            g_pUIPopup->SetPopup ( GlobalText[1386], 1, 50, POPUP_OK, NULL );
        }
        break;
    }
}

void ReceiveBCNPCList( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_NPCDBLIST Data = (LPPMSG_ANS_NPCDBLIST)ReceiveBuffer;
	int Offset = sizeof(PMSG_ANS_NPCDBLIST);
	
	switch( Data->btResult )
	{
	case 0:	// ����
		g_pChatListBox->AddText("", GlobalText[860], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 860 "�����߽��ϴ�."
		break;
	case 1:	// ����
		{
			for( int i=0 ; i<Data->iCount ; ++i )
			{
				LPPMSG_NPCDBLIST pNpcInfo = (LPPMSG_NPCDBLIST)(ReceiveBuffer+Offset);
				g_SenatusInfo.SetNPCInfo( pNpcInfo );
				Offset += sizeof(PMSG_NPCDBLIST);
			}
		}
		break;
	case 2:	// �����̾���
		g_pChatListBox->AddText("", GlobalText[1386], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1386 "������ �����ϴ�."
		break;
	}
}

void ReceiveBCDeclareGuildList( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CSREGGUILDLIST Data = (LPPMSG_ANS_CSREGGUILDLIST)ReceiveBuffer;
	int Offset = sizeof(PMSG_ANS_CSREGGUILDLIST);
	
	switch( Data->btResult )
	{
	case 0:	// ����
		g_pChatListBox->AddText("", GlobalText[860], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 860 "�����߽��ϴ�."
		break;
	case 1:	// ����
		{
			g_pGuardWindow->ClearDeclareGuildList();
			for( int i=0 ; i<Data->iCount ; ++i )
			{
				LPPMSG_CSREGGUILDLIST pData2 = (LPPMSG_CSREGGUILDLIST)(ReceiveBuffer+Offset);
				
				DWORD dwMarkCount;
				BYTE* pMarkCount = (BYTE*)&dwMarkCount;
				*pMarkCount++ = pData2->btRegMarks4;
				*pMarkCount++ = pData2->btRegMarks3;
				*pMarkCount++ = pData2->btRegMarks2;
				*pMarkCount++ = pData2->btRegMarks1;
				
				g_pGuardWindow->AddDeclareGuildList( pData2->szGuildName, dwMarkCount, pData2->btIsGiveUp, pData2->btSeqNum );
				
				Offset += sizeof(PMSG_CSREGGUILDLIST);
			}
			g_pGuardWindow->SortDeclareGuildList();
		}
		break;
	}
}

void ReceiveBCGuildList( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CSATTKGUILDLIST Data = (LPPMSG_ANS_CSATTKGUILDLIST)ReceiveBuffer;
	int Offset = sizeof(PMSG_ANS_CSATTKGUILDLIST);
	
	switch( Data->btResult )
	{
	case 0:	// ����
		g_pChatListBox->AddText("", GlobalText[860], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 860 "�����߽��ϴ�."
		break;
	case 1:	// ����
		{
			g_pGuardWindow->ClearGuildList();
			for( int i=0 ; i<Data->iCount ; ++i )
			{
				LPPMSG_CSATTKGUILDLIST pData2 = (LPPMSG_CSATTKGUILDLIST)(ReceiveBuffer+Offset);
				
				g_pGuardWindow->AddGuildList( pData2->szGuildName, pData2->btCsJoinSide, pData2->btGuildInvolved, pData2->iGuildScore);
				
				Offset += sizeof(PMSG_CSATTKGUILDLIST);
			}
		}
		break;
	case 2:	// �Ⱓ�ƴ�
		g_pChatListBox->AddText("", GlobalText[1609], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1609 "���� Ȯ������ �ʾҽ��ϴ�."
		break;
	case 3:	// �������غ�ʵ�
		g_pChatListBox->AddText("", GlobalText[1609], SEASON3B::TYPE_SYSTEM_MESSAGE);	// 1609 "���� Ȯ������ �ʾҽ��ϴ�."
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//  ���� ���� ��������.
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//  ���� ���� ���ý� ��밡�� ���� �� ��Ÿ ����.
//////////////////////////////////////////////////////////////////////////
void ReceiveGateState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_GATE_STATE Data = (LPPRECEIVE_GATE_STATE)ReceiveBuffer;
	int Key = ((int)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
	
	switch( Data->m_byResult )
	{
	case 0: //  ����.
		break;
		
	case 1: //  ����.
		npcGateSwitch::DoInterfaceOpen ( Key );
		g_pNewUISystem->Show(SEASON3B::INTERFACE_GATESWITCH);
		break;
		
	case 2: //  ������ ����.
		break;
		
	case 3: //  ���� ����.
		break;
		
	case 4: //  ���� ����.
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//  ������ ����/����.
//////////////////////////////////////////////////////////////////////////
void ReceiveGateOperator ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_GATE_OPERATOR Data = (LPPRECEIVE_GATE_OPERATOR)ReceiveBuffer;
    int Key = ((int)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
	
    //  ������ ���� ����.
    npcGateSwitch::ProcessState ( Key, Data->m_byOperator, Data->m_byResult );
}


//////////////////////////////////////////////////////////////////////////
//  ���� ������ ���°� ����Ǿ� �� ���¸� �����ش�.
//////////////////////////////////////////////////////////////////////////
void ReceiveGateCurrentState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_GATE_CURRENT_STATE Data = (LPPRECEIVE_GATE_CURRENT_STATE)ReceiveBuffer;
    int Key = ((int)(Data->m_byKeyH)<<8) + Data->m_byKeyL;
    int Index = FindCharacterIndex ( Key );
	
    CHARACTER* c = &CharactersClient[Index];
    OBJECT* o = &c->Object;
	
    if ( Data->m_byOperator )
    {
		// ���� �������̿��ٸ� ��ҽ�Ų��.
		if( Attacking != -1 && SelectedCharacter == Index )
		{
			Attacking = -1;
		}
        npcGateSwitch::GateOpen ( c, o );
    }
    else
    {
        npcGateSwitch::GateClose ( c, o );
    }
}


//////////////////////////////////////////////////////////////////////////
//  �հ� ����ġ �۵� ����.
//////////////////////////////////////////////////////////////////////////
void ReceiveCrownSwitchState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_SWITCH_PROC pData = (LPPRECEIVE_SWITCH_PROC)ReceiveBuffer;
	
    int iKey = ((int)(pData->m_byIndexH)<<8) + pData->m_byIndexL;
    int iIndex = FindCharacterIndex ( iKey );
	
    CHARACTER* CrownSwitch = &CharactersClient[iIndex];
	
    if(CrownSwitch == NULL)
	{
		return;
	}
    if(CrownSwitch->ID == NULL)
	{
		return;
	}
	
    switch( pData->m_byState )
    {
    case 0: //  ����ġ ��.
		{
			int iSwitchIndex = ((int)(pData->m_byIndexH)<<8) + pData->m_byIndexL;
			if(iSwitchIndex == FIRST_CROWN_SWITCH_NUMBER)
			{
				Switch_Info[0].Reset();
			}
			else
			{
				Switch_Info[1].Reset();
			}

			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCrownSwitchPopLayout));	
		}
        break;
		
    case 1: //  ����ġ �۵�.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCrownSwitchPushLayout));
        break;
		
    case 2: //  �ٸ��̰� ����ġ �۵���.
        {
			int iKey   = ((int)(pData->m_byKeyH)<<8) + pData->m_byKeyL;
            int iIndex = FindCharacterIndex ( iKey );
            CHARACTER* pCha = &CharactersClient[iIndex];
			unicode::t_char strText[256];
			
			SEASON3B::CProgressMsgBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCrownSwitchOtherPushLayout), &pMsgBox);
			if(pMsgBox)
			{
				if(pCha != NULL && pCha->ID != NULL)
				{
					// 1486 "%s�Բ���"
					unicode::_sprintf(strText, GlobalText[1486], pCha->ID);
				}
				else
				{
					// 1487 "�ƹ����Բ���"
					unicode::_sprintf(strText, GlobalText[1487]);	
				}
				pMsgBox->AddMsg(strText);
				
				// 1488 "�̹� %s�� ������ �ֽ��ϴ�"
				unicode::_sprintf(strText, GlobalText[1488], CrownSwitch->ID);
				pMsgBox->AddMsg(strText);
			}
        }
        break;
    }
}

// ���� ����߿��� ESC �� ���� ��Ҵ� �Ұ���
int DenyCrownRegistPopupClose( POPUP_RESULT Result )
{
	if( Result & POPUP_RESULT_ESC )
		return 0;
	return 1;
}

//////////////////////////////////////////////////////////////////////////
//  �հ� ���ε�� ����.
//////////////////////////////////////////////////////////////////////////
void ReceiveCrownRegist ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CROWN_STATE pData = (LPPRECEIVE_CROWN_STATE)ReceiveBuffer;
	
	g_MessageBox->PopAllMessageBoxes();
	
    switch ( pData->m_byCrownState )
    {
    case 0: //  ���� ��� ����.
		{
			//  �ð� ����ٸ� ������Ų��.
			SEASON3B::CProgressMsgBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterStartLayout), &pMsgBox);
			if(pMsgBox)
			{
				unicode::t_char strText[256];
				// 1980 "%s (�����ð� : %d��)"
				// 1489 "���� ����� �����մϴ�"
				int iTime = (pData->m_dwCrownAccessTime/1000);
				if(iTime >= 59)
					iTime = 59;
				unicode::_sprintf(strText, GlobalText[1980], GlobalText[1489], iTime);
				pMsgBox->AddMsg(strText);
				pMsgBox->SetElapseTime(60000 - pData->m_dwCrownAccessTime);
			}
		}
        break;
		
    case 1: //  ���� ��� ����.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterSuccessLayout));
        break;
		
    case 2: //  ���� ��� ����.
		{
			SEASON3B::CProgressMsgBox* pMsgBox = NULL;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterFailLayout), &pMsgBox);
			if(pMsgBox)
			{
				unicode::t_char strText[256];
				// 1980 "%s (�����ð� : %d��)"
				// 1491 "���� ��Ͽ� �����߽��ϴ�"
				int iTime = (pData->m_dwCrownAccessTime/1000);
				if(iTime >= 59)
					iTime = 59;
				unicode::_sprintf(strText, GlobalText[1980], GlobalText[1491], iTime);
				pMsgBox->AddMsg(strText);
			}
		}
        break;
		
    case 3: //  �ٸ� ��� �����.
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterOtherLayout));
		}
        break;
	case 4:
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterOtherCampLayout));
        break;
		
    }
}


//////////////////////////////////////////////////////////////////////////
//  �հ� ���ε�� ����.
//////////////////////////////////////////////////////////////////////////
void ReceiveCrownState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CROWN_STATE pData = (LPPRECEIVE_CROWN_STATE)ReceiveBuffer;
	
    //  ������ ����ִ� �ð��ٸ� ���ش�.
    g_pUIPopup->CancelPopup ();
    switch ( pData->m_byCrownState )
    {
    case 0: //  �� ����.
        {
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCrownDefenseRemoveLayout));	
			
            int Index = FindCharacterIndexByMonsterIndex ( 216 );

            OBJECT* o = &CharactersClient[Index].Object;

			g_CharacterRegisterBuff(o, eBuff_CastleCrown);
        }
        break;
		
    case 1: //  �� ����.
        {
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCrownDefenseCreateLayout));
			
            int Index = FindCharacterIndexByMonsterIndex ( 216 );

            OBJECT* o = &CharactersClient[Index].Object;

			g_CharacterClearBuff(o);
        }
        break;
		
    case 2: //  ��� ����.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSealRegisterSuccessLayout));
        
        break;
    }
}


//////////////////////////////////////////////////////////////////////////
//  �ڽ��� ��/�� ���� �Ӽ� �˸�.
//////////////////////////////////////////////////////////////////////////
void ReceiveBattleCastleRegiment ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CROWN_STATE pData = (LPPRECEIVE_CROWN_STATE)ReceiveBuffer;
	
    switch ( pData->m_byCrownState )
    {
    case 0:
		battleCastle::SettingBattleFormation ( Hero, static_cast<eBuffState>(0) );
        return;
    case 1: //  ����.
		battleCastle::SettingBattleFormation(Hero, eBuff_CastleRegimentDefense);
		break;
    case 2: //  ����.
		battleCastle::SettingBattleFormation ( Hero, eBuff_CastleRegimentAttack1 );
        break;
	case 3: //  ����.
		battleCastle::SettingBattleFormation ( Hero, eBuff_CastleRegimentAttack2 );
		break;
	case 4: //  ����.
		battleCastle::SettingBattleFormation ( Hero, eBuff_CastleRegimentAttack3 );
		break;
    }
}


//////////////////////////////////////////////////////////////////////////
//���� ������ ���� ���¸� �˸�.
//////////////////////////////////////////////////////////////////////////
void ReceiveBattleCasleSwitchInfo( BYTE* ReceiveBuffer )
{
	LPRECEIVE_CROWN_SWITCH_INFO pData = (LPRECEIVE_CROWN_SWITCH_INFO)ReceiveBuffer;
	Check_Switch (pData);
}

bool Check_Switch (PRECEIVE_CROWN_SWITCH_INFO *Data)
{
	if(Switch_Info == NULL)
	{
		Switch_Info = new CROWN_SWITCH_INFO[2];
		
		WORD Key = ((WORD)(Data->m_byIndex1)<<8) + Data->m_byIndex2;
		
		if(Key == FIRST_CROWN_SWITCH_NUMBER)
		{
			Switch_Info[0].m_bySwitchState = Data->m_bySwitchState;
			Switch_Info[0].m_JoinSide = Data->m_JoinSide;
		}
		else
		{
			Switch_Info[1].m_bySwitchState = Data->m_bySwitchState;
			Switch_Info[1].m_JoinSide = Data->m_JoinSide;
		}
	}
	else
	{
		WORD Key = ((WORD)(Data->m_byIndex1)<<8) + Data->m_byIndex2;
		
		if(Key == FIRST_CROWN_SWITCH_NUMBER)
		{
			Switch_Info[0].m_bySwitchState = Data->m_bySwitchState;
			Switch_Info[0].m_JoinSide = Data->m_JoinSide;
		}
		else
		{
			Switch_Info[1].m_bySwitchState = Data->m_bySwitchState;
			Switch_Info[1].m_JoinSide = Data->m_JoinSide;
		}
			
			char GName[8+1];
			memset(GName, 0, 8+1);
			memcpy(GName, (char*)Data->m_szGuildName, 8);
			
			GName[8] = NULL;
			
			if(Key == FIRST_CROWN_SWITCH_NUMBER)
				{
					memcpy(&Switch_Info[0].m_szGuildName, GName, 9);
				}
				else
				{
					memcpy(&Switch_Info[1].m_szGuildName, GName, 9);
				}
				
				char Name[MAX_ID_SIZE+1];
				memset(Name, 0, MAX_ID_SIZE+1);
				memcpy(Name, (char *)Data->m_szUserName, MAX_ID_SIZE);
				Name[MAX_ID_SIZE] = NULL;
				if(Key == FIRST_CROWN_SWITCH_NUMBER)
					{
						memcpy(&Switch_Info[0].m_szUserName,Name,MAX_ID_SIZE+1);
					}
					else
					{
						memcpy(&Switch_Info[1].m_szUserName,Name,MAX_ID_SIZE+1);
					}
					
	}
	return true;
}

bool Delete_Switch()
{
	if(Switch_Info != NULL)
	{
		delete [] Switch_Info;
		Switch_Info = NULL;
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
//  ���� ������ ���� ���θ� �˸�.
//////////////////////////////////////////////////////////////////////////
void ReceiveBattleCastleStart ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CROWN_STATE pData = (LPPRECEIVE_CROWN_STATE)ReceiveBuffer;
	
	bool bStartBattleCastle = (bool)(pData->m_byCrownState);
	
    battleCastle::SetBattleCastleStart ( bStartBattleCastle );
	
	if( bStartBattleCastle )
	{
		g_pSiegeWarfare->InitSkillUI();
	}
	else
	{
		// ����
		g_pSiegeWarfare->ReleaseSkillUI();
	}
}


//////////////////////////////////////////////////////////////////////////
//  ������ ���� ���� �˸�.
//////////////////////////////////////////////////////////////////////////
void ReceiveBattleCastleProcess ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_BC_PROCESS pData = (LPPRECEIVE_BC_PROCESS)ReceiveBuffer;
	
    switch ( pData->m_byBasttleCastleState )
    {
    case 0: //  ���� ���� ��� �õ�.
        {
            char GuildName[8+1];
			memset(GuildName, 0, 8+1);
            memcpy ( GuildName, (char *)pData->m_szGuildName, 8 );
            GuildName[8] = NULL;
			
            char Text[100];
            wsprintf ( Text, GlobalText[1496], GuildName );
			CreateNotice ( Text, 1 );
        }
        break;
		
    case 1: //  �߰� �¸�.
        {
            char Text[8+1];
			memset(Text, 0, 8+1);
            memcpy ( Text, (char *)pData->m_szGuildName, 8 );
            Text[8] = NULL;
            ChangeBattleFormation ( Text, true );
			
            char Text2[100];
            wsprintf ( Text2, GlobalText[1497], Text );
            CreateNotice ( Text2, 1 );
        }
        break;
    }
}


//////////////////////////////////////////////////////////////////////////
//  ������ ��ų�� ���� KillCount���� �޴´�.
//////////////////////////////////////////////////////////////////////////
void    ReceiveKillCount ( BYTE* ReceiveBuffer )
{
    LPPWHEADER_DEFAULT_WORD pData = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
    if ( pData->Value==0 )
    {
        if ( Hero->BackupCurrentSkill!=255 )
        {
            Hero->CurrentSkill = Hero->BackupCurrentSkill;
        }
        Hero->BackupCurrentSkill = 255;
        Hero->GuildMasterKillCount = 0;
    }
    else
    {
        Hero->GuildMasterKillCount = pData->Value;
    }
}


//////////////////////////////////////////////////////////////////////////
//  ������ �����Ǵ� �ð��� �޴´�.
//////////////////////////////////////////////////////////////////////////
void    ReceiveBuildTime ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_MONSTER_BUILD_TIME pData = (LPPRECEIVE_MONSTER_BUILD_TIME)ReceiveBuffer;
	int Key = ((int)(pData->m_byKeyH)<<8) + pData->m_byKeyL;
	int Index = FindCharacterIndex ( Key );
	
    CHARACTER* c = &CharactersClient[Index];
    OBJECT* o = &c->Object;
	
    //  ���� �ð��� ��´�.
    o->m_byBuildTime = pData->m_byBuildTime;
}


//////////////////////////////////////////////////////////////////////////
//  GC [0xB9][0x02] ���� ������ ��� ��ũ.
//////////////////////////////////////////////////////////////////////////
void    ReceiveCastleGuildMark ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CASTLE_FLAG pData = (LPPRECEIVE_CASTLE_FLAG)ReceiveBuffer;
	
	BYTE GuildMark[64];
	for(int i=0;i<64;i++)
	{
		if(i%2 == 0)
			GuildMark[i] = (pData->m_byGuildMark[i/2]>>4)&0x0f;
		else
			GuildMark[i] = pData->m_byGuildMark[i/2]&0x0f;
	}
    CreateCastleMark ( BITMAP_INTERFACE_MAP, GuildMark ); 
}


//////////////////////////////////////////////////////////////////////////
//  GC [0xB9][0x03] �� ����� �����Ⱑ �� ������� ���� ������ �˷��ش�.
//////////////////////////////////////////////////////////////////////////
void    ReceiveCastleHuntZoneInfo ( BYTE* RecevieBuffer )
{
    LPPRECEIVE_CASTLE_HUNTZONE_INFO pData = (LPPRECEIVE_CASTLE_HUNTZONE_INFO)RecevieBuffer;
	
    if ( pData->m_byResult==0 )
    {
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGatemanFailMsgBoxLayout));
    }
    else
    {
        g_pUIGateKeeper->SetInfo ( pData->m_byResult, (bool)pData->m_byEnable, pData->m_iCurrPrice, pData->m_iUnitPrice, pData->m_iMaxPrice );
		g_pNewUISystem->Show(SEASON3B::INTERFACE_GATEKEEPER);
    }
}


//////////////////////////////////////////////////////////////////////////
//  GC [0xB9][0x05] �� ����� ���� ���.
//////////////////////////////////////////////////////////////////////////
void    ReceiveCastleHuntZoneResult ( BYTE* ReceiveBuffer )
{
    LPPRECEVIE_CASTLE_HUNTZONE_RESULT pData = (LPPRECEVIE_CASTLE_HUNTZONE_RESULT)ReceiveBuffer;
	
    if ( pData->m_byResult==0 )
    {
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CGatemanFailMsgBoxLayout));
    }
}


//////////////////////////////////////////////////////////////////////////
//  ������ ���� ��������
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//  ���� ���� ���� ���.
//////////////////////////////////////////////////////////////////////////
void ReceiveCatapultState ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_CATAPULT_STATE pData = (LPPRECEIVE_CATAPULT_STATE)ReceiveBuffer;
	
    if ( pData->m_byResult==1 )
    {
        int Key = ((int)(pData->m_byKeyH)<<8) + pData->m_byKeyL;
		
		g_pNewUISystem->Show(SEASON3B::INTERFACE_CATAPULT);
		g_pCatapultWindow->Init(Key, pData->m_byWeaponType);
    }
    else if ( pData->m_byResult==0 )
    {
		g_pChatListBox->AddText( "", "���� ���� ���� ����", SEASON3B::TYPE_SYSTEM_MESSAGE);
    }
}


//////////////////////////////////////////////////////////////////////////
//  �������⸦ �߻��϶�� ����� �޴´�.
//////////////////////////////////////////////////////////////////////////
void    ReceiveCatapultFire ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_WEAPON_FIRE pData = (LPPRECEIVE_WEAPON_FIRE)ReceiveBuffer;
    
    if ( pData->m_byResult )
    {
        int Key = ((int)(pData->m_byKeyH)<<8) + pData->m_byKeyL;
		
        //  ������ ����Ѵ�.
		g_pCatapultWindow->DoFire(Key, pData->m_byResult, pData->m_byWeaponType, pData->m_byTargetX, pData->m_byTargetY);
    }
    else if ( pData->m_byResult==0 )    //  ����.
    {
		g_pChatListBox->AddText( "", "�������� �߻� �����߽��ϴ�.", SEASON3B::TYPE_SYSTEM_MESSAGE);
    }
}


//////////////////////////////////////////////////////////////////////////
//  �������Ⱑ �ڽŵ鿡�� �߻�Ǿ����� �˸�.
//////////////////////////////////////////////////////////////////////////
void    ReceiveCatapultFireToMe ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_BOMBING_ALERT pData = (LPPRECEIVE_BOMBING_ALERT)ReceiveBuffer;
	
	g_pCatapultWindow->DoFireFixStartPosition(pData->m_byWeaponType, pData->m_byTargetX, pData->m_byTargetY);
}


//////////////////////////////////////////////////////////////////////////
//  �������⿡ ������ �޴´�. ( ���� �޴� ĳ���͵鸸 ���� ).
//////////////////////////////////////////////////////////////////////////
/*
void    ReceiveDamageFrmeCatapult ( BYTE* ReceiveBuffer )
{
LPPRECEIVE_BOMBING_TARGET pData = (LPPRECEIVE_BOMBING_TARGET)ReceiveBuffer;
int Key = (((int)pData->m_byKeyH)<<8) + pData->m_byKeyL;
int Index = FindCharacterIndex ( Key );
CHARACTER* tc = &CharactersClient[Index];
OBJECT* to = &tc->Object;

  switch ( pData->m_byWeaponType )
  {
  case 1:
  SetAction ( to, PLAYER_SKILL_VITALITY );// PLAYER_HIGH_SHOCK );
  break;
  }
  }
*/

//  �ӽ����� ��ġ�� ����Ʈ ������ �޴´�. ( ���� ��ô�� ���� )
void    ReceivePreviewPort ( BYTE* ReceiveBuffer )
{
	LPPWHEADER_DEFAULT_WORD pData = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	for ( int i=0;i<pData->Value;i++ )
	{
		LPPRECEIVE_PREVIEW_PORT pData2 = (LPPRECEIVE_PREVIEW_PORT)(ReceiveBuffer+Offset);
		WORD Key       = ((WORD)(pData2->m_byKeyH)<<8) + pData2->m_byKeyL;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int CreateFlag = (Key>>15);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		Key &= 0x7FFF;
		
        switch ( pData2->m_byObjType )
        {
        case 1: //  ĳ����.
            {
				CHARACTER* c = CreateCharacter ( Key, MODEL_PLAYER, pData2->m_byPosX, pData2->m_byPosY, 0 );
				OBJECT* o = &c->Object;
				
				c->Class = ChangeServerClassTypeToClientClassType(pData2->m_byTypeH);
				c->Skin = 0;
				c->PK   = 0;
				o->Kind = KIND_TMP;
				
				for( int j = 0; j < pData2->s_BuffCount; ++j )
				{
					RegisterBuff(static_cast<eBuffState>(pData2->s_BuffEffectState[j]), o);
				}
                
                c->PositionX = pData2->m_byPosX;
                c->PositionY = pData2->m_byPosY;
                c->TargetX = pData2->m_byPosX;
                c->TargetY = pData2->m_byPosY;
                c->Object.Angle[2] = rand()%360;
				
                c->m_iDeleteTime = 150;
				
				ChangeCharacterExt ( FindCharacterIndex( Key ), pData2->m_byEquipment );
                
                strcpy ( c->ID, "   " );
                c->ID[MAX_ID_SIZE] = NULL;
            }
            break;
			
        case 2:    //   ����.
        case 3:    //   NPC
            {
                WORD Type = ((WORD)(pData2->m_byTypeH)<<8) + pData2->m_byTypeL;
				CHARACTER *c = CreateMonster ( Type, pData2->m_byPosX, pData2->m_byPosY, Key );
				if ( c==NULL ) break;
				OBJECT *o = &c->Object;
				
				for( int j = 0; j < pData2->s_BuffCount; ++j )
				{
					RegisterBuff(static_cast<eBuffState>(pData2->s_BuffEffectState[j]), o);
				}
				
                c->PositionX = pData2->m_byPosX;
                c->PositionY = pData2->m_byPosY;
                c->TargetX = pData2->m_byPosX;
                c->TargetY = pData2->m_byPosY;
                c->Object.Angle[2] = rand()%360;
				
                c->m_iDeleteTime = 150;
				
                if ( battleCastle::InBattleCastle() && c->MonsterIndex==277 )        
                {
                    //  State���� ���� �ൿ�� �����Ѵ�.
					
					if (g_isCharacterBuff((&c->Object), eBuff_CastleGateIsOpen))  //  ������ �����ִ� ����.
					{
						SetAction ( &c->Object, 1 );
						battleCastle::SetCastleGate_Attribute ( pData2->m_byPosX, pData2->m_byPosY, 0 );
					}
					else if(g_isNotCharacterBuff((&c->Object))) //  ������ �����ִ� ����. 
					{
						SetAction ( &c->Object, 0 );
						battleCastle::SetCastleGate_Attribute ( pData2->m_byPosX, pData2->m_byPosY, 1 );
					}
                }
            }
            break;
		}

		Offset += (sizeof(PRECEIVE_PREVIEW_PORT)-(sizeof(BYTE)*(MAX_BUFF_SLOT_INDEX-pData2->s_BuffCount)));
	}
}



//////////////////////////////////////////////////////////////////////////
//  �� ���� �������̽�.
//////////////////////////////////////////////////////////////////////////
//  �� ������ �ֱ������� �����޶�� ��û �����.
void ReceiveMapInfoResult ( BYTE* ReceiveBuffer )
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
    LPPRECEIVE_MAP_INFO_RESULT pData = (LPPRECEIVE_MAP_INFO_RESULT)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}

//  (����)��� �������� ����� �޴´�.
void ReceiveGuildCommand ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_GUILD_COMMAND  pData = (LPPRECEIVE_GUILD_COMMAND)ReceiveBuffer;
    GuildCommander            GCmd = { pData->m_byTeam, pData->m_byX, pData->m_byY, pData->m_byCmd };
	
	if( g_pSiegeWarfare )
	{
		g_pSiegeWarfare->SetMapInfo( GCmd );
	}
}

//  (����)�������� ��ġ�� �޴´�.
void ReceiveGuildMemberLocation ( BYTE* ReceiveBuffer )
{
	if( g_pSiegeWarfare->GetCurSiegeWarType() != TYPE_GUILD_COMMANDER )
		return;
	
	g_pSiegeWarfare->ClearGuildMemberLocation( );
	
    LPPWHEADER_DEFAULT_WORD2 pData = (LPPWHEADER_DEFAULT_WORD2)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD2);
	
	for ( int i=0; i<pData->Value; i++ )
	{
		LPPRECEIVE_MEMBER_LOCATION pData2 = (LPPRECEIVE_MEMBER_LOCATION)(ReceiveBuffer+Offset);
		
		g_pSiegeWarfare->SetGuildMemberLocation( 0, pData2->m_byX, pData2->m_byY );
		
		Offset += sizeof(PRECEIVE_MEMBER_LOCATION);
	}
}


//  (����)��忡 ���ԵǴ� NPC�� �޴´�.
void ReceiveGuildNpcLocation ( BYTE* ReceiveBuffer )
{
	if( g_pSiegeWarfare->GetCurSiegeWarType() != TYPE_GUILD_COMMANDER )
		return;
	
    LPPWHEADER_DEFAULT_WORD pData = (LPPWHEADER_DEFAULT_WORD)ReceiveBuffer;
	int Offset = sizeof(PWHEADER_DEFAULT_WORD);
	
	for ( int i=0; i<pData->Value; i++ )
	{
		LPPRECEIVE_NPC_LOCATION pData2 = (LPPRECEIVE_NPC_LOCATION)(ReceiveBuffer+Offset);
		g_pSiegeWarfare->SetGuildMemberLocation( pData2->m_byType+1, pData2->m_byX, pData2->m_byY );
		
		Offset += sizeof(PRECEIVE_NPC_LOCATION);
	}
}


//  ������(��Ÿ)�� ���� �ð��� ����ڵ鿡�� �ֱ������� �˸�.
void ReceiveMatchTimer ( BYTE* ReceiveBuffer )
{
    LPPRECEIVE_MATCH_TIMER pData = (LPPRECEIVE_MATCH_TIMER)ReceiveBuffer;
	
	g_pSiegeWarfare->SetTime( pData->m_byHour, pData->m_byMinute );
}

//////////////////////////////////////////////////////////////////////////
//	ũ���̿��� 1�� ���̵� MVP
//////////////////////////////////////////////////////////////////////////
void ReceiveCrywolfInfo ( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CRYWOLF_INFO pData = (LPPMSG_ANS_CRYWOLF_INFO)ReceiveBuffer;
	
	M34CryWolf1st::CheckCryWolf1stMVP(pData->btOccupationState, pData->btCrywolfState);	// ũ���̿��� �ʻ��¿� ���� ���� ��
	g_Direction.m_CMVP.GetCryWolfState(pData->btCrywolfState);	// ����κ� üũ
	
}

void ReceiveCrywolStateAltarfInfo ( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CRYWOLF_STATE_ALTAR_INFO pData = (LPPMSG_ANS_CRYWOLF_STATE_ALTAR_INFO)ReceiveBuffer;
	
	// ũ���̿��� ���� HP�� ũ���̿��� ���� ����
	M34CryWolf1st::CheckCryWolf1stMVPAltarfInfo(pData->iCrywolfStatueHP,
		pData->btAltarState1,
		pData->btAltarState2,
		pData->btAltarState3,
		pData->btAltarState4,
		pData->btAltarState5);
}

//���ܵ��� ���õ����� �亯
void ReceiveCrywolfAltarContract ( BYTE* ReceiveBuffer )
{
	LPPPMSG_ANS_CRYWOLF_ALTAR_CONTRACT pData = (LPPPMSG_ANS_CRYWOLF_ALTAR_CONTRACT)ReceiveBuffer;
	
	int Key = ((int)(pData->btObjIndexH)<<8) + pData->btObjIndexL; // ���� �ε���
	
	if(pData->bResult == 0)
	{
		g_CharacterUnRegisterBuff((&Hero->Object), eBuff_CrywolfHeroContracted );
		
        int level = CharacterAttribute->Level;
		if(level < 260)
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Dont_Set_Temple1));
			//			M34CryWolf1st::Set_Message_Box(54,0,0);	//"��� �ڰ��� �����մϴ�."
			//			M34CryWolf1st::Set_Message_Box(55,1,0);	//"350���� �̻� ����Ҽ� �ֽ��ϴ�."
		}
		else
		{
			//			M34CryWolf1st::Set_Message_Box(58,0,0);	//"����Ŀ� �ٽýõ����ּ���"
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Wat_Set_Temple1));
		}
	}
	else if(pData->bResult == 1)
	{
		//		M34CryWolf1st::Set_Message_Box(3,0,0);	//������ �Ż��� ��ȣ�ϱ� ���� ������ ��ϵǾ����ϴ�.
		//		M34CryWolf1st::Set_Message_Box(4,1,0);	//������ ������ �ϴ� ���� �����ϼ� �����ϴ�.
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CCry_Wolf_Set_Temple));
		
		M34CryWolf1st::Check_AltarState(Key-316,pData->btAltarState);
		
		g_CharacterRegisterBuff((&Hero->Object), eBuff_CrywolfHeroContracted);
		
		SetAction(&Hero->Object,PLAYER_HEALING_FEMALE1);
		
		SendRequestAction(AT_HEALING1,((BYTE)((Hero->Object.Angle[2]+22.5f)/360.f*8.f+1.f)%8));
	}
}

void ReceiveCrywolfLifeTime ( BYTE* ReceiveBuffer )
//ũ���̿����� ����ð��� �޾ƿ�.
{
    LPPPMSG_ANS_CRYWOLF_LEFTTIME pData = (LPPPMSG_ANS_CRYWOLF_LEFTTIME)ReceiveBuffer;
	
	// �ð�, �� ���� ó��
	M34CryWolf1st::SetTime ( pData->btHour, pData->btMinute );
	g_pCryWolfInterface->SetTime( (int)(pData->btHour), (int)(pData->btMinute) );
}

void ReceiveCrywolfTankerHit ( BYTE* ReceiveBuffer )
{
	//�۾��� - ������
    LPPMSG_NOTIFY_REGION_MONSTER_ATTACK pData = (LPPMSG_NOTIFY_REGION_MONSTER_ATTACK)ReceiveBuffer;
	
    M34CryWolf1st::DoTankerFireFixStartPosition ( pData->btSourceX, pData->btSourceY, pData->btPointX, pData->btPointY );
}

void ReceiveCrywolfBenefitPlusChaosRate( BYTE* ReceiveBuffer )
{
	LPPMSG_ANS_CRYWOLF_BENEFIT_PLUS_CHAOSRATE pData = (LPPMSG_ANS_CRYWOLF_BENEFIT_PLUS_CHAOSRATE)ReceiveBuffer;
	
	g_MixRecipeMgr.SetPlusChaosRate(pData->btPlusChaosRate);
}

void ReceiveCrywolfBossMonsterInfo( BYTE* ReceiveBuffer)
//ũ���̿��� ���� ���� ������ ����
{
	LPPMSG_ANS_CRYWOLF_BOSSMONSTER_INFO pData = (LPPMSG_ANS_CRYWOLF_BOSSMONSTER_INFO)ReceiveBuffer;
	
	M34CryWolf1st::Set_BossMonster(pData->btBossHP,pData->btMonster2);
}

void ReceiveCrywolfPersonalRank( BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_CRYWOLF_PERSONAL_RANK pData = (LPPMSG_ANS_CRYWOLF_PERSONAL_RANK)ReceiveBuffer;
	
	M34CryWolf1st::Set_MyRank(pData->btRank,pData->iGettingExp);
}

void ReceiveCrywolfHeroList( BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO_COUNT pData = (LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO_COUNT)ReceiveBuffer;
	int Offset = sizeof(PMSG_ANS_CRYWOLF_HERO_LIST_INFO_COUNT);
	for ( int i=0; i<pData->btCount; i++ )
	{
		LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO pData2 = (LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO)(ReceiveBuffer+Offset);
		Offset += sizeof(PMSG_ANS_CRYWOLF_HERO_LIST_INFO);
		M34CryWolf1st::Set_WorldRank(pData2->iRank,pData2->btHeroClass,pData2->iHeroScore,pData2->szHeroName);
	}
}

//////////////////////////////////////////////////////////////////////////
//	ĭ���� ����
//////////////////////////////////////////////////////////////////////////
void ReceiveKanturu3rdStateInfo(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_KANTURU_STATE_INFO pData = (LPPMSG_ANS_KANTURU_STATE_INFO)ReceiveBuffer;
	
	g_pKanturu2ndEnterNpc->ReceiveKanturu3rdInfo(pData->btState, pData->btDetailState, pData->btEnter, pData->btUserCount, pData->iRemainTime);
}

void ReceiveKanturu3rdEnterBossMap(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_ENTER_KANTURU_BOSS_MAP pData = (LPPMSG_ANS_ENTER_KANTURU_BOSS_MAP)ReceiveBuffer;
	g_pKanturu2ndEnterNpc->ReceiveKanturu3rdEnter(pData->btResult);
}

void ReceiveKanturu3rdCurrentState( BYTE* ReceiveBuffer)
{
	// ĭ���� ó�� �� ������ ��� ���� �� ���� ����
	LPPMSG_ANS_KANTURU_CURRENT_STATE pData = (LPPMSG_ANS_KANTURU_CURRENT_STATE)ReceiveBuffer;
	M39Kanturu3rd::Kanturu3rdState(pData->btCurrentState, pData->btCurrentDetailState);
	M39Kanturu3rd::CheckSuccessBattle(pData->btCurrentState, pData->btCurrentDetailState);
}

void ReceiveKanturu3rdState( BYTE* ReceiveBuffer)
{
	// ĭ���� �� ���� �� ���� ���� ����
	LPPMSG_ANS_KANTURU_STATE_CHANGE pData = (LPPMSG_ANS_KANTURU_STATE_CHANGE)ReceiveBuffer;
	
	if(M39Kanturu3rd::IsInKanturu3rd())
	{
		if((pData->btState == KANTURU_STATE_MAYA_BATTLE 
			&& (pData->btDetailState == KANTURU_MAYA_DIRECTION_MONSTER1 
			|| pData->btDetailState == KANTURU_MAYA_DIRECTION_MAYA1
			|| pData->btDetailState == KANTURU_MAYA_DIRECTION_MONSTER2
			|| pData->btDetailState == KANTURU_MAYA_DIRECTION_MAYA2
			|| pData->btDetailState == KANTURU_MAYA_DIRECTION_MONSTER3
			|| pData->btDetailState == KANTURU_MAYA_DIRECTION_MAYA3
			))
			|| (pData->btState == KANTURU_STATE_NIGHTMARE_BATTLE
			&& (pData->btDetailState == KANTURU_NIGHTMARE_DIRECTION_BATTLE
			))
			)
		{
			if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_KANTURU_INFO) == false)
			{
				g_pNewUISystem->Show(SEASON3B::INTERFACE_KANTURU_INFO);
			}
		}
		else
		{
			if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_KANTURU_INFO) == true)
			{
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_KANTURU_INFO);
			}
		}
		M39Kanturu3rd::Kanturu3rdState(pData->btState, pData->btDetailState);
		M39Kanturu3rd::CheckSuccessBattle(pData->btState, pData->btDetailState);
	}
}

void ReceiveKanturu3rdResult( BYTE* ReceiveBuffer)
{
	// ĭ���� ���� ���� ���
	LPPMSG_ANS_KANTURU_BATTLE_RESULT pData = (LPPMSG_ANS_KANTURU_BATTLE_RESULT)ReceiveBuffer;
	M39Kanturu3rd::Kanturu3rdResult(pData->btResult);
}

void ReceiveKanturu3rdTimer ( BYTE* ReceiveBuffer )
{
	//  ������(��Ÿ)�� ���� �ð��� ����ڵ鿡�� �ֱ������� �˸�.
    LPPMSG_ANS_KANTURU_BATTLE_SCENE_TIMELIMIT pData = (LPPMSG_ANS_KANTURU_BATTLE_SCENE_TIMELIMIT)ReceiveBuffer;
	g_pKanturuInfoWindow->SetTime(pData->btTimeLimit);
}

void RecevieKanturu3rdMayaSKill( BYTE* ReceiveBuffer)
{
	LPPMSG_NOTIFY_KANTURU_WIDE_AREA_ATTACK pData = (LPPMSG_NOTIFY_KANTURU_WIDE_AREA_ATTACK)ReceiveBuffer;
	M39Kanturu3rd::MayaSceneMayaAction(pData->btType);
}

void RecevieKanturu3rdLeftUserandMonsterCount( BYTE* ReceiveBuffer)
{
	LPPMSG_NOTIFY_KANTURU_USER_MONSTER_COUNT pData = (LPPMSG_NOTIFY_KANTURU_USER_MONSTER_COUNT)ReceiveBuffer;
	M39Kanturu3rd::Kanturu3rdUserandMonsterCount(pData->bMonsterCount, pData->btUserCount);
}

#ifdef ADD_PCROOM_POINT_SYSTEM
//----------------------------------------------------------------------------
// PC�� ����Ʈ �ý���
//----------------------------------------------------------------------------
// PC�� ����Ʈ ������ ����.
void ReceivePCRoomPointInfo(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_GC_PCROOM_POINT_INFO pData = (LPPMSG_ANS_GC_PCROOM_POINT_INFO)ReceiveBuffer;
	
	CPCRoomPtSys& rPCRoomPtSys = CPCRoomPtSys::Instance();

#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
#ifndef CSK_MOD_MOVE_COMMAND_WINDOW		// ������ �� ������ �ϴ� �ҽ�
	rPCRoomPtSys.SetPCRoom();	// �� ��Ŷ�� �޴� �ٸ� PC����.
#endif // CSK_MOD_MOVE_COMMAND_WINDOW	// ������ �� ������ �ϴ� �ҽ�

	// PC�� ����Ʈ ���� �Է�
	rPCRoomPtSys.SetPoint(pData->nPoint, pData->nMaxPoint);
#endif // KJH_DEL_PC_ROOM_SYSTEM

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
	rPCRoomPtSys.SetPCRoom(pData->bPCBang);
#endif // CSK_MOD_MOVE_COMMAND_WINDOW

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0xD0 0x04����[ReceivePCRoomPointInfo(%d | %d)]", pData->nPoint, pData->nMaxPoint);
#endif // CONSOLE_DEBUG
}

#ifndef KJH_DEL_PC_ROOM_SYSTEM			// #ifndef
// PC�� ����Ʈ �������� ���Խ� ����.
void ReceivePCRoomPointUse(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_GC_PCROOM_POINT_USE pData = (LPPMSG_ANS_GC_PCROOM_POINT_USE)ReceiveBuffer;
	
	// ��� 0x00:����, 0x01:�������� �ƴ�, 0x02:�ش���ġ�� �������� ����,
	//0x03:�κ��丮 ���� ����, 0x04:�⺻ ���� ����Ʈ����,
	//0x05:PC�� ����Ʈ �ý��� ����ڰ� �ƴ�, 0x06:����,
	//0x07:���� ��� ���� �ð� �ʰ�, 0x08:PC�� ����Ʈ ���� �������� �ƴ�
	//0x09:���� ������ ����Ʈ ����
	switch (pData->byResult)
	{
	case 0x00:	// ����.
		if (pData->byInvenPos != 0xff)	// ���� ������ �ƴ�.
		{
			// ������ ����.
			g_pMyInventory->InsertItem(pData->byInvenPos-MAX_EQUIPMENT_INDEX, pData->ItemInfo);
			
			PlayBuffer(SOUND_GET_ITEM01);
		}
		break;
		
	case 0x03:
		// 375 "�κ��丮�� ��á���ϴ�."
		g_pChatListBox->AddText("", GlobalText[375], SEASON3B::TYPE_ERROR_MESSAGE);		// "�κ��丮�� �� á���ϴ�."
		break;
					
	case 0x04:
		g_pChatListBox->AddText("", GlobalText[2333], SEASON3B::TYPE_ERROR_MESSAGE);	// "���� ������ Ȯ���ϼ���."
		break;
					
	case 0x09:
		g_pChatListBox->AddText("", GlobalText[2322], SEASON3B::TYPE_ERROR_MESSAGE);		// "����Ʈ�� �����մϴ�."
		break;
	}
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0xD0 0x05����[ReceivePCRoomPointUse(%d)]", pData->byInvenPos);
#endif // CONSOLE_DEBUG	
}

// PC�� ����Ʈ ���� ���� �䱸�� ���� ����.
void ReceivePCRoomPointShopOpen(BYTE* ReceiveBuffer)
{
	LPPMSG_REQ_PCROOM_POINT_SHOP_OPEN pData = (LPPMSG_REQ_PCROOM_POINT_SHOP_OPEN)ReceiveBuffer;
	
	// ���	0:����, 1:�������� �ƴ�, 2:������ ������ ����, 3:�ٸ� â ��� ��, 4:����
	if (0 == pData->byResult)
	{
		CPCRoomPtSys::Instance().SetPCRoomPointShopMode();	// PC�� ����Ʈ ���� �����.
		g_pNewUISystem->Show(SEASON3B::INTERFACE_NPCSHOP);
	}
}
#endif // KJH_DEL_PC_ROOM_SYSTEM

#endif	// ADD_PCROOM_POINT_SYSTEM

void ReceiveCursedTempleEnterInfo( BYTE* ReceiveBuffer )
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CURSED_TEMPLE_USER_COUNT data = (LPPMSG_CURSED_TEMPLE_USER_COUNT)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	g_pCursedTempleEnterWindow->ReceiveCursedTempleEnterInfo( ReceiveBuffer );
}

void ReceiveCursedTempleEnterResult( BYTE* ReceiveBuffer )
{
	LPPMSG_RESULT_ENTER_CURSED_TEMPLE data = (LPPMSG_RESULT_ENTER_CURSED_TEMPLE)ReceiveBuffer;
	//0 : ����, 1 : �˸��� ���� �η縶�� ����, 2 : ���� �ִ� �ð��� �ƴ�, 3 : ���� �η縶���� ������ �ڽ��� ������ ���� ����
	//4 : �ο������� �Ѿ���, 5 : 1�� �������� Ƚ���� �Ѿ���, 6 : ����ᰡ ���ڶ���., 7 : ī�������� ������ �� ����., 8 : ���Ź����� �����ϰ� ������ �� ����.
	if( data->Result == 0 ) 
	{
		g_pNewUISystem->HideAll();
	}
#ifdef PBG_FIX_CURSEDTEMPLE_SYSTEMMSG
	g_CursedTemple->UpdateTempleSystemMsg(data->Result);
#endif //PBG_FIX_CURSEDTEMPLE_SYSTEMMSG
}

void ReceiveCursedTempleInfo( BYTE* ReceiveBuffer )
{
	g_pCursedTempleWindow->ReceiveCursedTempleInfo( ReceiveBuffer );
	g_CursedTemple->ReceiveCursedTempleInfo( ReceiveBuffer );
}

void ReceiveCursedTempMagicResult( BYTE* ReceiveBuffer )
{
	g_pCursedTempleWindow->ReceiveCursedTempRegisterSkill( ReceiveBuffer );
}

void ReceiveCursedTempSkillEnd( BYTE* ReceiveBuffer )
{
	g_pCursedTempleWindow->ReceiveCursedTempUnRegisterSkill( ReceiveBuffer );
}

void ReceiveCursedTempSkillPoint( BYTE* ReceiveBuffer )
{
	g_pCursedTempleWindow->ReceiveCursedTempSkillPoint( ReceiveBuffer );
}

void ReceiveCursedTempleHolyItemRelics( BYTE* ReceiveBuffer )
{
	g_pCursedTempleWindow->ReceiveCursedTempleHolyItemRelics( ReceiveBuffer );
}

void ReceiveCursedTempleGameResult( BYTE* ReceiveBuffer )
{
	g_pNewUISystem->HideAll();
	
	if( g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_CURSEDTEMPLE_GAMESYSTEM ) )
	{
		g_pCursedTempleResultWindow->ResetGameResultInfo();
		g_pCursedTempleResultWindow->SetMyTeam( g_pCursedTempleWindow->GetMyTeam() );
		
		g_pNewUISystem->Hide( SEASON3B::INTERFACE_CURSEDTEMPLE_GAMESYSTEM );
	}
	
	PlayBuffer( SOUND_CURSEDTEMPLE_GAMESYSTEM5 );
	
	g_pNewUISystem->Show( SEASON3B::INTERFACE_CURSEDTEMPLE_RESULT );
	
	g_pCursedTempleResultWindow->ReceiveCursedTempleGameResult(ReceiveBuffer);
}

void ReceiveCursedTempleState( BYTE* ReceiveBuffer )
{
	LPPMSG_ILLUSION_TEMPLE_STATE data = (LPPMSG_ILLUSION_TEMPLE_STATE)ReceiveBuffer;
	
	// 0: wait, 1: wait->ready, 2: ready->play, 3: play->end
	SEASON3A::eCursedTempleState cursedtemple = static_cast<SEASON3A::eCursedTempleState>(data->btIllusionTempleState+1);
	
	if( cursedtemple == SEASON3A::eCursedTempleState_Ready )
	{
		g_pNewUISystem->HideAll();
		
		g_pCursedTempleWindow->ResetCursedTempleSystemInfo();
		g_pCursedTempleWindow->StartTutorialStep();
		
		PlayBuffer( SOUND_CURSEDTEMPLE_GAMESYSTEM1 );
		
		g_pNewUISystem->Show( SEASON3B::INTERFACE_CURSEDTEMPLE_GAMESYSTEM );		
	}
	
	g_CursedTemple->ReceiveCursedTempleState( cursedtemple );
}

#ifdef CSK_RAKLION_BOSS
void ReceiveRaklionStateInfo(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_RAKLION_STATE_INFO pData = (LPPMSG_ANS_RAKLION_STATE_INFO)ReceiveBuffer;
	g_Raklion.SetState(pData->btState, pData->btDetailState);
}

void ReceiveRaklionCurrentState(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_RAKLION_CURRENT_STATE pData = (LPPMSG_ANS_RAKLION_CURRENT_STATE)ReceiveBuffer;
	g_Raklion.SetState(pData->btCurrentState, pData->btCurrentDetailState);
}

void RecevieRaklionStateChange(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_RAKLION_STATE_CHANGE pData = (LPPMSG_ANS_RAKLION_STATE_CHANGE)ReceiveBuffer;
	g_Raklion.SetState(pData->btState, pData->btDetailState);
}

void RecevieRaklionBattleResult(BYTE* ReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_ANS_RAKLION_BATTLE_RESULT pData = (LPPMSG_ANS_RAKLION_BATTLE_RESULT)ReceiveBuffer;	
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}

void RecevieRaklionWideAreaAttack(BYTE* ReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_NOTIFY_RAKLION_WIDE_AREA_ATTACK pData = (LPPMSG_NOTIFY_RAKLION_WIDE_AREA_ATTACK)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}

void RecevieRaklionUserMonsterCount(BYTE* ReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_NOTIFY_RAKLION_USER_MONSTER_COUNT pData = (LPPMSG_NOTIFY_RAKLION_USER_MONSTER_COUNT)ReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
}
#endif // CSK_RAKLION_BOSS

///////////////////////////////////////////////////////////////////////////////
// ��ŷ ����
///////////////////////////////////////////////////////////////////////////////

void ReceiveCheckSumRequest( BYTE *ReceiveBuffer)
{
	LPPHEADER_DEFAULT_WORD Data = (LPPHEADER_DEFAULT_WORD)ReceiveBuffer;
	DWORD dwCheckSum = GetCheckSum( Data->Value);
	SendCheckSum( dwCheckSum );	
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_RECEIVE, "0x03����[ReceiveCheckSumRequest]");
#endif // CONSOLE_DEBUG
}


#ifdef NEW_USER_INTERFACE_SERVERMESSAGE

//////////////////////////////////////////////////////////////////////////
// [ĳ���� ���� ��û ���] 0xF5, 0x02
//////////////////////////////////////////////////////////////////////////
void RecevieCashShopInOut( BYTE* ReceiveBuffer )
{
	TheShopServerProxy().RecevieShopInOut( ReceiveBuffer );
}
//////////////////////////////////////////////////////////////////////////
// [ĳ�� ����Ʈ �ܷ� ��û ���] 0xF5, 0x04
//////////////////////////////////////////////////////////////////////////
void RecevieCashShopCashPoint( BYTE* ReceiveBuffer )
{
	TheShopServerProxy().RecevieShopCashPoint( ReceiveBuffer );
}
//////////////////////////////////////////////////////////////////////////
// [ĳ�� ������ ����Ʈ ��û ���] 0xF5, 0x06
//////////////////////////////////////////////////////////////////////////
void RecevieCashShopItemlist( BYTE* ReceiveBuffer )
{
	TheShopServerProxy().RecevieShopItemlist( ReceiveBuffer );
}
//////////////////////////////////////////////////////////////////////////
// [ĳ���� ���� ��û ���] 0xF5, 0x08
//////////////////////////////////////////////////////////////////////////
void RecevieCashShopItemPurchase( BYTE* ReceiveBuffer )
{
	TheShopServerProxy().RecevieShopItemPurchase( ReceiveBuffer );
}

#ifdef PSW_CHARACTER_CARD
void ReceiveBuyCharacterCard( BYTE* ReceiveBuffer )
{
	TheGameServerProxy().ReceiveBuyCharacterCard( ReceiveBuffer );
}

void ReceiveCharacterCard( BYTE* ReceiveBuffer )
{
	TheGameServerProxy().ReceiveCharacterCard( ReceiveBuffer );
}
#endif //PSW_CHARACTER_CARD

#endif //NEW_USER_INTERFACE_SERVERMESSAGE

void Action(CHARACTER *c,OBJECT *o,bool Now);


extern int TimeRemain;

///////////////////////////////////////////////////////////////////////////////

// �������� ����
///////////////////////////////////////////////////////////////////////////////

BOOL TranslateProtocol( int HeadCode, BYTE *ReceiveBuffer, int Size, BOOL bEcrypted);
void TranslateChattingProtocol(DWORD dwWindowUIID, int HeadCode, BYTE *ReceiveBuffer, int Size, BOOL bEcrypted);

void ProtocolCompiler( CWsctlc *pSocketClient, int iTranslation, int iParam)
{
	//if(CurrentProtocolState >= RECEIVE_JOIN_MAP_SERVER)
	//	return;
	int HeadCode;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Size = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Size;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	while(1)
	{
		BYTE *ReceiveBuffer = pSocketClient->GetReadMsg();
		if( ReceiveBuffer == NULL )
		{
			break;
		}
		else 
		{
#ifdef USE_SELFCHECKCODE
			SendCrcOfFunction( 13, 2, CheckClientArrow, 0xF2A8);
#endif
			BOOL bEncrypted = FALSE;
			BYTE byDec[MAX_SPE_BUFFERSIZE_];
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPBMSG_HEADER lpHeader = (LPPBMSG_HEADER)ReceiveBuffer;
				HeadCode = lpHeader->HeadCode;
				Size     = lpHeader->Size;
			}
			else if( ReceiveBuffer[0] == 0xC2 )
			{
				LPPWMSG_HEADER lpHeader = (LPPWMSG_HEADER)ReceiveBuffer;
				HeadCode = lpHeader->HeadCode;
				Size     = ((int)(lpHeader->SizeH)<<8) + lpHeader->SizeL;
			}
			else if( ReceiveBuffer[0] == 0xC3 || ReceiveBuffer[0] == 0xC4)
			{
				int iSize;
				if ( ReceiveBuffer[0] == 0xC3)
				{
					LPPBMSG_ENCRYPTED lpHeader = (LPPBMSG_ENCRYPTED)ReceiveBuffer;
					Size     = lpHeader->Size;
					// SC �� �ø���

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
					iSize = g_SessionCryptorSC.Decrypt( (int)pSocketClient->GetSocket(), byDec + 2, ReceiveBuffer + 2, Size - 2);
#else // PKD_ADD_ENHANCED_ENCRYPTION
					iSize = g_SimpleModulusSC.Decrypt( byDec + 2, ReceiveBuffer + 2, Size - 2);
#endif // PKD_ADD_ENHANCED_ENCRYPTION				
				}
				else
				{
					LPWBMSG_ENCRYPTED lpHeader = (LPWBMSG_ENCRYPTED)ReceiveBuffer;
					Size     = ((int)(lpHeader->SizeH)<<8) + lpHeader->SizeL;
					// SC �� �ø���
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
					iSize = g_SessionCryptorSC.Decrypt( (int)pSocketClient->GetSocket(), byDec + 2, ReceiveBuffer + 3, Size - 3);
#else // PKD_ADD_ENHANCED_ENCRYPTION
					iSize = g_SimpleModulusSC.Decrypt( byDec + 2, ReceiveBuffer + 3, Size - 3);
#endif // PKD_ADD_ENHANCED_ENCRYPTION
				}
				bEncrypted = TRUE;
				
				if ( iSize < 0)
				{	// �߸��� ��Ŷ
					SendHackingChecked( 0x06, 0);
					g_byPacketSerialRecv++;
					continue;
				}
				
				if ( ( g_byPacketSerialRecv) != byDec[2])
				{
					bEncrypted = FALSE;
					g_byPacketSerialRecv = byDec[2];		//. * ���� �߻� �ǽ��ڵ�
					
					g_ErrorReport.Write("Decrypt error : g_byPacketSerialRecv(0x%02X), byDec(0x%02X)\r\n", g_byPacketSerialRecv, byDec[2]);
					g_ErrorReport.Write("Dump : \r\n");
					g_ErrorReport.HexWrite(ReceiveBuffer, Size);
					g_ErrorReport.Write("\r\n");
					g_ErrorReport.HexWrite(byDec+2, iSize);
				}
				else
				{
					g_byPacketSerialRecv++;
				}
				// ��Ŷ �ϼ�
				if ( ReceiveBuffer[0] == 0xC3)
				{
					LPPBMSG_HEADER pHeader = (LPPBMSG_HEADER)&( byDec[1]);
					pHeader->Code = 0xC1;
					pHeader->Size = ( BYTE)iSize;
					HeadCode = pHeader->HeadCode;
					ReceiveBuffer = (BYTE*)pHeader;
				}
				else
				{
					LPPWMSG_HEADER pHeader = (LPPWMSG_HEADER)byDec;
					pHeader->Code = 0xC2;
					pHeader->SizeH = ( BYTE)( iSize / 256);
					pHeader->SizeL = ( BYTE)( iSize % 256);
					HeadCode = pHeader->HeadCode;
					ReceiveBuffer = (BYTE*)pHeader;
				}
				Size = iSize;
			}
			TotalPacketSize += Size;
#ifdef USE_SELFCHECKCODE
			if ( TimeRemain >= 40)
			{
				SendCrcOfFunction( 7, 17, Action, 0x823F);
			}
#endif
			
#ifdef ACC_PACKETSIZE
			g_iTotalPacketRecv += Size;
#endif
            
#ifdef SAVE_PACKET
			SOCKET socket = pSocketClient->GetSocket();
			
			SOCKADDR_IN sockaddr;
			int isockaddrlen	= sizeof(sockaddr);
			getpeername(socket, (SOCKADDR*)&sockaddr, &isockaddrlen);
			
			std::string timeString;
			leaf::GetTimeString(timeString);
			DebugAngel_Write( PACKET_SAVE_FILE, "%s [%d.%d.%d.%d] Receive ", timeString.c_str(),
				(UCHAR)sockaddr.sin_addr.S_un.S_un_b.s_b1, (UCHAR)sockaddr.sin_addr.S_un.S_un_b.s_b2, 
				(UCHAR)sockaddr.sin_addr.S_un.S_un_b.s_b3, (UCHAR)sockaddr.sin_addr.S_un.S_un_b.s_b4);
			for(int i=0; i<6; i++) {
				DebugAngel_Write( PACKET_SAVE_FILE, "%02X", ReceiveBuffer[i]);
			}
			DebugAngel_Write( PACKET_SAVE_FILE, "\r\n");
#endif
			
#ifdef CONSOLE_DEBUG
			//g_ConsoleDebug->Write(MCD_RECEIVE, "[Receive]HeadCode : %02X, Size : %d", HeadCode, Size);
#endif // CONSOLE_DEBUG
			
			switch ( iTranslation)
			{
			case 1:	// ä�ÿ�
				TranslateChattingProtocol(iParam, HeadCode, ReceiveBuffer, Size, bEncrypted);
				break;
			default:
				if ( !TranslateProtocol( HeadCode, ReceiveBuffer, Size, bEncrypted))
				{	// ��ȣȭ �Ǿ�� �ϴµ� �ȵ� �͵�
					g_ErrorReport.Write( "Strange packet\r\n");
					g_ErrorReport.HexWrite( ReceiveBuffer, Size);
				}
				break;
			}
		}
	}
#ifdef USE_SELFCHECKCODE
	END_OF_FUNCTION( Pos_SelfCheck01);
Pos_SelfCheck01:
	;
#endif
}

#ifdef PJH_CHARACTER_RENAME
void Receive_Change_Name_Result(BYTE *ReceiveBuffer)
{
	LPPMSG_CHANGE_NAME_RESULT Data = (LPPMSG_CHANGE_NAME_RESULT)ReceiveBuffer;
	
	if(Data->btResult == 0) //����
	{
		::strcpy(CharactersClient[SelectedHero].ID, Data->NewName);
		::StartGame(true);
	}
	else
	{
		CUIMng::Instance().PopUpMsgWin(RECEIVE_CREATE_CHARACTER_FAIL);
	}
}

void Receive_Check_Change_Name(BYTE *ReceiveBuffer)
{
	LPPMSG_ANS_CHECK_CHANGE_NAME Data = (LPPMSG_ANS_CHECK_CHANGE_NAME)ReceiveBuffer;
	
	if(Data->btResult == 0)	//ĳ���� �̸��� �ٲ��ʿ䰡 ����.
	{
		::StartGame(true);
	}
	else
		if(Data->btResult == 1)	//ĳ���� �̸��� �ٲ�� �Ѵ�.
		{
			//ĳ���� �̸��ٲٴ� ui�� ����ش�.
			CUIMng& rUIMng = CUIMng::Instance();
			rUIMng.ShowWin(&rUIMng.m_CharMakeWin);
			rUIMng.m_CharMakeWin.Set_State(true);
		}
}
#endif //PJH_CHARACTER_RENAME

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
//////////////////////////////////////////////////////////////////////////
// [����� ���� ����] 0xBF
//////////////////////////////////////////////////////////////////////////

//��ϵ� ���� ���� ����
bool ReceiveRegistedLuckyCoin(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_GET_COIN_COUNT _pData = (LPPMSG_ANS_GET_COIN_COUNT)ReceiveBuffer;
	
	if(_pData->nCoinCnt >= 0)
	{
		//0�̻����� ������ �Դٸ�, ��ϵ� ���� ����
		g_pLuckyCoinRegistration->SetRegistCount(_pData->nCoinCnt);
		return true;
	}
	
	//�̻��� ���� ���Դٸ�
	return false;
}

//���� ��� ����
bool ReceiveRegistLuckyCoin(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_REGEIST_COIN _pData = (LPPMSG_ANS_REGEIST_COIN)ReceiveBuffer;

	g_pLuckyCoinRegistration->UnLockLuckyCoinRegBtn();
	
	switch(_pData->btResult)
	{
	case 0:		// ���� (����� ��������)
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CUseRegistLuckyCoinMsgBoxLayout));
		}break;
	case 1:		// ����
		{
			//���� ��ϵ� ���� ����
			g_pLuckyCoinRegistration->SetRegistCount(_pData->nCurCoinCnt);
		}break;
#ifdef PBG_MOD_LUCKYCOINEVENT
	case 100:
		{
			//��ϵ� ������ 255���� �ʰ��ҽ�
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CRegistOverLuckyCoinMsgBoxLayout));
		}break;
#endif //PBG_MOD_LUCKYCOINEVENT
	default:	// �߸��� Result��
		return false;
	}

	return true;
}

//���� ��ȯ ����
bool ReceiveRequestExChangeLuckyCoin(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_TREADE_COIN _pData = (LPPMSG_ANS_TREADE_COIN)ReceiveBuffer;

	g_pExchangeLuckyCoinWindow->UnLockExchangeBtn();
	
	switch(_pData->btResult)
	{
	case 0:	// ����(����ǵ�����ȯ ��������)
		{
			// ���� �޼��� ó��
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CExchangeLuckyCoinMsgBoxLayout));
		}
		break;
	case 1:	//����
		{
			// ���� �� �κ� ������
			//g_pNewUISystem->Hide(SEASON3B::INTERFACE_EXCHANGE_LUCKYCOIN);
			g_pChatListBox->AddText("", GlobalText[1888], SEASON3B::TYPE_SYSTEM_MESSAGE);
		}break;
	case 2: // ��������
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CExchangeLuckyCoinInvenErrMsgBoxLayout));
		}break;
	default:
		//��Ŷ������ �߸���
		return false;
	}

	return true;
}

#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

#ifdef YDG_ADD_DOPPELGANGER_PROTOCOLS
bool ReceiveEnterDoppelGangerEvent(BYTE* ReceiveBuffer)
{
	LPPMSG_RESULT_ENTER_DOPPELGANGER Data = (LPPMSG_RESULT_ENTER_DOPPELGANGER)ReceiveBuffer;

	unicode::t_char szText[256] = { 0, };

	switch(Data->btResult)
	{
	case 0:		// ����
		break;
	case 1:		// �����Ǹ��� ����
		g_pDoppelGangerWindow->LockEnterButton(TRUE);
		break;
	case 2:		// �̹� �ٸ� ��Ƽ�� �����
		unicode::_sprintf(szText, GlobalText[2864]);
		g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
		g_pDoppelGangerWindow->LockEnterButton(TRUE);
		break;
	case 3:		// ī�������� ������ �� ����.
		unicode::_sprintf(szText, GlobalText[2865]);
		g_pChatListBox->AddText("", szText, SEASON3B::TYPE_ERROR_MESSAGE);
		g_pDoppelGangerWindow->LockEnterButton(TRUE);
		break;
	case 4:		// ���Ź����� �����ϰ� ������ �� ����.
		g_pDoppelGangerWindow->LockEnterButton(FALSE);
		break;
#ifdef KJH_MOD_ENTER_EVENTMAP_ERROR_MSG
	case 5:		// 150���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			char szText[256];
			sprintf(szText, GlobalText[1123], 150);			// "���� 150�̻���� �̿��� �� �ֽ��ϴ�."
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[3028], szText);
		}break;
#endif // KJH_MOD_ENTER_EVENTMAP_ERROR_MSG
	default:	// ��Ŷ������ �߸���
		return false;
	}

	return true;
}

bool ReceiveDoppelGangerMonsterPosition(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_MONSTER_POSITION Data = (LPPMSG_DOPPELGANGER_MONSTER_POSITION)ReceiveBuffer;

	// ��ġ��ȣ(0~22) ���� ���������� 0
	g_pDoppelGangerFrame->SetMonsterGauge((float)Data->btPosIndex / 22.0f);

	return true;
}

bool ReceiveDoppelGangerState(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_STATE Data = (LPPMSG_DOPPELGANGER_STATE)ReceiveBuffer;

	switch(Data->btDoppelgangerState)
	{
	case 0:		// wait
		// ������
		break;
	case 1:		// wait->ready
		// ������
		break;
	case 2:		// ready->play
		{
			// UI ���
			g_pNewUISystem->Show(SEASON3B::INTERFACE_DOPPELGANGER_FRAME);

			// �ȳ� �޽���
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDoppelGangerMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2763], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(" ");
			pMsgBox->AddMsg(GlobalText[2764], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(" ");
			pMsgBox->AddMsg(GlobalText[2765], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}
		break;
	case 3:		// play->end
		// ������
		break;
	}

	return true;
}

bool ReceiveDoppelGangerIcewalkerState(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_ICEWORKER_STATE Data = (LPPMSG_DOPPELGANGER_ICEWORKER_STATE)ReceiveBuffer;

	switch(Data->btIceworkerState)
	{
	case 0:		// ����
		g_pDoppelGangerFrame->SetIceWalkerMap(TRUE, (float)(22 - Data->btPosIndex) / 22.0f);
		break;
	case 1:		// �����
		g_pDoppelGangerFrame->SetIceWalkerMap(FALSE, 0);
		break;
	}

	return true;
}

bool ReceiveDoppelGangerTimePartyState(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_PLAY_INFO Data = (LPPMSG_DOPPELGANGER_PLAY_INFO)ReceiveBuffer;

	// �ð� ����
	g_pDoppelGangerFrame->SetRemainTime(Data->wRemainSec);
	g_pDoppelGangerFrame->SetPartyMemberRcvd();
	LPPMSG_DOPPELGANGER_USER_POS pUserPos = (LPPMSG_DOPPELGANGER_USER_POS)&Data->UserPosData;
	for (int i = 0; i < Data->btUserCount; ++i)
	{
		g_pDoppelGangerFrame->SetPartyMemberInfo(pUserPos[i].wUserIndex, (float)(22 - pUserPos[i].btPosIndex) / 22.0f);
	}

	return true;
}

bool ReceiveDoppelGangerResult(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_RESULT Data = (LPPMSG_DOPPELGANGER_RESULT)ReceiveBuffer;

#ifdef YDG_MOD_DOPPELGANGER_END_SOUND
	PlayBuffer(SOUND_CHAOS_END);
#endif	// YDG_MOD_DOPPELGANGER_END_SOUND

	g_pDoppelGangerFrame->StopTimer(TRUE);
	g_pDoppelGangerFrame->EnabledDoppelGangerEvent(FALSE);

	switch(Data->btResult)
	{
	case 0:		// ����
		{
			// ���� �ð��� 0���� �����Ѵ�
			g_pDoppelGangerFrame->SetRemainTime(0);

			// ���� �޽���
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDoppelGangerMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2769], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(" ");
			pMsgBox->AddMsg(GlobalText[2770], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
// 			pMsgBox->AddMsg(" ");
// 			pMsgBox->AddMsg(" ");
// 			char szText[256] = { 0, };
// 			sprintf(szText, GlobalText[2771], Data->dwRewardExp);
// 			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_BOLD);
		}
		break;
	case 1:		// ����(�׾����_�Ϲ�)
		{
			// ���� �޽���1
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDoppelGangerMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2766], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}
		break;
	case 2:		// ����(������)
		{
			// ���� �޽���2
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CDoppelGangerMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2767], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(" ");
			pMsgBox->AddMsg(GlobalText[2768], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}
		break;
	}

	return true;
}

bool ReceiveDoppelGangerMonsterGoal(BYTE* ReceiveBuffer)
{
	LPPMSG_DOPPELGANGER_MONSTER_GOAL Data = (LPPMSG_DOPPELGANGER_MONSTER_GOAL)ReceiveBuffer;

	// ���ð��� ���� ���� ������ ����
	g_pDoppelGangerFrame->SetMaxMonsters(Data->btMaxGoalCnt);
	g_pDoppelGangerFrame->SetEnteredMonsters(Data->btGoalCnt);

	return true;
}
#endif	// YDG_ADD_DOPPELGANGER_PROTOCOLS

#ifdef YDG_MOD_PROTECT_AUTO_V5
// ���� �� ��� ���� ����
bool ReceiveRequestCheckAutoTool(BYTE* ReceiveBuffer)
{
	LPPMSG_REQ_HACKTOOL_STATISTICS Data = (LPPMSG_REQ_HACKTOOL_STATISTICS)ReceiveBuffer;

	Data->Filename[MAX_HACKTOOL_FILENAME_LENGTH - 1] = '\0';
	BOOL bFindAutoTool = g_pProtectAuto->FindAutoTool(Data->Filename);
	memset(Data->Filename, 0, MAX_HACKTOOL_FILENAME_LENGTH);	// �޸𸮿� ���°��� �������� ����������

	SendRequestCheckAutoToolResult(Data->dwKey, (BYTE)bFindAutoTool);

	return true;
}
#endif	// YDG_MOD_PROTECT_AUTO_V5

#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
// �� �̵� üũ�� ��
bool ReceiveMoveMapChecksum(BYTE* ReceiveBuffer)
{
	LPPMSG_MAPMOVE_CHECKSUM Data = (LPPMSG_MAPMOVE_CHECKSUM)ReceiveBuffer;

	g_pMoveCommandWindow->SetMoveCommandKey(Data->dwKeyValue);
	
	return true;
}

// �� �̵� ���
bool ReceiveRequestMoveMap(BYTE* ReceiveBuffer)
{
	LPPMSG_ANS_MAPMOVE Data = (LPPMSG_ANS_MAPMOVE)ReceiveBuffer;

	if (Data->btResult == 0)
	{
		// �̵� ����
	}
	else
	{
		// �̵� ����
	}

//	������ȣ
// 	MAPMOVE_SUCCESS				= 0,			// �̵� ����
// 	MAPMOVE_FAILED,								// �̵� ���� (�̵� �Ұ����� �ٸ� ���)
// 	MAPMOVE_FAILED_TELEPORT,					// �̵� ���� (�ڷ���Ʈ ��)
// 	MAPMOVE_FAILED_PSHOP_OPEN,					// �̵� ���� (���λ����� �����ִ� ���)
// 	MAPMOVE_FAILED_RECALLED,					// �̵� ���� (��ȯ�Ǵ� ����)
// 	MAPMOVE_FAILED_NOT_ENOUGH_EQUIP,			// �̵� ���� (�ش� ������ �̵��ϱ� ���� ��� ����)
// 	MAPMOVE_FAILED_WEARING_EQUIP,				// �̵� ���� (�ش� �ʿ� ����� ������� ���ϴ� ��� ����)
// 	MAPMOVE_FAILED_MURDERER,					// �̵� ���� (���θ� �� ��� �� �̵� �Ұ�)
// 	MAPMOVE_FAILED_NOT_ENOUGH_LEVEL,			// �̵� ���� (���� ����)
// 	MAPMOVE_FAILED_NOT_ENOUGH_ZEN,				// �̵� ���� (���� �� ����)
// 	MAPMOVE_FORCED_EVENT_END		= 20,		// ���� �̵� (�̺�Ʈ ���ῡ ���� ���� �̵�)
// 	MAPMOVE_FORCED_GM							// ���� �̵� (GM�� ���� ���� �̵�)

	return true;
}
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
bool ReceiveEnterEmpireGuardianEvent(BYTE* ReceiveBuffer)
{
	LPPMSG_RESULT_ENTER_EMPIREGUARDIAN Data = (LPPMSG_RESULT_ENTER_EMPIREGUARDIAN)ReceiveBuffer;
	
	switch(Data->Result)
	{
	case 0:		// 0 : ����
		{
			g_pEmpireGuardianTimer->SetDay((int)Data->Day);
			g_pEmpireGuardianTimer->SetZone((int)Data->Zone);
			g_pEmpireGuardianTimer->SetRemainTime(Data->RemainTick);
			
			// ��� ���� ������ g_EmpireGuardian1���� ó����.
			g_EmpireGuardian1.SetWeather((int)Data->Wheather);
		}break;
	case 1:		// 1 : �̹� ���� ������
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2798], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(" ");
			unicode::t_char szText[256] = {NULL, };
			sprintf(szText,GlobalText[2799], (Data->RemainTick / 60000) );
			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 2:		// 2 : ����Ʈ �������� ����
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2839], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 3:		// 3 : �ο��� �ʰ�
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2841], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 4:		// 4 : �ð��� ��������
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2842], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 5:		// 5 : ��Ƽ �����ϰ�츸 ���尡���մϴ�.
		{
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2843], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
#ifdef KJH_MOD_ENTER_EVENTMAP_ERROR_MSG
	case 6:		// 6: 150���� �̻� �̿밡��
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			char szText[256];
			sprintf(szText, GlobalText[1123], 150);			// "���� 150�̻���� �̿��� �� �ֽ��ϴ�."
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[3028], szText);
		}break;
#endif // KJH_MOD_ENTER_EVENTMAP_ERROR_MSG

	default:	// ��Ŷ������ �߸���
		return false;
	}
	
	return true;
}

bool ReceiveRemainTickEmpireGuardian(BYTE* ReceiveBuffer)
{
	LPPMSG_REMAINTICK_EMPIREGUARDIAN Data =  (LPPMSG_REMAINTICK_EMPIREGUARDIAN)ReceiveBuffer;

	if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER) == false )
	{
		g_pNewUISystem->Show(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER);
	}

	g_pEmpireGuardianTimer->SetType((int)Data->Type);
	g_pEmpireGuardianTimer->SetRemainTime((int)Data->RemainTick);
	g_pEmpireGuardianTimer->SetMonsterCount((int)Data->MonsterCount);

	return true;
}

bool ReceiveResultEmpireGuardian(BYTE* ReceiveBuffer)
{
	LPPMSG_CLEAR_RESULT_EMPIREGUARDIAN Data =  (LPPMSG_CLEAR_RESULT_EMPIREGUARDIAN)ReceiveBuffer;
	
	switch(Data->Result)
	{
	case 0: //����
		{
			//���� ��ȣ�� �似 ������
			//�����Ͽ����ϴ�.
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			pMsgBox->AddMsg(GlobalText[2803], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(GlobalText[2804], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 1: //�� ����
		{
			//���� ��ȣ�� ��� %d��
			//%d�� ����
			int day = g_pEmpireGuardianTimer->GetDay();
			int zone = g_pEmpireGuardianTimer->GetZone();
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			unicode::t_char szText[256] = {NULL, };
			sprintf(szText, GlobalText[2801], day);
			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			sprintf(szText,"%d%s",zone, GlobalText[2840]);
			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	case 2: //�� ����
		{
			//���� ��ȣ�� ��� %d��
			//�Ϸ� �Ͽ����ϴ�.
			//���� ����ġ : %d
			int day = g_pEmpireGuardianTimer->GetDay();
			SEASON3B::CNewUICommonMessageBox* pMsgBox;
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CEmpireGuardianMsgBoxLayout), &pMsgBox);
			unicode::t_char szText[256] = {NULL, };
			sprintf(szText, GlobalText[2801], day);
			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
			pMsgBox->AddMsg(GlobalText[2802], RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
 			sprintf(szText, GlobalText[861], Data->Exp);
 			pMsgBox->AddMsg(szText, RGBA(255, 255, 255, 255), SEASON3B::MSGBOX_FONT_NORMAL);
		}break;
	}

	if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER) == true )
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_EMPIREGUARDIAN_TIMER);
	}
	
	return true;
}
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS

//////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ - �������� ĳ���� ���� ��������
//////////////////////////////////////////////////////////////////////////
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

//----------------------------------------------------------------------------
// ������� ĳ�� ����Ʈ ���� ���� (0xD2)(0x01)
bool ReceiveIGS_CashPoint(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_CASHPOINT_ANS Data =  (LPPMSG_CASHSHOP_CASHPOINT_ANS)pReceiveBuffer;

	g_InGameShopSystem->SetTotalCash((double)Data->dTotalCash);
	g_InGameShopSystem->SetTotalPoint((double)Data->dTotalPoint);
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	g_InGameShopSystem->SetCashCreditCard((double)Data->dCashCredit);
	g_InGameShopSystem->SetCashPrepaid((double)Data->dCashPrepaid);	
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	g_InGameShopSystem->SetTotalMileage((double)Data->dTotalMileage);

	return true;
}

//----------------------------------------------------------------------------
// ĳ���� Open ��� (0xD2)(0x02)
bool ReceiveIGS_ShopOpenResult(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_SHOPOPEN_ANS Data = (LPPMSG_CASHSHOP_SHOPOPEN_ANS)pReceiveBuffer;

	g_InGameShopSystem->SetIsRequestShopOpenning(false);	

	if( (BYTE)Data->byShopOpenResult == 0 )
	{
		// ���� ������ �޼���â
		return false;
	}

	SendRequestIGS_CashPointInfo();			// ������� ĳ�� ����Ʈ ���� ��û
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	char szCode = g_pInGameShop->GetCurrentStorageCode();
	SendRequestIGS_ItemStorageList(1, &szCode);		// ������ ����Ʈ ��û
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	SendRequestIGS_ItemStorageList();		// ������ ����Ʈ ��û
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// �ΰ��Ӽ� Open
	g_pNewUISystem->Show(SEASON3B::INTERFACE_INGAMESHOP);			
	
	return true;
}

//----------------------------------------------------------------------------
// ������ ���� ��� (0xD2)(0x03)
bool ReceiveIGS_BuyItem(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_BUYITEM_ANS Data = (LPPMSG_CASHSHOP_BUYITEM_ANS)pReceiveBuffer;

	switch( (BYTE)Data->byResultCode)
	{
	case -2: // DB���ٽ���
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2953]);
		}
		break;
	case -1: // DB����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2954]);
		}
		break;
	case 0: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2900], GlobalText[2901]);

			SendRequestIGS_CashPointInfo();		// ������� ĳ�� ����Ʈ ���� ��û

#ifdef KJH_FIX_BTS179_INGAMESHOP_STORAGE_UPDATE_WHEN_ITEM_BUY
			char szCode = g_pInGameShop->GetCurrentStorageCode();
			SendRequestIGS_ItemStorageList(1, &szCode);		// ������ ����Ʈ ��û
#endif // KJH_FIX_BTS179_INGAMESHOP_STORAGE_UPDATE_WHEN_ITEM_BUY
		}
		break;
	case 1: // ���� ĳ�� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2903]);
		}
		break;
	case 2:	// ������� ��ǰ ���� �Ұ���
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2904]);
		}
		break;
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
	case 3: // �ܿ� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2956]);
		}
		break;
	case 4: // �ǸűⰣ ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2957]);
		}
		break;
	case 5: // �Ǹ� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2958]);
		}
		break; 
	case 6:	// ���� �Ұ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "�����ϱ� ����" "���� �Ұ����� ��ǰ�Դϴ�."
			pMsgBox->Initialize(GlobalText[2902], GlobalText[3052]);
		}break;
	case 7:	// �̺�Ʈ ��ǰ ���� �Ұ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "�����ϱ� ����" "�̺�Ʈ��ǰ�� ���� �Ұ��� �մϴ�."
			pMsgBox->Initialize(GlobalText[2902], GlobalText[3053]);
		}break;
	case 8:	// �̺�Ʈ ��ǰ ���� Ƚ�� �ʰ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "�����ϱ� ����" "�̺�Ʈ��ǰ ���� Ƚ���� �ʰ� �Ͽ����ϴ�."
			pMsgBox->Initialize(GlobalText[2902], GlobalText[3054]);
		}break;
#else // KJH_MOD_INGAMESHOP_PATCH_091028
	case 4: // �ܿ� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2956]);
		}
		break;
	case 5: // �Ǹ� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[2958]);
		}
		break; 
	case 6:	// ��ǰ������ ����.
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[2958]);
		}break;
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	case 9: // �߸��� ĳ��Ÿ��
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2902], GlobalText[3264]);
		}
		break;
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	default:	// �� �� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[890]);		
		}
		break;
	}

	return true;
}

//----------------------------------------------------------------------------
// ������ ���� ��� (0xD2)(0x04)
bool ReceiveIGS_SendItemGift(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_GIFTSEND_ANS Data = (LPPMSG_CASHSHOP_GIFTSEND_ANS)pReceiveBuffer;

	switch( (BYTE)Data->byResultCode)
	{
	case -2: // DB���ٽ���
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2953]);
		}
		break;
	case -1: // DB����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2954]);
		}
		break;
	case 0: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2910], GlobalText[2911]);

			SendRequestIGS_CashPointInfo();		// ������� ĳ�� ����Ʈ ���� ��û
		}
		break;
	case 1: // ���� ĳ�� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2913]);
		}
		break;
	case 2:	// ������� ��ǰ ���� �Ұ���
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2914]);
		}
		break;
	case 3: // ������� �����ϱ� �ѵ� �ʰ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2915]);
		}
		break;
	case 4: // �ܿ� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2956]);
		}
		break;
	case 5: // �Ǹ� �Ⱓ ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2958]);
		}
		break; 
	case 6:	// ��ǰ������ ����.
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[2958]);
		}break;
	case 7: // ��ǰ ���� �Ұ���
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
#ifdef PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2959]);
#else //PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[1912], GlobalText[2959]);
#endif //PBG_FIX_MSGTITLENUM
		}
		break;
	case 8: // �̺�Ʈ��ǰ �����Ұ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
#ifdef PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2960]);
#else //PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[1912], GlobalText[2960]);
#endif //PBG_FIX_MSGTITLENUM
		}
		break;
	case 9: // �̺�Ʈ��ǰ �������� Ƚ�� �ʰ�
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
#ifdef PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[2912], GlobalText[2961]);
#else //PBG_FIX_MSGTITLENUM
			pMsgBox->Initialize(GlobalText[1912], GlobalText[2961]);
#endif //PBG_FIX_MSGTITLENUM
		}
		break;
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	case 10: // �߸��� ĳ��Ÿ��
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[3264]);
		}
		break;
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#ifdef KJH_FIX_BTS207_INGAMESHOP_SEND_GIFT_ERRORMSG_INCORRECT_ID
	case 20: // ������ ���̵� ������
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2912], GlobalText[3263]);
		}
		break;
#endif // KJH_FIX_BTS207_INGAMESHOP_SEND_GIFT_ERRORMSG_INCORRECT_ID
	default:	// �� �� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[890]);
		}
		break;
	}
	
	return true;
}

//----------------------------------------------------------------------------
// ������ ����Ʈ ī��Ʈ ���� (0xD2)(0x06)
bool ReceiveIGS_StorageItemListCount(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_STORAGECOUNT Data = (LPPMSG_CASHSHOP_STORAGECOUNT)pReceiveBuffer;

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_pInGameShop->InitStorage((int)Data->wTotalItemCount, (int)Data->wCurrentItemCount, (int)Data->wTotalPage, (int)Data->wPageIndex);
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_InGameShopSystem->SetStorageItemCnt((WORD)Data->wItemCount);
	g_pInGameShop->ClearAllStorageItem();
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	
	return true;
}

//----------------------------------------------------------------------------
// ������ ����Ʈ ���� (0xD2)(0x0D)
bool ReceiveIGS_StorageItemList(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_STORAGELIST Data = (LPPMSG_CASHSHOP_STORAGELIST)pReceiveBuffer;

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	if( g_InGameShopSystem->IsShopOpen() == false )
		return false;
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_pInGameShop->AddStorageItem((int)Data->lStorageIndex, (int)Data->lItemSeq, (int)Data->lStorageGroupCode,
									(int)Data->lProductSeq, (int)Data->lPriceSeq, (int)Data->dCashPoint, (char)Data->chItemType);
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_pInGameShop->AddStorageItem(CInGameShopSystem::IGS_SAFEKEEPING_LISTBOX, (int)Data->lStorageIndex, 
									(int)Data->lItemSeq, (int)Data->lStorageGroupCode, (int)Data->lProductSeq, 
									(int)Data->lPriceSeq, (int)Data->dCashPoint, (char)Data->chItemType);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	return true;
}

//----------------------------------------------------------------------------
// ������ ����Ʈ ���� (0xD2)(0x0E)
bool ReceiveIGS_StorageGiftItemList(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_GIFTSTORAGELIST Data = (LPPMSG_CASHSHOP_GIFTSTORAGELIST)pReceiveBuffer;

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	if( g_InGameShopSystem->IsShopOpen() == false )
		return false;
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

	unicode::t_char szID[MAX_ID_SIZE+1];
	unicode::t_char szMessage[MAX_GIFT_MESSAGE_SIZE];

	strncpy(szID, (unicode::t_char*)Data->chSendUserName, MAX_ID_SIZE+1);
	strncpy(szMessage, (unicode::t_char*)Data->chMessage, MAX_GIFT_MESSAGE_SIZE);
	szID[MAX_ID_SIZE] = '\0';
	szMessage[MAX_GIFT_MESSAGE_SIZE-1] = '\0';
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_pInGameShop->AddStorageItem( (int)Data->lStorageIndex, (int)Data->lItemSeq, (int)Data->lStorageGroupCode, (int)Data->lProductSeq, 
									(int)Data->lPriceSeq, (int)Data->dCashPoint, (char)Data->chItemType, szID, szMessage);
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	g_pInGameShop->AddStorageItem(CInGameShopSystem::IGS_PRESENTBOX_LISTBOX, (int)Data->lStorageIndex, 
									(int)Data->lItemSeq, (int)Data->lStorageGroupCode, (int)Data->lProductSeq, 
									(int)Data->lPriceSeq, (int)Data->dCashPoint, (char)Data->chItemType, szID, szMessage);
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	
	return true;
}

//----------------------------------------------------------------------------
// ĳ������ ��� (0xD2)(0x07)
bool ReceiveIGS_SendCashGift(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CASHSHOP_CASHSEND_ANS Data = (LPPMSG_CASHSHOP_CASHSEND_ANS)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	return true;
}

//----------------------------------------------------------------------------
// �ش� ����ڰ� ��ǰ�� ����/������ �������� Ȯ�� ��� (0xD2)(0x08)
bool ReceiveIGS_PossibleBuy(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CASHSHOP_ITEMBUY_CONFIRM_ANS Data = (LPPMSG_CASHSHOP_ITEMBUY_CONFIRM_ANS)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	return true;
}

//----------------------------------------------------------------------------
// ��ǰ �ܿ� ���� ��ȸ ��� (0xD2)(0x09)
bool ReceiveIGS_LeftCountItem(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_ANS Data = (LPPMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_ANS)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	return true;
}

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
//----------------------------------------------------------------------------
// ������ ������ ������ ��� (0xD2)(0x0A)
bool ReceiveIGS_DeleteStorageItem(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_STORAGE_ITEM_THROW_ANS Data = (LPPMSG_CASHSHOP_STORAGE_ITEM_THROW_ANS)pReceiveBuffer;

	switch( (BYTE)Data->byResult)
	{
	case -2: // DB����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2935], GlobalText[2967]);
		}
		break;
	case -1: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2935], GlobalText[2966]);
		}
		break;
	case 0: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2933], GlobalText[2934]);

			g_pInGameShop->DelStorageSelectedItem();		// ���� ���õ� �������� Item�� �����.
		}
		break;
	case 1: // ������ ������ �׸��� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2935], GlobalText[2936]);
		}
		break;
	default:	// �� �� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[890]);		
		}
		break;
	}
	
	return true;
}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

//----------------------------------------------------------------------------
// ������ ������ ��� ��� (0xD2)(0x0B)
bool ReceiveIGS_UseStorageItem(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_STORAGE_ITEM_USE_ANS Data = (LPPMSG_CASHSHOP_STORAGE_ITEM_USE_ANS)pReceiveBuffer;
	
	switch( (BYTE)Data->byResult )
	{
	case -2: // DB����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2967]);
		}
		break;
	case -1: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2966]);
		}
		break;	
	case 0: // ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2924], GlobalText[2925]);

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
			g_pInGameShop->UpdateStorageItemList();			// ������ ������ ����Ʈ ����
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
			g_pInGameShop->DelStorageSelectedItem();		// ���� ���õ� �������� Item�� �����.
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		}
		break;
	case 1: // ������ ����ϱ� �׸��� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2962]);
		}
		break;
	case 2:	// PC�濡���� �ޱ� ������ ������
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2963]);
		}
		break;
	case 3: // �Ⱓ �� ������� �÷� ����� �ִ°��
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2964]);
		}
		break;
	case 4: // �Ⱓ�� ������� ���� ���� ����� �ִ°��
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2965]);
		}break;
	case 21:	// �κ��丮 ������ �����մϴ�.
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2284]);
		}
		break;
	case 22:	// �ش�������� ����� �� �����ϴ�. (ĳ����ī��/ĳ���ͽ��Ծ����� ��� �Ϸ�)
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "����", "�ش�������� ����� �� �����ϴ�"
			pMsgBox->Initialize(GlobalText[2928], GlobalText[3036]);
		}
		break;
#ifdef LEM_FIX_SERVERMSG_SEALITEM	// ���� Ÿ���� ������ ������Դϴ�. [lem.2010.7.28]
	case 24:
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			// "����", "�ش�������� ����� �� �����ϴ�"
			pMsgBox->Initialize(GlobalText[2928], GlobalText[2610]);
		}
		break;
#endif	// LEM_FIX_SERVERMSG_SEALITEM
	default:	// �� �� ���� ����
		{
			CMsgBoxIGSCommon* pMsgBox = NULL;
			CreateMessageBox(MSGBOX_LAYOUT_CLASS(CMsgBoxIGSCommonLayout), &pMsgBox);
			pMsgBox->Initialize(GlobalText[2945], GlobalText[890]);		
		}
		break;
	}
	return true;
}

//----------------------------------------------------------------------------
// ��ũ��Ʈ ������Ʈ (0xD2)(0x0C)
bool ReceiveIGS_UpdateScript(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CASHSHOP_VERSION_UPDATE Data = (LPPMSG_CASHSHOP_VERSION_UPDATE)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
#ifdef _DEBUG
	// �系 �׽�Ʈ���� ��ũ��Ʈ�� �ٿ�ε� ������ �����Ƿ� ���� ��ũ��Ʈ ó��
	g_InGameShopSystem->SetScriptVersion(512, 0, 0);
#else // _DEBUG
	g_InGameShopSystem->SetScriptVersion(Data->wSaleZone, Data->wYear, Data->wYearIdentify);
#endif // _DEBUG

	g_InGameShopSystem->ShopOpenUnLock();
#else // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	// ������ �ݰ�, Release()
	if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == true )
	{
		SendRequestIGS_CashShopOpen(1);		// �� Close��û
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_INGAMESHOP);
	}

	g_InGameShopSystem->Release();
	
#ifdef _DEBUG
	// �系 �׽�Ʈ���� ��ũ��Ʈ�� �ٿ�ε� ������ �����Ƿ� ���� ��ũ��Ʈ ó��
	g_InGameShopSystem->SetScriptVersion(512, 0, 0);
#else // _DEBUG
 	g_InGameShopSystem->SetScriptVersion(Data->wSaleZone, Data->wYear, Data->wYearIdentify);
#endif // _DEBUG

	if( g_InGameShopSystem->ScriptDownload() == false )
	{
		return false;
	}

	g_InGameShopSystem->Initalize();
	
	g_pInGameShop->InitZoneBtn();
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

	return true;
}

//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ ī��Ʈ (0xD2)(0x13)
bool ReceiveIGS_EventItemlistCnt(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_EVENTITEM_COUNT Data = (LPPMSG_CASHSHOP_EVENTITEM_COUNT)pReceiveBuffer;

	g_InGameShopSystem->InitEventPackage((int)Data->wEventItemListCount);
	
	return true;
}

//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ (0xD2)(0x14)
bool ReceiveIGS_EventItemlist(BYTE* pReceiveBuffer)
{
	LPPMSG_CASHSHOP_EVENTITEM_LIST Data = (LPPMSG_CASHSHOP_EVENTITEM_LIST)pReceiveBuffer;
	
#ifdef KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
		g_InGameShopSystem->InsertEventPackage((int*)Data->lPackageSeq);
#else // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
	for( int i=0 ; i<INGAMESHOP_DISPLAY_ITEMLIST_SIZE ; i++ )
	{
		g_InGameShopSystem->InsertEventPackage((int)Data->lPackageSeq[i]);
	}
#endif // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE

	return true;
}

//----------------------------------------------------------------------------
// ��� ���� ������Ʈ (0xD2)(0x15)
bool ReceiveIGS_UpdateBanner(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_CASHSHOP_BANNER_UPDATE Data = (LPPMSG_CASHSHOP_BANNER_UPDATE)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
#ifdef _DEBUG
	// �系 �׽�Ʈ���� ��ũ��Ʈ�� �ٿ�ε� ������ �����Ƿ� ���� ��ũ��Ʈ ó��
	g_InGameShopSystem->SetBannerVersion(583, 0, 0);
#else // _DEBUG
	g_InGameShopSystem->SetBannerVersion(Data->wBannerZone, Data->wYear, Data->wYearIdentify);
#endif // _DEBUG
#else // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	if( g_InGameShopSystem->IsShopOpen() == false )
		return false;
	
#ifdef _DEBUG
	// �系 �׽�Ʈ���� ��ũ��Ʈ�� �ٿ�ε� ������ �����Ƿ� ���� ��ũ��Ʈ ó��
	g_InGameShopSystem->SetBannerVersion(583, 0, 0);
#else // _DEBUG
	g_InGameShopSystem->SetBannerVersion(Data->wBannerZone, Data->wYear, Data->wYearIdentify);
#endif // _DEBUG

	if( g_InGameShopSystem->BannerDownload() == false )
	{
		return false;
	}

	// ��� 
	g_pInGameShop->InitBanner(g_InGameShopSystem->GetBannerFileName(), g_InGameShopSystem->GetBannerURL());
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

	return true;
}

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#ifdef PBG_ADD_SECRETBUFF
bool ReceiveFatigueTime(BYTE* pReceiveBuffer)
{
	LPPMSG_FATIGUEPERCENTAGE Data = (LPPMSG_FATIGUEPERCENTAGE)pReceiveBuffer;

	// �Ƿε� �ۼ��������� ������ �޴´� 1������->100%
	if(g_FatigueTimeSystem->SetFatiguePercentage(Data->btFatiguePercentage))
	{
		// �Ƿε� �ý����� �����ϴ� ������
		g_FatigueTimeSystem->SetIsFatigueSystem(true);
#ifdef PBG_MOD_STAMINA_UI
		g_pNewUIStamina->SetCaution(Data->btFatiguePercentage);
#endif //PBG_MOD_STAMINA_UI
		return true;
	}
	else
		return false;

	return false;
}
#endif //PBG_ADD_SECRETBUFF

#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
//----------------------------------------------------------------------------
// �κ� ������ ���� ��� ���� (0xBF)(0x20)
// Data->btResult: 254 - ����, 255 - ����
//----------------------------------------------------------------------------
bool ReceiveEquippingInventoryItem(BYTE* pReceiveBuffer)
{
	LPPMSG_ANS_INVENTORY_EQUIPMENT_ITEM Data = (LPPMSG_ANS_INVENTORY_EQUIPMENT_ITEM)pReceiveBuffer;

	int iResult	 = (int)Data->btResult;
	int iItemPos = (int)Data->btItemPos;
	iItemPos -= MAX_EQUIPMENT_INDEX;
	
	// �������� ��(254-����, 255-����)�� �ƴϸ� return false
	if (!(iResult == 254 || iResult == 255))
		return false;
	// ���������� �������� ��ġ 
	if (iItemPos < 0 || iItemPos >= MAX_INVENTORY)
		return false;
	
	// ������� �������� ������ 254, ������������ ������ 255
	ITEM* pItem = g_pMyInventory->FindItem(iItemPos);
	pItem->Durability = iResult;
	
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "[0xBF][0x20]���� [ReceiveEquippingInventoryItem]");
#endif // CONSOLE_DEBUG

	return true;
}
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY


#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
//----------------------------------------------------------------------------
// �Ⱓ�� ������ ����Ʈ ī��Ʈ (0xD2)(0x11)
bool ReceivePeriodItemListCount(BYTE* pReceiveBuffer)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	LPPMSG_PERIODITEMEX_ITEMCOUNT Data = (LPPMSG_PERIODITEMEX_ITEMCOUNT)pReceiveBuffer;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	return true;
}

//----------------------------------------------------------------------------
// �Ⱓ�� ������ ����Ʈ (0xD2)(0x12)
bool ReceivePeriodItemList(BYTE* pReceiveBuffer)
{
	LPPMSG_PERIODITEMEX_ITEMLIST Data = (LPPMSG_PERIODITEMEX_ITEMLIST)pReceiveBuffer;

	if(Data->wItemSlotIndex < MAX_EQUIPMENT_INDEX)		//. ����
	{
		CharacterMachine->Equipment[Data->wItemSlotIndex].lExpireTime = (long)Data->lExpireDate;
	}
	else	// �κ�
	{
		ITEM* pItem = g_pMyInventory->FindItem(Data->wItemSlotIndex-MAX_EQUIPMENT_INDEX);

		if( pItem == NULL )
			return false;

		pItem->lExpireTime = (long)Data->lExpireDate;
	}

	return true;
}
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM

#ifdef PBG_MOD_GAMEGUARD_HANDLE
bool ReceiveGameGuardCharInfo(BYTE* pReceiveBuffer)
{
	LPPMSG_GAMEGUARD_HADLE Data = (LPPMSG_GAMEGUARD_HADLE)pReceiveBuffer;

	return true;
}
#endif //PBG_MOD_GAMEGUARD_HANDLE

#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
bool ReceiveSkillDummySeedValue(BYTE* pReceiveBuffer)
{
	LPPMSG_SET_ATTACK_PROTOCOL_DUMMY_VALUE Data = (LPPMSG_SET_ATTACK_PROTOCOL_DUMMY_VALUE)pReceiveBuffer;
	
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	g_DummyAttackChecker->Initialize((DWORD)Data->dwDummySeedValue, (DWORD)Data->dwAttackSerialSeedValue);
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	g_DummyAttackChecker->Initialize((DWORD)Data->dwDummySeedValue);
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL

	return true;
}
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL

#ifdef LJH_ADD_ONETIME_PASSWORD
void ShowOTPInputWin()
{
	CUIMng& rUIMng = CUIMng::Instance();
	
	rUIMng.ShowWin(&rUIMng.m_OneTimePasswordWin);		// OneTime Password �Է�â�� ������
}
#endif //LJH_ADD_ONETIME_PASSWORD

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
BOOL ReceiveStraightAttack(BYTE *ReceiveBuffer, int Size, BOOL bEncrypted)
{
	if(!bEncrypted)
	{
		GO_DEBUG;
		SendHackingChecked(0x00, 0x4A);
		return (FALSE);
	}
	
	LPPRECEIVE_STRAIGHTATTACK Data = (LPPRECEIVE_STRAIGHTATTACK)ReceiveBuffer;
	int SourceKey = ((int)(Data->SourceKeyH)<<8) + Data->SourceKeyL;
	int TargetKey = ((int)(Data->TargetKeyH)<<8) + Data->TargetKeyL;
	int Success = (TargetKey>>15);

	WORD AttackNumber = ((WORD)(Data->AttackH)<<8) + Data->AttackL;
	
	TargetKey &= 0x7FFF;
	int Index       = FindCharacterIndex(SourceKey);
	int TargetIndex = FindCharacterIndex(TargetKey);
	if(TargetIndex == MAX_CHARACTERS_CLIENT && AttackNumber != AT_SKILL_DARKSIDE)
		return (TRUE);
	
	AttackPlayer = Index;
	CHARACTER *sc = &CharactersClient[Index];
	CHARACTER *tc = &CharactersClient[TargetIndex];
	OBJECT *so = &sc->Object;
	OBJECT *to = &tc->Object;

	if(sc!=Hero && to->Visible)
		so->Angle[2] = CreateAngle(so->Position[0],so->Position[1],to->Position[0],to->Position[1]);

	sc->TargetCharacter = TargetIndex;
		
	sc->SkillSuccess = (Success != 0);
	sc->Skill = AttackNumber;

	so->m_sTargetIndex = TargetIndex;

	if(g_CMonkSystem.IsRageHalfwaySkillAni(AttackNumber))
	{
		if(sc!=Hero && AttackNumber == AT_SKILL_STAMP)
		{
			g_CMonkSystem.SetRageSkillAni(AttackNumber, so);
			g_CMonkSystem.RageCreateEffect(so, AttackNumber);
		}
		else if(AttackNumber != AT_SKILL_STAMP)
		{
			g_CMonkSystem.SetRageSkillAni(AttackNumber, so);
		}
		sc->AttackTime = 1;
	}

	switch(AttackNumber)
	{
	case AT_SKILL_DARKSIDE:
		{
			if(sc != Hero)
				g_CMonkSystem.RageCreateEffect(so, AttackNumber);

			g_CMonkSystem.SetRageSkillAni(AttackNumber, so);
			sc->AttackTime = 1;
		}
		break;
	}

	return (TRUE);
}

void ReceiveDarkside(BYTE* ReceiveBuffer)
{
	LPPRECEIVE_DARKSIDE_INDEX Data = (LPPRECEIVE_DARKSIDE_INDEX)ReceiveBuffer;
	
	if(Data->MagicNumber == AT_SKILL_DARKSIDE)
	{
		g_CMonkSystem.InitDarksideTarget();
		g_CMonkSystem.SetDarksideTargetIndex(Data->TargerIndex);
	}
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

//////////////////////////////////////////////////////////////////////////
// TranslateProtocol
//////////////////////////////////////////////////////////////////////////
BOOL TranslateProtocol( int HeadCode, BYTE *ReceiveBuffer, int Size, BOOL bEncrypted)
{
	switch( HeadCode )
	{
	case 0xF1:     			
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch( Data->SubCode )
			{
			case 0x00: //receive join server
                ReceiveJoinServer(ReceiveBuffer);
				break;
			case 0x01: //receive log in
                //AddDebugText(ReceiveBuffer,Size);
#ifdef LEM_ADD_GAMECHU
		#ifdef FOR_WORK
				g_ErrorReport.Write("\n\n!!!---- RECEIVE PACKET LOGINT : %d -------\n\n", Data->Value);				
		#endif // FOR_WORK
#endif // LEM_ADD_GAMECHU
				
				switch(Data->Value)
				{
				case 0x20:
					CurrentProtocolState = RECEIVE_LOG_IN_SUCCESS;
					LogIn = 2;
					m_pc_wanted = true;
                    CheckHack();
					break;
				case 0x00:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_PASSWORD);
					break;
				case 0x01:
					CurrentProtocolState = RECEIVE_LOG_IN_SUCCESS;
					LogIn = 2;
                    CheckHack();
					break;
				case 0x02:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_ID);
					break;
				case 0x03:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_ID_CONNECTED);
					break;
				case 0x04:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_SERVER_BUSY);
					break;
				case 0x05:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_ID_BLOCK);
					break;
				case 0x06:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_VERSION);
					g_ErrorReport.Write( "Version dismatch. - Login\r\n");
					break;
				case 0x07:
				default:	// ����
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_CONNECT);
					break;
				case 0x08:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_ERROR);
					break;
				case 0x09:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_NO_PAYMENT_INFO);
					break;
				case 0x0a:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_USER_TIME1);
					break;
				case 0x0b:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_USER_TIME2);
					break;
				case 0x0c:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_PC_TIME1);
					break;
				case 0x0d:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_PC_TIME2);
					break;
				case 0x11:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_ONLY_OVER_15);
					break;
#ifdef LEM_ADD_GAMECHU	// ������ �α��� �õ��� �߸��� ������ ���� ���� ���� ����.
				case 0x12:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_CONNECT);
					break;
#endif // LEM_ADD_GAMECHU
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
				case 0x40:	// ����ä�� ���� �Ұ�.(�۷ι� ����)
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_CHARGED_CHANNEL);
					break;
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
				case 0xc0:
				case 0xd0:	// �븸 ����
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_POINT_DATE);
					break;
				case 0xc1:
				case 0xd1:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_POINT_HOUR);
					break;
				case 0xc2:
				case 0xd2:
					CUIMng::Instance().PopUpMsgWin(RECEIVE_LOG_IN_FAIL_INVALID_IP);
					break;
#ifdef ADD_EXPERIENCE_SERVER
				case 0xb0:	// PC�濡���� ���� ����.
					CUIMng::Instance().PopUpMsgWin(MESSAGE_PCROOM_POSSIBLE);
					break;
#endif	// ADD_EXPERIENCE_SERVER
#ifdef LJH_ADD_ONETIME_PASSWORD
				//(0xF1 / 0x01, 0xA0): OTP ��� ����
				case 0xA0:
					ShowOTPInputWin();
					break;
				//(0xF1 / 0x01, 0xA1): OTP �̵�� ����
				case 0xA1:	
					g_ErrorReport.Write( "this user not register OPT yet.");
					g_ErrorReport.WriteCurrentTime();
					CUIMng::Instance().PopUpMsgWin(MESSAGE_OTP_NOT_REGISTERED);
					break;
				//(0xF1 / 0x01, 0xA2): OTP ����ġ
				case 0xA2:	
					g_ErrorReport.Write( "Incorrect OneTime Password.");
					g_ErrorReport.WriteCurrentTime();
					CUIMng::Instance().PopUpMsgWin(MESSAGE_OTP_INCORRECT);
					break;
				//(0xF1 / 0x01, 0xA3): ���������� byOTPBtnType���� ���´ٴ� ������ ����  
				//(0xF1 / 0x01, 0xA4): ��ȿ�Ⱓ�� ���� OneTime Password
				case 0xA3:
				case 0xA4:
					g_ErrorReport.Write( "Invalid information received.");
					g_ErrorReport.WriteCurrentTime();
					CUIMng::Instance().PopUpMsgWin(MESSAGE_OTP_INVALID_INFO);
#endif //LJH_ADD_ONETIME_PASSWORD
				}
				break;
				case 0x02:
					if ( !ReceiveLogOut(ReceiveBuffer, bEncrypted))
					{
						return ( FALSE);
					}
					break;
				case 0x12: //0x02 receive create account
					switch(Data->Value)
					{
					case 0x00:
						CurrentProtocolState = RECEIVE_CREATE_ACCOUNT_FAIL_ID;
						break;
					case 0x01:
						CurrentProtocolState = RECEIVE_CREATE_ACCOUNT_SUCCESS;
						break;
					case 0x02:
						CurrentProtocolState = RECEIVE_CREATE_ACCOUNT_FAIL_RESIDENT;
						break;
					}
					break;
					case 0x03: //receive confirm password
						//AddDebugText(ReceiveBuffer,Size);
						ReceiveConfirmPassword(ReceiveBuffer);
						break;
					case 0x04: //receive confirm password
						//AddDebugText(ReceiveBuffer,Size);
						ReceiveConfirmPassword2(ReceiveBuffer);
						break;
					case 0x05: //receive change password
						ReceiveChangePassword(ReceiveBuffer);
						break;
			}
			break;
		}
	case 0xF3:     			
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_RECEIVE, "[0xF3][0x%02x]����", subcode);
#endif // CONSOLE_DEBUG
			
			switch( subcode )
			{
			case 0x00: //receive characters list
                ReceiveCharacterList(ReceiveBuffer);
				break;
			case 0x01: //receive create character
                ReceiveCreateCharacter(ReceiveBuffer);
				break;
			case 0x02: //receive delete character
                ReceiveDeleteCharacter(ReceiveBuffer);
				break;
			case 0x03: //receive join map server
                if ( !ReceiveJoinMapServer(ReceiveBuffer, bEncrypted))
				{
					return ( FALSE);
				}
				break;
			case 0x04: //receive revival
                ReceiveRevival(ReceiveBuffer);
				break;
			case 0x10: //receive inventory
                //AddDebugText(ReceiveBuffer,Size);
                if ( !ReceiveInventory(ReceiveBuffer, bEncrypted))
				{
					return ( FALSE);
				}
				break;
			case 0x05: //receive level up
                ReceiveLevelUp(ReceiveBuffer);
				break;
			case 0x06: //receive Add Point
                ReceiveAddPoint(ReceiveBuffer);
				break;
			case 0x07: //receive damage
                //AddDebugText(ReceiveBuffer,Size);
                ReceiveDamage(ReceiveBuffer);
				break;
			case 0x08:
                //AddDebugText(ReceiveBuffer,Size);
                ReceivePK(ReceiveBuffer);
				break;
			case 0x11:
                //AddDebugText(ReceiveBuffer,Size);
                ReceiveMagicList(ReceiveBuffer);
				break;
			case 0x13:
                //AddDebugText(ReceiveBuffer,Size);
                ReceiveEquipment(ReceiveBuffer);
				break;
			case 0x14:
                //AddDebugText(ReceiveBuffer,Size);
                ReceiveModifyItem(ReceiveBuffer);
				break;
			case 0x20:
                ReceiveSummonLife(ReceiveBuffer);
				break;
			case 0x22://�����ð�
                ReceiveWTTimeLeft(ReceiveBuffer);
				break;
				
			case 0x24://��ġ ���
                ReceiveWTMatchResult(ReceiveBuffer);
				break;
				
			case 0x25://��Ʋ��Ŀ ����
				ReceiveWTBattleSoccerGoalIn(ReceiveBuffer);
				break;
			case 0x23://����
                ReceiveSoccerScore(ReceiveBuffer);
				break;
            case 0x30://���� ��Ű
                ReceiveOption(ReceiveBuffer);
                break;
			case 0x40:// �������� Ŭ���̾�Ʈ���� ��ɾ�
				ReceiveServerCommand(ReceiveBuffer);
				break;
			case 0x50:
				Receive_Master_Level_Exp(ReceiveBuffer);
				break;
			case 0x51:
				Receive_Master_LevelUp(ReceiveBuffer);
				break;
			case 0x52:
				Receive_Master_LevelGetSkill(ReceiveBuffer);
				break;
#ifdef PJH_CHARACTER_RENAME
			case 0x15:
				Receive_Check_Change_Name(ReceiveBuffer);
				break;
			case 0x16:
				Receive_Change_Name_Result(ReceiveBuffer);
				break;
#endif //PJH_CHARACTER_RENAME
			}
			break;
		}
	case 0xF4:     			
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch( subcode )
			{
			case 0x06:
				ReceiveServerList(ReceiveBuffer);
				break;
			case 0x03:
				ReceiveServerConnect(ReceiveBuffer);
				break;
			case 0x05:
				ReceiveServerConnectBusy(ReceiveBuffer);
				break;
			}
			break;
		}
	case 0x00://chat
        ReceiveChat(ReceiveBuffer);
		break;
	case 0x01://chat
        ReceiveChatKey(ReceiveBuffer);
		break;
	case 0x02://chat whisper
        ReceiveChatWhisper(ReceiveBuffer);
		break;
	case 0x03: // üũ�� ��û
		ReceiveCheckSumRequest( ReceiveBuffer);
		break;
	case 0x0B://
        AddDebugText(ReceiveBuffer,Size);
        ReceiveEvent(ReceiveBuffer);
		break;
	case 0x0C://
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveChatWhisperResult(ReceiveBuffer);
		break;
	case 0x0D://notice
        ReceiveNotice(ReceiveBuffer);
		break;
	case 0x0f:
        ReceiveWeather(ReceiveBuffer);
		break;
	case PACKET_MOVE: //move character
        ReceiveMoveCharacter(ReceiveBuffer,Size);
		break;
	case PACKET_POSITION: //move position
        ReceiveMovePosition(ReceiveBuffer);
		break;
	case 0x12: //create characters
        AddDebugText(ReceiveBuffer,Size);
        ReceiveCreatePlayerViewport(ReceiveBuffer,Size);
		break;
	case 0x13: //create monsters
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveCreateMonsterViewport(ReceiveBuffer);
		break;
	case 0x1F: //create monsters
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveCreateSummonViewport(ReceiveBuffer);
		break;
	case 0x45: //create monsters
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveCreateTransformViewport(ReceiveBuffer);
		break;
	case 0x14: //delete characters & monsters
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveDeleteCharacterViewport(ReceiveBuffer);
		break;
	case 0x20: //create item
        ReceiveCreateItemViewport(ReceiveBuffer);
		break;
	case 0x21://delete item
        ReceiveDeleteItemViewport(ReceiveBuffer);
		break;
	case 0x22://get item
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveGetItem(ReceiveBuffer);
		break;
	case 0x23://drop item
        ReceiveDropItem(ReceiveBuffer);
		break;
	case 0x24://equipment item
        AddDebugText(ReceiveBuffer,Size);
        if ( !ReceiveEquipmentItem(ReceiveBuffer, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x25://change character
        ReceiveChangePlayer(ReceiveBuffer);
		break;
	case PACKET_ATTACK://attack character
        ReceiveAttackDamage(ReceiveBuffer);
		break;
	case 0x18://action character
        ReceiveAction(ReceiveBuffer,Size);
		break;
	case 0x19://magic
        if ( !ReceiveMagic(ReceiveBuffer,Size, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x69:
        if ( !ReceiveMonsterSkill(ReceiveBuffer,Size, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x1A://magic
        ReceiveMagicPosition(ReceiveBuffer,Size);
		break;
	case 0x1E://magic
        if ( !ReceiveMagicContinue(ReceiveBuffer,Size, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x1B://magic
        ReceiveMagicFinish(ReceiveBuffer);
		break;
	case 0x07://setmagicstatus
		ReceiveSkillStatus(ReceiveBuffer);
		break;
	case 0x16://die character(exp)
        if ( !ReceiveDieExp(ReceiveBuffer,bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x9C://die character(exp)
        if ( !ReceiveDieExpLarge(ReceiveBuffer,bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x17://die character
        ReceiveDie(ReceiveBuffer,Size);
		break;
	case 0x2A:
        AddDebugText(ReceiveBuffer,Size);
        ReceiveDurability(ReceiveBuffer);
		break;
	case 0x26:
        ReceiveLife(ReceiveBuffer);
		break;
	case 0x27:
        ReceiveMana(ReceiveBuffer);
		break;
	case 0x28:
        ReceiveDeleteInventory(ReceiveBuffer);
		break;
	case 0x29:
        //AddDebugText(ReceiveBuffer,Size);
        if ( !ReceiveHelperItem(ReceiveBuffer,bEncrypted))
		{
			return ( FALSE);
		}
		break;
    case 0x2c:
        ReceiveUseStateItem ( ReceiveBuffer );
        break;
	case 0x30:
        if ( !ReceiveTalk(ReceiveBuffer, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x31:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeInventory(ReceiveBuffer);
		break;
	case 0x32:
        ReceiveBuy(ReceiveBuffer);
		break;
	case 0x33:
        ReceiveSell(ReceiveBuffer);
		break;
    case 0x34:
        ReceiveRepair(ReceiveBuffer);
        break;
	case 0x36:
        if ( !ReceiveTrade(ReceiveBuffer, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x37:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeResult(ReceiveBuffer);
		break;
	case 0x38:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeYourInventoryDelete(ReceiveBuffer);
		break;
	case 0x39:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeYourInventory(ReceiveBuffer);
		break;
	case 0x3A:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeMyGold(ReceiveBuffer);
		break;
	case 0x3B:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeYourGold(ReceiveBuffer);
		break;
	case 0x3C:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeYourResult(ReceiveBuffer);
		break;
	case 0x3D:
        //AddDebugText(ReceiveBuffer,Size);
        ReceiveTradeExit(ReceiveBuffer);
		break;
	case 0x1C:
        AddDebugText(ReceiveBuffer,Size);
		if ( !ReceiveTeleport(ReceiveBuffer, bEncrypted))
		{
			return ( FALSE);
		}
		break;
	case 0x40:
        ReceiveParty(ReceiveBuffer);
		break;
	case 0x41:
        ReceivePartyResult(ReceiveBuffer);
		break;
	case 0x42:
        ReceivePartyList(ReceiveBuffer);
		break;
	case 0x43:
        ReceivePartyLeave(ReceiveBuffer);
		break;
    case 0x44:
        ReceivePartyInfo(ReceiveBuffer);
        break;
    case 0x46:  //  �Ӽ� ����.
        ReceiveSetAttribute(ReceiveBuffer);
        break;
    case 0x47:
        ReceivePartyGetItem( ReceiveBuffer );
        break;
	case 0x48:
		ReceiveDisplayEffectViewport( ReceiveBuffer );
		break;
	case 0x50:
        ReceiveGuild(ReceiveBuffer);
		break;
	case 0x51:
        ReceiveGuildResult(ReceiveBuffer);
		break;
	case 0x52:
        ReceiveGuildList(ReceiveBuffer);
		break;
	case 0x53:
        ReceiveGuildLeave(ReceiveBuffer);
		break;
	case 0x54:	// ��帶���� NPC Ŭ����
        ReceiveCreateGuildInterface(ReceiveBuffer);
		break;
	case 0x55:	// ��帶���� NPC Ŭ���� ��� ���� Ŭ����
        ReceiveCreateGuildMasterInterface(ReceiveBuffer);
		break;
	case 0x56:
        ReceiveCreateGuildResult(ReceiveBuffer);
		break;
	case 0x65:
		ReceiveGuildIDViewport(ReceiveBuffer);
		break;
	case 0x66:
		ReceiveGuildInfo(ReceiveBuffer);
		break;
	case 0x5D:
        ReceiveDeleteGuildViewport(ReceiveBuffer);
		break;
	case 0x60:
        ReceiveDeclareWarResult(ReceiveBuffer);
		break;
	case 0x61:
        ReceiveDeclareWar(ReceiveBuffer);
		break;
	case 0x62:
        ReceiveGuildBeginWar(ReceiveBuffer);
		break;
	case 0x63:
        ReceiveGuildEndWar(ReceiveBuffer);
		break;
	case 0x64:
        ReceiveGuildWarScore(ReceiveBuffer);
		break;
	case 0xE1:	// �����å�� �Ӹ�/����/���� ���
		ReceiveGuildAssign(ReceiveBuffer);
		break;
	case 0xE5:	// ������ ��û ����
		ReceiveGuildRelationShip(ReceiveBuffer);
		break;
	case 0xE6:	// ������ ��û��� ����
		ReceiveGuildRelationShipResult(ReceiveBuffer);
		break;
	case 0xEB:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch(Data->SubCode)
			{
			case 0x01:	// ���ձ�� ����
				ReceiveBanUnionGuildResult(ReceiveBuffer);
				break;
			}
		}
		break;
	case 0x67:	// ��忬������ ���� ����
		ReceiveUnionViewportNotify(ReceiveBuffer);
		break;
	case 0xE9:	// ���ո���Ʈ ����
		ReceiveUnionList(ReceiveBuffer);
		break;
	case 0xBC:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch(Data->SubCode)
			{
			case 0x00:
				ReceiveGemMixResult(ReceiveBuffer);
				break;
			case 0x01:
				ReceiveGemUnMixResult(ReceiveBuffer);
				break;
			}
		}
		break;		
    case 0x68:  //  �ӽ� ����Ʈ ó��.
        ReceivePreviewPort ( ReceiveBuffer );
        break;
		
	case 0x71:
		ReceivePing(ReceiveBuffer);
		break;
#ifdef NP_GAME_GUARD
#ifdef GG_SERVER_AUTH
	case 0x73:
		if ( !ReceiveGGAuth(ReceiveBuffer, bEncrypted))
		{
			return ( FALSE);
		}
		break;
#endif
#endif
	case 0x81:
        ReceiveStorageGold(ReceiveBuffer);
		break;
	case 0x82:
        ReceiveStorageExit(ReceiveBuffer);
		break;
	case 0x83:
		ReceiveStorageStatus(ReceiveBuffer);
		break;
	case 0x86:
        ReceiveMix(ReceiveBuffer);
		break;
	case 0x87:
        ReceiveMixExit(ReceiveBuffer);
		break;
#ifdef YDG_MOD_PROTECT_AUTO_V5
	case 0x8A:
		ReceiveRequestCheckAutoTool(ReceiveBuffer);
		break;
#endif	// YDG_MOD_PROTECT_AUTO_V5
#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
	case 0x8E:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch(Data->SubCode)
			{
			case 0x01:
				ReceiveMoveMapChecksum(ReceiveBuffer);
				break;
			case 0x03:
				ReceiveRequestMoveMap(ReceiveBuffer);
				break;
			}
		}
		break;
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
	case 0x8D:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch(Data->SubCode)
			{
			case 0x05:
				ReceiveSkillDummySeedValue(ReceiveBuffer);
				break;
			}
		}
		break;
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
	case 0x90:
		ReceiveMoveToDevilSquareResult(ReceiveBuffer);
		break;
	case 0x91:
		ReceiveEventZoneOpenTime(ReceiveBuffer);
		break;
	case 0x92:
		ReceiveDevilSquareCountDown(ReceiveBuffer);
		break;
	case 0x93:
		ReceiveDevilSquareRank(ReceiveBuffer);
		break;
	case 0x9A://    ...
		ReceiveMoveToEventMatchResult(ReceiveBuffer);
		break;
    case 0x9B://    �̺�Ʈ ���� ����� �޴´�.
        ReceiveMatchGameCommand ( ReceiveBuffer );
        break;
    case 0x94://    �̺�ƮĨ ������ �޴´�.
        ReceiveEventChipInfomation(ReceiveBuffer);
        break;
    case 0x95://    �̺�ƮĨ��.
        ReceiveEventChip(ReceiveBuffer);
        break;
    case 0x96://    ���� ��ȣ.
        ReceiveMutoNumber(ReceiveBuffer);
        break;
	case 0x99:	// ���� ���� ���
		ReceiveServerImmigration(ReceiveBuffer);
		break;
#ifdef SCRATCH_TICKET
	case 0x9D:	//	���� ��÷ ��ǰ.
		ReceiveScratchResult( ReceiveBuffer );
		break;
#endif
	case 0x9E:	//	���� ���� ����
		ReceivePlaySoundEffect( ReceiveBuffer );
		break;
    case 0x9F:  //  �̺�Ʈ ���Ƚ��.
        ReceiveEventCount ( ReceiveBuffer );
        break;
    case 0xA0://    ����Ʈ ����Ʈ�� �޴´�.
        ReceiveQuestHistory ( ReceiveBuffer );
        break;
    case 0xA1://    Ư�� ����Ʈ ���� ������ �޴´�.
        ReceiveQuestState ( ReceiveBuffer );
        break;
    case 0xA2://    Ư�� ����Ʈ�� ����� �޴´�.    
        ReceiveQuestResult ( ReceiveBuffer );
        break;
    case 0xA3://    ����Ʈ�� ���� �޴´�.
        ReceiveQuestPrize ( ReceiveBuffer );
        break;
	case 0xA4:
		ReceiveQuestMonKillInfo(ReceiveBuffer);
		break;
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
	case 0xF6:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch (Data->SubCode)
			{
#ifdef ASG_ADD_TIME_LIMIT_QUEST
			case 0x00:
				ReceiveQuestLimitResult(ReceiveBuffer);		// ������ ���� ����Ʈ ���� �� ����.
				break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST
			case 0x03:
				ReceiveQuestByEtcEPList(ReceiveBuffer);		// ��Ÿ ��Ȳ�� ����Ʈ EP(���Ǽҵ�)����Ʈ�� ����.
				break;
#ifdef ASG_ADD_TIME_LIMIT_QUEST
			case 0x04:
				ReceiveQuestByItemUseEP(ReceiveBuffer);		// ����Ʈ ������ ��뿡 ���� EP(���Ǽҵ�)�� ����.
#endif	// ASG_ADD_TIME_LIMIT_QUEST
			case 0x0A:
				ReceiveQuestByNPCEPList(ReceiveBuffer);		// NPC�� ���� EP(���Ǽҵ�)����Ʈ�� ����.
				break;
			case 0x0B:
				ReceiveQuestQSSelSentence(ReceiveBuffer);	// ���ù��� �ִ� QS(����Ʈ ����)�� ����
				break;
			case 0x0C:
				ReceiveQuestQSRequestReward(ReceiveBuffer);	// �䱸, ������ �ִ� QS(����Ʈ ����)�� ����.
				break;
			case 0x0D:
				ReceiveQuestCompleteResult(ReceiveBuffer);	// �䱸, ���� ����� ����.
				break;
			case 0x0F:
				ReceiveQuestGiveUp(ReceiveBuffer);			// ����Ʈ ���������� ���� ����.
				break;
			case 0x1A:
				ReceiveProgressQuestList(ReceiveBuffer);	// ���� ���� ����Ʈ ����Ʈ�� ����.
				break;
			case 0x1B:
				ReceiveProgressQuestRequestReward(ReceiveBuffer);// �������� ����Ʈ ����Ʈ���� Ư�� ����Ʈ�� �䱸, ���� ������ ����.
				break;
#ifdef ASG_FIX_QUEST_PROTOCOL_ADD
			case 0x20:
				ReceiveProgressQuestListReady(ReceiveBuffer);	// ���� ���� ����Ʈ ����Ʈ�� �� �غ� ��.
				break;
#endif	// ASG_FIX_QUEST_PROTOCOL_ADD
			}
		}
		break;
#endif	// ASG_ADD_NEW_QUEST_SYSTEM

#ifdef ASG_ADD_GENS_SYSTEM
	case 0xF8:
		{
			BYTE bySubcode;

			if (ReceiveBuffer[0] == 0xC1)
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				bySubcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				bySubcode = Data->SubCode;
			}

			switch (bySubcode)
			{
			case 0x02:
				ReceiveGensJoining(ReceiveBuffer);			// �ս� ���� ��û ����. 
				break;
			case 0x04:
				ReceiveGensSecession(ReceiveBuffer);		// �ս� Ż�� ��û ����. 
				break;
			case 0x07:
				ReceivePlayerGensInfluence(ReceiveBuffer);	// �÷��̾��� �ս� ���� ���� ����.
				break;
			case 0x05:
				ReceiveOtherPlayerGensInfluenceViewport(ReceiveBuffer);	// ����Ʈ ���� �ٸ� �÷��̾��� �ս� ���� ���� ����.
				break;
#ifdef PBG_ADD_GENSRANKING
			case 0x0A:
				ReceiveReward(ReceiveBuffer);				// ����ޱ� ��û ����
				break;
#endif //PBG_ADD_GENSRANKING
			}
		}
		break;
#endif	// ASG_ADD_GENS_SYSTEM
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	case 0xF9:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch (Data->SubCode)
			{
			case 0x01:
				ReceiveNPCDlgUIStart(ReceiveBuffer);		// NPC UI�� ��ȭ�� ����Ǵ� NPC Ŭ�� �� ���� ����. 
				break;
			}
		}
		break;
#endif	// ASG_ADD_UI_NPC_DIALOGUE

#ifdef PET_SYSTEM
    case 0xA7:
        ReceivePetCommand ( ReceiveBuffer );
        break;
    case 0xA8:
        ReceivePetAttack ( ReceiveBuffer );
        break;
    case 0xA9:
        ReceivePetInfo ( ReceiveBuffer );
        break;
#endif// PET_SYSTEM
		
#ifdef YDG_ADD_NEW_DUEL_PROTOCOL
	case 0xAA:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch ( Data->SubCode )
			{
			case 0x01:	// ������û ���
				ReceiveDuelStart( ReceiveBuffer );
				break;
			case 0x02:	// ������û
				ReceiveDuelRequest( ReceiveBuffer );
				break;
			case 0x03:	// ��������
				ReceiveDuelEnd( ReceiveBuffer );
				break;
			case 0x04:	// ������ ���� ����
				ReceiveDuelScore( ReceiveBuffer );
				break;
			case 0x05:	// ������ ���� ����
				ReceiveDuelHP( ReceiveBuffer );
				break;
			case 0x06:	// ���� ä��(����) ����Ʈ
				ReceiveDuelChannelList( ReceiveBuffer );
				break;
			case 0x07:	// ä��(����) ��û
				ReceiveDuelWatchRequestReply( ReceiveBuffer );
				break;
			case 0x08:	// ä��(����) ������ ������
				ReceiveDuelWatcherJoin( ReceiveBuffer );
				break;
			case 0x09:	// ä��(����) ����
				ReceiveDuelWatchEnd( ReceiveBuffer );
				break;
			case 0x0A:	// ä��(����) ���� ������
				ReceiveDuelWatcherQuit( ReceiveBuffer );
				break;
			case 0x0B:	// ������ ����Ʈ(All)
				ReceiveDuelWatcherList( ReceiveBuffer );
				break;
			case 0x0C:	// ������� ����
				ReceiveDuelResult( ReceiveBuffer );
				break;
			case 0x0D:	// ���� ����/�� �˸�
				ReceiveDuelRound( ReceiveBuffer );
				break;
			}
		}
		break;
#else	// YDG_ADD_NEW_DUEL_PROTOCOL
#ifdef DUEL_SYSTEM
	case 0xAA:
		ReplyDuelStart( ReceiveBuffer );
		break;
	case 0xAB:
		ReplyDuelEnd( ReceiveBuffer );
		break;
	case 0xAC:
		NotifyDuelStart( ReceiveBuffer );
		break;
	case 0xAD:
		NotifyDuelScore( ReceiveBuffer );
		break;
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_PROTOCOL
#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
		//���� ��ȣ��
	case 0xF7:
		{
			LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
			switch ( Data->SubCode )
			{
			case 0x02:
				ReceiveEnterEmpireGuardianEvent( ReceiveBuffer );
				break;

			case 0x04:
				ReceiveRemainTickEmpireGuardian( ReceiveBuffer );
				break;

			case 0x06:
				ReceiveResultEmpireGuardian( ReceiveBuffer );
				break;
			}
		}
		break;
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
	case 0x3F:
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch(subcode)
			{
			case 0x00:
				ReceiveCreateShopTitleViewport( ReceiveBuffer );
				break;
			case 0x01:
				ReceiveSetPriceResult( ReceiveBuffer );
				break;
			case 0x02:
				ReceiveCreatePersonalShop( ReceiveBuffer );
				break;
			case 0x03:
				ReceiveDestroyPersonalShop( ReceiveBuffer );
				break;
			case 0x05:
				ReceivePersonalShopItemList( ReceiveBuffer );
				break;
			case 0x06:
				ReceivePurchaseItem( ReceiveBuffer );
				break;
			case 0x08:
				NotifySoldItem( ReceiveBuffer );
				break;
			case 0x10:
				ReceiveShopTitleChange( ReceiveBuffer );
				break;
			case 0x12:
				NotifyClosePersonalShop( ReceiveBuffer );
				break;
			case 0x13:
				ReceiveRefreshItemList( ReceiveBuffer );
				break;
			}
		}
		break;
    case 0xAF:
        {
            LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
            switch ( Data->SubCode )
            {
            case 0x01:
                ReceiveMoveToEventMatchResult2 ( ReceiveBuffer );
                break;
            }
        }
        break;
    case 0xB1:  //  �ʼ��� �̵��� ���� ��Ŷ ����.
        {
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch(subcode)
			{
            case 0x00:
                ReceiveChangeMapServerInfo ( ReceiveBuffer );
                break;
				
            case 0x01:
                ReceiveChangeMapServerResult ( ReceiveBuffer );
                break;
            }
        }
        break;
	case 0xB2:
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch( subcode )
			{
			case 0x00:	// ���� ����
				ReceiveBCStatus( ReceiveBuffer );
				break;
			case 0x01:	// ���� ��ϰ��
				ReceiveBCReg( ReceiveBuffer );
				break;
			case 0x02:	// ���� ������
				ReceiveBCGiveUp( ReceiveBuffer );
				break;
			case 0x03:	// ���� �������
				ReceiveBCRegInfo( ReceiveBuffer );
				break;
			case 0x04:	// ǥ�� ��ϰ��
				ReceiveBCRegMark( ReceiveBuffer );
				break;
			case 0x05:	// ������ NPC ����
				ReceiveBCNPCBuy( ReceiveBuffer );
				break;
			case 0x06:	// ������ NPC ����
				ReceiveBCNPCRepair( ReceiveBuffer );
				break;
			case 0x07:	// ������ NPC ��ȭ
				ReceiveBCNPCUpgrade( ReceiveBuffer );
				break;
			case 0x08:	// ���� ���� �ڱ�, ���� ���� ��û ���� (0xC1)
				ReceiveBCGetTaxInfo( ReceiveBuffer );
				break;
			case 0x09:	// ���� ���� ���� ���� ��û ���� (0xC1)
				ReceiveBCChangeTaxRate( ReceiveBuffer );
				break;
			case 0x10:	// ���� ���� �ڱ� ��� ��û ���� (0xC1)
				ReceiveBCWithdraw( ReceiveBuffer );
				break;
			case 0x1A:	// ���� ����
				ReceiveTaxInfo( ReceiveBuffer );
				break;
            case 0x1F:  //  ������ ������.
                ReceiveHuntZoneEnter( ReceiveBuffer );
                break;
				
            case 0x11:
                ReceiveGateState ( ReceiveBuffer );
                break;
				
            case 0x12:
                ReceiveGateOperator ( ReceiveBuffer );
                break;
				
            case 0x13:
                ReceiveGateCurrentState ( ReceiveBuffer );
                break;
				
            case 0x14:
                ReceiveCrownSwitchState ( ReceiveBuffer );
                break;
				
            case 0x15:
                ReceiveCrownRegist ( ReceiveBuffer );
                break;
				
            case 0x16:
                ReceiveCrownState ( ReceiveBuffer );
                break;
				
            case 0x17:
                ReceiveBattleCastleStart ( ReceiveBuffer );
                break;
				
            case 0x18:
                ReceiveBattleCastleProcess ( ReceiveBuffer );
                break;
				
            case 0x19:
                ReceiveBattleCastleRegiment ( ReceiveBuffer );
                break;
				
			case 0x20:
				ReceiveBattleCasleSwitchInfo (ReceiveBuffer);
				break;
				
            case 0x1B:
                ReceiveMapInfoResult ( ReceiveBuffer );
                break;
				
            case 0x1D:
                ReceiveGuildCommand ( ReceiveBuffer );
                break;
				
            case 0x1E:
                ReceiveMatchTimer ( ReceiveBuffer );
                break;
			}
		}
		break;
		
	case 0xB3:	// ���� NPC ���
		ReceiveBCNPCList( ReceiveBuffer );
		break;
	case 0xB4:	// ���� ��� ��� ���
		ReceiveBCDeclareGuildList( ReceiveBuffer );
		break;
	case 0xB5:	// ���� Ȯ�� ��� ���
		ReceiveBCGuildList( ReceiveBuffer );
		break;
    case 0xB6:  //  �������� ��ġ ������ �˾Ƴ���.
        ReceiveGuildMemberLocation ( ReceiveBuffer );
        break;
    case 0xBB:  //  �ʿ� �����ϴ� NPC������ �˾Ƴ���.
        ReceiveGuildNpcLocation ( ReceiveBuffer );
        break;
    case 0xB7:
        {
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch( subcode )
			{
            case 0x00:
                ReceiveCatapultState ( ReceiveBuffer );
                break;
				
            case 0x01:
                ReceiveCatapultFire ( ReceiveBuffer );
                break;
				
            case 0x02:
                ReceiveCatapultFireToMe ( ReceiveBuffer );
                break;
				
            case 0x03:
				//                ReceiveDamageFrmeCatapult ( ReceiveBuffer );
                break;
            }
        }
        break;
		
    case 0xB8:  //  ��Ʋ������ ��ų.
        {
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch( subcode )
			{
            case 0x01:
                ReceiveKillCount ( ReceiveBuffer );
                break;
				
            case 0x02:
                break;
            }
        }
        break;
    case 0xB9:
        {
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch( subcode )
			{
            case 0x01:
                ReceiveBuildTime ( ReceiveBuffer );
                break;
				
            case 0x02:
                ReceiveCastleGuildMark ( ReceiveBuffer );
                break;
				
            case 0x03:
                ReceiveCastleHuntZoneInfo ( ReceiveBuffer );
                break;
				
            case 0x05:
                ReceiveCastleHuntZoneResult ( ReceiveBuffer );
                break;
            }
        }
        break;
		
	case 0xBA:
		ReceiveSkillCount ( ReceiveBuffer );
		break;
	case 0xBD:
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch(subcode)
			{
			case 0x00:
				ReceiveCrywolfInfo(ReceiveBuffer);  // ũ���̿��� �� ���¸� �޴´�.
				break;
			case 0x02:
				ReceiveCrywolStateAltarfInfo(ReceiveBuffer);  // ũ���̿��� ���� ��, ���� ���¸� �޴´�.
				break;
			case 0x03:
				ReceiveCrywolfAltarContract(ReceiveBuffer);  // ���� ��� ����� �޴´�.
				break;
			case 0x04:
				ReceiveCrywolfLifeTime(ReceiveBuffer);  // ũ���̿��� ���� �ð��� ���� ������ �޴´�.
				break;
			case 0x0C:
				ReceiveCrywolfTankerHit(ReceiveBuffer);
				break;
			case 0x05:
				ReceiveCrywolfBossMonsterInfo(ReceiveBuffer);
				break;
			case 0x07:
				ReceiveCrywolfPersonalRank(ReceiveBuffer);
				break;
			case 0x09:
				ReceiveCrywolfBenefitPlusChaosRate(ReceiveBuffer);
				break;
			case 0x08:
				ReceiveCrywolfHeroList(ReceiveBuffer);
				break;
			}
			break;
		}
	case 0xC0:	// ģ�� ����Ʈ�� �޴´�.
		ReceiveFriendList(ReceiveBuffer);
		break;
	case 0xC1:	// ģ�� ��� ��û ����� �޴´�. (����� ���)
		ReceiveAddFriendResult(ReceiveBuffer);
		break;
	case 0xC2:	// ģ�� ��� ��û�� �޴´�. (��� ���� ���)
		ReceiveRequestAcceptAddFriend(ReceiveBuffer);
		break;
	case 0xC3:	// ģ�� ���� ��û ����� �޴´�.
		ReceiveDeleteFriendResult(ReceiveBuffer);
		break;
	case 0xC4:	// ģ�� ģ�� ���� ��ȭ�� �޴´�.
		ReceiveFriendStateChange(ReceiveBuffer);
		break;
	case 0xC5:	// ���� ���� ��� �ޱ�
		ReceiveLetterSendResult(ReceiveBuffer);
		break;
	case 0xC6:	// ���� �ޱ�
		ReceiveLetter(ReceiveBuffer);
		break;
	case 0xC7:	// ���� ���� �ޱ�
		ReceiveLetterText(ReceiveBuffer);
		break;
	case 0xC8:	// ���� ���� ��� �ޱ�
		ReceiveLetterDeleteResult(ReceiveBuffer);
		break;
	case 0xCA:	// ��ȭ�� ���� ��û ��� �ޱ�
		ReceiveCreateChatRoomResult(ReceiveBuffer);
		break;
	case 0xCB:	// �ʴ� ��� �ޱ�
		ReceiveChatRoomInviteResult(ReceiveBuffer);
		break;
	case 0x2D:	// ��� ������ ���۰� ���Ḧ �˷��ش�.( ����� ĳ���� )
		ReceiveBuffState(ReceiveBuffer);
		break;
	case 0xD1:
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			switch(subcode)
			{
			case 0x00:		// ĭ���� �������� ���� ���� ���� ��û�� ���� ����
				ReceiveKanturu3rdStateInfo(ReceiveBuffer);
				break;
			case 0x01:		// ĭ���� ������ ������ ���� ��û�� ���� ����
				ReceiveKanturu3rdEnterBossMap(ReceiveBuffer);
				break;
			case 0x02:		// ĭ���� ������ ���¿� �׿� ���� ���� ���� ���� ����(�ʿ� ó�� ���� ��)
				ReceiveKanturu3rdCurrentState(ReceiveBuffer);
				break;
			case 0x03:		// ĭ���� ������ ���¿� �׿� ���� ���� ���� ���� ����
				ReceiveKanturu3rdState(ReceiveBuffer);
				break;
			case 0x04:		// ĭ���� ������ ���� ����,���� ��� ����
				ReceiveKanturu3rdResult(ReceiveBuffer);
				break;
			case 0x05:		// ĭ���� ���� ���� �ð�
				ReceiveKanturu3rdTimer(ReceiveBuffer);
				break;
			case 0x06:		// ĭ���� ���� ��ü ��ų ����
				RecevieKanturu3rdMayaSKill(ReceiveBuffer);
				break;
			case 0x07:		// ĭ���� ���� �ο� �� ���� �� ǥ��
				RecevieKanturu3rdLeftUserandMonsterCount(ReceiveBuffer);
				break;
#ifdef CSK_RAKLION_BOSS
			case 0x10:		// ������ ��Ŭ���� �������� ���� ���� ���� ��û�� ���� ����
				ReceiveRaklionStateInfo(ReceiveBuffer);
				break;
			case 0x11:		// ������ ��Ŭ���� ������ �����ʿ� �������� �� ���� ���¸� ������.
				ReceiveRaklionCurrentState(ReceiveBuffer);
				break;
			case 0x12:		// ��Ŭ���� ������ ���� ���°� ������ �� ���°��� �˸���.
				RecevieRaklionStateChange(ReceiveBuffer);
				break;
			case 0x13:		// ��Ŭ���� ������ ���� ���� / ����
				RecevieRaklionBattleResult(ReceiveBuffer);
				break;
			case 0x14:		// ��Ŭ���� ������ ���� ����( ������ ��ų ��� )
				RecevieRaklionWideAreaAttack(ReceiveBuffer);
				break;
			case 0x15:		// ��Ŭ���� ���� ����&���� �� ���÷���
				RecevieRaklionUserMonsterCount(ReceiveBuffer);
				break;	
#endif // CSK_RAKLION_BOSS
			}
			break;
		}
#ifdef ADD_PCROOM_POINT_SYSTEM
	case 0xD0:
		{
			int nSubCode;
			if (ReceiveBuffer[0] == 0xC1)
			{
				LPPHEADER_DEFAULT_SUBCODE pData = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				nSubCode = pData->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD pData = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				nSubCode = pData->SubCode;
			}
			switch(nSubCode)
			{
			case 0x04:
				ReceivePCRoomPointInfo(ReceiveBuffer);
				break;
#ifndef KJH_DEL_PC_ROOM_SYSTEM		// #ifndef
			case 0x05:
				ReceivePCRoomPointUse(ReceiveBuffer);
				break;
			case 0x06:
				ReceivePCRoomPointShopOpen(ReceiveBuffer);
				break;
#endif // KJH_DEL_PC_ROOM_SYSTEM
			}
		}
		break;
#endif	// ADD_PCROOM_POINT_SYSTEM
	case 0xBF:
		{
			int subcode;
			if( ReceiveBuffer[0] == 0xC1 )
			{
				LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
				subcode = Data->SubCode;
			}
			else
			{
				LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
				subcode = Data->SubCode;
			}
					
			switch(subcode)
			{
			case 0x00:
				ReceiveCursedTempleEnterResult( ReceiveBuffer );
				break;
			case 0x01:
				ReceiveCursedTempleInfo(ReceiveBuffer);
				break;
			case 0x02:
				ReceiveCursedTempMagicResult( ReceiveBuffer );
				break;
			case 0x03:
				ReceiveCursedTempleEnterInfo( ReceiveBuffer );
				break;
			case 0x04:
				ReceiveCursedTempleGameResult( ReceiveBuffer );
				break;
			case 0x06:
				ReceiveCursedTempSkillPoint( ReceiveBuffer );
				break;
			case 0x07:
				ReceiveCursedTempSkillEnd( ReceiveBuffer );
			break;
			case 0x08:
				ReceiveCursedTempleHolyItemRelics( ReceiveBuffer );
				break;
			case 0x09:
				ReceiveCursedTempleState( ReceiveBuffer );
				break;
			case 0x0a:
				ReceiveChainMagic( ReceiveBuffer );
				break;
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
				//����� ���� ��������
			case 0x0B:
				//��ϵ� ��������
				ReceiveRegistedLuckyCoin(ReceiveBuffer);
				break;
			case 0x0C:
			//��ϵ���
				ReceiveRegistLuckyCoin(ReceiveBuffer);
				break;
			case 0x0D:
				//������ȯ
				ReceiveRequestExChangeLuckyCoin(ReceiveBuffer);
				break;
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_DOPPELGANGER_PROTOCOLS
			case 0x0E:	// ���ð���� ���� ��û ���
				ReceiveEnterDoppelGangerEvent(ReceiveBuffer);
				break;
			case 0x0F:	// ���ð��� ���� ���� ��ġ
				ReceiveDoppelGangerMonsterPosition(ReceiveBuffer);
				break;
			case 0x10:	// ���ð����� ���� ����
				ReceiveDoppelGangerState(ReceiveBuffer);
				break;
			case 0x11:	// ���ð����� ���̽���Ŀ�� ���� ����
				ReceiveDoppelGangerIcewalkerState(ReceiveBuffer);
				break;
			case 0x12:	// ���ð����� ���� ���� / �ð� ���� / ��Ƽ ��ġ����
				ReceiveDoppelGangerTimePartyState(ReceiveBuffer);
				break;
			case 0x13:	// ���ð����� ���
				ReceiveDoppelGangerResult(ReceiveBuffer);
				break;
			case 0x14:	// ���ð����� ���
				ReceiveDoppelGangerMonsterGoal(ReceiveBuffer);
				break;
#endif	// YDG_ADD_DOPPELGANGER_PROTOCOLS
#ifdef PBG_ADD_SECRETBUFF
			case 0x15:	// �Ƿε� �ۼ�Ʈ
				ReceiveFatigueTime(ReceiveBuffer);
				break;
#endif //PBG_ADD_SECRETBUFF
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
			case 0x20:
				ReceiveEquippingInventoryItem(ReceiveBuffer);
				break;
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
				}
			}
			break;
				
#if defined PSW_CHARACTER_CARD || defined PBG_ADD_CHARACTERCARD
			case 0xDE:
				{
					int subcode = 0;
					
					if( ReceiveBuffer[0] == 0xC1 ) {
						LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
						subcode = Data->SubCode;
					}
					else {
						LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
						subcode = Data->SubCode;
					}
					
					switch( subcode )
					{
#ifdef PBG_ADD_CHARACTERCARD
					case 0x00: ReceiveCharacterCard_New( ReceiveBuffer );	//��ȯ/����/��ũ
						break;
#else //PBG_ADD_CHARACTERCARD												//���� �ؿ� ����
					case 0x00: ReceiveCharacterCard( ReceiveBuffer );			break;
					case 0x01: ReceiveBuyCharacterCard( ReceiveBuffer );		break;
#endif //PBG_ADD_CHARACTERCARD
					}
				}
				break;
#endif //defined PSW_CHARACTER_CARD || defined PBG_ADD_CHARACTERCARD
				
#ifdef NEW_USER_INTERFACE_SERVERMESSAGE
			case 0xF5:
				{
					int subcode = 0;
					
					if( ReceiveBuffer[0] == 0xC1 )
					{
						LPPHEADER_DEFAULT_SUBCODE Data = (LPPHEADER_DEFAULT_SUBCODE)ReceiveBuffer;
						subcode = Data->SubCode;
					}
					else
					{
						LPPHEADER_DEFAULT_SUBCODE_WORD Data = (LPPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
						subcode = Data->SubCode;
					}
					
					switch( subcode )
					{
//#if SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
//					case 0xA1: RecevieCashShopInOut( ReceiveBuffer );			break;
//#else	// SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
					case 0x02:
						{
							RecevieCashShopInOut( ReceiveBuffer );
						}
						break;
//#endif	// SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
					case 0x04: 
						{
							RecevieCashShopCashPoint( ReceiveBuffer );
						}
						break;
					case 0x06:
						{
							RecevieCashShopItemlist( ReceiveBuffer );
						}
						break;
					case 0x08: RecevieCashShopItemPurchase( ReceiveBuffer );	break;
					}
				}
				break;
#endif //NEW_USER_INTERFACE_SERVERMESSAGE
#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
		case 0xD2:		// �ΰ��Ӽ�
			{
				PBMSG_HEADER2* Data = (PBMSG_HEADER2*)ReceiveBuffer;
				switch(Data->m_bySubCode)
				{
				case 0x01:
					ReceiveIGS_CashPoint(ReceiveBuffer);			// ĳ�� ����Ʈ ���
					break;
				case 0x02:
					ReceiveIGS_ShopOpenResult(ReceiveBuffer);		// �� Open/Close ���
					break;
				case 0x03:
					ReceiveIGS_BuyItem(ReceiveBuffer);				// ������ ���Ű��	
					break;
				case 0x04:
					ReceiveIGS_SendItemGift(ReceiveBuffer);			// ������ �������
					break;
				case 0x06:
					ReceiveIGS_StorageItemListCount(ReceiveBuffer);		// ������ ����Ʈ ī��Ʈ ����
					break;
				case 0x07:
					ReceiveIGS_SendCashGift(ReceiveBuffer);			// ĳ�ü��� ���
					break;
				case 0x08:
					ReceiveIGS_PossibleBuy(ReceiveBuffer);			// �������� ����/�������� ���
					break;
				case 0x09:
					ReceiveIGS_LeftCountItem(ReceiveBuffer);		// ��ǰ�ܿ� ��ȸ���� ���
					break;
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT					// #ifndef
				case 0x0A:
					ReceiveIGS_DeleteStorageItem(ReceiveBuffer);	// ������ ������ ���
					break;
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
				case 0x0B:
					ReceiveIGS_UseStorageItem(ReceiveBuffer);		// ������ ������ �����
					break;
				case 0x0C:
					ReceiveIGS_UpdateScript(ReceiveBuffer);			// ��ũ��Ʈ ������Ʈ
					break;
				case 0x0D:
					ReceiveIGS_StorageItemList(ReceiveBuffer);		// ������ ����Ʈ ����
					break;
				case 0x0E:
					ReceiveIGS_StorageGiftItemList(ReceiveBuffer);	// ������ ����Ʈ ����
					break;
				case 0x13:
					ReceiveIGS_EventItemlistCnt(ReceiveBuffer);		// �̺�Ʈ ������ ����Ʈ ī��Ʈ
					break;
				case 0x14:
					ReceiveIGS_EventItemlist(ReceiveBuffer);		// �̺�Ʈ ������ ����Ʈ
					break;
				case 0x15:
					ReceiveIGS_UpdateBanner(ReceiveBuffer);			// ��� ���� ������Ʈ
					break;
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
				case 0x11:
					ReceivePeriodItemListCount(ReceiveBuffer);		// �Ⱓ�� ������ ����Ʈ ī��Ʈ
					break;	
				case 0x12:
					ReceivePeriodItemList(ReceiveBuffer);			// �Ⱓ�� ������ ����Ʈ
					break;
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
				}
			}break;

#endif // KJH_PBG_ADD_INGAMESHOP_SYSTEM
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		case 0x4A:
			ReceiveStraightAttack(ReceiveBuffer, Size, bEncrypted);
			break;
		case 0x4B:
			ReceiveDarkside(ReceiveBuffer);
			break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		default:
			{
				//AddDebugText(ReceiveBuffer,Size);
			}
			
			break;
	}
	
	return ( TRUE);
}

void TranslateChattingProtocol(DWORD dwWindowUIID, int HeadCode, BYTE *ReceiveBuffer, int Size, BOOL bEcrypted)
{
	switch( HeadCode )
	{
	case 0x00:	// �� ���� ��� �ޱ�
		ReceiveChatRoomConnectResult(dwWindowUIID, ReceiveBuffer);
		break;
	case 0x01:	// �ٸ� ��� ���� ��ȭ
		ReceiveChatRoomUserStateChange(dwWindowUIID, ReceiveBuffer);
		break;
	case 0x02:	// ��������Ʈ �ޱ�
		ReceiveChatRoomUserList(dwWindowUIID, ReceiveBuffer);
		break;
	case 0x04:	// ä�� ��ȭ �� �ޱ�
		ReceiveChatRoomChatText(dwWindowUIID, ReceiveBuffer);
		break;
	case 0x0D:	// ��������
		ReceiveChatRoomNoticeText(dwWindowUIID, ReceiveBuffer);
		break;
	default:
		break;
	}
}

bool CheckExceptionBuff( eBuffState buff, OBJECT* o, bool iserase )
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!! ��� !!!!!!!!!!!!!!!!!!!!!!!!!!! 
	// !!!!!!!!!!!!!!!!!!!!!!!!!!! ��� !!!!!!!!!!!!!!!!!!!!!!!!!!! 
	
	// return false�� �� ��� buff�� ��� ��Ű�� �ʴ´�.
	// �ٴ� �����δ� ����� �̷��� ������ ����.
	// �� �κе��� ������ ������ �Ʋ��� ���� �����̴�...����� ���⿡ �߰� ���Ѽ� �۾��� ���� ����.
	// �߰��� �� �ϴ��� ����� �ٸ� ������� �����ϴ�.
	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!! ��� !!!!!!!!!!!!!!!!!!!!!!!!!!! 
	// !!!!!!!!!!!!!!!!!!!!!!!!!!! ��� !!!!!!!!!!!!!!!!!!!!!!!!!!! 
	
	if( iserase )
	{
		switch(buff)
		{
		case eBuff_SoulPotion:
			{
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					g_CharacterUnRegisterBuff(o, eBuff_CrywolfAltarEnable );
					return false;
				}
			}
			break;
			
		case eBuff_RemovalMagic:
			{
				list<eBuffState> bufflist;

				//debuff
				bufflist.push_back( eDeBuff_Poison ); 
				bufflist.push_back( eDeBuff_Freeze );
				bufflist.push_back( eDeBuff_Harden ); 
				bufflist.push_back( eDeBuff_Defense );
				bufflist.push_back( eDeBuff_Stun );
				bufflist.push_back( eDeBuff_Sleep );
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
				bufflist.push_back( eDeBuff_BlowOfDestruction );
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION

				//buff
				bufflist.push_back( eBuff_HpRecovery ); bufflist.push_back( eBuff_Attack );
				//bufflist.push_back( eBuff_Life ); bufflist.push_back( eBuff_Attack );
				bufflist.push_back( eBuff_Defense ); bufflist.push_back( eBuff_AddAG );
				bufflist.push_back( eBuff_Cloaking ); bufflist.push_back( eBuff_AddSkill );
				bufflist.push_back( eBuff_PhysDefense ); bufflist.push_back( eBuff_AddCriticalDamage );
				bufflist.push_back( eBuff_CrywolfAltarOccufied );
				
				g_CharacterUnRegisterBuffList(o, bufflist );
			}
			break;
		}
		
		return true;
	}
	else
	{
		switch(buff)
		{
		case eBuff_CastleRegimentAttack3:
			{
				g_CharacterUnRegisterBuff(o, eBuff_CastleRegimentDefense);
			}	
			break;
			
		case eBuff_SoulPotion:
			{
				// ������ ��츸..
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					// MVP�϶�  ���� ��� ���� ����
					g_CharacterRegisterBuff(o, eBuff_CrywolfAltarEnable);
					return false;
				}
			}
			break;
			
		case eBuff_CastleGateIsOpen:
			{
				// ������ ��츸..
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					// MVP�϶�  ���� ��� �Ҵ� ����
					g_CharacterRegisterBuff(o, eBuff_CrywolfAltarDisable);
					return false;
				}
			}
			break;
			
		case eBuff_CastleRegimentDefense:
			{
				// ������ ��츸..
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					// MVP�϶�  ���� ��� �� ����
					g_CharacterRegisterBuff(o, eBuff_CrywolfAltarContracted);
					return false;
				}
				else
				{
					g_TokenCharacterBuff(o, eBuff_CastleRegimentDefense);
					return false;
				}
			}
			break;
			
		case eBuff_CastleRegimentAttack1:
			{
				// ������ ��츸..
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					// MVP�϶�  ���� ��� �õ� ����
					g_CharacterRegisterBuff(o, eBuff_CrywolfAltarAttempt );
					return false;
				}
				else if( g_isCharacterBuff( o, eBuff_CastleRegimentDefense ) )
				{
					g_CharacterUnRegisterBuff(o, eBuff_CastleRegimentDefense);
				}
			}
			break;
			
		case eBuff_RemovalMagic:
			{
				// ������ ��츸..
				if(o->Type >= MODEL_CRYWOLF_ALTAR1 && o->Type <= MODEL_CRYWOLF_ALTAR5)
				{
					// MVP�϶�  ���� ���� ���� ����
					g_CharacterRegisterBuff(o, eBuff_CrywolfAltarOccufied);
					return false;
				}
			}
			break;
			
		case eBuff_CastleRegimentAttack2:
			{
				if( g_isCharacterBuff( o, eBuff_CastleRegimentDefense ) )
					g_CharacterUnRegisterBuff(o, eBuff_CastleRegimentDefense);
			}
			break;
		}
		
		return true;
	}
}

// ������ ����Ʈ ó���� ���⼭ �� ���ش�. ������ �����Ҷ�
void InsertBuffLogicalEffect( eBuffState buff, OBJECT* o, const int bufftime )
{
	if(o && o == &Hero->Object)
	{
		switch( buff )
		{
		case eBuff_Hellowin1:
		case eBuff_Hellowin2:
		case eBuff_Hellowin3:
		case eBuff_Hellowin4:
		case eBuff_Hellowin5:
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
				
				// ���� ���� ĳ���Ϳ� ����
				if( buff == eBuff_Hellowin1 ) 
				{
					CharacterMachine->CalculateAttackSpeed();
				}
				if( buff == eBuff_Hellowin2 ) 
				{
					CharacterMachine->CalculateDamage();
				}
				if( buff == eBuff_Hellowin3 ) 
				{
					CharacterMachine->CalculateDefense();
				}
			}
			break;
		case eBuff_PcRoomSeal1:
		case eBuff_PcRoomSeal2:
		case eBuff_PcRoomSeal3:
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
			}
			break;
		case eBuff_Seal1:
		case eBuff_Seal2:
		case eBuff_Seal3:
		case eBuff_Seal4:
#ifdef PSW_ADD_PC4_SEALITEM
		case eBuff_Seal_HpRecovery:
		case eBuff_Seal_MpRecovery:
#endif //PSW_ADD_PC4_SEALITEM
#ifdef ASG_ADD_CS6_GUARD_CHARM
		case eBuff_GuardCharm:
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
		case eBuff_ItemGuardCharm:
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		case eBuff_AscensionSealMaster:
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		case eBuff_WealthSealMaster:
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		case eBuff_NewWealthSeal:
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef YDG_ADD_CS7_MAX_AG_AURA
		case eBuff_AG_Addition:
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
		case eBuff_SD_Addition:
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
		case eBuff_PartyExpBonus:
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
			}
			break;
		case eBuff_EliteScroll1:
		case eBuff_EliteScroll2:
		case eBuff_EliteScroll3:
		case eBuff_EliteScroll4:
		case eBuff_EliteScroll5:
		case eBuff_EliteScroll6:
#ifdef PSW_ADD_PC4_SCROLLITEM
		case eBuff_Scroll_Battle:
		case eBuff_Scroll_Strengthen:
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef YDG_ADD_HEALING_SCROLL
		case eBuff_Scroll_Healing:	// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
				
				if( buff == eBuff_EliteScroll1 ) { //  ���ݼӵ� ���.
					CharacterMachine->CalculateAttackSpeed();
				}
				else if( buff == eBuff_EliteScroll2 ) { // ���� ���
					CharacterMachine->CalculateDefense();
				}
				else if( buff == eBuff_EliteScroll3 ) { // ���ݷ� ���
					CharacterMachine->CalculateDamage();
				}
				else if( buff == eBuff_EliteScroll4 ) { // ���� ���
					CharacterMachine->CalculateMagicDamage();
				}
			}
			break;
		case eBuff_SecretPotion1:
		case eBuff_SecretPotion2:
		case eBuff_SecretPotion3:
		case eBuff_SecretPotion4:
		case eBuff_SecretPotion5:
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
				
				CharacterMachine->CalculateAll();
			}
			break;
			
#ifdef CSK_EVENT_CHERRYBLOSSOM
		case eBuff_CherryBlossom_Liguor:
		case eBuff_CherryBlossom_RiceCake:
		case eBuff_CherryBlossom_Petal:
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
				
				if( buff == eBuff_CherryBlossom_Petal ) { // ���ݷ� ���
					CharacterMachine->CalculateDamage();
				}
			}
			break;
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
		case eBuff_SwellOfMagicPower:
			{
				// ���� �ð� ����
				g_RegisterBuffTime(buff, bufftime);
				
				if( buff == eBuff_SwellOfMagicPower ) {		// ���� ���
					CharacterMachine->CalculateMagicDamage();
				}
			}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef PBG_ADD_SANTABUFF
			//��Ÿ��������.(�ؿ� ũ�������� �̺�Ʈ)
		case eBuff_BlessingOfXmax:
		case eBuff_CureOfSanta:
		case eBuff_SafeGuardOfSanta:
		case eBuff_StrengthOfSanta:
		case eBuff_DefenseOfSanta:
		case eBuff_QuickOfSanta:
		case eBuff_LuckOfSanta:
			{
				//�����ð�����.(30��)
				g_RegisterBuffTime(buff, bufftime);

#ifdef KJH_FIX_TALK_SANTATOWN_NPC
				char _Temp[256] = {0,};
#else // KJH_FIX_TALK_SANTATOWN_NPC
				char _Temp[32] = {0,};
#endif // KJH_FIX_TALK_SANTATOWN_NPC
				//���� ���ݷ�+���� ���
				if(buff == eBuff_BlessingOfXmax)
				{
					// 2591 "���ݷ°� ������ ��� �Ǿ����ϴ�."
					g_pChatListBox->AddText("", GlobalText[2591], SEASON3B::TYPE_SYSTEM_MESSAGE);

					//���ݷ����
					CharacterMachine->CalculateDamage();
					//�������
					CharacterMachine->CalculateDefense();
				}
				else if(buff == eBuff_StrengthOfSanta)
				{
					// 2594 "���ݷ��� %d��ŭ ��� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2594], 30);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);

					//���ݷ� ���+30
					CharacterMachine->CalculateDamage();
				}
				else if(buff == eBuff_DefenseOfSanta)
				{
					// 2595 "������ %d��ŭ ��� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2595], 100);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);

					//���� ���+100
					CharacterMachine->CalculateDefense();
				}
				else if(buff == eBuff_QuickOfSanta)
				{
					// 2598 "���ݼӵ��� %d��ŭ ��� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2598], 15);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);

					//������+15
					CharacterMachine->CalculateAttackSpeed();
				}
				else if(buff == eBuff_LuckOfSanta)
				{
					// 2599 "AGȸ���ӵ��� %d��ŭ ���� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2599], 10);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);

					//AGȸ���ӵ��� �������� �޾Ƽ� ó���Ѵ�.
				}
				else if(buff == eBuff_CureOfSanta)
				{
					// 2592 "�ִ� ������ %d��ŭ ��� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2592], 500);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);
				}
				else if(buff == eBuff_SafeGuardOfSanta)
				{
					// 2593 "�ִ� ������ %d ��ŭ ��� �Ǿ����ϴ�."
					sprintf(_Temp, GlobalText[2593], 500);
					g_pChatListBox->AddText("", _Temp, SEASON3B::TYPE_SYSTEM_MESSAGE);
				}
			}
			break;
#endif //PBG_ADD_SANTABUFF
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
		case eBuff_DuelWatch:	// ���� ����
			{
				// UI�� ��� �ݴ´�.
				g_pNewUISystem->HideAll();
				// ������������ ��ü�Ѵ�.
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_MAINFRAME);
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_BUFF_WINDOW);
				g_pNewUISystem->Show(SEASON3B::INTERFACE_DUELWATCH_MAINFRAME);
				g_pNewUISystem->Show(SEASON3B::INTERFACE_DUELWATCH_USERLIST);
			}
			break;
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
#ifdef PBG_ADD_HONOROFGLADIATORBUFFTIME
		case eBuff_HonorOfGladiator:
			{
				g_RegisterBuffTime(buff, bufftime);
			}
			break;
#endif //PBG_ADD_HONOROFGLADIATORBUFFTIME
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		case eBuff_StrongCharm:			// ������ ���� (PC�� ������)
			{
				g_RegisterBuffTime(buff, bufftime);

				// 2591 "���ݷ°� ������ ��� �Ǿ����ϴ�." // 2591, 2472
				g_pChatListBox->AddText("", GlobalText[2591], SEASON3B::TYPE_SYSTEM_MESSAGE);
				
				//���ݷ����
				CharacterMachine->CalculateDamage();
				//�������
				CharacterMachine->CalculateDefense();
			}
			break;
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef PBG_ADD_SECRETBUFF
		case eBuff_Vitality_Lowest:				// Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
		case eBuff_Vitality_Low:
		case eBuff_Vitality_Middle:
		case eBuff_Vitality_High:
		case eDeBuff_Fatigue_FirstPenalty:		// �Ƿε� �����1
		case eDeBuff_Fatigue_SecondPenalty:		// �Ƿε� �����2
			{
				// Ȱ���� ������ �����Ǹ� �Ƿε� �ð��� �����
				//if(buff != eDeBuff_Fatigue_FirstPenalty && buff != eDeBuff_Fatigue_SecondPenalty)
				//	g_FatigueTimeSystem->SetIsVitalityBuff(true);

				g_RegisterBuffTime(buff, bufftime);
			}
			break;
#endif //PBG_ADD_SECRETBUFF
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
		case eDeBuff_MoveCommandWin:
			{
				// ȥ������ȭ ���� ��� ������ 1�ܰ�(5���� �Ұ�)�� ������� ��� �̵�â ��밡��
				g_PKSystem->SetMoveBuffState(g_isCharacterBuff((&Hero->Object), eDeBuff_MoveCommandWin));
			}
			break;
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
		}
	}
	// Hero�� �ƴ� ��츸�� ������ else�� �޾� �ش�. ������ �� �ȴ�..-=-;;;
}

// ������ ����Ʈ ó���� ���⼭ �� ���ش� ������ ���� �ɶ�
void ClearBuffLogicalEffect( eBuffState buff, OBJECT* o )
{
	if(o && o == &Hero->Object)
	{
		switch( buff )
		{
		case eBuff_Hellowin1:
		case eBuff_Hellowin2:
		case eBuff_Hellowin3:
		case eBuff_Hellowin4:
		case eBuff_Hellowin5:
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
				
				// ���� ���� ĳ���Ϳ� ����
				if( buff == eBuff_Hellowin1 )
				{
					CharacterMachine->CalculateAttackSpeed();
				}
				else if( buff == eBuff_Hellowin2 )
				{
					int iBaseClass = GetBaseClass(Hero->Class);
					
					if (iBaseClass == CLASS_WIZARD || iBaseClass == CLASS_DARK || iBaseClass == CLASS_SUMMONER)
					{
						CharacterMachine->CalculateMagicDamage();
					}
					else
					{
						CharacterMachine->CalculateDamage();
					}
				}
				else if( buff == eBuff_Hellowin3 )
				{
					CharacterMachine->CalculateDefense();
				}
			}
			break;
		case eBuff_PcRoomSeal1:
		case eBuff_PcRoomSeal2:
		case eBuff_PcRoomSeal3:
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
			}
			break;
		case eBuff_Seal1:
		case eBuff_Seal2:
		case eBuff_Seal3:
		case eBuff_Seal4:
#ifdef PSW_ADD_PC4_SEALITEM
		case eBuff_Seal_HpRecovery:
		case eBuff_Seal_MpRecovery:
#endif //PSW_ADD_PC4_SEALITEM
#ifdef ASG_ADD_CS6_GUARD_CHARM
		case eBuff_GuardCharm:
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
		case eBuff_ItemGuardCharm:
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		case eBuff_AscensionSealMaster:
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		case eBuff_WealthSealMaster:
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		case eBuff_NewWealthSeal:
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef YDG_ADD_CS7_MAX_AG_AURA
		case eBuff_AG_Addition:
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
		case eBuff_SD_Addition:
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
		case eBuff_PartyExpBonus:
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
			}
			break;
		case eBuff_EliteScroll1:
		case eBuff_EliteScroll2:
		case eBuff_EliteScroll3:
		case eBuff_EliteScroll4:
		case eBuff_EliteScroll5:
		case eBuff_EliteScroll6:
#ifdef PSW_ADD_PC4_SCROLLITEM
		case eBuff_Scroll_Battle:
		case eBuff_Scroll_Strengthen:
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef YDG_ADD_HEALING_SCROLL
		case eBuff_Scroll_Healing:	// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
				
				if( buff == eBuff_EliteScroll1 ) { //  ���ݼӵ� ���.
					CharacterMachine->CalculateAttackSpeed();
				}
				else if( buff == eBuff_EliteScroll2 ) { // ���� ���
					CharacterMachine->CalculateDefense();
				}
				else if( buff == eBuff_EliteScroll3 ) { // ���ݷ� ���
					CharacterMachine->CalculateDamage();
				}
				else if( buff == eBuff_EliteScroll4 ) { // ���� ���
					CharacterMachine->CalculateMagicDamage();
				}
			}
			break;
		case eBuff_SecretPotion1:
		case eBuff_SecretPotion2:
		case eBuff_SecretPotion3:
		case eBuff_SecretPotion4:
		case eBuff_SecretPotion5:
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
				
				CharacterMachine->CalculateAll();
			}
			break;
#ifdef CSK_EVENT_CHERRYBLOSSOM
		case eBuff_CherryBlossom_Liguor:
		case eBuff_CherryBlossom_RiceCake:
		case eBuff_CherryBlossom_Petal:
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
				
				if( buff == eBuff_CherryBlossom_Petal ) { // ���ݷ� ���
					CharacterMachine->CalculateDamage();
				}
			}
			break;
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
		case eBuff_SwellOfMagicPower:
			{
				// ���� �ð� ����
				g_UnRegisterBuffTime( buff );
				
				CharacterMachine->CalculateMagicDamage();
			}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef PBG_ADD_SANTABUFF
		//��Ÿ��������.(�ؿ� ũ�������� �̺�Ʈ)
		case eBuff_BlessingOfXmax:
		case eBuff_CureOfSanta:
		case eBuff_SafeGuardOfSanta:
		case eBuff_StrengthOfSanta:
		case eBuff_DefenseOfSanta:
		case eBuff_QuickOfSanta:
		case eBuff_LuckOfSanta:
			{
				//�����ð���������.
				g_UnRegisterBuffTime( buff );
				
				//�������� ĳ���� ����.
				if(buff == eBuff_BlessingOfXmax)
				{
					CharacterMachine->CalculateDamage();
					CharacterMachine->CalculateDefense();
				}
				else if(buff == eBuff_StrengthOfSanta)
				{
					CharacterMachine->CalculateDamage();
				}
				else if(buff == eBuff_DefenseOfSanta)
				{
					CharacterMachine->CalculateDefense();
				}
				else if(buff == eBuff_QuickOfSanta)
				{
					CharacterMachine->CalculateAttackSpeed();
				}
			}
			break;
#endif //PBG_ADD_SANTABUFF
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
		case eBuff_DuelWatch:	// ���� ����
			{
				// ������������ ��ü�Ѵ�.
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_DUELWATCH_MAINFRAME);
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_DUELWATCH_USERLIST);
				g_pNewUISystem->Show(SEASON3B::INTERFACE_MAINFRAME);
				g_pNewUISystem->Show(SEASON3B::INTERFACE_BUFF_WINDOW);
			}	
			break;
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
#ifdef PBG_ADD_HONOROFGLADIATORBUFFTIME
		case eBuff_HonorOfGladiator:
			{
				g_UnRegisterBuffTime( buff );
			}
			break;
#endif //PBG_ADD_HONOROFGLADIATORBUFFTIME
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		case eBuff_StrongCharm:					// ������ ���� (PC�� ������)
			{
				g_UnRegisterBuffTime( buff );

				// ���ݷ°� ������ ����Ͽ��ش�. 
				CharacterMachine->CalculateDamage();
				CharacterMachine->CalculateDefense();
			}
			break;
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef PBG_ADD_SECRETBUFF
		case eBuff_Vitality_Lowest:				// Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
		case eBuff_Vitality_Low:
		case eBuff_Vitality_Middle:
		case eBuff_Vitality_High:
		case eDeBuff_Fatigue_FirstPenalty:		// �Ƿε� �����1
		case eDeBuff_Fatigue_SecondPenalty:		// �Ƿε� �����2
			{
				// Ȱ���� ������ ������ �Ƿε� �缳��
				//if(buff != eDeBuff_Fatigue_FirstPenalty && buff != eDeBuff_Fatigue_SecondPenalty)
				//	g_FatigueTimeSystem->SetIsVitalityBuff(false);

				g_UnRegisterBuffTime( buff );
			}
			break;
#endif //PBG_ADD_SECRETBUFF
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
		case eDeBuff_MoveCommandWin:
			{
				// ȥ������ȭ ���� ��� ������ 1�ܰ�(5���� �Ұ�)�� ������� ��� �̵�â ��밡��
				g_PKSystem->SetMoveBuffState(g_isCharacterBuff((&Hero->Object), eDeBuff_MoveCommandWin));
			}
			break;
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
		}
	}
	// Hero�� �ƴ� ��츸�� ������ else�� �޾� �ش�. ������ �� �ȴ�..-=-;;;
}

void InsertBuffPhysicalEffect( eBuffState buff, OBJECT* o )
{
	switch(buff)
	{
	case eBuff_CursedTempleProdection:
		{
			// �÷��̾� ���׸� ����� ����Ʈ
			if( o->Type == MODEL_PLAYER )
			{
				DeleteEffect( MODEL_CURSEDTEMPLE_PRODECTION_SKILL, o );
				DeleteEffect( MODEL_SHIELD_CRASH, o );
				DeleteEffect( BITMAP_SHOCK_WAVE, o );
				vec3_t  Light;
				Vector(0.3f, 0.3f, 0.8f, Light);
				CreateEffect( MODEL_CURSEDTEMPLE_PRODECTION_SKILL, o->Position, o->Angle, Light, 0, o );
				CreateEffect( MODEL_SHIELD_CRASH, o->Position, o->Angle, Light, 1, o );				
				CreateEffect ( BITMAP_SHOCK_WAVE, o->Position, o->Angle, Light, 10, o );
			}	
		}
		break;
		
	case eBuff_PhysDefense:
		{
			// �÷��̾� ���׸� ����� ����Ʈ
			if( o->Type == MODEL_PLAYER )
			{
				PlayBuffer(SOUND_SOULBARRIER);
				DeleteJoint( MODEL_SPEARSKILL, o,0);
				for ( int j = 0; j < 5; ++j)
				{
					CreateJoint( MODEL_SPEARSKILL, o->Position, o->Position, o->Angle, 0, o, 50.0f);
				}
			}
		}
		break;
		
	case eBuff_AddAG:
		{
			DeleteEffect ( BITMAP_LIGHT, o, 2 );
			CreateEffect ( BITMAP_LIGHT, o->Position, o->Angle, o->Light, 2, o );
		}
		break;
		
	case eBuff_HpRecovery:
		//case eBuff_Life:
		{
			DeleteEffect ( BITMAP_LIGHT, o, 1 );
			CreateEffect ( BITMAP_LIGHT, o->Position, o->Angle, o->Light, 1, o );
		}
		break;
	case eDeBuff_Harden:
		{
			vec3_t Angle;
			VectorCopy ( o->Angle, Angle );
			
			DeleteEffect ( MODEL_ICE, o, 1 );
			CreateEffect(MODEL_ICE,o->Position,Angle,o->Light,1,o);
			
			Angle[2] += 180.f;
			CreateEffect(MODEL_ICE,o->Position,Angle,o->Light,2,o);
		}
		break;
		
	case eDeBuff_Defense:
		{
			vec3_t Light = { 1.0f, 1.f, 1.f};
			DeleteEffect(BITMAP_SKULL,o,0);
			CreateEffect(BITMAP_SKULL,o->Position,o->Angle,Light,0,o);
			
			PlayBuffer(SOUND_BLOODATTACK,o);
		}
		break;
		
	case eDeBuff_Stun:
		{
			DeleteEffect(BITMAP_SKULL,o,5);
			
			vec3_t Angle;
			vec3_t Position;
			VectorCopy(o->Position, Position);
			Vector ( 0.f, 0.f, 90.f, Angle );
			CreateJoint ( MODEL_SPEARSKILL, Position, Position, Angle, 8, o, 30.0f );
			Position[2] -= 10.f;
			Vector ( 0.f, 0.f, 180.f, Angle );
			CreateJoint ( MODEL_SPEARSKILL, Position, Position, Angle, 8, o, 30.0f );
			Position[2] -= 10.f;
			Vector ( 0.f, 0.f, 270.f, Angle );
			CreateJoint ( MODEL_SPEARSKILL, Position, Position, Angle, 8, o, 30.0f );
		}
		break;
	case eDeBuff_NeilDOT:
		{
			g_SummonSystem.CreateDamageOfTimeEffect(AT_SKILL_SUMMON_REQUIEM, o);
		}
		break;
	case eDeBuff_SahamuttDOT:
		{
			g_SummonSystem.CreateDamageOfTimeEffect(AT_SKILL_SUMMON_EXPLOSION, o);
		}
		break;
	case eBuff_Thorns:	
		{
			// Ÿ�� 43, 44�� ���� ���� ����Ʈ�̹Ƿ� ���� �ٸ� ����� ������� ������!!!!!!
			vec3_t vLight;
			Vector(0.9f, 0.6f, 0.1f, vLight);
			CreateJoint(BITMAP_FLARE, o->Position, o->Position, o->Angle, 43, o, 50.f, 0, 0, 0, 0, vLight);
		}
		break;
		
	case eDeBuff_Blind:
		{
			// 3, 4 Ÿ���� ���� ���� ����Ʈ �ٸ������ ���� ������� ������!!!!!
			vec3_t vLight;
			Vector(1.0f, 1.0f, 1.0f, vLight);
			CreateEffect(MODEL_ALICE_BUFFSKILL_EFFECT, o->Position, o->Angle, vLight, 3, o);
		}
		break;
		
	case eDeBuff_Sleep:
		{
			// 3, 4 Ÿ���� ���� ���� ����Ʈ �ٸ������ ���� ������� ������!!!!!
			vec3_t vLight;
			Vector(0.7f, 0.1f, 0.9f, vLight);
			CreateEffect(MODEL_ALICE_BUFFSKILL_EFFECT, o->Position, o->Angle, vLight, 4, o);
		}
		break;

	case eDeBuff_AttackDown:
		{
			vec3_t vLight;
			Vector(1.4f, 0.2f, 0.2f, vLight);
			CreateEffect(BITMAP_SHINY+6, o->Position, o->Angle, vLight, 1, o, -1, 0, 0, 0, 0.5f);
			CreateEffect(BITMAP_PIN_LIGHT, o->Position, o->Angle, vLight, 1, o, -1, 0, 0, 0, 1.f);
		}
		break;
		
	case eDeBuff_DefenseDown:
		{
			vec3_t vLight;
			Vector(0.25f, 1.0f, 0.7f, vLight);
			CreateEffect(BITMAP_SHINY+6, o->Position, o->Angle, vLight, 2, o, -1, 0, 0, 0, 0.5f);
			CreateEffect(BITMAP_PIN_LIGHT, o->Position, o->Angle, vLight, 2, o, -1, 0, 0, 0, 1.f);
		}
		break;
		
#ifdef ASG_ADD_SKILL_BERSERKER
	case eBuff_Berserker:
		{
			vec3_t vLight[2];
			Vector(0.9f, 0.0f, 0.1f, vLight[0]);
			Vector(1.0f, 1.0f, 1.0f, vLight[1]);
			for (int i = 0; i < 4; ++i)
			{
				DeleteEffect(BITMAP_ORORA, o, i);
				CreateEffect(BITMAP_ORORA, o->Position, o->Angle, vLight[0], i, o);
				if (i == 2 || i == 3)
				{
					DeleteEffect(BITMAP_SPARK+2, o, i);
					CreateEffect(BITMAP_SPARK+2, o->Position, o->Angle, vLight[1], i, o);
				}
			}
			DeleteEffect(BITMAP_LIGHT_MARKS, o);
			CreateEffect(BITMAP_LIGHT_MARKS, o->Position, o->Angle, vLight[0], 0, o);
		}
		break;
#endif	// ASG_ADD_SKILL_BERSERKER
		
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	case eDeBuff_FlameStrikeDamage:
		{
			CreateEffect(BITMAP_FIRE_CURSEDLICH, o->Position, o->Angle, o->Light, 2, o);
		}
		break;
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	case eDeBuff_GiganticStormDamage:
		{
#ifdef YDG_FIX_GIGANTIC_STORM_OPTIMIZE
			DeleteEffect(BITMAP_JOINT_THUNDER, o, 0);
#endif	// YDG_FIX_GIGANTIC_STORM_OPTIMIZE
			CreateEffect(BITMAP_JOINT_THUNDER, o->Position, o->Angle, o->Light, 0, o);
		}
		break;
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
	case eDeBuff_LightningShockDamage:
		{
			CreateEffect(MODEL_LIGHTNING_SHOCK, o->Position, o->Angle, o->Light, 2, o);
		}
		break;
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	case eDeBuff_BlowOfDestruction:
		{
			CreateEffect(MODEL_ICE, o->Position, o->Angle, o->Light);
		}
		break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifndef KJH_FIX_SWELLOFMAGIC_EFFECT				// #ifndef �����Ҷ� �������ϴ� �ҽ�
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	case eBuff_SwellOfMagicPower:
		{
			// ������ �ƴҶ��� ����Ʈ���
			if( g_isCharacterBuff(o, eBuff_Cloaking) )
				break;

			vec3_t vLight;
			Vector(0.7f, 0.2f, 0.9f, vLight);
			CreateEffect( MODEL_SWELL_OF_MAGICPOWER_BUFF_EFF, o->Position, o->Angle, vLight, 0, o );
		}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#endif // KJH_FIX_SWELLOFMAGIC_EFFECT			// �����Ҷ� �������ϴ� �ҽ�
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	case eBuff_Doppelganger_Ascension:	// ���ð��� ��õ
		{
			//3������ ȿ�� ���
#ifdef YDG_MOD_DOPPELGANGER_END_SOUND
			PlayBuffer(SOUND_SKILL_BERSERKER);
#else	// YDG_MOD_DOPPELGANGER_END_SOUND
			PlayBuffer(SOUND_CHAOS_END);
#endif	// YDG_MOD_DOPPELGANGER_END_SOUND
			CreateEffect(MODEL_CHANGE_UP_EFF,o->Position,o->Angle,o->Light,2,o);
			CreateEffect(MODEL_CHANGE_UP_CYLINDER,o->Position,o->Angle,o->Light,2,o);
			CreateEffect(MODEL_INFINITY_ARROW3, o->Position, o->Angle, o->Light, 1, o);
		}
		break;
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef PBG_ADD_AURA_EFFECT
	case eBuff_SD_Addition:
		{
			DeleteEffect(MODEL_EFFECT_SD_AURA,o);
			CreateEffect(MODEL_EFFECT_SD_AURA, o->Position, o->Angle, o->Light, 0, o);
		}
		break;
	case eBuff_AG_Addition:
		{
			DeleteParticle(BITMAP_AG_ADDITION_EFFECT);

			for(int i=0; i<5; ++i)
			{
				CreateParticle(BITMAP_AG_ADDITION_EFFECT,o->Position,o->Angle,o->Light,0, 1.0f, o);
				CreateParticle(BITMAP_AG_ADDITION_EFFECT,o->Position,o->Angle,o->Light,1, 1.0f, o);
				CreateParticle(BITMAP_AG_ADDITION_EFFECT,o->Position,o->Angle,o->Light,2, 1.0f, o);
			}
		}
		break;
#endif //PBG_ADD_AURA_EFFECT
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case eBuff_Att_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 1);
			CreateEffect(BITMAP_LIGHT_RED, o->Position, o->Angle, o->Light, 1, o,-1,0,0,0,1.5f);
		}
		break;
	case eBuff_Hp_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 0);
			CreateEffect(BITMAP_LIGHT_RED, o->Position, o->Angle, o->Light, 0, o,-1,0,0,0,1.5f);
		}
		break;
	case eBuff_Def_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 2);
			CreateEffect(BITMAP_LIGHT_RED, o->Position, o->Angle, o->Light, 2, o,-1,0,0,0,1.5f);		
		}
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}
}

void ClearBuffPhysicalEffect( eBuffState buff, OBJECT* o )
{
	switch(buff)
	{
	case eBuff_CursedTempleProdection:
		{
			if( g_isCharacterBuff(o, eBuff_CursedTempleProdection ) )
			{
				DeleteEffect( MODEL_CURSEDTEMPLE_PRODECTION_SKILL, o );
			}
		}
		break;
		
	case eBuff_Defense:
		{
			DeleteJoint(MODEL_SPEARSKILL,o,4);
			DeleteJoint(MODEL_SPEARSKILL, o, 9);	//^ �渱 ����
		}
		break;
		
	case eBuff_AddAG:
		{
			DeleteEffect(BITMAP_LIGHT,o, 2);
		}
		break;
		
	case eBuff_HpRecovery:
		//case eBuff_Life:
		{
			DeleteEffect(BITMAP_LIGHT,o, 1);
		}
		break;
		
	case eBuff_PhysDefense:
		{
			if ( o->Type==MODEL_PLAYER )
			{
				DeleteJoint( MODEL_SPEARSKILL, o,0);
			}
		}
		break;
		
	case eBuff_HelpNpc:
		{
			DeleteJoint(MODEL_SPEARSKILL, o, 4);
			DeleteJoint(MODEL_SPEARSKILL, o, 9);	// ����Ʈ ����Ʈ ����
		}
		break;
		
	case eBuff_RemovalMagic:
		{
			// ����Ʈ ����
			DeleteEffect( BITMAP_LIGHT, o, 2 );
			DeleteEffect( BITMAP_LIGHT, o, 1 );
			DeleteEffect( BITMAP_SKULL, o, 0 );
			// ����Ʈ ����Ʈ ����
			DeleteJoint ( MODEL_SPEARSKILL, o, 4 );
			DeleteJoint ( MODEL_SPEARSKILL, o, 9 );
			DeleteJoint ( MODEL_SPEARSKILL, o, 0 );
		}
		break;
	case eDeBuff_CursedTempleRestraint:
		{
			if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint ) )
			{
				DeleteEffect( MODEL_CURSEDTEMPLE_RESTRAINT_SKILL, o );
			}
		}
		break;
		
	case eDeBuff_Defense:
		{
			DeleteEffect(BITMAP_SKULL,o,0);
		}
		break;
		
	case eDeBuff_Stun:
		{
			DeleteEffect(BITMAP_SKULL,o,5);
		}
		break;
		
	case eDeBuff_NeilDOT:
		{
			g_SummonSystem.RemoveDamageOfTimeEffect(AT_SKILL_SUMMON_REQUIEM, o);
		}
		break;

	case eDeBuff_SahamuttDOT:
		{
			g_SummonSystem.RemoveDamageOfTimeEffect(AT_SKILL_SUMMON_EXPLOSION, o);
		}
		break;
		
	case eBuff_Thorns:
		{
			DeleteJoint(BITMAP_FLARE, o, 43);
		}
		break;

	case eDeBuff_Sleep:
		{
			DeleteEffect(MODEL_ALICE_BUFFSKILL_EFFECT, o, 4);
		}
		break;

	case eDeBuff_Blind:
		{
			DeleteEffect(MODEL_ALICE_BUFFSKILL_EFFECT, o, 3);
		}
		break;

	case eDeBuff_AttackDown:
		DeleteEffect(BITMAP_SHINY+6, o, 1);
		DeleteEffect(BITMAP_PIN_LIGHT, o, 1);
		break;
		
	case eDeBuff_DefenseDown:
		DeleteEffect(BITMAP_SHINY+6, o, 2);
		DeleteEffect(BITMAP_PIN_LIGHT, o, 2);
		break;
		
#ifdef ASG_ADD_SKILL_BERSERKER
	case eBuff_Berserker:
		{
			for (int i = 0; i < 4; ++i)
			{
				DeleteEffect(BITMAP_ORORA, o, i);
				if (i == 2 || i == 3)
					DeleteEffect(BITMAP_SPARK+2, o, i);
			}
			DeleteEffect(BITMAP_LIGHT_MARKS, o);
		}
		break;
#endif	// ASG_ADD_SKILL_BERSERKER
		
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	case eDeBuff_FlameStrikeDamage:
		{
// 			DeleteEffect(BITMAP_FIRE_CURSEDLICH, o, 2);
		}
		break;
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	case eDeBuff_GiganticStormDamage:
		{
// 			DeleteEffect(BITMAP_JOINT_THUNDER, o, 0);
		}
		break;
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
	case eDeBuff_LightningShockDamage:
		{
// 			DeleteEffect(MODEL_LIGHTNING_SHOCK, o, 2);
		}
		break;
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	case eDeBuff_BlowOfDestruction:
		{

		}
		break;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	case eBuff_SwellOfMagicPower:
		{
			// ���� ����Ʈ�� ����.
			DeleteEffect(MODEL_SWELL_OF_MAGICPOWER_BUFF_EFF, o, 0);
		}break;
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	case eBuff_Doppelganger_Ascension:	// ���ð��� ��õ
		{
// 			DeleteEffect(BITMAP_JOINT_THUNDER, o, 0);
		}
		break;
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef PBG_ADD_AURA_EFFECT
	case eBuff_SD_Addition:
		{
			DeleteEffect(MODEL_EFFECT_SD_AURA,o);
		}
		break;
	case eBuff_AG_Addition:
		{
			DeleteParticle(BITMAP_AG_ADDITION_EFFECT);
		}
		break;
#endif //PBG_ADD_AURA_EFFECT
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case eBuff_Att_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 1);
		}
		break;
	case eBuff_Hp_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 0);
		}
		break;
	case eBuff_Def_up_Ourforces:
		{
			DeleteEffect(BITMAP_LIGHT_RED, o, 2);
		}
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}	
}

void RegisterBuff( eBuffState buff, OBJECT* o, const int bufftime )
{
	eBuffClass buffclasstype = g_IsBuffClass( buff );
	
	if( buffclasstype == eBuffClass_Count ) return;
	
	// ī����ĳ���̸� �ڱ��ڽŸ� Register �Ǿ� �Ѵ�.
	if(InChaosCastle() && (o && o != &Hero->Object)) 
	{
		return;
	}
	// �������� ����Ʈ �κ�
	InsertBuffPhysicalEffect( buff, o );
	// ���� ���� �κ�
	if( CheckExceptionBuff( buff, o, false ) )
	{
		g_CharacterRegisterBuff(o, buff);
		// ������ ����Ʈ �κ�
		InsertBuffLogicalEffect( buff, o, bufftime );
	}
}

void UnRegisterBuff( eBuffState buff, OBJECT* o )
{
	eBuffClass buffclasstype = g_IsBuffClass( buff );
	
	if( buffclasstype == eBuffClass_Count ) return;

	// �������� ����Ʈ �κ�
	ClearBuffPhysicalEffect( buff, o );
	// ���� ���� �κ�
	if( CheckExceptionBuff( buff, o, true ) )
	{
		g_CharacterUnRegisterBuff(o, buff);
		// ������ ����Ʈ �κ�
		ClearBuffLogicalEffect( buff, o );
	}
}

