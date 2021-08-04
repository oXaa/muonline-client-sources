// w_CharacterInfo.cpp: implementation of the CHARACTER class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "w_CharacterInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHARACTER::CHARACTER()
{
	Initialize();
}

CHARACTER::~CHARACTER()
{
	Destroy();
}

void CHARACTER::Initialize()
{
	Object.Initialize();
	
	Blood = false;
	Ride = false;
	SkillSuccess = false;
	m_bFixForm = false;         //  �������� �¾Ƶ� ������ ���¿��� ������� �ʴ� ĳ����.	
	Foot[0] = false;
	Foot[1] = false;
	SafeZone = false;
	Change = false;
	HideShadow = false;
	m_bIsSelected = false;
	Decoy = false;

	Class = 0;
	Skin = 0;
	CtlCode = 0;
	ExtendState = 0;			//  0:��, 1:Ǯ��Ʈ������
	EtcPart = 0;				//  ��Ÿ ��Ź ������. ( ����Ʈ�� )
	GuildStatus = 0;			//  ��峻������ ��å ( -1 : NONE, 0 : PERSON, 32 : BATTLE_MASTER, 64 : SUB_MASTER, 128 : MASTER )
	GuildType = 0;				//  ������� �Ϲ�(0), ��ȣ���(1)
	GuildRelationShip = 0;	    //  ������ (0x00 : �������, 0x01 : Union, 0x04 Union Master, 0x02 : Rival, 0x08: Rival Union )
	GuildSkill = 0;             //  ��Ʋ �������� ��� ��ų.
	GuildMasterKillCount = 0;   //  ��Ʋ ������ ųī��Ʈ.
	BackupCurrentSkill = 0;     //  ��ų �ε��� ���.
	GuildTeam = 0;
#ifdef ASG_ADD_GENS_SYSTEM
	m_byGensInfluence = 0;		//	�ս� ����.(0:����, 1:��������, 2:�ٳ׸�Ʈ)
#endif	// ASG_ADD_GENS_SYSTEM
	PK = 0;
	AttackFlag = 0;
	AttackTime = 0;
	TargetAngle = 0;
	Dead = 0;
	Run = 0;
	Skill = 0;
	SwordCount = 0;
	byExtensionSkill = 0;		//	Ȯ�� ��ų. ( 0: ����, 1:�⺻�޺�, 2: ���� ).
	m_byDieType = 0;			//	�״� ����.
	StormTime = 0;
	JumpTime = 0;
	TargetX = 0;
	TargetY = 0;
	SkillX = 0;
	SkillY = 0;
	Appear = 0;
	CurrentSkill = 0;
	CastRenderTime = 0;
	m_byFriend = 0;
	MonsterSkill = 0;

#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( int i = 0; i < 32; ++i ) ID[i] = 0;
#else //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( int i = 0; i < 24; ++i ) ID[i] = 0;
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN

	Movement = 0;
	MovementType = 0;
	CollisionTime = 0;
	GuildMarkIndex = 0;		// ���� ���� ����� ��帶ũ���ۿ����� �ε���
	Key = 0;
	TargetCharacter = 0;

	Level = 0;
	MonsterIndex = 0;
	Damage = 0;
	Hit = 0;
	MoveSpeed = 0;

	Action = 0;
	ExtendStateTime = 0;
	LongRangeAttack = 0;
	SelectItem = 0;
	Item = 0;
	FreezeType = 0;
	PriorPositionX = 0;
	PriorPositionY = 0;
	PositionX = 0;
	PositionY = 0;
	m_iDeleteTime = 0;
	m_iFenrirSkillTarget = -1;

	ProtectGuildMarkWorldTime = 0.0f;
	AttackRange = 0.0f;
	Freeze = 0.0f;
	Duplication = 0.0f;
	Rot = 0.0f;

	IdentityVector3D( TargetPosition );
	IdentityVector3D( Light );

	m_pParts = NULL;

	// �� ����
#ifdef PET_SYSTEM
	m_pPet = NULL;
#endif// PET_SYSTEM
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	InitPetInfo(PET_TYPE_DARK_HORSE);
	InitPetInfo(PET_TYPE_DARK_SPIRIT);
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM

#ifdef YDG_ADD_NEW_DUEL_SYSTEM
#ifdef _VS2008PORTING
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( int i = 0; i < 32; ++i ) OwnerID[i] = 0;
#else //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( int i = 0; i < 24; ++i ) OwnerID[i] = 0;
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN
#else // _VS2008PORTING
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( i = 0; i < 32; ++i ) OwnerID[i] = 0;
#else //SELECTED_LANGUAGE != LANGUAGE_KOREAN
	for( i = 0; i < 24; ++i ) OwnerID[i] = 0;
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN
#endif // _VS2008PORTING
#endif	// YDG_ADD_NEW_DUEL_SYSTEM

#ifdef LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL
	m_pPostMoveProcess	= NULL;
#endif // LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

	m_pTempParts = NULL;
	m_iTempKey = 0;
	m_CursedTempleCurSkill = AT_SKILL_CURSED_TEMPLE_PRODECTION;
	m_CursedTempleCurSkillPacket = false;
#ifdef PBG_ADD_GENSRANKING
	m_byRankIndex=0;
#endif //PBG_ADD_GENSRANKING
#ifdef PBG_MOD_STRIFE_GENSMARKRENDER
	m_nContributionPoint=0;
#endif //PBG_MOD_STRIFE_GENSMARKRENDER
}

void CHARACTER::Destroy()
{

}

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
void CHARACTER::InitPetInfo(int iPetType)
{
	m_PetInfo[iPetType].m_dwPetType = PET_TYPE_NONE;
}

PET_INFO* CHARACTER::GetEquipedPetInfo(int iPetType)
{
	return &(m_PetInfo[iPetType]);
}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM



// MoveCharacter�Լ��� ����� ���� ������ RenderCharacter �Լ��󿡼� ����ϰ��� ���Դϴ�.
#ifdef LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL

// ���� Counting�� �ξ� PostMoveProcess�� Ȱ��ȭ �մϴ�.
void CHARACTER::PostMoveProcess_Active( unsigned int uiLimitCount )
{
	if( m_pPostMoveProcess != NULL )
	{
		delete m_pPostMoveProcess; m_pPostMoveProcess = NULL;
	}

	m_pPostMoveProcess = new ST_POSTMOVE_PROCESS();
	m_pPostMoveProcess->bProcessingPostMoveEvent = false;
	m_pPostMoveProcess->uiProcessingCount_PostMoveEvent = uiLimitCount;
}

// ���� Counting�� ��ȯ �մϴ�.
unsigned int CHARACTER::PostMoveProcess_GetCurProcessCount()
{
	return m_pPostMoveProcess->uiProcessingCount_PostMoveEvent;
}

// ���� PostMoveProcess�� Processing������ ��ȯ �մϴ�.
bool CHARACTER::PostMoveProcess_IsProcessing()
{
	if( m_pPostMoveProcess == NULL)
	{
		return false;
	}
	
	return (0 <= m_pPostMoveProcess->uiProcessingCount_PostMoveEvent);
}

// Tick Process �մϴ�.
bool CHARACTER::PostMoveProcess_Process()
{
	if( m_pPostMoveProcess == NULL )
	{
		return false;
	}
	
	// ��Tick�� �ѹ��� ���� ��ŵ�ϴ�.
	unsigned int uiCurretProcessingCount_ = m_pPostMoveProcess->uiProcessingCount_PostMoveEvent--;

	if( 0 >= uiCurretProcessingCount_)
	{
		delete m_pPostMoveProcess;
		m_pPostMoveProcess = NULL;
		return false;
	}
	
	return true;
}

#endif // LDS_FIX_MODULE_POSTMOVECHARACTER_SKILL_WHEEL
