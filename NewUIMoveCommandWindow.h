// NewUIMoveCommandWindow.h: interface for the CNewUIMoveCommandWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWUIMOVECOMMANDWINDOW_H__E6ABC928_0A79_41CD_8046_5ED052B1985A__INCLUDED_)
#define AFX_NEWUIMOVECOMMANDWINDOW_H__E6ABC928_0A79_41CD_8046_5ED052B1985A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NewUIBase.h"
#include "NewUIManager.h"
#include "MoveCommandData.h"
#include "NewUIChatLogWindow.h"

#ifdef YDG_ADD_ENC_MOVE_COMMAND_WINDOW

namespace SEASON3B
{
	class CNewUIMoveCommandWindow : public CNewUIObj
	{
#ifdef YDG_MOD_PROTECT_AUTO_V4
		friend class CMoveCommandWindowEncrypt;
#endif	// YDG_MOD_PROTECT_AUTO_V4
		enum IMAGE_LIST
		{
			IMAGE_MOVECOMMAND_SCROLL_TOP	= CNewUIChatLogWindow::IMAGE_SCROLL_TOP,			// newui_scrollbar_up.tga (7,3)
			IMAGE_MOVECOMMAND_SCROLL_MIDDLE	= CNewUIChatLogWindow::IMAGE_SCROLL_MIDDLE,			// newui_scrollbar_m.tga (7,15)
			IMAGE_MOVECOMMAND_SCROLL_BOTTOM	= CNewUIChatLogWindow::IMAGE_SCROLL_BOTTOM,			// newui_scrollbar_down.tga (7,3)
			IMAGE_MOVECOMMAND_SCROLLBAR_ON	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_ON,			// newui_scroll_On.tga (15,30)	
			IMAGE_MOVECOMMAND_SCROLLBAR_OFF	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_OFF,			// newui_scroll_Off.tga (15,30)
			//IMAGE_MOVECOMMAND_DRAG_BTN		= CNewUIChatLogWindow::IMAGE_DRAG_BTN			
		};
		
		enum 
		{
			MOVECOMMAND_SCROLLBTN_WIDTH = 15,
			MOVECOMMAND_SCROLLBTN_HEIGHT = 30,
			MOVECOMMAND_SCROLLBAR_TOP_WIDTH = 7,
			MOVECOMMAND_SCROLLBAR_TOP_HEIGHT = 3,
			MOVECOMMAND_SCROLLBAR_MIDDLE_WIDTH = 7,
			MOVECOMMAND_SCROLLBAR_MIDDLE_HEIGHT = 15,

			// �ؿ� ���� �⺻ �ʱⰪ���θ� ����ϰ� ���� ������ m_iTextLine ������ �̷�� ����.
			MOVECOMMAND_MAX_RENDER_TEXTLINE = 16,		// �̵���� ����â�� �������� �ؽ�Ʈ������ ���⼭ ���Ѵ�.(Default: 16)
		};

		enum MOVECOMMAND_MOUSE_EVENT
		{
			MOVECOMMAND_MOUSEBTN_NORMAL = 0,
			MOVECOMMAND_MOUSEBTN_OVER,
			MOVECOMMAND_MOUSEBTN_CLICKED,
		};

	protected:
//$$AUTO_BUILD_LINE_ SHUFFLE_BEGIN	// ������ �ӽ÷� ����
		CNewUIManager*				m_pNewUIMng;
		POINT						m_Pos;

		int							m_iRealFontHeight;
			
		std::list<CMoveCommandData::MOVEINFODATA*>	m_listMoveInfoData;
		POINT						m_StartUISubjectName;	// UI���� ��ġ
		POINT						m_StartMapNamePos;		// �� �̸� ���� ��ġ
		POINT						m_MapNameUISize;		// �� �̵����UI SIZE
#ifdef ASG_ADD_GENS_SYSTEM
		POINT						m_StrifePos;			// ��������
#endif	// ASG_ADD_GENS_SYSTEM
		POINT						m_MapNamePos;
		POINT						m_ReqLevelPos;
		POINT						m_ReqZenPos;
		int							m_iSelectedMapName;		// ���õ� ���ε���

		POINT						m_ScrollBarPos;
		POINT						m_ScrollBtnStartPos;
		POINT						m_ScrollBtnPos;

		int							m_iScrollBarHeightPixel;	// ��ũ�ѹ� ����
		int							m_iRenderStartTextIndex;	// UI�� �����Ǵ� ó�� Text�� �ε���
		int							m_iRenderEndTextIndex;		// UI�� �����Ǵ� ������ Text�� �ε���
		int							m_iSelectedTextIndex;		// ���� ���õ� Text
		int							m_iScrollBtnInterval;		// ��ũ�ѹ� �����̴� ����
		int							m_iScrollBarMiddleNum;				// ��ũ�ѹ� Middle ����
		int							m_iScrollBarMiddleRemainderPixel;	// ��ũ�ѹ� Middle������� ������ ���� �ȼ�
		int							m_iNumPage;					// ��ü������
		int							m_iCurPage;					// ����������
		int							m_iTotalMoveScrBtnPixel;			// ��ũ�ѹ�ư�� ��ü �ȼ���
		int							m_iRemainMoveScrBtnPixel;		// ��ũ�ѹ�ư�� �̵��ؾ��� ������ �ȼ���
		int							m_icurMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� ���� �̵� �ȼ���
		int							m_iMaxMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� �̵��ϴ� �ִ��ȼ���
		int							m_iMinMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� �̵��ϴ� �ּ��ȼ���
		int							m_iTotalMoveScrBtnperStep;		// ��ũ�ѹ�ư�� �̵��ؾ��� ��ü ĭ�� ����
		int							m_iRemainMoveScrBtnperStep;		// ��ũ�ѹ�ư�� �̵��ؾ��� ������ ĭ�� ����
		int							m_iTotalNumMaxMoveScrBtnperStep;	// ��ũ�ѹ�ư�� �ִ��̵�ĭ�� ��ü ����
		int							m_iTotalNumMinMoveScrBtnperStep;	// ��ũ�ѹ�ư�� �ּ��̵�ĭ�� ��ü ����
		int							m_iAcumMoveMouseScrollPixel;		// ���콺 ��ũ�Ѱ� ����(��ĭ �̵��Ҷ� ���δ�. ScrollUp/ScrollDown)
		int							m_iMousePosY;
		int							m_iScrollBtnMouseEvent;				// ��ũ�� ��ư ���콺 Ŭ��
		bool						m_bScrollBtnActive;					// ��ũ�ѹ�ư Ȱ��ȭ

		int							m_iPosY_Random;			// Y��ġ ������
		int							m_iPosY_Random_Min;		// Y��ġ ���� �ּҰ� 
		int							m_iPosY_Random_Range;	// Y��ġ ������ ����
		POINT						m_Pos_Start;			// â ���� ���� ��ġ Create�Լ� ȣ�� �� �� �Է� ���� ��
		int							m_iWindowOpenCount;		// â �� Ƚ��
		int							m_iWorldIndex;			// �� �ε���
		bool						m_bCastleOwner;			// ������ ��峪 �����̸� true �ƴϸ� false
		int							m_iTextLine;			// ȭ�鿡 ǥ�õ� �ؽ�Ʈ ���μ�
		int							m_iTextAlpha;			// �ؽ�Ʈ ���İ�
		int							m_iTopSpace;			// ��� ����
		int							m_iWheelCounter;		// ���� ó���� �� ī����
//$$AUTO_BUILD_LINE_ SHUFFLE_END
		float						m_fBackgroundAlpha;		// ��� ���İ�
#ifdef YDG_MOD_PROTECT_AUTO_V4_R3
		BYTE *						m_pbtKeyAddressBlock3;
#endif	// YDG_MOD_PROTECT_AUTO_V4_R3
#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
		DWORD						m_dwMoveCommandKey;		// �̵� ��� ���۽� Ű ��
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

	public:
		CNewUIMoveCommandWindow();
		virtual ~CNewUIMoveCommandWindow();
		
		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();
		
		bool BtnProcess();
		
		float GetLayerDepth();	//. 6.4f
		
		virtual void OpenningProcess();
		void ClosingProcess();

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
		void ResetWindowOpenCount();
		void SetCastleOwner(bool bOwner);
		bool IsCastleOwner();
#endif // CSK_MOD_MOVE_COMMAND_WINDOW

#ifdef CSK_LUCKY_SEAL
		bool IsLuckySealBuff();
		bool IsMapMove( const string& src );
#endif //CSK_LUCKY_SEAL

#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
		void SetMoveCommandKey(DWORD dwKey);	// �ʱⰪ ����
		DWORD GetMoveCommandKey();				// �ʱⰪ�� �������� Ű���� ������ [����!] SendRequestMoveMap �ѹ� ������ �ѹ��� ȣ��Ǿ�� �Ѵ�!
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

#ifdef LJH_ADD_SAVEOPTION_WHILE_MOVING_FROM_OR_TO_DIFF_SERVER
		BOOL IsTheMapInDifferentServer(const int iFromMapIndex, const int iToMapIndex) const;
#endif //LJH_ADD_SAVEOPTION_WHILE_MOVING_FROM_OR_TO_DIFF_SERVER
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		int GetMapIndexFromMovereq(const char *pszMapName);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	protected:
#ifdef ASG_ADD_GENS_SYSTEM
		void SetStrifeMap();
#endif	// ASG_ADD_GENS_SYSTEM
		void SettingCanMoveMap();
		void RenderFrame();
		//void MoveScrollBtn(int iMoveValue);
		void UpdateScrolling();
		void ScrollUp(int iMoveValue);
		void ScrollDown(int iMoveValue);
#ifdef KJH_FIX_MOVECOMMAND_WINDOW_SIZE
		// bSign : true(DownScroll,+), false(UpScroll,-)
		void RecursiveCalcScroll(IN int piScrollValue, OUT int* piMovePixel, bool bSign = true);
#endif // KJH_FIX_MOVECOMMAND_WINDOW_SIZE
		void LoadImages();
		void UnloadImages();
	};
	
#ifdef YDG_MOD_PROTECT_AUTO_V4
	class CMoveCommandWindowEncrypt
	{
	public:
		CMoveCommandWindowEncrypt();
		virtual ~CMoveCommandWindowEncrypt();
		static void Enable(BOOL bFlag);	// CMoveCommandWindow�� �ʱ�ȭ �ɶ� �ѹ��� ȣ��
#ifdef YDG_MOD_PROTECT_AUTO_V4_R2
#ifdef YDG_MOD_PROTECT_AUTO_V4_R4
		static int __fastcall Read(int * piValue);
		static LONG __fastcall Read(LONG * plValue);
		static void __fastcall Write(int * piValue, int iValue);
		static void __fastcall Write(LONG * plValue, LONG lValue);
#else	// YDG_MOD_PROTECT_AUTO_V4_R4
		static int Read(int * piValue);
		static LONG Read(LONG * plValue);
		static void Write(int * piValue, int iValue);
		static void Write(LONG * plValue, LONG lValue);
#endif	// YDG_MOD_PROTECT_AUTO_V4_R4
#endif	// YDG_MOD_PROTECT_AUTO_V4_R2
#ifdef YDG_MOD_PROTECT_AUTO_V4_R3
		static void CreateKey(BOOL bInit = FALSE);
		static void DeleteKey();
		static void CreateFakeKey();
#endif	// YDG_MOD_PROTECT_AUTO_V4_R3

	protected:
		static void Encrypt(int * piValue);
		static void Decrypt(int * piValue);
		static void Encrypt(POINT * pValue);
		static void Decrypt(POINT * pValue);
		static void EncryptWindowPos();
		static void DecryptWindowPos();

	protected:
		static DWORD m_dwEncryptSeed;
		static int m_iEncryptCounter;	// 0: ��ȣȭ, 1+:��ȣ ��������
	};
#endif	// YDG_MOD_PROTECT_AUTO_V4
};

#else	// YDG_ADD_ENC_MOVE_COMMAND_WINDOW































































namespace SEASON3B
{
	class CNewUIMoveCommandWindow : public CNewUIObj
	{
#ifdef YDG_MOD_PROTECT_AUTO_V4
		friend class CMoveCommandWindowEncrypt;
#endif	// YDG_MOD_PROTECT_AUTO_V4
		enum IMAGE_LIST
		{
			IMAGE_MOVECOMMAND_SCROLL_TOP	= CNewUIChatLogWindow::IMAGE_SCROLL_TOP,			// newui_scrollbar_up.tga (7,3)
			IMAGE_MOVECOMMAND_SCROLL_MIDDLE	= CNewUIChatLogWindow::IMAGE_SCROLL_MIDDLE,			// newui_scrollbar_m.tga (7,15)
			IMAGE_MOVECOMMAND_SCROLL_BOTTOM	= CNewUIChatLogWindow::IMAGE_SCROLL_BOTTOM,			// newui_scrollbar_down.tga (7,3)
			IMAGE_MOVECOMMAND_SCROLLBAR_ON	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_ON,			// newui_scroll_On.tga (15,30)	
			IMAGE_MOVECOMMAND_SCROLLBAR_OFF	= CNewUIChatLogWindow::IMAGE_SCROLLBAR_OFF,			// newui_scroll_Off.tga (15,30)
			//IMAGE_MOVECOMMAND_DRAG_BTN		= CNewUIChatLogWindow::IMAGE_DRAG_BTN			
		};
		
		enum 
		{
			MOVECOMMAND_SCROLLBTN_WIDTH = 15,
			MOVECOMMAND_SCROLLBTN_HEIGHT = 30,
			MOVECOMMAND_SCROLLBAR_TOP_WIDTH = 7,
			MOVECOMMAND_SCROLLBAR_TOP_HEIGHT = 3,
			MOVECOMMAND_SCROLLBAR_MIDDLE_WIDTH = 7,
			MOVECOMMAND_SCROLLBAR_MIDDLE_HEIGHT = 15,

			// �ؿ� ���� �⺻ �ʱⰪ���θ� ����ϰ� ���� ������ m_iTextLine ������ �̷�� ����.
#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
			MOVECOMMAND_MAX_RENDER_TEXTLINE = 16,		// �̵���� ����â�� �������� �ؽ�Ʈ������ ���⼭ ���Ѵ�.(Default: 16)
#else // CSK_MOD_MOVE_COMMAND_WINDOW
			MOVECOMMAND_MAX_RENDER_TEXTLINE = 31,		// �̵���� ����â�� �������� �ؽ�Ʈ������ ���⼭ ���Ѵ�.(Default: 31)
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
			
		};

		enum MOVECOMMAND_MOUSE_EVENT
		{
			MOVECOMMAND_MOUSEBTN_NORMAL = 0,
			MOVECOMMAND_MOUSEBTN_OVER,
			MOVECOMMAND_MOUSEBTN_CLICKED,
		};

#ifdef CSK_MOD_PROTECT_AUTO_V1
	protected:
#else // CSK_MOD_PROTECT_AUTO_V1
	private:
#endif // CSK_MOD_PROTECT_AUTO_V1
	
//$$AUTO_BUILD_LINE_ SHUFFLE_BEGIN
		CNewUIManager*				m_pNewUIMng;
		POINT						m_Pos;

		int							m_iRealFontHeight;
			
		std::list<CMoveCommandData::MOVEINFODATA*>	m_listMoveInfoData;
		POINT						m_StartUISubjectName;	// UI���� ��ġ
		POINT						m_StartMapNamePos;		// �� �̸� ���� ��ġ
		POINT						m_MapNameUISize;		// �� �̵����UI SIZE
#ifdef ASG_ADD_GENS_SYSTEM
		POINT						m_StrifePos;			// ��������
#endif	// ASG_ADD_GENS_SYSTEM
		POINT						m_MapNamePos;
		POINT						m_ReqLevelPos;
		POINT						m_ReqZenPos;
		int							m_iSelectedMapName;		// ���õ� ���ε���

		POINT						m_ScrollBarPos;
		POINT						m_ScrollBtnStartPos;
		POINT						m_ScrollBtnPos;

		int							m_iScrollBarHeightPixel;	// ��ũ�ѹ� ����
		int							m_iRenderStartTextIndex;	// UI�� �����Ǵ� ó�� Text�� �ε���
		int							m_iRenderEndTextIndex;		// UI�� �����Ǵ� ������ Text�� �ε���
		int							m_iSelectedTextIndex;		// ���� ���õ� Text
		int							m_iScrollBtnInterval;		// ��ũ�ѹ� �����̴� ����
		int							m_iScrollBarMiddleNum;				// ��ũ�ѹ� Middle ����
		int							m_iScrollBarMiddleRemainderPixel;	// ��ũ�ѹ� Middle������� ������ ���� �ȼ�
		int							m_iNumPage;					// ��ü������
		int							m_iCurPage;					// ����������
//$$AUTO_BUILD_LINE_ SHUFFLE_END
#ifdef KJH_FIX_MOVECOMMAND_WINDOW_SIZE
//$$AUTO_BUILD_LINE_ SHUFFLE_BEGIN
		int							m_iTotalMoveScrBtnPixel;			// ��ũ�ѹ�ư�� ��ü �ȼ���
		int							m_iRemainMoveScrBtnPixel;		// ��ũ�ѹ�ư�� �̵��ؾ��� ������ �ȼ���
		int							m_icurMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� ���� �̵� �ȼ���
		int							m_iMaxMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� �̵��ϴ� �ִ��ȼ���
		int							m_iMinMoveScrBtnPixelperStep;	// ��ũ�ѹ�ư�� �̵��ϴ� �ּ��ȼ���
		int							m_iTotalMoveScrBtnperStep;		// ��ũ�ѹ�ư�� �̵��ؾ��� ��ü ĭ�� ����
		int							m_iRemainMoveScrBtnperStep;		// ��ũ�ѹ�ư�� �̵��ؾ��� ������ ĭ�� ����
		int							m_iTotalNumMaxMoveScrBtnperStep;	// ��ũ�ѹ�ư�� �ִ��̵�ĭ�� ��ü ����
		int							m_iTotalNumMinMoveScrBtnperStep;	// ��ũ�ѹ�ư�� �ּ��̵�ĭ�� ��ü ����
		int							m_iAcumMoveMouseScrollPixel;		// ���콺 ��ũ�Ѱ� ����(��ĭ �̵��Ҷ� ���δ�. ScrollUp/ScrollDown)
//$$AUTO_BUILD_LINE_ SHUFFLE_END
#else KJH_FIX_MOVECOMMAND_WINDOW_SIZE		// �����Ҷ� ������ �ϴ¼ҽ�
		int							m_iMoveSCBtnPerPage;		// �������� ��ũ�ѹ�ư �̵���
		int							m_iNumMoveStep;				// ��ũ�� �����̴� �ܰ�
		int							m_iHeightByMoveStep;		// ��ũ�� �����̴� �ܰ� ��������
#endif // KJH_FIX_MOVECOMMAND_WINDOW_SIZE	// �����Ҷ� ������ �ϴ¼ҽ�
//$$AUTO_BUILD_LINE_ SHUFFLE_BEGIN
		int							m_iMousePosY;
		int							m_iScrollBtnMouseEvent;				// ��ũ�� ��ư ���콺 Ŭ��
		bool						m_bScrollBtnActive;					// ��ũ�ѹ�ư Ȱ��ȭ
//$$AUTO_BUILD_LINE_ SHUFFLE_END
		

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
//$$AUTO_BUILD_LINE_ SHUFFLE_BEGIN
		int							m_iPosY_Random;			// Y��ġ ������
		int							m_iPosY_Random_Min;		// Y��ġ ���� �ּҰ� 
		int							m_iPosY_Random_Range;	// Y��ġ ������ ����
		POINT						m_Pos_Start;			// â ���� ���� ��ġ Create�Լ� ȣ�� �� �� �Է� ���� ��
		int							m_iWindowOpenCount;		// â �� Ƚ��
		int							m_iWorldIndex;			// �� �ε���
		bool						m_bCastleOwner;			// ������ ��峪 �����̸� true �ƴϸ� false
//$$AUTO_BUILD_LINE_ SHUFFLE_END
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
#ifdef CSK_MOD_PROTECT_AUTO_V1
		int							m_iTextLine;			// ȭ�鿡 ǥ�õ� �ؽ�Ʈ ���μ�
#ifndef CSK_MOD_REMOVE_AUTO_V1_FLAG		// ������ �� ������ �ϴ� �ҽ�
		bool						m_bNewVersion;			// ��â ���ο� �����ΰ�
#endif //! CSK_MOD_REMOVE_AUTO_V1_FLAG	// ������ �� ������ �ϴ� �ҽ�
		int							m_iTextAlpha;			// �ؽ�Ʈ ���İ�
		float						m_fBackgroundAlpha;		// ��� ���İ�
		int							m_iTopSpace;			// ��� ����
#endif // CSK_MOD_PROTECT_AUTO_V1	
#ifdef YDG_MOD_PROTECT_AUTO_V3
		int							m_iWheelCounter;		// ���� ó���� �� ī����
#endif	// YDG_MOD_PROTECT_AUTO_V3
#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
		DWORD						m_dwMoveCommandKey;		// �̵� ��� ���۽� Ű ��
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

	public:
		CNewUIMoveCommandWindow();
		virtual ~CNewUIMoveCommandWindow();
		
		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();
		
		bool BtnProcess();
		
		float GetLayerDepth();	//. 6.4f
		
		virtual void OpenningProcess();
		void ClosingProcess();

#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
		void ResetWindowOpenCount();
		void SetCastleOwner(bool bOwner);
		bool IsCastleOwner();
#endif // CSK_MOD_MOVE_COMMAND_WINDOW

#ifndef CSK_MOD_REMOVE_AUTO_V1_FLAG  // ������ �� ������ �ϴ� �ҽ�
		void SetNewVersion(bool bNew);
		bool IsNewVersion();
#endif //! CSK_MOD_REMOVE_AUTO_V1_FLAG // ������ �� ������ �ϴ� �ҽ�

#ifdef CSK_LUCKY_SEAL
		bool IsLuckySealBuff();
		bool IsMapMove( const string& src );
#endif //CSK_LUCKY_SEAL
	
#ifdef YDG_ADD_MOVE_COMMAND_PROTOCOL
		void SetMoveCommandKey(DWORD dwKey);	// �ʱⰪ ����
		DWORD GetMoveCommandKey();				// �ʱⰪ�� �������� Ű���� ������ [����!] SendRequestMoveMap �ѹ� ������ �ѹ��� ȣ��Ǿ�� �Ѵ�!
#endif	// YDG_ADD_MOVE_COMMAND_PROTOCOL

#ifdef LJH_ADD_SAVEOPTION_WHILE_MOVING_FROM_OR_TO_DIFF_SERVER
		BOOL IsTheMapInDifferentServer(const int iFromMapIndex, const int iToMapIndex) const;
#endif //LJH_ADD_SAVEOPTION_WHILE_MOVING_FROM_OR_TO_DIFF_SERVER
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		int GetMapIndexFromMovereq(const char *pszMapName);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#ifdef CSK_MOD_PROTECT_AUTO_V1
	protected:
#else // CSK_MOD_PROTECT_AUTO_V1
	private:
#endif // CSK_MOD_PROTECT_AUTO_V1
#ifdef ASG_ADD_GENS_SYSTEM
		void SetStrifeMap();
#endif	// ASG_ADD_GENS_SYSTEM
		void SettingCanMoveMap();
		void RenderFrame();
		//void MoveScrollBtn(int iMoveValue);
		void UpdateScrolling();
		void ScrollUp(int iMoveValue);
		void ScrollDown(int iMoveValue);
#ifdef KJH_FIX_MOVECOMMAND_WINDOW_SIZE
		// bSign : true(DownScroll,+), false(UpScroll,-)
		void RecursiveCalcScroll(IN int piScrollValue, OUT int* piMovePixel, bool bSign = true);
#endif // KJH_FIX_MOVECOMMAND_WINDOW_SIZE
		void LoadImages();
		void UnloadImages();
	};
	
#ifdef YDG_MOD_PROTECT_AUTO_V4
	class CMoveCommandWindowEncrypt
	{
	public:
		CMoveCommandWindowEncrypt();
		virtual ~CMoveCommandWindowEncrypt();
		static void Enable(BOOL bFlag);	// CMoveCommandWindow�� �ʱ�ȭ �ɶ� �ѹ��� ȣ��
#ifdef YDG_MOD_PROTECT_AUTO_V4_R2
		static int Read(int * piValue);
		static LONG Read(LONG * plValue);
		static void Write(int * piValue, int iValue);
		static void Write(LONG * plValue, LONG lValue);
#endif	// YDG_MOD_PROTECT_AUTO_V4_R2

	protected:
		static void Encrypt(int * piValue);
		static void Decrypt(int * piValue);
		static void Encrypt(POINT * pValue);
		static void Decrypt(POINT * pValue);
		static void EncryptWindowPos();
		static void DecryptWindowPos();

	protected:
		static DWORD m_dwEncryptSeed;
		static int m_iEncryptCounter;	// 0: ��ȣȭ, 1+:��ȣ ��������
	};
#endif	// YDG_MOD_PROTECT_AUTO_V4
};

#ifdef CSK_MOD_PROTECT_AUTO_V1
class CNewUIMoveCommandWindowNew : public SEASON3B::CNewUIMoveCommandWindow
{
public:
	CNewUIMoveCommandWindowNew();
	virtual ~CNewUIMoveCommandWindowNew();

	virtual void OpenningProcess();
};
#endif // CSK_MOD_PROTECT_AUTO_V1

#endif	// YDG_ADD_ENC_MOVE_COMMAND_WINDOW

#endif // !defined(AFX_NEWUIMOVECOMMANDWINDOW_H__E6ABC928_0A79_41CD_8046_5ED052B1985A__INCLUDED_)

