//////////////////////////////////////////////////////////////////////////
//  
//  GMHellas.h
//  
//  ��  �� : 24��° �� ( ������ ���--��Ī )
//
//  ��  ¥ : 2004/05/20
//
//  �ۼ��� : �� �� ��
//
//////////////////////////////////////////////////////////////////////////
#ifndef __GMHELLAS_H__
#define __GMHELLAS_H__

//////////////////////////////////////////////////////////////////////////
//  Function.
//////////////////////////////////////////////////////////////////////////

// Į���� ���ΰ�?
inline  bool    InHellas ( int iMap=World ) { return ((iMap>=WD_24HELLAS && iMap<=WD_24HELLAS_END) || (iMap==WD_24HELLAS_7)); }
inline	bool	InHiddenHellas(int iMap=World ) { return (iMap==WD_24HELLAS_7) ? true : false; }


//////////////////////////////////////////////////////////////////////////
//  �� ���� ����.
//////////////////////////////////////////////////////////////////////////
bool    CreateWaterTerrain ( int mapIndex );
bool    IsWaterTerrain ( void );
void    AddWaterWave ( int x, int y, int range, int height );
float   GetWaterTerrain ( float x, float y );
void    MoveWaterTerrain ( void );
bool    RenderWaterTerrain ( void );
void    DeleteWaterTerrain ( void );
void    RenderWaterTerrain ( int Texture, float xf, float yf, float SizeX, float SizeY, vec3_t Light, float Rotation=0.f, float Alpha=1.f, float Height=0.f );


//////////////////////////////////////////////////////////////////////////
//  �� ����.
//////////////////////////////////////////////////////////////////////////
void    SettingHellasColor ( void );


//////////////////////////////////////////////////////////////////////////
//  ������ ����.
//////////////////////////////////////////////////////////////////////////
BYTE    GetHellasLevel ( int Class, int Level );
bool    GetUseLostMap ( bool bDrawAlert=false );
int     RenderHellasItemInfo ( ITEM* ip, int textNum );
bool	EnableKalima ( int Class, int Level, int ItemLevel);

//////////////////////////////////////////////////////////////////////////
//  ������Ʈ ����.
//////////////////////////////////////////////////////////////////////////
void    AddObjectDescription ( char* Text, vec3_t position );
void    RenderObjectDescription ( void );

bool    CreateHellasObject ( OBJECT* o );                                       //  ������Ʈ ������ ������ ����.
bool    MoveHellasObjectSetting ( int& objCount, int object );                  //  ���� ������Ʈ�� ���� ȿ���� ���� ������Ʈ ����.
bool    MoveHellasObject ( OBJECT* o, int& object, int& visibleObject );        //  ���õ� ������Ʈ�� ���� ȿ���� �����Ѵ�.
bool    MoveHellasAllObject ( OBJECT* o );                                      //  ��Ÿ ������Ʈ���� ���� ó��.
bool    MoveHellasVisual ( OBJECT* o );                                         //  ���� ������Ʈ���� ȿ�� ó��.
bool    RenderHellasVisual ( OBJECT* o, BMD* b );                               //  ���� ������Ʈ���� ȿ���� ��Ÿ����.
bool    RenderHellasObjectMesh  ( OBJECT* o, BMD* b );                          //  ���� ������Ʈ���� ( �޽� ) ȿ���� ��Ÿ����.
                                                                                //  �ش� �ʿ� ���ϴ� ���͵��� (�޽�) ȿ���� ó��.

//////////////////////////////////////////////////////////////////////////
//  Ȱ���ϴ� �� ������Ʈ.
//////////////////////////////////////////////////////////////////////////
int     CreateBigMon ( OBJECT* o );
void    MoveBigMon ( OBJECT* o );


//////////////////////////////////////////////////////////////////////////
//  ����. ( �ʿ� ���ϴ� ).
//////////////////////////////////////////////////////////////////////////
void    CreateMonsterSkill_ReduceDef ( OBJECT* o, int AttackTime, BYTE time, float Height );
void    CreateMonsterSkill_Poison ( OBJECT* o, int AttackTime, BYTE time );
void    CreateMonsterSkill_Summon ( OBJECT* o, int AttackTime, BYTE time );

void    SetActionDestroy_Def ( OBJECT* o );
void    RenderDestroy_Def ( OBJECT* o, BMD* b );
CHARACTER* CreateHellasMonster ( int Type, int PositionX, int PositionY, int Key );

bool    SettingHellasMonsterLinkBone ( CHARACTER* c, int Type );                //  ��� ������ ��ũ���� �����Ѵ�.

bool    SetCurrentAction_HellasMonster ( CHARACTER* c, OBJECT* o );                           //  ��� ������ �ൿ�� �����Ѵ�.
bool    AttackEffect_HellasMonster ( CHARACTER* c, CHARACTER* tc, OBJECT* o, OBJECT* to, BMD* b ); //  ��� ������ ���� ȿ��.
void    MonsterMoveWaterSmoke ( OBJECT* o );
void    MonsterDieWaterSmoke ( OBJECT* o );
bool    MoveHellasMonsterVisual ( OBJECT* o, BMD* b );                          //  ��� ���� ���־� ó��.
bool    RenderHellasMonsterCloth ( CHARACTER* c, OBJECT* o, bool Translate=true, int Select=0 );
bool    RenderHellasMonsterObjectMesh ( OBJECT* o, BMD* b );                    //  �ش� �ʿ� ���ϴ� ���͵��� (�޽�) ȿ�� ó��.
bool    RenderHellasMonsterVisual ( CHARACTER* c, OBJECT* o, BMD* b );          //  �ش� �ʿ� ���ϴ� ���͵��� ȿ�� ó��.

#endif// __GMHELLAS_H__