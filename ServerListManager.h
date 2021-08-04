// ServerListManager.h: interface for the CServerListManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERLISTMANAGER_H__9FFD345C_6AD5_4D74_9194_FEF1D016B3FD__INCLUDED_)
#define AFX_SERVERLISTMANAGER_H__9FFD345C_6AD5_4D74_9194_FEF1D016B3FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_SERVER_LIST_SYSTEM

#include "ServerGroup.h"

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
using namespace std;

#define SLM_MAX_SERVER_NAME_LENGTH	32		// ���� �̸� ����
#define SLM_MAX_SERVER_COUNT		15		// ������ ���� ���� ����

// ������ ���� ����ü
struct SServerGroupInfo
{
	char	m_szName[SLM_MAX_SERVER_NAME_LENGTH];	// ������ �̸�
	BYTE	m_byPos;							// ������ ��ġ(��:0, ��:1, ��:2)
	BYTE	m_bySequence;						// ������ ����
	BYTE	m_abyNonPVP[SLM_MAX_SERVER_COUNT];	// NonPVP �����ΰ�?(���������� ���� ������ NonPVP ����)
	string	m_strDescript;						// ������ ���� ���ڿ�
};

typedef map<WORD, SServerGroupInfo> ServerListScriptMap;
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS

typedef std::map<int, CServerGroup*>	type_mapServerGroup;

class CServerListManager  
{
protected:
	CServerListManager();
public:
	virtual ~CServerListManager();

public:
	static CServerListManager* GetInstance();

	void InsertServerGroup(int iConnectIndex, int iServerPercent);
	void Release();

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	void LoadServerListScript();
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS
#ifdef ASG_MOD_SERVER_LIST_CHANGE_MSG
	const char* GetNotice();
#endif	// ASG_MOD_SERVER_LIST_CHANGE_MSG
	
	void SetFirst();
	bool GetNext(OUT CServerGroup* &pServerGroup);
	CServerGroup* GetServerGroupByBtnPos(int iBtnPos);

	int GetServerGroupSize();

	// ���� ���õ� ���� ����
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	void SetSelectServerInfo(unicode::t_char* pszName, int iIndex, int iCensorshipIndex,
		BYTE byNonPvP, bool bTestServer);
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	void SetSelectServerInfo(unicode::t_char* pszName, int iIndex, int iCensorshipIndex, bool bNonPvP, bool bTestServer);
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	unicode::t_char* GetSelectServerName();
	int	GetSelectServerIndex();
	int GetCensorshipIndex();
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	BYTE GetNonPVPInfo();
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	bool IsNonPvP();
	bool IsTestServer();
	void SetTotalServer(int iTotalServer);
	int GetTotalServer();			// ��ü ���� ����
	
protected:
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	const SServerGroupInfo* GetServerGroupInfoInScript(WORD wServerGroupIndex);
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS
	bool MakeServerGroup(IN int iServerGroupIndex, OUT CServerGroup* pServerGroup);
	void InsertServer(CServerGroup* pServerGroup, int iConnectIndex, int iServerPercent);
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
	void BuxConvert(BYTE* pbyBuffer, int nSize);
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP

public:
	type_mapServerGroup			m_mapServerGroup;
	type_mapServerGroup::iterator	m_iterServerGroup;

	int				m_iTotalServer;
	unicode::t_char m_szSelectServerName[MAX_TEXT_LENGTH];
	int				m_iSelectServerIndex;
	int				m_iCensorshipIndex;
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	BYTE			m_byNonPvP;
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	bool			m_bNonPvP;
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	bool			m_bTestServer;

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
protected:
	ServerListScriptMap		m_mapServerListScript;	// ServerList.txt ������ ���⿡ ����.(���� �׷� �ε����� Ű)
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS
#ifdef ASG_MOD_SERVER_LIST_CHANGE_MSG
	string					m_strNotice;			// �������� ȭ�鿡���� ��������.
#endif	// ASG_MOD_SERVER_LIST_CHANGE_MSG
};

#define g_ServerListManager CServerListManager::GetInstance()

#endif // KJH_ADD_SERVER_LIST_SYSTEM

#endif // !defined(AFX_SERVERLISTMANAGER_H__9FFD345C_6AD5_4D74_9194_FEF1D016B3FD__INCLUDED_)
