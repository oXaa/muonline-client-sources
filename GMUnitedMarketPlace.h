// GMUnitedMarketPlace.h: interface for the GMUnitedMarketPlace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMUNITEDMARKETPLACE_H__8FF77135_1C1E_46B3_A060_48F13DC345D3__INCLUDED_)
#define AFX_GMUNITEDMARKETPLACE_H__8FF77135_1C1E_46B3_A060_48F13DC345D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE

#include "w_BaseMap.h"

BoostSmartPointer( GMUnitedMarketPlace );


class GMUnitedMarketPlace  : public BaseMap 
{
public:
	static GMUnitedMarketPlacePtr Make();
	virtual ~GMUnitedMarketPlace();

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
	bool MoveRain( PARTICLE* o );
	
protected:
	GMUnitedMarketPlace();
};

extern bool IsUnitedMarketPlace();

#endif // LDS_ADD_MAP_UNITEDMARKETPLACE

#endif // !defined(AFX_GMUNITEDMARKETPLACE_H__8FF77135_1C1E_46B3_A060_48F13DC345D3__INCLUDED_)
