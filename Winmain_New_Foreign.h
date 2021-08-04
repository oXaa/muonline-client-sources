#pragma once


// �κ� ����ȭ�� �ʿ� �ѱ��� ���� �ȵ�.
/*------------------------------------�κ� ����ȭ 1��----------------------------------------*/

// �κ� ����ȭ 1��
#define PSW_PARTCHARGE_ITEM1				
#ifdef PSW_PARTCHARGE_ITEM1
	#define CSK_FREE_TICKET						// ��������� - ����������, ����ĳ��, Į���� (2007.02.06)
	#define CSK_CHAOS_CARD						// ī����ī�� - ���� (2007.02.07)
	#define CSK_RARE_ITEM						// ��;�����(2006.02.15)
	#define CSK_LUCKY_CHARM						// ����� ����( 2007.02.22 )
	#define CSK_LUCKY_SEAL						// ����� ����( 2007.02.22 )	
	#define CSK_HIGHPRICEITE					// �� ������ ó��
	#define CSK_CHARGENOTMOVE					// �κ� ����ȭ ������ �̵� �Ұ�
#endif //PSW_PARTCHARGE_ITEM1

/*------------------------------------�κ� ����ȭ 2��----------------------------------------*/

// �κ� ����ȭ 2�� ( �Ϻ�, �븸 )
#define PSW_PARTCHARGE_ITEM2
				
#ifdef PSW_PARTCHARGE_ITEM2
	#define PSW_ELITE_ITEM						// ����Ʈ ����
	#define PSW_SCROLL_ITEM						// ����Ʈ ��ũ��
	#define PSW_SEAL_ITEM						// �̵� ����
	#define PSW_FRUIT_ITEM						// ���� ����
	#define PSW_SECRET_ITEM						// ��ȭ�� ���
	#define PSW_INDULGENCE_ITEM					// ���˺�
	#define PSW_RARE_ITEM						// ��� ������ Ƽ��
	#define PSW_CURSEDTEMPLE_FREE_TICKET		// ȯ���� ��� ���� �����
#endif //PSW_PARTCHARGE_ITEM2

/*----------------------------------���� 2.5�� �ؿ� Ưȭ �۾�----------------------------------------*/

// �Ϻ� �����̵� ���� ���� �߰� ���� 5�� ���۸� 10���� ����( 2006 - 08 - 10 )
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define REVISION_SLIDE_LEVEL_MAX          
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE

// ���� 2_5���� �������� ��Ŷ ����
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
	#define SEASON2_5_PACKET_MAGIC_ATTACK
#endif //SELECTED_LANGUAGE == LANGUAGE_TAIWANESE

// ���� 2_5���� ��ǥ ��Ŷ ����
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE
	#define SEASON2_5_PACKET_POSITION
#endif //SELECTED_LANGUAGE == LANGUAGE_CHINESE

/*------------------------------------�κ� ����ȭ 3��----------------------------------------*/

// �κ� ����ȭ 3�� ( �Ϻ� )
#define PSW_PARTCHARGE_ITEM3
				
#ifdef PSW_PARTCHARGE_ITEM3
	#if !defined(LDS_PATCH_GLOBAL_100520) // �۷ι��� 100527��ġ �� �ɸ��� ī�� ����
		#define PSW_CHARACTER_CARD						// ��ȯ���� ĳ���� ī��
	#endif // !defined(LDS_PATCH_GLOBAL_100520)
	#define PSW_NEW_CHAOS_CARD						// �ű� ī���� ī��
	#define PSW_NEW_ELITE_ITEM						// �߰� ����Ʈ ����
#endif //PSW_PARTCHARGE_ITEM3

/*--------------------------------�ؿ� ����( ���� 3 ���� )----------------------------------------*/

#define PSW_ADD_FOREIGN_HELPWINDOW                  // f1 key�� �������� �����߿� �̺�Ʈ�� (�ؿ�����)
													// ����ǥ �ؿ� ���� ���ϱ�( 2008.07.08 )


/*------------------------------------�κ� ����ȭ 4��----------------------------------------*/

// �κ� ����ȭ 4�� ( �Ϻ� )
#define PSW_PARTCHARGE_ITEM4

#ifdef PSW_PARTCHARGE_ITEM4
	#define PSW_ADD_PC4_SEALITEM       //  ġ��, �ż�( ü��, ���� ) ����
	#define PSW_ADD_PC4_SCROLLITEM     //  ����, ��ȭ( ũ��, �׼� ������ ���� ) ��ũ��
	#define PSW_ADD_PC4_CHAOSCHARMITEM //  ī���� ���� ����
	#define LDK_ADD_PC4_GUARDIAN		// ��ȣõ��, ��ź
	#define	LDK_FIX_GUARDIAN_CHANGE_LIFEWORD			// 1�� �����̾� ������ (������ ǥ�� -> �������� ����)(2009.01.14)
	#define LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE // lightmarks.jpg, effect #define ADD_SOCKET_ITEM �� �ߺ� �Ǵ°� ����... 
#endif //PSW_PARTCHARGE_ITEM4


/*------------------------------------�κ� ����ȭ 5��----------------------------------------*/

// �κ� ����ȭ 5�� ( �Ϻ� )
#define ADD_CASH_SHOP_5TH

#ifdef ADD_CASH_SHOP_5TH
	#define LDK_FIX_CS5_HIDE_SEEDLEVEL	// ���� �õ巹�� ǥ�� ����
	#define YDG_ADD_CS5_REVIVAL_CHARM	// ��Ȱ�� ����
	#define YDG_ADD_CS5_PORTAL_CHARM	// �̵��� ����
#endif	// YDG_ADD_CASH_SHOP_5TH

// - �ں���
#define PBG_WOPS_TEXT_MONMARK						// ����� ���� �ؽ�Ʈ ����(08.12.05)
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
	#define PBG_WOPS_MOVE_MAPNAME_JAPAN					// ������� �⺻ �� �̵� �Ұ����� ����(08.12.17)
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
#define PBG_WOPS_CURSEDTEMPLEBASKET_MOVING			//������������ �����̴� ���� ����(2008.12.18)
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN


/*------------------------------------�κ� ����ȭ 6��----------------------------------------*/

#if SELECTED_LANGUAGE != LANGUAGE_KOREAN

// [2009.02.18 �Ϻ� 1.03.05] - �Ȼ��
// ���Ŀ� �ٸ� ����鵵 �߰��� ��. ������ ���� �����Ǿ�� ��.
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
	#define ASG_FIX_LENA_REGISTRATION				// ���� ���� 32,767�� �̻� ��� �����ϵ��� ����.
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
// - �Ȼ��
// ���� ä��(��� ä��) ���� ������. 
	#define ASG_ADD_CHARGED_CHANNEL_TICKET			// ���� ä�� �����.�۷ι��� ����.(2010.02.05)
	#define ASG_MOD_CHARGED_CHANNEL_TICKET_ADD_DESCRIPTION	// ���� ä�� ����� ���� �߰�.(2010.02.24)
	#define ASG_ADD_CASH_SHOP_ALREADY_HAVE_ITEM_MSG	// ĳ���� �ߺ� ������ �޽��� �߰�.(2010.02.24)	
	#define KJH_ADD_SERVER_LIST_SYSTEM				// ��������Ʈ �ý��� ���� (09.10.19) - ������ ������ �̸� ��� ���.
	#define ASG_ADD_SERVER_LIST_SCRIPTS				// ServerList.txt ��ũ��Ʈ �߰�.(2009.10.29) - ������ ������ �̸� ��� ���.
	#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
		#define ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP	// �̸� ASG_ADD_SERVER_LIST_SCRIPTS �߰��� ���� ���� ����.(10.03.02) 
														//����5 ���� �����ص� ��.(BuxConvert() �Լ� ��ġ ����) // ����5 ������Ʈ�ÿ� �����ص� �Ǵ°����� Ȯ�� �ٽ� �Ұ�.
		#define ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL	// ��������Ʈ�� ���� ä�� �߰�.(10.02.26) - ���� �۷ι��� ����.
	#endif	//ASG_ADD_SERVER_LIST_SCRIPTS
	#define ASG_FIX_NOT_EXECUTION_WEBSTARTER_MSG	// ����Ÿ�� �̽��� �޽��� Text.txt ��ȣ ����(10.03.03)
#endif //SELECTED_LANGUAGE == LANGUAGE_ENGLISH

#define ADD_TOTAL_CHARGE_6TH
#ifdef ADD_TOTAL_CHARGE_6TH
// 1. �ɽ� �� ������ ( �Ϻ� )
// ---------------------------------------------------------------------------
#define ADD_CASH_SHOP_6TH
#ifdef ADD_CASH_SHOP_6TH
	// - �Ȼ��
	#define ASG_ADD_CS6_GUARD_CHARM				// ��ȣ�Ǻ���(2009.02.09)
	#define ASG_ADD_CS6_ITEM_GUARD_CHARM		// �����ۺ�ȣ����(2009.02.09)
	#define ASG_ADD_CS6_ASCENSION_SEAL_MASTER 	// ��������帶����(2009.02.24)
	#define ASG_ADD_CS6_WEALTH_SEAL_MASTER 		// ǳ�������帶����(2009.02.24)

	// - �̵���		// ���� Define : CSK_PCROOM_ITEM
	#define LDS_ADD_CS6_CHARM_MIX_ITEM_WING		// ���� ���� 100% ���� ����
#endif	// ADD_CASH_SHOP_6TH

// 2. Ȳ�� ���� 
// ---------------------------------------------------------------------------
// - �ּ���
#define CSK_ADD_GOLDCORPS_EVENT					// Ȳ�ݱ����̺�Ʈ(2009.03.13)
// - �̵���
#define LDS_ADD_GOLDCORPS_EVENT_MOD_GREATDRAGON // Ȳ�� �׷���Ʈ �巹�� ���־� ���۾�. ���־� ����Ʈ �߰�. ���� ������ �� ����. (2009.04.06) (BITMAP_FIRE_HIK3_MONO ȿ�� ����.)

// 3. PC �� �ý��� �� ������
// ---------------------------------------------------------------------------
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
#define ADD_CONTENTS_PCROOM_6TH
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
#ifdef ADD_CONTENTS_PCROOM_6TH
	#define	ADD_PCROOM_POINT_SYSTEM				// �Ϻ� PC�� �ý��� ����. winmain_new.h ���� (2009.03.25)
	#ifdef ADD_PCROOM_POINT_SYSTEM
		#define CSK_FIX_PCROOM_POINT_ZEN_BUG		// �Ϻ� PC�� �ý��� ����. winmain_new.h ���� (2009.03.25) // PC�� ����Ʈ �������� PC�� �ƴҶ� ����Ʈ�� ������ ǥ�õǴ� ����(2009.02.23) [09.02.24 ����]
		#define ASG_PCROOM_POINT_SYSTEM_MODIFY		// �Ϻ� PC�� �ý��� ����. winmain_new.h ���� (2009.03.25) // PC�� ����Ʈ �ý��� ����.(2008.06.13) [2008.07.17 ü���׼�]
	#endif // ADD_PCROOM_POINT_SYSTEM

	#define LDS_PCROOM_CONTENT_6TH				// �Ϻ� PC��� ������ �߰�. (2009.03.31)
		#define CSK_PCROOM_ITEM					// ���� ������ (ȥ���� ���� 3��) winmain_new.h ���� (2009.04.02)
		// �̵���		
		#define LDS_ADD_PCROOM_ITEM_JPN_6TH		// �ű� ������ (������ ����) (2009.03.31)
	#ifdef LDS_PCROOM_CONTENT_6TH
		
	#endif // LDS_PCROOM_CONTENT_01_6TH
#endif // ADD_CONTENTS_PCROOM_6TH

// 4. QA ���� Bug Fixed �۾� ����
// ---------------------------------------------------------------------------
#define ADD_FIX_AFTER_QA_6TH

#ifdef ADD_FIX_AFTER_QA_6TH
	#define LDS_FIX_APPLY_BUFF_STATEVALUES_WHEN_CALCULATE_CHARACTERSTATE_WITH_SETITEM	// �ɸ��� ����â�� ��Ʈ ������ ���� �� ���� ��ġ ����ÿ� ���� ���� ���� ���� ���� �� ���Ͼ����� ���� ���� �߰��ɷ�ġ��  �����Ǿ� �߰� (2009.04.13)
	#define LDS_FIX_WRONG_QUANTITY_SETITEMOPTION_WHEN_RENDER_SETITEMTOOTIP_IN_INVENTORY	// ���� ������ ��Ʈ �����۰� ������ ��Ʈ�� �κ��丮�� �ִ°�� �ش� �κ��丮 ��Ʈ ������ �ɼ� ��¿� ���� ����		(2009.04.13)
#endif // ADD_FIX_AFTER_QA_6TH

// 5. 6�� ���� ���� �׼� 1�� ���� ����
#define ADD_FIX_AFTER_6TH_TEST
#ifdef ADD_FIX_AFTER_6TH_TEST
//	#define PBG_FIX_REPAIRGOLD_DURABILITY0							// ������ 0�϶� ������ ������ �ٸ� ���� ����(09.04.13)
//	�������� Ŭ�󿡼� �������� �������� ���� ������ define ���ƾ� �� PBG_FIX_REPAIRGOLD_DURABILITY0
	#define PBG_FIX_SHIELD_MAGICDAMAGE								// ��������� ����â�� ������ ����ϴ� ���� ����(09.04.15)
	#define PBG_FIX_FENRIR_GELENALATTACK							// �渱�� Ÿ�� �Ϲݰ����� �ȵǴ� ���� (09.04.17)
	#define PBG_FIX_SKILL_RECOVER_TOOLTIP							// ȸ����ų�� �������� ��ų ���ݷ��� ��µǰ� �ִ� ����(09.04.20)
	#define PBG_FIX_SETITEM_4OVER									// ��Ʈ �������� 4�� �ʰ��Ͽ� �������� ��� ����(09.04.24)
	#define PBG_MOD_MASTERLEVEL_MESSAGEBOX							// ����� ���� �������ɸ��� ���Կ��� �߰�(09.4.24)
	#define PBG_FIX_REPAIRGOLD_DARKPAT								// ��ũȣ��,���Ǹ� ������ ���� ����(09.04.14)
	#define KJH_FIX_DARKLOAD_PET_SYSTEM								// ���λ�������â���� ��ũ�ε����� ������ ��Ȯ�ϰ� ��µ��� �ʴ� ���׼��� (09.04.16)	[JP_0226]
	#define KJH_FIX_WOPS_K32595_DOUBLE_CLICK_PURCHASE_ITEM			// NPC�������� �������� �����Ҷ�, ó���� �ι�Ŭ���ؾ� �������� ���ԵǴ� ���׼��� (09.04.16)	[JP_0348]
	#define ASG_FIX_ARROW_VIPER_BOW_EQUIP_DIRECTION					// �������� ���ο�����ۺ��� ���� ���� ���� ����.(2009.04.17)
//2�� ���� ����
	#define KJH_FIX_MOVECOMMAND_WINDOW_SIZE							// �̵����â ũ�⺯��� ������� ����� ���� ���� (09.03.02)		[JP_0420]
	#define PBG_FIX_CHARM_MIX_ITEM_WING								// ������ ���� ������ �Ǹ��� ���� ��ǰ �Ǹ� �ȵǴ� ���� ����(09.05.06)
	#define KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI					// Ȳ�ݱü� NPCâ�� �����·� �����۸� â�� ��������, �̻������� �߻��ϴ� ���׼��� (09.05.06)
	#define PBG_FIX_DARKPET_RENDER									// ��ũ�ε� ���� ���Ǹ��� ȣ���� ���� ����Ǵ� ����(09.05.08)
	#define KJH_FIX_JP0459_CAN_MIX_JEWEL_OF_HARMONY					// ��ȭ�Ǻ������� ���׷��̵� �Ҽ� �ִ� �������ε��� ������ ������ ���׼��� (09.05.08)
	#define LDS_FIX_NONINITPROGLEM_SKILLHOTKEY						// ��Ȥ �ű��ɸ��� ���� �ٷ����� �α����ߴ� �ɸ���ų����Ű�� �����ִ� ����. MainSceneȣ�⸶�� SkillKey ���̺� �ʱ�ȭ. (2009.01.20)
	#define KJH_FIX_JP0450_EQUIPITEM_ENABLE_MOVECOMMAND				// �̵����â�� ������ �̵��Ҽ� ���� ������ �������� ���콺�Ⱦ��� ���� �̵��ϴ� ���� ���� (09.05.08)
//	#define PBG_FIX_SKILLHOTKEY										// ���� ��ų�� ��Ű ��ȣ ����ϴ°� ���� ���Žÿ� ����(09.05.11)
	#define PBG_FIX_CHARM_MIX_ITEM_WING_TOOLTIP						// ������ ���� ���� �߸� ��µǴ� ����(09.05.11)
	#define LDS_FIX_SYNCRO_HEROATTACK_ACTION_WITH_SERVER			// wops 33863 - ���� ��ų ������ �������� ��ų �ޱ����� �̸� ��ų�ߵ��� �ɷ� ���� ��ų ���ϸ��̼��� �߸� ���. (09.04.22)
	#define LDK_FIX_MOTION_INTI_AT_THE_LOADINGWORLD					// wops 34113 - ����ε��� ��� �ʱ�ȭ(09.04.14)

	#define PBG_FIX_DARKPET_TIPUPDATE								// ��ũ���� ����ġ�� ǥ�ð� ���ŵ��� �ʴ´�.�� �����ÿ��� ���ŵǴ� ���׼���(09.05.29)
	#define PBG_FIX_MOVECOMMAND_WINDOW_SCROLL						// ��ũ�� ���콺 ���� Ŭ������ ������ �� ���� ���� ����(09.05.29)
	#define PBG_FIX_DARKPET_DURABILITY								// ��ũ�ε� �� ������ ���� ���� ����(09.05.29)
	#define PBG_FIX_DARKSPIRIT_ACTION								// ��ũ�ε� ���Ǹ��� �ʷε��� ���� ������ ����� ������ �ִ� ���� ����(09.05.29)
	#define PBG_FIX_LODING_ACTION									// �ε��ÿ� ���� �������� �ʴ�(���) ����(09.05.25)
	#define KJH_FIX_JP0467_RENDER_DARKLOAD_PET_OTHER_CHARATER		// �ٸ��ɸ����� ��ũ�ε����� �����ǰų� �����Ҷ�, ȭ��� ��ȭ���� �ʴ� ���� ���� (09.06.03)
	#define KJH_FIX_GOLD_RABBIT_INDEX								// Ȳ���䳢 �ε��� ���� (09.06.08)

	#define LDK_FIX_PCROOM_INFOMATION								// �ǽù� ����Ʈ ���� ������� ���� ����ó��(09.07.14)
	#define LDK_FIX_CHARM_MIX_ITEM_WING_TOOLTIP						// ������ ���� ���� �߸� ��� �� ���� �����Ǵ� ����(09.07.20)

	#define YDG_FIX_DARKSPIRIT_CHAOSCASTLE_CRASH					// ��ũ���Ǹ� ī����ĳ������ ��������ؼ� �տ���� ���â ������ ƨ��� ���� (09.07.17)
	#define YDG_FIX_SOCKETITEM_SELLPRICE_BUG						// ���Ͼ����� �ǸŰ��� ���� (09.09.03)
#endif //ADD_FIX_AFTER_6TH_TEST

#endif // ADD_TOTAL_CHARGE_6TH

#endif // SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE

/*---------------------------------���� ���� �κ� ����ȭ 6��-------------------------------------*/


#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 4.5 - PK�ʵ�/��ī����/�׺�/�Ҵ��� (09.06.23)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SEASON4_5										
#ifdef SEASON4_5

	//------------------------------------------------
	// ������ �߰�
	//------------------------------------------------
	// - ������
	#define KJH_ADD_09SUMMER_EVENT					// 09�� �����̺�Ʈ		(09.06.23)

	// - ����
	#define YDG_ADD_NEW_DUEL_SYSTEM					// ���ο� ���� �ý��� (2009.01.05) [09.03.19 �׼�]
	#ifdef YDG_ADD_NEW_DUEL_SYSTEM
		#define YDG_ADD_NEW_DUEL_UI					// ���ο� ���� ���� UI �߰� (2009.01.05) [09.03.19 �׼�]
		#define YDG_ADD_NEW_DUEL_PROTOCOL			// ���ο� ���� ���� �������� �߰� (2009.01.08) [09.03.19 �׼�]
		#define YDG_ADD_NEW_DUEL_NPC				// ���ο� ���� ���� NPC Ÿ������ �߰� (2009.01.19) [09.03.19 �׼�]
		#define YDG_ADD_NEW_DUEL_WATCH_BUFF			// ���ο� ���� ���� ���� �߰� (2009.01.20) [09.03.19 �׼�]
		#define YDG_ADD_MAP_DUEL_ARENA				// ���ο� ������ �� �߰� (2009.02.04) [09.03.19 �׼�]
	#endif	// YDG_ADD_PVP_SYSTEM

	// - �ں���
	#define PBG_ADD_PKFIELD							// PK�ʵ� �߰�(2008.12.29) [09.03.19 �׼�]
	#define PBG_ADD_HONOROFGLADIATORBUFFTIME		// �������� �� ���� �ð� ���� �߰�(2009.03.19) [09.03.19 �׼�]

	// - �̵���
	#define LDK_ADD_GAMBLE_SYSTEM					// ���Ҹ� ���� �̱� ���� (09.01.05) [09.03.19 �׼�]
	#ifdef LDK_ADD_GAMBLE_SYSTEM
		#define LDK_ADD_GAMBLE_NPC_MOSS				// �׺� ���� �� [09.03.19 �׼�]
		#define LDK_ADD_GAMBLE_RANDOM_ICON			// �׺�� �������� ������ [09.03.19 �׼�]
		#define LDK_ADD_GAMBLERS_WEAPONS			// �׺����� ���� ����� [09.03.19 �׼�]
	#endif //LDK_ADD_GAMBLE_SYSTEM

	// - ������
	#define PJH_ADD_PANDA_PET						// ��� ��
	#define PJH_ADD_PANDA_CHANGERING				// ��� ���Ź���


	//------------------------------------------------
	// ���׼���
	//------------------------------------------------
	// - ������
	#define KJH_FIX_MOVE_HERO_MOUSE_CLICK_EFFECT			// ĳ���� �̵��� ���콺Ŭ�� ����Ʈ�� �̵����� ���ϴ� ���� �����Ǵ� ���� ���� (09.03.04) [09.03.19 �׼�]
	#define KJH_FIX_GET_ZEN_SYSTEM_TEXT						// �׺�������� �����۱��Խ� ������ �޼����� ������ ����. (09.03.18) [09.03.19 �׼�]
	#define KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM	// ��ũ�ε尡 �κ��� ���� �����ϰ� ������, ������ ����Ұ��� ������ ���׼��� (09.04.27)
	#define KJH_FIX_WOPS_K33479_SELECT_CHARACTER_TO_HEAL	// ĳ���Ϳ��� �ѷ��׿�����, ������ ġ�ὺų��ȭ���� ĳ���� ������ �� �ȵǾ����� ���׼��� (09.04.27)
	#define KJH_FIX_CHAOTIC_ANIMATION_ON_RIDE_PET			// ����Ÿ�� ��ũ�ε� ī��ƽ���̾� ��ų�� �ִϸ��̼Ǽ��� (08.12.18)
	#define KJH_MOD_CAN_TRADE_PANDA_PET						// �Ҵ��� ���� �ŷ� ���� - �ؿܸ� ���� (09.07.07)

	// - �ּ���
	#define CSK_FIX_UI_FUNCTIONNAME							// UI���� �Լ��� ����(2009.01.22) [2009.03.26 �׼�]
	#define CSK_FIX_ANIMATION_BLENDING						// �ִϸ��̼� ������ ���� �ȵǰ� �ɼ� �ְ� ����(2009.01.29) [2009.03.26 �׼�]
	#define CSK_FIX_ADD_EXEPTION							// dmp���� �м��غ��� getTargetCharacterKey �Լ����� ƨ��°ɷ� �����Ǽ� ����ó�� �߰�(2009.01.29) [2009.03.26 �׼�]

	// - �ں���
	#define PBG_FIX_PKFIELD_ATTACK							// PKFIELD���� �������� ���ݵǴ� ����(09.04.02) [2009.04.06 �׼�]
	#define PBG_FIX_PKFIELD_CAOTIC							// ī��ƽ ���̾� Ż �Ϳ��� ���� ����(09.04.07) [2009.04.13 �׼�]
	#define PBG_FIX_GUILDWAR_PK								// PKFIELD���� ���� �߿� �Ϲ��� ���ݾȹ޴� ���� ����(09.04.07) [2009.04.13 �׼�]
	#define PBG_FIX_CHAOTIC_ANIMATION						// ī��ƽ ���̾� �ִϸ��̼� ����(09.06.11)
	#define PBG_FIX_DARK_FIRESCREAM_HACKCHECK				// ��ũ ���̾ũ�� (����)��üũ���� ���� ����(09.06.22)

	// - �̵���
	#define LDK_FIX_INVENTORY_SPEAR_SCALE					// �κ��丮 ����-spear ũ�� ó�� if�� ���� [09.03.19 �׼�]

	// - ����
	#define YDG_FIX_INVALID_TERRAIN_LIGHT					// �޸� ħ�� ���� ����(���� ����) (2009.03.30) [2009.04.13 �׼�]
	#define YDG_FIX_MEMORY_LEAK_0905						// �޸� ���� ���� (2009.05.11) [��ġ�ȵ�]
	#define YDG_FIX_INVALID_SET_DEFENCE_RATE_BONUS			// ����Ʈ �߰� ����ǥ�� ������ 10%�� �ƴ϶� ������� 10%�� (2009.04.15) [��ġ�ȵ�] wops_32937
	#define YDG_FIX_STAFF_FLAMESTRIKE_IN_CHAOSCASLE			// ī����ĳ������ ���˻� ������ ����� �÷��ӽ�Ʈ����ũ�� ������� �����ܻ� ���� (2009.04.15) [��ġ�ȵ�] wops_34747
	#define YDG_FIX_LEFTHAND_MAGICDAMAGE					// ���˻簡 �����̳� ��ٽ�Ÿ�带 �޼տ� á���� ������ �ö󰡴� ���� (2009.04.15) [��ġ�ȵ�] wops_32641
	#define YDG_FIX_BLOCK_STAFF_WHEEL						// ���˻� ������, �Ǽ� ȸ�������� ���� (2009.05.18) [��ġ�ȵ�]
	#define YDG_FIX_MEMORY_LEAK_0905_2ND					// �޸� ���� ���� 2�� (2009.05.19) [��ġ�ȵ�]

	// - �Ȼ��
	#define ASG_FIX_PICK_ITEM_FROM_INVEN					// �κ�â Ư�� ĭ���� �������� �������� �� ĳ������â���� �ɷ�ġ�� �����Ǵ� ����(2009.04.15) wops_33567
	#define ASG_FIX_MOVE_WIN_MURDERER1_BUG					// ������(ī��) ����1�� �� �� �̵�â ǥ�� ����.(2009.04.20) wops_34498

	// - ������
	#define PJH_FIX_4_BUGFIX_33								// wops_34066

	// - �̵���
	#define LDS_FIX_MASTERSKILLKEY_DISABLE_OVER_LIMIT_MAGICIAN	// ������ ��ų ��ȭ �� ��ų�鿡 ���� �䱸ġ �̴޽ÿ� �̿� �Ұ�. (09.04.22) no_wops
	#define LDS_FIX_SETITEM_WRONG_CALCULATION_IMPROVEATTACKVALUE	// ��Ʈ���������� ���� ����� ������ ������, �ɸ��� ����â�� ������ ���ȼ�ġ�� �ٸ�����. (09.04.23) wops_35131
	#define LDS_FIX_MEMORYLEAK_PHYSICSMANAGER_RELEASE		// �޸� ���� ����, Physicsmanager ������ �޸� ��ȯ ó��. (��ũ�ε� �ɸ� �ε����� ���� �� �� �߻�)(09.05.25)

// ���� 4.5 ���� �׼� ���� ����
#define ADD_FIX_AFTER_SEASON4_5_TEST
#ifdef ADD_FIX_AFTER_SEASON4_5_TEST
	#define YDG_FIX_PANDA_CHANGERING_PANTS_BUG				// ��ũ�ε� �Ǹ����� �Ҵ� ���Ź��� ����� ���� ���̴� ���� (09.07.21)
	#define YDG_FIX_DUEL_SUMMON_CLOAK						// ������ ���� ��ȯ�� ���� ������ ���� (09.07.29)

	#define	YDG_FIX_SMALL_ITEM_TOOLTIP_POSITION				// �Ϻ� ��û���� 1ĭ¥�� ������ ������ġ ���� (09.08.24)
	#define KJH_FIX_WOPS_K32595_DOUBLE_CLICK_PURCHASE_ITEM_EX	// NPC�������� �������� �����Ҷ�, ó���� �ι�Ŭ���ؾ� �������� ���ԵǴ� �߰� ���׼��� (09.08.24)

	#define YDG_FIX_TRADE_BUTTON_LOCK_WHNE_ITEM_MOVED		// �ŷ�â ������ Ʈ���̵� ��� �ű�� �ŷ���ư ��ױ�(��Ʈ������) (09.08.25)
	#define YDG_FIX_NPCSHOP_SELLING_LOCK					// NPC���� �ǸŽ� â ���ݰ� ���(��Ʈ������) (09.08.25)

	#define YDG_FIX_CATLE_MONEY_INT64_TYPE_CRASH			// ���� ����â ���� ���� ������ ƨ��� ���� (09.09.01)
	#define YDG_FIX_USED_PORTAL_CHARM_STORE_BAN				// �̵��� ���� ����ϸ� â�� ���� ���ϰ� ���� (09.09.02)

	#define PBG_FIX_CHANGEITEMCOLORSTATE							// �κ��丮 �ȿ��� �����¿� ���� ���� ��ȭ�ϵ��� ����(����/��ȣ����/�Ҵ���)(09.06.16)
	#define PBG_FIX_PETTIP									// �κ������� ��ũ�ε� ���� ���� ������ ������ ���� ������ ��µǴ� ���� ����(09.09.10)

	#define LJH_FIX_CHANGE_RING_DAMAGE_BUG					// ���Ź��� ���� ����� ���� ������ ������,����,���ַ� ������ �ǵ��� ���� (09.09.11)
	#define YDG_FIX_OVER_5_SETITEM_TOOLTIP_BUG				// ��Ʈ������ 5���� �̻� ���� ���ȵǴ� ���� ����(09.09.11)
	#define YDG_FIX_MAGIC_DAMAGE_CALC_ORDER					// ��Ʈ������ ���� ���� ��� ���� ���� (09.09.11)
	#define YDG_FIX_SETITEM_REQUIRED_STATUS_BUG				// ��Ʈ������ �䱸�ɷ�ġ ������ ��Ʈ��꿡�� ������ ���� (09.09.14)

	#define YDG_FIX_380ITEM_OPTION_TEXT_SD_PERCENT_MISSING	// 380������ �ɼǿ� SD������ % ���� ���� ���� (09.09.23)
	#define YDG_FIX_LUCKY_CHARM_VALUE_TO_0					// ����� ���� ���� 0���� ���� (09.09.23)

	#define YDG_FIX_BUFFTIME_OVERFLOW						// �����ð��� 0���� �۾����� ��ġ�� ���� (09.09.28)
	#define LJH_FIX_PET_SHOWN_IN_CHAOS_CASTLE_BUG			// ���� ī����ĳ������ ���̴� ���� ���� (09.09.29)
	#define YDG_FIX_REPAIR_COST_ADJUST_TO_SERVER_SETTING	// ���� ���� ��� ������ ���� (09.10.12)
#endif //ADD_FIX_AFTER_SEASON4_5_TEST

#endif // SEASON4_5
#endif // SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

/*--------------------------------------�κ� ����ȭ 7��------------------------------------------*/
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

#define ADD_TOTAL_CHARGE_7TH
#ifdef ADD_TOTAL_CHARGE_7TH
	// - ����
	#define YDG_ADD_CS7_CRITICAL_MAGIC_RING		// ġ��������
	#define YDG_ADD_CS7_MAX_AG_AURA				// AG���� ����
	#define YDG_ADD_CS7_MAX_SD_AURA				// SD���� ����
	#define YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM	// ��Ƽ ����ġ ���� ������
	#define YDG_ADD_CS7_ELITE_SD_POTION			// ����Ʈ SDȸ�� ����
	#define YDG_MOD_AURA_ITEM_EXCLUSIVELY_BUY	// ���� �ߺ� ���� ���� (09.11.02)

	// - �̵���
	#define LDK_MOD_PETPROCESS_SYSTEM			// �����μ��� ������Ʈ ���� ����(�ִϸ��̼� �ӵ� ���� ���� ����)(2009.09.11)
	#define LDK_ADD_CS7_UNICORN_PET				// ������ �� 
	#define LDK_FIX_CS7_UNICORN_PET_INFO		// ������ �� ĳ���� ����â ���� �߰�

	// - �ں���
	#define PBG_ADD_AURA_EFFECT					// AG SD ���� ���� ����Ʈ
#endif //ADD_TOTAL_CHARGE_7TH

// - �̵���
//#define LDK_MOD_NUMBERING_PETCREATE				// �׽�Ʈ (09.08.27)

#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
/*---------------------------------���� ���� �κ� ����ȭ 7��-------------------------------------*/


#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE  || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || defined(LDS_PATCH_GLOBAL_100520) || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 5 - ���ð���/������ȣ��/����Ʈ (09.09.11)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SEASON5										
#ifdef SEASON5
	// - ����
	#define YDG_ADD_DOPPELGANGER_EVENT						// ���ð��� �̺�Ʈ (2009.04.22)
	#define YDG_MOD_SEPARATE_EFFECT_SKILLS					// ��ų �˻��ϴ� ����Ʈ �и� (���� ���� ��) (2009.08.10)

	// - �Ȼ��
	#define ASG_ADD_NEW_DIVIDE_STRING						// ���ο� ���� ������ ���.(2009.06.08)
	#define ASG_ADD_NEW_QUEST_SYSTEM						// �� ����Ʈ �ý���(2009.05.20)

	// ���� ��ȣ�� ��Ƽ - �̵���, �̵���
	#define LDS_ADD_EMPIRE_GUARDIAN							// ���� ��ȣ��

	// - �ں���
	#define PBG_ADD_DISABLERENDER_BUFF						// �������� ���� �̹��� ó��(09.08.10)

	//------------------------------------------------
	#ifdef YDG_ADD_DOPPELGANGER_EVENT
		#define YDG_ADD_MAP_DOPPELGANGER1					// ���ð��� ��1 (��Ŭ���º��̽�) (2009.03.22)
		#define YDG_ADD_MAP_DOPPELGANGER2					// ���ð��� ��2 (��ī�������̽�) (2009.03.22)
		#define YDG_ADD_MAP_DOPPELGANGER3					// ���ð��� ��3 (��Ʋ�������̽�) (2009.03.22)
		#define YDG_ADD_MAP_DOPPELGANGER4					// ���ð��� ��4 (ĭ����1�����̽�) (2009.03.22)
		#define YDG_ADD_DOPPELGANGER_MONSTER				// ���ð��� ���� �߰� (2009.05.20)
		#define YDG_ADD_DOPPELGANGER_NPC					// ���ð��� NPC �簡�� �߰� (2009.05.20)
		#define YDG_ADD_DOPPELGANGER_ITEM					// ���ð��� ������ �߰� (2009.05.20)
		#define YDG_ADD_DOPPELGANGER_UI						// ���ð��� UI �߰� (2009.05.20)
		#define YDG_ADD_DOPPELGANGER_PROTOCOLS				// ���ð��� �������� �߰� (2009.06.23)
		#define YDG_ADD_DOPPELGANGER_PORTAL					// ���ð��� �� ��Ż �߰� (2009.07.30)
		#define YDG_ADD_DOPPELGANGER_SOUND					// ���ð��� ���� �߰� (2009.08.04)
	#endif	// YDG_ADD_DOPPELGANGER_EVENT

	#ifdef LDS_ADD_EMPIRE_GUARDIAN
		// - �̵���
		#define LDS_ADD_MAP_EMPIREGUARDIAN2					// ���� ��ȣ�� �� 2   (ȭ,  ��)
		#define LDS_ADD_MAP_EMPIREGUARDIAN4					// ���� ��ȣ�� �� 2   (��	  )
		#define LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN	// ���� ��ȣ�� �� 4   (��	  )���� ���� ���� ���̿� ī����	(504/164)
		#define LDS_ADD_EG_4_MONSTER_JELINT					// ���� ��ȣ�� �� 4   (��	  )���� ���̿� ���°� ����Ʈ		(505/165)
		#define LDS_ADD_EG_3_4_MONSTER_RAYMOND				// ���� ��ȣ�� �� 3,4 (����,��)���� �λ�ɰ� ���̸��			(506/166)
		#define LDS_ADD_EG_2_4_MONSTER_ERCANNE				// ���� ��ȣ�� �� 2,4 (ȭ��,��)���� ���ְ� ����ĭ��			(507/167)
		#define LDS_ADD_EG_2_MONSTER_2NDCORP_VERMONT		// ���� ��ȣ�� �� 2   (ȭ,  ��)���� 2������ ����Ʈ			(509/169)
		#define LDS_ADD_EG_2_MONSTER_ARTICLECAPTAIN			// ���� ��ȣ�� �� 2   (ȭ,  ��)���� ������					(514/174)
		#define LDS_ADD_EG_2_MONSTER_GRANDWIZARD			// ���� ��ȣ�� �� 2   (ȭ,  ��)���� �븶����					(515/176)

		// - �̵��� - �̸� define������ ���� define���� �۾� ����
		#define LDK_ADD_EG_MONSTER_DEASULER					// ���� ��ȣ�� 1������ ������									(508/168)
		#define LDK_ADD_EG_MONSTER_DRILLMASTER				// ���� ��ȣ�� ������ȣ����������
		#define LDK_ADD_EG_MONSTER_QUARTERMASTER			// ���� ��ȣ�� �����屳
		#define LDK_ADD_EG_MONSTER_CATO						// ���� ��ȣ�� 2������ ī��
		#define LDK_ADD_EG_MONSTER_ASSASSINMASTER			// ���� ��ȣ�� �ϻ��屳
		#define LDK_ADD_EG_MONSTER_RIDERMASTER				// ���� ��ȣ�� �⸶����
		#define LDK_ADD_EG_MONSTER_GALLIA					// ���� ��ȣ�� 4������ ������

		#define LDK_FIX_EG_DOOR_ROTATION_FIXED				// ���� ��ȣ�� ���� �Ƿɿ� ���� ȸ������(2009.07.21)
		#define LDK_ADD_EG_DOOR_EFFECT						// ���� ��ȣ�� �� ���� �ı� ����Ʈ
		#define LDK_ADD_EG_STATUE_EFFECT					// ���� ��ȣ�� �� ���� �ı� ����Ʈ

		//���� - ����
		#define	LDK_ADD_EG_MONSTER_RAYMOND					// ���� ��ȣ�� �λ�ɰ� ���̸�� (��, ��)
		#define LDK_ADD_EG_MONSTER_KNIGHTS					//���� ��ȣ�� ����	Imperial Guardian Knights	520 - 181	
		#define LDK_ADD_EG_MONSTER_GUARD					//���� ��ȣ�� ȣ����	Imperial Guardian guard		521 - 182
		#define ASG_ADD_EG_MONSTER_GUARD_EFFECT				// ���� ��ȣ�� ȣ���� (�˱� ����Ʈ)
		#define LDS_ADD_EG_MONSTER_GUARDIANDEFENDER			// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ���к�			(518/178)
		#define LDS_ADD_EG_MONSTER_GUARDIANPRIEST			// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ġ����			(519/179)

		//��
		#define LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC		//MapProcess�� RenderBaseSmoke ó�� �Լ� �߰�(09.07.31)
		#define	LDK_ADD_MAP_EMPIREGUARDIAN1					// ���� ��ȣ�� �� 1 (��, ��)
		#define	LDK_ADD_MAP_EMPIREGUARDIAN3					// ���� ��ȣ�� �� 3 (��, ��)

		#define LDK_ADD_EMPIRE_GUARDIAN_DOOR_ATTACK			// ���� ��ȣ�� ������ �ʼӼ������ϰ� ���ݰ����ϵ����� (09.08.06)

		//UI
		#define LDK_ADD_EMPIREGUARDIAN_UI					// ���� ��ȣ�� ui
		//��������
		#define LDK_ADD_EMPIREGUARDIAN_PROTOCOLS			// ���� ��ȣ�� ��������
		//item
		#define LDK_ADD_EMPIREGUARDIAN_ITEM					// ���� ��ȣ�� ������(4��:��ɼ�, ��������, ��ũ�ι���, ����)

		//��Ÿ RESOURCE - ������� 
		#define LDS_ADD_RESOURCE_FLARERED					// FLARE_RED.jpg ȿ�� �߰�

		//��Ÿ - �������	
		#define LDS_ADD_MODEL_ATTACH_SPECIFIC_NODE_			// Ư�� ���� Ư�� ��忡 �ٸ� Ư�� ���� ATTACH �ϴ� �Լ��� �߰��մϴ�. (09.06.12)
		#define LDS_ADD_INTERPOLATION_VECTOR3				// vec3_t�� ���� �Լ��� zzzmathlib.h�� �߰�. (09.06.24)
		#define LDS_MOD_INCREASE_BITMAPIDXBLURNUMBERS		// BITMAP_BLUR �ε��� ���� ����4�� ���� �ǻ�밹���� 10���� �ø��ϴ�. (09.07.02)
		#define LDS_ADD_EFFECT_FIRESCREAM_FOR_MONSTER		// ��ũ�ε��� ���̾ũ�� ��ų�� Ư�� ����(����ĭ��)�� ���̾ũ���� �߰��մϴ�. (09.07.07)
		#define LDS_MOD_EFFECTBLURSPARK_FORCEOFSWORD		// EffectBlurSpark �� �˱���� ���� ���ѿ� ������ �˱Ⱑ ��Ȥ ������ �������� �κ� ����. (09.07.28)
		#define LDS_ADD_MAP_EMPIREGUARDIAN4_MAPEFFECT		// �ָ����� �� Effect�� �߰��Ǵ� ��ƼŬ, EFFECT��.. 
		#define LDS_FIX_MEMORYLEAK_DESTRUCTORFORBMD			// BMD�� �Ҹ��ڷ� ���� ���� BMD���� �߻��� memoryleak FIXED.. (2009.08.13)

		// - �ں���
		#define PBG_ADD_RAYMOND_GUARDIANPRIEST_MONSTER_EFFECT	// (���̸��)(ġ����)���� ����Ʈ �۾�(09.07.02)

		// - ������
		#define KJH_ADD_EG_MONSTER_KATO_EFFECT					// 3������ ī�� ����Ʈ (09.07.20)
		#define KJH_ADD_EG_MONSTER_GUARDIANDEFENDER_EFFECT		// ��ȣ�� ���к� ����Ʈ (09.07.31)
	#endif //LDS_ADD_EMPIRE_GUARDIAN

	#ifdef ASG_ADD_NEW_QUEST_SYSTEM
		#define ASG_ADD_UI_NPC_DIALOGUE						// NPC ��ȭâ(2009.09.14)
		#define ASG_ADD_UI_QUEST_PROGRESS					// ����Ʈ ���� â(NPC��)(2009.05.27)
	#ifndef ASG_ADD_UI_NPC_DIALOGUE		// ������ ASG_ADD_UI_NPC_MENU ������ ��� ����.
		#define ASG_ADD_UI_NPC_MENU							// NPC �޴�â(2009.06.17)
	#endif	// ASG_ADD_UI_NPC_DIALOGUE
		#define ASG_ADD_UI_QUEST_PROGRESS_ETC				// ����Ʈ ���� â(��Ÿ��)(2009.06.24)
		#define ASG_MOD_UI_QUEST_INFO						// ����Ʈ ���� â(2009.07.06)
		#define ASG_MOD_3D_CHAR_EXCLUSION_UI				// 3D ĳ���� ǥ���� ���� UI�� �ٲ�.(2009.08.03)
		//(!����!) UI�� 3Dĳ���� ǥ���� �߰� �Ǹ� ������� �ǵ����� �ǹǷ� �������� �� ��.
	#endif	// ASG_ADD_NEW_QUEST_SYSTEM

	//------------------------------------------------
	// ���׼���
	//------------------------------------------------
	// - �̵���
	#define LDS_ADD_SET_BMDMODELSEQUENCE_					// BMD Ŭ������ ������ �ʴ� ������ BmdSequenceID�� BMDSequence ����. (09.08.05)
	#define LDS_FIX_MEMORYLEAK_BMDWHICHBONECOUNTZERO		// BoneCount==0 �� BMD�鿡 ���� BMD Destruct ������ �߻��ϴ� �޸� �� FIX. (09.08.13)
	#define LDS_FIX_MEMORYLEAK_0908_DUPLICATEITEM			// DuplicateItem() ���� �� ������ ������ Item�� �޸� ��ȯ ��ó���� �޸� �� FIX. (09.08.13)
	#define LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER			// ImageOpen�� WrapMode Param ���� �߸��Ǿ�, OpenGLERROR�� �߸� �̿� ���� FIX. (MR0 ���� �� ġ���� ������ �߻��ϹǷ�..) (09.08.18)
	#define LDS_ADD_EG_ADDMONSTER_ACTION_GUARDIANDEFENDER	// ���� ��ȣ�� ���к��� �����κ����� ���� ��ų==>Action ���� �۾�. (09.08.18)
	#define LDS_ADD_EG_ADDMONSTER_ACTION_GUARDIANDEFENDER_EX	// ���к��� 1�� ��ų(44)������ ������İ� �ٸ� ����� ���ϸ��̼� ȣ�� �� ���� (09.08.21)
	#define LDS_FIX_EG_COLOR_CHANDELIER							// release ��弭�� ���� ��ȣ�� �ָ��� ���鸮�� ���� �� �ٸ� ���� ���� (09.08.21)
	#define LDS_ADD_EG_ADDMONSTER_ACTION_GUARDIANDEFENDER_EX2	// ���к� 44�� ���и��� ��ų�� ��Ȥ �������� �ٶ󺸴� ���� ���� (09.08.24)
	#define LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL	// ���� �ڷ��迭(�ڷ�Ű�׽ý�,�����̵�) ��ų���� ������ȣ�� �������� ��� ���ϵ��� ����(09.08.28)
	#define LDS_FIX_EG_JERINT_ATTK1_ATTK2_SPEED				// ������ȣ�� ����Ʈ ����1, ����2 �ӵ� �߸��� ��ġ�� FIX �۾� (09.09.04)
	#define LDS_MOD_ANIMATIONTRANSFORM_WITHHIGHMODEL			// AnimationTransformWithAttachHighModel�Լ����� ���� arrayBone�� �ʿ��� ���� Transform���� Bone�� Vertices�� ������ �ʵ��� ����. (2009.09.09)
	#define LDS_ADD_ANIMATIONTRANSFORMWITHMODEL_USINGGLOBALTM	// AnimationTransformWithAttachHighModel�Լ��� TMArray�� Local�� ������ ���� ���꿡 TM�� Point�� �Ҿ������ �������� TM�� Global ���� ����. (09.09.07)
	#define LDS_FIX_EG_JERINT_ANIMATION_AND_SWORDFORCE_SPEED	// ����Ʈ�� ���� �ӵ� �� �˱� �ð� ���� ���۾� (09.09.08) 
// 	#define LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER	// �� �޴����� �� ���� �� ������ ��� �߻��ϴ� �޸𸮸� FIXED. (YDG_FIX_MEMORY_LEAK_0905) define�۾� ���� �߻� ������ �޸� ��ȯ�� Pet�� Effect ���϶� �߻�(Owner�� �ڽ��� �ѱ��츸)���� Effect�� ���� NULL ó�� �۾�. (09.09.17)

	// - �ں���
	#define PBG_MOD_INVENTORY_REPAIR_COST					// �ڵ������ݾ� ��������(09.06.08)
	#define PBG_ADD_NEWLOGO_IMAGECHANGE						// �ε�ȭ�� �̹��� ����(09.08.12)
	#define PJH_NEW_SERVER_SELECT_MAP						// ���� ����ȭ�� ����(09.08.17)
	#define YDG_MOD_TOURMODE_MAXSPEED						// ������ �ְ�ӵ� �ø� (2009.07.10)

	// - ����
	#define YDG_FIX_DOPPELGANGER_BUTTON_COLOR				// ���ð��� UI ��ư ��۶� �� �̻��� ���� (2009.08.14)
	#define YDG_MOD_DOPPELGANGER_END_SOUND					// ���ð��� ���� ���� �߰� (2009.08.20)
	#define YDG_DARK_SPIRIT_CRASH_BECAUSEOF_FIX_MEMORY_LEAK	// �޸� ���� ���������� �߻��� ��ũ���Ǹ� ƨ��� ���� �ӽ� ���� (2009.09.02)

	// - �Ȼ��
	#define ASG_FIX_QUEST_PROTOCOL_ADD						// �ű� ����Ʈ �������� �߰�.(2009.09.07)
	#define ASG_MOD_QUEST_WORDS_SCRIPTS						// QuestWords.txt �ִ� ��ȣ�� ȸ�� ���� (2009.10.22) (QuestWords.txt �Ϻ� ����� ������ ������ ��)

// ���� 5 ���� �׼� ���� ����
#define ADD_FIX_AFTER_SEASON5_TEST
#ifdef ADD_FIX_AFTER_SEASON5_TEST
	#define LDK_FIX_CHARACTER_UNLIVE_MOUSE_LOCK				// ���̵��� ĳ���� ������ �̵� �Ұ�(09.10.29)
	#define LDK_FIX_EMPIREGUARDIAN_UI_HOTKEY				// ���� ��ȣ��npc uiâ ���������� ĳ��â, �κ�â �ȿ��������Ѵ�(09.10.28)
	#define LDK_FIX_PETPOSITION_MULTIPLY_OWNERSCALE			// ĳ���� ����â ���� ĳ���� ũ�⿡ ���� ����ġ ����(09.10.28)
	#define YDG_FIX_DOPPELGANGER_NPC_WINDOW_SCREEN_SIZE		// ���ð��� NPCâ �������� ��Ƽâ�� �������� ����(09.10.28)
	#define YDG_FIX_MASTERLEVEL_PARTY_EXP_BONUS_BLOCK		// �����ͷ����� ��Ƽ ����ġ ���� �������� ���� ���ϵ��� ����(09.10.28)
	#define YDG_FIX_SETITEM_REQUIRED_STATUS_SECRET_POTION	// ��� ���� ��Ʈ ������ ���� ���� �߸� ������ ���� ���� (09.10.29)
	#define LJH_ADD_LOOK_FOR_MOVE_ILLEGALLY_BY_MSG			// ������ ä�ø޼����� �̿� �̵��Ҽ� ���� �ʿ� �̵��Ϸ� �ϴ��� ����(2009.10.29)
	#define PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION		// ������ ��Ʈ �ɼ� �������(09.11.04)
		
// ���� 5 3�� �������� ���� ����
	#define LJH_FIX_BUG_BUYING_AG_AURA_WHEN_USING_SD_AURA	// SD���� ���� �Ͽ��ϴ� �� AG���� ������ �� �ִ� ���� ����(09.11.16)
	#define PBG_FIX_JELINTNPC_TEXTWIDTH						// ����Ʈnpc ui���� ���� ����(09.11.10)
	#define PBG_FIX_STOPBGMSOUND							// �ε����� bgm���� ������� �ʴ� ���� ����(09.11.10)
	#define PBG_FIX_SDELITE_OVERLAY							// sd����Ʈ ���� �������� �ʴ� ���� ����(09.11.17)
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define LJH_MOD_JPN_PARTY_EXP_WITH_PARTY_BUFF			// ��Ƽ ���� ���� �߰��� ��� ����ġ ����(+190%, �Ѹ� �߰��� +10%)(09.11.19)
	#define LJH_ADD_JPN_MODIFYING_QUESTINFO_ABOUT_BC_AND_CT	// (�Ϻ���-JP_553)����Ʈâ�� ȯ������� ����ĳ���� ���� �޽��� ����(09.11.18)
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define YDG_FIX_CURSEDTEMPLE_GAUGEBAR_ERROR				// ȯ����� ���� ȹ��/��� ������ ���� ���� (2009.12.03)
	#define LJH_FIX_ITEM_CANNOT_BE_EQUIPPED_AFTER_LOGOUT	// (JP_575)�� �α��� �� �����ϰ� �ִ� ��Ʈ �������� �ɼ� ���������� �� �������� ���̻� �����Ҽ� ���� ���� ����(09.12.10)-> �ѱ��� �����ϰ�
	#define LJH_FIX_HERO_MOVES_EVEN_NOT_PRESENT				// (��������)(JP_524)������ ĳ���Ͱ� ȭ�鿡 �������� �̵��� �� �־��� ���� ���� (��:������������/���� �̵�)(09.12.11)
	#define LJH_FIX_NOT_CALCULATED_BUFF						// ��Ʈ���� ���õǾ� ������ ������� �ʾҴ� ���� ����(2010.01.15)

// ���� 5 ���䳢 �̺�Ʈ, ��Ÿ�� �н����� �߰�, ����Ʈ �ذ����� ���Ź��� ��� ����(2010.01.28)  	
	#define LJH_MOD_ELITE_SKELETON_WARRIOR_CHANGE_RING_SETTING	// �Ϻ��� ����Ʈ�ذ����� ���Ź��� ��纯��(2010.01.21)
	
	#define ADD_MOON_RABBIT_EVENT								// ���䳢 �̺�Ʈ �Ϻ��� �߰� (2010.01.31)
	#ifdef ADD_MOON_RABBIT_EVENT								
		#define KJH_PBG_ADD_SEVEN_EVENT_2008					// ���� ���ȭ 7�ֳ� �̺�Ʈ	(���䳢)(2008.10.30) 
		#define	LJH_MOD_POSITION_OF_REGISTERED_LUCKY_COIN		// ����� ���� ��� ���� ���� 2^31�� �ʿ� ���� �����̹����� ��ġ�� ���� �������� ����(2010.02.16)
	#endif //ADD_MOON_RABBIT_EVENT								
	
	#define LJH_ADD_LOCALIZED_BTNS							// Text.txt�� �ִ� ��ũ��Ʈ�� �̿��� ��/�ƴϿ�, Ȯ��/��� ��ư �߰�(2010.01.27)
	#ifdef LJH_ADD_LOCALIZED_BTNS
		#define LJH_ADD_ONETIME_PASSWORD					// ��Ÿ�� �н����� �߰�(2010.01.12~)	
	#endif //LJH_ADD_LOCALIZED_BTNS

#endif //ADD_FIX_AFTER_SEASON5_TEST
#endif	// SEASON5
#endif	// SELECTED_LANGUAGE == LANGUAGE_JAPANESE || defined(LDS_PATCH_GLOBAL_100520)|| SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE


/*--------------------------------------�κ� ����ȭ 8��------------------------------------------*/
// ġ���� ��ũ��, ��;����� Ƽ��, ���������(���ð���, �ٸ�ī, �ٸ�ī ��7��), ���̷��� ���Ź���, ���̷�����, ����Ʈ �䱸����,���� �߰�
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE  || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || defined(LDS_PATCH_GLOBAL_100520) || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

#define ADD_TOTAL_CHARGE_8TH
#ifdef  ADD_TOTAL_CHARGE_8TH
	#define YDG_ADD_HEALING_SCROLL						// ġ���� ��ũ�� (2009.12.03)
	
	#define LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12		// ��;����� Ƽ�� 7-12 �߰� (2010.02.12)

	#define LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH	//���ð���, �ٸ�ī, �ٸ�ī �� 7�� ��������� �߰�(2010.02.17)
	
	#define YDG_ADD_SKELETON_CHANGE_RING				// ���̷��� ���Ź��� (2009.12.03)
	#ifdef YDG_ADD_SKELETON_CHANGE_RING				
		#define YDG_FIX_MOVE_ICARUS_EQUIPED_SKELETON_CHANGE_RING	// ���̷��溯�Ź��� ������ ��ī�罺�� �̵��� �� ���� ���� (10.02.16)
	#endif //YDG_ADD_SKELETON_CHANGE_RING				
	
	#define ADD_SKELETON_PET							// ���̷��� �� (2009.12.03)
	#ifdef  ADD_SKELETON_PET
		#define YDG_ADD_SKELETON_PET					// ���̷��� �� 
		#define YDG_MOD_SKELETON_NOTSELLING				// ���̷��� �� ���� ���ȸ��� ����(2010.01.20)
		#define YDG_FIX_SKELETON_PET_CREATE_POSITION	// ���̷��� �� ���� ��ġ ���� (2010.01.26)
		#define LJH_FIX_IGNORING_EXPIRATION_PERIOD		// �Ϻ����� ���� �Ⱓ���� ������� �����Ƿ� bExpiredPeriod�� ������� �ʵ��� ����(2010.02.11)
		#define YDG_FIX_CHANGERING_STATUS_EXPIRE_CHECK	// ���Ź��� ���ȿø��� ���� üũ (2010.01.25)
		#define LDK_FIX_PC4_GUARDIAN_DEMON_INFO			// ���� ĳ��������â�� ���ݷ�,����,���ַ� �߰� ������ ����(09.10.15)
														//  --> ĳ��������â�� �� ������ ���� ���ַ� �߰� �������� ���� ��Ű�� ���� �߰�(10.02.19)
		#define LJH_FIX_NOT_POP_UP_HIGHVALUE_MSGBOX_FOR_BANNED_TO_TRADE	//NPC���� �Ǹ� ������ �������� �Ǹ��Ϸ��� �Ҷ� ���� �������̶�� ������ �޼��� â�� �ȳ����� ����(10.02.19)
	#endif  //ADD_SKELETON_PET
	
	#define YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT			// ���Ź��� �������� ����ϵ��� ���� (2009.12.28)
	#define ASG_ADD_QUEST_REQUEST_REWARD_TYPE			// ����Ʈ �䱸����, ���� �߰�(2009.12.15)
#endif  //ADD_TOTAL_CHARGE_8TH
#endif	//SELECTED_LANGUAGE == LANGUAGE_JAPANESE || defined(LDS_PATCH_GLOBAL_100520) || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
/*--------------------------------------������� �κ� ����ȭ 8��------------------------------------------*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 5-2, 5-3 - ��ų������ ������, �̴ϸ�, ������ ���׷��̵�(14, 15lv), �ս� �ý���, �η����� (10.04.27)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE  || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || defined(LDS_PATCH_GLOBAL_100520) || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

#define SEASON5_2
#ifdef  SEASON5_2

	#define KJH_ADD_SKILLICON_RENEWAL					// ��ų������ ������(10.01.20)

	#define PJH_ADD_MINIMAP								// �̴ϸ� 

	#define LDK_ADD_ITEM_UPGRADE_14_15					// ������ 14 15
	#ifdef LDK_ADD_ITEM_UPGRADE_14_15
		#define LDK_ADD_14_15_GRADE_ITEM_HELP_INFO			// ������ 14 15 ���� �߰�(09.12.2)
		#define LDK_ADD_14_15_GRADE_ITEM_VALUE				// ������ 14 15 �Ǹűݾ� �߰�(09.12.2)
		#define LDK_ADD_14_15_GRADE_ITEM_RENDERING			// ������ 14 15 ����ȿ�� �߰�(10.01.04) ������ 13ó�� ũ��,���� ó��
		#define LDK_ADD_14_15_GRADE_ITEM_SET_EFFECT			// ������ 14 15 ��Ʈ����Ʈȿ�� �߰�(10.01.22)
		#define LDK_ADD_14_15_GRADE_ITEM_TYPE_CHANGE		// ������ 14 15 ���� Ÿ�� ����(10.01.27)
		#define LDK_ADD_14_15_GRADE_ITEM_MODEL				// ������ 14 15 �𵨸� �߰�(10.01.18)
		#define YDG_FIX_ITEM_EFFECT_POSITION_ERROR			// ������ ����Ʈ ��ġ�� �̻��ϰ� ������ ���� (2010.01.27)
		#define LJH_FIX_NO_EFFECT_ON_WEAPONS_IN_SAFE_ZONE_OF_CURSED_TEMPLE	// ȯ������� ������������ 15���� ������ ����Ʈ ������ �ʴ� ���� ����(10.04.16)
	#endif //LDK_ADD_ITEM_UPGRADE_14_15

	#define ASG_ADD_GENS_SYSTEM							// �ս� �ý���(2009.09.14)	[����] �ս� �ý��� �������� ������ ASG_ADD_UI_NPC_MENU �������� ����. �ؿ� �߰��� ����.
	#ifdef ASG_ADD_GENS_SYSTEM
		#define ASG_ADD_INFLUENCE_GROUND_EFFECT				// �ս� ���� ���� �ٴ� ����Ʈ(2009.10.07)
		#define ASG_ADD_GENS_MARK							// �ս� ��ũ ǥ��(2009.10.09)
		#define ASG_ADD_GENS_NPC							// �ս� NPC �߰�(2009.10.12)
		#define ASG_ADD_GATE_TEXT_MAX_LEVEL					// Gate.txt �ִ� ���� �߰�.(2009.10.16)	[����] ���ҽ� ������ ���ο� �ҽ��� ������ �� ��.
		#define ASG_ADD_MOVEREQ_TEXT_MAX_LEVEL				// Movereq.txt �ִ� ���� �߰�.(2009.10.16)	[����] ���ҽ� ������ ���ο� �ҽ��� ������ �� ��.

		#define ASG_FIX_GENS_JOINING_ERR_CODE_ADD			// �ս� ���� ���� �ڵ� �߰�.(���ձ���� ����)(2009.11.12)
		#define ASG_MOD_GUILD_RESULT_GENS_MSG				// ��� ���Խ� �ս� ���� �޽���.(2009.11.23)
		#define PBG_ADD_GENSRANKING							// �ս� ��ŷ(09.12.01)
		#define PBG_FIX_GENSREWARDNOTREG					// �ս� �̰����ڰ� ��������� ���� ����(10.01.28)
		#define ASG_FIX_GENS_STRIFE_FRIEND_NAME_BLOCK		// �ս� ������������ ģ�� �̸� �ڵ��Է� ����(2010.02.03)
		#define ASG_MOD_GENS_STRIFE_ADD_PARTY_MSG			// �ս� �������� ���� ��Ƽ �޽��� �߰�.(2010.02.03)
		#define ASG_MOD_GM_VIEW_NAME_IN_GENS_STRIFE_MAP		// �ս� ������������ GM�� Ÿ���� ĳ���� �̸� ���̰�(10.02.26)
		#define LJH_FIX_DIVIDE_LINE_BY_PIXEL_FOR_GENS_RANK	// �ս����� ��ũ�̸��� �ʹ� ��� ���ٿ� �� ������ �ʾ� nPixelPerLine = 240���� ���� _ �Ϻ� ����(10.03.10)
		#define LJH_FIX_DEFINE_GENS_TEAMNAME_LENTH_TO_16	// �Ϻ����� ��� �� ���ڸ� 2����Ʈ�� ó���ϴµ� �ٳ׸�Ʈ�� ǥ���ϱ� ���� 12����Ʈ�� �ʿ��ϱ� ������ ����(10.03.15)
		#define PBG_MOD_STRIFE_GENSMARKRENDER				// ������������ǥ�� ����(10.02.18)
		#define LJH_FIX_UNABLE_TO_TRADE_OR_PURCHASE_IN_TROUBLED_AREAS	// ������������ /�ŷ�, /���� ��ɾ� ���� (10.03.31)
		
		#define DEFINES_FOR_FOREIGN_COUNTRIES_WHERE_WITHOUT_APPLYING_MU_BLUE	// !!! MU BLUE�� ����ǰ� ���� �� define ���� !!!
		#ifdef  DEFINES_FOR_FOREIGN_COUNTRIES_WHERE_WITHOUT_APPLYING_MU_BLUE
			#define LJH_MOD_TO_USE_ISBLUEMUSERVER_FUNC		// ��簡 ������� ���� �������� ���� ������ �ִ� ������ ������� �Ǻ��ϱ� ���� ����(10.03.17)
			#define LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC	// KJH_ADD_INGAMESHOP_UI_SYSTEM�� ���� ���ǵ� �Լ��� ����ϱ� ���� �߰� (10.03.17)
		#endif  //DEFINES_FOR_FOREIGN_COUNTRIES_WHERE_WITHOUT_APPLYING_MU_BLUE
	#endif	// ASG_ADD_GENS_SYSTEM

	
	#define LDS_ADD_MAP_UNITEDMARKETPLACE				// ���� ���� ���� (�η� ����) �߰� (09.12.04)
	#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
		#define LDS_ADD_NPC_UNITEDMARKETPLACE				// NPC �η����� 1.������ ���� �� ��ü ���, 2.���� ���� �ٸ���, 3.���� �� ��Ÿ ��ȭ ������ ���� ũ����ƾ (09.12.15)
		#define LDS_ADD_UI_UNITEDMARKETPLACE				// UI �η����� �޼��� ó�� 1.ī�����ɽ� ���� �Ұ� 2.������û�Ұ� 3.��Ƽ��û �Ұ� 4.
		#define LDS_ADD_SERVERPROCESSING_UNITEDMARKETPLACE	// �������� ���� ó�� 1.���ս�������� �̵� 2. (09.12.23)
		#define LDS_ADD_SOUND_UNITEDMARKETPLACE				// ���ս��� ȯ����, ����� ó��. (10.01.12)
		#define LDS_ADD_MOVEMAP_UNITEDMARKETPLACE			// ���̵� �����쿡 "���� ����" �߰�. (10.01.12)
		#define LDS_ADD_EFFECT_UNITEDMARKETPLACE			// ���ս��� NPC � �߰� EFFECT. (10.01.14)
		#define LDK_FIX_CHARACTER_UNLIVE_MOUSE_LOCK			// ���̵��� ĳ���� ������ �̵� �Ұ�(09.10.29)
		#define LJH_ADD_TO_USE_PARTCHARGESHOP_IN_LOREN_MARKET	// �κ�������� �̿��� �� �ִ� ��ҷ� �η����� �߰�(10.03.31)
		#define LDS_FIX_MEMORYLEAK_WHERE_NEWUI_DEINITIALIZE		// �η����� DEAD���� : NewUI �� ��� ó�� �޸� �̹�ȯ���� ���� �޸� ���� �۾� (10.03.23)
		#define LJH_ADD_SAVEOPTION_WHILE_MOVING_FROM_OR_TO_DIFF_SERVER	// (JP_622, JP_624)(��������)�ٸ� ����(���� ��������, �η�����)�������� �Ǵ� �ٸ� ������ �̵��� �� �ɼ��� ���� ���� �ʴ� ���� ����(10.04.16)
	#endif // LDS_ADD_MAP_UNITEDMARKETPLACE

	#define KJH_FIX_MOVE_ICARUS_EQUIPED_PANDA_CHANGE_RING		// �Ҵ����Ź��� ������ ��ī�罺�� �̵��� �� ���� ���� (09.11.30)

// ���� 5-2, 5-3 �������� ���� ���� (10.05.13)
	#define ADD_FIX_AFTER_SEASON5_3_REAL_SERVER_UPDATE
	#ifdef ADD_FIX_AFTER_SEASON5_3_REAL_SERVER_UPDATE 
		#define LJH_FIX_CHANING_FONT_FOR_DUAL_WATCHUSER_NAME	// ������ �����ϴ� ���� ���̵��� ��Ʈ�� ��������� '�Ϲ�'�� '����'�� �ݺ��ϸ� ���� �Ǵ� ���� ����(10.05.03)
		#define LJH_FIX_INCORRECT_SCHEDULE_FOR_BC_FREE_TICKET	// ���� 80������ ĳ���Ͱ� �����𿡿��� [����ĳ�����������]�� Ŭ���� ���, �������� ����Ʈ Ÿ�ӽ������� ǥ�õ��� �ʴ� ���� ����(10.05.04)
		#define LJH_FIX_CANNOT_CLICK_BASKETS_IN_CURSED_TEMPLE	// ȯ��������� ������ �� ������ �����Կ� ����Ϸ��� �� �ڿ��� �������� Ŭ���� �� ���� ���� ����(10.05.04) 
		#define LJH_FIX_NOT_INITIALIZING_BATTLECASTLE_UI		// �η������ ũ���̿�������� �̵��� �� ����UI�� �ʱ�ȭ ���� �ʾ� ȭ�� �����ϴ��� Ŭ���ص� �̵����� �ʴ� ���� ����(10.05.10)
		#define LJH_FIX_GETTING_ZEN_WITH_PET_OF_OTHER_PLAYER	// �ٸ� �÷��̾��� ���� ���� �Ծ��ִ� ���� ����(10.05.10)
	#endif //ADD_FIX_AFTER_SEASON5_3_REAL_SERVER_UPDATE

//-----------------------------------------------------------------------------
// [ ���� 5 - Part 3 �߰� ���׼���]
	#define KJH_FIX_BTS158_TEXT_CUT_ROUTINE							// UI�� �°� Text�� �ڸ��� �̻����� ���� (10.05.07)
	#define KJH_MOD_BTS173_INGAMESHOP_ITEM_STORAGE_PAGE_ZERO_PAGE	// �ΰ��Ӽ� ������ �������� ������ 0������ ��� (10.05.13)
	#define KJH_FIX_BTS179_INGAMESHOP_STORAGE_UPDATE_WHEN_ITEM_BUY	// �ΰ��Ӽ� ������ ���Խ� ������ �ǿ��� ������ �������� ���ŵǴ� ���׼��� (10.05.13)
	#define KJH_FIX_MINIMAP_NAME									// �̴ϸʿ��� NPC/Portal Name �� ©���� ���� ���� (10.05.14) - minimap ��ũ��Ʈ ��� ��������
	#define KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL			// ��ų ������ ���� �䱸ġ�� ���� ��ų ��� ���� (10.05.17)
	//^#define KJH_FIX_EMPIREGUARDIAN_ENTER_UI_RENDER_TEXT_ONLY_GLOBAL	// ������ȣ�� ���� UI(����ƮNPC) Text ���� (10.05.17) - �۷ι� ����
	//^#define KJH_FIX_DOPPELGANGER_ENTER_UI_RENDER_TEXT_ONLY_GLOBAL	// ���簻�� ���� UI(�簡��NPC) Text ���� (10.05.19) - �۷ι� ����
	#define KJH_FIX_BTS167_MOVE_NPC_IN_VIEWPORT						// ����Ʈ�ȿ� NPC�� ������ NPC�� ���ڱ� �̵��ϴ� ���׼��� (10.05.17)
	#define KJH_MOD_BTS191_GOLD_FLOATING_NUMBER						// �������̳� ĳ�� �ݾ���, �Ҽ����ڸ����� ��� (10.05.18)
	#define KJH_FIX_BTS204_INGAMESHOP_ITEM_STORAGE_SELECT_LINE		// �ΰ��Ӽ� �����Կ��� 1��° ������ ����, ��Ŀ���� 3��° ���������� ���õǴ� ���׼��� (10.05.18)
	#define	KJH_FIX_BTS206_INGAMESHOP_SEND_GIFT_MSGBOX_BLANK_ID		// �ΰ��Ӽ� �����ϱ� �޼���â���� ID�Է����� �ʰ� Ȯ�� ��ư Ŭ����, ����Ȯ�� �޼���â�� �ߴ� ���� (10.05.18)
	#define KJH_MOD_COMMON_MSG_BOX_BTN_DISABLE_TEXT_COLOR			// ���� �޼����ڽ� ��ư Disable�� ���ڻ� ���� (10.05.18)
	//^#define	KJH_MOD_BTS208_CANNOT_MOVE_TO_VULCANUS_IN_NONPVP_SERVER	// nonPVP �����ϴ� ��ī������ �̵��Ұ� (10.05.18)
	#define KJH_FIX_BTS207_INGAMESHOP_SEND_GIFT_ERRORMSG_INCORRECT_ID	// �ΰ��Ӽ� �����ϱ⿡�� ���� ���̵� Ʋ������ ���� �޼��� (10.05.19)
	#define KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP					// ����Ʈ SD���� ������ �ȳ����� ���� ���� (10.05.24)
	#define KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP					// �Ⱓ�������� �Ⱓ�� ���� ���� ���� ���� (10.05.24)
	#define KJH_MOD_INGAMESHOP_GIFT_FLAG							// �ΰ��Ӽ� �����ϱ� Flag�� �����ϱ� ��ư On/Off (10.05.25)
	#define ASG_FIX_QUEST_GIVE_UP									// ����Ʈ ���� ���� ����. ����Ʈ ����(QS) 0xfe������.(10.05.26)

//-----------------------------------------------------------------------------
// [ ���� 5 - Part 3 �߰��۾�]
	#define KJH_MOD_INGAMESHOP_UNITTTYPE_FILED_OF_PRODUCT_SCRIPT	// Product ���Ӽ� ��ũ��Ʈ�� UnitType�ʵ�� ������ ���� (10.04.22) - 10.03.29���� �ΰ��Ӽ� ���̺귯�� ����
	#define KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// �ΰ��Ӽ� ������ ������ ���� ������� ���� (10.04.27)
	#define KJH_MOD_INGAMESHOP_DOMAIN_EACH_NATION					// ������ ���Ӽ� ������ ���� (10.05.04)

//-----------------------------------------------------------------------------
// [ ���� 5 - Part 3 ���� ���׼���]
	#define KJH_FIX_INIT_EVENT_MAP_AT_ABNORMAL_EXIT			// ������������ ����� �̺�Ʈ�� �ʱ�ȭ (10.04.20)

	//^#define KJH_FIX_MOVE_MAP_GENERATE_KEY				// �� �̵�(&���̽�ų ��������)�� �����Ǵ� Ű�� ����

	#define ASG_ADD_LEAP_OF_CONTROL_TOOLTIP_TEXT			// ����� ��� ���� �ؽ�Ʈ �߰�(2010.01.28)
	//^#define PBG_FIX_GAMECENSORSHIP_1215							// 12/15�� �̿밡�� ��ũ ���� ���׼���(10.02.09)
	#define LDS_FIX_DISABLE_INPUTJUNKKEY_WHEN_LORENMARKT		// ���ս��� �̵� �ÿ� ������� Ű �� ���콺 ��ǲ �Է��� ���� �ʾ� ����� ������ �ϰ� Skip ó��. (10.02.02) 
	//^#define PBG_MOD_GAMECENSORSHIP_RED						// ������ ��쵵 18�̻󰡴ɰ��� ����(09.01.26)[10.02.04������ġ�� �׼�/���� ��� ���� ����]
	#define LDS_FIX_DISABLEALLKEYEVENT_WHENMAPLOADING			// ���̵� ��û���� �����κ��� ���̵� ����� ���������� ��� Ű�Է��� �����ϴ�. (�η�����, ���� ���� �̵� ��û�ÿ� esc�� �ɼ�â "��������"ȣ������ ��� Ű�Է��� �ȵǴ� ���� ). (10.01.28)

//-----------------------------------------------------------------------------
// [ ���� 5 - Part 2 ���� ���׼���]
	#define LJH_FIX_EXTENDING_OVER_MAX_TIME_4S_To_10S			// �ؿܻ���ڵ� �Ϻ� ����ڿ��� ĳ�ü��� ������ �ʾ� Max Time�� ���� 4�ʿ��� 10�ʷ� ����(09.12.17)
	#define KJH_FIX_INGAMESHOP_SCRIPTDOWN_BUG					// �ΰ��Ӽ� ��ũ��Ʈ �ٿ�ε� ���� (09.12.28)
	#define PJH_FIX_HELP_LAYER									// ���� ���̾� �ֻ����� ����(2009.12.01)
	#define LDS_FIX_VISUALRENDER_PERIODITEM_EXPIRED_RE			// �ΰ��Ә� �����۵��� �����, �����鿡 ���� �Ⱓ�� ���� ���� ��� �Ҵ� ó�� (�κ��丮�󿡼� ���־� ó����.) (09.12.10)
	#define KJH_FIX_SOURCE_CODE_REPEATED						// ���� �ҽ��ڵ� �ߺ��Ȱ� ���� (09.10.12)
	#define ASG_MOD_QUEST_OK_BTN_DISABLE						// ����Ʈ ���� Ȯ�� ��ư ��Ȱ��ȭ ���� �߰�(2009.11.23)
	#define LDK_MOD_BUFFTIMERTYPE_SCRIPT						// ����Ÿ�̸� Ÿ�԰��� buffEffect.txt�� Viewport�� �޾Ƽ� ����(09.11.10) - enum.h : Ÿ�̸� �ʿ��� ���� ��Ͻ� eBuffTimeType�� ��Ͼ��ص� ��
	#define KJH_FIX_INGAMESHOP_INIT_BANNER						// �ΰ��Ӽ� ��� �ٿ�ε� �� �ʱ�ȭ���� �ʾ� Render�� �ȵŴ� ���� (09.11.10)
	
	
	#define YDG_ADD_GM_DISCHARGE_STAMINA_DEBUFF					// GM�� �Ŵ� ���¹̳� ���� ����� (2009.11.13)
	#define PBG_FIX_MSGBUFFERSIZE								// �޽����ڽ��� ���� �߸��� ���׼���(09.11.13)
	#define PBG_FIX_MSGTITLENUM									// �޽����ڽ� title���� �߸������� ���� ����(09.11.13)
	#define LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING				// �����̾�� ������ ���� �ؽ�Ʈ ���� (09.11.06)
	#define LDK_MOD_TRADEBAN_ITEMLOCK_AGAIN						// �Ϻ� ���� �������� Ʈ���̵� ���� �Ұ��� ����(NOT DEFINE ó��)(09.10.29) (��ȹ���� ���÷� �ٲ� ��.��+)
	#define KJH_MOD_SHOP_SCRIPT_DOWNLOAD						// �� ��ũ��Ʈ �ٿ�ε� ��� ���� (09.11.09)
	#define KJH_FIX_SHOP_EVENT_CATEGORY_PAGE					// �� �̺�Ʈ ī�װ� ������ ���� ���� (09.11.09)
	#define KJH_FIX_EXPIRED_PERIODITEM_TOOLTIP					// �Ⱓ����� �Ⱓ�� �������� ����Render�� �ȵŴ� ���� ���� (09.11.09)
	#define LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR	// �ΰ��Ә� �����۵��� ����, ����� �ø����� STATUS ��ġ �ݿ�.
	#define LDK_FIX_NEWWEALTHSEAL_INFOTIMER_AND_MOVEWINDOW		// ǳ�������� �������� �ð�ǥ�� �߰�, �������� �̵�â ��Ȱ��ȭ (09.11.06)
	#define PBG_FIX_TRADECLOSE									// �ŷ��� �κ��� �����ÿ� �ŷ�â�� ������ �ʴ� ���� ����(09.11.06)
	#define LDS_MOD_INGAMESHOPITEM_POSSIBLETRASH_SILVERGOLDBOX	// ��,�� ���� �����Ⱑ �����ϵ���.
	#define KJH_MOD_RENDER_INGAMESHOP_KEEPBOX_ITEM				// ���Ӽ� ������ �������� ������ 1���϶� Render ���� (2009.11.03)
	#define LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE				// ȥ������ȭ ������ ���� ����(09.10.29)
	#define KJH_MOD_INGAMESHOP_PATCH_091028						// �ΰ��Ӽ� ���� - �̺�Ʈ ī�װ�, �ΰ��Ӽ� ���̺귯�� ������Ʈ (09.10.28)
	#define LDK_FIX_BLUESERVER_UNLIMIT_AREA						// ��缷 ���� �̵�â �̵����� ������ �߰����� ���� ����(09.10.28)
#endif  //SEASON5_2
#endif	//SELECTED_LANGUAGE == LANGUAGE_JAPANESE || defined(LDS_PATCH_GLOBAL_100520) || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ���� 5-2, 5-3
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if	SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE 
	#define LJH_MOD_DOMAIN_NAME_TO_IP_FOR_VIETNAM_VERSION	// ��Ʈ�� �ű� ���Ӽ��� ��ü�� �ڿ� ���� ���������� �������� ���� �����Ƿ� �Է� (10.04.12)
	#define KJH_FIX_BTS167_MOVE_NPC_IN_VIEWPORT						// ����Ʈ�ȿ� NPC�� ������ NPC�� ���ڱ� �̵��ϴ� ���׼��� (10.05.17)
#endif	//SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE

/*--------------------------------- �ؿ� ������ ���� ���� ���� -------------------------------------*/
#if	SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE
	#define LJH_FIX_BUG_CASTING_SKILLS_W_CURSOR_OUT_OF_VIEWPORT			// (��������)���콺 ������ ��ư Ŭ�� �� Ŀ���� ���Ӻ���Ʈ�� ��� �κ�â� �������� ����� ��� ���� �ִ� ���� ����(09.12.02)
	#define PBG_MOD_VIEMAPMOVE											// ��Ʈ�� �̵�â �̵��� ���� ���� �̵� �����ϰ� ����(09.12.07) 
	#define LJH_FIX_NO_MSG_FOR_FORCED_MOVEOUT_FROM_BATTLESOCCER			// �����౸�� ��帶���Ͱ� �ƴ� �ڽ��� ������ ����� ����� ������ ������ �� ��� �޼��� ������� ����(09.12.28) 
	#define YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT							// ���Ź��� �������� ����ϵ��� ���� (2009.12.28)
	#define LJH_MOD_EXTENDING_NUM_OF_MIX_RECIPES_FROM_100_TO_1000		// �� ���� â���� �����Ҽ� �ִ� ������ ���� ������ 100������ 1000���� ����(10.02.23)
	#define LJH_FIX_LOADING_INFO_OF_AN_OTHER_CHARACTER_IN_LOGIN			// (JP_607)(��������)ĳ���� ����ȭ�鿡�� ĳ���� B�� �����ϰ� ĳ���� A�� Ŭ���ϸ鼭 ����Ű�� ���ÿ� ������ ĳ���� B�� �Ϻ������� �α���(10.04.01)

	#define LJH_FIX_BUG_DISPLAYING_NULL_TITLED_QUEST_LIST				// (JP_618)(��������)�������� ���� ����Ʈ �ε����� �������� �ʾ� (null)�� ǥ�õǴ� �׸��� ����Ʈ ����� ���鶧 ���� �ʵ��� ����(10.04.14)
	#define LJH_FIX_BUG_SELLING_ITEM_CAUSING_OVER_LIMIT_OF_ZEN			// (JP_629)(��������)�����ѵ����� �ʰ��ϴ� �Ǹž��� �������� ���� ���ϰ� ������ �޼����� ������ �ʵ��� ����(10.04.15)
	#define LJH_FIX_BUG_MISSING_ITEM_NAMES_ITEM_HELPER_7				// (JP_633)(��������)��ȥ�� ����, �ູ�� ������ ������ �� '����+1'�̶�� ������ ���� ����(10.04.15)
	#define LJH_MOD_CANT_OPENNING_PERSONALSHOP_WIN_IN_CURSED_TEMPLE		// (JP_657)ȯ����������� ���λ���â�� ���� ���ϵ��� ����
	#define LJH_FIX_BUG_NOT_REMOVED_PET_WITH_1_DUR_WHEN_PLAYER_KILLED	// (JP_651)�÷��̾ ������ ������ ������ 1�� ���� ��������� �������� �ʴ� ���� ����(10.04.20)
	#define PBG_FIX_DROPBAN_GENS										// ������ ������ ����

#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_TAIWANESE || SELECTED_LANGUAGE == LANGUAGE_CHINESE

/*--------------------------------- �߱� �� ��û�� ���� ����(2010.10.28) -------------------------------------*/
#if SELECTED_LANGUAGE == LANGUAGE_CHINESE								
	#define KJW_FIX_CRYWOLF_NPC_MINIMAP_RENDER							// �߱��� ũ���̿����� NPC�� �̴ϸʿ� ǥ�õ��� �ʴ� ���� ����(10.10.28)
	#define KJW_FIX_CHINESE_POTION_PRICE								// �߱� ������� ������å ���ܽ�Ŵ(10.10.28)
	#define KJH_FIX_POTION_PRICE										// ���� ���డ�� ���׼��� (10.04.16)
	#define KJH_ADD_SERVER_LIST_SYSTEM									// ServerList.txt ��ũ��Ʈ �߱����� ���� (10.11.09) by LJW
	#define ASG_ADD_SERVER_LIST_SCRIPTS									// ServerList.txt ��ũ��Ʈ �߱����� ���� (10.11.09) by LJW
	#define LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA					// �߱����� ����� ����, ǳ���� ���� ����, '�� �̵�â ��� ���' �ʿ���� (10.11.13)
	#define LJW_FIX_MANY_FLAG_DISAPPEARED_PROBREM						// ������ ����(�߱� ��� �������Ʈ) ������ ������� ���� ���� (10.11.15) 
	#define	LJW_FIX_PARTS_ENUM											// ĳ���� EtcPart �κа��� enum ���� �߰� �� ���� (10.11.15)
#endif // SELECTED_LANGUAGE == LANGUAGE_CHINESE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 5-4
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
#define SEASON5_4
#ifdef  SEASON5_4
	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 4 ���� ���׼���]

	#define KJH_FIX_POTION_PRICE							// ���� ���డ�� ���׼��� (10.04.16)
	#define KJH_FIX_INIT_EVENT_MAP_AT_ABNORMAL_EXIT			// ������������ ����� �̺�Ʈ�� �ʱ�ȭ (10.04.20)
	#define PBG_FIX_SATAN_VALUEINCREASE						// ��ź ����� ��ġ ���� ���� ����(10.04.07)
	#define PBG_MOD_GUARDCHARMTEXT							// ��ȣ�Ǻ������� ��������(10.04.14)
	#define LDK_MOD_GUARDIAN_DROP_RESIZE					// ���� ��ȣ���� �ٴڿ� �������� ������ ����(10.03.04)
	#define PBG_FIX_CURSEDTEMPLE_SYSTEMMSG					// ȯ���ǻ�� �޽��� ó�� ���� ����(09.10.22)
	#define LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT			// ����ũ�� ����ȿ����ġ ��ȹ ����(HP +100, SD+500) (10.05.06)
	#define LJH_FIX_APP_SHUTDOWN_WEQUIPPING_INVENITEM_WITH_CLICKING_MOUSELBTN // ���콺 ���ʹ�ư�� ����ä�� �κ��������� �����Ϸ��� �Ҷ� ���α׷� ƨ��� ���� ����(10.04.29)
	#define KJH_FIX_INGAMESHOP_SENDGIFT_ELIXIROFCONTROL		// �ΰ��Ӽ� �����ϱ⿡�� ��ũ�ε尡 �ƴ� Ŭ������ �����ϱ� ������ �ִ¹��� ���� (10.06.23)
	#define ASG_FIX_MONSTER_MAX_COUNT_1024					// #define MAX_MONSTER 512 -> 1204�� ����(10.06.29)
	#define LJH_FIX_REARRANGE_INVISIBLE_CLOAK_LEVEL_FOR_CHECKING_REMAINING_TIME	// �������(lv1~8)�� ����ĳ��(lv0~7)�� ���̶����� 8���� ������� ��Ŭ�� �� �� �ð��� �̻��ϰ� ������ ���� ����(10.07.07) 
	#undef  LJH_FIX_IGNORING_EXPIRATION_PERIOD				// �Ϻ��� �Ⱓ���� ������� �ʾ�����  bExpiredPeriod�� ������� �ʵ��� �����߾����� ����(10.02.11)
		
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	#define LJH_MOD_SEND_TYPE_OF_PAYMENT_DUE_TO_CHANGED_LIBRARY	// ���̺귯���� ������ �ѱ��� �޶� ĳ�� Ȥ�� �������Ʈ�� �����ϴ��� ���θ� ������ ����(10.07.13)
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE
	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 4 ]
	// 1. ��ȯ���� �����ͷ���
	// - ������
	#define PJH_ADD_MASTERSKILL								//��ȯ���� �����ͷ��� �߰�(2010.03.09)
	#ifdef PJH_ADD_MASTERSKILL								
		#undef KJH_FIX_WOPS_K22193_SUMMONER_MASTERSKILL_UI_ABNORMAL_TEXT	//�ؿܿ� ��ȯ���� �����ͽ�ų �߰�(10.05.28)
	#endif //PJH_ADD_MASTERSKILL								

	//------------------------------------------------
	// 2. ����� Ȯ��
	// - �̵���, �̵���
	#define LDK_LDS_EXTENSIONMAP_HUNTERZONE					// ����� Ȯ�� �� (���� �� ������ �� ����, ������ ���� �߰�.). (10.02.18)
	#ifdef LDK_LDS_EXTENSIONMAP_HUNTERZONE						
		// - �̵���
		// �Ϲݸ��� ������
		#define LDS_EXTENSIONMAP_MONSTERS_RAKLION				// Ȯ�� �ʳ��� �Ϲ� ����. ��Ŭ���� (10.02.18)
		#define LDS_EXTENSIONMAP_MONSTERS_AIDA					// Ȯ�� �ʳ��� �Ϲ� ����. ���̴� (10.02.26)
		#define LDS_EXTENSIONMAP_MONSTERS_KANTUR				// Ȯ�� �ʳ��� �Ϲ� ����. ĭ���� (10.03.02)
		#define LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET			// Ȯ�� �ʳ��� �Ϲ� ����. ����Ǵ� (10.03.02)

		// �߰� �۾�
		#define LDS_MOD_EXTEND_MAXMODELLIMITS_200TO400			// ���� ���͸� ���� ���� (MAX_MODEL_MONSTER=200)���� �ʰ��Ͽ� ���� �߻����� (MAX_MODEL_MONSTER=400)����. (10.03.15)

		// - �̵���
		// ������ �޵��
		#define LDK_ADD_EXTENSIONMAP_BOSS_MEDUSA				// ����Ǵ� ���� ���� �޵�� (10.02.19)
		#define LDK_ADD_EXTENSIONMAP_BOSS_MEDUSA_EYE_EFFECT		// ����Ǵ� ���� ���� �޵�� �� �ܻ� ����Ʈ(10.03.03)
		#define LDK_ADD_EXTENSIONMAP_BOSS_MEDUSA_WAND_EFFECT	// ����Ǵ� ���� ���� �޵�� ������ ����Ʈ(10.03.04)
		#define LDK_MOD_EVERY_USE_SKILL_CAOTIC					// ī��ƽ ���̾� ���� ��� �����ϵ��� ����(10.03.08)

		// �� �۾�
		#define LDK_FIX_AIDA_OBJ41_UV_FIX							// ���̴ٸ� 41�� obj(��) uv �� ����(10.03.16)
		#define LDK_ADD_AIDA_OBJ77_OBJ78							// ���̴ٸ� 77,78�� obj uv�帧 �߰�(10.03.18)
	#endif // LDK_LDS_EXTENSIONMAP_HUNTERZONE

	//------------------------------------------------
	// 3. �κ����� �ý���
	// - ������
	#define LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY		// �κ����� �������� ���� �ý��� �߰�(10.02.22) 
	#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY	
		#define LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM		// �κ����� ������ �߰�-��������, ��������, ���� (10.02.26)
		#define LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2	// �߰��κ����� ������ �߰�-��ũ��, ����ũ��, ��������, ���������� (10.03.24)
	#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
	//-----------------------------------------------------------------------------
	// 4. ������ ����Ÿ��/ Season5-5 �̴Ͼ�����Ʈ, ��������
	// - ������

	//#define LEM_ADD_GAMECHU
//	#define LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 4 �߰� ���׼���_3]
	#define LEM_FIX_JP0716_INGAMESHOP_GIFT_POINT					// �����ϱ� Ȯ�� �޼��� �ڽ� �������� boolŸ�� �߰� [lem_2010.9.2]
	#define LEM_FIX_JP0714_JEWELMIXSOUND_INGAMBLESYSTEM				// �׺������ �������� �� ���� ���� �Ҹ� �߰� [lem_2010.9.8]
	#define LEM_FIX_JP0711_JEWELBOX_DROPFREE						// ITEM_POTION 141~144�����Է� ��� �����ϰ� Ǯ��. [lem_2010.9.8]
	#define LEM_FIX_SEAL_ITEM_BUYLIMIT								// ���������� ���� ���� [lem_2010.9.9]

	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 4 �߰� ���׼���_2]
	#define LEM_FIX_RENDER_ITEMTOOLTIP_FIELD						// �ٴڿ� ������ ������ ���� ���� ���� [lem_2010.8.19]
	#define LEM_FIX_USER_LOGOUT										// ������ �α׾ƿ��� �ϴ� ��� ���� ���� [lem_2010.8.19]
	#define LEM_FIX_WARNINNGMSG_DELETE								// ���� �����ۿ� ���Ͽ� �ߺ� ��뿡 ���� �޼��� ���� [lem_2010.8.19]
	#define LEM_FIX_USER_LOGOUT_SKILL_ENABLE						// �α׾ƿ� ��� ������ ���� ��ų ��� ��� [lem_2010.8.19]
	#define LEM_FIX_AUTOSKILLBAR_SAVE								// �ڵ����ݿ� �����Ǿ� �ִ� ��ų �α׾ƿ� ������ ���� [lem_2010.8.19]
	#define LEM_FIX_ITEMSET_FROMJAPAN								// ���� ĳ������ �Ϻ������� �Ϲ������� �Ǹ��Ͽ� �߻��� ����/��ȯ/����/����/������ ���׼��� [lem_2010.8.19]
	#define LEM_FIX_INGAMESHOP_BUY_TYPE								// �ΰ��Ӽ� ������ ���� ������ ���� ���� ���� [lem_2010.8.19]
	#define LEM_FIX_INGAMESHOP_ITEM_CARD							// �ΰ��Ӽ� ��ȯ���� ī�� �����ϱ� ���� [lem_2010.8.19]

	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 4 �߰� ���׼���]
	#define LEM_FIX_WARNINGMSG_BUYITEM								// ���ſ�û�� ��� �ʿ��� �����ۿ� ���Ͽ� �߰������� ���â�� ����ش�. [lem.2010.7.28]
	#define LEM_FIX_SEAL_ITEM_MAPMOVE_VIEW							// ���� ���� ��Ż ������ ����� ������ ���� �߰�[lem.2010.7.28]
	#define LEM_FIX_SERVERMSG_SEALITEM								// ���� ���� ��뿡 ���� �����޼��� ���ú� ���̽��� �߰� [lem.2010.7.28]
	#define LEM_FIX_SHOPITEM_DURABILITY_REPAIRGOLD					// ĳ�������� ������ ���� �߰� [lem.2010.7.28]
	#define LEM_FIX_ITEMTOOLTIP_POS									// �κ��丮 ������ ���� ��ġ ���� [lem.2010.7.28]
	#define LEM_FIX_MIXREQUIREZEN									// ���� �ʿ� �ݾ� �����ջ� ǥ�� [lem.2010.7.29]

	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 2 ]
	// 1. �ΰ��Ӽ� �ý���
	// - ������,�ں���
	#define KJH_PBG_ADD_INGAMESHOP_SYSTEM					// �ΰ��Ӽ� �ý���
	#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
		#define PBG_ADD_INGAMESHOP_UI_MAINFRAME				// ���������� UI(09.04.02)
		#define PBG_ADD_INGAMESHOP_UI_ITEMSHOP				// �ΰ��Ӽ� ���԰���(09.04.03)
		#define PBG_ADD_NAMETOPMSGBOX						// �ΰ��Ӽ� �޽��� �ڽ� Ʋ �����(09.05.26)
		#define KJH_ADD_INGAMESHOP_UI_SYSTEM				// �ΰ��Ӽ� �ý��� (09.08.17)
		#define KJH_ADD_PERIOD_ITEM_SYSTEM					// �Ⱓ�� ������ �ý��� (09.09.29)
		#define PBG_ADD_INGAMESHOPMSGBOX					// �ΰ��Ӽ����� �޽��� �ڽ�(09.06.24)
		#define PBG_ADD_MSGBACKOPACITY						// �ΰ��Ӽ� �޽����ڽ�â �޹�� ��Ӱ� ó��(09.07.20)
		#define PBG_ADD_ITEMRESIZE							// �ΰ��Ӽ� �������� ������ ����(09.09.10)
		#define PBG_FIX_ITEMANGLE							// �� ������ ������ ������ ����(09.10.05)
		#define PBG_ADD_MU_LOGO								// ���ο� �ΰ� ����(09.10.08)
		//^#define PBG_ADD_CHARACTERSLOT						// ĳ���� ���Ծ�����(09.05.06) - �۷ι� ����
		#define KJH_DEL_PC_ROOM_SYSTEM						// �Ǿ��� �ý��� ���� (09.10.22) - �Ǿ��� ���ӿ��δ� ���ܵ�(class CPCRoomPtSys)

		#define PBG_ADD_CHARACTERCARD					// ĳ���� ī�� (��ũ�ε�,���˻� ���� ī��) (09.05.04) - ��ȯ����ī�� �߰�(09.06.04)
		#ifdef	PBG_ADD_CHARACTERCARD					
			#undef	PSW_CHARACTER_CARD
		#endif	//PBG_ADD_CHARACTERCARD					
		//^#define LDK_ADD_INGAMESHOP_LIMIT_MOVE_WINDOW		// ���� ���� �̵�â �̵����� ����, �̵��� �������� ���� (PSW_SEAL_ITEM����) - �۷ι� ����
	#endif //KJH_PBG_ADD_INGAMESHOP_SYSTEM

	//------------------------------------------------
	// 2. �߰�������
	#define INGAMESHOP_ITEM01							// �ؿܿ��� ��ϵǾ��ְų� ���� ������ ������ ������ �߰�(2009.09.08)
	#ifdef	INGAMESHOP_ITEM01
		#define LDK_MOD_PREMIUMITEM_DROP					// �����̾������� ��������������(09.09.16)
		#define LDK_MOD_PREMIUMITEM_SELL					// �����̾������� �Ǹ���������(09.09.25)
		#define LDK_ADD_INGAMESHOP_GOBLIN_GOLD				// �����ȭ
		#define LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
		#define LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
		#define LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
		#define LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
		#define LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
		#define LDK_ADD_INGAMESHOP_SMALL_WING				// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		#define LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL			// �ű� ǳ���� ����

		#define LDS_ADD_NOTICEBOX_STATECOMMAND_ONLYUSEDARKLORD	// �ΰ��Ә� ������ // ���¿���5�� // ��ָ��¿��Ŵ� ��ũ�ε常 ��밡���� �޼��� ���.
		#define LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		#define LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
		#define LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		#define LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
		#define LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
		#define LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
		#define LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
		#define LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
		#define LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
		#define LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		#define LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
		#define LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
		#define LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	#endif	//INGAMESHOP_ITEM01
	//-----------------------------------------------------------------------------
	// [ ���� 5 - Part 2 ���� ���׼���]
	#ifdef KJH_PBG_ADD_INGAMESHOP_SYSTEM
		#define LDK_FIX_EXPIREDPERIOD_ITEM_EQUIP_WARNING			// ����� ������ �ۿ�Ұ� �� ��� 
		#define LDS_FIX_INGAMESHOPITEM_PASSCHAOSCASTLE_REQUEST		// ī����ĳ�� ���� ����� ���� ������ ��뿡 ���� ��Ŷ ������ ������ �ʴ� ���� ���� (09.11.02)
		#define KJH_FIX_RENDER_PERIODITEM_DURABILITY				// �Ⱓ�� �������϶� ������������ Render �Ǵ� ���� (2009.11.03)
		#define LDK_FIX_PERIODITEM_SELL_CHECK						// �ǸŽ� �Ⱓ�� ������ Ȯ�� �߰�(09.11.09)
		#define LDK_MOD_PC4_GUARDIAN_EXPIREDPERIOD_NOTPRINT_INFO	// ĳ��������â���� ����� ����, ��ȣ���� ��ġ ǥ�� ����(09.11.12)
		#define LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION				// ī��������,ī����ī��,����,��ȣ����,�Ҵ���,�Ҵ����Ź���,�������ǹ��� �Ϲݾ����۽� ������,���λ���,���ΰŷ� �����ϵ��� ó��(09.11.16)
		#define LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION		// �������� ����� ���� �ɷ�ġ ��� ����ó��(09.12.11)
		#define LDK_FIX_EQUIPED_EXPIREDPERIOD_AMULET_EXCEPTION		// �������� ����� ����� �ɷ�ġ ��� ����ó��(09.12.11)
		#define PBG_MOD_PANDAPETRING_NOTSELLING						// ��� �� ���� ���ȸ��� ����(10.01.11)
		#define LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM	// �η� ���� �����κ��� ���λ��� �������� ReceiveRefreshPersonalShopItem ���� �� Error Log ������ �� �ڼ��� ��� (10.03.30)
		#define KJH_FIX_BTS295_DONT_EXPIRED_WIZARD_RING_RENDER_SELL_PRICE	// �Ⱓ�� ����������� �Ⱓ�� ������� �ʾҴµ� �ǸŰ����� ������ ���� ���� (10.05.25)
	#endif // KJH_PBG_ADD_INGAMESHOP_SYSTEM
	//-----------------------------------------------------------------------------
#endif //SEASON5_4
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANESE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ���� 5-4
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
#define PBG_MOD_GM_ABILITY			//����� �����Ҽ� �ֵ��� ����(10.08.12)
#endif //SELECTED_LANGUAGE == LANGUAGE_TAIWANESE

/*----------------------------------UI or Font----------------------------------------*/

#ifndef	KJH_PBG_ADD_INGAMESHOP_SYSTEM
#define NEW_USER_INTERFACE	
#endif	//KJH_PBG_ADD_INGAMESHOP_SYSTEM
#ifdef NEW_USER_INTERFACE
	#define NEW_COMMANDS
	#define NEW_STRUCTS
	#define NEW_USER_INTERFACE_UTIL
	#define NEW_USER_INTERFACE_UISYSTEM
	#define NEW_USER_INTERFACE_INPUTSYSTEM
	#define NEW_USER_INTERFACE_SHELL
	#define NEW_USER_INTERFACE_FUNCTIONS
	#define NEW_USER_INTERFACE_PROXY
	#define NEW_USER_INTERFACE_FONT
	#define NEW_USER_INTERFACE_IMAGE
	#define NEW_USER_INTERFACE_CLIENTSYSTEM
	#define NEW_USER_INTERFACE_BUILDER
	#define NEW_USER_INTERFACE_RESOURCEFILE
	#define NEW_USER_INTERFACE_SERVERMESSAGE
	#define NEW_USER_INTERFACE_MAINFRAME_BUTTON  // �ű� UI�� ���� ��ư �߰�		

	// ��Ʈ ũ��
	#define FONTSIZE_KOREAN			12	// �ѱ���
	#define FONTSIZE_ENGLISH		12	// �۷ι�
	#define FONTSIZE_TAIWANESE		12	// �븸��
	#define FONTSIZE_CHINESE		12	// �߱���
	#define FONTSIZE_JAPANESE		15	// �Ϻ���
	#define FONTSIZE_THAILAND		12	// �±���
	#define FONTSIZE_PHILIPPINES	12	// �ʸ���
	#define FONTSIZE_VIETNAMESE		12	// ��Ʈ��

	#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
		#define FONTSIZE_LANGUAGE	( FONTSIZE_KOREAN )
	#elif SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
		#define FONTSIZE_LANGUAGE	( FONTSIZE_TAIWANESE )
	#elif SELECTED_LANGUAGE == LANGUAGE_JAPANESE
		#define FONTSIZE_LANGUAGE	( FONTSIZE_JAPANESE )
	#elif SELECTED_LANGUAGE == LANGUAGE_THAILAND
		#define FONTSIZE_LANGUAGE	( FONTSIZE_THAILAND )
	#elif SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
		#define FONTSIZE_LANGUAGE	( FONTSIZE_PHILIPPINES )
	#elif SELECTED_LANGUAGE == LANGUAGE_CHINESE
		#define FONTSIZE_LANGUAGE	( FONTSIZE_CHINESE )
	#elif SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		#define FONTSIZE_LANGUAGE	( FONTSIZE_ENGLISH )
	#elif SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
		#define FONTSIZE_LANGUAGE	( FONTSIZE_VIETNAMESE )
	#endif //SELECTED_LANGUAGE == LANGUAGE_TAIWANESE

	#ifdef _DEBUG
		#define _SHOPDEBUGMODE
	#endif //_DEBUG

#endif //NEW_USER_INTERFACE
