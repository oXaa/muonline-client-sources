#ifndef __SOCKETCLIENTINLINE_H__
#define __SOCKETCLIENTINLINE_H__

#pragma once

#include "wsctlc.h"
#include "dsplaysound.h"
#include "zzzscene.h"
#include "zzzinterface.h"
#include "zzzinventory.h"
#include "zzzMixInventory.h"
#include "SimpleModulus.h"
#include "WSclient.h"
#ifdef MODIFY_SOCKET_PROTOCOL
#include "SocketSystem.h"
#endif	// MODIFY_SOCKET_PROTOCOL
#include "ItemAddOptioninfo.h"
extern ItemAddOptioninfo*			g_pItemAddOptioninfo;
#ifdef _DEBUG
#define SAVE_PACKET
#define PACKET_SAVE_FILE	"��Ŷ.txt"
#include "./ExternalObject/leaf/stdleaf.h"
#endif
#ifdef CSK_LH_DEBUG_CONSOLE
#include "./Utilities/Log/muConsoleDebug.h"
#endif // CSK_LH_DEBUG_CONSOLE
#include "NewUISystem.h"

#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#include "DummyAttackProtocol.h"
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN		// �ѱ���
#define PACKET_MOVE         0xD3
#define PACKET_POSITION     0xDF
#define PACKET_MAGIC_ATTACK 0x10
#define PACKET_ATTACK       0xD7
#elif SELECTED_LANGUAGE == LANGUAGE_ENGLISH		// ����
#define PACKET_MOVE         0xD4
#define PACKET_POSITION     0x15
#define PACKET_MAGIC_ATTACK 0xDB
#define PACKET_ATTACK       0x11
#elif SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES // �ʸ���
#define PACKET_MOVE         0xDD
#define PACKET_POSITION     0xDF
#define PACKET_MAGIC_ATTACK 0x11
#define PACKET_ATTACK       0xD6 
#elif SELECTED_LANGUAGE == LANGUAGE_TAIWANESE	// �븸��
#define PACKET_MOVE         0xD6
#define PACKET_POSITION     0xDF
#ifdef SEASON2_5_PACKET_MAGIC_ATTACK
#define PACKET_MAGIC_ATTACK 0xD2
#else //SEASON2_5_PACKET_MAGIC_ATTACK
#define PACKET_MAGIC_ATTACK 0xD0
#endif //SEASON2_5_PACKET_MAGIC_ATTACK
#define PACKET_ATTACK       0xDD
#elif SELECTED_LANGUAGE == LANGUAGE_CHINESE		// �߱���
#define PACKET_MOVE         0xD7
#ifdef SEASON2_5_PACKET_POSITION
#define PACKET_POSITION     0xD2
#else //SEASON2_5_PACKET_POSITION
#define PACKET_POSITION     0xD0
#endif //SEASON2_5_PACKET_POSITION
#define PACKET_MAGIC_ATTACK 0x1D
#define PACKET_ATTACK       0xD9
#elif SELECTED_LANGUAGE == LANGUAGE_JAPANESE	// �Ϻ���
#define PACKET_MOVE         0x1D
#define PACKET_POSITION     0xD6
#define PACKET_MAGIC_ATTACK 0xD7
#define PACKET_ATTACK       0xDC
#elif SELECTED_LANGUAGE == LANGUAGE_THAILAND	// �±���
#define PACKET_MOVE         0x11
#define PACKET_POSITION     0xD4
#define PACKET_MAGIC_ATTACK 0xD9
#define PACKET_ATTACK       0xD6
#elif SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE	// ��Ʈ��
#define PACKET_MOVE         0xD9
#define PACKET_POSITION     0xDC
#define PACKET_MAGIC_ATTACK 0x1D
#define PACKET_ATTACK       0x15
#endif	// SELECTED_LANGUAGE


extern CWsctlc SocketClient;
extern CSimpleModulus g_SimpleModulusCS;
extern CSimpleModulus g_SimpleModulusSC;
extern BYTE g_byPacketSerialSend;

extern int HeroKey;
extern int CurrentProtocolState;

extern int DirTable[16];

// Wsclient.cpp �� �ִ� �Լ����� �ζ��� �Լ��� �ٲ� �͵�

void BuxConvert(BYTE *Buffer,int Size);


// �˼����� ��ũ������ ���⿡ ����
__forceinline bool FindText2(char *Text,char *Token,bool First=false)
{
	int LengthToken = (int)strlen(Token);
	int Length = (int)strlen(Text)-LengthToken;
	if(First)
		Length = 0;
	if(Length < 0)
		return false;
	for(int i=0;i<=Length;i++)
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

extern CWsctlc * g_pSocketClient;

// ��Ŷ ������ �Լ�
__forceinline int SendPacket( char *buf, int len, BOOL bEncrypt = FALSE, BOOL bForceC4 = FALSE)
{
#ifdef SAVE_PACKET
	LPPHEADER_DEFAULT_SUBCODE pData = ( LPPHEADER_DEFAULT_SUBCODE)buf;
	std::string timeString;
	leaf::GetTimeString(timeString);
	DebugAngel_Write( PACKET_SAVE_FILE, "%s Send \t0x%02X 0x%02X (size = %d)\r\n", timeString.c_str(), pData->Header.HeadCode, pData->SubCode, len);
#endif

	if ( !bEncrypt)
	{
#ifdef ACC_PACKETSIZE
		g_iTotalPacketSend += len;
#endif
		return ( g_pSocketClient->sSend( buf, len));
	}

	BYTE byBuffer[MAX_SPE_BUFFERSIZE_];
	memcpy( byBuffer, buf, len);
	byBuffer[len] = rand() % 256;
	// ��ȣȭ �ؼ� ������
	int iSkip = ( byBuffer[0] == 0xC1) ? 2 : 3;
	// �ø����� �߰��ؼ� ��Ŷ ���簡 �ȵǰ� �ϱ�
	byBuffer[iSkip - 1] = g_byPacketSerialSend++;
	--iSkip;

	PBMSG_ENCRYPTED bc;
	PWMSG_ENCRYPTED wc;
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
	int iSize = g_SessionCryptorCS.Encrypt( (int)g_pSocketClient->GetSocket(), NULL, byBuffer + iSkip, len - iSkip);
#else 
	int iSize = g_SimpleModulusCS.Encrypt( NULL, byBuffer + iSkip, len - iSkip);
#endif // PKD_ADD_ENHANCED_ENCRYPTION
	
	if ( iSize < 256 && bForceC4 == FALSE)
	{
		int iLength = iSize + 2;

		bc.Code = 0xC3;
		bc.Size = iLength;
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
		g_SessionCryptorCS.Encrypt( (int)g_pSocketClient->GetSocket(), bc.byBuffer, byBuffer + iSkip, len - iSkip);		
#else // PKD_ADD_ENHANCED_ENCRYPTION
		g_SimpleModulusCS.Encrypt( bc.byBuffer, byBuffer + iSkip, len - iSkip);
#endif // PKD_ADD_ENHANCED_ENCRYPTION
		assert( iSize < 256);

#ifdef ACC_PACKETSIZE
		g_iTotalPacketSend += iLength;
#endif
		return ( g_pSocketClient->sSend( ( char*)&bc, iLength));
	}
	else
	{
		int iLength = iSize + 3;

		wc.Code = 0xC4;
		wc.SizeL = iLength % 256;
		wc.SizeH = iLength / 256;

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
		g_SessionCryptorCS.Encrypt( (int)g_pSocketClient->GetSocket(), wc.byBuffer, byBuffer + iSkip, len - iSkip);
#else // PKD_ADD_ENHANCED_ENCRYPTION
		g_SimpleModulusCS.Encrypt( wc.byBuffer, byBuffer + iSkip, len - iSkip);
#endif // PKD_ADD_ENHANCED_ENCRYPTION

		assert( iSize <= MAX_SPE_BUFFERSIZE_);
#ifdef ACC_PACKETSIZE
		g_iTotalPacketSend += iLength;
#endif
		return ( g_pSocketClient->sSend( ( char*)&wc, iLength));
	}
}


#include "StreamPacketEngine.h"



#ifdef USE_SELFCHECKCODE

// ------------ self check �� ��� -->>

// �Լ� �� ǥ��
#define END_OF_FUNCTION( pos)\
	_asm { jmp pos };\
	_asm { __emit 0xF1 }\
	_asm { __emit 0xF2 }\
	_asm { __emit 0xA3 }\
	_asm { __emit 0x53 }\
	_asm { __emit 0x8A }\
	_asm { __emit 0x72 }

// �Լ� ���� ���
#ifdef _DEBUG
#define GetStartOfFunction( Address, Function)\
{\
	BYTE *pFunc = ( BYTE*)Function;\
	DWORD dwValue;\
	memcpy( &dwValue, pFunc + 1, 4);\
	dwValue += 5;\
	Address = ( BYTE*)( ( DWORD)Function + dwValue);\
}
#else
#define GetStartOfFunction( Address, Function)\
Address = ( BYTE*)Function;
#endif

// �Լ� �� ���
inline BYTE* GetEndOfFunction( BYTE *pbyStart)
{
	BYTE byCompare[] = { 0xF1, 0xF2, 0xA3, 0x53, 0x8A, 0x72};
	int iCompare = 0;
	for ( BYTE *pbySeek = pbyStart; pbySeek < pbyStart+(1024*128); ++pbySeek)
	{
		if ( *pbySeek == byCompare[iCompare])
		{
			if ( ++iCompare >= 6)
			{
				return ( pbySeek - 5);
			}
		}
		else
		{
			iCompare = 0;
		}
	}
	return ( pbySeek);
}

// CRC üũ

extern BYTE g_byNextFuncCrcCheck;
extern DWORD g_dwLatestFuncCrcCheck;
#define DELAY_FOR_FUNCCRCCHECK		( 6000)
//#define DELAY_FOR_FUNCCRCCHECK		( 1000)

#define SendCrcOfFunction( p_Index, p_Next, p_Function, p_Key)\
{\
	if ( g_byNextFuncCrcCheck == p_Index && ( abs( GetTickCount() - g_dwLatestFuncCrcCheck) > DELAY_FOR_FUNCCRCCHECK))\
	{\
		BYTE *pFuncPtr;\
		GetStartOfFunction( pFuncPtr, p_Function);\
		static DWORD s_dwSize = 0;\
		if ( 0 == s_dwSize)\
		{\
			BYTE *pFuncEnd = GetEndOfFunction( pFuncPtr);\
			s_dwSize = ( DWORD)pFuncEnd - ( DWORD)pFuncPtr;\
		}\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x72);\
		spe << ( BYTE)( p_Index);\
		DWORD dwResult = GenerateCheckSum2( pFuncPtr, s_dwSize, p_Key);\
		spe << ( DWORD)( dwResult);\
		spe << ( BYTE)( rand());\
		spe.Send( TRUE);\
		g_byNextFuncCrcCheck = p_Next;\
		g_dwLatestFuncCrcCheck = GetTickCount();\
	}\
}

// ------------ self check �� ��� <<--
#else

#define END_OF_FUNCTION( pos)	;
#define SendCrcOfFunction( p_Index, p_Next, p_Function, p_Key)	;

#endif	// USE_SELFCHECKCODE



///////////////////////////////////////////////////////////////////////////////
// ���� ����
///////////////////////////////////////////////////////////////////////////////

#define SendRequestServerList()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF4);\
	BYTE byData = ( BYTE)0x06;\
	spe.AddData( &byData, 1, FALSE);\
	spe.Send();\
}

#define SendRequestServerAddress( p_Index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF4);\
	BYTE byData = ( BYTE)0x03;\
	spe.AddData( &byData, 1, FALSE);\
	WORD Index = ( WORD)( p_Index);\
	spe.AddData( &Index, 2, FALSE);\
	spe.Send();\
	g_pChatListBox->AddText("",GlobalText[470],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[471],SEASON3B::TYPE_SYSTEM_MESSAGE);\
}

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
#define SendRequestServerList2()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF4);\
	BYTE byData = ( BYTE)0x06;\
	spe.AddData( &byData, 1, TRUE);\
	spe.Send();\
}

#define SendRequestServerAddress2( p_Index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF4);\
	BYTE byData = ( BYTE)0x03;\
	spe.AddData( &byData, 1, TRUE);\
	WORD Index = ( WORD)( p_Index);\
	spe.AddData( &Index, 2, TRUE);\
	spe.Send();\
	g_pChatListBox->AddText("",GlobalText[470],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[471],SEASON3B::TYPE_SYSTEM_MESSAGE);\
}
#endif // PKD_ADD_ENHANCED_ENCRYPTION

///////////////////////////////////////////////////////////////////////////////
// ����, ���� ����
///////////////////////////////////////////////////////////////////////////////

extern int  LogIn;
extern char LogInID[MAX_ID_SIZE+1];

extern bool First;
extern int FirstTime;
extern BOOL g_bGameServerConnected;

__forceinline void SendCheck( void)
{	
	if ( !g_bGameServerConnected)
	{
		return;
	}

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "SendCheck");
#endif // CONSOLE_DEBUG

	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x0E);
	DWORD dwTick = GetTickCount();
	spe.AddNullData( 1);
	spe << dwTick;
	//����

	if(CharacterAttribute->Ability & ABILITY_FAST_ATTACK_SPEED)
	{
		spe << ( WORD)( CharacterAttribute->AttackSpeed-20) << ( WORD)( CharacterAttribute->MagicSpeed-20);
	}
	else if(CharacterAttribute->Ability & ABILITY_FAST_ATTACK_SPEED2)
	{
		spe << ( WORD)( CharacterAttribute->AttackSpeed-20) << ( WORD)( CharacterAttribute->MagicSpeed-20);
	}
	else
	{
		spe << ( WORD)( CharacterAttribute->AttackSpeed) << ( WORD)( CharacterAttribute->MagicSpeed);
	}
	spe.Send( TRUE);

	if(!First)
	{
		First = true;
		FirstTime = dwTick;
	}
	hanguo_check1();
}

// üũ�� ������
#define SendCheckSum( dwCheckSum)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x03);\
	spe.AddNullData( 1);\
	spe << ( DWORD)( dwCheckSum);\
	spe.Send( TRUE);\
	hanguo_check2();\
}

#define SendHackingChecked( byType, byParam)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x03 << ( BYTE)( byType) << ( BYTE)( byParam);\
	spe.Send( TRUE);\
}

extern BYTE Version[SIZE_PROTOCOLVERSION];
extern BYTE Serial[SIZE_PROTOCOLSERIAL+1];

#ifdef LEM_ADD_GAMECHU
#define SendRequestLogIn_GameChu( szAuth, iAuthLen, szStat )\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+1] = { 0, };\
	char lpszPass[MAX_ID_SIZE+1] = { 0, };\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_ID_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_ID_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
		spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
		spe << Serial[i];\
 	char lpszAuth[MAX_GAMECHU_AUTHINFO];\
	char lpszStat[MAX_GAMECHU_USERINFO+1];\
	ZeroMemory( lpszAuth, MAX_GAMECHU_AUTHINFO);\
	ZeroMemory( lpszStat, MAX_GAMECHU_USERINFO+1);\
	strcpy( lpszAuth, szAuth );\
	strcpy( lpszStat, szStat );\
	spe.AddData( lpszStat, MAX_GAMECHU_USERINFO+1 );\
	spe.AddData( lpszAuth, iAuthLen+1 );\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#endif // LEM_ADD_GAMECHU
#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD	// ��й�ȣ �ڸ��� 10->12�� ���� ����



#ifdef _VS2008PORTING
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+1];\
	char lpszPass[MAX_PASSWORD_SIZE+1];\
	ZeroMemory( lpszID, MAX_ID_SIZE+1);\
	ZeroMemory( lpszPass, MAX_PASSWORD_SIZE+1);\
	memcpy( lpszID, p_lpszID, MAX_ID_SIZE );\
	memcpy( lpszPass, p_lpszPassword, MAX_PASSWORD_SIZE);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_PASSWORD_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_PASSWORD_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(int i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#else // _VS2008PORTING
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+1];\
	char lpszPass[MAX_PASSWORD_SIZE+1];\
	ZeroMemory( lpszID, MAX_ID_SIZE+1);\
	ZeroMemory( lpszPass, MAX_PASSWORD_SIZE+1);\
	memcpy( lpszID, p_lpszID, MAX_ID_SIZE );\
	memcpy( lpszPass, p_lpszPassword, MAX_PASSWORD_SIZE);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_PASSWORD_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_PASSWORD_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#endif // _VS2008PORTING

#else	// LDS_MODIFY_CHAR_LENGTH_USERPASSWORD

#ifdef _VS2008PORTING
#ifdef LDK_MOD_PASSWORD_LENGTH_20
//�۷ι� ���п�
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+1];\
	char lpszPass[MAX_PASSWORD_SIZE+1];\
	ZeroMemory( lpszID, MAX_ID_SIZE+1);\
	ZeroMemory( lpszPass, MAX_PASSWORD_SIZE+1);\
	strncpy(lpszID, p_lpszID, MAX_ID_SIZE);\
	strncpy(lpszPass, p_lpszPassword, MAX_PASSWORD_SIZE);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_PASSWORD_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_PASSWORD_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(int i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#else //LDK_MOD_PASSWORD_LENGTH_20
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE];\
	char lpszPass[MAX_ID_SIZE];\
	ZeroMemory( lpszID, MAX_ID_SIZE);\
	ZeroMemory( lpszPass, MAX_ID_SIZE);\
	strcpy( lpszID, p_lpszID);\
	strcpy( lpszPass, ( p_lpszPassword));\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_ID_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_ID_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(int i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#endif //LDK_MOD_PASSWORD_LENGTH_20
#else // _VS2008PORTING
#ifdef LDK_MOD_PASSWORD_LENGTH_20
//�۷ι� ���п�
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+1];\
	char lpszPass[MAX_PASSWORD_SIZE+1];\
	ZeroMemory( lpszID, MAX_ID_SIZE+1);\
	ZeroMemory( lpszPass, MAX_PASSWORD_SIZE+1);\
	strncpy(lpszID, p_lpszID, MAX_ID_SIZE);\
	strncpy(lpszPass, p_lpszPassword, MAX_PASSWORD_SIZE);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_PASSWORD_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_PASSWORD_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
		spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
		spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#else //LDK_MOD_PASSWORD_LENGTH_20
#define SendRequestLogIn( p_lpszID, p_lpszPassword)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE];\
	char lpszPass[MAX_ID_SIZE];\
	ZeroMemory( lpszID, MAX_ID_SIZE);\
	ZeroMemory( lpszPass, MAX_ID_SIZE);\
	strcpy( lpszID, p_lpszID);\
	strcpy( lpszPass, ( p_lpszPassword));\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPass,MAX_ID_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPass, MAX_ID_SIZE);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[472],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#endif //LDK_MOD_PASSWORD_LENGTH_20
#endif // _VS2008PORTING

#endif	// LDS_MODIFY_CHAR_LENGTH_USERPASSWORD

#ifdef LJH_ADD_ONETIME_PASSWORD
///////////////////////////////////////////////////////////////////////////////
// OneTime Password ����
///////////////////////////////////////////////////////////////////////////////
#define SendRequestOTP( p_lpszID, p_lpszPW, p_lpszOTP, p_byOTPBtnType)\
{\
	pre_send( g_hInst);\
	LogIn = 1;\
	strcpy(LogInID, ( p_lpszID));\
	CurrentProtocolState = REQUEST_LOG_IN;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF1);\
	spe << ( BYTE)0x05;\
	char lpszID[MAX_ID_SIZE];\
	char lpszPW[MAX_ID_SIZE];\
	char lpszOTP[MAX_ONETIME_PASSWORD_SIZE];\
	ZeroMemory( lpszID, MAX_ID_SIZE);\
	ZeroMemory( lpszPW, MAX_ID_SIZE);\
	ZeroMemory( lpszOTP, MAX_ONETIME_PASSWORD_SIZE);\
	strcpy( lpszID, p_lpszID);\
	strcpy( lpszPW, ( p_lpszPW));\
	strcpy( lpszOTP, ( p_lpszOTP));\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszPW,MAX_ID_SIZE);\
	BuxConvert(( BYTE*)lpszOTP,MAX_ONETIME_PASSWORD_SIZE);\
	spe.AddData( lpszID, MAX_ID_SIZE);\
	spe.AddData( lpszPW, MAX_ID_SIZE);\
	spe << GetTickCount();\
	int i = 0;\
	for(i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe << ( BYTE)p_byOTPBtnType;\
	spe.AddData( lpszOTP, MAX_ONETIME_PASSWORD_SIZE);\
	spe.Send( TRUE);\
	g_pChatListBox->AddText("",GlobalText[473],SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check3();\
}
#endif //LJH_ADD_ONETIME_PASSWORD

extern bool LogOut;

__forceinline void SendRequestLogOut(int Flag)
{
	pre_send( g_hInst);
	LogOut = true;
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0xF1);
	spe << ( BYTE)0x02 << ( BYTE)Flag;
	spe.Send( TRUE);

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0xF1����[SendRequestLogOut]");
#endif // CONSOLE_DEBUG
}

#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
extern char Password[MAX_PASSWORD_SIZE+1];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD
extern char Password[MAX_ID_SIZE+1];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD

extern char QuestionID[MAX_ID_SIZE+1];
extern char Question[31];

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define SendRequestCharactersList( byLanguage)\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_CHARACTERS_LIST;\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0xF3);\
	spe << (BYTE)0x00;\
	spe << (BYTE)byLanguage;\
	spe.Send();\
	hanguo_check5();\
}
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define SendRequestCharactersList()\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_CHARACTERS_LIST;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x00;\
	spe.Send();\
	hanguo_check5();\
}
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#define SendRequestCreateCharacter( p_ID, p_Class, p_Skin)\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_CREATE_CHARACTER;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x01;\
	spe.AddData( ( p_ID), strlen( p_ID));\
	spe.AddNullData( MAX_ID_SIZE - strlen( p_ID));\
	spe << ( BYTE)( (( p_Class)<<4)+( p_Skin));\
	spe.Send();\
	hanguo_check6();\
}

#ifdef LDK_MOD_PASSWORD_LENGTH_20
//�۷ι� ���п�
#define SendRequestDeleteCharacter( p_ID, p_Resident)\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_DELETE_CHARACTER;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x02;\
	spe.AddData( ( p_ID), strlen( p_ID));\
	spe.AddNullData( MAX_ID_SIZE - strlen( p_ID));\
	spe.AddData( ( p_Resident), 20);\
	spe.Send();\
	hanguo_check7();\
}
#else //LDK_MOD_PASSWORD_LENGTH_20
#define SendRequestDeleteCharacter( p_ID, p_Resident)\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_DELETE_CHARACTER;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x02;\
	spe.AddData( ( p_ID), strlen( p_ID));\
	spe.AddNullData( MAX_ID_SIZE - strlen( p_ID));\
	spe.AddData( ( p_Resident), 10);\
	spe.Send();\
	hanguo_check7();\
}
#endif //LDK_MOD_PASSWORD_LENGTH_20

#define SendRequestJoinMapServer( p_ID)\
{\
	pre_send( g_hInst);\
	CurrentProtocolState = REQUEST_JOIN_MAP_SERVER;\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x03;\
	spe.AddData( ( p_ID), strlen( ( p_ID)));\
	spe.AddNullData( MAX_ID_SIZE - strlen( ( p_ID)));\
	spe.Send();\
}

extern BOOL g_bWhileMovingZone;	// �� ���̸� ������ ���̴�.
extern DWORD g_dwLatestZoneMoving;	// ���� �ֱٿ� �� ���̸� ���� ����

#define SendRequestFinishLoading()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x12;\
	spe.Send();\
\
	g_dwLatestZoneMoving = GetTickCount();\
	g_bWhileMovingZone = FALSE;\
	hanguo_check9();\
}

///////////////////////////////////////////////////////////////////////////////
// ä��, �̵�
///////////////////////////////////////////////////////////////////////////////

extern int  ChatTime;
extern char ChatText[256];

__forceinline void SendChat(const char* Text)
{
	if(ChatTime > 50)
	{
		return;
	}
	else if(ChatTime > 0)
	{
		if(strcmp(ChatText,Text)==NULL) return;
	}
	strcpy(ChatText,Text);
	ChatTime = 70;

    if(FindText2(Hero->ID,"webzen"))
	{
		BOOL bReturn = TRUE;
		char *lspzCommand[2] = { "/", "!"};
		for ( int i = 0; i < sizeof ( lspzCommand) / sizeof ( char*); i++)
		{
			if ( 0 == strncmp( Text, lspzCommand[i], strlen( lspzCommand[i])))
			{
				bReturn = FALSE;
				break;
			}
		}

		if ( bReturn)
		{
			return;
		}
	}
    //  ����.
    if ( Hero->Dead>0 )
    {
        //  /�̵� ��ɾ� ��.
	    if ( strlen(GlobalText[260]) > 0 && !strncmp( Text, GlobalText[260], strlen(GlobalText[260]) ) )
	    {
            return;
	    }
    }
    else if ( Text[0]=='/' )
    {
		//  �Ӹ� ��ɾ� äũ.
        if( strlen(GlobalText[264]) > 0 && !strncmp( Text, GlobalText[264], strlen( GlobalText[264] ) ) )
        {
			g_pChatInputBox->SetBlockWhisper(true);
			g_pChatListBox->AddText("", GlobalText[267], SEASON3B::TYPE_SYSTEM_MESSAGE);
            return;
        }
        else if( strlen(GlobalText[265]) && !strncmp( Text, GlobalText[265], strlen( GlobalText[265] ) ) )
        {
			g_pChatInputBox->SetBlockWhisper(false);
			g_pChatListBox->AddText("", GlobalText[268], SEASON3B::TYPE_SYSTEM_MESSAGE);
            return;
        }
    }

	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x00);
	spe.AddData( Hero->ID, MAX_ID_SIZE);
	spe.AddData( (void*)Text, min( strlen( Text) + 1, MAX_CHAT_SIZE));
	spe.Send();
	hanguo_check10();
}

extern char ChatWhisperID[MAX_ID_SIZE+1];

#define SendChatWhisper( p_TargetID, p_Text)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x02);\
		spe.AddData( ( p_TargetID), MAX_ID_SIZE);\
		spe.AddData( ( p_Text), min( strlen( p_Text) + 1, MAX_CHAT_SIZE));\
		spe.Send();\
\
		memcpy(ChatWhisperID, ( p_TargetID),MAX_ID_SIZE);\
		ChatWhisperID[MAX_ID_SIZE] = NULL;\
		hanguo_check11();\
	}\
}

#define SendPosition( p_x, p_y)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, PACKET_POSITION );\
	spe << ( BYTE)( p_x) << ( BYTE)( p_y);\
	spe.Send();\
	hanguo_check12();\
}


extern int MoveCount;

__forceinline void SendCharacterMove(unsigned short Key,float Angle,unsigned char PathNum,unsigned char *PathX,unsigned char *PathY,unsigned char TargetX,unsigned char TargetY)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(Key == 0)
		return;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(PathNum < 1) 
		return;

	pre_send( g_hInst);

	if(PathNum >= MAX_PATH_FIND) 
	{
		PathNum = MAX_PATH_FIND-1;
	}

	CStreamPacketEngine spe;
	spe.Init( 0xC1, PACKET_MOVE );
	spe << PathX[0] << PathY[0];
	BYTE Path[8];
	ZeroMemory( Path, 8);
	BYTE Dir = 0;
	for(int i=1; i<PathNum; i++)
	{
		Dir = 0;
		for(int j=0; j<8; j++)
		{
			if(DirTable[j*2] == (PathX[i]-PathX[i-1]) && DirTable[j*2+1]==(PathY[i]-PathY[i-1]))
			{
				Dir = j;
				break;
			}
		}
		
		if(i%2 == 1)
		{
			Path[(i+1)/2]  = Dir<<4;
		}
		else
		{
			Path[(i+1)/2] += Dir;
		}
	}
	if(PathNum == 1)
	{
		Path[0] = ((BYTE)((Angle+22.5f)/360.f*8.f+1.f)%8) << 4;
	}
	else
	{
		for(int j=0; j<8; j++)
		{
			if(DirTable[j*2]==(TargetX-PathX[PathNum-1]) && DirTable[j*2+1]==(TargetY-PathY[PathNum-1]))
			{
				Dir = j;
				break;
			}
		}
		Path[0] = Dir << 4;
	}
	Path[0] += (BYTE)(PathNum - 1);
	spe.AddData( Path, 1 + (PathNum)/2);
	spe.Send();

#ifdef CONSOLE_DEBUG
	//g_ConsoleDebug->Write(MCD_SEND, "0x10����[SendCharacterMove(%d)]", MoveCount++);
#endif // CONSOLE_DEBUG
}

#define SendRequestAction( p_Action, p_Angle)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x18);\
	spe << ( BYTE)( p_Angle) << ( BYTE)( p_Action);\
	spe.Send();\
	hanguo_check1();\
}


///////////////////////////////////////////////////////////////////////////////
// ����, ����
///////////////////////////////////////////////////////////////////////////////

#ifdef KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT					// #ifndef
#define SendRequestAttack( p_Key, p_Dir)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, PACKET_ATTACK);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0);\
			spe2.Send();\
			hanguo_check2();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_ATTACK);\
		spe << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir) << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send();\
		hanguo_check2();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestAttack(int p_Key,int p_Dir)
{
    if(!FindText2(Hero->ID,"webzen"))
	{
		g_DummyAttackChecker->AddSkillCount();
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{
			pre_send( g_hInst);
			CStreamPacketEngine spe2;
			spe2.Init( 0xC1, PACKET_ATTACK);
			DWORD dwDummy;
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
			spe2 << (DWORD)dwDummy << (BYTE)(0);
			spe2.Send();
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
			hanguo_check2();
			g_DummyAttackChecker->InitSkillCount();
			g_DummyAttackChecker->AddSkillCount();
		}
		pre_send( g_hInst);
		CStreamPacketEngine spe;
		spe.Init( 0xC1, PACKET_ATTACK);
		BYTE btSkillSerial = g_DummyAttackChecker->GetSerial();
		spe << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir) << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)btSkillSerial;
		spe.Send();
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "0x15����[SendRequestAttack(%d)", p_Key);
		g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d, SkillSerial : %d", 
			g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq(), btSkillSerial);
#endif // CONSOLE_DEBUG
		hanguo_check2();
	}
}
#endif // ENABLE_EDIT
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT					// #ifndef
#define SendRequestAttack( p_Key, p_Dir)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, PACKET_ATTACK);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy;\
			spe2.Send();\
			hanguo_check2();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_ATTACK);\
		spe << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir) << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send();\
		hanguo_check2();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestAttack(int p_Key,int p_Dir)
{
    if(!FindText2(Hero->ID,"webzen"))
	{
		g_DummyAttackChecker->AddSkillCount();
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{
			pre_send( g_hInst);
			CStreamPacketEngine spe2;
			spe2.Init( 0xC1, PACKET_ATTACK);
			DWORD dwDummy;
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
			spe2 << (DWORD)dwDummy;
			spe2.Send();
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
			hanguo_check2();
			g_DummyAttackChecker->InitSkillCount();
			g_DummyAttackChecker->AddSkillCount();
		}
		pre_send( g_hInst);
		CStreamPacketEngine spe;
		spe.Init( 0xC1, PACKET_ATTACK);
		spe << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir) << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff);
		spe.Send();
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "0x15����[SendRequestAttack(%d)", p_Key);
		g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d", g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq());
#endif // CONSOLE_DEBUG
		hanguo_check2();
	}
}
#endif // ENABLE_EDIT
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#else // KJH_ADD_DUMMY_SKILL_PROTOCOL
#define SendRequestAttack( p_Key, p_Dir)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_ATTACK);\
		spe << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir) << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send();\
		hanguo_check2();\
	}\
}
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
#else // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#define SendRequestAttack( p_Key, p_Dir)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_ATTACK);\
		spe << ( BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff) << ( BYTE)AT_ATTACK1 << ( BYTE)( p_Dir);\
		spe.Send();\
		hanguo_check2();\
	}\
}
#endif // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK

//��������

extern DWORD g_dwLatestMagicTick;

#ifdef KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef _DEBUG
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
#else // _DEBUG
__forceinline void SendRequestMagic(int Type,int Key)
{
	if( !IsCanBCSkill(Type) )
		return;
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL		// ��ũ���̵� ��ų ������ �ɸ��� �ȵ�
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
	{
		g_DummyAttackChecker->AddSkillCount();
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
		{
			pre_send( g_hInst);
			CStreamPacketEngine spe2;
			spe2.Init( 0xC1, 0x19);
			DWORD dwDummy;
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0);
			spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
			hanguo_check3();
			g_DummyAttackChecker->InitSkillCount();
			g_DummyAttackChecker->AddSkillCount();
		}
		pre_send( g_hInst);
		g_dwLatestMagicTick = GetTickCount();
		CStreamPacketEngine spe;
				
		WORD p_Type = (WORD)Type;
		spe.Init( 0xC1, 0x19);
		BYTE btSkillSerial = (BYTE)g_DummyAttackChecker->GetSerial();
		spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type)) << (BYTE)(0) << ( BYTE)( Key>>8) << ( BYTE)( Key&0xff) << (BYTE)btSkillSerial;
		spe.Send( TRUE);
				
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "0x19����[SendRequestMagic(%d %d)]", Type, Key);
		g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d, SkillSerial : %d", 
			g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq(), btSkillSerial);
#endif // CONSOLE_DEBUG
				
			hanguo_check3();
	}
}
#endif //_DEBUG
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef _DEBUG
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 ||abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x19);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check3();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
#else // _DEBUG
__forceinline void SendRequestMagic(int Type,int Key)
{
	if( !IsCanBCSkill(Type) )
		return;
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL		// ��ũ���̵� ��ų ������ �ɸ��� �ȵ�
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
	{
		g_DummyAttackChecker->AddSkillCount();
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
		{
			pre_send( g_hInst);
			CStreamPacketEngine spe2;
			spe2.Init( 0xC1, 0x19);
			DWORD dwDummy;
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
			spe2 << (DWORD)dwDummy << (BYTE)(0);
			spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
			g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
			hanguo_check3();
			g_DummyAttackChecker->InitSkillCount();
			g_DummyAttackChecker->AddSkillCount();
		}
		pre_send( g_hInst);
		g_dwLatestMagicTick = GetTickCount();
		CStreamPacketEngine spe;
				
		WORD p_Type = (WORD)Type;
		spe.Init( 0xC1, 0x19);
		spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type)) << (BYTE)(0) << ( BYTE)( Key>>8) << ( BYTE)( Key&0xff);
		spe.Send( TRUE);
				
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "0x19����[SendRequestMagic(%d %d)]", Type, Key);
		g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d]", g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq());
#endif // CONSOLE_DEBUG
				
			hanguo_check3();
	}
}
#endif //_DEBUG
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#else // KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifndef _DEBUG
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
#else // _DEBUG
__forceinline void SendRequestMagic(int Type,int Key)
{
	if( !IsCanBCSkill(Type) )
		return;
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
	{
		pre_send( g_hInst);
		g_dwLatestMagicTick = GetTickCount();
		CStreamPacketEngine spe;
			
		WORD p_Type = (WORD)Type;
		spe.Init( 0xC1, 0x19);
		spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type)) << (BYTE)(0) << ( BYTE)( Key>>8) << ( BYTE)( Key&0xff);
		spe.Send( TRUE);
			
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "0x19����[SendRequestMagic(%d %d)]", Type, Key);
#endif // CONSOLE_DEBUG
			
		hanguo_check3();
	}
}
#endif //_DEBUG
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
#else // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifndef _DEBUG
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
	if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || p_Type==263 || p_Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#else //PBG_ADD_NEWCHAR_MONK_SKILL
#define SendRequestMagic( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen") && ( p_Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))\
	{\
		pre_send( g_hInst);\
		g_dwLatestMagicTick = GetTickCount();\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x19);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
#else // _DEBUG
__forceinline void SendRequestMagic(int Type,int Key)
{
	if( !IsCanBCSkill(Type) )
		return;
#ifdef _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( (int)(GetTickCount() - g_dwLatestMagicTick)) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#else // _VS2008PORTING
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!FindText2(Hero->ID,"webzen") && ( Type==40 || Type==263 || Type==261 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#else //PBG_ADD_NEWCHAR_MONK_SKILL
    if(!FindText2(Hero->ID,"webzen") && ( Type==40 || abs( GetTickCount() - g_dwLatestMagicTick) > 300 ))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#endif // _VS2008PORTING
	{
		pre_send( g_hInst);
		g_dwLatestMagicTick = GetTickCount();
		CStreamPacketEngine spe;

		WORD p_Type = (WORD)Type;
		spe.Init( 0xC1, 0x19);
		spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))<< ( BYTE)( Key>>8) << ( BYTE)( Key&0xff);
		spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x19����[SendRequestMagic(%d %d)]", Type, Key);
#endif // CONSOLE_DEBUG

		hanguo_check3();
	}
}
#endif //_DEBUG
#endif // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK


#define SendRequestCancelMagic( p_Type, p_Key)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x1B);\
	WORD Type = (WORD)p_Type;\
	spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type))<< ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
	spe.Send( TRUE);\
}

//��������
#ifdef PBG_FIX_DARK_FIRESCREAM_HACKCHECK
BYTE MakeSkillSerialNumber(BYTE * pSerialNumber);
#endif //PBG_FIX_DARK_FIRESCREAM_HACKCHECK

#ifdef KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT
#define SendRequestMagicAttack( p_Type, p_x, p_y, p_Serial, p_Count, p_Key, p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, PACKET_MAGIC_ATTACK );\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check5();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_MAGIC_ATTACK );\
		WORD Type = (WORD)p_Type;\
		spe << (BYTE)(p_x) << (BYTE)(p_y) << (BYTE)MakeSkillSerialNumber(&p_Serial) << (BYTE)(p_Count) << (BYTE)(HIBYTE(Type)) << (BYTE)(LOBYTE(Type)) << (BYTE)g_DummyAttackChecker->GetSerial();\
		int *pKey = ( int*)( p_Key);\
		for (int i=0;i<p_Count;i++)\
		{\
			spe << ( BYTE)p_SkillSerial;\
			spe << ( BYTE)(pKey[i]>>8) << ( BYTE)( pKey[i]&0xff);\
		}\
		spe.Send( TRUE);\
		hanguo_check5();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicAttack(int Type,int x,int y,BYTE Serial,int Count,int *Key, WORD SkillSerial)
{
    if(FindText2(Hero->ID,"webzen")) return;
	
	g_DummyAttackChecker->AddSkillCount();
	if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
	{
		pre_send( g_hInst);
		CStreamPacketEngine spe2;
		spe2.Init( 0xC1, PACKET_MAGIC_ATTACK );
		DWORD dwDummy;
		g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
		spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);
		spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
		hanguo_check5();
		g_DummyAttackChecker->InitSkillCount();
		g_DummyAttackChecker->AddSkillCount();
	}
	
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	
	spe.Init( 0xC1, PACKET_MAGIC_ATTACK);
	BYTE btSkillSerial = g_DummyAttackChecker->GetSerial();
	spe << (BYTE)x << (BYTE)y << (BYTE)MakeSkillSerialNumber(&Serial) << (BYTE)Count << (BYTE)(HIBYTE(p_Type)) << (BYTE)(LOBYTE(p_Type)) << (BYTE)btSkillSerial;
	for (int i=0;i<Count;i++)
	{
		spe << ( BYTE)SkillSerial;
		spe << ( BYTE)(Key[i]>>8) << ( BYTE)( Key[i]&0xff);	
	}
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1D����[SendRequestMagicAttack(%d)]", Serial);
	g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d, SkillSerial : %d", 
		g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq(), btSkillSerial);
	g_ConsoleDebug->Write(MCD_NORMAL, "%d %d %d %d %d %d %d", x, y, Serial, Count, HIBYTE(p_Type), LOBYTE(p_Type), btSkillSerial);
#ifdef _VS2008PORTING
	for (int i=0;i<Count;i++)
#else // _VS2008PORTING
	for (i=0;i<Count;i++)
#endif // _VS2008PORTING
	{
		g_ConsoleDebug->Write(MCD_NORMAL, " %d %d %d", SkillSerial, (Key[i]>>8), (Key[i]&0xff));
	}
#endif // CONSOLE_DEBUG
	
	hanguo_check5();
}
#endif //ENABLE_EDIT
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT
#define SendRequestMagicAttack( p_Type, p_x, p_y, p_Serial, p_Count, p_Key, p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, PACKET_MAGIC_ATTACK );\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check5();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_MAGIC_ATTACK );\
		WORD Type = (WORD)p_Type;\
		spe << (BYTE)(p_x) << (BYTE)(p_y) << (BYTE)MakeSkillSerialNumber(&p_Serial) << (BYTE)(p_Count) << (BYTE)(HIBYTE(Type))<<(BYTE)(LOBYTE(Type));\
		int *pKey = ( int*)( p_Key);\
		for (int i=0;i<p_Count;i++)\
		{\
			spe << ( BYTE)p_SkillSerial;\
			spe << ( BYTE)(pKey[i]>>8) << ( BYTE)( pKey[i]&0xff);\
		}\
		spe.Send( TRUE);\
		hanguo_check5();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicAttack(int Type,int x,int y,BYTE Serial,int Count,int *Key, WORD SkillSerial)
{
    if(FindText2(Hero->ID,"webzen")) return;
	
	g_DummyAttackChecker->AddSkillCount();
	if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
	{
		pre_send( g_hInst);
		CStreamPacketEngine spe2;
		spe2.Init( 0xC1, PACKET_MAGIC_ATTACK );
		DWORD dwDummy;
		g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
		spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);
		spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
		hanguo_check5();
		g_DummyAttackChecker->InitSkillCount();
		g_DummyAttackChecker->AddSkillCount();
	}
	
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	
	spe.Init( 0xC1, PACKET_MAGIC_ATTACK);
	spe << (BYTE)x << (BYTE)y << (BYTE)MakeSkillSerialNumber(&Serial) << (BYTE)Count << (BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type));
	for (int i=0;i<Count;i++)
	{
		spe << ( BYTE)SkillSerial;
		spe << ( BYTE)(Key[i]>>8) << ( BYTE)( Key[i]&0xff);	
	}
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "%x ����[SendRequestMagicAttack(%d)]", PACKET_MAGIC_ATTACK, Serial);
	g_ConsoleDebug->Write(MCD_NORMAL, "[Dummy] - Count : %d/%d]", g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq());
	g_ConsoleDebug->Write(MCD_NORMAL, "%d %d %d %d %d %d", x, y, Serial, Count, HIBYTE(p_Type), LOBYTE(p_Type));
	for (i=0;i<Count;i++)
	{
		g_ConsoleDebug->Write(MCD_NORMAL, " %d %d %d", SkillSerial, (Key[i]>>8), (Key[i]&0xff));
	}
#endif // CONSOLE_DEBUG
	
	hanguo_check5();
}
#endif //ENABLE_EDIT
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#else KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifndef ENABLE_EDIT
#define SendRequestMagicAttack( p_Type, p_x, p_y, p_Serial, p_Count, p_Key, p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_MAGIC_ATTACK );\
		WORD Type = (WORD)p_Type;\
		spe << (BYTE)(p_x) << (BYTE)(p_y) << (BYTE)MakeSkillSerialNumber(&p_Serial) << (BYTE)(p_Count) << (BYTE)(HIBYTE(Type))<<(BYTE)(LOBYTE(Type));\
		int *pKey = ( int*)( p_Key);\
		for (int i=0;i<p_Count;i++)\
		{\
			spe << ( BYTE)p_SkillSerial;\
			spe << ( BYTE)(pKey[i]>>8) << ( BYTE)( pKey[i]&0xff);\
		}\
		spe.Send( TRUE);\
		hanguo_check5();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicAttack(int Type,int x,int y,BYTE Serial,int Count,int *Key, WORD SkillSerial)
{
    if(FindText2(Hero->ID,"webzen")) return;

	pre_send( g_hInst);
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	
	spe.Init( 0xC1, PACKET_MAGIC_ATTACK);
	spe << (BYTE)x << (BYTE)y << (BYTE)MakeSkillSerialNumber(&Serial) << (BYTE)Count << (BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type));
	for (int i=0;i<Count;i++)
	{
		spe << ( BYTE)SkillSerial;
		spe << ( BYTE)(Key[i]>>8) << ( BYTE)( Key[i]&0xff);	
	}
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1D����[SendRequestMagicAttack(%d)]", Serial);
	g_ConsoleDebug->Write(MCD_NORMAL, "%d %d %d %d %d %d", x, y, Serial, Count, HIBYTE(p_Type), LOBYTE(p_Type));
#ifdef _VS2008PORTING
	for (int i=0;i<Count;i++)
#else // _VS2008PORTING
	for (i=0;i<Count;i++)
#endif // _VS2008PORTING
	{
		g_ConsoleDebug->Write(MCD_NORMAL, " %d %d %d", SkillSerial, (Key[i]>>8), (Key[i]&0xff));
	}
#endif // CONSOLE_DEBUG

	hanguo_check5();
}
#endif //ENABLE_EDIT
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
#else // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifndef ENABLE_EDIT
#ifdef PBG_FIX_DARK_FIRESCREAM_HACKCHECK
#define SendRequestMagicAttack( p_Type, p_x, p_y, p_Serial, p_Count, p_Key, p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_MAGIC_ATTACK );\
		WORD Type = (WORD)p_Type;\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( p_x) << ( BYTE)( p_y) << (BYTE)MakeSkillSerialNumber(&p_Serial) << ( BYTE)( p_Count);\
		int *pKey = ( int*)( p_Key);\
		for (int i=0;i<p_Count;i++)\
		{\
			spe << ( BYTE)(pKey[i]>>8) << ( BYTE)( pKey[i]&0xff);\
			spe << ( BYTE)p_SkillSerial;\
		}\
		spe.Send( TRUE);\
		hanguo_check5();\
	}\
}
#else //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
#define SendRequestMagicAttack( p_Type, p_x, p_y, p_Serial, p_Count, p_Key, p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, PACKET_MAGIC_ATTACK );\
		WORD Type = (WORD)p_Type;\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( p_x) << ( BYTE)( p_y) << ( BYTE)( p_Serial) << ( BYTE)( p_Count);\
		int *pKey = ( int*)( p_Key);\
		for (int i=0;i<p_Count;i++)\
		{\
			spe << ( BYTE)(pKey[i]>>8) << ( BYTE)( pKey[i]&0xff);\
			spe << ( BYTE)p_SkillSerial;\
		}\
		spe.Send( TRUE);\
		hanguo_check5();\
	}\
}
#endif //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
#else // ENABLE_EDIT
__forceinline void SendRequestMagicAttack(int Type,int x,int y,BYTE Serial,int Count,int *Key, WORD SkillSerial)
{
    if(FindText2(Hero->ID,"webzen")) return;
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;

	spe.Init( 0xC1, PACKET_MAGIC_ATTACK);
#ifdef PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))<< ( BYTE)x << ( BYTE)y << (BYTE)MakeSkillSerialNumber(&Serial) << ( BYTE)Count;
#else //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))<< ( BYTE)x << ( BYTE)y << ( BYTE)Serial << ( BYTE)Count;
#endif //PBG_FIX_DARK_FIRESCREAM_HACKCHECK
	for (int i=0;i<Count;i++)
	{
		spe << ( BYTE)(Key[i]>>8) << ( BYTE)( Key[i]&0xff);
		spe << ( BYTE)SkillSerial;
	}
	spe.Send( TRUE);

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1D����[SendRequestMagicAttack(%d)]", Serial);
#endif // CONSOLE_DEBUG

	hanguo_check5();
}
#endif //ENABLE_EDIT
#endif // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK


extern int CurrentSkill;

//��������

inline BYTE GetDestValue( int xPos, int yPos, int xDst, int yDst)
{
    int DestX = xDst-xPos;
    int DestY = yDst-yPos;
    if ( DestX<-8 ) DestX = -8;
    if ( DestX>7  ) DestX = 7;
    if ( DestY<-8 ) DestY = -8;
    if ( DestY>7  ) DestY = 7;
	assert( -8 <= DestX && DestX <= 7);
	assert( -8 <= DestY && DestY <= 7);
	BYTE byValue1 = ( ( BYTE)( DestX + 8)) << 4;
	BYTE byValue2 = ( ( BYTE)( DestY + 8)) & 0xf;
	return ( byValue1 | byValue2);
}
#ifndef PBG_FIX_DARK_FIRESCREAM_HACKCHECK
BYTE MakeSkillSerialNumber(BYTE * pSerialNumber);
#endif //PBG_FIX_DARK_FIRESCREAM_HACKCHECK

// ���� ȿ�� �����
#ifdef KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT
#define SendRequestMagicContinue( p_Type, p_x, p_y,p_Angle,p_Dest,p_Tpos,p_TKey,p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x1E);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check6();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CurrentSkill = p_Type;\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x1E);\
		spe << ( BYTE)(p_x) << ( BYTE)(p_y) << (BYTE)(HIBYTE(Type)) << (BYTE)(LOBYTE(Type)) << (BYTE)(p_Angle) << ( BYTE)( p_Dest) << ( BYTE)(p_Tpos) << MakeSkillSerialNumber(p_SkillSerial) << ( BYTE)( ( p_TKey)>>8) << ( BYTE)( ( p_TKey)&0xff) << (BYTE)g_DummyAttackChecker->GetSerial();\
		spe.Send( TRUE);\
		hanguo_check6();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicContinue(int Type,int x,int y,int Angle, BYTE Dest, BYTE Tpos, WORD TKey, BYTE * pSkillSerial)
{
    if(FindText2(Hero->ID,"webzen")) return;
	
	g_DummyAttackChecker->AddSkillCount();
	if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
	{
		pre_send( g_hInst);
		CStreamPacketEngine spe2;
		spe2.Init( 0xC1, 0x1E);
		DWORD dwDummy;
		g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
		spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) <<(BYTE)(0);
		spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
		hanguo_check6();
		g_DummyAttackChecker->InitSkillCount();
		g_DummyAttackChecker->AddSkillCount();
	}
	
	pre_send( g_hInst);
	CurrentSkill = Type;
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	spe.Init( 0xC1, 0x1E);
	BYTE btSkillSerial = g_DummyAttackChecker->GetSerial();
	spe << ( BYTE)( x) << ( BYTE)( y) << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))
		<< ( BYTE)( Angle) << ( BYTE)( Dest) << ( BYTE)( Tpos) << MakeSkillSerialNumber(pSkillSerial) << ( BYTE)( ( TKey)>>8) << ( BYTE)( ( TKey)&0xff) << (BYTE)btSkillSerial;
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1E����[SendRequestMagicContinue]");
	g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d, SkillSerial : %d", 
		g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq(), btSkillSerial);
#endif // CONSOLE_DEBUG
	
	hanguo_check6();
}
#endif //ENABLE_EDIT
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#ifndef ENABLE_EDIT
#define SendRequestMagicContinue( p_Type, p_x, p_y,p_Angle,p_Dest,p_Tpos,p_TKey,p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		g_DummyAttackChecker->AddSkillCount();\
		if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )\
		{\
			pre_send( g_hInst);\
			CStreamPacketEngine spe2;\
			spe2.Init( 0xC1, 0x1E);\
			DWORD dwDummy;\
			g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);\
			spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);\
			spe2.Send( TRUE);\
			hanguo_check6();\
			g_DummyAttackChecker->InitSkillCount();\
			g_DummyAttackChecker->AddSkillCount();\
		}\
		pre_send( g_hInst);\
		CurrentSkill = p_Type;\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x1E);\
		spe << ( BYTE)(p_x) << ( BYTE)(p_y) << (BYTE)(HIBYTE(Type)) << (BYTE)(LOBYTE(Type)) << (BYTE)(p_Angle) << ( BYTE)( p_Dest) << ( BYTE)(p_Tpos) << MakeSkillSerialNumber(p_SkillSerial) << ( BYTE)( ( p_TKey)>>8) << ( BYTE)( ( p_TKey)&0xff);\
		spe.Send( TRUE);\
		hanguo_check6();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicContinue(int Type,int x,int y,int Angle, BYTE Dest, BYTE Tpos, WORD TKey, 
											BYTE * pSkillSerial
											)
{
    if(FindText2(Hero->ID,"webzen")) return;
	
	g_DummyAttackChecker->AddSkillCount();
	if( g_DummyAttackChecker->GetSkillCount() >= g_DummyAttackChecker->GetDummyProtocolNextSeq() )
	{
		pre_send( g_hInst);
		CStreamPacketEngine spe2;
		spe2.Init( 0xC1, 0x1E);
		DWORD dwDummy;
		g_DummyAttackChecker->MakeDummyProtocol((LPBYTE)&dwDummy);
		spe2 << (DWORD)dwDummy << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0) << (BYTE)(0);
		spe2.Send( TRUE);
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_SEND, "Dummy���� - Count : %d, Value : %d]", g_DummyAttackChecker->GetSkillCount(), dwDummy);
#endif // CONSOLE_DEBUG
		hanguo_check6();
		g_DummyAttackChecker->InitSkillCount();
		g_DummyAttackChecker->AddSkillCount();
	}
		
	pre_send( g_hInst);
	CurrentSkill = Type;
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	spe.Init( 0xC1, 0x1E);
	spe << ( BYTE)( x) << ( BYTE)( y) << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))
		<< ( BYTE)( Angle) << ( BYTE)( Dest) << ( BYTE)( Tpos) << MakeSkillSerialNumber(pSkillSerial) << ( BYTE)( ( TKey)>>8) << ( BYTE)( ( TKey)&0xff);
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1E����[SendRequestMagicContinue]");
	g_ConsoleDebug->Write(MCD_SEND, "[Dummy] - Count : %d/%d", g_DummyAttackChecker->GetSkillCount(), g_DummyAttackChecker->GetDummyProtocolNextSeq());
#endif // CONSOLE_DEBUG
	
	hanguo_check6();
}
#endif //ENABLE_EDIT
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
#else // KJH_ADD_DUMMY_SKILL_PROTOCOL
#ifndef ENABLE_EDIT
#define SendRequestMagicContinue( p_Type, p_x, p_y,p_Angle,p_Dest,p_Tpos,p_TKey,p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CurrentSkill = p_Type;\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x1E);\
		spe << ( BYTE)(p_x) << ( BYTE)(p_y) << (BYTE)(HIBYTE(Type)) << (BYTE)(LOBYTE(Type)) << (BYTE)(p_Angle) << ( BYTE)( p_Dest) << ( BYTE)(p_Tpos) << MakeSkillSerialNumber(p_SkillSerial) << ( BYTE)( ( p_TKey)>>8) << ( BYTE)( ( p_TKey)&0xff);\
		spe.Send( TRUE);\
		hanguo_check6();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicContinue(int Type,int x,int y,int Angle, BYTE Dest, BYTE Tpos, WORD TKey, 
											BYTE * pSkillSerial
											)
{
    if(FindText2(Hero->ID,"webzen")) return;

	pre_send( g_hInst);
	CurrentSkill = Type;
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	spe.Init( 0xC1, 0x1E);
	spe << ( BYTE)( x) << ( BYTE)( y) << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))
		<< ( BYTE)( Angle) << ( BYTE)( Dest) << ( BYTE)( Tpos) << MakeSkillSerialNumber(pSkillSerial) << ( BYTE)( ( TKey)>>8) << ( BYTE)( ( TKey)&0xff);
	spe.Send( TRUE);
	
#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1E����[SendRequestMagicContinue]");
#endif // CONSOLE_DEBUG
	
	hanguo_check6();
}
#endif //ENABLE_EDIT
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL
#else // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
#ifndef ENABLE_EDIT
#define SendRequestMagicContinue( p_Type, p_x, p_y,p_Angle,p_Dest,p_Tpos,p_TKey,p_SkillSerial)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CurrentSkill = p_Type;\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x1E);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << ( BYTE)( p_x) << ( BYTE)( p_y) << ( BYTE)( p_Angle) << ( BYTE)( p_Dest) << ( BYTE)( p_Tpos) << ( BYTE)( ( p_TKey)>>8) << ( BYTE)( ( p_TKey)&0xff);\
		spe << MakeSkillSerialNumber(p_SkillSerial);\
		spe.Send( TRUE);\
		hanguo_check6();\
	}\
}
#else // ENABLE_EDIT
__forceinline void SendRequestMagicContinue(int Type,int x,int y,int Angle, BYTE Dest, BYTE Tpos, WORD TKey, 
											BYTE * pSkillSerial
											)
{
    if(FindText2(Hero->ID,"webzen")) return;
	pre_send( g_hInst);
	CurrentSkill = Type;
	CStreamPacketEngine spe;
	WORD p_Type = (WORD)Type;
	spe.Init( 0xC1, 0x1E);
	spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type))
		<< ( BYTE)( x) << ( BYTE)( y) << ( BYTE)( Angle) << ( BYTE)( Dest) << ( BYTE)( Tpos) << ( BYTE)( ( TKey)>>8) << ( BYTE)( ( TKey)&0xff);
	spe << MakeSkillSerialNumber(pSkillSerial);
	spe.Send( TRUE);

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x1E����[SendRequestMagicContinue]");
#endif // CONSOLE_DEBUG

	hanguo_check6();
}
#endif //ENABLE_EDIT
#endif // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK



extern bool Teleport;

// �̹� �ڷ���Ʈ ���̰ų�, �� ���̸� ������ �߿��� �ٽ� ��û���� ���ϰ� �Ѵ�.
#define SendRequestMagicTeleport( p_pbResult, p_Type, p_x, p_y)\
{	\
	if ( Teleport || g_bWhileMovingZone || ( GetTickCount() - g_dwLatestZoneMoving < 3000))\
	{\
		*( p_pbResult) = false;\
	}\
	else\
	{\
		pre_send( g_hInst);\
		if(( p_Type)==0)\
		{\
			Teleport = true;\
		}\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x1C);\
		spe.AddNullData( 1);\
		spe << ( WORD)( p_Type) << ( BYTE)( p_x) << ( BYTE)( p_y);\
		spe.Send( TRUE);\
		hanguo_check7();\
\
		*( p_pbResult) = true;\
	}\
}

// �̹� �ڷ���Ʈ ���̰ų�, �� ���̸� ������ �߿��� �ٽ� ��û���� ���ϰ� �Ѵ�.
#define SendRequestMagicTeleportB( p_pbResult, p_Index, p_x, p_y )\
{	\
	if ( Teleport )\
	{\
        Teleport = false;\
		*( p_pbResult) = false;\
	}\
	else\
	{\
		pre_send( g_hInst);\
		Teleport = true;\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0xB0);\
		spe << ( WORD)( p_Index) << ( BYTE)( p_x) << ( BYTE)( p_y);\
		spe.Send( TRUE);\
		hanguo_check7();\
\
		*( p_pbResult) = true;\
	}\
}

///////////////////////////////////////////////////////////////////////////////
// npc�� ��ȭ, ���, �ȴ�
///////////////////////////////////////////////////////////////////////////////

#define SendRequestTalk( p_Key)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x30);\
	spe << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
	spe.Send( TRUE);\
	hanguo_check8();\
}


#define SendExitInventory()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x31);\
	spe.Send( FALSE);\
}

#ifdef CSK_FIX_HIGHVALUE_MESSAGEBOX
#define SendRequestSell( p_Index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x33);\
	spe << ( BYTE)( p_Index);\
	spe.Send( TRUE);\
	hanguo_check9();\
	g_pNPCShop->SetSellingItem(true);\
}
#else // CSK_FIX_HIGHVALUE_MESSAGEBOX
#define SendRequestSell( p_Index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x33);\
	spe << ( BYTE)( p_Index);\
	spe.Send( TRUE);\
	hanguo_check9();\
}
#endif // CSK_FIX_HIGHVALUE_MESSAGEBOX



extern int BuyCost;

__forceinline void SendRequestBuy(int Index,int Cost)
{
    if(BuyCost != 0) return;
 	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x32);
	spe << ( BYTE)Index;
	spe.Send( TRUE);
	BuyCost = Cost;

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x32����[SendRequestBuy(%d)]", Index);
#endif // CONSOLE_DEBUG

	hanguo_check10();
}

#define SendRequestRepair( p_Index, p_AddGold)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x34);\
	spe << ( BYTE)( p_Index ) << ( BYTE )( p_AddGold );\
	spe.Send( TRUE);\
}

///////////////////////////////////////////////////////////////////////////////
// �̺�Ʈ Ĩ.
///////////////////////////////////////////////////////////////////////////////
//  ������ ����� ��û�Ѵ�.
#define SendRequestEventChip( p_Type, p_Index )\
{\
    pre_send( g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0x95);\
    spe << ( BYTE)( p_Type) << ( BYTE)( p_Index);\
    spe.Send( FALSE);\
}

//  ����� ���ڸ� ��û�Ѵ�.
#define SendRequestMutoNumber()\
{\
    pre_send( g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0x96);\
    spe.Send( FALSE);\
}

//  
#define SendRequestEventChipExit()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x97);\
	spe.Send( FALSE);\
}

//  ���� ȯ�� ��û.		( 0: ����, 1: ���� ).
#define SendRequestLenaExchange( p_byType )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x98);\
    spe << (BYTE)( p_byType );\
	spe.Send( FALSE);\
}


#ifdef SCRATCH_TICKET
//	���� ���.
#define SendRequestScratchSerial( p_strSerial1, p_strSerial2, p_strSerial3 )\
{\
	pre_send( g_hInst );\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x9D );\
	spe.AddData( p_strSerial1, 5 );\
	spe.AddData( p_strSerial2, 5 );\
	spe.AddData( p_strSerial3, 5 );\
	spe.Send( FALSE );\
}
#endif

//////////////////////////////////////////////////////////////////////////
//  ���� ����
//////////////////////////////////////////////////////////////////////////


#define SendRequestServerImmigration( p_ResidentNumber)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x99);\
	spe.AddData( ( p_ResidentNumber), 10);\
	spe.Send( TRUE);\
}


//////////////////////////////////////////////////////////////////////////
//  ����Ʈ �ý���.
//////////////////////////////////////////////////////////////////////////
//  ����Ʈ ���� ������ �䱸.
#define SendRequestQuestHistory()\
{\
    pre_send ( g_hInst );\
    CStreamPacketEngine spe;\
    spe.Init ( 0xC1, 0xA0 );\
    spe.Send ( TRUE );\
    hanguo_check9 ();\
}

//  Ư�� ����Ʈ �������� ���� �䱸.
#define SendRequestQuestState( p_Index, p_State )\
{\
    pre_send ( g_hInst );\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0xA2 );\
    spe << (BYTE)( p_Index ) << (BYTE)( p_State );\
    spe.Send ( TRUE );\
    hanguo_check9 ();\
}

//  �Ӽ�.
#define SendRequestAttribute( p_Att )\
{\
    pre_send ( g_hInst );\
    CStreamPacketEngine spe;\
    spe.Init ( 0xC1, 0x9B );\
    spe << (BYTE)( p_Att );\
    spe.Send ( FALSE );\
    hanguo_check9 ();\
}

//----------------------------------------------------------------------------
// CG [0xA4][0x00] ���� ų ī��Ʈ�� ����Ʈ �Ϸ������� ��� ���� ��û
//----------------------------------------------------------------------------
#define SendRequestQuestMonKillInfo(byQuestIndex)\
{\
    pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xA4);\
	spe << (BYTE)0x00;\
    spe << (BYTE)byQuestIndex;\
    spe.Send();\
}

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
// ������ dwQuestIndex ����Ʈ�� ���������� �˸�.
#define SendQuestSelection(dwQuestIndex, byResult)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x0A;\
	spe << (DWORD)(dwQuestIndex);\
    spe << (BYTE)(byResult);\
    spe.Send();\
    hanguo_check9();\
}

// ������ ����Ʈ ���ù��� ���������� �˸�.
#define SendQuestSelAnswer(dwQuestIndex, bySelAnswer)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x0B;\
	spe << (DWORD)(dwQuestIndex);\
    spe << (BYTE)(bySelAnswer);\
    spe.Send();\
    hanguo_check9();\
}

// ����Ʈ �Ϸ� ������ �䱸.
#define SendRequestQuestComplete(dwQuestIndex)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x0D;\
    spe << (DWORD)(dwQuestIndex);\
    spe.Send();\
    hanguo_check9();\
}

// Ŭ�󿡼� �����ϴ� �䱸 ���� ������ �� ���������� ������ ����.
//(��: Ʃ�丮�󿡼� 'ĳ���� â�� �����' ���.)
#define SendSatisfyQuestRequestFromClient(dwQuestIndex)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x10;\
    spe << (DWORD)(dwQuestIndex);\
    spe.Send();\
    hanguo_check9();\
}

// �������� ����Ʈ ����Ʈ ��û.
#define SendRequestProgressQuestList()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x1A;\
    spe.Send();\
    hanguo_check9();\
}

// �������� ����Ʈ ����Ʈ���� Ư�� ����Ʈ�� �䱸, ���� ���� ��û.
#define SendRequestProgressQuestRequestReward(dwQuestIndex)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x1B;\
    spe << (DWORD)(dwQuestIndex);\
    spe.Send();\
    hanguo_check9();\
}

// ����Ʈ ���� ��û.
#define SendRequestQuestGiveUp(dwQuestIndex)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x0F;\
    spe << (DWORD)(dwQuestIndex);\
    spe.Send();\
    hanguo_check9();\
}

#ifdef ASG_FIX_QUEST_PROTOCOL_ADD
// ��Ÿ ��Ȳ�� ���� ����Ʈ ����Ʈ ��û.
#define SendRequestQuestByEtcEPList()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x21;\
    spe.Send();\
    hanguo_check9();\
}
#endif	// ASG_FIX_QUEST_PROTOCOL_ADD
#endif	// ASG_ADD_NEW_QUEST_SYSTEM

#ifdef ASG_ADD_GENS_SYSTEM
// �ս� ���� ��û.
#define SendRequestGensJoining(byInfluence)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF8);\
	spe << (BYTE)0x01;\
    spe << (BYTE)(byInfluence);\
    spe.Send();\
    hanguo_check9();\
}

// �ս� Ż�� ��û.
#define SendRequestGensSecession()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF8);\
	spe << (BYTE)0x03;\
    spe.Send();\
    hanguo_check9();\
}

#endif	// ASG_ADD_GENS_SYSTEM
#ifdef PBG_ADD_GENSRANKING
// �ս� ���� �ޱ�
#define SendRequestGensReward(byInfluence)\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF8);\
	spe << (BYTE)0x09;\
	spe << (BYTE)(byInfluence);\
    spe.Send();\
    hanguo_check9();\
}
// �ս� ����â ����
#define SendRequestGensInfo_Open()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF8);\
	spe << (BYTE)0x0B;\
    spe.Send();\
    hanguo_check9();\
}
#endif //PBG_ADD_GENSRANKING
#ifdef ASG_ADD_UI_NPC_DIALOGUE
// NPC�� ���� ����Ʈ EP(���Ǽҵ�)����Ʈ ��û.(�������� (0xF6 0x0A)�� ����)
#define SendRequestQuestByNPCEPList()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x30;\
    spe.Send();\
    hanguo_check9();\
}

// ���ݷ�, ���� ��� ���� ��û.
#define SendRequestAPDPUp()\
{\
	pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xF6);\
	spe << (BYTE)0x31;\
    spe.Send();\
    hanguo_check9();\
}
#endif	// ASG_ADD_UI_NPC_DIALOGUE

///////////////////////////////////////////////////////////////////////////////
// ������
///////////////////////////////////////////////////////////////////////////////

__forceinline bool SendRequestEquipmentItem(int iSrcType,int iSrcIndex, ITEM* pItem, int iDstType,int iDstIndex)
{
	if(EquipmentItem || NULL == pItem) return false;
	pre_send( g_hInst);
	EquipmentItem = true;

	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x24);
	
	BYTE splitType;
	if( pItem->option_380 )
	{
		splitType = ((BYTE)(pItem->Type>>5)&240) | 0x08;
	}
	else
		splitType = ((BYTE)(pItem->Type>>5)&240);

#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
	if( pItem->bPeriodItem == true )
	{
		splitType |= 0x02;
	}
	
	if( pItem->bExpiredPeriod == true )
	{
		splitType |= 0x04;
	}
#endif // #ifdef KJH_ADD_PERIOD_ITEM_SYSTEM

#ifdef MODIFY_SOCKET_PROTOCOL
	BYTE spareBits;
	if (g_SocketItemMgr.IsSocketItem(pItem))
	{
		spareBits = pItem->SocketSeedSetOption;	// ���Ͼ������̸� ��ȭ�����ڸ��� ���� ��Ʈ�ɼ��� ����Ѵ�.
	}
	else
	{
		spareBits = (((BYTE)pItem->Jewel_Of_Harmony_Option)<<4)+((BYTE)pItem->Jewel_Of_Harmony_OptionLevel);
	}
#else	// MODIFY_SOCKET_PROTOCOL
	BYTE spareBits = (((BYTE)pItem->Jewel_Of_Harmony_Option)<<4)+((BYTE)pItem->Jewel_Of_Harmony_OptionLevel);
#endif	// MODIFY_SOCKET_PROTOCOL

#ifdef MODIFY_SOCKET_PROTOCOL
	BYTE socketBits[5] = { pItem->bySocketOption[0], pItem->bySocketOption[1], pItem->bySocketOption[2], pItem->bySocketOption[3], pItem->bySocketOption[4] };
#endif	// MODIFY_SOCKET_PROTOCOL
	
#ifdef KJH_FIX_SEND_REQUEST_INVENTORY_ITEMINFO_CASTING
	spe << (BYTE)(iSrcType&0xff) << (BYTE)(iSrcIndex&0xff) << (BYTE)(pItem->Type&0xff) << (BYTE)(pItem->Level&0xff)
		<< pItem->Durability << pItem->Option1 << pItem->ExtOption
		<< splitType << spareBits
#ifdef MODIFY_SOCKET_PROTOCOL
		<< socketBits[0] << socketBits[1] << socketBits[2] << socketBits[3] << socketBits[4]
#endif	// MODIFY_SOCKET_PROTOCOL
		<< (BYTE)(iDstType&0xff) << (BYTE)(iDstIndex&0xff);
#else // KJH_FIX_SEND_REQUEST_INVENTORY_ITEMINFO_CASTING
	spe << ( BYTE)iSrcType << ( BYTE)iSrcIndex << ( BYTE)pItem->Type << ( BYTE)( pItem->Level)
		<< ( BYTE)( pItem->Durability) << ( BYTE)( pItem->Option1) << ( BYTE)( pItem->ExtOption) 
		<< splitType << spareBits
#ifdef MODIFY_SOCKET_PROTOCOL
		<< socketBits[0] << socketBits[1] << socketBits[2] << socketBits[3] << socketBits[4]
#endif	// MODIFY_SOCKET_PROTOCOL
		<< ( BYTE)iDstType << ( BYTE)iDstIndex;
#endif // KJH_FIX_SEND_REQUEST_INVENTORY_ITEMINFO_CASTING
	spe.Send( TRUE);

	hanguo_check11();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x24����[SendRequestEquipmentItem(%d %d %d %d %d %d %d)]", 
		iSrcIndex, iDstIndex, iSrcType, iDstType, (pItem->Type&0x1FFF), 
		( BYTE)( pItem->Level), ( BYTE)( pItem->Durability));
#endif // CONSOLE_DEBUG
	return true;
}

__forceinline void SendRequestEquipmentItem(int SrcFlag,int SrcIndex,int DstFlag,int DstIndex)
{
	if(EquipmentItem) return;
	pre_send( g_hInst);
	EquipmentItem = true;

	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x24);
	
	BYTE splitType;

	if( PickItem.option_380 )
	{
		splitType = ((BYTE)(PickItem.Type>>5)&240) | 0x08;
	}
	else
		splitType = ((BYTE)(PickItem.Type>>5)&240);

#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
	if( PickItem.bPeriodItem == true )
	{
		splitType |= 0x02;
	}

	if( PickItem.bExpiredPeriod == true )
	{
		splitType |= 0x04;
	}
#endif // #ifdef KJH_ADD_PERIOD_ITEM_SYSTEM


#ifdef MODIFY_SOCKET_PROTOCOL
	BYTE spareBits;
	if (g_SocketItemMgr.IsSocketItem(&PickItem))
	{
		spareBits = PickItem.SocketSeedSetOption;	// ���Ͼ������̸� ��ȭ�����ڸ��� ���� ��Ʈ�ɼ��� ����Ѵ�.
	}
	else
	{
		spareBits = (((BYTE)PickItem.Jewel_Of_Harmony_Option)<<4)+((BYTE)PickItem.Jewel_Of_Harmony_OptionLevel);
	}
#else	// MODIFY_SOCKET_PROTOCOL

	BYTE Jewel = (((BYTE)PickItem.Jewel_Of_Harmony_Option)<<4)+((BYTE)PickItem.Jewel_Of_Harmony_OptionLevel);
	BYTE spareBits = Jewel;

#endif	// MODIFY_SOCKET_PROTOCOL

#ifdef MODIFY_SOCKET_PROTOCOL
	BYTE socketBits[5] = { PickItem.bySocketOption[0], PickItem.bySocketOption[1], PickItem.bySocketOption[2], PickItem.bySocketOption[3], PickItem.bySocketOption[4] };
#endif	// MODIFY_SOCKET_PROTOCOL
	

	
	spe << ( BYTE)SrcFlag << ( BYTE)SrcIndex << ( BYTE)PickItem.Type << ( BYTE)( PickItem.Level)
		<< ( BYTE)( PickItem.Durability) << ( BYTE)( PickItem.Option1) << ( BYTE)( PickItem.ExtOption) << splitType << spareBits
#ifdef MODIFY_SOCKET_PROTOCOL
		<< socketBits[0] << socketBits[1] << socketBits[2] << socketBits[3] << socketBits[4]
#endif	// MODIFY_SOCKET_PROTOCOL
		<< ( BYTE)DstFlag << ( BYTE)DstIndex;
	spe.Send( TRUE);

	hanguo_check11();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x24����[SendRequestEquipmentItem(%d %d %d %d %d %d %d)]", SrcIndex,DstIndex,SrcFlag,DstFlag, (PickItem.Type&0x1FFF), ( BYTE)( PickItem.Level), ( BYTE)( PickItem.Durability));
#endif // CONSOLE_DEBUG
}

extern int  EnableUse;


#ifndef ENABLE_EDIT

#define SendRequestUse( p_Index, p_Target)\
{\
	if( !IsCanUseItem() )\
	{\
		g_pChatListBox->AddText("",GlobalText[474],SEASON3B::TYPE_ERROR_MESSAGE);\
	}\
	else\
	{\
		if(EnableUse <= 0)\
		{\
			pre_send( g_hInst);\
			EnableUse = 10;\
			CStreamPacketEngine spe;\
			spe.Init( 0xC1, 0x26);\
			spe << ( BYTE)( ( p_Index)+12) << ( BYTE)( p_Target);\
			spe << (BYTE)g_byItemUseType;\
			spe.Send( TRUE);\
			hanguo_check12();\
			ITEM* pItem = g_pMyInventory->FindItem(p_Index);\
			if(pItem)\
			{\
				if(pItem->Type == ITEM_POTION)\
					PlayBuffer(SOUND_EAT_APPLE01);\
				else if(pItem->Type >= ITEM_POTION+1 && pItem->Type <= ITEM_POTION + 9)\
					PlayBuffer(SOUND_DRINK01);\
			}\
		}\
	}\
}

#else	// ENABLE_EDIT
__forceinline void SendRequestUse(int Index,int Target)
{
	if( !IsCanUseItem() )
	{
		// 474 "â�� ���ó� �ŷ��߿��� �������� ����Ͻ� �� �����ϴ�."
		g_pChatListBox->AddText("", GlobalText[474], SEASON3B::TYPE_ERROR_MESSAGE);
		return;
	}
	if(EnableUse > 0) 
	{
		return;
	}
	pre_send( g_hInst);
	EnableUse = 10;
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x26);
	spe << ( BYTE)( Index+MAX_EQUIPMENT_INDEX ) << ( BYTE)Target;
	spe << (BYTE)g_byItemUseType;
	spe.Send( TRUE);
	hanguo_check12();
	if(Inventory[Index].Type==ITEM_POTION)
		PlayBuffer(SOUND_EAT_APPLE01);
	else if(Inventory[Index].Type>=ITEM_POTION + 1 && Inventory[Index].Type<=ITEM_POTION + 9)
		PlayBuffer(SOUND_DRINK01);

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x26����[SendRequestUse(%d)]", Index+12);
#endif // CONSOLE_DEBUG
}
#endif //ENABLE_EDIT

extern int SendGetItem;
extern int SendDropItem;

#define SendRequestGetItem( p_Key)\
{\
	if(SendGetItem == -1)\
	{\
		pre_send( g_hInst);\
		SendGetItem = p_Key;\
\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x22);\
		spe << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check1();\
	}\
}

#define SendRequestDropItem( p_InventoryIndex, p_x, p_y)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x23);\
	spe << ( BYTE)( p_x) << ( BYTE)( p_y) << ( BYTE)( p_InventoryIndex);\
	spe.Send( TRUE);\
	SendDropItem = ( p_InventoryIndex);\
	hanguo_check2();\
}

#ifdef _PVP_ADD_MOVE_SCROLL
#define SendRequestCharacterEffect( p_key, p_type)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x48);\
	spe << ( BYTE)( p_key >> 8) << ( BYTE)( p_key & 0x00FF) << ( BYTE)( p_type);\
	spe.Send( FALSE);\
}
#endif	// _PVP_ADD_MOVE_SCROLL

///////////////////////////////////////////////////////////////////////////////
// ������ ����Ʈ ���
///////////////////////////////////////////////////////////////////////////////

#define SendRequestAddPoint( p_Type)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x06 << ( BYTE)( p_Type);\
	spe.Send();\
    PlayBuffer(SOUND_CLICK01);\
	hanguo_check3();\
}


///////////////////////////////////////////////////////////////////////////////
// ��ȯ
///////////////////////////////////////////////////////////////////////////////

#define SendRequestTrade( p_Key)\
{\
	if( IsCanTrade() && EnableMainRender )\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x36);\
		spe << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
\
		char Text[100];\
		sprintf(Text,GlobalText[475],CharactersClient[FindCharacterIndex(p_Key)].ID);\
		g_pChatListBox->AddText("", Text, SEASON3B::TYPE_SYSTEM_MESSAGE);\
		hanguo_check4();\
	}\
}

#define SendRequestTradeAnswer( p_Result)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x37);\
	spe << ( BYTE)( p_Result);\
	spe.Send();\
	hanguo_check5();\
}

#define SendRequestTradeGold( p_Gold)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3A);\
	spe.AddNullData( 1);\
	spe << ( DWORD)( p_Gold);\
	spe.Send();\
	hanguo_check7();\
}

#define SendRequestTradeResult( p_Result)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3C);\
	spe << ( BYTE)( p_Result);\
	spe.Send( TRUE);\
	hanguo_check8();\
}

#define SendRequestTradeExit()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3D);\
	spe.Send( TRUE);\
	hanguo_check9();\
}

#define SendPing()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x71);\
	spe.Send();\
}

#ifdef NPROTECT_AUTH2

#ifdef NP_GAME_GUARD
#ifdef GG_SERVER_AUTH
#define SendAuth( p_dwResult)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x73);\
	spe << ( BYTE)( 0) << ( p_dwResult);\
	spe.Send( TRUE);\
}
#endif
#endif

#else

#ifdef NP_GAME_GUARD
#ifdef GG_SERVER_AUTH
#define SendAuth( p_dwResult)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x73);\
	spe << ( BYTE)( 0) << ( DWORD)( p_dwResult);\
	spe.Send( TRUE);\
}
#endif
#endif

#endif // NPPROTECT_AUTH2

#ifdef YDG_MOD_PROTECT_AUTO_V5
///////////////////////////////////////////////////////////////////////////////
// ���� ���� ���� �˻�
///////////////////////////////////////////////////////////////////////////////
__forceinline void SendRequestCheckAutoToolResult(DWORD dwKey,BYTE btResult)
{
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x8A);
	spe.AddNullData( 1);
	spe << ( DWORD)dwKey << ( BYTE)btResult;
	spe.Send();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x8A����[SendRequestCheckAutoToolResult(%d %d)]", dwKey, btResult);
#endif // CONSOLE_DEBUG
}
#endif	// YDG_MOD_PROTECT_AUTO_V5

#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
///////////////////////////////////////////////////////////////////////////////
// �� �̵� ��û
///////////////////////////////////////////////////////////////////////////////
__forceinline void SendRequestMoveMap(DWORD dwBlockKey,WORD wMapIndex)
{
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x8E);
	spe << (BYTE)0x02;\
	spe << ( DWORD)dwBlockKey << ( WORD)wMapIndex;
	spe.Send();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x8E����[SendRequestMoveMap(%d %d)]", dwBlockKey, wMapIndex);
#endif // CONSOLE_DEBUG
#ifdef PJH_DEBUG
	//g_ConsoleDebug->Write(MCD_SEND, "���̵� ����[time : %d]", GetTickCount());
	char Text[300];
	wsprintf(Text,"���̵�����[time : %d]", GetTickCount());
	g_pChatListBox->AddText("DEBUG",Text, SEASON3B::TYPE_GM_MESSAGE);
#endif
}
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

///////////////////////////////////////////////////////////////////////////////
// â��
///////////////////////////////////////////////////////////////////////////////

__forceinline void SendRequestStorageGold(int Flag,int Gold)
{
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x81);
	spe << ( BYTE)Flag << ( DWORD)Gold;
	spe.Send();
	hanguo_check10();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x81����[SendRequestStorageGold(%d %d)]", Flag, Gold);
#endif // CONSOLE_DEBUG
}

__forceinline bool SendRequestStorageExit()
{
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x82);
	spe.Send();
	hanguo_check11();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x82����[SendRequestStorageExit]");
#endif // CONSOLE_DEBUG
	return true;
}

#ifdef LDK_MOD_PASSWORD_LENGTH_20
//�۷ι� ���п�
#define SendStoragePassword( p_byType, p_wPassword, p_ResidentNumber)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x83);\
	spe << ( BYTE)( p_byType) << ( WORD)( p_wPassword);\
	spe.AddData( ( p_ResidentNumber), 20);\
	spe.Send( TRUE);\
}
#else //LDK_MOD_PASSWORD_LENGTH_20
#define SendStoragePassword( p_byType, p_wPassword, p_ResidentNumber)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x83);\
	spe << ( BYTE)( p_byType) << ( WORD)( p_wPassword);\
	spe.AddData( ( p_ResidentNumber), 10);\
	spe.Send( TRUE);\
}
#endif //LDK_MOD_PASSWORD_LENGTH_20


///////////////////////////////////////////////////////////////////////////////
// ��Ƽ
///////////////////////////////////////////////////////////////////////////////

#define SendRequestParty( p_Key)\
{\
	if(EnableMainRender)\
	{\
		pre_send( g_hInst);\
		PartyKey = p_Key;\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x40);\
		spe << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check12();\
\
		char Text[100];\
		sprintf(Text,GlobalText[476],CharactersClient[FindCharacterIndex(p_Key)].ID);\
		g_pChatListBox->AddText("",Text,SEASON3B::TYPE_SYSTEM_MESSAGE);\
	}\
}

#define SendRequestPartyAnswer( p_Result)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x41);\
	spe << ( BYTE)( p_Result) << ( BYTE)( PartyKey>>8) << ( BYTE)( PartyKey&0xff);\
	spe.Send( TRUE);\
	hanguo_check1();\
}
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#define SendRequestPartyList()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x42);\
	spe.Send();\
	hanguo_check2();\
}

#define SendRequestPartyLeave( p_Index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x43);\
	spe << ( BYTE)( p_Index);\
	spe.Send();\
	hanguo_check3();\
}
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#define SendRequestPartyList()\
{\
	pre_send( g_hInst);\
	unsigned char Size = sizeof(PBMSG_HEADER);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x42);\
	spe.Send();\
	hanguo_check2();\
}

#define SendRequestPartyLeave( p_Index)\
{\
	pre_send( g_hInst);\
	unsigned char Size = sizeof(PHEADER_DEFAULT);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x43);\
	spe << ( BYTE)( p_Index);\
	spe.Send();\
	hanguo_check3();\
}
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX


///////////////////////////////////////////////////////////////////////////////
// ���
///////////////////////////////////////////////////////////////////////////////

#define SendRequestGuildMaster( p_Value)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x54);\
	spe << ( BYTE)( p_Value);\
	spe.Send();\
	hanguo_check4();\
}

// ������
#define SendRequestCreateGuild( GuildType, pGuildName, pGuildMark )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x55);\
	spe << (BYTE)(GuildType);\
	spe.AddData( (pGuildName), 8);\
	spe.AddData( (pGuildMark), 32);\
	spe.Send();\
	hanguo_check5();\
}
// �� ��������� ����
#define SendRequestEditGuildType( GuildType )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xE2);\
	spe << (BYTE)(GuildType);\
	spe.Send();\
	hanguo_check5();\
}
// ������ ��û
#define SendRequestGuildRelationShip( RelationType, RequestType, TargetUserIndexH, TargetUserIndexL )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xE5);\
	spe << (BYTE)(RelationType);\
	spe << (BYTE)(RequestType);\
	spe << (BYTE)(TargetUserIndexH);\
	spe << (BYTE)(TargetUserIndexL);\
	spe.Send();\
	char szTmp[100];\
	if( RelationType == 0x01 && RequestType == 0x01 )\
		sprintf(szTmp,GlobalText[1358],CharactersClient[FindCharacterIndex(MAKEWORD(TargetUserIndexL,TargetUserIndexH))].ID);\
	else if( RelationType == 0x01 && RequestType == 0x02 )\
		sprintf(szTmp,GlobalText[1387]);\
	else if( RelationType == 0x02 && RequestType == 0x01 )\
		sprintf(szTmp,GlobalText[1359],CharactersClient[FindCharacterIndex(MAKEWORD(TargetUserIndexL,TargetUserIndexH))].ID);\
	else if( RelationType == 0x02 && RequestType == 0x02 )\
		sprintf(szTmp,GlobalText[1360],CharactersClient[FindCharacterIndex(MAKEWORD(TargetUserIndexL,TargetUserIndexH))].ID);\
	g_pChatListBox->AddText("",szTmp,SEASON3B::TYPE_SYSTEM_MESSAGE);\
	hanguo_check5();\
}

// ������ ����
#define SendRequestGuildRelationShipResult( Type, RequestType, Result, TargetUserIndexH, TargetUserIndexL )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xE6);\
	spe << (BYTE)(Type);\
	spe << (BYTE)(RequestType);\
	spe << (BYTE)(Result);\
	spe << (BYTE)(TargetUserIndexH);\
	spe << (BYTE)(TargetUserIndexL);\
	spe.Send();\
	hanguo_check5();\
}
// ���ձ�� �����ϱ�
#define SendRequestBanUnionGuild( GuildName )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xEB);\
	spe << (BYTE)0x01;\
	spe.AddData( (GuildName), 8);\
    spe.Send();\
}
// ���ո���Ʈ ��û
#define SendRequestUnionList()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xE9);\
	spe.Send();\
	hanguo_check5();\
}

#define SendRequestEditGuildMark( p_Name, p_Mark )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x55);\
	spe.AddData( ( p_Name), 8);\
	spe.AddData( ( p_Mark), 32);\
	spe.Send();\
	hanguo_check5();\
}

#define SendRequestGuild( p_Key)\
{\
	if(EnableMainRender)\
	{\
		pre_send( g_hInst);\
		GuildPlayerKey = ( p_Key);\
		CStreamPacketEngine spe;\
		spe.Init( 0xC1, 0x50);\
		spe << ( BYTE)( ( p_Key)>>8) << ( BYTE)( ( p_Key)&0xff);\
		spe.Send();\
		hanguo_check6();\
\
		char Text[100];\
		sprintf(Text,GlobalText[477],CharactersClient[FindCharacterIndex(p_Key)].ID);\
		g_pChatListBox->AddText("",Text,SEASON3B::TYPE_SYSTEM_MESSAGE);\
	}\
}

#define SendRequestGuildAnswer( p_Result)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x51);\
	spe << ( BYTE)( p_Result) << ( BYTE)( GuildPlayerKey>>8) << ( BYTE)( GuildPlayerKey&0xff);\
	spe.Send();\
	hanguo_check7();\
}

#define SendRequestCreateGuildCancel()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x57);\
	spe.Send();\
	hanguo_check8();\
}

//��� ����Ʈ ��û
#define SendRequestGuildList()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x52);\
	spe.Send();\
	hanguo_check9();\
}

#ifdef LDK_MOD_PASSWORD_LENGTH_20
//�۷ι� ���п�
//��忡�� ����Ѹ� ����Ǵ� ���߷� ������
#define SendRequestGuildLeave( p_ID, p_ResidentNumber)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x53);\
	spe.AddData( ( p_ID), MAX_ID_SIZE);\
	spe.AddData( ( p_ResidentNumber), 20);\
	spe.Send();\
	hanguo_check10();\
}
#else //LDK_MOD_PASSWORD_LENGTH_20
#define SendRequestGuildLeave( p_ID, p_ResidentNumber)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x53);\
	spe.AddData( ( p_ID), MAX_ID_SIZE);\
	spe.AddData( ( p_ResidentNumber), 10);\
	spe.Send();\
	hanguo_check10();\
}
#endif //LDK_MOD_PASSWORD_LENGTH_20

#define SendRequestDeclareWar( p_Name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x60);\
	spe.AddData( ( p_Name), 8);\
	spe.Send();\
	hanguo_check11();\
}


void InitGuildWar();

#define SendRequestGuildWarAnswer( p_Result)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x61);\
	spe << ( BYTE)( p_Result);\
	spe.Send();\
	hanguo_check12();\
	if(!p_Result)\
	{\
		InitGuildWar();\
	}\
}

#define SendRequestGuildInfo( p_GuildKey)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x66);\
	spe.AddNullData( 1);\
	spe << ( int)( p_GuildKey);\
	spe.Send();\
}

// ��å�� �Ӹ� / ���� / ���� ��û
#define SendRequestGuildAssign( Type, GuildStatus, Name )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xE1 );\
	spe << (BYTE)(Type);\
	spe << (BYTE)(GuildStatus);\
	spe.AddData( (Name), MAX_ID_SIZE );\
	spe.Send();\
}

///////////////////////////////////////////////////////////////////////////////
// �ͽ����� �Լ�
///////////////////////////////////////////////////////////////////////////////

#ifdef ADD_SOCKET_MIX
#define SendRequestMix( p_Type, p_SubType)\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x86);\
    spe << ( BYTE)( p_Type);\
    spe << ( BYTE)( p_SubType);\
	spe.Send();\
	hanguo_check1();\
}
#else	// ADD_SOCKET_MIX
#define SendRequestMix( p_Type)\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x86);\
    spe << ( BYTE)( p_Type);\
	spe.Send();\
	hanguo_check1();\
}
#endif	// ADD_SOCKET_MIX

__forceinline bool SendRequestMixExit()
{
	pre_send( g_hInst);
	CStreamPacketEngine spe;
	spe.Init( 0xC1, 0x87);
	spe.Send();
	hanguo_check2();

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0x87����[SendRequestMixExit]");
#endif // CONSOLE_DEBUG
	return true;
}
//////////////////////////////////////////////////////////////////////////
// ���� ���� ���� �Լ�
//////////////////////////////////////////////////////////////////////////

#define SendRequestGemMix( iType, iLevel )\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xBC);\
	spe << (BYTE)0x00;\
	spe << ( BYTE)( iType ) << ( BYTE)( iLevel );\
	spe.Send();\
}

#define SendRequestGemUnMix( iType, iLevel, iPos )\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xBC);\
	spe << (BYTE)0x01;\
	spe << ( BYTE)( iType ) << ( BYTE)( iLevel ) << (BYTE)(iPos);\
	spe.Send();\
}

///////////////////////////////////////////////////////////////////////////////
// �Ǹ��� ���� ���� �Լ�
///////////////////////////////////////////////////////////////////////////////

#define SendRequestMoveToDevilSquare( bySquareNumber, iItemIndex)\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x90);\
	spe << ( BYTE)( bySquareNumber) << ( BYTE)( ( iItemIndex)+12);\
	spe.Send();\
}

#define SendRequestDevilSquareOpenTime()\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x91);\
	spe.Send();\
}

#define SendRequestEventCount(wType)\
{   \
    pre_send( g_hInst );\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0x9F );\
    spe << ( BYTE)( wType );\
    spe.Send();\
}

///////////////////////////////////////////////////////////////////////////////
// ���� ĳ�� ���� �Լ�
///////////////////////////////////////////////////////////////////////////////

#define SendRequestMoveToEventMatch(byCastleNumber, iItemIndex)\
{	\
	pre_send(g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0x9A);\
	spe << (BYTE)(byCastleNumber) << (BYTE)(iItemIndex);\
	spe.Send();\
}

#define SendRequestEventZoneOpenTime(byZoneType, iItemLevel)\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0x91);\
	spe << (BYTE)(byZoneType) << (BYTE)(iItemLevel);\
	spe.Send();\
}

//////////////////////////////////////////////////////////////////////////
//  ī���� ĳ�� ���� �Խ�.
//////////////////////////////////////////////////////////////////////////
#define SendRequestMoveToEventMatch2(byCastleNumber, iItemIndex)\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAF);\
	spe << (BYTE)0x01;\
    spe << (BYTE)(byCastleNumber) << (BYTE)(iItemIndex);\
	spe.Send();\
}


//////////////////////////////////////////////////////////////////////////
//  �ڽ��� ��ġ�� ���缺�� ���� ������ �˻縦 ��û�Ѵ�.
//////////////////////////////////////////////////////////////////////////
#define SendRequestCheckPosition(byPositionX, byPositionY)\
{   \
    pre_send( g_hInst);\
    CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAF);\
	spe << (BYTE)0x02;\
    spe << (BYTE)(byPositionX) << (BYTE)(byPositionY);\
    spe.Send();\
}

///////////////////////////////////////////////////////////////////////////////
// ���� �ɼ� ( ���� ��Ű, �ɼ�(�ڵ�����/��û), QWE ����Ű. )
///////////////////////////////////////////////////////////////////////////////


#ifdef CSK_FIX_SKILLHOTKEY_PACKET

#define SendRequestHotKey(option)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x30;\
	spe.AddData( option, 30);\
	spe.Send();\
}

#else // CSK_FIX_SKILLHOTKEY_PACKET

#define SendRequestHotKey(option)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << ( BYTE)0x30;\
	spe.AddData( option, 20);\
	spe.Send();\
}

#endif // CSK_FIX_SKILLHOTKEY_PACKET





#endif

#ifdef YDG_ADD_NEW_DUEL_PROTOCOL
#define SendRequestDuelStart(index, name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << ( BYTE)0x01;\
	spe << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData(name, 10);\
	spe.Send( TRUE);\
}
#define SendRequestDuelOk(ok, index, name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << ( BYTE)0x02;\
	spe << ( BYTE)( ok) << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData( name, 10);\
	spe.Send( TRUE);\
}
#define SendRequestDuelEnd()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << ( BYTE)0x03;\
	spe.Send( TRUE);\
}
#define SendRequestJoinChannel(channelid)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << ( BYTE)0x07;\
	spe << ( BYTE)( channelid);\
	spe.Send( TRUE);\
}
#define SendRequestQuitChannel(channelid)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << ( BYTE)0x09;\
	spe << ( BYTE)( channelid);\
	spe.Send( TRUE);\
}
#else	// YDG_ADD_NEW_DUEL_PROTOCOL
#ifdef DUEL_SYSTEM

#define SendRequestDuelStart(index, name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAA);\
	spe << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData(name, 10);\
	spe.Send( TRUE);\
}
#define SendRequestDuelEnd()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAB);\
	spe.Send( TRUE);\
}
#define SendRequestDuelOk(ok, index, name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xAC);\
	spe << ( BYTE)( ok) << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData( name, 10);\
	spe.Send( TRUE);\
}

#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_PROTOCOL

//. �������� �����̵� (0x24)
//. ���ݼ���
#define SendRequestSetSalePrice(offset, money)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << ( BYTE)0x01;\
	spe << ( BYTE)offset;\
	spe << ( INT)money;\
	spe.Send( TRUE);\
}

//. ���λ��� ����(�Ǹ�)
#define SendRequestCreatePersonalShop(name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << ( BYTE)0x02;\
	spe.AddData( name, MAX_SHOPTITLE);\
	spe.Send( TRUE);\
}
//. ���λ��� �ݱ�(�Ǹ�)
#define SendRequestDestoryPersonalShop()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << (BYTE)0x03;\
	spe.Send( TRUE);\
}

//. ���λ��� ����(����)
#define SendRequestOpenPersonalShop(index, Id)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << (BYTE)0x05;\
	spe << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData(Id, MAX_ID_SIZE);\
	spe.Send( TRUE);\
}

//. ������ ����
#define SendRequestPurchase(index, Id, offset)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << (BYTE)0x06;\
	spe << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData(Id, MAX_ID_SIZE);\
	spe << (BYTE)offset;\
	spe.Send( TRUE);\
}

//. ���λ��� �ݱ�(����)
#define SendRequestClosePersonalShop(index, Id)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x3F);\
	spe << (BYTE)0x07;\
	spe << (BYTE)((SHORT)index>>8) << (BYTE)((SHORT)index&0xFF);\
	spe.AddData(Id, MAX_ID_SIZE);\
	spe.Send( TRUE);\
}

//. �κ��丮 ��ü��û(���λ��� ���� ����)
#define SendRequestInventory()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xF3);\
	spe << (BYTE)0x10;\
	spe.Send( TRUE);\
}

//////////////////////////////////////////////////////////////////////////
//  ģ�� �ý���
//////////////////////////////////////////////////////////////////////////

#define SendRequestFriendList()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC0);\
	spe.Send();\
}

#define SendRequestAddFriend(name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC1);\
	spe.AddData(name, 10);\
	spe.Send();\
}

#define SendAcceptAddFriend(result, name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC2);\
	spe << ( BYTE)( result);\
	spe.AddData(name, 10);\
	spe.Send();\
}

#define SendRequestDeleteFriend(name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC3);\
	spe.AddData(name, 10);\
	spe.Send();\
}

#define SendRequestChangeState(ChatState)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC4);\
	spe << (BYTE)(ChatState);\
	spe.Send();\
}

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define SendRequestSendLetter(windowuiid, name, subject, photodir, photoaction, memosize, memo)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC2, 0xC5);\
	spe << (DWORD)(windowuiid);\
	spe.AddData(name, MAX_ID_SIZE);\
	spe.AddData(subject, MAX_LETTER_TITLE_LENGTH);\
	spe << (BYTE)(photodir);\
	spe << (BYTE)(photoaction);\
	spe << (WORD)(memosize);\
	spe.AddData(memo, memosize);\
	spe.Send(TRUE, TRUE);\
}
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define SendRequestSendLetter(windowuiid, name, subject, photodir, photoaction, memosize, memo)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC2, 0xC5);\
	spe << (DWORD)(windowuiid);\
	spe.AddData(name, 10);\
	spe.AddData(subject, 32);\
	spe << (BYTE)(photodir);\
	spe << (BYTE)(photoaction);\
	spe << (WORD)(memosize);\
	spe.AddData(memo, memosize);\
	spe.Send(TRUE, TRUE);\
}
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE


#define SendRequestLetterText(index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC7);\
	spe.AddNullData( 1);\
	spe << (WORD)(index);\
	spe.Send();\
}

#define SendRequestDeleteLetter(index)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC8);\
	spe.AddNullData( 1);\
	spe << (WORD)(index);\
	spe.Send();\
}

#define SendRequestDeliverLetter()\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xC9);\
	spe.Send();\
}

#define SendRequestCreateChatRoom(Name)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xCA);\
	spe.AddData(Name, 10);\
	spe.Send();\
}

#define SendRequestCRInviteFriend(Name, RoomNumber, WindowUIID)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xCB);\
	spe.AddData(Name, 10);\
	spe.AddNullData( 1);\
	spe << (WORD)(RoomNumber);\
	spe << (DWORD)(WindowUIID);\
	spe.Send();\
}

#define SendRequestCRConnectRoom(pSocketClient, RoomNumber, Ticket)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x00);\
	spe.AddNullData( 1);\
	spe << (WORD)(RoomNumber);\
	spe.AddData(Ticket, 10);\
	g_pSocketClient = pSocketClient;\
	spe.Send();\
	g_pSocketClient = &SocketClient;\
}

#define SendRequestCRDisconnectRoom(pSocketClient)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x01);\
	g_pSocketClient = pSocketClient;\
	spe.Send();\
	g_pSocketClient = &SocketClient;\
}

#define SendRequestCRUserList(pSocketClient)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x02);\
	g_pSocketClient = pSocketClient;\
	spe.Send();\
	g_pSocketClient = &SocketClient;\
}

#define SendRequestCRChatText(pSocketClient, Index, MsgSize, Msg)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x04);\
	spe << (BYTE)(Index);\
	spe << (BYTE)(MsgSize);\
	BuxConvert((BYTE *)Msg, MsgSize);\
	spe.AddData(Msg, MsgSize);\
	g_pSocketClient = pSocketClient;\
	spe.Send();\
	g_pSocketClient = &SocketClient;\
}

#define SendRequestCRConnectCheck(pSocketClient)\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0x05);\
	g_pSocketClient = pSocketClient;\
	spe.Send();\
	g_pSocketClient = &SocketClient;\
}

//////////////////////////////////////////////////////////////////////////
//  �� �ý���.
//////////////////////////////////////////////////////////////////////////
#ifdef PET_SYSTEM

//  �� ��ɾ� ������ ��û�Ѵ�.
#define SendRequestPetCommand(PetType, Command, Key )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xA7);\
	spe << (BYTE)(PetType);\
	spe << (BYTE)(Command);\
	spe << (BYTE)( (Key)>>8 ) << (BYTE)( (Key)&0xff);\
	spe.Send();\
}


//  ���� ������ ��û�Ѵ�.
#define SendRequestPetInfo(PetType, InvType, nPos )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xA9);\
    spe << (BYTE)(PetType);\
    spe << (BYTE)(InvType);\
    spe << (BYTE)(nPos);\
	spe.Send();\
}


#endif// PET_SYSTEM


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
#define SendChangeMServer(lpID, lpChr, iAuth1, iAuth2, iAuth3, iAuth4 )\
{\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+2];\
	char lpszCHR[MAX_ID_SIZE+2];\
	ZeroMemory( lpszID, MAX_ID_SIZE+2);\
	ZeroMemory( lpszCHR, MAX_ID_SIZE+2);\
	strcpy( lpszID, lpID);\
	strcpy( lpszCHR, lpChr);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE+2);\
	spe.AddData( lpszID, MAX_ID_SIZE+2);\
	spe.AddData( lpszCHR, MAX_ID_SIZE+2);\
	spe << (INT)(iAuth1);\
	spe << (INT)(iAuth2);\
	spe << (INT)(iAuth3);\
	spe << (INT)(iAuth4);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
	spe << ( BYTE)( Version[i]-(i+1));\
	for(int i=0;i<SIZE_PROTOCOLSERIAL;i++)\
	spe << Serial[i];\
	spe.Send(TRUE);\
	hanguo_check3();\
}
#else // _VS2008PORTING
#define SendChangeMServer(lpID, lpChr, iAuth1, iAuth2, iAuth3, iAuth4 )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB1);\
	spe << ( BYTE)0x01;\
	char lpszID[MAX_ID_SIZE+2];\
	char lpszCHR[MAX_ID_SIZE+2];\
	ZeroMemory( lpszID, MAX_ID_SIZE+2);\
	ZeroMemory( lpszCHR, MAX_ID_SIZE+2);\
	strcpy( lpszID, lpID);\
	strcpy( lpszCHR, lpChr);\
	BuxConvert(( BYTE*)lpszID,MAX_ID_SIZE+2);\
	spe.AddData( lpszID, MAX_ID_SIZE+2);\
	spe.AddData( lpszCHR, MAX_ID_SIZE+2);\
    spe << (INT)(iAuth1);\
    spe << (INT)(iAuth2);\
    spe << (INT)(iAuth3);\
    spe << (INT)(iAuth4);\
	spe << GetTickCount();\
	for(int i=0;i<SIZE_PROTOCOLVERSION;i++)\
    	spe << ( BYTE)( Version[i]-(i+1));\
	for(i=0;i<SIZE_PROTOCOLSERIAL;i++)\
    	spe << Serial[i];\
    spe.Send(TRUE);\
    hanguo_check3();\
}
#endif // _VS2008PORTING


//----------------------------------------------------------------------------
// CG [0xB2][0x00] Ŭ���̾�Ʈ�� ������ ���������� ��û
//----------------------------------------------------------------------------
#define SendRequestBCStatus()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x00;\
    spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x01] ������ ����� ��û
//----------------------------------------------------------------------------
#define SendRequestBCReg()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x01;\
    spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x02] ������ ���⸦ ��û
//----------------------------------------------------------------------------
#define SendRequestBCGiveUp( GiveUp )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x02;\
	spe << (BYTE)GiveUp;\
    spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x03] �ڽ��� ����� ������Ͽ� ���� ������ ��û
//----------------------------------------------------------------------------
#define SendRequestBCRegInfo()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x03;\
    spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x04] �ڽ��� ����� ������ ǥ�� ��� ��û
//----------------------------------------------------------------------------
#define SendRequestBCRegMark( ItemPos )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x04;\
 	spe << (BYTE)ItemPos;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x05] ������ NPC ���� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCNPCBuy( NPCNumber, NPCIndex )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x05;\
	spe << (int)NPCNumber;\
	spe << (int)NPCIndex;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x06] ������ NPC ���� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCNPCRepair( NPCNumber, NPCIndex )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x06;\
	spe << (int)NPCNumber;\
	spe << (int)NPCIndex;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x07] ������ NPC ���׷��̵� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCNPCUpgrade( NPCNumber, NPCIndex, NPCUpType, NPCUpValue )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x07;\
	spe << (int)NPCNumber;\
	spe << (int)NPCIndex;\
	spe << (int)NPCUpType;\
	spe << (int)NPCUpValue;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x08] ���� ���� �ڱ�, ���� ���� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCGetTaxInfo()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x08;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x09] ���� ���� ���� ���� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCChangeTaxRate( TaxType, TaxRate1, TaxRate2, TaxRate3, TaxRate4 )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x09;\
	spe << (BYTE)TaxType;\
    spe << (BYTE)TaxRate1 << (BYTE)TaxRate2 <<(BYTE)TaxRate3 <<(BYTE)TaxRate4;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB2][0x10] ���� ���� �ڱ� ��� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCWithdraw( Money1, Money2, Money3, Money4 )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB2);\
	spe << (BYTE)0x10;\
	spe << (BYTE)Money1;\
	spe << (BYTE)Money2;\
	spe << (BYTE)Money3;\
	spe << (BYTE)Money4;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB3] �������� DB�� �����Ǵ� Ư�� NPC�� ����� ��û -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCNPCList( MonsterCode )\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB3);\
	spe << (BYTE)MonsterCode;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB4] ���� ��� ����� ��û (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCDeclareGuildList()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB4);\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xB5] ���� Ȯ�� ����� ��û (0xC1)
//----------------------------------------------------------------------------
#define SendRequestBCGuildList()\
{\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xB5);\
	spe.Send();\
}

//////////////////////////////////////////////////////////////////////////
//  CG [0xB2][0x1F] �� ����� ���� ���� ���� ���� ��û ���� ( 0xC1 )
//////////////////////////////////////////////////////////////////////////
#define SendRequestHuntZoneEnter( p_HuntZoneEnter )\
{\
    pre_send( g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0xB2 );\
    spe << (BYTE)0x1F;\
    spe << (BYTE)p_HuntZoneEnter;\
    spe.Send();\
}


    //////////////////////////////////////////////////////////////////////////
    //  ���� ������ ����(���)�� ��ũ�� �����ּ���.
    //////////////////////////////////////////////////////////////////////////
    #define SendGetCastleGuildMark()\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB9);\
        spe << (BYTE)0x02;\
        spe.Send();\
    }


    //////////////////////////////////////////////////////////////////////////
    //  ����͸ʿ� ����.
    //////////////////////////////////////////////////////////////////////////
    #define SendCastleHuntZoneEnter( p_Money)\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB9);\
        spe << (BYTE)0x05;\
        spe << (INT)p_Money;\
        spe.Send();\
    }


    //////////////////////////////////////////////////////////////////////////
    //  ������ ���ų� �ݴ� ����� �Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    #define SendGateOparator( p_Operator, p_Key )\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB2);\
        spe << (BYTE)0x12;\
        spe << (BYTE)p_Operator << (BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff);\
        spe.Send();\
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� ���� �߻� ��� ��û.
    //////////////////////////////////////////////////////////////////////////
    #define SendCatapultFire( p_Key, p_Index )\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB7);\
        spe << (BYTE)0x01;\
        spe << (BYTE)( ( p_Key) >> 8) << ( BYTE)( ( p_Key)&0xff) << ( BYTE)(p_Index);\
        spe.Send();\
    }

    
    //////////////////////////////////////////////////////////////////////////
    //  ���� ���߽� ������ �����ߴٴ� �޼����� ������.
    //////////////////////////////////////////////////////////////////////////
    #define SendWeaponExplosion( p_KeyH, p_KeyL )\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB7);\
        spe << (BYTE)0x04;\
        spe << (BYTE)p_KeyH << ( BYTE)p_KeyL;\
        spe.Send();\
    }


    #define SendGuildCommand( p_Team, p_posX, p_posY, p_Cmd )\
    {\
        pre_send( g_hInst);\
        CStreamPacketEngine spe;\
        spe.Init( 0xC1, 0xB2);\
        spe << (BYTE)0x1D;\
        spe << (BYTE)p_Team << (BYTE)p_posX << (BYTE)p_posY << (BYTE)p_Cmd;\
        spe.Send();\
    }


//////////////////////////////////////////////////////////////////////////
// ũ���� ���� ���̵� MVP 1�� ���� �Լ�
//////////////////////////////////////////////////////////////////////////

#define SendRequestCrywolfInfo( )\
{	\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xBD);\
	spe << (BYTE)0x00;\
	spe.Send();\
}

#define SendRequestCrywolfAltarContract(p_Key)\
{	\
    pre_send( g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init( 0xC1, 0xBD);\
    spe << (BYTE)0x03;\
    spe << (BYTE)( (p_Key)>>8 ) << (BYTE)( (p_Key)&0xff);\
    spe.Send();\
}

#define SendRequestCrywolfBenefitPlusChaosRate( )\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xBD);\
	spe << (BYTE)0x09;\
	spe.Send();\
}

#define SendRequestKanturuInfo( )\
{	\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD1);\
	spe << (BYTE)0x00;\
	spe.Send();\
}

#define SendRequestKanturuEnter( )\
{	\
    pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD1);\
	spe << (BYTE)0x01;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xD0][0x00] PC�� Ŭ���̾�Ʈ�� ���� ������ ���� ��û
//----------------------------------------------------------------------------
#ifdef PCROOM_EVENT
#define SendRequestPCRoomCouponItem( )\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD0);\
	spe << (BYTE)0x00;\
	spe.Send();\
}
#endif // PCROOM_EVENT

//----------------------------------------------------------------------------
// CG [0xD0][0x03] Ŭ���̾�Ʈ�� ȭ��Ʈ���� �̺�Ʈ ������ �ޱ⸦ ��û�Ѵ�.
//----------------------------------------------------------------------------
#define SendRequestWhiteAngelItem( )\
{	\
	pre_send( g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD0);\
	spe << (BYTE)0x03;\
	spe.Send();\
}

#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
//----------------------------------------------------------------------------
// CG [0xD0][0x05] PC�� ����Ʈ ������ ���� ��û
//----------------------------------------------------------------------------
#define SendRequestPCRoomPointItemBuy(byInvenPos)\
{\
    pre_send(g_hInst);\
    CStreamPacketEngine spe;\
    spe.Init(0xC1, 0xD0);\
	spe << (BYTE)0x05;\
    spe << (BYTE)byInvenPos;\
    spe.Send();\
}

//----------------------------------------------------------------------------
// CG GC [0xD0][0x06] PC�� ����Ʈ �� ���� ��û
//----------------------------------------------------------------------------
#define SendRequestPCRoomPointShopOpen()\
{\
	pre_send(g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0xD0);\
	spe << (BYTE)0x06;\
	spe.Send();\
}

#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM

//----------------------------------------------------------------------------
// CG [0xD0][0x07] 3�� ���� ����Ʈ - ��������� ���� �߰����� ���� ���� ��û
//----------------------------------------------------------------------------
#define SendRequestEnterOnWerwolf()\
{\
	pre_send(g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0xD0);\
	spe << (BYTE)0x07;\
	spe.Send();\
}

//----------------------------------------------------------------------------
// CG [0xD0][0x08] 3�� ���� ����Ʈ - ������(����)�� ���� �߰����� �Ƚ�ó ���� ��û
//----------------------------------------------------------------------------
#define SendRequestEnterOnGateKeeper()\
{\
	pre_send(g_hInst);\
	CStreamPacketEngine spe;\
	spe.Init(0xC1, 0xD0);\
	spe << (BYTE)0x08;\
	spe.Send();\
}

#ifdef PRUARIN_EVENT07_3COLORHARVEST
//----------------------------------------------------------------------------
// CG [0xD0][0x09] ������ ���� NPC�ٷ� - ������ ���� ��û
//----------------------------------------------------------------------------
#define SendRequest3ColorHarvestItem( )\
{	\
	pre_send( g_hInst );\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD0 );\
	spe << (BYTE)0x09;\
	spe.Send();\
}
#endif // PRUARIN_EVENT07_3COLORHARVEST

#ifdef LDK_ADD_SANTA_NPC
//----------------------------------------------------------------------------
// CG [0xD0][0x10] ������ ���� �ؿܻ�ŸNPC - ������ ���� ��û
//----------------------------------------------------------------------------
#define SendRequestSantaItem( )\
{	\
	pre_send( g_hInst );\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD0 );\
	spe << (BYTE)0x10;\
	spe.Send();\
}
#endif //LDK_ADD_SANTA_NPC

#ifdef LDK_ADD_SNOWMAN_NPC
//----------------------------------------------------------------------------
// CG [0xD0][0x0a] ����ƽ��� �̵� �ؿܴ����NPC
//----------------------------------------------------------------------------
#define SendRequestMoveDevias( )\
{	\
	pre_send( g_hInst );\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD0 );\
	spe << (BYTE)0x0a;\
	spe.Send();\
}
#endif //LDK_ADD_SNOWMAN_NPC

#ifdef CSK_RAKLION_BOSS
//----------------------------------------------------------------------------
// CG [0xD1][0x10] ������ ��Ŭ���� �������� ���� ���� ���� ��û
//----------------------------------------------------------------------------
#define SendRequestRaklionStateInfo()\
{	\
	pre_send( g_hInst );\
	CStreamPacketEngine spe;\
	spe.Init( 0xC1, 0xD1 );\
	spe << (BYTE)0x10;\
	spe.Send();\
}
#endif // CSK_RAKLION_BOSS

#define SendRequestCursedEnter( mapnumber, itempos ) \
{ \
	pre_send(g_hInst); \
	CStreamPacketEngine spe; \
	spe.Init(0xC1, 0xBF); \
	spe << (BYTE)0x00; \
	spe << (BYTE)mapnumber << (BYTE)itempos; \
	spe.Send(); \
}

#define SendRequestCursedTempleMagic( MagicNumber, TargetObjIndex, Dis ) \
{ \
	pre_send(g_hInst); \
	CStreamPacketEngine spe; \
	WORD Magic = (WORD)MagicNumber;\
	spe.Init(0xC1, 0xBF); \
	spe << (BYTE)0x02; \
	spe << ( BYTE)(HIBYTE(Magic))<<( BYTE)(LOBYTE(Magic))<< (BYTE)((TargetObjIndex)>>8) << (BYTE)((TargetObjIndex)&0xff) << (BYTE)Dis; \
	spe.Send(); \
}

#define SendRequestCursedTempleRequital() \
{ \
	pre_send(g_hInst); \
	CStreamPacketEngine spe; \
	spe.Init(0xC1, 0xBF); \
	spe << (BYTE)0x05; \
	spe.Send(); \
}

#define SendRequestMasterLevelSkill(SkillNum) \
{ \
	pre_send(g_hInst); \
	CStreamPacketEngine spe; \
	spe.Init(0xC1, 0xF3); \
	spe << (BYTE)0x52; \
	spe << (int)SkillNum;\
	spe.Send(); \
}


#ifdef NEW_USER_INTERFACE_SERVERMESSAGE

//////////////////////////////////////////////////////////////////////////
// [ĳ���� ���� ��û] 0xF5, 0x01
//////////////////////////////////////////////////////////////////////////
// ĳ�� �� �������̽� ���� ( 0:�ݱ�, 1:����)
// ĳ�� ���� �� ���� �ִ� �� (0;����, 1:����)
#define SendRequestCashShopInOut( IsShopOpen, ShopOpenAlready ) \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF5); \
	spe << (BYTE)0x01;\
    spe << (BYTE)IsShopOpen << (BYTE)ShopOpenAlready; \
    spe.Send(); \
}
//////////////////////////////////////////////////////////////////////////
// [ĳ�� ����Ʈ �ܷ� ��û] 0xF5, 0x03
//////////////////////////////////////////////////////////////////////////
#define SendRequestCashShopCashPoint() \
{ \
    pre_send( g_hInst); \
	CStreamPacketEngine spe; \
	spe.Init( 0xC1, 0xF5); \
	spe << (BYTE)0x03;\
	spe.Send(); \
}
//////////////////////////////////////////////////////////////////////////
// [ĳ�� ������ ����Ʈ ��û] 0xF5, 0x05
//////////////////////////////////////////////////////////////////////////
// ������ ����Ʈ ī�װ�
// ������ �ε���
// �ش� �������� ����Ʈ�� �������� �ִ°� (0:����, 1:����)
#define SendRequestCashShopItemlist( CategoryIndex, PageIndex, btPageLoaded ) \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF5); \
	spe << (BYTE)0x05;\
    spe << (BYTE)CategoryIndex << (BYTE)PageIndex << (BYTE)btPageLoaded; \
    spe.Send(); \
}
//////////////////////////////////////////////////////////////////////////
// [ĳ���� ���� ��û] 0xF5, 0x07
//////////////////////////////////////////////////////////////////////////
#define SendRequestCashShopItemPurchase( itemcode, shopcategoryindex ) \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF5); \
	spe << (BYTE)0x07;\
    spe << (DWORD)itemcode << (BYTE)shopcategoryindex; \
    spe.Send(); \
}

#endif //NEW_USER_INTERFACE_SERVERMESSAGE

#ifdef PJH_CHARACTER_RENAME
#define SendRequestCheckChangeName( PCharaterName ) \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF3); \
	spe << (BYTE)0x15;\
	spe.AddData( (PCharaterName), MAX_ID_SIZE);\
    spe.Send(); \
}

#define SendRequestChangeName( POldName, PNewName ) \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF3); \
	spe << (BYTE)0x16;\
	spe.AddData( (POldName), MAX_ID_SIZE);\
	spe.AddData( (PNewName), MAX_ID_SIZE);\
    spe.Send(); \
}
#endif //PJH_CHARACTER_RENAME

#ifdef PSW_ADD_RESET_CHARACTER_POINT
#define SendRequestResetCharacterPoint() \
{ \
    pre_send( g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF2); \
	spe << (BYTE)0x00;\
    spe.Send(); \
}
#endif //PSW_ADD_RESET_CHARACTER_POINT

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
//////////////////////////////////////////////////////////////////////////
// [����� ���� ����] 0xBF
//////////////////////////////////////////////////////////////////////////

// ��ϵ� ���� ���� ��û
#define SendRequestRegistedLuckyCoin() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x0b;\
    spe.Send(); \
}

//���� ��� ��û
#define SendRequestRegistLuckyCoin() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x0C;\
    spe.Send(); \
}

//���� ��ȯ ��û
#define SendRequestExChangeLuckyCoin(nCoinCnt) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x0D;\
	spe << (int)nCoinCnt;\
    spe.Send(); \
}

#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

#ifdef YDG_ADD_DOPPELGANGER_PROTOCOLS
// ���ð��� ���� ��û
#define SendRequestEnterDoppelGangerEvent(btItemPos) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x0E;\
	spe << (BYTE)btItemPos;\
    spe.Send(); \
}
#endif	// YDG_ADD_DOPPELGANGER_PROTOCOLS

#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
// ���� ��ȣ�� ���� ��û
#define SendRequestEnterEmpireGuardianEvent() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xF7); \
	spe << (BYTE)0x01;\
	spe << (BYTE)0x01;\
    spe.Send(); \
}
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS


#ifdef LDS_ADD_SERVERPROCESSING_UNITEDMARKETPLACE
// ���� ���� ���� ��û
#define SendRequestEnterUnitedMarketPlaceEvent() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x17;\
    spe.Send(); \
}
#endif // LDS_ADD_SERVERPROCESSING_UNITEDMARKETPLACE


// �ΰ��Ӽ� ��������
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
//////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ - �������� ĳ���� ���� ��������
//////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// ������� ĳ�� ����Ʈ ���� ��û (0xD2)(0x01)
//----------------------------------------------------------------------------
#define SendRequestIGS_CashPointInfo() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x01; \
    spe.Send(); \
}


//----------------------------------------------------------------------------
// ĳ���� ���� ��û (0xD2)(0x02)
//----------------------------------------------------------------------------
// byShopOpened - �� �������̽� ���� Ÿ�� ( 0 : ����, 1 : �ݱ� )
#define SendRequestIGS_CashShopOpen(byShopOpenType) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x02; \
	spe << (BYTE)byShopOpenType; \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// ������ ���� ��û (0xD2)(0x03)
//----------------------------------------------------------------------------
// lBuyItemPackageSeq - Packege��ǰ SeqIndex
// lBuyItemDisplaySeq - ���� ���� SeqIndex(Product Index)
// lBuyItemPriceSeq - ���� Index
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#define SendRequestIGS_BuyItem(lBuyItemPackageSeq, lBuyItemDisplaySeq, lBuyItemPriceSeq, wItemCode, iCashType) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x03; \
	spe << (long)lBuyItemPackageSeq; \
	spe << (long)lBuyItemDisplaySeq; \
	spe << (long)lBuyItemPriceSeq; \
	spe << (WORD)wItemCode; \
	spe << (int)iCashType; \
    spe.Send(); \
}
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#ifdef LJH_MOD_SEND_TYPE_OF_PAYMENT_DUE_TO_CHANGED_LIBRARY
#define SendRequestIGS_BuyItem(lBuyItemPackageSeq, lBuyItemDisplaySeq, lBuyItemPriceSeq, wItemCode, bBuyingWithGP) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x03; \
	spe << (long)lBuyItemPackageSeq; \
	spe << (long)lBuyItemDisplaySeq; \
	spe << (long)lBuyItemPriceSeq; \
	spe << (WORD)wItemCode; \
	spe << (BOOL)bBuyingWithGP; \
    spe.Send(); \
}
#else  //LJH_MOD_SEND_TYPE_OF_PAYMENT_DUE_TO_CHANGED_LIBRARY 
#define SendRequestIGS_BuyItem(lBuyItemPackageSeq, lBuyItemDisplaySeq, lBuyItemPriceSeq, wItemCode) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x03; \
	spe << (long)lBuyItemPackageSeq; \
	spe << (long)lBuyItemDisplaySeq; \
	spe << (long)lBuyItemPriceSeq; \
	spe << (WORD)wItemCode; \
    spe.Send(); \
}
#endif //LJH_MOD_SEND_TYPE_OF_PAYMENT_DUE_TO_CHANGED_LIBRARY
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

//----------------------------------------------------------------------------
// ������ �����ϱ� ��û (0xD2)(0x04)
//----------------------------------------------------------------------------
// lGiftItemPackageSeq - ���� Package��ǰ SeqIndex
// lGiftItemPriceSeq - ���������� ���� ����
// lGiftItemDisplaySeq - ���������� ���� ���� Seqindex
// lSaleZone - �Ǹ� ����
// pstrReceiveUserID - �������� ID
// pstrGiftMessage - ���� Message
#ifdef KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#define SendRequestIGS_SendItemGift(lGiftItemPackageSeq, lGiftItemPriceSeq, lGiftItemDisplaySeq, \
	lSaleZone, wItemCode, iCashType, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+1]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE]; \
	ZeroMemory( strReceiveUserID, MAX_ID_SIZE+1); \
	ZeroMemory( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x04; \
	spe << (long)lGiftItemPackageSeq; \
	spe << (long)lGiftItemPriceSeq; \
	spe << (long)lGiftItemDisplaySeq; \
	spe << (long)lSaleZone; \
	spe << (WORD)wItemCode; \
	spe << (int)iCashType; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL


#ifdef LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT
#define SendRequestIGS_SendItemGift(lGiftItemPackageSeq, lGiftItemPriceSeq, lGiftItemDisplaySeq, \
	lSaleZone, wItemCode, bCashType, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+1]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE]; \
	ZeroMemory( strReceiveUserID, MAX_ID_SIZE+1); \
	ZeroMemory( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x04; \
	spe << (long)lGiftItemPackageSeq; \
	spe << (long)lGiftItemPriceSeq; \
	spe << (long)lGiftItemDisplaySeq; \
	spe << (long)lSaleZone; \
	spe << (WORD)wItemCode; \
	spe << (bool)bCashType; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}
#else // LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT
#define SendRequestIGS_SendItemGift(lGiftItemPackageSeq, lGiftItemPriceSeq, lGiftItemDisplaySeq, \
	lSaleZone, wItemCode, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+1]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE]; \
	ZeroMemory( strReceiveUserID, MAX_ID_SIZE+1); \
	ZeroMemory( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x04; \
	spe << (long)lGiftItemPackageSeq; \
	spe << (long)lGiftItemPriceSeq; \
	spe << (long)lGiftItemDisplaySeq; \
	spe << (long)lSaleZone; \
	spe << (WORD)wItemCode; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}
#endif // LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#else KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#define SendRequestIGS_SendItemGift(lGiftItemPackageSeq, lGiftItemPriceSeq, lGiftItemDisplaySeq, \
									lSaleZone, iCashType, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+1]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE]; \
	ZeroMemory( strReceiveUserID, MAX_ID_SIZE+1); \
	ZeroMemory( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x04; \
	spe << (long)lGiftItemPackageSeq; \
	spe << (long)lGiftItemPriceSeq; \
	spe << (long)lGiftItemDisplaySeq; \
	spe << (long)lSaleZone; \
	spe << (int)iCashType; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}
#else // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

#define SendRequestIGS_SendItemGift(lGiftItemPackageSeq, lGiftItemPriceSeq, lGiftItemDisplaySeq, \
	lSaleZone, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+1]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE]; \
	ZeroMemory( strReceiveUserID, MAX_ID_SIZE+1); \
	ZeroMemory( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x04; \
	spe << (long)lGiftItemPackageSeq; \
	spe << (long)lGiftItemPriceSeq; \
	spe << (long)lGiftItemDisplaySeq; \
	spe << (long)lSaleZone; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL

//----------------------------------------------------------------------------
// ������ ������ ����Ʈ ��û (0xD2)(0x05)
//----------------------------------------------------------------------------
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
#define SendRequestIGS_ItemStorageList(iPageIndex, szStorageType) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x05; \
	spe << (int)iPageIndex; \
	spe.AddData( szStorageType, sizeof(char)+1 ); \
    spe.Send(); \
}
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
#define SendRequestIGS_ItemStorageList() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x05; \
    spe.Send(); \
}
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

//----------------------------------------------------------------------------
// ĳ�� �����ϱ� ��û (0xD2)(0x07)
//----------------------------------------------------------------------------
// dCashValue - ĳ�ü��� �׼�
// pstrReceiveUserID - �������� ID
// pstrMessage - ���� Message
#define SendRequestIGS_SendCashGift(dCashValue, pstrReceiveUserID, pstrGiftMessage) \
{ \
	char strReceiveUserID[MAX_ID_SIZE+2]; \
	char strGiftMessage[MAX_GIFT_MESSAGE_SIZE+1]; \
	ZeroMemory( lpszID, MAX_ID_SIZE+2); \
	ZeroMemory( lpszPass, MAX_GIFT_MESSAGE_SIZE+1); \
	memcpy( strReceiveUserID, pstrReceiveUserID, MAX_ID_SIZE+1 ); \
	memcpy( strGiftMessage, pstrGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x07; \
	spe << (double)dCashValue; \
	spe.AddData( strReceiveUserID, MAX_ID_SIZE+1); \
	spe.AddData( strGiftMessage, MAX_GIFT_MESSAGE_SIZE); \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// ����ڰ� ��ǰ�� ����/������ �������� Ȯ�� ��û(0xD2)(0x08)
//----------------------------------------------------------------------------
#define SendRequestIGS_PossibleBuy() \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x08; \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// ��ǰ �ܿ� ���� ��ȸ ��û (0xD2)(0x09)
//----------------------------------------------------------------------------
// lPackageSeq - Package SeqIndex
#define SendRequestIGS_LeftCountItem(lPackageSeq) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x09; \
	spe << (long)lPackageSeq; \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// ������ ������ ������ ��û (0xD2)(0x0A)
//----------------------------------------------------------------------------
// lStorageSeq - ������ ����
// lStorageItemSeq - ������ Item SeqIndex
// pstrStorageItemType - C : ĳ��, P : ��ǰ
#define SendRequestIGS_DeleteStorageItem(lStorageSeq, lStorageItemSeq, pstrStorageItemType) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x0A; \
	spe << (long)lStorageSeq; \
	spe << (long)lStorageItemSeq; \
	spe.AddData( pstrStorageItemType, sizeof(char)); \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// ������ ������ ��� ��û (0xD2)(0x0B)
//----------------------------------------------------------------------------
// lStorageSeq - ������ ����
// lStorageItemSeq - ������ Item SeqIndex
// pstrStorageItemType - C : ĳ��, P : ��ǰ
#define SendRequestIGS_UseStorageItem(lStorageSeq, lStorageItemSeq, wItemCode, pstrStorageItemType) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x0B; \
	spe << (long)lStorageSeq; \
	spe << (long)lStorageItemSeq; \
	spe << (WORD)wItemCode; \
	spe.AddData( pstrStorageItemType, sizeof(char)); \
    spe.Send(); \
}

//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ ��û (0xD2)(0x13)
//---------------------------------------------------------------------------
#define SendRequestIGS_EventItemList(lEventCategorySeq) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xD2); \
	spe << (BYTE)0x13; \
	spe << (long)lEventCategorySeq; \
    spe.Send(); \
}


#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef PBG_MOD_GAMEGUARD_HANDLE
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define SendRequestNpDisconnect( pTick ) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0xBF); \
	spe << (BYTE)0x16;\
	spe << (DWORD)pTick; \
    spe.Send(); \
}
#endif //PBG_MOD_GAMEGUARD_HANDLE
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
//----------------------------------------------------------------------------
// �κ� ���� �ý��ۿ��� ������ ���� ��û (0xBF)(0x20)
// iValue: 254-������û, 255-������û
//---------------------------------------------------------------------------
__forceinline bool SendRequestEquippingInventoryItem(int iItemPos, int iValue)
{ 
	pre_send(g_hInst); 
    CStreamPacketEngine spe; 
    spe.Init( 0xC1, 0xBF); 
	spe << (BYTE)0x20;
	spe << (BYTE)iItemPos; 
	spe << (BYTE)iValue; 
    spe.Send(); 

#ifdef CONSOLE_DEBUG
	g_ConsoleDebug->Write(MCD_SEND, "0xBF, 0x20����[SendRequestEquippingInventoryItem(%d, %d)]", iItemPos, iValue);
#endif // CONSOLE_DEBUG
	return true;

}
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#ifdef _DEBUG
__forceinline void SendRequestRageAtt(int Type,int Key)
{
	if( !IsCanBCSkill(Type) )
		return;
	if(!FindText2(Hero->ID,"webzen"))
	{
		pre_send( g_hInst);
		CStreamPacketEngine spe;
		WORD p_Type = (WORD)Type;
		spe.Init( 0xC1, 0x4A);
		spe << ( BYTE)(HIBYTE(p_Type))<<( BYTE)(LOBYTE(p_Type)) << (BYTE)(0) << ( BYTE)(Key>>8) << ( BYTE)(Key&0xff);
		spe.Send( TRUE);
		hanguo_check3();
	}
}

__forceinline void SendRequestDarkside(WORD nSkill, int Key)
{
    pre_send(g_hInst);
    CStreamPacketEngine spe;
    spe.Init( 0xC1, 0x4B);
	spe <<(BYTE)(HIBYTE(nSkill))<<(BYTE)(LOBYTE(nSkill))<<(BYTE)(Key>>8)<<(BYTE)(Key&0xff);
	spe.Send( TRUE);
}
#else //_DEBUG
#define SendRequestRageAtt( p_Type, p_Key)\
{\
    if(!FindText2(Hero->ID,"webzen"))\
	{\
		pre_send( g_hInst);\
		CStreamPacketEngine spe;\
		WORD Type = (WORD)p_Type;\
		spe.Init( 0xC1, 0x4A);\
		spe << ( BYTE)(HIBYTE(Type))<<( BYTE)(LOBYTE(Type)) << (BYTE)(0) << ( BYTE)( (p_Key)>>8) << ( BYTE)( (p_Key)&0xff);\
		spe.Send( TRUE);\
		hanguo_check3();\
	}\
}

#define SendRequestDarkside( nSkill, p_Key) \
{ \
    pre_send(g_hInst); \
    CStreamPacketEngine spe; \
    spe.Init( 0xC1, 0x4B); \
	spe <<(BYTE)(HIBYTE(nSkill))<<(BYTE)(LOBYTE(nSkill))<<(BYTE)((p_Key)>>8)<<(BYTE)((p_Key)&0xff);\
    spe.Send(); \
}
#endif //_DEBUG
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

