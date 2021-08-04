//*****************************************************************************
// File: NewUINPCDialogue.cpp
//
// Desc: implementation of the CNewUINPCDialogue class.
//
// producer: Ahn Sang-Gyu
//*****************************************************************************

#include "stdafx.h"
#include "NewUINPCDialogue.h"
#include "wsclientinline.h"
#include "CRTDBG.h"

#ifdef ASG_ADD_UI_NPC_DIALOGUE

using namespace SEASON3B;

#define ND_NPC_MAX_LINE_PER_PAGE		7	// NPC ��� �������� �ִ� �� ��.
#define ND_SEL_TEXT_MAX_LINE_PER_PAGE	11	// ���ù� �������� �ִ� �� ��.
#define ND_TEXT_GAP						15	// �ؽ�Ʈ ����.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewUINPCDialogue::CNewUINPCDialogue()
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
	m_dwContributePoint = 0;
}

CNewUINPCDialogue::~CNewUINPCDialogue()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : NPC ��ȭ â ����.
// �Ű� ���� : pNewUIMng	: CNewUIManager ������Ʈ �ּ�.
//			   x			: x ��ǥ.
//			   y			: y ��ǥ.
//*****************************************************************************
bool CNewUINPCDialogue::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if (NULL == pNewUIMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_NPC_DIALOGUE, this);

	SetPos(x, y);

	LoadImages();

	// ��ȭ ���� L,R ��ư.
	m_btnProgressL.ChangeButtonImgState(true, IMAGE_ND_BTN_L);
	m_btnProgressL.ChangeButtonInfo(x + 131, y + 165, 17, 18);
	m_btnProgressR.ChangeButtonImgState(true, IMAGE_ND_BTN_R);
	m_btnProgressR.ChangeButtonInfo(x + 153, y + 165, 17, 18);

	// ���ù� ������ �ѱ�� L,R ��ư.
	m_btnSelTextL.ChangeButtonImgState(true, IMAGE_ND_BTN_L);
	m_btnSelTextL.ChangeButtonInfo(x + 131, y + 372, 17, 18);
	m_btnSelTextR.ChangeButtonImgState(true, IMAGE_ND_BTN_R);
	m_btnSelTextR.ChangeButtonInfo(x + 153, y + 372, 17, 18);

	// �ݱ� ��ư.
	m_btnClose.ChangeButtonImgState(true, IMAGE_ND_BTN_CLOSE);
	m_btnClose.ChangeButtonInfo(x + 13, y + 392, 36, 29);
	m_btnClose.ChangeToolTipText(GlobalText[1002], true);

	m_nSelTextCount = 0;
	m_bQuestListMode = false;

	Show(false);

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : â Release.
//*****************************************************************************
void CNewUINPCDialogue::Release()
{
	UnloadImages();

	if (m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPos()
// �Լ� ���� : â ��ġ ����.
//*****************************************************************************
void CNewUINPCDialogue::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;

	m_btnProgressL.SetPos(x + 131, y + 165);			// ��ȭ ���� L ��ư.
	m_btnProgressR.SetPos(x + 153, y + 165);			// ��ȭ ���� R ��ư.
	m_btnSelTextL.SetPos(x + 131, y + 372);			// ��ȭ ���� L ��ư.
	m_btnSelTextR.SetPos(x + 153, y + 372);			// ��ȭ ���� R ��ư.
	m_btnClose.SetPos(x + 13, y + 392);
}

//*****************************************************************************
// �Լ� �̸� : UpdateMouseEvent()
// �Լ� ���� : ���콺 �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUINPCDialogue::UpdateMouseEvent()
{
	if (ProcessBtns())
		return false;

	if (UpdateSelTextMouseEvent())
		return false;

	// â ���� Ŭ���� ���� UIó�� �� �̵� �Ұ�
	if(CheckMouseIn(m_Pos.x, m_Pos.y, ND_WIDTH, ND_HEIGHT))
		return false;

	return true;
}

//*****************************************************************************
// �Լ� �̸� : ProcessBtns()
// �Լ� ���� : ��ư ������ �̺�Ʈ ó��.
// ��ȯ ��	 : ó�� ������ true.
//*****************************************************************************
bool CNewUINPCDialogue::ProcessBtns()
{
	if (m_btnClose.UpdateMouseEvent())
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPC_DIALOGUE);
		return true;
	}
	else if (SEASON3B::IsPress(VK_LBUTTON) && CheckMouseIn(m_Pos.x+169, m_Pos.y+7, 13, 12))
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPC_DIALOGUE);
		return true;
	}
	else if (m_btnProgressR.UpdateMouseEvent())
	{
		m_nSelNPCPage = MIN(++m_nSelNPCPage, m_nMaxNPCPage);
		if (m_nSelNPCPage == m_nMaxNPCPage)
		{
			if (NON_SEL_TEXTS_MODE == m_eLowerView)
				m_eLowerView = SEL_TEXTS_MODE;
		}
		
		::PlayBuffer(SOUND_CLICK01);
		
		if (m_nSelNPCPage == m_nMaxNPCPage && NON_SEL_TEXTS_MODE != m_eLowerView)
			m_btnProgressR.Lock();
		if (0 != m_nMaxNPCPage)
			m_btnProgressL.UnLock();
		
		return true;
	}
	else if (m_btnProgressL.UpdateMouseEvent())
	{
		m_nSelNPCPage = MAX(--m_nSelNPCPage, 0);
		::PlayBuffer(SOUND_CLICK01);
		
		if (0 == m_nSelNPCPage)
			m_btnProgressL.Lock();
		m_btnProgressR.UnLock();
		
		return true;
	}
	else if (m_btnSelTextR.UpdateMouseEvent())
	{
		m_nSelSelTextPage = MIN(++m_nSelSelTextPage, m_nMaxSelTextPage);
		::PlayBuffer(SOUND_CLICK01);

		if (m_nSelSelTextPage == m_nMaxSelTextPage)
			m_btnSelTextR.Lock();
		if (0 != m_nMaxSelTextPage)
			m_btnSelTextL.UnLock();
		
		return true;
	}
	else if (m_btnSelTextL.UpdateMouseEvent())
	{
		m_nSelSelTextPage = MAX(--m_nSelSelTextPage, 0);
		::PlayBuffer(SOUND_CLICK01);

		if (0 == m_nSelSelTextPage)
			m_btnSelTextL.Lock();
		m_btnSelTextR.UnLock();
		
		return true;
	}

	return false;
}

//*****************************************************************************
// �Լ� �̸� : UpdateSelTextMouseEvent()
// �Լ� ���� : ���ù� ���콺 �̺�Ʈ ó��.
// ��ȯ ��	 : ó�� ������ true.
//*****************************************************************************
bool CNewUINPCDialogue::UpdateSelTextMouseEvent()
{
	if (SEL_TEXTS_MODE != m_eLowerView || !m_bCanClick)
		return false;

	m_nSelSelText = 0;
	if (MouseX < m_Pos.x+11 || MouseX > m_Pos.x+179)
		return false;

	int i;

	int nStartSelText = 0;	// �˻縦 ������ ���ù�.
	for (i = 0; i < m_nSelSelTextPage; ++i)
		nStartSelText += m_anSelTextCountPerPage[i];

	int nEndSelText = nStartSelText + m_anSelTextCountPerPage[m_nSelSelTextPage];

	int nTopY;
	int nBottomY = m_Pos.y+203;
	for (i = nStartSelText; i < nEndSelText; ++i)
	{
		nTopY = nBottomY;
		nBottomY += m_anSelTextLine[i] * ND_TEXT_GAP;

		if (nTopY <= MouseY && MouseY < nBottomY)
		{
			m_nSelSelText = i + 1;
			if (SEASON3B::IsRelease(VK_LBUTTON))
			{
				m_bCanClick = false;
				ProcessSelTextResult();
				::PlayBuffer(SOUND_CLICK01);
				return true;
			}
			break;
		}
	}

	return false;
}

//*****************************************************************************
// �Լ� �̸� : UpdateKeyEvent()
// �Լ� ���� : Ű���� �Է� ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUINPCDialogue::UpdateKeyEvent()
{
	if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE))
	{
		if (SEASON3B::IsPress(VK_ESCAPE))
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPC_DIALOGUE);
			return false;
		}
	}

	return true;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ��Ÿ �� ������ �Ͼ�� �̺�Ʈ ó��.
// ��ȯ ��	 : true�� â �ڷε� �̺�Ʈ�� ó��.
//*****************************************************************************
bool CNewUINPCDialogue::Update()
{
	return true;
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : â ����.
// ��ȯ ��	 : true�� ����.
//*****************************************************************************
bool CNewUINPCDialogue::Render()
{
	::EnableAlphaTest();

	::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderBackImage();
	RenderSelTextBlock();
	RenderText();
#ifdef ASG_ADD_GENS_SYSTEM
	RenderContributePoint();
#endif	// ASG_ADD_GENS_SYSTEM

	if (!m_btnProgressL.IsLock())
		m_btnProgressL.Render();
	if (!m_btnProgressR.IsLock())
		m_btnProgressR.Render();

	if (!m_btnSelTextL.IsLock())
		m_btnSelTextL.Render();
	if (!m_btnSelTextR.IsLock())
		m_btnSelTextR.Render();

	m_btnClose.Render();

	::DisableAlphaBlend();
	
	return true;
}

//*****************************************************************************
// �Լ� �̸� : RenderBackImage()
// �Լ� ���� : â ���� �̹��� ����.
//*****************************************************************************
void CNewUINPCDialogue::RenderBackImage()
{
	RenderImage(IMAGE_ND_BACK, m_Pos.x, m_Pos.y, float(ND_WIDTH), float(ND_HEIGHT));
	RenderImage(IMAGE_ND_TOP, m_Pos.x, m_Pos.y, float(ND_WIDTH), 64.f);
	RenderImage(IMAGE_ND_LEFT, m_Pos.x, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_ND_RIGHT, m_Pos.x+ND_WIDTH-21, m_Pos.y+64, 21.f, 320.f);
	RenderImage(IMAGE_ND_BOTTOM, m_Pos.x, m_Pos.y+ND_HEIGHT-45, float(ND_WIDTH), 45.f);

	RenderImage(IMAGE_ND_LINE, m_Pos.x+1, m_Pos.y+181, 188.f, 21.f);
}

//*****************************************************************************
// �Լ� �̸� : RenderSelTextBlock()
// �Լ� ���� : ���ù� �� ����.
//*****************************************************************************
void CNewUINPCDialogue::RenderSelTextBlock()
{
	if (SEL_TEXTS_MODE != m_eLowerView)
		return;

	if (0 == m_nSelSelText)
		return;

	int i;

	int nStartSelText = 0;	// �˻縦 ������ ���ù�.
	for (i = 0; i < m_nSelSelTextPage; ++i)
		nStartSelText += m_anSelTextCountPerPage[i];	

	int nBlockPosY = m_Pos.y+203;

	for (i = nStartSelText; i < m_nSelSelText - 1; ++i)
		nBlockPosY += ND_TEXT_GAP * m_anSelTextLine[i];

	::glColor4f(0.5f, 0.7f, 0.3f, 0.5f);
	::RenderColor(m_Pos.x+11, nBlockPosY, 168.f, ND_TEXT_GAP * m_anSelTextLine[m_nSelSelText - 1]);
	::EndRenderColor();
}

//*****************************************************************************
// �Լ� �̸� : RenderText()
// �Լ� ���� : �ؽ�Ʈ ����.
//*****************************************************************************
void CNewUINPCDialogue::RenderText()
{
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetBgColor(0);

// NPC �̸�.
	g_pRenderText->SetTextColor(150, 255, 240, 255);
	g_pRenderText->RenderText(m_Pos.x, m_Pos.y+12, g_QuestMng.GetNPCName(),
		ND_WIDTH, 0, RT3_SORT_CENTER);

	g_pRenderText->SetFont(g_hFont);
// NPC ���.
	g_pRenderText->SetTextColor(255, 230, 210, 255);
	int i;
	for (i = 0; i < ND_NPC_MAX_LINE_PER_PAGE; ++i)
		g_pRenderText->RenderText(m_Pos.x+13, m_Pos.y+59+(ND_TEXT_GAP*i),
			m_aszNPCWords[i + ND_NPC_MAX_LINE_PER_PAGE * m_nSelNPCPage],
			0, 0, RT3_SORT_LEFT);

// �÷��̾� ���.
	if (SEL_TEXTS_MODE == m_eLowerView)
	{
		g_pRenderText->SetTextColor(255, 230, 210, 255);
		
		int nStartSelTextLine = 0;	// �˻縦 ������ ���ù�.
		for (i = 0; i < m_nSelSelTextPage; ++i)
			nStartSelTextLine += m_anSelTextLinePerPage[i];

		for (i = 0; i < m_anSelTextLinePerPage[m_nSelSelTextPage]; ++i)
			g_pRenderText->RenderText(m_Pos.x+13, m_Pos.y+207+(ND_TEXT_GAP*i),
				m_aszSelTexts[nStartSelTextLine+i], 0, 0, RT3_SORT_LEFT);
	}
}

#ifdef ASG_ADD_GENS_SYSTEM
//*****************************************************************************
// �Լ� �̸� : RenderText()
// �Լ� ���� : �⿩�� ����.
//*****************************************************************************
void CNewUINPCDialogue::RenderContributePoint()
{
	// �ڽŰ� ���� ������ �ս� NPC�� ��쿡��.
	if ((543 == g_QuestMng.GetNPCIndex() && 1 == Hero->m_byGensInfluence)
		|| (544 == g_QuestMng.GetNPCIndex() && 2 == Hero->m_byGensInfluence))
	{
		RenderImage(IMAGE_ND_CONTRIBUTE_BG, m_Pos.x+11, m_Pos.y+27, 168.f, 18.f);

		char szContribute[32];
		::sprintf(szContribute, GlobalText[2986], m_dwContributePoint);	// 2986 "ȹ��⿩��:%u"
		g_pRenderText->SetTextColor(255, 230, 210, 255);
		g_pRenderText->RenderText(m_Pos.x, m_Pos.y+30, szContribute, ND_WIDTH, 0, RT3_SORT_CENTER);
	}
}
#endif	// ASG_ADD_GENS_SYSTEM

bool CNewUINPCDialogue::IsVisible() const
{ return CNewUIObj::IsVisible(); }

//*****************************************************************************
// �Լ� �̸� : GetLayerDepth()
// �Լ� ���� : â�� ���̾�� ����.
//*****************************************************************************
float CNewUINPCDialogue::GetLayerDepth()
{
	return 3.1f;
}

//*****************************************************************************
// �Լ� �̸� : LoadImages()
// �Լ� ���� : �̹��� ���ҽ� �ε�.
//*****************************************************************************
void CNewUINPCDialogue::LoadImages()
{
	LoadBitmap("Interface\\newui_msgbox_back.jpg", IMAGE_ND_BACK, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back04.tga", IMAGE_ND_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-L.tga", IMAGE_ND_LEFT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back02-R.tga", IMAGE_ND_RIGHT, GL_LINEAR);
	LoadBitmap("Interface\\newui_item_back03.tga", IMAGE_ND_BOTTOM, GL_LINEAR);

	LoadBitmap("Interface\\newui_myquest_Line.tga", IMAGE_ND_LINE, GL_LINEAR);
	LoadBitmap("Interface\\Quest_bt_L.tga", IMAGE_ND_BTN_L, GL_LINEAR);
	LoadBitmap("Interface\\Quest_bt_R.tga", IMAGE_ND_BTN_R, GL_LINEAR);
	LoadBitmap("Interface\\newui_exit_00.tga", IMAGE_ND_BTN_CLOSE, GL_LINEAR);
#ifdef ASG_ADD_GENS_SYSTEM
	LoadBitmap("Interface\\Gens_point.tga", IMAGE_ND_CONTRIBUTE_BG, GL_LINEAR);
#endif	// ASG_ADD_GENS_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : UnloadImages()
// �Լ� ���� : �̹��� ���ҽ� ����.
//*****************************************************************************
void CNewUINPCDialogue::UnloadImages()
{
#ifdef ASG_ADD_GENS_SYSTEM
	DeleteBitmap(IMAGE_ND_CONTRIBUTE_BG);
#endif	// ASG_ADD_GENS_SYSTEM
	DeleteBitmap(IMAGE_ND_BTN_CLOSE);
	DeleteBitmap(IMAGE_ND_BTN_R);
	DeleteBitmap(IMAGE_ND_BTN_L);
	DeleteBitmap(IMAGE_ND_LINE);

	DeleteBitmap(IMAGE_ND_BOTTOM);
	DeleteBitmap(IMAGE_ND_RIGHT);
	DeleteBitmap(IMAGE_ND_LEFT);
	DeleteBitmap(IMAGE_ND_TOP);
	DeleteBitmap(IMAGE_ND_BACK);
}

//*****************************************************************************
// �Լ� �̸� : ProcessOpening()
// �Լ� ���� : â�� �� �� ó��.
//*****************************************************************************
void CNewUINPCDialogue::ProcessOpening()
{
	m_bQuestListMode = false;
	SetContents(0);
	::PlayBuffer(SOUND_INTERFACE01);
}

//*****************************************************************************
// �Լ� �̸� : ProcessClosing()
// �Լ� ���� : â�� ���� �� ó��.
// ��ȯ ��	 : true �� �ݱ� ����.
//*****************************************************************************
bool CNewUINPCDialogue::ProcessClosing()
{
	m_dwCurDlgIndex = 0;
	m_dwContributePoint = 0;
	m_bQuestListMode = false;
	SendExitInventory();
	::PlayBuffer(SOUND_CLICK01);
	return true;
}

//*****************************************************************************
// �Լ� �̸� : SetContents()
// �Ű� ���� : dwDlgIndex	: ��ȭ �ε���
// �Լ� ���� : â�� ���� ����.(����Ʈ ����Ʈ�� ��� ����.)
//*****************************************************************************
void CNewUINPCDialogue::SetContents(DWORD dwDlgIndex)
{
	m_dwCurDlgIndex = dwDlgIndex;
	SetCurNPCWords();
	SetCurSelTexts();
	m_bCanClick = true;
	m_btnProgressL.Lock();
	m_btnSelTextL.Lock();
	m_nSelSelText = 0;
}

//*****************************************************************************
// �Լ� �̸� : SetCurNPCWords()
// �Լ� ���� : ���� ��ȭ �ε����� NPC ��� ����.
// �Ű� ���� : nQuestListCount	: ����Ʈ ����Ʈ ����.(�⺻�� 0)
//*****************************************************************************
void CNewUINPCDialogue::SetCurNPCWords(int nQuestListCount)
{
	::memset(m_aszNPCWords[0], 0, sizeof(char) * ND_NPC_LINE_MAX * ND_WORDS_ROW_MAX);

	g_pRenderText->SetFont(g_hFont);	// DivideStringByPixel()�Լ� ���� ��Ʈ�� �������־�� ��.
	const char* pszSrc;
	if (m_bQuestListMode)	// ����Ʈ ����Ʈ ����ΰ�?
		// ����Ʈ�� ���� �� ���� ���� �� ��� ����.(QuestWords.txt�� 1501,1502��)
		pszSrc = 0 < nQuestListCount ? g_QuestMng.GetWords(1501) : g_QuestMng.GetWords(1502);
	else
		pszSrc = g_QuestMng.GetNPCDlgNPCWords(m_dwCurDlgIndex);

	int nLine = ::DivideStringByPixel(&m_aszNPCWords[0][0], ND_NPC_LINE_MAX, ND_WORDS_ROW_MAX,
		pszSrc, 160);

	if (1 > nLine)
		return;

	m_nMaxNPCPage = (nLine - 1) / ND_NPC_MAX_LINE_PER_PAGE;
	if (1 <= m_nMaxNPCPage)
	{
	// NPC ��簡 2������ �̻��̸� ���ù��� ǥ�� ���ϰ�, ���� ���� ��ư�� ��Ÿ���� ��.
		m_eLowerView = NON_SEL_TEXTS_MODE;
		m_btnProgressR.UnLock();
	}
	else
	{
		m_eLowerView = SEL_TEXTS_MODE;
		m_btnProgressR.Lock();
	}

	m_nSelNPCPage = 0;
}

//*****************************************************************************
// �Լ� �̸� : SetCurSelTexts()
// �Լ� ���� : ���� ��ȭ �ε����� ���ù� ����.
//*****************************************************************************
void CNewUINPCDialogue::SetCurSelTexts()
{
	::memset(m_aszSelTexts[0], 0, sizeof(char) * ND_SEL_TEXT_LINE_MAX * ND_WORDS_ROW_MAX);
	::memset(m_anSelTextLine, 0, sizeof(int) * (ND_QUEST_INDEX_MAX_COUNT+1));

	g_pRenderText->SetFont(g_hFont);	// DivideStringByPixel()�Լ� ���� ��Ʈ�� �������־�� ��.

	char szAnswer[2 * ND_WORDS_ROW_MAX];
	const char* pszAnswer;
	int nSelTextLineSum = 0;	// ���ù� �� �հ�.
	int i;
	for (i = 0; i < QM_MAX_ND_ANSWER; ++i)		
	{
	// ���ù� �տ� ��ȣ ���̱�.
		::sprintf(szAnswer, "%d. ", i + 1);
		pszAnswer = g_QuestMng.GetNPCDlgAnswer(m_dwCurDlgIndex, i);
		if (NULL == pszAnswer)
			break;
		::strcat(szAnswer, pszAnswer);

	// �� ������. ���ù� 1���� �ִ� 2����.
		m_anSelTextLine[i] = ::DivideStringByPixel(&m_aszSelTexts[nSelTextLineSum][0],
			2, ND_WORDS_ROW_MAX, szAnswer, 160, false);

		nSelTextLineSum += m_anSelTextLine[i];

		if (ND_SEL_TEXT_LINE_MAX <= nSelTextLineSum)
			break;
	}

	m_nSelTextCount = i;

	CalculateSelTextMaxPage(i);
}

//*****************************************************************************
// �Լ� �̸� : CalculateSelTextMaxPage()
// �Լ� ���� : ���ù� �ִ� ������ ���ϱ�.
// �Ű� ���� : nSelTextCount	: ���ù� ����.
//*****************************************************************************
void CNewUINPCDialogue::CalculateSelTextMaxPage(int nSelTextCount)
{
	m_nSelSelTextPage = 0;
	m_nMaxSelTextPage = 0;
	::memset(m_anSelTextLinePerPage, 0, sizeof(int)*ND_SEL_TEXT_PAGE_LIMIT);
	::memset(m_anSelTextCountPerPage, 0, sizeof(int)*ND_SEL_TEXT_PAGE_LIMIT);
	
	int i;
	for (i = 0; i < nSelTextCount; ++i)
	{
		++m_anSelTextCountPerPage[m_nMaxSelTextPage];
		m_anSelTextLinePerPage[m_nMaxSelTextPage] += m_anSelTextLine[i];

		// �������� ���� �� ���� �Ѿ��.
		if (m_anSelTextLinePerPage[m_nMaxSelTextPage] > ND_SEL_TEXT_MAX_LINE_PER_PAGE)
		{
			// ���� �������� ���� �� ���� ���� �������� �����.
			--m_anSelTextCountPerPage[m_nMaxSelTextPage];
			m_anSelTextLinePerPage[m_nMaxSelTextPage] -= m_anSelTextLine[i];
			if (ND_SEL_TEXT_PAGE_LIMIT == ++m_nMaxSelTextPage)
				break;
			++m_anSelTextCountPerPage[m_nMaxSelTextPage];
			m_anSelTextLinePerPage[m_nMaxSelTextPage] += m_anSelTextLine[i];
		}
	}
	
	if (1 <= m_nMaxSelTextPage)	// 2������ �̻��̸�.
		m_btnSelTextR.UnLock();	// ���� ���� ��ư�� ��Ÿ���� ��.
	else
		m_btnSelTextR.Lock();
}

//*****************************************************************************
// �Լ� �̸� : SetQuestListText()
// �Լ� ���� : ����Ʈ ����Ʈ ����.
// �Ű� ���� : adwSrcQuestIndex	: ���� ����Ʈ �ε��� �迭 �ּ�.
//			   nIndexCount		: ���� ����Ʈ �ε��� ����.
//*****************************************************************************
void CNewUINPCDialogue::SetQuestListText(DWORD* adwSrcQuestIndex, int nIndexCount)
{
	_ASSERT(0 <= nIndexCount && nIndexCount <= ND_QUEST_INDEX_MAX_COUNT);

	::memset(m_adwQuestIndex, 0, sizeof(DWORD)*ND_QUEST_INDEX_MAX_COUNT);
	::memcpy(m_adwQuestIndex, adwSrcQuestIndex, sizeof(DWORD) * nIndexCount);

	m_nSelTextCount = nIndexCount + 1;	// "���ư���" ���ù� �߰��� ���� +1

	::memset(m_aszSelTexts[0], 0, sizeof(char) * ND_SEL_TEXT_LINE_MAX * ND_WORDS_ROW_MAX);
	::memset(m_anSelTextLine, 0, sizeof(int) * (ND_QUEST_INDEX_MAX_COUNT+1));

	char szSelText[2 * ND_WORDS_ROW_MAX];
	const char* pszSelText;
	int nSelTextRow = 0;
	g_pRenderText->SetFont(g_hFont);	// DivideStringByPixel()�Լ� ���� ��Ʈ�� �������־�� ��.
	int i;
	for (i = 0; i < m_nSelTextCount; ++i)
	{
		// ���ù� �տ� ��ȣ ���̱�(����Ʈ��� '[Q]'�� ����).
		if (m_nSelTextCount - 1 == i)
		{
			// QuestWords.txt�� 1007�� "���ư���"�� ������ ���ο� �߰�.
			::sprintf(szSelText, "%d. ", i + 1);
			pszSelText = g_QuestMng.GetWords(1007);
		}
		else
		{
			::sprintf(szSelText, "%d. [Q]", i + 1);	// ����Ʈ ���� �׸�.
			pszSelText = g_QuestMng.GetSubject(m_adwQuestIndex[i]);
		}

		if (NULL == pszSelText)
			break;
		::strcat(szSelText, pszSelText);

	// �� ������. ���ù� 1���� �ִ� 2����.
		m_anSelTextLine[i] = ::DivideStringByPixel(&m_aszSelTexts[nSelTextRow][0],
			2, ND_WORDS_ROW_MAX, szSelText, 160, false);
		
		nSelTextRow += m_anSelTextLine[i];
		
		if (ND_SEL_TEXT_LINE_MAX < nSelTextRow)
			break;
	}

	CalculateSelTextMaxPage(i);
}

//*****************************************************************************
// �Լ� �̸� : SetContributePoint()
// �Լ� ���� : �⿩�� ����.
// �Ű� ���� : dwContributePoint	: �⿩��.
//*****************************************************************************
void CNewUINPCDialogue::SetContributePoint(DWORD dwContributePoint)
{
	// �ս� NPC�� ��츸.
	if (543 == g_QuestMng.GetNPCIndex() || 544 == g_QuestMng.GetNPCIndex())
		m_dwContributePoint = dwContributePoint;
}

//*****************************************************************************
// �Լ� �̸� : ProcessSelTextResult()
// �Լ� ���� : ���ù� ����� ó��.
//*****************************************************************************
void CNewUINPCDialogue::ProcessSelTextResult()
{
	if (m_bQuestListMode)	// ����Ʈ ����Ʈ ����ΰ�?
	{
		if (m_nSelSelText == m_nSelTextCount)	// ���ư��⸦ ���� �ߴٸ�.
		{
			m_bQuestListMode = false;
			SetContents(0);
		}
		else
			SendQuestSelection(m_adwQuestIndex[m_nSelSelText - 1], (BYTE)m_nSelSelText);
	}
	else
	{
		int nAnswerResult = g_QuestMng.GetNPCDlgAnswerResult(m_dwCurDlgIndex, m_nSelSelText-1);
		if (900 >= nAnswerResult)
		{
			SetContents(nAnswerResult);
		}
		else
		{
			switch (nAnswerResult)
			{
			case 901:	// ����Ʈ
				SendRequestQuestByNPCEPList();
				break;

			case 902:	// �����
				SendRequestAPDPUp();
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_NPC_DIALOGUE);
				break;

#ifdef ASG_ADD_GENS_SYSTEM
			case 903:	// �ս� ����(��������)
				SendRequestGensJoining(1);
				break;

			case 904:	// �ս� ����(�ٳ׸�Ʈ)
				SendRequestGensJoining(2);
				break;

			case 905:	// �ս� Ż��
				SendRequestGensSecession();
				break;
#endif	// ASG_ADD_GENS_SYSTEM
#ifdef PBG_ADD_GENSRANKING
			case 906:	// ���� �ޱ�(��������)
				SendRequestGensReward(1);
				break;
			case 907:	// ���� �ޱ�(�ٳ׸�Ʈ)
				SendRequestGensReward(2);
				break;
#endif //PBG_ADD_GENSRANKING

			default:	// "NPC ��ȭ ��ũ��Ʈ ����� ����."
				SetContents(999);
			}
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : ProcessQuestListReceive()
// �Լ� ���� : ����Ʈ ����Ʈ �䱸 ���� ���� ó��.
// �Ű� ���� : adwSrcQuestIndex	: ���� ����Ʈ �ε��� �迭 �ּ�.
//			   nIndexCount		: ���� ����Ʈ �ε��� ����.
//*****************************************************************************
void CNewUINPCDialogue::ProcessQuestListReceive(DWORD* adwSrcQuestIndex, int nIndexCount)
{
	m_bQuestListMode = true;
	SetCurNPCWords(nIndexCount);
	SetQuestListText(adwSrcQuestIndex, nIndexCount);
	m_bCanClick = true;
	m_btnProgressL.Lock();
	m_btnSelTextL.Lock();
	m_nSelSelText = 0;
}

#ifdef ASG_ADD_GENS_SYSTEM
// �ս� ���� ���� �ڵ�.
enum GENS_JOINING_ERR_CODE
{	
	GJEC_NONE_ERR = 0,					// ���� ����.
	GJEC_REG_GENS_ERR,					// �̹� ���� �Ǿ� �ִ�
	GJEC_GENS_SECEDE_DAY_ERR,			// �ս����� Ż������ �������� �ȵƴ�.
	GJEC_REG_GENS_LV_ERR,				// ���� 50 �̸��̴�.
	GJEC_REG_GENS_NOT_EQL_GUILDMA_ERR,	// ������ ���� �ս��� �ƴϴ�.
	GJEC_NONE_REG_GENS_GUILDMA_ERR,		// ������� �ս��� ������ �ȵǾ� �ִ�.
	GJEC_PARTY,							// ��Ƽ�� �ΰ� ������ ���� �Ұ�.
#ifdef ASG_FIX_GENS_JOINING_ERR_CODE_ADD
	GJEC_GUILD_UNION_MASTER				// ���ձ�����̸� ���� �Ұ�.
#endif	// ASG_FIX_GENS_JOINING_ERR_CODE_ADD
};

//*****************************************************************************
// �Լ� �̸� : ProcessGensJoiningReceive()
// �Լ� ���� : �ս� ���� ���� ���� ó��.
// �Ű� ���� : byResult		: �ս� ���� ���� �ڵ�(GENS_JOINING_ERR_CODE).
//			   byInfluence	: �ս� ����.(0:����, 1:��������, 2:�ٳ׸�Ʈ)
//*****************************************************************************
void CNewUINPCDialogue::ProcessGensJoiningReceive(BYTE byResult, BYTE byInfluence)
{
	switch (byResult)
	{
	case GJEC_NONE_ERR:
		Hero->m_byGensInfluence = byInfluence;
		SetContents(5);
		break;
	case GJEC_REG_GENS_ERR:
		SetContents(9);
		break;
	case GJEC_GENS_SECEDE_DAY_ERR:
		SetContents(11);
		break;
	case GJEC_REG_GENS_LV_ERR:
		SetContents(8);
		break;
	case GJEC_REG_GENS_NOT_EQL_GUILDMA_ERR:
		SetContents(10);
		break;
	case GJEC_NONE_REG_GENS_GUILDMA_ERR:
		SetContents(12);
		break;
	case GJEC_PARTY:
		SetContents(18);
		break;
#ifdef ASG_FIX_GENS_JOINING_ERR_CODE_ADD
	case GJEC_GUILD_UNION_MASTER:
		SetContents(19);
		break;
#endif	// ASG_FIX_GENS_JOINING_ERR_CODE_ADD
	}
}

// �ս� Ż�� ���� �ڵ�.
enum GENS_SECEDE_ERR_CODE
{	
	GSEC_NONE_ERR = 0,					// ����Ż��
	GSEC_IS_NOT_REG_GENS,				// ���� �Ǿ� ���� �ʴ�.
	GSEC_GUILD_MASTER_CAN_NOT_SECEDE,	// ������� �Ұ�.
	GSEC_IS_NOT_INFLUENCE_NPC			// ���� ���� NPC�� �ƴ�.
};

#ifdef PBG_ADD_GENSRANKING
//�ս� ���� ���� �ڵ�
enum GENS_REWARD_ERR_CODE
{
	GENS_REWARD_CALL = 0,				// �����
	GENS_REWARD_TERM,					// ���� �Ⱓ�ƴ�
	GENS_REWARD_TARGET,					// ���� ����ھƴ�
	GENS_REWARD_SPACE,					// ���� ��������
	GENS_REWARD_ALREADY,				// �̹����޹޾Ҵ�
	GENS_REWARD_DIFFERENT,				// �ٸ��ս�
	GENS_REWARD_NOT_REG,				// �ս��� ���ԵǾ����� �ʴ�
};
#endif //PBG_ADD_GENSRANKING

//*****************************************************************************
// �Լ� �̸� : ProcessGensSecessionReceive()
// �Լ� ���� : �ս� Ż�� ���� ���� ó��.
// �Ű� ���� : byResult	: �ս� Ż�� ���� �ڵ�(GENS_SECEDE_ERR_CODE).
//*****************************************************************************
void CNewUINPCDialogue::ProcessGensSecessionReceive(BYTE byResult)
{
	switch (byResult)
	{
	case GSEC_NONE_ERR:
		Hero->m_byGensInfluence = 0;
		SetContents(16);
		break;
	case GSEC_IS_NOT_REG_GENS:
		SetContents(15);
		break;
	case GSEC_GUILD_MASTER_CAN_NOT_SECEDE:
		SetContents(14);
		break;
	case GSEC_IS_NOT_INFLUENCE_NPC:
		SetContents(17);
		break;
	}
}
#endif	// ASG_ADD_GENS_SYSTEM

#ifdef PBG_ADD_GENSRANKING
// ������� ���� �ڵ�
void CNewUINPCDialogue::ProcessGensRewardReceive(BYTE byResult)
{
	switch(byResult)
	{
	case GENS_REWARD_CALL:
		SetContents(20);
		break;
	case GENS_REWARD_TERM:
		SetContents(21);
		break;
	case GENS_REWARD_TARGET:
		SetContents(22);
		break;
	case GENS_REWARD_SPACE:
		SetContents(23);
		break;
	case GENS_REWARD_ALREADY:
		SetContents(24);
		break;
	case GENS_REWARD_DIFFERENT:
		SetContents(17);
		break;
	case GENS_REWARD_NOT_REG:
#ifdef PBG_FIX_GENSREWARDNOTREG
		SetContents(25);
#else //PBG_FIX_GENSREWARDNOTREG
		SetContents(15);
#endif //PBG_FIX_GENSREWARDNOTREG
		break;
	}
}
#endif //PBG_ADD_GENSRANKING
#endif	// ASG_ADD_UI_NPC_DIALOGUE