// GMDoppelGanger4.h: interface for the GMDoppelGanger4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMDOPPELGANGER4_H__75DEE7BA_F85A_46F3_B267_BFCA24157D83__INCLUDED_)
#define AFX_GMDOPPELGANGER4_H__75DEE7BA_F85A_46F3_B267_BFCA24157D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_DOPPELGANGER4

#include "w_BaseMap.h"

BoostSmartPointer( CGMDoppelGanger4 );
class CGMDoppelGanger4 : public BaseMap  
{
public:
	static CGMDoppelGanger4Ptr Make();
	virtual ~CGMDoppelGanger4();

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
	CGMDoppelGanger4();
};

extern bool IsDoppelGanger4();

#endif	// YDG_ADD_MAP_DOPPELGANGER4

#endif // !defined(AFX_GMDOPPELGANGER4_H__75DEE7BA_F85A_46F3_B267_BFCA24157D83__INCLUDED_)
