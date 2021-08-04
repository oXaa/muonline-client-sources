#ifndef __SOCKETCLIENT_H__
#define __SOCKETCLIENT_H__

#pragma once

#include "wsctlc.h"
#include "SimpleModulus.h"
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
#include "SessionCryptor.h"
#endif // PKD_ADD_ENHANCED_ENCRYPTION
#include "CSMapServer.h"

#define WM_ASYNCSELECTMSG (WM_USER+0)

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define MAX_CHAT_SIZE 90
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define MAX_CHAT_SIZE 60
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define SIZE_PROTOCOLVERSION	( 5)
#define SIZE_PROTOCOLSERIAL		( 16)
#define MAX_GUILDNAME			8

#define	REQUEST_JOIN_SERVER      		        0
#define RECEIVE_JOIN_SERVER_WAITING				1	// ���������� �ٻڴ� ����϶�.
#define	RECEIVE_JOIN_SERVER_SUCCESS		        2
#define	RECEIVE_JOIN_SERVER_FAIL_VERSION        3
#define	REQUEST_CREATE_ACCOUNT			        10	// ������.
#define	RECEIVE_CREATE_ACCOUNT_SUCCESS		    11	// ������.
#define	RECEIVE_CREATE_ACCOUNT_FAIL_ID          12	// ������.
#define	RECEIVE_CREATE_ACCOUNT_FAIL_RESIDENT    13	// ������.

#define	REQUEST_LOG_IN					        19
#define	RECEIVE_LOG_IN_SUCCESS			        20
#define	RECEIVE_LOG_IN_FAIL_PASSWORD	        21
#define	RECEIVE_LOG_IN_FAIL_ID			        22
#define RECEIVE_LOG_IN_FAIL_ID_CONNECTED        23
#define RECEIVE_LOG_IN_FAIL_SERVER_BUSY         24
#define RECEIVE_LOG_IN_FAIL_ID_BLOCK            25
#define RECEIVE_LOG_IN_FAIL_VERSION				26
#define RECEIVE_LOG_IN_FAIL_CONNECT				27
#define RECEIVE_LOG_IN_FAIL_ERROR				28
#define RECEIVE_LOG_IN_FAIL_USER_TIME1          29
#define RECEIVE_LOG_IN_FAIL_USER_TIME2          30
#define RECEIVE_LOG_IN_FAIL_PC_TIME1            31
#define RECEIVE_LOG_IN_FAIL_PC_TIME2            32
#define RECEIVE_LOG_IN_FAIL_DATE				33	// ��� ����.
#define RECEIVE_LOG_IN_FAIL_POINT_DATE			34	// �븸 ����
#define RECEIVE_LOG_IN_FAIL_POINT_HOUR			35	// �븸 ����
#define RECEIVE_LOG_IN_FAIL_INVALID_IP			36	// �븸 ����
#define RECEIVE_LOG_IN_FAIL_NO_PAYMENT_INFO		37
#define RECEIVE_LOG_IN_FAIL_ONLY_OVER_15		38
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
#define RECEIVE_LOG_IN_FAIL_CHARGED_CHANNEL		39	// �۷ι� ����.
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET

#define	REQUEST_CHARACTERS_LIST			        50
#define	RECEIVE_CHARACTERS_LIST			        51
#define	REQUEST_CREATE_CHARACTER		        52
#define	RECEIVE_CREATE_CHARACTER_SUCCESS        53
#define	RECEIVE_CREATE_CHARACTER_FAIL           54
#define	RECEIVE_CREATE_CHARACTER_FAIL2          55
#define	REQUEST_DELETE_CHARACTER	            56
#define	RECEIVE_DELETE_CHARACTER_SUCCESS        57
#define REQUEST_JOIN_MAP_SERVER			        60
#define RECEIVE_JOIN_MAP_SERVER			        61
#define	RECEIVE_CONFIRM_PASSWORD_SUCCESS        62	// ������.
#define	RECEIVE_CONFIRM_PASSWORD_FAIL_ID        63	// ������.
#define	RECEIVE_CONFIRM_PASSWORD2_SUCCESS       64	// ������.
#define	RECEIVE_CONFIRM_PASSWORD2_FAIL_ID       65	// ������.
#define	RECEIVE_CONFIRM_PASSWORD2_FAIL_ANSWER   66	// ������.
#define	RECEIVE_CONFIRM_PASSWORD2_FAIL_RESIDENT 67	// ������.
#define RECEIVE_CHANGE_PASSWORD_SUCCESS         68	// ������.
#define RECEIVE_CHANGE_PASSWORD_FAIL_ID         69	// ������.
#define RECEIVE_CHANGE_PASSWORD_FAIL_RESIDENT   70	// ������.
#define RECEIVE_CHANGE_PASSWORD_FAIL_PASSWORD   71	// ������.


#ifdef PJH_CHARACTER_RENAME
#define REQUEST_CHECK_CHANGE_NAME				72
#define RECEIVE_CHECK_CHANGE_NAME				73
#define REQUEST_CHANGE_NAME						74
#define RECEIVE_CHANGE_NAME_RESULT				75
#endif //PJH_CHARACTER_RENAME

#ifdef MODIFY_SOCKET_PROTOCOL
//2008. 5. 22 ���� ������ ���� ���� �ε��� Ȯ���� �� ���ڷ� ����
#define PACKET_ITEM_LENGTH  12
#else	// MODIFY_SOCKET_PROTOCOL
//2005. 7. 11 ������ �ε��� Ȯ���� �� ���ڷ� ����
#define PACKET_ITEM_LENGTH  7
#endif	// MODIFY_SOCKET_PROTOCOL

#define EQUIPMENT_LENGTH    17
#define MAX_SPE_BUFFERSIZE_	( 2048)

#ifdef YDG_MOD_PROTECT_AUTO_V5
#define MAX_HACKTOOL_FILENAME_LENGTH 64
#endif	// YDG_MOD_PROTECT_AUTO_V5

extern int CurrentProtocolState;

typedef struct {
	BYTE Code;
	BYTE Size;
	BYTE HeadCode;
} PBMSG_HEADER, * LPPBMSG_HEADER;

typedef struct {
	BYTE Code;
	BYTE SizeH;
	BYTE SizeL;
	BYTE HeadCode;
} PWMSG_HEADER, * LPPWMSG_HEADER;

// ��ȣȭ ��Ŷ
typedef struct {
	BYTE Code;
	BYTE Size;
	BYTE byBuffer[255];
} PBMSG_ENCRYPTED, * LPPBMSG_ENCRYPTED;

typedef struct {
	BYTE Code;
	BYTE SizeH;
	BYTE SizeL;
	BYTE byBuffer[MAX_SPE_BUFFERSIZE_];
} PWMSG_ENCRYPTED, * LPWBMSG_ENCRYPTED;

//request default SubCode
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
} PREQUEST_DEFAULT_SUBCODE, * LPPREQUEST_DEFAULT_SUBCODE;

//receive default
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Value;
} PHEADER_DEFAULT, * LPPHEADER_DEFAULT;

// ���̳ʽ� ���� ����
typedef struct {
	PBMSG_HEADER	Header;
	BYTE			result;
#ifdef PSW_FRUIT_ITEM
	WORD			btStatValue;	// �� / �� ���Ȱ�
#else //PSW_FRUIT_ITEM
	BYTE			btStatValue;	// �� / �� ���Ȱ�
#endif //PSW_FRUIT_ITEM	
	BYTE			btFruitType;	// ���� ����
} PMSG_USE_STAT_FRUIT, * LPPMSG_USE_STAT_FRUIT;

//receive default subcode
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Value;
} PHEADER_DEFAULT_SUBCODE, * LPPHEADER_DEFAULT_SUBCODE;

//receive Character List 
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
    BYTE         MaxClass;		// ������ �� �ִ� ���� �� - 1.
	BYTE		 MoveCount;
	BYTE         Value;			// �����Ǿ� �ִ� ĳ���� ��.
#ifdef PBG_ADD_CHARACTERSLOT
	BYTE         CharacterSlotCount;	//ĳ���� �������� ��
#endif //PBG_ADD_CHARACTERSLOT
} PHEADER_DEFAULT_CHARACTER_LIST, * LPPHEADER_DEFAULT_CHARACTER_LIST;

#ifdef PBG_ADD_CHARACTERCARD
//////////////////////////////////////////////////////////////////////////
// 0xDE, 0x00	�ؿ� ��ȯ���� ī��� ���� ����
#define CLASS_SUMMONER_CARD		0x01
#define CLASS_DARK_LORD_CARD	0x02
#define CLASS_DARK_CARD			0x04
#define CLASS_CHARACTERCARD_TOTALCNT	3

typedef struct {
	PWMSG_HEADER	header;
	BYTE			CharacterCard;	// ��ũ�ε� ���˻� ĳ���� ī��
} PHEADER_CHARACTERCARD, *LPPHEADER_CHARACTERCARD;

typedef struct {
	bool bCharacterEnable[CLASS_CHARACTERCARD_TOTALCNT];		// Ȱ��ȭ [0]���� [1]��ũ
}CHARACTER_ENABLE, *LPCHARACTER_ENABLE;

extern CHARACTER_ENABLE g_CharCardEnable;
#endif //PBG_ADD_CHARACTERCARD

//receive default key
typedef struct {
	PBMSG_HEADER Header;
	BYTE         KeyH;
	BYTE         KeyL;
} PHEADER_DEFAULT_KEY, * LPPHEADER_DEFAULT_KEY;

//receive default key
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Value;
	BYTE         KeyH;
	BYTE         KeyL;
} PHEADER_DEFAULT_VALUE_KEY, * LPPHEADER_DEFAULT_VALUE_KEY;

//(�̺�Ʈ)���½ð� ��û.
typedef struct {
    PBMSG_HEADER Header;
    BYTE         Value;
    BYTE         KeyH;
    BYTE         KeyM;
    BYTE         KeyL;
} PHEADER_MATCH_OPEN_VALUE, * LPPHEADER_MATCH_OPEN_VALUE;

// ���� �ɸ� ���� �ٲٱ� ��Ŷ
typedef struct
{
	PBMSG_HEADER Header;
	BYTE		State;				// 0 : ����, 1 : ��������
	BYTE		KeyH;
	BYTE		KeyL;
	BYTE		BuffIndex;
} PMSG_VIEWSKILLSTATE, *LPPMSG_VIEWSKILLSTATE;

//receive default(word)
typedef struct {
	PWMSG_HEADER Header;
	BYTE         Value;
} PWHEADER_DEFAULT_WORD, * LPPWHEADER_DEFAULT_WORD;

//receive default(word)
typedef struct {
	PWMSG_HEADER Header;
	INT          Value;
} PWHEADER_DEFAULT_WORD2, * LPPWHEADER_DEFAULT_WORD2;



//receive default subcode(word)
typedef struct {
	PWMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Value;
	
} PHEADER_DEFAULT_SUBCODE_WORD, * LPPHEADER_DEFAULT_SUBCODE_WORD;

typedef struct {
	PBMSG_HEADER Header;
	WORD        Value;
} PHEADER_DEFAULT_WORD, * LPPHEADER_DEFAULT_WORD;

typedef struct {
	PBMSG_HEADER Header;
	DWORD        Value;
} PHEADER_DEFAULT_DWORD, * LPPHEADER_DEFAULT_DWORD;

typedef struct {
	PBMSG_HEADER Header;
	BYTE        byBuffer[1024];
} PHEADER_DEFAULT_CUSTOM, * LPPHEADER_DEFAULT_CUSTOM;


typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Index;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PHEADER_DEFAULT_ITEM, * LPPHEADER_DEFAULT_ITEM;

typedef struct {
	PBMSG_HEADER  Header;
	BYTE          SubCode;
	BYTE          Index;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PHEADER_DEFAULT_SUBCODE_ITEM, * LPPHEADER_DEFAULT_SUBCODE_ITEM;

//send trade
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          SrcFlag;
	BYTE          SrcIndex;
	BYTE          Item[PACKET_ITEM_LENGTH];
	BYTE          DstFlag;
	BYTE          DstIndex;
} PSEND_TRADE, * LPSEND_TRADE;

///////////////////////////////////////////////////////////////////////////////
// log in
///////////////////////////////////////////////////////////////////////////////

typedef struct {
	WORD         Index;	// ���� ���� �þ�鼭 �ٲ�
	BYTE         Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
	BYTE		 IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
} PRECEIVE_SERVER_LIST, * LPPRECEIVE_SERVER_LIST;

//receive join server
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Result;
	BYTE         NumberH;
	BYTE         NumberL;
	BYTE         Version[SIZE_PROTOCOLVERSION];
} PRECEIVE_JOIN_SERVER, * LPPRECEIVE_JOIN_SERVER;

//request create acoount
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
	
#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD // ��й�ȣ �ڸ��� 10->12�� ���� ����
	BYTE         Password[MAX_PASSWORD_SIZE];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
	BYTE         Password[MAX_ID_SIZE];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 

	BYTE         Name[10];
	BYTE         ResidentNumber[13];
	BYTE         Quiz[30];
	BYTE         Answer[30];
	BYTE         PhoneNumber[20];
	BYTE         Email[50];
} PREQUEST_CREATE_ACCOUNT, * LPPREQUEST_CREATE_ACCOUNT;

//request log in
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
	
#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD  // ��й�ȣ �ڸ��� 10->12�� ���� ����
	BYTE         Password[MAX_PASSWORD_SIZE];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
	BYTE         Password[MAX_ID_SIZE];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
	
	DWORD        Time;
	BYTE         Version[SIZE_PROTOCOLVERSION];
	BYTE         Serial[SIZE_PROTOCOLSERIAL];
} PREQUEST_LOG_IN, * LPPREQUEST_LOG_IN;

//request confirm password
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
} PREQUEST_CONFIRM_PASSWORD, * LPPREQUEST_CONFIRM_PASSWORD;

//receive confirm password
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Result;
	BYTE         Question[30];
} PRECEIVE_CONFIRM_PASSWORD, * LPPRECEIVE_CONFIRM_PASSWORD;

//request confirm password
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         ResidentNumber[13];
	BYTE         Answer[30];
} PREQUEST_CONFIRM_PASSWORD2, * LPPREQUEST_CONFIRM_PASSWORD2;

//receive confirm password
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Result;
	
#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD  // ��й�ȣ �ڸ��� 10->12�� ���� ����
	BYTE         Password[MAX_PASSWORD_SIZE];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
	BYTE         Password[MAX_ID_SIZE];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD 
	
} PRECEIVE_CONFIRM_PASSWORD2, * LPPRECEIVE_CONFIRM_PASSWORD2;

//request change password
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];

#ifdef LDS_MODIFY_CHAR_LENGTH_USERPASSWORD   // ��й�ȣ �ڸ��� 10->12�� ���� ����
	BYTE         OldPassword[MAX_PASSWORD_SIZE];
	BYTE         NewPassword[MAX_PASSWORD_SIZE];
#else // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD
	BYTE         OldPassword[MAX_ID_SIZE];
	BYTE         NewPassword[MAX_ID_SIZE];
#endif // LDS_MODIFY_CHAR_LENGTH_USERPASSWORD

	BYTE         ResidentNumber[13];
} PREQUEST_CHANGE_PASSWORD, * LPPREQUEST_CHANGE_PASSWORD;

//receive characters list
typedef struct {
	BYTE         Index;
	BYTE         ID[MAX_ID_SIZE];
	WORD         Level;
	//BYTE         Level;
	BYTE		 CtlCode;
	BYTE         Class;
	BYTE         Equipment[EQUIPMENT_LENGTH];
#ifdef _PVP_BLOCK_PVP_CHAR
	BYTE		 PvPState;
#endif	// _PVP_BLOCK_PVP_CHAR
    BYTE         byGuildStatus;
} PRECEIVE_CHARACTER_LIST, * LPPRECEIVE_CHARACTER_LIST;

//request create character
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         Class;
} PREQUEST_CREATE_CHARACTER, * LPREQUEST_CREATE_CHARACTER;

//receive create character
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Result;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         Index;
    WORD         Level;
	BYTE		 Class;
	//BYTE         Equipment[24];
} PRECEIVE_CREATE_CHARACTER, * LPPRECEIVE_CREATE_CHARACTER;

//request delete character
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         Resident[10];
} PREQUEST_DELETE_CHARACTER, * LPREQUEST_DELETE_CHARACTER;

//request join map server
typedef struct {
	PBMSG_HEADER Header;
	BYTE		 SubCode;
	BYTE         ID[MAX_ID_SIZE];
} PREQUEST_JOIN_MAP_SERVER, * LPPREQUEST_JOIN_MAP_SERVER;

//receive join map server
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         Map;
	BYTE         Angle;

	BYTE		btMExp1;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMExp2;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMExp3;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMExp4;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMExp5;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMExp6;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMExp7;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMExp8;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 8)


	BYTE		btMNextExp1;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMNextExp2;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMNextExp3;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMNextExp4;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMNextExp5;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMNextExp6;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMNextExp7;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMNextExp8;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 8)

	WORD         LevelUpPoint;
	//BYTE         LevelUpPoint;
	WORD         Strength;
	WORD         Dexterity;
	WORD         Vitality;
	WORD         Energy;
	WORD         Life;
	WORD         LifeMax;
	WORD         Mana;
	WORD         ManaMax;
	WORD		 Shield;
	WORD		 ShieldMax;
	WORD		 SkillMana;
	WORD		 SkillManaMax;
	DWORD        Gold;
	BYTE         PK;
	BYTE		 CtlCode;
    short        AddPoint;
    short        MaxAddPoint;
    WORD         Charisma;  //  ���.
	WORD		 wMinusPoint;		// ���� ���� ����Ʈ
	WORD		 wMaxMinusPoint;	// �ִ� ���� ����Ʈ
} PRECEIVE_JOIN_MAP_SERVER, * LPPRECEIVE_JOIN_MAP_SERVER;

//receive revival
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         Map;
	BYTE         Angle;
	WORD         Life;
	WORD         Mana;
	WORD		 Shield;
	WORD		 SkillMana;
	BYTE		btMExp1;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMExp2;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMExp3;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMExp4;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMExp5;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMExp6;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMExp7;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMExp8;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 8)

	DWORD        Gold;
} PRECEIVE_REVIVAL, * LPPRECEIVE_REVIVAL;

//inventory
typedef struct {
	BYTE          Index;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PRECEIVE_INVENTORY, * LPPRECEIVE_INVENTORY;


///////////////////////////////////////////////////////////////////////////////
// trade
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         ID[MAX_ID_SIZE];
    WORD         Level;
    DWORD        GuildKey;
} PTRADE, * LPPTRADE;


///////////////////////////////////////////////////////////////////////////////
// game
///////////////////////////////////////////////////////////////////////////////

//request chat
typedef struct {
	PBMSG_HEADER Header;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         ChatText[MAX_CHAT_SIZE];
} PCHATING, * LPPCHATING;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         ChatText[MAX_CHAT_SIZE];
} PCHATING_KEY, * LPPCHATING_KEY;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         Result;
	BYTE		 Count;
	WORD		 Delay;
	DWORD		 Color;
	BYTE		 Speed;
	BYTE         Notice[256];
} PRECEIVE_NOTICE, * LPPRECEIVE_NOTICE;

//receive equipment
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         Class;
	BYTE         Equipment[EQUIPMENT_LENGTH];
} PRECEIVE_EQUIPMENT, * LPPRECEIVE_EQUIPMENT;

//receive other map character
typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         Class;
	BYTE         Equipment[EQUIPMENT_LENGTH];
	BYTE         ID[MAX_ID_SIZE];
	BYTE         TargetX;
	BYTE         TargetY;
	BYTE         Path;
	BYTE         s_BuffCount;
	BYTE		 s_BuffEffectState[MAX_BUFF_SLOT_INDEX];
} PCREATE_CHARACTER, * LPPCREATE_CHARACTER;

//receive other map character
typedef struct 
{
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         TypeH;
	BYTE         TypeL;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         TargetX;
	BYTE         TargetY;
	BYTE         Path;
	BYTE         Class;
	BYTE         Equipment[EQUIPMENT_LENGTH];
	BYTE         s_BuffCount;
	BYTE		 s_BuffEffectState[MAX_BUFF_SLOT_INDEX];
} PCREATE_TRANSFORM, * LPPCREATE_TRANSFORM;

//receive other map character
typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         TypeH;
	BYTE         TypeL;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         TargetX;
	BYTE         TargetY;
	BYTE         Path;
	BYTE         ID[MAX_ID_SIZE];
	BYTE         s_BuffCount;
	BYTE		 s_BuffEffectState[MAX_BUFF_SLOT_INDEX];
} PCREATE_SUMMON, * LPPCREATE_SUMMON;

//receive other map character
typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         TypeH;
	BYTE         TypeL;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         TargetX;
	BYTE         TargetY;
	BYTE         Path;
	BYTE         s_BuffCount;
	BYTE		 s_BuffEffectState[MAX_BUFF_SLOT_INDEX];
} PCREATE_MONSTER, * LPPCREATE_MONSTER;

//send move my character
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Path[8];
} PMOVE_MY_CHARACTER, * LPPMOVE_MY_CHARACTER;

//receive move character
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          PositionX;
	BYTE          PositionY;
	//BYTE          Path[8];
	BYTE          Path[1];
} PMOVE_CHARACTER, * LPPMOVE_CHARACTER;

//delete character and item
typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
} PDELETE_CHARACTER, * LPPDELETE_CHARACTER;

//create item
typedef struct {
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PCREATE_ITEM, * LPPCREATE_ITEM;

//request drop item
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          InventoryIndex;
} PREQUEST_DROP_ITEM, * LPPREQUEST_DROP_ITEM;

//request drop item
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          SrcIndex;
	BYTE          DstIndex;
} PREQUEST_EQUIPMENT_ITEM, * LPPREQUEST_EQUIPMENT_ITEM;

//change character
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PCHANGE_CHARACTER, * LPPCHANGE_CHARACTER;

//request attack
#ifdef KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Action;
	BYTE          Dir;
	BYTE          KeyH;
	BYTE          KeyL;
} PREQUEST_ATTACK, * LPPREQUEST_ATTACK;
#else // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          Action;
	BYTE          Dir;
} PREQUEST_ATTACK, * LPPREQUEST_ATTACK;
#endif // KJH_MOD_ATTACK_PROTOCOL_FOR_PROTECT_HACK

//receive get item
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Result;
	BYTE          Item[PACKET_ITEM_LENGTH];
} PRECEIVE_GET_ITEM, * LPPRECEIVE_GET_ITEM;

//receive attack
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          DamageH;
	BYTE          DamageL;
	BYTE		  DamageType;
	BYTE		  ShieldDamageH;
	BYTE		  ShieldDamageL;			
} PRECEIVE_ATTACK, * LPPRECEIVE_ATTACK;

//receive die
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          ExpH;
	BYTE          ExpL;
	BYTE          DamageH;
	BYTE          DamageL;
} PRECEIVE_DIE, * LPPRECEIVE_DIE;
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	WORD          ExpH;
	WORD          ExpL;
	BYTE          DamageH;
	BYTE          DamageL;
} PRECEIVE_DIE2, * LPPRECEIVE_DIE2;

//receive default key
typedef struct {
	PBMSG_HEADER Header;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE		 TKeyH;
	BYTE		 TKeyL;
} PHEADER_DEFAULT_DIE, * LPPHEADER_DEFAULT_DIE;

//request action
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Angle;
	BYTE          Action;
	BYTE		  TargetKeyH;
	BYTE		  TargetKeyL;
} PREQUEST_ACTION, * LPPREQUEST_ACTION;

//receive action
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          Angle;
	BYTE          Action;
	BYTE		  TargetKeyH;
	BYTE		  TargetKeyL;
} PRECEIVE_ACTION, * LPPRECEIVE_ACTION;

//send magic
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE          KeyH;
	BYTE          KeyL;
} PSEND_MAGIC, * LPPSEND_MAGIC;

//send magic continue
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Angle;
} PSEND_MAGIC_CONTINUE, * LPPSEND_MAGIC_CONTINUE;

//receive magic continue
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Angle;
} PRECEIVE_MAGIC_CONTINUE, * LPPRECEIVE_MAGIC_CONTINUE;

//receive magic
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE          SourceKeyH;
	BYTE          SourceKeyL;
	BYTE          TargetKeyH;
	BYTE          TargetKeyL;
} PRECEIVE_MAGIC, * LPPRECEIVE_MAGIC;

//receive MonsterSkill
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	WORD		  SourceKey;
	WORD		  TargetKey;
} PRECEIVE_MONSTERSKILL, * LPPRECEIVE_MONSTERSKILL;

//receive magic target
typedef struct {
	BYTE          KeyH;
	BYTE          KeyL;
} PRECEIVE_MAGIC_POSITION, * LPPRECEIVE_MAGIC_POSITION;

//send magic continue
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          MagicH;
	BYTE          MagicL;
	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Count;
	BYTE          Key[10];
} PSEND_MAGIC_CONTINUES, * LPPSEND_MAGIC_CONTINUES;

//receive magic target
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;

	BYTE          MagicH;
	BYTE          MagicL;

	BYTE          PositionX;
	BYTE          PositionY;
	BYTE          Count;
} PRECEIVE_MAGIC_POSITIONS, * LPPRECEIVE_MAGIC_POSITIONS;

//receive magic list count
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Value;
    BYTE         ListType;  //  ��ų ����Ʈ ����. ( 0:�Ϲ� ��ü ��ų ����Ʈ, 1:�߰����� ��ų ����Ʈ, 2:���� ��ų ����Ʈ ).
} PHEADER_MAGIC_LIST_COUNT, * LPPHEADER_MAGIC_LIST_COUNT;

#pragma pack(push, 1)
//receive magic target
typedef struct {
	BYTE          Index;

	WORD		  Type;
	BYTE          Level;
} PRECEIVE_MAGIC_LIST, * LPPRECEIVE_MAGIC_LIST;
#pragma pack(pop)

//receive skill count.
typedef	struct {
	PBMSG_HEADER  Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE		  m_byType;		//	��ų ��ȣ.
	BYTE		  m_byCount;	//	�ܰ� ī��Ʈ.
} PRECEIVE_EX_SKILL_COUNT, * LPPRECEIVE_EX_SKILL_COUNT;

//receive gold
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Flag;
	DWORD         Gold;
} PRECEIVE_GOLD, * LPPRECEIVE_GOLD;

//receive repair gold
typedef struct {
	PBMSG_HEADER  Header;
	DWORD         Gold;
} PRECEIVE_REPAIR_GOLD, * LPPRECEIVE_REPAIR_GOLD;

//receive level up
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	WORD         Level;
	WORD         LevelUpPoint;
	//BYTE         Level;
	//BYTE         LevelUpPoint;
	WORD         MaxLife;
	WORD         MaxMana;
	WORD		 MaxShield;
	WORD		 SkillManaMax;
    short        AddPoint;
    short        MaxAddPoint;
	WORD		 wMinusPoint;		// ���� ���� ����Ʈ
	WORD		 wMaxMinusPoint;	// �ִ� ���� ����Ʈ
} PRECEIVE_LEVEL_UP, * LPPRECEIVE_LEVEL_UP;

typedef struct {
	PBMSG_HEADER  Header;
	BYTE          Index;
	BYTE		  Life[5];
} PRECEIVE_LIFE, * LPPRECEIVE_LIFE;

//receive add point
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Result;
	WORD         Max;
	WORD		 ShieldMax;
	WORD		 SkillManaMax;
} PRECEIVE_ADD_POINT, * LPPRECEIVE_ADD_POINT;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         PositionX;
	BYTE         PositionY;
} PRECEIVE_MOVE_POSITION, * LPPRECEIVE_MOVE_POSITION;

typedef struct {
	PBMSG_HEADER Header;
	WORD		 Flag;
	BYTE         Map;
	BYTE         PositionX;
	BYTE         PositionY;
	BYTE         Angle;
} PRECEIVE_TELEPORT_POSITION, * LPPRECEIVE_TELEPORT_POSITION;

//receive damage
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         DamageH;
	BYTE         DamageL;
	BYTE		 ShieldDamageH;
	BYTE		 ShieldDamageL;
} PRECEIVE_DAMAGE, * LPPRECEIVE_DAMAGE;

//receive create guild master
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Name[8];
	BYTE         Mark[32];
} PSEND_CREATE_GUILD, * LPPSEND_CREATE_GUILD;

//receive party info
typedef struct {
    BYTE         value;
} PRECEIVE_PARTY_INFO, * LPPRECEIVE_PARTY_INFO;

//receive party infos
typedef struct {
	PBMSG_HEADER Header;
    BYTE         Count;
} PRECEIVE_PARTY_INFOS, * LPPRECEIVE_PARTY_INFOS;

//receive party list
typedef struct {
	BYTE         ID[MAX_ID_SIZE];
	BYTE         Number;
	BYTE         Map;
	BYTE         x;
	BYTE         y;
    int          currHP;
    int          maxHP;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
	char		 PKPartyLevel;
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
} PRECEIVE_PARTY_LIST, * LPPRECEIVE_PARTY_LIST;

//receive party list
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Result;
	BYTE         Count;
} PRECEIVE_PARTY_LISTS, * LPPRECEIVE_PARTY_LISTS;

typedef struct {
    PBMSG_HEADER Header;
    BYTE         KeyH;
    BYTE         KeyL;
	int			 ItemInfo;
	BYTE		 ItemLevel;
}PRECEIVE_GETITEMINFO_FOR_PARTY, * LPPRECEIVE_GETITEMINFO_FOR_PARTY;

//receive pk
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         PK;
} PRECEIVE_PK, * LPPRECEIVE_PK;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         Index;
	WORD         Time;
} PRECEIVE_HELPER_ITEM, * LPPRECEIVE_HELPER_ITEM;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         IP[15];
	WORD         Port;
} PRECEIVE_SERVER_ADDRESS, * LPPRECEIVE_SERVER_ADDRESS;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		 Server;
} PRECEIVE_SERVER_BUSY, * LPPRECEIVE_SERVER_BUSY;

typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         Name[8];
	BYTE         Mark[32];
} PRECEIVE_GUILD, * LPPRECEIVE_GUILD;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         Name[8];
	BYTE         Mark[32];
} PRECEIVE_GUILD_MARK, * LPPRECEIVE_GUILD_MARK;

typedef struct {
	BYTE         KeyH;
	BYTE         KeyL;
	BYTE         GuildKeyH;
	BYTE         GuildKeyL;
} PRECEIVE_GUILD_PLAYER, * LPPRECEIVE_GUILD_PLAYER;

// ���� ���
typedef struct {
	BYTE         ID[MAX_ID_SIZE];
	BYTE         Number;
	BYTE		 CurrentServer;
	BYTE		 GuildStatus;		// �������
} PRECEIVE_GUILD_LIST, * LPPRECEIVE_GUILD_LIST;

// ���� ��� ����Ʈ
typedef struct {
	PWMSG_HEADER Header;
	BYTE         Result;
	BYTE         Count;
	DWORD        TotalScore;
	BYTE         Score;
	char		szRivalGuildName[MAX_GUILDNAME];
} PRECEIVE_GUILD_LISTS, * LPPRECEIVE_GUILD_LISTS;

//send guild leave
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          ID[MAX_ID_SIZE];
	BYTE          ResidentNumber[10];
} PSEND_GUILD_LEAVE, * LPPSEND_GUILD_LEAVE;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         Name[8];
} PSEND_GUILD_WAR, * LPPSEND_GUILD_WAR;

//receive guild war
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Name[8];
	BYTE         Type;
	BYTE         Team;
} PRECEIVE_WAR, * LPPRECEIVE_WAR;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         Score1;
	BYTE         Score2;
	BYTE         Type;
} PRECEIVE_WAR_SCORE, * LPPRECEIVE_WAR_SCORE;

// ����Ʈ�� ��� ID ���
typedef struct
{
	int			 GuildKey;
	BYTE		 GuildStatus;		// ������� -1 : NONE, 0 : PERSON, 32 : BATTLE_MASTER, 64 : SUB_MASTER, 128 : MASTER
	BYTE		 GuildType;			// ������� �Ϲ�(0), ��ȣ���(1)
	BYTE		 GuildRelationShip;	// ������ (0x00 : �������, 0x01 : Union, 0x04 Union Master, 0x02 : Rival, 0x08: Rival Union )
	BYTE		 KeyH;
	BYTE		 KeyL;
#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
	BYTE btCastleOwner;		// ��������峪 �����̸� 1, �ƴϸ� 0
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
} PRECEIVE_GUILD_ID, *LPPRECEIVE_GUILD_ID;

// ��� ���� ��û ���
typedef struct
{
	PBMSG_HEADER Header;
	int			GuildKey;
	BYTE		GuildType;			// ������� �Ϲ�(0), �뺴(1), Ŭ��(2)
	BYTE		UnionName[MAX_GUILDNAME];
	BYTE		GuildName[MAX_GUILDNAME];
	BYTE		Mark[32];
} PPRECEIVE_GUILDINFO, *LPPPRECEIVE_GUILDINFO;

enum GUILD_REQ_COMMON_RESULT
{
	// ��尡 ����
	GUILD_ANS_NOTEXIST_GUILD			= 0x10,
	// ���հ��� ���� (���������趧����)
	GUILD_ANS_UNIONFAIL_BY_CASTLE		= 0x10,
	// ���� ����
	GUILD_ANS_NOTEXIST_PERMISSION		= 0x11,

	// �Ӹ� �� �� �ִ� ����� ����
	GUILD_ANS_NOTEXIST_EXTRA_STATUS		= 0x12,
	// �Ӹ� �� �� �ִ� Ÿ���� ����
	GUILD_ANS_NOTEXIST_EXTRA_TYPE		= 0x13,

	// ���� �� & ��
	GUILD_ANS_EXIST_RELATIONSHIP_UNION	= 0x15,
	GUILD_ANS_EXIST_RELATIONSHIP_RIVAL	= 0x16,

	// ���� �� & ��
	GUILD_ANS_EXIST_UNION				= 0x17,
	GUILD_ANS_EXIST_RIVAL				= 0x18,
	GUILD_ANS_NOTEXIST_UNION			= 0x19,
	GUILD_ANS_NOTEXIST_RIVAL			= 0x1A,

	// ���� �����Ͱ� �ƴ�
	GUILD_ANS_NOT_UNION_MASTER			= 0x1B,

	// ���� ��尡 �ƴ�
	GUILD_ANS_NOT_GUILD_RIVAL			= 0x1C,

	// ���ձ��������ǹ̴� (����20�̻�)
	GUILD_ANS_CANNOT_BE_UNION_MASTER_GUILD = 0x1D,
	
	// �ִ� ��� ���� ���� �ʰ���
	GUILD_ANS_EXCEED_MAX_UNION_MEMBER	= 0x1E,

	// ��û�� ��ҵǾ����ϴ�.
	GUILD_ANS_CANCEL_REQUEST			= 0x20,

#ifdef ASG_ADD_GENS_SYSTEM
	// ���� �渶�� �ս��� ������ �ȵǾ� �ִ�.
	GUILD_ANS_UNION_MASTER_NOT_GENS		= 0xA1,
	// �渶�� �ս��� ������ �ȵǾ� �ִ�.
	GUILD_ANS_GUILD_MASTER_NOT_GENS		= 0xA2,
	// ���� �渶�� �ս��� ���� �ٸ���.
	GUILD_ANS_UNION_MASTER_DISAGREE_GENS = 0xA3,
#endif	// ASG_ADD_GENS_SYSTEM
};

// ������ ���
typedef struct {
	PBMSG_HEADER	Header;
	BYTE			Value;
	BYTE			GuildType;
} PMSG_GUILD_CREATE_RESULT, *LPPMSG_GUILD_CREATE_RESULT;

// ��������� ���� ���
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			byGuildType;				// �Ϲ�(0), �뺴(1), Ŭ��(2)
	BYTE			byResult;					// ����(0x00), ����(0x01), ������(0x10), ���Ѿ���(0x11), �����������(0x13)
} PMSG_GUILD_ASSIGN_TYPE_RESULT, *LPPMSG_GUILD_ASSIGN_TYPE_RESULT;

// ��å�� �Ӹ� / ���� / ���� ���
typedef struct {
	PBMSG_HEADER	Header;
	BYTE			byType;						// �Ӹ�(1), ����(2), ����(3)
	BYTE			byResult;					// ���
	char			szTargetName[MAX_ID_SIZE];	// ��������̸�
} PRECEIVE_GUILD_ASSIGN, *LPPRECEIVE_GUILD_ASSIGN;

// ���ձ�� ����Ʈ ����
typedef struct {
	PWMSG_HEADER	Header;
	BYTE			byCount;
	BYTE			byResult;
	BYTE			byRivalCount;
	BYTE			byUnionCount;
} PMSG_UNIONLIST_COUNT, *LPPMSG_UNIONLIST_COUNT;
// ���ձ�� ����
typedef struct {
	BYTE			byMemberCount;
	BYTE			GuildMark[32];
	char			szGuildName[MAX_GUILDNAME];
} PMSG_UNIONLIST, *LPPMSG_UNIONLIST;

// �����̳� ������ ��û ����
typedef struct {
	PBMSG_HEADER	Header;
	BYTE			byRelationShipType;			// �������� ( 0x01 : Union, 0x02 : Rival )
	BYTE			byRequestType;				// ��û���� ( 0x01 : Join, 0x02 : BreakOff )
	BYTE			byTargetUserIndexH;			// ��ǥ�����ε���H
	BYTE			byTargetUserIndexL;			// ��ǥ�����ε���L
} PMSG_GUILD_RELATIONSHIP, *LPPMSG_GUILD_RELATIONSHIP;

// �����̳� ������ ��û��� ����
typedef struct {
	PBMSG_HEADER	Header;
	BYTE			byRelationShipType;			// �������� ( 0x01 : Union, 0x02 : Rival )
	BYTE			byRequestType;				// ��û���� ( 0x01 : Join, 0x02 : BreakOff )
	BYTE			byResult;					// ��� ( 0x00 : �ź�, 0x01 : ����, 0x10 : ������, 0x11 : ���Ѿ��� )
	BYTE			byTargetUserIndexH;			// ��ǥ�����ε���H
	BYTE			byTargetUserIndexL;			// ��ǥ�����ε���L
} PMSG_GUILD_RELATIONSHIP_RESULT, *LPPMSG_GUILD_RELATIONSHIP_RESULT;

typedef struct {
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE			byResult;
	BYTE			byRequestType;
	BYTE			byRelationShipType;
} PMSG_BAN_UNIONGUILD, *LPPMSG_BAN_UNIONGUILD;

// ����Ʈ���� �������� ��ȭ�� ����
typedef struct {
	PWMSG_HEADER	Header;
	BYTE			byCount;
} PMSG_UNION_VIEWPORT_NOTIFY_COUNT, *LPPMSG_UNION_VIEWPORT_NOTIFY_COUNT;
typedef struct {
	BYTE			byKeyH;
	BYTE			byKeyL;
	int				nGuildKey;
	BYTE			byGuildRelationShip;
	char			szUnionName[MAX_GUILDNAME];
} PMSG_UNION_VIEWPORT_NOTIFY, *LPPMSG_UNION_VIEWPORT_NOTIFY;

//receive gold
typedef struct {
	PBMSG_HEADER Header;
	BYTE         Result;
	DWORD        StorageGold;
	DWORD        Gold;
} PRECEIVE_STORAGE_GOLD, * LPPRECEIVE_STORAGE_GOLD;

//receive soccer time
typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	WORD         Time;
} PRECEIVE_SOCCER_TIME, * LPPRECEIVE_SOCCER_TIME;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE         Name1[8];
	BYTE         Score1;
	BYTE         Name2[8];
	BYTE         Score2;
} PRECEIVE_SOCCER_SCORE, * LPPRECEIVE_SOCCER_SCORE;

#ifdef CSK_FIX_QWER
#pragma pack(push, 1)
#endif // CSK_FIX_QWER
typedef struct {
    PBMSG_HEADER Header;
    BYTE         SubCode;
#ifdef CSK_FIX_SKILLHOTKEY_PACKET
	BYTE         HotKey[20];
#else // CSK_FIX_SKILLHOTKEY_PACKET
	BYTE         HotKey[10];
#endif // CSK_FIX_SKILLHOTKEY_PACKET
    BYTE         GameOption;
    BYTE         KeyQWE[3];
	BYTE		 ChatLogBox;
	BYTE		 KeyR;
	int			 QWERLevel;		// 4����Ʈ
} PRECEIVE_OPTION, * LPPRECEIVE_OPTION;
#ifdef CSK_FIX_QWER
#pragma pack(pop)
#endif // CSK_FIX_QWER

typedef struct {
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		 Cmd1;
	BYTE		 Cmd2;
	BYTE		 Cmd3;
} PRECEIVE_SERVER_COMMAND, * LPPRECEIVE_SERVER_COMMAND;


typedef struct {
	PBMSG_HEADER Header;
	BYTE		 m_MyRank;
	BYTE         m_Count;
	BYTE		 m_byRank;
} PDEVILRANK, * LPPDEVILRANK;

typedef struct {    //  �̺�ƮĨ ������. .
    PBMSG_HEADER Header;
    BYTE        m_byType;       //  ( 0:����, 1:����, 2:���ȭ 2�ֳ� ���� ... )
#ifdef ASG_FIX_LENA_REGISTRATION
	int			m_nChipCount;  //  �̺�ƮĨ ��.
#else	// ASG_FIX_LENA_REGISTRATION
	short       m_shChipCount;  //  �̺�ƮĨ ��.
#endif	// ASG_FIX_LENA_REGISTRATION
    short       m_shMutoNum[3]; //  ���� ��ȣ.
} PRECEIVE_EVENT_CHIP_INFO, * LPPRECEIVE_EVENT_CHIP_INFO;

typedef struct {    //  �̺�ƮĨ��.
    PBMSG_HEADER Header;
    BYTE        m_byType;       //  ( 0:����, 1:����, 2:���ȭ 2�ֳ� ���� ... )
#ifdef ASG_FIX_LENA_REGISTRATION
	unsigned int  m_unChipCount;
#else	// ASG_FIX_LENA_REGISTRATION
    unsigned short  m_shChipCount;
#endif	// ASG_FIX_LENA_REGISTRATION
} PRECEIVE_ENVET_CHIP, * LPPRECEIVE_EVENT_CHIP;

typedef struct {    //  �����ȣ.
    PBMSG_HEADER Header;
    short        m_shMutoNum[3];
} PRECEIVE_MUTONUMBER, * LPPRECEIVE_MUTONUMBER;

#ifdef SCRATCH_TICKET
typedef struct {	//	����.
	PBMSG_HEADER Header;
	BYTE		 m_byIsRegistered;	//	������ ��ϵ� �ִ��� �˻�. ( 0:�̵��, 1:���, 2:���Ƚ�� �ѱ� ).
	char		 m_strGiftName[64];	//	��ǰ�̸�.
} PRECEIVE_SCRATCH_TICKET_EVENT, *LPPRECEIVE_SCRATCH_TICKET_EVENT;
#endif

typedef struct {	//	ȿ���� ���
	PBMSG_HEADER Header;
	WORD		 wEffectNum;	//	ȿ���� ��ȣ
} PRECEIVE_PLAY_SOUND_EFFECT, *LPPRECEIVE_PLAY_SOUND_EFFECT;

typedef struct {
	PBMSG_HEADER Header;
	BYTE         m_byValue;     //  �̺�Ʈ ( 0:��Ȱ��, 1:Ȱ�� ).
    BYTE         m_byNumber;    //  �̺�Ʈ ��ȣ.
} PHEADER_EVENT, * LPPHEADER_EVENT;

typedef struct {
    PBMSG_HEADER    Header;
    BYTE            m_wEventType;       //  �̺�Ʈ ����.
    BYTE            m_wLeftEnterCount;  //  ���� Ƚ��.
}PRECEIVE_EVENT_COUNT, *LPPRECEIVE_EVENT_COUNT;

typedef struct {
    PBMSG_HEADER Header;
    BYTE         m_byCount;
    BYTE         m_byQuest[50];
} PRECEIVE_QUEST_HISTORY, * LPPRECEIVE_QUEST_HISTORY;

typedef struct {
    PBMSG_HEADER Header;
    BYTE         m_byQuestIndex;
    BYTE         m_byState;
} PRECEIVE_QUEST_STATE, * LPPRECEIVE_QUEST_STATE;

typedef struct {
    PBMSG_HEADER Header;
    BYTE         m_byQuestIndex;
    BYTE         m_byResult;
    BYTE         m_byState;
} PRECEIVE_QUEST_RESULT, * LPPRECEIVE_QUEST_RESULT;

typedef struct {
    PBMSG_HEADER Header;
    BYTE         m_byKeyH;
    BYTE         m_byKeyL;
    BYTE         m_byReparation;
    BYTE         m_byNumber;
} PRECEIVE_QUEST_REPARATION, * LPPRECEIVE_QUEST_REPARATION;

#ifdef ASG_ADD_NEW_QUEST_SYSTEM

// GC[0xF6][0x0A]
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	WORD			m_wNPCIndex;
	WORD			m_wQuestCount;
} PMSG_NPCTALK_QUESTLIST, *LPPMSG_NPCTALK_QUESTLIST;

//0xF6, 0x0B ��� ��� ����
//0xF6, 0x0C ����Ʈ ���� ����(����Ʈ ����â���� ���� ��)
//0xF6, 0x1B ����Ʈ ���� ����(���� ���� ����Ʈ ����Ʈ���� ���� ��)
#pragma pack(push, 1)
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	DWORD			m_dwQuestIndex;
	BYTE			m_byRequestCount;
	BYTE			m_byRewardCount;
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	BYTE			m_byRandRewardCount;	// ���� ���� ���� ����(A�� �߿� B�� �� B�� ����)
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
} PMSG_NPC_QUESTEXP_INFO, *LPPMSG_NPC_QUESTEXP_INFO;
#pragma pack(pop)

// �䱸 ����
enum QUEST_REQUEST_TYPE
{
	QUEST_REQUEST_NONE		= 0x0000,
	QUEST_REQUEST_MONSTER	= 0x0001,	// ���� ��ƿͶ�.
	QUEST_REQUEST_SKILL		= 0x0002,	// ��ų ����Ͷ�
	QUEST_REQUEST_ITEM		= 0x0004,	// ������ ���ؿͶ�
	QUEST_REQUEST_LEVEL		= 0x0008,	// ���� �÷��Ͷ�
	QUEST_REQUEST_TUTORIAL	= 0x0010,	// Ʃ�丮��
	QUEST_REQUEST_BUFF		= 0x0020,	// ������ �޾ƶ�.
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	QUEST_REQUEST_EVENT_MAP_USER_KILL		= 0x0040,	// ���� ų ����Ʈ
	QUEST_REQUEST_EVENT_MAP_MON_KILL		= 0x0041,	// ���� ų ����Ʈ
	QUEST_REQUEST_EVENT_MAP_BLOOD_GATE		= 0x0042,	// ���� ĳ�� ���� �ı�
	QUEST_REQUEST_EVENT_MAP_CLEAR_BLOOD		= 0x0100,	// ���� ĳ�� Ŭ����
	QUEST_REQUEST_EVENT_MAP_CLEAR_CHAOS		= 0x0101,	// ī���� ĳ�� Ŭ����
	QUEST_REQUEST_EVENT_MAP_CLEAR_DEVIL		= 0x0102,	// �Ǹ��� ���� Ŭ����
	QUEST_REQUEST_EVENT_MAP_CLEAR_ILLUSION	= 0x0103,	// ȯ�� ��� Ŭ����
	QUEST_REQUEST_EVENT_MAP_DEVIL_POINT		= 0x0104,	// �Ǹ��� ���� ����Ʈ ȹ��
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
#ifdef ASG_ADD_TIME_LIMIT_QUEST
	QUEST_REQUEST_ZEN		= 0x0105,	// ��
	QUEST_REQUEST_PVP_POINT	= 0x0106,	// PVP ����Ʈ
#endif	// ASG_ADD_TIME_LIMIT_QUEST
#ifdef ASG_ADD_QUEST_REQUEST_NPC_SEARCH
	QUEST_REQUEST_NPC_TALK	= 0x0107,	// NPC�� ã�ƶ�.
#endif	// ASG_ADD_QUEST_REQUEST_NPC_SEARCH

	QUEST_REQUEST_TYPE_MAX
};

#pragma pack(push, 1)
typedef struct 
{	
	DWORD	m_dwType;
	WORD	m_wIndex;
	DWORD	m_dwValue;
#ifdef ASG_ADD_TIME_LIMIT_QUEST
	DWORD	m_dwCurValue;
#else	// ASG_ADD_TIME_LIMIT_QUEST
	WORD	m_wCurValue;
#endif	// ASG_ADD_TIME_LIMIT_QUEST
	BYTE	m_byItemInfo[PACKET_ITEM_LENGTH];
} NPC_QUESTEXP_REQUEST_INFO, *LPNPC_QUESTEXP_REQUEST_INFO;
#pragma pack(pop)

// ����
enum QUEST_REWARD_TYPE
{
	QUEST_REWARD_NONE		= 0x0000,
	QUEST_REWARD_EXP		= 0x0001,	// ����ġ �ش�.
	QUEST_REWARD_ZEN		= 0x0002,	// �� �ش�.
	QUEST_REWARD_ITEM		= 0x0004,	// ������ �ش�.
	QUEST_REWARD_BUFF		= 0x0008,	// ���� �ش�.
#ifdef ASG_ADD_GENS_SYSTEM
	QUEST_REWARD_CONTRIBUTE	= 0x0010,	// �⿩���� �ش�.
#endif	// ASG_ADD_GENS_SYSTEM
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	QUEST_REWARD_RANDOM		= 0x0020,	// ��������
#endif //ASG_ADD_QUEST_REQUEST_REWARD_TYPE

	QUEST_REWARD_TYPE_MAX
};

#pragma pack(push, 1)
typedef struct 
{	
	DWORD	m_dwType;
	WORD	m_wIndex;
	DWORD	m_dwValue;
	BYTE	m_byItemInfo[PACKET_ITEM_LENGTH];
} NPC_QUESTEXP_REWARD_INFO, *LPNPC_QUESTEXP_REWARD_INFO;
#pragma pack(pop)

// �䱸 ����, ���� ����
typedef struct 
{	
	NPC_QUESTEXP_REQUEST_INFO	NpcQuestRequestInfo[5];
	NPC_QUESTEXP_REWARD_INFO	NpcQuestRewardInfo[5];
} NPC_QUESTEXP_INFO, *LPNPC_QUESTEXP_INFO;

//----------------------------------------------------------------------------
// GC[0xF6][0x0D] ����Ʈ �Ϸ� ���
//----------------------------------------------------------------------------
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	DWORD			m_dwQuestIndex;
	BYTE			m_byResult;	// 1 : ���� ���� ����, 2 : ���� �ִ�ġ�� �Ѿ���. 3 : �κ��� ������ �� �ڸ� ����.
} PMSG_ANS_QUESTEXP_COMPLETE, *LPPMSG_ANS_QUESTEXP_COMPLETE;

//----------------------------------------------------------------------------
// GC[0xF6][0x0F] ����Ʈ ����
//----------------------------------------------------------------------------
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;
	
	DWORD			m_dwQuestGiveUpIndex;
} PMSG_ANS_QUESTEXP_GIVEUP, *LPPMSG_ANS_QUESTEXP_GIVEUP;

//----------------------------------------------------------------------------
// GC[0xF6][0x1A] �������� ����Ʈ ����Ʈ ����
//----------------------------------------------------------------------------
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	BYTE			m_byQuestCount;
} PMSG_ANS_QUESTEXP_PROGRESS_LIST, *LPPMSG_ANS_QUESTEXP_PROGRESS_LIST;

#endif	// ASG_ADD_NEW_QUEST_SYSTEM

#ifdef ASG_ADD_TIME_LIMIT_QUEST

const enum QUESTEXP_RESULT
{
	QUEST_RESULT_TIME_LIMIT	= 0x00,		// �ð� ����
	QUEST_RESULT_CNT_LIMIT	= 0x01,		// ����Ʈ ���� ����.
		
	QUEST_RESULT_MAX
};

//----------------------------------------------------------------------------
// CG[0xF6][0x00] ����Ʈ ���� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	BYTE			m_byResult;			// enum QUESTEXP_RESULT ��
} PMSG_ANS_QUESTEXP_RESULT, *LPPMSG_ANS_QUESTEXP_RESULT;
#endif	// ASG_ADD_TIME_LIMIT_QUEST

#ifdef ASG_ADD_GENS_SYSTEM
//----------------------------------------------------------------------------
// GC[0xF8][0x02] �ս� ���� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			SubCode;

	BYTE			m_byResult;				// ���� ��û ���.
	BYTE			m_byInfluence;			// �ս� �Ҽ�.
} PMSG_ANS_REG_GENS_MEMBER, *LPPMSG_ANS_REG_GENS_MEMBER;

//----------------------------------------------------------------------------
// GC[0xF8][0x04] �ս� Ż�� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			SubCode;
	
	BYTE			m_byResult;				// Ż�� ��û ���.
	
} PMSG_ANS_SECEDE_GENS_MEMBER, *LPPMSG_ANS_SECEDE_GENS_MEMBER;

//----------------------------------------------------------------------------
// GC[0xF8][0x07] �ս� ���� ���� ����.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			SubCode;
	
	BYTE			m_byInfluence;			// �ս� �Ҽ�.
#ifdef PBG_ADD_GENSRANKING
	int				m_nRanking;				// ���� ��ŷ
	int				m_nGensClass;			// �ս� ���
	int				m_nContributionPoint;	// �⿩������
	int				m_nNextContributionPoint;	// ���� ��� �⿩������
#endif //PBG_ADD_GENSRANKING
} PMSG_MSG_SEND_GENS_INFO, *LPPMSG_MSG_SEND_GENS_INFO;

//----------------------------------------------------------------------------
// GC[0xF8][0x05] ����Ʈ ���� �ٸ� �÷��̾��� �ս� ���� ���� ����
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEADER    Header;
	BYTE			SubCode;

	BYTE			m_byCount;	
} PMSG_SEND_GENS_MEMBER_VIEWPORT, *LPPMSG_SEND_GENS_MEMBER_VIEWPORT;

typedef struct
{
	BYTE			m_byInfluence;			// �ս� �Ҽ�.
	BYTE			m_byNumberH;
	BYTE			m_byNumberL;
#ifdef PBG_ADD_GENSRANKING
	int				m_nRanking;				// ���� ��ŷ	//Ŭ�� ���� ������
	int				m_nGensClass;			// �ս� ���
	int				m_nContributionPoint;	// �⿩������	//Ŭ�� ���� ������
#endif //PBG_ADD_GENSRANKING
} PMSG_GENS_MEMBER_VIEWPORT_INFO, *LPPMSG_GENS_MEMBER_VIEWPORT_INFO;
#endif	// ASG_ADD_GENS_SYSTEM

#ifdef PBG_ADD_GENSRANKING
//----------------------------------------------------------------------------
// GC[0xF8][0x08] �ս� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	Header;
	BYTE			SubCode;
	BYTE			m_byRewardResult;				// �����û���
}PMSG_GENS_REWARD_CODE, *LPPMSG_GENS_REWARD_CODE;
#endif //PBG_ADD_GENSRANKING

#ifdef ASG_ADD_UI_NPC_DIALOGUE
//----------------------------------------------------------------------------
// GC[0xF9][0x01] NPC UI�� ��ȭ�� ����Ǵ� NPC Ŭ�� �� ����
//----------------------------------------------------------------------------
typedef struct 
{	
	PBMSG_HEADER	Header;
	BYTE			SubCode;
	
	WORD			m_wNPCIndex;
	DWORD			m_dwContributePoint;	//�⿩�� ����Ʈ
} PMSG_ANS_NPC_CLICK, *LPPMSG_ANS_NPC_CLICK;
#endif	// ASG_ADD_UI_NPC_DIALOGUE

//  �� �Ӽ� ��ġ.
typedef struct {
    BYTE        m_byX;
    BYTE        m_byY;
}PRECEIVE_MAP_ATTRIBUTE, *LPPRECEIVE_MAP_ATTRIBUTE;

//  �� �Ӽ� ���� ����.
typedef struct {
    PBMSG_HEADER    Header;
    BYTE            m_byType;
    BYTE            m_byMapAttr;
    BYTE            m_byMapSetType;
    BYTE            m_byCount;

    PRECEIVE_MAP_ATTRIBUTE  m_vAttribute[128*128];
}PRECEIVE_SET_MAPATTRIBUTE, *LPPRECEIVE_SET_MAPATTRIBUTE;

//  ���� ���� ����. ( ���� ĳ�� )
typedef struct  {
    PBMSG_HEADER    Header;
    BYTE            m_byPlayState;      //  ��� ���� (���� ĳ��--> 0:������, 1:�������, 2:������� )
    WORD            m_wRemainSec;       //  ���� �ð� ( �� )
    WORD            m_wMaxKillMonster;  //  ��ǥ ���ͷ�.
    WORD            m_wCurKillMonster;  //  ��ɵ� ���ͷ�.
    WORD            m_wIndex;           //  ���� �������� ��� ĳ���� �ε���
    BYTE            m_byItemType;       //  ���� ������ Ÿ��.
}PRECEIVE_MATCH_GAME_STATE, *LPPRECEIVE_MATCH_GAME_STATE;


#ifdef YDG_ADD_NEW_DUEL_PROTOCOL
// ������û�� ����� ��û ��� (1)
typedef struct		// SC4
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nResult;
	BYTE		bIndexH;				// ���� ������� �ε��� (���� ����Ʈ)
	BYTE		bIndexL;				// ���� ������� �ε��� (���� ����Ʈ)
	CHAR		szID[MAX_ID_SIZE];	// ���� �ɸ��̸�
} PMSG_ANS_DUEL_INVITE, *LPPMSG_ANS_DUEL_INVITE;

// ������û���� �������� ���� ��û (2)
typedef struct _tagPMSG_REQ_DUEL_ANSWER		// SC2
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		bIndexH;				// ���� ������� �ε��� (���� ����Ʈ)
	BYTE		bIndexL;				// ���� ������� �ε��� (���� ����Ʈ)
	CHAR		szID[MAX_ID_SIZE];	// ���� �ɸ��̸�
} PMSG_REQ_DUEL_ANSWER, *LPPMSG_REQ_DUEL_ANSWER;

// �������� (3)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nResult;
	BYTE		bIndexH;		// ���� ������� �ε��� (���� ����Ʈ)
	BYTE		bIndexL;		// ���� ������� �ε��� (���� ����Ʈ)
	CHAR		szID[MAX_ID_SIZE];	// �ɸ��̸�
} PMSG_ANS_DUEL_EXIT, *LPPMSG_ANS_DUEL_EXIT;

// ������ ���� ���� (4)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		bIndexH1;		// ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexL1;		// ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexH2;		// ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE		bIndexL2;		// ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE		btDuelScore1;		// �������� - 1��
	BYTE		btDuelScore2;		// �������� - 2��
} PMSG_DUEL_SCORE_BROADCAST, *LPPMSG_DUEL_SCORE_BROADCAST;

// ������ ���� ���� (5)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		bIndexH1;		// ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexL1;		// ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexH2;		// ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE		bIndexL2;		// ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE		btHP1;			// ���� - 1��(%)
	BYTE		btHP2;			// ���� - 2��(%)
	BYTE		btShield1;		// ���� - 1��(%)
	BYTE		btShield2;		// ���� - 2��(%)
} PMSG_DUEL_HP_BROADCAST, *LPPMSG_DUEL_HP_BROADCAST;

// ���� ä��(����) ����Ʈ (6)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	struct {
		CHAR	szID1[MAX_ID_SIZE];	// �ɸ��̸�
		CHAR	szID2[MAX_ID_SIZE];	// �ɸ��̸�
		BYTE	bStart;			// PK ���� ��/��
		BYTE	bWatch;			// �������� ��/��
	} channel[4];
} PMSG_ANS_DUEL_CHANNELLIST, *LPPMSG_ANS_DUEL_CHANNELLIST;

// ä��(����) ��û (7)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nResult;
	BYTE		nChannelId;				// ä�� ���̵�
	CHAR		szID1[MAX_ID_SIZE];	// �ɸ��̸�
	CHAR		szID2[MAX_ID_SIZE];	// �ɸ��̸�
	BYTE		bIndexH1;		// ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexL1;		// ������� �ε��� (���� ����Ʈ) - 1��
	BYTE		bIndexH2;		// ������� �ε��� (���� ����Ʈ) - 2��
	BYTE		bIndexL2;		// ������� �ε��� (���� ����Ʈ) - 2��
} PMSG_ANS_DUEL_JOINCNANNEL, *LPPMSG_ANS_DUEL_JOINCNANNEL;

// ä��(����) ������ ������ (8)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	CHAR		szID[MAX_ID_SIZE];	// �ɸ��̸�
} PMSG_DUEL_JOINCNANNEL_BROADCAST, *LPPMSG_DUEL_JOINCNANNEL_BROADCAST;

// ä��(����) ���� (9)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nResult;
} PMSG_ANS_DUEL_LEAVECNANNEL, *LPPMSG_ANS_DUEL_LEAVECNANNEL;

// ä��(����) ���� ������ (10)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	CHAR		szID[MAX_ID_SIZE];	// �ɸ��̸�
} PMSG_DUEL_LEAVECNANNEL_BROADCAST, *LPPMSG_DUEL_LEAVECNANNEL_BROADCAST;

// ������ ����Ʈ(All) (11)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nCount;
	struct {
		CHAR	szID[MAX_ID_SIZE];	// �ɸ��̸�
	} user[10];
} PMSG_DUEL_OBSERVERLIST_BROADCAST, *LPPMSG_DUEL_OBSERVERLIST_BROADCAST;

// ������� ���� (12)
typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	CHAR		szWinner[MAX_ID_SIZE];	// ���� �ɸ��̸�
	CHAR		szLoser[MAX_ID_SIZE];	// ���� �ɸ��̸�
} PMSG_DUEL_RESULT_BROADCAST, *LPPMSG_DUEL_RESULT_BROADCAST;

typedef struct
{
	PBMSG_HEADER Header;
	BYTE         SubCode;
	BYTE		nFlag;					// 0: ���� ����, 1: ���� ����
} PMSG_DUEL_ROUNDSTART_BROADCAST, *LPPMSG_DUEL_ROUNDSTART_BROADCAST;

#else	// YDG_ADD_NEW_DUEL_PROTOCOL
#ifdef DUEL_SYSTEM

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			bStart;
	BYTE			bIndexH;
	BYTE			bIndexL;
	BYTE			ID[MAX_ID_SIZE];
}PRECEIVE_DUELSTART, *LPPRECEIVE_DUELSTART;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			bIndexH;
	BYTE			bIndexL;
	BYTE			ID[MAX_ID_SIZE];
}PRECEIVE_DUELEND, *LPPRECEIVE_DUELEND;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			bIndexH;
	BYTE			bIndexL;
	BYTE			ID[MAX_ID_SIZE];
}PNOTIFY_DUELSTART, *LPPNOTIFY_DUELSTART;

typedef struct
{
	PBMSG_HEADER	h;
	BYTE			NumberH1;		// ���� ���̾��� ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE			NumberL1;		// ���� ���̾��� ���� ������� �ε��� (���� ����Ʈ) - 1��
	BYTE			NumberH2;		// ���� ���̾��� ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE			NumberL2;		// ���� ���̾��� ���� ������� �ε��� (���� ����Ʈ) - 2��
	BYTE			btDuelScore1;	// �������� - 1��
	BYTE			btDuelScore2;	// �������� - 1��
}PNOTIFY_DUELSCORE, *LPPNOTIFY_DUELSCORE;

#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_PROTOCOL

typedef struct tagPSHOPTITLE_HEADER {
	PWMSG_HEADER    Header;
	BYTE			bySubcode;
	BYTE			byCount;
} PSHOPTITLE_HEADERINFO, *LPPSHOPTITLE_HEADERINFO;
typedef struct tagPSHOPTITLE_DATA {
	BYTE	byIndexH;
	BYTE	byIndexL;
	BYTE	szTitle[36];	//. MAX_SHOPTITLE
} PSHOPTITLE_DATAINFO, *LPPSHOPTITLE_DATAINFO;
typedef struct tagPSHOPTITLE_CHANGE {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byIndexH;
	BYTE			byIndexL;
	BYTE			szTitle[36];	//. MAX_SHOPTITLE
	BYTE			szId[MAX_ID_SIZE];
} PSHOPTITLE_CHANGEINFO, *LPPSHOPTITLE_CHANGEINFO;

typedef struct tagPSHOPSETPRICE_RESULT {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byResult;
	BYTE			byItemPos;
} PSHOPSETPRICE_RESULTINFO, *LPPSHOPSETPRICE_RESULTINFO;

typedef struct tagCREATEPSHOP_RESULT {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byResult;
} CREATEPSHOP_RESULTINFO, *LPCREATEPSHOP_RESULSTINFO;
typedef struct tagDESTROYPSHOP_RESULT {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byResult;
	BYTE			byIndexH;
	BYTE			byIndexL;
} DESTROYPSHOP_RESULTINFO, *LPDESTROYPSHOP_RESULTINFO;

typedef struct tagGETPSHOPITEMLIST_HEADER {
	PWMSG_HEADER    Header;
	BYTE			bySubcode;
	BYTE			byResult;
	BYTE			byIndexH;
	BYTE			byIndexL;
	BYTE			szId[MAX_ID_SIZE];
	BYTE			szShopTitle[36];	//. MAX_SHOPTITLE
	BYTE			byCount;
} GETPSHOPITEMLIST_HEADERINFO, *LPGETPSHOPITEMLIST_HEADERINFO;
typedef struct tagGETPSHOPITEM_DATA {
	BYTE	byPos;
	BYTE	byItemInfo[PACKET_ITEM_LENGTH];
	INT		iItemPrice;
} GETPSHOPITEM_DATAINFO, *LPGETPSHOPITEM_DATAINFO;
typedef struct tagCLOSEPSHOP_RESULT {
	PWMSG_HEADER    Header;
	BYTE			bySubcode;
	BYTE			byIndexH;
	BYTE			byIndexL;
} CLOSEPSHOP_RESULTINFO, *LPCLOSEPSHOP_RESULTINFO;

typedef struct tagPURCHASEITEM_RESULT {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byResult;
	BYTE			byIndexH;
	BYTE			byIndexL;
	BYTE			byItemInfo[PACKET_ITEM_LENGTH];
	BYTE			byPos;
} PURCHASEITEM_RESULTINFO, *LPPURCHASEITEM_RESULTINFO;
typedef struct tagSOLDITEM_RESULT {
	PBMSG_HEADER	Header;
	BYTE			bySubcode;
	BYTE			byPos;
	BYTE			szId[MAX_ID_SIZE];
} SOLDITEM_RESULTINFO, *LPSOLDITEM_RESULTINFO;

typedef struct tagDISPLAYEFFECT_NOTIFY {
	PBMSG_HEADER	Header;
	BYTE			byIndexH;
	BYTE			byIndexL;
	BYTE			byType;			// ���� ����(ȿ��Ÿ��)
} DISPLAYEREFFECT_NOTIFYINFO, *LPDISPLAYEREFFECT_NOTIFYINFO;

typedef struct {
	PWMSG_HEADER    Header;
	BYTE			MemoCount;
	BYTE			MaxMemo;
	BYTE			Count;
} FS_FRIEND_LIST_HEADER, * LPFS_FRIEND_LIST_HEADER;

typedef struct {
	BYTE			Name[MAX_ID_SIZE];
	BYTE			Server;
} FS_FRIEND_LIST_DATA, * LPFS_FRIEND_LIST_DATA;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Result;
	BYTE			Name[MAX_ID_SIZE];
	BYTE			Server;
} FS_FRIEND_RESULT, * LPFS_FRIEND_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Name[MAX_ID_SIZE];
} FS_ACCEPT_ADD_FRIEND_RESULT, * LPFS_ACCEPT_ADD_FRIEND_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Name[MAX_ID_SIZE];
	BYTE			Server;
} FS_FRIEND_STATE_CHANGE, * LPFS_FRIEND_STATE_CHANGE;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Result;
	DWORD			WindowGuid;
} FS_SEND_LETTER_RESULT, * LPFS_SEND_LETTER_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	WORD			Index;
	BYTE			Name[MAX_ID_SIZE];
	BYTE			Date[30];
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	BYTE			Subject[MAX_LETTER_TITLE_LENGTH];
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	BYTE			Subject[32];
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	BYTE			Read;
} FS_LETTER_ALERT, * LPFS_LETTER_ALERT;

typedef struct {
	PWMSG_HEADER    Header;
	WORD			Index;
	WORD			MemoSize;
	BYTE			Class;
	BYTE			Equipment[EQUIPMENT_LENGTH];
	BYTE			PhotoDir;
	BYTE			PhotoAction;
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	BYTE			Memo[MAX_LETTERTEXT_LENGTH];
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	BYTE			Memo[1000];
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
} FS_LETTER_TEXT, * LPFS_LETTER_TEXT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Result;
	WORD			Index;
} FS_LETTER_RESULT, * LPFS_LETTER_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			IP[15];
	WORD			RoomNumber;
	DWORD			Ticket;
	BYTE			Type;
	BYTE			ID[10];
	BYTE			Result;
} FS_CHAT_CREATE_RESULT, * LPFS_CHAT_CREATE_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Result;
} FS_CHAT_JOIN_RESULT, * LPFS_CHAT_JOIN_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Type;
	BYTE			Index;
	BYTE			Name[MAX_ID_SIZE];
} FS_CHAT_CHANGE_STATE, * LPFS_CHAT_CHANGE_STATE;

typedef struct {
	PWMSG_HEADER    Header;
	WORD			RoomNumber;
	BYTE			Count;
} FS_CHAT_USERLIST_HEADER, * LPFS_CHAT_USERLIST_HEADER;

typedef struct {
	BYTE			Index;
	BYTE			Name[MAX_ID_SIZE];
} FS_CHAT_USERLIST_DATA, * LPFS_CHAT_USERLIST_DATA;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Result;
	DWORD			WindowGuid;
} FS_CHAT_INVITE_RESULT, * LPFS_CHAT_INVITE_RESULT;

typedef struct {
	PBMSG_HEADER    Header;
	BYTE			Index;
	BYTE			MsgSize;
	BYTE			Msg[100];
} FS_CHAT_TEXT, * LPFS_CHAT_TEXT;

//----------------------------------------------------------------------------
// GC [0x2D] ������ ȿ�� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	h;

	WORD		wOptionType;		// ������ �ɼ� ī�װ� (������ �ɼ��� ����)
	WORD		wEffectType;		// ������ �ɼ� ȿ�� �ε��� (wOptionType�� ����)
	BYTE		byEffectOption;		// ȿ�� �ɼ� (0 : ���, 1 : ��� �ð� ����, 2 : ���)
	int			wEffectTime;
	BYTE		byBuffType;
} PMSG_ITEMEFFECTCANCEL, *LPPMSG_ITEMEFFECTCANCEL;

//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
#ifdef PET_SYSTEM

typedef struct
{
    PBMSG_HEADER    m_Header;
    BYTE            m_byPetType;    //  Pet Type ( 0:��ũ���Ǹ�. ... )
    BYTE            m_byCommand;    //  ���. ( 0:�Ϲ�(���), 1:���� ����, 2:���ΰ� ���� ����, 3:Ÿ�ϰ���.
    BYTE            m_byKeyH;       //  ��� Key.
    BYTE            m_byKeyL;
}PRECEIVE_PET_COMMAND, *LPPRECEIVE_PET_COMMAND;


typedef struct 
{
    PBMSG_HEADER    m_Header;
    BYTE            m_byPetType;    //  Pet Type ( 0:��ũ���Ǹ�. ... )
    BYTE            m_bySkillType;  //  ���� Ÿ��. ( 0:�⺻, etc:��ų ).
    BYTE            m_byKeyH;       //  ��� Key;
    BYTE            m_byKeyL;
    BYTE            m_byTKeyH;      //  Ÿ�� Key;
    BYTE            m_byTKeyL;
}PRECEIVE_PET_ATTACK, *LPPRECEIVE_PET_ATTACK;


typedef struct 
{
    PBMSG_HEADER    m_Header;
    BYTE            m_byPetType;    //  �־����� Ÿ�� ( 0:��ũ���Ǹ�. etc ).
    BYTE            m_byInvType;    //  �κ� ���� ( 0:�κ��丮, 1:â��, 2:�ŷ�â... )
    BYTE            m_byPos;        //  ��ġ.
    BYTE            m_byLevel;      //  ������ ����.
    int             m_iExp;         //  ����ġ.
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	BYTE			m_byLife;		//	�����
#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
}PRECEIVE_PET_INFO, *LPPRECEIVE_PET_INFO;

#endif// PET_SYSTEM


//////////////////////////////////////////////////////////////////////////
//	
// From 10. 11 , �ȼ���
//
//////////////////////////////////////////////////////////////////////////

//Type�� 0: ��Ʋ��Ŀ, 1:�����, 2:����
typedef struct
{
	PBMSG_HEADER    m_Header;
	BYTE			m_subCode;
	BYTE			m_Type;	
	WORD			m_Time;		// ���ð� : ����(��)- ���۰��� 1���� ����
}PMSG_MATCH_TIMEVIEW, *LPPMSG_MATCH_TIMEVIEW;

typedef struct
{
	PBMSG_HEADER	m_Header;
	BYTE			m_subCode;
	BYTE			m_Type;

	char			m_MatchTeamName1[MAX_ID_SIZE];	//������ ��츸 ĳ�����̸�
	WORD			m_Score1;

	char			m_MatchTeamName2[MAX_ID_SIZE];
	WORD			m_Score2;
	void			Clear()
	{ 
		memset(&m_MatchTeamName1, NULL, MAX_ID_SIZE); 
		memset(&m_MatchTeamName2, NULL, MAX_ID_SIZE);
		m_Score1 = 0;
		m_Score2 = 0;
		m_Type = 0;
	}
}PMSG_MATCH_RESULT, *LPPMSG_MATCH_RESULT;

typedef struct 
{
	PBMSG_HEADER	m_Header;
	BYTE			m_subCode;
	BYTE			m_x;
	BYTE			m_y;
}PMSG_SOCCER_GOALIN, *LPPMSG_SOCCER_GOALIN;

extern PMSG_MATCH_RESULT		g_wtMatchResult;
extern PMSG_MATCH_TIMEVIEW		g_wtMatchTimeLeft;
extern int g_iGoalEffect;

//////////////////////////////////////////////////////////////////////////

typedef struct      //  �ʼ��� �̵��� ���� ���� ����.
{
    PBMSG_HEADER    m_Header;
    MServerInfo     m_vSvrInfo;
}PHEADER_MAP_CHANGESERVER_INFO, *LPPHEADER_MAP_CHANGESERVER_INFO;


enum CASTLESIEGE_STATE
{
	CASTLESIEGE_STATE_NONE					= -1,		// ���¾���
	CASTLESIEGE_STATE_IDLE_1				= 0,		// ���ޱⰣ - 1
	CASTLESIEGE_STATE_REGSIEGE				= 1,		// ��û�Ⱓ (�����ֱ� ����)
	CASTLESIEGE_STATE_IDLE_2				= 2,		// ���ޱⰣ - 1
	CASTLESIEGE_STATE_REGMARK				= 3,		// ���� ��ϱⰣ
	CASTLESIEGE_STATE_IDLE_3				= 4,		// ���ޱⰣ - 2
	CASTLESIEGE_STATE_NOTIFY				= 5,		// ��ǥ�Ⱓ
	CASTLESIEGE_STATE_READYSIEGE			= 6,		// �غ�Ⱓ
	CASTLESIEGE_STATE_STARTSIEGE			= 7,		// ��������
	CASTLESIEGE_STATE_ENDSIEGE				= 8,		// �����Ⱓ
	CASTLESIEGE_STATE_ENDCYCLE				= 9,		// �����ֱ� ����
};

//----------------------------------------------------------------------------
// GC [0xB2][0x00] Ŭ���̾�Ʈ�� ������ ���������� ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����ξ���/3:������������/4:����������) -> �����̸� ��������� Ȯ���� ����
	CHAR		cCastleSiegeState;			// ���� ������ ����
	BYTE		btStartYearH;				// ���� ���� - �� (���� ����Ʈ)
	BYTE		btStartYearL;				// ���� ���� - �� (���� ����Ʈ)
	BYTE		btStartMonth;				// ���� ���� - ��
	BYTE		btStartDay;					// ���� ���� - ��
	BYTE		btStartHour;				// ���� ���� - ��
	BYTE		btStartMinute;				// ���� ���� - ��
	BYTE		btEndYearH;					// ���� ���� - �� (���� ����Ʈ)
	BYTE		btEndYearL;					// ���� ���� - �� (���� ����Ʈ)
	BYTE		btEndMonth;					// ���� ���� - ��
	BYTE		btEndDay;					// ���� ���� - ��
	BYTE		btEndHour;					// ���� ���� - ��
	BYTE		btEndMinute;				// ���� ���� - ��
	BYTE		btSiegeStartYearH;			// ������ ���� - �� (���� ����Ʈ)
	BYTE		btSiegeStartYearL;			// ������ ���� - �� (���� ����Ʈ)
	BYTE		btSiegeStartMonth;			// ������ ���� - ��
	BYTE		btSiegeStartDay;			// ������ ���� - ��
	BYTE		btSiegeStartHour;			// ������ ���� - ��
	BYTE		btSiegeStartMinute;			// ������ ���� - ��
	CHAR		cOwnerGuild[8];				// ������ ���
	CHAR		cOwnerGuildMaster[10];		// ������ ��� ������

	CHAR		btStateLeftSec1;			// ���� ���±��� ���� �ð� - ���� 1��°
	CHAR		btStateLeftSec2;			// ���� ���±��� ���� �ð� - ���� 2��°
	CHAR		btStateLeftSec3;			// ���� ���±��� ���� �ð� - ���� 3��°
	CHAR		btStateLeftSec4;			// ���� ���±��� ���� �ð� - ���� 4��°
} PMSG_ANS_CASTLESIEGESTATE, *LPPMSG_ANS_CASTLESIEGESTATE;

//----------------------------------------------------------------------------
// GC [0xB2][0x01] ������ ����� ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�̵̹�ϵ�/3:���������/4:������/5:�渶��������/6:��忡����������/7:�ð���������/8:����������)
	CHAR		szGuildName[8];				// ����̸�
} PMSG_ANS_REGCASTLESIEGE, *LPPMSG_ANS_REGCASTLESIEGE;

//----------------------------------------------------------------------------
// GC [0xB2][0x02] ������ ���⸦ ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:��ϵȱ��ƴ�/3:�ð���������)
	BYTE		btIsGiveUp;					// ���⿩�� (0:�������/1:����)
	CHAR		szGuildName[8];				// ����̸�
} PMSG_ANS_GIVEUPCASTLESIEGE, *LPPMSG_ANS_GIVEUPCASTLESIEGE;

//----------------------------------------------------------------------------
// GC [0xB2][0x03] �ڽ��� ����� ������Ͽ� ���� ������ ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:��ϵȱ��ƴ�)
	CHAR		szGuildName[8];				// ����̸�
	BYTE		btGuildMark1;				// ������ ǥ�� - DWORD�� �ֻ��� ����Ʈ ���� 4�ܰ�� ����
	BYTE		btGuildMark2;
	BYTE		btGuildMark3;
	BYTE		btGuildMark4;
	BYTE		btIsGiveUp;					// ���⿩��
	BYTE		btRegRank;					// ��ϼ���
} PMSG_ANS_GUILDREGINFO, *LPPMSG_ANS_GUILDREGINFO;

//----------------------------------------------------------------------------
// GC [0xB2][0x04] �ڽ��� ����� ������ ǥ�� ��� ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:��ϵȱ��ƴ�/3:�߸��Ⱦ����۵��)
	CHAR		szGuildName[8];				// ����̸�
	BYTE		btGuildMark1;				// ������ ǥ�� - DWORD�� �ֻ��� ����Ʈ ���� 4�ܰ�� ����
	BYTE		btGuildMark2;
	BYTE		btGuildMark3;
	BYTE		btGuildMark4;
} PMSG_ANS_REGGUILDMARK, *LPPMSG_ANS_REGGUILDMARK;

//----------------------------------------------------------------------------
// GC [0xB2][0x05] ������ NPC ���� ��û ���� -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���/3:���̸��ڶ�/4:�̹�����)
	INT			iNpcNumber;					// NPC��ȣ
	INT			iNpcIndex;					// NPC�ε���
} PMSG_ANS_NPCBUY, *LPPMSG_ANS_NPCBUY;

//----------------------------------------------------------------------------
// GC [0xB2][0x06] ������ NPC ���� ��û ���� -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���/3:���̸��ڶ�)
	INT			iNpcNumber;					// NPC��ȣ
	INT			iNpcIndex;					// NPC�ε���
	INT			iNpcHP;						// ü��
	INT			iNpcMaxHP;					// �ִ�ü��
} PMSG_ANS_NPCREPAIR, *LPPMSG_ANS_NPCREPAIR;

//----------------------------------------------------------------------------
// GC [0xB2][0x07] ������ NPC ���׷��̵� ��û ���� -> ����üũ, �������� ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���/3:���̸��ڶ�/4:�����̸��ڶ�/5:Ÿ�����߸���/6:��û�����߸���/7:NPC��������������)
	INT			iNpcNumber;					// NPC��ȣ
	INT			iNpcIndex;					// NPC�ε���
	INT			iNpcUpType;					// ���׷��̵� Ÿ�� (1:����/2:ȸ����/3:������(�ִ����))
	INT			iNpcUpValue;				// ���׷��̵� ��ġ (3�� �������� ��� ������ �ö� ������ ��)
} PMSG_ANS_NPCUPGRADE, *LPPMSG_ANS_NPCUPGRADE;

//----------------------------------------------------------------------------
// CG [0xB2][0x08] ���� ���� �ڱ�, ���� ���� ��û ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���)
	BYTE		btTaxRateChaos;				// ���� ���� ���� - ī��������
	BYTE		btTaxRateStore;				// ���� ���� ���� - ����
	BYTE		btMoney1;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMoney2;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMoney3;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMoney4;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMoney5;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMoney6;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMoney7;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMoney8;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 8)
} PMSG_ANS_TAXMONEYINFO, *LPPMSG_ANS_TAXMONEYINFO;

//----------------------------------------------------------------------------
// CG [0xB2][0x09] ���� ���� ���� ���� ��û ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���)
	BYTE		btTaxType;					// ���� ���� (1:ī��������/2:����)
	BYTE		btTaxRate1;					// ����� ���� ����
	BYTE		btTaxRate2;					// ����� ���� ����
	BYTE		btTaxRate3;					// ����� ���� ����
	BYTE		btTaxRate4;					// ����� ���� ����
} PMSG_ANS_TAXRATECHANGE, *LPPMSG_ANS_TAXRATECHANGE;

//----------------------------------------------------------------------------
// CG [0xB2][0x10] ���� ���� �ڱ� ��� ��û ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���)
	BYTE		btMoney1;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMoney2;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMoney3;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMoney4;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMoney5;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMoney6;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMoney7;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMoney8;					// ���� ���� �ڱ� (INT64�� �ֻ��� ����Ʈ ���� 8)
} PMSG_ANS_MONEYDRAWOUT, *LPPMSG_ANS_MONEYDRAWOUT;

//----------------------------------------------------------------------------
// CG [0xB2][0x1A] ���� ���� (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	Header;
	BYTE		btTaxType;					// ���� ���� (1:ī��������/2:����)
	BYTE		btTaxRate;					// ����
} PMSG_ANS_MAPSVRTAXINFO, *LPPMSG_ANS_MAPSVRTAXINFO;

//----------------------------------------------------------------------------
// GC [0xB3] �������� DB�� �����Ǵ� Ư�� NPC�� ����� ��û ���� (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
    PREQUEST_DEFAULT_SUBCODE    m_Header;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�����̾���)
	INT			iCount;
} PMSG_ANS_NPCDBLIST, *LPPMSG_ANS_NPCDBLIST;
typedef struct
{
	INT			iNpcNumber;					// NPC��ȣ
	INT			iNpcIndex;					// NPC�ε���
	INT			iNpcDfLevel;				// ���� ����
	INT			iNpcRgLevel;				// ȸ���� ����
	INT			iNpcMaxHp;					// �ִ� HP
	INT			iNpcHp;						// HP
	BYTE		btNpcX;						// ��ǥ - X
	BYTE		btNpcY;						// ��ǥ - Y
	BYTE		btNpcLive;					// NPC�� ���� �����ϴ��� ����
} PMSG_NPCDBLIST, *LPPMSG_NPCDBLIST;


//----------------------------------------------------------------------------
// GC [0xB4] ���� ��� ����� ��û ���� (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	h;
	BYTE		btResult;					// ��û ��� (0:����/1:����)
	INT			iCount;
} PMSG_ANS_CSREGGUILDLIST, *LPPMSG_ANS_CSREGGUILDLIST;
typedef struct
{
	CHAR		szGuildName[8];				// ����̸�
	BYTE		btRegMarks1;				// ������ ǥ���� ���� (INT�� ���� ����Ʈ ���� 1)
	BYTE		btRegMarks2;				// ������ ǥ���� ���� (INT�� ���� ����Ʈ ���� 2)
	BYTE		btRegMarks3;				// ������ ǥ���� ���� (INT�� ���� ����Ʈ ���� 3)
	BYTE		btRegMarks4;				// ������ ǥ���� ���� (INT�� ���� ����Ʈ ���� 4)
	BYTE		btIsGiveUp;					// ���⿩�� (0:�������/1:������)
	BYTE		btSeqNum;					// ��ϼ���
} PMSG_CSREGGUILDLIST, *LPPMSG_CSREGGUILDLIST;

//----------------------------------------------------------------------------
// GC [0xB5] ���� Ȯ�� ����� ��û ���� (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PREQUEST_DEFAULT_SUBCODE	h;
	BYTE		btResult;					// ��û ��� (0:����/1:����/2:�Ⱓ�ƴ�/3:�������غ�ʵ�)
	INT			iCount;
} PMSG_ANS_CSATTKGUILDLIST, *LPPMSG_ANS_CSATTKGUILDLIST;
typedef struct
{
	BYTE		btCsJoinSide;				// ������ ���� (1:������/2�̻�:������)
	BYTE		btGuildInvolved;			// ��尡 ������ ���� ������� ���� (0:�ƴ�/1:������)
	CHAR		szGuildName[8];				// ����̸�
	INT			iGuildScore;				// ��� ���� ����� ���� <<--- �߰���
} PMSG_CSATTKGUILDLIST, *LPPMSG_CSATTKGUILDLIST;


typedef struct 
{
	PBMSG_HEADER    m_Header;
	BYTE            m_bySubCode;
}PBMSG_HEADER2;

//----------------------------------------------------------------------------
// GC [0xA4][0x00] ������ ���� ų ī��Ʈ ������ �ǵ����ش�.
//----------------------------------------------------------------------------
typedef struct
{ 
	PBMSG_HEADER2	h;
	BYTE	byResult;		// ��� 0x00:����(����)
							//		0x01:���� 
							//		0x02:�̹� �Ϸ��� ����Ʈ
							//		0x03:�������� ����Ʈ �ƴ�
							//		0x04:����Ʈ�� ����(����Ʈ ��ȣ�� �߸�����)
							//		0x05:�Ϸ������� ųī��Ʈ�� �ƴ�(Ŭ���̾�Ʈ���� ��û�ϸ� �ȵ�)
		
	BYTE	byQuestIndex;		// ����Ʈ �ε���
	int		anKillCountInfo[10];// ���� ųī��Ʈ ����
} PMSG_ANS_QUEST_MONKILL_INFO, *LPPMSG_ANS_QUEST_MONKILL_INFO;

    //////////////////////////////////////////////////////////////////////////
    //  GC [0xB2][0x1F] �� ����� ���� ���� ���� ���� ��û ���� ( 0xC1 )
    //////////////////////////////////////////////////////////////////////////
    typedef struct 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byResult;
        BYTE                m_byHuntZoneEnter;
    }PMSG_CSHUNTZONEENTER, *LPPMSG_CSHUNTZONEENTER;

    //////////////////////////////////////////////////////////////////////////
    //  GC [0xB9][0x03] �� ����� �����Ⱑ �� ������� ���� ������ �˷��ش�.
    //////////////////////////////////////////////////////////////////////////
    typedef struct 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byResult;         //  0:�Ϲ���, 1:�Ϲ���, 2:����(���)��, 3:����(���)������.
        BYTE                m_byEnable;         //  0:�Ϲ��� ���� �Ұ�, 1:�Ϲ��� ���� ����.
        INT                 m_iCurrPrice;       //  ���� ������ �����.
        INT                 m_iMaxPrice;        //  �ִ� ������ �ִ� �����.
        INT                 m_iUnitPrice;       //  ���� ����.
    }PRECEIVE_CASTLE_HUNTZONE_INFO, *LPPRECEIVE_CASTLE_HUNTZONE_INFO; 

    //////////////////////////////////////////////////////////////////////////
    //  GC [0xB9][0x05] �� ����� ���� ���.
    //////////////////////////////////////////////////////////////////////////
    typedef struct 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byResult;     //  0:����Ұ�, 1:���尡��
    }PRECEVIE_CASTLE_HUNTZONE_RESULT, *LPPRECEVIE_CASTLE_HUNTZONE_RESULT;

    //////////////////////////////////////////////////////////////////////////
    //  GC [0xB9][0x02] ���� ������ ��� ��ũ.
    //////////////////////////////////////////////////////////////////////////
    typedef struct 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byGuildMark[32];
    }PRECEIVE_CASTLE_FLAG, *LPPRECEIVE_CASTLE_FLAG;

    //////////////////////////////////////////////////////////////////////////
    //  ����.
    //////////////////////////////////////////////////////////////////////////
    typedef struct  //  ���� ����.
    {
        PBMSG_HEADER2        m_Header;           //  ���.
        BYTE                m_byResult;         //  ���� ���� ��û �����. ( 0:����, 1:����, 2:��������, 3:��������, 4:���Ѿ��� )
        BYTE                m_byKeyH;           //  
        BYTE                m_byKeyL;
    }PRECEIVE_GATE_STATE, *LPPRECEIVE_GATE_STATE;


    typedef struct  //  ������ ���� ��� ���.
    {
        PBMSG_HEADER2        m_Header;
        BYTE                m_byResult;         //  ���� ���� ��û �����. ( 0:����, 1:����, 2:��������, 3:��������, 4:���Ѿ��� )
        BYTE                m_byOperator;       //  �۵� ���.
        BYTE                m_byKeyH;
        BYTE                m_byKeyL;
    }PRECEIVE_GATE_OPERATOR, *LPPRECEIVE_GATE_OPERATOR;


    typedef struct  //  ������ ����.
    {
        PBMSG_HEADER2        m_Header;
        BYTE                m_byOperator;       //  �۵� ��Ȳ ( 0:�ݱ�, 1:���� )
        BYTE                m_byKeyH;
        BYTE                m_byKeyL;
    }PRECEIVE_GATE_CURRENT_STATE, *LPPRECEIVE_GATE_CURRENT_STATE;


    typedef struct  //  ����ġ �۵� ����.
    {
        PBMSG_HEADER2       m_Header;   
        BYTE                m_byIndexH;         //  �հ� ����ġ �ε���.
        BYTE                m_byIndexL;         //  
        BYTE                m_byKeyH;           //  ����� ����ġ �ε���.
        BYTE                m_byKeyL;           //  
        BYTE                m_byState;          //  ����. ( 0:����ġ��, 1:����ġ �۵�, 2:�ٸ��̰� ����� )
    }PRECEIVE_SWITCH_PROC, *LPPRECEIVE_SWITCH_PROC;


    typedef struct  //  �հ��� ����.
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byCrownState;     //  �հ��� ���� ( 0:���ε��, 1:���ε�ϼ���, 2:���ε�Ͻ���, 3:�ٸ������ ����� )

		DWORD				m_dwCrownAccessTime;

    }PRECEIVE_CROWN_STATE, *LPPRECEIVE_CROWN_STATE;


	typedef struct
	{
		PBMSG_HEADER2		m_Header;
		BYTE				m_byIndex1;
		BYTE				m_byIndex2;
		BYTE				m_bySwitchState;
		BYTE				m_JoinSide;

		BYTE				m_szGuildName[8];
		BYTE				m_szUserName[MAX_ID_SIZE+1];
	}PRECEIVE_CROWN_SWITCH_INFO, *LPRECEIVE_CROWN_SWITCH_INFO;


    typedef struct  //  ������ ���� ���� �˸�.
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byBasttleCastleState; //  0:���� ���� ���, 1:�߰� �¸�.
        BYTE                m_szGuildName[8];       //  ���, �¸��� ��� �̸�.
    }PRECEIVE_BC_PROCESS, *LPPRECEIVE_BC_PROCESS;


    //////////////////////////////////////////////////////////////////////////
    //  
    //////////////////////////////////////////////////////////////////////////
    typedef struct //   ���� ���� �ð�.
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byKeyH;
        BYTE                m_byKeyL;

        BYTE                m_byBuildTime;
    }PRECEIVE_MONSTER_BUILD_TIME, *LPPRECEIVE_MONSTER_BUILD_TIME;


    //////////////////////////////////////////////////////////////////////////
    //  ��������
    //////////////////////////////////////////////////////////////////////////
    typedef struct  //  Npc���ý� ������ Npc�� ���°�.
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byResult;         //  NPC��û ���. ( 0:����, 1:����, 2... ).

        BYTE                m_byWeaponType;     //  ���� ����.

        BYTE                m_byKeyH;           //  NPC Key��.
        BYTE                m_byKeyL;
    }PRECEIVE_CATAPULT_STATE, *LPPRECEIVE_CATAPULT_STATE;


    typedef struct  //  ���� ���� �߻� ��û ���.
    {
        PBMSG_HEADER2        m_Header;
        BYTE                m_byResult;         //  �߻� ��û ���.
        BYTE                m_byKeyH;           //  �߻��ϴ� ������ Ű��.
        BYTE                m_byKeyL;           

        BYTE                m_byWeaponType;     //  ���� ���� ( 0: ����, 1:���� )

        BYTE                m_byTargetX;        //  ���� ��ġ X.
        BYTE                m_byTargetY;        //  ���� ��ġ Y.
    }PRECEIVE_WEAPON_FIRE, *LPPRECEIVE_WEAPON_FIRE;


    typedef struct  //  ������ ���� �溸.
    {
        PBMSG_HEADER2        m_Header;
        BYTE                m_byWeaponType;     //  ���� ���� ( 0:����, 1:���� )

        BYTE                m_byTargetX;        //  ���� ��ġ X.
        BYTE                m_byTargetY;        //  ���� ��ġ Y.
    }PRECEIVE_BOMBING_ALERT, *LPPRECEIVE_BOMBING_ALERT;


    typedef struct //   ������ �޴� ��� ����.
    {
        PBMSG_HEADER2        m_Header;
        BYTE                m_byKeyH;           //  ���� ���ϴ� Key��.
        BYTE                m_byKeyL;

        BYTE                m_byWeaponType;     //  ���� ���� ( 0:����, 1:���� ).
    }PRECEIVE_BOMBING_TARGET, *LPPRECEIVE_BOMBING_TARGET;


    typedef struct //   �̸� �ӽ����� ��ġ�� ����Ʈ�� �޴´�.
    {
        BYTE                m_byObjType;        //  ������Ʈ ����. ( 0:ĳ����, 1:����, 2:NPC )
        BYTE                m_byTypeH;
        BYTE                m_byTypeL;
        BYTE                m_byKeyH;
        BYTE                m_byKeyL;
        BYTE                m_byPosX;
        BYTE                m_byPosY;
    	BYTE                m_byEquipment[EQUIPMENT_LENGTH];
		BYTE				s_BuffCount;
		BYTE				s_BuffEffectState[MAX_BUFF_SLOT_INDEX];     
    }PRECEIVE_PREVIEW_PORT, *LPPRECEIVE_PREVIEW_PORT;


    typedef struct 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byTeam;
        BYTE                m_byX;
        BYTE                m_byY;
        BYTE                m_byCmd;
    }PRECEIVE_GUILD_COMMAND, *LPPRECEIVE_GUILD_COMMAND;


    typedef struct 
    {
        BYTE                m_byX;
        BYTE                m_byY;
    }PRECEIVE_MEMBER_LOCATION, *LPPRECEIVE_MEMBER_LOCATION;


    typedef struct 
    {
        BYTE                m_byType;           //  ������Ʈ ����.
        BYTE                m_byX;
        BYTE                m_byY;
    }PRECEIVE_NPC_LOCATION, *LPPRECEIVE_NPC_LOCATION;


    typedef struct
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byResult;         //  ������ ��û ���.
    }PRECEIVE_MAP_INFO_RESULT, *LPPRECEIVE_MAP_INFO_RESULT;

    typedef struct  //  ������ �� ���� �ð��� ����ڵ鿡�� �ֱ������� �˸�. 
    {
        PBMSG_HEADER2       m_Header;
        BYTE                m_byHour;
        BYTE                m_byMinute;
    }PRECEIVE_MATCH_TIMER, *LPPRECEIVE_MATCH_TIMER;
	
	typedef struct  
	{
		PBMSG_HEADER2		m_Header;	
		BYTE				m_iJewelType;		//���� Ÿ�� ( 0: �༮ / 1: ����)
		BYTE				m_iJewelMix;		//���� Ÿ�� ( 0, 1, 2������ 10��, 20��, 30��)
	}PMSG_REQ_JEWEL_MIX, *LPPMSG_REQ_JEWEL_MIX;

	typedef struct 
	{
		PBMSG_HEADER2		m_Header;
		BYTE				m_iResult;			//0 : ����, 1: ����
												//2 : ���� Ÿ�� ����, 3: ����Ÿ�� ����, 4: ���� ����, 5: ���ձ� ����
	}PMSG_ANS_JEWEL_MIX, *LPPMSG_ANS_JEWEL_MIX;

	typedef struct  
	{
		PBMSG_HEADER2		m_Header;			
		BYTE				m_iJewelType;		//���� Ÿ��
		BYTE				m_iJewelLevel;		//���յ� ����
		BYTE				m_iJewelPos;		//�κ��丮 �� �ε���
	}PMSG_REQ_JEWEL_UNMIX, *LPPMSG_REQ_JEWEL_UNMIX;

	typedef struct  
	{
		PBMSG_HEADER2		m_Header;
		
		int		iMasterLevelSkill;	// �����Ϸ��� ��ų ��ȣ
	}PMSG_REQ_MASTERLEVEL_SKILL, *LPPMSG_REQ_MASTERLEVEL_SKILL;

	typedef struct 
	{
		PBMSG_HEADER2		m_Header;
		BYTE				m_iResult;			//0: ����, 1: ����
												//2: ���� Ÿ�� ����, 3: ���� ���� ���� 4: ������ ����
												//5: �κ��丮 ���� ����, 6: ��ü�� ������ ����
												//7: �κ��丮 ���� ����, 8: ���ձ��� ����
	}PMSG_ANS_JEWEL_UNMIX, *LPPMSG_ANS_JEWEL_UNMIX;

////////////////////////////////////////////////////////////////////////////
//  ũ���̿��� 1�� MVP �������� ( 0xBD ��� )
////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// GC [0xBD][0x00] Ŭ���̾�Ʈ�� ũ���̿��� ���� �� �������� ��û�� ���� ����
//--------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE			btOccupationState;	// ���� ���� (0:��ȭ, 1:����, 2:����)
	BYTE			btCrywolfState;		// ũ���̿��� ���� ����

} PMSG_ANS_CRYWOLF_INFO, *LPPMSG_ANS_CRYWOLF_INFO;

//--------------------------------------------------------------------------
// GC [0xBD][0x02] ��, ���� ���� ����
//--------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	INT				iCrywolfStatueHP;	// �� HP
	BYTE			btAltarState1;		// ���� 1 ����
	BYTE			btAltarState2;		// ���� 2 ����
	BYTE			btAltarState3;		// ���� 3 ����
	BYTE			btAltarState4;		// ���� 4 ����
	BYTE			btAltarState5;		// ���� 5 ����

} PMSG_ANS_CRYWOLF_STATE_ALTAR_INFO, *LPPMSG_ANS_CRYWOLF_STATE_ALTAR_INFO;

//--------------------------------------------------------------------------
// GC [0xBD][0x03] Ŭ���̾�Ʈ�� Ư�� ���ܰ� ���� ��� ��û�� ���� ����
//--------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE			bResult;			// ��� ��� (0:����, 1:����)
	BYTE			btAltarState;		// ���� ����
	BYTE			btObjIndexH;		// ���� �ε���
	BYTE			btObjIndexL;		// ���� �ε���

} PMSG_ANS_CRYWOLF_ALTAR_CONTRACT, *LPPPMSG_ANS_CRYWOLF_ALTAR_CONTRACT;

//--------------------------------------------------------------------------
// GC [0xBD][0x04] ũ���̿��� ���� �ð�
//--------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE			btHour;				// ���� �ð�
	BYTE			btMinute;			// ���� ��

} PMSG_ANS_CRYWOLF_LEFTTIME, *LPPPMSG_ANS_CRYWOLF_LEFTTIME;

//--------------------------------------------------------------------------
// GC [0xBD][0x0C] ũ���̿��� MVP ��Ŀ ���� ���� �˸�
//--------------------------------------------------------------------------
typedef struct
{
    PBMSG_HEADER2       h;

    BYTE                btObjClassH;        //  ���� ����
    BYTE                btObjClassL;           

	BYTE                btSourceX;        //  �߻� ��ġ X.
    BYTE                btSourceY;        //  �߻� ��ġ Y.

    BYTE                btPointX;        //  ���� ��ġ X.
    BYTE                btPointY;        //  ���� ��ġ Y.
} PMSG_NOTIFY_REGION_MONSTER_ATTACK, *LPPMSG_NOTIFY_REGION_MONSTER_ATTACK;

typedef struct
{
	PBMSG_HEADER2	h;

	int				btBossHP;			//�߰��� HP
	BYTE			btMonster2;			//��ũ���� ������
	
} PMSG_ANS_CRYWOLF_BOSSMONSTER_INFO, *LPPMSG_ANS_CRYWOLF_BOSSMONSTER_INFO;


typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE			btPlusChaosRate;	// ũ���̿��� ����
} PMSG_ANS_CRYWOLF_BENEFIT_PLUS_CHAOSRATE, *LPPMSG_ANS_CRYWOLF_BENEFIT_PLUS_CHAOSRATE;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

typedef struct
{
	PBMSG_HEADER2	h;
	BYTE			btRank;			//0 : D    1 : C   2 : B   3 : A   4 : S
	int				iGettingExp;	//ȹ�����ġ
} PMSG_ANS_CRYWOLF_PERSONAL_RANK, *LPPMSG_ANS_CRYWOLF_PERSONAL_RANK;

typedef struct
{
	PBMSG_HEADER2	h;
	BYTE			btCount;
} PMSG_ANS_CRYWOLF_HERO_LIST_INFO_COUNT, *LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO_COUNT;

typedef struct
{
	BYTE iRank;
	char szHeroName[MAX_ID_SIZE];
	int iHeroScore;
	BYTE btHeroClass;
} PMSG_ANS_CRYWOLF_HERO_LIST_INFO, *LPPMSG_ANS_CRYWOLF_HERO_LIST_INFO;
//////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//  ĭ���� ����  �������� ( 0xD1 ��� )
////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// CG [0xD1][0x00] Ŭ���̾�Ʈ�� ĭ���� �������� ���� ���� ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE	btState;			// ĭ���� ������ ����
	BYTE	btDetailState;		// ĭ���� ������ ���� ����

	BYTE	btEnter;			// ���� ���� ���� ( 0:�Ұ� 1:���� )
	BYTE	btUserCount;		// ������ ���� �� ��� ���� ���� �ο�
	int		iRemainTime;		// ������ ������ ��� ���� ������� ���� �ð�(Sec)
	
} PMSG_ANS_KANTURU_STATE_INFO, *LPPMSG_ANS_KANTURU_STATE_INFO;

//----------------------------------------------------------------------------
// GC [0xD1][0x01] Ŭ���̾�Ʈ�� ĭ���� ������ ������ ���� ��û�� ���� ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	
	BYTE		btResult;	// 0:���尡��
							// 1:���� ������ �ο� �� �ʰ�
							// 2:���忡 �ʿ��� �������� ����
							// 3:���尡���� ���°� �ƴ�

} PMSG_ANS_ENTER_KANTURU_BOSS_MAP, *LPPMSG_ANS_ENTER_KANTURU_BOSS_MAP;

//----------------------------------------------------------------------------
// GC [0xD1][0x02] ������ ĭ���� ������ �����ʿ� �������� �� ���� ���¸� ������
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE		btCurrentState;			// ĭ������ ���� ���� ����
	BYTE		btCurrentDetailState;	// �׿� ���� ���� ����

} PMSG_ANS_KANTURU_CURRENT_STATE, *LPPMSG_ANS_KANTURU_CURRENT_STATE;

//----------------------------------------------------------------------------
// GC [0xD1][0x03] ĭ���� ������ ���� ���°� ������ �� ���°��� �˸���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE		btState;			// ĭ������ ���� ����
	BYTE		btDetailState;		// �׿� ���� ���� ����
	
} PMSG_ANS_KANTURU_STATE_CHANGE, *LPPMSG_ANS_KANTURU_STATE_CHANGE;

//----------------------------------------------------------------------------
// GC [0xD1][0x04] ĭ���� ������ ���� ���� / ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE		btResult;	// 0:���� 1:����
	
} PMSG_ANS_KANTURU_BATTLE_RESULT, *LPPMSG_ANS_KANTURU_BATTLE_RESULT;

//----------------------------------------------------------------------------
// GC [0xD1][0x05] ĭ���� ������ ���� ���⸶�� ���� �ð�
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	int			btTimeLimit;	// ���� �ð�(Sec)
	
} PMSG_ANS_KANTURU_BATTLE_SCENE_TIMELIMIT, *LPPMSG_ANS_KANTURU_BATTLE_SCENE_TIMELIMIT;

//----------------------------------------------------------------------------
// GC [0xD1][0x06] ĭ���� ������ ���� ����( ���� ��ų ��� )
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE		btObjClassH;	// ���� ����
	BYTE		btObjClassL;
	
	BYTE		btType;			// 0 : ���̽�����  1:���ū����

} PMSG_NOTIFY_KANTURU_WIDE_AREA_ATTACK, *LPPMSG_NOTIFY_KANTURU_WIDE_AREA_ATTACK;

//----------------------------------------------------------------------------
// GC [0xD1][0x07] ĭ���� ���� ����&���� �� ���÷���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE		bMonsterCount;		// �������� ���� �� ���� ��
	BYTE		btUserCount;		// �������� ���� �� ���� ��

} PMSG_NOTIFY_KANTURU_USER_MONSTER_COUNT, *LPPMSG_NOTIFY_KANTURU_USER_MONSTER_COUNT;


#ifdef ADD_PCROOM_POINT_SYSTEM
//----------------------------------------------------------------------------
// PC�� ����Ʈ �ý��� : 0xD0 ���
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// GC [0xD0][0x04] PC�� ����Ʈ ���� ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;	
	short		nPoint;			// ���� ����Ʈ
	short		nMaxPoint;		// �ִ� ����Ʈ
#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
	BYTE		bPCBang;		// PC���ΰ� �ƴѰ�?	
#endif // CSK_MOD_MOVE_COMMAND_WINDOW	
} PMSG_ANS_GC_PCROOM_POINT_INFO, *LPPMSG_ANS_GC_PCROOM_POINT_INFO;

//----------------------------------------------------------------------------
// GC [0xD0][0x05] PC�� ����Ʈ ��� ��û ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		byResult;	// ��� ��� 0x00:���� 
							//			0x01:�������� �ƴ� 
							//			0x02:�ش���ġ�� �������� ���� 
							//			0x03:�κ��丮 ���� ����
							//			0x04:�⺻ ���� ����Ʈ����
							//			0x05:PC�� ����Ʈ �ý��� ����ڰ� �ƴ�
							//			0x06:����
							//			0x07:���� ��� ���� �ð� �ʰ�
							//			0x08:PC�� ����Ʈ ���� �������� �ƴ�
							//			0x09:���� ������ ����Ʈ ����
	BYTE		byInvenPos;		// �κ��丮 ��ġ	0xff�� ��� ����.
						// *������ ������ �ٷ� �����ϰ� �������� ������ �κ��� ������ �߰��Ѵ�.
	BYTE		ItemInfo[PACKET_ITEM_LENGTH];
} PMSG_ANS_GC_PCROOM_POINT_USE, *LPPMSG_ANS_GC_PCROOM_POINT_USE;

//----------------------------------------------------------------------------
// CG GC [0xD0][0x06] PC�� ����Ʈ �� ����/����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		byResult;	// ���	0x00:���� 
							//		0x01:�������� �ƴ�
							//		0x02:������ ������ ���� 
							//		0x03:�ٸ� â ��� �� 
							//		0x04:PC�� ����Ʈ �ý��� ����ڰ� �ƴ�							
							//		0x05:����
} PMSG_REQ_PCROOM_POINT_SHOP_OPEN, *LPPMSG_REQ_PCROOM_POINT_SHOP_OPEN;

#endif	// ADD_PCROOM_POINT_SYSTEM

//----------------------------------------------------------------------------
// CG [0xBF][0x00] ���� ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE			btCursedTempleIdx;// ���ֹ��� ��� ��ȣ
	BYTE			iItemPos;// ���� �η縶�� ��ġ
} PMSG_REQ_ENTER_CURSED_TEMPLE, *LPPMSG_REQ_ENTER_CURSED_TEMPLE;

//----------------------------------------------------------------------------
// GC [0xBF][0x00] ���� ��û ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE			Result;		/* ��û��� (	0 : ����
											1 : �˸��� ���� �η縶�� ����
											2 : ���� �ִ� �ð��� �ƴ�
											3 : ���� �η縶���� ������ �ڽ��� ������ ���� ����
											4 : �ο������� �Ѿ���
											5 : 1�� �������� Ƚ���� �Ѿ���
											6 : ����ᰡ ���ڶ���.
											7 : ī�������� ������ �� ����.
											8 : ���Ź����� �����ϰ� ������ �� ����.
										)
							    */
} PMSG_RESULT_ENTER_CURSED_TEMPLE, *LPPMSG_RESULT_ENTER_CURSED_TEMPLE;

//----------------------------------------------------------------------------
// GC [0xBF][0x01] ���� ���� / �ð� ���� / ��Ƽ ��ġ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	WORD		wRemainSec;			// ���ӽ��� �� ������� ���� ��
	WORD		btUserIndex;		// ������ ������ �ִ� ����� �ε���
	BYTE		btX;				// ���� ��ġ X
	BYTE		btY;				// ���� ��ġ Y
	BYTE		btAlliedPoint;		// ���ձ��� ����
	BYTE		btIllusionPoint;	// ȯ�������� ����
	BYTE		btMyTeam;		    // 0:���ձ�, 1: ȯ������

	BYTE		btPartyCount;
} PMSG_CURSED_TAMPLE_STATE, *LPPMSG_CURSED_TAMPLE_STATE;

typedef struct 
{
	WORD		wPartyUserIndex;
	BYTE		byMapNumber;
	BYTE		btX;
	BYTE		btY;	
} PMSG_CURSED_TAMPLE_PARTY_POS, *LPPMSG_CURSED_TAMPLE_PARTY_POS;

//----------------------------------------------------------------------------
// CG [0xBF][0x02]	���ֹ��� ��� ���� �������
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;

	BYTE          MagicH;
	BYTE          MagicL;
	WORD		wTargetObjIndex;	// Ÿ�� �ε���
	BYTE		Dis;				// �Ÿ�
} PMSG_CURSED_TEMPLE_USE_MAGIC, *LPPMSG_CURSED_TEMPLE_USE_MAGIC;

//----------------------------------------------------------------------------
// GC [0xBF][0x03]	���ֹ��� ����� ������ �ο����� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		btUserCount[6];		// �� ���ֹ��� ����� �ο���
} PMSG_CURSED_TEMPLE_USER_COUNT, *LPPMSG_CURSED_TEMPLE_USER_COUNT;

//----------------------------------------------------------------------------
// GC [0xBF][0x02]	���ֹ��� ��� ���� ������� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE        MagicResult;        // 0 ����, 1 ����

	BYTE          MagicH;
	BYTE          MagicL;

	WORD		wSourceObjIndex;	// �ҽ� �ε���
	WORD		wTargetObjIndex;	// Ÿ�� �ε���
} PMSG_CURSED_TEMPLE_USE_MAGIC_RESULT, *LPPMSG_CURSED_TEMPLE_USE_MAGIC_RESULT;

//----------------------------------------------------------------------------
// GC [0xBF][0x04] �̺�Ʈ ��� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		btAlliedPoint;		// ���ձ��� ����
	BYTE		btIllusionPoint;	// ȯ�������� ����

	BYTE		btUserCount;		// ĳ���� ��
} PMSG_CURSED_TEMPLE_RESULT, *LPPMSG_CURSED_TEMPLE_RESULT;

typedef struct 
{
	char		GameId[MAX_ID_SIZE];		// ĳ�����̸�
	BYTE		byMapNumber;				// �ʹ�ȣ
	BYTE		btTeam;						// ��
	BYTE		btClass;					// Ŭ����
	int			nAddExp;					// ���� ����ġ
} PMSG_CURSED_TEMPLE_USER_ADD_EXP, *LPPMSG_CURSED_TEMPLE_USER_ADD_EXP;


//----------------------------------------------------------------------------
// GC [0xBF][0x06] ���ֹ��� ������� ���͸� �׿��� ��� ��ų ����Ʈ
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	BYTE		btSkillPoint;		// ������ ��ų ����Ʈ
} PMSG_CURSED_TEMPLE_SKILL_POINT, *LPPMSG_CURSED_TEMPLE_SKILL_POINT;

//----------------------------------------------------------------------------
// GC [0xBF][0x07] ���ֹ��� ������� ���뽺ų ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;

	BYTE          MagicH;
	BYTE          MagicL;

	WORD		wObjIndex;
} PMSG_CURSED_TEMPLE_SKILL_END, *LPPMSG_CURSED_TEMPLE_SKILL_END;

//----------------------------------------------------------------------------
// GC [0xBF][0x08] ȯ�� ������� ������ ȹ��
//----------------------------------------------------------------------------
typedef struct  
{
	PBMSG_HEADER2 h;
	WORD		wUserIndex;
	char		Name[MAX_ID_SIZE];	
} PMSG_RELICS_GET_USER, *LPPMSG_RELICS_GET_USER;

//----------------------------------------------------------------------------
// GC [0xBF][0x09] ȯ�� ����� ���� ����
//----------------------------------------------------------------------------
typedef struct  
{
	PBMSG_HEADER2 h;
	BYTE		btTempleNumber;
	BYTE		btIllusionTempleState;	// 0: wait, 1: wait->ready, 2: ready->play, 3: play->end, 
} PMSG_ILLUSION_TEMPLE_STATE, *LPPMSG_ILLUSION_TEMPLE_STATE;

//----------------------------------------------------------------------------
// GC [0xBF][0x0a] ü�θ��� ����
//----------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////
// ������ ü�ζ���Ʈ�� ������ �����κ��� �޴� ��Ŷ
// �������� SendRequestMagicContinue() �� ����
/////////////////////////////////////////////////////////////////////
// Receive Chain Magic			
typedef struct {
	PBMSG_HEADER2	Header;

	BYTE			MagicH;
	BYTE			MagicL;

	WORD			wUserIndex;
	BYTE			byCount;
} PRECEIVE_CHAIN_MAGIC, *LPPRECEIVE_CHAIN_MAGIC;

	/////////////////////////////////////////////////////////////////////
	// ReceiveChainMagic()�� wCount ������� �����κ��� ��Ŷ�� �޴´�.
	/////////////////////////////////////////////////////////////////////
	// Receive Chain Magic Object
	typedef struct {
		WORD			wTargetIndex;
	} PRECEIVE_CHAIN_MAGIC_OBJECT, *LPPRECEIVE_CHAIN_MAGIC_OBJECT;

typedef struct 
{
	PBMSG_HEADER  h;	
	BYTE		subcode;	
	
	short		nMLevel;		// �����ͷ���

	BYTE		btMExp1;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMExp2;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMExp3;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMExp4;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMExp5;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMExp6;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMExp7;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMExp8;					// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 8)

	BYTE		btMNextExp1;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 1)
	BYTE		btMNextExp2;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 2)
	BYTE		btMNextExp3;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 3)
	BYTE		btMNextExp4;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 4)
	BYTE		btMNextExp5;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 5)
	BYTE		btMNextExp6;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 6)
	BYTE		btMNextExp7;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 7)
	BYTE		btMNextExp8;				// ���� �����ͷ��� ����ġ (INT64�� �ֻ��� ����Ʈ ���� 8)

	// �����ͷ��� ����Ʈ(����)
	// �����ͽ�ų �� �����ͽ�ų Ʈ�� ����(����)

	short		nMLPoint;					// �����ͷ��� ����Ʈ

	// �����ͷ����� ���� ������ �缳���ȴ�.
	WORD		wMaxLife;
	WORD		wMaxMana;
	WORD		wMaxShield;
	WORD		wMaxSkillMana;
} PMSG_MASTERLEVEL_INFO, *LPPMSG_MASTERLEVEL_INFO;

typedef struct 
{
	PBMSG_HEADER	h;
	BYTE		subcode;

	short		nMLevel;			// ���� �����ͷ���

	short		nAddMPoint;			// �߰��� �����ͷ��� ����Ʈ
	short       nMLevelUpMPoint;	// ��� ������ �����ͷ��� ����Ʈ
//	short		nTotalMPoint;		// ���� ���� �� �����ͷ��� ����Ʈ
	short		nMaxPoint;			// �ִ� �����ͷ��� ����Ʈ

	WORD		wMaxLife;
	WORD		wMaxMana;
	WORD		wMaxShield;
	WORD		wMaxBP;
} PMSG_MASTERLEVEL_UP, *LPPMSG_MASTERLEVEL_UP;

typedef struct  
{
	PBMSG_HEADER	h;
	BYTE		subcode;

	BYTE		btResult;	// �����	0:���� 1:�����ߴ�. 2:���� ������ ����� �ƴ� 3:���� ������ ��ų��ȣ �ƴ�
							//			4:�����ͷ��� ����Ʈ ���� 5:�� ��

	short       nMLPoint;	// ���� �����ͷ��� ����Ʈ

	int			nSkillNum;
	int			nSkillLevel;
} PMSG_ANS_MASTERLEVEL_SKILL, *LPPMSG_ANS_MASTERLEVEL_SKILL;

#ifdef PJH_CHARACTER_RENAME
//----------------------------------------------------------------------------
// GC [0xF3][0x15] ĳ���͸� ���� Ȯ�ο�û ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	char		Name[MAX_ID_SIZE];
	BYTE		btResult;		// 0: ���ʿ�, 1: �ʿ�
} PMSG_ANS_CHECK_CHANGE_NAME, *LPPMSG_ANS_CHECK_CHANGE_NAME;

//----------------------------------------------------------------------------
// GC [0xF3][0x16] ĳ���͸� ���� ��û ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	char		Name[MAX_ID_SIZE];
	char		NewName[MAX_ID_SIZE];
	BYTE		btResult;		// 0: ����, 1: ���� ĳ���͸� ����
} PMSG_CHANGE_NAME_RESULT, *LPPMSG_CHANGE_NAME_RESULT;
#endif //PJH_CHARACTER_RENAME

#ifdef CSK_RAKLION_BOSS
//----------------------------------------------------------------------------
// GC [0xD1][0x10] ������ ��Ŭ���� �������� ���� ���� ���� ��û�� ���� ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	
	BYTE			btState;		// ��Ŭ���� ������ ����
	BYTE			btDetailState;	// ��Ŭ���� ������ ���� ����
	
	BYTE			btEnter;		// ���� ���� ���� ( 0:�Ұ� 1:���� )
	int				iRemainTime;	// ������ ������ ��� ���� ������� ���� �ð�(Sec)
} PMSG_ANS_RAKLION_STATE_INFO, *LPPMSG_ANS_RAKLION_STATE_INFO;

//----------------------------------------------------------------------------
// GC [0xD1][0x11] ������ ��Ŭ���� ������ �����ʿ� �������� �� ���� ���¸� ������.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	
	BYTE			btCurrentState;				// ��Ŭ������ ���� ���� ����
	BYTE			btCurrentDetailState;		// �׿� ���� ���� ����
} PMSG_ANS_RAKLION_CURRENT_STATE, *LPPMSG_ANS_RAKLION_CURRENT_STATE;

//----------------------------------------------------------------------------
// GC [0xD1][0x12] ��Ŭ���� ������ ���� ���°� ������ �� ���°��� �˸���.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;	
	
	BYTE			btState;			// ��Ŭ������ ���� ����
	BYTE			btDetailState;		// �׿� ���� ���� ����	
} PMSG_ANS_RAKLION_STATE_CHANGE, *LPPMSG_ANS_RAKLION_STATE_CHANGE;

//----------------------------------------------------------------------------
// GC [0xD1][0x13] ��Ŭ���� ������ ���� ���� / ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	
	BYTE			btResult;			// 0:���� 1:����
} PMSG_ANS_RAKLION_BATTLE_RESULT, *LPPMSG_ANS_RAKLION_BATTLE_RESULT;

//----------------------------------------------------------------------------
// GC [0xD1][0x14] ��Ŭ���� ������ ���� ����( ������ ��ų ��� )
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	
	BYTE			btObjClassH;		// ���� ����
	BYTE			btObjClassL;
	
	BYTE			btType;				// ��ų ����
	
} PMSG_NOTIFY_RAKLION_WIDE_AREA_ATTACK, *LPPMSG_NOTIFY_RAKLION_WIDE_AREA_ATTACK;

//----------------------------------------------------------------------------
// GC [0xD1][0x15] ��Ŭ���� ���� ����&���� �� ���÷���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	
	BYTE			btMonsterCount;		// �������� ���� �� ���� ��
	BYTE			btUserCount;		// �������� ���� �� ���� ��
} PMSG_NOTIFY_RAKLION_USER_MONSTER_COUNT, *LPPMSG_NOTIFY_RAKLION_USER_MONSTER_COUNT;

#endif // CSK_RAKLION_BOSS

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
//----------------------------------------------------------------------------
// CG[0xBF][0x0b] ��ϵ� ���� ���� ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	int			nRegCoinCnt;	// ����� ���� ����
} PMSG_REQ_GET_COIN_COUNT, *LPPMSG_REQ_GET_COIN_COUNT;

//----------------------------------------------------------------------------
// GC[0xBF][0x0b] ��ϵ� ���� ���� ���� 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	int			nCoinCnt;					// ��ϵ� ���� ����
}PMSG_ANS_GET_COIN_COUNT, *LPPMSG_ANS_GET_COIN_COUNT;

//----------------------------------------------------------------------------
// CG[0xBF][0x0c] ������� ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
}PMSG_REQ_REGEIST_COIN, *LPPMSG_REQ_REGEIST_COIN;

//----------------------------------------------------------------------------
// GC0xBF][0x0c] ���� ��� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	BYTE		btResult;						// 0:����, 1:����
	int			nCurCoinCnt;					// ���� ��ϵ� ���� ����
}PMSG_ANS_REGEIST_COIN, *LPPMSG_ANS_REGEIST_COIN;

//----------------------------------------------------------------------------
// CG[0xBF][0x0d] ���� ��ȯ ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	int			nCoinCnt;	// ��ȯ ����
}PMSG_REQ_TRADE_COIN, *LPPMSG_REG_TREADE_COIN;

//----------------------------------------------------------------------------
// GC[0xBF][0x0d] ���� ��ȯ ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2 h;
	BYTE		btResult;	// 0: ���� ���� ����, 1: ����
}PMSG_ANS_TRADE_COIN, *LPPMSG_ANS_TREADE_COIN;

#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

#ifdef YDG_ADD_DOPPELGANGER_PROTOCOLS
//----------------------------------------------------------------------------
// GC [0xBF][0x0E] ���ð���� ���� ��û ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		btResult;		/* ��û��� (	0 : ����
											1 : �����Ǹ��� ����
											2 : �̹� �ٸ� ��Ƽ�� �����
											3 : ī�������� ������ �� ����.
											4 : ���Ź����� �����ϰ� ������ �� ����.
										)
							*/
} PMSG_RESULT_ENTER_DOPPELGANGER, *LPPMSG_RESULT_ENTER_DOPPELGANGER;
//----------------------------------------------------------------------------
// GC [0xBF][0x0F] ���ð��� ���� ���� ��ġ
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		btPosIndex;	// ��ġ��ȣ(0~9) ���� ���������� 0
} PMSG_DOPPELGANGER_MONSTER_POSITION, *LPPMSG_DOPPELGANGER_MONSTER_POSITION;
//----------------------------------------------------------------------------
// GC [0xBF][0x10] ���ð����� ���� ����
//----------------------------------------------------------------------------
typedef struct  
{
	PBMSG_HEADER2 h;
	BYTE		btDoppelgangerState;	// 0: wait, 1: wait->ready, 2: ready->play, 3: play->end, 
} PMSG_DOPPELGANGER_STATE, *LPPMSG_DOPPELGANGER_STATE;
//----------------------------------------------------------------------------
// GC [0xBF][0x11] ���ð����� ���̽���Ŀ�� ���� ����
//----------------------------------------------------------------------------
typedef struct  
{
	PBMSG_HEADER2 h;
	BYTE		btIceworkerState;	// 0: ����, 1: �����
	BYTE		btPosIndex;	// ��ġ��ȣ(0~9) ���� ���������� 0
} PMSG_DOPPELGANGER_ICEWORKER_STATE, *LPPMSG_DOPPELGANGER_ICEWORKER_STATE;
//----------------------------------------------------------------------------
// GC [0xBF][0x12] ���ð����� ���� ���� / �ð� ���� / ��Ƽ ��ġ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	WORD		wRemainSec;			// ���ӽ��� �� ������� ���� ��	
	BYTE		btUserCount;		// ������
	BYTE		btDummy;
	BYTE		UserPosData;
} PMSG_DOPPELGANGER_PLAY_INFO, *LPPMSG_DOPPELGANGER_PLAY_INFO;

typedef struct 
{
	WORD		wUserIndex;			// ����� �ε���
	BYTE		byMapNumber;		// �ʹ�ȣ
	BYTE		btPosIndex;	// ��ġ��ȣ(0~9) ���� ���������� 0
} PMSG_DOPPELGANGER_USER_POS, *LPPMSG_DOPPELGANGER_USER_POS;
//----------------------------------------------------------------------------
// GC [0xBF][0x13] ���ð����� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		btResult;		// 0: ����, 1: ����(�׾����_�Ϲ�), 2: ����(������)
	DWORD		dwRewardExp;	// �������ġ
}PMSG_DOPPELGANGER_RESULT, *LPPMSG_DOPPELGANGER_RESULT;
//----------------------------------------------------------------------------
// GC [0xBF][0x14] ���ð����� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2 h;
	BYTE		btMaxGoalCnt;
	BYTE		btGoalCnt;	
}PMSG_DOPPELGANGER_MONSTER_GOAL, * LPPMSG_DOPPELGANGER_MONSTER_GOAL;

#endif	// YDG_ADD_DOPPELGANGER_PROTOCOLS

#ifdef PBG_ADD_SECRETBUFF
//----------------------------------------------------------------------------
// GC [0xBF][0x15] �Ƿε��� �ۼ�Ʈ
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2 h;
	BYTE		btFatiguePercentage;
}PMSG_FATIGUEPERCENTAGE, * LPPMSG_FATIGUEPERCENTAGE;
#endif //PBG_ADD_SECRETBUFF


#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
//----------------------------------------------------------------------------
// GC [0xBF][0x20] �κ����� ������ ���
// btResult: 1-����, 2-����
//----------------------------------------------------------------------------
typedef struct _tagPMSG_ANS_INVENTORY_EQUIPMENT_ITEM
{
	PBMSG_HEADER2	h;
	
	BYTE	btItemPos;		// ������ ��ġ
	BYTE	btResult;		// ������ ���� �����
} PMSG_ANS_INVENTORY_EQUIPMENT_ITEM, *LPPMSG_ANS_INVENTORY_EQUIPMENT_ITEM;
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY

#ifdef YDG_MOD_PROTECT_AUTO_V5
//----------------------------------------------------------------------------
// GC[0x8A] ��ü �����ڿ��� �ش� ���α׷��� ��������� Ȯ�� ��I
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER	h;
	DWORD		dwKey;
	char		Filename[MAX_HACKTOOL_FILENAME_LENGTH];
}PMSG_REQ_HACKTOOL_STATISTICS, *LPPMSG_REQ_HACKTOOL_STATISTICS;
#endif	// YDG_MOD_PROTECT_AUTO_V5

#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
//----------------------------------------------------------------------------
// GC[0x8E][0x01] �� �̵� äũ�� �����͸� �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	DWORD		dwKeyValue;
}PMSG_MAPMOVE_CHECKSUM, *LPPMSG_MAPMOVE_CHECKSUM;

//----------------------------------------------------------------------------
// GC[0x8E][0x03] Ŭ���̾�Ʈ�� �� �̵� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2	h;
	BYTE		btResult;		
}PMSG_ANS_MAPMOVE, *LPPMSG_ANS_MAPMOVE;
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

#ifdef LDK_ADD_EMPIREGUARDIAN_PROTOCOLS
//----------------------------------------------------------------------------
// GC [0xF7][0x02] ���� ��ȣ���� ���� ��û ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		Result;		/* ��û��� (0 : ����, 1 : �̹� ���� ������, 2 : ����Ʈ �������� �����ϴ�.)*/
	BYTE		Day;			/* ���ϸ� (1:��, 2:��, 3:ȭ, 4:��, 5:��, 6:��, 7:��)*/
	BYTE		Zone;			/* ����ȣ (�� 1, 2, 3)*/
	BYTE		Wheather;		/* ���� (0:����, 1:��, 2:�Ȱ�, 3:��+����)*/
	DWORD		RemainTick;		// Result���� 1�ϰ�� ��� �ð����� �������
} PMSG_RESULT_ENTER_EMPIREGUARDIAN, *LPPMSG_RESULT_ENTER_EMPIREGUARDIAN;

//----------------------------------------------------------------------------
// GC [0xF7][0x04] ���� ��ȣ���� �ð� ���� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		Type;			/* ��û��� (0 : ���, 1 : ����, 2 : Ÿ�Ӿ���)*/
	DWORD		RemainTick;		// ���, ���� Ÿ�� ���� �ð��� �˷���.
	BYTE		MonsterCount;	// ���� ���� ��
} PMSG_REMAINTICK_EMPIREGUARDIAN, *LPPMSG_REMAINTICK_EMPIREGUARDIAN;

//----------------------------------------------------------------------------
// GC [0xF7][0x06] ���� ��ȣ���� Ÿ�Ӿ��� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2	h;
	BYTE		Result;			/* ��û��� (0 : ����, 1 : ���� �� ����, 2 : ��� �� ����)*/
	DWORD		Exp;			// result���� 2�ϰ�� ����ġ ���� �������
} PMSG_CLEAR_RESULT_EMPIREGUARDIAN, *LPPMSG_CLEAR_RESULT_EMPIREGUARDIAN;
#endif //LDK_ADD_EMPIREGUARDIAN_PROTOCOLS

// �ΰ��Ӽ�
//////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ - �������� ĳ���� ���� ��������
//////////////////////////////////////////////////////////////////////////
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#pragma pack(push, 1)

//----------------------------------------------------------------------------
// ������� ĳ�� ����Ʈ ���� ��û (0xD2)(0x01)
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEADER2		h;
}PMSG_CASHSHOP_CASHPOINT_REQ, *LPPMSG_CASHSHOP_CASHPOINT_REQ;

//----------------------------------------------------------------------------
// ������� ĳ�� ����Ʈ ���� ���� (0xD2)(0x01)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				btViewType;

	double				dTotalCash;
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	double				dCashCredit;		// C (CreditCard)
	double				dCashPrepaid;		// P (PrepaidCard)
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	double				dTotalPoint;
	double				dTotalMileage;
}PMSG_CASHSHOP_CASHPOINT_ANS, *LPPMSG_CASHSHOP_CASHPOINT_ANS;

//----------------------------------------------------------------------------
// ĳ���� Open/Close ��û (0xD2)(0x02)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byShopOpenType;				// �� �������̽� ���� Ÿ�� ( 0 : ����, 1 : �ݱ� )
}PMSG_CASHSHOP_SHOPOPEN_REQ, *LPPMSG_CASHSHOP_SHOPOPEN_REQ;

//----------------------------------------------------------------------------
// ĳ���� Open ��� (0xD2)(0x02)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byShopOpenResult;		// �� �������̽� ��� ( 0 : ����, 1 : ���� )
}PMSG_CASHSHOP_SHOPOPEN_ANS, *LPPMSG_CASHSHOP_SHOPOPEN_ANS;

//----------------------------------------------------------------------------
// ������ ���� ��û (0xD2)(0x03)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	
	long				lBuyItemPackageSeq;		// ���� ��ǰ ���� (��Ű�� �ε���)
	long				lBuyItemDisplaySeq;		// ���� ���� ���� (���û�ǰ �ε���)
	long				lBuyItemPriceSeq;		// ���� ����
	WORD				wItemCode;				// ������ ������ �ڵ�
}PMSG_CASHSHOP_BUYITEM_REQ, *LPPMSG_CASHSHOP_BUYITEM_REQ;

//----------------------------------------------------------------------------
// ������ ���� ��� (0xD2)(0x03)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byResultCode;			// ������ ���� ��� (���Ű���ڵ� ����)
	long				lItemLeftCount;			// ������ �Ǹ� �ܿ� ���� (������Ʈ)
}PMSG_CASHSHOP_BUYITEM_ANS, *LPPMSG_CASHSHOP_BUYITEM_ANS;

//----------------------------------------------------------------------------
// ������ ���� ��û (0xD2)(0x04)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lGiftItemPackageSeq;				// ���� ������ ���� ��ǰ ����
	long				lDiftItemDisplaySeq;				// ���� ���� ����
	long				lGiftItemPriceSeq;					// ���� ������ ���� ����
	long				lSaleZone;							// �Ǹ� ����
	// ����� ���̵� �ʿ�
	char				chReceiveUserID[MAX_ID_SIZE+1];
	char				chMessage[MAX_GIFT_MESSAGE_SIZE];
}PMSG_CASHSHOP_GIFTSEND_REQ, *LPPMSG_CASHSHOP_GIFTSEND_REQ;

//----------------------------------------------------------------------------
// ������ ���� ��� (0xD2)(0x04)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byResultCode;
	long				lItemLeftCount;
	double				dLimitedCash;
}PMSG_CASHSHOP_GIFTSEND_ANS, *LPPMSG_CASHSHOP_GIFTSEND_ANS;

//----------------------------------------------------------------------------
// ������ ����Ʈ ��û (0xD2)(0x05)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	int					iPageIndex;						// ��û ������ �ε���
	char				chStorageType;					// ������ Ÿ�� ( S : ���� ������, G : ������, A : ��ü)
#endif// KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}PMSG_CASHSHOP_STORAGELIST_REQ, *LPPMSG_CASHSHOP_STORAGELIST_REQ;

//----------------------------------------------------------------------------
// ������ ����Ʈ ī��Ʈ ���� (0xD2)(0x06)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	WORD				wTotalItemCount;				// ������ ��ü ������ ī��Ʈ
	WORD				wCurrentItemCount;				// ���� ������ ������ ����
	WORD				wPageIndex;						// ���� ������ �ε���
	WORD				wTotalPage;						// ��ü ������ ī��Ʈ
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	WORD				wItemCount;					// ������/������ ī��Ʈ
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
}PMSG_CASHSHOP_STORAGECOUNT, *LPPMSG_CASHSHOP_STORAGECOUNT;

//----------------------------------------------------------------------------
// ������ ����Ʈ ���� (0xD2)(0x0D)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lStorageIndex;
	long				lItemSeq;
	long				lStorageGroupCode;
	long				lProductSeq;
	long				lPriceSeq;
	double				dCashPoint;
	char				chItemType;
}PMSG_CASHSHOP_STORAGELIST, *LPPMSG_CASHSHOP_STORAGELIST;

//----------------------------------------------------------------------------
// ������ ������ ����Ʈ ���� (0xD2)(0x0E)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	
	long				lStorageIndex;
	long				lItemSeq;
	long				lStorageGroupCode;
	long				lProductSeq;
	long				lPriceSeq;
	double				dCashPoint;
	char				chItemType;

	char				chSendUserName[MAX_ID_SIZE+1];
	char				chMessage[MAX_GIFT_MESSAGE_SIZE];
}PMSG_CASHSHOP_GIFTSTORAGELIST, *LPPMSG_CASHSHOP_GIFTSTORAGELIST;

//----------------------------------------------------------------------------
// ĳ������ ��û (0xD2)(0x07)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	double				dCashValue;

	char				chReceiveUserID[MAX_ID_SIZE+1];
	char				chMessage[MAX_GIFT_MESSAGE_SIZE];
}PMSG_CASHSHOP_CASHSEND_REQ, *LPPMSG_CASHSHOP_CASHSEND_REQ;

//----------------------------------------------------------------------------
// ĳ������ ��� (0xD2)(0x07)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	double				dGiftCashLimit;
	BYTE				byResultCode;
}PMSG_CASHSHOP_CASHSEND_ANS, *LPPMSG_CASHSHOP_CASHSEND_ANS;

//----------------------------------------------------------------------------
// �ش� ����ڰ� ��ǰ�� ����/������ �������� Ȯ�� ��û (0xD2)(0x08)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
}PMSG_CASHSHOP_ITEMBUY_CONFIRM_REQ, *LPPMSG_CASHSHOP_ITEMBUY_CONFIRM_REQ;

//----------------------------------------------------------------------------
// �ش� ����ڰ� ��ǰ�� ����/������ �������� Ȯ�� ��� (0xD2)(0x08)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	double				dPresentedCash;					// �Ѵ� ���� ������ ĳ�� �հ�
	double				dPresenteLimitCash;				// �Ѵ� ���� ���� ������ ĳ�� �հ�

	BYTE				byResult;
	BYTE				byItemBuyPossible;				// ������ ���� ���� ���� ( 0 : �Ұ�, 1 : ���� )
	BYTE				byPresendPossible;				// ������ ���� ���� ���� ( 0 : �Ұ�, 1 : ���� )
}PMSG_CASHSHOP_ITEMBUY_CONFIRM_ANS, *LPPMSG_CASHSHOP_ITEMBUY_CONFIRM_ANS;

//----------------------------------------------------------------------------
// ��ǰ �ܿ� ���� ��ȸ ��û (0xD2)(0x09)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lPackageSeq;					// ���û�ǰ �ڵ�
}PMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_REQ, *LPPMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_REQ;

//----------------------------------------------------------------------------
// ��ǰ �ܿ� ���� ��ȸ ��� (0xD2)(0x09)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lPackageSeq;					// ���û�ǰ ����
	long				lLeftCount;						// �ܿ� ����
}PMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_ANS, *LPPMSG_CASHSHOP_ITEMBUY_LEFT_COUNT_ANS;

//----------------------------------------------------------------------------
// ������ ������ ������ ��û (0xD2)(0x0A)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lStorageSeq;					// ������ ����
	long				lStorageItemSeq;				// ������ ��ǰ ����
	char				chStorageItemType;				// ��ǰ ���� ( C : ĳ��, P : ��ǰ )
}PMSG_CASHSHOP_STORAGE_ITEM_THROW_REQ, *LPPMSG_CASHSHOP_STORAGE_ITEM_THROW_REQ;

//----------------------------------------------------------------------------
// ������ ������ ������ ��� (0xD2)(0x0A)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byResult;						// ��� �ڵ� ( 0 : ����, 1 : ������ ������ �׸��� ����, -1 : ���� �߻�, -2 : DB ���� ���� )
}PMSG_CASHSHOP_STORAGE_ITEM_THROW_ANS, *LPPMSG_CASHSHOP_STORAGE_ITEM_THROW_ANS;

//----------------------------------------------------------------------------
// ������ ������ ��� ��û (0xD2)(0x0B)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	long				lStorageSeq;					// ������ ����
	long				lStorageItemSeq;				// ������ ��ǰ ����

	WORD				wItemCode;						// ����� �������� ������ �ڵ�
	char				chStorageItemType;				// ��ǰ ���� ( C : ĳ��, P : ��ǰ )
}PMSG_CASHSHOP_STORAGE_ITEM_USE_REQ, *LPPMSG_CASHSHOP_STORAGE_ITEM_USE_REQ;

//----------------------------------------------------------------------------
// ������ ������ ��� ��� (0xD2)(0x0B)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;

	BYTE				byResult;						// ��� �ڵ�
}PMSG_CASHSHOP_STORAGE_ITEM_USE_ANS, *LPPMSG_CASHSHOP_STORAGE_ITEM_USE_ANS;

//----------------------------------------------------------------------------
// ������ ����Ʈ ���� ������Ʈ (0xD2)(0x0C)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	
	WORD				wSaleZone;
	WORD				wYear;
	WORD				wYearIdentify;
}PMSG_CASHSHOP_VERSION_UPDATE, *LPPMSG_CASHSHOP_VERSION_UPDATE;

//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ ��û (0xD2)(0x13)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2			h;
	
	long				lEventCategorySeq;			// ���� �̺�Ʈ ī�װ� Sequence
}PMSG_CASHSHOP_EVENTITEM_REQ, *LPPMSG_CASHSHOP_EVENTITEM_REQ;


//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ ī��Ʈ (0xD2)(0x13)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2			h;
	
	WORD				wEventItemListCount;						// ��ü ������ ����Ʈ ī��Ʈ
}PMSG_CASHSHOP_EVENTITEM_COUNT, *LPPMSG_CASHSHOP_EVENTITEM_COUNT;


//----------------------------------------------------------------------------
// �̺�Ʈ ������ ����Ʈ (0xD2)(0x14)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2			h;
	
	long				lPackageSeq[INGAMESHOP_DISPLAY_ITEMLIST_SIZE];			// �̺�Ʈ ������ ����Ʈ�� 9�� ������ ������.
}PMSG_CASHSHOP_EVENTITEM_LIST, *LPPMSG_CASHSHOP_EVENTITEM_LIST;

//----------------------------------------------------------------------------
// ��� ���� ������Ʈ (0xD2)(0x15)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2			h;
	
	WORD				wBannerZone;
	WORD				wYear;
	WORD				wYearIdentify;
}PMSG_CASHSHOP_BANNER_UPDATE, *LPPMSG_CASHSHOP_BANNER_UPDATE;

#pragma pack(pop)

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM


#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM

//----------------------------------------------------------------------------
// �Ⱓ�� ������ ����Ʈ ī��Ʈ (0xD2)(0x11)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	
	BYTE				byPeriodItemCount;				// �Ⱓ�� ������ ī��Ʈ
}PMSG_PERIODITEMEX_ITEMCOUNT, *LPPMSG_PERIODITEMEX_ITEMCOUNT;


//----------------------------------------------------------------------------
// �Ⱓ�� ������ ����Ʈ (0xD2)(0x12)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	
	WORD				wItemCode;						// ������ �ڵ�
	WORD				wItemSlotIndex;					// ������ ���� �ε���
	long				lExpireDate;					// ����ð� (CTime���� ���)
}PMSG_PERIODITEMEX_ITEMLIST, *LPPMSG_PERIODITEMEX_ITEMLIST;

#endif // KJH_ADD_PERIOD_ITEM_SYSTEM

#ifdef PBG_MOD_GAMEGUARD_HANDLE
//----------------------------------------------------------------------------
// ?????????
//----------------------------------------------------------------------------
typedef struct  
{
	PBMSG_HEADER2		h;
	WORD				wCharInfo;
}PMSG_GAMEGUARD_HADLE, *LPPMSG_GAMEGUARD_HADLE;
#endif //PBG_MOD_GAMEGUARD_HANDLE

#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL
//----------------------------------------------------------------------------
// ���� �������� �ʱ�ȭ (0x8D)(0x05)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEADER2		h;
	DWORD				dwDummySeedValue;
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	DWORD				dwAttackSerialSeedValue;
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
}PMSG_SET_ATTACK_PROTOCOL_DUMMY_VALUE, *LPPMSG_SET_ATTACK_PROTOCOL_DUMMY_VALUE;
#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
//----------------------------------------------------------------------------
// ������������ ��ų0x4A
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEADER  Header;
	BYTE          AttackH;
	BYTE          AttackL;
	BYTE          SourceKeyH;
	BYTE          SourceKeyL;
	BYTE          TargetKeyH;
	BYTE          TargetKeyL;
} PRECEIVE_STRAIGHTATTACK, * LPPRECEIVE_STRAIGHTATTACK;
//----------------------------------------------------------------------------
// Ÿ���ε�����û0x4B
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEADER Header;
	WORD		 MagicNumber;
	WORD		 TargerIndex[DARKSIDE_TARGET_MAX];
} PRECEIVE_DARKSIDE_INDEX, * LPPRECEIVE_DARKSIDE_INDEX;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
//////////////////////////////////////////////////////////////////////////
// ?????????????????????????????????????
//////////////////////////////////////////////////////////////////////////
extern CWsctlc SocketClient;
extern int HeroKey;

extern int SummonLife;
extern int SendGetItem;
extern int SendDropItem;

extern bool EnableGuildWar;
extern int  GuildWarIndex;
extern char GuildWarName[8+1];
extern int  GuildWarScore[2];

extern bool EnableSoccer;
extern BYTE HeroSoccerTeam;
extern int  SoccerTime;
extern char SoccerTeamName[2][8+1];
extern bool SoccerObserver;

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
extern CSessionCryptor g_SessionCryptorCS;
extern CSessionCryptor g_SessionCryptorSC;
#else
extern CSimpleModulus g_SimpleModulusCS;
extern CSimpleModulus g_SimpleModulusSC;
#endif // PKD_ADD_ENHANCED_ENCRYPTION

#ifdef ACC_PACKETSIZE
extern int g_iTotalPacketRecv;
extern int g_iTotalPacketSend;
extern DWORD g_dwPacketInitialTick;
#endif //ACC_PACKETSIZE


BOOL CreateSocket(char *IpAddr, unsigned short Port);
void DeleteSocket();
void ProtocolCompiler( CWsctlc *pSocketClient = &SocketClient, int iTranslation = 0, int iParam = 0);


void InitGame ();
void InitGuildWar();


bool Check_Switch (PRECEIVE_CROWN_SWITCH_INFO *Data);
bool Delete_Switch();

typedef struct _CROWN_SWITCH_INFO
{
	BYTE				m_bySwitchState;
	BYTE				m_JoinSide;
	BYTE				m_szGuildName[9];
	BYTE				m_szUserName[MAX_ID_SIZE+1];

	_CROWN_SWITCH_INFO()
	{
		Reset();	
	}

	void Reset()
	{
		m_bySwitchState = 0;
		m_JoinSide = 0;
		ZeroMemory(m_szGuildName, sizeof(m_szGuildName));
		ZeroMemory(m_szUserName, sizeof(m_szUserName));
	}
} CROWN_SWITCH_INFO;
extern CROWN_SWITCH_INFO *Switch_Info;

extern MASTER_LEVEL_VALUE	Master_Level_Data;
#endif
