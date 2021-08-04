// GMDuelArena.h: interface for the CGMDuelArena class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMDUELARENA_H__BD799B5C_04B6_49CA_A792_12E3D7111356__INCLUDED_)
#define AFX_GMDUELARENA_H__BD799B5C_04B6_49CA_A792_12E3D7111356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_DUEL_ARENA

#include "w_BaseMap.h"

BoostSmartPointer( CGMDuelArena );
class CGMDuelArena : public BaseMap  
{
public:
	static CGMDuelArenaPtr Make();
	virtual ~CGMDuelArena();

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

protected:
	CGMDuelArena();
};

extern bool IsDuelArena();

#endif	// YDG_ADD_MAP_DUEL_ARENA

#endif // !defined(AFX_GMDUELARENA_H__BD799B5C_04B6_49CA_A792_12E3D7111356__INCLUDED_)
