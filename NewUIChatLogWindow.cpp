
#include "stdafx.h"

#include "NewUIChatLogWindow.h"
#include "NewUIManager.h"
#include "NewUISystem.h"
#include "DSPlaySound.h"
#include "UIControls.h"
#include "ZzzInterface.h"

using namespace SEASON3B;

SEASON3B::CNewUIChatLogWindow::CNewUIChatLogWindow() 
{ 
	Init(); 
}

SEASON3B::CNewUIChatLogWindow::~CNewUIChatLogWindow() 
{ 
	Release(); 
}

void SEASON3B::CNewUIChatLogWindow::Init()
{
	m_pNewUIMng = NULL;
	m_WndPos.x = m_WndPos.y = 0;
	m_ScrollBtnPos.x = m_ScrollBtnPos.y = 0;
	m_WndSize.cx = WND_WIDTH; m_WndSize.cy = 0;
	m_nShowingLines = 6;
	m_iCurrentRenderEndLine = -1;
	m_fBackAlpha = 0.6f;

	m_EventState = EVENT_NONE;

	m_bShowFrame = false;

#ifdef KJH_FIX_UI_CHAT_MESSAGE
	m_CurrentRenderMsgType = TYPE_ALL_MESSAGE;
	m_bShowChatLog = true;
#else // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
	m_ShowMessageFlag = SHOW_ALL_MESSAGES;
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

	m_bPointedMessage = false;
	m_iPointedMessageIndex = 0;
}

void SEASON3B::CNewUIChatLogWindow::LoadImages()
{
	LoadBitmap("Interface\\newui_scrollbar_up.tga", IMAGE_SCROLL_TOP, GL_LINEAR);
	LoadBitmap("Interface\\newui_scrollbar_m.tga", IMAGE_SCROLL_MIDDLE, GL_LINEAR);
	LoadBitmap("Interface\\newui_scrollbar_down.tga", IMAGE_SCROLL_BOTTOM, GL_LINEAR);
	LoadBitmap("Interface\\newui_scroll_on.tga", IMAGE_SCROLLBAR_ON, GL_LINEAR);
	LoadBitmap("Interface\\newui_scroll_off.tga", IMAGE_SCROLLBAR_OFF, GL_LINEAR);
	LoadBitmap("Interface\\newui_scrollbar_stretch.jpg", IMAGE_DRAG_BTN, GL_LINEAR);
}

void SEASON3B::CNewUIChatLogWindow::UnloadImages()
{
	DeleteBitmap(IMAGE_SCROLL_TOP);
	DeleteBitmap(IMAGE_SCROLL_MIDDLE);
	DeleteBitmap(IMAGE_SCROLL_BOTTOM);
	DeleteBitmap(IMAGE_SCROLLBAR_ON);
	DeleteBitmap(IMAGE_SCROLLBAR_OFF);
	DeleteBitmap(IMAGE_DRAG_BTN);
}

bool SEASON3B::CNewUIChatLogWindow::RenderBackground()
{
	//. ���� �׸���
	if(m_bShowFrame)
	{
		float fRenderPosX = m_WndPos.x, fRenderPosY = m_WndPos.y - m_WndSize.cy;
		
		EnableAlphaTest();
		glColor4f(0.0f, 0.0f, 0.0f, GetBackAlpha());
		RenderColor (fRenderPosX, fRenderPosY, (float)m_WndSize.cx, (float)m_WndSize.cy);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		DisableAlphaBlend();
	}
	return true;
}

#ifdef KJH_FIX_UI_CHAT_MESSAGE
bool SEASON3B::CNewUIChatLogWindow::RenderMessages()
{
	float fRenderPosX = m_WndPos.x, fRenderPosY = m_WndPos.y - m_WndSize.cy + SCROLL_TOP_BOTTOM_PART_HEIGHT;

	// ���� �޼����� �����´�.
	type_vector_msgs* pvecMsgs = GetMsgs( GetCurrentMsgType() );

	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return false;
	}

	//. �޼��� �׸���
	int iRenderStartLine = 0;
	if(GetCurrentRenderEndLine() >= m_nShowingLines)
	{
		iRenderStartLine = GetCurrentRenderEndLine() - m_nShowingLines + 1;
	}
	else
	{
		fRenderPosY = fRenderPosY+FONT_LEADING+(SCROLL_MIDDLE_PART_HEIGHT*(m_nShowingLines-GetCurrentRenderEndLine()-1));
	}
	
	BYTE byAlpha = 150;
	if(m_bShowFrame) byAlpha = 100;

	EnableAlphaTest();
	for(int i=iRenderStartLine, s=0; i<=GetCurrentRenderEndLine(); i++, s++)
	{
#ifdef _VS2008PORTING
		if(i < 0 && i >= (int)pvecMsgs->size()) break;
#else // _VS2008PORTING
		if(i < 0 && i >= pvecMsgs->size()) break;
#endif // _VS2008PORTING
		
		bool bRenderMessage = true;	
		g_pRenderText->SetFont(g_hFont);

		CMessageText* pMsgText = (*pvecMsgs)[i];

		if( pMsgText->GetType() == TYPE_WHISPER_MESSAGE )		//�Ӹ�
		{
			g_pRenderText->SetBgColor(255, 200, 50, 150);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_SYSTEM_MESSAGE )		//�޼���
		{
			g_pRenderText->SetBgColor(0, 0, 0, 150);
			g_pRenderText->SetTextColor(100, 150, 255, 255);
		}
		else if( pMsgText->GetType() == TYPE_ERROR_MESSAGE )		//����
		{
			g_pRenderText->SetBgColor(0, 0, 0, 150);
			g_pRenderText->SetTextColor(255, 30, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_CHAT_MESSAGE )			//ä��
		{
			g_pRenderText->SetBgColor(0, 0, 0, byAlpha);
			g_pRenderText->SetTextColor(205, 220, 239, 255);
		}
		else if( pMsgText->GetType() == TYPE_PARTY_MESSAGE )		//��Ƽ ä��
		{
			g_pRenderText->SetBgColor(0, 200, 255, 150);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GUILD_MESSAGE )		//��� ä��
		{
			g_pRenderText->SetBgColor(0, 255, 150, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GUILD_MESSAGE )		//��� ä��
		{
			g_pRenderText->SetBgColor(0, 255, 150, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_UNION_MESSAGE  )		//���� ä��
		{
			g_pRenderText->SetBgColor(200, 200, 0, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GM_MESSAGE )		//+ �˹�: GM���� ����
		{
			g_pRenderText->SetBgColor(30, 30, 30, 200);
			g_pRenderText->SetTextColor(250, 200, 50, 255);
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			bRenderMessage = false;
		}


		if(bRenderMessage && !pMsgText->GetText().empty())
		{
			POINT ptRenderPos = { fRenderPosX+WND_LEFT_RIGHT_EDGE, 
				fRenderPosY+FONT_LEADING+(SCROLL_MIDDLE_PART_HEIGHT*s) };
			if(!pMsgText->GetID().empty())
			{
				if(m_bPointedMessage == true && m_iPointedMessageIndex == i)
				{
					g_pRenderText->SetBgColor(30, 30, 30, 180);
					g_pRenderText->SetTextColor(255, 128, 255, 255);
				}
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				string strIDUTF8 = "";
				g_pMultiLanguage->ConvertANSIToUTF8OrViceVersa(strIDUTF8, (pMsgText->GetID()).c_str());
				type_string strLine = strIDUTF8 + " : " + pMsgText->GetText();
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				type_string strLine = pMsgText->GetID() + " : " + pMsgText->GetText();
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				g_pRenderText->RenderText(ptRenderPos.x, ptRenderPos.y, strLine.c_str());
			}
			else
			{
				g_pRenderText->RenderText(ptRenderPos.x, ptRenderPos.y, pMsgText->GetText().c_str());
			}
		}
	}
	DisableAlphaBlend();

	return true;
}

#else // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
bool SEASON3B::CNewUIChatLogWindow::RenderMessages()
{
	float fRenderPosX = m_WndPos.x, fRenderPosY = m_WndPos.y - m_WndSize.cy + SCROLL_TOP_BOTTOM_PART_HEIGHT;

	//. �޼��� �׸���
	int iRenderStartLine = 0;
	if(GetCurrentRenderEndLine() >= m_nShowingLines)
		iRenderStartLine = GetCurrentRenderEndLine() - m_nShowingLines + 1;
	
	BYTE byAlpha = 150;
	if(m_bShowFrame) byAlpha = 100;

	EnableAlphaTest();
	for(int i=iRenderStartLine, s=0; i<=GetCurrentRenderEndLine(); i++, s++)
	{					
		if(i < 0 && i >= m_vecMsgs.size()) break;
		
		bool bRenderMessage = true;	
		g_pRenderText->SetFont(g_hFont);

		CMessageText* pMsgText = m_vecMsgs[i];

		if( pMsgText->GetType() == TYPE_WHISPER_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_WHISPER_MESSAGE)) )		//�Ӹ�
		{
			g_pRenderText->SetBgColor(255, 200, 50, 150);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_SYSTEM_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_SYSTEM_MESSAGE)) )		//�޼���
		{
			g_pRenderText->SetBgColor(0, 0, 0, 150);
			g_pRenderText->SetTextColor(100, 150, 255, 255);
		}
		else if( pMsgText->GetType() == TYPE_ERROR_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_ERROR_MESSAGE)) )		//����
		{
			g_pRenderText->SetBgColor(0, 0, 0, 150);
			g_pRenderText->SetTextColor(255, 30, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_CHAT_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_CHAT_MESSAGE)) )			//ä��
		{
			g_pRenderText->SetBgColor(0, 0, 0, byAlpha);
			g_pRenderText->SetTextColor(205, 220, 239, 255);
		}
		else if( pMsgText->GetType() == TYPE_PARTY_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_PARTY_MESSAGE)) )		//��Ƽ ä��
		{
			g_pRenderText->SetBgColor(0, 200, 255, 150);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GUILD_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_GUILD_MESSAGE)) )		//��� ä��
		{
			g_pRenderText->SetBgColor(0, 255, 150, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GUILD_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_GUILD_MESSAGE)) )		//��� ä��
		{
			g_pRenderText->SetBgColor(0, 255, 150, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_UNION_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_UNION_MESSAGE)) )		//���� ä��
		{
			g_pRenderText->SetBgColor(200, 200, 0, 200);
			g_pRenderText->SetTextColor(0, 0, 0, 255);
		}
		else if( pMsgText->GetType() == TYPE_GM_MESSAGE 
			&& (bRenderMessage = CheckMessageShowFlag(SHOW_GM_MESSAGE)) )		//+ �˹�: GM���� ����
		{
			g_pRenderText->SetBgColor(30, 30, 30, 200);
			g_pRenderText->SetTextColor(250, 200, 50, 255);
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			bRenderMessage = false;
		}
		if(bRenderMessage && !pMsgText->GetText().empty())
		{
			POINT ptRenderPos = { fRenderPosX+WND_LEFT_RIGHT_EDGE, 
				fRenderPosY+FONT_LEADING+(SCROLL_MIDDLE_PART_HEIGHT*s) };
			if(!pMsgText->GetID().empty())
			{
				if(m_bPointedMessage == true && m_iPointedMessageIndex == i)
				{
					g_pRenderText->SetBgColor(30, 30, 30, 180);
					g_pRenderText->SetTextColor(255, 128, 255, 255);
				}
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				string strIDUTF8 = "";
				g_pMultiLanguage->ConvertANSIToUTF8OrViceVersa(strIDUTF8, (pMsgText->GetID()).c_str());
				type_string strLine = strIDUTF8 + " : " + pMsgText->GetText();
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				type_string strLine = pMsgText->GetID() + " : " + pMsgText->GetText();
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				g_pRenderText->RenderText(ptRenderPos.x, ptRenderPos.y, strLine.c_str());
			}
			else
			{
				g_pRenderText->RenderText(ptRenderPos.x, ptRenderPos.y, pMsgText->GetText().c_str());
			}
		}
	}
	DisableAlphaBlend();

	return true;
}

//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�

bool SEASON3B::CNewUIChatLogWindow::RenderFrame()
{
	//. ������ �׸���
	if(m_bShowFrame)
	{
		float fRenderPosX = m_WndPos.x, fRenderPosY = m_WndPos.y - m_WndSize.cy;

		//. ������ ���� ��ư
		EnableAlphaTest();
		if(m_EventState == EVENT_RESIZING_BTN_DOWN)
		{
			glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
		}
		else
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		RenderImage(IMAGE_DRAG_BTN, fRenderPosX, fRenderPosY-(float)RESIZING_BTN_HEIGHT, 254.0f, 10.0f);	// ����������
		DisableAlphaBlend();
		
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//. ��ũ�ѹ� Ʋ
		RenderImage(IMAGE_SCROLL_TOP, fRenderPosX+m_WndSize.cx-SCROLL_BAR_WIDTH-WND_LEFT_RIGHT_EDGE, 
			fRenderPosY+WND_TOP_BOTTOM_EDGE, 7, 3);
		
#ifdef _VS2008PORTING
		for(int i=0; i<(int)GetNumberOfShowingLines(); i++)
#else // _VS2008PORTING
		for(int i=0; i<GetNumberOfShowingLines(); i++)
#endif // _VS2008PORTING
		{
			RenderImage(IMAGE_SCROLL_MIDDLE, fRenderPosX+m_WndSize.cx-SCROLL_BAR_WIDTH-WND_LEFT_RIGHT_EDGE, 
				fRenderPosY+WND_TOP_BOTTOM_EDGE+(float)(i*SCROLL_MIDDLE_PART_HEIGHT+SCROLL_TOP_BOTTOM_PART_HEIGHT), 7, 15);
		}
		
		RenderImage(IMAGE_SCROLL_BOTTOM, fRenderPosX+m_WndSize.cx-SCROLL_BAR_WIDTH-WND_LEFT_RIGHT_EDGE, 
			m_WndPos.y-WND_TOP_BOTTOM_EDGE-SCROLL_TOP_BOTTOM_PART_HEIGHT, 7, 3);
		
		//. ��ũ�ѹ� ��ư
		EnableAlphaTest();
		if(m_EventState == EVENT_SCROLL_BTN_DOWN)
		{
			glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
		}
		else
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		RenderImage(IMAGE_SCROLLBAR_ON, m_ScrollBtnPos.x, m_ScrollBtnPos.y, SCROLL_BTN_WIDTH, SCROLL_BTN_HEIGHT);
		DisableAlphaBlend();
	}

	return true;
}

bool SEASON3B::CNewUIChatLogWindow::Create(CNewUIManager* pNewUIMng, int x, int y, int nShowingLines /* = 6 */)
{
	Release();

	if(NULL == pNewUIMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_CHATLOGWINDOW, this);

	m_WndPos.x = x; m_WndPos.y = y;
	//. ��� ���� ���μ��� �����ϰ� â ����� ���´�.
	SetNumberOfShowingLines(nShowingLines);

	LoadImages();

	return true;
}

void SEASON3B::CNewUIChatLogWindow::Release()
{
	UnloadImages();
	
	ResetFilter();
#ifdef KJH_FIX_UI_CHAT_MESSAGE
	ClearAll();
#else // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
	Clear();
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
	Init();
}

void SEASON3B::CNewUIChatLogWindow::SetPosition(int x, int y) 
{ 
	m_WndPos.x = x; 
	m_WndPos.y = y; 
}

#ifdef KJH_FIX_UI_CHAT_MESSAGE

void SEASON3B::CNewUIChatLogWindow::AddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType , MESSAGE_TYPE ErrMsgType /*= TYPE_ALL_MESSAGE*/)
{
	if (strID.empty() && strText.empty()) 
	{
		return;
	}

	// �ش�޼��� �����̳�
	if (GetNumberOfLines(MsgType) >= MAX_NUMBER_OF_LINES)
	{
		RemoveFrontLine(MsgType);
	}

	// ��ü�޼��� �����̳�
	if (GetNumberOfLines(TYPE_ALL_MESSAGE) >= MAX_NUMBER_OF_LINES)
	{
		RemoveFrontLine(TYPE_ALL_MESSAGE);
	}
	
	if(m_vecFilters.empty() == true)		// ���� ���� ����
	{
		ProcessAddText(strID, strText, MsgType, ErrMsgType);	
	}
	else	// ���� ���� ����
	{
		if(MsgType != TYPE_CHAT_MESSAGE)
		{
			ProcessAddText(strID, strText, MsgType, ErrMsgType);
		}
		else if(CheckFilterText(strID) || CheckFilterText(strText))	// ���� �ܾ �ɷ� ����ٸ�
		{
			ProcessAddText(strID, strText, MsgType, ErrMsgType);		
			
			if(g_pOption->IsWhisperSound())
			{
				PlayBuffer(SOUND_WHISPER);	// ���� ���� �Ӹ��� ������
			} 
		}
	}
}

void SEASON3B::CNewUIChatLogWindow::ProcessAddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType, MESSAGE_TYPE ErrMsgType)
{
	// �ش� �޼��� ��������
	type_vector_msgs* pvecMsgs = GetMsgs(MsgType);
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

	int nScrollLines = 0;
	if(strText.size() >= 20)	//. �ؽ�Ʈ ����ó��
	{
		type_string	strText1, strText2;
		SeparateText(strID, strText, strText1, strText2);
		if(!strText1.empty())
		{
			CMessageText* pMsgText = new CMessageText;
			if(!pMsgText->Create(strID, strText1, MsgType))
				delete pMsgText;
			else
			{
				pvecMsgs->push_back(pMsgText);			// �ش� �޼��� �����̳�
			}

			CMessageText* pAllMsgText = new CMessageText;
			if(!pAllMsgText->Create(strID, strText1, MsgType))
				delete pAllMsgText;
			else
			{
				m_vecAllMsgs.push_back(pAllMsgText);		// ��� �޼��� �����̳�
			}

			// �ش� �޼����� ���� �޼����̸�,
			// ErrMsgType�� �˻��Ͽ� �ش� �޼��� �����̳ʿ� �߰�.
			// ex : ErrMsgType�� TYPE_WHISPER_ERROR �̸�, Whisper�����̳ʿ� �����޼����� �߰��Ѵ�.
			if( (MsgType == TYPE_ERROR_MESSAGE) 
				&& (ErrMsgType != TYPE_ERROR_MESSAGE && ErrMsgType != TYPE_ALL_MESSAGE) )
			{
				type_vector_msgs* pErrvecMsgs = GetMsgs(ErrMsgType);
				if( pErrvecMsgs == NULL )
				{
					assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
					return;
				}

				CMessageText* pErrMsgText = new CMessageText;
				if(!pErrMsgText->Create(strID, strText1, MsgType))
					delete pErrMsgText;
				else
				{
					pErrvecMsgs->push_back(pErrMsgText);		// ��� �޼��� �����̳�
				}
			}
			
			// ���� �����Ǵ� �޼����� ��ü�޼����̰ų� ���� �߰��Ǵ� �޼����̸�, ��ĭ �ø���.
			if( GetCurrentMsgType() == TYPE_ALL_MESSAGE || GetCurrentMsgType() == MsgType)
			{
				nScrollLines++;
			}
		}
		if(!strText2.empty())
		{
			CMessageText* pMsgText = new CMessageText;
			if(!pMsgText->Create("", strText2, MsgType))
				delete pMsgText;
			else
			{
				pvecMsgs->push_back(pMsgText);			// �ش� �޼��� �����̳�
			}
			
			CMessageText* pAllMsgText = new CMessageText;
			if(!pAllMsgText->Create("", strText2, MsgType))
				delete pAllMsgText;
			else
			{
				m_vecAllMsgs.push_back(pAllMsgText);		// ��� �޼��� �����̳�
			}

			// �ش� �޼����� ���� �޼����̸�,
			// ErrMsgType�� �˻��Ͽ� �ش� �޼��� �����̳ʿ� �߰�.
			// ex : ErrMsgType�� TYPE_WHISPER_ERROR �̸�, Whisper�����̳ʿ� �����޼����� �߰��Ѵ�.
			if( (MsgType == TYPE_ERROR_MESSAGE) 
				&& (ErrMsgType != TYPE_ERROR_MESSAGE && ErrMsgType != TYPE_ALL_MESSAGE) )
			{
				type_vector_msgs* pErrvecMsgs = GetMsgs(ErrMsgType);
				if( pErrvecMsgs == NULL )
				{
					assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
					return;
				}
				
				CMessageText* pErrMsgText = new CMessageText;
				if(!pErrMsgText->Create("", strText2, MsgType))
					delete pErrMsgText;
				else
				{
					pErrvecMsgs->push_back(pErrMsgText);		// ��� �޼��� �����̳�
				}
			}
			
			// ���� �����Ǵ� �޼����� ��ü�޼����̰ų� ���� �߰��Ǵ� �޼����̸�, ��ĭ �ø���.
			if( GetCurrentMsgType() == TYPE_ALL_MESSAGE || GetCurrentMsgType() == MsgType)
			{
				nScrollLines++;
			}
		}
	}
	else
	{
		CMessageText* pMsgText = new CMessageText;
		if(!pMsgText->Create(strID, strText, MsgType))
			delete pMsgText;
		else
		{
			pvecMsgs->push_back(pMsgText);			// �ش� �޼��� �����̳�
		}
		
		CMessageText* pAllMsgText = new CMessageText;
		if(!pAllMsgText->Create(strID, strText, MsgType))
			delete pAllMsgText;
		else
		{
			m_vecAllMsgs.push_back(pAllMsgText);		// ��� �޼��� �����̳�
		}

		// �ش� �޼����� ���� �޼����̸�,
		// ErrMsgType�� �˻��Ͽ� �ش� �޼��� �����̳ʿ� �߰�.
		// ex : ErrMsgType�� TYPE_WHISPER_ERROR �̸�, Whisper�����̳ʿ� �����޼����� �߰��Ѵ�.
		if( (MsgType == TYPE_ERROR_MESSAGE) 
			&& (ErrMsgType != TYPE_ERROR_MESSAGE && ErrMsgType != TYPE_ALL_MESSAGE) )
		{
			type_vector_msgs* pErrvecMsgs = GetMsgs(ErrMsgType);
			if( pErrvecMsgs == NULL )
			{
				assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
				return;
			}
			
			CMessageText* pErrMsgText = new CMessageText;
			if(!pErrMsgText->Create(strID, strText, MsgType))
				delete pErrMsgText;
			else
			{
				pErrvecMsgs->push_back(pErrMsgText);		// ��� �޼��� �����̳�
			}
		}

		// ���� �����Ǵ� �޼����� ��ü�޼����̰ų� ���� �߰��Ǵ� �޼����̸�, ��ĭ �ø���.
		if( GetCurrentMsgType() == TYPE_ALL_MESSAGE || GetCurrentMsgType() == MsgType)
		{
			nScrollLines++;
		}
	}

	// �������� �޼��� ��������
	pvecMsgs = GetMsgs( GetCurrentMsgType() );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}


	//. Auto Scrolling
	if( nScrollLines > 0 && ((pvecMsgs->size() - (m_iCurrentRenderEndLine+1) - nScrollLines) < 3) )
		m_iCurrentRenderEndLine = pvecMsgs->size()-1;
	else if(!m_bShowFrame)
		m_iCurrentRenderEndLine = pvecMsgs->size()-1;
}

#else // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
void SEASON3B::CNewUIChatLogWindow::AddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType)
{
	if (strID.empty() && strText.empty()) 
	{
		return;
	}

	if (GetNumberOfLines() > MAX_NUMBER_OF_LINES)
	{
		RemoveFrontLine();
	}
	
	if(m_vecFilters.empty() == true)		// ���� ���� ����
	{
		ProcessAddText(strID, strText, MsgType);	
	}
	else	// ���� ���� ����
	{
		if(MsgType != TYPE_CHAT_MESSAGE)
		{
			ProcessAddText(strID, strText, MsgType);
		}
		else if(CheckFilterText(strID) || CheckFilterText(strText))	// ���� �ܾ �ɷ� ����ٸ�
		{
			ProcessAddText(strID, strText, MsgType);		
			
			if(g_pOption->IsWhisperSound())
			{
				PlayBuffer(SOUND_WHISPER);	// ���� ���� �Ӹ��� ������
			}
		}
	}
}

void SEASON3B::CNewUIChatLogWindow::ProcessAddText(const type_string& strID, const type_string& strText, MESSAGE_TYPE MsgType)
{
	int nScrollLines = 0;
	if(strText.size() >= 20)	//. �ؽ�Ʈ ����ó��
	{
		type_string	strText1, strText2;
		SeparateText(strID, strText, strText1, strText2);
		if(!strText1.empty())
		{
			CMessageText* pMsgText = new CMessageText;
			if(!pMsgText->Create(strID, strText1, MsgType))
				delete pMsgText;
			else
			{
				m_vecMsgs.push_back(pMsgText);
				nScrollLines++;
			}
		}
		if(!strText2.empty())
		{
			CMessageText* pMsgText = new CMessageText;
			if(!pMsgText->Create("", strText2, MsgType))
				delete pMsgText;
			else
			{
				m_vecMsgs.push_back(pMsgText);
				nScrollLines++;
			}
		}
	}
	else
	{
		CMessageText* pMsgText = new CMessageText;
		if(!pMsgText->Create(strID, strText, MsgType))
			delete pMsgText;
		else
		{
			m_vecMsgs.push_back(pMsgText);
			nScrollLines++;
		}
	}
	//. Auto Scrolling
	if( nScrollLines > 0 && ((m_vecMsgs.size() - (m_iCurrentRenderEndLine+1) - nScrollLines) < 3) )
		m_iCurrentRenderEndLine = m_vecMsgs.size()-1;
	else if(!m_bShowFrame)
		m_iCurrentRenderEndLine = m_vecMsgs.size()-1;
}
//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

#ifdef KJH_FIX_UI_CHAT_MESSAGE
////////////////////////////////////////////////////////////////////////////////////
// RemoveFrontLine
// - �ش��ϴ� �޼��� �����̳��� �޼����� �� ó���� �� �޼����� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::RemoveFrontLine(MESSAGE_TYPE MsgType)
{
	type_vector_msgs* pvecMsgs = GetMsgs(MsgType);

	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

	type_vector_msgs::iterator vi = pvecMsgs->begin();
	if(vi != pvecMsgs->end())
	{
		delete (*vi);	//. ù�� �����
		vi = pvecMsgs->erase(vi);
	}

	if( MsgType == GetCurrentMsgType() )
	{
		Scrolling(GetCurrentRenderEndLine());
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Clear
// - �ش��ϴ� �޼��� �����̳ʸ� Clear�Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::Clear(MESSAGE_TYPE MsgType)
{
	type_vector_msgs* pvecMsgs = GetMsgs(MsgType);
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

	type_vector_msgs::iterator vi_msg = pvecMsgs->begin();
	for(; vi_msg != pvecMsgs->end(); vi_msg++)
		delete (*vi_msg);
	pvecMsgs->clear();

	if( MsgType == GetCurrentMsgType() )
	{
		m_iCurrentRenderEndLine = -1;
	}
}

////////////////////////////////////////////////////////////////////////////////////
// GetNumberOfLines
// - �ش� �޼��� �����̳ʿ��� �޼��� ������ ���Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
size_t SEASON3B::CNewUIChatLogWindow::GetNumberOfLines(MESSAGE_TYPE MsgType)
{ 
	type_vector_msgs* pvecMsgs = GetMsgs( MsgType );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return 0;
	}
	
	return pvecMsgs->size(); 
}

#else // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------

void SEASON3B::CNewUIChatLogWindow::RemoveFrontLine()
{
	type_vector_msgs::iterator vi = m_vecMsgs.begin();
	if(vi != m_vecMsgs.end())
	{
		delete (*vi);	//. ù�� �����
		vi = m_vecMsgs.erase(vi);

		if(vi != m_vecMsgs.end())
		{
			if((*vi)->GetType() == TYPE_CHAT_MESSAGE && (*vi)->GetID().empty())	//. ä���̰� ���̵� ���ٸ�
			{	//. �������� �Ǵ��ϰ� ����ϰ� ���� �� �����ش�.
				delete (*vi);
				m_vecMsgs.erase(vi);
			}
		}
		Scrolling(GetCurrentRenderEndLine());
	}
}

void SEASON3B::CNewUIChatLogWindow::Clear()
{
	type_vector_msgs::iterator vi_msg = m_vecMsgs.begin();
	for(; vi_msg != m_vecMsgs.end(); vi_msg++)
		delete (*vi_msg);
	m_vecMsgs.clear();

	m_iCurrentRenderEndLine = -1;
}

size_t SEASON3B::CNewUIChatLogWindow::GetNumberOfLines() const 
{ 
	return m_vecMsgs.size(); 
}

//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

int SEASON3B::CNewUIChatLogWindow::GetCurrentRenderEndLine() const 
{ 
	return m_iCurrentRenderEndLine; 
}

#ifdef KJH_FIX_UI_CHAT_MESSAGE
void SEASON3B::CNewUIChatLogWindow::Scrolling(int nRenderEndLine)
{
	type_vector_msgs* pvecMsgs = GetMsgs( m_CurrentRenderMsgType );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

#ifdef _VS2008PORTING
	if((int)pvecMsgs->size() <= m_nShowingLines)
#else // _VS2008PORTING
	if(pvecMsgs->size() <= m_nShowingLines)
#endif // _VS2008PORTING
	{
		m_iCurrentRenderEndLine = pvecMsgs->size() - 1;
	}
	else
	{
		if(nRenderEndLine < m_nShowingLines)
			m_iCurrentRenderEndLine = m_nShowingLines - 1;
#ifdef _VS2008PORTING
		else if(nRenderEndLine >= (int)pvecMsgs->size())
#else // _VS2008PORTING
		else if(nRenderEndLine >= pvecMsgs->size())
#endif // _VS2008PORTING
			m_iCurrentRenderEndLine = pvecMsgs->size() - 1;
		else
			m_iCurrentRenderEndLine = nRenderEndLine;
	}
}

#else // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
void SEASON3B::CNewUIChatLogWindow::Scrolling(int nRenderEndLine)
{
	if(m_vecMsgs.size() <= m_nShowingLines)
	{
		m_iCurrentRenderEndLine = m_vecMsgs.size() - 1;
	}
	else
	{
		if(nRenderEndLine < m_nShowingLines)
			m_iCurrentRenderEndLine = m_nShowingLines - 1;
		else if(nRenderEndLine >= m_vecMsgs.size())
			m_iCurrentRenderEndLine = m_vecMsgs.size() - 1;
		else
			m_iCurrentRenderEndLine = nRenderEndLine;
	}
}
//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�

void SEASON3B::CNewUIChatLogWindow::SetFilterText(const type_string& strFilterText)
{
	bool bPrevFilter = false;

	// �����ǵ��� 5������ ����String�� ���� �ϴ� ������ �˰� ������,
	// ������ ������, Reset�� �����ְ� ����... (��ȹ���ǵ�??)
	if(!m_vecFilters.empty())
	{
		bPrevFilter = true;
		ResetFilter();
	}

	unicode::t_char szTemp[MAX_CHAT_BUFFER_SIZE + 1] = {0, };
	unicode::_strncpy(szTemp, strFilterText.c_str(), MAX_CHAT_BUFFER_SIZE);
	szTemp[MAX_CHAT_BUFFER_SIZE] = '\0';
	unicode::t_char* token = unicode::_strtok(szTemp, " ");
	token = unicode::_strtok(NULL, " ");

	if(token == NULL)
	{
		ResetFilter();
		AddText("", GlobalText[756], TYPE_SYSTEM_MESSAGE);	// ���Ͱ� �����Ǿ����ϴ�.
	}
	else
	{
		for(int i=0; i<5; i++)
		{
			if(NULL == token) 
			{
				break;
			}
			AddFilterWord(token);
			token = unicode::_strtok(NULL, " ");
		}
		
		AddText("", GlobalText[755], TYPE_SYSTEM_MESSAGE);	// ���Ͱ� �����Ǿ����ϴ�.
	}
}

void SEASON3B::CNewUIChatLogWindow::ResetFilter() 
{ 
	m_vecFilters.clear();
}

void SEASON3B::CNewUIChatLogWindow::SetSizeAuto()
{
	SetNumberOfShowingLines(GetNumberOfShowingLines()+3);
}

void SEASON3B::CNewUIChatLogWindow::SetNumberOfShowingLines(int nShowingLines, OUT LPSIZE lpBoxSize/* = NULL*/)
{
	m_nShowingLines = (int)(nShowingLines/3)*3;
	if(m_nShowingLines<3)
		m_nShowingLines = 3;
	if(m_nShowingLines>15)
		m_nShowingLines = 3;
	
	if(m_nShowingLines > GetCurrentRenderEndLine())
		Scrolling(m_nShowingLines-1);

	UpdateWndSize();
	UpdateScrollPos();

	if(lpBoxSize)
	{
		lpBoxSize->cx = WND_WIDTH;
		lpBoxSize->cy = (SCROLL_MIDDLE_PART_HEIGHT*GetNumberOfShowingLines())
			+ (SCROLL_TOP_BOTTOM_PART_HEIGHT*2) + (WND_TOP_BOTTOM_EDGE*2);
	}
}
size_t SEASON3B::CNewUIChatLogWindow::GetNumberOfShowingLines() const 
{ 
	return m_nShowingLines; 
}

void SEASON3B::CNewUIChatLogWindow::SetBackAlphaAuto()
{
	m_fBackAlpha += 0.2f;

	if(m_fBackAlpha > 0.9f) 
	{
		m_fBackAlpha = 0.2f;
	}
}

void SEASON3B::CNewUIChatLogWindow::SetBackAlpha(float fAlpha)
{
	if(fAlpha < 0.f)
		m_fBackAlpha = 0.f;
	else if(fAlpha > 1.f)
		m_fBackAlpha = 1.f;
	else
		m_fBackAlpha = fAlpha;
}

float SEASON3B::CNewUIChatLogWindow::GetBackAlpha() const 
{ 
	return m_fBackAlpha; 
}

void SEASON3B::CNewUIChatLogWindow::ShowFrame()
{ 
	m_bShowFrame = true; 
}

void SEASON3B::CNewUIChatLogWindow::HideFrame()
{ 
	m_bShowFrame = false; 
}

bool SEASON3B::CNewUIChatLogWindow::IsShowFrame()
{
	return m_bShowFrame;
}

bool SEASON3B::CNewUIChatLogWindow::UpdateMouseEvent()
{
	extern float g_fScreenRate_x;

	if(m_EventState == EVENT_NONE && false == MouseLButtonPush &&
		SEASON3B::CheckMouseIn(m_WndPos.x, m_WndPos.y-m_WndSize.cy, m_WndSize.cx, m_WndSize.cy))
	{
		m_EventState = EVENT_CLIENT_WND_HOVER;
		return false;
	}
	if(false == MouseLButtonPush && m_EventState == EVENT_CLIENT_WND_HOVER &&
		false == SEASON3B::CheckMouseIn(m_WndPos.x, m_WndPos.y-m_WndSize.cy, m_WndSize.cx, m_WndSize.cy))
	{
		m_EventState = EVENT_NONE;
		return true;
	}

	//. ��ó��
	if(m_EventState == EVENT_CLIENT_WND_HOVER)
	{
		if(MouseWheel > 0)
			Scrolling(GetCurrentRenderEndLine()-1);
		if(MouseWheel < 0)
			Scrolling(GetCurrentRenderEndLine()+1);
		if(MouseWheel != 0)
			MouseWheel = 0;
	}

	m_bPointedMessage = false;
	if(SEASON3B::CheckMouseIn(m_WndPos.x, m_WndPos.y-m_WndSize.cy, m_WndSize.cx, m_WndSize.cy))
	{
		//. �޼��� �׸���
		int iRenderStartLine = 0;
		if(GetCurrentRenderEndLine() >= m_nShowingLines)
			iRenderStartLine = GetCurrentRenderEndLine() - m_nShowingLines + 1;

		for(int i=iRenderStartLine, s=0; i<=GetCurrentRenderEndLine(); i++, s++)
		{
#ifdef KJH_FIX_UI_CHAT_MESSAGE

			type_vector_msgs* pvecMsgs = GetMsgs( GetCurrentMsgType() );
			if( pvecMsgs == NULL )
			{
				assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
				return false;
			}

			CMessageText* pMsgText = (*pvecMsgs)[i];

#else // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�
			CMessageText* pMsgText = m_vecMsgs[i];
#endif // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�

			if(pMsgText->GetType() == TYPE_WHISPER_MESSAGE 
				|| pMsgText->GetType() == TYPE_CHAT_MESSAGE
				|| pMsgText->GetType() == TYPE_PARTY_MESSAGE
				|| pMsgText->GetType() == TYPE_GUILD_MESSAGE
				|| pMsgText->GetType() == TYPE_UNION_MESSAGE
				|| pMsgText->GetType() == TYPE_GM_MESSAGE
				)
			{
				float fRenderPosX = m_WndPos.x;
				float fRenderPosY = m_WndPos.y - m_WndSize.cy + SCROLL_TOP_BOTTOM_PART_HEIGHT;
#ifdef KJH_FIX_UI_CHAT_MESSAGE
				if(GetCurrentRenderEndLine() < m_nShowingLines)
				{
					fRenderPosY = fRenderPosY+FONT_LEADING+(SCROLL_MIDDLE_PART_HEIGHT*(m_nShowingLines-GetCurrentRenderEndLine()-1));
				}
#endif // KJH_FIX_UI_CHAT_MESSAGE

				POINT ptRenderPos;
				ptRenderPos.x = fRenderPosX+WND_LEFT_RIGHT_EDGE;
				ptRenderPos.y = fRenderPosY+FONT_LEADING+(SCROLL_MIDDLE_PART_HEIGHT*s);

				if(SEASON3B::CheckMouseIn(ptRenderPos.x, ptRenderPos.y, WND_WIDTH, SCROLL_MIDDLE_PART_HEIGHT))
				{
					m_bPointedMessage = true;
					m_iPointedMessageIndex = i;

					std::string strID = pMsgText->GetID();
					if(SEASON3B::IsPress(VK_RBUTTON) && strID.empty() == false)
					{
						g_pChatInputBox->SetWhsprID(strID.c_str());
					}
				}
			}
		}
	}

	if(m_bShowFrame)		//// �Ʒ����ʹ� �������� ������쿡�� ó�� ////
	{
		if(m_EventState == EVENT_CLIENT_WND_HOVER && MouseLButtonPush &&
			SEASON3B::CheckMouseIn(m_ScrollBtnPos.x, m_ScrollBtnPos.y, SCROLL_BTN_WIDTH, SCROLL_BTN_HEIGHT))
		{
			extern int MouseY;
			
			m_EventState = EVENT_SCROLL_BTN_DOWN;
			m_iGrapRelativePosY = MouseY - m_ScrollBtnPos.y;
			return false;
		}
		if(m_EventState == EVENT_SCROLL_BTN_DOWN)
		{
			if(SEASON3B::IsRepeat(VK_LBUTTON))
			{
#ifdef KJH_FIX_UI_CHAT_MESSAGE
				if(GetNumberOfLines(GetCurrentMsgType()) > GetNumberOfShowingLines())
#else // KJH_FIX_UI_CHAT_MESSAGE
				if(GetNumberOfLines() > GetNumberOfShowingLines())
#endif // KJH_FIX_UI_CHAT_MESSAGE
				{
					extern int MouseY;
					if(MouseY-m_iGrapRelativePosY < m_WndPos.y-m_WndSize.cy+WND_TOP_BOTTOM_EDGE)
					{
						Scrolling(GetNumberOfShowingLines()-1);
						m_ScrollBtnPos.y = m_WndPos.y-m_WndSize.cy+WND_TOP_BOTTOM_EDGE;
					}
					else if(MouseY-m_iGrapRelativePosY > m_WndPos.y-SCROLL_BTN_HEIGHT-WND_TOP_BOTTOM_EDGE)
					{
#ifdef KJH_FIX_UI_CHAT_MESSAGE
						Scrolling(GetNumberOfLines(GetCurrentMsgType())-1);
#else // KJH_FIX_UI_CHAT_MESSAGE
						Scrolling(GetNumberOfLines()-1);
#endif // KJH_FIX_UI_CHAT_MESSAGE
						m_ScrollBtnPos.y = m_WndPos.y-SCROLL_BTN_HEIGHT-WND_TOP_BOTTOM_EDGE;
					}
					else
					{
						float fScrollRate = (float)((MouseY-m_iGrapRelativePosY) - (m_WndPos.y-m_WndSize.cy+WND_TOP_BOTTOM_EDGE))
							/ (float)(m_WndSize.cy-WND_TOP_BOTTOM_EDGE*2-SCROLL_BTN_HEIGHT);
#ifdef KJH_FIX_UI_CHAT_MESSAGE
						Scrolling(GetNumberOfShowingLines() + (float)(GetNumberOfLines(GetCurrentMsgType())-GetNumberOfShowingLines())*fScrollRate);
#else // KJH_FIX_UI_CHAT_MESSAGE
						Scrolling(GetNumberOfShowingLines() + (float)(GetNumberOfLines()-GetNumberOfShowingLines())*fScrollRate);
#endif // KJH_FIX_UI_CHAT_MESSAGE
						
						m_ScrollBtnPos.y = MouseY - m_iGrapRelativePosY;
					}
				}
				return false;
			}
			if(SEASON3B::IsRelease(VK_LBUTTON))
			{
				m_EventState = EVENT_NONE;
				return true;
			}
		}

		//. ��ư ó��
		POINT ptResizingBtn = { m_WndPos.x, m_WndPos.y-m_WndSize.cy-RESIZING_BTN_HEIGHT };
		if(m_EventState == EVENT_NONE && false == MouseLButtonPush &&
			SEASON3B::CheckMouseIn(ptResizingBtn.x, ptResizingBtn.y, RESIZING_BTN_WIDTH, RESIZING_BTN_HEIGHT))
		{
			m_EventState = EVENT_RESIZING_BTN_HOVER;
			return false;
		}
		if(false == MouseLButtonPush && m_EventState == EVENT_RESIZING_BTN_HOVER &&
			false == SEASON3B::CheckMouseIn(ptResizingBtn.x, ptResizingBtn.y, RESIZING_BTN_WIDTH, RESIZING_BTN_HEIGHT))
		{
			m_EventState = EVENT_NONE;
			return true;
		}
		if(m_EventState == EVENT_RESIZING_BTN_HOVER && MouseLButtonPush && 
			SEASON3B::CheckMouseIn(ptResizingBtn.x, ptResizingBtn.y, RESIZING_BTN_WIDTH, RESIZING_BTN_HEIGHT))
		{
			m_EventState = EVENT_RESIZING_BTN_DOWN;
			return false;
		}
		if(m_EventState == EVENT_RESIZING_BTN_DOWN)
		{
			if(MouseLButtonPush)
			{
				int nTopSections = (15 - GetNumberOfShowingLines()) / 3;
				int nBottomSections = (GetNumberOfShowingLines() - 3) / 3;
				for(int i=0; i<nTopSections; i++)
				{
					if( SEASON3B::CheckMouseIn(0, ptResizingBtn.y-RESIZING_BTN_HEIGHT-((i+1)*SCROLL_MIDDLE_PART_HEIGHT*3*2), 
						640, SCROLL_MIDDLE_PART_HEIGHT*3+RESIZING_BTN_HEIGHT) )
					{
						SetNumberOfShowingLines(GetNumberOfShowingLines() + (i+1)*3);
						return false;
					}
				}
#ifdef _VS2008PORTING
				for(int i=0; i<nBottomSections; i++)
#else // _VS2008PORTING
				for(i=0; i<nBottomSections; i++)
#endif // _VS2008PORTING
				{
					if( SEASON3B::CheckMouseIn(0, ptResizingBtn.y+RESIZING_BTN_HEIGHT+((i+1)*SCROLL_MIDDLE_PART_HEIGHT*3), 
						640, RESIZING_BTN_HEIGHT+SCROLL_MIDDLE_PART_HEIGHT*3) )
					{
						SetNumberOfShowingLines(GetNumberOfShowingLines() - (i+1)*3);
						return false;
					}
				}
				if( SEASON3B::CheckMouseIn(0, 0, 640, m_WndPos.y-(SCROLL_MIDDLE_PART_HEIGHT*15+RESIZING_BTN_HEIGHT+SCROLL_TOP_BOTTOM_PART_HEIGHT*2)) )
				{
					SetNumberOfShowingLines(15);
				}
				if( SEASON3B::CheckMouseIn(0, m_WndPos.y-(SCROLL_MIDDLE_PART_HEIGHT*3+SCROLL_TOP_BOTTOM_PART_HEIGHT*2), 
					640, SCROLL_MIDDLE_PART_HEIGHT*3+SCROLL_TOP_BOTTOM_PART_HEIGHT*2) )
				{
					SetNumberOfShowingLines(3);
				}
				return false;
			}
			if(false == MouseLButtonPush || true == MouseLButtonPop)
			{
				m_EventState = EVENT_NONE;
				return true;
			}
		}
	}
	return true;
}

bool SEASON3B::CNewUIChatLogWindow::UpdateKeyEvent()
{
	return true;
}

bool SEASON3B::CNewUIChatLogWindow::Update()
{
	UpdateScrollPos();

	return true;
}
bool SEASON3B::CNewUIChatLogWindow::Render()
{
	if(RenderBackground() == false)
	{
		return false;
	}

	
#ifdef KJH_FIX_UI_CHAT_MESSAGE
	if( m_bShowChatLog == true )
	{
		if(RenderMessages() == false)
		{
			return false;
		}
	}
#else // KJH_FIX_UI_CHAT_MESSAGE
	if(RenderMessages() == false)
	{
		return false;
	}
#endif // KJH_FIX_UI_CHAT_MESSAGE

	if(RenderFrame() == false) 
	{
		return false;
	}

	return true;
}

float SEASON3B::CNewUIChatLogWindow::GetLayerDepth() 
{ 
	return 6.1f; 
}

float SEASON3B::CNewUIChatLogWindow::GetKeyEventOrder() 
{
	return 8.0f; 
}

#ifdef KJH_FIX_UI_CHAT_MESSAGE

bool SEASON3B::CNewUIChatLogWindow::CheckChatRedundancy(const type_string& strText, int iSearchLine/* = 1*/)
{
	// ��ü �޼����� �˻��Ѵ�.
	type_vector_msgs* pvecMsgs = GetMsgs( TYPE_ALL_MESSAGE );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return 0;
	}

	if( pvecMsgs->empty() ) return false;
	type_vector_msgs::reverse_iterator vri_msgs = pvecMsgs->rbegin();
	for(int i = 0; (i < iSearchLine) || (vri_msgs != pvecMsgs->rend()); vri_msgs++, i++)
		if(0 == (*vri_msgs)->GetText().compare(strText)) return true;		//. �ߺ� �߰�
	return false;
}

#else // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
bool SEASON3B::CNewUIChatLogWindow::CheckChatRedundancy(const type_string& strText, int iSearchLine/* = 1*/)
{
	if( m_vecMsgs.empty() ) return false;
	type_vector_msgs::reverse_iterator vri_msgs = m_vecMsgs.rbegin();
	for(int i = 0; (i < iSearchLine) || (vri_msgs != m_vecMsgs.rend()); vri_msgs++, i++)
		if(0 == (*vri_msgs)->GetText().compare(strText)) return true;		//. �ߺ� �߰�
	return false;
}
//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE					// ������ �� ������ �ϴ� �ҽ�

void SEASON3B::CNewUIChatLogWindow::SeparateText(IN const type_string& strID, IN const type_string& strText, OUT type_string& strText1, OUT type_string& strText2)
{
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	extern float g_fScreenRate_x;
	
	SIZE TextSize;
	type_string strIDPart = strID + " : ";
	wstring wstrUTF16 = L"";
	
	// ȭ�鿡 ������ ���ڿ� ������ ����: ���̵� + (:) + ����
	// MaxFirstLineWidth: ���̵� + (:) �� ���̸� �� ������
	g_pMultiLanguage->ConvertCharToWideStr(wstrUTF16, strIDPart.c_str());
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), wstrUTF16.c_str(), wstrUTF16.length(), &TextSize);
	size_t MaxFirstLineWidth = CLIENT_WIDTH - (size_t)(TextSize.cx / g_fScreenRate_x);
	
	g_pMultiLanguage->ConvertCharToWideStr(wstrUTF16, strText.c_str());
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), wstrUTF16.c_str(), wstrUTF16.length(), &TextSize);

	BOOL bSpaceExist = (wstrUTF16.find_last_of(L" ") != wstring::npos) ? TRUE : FALSE;
	int iLocToken = wstrUTF16.length(); 
	
	//�ڿ������� ���鼭 �˻�
	//���ڿ��� ������ ������ ? ���� ���� : ���� ����
	while (((size_t)(TextSize.cx / g_fScreenRate_x) > MaxFirstLineWidth) && (iLocToken > -1))
	{
		iLocToken = (bSpaceExist) ? wstrUTF16.find_last_of(L" ", iLocToken-1) : iLocToken-1;
		
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), 
												(wstrUTF16.substr(0, iLocToken)).c_str(), 
												iLocToken, 
												&TextSize);
	}

	g_pMultiLanguage->ConvertWideCharToStr(strText1, (wstrUTF16.substr(0, iLocToken)).c_str(), CP_UTF8);
	g_pMultiLanguage->ConvertWideCharToStr(strText2, (wstrUTF16.substr(iLocToken, wstrUTF16.length()-iLocToken)).c_str(), CP_UTF8);

#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	extern float g_fScreenRate_x;

	SIZE TextSize;
	type_string strIDPart = strID + " : ";

	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), strIDPart.c_str(), strIDPart.size(), &TextSize);
	size_t TextExtentWidth = (size_t)(TextSize.cx / g_fScreenRate_x);
	size_t MaxFirstLineWidth = CLIENT_WIDTH - TextExtentWidth;

	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), strText.c_str(), strText.size(), &TextSize);
	TextExtentWidth = (size_t)(TextSize.cx / g_fScreenRate_x);
	if(TextExtentWidth > MaxFirstLineWidth)	//. �߶�� �ϴ°�?
	{
#ifdef _VS2008PORTING
		int prev_offset = 0;
		for(int cur_offset = 0; cur_offset<(int)strText.size(); )	
#else // _VS2008PORTING
		int cur_offset = 0, prev_offset = 0;
		for(; cur_offset<strText.size(); )
#endif // _VS2008PORTING
		{
			prev_offset = cur_offset;
			size_t offset = _mbclen((const unsigned char*)(strText.c_str()+cur_offset));
			cur_offset += offset;

			type_string strTemp(strText, 0, cur_offset+offset/* size */);
			unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), strTemp.c_str(), strTemp.size(), &TextSize);
			TextExtentWidth = (size_t)(TextSize.cx / g_fScreenRate_x);
			if(TextExtentWidth > MaxFirstLineWidth && cur_offset != 0)
			{
				strText1 = type_string(strText, 0, prev_offset/* size */);
				strText2 = type_string(strText, prev_offset, strText.size()-prev_offset/* size */);
				return;
			}
		}
	}
	else
	{
		strText1 = strText;
	}
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
}
bool SEASON3B::CNewUIChatLogWindow::CheckFilterText(const type_string& strTestText)
{
	type_vector_filters::iterator vi_filters = m_vecFilters.begin();
	for(; vi_filters != m_vecFilters.end(); vi_filters++)
	{
		if(FindText(strTestText.c_str(), (*vi_filters).c_str()) == true)
		{
			return true;
		}
	}

	return false;
}

#ifndef KJH_FIX_UI_CHAT_MESSAGE					// #ifndef ������ �� ������ �ϴ� �ҽ�
//-----------------------------------------------------------------------------------------
bool SEASON3B::CNewUIChatLogWindow::CheckMessageShowFlag(SHOW_MESSAGE_FLAG Flag)
{
	if((m_ShowMessageFlag & Flag) == Flag)
		return true;
	return false;
}

void SEASON3B::CNewUIChatLogWindow::ShowMessage(SHOW_MESSAGE_FLAG Flag)
{
	m_ShowMessageFlag = Flag;
}
//-----------------------------------------------------------------------------------------
#endif // KJH_FIX_UI_CHAT_MESSAGE				// ������ �� ������ �ϴ� �ҽ�

void SEASON3B::CNewUIChatLogWindow::UpdateWndSize()
{
	m_WndSize.cx = WND_WIDTH;
	m_WndSize.cy = (SCROLL_MIDDLE_PART_HEIGHT*GetNumberOfShowingLines())
		+ (SCROLL_TOP_BOTTOM_PART_HEIGHT*2) + (WND_TOP_BOTTOM_EDGE*2);
}

void SEASON3B::CNewUIChatLogWindow::UpdateScrollPos()
{
	//. ��ũ�ѹ� ��ġ���
	float fPosRate = 1.f;
#ifdef KJH_FIX_UI_CHAT_MESSAGE
	if(GetNumberOfLines(GetCurrentMsgType()) > GetNumberOfShowingLines())
#else // KJH_FIX_UI_CHAT_MESSAGE
	if(GetNumberOfLines() > GetNumberOfShowingLines())
#endif // KJH_FIX_UI_CHAT_MESSAGE
	{
#ifdef _VS2008PORTING
		if((int)GetNumberOfShowingLines() > GetCurrentRenderEndLine())
#else // _VS2008PORTING
		if(GetNumberOfShowingLines() > GetCurrentRenderEndLine())
#endif // _VS2008PORTING
		{
			fPosRate = 0.f;
		}
		else
		{
#ifdef KJH_FIX_UI_CHAT_MESSAGE
			fPosRate = (float)(GetCurrentRenderEndLine()+1-GetNumberOfShowingLines()) 
				/ (float)(GetNumberOfLines(GetCurrentMsgType())-GetNumberOfShowingLines());
#else KJH_FIX_UI_CHAT_MESSAGE
			fPosRate = (float)(GetCurrentRenderEndLine()+1-GetNumberOfShowingLines()) 
				/ (float)(GetNumberOfLines()-GetNumberOfShowingLines());
#endif // KJH_FIX_UI_CHAT_MESSAGE
		}
	}
	if(m_EventState != EVENT_SCROLL_BTN_DOWN)
	{
		m_ScrollBtnPos.x = m_WndPos.x+m_WndSize.cx-SCROLL_BAR_WIDTH-WND_LEFT_RIGHT_EDGE-4;
		m_ScrollBtnPos.y = m_WndPos.y-m_WndSize.cy+WND_TOP_BOTTOM_EDGE 
			+ ((float)(m_WndSize.cy-SCROLL_BTN_HEIGHT-WND_TOP_BOTTOM_EDGE*2) * fPosRate);
	}
}

void SEASON3B::CNewUIChatLogWindow::AddFilterWord(const type_string& strWord)
{
	if(m_vecFilters.size() > 5)	//. �ִ� 5�� ����
		return;

	type_vector_filters::iterator vi_filters = m_vecFilters.begin();
	for(; vi_filters != m_vecFilters.end(); vi_filters++)	//. �ߺ��˻�
	{
		if(0 == (*vi_filters).compare(strWord))
		{
			return;
		}
	}

	m_vecFilters.push_back(strWord);
}

// �߰�
#ifdef KJH_FIX_UI_CHAT_MESSAGE

////////////////////////////////////////////////////////////////////////////////////
// ClearAll
// - ��� �޼��� �����̳ʸ� Clear�Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::ClearAll()
{
	for(int i=TYPE_ALL_MESSAGE ; i<NUMBER_OF_TYPES ; i++)
	{
		Clear((MESSAGE_TYPE)i);
	}

	m_iCurrentRenderEndLine = -1;
}

////////////////////////////////////////////////////////////////////////////////////
// SetCurrentMsgType()
// - ���� �޼��� Ÿ�� Return
////////////////////////////////////////////////////////////////////////////////////
SEASON3B::CNewUIChatLogWindow::type_vector_msgs* SEASON3B::CNewUIChatLogWindow::GetMsgs(MESSAGE_TYPE MsgType)
{
	switch( MsgType )
	{
		case TYPE_ALL_MESSAGE:
			return &m_vecAllMsgs;
		case TYPE_CHAT_MESSAGE:
			return &m_VecChatMsgs;	
		case TYPE_WHISPER_MESSAGE:
			return &m_vecWhisperMsgs;
		case TYPE_SYSTEM_MESSAGE:
			return &m_VecSystemMsgs;
		case TYPE_ERROR_MESSAGE:
			return &m_vecErrorMsgs;
		case TYPE_PARTY_MESSAGE:
			return &m_vecPartyMsgs;
		case TYPE_GUILD_MESSAGE:
			return &m_vecGuildMsgs;
		case TYPE_UNION_MESSAGE:
			return &m_vecUnionMsgs;
		case TYPE_GM_MESSAGE:
			return &m_vecGMMsgs;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
// SetCurrentMsgType()
// - ���� �޼��� Ÿ���� �ٲ۴�.
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::ChangeMessage(MESSAGE_TYPE MsgType)
{

	m_CurrentRenderMsgType = MsgType;

	type_vector_msgs* pvecMsgs = GetMsgs( GetCurrentMsgType() );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

	// ��ũ�Ѹ� �ʱ�ȭ
	m_iCurrentRenderEndLine = pvecMsgs->size() - 1;
}

////////////////////////////////////////////////////////////////////////////////////
// GetCurrentMsgType()
// - ���� �޼��� Ÿ���� return.
////////////////////////////////////////////////////////////////////////////////////
SEASON3B::MESSAGE_TYPE SEASON3B::CNewUIChatLogWindow::GetCurrentMsgType() const
{
	return m_CurrentRenderMsgType;
}

////////////////////////////////////////////////////////////////////////////////////
// ShowChatLog()
// - ä�ø޼��� Show
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::ShowChatLog()
{
	m_bShowChatLog = true;

	type_vector_msgs* pvecMsgs = GetMsgs( GetCurrentMsgType() );
	if( pvecMsgs == NULL )
	{
		assert(!"�޼��� Ÿ���� ���� �ʽ��ϴ�.!");
		return;
	}

	// ��ũ�Ѹ� �ʱ�ȭ
	m_iCurrentRenderEndLine = pvecMsgs->size() - 1;
}

////////////////////////////////////////////////////////////////////////////////////
// HideChatLog()
// - ä�ø޼��� Hide
////////////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIChatLogWindow::HideChatLog()
{
	m_bShowChatLog = false;
}

#endif // KJH_FIX_UI_CHAT_MESSAGE
