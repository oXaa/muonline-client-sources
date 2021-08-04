// w_MapProcess.h: interface for the MapProcess class.
//
//////////////////////////////////////////////////////////////////////

#ifdef PSW_ADD_MAPSYSTEM

#if !defined(AFX_W_MAPPROCESS_H__951C620C_F82C_4E25_90CB_A877040F49E2__INCLUDED_)
#define AFX_W_MAPPROCESS_H__951C620C_F82C_4E25_90CB_A877040F49E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "w_BaseMap.h"

BoostSmartPointer(MapProcess);
class MapProcess  
{
public:
	static MapProcessPtr Make();
	virtual ~MapProcess();
	
public:
	bool LoadMapData();

public:
	// ������Ʈ ����
	bool CreateObject(OBJECT* o);
	// ������Ʈ ���μ���
	bool MoveObject(OBJECT* o);
	// ������Ʈ ����Ʈ
	bool RenderObjectVisual(OBJECT* o, BMD* b);
	// ������Ʈ �Ž� ����Ʈ
	bool RenderObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);
	// �� ���� ������Ʈ ����Ʈ
	void RenderAfterObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);

#ifdef LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC
	// �� ���� ȭ�� �տ� ������ ȿ��
	void RenderFrontSideVisual();
#endif //LDK_ADD_MAPPROCESS_RENDERBASESMOKE_FUNC
	
public:
	// ���� ����
	CHARACTER* CreateMonster(int iType, int PosX, int PosY, int Key);
	// ����(NPC) ���μ���
	bool MoveMonsterVisual(OBJECT* o, BMD* b);
	// ���� ��ų �� ����Ʈ
	void MoveBlurEffect(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( �Ϲ� )	
	bool RenderMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( ��ų )
	bool AttackEffectMonster(CHARACTER* c, OBJECT* o, BMD* b);
	// ��ų �ִϸ��̼� ���� �Լ�
	bool SetCurrentActionMonster(CHARACTER* c, OBJECT* o);

public:
	bool PlayMonsterSound(OBJECT* o);

public:
	bool ReceiveMapMessage( BYTE code, BYTE subcode, BYTE* ReceiveBuffer );

public:
	// ���
	void Register( BoostSmart_Ptr( BaseMap ) pMap );
	// ��� ����
	void UnRegister( ENUM_WORLD type );

public:
	BaseMap& GetMap( int type );
	
private:
	bool FindMap( ENUM_WORLD type );
	BaseMap& FindBaseMap( ENUM_WORLD type );
	void Init();
	void Destroy();
	MapProcess();
	
private:
	typedef list< BoostSmart_Ptr(BaseMap) >		MapList;
	
private:
	MapList				m_MapList;
};

extern MapProcessPtr g_MapProcess;

extern MapProcess& TheMapProcess();

#endif // !defined(AFX_W_MAPPROCESS_H__951C620C_F82C_4E25_90CB_A877040F49E2__INCLUDED_)

#endif //PSW_ADD_MAPSYSTEM
