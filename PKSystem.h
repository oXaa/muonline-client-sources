// PKSystem.h: interface for the CPKSystem class.
//
// ȥ������ȭ ���������� PK �ý���
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PKSYSTEM_H__646E4968_61BD_45E8_8648_CC6C6B5CAA31__INCLUDED_)
#define AFX_PKSYSTEM_H__646E4968_61BD_45E8_8648_CC6C6B5CAA31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP

class CPKSystem  
{
public:
	CPKSystem();
	virtual ~CPKSystem();
	
	void Init();
	void Destroy();	
	static CPKSystem* GetInstance();

	// �䱸���� ����ϱ� (��踦 �����Ұ��ΰ�)
	int GetReqZen(const int& _iZen, int _iValue = 10);
	// ���� ���¸� Ȯ���Ѵ�(�⺻ ������1�ܰ躸�� �̻��ΰ�)
	bool IsPKState(int _iPKState = PVP_MURDERER1, int _iCharacterPK = 0);
	const bool& GetPKState() const;
	// �̵� �Ұ� ��������
	void SetMoveBuffState(const bool& _bIsBuff);
	const bool& GetMoveBuffState() const;
	// �̵�â ��밡�� �����ΰ�?
	bool GetCanDoMoveCommand();
	// Hero�� PK����
	void SetHeroPKState(const BYTE& _byHeroPK);
	const BYTE& GetHeroPKState() const;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER 
	// �������� ���� player�� ���� �ִ� ��Ƽ���� pk���� �� ���� ���� �� ����
	void SetHeroPartyPKState(const BYTE& _byHeroPartyPK);
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER

private:
	// eDeBuff_MoveCommandWin��������
	bool m_bIsMoveBuff;
	// ȥ������ȭ���������� PK�䱸���°�
	bool m_bIsPKState;
	//�� Hero->pk����
	BYTE m_HeroPKState;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER 
	// ���� Hero->PKPartyLevel(player�� ���� �ִ� ��Ƽ���� pk���� �� ���� ���� ��)
	BYTE m_HeroPartyPKState;
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
};

inline const bool& CPKSystem::GetPKState() const
{
	return m_bIsPKState; 
}

inline const bool& CPKSystem::GetMoveBuffState() const
{
	return m_bIsMoveBuff; 
}

inline const BYTE& CPKSystem::GetHeroPKState() const
{
	return m_HeroPKState; 
}

#define g_PKSystem	CPKSystem::GetInstance()

#endif //PBG_ADD_PKSYSTEM_INGAMESHOP
#endif // !defined(AFX_PKSYSTEM_H__646E4968_61BD_45E8_8648_CC6C6B5CAA31__INCLUDED_)
