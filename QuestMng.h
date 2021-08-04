//*****************************************************************************
// File: QuestMng.h
//
// Desc: interface for the QuestMng class.
//		 �ű� ����Ʈ �Ŵ��� Ŭ����.(09.05.20)
//
//		 �̹��� �߰��� �ű� ����Ʈ �ý����� ����Ʈ �ε��� ������ �����ȴ�.
//		 ����Ʈ �ε����� DWORD������ ���� 2����Ʈ�� ���Ǽҵ�(EP), ���� 2����Ʈ�� ����Ʈ ������Ʈ(QS
//		)�� �����Ǿ� �ִ�.
//		 ����Ʈ�� ũ�� �ϳ��� ���Ǽҵ�(EP)�� �����ȴ�. QS�� 255�̸� ����Ʈ �Ϸ�.
//		 ���ܷ� EP���� 0�̸� ����Ʈ�� �ƴ� NPC�� ���� ������� �з��Ѵ�.(�� : ������ ����, ���� ��
//		�� ��)
//		 ����Ʈ �ε����� ������ �������� ��� ��ũ��Ʈ�� �����ϸ�, �ش� �ε����� ���� Ŭ���̾�Ʈ
//		��ũ��Ʈ�� �����Ѵ�.(QuestProgress.txt, QuestWords(kor).txt)
//		 �ش� �ε����� '�䱸 ����', '����'�� �������� ��� ��ũ��Ʈ�� �����Ѵ�.
//		 ���� ���� �����ϴ� ������ ���� ����Ʈ �ý��ۿ��� �ϳ��� ����Ʈ�� �����ϱ� ���ؼ� ������ Ŭ
//		���̾�Ʈ�� �����ؾ��ϱ� ������ ���ʿ��� �߸��� ���� �����ϴ� ��� ����ʿ��� �߸��� ���� ��
//		���ߴ��� �˾Ƴ��Ⱑ �����.
//
// producer: Ahn Sang-Gyu
//*****************************************************************************

#if !defined(AFX_QUESTMNG_H__1ACBD446_412D_488D_9E0F_AC5BC22BEFE8__INCLUDED_)
#define AFX_QUESTMNG_H__1ACBD446_412D_488D_9E0F_AC5BC22BEFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef ASG_ADD_NEW_QUEST_SYSTEM

#include "WSclient.h"

#ifdef ASG_ADD_UI_NPC_DIALOGUE
#define QM_MAX_ND_ANSWER	10	// NPC ��ȭ ���ù� ����.
#endif	// ASG_ADD_UI_NPC_DIALOGUE
#define QM_MAX_ANSWER		5	// ��� �ִ� ����
#define QM_MAX_REQUEST_REWARD_TEXT_LEN	64	// �䱸 ����, ���� �ؽ�Ʈ �ִ� ���ڼ�.

#ifdef ASG_ADD_UI_NPC_DIALOGUE
// NPC ��ȭ ����ü
struct SNPCDialogue
{
	int		m_nNPCWords;			// NPC ��� ��ȣ
	int		m_anAnswer[QM_MAX_ND_ANSWER*2];	// ���ù� �� �����
};
#endif	// ASG_ADD_UI_NPC_DIALOGUE

// ����Ʈ ��� ���� ����ü
#pragma pack(push, 1)
struct SQuestProgress
{
	BYTE	m_byUIType;				// UI Ÿ��(0: NPC�� ���� ����Ʈ ����â, 1: ��Ÿ ��Ȳ���� ���� ����Ʈ ����â)
	int		m_nNPCWords;			// NPC ��� ��ȣ
	int		m_nPlayerWords;			// �÷��̾� ��� ��ȣ
	int		m_anAnswer[QM_MAX_ANSWER];	// ��� ��ȣ
	int		m_nSubject;				// ���� ��ȣ
	int		m_nSummary;				// ��� ��ȣ
};
#pragma pack(pop)

// ����Ʈ ��� ����ü
#ifndef ASG_MOD_QUEST_WORDS_SCRIPTS		// ������ ����.
struct SQuestWords
{
	short	m_nAction;				// �׼� �ִϸ��̼� ��ȣ
	BYTE	m_byActCount;			// �׼� �ִ� Ƚ��
	string	m_strWords;				// ���
};
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS

// �䱸���� ����ü
struct SQuestRequest
{
	DWORD	m_dwType;
	WORD	m_wIndex;
	DWORD	m_dwValue;
#ifdef ASG_ADD_TIME_LIMIT_QUEST
	DWORD	m_dwCurValue;
#else	// ASG_ADD_TIME_LIMIT_QUEST
	WORD	m_wCurValue;
#endif	// ASG_ADD_TIME_LIMIT_QUEST
	ITEM*	m_pItem;
};

// ���� ���� ����ü
struct SQuestReward
{	
	DWORD	m_dwType;
	WORD	m_wIndex;
	DWORD	m_dwValue;
	ITEM*	m_pItem;
};

// �䱸 ����, ���� ���� ����ü
#ifdef ASG_ADD_QUEST_REQUEST_REWARD_TYPE
struct SQuestRequestReward
{
	BYTE	m_byRequestCount;			// �䱸 ���� ����
	BYTE	m_byGeneralRewardCount;		// �Ϲ� ���� ����
	BYTE	m_byRandRewardCount;		// ���� ���� ����
	BYTE	m_byRandGiveCount;			// ���� ���� ���� ����
	SQuestRequest	m_aRequest[5];		// �䱸 ����
	SQuestReward	m_aReward[5];		// ����(�Ϲ�+������ 5���� ������ �ȵ�)
};
#else	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE
struct SQuestRequestReward
{
	BYTE	m_byRequestCount;		// �䱸 ���� ����
	BYTE	m_byRewardCount;		// ���� ����
	SQuestRequest	m_aRequest[5];	// �䱸 ����
	SQuestReward	m_aReward[5];	// ����
};
#endif	// ASG_ADD_QUEST_REQUEST_REWARD_TYPE

enum REQUEST_REWARD_CLASSIFY
{
	RRC_NONE	= 0,
	RRC_REQUEST	= 1,
	RRC_REWARD	= 2
};

// �䱸 ����, ���� �ؽ�Ʈ
struct SRequestRewardText
{
	HFONT	m_hFont;
	DWORD	m_dwColor;
	char	m_szText[QM_MAX_REQUEST_REWARD_TEXT_LEN];
	REQUEST_REWARD_CLASSIFY	m_eRequestReward;		// 
	DWORD	m_dwType;
	WORD	m_wIndex;
	ITEM*	m_pItem;
};

using namespace std;

#ifdef ASG_ADD_UI_NPC_DIALOGUE
typedef map<DWORD, SNPCDialogue> NPCDialogueMap;
#endif	// ASG_ADD_UI_NPC_DIALOGUE
typedef map<DWORD, SQuestProgress> QuestProgressMap;
#ifdef ASG_MOD_QUEST_WORDS_SCRIPTS
typedef map<int, string> QuestWordsMap;
#else	// ASG_MOD_QUEST_WORDS_SCRIPTS
typedef map<int, SQuestWords> QuestWordsMap;
#endif	// ASG_MOD_QUEST_WORDS_SCRIPTS
typedef map<DWORD, SQuestRequestReward> QuestRequestRewardMap;
typedef list<DWORD> DWordList;

class CQuestMng  
{
protected:
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	NPCDialogueMap			m_mapNPCDialogue;		// NPC ��ȭ("NPC �ε��� * 0x10000 + ��ȭ ���� ��ȣ"�� �˻�)
#endif	// ASG_ADD_UI_NPC_DIALOGUE
	QuestProgressMap		m_mapQuestProgress;		// ����Ʈ ��� ����(����Ʈ �ε����� �˻�)
	QuestWordsMap			m_mapQuestWords;		// ����Ʈ ���(��� ��ȣ�� �˻�)
	QuestRequestRewardMap	m_mapQuestRequestReward;// ����Ʈ �䱸 ����, ����(����Ʈ �ε����� �˻�)

	map<WORD, bool>			m_mapEPRequestRewardState;	// ����Ʈ �䱸 ������ �ִ� QS�� ���������� �ƴ��� ����(EP ��ȣ�� �˻�)
							//����Ʈ Ȯ�� ��ư ������ �������� true, ���� �� ���� false�� ���� ��.

	int		m_nNPCIndex;			// ���� ���õ� NPC �ε���.
	char	m_szNPCName[32];		// ���� ���õ� NPC �̸�.

	DWordList				m_listQuestIndexByEtc;	// ��Ÿ ��Ȳ�� ���� ����Ʈ �ε��� ����Ʈ.
	DWordList				m_listCurQuestIndex;	// ���� �������� ����Ʈ ����Ʈ.

public:
	CQuestMng();
	virtual ~CQuestMng();

	void LoadQuestScript();
	void SetQuestRequestReward(BYTE* pbyRequestRewardPacket);
	const SQuestRequestReward* GetRequestReward(DWORD dwQuestIndex);

	void SetNPC(int nNPCIndex);
	int GetNPCIndex();
	char* GetNPCName();

	void SetCurQuestProgress(DWORD dwQuestIndex);

	const char* GetWords(int nWordsIndex);
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	const char* GetNPCDlgNPCWords(DWORD dwDlgState);
	const char* GetNPCDlgAnswer(DWORD dwDlgState, int nAnswer);
	int GetNPCDlgAnswerResult(DWORD dwDlgState, int nAnswer);
#endif	// ASG_ADD_UI_NPC_DIALOGUE
	const char* GetNPCWords(DWORD dwQuestIndex);
	const char* GetPlayerWords(DWORD dwQuestIndex);
	const char* GetAnswer(DWORD dwQuestIndex, int nAnswer);
	const char* GetSubject(DWORD dwQuestIndex);
	const char* GetSummary(DWORD dwQuestIndex);
	bool IsRequestRewardQS(DWORD dwQuestIndex);
	bool GetRequestRewardText(SRequestRewardText* aDest, int nDestCount, DWORD dwQuestIndex);
	void SetEPRequestRewardState(DWORD dwQuestIndex, bool ProgressState);
	bool IsEPRequestRewardState(DWORD dwQuestIndex);
	bool IsQuestByEtc(DWORD dwQuestIndex);

	void SetQuestIndexByEtcList(DWORD* adwSrcQuestIndex, int nIndexCount);
	bool IsQuestIndexByEtcListEmpty();
	void SendQuestIndexByEtcSelection();
	void DelQuestIndexByEtcList(DWORD dwQuestIndex);

	void SetCurQuestIndexList(DWORD* adwCurQuestIndex, int nIndexCount);
	void AddCurQuestIndexList(DWORD dwQuestIndex);
	void RemoveCurQuestIndexList(DWORD dwQuestIndex);
	bool IsIndexInCurQuestIndexList(DWORD dwQuestIndex);

protected:
#ifdef ASG_ADD_UI_NPC_DIALOGUE
	void LoadNPCDialogueScript();
#ifdef _BLUE_SERVER		//  ��缭������ ����
	void DelAnswerAPDPUpBuff();
#endif // _BLUE_SERVER
#endif	// ASG_ADD_UI_NPC_DIALOGUE
	void LoadQuestProgressScript();
	void LoadQuestWordsScript();
};

extern CQuestMng g_QuestMng;

#endif	// ASG_ADD_NEW_QUEST_SYSTEM

#endif // !defined(AFX_QUESTMNG_H__1ACBD446_412D_488D_9E0F_AC5BC22BEFE8__INCLUDED_)
