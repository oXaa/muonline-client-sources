#include "stdafx.h"
#include "_GlobalFunctions.h"

#ifdef LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL
#include "GMEmpireGuardian1.h"
#endif // LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL

#ifdef CSK_DEBUG_RENDER_BOUNDINGBOX
bool g_bRenderBoundingBox = false; 
#endif // CSK_DEBUG_RENDER_BOUNDINGBOX

BuffStateSystemPtr			g_BuffSystem;

BuffStateSystem& TheBuffStateSystem() 
{
	assert( g_BuffSystem ); 
	return *g_BuffSystem;
}

BuffScriptLoader& TheBuffInfo() {
	return TheBuffStateSystem().GetBuffInfo();
}

BuffTimeControl& TheBuffTimeControl() {
	return TheBuffStateSystem().GetBuffTimeControl();
}

BuffStateValueControl& TheBuffStateValueControl() {
	return TheBuffStateSystem().GetBuffStateValueControl();
}

#ifdef NEW_USER_INTERFACE_FUNCTIONS

ShellPtr		g_shell;

Shell& TheShell()
{	
	assert( g_shell );
	return *g_shell;
}

BuildSystem& TheBuildSystem()
{
	return TheShell().GetBuildSystem();
}

ClientInfoBuilder& TheClientInfoBuilder()
{
	return TheBuildSystem().GetClientInfoBuilder();
}

GameInfoBuilder& TheGameInfoBuilder()
{
	return TheBuildSystem().GetGameInfoBuilder();
}

ServerProxySystem& TheSerProxySystem()
{
	return TheShell().GetServerProxySystem();
}

InputProxy&	TheInputProxy()
{
	return TheSerProxySystem().GetInputProxy();
}

input::InputSystem& TheInputSystem()
{
	return TheShell().GetInputSystem();
}

ui::UISystem& TheUISystem()
{
	return TheShell().GetUISystem();
}

GameServerProxy& TheGameServerProxy()
{
	return TheSerProxySystem().GetGameServerProxy();
}

ShopServerProxy& TheShopServerProxy()
{
	return TheSerProxySystem().GetShopServerProxy();
}

ClientSystem& TheClientSystem()
{
	return TheShell().GetClientSystem();
}

#endif //NEW_USER_INTERFACE_FUNCTIONS

#ifdef PSW_ADD_MAPSYSTEM



#endif //PSW_ADD_MAPSYSTEM

#ifdef PBG_FIX_SKILL_DEMENDCONDITION
namespace SKILLCONDITION
{
	//��ų�� ���ݿ䱸���� ĳ������ ���ݷ��� ���ϴ� �Լ�.
	BOOL skillVScharactorCheck( const DemendConditionInfo& basicInfo, const DemendConditionInfo& heroInfo )
	{
		//��ũ��Ʈ���ϳ��� ������������ ó���Ѵ�.
		if( basicInfo <= heroInfo )
		{
			//ĳ���� ���ݷ��� ��ų�� ���ݿ䱸������ ���ٸ�.
			return true;
		}
		return false;
	}
	
	BOOL DemendConditionCheckSkill(WORD SkillType)
	{
		if( SkillType >= MAX_SKILLS ) {
			assert( 0 );
			return false;
		}

		// ������ȣ�� ���� �����̵� �迭 ��ų�� ��� �����ϵ��� �մϴ�.
#ifdef LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL
		if( (true == IsEmpireGuardian()) && 
			(SkillType == AT_SKILL_TELEPORT_B || SkillType == AT_SKILL_TELEPORT) )
		{
			return false;
		}
#endif // LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL
		
		//������ �䱸ġ(��ũ��Ʈ���� 0���� ���°͵�)�� ���ٸ� �׳� �����Ѵ�.
 		if(SkillAttribute[SkillType].Energy == 0)
 		{
 			return true;
 		}

		// ������ ��ų ��ȭ�� ��� ��ȭ ������ ��ų�� ��ġ�� �״�� �����Ѵ�. - 
#ifdef KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL
		SkillType = MasterSkillToBaseSkillIndex(SkillType);
#else // KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL
#ifdef LDS_FIX_MASTERSKILLKEY_DISABLE_OVER_LIMIT_MAGICIAN		
		if(SkillType >= AT_SKILL_SOUL_UP &&				// �ҿ� �ٸ��� ��ȭ
			SkillType <= AT_SKILL_SOUL_UP + 5)
		{
			SkillType = AT_SKILL_WIZARDDEFENSE;
		}
		else if(SkillType >= AT_SKILL_HELL_FIRE_UP &&		// �����̾� ��ȭ
			SkillType <= AT_SKILL_HELL_FIRE_UP + 5)
		{
			SkillType = AT_SKILL_HELL;
		}
		else if(SkillType >= AT_SKILL_EVIL_SPIRIT_UP &&	// �Ƿ� ��ȭ (�渶����)
			SkillType <= AT_SKILL_EVIL_SPIRIT_UP + 5)
		{
			SkillType = AT_SKILL_EVIL;
		}
		else if(SkillType >= AT_SKILL_ICE_UP &&			// ���� ���̽� ��ȭ 
			SkillType <= AT_SKILL_ICE_UP + 5)
		{
			SkillType = AT_SKILL_BLAST_FREEZE;
		}
#endif // LDS_FIX_MASTERSKILLKEY_DISABLE_OVER_LIMIT_MAGICIAN
#endif // KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL


		bool result = true;	
		
		DemendConditionInfo BasicCharacterInfo;
		
		
		BasicCharacterInfo.SkillLevel     = SkillAttribute[SkillType].Level;
		BasicCharacterInfo.SkillStrength  = SkillAttribute[SkillType].Strength;
		BasicCharacterInfo.SkillDexterity = SkillAttribute[SkillType].Dexterity;
		BasicCharacterInfo.SkillVitality  = 0;
		//�������� ���� �䱸ġ ������.
		BasicCharacterInfo.SkillEnergy = (20 + ( SkillAttribute[SkillType].Energy * SkillAttribute[SkillType].Level ) * 0.04);
		BasicCharacterInfo.SkillCharisma = SkillAttribute[SkillType].Charisma;
		
		DemendConditionInfo HeroCharacterInfo;
		
		//ĳ������ ���� ������ ���� ���´�. ĳ���� ����+ ���� ����������� �������� ���Ѵ�.
		HeroCharacterInfo.SkillLevel     = CharacterMachine->Character.Level; 
		HeroCharacterInfo.SkillStrength  = CharacterMachine->Character.Strength + CharacterMachine->Character.AddStrength;
		HeroCharacterInfo.SkillDexterity = CharacterMachine->Character.Dexterity + CharacterMachine->Character.AddDexterity; 
		HeroCharacterInfo.SkillVitality  = CharacterMachine->Character.Vitality + CharacterMachine->Character.AddVitality; 
		HeroCharacterInfo.SkillEnergy    = CharacterMachine->Character.Energy + CharacterMachine->Character.AddEnergy; 
		HeroCharacterInfo.SkillCharisma  = CharacterMachine->Character.Charisma + CharacterMachine->Character.AddCharisma;
		
		result = skillVScharactorCheck( BasicCharacterInfo, HeroCharacterInfo );

		return result;	
	}
};
#endif //PBG_FIX_SKILL_DEMENDCONDITION

#if defined PBG_ADD_MU_LOGO || defined LJH_MOD_TO_USE_ISBLUEMUSERVER_FUNC
// ���� �ΰ� ���� ��缷 
//(�ҽ� �и��۾����� ���������� ��缷�ΰ� ���θ� Ȯ��) 
// ���� �۷ι������� ��� �� �������ݷ� ���� �Ұ��
namespace BLUE_MU
{
	bool g_bIsBlue_MU_Server = false;

	// ���¼������� ��Ȯ���� �ʿ��� ���
	BOOL IsBlueMuServer()
	{
#ifdef _BLUE_SERVER
		g_bIsBlue_MU_Server = true;
#endif //_BLUE_SERVER
		return g_bIsBlue_MU_Server;
	}
};
#endif //defined PBG_ADD_MU_LOGO || defined LJH_MOD_TO_USE_ISBLUEMUSERVER_FUNC


#ifdef KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL
int MasterSkillToBaseSkillIndex(int iMasterSkillIndex)
{
	int iBaseSkillIndex = 0;
	switch( iMasterSkillIndex )
	{	
	case AT_SKILL_EVIL_SPIRIT_UP:
	case AT_SKILL_EVIL_SPIRIT_UP+1:
	case AT_SKILL_EVIL_SPIRIT_UP+2:
	case AT_SKILL_EVIL_SPIRIT_UP+3:
	case AT_SKILL_EVIL_SPIRIT_UP+4:
	case AT_SKILL_EVIL_SPIRIT_UP_M:
	case AT_SKILL_EVIL_SPIRIT_UP_M+1:
	case AT_SKILL_EVIL_SPIRIT_UP_M+2:
	case AT_SKILL_EVIL_SPIRIT_UP_M+3:
	case AT_SKILL_EVIL_SPIRIT_UP_M+4:
		{
			iBaseSkillIndex = AT_SKILL_EVIL;			// �Ƿ�
		}
		break;
	case AT_SKILL_SOUL_UP:
	case AT_SKILL_SOUL_UP+1:
	case AT_SKILL_SOUL_UP+2:
	case AT_SKILL_SOUL_UP+3:
	case AT_SKILL_SOUL_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_WIZARDDEFENSE;	// �ҿ�ٸ���
		}
		break;	
	case AT_SKILL_HELL_FIRE_UP:
	case AT_SKILL_HELL_FIRE_UP+1:
	case AT_SKILL_HELL_FIRE_UP+2:
	case AT_SKILL_HELL_FIRE_UP+3:
	case AT_SKILL_HELL_FIRE_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_BLAST_HELL;		// �����Ʈ
		}
		break;	
	case AT_SKILL_ICE_UP:
	case AT_SKILL_ICE_UP+1:
	case AT_SKILL_ICE_UP+2:
	case AT_SKILL_ICE_UP+3:
	case AT_SKILL_ICE_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_BLAST_FREEZE;	// ������̽�
		}
		break;
	case AT_SKILL_TORNADO_SWORDA_UP:
	case AT_SKILL_TORNADO_SWORDA_UP+1:
	case AT_SKILL_TORNADO_SWORDA_UP+2:
	case AT_SKILL_TORNADO_SWORDA_UP+3:
	case AT_SKILL_TORNADO_SWORDA_UP+4:
	case AT_SKILL_TORNADO_SWORDB_UP:
	case AT_SKILL_TORNADO_SWORDB_UP+1:
	case AT_SKILL_TORNADO_SWORDB_UP+2:
	case AT_SKILL_TORNADO_SWORDB_UP+3:
	case AT_SKILL_TORNADO_SWORDB_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_WHEEL;			// ȸ��������
		}
		break;
	case AT_SKILL_BLOW_UP:
	case AT_SKILL_BLOW_UP+1:
	case AT_SKILL_BLOW_UP+2:
	case AT_SKILL_BLOW_UP+3:
	case AT_SKILL_BLOW_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ONETOONE;		// ��ο����
		}
		break;	
	case AT_SKILL_ANGER_SWORD_UP:
	case AT_SKILL_ANGER_SWORD_UP+1:
	case AT_SKILL_ANGER_SWORD_UP+2:
	case AT_SKILL_ANGER_SWORD_UP+3:
	case AT_SKILL_ANGER_SWORD_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_FURY_STRIKE;		// �г����ϰ�
		}
		break;
	case AT_SKILL_LIFE_UP:
	case AT_SKILL_LIFE_UP+1:
	case AT_SKILL_LIFE_UP+2:
	case AT_SKILL_LIFE_UP+3:
	case AT_SKILL_LIFE_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_VITALITY;		// ����������
		}
		break;
	case AT_SKILL_HEAL_UP:
	case AT_SKILL_HEAL_UP+1:
	case AT_SKILL_HEAL_UP+2:
	case AT_SKILL_HEAL_UP+3:
	case AT_SKILL_HEAL_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_HEALING;			// ġ��
		}
		break;
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_DEFENSE;			// ��������
		}
		break;	
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
		{	
			iBaseSkillIndex = AT_SKILL_ATTACK;			// ���ݷ�����
		}
		break;
	case AT_SKILL_MANY_ARROW_UP:
	case AT_SKILL_MANY_ARROW_UP+1:
	case AT_SKILL_MANY_ARROW_UP+2:
	case AT_SKILL_MANY_ARROW_UP+3:
	case AT_SKILL_MANY_ARROW_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_CROSSBOW;		// �ٹ�
		}
		break;
	case AT_SKILL_BLOOD_ATT_UP:
	case AT_SKILL_BLOOD_ATT_UP+1:
	case AT_SKILL_BLOOD_ATT_UP+2:
	case AT_SKILL_BLOOD_ATT_UP+3:
	case AT_SKILL_BLOOD_ATT_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_REDUCEDEFENSE;	// �������
		}
		break;
	case AT_SKILL_POWER_SLASH_UP:
	case AT_SKILL_POWER_SLASH_UP+1:
	case AT_SKILL_POWER_SLASH_UP+2:
	case AT_SKILL_POWER_SLASH_UP+3:
	case AT_SKILL_POWER_SLASH_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ICE_BLADE;		// �Ŀ�������
		}
		break;	
	case AT_SKILL_BLAST_UP:
	case AT_SKILL_BLAST_UP+1:
	case AT_SKILL_BLAST_UP+2:
	case AT_SKILL_BLAST_UP+3:
	case AT_SKILL_BLAST_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_BLAST;			// ����Ʈ
		}
		break;
	case AT_SKILL_ASHAKE_UP:
	case AT_SKILL_ASHAKE_UP+1:
	case AT_SKILL_ASHAKE_UP+2:
	case AT_SKILL_ASHAKE_UP+3:
	case AT_SKILL_ASHAKE_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_DARK_HORSE;		// �����ũ
		}
		break;
	case AT_SKILL_FIRE_BUST_UP:
	case AT_SKILL_FIRE_BUST_UP+1:
	case AT_SKILL_FIRE_BUST_UP+2:
	case AT_SKILL_FIRE_BUST_UP+3:
	case AT_SKILL_FIRE_BUST_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_LONGPIER_ATTACK;		// ���̾����Ʈ
		}
		break;
	case AT_SKILL_FIRE_SCREAM_UP:
	case AT_SKILL_FIRE_SCREAM_UP+1:
	case AT_SKILL_FIRE_SCREAM_UP+2:
	case AT_SKILL_FIRE_SCREAM_UP+3:
	case AT_SKILL_FIRE_SCREAM_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_DARK_SCREAM;			// ���̾ũ��
		}
		break;	
#ifdef PJH_ADD_MASTERSKILL
	case AT_SKILL_ALICE_SLEEP_UP:
	case AT_SKILL_ALICE_SLEEP_UP+1:
	case AT_SKILL_ALICE_SLEEP_UP+2:
	case AT_SKILL_ALICE_SLEEP_UP+3:
	case AT_SKILL_ALICE_SLEEP_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ALICE_SLEEP;			// ����
		}
		break;
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP:
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP+1:
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP+2:
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP+3:
	case AT_SKILL_ALICE_CHAINLIGHTNING_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ALICE_CHAINLIGHTNING;	// ü�ζ���Ʈ��
		}
		break;
	case AT_SKILL_LIGHTNING_SHOCK_UP:
	case AT_SKILL_LIGHTNING_SHOCK_UP+1:
	case AT_SKILL_LIGHTNING_SHOCK_UP+2:
	case AT_SKILL_LIGHTNING_SHOCK_UP+3:
	case AT_SKILL_LIGHTNING_SHOCK_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ALICE_LIGHTNINGORB;		// ����Ʈ�׿���(��ũ)
		}
		break;
	case AT_SKILL_ALICE_DRAINLIFE_UP:
	case AT_SKILL_ALICE_DRAINLIFE_UP+1:
	case AT_SKILL_ALICE_DRAINLIFE_UP+2:
	case AT_SKILL_ALICE_DRAINLIFE_UP+3:
	case AT_SKILL_ALICE_DRAINLIFE_UP+4:
		{
			iBaseSkillIndex = AT_SKILL_ALICE_DRAINLIFE;			// �巹�� ������
		}
		break;
#endif // PJH_ADD_MASTERSKILL
	default:
		{
			iBaseSkillIndex = iMasterSkillIndex;
		}
	}

	return iBaseSkillIndex;
}
#endif // KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL
