#ifndef __WINMAIN_H__
#define __WINMAIN_H__


//!! ��ġ�� �ּ� ó�� �ؾ� ��
/*-------------------- ���α׷� mode ���� ----------------------------------------------*/
#define FOR_LAST_TEST			// ���� �׽�Ʈ �� ���� (���� �ø��� ����)
#define FOR_WORK				// �系 �۾��� ���� (Alt-Tab ����)
#define FOR_HACKING				// ��ŷ���� ���� (Ŭ���̾�Ʈ ���� ���� ����)
/*--------------------------------------------------------------------------------------*/

//////////// �߿�!!!!! - ������ //////////////////////////////////////////////////////////////////////////////////
//	- ������ �׼� ��ġ�� �׽� �� ������ �� ���ݽô�. ^^ ������ �Ʒ��ִ� ������ ���� ��ġ�� ������				//
//	  exe ������ ���� �ʿ䰡 �������� �����͸� ��ġ�� ���������� ���� ���� ��ġ�� �ʿ� �������� �����Դϴ� ^^	//
//    �׽� �� �ӽô�.																							//
//////////// �߿�!!!!! - ������ //////////////////////////////////////////////////////////////////////////////////


//�׼��ÿ��� MuTest.ini�� �е��� �� �־�� �Ѵ�. 
#ifdef _TEST_SERVER	// �߿�!!!!! - ������ ���� ���� �о� �ּ���
	#define USE_MUTEST_INI	//MuTest ȣ��(�׼� ���Ӱ������)-> �׻� Ų��.
	#define USE_TEXTTEST_BMD
	#define USE_ITEMTEST_BMD
	#define USE_SKILLTEST_BMD
	#define USE_GATETEST_BMD
	#define USE_PLAYERTEST_BMD
	#define USE_QUESTTEST_BMD
	#define USE_DIALOGTEST_BMD
	#define USE_SET_ITEMTEST_BMD
	#define USE_MOVEREQTEST_BMD
	#define USE_SLIDETEST_BMD
	#define USE_MONSTERSKILLTEST_BMD
	#define USE_CREDITTEST_BMD
	#define USE_HARMONYJEWELOPTION_BMD
	#define USE_NOTSMELTING_BMD
	#define USE_ITEMADDOPTION_BMD
	#define USE_MIXTEST_BMD
	#define USE_MASTERTREE_BMD
	#define USE_SOCKETITEM_TEST_BMD
	#define USE_PET_TEST_BMD
	#define USE_FILTER_TEST_BMD
	#define USE_QUESTPROGRESSTEST_BMD
	#define USE_QUESTWORDSTEST_BMD
	#define USE_NPCDIALOGUETEST_BMD
	#define USE_MINIMAPTEST_BMD
#endif //_TEST_SERVER

/*-------------------- ���� ���� -------------------------------------------------------*/

// �����ϴ� ��� ����
#define LANGUAGE_KOREAN			( 0 )	// �ѱ���
#define LANGUAGE_ENGLISH		( 1 )	// ����
#define LANGUAGE_TAIWANESE		( 2 )	// �븸��
#define LANGUAGE_CHINESE		( 3 )	// �߱���
#define LANGUAGE_JAPANESE		( 4 )	// �Ϻ���
#define LANGUAGE_THAILAND		( 5 )	// �±���
#define LANGUAGE_PHILIPPINES	( 6 )	// �ʸ���
#define LANGUAGE_VIETNAMESE		( 7 )	// ��Ʈ��
#define NUM_LANGUAGE			( 8 )
// ���⼭ ��� ����

//#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
//----------------------------------------------------------------------------- Kor
// Kor
#ifdef _LANGUAGE_KOR
	#define SELECTED_LANGUAGE	( LANGUAGE_KOREAN )
//----------------------------------------------------------------------------- Eng
// Eng
#elif _LANGUAGE_ENG
	#define SELECTED_LANGUAGE	( LANGUAGE_ENGLISH )
//----------------------------------------------------------------------------- Tai
// Tai
#elif _LANGUAGE_TAI
	#define SELECTED_LANGUAGE	( LANGUAGE_TAIWANESE )
//----------------------------------------------------------------------------- Chs
// Chs
#elif _LANGUAGE_CHS
	#define SELECTED_LANGUAGE	( LANGUAGE_CHINESE )
//----------------------------------------------------------------------------- Jpn
// Jpn
#elif _LANGUAGE_JPN
	#define SELECTED_LANGUAGE	( LANGUAGE_JAPANESE )
//----------------------------------------------------------------------------- Tha
// Tha
#elif _LANGUAGE_THA
	#define SELECTED_LANGUAGE	( LANGUAGE_THAILAND )
//----------------------------------------------------------------------------- Phi
// Phi
#elif _LANGUAGE_PHI
	#define SELECTED_LANGUAGE	( LANGUAGE_PHILIPPINES )
//----------------------------------------------------------------------------- Vie
// Vie
#elif _LANGUAGE_VIE
	#define SELECTED_LANGUAGE	( LANGUAGE_VIETNAMESE )
#endif
//-----------------------------------------------------------------------------
// #else // KJH_MOD_LIBRARY_LINK_EACH_NATION
// 	#define SELECTED_LANGUAGE	( LANGUAGE_ENGLISH ) --> �������� ����
// #endif // KJH_MOD_LIBRARY_LINK_EACH_NATION

/*--------------------------------------------------------------------------------------*/
#ifdef _BLUE_SERVER
	#define GAMEGUARD_BLUEMU_VERSION			// ��� �� ����� ���Ӱ���
#endif //_BLUE_SERVER

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN || SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
// - �ȼ���
// ���Ӱ��� ���� 2.5����(���� ������ ��ġ �ű��� �� ��!)
//	�� �������� ���� ���� �ÿ���, ���Ӱ��� ���̺귯���� 051223���� ������ ������ ��
#define GAMEGUARD_AUTH25
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN || SELECTED_LANGUAGE == LANGUAGE_JAPANESE

/*-------------------- �������� �ٸ� �ɼ� ���� -----------------------------------------*/

#ifdef _DEBUG
	#define ENABLE_EDIT				// �ý��� �޼���
	#define ENABLE_EDIT2			// ����Ű�� �̵�
	//#define ACC_PACKETSIZE		// ���۵Ǵ� ��Ŷ ������ ���
	#if SELECTED_LANGUAGE == LANGUAGE_KOREAN	// �ѱ� ���������� �۵��ϸ�, �ؿܹ��������� boost new �� �浹 �߻��մϴ�. (2009.01.05)
		#define USE_CRT_DEBUG			// �޸� ���� �����
	#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN
	//#define PK_ATTACK_TESTSERVER_LOG		// �׼��� PK ���� ������ �α׳���� �۾�(2007.04.25)
#endif // _DEBUG

#ifdef FOR_WORK
/*----------------------- ������ ���� --------------------------------------------------*/

//#define KJH_LOG_ERROR_DUMP					// ����������� �α� ��� (2009.06.15)
#ifdef KJH_LOG_ERROR_DUMP
	#define LOG_ERROR_DUMP_FILENAME		"Log_ErrorDump.txt"		// ����������� �α������̸�
#endif // KJH_LOG_ERROR_DUMP

//#define PBG_LOG_PACKET_WINSOCKERROR		// ���ӿ��� �α� Ȯ��
#ifdef PBG_LOG_PACKET_WINSOCKERROR
	#define PACKET_LOG_FILE	"PacketLogFileRecv.txt"
#endif //PBG_LOG_PACKET_WINSOCKERROR

#ifdef _DEBUG

	//$ �ܼ� �����
	#define CSK_LH_DEBUG_CONSOLE			// �ַܼ� ����� ���� ����� ó��(2007.03.20)
	#ifdef CSK_LH_DEBUG_CONSOLE
		#define CONSOLE_DEBUG				// �ַܼ� ����� ���� ���(2007.03.20)
	#endif // CSK_LH_DEBUG_CONSOLE

	//$ �ʼӼ� ���� ���
	#define CSK_DEBUG_MAP_ATTRIBUTE			// �� �Ӽ��� ���ӳ��� ���(2008.10.14)

	//$ �ٿ���ڽ� ������ ���
	#define CSK_DEBUG_RENDER_BOUNDINGBOX		// �ٿ�� �ڽ� ������(2008.10.28)

	//$ ��ã���� ���� ���
	#define CSK_DEBUG_MAP_PATHFINDING		// ��ã���带 ���ӳ��� ���(2008.10.14)

	//$ �������ϸ� & ����� ī�޶�	
	// �������� �������� �����, �������ϸ�,ī�޶� �۾��� �Ҷ��� local�� �۾��Ͻÿ�
	//#define LDS_ADD_DEBUGINGMODULES	// ���� Profiling ��� (��������� RESULT_PROFILING.txt�� ����) 

	#ifdef LDS_ADD_DEBUGINGMODULES
		#define DO_PROCESS_DEBUGCAMERA	// Main GameScene �� ������ ī�޶� ���� (2008.07.30)
		//#define LDS_ADD_DEBUGINGMODULES_FOR_PROFILING
		#ifdef LDS_ADD_DEBUGINGMODULES_FOR_PROFILING
			#define DO_PROFILING			// PROFILING_RESULT.txt-��� ��� // ���� Profiling ��� ���� ����.  (2008.07.11)
			//#define DO_PROFILING_FOR_LOADING// PROFILING_FOR_LOADING_RESULT.txt-��� ��� // Loading������ Profiling ���.  (2008.08.19)
		#endif // LDS_ADD_DEBUGINGMODULES_FOR_PROFILING
	#endif // LDS_ADD_DEBUGINGMODULES

	// �������� �������� �����, �������ϸ�,ī�޶� �۾��� �Ҷ��� local�� �۾��Ͻÿ�
	//#define LDS_UNFIXED_FIXEDFRAME_FORDEBUG	// �ʴ� 20���� �������� ������ ��ȯ ���� ������Է��ڵ�($unfixframe on/$unfixframe off) ��� Ȱ��ȭ, ���� realease ��忡�� ����� ���� �� CSK_LH_DEBUG_CONSOLE �������� ���� �Ѿ� �մϴ�.

#endif // _DEBUG

//#define LDS_FOR_DEVELOPMENT_TESTMODE
#ifdef LDS_FOR_DEVELOPMENT_TESTMODE
	#define CSK_LH_DEBUG_CONSOLE			// �ַܼ� ����� ���� ����� ó��(2007.03.20)
	//#define ENABLE_FULLSCREEN				// Ǯ��ũ��	(��Ȥ Release(�系�׽�Ʈ��)�ÿ� ��üȭ�� ����� ���ϴ� ��찡 ����.)
#endif // LDS_FOR_DEVELOPMENT_TESTMODE

/*------------------------------------------------------------------------------------------*/
#endif // FOR_WORK

#ifdef NDEBUG
	#ifdef FOR_HACKING				// ��ŷ����
	#else // FOR_HACKING
		#define ENABLE_FULLSCREEN	// Ǯ��ũ��
	#endif // FOR_HACKING

	#ifndef FOR_WORK
		
		// ���ҽ�����
		#define RESOURCE_GUARD		
		
		//#define USE_SELFCHECKCODE	// ���� üũ �ڵ� ���

		// ���Ӱ���
		#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
			//#define USE_MU_INTERNAL_TEST			//���Ӱ��� �系 �׽�Ʈ����
			//#define USE_VIETNAMESE_NPGAME_TEST	//���Ӱ��� �系 �׽�Ʈ ����(��Ʈ��)
			#define NP_GAME_GUARD					// nProtect Game Guard.
			#define GG_SERVER_AUTH					// ���Ӱ��� - ������ ���� ����
			//#define USE_NPROTECT	// nProtect �� ����Ѵ�. ��ö�� �ٽ���� ����ȴ�
		#endif	// SELECTED_LANGUAGE != LANGUAGE_CHINESE

#ifdef KJH_MOD_NATION_LANGUAGE_REDEFINE
#ifndef _LANGUAGE_KOR				// KOR ����
		#define FOR_ADULT		// ���ο�(�ǻ�����)
#endif // _LANGUAGE_KOR
#else // KJH_MOD_LIBRARY_LINK_EACH_NATION
		#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
			//#define USING_MFGS	// MFGS ��� üũüũ
		#else // SELECTED_LANGUAGE == LANGUAGE_KOREAN
			#define FOR_ADULT		// ���ο�(�ǻ�����)
		#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN
#endif // KJH_MOD_NATION_LANGUAGE_REDEFINE

	#endif // FOR_WORK
#endif // NDEBUG

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	#define WAV_CONVERT		// wav ����Ʈ ����� ���� ���ΰ�? �ѱ� ���� ������ ����� �ٲٴ� ���
	#ifndef WAV_CONVERT
		#define KOREAN_WAV_USE		// �ѱ۷� �� wav ������ �� ���ΰ�? 
	#endif
#endif

#ifdef NP_GAME_GUARD
	#define GG_SERVER_AUTH			// ���Ӱ��� - ������ ���� ����

	#if defined(GAMEGUARD_AUTH25) || SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		#define NPROTECT_AUTH2		// NProtect Auth2����
	#endif

#endif // NP_GAME_GUARD 

#if defined USER_WINDOW_MODE || (defined WINDOWMODE)
#define ACTIVE_FOCUS_OUT				// â �ٱ����� ��Ŀ�� ������ ���� ���� �ȵ� & alt-tab�㰡
#endif	// USER_WINDOW_MODE

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
// 	#define LIMIT_CHAOS_MIX			// 2�� ����, ������ ����, �������, ���������� �ʴ�� �� ����� ��(npc �ؽ�Ʈ�� ��) -> ����4��ġ���� ����
// 	#define LIMIT_SKILL				// �۷ι��� ����������, ��ο� ��ų ���� -> ����4��ġ���� ����
	#define GRAMMAR_OF				// of ����
#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH

#if SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
	#define GRAMMAR_OF				// of ����
#endif

#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
	#define USER_WINDOW_MODE		// ���� â��� ���
	#define ONLY_PSWD_STORAGELOCK	// â�� ��� ��ɿ� ����� ��� (�߱�)
	#define CHINESE_PRICERISE		// �߱� ���������å
	//#define ANTIHACKING_ENABLE	// �߱����� ���ߵ� anti-hacking solution �� �̿��Ѵ�.
#else
	#define BAN_USE_CMDLINE				// ����ٻ���� �����Ѵ�. ���, Mu Virtual Commander�� �����Ѵ�. (2005-02-18)
	#define NEW_YEAR_BAG_EVENT		// ���� ���ָӴ� �̺�Ʈ.   ( �߱������� ������� �ʴ´�. )
#endif

#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define TAMAJJANG					// Ÿ��¯. ( �Ϻ� ).
	//#define HERO_SELECT					// �ڱ� �ڽ� �����ϱ�.
	#define JAPANESE_ITEM_HELP_FIX		// �Ϻ� ������ ���� ������ ǥ�� ���� (2004-07-22)
	//#define JPN_SERIAL_NOT_RENDERTEXT	// �Ϻ� Ȳ�� �ü� �ø��� �Է½� ������ ��Ī ǥ�� �ȵǰ� ����(2005.11.03)
#endif

#if SELECTED_LANGUAGE != LANGUAGE_TAIWANESE
	#define CONNECT_LIST_FIX		// ���� ���� ���� ���� ���� ��ģ�� (�븸������ ������� �ʰų� ���� ���� �ٲ���� ��)
#endif

#if SELECTED_LANGUAGE == LANGUAGE_CHINESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
	#define CHINA_MOON_CAKE			// �߱� ���� �̺�Ʈ.
#endif

#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_JAPANESE \
	|| SELECTED_LANGUAGE == LANGUAGE_CHINESE
	#define DISABLE_MUTO			// ���亹���� ������(�븸) (2004-07-27)
#endif

#if SELECTED_LANGUAGE == LANGUAGE_CHINESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE \
	|| SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES \
	|| SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
	#define GRAMMAR_VERB			// ���� ���� ( welcome to ����)
#endif

#if SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
	#define PHIL_LANGUAGE_PROBLEM	// ��� ���� (���� ���� ��� �����ؾ� ��, ���� �߽߰� �� �Ʒ��� �߰�)
#endif

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
	#define ENG_LANGUAGE_PROBLEM	// ��� ���� (���� ���� ��� �����ؾ� ��, ���� �߽߰� �� �Ʒ��� �߰�)
#endif

#if !defined(NP_GAME_GUARD) && !defined(FOR_WORK) && !defined(_DEBUG)
	//#define ATTACH_HACKSHIELD		// ��ö�������� �ٽ��� ����
#endif


#ifndef ANTIHACKING_ENABLE		// Anti-hacking solution ���� �Լ��� overload
	#define hanguo_check1();	{}
	#define hanguo_check2();	{}
	#define hanguo_check3();	{}
	#define hanguo_check4();	{}
	#define hanguo_check5();	{}
	#define hanguo_check6();	{}
	#define hanguo_check7();	{}
	#define hanguo_check8();	{}
	#define hanguo_check9();	{}
	#define hanguo_check10();	{}
	#define hanguo_check11();	{}
	#define hanguo_check12();	{}
	#define	pre_send( g_hInst);	{}
#endif

/*--------------------------------------------------------------------------------------*/


/*----------------------- �̺�Ʈ -------------------------------------------------------*/

//#define CSK_EVENT_HALLOWEEN_MAP	//	�ҷ��� �̺�Ʈ �� ó��(2006.10.09)
//#define DEVIAS_XMAS_EVENT			//  ũ�������� �̺�Ʈ ���� ����ƽ� �� �� ���ҽ� ����(2005.12)
#define STONE_EVENT_DIALOG			// ���� �̺�Ʈ ( ���� ���� ����, ��¥ ��� �̺�Ʈ ).
//#define LENA_EXCHANGE_ZEN			// ���� ȯ�� �ý���, ���� : ���濡���� �Ѽ��� �ȵȴ�.
#define BLOODCASTLE_2ND_PATCH		// ���� ȯ�� �ý���, ���հ���
#define USE_EVENT_ELDORADO			// �������� ���� �̺�Ʈ
#define SCRATCH_TICKET				// ���ȭ 2�ֳ� �̺�Ʈ.
#define FRIEND_EVENT				// ģ�� �̺�Ʈ.
#define FRIENDLYSTONE_EXCHANGE_ZEN	// �����ǵ� ȯ�� �ý���

#define CASTLE_EVENT				// ������ ���� ���
#ifdef CASTLE_EVENT
	#undef FRIEND_EVENT
	#undef FRIENDLYSTONE_EXCHANGE_ZEN
	#undef LENA_EXCHANGE_ZEN
	#define DISABLE_MUTO			// CASTLE_EVENT �� �ʿ�
#endif

#define BATTLE_SOCCER_EVENT         // ��Ʋ��Ŀ �̺�Ʈ.
#define LOREN_RAVINE_EVENT			// �η����� �̺�Ʈ���� ����.
//#define GUILD_WAR_EVENT           // ���� �̺�Ʈ.
//#define MYSTERY_BEAD				// �ź��� ���� �̺�Ʈ

#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define ANNIVERSARY_EVENT			// �Ϻ� 1�ֳ� ���� �̺�Ʈ (�ٸ����� ����� �� ����)
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE

#define	PCROOM_EVENT				//	PC�� �̺�Ʈ.(2006.1.26)

/*--------------------------------------------------------------------------------------*/


/*----------------------- �ý��� ���� --------------------------------------------------*/

#define DUEL_SYSTEM					// ���� �ý���
#define PET_SYSTEM					// �ֿ� �ý���.
#define PROTECT_SYSTEMKEY			// ������ �ý���Ű�κ��� ������ ��ȣ�Ѵ�.
#define CHANGE_RATE					// ��� �ٲٱ�
//#define SYSTEM_NOT_RENDER_TEXT	// �ؽ�Ʈ�� ���� ���� �ý���(2007.11.28)
//#define FOR_DRAMA					// ��� ���ѻ��
//#define ON_AIR_BLOODCASTLE		// ���� ĳ�� ����� ���� �۾�. �ʿ���� �޼��� ��� ����
//#define CAMERA_TEST				// ������ ( ĳ���� �Ⱥ��� )
//#define CAMERA_TEST_FPS			// 1��Ī ������ ���� ������ �ָ����� ����
//#define DONTRENDER_TERRAIN		// ������ �׸��� �ʴ´�

/*--------------------------------------------------------------------------------------*/


/*----------------------- ���Ѱ͵� -----------------------------------------------------*/

#define CRYINGWOLF_2NDMVP				// ũ���̿��� ������ - ����� �����Ƕ� ���õ� �Լ��� ���� ����� ����Ʈ�� ���ܵμ���
#define GIFT_BOX_EVENT					//  �߷�Ÿ�ε��� �̺�Ʈ ���� (2006.1)
#define BUGFIX_CRYWOLF_END_COUNT		// ����ī��Ʈ �߰� �ִµ� ���� Ŭ�� ������ ����
//#define CASTLE_TAX_LIMIT              // ������ ���� ���� ��� ������.
//#define STATE_LIMIT_TIME              // ĳ���� ���� ���� �ð�.
//#define AUTO_CHANGE_ITEM				// �ڵ����� ��� ��ü�ϱ�.
//#define UNDECIDED						// ���콺 �� ���� ( �߰� �� ��ư���� ���� �Ա�� �ٷ� ����Ű ����)
//#define ENABLE_CHAT_IN_CHAOS			// ī����ĳ������ ���ð����ϵ�����(��� ���)
//#define ENABLE_POTION_EFFECT			// ����Դ� ȿ���� �ѱ� (DISPLAYVIEWPORT_EFFECT�� ���� ���Ǿ�� �Ѵ�)
//#define _PVP_ATTACK_GUARD				// ��� ���� �����ϰ�
//#define _PVP_MURDERER_HERO_ITEM		// ����&���θ� ������&����
//#define _PVP_ADD_MOVE_SCROLL			// �̵����� �߰�
//#define _PVP_BLOCK_PVP_CHAR			// ĳ���� ���ý� ���θ� �α��� ����
//#define _PVP_DYNAMIC_SERVER_TYPE		// ���� pvp���� ���� ���� ����
//#define USE_SKILL_LEVEL				// ���̿� ���� ���� �߰�
//#define USE_SHADOWVOLUME		        // ������ ���� ���
//#ifdef _TEST_SERVER
//	#define	ADD_EXPERIENCE_SERVER			//	���� 2 ü�� ����(2006.08.04)
//#endif	//  _TEST_SERVER
//#define RE_PRICE_SPECIAL_ITEM
//#define USE_MASTER_SKILL
//#define CRYWOLF_1ST
//#define BATTLE_CASTLE_AS				// ���������۾�������(2005-10-14) ������ �׽�Ʈ �� ���ƾ� ��!!
//#define BATTLE_CASTLE					// ������.
//#define ADD_MONSTER_SKILL
//#define MVP_INTERFACE
//#define REPAIR_KALIMA					//  Į���� ��������(2005-12-12 �߰�)
//#define REPAIR_HELPER_ELF				//  ����npc ����,��� ��ġ����(2005-12-14 �߰�)
//#define MVP_RESULT					//	ũ���̿��� ���� +ī��������Ȯ��(2005-12-19 �߰�)
//#define SELL_ITEM_PRICE				//  ��ź�ϰ� ��ȣ�� ���� �ȶ� ���� /3 ���ϰ�(2006-02-21 �߰�)-�ѽ������� ��Ұ���.
//#define VISTA_ADD						//  ��Ÿ ��� �߰� �ڵ�(2006-12-11 �߰�)
//#define OBJECT_ID						//������Ʈ�� ID�߰�
//#define DYNAMIC_FRUSTRUM				//������Ʈ�� ������ ���������� ���� �� �ִ�

/*--------------------------------------------------------------------------------------*/


/*----------------------- �۾� ��ҵȰ� ------------------------------------------------*/
// - �ּ���
//#define MOVIE_DIRECTSHOW				//	DirectShow�� �̿��ؼ� ������ ����(2005.12.09)

// �ȼ���, �̵���
//#define MR0
#ifdef	MR0
	#define NEW_RENDERING_SYSTEM

	// 1. MR0:System Type
	#ifdef NEW_RENDERING_SYSTEM
		#define NEW_RENDER_OBJECT
		#define NEW_RENDER_TERRAIN
//		#define NEW_RENDER_EFFECT			
	#endif //NEW_RENDERING_SYSTEM

	// 2. MR0:���� �� ���׵�
	#define LDS_ADD_RENDERMESHEFFECT_FOR_VBO					// RenderMeshEffect() �Լ��� ���� VBO ������ �߰� �մϴ�. (�Լ������� VBO������ ���ȵǴ� WorldVertex�������� "ġ���� ����" �߻�) (09.09.09)
	#define LDS_MOD_ANIMATIONTRANSFORM_WITHHIGHMODEL			// AnimationTransformWithAttachHighModel�Լ����� ���� arrayBone�� �ʿ��� ���� Transform���� Bone�� Vertices�� ������ �ʵ��� ����. (2009.09.09)
	#define LDS_ADD_ANIMATIONTRANSFORMWITHMODEL_USINGGLOBALTM	// AnimationTransformWithAttachHighModel�Լ��� TMArray�� Local�� ������ ���� ���꿡 TM�� Point�� �Ҿ������ �������� TM�� Global ���� ����. (09.09.07)
	#define LDS_MR0_MODIFY_DIRECTLYAPPLY_SCALETM_INCLUDESHADER	// ShaderCode+RenderMachine���� ���� : Chromeȿ���� ���� VertexNormal�� �̿��� ���ÿ� Normal�� Scale������ ���� �ʵ��� Position���� Scale�� ���������� ��Ŀ���� ����. (2009.09.01)
	#define LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE			// ���� �ɸ��� �� ������Ʈ �Ƿ翧 ���� : ������ ��ȯ�� ����:������Ʈ�� ���� ������ ���� �ƴ� ���� ������ ���� ������ ���� ���� (2009.01.02)
	#define LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH			// ������ ��� :��κ��� �޽��� ������ ����� ���� (2009.01.05)
	#define LDS_MR0_MODIFY_LOGINSCENE_SHADOWPROBLEM				// Ư�� ���� LightDisable ó��. LightEnable �Ǹ� Blending �� ����, Fog ȿ���� ó�� ���� ����. (2009.01.07)
	#define LDS_MR0_MODIFY_ANIMATIONMAPPING_NOANIMATED			// ���ϸ��̼� Mapping�� ���� Animate ���� �ʴ� ����(BlendTexture�ν� ó���� �Ǿ�� �ϴµ� Blend ó���� �̷������ �ʴ� ����.) (2009.01.09)
	#define LDS_MR0_MODIFY_WHENREOPEN2_SKIPCONVERT				// Bmd::Open2�� �̹� ������ ���Ͽ� ���ؼ� Skip Parameter�� ���Ͽ�, VBO�� ConvertMesh���� Skip �ǵ��� �����մϴ�. (2009.02.24)
	#define LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER		// ShutDown �ÿ� ���� ���ᰡ �ǵ��� ModelManager Uninit �մϴ�. (2009.02.26)	
	#define LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH	// TextureScript Parsing �� _N �ؽ��ĵ鿡 ���� NonBlendMesh�� True���� �Ǹ�, AddRender()�Լ��󿡼� Render Skip�Ǿ�, ��ȯ���� ��� ������ �Ⱥ��̴� ����. (2009.02.26)
	#ifdef LDS_ADD_RENDERMESHEFFECT_FOR_VBO
		#define LDS_MR0_ADD_DONTDELETE_OLDMESHSBUFFER_DARKSPIRIT	// RenderMeshEffect �Լ����� ���𵨹��� ���ؽ������� �ʿ�, olddelmodel�� ���ϵ��� ����. ��ũ���Ǹ�. (09.09.10)
	#endif // LDS_ADD_RENDERMESHEFFECT_FOR_VBO
	
	#define LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX		// Physic���� �ٷ�� �빰����, �κй����� �� �κй����𵨿����� �߻��ϴ� ���� FIX�۾�. (09.09.28)
	#define LDS_MR0_ADD_VBOMANAGER_SETONOFF						// VBO Manager�� On/Off �ϴ� �Լ��� �߰� (09.09.29)
	#define LDS_MR0_ADD_SPECIFICMODEL_DOANIMATIONPROCESSING		// VBO Model�� ��ȯ�� ���� �� �� ������ �ʿ��Ͽ� ���縦 ���ܵδ� �𵨵鿡 ���� �� ������ Animation Transformation ������ ������ �޽��� �ϵ��� �մϴ�. ����� ���ؽ� ������ �ʿ��� ��� ���. (09.10.20)
	#define LDS_MR0_ADD_ENCRYPTION_ALLSHADERSCRIPT				// ��� Shader Script�鿡 ���� Encryption/Decryption. (09.11.25)

	#define LDS_MR0_MOD_WHENTRANFORM_BUILDOBB_ALLWAYS			// BMD������ ���� ���� BMD ���� OBB�� ������������ ����. (09.12.01)
	#define LDS_MR0_INTIALIZE_SOME_MAINVARIABLES				// ��� �ֿ亯������ �ʱ�ȭ�� �����ѰͿ� ���� ����. (09.12.02)
	#define LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT				// �ɼ�â�� ȿ�� ������ 3�ΰ�� ���ΰ� �ɸ��� ��������. RenderPartObjectEffect �Լ����� ShaderObject �̷����� ���·� ��ȯ ������ ����. (09.12.04)
	#define LDS_MR0_MOD_FIXEDFRAME_DELTA						// ���� 20�������� ���� DELTA�����ӿ� ���� ������꿡�� ������������ ����. (09.12.09s)

	#define LDS_MR0_MOD_DUETOOVERCOUNTBONES_BREAKVISUAL			// �޽��� �������� ���̴� �Ķ���� ���� �ѵ�(�� 70��) �ʰ��� ���� ���� �������� �޽��� �� ���� ���� (���� 3�� + ��� �õ� ������ + ���� ��) (10.01.20)

	#define LDS_MR0_FIX_BREAKVISUAL_DOPPELGANGER_CHARACTER		// ���ð������ "���ð���" ������ ������ RenderMesh, RenderBody ȣ��� ���� TM ���ġ�� ��������߻�-> SetTargetObject() �����ְ�, Move�ܰ迡�� ȣ��� RenderBody�� RenderMonsterVisual�� ��ġ �̵�. (10.02.03)

	#define LDS_MR0_MOD_SET_LOWRENDERER_INIT					// ���� ���־� ������ ���߱� ���� LOWRENDERER �� ���� ���� �մϴ�. (2010.03.30)

	// 3. MR0:For TESTDEBUG
	#ifdef _DEBUG
		#define LDS_MR0_FORDEBUG_USERRESPOND_BEINGVPMANAGERENABLE// ���� VPMANAGER�� Enable ���� ���� ���θ� ��ȯ �մϴ�.
		#define LDS_MR0_FORDEBUG_VERIFYCONVERTMESH				// ConvertMesh�� ��ȯ�� VBOMesh�� ������ ��� �մϴ�. (2009.01.15)
		#define LDS_MR0_FORDEBUG_CALCTRANFROMBYCPU				// Transform �� CPU�� ���� �մϴ�. (2009.02.02)

		// For Debug
		#define LDS_FOR_DEVELOPMENT_TESTMODE					// Debug ���� ��� (LDS_UNFIXED_FIXEDFRAME_FORDEBUG ����)
		#define CSK_LH_DEBUG_CONSOLE							// �ַܼ� ����� ���� ����� ó��(2007.03.20)
		//#define ENABLE_FULLSCREEN								// Ǯ��ũ��	(��Ȥ Release(�系�׽�Ʈ��)�ÿ� ��üȭ�� ����� ���ϴ� ��찡 ����.)

		// Output GL Error 
		#define LDS_MR0_OUTPUT_GLERROR_IN_BITMAPLOAD			// Output OpenGL Error In Jpeg, Tga Loading Function (2009.02.19)
		#define LDS_MR0_OUTPUT_GLERROR_INNER_GLRENDERER			// GL Renderer ������ GLERROR ���� �ڵ带 �ɾ� �����ϴ�. (2009.02.26)
		#define LDS_MR0_OUTPUT_GLERROR_GENERAL					// 
	#endif // _DEBUG

	// 4. MR0:For Temporary 
	#define LDS_MR0_TEMPORARY
	#ifdef LDS_MR0_TEMPORARY
		#define LDS_MR0_FORDEBUG_MESHALLWAYS_VSTYPE				// MR0 �޽� Ÿ���� �׻� VBO�� ���� �մϴ�. PBO ���� �̿ϼ� 
		#define LDS_MR0_FIXED_RIGHT_SHADER_MAXPARAM_VALUE		// Env Param, Local Param ������ ���� OpenGL���� �����Ǵ� ������ ���� (2009.04.02)
		#define LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY		// ��޴������� �׷����� �𵨵�(����,��ȣ����,���,�絹�����..)�� ShaderRender�� �ƴ� ���� VertexRender �մϴ�.- �ӽ��� ���� �Ҹ����. (09.12.01)
//		#define LDS_MR0_FIXED_SHADERPARAM_WHICH_MODEL_BREAKED_DUETO_BONE	// Shader���� DrawCall �ѹ��� �� �Ķ���� 64�� �̻� �ѱ� �� ���� ������ �����ϱ� ���� 
																			// ���� ���� 256���� ����� �� �ִ� env param���� 1024���� local param���� ���� (data\MixShader\Definitions.txt, data\Shader\shadowmap.vsh ���̴� ���� ���� )(2009.04.14)
	#endif // LDS_MR0_TEMPORARY

#endif //MR0
/*--------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------*/

#define WM_USER_MEMORYHACK	( WM_USER + 1)
#define WM_NPROTECT_EXIT_TWO  (WM_USER + 10001)

//#define PBG_ADD_INGAMESHOP_FONT

extern bool ashies;
extern int weather;
extern int Time_Effect;
extern HWND      g_hWnd;
extern HINSTANCE g_hInst;
extern HDC       g_hDC;
extern HGLRC     g_hRC;
extern HFONT     g_hFont;
extern HFONT     g_hFontBold;
extern HFONT     g_hFontBig;
extern HFONT     g_hFixFont;
#ifdef PBG_ADD_INGAMESHOP_FONT
extern HFONT	 g_hInGameShopFont;
#endif //PBG_ADD_INGAMESHOP_FONT
//extern HFONT     g_hFontSmall;
extern bool      Destroy;
extern int       RandomTable[];
extern char      *Language;

extern char m_ID[];
extern char m_Version[];
extern int  m_SoundOnOff;
extern int  m_MusicOnOff;
extern int  m_Resolution;
extern int m_nColorDepth;	

void MouseUpdate();
extern void CheckHack( void);
extern void CloseHack(HWND shWnd,bool Flag);
extern DWORD GetCheckSum( WORD wKey);
extern void StopMp3(char *Name, BOOL bEnforce=false);
extern void PlayMp3(char *Name, BOOL bEnforce=false);
extern bool IsEndMp3();
#ifdef YDG_ADD_DOPPELGANGER_SOUND
extern int GetMp3PlayPosition();
#endif	// YDG_ADD_DOPPELGANGER_SOUND
extern unsigned int GenID();

extern void CloseMainExe( void);
extern GLvoid KillGLWindow(GLvoid);
extern void DestroyWindow();
extern void DestroySound();

/*-------------------- Macro --------------------*/

/*----------------------- ������ ���� --------------------------------------------------*/
#ifdef DO_PROFILING
	#include "Profiler.h"
	extern CProfiler	*g_pProfiler;
#endif // DO_PROFILING

#ifdef DO_PROFILING_FOR_LOADING
	#include "Profiler.h"
	extern CProfiler	*g_pProfilerForLoading;
#endif // DO_PROFILING_FOR_LOADING

#ifdef DO_PROCESS_DEBUGCAMERA
	#include "DebugCameraManager.h"
	extern CDebugCameraManager *g_pDebugCameraManager;
#endif // DO_PROCESS_DEBUGCAMERA

#if defined(LDS_FOR_DEVELOPMENT_TESTMODE) || defined(LDS_UNFIXED_FIXEDFRAME_FORDEBUG)
	extern bool g_bUnfixedFixedFrame;
#endif // defined(LDS_FOR_DEVELOPMENT_TESTMODE) || defined(LDS_UNFIXED_FIXEDFRAME_FORDEBUG)

#if defined _DEBUG || defined PBG_LOG_PACKET_WINSOCKERROR
	#include "./Utilities/Log/DebugAngel.h"
#define ExecutionLog	DebugAngel_Write
#else
#define ExecutionLog	{}
#endif //_DEBUG

#ifdef USE_CRT_DEBUG				
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // USE_CRT_DEBUG

/*-------------------------------------------------------------------------------------------*/


/*----------------------- MR0 ���� --------------------------------------------------*/

#ifdef MR0
	#ifdef LDS_MR0_FIXED_RIGHT_SHADER_MAXPARAM_VALUE
		#define MR0_MAX_PARAMETERS			1024
		#define MR0_MAX_ENV_PARAMETERS		256
		#define MR0_MAX_LOCAL_PARAMETERS	1024
	#endif // LDS_MR0_FIXED_RIGHT_SHADER_MAXPARAM_VALUE

	#ifdef LDS_MR0_FIXED_SHADERPARAM_WHICH_MODEL_BREAKED_DUETO_BONE
		#define NUM_PRERESERVED_PARAM_GPUREGISTER	10
	#endif // LDS_MR0_FIXED_SHADERPARAM_WHICH_MODEL_BREAKED_DUETO_BONE
#endif // MR0
/*-------------------------------------------------------------------------------------------*/

#define FAKE_CODE( pos)\
	_asm { jmp pos };\
	_asm { __emit 0xFF };\
	_asm { __emit 0x15 }


#endif
