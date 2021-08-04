// SummonSystem.h: interface for the CSummonSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUMMONSYSTEM_H__B6F7054C_8D6B_4E3C_94E1_C9A5B1207076__INCLUDED_)
#define AFX_SUMMONSYSTEM_H__B6F7054C_8D6B_4E3C_94E1_C9A5B1207076__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zzzinfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include <map>

class CSummonSystem  
{
public:
	CSummonSystem();
	virtual ~CSummonSystem();

	void MoveEquipEffect(CHARACTER * pCharacter, int iItemType, int iItemLevel,int iItemOption1);		// ��ȯ�� ������ ��� ����Ʈ ó��
	void RemoveEquipEffects(CHARACTER * pCharacter);	// �ش� ĳ������ ��ȯ�� ������ ��� ����Ʈ�� ��� �����Ѵ�
	void RemoveEquipEffect_Summon(CHARACTER * pCharacter);	// ��ȯ�� ������ ���� ��ȯ ���� ȸ�� ����Ʈ ����
	
	BOOL SendRequestSummonSkill(int iSkill, CHARACTER * pCharacter, OBJECT * pObject);	// ��ȯ�� ��ų ��� ���� ����
	void CastSummonSkill(int iSkill, CHARACTER * pCharacter, OBJECT * pObject, int iTargetPos_X, int iTargetPos_Y);	// ��ȯ�� ��ų ����Ʈ ����

	void CreateDamageOfTimeEffect(int iSkill, OBJECT * pObject);	// DOT ����Ʈ ����
	void RemoveDamageOfTimeEffect(int iSkill, OBJECT * pObject);	// DOT ����Ʈ ����
	void RemoveAllDamageOfTimeEffect(OBJECT * pObject);	// DOT ����Ʈ ��� ����
	
protected:
	void CreateEquipEffect_WristRing(CHARACTER * pCharacter, int iItemType, int iItemLevel,int iItemOption1);	// ��ȯ�� ������ ���� �ȸ� ����Ʈ ����
	void RemoveEquipEffect_WristRing(CHARACTER * pCharacter);	// ��ȯ�� ������ ������ �ȸ� ����Ʈ ����
	void CreateEquipEffect_Summon(CHARACTER * pCharacter, int iItemType, int iItemLevel,int iItemOption1);	// ��ȯ�� ������ ���� ��ȯ ���� ȸ�� ����Ʈ ����

	void CreateCastingEffect(vec3_t vPosition, vec3_t vAngle, int iSubType);	// ��ȯ�� ��ų ������ ���� ����Ʈ ����

	void CreateSummonObject(int iSkill, CHARACTER * pCharacter, OBJECT * pObject, float fTargetPos_X, float fTargetPos_Y);	// ��ȯ�� ����
	void SetPlayerSummon(CHARACTER * pCharacter, OBJECT * pObject);
	
protected:
	std::map<SHORT, BYTE> m_EquipEffectRandom;
};

extern CSummonSystem g_SummonSystem;

#endif // !defined(AFX_SUMMONSYSTEM_H__B6F7054C_8D6B_4E3C_94E1_C9A5B1207076__INCLUDED_)
