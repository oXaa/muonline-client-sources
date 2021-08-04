//*****************************************************************************
// File: NewUIQuestProgressByEtc.h
//
// Desc: interface for the CNewUIQuestProgressByEtc class.
//		 �ű� (��Ÿ ��Ȳ���� ����)����Ʈ ���� â Ŭ����.(2009.06.24)
//		 NPC�� Ŭ���Ͽ� ����Ǵ� ����Ʈ�� �ƴ� ����Ʈ ������ �� UI�� ����.
//
// producer: Ahn Sang-Gyu
//*****************************************************************************

#if !defined(AFX_NEWUIQUESTPROGRESSBYETC_H__0D2110D4_FB24_4DA3_A2BC_198111DF4413__INCLUDED_)
#define AFX_NEWUIQUESTPROGRESSBYETC_H__0D2110D4_FB24_4DA3_A2BC_198111DF4413__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC

#include "NewUIBase.h"
#include "NewUIMyQuestInfoWindow.h"
#include "NewUIQuestProgress.h"
#include "QuestMng.h"

#define QPE_NPC_LINE_MAX	35	// NPC ��� �ִ� �� ��.
#define QPE_PLAYER_LINE_MAX	10	// �÷��̾� ��� �ִ� �� ��.
#define QPE_WORDS_ROW_MAX	64	// ��� �� �� �� �ִ� ���� �� + ���� ����.

namespace SEASON3B
{
	class CNewUIQuestProgressByEtc : public CNewUIObj  
	{
	public:
		enum IMAGE_LIST
		{
			IMAGE_QPE_BACK = CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,			// newui_msgbox_back.jpg
			IMAGE_QPE_TOP = CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP2,		// newui_item_back04.tga	(190,64)
			IMAGE_QPE_LEFT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,		// newui_item_back02-l.tga	(21,320)
			IMAGE_QPE_RIGHT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,	// newui_item_back02-r.tga	(21,320)
			IMAGE_QPE_BOTTOM = CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,	// newui_item_back03.tga	(190,45)

			IMAGE_QPE_LINE = CNewUIMyQuestInfoWindow::IMAGE_MYQUEST_LINE,
#ifdef ASG_ADD_UI_QUEST_PROGRESS
			IMAGE_QPE_BTN_L = CNewUIQuestProgress::IMAGE_QP_BTN_L,				// Quest_bt_L.tga	(17,36)
			IMAGE_QPE_BTN_R = CNewUIQuestProgress::IMAGE_QP_BTN_R,				// Quest_bt_R.tga	(17,36)
#endif	// ASG_ADD_UI_QUEST_PROGRESS
			IMAGE_QPE_BTN_COMPLETE = CNewUIMessageBoxMng::IMAGE_MSGBOX_BTN_EMPTY,
			IMAGE_QPE_BTN_CLOSE = CNewUIMyInventory::IMAGE_INVENTORY_EXIT_BTN,
		};	

	private:
		enum
		{
			QPE_WIDTH = 190,
			QPE_HEIGHT = 429,
		};

		CNewUIManager*		m_pNewUIMng;			// UI �Ŵ���.
		POINT				m_Pos;					// â�� ��ġ.
		
		CNewUIButton		m_btnProgressL;			// ��ȭ ���� L ��ư.
		CNewUIButton		m_btnProgressR;			// ��ȭ ���� R ��ư.
		CNewUIButton		m_btnComplete;			// ����Ʈ �Ϸ� ��ư.
		CNewUIButton		m_btnClose;

		DWORD	m_dwCurQuestIndex;		// ���� ���� ���� ����Ʈ �ε���.

		char	m_aszNPCWords[QPE_NPC_LINE_MAX][QPE_WORDS_ROW_MAX];	// NPC ���.
		int		m_nSelNPCPage;			// ���õ� NPC ��� ������(0 ~ 4).
		int		m_nMaxNPCPage;			// �ִ� NPC ��� ��������(0 ~ 4).

		enum LOWER_VIEW_MODE
		{
			NON_PLAYER_WORDS_MODE,		// �÷��̾� ��� �Ⱥ�����.
			PLAYER_WORDS_MODE,			// �÷��̾� ��� ������.
			REQUEST_REWARD_MODE			// �䱸 ����, ���� ������.
		};
		LOWER_VIEW_MODE	m_eLowerView;	// â�� �ϴ� �κ� ����.

		char	m_aszPlayerWords[QPE_PLAYER_LINE_MAX][QPE_WORDS_ROW_MAX];	// �÷��̾� ���.
		int		m_anAnswerLine[QM_MAX_ANSWER];	// �� ���ù� �� ��.
		int		m_nSelAnswer;			// ������ ���ù� ��ȣ.

		CUIQuestContentsListBox	m_RequestRewardListBox;	// �䱸 ����, ���� ����Ʈ �ڽ�.
		bool	m_bRequestComplete;		// �䱸 ���� ���� ����.
		
		bool	m_bCanClick;			// ���ù� �� ����Ʈ ó�� ��ư Ŭ�� ���� ����.(������ Ŭ�� ����)

	public:
		CNewUIQuestProgressByEtc();
		virtual ~CNewUIQuestProgressByEtc();

		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();
		
		bool IsVisible() const;
		
		float GetLayerDepth();	//. 3.1f
		
		void ProcessOpening();
		bool ProcessClosing();
		
		void SetContents(DWORD dwQuestIndex);
#ifdef ASG_MOD_QUEST_OK_BTN_DISABLE
		void EnableCompleteBtn(bool bEnable);
#endif	// ASG_MOD_QUEST_OK_BTN_DISABLE
		
	private:
		void LoadImages();
		void UnloadImages();
		
		bool UpdateSelTextMouseEvent();
		void RenderBackImage();
		void RenderSelTextBlock();
		void RenderText();
		
		bool ProcessBtns();
		
		void SetCurNPCWords();
		void SetCurPlayerWords();
		void SetCurRequestReward();
	};
}

#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC

#endif // !defined(AFX_NEWUIQUESTPROGRESSBYETC_H__0D2110D4_FB24_4DA3_A2BC_198111DF4413__INCLUDED_)
