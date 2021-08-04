#ifndef ___STRUCT_H__
#define ___STRUCT_H__

#pragma once

#include "w_Buff.h"

#include "w_ObjectInfo.h"
class OBJECT;
#include "w_CharacterInfo.h"
class CHARACTER;

/////////////////////// Predecaration ////////////////////////////////////
namespace SEASON3B
{
	class CNewUIItemMng;
}

#ifdef MR0
namespace ModelManager
{
	void	SetTargetObject(OBJECT*);	//�ִϸ��̼� Binding�� Object ����
	void	SetTargetObject_(int iFlag = 0);
}
#endif //MR0
//////////////////////////////////////////////////////////////////////////

//�迭�� ���ǵ� �κ��� �ٽ� ������ �ؾ��Ѵ�.
//���� �����ε��� ���� �ؼ� ���� ������ ��ũ �ɾ����...

#ifdef CSK_FIX_MONSTERSKILL
#define MAX_MONSTERSKILL_NUM	10
#endif // CSK_FIX_MONSTERSKILL

namespace info
{
	struct Script_Item
	{
		char Name[30];
		bool TwoHand;
		WORD Level;
		BYTE m_byItemSlot;
		BYTE m_bySkillIndex;
		BYTE Width;
		BYTE Height;
		BYTE DamageMin;
		BYTE DamageMax;
		BYTE SuccessfulBlocking;
		BYTE Defense;
		BYTE MagicDefense;
		BYTE WeaponSpeed;
		BYTE WalkSpeed;
		BYTE Durability;
		BYTE MagicDur;
		BYTE MagicPower;
		WORD RequireStrength;
		WORD RequireDexterity;
		WORD RequireEnergy;
		WORD  RequireVitality;
		WORD RequireCharisma;
		WORD RequireLevel;
		BYTE Value;
		int  iZen;
		BYTE  AttType;
		BYTE RequireClass[MAX_CLASS];
		BYTE Resistance[MAX_RESISTANCE];
	};
	
#ifndef CSK_FIX_MONSTERSKILL		// ������ �� ������ �ϴ� �ҽ�	
	struct Script_Skill
	{
		int Skill_Num[5];
		int Slot;
	};
#endif //! CSK_FIX_MONSTERSKILL		// ������ �� ������ �ϴ� �ҽ�

	struct Script_Silde 
	{
		typedef std::vector<char*>     SildeVECTOR;
		SildeVECTOR					   Sildelist;
	};

	struct Script_Dialog
	{
		char m_lpszText[MAX_LENGTH_DIALOG];
		int m_iNumAnswer;
		int m_iLinkForAnswer[MAX_ANSWER_FOR_DIALOG];
		int m_iReturnForAnswer[MAX_ANSWER_FOR_DIALOG];
		char m_lpszAnswer[MAX_ANSWER_FOR_DIALOG][MAX_LENGTH_ANSWER];
	};
	
	struct Script_Credit
	{
		BYTE	byClass;				// �� ��ġ.(1~3°��, 0�̸� ũ���� ����.)
		char	szName[32];	            // �׸�(�̸�, �μ� ��) ���ڿ�.
		//char	szName[CRW_NAME_MAX];	// �׸�(�̸�, �μ� ��) ���ڿ�.
	};

	struct Script_Movereq
	{
		int index;
		char szMainMapName[32];			//. Main map name
		char szSubMapName[32];			//. Substitute map name
		int	iReqLevel;					//. required level
		int iReqZen;					//. required zen
		int iGateNum;					//. Gate number
	};

	struct Script_Quest_Class_Act
	{
		BYTE    chLive;                 //  �ش�Ŭ����. 0:�ش���� ����. 1:�ش��.
		BYTE    byQuestType;            //  ����Ʈ ����.
		WORD    wItemType;				//  ������ Ÿ�� ��ȣ �Ǵ� �� �ε���.
		BYTE    byItemSubType;          //  ������.
		BYTE	byItemLevel;			//	������ ����.
		BYTE    byItemNum;              //  ������ ��.
		BYTE    byRequestType;          //  �䱸 ���� �ε���.
		BYTE    byRequestClass[MAX_CLASS];		//  �ش� Ŭ����.
		short   shQuestStartText[4];    //  ����Ʈ ���� ����. ( �����, �����, ���ǿϺ�, ����Ϸ� ) 
	};

	struct Script_Quest_Class_Request
	{
		BYTE    byLive;                 //  
		BYTE    byType;                 //  255�� ���� �䱸 ������.
		WORD    wCompleteQuestIndex;    //  ���� �޷�� ����Ʈ �ε���.
		WORD    wLevelMin;              //  �ּ� ����.
		WORD    wLevelMax;              //  �ִ� ����.
		WORD	wRequestStrength;		//	�䱸 ��.
		DWORD   dwZen;                  //  �䱸 ��.
		short   shErrorText;            //  
	};

	struct Script_Quest
	{
		short   shQuestConditionNum;    //  ����Ʈ ���� ���� ��.
		short   shQuestRequestNum;      //  ����Ʈ �䱸 ���� ��.
		WORD    wNpcType;              //  NPCŸ��.
		char    strQuestName[32];       //  ����Ʈ �̸�.

		Script_Quest_Class_Act     QuestAct[MAX_QUEST_CONDITION];        //  ���� ����.
		Script_Quest_Class_Request QuestRequest[MAX_QUEST_REQUEST];    //  �䱸 ����.
	};
};

#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
//scene start
typedef struct
{
	char  IP[20];						// �Ⱦ�.
	WORD  Port;							// �Ⱦ�.
	WORD  Index;
	BYTE  Percent;
#ifdef _PVP_DYNAMIC_SERVER_TYPE
	BYTE  IsPvPServer;
#endif	// _PVP_DYNAMIC_SERVER_TYPE
} SERVER_t;

typedef struct
{
	char     Name[20];
	BYTE     Number;
	bool     extServer;					// �Ⱦ�.
	SERVER_t Server[MAX_SERVER_LOW];
} SERVER_LIST_t;
//scene end
#endif // KJH_ADD_SERVER_LIST_SYSTEM

//infomation start
typedef struct
{
	BYTE Flag;
	BYTE Map;
	BYTE x1;
	BYTE y1;
	BYTE x2;
	BYTE y2;
	WORD Target;
	BYTE Angle;
#ifdef CSK_ADD_MAP_ICECITY	
	WORD Level;
#else // CSK_ADD_MAP_ICECITY	
	BYTE Level;
#endif // CSK_ADD_MAP_ICECITY
#ifdef ASG_ADD_GATE_TEXT_MAX_LEVEL
	WORD m_wMaxLevel;	// �ִ� ���� ����.
#endif	// ASG_ADD_GATE_TEXT_MAX_LEVEL
} GATE_ATTRIBUTE;

typedef struct
{
	char m_lpszText[MAX_LENGTH_DIALOG];
	int m_iNumAnswer;
	int m_iLinkForAnswer[MAX_ANSWER_FOR_DIALOG];
	int m_iReturnForAnswer[MAX_ANSWER_FOR_DIALOG];
	char m_lpszAnswer[MAX_ANSWER_FOR_DIALOG][MAX_LENGTH_ANSWER];
} DIALOG_SCRIPT;//Script_Dialog


typedef struct
{
	char Name[30];
	bool TwoHand;
	WORD Level;
	BYTE m_byItemSlot;
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	WORD m_wSkillIndex;
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	BYTE m_bySkillIndex;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	BYTE Width;
	BYTE Height;
	BYTE DamageMin;
	BYTE DamageMax;
	BYTE SuccessfulBlocking;
	BYTE Defense;
	BYTE MagicDefense;
	BYTE WeaponSpeed;
	BYTE WalkSpeed;
	BYTE Durability;
	BYTE MagicDur;
	BYTE MagicPower;
	WORD RequireStrength;
	WORD RequireDexterity;
	WORD RequireEnergy;
	WORD  RequireVitality;
	WORD RequireCharisma;
	WORD RequireLevel;
	BYTE Value;
	int  iZen;
	BYTE  AttType;
	BYTE RequireClass[MAX_CLASS];
	BYTE Resistance[MAX_RESISTANCE];
} ITEM_ATTRIBUTE;

typedef struct _MASTER_LEVEL_DATA
{
	BYTE Width;
	int Ability[8][4];
}MASTER_LEVEL_DATA;

#ifdef PJH_ADD_MINIMAP
typedef struct _MINI_MAP
{
	BYTE Kind;
	int	 Location[2];
	int  Rotation;
#ifdef KJH_FIX_MINIMAP_NAME
	char Name[100];
#else KJH_FIX_MINIMAP_NAME
	char Name[30];
#endif // KJH_FIX_MINIMAP_NAME
}MINI_MAP;
#endif //PJH_ADD_MINIMAP

#pragma pack(push, 1)
typedef struct tagITEM
{
	short Type;
	int   Level;
	BYTE  Part;
	BYTE  Class;
	bool  TwoHand;
	WORD  DamageMin;
	WORD  DamageMax;
	BYTE  SuccessfulBlocking;
	WORD  Defense;
	WORD  MagicDefense;
	BYTE  MagicPower;
	BYTE  WeaponSpeed;
	WORD  WalkSpeed;
	BYTE  Durability;
	BYTE  Option1;
	BYTE  ExtOption;
	WORD  RequireStrength;
	WORD  RequireDexterity;
	WORD  RequireEnergy;
	WORD  RequireVitality;
	WORD  RequireCharisma;
	WORD  RequireLevel;
	BYTE  SpecialNum;
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	WORD  Special     [MAX_ITEM_SPECIAL];
#else //PBG_ADD_NEWCHAR_MONK_SKILL
	BYTE  Special     [MAX_ITEM_SPECIAL];
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	BYTE  SpecialValue[MAX_ITEM_SPECIAL];
	DWORD Key;	//client olny
	
#ifdef LDS_FIX_OUTPUT_WRONG_COUNT_EQUIPPEDSETITEMOPTIONVALUE
	BYTE bySelectedSlotIndex;
#endif // LDS_FIX_OUTPUT_WRONG_COUNT_EQUIPPEDSETITEMOPTIONVALUE

	union 
	{
		BYTE  x;    //client olny
		BYTE  lineal_pos;	// ���� ��ġ(==y*column+x)
	};
	union
	{
		BYTE  y;    //client olny
		BYTE  ex_src_type;	// ������ �޴����� ������ �ʴ� static�� �������� ��� �� ������ �����Ѵ�.
		// 0: ����, 1: �κ��丮 ���â
	};
	WORD  Jewel_Of_Harmony_Option;//�ɼ� ����
	WORD  Jewel_Of_Harmony_OptionLevel;//�ɼ� ����( ���� �ƴ� )
	bool option_380;
#ifdef SOCKET_SYSTEM
	BYTE bySocketOption[MAX_SOCKETS];	// ���� ���� (�������� ������ �״�� ����-������ �����ۿ�)
	BYTE SocketCount;					// ���� ���� (0~MAX_SOCKETS), 0: ���� ������ �ƴ�
	BYTE SocketSeedID[MAX_SOCKETS];		// �õ� ������ȣ (0~49), SOCKET_EMPTY: �� ����
	BYTE SocketSphereLv[MAX_SOCKETS];	// ���Ǿ� ���� (1~5)
	BYTE SocketSeedSetOption;			// �õ� ��Ʈ �ɼ� (���� ������ �����Ǵ�)
#endif	// SOCKET_SYSTEM
	
	// ������ �� ������ �ϴ� �ҽ�
	int   Number;	//. UI_RENEW_INVENTORY_BASE: ������� ���� ����
	BYTE  Color;	//. UI_RENEW_INVENTORY_BASE: ������� ���� ����
	
	BYTE byColorState;		// ������ �ؿ� �򸮴� Į�� ����
	
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
	bool	bPeriodItem;	// �Ⱓ�� �������ΰ�?
	bool	bExpiredPeriod;	// �Ⱓ�� ����Ǿ���?
	//DWORD	dwLeftTime;		// �Ⱓ�� �������϶� �����ð� (���� : ��)	- Render��
	long	lExpireTime;	// �Ⱓ ���� �ð�.
	//DWORD	dwPastSystemTime;	// ����System�ð�		- ����
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM

private:
	friend class SEASON3B::CNewUIItemMng;
	int   RefCount;		//. ������ CNewUIItemMng ������ ���� ����
} ITEM;
#pragma pack(pop)

typedef struct
{
	WORD Life;
	WORD MoveSpeed;
	WORD AttackSpeed;
	WORD AttackDamageMin;
	WORD AttackDamageMax;
	WORD Defense;
	WORD MagicDefense;
	WORD AttackRating;
	WORD SuccessfulBlocking;
} MONSTER_ATTRIBUTE;

typedef struct
{
	WORD				Type;
	char				Name[32];
	WORD				Level;
	MONSTER_ATTRIBUTE	Attribute;
} MONSTER_SCRIPT;

typedef struct
{
	short             Type;
	BYTE              Level;
	int               Experince;
	MONSTER_ATTRIBUTE Attribute;
} MONSTER;

typedef struct
{
	char Name[32];
	BYTE Level;
	WORD Damage;
	WORD Mana;
	WORD AbilityGuage;
	BYTE Distance;
	int  Delay;

#ifdef PBG_FIX_SKILL_DEMENDCONDITION
	int Energy;				// �ʿ� ������ ( ������ �ʿ��� = 20+(ReqEng*Level)*0.04 )
#else //PBG_FIX_SKILL_DEMENDCONDITION
	BYTE Energy;            // �ʿ� ������ ( ������ �ʿ��� = 20+(ReqEng*Level)*0.04 )
#endif //PBG_FIX_SKILL_DEMENDCONDITION
	
	WORD Charisma;
	BYTE MasteryType;
	BYTE SkillUseType;      //  ��ų ���� ����.
	BYTE SkillBrand;        //  ��ų�� ����ϱ� ���� �����Ǿ� �ϴ� ��ų ��ȣ.
	BYTE KillCount;
	BYTE RequireDutyClass[MAX_DUTY_CLASS];
	BYTE RequireClass[MAX_CLASS];
	WORD Magic_Icon;		//������ ��ų���� ���
	
#ifdef LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER
	BYTE TypeSkill;
#endif // LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER

#ifdef PBG_FIX_SKILL_DEMENDCONDITION
	int Strength;		// �ʿ� ��
	int Dexterity;	    // �ʿ� ��ø
#endif //PBG_FIX_SKILL_DEMENDCONDITION
} SKILL_ATTRIBUTE;


typedef struct
{
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD Mana;
	WORD Shield;
	BYTE LevelLife;
	BYTE LevelMana;
	BYTE VitalityToLife;
	BYTE EnergyToMana;
	BYTE ClassSkill[MAX_SKILLS];
} CLASS_ATTRIBUTE;

typedef struct
{
	char Name[MAX_ID_SIZE+1];
	BYTE Class;
	BYTE Skin;
	WORD Level;
	DWORD Experience;
	DWORD NextExperince;

	WORD Strength;		//��
	WORD Dexterity;		//��ø
	WORD Vitality;		//ü��
	WORD Energy;		//������
	WORD Charisma;		//���
	WORD Life;
	WORD Mana;
	WORD LifeMax;
	WORD ManaMax;
	WORD Shield;
	WORD ShieldMax;
	WORD AttackRatingPK;
	WORD SuccessfulBlockingPK;
	WORD AddStrength;
	WORD AddDexterity;
	WORD AddVitality;
	WORD AddEnergy;
	WORD AddLifeMax;
	WORD AddManaMax;
	WORD AddCharisma;
	WORD SkillMana;
	WORD SkillManaMax;
	BYTE Ability;
	WORD AbilityTime[3];

	short AddPoint;			// ���� ���� ����Ʈ
	short MaxAddPoint;		// �ִ� ���� ����Ʈ
	WORD wMinusPoint;		// ���� ���� ����Ʈ
	WORD wMaxMinusPoint;	// �ִ� ���� ����Ʈ
	WORD AttackSpeed;
	WORD AttackRating;
	WORD AttackDamageMinRight;
	WORD AttackDamageMaxRight;
	WORD AttackDamageMinLeft;
	WORD AttackDamageMaxLeft;
	WORD MagicSpeed;
	WORD MagicDamageMin;
	WORD MagicDamageMax;
	WORD CurseDamageMin;	// ���ַ� ������ �ּҰ�
	WORD CurseDamageMax;	// ���ַ� ������ �ִ밪
	WORD CriticalDamage;
	WORD SuccessfulBlocking;
	WORD Defense;
	WORD MagicDefense;
	WORD WalkSpeed;
	WORD LevelUpPoint;
	BYTE SkillNumber;
	BYTE SkillMasterNumber;
	WORD Skill[MAX_SKILLS];
	BYTE SkillLevel[MAX_SKILLS];
	int  SkillDelay[MAX_SKILLS];        //  ��ų ������.
} CHARACTER_ATTRIBUTE;

typedef struct _MASTER_LEVEL_VALUE
{
	short		 nMLevel;			// ���� �����ͷ���
	__int64		 lMasterLevel_Experince;
	__int64		 lNext_MasterLevel_Experince;

	short		nAddMPoint;			// �߰��� �����ͷ��� ����Ʈ
	short      	nMLevelUpMPoint;	// ��� ������ �����ͷ��� ����Ʈ
	short		nTotalMPoint;		// ���� ���� �� �����ͷ��� ����Ʈ
	short		nMaxPoint;			// �ִ� �����ͷ��� ����Ʈ

	WORD		wMaxLife;
	WORD		wMaxMana;
	WORD		wMaxShield;
	WORD		wMaxBP;

} MASTER_LEVEL_VALUE;

//infomation end

#ifdef MR0
typedef struct _AUTOOBJ : public OBJECT
{
	_AUTOOBJ::_AUTOOBJ() : OBJECT()
	{
		m_iID = GenID();
	}
}AUTOOBJ;
#endif //MR0

typedef struct _OBJECT_BLOCK
{
	unsigned char Index;
	OBJECT        *Head;
	OBJECT        *Tail;
	bool          Visible;

	_OBJECT_BLOCK()
	{
		Index = 0;
		Head = NULL;
		Tail = NULL;
		Visible = false;
	}

} OBJECT_BLOCK;

typedef struct
{
	bool   Live;
	int    Type;
	int    TexType;
	int    SubType;
	float  Scale;
	vec3_t Position;
	vec3_t Angle;
	vec3_t Light;
	float  Alpha;
	int    LifeTime;
	OBJECT *Target;
	float  Rotation;
	int    Frame;

	bool   bEnableMove;
	float  Gravity;
	vec3_t Velocity;
	vec3_t TurningForce;
	vec3_t StartPosition; 
#ifdef ADD_SOCKET_ITEM
	int iNumBone;				// ������Ʈ�� �ش��ϴ� ����ȣ�� ��ġ�� ����
#endif // ADD_SOCKET_ITEM
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	bool bRepeatedly;
	float fRepeatedlyHeight;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
} PARTICLE;

typedef struct
{
	bool	 Live;
	int	     Type;
	OBJECT   *Owner;
} OPERATE;

typedef struct
{
	short  Key;
	ITEM   Item;
	OBJECT Object;
} ITEM_t;

//object end

typedef struct Script_Skill
{
#ifdef CSK_FIX_MONSTERSKILL
	int Skill_Num[MAX_MONSTERSKILL_NUM];
#else // CSK_FIX_MONSTERSKILL
	int Skill_Num[5];
#endif // CSK_FIX_MONSTERSKILL
	int Slot;
}Script_Skill;


typedef struct
{
	bool		Live;
	int			Type;
	int         TexType;
	int			SubType;
	BYTE        RenderType;
	BYTE        RenderFace;
	float		Scale;
	vec3_t		Position;
	vec3_t      StartPosition;
	vec3_t		Angle;
	vec3_t		HeadAngle;
	vec3_t		Light;
	OBJECT      *Target;
	vec3_t      TargetPosition;
	BYTE        byOnlyOneRender;
	int			NumTails;
	int			MaxTails;
	vec3_t		Tails[MAX_TAILS][4];
	int  		LifeTime;
	bool        Collision;
	float		Velocity;
	vec3_t		Direction;
	short       PKKey;
	WORD		Skill;
	BYTE		Weapon;
	int			MultiUse;
	bool        bTileMapping;
	BYTE        m_byReverseUV;          //  UV��ǥ ���� ( 0: ����, 1:V ��ǥ ����, 2:U ��ǥ ����. )
	bool        m_bCreateTails;         //  �⺻������ ������ �������� ����. ( true:�����Ѵ�. false:����ڰ� ���� �����Ѵ�. )
	int			TargetIndex[5];
	BYTE		m_bySkillSerialNum;
	int			m_iChaIndex;
	short int	m_sTargetIndex;			// ü�ζ���Ʈ�׽�ų ���� Ÿ���� ���� ����
} JOINT;
//character end

//inventory start
typedef struct
{
	char Name[MAX_ID_SIZE+1];
	BYTE Number;
	BYTE Server;
	BYTE GuildStatus;	// �������
} GUILD_LIST_t;

typedef struct
{
	int  Key;
	char UnionName[8+1];
	char GuildName[8+1];
	BYTE Mark[64];
} MARK_t;

typedef struct
{
	char    Name[MAX_ID_SIZE+1];
	BYTE    Number;
	BYTE    Map;
	BYTE    x;
	BYTE    y;
	int     currHP;
	int     maxHP;
	BYTE    stepHP;
	int     index;
} PARTY_t;
//inventory end

//interface start
typedef struct
{
	char      ID[MAX_ID_SIZE+1];
	char      Text[256];
	int       Type;
	int       LifeTime;
	int       Width;
} WHISPER;

typedef struct
{
	bool m_bMagic;
	int m_iSkill;
	int m_iTarget;
} MovementSkill;
//interface end

//matchevent start
typedef struct  // �Ǹ��� ���� ����
{
	char	m_lpID[MAX_ID_SIZE];	// ID
	int		m_iScore;				// ��������
	DWORD	m_dwExp;				// ���� ����ġ
	int		m_iZen;					// �����
} DevilSquareRank;
//matchevent end

//gmhellas start
//  ���õ� ������Ʈ�� ����.
typedef struct 
{
	char    m_strName[64];
	vec3_t  m_vPos;
}ObjectDescript;
//gmhellas end

//csquest start
typedef struct 
{
	BYTE    chLive;                 //  �ش�Ŭ����. 0:�ش���� ����. 1:�ش��.
	BYTE    byQuestType;            //  ����Ʈ ����.
	WORD    wItemType;				//  ������ Ÿ�� ��ȣ �Ǵ� �� �ε���.
	BYTE    byItemSubType;          //  ������.
	BYTE	byItemLevel;			//	������ ����.
	BYTE    byItemNum;              //  ������ ��.
	BYTE    byRequestType;          //  �䱸 ���� �ε���.
	BYTE    byRequestClass[MAX_CLASS];//  �ش� Ŭ����.
	short   shQuestStartText[4];    //  ����Ʈ ���� ����. ( �����, �����, ���ǿϺ�, ����Ϸ� ) 
} QUEST_CLASS_ACT;

typedef struct 
{
	BYTE    byLive;                 //  
	BYTE    byType;                 //  255�� ���� �䱸 ������.
	WORD    wCompleteQuestIndex;    //  ���� �޷�� ����Ʈ �ε���.
	WORD    wLevelMin;              //  �ּ� ����.
	WORD    wLevelMax;              //  �ִ� ����.
	WORD	wRequestStrength;		//	�䱸 ��.
	DWORD   dwZen;                  //  �䱸 ��.
	short   shErrorText;            //  
} QUEST_CLASS_REQUEST;

typedef struct 
{
	short   shQuestConditionNum;    //  ����Ʈ ���� ���� ��.
	short   shQuestRequestNum;      //  ����Ʈ �䱸 ���� ��.
	WORD	wNpcType;				//  NPCŸ��.

	unicode::t_char strQuestName[32];       //  ����Ʈ �̸�.

	QUEST_CLASS_ACT     QuestAct[MAX_QUEST_CONDITION];      //  ���� ����.
	QUEST_CLASS_REQUEST QuestRequest[MAX_QUEST_REQUEST];    //  �䱸 ����.
} QUEST_ATTRIBUTE;


//  ����Ʈ �÷��� ����.
typedef struct 
{
	BYTE    byFlag;                 //  0: �̻��. 1~128:����Ʈ ������, 129~255:���� ������.
	BYTE    byCount;                //  ����.
} QUEST_FLAG_BUFFER;


//  ũ����Ʈ.
typedef struct 
{
	int iCrastGold;                 //  ��.
	int iCrastSilver;               //  ��.
	int iCrastBronze;               //  ��.
} QUEST_CRAST;
//csquest end

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM							//## �ҽ����� �����.
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
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM						//## �ҽ����� �����.

//csmapinterface start 
//  ��ġ ����.
typedef struct
{
	BYTE    bIndex;
	BYTE    x;
	BYTE    y;
}VisibleUnitLocation;

//  ��� ���.
typedef struct 
{
	BYTE    byTeam;     //  �� ��ȣ.
	BYTE    byX;        //  ��ġ.
	BYTE    byY;        //  ��ġ.
	BYTE    byCmd;      //  ���. ( 0:����(A), 1:���(D), 2:���(H), 3:����(F) ).
	BYTE    byLifeTime; //  Ư�� ���¸� �����ִ� �ð�.
}GuildCommander;
//csmapinterface end

//csitemsetoption start
typedef	struct 
{
	//	���� 255�� �������� �ʴ� ��������.
	//	[0]: A��Ʈ, [1]:B��Ʈ.
	BYTE	byOption[2];		//	�ɼ� �ε���.
	BYTE	byMixItemLevel[2];	//	������ �ƾ����� ����.
}ITEM_SET_TYPE;


typedef struct 
{
	char	strSetName[64];			    //	��Ʈ �߰� �̸�.
	BYTE	byStandardOption[6][2];	    //	�⺻ �ɼ� ( �ɼ� 1 ~ 6 ).
	BYTE	byStandardOptionValue[6][2];//	�⺻ �ɼ� ��ġ ( �ɼ� 1 ~ 6 ).
	BYTE	byExtOption[2];			    //	�߰� �ɼ� ( �ɼ� 7 ~ 8 ).
	BYTE	byExtOptionValue[2];        //	�߰� �ɼ� ��ġ ( �ɼ� 7 ~ 8 ).
	BYTE	byOptionCount;
	BYTE	byFullOption[5];		    //	Ǯ   �ɼ� ( Ǯ�� 1 ~ 5 ).
	BYTE	byFullOptionValue[5];		//	Ǯ   �ɼ� ��ġ ( Ǯ�� 1 ~ 5 ).
	BYTE	byRequireClass[MAX_CLASS];	//	�ش� Ŭ����.
}ITEM_SET_OPTION;
//csitemsetoption end

//cseventmatch start
typedef struct      //  �̺�Ʈ ��� ��� ����.
{
	char	m_lpID[MAX_ID_SIZE];	// ID
	int		m_iScore;				// ��������         ( ī���� ĳ��:���ͼ� ).
	DWORD	m_dwExp;				// ���� ����ġ
	int		m_iZen;					// �����           ( ī���� ĳ��:����� ).
}MatchResult;
//cseventmatch end

//cdirection start
struct DirectionMonster
{
	int		m_Index;			// ������ ������ ��ȣ
	int		m_iActionCheck;		// ũ���̿��� ������ ���� üũ
	bool	m_bAngleCheck;		// ������ ���� ���� Ʈ�°� üũ
};
//cdirection end

#endif ___STRUCT_H__
