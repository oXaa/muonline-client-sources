// HackTest.h: interface for the CHackTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HACKTEST_H__04C83ED2_C91F_491C_BE3F_1B8DDD1EE6B9__INCLUDED_)
#define AFX_HACKTEST_H__04C83ED2_C91F_491C_BE3F_1B8DDD1EE6B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CSK_HACK_TEST


// ���Ͱ� ����ִ°�, �׾��°� �Ǻ��ϴ� �Լ�
bool IsLiveMonster(CHARACTER* pCha);


class CManagedItem 
{
public:
	CManagedItem():m_iRefCount(0) {}
	virtual ~CManagedItem() {}

	void AddRef()
	{
		++m_iRefCount;
	}

	bool DelRef()
	{
		return --m_iRefCount==0;
	}

private:
	int m_iRefCount;

};

template <class IDTYPE>
class CManager
{
public:
	CManager(void) {}

	void clear()
	{
		m_Names.clear();
		m_Items.clear();
	}
	
	virtual IDTYPE add(std::string name) { IDTYPE id; return id; }
	virtual void add(IDTYPE id, std::string name) {}

	virtual void Delete(IDTYPE id)
	{
		if(has(id))
		{
			if (m_Items[id]->DelRef()) 
			{
				CManagedItem *i = m_Items[id];
				DoDelete(id);
				m_Items.erase(m_Items.find(id));
				delete i;
			}
		}
	}

	void DeleteAll()
	{
		for (std::map<IDTYPE, CManagedItem*>::iterator it = m_Items.begin(); it != m_Items.end(); ++it) 
		{
			SAFE_DELETE( it->second );
		}

		clear();
	}

	virtual void DoDelete(IDTYPE id) {}

	bool has(IDTYPE id)
	{
		return (m_Items.find(id) != m_Items.end());
	}

	CManagedItem* get(IDTYPE id)
	{
		CManagedItem* pItem = NULL;

		if(has(id))
			pItem = m_Items[id];

		return pItem;
	}

protected:
	void DoAdd(IDTYPE id, CManagedItem* item)
	{
		item->AddRef();
		m_Items[id] = item;
	}

public:
	std::map<IDTYPE, CManagedItem*> m_Items;
};

class CMonster : public CManagedItem
{
public:
	CMonster();
	virtual ~CMonster();

public:
	short m_iIndex;		// ���� �ε���
	DWORD m_dwTime;		// ���� ���� Ÿ�̸�
};


class CMonsterManager	: public CManager<int>
{	
public:
	CMonsterManager();
	virtual ~CMonsterManager();

	// key������ ���� �߰�
	void Add(int iKey, int iIndex);

	// ����Ʈ���� ���� ���ʹ� �����Ѵ�.
	void DeleteDeadMonster();

	// ����Ʈ ������
	int Size();

	CMonster* GetMonster();

	void Reset();

	void Add(int iIndex);

private:
	int m_iIndex;
	int m_iKey;

public:
	vector<int> m_MonsterIndexList;
};

class HackLog
{
public:
	typedef std::map<int, int> SkillAttackMap;
	
	void Reset();

	// �α׽���
	bool m_bLogStart;

	// ���۽ð�
	DWORD m_dwStartTime;
	// ���ð�
	DWORD m_dwEndTime;
	// �ѽð�
	DWORD m_dwTotalTime;

	// �ѵ�����
	// ReceiveAttackDamage()
	int m_iTotalDamage;
	// �� ������ 
	int m_iTotalShieldDamage;
	// �޺������� ī��Ʈ
	int m_iComboDamageCount;
	// �������� ī��Ʈ
	int m_iDoubleDamageCount;
	// ���������� ī��Ʈ
	int m_iDamageCount;
	// ������ ���ġ
	int m_iAverageDamage;
	// miss ī��Ʈ
	int m_iMissCount;

	// ���� ���� ��
	int m_iDieMonsterCount;

	// ������Ŷ ���� ��
	int m_iSendClientAttackPacket;

	// ��ų���� ī��Ʈ ��
	SkillAttackMap m_SkillAttackCountList;

	// ������ ��� ���õ� ��ų
	WORD m_wCurrentSkill;

	DWORD m_dwTime;
	int m_iKey;
	CHARACTER* m_pMonster;
	int m_iSelectedMonster;
};

class CHackTest  
{
public:
	enum HackType
	{
		HACK_NONE = 0,
		HACK_AUTOATTACK,		// �Ϲ� ����
		HACK_PILLAR_OF_FIRE,	// �ұ��
		HACK_EVILSPIRIT,		// �Ƿ�
		HACK_DABAL,				// �ٹ�
		HACK_SKILL_LOG,			// ��ų�м�
	};

	CHackTest();
	virtual ~CHackTest();
	static CHackTest* GetInstance();
	
public:
	// �� ����� �ƹ���ġ�� �̵��ϴ� ���
	// x, y ��ǥ�� ������ ���ε� �̵� ������
	void MovePos(int x, int y);
	
	// �ʿ� �����ִ� ���� ���� ã�� �������� �̵��ϴ� �Լ�
	void MoveMonster();

	void MoveAuto();
	
	// �ʿ� �����ִ� ������ ���͸� ã�Ƽ� �����ϴ� �Լ�
	void AttackMonster();
	
	// �ʿ� �����ִ� ������ ���͸� ã�� �Լ�
	CHARACTER* FindMonster();
	
	// ����Ʈ �ȿ� ���� �ִ� ��� ���͸� ã�´�.
	void FindAllMonster();

	void PlusAttackSpeed();
	void MinusAttackSpeed();
	
	void StartAuto(int iType);
	void EndAuto();
	
	void Update();
	void UpdateAutoAttack();
	void UpdatePillarOfFire();
	void UpdateEvilSpirit();
	void UpdateDaval();
	void UpdateSkillLog();

	// ��ų�м��Լ�
	void StartSkill();
	void EndSkill();
	void ReceiveDamage(CHARACTER* pCha, OBJECT* pObj, int iSuccess, WORD wDamage, int iDamageType, bool bDoubleEnable, bool bComboEnable, WORD wShieldDamage, int iKey);
	void ReceiveDie(CHARACTER* pCha, OBJECT* pObj, WORD wSkillType, int iKey);
	void AddAttackCount(int iSkill);

public:
	int m_iAttackSpeed;
	
private:
	int m_iHackType;

	DWORD m_dwTime;
	DWORD m_dwAttackTime;
	
	int m_iCount;

	CMonsterManager m_MonsterManager;

	HackLog m_SkillLog;
};

#define g_pHackTest CHackTest::GetInstance()
#endif // CSK_HACK_TEST

#endif // !defined(AFX_HACKTEST_H__04C83ED2_C91F_491C_BE3F_1B8DDD1EE6B9__INCLUDED_)
