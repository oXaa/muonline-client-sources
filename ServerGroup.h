// ServerGroup.h: interface for the CServerGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERGROUP_H__2C57D7A7_11E9_42E8_812A_8D1B3E311657__INCLUDED_)
#define AFX_SERVERGROUP_H__2C57D7A7_11E9_42E8_812A_8D1B3E311657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_SERVER_LIST_SYSTEM

#include "ServerInfo.h"

typedef std::list<CServerInfo*>	type_listServer;

class CServerGroup  
{
public:
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	enum SERVER_BTN_POSITION
	{
		SBP_LEFT	= 0,
		SBP_RIGHT	= 1,
		SBP_CENTER	= 2,
	};
#else	// ASG_ADD_SERVER_LIST_SCRIPTS
	enum SERVER_BTN_POSITION
	{
		SBP_CENTER	= 0,
		SBP_LEFT	= 1,
		SBP_RIGHT	= 2,
	};
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS

public:
	CServerGroup();
	virtual ~CServerGroup();

public:
	void Release();

public:
	int		m_iSequence;				// ��������(��������)
	int		m_iWidthPos;				// ������ư�� ���� ������ (enum SERVER_BTN_POSITION ����)
	int		m_iBtnPos;					// ������ư�� ���� ������ - ��ư�����Ҷ� �����Ѵ�.
	int		m_iServerIndex;				// ���� ������ȣ
	int		m_iNumServer;				// ���� ����
	bool	m_bPvPServer;				// PvP�������
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	BYTE	m_abyNonPvpServer[MAX_SERVER_LOW];	// 0: �Ϲ� Pvp, 1: �Ϲ� NonPvp, 2: ����ä�� Pvp, 3: ����ä�� NonPvp
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	bool	m_bNonPvpServer[MAX_SERVER_LOW];	// NonPvP����(ServerGroup�� PvP �� ��� false)
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	unicode::t_char	m_szName[MAX_TEXT_LENGTH];				// �����̸�
	unicode::t_char	m_szDescription[MAX_TEXT_LENGTH];		// ��������

	type_listServer				m_listServerInfo;		// ���� ���� ����Ʈ
	
protected:
	type_listServer::iterator	m_iterServerList;		// ���� ��������Ʈ iterator


public:
	void InsertServerInfo(CServerInfo* pServerInfo);

	void SetFirst();
	bool GetNext(OUT CServerInfo* &pServerInfo);

	int GetServerSize();
	CServerInfo* GetServerInfo(int iSequence);
};

#endif // KJH_ADD_SERVER_LIST_SYSTEM

#endif // !defined(AFX_SERVERGROUP_H__2C57D7A7_11E9_42E8_812A_8D1B3E311657__INCLUDED_)
