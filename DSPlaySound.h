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
#define SOUND_TAMAJJANG1           101   //  타마짱1.
#define SOUND_TAMAJJANG2           102   //  타마짱2.
#endif

#define SOUND_CHANGE_UP            102   //  전직.

#define SOUND_PHOENIXEXP			103	// 불사조 폭파공격

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
    SOUND_EXPAND_START          = SOUND_MONSTER_END,    //  확장된 사운드 시작.
    SOUND_RUN_DARK_HORSE_1      ,                       //  말달리기 1
    SOUND_RUN_DARK_HORSE_2      ,                       //  말달리기 2
    SOUND_RUN_DARK_HORSE_3      ,                       //  말달리기 3
    SOUND_DARKLORD_PAIN         ,                       //  다크로드 아플때.
    SOUND_DARKLORD_DEAD         ,                       //  다크로드 죽을때.
    SOUND_ATTACK_SPEAR          ,                       //  스트롱 피어 공격.
    SOUND_ATTACK_FIRE_BUST      ,                       //  파이어버스트 공격.
    SOUND_ATTACK_FIRE_BUST_EXP  ,                       //  파이어버스트 터질때.
    SOUND_PART_TELEPORT         ,                       //  파티원 소환.
    SOUND_ELEC_STRIKE_READY     ,                       //  일렉 스트라이크 기모을때.
    SOUND_ELEC_STRIKE           ,                       //  일렉 스트라이크.
    SOUND_EARTH_QUAKE           ,                       //  어스퀘이크.
    SOUND_CRITICAL              ,                       //  크리티컬 데미지 확률증가.
    SOUND_DSPIRIT_MISSILE       ,                       //  다크스피릿 원거리 공격.
    SOUND_DSPIRIT_SHOUT         ,                       //  다크스피릿 외침.
    SOUND_DSPIRIT_RUSH          ,                       //  다크스피릿 돌진.

    SOUND_KALIMA_AMBIENT        ,                       //  칼리마 배경 효과음 1.
    SOUND_KALIMA_AMBIENT2       ,                       //  칼리마 배경 효과음 2 ( 랜덤 ).
    SOUND_KALIMA_AMBIENT3       ,                       //  칼리마 배경 효과음 3 ( 랜덤 ).
    SOUND_KALIMA_WATER_FALL     ,                       //  폭포.
    SOUND_KALIMA_FALLING_STONE  ,                       //  떨어지는 돌.
    SOUND_DEATH_BUBBLE          ,                       //  죽은뒤에 올라오는 거품.

    SOUND_KUNDUN_AMBIENT1       ,                       //  쿤둔 뷰포트 밖에 있을때1.
    SOUND_KUNDUN_AMBIENT2       ,                       //  쿤둔 뷰포트 밖에 있을때2.
    SOUND_KUNDUN_ROAR           ,                       //  쿤둔의 포효.
    SOUND_KUNDUN_SIGHT          ,                       //  쿤둔을 처음 보았을때.
    SOUND_KUNDUN_SHUDDER        ,                       //  쿤둔의 죽기전 움츠림.
    SOUND_KUNDUN_DESTROY        ,                       //  쿤둔의 폭발.
	
    SOUND_SKILL_SKULL           ,                       //  몬스터의 방어력 감소 스킬 효과음.
    SOUND_GREAT_POISON          ,                       //  연발 데스 포이즌.
    SOUND_GREAT_SHIELD          ,                       //  몬스터 방어막.
	
	SOUND_BC_AMBIENT            ,                       //  배경 효과음 ( 비공성 ).
	SOUND_BC_AMBIENT_BATTLE1    ,                       //  배경 효과음 ( 공성 ).
	SOUND_BC_AMBIENT_BATTLE2    ,                       //  배경 효과음 ( 공성 ).
	SOUND_BC_AMBIENT_BATTLE3    ,                       //  배경 효과음 ( 공성 ).
	SOUND_BC_AMBIENT_BATTLE4    ,                       //  배경 효과음 ( 공성 ).
	SOUND_BC_AMBIENT_BATTLE5    ,                       //  배경 효과음 ( 공성 ).
	SOUND_BC_GUARD_STONE_DIS    ,                       //  수호석상 파괴.
	SOUND_BC_SHIELD_SPACE_DIS   ,                       //  방어막 파괴.
	SOUND_BC_CATAPULT_ATTACK    ,                       //  공성무기 발사.
	SOUND_BC_CATAPULT_HIT       ,                       //  공성무기 폭발 소리.
	SOUND_BC_WALL_HIT           ,                       //  성벽 부서질때.
	SOUND_BC_GATE_OPEN          ,                       //  성문 열림/닫기.
	SOUND_BC_GUARDIAN_ATTACK    ,                       //  가디언 공격.
	
	SOUND_BC_HUNTINGGROUND_AMBIENT,						// 공성사냥터 배경음악
	SOUND_BC_AXEWARRIOR_MOVE1	,						// 액스 워리어 이동1
	SOUND_BC_AXEWARRIOR_MOVE2	,						// 액스 워리어 이동2
	SOUND_BC_AXEWARRIOR_ATTACK1	,						// 액스 워리어 공격1
	SOUND_BC_AXEWARRIOR_ATTACK2	,						// 액스 워리어 공격2
	SOUND_BC_AXEWARRIOR_DIE		,						// 액스 워리어 죽기
	SOUND_BC_LIZARDWARRIOR_MOVE1	,					// 리자드 워리어 이동1
	SOUND_BC_LIZARDWARRIOR_MOVE2	,					// 리자드 워리어 이동2
	SOUND_BC_LIZARDWARRIOR_ATTACK1	,					// 리자드 워리어 공격1
	SOUND_BC_LIZARDWARRIOR_ATTACK2	,					// 리자드 워리어 공격2
	SOUND_BC_LIZARDWARRIOR_DIE		,					// 리자드 워리어 죽기
	SOUND_BC_POISONGOLEM_MOVE1		,					// 독골렘 이동1
	SOUND_BC_POISONGOLEM_MOVE2		,					// 독골렘 이동2
	SOUND_BC_POISONGOLEM_ATTACK1	,					// 독골렘 공격1
	SOUND_BC_POISONGOLEM_ATTACK2	,					// 독골렘 공격2
	SOUND_BC_POISONGOLEM_ATTACK3	,					// 독골렘 공격3
	SOUND_BC_POISONGOLEM_DIE		,					// 독골렘 죽기
	SOUND_BC_QUEENBEE_MOVE1		,						// 퀸비 이동1
	SOUND_BC_QUEENBEE_MOVE2		,						// 퀸비 이동2
	SOUND_BC_QUEENBEE_ATTACK1	,						// 퀸비 공격1
	SOUND_BC_QUEENBEE_ATTACK2	,						// 퀸비 공격2
	SOUND_BC_QUEENBEE_DIE		,						// 퀸비 죽기
	SOUND_BC_FIREGOLEM_MOVE1	,						// 불골렘 이동1
	SOUND_BC_FIREGOLEM_MOVE2	,						// 불골렘 이동2
	SOUND_BC_FIREGOLEM_ATTACK1	,						// 불골렘 공격1
	SOUND_BC_FIREGOLEM_ATTACK2	,						// 불골렘 공격2
	SOUND_BC_FIREGOLEM_DIE		,						// 불골렘 죽기
	SOUND_BC_EROHIM_ENTER		,						// 에로힘 입장
	SOUND_BC_EROHIM_ATTACK1		,						// 에로힘 공격1
	SOUND_BC_EROHIM_ATTACK2		,						// 에로힘 공격2
	SOUND_BC_EROHIM_ATTACK3		,						// 에로힘 공격3
	SOUND_BC_EROHIM_DIE			,						// 에로힘 죽기
	SOUND_CRY1ST_AMBIENT		,
	SOUND_CRY1ST_WWOLF_MOVE1    ,						// 웨어울프 이동1
	SOUND_CRY1ST_WWOLF_MOVE2    ,						// 웨어울프 이동2
	SOUND_CRY1ST_WWOLF_ATTACK1  ,						// 웨어울프 공격1
	SOUND_CRY1ST_WWOLF_ATTACK2  ,						// 웨어울프 공격2
	SOUND_CRY1ST_WWOLF_DIE      ,						// 웨어울프 죽기
	
	SOUND_CRY1ST_SCOUT1_MOVE1    ,						// 스카우트근거리 이동1
	SOUND_CRY1ST_SCOUT1_MOVE2    ,						// 스카우트근거리 이동2
	SOUND_CRY1ST_SCOUT1_ATTACK1  ,						// 스카우트근거리 공격1
	SOUND_CRY1ST_SCOUT1_ATTACK2  ,						// 스카우트근거리 공격2
	SOUND_CRY1ST_SCOUT1_DIE      ,						// 스카우트근거리 죽기
	
	SOUND_CRY1ST_SCOUT2_MOVE1    ,						// 스카우트중거리 이동1
	SOUND_CRY1ST_SCOUT2_MOVE2    ,						// 스카우트중거리 이동2
	SOUND_CRY1ST_SCOUT2_ATTACK1  ,						// 스카우트중거리 공격1
	SOUND_CRY1ST_SCOUT2_ATTACK2  ,						// 스카우트중거리 공격2
	SOUND_CRY1ST_SCOUT2_DIE      ,						// 스카우트중거리 죽기
	
	SOUND_CRY1ST_SCOUT3_MOVE1    ,						// 스카우트장거리 이동1
	SOUND_CRY1ST_SCOUT3_MOVE2    ,						// 스카우트장거리 이동2
	SOUND_CRY1ST_SCOUT3_ATTACK1  ,						// 스카우트장거리 공격1
	SOUND_CRY1ST_SCOUT3_ATTACK2  ,						// 스카우트장거리 공격2
	SOUND_CRY1ST_SCOUT3_DIE      ,						// 스카우트장거리 죽기
	
	SOUND_CRY1ST_SORAM_MOVE1    ,						// 스카우트장거리 이동1
	SOUND_CRY1ST_SORAM_MOVE2    ,						// 스카우트장거리 이동2
	SOUND_CRY1ST_SORAM_ATTACK1  ,						// 스카우트장거리 공격1
	SOUND_CRY1ST_SORAM_ATTACK2  ,						// 스카우트장거리 공격2
	SOUND_CRY1ST_SORAM_DIE      ,						// 스카우트장거리 죽기
	
	SOUND_CRY1ST_BALRAM_MOVE1    ,						// 스카우트장거리 이동1
	SOUND_CRY1ST_BALRAM_MOVE2    ,						// 스카우트장거리 이동2
	SOUND_CRY1ST_BALRAM_ATTACK1  ,						// 스카우트장거리 공격1
	SOUND_CRY1ST_BALRAM_ATTACK2  ,						// 스카우트장거리 공격2
	SOUND_CRY1ST_BALRAM_DIE      ,						// 스카우트장거리 죽기
	
	SOUND_CRY1ST_BALGAS_MOVE1	,						// 발가스 이동1
	SOUND_CRY1ST_BALGAS_MOVE2	,						// 발가스 이동2
	SOUND_CRY1ST_BALGAS_ATTACK1	,						// 발가스 공격1
	SOUND_CRY1ST_BALGAS_ATTACK2	,						// 발가스 공격1
	SOUND_CRY1ST_BALGAS_DIE		,						// 발가스 죽기
	SOUND_CRY1ST_BALGAS_SKILL1	,						// 발가스 스킬1
	SOUND_CRY1ST_BALGAS_SKILL2	,						// 발가스 스킬1
	
	SOUND_CRY1ST_DARKELF_MOVE1	,						// 다크엘프 이동1
	SOUND_CRY1ST_DARKELF_MOVE2	,						// 다크엘프 이동2
	SOUND_CRY1ST_DARKELF_ATTACK1,						// 다크엘프 공격1
	SOUND_CRY1ST_DARKELF_ATTACK2,						// 다크엘프 공격2
	SOUND_CRY1ST_DARKELF_DIE	,						// 다크엘프 죽기
	SOUND_CRY1ST_DARKELF_SKILL1	,						// 다크엘프 스킬1
	SOUND_CRY1ST_DARKELF_SKILL2	,						// 다크엘프 스킬1
	
	SOUND_CRY1ST_DEATHSPIRIT_MOVE1	,					// 데스스피릿 이동1
	SOUND_CRY1ST_DEATHSPIRIT_MOVE2	,					// 데스스피릿 이동2
	SOUND_CRY1ST_DEATHSPIRIT_ATTACK1,					// 데스스피릿 공격1
	SOUND_CRY1ST_DEATHSPIRIT_ATTACK2,					// 데스스피릿 공격2
	SOUND_CRY1ST_DEATHSPIRIT_DIE	,					// 데스스피릿 죽기
	
	SOUND_CRY1ST_TANKER_ATTACK1		,					// 탱커 공격1
	SOUND_CRY1ST_TANKER_DIE			,					// 탱커 죽기
	SOUND_CRY1ST_SUMMON				,					// 소환 효과 음악
	SOUND_CRY1ST_SUCCESS			,					// MVP 성공
	SOUND_CRY1ST_FAILED				,					// MVP 실패
	SOUND_AIDA_AMBIENT			  ,						// 아이다 배경음악
	SOUND_AIDA_BLUEGOLEM_MOVE1    ,						// 블루골렘 이동1
	SOUND_AIDA_BLUEGOLEM_MOVE2    ,						// 블루골렘 이동2
	SOUND_AIDA_BLUEGOLEM_ATTACK1  ,						// 블루골렘 공격1
	SOUND_AIDA_BLUEGOLEM_ATTACK2  ,						// 블루골렘 공격2
	SOUND_AIDA_BLUEGOLEM_DIE      ,						// 블루골렘 죽기
	SOUND_AIDA_DEATHRAIDER_MOVE1  ,						// 데쓰라이더 이동1
	SOUND_AIDA_DEATHRAIDER_MOVE2  ,						// 데쓰라이더 이동2
	SOUND_AIDA_DEATHRAIDER_ATTACK1,						// 데쓰라이더 공격1
	SOUND_AIDA_DEATHRAIDER_ATTACK2,						// 데쓰라이더 공격2
	SOUND_AIDA_DEATHRAIDER_DIE    ,						// 데쓰라이더 죽기
	SOUND_AIDA_DEATHTREE_MOVE1    ,						// 데쓰트리 이동1
	SOUND_AIDA_DEATHTREE_MOVE2    ,						// 데쓰트리 이동2
	SOUND_AIDA_DEATHTREE_ATTACK1  ,						// 데쓰트리 공격1
	SOUND_AIDA_DEATHTREE_ATTACK2  ,						// 데쓰트리 공격2
	SOUND_AIDA_DEATHTREE_DIE      ,						// 데쓰트리 죽기
	SOUND_AIDA_FORESTORC_MOVE1    ,						// 포레스트오크 이동1
	SOUND_AIDA_FORESTORC_MOVE2    ,						// 포레스트오크 이동2
	SOUND_AIDA_FORESTORC_ATTACK1  ,						// 포레스트오크 공격1
	SOUND_AIDA_FORESTORC_ATTACK2  ,						// 포레스트오크 공격2
	SOUND_AIDA_FORESTORC_DIE	  ,						// 포레스트오크 죽기
	SOUND_AIDA_HELL_MOVE1		  ,						// 헬마이네 이동1
	SOUND_AIDA_HELL_MOVE2		  ,						// 헬마이네 이동2
	SOUND_AIDA_HELL_ATTACK1		  ,						// 헬마이네 공격1
	SOUND_AIDA_HELL_ATTACK2		  ,						// 헬마이네 공격2
	SOUND_AIDA_HELL_ATTACK3		  ,						// 헬마이네 공격3
	SOUND_AIDA_HELL_DIE			  ,						// 헬마이네 죽기
	SOUND_AIDA_WITCHQUEEN_MOVE1   ,						// 위치퀸 이동1
	SOUND_AIDA_WITCHQUEEN_MOVE2   ,						// 위치퀸 이동2
	SOUND_AIDA_WITCHQUEEN_ATTACK1 ,						// 위치퀸 공격1
	SOUND_AIDA_WITCHQUEEN_ATTACK2 ,						// 위치퀸 공격2
	SOUND_AIDA_WITCHQUEEN_DIE     ,						// 위치퀸 죽기
	// 배경(BG) 효과음.
	SOUND_KANTURU_1ST_BG_WATERFALL	,					// 폭포.
	SOUND_KANTURU_1ST_BG_ELEC		,					// 전기 스파크.
	SOUND_KANTURU_1ST_BG_WHEEL		,					// 톱니바퀴.
	SOUND_KANTURU_1ST_BG_PLANT		,					// 식충 식물.
	SOUND_KANTURU_1ST_BG_GLOBAL		,					// 맵 전체.

	// 몬스터 효과음.
	SOUND_KANTURU_1ST_BER_MOVE1		,					// 버서커
	SOUND_KANTURU_1ST_BER_MOVE2		,
	SOUND_KANTURU_1ST_BER_ATTACK1	,
	SOUND_KANTURU_1ST_BER_ATTACK2	,
	SOUND_KANTURU_1ST_BER_DIE		,
	SOUND_KANTURU_1ST_GIGAN_MOVE1	,					// 기간티스.
	SOUND_KANTURU_1ST_GIGAN_ATTACK1	,
	SOUND_KANTURU_1ST_GIGAN_ATTACK2	,
	SOUND_KANTURU_1ST_GIGAN_DIE		,
	SOUND_KANTURU_1ST_GENO_MOVE1	,					// 제노사이더.
	SOUND_KANTURU_1ST_GENO_MOVE2	,
	SOUND_KANTURU_1ST_GENO_ATTACK1	,
	SOUND_KANTURU_1ST_GENO_ATTACK2	,
	SOUND_KANTURU_1ST_GENO_DIE		,
	
	SOUND_KANTURU_1ST_KENTA_MOVE1	,					// 켄타우로스
	SOUND_KANTURU_1ST_KENTA_MOVE2	,
	SOUND_KANTURU_1ST_KENTA_ATTACK1	,
	SOUND_KANTURU_1ST_KENTA_ATTACK2	,
	SOUND_KANTURU_1ST_KENTA_DIE		,
	SOUND_KANTURU_1ST_BLADE_MOVE1	,					// 블레이드헌터
	SOUND_KANTURU_1ST_BLADE_MOVE2	,					// 블레이드헌터
	SOUND_KANTURU_1ST_BLADE_ATTACK1	,
	SOUND_KANTURU_1ST_BLADE_ATTACK2	,
	SOUND_KANTURU_1ST_BLADE_DIE		,
	SOUND_KANTURU_1ST_SATI_MOVE1	,					// 사티로스
	SOUND_KANTURU_1ST_SATI_MOVE2	,
	SOUND_KANTURU_1ST_SATI_ATTACK1	,
	SOUND_KANTURU_1ST_SATI_ATTACK2	,
	SOUND_KANTURU_1ST_SATI_DIE		,
	
	SOUND_KANTURU_1ST_SWOLF_MOVE1	,					// 스플린터 울프
	SOUND_KANTURU_1ST_SWOLF_MOVE2	,
	SOUND_KANTURU_1ST_SWOLF_ATTACK1	,
	SOUND_KANTURU_1ST_SWOLF_ATTACK2	,
	SOUND_KANTURU_1ST_SWOLF_DIE		,
	
	SOUND_KANTURU_1ST_IR_MOVE1		,					// 아이언 라이더
	SOUND_KANTURU_1ST_IR_MOVE2		,
	SOUND_KANTURU_1ST_IR_ATTACK1	,
	SOUND_KANTURU_1ST_IR_ATTACK2	,
	SOUND_KANTURU_1ST_IR_DIE		,
	
	// 2차맵 환경 사운드
	SOUND_KANTURU_2ND_MAPSOUND_GEAR	,	// 기어 소리
	SOUND_KANTURU_2ND_MAPSOUND_INCUBATOR,	// 기포 소리
	SOUND_KANTURU_2ND_MAPSOUND_HOLE,	// NPC장치 소리
	SOUND_KANTURU_2ND_MAPSOUND_GLOBAL,	// 전체적인 소리
	SOUND_KANTURU_2ND_PERSO_MOVE1	,	// 페르소나
	SOUND_KANTURU_2ND_PERSO_MOVE2	,
	SOUND_KANTURU_2ND_PERSO_ATTACK1	,
	SOUND_KANTURU_2ND_PERSO_ATTACK2	,
	SOUND_KANTURU_2ND_PERSO_DIE		,
	SOUND_KANTURU_2ND_TWIN_MOVE1	,	// 트윈테일
	SOUND_KANTURU_2ND_TWIN_MOVE2	,
	SOUND_KANTURU_2ND_TWIN_ATTACK1	,
	SOUND_KANTURU_2ND_TWIN_ATTACK2	,
	SOUND_KANTURU_2ND_TWIN_DIE		,
	SOUND_KANTURU_2ND_DRED_MOVE1	,	//	드레드피어
	SOUND_KANTURU_2ND_DRED_MOVE2	,
	SOUND_KANTURU_2ND_DRED_ATTACK1	,
	SOUND_KANTURU_2ND_DRED_ATTACK2	,
	SOUND_KANTURU_2ND_DRED_DIE		,
	SOUND_BMS_STUN              ,                       //  스턴 발동.
	SOUND_BMS_STUN_REMOVAL      ,                       //  스턴 해제 발동.
	SOUND_BMS_MANA              ,                       //  마나 증가 발동.
	SOUND_BMS_INVISIBLE         ,                       //  투명 발동.
	SOUND_BMS_VISIBLE           ,                       //  투명 해제.
	SOUND_BMS_MAGIC_REMOVAL     ,                       //  마법 해제.
	SOUND_BCS_RUSH              ,                       //  기사 돌격 스킬.
	SOUND_BCS_JAVELIN           ,                       //  법사 표창 스킬.
	SOUND_BCS_DEEP_IMPACT       ,                       //  요정 입펙트 샷.
	SOUND_BCS_DEATH_CANON       ,                       //  마검사 마살포.
	SOUND_BCS_ONE_FLASH         ,                       //  마검사 일섬.
	SOUND_BCS_SPACE_SPLIT       ,                       //  다크로드 공간 가르기.
	SOUND_BCS_BRAND_OF_SKILL    ,                       //  다크로드 보조 스킬.
	
	//^ 펜릴 사운드 관련
	SOUND_FENRIR_RUN_1			,						//	펜릴 달리기 1
	SOUND_FENRIR_RUN_2			,						//	펜릴 달리기 2
	SOUND_FENRIR_RUN_3			,						//	펜릴 달리기 3
	SOUND_FENRIR_WALK_1			,						//	펜릴 걷기 1
	SOUND_FENRIR_WALK_2			,						//	펜릴 걷기 2
	SOUND_FENRIR_DEATH			,						//	펜릴 죽음
	SOUND_FENRIR_IDLE_1			,						//	펜릴 평상시 1
	SOUND_FENRIR_IDLE_2			,						//	펜릴 평상시 2
	SOUND_FENRIR_DAMAGE_1		,						//	펜릴 데미지 1
	SOUND_FENRIR_DAMAGE_2		,						//	펜릴 데미지 2
	SOUND_FENRIR_SKILL			,						//	펜릴 스킬
	
	SOUND_KANTURU_3RD_MAYA_INTRO		,				//  마야 등장시
	SOUND_KANTURU_3RD_MAYA_END			,				//  마야 죽을시
	SOUND_KANTURU_3RD_MAYA_STORM		,				//  마야 죽을시
	SOUND_KANTURU_3RD_NIGHTMARE_INTRO	,				//  나이트메어 등장시
	SOUND_KANTURU_3RD_MAYAHAND_ATTACK1	,				//  마야손 공격 1 (바닦 치기)
	SOUND_KANTURU_3RD_MAYAHAND_ATTACK2	,				//  마야손 공격 2 (손날 공격)
	SOUND_KANTURU_3RD_MAP_SOUND01		,				//  칸투르3차 오브젝트 효과음
	SOUND_KANTURU_3RD_MAP_SOUND02		,				//  칸투르3차 오브젝트 효과음
	SOUND_KANTURU_3RD_MAP_SOUND03		,				//  칸투르3차 오브젝트 효과음
	SOUND_KANTURU_3RD_MAP_SOUND04		,				//  칸투르3차 오브젝트 효과음
	SOUND_KANTURU_3RD_MAP_SOUND05		,				//  칸투르3차 오브젝트 효과음
	SOUND_KANTURU_3RD_AMBIENT			,				//  칸투르3차 맵 효과음
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
	SOUND_XMAS_JUMP_SANTA,		// 크리스마스 점프 사운드(눈사람)
	SOUND_XMAS_JUMP_DEER,		// 크리스마스 점프 사운드(사슴)
	SOUND_XMAS_JUMP_SNOWMAN,	// 크리스마스 점프 사운드(산타)
	SOUND_XMAS_TURN,			// 크리스마스 턴 사운트
	// 설이벤트 사운드 효과음
	SOUND_NEWYEARSDAY_DIE,		// 복주머니 죽을때 나는 사운드
	SOUND_KUNDUN_ITEM_SOUND,	// 쿤둔의표식 아이템 5개 쌓일때 나는 사운드
	SOUND_SHIELDCLASH		,
	SOUND_INFINITYARROW	,
	SOUND_FIRE_SCREAM		,	//다크로드 파이어스크림마법 효과음.
	// 3차 체인지업 퀘스트 맵 배경 효과음.
	SOUND_3RD_CHANGE_UP_BG_CAGE1,		// 새장1
	SOUND_3RD_CHANGE_UP_BG_CAGE2,		// 새장2
	SOUND_3RD_CHANGE_UP_BG_VOLCANO,		// 용암
	SOUND_3RD_CHANGE_UP_BG_FIREPILLAR,	// 불기둥

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
	SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01,	// 네이핀 공통 타격음
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
	SOUND_CHERRYBLOSSOM_EFFECT0, // 샤라라
	SOUND_CHERRYBLOSSOM_EFFECT1, // 폭음
#endif //CSK_EVENT_CHERRYBLOSSOM

#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER	// 라클리온 아이스워커 공격, 무브 사운드
	SOUND_RAKLION_ICEWALKER_ATTACK,
	SOUND_RAKLION_ICEWALKER_MOVE,
#endif //LDS_RAKLION_ADDMONSTER_ICEWALKER

#ifdef ADD_RAKLION_MOB_ICEGIANT
	SOUND_RAKLION_ICEGIANT_MOVE,
	SOUND_RAKLION_ICEGIANT_DEATH,
#endif	// ADD_RAKLION_MOB_ICEGIANT
	
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN // 라클리온 쿨러틴 공격, 무브 사운드
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
	SOUND_RAKLION_SERUFAN_ATTACK1,		// 공격 1, 2
	SOUND_RAKLION_SERUFAN_ATTACK2,		// 공격 3
	SOUND_RAKLION_SERUFAN_CURE,			// 치료
	SOUND_RAKLION_SERUFAN_RAGE,			// 광폭
	SOUND_RAKLION_SERUFAN_WORD1,		// 출현
	SOUND_RAKLION_SERUFAN_WORD2,		// 사망
	SOUND_RAKLION_SERUFAN_WORD3,		// 얼리기
	SOUND_RAKLION_SERUFAN_WORD4,		// 소환
#endif // CSK_RAKLION_BOSS

#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
	SOUND_SKILL_BLOWOFDESTRUCTION,		// 파괴의 일격 사운드
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
#ifdef YDG_ADD_SKILL_FLAME_STRIKE_SOUND
	SOUND_SKILL_FLAME_STRIKE,			// 플레임 스트라이크 사운드
#endif	// YDG_ADD_SKILL_FLAME_STRIKE_SOUND
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
	SOUND_SKILL_GIGANTIC_STORM,			// 기간틱 스톰 사운드
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND
	SOUND_SKILL_LIGHTNING_SHOCK,		// 라이트닝 쇼크 사운드
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
	SOUND_SKILL_SWELL_OF_MAGICPOWER,	// 마법사 마력증대 사운드
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
	SOUND_PKFIELD_ZOMBIEWARRIOR_ATTACK,		//좀비투사
	SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE01,
	SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE02,
	SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE01,
	SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE02,
	SOUND_PKFIELD_ZOMBIEWARRIOR_DEATH,

	SOUND_PKFIELD_RAISEDGLADIATOR_ATTACK,	//되살아난 검투사
	SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE01,
	SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE02,
	SOUND_PKFIELD_RAISEDGLADIATOR_DEATH,
	SOUND_PKFIELD_RAISEDGLADIATOR_MOVE01,
	SOUND_PKFIELD_RAISEDGLADIATOR_MOVE02,

	SOUND_PKFIELD_ASHESBUTCHER_ATTACK,		//잿더미 도살자
	SOUND_PKFIELD_ASHESBUTCHER_DAMAGE01,
	SOUND_PKFIELD_ASHESBUTCHER_DAMAGE02,
	SOUND_PKFIELD_ASHESBUTCHER_DEATH,
	SOUND_PKFIELD_ASHESBUTCHER_MOVE01,
	SOUND_PKFIELD_ASHESBUTCHER_MOVE02,

	SOUND_PKFIELD_BLOODASSASSIN_ATTACK,		//피의 암살자
	SOUND_PKFIELD_BLOODASSASSIN_DAMAGE01,
	SOUND_PKFIELD_BLOODASSASSIN_DAMAGE02,
	SOUND_PKFIELD_BLOODASSASSIN_DEDTH,
	SOUND_PKFIELD_BLOODASSASSIN_MOVE01,
	SOUND_PKFIELD_BLOODASSASSIN_MOVE02,

	SOUND_PKFIELD_BURNINGLAVAGOLEM_ATTACK01,	//불타는 용암거인
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

	// 보스 가이온 카레인		(504/164)
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_MOVE,		// GaionKalein_move.wav
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_RAGE,		// GaionKalein_rage.wav
	SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_DEATH,		// GrandWizard_death.wav
	
	// 보좌관 제린트			(505/165)
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK01,		// Jelint_attack1.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK03,		// Jelint_attack3.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE01,			// Jelint_move01.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE02,			// Jelint_move02.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_RAGE,			// Jelint_rage.wav
	SOUND_EMPIREGUARDIAN_JERINT_MONSTER_DEATH,			// Jelint_death.wav

	// 부사령관 레이몬드		(506/166)
	SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_ATTACK02,		// Raymond_attack2.wav
	SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_RAGE,			// Raymond_rage.wav

	// 지휘관 에르칸느			(507/167)
	SOUND_EMPIREGUARDIAN_ERCANNE_MONSTER_ATTACK03,		// Ercanne_attack3.wav

	// 1군단장 데슬러			(508/168)
	SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK02,// 1Deasuler_attack2.wav
	SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK03,// 1Deasuler_attack3.wav

	// 2군단장 버몬트			(509/169)
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK01,// 2Vermont_attack1.wav
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK02,// 2Vermont_attack2.wav
	SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_DEATH,	// 2Vermont_death.wav

	// 3군단장 카토				(510/170)
	SOUND_EMPIREGUARDIAN_3CORP_CATO_ATTACK02,			// 3Cato_attack2.wav
	SOUND_EMPIREGUARDIAN_3CORP_CATO_MOVE,				// 3Cato_move.wav

	// 4군단장 갈리아			(511/171)
	SOUND_EMPIREGUARDIAN_4CORP_GALLIA_ATTACK02,			// 4Gallia_attack2.wav
	
	// 병참장교					(512/172)
	SOUND_EMPIREGUARDIAN_QUATERMASTER_ATTACK02,			// QuaterMaster_attack2.wav

	// 전투교관					(513/173)
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK01,			// CombatMaster_attack1.wav
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK02,			// CombatMaster_attack2.wav
	SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK03,			// CombatMaster_attack3.wav

	// 대마법사					(515/175)
	SOUND_EMPIREGUARDIAN_GRANDWIZARD_DEATH,				// GrandWizard_death.wav

	// 암살단장					(516/176)
	SOUND_EMPIREGUARDIAN_ASSASSINMASTER_DEATH,			// AssassinMaster_Death.wav

	// 기마단장					(517/177)
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK01,		// CavalryLeader_attack1.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK02,		// CavalryLeader_attack2.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE01,			// CavalryLeader_move01.wav
	SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE02,			// CavalryLeader_move02.wav
	
	// 방패병					(519/178)
	SOUND_EMPIREGUARDIAN_DEFENDER_ATTACK02,				// Defender_attack2.wav
	
	// 치유병					(519/179)
	SOUND_EMPIREGUARDIAN_PRIEST_STOP,					// Priest_stay.wav
#endif // LDS_ADD_EMPIRE_GUARDIAN

#ifdef PBG_ADD_NEWCHAR_MONK
	SOUND_RAGESKILL_THRUST,								// 레이지 파이터스킬 사운드
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
	// 맹독고리전갈
	SOUND_KARUTAN_TCSCORPION_ATTACK,					// ToxyChainScorpion_attack.wav
	SOUND_KARUTAN_TCSCORPION_DEATH,						// ToxyChainScorpion_death.wav
	SOUND_KARUTAN_TCSCORPION_HIT,						// ToxyChainScorpion_hit.wav

	// 본스콜피온
	SOUND_KARUTAN_BONESCORPION_ATTACK,					// BoneScorpion_attack.wav
	SOUND_KARUTAN_BONESCORPION_DEATH,					// BoneScorpion_death.wav
	SOUND_KARUTAN_BONESCORPION_HIT,						// BoneScorpion_hit.wav

	// 오르커스
	SOUND_KARUTAN_ORCUS_MOVE1,							// Orcus_move1.wav
	SOUND_KARUTAN_ORCUS_MOVE2,							// Orcus_move2.wav
	SOUND_KARUTAN_ORCUS_ATTACK1,						// Orcus_attack_1.wav
	SOUND_KARUTAN_ORCUS_ATTACK2,						// Orcus_attack_2.wav
	SOUND_KARUTAN_ORCUS_DEATH,							// Orcus_death.wav

	// 골록
	SOUND_KARUTAN_GOLOCH_MOVE1,							// Goloch_move1.wav
	SOUND_KARUTAN_GOLOCH_MOVE2,							// Goloch_move2.wav
	SOUND_KARUTAN_GOLOCH_ATTACK,						// Goloch_attack.wav
	SOUND_KARUTAN_GOLOCH_DEATH,							// Goloch_death.wav

	// 크립타
	SOUND_KARUTAN_CRYPTA_MOVE1,							// Crypta_move1.wav
	SOUND_KARUTAN_CRYPTA_MOVE2,							// Crypta_move2.wav
	SOUND_KARUTAN_CRYPTA_ATTACK,						// Crypta_attack.wav
	SOUND_KARUTAN_CRYPTA_DEATH,							// Crypta_death.wav

	// 크립포스
	SOUND_KARUTAN_CRYPOS_MOVE1,							// Crypos_move1.wav
	SOUND_KARUTAN_CRYPOS_MOVE2,							// Crypos_move2.wav
	SOUND_KARUTAN_CRYPOS_ATTACK1,						// Crypos_attack_1.wav
	SOUND_KARUTAN_CRYPOS_ATTACK2,						// Crypos_attack_2.wav

	// 콘드라
	SOUND_KARUTAN_CONDRA_MOVE1,							// Condra_move1.wav
	SOUND_KARUTAN_CONDRA_MOVE2,							// Condra_move2.wav
	SOUND_KARUTAN_CONDRA_ATTACK,						// Condra_attack.wav
	SOUND_KARUTAN_CONDRA_DEATH,							// Condra_death.wav

	// 나르콘드라
	SOUND_KARUTAN_NARCONDRA_ATTACK,						// NarCondra_attack.wav
#endif	// ASG_ADD_KARUTAN_MONSTERS

#ifdef ASG_ADD_MAP_KARUTAN
	//  칼루탄 환경음
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