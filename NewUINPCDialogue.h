//*****************************************************************************
// File: NewUINPCDialogue.h
//
// Desc: interface for the CNewUINPCDialogue class.
//		 NPC�� ��ȭ �������� ����Ǵ� â Ŭ����.(2009.09.14)
//		 NPC�� Ŭ���ϸ� ��Ÿ���� UI�� ����Ʈ NPC, �ս� NPC ���� ���. 
//
// producer: Ahn Sang-Gyu
//*****************************************************************************

#if !defined(AFX_NEWUINPCDIALOGUE_H__5E3DE00E_7D68_42C8_A796_AA368AD96ECC__INCLUDED_)
#define AFX_NEWUINPCDIALOGUE_H__5E3DE00E_7D68_42C8_A796_AA368AD96ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef ASG_ADD_UI_NPC_DIALOGUE

#include "NewUIBase.h"
#include "NewUIQuestProgress.h"

#define ND_NPC_LINE_MAX				35	// NPC ��� �ִ� �� ��.
#define ND_WORDS_ROW_MAX			64	// ��� �� �� �� �ִ� ���� �� + ���� ����.
#define ND_QUEST_INDEX_MAX_COUNT	20	// ����Ʈ �ε��� �ִ� ����.
#define ND_SEL_TEXT_LINE_MAX		((ND_QUEST_INDEX_MAX_COUNT+1)*2)	// ���ù� �ִ� �� ��.(+1�� "���ư���" ���ù�)
#define ND_SEL_TEXT_PAGE_LIMIT		4	// ���ù� �ִ� ���� ������.

namespace SEASON3B
{
	class CNewUINPCDialogue : public CNewUIObj  
	{
	public:
		enum IMAGE_LIST
		{
			IMAGE_ND_BACK = CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,			// newui_msgbox_back.jpg
			IMAGE_ND_TOP = CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP,		// newui_item_back01.tga	(190,64)
			IMAGE_ND_LEFT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,		// newui_item_back02-l.tga	(21,320)
			IMAGE_ND_RIGHT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,	// newui_item_back02-r.tga	(21,320)
			IMAGE_ND_BOTTOM = CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,	// newui_item_back03.tga	(190,45)

			IMAGE_ND_LINE = CNewUIMyQuestInfoWindow::IMAGE_MYQUEST_LINE,
			IMAGE_ND_BTN_L = CNewUIQuestProgress::IMAGE_QP_BTN_L,				// Quest_bt_L.tga	(17,36)
			IMAGE_ND_BTN_R = CNewUIQuestProgress::IMAGE_QP_BTN_R,				// Quest_bt_R.tga	(17,36)
			IMAGE_ND_BTN_CLOSE = CNewUIMyInventory::IMAGE_INVENTORY_EXIT_BTN,

#ifdef ASG_ADD_GENS_SYSTEM
			IMAGE_ND_CONTRIBUTE_BG = BITMAP_INTERFACE_NPC_DIALOGUE_BEGIN,
#endif	// ASG_ADD_GENS_SYSTEM
		};	
		
	private:
		enum
		{
			ND_WIDTH = 190,
			ND_HEIGHT = 429,
		};
		
		CNewUIManager*		m_pNewUIMng;			// UI �Ŵ���.
		POINT				m_Pos;					// â�� ��ġ.
		
		CNewUIButton		m_btnProgressL;			// ��ȭ ���� L ��ư.
		CNewUIButton		m_btnProgressR;			// ��ȭ ���� R ��ư.
		CNewUIButton		m_btnSelTextL;			// ���ù� ������ �ѱ�� L ��ư.
		CNewUIButton		m_btnSelTextR;			// ���ù� ������ �ѱ�� R ��ư.
		CNewUIButton		m_btnClose;
		
		char	m_aszNPCWords[ND_NPC_LINE_MAX][ND_WORDS_ROW_MAX];	// NPC ��� ���ڿ� �迭.
		int		m_nSelNPCPage;			// ���õ� NPC ��� ������(0 ~ 4).
		int		m_nMaxNPCPage;			// �ִ� NPC ��� ��������(0 ~ 4).
		
		char	m_aszSelTexts[ND_SEL_TEXT_LINE_MAX][ND_WORDS_ROW_MAX];	// ���ù� ���ڿ� �迭.
		int		m_nSelTextCount;		// ���ù� ����.
		int		m_anSelTextLine[ND_QUEST_INDEX_MAX_COUNT+1];	// �� ���ù� �� ��.
		int		m_nSelSelText;			// ������ ���ù� ��ȣ.
		int		m_nSelSelTextPage;		// ���õ� ���ù� ������(0 ~ 3).
		int		m_nMaxSelTextPage;		// �ִ� ���ù� ��������(0 ~ 3).
		int		m_anSelTextLinePerPage[ND_SEL_TEXT_PAGE_LIMIT];		// ���ù� �� ������ �� �� ��.
		int		m_anSelTextCountPerPage[ND_SEL_TEXT_PAGE_LIMIT];	// ���ù� �� ������ �� ����.

		enum LOWER_VIEW_MODE
		{
			NON_SEL_TEXTS_MODE,			// ���ù� �Ⱥ�����.
			SEL_TEXTS_MODE,				// ���ù� ������.
		};
		LOWER_VIEW_MODE	m_eLowerView;	// â�� �ϴ� �κ� ����.

		bool	m_bQuestListMode;		// ����Ʈ ����Ʈ ����̸� true.
		DWORD	m_dwCurDlgIndex;		// ���� ���� ���� ��ȭ �ε���.(m_bQuestListMode�� false�� ��츸 ���)
		DWORD	m_adwQuestIndex[ND_QUEST_INDEX_MAX_COUNT];	// ����Ʈ �ε��� �迭.(m_bQuestListMode�� true�� ��츸 ���)

		bool	m_bCanClick;			// ���ù� �� ����Ʈ ó�� ��ư Ŭ�� ���� ����.(������ Ŭ�� ����)
		DWORD	m_dwContributePoint;	// �⿩��.

	public:
		CNewUINPCDialogue();
		virtual ~CNewUINPCDialogue();

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
		
		void SetContents(DWORD dwDlgIndex);
		void SetContributePoint(DWORD dwContributePoint);

		void ProcessQuestListReceive(DWORD* adwSrcQuestIndex, int nIndexCount);
		void ProcessGensJoiningReceive(BYTE byResult, BYTE byInfluence);
		void ProcessGensSecessionReceive(BYTE byResult);
#ifdef PBG_ADD_GENSRANKING
		void ProcessGensRewardReceive(BYTE byResult);
#endif //PBG_ADD_GENSRANKING
		
	private:
		void LoadImages();
		void UnloadImages();
		
		bool UpdateSelTextMouseEvent();
		void RenderBackImage();
		void RenderSelTextBlock();
		void RenderText();
#ifdef ASG_ADD_GENS_SYSTEM
		void RenderContributePoint();
#endif	// ASG_ADD_GENS_SYSTEM
		
		bool ProcessBtns();
		
		void SetCurNPCWords(int nQuestListCount = 0);
		void SetCurSelTexts();
		void SetQuestListText(DWORD* adwSrcQuestIndex, int nIndexCount);
		void CalculateSelTextMaxPage(int nSelTextCount);

		void ProcessSelTextResult();
	};
}

#endif	// ASG_ADD_UI_NPC_DIALOGUE

#endif // !defined(AFX_NEWUINPCDIALOGUE_H__5E3DE00E_7D68_42C8_A796_AA368AD96ECC__INCLUDED_)
