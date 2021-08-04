// GMDoppelGanger2.h: interface for the GMDoppelGanger2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMDOPPELGANGER2_H__492710D3_0D2E_4903_85DD_ABF78B68BD7A__INCLUDED_)
#define AFX_GMDOPPELGANGER2_H__492710D3_0D2E_4903_85DD_ABF78B68BD7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_DOPPELGANGER2

#include "w_BaseMap.h"

BoostSmartPointer( CGMDoppelGanger2 );
class CGMDoppelGanger2 : public BaseMap  
{
public:
	static CGMDoppelGanger2Ptr Make();
	virtual ~CGMDoppelGanger2();

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
public:
	// �ʿ� �Ҿ� ������ �ϴ� ȿ��
	bool CreateFireSpark(PARTICLE* o);
	
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
	
public: // Sound
	// ���� ����
	virtual bool PlayMonsterSound(OBJECT* o);
	// ������Ʈ ����
	virtual void PlayObjectSound(OBJECT* o);

public:
	void Init();
	void Destroy();

protected:
	CGMDoppelGanger2();
};

extern bool IsDoppelGanger2();

#endif	// YDG_ADD_MAP_DOPPELGANGER2

#endif // !defined(AFX_GMDOPPELGANGER2_H__492710D3_0D2E_4903_85DD_ABF78B68BD7A__INCLUDED_)
