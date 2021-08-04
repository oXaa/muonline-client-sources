// GMSantaTown.h: interface for the CGMSantaTown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMSANTATOWN_H__BFA5CEE0_59CC_43E9_842B_C5DD402D263D__INCLUDED_)
#define AFX_GMSANTATOWN_H__BFA5CEE0_59CC_43E9_842B_C5DD402D263D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_SANTA_TOWN

#include "w_BaseMap.h"

BoostSmartPointer( CGMSantaTown );
class CGMSantaTown : public BaseMap  
{
public:
	static CGMSantaTownPtr Make();
	virtual ~CGMSantaTown();

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
	// �������
	void PlayBGM();

public:
	void Init();
	void Destroy();

	// �ʿ� �� ������ �ϴ� ȿ��
	bool CreateSnow( PARTICLE* o );

protected:
	CGMSantaTown();
};

extern bool IsSantaTown();

#endif	// YDG_ADD_MAP_SANTA_TOWN

#endif // !defined(AFX_GMSANTATOWN_H__BFA5CEE0_59CC_43E9_842B_C5DD402D263D__INCLUDED_)
