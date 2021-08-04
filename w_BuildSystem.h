// w_BuildSystem.h: interface for the BuildSystem class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_BUILDER

#if !defined(AFX_W_BUILDSYSTEM_H__40403F88_C341_4728_9D8E_D5005A519406__INCLUDED_)
#define AFX_W_BUILDSYSTEM_H__40403F88_C341_4728_9D8E_D5005A519406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	���� Build �Լ��� ���� �̿����� ����. �Լ� �ݵ� ���� ����� �Ҹ� �� �� �ִ�.
	�׷��Ƿ� �� �����ӿ� ��� ���� ����̸� ����� ���ϵ��� ����.
	Initialize�� �Ҷ� ��� ������ �غ���.
*/

#include "w_ClientInfoBuilder.h"
#include "w_GameInfoBuilder.h"

BoostSmartPointer( BuildSystem );
class BuildSystem  
{
public:
	enum eType
	{
		eClientInfo,
		eGameInfo,
		eCount,
	};

public:
	static BuildSystemPtr Make();
	virtual ~BuildSystem();

public:
	ClientInfoBuilder& GetClientInfoBuilder();
	GameInfoBuilder& GetGameInfoBuilder();

private:
	void Initialize( BoostWeak_Ptr(BuildSystem) handler );
	void Destroy();
	BuildSystem();

private:
	ClientInfoBuilderPtr			m_ClientInfoBuilder;
	GameInfoBuilderPtr				m_GameInfoBuilder;
	
};

inline
ClientInfoBuilder& BuildSystem::GetClientInfoBuilder()
{
	assert(m_ClientInfoBuilder);
	return *m_ClientInfoBuilder;
}

inline
GameInfoBuilder& BuildSystem::GetGameInfoBuilder()
{
	assert(m_GameInfoBuilder);
	return *m_GameInfoBuilder;
}

#endif // !defined(AFX_W_BUILDSYSTEM_H__40403F88_C341_4728_9D8E_D5005A519406__INCLUDED_)

#endif //NEW_USER_INTERFACE_BUILDER