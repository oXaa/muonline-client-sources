// DummyAttackProtocol.h: interface for the CDummyAttackProtocol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUMMYATTACKPROTOCOL_H__9CB5AB50_D2E6_46AB_8B37_B261286D5FE6__INCLUDED_)
#define AFX_DUMMYATTACKPROTOCOL_H__9CB5AB50_D2E6_46AB_8B37_B261286D5FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_DUMMY_SKILL_PROTOCOL

#include "WSclient.h"

enum
{
	PROTOCOL_TYPE_ATTACK_NORMAL			= 1,
	PROTOCOL_TYPE_ATTACK_SKILL			= 2,
};

CONST int MAX_DUMMY_PROTOCOL_ERROR_COUNT	= 3;


class CDummyAttackProtocol  
{
protected:
	CDummyAttackProtocol();
public:
	virtual ~CDummyAttackProtocol();

	//////////////////////////////////////////////////////////////////////////
	//
	// 1. ���������� �õ尪�� �߱��ϰ� �õ尪�� ������ �����Ѵ�. (�� ������ ������ �����ص� �������)
	// 2. Ŭ���̾�Ʈ�� �õ尪���� ���� ���� ���������� ���� ������ Ȯ���ϰ� �ش� ������ ���� ���������� �����Ѵ�. (GetDummyProtocolNextSeq())
	// 3. ���� ���������� �Ϲ� ���� �������ݰ� ������ ���� �ٸ��� ������.
	// 4. VerifyDummyProtocol�� �ش� ���������� ���� ������������ Ȯ���Ѵ�.
	// 5. Ŭ���̾�Ʈ�� MakeDummyProtocol()�� �������������� ������ �� �ñ⿡ ������ �����Ѵ�.
	//
	// - Ŭ���̾�Ʈ ��� ��� -
	// 1. �������� PMSG_SET_ATTACK_PROTOCOL_DUMMY_VALUE�� ���۵Ǹ� �ش� ���������� dwDummySeedValue���� �����Ѵ�.
	// 2. GetDummyProtocolNextSeq()�Լ��� ���� ���� ���������� ���� ������ �����Ѵ�. ( �Ķ���ʹ� dwDummySeedValue �� )
	// 3. ���� ���������� MakeDummyProtocol()�Լ��� ���� ������ ���� ���������� ���� ���������� header�� ������ 4BYTE�� �Է��Ͽ� ������ �����Ѵ�.
	// 
	//////////////////////////////////////////////////////////////////////////

public:
	static CDummyAttackProtocol* GetInstance();

	// 1. �ʱ�ȭ
	// 1-1. �ʱ�ȭ
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	void	Initialize(DWORD dwDummySeedValue, DWORD dwAttackSerialSeedValue);			// 1. �����κ��� �޴� SeedValue
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	void	Initialize(DWORD dwSeedValue);			// 1. �����κ��� �޴� SeedValue
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL

	// 3. ���� �������� ����
	// 3-1. ���� ���� ���������� ���� ������ �����Ѵ�.
	WORD	GetDummyProtocolNextSeq();

	// 3-4. ���� ���������� �����Ѵ�.
	void	MakeDummyProtocol(LPBYTE lpProtocol);

#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	// 4. ���� �������� �ø��� ����
	// 4-1. ���� �ø��� ������ �ø����� �����Ѵ�.
	BYTE	GetSerial();
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL

	void	AddSkillCount();
	int		GetSkillCount();
	void	InitSkillCount();

private:
	// 2-2. ���� �õ尪�� �����Ѵ�.
#ifndef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL		// #ifndef
	void	GenerateNextSeedValue();
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL

private:
#ifdef KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	DWORD	m_dwDummySeedValue;
	DWORD	m_dwAttackSerialSeedValue;
#else // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	DWORD	m_dwSeedValue;
#endif // KJH_ADD_CREATE_SERIAL_NUM_AT_ATTACK_SKILL
	int		m_iSkillCount;
};

#define g_DummyAttackChecker CDummyAttackProtocol::GetInstance()

#endif // KJH_ADD_DUMMY_SKILL_PROTOCOL

#endif // !defined(AFX_DUMMYATTACKPROTOCOL_H__9CB5AB50_D2E6_46AB_8B37_B261286D5FE6__INCLUDED_)
