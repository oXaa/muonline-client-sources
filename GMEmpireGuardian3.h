// GMEmpireGuardian3.h: interface for the GMEmpireGuardian3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMEmpireGuardian3_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_)
#define AFX_GMEmpireGuardian3_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LDK_ADD_MAP_EMPIREGUARDIAN3

#include "w_BaseMap.h"

BoostSmartPointer( GMEmpireGuardian3 );

class GMEmpireGuardian3 : public BaseMap
{
public:
	static GMEmpireGuardian3Ptr Make();
	virtual ~GMEmpireGuardian3();

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
	bool CreateRain( PARTICLE* o );
	void SetWeather(int weather);

private:
	bool m_bCurrentIsRage_Kato;			// 3�� ī���� ����ȭ ���� ���� �Լ�.
	
protected:
	GMEmpireGuardian3();
};

extern bool IsEmpireGuardian3();

#endif	// LDK_ADD_MAP_EMPIREGUARDIAN3

#endif // !defined(AFX_GMEmpireGuardian3_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_)
