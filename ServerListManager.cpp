// ServerListManager.cpp: implementation of the CServerListManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#ifdef KJH_ADD_SERVER_LIST_SYSTEM

#include "ServerListManager.h"

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
#include "./Utilities/Log/ErrorReport.h"
#ifndef ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP	// ������ ����.
#include "wsclientinline.h"
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP

#define	SLM_SERVERLIST_FILE			"Data\\Local\\ServerList.bmd"
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerListManager::CServerListManager()
{
	m_iTotalServer = 0;
	m_szSelectServerName[0] = '\0';
	m_iSelectServerIndex = -1;
}

CServerListManager::~CServerListManager()
{
	Release();
}

CServerListManager* CServerListManager::GetInstance()
{
	static CServerListManager s_ServerListManager;
	return &s_ServerListManager;
}

void CServerListManager::Release()
{	
	type_mapServerGroup::iterator iterServerGroup = m_mapServerGroup.begin();
	for( ; iterServerGroup!=m_mapServerGroup.end() ; iterServerGroup++ )
	{
		delete iterServerGroup->second;
	}

	m_mapServerGroup.clear();
	
	m_iTotalServer = 0;
	m_bTestServer = false;
}

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
void CServerListManager::BuxConvert(BYTE* pbyBuffer, int nSize)
{
	BYTE abyBuxCode[3] = { 0xfc, 0xcf, 0xab };
	for (int i = 0; i < nSize; ++i)
		pbyBuffer[i] ^= abyBuxCode[i%3];
}
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
//*****************************************************************************
// �Լ� �̸� : LoadServerListScript()
// �Լ� ���� : ���� ����Ʈ ��Ʈ��Ʈ(ServerList.bmd) �ε�.
//*****************************************************************************
void CServerListManager::LoadServerListScript()
{
	FILE* fp = ::fopen(SLM_SERVERLIST_FILE, "rb");
	if (fp == NULL)
	{
		char szMessage[256];
		::sprintf(szMessage, "%s file not found.\r\n", SLM_SERVERLIST_FILE);
		g_ErrorReport.Write(szMessage);
		::MessageBox(g_hWnd, szMessage, NULL, MB_OK);
		::PostMessage(g_hWnd, WM_DESTROY, 0, 0);
		return;
	}
	
#pragma pack(push, 1)
// ������ ���� ����ü
typedef struct _SERVER_GROUP_INFO
{
	WORD	m_wIndex;							// ���������� ù��° ���� �ε���(20�� �����)
	char	m_szName[SLM_MAX_SERVER_NAME_LENGTH];	// ������ �̸�
	BYTE	m_byPos;							// ������ ��ġ(��:0, ��:1, ��:2)
	BYTE	m_bySequence;						// ������ ����
	BYTE	m_abyNonPVP[SLM_MAX_SERVER_COUNT];	// NonPVP �����ΰ�?(���������� ���� ������ NonPVP ����)
	short	m_nDescriptLen;						// ������ ���� ���ڿ� ����
} SERVER_GROUP_INFO;
#pragma pack(pop)
	
	int nSize = sizeof(SERVER_GROUP_INFO);
	SERVER_GROUP_INFO sServerGroupScript;
	char szDescript[1024];
	SServerGroupInfo sServerGroupInfo;
	int i;

	while (0 != ::fread(&sServerGroupScript, nSize, 1, fp))
	{
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
		BuxConvert((BYTE*)&sServerGroupScript, nSize);
#else	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
		::BuxConvert((BYTE*)&sServerGroupScript, nSize);
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
		
		::fread(szDescript, sServerGroupScript.m_nDescriptLen, 1, fp);
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
		BuxConvert((BYTE*)szDescript, sServerGroupScript.m_nDescriptLen);
#else	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP
		::BuxConvert((BYTE*)szDescript, sServerGroupScript.m_nDescriptLen);
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS_GLOBAL_TEMP

#ifdef ASG_MOD_SERVER_LIST_CHANGE_MSG
		if (500 <= sServerGroupScript.m_wIndex)
		{
			// �º���̸鼭 �����׷� ��ȣ�� 501�̰ų�, �·����̸鼭 �����׷� ��ȣ�� 500�̸� ����������.
			if ((BLUE_MU::IsBlueMuServer() && 501 == sServerGroupScript.m_wIndex)
				|| (!BLUE_MU::IsBlueMuServer() && 500 == sServerGroupScript.m_wIndex))
			{
				m_strNotice = szDescript;
			}

			continue;	// �����׷� ��ȣ�� 500 �̻��� ���������̹Ƿ�.
		}
#endif	// ASG_MOD_SERVER_LIST_CHANGE_MSG

		::strncpy(sServerGroupInfo.m_szName, sServerGroupScript.m_szName,
			SLM_MAX_SERVER_NAME_LENGTH);
		sServerGroupInfo.m_byPos = sServerGroupScript.m_byPos;
		sServerGroupInfo.m_bySequence = sServerGroupScript.m_bySequence;
		for (i = 0; i < SLM_MAX_SERVER_COUNT; ++i)
			sServerGroupInfo.m_abyNonPVP[i] = sServerGroupScript.m_abyNonPVP[i];
		sServerGroupInfo.m_strDescript = szDescript;
		
		m_mapServerListScript.insert(make_pair(sServerGroupScript.m_wIndex, sServerGroupInfo));
	}
	
	::fclose(fp);
}

//*****************************************************************************
// �Լ� �̸� : GetServerGroupInfoInScript()
// �Լ� ���� : ���� �׷� ��ũ��Ʈ ���� ���.
// �Ű� ���� : wServerGroupIndex	: ���� �׷� �ε���.(���� �ε��� / 20)
// ��ȯ ��	 : ���� �׷� ��ũ��Ʈ ����
//*****************************************************************************
const SServerGroupInfo* CServerListManager::GetServerGroupInfoInScript(WORD wServerGroupIndex)
{
	ServerListScriptMap::const_iterator iter = m_mapServerListScript.find(wServerGroupIndex);
	if (iter == m_mapServerListScript.end())
		return NULL;

	return &(iter->second);
}
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS

#ifdef ASG_MOD_SERVER_LIST_CHANGE_MSG
//*****************************************************************************
// �Լ� �̸� : GetNotice()
// �Լ� ���� : �������� ���ڿ� ���.
// ��ȯ ��	 : �������� ���ڿ�
//*****************************************************************************
const char* CServerListManager::GetNotice()
{
	return m_strNotice.c_str();
}
#endif	// ASG_MOD_SERVER_LIST_CHANGE_MSG

void CServerListManager::InsertServerGroup(int iConnectIndex, int iServerPercent)
{
	CServerGroup* pServerGroup = NULL;

	type_mapServerGroup::iterator iterServerGroup = m_mapServerGroup.begin();

	bool bEqual = false;
	while( iterServerGroup != m_mapServerGroup.end() )
	{
		if( (iterServerGroup->second)->m_iServerIndex == iConnectIndex/20 )
		{
			bEqual = true;
			break;
		}

		iterServerGroup++;
	}

	if( bEqual == true )
	{
		pServerGroup = iterServerGroup->second;
	}
	else
	{
		pServerGroup = new CServerGroup;
		
		if( MakeServerGroup(iConnectIndex/20, pServerGroup) == false)
			return;
		
		m_mapServerGroup.insert(type_mapServerGroup::value_type(pServerGroup->m_iSequence, pServerGroup));
	}	
	
	InsertServer(pServerGroup, iConnectIndex, iServerPercent);
	
	m_iterServerGroup = m_mapServerGroup.begin();
}

bool CServerListManager::MakeServerGroup(IN int iServerGroupIndex, OUT CServerGroup* pServerGroup)
{
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	const SServerGroupInfo* pServerGroupInfo = GetServerGroupInfoInScript(iServerGroupIndex);
	if (NULL == pServerGroupInfo)
		return false;

	::strcpy(pServerGroup->m_szName, pServerGroupInfo->m_szName);	// Name
	::strcpy(pServerGroup->m_szDescription, pServerGroupInfo->m_strDescript.c_str());// Description
	pServerGroup->m_iSequence = (int)pServerGroupInfo->m_bySequence;// ����
	pServerGroup->m_iWidthPos = (int)pServerGroupInfo->m_byPos;		// Position
	pServerGroup->m_iServerIndex = iServerGroupIndex;				// ����������ȣ
	pServerGroup->m_bPvPServer = true;
	int i;
	for (i = 0; i < SLM_MAX_SERVER_COUNT; ++i)
	{
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		pServerGroup->m_abyNonPvpServer[i] = pServerGroupInfo->m_abyNonPVP[i];
		if (0x01 & pServerGroup->m_abyNonPvpServer[i])	// 1�̰ų� 3�̸� NonPVP ������.
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		pServerGroup->m_bNonPvpServer[i] = (bool)pServerGroupInfo->m_abyNonPVP[i];
		if (pServerGroup->m_bNonPvpServer[i])
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		if (pServerGroup->m_bNonPvpServer[i] = (bool)pServerGroupInfo->m_abyNonPVP[i])
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
			pServerGroup->m_bPvPServer = false;	// NonPVP ������ �Ѱ��� ������  �� ���� �׷��� PvPServer�� �ƴ�.
	}
	for (; i < MAX_SERVER_LOW; ++i)
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		pServerGroup->m_abyNonPvpServer[i] = 0;
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		pServerGroup->m_bNonPvpServer[i] = false;
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL

	return true;
#else	// ASG_ADD_SERVER_LIST_SCRIPTS
	// - Original Server
	//����		= 0		
	//����		= 1		
	//�ٸ�		= 2		
	//ī��		= 3	
	//��		= 4
	//��Į		= 5
	//���		= 6
	//����(X)	= 7
	//Ÿ��(X)	= 8
	//����(X)	= 9
	//���(X)	= 10
	//���(X)	= 11
	//�׽�Ʈ	= 12
	//�̿�(X)	= 13
	//�з�(X)	= 14
	//�·�(X)	= 15
	//�簡(X)	= 16
	//Ƽź(X)	= 17
	//��ī(X)	= 18
	//�÷�(X)	= 19
	//����		= 20 - PvP
	//���		= 21
	//����		= 22
	//�ǹ�		= 23
	//����		= 24
	//�η�		= 25 - PvP

	// - Blue Server
	//��׵�	= 35 - PvP
	//�߰���	= 36 - PvP
	//��������	= 37 - PvP

	/*
	//----------------------------------------------------------------
	 < ��ũ��Ʈ�� ���� �ϴºκ�>
		* m_szName
			- �����̸�
		* m_szDescription
			- ���� ����
		* m_iSequence
			- �������̾�� ��. (��ġ�� �ȵ�)
			- ������ ��ư�� ���� �����ʿ� m_iSequence�� ������������ ��ϵ�.
		* m_iWidthPos 
			- SBP_CENTER�� ������ �ϳ�. (TestServer��Ͽ�)
			- SBP_RIGHT/SBP_LEFT�� �ִ� 10����
		* m_bPvPServer 
			- true : PvP������, false : PvP, NonPvP���� ȥ�ռ����� (������� ���� �ʿ�)
		* m_bNonPvpServer
			- �������� NonPvp�� �������ش�. (�������� �ִ� 20�� ������ ���´�.)
			- ������ȣ���� �������־�� �Ѵ�. 
			- true : NonPvP����
			- ����Ʈ�� false
	//----------------------------------------------------------------
	*/

	switch(iServerGroupIndex)
	{
	case 0:		// ����
		{
			strcpy(pServerGroup->m_szName, GlobalText[540]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1736]);		// Description
			pServerGroup->m_iSequence = 13;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ����������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;	
	case 1:		// ����
		{
			strcpy(pServerGroup->m_szName, GlobalText[541]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1735]);		// Description
			pServerGroup->m_iSequence = 12;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;	
	case 2:		// �ٸ�
		{
			strcpy(pServerGroup->m_szName, GlobalText[542]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1734]);		// Description
			pServerGroup->m_iSequence = 11;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 3:		// ī��
		{
			strcpy(pServerGroup->m_szName, GlobalText[543]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1733]);		// Description
			pServerGroup->m_iSequence = 10;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 4:		// ��
		{
			strcpy(pServerGroup->m_szName, GlobalText[544]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1732]);		// Description
			pServerGroup->m_iSequence = 9;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 5:		// ��Į
		{
			strcpy(pServerGroup->m_szName, GlobalText[545]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1731]);		// Description
			pServerGroup->m_iSequence = 8;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_RIGHT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 6:		// ���
		{
			strcpy(pServerGroup->m_szName, GlobalText[546]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1730]);		// Description
			pServerGroup->m_iSequence = 7;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;				// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 12:	// �׽�Ʈ
		{
			strcpy(pServerGroup->m_szName, GlobalText[559]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1737]);		// Description
			pServerGroup->m_iSequence = 0;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_CENTER;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 20:	// ����
		{
			strcpy(pServerGroup->m_szName, GlobalText[1829]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1717]);		// Description
			pServerGroup->m_iSequence = 2;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;				// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = true;
		}break;
	case 21:	// ���
		{
			strcpy(pServerGroup->m_szName, GlobalText[1873]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1876]);		// Description
			pServerGroup->m_iSequence = 4;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 22:	// ����
		{
			strcpy(pServerGroup->m_szName, GlobalText[1874]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1877]);		// Description
			pServerGroup->m_iSequence = 3;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 23:	// �ǹ�
		{
			strcpy(pServerGroup->m_szName, GlobalText[1272]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1274]);		// Description
			pServerGroup->m_iSequence = 5;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 24:	// ����
		{
			strcpy(pServerGroup->m_szName, GlobalText[1273]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[1275]);		// Description
			pServerGroup->m_iSequence = 6;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = false;
			pServerGroup->m_bNonPvpServer[0] = true;
			pServerGroup->m_bNonPvpServer[1] = true;
			pServerGroup->m_bNonPvpServer[14] = true;
		}break;
	case 25:	// �η�
		{
			strcpy(pServerGroup->m_szName, GlobalText[728]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[729]);		// Description
			pServerGroup->m_iSequence = 1;									// ����
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;			// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = true;
		}break;
	case 35:		// ��׵�
		{
			strcpy(pServerGroup->m_szName, GlobalText[3022]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[3023]);		// Description
#ifdef YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iSequence = 32;									// ����
#else	// YDG_MOD_BLUE_NEWSERVER_ORDER
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
			pServerGroup->m_iSequence = 31;									// ����
#else // KJH_MOD_INGAMESHOP_PATCH_091028
			pServerGroup->m_iSequence = 30;									// ����
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
#endif	// YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;				// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ����������ȣ
			pServerGroup->m_bPvPServer = true;
		}break;	
	case 36:		// �߰���
		{
			strcpy(pServerGroup->m_szName, GlobalText[3024]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[3025]);		// Description
#ifdef YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iSequence = 31;									// ����
#else	// YDG_MOD_BLUE_NEWSERVER_ORDER
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
			pServerGroup->m_iSequence = 30;									// ����
#else // KJH_MOD_INGAMESHOP_PATCH_091028
			pServerGroup->m_iSequence = 31;									// ����
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
#endif	// YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;				// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = true;
		}break;	
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
	case 37:		// ��������
#else // KJH_MOD_INGAMESHOP_PATCH_091028
	case 38:		// �Ƹ�ī
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
		{
			strcpy(pServerGroup->m_szName, GlobalText[3026]);				// Name
			strcpy(pServerGroup->m_szDescription, GlobalText[3027]);		// Description
#ifdef YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iSequence = 30;									// ����
#else	// YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iSequence = 32;									// ����
#endif	// YDG_MOD_BLUE_NEWSERVER_ORDER
			pServerGroup->m_iWidthPos = CServerGroup::SBP_LEFT;				// Position
			pServerGroup->m_iServerIndex = iServerGroupIndex;				// ���� ������ȣ
			pServerGroup->m_bPvPServer = true;
		}break;
	default:
		{
			return false;
		}
	}

	return true;
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS
}

void CServerListManager::InsertServer(CServerGroup* pServerGroup, int iConnectIndex, int iServerPercent)
{
	CServerInfo* pServerInfo = new CServerInfo;
	pServerInfo->m_iSequence = pServerGroup->GetServerSize();
	pServerInfo->m_iIndex = (iConnectIndex%20)+1;
	pServerInfo->m_iConnectIndex = iConnectIndex;
	pServerInfo->m_iPercent = iServerPercent;
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	pServerInfo->m_byNonPvP = pServerGroup->m_abyNonPvpServer[pServerInfo->m_iIndex-1];
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	pServerInfo->m_bNonPvP = pServerGroup->m_bNonPvpServer[pServerInfo->m_iIndex-1];
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL

	int iTextIndex;
	if (iServerPercent >= 128)
	{
		iTextIndex = 560;	// "�غ���"
	}
	else if(iServerPercent >= 100)
	{
		iTextIndex = 561;	// "(Full)"
	}
	else
	{
		iTextIndex = 562;	// "����"
	}

#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	switch (pServerInfo->m_byNonPvP)
	{
	case 0:
		sprintf(pServerInfo->m_bName, "%s-%d %s", pServerGroup->m_szName,
			pServerInfo->m_iIndex, GlobalText[iTextIndex]);
		break;

	case 1:
		sprintf(pServerInfo->m_bName, "%s-%d(Non-PVP) %s", pServerGroup->m_szName,
			pServerInfo->m_iIndex, GlobalText[iTextIndex]);
		break;

	case 2:
		sprintf(pServerInfo->m_bName, "%s-%d(Gold PVP) %s", pServerGroup->m_szName,
			pServerInfo->m_iIndex, GlobalText[iTextIndex]);
		break;

	case 3:
		sprintf(pServerInfo->m_bName, "%s-%d(Gold) %s", pServerGroup->m_szName,
			pServerInfo->m_iIndex, GlobalText[iTextIndex]);
		break;
	}
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	if( pServerInfo->m_bNonPvP == true )		// NonPvP
	{
		sprintf(pServerInfo->m_bName, "%s-%d(Non-PVP) %s",pServerGroup->m_szName, pServerInfo->m_iIndex, GlobalText[iTextIndex]);
	}
	else
	{
		sprintf(pServerInfo->m_bName, "%s-%d %s",pServerGroup->m_szName, pServerInfo->m_iIndex, GlobalText[iTextIndex]);
	}
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	
	pServerGroup->InsertServerInfo(pServerInfo);
}

int CServerListManager::GetServerGroupSize()
{
	return m_mapServerGroup.size();
}

void CServerListManager::SetFirst()
{
	m_iterServerGroup = m_mapServerGroup.begin();
}

bool CServerListManager::GetNext(OUT CServerGroup* &pServerGroup)
{
	if(m_iterServerGroup == m_mapServerGroup.end())
	{
		pServerGroup = NULL;

		return false;
	}

	pServerGroup = m_iterServerGroup->second;
	
	m_iterServerGroup++;

	return true;
}

CServerGroup* CServerListManager::GetServerGroupByBtnPos(int iBtnPos)
{
	type_mapServerGroup::iterator iterServerGroup = m_mapServerGroup.begin();
	
	while(iterServerGroup != m_mapServerGroup.end())
	{
		if( iterServerGroup->second->m_iBtnPos == iBtnPos )
			return iterServerGroup->second;

		iterServerGroup++;
	}
	
	return NULL;
}

#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
void CServerListManager::SetSelectServerInfo(unicode::t_char* pszName, int iIndex,
											 int iCensorshipIndex, BYTE byNonPvP, bool bTestServer)
{
	strcpy(m_szSelectServerName, pszName);
	m_iSelectServerIndex = iIndex;
	m_iCensorshipIndex = iCensorshipIndex;
	m_byNonPvP = byNonPvP;
	m_bTestServer = bTestServer;
}
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
void CServerListManager::SetSelectServerInfo(unicode::t_char* pszName, int iIndex, int iCensorshipIndex, bool bNonPvP, bool bTestServer)
{
	strcpy(m_szSelectServerName, pszName);
	m_iSelectServerIndex = iIndex;
	m_iCensorshipIndex = iCensorshipIndex;
	m_bNonPvP = bNonPvP;
	m_bTestServer = bTestServer;
}
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL

unicode::t_char* CServerListManager::GetSelectServerName()
{
	return m_szSelectServerName;
}

int CServerListManager::GetSelectServerIndex()
{
	return m_iSelectServerIndex;
}

int CServerListManager::GetCensorshipIndex()
{
	return m_iCensorshipIndex;
}

#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
BYTE CServerListManager::GetNonPVPInfo()
{
	return m_byNonPvP;
}
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL

bool CServerListManager::IsNonPvP()
{
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	return bool(0x01 & GetNonPVPInfo());
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	return m_bNonPvP;
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
}

bool CServerListManager::IsTestServer()
{
	return m_bTestServer;
}

void CServerListManager::SetTotalServer(int iTotalServer)
{
	m_iTotalServer = iTotalServer;
}

int CServerListManager::GetTotalServer()
{
	return m_iTotalServer;
}

#endif // KJH_ADD_SERVER_LIST_SYSTEM
