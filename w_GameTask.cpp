// w_GameTask.cpp: implementation of the GameTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "w_GameTask.h"

#ifdef NEW_USER_INTERFACE_CLIENTSYSTEM

#include "UIManager.h"
#include "ZzzOpenglUtil.h"
#include "ZzzLodTerrain.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzAI.h"
#include "NewUISystem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameTaskPtr GameTask::Make( Task::eType type )
{
	BoostSmart_Ptr(GameTask) task( new GameTask( type ) );
	task->Initialize( task );
	TheGameServerProxy().RegisterHandler( task );
	TheShopServerProxy().RegisterHandler( task );
	return task;
}

GameTask::GameTask( Task::eType type ) : Task( type )
{

}

GameTask::~GameTask()
{
	Destroy();
}

void GameTask::Initialize( BoostWeak_Ptr(GameTask) handler )
{
	//�ڱ� �ڽ� �����͸� ������ �ִٰ� ������ �ʿ��ϸ� �Ѱ� �ٱ�..--;;���� ���� ����..���Ͻ÷� ���ϴ°� ������ ����.
	//�׷��� ����� ���� �޾ƾ���...�̤�
	m_Handler = handler;
}

void GameTask::Destroy()
{
	
}

void GameTask::OnShopIn( const eShopType shoptype )
{
	ShopMake( shoptype );
	g_pNewUISystem->HideAll();
#ifdef KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
	g_pNewUISystem->Show( SEASON3B::INTERFACE_PARTCHARGE_SHOP );
#else // KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
	g_pNewUISystem->Toggle( SEASON3B::INTERFACE_PARTCHARGE_SHOP );
#endif // KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
}

void GameTask::OnShopOunt( const eShopType shoptype )
{
	ShopClear;
#ifdef KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
	MessageBoxClear;
	g_pNewUISystem->Hide( SEASON3B::INTERFACE_PARTCHARGE_SHOP );
#else // KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
	g_pNewUISystem->Toggle( SEASON3B::INTERFACE_PARTCHARGE_SHOP );
#endif // KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
}

#endif //NEW_USER_INTERFACE_CLIENTSYSTEM