//*****************************************************************************
// File: CQuestMng.cpp
//
// Desc: implementation of the CQuestMng class.
//
// producer: Ahn Sang-Gyu
//*****************************************************************************

#include "stdafx.h"
#include "QuestMng.h"
#include "./Utilities/Log/ErrorReport.h"
#include "wsclientinline.h"

#include <crtdbg.h>		// _ASSERT() ���.

#ifdef ASG_ADD_NEW_QUEST_SYSTEM

#ifdef ASG_ADD_UI_NPC_DIALOGUE
// NPC ��ȭ ��ũ��Ʈ ���ϸ�.
#ifdef USE_NPCDIALOGUETEST_BMD
#define	QM_NPCDIALOGUE_FILE			"Data\\Local\\NPCDialoguetest.bmd"
#else
#define	QM_NPCDIALOGUE_FILE			"Data\\Local\\NPCDialogue.bmd"
#endif
#endif	// ASG_ADD_UI_NPC_DIALOGUE

// ����Ʈ ���� ��ũ��Ʈ ���ϸ�.
#ifdef USE_QUESTPROGRESSTEST_BMD
#define	QM_QUESTPROGRESS_FILE		"Data\\Local\\QuestProgresstest.bmd"
#else
#define	QM_QUESTPROGRESS_FILE		"Data\\Local\\QuestProgress.bmd"
#endif

// ����Ʈ ��� ��ũ��Ʈ ���ϸ�.
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef USE_QUESTWORDSTEST_BMD
#define	QM_QUESTWORDS_FILE			string("Data\\Local\\"+g_strSelectedML+"\\QuestWordstest_"+g_strSelectedML+".bmd").c_str()
#else
#define	QM_QUESTWORDS_FILE			string("Data\\Local\\"+g_strSelectedML+"\\QuestWords_"+g_strSelectedML+".bmd").c_str()
#endif
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef USE_QUESTWORDSTEST_BMD
#define	QM_QUESTWORDS_FILE			"Data\\Local\\QuestWordstest.bmd"
#else
#define	QM_QUESTWORDS_FILE			"Data\\Local\\QuestWords.bmd"
#endif
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

CQuestMng g_QuestMng;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuestMng::CQuestMng()
{
	m_nNPCIndex = 0;
	::memset(m_szNPCName, 0, sizeof(char)*32);
}

CQuestMng::~CQuestMng()
{

}

//*****************************************************************************
// �Լ� �̸� : LoadQuestScript()
// �Լ� ���� : ����Ʈ ��ũ��Ʈ �ε�.
//*****************************************************************************
void CQuestMng::LoadQuestScript()
{
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	LoadNPCDialogueScript();
#endif	// ASG_ADD_UI_NPC_DIALOGUE
	LoadQuestProgressScript();
	LoadQuestWordsScript();
}

#ifdef ASG_ADD_UI_NPC_DIALOGUE
//*****************************************************************************
// �Լ� �̸� : LoadNPCDialogueScript()
// �Լ� ���� : NPC ��ȭ ��ũ��Ʈ �ε�.
//*****************************************************************************
void CQuestMng::LoadNPCDialogueScript()
{
	FILE* fp = ::fopen(QM_NPCDIALOGUE_FILE, "rb");
	if (fp == NULL)
	{
		char szMessage[256];
		::sprintf(szMessage, "%s file not found.\r\n", QM_NPCDIALOGUE_FILE);
		g_ErrorReport.Write(szMessage);
		::MessageBox(g_hWnd, szMessage, NULL, MB_OK);
		::PostMessage(g_hWnd, WM_DESTROY, 0, 0);
		return;
	}

	const int nSize = sizeof(DWORD) + sizeof(SNPCDialogue);
	BYTE abyBuffer[nSize];
	DWORD dwIndex = 0;
	SNPCDialogue sNPCDialogue;

	while (0 != ::fread(abyBuffer, nSize, 1, fp))
	{
		::BuxConvert(abyBuffer, nSize);

		::memcpy(&dwIndex, abyBuffer, sizeof(DWORD));
		::memcpy(&sNPCDialogue, abyBuffer + sizeof(DWORD), sizeof(SNPCDialogue));

		m_mapNPCDialogue.insert(make_pair(dwIndex, sNPCDialogue));
	}
	
	::fclose(fp);

#ifdef _BLUE_SERVER		//  ��缭������ ����
	DelAnswerAPDPUpBuff();
#endif // _BLUE_SERVER
}

#ifdef _BLUE_SERVER		//  ��缭������ ����
//*****************************************************************************
// �Լ� �̸� : DelAnswerAPDPUpBuff()
// �Լ� ���� : ���ù��� ������ ���� ȿ��(����� ����) ����.
//			   (������ ���� �δ�� NPC�� 0�� ��ȭ ���¸� �˻���)
//*****************************************************************************
void CQuestMng::DelAnswerAPDPUpBuff()
{
	const DWORD dwNPCIndex = 257;	// ������ ���� �δ�� NPC �ε���.
	const DWORD dwDlgState = 0;		// 0�� ��ȭ ����.
	const DWORD dwNPCDlgIndex = dwNPCIndex * 0x10000 + dwDlgState;

	NPCDialogueMap::iterator iter = m_mapNPCDialogue.find(dwNPCDlgIndex);
	if (iter == m_mapNPCDialogue.end())
		return;

	bool bLShift = false;
	int i;
	for (i = 0; i < QM_MAX_ND_ANSWER; ++i)
	{
		if (bLShift)
		{
			iter->second.m_anAnswer[(i-1)*2] = iter->second.m_anAnswer[i*2];
			iter->second.m_anAnswer[(i-1)*2+1] = iter->second.m_anAnswer[i*2+1];
		}
		else if (902 == iter->second.m_anAnswer[i*2+1])	// ���ù� ����� �����(902)�ΰ�?
			bLShift = true;		// ���� ���ù� ���� ���� ���ù����� ī��.
	}

	if (bLShift)
	{	// ������ ���ù��� 0���� �ʱ�ȭ.
		iter->second.m_anAnswer[(i-1)*2] = 0;
		iter->second.m_anAnswer[(i-1)*2+1] = 0;
	}
}
#endif // _BLUE_SERVER
#endif	// ASG_ADD_UI_NPC_DIALOGUE

//*****************************************************************************
// �Լ� �̸� : LoadQuestProgressScript()
// �Լ� ���� : ����Ʈ ��� ���� ��ũ��Ʈ �ε�.
//*****************************************************************************
void CQuestMng::LoadQuestProgressScript()
{
	FILE* fp = ::fopen(QM_QUESTPROGRESS_FILE, "rb");
	if (fp == NULL)
	{
		char szMessage[256];
		::sprintf(szMessage, "%s file not found.\r\n", QM_QUESTPROGRESS_FILE);
		g_ErrorReport.Write(szMessage);
		::MessageBox(g_hWnd, szMessage, NULL, MB_OK);
		::PostMessage(g_hWnd, WM_DESTROY, 0, 0);
		return;
	}

	const int nSize = sizeof(DWORD) + sizeof(SQuestProgress);
	BYTE abyBuffer[nSize];
	DWORD dwIndex = 0;
	SQuestProgress sQuestProgress;

	while (0 != ::fread(abyBuffer, nSize, 1, fp))
	{
		::BuxConvert(abyBuffer, nSize);

		::memcpy(&dwIndex, abyBuffer, sizeof(DWORD));
		::memcpy(&sQuestProgress, abyBuffer + sizeof(DWORD), sizeof(SQuestProgress));

		m_mapQuestProgress.insert(make_pair(dwIndex, sQuestProgress));
	}
	
	::fclose(fp);
}

//*****************************************************************************
// �Լ� �̸� : LoadQuestWordsScript()
// �Լ� ���� : ����Ʈ ��� ��ũ��Ʈ �ε�.
//*****************************************************************************
void CQuestMng::LoadQuestWordsScript()
{
	FILE* fp = ::fopen(QM_QUESTWORDS_FILE, "rb");
	if (fp == NULL)
	{
		char szMessage[256];
		::sprintf(szMessage, "%s file not found.\r\n", QM_QUESTWORDS_FILE);
		g_ErrorReport.Write(szMessage);
		::MessageBox(g_hWnd, szMessage, NULL, MB_OK);
		::PostMessage(g_hWnd, WM_DESTROY, 0, 0);
		return;
	}

#pragma pack(push, 1)
	struct SQuestWordsHeader
	{
		int		m_nIndex;				// ��� �ε���
#ifndef ASG_MOD_QUEST_WORDS_SCRIPTS	// ������ ����.
		short	m_nAction;				// �׼� �ִϸ��̼� ��ȣ
		BYTE	m_byActCount;			// �׼� �ִ� Ƚ��
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS
		short	m_nWordsLen;			// ��� ���� ����
	};
#pragma pack(pop)

	int nSize = sizeof(SQuestWordsHeader);
	SQuestWordsHeader sQuestWordsHeader;
	char szWords[1024];
#ifdef ASG_MOD_QUEST_WORDS_SCRIPTS
	string	strWords;
#else	// ASG_MOD_QUEST_WORDS_SCRIPTS
	SQuestWords sQuestWords;
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS
	
	while (0 != ::fread(&sQuestWordsHeader, nSize, 1, fp))
	{
		::BuxConvert((BYTE*)&sQuestWordsHeader, nSize);

		::fread(szWords, sQuestWordsHeader.m_nWordsLen, 1, fp);
		::BuxConvert((BYTE*)szWords, sQuestWordsHeader.m_nWordsLen);
#ifdef ASG_MOD_QUEST_WORDS_SCRIPTS
		strWords = szWords;

		m_mapQuestWords.insert(make_pair(sQuestWordsHeader.m_nIndex, strWords));
#else	// ASG_MOD_QUEST_WORDS_SCRIPTS
		sQuestWords.m_nAction = sQuestWordsHeader.m_nAction;
		sQuestWords.m_byActCount = sQuestWordsHeader.m_byActCount;
		sQuestWords.m_strWords = szWords;

		m_mapQuestWords.insert(make_pair(sQuestWordsHeader.m_nIndex, sQuestWords));
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS
	}
	
	::fclose(fp);
}

//*****************************************************************************
// �Լ� �̸� : SetQuestRequestReward()
// �Լ� ���� : �䱸, ���� ���� ����.
// �Ű� ���� : pRequestRewardPacket	: �䱸, ���� ����.
//*****************************************************************************
void CQuestMng::SetQuestRequestReward(BYTE* pbyRequestRewardPacket)
{
	LPPMSG_NPC_QUESTEXP_INFO pRequestRewardPacket
		= (LPPMSG_NPC_QUESTEXP_INFO)pbyRequestRewardPacket;
	DWORD dwQuestIndex = pRequestRewardPacket->m_dwQuestIndex;
	int i;

// ���� �ε����� �䱸����, ���� ������ ������ ���� ������ ������ �����Ѵ�.
	const SQuestRequestReward* pOldRequestReward = GetRequestReward(dwQuestIndex);
	if (pOldRequestReward)
	{
		for (i = 0; i < pOldRequestReward->m_byRequestCount; ++i)
			g_pNewItemMng->DeleteItem(pOldRequestReward->m_aRequest[i].m_pItem);
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		BYTE byRewardCount
			= pOldRequestReward->m_byGeneralRewardCount + pOldRequestReward->m_byRandRewardCount;
		for (i = 0; i < byRewardCount; ++i)
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		for (i = 0; i < pOldRequestReward->m_byRewardCount; ++i)
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
			g_pNewItemMng->DeleteItem(pOldRequestReward->m_aReward[i].m_pItem);
	}

// ���ο� �䱸����, ���� ���� ����.
	SQuestRequestReward sRequestReward;
	::memset(&sRequestReward, 0, sizeof(SQuestRequestReward));

// �䱸 ����.
	LPNPC_QUESTEXP_REQUEST_INFO pRequestPacket
		= (LPNPC_QUESTEXP_REQUEST_INFO)(pbyRequestRewardPacket + sizeof(PMSG_NPC_QUESTEXP_INFO));

	// '����'�̶�� ǥ���ؾ��ϱ� ������ ī��Ʈ�� 1.
	if (pRequestPacket->m_dwType == QUEST_REQUEST_NONE
		|| pRequestRewardPacket->m_byRequestCount == 0)
	{
		sRequestReward.m_byRequestCount = 1;
	}
	else
	{
		sRequestReward.m_byRequestCount = pRequestRewardPacket->m_byRequestCount;
		for (i = 0; i < sRequestReward.m_byRequestCount; ++i)
		{
			sRequestReward.m_aRequest[i].m_dwType = pRequestPacket->m_dwType;
			sRequestReward.m_aRequest[i].m_wIndex = pRequestPacket->m_wIndex;
			sRequestReward.m_aRequest[i].m_dwValue = pRequestPacket->m_dwValue;
#ifdef ASG_ADD_TIME_LIMIT_QUEST
			sRequestReward.m_aRequest[i].m_dwCurValue = pRequestPacket->m_dwCurValue;
#else	// ASG_ADD_TIME_LIMIT_QUEST
			sRequestReward.m_aRequest[i].m_wCurValue = pRequestPacket->m_wCurValue;
#endif	// ASG_ADD_TIME_LIMIT_QUEST
			if (pRequestPacket->m_dwType == QUEST_REQUEST_ITEM)
				sRequestReward.m_aRequest[i].m_pItem
				= g_pNewItemMng->CreateItem(pRequestPacket->m_byItemInfo);
			++pRequestPacket;
		}
	}

// ����.
	LPNPC_QUESTEXP_REWARD_INFO pRewardPacket
		= (LPNPC_QUESTEXP_REWARD_INFO)(pbyRequestRewardPacket + sizeof(PMSG_NPC_QUESTEXP_INFO)
			+ sizeof(NPC_QUESTEXP_REQUEST_INFO) * 5);

	// '����'�̶�� ǥ���ؾ��ϱ� ������ ī��Ʈ�� 1.
	if (pRewardPacket->m_dwType == QUEST_REWARD_NONE
		|| pRequestRewardPacket->m_byRewardCount == 0)
	{
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		sRequestReward.m_byGeneralRewardCount = 1;
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		sRequestReward.m_byRewardCount = 1;
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	}
	else
	{
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		sRequestReward.m_byRandGiveCount = pRequestRewardPacket->m_byRandRewardCount;

	// �Ϲ� ����� ���� ������ �з�.
		BYTE byGeneralCount = 0;
		BYTE byRandCount = 0;
		SQuestReward aTempRandReward[5];
		::memset(aTempRandReward, 0, sizeof(SQuestReward) * 5);

		for (i = 0; i < pRequestRewardPacket->m_byRewardCount; ++i)
		{
			if (QUEST_REWARD_TYPE(pRewardPacket->m_dwType & 0xFFE0) == QUEST_REWARD_RANDOM)	// ���� �����ΰ�?
			{
			// ���������̸� �ӽ� �����ҿ� ����.
				aTempRandReward[byRandCount].m_dwType = pRewardPacket->m_dwType & 0x1F;	// QUEST_REWARD_RANDOM�� �ڸ�.
				aTempRandReward[byRandCount].m_wIndex = pRewardPacket->m_wIndex;
				aTempRandReward[byRandCount].m_dwValue = pRewardPacket->m_dwValue;
				if (aTempRandReward[byRandCount].m_dwType == QUEST_REWARD_ITEM)
					aTempRandReward[byRandCount].m_pItem
						= g_pNewItemMng->CreateItem(pRewardPacket->m_byItemInfo);
				++byRandCount;
			}
			else
			{
			// �Ϲݺ����� ��� sRequestReward.m_aReward�� ���� ä�� �ִ´�.
				sRequestReward.m_aReward[byGeneralCount].m_dwType = pRewardPacket->m_dwType;
				sRequestReward.m_aReward[byGeneralCount].m_wIndex = pRewardPacket->m_wIndex;
				sRequestReward.m_aReward[byGeneralCount].m_dwValue = pRewardPacket->m_dwValue;
				if (pRewardPacket->m_dwType == QUEST_REWARD_ITEM)
					sRequestReward.m_aReward[byGeneralCount].m_pItem
						= g_pNewItemMng->CreateItem(pRewardPacket->m_byItemInfo);
				++byGeneralCount;
			}

			++pRewardPacket;
		}

		sRequestReward.m_byGeneralRewardCount = byGeneralCount;
		sRequestReward.m_byRandRewardCount = byRandCount;

	// ���� ������ sRequestReward.m_aReward�� ä�� �ִ´�.
		for (i = 0; i < sRequestReward.m_byRandRewardCount; ++i)
			sRequestReward.m_aReward[byGeneralCount++] = aTempRandReward[i];
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		sRequestReward.m_byRewardCount = pRequestRewardPacket->m_byRewardCount;
		for (i = 0; i < sRequestReward.m_byRewardCount; ++i)
		{
			sRequestReward.m_aReward[i].m_dwType = pRewardPacket->m_dwType;
			sRequestReward.m_aReward[i].m_wIndex = pRewardPacket->m_wIndex;
			sRequestReward.m_aReward[i].m_dwValue = pRewardPacket->m_dwValue;
			if (pRewardPacket->m_dwType == QUEST_REWARD_ITEM)
				sRequestReward.m_aReward[i].m_pItem
				= g_pNewItemMng->CreateItem(pRewardPacket->m_byItemInfo);
			++pRewardPacket;
		}
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	}

	m_mapQuestRequestReward[dwQuestIndex] = sRequestReward;
}

//*****************************************************************************
// �Լ� �̸� : GetRequestReward()
// �Լ� ���� : ����Ʈ �ε����� �䱸����, ���� ���� ���.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : ����Ʈ �ε����� �䱸����, ���� ����.
//*****************************************************************************
const SQuestRequestReward* CQuestMng::GetRequestReward(DWORD dwQuestIndex)
{
	QuestRequestRewardMap::const_iterator iter = m_mapQuestRequestReward.find(dwQuestIndex);
	if (iter == m_mapQuestRequestReward.end())
		return NULL;

	return &(iter->second);
}

//*****************************************************************************
// �Լ� �̸� : SetNPC()
// �Լ� ���� : NPC ����.
// �Ű� ���� : nNPCIndex	: NPC �ε���.
//*****************************************************************************
void CQuestMng::SetNPC(int nNPCIndex)
{
	m_nNPCIndex = nNPCIndex;
	::strcpy(m_szNPCName, ::getMonsterName(nNPCIndex));
}

//*****************************************************************************
// �Լ� �̸� : GetNPCIndex()
// �Լ� ���� : NPC �ε��� ���.
// ��ȯ ��	 : NPC �ε���.
//*****************************************************************************
int CQuestMng::GetNPCIndex()
{
	return m_nNPCIndex;
}

//*****************************************************************************
// �Լ� �̸� : GetNPCName()
// �Լ� ���� : NPC �̸� ���.
// ��ȯ ��	 : NPC �̸�.
//*****************************************************************************
char* CQuestMng::GetNPCName()
{
	return m_szNPCName;
}

//*****************************************************************************
// �Լ� �̸� : SetCurQuestProgress()
// �Լ� ���� : ���׿� �´� ����Ʈ ����â ����.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
//*****************************************************************************
void CQuestMng::SetCurQuestProgress(DWORD dwQuestIndex)
{
	AddCurQuestIndexList(dwQuestIndex);

// QS��(���� 2����Ʈ)�� 255(0x00FF)�� ����Ʈ ����.
	if (LOWORD(dwQuestIndex) == 0x00FF)
	{
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_QUEST_PROGRESS);
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC);
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC

		g_pChatListBox->AddText("", GlobalText[2814], SEASON3B::TYPE_ERROR_MESSAGE);	// 2814 "����Ʈ�� ���������� �Ϸ��Ͽ����ϴ�"

		return;
	}

	// NPC�� ����Ʈ ����â.
	if (0 == m_mapQuestProgress[dwQuestIndex].m_byUIType)
	{
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		g_pQuestProgress->SetContents(dwQuestIndex);
		if (!g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
			g_pNewUISystem->Show(SEASON3B::INTERFACE_QUEST_PROGRESS);
#endif	// ASG_ADD_UI_QUEST_PROGRESS
	}
	// ������, ��Ÿ�� ����Ʈ ���� â.
	else
	{
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		g_pQuestProgressByEtc->SetContents(dwQuestIndex);
		if (!g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
			g_pNewUISystem->Show(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC);
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC
	}
}

//*****************************************************************************
// �Լ� �̸� : GetWords()
// �Լ� ���� : ����Ʈ ��� ���.
// �Ű� ���� : nWordsIndex	: ��� �ε���.
// ��ȯ ��	 : ����Ʈ ���.
//*****************************************************************************
const char* CQuestMng::GetWords(int nWordsIndex)
{
	QuestWordsMap::const_iterator iter = m_mapQuestWords.find(nWordsIndex);
	if (iter == m_mapQuestWords.end())
		return NULL;

#ifdef ASG_MOD_QUEST_WORDS_SCRIPTS
	return iter->second.c_str();
#else	// ASG_MOD_QUEST_WORDS_SCRIPTS
	return iter->second.m_strWords.c_str();
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS
}

#ifdef ASG_ADD_UI_NPC_DIALOGUE
//*****************************************************************************
// �Լ� �̸� : GetNPCDlgNPCWords()
// �Լ� ���� : NPC ��ȭ�� NPC ��� ���.
// �Ű� ���� : dwDlgState	: ��ȭ ���� ��ȣ.
// ��ȯ ��	 : NPC ���.
//*****************************************************************************
const char* CQuestMng::GetNPCDlgNPCWords(DWORD dwDlgState)
{
	if (0 == m_nNPCIndex)
		return NULL;

	DWORD dwNPCDlgIndex = (DWORD)m_nNPCIndex * 0x10000 + dwDlgState;

	NPCDialogueMap::const_iterator iter = m_mapNPCDialogue.find(dwNPCDlgIndex);
	if (iter == m_mapNPCDialogue.end())
		return NULL;

	return GetWords(iter->second.m_nNPCWords);
}

//*****************************************************************************
// �Լ� �̸� : GetNPCDlgAnswer()
// �Լ� ���� : NPC ��ȭ�� ���ù� ���.
// �Ű� ���� : dwDlgState	: ��ȭ ���� ��ȣ.
//			   nAnswer		: ���ù���ȣ (0 ~ 9).
// ��ȯ ��	 : ���ù�.
//*****************************************************************************
const char* CQuestMng::GetNPCDlgAnswer(DWORD dwDlgState, int nAnswer)
{
	if (0 == m_nNPCIndex)
		return NULL;

	_ASSERT(0 <= nAnswer || nAnswer < QM_MAX_ND_ANSWER);

	DWORD dwNPCDlgIndex = (DWORD)m_nNPCIndex * 0x10000 + dwDlgState;

	NPCDialogueMap::const_iterator iter = m_mapNPCDialogue.find(dwNPCDlgIndex);
	if (iter == m_mapNPCDialogue.end())
		return NULL;

	DWORD nNowAnswer = iter->second.m_anAnswer[nAnswer*2];
	if (0 == nNowAnswer)
		return NULL;

	return GetWords(nNowAnswer);
}

//*****************************************************************************
// �Լ� �̸� : GetNPCDlgAnswerResult()
// �Լ� ���� : NPC ��ȭ�� ���ù� ��� �� ���.
// �Ű� ���� : dwDlgState	: ��ȭ ���� ��ȣ.
//			   nAnswer		: ���ù���ȣ (0 ~ 9).
// ��ȯ ��	 : ���ù� ��� ��. -1�̸� ���ù��� ����.
//*****************************************************************************
int CQuestMng::GetNPCDlgAnswerResult(DWORD dwDlgState, int nAnswer)
{
	if (0 == m_nNPCIndex)
		return NULL;

	_ASSERT(0 <= nAnswer || nAnswer < QM_MAX_ND_ANSWER);

	DWORD dwNPCDlgIndex = (DWORD)m_nNPCIndex * 0x10000 + dwDlgState;

	NPCDialogueMap::const_iterator iter = m_mapNPCDialogue.find(dwNPCDlgIndex);
	if (iter == m_mapNPCDialogue.end())
		return -1;

	DWORD nNowAnswer = iter->second.m_anAnswer[nAnswer*2];
	if (0 == nNowAnswer)
		return -1;

	return iter->second.m_anAnswer[nAnswer*2+1];
}
#endif	// ASG_ADD_UI_NPC_DIALOGUE

//*****************************************************************************
// �Լ� �̸� : GetNPCWords()
// �Լ� ���� : ����Ʈ ������ NPC ��� ���.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : NPC ���.
//*****************************************************************************
const char* CQuestMng::GetNPCWords(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	if (iter == m_mapQuestProgress.end())
		return NULL;

	return GetWords(iter->second.m_nNPCWords);
}

//*****************************************************************************
// �Լ� �̸� : GetPlayerWords()
// �Լ� ���� : ����Ʈ ������ �÷��̾� ��� ���.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : �÷��̾� ���.
//*****************************************************************************
const char* CQuestMng::GetPlayerWords(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	if (iter == m_mapQuestProgress.end())
		return NULL;

	return GetWords(iter->second.m_nPlayerWords);
}

//*****************************************************************************
// �Լ� �̸� : GetAnswer()
// �Լ� ���� : ����Ʈ ������ ���ù� ���.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
//			   nAnswer		: ���ù���ȣ (0 ~ 4).
// ��ȯ ��	 : ���ù�.
//*****************************************************************************
const char* CQuestMng::GetAnswer(DWORD dwQuestIndex, int nAnswer)
{
	_ASSERT(0 <= nAnswer || nAnswer < QM_MAX_ANSWER);

	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	if (iter == m_mapQuestProgress.end())
		return NULL;

	DWORD nNowAnswer = iter->second.m_anAnswer[nAnswer];
	if (0 == nNowAnswer)
		return NULL;

	return GetWords(nNowAnswer);
}

//*****************************************************************************
// �Լ� �̸� : GetSubject()
// �Լ� ���� : ����Ʈ ������ ����Ʈ �ε����� ���� ���.
// ��ȯ ��	 : ����Ʈ �ε����� ����.
//*****************************************************************************
const char* CQuestMng::GetSubject(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	if (iter == m_mapQuestProgress.end())
		return NULL;

	return GetWords(iter->second.m_nSubject);
}

//*****************************************************************************
// �Լ� �̸� : GetSummary()
// �Լ� ���� : ����Ʈ ������ ����Ʈ �ε����� ��� ���.
// ��ȯ ��	 : ����Ʈ �ε����� ���.
//*****************************************************************************
const char* CQuestMng::GetSummary(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	if (iter == m_mapQuestProgress.end())
		return NULL;

	return GetWords(iter->second.m_nSummary);
}

//*****************************************************************************
// �Լ� �̸� : IsRequestRewardQS()
// �Լ� ���� : �䱸����, ���� ������ �ִ� QS(Quest State)�ΰ�?
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : �䱸����, ���� ������ ������ true.
//*****************************************************************************
bool CQuestMng::IsRequestRewardQS(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	_ASSERT(iter != m_mapQuestProgress.end());	// ����Ʈ ������ �����Ͽ�����.

	// ���ù� 0��° ���� 0�̸� �䱸����, ���� ������ �ִ� QS.
	if (0 == iter->second.m_anAnswer[0])
		return true;
	else
		return false;	
}

//*****************************************************************************
// �Լ� �̸� : GetRequestRewardText()
// �Լ� ���� : �䱸����, ���� �ؽ�Ʈ�� ����.
// �Ű� ���� : aDest		: SRequestRewardText����ü �迭 �̸�.
//			   nDestCount	: SRequestRewardText����ü �迭 ����.
//			   dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : �䱸���� ���� ����.
//*****************************************************************************
bool CQuestMng::GetRequestRewardText(SRequestRewardText* aDest, int nDestCount, DWORD dwQuestIndex)
{
	SQuestRequestReward* pRequestReward = &m_mapQuestRequestReward[dwQuestIndex];

	// GlobalText[2809] "�䱸 ����", GlobalText[2810] "��     ��",
	//GlobalText[3082] "���� ����(%lu���� ����)"�� ����ϱ� ���� 3���� �� �ʿ�.
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	if (pRequestReward->m_byRequestCount + pRequestReward->m_byGeneralRewardCount
		+ pRequestReward->m_byRandRewardCount + 3 > nDestCount)
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	if (pRequestReward->m_byRequestCount + pRequestReward->m_byRewardCount + 2 > nDestCount)
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		return false;

	::memset(aDest, 0, sizeof(SRequestRewardText) * nDestCount);

	int nLine = 0;
	bool bRequestComplete = true;
	int i;

// �䱸 ����.
	aDest[nLine].m_hFont = g_hFontBold;
	aDest[nLine].m_dwColor = ARGB(255, 179, 230, 77);
	::strcpy(aDest[nLine++].m_szText, GlobalText[2809]);	// 2809 "�䱸 ����"

	SQuestRequest* pRequestInfo;
	for (i = 0; i < pRequestReward->m_byRequestCount; ++i, ++nLine)
	{
		pRequestInfo = &pRequestReward->m_aRequest[i];

		aDest[nLine].m_hFont = g_hFont;
		aDest[nLine].m_eRequestReward = RRC_REQUEST;
		aDest[nLine].m_dwType = pRequestInfo->m_dwType;
		aDest[nLine].m_wIndex = pRequestInfo->m_wIndex;
		aDest[nLine].m_pItem = pRequestInfo->m_pItem;

		switch (pRequestInfo->m_dwType)
		{
		case QUEST_REQUEST_NONE:
			aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);
			::strcpy(aDest[nLine].m_szText, GlobalText[1361]);	// 1361 "����"
			break;

#ifdef ASG_ADD_TIME_LIMIT_QUEST
		case QUEST_REQUEST_MONSTER:
		case QUEST_REQUEST_ITEM:
		case QUEST_REQUEST_LEVEL:
		case QUEST_REQUEST_ZEN:
		case QUEST_REQUEST_PVP_POINT:
			if (pRequestInfo->m_dwCurValue < pRequestInfo->m_dwValue)
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);
			
			switch (pRequestInfo->m_dwType)
			{
			case QUEST_REQUEST_MONSTER:
				::sprintf(aDest[nLine].m_szText, "Mon.: %s x %lu/%lu",
					::getMonsterName(int(pRequestInfo->m_wIndex)),
					MIN(pRequestInfo->m_dwCurValue, pRequestInfo->m_dwValue),
					pRequestInfo->m_dwValue);
				break;
			case QUEST_REQUEST_ITEM:
				{
					char szItemName[32];
					::GetItemName((int)pRequestInfo->m_pItem->Type,
						(pRequestInfo->m_pItem->Level>>3)&15, szItemName);
					::sprintf(aDest[nLine].m_szText, "Item: %s x %lu/%lu", szItemName,
						MIN(pRequestInfo->m_dwCurValue, pRequestInfo->m_dwValue),
						pRequestInfo->m_dwValue);
				}
				break;
			case QUEST_REQUEST_LEVEL:
				::sprintf(aDest[nLine].m_szText, "Level: %lu %s",
					pRequestInfo->m_dwValue, GlobalText[2812]);	// 2812 "�̻�"
				break;
			case QUEST_REQUEST_ZEN:
				::sprintf(aDest[nLine].m_szText, "Zen : %lu", pRequestInfo->m_dwValue);
				break;
			case QUEST_REQUEST_PVP_POINT:
				::sprintf(aDest[nLine].m_szText, GlobalText[3278],	// 3278	"�� �ս��� x %lu/%lu"
					MIN(pRequestInfo->m_dwCurValue, pRequestInfo->m_dwValue),
					pRequestInfo->m_dwValue);
				break;
			}
			break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST

#ifndef ASG_ADD_TIME_LIMIT_QUEST	// ������ ����.
		case QUEST_REQUEST_MONSTER:
			if ((DWORD)pRequestInfo->m_wCurValue < pRequestInfo->m_dwValue)
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

			::sprintf(aDest[nLine].m_szText, "Mon.: %s x %lu/%lu",
				::getMonsterName(int(pRequestInfo->m_wIndex)),
				MIN((DWORD)pRequestInfo->m_wCurValue, pRequestInfo->m_dwValue),
				pRequestInfo->m_dwValue);
			break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST	// ������ ����.

		case QUEST_REQUEST_SKILL:
#ifdef ASG_ADD_TIME_LIMIT_QUEST
			if (0 == pRequestInfo->m_dwCurValue)
#else	// ASG_ADD_TIME_LIMIT_QUEST
			if (0 == pRequestInfo->m_wCurValue)
#endif	// ASG_ADD_TIME_LIMIT_QUEST
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

			::sprintf(aDest[nLine].m_szText, "Skill: %s",
				SkillAttribute[pRequestInfo->m_wIndex].Name);
			break;

#ifndef ASG_ADD_TIME_LIMIT_QUEST	// ������ ����.
		case QUEST_REQUEST_ITEM:
			if ((DWORD)pRequestInfo->m_wCurValue < pRequestInfo->m_dwValue)
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

			char szItemName[32];
			::GetItemName((int)pRequestInfo->m_pItem->Type, (pRequestInfo->m_pItem->Level>>3)&15,
				szItemName);
			::sprintf(aDest[nLine].m_szText, "Item: %s x %lu/%lu", szItemName,
				MIN((DWORD)pRequestInfo->m_wCurValue, pRequestInfo->m_dwValue),
				pRequestInfo->m_dwValue);
			break;

		case QUEST_REQUEST_LEVEL:
			if ((DWORD)pRequestInfo->m_wCurValue < pRequestInfo->m_dwValue)
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

			::sprintf(aDest[nLine].m_szText, "Level: %lu %s",
				pRequestInfo->m_dwValue, GlobalText[2812]);	// 2812 "�̻�"
			break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST	// ������ ����.

		case QUEST_REQUEST_TUTORIAL:
#ifdef ASG_ADD_TIME_LIMIT_QUEST
			if (pRequestInfo->m_dwCurValue == 1)
#else	// ASG_ADD_TIME_LIMIT_QUEST
			if (pRequestInfo->m_wCurValue == 1)
#endif	// ASG_ADD_TIME_LIMIT_QUEST
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);
			else
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			
			switch (dwQuestIndex)
			{
			case 0x10009:	// ĳ����â ����.
				::sprintf(aDest[nLine].m_szText, "%s", GlobalText[2819]);	// 2819 "ĳ���� â(C) ����"
				break;
			case 0x1000F:	// ���â ����.
				::sprintf(aDest[nLine].m_szText, "%s", GlobalText[2820]);	// 2820 "��� â(I, V) ����"
				break;
			}
			break;

		case QUEST_REQUEST_BUFF:
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
			{
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
#ifdef ASG_ADD_TIME_LIMIT_QUEST
				if (pRequestInfo->m_dwCurValue == 0)
#else	// ASG_ADD_TIME_LIMIT_QUEST
				if (pRequestInfo->m_wCurValue == 0)
#endif	// ASG_ADD_TIME_LIMIT_QUEST
				{
					aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
					bRequestComplete = false;
				}
				else
					aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

				const BuffInfo buffinfo = g_BuffInfo((eBuffState)pRequestInfo->m_wIndex);
				::sprintf(aDest[nLine].m_szText, "Bonus: %s", buffinfo.s_BuffName);
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
			}
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
			break;

#ifdef ASG_ADD_QUEST_REQUEST_NPC_SEARCH
		case QUEST_REQUEST_NPC_TALK:	//pRequestInfo->m_wIndex�� NPC �ε����� �������� Ŭ�󿡼��� ��� ����.
			if (pRequestInfo->m_dwCurValue == 0)
			{
				aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
				bRequestComplete = false;
			}
			else
				aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

			::sprintf(aDest[nLine].m_szText, "%s", GlobalText[3249]);	// 3249	"�Ƿ��� ã��"
			break;
#endif	// ASG_ADD_QUEST_REQUEST_NPC_SEARCH

#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		case QUEST_REQUEST_EVENT_MAP_MON_KILL:
		case QUEST_REQUEST_EVENT_MAP_BLOOD_GATE:
		case QUEST_REQUEST_EVENT_MAP_USER_KILL:
		case QUEST_REQUEST_EVENT_MAP_DEVIL_POINT:
			{
#ifdef ASG_ADD_TIME_LIMIT_QUEST
				if (pRequestInfo->m_dwCurValue < pRequestInfo->m_dwValue)
#else	// ASG_ADD_TIME_LIMIT_QUEST
				if ((DWORD)pRequestInfo->m_wCurValue < pRequestInfo->m_dwValue)
#endif	// ASG_ADD_TIME_LIMIT_QUEST
				{
					aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
					bRequestComplete = false;
				}
				else
					aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

				int nTextIndex = 0;
				switch (pRequestInfo->m_dwType)
				{
				case QUEST_REQUEST_EVENT_MAP_MON_KILL:
					nTextIndex = 3074;	// 3074	"ī����ĳ�� Lv.%lu ������ x %lu/%lu"
					break;
				case QUEST_REQUEST_EVENT_MAP_BLOOD_GATE:
					nTextIndex = 3077;	// 3077	"����ĳ�� Lv.%lu ���� �ı� x %lu/%lu"
					break;
				case QUEST_REQUEST_EVENT_MAP_USER_KILL:
					nTextIndex = 3075;	// 3075	"ī����ĳ�� Lv.%lu �÷��̾� x %lu/%lu"
					break;
				case QUEST_REQUEST_EVENT_MAP_DEVIL_POINT:
					nTextIndex = 3079;	// 3079	"�Ǹ��Ǳ��� Lv.%lu Point x %lu/%lu"
					break;
				}
				::sprintf(aDest[nLine].m_szText, GlobalText[nTextIndex], pRequestInfo->m_wIndex,
#ifdef ASG_ADD_TIME_LIMIT_QUEST
					MIN(pRequestInfo->m_dwCurValue, pRequestInfo->m_dwValue),
#else	// ASG_ADD_TIME_LIMIT_QUEST
					MIN((DWORD)pRequestInfo->m_wCurValue, pRequestInfo->m_dwValue),
#endif	// ASG_ADD_TIME_LIMIT_QUEST
					pRequestInfo->m_dwValue);
			}
			break;

		case QUEST_REQUEST_EVENT_MAP_CLEAR_BLOOD:
		case QUEST_REQUEST_EVENT_MAP_CLEAR_CHAOS:
		case QUEST_REQUEST_EVENT_MAP_CLEAR_DEVIL:
		case QUEST_REQUEST_EVENT_MAP_CLEAR_ILLUSION:
			{
#ifdef ASG_ADD_TIME_LIMIT_QUEST
				if (pRequestInfo->m_dwCurValue == 0)
#else	// ASG_ADD_TIME_LIMIT_QUEST
				if (pRequestInfo->m_wCurValue == 0)
#endif	// ASG_ADD_TIME_LIMIT_QUEST
				{
					aDest[nLine].m_dwColor = ARGB(255, 255, 30, 30);
					bRequestComplete = false;
				}
				else
					aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);

				int nTextIndex = 0;
				switch (pRequestInfo->m_dwType)
				{
				case QUEST_REQUEST_EVENT_MAP_CLEAR_BLOOD:
					nTextIndex = 3078;	// 3078	"����ĳ�� Lv.%lu Ŭ����"
					break;
				case QUEST_REQUEST_EVENT_MAP_CLEAR_CHAOS:
					nTextIndex = 3076;	// 3076	"ī����ĳ�� Lv.%lu Ŭ����"
					break;
				case QUEST_REQUEST_EVENT_MAP_CLEAR_DEVIL:
					nTextIndex = 3080;	// 3080	"�Ǹ��Ǳ��� Lv.%lu Ŭ����"
					break;
				case QUEST_REQUEST_EVENT_MAP_CLEAR_ILLUSION:
					nTextIndex = 3081;	// 3081	"ȯ����� Lv.%lu Ŭ����"
					break;
				}
				::sprintf(aDest[nLine].m_szText, GlobalText[nTextIndex], pRequestInfo->m_wIndex);
			}
			break;
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
		}
		aDest[nLine].m_szText[QM_MAX_REQUEST_REWARD_TEXT_LEN - 1] = 0;	// ���� ���� ���� ���� ��� ���� ���� ������ �־���.
	}

// ����.
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	BYTE byRewardCount;
	SQuestReward* pRewardInfo;
	i = 0;
	int j;
	for (j = 0; j < 2; ++j)
	{
		if (0 == j && pRequestReward->m_byGeneralRewardCount)	// �Ϲ� ���� ������ �ִٸ�.
			::strcpy(aDest[nLine].m_szText, GlobalText[2810]);		// 2810 "��     ��"
		else if (1 == j && pRequestReward->m_byRandRewardCount)	// ���� ���� ������ �ִٸ�. 
			::sprintf(aDest[nLine].m_szText, GlobalText[3082], pRequestReward->m_byRandGiveCount);// 3082 "���� ����(%lu���� ����)"
		else
			continue;
		aDest[nLine].m_hFont = g_hFontBold;
		aDest[nLine++].m_dwColor = ARGB(255, 179, 230, 77);

		byRewardCount = 0 == j
			? pRequestReward->m_byGeneralRewardCount
			: pRequestReward->m_byGeneralRewardCount + pRequestReward->m_byRandRewardCount;
		for (; i < byRewardCount; ++i, ++nLine)
		{
			pRewardInfo = &pRequestReward->m_aReward[i];
			
			aDest[nLine].m_hFont = g_hFont;
			aDest[nLine].m_dwColor = 0 == j ? ARGB(255, 223, 191, 103) : ARGB(255, 103, 103, 223);
			aDest[nLine].m_eRequestReward = RRC_REWARD;
			aDest[nLine].m_dwType = pRewardInfo->m_dwType;
			aDest[nLine].m_wIndex = pRewardInfo->m_wIndex;
			aDest[nLine].m_pItem = pRewardInfo->m_pItem;
		
			switch (pRewardInfo->m_dwType)
			{
			case QUEST_REWARD_NONE:
				::strcpy(aDest[nLine].m_szText, GlobalText[1361]);	// 1361 "����"
				break;
				
			case QUEST_REWARD_EXP:
				::sprintf(aDest[nLine].m_szText, "Exp.: %lu", pRewardInfo->m_dwValue);
				break;
				
			case QUEST_REWARD_ZEN:
				::sprintf(aDest[nLine].m_szText, "Zen: %lu", pRewardInfo->m_dwValue);
				break;
				
			case QUEST_REWARD_ITEM:
				char szItemName[32];
				::GetItemName((int)pRewardInfo->m_pItem->Type, (pRewardInfo->m_pItem->Level>>3)&15,
					szItemName);
				::sprintf(aDest[nLine].m_szText, "Item: %s x %lu",
					szItemName, pRewardInfo->m_dwValue);
				break;
				
			case QUEST_REWARD_BUFF:
				{
					const BuffInfo buffinfo = g_BuffInfo((eBuffState)pRewardInfo->m_wIndex);
					::sprintf(aDest[nLine].m_szText, "Bonus: %s x %lu%s", buffinfo.s_BuffName,
						pRewardInfo->m_dwValue, GlobalText[2300]);	// '��'
				}
				break;
				
	#ifdef ASG_ADD_GENS_SYSTEM
			case QUEST_REWARD_CONTRIBUTE:
				::sprintf(aDest[nLine].m_szText, GlobalText[2994], pRewardInfo->m_dwValue);	// 2994 "�⿩��: %lu"
				break;
	#endif	// ASG_ADD_GENS_SYSTEM
			}
			aDest[nLine].m_szText[QM_MAX_REQUEST_REWARD_TEXT_LEN - 1] = 0;
		}
	}
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
	aDest[nLine].m_hFont = g_hFontBold;
	aDest[nLine].m_dwColor = ARGB(255, 179, 230, 77);
	::strcpy(aDest[nLine++].m_szText, GlobalText[2810]);	// 2810 "��     ��"

	SQuestReward* pRewardInfo;
	for (i = 0; i < pRequestReward->m_byRewardCount; ++i, ++nLine)
	{
		pRewardInfo = &pRequestReward->m_aReward[i];

		aDest[nLine].m_hFont = g_hFont;
		aDest[nLine].m_dwColor = ARGB(255, 223, 191, 103);
		aDest[nLine].m_eRequestReward = RRC_REWARD;
		aDest[nLine].m_dwType = pRewardInfo->m_dwType;
		aDest[nLine].m_wIndex = pRewardInfo->m_wIndex;
		aDest[nLine].m_pItem = pRewardInfo->m_pItem;

		switch (pRewardInfo->m_dwType)
		{
		case QUEST_REWARD_NONE:
			::strcpy(aDest[nLine].m_szText, GlobalText[1361]);	// 1361 "����"
			break;

		case QUEST_REWARD_EXP:
			::sprintf(aDest[nLine].m_szText, "Exp.: %lu", pRewardInfo->m_dwValue);
			break;

		case QUEST_REWARD_ZEN:
			::sprintf(aDest[nLine].m_szText, "Zen: %lu", pRewardInfo->m_dwValue);
			break;
			
		case QUEST_REWARD_ITEM:
			char szItemName[32];
			::GetItemName((int)pRewardInfo->m_pItem->Type, (pRewardInfo->m_pItem->Level>>3)&15,
				szItemName);
			::sprintf(aDest[nLine].m_szText, "Item: %s x %lu",
				szItemName, pRewardInfo->m_dwValue);
			break;
			
		case QUEST_REWARD_BUFF:
			{
				const BuffInfo buffinfo = g_BuffInfo((eBuffState)pRewardInfo->m_wIndex);
				::sprintf(aDest[nLine].m_szText, "Bonus: %s x %lu%s", buffinfo.s_BuffName,
					pRewardInfo->m_dwValue, GlobalText[2300]);	// '��'
			}
			break;

#ifdef ASG_ADD_GENS_SYSTEM
		case QUEST_REWARD_CONTRIBUTE:
			::sprintf(aDest[nLine].m_szText, GlobalText[2994], pRewardInfo->m_dwValue);	// 2994 "�⿩��: %lu"
			break;
#endif	// ASG_ADD_GENS_SYSTEM
		}
		aDest[nLine].m_szText[QM_MAX_REQUEST_REWARD_TEXT_LEN - 1] = 0;
	}
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE

	return bRequestComplete;
}

//*****************************************************************************
// �Լ� �̸� : SetEPRequestRewardState()
// �Լ� ���� : ���Ǽҵ� �䱸, ���� ���� ����.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
//			   ProgressState: �䱸������ �ִ� QS ���� ���϶��� true.
//*****************************************************************************
void CQuestMng::SetEPRequestRewardState(DWORD dwQuestIndex, bool ProgressState)
{
	m_mapEPRequestRewardState[HIWORD(dwQuestIndex)] = ProgressState;
}

//*****************************************************************************
// �Լ� �̸� : IsEPRequestRewardState()
// �Լ� ���� : ���Ǽҵ尡 �䱸, ���� �����ΰ�?.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : �䱸������ �ִ� QS ���� ���϶��� true. �� �ܴ� false.
//*****************************************************************************
bool CQuestMng::IsEPRequestRewardState(DWORD dwQuestIndex)
{
	WORD wEP = HIWORD(dwQuestIndex);

	map<WORD, bool>::const_iterator iter = m_mapEPRequestRewardState.find(wEP);
	if (iter == m_mapEPRequestRewardState.end())
		return false;

	return m_mapEPRequestRewardState[wEP];
}

//*****************************************************************************
// �Լ� �̸� : IsQuestByEtc()
// �Լ� ���� : ����Ʈ �ε���(dwQuestIndex)�� ��Ÿ ��Ȳ�� ���� ����Ʈ�ΰ�?
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
// ��ȯ ��	 : �䱸������ �ִ� QS ���� ���϶��� true. �� �ܴ� false.
//*****************************************************************************
bool CQuestMng::IsQuestByEtc(DWORD dwQuestIndex)
{
	QuestProgressMap::const_iterator iter = m_mapQuestProgress.find(dwQuestIndex);
	_ASSERT(iter != m_mapQuestProgress.end());

	if (iter->second.m_byUIType == 1)	// ��Ÿ ��Ȳ�� ���� ����Ʈ ����(1)�̶��.
		return true;
	else
		return false;
}

//*****************************************************************************
// �Լ� �̸� : SetQuestIndexByEtcList()
// �Լ� ���� : ��Ÿ ��Ȳ�� ���� ����Ʈ �ε��� ����Ʈ ����.
// �Ű� ���� : adwSrcQuestIndex	: ���� ����Ʈ �ε��� �迭 �ּ�.
//								 (NULL�̸� ����Ʈ �ʱ�ȭ)
//			   nIndexCount		: ���� ����Ʈ �ε��� ����.
//*****************************************************************************
void CQuestMng::SetQuestIndexByEtcList(DWORD* adwSrcQuestIndex, int nIndexCount)
{
	m_listQuestIndexByEtc.clear();

	if (NULL == adwSrcQuestIndex)
		return;
	
	int i;
	for (i = 0; i < nIndexCount; ++i)
		m_listQuestIndexByEtc.push_back(adwSrcQuestIndex[i]);
}

//*****************************************************************************
// �Լ� �̸� : IsQuestIndexByEtcListEmpty()
// �Լ� ���� : ��Ÿ ��Ȳ�� ���� ����Ʈ �ε��� ����Ʈ�� ����ִ°�?
// ��ȯ ��	 : true�̸� ��� ����.
//*****************************************************************************
bool CQuestMng::IsQuestIndexByEtcListEmpty()
{
	return m_listQuestIndexByEtc.empty();
}

//*****************************************************************************
// �Լ� �̸� : SendQuestIndexByEtcSelection()
// �Լ� ���� : ��Ÿ ��Ȳ�� ���� ����Ʈ �ε����� �����ؼ� ������ �˸�.
//*****************************************************************************
void CQuestMng::SendQuestIndexByEtcSelection()
{
	if (IsQuestIndexByEtcListEmpty())
		return;

	DWordList::iterator iter = m_listQuestIndexByEtc.begin();
	SendQuestSelection(*iter, 0);
}

//*****************************************************************************
// �Լ� �̸� : DelQuestIndexByEtcList()
// �Լ� ���� : ��Ÿ ��Ȳ�� ���� ����Ʈ �ε��� ����Ʈ���� �Ű�����(dwQuestIndex)
//			  �� ���� ���Ǽҵ� ����Ʈ ����.
// �Ű� ���� : dwQuestIndex	: ������ ���Ǽҵ��� ����Ʈ �ε���.
//*****************************************************************************
void CQuestMng::DelQuestIndexByEtcList(DWORD dwQuestIndex)
{
	// QS�� 0�̸� �������� ����Ʈ ����Ʈ�� �ȳ����Ƿ� �����ϸ� �ȵ�.
	//�ٽ� �α��� �ϱ� ������ �ش� ���Ǽҵ� ����Ʈ�� ������ ����� ���� ����.
	if (0x0000 == LOWORD(dwQuestIndex))
		return;

	// ���� EP(���Ǽҵ�)�� ����Ʈ�� ������ ����.
	DWordList::iterator iter;
	for (iter = m_listQuestIndexByEtc.begin(); iter != m_listQuestIndexByEtc.end(); advance(iter, 1))
	{
		if (HIWORD(*iter) == HIWORD(dwQuestIndex))
		{
			m_listQuestIndexByEtc.erase(iter);
			break;
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : SetCurQuestIndexList()
// �Լ� ���� : ���� ���� ���� ����Ʈ �ε��� ����Ʈ ����.
// �Ű� ���� : adwCurQuestIndex	: ���� �������� ����Ʈ �ε��� �迭 �ּ�.
//			   nIndexCount		: ���� �������� ����Ʈ �ε��� ����.
//*****************************************************************************
void CQuestMng::SetCurQuestIndexList(DWORD* adwCurQuestIndex, int nIndexCount)
{
	m_listCurQuestIndex.clear();

	int i;
	for (i = 0; i < nIndexCount; ++i)
#ifdef LJH_FIX_BUG_DISPLAYING_NULL_TITLED_QUEST_LIST
		if (GetSubject(adwCurQuestIndex[i]) != NULL)
			m_listCurQuestIndex.push_back(adwCurQuestIndex[i]);
#else  //LJH_FIX_BUG_DISPLAYING_NULL_TITLED_QUEST_LIST
		m_listCurQuestIndex.push_back(adwCurQuestIndex[i]);
#endif //LJH_FIX_BUG_DISPLAYING_NULL_TITLED_QUEST_LIST

	// ����Ʈ ����â�� �������� ����Ʈ ����Ʈ �ڽ� ����.
	g_pMyQuestInfoWindow->SetCurQuestList(&m_listCurQuestIndex);
}

//*****************************************************************************
// �Լ� �̸� : AddCurQuestIndexList()
// �Լ� ���� : ���� ���� ����Ʈ �ε��� ����Ʈ�� ����Ʈ �ε���(dwQuestIndex) ��
//			  ��.
//			   ����Ʈ ���� ���� ���Ǽҵ��� ����Ʈ�� �ִٸ� dwQuestIndex�� �߰�
//            �� ����.
//			   QS(����Ʈ ����)�� 0, 255�� ���� ����Ʈ ���� ���� ���Ǽҵ��� ��
//			  ��Ʈ �ε����� �ִٸ� �߰��� �ʰ� ������ ��.
// �Ű� ���� : dwQuestIndex	: �߰��� ����Ʈ �ε���.
//*****************************************************************************
void CQuestMng::AddCurQuestIndexList(DWORD dwQuestIndex)
{
	WORD wEP = HIWORD(dwQuestIndex);	// ���Ǽҵ�.
	WORD wQS = LOWORD(dwQuestIndex);	// ����Ʈ ����.
	bool bNotFound = true;

	DWordList::iterator iter;
	for (iter = m_listCurQuestIndex.begin(); iter != m_listCurQuestIndex.end(); advance(iter, 1))
	{
		if (wEP == HIWORD(*iter))	// ���� ���Ǽҵ��ΰ�?
		{
#ifdef ASG_FIX_QUEST_GIVE_UP
			// 0, 255�� �ƴϸ� �ٷ� �տ� ����.
			if (wQS != 0x0000 && wQS != 0x00ff)
#else	// ASG_FIX_QUEST_GIVE_UP
			// 0, 254, 255�� �ƴϸ� �ٷ� �տ� ����.
			if (wQS != 0x0000 && wQS != 0x00fe && wQS != 0x00ff)
#endif	// ASG_FIX_QUEST_GIVE_UP
				m_listCurQuestIndex.insert(iter, dwQuestIndex);

			// ���� ���Ǽҵ��� �������� ����Ʈ �ε��� ����.
			m_listCurQuestIndex.erase(iter);

			bNotFound = false;
			break;
		}
	}

	if (bNotFound)	// �� ã�Ҵٸ�.
	{
#ifdef ASG_FIX_QUEST_GIVE_UP
		// 0, 255�� �ƴϸ� ����Ʈ �ڿ� �߰�.
		if (wQS != 0x0000 && wQS != 0x00ff)
#else	// ASG_FIX_QUEST_GIVE_UP
		// 0, 254, 255�� �ƴϸ� ����Ʈ �ڿ� �߰�.
		if (wQS != 0x0000 && wQS != 0x00fe && wQS != 0x00ff)
#endif	// ASG_FIX_QUEST_GIVE_UP
			m_listCurQuestIndex.push_back(dwQuestIndex);
	}

	m_listCurQuestIndex.sort();	// ����Ʈ ����.

	// ����Ʈ ����â�� �������� ����Ʈ ����Ʈ �ڽ� ����.
	g_pMyQuestInfoWindow->SetCurQuestList(&m_listCurQuestIndex);
}

//*****************************************************************************
// �Լ� �̸� : RemoveCurQuestIndexList()
// �Լ� ���� : ����Ʈ ���� ���� ���Ǽҵ��� ����Ʈ�� �ִٸ� �ش� �ε��� ����.
// �Ű� ���� : dwQuestIndex	: ����Ʈ �ε���.
//*****************************************************************************
void CQuestMng::RemoveCurQuestIndexList(DWORD dwQuestIndex)
{
	WORD wEP = HIWORD(dwQuestIndex);	// ���Ǽҵ�.

	DWordList::iterator iter;
	for (iter = m_listCurQuestIndex.begin(); iter != m_listCurQuestIndex.end(); advance(iter, 1))
	{
		if (wEP == HIWORD(*iter))	// ���� ���Ǽҵ��ΰ�?
		{	
			// ���� ���Ǽҵ��� �������� ����Ʈ �ε��� ����.
			m_listCurQuestIndex.erase(iter);			
			break;
		}
	}
	
	// ����Ʈ ����â�� �������� ����Ʈ ����Ʈ �ڽ� ����.
	g_pMyQuestInfoWindow->SetCurQuestList(&m_listCurQuestIndex);
}

//*****************************************************************************
// �Լ� �̸� : IsIndexInCurQuestIndexList()
// �Լ� ���� : ���� ���� ����Ʈ �ε��� ����Ʈ�� ����Ʈ �ε���(dwQuestIndex)��
//			  �ִ°�?
// �Ű� ���� : dwQuestIndex	: ã�� ����Ʈ �ε���.
// ��ȯ ��	 : true�̸� ����.
//*****************************************************************************
bool CQuestMng::IsIndexInCurQuestIndexList(DWORD dwQuestIndex)
{
	DWordList::iterator iter;
	for (iter = m_listCurQuestIndex.begin(); iter != m_listCurQuestIndex.end(); advance(iter, 1))
	{
		if (*iter == dwQuestIndex)
			return true;
	}

	return false;
}

#endif	// ASG_ADD_NEW_QUEST_SYSTEM