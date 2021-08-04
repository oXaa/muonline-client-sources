#ifndef _MIX_MGR_H_
#define _MIX_MGR_H_

#pragma once

//////////////////////////////////////////////////////////////////////////////////////
// MIX_RECIPE_ITEM		// �ͽ� ��� ������
// MIX_RECIPE			// �ͽ� ��� (������ ����)
// CMixRecipes			// �ͽ� ����� (������� ����)
// CMixRecipeMgr		// �ͽ� ��ҿ� ���� �ͽ� ����� ���� (������� ����)
// 
// CMixItem				// ����â ������
// CMixItemInventory	// ����â �����۵� ���� (����â �����۵��� ����)
//
// 1. CMixRecipeMgr�� �����Ǹ鼭 mix.bmd�� �ε��Ͽ� ���ձ�(���� ���)�� ���� CMixRecipe�� �����մϴ�.
// 2. CMixRecipe�� MIX_RECIPE��� �����Ǿ� ������ �� MIX_RECIPE�� ������ ���,���(MIX_RECIPE_ITEM) ������ ��� �ֽ��ϴ�.
// 3. zzzMixInventory�� CheckMixInventoryNewCore()���� ���� ���� �κ��丮 ���� �������� CMixItem���� ��ȯ�Ͽ�
// CMixItemInventory�� �����մϴ�.
// 4. CMixItemInventory�� CMixRecipeMgr�� ���� ����â�� �����۰� ���� ����� ���Ͽ� �ùٸ� ������ ã�Ƴ��ϴ�.
// 5. ��ũ��Ʈ���� id�� ������ �����մϴ�. (������ ��ӵ� ��)

namespace SEASON3A
{
	class CMixItem	// ���� ��� ������
	{
	public:
		CMixItem() { Reset(); }
		virtual ~CMixItem() { }
		CMixItem(ITEM * pItem, int iMixValue) { SetItem(pItem, iMixValue); }
		
		void Reset();
		void SetItem(ITEM * pItem, DWORD dwMixValue);	// ITEM ����ü�� ���ϱ� ���� ���·� ��ȯ�ϸ�, ���� ���� �˻縦 �ϴ� �Լ�

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
		bool IsSameItem(const CMixItem& rhs)
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
		bool IsSameItem(CMixItem & rhs)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
		{
			return (m_sType == rhs.m_sType && m_iLevel == rhs.m_iLevel &&
				(m_bCanStack || m_iDurability == rhs.m_iDurability) && m_iOption == rhs.m_iOption &&
				m_dwSpecialItem == rhs.m_dwSpecialItem);
		}
		
		bool operator==(ITEM * rhs)
		{
			return IsSameItem(CMixItem(rhs, 0));
		}

		// ���� ���� �񱳿� ����
		short m_sType;
		int m_iLevel;
		int m_iOption;
		int m_iDurability;
		DWORD m_dwSpecialItem;	// ������Ʈ,380������,��Ʈ������ (_SPECIAL_ITEM_RECIPE_)
		int m_iCount;		// ������ ������ ����
		int m_iTestCount;	// ���� �˻�� ����

		// ���� Ȯ��/���� ���� ����
		BOOL m_bMixLuck;	// ���ɼ�
		BOOL m_bIsEquipment;	// ����ΰ�
		BOOL m_bCanStack;	// ���� �� �ִ� �������ΰ� (���� �� �������� ������ ����ϴ� ������)
		BOOL m_bIsWing;		// �����ΰ�
		BOOL m_bIsUpgradedWing;	// ���׷��̵� �����ΰ�
		BOOL m_bIs3rdUpgradedWing;	// 3�� ���׷��̵� �����ΰ�
		DWORD m_dwMixValue;	// ���ս� ���Ǵ� ����
		BOOL m_bIsCharmItem;	// ����� �����ΰ�
#ifdef PSW_ADD_MIX_CHAOSCHARM
		BOOL m_bIsChaosCharmItem; // ���� �����ΰ�
#endif //PSW_ADD_MIX_CHAOSCHARM
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
		BOOL m_bIsJewelItem;	// ���� �������ΰ� (��,��,ȥ,â,��,��,��,������)
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE

		// ��Ÿ ����
		BOOL m_b380AddedItem;	// 380 �ɼ��� �̹� �߰��� ������ ����
		BOOL m_bFenrirAddedItem;	// �渱 �ɼ� �߰��� �� ������ ����
		WORD m_wHarmonyOption;		// ��ȭ�� ���� �ɼ� (ȯ�� ���� �����)
		WORD m_wHarmonyOptionLevel;	// ��ȭ�� ���� �ɼ� ���� (ȯ�� ���� �����)

#ifdef ADD_SOCKET_MIX
		// ���Ͼ����� ���� (���Ͼ������϶���)
		BYTE m_bySocketCount;					// ���� ���� (0~MAX_SOCKETS), 0: ���� ������ �ƴ�
		BYTE m_bySocketSeedID[MAX_SOCKETS];		// �õ� ������ȣ (0~49), -1: �� ����
		BYTE m_bySocketSphereLv[MAX_SOCKETS];	// ���Ǿ� ���� (1~5)
		// �õ���Ǿ� ������ ���� (�õ彺�Ǿ��϶���)
		BYTE m_bySeedSphereID;					// �õ彺�Ǿ��� �õ� ������ȣ (0~49), -1: �õ彺�Ǿ� �ƴ�
#endif	// ADD_SOCKET_MIX
	};

	class CMixItemInventory	// ���� �κ��丮�� �÷��� ��� ������ ���� Ŭ����
	{
	public:
		CMixItemInventory() { Reset(); }
		virtual ~CMixItemInventory() { Reset(); }
		void Reset() { m_iNumMixItems = 0; }

		int AddItem(ITEM * pItem);
		int GetNumMixItems() { return m_iNumMixItems; }
		CMixItem * GetMixItems() { return m_MixItems; }
		
	protected:
		DWORD EvaluateMixItemValue(ITEM * pItem);

	protected:
		CMixItem m_MixItems[32];
		int m_iNumMixItems;
	};

	enum _SPECIAL_ITEM_RECIPE_
	{
		RCP_SP_EXCELLENT = 1,
		RCP_SP_ADD380ITEM = 2,
		RCP_SP_SETITEM = 4,
		RCP_SP_HARMONY = 8,		// ��ȭ�� ���� ���� ������ ����
#ifdef ADD_SOCKET_MIX
		RCP_SP_SOCKETITEM = 16,
#endif	// ADD_SOCKET_MIX
	};

	typedef struct _MIX_RECIPE_ITEM		// ���� ���: ��ũ��Ʈ(��)�� ����Ǿ����� -> ���� ����� ���� �ҽ� ����
	{
		short m_sTypeMin;
		short m_sTypeMax;
		int m_iLevelMin;
		int m_iLevelMax;
		int m_iOptionMin;
		int m_iOptionMax;
		int m_iDurabilityMin;
		int m_iDurabilityMax;
		int m_iCountMin;
		int m_iCountMax;		// ������ ������ ����
		DWORD m_dwSpecialItem;	// ������Ʈ,380������,��Ʈ������ (_SPECIAL_ITEM_RECIPE_)
	} MIX_RECIPE_ITEM;

	enum _MIX_TYPES_
	{
		MIXTYPE_GOBLIN_NORMAL,		// 0. ��� �Ϲ� ����
		MIXTYPE_GOBLIN_CHAOSITEM,	// 1. ī���� ���� ����������
		MIXTYPE_GOBLIN_ADD380,		// 2. 380������ �ɼ� �߰�
		MIXTYPE_CASTLE_SENIOR,		// 3. ���ο� ���� ����
		MIXTYPE_TRAINER,			// 4. ���û�
		MIXTYPE_OSBOURNE,			// 5. ������ ���ü�
		MIXTYPE_JERRIDON,			// 6. ������ ��ȭ�Ǻ��� ������ ȯ��
		MIXTYPE_ELPIS,				// 7. ���ǽ� ��ȭ�Ǻ���
#ifdef ADD_GLOBAL_MIX_MAR08
		MIXTYPE_CHAOS_CARD,			// 8. �ؿ� ī����ī�� ����
		MIXTYPE_CHERRYBLOSSOM,		// 9. �ؿ� ���ɰ��� ����
#endif	// ADD_GLOBAL_MIX_MAR08
#ifdef ADD_SOCKET_MIX
		MIXTYPE_EXTRACT_SEED,		// 10. �õ� ����
		MIXTYPE_SEED_SPHERE,		// 11. �õ� ���Ǿ� �ռ�
		MIXTYPE_ATTACH_SOCKET,		// 12. ���� ������ ����
		MIXTYPE_DETACH_SOCKET,		// 13. ���� ������ ��ü
#endif	// ADD_SOCKET_MIX
		MAX_MIX_TYPES
	};
	#define MAX_MIX_SOURCES 8	// �ִ� ��� ���� ��
	#define MAX_MIX_NAMES 3		// ���� �̸� �ؽ�Ʈ ���� �� (%s %s %s)
	#define MAX_MIX_DESCRIPTIONS 3	// ���� ������ �� (%s\n%s\n...)
	#define MAX_MIX_RATE_TOKEN 32	// txt���� �о���� Ȯ�� ������ ��ū ��

	enum _MIXRATE_OPS
	{
		// ������
		MRCP_NUMBER = 0,
		MRCP_ADD,	// +
		MRCP_SUB,	// -
		MRCP_MUL,	// *
		MRCP_DIV,	// /
		MRCP_LP,	// (
		MRCP_RP,	// )
		MRCP_INT,	// INT()

		// ��
		MRCP_MAXRATE = 32,	// ��ũ��Ʈ�� �ִ� Ȯ��
		MRCP_ITEM,			// ����â ������ ���� ����
		MRCP_WING,			// ����â ���� ���� ����
		MRCP_EXCELLENT,		// ����â ���� ���� ����
		MRCP_EQUIP,			// ����â ����+�� ���� ����
		MRCP_SET,			// ����â ��Ʈ������ ���� ����
		MRCP_LEVEL1,		// ���� ���� ù��° �������� ���� (1~13)
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
		MRCP_NONJEWELITEM,	// ���������� ������ ����â ������ ���� ���� (��,��,ȥ,â,��,��,��,������)
#endif	/ /YDG_FIX_SOCKETSPHERE_MIXRATE

		// ���� ��
		MRCP_LUCKOPT = 64	// �������� ��� �ɼ� ���ʽ� ���� ������ 25, ������ 0
	};

	typedef struct _MIXRATE_TOKEN
	{
		enum _MIXRATE_OPS op;
		float value;
	} MIXRATE_TOKEN;

	typedef struct _MIX_RECIPE	// ���� ���: ��ũ��Ʈ(��)�� ����Ǿ����� -> ������ ���� ���� ���������
	{
		int m_iMixIndex;	// ���� �Ϸù�ȣ
		int m_iMixID;		// ������ ���� ���� ID
		int m_iMixName[MAX_MIX_NAMES];
		int m_iMixDesc[MAX_MIX_DESCRIPTIONS];
		int m_iMixAdvice[MAX_MIX_DESCRIPTIONS];
		int m_iWidth;
		int m_iHeight;
		int m_iRequiredLevel;
		BYTE m_bRequiredZenType;
		DWORD m_dwRequiredZen;
		int m_iNumRateData;
		MIXRATE_TOKEN m_RateToken[MAX_MIX_RATE_TOKEN];
		int m_iSuccessRate;
		BYTE m_bMixOption;
		BYTE m_bCharmOption;
#ifdef PSW_ADD_MIX_CHAOSCHARM
		BYTE m_bChaosCharmOption;
#endif //PSW_ADD_MIX_CHAOSCHARM
		MIX_RECIPE_ITEM m_MixSources[MAX_MIX_SOURCES];
		int m_iNumMixSoruces;
	} MIX_RECIPE;

	enum _MIX_SOURCE_STATUS { MIX_SOURCE_ERROR, MIX_SOURCE_NO, MIX_SOURCE_PARTIALLY, MIX_SOURCE_YES };

	class CMixRecipes	// ���� ��� ���� Ŭ����
	{
	public:
		CMixRecipes() { Reset(); }
		virtual ~CMixRecipes() { Reset(); }

		void Reset();
		void AddRecipe(MIX_RECIPE * pMixRecipe);
		void ClearCheckRecipeResult();	// ������ �κ� �˻��� �ʱ�ȭ
		int CheckRecipe(int iNumMixItems, CMixItem * pMixItems);	// ������ �κ� ������ ���� ����� ���Ͽ� ��� ��ȯ
		int CheckRecipeSimilarity(int iNumMixItems, CMixItem * pMixItems);	// ������ ���� ���絵 �˻�

		BOOL IsMixSource(ITEM * pItem);	// �� �������� ���� ���� ���� �ִ� �������ΰ�
		MIX_RECIPE * GetCurRecipe();	// ���� ���� ���
		int GetCurMixID();	// ������ ������ ���� ID ���
		BOOL GetCurRecipeName(unicode::t_char * pszNameOut, int iNameLine);	// ���� �̸� ���
		BOOL GetCurRecipeDesc(unicode::t_char * pszDescOut, int iDescLine);	// ���� ���� ���
		MIX_RECIPE * GetMostSimilarRecipe();	// ���� ���� ���
		BOOL GetMostSimilarRecipeName(unicode::t_char * pszNameOut, int iNameLine);	// ���� ���� �̸� ���
		BOOL GetRecipeAdvice(unicode::t_char * pszAdviceOut, int iAdivceLine);	// ���� ������ ���� ���
		int GetSourceName(int iItemNum, unicode::t_char * pszNameOut, int iNumMixItems, CMixItem * pMixItems);	// ���� ���� ��� �̸� ���
		BOOL IsReadyToMix() { return (m_iCurMixIndex > 0); }	// ���� ���� �����ΰ�
		int GetSuccessRate() { return m_iSuccessRate; }	// ������ ���
		DWORD GetReqiredZen() { return m_dwRequiredZen; }	// �䱸�� ���
#ifdef ADD_SOCKET_MIX
		int GetFirstItemSocketCount() { return m_byFirstItemSocketCount; }
		int GetFirstItemSocketSeedID(int iIndex) { if (iIndex >= m_byFirstItemSocketCount) return SOCKET_EMPTY; else return m_byFirstItemSocketSeedID[iIndex]; }
		int GetFirstItemSocketShpereLv(int iIndex) { if (iIndex >= m_byFirstItemSocketCount) return 0; else return m_byFirstItemSocketSphereLv[iIndex]; }
#endif	// ADD_SOCKET_MIX

		void CalcCharmBonusRate(int iNumMixItems, CMixItem * pMixItems);	// ����� ���������� Ȯ�� ���� ���� ���
#ifdef PSW_ADD_MIX_CHAOSCHARM
		void CalcChaosCharmCount(int iNumMixItems, CMixItem * pMixItems);
#endif //PSW_ADD_MIX_CHAOSCHARM

#ifdef LJH_MOD_CANNOT_USE_CHARMITEM_AND_CHAOSCHARMITEM_SIMULTANEOUSLY
		WORD GetTotalChaosCharmCount()	{ return m_wTotalChaosCharmCount; }
		WORD GetTotalCharmCount()		{ return m_wTotalCharmBonus; }
#endif //LJH_MOD_CANNOT_USE_CHARMITEM_AND_CHAOSCHARMITEM_SIMULTANEOUSLY

	protected:
		bool IsOptionItem(MIX_RECIPE_ITEM & rItem) { return (rItem.m_iCountMin == 0); }	// �ɼ�(�ȳ־ �Ǵ�) �������ΰ�
		BOOL CheckRecipeSub(std::vector<MIX_RECIPE *>::iterator iter, int iNumMixItems, CMixItem * pMixItems);
		int CheckRecipeSimilaritySub(std::vector<MIX_RECIPE *>::iterator iter, int iNumMixItems, CMixItem * pMixItems);	// ���絵 ��
		bool CheckItem(MIX_RECIPE_ITEM & rItem, CMixItem & rSource);	// ���� ���������� ��
		void EvaluateMixItems(int iNumMixItems, CMixItem * pMixItems);
		void CalcMixRate(int iNumMixItems, CMixItem * pMixItems);
		void CalcMixReqZen(int iNumMixItems, CMixItem * pMixItems);
		BOOL GetRecipeName(MIX_RECIPE * pRecipe, unicode::t_char * pszNameOut, int iNameLine, BOOL bSimilarRecipe);	// �־��� ���չ��� �̸� ���

		// ���տɼ� ���� �˻��
		BOOL IsChaosItem(CMixItem & rSource);	// ī���������ΰ�
		BOOL IsChaosJewel(CMixItem & rSource);	// ȥ���ΰ�
		BOOL Is380AddedItem(CMixItem & rSource);	// 380 �߰��ɼ��� �̹� ����ִ� �������ΰ�
		BOOL IsFenrirAddedItem(CMixItem & rSource);	// �渱 �߰��ɼ��� �̹� ����ִ� �������ΰ�
		BOOL IsUpgradableItem(CMixItem & rSource);	// ������ ������ �������ΰ�(����+����+����)
		BOOL IsSourceOfRefiningStone(CMixItem & rSource);	// ���ü��� ����ΰ�
		BOOL IsCharmItem(CMixItem & rSource);	// ����� �����ΰ�
#ifdef PSW_ADD_MIX_CHAOSCHARM
		BOOL IsChaosCharmItem(CMixItem & rSource);
#endif //PSW_ADD_MIX_CHAOSCHARM
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
		BOOL IsJewelItem(CMixItem & rSource);	// �����������ΰ� (��,��,ȥ,â,��,��,��,������)
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
#ifdef YDG_FIX_SOCKET_ATTACH_CONDITION
		BOOL IsSourceOfAttachSeedSphereToWeapon(CMixItem & rSource);	// ���⿡ ������ �� �ִ� �õ彺�Ǿ��ΰ�
		BOOL IsSourceOfAttachSeedSphereToArmor(CMixItem & rSource);		// ���� ������ �� �ִ� �õ彺�Ǿ��ΰ�
#endif	// YDG_FIX_SOCKET_ATTACH_CONDITION

		// ������ ���
		float MixrateAddSub();
		float MixrateMulDiv();
		float MixrateFactor();
	protected:
		std::vector<MIX_RECIPE *> m_Recipes;
		int m_iCurMixIndex;
		int m_iMostSimilarMixIndex;

		int m_iSuccessRate;
		DWORD m_dwRequiredZen;

		BOOL m_bFindMixLuckItem;		// ���� �κ��� ��� �������� �ִ°�
		DWORD m_dwTotalItemValue;		// �� ������ ����
		DWORD m_dwExcellentItemValue;	// �� ���� ����
		DWORD m_dwEquipmentItemValue;	// �� ����/�� ����
		DWORD m_dwWingItemValue;		// �� ���� ����
		DWORD m_dwSetItemValue;			// �� ��Ʈ ������ ����
		DWORD m_iFirstItemLevel;		// ù��° ����� ����
		int m_iFirstItemType;			// ù��° ����� Ÿ��(380��)
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
		DWORD m_dwTotalNonJewelItemValue;	// ������ ������ �� ������ ����
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
#ifdef ADD_SOCKET_MIX
		// ù��° ����� ���� ����
		BYTE m_byFirstItemSocketCount;					// ���� ���� (0~MAX_SOCKETS), 0: ���� ������ �ƴ�
		BYTE m_byFirstItemSocketSeedID[MAX_SOCKETS];	// �õ� ������ȣ (0~49), -1: �� ����
		BYTE m_byFirstItemSocketSphereLv[MAX_SOCKETS];	// ���Ǿ� ���� (1~5)
#endif	// ADD_SOCKET_MIX
		WORD m_wTotalCharmBonus;		// �� ����� ���� ���� Ȯ��
#ifdef PSW_ADD_MIX_CHAOSCHARM
		WORD m_wTotalChaosCharmCount;
#endif //PSW_ADD_MIX_CHAOSCHARM

		// ���絵 �˻��� ������ ��� ��½� �κ��丮�� �ش� �������� ������ ���� �ٲ��ֱ� ���� ���� ����
		int m_iMixSourceTest[MAX_MIX_SOURCES];
		int m_iMostSimilarMixSourceTest[MAX_MIX_SOURCES];	// ���� ���չ� ����� ������ ��

		// ������ ����
		int m_iMixRateIter;		// ������ ���� ���� (iter)
		MIXRATE_TOKEN * m_pMixRates;
	};

	class CMixRecipeMgr
	{
	public:
		CMixRecipeMgr():m_iMixType(0),m_bIsMixInit(TRUE)
		{
#ifdef ADD_SOCKET_MIX
			m_iMixSubType = 0;
#endif	// ADD_SOCKET_MIX
			m_btPlusChaosRate = 0;
#ifdef USE_MIXTEST_BMD
			OpenRecipeFile("Data\\Local\\Mixtest.bmd");
#else	// USE_MIXTEST_BMD
			OpenRecipeFile("Data\\Local\\Mix.bmd");
#endif	// USE_MIXTEST_BMD
		}
		virtual ~CMixRecipeMgr() {}

		void SetMixType(int iMixType) { m_iMixType = iMixType; }	// ����â ���� ����-0:�Ϲ�����,1:ī����������,2:380�ɼ��߰�
		int GetMixInventoryType();	// ����â ���� ���-0:�Ϲ�����,1:ī����������,2:380�ɼ��߰�
		int GetMixInventoryEquipmentIndex();	// ���� ����â �ε��� ��� (SendRequestEquipmentItem�� ������ ����)

		void ResetMixItemInventory();
		void AddItemToMixItemInventory(ITEM * pItem);
		void CheckMixInventory();

#ifdef ADD_SOCKET_MIX
		void SetMixSubType(int iMixSubType) { m_iMixSubType = iMixSubType; }
		int GetMixSubType() { return m_iMixSubType; }
#endif	// ADD_SOCKET_MIX

		BOOL IsMixSource(ITEM * pItem)	// �� �������� ���� ���� ���� �ִ� �������ΰ�
		{
			m_MixRecipe[GetMixInventoryType()].CalcCharmBonusRate(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
#ifdef PSW_ADD_MIX_CHAOSCHARM
			m_MixRecipe[GetMixInventoryType()].CalcChaosCharmCount(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
#endif //PSW_ADD_MIX_CHAOSCHARM
			return m_MixRecipe[GetMixInventoryType()].IsMixSource(pItem);
		}
		int CheckRecipe(int iNumMixItems, CMixItem * pMixItems)	// ���� �˻�
		{
			return m_MixRecipe[GetMixInventoryType()].CheckRecipe(iNumMixItems, pMixItems);
		}
		int CheckRecipeSimilarity(int iNumMixItems, CMixItem * pMixItems)	// ���� ���� �˻�
		{
			return m_MixRecipe[GetMixInventoryType()].CheckRecipeSimilarity(iNumMixItems, pMixItems);
		}
		BOOL IsReadyToMix()	// ���� ���� �����ΰ�
		{
			return m_MixRecipe[GetMixInventoryType()].IsReadyToMix();
		}
		MIX_RECIPE * GetCurRecipe()	// ���� ���� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetCurRecipe();
		}
		int GetSuccessRate()	// ������ ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetSuccessRate();
		}
		int GetReqiredZen()	// �䱸�� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetReqiredZen();
		}
		int GetCurMixID()	// ������ ������ ���� ID ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetCurMixID();
		}
		BOOL GetCurRecipeName(unicode::t_char * pszNameOut, int iNameLine)	// ���� �̸� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetCurRecipeName(pszNameOut, iNameLine);
		}
		BOOL GetCurRecipeDesc(unicode::t_char * pszDescOut, int iDescLine)	// ���� ���� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetCurRecipeDesc(pszDescOut, iDescLine);
		}
		MIX_RECIPE * GetMostSimilarRecipe()	// ���� ���� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetMostSimilarRecipe();
		}
		BOOL GetMostSimilarRecipeName(unicode::t_char * pszNameOut, int iNameLine)	// ���� ���� �̸� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetMostSimilarRecipeName(pszNameOut, iNameLine);
		}
		BOOL GetRecipeAdvice(unicode::t_char * pszAdviceOut, int iAdivceLine)	// ���� ������ ���� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetRecipeAdvice(pszAdviceOut, iAdivceLine);
		}
		int GetSourceName(int iItemNum, unicode::t_char * pszNameOut)	// ���� ���� ��� �̸� ���
		{
			return m_MixRecipe[GetMixInventoryType()].GetSourceName(iItemNum, pszNameOut, m_MixItemInventory.GetNumMixItems(),
				m_MixItemInventory.GetMixItems());
		}
		void ClearCheckRecipeResult()	// ���� �˻� ��� �ʱ�ȭ
		{
			m_MixRecipe[GetMixInventoryType()].ClearCheckRecipeResult();
			SetMixType(0);
		}
		BOOL IsMixInit() { return m_bIsMixInit; }

		void SetPlusChaosRate(BYTE btPlusChaosRate) { m_btPlusChaosRate = btPlusChaosRate; }
		BYTE GetPlusChaosRate() { return m_btPlusChaosRate; }
#ifdef ADD_SOCKET_MIX
		int GetFirstItemSocketCount() { return m_MixRecipe[GetMixInventoryType()].GetFirstItemSocketCount(); }
		int GetFirstItemSocketSeedID(int iIndex) { if (iIndex >= GetFirstItemSocketCount()) return SOCKET_EMPTY; else return m_MixRecipe[GetMixInventoryType()].GetFirstItemSocketSeedID(iIndex); }
		int GetFirstItemSocketShpereLv(int iIndex) { if (iIndex >= GetFirstItemSocketCount()) return 0; else return m_MixRecipe[GetMixInventoryType()].GetFirstItemSocketShpereLv(iIndex); }
		int GetSeedSphereID(int iOrder);	// ��� �õ� ���Ǿ��� ID�� ��´�. ���̻� ������SOCKET_EMPTY ��ȯ (SOCKET_EMPTY�� ���ö����� ���� �� �� �ִ�)
#endif	// ADD_SOCKET_MIX
#ifdef LJH_MOD_CANNOT_USE_CHARMITEM_AND_CHAOSCHARMITEM_SIMULTANEOUSLY
		WORD GetTotalChaosCharmCount()
		{ 
			m_MixRecipe[GetMixInventoryType()].CalcChaosCharmCount(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
			return m_MixRecipe[GetMixInventoryType()].GetTotalChaosCharmCount(); 
		}
		WORD GetTotalCharmCount()
		{ 
			m_MixRecipe[GetMixInventoryType()].CalcCharmBonusRate(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
			return m_MixRecipe[GetMixInventoryType()].GetTotalCharmCount(); 
		}
#endif //LJH_MOD_CANNOT_USE_CHARMITEM_AND_CHAOSCHARMITEM_SIMULTANEOUSLY

	protected:
		void OpenRecipeFile(const unicode::t_char * szFileName);	// mix.bmd�� �о���δ�.

	protected:
		CMixRecipes m_MixRecipe[MAX_MIX_TYPES];
		CMixItemInventory m_MixItemInventory;
		int m_iMixType;	// ����â ����-0:�Ϲ�����,1:ī����������,2:380�ɼ��߰�
#ifdef ADD_SOCKET_MIX
		int m_iMixSubType;	// ����â ����Ÿ��(���Ͼ����� ���� ��ȣ)
#endif	// ADD_SOCKET_MIX
		BOOL m_bIsMixInit;	// ���� �ʱ� �����ΰ� (������ �ϳ��� �ø��� ���� ����)
		BYTE m_btPlusChaosRate;	// ũ���̿��� ���� ���������� Ȯ�� ���ʽ� (�����κ��� ����)
	};
}

extern SEASON3A::CMixRecipeMgr g_MixRecipeMgr;

#endif	// _MIX_MGR_H_
