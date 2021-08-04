// GMEmpireGuardian2.h: interface for the GMEmpireGuardian2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMEMPIREGUARDIAN2_H__823C7D40_34C6_4235_9EBD_69026B7F67FD__INCLUDED_)
#define AFX_GMEMPIREGUARDIAN2_H__823C7D40_34C6_4235_9EBD_69026B7F67FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LDS_ADD_MAP_EMPIREGUARDIAN2

#include "w_BaseMap.h"

BoostSmartPointer( GMEmpireGuardian2 );

class GMEmpireGuardian2 : public BaseMap
{
public:
	static GMEmpireGuardian2Ptr Make();
	virtual ~GMEmpireGuardian2();
	
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
	
public: //Weather
	bool CreateRain( PARTICLE* o );
 	void SetWeather(int weather);

private:
	bool m_bCurrentIsRage_Bermont;			// 2�� ����Ʈ�� ����ȭ ���� ���� �Լ�.
	
public:
	void Init();
	void Destroy();
	
protected:
	GMEmpireGuardian2();
};

extern bool IsEmpireGuardian2();

#endif // LDS_ADD_MAP_EMPIREGUARDIAN2

#endif // !defined(AFX_GMEMPIREGUARDIAN2_H__823C7D40_34C6_4235_9EBD_69026B7F67FD__INCLUDED_)
