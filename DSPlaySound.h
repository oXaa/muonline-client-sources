#ifndef __DSPLAYSOUND_H__
#define __DSPLAYSOUND_H__


#define MAX_CHANNEL 4

#define SOUND_WIND01               0
#define SOUND_RAIN01               1
#define SOUND_FOREST01             2
#define SOUND_DUNGEON01            3
#define SOUND_TITLE01              4
#define SOUND_TOWER01              5
#define SOUND_WATER01              6
#define SOUND_DESERT01             7

#define SOUND_HUMAN_WALK_GROUND    8
#define SOUND_HUMAN_WALK_GRASS     9
#define SOUND_HUMAN_WALK_SNOW      10
#define SOUND_HUMAN_WALK_SWIM      11

#define SOUND_BIRD01               12
#define SOUND_BIRD02               13
#define SOUND_BAT01                14
#define SOUND_RAT01                15
#define SOUND_TRAP01               16
#define SOUND_DOOR01               17
#define SOUND_DOOR02               18
#define SOUND_ASSASSIN             19


#define SOUND_HEAVEN01             20
#define SOUND_THUNDERS01           21
#define SOUND_THUNDERS02           22
#define SOUND_THUNDERS03           23

//interface
#define SOUND_CLICK01              25
#define SOUND_ERROR01              26
#define SOUND_MENU01               27
#define SOUND_INTERFACE01          28
#define SOUND_GET_ITEM01           29
#define SOUND_DROP_ITEM01          30
#define SOUND_DROP_GOLD01          31
#define SOUND_DRINK01              32
#define SOUND_EAT_APPLE01          33
#define SOUND_HEART                34
#define SOUND_GET_ENERGY           35
#define SOUND_SHOUT01              36
#define SOUND_REPAIR               37
#define SOUND_WHISPER              38
#define SOUND_ALERT                39
#define SOUND_FRIEND_CHAT_ALERT    40
#define SOUND_FRIEND_MAIL_ALERT    41
#define SOUND_FRIEND_LOGIN_ALERT   42

//attack
#define SOUND_BRANDISH_SWORD01     60
#define SOUND_BRANDISH_SWORD02     61
#define SOUND_BRANDISH_SWORD03     62
#define SOUND_BRANDISH_SWORD04     63
#define SOUND_EXPLOTION01          64
#define SOUND_EXPLOTION02          65
#define SOUND_METEORITE01          66
#define SOUND_METEORITE02          67
#define SOUND_BREAK01              68
#define SOUND_JEWEL01              69
#define SOUND_ATTACK01             70

//effect
#define SOUND_THUNDER01            80
#define SOUND_OPEN_DOOR01          81
#define SOUND_OPEN_DOOR02          82
#define SOUND_LEVEL_UP01           83
#define SOUND_HEALING01            84
#define SOUND_BOW01                85
#define SOUND_CROSSBOW01           86
#define SOUND_MIX01                87
#define SOUND_FIRECRACKER1         88
#define SOUND_FIRECRACKER2         89
#define SOUND_MEDAL			       90
#define SOUND_RING_EVENT_READY	   91
#define SOUND_RING_EVENT_START	   92
#define SOUND_RING_EVENT_END	   93
#define SOUND_CHAOS_MOB_BOOM01     94
#define SOUND_CHAOS_MOB_BOOM02     95
#define SOUND_CHAOS_FALLING        96
#define SOUND_CHAOS_FALLING_STONE  97

#ifdef TAMAJJANG
#define SOUND_TAMAJJANG1           101   //  Ÿ��¯1.
#define SOUND_TAMAJJANG2           102   //  Ÿ��¯2.
#endif

#define SOUND_CHANGE_UP            102   //  ����.

#define SOUND_PHOENIXEXP			103	// �һ��� ���İ���

//player
#define SOUND_HUMAN_SCREAM01       105
#define SOUND_HUMAN_SCREAM02       106
#define SOUND_HUMAN_SCREAM03       107
#define SOUND_HUMAN_SCREAM04       108
#define SOUND_FEMALE_SCREAM01      109
#define SOUND_FEMALE_SCREAM02     110

//skill
#define SOUND_SKILL_DEFENSE       111
#define SOUND_SKILL_SWORD1        112
#define SOUND_SKILL_SWORD2        113
#define SOUND_SKILL_SWORD3        114
#define SOUND_SKILL_SWORD4        115
#define SOUND_STORM               116
#define SOUND_EVIL                117
#define SOUND_MAGIC               118
#define SOUND_HELLFIRE            119
#define SOUND_ICE                 120
#define SOUND_FLAME               121
#define SOUND_FLASH               122
#define SOUND_BONE1               123
#define SOUND_BONE2               124

#define SOUND_RIDINGSPEAR			125
#define SOUND_RAIDSHOOT				126
#define SOUND_SWELLLIFE				127
#define SOUND_FURY					128
#define SOUND_PIERCING				129
#define SOUND_ICEARROW				130
#define SOUND_TELEKINESIS			131
#define SOUND_SOULBARRIER			132
#define SOUND_BLOODATTACK			133

#define SOUND_HIT_GATE              134
#define SOUND_HIT_GATE2             135
#define SOUND_HIT_CRISTAL           136
#define SOUND_DOWN_GATE             137
#define SOUND_CROW                  138
#define SOUND_BLOODCASTLE           139

#ifdef DUEL_SYSTEM
#define SOUND_OPEN_DUELWINDOW		140
#define SOUND_START_DUEL			141
#endif // DUEL_SYSTEM

#define SOUND_DEATH_POISON1	142
#define SOUND_DEATH_POISON2	143
#define SOUND_SUDDEN_ICE1   144
#define SOUND_SUDDEN_ICE2   145
#define SOUND_NUKE1			146
#define SOUND_NUKE2			147
#define SOUND_COMBO			148
#define SOUND_FURY_STRIKE1	149
#define SOUND_FURY_STRIKE2	150
#define SOUND_FURY_STRIKE3	151
#define SOUND_LEVEL_UP		152
#define SOUND_CHAOSCASTLE   153


#define SOUND_CHAOS_THUNDER01   156
#define SOUND_CHAOS_THUNDER02   157
#define SOUND_CHAOS_ENVIR       158
#define SOUND_CHAOS_END         159

//npc
#define SOUND_NPC                  160
#define SOUND_NPC_END              210

//monster
#define SOUND_MONSTER              210
#define SOUND_MONSTER_END          450

enum
{
    SOUND_EXPAND_START          = SOUND_MONSTER_END,    //  Ȯ��� ���� ����.
    SOUND_RUN_DARK_HORSE_1      ,                       //  ���޸��� 1
    SOUND_RUN_DARK_HORSE_2      ,                       //  ���޸��� 2
    SOUND_RUN_DARK_HORSE_3      ,                       //  ���޸��� 3
    SOUND_DARKLORD_PAIN         ,                       //  ��ũ�ε� ���ö�.
    SOUND_DARKLORD_DEAD         ,                       //  ��ũ�ε� ������.
    SOUND_ATTACK_SPEAR          ,                       //  ��Ʈ�� �Ǿ� ����.
    SOUND_ATTACK_FIRE_BUST      ,                       //  ���̾����Ʈ ����.
    SOUND_ATTACK_FIRE_BUST_EXP  ,                       //  ���̾����Ʈ ������.
    SOUND_PART_TELEPORT         ,                       //  ��Ƽ�� ��ȯ.
    SOUND_ELEC_STRIKE_READY     ,                       //  �Ϸ� ��Ʈ����ũ �������.
    SOUND_ELEC_STRIKE           ,                       //  �Ϸ� ��Ʈ����ũ.
    SOUND_EARTH_QUAKE           ,                       //  �����ũ.
    SOUND_CRITICAL              ,                       //  ũ��Ƽ�� ������ Ȯ������.
    SOUND_DSPIRIT_MISSILE       ,                       //  ��ũ���Ǹ� ���Ÿ� ����.
    SOUND_DSPIRIT_SHOUT         ,                       //  ��ũ���Ǹ� ��ħ.
    SOUND_DSPIRIT_RUSH          ,                       //  ��ũ���Ǹ� ����.

    SOUND_KALIMA_AMBIENT        ,                       //  Į���� ��� ȿ���� 1.
    SOUND_KALIMA_AMBIENT2       ,                       //  Į���� ��� ȿ���� 2 ( ���� ).
    SOUND_KALIMA_AMBIENT3       ,                       //  Į���� ��� ȿ���� 3 ( ���� ).
    SOUND_KALIMA_WATER_FALL     ,                       //  ����.
    SOUND_KALIMA_FALLING_STONE  ,                       //  �������� ��.
    SOUND_DEATH_BUBBLE          ,                       //  �����ڿ� �ö���� ��ǰ.

    SOUND_KUNDUN_AMBIENT1       ,                       //  ��� ����Ʈ �ۿ� ������1.
    SOUND_KUNDUN_AMBIENT2       ,                       //  ��� ����Ʈ �ۿ� ������2.
    SOUND_KUNDUN_ROAR           ,                       //  ����� ��ȿ.
    SOUND_KUNDUN_SIGHT          ,                       //  ����� ó�� ��������.
    SOUND_KUNDUN_SHUDDER        ,                       //  ����� �ױ��� ������.
    SOUND_KUNDUN_DESTROY        ,                       //  ����� ����.
	
    SOUND_SKILL_SKULL           ,                       //  ������ ���� ���� ��ų ȿ����.
    SOUND_GREAT_POISON          ,                       //  ���� ���� ������.
    SOUND_GREAT_SHIELD          ,                       //  ���� ��.
	
	SOUND_BC_AMBIENT            ,                       //  ��� ȿ���� ( ����� ).
	SOUND_BC_AMBIENT_BATTLE1    ,                       //  ��� ȿ���� ( ���� ).
	SOUND_BC_AMBIENT_BATTLE2    ,                       //  ��� ȿ���� ( ���� ).
	SOUND_BC_AMBIENT_BATTLE3    ,                       //  ��� ȿ���� ( ���� ).
	SOUND_BC_AMBIENT_BATTLE4    ,                       //  ��� ȿ���� ( ���� ).
	SOUND_BC_AMBIENT_BATTLE5    ,                       //  ��� ȿ���� ( ���� ).
	SOUND_BC_GUARD_STONE_DIS    ,                       //  ��ȣ���� �ı�.
	SOUND_BC_SHIELD_SPACE_DIS   ,                       //  �� �ı�.
	SOUND_BC_CATAPULT_ATTACK    ,                       //  �������� �߻�.
	SOUND_BC_CATAPULT_HIT       ,                       //  �������� ���� �Ҹ�.
	SOUND_BC_WALL_HIT           ,                       //  ���� �μ�����.
	SOUND_BC_GATE_OPEN          ,                       //  ���� ����/�ݱ�.
	SOUND_BC_GUARDIAN_ATTACK    ,                       //  ����� ����.
	
	SOUND_BC_HUNTINGGROUND_AMBIENT,						// ��������� �������
	SOUND_BC_AXEWARRIOR_MOVE1	,						// �׽� ������ �̵�1
	SOUND_BC_AXEWARRIOR_MOVE2	,						// �׽� ������ �̵�2
	SOUND_BC_AXEWARRIOR_ATTACK1	,						// �׽� ������ ����1
	SOUND_BC_AXEWARRIOR_ATTACK2	,						// �׽� ������ ����2
	SOUND_BC_AXEWARRIOR_DIE		,						// �׽� ������ �ױ�
	SOUND_BC_LIZARDWARRIOR_MOVE1	,					// ���ڵ� ������ �̵�1
	SOUND_BC_LIZARDWARRIOR_MOVE2	,					// ���ڵ� ������ �̵�2
	SOUND_BC_LIZARDWARRIOR_ATTACK1	,					// ���ڵ� ������ ����1
	SOUND_BC_LIZARDWARRIOR_ATTACK2	,					// ���ڵ� ������ ����2
	SOUND_BC_LIZARDWARRIOR_DIE		,					// ���ڵ� ������ �ױ�
	SOUND_BC_POISONGOLEM_MOVE1		,					// ���� �̵�1
	SOUND_BC_POISONGOLEM_MOVE2		,					// ���� �̵�2
	SOUND_BC_POISONGOLEM_ATTACK1	,					// ���� ����1
	SOUND_BC_POISONGOLEM_ATTACK2	,					// ���� ����2
	SOUND_BC_POISONGOLEM_ATTACK3	,					// ���� ����3
	SOUND_BC_POISONGOLEM_DIE		,					// ���� �ױ�
	SOUND_BC_QUEENBEE_MOVE1		,						// ���� �̵�1
	SOUND_BC_QUEENBEE_MOVE2		,						// ���� �̵�2
	SOUND_BC_QUEENBEE_ATTACK1	,						// ���� ����1
	SOUND_BC_QUEENBEE_ATTACK2	,						// ���� ����2
	SOUND_BC_QUEENBEE_DIE		,						// ���� �ױ�
	SOUND_BC_FIREGOLEM_MOVE1	,						// �Ұ� �̵�1
	SOUND_BC_FIREGOLEM_MOVE2	,						// �Ұ� �̵�2
	SOUND_BC_FIREGOLEM_ATTACK1	,						// �Ұ� ����1
	SOUND_BC_FIREGOLEM_ATTACK2	,						// �Ұ� ����2
	SOUND_BC_FIREGOLEM_DIE		,						// �Ұ� �ױ�
	SOUND_BC_EROHIM_ENTER		,						// ������ ����
	SOUND_BC_EROHIM_ATTACK1		,						// ������ ����1
	SOUND_BC_EROHIM_ATTACK2		,						// ������ ����2
	SOUND_BC_EROHIM_ATTACK3		,						// ������ ����3
	SOUND_BC_EROHIM_DIE			,						// ������ �ױ�
	SOUND_CRY1ST_AMBIENT		,
	SOUND_CRY1ST_WWOLF_MOVE1    ,						// ������� �̵�1
	SOUND_CRY1ST_WWOLF_MOVE2    ,						// ������� �̵�2
	SOUND_CRY1ST_WWOLF_ATTACK1  ,						// ������� ����1
	SOUND_CRY1ST_WWOLF_ATTACK2  ,						// ������� ����2
	SOUND_CRY1ST_WWOLF_DIE      ,						// ������� �ױ�
	
	SOUND_CRY1ST_SCOUT1_MOVE1    ,						// ��ī��Ʈ�ٰŸ� �̵�1
	SOUND_CRY1ST_SCOUT1_MOVE2    ,						// ��ī��Ʈ�ٰŸ� �̵�2
	SOUND_CRY1ST_SCOUT1_ATTACK1  ,						// ��ī��Ʈ�ٰŸ� ����1
	SOUND_CRY1ST_SCOUT1_ATTACK2  ,						// ��ī��Ʈ�ٰŸ� ����2
	SOUND_CRY1ST_SCOUT1_DIE      ,						// ��ī��Ʈ�ٰŸ� �ױ�
	
	SOUND_CRY1ST_SCOUT2_MOVE1    ,						// ��ī��Ʈ�߰Ÿ� �̵�1
	SOUND_CRY1ST_SCOUT2_MOVE2    ,						// ��ī��Ʈ�߰Ÿ� �̵�2
	SOUND_CRY1ST_SCOUT2_ATTACK1  ,						// ��ī��Ʈ�߰Ÿ� ����1
	SOUND_CRY1ST_SCOUT2_ATTACK2  ,						// ��ī��Ʈ�߰Ÿ� ����2
	SOUND_CRY1ST_SCOUT2_DIE      ,						// ��ī��Ʈ�߰Ÿ� �ױ�
	
	SOUND_CRY1ST_SCOUT3_MOVE1    ,						// ��ī��Ʈ��Ÿ� �̵�1
	SOUND_CRY1ST_SCOUT3_MOVE2    ,						// ��ī��Ʈ��Ÿ� �̵�2
	SOUND_CRY1ST_SCOUT3_ATTACK1  ,						// ��ī��Ʈ��Ÿ� ����1
	SOUND_CRY1ST_SCOUT3_ATTACK2  ,						// ��ī��Ʈ��Ÿ� ����2
	SOUND_CRY1ST_SCOUT3_DIE      ,						// ��ī��Ʈ��Ÿ� �ױ�
	
	SOUND_CRY1ST_SORAM_MOVE1    ,						// ��ī��Ʈ��Ÿ� �̵�1
	SOUND_CRY1ST_SORAM_MOVE2    ,						// ��ī��Ʈ��Ÿ� �̵�2
	SOUND_CRY1ST_SORAM_ATTACK1  ,						// ��ī��Ʈ��Ÿ� ����1
	SOUND_CRY1ST_SORAM_ATTACK2  ,						// ��ī��Ʈ��Ÿ� ����2
	SOUND_CRY1ST_SORAM_DIE      ,						// ��ī��Ʈ��Ÿ� �ױ�
	
	SOUND_CRY1ST_BALRAM_MOVE1    ,						// ��ī��Ʈ��Ÿ� �̵�1
	SOUND_CRY1ST_BALRAM_MOVE2    ,						// ��ī��Ʈ��Ÿ� �̵�2
	SOUND_CRY1ST_BALRAM_ATTACK1  ,						// ��ī��Ʈ��Ÿ� ����1
	SOUND_CRY1ST_BALRAM_ATTACK2  ,						// ��ī��Ʈ��Ÿ� ����2
	SOUND_CRY1ST_BALRAM_DIE      ,						// ��ī��Ʈ��Ÿ� �ױ�
	
	SOUND_CRY1ST_BALGAS_MOVE1	,						// �߰��� �̵�1
	SOUND_CRY1ST_BALGAS_MOVE2	,						// �߰��� �̵�2
	SOUND_CRY1ST_BALGAS_ATTACK1	,						// �߰��� ����1
	SOUND_CRY1ST_BALGAS_ATTACK2	,						// �߰��� ����1
	SOUND_CRY1ST_BALGAS_DIE		,						// �߰��� �ױ�
	SOUND_CRY1ST_BALGAS_SKILL1	,						// �߰��� ��ų1
	SOUND_CRY1ST_BALGAS_SKILL2	,						// �߰��� ��ų1
	
	SOUND_CRY1ST_DARKELF_MOVE1	,						// ��ũ���� �̵�1
	SOUND_CRY1ST_DARKELF_MOVE2	,						// ��ũ���� �̵�2
	SOUND_CRY1ST_DARKELF_ATTACK1,						// ��ũ���� ����1
	SOUND_CRY1ST_DARKELF_ATTACK2,						// ��ũ���� ����2
	SOUND_CRY1ST_DARKELF_DIE	,						// ��ũ���� �ױ�
	SOUND_CRY1ST_DARKELF_SKILL1	,						// ��ũ���� ��ų1
	SOUND_CRY1ST_DARKELF_SKILL2	,						// ��ũ���� ��ų1
	
	SOUND_CRY1ST_DEATHSPIRIT_MOVE1	,					// �������Ǹ� �̵�1
	SOUND_CRY1ST_DEATHSPIRIT_MOVE2	,					// �������Ǹ� �̵�2
	SOUND_CRY1ST_DEATHSPIRIT_ATTACK1,					// �������Ǹ� ����1
	SOUND_CRY1ST_DEATHSPIRIT_ATTACK2,					// �������Ǹ� ����2
	SOUND_CRY1ST_DEATHSPIRIT_DIE	,					// �������Ǹ� �ױ�
	
	SOUND_CRY1ST_TANKER_ATTACK1		,					// ��Ŀ ����1
	SOUND_CRY1ST_TANKER_DIE			,					// ��Ŀ �ױ�
	SOUND_CRY1ST_SUMMON				,					// ��ȯ ȿ�� ����
	SOUND_CRY1ST_SUCCESS			,					// MVP ����
	SOUND_CRY1ST_FAILED				,					// MVP ����
	SOUND_AIDA_AMBIENT			  ,						// ���̴� �������
	SOUND_AIDA_BLUEGOLEM_MOVE1    ,						// ���� �̵�1
	SOUND_AIDA_BLUEGOLEM_MOVE2    ,						// ���� �̵�2
	SOUND_AIDA_BLUEGOLEM_ATTACK1  ,						// ���� ����1
	SOUND_AIDA_BLUEGOLEM_ATTACK2  ,						// ���� ����2
	SOUND_AIDA_BLUEGOLEM_DIE      ,						// ���� �ױ�
	SOUND_AIDA_DEATHRAIDER_MOVE1  ,						// �������̴� �̵�1
	SOUND_AIDA_DEATHRAIDER_MOVE2  ,						// �������̴� �̵�2
	SOUND_AIDA_DEATHRAIDER_ATTACK1,						// �������̴� ����1
	SOUND_AIDA_DEATHRAIDER_ATTACK2,						// �������̴� ����2
	SOUND_AIDA_DEATHRAIDER_DIE    ,						// �������̴� �ױ�
	SOUND_AIDA_DEATHTREE_MOVE1    ,						// ����Ʈ�� �̵�1
	SOUND_AIDA_DEATHTREE_MOVE2    ,						// ����Ʈ�� �̵�2
	SOUND_AIDA_DEATHTREE_ATTACK1  ,						// ����Ʈ�� ����1
	SOUND_AIDA_DEATHTREE_ATTACK2  ,						// ����Ʈ�� ����2
	SOUND_AIDA_DEATHTREE_DIE      ,						// ����Ʈ�� �ױ�
	SOUND_AIDA_FORESTORC_MOVE1    ,						// ������Ʈ��ũ �̵�1
	SOUND_AIDA_FORESTORC_MOVE2    ,						// ������Ʈ��ũ �̵�2
	SOUND_AIDA_FORESTORC_ATTACK1  ,						// ������Ʈ��ũ ����1
	SOUND_AIDA_FORESTORC_ATTACK2  ,						// ������Ʈ��ũ ����2
	SOUND_AIDA_FORESTORC_DIE	  ,						// ������Ʈ��ũ �ױ�
	SOUND_AIDA_HELL_MOVE1		  ,						// �︶�̳� �̵�1
	SOUND_AIDA_HELL_MOVE2		  ,						// �︶�̳� �̵�2
	SOUND_AIDA_HELL_ATTACK1		  ,						// �︶�̳� ����1
	SOUND_AIDA_HELL_ATTACK2		  ,						// �︶�̳� ����2
	SOUND_AIDA_HELL_ATTACK3		  ,						// �︶�̳� ����3
	SOUND_AIDA_HELL_DIE			  ,						// �︶�̳� �ױ�
	SOUND_AIDA_WITCHQUEEN_MOVE1   ,						// ��ġ�� �̵�1
	SOUND_AIDA_WITCHQUEEN_MOVE2   ,						// ��ġ�� �̵�2
	SOUND_AIDA_WITCHQUEEN_ATTACK1 ,						// ��ġ�� ����1
	SOUND_AIDA_WITCHQUEEN_ATTACK2 ,						// ��ġ�� ����2
	SOUND_AIDA_WITCHQUEEN_DIE     ,						// ��ġ�� �ױ�
	// ���(BG) ȿ����.
	SOUND_KANTURU_1ST_BG_WATERFALL	,					// ����.
	SOUND_KANTURU_1ST_BG_ELEC		,					// ���� ����ũ.
	SOUND_KANTURU_1ST_BG_WHEEL		,					// ��Ϲ���.
	SOUND_KANTURU_1ST_BG_PLANT		,					// ���� �Ĺ�.
	SOUND_KANTURU_1ST_BG_GLOBAL		,					// �� ��ü.

	// ���� ȿ����.
	SOUND_KANTURU_1ST_BER_MOVE1		,					// ����Ŀ
	SOUND_KANTURU_1ST_BER_MOVE2		,
	SOUND_KANTURU_1ST_BER_ATTACK1	,
	SOUND_KANTURU_1ST_BER_ATTACK2	,
	SOUND_KANTURU_1ST_BER_DIE		,
	SOUND_KANTURU_1ST_GIGAN_MOVE1	,					// �ⰣƼ��.
	SOUND_KANTURU_1ST_GIGAN_ATTACK1	,
	SOUND_KANTURU_1ST_GIGAN_ATTACK2	,
	SOUND_KANTURU_1ST_GIGAN_DIE		,
	SOUND_KANTURU_1ST_GENO_MOVE1	,					// ������̴�.
	SOUND_KANTURU_1ST_GENO_MOVE2	,
	SOUND_KANTURU_1ST_GENO_ATTACK1	,
	SOUND_KANTURU_1ST_GENO_ATTACK2	,
	SOUND_KANTURU_1ST_GENO_DIE		,
	
	SOUND_KANTURU_1ST_KENTA_MOVE1	,					// ��Ÿ��ν�
	SOUND_KANTURU_1ST_KENTA_MOVE2	,
	SOUND_KANTURU_1ST_KENTA_ATTACK1	,
	SOUND_KANTURU_1ST_KENTA_ATTACK2	,
	SOUND_KANTURU_1ST_KENTA_DIE		,
	SOUND_KANTURU_1ST_BLADE_MOVE1	,					// ���̵�����
	SOUND_KANTURU_1ST_BLADE_MOVE2	,					// ���̵�����
	SOUND_KANTURU_1ST_BLADE_ATTACK1	,
	SOUND_KANTURU_1ST_BLADE_ATTACK2	,
	SOUND_KANTURU_1ST_BLADE_DIE		,
	SOUND_KANTURU_1ST_SATI_MOVE1	,					// ��Ƽ�ν�
	SOUND_KANTURU_1ST_SATI_MOVE2	,
	SOUND_KANTURU_1ST_SATI_ATTACK1	,
	SOUND_KANTURU_1ST_SATI_ATTACK2	,
	SOUND_KANTURU_1ST_SATI_DIE		,
	
	SOUND_KANTURU_1ST_SWOLF_MOVE1	,					// ���ø��� ����
	SOUND_KANTURU_1ST_SWOLF_MOVE2	,
	SOUND_KANTURU_1ST_SWOLF_ATTACK1	,
	SOUND_KANTURU_1ST_SWOLF_ATTACK2	,
	SOUND_KANTURU_1ST_SWOLF_DIE		,
	
	SOUND_KANTURU_1ST_IR_MOVE1		,					// ���̾� ���̴�
	SOUND_KANTURU_1ST_IR_MOVE2		,
	SOUND_KANTURU_1ST_IR_ATTACK1	,
	SOUND_KANTURU_1ST_IR_ATTACK2	,
	SOUND_KANTURU_1ST_IR_DIE		,
	
	// 2���� ȯ�� ����
	SOUND_KANTURU_2ND_MAPSOUND_GEAR	,	// ��� �Ҹ�
	SOUND_KANTURU_2ND_MAPSOUND_INCUBATOR,	// ���� �Ҹ�
	SOUND_KANTURU_2ND_MAPSOUND_HOLE,	// NPC��ġ �Ҹ�
	SOUND_KANTURU_2ND_MAPSOUND_GLOBAL,	// ��ü���� �Ҹ�
	SOUND_KANTURU_2ND_PERSO_MOVE1	,	// �丣�ҳ�
	SOUND_KANTURU_2ND_PERSO_MOVE2	,
	SOUND_KANTURU_2ND_PERSO_ATTACK1	,
	SOUND_KANTURU_2ND_PERSO_ATTACK2	,
	SOUND_KANTURU_2ND_PERSO_DIE		,
	SOUND_KANTURU_2ND_TWIN_MOVE1	,	// Ʈ������
	SOUND_KANTURU_2ND_TWIN_MOVE2	,
	SOUND_KANTURU_2ND_TWIN_ATTACK1	,
	SOUND_KANTURU_2ND_TWIN_ATTACK2	,
	SOUND_KANTURU_2ND_TWIN_DIE		,
	SOUND_KANTURU_2ND_DRED_MOVE1	,	//	�巹���Ǿ�
	SOUND_KANTURU_2ND_DRED_MOVE2	,
	SOUND_KANTURU_2ND_DRED_ATTACK1	,
	SOUND_KANTURU_2ND_DRED_ATTACK2	,
	SOUND_KANTURU_2ND_DRED_DIE		,
	SOUND_BMS_STUN              ,                       //  ���� �ߵ�.
	SOUND_BMS_STUN_REMOVAL      ,                       //  ���� ���� �ߵ�.
	SOUND_BMS_MANA              ,                       //  ���� ���� �ߵ�.
	SOUND_BMS_INVISIBLE         ,                       //  ���� �ߵ�.
	SOUND_BMS_VISIBLE           ,                       //  ���� ����.
	SOUND_BMS_MAGIC_REMOVAL     ,                       //  ���� ����.
	SOUND_BCS_RUSH              ,                       //  ��� ���� ��ų.
	SOUND_BCS_JAVELIN           ,                       //  ���� ǥâ ��ų.
	SOUND_BCS_DEEP_IMPACT       ,                       //  ���� ����Ʈ ��.
	SOUND_BCS_DEATH_CANON       ,                       //  ���˻� ������.
	SOUND_BCS_ONE_FLASH         ,                       //  ���˻� �ϼ�.
	SOUND_BCS_SPACE_SPLIT       ,                       //  ��ũ�ε� ���� ������.
	SOUND_BCS_BRAND_OF_SKILL    ,                       //  ��ũ�ε� ���� ��ų.
	
	//^ �渱 ���� ����
	SOUND_FENRIR_RUN_1			,						//	�渱 �޸��� 1
	SOUND_FENRIR_RUN_2			,						//	�渱 �޸��� 2
	SOUND_FENRIR_RUN_3			,						//	�渱 �޸��� 3
	SOUND_FENRIR_WALK_1			,						//	�渱 �ȱ� 1
	SOUND_FENRIR_WALK_2			,						//	�渱 �ȱ� 2
	SOUND_FENRIR_DEATH			,						//	�渱 ����
	SOUND_FENRIR_IDLE_1			,						//	�渱 ���� 1
	SOUND_FENRIR_IDLE_2			,						//	�渱 ���� 2
	SOUND_FENRIR_DAMAGE_1		,						//	�渱 ������ 1
	SOUND_FENRIR_DAMAGE_2		,						//	�渱 ������ 2
	SOUND_FENRIR_SKILL			,						//	�渱 ��ų
	
	SOUND_KANTURU_3RD_MAYA_INTRO		,				//  ���� �����
	SOUND_KANTURU_3RD_MAYA_END			,				//  ���� ������
	SOUND_KANTURU_3RD_MAYA_STORM		,				//  ���� ������
	SOUND_KANTURU_3RD_NIGHTMARE_INTRO	,				//  ����Ʈ�޾� �����
	SOUND_KANTURU_3RD_MAYAHAND_ATTACK1	,				//  ���߼� ���� 1 (�ٴ� ġ��)
	SOUND_KANTURU_3RD_MAYAHAND_ATTACK2	,				//  ���߼� ���� 2 (�ճ� ����)
	SOUND_KANTURU_3RD_MAP_SOUND01		,				//  ĭ����3�� ������Ʈ ȿ����
	SOUND_KANTURU_3RD_MAP_SOUND02		,				//  ĭ����3�� ������Ʈ ȿ����
	SOUND_KANTURU_3RD_MAP_SOUND03		,				//  ĭ����3�� ������Ʈ ȿ����
	SOUND_KANTURU_3RD_MAP_SOUND04		,				//  ĭ����3�� ������Ʈ ȿ����
	SOUND_KANTURU_3RD_MAP_SOUND05		,				//  ĭ����3�� ������Ʈ ȿ����
	SOUND_KANTURU_3RD_AMBIENT			,				//  ĭ����3�� �� ȿ����
	SOUND_KANTURU_3RD_NIGHTMARE_ATT1	, 		
	SOUND_KANTURU_3RD_NIGHTMARE_ATT2	, 
	SOUND_KANTURU_3RD_NIGHTMARE_ATT3	, 
	SOUND_KANTURU_3RD_NIGHTMARE_ATT4	, 
	SOUND_KANTURU_3RD_NIGHTMARE_DIE		,  
	SOUND_KANTURU_3RD_NIGHTMARE_IDLE1	,
	SOUND_KANTURU_3RD_NIGHTMARE_IDLE2	,
	SOUND_KANTURU_3RD_NIGHTMARE_TELE	, 
	SOUND_JEWEL02						,

#ifdef WORLDCUP_ADD
	SOUND_WORLDCUP_RND1	,			
	SOUND_WORLDCUP_RND2	,		
	SOUND_WORLDCUP_RND3	,		
	SOUND_WORLDCUP_RND4	,		
	SOUND_WORLDCUP_RND5	,		
	SOUND_WORLDCUP_RND6	,		
#endif
	SOUND_XMAS_JUMP_SANTA,		// ũ�������� ���� ����(�����)
	SOUND_XMAS_JUMP_DEER,		// ũ�������� ���� ����(�罿)
	SOUND_XMAS_JUMP_SNOWMAN,	// ũ�������� ���� ����(��Ÿ)
	SOUND_XMAS_TURN,			// ũ�������� �� ���Ʈ
	// ���̺�Ʈ ���� ȿ����
	SOUND_NEWYEARSDAY_DIE,		// ���ָӴ� ������ ���� ����
	SOUND_KUNDUN_ITEM_SOUND,	// �����ǥ�� ������ 5�� ���϶� ���� ����
	SOUND_SHIELDCLASH		,
	SOUND_INFINITYARROW	,
	SOUND_FIRE_SCREAM		,	//��ũ�ε� ���̾ũ������ ȿ����.
	// 3�� ü������ ����Ʈ �� ��� ȿ����.
	SOUND_3RD_CHANGE_UP_BG_CAGE1,		// ����1
	SOUND_3RD_CHANGE_UP_BG_CAGE2,		// ����2
	SOUND_3RD_CHANGE_UP_BG_VOLCANO,		// ���
	SOUND_3RD_CHANGE_UP_BG_FIREPILLAR,	// �ұ��

	SOUND_CURSEDTEMPLE_GAMESYSTEM1,
	SOUND_CURSEDTEMPLE_GAMESYSTEM2,
	SOUND_CURSEDTEMPLE_GAMESYSTEM3,
	SOUND_CURSEDTEMPLE_GAMESYSTEM4,
	SOUND_CURSEDTEMPLE_GAMESYSTEM5,
	
	SOUND_CURSEDTEMPLE_MONSTER1_IDLE,
	SOUND_CURSEDTEMPLE_MONSTER_MOVE,
	SOUND_CURSEDTEMPLE_MONSTER1_DAMAGE,
	SOUND_CURSEDTEMPLE_MONSTER1_DEATH,
	
	SOUND_CURSEDTEMPLE_MONSTER2_IDLE,
	SOUND_CURSEDTEMPLE_MONSTER2_ATTACK,
	SOUND_CURSEDTEMPLE_MONSTER2_DAMAGE,
	SOUND_CURSEDTEMPLE_MONSTER2_DEATH,
	
#ifdef PRUARIN_EVENT07_3COLORHARVEST
	SOUND_MOONRABBIT_WALK,
	SOUND_MOONRABBIT_DAMAGE,
	SOUND_MOONRABBIT_DEAD,
	SOUND_MOONRABBIT_EXPLOSION,
#endif // PRUARIN_EVENT07_3COLORHARVEST
	
	SOUND_ELBELAND_RABBITSTRANGE_ATTACK01,
	SOUND_ELBELAND_RABBITSTRANGE_DEATH01,
	SOUND_ELBELAND_RABBITUGLY_BREATH01,
	SOUND_ELBELAND_RABBITUGLY_ATTACK01,
	SOUND_ELBELAND_RABBITUGLY_DEATH01,
	SOUND_ELBELAND_WOLFHUMAN_MOVE02,
	SOUND_ELBELAND_WOLFHUMAN_ATTACK01,
	SOUND_ELBELAND_WOLFHUMAN_DEATH01,
	SOUND_ELBELAND_BUTTERFLYPOLLUTION_MOVE01,
	SOUND_ELBELAND_BUTTERFLYPOLLUTION_DEATH01,
 	SOUND_ELBELAND_CURSERICH_MOVE01,
 	SOUND_ELBELAND_CURSERICH_ATTACK01,
 	SOUND_ELBELAND_CURSERICH_DEATH01,
	SOUND_ELBELAND_TOTEMGOLEM_MOVE01,
	SOUND_ELBELAND_TOTEMGOLEM_MOVE02,
	SOUND_ELBELAND_TOTEMGOLEM_ATTACK01,
	SOUND_ELBELAND_TOTEMGOLEM_ATTACK02,
	SOUND_ELBELAND_TOTEMGOLEM_DEATH01,
 	SOUND_ELBELAND_BEASTWOO_MOVE01,
	SOUND_ELBELAND_BEASTWOO_ATTACK01,
	SOUND_ELBELAND_BEASTWOO_DEATH01,
 	SOUND_ELBELAND_BEASTWOOLEADER_MOVE01,
	SOUND_ELBELAND_BEASTWOOLEADER_ATTACK01,
	SOUND_ELBELAND_VILLAGEPROTECTION01,
	SOUND_ELBELAND_WATERFALLSMALL01,
	SOUND_ELBELAND_WATERWAY01,
	SOUND_ELBELAND_ENTERDEVIAS01,
	SOUND_ELBELAND_WATERSMALL01,
	SOUND_ELBELAND_RAVINE01,
	SOUND_ELBELAND_ENTERATLANCE01,
	
	SOUND_SWAMPOFQUIET_SAPI_UNUS_ATTACK01,
	SOUND_SWAMPOFQUIET_SAPI_DEATH01,
	SOUND_SWAMPOFQUIET_SAPI_TRES_ATTACK01,
	SOUND_SWAMPOFQUIET_SHADOW_PAWN_ATTACK01,
	SOUND_SWAMPOFQUIET_SHADOW_KNIGHT_ATTACK01,
	SOUND_SWAMPOFQUIET_SHADOW_ROOK_ATTACK01,
	SOUND_SWAMPOFQUIET_SHADOW_DEATH01,
	SOUND_SWAMPOFQUIET_THUNDER_NAIPIN_BREATH01,
	SOUND_SWAMPOFQUIET_GHOST_NAIPIN_BREATH01,
	SOUND_SWAMPOFQUIET_BLAZE_NAIPIN_BREATH01,
	SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01,	// ������ ���� Ÿ����
	SOUND_SWAMPOFQUIET_NAIPIN_DEATH01,

	SOUND_SUMMON_CASTING,
	SOUND_SUMMON_SAHAMUTT,
	SOUND_SUMMON_EXPLOSION,
	SOUND_SUMMON_NEIL,
	SOUND_SUMMON_REQUIEM,
#ifdef ASG_ADD_SUMMON_RARGLE_SOUND
	SOUND_SUMMOM_RARGLE,
#endif	// ASG_ADD_SUMMON_RARGLE_SOUND
	SOUND_SUMMON_SKILL_LIGHTORB,
	SOUND_SUMMON_SKILL_SLEEP,
	SOUND_SUMMON_SKILL_BLIND,
	SOUND_SUMMON_SKILL_THORNS,
	SOUND_SKILL_CHAIN_LIGHTNING,
	SOUND_SKILL_DRAIN_LIFE,
	SOUND_SKILL_WEAKNESS,
	SOUND_SKILL_ENERVATION,
#ifdef ASG_ADD_SKILL_BERSERKER_SOUND
	SOUND_SKILL_BERSERKER,
#endif	// ASG_ADD_SKILL_BERSERKER_SOUND

#ifdef CSK_EVENT_CHERRYBLOSSOM
	SOUND_CHERRYBLOSSOM_EFFECT0, // �����
	SOUND_CHERRYBLOSSOM_EFFECT1, // ����
#endif //CSK_EVENT_CHERRYBLOSSOM

#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER	// ��Ŭ���� ���̽���Ŀ ����, ���� ����
	SOUND_RAKLION_ICEWALKER_ATTACK,
	SOUND_RAKLION_ICEWALKER_MOVE,
#endif //LDS_RAKLION_ADDMONSTER_ICEWALKER

#ifdef ADD_RAKLION_MOB_ICEGIANT
	SOUND_RAKLION_ICEGIANT_MOVE,
	SOUND_RAKLION_ICEGIANT_DEATH,
#endif	// ADD_RAKLION_MOB_ICEGIANT
	
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN // ��Ŭ���� ��ƾ ����, ���� ����
	SOUND_RAKLION_COOLERTIN_ATTACK,
	SOUND_RAKLION_COOLERTIN_MOVE,
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
	
#ifdef ADD_RAKLION_IRON_KNIGHT
	SOUND_RAKLION_IRON_KNIGHT_MOVE,
	SOUND_RAKLION_IRON_KNIGHT_ATTACK,
#endif	// ADD_RAKLION_IRON_KNIGHT

#ifdef PJH_GIANT_MAMUD
	SOUND_RAKLION_GIANT_MAMUD_MOVE,
	SOUND_RAKLION_GIANT_MAMUD_ATTACK,
	SOUND_RAKLION_GIANT_MAMUD_DEATH,
#endif //PJH_GIANT_MAMUD

#ifdef CSK_RAKLION_BOSS
	SOUND_RAKLION_SERUFAN_ATTACK1,		// ���� 1, 2
	SOUND_RAKLION_SERUFAN_ATTACK2,		// ���� 3
	SOUND_RAKLION_SERUFAN_CURE,			// ġ��
	SOUND_RAKLION_SERUFAN_RAGE,			// ����
	SOUND_RAKLION_SERUFAN_WORD1,		// ����
	SOUND_RAKLION_SERUFAN_WORD2,		// ���
	SOUND_RAKLION_SERUFAN_WORD3,		// �󸮱�
	SOUND_RAKLION_SERUFAN_WORD4,		// ��ȯ
#endif // CSK_RAKLION_BOSS

#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
	SOUND_SKILL_BLOWOFDESTRUCTION,		// �ı��� �ϰ� ����
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
#ifdef YDG_ADD_SKILL_FLAME_STRIKE_SOUND
	SOUND_SKILL_FLAME_STRIKE,			// �÷��� ��Ʈ����ũ ����
#endif	// YDG_ADD_SKILL_FLAME_STRIKE_SOUND
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
	SOUND_SKILL_GIGANTIC_STORM,			// �Ⱓƽ ���� ����
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND
	SOUND_SKILL_LIGHTNING_SHOCK,		// ����Ʈ�� ��ũ ����
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
	SOUND_SKILL_SWELL_OF_MAGICPOWER,	// ������ �������� ����
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	SOUND_SKILL_MULTI_SHOT,
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	SOUND_SKILL_RECOVER,
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	SOUND_SKILL_CAOTIC,
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC

#ifdef YDG_ADD_FIRECRACKER_ITEM
	SOUND_XMAS_FIRECRACKER,
#endif	// YDG_ADD_FIRECRACKER_ITEM
#ifdef YDG_ADD_SANTA_MONSTER
	SOUND_XMAS_SANTA_IDLE_1,
	SOUND_XMAS_SANTA_IDLE_2,
	SOUND_XMAS_SANTA_WALK_1,
	SOUND_XMAS_SANTA_WALK_2,
	SOUND_XMAS_SANTA_ATTACK_1,
	SOUND_XMAS_SANTA_DAMAGE_1,
	SOUND_XMAS_SANTA_DAMAGE_2,
	SOUND_XMAS_SANTA_DEATH_1,
#endif	// YDG_ADD_SANTA_MONSTER
	
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	SOUND_XMAS_SNOWMAN_WALK_1,
	SOUND_XMAS_SNOWMAN_ATTACK_1,
	SOUND_XMAS_SNOWMAN_ATTACK_2,
	SOUND_XMAS_SNOWMAN_DAMAGE_1,
	SOUND_XMAS_SNOWMAN_DEATH_1,
#endif //LDK_ADD_SNOWMAN_CHANGERING
	
#ifdef YDG_ADD_NEW_DUEL_NPC
	SOUND_DUEL_NPC_IDLE_1,
#endif	// YDG_ADD_NEW_DUEL_NPC
	
#ifdef PBG_ADD_PKFIELD
	SOUND_PKFIELD_ZOMBIEWARRIOR_ATTACK,		//��������
	SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE01,
	SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE02,
	SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE01,
	SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE02,
	SOUND_PKFIELD_ZOMBIEWARRIOR_DEATH,

	SOUND_PKFIELD_RAISEDGLADIATOR_ATTACK,	//�ǻ�Ƴ� ������
	SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE01,
	SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE02,
	SOUND_PKFIELD_RAISEDGLADIATOR_DEATH,
	SOUND_PKFIELD_RAISEDGLADIATOR_MOVE01,
	SOUND_PKFIELD_RAISEDGLADIATOR_MOVE02,

	SOUND_PKFIELD_ASHESBUTCHER_ATTACK,		//����� ������
	SOUND_PKFIELD_ASHESBUTCHER_DAMAGE01,
	SOUND_PKFIELD_ASHESBUTCHER_DAMAGE02,
	SOUND_PKFIELD_ASHESBUTCHER_DEATH,
	SOUND_PKFIELD_ASHESBUTCHER_MOVE01,
	SOUND_PKFIELD_ASHESBUTCHER_MOVE02,

	SOUND_PKFIELD_BLOODASSASSIN_ATTACK,		//���� �ϻ���
	SOUND_PKFIELD_BLOODASSASSIN_DAMAGE01,
	SOUND_PKFIELD_BLOODASSASSIN_DAMAGE02,
	SOUND_PKFIELD_BLOODASSASSIN_DEDTH,
	SOUND_PKFIELD_BLOODASSASSIN_MOVE01,
	SOUND_PKFIELD_BLOODASSASSIN_MOVE02,

	SOUND_PKFIELD_BURNINGLAVAGOLEM_ATTACK01,	//��Ÿ�� ��ϰ���
	SOUND_PKFIELD_BURNINGLAVAGOLEM_ATTACK02,
	SOUND_PKFIELD_BURNINGLAVAGOLEM_DAMAGE01,
	SOUND_PKFIELD_BURNINGLAVAGOLEM_DAMAGE02,
	SOUND_PKFIELD_BURNINGLAVAGOLEM_DEATH,
	SOUND_PKFIELD_BURNINGLAVAGOLEM_MOVE01,
	SOUND_PKFIELD_BURNINGLAVAGOLEM_MOVE02,
#endif //PBG_ADD_PKFIELD

#ifdef KJH_ADD_09SUMMER_EVENT
	SOUND_UMBRELLA_MONSTER_WALK1,
	SOUND_UMBRELLA_MONSTER_WALK2,
	SOUND_UMBRELLA_MONSTER_DAMAGE,
	SOUND_UMBRELLA_MONSTER_DEAD,
#endif // KJH_ADD_09SUMMER_EVENT
	
#ifdef YDG_ADD_DOPPELGANGER_SOUND
	SOUND_DOPPELGANGER_SLIME_ATTACK,
	SOUND_DOPPELGANGER_SLIME_DEATH,
	SOUND_DOPPELGANGER_BUGBEAR_ATTACK,
	SOUND_DOPPELGANGER_BUGBEAR_DEATH,
	SOUND_DOPPELGANGER_RED_BUGBEAR_ATTACK,
	SOUND_DOPPELGANGER_RED_BUGBEAR_DEATH,
	SOUND_DOPPELGANGER_LUGARD_BREATH,
	SOUND_DOPPELGANGER_JEWELBOX_OPEN,
#endif	// YDG_ADD_DOPPELGANGER_SOUND
	
#ifdef LDS_ADD_EMPIRE_GUARDIAN
	SOUND_EMPIREGUARDIAN_WEATHER_RAIN,					// ImperialGuardianFort_out1.wav
	SOUND_EMPIREGUARDIAN_WEATHER_FOG,					// ImperialGuardianFort_out2.wav
	SOUND_EMPIREGUARDIAN_WEATHER_STORM,					// ImperialGuardianFort_out3.wav

	SOUND_EMPIREGUARDIAN_INDOOR_SOUND,					// ImperialGuardianFort_in.wav

	// ���� ���̿� ī����		(504/164)
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_MOVE,		// GaionKalein_move.wav
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_RAGE,		// GaionKalein_rage.wav
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_DEATH,		// GrandWizard_death.wav
	
	// ���°� ����Ʈ			(505/165)
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK01,		// Jelint_attack1.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK03,		// Jelint_attack3.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE01,			// Jelint_move01.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE02,			// Jelint_move02.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_RAGE,			// Jelint_rage.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_DEATH,			// Jelint_death.wav

	// �λ�ɰ� ���̸��		(506/166)
	SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_ATTACK02,		// Raymond_attack2.wav
	SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_RAGE,			// Raymond_rage.wav

	// ���ְ� ����ĭ��			(507/167)
	SOUND_EMPIREGUARDIAN_ERCANNE_MONSTER_ATTACK03,		// Ercanne_attack3.wav

	// 1������ ������			(508/168)
	SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK02,// 1Deasuler_attack2.wav
	SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK03,// 1Deasuler_attack3.wav

	// 2������ ����Ʈ			(509/169)
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK01,// 2Vermont_attack1.wav
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK02,// 2Vermont_attack2.wav
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_DEATH,	// 2Vermont_death.wav

	// 3������ ī��				(510/170)
	SOUND_EMPIREGUARDIAN_3CORP_CATO_ATTACK02,			// 3Cato_attack2.wav
	SOUND_EMPIREGUARDIAN_3CORP_CATO_MOVE,				// 3Cato_move.wav

	// 4������ ������			(511/171)
	SOUND_EMPIREGUARDIAN_4CORP_GALLIA_ATTACK02,			// 4Gallia_attack2.wav
	
	// �����屳					(512/172)
	SOUND_EMPIREGUARDIAN_QUATERMASTER_ATTACK02,			// QuaterMaster_attack2.wav

	// ��������					(513/173)
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK01,			// CombatMaster_attack1.wav
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK02,			// CombatMaster_attack2.wav
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK03,			// CombatMaster_attack3.wav

	// �븶����					(515/175)
	SOUND_EMPIREGUARDIAN_GRANDWIZARD_DEATH,				// GrandWizard_death.wav

	// �ϻ����					(516/176)
	SOUND_EMPIREGUARDIAN_ASSASSINMASTER_DEATH,			// AssassinMaster_Death.wav

	// �⸶����					(517/177)
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK01,		// CavalryLeader_attack1.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK02,		// CavalryLeader_attack2.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE01,			// CavalryLeader_move01.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE02,			// CavalryLeader_move02.wav
	
	// ���к�					(519/178)
	SOUND_EMPIREGUARDIAN_DEFENDER_ATTACK02,				// Defender_attack2.wav
	
	// ġ����					(519/179)
	SOUND_EMPIREGUARDIAN_PRIEST_STOP,					// Priest_stay.wav
#endif // LDS_ADD_EMPIRE_GUARDIAN

#ifdef PBG_ADD_NEWCHAR_MONK
	SOUND_RAGESKILL_THRUST,								// ������ �����ͽ�ų ����
	SOUND_RAGESKILL_THRUST_ATTACK,
	SOUND_RAGESKILL_STAMP,
	SOUND_RAGESKILL_STAMP_ATTACK,
	SOUND_RAGESKILL_GIANTSWING,
	SOUND_RAGESKILL_GIANTSWING_ATTACK,
	SOUND_RAGESKILL_DARKSIDE,
	SOUND_RAGESKILL_DARKSIDE_ATTACK,
	SOUND_RAGESKILL_DRAGONLOWER,
	SOUND_RAGESKILL_DRAGONLOWER_ATTACK,
	SOUND_RAGESKILL_DRAGONKICK,
	SOUND_RAGESKILL_DRAGONKICK_ATTACK,
	SOUND_RAGESKILL_BUFF_1,
	SOUND_RAGESKILL_BUFF_2,
#endif //PBG_ADD_NEWCHAR_MONK

#ifdef ASG_ADD_KARUTAN_MONSTERS
	// �͵�������
	SOUND_KARUTAN_TCSCORPION_ATTACK,					// ToxyChainScorpion_attack.wav
	SOUND_KARUTAN_TCSCORPION_DEATH,						// ToxyChainScorpion_death.wav
	SOUND_KARUTAN_TCSCORPION_HIT,						// ToxyChainScorpion_hit.wav

	// �������ǿ�
	SOUND_KARUTAN_BONESCORPION_ATTACK,					// BoneScorpion_attack.wav
	SOUND_KARUTAN_BONESCORPION_DEATH,					// BoneScorpion_death.wav
	SOUND_KARUTAN_BONESCORPION_HIT,						// BoneScorpion_hit.wav

	// ����Ŀ��
	SOUND_KARUTAN_ORCUS_MOVE1,							// Orcus_move1.wav
	SOUND_KARUTAN_ORCUS_MOVE2,							// Orcus_move2.wav
	SOUND_KARUTAN_ORCUS_ATTACK1,						// Orcus_attack_1.wav
	SOUND_KARUTAN_ORCUS_ATTACK2,						// Orcus_attack_2.wav
	SOUND_KARUTAN_ORCUS_DEATH,							// Orcus_death.wav

	// ���
	SOUND_KARUTAN_GOLOCH_MOVE1,							// Goloch_move1.wav
	SOUND_KARUTAN_GOLOCH_MOVE2,							// Goloch_move2.wav
	SOUND_KARUTAN_GOLOCH_ATTACK,						// Goloch_attack.wav
	SOUND_KARUTAN_GOLOCH_DEATH,							// Goloch_death.wav

	// ũ��Ÿ
	SOUND_KARUTAN_CRYPTA_MOVE1,							// Crypta_move1.wav
	SOUND_KARUTAN_CRYPTA_MOVE2,							// Crypta_move2.wav
	SOUND_KARUTAN_CRYPTA_ATTACK,						// Crypta_attack.wav
	SOUND_KARUTAN_CRYPTA_DEATH,							// Crypta_death.wav

	// ũ������
	SOUND_KARUTAN_CRYPOS_MOVE1,							// Crypos_move1.wav
	SOUND_KARUTAN_CRYPOS_MOVE2,							// Crypos_move2.wav
	SOUND_KARUTAN_CRYPOS_ATTACK1,						// Crypos_attack_1.wav
	SOUND_KARUTAN_CRYPOS_ATTACK2,						// Crypos_attack_2.wav

	// �ܵ��
	SOUND_KARUTAN_CONDRA_MOVE1,							// Condra_move1.wav
	SOUND_KARUTAN_CONDRA_MOVE2,							// Condra_move2.wav
	SOUND_KARUTAN_CONDRA_ATTACK,						// Condra_attack.wav
	SOUND_KARUTAN_CONDRA_DEATH,							// Condra_death.wav

	// �����ܵ��
	SOUND_KARUTAN_NARCONDRA_ATTACK,						// NarCondra_attack.wav
#endif	// ASG_ADD_KARUTAN_MONSTERS

#ifdef ASG_ADD_MAP_KARUTAN
	//  Į��ź ȯ����
	SOUND_KARUTAN_DESERT_ENV,							// Karutan_desert_env.wav
	SOUND_KARUTAN_INSECT_ENV,							// Karutan_insect_env.wav
	SOUND_KARUTAN_KARDAMAHAL_ENV,						// Kardamahal_entrance_env.wav
#endif	// ASG_ADD_MAP_KARUTAN

    MAX_BUFFER
};

HRESULT InitDirectSound( HWND hDlg );
void    SetEnableSound ( bool b );
void    FreeDirectSound();

void    LoadWaveFile(int Buffer,TCHAR* strFileName,int BufferChannel=MAX_CHANNEL, bool Enable3DSound=false);
HRESULT PlayBuffer(int Buffer,OBJECT *Object=NULL,BOOL bLooped=false);
void    StopBuffer(int Buffer,BOOL bResetPosition);
void    AllStopSound(void);
void    Set3DSoundPosition();
HRESULT ReleaseBuffer(int Buffer);
HRESULT RestoreBuffers(int Buffer,int Channel);
void	SetVolume(int Buffer, long vol);
void	SetMasterVolume(long vol);

#endif //__DSPLAYSOUND_H__