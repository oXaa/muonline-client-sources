//////////////////////////////////////////////////////////////////////////
//  
//  UISenatus.h
//  
//  ��  �� : ���ο� �������̽�
//  
//  ��  ¥ : 2004�� 11�� 25��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UISENATUS_H__05379221_4D2C_472A_9048_8E9AB0A4367B__INCLUDED_)
#define AFX_UISENATUS_H__05379221_4D2C_472A_9048_8E9AB0A4367B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSenatusInfo
{
private:
	enum NPC_NUMBERS
	{
		GATENPC_NUMBER = 277,
		STATUENPC_NUMBER = 283,
	};
	enum MAX_LEVELS
	{
		GATE_MAX_HP_LEVEL = 3,
		GATE_MAX_DEFENSE_LEVEL = 3,

		STATUE_MAX_HP_LEVEL = 3,
		STATUE_MAX_DEFENSE_LEVEL = 3,
		STATUE_MAX_RECOVER_LEVEL = 3,
	};
	enum LEVEL_VALUES
	{
#ifdef KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		GATELEVEL_HP_0 = 1900000,
		GATELEVEL_HP_1 = 2500000,
		GATELEVEL_HP_2 = 3500000,
		GATELEVEL_HP_3 = 5200000,
#else KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		GATELEVEL_HP_0 = 500000,
		GATELEVEL_HP_1 = 800000,
		GATELEVEL_HP_2 = 1500000,
		GATELEVEL_HP_3 = 3000000,
#endif // KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		GATELEVEL_DEFENSE_0 = 100,
		GATELEVEL_DEFENSE_1 = 180,
		GATELEVEL_DEFENSE_2 = 300,
		GATELEVEL_DEFENSE_3 = 520,

#ifdef KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		STATUELEVEL_HP_0 = 1500000,
		STATUELEVEL_HP_1 = 2200000,
		STATUELEVEL_HP_2 = 3400000,
		STATUELEVEL_HP_3 = 5000000,
#else // KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		STATUELEVEL_HP_0 = 400000,
		STATUELEVEL_HP_1 = 750000,
		STATUELEVEL_HP_2 = 1300000,
		STATUELEVEL_HP_3 = 2500000,
#endif // KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
		STATUELEVEL_DEFENSE_0 = 80,
		STATUELEVEL_DEFENSE_1 = 180,
		STATUELEVEL_DEFENSE_2 = 340,
		STATUELEVEL_DEFENSE_3 = 550,
		STATUELEVEL_RECOVER_0 = 0,
		STATUELEVEL_RECOVER_1 = 1,
		STATUELEVEL_RECOVER_2 = 2,
		STATUELEVEL_RECOVER_3 = 3,
	};
	enum TAX_RATES
	{
		MIN_TAX_RATE = 0,
		MAX_TAX_RATE = 3,
		MAX_NORMAL_TAX_RATE = 3,
	};
	enum NPCUPGRADE_VALUES
	{
		NPCUPGRADE_DEFENSE = 1,
		NPCUPGRADE_RECOVER = 2,
		NPCUPGRADE_HP = 3,
	};

public:
	CSenatusInfo();
	virtual ~CSenatusInfo();
	
	// ��ġ ���
	int GetRepairCost( LPPMSG_NPCDBLIST pInfo );		// ������ ��´�.
	int GetHP( int nType, int nLevel );					// NPC �� ������ �� ��´�.
	int GetHPLevel( LPPMSG_NPCDBLIST pInfo );			// NPC �� ������ ������ ��´�.
	int GetNextAddHP( LPPMSG_NPCDBLIST pInfo );			// NPC �� ���׷��̵�ɽ� �����Ǵ� ������ �� ��´�.
	int GetDefense( int nType, int nLevel );			// NPC �� ������ ��´�.
	int GetDefenseLevel( LPPMSG_NPCDBLIST pInfo );		// NPC �� ���� ������ ��´�.
	int GetNextAddDefense( LPPMSG_NPCDBLIST pInfo );	// NPC �� ���׷��̵�ɽ� �����Ǵ� ���� �� ��´�.
	int GetRecover( int nType, int nLevel );			// NPC �� ȸ������ ��´�.
	int GetRecoverLevel( LPPMSG_NPCDBLIST pInfo );		// NPC �� ȸ���� ������ ��´�.
	int GetNextAddRecover( LPPMSG_NPCDBLIST pInfo );	// NPC �� ���׷��̵�ɽ� �����Ǵ� ȸ���� �� ��´�.

	// ������ ��û ����
	void DoGateRepairAction();
	void DoGateUpgradeHPAction();
	void DoGateUpgradeDefenseAction();
	void DoStatueRepairAction();
	void DoStatueUpgradeHPAction();
	void DoStatueUpgradeDefenseAction();
	void DoStatueUpgradeRecoverAction();
	void DoApplyTaxAction();
	void DoWithdrawAction(DWORD dwMoney);

	// �����κ��� �޾ƿ� ���� ����
	void SetNPCInfo( LPPMSG_NPCDBLIST pInfo );
	LPPMSG_NPCDBLIST GetNPCInfo(int iNpcNumber, int iNpcIndex);
	void SetTaxInfo( LPPMSG_ANS_TAXMONEYINFO pInfo );
	void ChangeTaxInfo( LPPMSG_ANS_TAXRATECHANGE pInfo );
	void ChangeCastleMoney( LPPMSG_ANS_MONEYDRAWOUT pInfo );
	void BuyNewNPC(int iNpcNumber, int iNpcIndex);

	// ���� ���� ����
	int GetCurrGate() { return m_iCurrGate; }
	void SetCurrGate(int iCurrGate) { m_iCurrGate = iCurrGate; }
	int GetCurrStatue() { return m_iCurrStatue; }
	void SetCurrStatue(int iCurrStatue) { m_iCurrStatue = iCurrStatue; }

	PMSG_NPCDBLIST & GetGateInfo(int iIndex) { return m_GateInfo[iIndex]; }
	PMSG_NPCDBLIST & GetStatueInfo(int iIndex) { return m_StatueInfo[iIndex]; }
	PMSG_NPCDBLIST & GetCurrGateInfo() { return m_GateInfo[m_iCurrGate]; }
	PMSG_NPCDBLIST & GetCurrStatueInfo() { return m_StatueInfo[m_iCurrStatue]; }
	
	// ���õ� �ü��� ���׷��̵� ���� ����
	BOOL IsGateRepairable() { return (GetCurrGateInfo().iNpcHp < GetCurrGateInfo().iNpcMaxHp); }
	BOOL IsGateHPUpgradable() { return (GetHPLevel(&GetCurrGateInfo()) < GATE_MAX_HP_LEVEL); }
	BOOL IsGateDefeseUpgradable() { return (GetDefenseLevel(&GetCurrGateInfo()) < GATE_MAX_DEFENSE_LEVEL); }
	
	BOOL IsStatueRepairable() { return (GetCurrStatueInfo().iNpcHp < GetCurrStatueInfo().iNpcMaxHp); }
	BOOL IsStatueHPUpgradable() { return (GetHPLevel(&GetCurrStatueInfo()) < STATUE_MAX_HP_LEVEL); }
	BOOL IsStatueDefeseUpgradable() { return (GetDefenseLevel(&GetCurrStatueInfo()) < STATUE_MAX_DEFENSE_LEVEL); }
#ifdef KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
	BOOL IsStatueRecoverUpgradable() { return (GetRecoverLevel(&GetCurrStatueInfo()) < STATUE_MAX_RECOVER_LEVEL); }
#else // KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE
	BOOL IsStatueRecoverUpgradable() { return (GetDefenseLevel(&GetCurrStatueInfo()) < STATUE_MAX_RECOVER_LEVEL); }
#endif // KJH_FIX_WOPS_K25856_UPGRADE_WARFARE_DEFENCE_GATE_AND_STONESTATUE

	// ���� ����
	int GetChaosTaxRate() { return m_iChaosTaxRate; }
	void PlusChaosTaxRate(int iValue);
	int GetNormalTaxRate() { return m_iNormalTaxRate; }
	void PlusNormalTaxRate(int iValue);
	int GetRealTaxRateChaos() { return m_iRealTaxRateChaos; }
	int GetRealTaxRateStore() { return m_iRealTaxRateStore; }
	__int64 GetCastleMoney() { return m_i64CastleMoney; }
	void RollbackTaxRates();

	// ��Ÿ ���� ���
	int GetMaxHPLevel() { return STATUE_MAX_HP_LEVEL; }
	int GetMaxDefenseLevel() { return STATUE_MAX_DEFENSE_LEVEL; }
	int GetMaxRecoverLevel() { return STATUE_MAX_RECOVER_LEVEL; }

	BOOL IsGate(LPPMSG_NPCDBLIST pInfo) { return (pInfo->iNpcNumber == GATENPC_NUMBER); }
	BOOL IsStatue(LPPMSG_NPCDBLIST pInfo) { return (pInfo->iNpcNumber == STATUENPC_NUMBER); }

protected:
	int m_iCurrGate;
	int m_iCurrStatue;
	PMSG_NPCDBLIST m_GateInfo[6];
	PMSG_NPCDBLIST m_StatueInfo[4];

	int m_iChaosTaxRate;			// ������ ���� - ī����
	int m_iNormalTaxRate;			// ������ ���� - ����
	int m_iRealTaxRateChaos;		// ���� ���� ���� - ī��������
	int m_iRealTaxRateStore;		// ���� ���� ���� - ����
	__int64 m_i64CastleMoney;		// ���� ���� ��
};

extern CSenatusInfo g_SenatusInfo;

#endif // !defined(AFX_UISENATUS_H__05379221_4D2C_472A_9048_8E9AB0A4367B__INCLUDED_)
