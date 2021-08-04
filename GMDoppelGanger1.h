// GMDoppelGanger1.h: interface for the CGMDoppelGanger1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMDOPPELGANGER1_H__12D0B73D_137C_40E6_81C6_D9495961AE3D__INCLUDED_)
#define AFX_GMDOPPELGANGER1_H__12D0B73D_137C_40E6_81C6_D9495961AE3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_MAP_DOPPELGANGER1

#include "w_BaseMap.h"

BoostSmartPointer( CGMDoppelGanger1 );
class CGMDoppelGanger1 : public BaseMap  
{
public:
	static CGMDoppelGanger1Ptr Make();
	virtual ~CGMDoppelGanger1();

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
	CGMDoppelGanger1();

	BOOL m_bIsMP3Playing;
};

extern bool IsDoppelGanger1();

#endif	// YDG_ADD_MAP_DOPPELGANGER1

#endif // !defined(AFX_GMDOPPELGANGER1_H__12D0B73D_137C_40E6_81C6_D9495961AE3D__INCLUDED_)
