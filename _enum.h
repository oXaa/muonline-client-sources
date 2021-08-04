#pragma once

#ifdef KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE
#include "_define.h"
#endif // KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE

namespace SEASON3A
{
	enum eCursedTempleState
	{
		eCursedTempleState_None = 0,
		eCursedTempleState_Wait,
		eCursedTempleState_Ready,
		eCursedTempleState_Play,
		eCursedTempleState_End,
	};
	
	enum eCursedTempleTeam
	{
		eTeam_Allied = 0,      // ���ձ�
		eTeam_Illusion,        // ȯ������
		eTeam_Count,
	};
};

namespace SEASON3B
{
	enum INTERFACE_LIST
	{
		INTERFACE_BEGIN = 0x00,

		INTERFACE_FRIEND,					// ģ��â
		INTERFACE_MOVEMAP,					// ���̵�â
		INTERFACE_PARTY,					// ��Ƽ����â
		INTERFACE_MYQUEST,					// ����Ʈ����â
		INTERFACE_NPCQUEST,					// NPC����Ʈâ
		INTERFACE_GUILDINFO,				// �������â
		INTERFACE_TRADE,					// �ŷ�â
		INTERFACE_STORAGE,					// â��â
		INTERFACE_MIXINVENTORY,				// ����â
		INTERFACE_COMMAND,					// Ŀ�ǵ�â
		INTERFACE_PET,						// ������â
		INTERFACE_NPCSHOP,					// NPC����â
		INTERFACE_INVENTORY,				// �κ��丮â
		INTERFACE_MYSHOP_INVENTORY,			// ���λ�������â
		INTERFACE_PURCHASESHOP_INVENTORY,	// ���λ�������â
		INTERFACE_CHARACTER,				// ĳ��������â
		INTERFACE_NPCBREEDER,	
		INTERFACE_SERVERDIVISION,
		INTERFACE_DEVILSQUARE,			
		INTERFACE_BLOODCASTLE,

		INTERFACE_NPCGUILDMASTER,
		INTERFACE_GUARDSMAN,
		INTERFACE_SENATUS,
		INTERFACE_GATEKEEPER,
		INTERFACE_GATESWITCH,
		INTERFACE_CATAPULT,
		INTERFACE_REFINERY,
		INTERFACE_REFINERYINFO,
		INTERFACE_KANTURU2ND_ENTERNPC,
		INTERFACE_CURSEDTEMPLE_NPC,
		INTERFACE_CURSEDTEMPLE_GAMESYSTEM,
		INTERFACE_CURSEDTEMPLE_RESULT,
		INTERFACE_CHATINPUTBOX,
		INTERFACE_WINDOW_MENU,
		INTERFACE_OPTION,
		INTERFACE_HELP,
		INTERFACE_ITEM_EXPLANATION,
		INTERFACE_SETITEM_EXPLANATION,
		INTERFACE_QUICK_COMMAND,

		INTERFACE_KANTURU_INFO,				// ĭ���� �̺�Ʈ ����
		INTERFACE_CHATLOGWINDOW,			// ä�� �α� 
		INTERFACE_PARTY_INFO_WINDOW,		// �̴� ��Ƽ����Ʈ â
		INTERFACE_BLOODCASTLE_TIME,			// ����ĳ�� Time Window UI
		INTERFACE_CHAOSCASTLE_TIME,			// ī����ĳ�� Time Window UI
		INTERFACE_BATTLE_SOCCER_SCORE,		// ��Ʋ ��Ŀ ���� UI		
		INTERFACE_SLIDEWINDOW,				// �����̵�â
		INTERFACE_HERO_POSITION_INFO,		// ���ΰ���ǥâ
		INTERFACE_MESSAGEBOX,				// �޼����ڽ�â
		INTERFACE_DUEL_WINDOW,				// ���� ���� â
		INTERFACE_CRYWOLF,					// ũ���̿��� ����â
		INTERFACE_NAME_WINDOW,				// ���� �̸�, NPC �̸��� �̸� ǥ�� â
		INTERFACE_SIEGEWARFARE,				// ������ UI
		INTERFACE_MAINFRAME,				// ����������â
		INTERFACE_SKILL_LIST,				// ���������� - ��ų����Ʈ
		INTERFACE_ITEM_ENDURANCE_INFO,		// ������ ���������� UI
		INTERFACE_BUFF_WINDOW,				// ���� ���� ǥ�� ������
#ifdef NEW_USER_INTERFACE_UISYSTEM
		INTERFACE_PARTCHARGE_SHOP,			// �κ� ����ȭ ���� â
#endif //NEW_USER_INTERFACE_UISYSTEM
		INTERFACE_MASTER_LEVEL,				// ������ ���� ��ų â
#ifdef PSW_GOLDBOWMAN
		INTERFACE_GOLD_BOWMAN,
#endif //PSW_GOLDBOWMAN
#ifdef PSW_EVENT_LENA		
		INTERFACE_GOLD_BOWMAN_LENA,
#endif //PSW_EVENT_LENA
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
		INTERFACE_LUCKYCOIN_REGISTRATION,	// ����� ���� ���â
		INTERFACE_EXCHANGE_LUCKYCOIN,		// ����� ���� ��ȯâ
#endif // KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_NEW_DUEL_UI
		INTERFACE_DUELWATCH,				// ������ ������ ���� ä�μ��� UI
#endif	// YDG_ADD_NEW_DUEL_UI
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
		INTERFACE_DUELWATCH_MAINFRAME,		// ���� ���� ���� ���� ������
		INTERFACE_DUELWATCH_USERLIST,		// ���� ���� ä�� ���� ����Ʈ
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
#ifdef PBG_ADD_INGAMESHOP_UI_ITEMSHOP
		INTERFACE_INGAMESHOP,
#endif //PBG_ADD_INGAMESHOP_UI_ITEMSHOP
#ifdef YDG_ADD_DOPPELGANGER_UI
		INTERFACE_DOPPELGANGER_NPC,			// ���ð��� NPC
		INTERFACE_DOPPELGANGER_FRAME,		// ���ð��� ȭ�� UI
#endif	// YDG_ADD_DOPPELGANGER_UI
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		INTERFACE_QUEST_PROGRESS,			// �ű� ����Ʈ ���� â(NPC�� ����)
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#ifdef ASG_ADD_UI_NPC_MENU
		INTERFACE_NPC_MENU,					// NPC �޴� â(NPC�� Ŭ���ϸ� ����Ʈ�� ������ ����Ʈ�� ���� ����Ʈ ���� ���� ������ â)
#endif	// ASG_ADD_UI_NPC_MENU
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		INTERFACE_QUEST_PROGRESS_ETC,		// �ű� ����Ʈ ���� â(��Ÿ������� ����)
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC
#ifdef LDK_ADD_EMPIREGUARDIAN_UI
		INTERFACE_EMPIREGUARDIAN_NPC,		// ���� ��ȣ�� npc
		INTERFACE_EMPIREGUARDIAN_TIMER,		// ���� ��ȣ�� ui
#endif //LDK_ADD_EMPIREGUARDIAN_UI
#ifdef PJH_ADD_MINIMAP
		INTERFACE_MINI_MAP,
#endif //PJH_ADD_MINIMAP
#ifdef ASG_ADD_UI_NPC_DIALOGUE
		INTERFACE_NPC_DIALOGUE,				// NPC ��ȭ â(NPC�� Ŭ���ϸ� �ߴ� NPC�� ��ȭ ������ â���� ����Ʈ ���� ���� ������ â)
#endif	// ASG_ADD_UI_NPC_DIALOGUE
#ifdef PBG_MOD_STAMINA_UI
		INTERFACE_STAMINA_GAUGE,			// ���׹̳� ������
#endif //PBG_MOD_STAMINA_UI
#ifdef PBG_ADD_GENSRANKING
		INTERFACE_GENSRANKING,				// �ս���ŷ
#endif //PBG_ADD_GENSRANKING
#ifdef LDS_ADD_UI_UNITEDMARKETPLACE
		INTERFACE_UNITEDMARKETPLACE_NPC_JULIA,	// ���ս��� �ٸ��� (���ս������� ���� �뱸)
#endif // LDS_ADD_UI_UNITEDMARKETPLACE

#ifdef LEM_ADD_LUCKYITEM					// ��Ű������ NPC�������̽� enum ���.
		INTERFACE_LUCKYITEMWND,
#endif // LEM_ADD_LUCKYITEM
		/* UI �ý��� �������̽� */
		INTERFACE_HOTKEY,
		INTERFACE_3DRENDERING_CAMERA_BEGIN,
		INTERFACE_3DRENDERING_CAMERA_END = INTERFACE_3DRENDERING_CAMERA_BEGIN + 24, 
		INTERFACE_ITEM_TOOLTIP,	
		INTERFACE_END,
		INTERFACE_COUNT = INTERFACE_END-2,
	};
}

namespace info
{
	enum InfoTextType
	{
		eInfo_Text_File = 0,
		eInfo_Item_File,
		eInfo_Skill_File,
		eInfo_Slide_File,
		eInfo_Dialog_File,
		eInfo_Credit_File,
		eInfo_Filter_File,
		eInfo_FilterName_File,
		eInfo_MonsterSkill_File,
		eInfo_Movereq_File,
		eInfo_Quest_File,
		eInfo_ItemSetType_File,
		eInfo_ItemSetOption_File,
		eInfo_NpcName_File,
		eInfo_JewelOfHarmonyOption_File,
		eInfo_JewelOfHarmonySmelt_File,
		eInfo_ItemAddOption_File,
		eInfo_File_Count,
	};
};

//scene start
enum ENUM_MUSIC
{
	MUSIC_PUB = 0,
	MUSIC_MUTHEME,
	MUSIC_CHURCH,
	MUSIC_DEVIAS,
	MUSIC_NORIA,
	MUSIC_DUNGEON,
	MUSIC_ATLANS,
	MUSIC_ICARUS,
	MUSIC_TARKAN,
	MUSIC_LOSTTOWER_A,
	MUSIC_LOSTTOWER_B,
	MUSIC_KALIMA,
	MUSIC_CASTLE_PEACE,
	MUSIC_CASTLE_BATTLE_START,
	MUSIC_CASTLE_BATTLE_ING,
	MUSIC_BC_HUNTINGGROUND,
	MUSIC_BC_ADIA,
	MUSIC_BC_CRYWOLF_1ST,
	MUSIC_CRYWOLF_READY,	// ũ���̿��� �غ� ��Ȳ���� ����
	MUSIC_CRYWOLF_BEFORE,	// ũ���̿��� ����2 ��Ȳ(����)���� ����
	MUSIC_CRYWOLF_BACK,		// ũ���̿��� �������϶� ����
	MUSIC_MAIN_THEME,
	MUSIC_KANTURU_1ST,
	MUSIC_KANTURU_2ND,
	MUSIC_KANTURU_MAYA_BATTLE,
	MUSIC_KANTURU_NIGHTMARE_BATTLE,
	MUSIC_KANTURU_TOWER,
	MUSIC_BALGAS_BARRACK,
	MUSIC_BALGAS_REFUGE,
	MUSIC_CURSEDTEMPLE_WAIT,
	MUSIC_CURSEDTEMPLE_GAME,
	MUSIC_ELBELAND,			// �������� ����
	MUSIC_LOGIN_THEME,		// ���ο� �α��� ����
	MUSIC_SWAMP_OF_QUIET,	// ����� �� ����
#ifdef CSK_ADD_MAP_ICECITY	
	MUSIC_RAKLION,			// ��Ŭ���� ����
	MUSIC_RAKLION_BOSS,		// ��Ŭ���� ���� ����
#endif // CSK_ADD_MAP_ICECITY
#ifdef YDG_ADD_MAP_SANTA_TOWN
	MUSIC_SANTA_TOWN,		// ��Ÿ���� ����
#endif	// YDG_ADD_MAP_SANTA_TOWN
#ifdef YDG_ADD_MAP_DUEL_ARENA
	MUSIC_DUEL_ARENA,		// ������ ����
#endif	// YDG_ADD_MAP_DUEL_ARENA
#ifdef PBG_ADD_PKFIELD
	MUSIC_PKFIELD,
#endif //PBG_ADD_PKFIELD
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN1
	MUSIC_EMPIREGUARDIAN1,	// ���� ��ȣ�� ��1 (��, �� ���ϸ�) ����
#endif //LDK_ADD_MAP_EMPIREGUARDIAN1
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN2
	MUSIC_EMPIREGUARDIAN2,	// ���� ��ȣ�� ��2 (ȭ, �� ���ϸ�) ����
#endif // LDS_ADD_MAP_EMPIREGUARDIAN2
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN3
	MUSIC_EMPIREGUARDIAN3,	// ���� ��ȣ�� ��3 (��, �� ���ϸ�) ����
#endif //LDK_ADD_MAP_EMPIREGUARDIAN3
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN4
	MUSIC_EMPIREGUARDIAN4,	// ���� ��ȣ�� ��4 (�� �ָ���) ����
#endif // LDS_ADD_MAP_EMPIREGUARDIAN4
#ifdef YDG_ADD_DOPPELGANGER_SOUND
	MUSIC_DOPPELGANGER,		// ���ð��� ����
#endif	// YDG_ADD_DOPPELGANGER_SOUND
#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
	MUSIC_UNITEDMARKETPLACE,
#endif // LDS_ADD_MAP_UNITEDMARKETPLACE
#ifdef ASG_ADD_MAP_KARUTAN
	MUSIC_KARUTAN1,			// Į��ź ��1 ����
	MUSIC_KARUTAN2,			// Į��ź ��2 ����
#endif	// ASG_ADD_MAP_KARUTAN
	NUM_MUSIC
};

enum
{
	MESSAGE_FREE_MSG_NOT_BTN	= 91,
	MESSAGE_GAME_END_COUNTDOWN		,
	MESSAGE_WAIT				= 93,
	MESSAGE_DELETE_CHARACTER_CONFIRM,
	MESSAGE_DELETE_CHARACTER_RESIDENT,
	MESSAGE_DELETE_CHARACTER_SUCCESS,
	MESSAGE_DELETE_CHARACTER_ID_BLOCK,
	MESSAGE_DELETE_CHARACTER_ITEM_BLOCK,
	MESSAGE_SERVER_BUSY,
	MESSAGE_INPUT_ID              = 100,
	MESSAGE_INPUT_PASSWORD        ,
	MESSAGE_INPUT_CONFIRM         ,
	MESSAGE_INPUT_QUIZ            ,
	MESSAGE_INPUT_ANSWER          ,
	MESSAGE_INPUT_NAME            ,
	MESSAGE_INPUT_RESIDENT_NUMBER ,
	MESSAGE_INPUT_PHONE           ,
	MESSAGE_INPUT_EMAIL           ,
	MESSAGE_PASSWORD              ,
	MESSAGE_LOG_OUT               ,	//(110)		// Custom
	MESSAGE_VERSION               ,				// ����� 
	MESSAGE_SERVER_LOST		      ,				// �����
	MESSAGE_DELETE_CHARACTER      ,				// ���� ��� ����.
	MESSAGE_ID_SPACE_ERROR        ,
	MESSAGE_INPUT_GOLD            ,
	MESSAGE_NOT_ENOUGH_GOLD       ,
	MESSAGE_OVERFLOW_GOLD         ,
	MESSAGE_GUILD                 ,
	MESSAGE_PARTY                 ,
	MESSAGE_TRADE                 ,	//(120)
	MESSAGE_MIN_LENGTH            ,
	MESSAGE_SPECIAL_NAME          ,
	MESSAGE_RESIDENT_NUMBER_ERROR ,		// ���� ��� ����.
	MESSAGE_INPUT_GUILD           ,
	MESSAGE_DELETE_GUILD          ,
	MESSAGE_NO_GUILD_MARK         ,
	MESSAGE_GUILD_WAR             ,
	MESSAGE_HOMEPAGE1             ,
	MESSAGE_HOMEPAGE2             ,
	MESSAGE_HOMEPAGE3             ,	//(130)
	MESSAGE_DELETE_CHARACTER_WARNING ,
	MESSAGE_BLOCKED_CHARACTER	  ,
	MESSAGE_STORAGE_PASSWORDWRONG ,
	MESSAGE_STORAGE_ALREADYLOCKED ,
	MESSAGE_STORAGE_PASSWORDTOOSIMPLE ,
	MESSAGE_STORAGE_PASSWORDNOTMATCH  ,
	MESSAGE_STORAGE_RESIDENTWRONG ,
	MESSAGE_CUSTOM				  ,
	MESSAGE_DEVILSQUARERANK		  ,
	MESSAGE_SEMI_QUEST            ,	//(140)
	MESSAGE_DIALOG				  ,
	MESSAGE_SELECT_CHAOS		  ,
	MESSAGE_SERVER_IMMIGR_ERROR_RESIDENT,
	MESSAGE_SERVER_IMMIGR_ERROR_DB	    ,

	MESSAGE_PERSONALSHOP		  ,     //. Type 1 : ������ �Է�, Type 2 : �ǸŰ��� �Է�
	MESSAGE_DELETE_CHARACTER_GUILDWARNING,

	MESSAGE_OPTIONS               ,
	MESSAGE_TRADE_CHECK           ,
	MESSAGE_LOCK_STORAGE          ,
	MESSAGE_USE_STATE             ,	//(150)
	MESSAGE_BLOODCASTLE_RESULT    ,
	MESSAGE_CHECK                 ,
	MESSAGE_PERSONALSHOP_WARNING  ,

	MESSAGE_CHAOS_CASTLE_CHECK    ,     //  ī���� ĳ�� ���� üũ.
	MESSAGE_CHAOS_CASTLE_RESULT   ,     //  ī���� ĳ�� ���.
	MESSAGE_CUSTOM_MESSAGEBOX     ,
	MESSAGE_GEM_INTEGRATION		  ,		//	�༮ ����-��ü�� ���� �������̽�
	MESSAGE_GEM_INTEGRATION2	  ,
	MESSAGE_GEM_INTEGRATION3	  ,
	MESSAGE_GEM_INTEGRATION4	  ,	//(160)
	MESSAGE_GEM_INTEGRATION5	  ,
	MESSAGE_GEM_INTEGRATION6	  ,
	MESSAGE_WT_MATCH_RESULT       ,		// ��� ����� ǥ���ϴ� ���̾�α�
	MESSAGE_USE_STATE2			  ,		//: ���Ż�� �����Ұ��ΰ�? �����Ұ��ΰ�?
	MESSAGE_FENRIR_REPAIR		  ,		// �渱�� ���Ǹ��� �����Ͻðڽ��ϱ�?
	MESSAGE_CANCEL_SKILL		  ,		// ��ų�� ����ϴ� �޼���â!
#ifdef PCROOM_EVENT
	MESSAGE_PCROOM_EVENT		  ,		// (�̺�Ʈ�� ���� ��Ȯ��)
#endif	// PCROOM_EVENT
	MESSAGE_WHITEANGEL_EVENT	  ,	    // ȭ��Ʈ���� �̺�Ʈ	(�̺�Ʈ�� ���� ��Ȯ��)
#ifdef ADD_EXPERIENCE_SERVER
	MESSAGE_PCROOM_POSSIBLE		  ,		// PC�濡���� ������ �����մϴ�.	(�α��ν�)
#endif	// ADD_EXPERIENCE_SERVER
#ifdef PRUARIN_EVENT07_3COLORHARVEST
	MESSAGE_3COLORHARVEST_EVENT		,	// 07�⵵ 3Color & �߼� �̺�Ʈ
#endif // PRUARIN_EVENT07_3COLORHARVEST
#ifdef LDK_ADD_GLOBAL_PORTAL_SYSTEM
	MESSAGE_NOT_EXECUTION_WEBSTARTER	,	// ������ �α������ּ���. (����Ÿ�� �̽���)
#endif //LDK_ADD_GLOBAL_PORTAL_SYSTEM
#ifdef LJH_ADD_ONETIME_PASSWORD
	MESSAGE_OTP_NOT_REGISTERED		,	// OneTime Password �̵��
	MESSAGE_OTP_INCORRECT			,	// OneTime Password ����ġ 
	MESSAGE_OTP_NOT_WRITTEN			,	// OneTime Password ���Է� 
	MESSAGE_OTP_INVALID_INFO		,	// ��ȿ�Ⱓ�� ���� OneTime Password, �Ǵ� ��Ÿ ����
#endif //LJH_ADD_ONETIME_PASSWORD
};

/*
#define MESSAGE_GEM_INTEGRATION		  161	//	�ʱ� �˾�
#define MESSAGE_GEM_INTEGRATION2	  162	//	���� �� ����â
#define MESSAGE_GEM_INTEGRATION3	  163	//	Yes/No
#define MESSAGE_GEM_INTEGRATION4	  164	//	��ü �� ����â
#define MESSAGE_GEM_INTEGRATION5	  165	//	���â
#define MESSAGE_GEM_INTEGRATION6	  166	//  ���� ���
#define	MESSAGE_WT_MATCH_RESULT       167	// ��� ����� ǥ���ϴ� ���̾�α�
#define MESSAGE_USE_STATE2			  168	//: ���� ����/����
#define MESSAGE_FENRIR_REPAIR		  169	// �渱 ����
*/

//scene end

//infomation start
/*
enum
{
	STAMINA_WHEEL = 0,
	STAMINA_MULTI_USE,	// ���� ��ų�� �������� ����
	STAMINA_FURY_STRIKE,
	STAMINA_SWORDFORCE,
	STAMINA_VITALITY,
	STAMINA_COMBINATION,
	MAX_SKILL_STAMINAS
};
*/
enum
{
	SKILL_ABILITY_NONE = 0,
	SKILL_ABILITY_FIRE,
	SKILL_ABILITY_THUNDER,
	SKILL_ABILITY_ICE,
	SKILL_ABILITY_POSION,
	SKILL_ABILITY_EARTH,
	SKILL_ABILITY_WIND,
	SKILL_ABILITY_WATER
};

enum
{
	SKILL_USE_TYPE_NONE = 0,
	SKILL_USE_TYPE_MASTER,			// 1
	SKILL_USE_TYPE_BRAND,			// 2
	SKILL_USE_TYPE_MASTERLEVEL,		// 3
	SKILL_USE_TYPE_MASTERACTIVE,	// 4
};
//infomation end

//character start
enum
{
	CHARACTER_NONE = 0,
	CHARACTER_RENDER_OBJ,
	CHARACTER_ANIMATION
};

enum
{
	RENDER_TYPE_NONE = 0,
	RENDER_TYPE_ALPHA_BLEND,
	RENDER_TYPE_ALPHA_TEST,
	RENDER_TYPE_ALPHA_BLEND_MINUS,
	RENDER_TYPE_ALPHA_BLEND_OTHER,
};
//character end

//object start
enum
{
	//nature
	MODEL_WORLD_OBJECT       = 0,
	MODEL_TREE01             = 0,
	MODEL_GRASS01            = 20,
	MODEL_STONE01            = 30,
	//outside
	MODEL_STONE_STATUE01	 = 40,
	MODEL_STONE_STATUE02	 ,
	MODEL_STONE_STATUE03     ,
	MODEL_STEEL_STATUE       ,
	MODEL_TOMB01             ,
	MODEL_TOMB02             ,
	MODEL_TOMB03             ,
	MODEL_FIRE_LIGHT01  	 = 50,
	MODEL_FIRE_LIGHT02  	 ,
	MODEL_BONFIRE            ,
	MODEL_DUNGEON_GATE  	 = 55,
	MODEL_MERCHANT_ANIMAL01  ,
	MODEL_MERCHANT_ANIMAL02  ,
	MODEL_TREASURE_DRUM  	 ,
	MODEL_TREASURE_CHEST     ,
	MODEL_SHIP               ,
	//wall
	MODEL_STEEL_WALL01       = 65,
	MODEL_STEEL_WALL02       ,
	MODEL_STEEL_WALL03       ,
	MODEL_STEEL_DOOR         ,
	MODEL_STONE_WALL01       ,
	MODEL_STONE_WALL02       ,
	MODEL_STONE_WALL03       ,
	MODEL_STONE_WALL04       ,
	MODEL_STONE_WALL05       ,
	MODEL_STONE_WALL06       ,
	MODEL_MU_WALL01          ,
	MODEL_MU_WALL02          ,
	MODEL_MU_WALL03          ,
	MODEL_MU_WALL04          ,
	MODEL_BRIDGE    	     = 80,
	MODEL_FENCE01     	     ,
	MODEL_FENCE02     	     ,
	MODEL_FENCE03     	     ,
	MODEL_FENCE04     	     ,
	MODEL_BRIDGE_STONE	     ,
	//town
	MODEL_STREET_LIGHT   	 = 90,
	MODEL_CANNON01    	     ,
	MODEL_CANNON02    	     ,
	MODEL_CANNON03    	     ,
	MODEL_CURTAIN    	     = 95,
	MODEL_SIGN01             ,
	MODEL_SIGN02             ,
	MODEL_CARRIAGE01  	     ,
	MODEL_CARRIAGE02  	     ,
	MODEL_CARRIAGE03  	     ,
	MODEL_CARRIAGE04  	     ,
	MODEL_STRAW01 	         ,
	MODEL_STRAW02 	         ,
	MODEL_WATERSPOUT	     = 105,
	MODEL_WELL01 	         ,
	MODEL_WELL02 	         ,
	MODEL_WELL03 	         ,
	MODEL_WELL04 	         ,
	MODEL_HANGING            ,
	MODEL_STAIR              ,
	//house
	MODEL_HOUSE01            = 115,
	MODEL_HOUSE02            ,
	MODEL_HOUSE03            ,
	MODEL_HOUSE04            ,
	MODEL_HOUSE05            ,
	MODEL_TENT               ,
	MODEL_HOUSE_WALL01       ,
	MODEL_HOUSE_WALL02       ,
	MODEL_HOUSE_WALL03       ,
	MODEL_HOUSE_WALL04       ,
	MODEL_HOUSE_WALL05       ,
	MODEL_HOUSE_WALL06       ,
	MODEL_HOUSE_ETC01        ,
	MODEL_HOUSE_ETC02        ,
	MODEL_HOUSE_ETC03        ,
	MODEL_LIGHT01            = 130,
	MODEL_LIGHT02            ,
	MODEL_LIGHT03            ,
	MODEL_POSE_BOX           ,
	//bar
	MODEL_FURNITURE01	     = 140,
	MODEL_FURNITURE02	     ,
	MODEL_FURNITURE03	     ,
	MODEL_FURNITURE04	     ,
	MODEL_FURNITURE05	     ,
	MODEL_FURNITURE06	     ,
	MODEL_FURNITURE07	     ,
	MODEL_CANDLE        	 = 150,
	MODEL_BEER01        	 ,
	MODEL_BEER02        	 ,
	MODEL_BEER03        	 ,
	MODEL_HERO_CHAIR		 ,
	MODEL_HERO_GUARD		 ,
	MODEL_MURDERER_DOG		 ,
	MAX_WORLD_OBJECTS        = 160,
	//logo
	MODEL_LOGO   	         = MAX_WORLD_OBJECTS,
	MODEL_WAVEBYSHIP		 ,
	MODEL_MUGAME			 ,
	MODEL_LOGOSUN		     ,
	MODEL_CARD   	         ,
	MODEL_FACE   	         = MODEL_CARD   	         + 4,	// ĳ���� ���� ���� ���Ǵ� ĳ���� ��ݽ� ��.
	//animal
	MODEL_BIRD01			 = MODEL_FACE   	         + MAX_CLASS,

	MODEL_BUTTERFLY01		 ,
	MODEL_BAT01			     ,
	MODEL_RAT01		       	 ,
	MODEL_BUG01		         ,
	MODEL_FISH01			 ,
	MODEL_GHOST				 ,
	MODEL_DRAGON			 ,
	MODEL_LOGIN_WARP		 ,
	MODEL_CLOUD              = MODEL_FISH01			     + 9,
#ifdef TAMAJJANG
	MODEL_TAMAJJANG          ,
#endif //TAMAJJANG
	MODEL_CROW               ,
	MODEL_SHINE              ,
	MODEL_EAGLE				 ,		// �� ȿ�� ������
	MODEL_MAP_TORNADO		 ,		// �� ȿ�� ȸ����
	MODEL_GM_CHARACTER,				// GM ���Ź��� ��
	MODEL_XMAS_EVENT_CHA_SSANTA,	// ��Ÿ�Ҿƹ���
	MODEL_XMAS_EVENT_CHA_SNOWMAN,	// �����
	MODEL_XMAS_EVENT_CHA_DEER,		// �罿
	MODEL_XMAS_EVENT_CHANGE_GIRL,	// ũ�������� �̺�Ʈ ���Ű�
	MODEL_XMAS_EVENT_EARRING,		// ���Ű� �Ͱ���
	MODEL_XMAS_EVENT_ICEHEART,		// ������Ʈ
	MODEL_XMAS_EVENT_BOX,			// �ڽ�
	MODEL_XMAS_EVENT_CANDY,			// ĵ��
	MODEL_XMAS_EVENT_TREE,			// Ʈ��
	MODEL_XMAS_EVENT_SOCKS,			// �縻
	MODEL_NEWYEARSDAY_EVENT_BEKSULKI,			// �鼳��
	MODEL_NEWYEARSDAY_EVENT_CANDY,				// ����
	MODEL_NEWYEARSDAY_EVENT_HOTPEPPER_GREEN,	// û����
	MODEL_NEWYEARSDAY_EVENT_HOTPEPPER_RED,		// ȫ����
	MODEL_NEWYEARSDAY_EVENT_PIG,				// Ȳ�ݵ���
	MODEL_NEWYEARSDAY_EVENT_YUT,				// �� 
	MODEL_NEWYEARSDAY_EVENT_MONEY,				// ��
	
#ifdef PRUARIN_EVENT07_3COLORHARVEST
	MODEL_MOONHARVEST_GAM,			// ��
	MODEL_MOONHARVEST_SONGPUEN1,	// ����1 (���)
	MODEL_MOONHARVEST_SONGPUEN2,	// ����2 (���)
	MODEL_MOONHARVEST_MOON,			// ��
#endif // PRUARIN_EVENT07_3COLORHARVEST
	
	MODEL_LIGHTNING_ORB,			// ����Ʈ�׿��� ��ų�� ���̴� �������� ����Ʈ�� �߻���Ű�� ���� ���� ��Ÿ��(�𵨵���Ÿ�� ����)
	MODEL_CHAIN_LIGHTNING,			// ü�ζ���Ʈ�� ��ų (�𵨵���Ÿ ����)
	MODEL_ALICE_BUFFSKILL_EFFECT,	// �������� ��ų �� �� ��Ÿ���� �� ����Ʈ
	MODEL_ALICE_BUFFSKILL_EFFECT2,
	MODEL_ALICE_DRAIN_LIFE,			// �巹�� ������ (�𵨵���Ÿ ����)
#ifdef CSK_RAKLION_BOSS
	MODEL_RAKLION_BOSS_CRACKEFFECT,	// ��Ŭ���� ���� ����Ʈ�� �� �������� ����Ʈ
	MODEL_RAKLION_BOSS_MAGIC,		// ��Ŭ���� ���� ����Ʈ�� ������ ����Ʈ
#endif // CSK_RAKLION_BOSS
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
	MODEL_LIGHTNING_SHOCK,			// ����Ʈ�׼�ũ ��ų�� ���̴� �������� ����Ʈ�� �߻���Ű�� ���� ���� ��Ÿ��(�𵨵���Ÿ�� ����)
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
	MODEL_MOVE_TARGETPOSITION_EFFECT,

	//////////////////////////////////////////////////////////////////////////
	// MODEL_SKILL_BEGIN ~ MODEL_SKILL_END ������ OpenTexture() �Լ��� �ڵ� //
	// ���� ȣ��Ǿ AccessModel() �Լ��� ȣ���ϸ� ��!!!					//
	//////////////////////////////////////////////////////////////////////////
	
	//skill
	MODEL_SKILL_BEGIN  		 ,	
	MODEL_DARK_HORSE         ,  //  ��ũȣ��.
#ifdef PET_SYSTEM
	MODEL_DARK_SPIRIT        ,  //  ��ũ ���Ǹ�.
#endif// PET_SYSTEM
#ifdef DARK_WOLF
	MODEL_DARK_WOLF          ,  //  ��ũ����.
#endif// DARK_WOLF
	MODEL_ICE		         ,
	MODEL_FIRE               ,
	MODEL_POISON             ,
	MODEL_WOLF               ,
	MODEL_WARCRAFT           ,  //  ���� ( ��󽺷� ���� ��Ż �� ).
	MODEL_UNICON             ,
	MODEL_BLOOD              ,
	MODEL_STONE1             ,
	MODEL_STONE2             ,
	MODEL_ICE_SMALL          ,
	MODEL_CIRCLE             ,
	MODEL_CIRCLE_LIGHT       ,
	MODEL_MAGIC1             ,
	MODEL_MAGIC2             ,
	MODEL_STORM              ,
	MODEL_LASER              ,
	MODEL_SKELETON1          ,
	MODEL_SKELETON2          ,
	MODEL_SKELETON3          ,
	MODEL_SKELETON_PCBANG	 ,		// PC�� �̺�Ʈ �ذ����� ���Ź��� ��
	MODEL_HALLOWEEN			 ,		// �ҷ��� �̺�Ʈ �� ������ ���Ź��� ��
	MODEL_HALLOWEEN_EX		 ,
	MODEL_HALLOWEEN_CANDY_BLUE,
	MODEL_HALLOWEEN_CANDY_ORANGE,
	MODEL_HALLOWEEN_CANDY_RED,
	MODEL_HALLOWEEN_CANDY_YELLOW,
	MODEL_HALLOWEEN_CANDY_HOBAK,
	MODEL_HALLOWEEN_CANDY_STAR,
	MODEL_CURSEDTEMPLE_ALLIED_PLAYER,
	MODEL_CURSEDTEMPLE_ILLUSION_PLAYER,
	MODEL_WOOSISTONE		 ,
	MODEL_SAW                ,
	MODEL_BONE1              ,
	MODEL_BONE2              ,
	MODEL_SNOW1              ,
	MODEL_SNOW2              ,
	MODEL_SNOW3              ,
	MODEL_DUNGEON_STONE01    ,
	MODEL_ARROW              ,
	MODEL_ARROW_STEEL        ,
	MODEL_ARROW_THUNDER      ,
	MODEL_ARROW_LASER        ,
	MODEL_ARROW_V            ,
	MODEL_ARROW_SAW          ,
	MODEL_ARROW_NATURE       ,
	MODEL_ARROW_BOMB         ,
	MODEL_ARROW_WING         ,
	MODEL_PROTECT            ,
	MODEL_BIG_STONE1         ,
	MODEL_BIG_STONE2         ,
	MODEL_BIG_METEO1         ,
	MODEL_BIG_METEO2         ,
	MODEL_BIG_METEO3         ,
	MODEL_METEO1             ,
	MODEL_METEO2             ,
	MODEL_MAGIC_CIRCLE1      ,
	MODEL_ARROW_TANKER       ,	// ��Ŀ ����
	MODEL_ARROW_TANKER_HIT	 ,	// ��Ŀ ���� ������
	MODEL_BOSS_HEAD          ,
	MODEL_PRINCESS           ,
	MODEL_BALL               ,
	MODEL_BOSS_ATTACK        ,
	MODEL_SKILL_WHEEL1       ,
	MODEL_SKILL_WHEEL2       ,
	MODEL_SKILL_BLAST        ,
	MODEL_SKILL_INFERNO      ,
	MODEL_ARROW_DOUBLE       ,
	MODEL_ARROW_HOLY         ,
	MODEL_ARROW_SPARK        ,
	MODEL_ARROW_RING		 ,
#ifdef ADD_SOCKET_ITEM
	MODEL_ARROW_DARKSTINGER		,		// ��ũ���ð� ȭ�� ��
	MODEL_FEATHER,						// ��ũ ���ð� ���� ��
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
	MODEL_FEATHER_FOREIGN,						// ��ũ ���ð� ���� ��
#endif //LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
	MODEL_SKILL_FURY_STRIKE  ,
	MODEL_WAVE              = MODEL_SKILL_FURY_STRIKE  +9,
	MODEL_TAIL               ,
	MODEL_PIERCING           ,
	MODEL_WAVE_FORCE        = MODEL_PIERCING           +2,
	MODEL_BLIZZARD	         ,//	�������� ��������.
	MODEL_MAGIC_CAPSULE2     ,// ����� �� ������
	MODEL_STONE_COFFIN       ,//  ���� ����1. 2.
	MODEL_GATE              = MODEL_STONE_COFFIN       +2,//  ���� ����1. 2.
	MODEL_ARROW_BEST_CROSSBOW= MODEL_GATE              +2,//	���� ���� ȭ��.
	MODEL_SPEARSKILL         ,// ��� â��
	MODEL_PEGASUS            ,//  �䰡����.
	MODEL_ARROW_DRILL		 ,//    ������ ���� ȭ��.
	MODEL_COMBO				 ,//	�޺� ��ų ȿ��.
	MODEL_AIR_FORCE          ,//    ���� ���� ȿ��.
	MODEL_WAVES              ,//    ��Ʈ�� �Ǿ��� ����.
	MODEL_PIERCING2          ,//    ��Ʈ�� �Ǿ� ��ǰ.
	MODEL_PIER_PART          ,//    �Ǿ�� ��ǰ.
	MODEL_DARKLORD_SKILL     ,//    ��ũ�ε� �̰����ͽ�ų�� ���̴°�.
	MODEL_GROUND_STONE       ,//    ����.
	MODEL_GROUND_STONE2      ,//    ����2.
	MODEL_WATER_WAVE         ,  //  ���� ���̺� ����
	MODEL_SKULL              ,  //  �ذ�.
	MODEL_LACEARROW			 ,  //	���̽� ���ο�
	MODEL_CUNDUN_PART1		 ,  //  ��� ����1
	MODEL_CUNDUN_PART2		 ,  //  ��� ����2
	MODEL_CUNDUN_PART3		 ,  //  ��� ����3
	MODEL_CUNDUN_PART4		 ,  //  ��� ����4
	MODEL_CUNDUN_PART5		 ,  //  ��� ����5
	MODEL_CUNDUN_PART6		 ,  //  ��� ����6
	MODEL_CUNDUN_PART7		 ,  //  ��� ����7
	MODEL_CUNDUN_PART8		 ,  //  ��� ����8
	MODEL_CUNDUN_DRAGON_HEAD ,  //  ��� ��Ӹ�
	MODEL_CUNDUN_PHOENIX	 ,  //  ��� �һ�
	MODEL_CUNDUN_GHOST		 ,  //  ��� �������� ȥ
	MODEL_CUNDUN_SKILL		 ,  //  ��� ��ų�� (������ ����)
	MODEL_MANY_FLAG          ,  //  �߱� ��ؿ��� ���Ǵ� ���.
	MODEL_WEBZEN_MARK        ,  //  ������ũ.
	MODEL_FLY_BIG_STONE1     ,  //  �������� ���� ( ������ ).
	MODEL_FLY_BIG_STONE2     ,  //  �������� ���� ( ������ ).
	MODEL_BIG_STONE_PART1    ,  //  ������ ���� ����1.
	MODEL_BIG_STONE_PART2    ,  //  ������ ���� ����2.
	MODEL_WALL_PART1         ,  //  ���� ����1.
	MODEL_WALL_PART2         ,  //  ���� ����2.
	MODEL_GATE_PART1         ,  //  ���� ����1.
	MODEL_GATE_PART2         ,  //  ���� ����2.
	MODEL_GATE_PART3         ,  //  ���� ����3.
	MODEL_AURORA             ,  //  ȸ�� ���� ǥ��.
	MODEL_TOWER_GATE_PLANE   ,  //  �̵� ����.
	MODEL_STUN_STONE         ,  //  ������ ���� ��1.
	MODEL_SKIN_SHELL         ,  //  ��Ų ���� ����.
	MODEL_MANA_RUNE          ,  //  ���� ���� ��.
	MODEL_SKILL_JAVELIN      ,  //  ǥâ.
	MODEL_ARROW_IMPACT       ,  //  ������ �ѹ�.
	MODEL_SWORD_FORCE        ,  //  
	MODEL_GOLEM_STONE		 ,	// �� ����
	MODEL_FISSURE			 ,	// ���� �տ�
	MODEL_FISSURE_LIGHT		 ,  // ���� �տ� ��
	MODEL_SKILL_FISSURE		 ,	// ����� ���� ��ü����
	MODEL_PROTECTGUILD       ,  // ��ȣ���
	MODEL_TREE_ATTACK		 ,  //  ���̴� ����Ʈ�� ����
	MODEL_WARP				 ,	//  �븮�� -> ���̴�, ��Ŭ���� -> ����ž 
	MODEL_WARP2				 ,	//  �븮�� -> ���̴�, ��Ŭ���� -> ����ž
	MODEL_WARP3				 ,	//  �븮�� -> ���̴�, ��Ŭ���� -> ����ž
#ifdef CSK_ADD_MAP_ICECITY
	MODEL_WARP4				 ,	//  ��Ŭ���� -> ��Ŭ���� ������
	MODEL_WARP5				 ,	//  ��Ŭ���� -> ��Ŭ���� ������
	MODEL_WARP6				 ,	//  ��Ŭ���� -> ��Ŭ���� ������
#endif // CSK_ADD_MAP_ICECITY
	MODEL_DARK_ELF_SKILL	,
	MODEL_BALGAS_SKILL		,
	MODEL_DEATH_SPI_SKILL	,
	MODEL_SCOLPION			,
	MODEL_BUG_CRY1ST		,
	MODEL_FENRIR_BLACK		,	// �渱 ����
	MODEL_FENRIR_RED		,	// �渱 ����
	MODEL_FENRIR_BLUE		,	// �渱 �Ķ�
	MODEL_FENRIR_GOLD		,	// �渱 ���
	MODEL_FENRIR_THUNDER	,	// �渱 �� ������ �����ٱ�, ������ ü�ζ���Ʈ�� �� ����ȿ��
	MODEL_FENRIR_FOOT_THUNDER	,	// �渱 �߹ٴ� ����
	MODEL_FENRIR_SKILL_THUNDER	,	// �渱 ��ų ���� �����ٱ�
	MODEL_FENRIR_SKILL_DAMAGE	,	// �渱 ��ų ������ Ÿ�� ����Ʈ
	MODEL_ARROW_AUTOLOAD		,	// ȭ�� ���ѻ�� (AT_INFINITY_ARROW) ����Ʈ ���
	MODEL_SHIELD_CRASH			,	// �ǵ� �ı� ����Ʈ
	MODEL_SHIELD_CRASH2			,	// �ǵ� �ı� ����Ʈ2
	MODEL_INFINITY_ARROW		,	// ���ѻ�� �� ����Ʈ
	MODEL_INFINITY_ARROW1		,
	MODEL_INFINITY_ARROW2		,
	MODEL_INFINITY_ARROW3		,
	MODEL_INFINITY_ARROW4		,
	MODEL_IRON_RIDER_ARROW		,
	MODEL_KENTAUROS_ARROW		,
	MODEL_BLADE_SKILL			,
	MODEL_TWINTAIL_EFFECT		,	// ĭ���� 2�� ���� Ʈ������ �Ӹ��߹ٴ� ȿ��
	MODEL_STORM2				,   //  ĭ���� 3�� ������ ����Ʈ�޾� ���� ��ų
	MODEL_SUMMON				,   //  ĭ���� 3�� ������ ����Ʈ�޾� ��ȯ ��ų
	MODEL_STORM3				,	//  ĭ���� 3�� ���� ȸ���� ��ų
	MODEL_MAYASTAR				,	//  ĭ���� 3�� ���� ������ ��
	MODEL_MAYASTONE1			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� �������� ũ����Ż1
	MODEL_MAYASTONE2			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� �������� ũ����Ż2
	MODEL_MAYASTONE3			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� �������� ũ����Ż3
	MODEL_MAYASTONE4			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� ũ����Ż ���� ����1
	MODEL_MAYASTONE5			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� ũ����Ż ���� ����2
	MODEL_MAYASTONEFIRE			,	//  ĭ���� 3�� ���� ũ����Ż ��ų�� �������� ũ����Ż�� �� ȿ��
	MODEL_MAYAHANDSKILL			,	//  ĭ���� 3�� ���߼� ��ų
	MODEL_DARK_SCREAM			,	// ��ũ�ε� ���̾ũ��
	MODEL_DARK_SCREAM_FIRE		,	// ��ũ�ε� ���̾ũ��
	MODEL_CURSEDTEMPLE_HOLYITEM ,
	MODEL_CURSEDTEMPLE_PRODECTION_SKILL ,
	MODEL_CURSEDTEMPLE_RESTRAINT_SKILL ,
	MODEL_FALL_STONE_EFFECT,
	MODEL_CURSEDTEMPLE_STATUE_PART1,
	MODEL_CURSEDTEMPLE_STATUE_PART2,
	MODEL_CHANGE_UP_EFF,
	MODEL_CHANGE_UP_NASA,
	MODEL_CHANGE_UP_CYLINDER,	
	MODEL_TOTEMGOLEM_PART1,
	MODEL_TOTEMGOLEM_PART2,
	MODEL_TOTEMGOLEM_PART3,
	MODEL_TOTEMGOLEM_PART4,
	MODEL_TOTEMGOLEM_PART5,
	MODEL_TOTEMGOLEM_PART6,
	MODEL_SUMMONER_WRISTRING_EFFECT,	// �ո� �� ����Ʈ ��
	MODEL_SUMMONER_EQUIP_HEAD_SAHAMUTT,	// ���Ϲ�Ʈ �Ӹ� ȸ��
	MODEL_SUMMONER_EQUIP_HEAD_NEIL,		// �� �Ӹ� ȸ��
#ifdef ASG_ADD_SUMMON_RARGLE
	MODEL_SUMMONER_EQUIP_HEAD_LAGUL,	// ��� �Ӹ� ȸ��
#endif	// ASG_ADD_SUMMON_RARGLE
	MODEL_SUMMONER_CASTING_EFFECT1,		// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT11,	// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT111,	// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT2,		// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT22,	// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT222,	// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_CASTING_EFFECT4,		// ��ȯ ���� ����Ʈ
	MODEL_SUMMONER_SUMMON_SAHAMUTT,		// ���Ϲ�Ʈ
	MODEL_SUMMONER_SUMMON_NEIL,			// ��
#ifdef ASG_ADD_SUMMON_RARGLE
	MODEL_SUMMONER_SUMMON_LAGUL,		// ���
#endif	// ASG_ADD_SUMMON_RARGLE
	MODEL_SUMMONER_SUMMON_NEIL_NIFE1,	// �� ��ų ����Ʈ Į
	MODEL_SUMMONER_SUMMON_NEIL_NIFE2,	// �� ��ų ����Ʈ Į
	MODEL_SUMMONER_SUMMON_NEIL_NIFE3,	// �� ��ų ����Ʈ Į
	MODEL_SUMMONER_SUMMON_NEIL_GROUND1,	// �� ��ų ����Ʈ �ٴ�
	MODEL_SUMMONER_SUMMON_NEIL_GROUND2,	// �� ��ų ����Ʈ �ٴ�
	MODEL_SUMMONER_SUMMON_NEIL_GROUND3,	// �� ��ų ����Ʈ �ٴ�
	MODEL_SHADOW_PAWN_ANKLE_LEFT,	// ������ ��
	MODEL_SHADOW_PAWN_ANKLE_RIGHT,
	MODEL_SHADOW_PAWN_BELT,
	MODEL_SHADOW_PAWN_CHEST,
	MODEL_SHADOW_PAWN_HELMET,
	MODEL_SHADOW_PAWN_KNEE_LEFT,
	MODEL_SHADOW_PAWN_KNEE_RIGHT,
	MODEL_SHADOW_PAWN_WRIST_LEFT,
	MODEL_SHADOW_PAWN_WRIST_RIGHT,

	MODEL_SHADOW_KNIGHT_ANKLE_LEFT,	// ������ ����Ʈ ��� ������
	MODEL_SHADOW_KNIGHT_ANKLE_RIGHT,
	MODEL_SHADOW_KNIGHT_BELT,
	MODEL_SHADOW_KNIGHT_CHEST,
	MODEL_SHADOW_KNIGHT_HELMET,
	MODEL_SHADOW_KNIGHT_KNEE_LEFT,
	MODEL_SHADOW_KNIGHT_KNEE_RIGHT,
	MODEL_SHADOW_KNIGHT_WRIST_LEFT,
	MODEL_SHADOW_KNIGHT_WRIST_RIGHT,

	MODEL_SHADOW_ROOK_ANKLE_LEFT,	// ������ �� ��� ������
	MODEL_SHADOW_ROOK_ANKLE_RIGHT,
	MODEL_SHADOW_ROOK_BELT,
	MODEL_SHADOW_ROOK_CHEST,
	MODEL_SHADOW_ROOK_HELMET,
	MODEL_SHADOW_ROOK_KNEE_LEFT,
	MODEL_SHADOW_ROOK_KNEE_RIGHT,
	MODEL_SHADOW_ROOK_WRIST_LEFT,
	MODEL_SHADOW_ROOK_WRIST_RIGHT,
	
#ifdef ADD_RAKLION_MOB_ICEGIANT
	MODEL_ICE_GIANT_PART1,			// ���̽� ���̾�Ʈ ����� �� ����.
	MODEL_ICE_GIANT_PART2,
	MODEL_ICE_GIANT_PART3,
	MODEL_ICE_GIANT_PART4,
	MODEL_ICE_GIANT_PART5,
	MODEL_ICE_GIANT_PART6,
#endif	// ADD_RAKLION_MOB_ICEGIANT

	MODEL_EFFECT_SAPITRES_ATTACK,		// ����Ʈ���� ���� ����Ʈ(BMD����)
	MODEL_EFFECT_SAPITRES_ATTACK_1,		// ����Ʈ���� ���� ���� ��
	MODEL_EFFECT_SAPITRES_ATTACK_2,		// ����Ʈ���� ���� ������� ������ ��
	MODEL_EFFECT_THUNDER_NAPIN_ATTACK_1,	// ��������� ��� ��������(BMD����)
#ifdef CSK_EVENT_CHERRYBLOSSOM
	MODEL_EFFECT_SKURA_ITEM,      // ���� �̺�Ʈ ����Ʈ
#endif //CSK_EVENT_CHERRYBLOSSOM	
#ifdef ADD_RAKLION_IRON_KNIGHT
	MODEL_EFFECT_BROKEN_ICE0,
	MODEL_EFFECT_BROKEN_ICE1,
	MODEL_EFFECT_BROKEN_ICE2,
	MODEL_EFFECT_BROKEN_ICE3,
#endif	// ADD_RAKLION_IRON_KNIGHT
#ifdef KJH_ADD_09SUMMER_EVENT
	MODEL_EFFECT_UMBRELLA_LIGHT,
#endif // KJH_ADD_09SUMMER_EVENT
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	MODEL_DESAIR,
#endif //SKILL_DEBUG
#ifdef ADD_SOCKET_ITEM	
	// [�ܻ�����Ʈ] (BMD����)
	//* ���������� �ܻ��� ����Ҷ�(BITMAP_JOINT_ENERGY) zzzCharacter::RenderCharacer()���� CreateJoint()�� ȣ���ϴµ�,
	//* CreateJoint()�� ������ OBJECT�� ĳ������ Object�� �ѱ��.
	//* �̴� ���� �ܻ�����Ʈ ����Ÿ�� �� ����ϴ� ���Ⱑ �ΰ��� ���ÿ� �������ÿ�, ���� ���̰� �ȴ�.
	//* ex) BITMAP_JOINT_ENERGY Subtype 17��,
	//* ���� CreateEffect()�� ȣ���Ͽ�, �� �ȿ��� CreateJoint()�� ȣ���Ͽ� OBJECT�� ���ڷ� Effect�� Object�� �ѱ�� �ȴ�.
	MODEL_EFFECT_TRACE,
	MODEL_STAR_SHINE,			// �� ��� ��¦�̱� (��¦��¦ ������!!)
#endif // ADD_SOCKET_ITEM
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	MODEL_BLOW_OF_DESTRUCTION,			// ���� �ı��� �ϰ� ����Ʈ(BMD����)
	MODEL_NIGHTWATER_01,				// ���� �ı��� �ϰ� ����Ʈ
	MODEL_KNIGHT_PLANCRACK_A,			// ���� �ı��� �ϰ� ����Ʈ
	MODEL_KNIGHT_PLANCRACK_B,			// ���� �ı��� �ϰ� ����Ʈ
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	MODEL_SWELL_OF_MAGICPOWER,			// �渶����(�ҿ︶����) "��������"
	MODEL_SWELL_OF_MAGICPOWER_GUIDE,	// �渶����(�ҿ︶����) "��������" (���ϸ��̼���ġ ����)
	MODEL_ARROWSRE06,					// �渶����(�ҿ︶����) "��������" �ȿ� �ٴ� ����Ʈ��
	MODEL_SWELL_OF_MAGICPOWER_BUFF_EFF,	// �渶����(�ҿ︶����) "��������" ������ ����Ʈ
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	MODEL_EFFECT_FLAME_STRIKE,			// ���˻� �÷��ӽ�Ʈ����ũ ����Ʈ
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	MODEL_STREAMOFICEBREATH,			// ��Ŭ���� ���̽���Ŀ Attack2 ����Ʈ �Ա�(����¦)
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	MODEL_1_STREAMBREATHFIRE,			// ��Ŭ���� ��ƾ �Ա� ���̾� �Ѱ� �߻�
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	MODEL_ARROW_GAMBLE,					// �׺� ���� ȭ��
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef PBG_ADD_PKFIELD
	MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_HEAD,		// PK�ʵ� �ϻ��� ����Ʈ
	MODEL_PKFIELD_ASSASSIN_EFFECT_RED_HEAD,
	MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_BODY,
	MODEL_PKFIELD_ASSASSIN_EFFECT_RED_BODY,
	MODEL_LAVAGIANT_FOOTPRINT_R,
	MODEL_LAVAGIANT_FOOTPRINT_V,
#endif //PBG_ADD_PKFIELD
#ifdef LDS_ADD_GOLDCORPS_EVENT_MOD_GREATDRAGON
	MODEL_EFFECT_FIRE_HIK3_MONO,					// Ȳ�� ������ Ȳ�� �׷���Ʈ �巡�� ���־� ����Ʈ. 
#endif // LDS_ADD_GOLDCORPS_EVENT_MOD_GREATDRAGON
#ifdef LDS_ADD_EMPIRE_GUARDIAN
	MODEL_PROJECTILE,		//���� ��ȣ�� ����Ʈ - ������ �߻�ü
	MODEL_DOOR_CRUSH_EFFECT,			//���� �ı� ����Ʈ
	MODEL_DOOR_CRUSH_EFFECT_PIECE01,	//���� �ı� ����Ʈ ���� 1
	MODEL_DOOR_CRUSH_EFFECT_PIECE02,	//���� �ı� ����Ʈ ���� 2
	MODEL_DOOR_CRUSH_EFFECT_PIECE03,	//���� �ı� ����Ʈ ���� 3
	MODEL_DOOR_CRUSH_EFFECT_PIECE04,	//���� �ı� ����Ʈ ���� 4
	MODEL_DOOR_CRUSH_EFFECT_PIECE05,	//���� �ı� ����Ʈ ���� 5
	MODEL_DOOR_CRUSH_EFFECT_PIECE06,	//���� �ı� ����Ʈ ���� 6
	MODEL_DOOR_CRUSH_EFFECT_PIECE07,	//���� �ı� ����Ʈ ���� 7
	MODEL_DOOR_CRUSH_EFFECT_PIECE08,	//���� �ı� ����Ʈ ���� 8
	MODEL_DOOR_CRUSH_EFFECT_PIECE09,	//���� �ı� ����Ʈ ���� 9
	MODEL_DOOR_CRUSH_EFFECT_PIECE10,	// �ָ� ���� �ı� ����Ʈ ����1 ����
	MODEL_DOOR_CRUSH_EFFECT_PIECE11,	// �ָ� ���� �ı� ����Ʈ ����2
	MODEL_DOOR_CRUSH_EFFECT_PIECE12,	// �ָ� ���� �ı� ����Ʈ ����3
	MODEL_DOOR_CRUSH_EFFECT_PIECE13,	// �ָ� ���� �ı� ����Ʈ ����4
	MODEL_STATUE_CRUSH_EFFECT,			//���� �ı� ����Ʈ
	MODEL_STATUE_CRUSH_EFFECT_PIECE01,	//���� �ı� ����Ʈ ���� 1
	MODEL_STATUE_CRUSH_EFFECT_PIECE02,	//���� �ı� ����Ʈ ���� 2
	MODEL_STATUE_CRUSH_EFFECT_PIECE03,	//���� �ı� ����Ʈ ���� 3
	MODEL_STATUE_CRUSH_EFFECT_PIECE04,	//���� �ı� ����Ʈ ���� 4 ����
#endif //LDS_ADD_EMPIRE_GUARDIAN
#ifdef PJH_ADD_PANDA_CHANGERING
	MODEL_PANDA,			//
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN		// ���� ��ȣ�� �������̿� ����Ʈ
	MODEL_EMPIREGUARDIANBOSS_SKILLEFF01_GENERALATTACK,	// ���� ��ȣ�� �������̿� 1 ��ų (�Ϲ� ����)
	MODEL_EMPIREGUARDIANBOSS_SKILLEFF02_BLOODATTACK,	// ���� ��ȣ�� �������̿� 2 ��ų (���� ����)
	MODEL_EMPIREGUARDIANBOSS_SKILLEFF03_GIGANTIC,		// ���� ��ȣ�� �������̿� 3 ��ų (�Ⱓƽ)
	MODEL_EMPIREGUARDIANBOSS_SKILLEFF04_FRAMESTRIKE,	// ���� ��ȣ�� �������̿� 4 ��ų (�����ӽ�Ʈ����ũ)
	MODEL_SWORDLEFT01_EMPIREGUARDIAN_BOSS_GAION_,		// ���� ��ȣ�� �������̿� ONE OF 5SWORDS
	MODEL_SWORDLEFT02_EMPIREGUARDIAN_BOSS_GAION_,		// ���� ��ȣ�� �������̿� ONE OF 5SWORDS
	MODEL_SWORDRIGHT01_EMPIREGUARDIAN_BOSS_GAION_,		// ���� ��ȣ�� �������̿� ONE OF 5SWORDS
	MODEL_SWORDRIGHT02_EMPIREGUARDIAN_BOSS_GAION_,		// ���� ��ȣ�� �������̿� ONE OF 5SWORDS
	MODEL_SWORDMAIN01_EMPIREGUARDIAN_BOSS_GAION_,		// ���� ��ȣ�� �������̿� ONE OF 5SWORDS
#endif // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
#ifdef LDS_ADD_EG_4_MONSTER_JELINT	
	MODEL_EMPIREGUARDIAN_BLOW_OF_DESTRUCTION,			// ���� ��ȣ�� "�ı��� �ϰ�" ������ ����Ʈ
#endif // LDS_ADD_EG_4_MONSTER_JELINT
#ifdef KJH_ADD_09SUMMER_EVENT
	MODEL_EFFECT_UMBRELLA_DIE,							// ������ ������ ����Ʈ(BMD����)
	MODEL_EFFECT_UMBRELLA_GOLD,							// ������ �ݵ�� ����Ʈ
#endif // KJH_ADD_09SUMMER_EVENT
#ifdef PBG_ADD_CHARACTERSLOT
	MODEL_SLOT_LOCK,									// ĳ���� ����â�� �ڹ���
#endif //PBG_ADD_CHARACTERSLOT
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	MODEL_DOPPELGANGER_SLIME_CHIP,		// ���ð��� ������ �����Ҷ� ���� ���
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
	MODEL_EMPIREGUARDIANBOSS_FRAMESTRIKE,
#endif // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
#ifdef LDK_ADD_EG_MONSTER_DEASULER
	MODEL_DEASULER,
#endif //LDK_ADD_EG_MONSTER_DEASULER
#ifdef KJH_ADD_EG_MONSTER_GUARDIANDEFENDER_EFFECT		
	MODEL_EFFECT_EG_GUARDIANDEFENDER_ATTACK2,			// ������ȣ�� ���к� ����2 ����Ʈ
#endif // KJH_ADD_EG_MONSTER_GUARDIANDEFENDER_EFFECT
#ifdef PBG_ADD_AURA_EFFECT
	MODEL_EFFECT_SD_AURA,									// SD���� ����Ʈ
#endif //PBG_ADD_AURA_EFFECT
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	MODEL_SKELETON_CHANGED,								// ���̷��� ����
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef LDK_ADD_14_15_GRADE_ITEM_MODEL
	MODEL_15GRADE_ARMOR_OBJ_ARMLEFT,					// 14, 15��� ���� �� ����
	MODEL_15GRADE_ARMOR_OBJ_ARMRIGHT,					// 14, 15��� ���� �� ������
	MODEL_15GRADE_ARMOR_OBJ_BODYLEFT,					// 14, 15��� ���� �� ���ʿ���
	MODEL_15GRADE_ARMOR_OBJ_BODYRIGHT,					// 14, 15��� ���� �� ���ʿ�����
	MODEL_15GRADE_ARMOR_OBJ_BOOTLEFT,					// 14, 15��� ���� �� �޹�
	MODEL_15GRADE_ARMOR_OBJ_BOOTRIGHT,					// 14, 15��� ���� �� ������
	MODEL_15GRADE_ARMOR_OBJ_HEAD,						// 14, 15��� ���� �� �Ӹ�
	MODEL_15GRADE_ARMOR_OBJ_PANTLEFT,					// 14, 15��� ���� �� ��������
	MODEL_15GRADE_ARMOR_OBJ_PANTRIGHT,					// 14, 15��� ���� �� ����������
#endif //LDK_ADD_14_15_GRADE_ITEM_MODEL
#ifdef LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET		
	MODEL_EX01_SHADOW_MASTER_ANKLE_LEFT,				// Ȯ��� : ����� �� ������ ������ (������ �� ����) DIE EFFECT
	MODEL_EX01_SHADOW_MASTER_ANKLE_RIGHT,
	MODEL_EX01_SHADOW_MASTER_BELT,
	MODEL_EX01_SHADOW_MASTER_CHEST,
	MODEL_EX01_SHADOW_MASTER_HELMET,
	MODEL_EX01_SHADOW_MASTER_KNEE_LEFT,
	MODEL_EX01_SHADOW_MASTER_KNEE_RIGHT,
	MODEL_EX01_SHADOW_MASTER_WRIST_LEFT,
	MODEL_EX01_SHADOW_MASTER_WRIST_RIGHT,
#endif // LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET

#ifdef ASG_ADD_KARUTAN_MONSTERS
	MODEL_CONDRA_ARM_L,		// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_ARM_L2,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_SHOULDER,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_ARM_R,		// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_ARM_R2,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_CONE_L,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_CONE_R,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_PELVIS,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STOMACH,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_NECK,		// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE,		// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE1,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE2,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE3,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE4,	// �ܵ�� �״� ����Ʈ �� ����
	MODEL_CONDRA_STONE5,	// �ܵ�� �״� ����Ʈ �� ����

	MODEL_NARCONDRA_ARM_L,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_ARM_L2,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_SHOULDER_L,	// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_SHOULDER_R,	// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_ARM_R,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_ARM_R2,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_ARM_R3,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_1,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_2,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_3,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_4,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_5,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_CONE_6,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_PELVIS,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_STOMACH,	// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_NECK,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_STONE,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_STONE1,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_STONE2,		// �����ܵ�� �״� ����Ʈ �� ����
	MODEL_NARCONDRA_STONE3,		// �����ܵ�� �״� ����Ʈ �� ����
#endif	// ASG_ADD_KARUTAN_MONSTERS

#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	MODEL_SWORD_32_LEFT,
	MODEL_SWORD_32_RIGHT,
	MODEL_SWORD_33_LEFT,
	MODEL_SWORD_33_RIGHT,
	MODEL_SWORD_34_LEFT,
	MODEL_SWORD_34_RIGHT,
	MODEL_WOLF_HEAD_EFFECT,
	MODEL_ARMORINVEN_60,
	MODEL_ARMORINVEN_61,
	MODEL_ARMORINVEN_62,
	MODEL_DOWN_ATTACK_DUMMY_L,
	MODEL_DOWN_ATTACK_DUMMY_R,
	MODEL_SHOCKWAVE01,
	MODEL_SHOCKWAVE02,
	MODEL_SHOCKWAVE_SPIN01,
	MODEL_WINDFOCE,
	MODEL_WINDFOCE_MIRROR,
	MODEL_WOLF_HEAD_EFFECT2,
	MODEL_SHOCKWAVE_GROUND01,
	MODEL_DRAGON_KICK_DUMMY,
	MODEL_DRAGON_LOWER_DUMMY,
	MODEL_TARGETMON_EFFECT,
	MODEL_SHOCKWAVE03,
	MODEL_VOLCANO_OF_MONK,
	MODEL_VOLCANO_STONE,
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

	MODEL_SKILL_END
};

enum 
{
	//npc
	MODEL_NPC_BEGIN = MODEL_MONSTER_END,
	MODEL_MERCHANT_FEMALE,
	MODEL_MERCHANT_MAN   ,
	MODEL_MERCHANT_GIRL  ,
	MODEL_SMITH          ,
	MODEL_SCIENTIST      ,
	MODEL_SNOW_MERCHANT  ,
	MODEL_SNOW_SMITH     ,
	MODEL_SNOW_WIZARD    ,
	MODEL_ELF_WIZARD     ,
	MODEL_ELF_MERCHANT   ,
	MODEL_MASTER         ,
	MODEL_STORAGE        ,
	MODEL_TOURNAMENT     ,
	MODEL_MIX_NPC        ,
	MODEL_NPC_DEVILSQUARE,
	MODEL_MERCHANT_FEMALE_HEAD  ,
	MODEL_MERCHANT_FEMALE_UPPER = MODEL_MERCHANT_FEMALE_HEAD  +2,
	MODEL_MERCHANT_FEMALE_LOWER = MODEL_MERCHANT_FEMALE_UPPER +2,
	MODEL_MERCHANT_FEMALE_GLOVES= MODEL_MERCHANT_FEMALE_LOWER +2,
	MODEL_MERCHANT_FEMALE_BOOTS = MODEL_MERCHANT_FEMALE_GLOVES+2,
	MODEL_MERCHANT_MAN_HEAD     = MODEL_MERCHANT_FEMALE_BOOTS +2,
	MODEL_MERCHANT_MAN_UPPER    = MODEL_MERCHANT_MAN_HEAD     +2,
	MODEL_MERCHANT_MAN_GLOVES   = MODEL_MERCHANT_MAN_UPPER    +2,
	MODEL_MERCHANT_MAN_BOOTS    = MODEL_MERCHANT_MAN_GLOVES   +2,
	MODEL_MERCHANT_GIRL_HEAD    = MODEL_MERCHANT_MAN_BOOTS    +2,
	MODEL_MERCHANT_GIRL_UPPER   = MODEL_MERCHANT_GIRL_HEAD    +2,
	MODEL_MERCHANT_GIRL_LOWER   = MODEL_MERCHANT_GIRL_UPPER   +2,
	MODEL_NPC_SEVINA            = MODEL_MERCHANT_GIRL_LOWER   +2,
	MODEL_NPC_ARCHANGEL			 ,
	MODEL_NPC_ARCHANGEL_MESSENGER,
	MODEL_DEVIAS_TRADER          ,  //  ����ƽ�, �η��þ� �߰� ���� NPC
	MODEL_NPC_BREEDER            ,  //  ���û� NPC
	MODEL_ANGEL					 ,
#ifdef _PVP_MURDERER_HERO_ITEM
	MODEL_HERO_SHOP				 ,
#endif	// _PVP_MURDERER_HERO_ITEM
	MODEL_KALIMA_SHOP			 ,
	MODEL_BC_NPC1,					// ���� ���� NPC ���� ĳ��
	MODEL_BC_NPC2,					// ���� ���� NPC ���� ĳ��
	MODEL_BC_BOX,					// ���� ���� NPC �ڽ�
	MODEL_NPC_CAPATULT_ATT       ,  //  ������ ������.
	MODEL_NPC_CAPATULT_DEF       ,  //  ������ ������.
	MODEL_NPC_SENATUS            ,  //  ���ο�.
	MODEL_NPC_GATE_SWITCH        ,  //  ���� ����ġ.
	MODEL_NPC_CROWN              ,  //  �հ� NPC.
	MODEL_NPC_CHECK_FLOOR        ,  //  �հ� üũ ����
	MODEL_NPC_CLERK              ,  //  ��û ����.
	MODEL_NPC_BARRIER            ,  //  ��ȣ��.
	MODEL_NPC_SERBIS			 ,	//  ������ NPC
	MODEL_NPC_SERBIS_DONKEY		 ,	//	�糪��
	MODEL_NPC_SERBIS_FLAG		 ,  //  ���
	MODEL_CRYWOLF_STATUE		 ,  //  ���� �Ż�
	MODEL_CRYWOLF_ALTAR1		 ,  //  ���� 1
	MODEL_CRYWOLF_ALTAR2		 ,  //  ���� 2
	MODEL_CRYWOLF_ALTAR3		 ,  //  ���� 3
	MODEL_CRYWOLF_ALTAR4		 ,  //  ���� 4
	MODEL_CRYWOLF_ALTAR5		 ,  //  ���� 5
	MODEL_KANTURU2ND_ENTER_NPC	 ,	//	ĭ���� 2������ 3���� ���� �Ա� NPC
	MODEL_TRAP_CANON			,	// ĭ���� 2���� Ʈ���� ĳ��
	MODEL_SMELTING_NPC			 ,  //  ������ ž NPC
	MODEL_REFINERY_NPC  ,           //   ���� NPC
	MODEL_RECOVERY_NPC  ,           //   ȯ�� NPC
	MODEL_WEDDING_NPC	,			// ���� NPC
#ifdef ADD_NPC_DEVIN
	MODEL_NPC_DEVIN				,	// ���� ���� NPC
#endif	// ADD_NPC_DEVIN
	MODEL_NPC_QUARREL			,	// ����������� NPC
	MODEL_NPC_CASTEL_GATE		,	// ���� NPC
	MODEL_CURSEDTEMPLE_ENTER_NPC,       // �̺�Ʈ �� ���� NPC
	MODEL_CURSEDTEMPLE_ALLIED_NPC,      // �̺�Ʈ �� ���ձ� NPC
	MODEL_CURSEDTEMPLE_ILLUSION_NPC,    // �̺�Ʈ �� ȯ���� NPC
	MODEL_CURSEDTEMPLE_STATUE,       // ���� NPC
	MODEL_CURSEDTEMPLE_ALLIED_BASKET,      // ���ձ� ���������� NPC
	MODEL_CURSEDTEMPLE_ILLUSION__BASKET,    // ȯ������ ���������� NPC
	MODEL_ELBELAND_SILVIA,			// 6��° ĳ���� ���۸� �����Ĵ� NPC �Ǻ��
	MODEL_ELBELAND_RHEA,			// 6��° ĳ���� ���۸� �����Ĵ� NPC ����
	MODEL_ELBELAND_MARCE,			// 6��° ĳ���� ���۸� ��ų���Ĵ� NPC ������
#ifdef CSK_EVENT_CHERRYBLOSSOM
	MODEL_NPC_CHERRYBLOSSOM,        // ������ ����
#endif // CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_EVENT_CHERRYBLOSSOMTREE
	MODEL_NPC_CHERRYBLOSSOMTREE,        // ������ ����
#endif //PSW_EVENT_CHERRYBLOSSOMTREE
#ifdef ADD_SOCKET_MIX
	MODEL_SEED_MASTER,			// �õ� ������ (���Ͼ�����)
	MODEL_SEED_INVESTIGATOR,	// �õ� ������ (���Ͼ�����)
#endif	// ADD_SOCKET_MIX
#ifdef PBG_ADD_LITTLESANTA_NPC
	MODEL_LITTLESANTA,			// ��Ʋ��Ÿ(1~8)
	MODEL_LITTLESANTA_END = MODEL_LITTLESANTA + 7,
#endif //PBG_ADD_LITTLESANTA_NPC
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	MODEL_XMAS2008_SNOWMAN,		//2008ũ��������(�ؿ�) ����� ���� ��
	MODEL_XMAS2008_SNOWMAN_HEAD,
	MODEL_XMAS2008_SNOWMAN_BODY,
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef LDK_ADD_SNOWMAN_NPC
	MODEL_XMAS2008_SNOWMAN_NPC,	//2008����� npc
#endif //LDK_ADD_SNOWMAN_NPC
#ifdef LDK_ADD_SANTA_NPC
	MODEL_XMAS2008_SANTA_NPC,	//2008��Ÿ NPC
#endif //LDK_ADD_SANTA_NPC
#ifdef YDG_ADD_NEW_DUEL_NPC
	MODEL_DUEL_NPC_TITUS,		// ������ ������ Ÿ������
#endif	// YDG_ADD_NEW_DUEL_NPC
#ifdef LDK_ADD_GAMBLE_NPC_MOSS
	MODEL_GAMBLE_NPC_MOSS,			// �׺� ���� ���� ��
#endif //LDK_ADD_GAMBLE_NPC_MOSS
#ifdef YDG_ADD_DOPPELGANGER_NPC
	MODEL_DOPPELGANGER_NPC_LUGARD,		// ���ð��� NPC �簡��
	MODEL_DOPPELGANGER_NPC_BOX,			// ���ð��� ���� ����
	MODEL_DOPPELGANGER_NPC_GOLDENBOX,	// ���ð��� �������� ����
#endif	// YDG_ADD_DOPPELGANGER_NPC
#ifdef ASG_ADD_GENS_NPC
	MODAL_GENS_NPC_DUPRIAN,			// �ս� NPC �������� ����
	MODAL_GENS_NPC_BARNERT,			// �ս� NPC �ٳ׸�Ʈ ����
#endif	// ASG_ADD_GENS_NPC
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
	MODEL_UNITEDMARKETPLACE_CHRISTIN,	// ���� ���� ũ����ƾ
	MODEL_UNITEDMARKETPLACE_RAUL,		// ���� ���� ���
	MODEL_UNITEDMARKETPLACE_JULIA,		// ���� ���� �ٸ���
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
#ifdef ASG_ADD_TIME_LIMIT_QUEST_NPC
	MODEL_TIME_LIMIT_QUEST_NPC_TERSIA,	// �������� �׸��þ�
	MODEL_TIME_LIMIT_QUEST_NPC_BENA,	// �ų� ���̳�
	MODEL_TIME_LIMIT_QUEST_NPC_ZAIRO,	// �����̻��� ���̷�
#endif	// ASG_ADD_TIME_LIMIT_QUEST_NPC
#ifdef ASG_ADD_KARUTAN_NPC
	MODEL_KARUTAN_NPC_REINA,			// ��ȭ���� ���̳�
	MODEL_KARUTAN_NPC_VOLVO,			// ������� ����
#endif	// ASG_ADD_KARUTAN_NPC
#ifdef LEM_ADD_LUCKYITEM				// ��Ű������ NPC
	MODEL_LUCKYITEM_NPC,			
#endif // LEM_ADD_LUCKYITEM
	MODEL_NPC_END                ,
	//player
	MODEL_PLAYER         		 ,	// (507)
	MODEL_SHADOW_BODY     		 ,
	MODEL_SHADOW_SWORD	    	 ,
	MODEL_SHADOW_AXE	    	 ,
	MODEL_SHADOW_MACE   		 ,
	MODEL_SHADOW_SPEAR	    	 ,
	MODEL_SHADOW_BOW		     ,
	MODEL_SHADOW_STAFF		     ,

	//item
	MODEL_ITEM					 ,	// (515)
	
	MODEL_SWORD					= MODEL_ITEM,
	MODEL_AXE					= (MODEL_ITEM+ITEM_AXE),
	MODEL_MACE					= (MODEL_ITEM+ITEM_MACE),
	MODEL_SPEAR					= (MODEL_ITEM+ITEM_SPEAR),
	MODEL_BOW					= (MODEL_ITEM+ITEM_BOW),
	MODEL_STAFF					= (MODEL_ITEM+ITEM_STAFF),
	MODEL_SHIELD				= (MODEL_ITEM+ITEM_SHIELD),
	MODEL_HELM 					= (MODEL_ITEM+ITEM_HELM),	//���
	MODEL_ARMOR					= (MODEL_ITEM+ITEM_ARMOR),	//����
	MODEL_PANTS					= (MODEL_ITEM+ITEM_PANTS),	//����
	MODEL_GLOVES				= (MODEL_ITEM+ITEM_GLOVES),	//�尩
	MODEL_BOOTS					= (MODEL_ITEM+ITEM_BOOTS),	//����
	MODEL_WING 					= (MODEL_ITEM+ITEM_WING),	//����
	MODEL_HELPER				= (MODEL_ITEM+ITEM_HELPER),
	MODEL_POTION				= (MODEL_ITEM+ITEM_POTION),
	MODEL_ETC					= (MODEL_ITEM+ITEM_ETC),

	// ��ȯ����� ������ ���� ���� ����, ��ũ �ø��� ������.
	MODEL_HELM2 				= (MODEL_ITEM+MAX_ITEM),
	MODEL_ARMOR2				= (MODEL_HELM2+MODEL_ITEM_COMMON_NUM),
	MODEL_PANTS2				= (MODEL_ARMOR2+MODEL_ITEM_COMMON_NUM),
	MODEL_GLOVES2				= (MODEL_PANTS2+MODEL_ITEM_COMMON_NUM),
	MODEL_BOOTS2				= (MODEL_GLOVES2+MODEL_ITEM_COMMON_NUM),
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	// �������������� ���� �𵨰� ���� �Ӽ��� �𵨸� �ٸ� �������߰�
	MODEL_HELM_MONK				= (MODEL_BOOTS2+MODEL_ITEM_COMMON_NUM),
	MODEL_ARMOR_MONK			= (MODEL_HELM_MONK+MODEL_ITEM_COMMONCNT_RAGEFIGHTER),
	MODEL_PANTS_MONK			= (MODEL_ARMOR_MONK+MODEL_ITEM_COMMONCNT_RAGEFIGHTER),
	MODEL_BOOTS_MONK			= (MODEL_PANTS_MONK+MODEL_ITEM_COMMONCNT_RAGEFIGHTER),

	MODEL_BODY_HELM 			= (MODEL_BOOTS_MONK+MODEL_ITEM_COMMONCNT_RAGEFIGHTER),
#else //PBG_ADD_NEWCHAR_MONK_ITEM
	MODEL_BODY_HELM 			= (MODEL_BOOTS2+MODEL_ITEM_COMMON_NUM),
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	MODEL_BODY_ARMOR			= (MODEL_BODY_HELM+MODEL_BODY_NUM),
	MODEL_BODY_PANTS			= (MODEL_BODY_ARMOR+MODEL_BODY_NUM),
	MODEL_BODY_GLOVES			= (MODEL_BODY_PANTS+MODEL_BODY_NUM),
	MODEL_BODY_BOOTS			= (MODEL_BODY_GLOVES+MODEL_BODY_NUM),

	MODEL_EVENT					= (MODEL_BODY_BOOTS+MODEL_BODY_NUM),
	MODEL_QUEST                 = (MODEL_EVENT+MAX_EVENT_ITEM),		 //  ����Ʈ ������.
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	MODEL_MULTI_SHOT1			,
	MODEL_MULTI_SHOT2			,
	MODEL_MULTI_SHOT3			,
	MODEL_MASK_HELM             = (MODEL_MULTI_SHOT3+MAX_QUEST_ITEM),		 //  ��ũ�ε忡 �߰��Ǵ� ����ũ.
#else
	MODEL_MASK_HELM             = (MODEL_QUEST+MAX_QUEST_ITEM),		 //  ��ũ�ε忡 �߰��Ǵ� ����ũ.
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	MAX_MODELS					= (MODEL_MASK_HELM+MAX_ITEM_INDEX),
};
//object end

//lodterrain start
enum ENUM_WORLD
{
	WD_0LORENCIA = 0,	// 0    �η��þ�.
	WD_1DUNGEON,		// 1    ����.
	WD_2DEVIAS,			// 2    ����ƽ�.
	WD_3NORIA,			// 3    �븮��.
	WD_4LOSTTOWER,		// 4    �ν�ƮŸ��.
	WD_5UNKNOWN,		// 5    
	WD_6STADIUM,		// 6    ��Ʋ��Ŀ �����.
	WD_7ATLANSE,		// 7    ��Ʋ����.
	WD_8TARKAN,			// 8    Ÿ��ĭ.
	WD_9DEVILSQUARE,	// 9    �Ǹ��� ����.
	WD_10HEAVEN,        // 10   õ��.
	WD_11BLOODCASTLE1,  // 11   ���� 1ĳ��.
	WD_11BLOODCASTLE_END = WD_11BLOODCASTLE1+6,// 11 + 6   ���� 7ĳ��.
	WD_18CHAOS_CASTLE,          //  18  ī����ĳ��.
	WD_18CHAOS_CASTLE_END = WD_18CHAOS_CASTLE+(CHAOS_NUM-1),
	WD_24HELLAS,        //  24  ���.
	WD_24HELLAS_END = WD_24HELLAS+(HELLAS_NUM-2),	//6Į��������
	WD_30BATTLECASTLE, 
	WD_31HUNTING_GROUND = 31,	// 31 ������ �����
								// 32 �Ǹ��� ���� 5,6 Ȯ�忡 ����
	WD_33AIDA			= 33,	// 33 ���̴�
	WD_34CRYWOLF_1ST	= 34,	// 34 ũ���̿��� MVP
	WD_35CRYWOLF_2ND    = 35,	// 35 ũ���̿��� 2���� ���ϻ���(���� �Ⱦ� : �̹�ȣ ���ɷ� �ᵵ��)
	WD_24HELLAS_7		= 36,	// 36 ���� Į����
	WD_37KANTURU_1ST	= 37,	// 37 ĭ���� 1��
	WD_38KANTURU_2ND	= 38,	// 38 ĭ���� 2��
	WD_39KANTURU_3RD	= 39,	// 39 ĭ���� 3��
	WD_40AREA_FOR_GM	= 40,	// GM ��ȯ ����
	WD_41CHANGEUP3RD_1ST	= 41,	// 41 �߰����� ����
	WD_42CHANGEUP3RD_2ND	= 42,	// 42 �߰����� �Ƚ�ó
	WD_45CURSEDTEMPLE_LV1	= 45,	// The event map for the capture the flag
	WD_45CURSEDTEMPLE_LV2,			// The event map for the capture the flag
	WD_45CURSEDTEMPLE_LV3,			// The event map for the capture the flag
	WD_45CURSEDTEMPLE_LV4,			// The event map for the capture the flag
	WD_45CURSEDTEMPLE_LV5,			// The event map for the capture the flag
	WD_45CURSEDTEMPLE_LV6,			// The event map for the capture the flag
	WD_51HOME_6TH_CHAR		= 51,	// 51 ��ĳ���� ���۸�
	WD_52BLOODCASTLE_MASTER_LEVEL = 52,
	WD_53CAOSCASTLE_MASTER_LEVEL = 53,
	WD_54CHARACTERSCENE = 54,			// 54 ���ο� �ɸ��� ��
	WD_55LOGINSCENE		= 55,			// 55 ���ο� �α��� ��
	WD_56MAP_SWAMP_OF_QUIET = 56,		// 56 ����� ��
#ifdef CSK_ADD_MAP_ICECITY
	WD_57ICECITY			= 57,		// 57 ��������
	WD_58ICECITY_BOSS		= 58,		// 58 �������� ������
#endif // CSK_ADD_MAP_ICECITY
#ifdef YDG_ADD_MAP_SANTA_TOWN
	WD_62SANTA_TOWN			= 62,		// 62 ��Ÿ����
#endif	// YDG_ADD_MAP_SANTA_TOWN
#ifdef PBG_ADD_PKFIELD
	WD_63PK_FIELD			= 63,		// 63 PK�ʵ�
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DUEL_ARENA
	WD_64DUELARENA			= 64,		// 64 ������
#endif	// YDG_ADD_MAP_DUEL_ARENA
#ifdef YDG_ADD_MAP_DOPPELGANGER1
	WD_65DOPPLEGANGER1		= 65,		// 65 ���ð��� �̺�Ʈ �� 1 (57��Ŭ���º��̽�)
#endif	// YDG_ADD_MAP_DOPPELGANGER1
#ifdef YDG_ADD_MAP_DOPPELGANGER2
	WD_66DOPPLEGANGER2		= 66,		// 66 ���ð��� �̺�Ʈ �� 2 (63��ī�������̽�)
#endif	// YDG_ADD_MAP_DOPPELGANGER2
#ifdef YDG_ADD_MAP_DOPPELGANGER3
	WD_67DOPPLEGANGER3		= 67,		// 67 ���ð��� �̺�Ʈ �� 3 ( 7��Ʋ�������̽�)
#endif	// YDG_ADD_MAP_DOPPELGANGER3
#ifdef YDG_ADD_MAP_DOPPELGANGER4
	WD_68DOPPLEGANGER4		= 68,		// 68 ���ð��� �̺�Ʈ �� 4 (37ĭ����1�����̽�)
#endif	// YDG_ADD_MAP_DOPPELGANGER4
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN1
	WD_69EMPIREGUARDIAN1	= 69,		// 69 ���� ��ȣ�� �� 1 (��, �� ���ϸ�)
#endif //LDK_ADD_MAP_EMPIREGUARDIAN1
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN2		
	WD_70EMPIREGUARDIAN2	= 70,		// 70 ���� ��ȣ�� �� 2 (ȭ, �� ���ϸ�)
#endif // LDS_ADD_MAP_EMPIREGUARDIAN2
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN3
	WD_71EMPIREGUARDIAN3	= 71,		// 71 ���� ��ȣ�� �� 3 (��, �� ���ϸ�)
#endif //LDK_ADD_MAP_EMPIREGUARDIAN3
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN4		
	WD_72EMPIREGUARDIAN4	= 72,		// 72 ���� ��ȣ�� �� 4 (��     �ָ���)
#endif // LDS_ADD_MAP_EMPIREGUARDIAN4
#ifdef PJH_NEW_SERVER_SELECT_MAP
	WD_73NEW_LOGIN_SCENE		= 73,	// 74 �⺻ ������ȣ��4 ������ ����
	WD_74NEW_CHARACTER_SCENE	= 74,	// 75 �⺻ ������ȣ��4 ������ ����
#else //PJH_NEW_SERVER_SELECT_MAP
	WD_77NEW_LOGIN_SCENE		= 77,	// 77 �� ���ο� ���� ���þ�
	WD_78NEW_CHARACTER_SCENE	= 78,	// 78 �� ���ο� ĳ���� ���þ�
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
	WD_79UNITEDMARKETPLACE		= 79,	// 79 ���� ���� ���� (�η�����)
#endif // LDS_ADD_MAP_UNITEDMARKETPLACE
#ifdef ASG_ADD_MAP_KARUTAN
	WD_80KARUTAN1			= 80,		// 80 Į��ź 1
	WD_81KARUTAN2			= 81,		// 81 Į��ź 2
#endif	// ASG_ADD_MAP_KARUTAN
	NUM_WD
};
//lodterrain end

//inventory start
enum 
{ 
	PSHOPWNDTYPE_NONE = -1,
	PSHOPWNDTYPE_SALE = 1,
	PSHOPWNDTYPE_PURCHASE 
};
enum ITEM_EX_SRC_TYPE
{
	ITEM_EX_SRC_EQUIPMENT = 1,		//. �κ��丮 ���â
};

enum ENUM_KEYPADMODE
{
	// ���� ���
	KPM_MOVE = 1,
	KPM_LOCK3 = 2,
	KPM_UNLOCK = 3,
	KPM_LOCK1 = 4,
	KPM_LOCK2 = 5,

	// ���� ���� ���� �ֹι�ȣ Ȯ��
	KPM_SERVER_IMMIGRATION_CHECK = 6,
};

enum
{
	EVENT_NONE = 0,
	EVENT_LENA,             //  ����.
	EVENT_STONE,            //  ����.
	EVENT_SCRATCH_TICKET,   //  ����.
	EVENT_STONE_EXCHANGE,   //  ���� ȯ��.
	EVENT_FRIEND,           //  ģ�� �̺�Ʈ.
};

//inventory end

//ai start

enum
{
	PLAYER_SET,	
	PLAYER_STOP_MALE,
	PLAYER_STOP_FEMALE,
	PLAYER_STOP_SUMMONER,				// ��ȯ���� ���ڸ�
	PLAYER_STOP_SWORD,
	PLAYER_STOP_TWO_HAND_SWORD,
	PLAYER_STOP_SPEAR,
	PLAYER_STOP_SCYTHE,
	PLAYER_STOP_BOW,
	PLAYER_STOP_CROSSBOW,
	PLAYER_STOP_WAND,					// �ϵ� ��� ���ڸ�
	PLAYER_STOP_FLY,
	PLAYER_STOP_FLY_CROSSBOW,
	PLAYER_STOP_RIDE,
	PLAYER_STOP_RIDE_WEAPON,

	PLAYER_WALK_MALE,
	PLAYER_WALK_FEMALE,
	PLAYER_WALK_SWORD,
	PLAYER_WALK_TWO_HAND_SWORD,
	PLAYER_WALK_SPEAR,
	PLAYER_WALK_SCYTHE,
	PLAYER_WALK_BOW,
	PLAYER_WALK_CROSSBOW,
	PLAYER_WALK_WAND,					// �ϵ� ��� �ȱ�
	PLAYER_WALK_SWIM,
	PLAYER_RUN,
	PLAYER_RUN_SWORD,
	PLAYER_RUN_TWO_SWORD,
	PLAYER_RUN_TWO_HAND_SWORD,
	PLAYER_RUN_SPEAR,
	PLAYER_RUN_BOW,
	PLAYER_RUN_CROSSBOW,
	PLAYER_RUN_WAND,					// �ϵ� ��� �ٱ�
	PLAYER_RUN_SWIM,
	PLAYER_FLY,
	PLAYER_FLY_CROSSBOW,
	PLAYER_RUN_RIDE,
	PLAYER_RUN_RIDE_WEAPON,

	PLAYER_ATTACK_FIST,					// �ָ� ���ϸ��̼�
	PLAYER_ATTACK_SWORD_RIGHT1,
	PLAYER_ATTACK_SWORD_RIGHT2,
	PLAYER_ATTACK_SWORD_LEFT1,
	PLAYER_ATTACK_SWORD_LEFT2,
	PLAYER_ATTACK_TWO_HAND_SWORD1,
	PLAYER_ATTACK_TWO_HAND_SWORD2,
	PLAYER_ATTACK_TWO_HAND_SWORD3,
	PLAYER_ATTACK_SPEAR1,
	PLAYER_ATTACK_SCYTHE1,
	PLAYER_ATTACK_SCYTHE2,
	PLAYER_ATTACK_SCYTHE3,
	PLAYER_ATTACK_BOW,
	PLAYER_ATTACK_CROSSBOW,
	PLAYER_ATTACK_FLY_BOW,
	PLAYER_ATTACK_FLY_CROSSBOW,
	PLAYER_ATTACK_RIDE_SWORD,
	PLAYER_ATTACK_RIDE_TWO_HAND_SWORD,
	PLAYER_ATTACK_RIDE_SPEAR,
	PLAYER_ATTACK_RIDE_SCYTHE,
	PLAYER_ATTACK_RIDE_BOW,
	PLAYER_ATTACK_RIDE_CROSSBOW,

	PLAYER_ATTACK_SKILL_SWORD1,
	PLAYER_ATTACK_SKILL_SWORD2,
	PLAYER_ATTACK_SKILL_SWORD3,
	PLAYER_ATTACK_SKILL_SWORD4,
	PLAYER_ATTACK_SKILL_SWORD5,

	PLAYER_ATTACK_SKILL_WHEEL,
	PLAYER_ATTACK_SKILL_FURY_STRIKE,
	PLAYER_SKILL_VITALITY,
	PLAYER_SKILL_RIDER,
	PLAYER_SKILL_RIDER_FLY,
	PLAYER_ATTACK_SKILL_SPEAR,
	PLAYER_ATTACK_ONETOONE,
	PLAYER_SKILL_HELL_BEGIN,
	PLAYER_SKILL_HELL_START,

	PLAYER_ATTACK_END,

	PLAYER_FLY_RIDE                 = PLAYER_ATTACK_END,
	PLAYER_FLY_RIDE_WEAPON          ,
	PLAYER_DARKLORD_STAND           ,   //  ��ũ�ε� ��ũ���Ǹ���� ����.
	PLAYER_DARKLORD_WALK            ,   //  ��ũ�ε� ��ũ���Ǹ���� �ȱ�.
	PLAYER_STOP_RIDE_HORSE          ,   //  ��ũ�ε� ���� ( ��� �� ).        (��) 
	PLAYER_RUN_RIDE_HORSE           ,   //  ��ũ�ε� ��Ƽ ��ȯ.                 (��) 
	PLAYER_ATTACK_STRIKE            ,   //  ��ũȦ�� Ÿ�� ����.                 (��)
	PLAYER_ATTACK_TELEPORT          ,   //  ��ũȦ�� �޸���.                        
	PLAYER_ATTACK_RIDE_STRIKE       ,   //  ��ũȦ�� Ÿ�� ���� ( ��� �� ).
	PLAYER_ATTACK_RIDE_TELEPORT     ,   //  ��ũȦ�� Ÿ��  ��Ƽ ��ȯ.
	PLAYER_ATTACK_RIDE_HORSE_SWORD  ,   //  ��ũȦ�� Ÿ�� �Ѽ� ����.
	PLAYER_ATTACK_RIDE_ATTACK_FLASH ,   //  ��ũȦ�� Ÿ�� ���͚�Ʈ����ũ.
	PLAYER_ATTACK_RIDE_ATTACK_MAGIC ,   //  ��ũȦ�� Ÿ�� ���� ����.
	PLAYER_ATTACK_DARKHORSE         ,   //  ��ũȦ�� ��ų.
	PLAYER_IDLE1_DARKHORSE			,   //  (�α��ξ���)��ũȦ�� Ÿ�� ���� �ֵθ���
	PLAYER_IDLE2_DARKHORSE			,   //  (�α��ξ���)��ũȦ�� ���� �ٸ� ���
	PLAYER_FENRIR_ATTACK			,		//	�Ϲݰ��� - �ƹ��͵� �ȵ� ����
	PLAYER_FENRIR_ATTACK_DARKLORD_AQUA,		//	�Ϲݰ��� - ������
	PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE,	//	�Ϲݰ��� - ��ũ�ε� ���
	PLAYER_FENRIR_ATTACK_DARKLORD_SWORD,	//	�Ϲݰ��� - ��ũ�ε� Ÿ��(�Ѽ� ����)
	PLAYER_FENRIR_ATTACK_DARKLORD_TELEPORT,	//	�Ϲݰ��� - ��ũ�ε� ��Ƽ ��ȯ
	PLAYER_FENRIR_ATTACK_DARKLORD_FLASH,	//	�Ϲݰ��� - ��ũ�ε� ������÷���
	PLAYER_FENRIR_ATTACK_TWO_SWORD,			//	�Ϲݰ��� - �μ�Į ����(���)
	PLAYER_FENRIR_ATTACK_MAGIC,				//	�Ϲݰ��� - ���� ����(������)
	PLAYER_FENRIR_ATTACK_CROSSBOW,			//	�Ϲݰ��� - ���� ����(����)
	PLAYER_FENRIR_ATTACK_SPEAR,				//	�Ϲݰ��� - â ����(���)
	PLAYER_FENRIR_ATTACK_ONE_SWORD,			//	�Ϲݰ��� - �Ѽ�Į ����(���)
	PLAYER_FENRIR_ATTACK_BOW,				//  �Ϲݰ��� - Ȱ ����(����)
	PLAYER_FENRIR_SKILL,					//	��ų���� - �Ǽ�
	PLAYER_FENRIR_SKILL_TWO_SWORD,			//	��ų���� - ���Į
	PLAYER_FENRIR_SKILL_ONE_RIGHT,			//	��ų���� - �Ѽ� ������(100)
	PLAYER_FENRIR_SKILL_ONE_LEFT,			//	��ų���� - �Ѽ� ����
	PLAYER_FENRIR_DAMAGE,					//	������ - �Ǽ�
	PLAYER_FENRIR_DAMAGE_TWO_SWORD,			//	������ - ���Į
	PLAYER_FENRIR_DAMAGE_ONE_RIGHT,			//	������ - �Ѽ� ������
	PLAYER_FENRIR_DAMAGE_ONE_LEFT,			//	������ - �Ѽ� ����
	PLAYER_FENRIR_RUN,						//	�޸��� - �Ǽ�(110)
	PLAYER_FENRIR_RUN_TWO_SWORD,			//	�޸��� - ���Į
	PLAYER_FENRIR_RUN_ONE_RIGHT,			//	�޸��� - �Ѽ� ������
	PLAYER_FENRIR_RUN_ONE_LEFT,				//	�޸��� - �Ѽ� ����
	PLAYER_FENRIR_RUN_MAGOM,				//	�޸��� - �Ǽ�_����(114)
	PLAYER_FENRIR_RUN_TWO_SWORD_MAGOM,		//	�޸��� - ���_����
	PLAYER_FENRIR_RUN_ONE_RIGHT_MAGOM,		//	�޸��� - ������_����
	PLAYER_FENRIR_RUN_ONE_LEFT_MAGOM,		//	�޸��� - �޼�_����
	PLAYER_FENRIR_RUN_ELF,					//	�޸��� - �Ǽ�_����
	PLAYER_FENRIR_RUN_TWO_SWORD_ELF,		//	�޸��� - ���_����
	PLAYER_FENRIR_RUN_ONE_RIGHT_ELF,		//	�޸��� - ������_����
	PLAYER_FENRIR_RUN_ONE_LEFT_ELF,			//	�޸��� - �޼�_����
	PLAYER_FENRIR_STAND,					//  ���� - �Ǽ�
	PLAYER_FENRIR_STAND_TWO_SWORD,			//	���� - ���Į
	PLAYER_FENRIR_STAND_ONE_RIGHT,			//	���� - �Ѽ� ������
	PLAYER_FENRIR_STAND_ONE_LEFT,			//  ���� - �Ѽ� ����
	PLAYER_FENRIR_WALK,						//	�ȱ� - �Ǽ�
	PLAYER_FENRIR_WALK_TWO_SWORD,			//	�ȱ� - ���Į
	PLAYER_FENRIR_WALK_ONE_RIGHT,			//	�ȱ� - �Ѽ� ������
	PLAYER_FENRIR_WALK_ONE_LEFT,			//	�ȱ� - �Ѽ� ����(129)

	PLAYER_ATTACK_BOW_UP			,   //  Ȱ�� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_CROSSBOW_UP       ,   //  �������� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_FLY_BOW_UP		,   //  ���� �ް� Ȱ�� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_FLY_CROSSBOW_UP   ,   //  ���� �ް� �������� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_RIDE_BOW_UP       ,   //  ��Ÿ�� Ȱ�� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_RIDE_CROSSBOW_UP  ,   //  ��Ÿ�� �������� �ϴ÷� ���ؼ� ����
	PLAYER_ATTACK_ONE_FLASH         ,   //  �⸶�� �ϼ�����.
	PLAYER_ATTACK_RUSH              ,   //  ��� ���� ����.
	PLAYER_ATTACK_DEATH_CANNON      ,   //  ������ ������.
	PLAYER_ATTACK_REMOVAL           ,   //  ������ ��ų ���� ����.
	PLAYER_ATTACK_STUN              ,   //  ���� ����
	PLAYER_HIGH_SHOCK               ,   //  �ɰ��� ��� ȿ��.(142)

	//	�߰��Ǵ� �μ� ���� �ִϸ��̼�.
	PLAYER_STOP_TWO_HAND_SWORD_TWO	,
	PLAYER_WALK_TWO_HAND_SWORD_TWO	,
	PLAYER_RUN_TWO_HAND_SWORD_TWO	,
	PLAYER_ATTACK_TWO_HAND_SWORD_TWO,

	PLAYER_SKILL_HAND1              ,
	PLAYER_SKILL_HAND2				,
	PLAYER_SKILL_WEAPON1    		,
	PLAYER_SKILL_WEAPON2		    , //(150)
	PLAYER_SKILL_ELF1				,	// ���� : ���ݷ¾�/�߾�¾�/����
	PLAYER_SKILL_TELEPORT  		    ,
	PLAYER_SKILL_FLASH     		    ,
	PLAYER_SKILL_INFERNO            ,
	PLAYER_SKILL_HELL     		    ,
	PLAYER_RIDE_SKILL               ,
// ��ȯ���� ���� ��ų.
	PLAYER_SKILL_SLEEP				,
	PLAYER_SKILL_SLEEP_UNI			,
	PLAYER_SKILL_SLEEP_DINO			,
	PLAYER_SKILL_SLEEP_FENRIR		,
	PLAYER_SKILL_CHAIN_LIGHTNING	,
	PLAYER_SKILL_CHAIN_LIGHTNING_UNI,
	PLAYER_SKILL_CHAIN_LIGHTNING_DINO,
	PLAYER_SKILL_CHAIN_LIGHTNING_FENRIR,
	PLAYER_SKILL_LIGHTNING_ORB		,
	PLAYER_SKILL_LIGHTNING_ORB_UNI	,
	PLAYER_SKILL_LIGHTNING_ORB_DINO	,
	PLAYER_SKILL_LIGHTNING_ORB_FENRIR,
	PLAYER_SKILL_DRAIN_LIFE			,	// ��ȯ���� : �巹�ζ�����
	PLAYER_SKILL_DRAIN_LIFE_UNI		,
	PLAYER_SKILL_DRAIN_LIFE_DINO	,
	PLAYER_SKILL_DRAIN_LIFE_FENRIR	,
// ��ȯ���� ��ȯ ����.
	PLAYER_SKILL_SUMMON				,
	PLAYER_SKILL_SUMMON_UNI			,
	PLAYER_SKILL_SUMMON_DINO		,
	PLAYER_SKILL_SUMMON_FENRIR		,

#ifdef ADD_NEW_SKILL_SEASON4
	PLAYER_SKILL_BLOW_OF_DESTRUCTION,	// �ı��� �ϰ�
	PLAYER_SKILL_SWELL_OF_MP		,	// ���� ����
	PLAYER_SKILL_MULTISHOT_BOW_STAND,	// ��Ƽ��
	PLAYER_SKILL_MULTISHOT_BOW_FLYING,
	PLAYER_SKILL_MULTISHOT_CROSSBOW_STAND,
	PLAYER_SKILL_MULTISHOT_CROSSBOW_FLYING,
	PLAYER_SKILL_RECOVERY			,	// �ǵ� ȸ�� ����
	PLAYER_SKILL_GIGANTICSTORM		,	// �Ⱓƽ����
	PLAYER_SKILL_FLAMESTRIKE		,	// �÷��ӽ�Ʈ����ũ
	PLAYER_SKILL_LIGHTNING_SHOCK	,	// ����Ʈ�׼�ũ
#endif	// ADD_NEW_SKILL_SEASON4
#ifdef YDG_ADD_SKILL_RIDING_ANIMATIONS
	PLAYER_SKILL_GIGANTICSTORM_UNI	,	// �Ⱓƽ���� ž���߰�
	PLAYER_SKILL_GIGANTICSTORM_DINO	,
	PLAYER_SKILL_GIGANTICSTORM_FENRIR	,
	PLAYER_ATTACK_SKILL_WHEEL_UNI	,	// ȸ�������� ������� ž���߰�
	PLAYER_ATTACK_SKILL_WHEEL_DINO	,
	PLAYER_ATTACK_SKILL_WHEEL_FENRIR	,
#endif	// YDG_ADD_SKILL_RIDING_ANIMATIONS
	PLAYER_DEFENSE1                 ,
	PLAYER_GREETING1                ,
	PLAYER_GREETING_FEMALE1       	,
	PLAYER_GOODBYE1               	, //(160)
	PLAYER_GOODBYE_FEMALE1          ,
	PLAYER_CLAP1                  	,//�ڼ�
	PLAYER_CLAP_FEMALE1             ,
	PLAYER_CHEER1                   ,//ȯȣ
	PLAYER_CHEER_FEMALE1            ,
	PLAYER_DIRECTION1               ,
	PLAYER_DIRECTION_FEMALE1        ,
	PLAYER_GESTURE1                 ,
	PLAYER_GESTURE_FEMALE1        	,
	PLAYER_UNKNOWN1               	, //(170)
	PLAYER_UNKNOWN_FEMALE1          ,
	PLAYER_CRY1                   	,//
	PLAYER_CRY_FEMALE1              ,
	PLAYER_AWKWARD1                 ,//���
	PLAYER_AWKWARD_FEMALE1          ,
	PLAYER_SEE1                     ,
	PLAYER_SEE_FEMALE1              ,
	PLAYER_WIN1                     ,
	PLAYER_WIN_FEMALE1            	,
	PLAYER_SMILE1                 	, //(180)
	PLAYER_SMILE_FEMALE1            ,
	PLAYER_SLEEP1                 	,
	PLAYER_SLEEP_FEMALE1            ,
	PLAYER_COLD1                    ,
	PLAYER_COLD_FEMALE1             ,
	PLAYER_AGAIN1                   ,
	PLAYER_AGAIN_FEMALE1            ,
	PLAYER_RESPECT1                 ,//����
	PLAYER_SALUTE1                	,//���
	PLAYER_SCISSORS				  	,	// ���� (���� ���� �ȸ����� SetActionClass() ����) (190)
	PLAYER_ROCK					    ,	// ���� (��� ���� �ȵǰ� �Ϸ��� PLAYER_SHOCK���� �߰�)
	PLAYER_PAPER				  	,	// ��
	PLAYER_HUSTLE					,	// �Ϻ� ������ ���� -_-
	PLAYER_PROVOCATION				,
	PLAYER_LOOK_AROUND				,
	PLAYER_CHEERS					,
#ifdef WORLDCUP_ADD
	PLAYER_KOREA_HANDCLAP			,
	PLAYER_POINT_DANCE				,
#endif //WORLDCUP_ADD
	PLAYER_RUSH1                    ,
	PLAYER_COME_UP                  ,
	PLAYER_SHOCK                    ,
	PLAYER_DIE1                     ,
	PLAYER_DIE2                     ,
	PLAYER_SIT1                   	,
	PLAYER_SIT2                   	,
	PLAYER_SIT_FEMALE1              ,
	PLAYER_SIT_FEMALE2            	,
	PLAYER_HEALING1                 ,
	PLAYER_HEALING_FEMALE1          ,
	PLAYER_POSE1                    ,
	PLAYER_POSE_FEMALE1             ,
	PLAYER_JACK_1					,	// ������ ����1
	PLAYER_JACK_2					,	// ������ ����2
	PLAYER_SANTA_1					,	// ���� ����
	PLAYER_SANTA_2					,	// �� ����
	PLAYER_CHANGE_UP				,
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	PLAYER_RECOVER_SKILL			,
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	PLAYER_SKILL_THRUST				,
	PLAYER_SKILL_STAMP				,
	PLAYER_SKILL_GIANTSWING			,
	PLAYER_SKILL_DARKSIDE_READY		,
	PLAYER_SKILL_DARKSIDE_ATTACK	,
	PLAYER_SKILL_DRAGONKICK			,
	PLAYER_SKILL_DRAGONLORE			,
	PLAYER_SKILL_ATT_UP_OURFORCES	,
	PLAYER_SKILL_HP_UP_OURFORCES	,
// ������ ������ ���� �ִ�
	PLAYER_RAGE_UNI_ATTACK			,
	PLAYER_RAGE_UNI_ATTACK_ONE_RIGHT,
	PLAYER_RAGE_UNI_RUN				,
	PLAYER_RAGE_UNI_RUN_ONE_RIGHT	,
	PLAYER_RAGE_UNI_STOP_ONE_RIGHT	,
	PLAYER_RAGE_FENRIR				,
	PLAYER_RAGE_FENRIR_TWO_SWORD	,
	PLAYER_RAGE_FENRIR_ONE_RIGHT	,
	PLAYER_RAGE_FENRIR_ONE_LEFT		,
	PLAYER_RAGE_FENRIR_WALK			,
	PLAYER_RAGE_FENRIR_WALK_ONE_RIGHT,
	PLAYER_RAGE_FENRIR_WALK_ONE_LEFT,
	PLAYER_RAGE_FENRIR_WALK_TWO_SWORD,
	PLAYER_RAGE_FENRIR_RUN			,
	PLAYER_RAGE_FENRIR_RUN_TWO_SWORD,
	PLAYER_RAGE_FENRIR_RUN_ONE_RIGHT,
	PLAYER_RAGE_FENRIR_RUN_ONE_LEFT	,
	PLAYER_RAGE_FENRIR_STAND		,
	PLAYER_RAGE_FENRIR_STAND_TWO_SWORD,
	PLAYER_RAGE_FENRIR_STAND_ONE_RIGHT,
	PLAYER_RAGE_FENRIR_STAND_ONE_LEFT,
	PLAYER_RAGE_FENRIR_DAMAGE		,
	PLAYER_RAGE_FENRIR_DAMAGE_TWO_SWORD,
	PLAYER_RAGE_FENRIR_DAMAGE_ONE_RIGHT,
	PLAYER_RAGE_FENRIR_DAMAGE_ONE_LEFT,
	PLAYER_RAGE_FENRIR_ATTACK_RIGHT	,
	PLAYER_STOP_RAGEFIGHTER			,
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	MAX_PLAYER_ACTION               ,
};
//ai end

//publicfile start
// ĳ���� ��ȣ


enum CLASS_TYPE
{
// 1�� ����
	CLASS_WIZARD = 0,		// �渶����
	CLASS_KNIGHT,			// ����
	CLASS_ELF,				// ����
	CLASS_DARK,				// ���˻�
	CLASS_DARK_LORD,		// ��ũ�ε�
	CLASS_SUMMONER,			// ��ȯ����
#ifdef PBG_ADD_NEWCHAR_MONK
	CLASS_RAGEFIGHTER,		// ������������
#endif //PBG_ADD_NEWCHAR_MONK

// 2�� ����
	CLASS_SOULMASTER,		// �渶���� - �ҿ︶����
	CLASS_BLADEKNIGHT,		// ���� - ���̵峪��Ʈ
	CLASS_MUSEELF,			// ���� - �����
	CLASS_BLOODYSUMMONER,	// ��ȯ���� - ���𼭸ӳ�

// 3�� ����
	CLASS_GRANDMASTER,		// �渶���� - �ҿ︶���� - �׷��帶����
	CLASS_BLADEMASTER,		// ���� - ���̵峪��Ʈ - ���̵帶����
	CLASS_HIGHELF,			// ���� - ����� - ���̿���
	CLASS_DUELMASTER,		// ���˻� - X - ��󸶽���
	CLASS_LORDEMPEROR,		// ��ũ�ε� - X - �ε忥�۷�
	CLASS_DIMENSIONMASTER,	// ��ȯ���� - ���𼭸ӳ� - ���Ǹ�����
#ifdef PBG_ADD_NEWCHAR_MONK
	CLASS_TEMPLENIGHT,		// ������������ - ���� ����Ʈ
#endif //PBG_ADD_NEWCHAR_MONK
};

enum MonsterSkillType
{
	ATMON_SKILL_BIGIN		= 0,
	ATMON_SKILL_THUNDER		= 1,   //�����극��ũ
	ATMON_SKILL_WIND		= 2,   //��������
	ATMON_SKILL_FIRELAY		= 3,   //���̾��
	ATMON_SKILL_CHARM		= 4,   //��
	ATMON_SKILL_TOUCH		= 5,   //�����̾��ġ
	ATMON_SKILL_NUM1		= 6,	// ��ũ����-�׷��ȯ��
	ATMON_SKILL_NUM2		= 7,	// ��ũ����-�׷�ġ��
	ATMON_SKILL_NUM3		= 8,	// ��ũ����-�˱�
	ATMON_SKILL_NUM4		= 9,	// �߶�-��������
	ATMON_SKILL_NUM5		= 10,	// �������Ǹ�-����AG����
	ATMON_SKILL_NUM6		= 11,	// �Ҷ�-�о��
	ATMON_SKILL_NUM7		= 12,	// �߰���-��������
	ATMON_SKILL_NUM8		= 13,	// �߰���-10�ں���
	ATMON_SKILL_NUM9		= 14,	// ��Ÿ��ν�-�ٹ߽�ų
	ATMON_SKILL_NUM10		= 15,
	ATMON_SKILL_NUM11		= 16,	// Ʈ������ - ������
	ATMON_SKILL_NUM12		= 17,	// �巡���Ǿ� - 2�ܰ���
	ATMON_SKILL_NORMAL		= 18,	// ��� ��ų
	ATMON_SKILL_STORM		= 19,	// ȸ���� ��ų
	ATMON_SKILL_SUMMON		= 20,	// ��ȯ ��ų
	ATMON_SKILL_HELL		= 21,	// ������� ��ų
	ATMON_SKILL_TELEPORT	= 22,	// �����̵� ��ų
	ATMON_SKILL_SHOCK		= 23,	// ����� ��ų
	ATMON_SKILL_CRYSTAL		= 24,	// ũ����Ż ��ų
	ATMON_SKILL_MAYASTORM	= 25,	// ȸ���� ��ų
	ATMON_SKILL_MAYACRYSTAL = 26,	// ũ����Ż ���׿�
	ATMON_SKILL_COURSED_STUN   = 27,
	ATMON_SKILL_COURSED_POISON = 28,
#ifdef CSK_RAKLION_BOSS
	// ��Ŭ���� �������� ��ų
	ATMON_SKILL_SERUFAN_POISONGEM = 34,		// ������(������)
	ATMON_SKILL_SERUFAN_COOLSTORM = 35,		// �ñ���ǳ(������)
	ATMON_SKILL_SERUFAN_COOLSHOCK = 36,		// �ñ����(������)
	ATMON_SKILL_SERUFAN_FALLING = 37,		// ����(������)
	ATMON_SKILL_SERUFAN_SUMMON = 38,		// ��ȯ(������)
	ATMON_SKILL_SERUFAN_HEAL = 39,			// ġ��(������)
	ATMON_SKILL_SERUFAN_FREEZE = 40,		// �󸮱�(������)
	ATMON_SKILL_SERUFAN_TELEPORT = 41,		// �����̵�(������)
	ATMON_SKILL_SERUFAN_SUPERMAN = 42,		// ����(������)
#endif // CSK_RAKLION_BOSS
#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
	ATMON_SKILL_EMPIREGUARDIAN_BERSERKER = 59,				// ������ȣ�� ��� ���� - ����ȭ
	ATMON_SKILL_EMPIREGUARDIAN_GAION_02_BLOODATTACK = 64,	// ������ȣ�� ���� ���̿� - SKILL02 - �������
	ATMON_SKILL_EMPIREGUARDIAN_GAION_03_GIGANTIKSTORM = 65,	// ������ȣ�� ���� ���̿� - SKILL03 - �Ⱓƽ����
	ATMON_SKILL_EMPIREGUARDIAN_GAION_04_FLAMEATTACK = 66,	// ������ȣ�� ���� ���̿� - SKILL04 - �÷���
	ATMON_SKILL_EMPIREGUARDIAN_GAION_01_GENERALATTACK = 67,	// ������ȣ�� ���� ���̿� - SKILL01 - �⺻����	// �۾����� �߰�
#endif // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
#ifdef LDS_EXTENSIONMAP_MONSTERS_AIDA
	ATMON_SKILL_EX_BLOODYGOLUEM_ATTACKSKILL = 68,		// Ȯ��� ���� �߰� ��ų (���� ��)
	ATMON_SKILL_EX_BLOODYWITCHQUEEN_ATTACKSKILL = 69,	// Ȯ��� ���� �߰� ��ų (���� ��ġ��)
#endif // LDS_EXTENSIONMAP_MONSTERS_AIDA
#ifdef LDS_EXTENSIONMAP_MONSTERS_KANTUR
	ATMON_SKILL_EX_BERSERKERWARRIOR_ATTACKSKILL = 70,	// Ȯ��� ���� �߰� ��ų (����Ŀ ������)
	ATMON_SKILL_EX_KENTAURUSWARRIOR_ATTACKSKILL = 14,	// Ȯ��� ���� �߰� ��ų (��Ÿ��罺 ������)
	ATMON_SKILL_EX_GENOSIDEWARRIOR_ATTACKSKILL = 71,	// Ȯ��� ���� �߰� ��ų (������̵� ������)
#endif // LDS_EXTENSIONMAP_MONSTERS_KANTUR
#ifdef LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET
	ATMON_SKILL_EX_SAPIQUEEN_ATTACKSKILL = 72,			// Ȯ��� ���� �߰� ��ų (������)
	ATMON_SKILL_EX_ICENAPIN_ATTACKSKILL = 73,			// Ȯ��� ���� �߰� ��ų (���̽� ������)
	ATMON_SKILL_EX_SHADOWMASTER_ATTACKSKILL = 74,		// Ȯ��� ���� �߰� ��ų (������ ������)
#endif // LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	ATMON_SKILL_EX_DARKMEMUD_ATTACKSKILL = 75,			// Ȯ��� ���� �߰� ��ų (��ũ �޸ӵ�)
	ATMON_SKILL_EX_DARKGIANT_ATTACKSKILL = 76,			// Ȯ��� ���� �߰� ��ų (��ũ ���̾�Ʈ)
	ATMON_SKILL_EX_DARKAIONNIGHT_ATTACKSKILL = 32,		// Ȯ��� ���� �߰� ��ų (��ũ ���̾� ����Ʈ)
	ATMON_SKILL_EX_DARKCOOLERTIN_ATTACKSKILL = 77,		// Ȯ��� ���� �߰� ��ų (��ũ ��ƾ)
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	ATMON_SKILL_END,
};

//----------------------------------------------------------------------------
// ĳ������ �ൿ ��ȣ
enum ActionSkillType
{
	//////////////////////////////////////////////////////////////////////////
	//  ��ų.
	//////////////////////////////////////////////////////////////////////////

	//������
	AT_SKILL_POISON			= 1,	//	������			// �̰����� 16���� ����å�� �����Ѵ�.(�����Ҽ� ����)
	AT_SKILL_METEO			= 2,	//	�
	AT_SKILL_THUNDER		= 3,	//	����
	AT_SKILL_FIREBALL		= 4,	//	���̾
	AT_SKILL_FLAME			= 5,	//	�ұ��
	AT_SKILL_TELEPORT		= 6,	//	�����̵�
	AT_SKILL_SLOW			= 7,	//	����
	AT_SKILL_STORM			= 8,	//	ȸ����
	AT_SKILL_EVIL			= 9,	//	�Ƿ�
	AT_SKILL_HELL			= 10,	//	�����̾�
	AT_SKILL_POWERWAVE		= 11,	//	�Ŀ����̺�
	AT_SKILL_FLASH			= 12,	//	������÷���
	AT_SKILL_BLAST			= 13,	//	����Ʈ
	AT_SKILL_INFERNO		= 14,	//	���丣��
	AT_SKILL_TELEPORT_B		= 15,   //	�ڷ�Ű�׽ý�	// �����̵� B. ( ��Ƽ���� �̵���Ų��. )
	AT_SKILL_WIZARDDEFENSE	= 16,	//	�ҿ�ٸ���		// �������ݹ�� ***
	AT_SKILL_ENERGYBALL		= 17,	//	��������
	
	AT_SKILL_BLAST_POISON		= 38,	//	����������
	AT_SKILL_BLAST_FREEZE		= 39,	//	������̽�
	AT_SKILL_BLAST_HELL			= 40,	//	�����Ʈ
	AT_SKILL_BLAST_HELL_BEGIN	= 58,	//	�����Ʈ ����.
	
	//���
	AT_SKILL_BLOCKING   = 18,	//	���
	AT_SKILL_SWORD1     = 19,	//	�������
	AT_SKILL_SWORD2     = 20,	//	���
	AT_SKILL_SWORD3     = 21,	//	�÷�ġ��
	AT_SKILL_SWORD4     = 22,	//	����ġ��
	AT_SKILL_SWORD5     = 23,	//	����
	AT_SKILL_SPEAR		= 47,	//	â���	(�⸶�� â ��ų ***)
	AT_SKILL_VITALITY	= 48,	//	����������	(��� ����� ����	**)
	AT_SKILL_RIDER      = 49,	//	���̵彸	(��� ����Ʈ ����. ***)


	//����
	AT_SKILL_CROSSBOW   = 24,	//	�ٹ� (Ȱ��ų)
	AT_SKILL_BOW        = 25,	//	Ȱ��ų
	AT_SKILL_HEALING    = 26,	//	ġ��       (������/5+(�����۷���+1)*5)            //�̰����ʹ� ���������� �����Ѵ�.
	AT_SKILL_DEFENSE    = 27,	//	�������� (��30�ʰ� ������/8+(�ƾ��۷���+1)*2��ŭ ����)
	AT_SKILL_ATTACK     = 28,	//	���ݷ����� (��30�ʰ� ������/7+(�ƾ��۷���+1)*3��ŭ ����)
	AT_SKILL_SUMMON     = 30,	//	��ȯ       (�ƾ��۷����� ���� ����ȯ)
	AT_SKILL_PARALYZE	= 51,	//	���ͼ�ȭ��Ű��			***
	AT_SKILL_PIERCING	= 52,	//	���̽��ַο�	(��������					***)
	AT_SKILL_IMPROVE_AG = 53,	//	�ο��� ( AG���� �ӵ� ����. )
	AT_SKILL_BLAST_CROSSBOW4 = 54,	//	Ȱ��ų ( 4 �ٹ� ).
	

	//���˻�
	AT_SKILL_REDUCEDEFENSE	= 55,	//	�������	(���� ���� ����		***)
	AT_SKILL_ICE_BLADE      = 56,	//	�Ŀ�������	(�������̵� ���⽺ų)(�������� �������.)

	//���߰���
	AT_SKILL_WHEEL      = 41,		//  ȸ��������
	AT_SKILL_FURY_STRIKE= 42,		//  �г����ϰ� (������������ �ִ� ���� ���ݼӵ�/�̵��ӵ� 30%������.)
	AT_SKILL_ONETOONE	= 43,		//  ��ο� (��� 1��1 ����		***)
	AT_SKILL_RUSH       = 44,   //  ��� ���� ��ų.
	AT_SKILL_JAVELIN    = 45,   //  ���� ���� ǥâ ����.
	AT_SKILL_DEEPIMPACT = 46,   //  ���� ������ ��� ����.
	AT_SKILL_ONEFLASH   = 57,   //  �⸶�� �ϼ� ����.

	//����
	AT_SKILL_BOSS       = 50,	

	//�޺���ų.
	AT_SKILL_COMBO		= 59,//�޺���ų.

	//. ��ũ�ε�
	AT_SKILL_STRONG_PIER        = 60,   //  ��Ʈ�� �Ǿ�
	AT_SKILL_LONGPIER_ATTACK,           //  ���Ǿ� ����.(���̾� ����Ʈ)
	AT_SKILL_DARK_HORSE,                //  ��ũȦ�� ����.(�����ũ)
	AT_SKILL_PARTY_TELEPORT,            //  ��Ƽ�� ��ȯ.
	AT_SKILL_ADD_CRITICAL,              //  ũ��Ƽ�õ���������
	AT_SKILL_THUNDER_STRIKE,            //  �Ϸ�Ʈ�� ������ũ.
	AT_SKILL_LONG_SPEAR,                //  ���������� ����ϴ� �ս��Ǿ�. 
	AT_SKILL_STUN               ,       //  ����.
	AT_SKILL_REMOVAL_STUN       ,       //  ���� ����.
	AT_SKILL_MANA               ,       //  ��������.
	AT_SKILL_INVISIBLE          ,       //  ����.(70)
	AT_SKILL_REMOVAL_INVISIBLE  ,       //  ���� ����.
	AT_SKILL_REMOVAL_BUFF       ,       //  �������� �Ͻ� ����.
	AT_SKILL_DEATH_CANNON       ,       //  ������ ������ ����.
	AT_SKILL_SPACE_SPLIT        ,       //  ��ũ�ε� ���ݽ�ų ( ���� ������ ).
	AT_SKILL_BRAND_OF_SKILL     ,       //  ��ũ�ε� ��ų�� ���� ( Ȯ��� ��ų�� ����Ҽ� �ְ� �ϴ� ��ų )
	AT_SKILL_PLASMA_STORM_FENRIR	= 76	,	// �渱 �ö�� ����(76)
	AT_SKILL_INFINITY_ARROW		,		//	���ӽð����� ȭ���� �������� ���� �ʴ´�.
	AT_SKILL_DARK_SCREAM,				// ���̾� ��ũ��
	AT_SKILL_EXPLODE,

//////////////////////////////////////////////////////////////////////////
//  �ɼ�.
//////////////////////////////////////////////////////////////////////////
	AT_IMPROVE_DAMAGE           ,//�߰� ���ݷ�           (Level*4)
	AT_IMPROVE_MAGIC            ,//�߰� ����             (Level*4)
	AT_IMPROVE_CURSE            ,//�߰� ���ַ�
	AT_IMPROVE_BLOCKING         ,//�߰� �����           (Level*5)
	AT_IMPROVE_DEFENSE          ,//�߰� ����           (Level*4)
	AT_LUCK                     ,//��ȥ�� ���� ���� Ȯ�� +25%
	AT_LIFE_REGENERATION        ,//���� �ڵ� ȸ��        (Level*1%)

	AT_IMPROVE_LIFE             ,//����� ����
	AT_IMPROVE_MANA             ,//���� ����
	AT_DECREASE_DAMAGE          ,//������ ����
	AT_REFLECTION_DAMAGE        ,//������ �ݻ�
	AT_IMPROVE_BLOCKING_PERCENT ,//������
	AT_IMPROVE_GAIN_GOLD        ,//ȹ�� �� ����
	AT_EXCELLENT_DAMAGE         ,//�׼���Ʈ ������ ����
	AT_IMPROVE_DAMAGE_LEVEL     ,//���ݷ� ����(����)
	AT_IMPROVE_DAMAGE_PERCENT   ,//���ݷ� ����(2�ۼ�Ʈ)
	AT_IMPROVE_MAGIC_LEVEL      ,//���� ����(����)
	AT_IMPROVE_MAGIC_PERCENT    ,//���� ����(�ۼ�Ʈ)
	AT_IMPROVE_ATTACK_SPEED     ,//���� �ӵ�
	AT_IMPROVE_GAIN_LIFE        ,//ȹ�� �����
	AT_IMPROVE_GAIN_MANA        ,//ȹ�� ����

	//  ���� �߰� �ɼ�.
	AT_IMPROVE_HP_MAX           ,   //  �ִ� HP +50 ����.
	AT_IMPROVE_MP_MAX           ,   //  �ִ� MP +50 ����.
	AT_ONE_PERCENT_DAMAGE       ,   //  3% Ȯ���� ���� ���� ���� ����.
	AT_IMPROVE_AG_MAX           ,   //  �ִ� AG +50 ����.
	AT_DAMAGE_ABSORB            ,   //  �߰� ������ ���.

	//  ���� 3�� �߰� �ɼ�
	AT_DAMAGE_REFLECTION     ,	// [����� ������ �������� ������ ���] 5% Ȯ���� �� ���ݷ� 50% ������
	AT_RECOVER_FULL_LIFE     ,	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��
	AT_RECOVER_FULL_MANA     ,	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��

	//  ���� �߰� �ɼ�.
	AT_IMPROVE_CHARISMA         ,   //  ��� ����.

	//  ����Ʈ.
	AT_IMPROVE_EVADE            = 110,   //  ĳ���� ȸ���� 10% ����.

	//  ���� ��ų.
	AT_SKILL_MONSTER_SUMMON     = 200,  //  ���� ��ȯ.
	AT_SKILL_MONSTER_MAGIC_DEF  ,       //  ���� ���� �ְ�.
	AT_SKILL_MONSTER_PHY_DEF    ,       //  ���� ���� �ְ�.
#ifdef HELLOWIN_EVENT
	AT_SKILL_HELLOWIN_EVENT_1	= 205,
	AT_SKILL_HELLOWIN_EVENT_2	= 206,
	AT_SKILL_HELLOWIN_EVENT_3	= 207,
	AT_SKILL_HELLOWIN_EVENT_4	= 208,
	AT_SKILL_HELLOWIN_EVENT_5	= 209,
#endif //HELLOWIN_EVENT
	AT_SKILL_CURSED_TEMPLE_PRODECTION  = 210,        //��ȣ�� �ֹ�
	AT_SKILL_CURSED_TEMPLE_RESTRAINT   = 211,        //�ӹ��� �ֹ�
	AT_SKILL_CURSED_TEMPLE_TELEPORT    = 212,        //��ȯ�� �ֹ�
//	AT_SKILL_CURSED_TEMPLE_QUICKNESS   = 213,        //�ż��� �ֹ�
	AT_SKILL_CURSED_TEMPLE_SUBLIMATION = 213,        //�����
	AT_SKILL_ALICE_DRAINLIFE = 214,				// 214	"�巹�� ������"
	AT_SKILL_ALICE_CHAINLIGHTNING = 215,		// 215	"ü�� ����Ʈ��"
	AT_SKILL_ALICE_LIGHTNINGORB = 216,			// 216	"����Ʈ�� ����"
	AT_SKILL_ALICE_THORNS = 217,				// 217	"����"
	AT_SKILL_ALICE_BERSERKER = 218,				// 218	"����Ŀ"
	AT_SKILL_ALICE_SLEEP = 219,					// 219	"����"
	AT_SKILL_ALICE_BLIND = 220,					// 220	"����ε�"
	AT_SKILL_ALICE_WEAKNESS = 221,				// 221	"��ũ�Ͻ�"
	AT_SKILL_ALICE_ENERVATION = 222,			// 222	"�̳ʺ��̼�"

	// ��ȯ����
	AT_SKILL_SUMMON_EXPLOSION = 223,			// �ͽ��÷���
	AT_SKILL_SUMMON_REQUIEM,					// ������
#ifdef ASG_ADD_SUMMON_RARGLE
	AT_SKILL_SUMMON_POLLUTION = 225,			// �޷��.
#endif	// ASG_ADD_SUMMON_RARGLE
	
	// ����4 �ű� ��ų
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
	AT_SKILL_LIGHTNING_SHOCK = 230,			// 230 ��ȯ���� ����Ʈ�� ��ũ
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	AT_SKILL_BLOW_OF_DESTRUCTION = 232,		// 232	"�ı����ϰ�"
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
	
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	AT_SKILL_SWELL_OF_MAGICPOWER = 233,			// 233	�渶����(�ҿ︶����) "��������"
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER

#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	AT_SKILL_FLAME_STRIKE = 236,		// 236 ���˻� �÷��� ��ũ����ũ
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	AT_SKILL_GIGANTIC_STORM = 237,		// 237 ���˻� �Ⱓƽ ����
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	AT_SKILL_RECOVER = 234,             // 234 ȸ��
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	AT_SKILL_MULTI_SHOT = 235,
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	AT_SKILL_GAOTIC = 238,
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	AT_SKILL_DOPPELGANGER_SELFDESTRUCTION = 239,	// 239 ���ð��� ����
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL		// ������������ ��ų
	AT_SKILL_THRUST = 260,				// ���
	AT_SKILL_STAMP = 261,				// �������
	AT_SKILL_GIANTSWING = 262,			// ���̾�Ʈ ����
	AT_SKILL_DARKSIDE = 263,			// ��ũ���̵�
	AT_SKILL_DRAGON_LOWER = 264,		// �巹��ξ�
	AT_SKILL_DRAGON_KICK = 265,			// �巹��ű
	AT_SKILL_ATT_UP_OURFORCES = 266,	// ���ݼ��������
	AT_SKILL_HP_UP_OURFORCES = 267,		// ü�����
	AT_SKILL_DEF_UP_OURFORCES = 268,	// ���������
	AT_SKILL_OCCUPY = 269,				// ����
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

	AT_SKILL_ATTACK_RATEUP		= 300,								//���� ������ ���.
	AT_SKILL_TOMAN_ATTACKUP		= AT_SKILL_ATTACK_RATEUP + 5,		//���� ������ ���.
	AT_SKILL_TOMAN_DEFENCEUP	= AT_SKILL_TOMAN_ATTACKUP + 5,		//���� ����� ����.
	AT_SKILL_DURABLE_MINUS1		= AT_SKILL_TOMAN_DEFENCEUP + 5,		//���� ���� 1
	AT_SKILL_DURABLE_MINUS2		= AT_SKILL_DURABLE_MINUS1 + 5,		//���� ���� 2
	AT_SKILL_RESIST_UP_POISON	= AT_SKILL_DURABLE_MINUS2 + 5,		//���׷� ���(��)
	AT_SKILL_RESIST_UP_LIGHT	= AT_SKILL_RESIST_UP_POISON + 5,	//���׷� ���(����)
	AT_SKILL_RESIST_UP_ICE		= AT_SKILL_RESIST_UP_LIGHT + 5,		//���׷� ���(����)
	AT_SKILL_AUTO_RECOVER_LIFE	= AT_SKILL_RESIST_UP_ICE + 5,		//����� �ڵ� ȸ�� ��ȭ
	AT_SKILL_GET_MONEY_UP		= AT_SKILL_AUTO_RECOVER_LIFE + 5,	//�� ����
	AT_SKILL_DEF_UP				= AT_SKILL_GET_MONEY_UP + 5,		//���� ����(350)
	AT_SKILL_MAX_HP_UP			= AT_SKILL_DEF_UP + 5,				//�ִ�HP����
	AT_SKILL_MAX_AG_UP			= AT_SKILL_MAX_HP_UP + 5,			//�ִ�AG����
	AT_SKILL_MANA_RECOVER		= AT_SKILL_MAX_AG_UP + 5,			//����ų�ø���ȸ��
	AT_SKILL_HP_RECOVER			= AT_SKILL_MANA_RECOVER + 5,		//����ų�û����ȸ��
	AT_SKILL_SD_RECOVER			= AT_SKILL_HP_RECOVER + 5,			//����ų��SD����
	AT_SKILL_EXP_UP				= AT_SKILL_SD_RECOVER + 5,			//����ġ���
	AT_SKILL_MAX_SD_UP			= AT_SKILL_EXP_UP + 5,				//�ִ�SD����
	AT_SKILL_SD_RECOVER_SPD_UP	= AT_SKILL_MAX_SD_UP + 5,			//SDȸ���ӵ����
	AT_SKILL_MAX_ATTACKRATE_UP  = AT_SKILL_SD_RECOVER_SPD_UP + 5,	//�ִ���ݷ»��
	AT_SKILL_MIN_ATTACKRATE_UP  = AT_SKILL_MAX_ATTACKRATE_UP + 5,	//�ּҰ��ݷ»��(400)
	AT_SKILL_MANA_MINUS_ADD     = AT_SKILL_MIN_ATTACKRATE_UP + 5,	//�������Ұ�ȭ
	AT_SKILL_MAX_MANA_UP		= AT_SKILL_MANA_MINUS_ADD + 5,		//�ִ븶�»��
	AT_SKILL_MIN_MANA_UP		= AT_SKILL_MAX_MANA_UP + 5,			//�ּҸ��»��
	AT_SKILL_PET_DURABLE_SPD_DN = AT_SKILL_MIN_MANA_UP + 5,			//�곻���Ҹ�ӵ�����
	AT_SKILL_MAX_ATT_MAGIC_UP	= AT_SKILL_PET_DURABLE_SPD_DN + 5,	//�ִ���ݷ�/���»��
	AT_SKILL_MIN_ATT_MAGIC_UP   = AT_SKILL_MAX_ATT_MAGIC_UP	+ 5,	//�ּҰ��ݷ�/���»��

	AT_SKILL_SOUL_UP			= AT_SKILL_MIN_ATT_MAGIC_UP	+ 5,	//�ҿ�ٸ��ȭ
	AT_SKILL_HELL_FIRE_UP		= AT_SKILL_SOUL_UP + 5,				//�����̾ȭ
	AT_SKILL_EVIL_SPIRIT_UP		= AT_SKILL_HELL_FIRE_UP + 5,		//�Ƿɰ�ȭ(�渶����)
	AT_SKILL_ICE_UP				= AT_SKILL_EVIL_SPIRIT_UP + 5,		//������̽���ȭ(450)
	AT_SKILL_TORNADO_SWORDA_UP	= AT_SKILL_ICE_UP + 5,				//ȸ�������ⰭȭA(����)
	AT_SKILL_BLOW_UP			= AT_SKILL_TORNADO_SWORDA_UP + 5,	//��ο찭ȭ
	AT_SKILL_ANGER_SWORD_UP		= AT_SKILL_BLOW_UP + 5,				//�г����ϰݰ�ȭ
	AT_SKILL_LIFE_UP			= AT_SKILL_ANGER_SWORD_UP + 5,		//������������ȭ

	AT_SKILL_HEAL_UP			= AT_SKILL_LIFE_UP + 5,				//ġ�ᰭȭ
	AT_SKILL_DEF_POWER_UP		= AT_SKILL_HEAL_UP + 5,				//�������ȭ
	AT_SKILL_ATT_POWER_UP		= AT_SKILL_DEF_POWER_UP + 5,		//���ݷ����ȭ
	AT_SKILL_MANY_ARROW_UP		= AT_SKILL_ATT_POWER_UP + 5,		//�ٹ߰�ȭ

	AT_SKILL_TORNADO_SWORDB_UP	= AT_SKILL_MANY_ARROW_UP + 5,		//ȸ�������ⰭȭB
	AT_SKILL_BLOOD_ATT_UP		= AT_SKILL_TORNADO_SWORDB_UP + 5,   //������ð�ȭ(500)
	AT_SKILL_POWER_SLASH_UP		= AT_SKILL_BLOOD_ATT_UP + 5,		//�Ŀ���������ȭ
	AT_SKILL_BLAST_UP			= AT_SKILL_POWER_SLASH_UP + 5,		//����Ʈ��ȭ

	AT_SKILL_ASHAKE_UP			= AT_SKILL_BLAST_UP + 5,			//�����ũ��ȭ
	AT_SKILL_FIRE_BUST_UP		= AT_SKILL_ASHAKE_UP + 5,			//���̾����Ʈ��ȭ
	AT_SKILL_FIRE_SCREAM_UP		= AT_SKILL_FIRE_BUST_UP + 5,		//���̾ũ����ȭ

	AT_SKILL_EVIL_SPIRIT_UP_M	= AT_SKILL_FIRE_SCREAM_UP + 5,		//�Ƿɰ�ȭ(���˻�)
#ifdef PJH_ADD_MASTERSKILL
	AT_SKILL_ALICE_SLEEP_UP				= AT_SKILL_EVIL_SPIRIT_UP_M + 5,		//���� ��ȭ
	AT_SKILL_ALICE_CHAINLIGHTNING_UP	= AT_SKILL_ALICE_SLEEP_UP + 5,	//ü�ζ���Ʈ�� ��ȭ
	AT_SKILL_LIGHTNING_SHOCK_UP			= AT_SKILL_ALICE_CHAINLIGHTNING_UP + 5,	//����Ʈ�׼�ũ(����) ��ȭ
	AT_SKILL_ALICE_DRAINLIFE_UP			= AT_SKILL_LIGHTNING_SHOCK_UP + 5,		//�巹�ζ����� ��ȭ
#endif
};


enum    PetCommandType
{
	//  Ŀ�ǵ� ��ų.
	AT_PET_COMMAND_DEFAULT      = 120,  //  �Ϲ� �ൿ.
	AT_PET_COMMAND_RANDOM       ,       //  ���� ����.
	AT_PET_COMMAND_OWNER        ,       //  ���ΰ� ���� ����.
	AT_PET_COMMAND_TARGET       ,       //  Ÿ�� ����.
	AT_PET_COMMAND_END          ,   
};

enum    OptionType
{

	//////////////////////////////////////////////////////////////////////////
	//  �ൿ.
	//////////////////////////////////////////////////////////////////////////

	AT_ATTACK1          = 120,
	AT_ATTACK2,

	AT_STAND1,
	AT_STAND2,
	AT_MOVE1,
	AT_MOVE2,

	AT_DAMAGE1,
	AT_DIE1,
	AT_SIT1,
	AT_POSE1,
	AT_HEALING1,
	AT_GREETING1,
	AT_GOODBYE1,
	AT_CLAP1,
	AT_GESTURE1,
	AT_DIRECTION1,
	AT_UNKNOWN1,
	AT_CRY1,
	AT_CHEER1,
	AT_AWKWARD1,
	AT_SEE1,
	AT_WIN1,
	AT_SMILE1,
	AT_SLEEP1,
	AT_COLD1,
	AT_AGAIN1,
	AT_RESPECT1,
	AT_SALUTE1,
	AT_RUSH1,
	AT_SCISSORS,	// ����
	AT_ROCK,		// ����
	AT_PAPER,		// ��
	AT_HUSTLE,		// �Ϻ� ������ ����
	AT_PROVOCATION,
	AT_LOOK_AROUND,
	AT_CHEERS,
#ifdef WORLDCUP_ADD
	AT_HANDCLAP,
	AT_POINTDANCE,
#endif
	AT_JACK1,		// �� �ൿ1
	AT_JACK2,		// �� �ൿ2
	AT_SANTA1_1,		// ��Ÿ �ൿ1
	AT_SANTA1_2,
	AT_SANTA1_3,
	AT_SANTA2_1,		// ��Ÿ �ൿ2
	AT_SANTA2_2,
	AT_SANTA2_3,
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	AT_RAGEBUFF_1,
	AT_RAGEBUFF_2,
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

	//////////////////////////////////////////////////////////////////////////
	//  ��Ʈ �ɼ�.
	//////////////////////////////////////////////////////////////////////////
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	AT_SET_OPTION_IMPROVE_STRENGTH              = AT_RAGEBUFF_2+1,  //	�� ����                         (��)	                
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	AT_SET_OPTION_IMPROVE_STRENGTH              = 140,  //	�� ����                         (��)	                
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	AT_SET_OPTION_IMPROVE_DEXTERITY,					//	��ø�� ����                     (��)		            
	AT_SET_OPTION_IMPROVE_ENERGY,						//	������ ����	                    (��)	                
	AT_SET_OPTION_IMPROVE_VITALITY,					    //	ü�� ����	                    (��)	                
	AT_SET_OPTION_IMPROVE_CHARISMA,					    //	��ַ� ����	                    (��)	                
	AT_SET_OPTION_IMPROVE_ATTACK_MIN,                   //  �ּ� ���ݷ� ����    
	AT_SET_OPTION_IMPROVE_ATTACK_MAX,                   //  �ִ� ���ݷ� ����
	AT_SET_OPTION_IMPROVE_MAGIC_POWER,                  //  ���� ����
	AT_SET_OPTION_IMPROVE_DAMAGE,		                //	������ ����
	AT_SET_OPTION_IMPROVE_ATTACKING_PERCENT,			//	���� ������ ����                (��)
	AT_SET_OPTION_IMPROVE_DEFENCE,				        //	���� ����                     (��)
	AT_SET_OPTION_IMPROVE_MAX_LIFE,					    //	�ִ� ����� ����
	AT_SET_OPTION_IMPROVE_MAX_MANA,					    //	�ִ� ���� ����
	AT_SET_OPTION_IMPROVE_MAX_AG,						//	�ִ� AG ����
	AT_SET_OPTION_IMPROVE_ADD_AG,					    //	AG ������ ����	                (��)
	AT_SET_OPTION_IMPROVE_CRITICAL_DAMAGE_PERCENT,      //  ũ��Ƽ�� ������ Ȯ�� ����
	AT_SET_OPTION_IMPROVE_CRITICAL_DAMAGE,              //  ũ��Ƽ�� ������ ����
	AT_SET_OPTION_IMPROVE_EXCELLENT_DAMAGE_PERCENT,     //  �׼���Ʈ ������ Ȯ�� ����
	AT_SET_OPTION_IMPROVE_EXCELLENT_DAMAGE,             //  �׼���Ʈ ������ ����
	AT_SET_OPTION_IMPROVE_SKILL_ATTACK,                 //  ��ų ���ݷ� ����
	AT_SET_OPTION_DOUBLE_DAMAGE,                        //	���� ������ Ȯ��
	AT_SET_OPTION_DISABLE_DEFENCE,                      //  �� ���� ����
	AT_SET_OPTION_IMPROVE_SHIELD_DEFENCE,               //  ���� ���� ���� ����.
	AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE,        //  ��հ� ���� ������ ����.
	
	AT_SET_OPTION_IMPROVE_ATTACK_2,						//	Ư�� ĳ���� ���ݷ� ���� ��/50   	(��)
	AT_SET_OPTION_IMPROVE_ATTACK_1,						//	Ư�� ĳ���� ���ݷ� ���� ��ø��/60	(��)
	AT_SET_OPTION_IMPROVE_DEFENCE_3,					//	Ư�� ĳ���� ���� ���� ��ø��/50	(��)
	AT_SET_OPTION_IMPROVE_DEFENCE_4,					//	Ư�� ĳ���� ���� ���� ü��/40	    (��)
	AT_SET_OPTION_IMPROVE_MAGIC,						//	Ư�� ĳ���� ���� ���� ������/70	    (��)
	AT_SET_OPTION_ICE_MASTERY,							//	Ư�� ĳ���� �����Ӽ� �߰�			    
	AT_SET_OPTION_POSION_MASTERY,						//	Ư�� ĳ���� ���Ӽ� �߰�			        
	AT_SET_OPTION_THUNDER_MASTERY,						//	Ư�� ĳ���� �����Ӽ� �߰�			    
	AT_SET_OPTION_FIRE_MASTERY,							//	Ư�� ĳ���� �ҼӼ� �߰�			        
	AT_SET_OPTION_EARTH_MASTERY,						//	Ư�� ĳ���� ���Ӽ� �߰�			        
	AT_SET_OPTION_WIND_MASTERY,							//	Ư�� ĳ���� �ٶ��Ӽ� �߰�			    
	AT_SET_OPTION_WATER_MASTERY,						//	Ư�� ĳ���� ���Ӽ� �߰�			        

	AT_IMPROVE_MAX_MANA,                                //  �ִ� ���� ���� �ɼ�. ( 1%, 2%, 3%, 4% )
	AT_IMPROVE_MAX_AG,                                  //  �ִ� AG���� �ɼ�. ( 1%, 2%, 3%, 4% )
};
//publicfile end

//npcbreederfile start
enum
{
	BREEDER_NONE    = 0 ,
	BREEDER_START       ,   //  ���ϴ� ��� ����â�� ����.
	BREEDER_RECOVERY    ,   //  ���� ȸ��â ����.
	BREEDER_REVIVAL     ,   //  ��ȥ ȯ��â ����.
//  BREEDER_UPGRADE     ,   //  ���׷��̵�â ����.
	BREEDER_END
};

enum
{
	REVIVAL_NONE    = 0 ,   //  ���� ���� no.
	REVIVAL_DARKHORSE   ,   //  ��ũȦ�� ȯ��.
	REVIVAL_DARKSPIRIT  ,   //  ��ũ���Ǹ� ȯ��.
#ifdef DARK_WOLF
	REVIVAL_DARKWOLF    ,   //  ��ũ���� ȯ��.
#endif// DARK_WOLF
	REVIVAL_END
};

enum
{
	REVIVAL_SUCCESS = 0 ,   //  ȯ�� ���� ����.
	REVIVAL_ERROR_ZEN   ,   //  ������.
	REVIVAL_ERROR_LEVEL ,   //  ��������.
	REVIVAL_ERROR_END   
};

enum
{
	ITEM_ETC_TYPE   = 0 ,
	ITEM_DARKHORSE      ,                    
	ITEM_DARKSPIRIT     ,
#ifdef DARK_WOLF
	ITEM_DARKWOLF       ,   
#endif// DARK_WOLF
	ITEM_BLESS_GEM      ,
	ITEM_SPIRIT_GEM     ,
	ITEM_CHAOS_GEM      ,
	ITEM_CREATING_GEM   ,
	ITEM_LIFE_GEM       ,
	ITEM_END
};
//npcbreederfile end

//gm_kanturu_2nd start
enum POPUP_MESSAGE
{
	POPUP_NONE = 0,
	POPUP_USER_OVER,	// ���� ������ �ο� �� �ʰ�
	POPUP_NOT_MUNSTONE,	// ������ ���Ʈ �����ϰ� �ִ� �ʴ�.
	POPUP_FAILED,		// ���� ������ ���°� �ƴ�
	POPUP_FAILED2,		// �̻��� ������ ����
	POPUP_UNIRIA = 5,	// ���ϸ��Ƹ� ž���ϰ� �̵� �Ұ�
	POPUP_CHANGERING,	// ���Ź��� �����ϸ� �̵� �Ұ�
	POPUP_NOT_HELPER,	// ����, ����, ����Ʈ, �渱, ��ũȣ���� ������ ���� ���� ���
};
//gm_kanturu_2nd end

//csquest start
enum    //  ����Ʈ Ÿ��.
{
	TYPE_QUEST = 0,         //  �⺻ ����Ʈ.
	TYPE_DEVIL_SQUARE,      //  �Ǹ��� ����.
	TYPE_BLOOD_CASTLE,      //  ����ĳ��.
	TYPE_CURSEDTEMPLE,      //  ȯ�����
	TYPE_QUEST_END
};

enum    //  ����Ʈ�� �����ִ� ���.
{
	QUEST_VIEW_NONE = 0,
	QUEST_VIEW_NPC,
	QUEST_VIEW_PREVIEW,
	QUEST_VIEW_END
};

enum    //
{
	QUEST_ITEM = 1,
	QUEST_MONSTER,
};

enum    //  ����Ʈ ����.
{
	QUEST_NONE = 0, //
	QUEST_ING = 1,  //  ����Ʈ ���� ����.
	QUEST_END,      //  ����Ʈ �Ϸ� ����.
	QUEST_NO,       //  ����Ʈ�� ���� ���� ����.
	QUEST_READY,    //  ����Ʈ ��� ����.
	QUEST_ERROR,    //  ���� ����.
};

enum	//	����Ʈ ����Ʈ.
{
	QUEST_CHANGE_UP_1 = 0,	//	1�� ���� ����Ʈ.
	QUEST_CHANGE_UP_2,		//	2�� ���� ����Ʈ.
	QUEST_CHANGE_UP_3,		//	3�� ���� ����Ʈ.
	QUEST_COMBO,			//	�޺� ����Ʈ.
	QUEST_3RD_CHANGE_UP_1,	//	3�� ���� ����Ʈ.
	QUEST_3RD_CHANGE_UP_2,	//	3�� ���� ����Ʈ.
	QUEST_3RD_CHANGE_UP_3,	//	3�� ���� ����Ʈ.
	QUEST_LIST_END
};
//csquest end

//cspetsystem start
enum
{
	PET_FLYING    = 0,
	PET_FLY          ,      //  �ϴ��� ����.
	PET_ESCAPE       ,      //  ȸ��.
	PET_STAND        ,      //  �տ� ���ִ´�.
	PET_STAND_START  ,      //  ���� ��ġ�� ������ �̵��� �Ѵ�.
	PET_ATTACK       ,      //  �� �� �����Ѵ�.
	PET_ATTACK_MAGIC ,      //  Ư�� ����1.
	PET_END
};


enum    PET_TYPE
{
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	PET_TYPE_NONE		 = -1,	// ���� ������,
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
	PET_TYPE_DARK_SPIRIT = 0,   //  ��ũ ���Ǹ�.
	PET_TYPE_DARK_HORSE,        //  ��ũ ȣ��.
//	PET_TYPE_DARK_WOLF,         //  ��ũ ����. (������)
	PET_TYPE_END
};


enum    PET_COMMAND
{
	PET_CMD_DEFAULT = 0 ,   //  �⺻ ����.
	PET_CMD_RANDOM      ,   //  ���� ����.
	PET_CMD_OWNER       ,   //  ���ΰ� ���� ����.
	PET_CMD_TARGET      ,   //  Ÿ�ϰ���.
	PET_CMD_END
};
//cspetsystem end

//csparts start
enum    
{
#ifdef LJW_FIX_PARTS_ENUM
	PARTS_NONE = 0,
	PARTS_START,
	PARTS_STAFF = PARTS_START,
	PARTS_SWORD,
	PARTS_BOW,
#endif // LJW_FIX_PARTS_ENUM
	PARTS_LION = 4,
	PARTS_WEBZEN,
	PARTS_ATTACK_TEAM_MARK,
	PARTS_ATTACK_TEAM_MARK2,
	PARTS_ATTACK_TEAM_MARK3,
	PARTS_ATTACK_KING_TEAM_MARK,
	PARTS_ATTACK_KING_TEAM_MARK2,
	PARTS_ATTACK_KING_TEAM_MARK3,
	PARTS_DEFENSE_TEAM_MARK,
	PARTS_DEFENSE_KING_TEAM_MARK,
	PARTS_END
};
//csparts end

//csmapinterface start
enum
{
	TYPE_OBSERVER = 0,
	TYPE_GUILD_SOLDIER,
	TYPE_GUILD_COMMANDER
};
//csmapinterface end

//csitemsetoption start
enum
{
	SET_OPTION_NONE = 0,        //  �ɼ��� ����.
	SET_OPTION_STRENGTH,        //  �� �ɼ� ����.
	SET_OPTION_DEXTERITY,       //  ��ø �ɼ� ����.
	SET_OPTION_ENERGY,          //  ������ �ɼ� ����.
	SET_OPTION_VITALITY,        //  ü�� �ɼ� ����.
	SET_OPTION_END
};
//csitemsetoption start


//cseventmatch start
enum  MATCH_TYPE
{
	TYPE_MATCH_NONE = 0,
	TYPE_MATCH_DEVIL_ENTER_START,   //  �Ǹ��Ǳ��� �������
	TYPE_MATCH_DEVIL_ENTER_CLOSE,   //  �Ǹ��Ǳ��� ���帶��
	TYPE_MATCH_DEVIL_CLOSE,         //  �Ǹ��Ǳ��� �м�
	TYPE_MATCH_CASTLE_ENTER_CLOSE,  //  ����ĳ�� ���帶��
	TYPE_MATCH_CASTLE_INFILTRATION, //  ����ĳ�� ����
	TYPE_MATCH_CASTLE_CLOSE,        //  ����ĳ�� ��� ����
	TYPE_MATCH_CASTLE_END,          //  ����ĳ�� ��� �м�
	TYPE_MATCH_CHAOS_ENTER_START = 11,  //  ī���� ĳ�� �������
	TYPE_MATCH_CHAOS_EINFILTRATION,     //  ī���� ĳ�� ����
	TYPE_MATCH_CHAOS_CLOSE,             //  ī���� ĳ�� ����
	TYPE_MATCH_CHAOS_END,               //  ī���� ĳ�� �м�
	TYPE_MATCH_CURSEDTEMPLE_ENTER_CLOSE, 
	TYPE_MATCH_CURSEDTEMPLE_GAME_START, 
#ifdef YDG_ADD_DOPPELGANGER_UI
	TYPE_MATCH_DOPPELGANGER_ENTER_CLOSE,
	TYPE_MATCH_DOPPELGANGER_GAME_START,
	TYPE_MATCH_DOPPELGANGER_ICEWALKER,
	TYPE_MATCH_DOPPELGANGER_CLOSE,
#endif	// YDG_ADD_DOPPELGANGER_UI
	TYPE_MATCH_END
};

enum
{
	MATCH_TYPE_NONE_EVENT = 0,
	MATCH_TYPE_DEVIL_SQUARE,
	MATCH_TYPE_BLOOD_CASTLE,
	MATCH_TYPE_END
};
//cseventmatch end

// ���â
enum COMMAND_TYPE
{
	COMMAND_NONE  = -1, //  �ʱⰪ.
	COMMAND_TRADE = 0,  //  �ŷ�.
	COMMAND_PURCHASE,	//  ����.
	COMMAND_PARTY,      //  ��Ƽ.
	COMMAND_WHISPER,    //  �ӼӸ�.
	COMMAND_GUILD,      //  ���.
	COMMAND_GUILDUNION,	//  ��忬��.
	COMMAND_RIVAL,		//  ������.
	COMMAND_RIVALOFF,	//  ����������.
	COMMAND_ADD_FRIEND, //  ģ���߰�.
	COMMAND_FOLLOW,     //  ���󰡱�.
	COMMAND_BATTLE,     //  ����.
#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
	COMMAND_PCBANG,		// PC�� ����Ʈ ����.
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
	COMMAND_END
};


//cmvp1stdirection start

enum CRYWOLF_OCCUPATION_STATE_TYPE			  // ũ���� ���� �� ����
{
	CRYWOLF_OCCUPATION_STATE_PEACE		= 0,  // ��ȭ����
	CRYWOLF_OCCUPATION_STATE_OCCUPIED	= 1,  // ���ɻ���
	CRYWOLF_OCCUPATION_STATE_WAR		= 2,  // �������
};

enum CRYWOLF_STATE_TYPE						  // ũ���� ���� ���� ����
{
	CRYWOLF_STATE_NONE					= 0,  // NONE
	CRYWOLF_STATE_NOTIFY_1				= 1,  // ���� 1
	CRYWOLF_STATE_NOTIFY_2				= 2,  // ���� 2
	CRYWOLF_STATE_READY					= 3,  // �غ�
	CRYWOLF_STATE_START					= 4,  // ����
	CRYWOLF_STATE_END					= 5,  // ����
	CRYWOLF_STATE_ENDCYCLE				= 6,  // ���� �� �ֱ� ����� �غ�
};

enum CRYWOLF_ALTAR_STATE					  // ������ ���� ����
{
	CRYWOLF_ALTAR_STATE_NONE					= 0,  // ��� ���� �ƴ�
	CRYWOLF_ALTAR_STATE_CONTRACTED				= 1,  // ��� ��ä ����
	CRYWOLF_ALTAR_STATE_APPLYING_CONTRACT		= 2,  // ����� �õ� ����
	CRYWOLF_ALTAR_STATE_EXCEEDING_CONTRACT_COUNT= 3,  // ��� Ƚ���� �ʰ�����
	CRYWOLF_ALTAR_STATE_OCCUPYING				= 4,  // ���� ������ �õ� ���̴�
	CRYWOLF_ALTAR_STATE_OCCUPIED				= 5,  // ������ ���� �Ǿ���
};

//cmvp1stdirection end

//ckanturudirection start
enum KANTURU_STATE_TYPE				  // ĭ���� ���� ����
{
	KANTURU_STATE_NONE				= 0,  // NONE
	KANTURU_STATE_STANDBY			= 1,  // ĭ���� �غ�
	KANTURU_STATE_MAYA_BATTLE		= 2,  // ���� ����
	KANTURU_STATE_NIGHTMARE_BATTLE	= 3,  // ����Ʈ�޾� ����
	KANTURU_STATE_TOWER				= 4,  // ������ ž
	KANTURU_STATE_END				= 5,  // ��

};

enum KANTURU_MAYA_DIRECTION_TYPE
{
	KANTURU_MAYA_DIRECTION_NONE				= 0,
	KANTURU_MAYA_DIRECTION_STANBY1			= 1,
	KANTURU_MAYA_DIRECTION_NOTIFY			= 2,
	KANTURU_MAYA_DIRECTION_MONSTER1			= 3,
	KANTURU_MAYA_DIRECTION_MAYA1			= 4,
	KANTURU_MAYA_DIRECTION_END_MAYA1		= 5,
	KANTURU_MAYA_DIRECTION_ENDCYCLE_MAYA1	= 6,
	KANTURU_MAYA_DIRECTION_STANBY2			= 7,
	KANTURU_MAYA_DIRECTION_MONSTER2			= 8,
	KANTURU_MAYA_DIRECTION_MAYA2			= 9,
	KANTURU_MAYA_DIRECTION_END_MAYA2		= 10,
	KANTURU_MAYA_DIRECTION_ENDCYCLE_MAYA2	= 11,
	KANTURU_MAYA_DIRECTION_STANBY3			= 12,
	KANTURU_MAYA_DIRECTION_MONSTER3			= 13,
	KANTURU_MAYA_DIRECTION_MAYA3			= 14,
	KANTURU_MAYA_DIRECTION_END_MAYA3		= 15,
	KANTURU_MAYA_DIRECTION_ENDCYCLE_MAYA3	= 16,
	KANTURU_MAYA_DIRECTION_END				= 17,
	KANTURU_MAYA_DIRECTION_ENDCYCLE			= 18,
};

enum KANTURU_NIGHTMARE_DIRECTION_TYPE
{
	KANTURU_NIGHTMARE_DIRECTION_NONE		= 0,
	KANTURU_NIGHTMARE_DIRECTION_IDLE		= 1,
	KANTURU_NIGHTMARE_DIRECTION_NIGHTMARE	= 2,
	KANTURU_NIGHTMARE_DIRECTION_BATTLE		= 3,
	KANTURU_NIGHTMARE_DIRECTION_END			= 4,
	KANTURU_NIGHTMARE_DIRECTION_ENDCYCLE	= 5,
};

enum KANTURU_TOWER_STATE_TYPE
{
	KANTURU_TOWER_NONE						= 0,
	KANTURU_TOWER_REVITALIXATION			= 1,
	KANTURU_TOWER_NOTIFY					= 2,
	KANTURU_TOWER_CLOSE						= 3,
	KANTURU_TOWER_NOTIFY2					= 4,
	KANTURU_TOWER_END						= 5,
	KANTURU_TOWER_ENDCYCLE					= 6,
};
//ckanturudirection end

//ccomgem start
namespace COMGEM
{
	enum	_METHOD			//â�� ��ɺз� - ����/��ü
	{
		ATTACH	= 0,
		DETACH
	};

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	enum	eGEMTYPE		//������ ����
	{
		eNOGEM = -1,
		eBLESS = 0,		
		eBLESS_C,

		eSOUL, 
		eSOUL_C, 

		eLIFE,		
		eLIFE_C,

		eCREATE, 
		eCREATE_C, 

		ePROTECT,	
		ePROTECT_C,	

		eGEMSTONE, 
		eGEMSTONE_C, 

		eHARMONY,	
		eHARMONY_C,	

		eCHAOS, 
		eCHAOS_C, 

		eLOW,		
		eLOW_C,		

		eUPPER, 		
		eUPPER_C, 

		eGEMTYPE_END = 10,
		eGEMTYPE_END_ALL = 20,
	};
	enum eGEMINDEXTYPE
	{
		eGEM_NAME, eGEM_INDEX, eGEM_END
	};
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

	enum	_GEMTYPE		//������ ����
	{
		NOGEM = -1,
		CELE = 0,			//�ູ�� ����
		SOUL = 1,			//��ȥ�� ����
		COMCELE = 2,		//���յ� �ູ�� ����
		COMSOUL= 3			//���յ� ��ȥ�� ����
	};

	enum	_COMTYPE		//������ ������ ����
	{
		NOCOM = -1,
		FIRST	= 10,
		SECOND	= 20,
		THIRD	= 30
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		,eCOMTYPE_END = 3
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	};

	enum	_STATE			//���� â�� ����
	{
		STATE_READY,		//���� ��
		STATE_HOLD,			//������ ���� �����
		STATE_END			//���� ��
	};

	enum	_ERRORTYPE
	{
		NOERR = 0,
		POPERROR_NOTALLOWED,		//�������� ������ â�� ��� �õ�
		COMERROR_NOTALLOWED,		//�������� ������ ���� �õ�
		DEERROR_SOMANY,			//�ʹ� ���Ƽ� ��ü �Ұ���
		DEERROR_NOTALLOWED,		//�������� ������ ��ü �õ�
		ERROR_UNKNOWN,
		ERROR_ALL
	};

};
//ccomgem end

#ifdef FIX_MIX_NOT_PICKING_BUG
enum eMixState
{
	eMixState_MixFunctionPossibility = 0,     //���� ����� �� �� �� �ִ�..
	eMixState_MixFunctionImpossibility,       //���������� ���� �޼����� ������ ��� ������ ����� ���� �� �� �ִ�
	eMixState_MixEnd,
};
#endif //FIX_MIX_NOT_PICKING_BUG

enum ITEM_COLORSTATE
{
	ITEM_COLOR_NORMAL = 0,
	ITEM_COLOR_DURABILITY_50,
	ITEM_COLOR_DURABILITY_70,
	ITEM_COLOR_DURABILITY_80,
	ITEM_COLOR_DURABILITY_100,
	ITEM_COLOR_TRADE_WARNING,
};

enum eCursorType
{
	CURSOR_NORMAL = 0,
	CURSOR_PUSH,
	CURSOR_ATTACK,
	CURSOR_GET,
	CURSOR_TALK,
	CURSOR_REPAIR,
	CURSOR_LEANAGAINST,
	CURSOR_SITDOWN,
	CURSOR_DONTMOVE,
	CURSOR_IDSELECT,
};

// Skill.txt (Skill.Bmd)���Ͽ� "��ų Ÿ��" Column ���� ����.
#ifdef LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER
enum eTypeSkill
{
	eTypeSkill_None = -1,
		eTypeSkill_CommonAttack,	// 0 �Ϲ� ����	
		eTypeSkill_Buff,			// 1 ����
		eTypeSkill_DeBuff,			// 2 �����
		eTypeSkill_FrendlySkill,	// 3 ��Ÿ �Ʊ� ģȭ�� ��ų (�� ���� ��ų)
		eTypeSkill_End,
};
#endif // LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER

enum eBuffClass
{
	eBuffClass_Buff = 0,
	eBuffClass_DeBuff,

	eBuffClass_Count,
};

enum eBuffState
{
	eBuffNone        = 0,           // ������ ���� �Ⱦ�                                            STATE_NONE
	// Buff
	eBuff_Attack,				    // ���ݷ� ���                                                 STATE_ATTACK
	eBuff_Defense,					// ���� ���                                                 STATE_DEFENSE
	eBuff_HelpNpc,                  // ������ ����                                                 STATE_HELPER_DEFENSE

	//eBuff_HpRecovery == eBuff_Life ���� �ε���
	//eBuff_Life,						// ����� ���                                                 STATE_ADD_VITALITY
	eBuff_PhysDefense,				// ���� ���� ��( ���� )                                    STATE_PHYS_DEF
	eBuff_AddCriticalDamage,		// ũ��Ƽ�� ������ ���                                        STATE_ADD_CRITICAL_DMG
	eBuff_InfinityArrow,            // ���Ǵ�Ƽ ���ο�									           STATE_INFINITY_ARROW      xxxxxx
	eBuff_AddAG,					// AG �����ӵ� ���                                            STATE_ADD_AG
	eBuff_HpRecovery,               // ü�� ����                                                   STATE_HP_RECOVERY
	eBuff_AddMana     ,             // ���� ���                                                   STATE_ADD_MANA
	eBuff_BlessPotion,              // �ູ�� ���� ���� ����                                       STATE_BLESS_POTION
	eBuff_SoulPotion,               // ��ȥ�� ���� ���� ����                                       STATE_SPIRIT_POTION
	eBuff_RemovalMagic,             // ���� ���� ( �������� ���� �����? Ȥ�� ���� )               STATE_REMOVAL_MAGIC
	eBuff_CastleGateIsOpen,         // ���� ���� ������ ����                                       STATE_GATE_OPEN
	eBuff_CastleRegimentDefense,    // ���� ������                                                 STATE_REGIMENT_DEFENSE
	eBuff_CastleRegimentAttack1,    // ���� ������ 1                                               STATE_REGIMENT_ATTACK
	eBuff_CastleRegimentAttack2,    // ���� ������ 2                                               STATE_REGIMENT_ATTACK2
	eBuff_CastleRegimentAttack3,    // ���� ������ 3                                               STATE_REGIMENT_ATTACK3
	eBuff_Cloaking,                 // ����                                                        STATE_INVISIBLE
	eBuff_AddSkill		,		    // �߰� ��ų�� ���� �ϴ� ����( ��ũ �ε� ���� ��ų )           STATE_SKILL_BUFF
	eBuff_CastleCrown,              // ���� �հ� ��� �� ���� ( STATE_GATE_OPEN�� Index�� ���� ) ================  X
	eBuff_CrywolfAltarEnable,       // ũ���̿��� ������ ���� ONLY - ��� ���� ����                STATE_CRYWOLF_ALTAR_ENABLE
	eBuff_CrywolfAltarDisable,      // ũ���̿��� ������ ���� ONLY - ��� �Ҵ� ����                STATE_CRYWOLF_ALTAR_DISABLE
	eBuff_CrywolfAltarContracted,   // ũ���̿��� ������ ���� ONLY - ��� �Ǿ� �ִ� ����           STATE_CRYWOLF_ALTAR_CONTRACTED
	eBuff_CrywolfAltarAttempt,      // ũ���̿��� ������ ���� ONLY - ��� �õ� ����                STATE_CRYWOLF_ALTAR_ATTEMPT
	eBuff_CrywolfAltarOccufied,     // ũ���̿��� ������ ���� ONLY - ���� ���� ����                STATE_CRYWOLF_ALTAR_OCCUFIED 
	eBuff_CrywolfHeroContracted,    // ũ���̿��� ����� ��� ���� ����                            HERO_ALTAR_CONTRACTED
	eBuff_CrywolfNPCHide,           // ũ���̿��� ONLY - NPC HIDE ����                             STATE_CRYWOLF_NPC_HIDE
	eBuff_GMEffect,                 // GM ȿ��                                                     STATE_GM_EFFECT
	eBuff_PcRoomSeal1,				// Pc�� ���� 1                                                 STATE_SEAL1
	eBuff_PcRoomSeal2,              // Pc�� ���� 2                                                 STATE_SEAL2
	eBuff_PcRoomSeal3,              // Pc�� ���� 3                                                 STATE_SEAL3
	eBuff_CursedTempleQuickness,    // �ż��� ��ų 	                                               STATE_CURSED_TEMPLE_QUICKNESS
	eBuff_CursedTempleSublimation,	// ��ȭ�� �ֹ�												   STATE_CURSED_TEMPLE_SUBLIMATION
	eBuff_CursedTempleProdection,   // ��ȣ�� ��ų								                   STATE_CURSED_TEMPLE_PRODECTION
	eBuff_Hellowin1,                // ��������� �ູ											   STATE_HELLOWIN_1
	eBuff_Hellowin2,                // ��������� �г�                                             STATE_HELLOWIN_2
	eBuff_Hellowin3,                // ��������� ��ħ                                             STATE_HELLOWIN_3
	eBuff_Hellowin4,                // ��������� ����                                             STATE_HELLOWIN_4
	eBuff_Hellowin5,				// ��������� ����                                             STATE_HELLOWIN_5
//	eBuff_LuckSeal,                 // ����( ����θ� ������ ������ ���� ĳ����)                   STATE_LUCK_SEAL
	eBuff_Seal1,                    // ���� 1                                                      STATE_SEAL1
	eBuff_Seal2,                    // ���� 2                                                      STATE_SEAL2
	eBuff_Seal3,                    // ���� 3                                                      STATE_SEAL3
	eBuff_Seal4,                    // ���� 4                                                      STATE_SEAL4
	eBuff_EliteScroll1,				// �ż�                                                        STATE_ELITE_SCROLL1
	eBuff_EliteScroll2,				// ���                                                        STATE_ELITE_SCROLL2
	eBuff_EliteScroll3,				// �г�                                                        STATE_ELITE_SCROLL3
	eBuff_EliteScroll4,				// ����                                                        STATE_ELITE_SCROLL4
	eBuff_EliteScroll5,				// ü��                                                        STATE_ELITE_SCROLL5
	eBuff_EliteScroll6,				// ����                                                        STATE_ELITE_SCROLL6
	eBuff_SecretPotion1,            // ��                                                          STATE_ELITE_SECRET1
	eBuff_SecretPotion2,            // ��ø                                                        STATE_ELITE_SECRET2
	eBuff_SecretPotion3,            // ü��                                                        STATE_ELITE_SECRET3
	eBuff_SecretPotion4,            // ������                                                      STATE_ELITE_SECRET4
	eBuff_SecretPotion5,            // ���                                                        STATE_ELITE_SECRET5
	
	// DeBuff
	eDeBuff_Poison,						// �� �ɸ� ����                                                STATE_POISON
	eDeBuff_Freeze,						// ���� �ɸ� ����                                              STATE_FREEZE
	eDeBuff_Harden,						// ��ȭ�� ����                                                 STATE_PARALYZE
	eDeBuff_Defense,					// ���� ����( ���˻� )                                       STATE_REDUCE_DEF
	eDeBuff_Attack,						// ���ݷ� ����( ���� ) ( Ŭ�󿡼� ���� ���� )
	eDeBuff_MagicPower,					// ���� ���� ( Ŭ�󿡼� ���� ���� )
	eDeBuff_Stun,						// ���Ͽ� �ɸ� ����                                            STATE_STUN
	eDeBuff_InvincibleMagic,			// ���� ��� ����( �� ���׸� )                                 STATE_ABSOLUTE_DEF
	eDeBuff_InvincibleMagicAttack,		// ���� ���� ���� ���� ���� ȿ��
	eDeBuff_InvinciblePhysAttack,       // ���� ���� ���� ���� ���� ȿ�� 
	eDeBuff_CursedTempleRestraint,      // �ӹ� ��ų								                   STATE_CURSED_TEMPLE_RESTRAINT
	// ������ eBuff ���̰�, ������� eDeBuff �ٿ��ּ��� ^^

	eBuff_CrywolfProdection1, 
	eBuff_CrywolfProdection2, 
	eBuff_CrywolfProdection3, 
	eBuff_CrywolfProdection4, 
	eBuff_CrywolfProdection5, 

	// ��ȯ���� ���� ���� ��ų
	eBuff_Thorns		= 71,	// ����(����)
	eDeBuff_Sleep		= 72,	// ����(�����)
	eDeBuff_Blind		= 73,	// ����ε�(�����)
	eDeBuff_NeilDOT		= 74,	// ��ȯ�� �� DOT (����)
	eDeBuff_SahamuttDOT = 75,	// ��ȯ�� ���Ϲ�Ʈ DOT (����)
	eDeBuff_AttackDown	= 76,	// ��ũ�Ͻ�
	eDeBuff_DefenseDown = 77,	// �̳ʺ��̼�
#ifdef CSK_EVENT_CHERRYBLOSSOM
	eBuff_CherryBlossom_Liguor,	// ���ɼ�
	eBuff_CherryBlossom_RiceCake,// ���ɰ��
	eBuff_CherryBlossom_Petal,	// ���ɲ���
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef ASG_ADD_SKILL_BERSERKER
	eBuff_Berserker		= 81,	// ����Ŀ
#endif	// ASG_ADD_SKILL_BERSERKER
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	eBuff_SwellOfMagicPower	= 82,	// �������� (����)
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	eDeBuff_FlameStrikeDamage	= 83,	// �÷��ӽ�Ʈ����ũ ������
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	eDeBuff_GiganticStormDamage	= 84,	// �Ⱓƽ���� ������
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK
	eDeBuff_LightningShockDamage = 85,	// ����Ʈ�׼�ũ ������
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	eDeBuff_BlowOfDestruction = 86,		// �ı����ϰ� ������
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef PSW_ADD_PC4_SEALITEM
	eBuff_Seal_HpRecovery = 87,         // ü���� ����( �κ�4�� ), eBuffTime_Seal ���� ���� �ȴ�
	eBuff_Seal_MpRecovery = 88,         // ������ ����( �κ�4�� ), eBuffTime_Seal ���� ���� �ȴ�
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
	eBuff_Scroll_Battle = 89,           // ���� ��ũ��( �κ�4�� ), eBuffTime_Scroll ���� ���� �ȴ�
	eBuff_Scroll_Strengthen = 90,       // ��ȭ ��ũ��( �κ�4�� ), eBuffTime_Scroll ���� ���� �ȴ�
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PBG_ADD_SANTABUFF
	eBuff_BlessingOfXmax = 91,		//ũ�����������ູ	index 91
	eBuff_CureOfSanta,				//��Ÿ��ġ��		index 92
	eBuff_SafeGuardOfSanta,			//��Ÿ�Ǻ�ȣ		index 93
	eBuff_StrengthOfSanta,			//��Ÿ�ǰ�ȭ		index 94
	eBuff_DefenseOfSanta,			//��Ÿ�ǹ��		index 95
	eBuff_QuickOfSanta,				//��Ÿ�ǽż�		index 96
	eBuff_LuckOfSanta,				//��Ÿ�����		index 97
#endif //PBG_ADD_SANTABUFF
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
	eBuff_DuelWatch = 98,			// ���� �������
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF
#ifdef ASG_ADD_CS6_GUARD_CHARM
	eBuff_GuardCharm = 99,				// ��ȣ�Ǻ���
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	eBuff_ItemGuardCharm = 100,			// �����ۺ�ȣ����
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
	eBuff_AscensionSealMaster = 101,	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
	eBuff_WealthSealMaster = 102,		// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
	eBuff_HonorOfGladiator = 103,		// �������� ��
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	eBuff_StrongCharm = 104,			// ������ ����
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	eBuff_Doppelganger_Ascension = 105,	// ���ð��� ��õ
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
	eDeBuff_MoveCommandWin = 106,		// PK�г�Ƽ
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#ifdef PBG_ADD_SECRETBUFF
	eDeBuff_Fatigue_FirstPenalty = 107,	// �Ƿ���1
	eDeBuff_Fatigue_SecondPenalty = 108,// �Ƿ���2
#endif //PBG_ADD_SECRETBUFF
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	eBuff_PartyExpBonus = 112,			// ��Ƽ ����ġ ����
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef PBG_ADD_AURA_EFFECT
	eBuff_AG_Addition = 113,			// AG���� ����
	eBuff_SD_Addition = 114,			// SD���� ����
#endif //PBG_ADD_AURA_EFFECT
#ifdef PBG_ADD_SECRETBUFF
	eBuff_Vitality_Lowest = 115,		// ���ϱ�Ȱ��
	eBuff_Vitality_Low = 116,			// �ϱ�Ȱ��
	eBuff_Vitality_Middle = 117,		// �߱�Ȱ��
	eBuff_Vitality_High = 118,			// ���Ȱ��
#endif //PBG_ADD_SECRETBUFF
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	eBuff_NewWealthSeal = 119,
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef YDG_ADD_GM_DISCHARGE_STAMINA_DEBUFF
	eDeBuff_Discharge_Stamina = 120,	// GM�� �Ŵ� ���¹̳� ���� �����
#endif	// YDG_ADD_GM_DISCHARGE_STAMINA_DEBUFF
#ifdef YDG_ADD_HEALING_SCROLL
	eBuff_Scroll_Healing = 121,			// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	eBuff_Att_up_Ourforces = 129,		// ���ݼ����� ���
	eBuff_Hp_up_Ourforces = 130,		// ü�»��
	eBuff_Def_up_Ourforces = 131,		// ������ ���
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	eBuff_Count,
};

// ������ �ð��� ��� ���� ���⿡ �߰��� �ϸ� �ȴ�.
// BuffTimeControl ���⿡ �߰��� ����� �Ѵ�. <------- �� �κе� ��ũ��Ʈ�� ������ �ϴ���....-=-
enum eBuffTimeType 
{ 
	eBuffTime_None = 0, 
	eBuffTime_Hellowin = 1006, 
	eBuffTime_PcRoomSeal, 
	eBuffTime_Seal, 
	eBuffTime_Scroll, 
	eBuffTime_Secret,
#ifdef CSK_EVENT_CHERRYBLOSSOM
	eBuffTime_CherryBlossom,
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	eBuffTime_SwellOfMP,
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef PBG_ADD_SANTABUFF
	eBuffTime_Christmax,
#endif //PBG_ADD_SANTABUFF
#ifdef PBG_ADD_HONOROFGLADIATORBUFFTIME
	eBuffTime_HonorOfGladiator,
#endif //PBG_ADD_HONOROFGLADIATORBUFFTIME
#ifdef ASG_ADD_CS6_GUARD_CHARM
	eBuffTime_GuardCharm,
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	eBuffTime_ItemGuardCharm,
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	eBuffTime_ItemStrongCharm,				// ������ ���� (PC�� ������)
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef PBG_ADD_SECRETBUFF
	eBuffTime_Vitality,
#endif //PBG_ADD_SECRETBUFF
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	eBuffTime_AG_Addition,
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	eBuffTime_SD_Addition,
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	eBuffTime_PartyExpBonus,
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	eBuffTime_Count,
};

// value�κ��� ���� �Ҷ� � ���Ͽ��� ���� ������ �����Ѵ�.
enum eBuffValueLoadType
{
	eBuffValueLoad_None = 0,
	eBuffValueLoad_Skill,
	eBuffValueLoad_Item,
	eBuffValueLoad_Text,
	eBuffValueLoad_ItemAddOption,

	eBuffValueLoad_Count,
};

#define BUFFINDEX( buff )				static_cast<eBuffState>(buff)
#define BUFFTIMEINDEX( timetype )		static_cast<eBuffTimeType>(timetype)
#define ITEMINDEX( type, index )        static_cast<DWORD>((type*MAX_ITEM_INDEX)+index)

#ifdef NEW_COMMANDS

//client enums
enum eShopType
{
	eShop_NoCharge,                 //�������
	eShop_PartCharge,				//�κ��������
	eShop_Count,
};

enum eHighCategoryType
{
	eHighCategory_None = 0,         //0 = ī�װ��� ���°��� ����
	eHighCategory_NewItem,		    //������
	eHighCategory_OldItem,			//�ӽ�
	eHighCategory_MyItem,			//�� ������
	eHighCategory_Count,
};

enum eLowCategoryType
{
	eLowCategory_None = 0,			//0 = ī�װ��� ���°��� ����
	eLowCategory_All,				//��������ü
	eLowCategory_NewItem,			//��������
	eLowCategory_BestItem,			//����Ʈ������
	eLowCategory_DiscountItem,		//��ī��Ʈ������
	eLowCategory_Count,
};

enum eSortType
{
	eSort_ClassAll = 0,
	eSort_Class_Wizard,				//�渶����		  1
	eSort_ClassKnight,				//����		  2
	eSort_ClassElf,					//����            3
	eSort_ClassDark,				//���˻�          4
	eSort_ClassDarkLord,			//��ũ�ε�        5

	eSort_ClassSoulMaster = 9,		//�ҿ︶����	  6   1-1
	eSort_ClassBladeKnight,			//���̵峪��Ʈ  7   2-1
	eSort_ClassMuzElf,				//�����        8   3-1

	eSort_ClassCount,
};



enum eCashShopResult
{
	//���� Ŭ�� ����.
	eCashShop_Success = 0,									// ����, ���� ���� ��� ����
	eCashShop_Fail_NotEnoughCash,							// ���� ���� (ĳ�� �ܾ� ����)
	eCashShop_Fail_NotEmptySpace,							// ���� ���� (�κ��丮 ���� ����)
	eCashShop_Fail_NotFoundItem,							// ���� ���� (��ġ�ϴ� ������ ������ ����)
	eCashShop_Fail_AlreadyHaveItem,							// ���� ���� (�ߺ� ���� �Ұ����� �������� ����)
	eCashShop_Fail_DbError,									// ���� ���� (DB ����)
	eCashShop_Fail_ShopserverDisconnect,					// ���� ���� (�� �������� ������ ��������)
	eCashShop_Fail_ShopErrror,								// ���� ���� (�� �����κ��� �̻��� ���� Ȯ��)
	eCashShop_Fail_OpenCashShop,							// ���� ���� �ݱ� ����
	eCashShop_Fail_ETC,										// ���� ���� (��Ÿ)

	//fail Message�� �ƴ�( Ŭ���̾�Ʈ ���� )
	eCashShop_ItemEqual,
	eCashShop_NotItem,
	eCashShop_Count,
};

enum eMessageBoxType
{
    eMB_OK,
    eMB_YESNO,
    eMB_OKCANCEL,
};

/*
enum eBottomCategoryType
{
	//0 = ī�װ��� ���°��� ����
	eBottomCategory_Weapon = 1,		//����
	eBottomCategory_Armor,			//��
	eBottomCategory_Supplies,		//�Ҹ�
	eBottomCategory_Pet,			//��
	eBottomCategory_Ability,		//��ɼ�
	eBottomCategory_Count,
};
*/

#endif //NEW_COMMANDS

#ifdef CSK_FREE_TICKET
enum
{
	FREETICKET_TYPE_DEVILSQUARE = 0,
	FREETICKET_TYPE_BLOODCASTLE,
	FREETICKET_TYPE_KALIMA,
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	FREETICKET_TYPE_CURSEDTEMPLE,
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE
	FREETICKED_TYPE_CHAOSCASTLE,
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	FREETICKED_TYPE_DOPPLEGANGGER,
	FREETICKED_TYPE_BARCA,
	FREETICKED_TYPE_BARCA7TH,
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
};
#endif // CSK_FREE_TICKET

#ifdef ADD_SOCKET_ITEM
// Ȱ�� Ÿ���� ����
// zzzCharacter::GetEquipedBowType() ���� ���
enum eTYPEBOW
{
	BOWTYPE_NONE = 0,
	BOWTYPE_BOW,
	BOWTYPE_CROSSBOW,	
};
#endif // ADD_SOCKET_ITEM


#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING

// �ҽ� �۾��߿� ��ũ��Ʈ �������� ���� �߰� ���� ����. 
#define ITEM_TYPE_CHARM_MIXWING		ITEM_HELPER
#define MODEL_TYPE_CHARM_MIXWING	MODEL_HELPER

enum E_WINGMIXCHAR_SEQUENCE
{
	EWS_KNIGHT_1_CHARM	= 83,
	EWS_MAGICIAN_1_CHARM,
	EWS_ELF_1_CHARM,
	EWS_SUMMONER_1_CHARM,
	EWS_DARKLORD_1_CHARM,
	EWS_KNIGHT_2_CHARM,
	EWS_MAGICIAN_2_CHARM,
	EWS_ELF_2_CHARM,
	EWS_SUMMONER_2_CHARM,
	EWS_DARKKNIGHT_2_CHARM,
	EWS_BEGIN = 83,
	EWS_END = EWS_BEGIN + 10,
};
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
