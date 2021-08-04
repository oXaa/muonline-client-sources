//*****************************************************************************
// file    : GM_PK_Field.h
// producer: BGPARK
//*****************************************************************************

#ifndef _GM_PK_FIELD_H_
#define _GM_PK_FIELD_H_

#ifdef PBG_ADD_PKFIELD

class BMD;

#include "w_BaseMap.h"
#include "./Time/Timer.h"

BoostSmartPointer(CGM_PK_Field);
class CGM_PK_Field: public BaseMap
{
public:
	static CGM_PK_FieldPtr Make();
	virtual ~CGM_PK_Field();

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
	// ���� ����Ʈ
	virtual bool RenderMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);

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
	
private:
	CGM_PK_Field();
	
	// ���� ������
	bool RenderMonster(OBJECT* o, BMD* b, bool ExtraMon = 0);
};

// pk�ʵ� ���ΰ�
extern bool IsPKField();

#endif //PBG_ADD_PKFIELD

#endif //_GM_PK_FIELD_H_