// PKSystem.cpp: implementation of the CPKSystem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#ifdef PBG_ADD_PKSYSTEM_INGAMESHOP
#include "PKSystem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPKSystem::CPKSystem()
{
	Init();
}
//////////////////////////////////////////////////////////////////////
CPKSystem::~CPKSystem()
{
	Destroy();
}
//////////////////////////////////////////////////////////////////////
CPKSystem* CPKSystem::GetInstance()
{
	static CPKSystem sInstance;
	return &sInstance;
}
//////////////////////////////////////////////////////////////////////
void CPKSystem::Init()
{
	m_bIsPKState = false;
	m_bIsMoveBuff = false;
	m_HeroPKState = PVP_NEUTRAL;
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
	m_HeroPartyPKState = m_HeroPKState;
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
}
//////////////////////////////////////////////////////////////////////
void CPKSystem::Destroy()
{
	//n/a
}
//////////////////////////////////////////////////////////////////////
int CPKSystem::GetReqZen(const int& _iZen, int _iValue)
{
	// ��� �� ������ �ƴϸ� ��� �ʿ����
	if(!BLUE_MU::IsBlueMuServer())
		return _iZen;

	return _iZen*_iValue;
}
//////////////////////////////////////////////////////////////////////
bool CPKSystem::IsPKState(int _iPKState, int _iCharacterPK)
{
	// ���� ������ �ƴϸ� ��� �ʿ����
	if(!BLUE_MU::IsBlueMuServer())
		return false;
	// Ÿ������ pk����
	if(!_iCharacterPK)
#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
		_iCharacterPK = max(m_HeroPKState, m_HeroPartyPKState);
#else  //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
		_iCharacterPK = m_HeroPKState;
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
		
	if(_iCharacterPK >= _iPKState)
		m_bIsPKState = true;
	else 
		m_bIsPKState = false;


	return m_bIsPKState;
}
//////////////////////////////////////////////////////////////////////
void CPKSystem::SetMoveBuffState(const bool& _bIsBuff)
{
	// ������ �ɷ��ִ� ����
	m_bIsMoveBuff = _bIsBuff;
}
//////////////////////////////////////////////////////////////////////
bool CPKSystem::GetCanDoMoveCommand()
{
	// ��� �� ������ �ƴҰ�� �Ǵܴ��
	if(!BLUE_MU::IsBlueMuServer())
		return (m_HeroPKState<PVP_MURDERER1);

	IsPKState();
	// ȥ������ȭ �����ϰ�� �Ǵܴ��
	// pk�����϶� ������ �޾��� ��츸 �Ǵ�(false)�̵� �Ұ�
	// �׿� ���� ���´� �����Ѵ�(true)
	//*5�� ���� �̵���ɾ�(â) ��� �Ұ� �г�Ƽ ���� ����
	//- ������ ��� �ܰ迡�� pk�� �ؼ� ������1�ܰ谡 �� ��� ���������� '�̵��Ұ� ����'(������ �� �� ����)�� 
	//�ο� �ް� �Ǿ� ���ӽð�(5��) ���� �̵���ɾ�(â)�� ����� �� �����ϴ�.
	//- ������ 1�ܰ迡�� ������ 2�ܰ�� ����� �� '�̵��Ұ� ����'�� �ٽ� �ο� �ް� �˴ϴ�.
	//- ������ 2�ܰ迡�� PK�� �� ������ '�̵��Ұ� ����'�� �ο� �ް� �˴ϴ�.
	//- '�̵��Ұ� ����'�� ������ ����� ��ȭ�� ������� ���ӵ˴ϴ�.
	return !(m_bIsPKState&m_bIsMoveBuff);
}
//////////////////////////////////////////////////////////////////////
void CPKSystem::SetHeroPKState(const BYTE& _byHeroPK)
{
	m_HeroPKState = _byHeroPK;
}

#ifdef LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER 
void CPKSystem::SetHeroPartyPKState(const BYTE& _byHeroPartyPK)
{
	m_HeroPartyPKState = _byHeroPartyPK;
}
#endif //LJH_ADD_MORE_ZEN_FOR_ONE_HAVING_A_PARTY_WITH_MURDERER
#endif //PBG_ADD_PKSYSTEM_INGAMESHOP