
#ifndef _NEWCHATLONGWINDOW_H_
#define _NEWCHATLONGWINDOW_H_

#pragma once

#include "NewUIBase.h"
#include "ZzzTexture.h"

#pragma warning(disable : 4786)
#include <string>
#include <vector>

namespace SEASON3B 
{
	class CNewUIManager;

	enum MESSAGE_TYPE
	{
#ifdef KJH_FIX_UI_CHAT_MESSAGE
		TYPE_ALL_MESSAGE = 0,
		TYPE_CHAT_MESSAGE,
		TYPE_WHISPER_MESSAGE,
		TYPE_SYSTEM_MESSAGE,
		TYPE_ERROR_MESSAGE,
#else // KJH_FIX_UI_CHAT_MESSAGE		// ������ �� ������ �ϴ� �ҽ�
		TYPE_WHISPER_MESSAGE = 0,
		TYPE_SYSTEM_MESSAGE,
		TYPE_ERROR_MESSAGE,
		TYPE_CHAT_MESSAGE,
#endif // KJH_FIX_UI_CHAT_MESSAGE		// ������ �� ������ �ϴ� �ҽ�
		TYPE_PARTY_MESSAGE,
		TYPE_GUILD_MESSAGE,
		TYPE_UNION_MESSAGE,
		TYPE_GM_MESSAGE,
			
		NUMBER_OF_TYPES,
		TYPE_UNKNOWN = 0xFFFFFFFF
	};
	
	template <class T>
	class TMessageText
	{
		typedef std::basic_string<T, std::char_traits<T>, std::allocator<T> > type_string;
		
		type_string	m_strID, m_strText;
		MESSAGE_TYPE m_MsgType;
		DWORD m_dwIndentSize;


	public:
		TMessageText() : m_MsgType(TYPE_UNKNOWN), m_dwIndentSize(0) {}
		~TMessageText() { Release(); }

		bool Create(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType)
		{
			if(MsgType >= NUMBER_OF_TYPES)
				return false;

			m_strID = strID;
			m_strText = strText;
			m_MsgType = MsgType;

			return true;
		}
		void Release()
		{
			m_strID.resize(0);
			m_strText.resize(0);
			m_MsgType = TYPE_UNKNOWN;
		}

		const type_string& GetID() const { return m_strID; }
		const type_string& GetText() const { return m_strText; }
		MESSAGE_TYPE GetType() const { return m_MsgType; }
	};

	typedef TMessageText<unicode::t_char> CMessageText;

	class CNewUIChatLogWindow: public CNewUIObj
	{
	public:
#ifndef KJH_FIX_UI_CHAT_MESSAGE				// #ifndef ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
		enum SHOW_MESSAGE_FLAG
		{
			SHOW_NOTHING = 0,
			
			SHOW_SYSTEM_MESSAGE = 0x00000001,
			SHOW_ERROR_MESSAGE = 0x00000002,
			SHOW_CHAT_MESSAGE = 0x00000004,
			SHOW_WHISPER_MESSAGE = 0x00000008,
			SHOW_PARTY_MESSAGE = 0x00000010,
			SHOW_GUILD_MESSAGE = 0x00000020,
			SHOW_UNION_MESSAGE = 0x00000040,
			SHOW_GM_MESSAGE = 0x00000080,

			SHOW_ALL_MESSAGES = 0xFFFFFFFF
		};
//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
		enum IMAGE_LIST
		{	//. max: 8��
			IMAGE_SCROLL_TOP = BITMAP_INTERFACE_NEW_CHATLOGWND_BEGIN,	//. newui_scrollbar_up.tga
			IMAGE_SCROLL_MIDDLE,	//. newui_scrollbar_m.tga
			IMAGE_SCROLL_BOTTOM,	//. newui_scrollbar_down.tga
			IMAGE_SCROLLBAR_ON,		//. newui_scroll_on.tga
			IMAGE_SCROLLBAR_OFF,	//. newui_scroll_off.tga
			IMAGE_DRAG_BTN,			//. newui_scrollbar_stretch.tga
		};

	private:
		enum 
		{
			MAX_CHAT_BUFFER_SIZE = 60,
			MAX_NUMBER_OF_LINES = 200,
			WND_WIDTH = 254,
			FONT_LEADING = 4,
			WND_TOP_BOTTOM_EDGE = 2,
			WND_LEFT_RIGHT_EDGE = 4,
			RESIZING_BTN_WIDTH = WND_WIDTH,
			RESIZING_BTN_HEIGHT = 10,
			SCROLL_BAR_WIDTH = 7,
			SCROLL_TOP_BOTTOM_PART_HEIGHT = 3,
			SCROLL_MIDDLE_PART_HEIGHT = 15,
			SCROLL_BTN_WIDTH = 15,
			SCROLL_BTN_HEIGHT = 30,
			CLIENT_WIDTH = WND_WIDTH - SCROLL_BAR_WIDTH - (WND_LEFT_RIGHT_EDGE*2),
		};
		enum EVENT_STATE
		{
			EVENT_NONE = 0,
			EVENT_CLIENT_WND_HOVER,
			EVENT_SCROLL_BTN_DOWN,
			EVENT_RESIZING_BTN_HOVER,
			EVENT_RESIZING_BTN_DOWN,
			EVENT_RESIZING_BTN_UP,
		};

		typedef std::basic_string<unicode::t_char, std::char_traits<unicode::t_char>, 
			std::allocator<unicode::t_char> > type_string;
		typedef std::vector<CMessageText*>	type_vector_msgs;
		typedef std::vector<type_string>	type_vector_filters;

		CNewUIManager*	m_pNewUIMng;

#ifdef KJH_FIX_UI_CHAT_MESSAGE
		type_vector_msgs	m_vecAllMsgs;			// ��ü�޼��� �����̳�
		type_vector_msgs	m_VecChatMsgs;			// �Ϲݸ޼��� �����̳�
		type_vector_msgs	m_vecWhisperMsgs;		// �ӼӸ��޼��� �����̳�
		type_vector_msgs	m_vecPartyMsgs;			// ��Ƽ�޼��� �����̳�
		type_vector_msgs	m_vecGuildMsgs;			// ���޼��� �����̳�
		type_vector_msgs	m_vecUnionMsgs;			// ���ո޼��� �����̳�
		type_vector_msgs	m_VecSystemMsgs;		// �ý��۸޼��� �����̳�
		type_vector_msgs	m_vecErrorMsgs;			// �����޼��� �����̳�
		type_vector_msgs	m_vecGMMsgs;			// GM�޼��� �����̳�
#else // KJH_FIX_UI_CHAT_MESSAGE
		type_vector_msgs	m_vecMsgs;				// ��ü�޼��� �����̳�
#endif // KJH_FIX_UI_CHAT_MESSAGE
		type_vector_filters	m_vecFilters;
		
		POINT	m_WndPos, m_ScrollBtnPos;
		SIZE	m_WndSize;
		int		m_nShowingLines;
#ifdef KJH_FIX_UI_CHAT_MESSAGE					
		MESSAGE_TYPE		m_CurrentRenderMsgType;				// ���� �������� �޼��� Ÿ�� 
		bool				m_bShowChatLog;						// ä�ø޼��� On/Off
#endif // KJH_FIX_UI_CHAT_MESSAGE
		int		m_iCurrentRenderEndLine;
		int		m_iGrapRelativePosY;
		float	m_fBackAlpha;
		
		EVENT_STATE			m_EventState;
		
		bool m_bShowFrame;
#ifndef KJH_FIX_UI_CHAT_MESSAGE					// #ifndef ������ �� ������ �ϴ� �ҽ�
		SHOW_MESSAGE_FLAG m_ShowMessageFlag;
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
		
		// �޼����� ���콺�� ����Ű�� �ִ°�?
		bool m_bPointedMessage;
		int m_iPointedMessageIndex;
		
		void Init();
		void LoadImages();
		void UnloadImages();

		bool RenderBackground();
#ifdef KJH_FIX_UI_CHAT_MESSAGE
		bool RenderMessage( const type_string& MsgText, const POINT& Pos, DWORD dwTextColor, DWORD dwTextBG, HFONT hFont = g_hFont );
#endif // KJH_FIX_UI_CHAT_MESSAGE
		bool RenderMessages();
		bool RenderFrame();
		
	public:
		CNewUIChatLogWindow();
		virtual ~CNewUIChatLogWindow();
		
		bool Create(CNewUIManager* pNewUIMng, int x, int y, int nShowingLines = 6);
		void Release();
		
		void SetPosition(int x, int y);
#ifdef KJH_FIX_UI_CHAT_MESSAGE
		void AddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType, MESSAGE_TYPE ErrMsgType = TYPE_ALL_MESSAGE);
		void RemoveFrontLine(MESSAGE_TYPE MsgType);
		void Clear(MESSAGE_TYPE MsgType);
		void ClearAll();

		size_t GetNumberOfLines(MESSAGE_TYPE MsgType);
		MESSAGE_TYPE GetCurrentMsgType() const;

		void ChangeMessage(MESSAGE_TYPE MsgType);

		void ShowChatLog();
		void HideChatLog();
#else // KJH_FIX_UI_CHAT_MESSAGE
		void AddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType);
		void RemoveFrontLine();
		void Clear();
		
		size_t GetNumberOfLines() const;
#endif // KJH_FIX_UI_CHAT_MESSAGE

		int GetCurrentRenderEndLine() const;
		void Scrolling(int nRenderEndLine);
		
		void SetFilterText(const type_string& strFilterText);
		void ResetFilter();
		
		void SetSizeAuto();
		void SetNumberOfShowingLines(int nShowingLines, OUT LPSIZE lpBoxSize = NULL);	//. ����ó�� ����
		size_t GetNumberOfShowingLines() const;
		void SetBackAlphaAuto();
		void SetBackAlpha(float fAlpha);
		float GetBackAlpha() const;

		void ShowFrame();
		void HideFrame();
		bool IsShowFrame();

		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();	// g_pRenderText

		float GetLayerDepth();	//. 6.1f
		float GetKeyEventOrder();	//. 8.0f
		
		//. ���� iSearchLine������, ���� ���ڿ��� �ִ��� �˻��Ѵ�.
		bool CheckChatRedundancy(const type_string& strText, int iSearchLine = 1);

#ifndef KJH_FIX_UI_CHAT_MESSAGE					// #ifndef ������ �� ������ �ϴ� �ҽ�
		void ShowMessage(SHOW_MESSAGE_FLAG Flag);
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

		void UpdateWndSize();
		void UpdateScrollPos();

	protected:
#ifdef KJH_FIX_UI_CHAT_MESSAGE
		type_vector_msgs* GetMsgs(MESSAGE_TYPE MsgType);
		void ProcessAddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType, MESSAGE_TYPE ErrMsgType);
#else // KJH_FIX_UI_CHAT_MESSAGE
		void ProcessAddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType);
#endif // KJH_FIX_UI_CHAT_MESSAGE
		
		void SeparateText(IN const type_string& strID, IN const type_string& strText, OUT type_string& strText1, OUT type_string& strText2);

		bool CheckFilterText(const type_string& strTestText);
		void AddFilterWord(const type_string& strWord);

#ifndef KJH_FIX_UI_CHAT_MESSAGE					// #ifndef ������ �� ������ �ϴ� �ҽ�
		bool CheckMessageShowFlag(SHOW_MESSAGE_FLAG Flag);
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
	};
}

#endif // _NEWCHATLONGWINDOW_H_