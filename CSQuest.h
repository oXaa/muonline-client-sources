//////////////////////////////////////////////////////////////////////////
//  - ����Ʈ ���� -
//  
//  
//////////////////////////////////////////////////////////////////////////
#ifndef __CSQUEST_H__
#define __CSQUEST_H__

/*+++++++++++++++++++++++++++++++++++++
    INCLUDE.
+++++++++++++++++++++++++++++++++++++*/
#include "Singleton.h"

class CSQuest : public Singleton<CSQuest>
{
private:
	// �� ����Ʈ�� ����.
    BYTE getQuestState(int questIndex=-1);
	// ����Ʈ�� ���¸� �˻��Ѵ�.
    BYTE CheckQuestState(BYTE state=255);
	// �ش� ����Ʈ�� ��ȭ�� ã�´�.
    short FindQuestContext(QUEST_ATTRIBUTE* pQuest, int index);    
	// �䱸 ������ �˻��Ѵ�.
    bool CheckRequestCondition(QUEST_ATTRIBUTE* pQuest, bool bLastCheck=0); 
	// ���� ������ �˻��Ѵ�.
    bool CheckActCondition(QUEST_ATTRIBUTE* pQuest);              
    void RenderDevilSquare(void);         //  ���� ������.
    void RenderBloodCastle(void);         //  ����ĳ��.

public :
    CSQuest(void);
    ~CSQuest(void);

    //  Quest Init Functions
    bool OpenQuestScript(char* filename);     //  ����Ʈ ������ �д´�.
    bool IsInit(void);                        //  ����Ʈ �ʱ�ȭ?
    void clearQuest(void);                    //  ����Ʈ ����.

    //  Quest Setting.
    void setQuestLists( BYTE* byList, int num, int Class=-1 );	//  ����Ʈ ���������� �����Ѵ�. ( ó�� �������� �޴´�. )
    void setQuestList( int index, int result );					//  ����Ʈ �������� ���� ( �ش� ����Ʈ ������ �����Ѵ�. )
	BYTE getQuestState2( int questIndex );	//  �� ����Ʈ�� ����.
    void ShowQuestPreviewWindow( int index = -1 );  //  �ڽ��� ����Ʈ ������ �����ִ� â.
    void ShowQuestNpcWindow( int index = -1 );      //  NPC���� ��ȭ�� ���� ������ ����Ʈ ������ �����ִ� â.
    

	BYTE getCurrQuestState(void);				// ���� ����Ʈ�� ����.
	unicode::t_char* GetNPCName(BYTE byQuestIndex);
	unicode::t_char* getQuestTitle();			// ���� ����Ʈ Ÿ��Ʋ.
	unicode::t_char* getQuestTitle(BYTE byQuestIndex);		// ���� ����Ʈ Ÿ��Ʋ.
	unicode::t_char* getQuestTitleWindow();
    void SetEventCount(BYTE type, BYTE count);
	int GetEventCount(BYTE byType);
	DWORD GetNeedZen() { return m_dwNeedZen; }
	QUEST_ATTRIBUTE* GetCurQuestAttribute()
	{ return &m_Quest[m_byCurrQuestIndex]; }

	BYTE GetCurrQuestIndex(){ return m_byCurrQuestIndex; }
	void SetKillMobInfo(int* anKillMobInfo);
	bool ProcessNextProgress();
    void ShowDialogText(int iDialogIndex);
	bool BeQuestItem();
	int FindQuestItemsInInven(int nType, int nCount, int nLevel = -1);
	int GetKillMobCount(int nMobType);

private :
    BYTE    m_byClass;                          //  ���ΰ� Ŭ����.

    BYTE    m_byEventCount[TYPE_QUEST_END];      //  ���� ����Ʈ(�̺�Ʈ) ���� Ƚ��.
    QUEST_ATTRIBUTE m_Quest[MAX_QUESTS];        //  ����Ʈ ����.

    BYTE    m_byQuestList[MAX_QUESTS/4];        //  ����Ʈ ��������.
	//(0x00:���� ���� �ʾ���, 0x01:����Ʈ�� ����, 0x02:����Ʈ ���� �Ϸ�, 0x03:���� ����Ʈ ���� ����)
    BYTE    m_byCurrQuestIndex;                 //  ���� ����Ʈ �ε���.
    BYTE    m_byCurrQuestIndexWnd;              //  ����Ʈâ������ ���� ����Ʈ �ε���.

    BYTE    m_byStartQuestList;                 //  ����Ʈ ����Ʈâ�� 

    BYTE    m_byViewQuest;                      //  ����Ʈ â�� Ȱ��/��Ȱ��.
    short   m_shCurrPage;                       //  ���� ����Ʈ ���� ������.
    BYTE    m_byCurrState;                      //  ���� ����Ʈ ����.
    DWORD   m_dwNeedZen;                         //  �ʿ� ��.

    BYTE    m_byQuestType;                      //  ����Ʈ ����.
	bool	m_bOnce;							//  0xF3(�ɸ��� ����)���� 0xA0�� ���� ���°Ϳ� ����� äũ
	
	int 	m_anKillMobType[5];					//	�� �������� ����Ʈ ������ ���� ���� Ÿ��.
	int		m_anKillMobCount[5];				//	�� �������� ����Ʈ ������ ���� ���� ����.
	WORD	m_wNPCIndex;						//	NPC ����

    int     m_iStartX;
    int     m_iStartY;
};

#define g_csQuest CSQuest::GetSingleton ()

#endif
