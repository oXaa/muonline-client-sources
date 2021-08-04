// GMEmpireGuardian4.h: interface for the GMEmpireGuardian4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMEMPIREGUARDIAN4_H__C0F94320_4136_40DD_9931_BDD826E02987__INCLUDED_)
#define AFX_GMEMPIREGUARDIAN4_H__C0F94320_4136_40DD_9931_BDD826E02987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LDS_ADD_MAP_EMPIREGUARDIAN4

#include "w_BaseMap.h"

BoostSmartPointer( GMEmpireGuardian4 );

class GMEmpireGuardian4 : public BaseMap
{
public:
	static GMEmpireGuardian4Ptr Make();
	virtual ~GMEmpireGuardian4();
	
public:	// Object
	// ������Ʈ ����
	virtual bool CreateObject(OBJECT* o);
	// ������Ʈ ���μ���
	virtual bool MoveObject(OBJECT* o);
	// ������Ʈ ����Ʈ
	virtual bool RenderObjectVisual(OBJECT* o, BMD* b);
	// ������Ʈ ����
	virtual bool RenderObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);
	// �� ���� ������Ʈ ����Ʈ
	virtual void RenderAfterObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);
	// �� ���� ȭ�� �տ� ������ ȿ��
	virtual void RenderFrontSideVisual();

	// ���� ������
	bool RenderMonster(OBJECT* o, BMD* b, bool ExtraMon = 0);
	
public:	// Character
	// ���� ����
	virtual CHARACTER* CreateMonster(int iType, int PosX, int PosY, int Key);
	// ����(NPC) ���μ���
	virtual bool MoveMonsterVisual(OBJECT* o, BMD* b);

	// ���� ��ų �� ����Ʈ
	virtual void MoveBlurEffect(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( �Ϲ� )	
	virtual bool RenderMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( ��ų )
	virtual bool AttackEffectMonster(CHARACTER* c, OBJECT* o, BMD* b);
	// ��ų �ִϸ��̼� ���� �Լ�
	virtual bool SetCurrentActionMonster(CHARACTER* c, OBJECT* o);

	// ����(NPC) ���μ���
	bool MoveMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);
	
public: // Sound
	// ���� ����
	virtual bool PlayMonsterSound(OBJECT* o);
	// ������Ʈ ����
	virtual void PlayObjectSound(OBJECT* o);
	// �������
	void PlayBGM();
	
public:
	void Init();
	void Destroy();
	
public: //Weather
	void SetWeather(int weather);
	
private:
	bool m_bCurrentIsRage_BossGaion;		// ���� ���̿��� ����ȭ ���� ���� �Լ�.
	bool m_bCurrentIsRage_Jerint;			// ����Ʈ�� ����ȭ ���� ���� �Լ�.
	
protected:
	GMEmpireGuardian4();
};

extern bool IsEmpireGuardian4();

#endif	// LDS_ADD_MAP_EMPIREGUARDIAN4

#endif // !defined(AFX_GMEMPIREGUARDIAN4_H__C0F94320_4136_40DD_9931_BDD826E02987__INCLUDED_)
