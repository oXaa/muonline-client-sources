// w_CharacterInfo.h: interface for the CHARACTER class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_W_CHARACTER_H__95647591_5047_48A4_81AE_E88B5F17EE94__INCLUDED_)
#define AFX_W_CHARACTER_H__95647591_5047_48A4_81AE_E88B5F17EE94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _PATH_t
{
	unsigned char CurrentPath;
	unsigned char CurrentPathFloat;
	unsigned char PathNum;
	unsigned char PathX[MAX_PATH_FIND];
	unsigned char PathY[MAX_PATH_FIND];

	bool          Success;
	bool          Error;
	unsigned char x,y;
	unsigned char Direction;
	unsigned char Run;
	int           Count;

	_PATH_t()
	{
		CurrentPath = 0;
		CurrentPathFloat = 0;
		PathNum = 0;

		for ( int i = 0; i < MAX_PATH_FIND; ++i )
		{
			PathX[i] = 0;
			PathY[i] = 0;
		}

		Success = 0;
		Error = 0;
		x = 0, y = 0;
		Direction = 0;
		Run = 0;
		Count = 0;
	}

} PATH_t;

typedef struct _PART_t
{
	short Type;
	BYTE  Level;
	BYTE  Option1;
	BYTE  ExtOption;
	BYTE  LinkBone;
	BYTE  CurrentAction;
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
	unsigned short  PriorAction;
#else //PBG_ADD_NEWCHAR_MONK_ANI
	BYTE  PriorAction;
#endif //PBG_ADD_NEWCHAR_MONK_ANI
	float AnimationFrame;
	float PriorAnimationFrame;
	float PlaySpeed;
	BYTE m_byNumCloth;
	void *m_pCloth[2];	// �����ۿ� õ���̱�

#if defined MR0 || defined OBJECT_ID
	unsigned int m_iID;	//Object�� ���
#endif //MR0

	_PART_t()
	{
		Type = 0;
		Level = 0;
		Option1 = 0;
		ExtOption = 0;
		LinkBone = 0;
		CurrentAction = 0;
		PriorAction = 0;
		AnimationFrame = 0;
		PriorAnimationFrame = 0;
		PlaySpeed = 0;
		m_byNumCloth = 0;
		m_pCloth[0] = NULL;
		m_pCloth[1] = NULL;
#if defined MR0 || defined OBJECT_ID
		m_iID = 0;	//Object�� ���
#endif //MR0
	}

} PART_t;

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
//cspetsystem start
typedef struct 
{
	DWORD		m_dwPetType;	//	��Ÿ��
	DWORD       m_dwExp1;       //  ����ġ1.
	DWORD       m_dwExp2;       //  ����ġ2.
	WORD        m_wLevel;       //  ����.
	WORD        m_wLife;        //  �����.
	WORD        m_wDamageMin;   //  �ּ� ������.
	WORD        m_wDamageMax;   //  �ִ� ������.
	WORD        m_wAttackSpeed; //  ���� �ӵ�.
	WORD        m_wAttackSuccess;// ���� ������.
}PET_INFO;
//cspetsystem end
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM


#ifdef LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

#define DEFAULT_MAX_POSTMOVEPCOCESS		15

struct ST_POSTMOVE_PROCESS 
{
	bool				bProcessingPostMoveEvent;
	unsigned int		uiProcessingCount_PostMoveEvent;

	ST_POSTMOVE_PROCESS()
	{
		bProcessingPostMoveEvent = false;
		uiProcessingCount_PostMoveEvent = 0;
	}

	~ST_POSTMOVE_PROCESS()
	{
	}
};
#endif // LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL


class CHARACTER  
{
public:
	CHARACTER();
	virtual ~CHARACTER();

public:
	void Initialize();
	void Destroy();

public:
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	void InitPetInfo(int iPetType);
	PET_INFO* GetEquipedPetInfo(int iPetType);
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
	
	// MoveCharacter�Լ��� ����� ���� ������ RenderCharacter �Լ��󿡼� ����ϰ��� ���Դϴ�.
#ifdef LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

	void			PostMoveProcess_Active( unsigned int uiLimitCount );
	unsigned int	PostMoveProcess_GetCurProcessCount();
	bool			PostMoveProcess_IsProcessing();
	bool			PostMoveProcess_Process();

#endif // LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

public:
	bool        Blood;
	bool        Ride;
	bool        SkillSuccess;
	BOOL        m_bFixForm;         //  �������� �¾Ƶ� ������ ���¿��� ������� �ʴ� ĳ����.	
	bool        Foot[2];
	bool        SafeZone;
	bool        Change;
	bool		HideShadow;
	bool        m_bIsSelected;
	bool        Decoy;

	BYTE	    Class;
	BYTE	    Skin;
	BYTE		CtlCode;
	BYTE        ExtendState;			//  0:��, 1:Ǯ��Ʈ������
	BYTE        EtcPart;				//  ��Ÿ ��Ź ������. ( ����Ʈ�� )
	BYTE		GuildStatus;			//  ��峻������ ��å ( -1 : NONE, 0 : PERSON, 32 : BATTLE_MASTER, 64 : SUB_MASTER, 128 : MASTER )
	BYTE		GuildType;				//  ������� �Ϲ�(0), ��ȣ���(1)
	BYTE		GuildRelationShip;	    //  ������ (0x00 : �������, 0x01 : Union, 0x04 Union Master, 0x02 : Rival, 0x08: Rival Union )
	BYTE        GuildSkill;             //  ��Ʋ �������� ��� ��ų.
	BYTE        GuildMasterKillCount;   //  ��Ʋ ������ ųī��Ʈ.
	BYTE        BackupCurrentSkill;     //  ��ų �ε��� ���.
	BYTE        GuildTeam;
#ifdef ASG_ADD_GENS_SYSTEM
	BYTE		m_byGensInfluence;		//	�ս� ����.(0:����, 1:��������, 2:�ٳ׸�Ʈ)
#endif	// ASG_ADD_GENS_SYSTEM
	BYTE        PK;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
	char		PKPartyLevel;
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER	
	BYTE        AttackFlag;
	BYTE		AttackTime;
	BYTE        TargetAngle;
	BYTE        Dead;
	BYTE        Run;
	WORD		Skill;
	BYTE        SwordCount;
	BYTE		byExtensionSkill;		//	Ȯ�� ��ų. ( 0: ����, 1:�⺻�޺�, 2: ���� ).
	BYTE		m_byDieType;			//	�״� ����.
	BYTE		StormTime;
	BYTE		JumpTime;
	BYTE        TargetX;
	BYTE        TargetY;
	BYTE        SkillX;
	BYTE        SkillY;
	BYTE        Appear;
	BYTE	    CurrentSkill;
	BYTE        CastRenderTime;
	BYTE        m_byFriend;
	WORD        MonsterSkill; 


#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char        ID[32];		// �ѱ��� �ƴϸ� ID 32����Ʈ ���
#else //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char        ID[24];		// �ѱ��̸� ID 24����Ʈ ���
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char 		Movement;
	char		MovementType;
	char		CollisionTime;

	short       GuildMarkIndex;		// ���� ���� ����� ��帶ũ���ۿ����� �ε���
	SHORT       Key;
	short   	TargetCharacter;

	WORD        Level;
	WORD        MonsterIndex;
	WORD        Damage;
	WORD        Hit;
	WORD        MoveSpeed;

	int			Action;
	int         ExtendStateTime;
	int			LongRangeAttack;
	int			SelectItem;
	int			Item;
	int         FreezeType;
	int         PriorPositionX;
	int         PriorPositionY;
	int         PositionX;
	int         PositionY;
	int         m_iDeleteTime;
	int			m_iFenrirSkillTarget;

	float		ProtectGuildMarkWorldTime;
	float		AttackRange;
	float       Freeze;
	float       Duplication;
	float		Rot;

	vec3_t		TargetPosition;
	vec3_t      Light;

	PART_t    	BodyPart[MAX_BODYPART];
	PART_t		Weapon[2];
	PART_t		Wing;
	PART_t		Helper;
	PART_t		Flag;
	PATH_t      Path;

	void*       m_pParts;

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
#ifdef PET_SYSTEM
	void*       m_pPet;
#endif// PET_SYSTEM
	PET_INFO	m_PetInfo[PET_TYPE_END];		// ���� �����ϰ��ִ� ��(��ũ�ε常 ���) - ��ũȣ��/��ũ���Ǹ�
#else // KJH_FIX_DARKLOAD_PET_SYSTEM																		//## �ҽ����� �����
#ifdef PET_SYSTEM
	void*       m_pPet;
#endif// PET_SYSTEM
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM																		//## �ҽ����� �����
	
#ifdef YDG_ADD_NEW_DUEL_SYSTEM
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char        OwnerID[32];		// �ڽ��� ��ȯ�� ĳ������ ID(���� ��ȯ����) �ѱ��� �ƴϸ� ID 32����Ʈ ���
#else //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	char        OwnerID[24];		// �ڽ��� ��ȯ�� ĳ������ ID(���� ��ȯ����) �ѱ��̸� ID 24����Ʈ ���
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN
#endif	// YDG_ADD_NEW_DUEL_SYSTEM
		
#ifdef LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL
	private: 
	ST_POSTMOVE_PROCESS*
				m_pPostMoveProcess;

	public:
#endif // LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

	void*		m_pTempParts;	// �ɸ��Ϳ� �ӽ÷� ����� ������Ʈ
	int			m_iTempKey;		// �ɸ��Ϳ� �ӽ÷� ������ �ִ� Key��
	WORD		m_CursedTempleCurSkill;
	bool		m_CursedTempleCurSkillPacket;
	OBJECT	    Object;
#ifdef PBG_ADD_GENSRANKING
	BYTE		m_byRankIndex;
#endif //PBG_ADD_GENSRANKING
#ifdef PBG_MOD_STRIFE_GENSMARKRENDER
#ifdef KJH_FIX_CONTRIBUTIONPOINT_CASTING
	int			m_nContributionPoint;	// �⿩�� ����Ʈ
#else // KJH_FIX_CONTRIBUTIONPOINT_CASTING
	BYTE		m_nContributionPoint;	// �⿩�� ����Ʈ
#endif // KJH_FIX_CONTRIBUTIONPOINT_CASTING
#endif //PBG_MOD_STRIFE_GENSMARKRENDER
};

#endif // !defined(AFX_W_CHARACTERINFO_H__95647591_5047_48A4_81AE_E88B5F17EE94__INCLUDED_)
