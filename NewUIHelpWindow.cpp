// NewUIHelpWindow.cpp: implementation of the CNewUIHelpWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NewUIHelpWindow.h"
#include "NewUISystem.h"
#include "ZzzInventory.h"
#include "DSPlaySound.h"


using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SEASON3B::CNewUIHelpWindow::CNewUIHelpWindow()
{
	m_pNewUIMng = NULL;
	m_Pos.x = 0;
	m_Pos.y = 0;

	m_iIndex = 0;
}

SEASON3B::CNewUIHelpWindow::~CNewUIHelpWindow()
{
	Release();
}

bool SEASON3B::CNewUIHelpWindow::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if( NULL == pNewUIMng )
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_HELP, this);
	
	SetPos(x, y);

	Show(false);

	return true;
}

void SEASON3B::CNewUIHelpWindow::Release()
{
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}	
}

void SEASON3B::CNewUIHelpWindow::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

bool SEASON3B::CNewUIHelpWindow::UpdateMouseEvent()
{
	return true;
}

bool SEASON3B::CNewUIHelpWindow::UpdateKeyEvent()
{
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_HELP))
	{
		if(IsPress(VK_F1) == true)
		{
#ifdef PSW_ADD_FOREIGN_HELPWINDOW
			if(++m_iIndex > 1)
#else //PSW_ADD_FOREIGN_HELPWINDOW
			if(++m_iIndex > 3)
#endif //PSW_ADD_FOREIGN_HELPWINDOW			
			{
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_HELP);
				PlayBuffer(SOUND_CLICK01);
			}

			return false;
		}
		
		if(IsPress(VK_ESCAPE) == true)
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_HELP);
			PlayBuffer(SOUND_CLICK01);

			return false;
		}
	}

	return true;
}

bool SEASON3B::CNewUIHelpWindow::Update()
{
	return true;
}

bool SEASON3B::CNewUIHelpWindow::Render()
{
	EnableAlphaTest();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	extern char TextList[30][100];
	extern int TextListColor[30];
	extern int TextBold[30];
	
	if(m_iIndex == 0)
	{
		int iTextNum = 0;

		unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 120 "Ű ����"
		unicode::_strcpy(TextList[iTextNum], GlobalText[120]);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE;
		TextBold[iTextNum] = true;
		iTextNum++;

     	unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 121 "F1 : ���� On/Off"
		// 122 "F2 : ä��â On/Off"
		// 123 "F3 : �ӼӸ� On/Off"
		// 124 "F4 : ä��â ũ�� ����"
		// 125 "Enter : ä�ø��"
		// 126 "C : �ɸ�������â"
		// 127 "I,V : �κ��丮â"
		// 128 "P : ��Ƽâ"
		// 129 "G : ���â"
		// 130 "Q : ȸ������ ���"
		// 131 "W : �������� ���"
		// 132 "E : �ص����� ���"
		// 133 "Shift : �ɸ��� ����Ű"
		// 134 "Ctrl+����Ű : ��ų��Ű ���"
		// 135 "����Ű : ��Ű�� ��ϵ� ��ų ����"
		// 136 "Alt : �ٴڿ� ������ ������ ����"
		// 137 "Alt+������ : �������� �켱������ ����"
		// 138 "Ctrl+�ɸ��� : PK ���"
		// 139 "PrintScreen : ��ũ���� ����"
		for(int i=0; i<19; ++i)
		{
			unicode::_strcpy(TextList[iTextNum], GlobalText[121+i]);
			TextListColor[iTextNum] = TEXT_COLOR_WHITE;
			TextBold[iTextNum] = false;
			iTextNum++;
		}

     	unicode::_sprintf(TextList[iTextNum],"\n");
		iTextNum++;

		RenderTipTextList(1, 1, iTextNum, 0, RT3_SORT_CENTER);
	}
	else if(m_iIndex == 1)
	{
		int iTextNum = 0;

		unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 140 "ä�ø�� Ű ����"
		unicode::_strcpy(TextList[iTextNum], GlobalText[140]);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE;
		TextBold[iTextNum] = true;
		iTextNum++;

     	unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 141 "Tab : �ӼӸ� ���̵� �Է�â ��ȯ"
		// 142 "ä�ñ� ������Ŭ�� : �ӼӸ� ID ����"
		// 143 "���� ����Ű : ä��â �����丮 ���"
		// 144 "PageUP, PageDN : ������ �� ����"
		// 145 "�۾տ� ~�� ���� : ��Ƽ���鿡�� ä��"
		// 146 "�۾տ� @�� ���� : �����鿡�� ä��"
		// 147 "�۾տ� @>�� ���� : �����鿡�� ����"
		// 148 "�۾տ� #�� ���� : ���� �������� ����"
		// 149 "���濡 ���콺�� �ø��� /�ŷ�: �ŷ�"
		// 150 "���濡 ���콺�� �ø��� /��Ƽ : ��Ƽ"
		// 151 "��帶���Ϳ� ���콺�� �ø��� /��� : ���"
		// 152 "/���� ���� : ����� ��û"
		// 153 "/�������̸� : ������ ����"
		// 154 "/�̵� �����̸� : ����� �����̵�"
		// 155 "/���� �ܾ�1 �ܾ�2 : �ܾ� �ִ� ä�ø� ����"
		// 156 "�Ʒ��� ���콺 Ŀ�� �̵� -> ä��â ������ư"
		for(int i=0;i<16; ++i)
		{
#ifdef CSK_MOD_MOVE_COMMAND_WINDOW
			if(i == 13)
			{
				continue;
			}
#endif // CSK_MOD_MOVE_COMMAND_WINDOW
			unicode::_strcpy(TextList[iTextNum], GlobalText[141+i]);
			TextListColor[iTextNum] = TEXT_COLOR_WHITE;
			TextBold[iTextNum] = false;
			iTextNum++;
		}

     	unicode::_sprintf(TextList[iTextNum],"\n");
		iTextNum++;

		RenderTipTextList(1, 1, iTextNum, 0, RT3_SORT_CENTER);
	}
	else if(m_iIndex == 2)
	{
		int iTextNum = 0;

		unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 2421 "<AM>                  <PM>"	
		unicode::_strcpy(TextList[iTextNum], GlobalText[2421]);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE; 
		TextBold[iTextNum] = true;
		iTextNum++;

		// 2422 "0:30  ȯ�����             12:30   ȯ�����"
		// 2423 "1:00  ī����ĳ��(PC)   13:00   ī����ĳ��"
		// 2424 "1:30  ����ĳ��          13:30   ����ĳ��"
		// 2425 "2:00  �Ǹ��Ǳ���          14:00   �Ǹ��Ǳ���"
		// 2426 "2:30  ȯ�����             14:30   ȯ�����"
		// 2427 "3:00  -                        15:00   ī����ĳ��(PC)"
		// 2428 "3:30  ����ĳ��          15:30   ����ĳ��"
		// 2429 "4:00  -                        16:00   ī����ĳ��"
		// 2430 "4:30  ȯ�����                 16:30   ȯ�����"
		// 2431 "5:00  �Ǹ��Ǳ���          17:00   �Ǹ��Ǳ���"
		// 2432 "5:30  ����ĳ��          17:30   ����ĳ��"
		// 2433 "6:00  -                        18:00   ī����ĳ��(PC)"
		// 2434 "6:30  -                        18:30   ȯ�����"
		// 2435 "7:00  -                        19:00   ī����ĳ��"
		// 2436 "7:30  ����ĳ��          19:30   ����ĳ��"
		// 2437 "8:00  �Ǹ��Ǳ���          20:00   �Ǹ��Ǳ���"
		// 2438 "8:30  ȯ�����                 20:30   ȯ�����"
		// 2439 "9:00  -                        21:00   ī����ĳ��"
		// 2440 "9:30  ����ĳ��          21:30   ����ĳ��"
		// 2441 "10:00 ī����ĳ��          22:00   ī����ĳ��(PC)"
		// 2442 "10:30 ī����ĳ��(PC)   22:30   ȯ�����"
		// 2443 "11:00 �Ǹ��Ǳ���          23:00   �Ǹ��Ǳ���"
		// 2444 "11:30 ����ĳ��          23:30   ����ĳ��"
		// 2445 "12:00 ī����ĳ��(PC)   24:00   ī����ĳ��"
		for(int i = 0; i<24; ++i)
		{
			unicode::_strcpy(TextList[iTextNum], GlobalText[2422+i]);
			TextListColor[iTextNum] = TEXT_COLOR_WHITE; 
			TextBold[iTextNum] = false;
			iTextNum++;
		}

		unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		RenderTipTextList(1, 1, iTextNum, 0, RT3_SORT_LEFT);
	}
	else if(m_iIndex == 3)
	{
		int iTextNum = 0;
		
		unicode::_sprintf(TextList[iTextNum], "\n");
		iTextNum++;

		// 2446 " << ī����ĳ�� ���巹�� >>     << �Ǹ��Ǳ��� ���巹�� >>"		
		unicode::_strcpy(TextList[iTextNum], GlobalText[2446]);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE; 
		TextBold[iTextNum] = true;
		iTextNum++;

// 		2447 "���   �Ϲ�      2��      ���   �Ϲ�       2��"     
// 		2448 " 1    15-49     15-29      1    15-130    10-110"
// 		2449 " 2    50-119    30-99      2    131-180   111-160"
// 		2450 " 3    120-179   100-159    3    181-230   161-210"
// 		2451 " 4    180-239   160-219    4    231-280   211-260"
// 		2452 " 5    240-299   220-279    5    281-330   261-310"
// 		2453 " 6    300-400   280-400    6    331-400   311-400"
// 		2454 " 7    ������    ������      7    ������    ������"
// 		2455 " << ����ĳ�� >>         << ȯ����� >>"
// 		2456 "���   �Ϲ�      2��      ���   �Ϲ�       2��" 
// 		2457 " 1    15-80     10-60          1    220-270"	
// 		2458 " 2    81-130    61-110        2    271-320"	
// 		2459 " 3    131-180   111-160      3    321-350"	
// 		2460 " 4    181-230   161-210      4    351-380"	
// 		2461 " 5    231-280   211-260      5    381-400"	
// 		2462 " 6    281-330   261-310      6    ������"			
// 		2463 " 7    331-400   311-400" 
// 		2464 " 8    ������    ������"

		for( int i=0; i<18; ++i )
		{
			unicode::_strcpy(TextList[iTextNum], GlobalText[2447+i]);
			if(i == 0 || i == 8 || i == 9)
			{
				TextListColor[iTextNum] = TEXT_COLOR_BLUE; 
				TextBold[iTextNum] = true;
				iTextNum++;
			}
			else
			{
				TextListColor[iTextNum] = TEXT_COLOR_WHITE; 
				TextBold[iTextNum] = false;
				iTextNum++;
			}
		}

		unicode::_sprintf(TextList[iTextNum],"\n");
		iTextNum++;

		RenderTipTextList(1, 1, iTextNum, 0, RT3_SORT_LEFT);
	}


	DisableAlphaBlend();
	return true;
}

float SEASON3B::CNewUIHelpWindow::GetLayerDepth()
{
#ifdef PJH_FIX_HELP_LAYER
	return 8.2f;
#else
	return 7.1f;
#endif //PJH_FIX_HELP_LAYER
}

float SEASON3B::CNewUIHelpWindow::GetKeyEventOrder()
{
	return 10.f;
}

void SEASON3B::CNewUIHelpWindow::OpenningProcess()
{
	m_iIndex = 0;
}

void SEASON3B::CNewUIHelpWindow::ClosingProcess()
{

}

void SEASON3B::CNewUIHelpWindow::AutoUpdateIndex()
{
#ifdef PSW_ADD_FOREIGN_HELPWINDOW
	if(++m_iIndex > 1) {
#else //PSW_ADD_FOREIGN_HELPWINDOW
	if(++m_iIndex > 3) {
#endif //PSW_ADD_FOREIGN_HELPWINDOW
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_HELP);
	}
}
