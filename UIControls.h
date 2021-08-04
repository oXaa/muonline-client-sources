#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#include "zzzinfomation.h"

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#include "MultiLanguage.h"
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
#define UIMAX_TEXT_LINE			150
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

inline DWORD _ARGB(BYTE a, BYTE r, BYTE g, BYTE b) { return (a << 24) + (b << 16) + (g << 8) + (r); }

#ifndef ASG_ADD_NEW_QUEST_SYSTEM		// ������ ����.
void CutText2(const char* Text,char* Text1,char* Text2,int Length);
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
#ifdef KJH_FIX_BTS158_TEXT_CUT_ROUTINE
int CutStr(const char* pszText, char * pTextOut, const int iTargetPixelWidth, const int iMaxOutLine, const int iOutStrLength, const int iFirstLineTab = 0);
#endif // KJH_FIX_BTS158_TEXT_CUT_ROUTINE
int CutText3(const char* pszText, char* pTextOut, const int TargetWidth, const int iMaxOutLine, const int iOutStrLength, const int iFirstLineTab = 0, const BOOL bReverseWrite = FALSE);
// pszText : ���� �ؽ�Ʈ
// pTextOut : ��ȯ�� �ؽ�Ʈ �迭�� ù��° �ּ� Array[4][100] -> Array[0]
// TargetWidth : ��ǥ �ʺ�
// iiMaxOutLine : �ִ� ���� ��
// iOutStrLength : �ִ� �ؽ�Ʈ ����
// iFirstLineTab : ù ���� ��� ���� (px)
// bReverseWrite : ���� �ؽ�Ʈ�� �迭 �ڿ������� ������ ����
void CutText4(const char* pszSource, char* pszResult1, char* pszResult2, int iCutCount);

void RenderCheckBox(int iPos_x, int iPos_y, BOOL bFlag);

const int COORDINATE_TYPE_LEFT_TOP = 1;
const int COORDINATE_TYPE_LEFT_DOWN = 2;

BOOL CheckMouseIn(int iPos_x, int iPos_y, int iWidth, int iHeight, int CoordType = COORDINATE_TYPE_LEFT_TOP);

#define ID_UICEDIT 0x0001
#define SLIDEHELP_TIMER 1003

using namespace std;

enum UISTATES
{
	UISTATE_NORMAL = 0, UISTATE_RESIZE, UISTATE_SCROLL, UISTATE_HIDE,
	UISTATE_MOVE, UISTATE_READY, UISTATE_DISABLE
};

enum UIOPTIONS
{
	UIOPTION_NULL = 0,				// �ɼ� ����
	UIOPTION_NUMBERONLY = 1,		// ���ڸ� �Է� ����
	UIOPTION_SERIALNUMBER = 2,		// ���ڿ� ���빮�ڸ� �Է� ����
	UIOPTION_ENTERIMECHKOFF = 4,	// ���͸� ������ IME ���¸� �ٲ��� ���� (���� ������ ������� �ʴ� �Է�â, ��Ƽ���ε�)
#ifdef LJH_ADD_RESTRICTION_ON_ID
	UIOPTION_PAINTBACK = 8,			// ����� ���������� ĥ����
	UIOPTION_NOLOCALIZEDCHARACTERS = 16	// �ٱ��������� ���̵�� ���� �Է�(����θ� �Է��� �� �ְ� ��ȹ)
#else  //LJH_ADD_RESTRICTION_ON_ID
	UIOPTION_PAINTBACK = 8			// ����� ���������� ĥ����
#endif //LJH_ADD_RESTRICTION_ON_ID

};

#ifndef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
const int MAX_LETTERTEXT_LENGTH = 1000;
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
typedef struct
{
	BOOL	m_bIsSelected;
	char	m_szID[MAX_ID_SIZE+1];
	char	m_szText[MAX_TEXT_LENGTH + 1];
	int		m_iType;
	int		m_iColor;
	UINT	m_uiEmptyLines;
} WHISPER_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	char	m_szID[MAX_ID_SIZE+1];
	BYTE	m_Number;
	BYTE	m_Server;
	BYTE	m_GuildStatus;
} GUILDLIST_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	DWORD	m_dwUIID;		// ������ ID
	char	m_szTitle[64];	// ������ Ÿ��Ʋ
	int		m_iStatus;		// ������ ����
} WINDOWLIST_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	DWORD	m_dwLetterID;	// ���� ��ȣ (����)
	char	m_szID[MAX_ID_SIZE+1];	// �������
	char	m_szText[MAX_TEXT_LENGTH + 1];			// ����
	char	m_szDate[16];			// ��¥
	char	m_szTime[16];			// �ð�
	BOOL	m_bIsRead;				// ���� ����
} LETTERLIST_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	char	m_szText[MAX_LETTERTEXT_LENGTH + 1];
} LETTER_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	char	m_szContent[60];
} GUILDLOG_TEXT;
typedef struct
{
	BOOL	m_bIsSelected;
	BYTE	GuildMark[64];
	char	szName[8+1];
	int		nMemberCount;
} UNIONGUILD_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	char	szName[8+1];
	int		nCount;
	BYTE	byIsGiveUp;
	BYTE	bySeqNum;
} BCDECLAREGUILD_TEXT;

typedef struct tagMOVECOMMAND_TEXT
{
	BOOL	m_bIsSelected;
	BOOL	m_bCanMove;
	char	szMainMapName[32];		//. Main map name
	char	szSubMapName[32];		//. Substitute map name
	int		iReqLevel;				//. required level
	int		iReqZen;				//. required zen
	int		iGateNum;				//. Gate number
} MOVECOMMAND_TEXT;

typedef struct
{
	BOOL	m_bIsSelected;
	char	szName[8+1];
	BYTE	byJoinSide;
	BYTE	byGuildInvolved;
	int		iGuildScore;
} BCGUILD_TEXT;

typedef struct _UNMIX_TEXT
{
	BOOL	m_bIsSelected;
	int		m_iInvenIdx;
	char	m_cLevel;

	_UNMIX_TEXT() : m_bIsSelected(false), m_iInvenIdx(-1), m_cLevel(-1) {}

}UNMIX_TEXT;

#ifdef ADD_SOCKET_MIX
typedef struct _SOCKETLIST_TEXT
{
	BOOL	m_bIsSelected;
	int		m_iSocketIndex;		// ���� ��ȣ
	char	m_szText[64 + 1];	// ���� ���� ���ڿ�
} SOCKETLIST_TEXT;
#endif	// ADD_SOCKET_MIX

////////////////////////////////////////////////////////////////////////////////////////////////////

enum UI_MESSAGE_ENUM
{							// Func						|Param1				|Param2
	UI_MESSAGE_NULL = 0,	// NULL

	// ������ ������ �޽���
	UI_MESSAGE_SELECT,		// ������ ����				|���õ� ������ID
	UI_MESSAGE_HIDE,		// ������ ����				|���� ������ ID
	UI_MESSAGE_MAXIMIZE,	// ������ �ִ�ȭ			|�ִ�ȭ ��ų ������ ID
	UI_MESSAGE_CLOSE,		// ������ �ݱ�				|���� ������ID
	UI_MESSAGE_BOTTOM,		// ������ ���� �� ������	|������ ���� ������ ID

	// ������ �޽���
	UI_MESSAGE_SELECTED,	// ������ ���õ�
	UI_MESSAGE_TEXTINPUT,	// �ؽ�Ʈ �Է� ����
	UI_MESSAGE_P_MOVE,		// (�θ�)�����찡 �̵�
	UI_MESSAGE_P_RESIZE,	// (�θ�)�����찡 ũ������
	UI_MESSAGE_BTNLCLICK,	// ��ư Ŭ��				|Ŭ���� ��ư ID
	UI_MESSAGE_TXTRETURN,	// �ؽ�Ʈ�� ����			|������ ������ ID	|������ �ؽ�Ʈ �ּ�
							//												 (delete�������)
	UI_MESSAGE_YNRETURN,	// ���� �� ����				|������ ������ ID	|���� �� (1:Yes, 2:No)

	// ����Ʈ �޽���
	UI_MESSAGE_LISTDBLCLICK,// ����Ʈ�׸� ����Ŭ��		|������ ������ ID
	UI_MESSAGE_LISTSCRLTOP,	// ����Ʈ ��ũ�� ������
	UI_MESSAGE_LISTSELUP,	// ����Ʈ ���� ����
	UI_MESSAGE_LISTSELDOWN	// ����Ʈ ���� �Ʒ���
};

struct UI_MESSAGE
{
	int m_iMessage;
	int m_iParam1;
	int m_iParam2;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIMessage
{
public:
	CUIMessage() {}
	virtual ~CUIMessage() { m_MessageList.clear(); }

	void SendUIMessage(int iMessage, int iParam1, int iParam2);
	void GetUIMessage();
protected:
	deque<UI_MESSAGE> m_MessageList;
	UI_MESSAGE m_WorkMessage;			// ���� ó���� �޽��� �����
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIControl : public CUIMessage
{
public:
	CUIControl();
	virtual ~CUIControl() {}

	DWORD GetUIID() { return m_dwUIID; }
	void SetParentUIID(DWORD dwParentUIID) { m_dwParentUIID = dwParentUIID; }
	DWORD GetParentUIID() { return m_dwParentUIID; }
	virtual void SetState(int iState);
	int GetState();
	void SetOption(int iOption) { m_iOptions = iOption; }
	BOOL CheckOption(int iOption) { return m_iOptions & iOption; }

	void SendUIMessageDirect(int iMessage, int iParam1, int iParam2);

	void SetPosition(int iPos_x, int iPos_y);
	int GetPosition_x() { return m_iPos_x; }
	int GetPosition_y() { return m_iPos_y; }
	virtual void SetSize(int iWidth, int iHeight);
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	virtual void SetArrangeType(int iArrangeType = 0, int iRelativePos_x = 0, int iRelativePos_y = 0);
	virtual void SetResizeType(int iResizeType = 0, int iRelativeWidth = 0, int iRelativeHeight = 0);
	virtual void Render() {}
	virtual BOOL DoAction(BOOL bMessageOnly = FALSE);	// �޽���, ���콺 �׼� ���� ó���Ѵ�.

protected:
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DoActionSub()					{ return;	}
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DoActionSub(BOOL bMessageOnly) {			}
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoMouseAction() { return TRUE; }
	virtual void DefaultHandleMessage();			// �⺻ �޽��� ó�� �Լ�
	virtual BOOL HandleMessage() { return FALSE; }	// Ŭ������ �޽��� ó�� �Լ� (FALSE�� DefaultHandleMessage ����)

protected:
	DWORD m_dwUIID;		// ���� ID
	DWORD m_dwParentUIID;	// �θ� ID
	int m_iState;
	int m_iOptions;
	int m_iPos_x, m_iPos_y;
	int m_iWidth, m_iHeight;
	int m_iArrangeType;		// ���� Ÿ�� (0: ��->��;��->��, 1: ��->��;��->��, 2:��->��;��->��, 3:��->��;��->��)
	int m_iResizeType;		// ũ�� ���� Ÿ�� (0: ����;����, 1: ���;����, 2: ����;���, 3: ���;���)
	int m_iRelativePos_x, m_iRelativePos_y;
	int m_iRelativeWidth, m_iRelativeHeight;
	int m_iCoordType;		// ��ǥ Ÿ��
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIButton : public CUIControl
{
public:
	CUIButton();
	virtual ~CUIButton();

	virtual void Init(DWORD dwButtonID, const char* pszCaption);
	virtual void SetCaption(const char* pszCaption);
	virtual BOOL DoMouseAction();
	virtual void Render();

protected:
	DWORD m_dwButtonID;
	char* m_pszCaption;
	BOOL m_bMouseState;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum UILISTBOX_SCROLL_TYPE { UILISTBOX_SCROLL_DOWNUP = 0, UILISTBOX_SCROLL_UPDOWN };

template <class T>
class CUITextListBox : public CUIControl
{
public:
	CUITextListBox();
	virtual ~CUITextListBox();
	
	virtual void Clear();
	virtual void AddText() {}									// �����Ϳ� �°� ��ӹ޾� ���

	virtual void Render();
	virtual void Scrolling(int iValue);

	virtual int GetBoxSize() { return m_iNumRenderLine; }
	virtual void SetBoxSize(int iLineNum) { m_iNumRenderLine = iLineNum; }
	virtual void SetNumRenderLine(int iLine) { m_iNumRenderLine = iLine; }
	virtual void Resize(int iValue);
	virtual BOOL HandleMessage();

	virtual void ResetCheckedLine(BOOL bFlag = FALSE);			// ���� üũ �ʱ�ȭ
	virtual BOOL HaveCheckedLine();								// üũ�� ������ �ֳ�
	virtual int GetCheckedLines(deque<T*> * pSelectLineList);	// üũ�� ���ε� ���
	virtual int GetLineNum() { return (m_bUseMultiline == TRUE ? m_RenderTextList.size() : m_TextList.size()); }

	virtual void SLSetSelectLine(int iLineNum);					// ���� ���� (1~���μ�) , 0: ���� ����
	virtual void SLSelectPrevLine(int iLineNum = 1);			// ���� �������� �̵� (-)
	virtual void SLSelectNextLine(int iLineNum = 1);			// ���� �������� �̵� (+)
#ifdef _VS2008PORTING
	virtual typename deque<T>::iterator SLGetSelectLine();		// ���� ���� ������ ���
#else // _VS2008PORTING
	virtual deque<T>::iterator SLGetSelectLine();				// ���� ���� ������ ���
#endif // _VS2008PORTING

	virtual int SLGetSelectLineNum() { return m_iSelectLineNum; }

protected:
	virtual BOOL DoMouseAction();
	virtual void RemoveText();									// ��ġ�� �ؽ�Ʈ ����
	virtual void ComputeScrollBar();
	virtual void MoveRenderLine();								// ��� ���� �� �ٱ��� m_TextListIter�� �Ű��ش�
	virtual BOOL CheckMouseInBox();								// ���콺 ó���� �� �����ΰ� üũ

	virtual void RenderInterface() = 0;							// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber) = 0;			// ���� �ؽ�Ʈ ���� ���
	virtual void RenderCoveredInterface() { }					// �ֻ�� �������̽� ���
	virtual BOOL DoLineMouseAction(int iLineNumber) = 0;		// ���� ���� ���콺 �׼�
	virtual BOOL DoSubMouseAction() { return TRUE; }

	virtual void CalcLineNum() {}								// �� �� ���� (��Ƽ���ο��� ���)

protected:
	deque<T> m_TextList;
#ifdef _VS2008PORTING
	typename deque<T>::iterator m_TextListIter;
#else // _VS2008PORTING
	deque<T>::iterator m_TextListIter;
#endif // _VS2008PORTING

	BOOL m_bUseSelectLine;				// ���� ���� ���ɿ���
	BOOL m_bPressCursorKey;				// Ű �Է� ó����a
	int m_iSelectLineNum;				// ���õ� ���� ��ȣ

	BOOL m_bUseMultiline;		// ��Ƽ���� ���
	deque<T> m_RenderTextList;	// ��¿� (m_TextList ���� �����´�)

	int m_iMaxLineCount;	// �ִ� �����ͼ�
	int m_iCurrentRenderEndLine;
	int m_iNumRenderLine;

	float m_fScrollBarRange_top;
	float m_fScrollBarRange_bottom;

	float m_fScrollBarPos_y;	// 0.0 ~ 1.0
	float m_fScrollBarWidth;
	float m_fScrollBarHeight;

	float m_fScrollBarClickPos_y;
	BOOL m_bScrollBtnClick;
	BOOL m_bScrollBarClick;

	int m_iScrollType;	// ��ũ�� ����
	BOOL m_bNewTypeScrollBar;	// ��ũ�ѹ� �����

	BOOL m_bUseNewUIScrollBar;	// ���ο� ��� ��ũ�ѹ� ��� (��ư���� ��ũ�ѹ� �巡�׸� ������)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIGuildListBox : public CUITextListBox<GUILDLIST_TEXT>	// ��� ����Ʈ â
{
public:
	CUIGuildListBox();
	virtual ~CUIGuildListBox() {}

	virtual void AddText(const char* pszID, BYTE Number, BYTE Server);
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber) { return TRUE; }	// ���� ���� ���콺 �׼�
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoSubMouseAction();
protected:
	BOOL m_bIsGuildMaster;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUISimpleChatListBox : public CUITextListBox<WHISPER_TEXT>	// ä�� ���� ����Ʈâ (������,�ڵ���Ƽ����)
{
public:
	CUISimpleChatListBox();
	virtual ~CUISimpleChatListBox() {}

	virtual void Render();
	virtual void AddText(const char* pszID, const char* pszText, int iType, int iColor);
protected:
	virtual void AddTextToRenderList(const char* pszID, const char* pszText, int iType, int iColor);
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber)		{ return TRUE; }	// ���� ���� ���콺 �׼�
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
			void CalcLineNum();	// �� �� ���
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUILetterTextListBox : public CUITextListBox<LETTER_TEXT>	// ���� ���� ����Ʈâ (������,�ڵ���Ƽ����)
{
public:
	CUILetterTextListBox();
	virtual ~CUILetterTextListBox() {}

	virtual void Render();
	virtual void AddText(const char* pszText);
protected:
	virtual void AddTextToRenderList(const char* pszText);
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL DoLineMouseAction(int iLineNumber) { return TRUE;	}	// ���� ���� ���콺 �׼�
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
			void CalcLineNum();	// �� �� ���
	virtual int	GetRenderLinePos_y(int iLineNumber);
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIChatPalListBox : public CUITextListBox<GUILDLIST_TEXT>	// ä�� ��� ����Ʈâ (������)
{
public:
	CUIChatPalListBox();
	virtual ~CUIChatPalListBox() {}

	virtual void AddText(const char* pszID, BYTE Number, BYTE Server);
	virtual void DeleteText(const char* pszID);
	virtual void SetNumRenderLine(int iLine);
	GUILDLIST_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	deque<GUILDLIST_TEXT> & GetFriendList() { m_bForceEditList = TRUE; return m_TextList; }
	void SetLayout(int iType) { m_iLayoutType = iType; }
	const char* GetNameByNumber(BYTE byNumber);
	void SetColumnWidth(UINT uiColumnNum, int iWidth) { if (uiColumnNum < 4) m_iColumnWidth[uiColumnNum] = iWidth; }
	int GetColumnWidth(UINT uiColumnNum) { return (uiColumnNum < 4 ? m_iColumnWidth[uiColumnNum] : 0); }
	int GetColumnPos_x(UINT uiColumnNum)
	{
		int iResult = 0;
#ifdef _VS2008PORTING
		for (unsigned int i = 0; i < uiColumnNum; ++i)
#else // _VS2008PORTING
		for (int i = 0; i < uiColumnNum; ++i)
#endif // _VS2008PORTING
		{
			iResult += m_iColumnWidth[i];
		}
		return iResult;
	}
	void MakeTitleText(char* pszTitleText);	// ä�� �濡 �ִ� ����� �̸� ���

protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);

protected:
	int m_iLayoutType;
	int m_iColumnWidth[4];	// �� �׸� �ʺ�
	BOOL m_bForceEditList;	// ����Ʈ �ܺ� ����
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIWindowListBox : public CUITextListBox<WINDOWLIST_TEXT>	// ������ ����Ʈ â
{
public:
	CUIWindowListBox();
	virtual ~CUIWindowListBox() {}

	virtual void AddText(DWORD dwUIID, const char* pszTitle, int iStatus = 0);
	virtual void DeleteText(DWORD dwUIID);
	virtual void SetNumRenderLine(int iLine);
	WINDOWLIST_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUILetterListBox : public CUITextListBox<LETTERLIST_TEXT>	// ���� ����Ʈ â
{
public:
	CUILetterListBox();
	virtual ~CUILetterListBox() {}

	virtual void AddText(const char* pszID, const char* pszText, const char* pszDate, const char* pszTime, BOOL bIsRead);
	virtual void DeleteText(DWORD dwLetterID);
	virtual void SetNumRenderLine(int iLine);
	LETTERLIST_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	deque<LETTERLIST_TEXT> & GetLetterList() { m_bForceEditList = TRUE; return m_TextList; }
	
	void SetColumnWidth(UINT uiColumnNum, int iWidth) { if (uiColumnNum < 4) m_iColumnWidth[uiColumnNum] = iWidth; }
	int GetColumnWidth(UINT uiColumnNum) { return (uiColumnNum < 4 ? m_iColumnWidth[uiColumnNum] : 0); }
	int GetColumnPos_x(UINT uiColumnNum)
	{
		int iResult = 0;
#ifdef _VS2008PORTING
		for (unsigned int i = 0; i < uiColumnNum; ++i)
#else // _VS2008PORTING
		for (int i = 0; i < uiColumnNum; ++i)
#endif // _VS2008PORTING
		{
			iResult += m_iColumnWidth[i];
		}
		return iResult;
	}
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);

protected:
	int m_iColumnWidth[4];	// �� �׸� �ʺ�
	BOOL m_bForceEditList;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ADD_SOCKET_MIX
class CUISocketListBox : public CUITextListBox<SOCKETLIST_TEXT>	// ������ ����Ʈ â
{
public:
	CUISocketListBox();
	virtual ~CUISocketListBox() {}

	virtual void AddText(int iSocketIndex, const char * pszText);
	virtual void DeleteText(int iSocketIndex);
	virtual void SetNumRenderLine(int iLine);
	SOCKETLIST_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif	// ADD_SOCKET_MIX

// ������ ����Ʈâ
class CUIGuildNoticeListBox : public CUITextListBox<GUILDLOG_TEXT>
{
public:
	CUIGuildNoticeListBox();
	virtual ~CUIGuildNoticeListBox() {}

	virtual void AddText( const char* szContent );
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DeleteText( DWORD dwIndex );
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void SetNumRenderLine( int nLine );
	GUILDLOG_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};

// ����� ����Ʈâ
class CUINewGuildMemberListBox : public CUITextListBox<GUILDLIST_TEXT>
{
public:
	CUINewGuildMemberListBox();
	virtual ~CUINewGuildMemberListBox() {}

	virtual void AddText(const char* pszID, BYTE Number, BYTE Server, BYTE GuildStatus);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DeleteText(DWORD dwUIID);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void SetNumRenderLine(int iLine);
	GUILDLIST_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
protected:
	BOOL m_bIsGuildMaster;
};

// ���ձ�� ����Ʈ
class CUIUnionGuildListBox : public CUITextListBox<UNIONGUILD_TEXT>	// �뺴��� ����Ʈ â

{
public:
	CUIUnionGuildListBox();
	virtual ~CUIUnionGuildListBox() {}

	virtual void AddText(BYTE* pGuildMark, const char* szGuildName, int nMemberCount);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DeleteText(DWORD dwGuildIndex);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual int GetTextCount();
	virtual void SetNumRenderLine(int iLine);
	UNIONGUILD_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};

// ���� ���� ����Ʈ â
class CUIUnmixgemList : public CUITextListBox<UNMIX_TEXT>
{
public:
	CUIUnmixgemList();
	virtual ~CUIUnmixgemList() {}
	virtual void SetNumRenderLine(int iLine);
	UNMIX_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	virtual void AddText( int iIndex, BYTE cComType );
	void Sort();

	inline bool IsNotified() { return m_bNotify; }
	inline bool IsEmpty() { return m_TextList.empty(); }

protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);

	bool	m_bNotify;
};

// ������ ������ ��帮��Ʈ
class CUIBCDeclareGuildListBox : public CUITextListBox<BCDECLAREGUILD_TEXT>

{
public:
	CUIBCDeclareGuildListBox();
	virtual ~CUIBCDeclareGuildListBox() {}

	virtual void AddText( const char* szGuildName, int nMarkCount, BYTE byIsGiveUp, BYTE bySeqNum );
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DeleteText(DWORD dwGuildIndex);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void SetNumRenderLine(int iLine);
	BCDECLAREGUILD_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	void Sort();

protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};
// ������ Ȯ���� ��帮��Ʈ
class CUIBCGuildListBox : public CUITextListBox<BCGUILD_TEXT>

{
public:
	int		Select_Guild;
	CUIBCGuildListBox();
	virtual ~CUIBCGuildListBox() {}

	virtual void AddText( const char* szGuildName, BYTE byJoinSide, BYTE byGuildInvolved 	
		,int iGuildScore
		);
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void DeleteText(DWORD dwGuildIndex);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void SetNumRenderLine(int iLine);
	BCGUILD_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
protected:
	virtual void RenderInterface();	// �������̽� ���
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int iLineNumber);
};

//-------------------------------------------------------------------------------------------
// �̵����â ����Ʈ�ڽ�
class CUIMoveCommandListBox : public CUITextListBox<MOVECOMMAND_TEXT>
{
public:
	CUIMoveCommandListBox();
	virtual ~CUIMoveCommandListBox() {}

	virtual void AddText( int iIndex, const char* szMapName, const char* szSubMapName, int iReqLevel, int iReqZen, int iGateNum );
	//virtual void DeleteText(DWORD dwGuildIndex);
	virtual void SetNumRenderLine(int iLine);
	MOVECOMMAND_TEXT * GetSelectedText() { return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	//void Sort();

protected:
	virtual void RenderInterface();	// �������̽� ���
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual BOOL RenderDataLine(int iLineNumber);	// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int iLineNumber);	// ���� ���� ���콺 �׼�
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual int GetRenderLinePos_y(int iLineNumber);
};
//-------------------------------------------------------------------------------------------

#ifdef ASG_MOD_UI_QUEST_INFO
// ���� ���� ����Ʈ �׸� ����ü.
struct SCurQuestItem
{
	BOOL	m_bIsSelected;
	DWORD	m_dwIndex;
	char	m_szText[64];
};

// ���� ���� ����Ʈ ����Ʈ �ڽ� UI Ŭ����
class CUICurQuestListBox : public CUITextListBox<SCurQuestItem>
{
public:
	CUICurQuestListBox();
	virtual ~CUICurQuestListBox() {}
	
	virtual void AddText(DWORD dwQuestIndex, const char* pszText);
	virtual void DeleteText(DWORD dwQuestIndex);
	virtual void SetNumRenderLine(int nLine);
	SCurQuestItem* GetSelectedText()
	{ return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	
protected:
	virtual void RenderInterface();				// �������̽� ���
	virtual BOOL RenderDataLine(int nLine);		// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int nLine);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int nLine);
};

enum REQUEST_REWARD_CLASSIFY;

struct SQuestContents
{
	BOOL	m_bIsSelected;
	HFONT	m_hFont;
	DWORD	m_dwColor;
	int		m_nSort;
	char	m_szText[64];
	REQUEST_REWARD_CLASSIFY	m_eRequestReward;
	DWORD	m_dwType;
	WORD	m_wIndex;
	ITEM*	m_pItem;
};

struct SRequestRewardText;

class CUIQuestContentsListBox : public CUITextListBox<SQuestContents>
{
public:
	CUIQuestContentsListBox();
	virtual ~CUIQuestContentsListBox() {}

	virtual void AddText(HFONT hFont, DWORD dwColor, int nSort, const char* pszText);
	virtual void AddText(SRequestRewardText* pRequestRewardText, int nSort);
/*	virtual void DeleteText(DWORD dwQuestIndex);
	virtual void SetNumRenderLine(int nLine);
	SQuestContents* GetSelectedText()
	{ return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
*/	
protected:
	virtual void RenderInterface();				// �������̽� ���
	virtual BOOL RenderDataLine(int nLine);		// ���� �ؽ�Ʈ ���� ���
	virtual void RenderCoveredInterface();		// �ֻ�� �������̽� ���
	virtual void DoActionSub(BOOL bMessageOnly);
	virtual BOOL DoLineMouseAction(int nLine);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int nLine);
};

#endif	// ASG_MOD_UI_QUEST_INFO

struct TEXTCOLOR_DATA
{
	int m_iCharPos;		// ���ڻ��� ��ġ
	int m_iStartPos;	// �ȼ� ���� ��ġ
	DWORD m_dwTextColor;
	DWORD m_dwBackColor;
};
const int MAX_COLOR_PER_LINE = 10;

struct RENDER_TEXT_DATA
{
	char m_szText[MAX_TEXT_LENGTH + 1];		// �ؽ�Ʈ ����
	int m_iWidth;
	int m_iHeight;
	int m_iTab;				// �� ũ��
	DWORD m_dwUseCount;		// ������ ��� ī��Ʈ
	DWORD m_dwTextColor;	// ���� ���ڻ��� ����
	DWORD m_dwBackColor;
	int m_iTextureIndex;	// �ؽ�Ʈ �ؽ��� ��ȣ
	int m_iTextureIndexEx;
	BOOL m_bUseTextEX;		// Ȯ�� �ؽ�Ʈ �׷��� ��� ���� (256px �̻�)
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class IUIRenderText
{
public:
	virtual bool Create(HDC hDC) = 0;
	virtual void Release() = 0;

	virtual HDC GetFontDC() const = 0;
	virtual BYTE* GetFontBuffer() const = 0;

	virtual DWORD GetTextColor() const = 0;
	virtual DWORD GetBgColor() const = 0;

	virtual void SetTextColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha) = 0;
	virtual void SetTextColor(DWORD dwColor) = 0;
	virtual void SetBgColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha) = 0;
	virtual void SetBgColor(DWORD dwColor) = 0;

	virtual void SetFont(HFONT hFont) = 0;

	//. lpTextSize: 640*480 ���� �ؽ�Ʈ ����� ������ (GetTextExtentPoint�� Ʋ��)
	virtual void RenderText(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth = 0, int iBoxHeight = 0, 
		int iSort = RT3_SORT_LEFT, OUT SIZE* lpTextSize = NULL) = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef multimap<int, RENDER_TEXT_DATA, less<int> > RTMap;
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIRenderTextOriginal : public IUIRenderText
{
	HDC	m_hFontDC;
	HBITMAP m_hBitmap;
	BYTE* m_pFontBuffer;			// �ؽ�Ʈ ���� ����
	DWORD m_dwTextColor, m_dwBackColor;
public:
	CUIRenderTextOriginal();
	virtual ~CUIRenderTextOriginal();

	bool Create(HDC hDC);
	void Release();

	HDC GetFontDC() const;
	BYTE* GetFontBuffer() const;

	DWORD GetTextColor() const;
	DWORD GetBgColor() const;

	void SetTextColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha);
	void SetTextColor(DWORD dwColor);
	void SetBgColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha);
	void SetBgColor(DWORD dwColor);
#ifdef KJH_FIX_UI_CHAT_MESSAGE
	DWORD ConvertColorToDword(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha);
#endif // KJH_FIX_UI_CHAT_MESSAGE

	void SetFont(HFONT hFont);

	//. lpTextSize: 640*480 ���� �ؽ�Ʈ ����� ������ (GetTextExtentPoint�� Ʋ��)
	void RenderText(int iPos_x, int iPos_y, const unicode::t_char* pszText, int iBoxWidth = 0, int iBoxHeight = 0, 
		int iSort = RT3_SORT_LEFT, OUT SIZE* lpTextSize = NULL);

protected:
	void WriteText(int iOffset, int iWidth, int iHeight);
	void UploadText(int sx,int sy,int Width,int Height);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIRenderText
{
	CUIRenderText();

	IUIRenderText*	m_pRenderText;
	int m_iRenderTextType;

public:
	virtual ~CUIRenderText();

	static CUIRenderText* GetInstance();

	bool Create(int iRenderTextType, HDC hDC);
	void Release();
	
	int GetRenderTextType() const;

	HDC GetFontDC() const;
	BYTE* GetFontBuffer() const;
	DWORD GetTextColor() const;
	DWORD GetBgColor() const;

	void SetTextColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha);
	void SetTextColor(DWORD dwColor);
	void SetBgColor(BYTE byRed, BYTE byGreen, BYTE byBlue, BYTE byAlpha);
	void SetBgColor(DWORD dwColor);

	void SetFont(HFONT hFont);

	void RenderText(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth = 0, int iBoxHeight = 0, 
		int iSort = RT3_SORT_LEFT, OUT SIZE* lpTextSize = NULL);
};

#define g_pRenderText CUIRenderText::GetInstance()
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#define g_pMultiLanguage CMultiLanguage::GetSingletonPtr()
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

////////////////////////////////////////////////////////////////////////////////////////////////////

void SaveIMEStatus();		// IME ���� ����
void RestoreIMEStatus();	// IME ���� ����
void CheckTextInputBoxIME(int iMode);	// IME ���� �ٲ� ó���� �Լ� (������ �����Է� ���·� �ٲ��ֱ� ����)

class CUITextInputBox : public CUIControl
{
public:
	CUITextInputBox();
	virtual ~CUITextInputBox();

	virtual void SetSize(int iWidth, int iHeight);

	virtual void Init(HWND hWnd, int iWidth, int iHeight, int iMaxLength = 50, BOOL bIsPassword = FALSE);
	virtual void Render();
	virtual void GiveFocus(BOOL bSel = FALSE);	// ���� �����ϰ� ������ bSel�� TRUE�� ���ּ���.

	virtual void SetState(int iState);	// UISTATE_NORMAL ������ �ؾ� ȭ�鿡 ǥ�õ˴ϴ�
	virtual void SetFont(HFONT hFont);	// ��Ʈ ����
	virtual void SetMultiline(BOOL bUseFlag) { m_bUseMultiLine = bUseFlag; }	// ��Ƽ���� �ؽ�Ʈ ��� (Init���� ȣ��)

	virtual void SetTextLimit(int iLimit);	// �ִ� �Է� ���ڼ� ����
	virtual void SetTextColor(BYTE a, BYTE r, BYTE g, BYTE b) { m_dwTextColor = _ARGB(a, r, g, b); }
	virtual void SetBackColor(BYTE a, BYTE r, BYTE g, BYTE b) { m_dwBackColor = _ARGB(a, r, g, b); }
	virtual void SetSelectBackColor(BYTE a, BYTE r, BYTE g, BYTE b) { m_dwSelectBackColor = _ARGB(a, r, g, b); }
	virtual void SetText(const char* pszText);	// NULL: Ŭ����
	virtual void GetText(char* pszText, int iGetLenght = MAX_TEXT_LENGTH);	// �ؽ�Ʈ ���

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	virtual void GetText(wchar_t* pwszText, int iGetLenght = MAX_TEXT_LENGTH);	// �ؽ�Ʈ ���
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	HWND GetHandle() { return m_hEditWnd; }
	HWND GetParentHandle() { return m_hParentWnd; }
	BOOL HaveFocus() { return (GetHandle() == GetFocus()); }	// Ŀ���� ������ �ִ°�
	BOOL UseMultiline() { return m_bUseMultiLine; }
	virtual void SetTabTarget(CUITextInputBox * pTabTarget) {  m_pTabTarget = pTabTarget; }
	CUITextInputBox * GetTabTarget() { return m_pTabTarget; }

	virtual void Lock(BOOL bFlag) { m_bLock = bFlag; }
	virtual BOOL IsLocked() { return m_bLock; }
	BOOL IsPassword() { return m_bPasswordInput; }

	virtual void SetIMEPosition();
#ifdef PBG_ADD_INGAMESHOPMSGBOX
	bool GetUseScrollbar() { return m_bUseScrollbarRender; }		//��ũ�ѹ� ��뿩��
	void SetUseScrollbar(bool _scrollbar = TRUE) { m_bUseScrollbarRender = _scrollbar; }
#endif //PBG_ADD_INGAMESHOPMSGBOX

protected:
	virtual BOOL DoMouseAction();
	void RenderScrollbar();

	void WriteText(int iOffset, int iWidth, int iHeight);
	void UploadText(int sx,int sy,int Width,int Height);

public:
	WNDPROC m_hOldProc;
	int m_iCaretBlinkTemp;		// Ŀ�� ������ ������ üũ

protected:
	HWND m_hParentWnd;
	HWND m_hEditWnd;
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	BYTE* m_pFontBuffer;			// �ؽ�Ʈ ���� ����

	CUITextInputBox* m_pTabTarget;	// �� �������� �̵��� �Է�â

	DWORD m_dwTextColor;
	DWORD m_dwBackColor;
	DWORD m_dwSelectBackColor;

	float m_fCaretWidth;
	float m_fCaretHeight;

	BOOL m_bPasswordInput;
	BOOL m_bLock;

	// IME��
	BOOL m_bIsReady;
	int m_iRealWindowPos_x;
	int m_iRealWindowPos_y;

	// ��Ƽ���ο�
	BOOL m_bUseMultiLine;	// ��Ƽ���� ���
	BOOL m_bScrollBtnClick;
	BOOL m_bScrollBarClick;
	int m_iNumLines;		// �ִ� ����
	float m_fScrollBarWidth;
	float m_fScrollBarRange_top;
	float m_fScrollBarRange_bottom;
	float m_fScrollBarHeight;
	float m_fScrollBarPos_y;
	float m_fScrollBarClickPos_y;
#ifdef PBG_ADD_INGAMESHOPMSGBOX
	bool m_bUseScrollbarRender;
#endif //PBG_ADD_INGAMESHOPMSGBOX
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIChatInputBox
{
public:
	CUIChatInputBox() {}
	virtual ~CUIChatInputBox() { RemoveHistory(TRUE); }

	virtual void Init(HWND hWnd);
	void Reset();
	void Render();
	void TabMove(int iBoxNumber);	// 0: ù��°, 1: �ι�°
	void GetTexts(char* pText, char* pBuddyText);	// �ؽ�Ʈ ��������
	void ClearTexts();
	void SetText(BOOL bSetText, const char* pText, BOOL bSetBuddyText, const char* pBuddyText);	// �ؽ�Ʈ ���� (NULL: �����)
	void SetState(int iState);
	int GetState() { return m_TextInputBox.GetState(); }
	void SetFont(HFONT hFont);
	void SetTextPosition(int iPos_x, int iPos_y) { m_TextInputBox.SetPosition(iPos_x, iPos_y); }
	void SetBuddyPosition(int iPos_x, int iPos_y) { m_BuddyInputBox.SetPosition(iPos_x, iPos_y); }
	BOOL HaveFocus() { return (m_TextInputBox.HaveFocus() || m_BuddyInputBox.HaveFocus()); }	// Ŀ���� ������ �ִ°�
	BOOL DoMouseAction();
#if defined FOR_WORK || defined USER_WINDOW_MODE || (defined WINDOWMODE)
	void RestoreFocus() { m_bFocusLose = TRUE; }
#endif

protected:
	CUITextInputBox m_TextInputBox;
	CUITextInputBox m_BuddyInputBox;
#if defined FOR_WORK || defined USER_WINDOW_MODE || (defined WINDOWMODE)
	BOOL m_bFocusLose;
	int m_iBackupFocus;
#endif

public:
	virtual void AddHistory(const char* pszText);	// �����丮�� �߰��Ѵ�
	virtual void MoveHistory(int iDegree);		// �����丮 ����Ʈ�� �ű��
private:
	void RemoveHistory(BOOL bClear);	// ���尳�� �ʰ��� �����丮 ����
	BOOL m_bHistoryMode;
	char m_szTempText[MAX_TEXT_LENGTH + 1];				// �Է� ���̴� ���� �ӽ�����
	deque<char*> m_HistoryList;
	deque<char*>::iterator m_CurrentHistoryLine;
	deque<char*>::iterator m_HistoryListIter;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class CUILoginInputBox : public CUIChatInputBox
{
public:
	CUILoginInputBox() {}
	virtual ~CUILoginInputBox() {}

	virtual void Init(HWND hWnd);
	// �����丮 �Ⱦ� -_-
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void AddHistory(const char* pszText) {}
	virtual void MoveHistory(int iDegree) {}
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
};
////////////////////////////////////////////////////////////////////////////////////////////////////

class CUIMercenaryInputBox : public CUIChatInputBox
{
public:
	CUIMercenaryInputBox() {}
	virtual ~CUIMercenaryInputBox() {}

	virtual void Init(HWND hWnd);
	// �����丮 �Ⱦ� -_-
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	virtual void AddHistory(const char* pszText) {}
	virtual void MoveHistory(int iDegree) {}
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
};
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef REVISION_SLIDE_LEVEL_MAX
#define SLIDE_LEVEL_MAX 10 
#else //REVISION_SLIDE_LEVEL_MAX
#define SLIDE_LEVEL_MAX 5
#endif //REVISION_SLIDE_LEVEL_MAX

#define SLIDE_TEXT_LENGTH 1024

struct SLIDEHELPTEXT
{
	int iLevel;
	int iNumber;
	char szSlideHelpText[32][256];
};

struct SLIDEHELP
{
	int iCreateDelay;
	float fSpeed;
	SLIDEHELPTEXT SlideHelp[SLIDE_LEVEL_MAX];
};

struct SLIDE_QUEUE_DATA
{
	int m_iType;
	char* m_pszText;
	DWORD m_dwTextColor;
	float m_fSpeed;
	BOOL m_bLastData;
};

typedef multimap<DWORD, SLIDE_QUEUE_DATA, less<DWORD> > SLIDE_QUEUE;

class CUISlideHelp : public CUIControl
{
public:
	CUISlideHelp();
	virtual ~CUISlideHelp();

	// �����̵� �⺻
	void Init(BOOL bBold = FALSE, BOOL bBlink = FALSE);
	BOOL DoMouseAction();
	void Render(BOOL bForceFadeOut = FALSE);
	void SetScrollSpeed(float fSpeed);								// �����̵� �ӵ�
	BOOL AddSlideText(const char* pszNewText, DWORD dwTextColor = (255<<24)+(200<<16)+(220<<8)+(230));	// �����̵� ���ۿ� �ؽ�Ʈ �߰�

	int GetAlphaRate() { return m_iAlphaRate; }
	BOOL HaveText();

	// �ð� ����
	void AddSlide(int iLoopCount, int iLoopDelay, const char* pszText, int iType, float fSpeed, DWORD dwTextColor);
	void CheckTime();	// �ð� üũ
	void ManageSlide();
	DWORD m_dwTimer;
	DWORD m_dwCurrentSecond;

	SLIDE_QUEUE m_SlideQueue;
	SLIDE_QUEUE::iterator m_SlideQueueIter;
	list <DWORD> m_RemoveQueueList;

protected:
	void SlideMove();
	void ComputeSpeed();

	int CheckCutSize(const char* pszSource, int iNeedValue);				// �ڸ��� ������ ���
	
protected:
	HFONT m_hFont;
	char* m_pszSlideText;
	char m_szSlideTextA[SLIDE_TEXT_LENGTH];
	char m_szSlideTextB[SLIDE_TEXT_LENGTH];
	float m_fMovePosition;
	float m_fMoveAccel;
	float m_fMoveSpeed;
	float m_fMaxMoveSpeed;
	int m_iAlphaRate;
	int m_iCutLength;
	int m_iCutSize;
	int m_iFontHeight;
	DWORD m_dwSlideTextColor;
	BOOL m_bBlink;
};

class CSlideHelpMgr
{
public:
	CSlideHelpMgr();
	virtual ~CSlideHelpMgr();

	void Init();
	void Render();

	// �����̵� ����
	void CreateSlideText();											// �����̵� ���� �߰�
	void OpenSlideTextFile(const char* szFileName);						// slide(?).txt �ε�
	void ClearSlideText();											// �����̵� �ؽ�Ʈ �����
	const char* GetSlideText(int iLevel);								// ���� ������ �����̵� �ؽ�Ʈ ���
	void SetCreateDelay(int iDelay) { m_iCreateDelay = iDelay; }	// �����̵� ���� ���� ������

	// �����̵� ������
	void AddSlide(int iLoopCount, int iLoopDelay, const char* pszText,
		int iType, float fSpeed, DWORD dwTextColor = (255<<24)+(200<<16)+(220<<8)+(230));
	void ManageSlide();
	BOOL IsIdle();
protected:
	CUISlideHelp m_HelpSlide;
	CUISlideHelp m_NoticeSlide;

	int m_iCreateDelay;
	int m_iLevelCap[SLIDE_LEVEL_MAX];
	int m_iTextNumber[SLIDE_LEVEL_MAX];
	list<char*> m_SlideTextList[SLIDE_LEVEL_MAX];
	list<char*>::iterator m_SlideTextListIter;
	float m_fHelpSlideSpeed;
};


extern DWORD g_dwActiveUIID;	// ���� �۵����� UI ID
extern DWORD g_dwMouseUseUIID;	

#ifdef PBG_ADD_INGAMESHOP_UI_ITEMSHOP
typedef struct
{
	BOOL	m_bIsSelected;

	int		m_iStorageSeq;
	int		m_iStorageItemSeq;
	int		m_iStorageGroupCode;
	int		m_iProductSeq;
	int		m_iPriceSeq;
	int		m_iCashPoint;
	int		m_iNum;
	WORD	m_wItemCode;
	
	unicode::t_char	m_szName[MAX_TEXT_LENGTH];
	unicode::t_char m_szNum[MAX_TEXT_LENGTH];
	unicode::t_char m_szPeriod[MAX_TEXT_LENGTH];
	unicode::t_char	m_szSendUserName[MAX_ID_SIZE+1];
	unicode::t_char	m_szMessage[MAX_GIFT_MESSAGE_SIZE];
	unicode::t_char m_szType;
}IGS_StorageItem;

// ������ �������� ����Ʈ �ڽ� UI Ŭ����
class CUIInGameShopListBox : public CUITextListBox<IGS_StorageItem>
{
	enum IMAGE_LISTBOX_SIZE
	{
#ifdef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		LISTBOX_WIDTH =146,
#else // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		LISTBOX_WIDTH =140,
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
		LISTBOX_HEIGHT =115,
	};
public:
	CUIInGameShopListBox();
	virtual ~CUIInGameShopListBox() {}
	
	virtual void AddText(IGS_StorageItem& _StorageItem);
	virtual void SetNumRenderLine(int nLine);
	IGS_StorageItem* GetSelectedText()
	{ return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	void DelData(int iIndex);		// Data�ϳ��� �����.
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT
	
protected:
	virtual void RenderInterface();				// �������̽� ���
	virtual BOOL RenderDataLine(int nLine);		// ���� �ؽ�Ʈ ���� ���
	virtual BOOL DoLineMouseAction(int nLine);	// ���� ���� ���콺 �׼�
	virtual int GetRenderLinePos_y(int nLine);
};


#define LINE_TEXTMAX	64
// �ִ� 10�������� �ý�Ʈ�� ��������.Ȯ���ص� �������.800x600������
#define INFO_LINEMAX	10
// FULLSCREEN�� �ִ� ������
#define INFO_LINE_CNTMAX	50


struct IGS_BuyList
{
	BOOL	m_bIsSelected;
	char	m_pszItemExplanation[LINE_TEXTMAX];	// ��ǰ ����
};

// ���� ����â�� ����Ʈ �ڽ� UIŬ����
class CUIBuyingListBox : public CUITextListBox<IGS_BuyList>
{
	enum IMAGE_LISTBOX_SIZE
	{
		LISTBOX_WIDTH = 175,		// ����Ʈ �ڽ� ������
		LISTBOX_HEIGHT = 95,
	};
public:
	CUIBuyingListBox();
	virtual ~CUIBuyingListBox() {}

	virtual void AddText(const char* pszExplanationText);
	virtual void SetNumRenderLine(int nLine);
	IGS_BuyList* GetSelectedText()
	{ return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }

	// �ؽ�Ʈ ���� ���ý� ������ ���ֱ� ���� ��� default �� ���� �ִ´�
	void SetLineColorRender(const bool _LineColor = true);
	const bool& GetLineColorRender() const { return m_bRenderLineColor; }

protected:
	virtual void RenderInterface();
	virtual BOOL RenderDataLine(int nLine);
	virtual BOOL DoLineMouseAction(int nLine);
	virtual int GetRenderLinePos_y(int nLine);

	// �ؽ�Ʈ ���λ� �׸���
	bool m_bRenderLineColor;
};
// listbox������ ����ϴ� üũ ��ư 3��ǿ�
// iter ���� ��ü�� ���� �������
class CRadioButton
{
	enum IMAGE_RADIOBUTTON
	{
		IMAGE_CHECKBTN = BITMAP_IGS_CHECK_BUTTON,
	};
	enum SIZE_BTN
	{
		BTN_WIDTH = 14,
		BTN_HEIGHT = 14,
		BTN_SPACE = 1,
	};
	enum STATE_BUTTON
	{
		LBTN_DEFAULT=0,
		LBTN_UP,
		LBTN_DOWN,
	};
public:
	CRadioButton();
	~CRadioButton();
	// ���콺 ����
	bool UpdateMouseAction();
	// Ŭ�����¿� ���� ������ư ����
	bool UpdateActionCheck(int _nState);
	// ���콺 ���¿� ���� ����
	void RadiobuttonBoxRender();
	// ��ư�� rect
	void SetRadioBtnRect(float _x=0, float _y=0, float _width=BTN_WIDTH, float _height=BTN_HEIGHT);
	bool IsRadioBtn(RECT _rt);
	void RenderImage(GLuint uiImageType, float x, float y, float width, float height, float su, float sv);
	// üũ �Ȼ���
	const bool& GetCheckBtn() const { return m_bCheckState; }

	///////////////////////////////////////////////////////////
	// �̺κ��� ����� �����ϸ� check��ư���� ��밡��
	// static ������ ���� Ŭ���� �ε��� ��ȣ�� ����Ѵ�
	static int m_nIterIndex;
	// Ŭ���� �����ÿ� ������ �ε����� ���´�
	int m_nRadioBtnEnable;
	void SetCheckState(bool _Value);
	void SetRadioBtnIsEnable(int _Value);
	int GetRadioBtnIsEnable(){ return m_nRadioBtnEnable; }
	///////////////////////////////////////////////////////////
private:
	RECT m_rtCheckBtn;
	// üũ ����
	bool m_bCheckState;
	// ���콺 ��������
	BYTE m_byMouseState;	
};
// ��Ű�� ����â�� ����Ʈ �ڽ� UIŬ����
struct IGS_PackBuyList
{
	BOOL	m_bIsSelected;
	char	m_pszItemName[32];	// �����۸�
	char	m_nItemInfo[32];	// �Ⱓ�� ���� ���ڿ��� �޴´�
	CRadioButton m_CheckBtn;	// üũ ��ư Ŭ������ü
};

typedef struct 
{
	BOOL	m_bIsSelected;
	int		m_iPackageSeq;
	int		m_iDisplaySeq;
	int		m_iPriceSeq;
	WORD	m_wItemCode;
#ifndef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL			// #ifndef
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	int		m_iCashType;		// ĳ��Ÿ�� (C/P) - �۷ι� ����
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL

	unicode::t_char m_szItemName[MAX_TEXT_LENGTH];
	unicode::t_char m_szItemPrice[MAX_TEXT_LENGTH];
#ifdef KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char m_szItemPriceUnit[MAX_TEXT_LENGTH];
#endif // KJH_MOD_INGAMESHOP_SELECT_CASHPOINT_SYSYEM_ONLY_GLOBAL
	unicode::t_char m_szItemPeriod[MAX_TEXT_LENGTH];
	unicode::t_char m_szAttribute[MAX_TEXT_LENGTH];

	CRadioButton m_RadioBtn;	//���� ��ư ���
}IGS_SelectBuyItem;

class CUIPackCheckBuyingListBox : public CUITextListBox<IGS_SelectBuyItem>
{
	enum IMAGE_LISTBOX_SIZE
	{
		LISTBOX_WIDTH = 180,		// ����Ʈ �ڽ� ������
		LISTBOX_HEIGHT = 100,
		TEXT_HEIGHTSIZE = 33,
	};
public:
	CUIPackCheckBuyingListBox();
	virtual ~CUIPackCheckBuyingListBox();

	virtual void AddText(IGS_SelectBuyItem& Item);
	virtual void SetNumRenderLine(int iLine);
	IGS_SelectBuyItem* GetSelectedText()
	{ return (SLGetSelectLine() == m_TextList.end() ? NULL : &(*SLGetSelectLine())); }
	BOOL IsChangeLine();
	
protected:
	virtual void RenderInterface();
	virtual BOOL RenderDataLine(int nLine);
	virtual BOOL DoLineMouseAction(int nLine);
	virtual int GetRenderLinePos_y(int nLine);

private:
	int	m_iCurrentLine;
};
#endif //PBG_ADD_INGAMESHOP_UI_ITEMSHOP

#endif	//__UICONTROL_H__
