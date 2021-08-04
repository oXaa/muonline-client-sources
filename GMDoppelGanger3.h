// GMDoppelGanger3.h: interface for the GMDoppelGanger3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMDOPPELGANGER3_H__EE74650C_6401_4751_B2A8_64BF23A42B68__INCLUDED_)
#define AFX_GMDOPPELGANGER3_H__EE74650C_6401_4751_B2A8_64BF23A42B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_DOPPELGANGER3

#include "w_BaseMap.h"

BoostSmartPointer( CGMDoppelGanger3 );
class CGMDoppelGanger3 : public BaseMap  
{
public:
	static CGMDoppelGanger3Ptr Make();
	virtual ~CGMDoppelGanger3();

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

public:
	void Init();
	void Destroy();

protected:
	CGMDoppelGanger3();
};

extern bool IsDoppelGanger3();

#endif	// YDG_ADD_MAP_DOPPELGANGER3

#endif // !defined(AFX_GMDOPPELGANGER3_H__EE74650C_6401_4751_B2A8_64BF23A42B68__INCLUDED_)
