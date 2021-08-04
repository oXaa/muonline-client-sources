// Slotlimit.cpp: implementation of the CSlotlimit class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#ifdef PBG_ADD_CHARACTERSLOT
#include "Slotlimit.h"
#include "ZzzEffect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSlotlimit::CSlotlimit()
{
	Init();
}

CSlotlimit::~CSlotlimit()
{

}

CSlotlimit* CSlotlimit::GetInstance()
{
	static CSlotlimit sInstance;
	return &sInstance;
}

void CSlotlimit::Init()
{
	for(int i=0; i<SLOTCNT_MAX; ++i)
		m_bSlotEnable[i]=false;

	memset(m_vPos, 0, sizeof(vec3_t)*SLOTCNT_MAX);

	m_nCharacterCnt=0;
}

void CSlotlimit::SetCharacterCnt(int _Value)
{
	// ĳ���Ͱ� �����ɼ� �ִ� ����
	m_nCharacterCnt = _Value;
}

int CSlotlimit::GetCharacterCnt()
{
	return m_nCharacterCnt;
}

void CSlotlimit::SetSlotEnable(int _Value)
{
	// �����ġ�� �Ǿ��� ��� Ȱ��ȭ����
	m_bSlotEnable[_Value] = true;
}

BOOL CSlotlimit::GetIsSlotEnable(int _Index)
{
	return m_bSlotEnable[_Index];
}

int CSlotlimit::GetDisableSlot()
{
	return (CHARCNT_MAX-m_nCharacterCnt);
}

void CSlotlimit::SetSlotPosition()
{
	// ���� �ܿ� �������ݷ� Ȯ������
	// ���� �ܿ� ����
	if(!BLUE_MU::IsBlueMuServer())
		return;

	if(!GetDisableSlot())
		return;

	for(int i=0; i<GetDisableSlot(); ++i)
	{
		// �⺻ ���� ī��Ʈ�� 3�̶� �ִ� 0,1 �� ȣ�Ⱑ��
		// �� �������� 0��~4��
		switch(i)
		{
		case 0: m_vPos[i][0] = POS_FIRST_X; m_vPos[i][1] = POS_FIRST_Y; m_vPos[i][2] = POS_FIRST_ANGLE; break;
		case 1: m_vPos[i][0] = POS_SECOND_X; m_vPos[i][1] = POS_SECOND_Y; m_vPos[i][2] = POS_SECOND_ANGLE; break;
		case 2: m_vPos[i][0] = POS_THIRD_X; m_vPos[i][1] = POS_THIRD_Y; m_vPos[i][2] = POS_THIRD_ANGLE; break;
		case 3: m_vPos[i][0] = POS_FOURTH_X; m_vPos[i][1] = POS_FOURTH_Y; m_vPos[i][2] = POS_FOURTH_ANGLE; break;
		case 4: m_vPos[i][0] = POS_FIFTH_X; m_vPos[i][1] = POS_FIFTH_Y; m_vPos[i][2] = POS_FIFTH_ANGLE; break;
		}
		SetSlotEnable(i);
	}
}

void CSlotlimit::CreateSlotLock()
{
	// ���� �ܿ� �������ݷ� Ȯ������
	// ���� �ܿ� ����
	if(!BLUE_MU::IsBlueMuServer())
		return;

	for(int i=0; i<SLOTCNT_MAX; ++i)
	{
		if(GetIsSlotEnable(i))
		{
			vec3_t vLight = {1.0f,1.0f,1.0f};
			vec3_t vAngle = {0.0f,0.0f,m_vPos[i][2]};
			CreateEffect(MODEL_SLOT_LOCK, m_vPos[i], vAngle, vLight, i);
		}
	}
}
#endif //PBG_ADD_CHARACTERSLOT