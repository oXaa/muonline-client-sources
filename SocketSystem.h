#if !defined(_SOCKET_SYSTEM_H_)
#define _SOCKET_SYSTEM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SOCKET_SYSTEM

namespace SEASON4A
{
	enum _SOCKET_OPTION_TYPE
	{
		SOT_SOCKET_ITEM_OPTIONS,		// �Ϲ� ���� �ɼ�
		SOT_MIX_SET_BONUS_OPTIONS,		// ���ʽ� ���� �ɼ�
		SOT_EQUIP_SET_BONUS_OPTIONS,	// ��Ʈ �ɼ�
		MAX_SOCKET_OPTION_TYPES
	};
	
	const int MAX_SOCKET_OPTION = 50;
	const int MAX_SOCKET_OPTION_NAME_LENGTH = 64;
	const int MAX_SPHERE_LEVEL = 5;
#ifdef YDG_FIX_SOCKETITEM_SELLPRICE_BUG
	const int MAX_SOCKET_TYPES = 6;
#endif	// YDG_FIX_SOCKETITEM_SELLPRICE_BUG

	enum _SOCKET_OPTION_CATEGORY
	{
		SOC_NULL,
		SOC_IMPROVE_ATTACK,		// ���� ��ȭ
		SOC_IMPROVE_DEFENSE,	// ��� ��ȭ
		SOC_IMPROVE_WEAPON,		// ���� ��ȭ
		SOC_IMPROVE_ARMOR,		// �� ��ȭ
		SOC_IMPROVE_BATTLE,		// ���� ��ȭ
		SOC_IMPROVE_STATUS,		// ���� ��ȭ
		SOC_UNIQUE_OPTION,		// ����ũ �ɼ�
		MAX_SOCKET_OPTION_CATEGORY
	};

	enum _SOCKET_OPTIONS
	{
		SOPT_ATTACK_N_MAGIC_DAMAGE_BONUS_BY_LEVEL = 0,	// "(������)���ݷ�/��������"
		SOPT_ATTACK_SPEED_BONUS,				// "���ݼӵ�����"
		SOPT_ATTACT_N_MAGIC_DAMAGE_MAX_BONUS,	// "�ִ���ݷ�/��������"
		SOPT_ATTACK_N_MAGIC_DAMAGE_MIN_BONUS,	// "�ּҰ��ݷ�/��������"
		SOPT_ATTACK_N_MAGIC_DAMAGE_BONUS,		// "���ݷ�/��������"
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
		SOPT_DECREASE_AG_USE,					// "AG�Ҹ𷮰���"
#else	// YDG_FIX_SOCKET_BALANCE_PATCH
		SOPT_SKILL_DAMAGE_BONUS,				// "��ų���ݷ�����"
		SOPT_ATTACK_RATE_BONUS,					// "���ݼ���������"
		SOPT_PVP_ATTACK_RATE_BONUS,				// "���ΰ��ݼ���������"
		SOPT_MAGIC_POWER_BONUS,					// "��������"
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

		SOPT_DEFENCE_RATE_BONUS = 10,			// "����������"
		SOPT_DEFENCE_BONUS,						// "��������"
		SOPT_SHIELD_DEFENCE_BONUS,				// "���й�������"
		SOPT_DECREASE_DAMAGE,					// "����������"
		SOPT_REFLECT_DAMAGE,					// "�������ݻ�"

		SOPT_MONSTER_DEATH_LIFE_BONUS = 16,		// "���ͻ���û�������"
		SOPT_MONSTER_DEATH_MANA_BONUS,			// "���ͻ���ø�������"
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
		SOPT_SKILL_DAMAGE_BONUS,				// "��ų���ݷ�����"
		SOPT_ATTACK_RATE_BONUS,					// "���ݼ���������"
		SOPT_INCREASE_ITEM_DURABILITY,			// "�����۳�������ȭ"
#else	// YDG_FIX_SOCKET_BALANCE_PATCH
		SOPT_SD_USE_RATE_BONUS,					// "SD���������" -> PvP�� �� ��� SD�� ���̴� ������ �ÿ��ش�
		SOPT_IGNORE_SD_RATE_BONUS,				// "���ݽ�SD����Ȯ�����"
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

		SOPT_LIFE_REGENERATION_BONUS = 21,		// "�����ڵ�ȸ������"
		SOPT_MAX_LIFE_BONUS,					// "�ִ��������"
		SOPT_MAX_MANA_BONUS,					// "�ִ븶������"
		SOPT_MANA_REGENERATION_BONUS,			// "�����ڵ�ȸ������"
		SOPT_MAX_AG_BONUS,						// "�ִ�AG����"
		SOPT_AG_REGENERATION_BONUS,				// "AG������"
#ifndef YDG_FIX_SOCKET_BALANCE_PATCH	// ������ �����ؾ���
		SOPT_MONSTER_DEATH_ZEN_BONUS,			// "���ͻ����������"
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

		SOPT_EXCELLENT_DAMAGE_BONUS = 29,		// "������Ʈ����������"
		SOPT_EXCELLENT_DAMAGE_RATE_BONUS,		// "������Ʈ������Ȯ������"
		SOPT_CRITICAL_DAMAGE_BONUS,				// "ũ��Ƽ�õ���������"
		SOPT_CRITICAL_DAMAGE_RATE_BONUS,		// "ũ��Ƽ�õ�����Ȯ������"

		SOPT_STRENGTH_BONUS = 34,				// "������"
		SOPT_DEXTERITY_BONUS,					// "��ø����"
		SOPT_VITALITY_BONUS,					// "ü������"
		SOPT_ENERGY_BONUS,						// "����������"
		SOPT_REQUIRED_STENGTH_BONUS,			// "�ʿ�������"
		SOPT_REQUIRED_DEXTERITY_BONUS,			// "�ʿ��ø����"

		SOPT_UNIQUE01 = 41,						// "����ũ�ɼ�1" (�̻��)
		SOPT_UNIQUE02,							// "����ũ�ɼ�2" (�̻��)
	};

	enum _SOCKET_BONUS_OPTIONS
	{
		SBOPT_ATTACK_DAMAGE_BONUS = 0,			// "���ݷ� ���"
		SBOPT_SKILL_DAMAGE_BONUS,				// "��ų ���ݷ� ���"
		SBOPT_MAGIC_POWER_BONUS,				// "���ݷ�/���� ���"
		SBOPT_SKILL_DAMAGE_BONUS_2,				// "��ų ���ݷ� ���"
		SBOPT_DEFENCE_BONUS,					// "���� ���"
		SBOPT_MAX_LIFE_BONUS,					// "�ִ� ���� ����"
	};

	typedef struct _SOCKET_OPTION_INFO
	{
		int m_iOptionID;
		int m_iOptionCategory;
		char m_szOptionName[MAX_SOCKET_OPTION_NAME_LENGTH];
		char m_bOptionType;
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
		int m_iOptionValue[5];		// �ɼ� ��ġ �� (���Ǿ� ������)
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
		int m_iOptionValue;
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
		BYTE m_bySocketCheckInfo[6];
	} SOCKET_OPTION_INFO;

// 	typedef struct _SOCKET_OPTION_INFO_UNICODE
// 	{
// 		int m_iOptionID;
// 		int m_iOptionCategory;
// 		wchar_t m_szOptionName[MAX_SOCKET_OPTION_NAME_LENGTH];
// 		wchar_t m_bOptionType;
// #ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
// 		int m_iOptionValue[5];		// �ɼ� ��ġ �� (���Ǿ� ������)
// #else	// YDG_FIX_SCRIPT_LEVEL_VALUE
// 		int m_iOptionValue;
// #endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
// 		BYTE m_bySocketCheckInfo[6];
// 	} SOCKET_OPTION_INFO_UNICODE;

	typedef struct _SOCKET_OPTION_STATUS_BONUS
	{
		int m_iAttackDamageMinBonus;	// �ּ� ���ݷ�
		int m_iAttackDamageMaxBonus;	// �ִ� ���ݷ�
		int m_iAttackRateBonus;			// ���� ������
		int m_iSkillAttackDamageBonus;	// ��ų ���ݷ�
		int m_iAttackSpeedBonus;		// ���ݼӵ�
#ifndef YDG_FIX_SOCKET_BALANCE_PATCH
		int m_iPvPAttackRateBonus;		// ���� ���� ������
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
		int m_iMagicPowerMinBonus;		// �ּ� ����
		int m_iMagicPowerMaxBonus;		// �ִ� ����
#else	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
		int m_iMagicPowerBonus;			// ����
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS

		int m_iDefenceBonus;			// ����
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
		float m_fDefenceRateBonus;		// ������
#else	// YDG_FIX_SOCKET_BALANCE_PATCH
		int m_iDefenceRateBonus;		// �����
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
		int m_iShieldDefenceBonus;		// ���� ����

		int m_iStrengthBonus;			// ��
		int m_iDexterityBonus;			// ��ø
		int m_iVitalityBonus;			// ü��
		int m_iEnergyBonus;				// ������
	} SOCKET_OPTION_STATUS_BONUS;

	// ���� ���� ���� Ŭ���� (���� ������ �ɼ� ��)
	class CSocketItemMgr
	{
	public:
		CSocketItemMgr();
		virtual ~CSocketItemMgr();

		BOOL IsSocketItem(const ITEM* pItem);	// ���� �������ΰ�
		BOOL IsSocketItem(const OBJECT* pObject);	// ���� ������ ������Ʈ�ΰ�
		int GetSeedShpereSeedID(const ITEM* pItem);	// �õ彺�Ǿ��̸� �õ� ID�� ��ȯ�Ѵ�. �õ彺�Ǿ �ƴϸ� SOCKET_EMPTY ��ȯ
		int GetSocketCategory(int iSeedID);		// �õ� ID�� � �Ӽ����� �˷��ش�
		
		// ���� ������ ���� ����
		int AttachToolTipForSocketItem(const ITEM* pItem, int iTextNum);	// ������ ������ ���� �ɼ� ����� �ѷ��ش�.
		int AttachToolTipForSeedSphereItem(const ITEM* pItem, int iTextNum);	// �õ�, ���Ǿ�, �õ彺�Ǿ� ������ ������ �����ش�.

		// ���� ������ ��Ʈ ����
		void CheckSocketSetOption();		// ����� ���� ��Ʈ�� �˻� (��� ��ü ��Ʈ�ɼ�)
		BOOL IsSocketSetOptionEnabled();	// ���� ��Ʈ�ɼ��� �ֳ�
		void RenderToolTipForSocketSetOption(int iPos_x, int iPos_y);	// ���� ��Ʈ �ɼ� ����� �ѷ��ش�.
		
		// ���� �ɼ� �ؽ�Ʈ ����
		void CreateSocketOptionText(char * pszOptionText, int iSeedID, int iSphereLv);

		// ���� ������ ���� ���ʽ� ���
#ifdef KJW_FIX_SOCKET_BONUS_BIT_OPERATION
		__int64 CalcSocketBonusItemValue(const ITEM * pItem, __int64 iOrgGold);
#else // KJW_FIX_SOCKET_BONUS_BIT_OPERATION
		int CalcSocketBonusItemValue(const ITEM * pItem, int iOrgGold);
#endif // KJW_FIX_SOCKET_BONUS_BIT_OPERATION

		// ���Ͼ����� �ɼǰ��� ���Ѵ�
		int GetSocketOptionValue(const ITEM * pItem, int iSocketIndex);

		void CalcSocketStatusBonus();		// ����� �������ͽ� ���ʽ��� �˻� (m_StatusBonus ����)
		SOCKET_OPTION_STATUS_BONUS m_StatusBonus; 

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		void OpenSocketItemScript(const unicode::t_char * szFileName);	// socketitem.bmd�� �о���δ�.
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	protected:
		BOOL IsSocketItem(int iItemType);	// ���� �������ΰ�
#ifndef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		void OpenSocketItemScript(const unicode::t_char * szFileName);	// socketitem.bmd�� �о���δ�.
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
		void CalcSocketOptionValueText(char * pszOptionValueText, int iOptionType, float fOptionValue);	// ���� �ɼ� �ؽ�Ʈ ���
		int CalcSocketOptionValue(int iOptionType, float fOptionValue);	// ���� �ɼ� �� ���
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
		void CalcSocketOptionValueText(char * pszOptionValueText, int iOptionType, float fOptionValue, float fSphereValue);	// ���� �ɼ� �ؽ�Ʈ ���
		int CalcSocketOptionValue(int iOptionType, float fOptionValue, float fSphereValue);	// ���� �ɼ� �� ���
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE

	protected:
		SOCKET_OPTION_INFO m_SocketOptionInfo[MAX_SOCKET_OPTION_TYPES][MAX_SOCKET_OPTION];
		int m_iNumEquitSetBonusOptions;		// �˻��� ������� ��Ʈ�ɼ� ����

		std::deque<DWORD> m_EquipSetBonusList;	// ĳ������ ������� ��Ʈ�ɼ� ID ���
#ifndef YDG_FIX_SCRIPT_LEVEL_VALUE
		float m_fSphereValues[5];
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
	};
}

extern SEASON4A::CSocketItemMgr g_SocketItemMgr;
#endif	// SOCKET_SYSTEM
#endif // !defined(_SOCKET_SYSTEM_H_)
