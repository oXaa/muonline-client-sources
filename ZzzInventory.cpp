///////////////////////////////////////////////////////////////////////////////
// â ���� �Լ�
// ���â, �ŷ�â, â��â, ��Ƽâ, ���â ���� �� ������ ���
//
// *** �Լ� ����: 3
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "UIManager.h"
#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "ZzzLodTerrain.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzTexture.h"
#include "ZzzInterface.h"
#include "ZzzInventory.h"
#include "ZzzAI.h"
#include "ZzzEffect.h"
#include "DSPlaySound.h"
#include "DIMouse.h"
#include "wsclientinline.h"
#include "ZzzScene.h"
#include "./Utilities/Log/ErrorReport.h"
#include "CSQuest.h"
#include "Local.h"
#include "zzzMixInventory.h"
#include "PersonalShopTitleImp.h"
#include "GOBoid.h"
#include "CSItemOption.h"
#include "CSChaosCastle.h"
#include "GMHellas.h"
#include "npcBreeder.h"
#ifdef PET_SYSTEM
#include "GIPetManager.h"
#endif// PET_SYSTEM
#include "CSParts.h"
#include "npcGateSwitch.h"
#include "GMBattleCastle.h"
#include "CComGem.h"
#include "PvPSystem.h"
#include "GMCrywolf1st.h"
#include "CDirection.h"
#include "ChangeRingManager.h"
#ifndef KJH_DEL_PC_ROOM_SYSTEM			// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
#include "PCRoomPoint.h"
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
#include "MixMgr.h"
#include "NewUICommonMessageBox.h"
#include "NewUICustomMessageBox.h"
#include "NewUIInventoryCtrl.h"
#include "GM3rdChangeUp.h"
#include "w_CursedTemple.h"
#ifdef SOCKET_SYSTEM
#include "SocketSystem.h"
#endif	// SOCKET_SYSTEM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
#include "PortalMgr.h"
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef PBG_ADD_ITEMRESIZE
#include "NewUISystem.h"
#endif //PBG_ADD_ITEMRESIZE

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
#include "ServerListManager.h"
#endif // KJH_ADD_SERVER_LIST_SYSTEM
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
#include <time.h>
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM


///////////////////////////////////////////
extern CUITextInputBox * g_pSingleTextInputBox;
extern int g_iChatInputType;
extern CUIGuildListBox * g_pGuildListBox;
////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  Global Variable
//////////////////////////////////////////////////////////////////////////

int			g_nTaxRate			= 0;

int			g_nChaosTaxRate		= 0;

char         g_GuildNotice[3][128];
GUILD_LIST_t GuildList[MAX_GUILDS];
int			 g_nGuildMemberCount = 0;
int			 GuildTotalScore = 0;
int			 GuildPlayerKey = 0;
int			 SelectMarkColor = 0;
MARK_t		 GuildMark[MAX_MARKS];

// ��Ƽ ����
PARTY_t Party[MAX_PARTYS];
int     PartyNumber = 0;
int     PartyKey = 0;

ITEM_t Items[MAX_ITEMS];
ITEM   PickItem;
ITEM   TargetItem;

ITEM Inventory         [MAX_INVENTORY];
ITEM ShopInventory     [MAX_SHOP_INVENTORY];
ITEM g_PersonalShopInven	[MAX_PERSONALSHOP_INVEN];
ITEM g_PersonalShopBackup	[MAX_PERSONALSHOP_INVEN];
bool g_bEnablePersonalShop = false;
int g_iPShopWndType = PSHOPWNDTYPE_NONE;
POINT g_ptPersonalShop = { 0, 0 };
int g_iPersonalShopMsgType = 0;
char g_szPersonalShopTitle[64] = { 0, };

CHARACTER g_PersonalShopSeller;
bool g_bIsTooltipOn = false;

int   CheckSkill = -1;
ITEM  *CheckInventory = NULL;

bool  EquipmentSuccess = false;
bool  CheckShop;
int   CheckX;
int   CheckY;
ITEM  *SrcInventory;
int   SrcInventoryIndex;
int   DstInventoryIndex;

int  AllRepairGold              = 0;     //  ��ü ���� ���.
int  StorageGoldFlag            = 0;

int ListCount                = 0;
int GuildListPage            = 0;

#ifndef YDG_ADD_NEW_DUEL_SYSTEM		// �����Ҷ� �����ؾ� ��
#ifdef DUEL_SYSTEM
bool g_bEnableDuel = false;
bool g_PetEnableDuel = true;	// LHJ - �����߿� ��ũ�ε��� ��ũ���Ǹ��� ������ ���� �Ǵ��ϴ� ����

int g_iDuelPlayerIndex = 0;
char g_szDuelPlayerID[24] = { 0, };
extern int g_iMyPlayerScore = 0;
extern int g_iDuelPlayerScore = 0;
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM	// �����Ҷ� �����ؾ� ��

int  g_bEventChipDialogEnable  = EVENT_NONE;       //  ����.     ( 1:����, 2:����, 3:���ȭ 2�ֳ� ���� �̺�Ʈ. ).
int  g_shEventChipCount        = 0;       //  ��������.
short g_shMutoNumber[3]        = { -1, -1, -1 };//  ���� ��ȣ.

bool g_bServerDivisionAccept   = false; //  �������� ����?
#ifdef SCRATCH_TICKET
char g_strGiftName[64];					//	���ȭ 2�ֳ� ��ǰ �̸�.
#endif

//  ������ ����.
bool RepairShop                = false; //  ������ ���ִ� ����.
int  RepairEnable              = 0;     //  ����.
int AskYesOrNo                  = 0;    //  Ȯ��â(1-�ȱ�, 2-ī���� ����, 3-�ŷ�Ȯ��, 4-��������, 5-����Ȯ��, 6-����Ȯ��)
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
char OkYesOrNo                  = -1;   //  Ȯ��â�� Ȯ��
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
BYTE OkYesOrNo                  = -1;   //  Ȯ��â�� Ȯ��
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

// â�� ��� ����
int g_iKeyPadEnable = 0;
WORD g_wStoragePassword = 0;
short	g_nKeyPadMapping[10];
char	g_lpszKeyPadInput[2][MAX_KEYPADINPUT + 1];

// ���Ż�� ���� ����
BYTE g_byItemUseType = 0;	//: ���� ��� �뵵 0x00 ���Ȼ��� 0x01 ���Ȱ���

static  const int DEFAULT_DEVILSQUARELEVEL[6][2] = { {15, 130}, { 131, 180}, { 181, 230}, {231, 280}, { 281, 330}, { 331, 99999} };
static  const int DARKCLASS_DEVILSQUARELEVEL[6][2] = { {15, 110}, { 111, 160}, { 161, 210}, {211, 260}, { 261, 310}, { 311, 99999} };
int g_iDevilSquareLevel[6][2];

// (0~5)�Ϲ� ��������, (6~9)(���˻�|��ũ�ε�) ��������
static  const int g_iChaosCastleLevel[12][2] = {  
						{ 15, 49 }, { 50, 119 }, { 120, 179 }, { 180, 239 }, { 240, 299 }, { 300, 999 }, 
                        { 15, 29 }, { 30,  99 }, { 100, 159 }, { 160, 219 }, { 220, 279 }, { 280, 999 }  
												};
//  �⺻ õ��(1000��)�̴�.
#ifdef CHINESE_PRICERISE
static  const int g_iChaosCastleZen[6] = {  25, 80, 200, 350, 600, 900 };
#else
static  const int g_iChaosCastleZen[6] = {  25, 80, 150, 250, 400, 650 };
#endif // CHINESE_PRICERISE

BYTE BuyItem[4];

//  ���� ����.
static  int iStateNum = 4;

//////////////////////////////////////////////////////////////////////////
//  Extern.
//////////////////////////////////////////////////////////////////////////
extern bool Teleport;

extern float g_fScreenRate_x;	// ��
extern float g_fScreenRate_y;

#ifdef _PVP_ADD_MOVE_SCROLL
extern CMurdererMove g_MurdererMove;
#endif	// _PVP_ADD_MOVE_SCROLL

///////////////////////////////////////////////////////////////////////////////
// ��ƿ��Ƽ.
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//  ĳ���� ������ ���� ���� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
int getLevelGeneration ( int level, unsigned int* color )
{
    int lvl;
    if(level>=300) //
    {
        lvl = 300;
	    *color = (255<<24)+(255<<16)+(153<<8)+(255);
    }
    else if(level>=200) //  ���.
    {
        lvl = 200;
	    *color = (255<<24)+(255<<16)+(230<<8)+(210);
    }
    else if(level>=100) //  ���.
    {
        lvl = 100;
        *color = (255<<24)+(24<<16)+(201<<8)+(0);
    }
    else if(level>=50)  //  ��Ȳ��.
    {
        lvl = 50;
        *color = (255<<24)+(0<<16)+(150<<8)+(255);
    }
    else                //  ������.
    {
        lvl = 10;
        *color = (255<<24)+(0<<16)+(0<<8)+(255);
    }
    return lvl;
}
///////////////////////////////////////////////////////////////////////////////
// ����â ������(����, ������, ��ų ����â�� ���)
///////////////////////////////////////////////////////////////////////////////

char TextList[30][100];
int  TextListColor[30];
int  TextBold[30];
SIZE Size[30];

int RenderTextList(int sx,int sy,int TextNum,int Tab, int iSort = RT3_SORT_CENTER)	// ��
{
	int TextWidth = 0;
	float fsy = sy;
	for(int i=0;i<TextNum;i++)
	{
     	if(TextBold[i])
		{
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			g_pRenderText->SetFont(g_hFont);
		}

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[i],lstrlen(TextList[i]),&Size[i]);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[i],lstrlen(TextList[i]),&Size[i]);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
      	
		if(TextWidth < Size[i].cx)
		{
			TextWidth = Size[i].cx;
		}
	}

	if(Tab == 0)
	{
		sx -= (TextWidth+Tab)*640/WindowWidth/2;
	}

#ifdef _VS2008PORTING
	for(int i=0;i<TextNum;i++)
#else // _VS2008PORTING
	for(i=0;i<TextNum;i++)
#endif // _VS2008PORTING
	{
		g_pRenderText->SetTextColor(0xffffffff);
		
		switch(TextListColor[i])
		{
		case TEXT_COLOR_WHITE:
		case TEXT_COLOR_DARKRED:
        case TEXT_COLOR_DARKBLUE:
        case TEXT_COLOR_DARKYELLOW:
         	glColor3f(1.f,1.f,1.f);
			break;
		case TEXT_COLOR_BLUE:
            glColor3f(0.5f,0.7f,1.f);
			break;
        case TEXT_COLOR_GRAY:
			glColor3f(0.4f,0.4f,0.4f);
            break;
		case TEXT_COLOR_GREEN_BLUE:
			glColor3f(1.f,1.f,1.f);
			break;
		case TEXT_COLOR_RED:
            glColor3f(1.f,0.2f,0.1f);
			break;
		case TEXT_COLOR_YELLOW:
            glColor3f(1.f,0.8f,0.1f);
			break;
		case TEXT_COLOR_GREEN:
            glColor3f(0.1f,1.f,0.5f);
			break;
        case TEXT_COLOR_PURPLE:
            glColor3f(1.f,0.1f,1.f);
            break;
		}
		if ( TEXT_COLOR_DARKRED == TextListColor[i])
		{
			g_pRenderText->SetBgColor(160, 0, 0, 255);
		}
		else if ( TEXT_COLOR_DARKBLUE==TextListColor[i])
		{
			g_pRenderText->SetBgColor(0, 0, 160, 255);
		}
		else if ( TEXT_COLOR_DARKYELLOW==TextListColor[i])
		{
			g_pRenderText->SetBgColor(160, 102, 0, 255);
		}
        else if ( TEXT_COLOR_GREEN_BLUE==TextListColor[i])
        {
			g_pRenderText->SetTextColor(0, 255, 0, 255);
			g_pRenderText->SetBgColor(60, 60, 200, 255);
        }
		else
		{
			g_pRenderText->SetBgColor(0, 0, 0, 0);
		}

     	if(TextBold[i])
		{
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			g_pRenderText->SetFont(g_hFont);
		}
		SIZE TextSize;
		g_pRenderText->RenderText(sx, fsy, TextList[i], TextWidth+Tab, 0, iSort, &TextSize);
		fsy += TextSize.cy;
	}
	return TextWidth+Tab;
}

void RenderTipTextList(const int sx, const int sy, int TextNum, int Tab, int iSort, int iRenderPoint, BOOL bUseBG)
{
	// â�ʺ�� ����
	SIZE TextSize = {0, 0};
	int TextLine = 0; int EmptyLine = 0;
	float fWidth = 0; float fHeight = 0;
	for(int i = 0; i < TextNum; ++i)
	{
		if (TextList[i][0] == '\0')
		{
			TextNum = i;
			break;
		}

		if(TextBold[i])
		{
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			g_pRenderText->SetFont(g_hFont);
		}

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[i], lstrlen(TextList[i]), &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[i], lstrlen(TextList[i]), &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		
		if (fWidth < TextSize.cx) 
			fWidth = TextSize.cx;

		if (TextList[i][0] == '\n')
		{
			++EmptyLine;
		}
		else
		{
			++TextLine;
		}
	}

	fHeight = TextSize.cy * TextLine + TextSize.cy / 2.0f * EmptyLine;
	fHeight /= g_fScreenRate_y / 1.1f;
	EnableAlphaTest();
	fWidth /= g_fScreenRate_x;
	if (Tab > 0) 
		fWidth = Tab / g_fScreenRate_x * 2;
	fWidth += 4;
	int iPos_x = sx - fWidth / 2;
	if(iPos_x < 0) iPos_x = 0;
	if(iPos_x + fWidth > (int)WindowWidth / g_fScreenRate_x)	// ȭ�� ������ ���� �� ó��
	{
		iPos_x = ((int)WindowWidth) / g_fScreenRate_x - fWidth - 1;
	}
	
	float fsx = iPos_x + 1;
	float fsy = 0.f;
	
	switch( iRenderPoint )
	{
	case STRP_BOTTOMCENTER:
		{
			fsy = sy - fHeight;
		}break;
	default:
		{
			fsy = sy;
		}break;
	}

	if (bUseBG == TRUE && TextNum > 0)
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		RenderColor ((float)iPos_x-1, fsy - 1, (float)fWidth + 1, (float)1);	// ��
		RenderColor ((float)iPos_x-1, fsy - 1, (float)1, (float)fHeight + 1);	// ��
		RenderColor ((float)iPos_x-1 + fWidth + 1, (float)fsy - 1, (float)1, (float)fHeight + 1);	
		RenderColor ((float)iPos_x-1, fsy - 1 + fHeight + 1, (float)fWidth + 2, (float)1);

		glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
		RenderColor ((float)iPos_x, fsy, (float)fWidth, (float)fHeight);
		glEnable(GL_TEXTURE_2D);
	}

#ifdef _VS2008PORTING
	for(int i=0;i<TextNum;i++)
#else // _VS2008PORTING
	for(i=0;i<TextNum;i++)
#endif // _VS2008PORTING
	{
     	if(TextBold[i])
		{
			g_pRenderText->SetFont(g_hFontBold);
		}
		else
		{
			g_pRenderText->SetFont(g_hFont);
		}
		
		float fHeight = 0;
		if(TextList[i][0] == 0x0a || (TextList[i][0] == ' ' && TextList[i][1] == 0x00))
		{
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[i], lstrlen(TextList[i]), &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[i], lstrlen(TextList[i]), &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			fHeight = (float)TextSize.cy / g_fScreenRate_y / (TextList[i][0] == 0x0a ? 2.0f : 1.0f);
		}
		else
		{
		g_pRenderText->SetTextColor(0xffffffff);
			switch(TextListColor[i])
			{
			case TEXT_COLOR_WHITE:
			case TEXT_COLOR_DARKRED:
            case TEXT_COLOR_DARKBLUE:
            case TEXT_COLOR_DARKYELLOW:
         		glColor3f(1.f,1.f,1.f);
				break;
			case TEXT_COLOR_BLUE:
				glColor3f(0.5f,0.7f,1.f);
				break;
            case TEXT_COLOR_GRAY:
				glColor3f(0.4f,0.4f,0.4f);
                break;
            case TEXT_COLOR_GREEN_BLUE:
				glColor3f(1.f,1.f,1.f);
				break;
            case TEXT_COLOR_RED:
				glColor3f(1.f,0.2f,0.1f);
				break;
			case TEXT_COLOR_YELLOW:
				glColor3f(1.f,0.8f,0.1f);
				break;
			case TEXT_COLOR_GREEN:
				glColor3f(0.1f,1.f,0.5f);
				break;
            case TEXT_COLOR_PURPLE:
                glColor3f(1.f,0.1f,1.f);
                break;
			case TEXT_COLOR_REDPURPLE:
				glColor3f(0.8f,0.5f,0.8f);
				break;
#ifdef SOCKET_SYSTEM
			case TEXT_COLOR_VIOLET:
				glColor3f(0.7f,0.4f,1.0f);
				break;
#endif	// SOCKET_SYSTEM
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
			case TEXT_COLOR_ORANGE:
				glColor3f(0.9f, 0.42f, 0.04f );
				break;
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM

				
			}
			if ( TEXT_COLOR_DARKRED == TextListColor[i])
			{
				g_pRenderText->SetBgColor(160, 0, 0, 255);
			}
		    else if ( TEXT_COLOR_DARKBLUE==TextListColor[i])
		    {
				g_pRenderText->SetBgColor(0, 0, 160, 255);
		    }
			else if ( TEXT_COLOR_DARKYELLOW==TextListColor[i])
			{
				g_pRenderText->SetBgColor(160, 102, 0, 255);
			}
            else if ( TEXT_COLOR_GREEN_BLUE==TextListColor[i])
            {
				g_pRenderText->SetBgColor(60, 60, 200, 255);
				g_pRenderText->SetTextColor(0, 255, 0, 255);
            }
			else
			{
				g_pRenderText->SetBgColor(0);
			}
			SIZE TextSize;
			g_pRenderText->RenderText(fsx,fsy,TextList[i],(fWidth-2),0,iSort, &TextSize);	// ��
			fHeight = TextSize.cy;
		}
		fsy += fHeight * 1.1f;
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	DisableAlphaBlend();
}

bool IsCanUseItem()
{
	if(	g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_TRADE)
		)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool IsCanTrade()
{
	if( g_pUIManager->IsOpen(INTERFACE_PERSONALSHOPSALE) || g_pUIManager->IsOpen(INTERFACE_PERSONALSHOPPURCHASE) )
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// ������ ����â���� ����� �� �ִ� Ŭ���� ã�Ƴ��� �Լ�
///////////////////////////////////////////////////////////////////////////////

int TextNum = 0;
int SkipNum = 0;

bool IsRequireClassRenderItem(const short sType)
{
	if(
		sType == ITEM_HELPER+19		// 0: ��õ���� ����������, 1: ��õ���� �����, 2: ��õ���� ���뼮��
		|| sType == ITEM_HELPER+29	// �������� ���ʼ�Ʈ.
		|| sType == ITEM_WING+26	// �ź��� ����
		|| (sType >= ITEM_WING+30 && sType <= ITEM_WING+31)	// ���� ����
		|| (sType >= ITEM_HELPER+43 && sType <= ITEM_HELPER+45)	// ���� ����
		|| sType == ITEM_HELPER+10	// ���Ź���
		|| (sType >= ITEM_HELPER+39 && sType <= ITEM_HELPER+42)	// ���Ź�����
		|| sType == ITEM_HELPER+37
		|| sType == ITEM_WING+15	// ȥ���� ����
		|| sType == ITEM_WING+32	// ���������ǻ���
		|| sType == ITEM_WING+33	// �ʷϸ����ǻ���
		|| sType == ITEM_WING+34	// �Ķ������ǻ���
		)
	{
		return false;
	}

	if(
#ifdef CSK_LUCKY_SEAL
		(sType >= ITEM_HELPER+43 && sType <= ITEM_HELPER+45)
#endif //CSK_LUCKY_SEAL	
#ifdef CSK_FREE_TICKET
		|| (sType >= ITEM_HELPER+46 && sType <= ITEM_HELPER+48)
#endif // CSK_FREE_TICKET
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
		|| (sType >= ITEM_HELPER+125 && sType <= ITEM_HELPER+127)
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef CSK_CHAOS_CARD
		|| (sType == ITEM_POTION+54)
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
		|| (sType >= ITEM_POTION+58 && sType <= ITEM_POTION+62)
#endif // CSK_RARE_ITEM
#ifdef CSK_LUCKY_CHARM
		|| (sType == ITEM_POTION+53)
#endif //CSK_LUCKY_CHARM
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
		|| (sType >= ITEM_POTION+70 && sType <= ITEM_POTION+71)
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
		|| (sType >= ITEM_POTION+72 && sType <= ITEM_POTION+77)
#endif //PSW_SCROLL_ITEM
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// ���� ���� 100% ���� ����
		|| (sType >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN 
			&& sType <= ITEM_TYPE_CHARM_MIXWING+EWS_END)
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef PSW_SEAL_ITEM               // �̵� ����
		|| (sType == ITEM_HELPER+59)
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
		|| ( sType >= ITEM_HELPER+54 && sType <= ITEM_HELPER+58)
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
		||(sType >= ITEM_POTION+78 && sType <= ITEM_POTION+82)
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
		|| (sType == ITEM_HELPER+60)
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET // ȯ���� ��� ���� �����
		|| (sType == ITEM_HELPER+61)
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_CHARACTER_CARD         // ĳ���� ī��
		|| (sType == ITEM_POTION+91)
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_ELITE_ITEM         // ����Ʈ �߰� ġ�� ����
		|| (sType == ITEM_POTION+94)
#endif //PSW_NEW_ELITE_ITEM
#ifdef PSW_NEW_CHAOS_CARD
		|| (sType >= ITEM_POTION+92 && sType <= ITEM_POTION+93) // ī���� ī�� ���, ����
		|| (sType == ITEM_POTION+95)							// ī���� ī�� �̴�
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_ADD_PC4_SEALITEM
		|| ( sType >= ITEM_HELPER+62 && sType <= ITEM_HELPER+63 )
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
		|| ( sType >= ITEM_POTION+97 && sType <= ITEM_POTION+98 )
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
		|| (sType == ITEM_POTION+96)
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
		|| ( sType == ITEM_HELPER+64 || sType == ITEM_HELPER+65 )
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDK_ADD_RUDOLPH_PET
		|| ( sType == ITEM_HELPER+67 )
#endif //LDK_ADD_RUDOLPH_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
		|| ( sType == ITEM_HELPER+68 )
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
		|| ( sType == ITEM_HELPER+76 )
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| ( sType == ITEM_HELPER+122 )	// ���̷��� ���Ź���
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
		|| ( sType == ITEM_HELPER+69 )	// ��Ȱ�� ����
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
		|| ( sType == ITEM_HELPER+70 )	// �̵��� ����
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
		|| ( sType == ITEM_HELPER+71 || sType == ITEM_HELPER+72 || sType == ITEM_HELPER+73 || sType == ITEM_HELPER+74 ||sType == ITEM_HELPER+75 )	// �׺� ������
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef PJH_ADD_PANDA_PET
		|| ( sType == ITEM_HELPER+80 )
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
		|| ( sType == ITEM_HELPER+106 )
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef ASG_ADD_CS6_GUARD_CHARM
		|| sType == ITEM_HELPER+81	// ��ȣ�Ǻ���
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
		|| sType == ITEM_HELPER+82	// �����ۺ�ȣ����
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		|| sType == ITEM_HELPER+93	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		|| sType == ITEM_HELPER+94	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		|| sType == ITEM_HELPER+121	// ī�����ɽ� ���������
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12	// ��;�����Ƽ�� 7-12
		|| (sType >= ITEM_POTION+145 && sType <= ITEM_POTION+150)
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| g_pMyInventory->IsInvenItem(sType)
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
		|| (sType==ITEM_POTION+133)		// ����Ʈ SDȸ�� ����
#endif // YDG_ADD_CS7_ELITE_SD_POTION
#endif // KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
		)
	{
		return false;
	}	

	return true;
}

void RequireClass(ITEM_ATTRIBUTE* pItem)
{
	if(pItem == NULL)
		return;

	BYTE byFirstClass = GetBaseClass(Hero->Class);
	BYTE byStepClass = GetStepClass(Hero->Class);

	int iTextColor = 0;

	TextListColor[TextNum + 2] = TextListColor[TextNum + 3] = TEXT_COLOR_WHITE;
	sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

	// ��� Ŭ������ ��밡���ϸ� ����ģ��.
	int iCount = 0;
	for(int i=0; i<MAX_CLASS; ++i)
	{
		if(pItem->RequireClass[i] == 1)
		{
			iCount++;
		}
	}
	if(iCount == MAX_CLASS)
		return;

	// ���Ŭ���� �ؽ�Ʈ �Է�
#ifdef _VS2008PORTING
	for(int i=0; i<MAX_CLASS; ++i)
#else // _VS2008PORTING
	for(i=0; i<MAX_CLASS; ++i)
#endif // _VS2008PORTING
	{
		BYTE byRequireClass = pItem->RequireClass[i];

		if(byRequireClass == 0)
			continue;

		if(i == byFirstClass && byRequireClass <= byStepClass)
		{
			iTextColor = TEXT_COLOR_WHITE;
		}
		else
		{
			iTextColor = TEXT_COLOR_DARKRED;
		}

		switch(i)
		{
		case CLASS_WIZARD:
			{
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 20 "�渶����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[20]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 2)
				{
					// 61 "%s ��� ����"
					// 25 "�ҿ︶����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[25]);
					TextListColor[TextNum] = iTextColor;	
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1669 "�׷��帶����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1669]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;
		case CLASS_KNIGHT:
			{
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 21 "����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[21]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 2)
				{
					// 61 "%s ��� ����"
					// 26 "���̵峪��Ʈ"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[26]);
					TextListColor[TextNum] = iTextColor;	
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1668 "���̵帶����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1668]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;
		case CLASS_ELF:
			{	
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 22 "����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[22]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 2)
				{
					// 61 "%s ��� ����"
					// 27 "�����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[27]);
					TextListColor[TextNum] = iTextColor;	
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1670 "���̿���"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1670]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;
		case CLASS_DARK:
			{	
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 23 "���˻�"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[23]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1671 "��󸶽���"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1671]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;	
		case CLASS_DARK_LORD:
			{	
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 24 "��ũ�ε�"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[24]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1672 "�ε忥�۷�"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1672]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;
		case CLASS_SUMMONER:
			{	
				if(byRequireClass == 1)
				{
					// 61 "%s ��� ����"
					// 1687 "��ȯ����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1687]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass == 2)
				{
					// 61 "%s ��� ����"
					// 1688 "���𼭸ӳ�"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1688]);
					TextListColor[TextNum] = iTextColor;	
				}
				else if(byRequireClass == 3)
				{
					// 61 "%s ��� ����"
					// 1689 "���Ǹ�����"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[1689]);
					TextListColor[TextNum] = iTextColor;	
				}

				TextBold[TextNum] = false;	TextNum++;
			}
			break;
#ifdef PBG_ADD_NEWCHAR_MONK
		case CLASS_RAGEFIGHTER:
			{
				if(byRequireClass==1)
				{
					// 61 "%s ��� ����"	3150 "������������"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[3150]);
					TextListColor[TextNum] = iTextColor;
				}
				else if(byRequireClass==3)
				{
					// 61 "%s ��� ����"	3151 "���ó���Ʈ"
					sprintf(TextList[TextNum], GlobalText[61], GlobalText[3151]);
					TextListColor[TextNum] = iTextColor;	
				}
				TextBold[TextNum] = false;	TextNum++;
			}
			break;
#endif //PBG_ADD_NEWCHAR_MONK
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
// ������ 14 15 ���� �߰�(09.12.2)
const int iMaxLevel = 15;	// �ִ� ������ ������
#else //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
const int iMaxLevel = 13;	// �ִ� ������ ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO

const int iMaxColumn = 17;	// �ִ� ���� �׸�

int g_iCurrentItem = -1;
int g_iItemInfo[iMaxLevel + 1][iMaxColumn];	// ������ ���� �̸� ���

void RenderHelpLine(int iColumnType, const char * pPrintStyle, int & TabSpace, const char * pGapText, int Pos_y, int iType)	// ��
{
    int iCurrMaxLevel = iMaxLevel;

    if ( iType==5 ) //  ����.
        iCurrMaxLevel = 0;

	for (int Level = 0; Level <= iCurrMaxLevel; ++Level)
	{
		sprintf(TextList[TextNum], pPrintStyle, g_iItemInfo[Level][iColumnType]);
		if (g_iItemInfo[Level][_COLUMN_TYPE_CAN_EQUIP] == TRUE)
		{
			TextListColor[Level] = TEXT_COLOR_WHITE;
		}
		else
		{
			TextListColor[Level] = TEXT_COLOR_RED;
		}
		TextBold[Level] = false;
		++TextNum;
	}

	SIZE TextSize;
	RenderTipTextList(TabSpace, Pos_y, TextNum, 0, RT3_SORT_CENTER, FALSE);

	if (pGapText == NULL)
	{
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[TextNum - 1], lstrlen(TextList[TextNum - 1]), &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[TextNum - 1], lstrlen(TextList[TextNum - 1]), &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	}
	else 
	{
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), pGapText, lstrlen(pGapText), &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), pGapText, lstrlen(pGapText), &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	}
	TabSpace += int(TextSize.cx / g_fScreenRate_x);
#ifdef CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
	if(iType == 6)	// ��ȯ���� ���̸�
	{
		TabSpace += 5;	
	}
#endif // CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
	TextNum -= iCurrMaxLevel + 1;
}

void RenderHelpCategory(int iColumnType, int Pos_x, int Pos_y)	// �� ���� �׸� ���
{
	const char* pText = NULL;

	switch(iColumnType)
	{
	case _COLUMN_TYPE_LEVEL:
		pText = GlobalText[161];//" ����";
		break;
	case _COLUMN_TYPE_ATTMIN: case _COLUMN_TYPE_ATTMAX:
		pText = GlobalText[162];//" ���ݷ�";
		break;
	case _COLUMN_TYPE_MAGIC:
		pText = GlobalText[163];//"���� ";
		break;
#ifdef CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
	case _COLUMN_TYPE_CURSE:
		pText = GlobalText[1144];	// 1144 "���ַ�"
		break;
#endif // CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
    case _COLUMN_TYPE_PET_ATTACK:
		pText = GlobalText[1239];//"�ְ��ݷ� ";
        break;
	case _COLUMN_TYPE_DEFENCE:
		pText = GlobalText[164];//"���� ";
		break;
	case _COLUMN_TYPE_DEFRATE:
		pText = GlobalText[165];//"�����";
		break;
	case _COLUMN_TYPE_REQSTR:
		pText = GlobalText[166];//"�� ";
		break;
	case _COLUMN_TYPE_REQDEX:
		pText = GlobalText[167];//"��ø";
		break;
	case _COLUMN_TYPE_REQENG:
		pText = GlobalText[168];//"������";
		break;
	case _COLUMN_TYPE_REQCHA:
		pText = GlobalText[1900];//"���";
		break;
	case _COLUMN_TYPE_REQVIT:
		pText = GlobalText[169];//"ü��";
		break;
	case _COLUMN_TYPE_REQNLV:
		pText = GlobalText[1931];//"�ʿ䷹��";
		break;
	default:
		break;
	}
	sprintf(TextList[TextNum], pText);
	TextListColor[TextNum] = TEXT_COLOR_BLUE;
	TextNum++;
	RenderTipTextList(Pos_x, Pos_y, TextNum, 0, RT3_SORT_RIGHT, FALSE);
	TextNum = 0;
}

void ComputeItemInfo(int iHelpItem)	// ��
{
	if (g_iCurrentItem == iHelpItem) 
		return;
	else 
		g_iCurrentItem = iHelpItem;

	ITEM_ATTRIBUTE *p = &ItemAttribute[ItemHelp];

	for(int Level = 0; Level <= iMaxLevel; Level++)
	{
		int RequireStrength = 0;
		int RequireDexterity = 0;
		int RequireEnergy = 0;
		int RequireCharisma = 0;
		int RequireVitality = 0;
		int RequireLevel = 0;
		int DamageMin = p->DamageMin;	// �ּҰ��ݷ�
		int DamageMax = p->DamageMax;	// �ִ���ݷ�
		int Defense   = p->Defense;		// ����
		int Magic	  = p->MagicPower;	// ����
		int Blocking  = p->SuccessfulBlocking;	// �����

		if(DamageMin > 0)
        {
            DamageMin += (min(9,Level)*3);	// ~ +9������
			switch(Level - 9)
			{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 6: DamageMin += 9;	// +15 ������
			case 5: DamageMin += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 4: DamageMin += 7;	// +13 ������
			case 3: DamageMin += 6;	// +12 ������
			case 2: DamageMin += 5;	// +11 ������
			case 1: DamageMin += 4;	// +10 ������
			default: break;
			};
        }
		if(DamageMax > 0)
        {
            DamageMax += (min(9,Level)*3);	// ~ +9������
			switch(Level - 9)
			{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 6: DamageMax += 9;	// +15 ������
			case 5: DamageMax += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 4: DamageMax += 7;	// +13 ������
			case 3: DamageMax += 6;	// +12 ������
			case 2: DamageMax += 5;	// +11 ������
			case 1: DamageMax += 4;	// +10 ������
			default: break;
			};
        }

		if(Magic > 0)
		{
			Magic += (min(9,Level)*3);	// ~ +9������
			switch(Level - 9)
			{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 6: Magic += 9;		// +15 ������
			case 5: Magic += 8;		// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 4: Magic += 7;	    // +13 ������
			case 3: Magic += 6;		// +12 ������
			case 2: Magic += 5;		// +11 ������
			case 1: Magic += 4;		// +10 ������
			default: break;
			};
			Magic /= 2;
            //  ���Ͱ� �ƴ� ��쿡��.
#ifdef CSK_FIX_EPSOLUTESEPTER
			if(IsCepterItem(ItemHelp) == false)
#else // CSK_FIX_EPSOLUTESEPTER
			if ( ItemHelp < ITEM_MACE+8 || ItemHelp > ITEM_MACE+15 )
#endif // CSK_FIX_EPSOLUTESEPTER
            {
    			Magic += Level*2;
			}
		}

        if(Defense > 0)
		{
			if(ItemHelp>=ITEM_SHIELD && ItemHelp<ITEM_SHIELD+MAX_ITEM_INDEX)
			{
				Defense += Level;
			}
			else
            {
                Defense     += (min(9,Level)*3);	// ~ +9������
				switch(Level - 9)
				{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 6: Defense += 9;	// +15 ������
				case 5: Defense += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 4: Defense += 7;	// +13 ������
				case 3: Defense += 6;	// +12 ������
				case 2: Defense += 5;	// +11 ������
				case 1: Defense += 4;	// +10 ������
				default: break;
				};
            }
		}
		if(Blocking  > 0)
		{
            Blocking     += (min(9,Level)*3);	// ~ +9������
			switch(Level - 9)
			{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 6: Blocking += 9;	// +15 ������
			case 5: Blocking += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
			case 4: Blocking += 7;	// +13 ������
			case 3: Blocking += 6;	// +12 ������
			case 2: Blocking += 5;	// +11 ������
			case 1: Blocking += 4;	// +10 ������
			default: break;
			};
		}

		if(p->RequireLevel)
		{
			RequireLevel     = p->RequireLevel;
		}
		else
		{
			RequireLevel  = 0;
		}

		if(p->RequireStrength)
		{
			RequireStrength  = 20+p->RequireStrength *(p->Level+Level*3)*3/100;
		}
		else
		{
			RequireStrength  = 0;
		}

		if(p->RequireDexterity)	RequireDexterity = 20+p->RequireDexterity*(p->Level+Level*3)*3/100;
		else RequireDexterity = 0;

		if(p->RequireVitality)	RequireVitality  = 20+p->RequireVitality *(p->Level+Level*3)*3/100;
		else RequireVitality  = 0;

		if(p->RequireEnergy)
		{
			if (ItemHelp >= ITEM_STAFF+21 && ItemHelp <= ITEM_STAFF+29)	// ��ȯ���� ���� �䱸�������� ����
			{
				RequireEnergy    = 20+p->RequireEnergy   *(p->Level+Level*1)*3/100;
			}
			else
// p->RequireLevel : ������ ���� �䱸ġ
// p->RequireEnergy : ������ ������ �䱸ġ
// ip->RequireEnergy : ���� ������ �䱸ġ (����Ȱ�)
#ifdef KJH_FIX_LEARN_SKILL_ITEM_REQUIRE_STAT_CALC
		// ���� �䱸ġ�� 0�̸� ���� ����� ����.
		// skill.txt ���� ���� ������ �����䱸ġ�� ������ ���� ���, ����ó�� ��.
		// �䱸ġ ����� �ڵ忡 �� �־�� �ϴ��� �ǹ�.. ��ġ��!!!!
		if((p->RequireLevel > 0) && (ItemHelp >= ITEM_ETC && ItemHelp < ITEM_ETC+MAX_ITEM_INDEX) )	// ����
		{
			RequireEnergy = 20+(p->RequireEnergy)*(p->RequireLevel)*4/100;
		}
		else
#endif // KJH_FIX_LEARN_SKILL_ITEM_REQUIRE_STAT_CALC
			{
				RequireEnergy    = 20+p->RequireEnergy   *(p->Level+Level*3)*4/100;
			}
		}
		else
		{
			RequireEnergy    = 0;
		}

		if(p->RequireCharisma)	RequireCharisma  = 20+p->RequireCharisma *(p->Level+Level*3)*3/100;
		else RequireCharisma  = 0;

		g_iItemInfo[Level][_COLUMN_TYPE_LEVEL] = Level;
		g_iItemInfo[Level][_COLUMN_TYPE_ATTMIN] = DamageMin;
		g_iItemInfo[Level][_COLUMN_TYPE_ATTMAX] = DamageMax;
		
#ifdef CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
		// ��ȯ���� ���� ���ַ� Į���� ���� �Է��Ͽ��� �Ѵ�.
		if (ItemHelp >= ITEM_STAFF+21 && ItemHelp <= ITEM_STAFF+29)
		{
			g_iItemInfo[Level][_COLUMN_TYPE_CURSE] = Magic;
		}
		else
		{
			g_iItemInfo[Level][_COLUMN_TYPE_MAGIC] = Magic;
		}
#else // CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
		g_iItemInfo[Level][_COLUMN_TYPE_MAGIC] = Magic;
#endif // CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
		
		g_iItemInfo[Level][_COLUMN_TYPE_PET_ATTACK] = Magic;
		g_iItemInfo[Level][_COLUMN_TYPE_DEFENCE] = Defense;
		g_iItemInfo[Level][_COLUMN_TYPE_DEFRATE] = Blocking;
		g_iItemInfo[Level][_COLUMN_TYPE_REQSTR] = RequireStrength;
		g_iItemInfo[Level][_COLUMN_TYPE_REQDEX] = RequireDexterity;
		g_iItemInfo[Level][_COLUMN_TYPE_REQENG] = RequireEnergy;
		g_iItemInfo[Level][_COLUMN_TYPE_REQCHA] = RequireCharisma;
		g_iItemInfo[Level][_COLUMN_TYPE_REQVIT] = RequireVitality;
		g_iItemInfo[Level][_COLUMN_TYPE_REQNLV] = RequireLevel;

        //  �������� �����ϰ��.
#ifdef CSK_FIX_EPSOLUTESEPTER
		if ( IsCepterItem(ItemHelp) == true )
#else // CSK_FIX_EPSOLUTESEPTER
		if ( ItemHelp>=ITEM_MACE+8 && ItemHelp<=ITEM_MACE+15 )
#endif // CSK_FIX_EPSOLUTESEPTER	
        {
    		g_iItemInfo[Level][_COLUMN_TYPE_MAGIC] = 0;
        }
        else
        {
    		g_iItemInfo[Level][_COLUMN_TYPE_PET_ATTACK] = 0;
        }

		WORD Strength, Dexterity, Energy, Vitality, Charisma;

		Strength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
		Dexterity= CharacterAttribute->Dexterity+ CharacterAttribute->AddDexterity;
		Energy	 = CharacterAttribute->Energy   + CharacterAttribute->AddEnergy;
		Vitality	 = CharacterAttribute->Vitality   + CharacterAttribute->AddVitality;
		Charisma	 = CharacterAttribute->Charisma   + CharacterAttribute->AddCharisma;

		if(RequireStrength  <=Strength
			&&	RequireDexterity<=Dexterity
			&&	RequireEnergy   <=Energy
			&&	RequireVitality <= Vitality
			&&	RequireCharisma <= Charisma
			&&	RequireLevel <= CharacterAttribute->Level )
			g_iItemInfo[Level][_COLUMN_TYPE_CAN_EQUIP] = TRUE;
		else
			g_iItemInfo[Level][_COLUMN_TYPE_CAN_EQUIP] = FALSE;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ����â �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////
unsigned int getGoldColor ( DWORD Gold )
{
    if ( Gold>=10000000 )        //  ����.
    {
        return  (255<<24)+(0<<16)+(0<<8)+(255);
    }
    else if ( Gold>=1000000 )    //  ��Ȳ.
    {
        return  (255<<24)+(0<<16)+(150<<8)+(255);
    }
    else if( Gold>=100000 )      //  ���.
    {
        return  (255<<24)+(24<<16)+(201<<8)+(0);
    }

    return  (255<<24)+(150<<16)+(220<<8)+(255);
}

#ifdef KJH_MOD_BTS191_GOLD_FLOATING_NUMBER
void ConvertGold(double dGold, unicode::t_char* szText, int iDecimals /*= 0*/)
{
	unicode::t_char szTemp[256];
	int iCipherCnt=0;
	DWORD dwValueTemp = (DWORD)dGold;
	
	// �����ڸ�
	while( dwValueTemp/1000 > 0 )
	{
		iCipherCnt = iCipherCnt + 3;
		dwValueTemp = dwValueTemp/1000;
	}

	unicode::_sprintf(szText, "%d", dwValueTemp);

	while( iCipherCnt > 0 )
	{
		dwValueTemp = (DWORD)dGold;
#ifdef _VS2008PORTING
		dwValueTemp = (dwValueTemp%(int)pow(10.f,(float)iCipherCnt))/(int)pow(10.f,(float)(iCipherCnt-3));
#else // _VS2008PORTING
		dwValueTemp = (dwValueTemp%(int)pow(10,iCipherCnt))/(int)pow(10,(iCipherCnt-3));
#endif // _VS2008PORTING
		unicode::_sprintf(szTemp, ",%03d", dwValueTemp);
		strcat(szText, szTemp);
		iCipherCnt = iCipherCnt - 3;
	}

	// �Ҽ��� �Ʒ� �ڸ� 
	if( iDecimals > 0 )
	{
#ifdef _VS2008PORTING
		dwValueTemp = (int)(dGold*pow(10.f,(float)iDecimals))%(int)pow(10.f, (float)iDecimals);
#else // _VS2008PORTING
		dwValueTemp = (int)(dGold*pow(10,iDecimals))%(int)pow(10, iDecimals);
#endif // _VS2008PORTING
		unicode::_sprintf(szTemp, ".%d", dwValueTemp);
		strcat(szText, szTemp);
	}
}
#else // KJH_MOD_BTS191_GOLD_FLOATING_NUMBER
void ConvertGold(DWORD Gold,unicode::t_char* Text)
{
	int Gold1 = Gold%1000;
	int Gold2 = Gold%1000000/1000;
	int Gold3 = Gold%1000000000/1000000;
	int Gold4 = Gold/1000000000;
	if(Gold >= 1000000000)
		unicode::_sprintf(Text,"%d,%03d,%03d,%03d",Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000)
		unicode::_sprintf(Text,"%d,%03d,%03d",Gold3,Gold2,Gold1);
	else if(Gold >= 1000)
		unicode::_sprintf(Text,"%d,%03d",Gold2,Gold1);
	else 
		unicode::_sprintf(Text,"%d",Gold1);
}
#endif // KJH_MOD_BTS191_GOLD_FLOATING_NUMBER

#ifdef YDG_FIX_CATLE_MONEY_INT64_TYPE_CRASH
void ConvertGold64(__int64 Gold,unicode::t_char* Text)
{
	int Gold1 = Gold%1000;
	int Gold2 = Gold%1000000/1000;
	int Gold3 = Gold%1000000000/1000000;
	int Gold4 = Gold%1000000000000/1000000000;
	int Gold5 = Gold%1000000000000000/1000000000000;
	int Gold6 = Gold/1000000000000000;
	if(Gold >= 1000000000000000)
		unicode::_sprintf(Text,"%d,%03d,%03d,%03d,%03d,%03d",Gold6,Gold5,Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000000000)
		unicode::_sprintf(Text,"%d,%03d,%03d,%03d,%03d",Gold5,Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000000)
		unicode::_sprintf(Text,"%d,%03d,%03d,%03d",Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000)
		unicode::_sprintf(Text,"%d,%03d,%03d",Gold3,Gold2,Gold1);
	else if(Gold >= 1000)
		unicode::_sprintf(Text,"%d,%03d",Gold2,Gold1);
	else 
		unicode::_sprintf(Text,"%d",Gold1);
}
#endif	// YDG_FIX_CATLE_MONEY_INT64_TYPE_CRASH

void ConvertTaxGold(DWORD Gold,char *Text)
{
	Gold += ((LONGLONG)Gold * g_pNPCShop->GetTaxRate()) / 100;

	int Gold1 = Gold%1000;
	int Gold2 = Gold%1000000/1000;
	int Gold3 = Gold%1000000000/1000000;
	int Gold4 = Gold/1000000000;
	if(Gold >= 1000000000)
       	sprintf(Text,"%d,%03d,%03d,%03d",Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000)
       	sprintf(Text,"%d,%03d,%03d",Gold3,Gold2,Gold1);
	else if(Gold >= 1000)
       	sprintf(Text,"%d,%03d",Gold2,Gold1);
	else 
       	sprintf(Text,"%d",Gold1);
}

void ConvertChaosTaxGold(DWORD Gold,char *Text)
{
	Gold += ((LONGLONG)Gold*g_nChaosTaxRate)/100;

	int Gold1 = Gold%1000;
	int Gold2 = Gold%1000000/1000;
	int Gold3 = Gold%1000000000/1000000;
	int Gold4 = Gold/1000000000;
	if(Gold >= 1000000000)
       	sprintf(Text,"%d,%03d,%03d,%03d",Gold4,Gold3,Gold2,Gold1);
	else if(Gold >= 1000000)
       	sprintf(Text,"%d,%03d,%03d",Gold3,Gold2,Gold1);
	else if(Gold >= 1000)
       	sprintf(Text,"%d,%03d",Gold2,Gold1);
	else 
       	sprintf(Text,"%d",Gold1);
}

int ConvertRepairGold(int Gold,int Durability, int MaxDurability, short Type, char *Text)
{
	Gold = min(Gold,400000000);

	float   repairGold = (float)Gold;
	float   persent = 1.f - (float)( Durability / (float)MaxDurability );
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	float   baseP = 1.f;
	float   addP  = 1.f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	bool    doubleP = false;
	
	if ( persent > 0 )
	{
		float fRoot = ( float)sqrt( ( double)repairGold);
		float fRootRoot = ( float)sqrt( sqrt( ( double)repairGold));
		repairGold = 3.f * fRoot * fRootRoot;

		// �ι�
		if(doubleP)
		{
			repairGold *= 2;
		}
		
		repairGold *= persent;
		repairGold++;

		// �������� 0�϶�
		if ( Durability <= 0 )
		{
#ifdef KJH_FIX_REPAIR_DARKLOAD_PET_DURABILITY_ZERO
			if(Type == ITEM_HELPER+4 ||  Type == ITEM_HELPER+5)	// ��ũȣ��, ��ũ���Ǹ� ����ó��
			{
				repairGold *= 2;
			}
			else
			{
#ifdef PBG_FIX_REPAIRGOLD_DURABILITY0
				repairGold = repairGold*0.4f;
#else //PBG_FIX_REPAIRGOLD_DURABILITY0
				repairGold += repairGold*0.4f;
#endif //PBG_FIX_REPAIRGOLD_DURABILITY0
			}
#else // KJH_FIX_REPAIR_DARKLOAD_PET_DURABILITY_ZERO
#ifdef PBG_FIX_REPAIRGOLD_DURABILITY0
				repairGold = repairGold*0.4f;
#else //PBG_FIX_REPAIRGOLD_DURABILITY0
				repairGold += repairGold*0.4f;
#endif //PBG_FIX_REPAIRGOLD_DURABILITY0
#endif // KJH_FIX_REPAIR_DARKLOAD_PET_DURABILITY_ZERO
		}
	}
	else
	{
		repairGold = 0;
	}
	
#ifdef KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) == true && g_pNPCShop->IsRepairShop())
	{
		Gold = (int)(repairGold);		// npc���� ���� �ݾ� (�Ϲݰ���)
	}
	else if((g_pMyInventory->IsVisible()) && (!g_pNPCShop->IsVisible()))
	{
#ifdef PBG_MOD_INVENTORY_REPAIR_COST
		Gold = (int)(repairGold + (repairGold * 1.5f));		// �ڵ����� �ݾ� ���� ����
#else //PBG_MOD_INVENTORY_REPAIR_COST
		Gold = (int)(repairGold + (repairGold * 2.0f));		// �κ��丮 �ڵ����� �ݾ� ����(3�����)
#endif //PBG_MOD_INVENTORY_REPAIR_COST
	}	
	else
	{
		// ���û�npc ��ȭâ�� ���ִ��� �˻縦 �Ҽ� ���� ������,
		// ���ʿ��� ����ó�� �ϰ� �������� ���û�npc��� �����Ͽ���.
		Gold = (int)(repairGold);		// npc����(���û�) ���� �ݾ� (�Ϲݰ���)
	}
#else // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) == true && g_pNPCShop->IsRepairShop())
	{
		Gold = (int)(repairGold);		// npc���� ��ü���� �ݾ�
	}
	else if(Type == ITEM_HELPER+4 ||  Type == ITEM_HELPER+5)	// ��ũȣ��, ��ũ���Ǹ��� ���� ����
	{
		Gold = (int)(repairGold);		
	}
	else
	{
#ifdef KJH_FIX_INVENTORY_REPAIR_COST
		Gold = (int)(repairGold + (repairGold * 2.0f));		// �κ��丮 �ڵ����� �ݾ� ����
#else // KJH_FIX_INVENTORY_REPAIR_COST
		Gold = (int)(repairGold + (repairGold * 0.05f));
#endif // KJH_FIX_INVENTORY_REPAIR_COST
	}
#endif // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
	
	if(Gold >= 1000)
	{
		Gold = (Gold / 100) * 100;
	}
#ifdef PBG_FIX_REPAIRGOLD_DURABILITY0
	else if(Gold > 10)
#else //PBG_FIX_REPAIRGOLD_DURABILITY0
	else if(Gold >= 100)
#endif //PBG_FIX_REPAIRGOLD_DURABILITY0
	{
		Gold = (Gold / 10) * 10;
	}
	
	ConvertGold(Gold, Text);
	
	return  Gold;
}


void RepairAllGold ( void )
{
    char    text[100];

    AllRepairGold = 0;
    //  ���â�� �������� �˻��Ѵ�.
	for( int i=0; i<MAX_EQUIPMENT; ++i )
	{
		if( CharacterMachine->Equipment[i].Type != -1)
        {
            ITEM* ip = &CharacterMachine->Equipment[i];
	        ITEM_ATTRIBUTE* p = &ItemAttribute[ip->Type];

			int Level = (ip->Level>>3)&15;
            int maxDurability = calcMaxDurability(ip, p, Level);

#ifdef LDK_FIX_USING_ISREPAIRBAN_FUNCTION
			// �ִ� �Լ��� Ȱ���սô�...
			if(IsRepairBan(ip) == true)
			{
				continue;
			}
#else //LDK_FIX_USING_ISREPAIRBAN_FUNCTION
			// CSK��������
#ifdef CSK_PCROOM_ITEM
			if(ip->Type >= ITEM_POTION+55 && ip->Type <= ITEM_POTION+57)
			{
				continue;
			}
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH	
			if(ip->Type == ITEM_HELPER+96)	// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
			{
				continue;
			}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH	

			//. item filtering
			if( (ip->Type >= ITEM_HELPER && ip->Type <= ITEM_HELPER+5) || ip->Type == ITEM_HELPER+10 || ip->Type == ITEM_HELPER+31 )   // ������ - ���� �����Ҷ� ITEM_HELPER+5 �� ��ũ ���Ǹ� ������
				continue;
			if( ip->Type == ITEM_BOW+7 || ip->Type == ITEM_BOW+15 || ip->Type >= ITEM_POTION )
				continue;
			if( ip->Type >= ITEM_WING+7 && ip->Type <= ITEM_WING+19 )	//. ���� ���͸�
				continue;
			if( (ip->Type >= ITEM_HELPER+14 && ip->Type <= ITEM_HELPER+19) || ip->Type==ITEM_POTION+21 )
				continue;
			if( ip->Type == ITEM_HELPER+20)
				continue;
#ifdef MYSTERY_BEAD
			if( ip->Type == ITEM_WING+26)
				continue;
#endif // MYSTERY_BEAD

			if(ip->Type == ITEM_HELPER+37)
				continue;

			if( ip->Type == ITEM_HELPER+38 )
				continue;
#endif //LDK_FIX_USING_ISREPAIRBAN_FUNCTION

			//. check durability
            if( ip->Durability<maxDurability )
            {
                int gold = ConvertRepairGold(ItemValue(ip,2),ip->Durability, maxDurability, ip->Type, text);

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ ���â�� ������ �˻� ����
				if( Check_LuckyItem( ip->Type ) )	gold = 0;
#endif // LEM_ADD_LUCKYITEM
                AllRepairGold += gold;
            }
        }
	}

	ITEM * pItem = NULL;
#ifdef _VS2008PORTING
	for(int i = 0; i < (int)(g_pMyInventory->GetInventoryCtrl()->GetNumberOfItems()); ++i)
#else // _VS2008PORTING
	for(i = 0; i < g_pMyInventory->GetInventoryCtrl()->GetNumberOfItems(); ++i)
#endif // _VS2008PORTING
	{
		pItem = g_pMyInventory->GetInventoryCtrl()->GetItem(i);

		if(pItem)
		{
			ITEM_ATTRIBUTE* p = &ItemAttribute[pItem->Type];
			
			int Level = (pItem->Level>>3)&15;
			int maxDurability = calcMaxDurability( pItem, p, Level );
			
			// CSK��������
#ifdef CSK_PCROOM_ITEM
			if(pItem->Type >= ITEM_POTION+55 && pItem->Type <= ITEM_POTION+57)
			{
				continue;
			}
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
			if(pItem->Type == ITEM_HELPER+96)	// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
			{
				continue;
			}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH	
			//. item filtering
			if( (pItem->Type >= ITEM_HELPER && pItem->Type <= ITEM_HELPER+5) || pItem->Type == ITEM_HELPER+10  || pItem->Type == ITEM_HELPER+31)  // ������ - ���� �����Ҷ� ITEM_HELPER+5 �� ��ũ ���Ǹ� ������
				continue;
			if( pItem->Type == ITEM_BOW+7 || pItem->Type == ITEM_BOW+15 || pItem->Type >= ITEM_POTION )
				continue;
			if( pItem->Type >= ITEM_WING+7 && pItem->Type <= ITEM_WING+19 )	//. ���� ���͸�
				continue;
			if( (pItem->Type >= ITEM_HELPER+14 && pItem->Type <= ITEM_HELPER+19) || pItem->Type==ITEM_POTION+21 )
				continue;
			if( pItem->Type == ITEM_HELPER+20)
				continue;
#ifdef MYSTERY_BEAD
			if( pItem->Type == ITEM_WING+26)
				continue;
#endif // MYSTERY_BEAD
			if( pItem->Type == ITEM_HELPER+38 )
				continue;
#ifdef CSK_FREE_TICKET
			// ������ ���� �ȵǰ� ���� ó��
			if(pItem->Type >= ITEM_HELPER+46 && pItem->Type <= ITEM_HELPER+48)
			{
				continue;
			}
#endif // CSK_FREE_TICKET
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
			if(pItem->Type >= ITEM_HELPER+125 && pItem->Type <= ITEM_HELPER+127)
			{
				continue;
			}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
			// ������ ���� �ȵǰ� ���� ó��
			if(pItem->Type >= ITEM_POTION+145 && pItem->Type <= ITEM_POTION+150)
			{
				continue;
			}
#endif // LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12

#ifdef CSK_RARE_ITEM
			// ������ ���� �ȵǰ� ���� ó��
			if(pItem->Type >= ITEM_POTION+58 && pItem->Type <= ITEM_POTION+62)
			{
				continue;
			}
#endif // CSK_RARE_ITEM

#ifdef CSK_LUCKY_CHARM
			if( pItem->Type == ITEM_POTION+53 )// ����� ����
			{
				continue;
			}
#endif //CSK_LUCKY_CHARM
			
#ifdef CSK_LUCKY_SEAL
			if( pItem->Type == ITEM_HELPER+43 || pItem->Type == ITEM_HELPER+44 || pItem->Type == ITEM_HELPER+45 )
			{
				continue;
			}
#endif //CSK_LUCKY_SEAL
			
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
			if( pItem->Type >= ITEM_POTION+70 && pItem->Type <= ITEM_POTION+71 )
			{
				continue;
			}
#endif //PSW_ELITE_ITEM
			
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
			if( pItem->Type >= ITEM_POTION+72 && pItem->Type <= ITEM_POTION+77 )
			{
				continue;
			}
#endif //PSW_SCROLL_ITEM
			
#ifdef PSW_SEAL_ITEM               // �̵� ����
			if( pItem->Type == ITEM_HELPER+59 )
			{
				continue;
			}
#endif //PSW_SEAL_ITEM
			
#ifdef PSW_FRUIT_ITEM              // ���� ����
			if( pItem->Type >= ITEM_HELPER+54 && pItem->Type <= ITEM_HELPER+58 )
			{
				continue;
			}
#endif //PSW_FRUIT_ITEM
			
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
			if( pItem->Type >= ITEM_POTION+78 && pItem->Type <= ITEM_POTION+82 )
			{
				continue;
			}
#endif //PSW_SECRET_ITEM
			
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
			if( pItem->Type == ITEM_HELPER+60 )
			{
				continue;
			}
#endif //PSW_INDULGENCE_ITEM
			
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET  // ȯ���� ��� ���� �����
			if( pItem->Type == ITEM_HELPER+61 )
			{
				continue;
			}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET

#ifdef PSW_CHARACTER_CARD						// ��ȯ���� ĳ���� ī��
			if( pItem->Type == ITEM_POTION+91 )
			{
				continue;
			}
#endif //PSW_CHARACTER_CARD						// ��ȯ���� ĳ���� ī��

#ifdef PSW_NEW_CHAOS_CARD						// �ű� ī���� ī��
			if( pItem->Type >= ITEM_POTION+92 && pItem->Type <= ITEM_POTION+93 )
			{
				continue;
			}
			if( pItem->Type == ITEM_POTION+95 )
			{
				continue;
			}
#endif //PSW_NEW_CHAOS_CARD						// �ű� ī���� ī��

#ifdef PSW_NEW_ELITE_ITEM						// �߰� ����Ʈ ����
			if( pItem->Type == ITEM_POTION+95 )
			{
				continue;
			}
#endif //PSW_NEW_ELITE_ITEM						// �߰� ����Ʈ ����	

#ifdef PSW_ADD_PC4_SEALITEM
			if( pItem->Type >= ITEM_HELPER+62 && pItem->Type <= ITEM_HELPER+63 )
			{
				continue;
			}
#endif //PSW_ADD_PC4_SEALITEM

#ifdef PSW_ADD_PC4_SCROLLITEM
			if( pItem->Type >= ITEM_POTION+97 && pItem->Type <= ITEM_POTION+98 )
			{
				continue;
			}
#endif //PSW_ADD_PC4_SCROLLITEM
			
#ifdef YDG_ADD_HEALING_SCROLL
			if (pItem->Type == ITEM_POTION+140)	// ġ���� ��ũ��
			{
				continue;
			}
#endif	// YDG_ADD_HEALING_SCROLL
			
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
			if( pItem->Type == ITEM_POTION+96 )
			{
				continue;
			}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
			if ( pItem->Type == ITEM_HELPER+64 || pItem->Type == ITEM_HELPER+65 ) 
			{
				continue;
			}
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDK_ADD_RUDOLPH_PET
			if ( pItem->Type == ITEM_HELPER+67 ) 
			{
				continue;
			}
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
			if ( pItem->Type == ITEM_HELPER+80 ) 
			{
				continue;
			}
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
			if ( pItem->Type == ITEM_HELPER+106 ) 
			{
				continue;
			}
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
			if ( pItem->Type == ITEM_HELPER+123 )	// ���̷��� ��
			{
				continue;
			}
#endif	// YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
			//��������
			if ( pItem->Type == ITEM_HELPER+68 ) 
			{
				continue;
			}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
			if ( pItem->Type == ITEM_HELPER+76 ) 
			{
				continue;
			}
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
			if ( pItem->Type == ITEM_HELPER+122 )	// ���̷��� ���Ź���
			{
				continue;
			}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
			if ( pItem->Type == ITEM_HELPER+69 ) 	// ��Ȱ�� ����
				continue;
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
			if ( pItem->Type == ITEM_HELPER+70 ) 	// �̵��� ����
				continue;
#endif	// YDG_ADD_CS5_PORTAL_CHARM
			if(pItem->Type == ITEM_HELPER+37)	// �渱
				continue;
#ifdef PBG_ADD_SANTAINVITATION
			if(pItem->Type == ITEM_HELPER+66)	//��Ÿ������ �ʴ���
				continue;
#endif //PBG_ADD_SANTAINVITATION
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON //�׺� ������
			if(	pItem->Type == ITEM_HELPER+71 
				|| pItem->Type == ITEM_HELPER+72 
				|| pItem->Type == ITEM_HELPER+73
				|| pItem->Type == ITEM_HELPER+74
				|| pItem->Type == ITEM_HELPER+75 )
				continue;
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef ASG_ADD_CS6_GUARD_CHARM
			if (pItem->Type == ITEM_HELPER+81)	// ��ȣ�Ǻ���
				continue;
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
			if (pItem->Type == ITEM_HELPER+82)	// �����ۺ�ȣ����
				continue;
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
			if (pItem->Type == ITEM_HELPER+93)	// ��������帶����
				continue;
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
			if (pItem->Type == ITEM_HELPER+94)	// ǳ�������帶����
				continue;
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER


#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING
			if( pItem->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN 
				&& pItem->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END ) // ���� ���� 100% ���� ����
			{
				continue;
			}
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef PBG_ADD_CHARACTERCARD
			// ���� ��ũ ��ȯ���� ī��
			if(pItem->Type == ITEM_HELPER+97 || pItem->Type == ITEM_HELPER+98 || pItem->Type == ITEM_POTION+91)
				continue;
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
			if(pItem->Type == ITEM_HELPER+99)		// ����ī��
				continue;
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
			if(pItem->Type >= ITEM_HELPER+117 && pItem->Type <= ITEM_HELPER+120)	// Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
				continue;
#endif //PBG_ADD_SECRETITEM
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
			if(pItem->Type == ITEM_HELPER+121)		// �ΰ��Ә� ������ // ī�����ɽ� ���������
				continue;
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
			if(g_pMyInventory->IsInvenItem(pItem->Type))
				continue;

#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef LEM_FIX_SHOPITEM_DURABILITY_REPAIRGOLD	// �ΰ��Ӽ� 5-4�� �߰��� �Ϻ� ������ ������ ������ ���� [lem.2010.7.28]
		#ifdef LDK_ADD_INGAMESHOP_SMALL_WING	// �Ⱓ�� ���� ����(����/���/����/õ��/��ź)�� ���� ����
			if( pItem->Type >= ITEM_WING+130 && pItem->Type <= ITEM_WING+134 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
			if( pItem->Type == ITEM_HELPER+109 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
			if( pItem->Type == ITEM_HELPER+110 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
			if( pItem->Type == ITEM_HELPER+111 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
			if( pItem->Type == ITEM_HELPER+112 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
			if( pItem->Type == ITEM_HELPER+113 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
			if( pItem->Type == ITEM_HELPER+114 )
				continue;
		#endif
		#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE
			if( pItem->Type == ITEM_HELPER+115 )
				continue;
		#endif
		#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
			if( pItem->Type == ITEM_HELPER+107 )
				continue;
		#endif			
#endif	// LEM_FIX_SHOPITEM_DURABILITY_REPAIRGOLD
#ifdef LEM_ADD_LUCKYITEM
		if( Check_ItemAction( pItem, eITEM_REPAIR ) )	continue;
#endif // LEM_ADD_LUCKYITEM

			//. check durability
			if( pItem->Durability<maxDurability )
			{
				int gold = ConvertRepairGold(ItemValue(pItem,2),pItem->Durability, maxDurability, pItem->Type, text);
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮�� ������ �˻� ����
				if( Check_LuckyItem( pItem->Type ) )	gold = 0;
#endif // LEM_ADD_LUCKYITEM
				AllRepairGold += gold;
			}
		}
	}
}


int InventoryStartX;
int InventoryStartY;
int ShopInventoryStartX;
int ShopInventoryStartY;
int TradeInventoryStartX;
int TradeInventoryStartY;
int CharacterInfoStartX;
int CharacterInfoStartY;
int GuildStartX;
int GuildStartY;
int GuildListStartX;
int GuildListStartY;
int SommonTable[]={2,7,14,8,9,41};

char ChaosEventName[][100] = {
	"����ũ ���� �����",
	"��Ƽ��4 ��ǻ��",
	"����Żī�޶�",
	"������ ���� ���콺+Ű���� ��Ʈ",
	"256M ��",
    "6���� ���� ������",
	"��ȭ��ǰ��(����)",
	"�� �ӱ���",
	"�� T����",
	"�� 10�ð� �����̿��"
};

WORD calcMaxDurability ( const ITEM* ip, ITEM_ATTRIBUTE *p, int Level )
{
    WORD maxDurability = p->Durability;
	
#ifdef KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
	// ��ũ�ε� ��
#ifndef PBG_FIX_DARKPET_DURABILITY
	if( ip->Type==ITEM_HELPER+4 || ip->Type== ITEM_HELPER+5)
	{
#ifdef PBG_FIX_REPAIRGOLD_DARKPAT
		maxDurability = 255 -1;
#else //PBG_FIX_REPAIRGOLD_DARKPAT
		maxDurability = 255;		// ����ó��
#endif //PBG_FIX_REPAIRGOLD_DARKPAT
	}
#endif //PBG_FIX_DARKPET_DURABILITY
#endif // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
    if( ip->Type>=ITEM_STAFF && ip->Type<ITEM_STAFF+MAX_ITEM_INDEX )
    {
        maxDurability = p->MagicDur;
    }
    for( int i=0; i<Level; i++ )
    {
		if (ip->Type>=ITEM_HELPER+51)
		{
			break;
		}
		else
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		if(i>=14)	// 15����
		{
			maxDurability = (maxDurability+8 >= 255 ? 255 : maxDurability+8);
		}
		else if(i>=13)	// 14����
		{
			maxDurability = (maxDurability+7 >= 255 ? 255 : maxDurability+7);
		}
		else
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		if(i>=12)	// 13����
		{
			maxDurability+=6;
		}
		else if(i>=11)	// 12����
		{
			maxDurability+=5;
		}
		else 
		if(i>=10)	// 11����
		{
			maxDurability+=4;
		}
        else if(i>=9)	// 10����
		{
			maxDurability+=3;
		}
        else if(i>=4)	// 5~9����
        {
            maxDurability+=2;
        }
        else	// 1~4����
        {
            maxDurability++;
        }
    }
#ifdef PBG_FIX_DARKPET_DURABILITY
	if( ip->Type==ITEM_HELPER+4 || ip->Type== ITEM_HELPER+5)
	{
		maxDurability = 255;		// ����ó��
	}
#endif //PBG_FIX_DARKPET_DURABILITY
    if ( (ip->ExtOption%0x04)==EXT_A_SET_OPTION || (ip->ExtOption%0x04)==EXT_B_SET_OPTION )    //  ��Ʈ ������.
    {
        maxDurability+=20;
    }
    else if( ( ip->Option1&63)>0 && 
		( ip->Type<ITEM_WING+3 || ip->Type>ITEM_WING+6 ) &&		// 1�� ���� ����, 2�� ���� ����.
		( ip->Type!=ITEM_SWORD+19 && ip->Type!=ITEM_BOW+18 && ip->Type!=ITEM_STAFF+10 )
        && ip->Type!=ITEM_HELPER+30   //  ������ ����.
		&& ( ip->Type<ITEM_WING+36 || ip->Type>ITEM_WING+40 )	// 3������ ����.
#ifdef ADD_ALICE_WINGS_1
		&& (ip->Type<ITEM_WING+42 || ip->Type>ITEM_WING+43)	// ��ȯ���� 2,3������ ����.
#endif	// ADD_ALICE_WINGS_1
		&& ip->Type!=ITEM_MACE+13	// ���� ���� 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		&& !(ip->Type >= ITEM_WING+49 && ip->Type <= ITEM_WING+50)	//�����������ͳ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	  )
    {
        maxDurability+=15;	// ����
    }
#ifdef LEM_ADD_LUCKYITEM		// ��Ű������ ������ ���� Max���� ����ó��
	if( Check_LuckyItem(ip->Type) )
	{
		maxDurability	= 255;
	}
#endif // LEM_ADD_LUCKYITEM

    return  maxDurability;
}


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//	�ش� �������� �̸��� �˾Ƴ���.
//////////////////////////////////////////////////////////////////////////
void GetItemName ( int iType, int iLevel, char* Text )
{
	ITEM_ATTRIBUTE *p = &ItemAttribute[iType];

    //  �������� �̸�.
    if (iType>=ITEM_POTION+23 && iType<=ITEM_POTION+26 )   //  ����Ʈ ������.
    {
		if(iType == ITEM_POTION+23)	//. ������ ��, �����ǹ���
		{
			switch( iLevel )
			{
			case 0: sprintf ( Text, "%s", p->Name ); break;			//	������ ��
			case 1: sprintf ( Text, "%s", GlobalText[906] ); break;	//  ������ ����
			}
		}
		else if(iType == ITEM_POTION+24)	//. �η�����, ��ũ����
		{
			switch( iLevel )
			{
			case 0: sprintf ( Text, "%s", p->Name ); break;			//	�η�����.
			case 1: sprintf ( Text, "%s", GlobalText[907] ); break;	//  ��ũ����.
			}
		}
		else
		{
			sprintf ( Text, "%s", p->Name );
		}
    }
	else if(iType == ITEM_POTION+12)//�̹�Ʈ ������
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", GlobalText[100] ); break;
		case 1:	sprintf ( Text, "%s", GlobalText[101] ); break;
		case 2:	sprintf ( Text, "%s", ChaosEventName[p->Durability] ); break;
		}
	}
	else if(iType == ITEM_POTION+11)//����� ����/��ź�Ǻ�/����/���� �ָӴ�./����� ��Ʈ//����
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", p->Name ); break;
		case 1: sprintf ( Text, "%s", GlobalText[105] ); break;
		case 2: sprintf ( Text, "%s", GlobalText[106] ); break;
		case 3: sprintf ( Text, "%s", GlobalText[107] ); break;
		case 5: sprintf ( Text, "%s", GlobalText[109] ); break;
		case 6: sprintf ( Text, "%s", GlobalText[110] ); break;
        case 7: sprintf ( Text, "%s", GlobalText[111] ); break; //  õ���� ����.
			break;
#ifdef USE_EVENT_ELDORADO
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:	// õ���� ����
			sprintf(Text,"%s +%d",GlobalText[115], iLevel - 7);
			break;
#endif // USE_EVENT_ELDORADO
		case 13:	// ��ũ�ε��� ����
			sprintf(Text, GlobalText[117]); break;
#ifdef NEW_YEAR_BAG_EVENT
        case 14:    //  ���ָӴ�.
			sprintf(Text, GlobalText[1650]); break;
            break;

        case 15:
			sprintf(Text, GlobalText[1651]); break;
            break;
#else
    #ifdef CHINA_MOON_CAKE
        case 14:    //  �߱� ����.
            sprintf(Text,GlobalText[118]); break;
            break;
    #endif// CHINA_MOON_CAKE
#endif// NEW_YEAR_BAG_EVENT
		}
	}
    else if ( iType==ITEM_HELPER+15 )//  ��Ŭ. ( ������/ü��/��ø/��/��� )
    {
        switch ( iLevel )
        {
        case 0:sprintf(Text,"%s %s", GlobalText[168], p->Name ); break;
        case 1:sprintf(Text,"%s %s", GlobalText[169], p->Name ); break;
        case 2:sprintf(Text,"%s %s", GlobalText[167], p->Name ); break;
        case 3:sprintf(Text,"%s %s", GlobalText[166], p->Name ); break;
		case 4:sprintf(Text,"%s %s", GlobalText[1900], p->Name ); break;	// ��ֿ���
        }
    }
    else if ( iType==ITEM_HELPER+14 )//  ��ũ�� ����.
    {
        switch ( iLevel )
        {
        case 0: sprintf ( Text, "%s", p->Name ); break;             //  ��ũ�� ����.
        case 1: sprintf ( Text, "%s", GlobalText[1235] ); break;    //  ������ ����.
        }
    }
    else if ( iType==ITEM_HELPER+31 )   //  ��ȥ.
    {
        switch ( iLevel )
        {
        case 0: sprintf ( Text, "%s %s", GlobalText[1187], p->Name ); break;
        case 1: sprintf ( Text, "%s %s", GlobalText[1214], p->Name ); break;
        }
    }
#ifdef ANNIVERSARY_EVENT
    else if ( iType==ITEM_POTION+20 )//  ����� ����
    {
        switch ( iLevel )
        {
        case 0: sprintf ( Text, "%s", p->Name ); break;
        case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			sprintf ( Text, "%s +%d", GlobalText[116], iLevel ); break;     //  �ִϹ����� �ڽ�
        }
    }
#endif	// ANNIVERSARY_EVENT
#ifdef _PVP_ADD_MOVE_SCROLL
    else if ( iType==ITEM_POTION+10 )//  �̵�����
    {
        switch ( iLevel )
        {
        case 0: sprintf ( Text, "%s", p->Name ); break;
        case 1: sprintf ( Text, GlobalText[158], GlobalText[30] ); break;     //  �η��þ�
		case 2: sprintf ( Text, GlobalText[158], GlobalText[33] ); break;     //  �븮��
		case 3: sprintf ( Text, GlobalText[158], GlobalText[32] ); break;     //  ����ƽ�
		case 4: sprintf ( Text, GlobalText[158], GlobalText[31] ); break;     //  ����
		case 5: sprintf ( Text, GlobalText[158], GlobalText[37] ); break;     //  ��Ʋ����
		case 6: sprintf ( Text, GlobalText[158], GlobalText[34] ); break;     //  �ν�ƮŸ��
		case 7: sprintf ( Text, GlobalText[158], GlobalText[38] ); break;     //  Ÿ��ĭ
		case 8: sprintf ( Text, GlobalText[158], GlobalText[55] ); break;     //  ��ī�罺
        }
    }
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef _PVP_MURDERER_HERO_ITEM
    else if ( iType==ITEM_POTION+30 )//  �������θ�¡ǥ(pick)
    {
		sprintf ( Text, "%s", p->Name );
    }
#endif	// _PVP_MURDERER_HERO_ITEM
    else if ( iType==ITEM_POTION+21 )    //  ����. ( 1:����).
    {
        switch ( iLevel )
        {
        case 0: sprintf ( Text, "%s", p->Name ); break;
        case 1: sprintf ( Text, "%s", GlobalText[810] ); break;     //  ����.
        case 2: sprintf ( Text, "%s", GlobalText[1098] ); break;    //  ������ ��.
        case 3: sprintf ( Text, "%s", GlobalText[1290] ); break;    //  ������ǥ��
        }
    }
    else if ( iType==ITEM_HELPER+19 )	//  ��õ���� ���� ����
    {
        sprintf ( Text, "%s", GlobalText[809] );
    }
	else if ( iType == ITEM_HELPER+20 )
	{
		switch(iLevel)
		{
		case 0: sprintf( Text, "%s", p->Name ); break;			//. �������� ����	
		case 1: sprintf( Text, "%s", GlobalText[922] ); break;	//. ������ ����
        case 2: sprintf( Text, "%s", GlobalText[928] ); break;	//. ������ ����
        case 3: sprintf( Text, "%s", GlobalText[929] ); break;	//. ������ ����
		}
	}
	else if(iType == ITEM_POTION+9)//��, ����� �ø���
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", p->Name ); break;
		case 1:	sprintf ( Text, "%s", GlobalText[108] ); break;
		}
	}
    else if(iType == ITEM_WING+11)//��ȯ����
	{
#ifdef KJW_FIX_ITEMNAME_ORB_OF_SUMMONING
		sprintf(Text,"%s %s",SkillAttribute[30+iLevel].Name,GlobalText[102]);
#else // KJW_FIX_ITEMNAME_ORB_OF_SUMMONING
        sprintf ( Text, "%s %s", GlobalText[738], GlobalText[102] );
#endif // KJW_FIX_ITEMNAME_ORB_OF_SUMMONING
	}
#ifdef MYSTERY_BEAD
	else if(iType == ITEM_WING+26)
	{
		switch(iLevel)
		{
		case 0:		//. �ź��Ǳ���
			strcpy( Text, p->Name); break;
		case 1:		//. ��������
			strcpy( Text, GlobalText[1831]); break;
		case 2:		//. �Ķ�����
			strcpy( Text, GlobalText[1832]); break;
		case 3:		//. ��������
			strcpy( Text, GlobalText[1833]); break;
		case 4:		//. ��������
			strcpy( Text, GlobalText[1834]); break;
		case 5:		//. ��¦����
			strcpy( Text, GlobalText[1838]); break;
		}
	}
#endif // MYSTERY_BEAD
	else if(iType == ITEM_WING+32)//������������.(x-mas�̺�Ʈ��)
	{
		sprintf(Text, "%s", p->Name);	
	}
	else if(iType == ITEM_WING+33)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		sprintf(Text, "%s", p->Name);	
	}
	else if(iType == ITEM_WING+34)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		sprintf(Text, "%s", p->Name);	
	}
	else if(iType == ITEM_WING+35)//���̾ũ��
	{
		sprintf(Text, "%s", p->Name);	
	}

#ifdef HELLOWIN_EVENT
	else if(iType >= ITEM_POTION+45 && iType <= ITEM_POTION+50)//�ҷ������� �̺�Ʈ
	{
 		sprintf ( Text, "%s", p->Name ); 
	}
#endif //#ifdef HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	else if(iType == ITEM_POTION+32)//��ȫ ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", p->Name ); break;
 		case 1:	sprintf ( Text, "%s", GlobalText[2012] ); break;
		}
	}
	else if(iType == ITEM_POTION+33)//���� ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", p->Name ); break;
		case 1:	sprintf ( Text, "%s", GlobalText[2013] ); break;
		}
	}
	else if(iType == ITEM_POTION+34)//�Ķ� ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(iLevel)
		{
		case 0: sprintf ( Text, "%s", p->Name ); break;
		case 1:	sprintf ( Text, "%s", GlobalText[2014] ); break;
		}
	}
#endif

    else if(iType == ITEM_HELPER+10)//���Ź���
	{
		for(int i=0;i<MAX_MONSTER;i++)
		{
			if(SommonTable[iLevel] == MonsterScript[i].Type)
			{
        		sprintf(Text,"%s %s",MonsterScript[i].Name,GlobalText[103]);
			}
		}
	}
    else if ( iType>=ITEM_WING+3 && iType<=ITEM_WING+6 )  //  ������ ���� ~ ����� ����.
    {
		if(iLevel==0)
			sprintf(Text,"%s",p->Name);
		else
			sprintf(Text,"%s +%d",p->Name,iLevel);
    }
#ifdef ADD_ALICE_WINGS_1
	else if ((iType>=ITEM_WING+36 && iType<=ITEM_WING+40) || (iType>=ITEM_WING+42 && iType<=ITEM_WING+43)
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (iType == ITEM_WING+50) //�����Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)	// ��ǳ�� ���� ~ ������ ����, ��ȯ���� 2,3�� ����.
#else	// ADD_ALICE_WINGS_1
	else if ( iType>=ITEM_WING+36 && iType<=ITEM_WING+40 )  //  ��ǳ�� ���� ~ ������ ����
#endif	// ADD_ALICE_WINGS_1
    {
		if(iLevel==0)
			sprintf(Text,"%s",p->Name);
		else
			sprintf(Text,"%s +%d",p->Name,iLevel);
    }
	else if ( iType==ITEM_SWORD+19 || iType==ITEM_BOW+18 || iType==ITEM_STAFF+10 || iType==ITEM_MACE+13) //	��õ���� ���� ����.
	{
		if(iLevel==0)
			sprintf(Text,"%s",p->Name);
		else
			sprintf(Text,"%s +%d",p->Name,iLevel);
	}
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if ( COMGEM::NOGEM != COMGEM::Check_Jewel_Com(iType) )
	{
		// ���� ����
 		sprintf(Text,"%s +%d", p->Name, iLevel+1);
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if ( iType==INDEX_COMPILED_CELE)
	{
		sprintf(Text,"%s +%d", GlobalText[1806], iLevel+1);	// �ູ�� ���� ����
	}
	else if ( iType==INDEX_COMPILED_SOUL)
	{
		sprintf(Text,"%s +%d", GlobalText[1807], iLevel+1);	// ��ȥ�� ���� ����
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if ((iType >= ITEM_WING+60 && iType <= ITEM_WING+65)	// �õ�
		|| (iType >= ITEM_WING+70 && iType <= ITEM_WING+74)	// ���Ǿ�
		|| (iType >= ITEM_WING+100 && iType <= ITEM_WING+129))	// �õ彺�Ǿ�
	{
		sprintf(Text,"%s",p->Name);
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef LJH_FIX_BUG_MISSING_ITEM_NAMES_ITEM_HELPER_7 
    else if ( iType == ITEM_POTION+7 ) //  ���м� ����.//���ƹ���
    {
		int iTextIndex = 0;
		
		iTextIndex = (iLevel == 0) ? 1413 : 1414;
        sprintf ( Text, "%s", GlobalText[iTextIndex] );
    }
#endif //LJH_FIX_BUG_MISSING_ITEM_NAMES_ITEM_HELPER_7
	else
	{
		if(iLevel==0)
			sprintf(Text,"%s",p->Name);
		else
			sprintf(Text,"%s +%d",p->Name,iLevel);
	}
}


//////////////////////////////////////////////////////////////////////////
//  ������ �ɼ� ���� ���.
//////////////////////////////////////////////////////////////////////////
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
void GetSpecialOptionText ( int Type, char* Text, WORD Option, BYTE Value, int iMana )
#else //PBG_ADD_NEWCHAR_MONK_SKILL
void GetSpecialOptionText ( int Type, char* Text, BYTE Option, BYTE Value, int iMana )
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
{
    switch(Option)
    {
    case AT_SKILL_BLOCKING:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[80], iMana);
        break;
    case AT_SKILL_SWORD1:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[81], iMana);
        break;
    case AT_SKILL_SWORD2:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[82], iMana);
        break;
    case AT_SKILL_SWORD3:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[83], iMana);
        break;
    case AT_SKILL_SWORD4:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[84], iMana);
        break;
    case AT_SKILL_SWORD5:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[85], iMana);
        break;
	case AT_SKILL_MANY_ARROW_UP:
	case AT_SKILL_MANY_ARROW_UP+1:
	case AT_SKILL_MANY_ARROW_UP+2:
	case AT_SKILL_MANY_ARROW_UP+3:
	case AT_SKILL_MANY_ARROW_UP+4:

    case AT_SKILL_CROSSBOW:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[86], iMana);
        break;
    case AT_SKILL_BLAST_CROSSBOW4:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[920], iMana);
        break;
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	case AT_SKILL_MULTI_SHOT:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[920], iMana);
		break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	case AT_SKILL_RECOVER:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[920], iMana);
		break;
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_POWER_SLASH_UP:
	case AT_SKILL_POWER_SLASH_UP+1:
	case AT_SKILL_POWER_SLASH_UP+2:
	case AT_SKILL_POWER_SLASH_UP+3:
	case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
    case AT_SKILL_ICE_BLADE:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[98], iMana);
        break;
    case AT_LUCK:
        sprintf(Text,GlobalText[87]);
        break;
    case AT_IMPROVE_DAMAGE:
        sprintf(Text,GlobalText[88],Value);
        break;
    case AT_IMPROVE_MAGIC:
		sprintf(Text,GlobalText[89],Value);
        break;
	case AT_IMPROVE_CURSE:
		sprintf(Text,GlobalText[1697],Value);
		break;
    case AT_IMPROVE_BLOCKING:
        sprintf(Text,GlobalText[90],Value);
        break;
    case AT_IMPROVE_DEFENSE:
        sprintf(Text,GlobalText[91],Value);
        break;
    case AT_LIFE_REGENERATION:
        if ( !( ITEM_HELPER+14 <= Type && Type <= ITEM_HELPER+18))
        {
            sprintf(Text,GlobalText[92],Value);
        }
        break;
    case AT_IMPROVE_LIFE:
        sprintf(Text,GlobalText[622]);
        break;
    case AT_IMPROVE_MANA:
        sprintf(Text,GlobalText[623]);
        break;
    case AT_DECREASE_DAMAGE:
        sprintf(Text,GlobalText[624]);
        break;

    case AT_REFLECTION_DAMAGE:
        sprintf(Text,GlobalText[625]);
        break;
    case AT_IMPROVE_BLOCKING_PERCENT:
        sprintf(Text,GlobalText[626]);
        break;
    case AT_IMPROVE_GAIN_GOLD:
        sprintf(Text,GlobalText[627]);
        break;
    case AT_EXCELLENT_DAMAGE:
        sprintf(Text,GlobalText[628]);
        break;
    case AT_IMPROVE_DAMAGE_LEVEL:
        sprintf(Text,GlobalText[629]);
        break;
    case AT_IMPROVE_DAMAGE_PERCENT:
        sprintf(Text,GlobalText[630], Value);
        break;
    case AT_IMPROVE_MAGIC_LEVEL:
        sprintf(Text,GlobalText[631]);
        break;
    case AT_IMPROVE_MAGIC_PERCENT:
        sprintf(Text,GlobalText[632], Value);
        break;
    case AT_IMPROVE_ATTACK_SPEED:
        sprintf(Text,GlobalText[633], Value);
        break;
    case AT_IMPROVE_GAIN_LIFE:
        sprintf(Text,GlobalText[634]);
        break;
    case AT_IMPROVE_GAIN_MANA:
        sprintf(Text,GlobalText[635]);
        break;
    case AT_IMPROVE_EVADE :
        sprintf(Text, GlobalText[746] );
        break;
    case AT_SKILL_RIDER :
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text, GlobalText[745], iMana  );
        break;
    case AT_SKILL_STRONG_PIER:  //  
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf ( Text, GlobalText[1210], iMana );
        break;
    case AT_SKILL_LONG_SPEAR:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf ( Text, GlobalText[1186], iMana );
        break;
	case AT_SKILL_ASHAKE_UP:
	case AT_SKILL_ASHAKE_UP+1:
	case AT_SKILL_ASHAKE_UP+2:
	case AT_SKILL_ASHAKE_UP+3:
	case AT_SKILL_ASHAKE_UP+4:
    case AT_SKILL_DARK_HORSE:
        GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf ( Text, GlobalText[1189], iMana );
        break;
	case AT_SKILL_PLASMA_STORM_FENRIR:	// �ö�� ����
		GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf ( Text, GlobalText[1928], iMana );
		break;
    case AT_SET_OPTION_IMPROVE_DEFENCE :
        sprintf ( Text, GlobalText[959], Value );
        break;
    case AT_SET_OPTION_IMPROVE_CHARISMA :
        sprintf ( Text, GlobalText[954], Value );
        break;
    case AT_SET_OPTION_IMPROVE_DAMAGE :
        sprintf ( Text, GlobalText[577], Value );
        break;
    case AT_IMPROVE_HP_MAX :
        sprintf(Text, GlobalText[740], Value);
        break;
    case AT_IMPROVE_MP_MAX :
        sprintf(Text, GlobalText[741], Value);
        break;
    case AT_ONE_PERCENT_DAMAGE :
        sprintf(Text, GlobalText[742], Value);
        break;
    case AT_IMPROVE_AG_MAX :
        sprintf(Text, GlobalText[743], Value);
        break;
    case AT_DAMAGE_ABSORB :
        sprintf(Text, GlobalText[744], Value);
        break;
    case AT_SET_OPTION_IMPROVE_STRENGTH :
        sprintf(Text, GlobalText[985], Value );
        break;
        
    case AT_SET_OPTION_IMPROVE_DEXTERITY :
        sprintf(Text, GlobalText[986], Value );
        break;
        
    case AT_SET_OPTION_IMPROVE_VITALITY :
        sprintf(Text, GlobalText[987], Value );
        break;
        
    case AT_SET_OPTION_IMPROVE_ENERGY :
        sprintf(Text, GlobalText[988], Value );
        break;
        
    case AT_IMPROVE_MAX_MANA :
        sprintf(Text, GlobalText[1087], Value );
        break;
        
    case AT_IMPROVE_MAX_AG :
        sprintf(Text, GlobalText[1088], Value );
        break;
	case AT_DAMAGE_REFLECTION:	// [����� ������ �������� ������ ���] 5% Ȯ���� �� ���ݷ� 50% ������
		sprintf(Text, GlobalText[1673], Value );
		break;
	case AT_RECOVER_FULL_LIFE:	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��
		sprintf(Text, GlobalText[1674], Value );
		break;
	case AT_RECOVER_FULL_MANA:	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��
		sprintf(Text, GlobalText[1675], Value );
		break;
	case AT_SKILL_SUMMON_EXPLOSION:
		sprintf(Text, GlobalText[1695], iMana );
		break;
	case AT_SKILL_SUMMON_REQUIEM:
		sprintf(Text, GlobalText[1696], iMana );
		break;
#ifdef ASG_ADD_SUMMON_RARGLE
	case AT_SKILL_SUMMON_POLLUTION:
		sprintf(Text, GlobalText[1789], iMana );
		break;
#endif	// ASG_ADD_SUMMON_RARGLE
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case AT_SKILL_THRUST:
		GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[3153], iMana);
		break;
	case AT_SKILL_STAMP:
		GetSkillInformation( Option, 1, NULL, &iMana, NULL);
        sprintf(Text,GlobalText[3154], iMana);
		break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
    }
}



//////////////////////////////////////////////////////////////////////////
//  �������� ���� ���.
//////////////////////////////////////////////////////////////////////////
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
void RenderItemInfo(int sx,int sy,ITEM *ip,bool Sell, int Inventype, bool bItemTextListBoxUse)
#else	// ASG_ADD_NEW_QUEST_SYSTEM
void RenderItemInfo(int sx,int sy,ITEM *ip,bool Sell, int Inventype)
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
{
	if (ip->Type == -1)
		return;

#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
	// �Ⱓ�� �������϶� �ð����. (�Ⱓ�� �ð� ������ ���� ������ render���� �ʴ´�.)
	tm* ExpireTime;
#ifdef KJH_FIX_EXPIRED_PERIODITEM_TOOLTIP
	if( ip->bPeriodItem == true && ip->bExpiredPeriod == false)
#else // KJH_FIX_EXPIRED_PERIODITEM_TOOLTIP
	if( ip->bPeriodItem == true )
#endif // KJH_FIX_EXPIRED_PERIODITEM_TOOLTIP
	{
		_tzset();
		if( ip->lExpireTime == 0 )
			return;

#ifdef _VS2008PORTING
		ExpireTime = localtime((time_t*)&(ip->lExpireTime));
#else // _VS2008PORTING
		ExpireTime = localtime(&(ip->lExpireTime));
#endif // _VS2008PORTING
	}
#endif	// KJH_ADD_PERIOD_ITEM_SYSTEM
	
	ITEM_ATTRIBUTE *p = &ItemAttribute[ip->Type];
	TextNum = 0;
	SkipNum = 0;

	ZeroMemory( TextListColor, 20 * sizeof ( int));
	for(int i=0;i<30;i++)
	{
		TextList[i][0] = NULL;
	}

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
#ifdef PET_SYSTEM
	if ( ip->Type==ITEM_HELPER+4 || ip->Type==ITEM_HELPER+5 ) 
	{
#ifdef PBG_FIX_DARKPET_TIPUPDATE
		BYTE PetType = PET_TYPE_DARK_SPIRIT;
		if(ip->Type==ITEM_HELPER+4)
		{
			PetType = PET_TYPE_DARK_HORSE;
#ifdef PBG_FIX_PETTIP
			if((g_pMyInventory->GetPointedItemIndex()) == EQUIPMENT_HELPER)
#endif //PBG_FIX_PETTIP
				SendRequestPetInfo(PetType, Inventype, EQUIPMENT_HELPER);
		}
		else
#ifdef PBG_FIX_PETTIP
			if((g_pMyInventory->GetPointedItemIndex()) == EQUIPMENT_WEAPON_LEFT)
#endif //PBG_FIX_PETTIP
			SendRequestPetInfo(PetType, Inventype, EQUIPMENT_WEAPON_LEFT);
#endif //PBG_FIX_DARKPET_TIPUPDATE
		giPetManager::RenderPetItemInfo( sx, sy, ip, Inventype );
		return;
	}
#endif// PET_SYSTEM
#else // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
#ifdef PET_SYSTEM
    if ( giPetManager::RenderPetItemInfo( sx, sy, ip, Sell ) ) return;
#endif// PET_SYSTEM
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.

	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	int Level = (ip->Level>>3)&15;
	int Color;

    //  ������ ��.
	if(ip->Type==ITEM_POTION+13 || ip->Type==ITEM_POTION+14 || ip->Type==ITEM_WING+15 || ip->Type==ITEM_POTION+31 ||	// ��ȣ�Ǻ���
		(COMGEM::isCompiledGem(ip)) ||
		ip->Type == ITEM_POTION+65 || ip->Type == ITEM_POTION+66 || ip->Type == ITEM_POTION+67 ||	// ����������Ʈ�� �Ҳ�, �︶�̳��� ��, ����Ǻһ����� ����
		ip->Type == ITEM_POTION+68 ||	// �ɿ��Ǵ�����
		ip->Type==ITEM_HELPER+52 || ip->Type==ITEM_HELPER+53 ||	// �ܵ��� ���� �Ҳ�
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
		ip->Type==ITEM_POTION+100 ||	//����� ����
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef PBG_ADD_GENSRANKING
		(ip->Type >= ITEM_POTION+141 && ip->Type <= ITEM_POTION+144) ||
#endif //PBG_ADD_GENSRANKING

#ifdef LEM_ADD_LUCKYITEM
		(ip->Type >= ITEM_HELPER+135 && ip->Type <= ITEM_HELPER+145) ||
		(ip->Type == ITEM_POTION+160 || ip->Type == ITEM_POTION+161) ||
#endif // LEM_ADD_LUCKYITEM
		ip->Type==ITEM_POTION+16 || ip->Type==ITEM_POTION+22 )  //  �ູ�� ���� ~ â���� ����.
	{
		Color = TEXT_COLOR_YELLOW;
	}
    //  ��õ���� ���빫��.
    else if ( ip->Type==ITEM_STAFF+10 || ip->Type==ITEM_SWORD+19 || ip->Type==ITEM_BOW+18 || ip->Type==ITEM_MACE+13)
    {
        Color = TEXT_COLOR_PURPLE;
    }
	else if(ip->Type==ITEM_POTION+17 || ip->Type==ITEM_POTION+18 || ip->Type==ITEM_POTION+19)	// ���������� ���� ������
	{
		Color = TEXT_COLOR_YELLOW;
	}
    else if( ip->Type==ITEM_HELPER+16 || ip->Type==ITEM_HELPER+17 )
    {
        Color = TEXT_COLOR_YELLOW;
    }
    else if ( (ip->ExtOption%0x04)==EXT_A_SET_OPTION || (ip->ExtOption%0x04)==EXT_B_SET_OPTION )
    {
        Color = TEXT_COLOR_GREEN_BLUE;
    }
#ifdef _PVP_ADD_MOVE_SCROLL
    else if( ip->Type==ITEM_POTION+10 )
    {
        Color = TEXT_COLOR_WHITE;
    }
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef _PVP_MURDERER_HERO_ITEM
    else if( ip->Type==ITEM_POTION+30 )
    {
        Color = TEXT_COLOR_WHITE;
    }
#endif	// _PVP_MURDERER_HERO_ITEM
#ifdef SOCKET_SYSTEM
    else if( g_SocketItemMgr.IsSocketItem(ip) )
    {
        Color = TEXT_COLOR_VIOLET;
    }
#endif	// SOCKET_SYSTEM
	else if(ip->SpecialNum > 0 && (ip->Option1&63) > 0)
	{
		Color = TEXT_COLOR_GREEN;
	}
	else if(Level >= 7)
	{
		Color = TEXT_COLOR_YELLOW;
	}
	else
	{
		if(ip->SpecialNum > 0)
		{
   			Color = TEXT_COLOR_BLUE;
		}
		else
		{
			Color = TEXT_COLOR_WHITE;
		}
	}

    if ( ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 ) || ip->Type==ITEM_HELPER+30 
		|| ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )
#ifdef ADD_ALICE_WINGS_1
		|| (ip->Type>=ITEM_WING+42 && ip->Type<=ITEM_WING+43)
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)  //  ������ ���� ~ ������ ����. ����, ��ǳ�� ���� ~ ������ ����, ��ȯ���� 2,3�� ����.
    {
	    if ( Level >= 7 )
	    {
		    Color = TEXT_COLOR_YELLOW;
	    }
	    else
	    {
		    if(ip->SpecialNum > 0)
		    {
   			    Color = TEXT_COLOR_BLUE;
		    }
		    else
		    {
			    Color = TEXT_COLOR_WHITE;
		    }
	    }
    }

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// �κ��丮 ������ ���� �� ����
	int nGemType = COMGEM::Check_Jewel( ip->Type );
	if( nGemType != COMGEM::NOGEM)
	{
		Color = TEXT_COLOR_YELLOW;
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

    //  �������� ����.

// wani �κ� ����ȭ �����۵� IsSellingBan ���⿡ �߰� �Ͽ���

	if ( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) && !IsSellingBan(ip) )
	{
		char Text[100];
#ifndef KJH_DEL_PC_ROOM_SYSTEM				// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
		CPCRoomPtSys& rPCRoomPtSys = CPCRoomPtSys::Instance();
		if (rPCRoomPtSys.IsPCRoomPointShopMode())
		{
			if (Sell)    //  ���� ����.
			{
#ifdef ASG_PCROOM_POINT_SYSTEM_MODIFY
				// 2331 "���� ���� : %d ����Ʈ"
				::sprintf(TextList[TextNum], GlobalText[2331], ItemValue(ip, 0));
#else	// ASG_PCROOM_POINT_SYSTEM_MODIFY
				// 2331 "���� ���� : %d ����Ʈ (���� ���� : %d �̻�)"
				::sprintf(TextList[TextNum], GlobalText[2331],
					ItemValue(ip, 0), GetItemBuyingTermsPoint(ip));
#endif	// ASG_PCROOM_POINT_SYSTEM_MODIFY
				TextListColor[TextNum] = Color;
				++TextNum;

				::sprintf(TextList[TextNum],"\n");
				++TextNum;
				++SkipNum;
			}
		}
		else
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
		{
			if(Sell)    //  ���� ����.
			{
				DWORD dwValue = ItemValue(ip, 0);
				ConvertGold(dwValue, Text);
				char Text2[100];

				// �������� ǥ��
				ConvertTaxGold(ItemValue(ip,0),Text2);
				sprintf(TextList[TextNum],GlobalText[1620],Text2,Text);	// 1620 "���� ����: %s(%s)"
			}
			else        //  �Ǹ� ����.
			{
				ConvertGold(ItemValue(ip,1),Text);
				sprintf(TextList[TextNum],GlobalText[63],Text);
			}

			TextListColor[TextNum] = Color;
//			TextBold[TextNum] = true;
			TextNum++;
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
		}
	}
		if(	(Inventype == SEASON3B::TOOLTIP_TYPE_MY_SHOP || Inventype == SEASON3B::TOOLTIP_TYPE_PURCHASE_SHOP)
			&& !IsPersonalShopBan(ip) )
	{
		//. ��ϵ� ��ǰ�� �ѿ����� ����Ѵ�
		{
			int price = 0;
			int indexInv = (MAX_EQUIPMENT + MAX_INVENTORY)+(ip->y*COL_PERSONALSHOP_INVEN)+ip->x;
			char Text[100];

			if(GetPersonalItemPrice(indexInv, price, g_IsPurchaseShop)) 
			{
				ConvertGold(price, Text);
				sprintf(TextList[TextNum], GlobalText[63],Text);
				
				if ( price>=10000000 )        //  ����.
					TextListColor[TextNum] = TEXT_COLOR_RED;
				else if ( price>=1000000 )    //  ��Ȳ.
					TextListColor[TextNum] = TEXT_COLOR_YELLOW;
				else if( price>=100000 )      //  ���.
					TextListColor[TextNum] = TEXT_COLOR_GREEN;
				else
					TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = true;
				TextNum++;
				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
				
				DWORD gold = CharacterMachine->Gold;
#ifdef _VS2008PORTING
				if((int)gold < price && g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE) 
#else // _VS2008PORTING
				if(gold < price && g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE) 
#endif // _VS2008PORTING
				{
					TextListColor[TextNum] = TEXT_COLOR_RED;
					TextBold[TextNum] = true;
					sprintf(TextList[TextNum], GlobalText[423]);
					TextNum++;
					sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
				}
			}
			else if(g_IsPurchaseShop == PSHOPWNDTYPE_SALE)
			{
				TextListColor[TextNum] = TEXT_COLOR_RED;
				TextBold[TextNum] = true;
				sprintf(TextList[TextNum], GlobalText[1101]);
				TextNum++;
				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			}
		}
	}

    //  �������� �̸�.
    if (ip->Type>=ITEM_POTION+23 && ip->Type<=ITEM_POTION+26 )   //  ����Ʈ ������.
    {
		if(ip->Type == ITEM_POTION+23)	//. ������ ��, �����ǹ���
		{
			Color = TEXT_COLOR_YELLOW;
			switch( Level )
			{
			case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;	//. ������ ��
			case 1: sprintf ( TextList[TextNum], GlobalText[906] ); break;  //  ������ ����
			}
		}
		else if(ip->Type == ITEM_POTION+24)	//. �η�����, ��ũ����
		{
			Color = TEXT_COLOR_YELLOW;
			switch( Level )
			{
			case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;	//. �η�����
			case 1: sprintf ( TextList[TextNum], GlobalText[907] ); break;  //  ��ũ����
			}
		}
		else{
			sprintf(TextList[TextNum],"%s", p->Name);
			Color = TEXT_COLOR_YELLOW;
		}
    }
	else if(ip->Type == ITEM_POTION+12)//�̹�Ʈ ������
	{
		switch(Level)
		{
		case 0:sprintf(TextList[TextNum],GlobalText[100]);break;
		case 1:sprintf(TextList[TextNum],GlobalText[101]);break;
		case 2:sprintf(TextList[TextNum],"%s",ChaosEventName[ip->Durability]);break;
		}
	}
	else if(ip->Type == ITEM_POTION+11)//����� ����/��ź�Ǻ�/����/���� �ָӴ�./����� ��Ʈ//����
	{
		switch(Level)
		{
		case 0:sprintf(TextList[TextNum],"%s",p->Name);break;
		case 1:sprintf(TextList[TextNum],GlobalText[105]);break;
		case 2:sprintf(TextList[TextNum],GlobalText[106]);break;
		case 3:sprintf(TextList[TextNum],GlobalText[107]);break;
		case 5:sprintf(TextList[TextNum],GlobalText[109]);break;
		case 6:sprintf(TextList[TextNum],GlobalText[110]);break;
        case 7:sprintf(TextList[TextNum],GlobalText[111]);break; //  õ���� ����.
#ifdef USE_EVENT_ELDORADO
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:	// õ���� ����
			sprintf(TextList[TextNum],"%s +%d",GlobalText[115], Level - 7);
			break;
#endif
		case 13:	// ��ũ�ε��� ����
			sprintf(TextList[TextNum],GlobalText[117]);
			break;
#ifdef NEW_YEAR_BAG_EVENT
        case 14:    //  ���ָӴ�.
            sprintf(TextList[TextNum],GlobalText[1650]);
            break;

        case 15:
            sprintf(TextList[TextNum],GlobalText[1651]);
            break;
#else 
    #ifdef CHINA_MOON_CAKE
        case 14:    //  �߱� ����.
            sprintf(TextList[TextNum],GlobalText[118]);
            break;
    #endif// CHINA_MOON_CAKE
#endif// NEW_YEAR_BAG_EVENT
		}
	}
#ifdef ANNIVERSARY_EVENT
	else if(ip->Type == ITEM_POTION+20)	//����� ����
	{
		switch(Level)
		{
        case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;
        case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			sprintf ( TextList[TextNum], "%s +%d", GlobalText[116], Level );     //  �ִϹ����� �ڽ�
			break;
        }
    }
#endif	// ANNIVERSARY_EVENT
#ifdef _PVP_ADD_MOVE_SCROLL
    else if (ip->Type == ITEM_POTION+10)//  �̵�����
    {
        switch (Level)
        {
        case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;
        case 1: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[30] ); break;     //  �η��þ�
		case 2: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[33] ); break;     //  �븮��
		case 3: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[32] ); break;     //  ����ƽ�
		case 4: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[31] ); break;     //  ����
		case 5: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[37] ); break;     //  ��Ʋ����
		case 6: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[34] ); break;     //  �ν�ƮŸ��
		case 7: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[38] ); break;     //  Ÿ��ĭ
		case 8: sprintf ( TextList[TextNum], GlobalText[158], GlobalText[55] ); break;     //  ��ī�罺
        }
    }
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef _PVP_MURDERER_HERO_ITEM
    else if ( ip->Type==ITEM_POTION+30 )//  �������θ�¡ǥ(inv)
    {
		if (ip->Durability % 100 < 3) Color = TEXT_COLOR_WHITE;
		else Color = TEXT_COLOR_WHITE;

		sprintf ( TextList[TextNum], "%s", p->Name );
	}
#endif	// _PVP_MURDERER_HERO_ITEM
	else if(ip->Type == ITEM_POTION+12)//�̹�Ʈ ������
	{
		switch(Level)
		{
		case 0:sprintf(TextList[TextNum],GlobalText[100]);break;
		case 1:sprintf(TextList[TextNum],GlobalText[101]);break;
		case 2:sprintf(TextList[TextNum],"%s",ChaosEventName[ip->Durability]);break;
		}
	}
    else if ( ip->Type==ITEM_HELPER+15 )//  ��Ŭ. ( ������/ü��/��ø/��/��� )
    {
        Color = TEXT_COLOR_YELLOW;
        switch ( Level )
        {
        case 0:sprintf(TextList[TextNum],"%s %s", GlobalText[168], p->Name );break;
        case 1:sprintf(TextList[TextNum],"%s %s", GlobalText[169], p->Name );break;
        case 2:sprintf(TextList[TextNum],"%s %s", GlobalText[167], p->Name );break;
        case 3:sprintf(TextList[TextNum],"%s %s", GlobalText[166], p->Name );break;
		case 4:sprintf(TextList[TextNum],"%s %s", GlobalText[1900], p->Name );break;// ��ֿ���
        }
    }
    else if ( ip->Type==ITEM_HELPER+14 )//  ��ũ�� ����.
    {
        Color = TEXT_COLOR_YELLOW;
        switch ( Level )
        {
        case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;            //  ��ũ�� ����.
        case 1: sprintf ( TextList[TextNum], "%s", GlobalText[1235] ); break;   //  ������ �Ҹ�.
        }
    }
    else if ( ip->Type==ITEM_POTION+21 )    //  ����. ( 1:����).
    {
        Color = TEXT_COLOR_YELLOW;
        switch ( Level )
        {
        case 0: sprintf ( TextList[TextNum], "%s", p->Name ); break;
        case 1: sprintf ( TextList[TextNum], GlobalText[810] ); break;      //  ����.
#ifdef FRIEND_EVENT
        case 2: sprintf ( TextList[TextNum], GlobalText[1098] ); break;     //  ������ ��.
#endif// FRIEND_EVENT
        case 3: sprintf ( TextList[TextNum], GlobalText[1290] ); break;     //  ������ǥ��
        }
    }
    else if ( ip->Type==ITEM_HELPER+19 )    //  0:��õ���� ����������, 1: ��õ���� �����, 2: ��õ���� ���뼮�� ).
    {
        Color = TEXT_COLOR_YELLOW;
        switch ( Level )
        {
        case 0: sprintf ( TextList[TextNum], GlobalText[811] ); break;  //  ��õ���� ���� ������.
        case 1: sprintf ( TextList[TextNum], GlobalText[812] ); break;  //  ��õ���� ���� ��.
        case 2: sprintf ( TextList[TextNum], GlobalText[817] ); break;  //  ��õ���� ���� ����.
        }
    }
	else if(ip->Type == ITEM_HELPER+20)
	{
		Color = TEXT_COLOR_YELLOW;
		switch( Level )
		{
		case 0: sprintf( TextList[TextNum], p->Name ); break;	//. �������� ����
		case 1: sprintf( TextList[TextNum], GlobalText[922] ); break;	//. ������ ����
        case 2: sprintf( TextList[TextNum], GlobalText[928] ); break;	//. ������ ����
        case 3: sprintf ( TextList[TextNum], GlobalText[929] ); break;  //  ������ ����.
		}
	}
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	else if(ip->Type == ITEM_HELPER+107)		// ġ��������
	{
		Color = TEXT_COLOR_YELLOW;
		sprintf( TextList[TextNum], p->Name );
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
    else if ( ip->Type==ITEM_POTION+7 ) //  ���м� ����.//���ƹ���
    {
        switch ( Level )
        {
        case 0: sprintf( TextList[TextNum], GlobalText[1413] ); break;
        case 1: sprintf( TextList[TextNum], GlobalText[1414] ); break;
        }
    }
    else if ( ip->Type==ITEM_HELPER+7 ) //  ��� ����
    {
        switch ( Level )
        {
        case 0: sprintf( TextList[TextNum], GlobalText[1460] ); break;  //  Ȱ �뺴.
        case 1: sprintf( TextList[TextNum], GlobalText[1461] ); break;  //  â �뺴.
        }
    }
    else if ( ip->Type==ITEM_HELPER+11 )    //  �ֹ���.
    {
        switch ( Level )
        {
        case 0: sprintf( TextList[TextNum], GlobalText[1416] ); break;  //  ����� �ֹ���.
        case 1: sprintf( TextList[TextNum], GlobalText[1462] ); break;  //  ������ ���� ��ġ.
        }
    }
	else if ( ip->Type==ITEM_POTION+9 ) //  ��, ����� �ø���
	{
		switch(Level)
		{
		case 0:sprintf(TextList[TextNum],"%s",p->Name);break;
		case 1:sprintf(TextList[TextNum],GlobalText[108]);break;
		}
	}
    else if(ip->Type == ITEM_WING+11)//��ȯ����
	{
		sprintf(TextList[TextNum],"%s %s",SkillAttribute[30+Level].Name,GlobalText[102]);
	}
    else if(ip->Type == ITEM_HELPER+10)//���Ź���
	{
		for(int i=0;i<MAX_MONSTER;i++)
		{
			if(SommonTable[Level] == MonsterScript[i].Type)
			{
        		sprintf(TextList[TextNum],"%s %s",MonsterScript[i].Name,GlobalText[103]);
				break;
			}
		}
	}
    else if ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )  //  ������ ���� ~ ����� ����.
    {
		if(Level==0)
			sprintf(TextList[TextNum],"%s",p->Name);
		else
			sprintf(TextList[TextNum],"%s +%d",p->Name,Level);
    }
#ifdef ADD_ALICE_WINGS_1
	else if ((ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40) || (ip->Type>=ITEM_WING+42 && ip->Type<=ITEM_WING+43)
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)  //  ��ǳ�� ���� ~ ������ ����, ��ȯ���� 2,3�� ����
#else	// ADD_ALICE_WINGS_1
	else if ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )  //  ��ǳ�� ���� ~ ������ ����
#endif	// ADD_ALICE_WINGS_1
    {
		if(Level==0)
			sprintf(TextList[TextNum],"%s",p->Name);
		else
			sprintf(TextList[TextNum],"%s +%d",p->Name,Level);
    }
    else if ( ip->Type==ITEM_HELPER+31 )    //  ��ȥ.
    {
        switch ( Level )
        {
#if SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		case 0: sprintf ( TextList[TextNum], "%s of %s", p->Name, GlobalText[1187] ); break;
        case 1: sprintf ( TextList[TextNum], "%s of %s", p->Name, GlobalText[1214] ); break;
#else // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		// �ѱ�
        case 0: sprintf ( TextList[TextNum], "%s %s", GlobalText[1187], p->Name ); break;
        case 1: sprintf ( TextList[TextNum], "%s %s", GlobalText[1214], p->Name ); break;
#endif // SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
        }
    }
    else if ( ip->Type==ITEM_HELPER+30 )      //  ������ ����.
    {
		if ( Level==0 )
			sprintf ( TextList[TextNum], "%s", p->Name );
		else
			sprintf ( TextList[TextNum], "%s +%d", p->Name, Level );
    }
    else if ( ip->Type==ITEM_POTION+29 )    //  ����� ǥ��.
    {
        sprintf ( TextList[TextNum], GlobalText[1180], Level );
    }
    else if ( ip->Type==ITEM_POTION+28 )    //  �Ҿ���� ����.
    {
        Color = TEXT_COLOR_YELLOW;
        sprintf ( TextList[TextNum], "%s +%d", p->Name, Level );
    }
#ifdef MYSTERY_BEAD
	else if( ip->Type==ITEM_WING+26 )		//. �ź��Ǳ���
	{
		Color = TEXT_COLOR_YELLOW;
		switch(Level)
		{
		case 0:		//. �ź��Ǳ���
			sprintf( TextList[TextNum], "%s", p->Name); break;
		case 1:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[1831]); break;
		case 2:		//. �Ķ�����
			sprintf( TextList[TextNum], "%s", GlobalText[1832]); break;
		case 3:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[1833]); break;
		case 4:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[1834]); break;
		case 5:		//. ��¦����
			sprintf( TextList[TextNum], "%s", GlobalText[1838]); break;
		}
	}
#endif // MYSTERY_BEAD
	else if(ip->Type == ITEM_WING+32)//������������.(x-mas�̺�Ʈ��)
	{
		sprintf(TextList[TextNum], "%s", p->Name);	
	}
	else if(ip->Type == ITEM_WING+33)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		sprintf(TextList[TextNum], "%s", p->Name);	
	}
	else if(ip->Type == ITEM_WING+34)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		sprintf(TextList[TextNum], "%s", p->Name);	
	}
	else if(ip->Type == ITEM_WING+35)
	{
		sprintf(TextList[TextNum], "%s", p->Name);	
	}
#ifdef HELLOWIN_EVENT
	else if(ip->Type >= ITEM_POTION+45 && ip->Type <= ITEM_POTION+50)//�ҷ������� �̺�Ʈ
	{
		sprintf ( TextList[TextNum], "%s", p->Name );
	}
#endif //#ifdef HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	else if(ip->Type == ITEM_POTION+32)//��ȫ ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(Level)
		{
		case 0:		//. �ź��Ǳ���
			sprintf( TextList[TextNum], "%s", p->Name); break;
		case 1:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[2012]); break;
		}
	}
	else if(ip->Type == ITEM_POTION+33)//���� ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(Level)
		{
		case 0:		//. �ź��Ǳ���
			sprintf( TextList[TextNum], "%s", p->Name); break;
		case 1:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[2013]); break;
		}
	}
	else if(ip->Type == ITEM_POTION+34)//�Ķ� ���ݸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		switch(Level)
		{
		case 0:		//. �ź��Ǳ���
			sprintf( TextList[TextNum], "%s", p->Name); break;
		case 1:		//. ��������
			sprintf( TextList[TextNum], "%s", GlobalText[2014]); break;
		}
	}
#endif
	else if(ip->Type >= ITEM_HELPER+32 && ip->Type <= ITEM_HELPER+37)	
	{
		if(ip->Type == ITEM_HELPER+37)	// �渱�� ���Ǹ�
		{
			Color = TEXT_COLOR_BLUE;
			if((ip->Option1&63) == 0x01)
				sprintf(TextList[TextNum], "%s %s", p->Name, GlobalText[1863]);
			else if((ip->Option1&63) == 0x02)
				sprintf(TextList[TextNum], "%s %s", p->Name, GlobalText[1864]);
			else if((ip->Option1&63) == 0x04)
				sprintf(TextList[TextNum], "%s %s", p->Name, GlobalText[1866]);
			else
				sprintf(TextList[TextNum], "%s", p->Name);
		}
		else
		{
			Color = TEXT_COLOR_WHITE;
			sprintf(TextList[TextNum], "%s", p->Name);	
		}
	}
	else if ( ip->Type==ITEM_SWORD+19 || ip->Type==ITEM_BOW+18 || ip->Type==ITEM_STAFF+10 || ip->Type==ITEM_MACE+13) //	��õ���� ���� ����.
	{
		if(Level==0)
			sprintf(TextList[TextNum],"%s",p->Name);
		else
			sprintf(TextList[TextNum],"%s +%d",p->Name,Level);
	}
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// �κ��丮 ���� ���� �̸� �ؽ�Ʈ
	else if( nGemType != COMGEM::NOGEM && nGemType%2 == 1 )
	{
		int nGlobalIndex = COMGEM::GetJewelIndex( nGemType , COMGEM::eGEM_NAME );
		sprintf(TextList[TextNum],"%s +%d", GlobalText[nGlobalIndex], Level+1);
	}
#else // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if ( ip->Type==INDEX_COMPILED_CELE)
	{
		sprintf(TextList[TextNum],"%s +%d", GlobalText[1806], Level+1);
	}
	else if ( ip->Type==INDEX_COMPILED_SOUL)
	{
		sprintf(TextList[TextNum],"%s +%d", GlobalText[1807], Level+1);
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if( ip->Type == ITEM_POTION + 41 || ip->Type == ITEM_POTION + 42 ||
			 ip->Type == ITEM_POTION + 43 || ip->Type == ITEM_POTION + 44 ||
			 ip->Type == ITEM_HELPER + 38
		    ) 
	{
		sprintf(TextList[TextNum],"%s",p->Name);
		Color = TEXT_COLOR_YELLOW;
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if ((ip->Type >= ITEM_WING+60 && ip->Type <= ITEM_WING+65)	// �õ�
		|| (ip->Type >= ITEM_WING+70 && ip->Type <= ITEM_WING+74)	// ���Ǿ�
		|| (ip->Type >= ITEM_WING+100 && ip->Type <= ITEM_WING+129))	// �õ彺�Ǿ�
	{
		sprintf(TextList[TextNum],"%s",p->Name);
		Color = TEXT_COLOR_VIOLET;
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
    else if ( ip->Type==ITEM_POTION+111 )    // �����Ǹ���
    {
        Color = TEXT_COLOR_YELLOW;
        sprintf ( TextList[TextNum], "%s", p->Name );
    }
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	else if( ITEM_POTION+101 <= ip->Type && ip->Type <= ITEM_POTION+109 )
	{
        Color = TEXT_COLOR_YELLOW;
        sprintf ( TextList[TextNum], "%s", p->Name );
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
	else
	{
		char TextName[64];
		if ( g_csItemOption.GetSetItemName( TextName, ip->Type, ip->ExtOption ) )
		{
			strcat ( TextName, p->Name );
		}
		else
		{
			strcpy ( TextName, p->Name );
		}

		if((ip->Option1&63) > 0)
		{
			if(Level==0)
				sprintf(TextList[TextNum],"%s %s", GlobalText[620], TextName);
			else
				sprintf(TextList[TextNum],"%s %s +%d", GlobalText[620], TextName,Level);
		}
		else
		{
			if(Level==0)
				sprintf(TextList[TextNum],"%s",TextName);
			else
				sprintf(TextList[TextNum],"%s +%d",TextName,Level);
		}
	}

	TextListColor[TextNum] = Color;TextBold[TextNum] = true;TextNum++;
	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

    if ( ip->Type==ITEM_HELPER+19)    // 0: ��õ���� ����������, 1: ��õ���� �����, 2: ��õ���� ���뼮�� ).
    {
        int iMana;
        int iWeaponSpeed;
        int iNeedStrength;
        int iNeedDex;

        TextListColor[TextNum] = TEXT_COLOR_WHITE;
		sprintf ( TextList[TextNum], GlobalText[730] ); TextBold[TextNum] = false; TextNum++;

        TextListColor[TextNum] = TEXT_COLOR_DARKRED;
        sprintf ( TextList[TextNum], GlobalText[815] ); TextBold[TextNum] = false; TextNum++;
        sprintf ( TextList[TextNum], "\n" ); TextBold[TextNum] = false; TextNum++; SkipNum++;

        //  �ɼ�.
        switch ( Level )
        {
        case 0: //  ��õ���� ����������.
    		sprintf ( TextList[TextNum], "%s: %d ~ %d", GlobalText[42], 107, 110 );  TextListColor[TextNum] = TEXT_COLOR_WHITE; TextBold[TextNum] = false; TextNum++;    //  ���ݷ�.
            iWeaponSpeed  = 20;
            iNeedStrength = 132;
            iNeedDex      = 32;
            break;  
        case 1: //  ��õ���� �����.
    		sprintf ( TextList[TextNum], "%s: %d ~ %d", GlobalText[40], 110, 120 );  TextListColor[TextNum] = TEXT_COLOR_WHITE; TextBold[TextNum] = false; TextNum++;    //  ���ݷ�.
            iWeaponSpeed  = 35;
            iNeedStrength = 381;
            iNeedDex      = 149;
            break;
        case 2: //  ��õ���� ���뼮��.
    		sprintf ( TextList[TextNum], "%s: %d ~ %d", GlobalText[41], 120, 140 );  TextListColor[TextNum] = TEXT_COLOR_WHITE; TextBold[TextNum] = false; TextNum++;    //  ���ݷ�.
            iWeaponSpeed  = 35;
            iNeedStrength = 140;
            iNeedDex      = 350;
            break;  
        }

        //  ���� �ӵ�.
    	sprintf ( TextList[TextNum], GlobalText[64], iWeaponSpeed ); TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        //  �䱸��.
        sprintf ( TextList[TextNum], GlobalText[73], iNeedStrength );TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        //  �䱸 ��ø.
        sprintf ( TextList[TextNum], GlobalText[75], iNeedDex );     TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        sprintf ( TextList[TextNum], "\n" ); TextBold[TextNum] = false; TextNum++; SkipNum++;

        //  ���.
		sprintf ( TextList[TextNum], GlobalText[87] );     TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;
		sprintf ( TextList[TextNum], GlobalText[94], 20 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;

        //  ��ų, �׼���Ʈ.
        switch ( Level )
        {
        case 0: //  ��õ���� ����������.
            {
		        sprintf ( TextList[TextNum], GlobalText[79], 53 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = true; TextNum++;   //  ���� ���.
                sprintf ( TextList[TextNum], GlobalText[631] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���� ����(����)
		        sprintf ( TextList[TextNum], GlobalText[632], 2 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���� ����(�ۼ�Ʈ)
            }
            break;  
        case 1: //  ��õ���� �����.
            {
                GetSkillInformation ( AT_SKILL_SWORD4, 1, NULL, &iMana, NULL );
			    sprintf ( TextList[TextNum], GlobalText[84], iMana ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++; //  ����ġ�� ��ų.
                sprintf ( TextList[TextNum], GlobalText[629] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���ݷ� ����(����)
                sprintf ( TextList[TextNum], GlobalText[630], 2 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���ݷ� ����(2�ۼ�Ʈ)
            }
            break;
        case 2: //  ��õ���� ���뼮��.
            {
			    GetSkillInformation ( AT_SKILL_CROSSBOW, 1, NULL, &iMana, NULL );
			    sprintf ( TextList[TextNum], GlobalText[86], iMana ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++; //  �ٹ߽�ų.
                sprintf ( TextList[TextNum], GlobalText[629] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���ݷ� ����(����)
                sprintf ( TextList[TextNum], GlobalText[630], 2 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //���ݷ� ����(2�ۼ�Ʈ)
           }
            break;  
        }
        sprintf ( TextList[TextNum], GlobalText[628] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //�׼���Ʈ ������ ����
		sprintf ( TextList[TextNum], GlobalText[633], 7 ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;//���� �ӵ�
		sprintf ( TextList[TextNum], GlobalText[634] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //ȹ�� �����
		sprintf ( TextList[TextNum], GlobalText[635] ); TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;   //ȹ�� ����

    }

    //  �ɼǵ� �̸��� Ư¡.
    if (ip->Type>=ITEM_POTION+23 && ip->Type<=ITEM_POTION+26 )   //  ����Ʈ ������.
    {
		sprintf(TextList[TextNum],GlobalText[730]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[731]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[732]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
    }
	else if(ip->Type == ITEM_POTION+12)//�̹�Ʈ ������
	{
		if(Level <= 1)
		{
			sprintf(TextList[TextNum],GlobalText[119]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}
#ifdef CSK_FREE_TICKET
	// ��������� ������ ����
	else if(ip->Type >= ITEM_HELPER+46 && ip->Type <= ITEM_HELPER+48)
	{
		int iMap = 0;
		if(ip->Type == ITEM_HELPER+46)	// ���������� ���������
			iMap = 39;	// 39 "�Ǹ��� ����"	
		else if(ip->Type == ITEM_HELPER+47)	// ����ĳ�� ���������
			iMap = 56;	// 56 "���� ĳ��"
		else if(ip->Type == ITEM_HELPER+48)	// Į���� ���������
			iMap = 58;	// 58 "Į����"

		// 2259 "%s ����� ������ Ƚ����ŭ ����� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2259], GlobalText[iMap]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
#ifndef LDK_FIX_TICKET_INFO
		if(ip->Type == ITEM_HELPER+48)	// Į���� ���������
#endif //LDK_FIX_TICKET_INFO
		{
			// 2270 "���� ������ ������ ���߾� �ڵ� ����˴ϴ�."
			sprintf(TextList[TextNum], GlobalText[2270]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
		}

		// ��ĭ �߰�
		sprintf(TextList[TextNum], "\n");
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // CSK_FREE_TICKET

#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ��������� ������ ����
	else if(ip->Type >= ITEM_HELPER+125 && ip->Type <= ITEM_HELPER+127)
	{
		int iMap = 0;
		if(ip->Type == ITEM_HELPER+125)			// ���ð��� ���������
			iMap = 3057;	// 3057 "���ð���"	
		else if(ip->Type == ITEM_HELPER+126)	// �ٸ�ī ���������
			iMap = 2806;	// 2806 "�ٸ�ī"
		else if(ip->Type == ITEM_HELPER+127)	// �ٸ�ī ��7��  ���������
			iMap = 3107;	// 3107 "�ٸ�ī ��7��"
		
		// 2259 "%s ����� ������ Ƚ����ŭ ����� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2259], GlobalText[iMap]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ��ĭ �߰�
		sprintf(TextList[TextNum], "\n");
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH

#ifdef CSK_CHAOS_CARD
	// ī����ī�� ������ ����
	else if(ip->Type == ITEM_POTION+54)
	{
		// 2261 "ī����ī�� ������ ���� Ư���� �������� ȹ���� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2261]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
	// ��;����� ������ ����
	else if(ip->Type >= ITEM_POTION+58 && ip->Type <= ITEM_POTION+62)
	{
		// 2269 "�����մϴ�. ����� ������ �� ���������� ��ȯ�� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2269]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // CSK_RARE_ITEM
#ifdef PSW_RARE_ITEM
	// ��;����� ������ ����
	else if(ip->Type == ITEM_POTION+83 )
	{
		// 2269 "�����մϴ�. ����� ������ �� ���������� ��ȯ�� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2269]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // PSW_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	// ��;����� ������ ����
	else if(ip->Type >= ITEM_POTION+145 && ip->Type <= ITEM_POTION+150)
	{
		// 2269 "�����մϴ�. ����� ������ �� ���������� ��ȯ�� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2269]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef CSK_LUCKY_CHARM
	else if( ip->Type == ITEM_POTION+53 )// ����� ����
	{
		sprintf(TextList[TextNum], GlobalText[2250]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
	else if( ip->Type == ITEM_HELPER+43 )
	{
		sprintf(TextList[TextNum], GlobalText[2256]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
#ifdef LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
#else
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA

#if !defined(PBG_WOPS_TEXT_MONMARK) || defined(PBG_FIX_SEALTOOLTIP_BUG_ENG)
		sprintf(TextList[TextNum], GlobalText[2567]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2568]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#else //!defined(PBG_WOPS_TEXT_MONMARK) || defined(PBG_FIX_SEALTOOLTIP_BUG_ENG)
		sprintf(TextList[TextNum], GlobalText[2612]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif //!defined(PBG_WOPS_TEXT_MONMARK) || defined(PBG_FIX_SEALTOOLTIP_BUG_ENG)
#endif // SELECTED_LANGUAGE != LANGUAGE_KOREAN
	}
	else if( ip->Type == ITEM_HELPER+44 )
	{
		sprintf(TextList[TextNum], GlobalText[2257]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
#ifdef LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
#else
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA

		sprintf(TextList[TextNum], GlobalText[2567]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum], GlobalText[2568]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif // SELECTED_LANGUAGE != LANGUAGE_KOREAN
	}
	else if( ip->Type == ITEM_HELPER+45 )
	{
		sprintf(TextList[TextNum], GlobalText[2258]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
#ifdef LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
#else
		sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA

		sprintf(TextList[TextNum], GlobalText[2566]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif // SELECTED_LANGUAGE != LANGUAGE_KOREAN
	}
#endif //CSK_LUCKY_SEAL	
#ifdef CSK_PCROOM_ITEM
	else if(ip->Type >= ITEM_POTION+55 && ip->Type <= ITEM_POTION+57)
	{
		// 571 "�ٴڿ� ������ ���̳� �������� ����"	// ���� ���.
		sprintf(TextList[TextNum],GlobalText[571]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	else if(ip->Type == ITEM_HELPER+96)		// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
	{
		// 2742 "������ ����" ���� "���ݷ°� ������ ���˴ϴ�"
		sprintf(TextList[TextNum],GlobalText[2742]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	else if(ip->Type >= ITEM_POTION+70 && ip->Type <= ITEM_POTION+71)
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		int index = ip->Type-(ITEM_POTION+70);

		sprintf(TextList[TextNum], GlobalText[2500+index]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	else if(ip->Type >= ITEM_POTION+72 && ip->Type <= ITEM_POTION+77)
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);

		sprintf(TextList[TextNum], GlobalText[2503+(ip->Type-(ITEM_POTION+72))],Item_data.m_byValue1);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2502]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
	else if(ip->Type == ITEM_HELPER+59)
	{
		sprintf(TextList[TextNum], GlobalText[2509]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
	else if( ip->Type >= ITEM_HELPER+54 && ip->Type <= ITEM_HELPER+58)
	{
		DWORD statpoint = 0;
		statpoint = ip->Durability*10;

		sprintf(TextList[TextNum], GlobalText[2511], statpoint );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2510]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
#ifdef LDS_ADD_NOTICEBOX_STATECOMMAND_ONLYUSEDARKLORD
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;
		sprintf(TextList[TextNum], GlobalText[1908]);	// 1908 "������ ������� ��밡��"
		TextNum++;
		
		if(ip->Type == ITEM_HELPER+58)	// ��ָ��¿����̸�?
		{
			if(GetBaseClass( Hero->Class ) == CLASS_DARK_LORD)
			{
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
			}
			else
			{
				TextListColor[TextNum] = TEXT_COLOR_DARKRED;
			}
			
			sprintf(TextList[TextNum],GlobalText[61], GlobalText[24]);
			TextNum++;
		}
#endif // LDS_ADD_NOTICEBOX_STATECOMMAND_ONLYUSEDARKLORD
	}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	else if(ip->Type >= ITEM_POTION+78 && ip->Type <= ITEM_POTION+82)
	{
		int index = ip->Type-(ITEM_POTION+78);
		DWORD value = 0;

		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
		value = Item_data.m_byValue1;

		sprintf( TextList[TextNum],GlobalText[2512+index], value );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2517]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2518]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#ifdef ASG_ADD_LEAP_OF_CONTROL_TOOLTIP_TEXT
		if( ip->Type == ITEM_POTION+82 )
		{
			sprintf(TextList[TextNum], GlobalText[3115]);
			TextListColor[TextNum] = TEXT_COLOR_YELLOW;
			TextBold[TextNum] = false;
			TextNum++;
		}
#endif	// ASG_ADD_LEAP_OF_CONTROL_TOOLTIP_TEXT

		string timetext;
		g_StringTime( Item_data.m_Time, timetext, true );
		sprintf(TextList[TextNum], timetext.c_str() );
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2302] );
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	else if(ip->Type == ITEM_HELPER+60)
	{
		sprintf(TextList[TextNum], GlobalText[2519]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_INDULGENCE_ITEM

#ifdef PSW_ADD_PC4_SEALITEM
	else if( ip->Type == ITEM_HELPER+62 )
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);

		sprintf(TextList[TextNum], GlobalText[2253], Item_data.m_byValue1 );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2569], Item_data.m_byValue2 );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2570] );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
#ifdef LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG_ENG
		sprintf(TextList[TextNum], GlobalText[2566]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG_ENG
	#else
#ifdef LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG
		sprintf(TextList[TextNum], GlobalText[2567]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2568]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG
	#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH
#endif	// SELECTED_LANGUAGE != LANGUAGE_KOREAN
	}
	else if( ip->Type == ITEM_HELPER+63 )
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);

		sprintf(TextList[TextNum], GlobalText[2254], Item_data.m_byValue1 );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2571], Item_data.m_byValue2 );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2572] );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN && SELECTED_LANGUAGE != LANGUAGE_ENGLISH
#ifdef LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG
		sprintf(TextList[TextNum], GlobalText[2567]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2568]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LDK_FIX_PC4_SEALITEM_TOOLTIP_BUG
#endif	// SELECTED_LANGUAGE != LANGUAGE_KOREAN
	}
#endif //PSW_ADD_PC4_SEALITEM
	
#ifdef PSW_ADD_PC4_SCROLLITEM
	else if( ip->Type == ITEM_POTION+97 )
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		sprintf(TextList[TextNum], GlobalText[2580]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2502]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+98 )
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		
		sprintf(TextList[TextNum], GlobalText[2581]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2502]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_ADD_PC4_SCROLLITEM

#ifdef YDG_ADD_HEALING_SCROLL
	else if (ip->Type == ITEM_POTION+140)	// ġ���� ��ũ��
	{
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2188], 100);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_HEALING_SCROLL

#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	else if( ip->Type == ITEM_POTION+96 )
	{
		sprintf(TextList[TextNum], GlobalText[2573]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2574]);
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;

#ifdef LDK_FIX_CHAOSCHARMITEM_TOOLTIP
		sprintf(TextList[TextNum], GlobalText[2708]);
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
#endif //LDK_FIX_CHAOSCHARMITEM_TOOLTIP
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
	else if( ip->Type == ITEM_HELPER+64 )
	{
		sprintf(TextList[TextNum], GlobalText[2575]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum], GlobalText[2576]);
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_HELPER+65 )
	{
		sprintf(TextList[TextNum], GlobalText[2577]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum], GlobalText[2578]);
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_PC4_GUARDIAN

#ifdef LDK_ADD_RUDOLPH_PET
	else if( ip->Type == ITEM_HELPER+67 )
	{
		sprintf(TextList[TextNum], GlobalText[2600]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_RUDOLPH_PET

#ifdef YDG_ADD_SKELETON_PET
	else if( ip->Type == ITEM_HELPER+123 )	// ���̷��� ��
	{
		sprintf(TextList[TextNum], GlobalText[2600]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3068]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3069]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3070]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_SKELETON_PET

#ifdef PJH_ADD_PANDA_PET
	else if( ip->Type == ITEM_HELPER+80 )
	{
		sprintf(TextList[TextNum], GlobalText[2746]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2747]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2748]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PJH_ADD_PANDA_PET

#ifdef LDK_ADD_CS7_UNICORN_PET
	else if( ip->Type == ITEM_HELPER+106 )
	{
		sprintf(TextList[TextNum], GlobalText[2746]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2744]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2748]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_CS7_UNICORN_PET
	
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	else if(ip->Type == ITEM_HELPER+107)		// ġ��������
	{
		sprintf(TextList[TextNum],GlobalText[926]);	// ���� �Ұ���
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING

#ifdef YDG_ADD_CS7_MAX_AG_AURA
	else if(ip->Type == ITEM_HELPER+104)		// AG���� ����
	{
		sprintf(TextList[TextNum], GlobalText[2968]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	else if(ip->Type == ITEM_HELPER+105)		// SD���� ����
	{
		sprintf(TextList[TextNum], GlobalText[2969]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	else if(ip->Type == ITEM_HELPER+103)		// ��Ƽ ����ġ ���� ������
	{
// (�Ϻ���)��Ƽ ���� ���� �߰��� ��� ����ġ ����(+190%, �Ѹ� �߰��� +10%)(09.11.19)
#ifdef LJH_MOD_JPN_PARTY_EXP_WITH_PARTY_BUFF
		sprintf(TextList[TextNum], GlobalText[2970]);
#else	//LJH_MOD_JPN_PARTY_EXP_WITH_PARTY_BUFF
		sprintf(TextList[TextNum], GlobalText[2970], 170);
#endif	//LJH_MOD_JPN_PARTY_EXP_WITH_PARTY_BUFF
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	else if( ip->Type == ITEM_HELPER+69 )	// ��Ȱ�� ����
	{
		sprintf(TextList[TextNum], GlobalText[2602]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		if (g_PortalMgr.IsRevivePositionSaved())
		{
			sprintf(TextList[TextNum], GlobalText[2603]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
			g_PortalMgr.GetRevivePositionText(TextList[TextNum]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	else if( ip->Type == ITEM_HELPER+70 )	// �̵��� ����
	{
		sprintf(TextList[TextNum], GlobalText[2604]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef ASG_ADD_CS6_GUARD_CHARM
	else if (ip->Type == ITEM_HELPER+81)	// ��ȣ�Ǻ���
	{
		::sprintf(TextList[TextNum], GlobalText[2714]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
		::sprintf(TextList[TextNum], GlobalText[2729]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#ifdef PBG_MOD_GUARDCHARMTEXT
		::sprintf(TextList[TextNum], GlobalText[3084]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#endif //PBG_MOD_GUARDCHARMTEXT
	}
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	else if (ip->Type == ITEM_HELPER+82)	// ������ ��ȣ ����
	{
		::sprintf(TextList[TextNum], GlobalText[2715]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
		::sprintf(TextList[TextNum], GlobalText[2730]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
		::sprintf(TextList[TextNum], GlobalText[2716]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
	}
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
	else if (ip->Type == ITEM_HELPER+93)	// ��������帶����
	{
		::sprintf(TextList[TextNum], GlobalText[2256]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#ifdef LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
		::sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
	#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
#else
		::sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#endif //LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	}
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
	else if (ip->Type == ITEM_HELPER+94)	// ǳ�������帶����
	{
		::sprintf(TextList[TextNum], GlobalText[2257]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#ifdef LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	#if SELECTED_LANGUAGE != LANGUAGE_CHINESE
		::sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
	#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
#else
		::sprintf(TextList[TextNum], GlobalText[2297]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum++] = false;
#endif //LJW_FIX_CASHSHOPITEM_BUFF_CONTENT_IN_CHANA
	}
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER

#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	// ��������� ������ ����
	else if(ip->Type == ITEM_HELPER+61)
	{
		// 2259 "%s ����� ������ Ƚ����ŭ ����� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2259], GlobalText[2369]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		// 2270 "���� ������ ������ ���߾� �ڵ� ����˴ϴ�."
		sprintf(TextList[TextNum], GlobalText[2270]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		// ��ĭ �߰�
		sprintf(TextList[TextNum], "\n");
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_CHARACTER_CARD 
	else if(ip->Type == ITEM_POTION+91) // ĳ���� ī��
	{
		// "��ȯ���� ĳ���͸� ������ �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2551]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
	else if(ip->Type == ITEM_POTION+92) // ī����ī�� ���
	{
		// 2261 "ī����ī�� ������ ���� Ư���� �������� ȹ���� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2261]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		// "�Ϲ�, ������ ������ ����"
		sprintf(TextList[TextNum], GlobalText[2553]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_POTION+93) // ī����ī�� ����
	{
		// 2261 "ī����ī�� ������ ���� Ư���� �������� ȹ���� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2261]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		// "�̺�Ʈ�� ������ ����"
		sprintf(TextList[TextNum], GlobalText[2556]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_POTION+95) // ī����ī�� �̴�
	{
		// 2261 "ī����ī�� ������ ���� Ư���� �������� ȹ���� �� �ֽ��ϴ�."
		sprintf(TextList[TextNum], GlobalText[2261]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// "�ʺ��� ������ ����"
		sprintf(TextList[TextNum], GlobalText[2552]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
	else if( ip->Type == ITEM_POTION+94 )
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum], GlobalText[2559]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
	else if( ip->Type == ITEM_POTION+84 )  // ���ɻ���
	{
		sprintf(TextList[TextNum], GlobalText[2011] );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+85 )  // ���ɼ�
	{
		sprintf(TextList[TextNum], GlobalText[2549] );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		string timetext;
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
		g_StringTime( Item_data.m_Time, timetext, true );
		sprintf(TextList[TextNum], timetext.c_str() );
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+86 )  // ���ɰ��
	{
		sprintf(TextList[TextNum], GlobalText[2550]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		string timetext;
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
		g_StringTime( Item_data.m_Time, timetext, true );
		sprintf(TextList[TextNum], timetext.c_str() );
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+87 )  // ������
	{
		sprintf(TextList[TextNum], GlobalText[2532]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		string timetext;
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
		g_StringTime( Item_data.m_Time, timetext, true );
		sprintf(TextList[TextNum], timetext.c_str() );
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+88 )  // ��� ����
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2534]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2535]);
		TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+89 )  // ������ ����
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2534]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2536]);
		TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+90 )  // ����� ����
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[2534]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
		sprintf(TextList[TextNum], GlobalText[2564]);
		TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
		sprintf(TextList[TextNum], GlobalText[2537]);
		TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
		TextBold[TextNum] = false;
		TextNum++;
#endif SELECTED_LANGUAGE == LANGUAGE_KOREAN
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
	else if(ip->Type == ITEM_HELPER+49)
	{
		sprintf(TextList[TextNum], GlobalText[2397]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+50)
	{
		sprintf(TextList[TextNum], GlobalText[2398]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+51)
	{
		sprintf(TextList[TextNum], GlobalText[2399]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_POTION+64)
	{
		sprintf(TextList[TextNum], GlobalText[2420]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}	
	else if(ip->Type >= ITEM_POTION+65 && ip->Type <= ITEM_POTION+68)	// ����������Ʈ�� �Ҳ�, �︶�̳��� ��, ����Ǻһ����� ����, �ɿ��Ǵ�����
	{
		sprintf(TextList[TextNum], GlobalText[730]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[731]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[732]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
	}
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	else if(ip->Type >= ITEM_POTION+151 && ip->Type <= ITEM_POTION+156)
	{
		switch(ip->Type)
		{
		case ITEM_POTION+151:	// 1���� �Ƿڼ�
			sprintf(TextList[TextNum], GlobalText[3268]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			sprintf(TextList[TextNum],GlobalText[3269]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			sprintf(TextList[TextNum],GlobalText[733]);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		case ITEM_POTION+152:	// 1���� �Ƿ� �Ϸ� Ȯ�μ�
			sprintf(TextList[TextNum], GlobalText[3270]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			sprintf(TextList[TextNum],GlobalText[733]);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		case ITEM_POTION+153:	// ��Ÿ����Ʈ
			sprintf(TextList[TextNum], GlobalText[3271]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		case ITEM_POTION+154:	// ĮƮ��
			sprintf(TextList[TextNum], GlobalText[3272]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		case ITEM_POTION+155:	// źŻ�ν��� ����
			sprintf(TextList[TextNum], GlobalText[3273]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		case ITEM_POTION+156:	// ����� �������� ������
			sprintf(TextList[TextNum], GlobalText[3274]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
			break;
		}

		sprintf(TextList[TextNum],GlobalText[731]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[732]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
		
	}
	else if(ip->Type == ITEM_POTION+157)	// �ʷϺ� ����
	{
		sprintf(TextList[TextNum], GlobalText[3275]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_POTION+158)	// ������ ����
	{
		sprintf(TextList[TextNum], GlobalText[3276]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_POTION+159)	// ����� ����
	{
		sprintf(TextList[TextNum], GlobalText[3277]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
	else if(ip->Type == ITEM_HELPER+52)
	{
		sprintf(TextList[TextNum], GlobalText[1665]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+53)
	{
		sprintf(TextList[TextNum], GlobalText[1665]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if ((ip->Type >= ITEM_WING+60 && ip->Type <= ITEM_WING+65)	// �õ�
		|| (ip->Type >= ITEM_WING+70 && ip->Type <= ITEM_WING+74)	// ���Ǿ�
		|| (ip->Type >= ITEM_WING+100 && ip->Type <= ITEM_WING+129))	// �õ彺�Ǿ�
	{
		TextNum = g_SocketItemMgr.AttachToolTipForSeedSphereItem(ip, TextNum);
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
	else if( ip->Type == ITEM_HELPER+71 || ip->Type == ITEM_HELPER+72 || ip->Type == ITEM_HELPER+73 || ip->Type == ITEM_HELPER+74 ||ip->Type == ITEM_HELPER+75 )	// �׺� ������
	{
		sprintf(TextList[TextNum], GlobalText[2709]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_GAMBLE_RANDOM_ICON

	else if(ip->Type == ITEM_HELPER+38)
	{
		sprintf(TextList[TextNum],GlobalText[926]);	// ���� �Ұ���
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+20)		//. ������ ����, �������� ����
	{
        switch ( Level )
        {
        case 0:
            {
                sprintf(TextList[TextNum],GlobalText[926]);	// ���� �Ұ���
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
            }
            break;

        case 1:
		    {
			    sprintf(TextList[TextNum],GlobalText[924], 40 );
			    TextListColor[TextNum] = TEXT_COLOR_WHITE;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[731]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[732]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[733]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
		    }
            break;
        case 2:
		    {
			    sprintf(TextList[TextNum],GlobalText[924], 80 );
			    TextListColor[TextNum] = TEXT_COLOR_WHITE;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[731]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[732]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
			    sprintf(TextList[TextNum],GlobalText[733]);
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
		    }
            break;
        case 3:     //  ������ ����.
            {
                sprintf(TextList[TextNum],GlobalText[926]);	// ���� �Ұ���
			    TextListColor[TextNum] = TEXT_COLOR_RED;
			    TextBold[TextNum] = false;
			    TextNum++;
            }
            break;
        }
	}
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING             // (�������)���� ���� 100% ���� ����
	else if(ip->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN
			&& ip->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END)
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);
#ifdef LDK_FIX_CHARM_MIX_ITEM_WING_TOOLTIP
		// �������̸��� �ƴ� �������� ���� �� ���� ���� �߰�

		//"���� ���� �� ���ϴ� Ŭ���������� ������ �� �ֵ��� ���ݴϴ�."
		sprintf(TextList[TextNum],GlobalText[2717]);
		TextBold[TextNum] = false;
		TextNum++;
		
		switch (ip->Type)
		{
		case ITEM_TYPE_CHARM_MIXWING+EWS_KNIGHT_1_CHARM: //��ź��������
			{
				sprintf(TextList[TextNum], GlobalText[2718], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_MAGICIAN_1_CHARM: //õ����������
			{
				sprintf(TextList[TextNum], GlobalText[2720], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_ELF_1_CHARM: //������������
			{
				sprintf(TextList[TextNum], GlobalText[2722], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_SUMMONER_1_CHARM: //��ӳ�������
			{
				sprintf(TextList[TextNum], GlobalText[2724], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_DARKLORD_1_CHARM: //�������պ���
			{
				sprintf(TextList[TextNum], GlobalText[2727], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_KNIGHT_2_CHARM: //���ﳯ������
			{
				sprintf(TextList[TextNum], GlobalText[2719], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_MAGICIAN_2_CHARM: //��ȥ��������
			{
				sprintf(TextList[TextNum], GlobalText[2721], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_ELF_2_CHARM: //���ɳ�������
			{
				sprintf(TextList[TextNum], GlobalText[2723], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_SUMMONER_2_CHARM: //������������
			{
				sprintf(TextList[TextNum], GlobalText[2725], Item_data.m_byValue1);
			}break;
		case ITEM_TYPE_CHARM_MIXWING+EWS_DARKKNIGHT_2_CHARM: //���泯������
			{
				sprintf(TextList[TextNum], GlobalText[2726], Item_data.m_byValue1);
			}break;
		}

#else //LDK_FIX_CHARM_MIX_ITEM_WING_TOOLTIP

#ifdef PBG_FIX_CHARM_MIX_ITEM_WING_TOOLTIP
		sprintf(TextList[TextNum], GlobalText[2732+(ip->Type-(ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN))],
			Item_data.m_byValue1);
#else //PBG_FIX_CHARM_MIX_ITEM_WING_TOOLTIP
		sprintf(TextList[TextNum], GlobalText[2732+(ip->Type-(MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN))],
			Item_data.m_byValue1);
#endif //PBG_FIX_CHARM_MIX_ITEM_WING_TOOLTIP

#endif //LDK_FIX_CHARM_MIX_ITEM_WING_TOOLTIP

		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	else if( ip->Type == ITEM_POTION+110 )
	{
		sprintf(TextList[TextNum], GlobalText[2773]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2774]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2775]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		sprintf(TextList[TextNum], GlobalText[1181], ip->Durability, 5);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2776], 5 - ip->Durability);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
	}
	else if( ip->Type == ITEM_POTION+111 )
	{
		sprintf(TextList[TextNum], GlobalText[2777]);
		TextListColor[TextNum] = TEXT_COLOR_DARKBLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2778]);
		TextListColor[TextNum] = TEXT_COLOR_DARKBLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	else if( ITEM_POTION+101 <= ip->Type && ip->Type <= ITEM_POTION+109 )
	{
		switch(ip->Type)
		{
		case ITEM_POTION+101: // �ǹ�������
			{
				sprintf ( TextList[TextNum], GlobalText[1181], ip->Durability, 5 ); 
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;

				sprintf(TextList[TextNum], GlobalText[2788]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
			}break;
		case ITEM_POTION+102: // ���̿��� ��ɼ�
			{
				sprintf(TextList[TextNum], GlobalText[2784]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf(TextList[TextNum], GlobalText[2785]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf(TextList[TextNum], GlobalText[2786]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
			}break;
		case ITEM_POTION+103: // ��ũ�ι��� ����
		case ITEM_POTION+104: 
		case ITEM_POTION+105: 
		case ITEM_POTION+106: 
		case ITEM_POTION+107: 
		case ITEM_POTION+108: 
			{
				sprintf(TextList[TextNum], GlobalText[2790]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
			}break;
		case ITEM_POTION+109: // ��ũ�ι���
			{
				sprintf(TextList[TextNum], GlobalText[2792]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf(TextList[TextNum], GlobalText[2793]);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
			}break;
		}
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	else if( ITEM_HELPER+109 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;

		// ���� ���� 4%
#ifdef LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		sprintf(TextList[TextNum], GlobalText[3058], 4);
#else // LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		sprintf(TextList[TextNum], GlobalText[632], 4);
#endif // LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
	else if( ITEM_HELPER+110 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// �ִ� ����� ���� 4%
		sprintf(TextList[TextNum], GlobalText[622], 4);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY	// �ű� ���(������)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	else if( ITEM_HELPER+111 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// �� ���� 50%
#ifdef LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		sprintf(TextList[TextNum], GlobalText[627], 50);
#else // LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		sprintf(TextList[TextNum], GlobalText[2744], 50);
#endif // LDS_MOD_MODIFYTEXT_TOPAZRING_SAPIRERING
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	else if( ITEM_HELPER+112 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ������ ���� 4%
		sprintf(TextList[TextNum], GlobalText[624], 4);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
	else if( ITEM_HELPER+113 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ������Ʈ ������ Ȯ�� +10%
		sprintf(TextList[TextNum], GlobalText[628], 10);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
	else if( ITEM_HELPER+114 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ���ݼӵ�+7
		sprintf(TextList[TextNum], GlobalText[2229], 7);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
	else if( ITEM_HELPER+115 == ip->Type )
	{
		// ���� �ڵ� ȸ�� 3%
		sprintf(TextList[TextNum], GlobalText[92], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ���� �׿����� ȹ�� ���� ���� +����/8
		sprintf(TextList[TextNum], GlobalText[635]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
	else if( ITEM_POTION+112 == ip->Type )
	{
		// ���εȱݻ����ڿ���...
		sprintf ( TextList[TextNum], GlobalText[2876] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
	else if( ITEM_POTION+113 == ip->Type )
	{
		// ���εȱݻ����ڿ���...
		sprintf ( TextList[TextNum], GlobalText[2875] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
	// �����ȭ
	else if(ip->Type == ITEM_POTION+120)
	{
		sprintf ( TextList[TextNum], GlobalText[2971] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	else if( ITEM_POTION+121 == ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[2877] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
	else if( ITEM_POTION+122 == ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[2878] );
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
	else if( ITEM_POTION+123 == ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[2879] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
	else if( ITEM_POTION+124 == ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[2880] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX		// �ΰ��Ә� ������ // ��Ű������6��			// MODEL_POTION+134~139
	else if( ITEM_POTION+134 <= ip->Type && ITEM_POTION+139 >= ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[2972] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDK_ADD_INGAMESHOP_PACKAGE_BOX		// �ΰ��Ә� ������ // ��Ű������6��			// MODEL_POTION+134~139
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	else if( ITEM_HELPER+116 == ip->Type )
	{
		sprintf ( TextList[TextNum], GlobalText[3018] ); 
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	else if( ITEM_HELPER+121 == ip->Type )
	{
		int iMap = 57;

		// ������ Ƚ����ŭ ����� �� �ֽ��ϴ�.
		sprintf ( TextList[TextNum], GlobalText[2259], GlobalText[iMap] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		
		// ������ ���߾� �ڵ� ���� �˴ϴ�.
		sprintf ( TextList[TextNum], GlobalText[2270] ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;

		// %d�� ��� ����
		sprintf ( TextList[TextNum], GlobalText[2260], ip->Durability ); 
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	// ����ä�� ����� ����
	else if(ip->Type == ITEM_HELPER+124)
	{
		sprintf(TextList[TextNum], GlobalText[3116]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
#ifdef ASG_MOD_CHARGED_CHANNEL_TICKET_ADD_DESCRIPTION
		sprintf(TextList[TextNum], GlobalText[3127]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = true;
		TextNum++;
#endif	// ASG_MOD_CHARGED_CHANNEL_TICKET_ADD_DESCRIPTION
	}
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
#ifdef PBG_ADD_GENSRANKING
	else if(ip->Type >= ITEM_POTION+141 && ip->Type <= ITEM_POTION+144)
	{
		sprintf(TextList[TextNum], GlobalText[571]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PBG_ADD_GENSRANKING
#ifdef KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	else if(ip->Type==ITEM_POTION+133)		// ����Ʈ SDȸ�� ����
	{
		sprintf(TextList[TextNum], GlobalText[69], ip->Durability );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum], GlobalText[3267]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#endif // KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP


	Color = TEXT_COLOR_YELLOW;
	sprintf ( TextList[TextNum], "%s", p->Name );

	if(ip->Type == ITEM_POTION+19)//�ʴ���
	{
		sprintf(TextList[TextNum],GlobalText[638]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[639]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}

    //////////////////////////////////////////////////////////////////////////
    //  �ɼ�.
    //////////////////////////////////////////////////////////////////////////
	if(ip->DamageMin)   //  ���ݷ�.
	{

		int minindex = 0, maxindex = 0, magicalindex = 0; 

		if( Level >= ip->Jewel_Of_Harmony_OptionLevel )	
		{
			StrengthenCapability SC;
			g_pUIJewelHarmonyinfo->GetStrengthenCapability( &SC, ip, 1 );

			if( SC.SI_isSP )
			{
				minindex     = SC.SI_SP.SI_minattackpower;
				maxindex     = SC.SI_SP.SI_maxattackpower;
				magicalindex = SC.SI_SP.SI_magicalpower;
			}
		}
		int DamageMin = ip->DamageMin;
		int DamageMax = ip->DamageMax;
		if(ip->Type>>4 == 15)
		{
			sprintf(TextList[TextNum],"%s: %d ~ %d",GlobalText[40+2],DamageMin,DamageMax);
		}
		else if ( ip->Type != ITEM_ETC+5 && ip->Type != ITEM_ETC+14 && ip->Type != ITEM_ETC+15)
		{	
			// �Ϻ� ������ ���ݷ��� ����
			if ( ip->Type>=ITEM_ETC && ip->Type<ITEM_ETC+MAX_ITEM_INDEX )
			{
				int SkillIndex = getSkillIndexByBook( ip->Type );

				SKILL_ATTRIBUTE *skillAtt = &SkillAttribute[SkillIndex];
				
				DamageMin = skillAtt->Damage;
				DamageMax = skillAtt->Damage+skillAtt->Damage/2;

				sprintf(TextList[TextNum],"%s: %d ~ %d",GlobalText[42],DamageMin,DamageMax);
			}
			else
			{
				if( DamageMin + minindex >= DamageMax + maxindex )
					sprintf(TextList[TextNum],"%s: %d ~ %d",GlobalText[40+p->TwoHand],DamageMax + maxindex, DamageMax + maxindex);
				else
					sprintf(TextList[TextNum],"%s: %d ~ %d",GlobalText[40+p->TwoHand],DamageMin + minindex, DamageMax + maxindex);
			}
		}
		else
		{	// ���ݷ� ���� �Ϻι���
			TextNum--;
		}

		if ( DamageMin>0 )
		{
			if( minindex != 0 || maxindex != 0 )
			{
				TextListColor[TextNum] = TEXT_COLOR_YELLOW;
				TextBold[TextNum] = false;
				TextNum++;
			}
			else
			{
				if((ip->Option1&63) > 0)
					TextListColor[TextNum] = TEXT_COLOR_BLUE;
				else
					TextListColor[TextNum] = TEXT_COLOR_WHITE;
				TextBold[TextNum] = false;
				TextNum++;
			}
		}
		else
		{
			TextNum--;
		}
	}
	if(ip->Defense)     //  ����.
	{
		int maxdefense = 0; 

		if( Level >= ip->Jewel_Of_Harmony_OptionLevel )	
		{
			StrengthenCapability SC;
			g_pUIJewelHarmonyinfo->GetStrengthenCapability( &SC, ip, 2 );

			if( SC.SI_isSD )
			{
				maxdefense     = SC.SI_SD.SI_defense;
			}
		}
		sprintf(TextList[TextNum],GlobalText[65],ip->Defense + maxdefense );

		if( maxdefense != 0 )
			TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		else
		{
			if(ip->Type>=ITEM_HELM && ip->Type<ITEM_BOOTS+MAX_ITEM_INDEX && (ip->Option1&63) > 0)
      			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			else
      			TextListColor[TextNum] = TEXT_COLOR_WHITE;

		}

		TextBold[TextNum] = false;
		TextNum++;
	}
	if(ip->MagicDefense)//  ���� ����.
	{
    	sprintf(TextList[TextNum],GlobalText[66],ip->MagicDefense);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	if(p->SuccessfulBlocking)   //  ��� ������.
	{
		sprintf(TextList[TextNum],GlobalText[67],ip->SuccessfulBlocking);
		if((ip->Option1&63) > 0)
      		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		else
      		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	if(p->WeaponSpeed)  //  ���� �ӵ�.
	{
    	sprintf(TextList[TextNum],GlobalText[64],p->WeaponSpeed);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
	if(p->WalkSpeed)    //  �̵� �ӵ�.
	{
    	sprintf(TextList[TextNum],GlobalText[68],p->WalkSpeed);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#ifdef MYSTERY_BEAD
	if(ip->Type==ITEM_WING+26)
	{
		if(Level == 0)	//. �ź��� ����
		{
			sprintf(TextList[TextNum],GlobalText[112]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[1835]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
            sprintf(TextList[TextNum],GlobalText[114]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
		else if (Level >= 1 && Level <= 3)	//. ������
		{
			sprintf(TextList[TextNum],GlobalText[1836]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[1837]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[732]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[733]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
		}
		else if (Level == 4)	//. ��������
		{
			sprintf(TextList[TextNum],GlobalText[571]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[732]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[733]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
		}
		else if (Level == 5)	//. ��¦����
		{
			sprintf(TextList[TextNum],GlobalText[1839]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[732]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[733]);
		    TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
		}
	}
#endif // MYSTERY_BEAD
	if(ip->Type >= ITEM_WING+32 && ip->Type <= ITEM_WING+34)//��������.(x-mas�̺�Ʈ��)
	{
		sprintf(TextList[TextNum],GlobalText[571]);
		switch(ip->Type)
		{
		case ITEM_WING+32:
			TextListColor[TextNum] = TEXT_COLOR_RED;
			break;
		case ITEM_WING+33:
			TextListColor[TextNum] = TEXT_COLOR_GREEN;
			break;
		case ITEM_WING+34:
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			break;
		}
		TextBold[TextNum] = false;TextNum++;
	}
#ifdef HELLOWIN_EVENT
	if(ip->Type >= ITEM_POTION+45 && ip->Type <= ITEM_POTION+50)//�ҷ������� �̺�Ʈ
	{
		char Text_data[300];
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ip->Type);

		switch(ip->Type)
		{
		case ITEM_POTION+45:
			sprintf(TextList[TextNum],GlobalText[2011]);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		case ITEM_POTION+46:
			wsprintf(Text_data,GlobalText[2229],Item_data.m_byValue1);
			sprintf(TextList[TextNum],Text_data);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		case ITEM_POTION+47:
			wsprintf(Text_data,GlobalText[2230],Item_data.m_byValue1);
			sprintf(TextList[TextNum],Text_data);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		case ITEM_POTION+48:
			wsprintf(Text_data,GlobalText[2231],Item_data.m_byValue1);
			sprintf(TextList[TextNum],Text_data);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		case ITEM_POTION+49:
			wsprintf(Text_data,GlobalText[960],Item_data.m_byValue1);
			sprintf(TextList[TextNum],Text_data);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		case ITEM_POTION+50:
			wsprintf(Text_data,GlobalText[961],Item_data.m_byValue1);
			sprintf(TextList[TextNum],Text_data);
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW;
			break;
		}
		TextBold[TextNum] = false;TextNum++;
	}
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	if(ip->Type >= ITEM_POTION+32 && ip->Type <= ITEM_POTION+34)//��������.(x-mas�̺�Ʈ��)
	{
		sprintf(TextList[TextNum],GlobalText[2011]);
		switch(ip->Type)
		{
		case ITEM_POTION+32:
			if(Level == 0)
				TextListColor[TextNum] = TEXT_COLOR_PURPLE;
			else
			if(Level == 1)
				TextListColor[TextNum] = TEXT_COLOR_PURPLE;
			break;
		case ITEM_POTION+33:
			if(Level == 0)
				TextListColor[TextNum] = TEXT_COLOR_RED;
			else
			if(Level == 1)
				TextListColor[TextNum] = TEXT_COLOR_RED;
			break;
		case ITEM_POTION+34:
			if(Level == 0)
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
			else
			if(Level == 1)
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
			break;
		}
		TextBold[TextNum] = false;TextNum++;
	}
#endif
	if(ip->Type==ITEM_POTION+11)//  ����� ����.
	{
		if( Level==7 )//  õ���� ����.
		{
            sprintf(TextList[TextNum],GlobalText[112]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
            sprintf(TextList[TextNum],GlobalText[113]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
            sprintf(TextList[TextNum],GlobalText[114]);  
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
#ifdef NEW_YEAR_BAG_EVENT
        else if ( Level==14 )   //  �Ķ� ���ָӴ�
        {
            sprintf(TextList[TextNum],GlobalText[1652]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
            sprintf(TextList[TextNum],GlobalText[1653]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        }
#endif// NEW_YEAR_BAG_EVENT
        else
        {
            sprintf(TextList[TextNum],GlobalText[571]);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        }
		sprintf(TextList[TextNum],GlobalText[733]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
		if (Level == 13)	// ��ũ�ε��� ����
		{
			sprintf(TextList[TextNum],GlobalText[731]);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}
	char tCount = COMGEM::CalcCompiledCount(ip);
	if(tCount > 0)
	{
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// ���� ���� ������ ���� �߰�
		int	nJewelIndex = COMGEM::Check_Jewel_Com(ip->Type);
		if( nJewelIndex != COMGEM::NOGEM )
		{
			sprintf(TextList[TextNum], GlobalText[1819], tCount, GlobalText[COMGEM::GetJewelIndex(nJewelIndex, COMGEM::eGEM_NAME)]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum], GlobalText[1820]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
#else // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		switch(COMGEM::CheckOneItem(ip))
		{
			case COMGEM::COMCELE:
				{
					sprintf(TextList[TextNum], GlobalText[1819], tCount, GlobalText[1806]);
					TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
					sprintf(TextList[TextNum], GlobalText[1820]);
					TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
				}
				break;
			case COMGEM::COMSOUL:
				{
					sprintf(TextList[TextNum], GlobalText[1819], tCount, GlobalText[1807]);
					TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
					sprintf(TextList[TextNum], GlobalText[1820]);
					TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
				}
				break;
		}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	}
	if(ip->Type==ITEM_POTION+13)//  �༮
	{
		sprintf(TextList[TextNum],GlobalText[572]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_POTION+14)//  ����
	{
		sprintf(TextList[TextNum],GlobalText[573]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_POTION+16)//  ����
	{
		sprintf(TextList[TextNum],GlobalText[621]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_POTION+17 || ip->Type==ITEM_POTION+18)//�Ǹ��� ��, ����
	{
		sprintf(TextList[TextNum],GlobalText[637]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#ifdef ANNIVERSARY_EVENT
	if(ip->Type==ITEM_POTION+20 && Level >= 1 && Level <= 5)//�ִϹ����� �ڽ�
	{
		sprintf(TextList[TextNum],GlobalText[571]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#endif	// ANNIVERSARY_EVENT
#ifdef _PVP_ADD_MOVE_SCROLL
	if(ip->Type==ITEM_POTION+10 && Level >= 1 && Level <= 8)//�̵�����
	{
		sprintf(TextList[TextNum],GlobalText[157], 3);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef _PVP_MURDERER_HERO_ITEM
	if(ip->Type==ITEM_POTION+30)	//�������θ�¡ǥ
	{
//		ITEM_EX_INFO * pItemExInfo = g_ItemExInfo.GetInfo(wInvenPos);
		if (pItemExInfo != NULL)	// ���� �̹� �޾�����
		{
			TextNum--;
			sprintf(TextList[TextNum],"(%d %s %s)", pItemExInfo->m_wLevel_T, GlobalText[368], pItemExInfo->m_szClass_T);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
			sprintf(TextList[TextNum], pItemExInfo->m_szDate);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],"%d %s %s", pItemExInfo->m_wLevel, GlobalText[368], pItemExInfo->m_szClass);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;

			if (ip->Durability % 100 < 3)	// ����
			{
				sprintf(TextList[TextNum],"%s %s %s", GlobalText[490], pItemExInfo->m_szName, GlobalText[918]);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;
			}
			else	// ���θ�
			{
				sprintf(TextList[TextNum],"%s %s %s", GlobalText[487], pItemExInfo->m_szName, GlobalText[918]);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;
			}
			sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
			sprintf(TextList[TextNum],GlobalText[1193], pItemExInfo->m_wRemainTime);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
		else	// ������ ������
		{
			sprintf(TextList[TextNum],GlobalText[1190]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			sprintf(TextList[TextNum],GlobalText[1191]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		if (ip->Durability / 100 == 2)
		{
			sprintf(TextList[TextNum],GlobalText[1194]);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
		else
		{
			sprintf(TextList[TextNum],GlobalText[1195]);
			TextListColor[TextNum] = TEXT_COLOR_RED;TextBold[TextNum] = false;TextNum++;
		}
	}
#endif	// _PVP_MURDERER_HERO_ITEM
	if(ip->Type==ITEM_WING+15)  //  ȥ��.
	{
		sprintf(TextList[TextNum],GlobalText[574]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_POTION+22)  //  â���� ����.
	{
		sprintf(TextList[TextNum],GlobalText[619]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_POTION+31)  //  ��ȣ�� ����.
	{
//		sprintf(TextList[TextNum],GlobalText[1288]);	// 1288 "����� ��ӹ���"
//		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[1289]);	// 1289 "������ ���� ��ü���� ������ ��ȭ"
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_HELPER+0) //  
	{
		sprintf(TextList[TextNum],GlobalText[578], 20);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[739], 50);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	if(ip->Type==ITEM_HELPER+1) //  ��ȣõ��/�Ǹ�.
	{
		sprintf(TextList[TextNum],GlobalText[576]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#ifdef ADD_ALICE_WINGS_1
	if((ip->Type>=ITEM_WING && ip->Type<=ITEM_WING+2) || ip->Type==ITEM_WING+41)//����
#else	// ADD_ALICE_WINGS_1
    if(ip->Type>=ITEM_WING && ip->Type<=ITEM_WING+2)//����
#endif	// ADD_ALICE_WINGS_1
	{
		sprintf(TextList[TextNum],GlobalText[577],12+Level*2);  //  ������ ��%����.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[578],12+Level*2);  //  ������ ��%���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[579]);             //  �̵� �ӵ� ���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_HELPER + 38 )
	{
		sprintf(TextList[TextNum],GlobalText[2207]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_POTION + 41 )
	{
		sprintf(TextList[TextNum],GlobalText[2208]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_POTION + 42 )
	{
		sprintf(TextList[TextNum],GlobalText[2209]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_POTION + 43 )
	{
		sprintf(TextList[TextNum],GlobalText[2210]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_POTION + 44 )
	{
		sprintf(TextList[TextNum],GlobalText[2210]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#ifdef LEM_ADD_LUCKYITEM		// ��Ű������ ���� ���� �ؽ�Ʈ ����
	else if( ip->Type == ITEM_POTION+160 )
	{
		// ������ ����
		sprintf(TextList[TextNum],GlobalText[3305]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
	else if( ip->Type == ITEM_POTION+161 )
	{
		// ����� ����
		sprintf(TextList[TextNum],GlobalText[2209]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#endif // LEM_ADD_LUCKYITEM
#ifdef ADD_ALICE_WINGS_1
	else if ((ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6) || ip->Type==ITEM_WING+42) //����
#else	// ADD_ALICE_WINGS_1
	else if ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 ) //����
#endif	// ADD_ALICE_WINGS_1
    {
		sprintf(TextList[TextNum],GlobalText[577],32+Level);  //  ������ ��%����.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[578],25+Level*2);  //  ������ ��%���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[579]);             //  �̵� �ӵ� ���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
    }
#ifdef ADD_ALICE_WINGS_1
	else if ((ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40) || ip->Type==ITEM_WING+43
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| ip->Type==ITEM_WING+50
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		) //3������
#else	// ADD_ALICE_WINGS_1
	else if ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 ) //3������
#endif	// ADD_ALICE_WINGS_1
    {
		sprintf(TextList[TextNum],GlobalText[577],39+Level*2);  //  ������ ��%����.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		if ( ip->Type==ITEM_WING+40 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
#ifndef PBG_MOD_NEWCHAR_MONK_WING		//�����Ǹ��� ��ġ 39�� ����
			|| ip->Type==ITEM_WING+50
#endif //PBG_MOD_NEWCHAR_MONK_WING
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			) // �����Ǹ���
		{
			sprintf(TextList[TextNum],GlobalText[578],24+Level*2);  //  ������ ��%���.
		}
		else	// ��ǳ�ǳ���~�ĸ��ǳ���
		{
			sprintf(TextList[TextNum],GlobalText[578],39+Level*2);  //  ������ ��%���.
		}
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[579]);             //  �̵� �ӵ� ���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
    }
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	else if( ITEM_WING+130 <= ip->Type && 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		ip->Type <= ITEM_WING+135
#else //PBG_ADD_NEWCHAR_MONK_ITEM
		ip->Type <= ITEM_WING+134
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)
	{
		switch(ip->Type)
		{
		case ITEM_WING+130:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		case ITEM_WING+135:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			{
				sprintf(TextList[TextNum],GlobalText[577],20+Level*2);  //  ������ ��%����.
				TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
				sprintf(TextList[TextNum],GlobalText[578],20+Level*2);  //  ������ ��%���.
				TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			}break;
		case ITEM_WING+131:
		case ITEM_WING+132:
		case ITEM_WING+133:
		case ITEM_WING+134:
			{
				sprintf(TextList[TextNum],GlobalText[577],12+Level*2);  //  ������ ��%����.
				TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
				sprintf(TextList[TextNum],GlobalText[578],12+Level*2);  //  ������ ��%���.
				TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			}break;
		}
		sprintf(TextList[TextNum],GlobalText[579]);             //  �̵� �ӵ� ���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
	else if ( ip->Type==ITEM_HELPER+3 )     //  ����Ʈ.
    {
		sprintf(TextList[TextNum],GlobalText[577],15 );  //  ������ ��%����.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		sprintf(TextList[TextNum],GlobalText[578],10 );  //  ������ ��%���.
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+31 )    //  ��ȥ.
    {
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
        switch ( Level )
        {
        case 0: sprintf ( TextList[TextNum], GlobalText[1215] ); TextNum++; break; //  ��ũȣ��.
        case 1: sprintf ( TextList[TextNum], GlobalText[1216] ); TextNum++; break; //  ��ũ���Ǹ�.
        }
    }
    else if ( ip->Type==ITEM_HELPER+14 )    //  ��ũ�� ����.
    {
        TextListColor[TextNum] = TEXT_COLOR_WHITE;
        switch ( Level )
        {
        case 0: sprintf ( TextList[TextNum], "%s", GlobalText[748] ); TextNum++; break;     //  ��ũ�� ����.
        case 1: sprintf ( TextList[TextNum], "%s", GlobalText[1236] );TextNum++; break;     //  ������ �Ҹ�.
        }
    }
	
    else if ( ip->Type==ITEM_HELPER+15 ) //  ��Ŭ. ( ������/ü��/��ø/��/��� )
    {
        TextListColor[TextNum] = TEXT_COLOR_WHITE;
        switch ( Level )
        {
		case 0:sprintf(TextList[TextNum],"%s %s", GlobalText[168], GlobalText[636] );break;
		case 1:sprintf(TextList[TextNum],"%s %s", GlobalText[169], GlobalText[636] );break;
		case 2:sprintf(TextList[TextNum],"%s %s", GlobalText[167], GlobalText[636] );break;
		case 3:sprintf(TextList[TextNum],"%s %s", GlobalText[166], GlobalText[636] );break;
		case 4:sprintf(TextList[TextNum],"%s %s", GlobalText[1900], GlobalText[636]);break;
		}
		TextNum++;
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
        switch ( Level )
        {
		case 0:sprintf(TextList[TextNum],"%s %s", GlobalText[168], GlobalText[1910] );break;
		case 1:sprintf(TextList[TextNum],"%s %s", GlobalText[169], GlobalText[1910] );break;
		case 2:sprintf(TextList[TextNum],"%s %s", GlobalText[167], GlobalText[1910] );break;
		case 3:sprintf(TextList[TextNum],"%s %s", GlobalText[166], GlobalText[1910] );break;
		case 4:sprintf(TextList[TextNum],"%s %s", GlobalText[1900], GlobalText[1910]);break;
		}
		TextNum++;
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;
		sprintf(TextList[TextNum], GlobalText[1908]);	// 1908 "������ ������� ��밡��"
		
		
		if(Level == 4)	// ��ֿ����̸�?
		{
			TextNum++;
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			sprintf(TextList[TextNum],GlobalText[61], GlobalText[24]);
		}
        TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+16 )    //  ��õ���� ��.
    {
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
        sprintf ( TextList[TextNum], GlobalText[816] );
        TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+17 )    //  ���� ��.
    {
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
        sprintf ( TextList[TextNum], GlobalText[816] );
        TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+18 )    //  �������.
    {
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
        sprintf ( TextList[TextNum], GlobalText[814] );
        TextNum++;
        sprintf ( TextList[TextNum], "\n" );
        TextNum++; SkipNum++;
		sprintf(TextList[TextNum],GlobalText[638]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum],GlobalText[639]);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
    }
    else if ( ip->Type==ITEM_POTION+7 ) //  ���м� ����.//���ƹ���
    {
        switch ( Level )
        {
        case 0:     //  �ູ�� ����.
            {
                sprintf( TextList[TextNum], GlobalText[1417] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
                sprintf( TextList[TextNum], GlobalText[1418] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
                sprintf( TextList[TextNum], GlobalText[1419] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
            }
            break;
        case 1:     //  ��ȥ�� ����.
            {
                sprintf( TextList[TextNum], GlobalText[1638] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
                sprintf( TextList[TextNum], GlobalText[1639] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
                sprintf( TextList[TextNum], GlobalText[1472] ); TextListColor[TextNum] = TEXT_COLOR_DARKRED; TextBold[TextNum] = false; TextNum++;
            }
            break;
        }
    }
    else if ( ip->Type==ITEM_HELPER+7 ) //  ��� ����
    {
        switch ( Level )
        {
        case 0: sprintf( TextList[TextNum], GlobalText[1460] ); break;  //  Ȱ �뺴.
        case 1: sprintf( TextList[TextNum], GlobalText[1461] ); break;  //  â �뺴.
        }
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+11 )    //  �ֹ���.
    {
        switch ( Level )
        {
        case 0: sprintf( TextList[TextNum], GlobalText[1416] ); break;  //  ����� �ֹ���.
        case 1: sprintf( TextList[TextNum], GlobalText[1462] ); break;  //  ������ ����.
        }
		TextListColor[TextNum] = TEXT_COLOR_YELLOW;
		TextBold[TextNum] = false;
		TextNum++;
    }
    else if ( ip->Type==ITEM_HELPER+29 )    //  �������� ���ʼ�Ʈ.
    {
        //  �ش� Ŭ������ �´� ���� ���� ���� ��ġ�� ã�´�.
        int startIndex = 0;
        if ( GetBaseClass( Hero->Class )==CLASS_DARK || GetBaseClass( Hero->Class )==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK
			|| GetBaseClass( Hero->Class )==CLASS_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK
			)
		{
            startIndex = 6;
		}

        int HeroLevel = CharacterAttribute->Level;

		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		// 1147 "ī���� ĳ��"
		// 368 "����"
		// 935 "��������"
		// 936 "�䱸��"
		sprintf(TextList[TextNum],"%s %s    %s      %s    ",GlobalText[1147], GlobalText[368], GlobalText[935], GlobalText[936] ); TextListColor[TextNum] = TEXT_COLOR_WHITE; TextBold[TextNum] = false; TextNum++;
#ifdef _VS2008PORTING
        for ( int i=0; i<6; i++ )
#else // _VS2008PORTING
        for ( i=0; i<6; i++ )
#endif // _VS2008PORTING
        {
            int Zen = g_iChaosCastleZen[i];

    		sprintf(TextList[TextNum],"        %d             %3d~%3d     %3d,000", i+1,  g_iChaosCastleLevel[startIndex+i][0],  min( 400, g_iChaosCastleLevel[startIndex+i][1] ),  Zen ); 
            if ( (HeroLevel>=g_iChaosCastleLevel[startIndex+i][0] && HeroLevel<=g_iChaosCastleLevel[startIndex+i][1])
				&& IsMasterLevel(Hero->Class) == false)
            {
                TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW; 
            }
            else
            {
                TextListColor[TextNum] = TEXT_COLOR_WHITE; 
            }
            TextBold[TextNum] = false; TextNum++;
        }
		// 737 "�����ͷ���"
		sprintf(TextList[TextNum], "         %d          %s   %3d,000", 7, GlobalText[737], 1000); 
		if(IsMasterLevel(Hero->Class) == true)
		{
			TextListColor[TextNum] = TEXT_COLOR_DARKYELLOW; 
		}
		else
		{
			TextListColor[TextNum] = TEXT_COLOR_WHITE; 
		}
		TextBold[TextNum] = false; 
		TextNum++;

        sprintf ( TextList[TextNum], "\n" ); 
		TextNum++; 
		SkipNum++;
		// 1157 "������ Ŭ������ �����ϼ���."
    	sprintf ( TextList[TextNum], GlobalText[1157] );  
		TextListColor[TextNum] = TEXT_COLOR_DARKBLUE; 
		TextNum++;
    }
    else if ( ip->Type==ITEM_POTION+21 )    //  ����. ( 1:����).
    {
        TextListColor[TextNum] = TEXT_COLOR_WHITE;
        switch ( Level )
        {
#ifndef BLOODCASTLE_2ND_PATCH
        case 1: sprintf ( TextList[TextNum], GlobalText[813] ); break;      //  ����.
#endif
#ifdef FRIEND_EVENT
        case 2: sprintf ( TextList[TextNum], GlobalText[1099] ); break;     //  ������ ��.
#endif// FRIEND_EVENT
        case 3: sprintf ( TextList[TextNum], GlobalText[1291] ); break;     //  1291 "������Ͽ� ���"
		default: break;
        }
        TextNum++;
    }
    else if ( ip->Type==ITEM_POTION+28 || ip->Type==ITEM_POTION+29 )    //  �Ҿ���� ����, ����� ǥ��
    {
        TextNum = RenderHellasItemInfo ( ip, TextNum );
    }
#ifdef PBG_MOD_NEWCHAR_MONK_WING_2
	else if(ip->Type==ITEM_WING+49 || ip->Type==ITEM_HELPER+30)
	{
		// ���� ���� �ɼǺ���
		sprintf(TextList[TextNum],GlobalText[577],20+Level*2);  //  ������ ��%����
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		int _iDamage = (ip->Type==ITEM_WING+49) ? 10+Level*2 : 10+Level;
		sprintf(TextList[TextNum],GlobalText[578],_iDamage);  //  ������ ��%���
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
#endif //PBG_MOD_NEWCHAR_MONK_WING_2

	BOOL bDurExist = FALSE;
	if ( ( p->Durability || p->MagicDur ) && 
         ( (ip->Type<ITEM_WING || ip->Type>=ITEM_HELPER ) && ip->Type<ITEM_POTION ) ||
           (ip->Type>=ITEM_WING && ip->Type<=ITEM_WING+6)          //  ���� ������.
#ifdef ADD_ALICE_WINGS_1
		|| (ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+43)          //  ���� ������.
#else	// ADD_ALICE_WINGS_1
		|| (ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40)          //  ���� ������.
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
       )
	{
		bDurExist = TRUE;
	}
	if( ( bDurExist || ip->Durability) && 
		( ip->Type<ITEM_HELPER+14 || ip->Type>ITEM_HELPER+19 )  //  ���� ĳ�� ����Ʈ �������� �������� ǥ������ �ʴ´�.
		&& !(ip->Type==ITEM_HELPER+20 && Level == 1)            //  ������ ������ ������ ǥ�� ����.
		&& !(ip->Type==ITEM_HELPER+20 && Level == 2)            //  ������ ������ ������ ǥ�� ����.
		&& !(ip->Type==ITEM_HELPER+29 )                         //  ī���� ĳ�� ����Ʈ ������ ǥ�� ����.
        && ip->Type!=ITEM_POTION+7 && ip->Type!=ITEM_HELPER+7 && ip->Type!=ITEM_HELPER+11//���ƹ���
		&& ip->Type != ITEM_HELPER+35	//^ �渱 ������ ������ ����� ���� ������ ����
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
		&& !(ip->Type >= ITEM_POTION+70 && ip->Type <= ITEM_POTION+71)
#endif //PSW_ELITE_ITEM            // ����Ʈ ����
#ifdef PSW_FRUIT_ITEM
		&& !(ip->Type >= ITEM_HELPER+54 && ip->Type <= ITEM_HELPER+58) 
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
		&& !(ip->Type >= ITEM_POTION+78 && ip->Type <= ITEM_POTION+82)
#endif //PSW_SECRET_ITEM             // ��ȭ�� ���
#ifdef PBG_ADD_SANTAINVITATION
		&& !(ip->Type == ITEM_HELPER+66)	//��Ÿ������ �ʴ���
#endif //PBG_ADD_SANTAINVITATION
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON	// �׺� ������
		&& !( ip->Type == ITEM_HELPER+71 || ip->Type == ITEM_HELPER+72 || ip->Type == ITEM_HELPER+73 || ip->Type == ITEM_HELPER+74 || ip->Type == ITEM_HELPER+75 )
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef PBG_ADD_CHARACTERCARD
		&& !(ip->Type == ITEM_HELPER+97)	//���˻� ĳ���� ī��
		&& !(ip->Type == ITEM_HELPER+98)	//��ũ�ε� ĳ���� ī��
		&& !(ip->Type == ITEM_POTION+91)	//��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		&& !(ip->Type == ITEM_HELPER+99)	//ĳ���� ���� ����
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
		&& !(ip->Type >= ITEM_HELPER+117 && ip->Type <= ITEM_HELPER+120)	//Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
#endif //PBG_ADD_SECRETITEM
#ifdef KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
		&& !(ip->Type==ITEM_POTION+133)
#endif // KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
      )  //  ������.
	{
		int Success = false;
        int arrow = false;
		if(ip->Type>=ITEM_POTION && ip->Type<=ITEM_POTION+8)    //  ���� ����.
		{
          	sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
		else if(ip->Type == ITEM_POTION+21 && Level == 3 )    //  ������ǥ�� ����.
		{
          	sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
		else if(ip->Type==ITEM_BOW+7 || ip->Type==ITEM_BOW+15)  //  ȭ�� ����.
		{
          	sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
            arrow = true;
		}
		else if(ip->Type>=ITEM_POTION+35 && ip->Type<=ITEM_POTION+40)    //  ���� ����.
		{
          	sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
#ifndef KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP			// #ifndef
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
		else if(ip->Type==ITEM_POTION+133)		// ����Ʈ SDȸ�� ����
		{
          	sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#endif // KJH_FIX_BTS251_ELITE_SD_POTION_TOOLTIP
#ifdef HELLOWIN_EVENT
		else if(ip->Type >= ITEM_POTION+46 && ip->Type <= ITEM_POTION+50)
		{
			sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
#endif // HELLOWIN_EVENT
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if(ip->Type >= ITEM_POTION+153 && ip->Type <= ITEM_POTION+156)	// ��Ÿ����Ʈ ~ ����� �������� ������
		{
			sprintf(TextList[TextNum],GlobalText[69],ip->Durability);		// 69 "����: %d"
			Success = true;
		}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		//^ �渱 ���� ǥ��
		else if(ip->Type >= ITEM_HELPER+32 && ip->Type <= ITEM_HELPER+33)	// �渱 ������ ����
		{
			sprintf(TextList[TextNum],GlobalText[1181],ip->Durability, 20);	// "%d�� / %d��"(���簹�� / �ִ�)
			Success = true;
		}
		else if(ip->Type == ITEM_HELPER+34)	// �ͼ��� ����
		{
			sprintf(TextList[TextNum],GlobalText[1181],ip->Durability, 10);	// "%d�� / %d��"(���簹�� / �ִ�)
			Success = true;
		}
		else if(ip->Type == ITEM_HELPER+37)	// �渱�� ���Ǹ�
		{
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
			if( ip->bPeriodItem == false )
			{
				sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
				Success = true;
			}
#else // KJH_ADD_PERIOD_ITEM_SYSTEM
			sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
			Success = true;
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
		}
		else if(ip->Type>=ITEM_HELPER && ip->Type<=ITEM_HELPER+7)   //  �����.
		{
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
			if( ip->bPeriodItem == false )
			{
				sprintf(TextList[TextNum],GlobalText[70],ip->Durability);
				Success = true;
			}
#else // KJH_ADD_PERIOD_ITEM_SYSTEM
          	sprintf(TextList[TextNum],GlobalText[70],ip->Durability);
			Success = true;
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
		}
        else if(ip->Type == ITEM_HELPER+10)                             //���Ź���
		{
          	sprintf(TextList[TextNum],GlobalText[95],ip->Durability);
			Success = true;
		}
#ifdef LDK_FIX_GUARDIAN_CHANGE_LIFEWORD
		else if(ip->Type == ITEM_HELPER+64 || ip->Type == ITEM_HELPER+65)
		{
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
			if( ip->bPeriodItem == false )
			{
				sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
				Success = true;
			}
#else // KJH_ADD_PERIOD_ITEM_SYSTEM
			sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
			Success = true;
#endif // #ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
		}
#endif //LDK_FIX_GUARDIAN_CHANGE_LIFEWORD
#ifdef YDG_ADD_SKELETON_PET
		else if(ip->Type == ITEM_HELPER+67 || ip->Type == ITEM_HELPER+80
			|| ip->Type == ITEM_HELPER+106 ||ip->Type == ITEM_HELPER+123)
		{
#ifdef LJH_FIX_IGNORING_EXPIRATION_PERIOD
			sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
			Success = true;
#else  //LJH_FIX_IGNORING_EXPIRATION_PERIOD
			if( ip->bPeriodItem == false )
			{
				sprintf(TextList[TextNum],GlobalText[70],ip->Durability);	// "����: %d"
				Success = true;
			}
#endif //LJH_FIX_IGNORING_EXPIRATION_PERIOD
		}
#endif	// YDG_ADD_SKELETON_PET
#ifdef CSK_FREE_TICKET
		// ��������� ������ ���Ƚ�� ����
		else if(ip->Type >= ITEM_HELPER+46 && ip->Type <= ITEM_HELPER+48)
		{
			// 2260 "%d�� ��� ����"
			sprintf(TextList[TextNum], GlobalText[2260], ip->Durability);
			Success = true;
		}
#endif // CSK_FREE_TICKET
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
		// ��������� ������ ���Ƚ�� ����
		else if(ip->Type >= ITEM_HELPER+125 && ip->Type <= ITEM_HELPER+127)
		{
			// 2260 "%d�� ��� ����"
			sprintf(TextList[TextNum], GlobalText[2260], ip->Durability);
			
			if (ip->Type == ITEM_HELPER+126)
			{
				TextNum++;
				// 3105 "��-����ϸʿ� ������ �����մϴ�"
				sprintf(TextList[TextNum], GlobalText[3105]);
			
			}
			else if (ip->Type == ITEM_HELPER+127)
			{
				TextNum++;
				// 3106 "�Ͽ��ϸʿ� ������ �����մϴ�"
				sprintf(TextList[TextNum], GlobalText[3106]);
			}
			Success = true;
		}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef CSK_LUCKY_CHARM	
		else if( ip->Type == ITEM_POTION+53 )// ����� ����
		{
			// 2296 "%d% ���� ����Ȯ�� ���"
			sprintf(TextList[TextNum], GlobalText[2296], ip->Durability);
			Success = true;
		}
#endif //CSK_LUCKY_CHARM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
		// ��������� ������ ���Ƚ�� ����
		else if(ip->Type == ITEM_HELPER+61)
		{
			// 2260 "%d�� ��� ����"
			sprintf(TextList[TextNum], GlobalText[2260], ip->Durability);
			Success = true;
		}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
		//����� ����
		else if(ip->Type == ITEM_POTION+100)
		{
			//69 "����: %d"
			sprintf(TextList[TextNum],GlobalText[69],ip->Durability);
			Success = true;
		}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef CSK_LUCKY_SEAL
		/*
		else if( ip->Type >= ITEM_HELPER+43 && ip->Type <= ITEM_HELPER+45 )
		{
		// 2252 "%s %d�� ��� ����"
		sprintf( TextList[TextNum], "%s %d%s %s", p->Name, ip->Durability, GlobalText[2298], GlobalText[2302] );
		Success = true;
		}
		*/
#endif //CSK_LUCKY_SEAL
#ifdef YDG_ADD_CS5_PORTAL_CHARM
		else if(ip->Type == ITEM_HELPER+70 )	// �̵��� ����
		{
			if (ip->Durability == 2)
			{
				sprintf(TextList[TextNum], GlobalText[2605]);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
			}
			else if (ip->Durability == 1)
			{
				sprintf(TextList[TextNum], GlobalText[2606]);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				g_PortalMgr.GetPortalPositionText(TextList[TextNum]);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
			}
		}
#endif	// YDG_ADD_CS5_PORTAL_CHARM

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ ������ Ƽ�� ����
		else if( ip->Type >= ITEM_HELPER+135 && ip->Type <= ITEM_HELPER+145 )
		{
			sprintf(TextList[TextNum], GlobalText[2261]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			Success = true;
		}
#endif // LEM_ADD_LUCKYITEM

        //  �������� �����ϴ� ������. (��� �����ϴ� ������).
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
		else if ( (bDurExist) && (ip->bPeriodItem == false) )		// �Ⱓ�� �������� �������� �������� �ʴ´�.
#else // KJH_ADD_PERIOD_ITEM_SYSTEM
		else if ( bDurExist)
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
        {
            int maxDurability = calcMaxDurability ( ip, p, Level );

            sprintf(TextList[TextNum],GlobalText[71],ip->Durability, maxDurability);
			Success = true;
        }
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// �������
		else if( ip->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN 
				&& ip->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END ) // ���� ���� 100% ���� ����
		{
			// ���� ���� 100% ���� ����
			sprintf(TextList[TextNum], GlobalText[2732+(ip->Type-(MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN))]);
			
			Success = true;
		}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		else if(ip->Type == ITEM_HELPER+121)		// ������ Ƚ��
		{
			// 2260 "%d�� ��� ����"
			sprintf(TextList[TextNum], GlobalText[2260], ip->Durability);
			Success = true;
		}
#endif //LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121

		if(Success)
		{
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
    }
    else
    {
        if(ip->Type == ITEM_HELPER+10)                             //���Ź���
		{
          	sprintf(TextList[TextNum],GlobalText[95],ip->Durability);

            TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
    }

    //  ȭ���� ���.
    if( ip->Type==ITEM_BOW+7 || ip->Type==ITEM_BOW+15)
	{
        if ( Level>=1 )
        {
            int value = Level*2+1;

            //  �߰� ���ݷ� 2%����.
          	sprintf(TextList[TextNum],GlobalText[577], value );
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;

            //  �߰� ���ݷ� 1 ����.
            sprintf(TextList[TextNum],GlobalText[88], 1);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
        }
    }

#ifdef _VS2008PORTING
	for(int i=0;i<MAX_RESISTANCE;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_RESISTANCE;i++)
#endif // _VS2008PORTING
	{
        //  ���� ���׷�.
		if(p->Resistance[i])
		{
			sprintf(TextList[TextNum],GlobalText[72],GlobalText[48+i],Level+1);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	if(ip->RequireLevel && ip->Type!=ITEM_HELPER+14 )    //  �䱸 ����. ( ��ũ�� ���� )
	{
		sprintf(TextList[TextNum],GlobalText[76],ip->RequireLevel);
		if(CharacterAttribute->Level < ip->RequireLevel)
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
      		sprintf(TextList[TextNum],GlobalText[74],ip->RequireLevel - CharacterAttribute->Level);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
    		TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	int si_iNeedStrength= 0, si_iNeedDex = 0;
	bool bRequireStat	= true;

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �䱸 ���� ǥ�� ����
	if( Check_LuckyItem( ip->Type ) ) bRequireStat = false;
#endif // LEM_ADD_LUCKYITEM

	if( Level >= ip->Jewel_Of_Harmony_OptionLevel )
	{
		StrengthenCapability SC;
		g_pUIJewelHarmonyinfo->GetStrengthenCapability( &SC, ip, 0 );

		if( SC.SI_isNB ) 
		{
			si_iNeedStrength = SC.SI_NB.SI_force;
			si_iNeedDex      = SC.SI_NB.SI_activity;
		}
	}	
#ifdef ADD_SOCKET_STATUS_BONUS
	if (ip->SocketCount > 0)
	{
		for (int i = 0; i < ip->SocketCount; ++i)
		{
			if (ip->SocketSeedID[i] == 38)	// �ʿ��� ����
			{
				int iReqStrengthDown = g_SocketItemMgr.GetSocketOptionValue(ip, i);
				si_iNeedStrength += iReqStrengthDown;
			}
			else if (ip->SocketSeedID[i] == 39)	// �ʿ�� ����
			{
				int iReqDexterityDown = g_SocketItemMgr.GetSocketOptionValue(ip, i);
				si_iNeedDex += iReqDexterityDown;
			}
		}
	}
#endif	// ADD_SOCKET_STATUS_BONUS

	if(ip->RequireStrength && bRequireStat ) //  �䱸��.
	{
		sprintf(TextList[TextNum],GlobalText[73],ip->RequireStrength - si_iNeedStrength);

		WORD Strength;
		Strength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
     	if( Strength < ip->RequireStrength - si_iNeedStrength )
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
      		sprintf(TextList[TextNum],GlobalText[74],(ip->RequireStrength - Strength) - si_iNeedStrength );
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
			if( si_iNeedStrength != 0 )
			{
				TextListColor[TextNum] = TEXT_COLOR_YELLOW;
			}
			else
			{
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
			}
    		
			TextBold[TextNum] = false;
			TextNum++;
		}
	}
	if(ip->RequireDexterity && bRequireStat )//  �䱸 ��ø.
	{
		sprintf(TextList[TextNum],GlobalText[75],ip->RequireDexterity - si_iNeedDex );
		WORD Dexterity;
		Dexterity = CharacterAttribute->Dexterity + CharacterAttribute->AddDexterity;
		if( Dexterity < ( ip->RequireDexterity - si_iNeedDex) )
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;

			sprintf(TextList[TextNum],GlobalText[74],(ip->RequireDexterity - Dexterity) - si_iNeedDex);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
    		if( si_iNeedDex != 0 )
			{
				TextListColor[TextNum] = TEXT_COLOR_YELLOW;
			}
			else
			{
				TextListColor[TextNum] = TEXT_COLOR_WHITE;
			}
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	if(ip->RequireVitality && bRequireStat ) //  �䱸ü��.
	{
		sprintf(TextList[TextNum],GlobalText[1930],ip->RequireVitality);

		WORD Vitality;
		Vitality = CharacterAttribute->Vitality + CharacterAttribute->AddVitality;
     	if(Vitality < ip->RequireVitality)
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
      		sprintf(TextList[TextNum],GlobalText[74],ip->RequireVitality - Vitality);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
    		TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	if(ip->RequireEnergy && bRequireStat )  //  �䱸 ������.
	{
   		sprintf(TextList[TextNum],GlobalText[77],ip->RequireEnergy);

        WORD Energy;
		Energy = CharacterAttribute->Energy   + CharacterAttribute->AddEnergy;  

		if( Energy < ip->RequireEnergy)
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
      		sprintf(TextList[TextNum],GlobalText[74],ip->RequireEnergy - Energy);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
    		TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	if(ip->RequireCharisma && bRequireStat ) //  �䱸���.
	{
		sprintf(TextList[TextNum],GlobalText[698],ip->RequireCharisma);

		WORD Charisma;
		Charisma = CharacterAttribute->Charisma + CharacterAttribute->AddCharisma;
     	if(Charisma < ip->RequireCharisma)
		{
    		TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
      		sprintf(TextList[TextNum],GlobalText[74],ip->RequireCharisma - Charisma);
			TextListColor[TextNum] = TEXT_COLOR_RED;
			TextBold[TextNum] = false;
			TextNum++;
		}
		else
		{
    		TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
	}

	if(IsRequireClassRenderItem(ip->Type))
    {
        RequireClass(p);    //  �䱸 Ŭ����.
    }

    //  ����.
	if(ip->Type>=MODEL_BOOTS-MODEL_ITEM && ip->Type<MODEL_BOOTS+MAX_ITEM_INDEX-MODEL_ITEM)
	{
        //  �̵� �ӵ� ���.
		if(Level >= 5)
		{
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			
			sprintf(TextList[TextNum],GlobalText[78]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = true;TextNum++;
		}
	}
    //  �尩.
	if(ip->Type>=MODEL_GLOVES-MODEL_ITEM && ip->Type<MODEL_GLOVES+MAX_ITEM_INDEX-MODEL_ITEM)
	{
        //  ���� �ӵ� ���.
		if(Level >= 5)
		{
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			
			sprintf(TextList[TextNum],GlobalText[93]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = true;TextNum++;
		}
	}
    //  ������.
	if ( ( ip->Type>=MODEL_STAFF-MODEL_ITEM && ip->Type<MODEL_STAFF+MAX_ITEM_INDEX-MODEL_ITEM ) 
		 || ( ip->Type==(MODEL_SWORD+31-MODEL_ITEM) ) 
		 || ( ip->Type==(MODEL_SWORD+23-MODEL_ITEM) )
		 || ( ip->Type==(MODEL_SWORD+25-MODEL_ITEM) )
		 || ( ip->Type==(MODEL_SWORD+21-MODEL_ITEM) )
#ifdef KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
		 || ( ip->Type==(MODEL_SWORD+28-MODEL_ITEM) )
#endif // KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
	   )
	{
		sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

		// ��ȯ����� å�̸� ���ַ� �ƴϸ� ����.
		int nText = ITEM_STAFF+21 <= ip->Type && ip->Type <= ITEM_STAFF+29 ? 1691 : 79;
		::sprintf(TextList[TextNum], GlobalText[nText], ip->MagicPower);

		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = true;
		TextNum++;
	}
    //  ������ �� ���ݷ� ��� �ɼ� ���.
#ifdef CSK_FIX_EPSOLUTESEPTER

	if(IsCepterItem(ip->Type) == true)

#else // CSK_FIX_EPSOLUTESEPTER 

	if ( (ip->Type>=ITEM_MACE+8 && ip->Type<=ITEM_MACE+15) 
#ifdef KJH_FIX_ABSOLUTE_CEPTER_TOOLTIP
		|| (ip->Type == ITEM_MACE+17)					// ���ַ�Ʈ����
#endif // KJH_FIX_ABSOLUTE_CEPTER_TOOLTIP
		)
		
#endif // CSK_FIX_EPSOLUTESEPTER
    {
		sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

        //  �� ���ݷ� ���.
        sprintf(TextList[TextNum],GlobalText[1234],ip->MagicPower);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = true;TextNum++;
    }

	if(ip->SpecialNum > 0)
	{
#ifdef LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR	// �ΰ��Ә��� ������ ����̵��� ��� �̹� �ϵ��ڵ����� �Ǿ����ϴ�.
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int iModelType = ip->Type;
		int iStartModelType = ITEM_HELPER+109;
		int iEndModelType = ITEM_HELPER+115;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

		if(!( ITEM_HELPER+109 <= ip->Type  && ITEM_HELPER+115 >= ip->Type ))
		{
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
		}
#else // LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
		sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
#endif // LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
	}

	if( ip->option_380 != 0 )
	{
		std::vector<string> Text380;

		if( g_pItemAddOptioninfo )
		{
			g_pItemAddOptioninfo->GetItemAddOtioninfoText( Text380, ip->Type );

			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

#ifdef _VS2008PORTING
			for( int i = 0; i < (int)Text380.size(); ++i )
#else // _VS2008PORTING
			for( int i = 0; i < Text380.size(); ++i )
#endif // _VS2008PORTING
			{
#ifdef YDG_FIX_380ITEM_OPTION_TEXT_SD_PERCENT_MISSING
				strncpy(TextList[TextNum], Text380[i].c_str(), 100);
#else	// YDG_FIX_380ITEM_OPTION_TEXT_SD_PERCENT_MISSING
				sprintf(TextList[TextNum], (char*)Text380[i].c_str() );
#endif	// YDG_FIX_380ITEM_OPTION_TEXT_SD_PERCENT_MISSING
				TextListColor[TextNum] = TEXT_COLOR_REDPURPLE;TextBold[TextNum] = true;TextNum++;
			}

			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
		}
	}
#ifndef PBG_MOD_NEWCHAR_MONK_WING_2
#ifdef PBG_MOD_NEWCHAR_MONK_WING
	if(ip->Type==ITEM_WING+49)
	{
		sprintf(TextList[TextNum],GlobalText[578],15+Level);	// ������ ��%���
		TextListColor[TextNum] = TEXT_COLOR_BLUE;				// �ɼ���ġ�� ��¿���
		TextNum++;
	}
#endif //PBG_MOD_NEWCHAR_MONK_WING
#endif //PBG_MOD_NEWCHAR_MONK_WING_2
#ifdef ADD_SOCKET_ITEM
	if (g_SocketItemMgr.IsSocketItem(ip));	// ���Ͼ������� ��ȭ���� �ɼ� ��� ����
	else
#endif	// ADD_SOCKET_ITEM
	if( ip->Jewel_Of_Harmony_Option != 0 )
	{
		StrengthenItem type = g_pUIJewelHarmonyinfo->GetItemType( static_cast<int>(ip->Type) );

		if( type < SI_None )
		{
			if( g_pUIJewelHarmonyinfo->IsHarmonyJewelOption( type, ip->Jewel_Of_Harmony_Option ) )
			{
				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

				HARMONYJEWELOPTION harmonyjewel = g_pUIJewelHarmonyinfo->GetHarmonyJewelOptionInfo( type, ip->Jewel_Of_Harmony_Option );

				if(type == SI_Defense && ip->Jewel_Of_Harmony_Option == 7)
				{
					sprintf(TextList[TextNum], "%s +%d%%", harmonyjewel.Name, harmonyjewel.HarmonyJewelLevel[ip->Jewel_Of_Harmony_OptionLevel]);
				}
				else
				{
					sprintf(TextList[TextNum], "%s +%d", harmonyjewel.Name, harmonyjewel.HarmonyJewelLevel[ip->Jewel_Of_Harmony_OptionLevel]);
				}

				if( Level >= ip->Jewel_Of_Harmony_OptionLevel ) TextListColor[TextNum] = TEXT_COLOR_YELLOW;
				else TextListColor[TextNum] = TEXT_COLOR_GRAY;
				
				TextBold[TextNum] = true;TextNum++;

				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			}
			else
			{
				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

				sprintf( TextList[TextNum], "%s : %d %d %d"
					   ,GlobalText[2204]
					   , (int)type
					   , (int)ip->Jewel_Of_Harmony_Option
					   , (int)ip->Jewel_Of_Harmony_OptionLevel
					   );

				TextListColor[TextNum] = TEXT_COLOR_DARKRED;
				TextBold[TextNum] = true;TextNum++;

				sprintf( TextList[TextNum], GlobalText[2205] );

				TextListColor[TextNum] = TEXT_COLOR_DARKRED;
				TextBold[TextNum] = true;TextNum++;

				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			}
		}
	}

    //  ��Ʈ �⺻ �ɼ�.
	TextNum = g_csItemOption.RenderDefaultOptionText( ip, TextNum );

    //  Ư�� ���.
	int iMana;
#ifdef _VS2008PORTING
	for(int i=0;i<ip->SpecialNum;i++)
#else // _VS2008PORTING
	for(i=0;i<ip->SpecialNum;i++)
#endif // _VS2008PORTING
	{
#ifdef LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
		if( ITEM_HELPER+109 <= ip->Type  && ITEM_HELPER+115 >= ip->Type )
		{
			break;
		}
#endif // LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR

		GetSkillInformation( ip->Special[i], 1, NULL, &iMana, NULL);
        GetSpecialOptionText ( ip->Type, TextList[TextNum], ip->Special[i], ip->SpecialValue[i], iMana );

       	TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;TextNum++;

        //  ���.
		if(ip->Special[i] == AT_LUCK)
		{
			sprintf(TextList[TextNum],GlobalText[94],ip->SpecialValue[i]);
     		TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;
		}
        else if ( ip->Special[i]==AT_SKILL_RIDER )
        {
			sprintf(TextList[TextNum], GlobalText[179] );
     		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
        }
        else if ( ip->Special[i]==AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= ip->Special[i] && ip->Special[i] <= AT_SKILL_ASHAKE_UP+4))
        {
			sprintf(TextList[TextNum], GlobalText[1201] );
     		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
        }
#ifdef KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
		// ���˻� ��
		else if ( (ip->Special[i]==AT_IMPROVE_DAMAGE) && 
					( (ip->Type==ITEM_SWORD+31)
					|| (ip->Type==ITEM_SWORD+21)
					|| (ip->Type==ITEM_SWORD+23)
					|| (ip->Type==ITEM_SWORD+25)
					|| (ip->Type==ITEM_SWORD+28)
					)
				)
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;
		}
#else // KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
		else if ( ip->Type==ITEM_SWORD+31 && ip->Special[i]==AT_IMPROVE_DAMAGE )
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;
		}
		else if ( ip->Type==ITEM_SWORD+21 && ip->Special[i]==AT_IMPROVE_DAMAGE )
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;
		}
		else if ( ip->Type==ITEM_SWORD+23 && ip->Special[i]==AT_IMPROVE_DAMAGE )
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;
		}
		else if(ip->Type == ITEM_SWORD+25 && ip->Special[i]==AT_IMPROVE_DAMAGE)
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;	
		}
		else if(ip->Type == ITEM_SWORD+28 && ip->Special[i]==AT_IMPROVE_DAMAGE)
		{
			sprintf(TextList[TextNum],GlobalText[89],ip->SpecialValue[i]);
       		TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++;	
		}
#endif // KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
	}

	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	//^ �渱 ������ ���� ����
	if(ip->Type == ITEM_HELPER+32 || ip->Type == ITEM_HELPER+33)
	{
		sprintf(TextList[TextNum], GlobalText[1917]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW; 
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+34 || ip->Type == ITEM_HELPER+35)
	{
		sprintf(TextList[TextNum], GlobalText[1918]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW; 
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+36)
	{
		sprintf(TextList[TextNum], GlobalText[1919]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW; 
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+37)
	{
		GetSpecialOptionText ( 0, TextList[TextNum], AT_SKILL_PLASMA_STORM_FENRIR, 0, 0 );
   		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false; TextNum++; SkipNum++;
		if(ip->Option1 == 0x01)	// ���� ������ ���� �ɼ�
		{
			sprintf(TextList[TextNum], GlobalText[1860], 10); // 1860 "���� ������ %d%% ����"
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[579]); // 579 "�̵� �ӵ� ���"
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;
		}
		else if(ip->Option1 == 0x02) // ���� ������ ���� �ɼ�
		{
			sprintf(TextList[TextNum], GlobalText[1861], 10); // 1861 "���� ������ %d%% ���"
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[579]); // 579 "�̵� �ӵ� ���"
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;
		}
		else if(ip->Option1 == 0x04)
		{
			WORD wLevel = CharacterAttribute->Level;
			//1867 "���� %d ����"
			//1868 "���� %d ����"
			//1869 "���ݷ� %d ����"
			//1870 "���� %d ����"
			//1871 "ȯ��������� ū ������ ���� �������� ����"
			//1872 "Ư���� ���۵Ǿ����ϴ�."
	
			sprintf(TextList[TextNum], GlobalText[1867], (wLevel / 2)); 
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[1868], (wLevel / 2));
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[1869], (wLevel / 12));
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[1870], (wLevel / 25));
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;

			sprintf(TextList[TextNum], "\n");
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[1871], (Hero->Level / 2));
			TextListColor[TextNum] = TEXT_COLOR_GREEN; 
			TextNum++;

			sprintf(TextList[TextNum], GlobalText[1872], (Hero->Level / 2));
			TextListColor[TextNum] = TEXT_COLOR_GREEN; 
			TextNum++;
		}

		sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

		sprintf(TextList[TextNum], GlobalText[1920]);
		TextListColor[TextNum] = TEXT_COLOR_YELLOW; 
		TextNum++;
		
		if(ip->Option1 == 0x00)	// ���׷��̵� ���� �渱�� ���Ǹ�
		{
			sprintf(TextList[TextNum], GlobalText[1929]);
			TextListColor[TextNum] = TEXT_COLOR_YELLOW; 
			TextNum++;
		}
	}
#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
    else if(ip->Type == ITEM_HELPER+10)	// �Ϲ� ���Ź����� ���޽��� �߰�
	{
		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	// ����Ʈ �ذ����� ���Ź��� ������ ����(���� ������ ����� ����)
	else if(ip->Type == ITEM_HELPER+39)
	{
		// ���� ����
		char strText[100];
		sprintf(strText, GlobalText[959], 10);	// 959 "���� ���� +%d"
		sprintf(TextList[TextNum], "%s%%", strText);
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		TextNum++;

		// �����
		WORD wlevel = CharacterAttribute->Level;
		sprintf(TextList[TextNum], GlobalText[2225], wlevel);	// 2225 "����� +%d"
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		TextNum++;

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
	else if (ip->Type == ITEM_POTION+63)
	{
		TextListColor[TextNum] = TEXT_COLOR_WHITE; 
		sprintf(TextList[TextNum], GlobalText[2244]); TextNum++;
	}
	else if (ip->Type == ITEM_POTION+52)
	{
		TextListColor[TextNum] = TEXT_COLOR_WHITE; 
		sprintf(TextList[TextNum], GlobalText[2323]); TextNum++;
		TextListColor[TextNum] = TEXT_COLOR_WHITE; 
		sprintf(TextList[TextNum], GlobalText[2011]); TextNum++;
	}
	// �ҷ��� �̺�Ʈ ���Ź��� ������ ����
	else if(ip->Type == ITEM_HELPER+40)
	{
		sprintf(TextList[TextNum], "%s", GlobalText[2232]);	// 2232 "�ҷ��� ������ ��⼼��."
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		TextNum++;	

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
	else if(ip->Type == ITEM_HELPER+41)	// ũ�������� �̺�Ʈ ���Ź��� ����
	{
		// �߰� ���ݷ� +20
		sprintf(TextList[TextNum], GlobalText[88], 20);	// 88 "�߰� ���ݷ� +%d"
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		TextNum++;

		// �߰� ���� +20
		sprintf(TextList[TextNum], GlobalText[89], 20);	// 89 "�߰� ���� +%d"
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		TextNum++;

		// ��ĭ
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], "%s", GlobalText[2248]);	// 2248 "�ູ�� ũ�������� ��������."
		TextListColor[TextNum] = TEXT_COLOR_RED; 
		TextNum++;

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
#ifdef PJH_ADD_PANDA_CHANGERING
	else if( ip->Type == ITEM_HELPER+76 )
	{
		sprintf(TextList[TextNum], GlobalText[2743]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2744]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		sprintf(TextList[TextNum], GlobalText[2745]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
#endif //#ifdef PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	else if(ip->Type == ITEM_HELPER+122)	// ���̷��� ���Ź���
	{
		sprintf(TextList[TextNum], GlobalText[3065]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3066]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3067]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3072]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
	else if(ip->Type == ITEM_POTION+51)	// ũ���������Ǻ�
	{
		sprintf(TextList[TextNum], "%s", GlobalText[2244]);	// 2244 "�ٴڿ� ������ ������ �����ϴ�."
		TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		TextNum++;
	}
	else if(ip->Type == ITEM_HELPER+42)	// GM ���Ź��� ����
	{
		// 976 "�����Ӽ� ��ų ���ݷ� ���� +%d"			 
		// 977 "���Ӽ� ��ų ���ݷ� ���� +%d"			 
		// 978 "�����Ӽ� ��ų ���ݷ� ���� +%d"			 
		// 979 "�ҼӼ� ��ų ���ݷ� ���� +%d"			 
		// 980 "���Ӽ� ��ų ���ݷ� ���� +%d"			 
		// 981 "�ٶ��Ӽ� ��ų ���ݷ� ���� +%d"			 
		// 982 "���Ӽ� ��ų ���ݷ� ���� +%d"

		for(int i=0; i<7; ++i)
		{
			sprintf(TextList[TextNum], GlobalText[976+i], 255);
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
			TextNum++;
		}

#ifdef YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
#endif	// YDG_MOD_CHANGE_RING_EQUIPMENT_LIMIT
	}
#ifdef PBG_ADD_SANTAINVITATION
	//��Ÿ������ �ʴ���.
	else if(ip->Type == ITEM_HELPER+66)
	{
		//2260 "%d"�� ��� ����.
		TextNum--;
		sprintf(TextList[TextNum], GlobalText[2260], ip->Durability);
 		TextListColor[TextNum] = TEXT_COLOR_RED;
 		TextNum++;
 		
 		//2589 ���콺 ������ Ŭ�� �� ��Ÿ������ �̵�����
 		sprintf(TextList[TextNum], "%s", GlobalText[2589]);
 		TextListColor[TextNum] = TEXT_COLOR_BLUE;
 		TextNum++;
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	//����� ����
	else if(ip->Type == ITEM_POTION+100)
	{
		//1887 "NPC���� ����ϸ� �پ��� ������ �帳�ϴ�."
		sprintf(TextList[TextNum], GlobalText[1887], ip->Durability);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
 		TextNum++;
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_SKELETON_PET
	else if( ip->Type == ITEM_HELPER+123 )	// ���̷��� ��
	{
		TextNum--; SkipNum--;

		sprintf(TextList[TextNum], GlobalText[3071]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;

		sprintf(TextList[TextNum], GlobalText[3072]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif	// YDG_ADD_SKELETON_PET
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
	else if(g_pMyInventory->IsInvenItem(ip->Type))
	{
		TextNum--; SkipNum--;
		
		// ������� ��� "(�����)" ���� ���
		if (ip->Durability == 254)
		{
			sprintf(TextList[TextNum], GlobalText[3143]);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
			sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		}

		// ������ ���� ���
		switch (ip->Type)
		{
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
			// ��� ������
			case ITEM_HELPER+128:	// ��������
			case ITEM_HELPER+129:	// ��������
				sprintf(TextList[TextNum], GlobalText[3121]);
				break;

			// ���� ������
			case ITEM_HELPER+134:	// ����
				sprintf(TextList[TextNum], GlobalText[3123]);
				break;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
			// �� ������
			case ITEM_HELPER+130:	// ��ũ��
			case ITEM_HELPER+131:	// ��������
			case ITEM_HELPER+132:	// ����ũ��
			case ITEM_HELPER+133:	// ����������
				sprintf(TextList[TextNum], GlobalText[3122]);
				break;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2

			default:
				break;
		}

		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
		
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;


		// ������ ������ ȿ�� ���
		switch (ip->Type)
		{
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
			case ITEM_HELPER+128:	// ��������
				sprintf(TextList[TextNum], GlobalText[965], 10);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
			case ITEM_HELPER+129:	// ��������
				sprintf(TextList[TextNum], GlobalText[967], 10);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
			case ITEM_HELPER+134:	// ����
				sprintf(TextList[TextNum], GlobalText[3126], 20);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
			case ITEM_HELPER+130:	// ��ũ��
				sprintf(TextList[TextNum], GlobalText[3132], 50);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
			case ITEM_HELPER+131:	// ��������
				sprintf(TextList[TextNum], GlobalText[3134], 50);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
			case ITEM_HELPER+132:	// ����ũ��
#ifdef LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				sprintf(TextList[TextNum], GlobalText[3132], 100);
#else //LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				sprintf(TextList[TextNum], GlobalText[3132], 150);
#endif //LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
#ifdef LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				sprintf(TextList[TextNum], GlobalText[3133], 500);
#else //LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				sprintf(TextList[TextNum], GlobalText[3133], 50);
#endif //LJH_MOD_CHANGED_GOLDEN_OAK_CHARM_STAT
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
			case ITEM_HELPER+133:	// ����������
				sprintf(TextList[TextNum], GlobalText[3134], 150);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf(TextList[TextNum], GlobalText[3135], 50);
				TextListColor[TextNum] = TEXT_COLOR_BLUE;
				TextBold[TextNum] = false;
				TextNum++;
				break;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
			default:
				break;
		}

		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;
		sprintf(TextList[TextNum],"\n"); TextNum++; SkipNum++;

		// �κ����� �����ۿ� "�κ����� ������ ���콺�� ����Ҽ� �ֽ��ϴ�" ���� ���
		sprintf(TextList[TextNum], GlobalText[3124]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef PBG_MOD_SECRETITEM
	else if(ip->Type >= ITEM_HELPER+117 && ip->Type <= ITEM_HELPER+120)
	{
		TextNum--;		
		sprintf(TextList[TextNum], GlobalText[3142]);
 		TextListColor[TextNum] = TEXT_COLOR_WHITE;
 		TextNum++;

		char _str_dest[4][32] = {"6", "24", "7", "30"};
		char _str_src[2][32] ={0,};
		int _index =ip->Type - (ITEM_HELPER+117);
		int _index_src = (int)(_index/2);

		strcpy(_str_src[_index_src], GlobalText[2299-_index_src]);
		strcat(_str_dest[_index], _str_src[_index_src]);
		sprintf(TextList[TextNum], GlobalText[2533], _str_dest[_index]);
		TextListColor[TextNum] = TEXT_COLOR_BLUE;
		TextNum++;
	}
#endif //PBG_MOD_SECRETITEM
#ifdef PBG_ADD_NEWCHAR_MONK
    else if(ip->Type == ITEM_HELPER+68)
	{
		sprintf(TextList[TextNum], GlobalText[3088]);
		TextListColor[TextNum] = TEXT_COLOR_RED;
		TextBold[TextNum] = false;
		TextNum++;
	}
#endif //PBG_ADD_NEWCHAR_MONK
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
	if( ip->bPeriodItem == true )		// �Ⱓ�� ������
	{
		if( ip->bExpiredPeriod == true )		// �Ⱓ����
		{
#ifdef KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			sprintf(TextList[TextNum], GlobalText[3266]);
#else // KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			sprintf(TextList[TextNum], "���������");
#endif // KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			TextListColor[TextNum] = TEXT_COLOR_RED; 	
		}
		else
		{
#ifdef KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			sprintf(TextList[TextNum], GlobalText[3265]);
#else // KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			sprintf(TextList[TextNum], "������");
#endif // KJH_FIX_BTS260_PERIOD_ITEM_INFO_TOOLTIP
			TextListColor[TextNum] = TEXT_COLOR_ORANGE; 	
			TextNum++;
			SkipNum++;

			sprintf(TextList[TextNum], "%d-%02d-%02d  %02d:%02d", ExpireTime->tm_year+1900, ExpireTime->tm_mon+1, 
					ExpireTime->tm_mday, ExpireTime->tm_hour, ExpireTime->tm_min);
			TextListColor[TextNum] = TEXT_COLOR_BLUE; 
		}

		TextNum++;
	}
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
	if (!bItemTextListBoxUse)
	{
#endif	// ASG_ADD_NEW_QUEST_SYSTEM

		// �κ��丮���� ���� �������� �˻��Ͽ�, ������ ���������� �κ��丮�� �ִ¾��������� ���θ� ����.
#ifdef LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY
		bool bThisisEquippedItem = false;
#ifdef PBG_FIX_SETITEMTOOLTIP
		// ��Ʈ ������ �κ����� ���Կ��� ������ �����۰� ���� �ɼ���¸�������
		int _iEquipIndex = g_pMyInventory->GetPointedItemIndex();
		if((_iEquipIndex != -1) && (_iEquipIndex>=EQUIPMENT_WEAPON_RIGHT && _iEquipIndex<MAX_EQUIPMENT))
		{
			bThisisEquippedItem=false;
		}
		else
		{
			bThisisEquippedItem=true;
		}
#else //PBG_FIX_SETITEMTOOLTIP
		//ITEM *pFindItem = SEASON3B::CNewUIInventoryCtrl::FindItemByKey( ip->Key );	// �κ��丮 �˻����� ���� ���������� ���� ����.
		SEASON3B::CNewUIInventoryCtrl * pNewInventoryCtrl = g_pMyInventory->GetInventoryCtrl();
		ITEM *pFindItem = pNewInventoryCtrl->FindItemByKey( ip->Key );	// �κ��丮 �˻����� ���� ���������� ���� ����.
		(pFindItem==NULL)?bThisisEquippedItem=true:bThisisEquippedItem=false;
#endif //PBG_FIX_SETITEMTOOLTIP
		TextNum = g_csItemOption.RenderSetOptionListInItem ( ip, TextNum, bThisisEquippedItem );
#else // LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY
		TextNum = g_csItemOption.RenderSetOptionListInItem ( ip, TextNum );
#endif // LDS_FIX_SETITEM_OUTPUTOPTION_WHICH_LOCATED_INVENTORY

#ifdef SOCKET_SYSTEM
		TextNum = g_SocketItemMgr.AttachToolTipForSocketItem(ip, TextNum);
#endif	// SOCKET_SYSTEM

		SIZE TextSize = {0, 0};
		float fRateY	= g_fScreenRate_y;
		int	Height		= 0;
		int	EmptyLine	= 0;
		int TextLine	= 0;

		
#ifdef	LEM_FIX_ITEMTOOLTIP_POS	// ������ ���� ��ġ ���� [lem.2010.7.28]
		for(int i = 0; i < TextNum; ++i)
		{
			if(TextList[i][0] == '\0')		break;
			else if(TextList[i][0] == '\n')	++EmptyLine;
			else							++TextLine;
		}
		fRateY	= fRateY / 1.1f;
		g_pRenderText->SetFont(g_hFont);
#endif // LEM_FIX_ITEMTOOLTIP_POS
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		Height = (TextLine * TextSize.cy + EmptyLine * TextSize.cy / 2.0f) / fRateY;
		
#ifdef CSK_FIX_ITEMTOOLTIP_POS
		int iScreenHeight	= 420;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int nInvenHeight	= p->Height*INVENTORY_SCALE;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

		sy += INVENTORY_SCALE;
		if( sy + Height > iScreenHeight)
		{
			sy += iScreenHeight - ( sy + Height );

		}	
		else if(sy + Height > iScreenHeight)
		{
			
		}

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
	}	// if (!bItemTextListBoxUse) ��.
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
#else // CSK_FIX_ITEMTOOLTIP_POS
	if(sy-Height >= 0)
		sy -= Height;
	else
		sy += p->Height*INVENTORY_SCALE;
#endif // CSK_FIX_ITEMTOOLTIP_POS
	
	bool isrendertooltip = true;

#ifdef NEW_USER_INTERFACE_SHELL
	isrendertooltip = g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_PARTCHARGE_SHOP ) ? false : true;
#endif //NEW_USER_INTERFACE_SHELL

	if( isrendertooltip )
	{
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
		if (bItemTextListBoxUse)
			RenderTipTextList(sx, sy, TextNum, 0, RT3_SORT_CENTER, STRP_BOTTOMCENTER);
		else
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
			RenderTipTextList(sx,sy,TextNum,0);
	}
}

void RenderRepairInfo(int sx,int sy,ITEM *ip,bool Sell)
{
	// CSK��������
    //  ��� â�� ������ �ִ� �������� ���� ������ �����ش�.	
	//. item filtering

#ifdef LDK_FIX_USING_ISREPAIRBAN_FUNCTION
	// �ִ� �Լ��� Ȱ���սô�...
	if(IsRepairBan(ip) == true)
	{
		return;
	}
#else //LDK_FIX_USING_ISREPAIRBAN_FUNCTION
	if(g_ChangeRingMgr->CheckRepair(ip->Type) == true)
	{
		return;
	}
#ifdef CSK_PCROOM_ITEM
	if(ip->Type >= ITEM_POTION+55 && ip->Type <= ITEM_POTION+57)
	{
		return;
	}
#endif // CSK_PCROOM_ITEM

#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	if(ip->Type == ITEM_HELPER+96)		// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
	{
		return;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
	
	if( ( ip->Type >= ITEM_HELPER && ip->Type <= ITEM_HELPER+4 ) || ip->Type == ITEM_HELPER+10 )    return;
	if( ip->Type == ITEM_BOW+7 || ip->Type == ITEM_BOW+15 || ip->Type >= ITEM_POTION )              return;
	if( ip->Type >= ITEM_WING+7 && ip->Type <= ITEM_WING+19 )	return;		//. ���� ���͸�
	if( (ip->Type >= ITEM_HELPER+14 && ip->Type <= ITEM_HELPER+19) || ip->Type==ITEM_POTION+21 )    return;
	if( ip->Type == ITEM_HELPER+20)   return;
	if(ip->Type == ITEM_HELPER+29)   return;
    if ( ip->Type==ITEM_HELPER+4 || ip->Type==ITEM_HELPER+5 )  return;
#ifdef DARK_WOLF
    if ( ip->Type==ITEM_HELPER+6 )    return;
#endif// DARK_WOLF
#ifdef MYSTERY_BEAD
	if ( ip->Type==ITEM_WING+26 )	return;
#endif // MYSTERY_BEAD
	if(ip->Type==ITEM_HELPER+7)	return;
	if(ip->Type==ITEM_HELPER+11) return;
	if(ip->Type >= ITEM_HELPER+32 && ip->Type <= ITEM_HELPER+37) return;	//^ �渱 ������ ���� �Ұ���
	if(ip->Type == ITEM_HELPER+38)
		return;
#ifdef CSK_LUCKY_SEAL
	if( ip->Type == ITEM_HELPER+43 || ip->Type == ITEM_HELPER+44 || ip->Type == ITEM_HELPER+45 )
	{
		return;
	}
#endif //CSK_LUCKY_SEAL	
#ifdef CSK_FREE_TICKET
	// ������ ���� �ȵǰ� ���� ó��
	if(ip->Type >= ITEM_HELPER+46 && ip->Type <= ITEM_HELPER+48)
	{
		return;
	}
#endif // CSK_FREE_TICKET
	
#ifdef CSK_RARE_ITEM
	// ������ ���� �ȵǰ� ���� ó��
	if(ip->Type >= ITEM_POTION+58 && ip->Type <= ITEM_POTION+62)
	{
		return;
	}
#endif // CSK_RARE_ITEM

#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	// ��;�����Ƽ�� 7-12 ���� �ȵǰ� ���� ó��
	if(ip->Type >= ITEM_POTION+145 && ip->Type <= ITEM_POTION+150)
	{
		return;
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12

#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ������ ���� �ȵǰ� ���� ó��
	if(ip->Type >= ITEM_HELPER+125 && ip->Type <= ITEM_HELPER+127)
	{
		return;
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	
#ifdef CSK_LUCKY_CHARM
	if( ip->Type == ITEM_POTION+53 )// ����� ����
	{
		return;
	}
#endif //CSK_LUCKY_CHARM
	
#ifdef CSK_LUCKY_SEAL
	if( ip->Type == ITEM_HELPER+43 || ip->Type == ITEM_HELPER+44 || ip->Type == ITEM_HELPER+45 )
	{
		return;
	}
#endif //CSK_LUCKY_SEAL
	
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	if( ip->Type >= ITEM_POTION+70 && ip->Type <= ITEM_POTION+71 )
	{
		return;
	}
#endif //PSW_ELITE_ITEM
	
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	if( ip->Type >= ITEM_POTION+72 && ip->Type <= ITEM_POTION+77 )
	{
		return;
	}
#endif //PSW_SCROLL_ITEM
	
#ifdef PSW_SEAL_ITEM               // �̵� ����
	if( ip->Type == ITEM_HELPER+59 )
	{
		return;
	}
#endif //PSW_SEAL_ITEM
	
#ifdef PSW_FRUIT_ITEM              // ���� ����
	if( ip->Type >= ITEM_HELPER+54 && ip->Type <= ITEM_HELPER+58 )
	{
		return;
	}
#endif //PSW_FRUIT_ITEM
	
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	if( ip->Type >= ITEM_POTION+78 && ip->Type <= ITEM_POTION+82 )
	{
		return;
	}
#endif //PSW_SECRET_ITEM
	
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	if( ip->Type == ITEM_HELPER+60 )
	{
		return;
	}
#endif //PSW_INDULGENCE_ITEM
	
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	if( ip->Type == ITEM_HELPER+61 )
	{
		return;
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET

#ifdef PSW_ADD_PC4_SEALITEM
	if( ip->Type == ITEM_HELPER+62 ) {
		return;
	}
	if( ip->Type == ITEM_HELPER+63 ) {
		return;
	}
#endif //PSW_ADD_PC4_SEALITEM
	
#ifdef PSW_ADD_PC4_SCROLLITEM
	if( ip->Type == ITEM_POTION+97 ) {
		return;
	}
	if( ip->Type == ITEM_POTION+98 ) {
		return;
	}
#endif //PSW_ADD_PC4_SCROLLITEM

#ifdef YDG_ADD_HEALING_SCROLL
	if (ip->Type == ITEM_POTION+140)	// ġ���� ��ũ��
	{
		return;
	}
#endif	// YDG_ADD_HEALING_SCROLL

#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	if( ip->Type == ITEM_POTION+96 ) {
		return;
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
	if( ip->Type == ITEM_HELPER+64 || ip->Type == ITEM_HELPER+65 ) 
	{
		return;
	}
#endif //LDK_ADD_PC4_GUARDIAN	
#ifdef LDK_ADD_RUDOLPH_PET
	if( ip->Type == ITEM_HELPER+67 )
	{
		return;
	}
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
	if( ip->Type == ITEM_HELPER+80 )
	{
		return;
	}
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
	if( ip->Type == ITEM_HELPER+106 )
	{
		return;
	}
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
	if( ip->Type == ITEM_HELPER+123 )	// ���̷��� ��
	{
		return;
	}
#endif	// YDG_ADD_SKELETON_PET
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	if( ip->Type == ITEM_HELPER+69 )	// ��Ȱ�� ����
	{
		return;
	}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	if( ip->Type == ITEM_HELPER+70 )	// �̵��� ����
	{
		return;
	}
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef PBG_ADD_SANTAINVITATION
	if( ip->Type == ITEM_HELPER+66 )	return;	//��Ÿ������ �ʴ���
#endif //PBG_ADD_SANTAINVITATION
	if (ip->Type>=ITEM_HELPER+49 || ip->Type>=ITEM_HELPER+50 || ip->Type>=ITEM_HELPER+51)	// ���� �η縶�� �� ���� �Ұ���
	{
		return;
	}
#endif //LDK_FIX_USING_ISREPAIRBAN_FUNCTION

#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING             // ���� ���� 100% ���� ����
	if( ip->Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN 
		&& ip->Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END )
	{
		return;
	}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	if(ip->Type == ITEM_HELPER+107)		// ġ��������
	{
		return;
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	if(ip->Type == ITEM_HELPER+104)		// AG���� ����
	{
		return;
	}
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	if(ip->Type == ITEM_HELPER+105)		// SD���� ����
	{
		return;
	}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	if(ip->Type == ITEM_HELPER+103)		// ��Ƽ ����ġ ���� ������
	{
		return;
	}
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	if(ip->Type == ITEM_POTION+133)		// ����Ʈ SDȸ�� ����
	{
		return;
	}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	if(ip->Type == MODEL_HELPER+109)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
	if(ip->Type == MODEL_HELPER+110)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	if(ip->Type == MODEL_HELPER+111)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	if(ip->Type == MODEL_HELPER+112)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
	if(ip->Type == MODEL_HELPER+113)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
	if(ip->Type == MODEL_HELPER+114)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
	if(ip->Type == MODEL_HELPER+115)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
	if(ip->Type == MODEL_POTION+112)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
	if(ip->Type == MODEL_POTION+113)
	{
		return;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113

#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
	// �����ȭ
	if(ip->Type == ITEM_POTION+120)
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	if(ip->Type == ITEM_POTION+121)
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
	if(ip->Type == ITEM_POTION+122)
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
	if( ITEM_POTION+123 == ip->Type )
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
	if( ITEM_POTION+124 == ip->Type )
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
	if( ITEM_POTION+134 <= ip->Type && ip->Type <= ITEM_POTION+139)
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	if( ITEM_WING+130 <= ip->Type && 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		ip->Type <= ITEM_WING+135
#else //PBG_ADD_NEWCHAR_MONK_ITEM
		ip->Type <= ITEM_WING+134
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)
	{
		return;
	}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
	if( ITEM_POTION+114 <= ip->Type && ip->Type <= ITEM_POTION+119)
	{
		return;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
	if( ITEM_POTION+126 <= ip->Type && ip->Type <= ITEM_POTION+129)
	{
		return;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	if( ITEM_POTION+130 <= ip->Type && ip->Type <= ITEM_POTION+132)
	{
		return;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	if( ITEM_HELPER+121 == ip->Type )
	{
		return;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121

	ITEM_ATTRIBUTE *p = &ItemAttribute[ip->Type];
	TextNum = 0;
	SkipNum = 0;
	for(int i=0;i<30;i++)
	{
		TextList[i][0] = NULL;
	}

	int Level = (ip->Level>>3)&15;
	int Color;

    //  ������ ��.
	if(ip->Type==ITEM_POTION+13 || ip->Type==ITEM_POTION+14 || ip->Type==ITEM_WING+15)  //  �ູ�� ����, ��ȥ�� ����, ������ ����.
	{
		Color = TEXT_COLOR_YELLOW;
	}
	else if(COMGEM::isCompiledGem(ip))
	{
		Color = TEXT_COLOR_YELLOW;
	}
    //  ��õ���� ���빫��.
    else if ( ip->Type==ITEM_STAFF+10 || ip->Type==ITEM_SWORD+19 || ip->Type==ITEM_BOW+18 || ip->Type==ITEM_MACE+13)
    {
        Color = TEXT_COLOR_PURPLE;
    }
	else if(ip->Type==ITEM_POTION+17 || ip->Type==ITEM_POTION+18 || ip->Type==ITEM_POTION+19)	// ���������� ���� ������
	{
		Color = TEXT_COLOR_YELLOW;
	}
	else if(ip->SpecialNum > 0 && (ip->Option1&63) > 0)
	{
		Color = TEXT_COLOR_GREEN;
	}
	else if(Level >= 7)
	{
		Color = TEXT_COLOR_YELLOW;
	}
	else
	{
		if(ip->SpecialNum > 0)
		{
   			Color = TEXT_COLOR_BLUE;
		}
		else
		{
			Color = TEXT_COLOR_WHITE;
		}
	}

    if ( (  ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )    //  ������ ���� ~ ����� ����.
         || ip->Type>=ITEM_HELPER+30                            //  ������ ����.
		 || ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )// ��ǳ�� ���� ~ ������ ����
#ifdef ADD_ALICE_WINGS_1
		 || (ip->Type>=ITEM_WING+42 && ip->Type<=ITEM_WING+43)	// ��ȯ���� 2,3�� ����.
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		 || (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)	// �����������ͳ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
       )  
	{
	    if ( Level >= 7 )
	    {
		    Color = TEXT_COLOR_YELLOW;
	    }
	    else
	    {
		    if(ip->SpecialNum > 0)
		    {
   			    Color = TEXT_COLOR_BLUE;
		    }
		    else
		    {
			    Color = TEXT_COLOR_WHITE;
		    }
	    }
    }

	//  ���� ���.
	if ( ip->Type<ITEM_POTION)
    {
        int maxDurability;

	    sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

        //  �������� ���� ���.
	    char Text[100];

        //  �������� ����������. 
        //  ���߿��� �׳� ������� ó���Ѵ�.
        maxDurability = calcMaxDurability ( ip, p, Level );
        if(ip->Durability<maxDurability)
        {
            RepairEnable = 2;
			
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
			int iGold = ItemValue(ip,2);
			if( iGold == -1 )
				return;
            ConvertRepairGold(iGold, ip->Durability, maxDurability, ip->Type, Text);
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
            ConvertRepairGold(ItemValue(ip,2),ip->Durability, maxDurability, ip->Type, Text);
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
		    sprintf(TextList[TextNum],GlobalText[238],Text);

            TextListColor[TextNum] = Color;//TEXT_COLOR_RED;
        }
        else
        {
            RepairEnable = 1;

		    sprintf(TextList[TextNum],GlobalText[238], "0" );

            TextListColor[TextNum] = Color;//TEXT_COLOR_WHITE;
        }
	    TextBold[TextNum] = true;
	    TextNum++;

//        RepairEnable = 1;
    }
	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

    //  �������� �̸�.
    if(ip->Type == ITEM_WING+11)//��ȯ����
	{
		sprintf(TextList[TextNum],"%s %s",SkillAttribute[30+Level].Name,GlobalText[102]);
	}
    else if(ip->Type == ITEM_HELPER+10)//���Ź���
	{
		for(int i=0;i<MAX_MONSTER;i++)
		{
			if(SommonTable[Level] == MonsterScript[i].Type)
			{
        		sprintf(TextList[TextNum],"%s %s",MonsterScript[i].Name,GlobalText[103]);
				break;
			}
		}
	}
#ifdef KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
	// ��ũ��Ʈ �� ����ó��
	// ������ ������ ǥ������ �ʴ´�.
	else if( (ip->Type==ITEM_HELPER+4) || (ip->Type==ITEM_HELPER+5) )
	{
		sprintf(TextList[TextNum],"%s",p->Name);
	}
#endif // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
    else if ( ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )    //  ������ ���� ~ ����� ����.
             || ip->Type>=ITEM_HELPER+30                            //  ������ ����.
			 || ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )	// ��ǳ�� ���� ~ ������ ����
#ifdef ADD_ALICE_WINGS_1
		 || (ip->Type>=ITEM_WING+42 && ip->Type<=ITEM_WING+43)	// ��ȯ���� 2,3�� ����.
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)	// ������������ ����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
            )
    {
		if(Level==0)
			sprintf(TextList[TextNum],"%s",p->Name);
		else
			sprintf(TextList[TextNum],"%s +%d",p->Name,Level);
    }
	else
	{
		if((ip->Option1&63) > 0)
		{
			if(Level==0)
				sprintf(TextList[TextNum],"%s %s", GlobalText[620], p->Name);
			else
				sprintf(TextList[TextNum],"%s %s +%d", GlobalText[620], p->Name,Level);
		}
		else
		{
			if(Level==0)
				sprintf(TextList[TextNum],"%s",p->Name);
			else
				sprintf(TextList[TextNum],"%s +%d",p->Name,Level);
		}
	}
	TextListColor[TextNum] = Color;TextBold[TextNum] = true;TextNum++;
	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	if ( ip->Type<ITEM_POTION )
    {
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
		if( ip->bPeriodItem == false )
		{
			int maxDurability = calcMaxDurability ( ip, p, Level );
			
			sprintf(TextList[TextNum],GlobalText[71],ip->Durability, maxDurability);
			
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = false;
			TextNum++;
		}
#else // KJH_ADD_PERIOD_ITEM_SYSTEM
        int maxDurability = calcMaxDurability ( ip, p, Level );

        sprintf(TextList[TextNum],GlobalText[71],ip->Durability, maxDurability);

        TextListColor[TextNum] = TEXT_COLOR_WHITE;
		TextBold[TextNum] = false;
		TextNum++;
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
    }

	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	SIZE TextSize = {0, 0};

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	
	int Height = ((TextNum-SkipNum)*TextSize.cy+SkipNum*TextSize.cy/2)*480/WindowHeight;
	if(sy-Height >= 0)
		sy -= Height;
	else
		sy += p->Height*INVENTORY_SCALE;

	RenderTipTextList(sx,sy,TextNum,0);
}

//////////////////////////////////////////////////////////////////////////
//	���ݷ��� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////
bool GetAttackDamage ( int* iMinDamage, int* iMaxDamage )
{
	int AttackDamageMin;
	int AttackDamageMax;


	ITEM *r = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT];
	ITEM *l = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT];
	if ( PickItem.Number>0 && SrcInventory==Inventory )
	{	
		// �������� �� ���
		switch ( SrcInventoryIndex)
		{
		case EQUIPMENT_WEAPON_RIGHT:
			r = &PickItem;
			break;
		case EQUIPMENT_WEAPON_LEFT:
			l = &PickItem;
			break;
		}
	}
#ifdef ADD_SOCKET_ITEM
	if( GetEquipedBowType( ) == BOWTYPE_CROSSBOW )
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	if( (r->Type>=ITEM_BOW+8  && r->Type<ITEM_BOW+15)	||
		(r->Type>=ITEM_BOW+16 && r->Type<ITEM_BOW+17)	||
		(r->Type>=ITEM_BOW+18 && r->Type<ITEM_BOW+MAX_ITEM_INDEX)
	  )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	{
		AttackDamageMin = CharacterAttribute->AttackDamageMinRight;
		AttackDamageMax = CharacterAttribute->AttackDamageMaxRight;
	}
#ifdef ADD_SOCKET_ITEM
	else if( GetEquipedBowType( ) == BOWTYPE_BOW )
#else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	else if((l->Type>=ITEM_BOW && l->Type<ITEM_BOW+7) 
			|| l->Type==ITEM_BOW+17 
			|| l->Type==ITEM_BOW+20
			|| l->Type == ITEM_BOW+21
			|| l->Type == ITEM_BOW+22
		)
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	{
		AttackDamageMin = CharacterAttribute->AttackDamageMinLeft;
		AttackDamageMax = CharacterAttribute->AttackDamageMaxLeft;
	}
	else if(r->Type == -1)
	{
		AttackDamageMin = CharacterAttribute->AttackDamageMinLeft;
		AttackDamageMax = CharacterAttribute->AttackDamageMaxLeft;
	}
	else if(r->Type >= ITEM_STAFF && r->Type < ITEM_SHIELD)	//������ - ������ ��� ���� ������ ���� �����̷��� ����(AttackDamageMinLeft)�� ������ ����Ǿ�����
	{
		AttackDamageMin = CharacterAttribute->AttackDamageMinLeft;
		AttackDamageMax = CharacterAttribute->AttackDamageMaxLeft;
	}	
	else
	{
		AttackDamageMin = CharacterAttribute->AttackDamageMinRight;
		AttackDamageMax = CharacterAttribute->AttackDamageMaxRight;
	}

	bool Alpha = false;
	if ( GetBaseClass(Hero->Class)==CLASS_KNIGHT || GetBaseClass(Hero->Class)==CLASS_DARK )
	{
		if ( l->Type>=ITEM_SWORD && l->Type<ITEM_STAFF+MAX_ITEM_INDEX && r->Type>=ITEM_SWORD && r->Type<ITEM_STAFF+MAX_ITEM_INDEX )
		{
			Alpha = true;
			AttackDamageMin = ((CharacterAttribute->AttackDamageMinRight*55)/100+(CharacterAttribute->AttackDamageMinLeft*55)/100);
			AttackDamageMax = ((CharacterAttribute->AttackDamageMaxRight*55)/100+(CharacterAttribute->AttackDamageMaxLeft*55)/100);
		}
	}
    else if(GetBaseClass(Hero->Class) == CLASS_ELF )
    {
        if ( ( r->Type>=ITEM_BOW && r->Type<ITEM_BOW+MAX_ITEM_INDEX ) &&
             ( l->Type>=ITEM_BOW && l->Type<ITEM_BOW+MAX_ITEM_INDEX ) )
        {
            //  ARROW�� LEVEL�� 1�̻� �̸��� ���ݷ� ����. 
            if ( ( l->Type==ITEM_BOW+7 && ((l->Level>>3)&15)>=1 ) || ( r->Type==ITEM_BOW+15 && ((r->Level>>3)&15)>=1 ) )
            {
                Alpha = true;
            }
        }
    }
#ifdef PBG_ADD_NEWCHAR_MONK
	else if(GetBaseClass(Hero->Class) == CLASS_RAGEFIGHTER)
	{
		if(l->Type>=ITEM_SWORD && l->Type<ITEM_MACE+MAX_ITEM_INDEX && r->Type>=ITEM_SWORD && r->Type<ITEM_MACE+MAX_ITEM_INDEX)
		{
			Alpha = true;
			AttackDamageMin = ((CharacterAttribute->AttackDamageMinRight+CharacterAttribute->AttackDamageMinLeft)*60/100);
			AttackDamageMax = ((CharacterAttribute->AttackDamageMaxRight+CharacterAttribute->AttackDamageMaxLeft)*65/100);
		}
	}
#endif //PBG_ADD_NEWCHAR_MONK

	if ( CharacterAttribute->Ability&ABILITY_PLUS_DAMAGE )
	{
		AttackDamageMin += 15;
		AttackDamageMax += 15;
	}
	

	*iMinDamage = AttackDamageMin;
	*iMaxDamage = AttackDamageMax;

	return Alpha;
}



///////////////////////////////////////////////////////////////////////////////
// ��ų ����â �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderSkillInfo(int sx,int sy,int Type,int SkillNum, int iRenderPoint /*= STRP_NONE*/)
{
	char lpszName[256];
	int  iMinDamage, iMaxDamage;
    int  HeroClass = GetBaseClass ( Hero->Class );
	int  iMana, iDistance, iSkillMana;
    int  TextNum = 0;		// Text�ټ�
	int  SkipNum = 0;		// ��Text�ټ�

#ifdef PET_SYSTEM
    //  �� ��ɾ� ������ �Ѵ�.
    if ( giPetManager::RenderPetCmdInfo( sx, sy, Type ) ) return;
#endif// PET_SYSTEM

	int  AttackDamageMin, AttackDamageMax;
	int  iSkillMinDamage, iSkillMaxDamage;

    int  SkillType = CharacterAttribute->Skill[Type];
    CharacterMachine->GetMagicSkillDamage( CharacterAttribute->Skill[Type], &iMinDamage, &iMaxDamage);
	CharacterMachine->GetSkillDamage( CharacterAttribute->Skill[Type], &iSkillMinDamage, &iSkillMaxDamage );
	
    //	ĳ������ ���ݷ��� ���Ѵ�.
	GetAttackDamage ( &AttackDamageMin, &AttackDamageMax );	

    iSkillMinDamage += AttackDamageMin;
	iSkillMaxDamage += AttackDamageMax;
	GetSkillInformation( CharacterAttribute->Skill[Type], 1, lpszName, &iMana, &iDistance, &iSkillMana);
	
    if ( CharacterAttribute->Skill[Type]==AT_SKILL_STRONG_PIER && Hero->Weapon[0].Type!=-1 )
    {
        for ( int i=0; i<CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].SpecialNum; i++ )
        {
            if ( CharacterMachine->Equipment[0].Special[i]==AT_SKILL_LONG_SPEAR )    
            {
                wsprintf ( lpszName, "%s", GlobalText[1200] );
                break;
            }
        }
    }

	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
   	sprintf(TextList[TextNum],"%s",lpszName);
	TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = true;TextNum++;
	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	WORD Dexterity;		// ��ø
	WORD Energy;		// ������

	//^ �渱 ��ų ���ݷ�
	WORD Strength;		// ��
	WORD Vitality;		// ü��
    WORD Charisma;		// ���

	Dexterity= CharacterAttribute->Dexterity+ CharacterAttribute->AddDexterity;
	Energy	 = CharacterAttribute->Energy   + CharacterAttribute->AddEnergy;  

	//^ �渱 ��ų ���ݷ�
	Strength	=	CharacterAttribute->Strength+ CharacterAttribute->AddStrength;
	Vitality	=	CharacterAttribute->Vitality+ CharacterAttribute->AddVitality;
	Charisma	=	CharacterAttribute->Charisma+ CharacterAttribute->AddCharisma;

	int skillattackpowerRate = 0;

	StrengthenCapability rightinfo, leftinfo;

	ITEM* rightweapon = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT];
	ITEM* leftweapon  = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT];

	int rightlevel = (rightweapon->Level>>3)&15;

	if( rightlevel >= rightweapon->Jewel_Of_Harmony_OptionLevel )
	{
		g_pUIJewelHarmonyinfo->GetStrengthenCapability( &rightinfo, rightweapon, 1 );
	}

	int leftlevel = (leftweapon->Level>>3)&15;

	if( leftlevel >= leftweapon->Jewel_Of_Harmony_OptionLevel )
	{
		g_pUIJewelHarmonyinfo->GetStrengthenCapability( &leftinfo, leftweapon, 1 );
	}

	if( rightinfo.SI_isSP )
	{
		skillattackpowerRate += rightinfo.SI_SP.SI_skillattackpower;
		skillattackpowerRate += rightinfo.SI_SP.SI_magicalpower;	// ���� ��� (�����տ��� ������ �� �� �ִ�)
	}
	if( leftinfo.SI_isSP )
	{
		skillattackpowerRate += leftinfo.SI_SP.SI_skillattackpower;
	}

	if (HeroClass==CLASS_WIZARD || HeroClass==CLASS_SUMMONER)
	{
        if ( CharacterAttribute->Skill[Type]==AT_SKILL_WIZARDDEFENSE || (AT_SKILL_SOUL_UP <= CharacterAttribute->Skill[Type] && CharacterAttribute->Skill[Type] <= AT_SKILL_SOUL_UP+4))	// �ҿ�ٸ���
        {
#ifdef KJH_FIX_WOPS_K29544_SOULBARRIER_UPGRADE_TOOLTIP
			int iDamageShield;
			// �ҿ�ٸ����� ��������� ��ġ�� ������ �����ͽ�ų ������ ���� +5%�� �þ��.
			if( CharacterAttribute->Skill[Type]==AT_SKILL_WIZARDDEFENSE )
			{
				iDamageShield = (int)(10+(Dexterity/50.f)+(Energy/200.f));
			}
			else if((AT_SKILL_SOUL_UP <= CharacterAttribute->Skill[Type]) && (CharacterAttribute->Skill[Type] <= AT_SKILL_SOUL_UP+4))
			{
				iDamageShield = (int)(10+(Dexterity/50.f)+(Energy/200.f)) + ((CharacterAttribute->Skill[Type]-AT_SKILL_SOUL_UP+1)*5);		
			}
#else KJH_FIX_WOPS_K29544_SOULBARRIER_UPGRADE_TOOLTIP
            int iDamageShield = (int)(10+(Dexterity/50.f)+(Energy/200.f));
#endif // KJH_FIX_WOPS_K29544_SOULBARRIER_UPGRADE_TOOLTIP
            int iDeleteMana   = (int)(CharacterAttribute->ManaMax*0.02f);
            int iLimitTime    = (int)(60+(Energy/40.f));

		    sprintf(TextList[TextNum],GlobalText[578],iDamageShield);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;

		    sprintf(TextList[TextNum],GlobalText[880],iDeleteMana);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;

		    sprintf(TextList[TextNum],GlobalText[881],iLimitTime);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
        }
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
		// ����ó�� ( ���� : %d ~ %d )
		// �������� ��ų�� ������ �������� �ʴ´�.
		else if( SkillType != AT_SKILL_SWELL_OF_MAGICPOWER 
#ifdef KJW_FIX_SLEEPUP_SKILL_INFO
			// ���� ��ȭ�� ������ �������� �ʴ´�.
			&& SkillType != AT_SKILL_ALICE_SLEEP
			&& !(AT_SKILL_ALICE_SLEEP_UP <= SkillType && SkillType <= AT_SKILL_ALICE_SLEEP_UP + 4 )
#endif // KJW_FIX_SLEEPUP_SKILL_INFO
			)
#else // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
        else
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
        {
#ifdef KWAK_FIX_CHARACTER_SKILL_RUNTIME_ERR
			int iSkill = (int)CharacterAttribute->Skill[Type];
			if (!(AT_SKILL_STUN <= iSkill && iSkill <= AT_SKILL_MANA)
				&& !(AT_SKILL_ALICE_THORNS <= iSkill && iSkill <= AT_SKILL_ALICE_ENERVATION)
				&& iSkill != AT_SKILL_TELEPORT
				&& iSkill != AT_SKILL_TELEPORT_B)
			{
#ifdef ASG_ADD_SUMMON_RARGLE
				if (AT_SKILL_SUMMON_EXPLOSION <= iSkill && iSkill <= AT_SKILL_SUMMON_POLLUTION)
#else	// ASG_ADD_SUMMON_RARGLE
				if (AT_SKILL_SUMMON_EXPLOSION <= iSkill && iSkill <= AT_SKILL_SUMMON_REQUIEM)
#endif	// ASG_ADD_SUMMON_RARGLE
				{
					CharacterMachine->GetCurseSkillDamage(iSkill, &iMinDamage, &iMaxDamage);
					sprintf(TextList[TextNum], GlobalText[1692], iMinDamage, iMaxDamage);
				}
#else // KWAK_FIX_CHARACTER_SKILL_RUNTIME_ERR
			BYTE bySkill = CharacterAttribute->Skill[Type];
			if (!(AT_SKILL_STUN <= bySkill && bySkill <= AT_SKILL_MANA)
				&& !(AT_SKILL_ALICE_THORNS <= bySkill && bySkill <= AT_SKILL_ALICE_ENERVATION)
				&& bySkill != AT_SKILL_TELEPORT
				&& bySkill != AT_SKILL_TELEPORT_B)
			{
#ifdef ASG_ADD_SUMMON_RARGLE
				if (AT_SKILL_SUMMON_EXPLOSION <= bySkill && bySkill <= AT_SKILL_SUMMON_POLLUTION)
#else	// ASG_ADD_SUMMON_RARGLE
				if (AT_SKILL_SUMMON_EXPLOSION <= bySkill && bySkill <= AT_SKILL_SUMMON_REQUIEM)
#endif	// ASG_ADD_SUMMON_RARGLE
				{
					CharacterMachine->GetCurseSkillDamage(bySkill, &iMinDamage, &iMaxDamage);
					sprintf(TextList[TextNum], GlobalText[1692], iMinDamage, iMaxDamage);
				}
#endif // KWAK_FIX_CHARACTER_SKILL_RUNTIME_ERR
				else
					sprintf(TextList[TextNum],GlobalText[170],iMinDamage + skillattackpowerRate,iMaxDamage + skillattackpowerRate);
				TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
			}
        }
	}
    if ( HeroClass==CLASS_KNIGHT || HeroClass==CLASS_DARK || HeroClass==CLASS_ELF || HeroClass==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		|| HeroClass==CLASS_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		)
    {
        switch ( CharacterAttribute->Skill[Type] )
        {
        case AT_SKILL_TELEPORT :
        case AT_SKILL_TELEPORT_B :
		case AT_SKILL_SOUL_UP:
		case AT_SKILL_SOUL_UP+1:
		case AT_SKILL_SOUL_UP+2:
		case AT_SKILL_SOUL_UP+3:
		case AT_SKILL_SOUL_UP+4:

		case AT_SKILL_HEAL_UP:
		case AT_SKILL_HEAL_UP+1:
		case AT_SKILL_HEAL_UP+2:
		case AT_SKILL_HEAL_UP+3:
		case AT_SKILL_HEAL_UP+4:

		case AT_SKILL_LIFE_UP:
		case AT_SKILL_LIFE_UP+1:
		case AT_SKILL_LIFE_UP+2:
		case AT_SKILL_LIFE_UP+3:
		case AT_SKILL_LIFE_UP+4:

        case AT_SKILL_WIZARDDEFENSE :
        case AT_SKILL_BLOCKING :
        case AT_SKILL_VITALITY :
        case AT_SKILL_HEALING :
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
        case AT_SKILL_DEFENSE :
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
        case AT_SKILL_ATTACK :
        case AT_SKILL_SUMMON :      // ���.
        case AT_SKILL_SUMMON+1 :    // ������.
        case AT_SKILL_SUMMON+2 :    // �ϻ���.
        case AT_SKILL_SUMMON+3 :    // ���δ���.
        case AT_SKILL_SUMMON+4 :    // ��ũ����Ʈ.
        case AT_SKILL_SUMMON+5 :    // �߸�.
        case AT_SKILL_SUMMON+6 :    // ����.
#ifdef ADD_ELF_SUMMON
		case AT_SKILL_SUMMON+7:		// �����쳪��Ʈ
#endif // ADD_ELF_SUMMON
        case AT_SKILL_IMPROVE_AG:
        case AT_SKILL_STUN:			//  ��Ʋ������ ��ų.
        case AT_SKILL_REMOVAL_STUN:
        case AT_SKILL_MANA:
        case AT_SKILL_INVISIBLE:
		case AT_SKILL_REMOVAL_INVISIBLE:
        case AT_SKILL_REMOVAL_BUFF:
            break;
        case AT_SKILL_PARTY_TELEPORT:   //  ��Ƽ�� ��ȯ.
        case AT_SKILL_ADD_CRITICAL:     //  ũ��Ƽ�� ������ Ȯ�� ����.
            break;
		case AT_SKILL_ASHAKE_UP:
		case AT_SKILL_ASHAKE_UP+1:
		case AT_SKILL_ASHAKE_UP+2:
		case AT_SKILL_ASHAKE_UP+3:
		case AT_SKILL_ASHAKE_UP+4:
        case AT_SKILL_DARK_HORSE:   //  ��ũȣ��.
		    sprintf ( TextList[TextNum], GlobalText[1237] );
		    TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
            break;
        case AT_SKILL_BRAND_OF_SKILL:
            break;
		case AT_SKILL_PLASMA_STORM_FENRIR:	//^ �渱 ��ų ���ݷ�
#ifdef PBG_FIX_SKILL_RECOVER_TOOLTIP
		case AT_SKILL_RECOVER:				// ȸ����ų
#endif //PBG_FIX_SKILL_RECOVER_TOOLTIP
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		case AT_SKILL_ATT_UP_OURFORCES:
		case AT_SKILL_HP_UP_OURFORCES:
		case AT_SKILL_DEF_UP_OURFORCES:
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
			break;
        default :
		    sprintf(TextList[TextNum],GlobalText[879],iSkillMinDamage,iSkillMaxDamage + skillattackpowerRate);
		    TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
            break;
        }
	}

	//^ �渱 ��ų ���ݷ�
	if(CharacterAttribute->Skill[Type] == AT_SKILL_PLASMA_STORM_FENRIR)
	{
		int iSkillDamage;
		GetSkillInformation_Damage(AT_SKILL_PLASMA_STORM_FENRIR, &iSkillDamage);

		if(HeroClass == CLASS_KNIGHT || HeroClass == CLASS_DARK)	// ���, ����
		{
			iSkillMinDamage = (Strength/3)+(Dexterity/5)+(Vitality/5)+(Energy/7)+iSkillDamage;
		}
		else if(HeroClass == CLASS_WIZARD || HeroClass == CLASS_SUMMONER)	// ����, ��ȯ����
		{
			iSkillMinDamage = (Strength/5)+(Dexterity/5)+(Vitality/7)+(Energy/3)+iSkillDamage;
		}
		else if(HeroClass == CLASS_ELF)	// ����
		{
			iSkillMinDamage = (Strength/5)+(Dexterity/3)+(Vitality/7)+(Energy/5)+iSkillDamage;
		}
		else if(HeroClass == CLASS_DARK_LORD)	// ��ũ�ε�
		{
			iSkillMinDamage = (Strength/5)+(Dexterity/5)+(Vitality/7)+(Energy/3)+(Charisma/3)+iSkillDamage;
		}
#ifdef PBG_ADD_NEWCHAR_MONK
		else if(HeroClass == CLASS_RAGEFIGHTER)	//������������
		{
			iSkillMinDamage = (Strength/5)+(Dexterity/5)+(Vitality/3)+(Energy/7)+iSkillDamage;
		}
#endif //PBG_ADD_NEWCHAR_MONK
		iSkillMaxDamage = iSkillMinDamage + 30;
		
		sprintf(TextList[TextNum],GlobalText[879],iSkillMinDamage,iSkillMaxDamage + skillattackpowerRate);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}

    if(GetBaseClass(Hero->Class) == CLASS_ELF)
	{
		bool Success = true;
		switch(CharacterAttribute->Skill[Type])
		{
		case AT_SKILL_HEAL_UP:
		case AT_SKILL_HEAL_UP+1:
		case AT_SKILL_HEAL_UP+2:
		case AT_SKILL_HEAL_UP+3:
		case AT_SKILL_HEAL_UP+4:
		{
			int Cal = (Energy/5)+5;
			sprintf(TextList[TextNum],GlobalText[171],(Cal) + (int)((float)Cal*(float)(SkillAttribute[CharacterAttribute->Skill[Type]].Damage/(float)100)));
		}
		break;
	case AT_SKILL_HEALING:
		sprintf(TextList[TextNum],GlobalText[171],Energy/5+5);
		break;
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_DEF_POWER_UP:
	case AT_SKILL_DEF_POWER_UP+1:
	case AT_SKILL_DEF_POWER_UP+2:
	case AT_SKILL_DEF_POWER_UP+3:
	case AT_SKILL_DEF_POWER_UP+4:
		{
			int Cal = Energy/8+2;
#ifdef YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
			sprintf(TextList[TextNum],GlobalText[172],(Cal) + (int)((float)Cal/(float)((float)SkillAttribute[CharacterAttribute->Skill[Type]].Damage/(float)10)));
#else	// YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
			sprintf(TextList[TextNum],GlobalText[172],(int)((float)Cal/(float)((float)SkillAttribute[CharacterAttribute->Skill[Type]].Damage/(float)10)));
#endif	// YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
		}
		break;
#endif //PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_DEFENSE:sprintf(TextList[TextNum],GlobalText[172],Energy/8+2);break;
#ifdef PJH_SEASON4_MASTER_RANK4
	case AT_SKILL_ATT_POWER_UP:
	case AT_SKILL_ATT_POWER_UP+1:
	case AT_SKILL_ATT_POWER_UP+2:
	case AT_SKILL_ATT_POWER_UP+3:
	case AT_SKILL_ATT_POWER_UP+4:
		{
			int Cal = Energy/7+3;
#ifdef YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
			sprintf(TextList[TextNum],GlobalText[173],(Cal) + (int)((float)Cal/(float)((float)SkillAttribute[CharacterAttribute->Skill[Type]].Damage/(float)10)));
#else	// YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
			sprintf(TextList[TextNum],GlobalText[173],(int)((float)Cal/(float)((float)SkillAttribute[CharacterAttribute->Skill[Type]].Damage/(float)10)));
#endif	// YDG_FIX_MASTERLEVEL_ELF_ATTACK_TOOLTIP
		}
	break;
#endif //PJH_SEASON4_MASTER_RANK4
		case AT_SKILL_ATTACK :sprintf(TextList[TextNum],GlobalText[173],Energy/7+3);break;
#ifdef PBG_FIX_SKILL_RECOVER_TOOLTIP
		case AT_SKILL_RECOVER:
			{
				int Cal = Energy/4;
				sprintf(TextList[TextNum],GlobalText[1782], (int)((float)Cal+(float)CharacterAttribute->Level));
			}
		break;
#endif //PBG_FIX_SKILL_RECOVER_TOOLTIP
		default:Success = false;
		}
		if(Success)
		{
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
		}
	}

#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	// ����ó�� ( ��� ���� �Ÿ�: %d )
	// ����������ų�� ��밡�ɰŸ��� �������� �ʴ´�.
	if( SkillType != AT_SKILL_SWELL_OF_MAGICPOWER )
	{
		if(iDistance)
		{
			sprintf(TextList[TextNum],GlobalText[174],iDistance);
			TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;//SkipNum++;
		}
	}
#else // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	if(iDistance)
	{
		sprintf(TextList[TextNum],GlobalText[174],iDistance);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;//SkipNum++;
	}
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER

   	sprintf(TextList[TextNum],GlobalText[175],iMana);
	TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	if ( iSkillMana > 0)
	{
   		sprintf(TextList[TextNum],GlobalText[360],iSkillMana);
		TextListColor[TextNum] = TEXT_COLOR_WHITE;TextBold[TextNum] = false;TextNum++;
	}
    if ( GetBaseClass(Hero->Class) == CLASS_KNIGHT )
    {
        if ( CharacterAttribute->Skill[Type]==AT_SKILL_SPEAR )
        {
            sprintf(TextList[TextNum],GlobalText[96] );
		    TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
        }

		// �޺���ų�� �����߰� ������ 220�̻��̸�
		if ( Hero->byExtensionSkill == 1 && CharacterAttribute->Level >= 220 )
		{
			if ( ( CharacterAttribute->Skill[Type] >= AT_SKILL_SWORD1 && CharacterAttribute->Skill[Type] <= AT_SKILL_SWORD5 ) 
				|| CharacterAttribute->Skill[Type]==AT_SKILL_WHEEL || CharacterAttribute->Skill[Type]==AT_SKILL_FURY_STRIKE 
				|| CharacterAttribute->Skill[Type]==AT_SKILL_ONETOONE 
#ifdef PJH_SEASON4_MASTER_RANK4
				|| (AT_SKILL_ANGER_SWORD_UP <= CharacterAttribute->Skill[Type] && CharacterAttribute->Skill[Type] <= AT_SKILL_ANGER_SWORD_UP+4)
				|| (AT_SKILL_BLOW_UP <= CharacterAttribute->Skill[Type] && CharacterAttribute->Skill[Type] <= AT_SKILL_BLOW_UP+4)
#endif	//PJH_SEASON4_MASTER_RANK4
				|| (AT_SKILL_TORNADO_SWORDA_UP <= CharacterAttribute->Skill[Type] && CharacterAttribute->Skill[Type] <= AT_SKILL_TORNADO_SWORDA_UP+4)
				|| (AT_SKILL_TORNADO_SWORDB_UP <= CharacterAttribute->Skill[Type] && CharacterAttribute->Skill[Type] <= AT_SKILL_TORNADO_SWORDB_UP+4)
				   )
			{
				// 99 "�޺� ����"
				sprintf(TextList[TextNum], GlobalText[99] );
				TextListColor[TextNum] = TEXT_COLOR_DARKRED;
				TextBold[TextNum] = false;
				TextNum++;
			}
#ifdef CSK_FIX_SKILL_BLOWOFDESTRUCTION_COMBO
			else if(CharacterAttribute->Skill[Type] == AT_SKILL_BLOW_OF_DESTRUCTION)	// �ı��� �ϰ�
			{
				// 2115 "�޺� ����(2�ܰ踸)"
				sprintf(TextList[TextNum], GlobalText[2115] );
				TextListColor[TextNum] = TEXT_COLOR_DARKRED;
				TextBold[TextNum] = false;
				TextNum++;
			}
#endif // CSK_FIX_SKILL_BLOWOFDESTRUCTION_COMBO)
		}
    }

    BYTE MasteryType = CharacterMachine->GetSkillMasteryType( CharacterAttribute->Skill[Type] );
    if ( MasteryType!=255 )
    {
        sprintf ( TextList[TextNum], GlobalText[1080+MasteryType] );
		TextListColor[TextNum] = TEXT_COLOR_BLUE;TextBold[TextNum] = false;TextNum++;
    }

	
    int SkillUseType;
    int BrandType = SkillAttribute[SkillType].SkillBrand;
    SkillUseType = SkillAttribute[SkillType].SkillUseType;
    if ( SkillUseType==SKILL_USE_TYPE_BRAND )
    {
		// 1480 "%s�� ��ų�� ������"
		sprintf ( TextList[TextNum], GlobalText[1480], SkillAttribute[BrandType].Name );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
		// 1481 "%d�ʵ��� ��밡���մϴ�"
        sprintf ( TextList[TextNum], GlobalText[1481], SkillAttribute[BrandType].Damage );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
    }
    SkillUseType = SkillAttribute[SkillType].SkillUseType;
    if ( SkillUseType==SKILL_USE_TYPE_MASTER )
    {
        sprintf ( TextList[TextNum], GlobalText[1482] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
        sprintf ( TextList[TextNum], GlobalText[1483], SkillAttribute[SkillType].KillCount );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
    }

    if ( GetBaseClass(Hero->Class)==CLASS_DARK_LORD )
    {
        if ( CharacterAttribute->Skill[Type]==AT_SKILL_PARTY_TELEPORT && PartyNumber<=0 )
        {
		    sprintf ( TextList[TextNum], GlobalText[1185] );
		    TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
        }
	}

	if(CharacterAttribute->Skill[Type] == AT_SKILL_PLASMA_STORM_FENRIR)	//^ �渱 ��ų ����
	{
		sprintf ( TextList[TextNum], GlobalText[1926] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
		sprintf ( TextList[TextNum], GlobalText[1927] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;	
	}

	//�������� ������ �����
	if(CharacterAttribute->Skill[Type] == AT_SKILL_INFINITY_ARROW)
	{
		sprintf(TextList[1],lpszName);
		TextListColor[1] = TEXT_COLOR_BLUE;TextBold[1] = true;
		sprintf(TextList[2],"\n");
		sprintf(TextList[3],GlobalText[2040]);
		TextListColor[3] = TEXT_COLOR_DARKRED;TextBold[3] = false;
		sprintf(TextList[4],GlobalText[175],iMana);
		TextListColor[4] = TEXT_COLOR_WHITE;TextBold[4] = false;
		sprintf(TextList[5],GlobalText[360],iSkillMana);
		TextListColor[5] = TEXT_COLOR_WHITE;TextBold[5] = false;
		TextNum = 6; SkipNum = 2;
	}

	sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;

	if(CharacterAttribute->Skill[Type] == AT_SKILL_RUSH || CharacterAttribute->Skill[Type] == AT_SKILL_SPACE_SPLIT
		|| CharacterAttribute->Skill[Type] == AT_SKILL_DEEPIMPACT || CharacterAttribute->Skill[Type] == AT_SKILL_JAVELIN
		|| CharacterAttribute->Skill[Type] == AT_SKILL_ONEFLASH || CharacterAttribute->Skill[Type] == AT_SKILL_DEATH_CANNON
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		|| CharacterAttribute->Skill[Type] == AT_SKILL_OCCUPY
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
		)
	{
		sprintf ( TextList[TextNum], GlobalText[2047] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
	}
	if(CharacterAttribute->Skill[Type] == AT_SKILL_STUN || CharacterAttribute->Skill[Type] == AT_SKILL_REMOVAL_STUN
		|| CharacterAttribute->Skill[Type] == AT_SKILL_INVISIBLE || CharacterAttribute->Skill[Type] == AT_SKILL_REMOVAL_INVISIBLE
		|| CharacterAttribute->Skill[Type] == AT_SKILL_REMOVAL_BUFF)
	{
		sprintf ( TextList[TextNum], GlobalText[2048] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
	}
	if(CharacterAttribute->Skill[Type] == AT_SKILL_SPEAR)
	{
		sprintf ( TextList[TextNum], GlobalText[2049] );
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;TextBold[TextNum] = false;TextNum++;
	}

#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	if( SkillType == AT_SKILL_SWELL_OF_MAGICPOWER )
	{
		sprintf ( TextList[TextNum], GlobalText[2054] );		// 2054 : "�ּ� ���� 20%���"
		TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false; TextNum++;
	}
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER

	SIZE TextSize = {0, 0};	
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	
	if( iRenderPoint == STRP_NONE )
	{
		int Height = ((TextNum - SkipNum) * TextSize.cy + SkipNum * TextSize.cy / 2) / g_fScreenRate_y;
		sy -= Height;	
	}
	
	RenderTipTextList(sx,sy,TextNum,0, RT3_SORT_CENTER, iRenderPoint);
}

///////////////////////////////////////////////////////////////////////////////
// �ٴڿ� ������ ������ �̸� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderItemName(int i,OBJECT *o,int ItemLevel,int ItemOption,int ItemExtOption,bool Sort)
{
	char Name[80];

	int Level = (ItemLevel>>3)&15;
	
	g_pRenderText->SetFont(g_hFont);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 255);

#ifdef PBG_FIX_ITEMNAMEINDEX
	////////////////////////////////////////////////////////////////////////
	// ������ �̸� ������ �־ �޸� �̿��� ��ġ�� �о���̴� ���װ� ����
	// �����? �������� �����ϱⰡ �����, �ڵ� ��������
	// item�� name�� Ư�� ���� ���Ͽ��� �÷��� �����ϼ���	nColorType
	// ��Ʈ�� �޸��ϰ��� �Ұ��	nFontType �����ϼ���
	// ����Ʈ�� === �÷� 1.0f,1.0f,1.0f === ��Ʈ	g_hFont
	// Ư�� ���� �ƴҰ�� �������� ������^^;;
	////////////////////////////////////////////////////////////////////////		[10.09.07]
	int nColorType=0;
	int nFontType=0;
	int nGlobalTextIndex = 0;

	////////////////////////////////////////////////////////////////////////
	// Ư�� �÷�������ϴ� ������ �߰�
	////////////////////////////////////////////////////////////////////////
	if(o->Type==MODEL_POTION+15				//��
		|| (o->Type==MODEL_POTION+13) || (o->Type==MODEL_POTION+14) || (o->Type==MODEL_POTION+16)
		|| (o->Type==MODEL_WING+15) || (o->Type==MODEL_POTION+22) || (o->Type==MODEL_POTION+31)
		|| (o->Type==MODEL_HELPER+14) || (o->Type==MODEL_POTION+41) || (o->Type==MODEL_POTION+42)
		|| (o->Type==MODEL_POTION+43) || (o->Type==MODEL_POTION+44)
		|| (o->Type==MODEL_COMPILED_CELE) || (o->Type==MODEL_COMPILED_SOUL)
		|| (o->Type==MODEL_POTION+17 || o->Type==MODEL_POTION+18 || o->Type==MODEL_POTION+19)
		|| (o->Type == MODEL_POTION+11 && Level==7 )
		|| ( o->Type==MODEL_HELPER+15 ) || ( o->Type==MODEL_HELPER+31 ) || ( o->Type==MODEL_EVENT+16 )
		|| (o->Type == MODEL_EVENT+5) || (o->Type == MODEL_EVENT+6 && Level == 13)
#ifdef MYSTERY_BEAD
		|| ( o->Type == MODEL_EVENT+19 ) || ( o->Type == MODEL_EVENT+20 ) || (o->Type == MODEL_POTION+11 && Level==4)
		|| (o->Type == MODEL_POTION+11 && Level==5)
#endif //MYSTERY_BEAD
#ifdef CSK_PCROOM_ITEM
		|| (o->Type == MODEL_POTION+55) || (o->Type == MODEL_POTION+56) || (o->Type == MODEL_POTION+57)
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		|| (o->Type == MODEL_HELPER+96)		// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
#endif //LDS_ADD_PCROOM_ITEM_JPN_6TH
		|| (o->Type == ITEM_HELPER+49) || (o->Type == ITEM_HELPER+50) || (o->Type == ITEM_HELPER+51) || (o->Type == MODEL_POTION+64)
		|| (o->Type>=MODEL_EVENT+11 && o->Type<=MODEL_EVENT+15)
#ifdef CHINA_MOON_CAKE
		|| (o->Type==MODEL_EVENT+17)
#endif// CHINA_MOON_CAKE
		|| (o->Type==MODEL_POTION+21 && Level == 3)
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
		|| (o->Type == MODEL_POTION+100)
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef PBG_ADD_CHARACTERCARD
		|| (o->Type == MODEL_HELPER+97 || o->Type == MODEL_HELPER+98 || o->Type == MODEL_POTION+91)
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		|| (o->Type == MODEL_HELPER+99)
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
		|| (o->Type >= MODEL_HELPER+117 && o->Type <= MODEL_HELPER+120)// Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
#endif //PBG_ADD_SECRETITEM
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		|| (o->Type == MODEL_HELPER+109)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ű� ���(������)��		// MODEL_HELPER+110
		|| (o->Type == MODEL_HELPER+110)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		|| (o->Type == MODEL_HELPER+111)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
		|| (o->Type == MODEL_HELPER+112)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST	// �ű� �ڼ���(�����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
		|| (o->Type == MODEL_HELPER+113)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY	// �ű� ���(������) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
		|| (o->Type == MODEL_HELPER+114)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
		|| (o->Type == MODEL_HELPER+115)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE// �ű� �����̾�(���) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER		// �ű� Ű(�ǹ�)	// MODEL_POTION+112
		|| (o->Type == MODEL_POTION+112)
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER		// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD			// �ű� Ű(���)	// MODEL_POTION+113
		|| (o->Type == MODEL_POTION+113)
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
		|| ( MODEL_POTION+101 <= o->Type && o->Type <= MODEL_POTION+109 )
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
		|| (o->Type == MODEL_POTION+111)	// ������ ����
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
		|| (o->Type == MODEL_POTION+120)	// �����ȭ
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
		|| (o->Type == MODEL_POTION+121)
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
		|| (o->Type == MODEL_POTION+122)
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
		|| (o->Type == MODEL_POTION+123 )
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
		|| (o->Type == MODEL_POTION+124 )
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
		|| ( MODEL_POTION+134 <= o->Type && o->Type <= MODEL_POTION+139 )
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
		|| ( MODEL_POTION+114 <= o->Type && o->Type <= MODEL_POTION+119 )
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
		|| ( MODEL_POTION+126 <= o->Type && o->Type <= MODEL_POTION+129 )
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
		|| ( MODEL_POTION+130 <= o->Type && o->Type <= MODEL_POTION+132 )
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		|| ( MODEL_HELPER+121==o->Type )
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| (o->Type >= MODEL_POTION+157 && o->Type <= MODEL_POTION+159)
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| ( o->Type==MODEL_WING+25 ) || ( o->Type==MODEL_POTION+28 || o->Type==MODEL_POTION+29 )    //  ������ ǥ��.
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		|| ( COMGEM::Check_Jewel_Com(o->Type, true) != COMGEM::NOGEM )
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		)
	{
		nColorType = 1;			//	glColor3f(1.f,0.8f,0.1f);
	}
	else if(o->Type == MODEL_POTION+54
#ifdef CSK_FREE_TICKET
		|| o->Type==MODEL_HELPER+46 || o->Type==MODEL_HELPER+47 || o->Type==MODEL_HELPER+48 
#endif //CSK_FREE_TICKET
#ifdef CSK_RARE_ITEM
		|| (o->Type >= MODEL_POTION+58 && o->Type <= MODEL_POTION+62)	// ���� ������ ������ �̸�(�����δ� ���� �������� ����, �׽�Ʈ��)
#endif //CSK_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12	//��;�����Ƽ�� 7-12
		|| (o->Type >= MODEL_POTION+145 && o->Type <= MODEL_POTION+150)
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
		|| (o->Type == MODEL_HELPER+125 || o->Type == MODEL_HELPER+126 || o->Type == MODEL_HELPER+127)	//���ð��� ���������
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef CSK_LUCKY_CHARM
		|| ( o->Type == MODEL_POTION+53 )// ����� ����
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
		|| ( o->Type == MODEL_HELPER+43 || o->Type == MODEL_HELPER+44 || o->Type == MODEL_HELPER+45 )
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
		|| (o->Type >= ITEM_POTION+70 && o->Type <= ITEM_POTION+71)
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
		|| (o->Type >= ITEM_POTION+72 && o->Type <= ITEM_POTION+77)
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
		|| (o->Type == ITEM_HELPER+59)
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
		|| ( o->Type >= ITEM_HELPER+54 && o->Type <= ITEM_HELPER+58)
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
		|| (o->Type >= ITEM_POTION+78 && o->Type <= ITEM_POTION+82)
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
		|| (o->Type == ITEM_HELPER+60)
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
		|| (o->Type == ITEM_HELPER+61)
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
		|| (o->Type == MODEL_POTION+83)
#endif //PSW_RARE_ITEM
#ifdef CSK_LUCKY_SEAL
		|| ( o->Type == MODEL_HELPER+43 || o->Type == MODEL_HELPER+44 || o->Type == MODEL_HELPER+45 )
#endif //CSK_LUCKY_SEAL
#ifdef PSW_CHARACTER_CARD 
		|| (o->Type == MODEL_POTION+91) // ĳ���� ī��
#endif //PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
		|| (o->Type == MODEL_POTION+92 || o->Type == MODEL_POTION+93 || o->Type == MODEL_POTION+95) // ī����ī�� ���
#endif //PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
		|| (o->Type == ITEM_POTION+94) // ����Ʈ �߰� ġ�� ����
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
		|| ( o->Type>=MODEL_POTION+84 && o->Type<=MODEL_POTION+90)  // ���ɻ���
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
		|| ( o->Type == MODEL_HELPER+62 || o->Type == MODEL_HELPER+63)
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
		|| ( o->Type == MODEL_POTION+97 ) || ( o->Type == MODEL_POTION+98 )
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
		|| ( o->Type == MODEL_POTION+96 ) 
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
		|| ( o->Type == MODEL_HELPER+64 ) || ( o->Type == MODEL_HELPER+65 )
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDK_ADD_RUDOLPH_PET
		|| ( o->Type == MODEL_HELPER+67 )
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
		|| ( o->Type == MODEL_HELPER+80 )
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
		|| ( o->Type == MODEL_HELPER+106 )
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
		|| ( o->Type == MODEL_HELPER+123 )	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
		|| ( o->Type == MODEL_HELPER+68 )
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
		|| ( o->Type == MODEL_HELPER+76 )
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| ( o->Type == MODEL_HELPER+122 )	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM	// ��������, ��������, ����
		|| ( o->Type == MODEL_HELPER+128 ) || ( o->Type == MODEL_HELPER+129 ) || ( o->Type == MODEL_HELPER+134 )
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2	// ��ũ��, ��������, ����ũ��, ����������
		|| ( o->Type >= MODEL_HELPER+130 && o->Type <= MODEL_HELPER+133)
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
#ifdef HELLOWIN_EVENT
		|| (o->Type >= MODEL_POTION+45 && o->Type <= MODEL_POTION+50)//(�߷�Ÿ�ε��� �̺�Ʈ��)
#endif	//HELLOWIN_EVENT
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING // (����) ���� ���� 100% ���� ���� 
		|| (o->Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN && o->Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END)
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		|| ( o->Type == MODEL_HELPER+116 )
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		|| ( ITEM_WING+130 <= o->Type && 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		o->Type <= ITEM_WING+135
#else //PBG_ADD_NEWCHAR_MONK_ITEM
		o->Type <= ITEM_WING+134 
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PBG_ADD_GENSRANKING
		|| (o->Type>=MODEL_POTION+141 && o->Type<=MODEL_POTION+144)		// ������
#endif //PBG_ADD_GENSRANKING
		)
	{
		nColorType = 2;			//	glColor3f(0.9f,0.53f,0.13f);
	}
#ifdef LEM_FIX_RENDER_ITEMTOOLTIP_FIELD
	else if((o->Type == MODEL_WING+7 || o->Type == MODEL_WING+21 || o->Type == MODEL_WING+22 || o->Type == MODEL_WING+23))
	{
		nColorType = 3;			//	glColor3f(0.7f,0.7f,0.7f);
	}
#endif //LEM_FIX_RENDER_ITEMTOOLTIP_FIELD
	else if(o->Type == MODEL_WING+32
#ifdef GIFT_BOX_EVENT
		|| (o->Type == MODEL_POTION+33 && (Level == 0 || Level == 1)) || (o->Type == MODEL_EVENT+22)
#endif //GIFT_BOX_EVENT
		)
	{
		nColorType = 4;			//	glColor3f(1.f, 0.3f, 0.3f);
	}
	else if(o->Type == MODEL_WING+33)
	{
		nColorType = 5;			//	glColor3f(0.3f, 1.0f, 0.3f);
	}
	else if(o->Type == MODEL_WING+34
#ifdef GIFT_BOX_EVENT
		|| (o->Type == MODEL_POTION+34 && (Level == 0 || Level == 1)) || (o->Type == MODEL_EVENT+23)
#endif //GIFT_BOX_EVENT	
		)
	{
		nColorType = 6;			//	glColor3f(0.3f, 0.3f, 1.0f);
	}
	else if((o->Type == MODEL_POTION+32 && (Level == 0 || Level == 1)) || (o->Type == MODEL_EVENT+21))
	{
		nColorType = 7;			//	glColor3f(1.0f, 0.3f, 1.0f);
	}
	else if((g_SocketItemMgr.IsSocketItem(o))
#ifdef ADD_SEED_SPHERE_ITEM
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		|| (o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ�
		|| (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
		|| (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129)	// �õ彺�Ǿ�
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		|| ((o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ�
		|| (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
		|| (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129)	// �õ彺�Ǿ�
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#endif	// ADD_SEED_SPHERE_ITEM
		)
	{
		nColorType = 8;			//	glColor3f(0.7f,0.4f,1.0f);
	}
	else if( o->Type == MODEL_HELPER+66)
	{
		nColorType = 9;			//	glColor3f(0.6f, 0.4f, 1.0f);
	}
	else if(o->Type==MODEL_STAFF+10 || o->Type==MODEL_SWORD+19 || o->Type==MODEL_BOW+18 || o->Type==MODEL_MACE+13)
	{
		nColorType = 10;		//	glColor3f(1.f,0.1f,1.f);
	}
	else if((ItemOption&63) > 0 && ( o->Type<MODEL_WING+3 || o->Type>MODEL_WING+6 ) && o->Type!=MODEL_HELPER+30 
		&& ( o->Type<MODEL_WING+36 || o->Type>MODEL_WING+40 )
#ifdef ADD_ALICE_WINGS_1
		&& (o->Type<MODEL_WING+42 || o->Type>MODEL_WING+43)
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		&& !(o->Type>=MODEL_WING+49 && o->Type<=MODEL_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)  //  ������ ���� ~ ����� ����. ����. ��ȯ���� 2,3�� ����.
	{
		nColorType = 11;		//	glColor3f(0.1f,1.f,0.5f);
	}
	else
	{
		if(Level >= 7)
		{
			nColorType = 1;
		}
		else if(((ItemLevel>>7)&1) || ((ItemLevel>>2)&1) || ((ItemLevel>>1)&1) || (ItemLevel&1))
		{
			nColorType = 12;
		}
		else if(Level == 0)
		{
			nColorType = 3;
		}
		else if(Level < 3)
		{
			nColorType = 13;
		}
		else if(Level < 5)
		{
			nColorType = 14;
		}
		else if(Level < 7)
		{
			nColorType = 12;
		}
		else
		{
			nColorType = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////
	// Ư�� ��Ʈ������ϴ� ������ �߰�
	////////////////////////////////////////////////////////////////////////
	if((o->Type==MODEL_POTION+13) || (o->Type==MODEL_POTION+14) || (o->Type==MODEL_POTION+16)
		|| (o->Type==MODEL_WING+15) || (o->Type==MODEL_POTION+22) || (o->Type==MODEL_POTION+31)
		|| (o->Type==MODEL_HELPER+14) || (o->Type==MODEL_POTION+41) || (o->Type==MODEL_POTION+42)
		|| (o->Type==MODEL_POTION+43) || (o->Type==MODEL_POTION+44)
		|| (o->Type==MODEL_COMPILED_CELE) || (o->Type==MODEL_COMPILED_SOUL)
		|| (o->Type==MODEL_POTION+17 || o->Type==MODEL_POTION+18 || o->Type==MODEL_POTION+19)
		)
	{
		nFontType=1;				// g_hFontBold
	}

	switch(nColorType)
	{
	case 0:		glColor3f(1.f,1.0f,1.0f);		break;
	case 1:		glColor3f(1.f,0.8f,0.1f);		break;
	case 2:		glColor3f(0.9f,0.53f,0.13f);	break;
	case 3:		glColor3f(0.7f,0.7f,0.7f);		break;
	case 4:		glColor3f(1.0f,0.3f,0.3f);		break;
	case 5:		glColor3f(0.3f,1.0f,0.3f);		break;
	case 6:		glColor3f(0.3f,0.3f,1.0f);		break;
	case 7:		glColor3f(1.0f,0.3f,1.0f);		break;
	case 8:		glColor3f(0.7f,0.4f,1.0f);		break;
	case 9:		glColor3f(0.6f,0.4f,1.0f);		break;
	case 10:	glColor3f(1.0f,0.1f,1.0f);		break;
	case 11:	glColor3f(0.1f,1.0f,0.5f);		break;
	case 12:	glColor3f(0.4f,0.7f,1.0f);		break;
	case 13:	glColor3f(0.9f,0.9f,0.9f);		break;
	case 14:	glColor3f(1.0f,0.5f,0.2f);		break;
	default:	glColor3f(1.0f,1.0f,1.0f);		break;
	}

	if(nFontType==1)
	{
		g_pRenderText->SetFont(g_hFontBold);
	}

	////////////////////////////////////////////////////////////////////////
	// ������ �̸� ���� �������� �ε����� ����ؾ� ��
	////////////////////////////////////////////////////////////////////////
	if(o->Type==MODEL_POTION+17 || o->Type==MODEL_POTION+18 || o->Type==MODEL_POTION+19)
	{	
		if ( ((ItemLevel>>3)&15) == 0)
		{
			sprintf(Name,"%s",ItemAttribute[o->Type-MODEL_ITEM].Name);
		}
		else
		{
			sprintf(Name,"%s +%d",ItemAttribute[o->Type-MODEL_ITEM].Name,((ItemLevel>>3)&15));
		}
	}
	else if(o->Type == MODEL_POTION+11 && Level==7 )
	{
		sprintf (Name, GlobalText[111]); //  õ���� ����.
	}
#ifdef ANNIVERSARY_EVENT
	else if(o->Type == MODEL_POTION+11 && Level >= 1 && Level <= 5)
	{
		sprintf(Name,"%s +%d",GlobalText[116], Level);
	}
#endif	// ANNIVERSARY_EVENT
	else if(o->Type == MODEL_POTION+12)//�̹�Ʈ ������
	{
		switch(Level)
		{
		case 0:sprintf(Name,GlobalText[100]);break;
		case 1:sprintf(Name,GlobalText[101]);break;
		case 2:sprintf(Name,GlobalText[104]);break;
		}
	}
	else if ( o->Type==MODEL_HELPER+15 ) //     ��Ŭ.
	{
		switch ( Level )
		{
		case 0:sprintf(Name,"%s %s", GlobalText[168], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		case 1:sprintf(Name,"%s %s", GlobalText[169], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		case 2:sprintf(Name,"%s %s", GlobalText[167], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		case 3:sprintf(Name,"%s %s", GlobalText[166], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		case 4:sprintf(Name,"%s %s", GlobalText[1900], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		}
	}
	else if ( o->Type==MODEL_HELPER+31 )    //  ��ȥ.
	{
		switch ( Level )
		{
#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
	case 0:sprintf ( Name, "%s of %s", ItemAttribute[o->Type-MODEL_ITEM].Name, GlobalText[1187] ); break;
	case 1:sprintf ( Name, "%s of %s", ItemAttribute[o->Type-MODEL_ITEM].Name, GlobalText[1214] ); break;
#else // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
			// �ѱ�
	case 0:sprintf ( Name, "%s %s", GlobalText[1187], ItemAttribute[o->Type-MODEL_ITEM].Name ); break;
	case 1:sprintf ( Name, "%s %s", GlobalText[1214], ItemAttribute[o->Type-MODEL_ITEM].Name ); break;
#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
		}
	}
	else if ( o->Type==MODEL_EVENT+16 )     //  ������ �Ҹ�.
	{
		sprintf ( Name, GlobalText[1235] );
	}
	else if(o->Type == MODEL_EVENT+4)//��ź�Ǻ�
	{
		sprintf(Name,GlobalText[105]);
	}
	else if(o->Type == MODEL_EVENT+5)//����/���� �ָӴ�.
	{
#ifdef  NEW_YEAR_BAG_EVENT
		switch ( Level )
		{
		case 14: sprintf(Name,GlobalText[1650]); break;
		case 15: sprintf(Name,GlobalText[1651]); break;
		default: sprintf(Name,GlobalText[106]); break;
		}
#else // NEW_YEAR_BAG_EVENT
		sprintf(Name,GlobalText[106]);
#endif// NEW_YEAR_BAG_EVENT
	}
	else if(o->Type == MODEL_EVENT+6)//����� ��Ʈ
	{
		if (Level == 13)	//��ũ�ε��� ����
		{
			sprintf(Name,"%s",GlobalText[117]);
		}
		else
		{
			sprintf(Name,GlobalText[107]);
		}
	}
	else if(o->Type == MODEL_EVENT+7)//����� �ø���
	{
		sprintf(Name,GlobalText[108]);
	}
	else if(o->Type == MODEL_EVENT+8)//�� ����
	{
		sprintf(Name,GlobalText[109]);
	}
	else if(o->Type == MODEL_EVENT+9)//�� ����
	{
		sprintf(Name,GlobalText[110]);
	}
#ifdef USE_EVENT_ELDORADO
	else if(o->Type == MODEL_EVENT+10)//������
	{
		sprintf(Name,"%s +%d",GlobalText[115], Level - 7);
	}
#endif
#ifdef _PVP_ADD_MOVE_SCROLL
	else if (o->Type == MODEL_POTION+10 && Level >= 1 && Level <= 8)//  �̵�����
	{
		switch (Level)
		{
		case 1: sprintf ( Name, GlobalText[158], GlobalText[30] ); break;     //  �η��þ�
		case 2: sprintf ( Name, GlobalText[158], GlobalText[33] ); break;     //  �븮��
		case 3: sprintf ( Name, GlobalText[158], GlobalText[32] ); break;     //  ����ƽ�
		case 4: sprintf ( Name, GlobalText[158], GlobalText[31] ); break;     //  ����
		case 5: sprintf ( Name, GlobalText[158], GlobalText[37] ); break;     //  ��Ʋ����
		case 6: sprintf ( Name, GlobalText[158], GlobalText[34] ); break;     //  �ν�ƮŸ��
		case 7: sprintf ( Name, GlobalText[158], GlobalText[38] ); break;     //  Ÿ��ĭ
		case 8: sprintf ( Name, GlobalText[158], GlobalText[55] ); break;     //  ��ī�罺
		}
	}
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef MYSTERY_BEAD
	else if( o->Type == MODEL_EVENT+19 )
	{
		sprintf(Name, ItemAttribute[ITEM_WING+26].Name);
	}
	else if( o->Type == MODEL_EVENT+20 )
	{
		switch(Level)
		{
		case 1:		//. ��������
			strcpy( Name, GlobalText[1831]); break;
		case 2:		//. �Ķ�����
			strcpy( Name, GlobalText[1832]); break;
		case 3:		//. ��������
			strcpy( Name, GlobalText[1833]); break;
		}
	}
	else if(o->Type == MODEL_POTION+11 && Level==4)
	{
		strcpy(Name, GlobalText[1834]);
	}
	else if(o->Type == MODEL_POTION+11 && Level==5)
	{
		strcpy(Name, GlobalText[1838]);
	}
#endif // MYSTERY_BEAD
#ifdef GIFT_BOX_EVENT
	else if(o->Type == MODEL_POTION+32 && Level == 1)
	{
		sprintf(Name, GlobalText[2012]);	
	}
	else if(o->Type == MODEL_POTION+33 && Level == 1)
	{
		sprintf(Name, GlobalText[2013]);	
	}
	else if(o->Type == MODEL_POTION+34 && Level == 1)
	{
		sprintf(Name, GlobalText[2014]);	
	}
	else if(o->Type == MODEL_EVENT+21)
	{
		sprintf(Name, GlobalText[2012]);	
	}
	else if(o->Type == MODEL_EVENT+22)
	{
		sprintf(Name, GlobalText[2013]);	
	}
	else if(o->Type == MODEL_EVENT+23)
	{
		sprintf(Name, GlobalText[2014]);	
	}
#endif //GIFT_BOX_EVENT
	else if ( o->Type==MODEL_EVENT+11 )
	{
#ifdef FRIEND_EVENT
		if ( Level==2 ) //  ������ ��.
		{
			sprintf ( Name, GlobalText[1098] );  //  ������ ��/
		}
		else
#endif// FRIEND_EVENT
		{
			sprintf ( Name, GlobalText[810] );  //  ����.
		}
	}
	else if(o->Type==MODEL_EVENT+12)
	{
		sprintf ( Name, GlobalText[906] );	//. ������ ����
	}
	else if(o->Type==MODEL_EVENT+13)
	{
		sprintf ( Name, GlobalText[907] );	//. ��ũ����
	}
	else if(o->Type==MODEL_EVENT+14)
	{
		switch ( Level )
		{
		case 2:
			sprintf( Name, GlobalText[928] );	//. ������ ����
			break;
		case 3:
			sprintf( Name, GlobalText[929] );	//. ������ ����
			break;
		default :
			sprintf( Name, GlobalText[922] );	//. ������ ����
			break;
		}
	}
	else if(o->Type==MODEL_EVENT+15)
	{
		sprintf( Name, GlobalText[925] );	// �������� ����
	}
#ifdef CHINA_MOON_CAKE
	else if(o->Type==MODEL_EVENT+17)
	{
		sprintf( Name, GlobalText[118]);    //  �߱� ����.
	}
#endif// CHINA_MOON_CAKE
	else if(o->Type == MODEL_WING+11)//��ȯ����
	{
		sprintf(Name,"%s %s",SkillAttribute[30+Level].Name,GlobalText[102]);
	}
	else if(o->Type == MODEL_HELPER+10)//���Ź���
	{
		for(int i=0;i<MAX_MONSTER;i++)
		{
			if(SommonTable[Level] == MonsterScript[i].Type)
			{
				sprintf(Name,"%s %s",MonsterScript[i].Name,GlobalText[103]);
				break;
			}
		}
	}
	else if ( o->Type==MODEL_POTION+21 && Level == 3 )    //  ������ǥ��
	{
		sprintf( Name, GlobalText[1290] );
	}
	else if ( o->Type==MODEL_POTION+7 ) //  ���м� ����.//���ƹ���
	{
		switch ( Level )
		{
		case 0: sprintf( Name, GlobalText[1413] ); break;
		case 1: sprintf( Name, GlobalText[1414] ); break;
		}
	}
	else if ( o->Type==MODEL_HELPER+7 ) //  ��� ����
	{
		switch ( Level )
		{
		case 0: sprintf( Name, GlobalText[1460] ); break;  //  Ȱ �뺴.
		case 1: sprintf( Name, GlobalText[1461] ); break;  //  â �뺴.
		}
	}
	else if ( o->Type==MODEL_HELPER+11 )    //  �ֹ���.
	{
		switch ( Level )
		{
		case 0: sprintf( Name, GlobalText[1416] ); break;  //  ����� �ֹ���.
		case 1: sprintf( Name, GlobalText[1462] ); break;  //  ������ ���� ��ġ.
		}
	}
	else if ( o->Type==MODEL_EVENT+18 )
	{
		sprintf( Name, GlobalText[1462] );  //  ������ ���� ��ġ.
	}
	else
	{
		strcpy(Name, ItemAttribute[o->Type-MODEL_ITEM].Name);
	}

	char TextName[64]={0,};
	if ( g_csItemOption.GetSetItemName( TextName, o->Type-MODEL_ITEM, ItemExtOption ) )
	{
		glColor3f ( 1.f, 1.f, 1.f );
		g_pRenderText->SetFont(g_hFontBold);
		g_pRenderText->SetTextColor(0, 255, 0, 255);
		g_pRenderText->SetBgColor(60, 60, 200, 255);

		strcat ( TextName, ItemAttribute[o->Type-MODEL_ITEM].Name );
	}
	else
	{
		strcpy ( TextName, ItemAttribute[o->Type-MODEL_ITEM].Name );
	}

	if((ItemLevel>>7)&1)
	{
		if(o->Type!=MODEL_HELPER+3)
			strcat(Name,GlobalText[176]);
		else    //  ����Ʈ.
		{
			strcat(Name, " +" );
			strcat(Name,GlobalText[179]);
		}
	}
	//  �ɼ�.
	if( (ItemLevel&3) || ((ItemOption>>6)&1) )
		strcat(Name,GlobalText[177]);
	//  ���.
	if((ItemLevel>>2)&1)
		strcat(Name,GlobalText[178]);
#else //PBG_FIX_ITEMNAMEINDEX

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	bool bFirstOK = true;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

	if(o->Type==MODEL_POTION+15)//��
	{
		glColor3f(1.f,0.8f,0.1f);
       	sprintf(Name,"%s %d",ItemAttribute[o->Type-MODEL_ITEM].Name,ItemLevel);
	}
	else if( (o->Type==MODEL_POTION+13) 
		  || (o->Type==MODEL_POTION+14)
		  || (o->Type==MODEL_POTION+16)
		  || (o->Type==MODEL_WING+15)
		  || (o->Type==MODEL_POTION+22)
		  || (o->Type==MODEL_POTION+31)
		  || (o->Type==MODEL_HELPER+14)
		  || (o->Type==MODEL_POTION+41)
		  || (o->Type==MODEL_POTION+42)
		  || (o->Type==MODEL_POTION+43)
		  || (o->Type==MODEL_POTION+44)
		   ) //  ��ũ�� ����.
	{
		g_pRenderText->SetFont(g_hFontBold);
		glColor3f(1.f,0.8f,0.1f);
       	sprintf(Name,"%s",ItemAttribute[o->Type-MODEL_ITEM].Name);
	}
#ifdef KJW_FIX_ITEMNAME_ORB_OF_SUMMONING
	else if( o->Type == MODEL_WING+11)//��ȯ����
	{
		glColor3f(0.7f,0.7f,0.7f);
		sprintf( Name,"%s %s", SkillAttribute[ 30 + Level ].Name, GlobalText[102] );
	}
#endif // KJW_FIX_ITEMNAME_ORB_OF_SUMMONING
#ifdef LEM_FIX_RENDER_ITEMTOOLTIP_FIELD
	else if(o->Type == MODEL_WING+7)	
	{
		glColor3f(0.7f,0.7f,0.7f);
		sprintf(Name, ItemAttribute[ITEM_WING+7].Name);	
	}
	else if(o->Type == MODEL_WING+21)	
	{
		glColor3f(0.7f,0.7f,0.7f);
		sprintf(Name, ItemAttribute[ITEM_WING+21].Name);	
	}
	else if(o->Type == MODEL_WING+22)	
	{
		glColor3f(0.7f,0.7f,0.7f);
		sprintf(Name, ItemAttribute[ITEM_WING+22].Name);	
	}
	else if(o->Type == MODEL_WING+23)	
	{
		glColor3f(0.7f,0.7f,0.7f);
		sprintf(Name, ItemAttribute[ITEM_WING+23].Name);	
	}
#endif	// LEM_FIX_RENDER_ITEMTOOLTIP_FIELD [lem_2010.8.18]
#ifdef CSK_FREE_TICKET
	// ���� ������ ������ �̸�(�����δ� ���� �������� ����, �׽�Ʈ��)
	else if(o->Type == MODEL_HELPER+46)	// ���������� ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+46].Name);	
	}
	else if(o->Type == MODEL_HELPER+47)	// ����ĳ�� ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+47].Name);
	}
	else if(o->Type == MODEL_HELPER+48)	// Į���� ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+48].Name);
	}
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
	// ���� ������ ������ �̸�(�����δ� ���� �������� ����, �׽�Ʈ��)
	else if(o->Type == MODEL_POTION+54)	// ī����ī��
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+54].Name);
	}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
	// ���� ������ ������ �̸�(�����δ� ���� �������� ����, �׽�Ʈ��)
	else if(o->Type >= MODEL_POTION+58 && o->Type <= MODEL_POTION+62)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif // CSK_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12	//��;�����Ƽ�� 7-12
	else if(o->Type >= MODEL_POTION+145 && o->Type <= MODEL_POTION+150)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	else if(o->Type == MODEL_HELPER+125)	//���ð��� ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+125].Name);	
	}
	else if(o->Type == MODEL_HELPER+126)	//�ٸ�ī ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+126].Name);
	}
	else if(o->Type == MODEL_HELPER+127)	//�ٸ�ī ��7�� ���������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+127].Name);
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef CSK_LUCKY_CHARM
	else if( o->Type == MODEL_POTION+53 )// ����� ����
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+53].Name);
	}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
	else if( o->Type == MODEL_HELPER+43 || o->Type == MODEL_HELPER+44 || o->Type == MODEL_HELPER+45 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_HELPER].Name);
	}
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	else if(o->Type >= ITEM_POTION+70 && o->Type <= ITEM_POTION+71)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	else if(o->Type >= ITEM_POTION+72 && o->Type <= ITEM_POTION+77)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
	else if(o->Type == ITEM_HELPER+59)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
	else if( o->Type >= ITEM_HELPER+54 && o->Type <= ITEM_HELPER+58)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	else if(o->Type >= ITEM_POTION+78 && o->Type <= ITEM_POTION+82)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	else if(o->Type == ITEM_HELPER+60)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	else if(o->Type == ITEM_HELPER+61)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
	else if(o->Type == MODEL_POTION+83)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //PSW_RARE_ITEM
#ifdef CSK_LUCKY_SEAL
	else if( o->Type == MODEL_HELPER+43 || o->Type == MODEL_HELPER+44 || o->Type == MODEL_HELPER+45 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_HELPER].Name);
	}
#endif //CSK_LUCKY_SEAL
#ifdef PSW_CHARACTER_CARD 
	else if(o->Type == MODEL_POTION+91) // ĳ���� ī��
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+91].Name);
	}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
	else if(o->Type == MODEL_POTION+92) // ī����ī�� ���
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+92].Name);
	}
	else if(o->Type == MODEL_POTION+93) // ī����ī�� ����
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+93].Name);
	}
	else if(o->Type == MODEL_POTION+95) // ī����ī�� �̴�
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+95].Name);
	}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
#ifdef KJW_FIX_ITEMNAME_CRITICAL_SCROLL
	else if( o->Type == MODEL_POTION + 94 ) // ����Ʈ �߰� ġ�� ����
#else // KJW_FIX_ITEMNAME_CRITICAL_SCROLL
	else if(o->Type == ITEM_POTION+94) // ����Ʈ �߰� ġ�� ����
#endif // KJW_FIX_ITEMNAME_CRITICAL_SCROLL
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+94].Name);
	}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
	else if( o->Type==MODEL_POTION+84 )  // ���ɻ���
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+84].Name);
	}
	else if( o->Type==MODEL_POTION+85 )  // ���ɼ�
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+85].Name);
	}
	else if( o->Type==MODEL_POTION+86 )  // ���ɰ��
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+86].Name);
	}
	else if( o->Type==MODEL_POTION+87 )  // ������
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+87].Name);
	}
	else if( o->Type==MODEL_POTION+88 )  // ��� ����
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+88].Name);
	}
	else if( o->Type==MODEL_POTION+89 )  // ������ ����
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+89].Name);
	}
	else if( o->Type==MODEL_POTION+90 )  // ����� ����
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+90].Name);
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
	else if( o->Type == MODEL_HELPER+62 ) {
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+62].Name);
	}
	else if( o->Type == MODEL_HELPER+63 ) {
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+63].Name);
	}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
	else if( o->Type == MODEL_POTION+97 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+97].Name);
	}
	else if( o->Type == MODEL_POTION+98 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+98].Name);
	}
#endif //PSW_ADD_PC4_SCROLLITEM

#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	else if( o->Type == MODEL_POTION+96 ) 
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+96].Name);
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
	else if( o->Type == MODEL_HELPER+64 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+64].Name);
	}
	else if( o->Type == MODEL_HELPER+65 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+65].Name);
	}
#endif //LDK_ADD_PC4_GUARDIAN

#ifdef LDK_ADD_RUDOLPH_PET
	else if( o->Type == MODEL_HELPER+67 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+67].Name);
	}
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
	else if( o->Type == MODEL_HELPER+80 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+80].Name);
	}
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
	else if( o->Type == MODEL_HELPER+106 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+106].Name);
	}
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
	else if( o->Type == MODEL_HELPER+123 )	// ���̷��� ��
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+123].Name);
	}
#endif	// YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	else if( o->Type == MODEL_HELPER+68 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+68].Name);
	}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
	else if( o->Type == MODEL_HELPER+76 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+76].Name);
	}
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	else if( o->Type == MODEL_HELPER+122 )	// ���̷��� ���Ź���
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+122].Name);
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM	// ��������, ��������, ����

	else if( o->Type == MODEL_HELPER+128 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+128].Name);
	}
	else if( o->Type == MODEL_HELPER+129 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+129].Name);
	}
	else if( o->Type == MODEL_HELPER+134 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+134].Name);
	}
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2	// ��ũ��, ��������, ����ũ��, ����������
	else if( o->Type == MODEL_HELPER+130 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+130].Name);
	}
	else if( o->Type == MODEL_HELPER+131 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+131].Name);
	}
	else if( o->Type == MODEL_HELPER+132 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+132].Name);
	}
	else if( o->Type == MODEL_HELPER+133 )
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+133].Name);
	}
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if ( COMGEM::NOGEM != COMGEM::Check_Jewel_Com(o->Type, true) )
	{
		int iJewelItemIndex = COMGEM::GetJewelIndex(COMGEM::Check_Jewel_Com(o->Type, true), COMGEM::eGEM_NAME);
		g_pRenderText->SetFont(g_hFontBold);
		glColor3f(1.f,0.8f,0.1f);
		sprintf(Name,"%s",GlobalText[iJewelItemIndex]);
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if(o->Type==MODEL_COMPILED_CELE)
	{
		g_pRenderText->SetFont(g_hFontBold);
		glColor3f(1.f,0.8f,0.1f);
		sprintf(Name,"%s",ItemAttribute[MODEL_POTION+13-MODEL_ITEM].Name);
	}
	else if(o->Type==MODEL_COMPILED_SOUL)
	{
		g_pRenderText->SetFont(g_hFontBold);
		glColor3f(1.f,0.8f,0.1f);
		sprintf(Name,"%s",ItemAttribute[MODEL_POTION+14-MODEL_ITEM].Name);		
	}
	else if(o->Type==MODEL_POTION+17 || o->Type==MODEL_POTION+18 || o->Type==MODEL_POTION+19)
	{	
		// �Ǹ��� ��, �Ǹ��� ����, ���������� �ʴ��
		g_pRenderText->SetFont(g_hFontBold);
		glColor3f(1.f,0.8f,0.1f);
		if ( ((ItemLevel>>3)&15) == 0)
		{
			sprintf(Name,"%s",ItemAttribute[o->Type-MODEL_ITEM].Name);
		}
		else
		{
       		sprintf(Name,"%s +%d",ItemAttribute[o->Type-MODEL_ITEM].Name,((ItemLevel>>3)&15));
		}
	}
    else if(o->Type == MODEL_POTION+11 && Level==7 )
    {
		glColor3f(1.f,0.8f,0.1f);
        sprintf (Name, GlobalText[111]); //  õ���� ����.
    }
#ifdef ANNIVERSARY_EVENT
    else if(o->Type == MODEL_POTION+11 && Level >= 1 && Level <= 5)
    {
		sprintf(Name,"%s +%d",GlobalText[116], Level);
    }
#endif	// ANNIVERSARY_EVENT
	else if(o->Type == MODEL_POTION+12)//�̹�Ʈ ������
	{
		switch(Level)
		{
		case 0:sprintf(Name,GlobalText[100]);break;
		case 1:sprintf(Name,GlobalText[101]);break;
		case 2:sprintf(Name,GlobalText[104]);break;
		}
	}
    else if ( o->Type==MODEL_HELPER+15 ) //     ��Ŭ.
    {
		glColor3f(1.f,0.8f,0.1f);
        switch ( Level )
        {
        case 0:sprintf(Name,"%s %s", GlobalText[168], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
        case 1:sprintf(Name,"%s %s", GlobalText[169], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
        case 2:sprintf(Name,"%s %s", GlobalText[167], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
        case 3:sprintf(Name,"%s %s", GlobalText[166], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
		case 4:sprintf(Name,"%s %s", GlobalText[1900], ItemAttribute[o->Type-MODEL_ITEM].Name );break;
        }
    }
    else if ( o->Type==MODEL_HELPER+31 )    //  ��ȥ.
    {
		glColor3f(1.f,0.8f,0.1f);
        switch ( Level )
        {
#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
		case 0:sprintf ( Name, "%s of %s", ItemAttribute[o->Type-MODEL_ITEM].Name, GlobalText[1187] ); break;
        case 1:sprintf ( Name, "%s of %s", ItemAttribute[o->Type-MODEL_ITEM].Name, GlobalText[1214] ); break;
#else // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
		// �ѱ�
        case 0:sprintf ( Name, "%s %s", GlobalText[1187], ItemAttribute[o->Type-MODEL_ITEM].Name ); break;
        case 1:sprintf ( Name, "%s %s", GlobalText[1214], ItemAttribute[o->Type-MODEL_ITEM].Name ); break;
#endif // SELECTED_LANGUAGE == LANGUAGE_ENGLISH || SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
        }
    }
	else if ( o->Type==MODEL_EVENT+16 )     //  ������ �Ҹ�.
	{
		glColor3f(1.f,0.8f,0.1f);
		sprintf ( Name, GlobalText[1235] );
	}
	else if(o->Type == MODEL_EVENT+4)//��ź�Ǻ�
	{
		sprintf(Name,GlobalText[105]);
	}
	else if(o->Type == MODEL_EVENT+5)//����/���� �ָӴ�.
	{
    	glColor3f(1.f,0.8f,0.1f);
#ifdef  NEW_YEAR_BAG_EVENT
        switch ( Level )
        {
        case 14:
	    	sprintf(Name,GlobalText[1650]);
            break;

        case 15:
	    	sprintf(Name,GlobalText[1651]);
            break;

        default:
		    sprintf(Name,GlobalText[106]);
            break;
        }
#else // NEW_YEAR_BAG_EVENT
		sprintf(Name,GlobalText[106]);
#endif// NEW_YEAR_BAG_EVENT
	}
	else if(o->Type == MODEL_EVENT+6)//����� ��Ʈ
	{
		if (Level == 13)	//��ũ�ε��� ����
		{
			glColor3f ( 1.f, 0.8f, 0.1f );
			sprintf(Name,"%s",GlobalText[117]);
		}
		else
		{
			sprintf(Name,GlobalText[107]);
		}
	}
	else if(o->Type == MODEL_EVENT+7)//����� �ø���
	{
		sprintf(Name,GlobalText[108]);
	}
	else if(o->Type == MODEL_EVENT+8)//�� ����
	{
		sprintf(Name,GlobalText[109]);
	}
	else if(o->Type == MODEL_EVENT+9)//�� ����
	{
		sprintf(Name,GlobalText[110]);
	}
#ifdef USE_EVENT_ELDORADO
	else if(o->Type == MODEL_EVENT+10)//������
	{
		sprintf(Name,"%s +%d",GlobalText[115], Level - 7);
	}
#endif
#ifdef _PVP_ADD_MOVE_SCROLL
    else if (o->Type == MODEL_POTION+10 && Level >= 1 && Level <= 8)//  �̵�����
    {
		glColor3f ( 1.f, 1.f, 1.f );
        switch (Level)
        {
        case 1: sprintf ( Name, GlobalText[158], GlobalText[30] ); break;     //  �η��þ�
		case 2: sprintf ( Name, GlobalText[158], GlobalText[33] ); break;     //  �븮��
		case 3: sprintf ( Name, GlobalText[158], GlobalText[32] ); break;     //  ����ƽ�
		case 4: sprintf ( Name, GlobalText[158], GlobalText[31] ); break;     //  ����
		case 5: sprintf ( Name, GlobalText[158], GlobalText[37] ); break;     //  ��Ʋ����
		case 6: sprintf ( Name, GlobalText[158], GlobalText[34] ); break;     //  �ν�ƮŸ��
		case 7: sprintf ( Name, GlobalText[158], GlobalText[38] ); break;     //  Ÿ��ĭ
		case 8: sprintf ( Name, GlobalText[158], GlobalText[55] ); break;     //  ��ī�罺
        }
    }
#endif	// _PVP_ADD_MOVE_SCROLL
#ifdef _PVP_MURDERER_HERO_ITEM
    else if ( o->Type==MODEL_POTION+30 )//  �������θ�¡ǥ(wld)
    {
		glColor3f ( 1.f, 1.f, 1.f );
		sprintf(Name, ItemAttribute[o->Type-MODEL_ITEM].Name);
    }
#endif	// _PVP_MURDERER_HERO_ITEM
#ifdef MYSTERY_BEAD
	else if( o->Type == MODEL_EVENT+19 )
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_WING+26].Name);
	}
	else if( o->Type == MODEL_EVENT+20 )
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		switch(Level)
		{
		case 1:		//. ��������
			strcpy( Name, GlobalText[1831]); break;
		case 2:		//. �Ķ�����
			strcpy( Name, GlobalText[1832]); break;
		case 3:		//. ��������
			strcpy( Name, GlobalText[1833]); break;
		}
	}
	else if(o->Type == MODEL_POTION+11 && Level==4)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		strcpy(Name, GlobalText[1834]);
	}
	else if(o->Type == MODEL_POTION+11 && Level==5)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		strcpy(Name, GlobalText[1838]);
	}
#endif // MYSTERY_BEAD
	else if(o->Type == MODEL_WING+32)//������������.(x-mas�̺�Ʈ��)
	{
		glColor3f ( 1.f, 0.3f, 0.3f );
		sprintf(Name, ItemAttribute[ITEM_WING+32].Name);	
	}
	else if(o->Type == MODEL_WING+33)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		glColor3f ( 0.3f, 1.0f, 0.3f );
		sprintf(Name, ItemAttribute[ITEM_WING+33].Name);	
	}
	else if(o->Type == MODEL_WING+34)//�ʷϸ�������.(x-mas�̺�Ʈ��)
	{
		glColor3f ( 0.3f, 0.3f, 1.f );
		sprintf(Name, ItemAttribute[ITEM_WING+34].Name);	
	}
#ifdef CSK_PCROOM_ITEM
	else if(o->Type == MODEL_POTION+55)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_POTION+55].Name);
	}
	else if(o->Type == MODEL_POTION+56)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_POTION+56].Name);
	}
	else if(o->Type == MODEL_POTION+57)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_POTION+57].Name);
	}
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	else if(o->Type == MODEL_HELPER+96)		// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_POTION+57].Name);
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
	else if(o->Type == ITEM_HELPER+49)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+49].Name);
	}
	else if(o->Type == ITEM_HELPER+50)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+50].Name);
	}
	else if(o->Type == ITEM_HELPER+51)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_HELPER+51].Name);
	}
	else if(o->Type == MODEL_POTION+64)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf(Name, ItemAttribute[ITEM_POTION+64].Name);
	}
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	else if(o->Type == MODEL_WING+48)//
	{
		//Ȥ��?
		glColor3f ( 1.f, 1.f, 1.f );
		sprintf(Name, ItemAttribute[ITEM_WING+48].Name);	
	}
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	else if(o->Type == MODEL_WING+35)//
	{
		//Ȥ��?
		glColor3f ( 1.f, 1.f, 1.f );
		sprintf(Name, ItemAttribute[ITEM_WING+35].Name);	
	}
#ifdef HELLOWIN_EVENT
	else if(o->Type == MODEL_POTION+45)//��ȫ ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+45].Name);	
	}
	else if(o->Type == MODEL_POTION+46)//���� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+46].Name);	
	}
	else if(o->Type == MODEL_POTION+47)//�Ķ� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+47].Name);	
	}
	else if(o->Type == MODEL_POTION+48)//��ȫ ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+48].Name);		
	}
	else if(o->Type == MODEL_POTION+49)//���� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+49].Name);	
	}
	else if(o->Type == MODEL_POTION+50)//�Ķ� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[ITEM_POTION+50].Name);		
	}
#endif	//HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	else if(o->Type == MODEL_POTION+32)//��ȫ ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int i = MODEL_POTION+32;
		int k = ITEM_POTION+32;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		if(Level == 0)
		{
			glColor3f ( 1.f, 0.3f, 1.f );
			sprintf(Name, ItemAttribute[ITEM_POTION+32].Name);	
		}
		else
		if(Level == 1)
		{
			glColor3f ( 1.f, 0.3f, 1.f );
			sprintf(Name, GlobalText[2012]);	
		}
	}
	else if(o->Type == MODEL_POTION+33)//���� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		if(Level == 0)
		{
			glColor3f ( 1.0f, 0.3f, 0.3f );
			sprintf(Name, ItemAttribute[ITEM_POTION+33].Name);	
		}
		else
		if(Level == 1)
		{
			glColor3f ( 1.0f, 0.3f, 0.3f );
			sprintf(Name, GlobalText[2013]);	
		}
	}
	else if(o->Type == MODEL_POTION+34)//�Ķ� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		if(Level == 0)
		{
			glColor3f ( 0.3f, 0.3f, 1.f );
			sprintf(Name, ItemAttribute[ITEM_POTION+34].Name);	
		}
		else
		if(Level == 1)
		{
			glColor3f ( 0.3f, 0.3f, 1.f );
			sprintf(Name, GlobalText[2014]);	
		}
	}
	else if(o->Type == MODEL_EVENT+21)//��ȫ ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 1.f, 0.3f, 1.f );
		sprintf(Name, GlobalText[2012]);	
	}
	else if(o->Type == MODEL_EVENT+22)//���� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 1.0f, 0.3f, 0.3f );
		sprintf(Name, GlobalText[2013]);	
	}
	else if(o->Type == MODEL_EVENT+23)//�Ķ� ���ڸ�����.(�߷�Ÿ�ε��� �̺�Ʈ��)
	{
		glColor3f ( 0.3f, 0.3f, 1.f );
		sprintf(Name, GlobalText[2014]);	
	}
#endif

    else if ( o->Type==MODEL_EVENT+11 )
    {
        glColor3f ( 1.f, 0.8f, 0.1f );
#ifdef FRIEND_EVENT
        if ( Level==2 ) //  ������ ��.
        {
            sprintf ( Name, GlobalText[1098] );  //  ������ ��/
        }
        else
#endif// FRIEND_EVENT
        {
            sprintf ( Name, GlobalText[810] );  //  ����.
        }
    }
	else if(o->Type==MODEL_EVENT+12)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf ( Name, GlobalText[906] );	//. ������ ����
	}
	else if(o->Type==MODEL_EVENT+13)
	{
		glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf ( Name, GlobalText[907] );	//. ��ũ����
	}
	else if(o->Type==MODEL_EVENT+14)
	{
		glColor3f( 1.f, 0.8f, 0.1f );
        switch ( Level )
        {
        case 2:
		    sprintf( Name, GlobalText[928] );	//. ������ ����
            break;
        case 3:
		    sprintf( Name, GlobalText[929] );	//. ������ ����
            break;
        default :
		    sprintf( Name, GlobalText[922] );	//. ������ ����
            break;
        }
	}
	else if(o->Type==MODEL_EVENT+15)
	{
		glColor3f( 1.f, 0.8f, 0.1f );
		sprintf( Name, GlobalText[925] );	// �������� ����
	}
#ifdef CHINA_MOON_CAKE
	else if(o->Type==MODEL_EVENT+17)
    {
		glColor3f( 1.f, 0.8f, 0.1f );
		sprintf( Name, GlobalText[118]);    //  �߱� ����.
    }
#endif// CHINA_MOON_CAKE
	else if(o->Type == MODEL_WING+11)//��ȯ����
	{
		sprintf(Name,"%s %s",SkillAttribute[30+Level].Name,GlobalText[102]);
	}
    else if(o->Type == MODEL_HELPER+10)//���Ź���
	{
		for(int i=0;i<MAX_MONSTER;i++)
		{
			if(SommonTable[Level] == MonsterScript[i].Type)
			{
        		sprintf(Name,"%s %s",MonsterScript[i].Name,GlobalText[103]);
				break;
			}
		}
	}
    else if ( o->Type==MODEL_POTION+21 && Level == 3 )    //  ������ǥ��
    {
	    glColor3f ( 1.f, 0.8f, 0.1f );
		sprintf( Name, GlobalText[1290] );
    }
    else if ( o->Type==MODEL_POTION+7 ) //  ���м� ����.//���ƹ���
    {
        switch ( Level )
        {
        case 0: sprintf( Name, GlobalText[1413] ); break;
        case 1: sprintf( Name, GlobalText[1414] ); break;
        }
    }
    else if ( o->Type==MODEL_HELPER+7 ) //  ��� ����
    {
        switch ( Level )
        {
        case 0: sprintf( Name, GlobalText[1460] ); break;  //  Ȱ �뺴.
        case 1: sprintf( Name, GlobalText[1461] ); break;  //  â �뺴.
        }
    }
    else if ( o->Type==MODEL_HELPER+11 )    //  �ֹ���.
    {
        switch ( Level )
        {
        case 0: sprintf( Name, GlobalText[1416] ); break;  //  ����� �ֹ���.
        case 1: sprintf( Name, GlobalText[1462] ); break;  //  ������ ���� ��ġ.
        }
    }
    else if ( o->Type==MODEL_EVENT+18 )
    {
        sprintf( Name, GlobalText[1462] );  //  ������ ���� ��ġ.
    }
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	else
	{
		bFirstOK = false;
	}

	if( bFirstOK == false )
	{
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef ADD_SEED_SPHERE_ITEM
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		if ((o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ�
			|| (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
		|| (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129))	// �õ彺�Ǿ�
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
	else if ((o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ�
		|| (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
		|| (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129))	// �õ彺�Ǿ�
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	{
		glColor3f(0.7f,0.4f,1.0f);	// TEXT_COLOR_VIOLET
		strcpy ( Name, ItemAttribute[o->Type-MODEL_ITEM].Name );
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef PBG_ADD_SANTAINVITATION
	//��Ÿ������ �ʴ���.
	else if( o->Type == MODEL_HELPER+66 )
	{
		glColor3f( 0.6f, 0.4f, 1.0f);
		sprintf(Name, ItemAttribute[ITEM_HELPER+66].Name);
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	//����� ����
	else if( o->Type == MODEL_POTION+100 )
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[ITEM_POTION+100].Name);
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING // (����) ���� ���� 100% ���� ���� 
	else if(o->Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN 
			&& o->Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END)
	{
		glColor3f ( 0.9f, 0.53f, 0.13f );
		sprintf(Name, ItemAttribute[o->Type - MODEL_ITEM].Name);
	}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef PBG_ADD_CHARACTERCARD
	// ���� ��ũ ��ȯ���� ī��
	else if(o->Type == MODEL_HELPER+97 || o->Type == MODEL_HELPER+98 || o->Type == MODEL_POTION+91)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[o->Type].Name);
	}
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	else if(o->Type == MODEL_HELPER+99)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[ITEM_HELPER+99].Name);
	}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
	// Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
	else if(o->Type >= MODEL_HELPER+117 && o->Type <= MODEL_HELPER+120)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[o->Type-MODEL_ITEM].Name);
	}
#endif //PBG_ADD_SECRETITEM
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	else if(o->Type == MODEL_HELPER+109)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+109].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
	else if(o->Type == MODEL_HELPER+110)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+110].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	else if(o->Type == MODEL_HELPER+111)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+111].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	else if(o->Type == MODEL_HELPER+112)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+112].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
	else if(o->Type == MODEL_HELPER+113)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+113].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
	else if(o->Type == MODEL_HELPER+114)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+114].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
	else if(o->Type == MODEL_HELPER+115)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_HELPER+115].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
	else if(o->Type == MODEL_POTION+112)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_POTION+112].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
	else if(o->Type == MODEL_POTION+113)
	{
		glColor3f(1.0f, 0.8f, 0.1f);
		sprintf(Name, ItemAttribute[MODEL_POTION+113].Name);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD		// �ű� Ű(���)	// MODEL_POTION+113
	else
	{
        //  �׼���Ʈ ������.
		//	���� �ø���
        if ( o->Type==MODEL_STAFF+10 || o->Type==MODEL_SWORD+19 || o->Type==MODEL_BOW+18 || o->Type==MODEL_MACE+13)
        {
            glColor3f(1.f,0.1f,1.f);
        }
#ifdef SOCKET_SYSTEM
		else if (g_SocketItemMgr.IsSocketItem(o))
		{
			glColor3f(0.7f,0.4f,1.0f);	// TEXT_COLOR_VIOLET
		}
#endif	// SOCKET_SYSTEM
        else if((ItemOption&63) > 0 && ( o->Type<MODEL_WING+3 || o->Type>MODEL_WING+6 ) && o->Type!=MODEL_HELPER+30 
			&& ( o->Type<MODEL_WING+36 || o->Type>MODEL_WING+40 )
#ifdef ADD_ALICE_WINGS_1
			&& (o->Type<MODEL_WING+42 || o->Type>MODEL_WING+43)
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			&& !(o->Type>=MODEL_WING+49 && o->Type<=MODEL_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)  //  ������ ���� ~ ����� ����. ����. ��ȯ���� 2,3�� ����.
		{
			glColor3f(0.1f,1.f,0.5f);
		}
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
		else if( MODEL_POTION+101 <= o->Type && o->Type <= MODEL_POTION+109 )
		{
			// �ǹ�������, ���̿��� ��ɼ�, ��ũ�ι��� ����, ��ũ�ι���
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
		else if (o->Type == MODEL_POTION+111)	// ������ ����
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
		// �����ȭ
		else if(o->Type == MODEL_POTION+120)
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
		else if(o->Type == MODEL_POTION+121)
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
		else if(o->Type == MODEL_POTION+122)
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
		else if(o->Type == MODEL_POTION+123 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
		else if(o->Type == MODEL_POTION+124 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
		else if( MODEL_POTION+134 <= o->Type && o->Type <= MODEL_POTION+139 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		else if( o->Type == MODEL_HELPER+116 )
		{
			glColor3f ( 0.9f, 0.53f, 0.13f );
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		else if( ITEM_WING+130 <= o->Type && 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			o->Type <= ITEM_WING+135
#else //PBG_ADD_NEWCHAR_MONK_ITEM
			o->Type <= ITEM_WING+134 
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)
		{
			glColor3f ( 0.9f, 0.53f, 0.13f );
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
		else if( MODEL_POTION+114 <= o->Type && o->Type <= MODEL_POTION+119 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
		else if( MODEL_POTION+126 <= o->Type && o->Type <= MODEL_POTION+129 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
		else if( MODEL_POTION+130 <= o->Type && o->Type <= MODEL_POTION+132 )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		else if( MODEL_HELPER+121==o->Type )
		{
			glColor3f(1.f,0.8f,0.1f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef PBG_ADD_GENSRANKING
		else if(o->Type>=MODEL_POTION+141 && o->Type<=MODEL_POTION+144)		// ������
		{
		   	glColor3f (0.9f, 0.53f, 0.13f);
			sprintf(Name, ItemAttribute[o->Type].Name);
		}
#endif //PBG_ADD_GENSRANKING
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if (o->Type >= MODEL_POTION+157 && o->Type <= MODEL_POTION+159)
		{
			glColor3f(1.f, 0.8f, 0.1f);
		}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if ( o->Type==MODEL_WING+25 )      //  ������ ����.
		{
		    glColor3f ( 1.f, 0.8f, 0.1f );
		}
        else if ( o->Type==MODEL_POTION+28 || o->Type==MODEL_POTION+29 )    //  ������ ǥ��.
        {
		    glColor3f ( 1.f, 0.8f, 0.1f );
        }
		else if(Level >= 7)
		{
			glColor3f(1.f,0.8f,0.1f);
		}
		else if(((ItemLevel>>7)&1) || ((ItemLevel>>2)&1) || ((ItemLevel>>1)&1) || (ItemLevel&1))
		{
			glColor3f(0.4f,0.7f,1.f);
		}
		else if(Level == 0)
		{
			glColor3f(0.7f,0.7f,0.7f);
		}
		else if(Level < 3)
		{
			glColor3f(0.9f,0.9f,0.9f);
		}
		else if(Level < 5)
		{
			glColor3f(1.f,0.5f,0.2f);
		}
		else if(Level < 7)
		{
			glColor3f(0.4f,0.7f,1.f);
		}

		char TextName[64];
		if ( g_csItemOption.GetSetItemName( TextName, o->Type-MODEL_ITEM, ItemExtOption ) )
		{
            glColor3f ( 1.f, 1.f, 1.f );
			g_pRenderText->SetFont(g_hFontBold);
			g_pRenderText->SetTextColor(0, 255, 0, 255);
			g_pRenderText->SetBgColor(60, 60, 200, 255);

			strcat ( TextName, ItemAttribute[o->Type-MODEL_ITEM].Name );
		}
		else
		{
			strcpy ( TextName, ItemAttribute[o->Type-MODEL_ITEM].Name );
		}

		if(Level == 0)
			sprintf(Name,"%s",TextName);
		else
			sprintf(Name,"%s +%d",TextName,Level);

		if((ItemLevel>>7)&1)
		{
			if(o->Type!=MODEL_HELPER+3)
    			strcat(Name,GlobalText[176]);
			else    //  ����Ʈ.
            {
                strcat(Name, " +" );
    			strcat(Name,GlobalText[179]);
            }
		}
        //  �ɼ�.
		if( (ItemLevel&3) || ((ItemOption>>6)&1) )
			strcat(Name,GlobalText[177]);
        //  ���.
		if((ItemLevel>>2)&1)
			strcat(Name,GlobalText[178]);
	}
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#endif //PBG_FIX_ITEMNAMEINDEX
#ifdef LJH_FIX_RUNTIME_ERROR_WHEN_RENDERING_DROPPED_ITEMNAME
	GLfloat fCurColor[4] = { 1.f, 1.f, 1.f, 0.0f };
#else  //LJH_FIX_RUNTIME_ERROR_WHEN_RENDERING_DROPPED_ITEMNAME
	GLfloat fCurColor[3] = { 1.f, 1.f, 1.f };
#endif //LJH_FIX_RUNTIME_ERROR_WHEN_RENDERING_DROPPED_ITEMNAME
	glGetFloatv(GL_CURRENT_COLOR, fCurColor);
	if(fCurColor[0] < 0.9f || fCurColor[1] < 0.9f || fCurColor[2] < 0.9f)
		g_pRenderText->SetTextColor(fCurColor[0]*255, fCurColor[1]*255, fCurColor[2]*255, 255);
	
	if(!Sort)
	{
    	g_pRenderText->RenderText(MouseX,MouseY-15,Name,0, 0, RT3_WRITE_CENTER);
	}
	else
	{
    	g_pRenderText->RenderText(o->ScreenX,o->ScreenY-15,Name,0, 0, RT3_WRITE_CENTER);
	}

	g_pRenderText->SetTextColor(255, 230, 200, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 255);
}

///////////////////////////////////////////////////////////////////////////////
// ����ȭ�� Width�� ���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////
int GetScreenWidth()
{
	int iWidth = 0;

#ifdef MOD_INTERFACE_CAMERAWORK
	return 640;
#endif //MOD_INTERFACE_CAMERAWORK

	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INVENTORY)
		&& (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHARACTER)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MIXINVENTORY)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_TRADE)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYSHOP_INVENTORY)
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY)
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYCOIN_REGISTRATION)
#endif // KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef LEM_ADD_LUCKYITEM
			|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYITEMWND)
#endif // LEM_ADD_LUCKYITEM
		))
	{
		iWidth = 640 - (190 * 2);
	}
	else if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHARACTER)
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		&& (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYQUEST)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC))
#else	// ASG_ADD_UI_QUEST_PROGRESS_ETC
		&& g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYQUEST)
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC
		)
	{
     	iWidth = 640 - (190 * 2);
	}
	else if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHARACTER) 
		&& g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PET)
		)
	{
        iWidth = 640 - (190 * 2);
	}
	else if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_REFINERY) )
	{
		iWidth = 640 - (190 * 2);
	}
	else if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INVENTORY) 
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHARACTER) 
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PARTY)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCGUILDMASTER)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GUILDINFO)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GUARDSMAN) 
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_SENATUS) 
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GATEKEEPER)
        || g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYQUEST)
        || g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_SERVERDIVISION)
        || g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_COMMAND)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCQUEST)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GATESWITCH)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CATAPULT)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DEVILSQUARE)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_BLOODCASTLE)
#ifdef PSW_GOLDBOWMAN
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GOLD_BOWMAN)
#endif //PSW_GOLDBOWMAN
#ifdef PSW_EVENT_LENA
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GOLD_BOWMAN_LENA)
#endif //PSW_EVENT_LENA	
#ifdef YDG_ADD_NEW_DUEL_UI
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DUELWATCH)
#endif	// YDG_ADD_NEW_DUEL_UI
#ifdef ASG_ADD_UI_NPC_DIALOGUE
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE)
#endif	// ASG_ADD_UI_NPC_DIALOGUE
#ifdef ASG_ADD_UI_NPC_MENU
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_MENU)
#endif	// ASG_ADD_UI_NPC_MENU
#ifdef ASG_MOD_3D_CHAR_EXCLUSION_UI
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS)
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#endif	// ASG_MOD_3D_CHAR_EXCLUSION_UI
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC)
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC
#ifdef LDK_ADD_EMPIREGUARDIAN_UI
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_EMPIREGUARDIAN_NPC)		
#endif //LDK_ADD_EMPIREGUARDIAN_UI
#ifdef YDG_FIX_DOPPELGANGER_NPC_WINDOW_SCREEN_SIZE
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DOPPELGANGER_NPC)
#endif	// YDG_FIX_DOPPELGANGER_NPC_WINDOW_SCREEN_SIZE
#ifdef LDS_ADD_UI_UNITEDMARKETPLACE
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_UNITEDMARKETPLACE_NPC_JULIA)
#endif // LDS_ADD_UI_UNITEDMARKETPLACE
#ifdef PBG_ADD_GENSRANKING
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GENSRANKING)
#endif //PBG_ADD_GENSRANKING
		) 
	{
        iWidth = 640 - 190;
	}
#ifndef ASG_MOD_3D_CHAR_EXCLUSION_UI
#ifdef ASG_ADD_UI_QUEST_PROGRESS
	else if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS))
	{
		iWidth = 640 - 267;
	}
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#endif	// ASG_MOD_3D_CHAR_EXCLUSION_UI
	else
	{
		iWidth = 640;
	}

	return iWidth;
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮 ��ü �ʱ�ȭ
///////////////////////////////////////////////////////////////////////////////

void ClearInventory()
{
#ifdef _VS2008PORTING
	for(int i=0;i<MAX_EQUIPMENT;i++)
	{
		CharacterMachine->Equipment[i].Type = -1;
		CharacterMachine->Equipment[i].Number = 0;
	}
	for(int i=0;i<MAX_INVENTORY;i++)
	{
		Inventory[i].Type = -1;
		Inventory[i].Number = 0;
	}
	for(int i=0;i<MAX_SHOP_INVENTORY;i++)
	{
		ShopInventory[i].Type = -1;
		ShopInventory[i].Number = 0;
	}
#else // _VS2008PORTING
	int i;
	for(i=0;i<MAX_EQUIPMENT;i++)
	{
	    CharacterMachine->Equipment[i].Type = -1;
	    CharacterMachine->Equipment[i].Number = 0;
	}
	for(i=0;i<MAX_INVENTORY;i++)
	{
		Inventory[i].Type = -1;
		Inventory[i].Number = 0;
	}
	for(i=0;i<MAX_SHOP_INVENTORY;i++)
	{
		ShopInventory[i].Type = -1;
		ShopInventory[i].Number = 0;
	}
#endif // _VS2008PORTING

	COMGEM::Init();
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮�� ������ �߰�
///////////////////////////////////////////////////////////////////////////////

//  �������� ���� �����Ѵ�.
void SetItemColor ( int index, ITEM* Inv, int color )
{
	int Width  = ItemAttribute[Inv[index].Type].Width;
	int Height = ItemAttribute[Inv[index].Type].Height;

    for(int k=Inv[index].y;k<Inv[index].y+Height;k++)
	{
		for(int l=Inv[index].x;l<Inv[index].x+Width;l++)
		{
			int Number = k*COLUMN_TRADE_INVENTORY+l;
            Inv[Number].Color = color;
		}
	}
}

//  �� �����۸� ���Ѵ�. ( -1: �� ���� ������, 0: ���� ������, 1: �� ���� ������ ).
int CompareItem ( ITEM item1, ITEM item2 )
{
    int equal = 0;
    if ( item1.Type!=item2.Type )
    {
        return  2;
    }
    else
    if ( item1.Class==item2.Class && item1.Type==item2.Type )
    {
        int level1 = (item1.Level>>3)&15;
        int level2 = (item2.Level>>3)&15;
        int option1= (item1.Option1&63);
        int option2= (item2.Option1&63);
        int skill1 = (item1.Level>>7)&1;
        int skill2 = (item2.Level>>7)&1;

        equal = 1;
        if( level1==level2 )
        {
            equal = 0;
        }
        else
        if( level1<level2 )
        {
            equal = -1;
        }
        //  ��ų.
        if ( equal==0 )
        {
            if ( skill1<skill2 )
            {
                equal = -1;
            }
            else if ( skill1>skill2 )
            {
                equal = 1;
            }
        }
        //  �׼���Ʈ.
        if ( equal==0 )
        {
            if ( option1<option2 )
            {
                equal = -1;
            }
            else if ( option1>option2 )
            {
                equal = 1;
            }
        }
        //  �ɼ�.
        if ( equal==0 )
        {
            if ( item1.SpecialNum<item2.SpecialNum )
            {
                equal = -1;
            }
            else if ( item1.SpecialNum>item2.SpecialNum )
            {
                equal = 1;
            }
            else
            {
                int     Num = max ( item1.SpecialNum, item2.SpecialNum );
                int     addOption1 = 0;
                int     addOptionV1= 0;
                int     addOption2 = 0;
                int     addOptionV2= 0;
                for( int i=0; i<Num; ++i )
                {
		            switch(item1.Special[i])
		            {
		            case AT_IMPROVE_DAMAGE:
		            case AT_IMPROVE_MAGIC:
					case AT_IMPROVE_CURSE:
		            case AT_IMPROVE_BLOCKING:
		            case AT_IMPROVE_DEFENSE:
			            addOption1 = 1;
                        addOptionV1= item1.SpecialValue[i];
			            break;
		            }
		            switch(item2.Special[i])
		            {
		            case AT_IMPROVE_DAMAGE:
		            case AT_IMPROVE_MAGIC:
					case AT_IMPROVE_CURSE:
		            case AT_IMPROVE_BLOCKING:
		            case AT_IMPROVE_DEFENSE:
			            addOption2 = 1;
                        addOptionV2= item2.SpecialValue[i];
			            break;
		            }
                }

                if ( addOption1<addOption2 || addOptionV1<addOptionV2 )
                {
                    equal = -1;
                }
                else if ( addOption1!=addOption2 && addOptionV1!=addOptionV2 )
                {
                    equal = 1;
                }
            }
        }
        //  ������.
        if ( equal==0 )
        {
            if( item1.Durability<item2.Durability  )
                equal = -1;
            if( item1.Durability>item2.Durability  )
                equal = 1;
        }
    }
    return  equal;
}

void InsertInventory(ITEM *Inv,int Width,int Height,int Index,BYTE *Item,bool First)
{
	int Type = ConvertItemType(Item);

	if(Type == 0x1FFF) return;

	if(Inv==Inventory)
	{
		//�����
		if(Index < 12)
		{
			ITEM *ip = &CharacterMachine->Equipment[Index];
			ip->Type       = Type;
			ip->Durability = Item[2];
			ip->Option1    = Item[3];
            ip->ExtOption  = Item[4];   //  ��Ʈ Ÿ��.
			ip->Number     = 1;
			ip->option_380 = false;
			byte b = ( ( (Item[5] & 0x08) << 4) >>7);
			ip->option_380 = b;
			ip->Jewel_Of_Harmony_Option = (Item[6] & 0xf0) >> 4;//�ɼ� ����
			ip->Jewel_Of_Harmony_OptionLevel = Item[6] & 0x0f;//�ɼ� ����( ���� �ƴ� )

			ItemConvert(ip,Item[1],Item[3],Item[4]);			
            SetCharacterClass(Hero);
			OBJECT *o = &Hero->Object;
			if(Index==EQUIPMENT_HELPER)
			{
                if ( InChaosCastle()==false )
                {
                    switch(Type)
                    {
                    case ITEM_HELPER  :CreateBug(MODEL_HELPER  ,o->Position,o);break;
                    case ITEM_HELPER+2:CreateBug(MODEL_UNICON  ,o->Position,o);
                        if(!Hero->SafeZone)
                            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,1,o);
                        break;
                    case ITEM_HELPER+3:CreateBug(MODEL_PEGASUS, o->Position,o);
                        if(!Hero->SafeZone)
                            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,1,o);
                        break;
                    case ITEM_HELPER+4:CreateBug(MODEL_DARK_HORSE ,o->Position,o);
                        if(!Hero->SafeZone)
                            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,1,o);
                        break;
					case ITEM_HELPER+37:	//^ �渱 �κ��丮�� ������ ������ ȿ��
						Hero->Helper.Option1 = ip->Option1;
						if(ip->Option1 == 0x01)
						{
							CreateBug(MODEL_FENRIR_BLACK, o->Position, o);
						}
						else if(ip->Option1 == 0x02)
						{
							CreateBug(MODEL_FENRIR_BLUE, o->Position, o);
						}
						else if(ip->Option1 == 0x04)
						{
							CreateBug(MODEL_FENRIR_GOLD, o->Position, o);
						}
						else
						{
							CreateBug(MODEL_FENRIR_RED, o->Position, o);
						}
						if(!Hero->SafeZone)
                            CreateEffect(BITMAP_MAGIC+1,o->Position,o->Angle,o->Light,1,o);
						break;
                    }
                }
			}
#ifdef PET_SYSTEM
            else if ( Index==EQUIPMENT_WEAPON_LEFT )
            {
                switch ( Type )
                {
                case ITEM_HELPER+5:
                    giPetManager::CreatePetDarkSpirit ( Hero );            
                    break;
    #ifdef DARK_WOLF
                    //  ���Ƿ� ����.
                case ITEM_SHIELD :
                    giPetManager::CreatePetDarkWolf ( Hero );            
                    break;
    #endif// DARK_WOLF
                }
            }
#endif// PET_SYSTEM

            if ( Index==EQUIPMENT_RING_LEFT || Index==EQUIPMENT_RING_RIGHT && ( Hero->EtcPart<=0 || Hero->EtcPart>3 ) )
            {
                if ( Type==ITEM_HELPER+20 && (ip->Level>>3)==3 )
                {
                    DeleteParts ( Hero );
                    Hero->EtcPart = PARTS_LION;
                }
            }

			if ( Index==EQUIPMENT_WING)
			{
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
				if (Type==ITEM_WING+39 || 
					Type==ITEM_HELPER+30 || 
					Type==ITEM_WING+130 ||	// �߰� ����
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
					Type==ITEM_WING+49 ||
					Type==ITEM_WING+50 ||
					Type==ITEM_WING+135||
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
					Type==ITEM_WING+40 )	// ���� ������ ���� ��� ����
#else //LDK_ADD_INGAMESHOP_SMALL_WING
				if (Type==ITEM_WING+39 || Type==ITEM_HELPER+30 || Type==ITEM_WING+40)	// ���� ������ ���� ��� ����
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
				{
					DeleteCloth(Hero, &Hero->Object);
				}
			}

		}
		else if(Index >= 12 && Index < 76)
		{
			int InventoryIndex = Index - 12;
			ITEM_ATTRIBUTE *ap = &ItemAttribute[Type];
			for(int i=0;i<ap->Height;i++)
			{
				for(int j=0;j<ap->Width;j++)
				{
					ITEM *ip = &Inv[InventoryIndex+i*Width+j];
					ip->Type       = Type;
           			ip->Durability = Item[2];
           			ip->Option1    = Item[3];
                    ip->ExtOption  = Item[4];
					ip->x          = InventoryIndex%8;
					ip->y          = InventoryIndex/8;
					ip->option_380 = false;
					byte b = ( ( (Item[5] & 0x08) << 4) >>7);
					ip->option_380 = b;
					ip->Jewel_Of_Harmony_Option = (Item[6] & 0xf0) >> 4;//�ɼ� ����
					ip->Jewel_Of_Harmony_OptionLevel = Item[6] & 0x0f;//�ɼ� ����( ���� �ƴ� )

					if(i==0 && j==0)
						ip->Number = 1;
					else
						ip->Number = 0;
		        	ItemConvert(ip,Item[1],Item[3],Item[4]);


				}
			}

            if( SrcInventoryIndex < 12 )
            {
                //  ���ݼӵ� ���.
        		if(CharacterAttribute->AbilityTime[0] != 0)
                {
                    CharacterMachine->CalculateAttackSpeed();
                }
                //  ���ݼӵ� ���.
        		if(CharacterAttribute->AbilityTime[2] != 0)
                {
                    CharacterMachine->CalculateAttackSpeed();
                }
            }
		}
		else
		{
			int InventoryIndex = Index - 76;
			ITEM_ATTRIBUTE *ap = &ItemAttribute[Type];
			for(int i=0;i<ap->Height;i++)
			{
				for(int j=0;j<ap->Width;j++)
				{
					ITEM *ip = &g_PersonalShopInven[InventoryIndex+i*Width+j];
					ip->Type       = Type;
					ip->Durability = Item[2];
					ip->Option1    = Item[3];
                    ip->ExtOption  = Item[4];
					ip->x          = InventoryIndex%8;
					ip->y          = InventoryIndex/8;
					ip->option_380 = false;
					byte b = ( ( (Item[5] & 0x08) << 4) >>7);
					ip->option_380 = b;
					ip->Jewel_Of_Harmony_Option = (Item[6] & 0xf0) >> 4;//�ɼ� ����
					ip->Jewel_Of_Harmony_OptionLevel = Item[6] & 0x0f;//�ɼ� ����( ���� �ƴ� )
					if(i==0 && j==0)
						ip->Number = 1;
					else
						ip->Number = 0;
					ItemConvert(ip,Item[1],Item[3],Item[4]);
				}
			}
			
            if( SrcInventoryIndex < 12 )
            {
                //  ���ݼӵ� ���.
				if(CharacterAttribute->AbilityTime[0] != 0)
                {
                    CharacterMachine->CalculateAttackSpeed();
                }
				if(CharacterAttribute->AbilityTime[2] != 0)
                {
                    CharacterMachine->CalculateAttackSpeed();
                }
            }
		}
	}
	else
	{
		//Ʈ���̵����
		int InventoryIndex = Index;
		ITEM_ATTRIBUTE *ap = &ItemAttribute[Type];
		for(int i=0;i<ap->Height;i++)
		{
			for(int j=0;j<ap->Width;j++)
			{
				ITEM *ip = &Inv[InventoryIndex+i*Width+j];
				ip->Type       = Type;
       			ip->Durability = Item[2];
      			ip->Option1    = Item[3];
                ip->ExtOption  = Item[4];
				ip->x          = InventoryIndex%8;
				ip->y          = InventoryIndex/8;
				ip->option_380 = false;
				byte b = ( ( (Item[5] & 0x08) << 4) >>7);
				ip->option_380 = b;
				ip->Jewel_Of_Harmony_Option = (Item[6] & 0xf0) >> 4;//�ɼ� ����
				ip->Jewel_Of_Harmony_OptionLevel = Item[6] & 0x0f;//�ɼ� ����( ���� �ƴ� )
				if(i==0 && j==0)
					ip->Number = 1;
				else
					ip->Number = 0;
	    		ItemConvert(ip,Item[1],Item[3],Item[4]);
			}
		}
	}

	hanguo_check12();
	if(!First)
	{
		if(CharacterMachine->Equipment[EQUIPMENT_HELPER].Type == -1)
    		DeleteBug(&Hero->Object);
#ifdef PET_SYSTEM
        if ( CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type==-1 )
            giPetManager::DeletePet ( Hero );            
#endif// PET_SYSTEM

        ITEM& rl = CharacterMachine->Equipment[EQUIPMENT_RING_LEFT];
        ITEM& rr = CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT];
        if ( ( rl.Type!=ITEM_HELPER+20 || (rl.Level>>3)!=3 ) && ( rr.Type!=ITEM_HELPER+20 || (rr.Level>>3)!=3 ) )
        {
            if ( Hero->EtcPart<PARTS_ATTACK_TEAM_MARK )
            {
                DeleteParts ( Hero );
                if ( Hero->EtcPart>3 ) Hero->EtcPart = 0;
            }
        }
	}
}

bool EquipmentItem = false;
extern int BuyCost;

#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
// �ΰ��Ӽ��� ���� ���� �ؿ����� ĳ�ü������� �����Լ� �̹Ƿ� �� �Լ��� ���̻� �߰����� ������!!!!!
bool IsPartChargeItem(ITEM* pItem)
{
#if !defined(PSW_PARTCHARGE_ITEM1) && defined(LDK_ADD_CASHSHOP_FUNC)
	//���� ���� ������ ó��
	switch(pItem->Type)
	{
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	case ITEM_POTION+96:
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
	case ITEM_HELPER+64:
	case ITEM_HELPER+65:
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef PBG_FIX_CHAOSCARD
	case ITEM_POTION+54:
#endif //PBG_FIX_CHAOSCARD
		return true;
	default:
		return false;
	}
#else //!defined(PSW_PARTCHARGE_ITEM1) && defined(LDK_ADD_CASHSHOP_FUNC)
	//�ؿ� ���� ������ ó�� - ���� �������� ��������
	if(
#ifdef CSK_FREE_TICKET
		// ���� ����� �Ǹ� ���� ǥ�� ���ϰ� ���� ó��
		(pItem->Type >= ITEM_HELPER+46 && pItem->Type <= ITEM_HELPER+48)
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
		|| (pItem->Type == ITEM_POTION+54)
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
		// ��;����� �Ǹ� ���� ǥ�� ���ϰ� ����ó��
		|| (pItem->Type >= ITEM_POTION+58 && pItem->Type <= ITEM_POTION+62)
#endif // CSK_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
		// ��;����� �Ǹ� (7-12) ���� ǥ�� ���ϰ� ����ó��
		|| (pItem->Type >= ITEM_POTION+145 && pItem->Type <= ITEM_POTION+150)
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
		// ���� �����(���ð���, �ٸ�ī, �ٸ�ī ��7��) �Ǹ� ���� ǥ�� ���ϰ� ���� ó��
		|| (pItem->Type >= ITEM_HELPER+125 && pItem->Type <= ITEM_HELPER+127)
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef CSK_LUCKY_CHARM
		|| pItem->Type == ITEM_POTION+53
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
		|| (pItem->Type >= ITEM_HELPER+43 && pItem->Type <= ITEM_HELPER+45)
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
		|| (pItem->Type >= ITEM_POTION+70 && pItem->Type <= ITEM_POTION+71)
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
		|| (pItem->Type >= ITEM_POTION+72 && pItem->Type <= ITEM_POTION+77)
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
		|| (pItem->Type == ITEM_HELPER+59)
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
		|| ( pItem->Type >= ITEM_HELPER+54 && pItem->Type <= ITEM_HELPER+58)
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
		|| (pItem->Type >= ITEM_POTION+78 && pItem->Type <= ITEM_POTION+82)
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
		|| (pItem->Type == ITEM_HELPER+60)
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET // ȯ���� ��� ���� �����
		|| (pItem->Type == ITEM_HELPER+61)
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_CHARACTER_CARD
		|| (pItem->Type == ITEM_POTION+91)
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD      
		|| (pItem->Type >= ITEM_POTION+92 && pItem->Type <= ITEM_POTION+93)
		|| (pItem->Type == ITEM_POTION+95)
#endif //PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
		|| (pItem->Type == ITEM_POTION+94) // ����Ʈ �߰� ġ�� ����
#endif //PSW_NEW_ELITE_ITEM
#ifdef PSW_ADD_PC4_SEALITEM
		|| (pItem->Type >= ITEM_HELPER+62 && pItem->Type <= ITEM_HELPER+63)
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
		|| (pItem->Type >= ITEM_POTION+97 && pItem->Type <= ITEM_POTION+98)
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
		|| (pItem->Type == ITEM_POTION+96)
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
		|| ( pItem->Type == ITEM_HELPER+64 || pItem->Type == ITEM_HELPER+65 )
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
		|| ( pItem->Type == ITEM_HELPER+69 )	// ��Ȱ�� ����
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
		|| ( pItem->Type == ITEM_HELPER+70 )	// �̵��� ����
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef ASG_ADD_CS6_GUARD_CHARM
		|| pItem->Type == ITEM_HELPER+81		// ��ȣ�Ǻ���
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
		|| pItem->Type == ITEM_HELPER+82		// �����ۺ�ȣ����
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM 
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		|| pItem->Type == ITEM_HELPER+93		// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		|| pItem->Type == ITEM_HELPER+94		// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		|| pItem->Type == ITEM_HELPER+107		// ġ��������
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
		|| pItem->Type == ITEM_HELPER+104		// AG���� ����
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
		|| pItem->Type == ITEM_HELPER+105		// SD���� ����
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
		|| pItem->Type == ITEM_HELPER+103		// ��Ƽ ����ġ ���� ������
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
		|| pItem->Type == ITEM_POTION+133		// ����Ʈ SDȸ�� ����
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		|| pItem->Type == ITEM_HELPER+109
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
		|| pItem->Type == ITEM_HELPER+110
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		|| pItem->Type == ITEM_HELPER+111
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
		|| pItem->Type == ITEM_HELPER+112
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
		|| pItem->Type == ITEM_HELPER+113
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
		|| pItem->Type == ITEM_HELPER+114
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
		|| pItem->Type == ITEM_HELPER+115
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
		|| pItem->Type == ITEM_POTION+112
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(���)	// MODEL_POTION+113
		|| pItem->Type == ITEM_POTION+113
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(���)	// MODEL_POTION+113
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
		|| pItem->Type == ITEM_POTION+120 // �����ȭ
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
		|| pItem->Type == ITEM_POTION+123
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
		|| pItem->Type == ITEM_POTION+124
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
		|| pItem->Type == ITEM_POTION+134			
		|| pItem->Type == ITEM_POTION+135			
		|| pItem->Type == ITEM_POTION+136			
		|| pItem->Type == ITEM_POTION+137			
		|| pItem->Type == ITEM_POTION+138			
		|| pItem->Type == ITEM_POTION+139			
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		|| pItem->Type == ITEM_WING+130
		|| pItem->Type == ITEM_WING+131			
		|| pItem->Type == ITEM_WING+132			
		|| pItem->Type == ITEM_WING+133			
		|| pItem->Type == ITEM_WING+134	
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| pItem->Type == ITEM_WING+135
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		|| pItem->Type == ITEM_HELPER+116			//�ű� ǳ���� ����
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDK_ADD_CS7_UNICORN_PET
		|| pItem->Type == ITEM_HELPER+106			//������ ��
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
		|| pItem->Type == ITEM_HELPER+124			// ����ä�� �����.
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
		|| pItem->Type == ITEM_POTION+114
		|| pItem->Type == ITEM_POTION+115
		|| pItem->Type == ITEM_POTION+116
		|| pItem->Type == ITEM_POTION+117
		|| pItem->Type == ITEM_POTION+118
		|| pItem->Type == ITEM_POTION+119
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
		|| pItem->Type == ITEM_POTION+126
		|| pItem->Type == ITEM_POTION+127
		|| pItem->Type == ITEM_POTION+128
		|| pItem->Type == ITEM_POTION+129
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
		|| pItem->Type == ITEM_POTION+130
		|| pItem->Type == ITEM_POTION+131
		|| pItem->Type == ITEM_POTION+132
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		|| pItem->Type == ITEM_HELPER+121
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef YDG_ADD_HEALING_SCROLL
		|| pItem->Type == ITEM_POTION+140	// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL
	)
	{
		return true;
	}
#endif //!defined(PSW_PARTCHARGE_ITEM1) && defined(LDK_ADD_CASHSHOP_FUNC)
	
	return false;
}
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)

// �������� ǰ�� ����Ʈ ����
bool IsHighValueItem(ITEM* pItem)
{
	// �������� ������ ���� ���س��´�.
	int iLevel = (pItem->Level >> 3) & 15;

	if(
		pItem->Type == ITEM_HELPER+3 ||		// ����Ʈ
		pItem->Type == ITEM_POTION+13 ||	// �ູ�� ����
		pItem->Type == ITEM_POTION+14 ||	// ��ȥ�� ����
		pItem->Type == ITEM_POTION+16 ||	// ������ ����
		pItem->Type == ITEM_POTION+22 ||	// â���� ����
		pItem->Type == ITEM_WING+15 ||		// ȥ���� ����
		pItem->Type == ITEM_POTION+31 ||	// ��ȣ�� ����
		pItem->Type == ITEM_WING+30	||		// �༮ ����
		pItem->Type == ITEM_WING+31	||		// ���� ����
		// ������
        (pItem->Type >= ITEM_WING && pItem->Type <= ITEM_WING+6 ) ||	
        pItem->Type == ITEM_HELPER+4 ||		// ��ũȣ���� ��
		pItem->Type == ITEM_HELPER+5 ||		// ��ũ���Ǹ��� ����
		pItem->Type == ITEM_HELPER+30 ||	// ������ ����
#ifdef ADD_ALICE_WINGS_1
		(pItem->Type >= ITEM_WING+36 && pItem->Type <= ITEM_WING+43 ) ||	// 3�� ����, ��ȯ���� ����.
#else	// ADD_ALICE_WINGS_1
		(pItem->Type >= ITEM_WING+36 && pItem->Type <= ITEM_WING+40 ) ||	// 3�� ������
#endif	// ADD_ALICE_WINGS_1
		// ��Ʈ �����۵�
        ((pItem->ExtOption%0x04) == EXT_A_SET_OPTION || (pItem->ExtOption%0x04) == EXT_B_SET_OPTION ) ||
		pItem->Type == ITEM_SWORD+19 ||		// ��õ���� �����
		pItem->Type == ITEM_STAFF+10 ||		// ��õ���� ����������
		pItem->Type == ITEM_BOW+18 ||		// ��õ���� ���뼮��	
		pItem->Type == ITEM_MACE+13 ||		// ��õ���� �������
		pItem->Type == ITEM_HELPER+14 ||	// ��ũ�� ����	
		pItem->Type == ITEM_HELPER+15 ||	// ����
		pItem->Type == ITEM_HELPER+19 ||	// ����������(����Ʈ)
		pItem->Type == ITEM_HELPER+31 ||	// ��ũȣ���� ��ȥ, ��ũ���Ǹ��� ��ȥ
		// ��������, ��ȭ�Ǻ���, �ϱ����ü�, ������ü�
		(pItem->Type >= ITEM_POTION+41 && pItem->Type <= ITEM_POTION+44) ||
		// +7���� �̻��� �����۵�
		(iLevel > 6 && pItem->Type < ITEM_WING) ||
		(pItem->Option1 & 63) > 0 ||		// �ɼ��ִ� ������ 
		// �渱 ���� ������
		(pItem->Type >= ITEM_HELPER+34 && pItem->Type <= ITEM_HELPER+37)
		|| pItem->Type == ITEM_HELPER+52	// �ܵ����� �Ҳ�
		|| pItem->Type == ITEM_HELPER+53	// �ܵ����� ����
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
		|| pItem->Type == ITEM_POTION+121
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST	// ���ε� ��������
		|| pItem->Type == ITEM_POTION+122
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifndef LDS_MOD_INGAMESHOPITEM_POSSIBLETRASH_SILVERGOLDBOX	// ���� ifndef !! ���� ���� // �ݻ�����, �������ڴ� �����Ⱑ �����ϵ��� ��ȹ ����. 
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST			// �ݻ�����
		|| pItem->Type == ITEM_POTION+123
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST			// ��������
		|| pItem->Type == ITEM_POTION+124
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#endif // LDS_MOD_INGAMESHOPITEM_POSSIBLETRASH_SILVERGOLDBOX	// ���� ifndef !! ���� ���� // �ݻ�����, �������ڴ� �����Ⱑ �����ϵ��� ��ȹ ����.
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		|| pItem->Type == ITEM_WING+130
		|| pItem->Type == ITEM_WING+131
		|| pItem->Type == ITEM_WING+132
		|| pItem->Type == ITEM_WING+133
		|| pItem->Type == ITEM_WING+134
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| pItem->Type == ITEM_WING+135
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80  //�����
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76  //������Ź���
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_PC4_GUARDIAN
		|| pItem->Type == ITEM_HELPER+64  //���� ����
		|| pItem->Type == ITEM_HELPER+65  //���� ��ȣ����
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		|| pItem->Type == ITEM_HELPER+109
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
		|| pItem->Type == ITEM_HELPER+110
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		|| pItem->Type == ITEM_HELPER+111
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
		|| pItem->Type == ITEM_HELPER+112
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
		|| pItem->Type == ITEM_HELPER+113
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
		|| pItem->Type == ITEM_HELPER+114
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
		|| pItem->Type == ITEM_HELPER+115
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
		|| pItem->Type == ITEM_POTION+112
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
		|| pItem->Type == ITEM_POTION+113
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
#ifdef LDK_MOD_PREMIUMITEM_SELL
		|| ( pItem->Type==ITEM_HELPER+20 && iLevel==0) 			// �������� ����
#endif //LDK_MOD_PREMIUMITEM_SELL
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type) && pItem->Durability == 255)	// ������������ �κ������۸� �������� ���� �� �ǸŰ���
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (pItem->Type >= ITEM_WING+49 && pItem->Type <= ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef KJH_FIX_SELL_LUCKYITEM
		|| ( Check_ItemAction(pItem, eITEM_SELL) && pItem->Durability > 0 )		// ��Ű �������� �������� �������� �ȼ� ����.
#endif // KJH_FIX_SELL_LUCKYITEM
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// �������� �������� ����
		|| ( COMGEM::isCompiledGem( pItem ) )
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		)
	{
#ifdef LDK_FIX_PERIODITEM_SELL_CHECK
		if(true == pItem->bPeriodItem && false == pItem->bExpiredPeriod)
		{
			return false;
		}
#endif //LDK_FIX_PERIODITEM_SELL_CHECK
#ifdef PBG_MOD_PANDAPETRING_NOTSELLING
		else if(pItem->Type == ITEM_HELPER+80
			|| pItem->Type == ITEM_HELPER+76
			|| pItem->Type == ITEM_HELPER+64
			|| pItem->Type == ITEM_HELPER+65
#ifdef YDG_MOD_SKELETON_NOTSELLING
			|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
			|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif // YDG_MOD_SKELETON_NOTSELLING
			)
		{
			// �Ⱓ�� ����Ǹ� ���� ���� �Ǻ� �̿ܿ� �ǸźҰ�
			if(true == pItem->bPeriodItem && true == pItem->bExpiredPeriod)
			{
				return true;
			}
			else	
				return false;
		}
#endif //PBG_MOD_PANDAPETRING_NOTSELLING
		return true;
	}
	
	return false;
}

// ���λ��� �ŷ����� ������ ǰ��(���߿� �� ����Ʈ�� �⺻���� ��ũ��Ʈ�۾�)
bool IsPersonalShopBan(ITEM* pItem)
{
	if(pItem == NULL)
	{
		return false;
	}

#ifdef KJH_FIX_PERSONALSHOP_BAN_CASHITEM
	if(pItem->bPeriodItem)
	{
		return true;
	}
#endif // KJH_FIX_PERSONALSHOP_BAN_CASHITEM

#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// ���λ��� ���ɿ��� ������ ��� [lem_2010.8.19]
	int nJapanResult = IsItemSet_FromJapan( pItem, eITEM_PERSONALSHOP );
	if( nJapanResult == 1 )			return true;
	else if( nJapanResult == 0 )	return false;
#endif	// LEM_FIX_ITEMSET_FROMJAPAN [lem_2010.8.19]
#if defined LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION || defined PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE
	// �Ⱓ�� �������� �ƴҰ�� �Ϻ� ������ ���� ����( ��ȹ�� ��� �ٲ�� �� ��.��;;;;;; )
	if( (!pItem->bPeriodItem) && 
#ifdef PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE
#ifndef _BLUE_SERVER						// ���� �Ұ���
		pItem->Type == ITEM_POTION+96 ||	// ī��������
		pItem->Type == ITEM_POTION+54 ||	// ī����ī��
#endif //_BLUE_SERVER
#endif //PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE
		pItem->Type == ITEM_HELPER+64		// ����
		|| pItem->Type == ITEM_HELPER+65	// ��ȣ����
		|| pItem->Type == ITEM_HELPER+80	// �Ҵ���
		|| pItem->Type == ITEM_HELPER+76	// �Ҵ����Ź���
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type) && pItem->Durability == 255)	// �������϶� ���ΰŷ� ����
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (pItem->Type==ITEM_HELPER+20 && ((pItem->Level >> 3) & 15)==0) 			// �������� ����
		)
	{
		return false;
	}		
#endif //LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION

// �Ϻ��� ����Ʈ �ذ����� ���Ź��� ��ȹ���濡 ���� ���� ���� (2010.01.21)
// (���� ������, ������ �ŷ�, â����, ���λ��� �Ұ���->����)
	if(pItem->Type == ITEM_HELPER+38		// ������ �Ҵ�Ʈ
#ifndef LJH_MOD_ELITE_SKELETON_WARRIOR_CHANGE_RING_SETTING
		|| pItem->Type == ITEM_HELPER+39	// ����Ʈ �ذ����� ���Ź���
#endif	//LJH_MOD_ELITE_SKELETON_WARRIOR_CHANGE_RING_SETTING	
		|| (pItem->Type == ITEM_POTION+21 && ((pItem->Level>>3)&15) != 3)		// ������ ǥ��
		|| ( pItem->Type >= ITEM_POTION+23 && pItem->Type <= ITEM_POTION+26 )   //  ����Ʈ ������
		|| pItem->Type == ITEM_HELPER+19	// ����������
		|| (pItem->Type == ITEM_POTION+11 && ((pItem->Level>>3)&0x0F) == 13)
#ifdef CSK_LUCKY_SEAL
		|| (pItem->Type >= ITEM_HELPER+43 && pItem->Type <= ITEM_HELPER+45)
#endif //CSK_LUCKY_SEAL
		|| (pItem->Type == ITEM_HELPER+20 && ((pItem->Level>>3)&15) != 0)
		|| pItem->Type == ITEM_POTION+65	// ����������Ʈ�� �Ҳ�
		|| pItem->Type == ITEM_POTION+66	// �︶�̳��� ��
		|| pItem->Type == ITEM_POTION+67	// ����Ǻһ����� ����
		|| pItem->Type == ITEM_POTION+68	// �ɿ��Ǵ�����
#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
		|| IsPartChargeItem(pItem)
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
#ifdef PBG_ADD_CHARACTERCARD
		|| pItem->Type == ITEM_HELPER+97	//���˻� ĳ���� ī��
		|| pItem->Type == ITEM_HELPER+98	//��ũ�ε� ĳ���� ī��
		|| pItem->Type == ITEM_POTION+91	//��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		|| pItem->Type == ITEM_HELPER+99	//ĳ���� ���� ����
#endif //PBG_ADD_CHARACTERSLOT
#ifndef KJH_MOD_CAN_TRADE_PANDA_PET		// ���� �ؿܿ� define
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80	//�Ҵ���
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76	//�Ҵ�����
#endif //PJH_ADD_PANDA_CHANGERING
#endif // KJH_MOD_CAN_TRADE_PANDA_PET	// ���� �ؿܿ� define
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifndef PBG_MOD_SECRETITEM
		// �ŷ� �����ϰԷ� ����
#ifdef PBG_ADD_SECRETITEM
		//Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
		|| (pItem->Type >= ITEM_HELPER+117 && pItem->Type <= ITEM_HELPER+120)
#endif //PBG_ADD_SECRETITEM
#endif //PBG_MOD_SECRETITEM
#ifdef LDS_MOD_CHAOSCHARMITEM_DONOT_TRADE
		|| (pItem->Type == MODEL_POTION+96)		// ī���� ���� ����
#endif // LDS_MOD_CHAOSCHARMITEM_DONOT_TRADE
#ifdef LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
		|| pItem->Type ==ITEM_HELPER+109	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		|| pItem->Type ==ITEM_HELPER+110	// �ű� ���(������)��		// MODEL_HELPER+110
		|| pItem->Type ==ITEM_HELPER+111	// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		|| pItem->Type ==ITEM_HELPER+112	// �ű� �ڼ���(�����)��	// MODEL_HELPER+112
		|| pItem->Type ==ITEM_HELPER+113	// �ű� ���(������) �����	// MODEL_HELPER+113
		|| pItem->Type ==ITEM_HELPER+114	// �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
		|| pItem->Type ==ITEM_HELPER+115	// �ű� �����̾�(���) �����// MODEL_HELPER+115	
#endif // LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
#ifdef LDK_MOD_INGAMESHOP_WIZARD_RING_PERSONALSHOPBAN
		|| ( pItem->Type==ITEM_HELPER+20 && ((pItem->Level >> 3) & 15)==0) 			// �������� ����
#endif //LDK_MOD_INGAMESHOP_WIZARD_RING_PERSONALSHOPBAN
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| (pItem->Type >= ITEM_POTION+151 && pItem->Type <= ITEM_POTION+156)	// �ð��� ����Ʈ ������
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| g_pMyInventory->IsInvenItem(pItem->Type)
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		)
	{		
		return true;
	}
#ifdef LEM_ADD_LUCKYITEM
	if( Check_ItemAction( pItem, eITEM_PERSONALSHOP ) )	return true;
#endif // LEM_ADD_LUCKYITEM
	
	return false;
}

// ��ȯ �ŷ����� ������ ǰ��
bool IsTradeBan(ITEM* pItem)
{
#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// ������ �ŷ� ���ɿ��� ������ ��� [lem_2010.8.19]
	int nJapanResult = IsItemSet_FromJapan( pItem, eITEM_TRADE );
	if( nJapanResult == 1 )			return true;
	else if( nJapanResult == 0 )	return false;
#endif	// LEM_FIX_ITEMSET_FROMJAPAN [lem_2010.8.19]

#ifdef PBG_MOD_PREMIUMITEM_TRADE
	// �Ϻ� �����̾� ������ IsPartChargeItem(pItem)�Լ����� ���Ե� �������߿�
	// �ŷ��� Ǯ�� �������� ����ó��.IsPartChargeItem(pItem)�ȿ��� �����ϸ� ���� Ǯ��.
	// ���� �ɷ�����,�� �ؿ� �����۰��� �������� �����ۺ� ����ó��
#if defined LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION || defined PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE
	// ���� not defined�� �ݴ� �Ǵ� ����( ��ȹ�� ��� �ٲ�� �� ��.��;;;;;; )
	if( (!pItem->bPeriodItem) && ( 
#if !defined PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE || defined PBG_MOD_PREMIUMITEM_TRADE_0118
		// ��� ���� ������� ���ΰŷ� �����ϵ��� ��ȹ����..(10.01.18)
//#ifndef _BLUE_SERVER						// ���� �Ұ���
		pItem->Type == ITEM_POTION+96 ||	// ī��������
		pItem->Type == ITEM_POTION+54 ||	// ī����ī��
#ifdef PBG_MOD_PREMIUMITEM_TRADE_0118
		pItem->Type == ITEM_POTION+53 ||	// ����Ǻ���
#endif //PBG_MOD_PREMIUMITEM_TRADE_0118
//#endif //_BLUE_SERVER
#endif //!defined PBG_MOD_PREMIUMITEM_TRADE_ENDURANCE || defined PBG_MOD_PREMIUMITEM_TRADE_0118
		pItem->Type == ITEM_HELPER+64		// ����
		|| pItem->Type == ITEM_HELPER+65	// ��ȣ����
		|| pItem->Type == ITEM_HELPER+80	// �Ҵ���
		|| pItem->Type == ITEM_HELPER+76	// �Ҵ����Ź���
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type) && pItem->Durability == 255)	// �������϶� �Ǹ� ���� 
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (pItem->Type==ITEM_HELPER+20 && ((pItem->Level >> 3) & 15)==0) 			// �������� ����
		) )
	{
		return false;
	}		
#endif //LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION
#ifndef LDK_MOD_TRADEBAN_ITEMLOCK_AGAIN // �Ϻ� ���� �������� Ʈ���̵� ���� �Ұ��� ����(���̷������� ��ó���� �ؾߵǳ�....)(09.10.29)
	if(pItem->Type == ITEM_POTION+96		// ī��������
		|| pItem->Type == ITEM_POTION+54	// ī����ī��
		|| pItem->Type == ITEM_HELPER+64	// ����
		|| pItem->Type == ITEM_HELPER+65	// ��ȣ����
		|| pItem->Type == ITEM_HELPER+80	// �Ҵ���
		|| pItem->Type == ITEM_HELPER+76	// �Ҵ����Ź���
		)
	{
		return false;
	}		
#endif //LDK_MOD_TRADEBAN_ITEMLOCK_AGAIN
#endif //PBG_MOD_PREMIUMITEM_TRADE

// �Ϻ��� ����Ʈ �ذ����� ���Ź��� ��ȹ���濡 ���� ���� ���� (2010.01.21)
// (���� ������, ������ �ŷ�, â����, ���λ��� �Ұ���->����)
	if(
		pItem->Type == ITEM_HELPER+38		// ������ �Ҵ�Ʈ
#ifndef LJH_MOD_ELITE_SKELETON_WARRIOR_CHANGE_RING_SETTING
		|| pItem->Type == ITEM_HELPER+39	// ����Ʈ �ذ����� ���Ź���
#endif //LJH_MOD_ELITE_SKELETON_WARRIOR_CHANGE_RING_SETTING
		|| (pItem->Type == ITEM_POTION+21 && ((pItem->Level>>3)&15) != 3)		// ������ ǥ��
		|| ( pItem->Type >= ITEM_POTION+23 && pItem->Type <= ITEM_POTION+26 )   //  ����Ʈ ������
		|| pItem->Type == ITEM_HELPER+19 
		|| (pItem->Type == ITEM_POTION+11 && ((pItem->Level>>3)&0x0F) == 13)
#ifdef CSK_LUCKY_SEAL
		|| (pItem->Type >= ITEM_HELPER+43 && pItem->Type <= ITEM_HELPER+45)
#endif //CSK_LUCKY_SEAL
		|| (pItem->Type == ITEM_HELPER+20 && ((pItem->Level>>3)&15) != 0)
		|| pItem->Type == ITEM_POTION+64	// ����
		|| pItem->Type == ITEM_POTION+65	// ����������Ʈ�� �Ҳ�
		|| pItem->Type == ITEM_POTION+66	// �︶�̳��� ��
		|| pItem->Type == ITEM_POTION+67	// ����Ǻһ����� ����
		|| pItem->Type == ITEM_POTION+68	// �ɿ��Ǵ�����
#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
		|| IsPartChargeItem(pItem)
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
#ifdef PBG_ADD_CHARACTERCARD
		|| pItem->Type == ITEM_HELPER+97	// ���˻� ĳ���� ī��
		|| pItem->Type == ITEM_HELPER+98	// ��ũ�ε� ĳ���� ī��
		|| pItem->Type == ITEM_POTION+91	// ��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		|| pItem->Type == ITEM_HELPER+99	// ĳ���� ���� ����
#endif //PBG_ADD_CHARACTERSLOT
#ifndef KJH_MOD_CAN_TRADE_PANDA_PET		// ���� �ؿܿ� define
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80	// �Ҵ���
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76	//�Ҵ�����
#endif //PJH_ADD_PANDA_CHANGERING
#endif // KJH_MOD_CAN_TRADE_PANDA_PET	// ���� �ؿܿ� define
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifndef PBG_MOD_SECRETITEM
		// �����ϵ��� ����
#ifdef PBG_ADD_SECRETITEM
		//Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
		|| (pItem->Type >= ITEM_HELPER+117 && pItem->Type <= ITEM_HELPER+120)
#endif //PBG_ADD_SECRETITEM
#endif //PBG_MOD_SECRETITEM
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| (pItem->Type >= ITEM_POTION+151 && pItem->Type <= ITEM_POTION+156)	// �ð��� ����Ʈ ������
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| g_pMyInventory->IsInvenItem(pItem->Type)
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		)
	{
		return true;
	}

	if( pItem->Type == ITEM_POTION+52)		// GM ��������: GM�� �ŷ� ����
	{
		if( g_isCharacterBuff((&Hero->Object), eBuff_GMEffect) ||	
			(Hero->CtlCode == CTLCODE_20OPERATOR) || (Hero->CtlCode == CTLCODE_08OPERATOR) )
			return false;
		else
			return true;
	}
#ifdef LEM_ADD_LUCKYITEM
	if( Check_ItemAction( pItem, eITEM_TRADE ) )	return true;
#endif // LEM_ADD_LUCKYITEM

	return false;
}

// ����â������ ���� ������ ǰ��
bool IsStoreBan(ITEM* pItem)
{
#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// â������ ���ɿ��� ������ ��� [lem_2010.8.19]
	int nJapanResult = IsItemSet_FromJapan( pItem, eITEM_STORE );
	if( nJapanResult == 1 )			return true;
	else if( nJapanResult == 0 )	return false;
#endif	// LEM_FIX_ITEMSET_FROMJAPAN [lem_2010.8.19]

	if(( pItem->Type >= ITEM_POTION+23 && pItem->Type <= ITEM_POTION+26 )   //  ����Ʈ ������
		|| (pItem->Type == ITEM_POTION+21 && ((pItem->Level>>3)&15) != 3)		// ������ ǥ��
		|| pItem->Type == ITEM_HELPER+19 
		|| (pItem->Type == ITEM_POTION+11 && ((pItem->Level>>3)&0x0F) == 13)
#ifdef CSK_LUCKY_SEAL
		|| (pItem->Type >= ITEM_HELPER+43 && pItem->Type <= ITEM_HELPER+45)
#endif //CSK_LUCKY_SEAL
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		|| pItem->Type == ITEM_HELPER+93	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		|| pItem->Type == ITEM_HELPER+94	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
		|| (pItem->Type == ITEM_HELPER+20 && ((pItem->Level>>3)&15) != 0)
		|| pItem->Type == ITEM_POTION+65	// ����������Ʈ�� �Ҳ�
		|| pItem->Type == ITEM_POTION+66	// �︶�̳��� ��
		|| pItem->Type == ITEM_POTION+67	// ����Ǻһ����� ����
		|| pItem->Type == ITEM_POTION+68	// �ɿ��Ǵ�����
#ifdef YDG_FIX_USED_PORTAL_CHARM_STORE_BAN
#ifdef YDG_ADD_CS5_PORTAL_CHARM
		|| (pItem->Type == ITEM_HELPER+70 && pItem->Durability == 1)	// ��� ������ �̵��� ����
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#endif	// YDG_FIX_USED_PORTAL_CHARM_STORE_BAN
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| (pItem->Type >= ITEM_POTION+151 && pItem->Type <= ITEM_POTION+156)	// �ð��� ����Ʈ ������
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef KJH_ADD_PERIOD_ITEM_SYSTEM
		|| (pItem->bPeriodItem == true)
#endif // KJH_ADD_PERIOD_ITEM_SYSTEM
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type) && pItem->Durability == 254)		// �κ��������� �Ϲݾ��������� ������ ���(����) �����ÿ��� â���� �Ұ� 
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		)
	{
		return true;
	}
#ifdef LEM_ADD_LUCKYITEM
	if( Check_ItemAction( pItem, eITEM_STORE ) )	return true;
#endif // LEM_ADD_LUCKYITEM

	return false;
}
//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.10]-
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �׼� ���� ���� ( ���λ���/ â��/ �ŷ�/ ������/ �Ǹ� )
sItemAct Set_ItemActOption( int _nIndex, int _nOption )
{
	sItemAct	sItem;
	// eITEM_PERSONALSHOP = ���λ���, eITEM_STORE = â��, eITEM_TRADE = �ŷ�, eITEM_DROP = ������, eITEM_SELL = �Ǹ�, eITEM_REPAIR = ����
	int	nItemOption[][eITEM_END]	= { 0, 1, 1, 0, 0, 0,
										0, 0, 0, 0, 1, 0,
		-1 };
	
	
	sItem.s_nItemIndex	= _nIndex;
	
	for( int i=0; i< eITEM_END; i++ )
	{
		sItem.s_bType[i] = nItemOption[_nOption][i];
	}
	return sItem;
}

//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.10]-
bool Check_ItemAction( ITEM* _pItem, ITEMSETOPTION _eAction, bool _bType )
{
	std::vector<sItemAct>			sItem;
	std::vector<sItemAct>::iterator li;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int		nMaxClass	= 11;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int		i			= 0;
	
	for( i=0; i<12; i++ )	sItem.push_back( Set_ItemActOption( ITEM_HELPER+135 +i, 0 ) );		// ��Ű������ ��ȯ Ƽ�� [lem_2010.9.8]
	for( i=0; i< 2; i++ )	sItem.push_back( Set_ItemActOption( ITEM_POTION+160 +i, 0 ) );		// ����� ����, ������ ���� [lem_2010.9.8]
	for( i=0; i<12; i++ )
	{
		sItem.push_back( Set_ItemActOption( ITEM_ARMOR+62 +i, 1 ) );
		sItem.push_back( Set_ItemActOption( ITEM_HELM+62 +i, 1 ) );
		sItem.push_back( Set_ItemActOption( ITEM_BOOTS+62 +i, 1 ) );
		sItem.push_back( Set_ItemActOption( ITEM_GLOVES+62 +i, 1 ) );
		sItem.push_back( Set_ItemActOption( ITEM_PANTS+62 +i, 1 ) );
	}
	
	for( li = sItem.begin(); li != sItem.end(); li++ )
	{
		if( li->s_nItemIndex == _pItem->Type )	
		{
			_bType = (li->s_bType[_eAction])^ (!_bType);
			return _bType;
		}
	}
	
	// ��ϵ��� ���� �������� ����.
	return false;
}

//----------------------------------------------------------------------------------------
// Function: ��Ű������ üũ�� �Ѵ�.
// Input   : ������ ������
// Output  : ��Ű������ TRUE, �Ϲ��� FALSE
//------------------------------------------------------------------------[lem_2010.9.7]-
bool Check_LuckyItem( int _nIndex, int _nType )
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int		nItemTab		= int( (_nIndex+_nType)/ 512.0f);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int		nItemTabIndex	= (_nIndex + _nType)% 512;

	if( _nIndex < ITEM_HELM || _nIndex > ITEM_WING )	return false;
	if( nItemTabIndex >= 62 && nItemTabIndex <= 72 )		return true;

	return false;
}
#endif // LEM_ADD_LUCKYITEM

#ifdef KJH_FIX_SELL_LUCKYITEM
bool IsLuckySetItem( int iType )
{
	int iItemIndex = iType%MAX_ITEM_INDEX;
	
#ifdef LEM_FIX_SELL_LUCKYITEM_BOOTS_POPUP
	if( (iType >= ITEM_HELM && iType <= ITEM_WING)
#else // LEM_FIX_SELL_LUCKYITEM_BOOTS_POPUP
	if( (iType >= ITEM_HELM && iType <= ITEM_BOOTS)
#endif // LEM_FIX_SELL_LUCKYITEM_BOOTS_POPUP
		&& (iItemIndex >= 62 && iItemIndex <= 72 ) )
	{
		return true;
	}
	
	return false;
}
#endif // KJH_FIX_SELL_LUCKYITEM

//----------------------------------------------------------------------------------------
// Function: �Ϻ����� ī���� ī�带 ���� ���������� ĳ������ �Ϲ������� �����ϰ� �ִ� ������.
// Input   :  ITEM* pItem 
// Output  : ����� �� ���ٸ� FALSE, ��밡�� TRUE
//------------------------------------------------------------------------[lem_2010.8.19]-
#ifdef	LEM_FIX_ITEMSET_FROMJAPAN	// IsItemSet_FromJapan �Լ�[lem_2010.8.19]
int IsItemSet_FromJapan( ITEM* _pItem, int _nType )
{
	int	bEnAble		= 1;
	int	nItem		= -1;
	int nList[9]	= { ITEM_POTION+ 96,	// 0: ī���� ���պ���
						ITEM_HELPER+ 64,	// 1: ���� ��
						ITEM_HELPER+ 65,	// 2: ��ȣ���� ��
						ITEM_HELPER+ 80,	// 3: �Ҵ� ��
						ITEM_HELPER+ 76,	// 4: �Ҵ� ���Ź���
						ITEM_HELPER+122,	// 5: ���̷��� ���Ź���
						ITEM_HELPER+123,	// 6: ���̷��� ��
						ITEM_HELPER+106,	// 7: ������ ��
						ITEM_HELPER+107 };	// 8: ġ������ �������� ����


	for( int i=0; i<10; i++ )
	{
		if( nList[i] != _pItem->Type )	continue;
		nItem = i;
		break;
	}
	if( nItem < 0 )		return -1;

	switch( _nType )
	{
		// ���λ���
		case eITEM_PERSONALSHOP:
			if( nItem == 3 || nItem == 4 )	bEnAble	= 0;
		break;
		// â���̿�
		case eITEM_STORE:
			bEnAble	= 0;
		break;
		// �ŷ�
		case eITEM_TRADE:
			if( nItem == 3 || nItem == 4 )	bEnAble	= 0;
		break;
		// ������
		case eITEM_DROP:
			if( nItem == 3 || nItem == 4 )	bEnAble	= 0;
		break;
		// NPC�Ǹ�
		case eITEM_SELL:
			if( nItem == 3 || nItem == 4 )	bEnAble	= 0;
		break;
	}

	return bEnAble;
}
#endif

// ������ ���� ������ ǰ��
bool IsDropBan(ITEM* pItem)
{
#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// ������ ���ɿ��� ������ ��� (2010.8.19)
	int nJapanResult = IsItemSet_FromJapan( pItem, eITEM_DROP );
	if( nJapanResult == 1 )			return true;
	else if( nJapanResult == 0 )	return false;
#endif // LEM_FIX_ITEMSET_FROMJAPAN

#ifdef LDK_MOD_PREMIUMITEM_DROP
	// * ��,���� ���ڿ� ��,���� ��� ���� ��� �����Ⱑ ������ ��ȹ ��û���� ���� �Ͽ����ϴ�.
	// �Ϻ� �����̾� ������ IsPartChargeItem(pItem)�Լ����� ���Ե� �������߿�
	// ������ Ǯ�� �������� ����ó��.IsPartChargeItem(pItem)�ȿ��� �����ϸ� ���� Ǯ��.
	// ���� �ɷ�����,�� �ؿ� �����۰��� �������� �����ۺ� ����ó��

#ifdef LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION
	// �Ⱓ�� �������� �ƴҰ�� �Ϻ� ������ ���� ����( ��ȹ�� ��� �ٲ�� �� ��.��;;;;;; )
	if( (!pItem->bPeriodItem) &&
		( pItem->Type == ITEM_POTION+96		// ī��������
		|| pItem->Type == ITEM_POTION+54	// ī����ī��
		|| pItem->Type == ITEM_HELPER+64	// ����
		|| pItem->Type == ITEM_HELPER+65	// ��ȣ����
		|| pItem->Type == ITEM_HELPER+80	// �Ҵ���
		|| pItem->Type == ITEM_HELPER+76	// �Ҵ����Ź���
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
		|| (pItem->Type==ITEM_HELPER+20 && ((pItem->Level >> 3) & 15)==0) 			// �������� ����
		) )
	{
		return false;
	}		
#endif //LDK_MOD_ITEM_DROP_TRADE_SHOP_EXCEPTION

	if( true == false
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
		|| pItem->Type == ITEM_POTION+123
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
		|| pItem->Type == ITEM_POTION+124
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
		)
	{
		return false;
	}
#endif //LDK_MOD_PREMIUMITEM_DROP

	if (( pItem->Type >= ITEM_POTION+23 && pItem->Type <= ITEM_POTION+26 )	//  ����Ʈ ������
	//���� 3�� ü������ ����Ʈ ���� �����۵��� �������� ó��.(��Ƽ���� ���� �� �����Ƿ�)
		|| (pItem->Type >= ITEM_POTION+65 && pItem->Type <= ITEM_POTION+68)	// ����������Ʈ�� �Ҳ�, �︶�̳��� ��, ����Ǻһ����� ����, �ɿ��Ǵ�����
#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
		|| IsPartChargeItem(pItem)
#ifdef PBG_FIX_CHARM_MIX_ITEM_WING
		|| ((pItem->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN)		//���� ������
			&& (pItem->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END))
#endif //PBG_FIX_CHARM_MIX_ITEM_WING
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
#ifdef PBG_ADD_CHARACTERCARD
		|| pItem->Type == ITEM_HELPER+97	//���˻� ĳ���� ī��
		|| pItem->Type == ITEM_HELPER+98	//��ũ�ε� ĳ���� ī��
		|| pItem->Type == ITEM_POTION+91	//��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		|| pItem->Type == ITEM_HELPER+99	//ĳ���� ���� ����
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80	//ĳ���� ���� ����
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76	//�Ҵ�����
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef PBG_ADD_SECRETITEM
		//Ȱ���� ���(���ϱ�/�ϱ�/�߱�/���)
		|| (pItem->Type >= ITEM_HELPER+117 && pItem->Type <= ITEM_HELPER+120)
#endif //PBG_ADD_SECRETITEM
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST			// �ΰ��Ә� ������ - ���ε� �ݻ�����
		|| pItem->Type == ITEM_POTION+121
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// �ΰ��Ә� ������ - ���ε� ��������
		|| pItem->Type == ITEM_POTION+122
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifndef PBG_FIX_DROPBAN_GENS

#ifndef LEM_FIX_JP0711_JEWELBOX_DROPFREE
#ifdef PBG_ADD_GENSRANKING
		|| (pItem->Type>=ITEM_POTION+141 && pItem->Type<=ITEM_POTION+144)		// ������
#endif //PBG_ADD_GENSRANKING
#endif // LEM_FIX_JP0711_JEWELBOX_DROPFREE

#endif //PBG_FIX_DROPBAN_GENS
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| (pItem->Type>=ITEM_POTION+151 && pItem->Type<=ITEM_POTION+156)	// �ð��� ����Ʈ ������
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| g_pMyInventory->IsInvenItem(pItem->Type)
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		)
	{
		return true;
	}
#ifdef LEM_ADD_LUCKYITEM
	if( Check_ItemAction( pItem, eITEM_DROP ) )	return true;
#endif // LEM_ADD_LUCKYITEM
	
	return false;
}

// �����Ǹ� ���� ������ ǰ�� (������ ��ũ��Ʈ�� ���� �۾� ���� - ������)
bool IsSellingBan(ITEM* pItem)
{
	int Level = (pItem->Level>>3)&15;

#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// �����Ǹ� ���ɿ��� ������ ��� [lem_2010.8.19]
	int nJapanResult = IsItemSet_FromJapan( pItem, eITEM_SELL );
	if( nJapanResult == 1 )			return true;
	else if( nJapanResult == 0 )	return false;
#endif


#ifdef LDK_MOD_PREMIUMITEM_SELL
	// �Ϻ� �����̾� ������ IsPartChargeItem(pItem)�Լ����� ���Ե� �������߿�
	// �ǸŰ��� �ϵ��� ����ó��.IsPartChargeItem(pItem)�ȿ��� �����ϸ� ���� Ǯ��.
	// ���� �ɷ�����,�� �ؿ� �����۰��� �������� �����ۺ� ����ó��
	if( true == false
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
		|| pItem->Type ==ITEM_POTION+112
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
		|| pItem->Type ==ITEM_POTION+113
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
		|| pItem->Type == ITEM_POTION+121
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST	// ���ε� ��������
		|| pItem->Type == ITEM_POTION+122
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST			// �ݻ�����
		|| pItem->Type == ITEM_POTION+123
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST			// ��������
		|| pItem->Type == ITEM_POTION+124
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		|| pItem->Type == ITEM_WING+130
		|| pItem->Type == ITEM_WING+131
		|| pItem->Type == ITEM_WING+132
		|| pItem->Type == ITEM_WING+133
		|| pItem->Type == ITEM_WING+134
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| pItem->Type == ITEM_WING+135
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80  //�����
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76  //������Ź���
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_PC4_GUARDIAN
		|| pItem->Type == ITEM_HELPER+64  //���� ����
		|| pItem->Type == ITEM_HELPER+65  //���� ��ȣ����
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
		|| pItem->Type ==ITEM_HELPER+109
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
		|| pItem->Type ==ITEM_HELPER+110
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ	// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
		|| pItem->Type ==ITEM_HELPER+111
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST	// �ű� �ڼ���(�����)��	// MODEL_HELPER+112
		|| pItem->Type ==ITEM_HELPER+112
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY	// �ű� ���(������) �����	// MODEL_HELPER+113
		|| pItem->Type ==ITEM_HELPER+113
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
		|| pItem->Type ==ITEM_HELPER+114
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE // �ű� �����̾�(���) �����// MODEL_HELPER+115
		|| pItem->Type ==ITEM_HELPER+115
#endif //LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type) && pItem->Durability != 254)	// ���������� �κ������۸� �ǸŰ���
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef KJH_FIX_BTS295_DONT_EXPIRED_WIZARD_RING_RENDER_SELL_PRICE
		|| ((pItem->Type==ITEM_HELPER+20)&&(Level == 0))	// �������� ����
#endif // KJH_FIX_BTS295_DONT_EXPIRED_WIZARD_RING_RENDER_SELL_PRICE
#ifdef KJH_FIX_SELL_EXPIRED_UNICON_PET
		|| (pItem->Type == ITEM_HELPER+106)			// ������ ��
#endif // KJH_FIX_SELL_EXPIRED_UNICON_PET
#ifdef KJH_FIX_SELL_EXPIRED_CRITICAL_WIZARD_RING
		|| (pItem->Type == ITEM_HELPER+107)			// ġ������ �������� ����
#endif // KJH_FIX_SELL_EXPIRED_CRITICAL_WIZARD_RING
		)
	{
#ifdef LDK_FIX_PERIODITEM_SELL_CHECK
		if(true == pItem->bPeriodItem && true == pItem->bExpiredPeriod)
		{
			return false;		// �ȼ� ����
		}
#else //LDK_FIX_PERIODITEM_SELL_CHECK
		return false;
#endif //LDK_FIX_PERIODITEM_SELL_CHECK
	}
#endif //LDK_MOD_PREMIUMITEM_SELL
	
	if(
		pItem->Type==ITEM_POTION+11                                  //  ����� ���ڴ� �ȼ� ����.
#ifndef BLOODCASTLE_2ND_PATCH
		|| ( pItem->Type==ITEM_POTION+21 && Level==1 )                 //  ������ �������� �ȼ� ����.
#endif // BLOODCASTLE_2ND_PATCH
#ifdef FRIEND_EVENT
#ifndef FRIENDLYSTONE_EXCHANGE_ZEN
		|| ( pItem->Type==ITEM_POTION+21 && Level==2 )                 //  ������ ���� �������� �ȼ� ����.
#endif // FRIENDLYSTONE_EXCHANGE_ZEN
		|| (pItem->Type==ITEM_HELPER+20 && (Level==1 || Level==2) )    //  �������� ���� �ø���.
#endif // FRIEND_EVENT
#ifdef KJH_FIX_BTS295_DONT_EXPIRED_WIZARD_RING_RENDER_SELL_PRICE
		|| ((pItem->bPeriodItem==true)&&(pItem->bExpiredPeriod==false)&&(pItem->Type==ITEM_HELPER+20)&&(Level==0))    //  �Ⱓ�� ������ ���� �������� ����
		|| (pItem->Type==ITEM_HELPER+20 && (Level==1 || Level==2) )    //  �������� ���� �ø���.
#endif // KJH_FIX_BTS295_DONT_EXPIRED_WIZARD_RING_RENDER_SELL_PRICE
		|| pItem->Type == ITEM_HELPER+19			// ��õ���� ���� ���� (��¥)�� �� �� ����.
		|| (pItem->Type==ITEM_POTION+20 && Level >= 1 && Level <= 5)     //  �ִϹ����� �ڽ�
#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
		|| IsPartChargeItem(pItem)
#ifdef PBG_FIX_CHARM_MIX_ITEM_WING
		|| ((pItem->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN)		//���� ������
			&& (pItem->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END))
#endif //PBG_FIX_CHARM_MIX_ITEM_WING
#ifdef PBG_MOD_PANDAPETRING_NOTSELLING
		|| pItem->Type == ITEM_HELPER+80  //�����
		|| pItem->Type == ITEM_HELPER+76  //������Ź���
#endif //PBG_MOD_PANDAPETRING_NOTSELLING
#ifdef YDG_MOD_SKELETON_NOTSELLING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif // YDG_MOD_SKELETON_NOTSELLING
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| (g_pMyInventory->IsInvenItem(pItem->Type))	// ���������� �κ������۸� �ǸŰ���
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
#ifdef PBG_MOD_SECRETITEM
		|| (pItem->Type >= ITEM_HELPER+117 && pItem->Type <= ITEM_HELPER+120) // Ȱ�� ������
#endif //PBG_MOD_SECRETITEM
#ifdef KJH_FIX_SELL_EXPIRED_UNICON_PET
		|| (pItem->Type == ITEM_HELPER+106)			// ������ ��
#endif // KJH_FIX_SELL_EXPIRED_UNICON_PET
#ifdef KJH_FIX_SELL_EXPIRED_CRITICAL_WIZARD_RING
		|| (pItem->Type == ITEM_HELPER+107)			// ġ������ �������� ����
#endif // KJH_FIX_SELL_EXPIRED_CRITICAL_WIZARD_RING
#endif //#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| pItem->Type == ITEM_POTION+151	// 1���� �Ƿڼ�
		|| pItem->Type == ITEM_POTION+152	// 1���� �Ƿ� �Ϸ� Ȯ�μ�
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef KJH_FIX_SELL_LUCKYITEM
		|| ( (IsLuckySetItem(pItem->Type) == true ) && (pItem->Durability > 0) )		// ��Ű �������� �������� �������� �ȼ� ����.
#endif // KJH_FIX_SELL_LUCKYITEM
		)
	{
		return true;		// �ȼ� ����
	}
#ifndef KJH_FIX_SELL_LUCKYITEM			// #ifndef
#ifdef LEM_ADD_LUCKYITEM
	if( Check_ItemAction( pItem, eITEM_SELL ) )	return true;
#endif // LEM_ADD_LUCKYITEM
#endif // KJH_FIX_SELL_LUCKYITEM

	return false;			// �ȼ� ����
}



bool IsRepairBan(ITEM* pItem)
{
	if(g_ChangeRingMgr->CheckRepair(pItem->Type) == true)
	{
		return true;
	}
#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC) // ������� ������
	if( IsPartChargeItem(pItem) == true
#ifdef PBG_FIX_CHARM_MIX_ITEM_WING
		|| ((pItem->Type >= ITEM_TYPE_CHARM_MIXWING+EWS_BEGIN)		//���� ������
			&& (pItem->Type <= ITEM_TYPE_CHARM_MIXWING+EWS_END))
#endif //PBG_FIX_CHARM_MIX_ITEM_WING
		)
	{
		return true;
	}
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)

	if(
		(pItem->Type >= ITEM_POTION+55 && pItem->Type <= ITEM_POTION+57)	// ȥ���� ����
		|| pItem->Type == MODEL_HELPER+43		// ��������� 
		|| pItem->Type == MODEL_HELPER+44		// ǳ��������
		|| pItem->Type == MODEL_HELPER+45		// ����������
#ifdef KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
		|| (pItem->Type >= ITEM_HELPER && pItem->Type <= ITEM_HELPER+3)		// ��ȣõ��, ��ź, ���ϸ���, ����Ʈ
#else // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
		|| (pItem->Type >= ITEM_HELPER && pItem->Type <= ITEM_HELPER+4)		// ��ȣõ��, ��ź, ���ϸ���, ����Ʈ, ��ũȣ���� ��
#endif // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET
		|| pItem->Type == ITEM_BOW+7		// ���ÿ�ȭ��
		|| pItem->Type == ITEM_BOW+15		// ȭ��
		|| pItem->Type >= ITEM_POTION		// ����index ����
		|| (pItem->Type >= ITEM_WING+7 && pItem->Type <= ITEM_WING+19)		// ������
		|| (pItem->Type >= ITEM_HELPER+14 && pItem->Type <= ITEM_HELPER+19)	// ��ũ�Ǳ���, ����, ��õ���Ǽ�, ���庻, �������, ��õ�������빫��
		|| pItem->Type == ITEM_POTION+21	// ����
#ifdef MYSTERY_BEAD
		|| pItem->Type == ITEM_WING+26		// �ź��� ����
#endif // MYSTERY_BEAD	
#ifndef KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET					// #ifndef
		|| pItem->Type == ITEM_HELPER+4		// ��ũȣ���� ��
		|| pItem->Type == ITEM_HELPER+5		// ��ũ���Ǹ��� ��
#endif // KJH_ADD_INVENTORY_REPAIR_DARKLOAD_PET					// #ifndef
		|| pItem->Type == ITEM_HELPER+38	// �������Ҵ�Ʈ
#ifdef LDK_ADD_RUDOLPH_PET
		|| pItem->Type == ITEM_HELPER+67	//ũ�������� �絹��
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
		|| pItem->Type == ITEM_HELPER+80	//�Ҵ���
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
		|| pItem->Type == ITEM_HELPER+76	//�Ҵ�����
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		|| pItem->Type == ITEM_HELPER+122	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		|| pItem->Type == ITEM_HELPER+123	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
		|| pItem->Type == ITEM_HELPER+106	//������
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef CSK_EVENT_CHERRYBLOSSOM
		|| pItem->Type == ITEM_POTION+84  // ���ɻ���
		|| pItem->Type == ITEM_POTION+85  // ���ɼ�
		|| pItem->Type == ITEM_POTION+86  // ���ɰ��
		|| pItem->Type == ITEM_POTION+87  // ������
		|| pItem->Type == ITEM_POTION+88  // ��� ����
		|| pItem->Type == ITEM_POTION+89  // ������ ����
		|| pItem->Type == ITEM_POTION+90  // ����� ����
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY
		|| g_pMyInventory->IsInvenItem(pItem->Type)
#endif //LJH_ADD_SYSTEM_OF_EQUIPPING_ITEM_FROM_INVENTORY

//------------------------------------------------------------------------------
#ifdef LDK_FIX_USING_ISREPAIRBAN_FUNCTION
		// ������ �����ִ� �κ� �߰���
		// �Լ��� Ȱ���սô�...
#ifdef DARK_WOLF
		 || pItem->Type == ITEM_HELPER+6
#endif// DARK_WOLF
		|| pItem->Type == ITEM_HELPER+7
		|| pItem->Type == ITEM_HELPER+10
		|| pItem->Type == ITEM_HELPER+11
		|| pItem->Type == ITEM_HELPER+20
		|| pItem->Type == ITEM_HELPER+29
		
		//^ �渱 ������ ���� �Ұ���
		|| pItem->Type == ITEM_HELPER+32
		|| pItem->Type == ITEM_HELPER+33
		|| pItem->Type == ITEM_HELPER+34
		|| pItem->Type == ITEM_HELPER+35
		|| pItem->Type == ITEM_HELPER+36
		|| pItem->Type == ITEM_HELPER+37

		// ���� �η縶�� �� ���� �Ұ���
		|| pItem->Type == ITEM_HELPER+49
		|| pItem->Type == ITEM_HELPER+50
		|| pItem->Type == ITEM_HELPER+51

#ifdef PBG_ADD_SANTAINVITATION		//��Ÿ������ �ʴ���
#ifdef YDG_FIX_SANTA_INVITAION_REPAIR
		|| pItem->Type == ITEM_HELPER+66
#else	// YDG_FIX_SANTA_INVITAION_REPAIR
		|| pItem->Type == MODEL_HELPER+66
#endif	// YDG_FIX_SANTA_INVITAION_REPAIR
#endif //PBG_ADD_SANTAINVITATION

#endif //LDK_FIX_USING_ISREPAIRBAN_FUNCTION
//------------------------------------------------------------------------------

#ifdef LDK_ADD_GAMBLE_RANDOM_ICON	// �׺� ������
		|| pItem->Type == ITEM_HELPER+71
		|| pItem->Type == ITEM_HELPER+72
		|| pItem->Type == ITEM_HELPER+73
		|| pItem->Type == ITEM_HELPER+74
		|| pItem->Type == ITEM_HELPER+75
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
		)
	{
		return true;
	}
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ ���� ���� [lem_2010.9.8]
	if( Check_ItemAction( pItem, eITEM_REPAIR ) )	return true;
#endif // LEM_ADD_LUCKYITEM
	
	return false;
}

bool IsWingItem(ITEM* pItem)
{
	switch(pItem->Type)		// �������� �˻�
	{
	case ITEM_WING:			// ��������
	case ITEM_WING+1:		// õ������
	case ITEM_WING+2:		// ��ź����
	case ITEM_WING+3:		// ���ɳ���
	case ITEM_WING+4:		// ��ȥ����
	case ITEM_WING+5:		// ���ﳯ��
	case ITEM_WING+6:		// ���泯��
	case ITEM_HELPER+30:	// ������ ����
	case ITEM_WING+36:		// ��ǳ�ǳ���
	case ITEM_WING+37:		// �ð��ǳ���
	case ITEM_WING+38:		// ȯ���ǳ���
	case ITEM_WING+39:		// �ĸ��ǳ���
	case ITEM_WING+40:		// �����Ǹ���
#ifdef ADD_ALICE_WINGS_1
	case ITEM_WING+41:		// ����ǳ���
	case ITEM_WING+42:		// �����ǳ���
	case ITEM_WING+43:		// �����ǳ���
#endif	// ADD_ALICE_WINGS_1
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	case ITEM_WING+130:
	case ITEM_WING+131:
	case ITEM_WING+132:
	case ITEM_WING+133:
	case ITEM_WING+134:
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+49:		// �����ǳ���
	case ITEM_WING+50:		// �����ǳ���
	case ITEM_WING+135:		// ���������Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
// ȭ�鿡 ������Ʈ�� ������ �ϴ� �Լ�
// ������Ʈ ��ġ, ���� ����
///////////////////////////////////////////////////////////////////////////////

#ifdef MR0
AUTOOBJ ObjectSelect;
#else
OBJECT ObjectSelect;
#endif //MR0
void RenderObjectScreen(int Type,int ItemLevel,int Option1,int ExtOption,vec3_t Target,int Select,bool PickUp)
{	
   	int Level = (ItemLevel>>3)&15;
    vec3_t Direction,Position;

	VectorSubtract(Target,MousePosition,Direction);
	if(PickUp)
      	VectorMA(MousePosition,0.07f,Direction,Position);
	else
      	VectorMA(MousePosition,0.1f,Direction,Position);

	// ObjectSelect ó�� �κ� 1. �Ϲ� ������
	// =====================================================================================
	// �˷�
	if(Type == MODEL_SWORD+0)	// ũ����
	{
		Position[0] -= 0.02f;
		Position[1] += 0.03f;
		Vector(180.f,270.f,15.f,ObjectSelect.Angle);
	}
	// ���ʷ�
	else if(Type==MODEL_BOW+7 || Type==MODEL_BOW+15 )
	{
    	Vector(0.f,270.f,15.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_SPEAR+0)	// ������
	{
		Position[1] += 0.05f;
		Vector(0.f,90.f,20.f,ObjectSelect.Angle);
	}
	else if( Type==MODEL_BOW+17)    //  ����Ȱ.
	{
    	Vector(0.f,90.f,15.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELM+31)
	{
		Position[1] -= 0.06f;
		Position[0] += 0.03f;
    	Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELM+30)
	{
		Position[1] += 0.07f;
		Position[0] -= 0.03f;
    	Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_ARMOR+30)
	{
		Position[1] += 0.1f;
    	Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_ARMOR+29)
	{
		Position[1] += 0.07f;
    	Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}	
	else if( Type == MODEL_BOW+21)
	{
		Position[1] += 0.12f;
    	Vector(180.f,-90.f,15.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_STAFF+12)
	{
		Position[1] -= 0.1f;
		Position[0] += 0.025f;
    	Vector(180.f,0.f,8.f,ObjectSelect.Angle);
	}
	else if (Type >= MODEL_STAFF+21 && Type <= MODEL_STAFF+29)	// ��ƹ�Ʈ�� ��, ���� ��
	{
    	Vector(0.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_MACE+14)
	{
		Position[1] += 0.1f;
		Position[0] -= 0.01;
    	Vector(180.f,90.f,13.f,ObjectSelect.Angle);
	}	
	//$ ũ���̿��� ������
	else if(Type == MODEL_ARMOR+34)	// ���� ����
	{
		Position[1] += 0.03f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELM+35)	// �渶���� ���
	{
		Position[0] -= 0.02f;
		Position[1] += 0.05f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMOR+35)	// �渶���� ����
	{
		Position[1] += 0.05f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMOR+36)	// ���� ����
	{
		Position[1] -= 0.05f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMOR+37)	// ��ũ�ε� ����
	{
		Position[1] -= 0.05f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	// ���̿÷����� ~ ���ͳ��� ���
	else if (MODEL_HELM+39 <= Type && MODEL_HELM+44 >= Type)
	{
		Position[1] -= 0.05f;
		Vector(-90.f,25.f,0.f,ObjectSelect.Angle);
	}
	// �۷θ�� ~ ���ͳ��� ����
	else if(MODEL_ARMOR+38 <= Type && MODEL_ARMOR+44 >= Type)
	{
		Position[1] -= 0.08f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_SWORD+24)	// ���� ��
	{
		Position[0] -= 0.02f;
		Position[1] += 0.03f;
    	Vector(180.f,90.f,15.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_MACE+15)	// ��ũ�ε� ����
	{
		Position[1] += 0.05f;
    	Vector(180.f,90.f,13.f,ObjectSelect.Angle);
	}
#ifdef ADD_SOCKET_ITEM
	else if(Type == MODEL_BOW+22 || Type == MODEL_BOW+23)	// ���� Ȱ
	{
		Position[0] -= 0.10f;
		Position[1] += 0.08f;
    	Vector(180.f,-90.f,15.f,ObjectSelect.Angle);
	}
#else // ADD_SOCKET_ITEM
	else if( Type == MODEL_BOW+22)	// ���� Ȱ
	{
		Position[1] += 0.12f;
    	Vector(180.f,90.f,15.f,ObjectSelect.Angle);
	}
#endif // ADD_SOCKET_ITEM
	else if(Type == MODEL_STAFF+13)	// �渶���� ������
	{
		Position[0] += 0.02f;
		Position[1] += 0.02f;
		Vector(180.f,90.f,8.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_BOW+20)		//. �����߰�Ȱ
	{
		Vector(180.f,-90.f,15.f,ObjectSelect.Angle);
	}
	else if(Type>=MODEL_BOW+8 && Type<MODEL_BOW+MAX_ITEM_INDEX)
	{
    	Vector(90.f,180.f,20.f,ObjectSelect.Angle);
	}
	else if ( Type==MODEL_SPEAR+10 )
	{
      	Vector(180.f,270.f,20.f,ObjectSelect.Angle);
	}
	else if(Type >= MODEL_SWORD && Type < MODEL_STAFF+MAX_ITEM_INDEX)
	{
		switch (Type)
		{
		case MODEL_STAFF+14:							Position[1] += 0.04f;	break;
		case MODEL_STAFF+17:	Position[0] += 0.02f;	Position[1] += 0.03f;	break;
		case MODEL_STAFF+18:	Position[0] += 0.02f;							break;
		case MODEL_STAFF+19:	Position[0] -= 0.02f;	Position[1] -= 0.02f;	break;
		case MODEL_STAFF+20:	Position[0] += 0.01f;	Position[1] -= 0.01f;	break;
		}

		if(!ItemAttribute[Type-MODEL_ITEM].TwoHand)
		{
      		Vector(180.f,270.f,15.f,ObjectSelect.Angle);
		}
		else
		{
      		Vector(180.f,270.f,25.f,ObjectSelect.Angle);
		}
		// ���Ͼ������߰� [����4]
	}									
	else if(Type>=MODEL_SHIELD && Type<MODEL_SHIELD+MAX_ITEM_INDEX)
	{
		Vector(270.f,270.f,0.f,ObjectSelect.Angle);
	}
    else if(Type==MODEL_HELPER+3)
    {
		Vector(-90.f,-90.f,0.f,ObjectSelect.Angle);
    }
    else if ( Type==MODEL_HELPER+4 )    //  ��ũȣ��.
    {
		Vector(-90.f,-90.f,0.f,ObjectSelect.Angle);
    }
    else if ( Type==MODEL_HELPER+5 )    //  ��ũ���Ǹ�.
    {
		Vector(-90.f,-35.f,0.f,ObjectSelect.Angle);
    }
    else if ( Type==MODEL_HELPER+31 )   //  ��ȥ.
    {
		Vector(-90.f,-90.f,0.f,ObjectSelect.Angle);
    }
    else if ( Type==MODEL_HELPER+30 )   //  ����.    
    {
        Vector ( -90.f, 0.f, 0.f, ObjectSelect.Angle );
    }
	else if ( Type==MODEL_EVENT+16 )    //  ������ �Ҹ�
	{
		Vector ( -90.f, 0.f, 0.f, ObjectSelect.Angle );
	}
    else if ( Type==MODEL_HELPER+16 || Type == MODEL_HELPER+17 )
    {	//. ��õ���Ǽ�, ���庻
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
    }
	else if ( Type==MODEL_HELPER+18 )	//. �������
	{
		Vector(290.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if ( Type==MODEL_EVENT+11 )	//. ����
	{
#ifdef FRIEND_EVENT
        if ( Type==MODEL_EVENT+11 && Level==2 )    //  ������ ��.
        {
    		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
        }
        else
#endif// FRIEND_EVENT
        {
            Vector(-90.f, -20.f, -20.f, ObjectSelect.Angle);
        }
	}
	else if ( Type==MODEL_EVENT+12)		//. ������ ����
	{
		Vector(250.f, 140.f, 0.f, ObjectSelect.Angle);
	}
	else if (Type==MODEL_EVENT+14)		//. ������ ����
	{
		Vector(255.f, 160.f, 0.f, ObjectSelect.Angle);
	}
	else if (Type==MODEL_EVENT+15)		// �������� ����
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
    else if ( Type>=MODEL_HELPER+21 && Type<=MODEL_HELPER+24 )
    {
		Vector(270.f, 160.f, 20.f, ObjectSelect.Angle);
    }
	else if ( Type==MODEL_HELPER+29 )	//. �������
	{
		Vector(290.f,0.f,0.f,ObjectSelect.Angle);
	}
	//^ �渱 ��ġ, ���� ����
	else if(Type == MODEL_HELPER+32)	// ���� ����
	{
		Position[0] += 0.01f;
		Position[1] -= 0.03f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+33)	// ������ ��ȣ
	{
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+34)	// �ͼ��� ����
	{
		Position[0] += 0.01f;
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+35)	// ���Ǹ� ����
	{
		Position[0] += 0.01f;
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+36)	// �η��� ���Ǹ�
	{
		Position[0] += 0.01f;
		Position[1] += 0.05f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+37)	// �渱�� ���Ǹ�
	{
		Position[0] += 0.01f;
		Position[1] += 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#ifdef CSK_PCROOM_ITEM
	else if(Type >= MODEL_POTION+55 && Type <= MODEL_POTION+57
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| Type >= MODEL_POTION+157 && Type <= MODEL_POTION+159
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
	{
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // CSK_PCROOM_ITEM
	else if(Type == MODEL_HELPER+49)
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+50)
	{
		Position[1] -= 0.03f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+51)
	{
		Position[1] -= 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+64
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
			|| Type == MODEL_POTION+153
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
	{
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+52)
	{
		Position[1] += 0.045f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+53)
	{
		Position[1] += 0.04f;
		Vector(270.f, 120.f, 0.f, ObjectSelect.Angle);
	}
// 	else if(Type == MODEL_WING+36)	// ��ǳ�ǳ���(����)
// 	{
// 		Position[1] -= 0.35f;
// 		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
// 	}
	else if(Type == MODEL_WING+37)	// �ð��ǳ���(����)
	{
		Position[1] += 0.05f;
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_WING+38)	// ȯ���ǳ���(����)
	{
		Position[1] += 0.05f;
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_WING+39)	// �ĸ��ǳ���(����)
	{
		Position[1] += 0.08f;
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_WING+40)	// �����Ǹ���(��ũ�ε�)
	{
		Position[1] += 0.05f;
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
#ifdef ADD_ALICE_WINGS_1
	else if(Type == MODEL_WING+42)	// �����ǳ���(��ȯ����)
	{
		Position[1] += 0.05f;
		Vector(270.f,0.f,2.f,ObjectSelect.Angle);
	}
#endif	// ADD_ALICE_WINGS_1
#ifdef CSK_FREE_TICKET
	// ������ ��ġ�� ���� ����
	else if(Type == MODEL_HELPER+46)	// ���������� ���������
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+47)	// ����ĳ�� ���������
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+48)	// Į���� ���������
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);	
	}
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
	// ������ ��ġ�� ���� ����
	else if(Type == MODEL_POTION+54)	// ī����ī��
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
	// ������ ��ġ�� ��������
	else if(Type == MODEL_POTION+58)// ��� ������ Ƽ��( �κ� 1�� )
	{
		Position[1] += 0.07f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+59 || Type == MODEL_POTION+60)
	{
		Position[1] += 0.06f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+61 || Type == MODEL_POTION+62)
	{
		Position[1] += 0.06f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // CSK_RARE_ITEM
#ifdef CSK_LUCKY_CHARM
	else if( Type == MODEL_POTION+53 )// ����� ����
	{
		Position[1] += 0.042f;
		Vector(180.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
#ifdef PBG_FIX_ITEMANGLE
	else if( Type == MODEL_HELPER+43 )
	{
		Position[1] -= 0.027f;
		Position[0] += 0.005f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+44 )
	{
		Position[1] -= 0.03f;
		Position[0] += 0.005f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+45 )
	{
		Position[1] -= 0.02f;
		Position[0] += 0.005f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#else //PBG_FIX_ITEMANGLE
	else if( Type == MODEL_HELPER+43 )// ����� ����
	{
		Position[1] += 0.082f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+44 )
	{
		Position[1] += 0.08f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+45 )
	{
		Position[1] += 0.07f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PBG_FIX_ITEMANGLE
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	else if( Type >= MODEL_POTION+70 && Type <= MODEL_POTION+71 )
	{
		Position[0] += 0.01f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	else if( Type >= MODEL_POTION+72 && Type <= MODEL_POTION+77 )
	{
		Position[1] += 0.08f;
		Vector(0.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
	else if( Type == MODEL_HELPER+59 )
	{
		Position[0] += 0.01f;
		Position[1] += 0.02f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
	else if( Type >= MODEL_HELPER+54 && Type <= MODEL_HELPER+58 )
	{
  		Position[1] -= 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	else if( Type >= MODEL_POTION+78 && Type <= MODEL_POTION+82 )
	{
		Position[1] += 0.01f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	else if( Type == MODEL_HELPER+60 )
	{
		Position[1] -= 0.06f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	else if( Type == MODEL_HELPER+61 )// ȯ���� ��� ���� �����
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
	else if(Type == MODEL_POTION+83)// ��� ������ Ƽ��( �κ� 2�� )
	{
		Position[1] += 0.06f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_RARE_ITEM
#ifdef PSW_CHARACTER_CARD 
	else if(Type == MODEL_POTION+91) // ĳ���� ī��
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
	else if(Type == MODEL_POTION+92) // ī����ī�� ���
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+93) // ī����ī�� ����
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+95) // ī����ī�� �̴�
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
	else if( Type == MODEL_POTION+94 ) // ����Ʈ �߰� ġ�� ����
	{
		Position[0] += 0.01f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
	else if( Type >= MODEL_POTION+84 && Type <= MODEL_POTION+90 )
	{
		if( Type == MODEL_POTION+84 )  // ���ɻ���
		{
			Position[1] += 0.01f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+85 )  // ���ɼ�
		{
			Position[1] -= 0.01f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+86 )  // ���ɰ��
		{
			Position[1] += 0.01f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+87 )  // ������
		{
			Position[1] += 0.01f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+88 )  // ��� ����
		{
			Position[1] += 0.015f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+89 )  // ������ ����
		{
			Position[1] += 0.015f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
		else if( Type == MODEL_POTION+90 )  // ����� ����
		{
			Position[1] += 0.015f;
			Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
		}
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
	else if(Type == MODEL_HELPER+62)
	{
#ifdef PBG_FIX_ITEMANGLE
		Position[0] += 0.01f;
		Position[1] -= 0.03f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
#else //PBG_FIX_ITEMANGLE
		Position[0] += 0.01f;
		Position[1] += 0.08f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
#endif //PBG_FIX_ITEMANGLE
	}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SEALITEM
	else if(Type == MODEL_HELPER+63)
	{
		Position[0] += 0.01f;
		Position[1] += 0.082f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
	else if(Type >= MODEL_POTION+97 && Type <= MODEL_POTION+98)
	{
		Position[1] += 0.09f;
		Vector(0.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	else if( Type == MODEL_POTION+96 ) 
	{
#ifdef PBG_FIX_ITEMANGLE
		Position[1] -= 0.013f;
		Position[0] += 0.003f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
#else //PBG_FIX_ITEMANGLE
		Position[1] += 0.13f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
#endif //PBG_FIX_ITEMANGLE
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
	else if( MODEL_HELPER+64 <= Type && Type <= MODEL_HELPER+65 )
	{
		switch(Type)
		{
		case MODEL_HELPER+64:
			Position[1] -= 0.05f;
			break;
		case MODEL_HELPER+65: 
			Position[1] -= 0.02f;
			break;
		}
		Vector(270.f, -10.f, 0.f, ObjectSelect.Angle);
	}
#endif //LDK_ADD_PC4_GUARDIAN
	else if (Type == MODEL_POTION+65)
	{
		Position[1] += 0.05f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if (Type == MODEL_POTION+66)
	{
		Position[1] += 0.11f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if (Type == MODEL_POTION+67)
	{
		Position[1] += 0.11f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	// ����Ʈ �ذ����� ���Ź��� ���� ����
	else if(Type == MODEL_HELPER+39)	// ����Ʈ �ذ����� ���Ź���
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#ifdef CSK_LUCKY_SEAL
	else if( Type == MODEL_HELPER+43 )
	{
//		Position[1] += 0.082f;
		Position[1] -= 0.03f;
		Vector(90.f, 0.f, 180.f, ObjectSelect.Angle);
	}
 	else if( Type == MODEL_HELPER+44 )
	{
		Position[1] += 0.08f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+45 )
	{
		Position[1] += 0.07f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //CSK_LUCKY_SEAL
	// �ҷ��� �̺�Ʈ ���Ź��� ���� ����
	else if(Type == MODEL_HELPER+40)
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+41)
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_HELPER+51)
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	// GM ���Ź��� ���� ����
	else if(Type == MODEL_HELPER+42)
	{
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type==MODEL_HELPER+38 )
	{
		Position[0] += 0.00f;
		Position[1] += 0.02f;
		Vector( -48-150.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if(Type == MODEL_POTION+41)
	{
		Position[1] += 0.02f;
		Vector(270.f, 90.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type==MODEL_POTION+42 )
	{
		Position[1] += 0.02f;
		Vector(270.f, -10.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type==MODEL_POTION+43 || Type==MODEL_POTION+44 )	// ���ü� �κ��丮 ��ġ ����.
	{
		Position[0] -= 0.04f;
		Position[1] += 0.02f;
		Position[2] += 0.02f;
		Vector( 270.f, -10.f, -45.f, ObjectSelect.Angle );
	}
	else if(Type>=MODEL_HELPER+12 && Type<MODEL_HELPER+MAX_ITEM_INDEX && Type!=MODEL_HELPER+14  && Type!=MODEL_HELPER+15)
	{
		Vector(270.f+90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_POTION+12)//�̹�Ʈ ������
	{
		switch(Level)
		{
		case 0:Vector(180.f,0.f,0.f,ObjectSelect.Angle);break;
		case 1:Vector(270.f,90.f,0.f,ObjectSelect.Angle);break;
		case 2:Vector(90.f,0.f,0.f,ObjectSelect.Angle);break;
		}
	}
	else if(Type==MODEL_EVENT+5)            //  ����. /���� �ָӴ�.
	{
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
#else // SELECTED_LANGUAGE == LANGUAGE_KOREAN
		Vector(270.f,180.f,0.f,ObjectSelect.Angle);
#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN
	}
	else if(Type==MODEL_EVENT+6)            //  ����� ��Ʈ
	{
		Vector(270.f,90.f,0.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_EVENT+7)            //  ����� �ø���
	{
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_POTION+20)          //  ����� ����
	{
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
    else if ( Type==MODEL_POTION+27 )    //  ����� �ݼ�.
    {
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
    }
	else if ( Type == MODEL_POTION+63 )	// ����
	{
		Position[1] += 0.08f;
		Vector(-50.f,-60.f,0.f,ObjectSelect.Angle);
	}
	else if ( Type == MODEL_POTION+52)	// GM ��������
	{
		//Position[1] += 0.08f;
		Vector(270.f,-25.f,0.f,ObjectSelect.Angle);
	}
#ifdef _PVP_MURDERER_HERO_ITEM
    else if ( Type==MODEL_POTION+30 )    // ¡ǥ
    {
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
    }
#endif// _PVP_MURDERER_HERO_ITEM
	else if(Type >= MODEL_ETC+19 && Type <= MODEL_ETC+27)	// ��������
	{
		Position[0] += 0.03f;
		Position[1] += 0.03f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_WING+7)	// ȸ�������� ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.015f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMOR+10)		// ���𰩿�
	{
		Position[1] -= 0.1f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_PANTS+10)		// �������
	{
		Position[1] -= 0.08f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMOR+11)		// ��ũ����
	{
		Position[1] -= 0.1f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_PANTS+11)		// ��ũ����
	{
		Position[1] -= 0.08f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	else if(Type == MODEL_WING+44)	// �ı����ϰ� ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.015f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION

#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	else if(Type == MODEL_WING+46
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
										|| Type==MODEL_WING+45
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
		)	// ȸ�� ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.015f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
    else
	{
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
#ifdef ADD_SEED_SPHERE_ITEM
	
	// if-else if�� 128�� �Ѿ�� ������ ������! �߰��Ҷ� �� �Ʒ��� �߰��ϴ��� �ƴϸ� ������ ���ľ� �� ��
	if(Type >= MODEL_WING+60 && Type <= MODEL_WING+65)	// �õ�
	{
		Vector(10.f,-10.f,10.f,ObjectSelect.Angle);
	}
	else if(Type >= MODEL_WING+70 && Type <= MODEL_WING+74)	// ���Ǿ�
	{
		Vector(0.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type >= MODEL_WING+100 && Type <= MODEL_WING+129)	// �õ彺�Ǿ�
	{
		Vector(0.f,0.f,0.f,ObjectSelect.Angle);
	}
#endif	// ADD_SEED_SPHERE_ITEM

#ifdef LDK_ADD_RUDOLPH_PET //�絹�� �� ... limit �ɸ�.....
	else if( Type == MODEL_HELPER+67 )
	{
		Position[1] -= 0.05f;
		Vector(270.f, 40.f, 0.f, ObjectSelect.Angle);
	}
#endif //LDK_ADD_RUDOLPH_PET
#ifdef YDG_ADD_SKELETON_PET
	else if( Type == MODEL_HELPER+123 )	// ���̷��� ��
	{
		Position[1] -= 0.05f;
		Vector(270.f, 40.f, 0.f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_SKELETON_PET
#ifdef YDG_ADD_HEALING_SCROLL
	else if(Type == MODEL_POTION+140)	// ġ���� ��ũ��
	{
		Position[1] += 0.09f;
		Vector(0.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_HEALING_SCROLL
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	else if(Type >= MODEL_POTION+145 && Type <= MODEL_POTION+150)
	{
		Position[0] += 0.010f;
		Position[1] += 0.040f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	else if (Type == MODEL_POTION+151 || Type == MODEL_POTION+152)	// 1���� �Ƿڼ�, 1���� �Ƿ� �Ϸ� Ȯ�μ�
	{
		Position[0] += 0.02f;
		Position[1] += 0.13f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if (Type == MODEL_POTION+155)	// źŻ�ν��� ����
	{
		Position[1] += 0.120f;
	}
	else if (Type == MODEL_POTION+156)	// ����� �������� ������
	{
		Position[0] += 0.040f;
		Position[1] += 0.110f;
		Vector(180.f, 270.f, 15.f, ObjectSelect.Angle);
	}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ������ ��ġ�� ���� ����
	else if(Type >= MODEL_HELPER+125 && Type <= MODEL_HELPER+127)	//���ð���, �ٸ�ī, �ٸ�ī��7�� ���������
	{
		Position[0] += 0.007f;
		Position[1] -= 0.035f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	else if (Type == MODEL_HELPER+124)	// ����ä�� �����.
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //ASG_ADD_CHARGED_CHANNEL_TICKET
#ifdef PJH_ADD_PANDA_PET 
	else if( Type == MODEL_HELPER+80 )
	{
		Position[1] -= 0.05f;
		Vector(270.f, 40.f, 0.f, ObjectSelect.Angle);
	}
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET	//������
	else if( Type == MODEL_HELPER+106 )
	{
		Position[0] += 0.01f;
		Position[1] -= 0.05f;
		Vector(255.f, 45.f, 0.f, ObjectSelect.Angle);
	}
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	else if( Type == MODEL_HELPER+68 )
	{
		Position[0] += 0.02f;
		Position[1] -= 0.02f;
		Vector(300.f, 10.f, 20.f, ObjectSelect.Angle);
	}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
	else if( Type == MODEL_HELPER+76 )
	{
//		Position[0] += 0.02f;
		Position[1] -= 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	else if( Type == MODEL_HELPER+122 )	// ���̷��� ���Ź���
	{
		Position[0] += 0.01f;
		Position[1] -= 0.035f;
		Vector(290.f, -20.f, 0.f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM	
	else if( Type == MODEL_HELPER+128 )	// ��������
	{
		Position[0] += 0.017f;
		Position[1] -= 0.053f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+129 )	// ��������
	{
		Position[0] += 0.012f;
		Position[1] -= 0.045f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+134 )	// ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.033f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
#endif	//LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	else if( Type == MODEL_HELPER+130 )	// ��ũ��
	{
		Position[0] += 0.007f;
		Position[1] += 0.005f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+131 )	// ������
	{
		Position[0] += 0.017f;
		Position[1] -= 0.053f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+132 )	// ����ũ��
	{
		Position[0] += 0.007f;
		Position[1] += 0.045f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_HELPER+133 )	// ��������
	{
		Position[0] += 0.017f;
		Position[1] -= 0.053f;
		Vector(270.f, -20.f, 0.f, ObjectSelect.Angle);
	}
#endif	//LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	else if( Type == MODEL_HELPER+69 )	// ��Ȱ�� ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.05f;
		Vector(270.f, -30.f, 0.f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	else if( Type == MODEL_HELPER+70 )	// �̵��� ����
	{
		Position[0] += 0.040f;
		Position[1] -= 0.000f;
		Vector(270.f, -0.f, 70.f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef ASG_ADD_CS6_GUARD_CHARM
	else if (Type == MODEL_HELPER+81)	// ��ȣ�Ǻ���
	{
		Position[0] += 0.005f;
		Position[1] += 0.035f;
		Vector(-90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	else if (Type == MODEL_HELPER+82)	// �����ۺ�ȣ����
	{
		Position[0] += 0.005f;
		Position[1] += 0.035f;
		Vector(-90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
	else if (Type == MODEL_HELPER+93)	// ��������帶����
	{
		Position[0] += 0.005f;
		Vector(-90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
	else if (Type == MODEL_HELPER+94)	// ǳ�������帶����
	{
		Position[0] += 0.005f;
		Vector(-90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef PBG_ADD_SANTAINVITATION
	//��Ÿ������ �ʴ���.
	else if( Type == MODEL_HELPER+66 )
	{
		Position[0] += 0.01f;
		Position[1] -= 0.05f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	//����� ����
	else if( Type == MODEL_POTION+100 )
	{
		Position[0] += 0.01f;
		Position[1] -= 0.05f;
		Vector(0.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef YDG_ADD_FIRECRACKER_ITEM
	else if (Type == MODEL_POTION+99)	// ũ�������� ����
	{
		Position[0] += 0.02f;
		Position[1] -= 0.03f;
		//Vector(270.f,0.f,30.f,ObjectSelect.Angle);
		Vector(290.f,-40.f,0.f,ObjectSelect.Angle);
	}
#endif	// YDG_ADD_FIRECRACKER_ITEM
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	else if( Type == MODEL_STAFF+33 )	// �׺� ���� ������
	{
		Position[0] += 0.02f;
		Position[1] -= 0.06f;
		Vector(180.f,90.f,10.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_STAFF+34 )	// �׺� ���� ������(��ȯ�����)
	{
		Position[1] -= 0.05f;
		Vector(180.f,90.f,10.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_SPEAR+11 )	// �׺� ���� ��
	{
		Position[1] += 0.02f;
		Vector(180.f,90.f,15.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_MACE+18 )
	{
		Position[0] -= 0.03f;
		Position[1] += 0.06f;
		Vector(180.f,90.f,2.f,ObjectSelect.Angle);
	}
	else if( Type == MODEL_BOW+24 )
	{
		Position[0] -= 0.07f;
		Position[1] += 0.07f;
    	Vector(180.f,-90.f,15.f,ObjectSelect.Angle);
	}
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	else if(Type == MODEL_WING+47)	// �÷��ӽ�Ʈ����ũ ����
	{
		Position[0] += 0.005f;
		Position[1] -= 0.015f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
	//�׺� ���� ������ �� ��ȣ ���� �ؾߵ�
	else if ( Type==MODEL_HELPER+71 || Type==MODEL_HELPER+72 || Type==MODEL_HELPER+73 || Type==MODEL_HELPER+74 || Type==MODEL_HELPER+75 )
	{
		Position[1] += 0.07f;
      	Vector(270.f,180.f,0.f,ObjectSelect.Angle);
		if(Select != 1)
		{
			ObjectSelect.Angle[1] = WorldTime*0.2f;
		}
	}
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// ���� ���� 100% ���� ����
	else if( Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN
			&& Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END )
	{
		Position[1] -= 0.03f;
		Vector(-90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	else if(Type == MODEL_HELPER+96)		// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
	{
		Position[0] -= 0.001f;
		Position[1] += 0.028f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef PBG_ADD_CHARACTERCARD
	// ���� ��ũ ��ȯ���� ī��
	else if(Type == MODEL_HELPER+97 || Type == MODEL_HELPER+98 || Type == MODEL_POTION+91)
	{
		Position[1] -= 0.04f;
		Position[0] += 0.002f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	else if(Type == MODEL_HELPER+99)
	{
		Position[0] += 0.002f;
		Position[1] += 0.025f;
		Vector(270.0f, 180.0f, 45.0f, ObjectSelect.Angle);
	}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
	//Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
	else if(Type >= MODEL_HELPER+117 && Type <= MODEL_HELPER+120)
	{
		Position[0] += 0.01f;
		Position[1] -= 0.05f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	else if ( Type==MODEL_POTION+110 )	// ������ǥ��
	{
		Position[0] += 0.005f;
		Position[1] -= 0.02f;
	}
	else if ( Type==MODEL_POTION+111 )	// �����Ǹ���
	{
		Position[0] += 0.01f;
		Position[1] -= 0.02f;
	}
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	else if(Type == MODEL_HELPER+107)
	{
		// ġ��������
		Position[0] -= 0.0f;
		Position[1] += 0.0f;
		Vector(90.0f, 225.0f, 45.0f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	else if(Type == MODEL_HELPER+104)
	{
		// AG���� ����
		Position[0] += 0.01f;
		Position[1] -= 0.03f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	else if(Type == MODEL_HELPER+105)
	{
		// SD���� ����
		Position[0] += 0.01f;
		Position[1] -= 0.03f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	else if(Type == MODEL_HELPER+103)
	{
		// ��Ƽ ����ġ ���� ������
		Position[0] += 0.01f;
		Position[1] += 0.01f;
		Vector(0.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	else if(Type == MODEL_POTION+133)
	{
		// ����Ʈ SDȸ�� ����
		Position[0] += 0.01f;
		Position[1] -= 0.0f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	else if( MODEL_POTION+101 <= Type && Type <= MODEL_POTION+109 )
	{
		switch(Type)
		{
		case MODEL_POTION+101: // �ǹ�������
			{
				Position[0] += 0.005f;
				//Position[1] -= 0.02f;
			}break;
		case MODEL_POTION+102: // ���̿��� ��ɼ�
			{
				Position[0] += 0.005f;
				Position[1] += 0.05f;
				Vector(0.0f, 0.0f, 30.0f, ObjectSelect.Angle);
			}break;
		case MODEL_POTION+103: // ��ũ�ι��� ����
		case MODEL_POTION+104: 
		case MODEL_POTION+105: 
		case MODEL_POTION+106: 
		case MODEL_POTION+107: 
		case MODEL_POTION+108: 
			{
				Position[0] += 0.005f;
				Position[1] += 0.05f;
				Vector(0.0f, 0.0f, 30.0f, ObjectSelect.Angle);
			}break;
		case MODEL_POTION+109: // ��ũ�ι���
			{
				Position[0] += 0.005f;
				Position[1] += 0.05f;
				Vector(0.0f, 0.0f, 0.0f, ObjectSelect.Angle);
			}break;
		}
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#if defined(LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST)	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	else if( Type >= MODEL_HELPER+109 && Type <= MODEL_HELPER+112 )	// �����̾�(Ǫ����)��, ���(������)��, ������(��Ȳ)��, �ڼ���(�����)��
	{
		// �ű� �����̾�(Ǫ����)��
		Position[0] += 0.025f;
		Position[1] -= 0.035f;
		Vector(270.0f, 25.0f, 25.0f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
#if defined(LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE)
	else if( Type >= MODEL_HELPER+113 && Type <= MODEL_HELPER+115 )	// ���(������), ���޶���(Ǫ��), �����̾�(���) �����
	{
		// ���(������), ���޶���(Ǫ��), �����̾�(���) �����
		Position[0] += 0.005f;
		Position[1] -= 0.00f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE)	// ���(������), ���޶���(Ǫ��), �����̾�(���) �����
#if defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD)
	else if( Type >= MODEL_POTION+112 && Type <= MODEL_POTION+113 )	// Ű(�ǹ�), Ű(���)
	{
		// Ű(�ǹ�), Ű(���)
 		Position[0] += 0.05f;
 		Position[1] += 0.009f;
		Vector(270.0f, 180.0f, 45.0f, ObjectSelect.Angle);
	}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD)
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
	// �����ȭ
	else if( Type == MODEL_POTION+120 )
	{
		Position[0] += 0.01f;
		Position[1] += 0.05f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
		
	}
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
	else if( MODEL_POTION+134 <= Type && Type <= MODEL_POTION+139 )
	{
		Position[0] += 0.00f;
		Position[1] += 0.05f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	else if( Type == MODEL_HELPER+116 )
	{
#ifdef PBG_FIX_ITEMANGLE
		Position[1] -= 0.03f;
		Position[0] += 0.005f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
#else //PBG_FIX_ITEMANGLE
		Position[1] += 0.08f;
		Vector(90.f, 0.f, 0.f, ObjectSelect.Angle);
#endif //PBG_FIX_ITEMANGLE
	}
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
	else if( Type >= MODEL_POTION+114 && Type <= MODEL_POTION+119 )
	{
		Position[0] += 0.00f;
		Position[1] += 0.06f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
	else if( Type >= MODEL_POTION+126 && Type <= MODEL_POTION+129 )
	{
		Position[0] += 0.00f;
		Position[1] += 0.06f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	else if( Type >= MODEL_POTION+130 && Type <= MODEL_POTION+132 )
	{
		Position[0] += 0.00f;
		Position[1] += 0.06f;
		Vector(270.0f, 0.0f, 0.0f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	else if( Type == MODEL_HELPER+121 )
	{
		Position[1] -= 0.04f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX	// ���� �� �ҿ� ����/�׷���ҿ� ���� // MODEL_PANTS +22 
	else if( Type == MODEL_PANTS +22 || Type == MODEL_PANTS +18 )
	{
		vec3_t		v3Angle;
		VectorCopy(ObjectSelect.Angle, v3Angle);
		
		v3Angle[1] = v3Angle[1] + 10.0f;
		
		VectorCopy(v3Angle, ObjectSelect.Angle);
	}	
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type == MODEL_HELM+59)
	{
		Position[1] += 0.04f;
		Vector(-90.f,25.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_ARMORINVEN_60
		|| Type ==  MODEL_ARMORINVEN_61
		|| Type == MODEL_ARMORINVEN_62)
	{
		Position[0] += 0.01f;
		Position[1] += 0.08f;
		Vector(0.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type == MODEL_SWORD+32)
	{
		Position[0] += 0.005f;
		Position[1] += 0.015f;
		Vector(-90.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type >= MODEL_SWORD+33 && Type <= MODEL_SWORD+34)
	{
		Position[0] += 0.002f;
		Position[1] += 0.02f;
		Vector(0.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_WING+49)
	{
		Position[1] += 0.01f;
		Position[0] += 0.015f;
		Vector ( -90.f, 0.f, 0.f, ObjectSelect.Angle );
	}
	else if(Type==MODEL_WING+50)
	{
		Position[1] += 0.15f;
		Vector(270.f,-10.f,0.f,ObjectSelect.Angle);
	}
	else if(Type >= MODEL_ETC+30 && Type <= MODEL_ETC+36)
	{
		Position[0] += 0.03f;
		Position[1] += 0.03f;
		Vector(270.f,0.f,0.f,ObjectSelect.Angle);
	}
	else if(Type==MODEL_WING+135)
	{
		Position[1] += 0.05f;
		Position[0] += 0.005f;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮 ��ġ ����
	else if( Type >= MODEL_HELPER+135 && Type <= MODEL_HELPER+145 ) // ��Ű ������ Ƽ��
	{
		Position[1] += 0.02f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
	else if( Type == MODEL_POTION+160 || Type == MODEL_POTION+161 )	// ����� ����, ������ ����
	{
		Position[1] += 0.05f;
		Vector(270.f, 0.f, 0.f, ObjectSelect.Angle);
	}
#endif // LEM_ADD_LUCKYITEM
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// ���� ���� �κ��丮 ��ġ, ���� ����
	else if( COMGEM::Check_Jewel_Com(Type-MODEL_ITEM) != COMGEM::NOGEM)
	{
		Vector(270.f, -10.f, 0.f, ObjectSelect.Angle);
		switch( COMGEM::Check_Jewel_Com(Type-MODEL_ITEM) )
		{
		case COMGEM::eLOW_C:
		case COMGEM::eUPPER_C:
			Vector( 270.f, -10.f, -45.f, ObjectSelect.Angle );
			break;
		case COMGEM::eLIFE_C:
		case COMGEM::eCREATE_C:
			Position[1] -= 0.05f;
		break;
		case COMGEM::eGEMSTONE_C:
			Position[1] -= 0.05f;
			Vector(270.f, 90.f, 0.f, ObjectSelect.Angle);
		break;
		}
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	// =====================================================================================/
	// ObjectSelect ó�� �κ� 1. �Ϲ� ������


	// ObjectSelect ó�� �κ� 2. ���� ������
	// =====================================================================================
#ifdef ADD_SOCKET_ITEM			
	// �κ��丮 ���� ������ ��ġ�� ����(������ �����۵� ������)
	switch (Type)
	{
	case MODEL_SWORD+26:		// �ö�������
		{
			Position[0] -= 0.02f;				// ����
			Position[1] += 0.04f;				// ����
			Vector(180.f,270.f,10.f,ObjectSelect.Angle);
		}break;
	case MODEL_SWORD+27:		// �ҵ�극��Ŀ
		{
			Vector(180.f,270.f,15.f,ObjectSelect.Angle);
		}break;
	case MODEL_SWORD+28:		// ��ٽ�Ÿ��
		{
			Position[1] += 0.02f;
			Vector(180.f,270.f,10.f,ObjectSelect.Angle);
		}break;
	case MODEL_MACE+16:			// ���ν�Ʈ���̽�
		{
			Position[0] -= 0.02f;
			Vector(180.f,270.f,15.f,ObjectSelect.Angle);
		}
		break;
	case MODEL_MACE+17:			// �ۼַ�Ʈ����
		{
			Position[0] -= 0.02f;
			Position[1] += 0.04f;
			Vector(180.f,270.f,15.f,ObjectSelect.Angle);
		}break;
// 	case MODEL_BOW+23:			// ��ũ���ð�
// 		{
// 			Position[0] -= 0.04f;
// 			Position[1] += 0.12f;
// 			Vector(180.f, -90.f, 15.f,ObjectSelect.Angle);
// 		}break;
	case MODEL_STAFF+30:			// ���鸮������
		{
			Vector(180.f,90.f,10.f,ObjectSelect.Angle);
		}break;
	case MODEL_STAFF+31:			// �κ����˽�����
		{
			Vector(180.f,90.f,10.f,ObjectSelect.Angle);
		}break;
	case MODEL_STAFF+32:			// �ҿ�긵��
		{
			Vector(180.f,90.f,10.f,ObjectSelect.Angle);
		}break;
	}
#endif // ADD_SOCKET_ITEM
	// =====================================================================================/
	// ObjectSelect ó�� �κ� 2. ���� ������


	// ObjectSelect ó�� �κ� 3. ��Ÿ ������
	// =====================================================================================
#ifdef LDK_FIX_CAOS_THUNDER_STAFF_ROTATION
	//inventory ī���� ���� ������ ȸ���� �̻�(2008.08.12)
	switch(Type)
	{
	case MODEL_STAFF+7:
		{
			Vector(0.f,0.f,205.f,ObjectSelect.Angle);
		}break;
	}
#endif //LDK_FIX_CAOS_THUNDER_STAFF_ROTATION
	// =====================================================================================/
	// ObjectSelect ó�� �κ� 3. ��Ÿ ������


#ifdef KJH_FIX_20080904_INVENTORY_ITEM_RENDER
	switch(Type)
	{
	case MODEL_WING+8:			// ġ�ᱸ��
	case MODEL_WING+9:			// ������󱸽�
	case MODEL_WING+10:			// ���ݷ���󱸽�
	case MODEL_WING+11:			// ��ȯ����
		{
			Position[0] += 0.005f;
			Position[1] -= 0.02f;
		}break;
	case MODEL_POTION+21:		// ������ǥ��
		{
			Position[0] += 0.005f;
			Position[1] -= 0.005f;
		}break;
	case MODEL_POTION+13:		// �༮
	case MODEL_POTION+14:		// ����
	case MODEL_POTION+22:		// â��
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	case MODEL_POTION+154:		// ĮƮ��
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		{			
			Position[0] += 0.005f;
			Position[1] += 0.015f;
		}break;
	}
#endif // KJH_FIX_20080904_INVENTORY_ITEM_RENDER

	//���� �Ǿ�����...--;;
	if(1==Select)
	{
		ObjectSelect.Angle[1] = WorldTime*0.45f;
	}

	ObjectSelect.Type = Type;
	if(ObjectSelect.Type>=MODEL_HELM && ObjectSelect.Type<MODEL_BOOTS+MAX_ITEM_INDEX
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| ObjectSelect.Type == MODEL_ARMORINVEN_60
		|| ObjectSelect.Type == MODEL_ARMORINVEN_61
		|| ObjectSelect.Type == MODEL_ARMORINVEN_62
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)
		ObjectSelect.Type = MODEL_PLAYER;
	else if(ObjectSelect.Type==MODEL_POTION+12)//�̹�Ʈ ������
	{
		if(Level==0)
		{
			ObjectSelect.Type = MODEL_EVENT;
			Type = MODEL_EVENT;
		}
		else if(Level==2)
		{
			ObjectSelect.Type = MODEL_EVENT+1;
			Type = MODEL_EVENT+1;
		}
	}
	
	BMD *b = &Models[ObjectSelect.Type];
	b->CurrentAction                 = 0;
	ObjectSelect.AnimationFrame      = 0;
	ObjectSelect.PriorAnimationFrame = 0;
	ObjectSelect.PriorAction         = 0;
	if(Type >= MODEL_HELM && Type<MODEL_HELM+MAX_ITEM_INDEX)
	{
		b->BodyHeight = -160.f;

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮 ��ġ ����
		if( Check_LuckyItem( Type - MODEL_ITEM ))				b->BodyHeight-=10.0f;
		if( Type == MODEL_HELM+65 || Type == MODEL_HELM+70 )	Position[0] += 0.04f;
#endif // LEM_ADD_LUCKYITEM
	}
	else if(Type >= MODEL_ARMOR && Type<MODEL_ARMOR+MAX_ITEM_INDEX)
	{
		b->BodyHeight = -100.f;

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮 ��ġ ����
		if( Check_LuckyItem( Type - MODEL_ITEM ))	b->BodyHeight-=13.0f;
#endif // LEM_ADD_LUCKYITEM
	}
	else if(Type >= MODEL_GLOVES && Type<MODEL_GLOVES+MAX_ITEM_INDEX)
		b->BodyHeight = -70.f;
	else if(Type >= MODEL_PANTS && Type<MODEL_PANTS+MAX_ITEM_INDEX)
		b->BodyHeight = -50.f;
	else
		b->BodyHeight = 0.f;
	float Scale  = 0.f;

	if(Type>=MODEL_HELM && Type<MODEL_BOOTS+MAX_ITEM_INDEX)
	{
		if(Type>=MODEL_HELM && Type<MODEL_HELM+MAX_ITEM_INDEX)			
		{
			Scale = MODEL_HELM+39 <= Type && MODEL_HELM+44 >= Type ? 0.007f : 0.0039f;
#ifdef LDS_FIX_ELFHELM_CILPIDREI_RESIZE			// ���ǵ巹�� ��� SIZE ����� ���� �ϱ� ����.
			if( Type == MODEL_HELM+31)			// ���ǵ巹�� ����ΰ�� scale �� ����
				Scale = 0.007f;
#endif // LDS_FIX_ELFHELM_CILPIDREI_RESIZE

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮 ������ ���� ( ��ȯ����HELM )
			if( Type == MODEL_HELM+65 || Type == MODEL_HELM+70 )	Scale = 0.007f;
#endif // LEM_ADD_LUCKYITEM
		}
		else if(Type>=MODEL_ARMOR && Type<MODEL_ARMOR+MAX_ITEM_INDEX)
      		Scale = 0.0039f;
		else if(Type>=MODEL_GLOVES && Type<MODEL_GLOVES+MAX_ITEM_INDEX)
      		Scale = 0.0038f;
		else if(Type>=MODEL_PANTS && Type<MODEL_PANTS+MAX_ITEM_INDEX)
      		Scale = 0.0033f;
		else if(Type>=MODEL_BOOTS && Type<MODEL_BOOTS+MAX_ITEM_INDEX)
      		Scale = 0.0032f;
#ifndef LDS_FIX_ELFHELM_CILPIDREI_RESIZE	// ������ �� ������ �ϴ� �ҽ�	
		else if( Type == MODEL_HELM+31)				// ���ǵ巹�� ��� SIZE ���� ��
			Scale = 0.007f;
#endif // LDS_FIX_ELFHELM_CILPIDREI_RESIZE // ������ �� ������ �ϴ� �ҽ�
		else if (Type == MODEL_ARMOR+30)
			Scale = 0.0035f;
		else if (Type == MODEL_ARMOR+32)
			Scale = 0.0035f;
		else if (Type == MODEL_ARMOR+29)
			Scale = 0.0033f;

		//$ ũ���̿��� ������(���)
		if(Type == MODEL_ARMOR+34)	// ���� ����
			Scale = 0.0032f;
		else if(Type == MODEL_ARMOR+35)	// �渶���� ����
			Scale = 0.0032f;
		else if(Type == MODEL_GLOVES+38)	// ���˻� �尩
			Scale = 0.0032f;
	}
	else
	{
        if(Type==MODEL_WING+6)     //  ���˻� ����.
            Scale = 0.0015f;
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// ���� ���� �κ��丮 ������
		else if( COMGEM::Check_Jewel_Com(Type-MODEL_ITEM) != COMGEM::NOGEM)
		{
			Scale = 0.004f;
			switch( COMGEM::Check_Jewel_Com(Type-MODEL_ITEM) )
			{
				case COMGEM::eLOW_C:
					Position[0] -= 0.05f;
					Scale = 0.003f;
				break;
				case COMGEM::eUPPER_C:
					Position[0] -= 0.05f;
					Scale = 0.004f;
				break;
				case COMGEM::eCREATE_C:
					Position[1] += 0.05f;
					Scale = 0.0025f;
				break;
				case COMGEM::eCHAOS_C:
					Position[1] += 0.025f;
					Scale = 0.002f;
				break;
				case COMGEM::ePROTECT_C:
					Position[1] += 0.05f;
					Scale = 0.0036f;
				break;
				case COMGEM::eLIFE_C:
					Position[1] += 0.025f;
					Scale = 0.0035f;
				break;
				case COMGEM::eGEMSTONE_C:
					Position[1] += 0.05f;
					Scale = 0.0035f;
				break;
				case COMGEM::eHARMONY_C:
					Scale = 0.005f;
				break;

			}
		}
#else // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		else if(Type==MODEL_COMPILED_CELE || Type==MODEL_COMPILED_SOUL)
			Scale = 0.004f;
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
		else if ( Type>=MODEL_WING+32 && Type<=MODEL_WING+34)
		{
			Scale = 0.001f;
			Position[1] -= 0.05f;
		}
#ifdef ADD_SEED_SPHERE_ITEM
		else if(Type >= MODEL_WING+60 && Type <= MODEL_WING+65)	// �õ�
			Scale = 0.0022f; 
		else if(Type >= MODEL_WING+70 && Type <= MODEL_WING+74)	// ���Ǿ�
			Scale = 0.0017f; 
		else if(Type >= MODEL_WING+100 && Type <= MODEL_WING+129)	// �õ彺�Ǿ�
			Scale = 0.0017f; 
#endif	// ADD_SEED_SPHERE_ITEM
		else if(Type>=MODEL_WING && Type<MODEL_WING+MAX_ITEM_INDEX)
		{
      			Scale = 0.002f;
		}
#ifdef HELLOWIN_EVENT
		//�ҷ�������
		else
		if ( Type==MODEL_POTION+45 || Type==MODEL_POTION+49)
		{
			Scale = 0.003f;
		}
		else
		if(Type>=MODEL_POTION+46 && Type<=MODEL_POTION+48)
		{
			Scale = 0.0025f;
		}
		else
		if(Type == MODEL_POTION+50)
		{
			Scale = 0.001f;

//			Position[1] += 0.05f;
//   			Vector(0.f,ObjectSelect.Angle[1],0.f,ObjectSelect.Angle);
		}
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
		else
		if ( Type>=MODEL_POTION+32 && Type<=MODEL_POTION+34)
		{
			Scale = 0.002f;
			Position[1] += 0.05f;
   			Vector(0.f,ObjectSelect.Angle[1],0.f,ObjectSelect.Angle);
		}
		else
		if ( Type>=MODEL_EVENT+21 && Type<=MODEL_EVENT+23)
		{
			Scale = 0.002f;
			if(Type==MODEL_EVENT+21)
				Position[1] += 0.08f;
			else
				Position[1] += 0.06f;
   			Vector(0.f,ObjectSelect.Angle[1],0.f,ObjectSelect.Angle);
		}
#endif
        else if(Type==MODEL_POTION+21)	// ����
			Scale = 0.002f;
		else if(Type == MODEL_BOW+19)
			Scale = 0.002f;
        else if(Type==MODEL_EVENT+11)	// ����
			Scale = 0.0015f;
        else if ( Type==MODEL_HELPER+4 )    //  ��ũȣ��
			Scale = 0.0015f;
        else if ( Type==MODEL_HELPER+5 )    //  ��ũ���Ǹ�.
			Scale = 0.005f;
        else if ( Type==MODEL_HELPER+30 )   //  ����.    
			Scale = 0.002f;
        else if ( Type==MODEL_EVENT+16 )    //  ������ ����.
 			Scale = 0.002f;
#ifdef MYSTERY_BEAD
		else if ( Type==MODEL_EVENT+19 )	//. �ź��Ǳ���
			Scale = 0.0025f;
#endif // MYSTERY_BEAD
		else if(Type==MODEL_HELPER+16)	//. ��õ���� ��
			Scale = 0.002f;
		else if(Type==MODEL_HELPER+17)	//. ���庻
			Scale = 0.0018f;
		else if(Type==MODEL_HELPER+18)	//. �������
			Scale = 0.0018f;
#ifdef CSK_FREE_TICKET
		// ������ ������ ���ϴ� ��
		else if(Type == MODEL_HELPER+46)	// ���������� ���������
		{
			Scale = 0.0018f;
		}
		else if(Type == MODEL_HELPER+47)	// ����ĳ�� ���������
		{
			Scale = 0.0018f;
		}
		else if(Type == MODEL_HELPER+48)	// Į���� ���������
		{
			Scale = 0.0018f;
		}
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
		// ������ ������ ���ϴ� ��
		else if(Type == MODEL_POTION+54)	// ī����ī��
		{
			Scale = 0.0024f;
		}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
		// ������ ������ ���ϴ� ��
		else if(Type == MODEL_POTION+58)
		{
			Scale = 0.0012f;
		}
		else if(Type == MODEL_POTION+59 || Type == MODEL_POTION+60)
		{
			Scale = 0.0010f;
		}
		else if(Type == MODEL_POTION+61 || Type == MODEL_POTION+62)
		{
			Scale = 0.0009f;
		}
#endif // CSK_RARE_ITEM
#ifdef CSK_LUCKY_CHARM
		else if( Type == MODEL_POTION+53 )// ����� ����
		{
			Scale = 0.00078f;
		}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
		else if( Type == MODEL_HELPER+43 || Type == MODEL_HELPER+44 || Type == MODEL_HELPER+45 )
		{
			Scale = 0.0021f;
		}
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
		else if( Type >= MODEL_POTION+70 && Type <= MODEL_POTION+71 )
		{
			Scale = 0.0028f;
		}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
		else if( Type >= MODEL_POTION+72 && Type <= MODEL_POTION+77 )
		{
			Scale = 0.0025f;
		}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
		else if( Type == MODEL_HELPER+59 )
		{
			Scale = 0.0008f;
		}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
		else if( Type >= MODEL_HELPER+54 && Type <= MODEL_HELPER+58 )
		{
			Scale = 0.004f;
		}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
		else if( Type >= MODEL_POTION+78 && Type <= MODEL_POTION+82 )
		{
			Scale = 0.0025f;
		}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
		else if( Type == MODEL_HELPER+60 )
		{
			Scale = 0.005f;
		}
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
		else if( Type == MODEL_HELPER+61 )
		{
			Scale = 0.0018f;
		}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
		else if(Type == MODEL_POTION+83)
		{
			Scale = 0.0009f;
		}
#endif //PSW_RARE_ITEM
#ifdef CSK_LUCKY_SEAL
		else if( Type == MODEL_HELPER+43 || Type == MODEL_HELPER+44 || Type == MODEL_HELPER+45 )
		{
			Scale = 0.0021f;
		}
#endif //CSK_LUCKY_SEAL
#ifdef PSW_CHARACTER_CARD 
		else if(Type == MODEL_POTION+91) // ĳ���� ī��
		{
			Scale = 0.0034f;
		}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
		else if(Type == MODEL_POTION+92) // ī����ī�� ���
		{
			Scale = 0.0024f;
		}
		else if(Type == MODEL_POTION+93) // ī����ī�� ����
		{
			Scale = 0.0024f;
		}
		else if(Type == MODEL_POTION+95) // ī����ī�� �̴�
		{
			Scale = 0.0024f;
		}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
		else if( Type == MODEL_POTION+94 ) // ����Ʈ �߰� ġ�� ����
		{
			Scale = 0.0022f;
		}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
		else if( Type == MODEL_POTION+84 )  // ���ɻ���
		{
			Scale = 0.0031f;
		}
		else if( Type == MODEL_POTION+85 )  // ���ɼ�
		{
			Scale = 0.0044f;
		}
		else if( Type == MODEL_POTION+86 )  // ���ɰ��
		{
			Scale = 0.0031f;
		}
		else if( Type == MODEL_POTION+87 )  // ������
		{
			Scale = 0.0061f;
		}
		else if( Type == MODEL_POTION+88 )  // ��� ����
		{
			Scale = 0.0035f;
		}
		else if( Type == MODEL_POTION+89 )  // ������ ����
		{
			Scale = 0.0035f;
		}
		else if( Type == MODEL_POTION+90 )  // ����� ����
		{
			Scale = 0.0035f;
		}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
		else if(Type >= MODEL_HELPER+62 && Type <= MODEL_HELPER+63)
		{
			Scale = 0.002f;
		}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
		else if(Type >= MODEL_POTION+97 && Type <= MODEL_POTION+98)
		{
			Scale = 0.003f;
		}
#endif //PSW_ADD_PC4_SCROLLITEM	
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
		else if( Type == MODEL_POTION+96 ) 
		{
			Scale = 0.0028f;
		}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
		else if( MODEL_HELPER+64 == Type || Type == MODEL_HELPER+65 )
		{
			switch(Type)
			{
			case MODEL_HELPER+64: Scale = 0.0005f; break;
			case MODEL_HELPER+65: Scale = 0.0016f; break;
			}			
		}
#endif //LDK_ADD_PC4_GUARDIAN	
#ifdef LDK_ADD_RUDOLPH_PET
		else if( Type == MODEL_HELPER+67 )
		{
			Scale = 0.0015f;
		}
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
		else if( Type == MODEL_HELPER+80 )
		{
			Scale = 0.0020f;
		}
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_SNOWMAN_CHANGERING
		else if( Type == MODEL_HELPER+68 )
		{
			Scale = 0.0026f;
		}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
		else if( Type == MODEL_HELPER+76 )
		{
			Scale = 0.0026f;
		}
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
		else if( Type == MODEL_HELPER+69 )	// ��Ȱ�� ����
		{
			Scale = 0.0023f;
		}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
		else if( Type == MODEL_HELPER+70 )	// �̵��� ����
		{
			Scale = 0.0018f;
		}
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef ASG_ADD_CS6_GUARD_CHARM
		else if (Type == MODEL_HELPER+81)	// ��ȣ�Ǻ���
			Scale = 0.0012f;
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM 
		else if (Type == MODEL_HELPER+82)	// �����ۺ�ȣ����
			Scale = 0.0012f;
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM 
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		else if (Type == MODEL_HELPER+93)	// ��������帶����
			Scale = 0.0021f;
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		else if (Type == MODEL_HELPER+94)	// ǳ�������帶����
			Scale = 0.0021f;
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
        else if(Type==MODEL_SWORD+19)   //  ��õ���� �����.
        {
            if ( ItemLevel>=0 )
            {
                Scale = 0.0025f;
            }
            else    //  ����Ʈ ������.
            {
                Scale = 0.001f;
                ItemLevel = 0;
            }
        }
        else if(Type==MODEL_STAFF+10)   //  ��õ���� ���� ������.
        {
            if ( ItemLevel>=0 )
            {
                Scale = 0.0019f;
            }
            else    //  ����Ʈ ������.
            {
                Scale = 0.001f;
                ItemLevel = 0;
            }
        }
        else if(Type==MODEL_BOW+18)     //  ��õ���� ���뼮��.
        {
            if ( ItemLevel>=0 )
            {
                Scale = 0.0025f;
            }
            else    //  ����Ʈ ������.
            {
                Scale = 0.0015f;
                ItemLevel = 0;
            }
        }
        else if ( Type>=MODEL_MACE+8 && Type<=MODEL_MACE+11 )
        {
            Scale = 0.003f;
        }
		else if(Type == MODEL_MACE+12)
		{
			Scale = 0.0025f;
		}
#ifdef LDK_ADD_GAMBLERS_WEAPONS
		else if( Type == MODEL_MACE+18 )
		{
			Scale = 0.0024f;
		}
#endif //LDK_ADD_GAMBLERS_WEAPONS
		else if(Type == MODEL_EVENT+12)		//. ������ ����
		{
			Scale = 0.0012f;
		}
		else if(Type == MODEL_EVENT+13)		//. ��ũ����
		{
			Scale = 0.0025f;
		}
		else if ( Type == MODEL_EVENT+14)	//. ������ ����
		{
			Scale = 0.0028f;
		}
		else if ( Type == MODEL_EVENT+15)	// �������� ����
		{
			Scale = 0.0023f;
		}
        else if ( Type>=MODEL_POTION+22 && Type<MODEL_POTION+25 )
        {
            Scale = 0.0025f;
        }
        else if ( Type>=MODEL_POTION+25 && Type<MODEL_POTION+27 )
        {
            Scale = 0.0028f;
        }
		else if ( Type == MODEL_POTION+63)	// ����
		{
			Scale = 0.007f;
		}
#ifdef YDG_ADD_FIRECRACKER_ITEM
		else if ( Type == MODEL_POTION+99)	// ũ�������� ����
		{
			Scale = 0.0025f;
		}
#endif	// YDG_ADD_FIRECRACKER_ITEM

		else if ( Type == MODEL_POTION+52)	// GM ��������
		{
			Scale = 0.0014f;
		}
#ifdef _PVP_MURDERER_HERO_ITEM
        else if ( Type==MODEL_POTION+30 )	// ¡ǥ
        {
            Scale = 0.002f;
        }
#endif// _PVP_MURDERER_HERO_ITEM
		else if( Type==MODEL_HELPER+38 )
		{
			Scale = 0.0025f;
		}
		else if( Type==MODEL_POTION+41 )
		{
			Scale = 0.0035f;
		}
		else if( Type==MODEL_POTION+42 )
		{
			Scale = 0.005f;
		}
		else if( Type==MODEL_POTION+43 )
		{
			Position[1] += -0.005f;
			Scale = 0.0035f;
		}
		else if( Type==MODEL_POTION+44 )
		{
			Position[1] += -0.005f;
			Scale = 0.004f;
		}
        else if ( Type==MODEL_POTION+7 )
        {
            Scale = 0.0025f;
        }
#ifdef CSK_LUCKY_SEAL
		else if( Type == MODEL_HELPER+43 || Type == MODEL_HELPER+44 || Type == MODEL_HELPER+45 )
		{
			Scale = 0.0021f;
		}
#endif //CSK_LUCKY_SEAL
        else if ( Type==MODEL_HELPER+7 )
        {
            Scale = 0.0025f;
        }
        else if ( Type==MODEL_HELPER+11 )
        {
            Scale = 0.0025f;
        }
		//^ �渱 ������ ����
		else if(Type == MODEL_HELPER+32)	// ���� ����
		{
			Scale = 0.0019f;
		}
		else if(Type == MODEL_HELPER+33)	// ������ ��ȣ
		{
			Scale = 0.004f;
		}
		else if(Type == MODEL_HELPER+34)	// �ͼ��� ����
		{
			Scale = 0.004f;
		}
		else if(Type == MODEL_HELPER+35)	// ���Ǹ� ����
		{
			Scale = 0.004f;
		}
		else if(Type == MODEL_HELPER+36)	// �η��� ���Ǹ�
		{
			Scale = 0.007f;
		}
		else if(Type == MODEL_HELPER+37)	// �渱�� ���Ǹ�
		{
			Scale = 0.005f;
		}
		else if( Type == MODEL_BOW+21)
		{
			Scale = 0.0022f;
		}
#ifdef CSK_PCROOM_ITEM
		else if(Type >= MODEL_POTION+55 && Type <= MODEL_POTION+57
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
			|| Type >= MODEL_POTION+157 && Type <= MODEL_POTION+159
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
			)
		{
			Scale = 0.0014f;
		}
#endif // CSK_PCROOM_ITEM
		else if(Type == MODEL_HELPER+49)
		{
			Scale = 0.0013f;
		}
		else if(Type == MODEL_HELPER+50)
		{
			Scale = 0.003f;
		}
		else if(Type == MODEL_HELPER+51)
		{
			Scale = 0.003f;
		}
		else if(Type == MODEL_POTION+64
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
			|| Type == MODEL_POTION+153
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
			)
		{
			Scale = 0.003f;
		}
		else if (Type == MODEL_POTION+65)
			Scale = 0.003f;
		else if (Type == MODEL_POTION+66)
			Scale = 0.0035f;
		else if (Type == MODEL_POTION+67)
			Scale = 0.0035f;
		else if (Type == MODEL_POTION+68)
			Scale = 0.003f;
		else if (Type == MODEL_HELPER+52)
			Scale = 0.005f;
		else if (Type == MODEL_HELPER+53)
			Scale = 0.005f; 
		//$ ũ���̿��� ������(����)
		else if(Type == MODEL_SWORD+24)	// ���� ��
		{
			Scale = 0.0028f;
		}
		else if(Type == MODEL_BOW+22)	// ����Ȱ
		{
			Scale = 0.0020f;
		}
#ifdef ADD_SOCKET_ITEM
		else if( Type == MODEL_BOW+23 )		// ��ũ���ð�
		{
			Scale = 0.0032f;
		}
#endif // ADD_SOCKET_ITEM
        else if( Type==MODEL_HELPER+14 || Type==MODEL_HELPER+15 )
        {
            Scale = 0.003f;
        }
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
		//����� ����
		else if(Type == MODEL_POTION+100)
		{
			Scale = 0.0040f;
		}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if (Type == MODEL_POTION+156)
			Scale = 0.0039f;
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if(Type>=MODEL_POTION && Type<MODEL_POTION+MAX_ITEM_INDEX)
		{
      		Scale = 0.0035f;
		}
		else if(Type>=MODEL_SPEAR && Type<MODEL_SPEAR+MAX_ITEM_INDEX)
        {
#ifdef LDK_FIX_INVENTORY_SPEAR_SCALE
			// if�� ����
			if(Type == MODEL_SPEAR+10)	//. ��� â
				Scale = 0.0018f;
#ifdef LDK_ADD_GAMBLERS_WEAPONS
			else if( Type == MODEL_SPEAR+11 )	// �׺� ���� ��
				Scale = 0.0025f;
#endif //LDK_ADD_GAMBLERS_WEAPONS
			else
				Scale = 0.0021f;
#else //LDK_FIX_INVENTORY_SPEAR_SCALE
			if(MODEL_SPEAR+10)	//. ��� â
				Scale = 0.0018f;
			else
				Scale = 0.0021f;
#endif //LDK_FIX_INVENTORY_SPEAR_SCALE
		}
		else if(Type>=MODEL_STAFF && Type<MODEL_STAFF+MAX_ITEM_INDEX)
		{
			if (Type >= MODEL_STAFF+14 && Type <= MODEL_STAFF+20)	// ��ȯ���� ��ƽ.
				Scale = 0.0028f;
			else if (Type >= MODEL_STAFF+21 && Type <= MODEL_STAFF+29)	// ��ƹ�Ʈ�� ��, ���� ��
				Scale = 0.004f;
#ifdef LDK_ADD_GAMBLERS_WEAPONS
			else if( Type == MODEL_STAFF+33 )	// �׺� ���� ������
				Scale = 0.0028f;
			else if( Type == MODEL_STAFF+34 )	// �׺� ���� ������(��ȯ�����)
				Scale = 0.0028f;
#endif //LDK_ADD_GAMBLERS_WEAPONS
			else
      			Scale = 0.0022f;
		}
        else if(Type==MODEL_BOW+15)
      		Scale = 0.0011f;
		else if(Type==MODEL_BOW+7)
      		Scale = 0.0012f;
		else if(Type==MODEL_EVENT+6)
      		Scale = 0.0039f;
		else if(Type==MODEL_EVENT+8)	//  �� ����
			Scale = 0.0015f;
		else if(Type==MODEL_EVENT+9)	//  �� ����
			Scale = 0.0019f;
		else
		{
			Scale = 0.0025f;
		}

#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// ���� ���� 100% ���� ����
		if( Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN
			&& Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END )
		{
			Scale = 0.0020f;
		}
#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING

#ifdef USE_EVENT_ELDORADO
		if(Type==MODEL_EVENT+10)	//  ������
		{
			Scale = 0.001f;
		}
#endif // USE_EVENT_ELDORADO
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH	// ������ ���� (PC�� ������, �Ϻ� 6�� ������)
		else if(Type == MODEL_HELPER+96)
		{
			Scale = 0.0031f;
		}	
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH	
		else if(Type >= MODEL_ETC+19 && Type <= MODEL_ETC+27		// ������
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
			|| Type == MODEL_POTION+151 || Type == MODEL_POTION+152	// 1���� �Ƿڼ�, 1���� �Ƿ� �Ϸ� Ȯ�μ�
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
			)
		{
			Scale = 0.0023f;
		}
#ifdef PBG_ADD_SANTAINVITATION
		else if(Type == MODEL_HELPER+66)
		{
			Scale = 0.0020f;
		}
#endif //PBG_ADD_SANTAINVITATION
#ifdef YDG_ADD_HEALING_SCROLL
		else if(Type == MODEL_POTION+140)	// ġ���� ��ũ��
		{
			Scale = 0.0026f;
		}
#endif	// YDG_ADD_HEALING_SCROLL
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		else if( Type == MODEL_HELPER+122 )	// ���̷��� ���Ź���
		{
			Scale = 0.0033f;
		}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
		else if( Type == MODEL_HELPER+123 )	// ���̷��� ��
		{
			Scale = 0.0009f;
		}
#endif	// YDG_ADD_SKELETON_PET
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
		else if(Type >= MODEL_POTION+145 && Type <= MODEL_POTION+150)
		{
			Scale = 0.0018f;
		}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
		// ������ ������ ���ϴ� ��
		//���ð���, �ٸ�ī, �ٸ�ī��7�� ���������
		else if(Type >= MODEL_HELPER+125 && Type <= MODEL_HELPER+127)	//���ð���, �ٸ�ī, �ٸ�ī��7�� ���������
		{
			Scale = 0.0013f;
		}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM	
		else if( Type == MODEL_HELPER+128 )		// ��������
		{
			Scale = 0.0035f;
		}
		else if( Type == MODEL_HELPER+129 )		// ��������
		{
			Scale = 0.0035f;
		}
		else if( Type == MODEL_HELPER+134 )		// ����
		{
			Scale = 0.0033f;
		}
#endif	//LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
		else if( Type == MODEL_HELPER+130 )		// ��ũ��
		{
			Scale = 0.0032f;
		}
		else if( Type == MODEL_HELPER+131 )		// ��������
		{
			Scale = 0.0033f;
		}
		else if( Type == MODEL_HELPER+132 )		// ����ũ��
		{
			Scale = 0.0025f;
		}
		else if( Type == MODEL_HELPER+133 )		// ����������
		{
			Scale = 0.0033f;
		}
#endif	//LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
		//�׺� ���� ������ �� ��ȣ ���� �ؾߵ�
		else if ( Type==MODEL_HELPER+71 || Type==MODEL_HELPER+72 || Type==MODEL_HELPER+73 || Type==MODEL_HELPER+74 || Type==MODEL_HELPER+75 )
		{
			Scale = 0.0019f;
		}
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef LDK_ADD_GAMBLERS_WEAPONS
		else if( Type == MODEL_BOW+24 )
		{
			Scale = 0.0023f;
		}
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef PBG_ADD_CHARACTERCARD
		//���� ��ũ ��ȯ���� ī��
		else if(Type == MODEL_HELPER+97 || Type == MODEL_HELPER+98 || Type == MODEL_POTION+91)
		{
			Scale = 0.0028f;
		}
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
		else if(Type == MODEL_HELPER+99)
		{
			Scale = 0.0025f;
		}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
		//Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
		else if(Type >= MODEL_HELPER+117 && Type <= MODEL_HELPER+120)
		{
			// �κ��� �ȵ��� 1x2������� ����
#ifdef PBG_MOD_SECRETITEM
			Scale = 0.0022f;
#else //PBG_MOD_SECRETITEM
			Scale = 0.0035f;
#endif //PBG_MOD_SECRETITEM
		}
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
		else if (Type == MODEL_POTION+110)	// ������ǥ��
		{
			Scale = 0.004f;
		}
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		else if(Type == MODEL_HELPER+107)
		{
			// ġ��������
			Scale = 0.0034f;
		}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
		else if(Type == MODEL_POTION+133)		// ����Ʈ SDȸ�� ����
		{
			Scale = 0.0030f;
		}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#ifdef YDG_ADD_CS7_MAX_SD_AURA
		else if(Type == MODEL_HELPER+105)		// SD���� ����
		{
			Scale = 0.002f;
		}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
		else if( MODEL_POTION+101 <= Type && Type <= MODEL_POTION+109 )
		{
			switch(Type)
			{
			case MODEL_POTION+101: // �ǹ�������
				{
					Scale = 0.004f;
				}break;
			case MODEL_POTION+102: // ���̿��� ��ɼ�
				{
					Scale = 0.005f;
				}break;
			case MODEL_POTION+103: // ��ũ�ι��� ����
			case MODEL_POTION+104: 
			case MODEL_POTION+105: 
			case MODEL_POTION+106: 
			case MODEL_POTION+107: 
			case MODEL_POTION+108: 
				{
					Scale = 0.004f;
				}break;
			case MODEL_POTION+109: // ��ũ�ι���
				{
					Scale = 0.003f;
				}break;
			}
		}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef LDK_ADD_CS7_UNICORN_PET	//������
		else if( Type == MODEL_HELPER+106 )
		{
			Scale = 0.0015f;
		}	
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING
		else if( Type == MODEL_WING+130 )
		{
			Scale = 0.0012f;
		}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX // �ΰ��Ә� ������ // ��Ű������6��			// MODEL_POTION+134~139
		else if( Type >= MODEL_POTION+134 && Type <= MODEL_POTION+139 )
		{
			Scale = 0.0050f;
		}
#endif // LDK_ADD_INGAMESHOP_PACKAGE_BOX // �ΰ��Ә� ������ // ��Ű������6��			// MODEL_POTION+134~139
#if defined(LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE)||defined(LDS_ADD_INGAMESHOP_ITEM_RINGRUBY)||defined(LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ)||defined(LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST)	
		else if( Type >= MODEL_HELPER+109 && Type <= MODEL_HELPER+112  )	// �����̾�(Ǫ����)��,���(������)��,������(��Ȳ)��,�ڼ���(�����)��
		{
			Scale = 0.0045f;
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �����̾�(Ǫ����)��,���(������)��,������(��Ȳ)��,�ڼ���(�����)��
#if defined(LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY)||defined(LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD)||defined(LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE)		
		else if( Type >= MODEL_HELPER+113 && Type <= MODEL_HELPER+115 )		// ���(������)�����, ���޶���(Ǫ��), �����̾�(���) �����
		{
			Scale = 0.0018f;
		}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY)||defined(LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD)||defined(LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE) // ���(������)�����, ���޶���(Ǫ��), �����̾�(���) �����
#if defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD)	// Ű(�ǹ�), Ű(���)
		else if( Type >= MODEL_POTION+112 && Type <= MODEL_POTION+113 )
		{
			Scale = 0.0032f;
		}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD)	// Ű(�ǹ�), Ű(���)
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		else if( Type == MODEL_HELPER+116 )
		{
			Scale = 0.0021f;
		}
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
		else if( Type >= MODEL_POTION+114 && Type <= MODEL_POTION+119 )
		{
			Scale = 0.0038f;
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
		else if( Type >= MODEL_POTION+126 && Type <= MODEL_POTION+129 )
		{
			Scale = 0.0038f;
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
		else if( Type >= MODEL_POTION+130 && Type <= MODEL_POTION+132 )
		{
			Scale = 0.0038f;
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
		else if( Type == MODEL_HELPER+121 )
		{
			Scale = 0.0018f;
			//Scale = 1.f;
		}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
		else if(Type == MODEL_HELPER+124)
			Scale = 0.0018f;
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		else if(Type >= MODEL_WING+49 && Type <= MODEL_WING+50)
		{
			Scale = 0.002f;
		}
		else if(Type == MODEL_WING+135)
		{
			Scale = 0.0012f;
		}
		else if(Type >= MODEL_SWORD+32 && Type <= MODEL_SWORD+34)
		{
			Scale = 0.0035f;
		}
		else if(Type >= MODEL_ETC+30 && Type <= MODEL_ETC+36)
		{
			Scale = 0.0023f;
		}
		else if(Type == MODEL_ARMORINVEN_60 || Type == MODEL_ARMORINVEN_62 || Type == MODEL_ARMORINVEN_61)
		{
			b->BodyHeight = -100.f;
			Scale = 0.0039f;
		}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		else if (Type == MODEL_POTION+156)
			Scale = 0.0025f;
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �κ��丮 ������ ���� [lem_2010.9.7]
		// LEM_TSET  ����� ����, ������ ���� ������[lem_2010.9.7]
		else if(Type >= MODEL_HELPER+135 && Type <= MODEL_HELPER+145)
		{
			Scale = 0.001f;
		}
		else if(Type == MODEL_POTION+160 || Type == MODEL_POTION+161)
		{
			Scale = 0.001f;
		}
		else if(Type == MODEL_HELM+62 || Type == MODEL_HELM+63 || Type == MODEL_HELM+65 || Type == MODEL_HELM+70)
		{
			Scale = 0.001f;
		}
#endif // LEM_ADD_LUCKYITEM
	}

	b->Animation(BoneTransform,ObjectSelect.AnimationFrame,ObjectSelect.PriorAnimationFrame,ObjectSelect.PriorAction,ObjectSelect.Angle,ObjectSelect.HeadAngle,false,false);

	CHARACTER Armor;
	OBJECT *o      = &Armor.Object;
	o->Type        = Type;
    ItemObjectAttribute(o);
	o->LightEnable = false;
	Armor.Class    = 2;

#ifdef PBG_ADD_ITEMRESIZE
	int ScreenPos_X=0, ScreenPos_Y=0;
	Projection(Position,&ScreenPos_X, &ScreenPos_Y);
	if(g_pInGameShop->IsInGameShopRect(ScreenPos_X, ScreenPos_Y))
	{
		o->Scale = Scale * g_pInGameShop->GetRateScale();
	}
	else
#endif //PBG_ADD_ITEMRESIZE
#ifdef NEW_USER_INTERFACE
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PARTCHARGE_SHOP) == true) {
		float ChangeScale = (640.f/static_cast<float>(TheShell().GetWindowSize().x))*3.7f;
		o->Scale = Scale-(Scale/ChangeScale);
	}
	else
#endif // NEW_USER_INTERFACE
	{
		o->Scale = Scale;
	}
		
	VectorCopy(Position,o->Position);
	
    vec3_t Light;
    float  alpha = o->Alpha;

    Vector(1.f,1.f,1.f,Light);

#ifdef MR0
	VPManager::Enable();
#endif //MR0
	
#ifdef MR0
	// Object�� �ִٸ� ���� Lock�� �ɰ�, ������ Lock�� �ɰ� Render 
	ModelManager::SetTargetObject( o );
#endif //MR0

	//�ΰ�
#ifdef PJH_NEW_CHROME
	int Set_Count = 0;

	int nItemType = (Type - MODEL_ITEM) / MAX_ITEM_INDEX;
	int nItemSubType = (Type - MODEL_ITEM) % MAX_ITEM_INDEX;
	// ����ũ�� �ø����ΰ�?
	if (nItemType >= 7 && nItemType <= 11 && (nItemSubType >= 62 && nItemSubType <= 72))
	{
		Set_Count = 1;
	}

	if(Set_Count == 1)
		RenderPartObject(o,Type,NULL,Light,alpha,ItemLevel,Option1,MAX_MODELS+1,true,true,true);
	else
#endif //PJH_NEW_CHROME
    RenderPartObject(o,Type,NULL,Light,alpha,ItemLevel,Option1,ExtOption,true,true,true);

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
	
#ifdef MR0
	VPManager::Disable();
#endif //MR0
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮�� �������� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderItem3D(float sx,float sy,float Width,float Height,int Type,int Level,int Option1,int ExtOption,bool PickUp)
{
	bool Success = false;
	if((g_pPickedItem == NULL || PickUp) 
		&& SEASON3B::CheckMouseIn(sx, sy, Width, Height))
	{
#ifdef NEW_USER_INTERFACE
		if( g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_PARTCHARGE_SHOP) ) 
		{
			Success = true;
		}
		else  
#endif // NEW_USER_INTERFACE
#ifdef PBG_ADD_INGAMESHOPMSGBOX
		if(g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_INGAMESHOP))
		{
			Success = true;
		}
		else
#endif //PBG_ADD_INGAMESHOPMSGBOX
		{
			if( g_pNewUISystem->CheckMouseUse() == false )
				Success = true;
		}
	}

#ifdef PBG_ADD_ITEMRESIZE	
	// �ΰ��Ӽ� ��ġ ������
	if(g_pInGameShop->IsInGameShopRect(sx, sy))
	{
		// �ΰ��Ӽ� ��ǥ ����
		g_pInGameShop->SetConvertInvenCoord(Type,Width,Height);
		// �ΰ��Ӽ� ������ ����
		g_pInGameShop->SetRateScale(Type);

		// �κ��� �������������� �ΰ��Ӽ����� ����
		sx += g_pInGameShop->GetConvertPos().x;
		sy += g_pInGameShop->GetConvertPos().y;
		Width = g_pInGameShop->GetConvertSize().x;
		Height = g_pInGameShop->GetConvertSize().y;
	}
#endif //PBG_ADD_ITEMRESIZE
	if(Type>=ITEM_SWORD && Type<ITEM_SWORD+MAX_ITEM_INDEX)
	{
		sx += Width*0.8f;
		sy += Height*0.85f;
	}
	else if(Type>=ITEM_AXE && Type<ITEM_MACE+MAX_ITEM_INDEX)
	{
		if(Type==ITEM_MACE+13)
		{
			sx += Width*0.6f;
			sy += Height*0.5f;
		}
		else
		{
			sx += Width*0.8f;
			sy += Height*0.7f;
		}
	}
	else if(Type>=ITEM_SPEAR && Type<ITEM_SPEAR+MAX_ITEM_INDEX)
	{
		sx += Width*0.6f;
		sy += Height*0.65f;
	}
	else if( Type==ITEM_BOW+17 )
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if( Type==ITEM_BOW+19 )
	{
		sx += Width*0.7f;
		sy += Height*0.75f;
	}
	else if(Type==ITEM_BOW+20) 
	{
		sx += Width*0.5f;
		sy += Height*0.55f;
	}
	else if( Type>=ITEM_BOW+8 && Type<ITEM_BOW+MAX_ITEM_INDEX )
	{
		sx += Width*0.7f;
		sy += Height*0.7f;
	}
	else if(Type>=ITEM_STAFF && Type<ITEM_STAFF+MAX_ITEM_INDEX)
	{
		sx += Width*0.6f;
		sy += Height*0.55f;
	}
	else if(Type>=ITEM_SHIELD && Type<ITEM_SHIELD+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		if(Type == ITEM_SHIELD+15)
			sy += Height*0.7f;
		else if(Type == ITEM_SHIELD+16)
			sy += Height*0.9f;
#ifdef CSK_ADD_ITEM_CROSSSHIELD
		else if(Type == ITEM_SHIELD+21)		// ũ�ν��ǵ�
		{
			sx += Width*0.05f;
			sy += Height*0.5f;
		}
#endif // CSK_ADD_ITEM_CROSSSHIELD
		else
			sy += Height*0.6f;
	}
	else if(Type>=ITEM_HELM && Type<ITEM_HELM+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		sy += Height*0.8f;
	}
	else if(Type>=ITEM_ARMOR && Type<ITEM_ARMOR+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		if(Type==ITEM_ARMOR+2 || Type==ITEM_ARMOR+4 || Type==ITEM_ARMOR+6)
		{
			sy += Height*1.05f;
		}
		else if(Type==ITEM_ARMOR+3 || Type==ITEM_ARMOR+8)
		{
			sy += Height*1.1f;
		}
		else if ( Type==ITEM_ARMOR+17 || Type==ITEM_ARMOR+18 || Type==ITEM_ARMOR+20 ) //  ���̵峪��Ʈ.�ҿ︶����. ���� ���˻�.
		{
			sy += Height*0.8f;
		}
		else if(Type == ITEM_ARMOR+15)
		{
			sy += Height * 1.0f;
		}
		else
		{
			sy += Height*0.8f;
		}
	}
	else if(Type>=ITEM_PANTS && Type<ITEM_BOOTS+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		sy += Height*0.9f;
	}
	else if ( Type==ITEM_HELPER+14 && (Level>>3)==1 )    //  ������ ����.
	{
		sx += Width*0.55f;
		sy += Height*0.85f;
	}
	else if( Type==ITEM_HELPER+14 || Type==ITEM_HELPER+15 )
	{
		sx += Width*0.6f;
		sy += Height*1.f;
	}
	else if(Type==ITEM_HELPER+16 || Type==ITEM_HELPER+17)
	{
		sx += Width*0.5f;
		sy += Height*0.9f;
	}
	else if(Type==ITEM_HELPER+18)
	{
		sx += Width*0.5f;
		sy += Height*0.75f;
	}
	else if(Type==ITEM_HELPER+19)
	{
		switch ( Level>>3 )
		{
		case 0: sx += Width*0.5f; sy += Height*0.5f; break; //  ��õ���� ����������.
		case 1: sx += Width*0.7f; sy += Height*0.8f; break; //  ��õ���� �����.
		case 2: sx += Width*0.7f; sy += Height*0.7f; break; //  ��õ���� ���뼮��.
		}
	}
	else if( Type == ITEM_HELPER+20 )
	{
		switch( Level>>3 )
		{
		case 0: sx += Width*0.5f; sy+= Height*0.65f; break;  // �������� ����
		case 1: // ������ ����
		case 2: // ������ ����
		case 3: // ������ ����.
			sx += Width*0.5f; sy+= Height*0.8f; break;
		}
	}
	else if ( Type==ITEM_HELPER+29 )	//. �������� ���ʼ�Ʈ
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if ( Type==ITEM_HELPER+4 )
	{
		sx += Width*0.5f;
		sy += Height*0.6f;
	}
	else if ( Type==ITEM_HELPER+30 )    //  ����.
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if ( Type==ITEM_HELPER+31 )    //  ��ȥ.
	{
		sx += Width*0.5f;
		sy += Height*0.9f;
	}
	else if ( Type==ITEM_POTION+7 )//���ƹ���
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if ( Type==ITEM_HELPER+7 )
	{
		sx += Width*0.5f;
		sy += Height*0.9f;
	}
	else if ( Type==ITEM_HELPER+11 )
	{
		switch ( Level>>3 )
		{
		case 0: sx += Width*0.5f; sy += Height*0.8f; break;
		case 1: sx += Width*0.5f; sy += Height*0.5f; break;
		}
	}
	//^ �渱 �κ��丮 ��ġ ����
	else if(Type == ITEM_HELPER+32)	// ���� ����
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type == MODEL_HELPER+33)	// ������ ��ȣ
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type == MODEL_HELPER+34)	// �ͼ��� ����
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type == MODEL_HELPER+35)	// ���Ǹ��� ����
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type == MODEL_HELPER+36)	// �η��� ���Ǹ�
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type == MODEL_HELPER+37)	// �渱�� ���Ǹ�
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type>=ITEM_HELPER && Type<ITEM_HELPER+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		sy += Height*0.7f;
	}
	else if(Type==ITEM_POTION+12)
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type==ITEM_POTION+11 && ((Level>>3) == 3 || (Level>>3) == 13))	// ����� ��Ʈ, ��ũ�ε��� ����
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
#ifdef NEW_YEAR_BAG_EVENT
	else if ( Type==ITEM_POTION+11 && ( (Level>>3)==14 || (Level>>3)==15 ) )  //  �Ķ�, ���� ���ָӴ�
	{
		sx += Width*0.5f;
		sy += Height*0.8f;
	}
#else
#ifdef CHINA_MOON_CAKE
	else if ( Type==ITEM_POTION+11 && (Level>>3)==14 )  //  �߱� ����.
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
#endif// CHINA_MOON_CAKE
#endif// NEW_YEAR_BAG_EVENT
#ifdef MYSTERY_BEAD
	else if(Type==ITEM_WING+26 && (Level>>3) == 0)	//. �ź��Ǳ���
	{
		sx += Width*0.5f;
		sy += Height*0.8f;
	}
#endif // MYSTERY_BEAD
	else if(Type==ITEM_POTION+9 && (Level>>3) == 1)	// ����� �ø���
	{
		sx += Width*0.5f;
		sy += Height*0.8f;
	}
	else if(Type==ITEM_POTION+17 || Type==ITEM_POTION+18 || Type==ITEM_POTION+19)
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type==ITEM_POTION+21)
	{
		switch ( Level>>3 )
		{
		case 0: sx += Width*0.5f; sy += Height*0.5f; break; //  ����.
		case 1: sx += Width*0.4f; sy += Height*0.8f; break; //  ����.
#ifdef FRIEND_EVENT
		case 2: sx += Width*0.4f; sy += Height*0.8f; break; //  ������ ��.
#endif	// FRIEND_EVENT
		case 3: sx += Width*0.5f; sy += Height*0.5f; break; //  ������ǥ��
		}
	}
	else if ( Type>=ITEM_POTION+22 && Type<ITEM_POTION+25 )
	{
		if( Type==ITEM_POTION+24 && (Level>>3)==1 )
		{
			sx += Width*0.5f;
			sy += Height*0.8f;
		}
		else
		{
			sx += Width*0.5f;
			sy += Height*0.95f;
		}
	}
#ifdef HELLOWIN_EVENT
	else if (Type>=ITEM_POTION+46 && Type<=ITEM_POTION+48 )
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
#endif//HELLOWIN_EVENT
	else if ( Type>=ITEM_POTION+25 && Type<ITEM_POTION+27 )
	{
		sx += Width*0.5f;
		sy += Height*0.9f;
	}
#ifdef _PVP_MURDERER_HERO_ITEM
	else if ( Type==ITEM_POTION+30 )	// ¡ǥ
	{
		sx += Width*0.6f;
		sy += Height*1.0f;
	}
#endif	// _PVP_MURDERER_HERO_ITEM
	else if(Type==ITEM_POTION+31)	// ��ȣ�Ǻ���
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type==INDEX_COMPILED_CELE || Type == INDEX_COMPILED_SOUL)
	{
		sx += Width*0.55f;
		sy += Height*0.8f;
	}
	//  �߰��Ǵ� ����.
	else if ( Type==ITEM_WING+3 )   //  ������ ����.
	{
		sx += Width*0.5f;
		sy += Height*0.45f;
	}
	else if ( Type==ITEM_WING+4 )   //  ��ȥ�� ����.
	{
		sx += Width*0.5f;
		sy += Height*0.4f;
	}
	else if ( Type==ITEM_WING+5 )   //  ���� ����.
	{
		sx += Width*0.5f;
		sy += Height*0.75f;
	}
	else if ( Type==ITEM_WING+6 )   //  ����� ����.
	{
		sx += Width*0.5f;
		sy += Height*0.55f;
	}
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	//����� ����
	else if(Type == ITEM_POTION+100)
	{
		sx += Width*0.49f;
		//sy += Height*0.28f;
		sy += Height*0.28f;
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008


#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// �κ��丮 ��ġ ����
	else if (COMGEM::Check_Jewel_Com(Type) != COMGEM::NOGEM)
	{
		sx += Width*0.55f;
		sy += Height*0.82f;
	}
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	else if(Type>=ITEM_POTION && Type<ITEM_POTION+MAX_ITEM_INDEX)
	{
		sx += Width*0.5f;
		sy += Height*0.95f;
	}
	else if((Type >= ITEM_WING+12 && Type <= ITEM_WING+14) || (Type >= ITEM_WING+16 && Type <= ITEM_WING+19))
	{
		sx += Width*0.5f;
		sy += Height*0.75f;
	}
#ifdef PBG_ADD_SANTAINVITATION
	//��Ÿ������ �ʴ���.
	else if( Type == ITEM_HELPER+66 )
	{
		sx += Width*1.5f;
		sy += Height*1.5f;
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type==ITEM_WING+49)
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
	else if(Type==ITEM_WING+50)
	{
		sx += Width*0.5f;
		sy += Height*0.5f;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else
	{
		sx += Width*0.5f;
		sy += Height*0.6f;
	}

#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	if(Type>=ITEM_SWORD+32 && Type<=ITEM_SWORD+34)
	{
		sx -= Width*0.25f;
		sy -= Height*0.25f;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

	vec3_t Position;
	CreateScreenVector((int)(sx),(int)(sy),Position, false);
	//RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,Position,Success,PickUp);
	if ( Type==ITEM_POTION+11 && ( Level>>3) == 1)	// ��ź�Ǻ�
	{
		RenderObjectScreen(MODEL_EVENT+4,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 2)	// ����/ ���� �ָӴ�.
	{
		RenderObjectScreen(MODEL_EVENT+5,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#ifdef ANNIVERSARY_EVENT
	else if ( Type==ITEM_POTION+20 && ( Level>>3) >= 1 && ( Level>>3) <= 5)	// �ִϹ����� �ڽ�
	{
		RenderObjectScreen(MODEL_POTION+11,(7 << 3),Option1,ExtOption,Position,Success,PickUp);
	}
#endif	// ANNIVERSARY_EVENT
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 3)	// ����� ��Ʈ
	{
		RenderObjectScreen(MODEL_EVENT+6,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 5)	// ������
	{
		RenderObjectScreen(MODEL_EVENT+8,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 6)	// ������
	{
		RenderObjectScreen(MODEL_EVENT+9,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#ifdef USE_EVENT_ELDORADO
	else if ( Type==ITEM_POTION+11 && 8 <= ( Level>>3) && ( Level>>3) <= 12)	// ������
	{
		RenderObjectScreen(MODEL_EVENT+10,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#endif
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 13)	// ��ũ�ε��� ����
	{
		RenderObjectScreen(MODEL_EVENT+6,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#ifdef NEW_YEAR_BAG_EVENT
	else if ( Type==ITEM_POTION+11 && ( (Level>>3)==14 || (Level>>3)==15 ) )    //  ���ָӴ�
	{
		RenderObjectScreen(MODEL_EVENT+5,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#else
#ifdef CHINA_MOON_CAKE
	else if ( Type==ITEM_POTION+11 && ( Level>>3) == 14)	//  �߱� ����.
	{
		RenderObjectScreen(MODEL_EVENT+17,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#endif	//  CHINA_MOON_CAKE
#endif// NEW_YEAR_BAG_EVENT
	
	else if ( Type==ITEM_HELPER+14 && ( Level>>3) == 1)	// ������ �Ҹ�.
	{
		RenderObjectScreen ( MODEL_EVENT+16, Level, Option1, ExtOption, Position, Success, PickUp );
	}
	else if ( Type==ITEM_POTION+9 && ( Level>>3) == 1)	// ����� �ø���
	{
		RenderObjectScreen(MODEL_EVENT+7,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type==ITEM_POTION+21 )
	{
		switch ( (Level>>3) )
		{
		case 1:
			RenderObjectScreen(MODEL_EVENT+11,Level,Option1,ExtOption,Position,Success,PickUp);   //  ����.
			break;
#ifdef FRIEND_EVENT
		case 2:
			RenderObjectScreen(MODEL_EVENT+11,Level,Option1,ExtOption,Position,Success,PickUp); //  ������ ��.
			break;
#endif// FRIEND_EVENT
		case 3:
			RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		default:
			RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		}
	}
#ifdef HELLOWIN_EVENT
	else if ( Type ==ITEM_POTION+45)
	{
		RenderObjectScreen(MODEL_POTION+45,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type >=ITEM_POTION+46 && Type <=ITEM_POTION+48)
	{
		RenderObjectScreen(MODEL_POTION+46,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type ==ITEM_POTION+49)
	{
		RenderObjectScreen(MODEL_POTION+49,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if ( Type ==ITEM_POTION+50)
	{
		RenderObjectScreen(MODEL_POTION+50,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	else if ( Type ==ITEM_POTION+32)
	{
		switch ( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(MODEL_POTION+32,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
			RenderObjectScreen(MODEL_EVENT+21,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		}
	}
	else if ( Type ==ITEM_POTION+33)
	{
		switch ( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(MODEL_POTION+33,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
			RenderObjectScreen(MODEL_EVENT+22,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		}
	}
	else if ( Type ==ITEM_POTION+34)
	{
		switch ( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(MODEL_POTION+34,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
			RenderObjectScreen(MODEL_EVENT+23,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		}
	}
	
#endif
	
#ifdef MYSTERY_BEAD
	else if ( Type ==ITEM_WING+26)
	{
		switch ( (Level>>3) )
		{
		case 0:		//. �ź��� ����
			RenderObjectScreen(MODEL_EVENT+19,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
		case 2:
		case 3:
			RenderObjectScreen(MODEL_EVENT+20,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 4:
			RenderObjectScreen(MODEL_POTION+11,4<<3,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 5:
			RenderObjectScreen(MODEL_POTION+11,7<<3,Option1,ExtOption,Position,Success,PickUp);
			break;
		}
	}
#endif // MYSTERY_BEAD
	else if ( Type==ITEM_HELPER+19)     //  ��õ���� ���� ���� �ø���.
	{
		switch ( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(MODEL_STAFF+10,-1,Option1,ExtOption,Position,Success,PickUp);   //  ��õ���� ����������.
			break;
		case 1:
			RenderObjectScreen(MODEL_SWORD+19,-1,Option1,ExtOption,Position,Success,PickUp);   //  ��õ���� �����.
			break;
		case 2:
			RenderObjectScreen(MODEL_BOW+18,-1,Option1,ExtOption,Position,Success,PickUp);   //  ��õ���� ���뼮��.
			break;
		}
	}
	else if ( Type==ITEM_POTION+23)
	{
		switch( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
			RenderObjectScreen(MODEL_EVENT+12,-1,Option1,ExtOption,Position,Success,PickUp);   //. ������ ����
			break;
		}
	}
	else if ( Type==ITEM_POTION+24)
	{
		switch( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,ExtOption,Position,Success,PickUp);
			break;
		case 1:
			RenderObjectScreen(MODEL_EVENT+13,-1,Option1,ExtOption,Position,Success,PickUp);   //. ��ũ����
			break;
		}
	}
	else if ( Type==ITEM_HELPER+20)
	{
		switch( (Level>>3) )
		{
		case 0:
			RenderObjectScreen(MODEL_EVENT+15,Level,Option1,ExtOption,Position,Success,PickUp);	// �������� ����
			break;
		case 1:
		case 2: //  ������ ����.
		case 3: //  ������ ����.
			RenderObjectScreen(MODEL_EVENT+14,Level,Option1,ExtOption,Position,Success,PickUp);	//. ������ ����
			break;
		}
	}
	else if ( Type==ITEM_HELPER+11 && (Level>>3)==1 )
	{
		RenderObjectScreen ( MODEL_EVENT+18,Level,Option1,ExtOption,Position,Success,PickUp);	//  ������ ����.
	}
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	else if(Type == ITEM_POTION+100)
	{
		bool _Angle;
		if(g_pLuckyCoinRegistration->GetItemRotation())
		{
			//���â �ȿ� �׷��� ������
			_Angle = true;
		}
		else
		{
			//��Ÿ �κ��� �׷��� ������
			_Angle = Success;
		}

		RenderObjectScreen(MODEL_POTION+100,Level,Option1,ExtOption,Position,_Angle,PickUp);	// ����� ����
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type == ITEM_ARMOR+59)
	{
		RenderObjectScreen(MODEL_ARMORINVEN_60,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if(Type == ITEM_ARMOR+60)
	{
		RenderObjectScreen(MODEL_ARMORINVEN_61,Level,Option1,ExtOption,Position,Success,PickUp);
	}
	else if(Type == ITEM_ARMOR+61)
	{
		RenderObjectScreen(MODEL_ARMORINVEN_62,Level,Option1,ExtOption,Position,Success,PickUp);
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else
	{
		RenderObjectScreen(Type+MODEL_ITEM,Level,Option1,ExtOption,Position,Success,PickUp);
	}
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮 Į�� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void InventoryColor(ITEM *p)
{
	switch(p->Color)
	{
	case 0:
		glColor3f(1.f,1.f,1.f);     //  ���� ����.
		break;
	case 1:
		glColor3f(0.8f,0.8f,0.8f);  //  
		break;
	case 2:
		glColor3f(0.6f,0.7f,1.f);
		break;
	case 3:
		glColor3f(1.f,0.2f,0.1f);   //  ��� �Ұ���.
		break;
	case 4:
		glColor3f(0.5f,1.f,0.6f);
		break;
    case 5:
		glColor4f(0.8f,0.7f,0.f,1.f);  //  ������ ���. 50%
        break;
    case 6:
		glColor4f(0.8f,0.5f,0.f,1.f);  //  ������ ���. 70%
        break;
    case 7:
		glColor4f(0.8f,0.3f,0.3f,1.f); //  ������ ���. 80%
        break;
    case 8:
		glColor4f(1.0f,0.f,0.f,1.f);    //  ������ ���. 100%
        break;
    case 99:
		glColor3f(1.f,0.2f,0.1f);       //  �ŷ� â���� ���.
        break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���â �ڽ� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderEqiupmentBox()
{
	int StartX = InventoryStartX;
	int StartY = InventoryStartY;
	float x,y,Width,Height;

	EnableAlphaTest();

	//helper
	Width=40.f;Height=40.f;x=15.f;y=46.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_HELPER]);
    RenderBitmap(BITMAP_INVENTORY+15,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
	//wing
	Width=60.f;Height=40.f;x=115.f;y=46.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WING]);
    RenderBitmap(BITMAP_INVENTORY+14,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
	if(GetBaseClass(CharacterAttribute->Class)!=CLASS_DARK)
	{
		//helmet
		Width=40.f;Height=40.f;x=75.f;y=46.f;
		InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_HELM]);
		RenderBitmap(BITMAP_INVENTORY+3,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
	}
    //armor upper
	Width=40.f;Height=60.f;x=75.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_ARMOR]);
    RenderBitmap(BITMAP_INVENTORY+4,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
    //armor lower
	//if(GetBaseClass(CharacterAttribute->Class) != CLASS_ELF)
	{
		Width=40.f;Height=40.f;x=75.f;y=152.f;
		InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_PANTS]);
		RenderBitmap(BITMAP_INVENTORY+5,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
	}
    //weapon right
	Width=40.f;Height=60.f;x=15.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT]);
    RenderBitmap(BITMAP_INVENTORY+6,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
    //weapon left
	Width=40.f;Height=60.f;x=134.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT]);
    RenderBitmap(BITMAP_INVENTORY+16,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
    //glove
#ifdef PBG_ADD_NEWCHAR_MONK
	if(GetBaseClass(CharacterAttribute->Class)!=CLASS_RAGEFIGHTER)
	{
#endif //PBG_ADD_NEWCHAR_MONK
	Width=40.f;Height=40.f;x=15.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_GLOVES]);
    RenderBitmap(BITMAP_INVENTORY+7,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
#ifdef PBG_ADD_NEWCHAR_MONK
	}
#endif //PBG_ADD_NEWCHAR_MONK
    //boot
	Width=40.f;Height=40.f;x=134.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_BOOTS]);
    RenderBitmap(BITMAP_INVENTORY+8,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/64.f,Height/64.f);
    //necklace
	Width=20.f;Height=20.f;x=55.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_AMULET]);
    RenderBitmap(BITMAP_INVENTORY+9,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/32.f,Height/32.f);
    //ring
	Width=20.f;Height=20.f;x=55.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT]);
    RenderBitmap(BITMAP_INVENTORY+10,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/32.f,Height/32.f);
    //ring
	Width=20.f;Height=20.f;x=115.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_RING_LEFT]);
    RenderBitmap(BITMAP_INVENTORY+10,x+StartX,y+StartY,Width,Height,0.f,0.f,Width/32.f,Height/32.f);
}

///////////////////////////////////////////////////////////////////////////////
// ���â�� ������ �Ѱ� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderEqiupmentPart3D(int Index,float sx,float sy,float Width,float Height)
{
	ITEM *p = &CharacterMachine->Equipment[Index];
	if(p->Type != -1)
	{
		if(p->Number > 0)
            RenderItem3D(sx,sy,Width,Height,p->Type,p->Level,p->Option1,p->ExtOption,false);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���â�� ������ ��� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderEqiupment3D()
{
#ifdef MR0
	VPManager::Enable();
#endif //MR0

	int StartX = InventoryStartX;
	int StartY = InventoryStartY;
	float x,y,Width,Height;

	//helper
	Width=40.f;Height=40.f;x=15.f;y=46.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_HELPER]);
	RenderEqiupmentPart3D(EQUIPMENT_HELPER,StartX+x,StartY+y,Width,Height);
	//wing
	Width=60.f;Height=40.f;x=115.f;y=46.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WING]);
	RenderEqiupmentPart3D(EQUIPMENT_WING,StartX+x,StartY+y,Width,Height);
    //helmet
	Width=40.f;Height=40.f;x=75.f;y=46.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_HELM]);
	RenderEqiupmentPart3D(EQUIPMENT_HELM,StartX+x,StartY+y,Width,Height);
    //armor upper
	Width=40.f;Height=60.f;x=75.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_ARMOR]);
	RenderEqiupmentPart3D(EQUIPMENT_ARMOR,StartX+x,StartY+y-10,Width,Height);
    //armor lower
	//if(GetBaseClass(CharacterAttribute->Class) != CLASS_ELF)
	{
		Width=40.f;Height=40.f;x=75.f;y=152.f;
		InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_PANTS]);
		RenderEqiupmentPart3D(EQUIPMENT_PANTS,StartX+x,StartY+y,Width,Height);
	}
    //weapon right
	Width=40.f;Height=60.f;x=15.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT]);
	RenderEqiupmentPart3D(EQUIPMENT_WEAPON_RIGHT,StartX+x,StartY+y,Width,Height);
    //weapon left
	Width=40.f;Height=60.f;x=134.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT]);
	RenderEqiupmentPart3D(EQUIPMENT_WEAPON_LEFT,StartX+x,StartY+y,Width,Height);
    //glove
	Width=40.f;Height=40.f;x=15.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_GLOVES]);
	RenderEqiupmentPart3D(EQUIPMENT_GLOVES,StartX+x,StartY+y,Width,Height);
    //boot
	Width=40.f;Height=40.f;x=134.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_BOOTS]);
	RenderEqiupmentPart3D(EQUIPMENT_BOOTS,StartX+x,StartY+y,Width,Height);
    //necklace
	Width=20.f;Height=20.f;x=55.f;y=89.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_AMULET]);
	RenderEqiupmentPart3D(EQUIPMENT_AMULET,StartX+x,StartY+y,Width,Height);
    //ring
	Width=20.f;Height=20.f;x=55.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT]);
	RenderEqiupmentPart3D(EQUIPMENT_RING_RIGHT,StartX+x,StartY+y,Width,Height);
    //ring
	Width=20.f;Height=20.f;x=115.f;y=152.f;
    InventoryColor(&CharacterMachine->Equipment[EQUIPMENT_RING_LEFT]);
	RenderEqiupmentPart3D(EQUIPMENT_RING_LEFT,StartX+x,StartY+y,Width,Height);

#ifdef MR0
	VPManager::Disable();
#endif //MR0	
}

///////////////////////////////////////////////////////////////////////////////
// �ι��丮 ��ư�� ó���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

bool CheckEmptyInventory(ITEM *Inv,int InvWidth,int InvHeight)
{
	bool Empty = true;
	for(int y=0;y<InvHeight;y++)
	{
		for(int x=0;x<InvWidth;x++)
		{
			int Index  = y*InvWidth+x;
			ITEM *p = &Inv[Index];
			if(p->Type!=-1 && p->Number>0)
			{
				Empty = false;
			}
		}
	}
	return Empty;
}

///////////////////////////////////////////////////////////////////////////////
//  ��Ƽâ �������̽�.
///////////////////////////////////////////////////////////////////////////////
void InitPartyList ()
{
    PartyNumber = 0;
    PartyKey = 0;
}

//////////////////////////////////////////////////////////////////////////
//  ���� ���� �������̽�.
//////////////////////////////////////////////////////////////////////////
void MoveServerDivisionInventory ()
{
    if ( !g_pUIManager->IsOpen(INTERFACE_SERVERDIVISION) ) return;
    int x = 640-190;
    int y = 0;
    int Width, Height;

	if( MouseX>=(int)(x) && MouseX<(int)(x+190) && 
		MouseY>=(int)(y) && MouseY<(int)(y+256+177) )
    {
		MouseOnWindow = true;
    }

    //  ����.
    Width = 16; Height = 16; x = InventoryStartX+25;y = 240;
	if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height && MouseLButtonPush )
    {
        g_bServerDivisionAccept ^= true;

        MouseLButtonPush = false;
        MouseLButton = false;
    }

    //  Ȯ�� ��ư.
    if ( g_bServerDivisionAccept )
    {
        Width = 120; Height = 24; x = (float)InventoryStartX+35;y = 320;
	    if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height && MouseLButtonPush )
        {
            MouseLButtonPush = false;
            MouseLButton = false;

            AskYesOrNo =  4;
            OkYesOrNo  = -1;

            //  �������� Ȯ��â.
            ShowCheckBox(1, 448, MESSAGE_CHECK );
        }
    }

    //  ���.
    Width = 120; Height = 24; x = (float)InventoryStartX+35;y = 350;
	if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height && MouseLButtonPush )
    {
        MouseLButtonPush = false;
        MouseLButton = false;
        MouseUpdateTime = 0;
		MouseUpdateTimeMax = 6;

        SendExitInventory();
		g_pUIManager->CloseAll();
    }
    
    //  �ݱ� ��ư.
    Width=24;Height=24;x=InventoryStartX+25;y=InventoryStartY+395;
	if(MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height)
	{
		if(MouseLButtonPush)
		{
			MouseLButtonPush = false;
			MouseUpdateTime = 0;
			MouseUpdateTimeMax = 6;

            g_bEventChipDialogEnable = EVENT_NONE;

			SendExitInventory();
			g_pUIManager->CloseAll();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//  â�� ���/������ ���� Ű�е�â
///////////////////////////////////////////////////////////////////////////////

void HideKeyPad( void)
{
	g_iKeyPadEnable = 0;
}

int CheckMouseOnKeyPad( void)
{
	// 1. Ʋ
	int Width, Height, WindowX, WindowY;
    Width = 213;Height = 2*5+6*40;WindowX = (640-Width)/2;WindowY = 60+40;//60 220
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int yPos = WindowY;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	int iButtonTop = 50;
	// ���� ( 0 - 10)
	for ( int i = 0; i < 11; ++i)
	{
		int xButton = i % 5;
		int yButton = i / 5;

		int xLeft = WindowX + 10 + xButton * 40;
		int yTop = WindowY + iButtonTop + yButton * 40;
		if ( xLeft <= MouseX && MouseX < xLeft + 32 &&
			yTop <= MouseY && MouseY < yTop + 32)
		{
			return ( i);
		}
	}
	// Ok, Cancel ( 11 - 12)
	int yTop = WindowY + iButtonTop + 2 * 40 + 5;
#ifdef _VS2008PORTING
	for ( int i = 0; i < 2; ++i)
#else // _VS2008PORTING
	for ( i = 0; i < 2; ++i)
#endif // _VS2008PORTING
	{
		int xLeft = WindowX + 52 + i * 78;
		if ( xLeft <= MouseX && MouseX < xLeft + 70 &&
			yTop <= MouseY && MouseY < yTop + 21)
		{
			return ( 11 + i);
		}
	}

	return ( -1);
}

bool g_bPadPushed = false;

void MovePersonalShop()
{
	if((g_pUIManager->IsOpen(INTERFACE_PERSONALSHOPSALE) || g_pUIManager->IsOpen(INTERFACE_PERSONALSHOPPURCHASE)) && g_iPShopWndType == PSHOPWNDTYPE_SALE)		//. �Ǹ��� ���
	{
		if(g_iPersonalShopMsgType == 1)		//. ���� Ÿ��Ʋ ����
		{
			if(OkYesOrNo == 1) {				//. Ok
				g_iPersonalShopMsgType = 0;
				OkYesOrNo = -1;
			}
			else if(OkYesOrNo == 2) {			//. Cancel
				g_iPersonalShopMsgType = 0;
				OkYesOrNo = -1;
			}
		}
		g_ptPersonalShop.x = 640-190*2;
		g_ptPersonalShop.y = 0;

		int Width = 56, Height = 24;
		int ButtonX = g_ptPersonalShop.x + 30, ButtonY = g_ptPersonalShop.y + 396;
		if(MouseX>=ButtonX && MouseX<ButtonX+Width && MouseY>=ButtonY && MouseY<ButtonY+Height && MouseLButtonPush)
		{
			//. ���� ��Ŷ ������
			MouseLButtonPush = false;
			if(!IsExistUndecidedPrice() && strlen(g_szPersonalShopTitle) > 0) 
			{
				if(g_bEnablePersonalShop) 
				{
					SendRequestCreatePersonalShop(g_szPersonalShopTitle);
					g_pUIManager->Close( INTERFACE_INVENTORY );
				}
				else 
				{
					SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CPersonalshopCreateMsgBoxLayout));
				}
			}
			else 
			{
				g_pChatListBox->AddText("", GlobalText[1119], SEASON3B::TYPE_ERROR_MESSAGE);
			}
		}
		
		ButtonX = g_ptPersonalShop.x + 105;
		if(MouseX>=ButtonX && MouseX<ButtonX+Width && MouseY>=ButtonY && MouseY<ButtonY+Height && MouseLButtonPush){
			//. ���� ��Ŷ ������
			MouseLButtonPush = false;
			if(g_bEnablePersonalShop) 
			{
				SendRequestDestoryPersonalShop();
			}
		}

		//. ����Ÿ��Ʋ ����
		Width = 150;
		ButtonX = g_ptPersonalShop.x + 20;
		ButtonY = g_ptPersonalShop.y + 65;
		if(MouseX>=ButtonX && MouseX<ButtonX+Width && MouseY>=ButtonY && MouseY<ButtonY+Height && MouseLButtonPush)
		{
			OpenPersonalShopMsgWnd(1);
		}
	}
}

void ClosePersonalShop()
{
	if(g_iPShopWndType == PSHOPWNDTYPE_PURCHASE) 
	{	//. ������ ����϶�
		//. �� ���λ��� ������ �����Ѵ�.
		memcpy(g_PersonalShopInven, g_PersonalShopBackup, sizeof(ITEM)*MAX_PERSONALSHOP_INVEN);
		if(IsShopInViewport(Hero)) 
		{	//. ������ ���� �������϶� ���� Ÿ��Ʋ�� �����Ѵ�.
			std::string title;
			GetShopTitle(Hero, title);
			strcpy(g_szPersonalShopTitle, title.c_str());
		}
		else 
		{
			g_szPersonalShopTitle[0] = '\0';
		}
		if(g_PersonalShopSeller.Key)
		{
			SendRequestClosePersonalShop(g_PersonalShopSeller.Key, g_PersonalShopSeller.ID);
		}
	}
	
	g_PersonalShopSeller.Initialize();
	
	g_iPShopWndType = PSHOPWNDTYPE_NONE;
}
void ClearPersonalShop()
{
	g_bEnablePersonalShop = false;
	g_iPShopWndType = PSHOPWNDTYPE_NONE;
	g_iPersonalShopMsgType = 0;
	g_szPersonalShopTitle[0] = '\0';

	RemoveAllShopTitle();
}

bool IsExistUndecidedPrice()
{
	bool bResult = true;

	for(int i=0; i<MAX_PERSONALSHOP_INVEN; ++i) 
	{
		int iPrice = 0;
		int iIndex;
		ITEM* pItem = g_pMyShopInventory->FindItem(i);
		if(pItem)
		{
			bResult = false;

			iIndex = MAX_MY_INVENTORY_INDEX + (pItem->y*COL_PERSONALSHOP_INVEN)+pItem->x;
			if(GetPersonalItemPrice(iIndex, iPrice, g_IsPurchaseShop) == false)
			{
				return true;
			}	

			if(iPrice <= 0)
			{
				return true;
			}
		}
		else
		{
			continue;
		}
	}

	return bResult;
}

void OpenPersonalShopMsgWnd(int iMsgType)
{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Width = 213; int Height = 2*5+6*40;
	int WindowX = (640-Width)/2; int WindowY = 60+40;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	if(iMsgType == 1) 
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CPersonalShopNameMsgBoxLayout));
	}
	else if(iMsgType == 2) 
	{
		SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CPersonalShopItemValueMsgBoxLayout));
	}
}
bool IsCorrectShopTitle(const char* szShopTitle)
{
	//  ������ ������ ���ڿ��� �����.
#ifdef _VS2008PORTING
	int j=0;
	char TmpText[2048];
	for( int i=0; i<(int)strlen(szShopTitle); ++i )
	{
		if ( szShopTitle[i]!=32 )
		{
			TmpText[j] = szShopTitle[i];
			j++;
		}
	}
	TmpText[j] = 0;

	for( int i=0;i<AbuseFilterNumber;i++ )
#else // _VS2008PORTING
    int i, j;
    char TmpText[2048];
    for( i=0, j=0; i<(int)strlen(szShopTitle); ++i )
    {
        if ( szShopTitle[i]!=32 )
        {
            TmpText[j] = szShopTitle[i];
            j++;
        }
    }
    TmpText[j] = 0;

	for( i=0;i<AbuseFilterNumber;i++)
#endif // _VS2008PORTING
	{
		if(FindText(TmpText,AbuseFilter[i]))
		{
			return false;
		}
	}
	
	int len = strlen(szShopTitle);
	int count = 0;
#ifdef _VS2008PORTING
	for(int i=0; i<len; i++)
#else // _VS2008PORTING
	for(i=0; i<len; i++)
#endif // _VS2008PORTING
	{
		if(szShopTitle[i] == 0x20) { 
			count++; 
			if(i==1 && count>=2) return false;
		}
		else { 
			count = 0;
		}
	}
	if(count >= 2)
		return false;
	return true;
}

#ifndef YDG_ADD_NEW_DUEL_SYSTEM		// �����Ҷ� �����ؾ� ��
void ClearDuelWindow()
{
	g_bEnableDuel = false;
	g_iMyPlayerScore = 0;
	g_iDuelPlayerScore = 0;
}
#endif	// YDG_ADD_NEW_DUEL_SYSTEM	// �����Ҷ� �����ؾ� ��

///////////////////////////////////////////////////////////////////////////////
//  �κ��丮 ó���Լ�.
///////////////////////////////////////////////////////////////////////////////

extern DWORD g_dwActiveUIID;
extern DWORD g_dwMouseUseUIID;		// ���콺�� ������ ���� �ִ°� (������ ������ ID)

///////////////////////////////////////////////////////////////////////////////
// �ι��丮 ��׶��� �׸� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderInventoryInterface(int StartX,int StartY,int Flag)
{
	float x,y,Width,Height; 
	Width=190.f;Height=256.f;x=(float)StartX;y=(float)StartY;

    RenderBitmap(BITMAP_INVENTORY  ,x,y,Width,Height,0.f,0.f,Width/256.f,Height/256.f);

	Width=190.f;Height=177.f;x=(float)StartX;y=(float)StartY+256;
	RenderBitmap(BITMAP_INVENTORY+1,x,y,Width,Height,0.f,0.f,Width/256.f,Height/256.f);

	if(Flag)
	{
		Width=190.f;Height=10.f;x=(float)StartX;y=(float)StartY+225;
		RenderBitmap(BITMAP_INVENTORY+19,x,y,Width,Height,0.f,0.f,Width/256.f,Height/16.f);
	}
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��� ����â �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
extern  int  ServerSelectHi;
extern  int  ServerLocalSelect;
#endif // KJH_ADD_SERVER_LIST_SYSTEM


///////////////////////////////////////////////////////////////////////////////
// ��Ƽ ����Ʈâ �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

const char* GetMapName( int iMap)
{
	if(iMap == WD_34CRYWOLF_1ST)
	{
		return( GlobalText[1851]);
	}
	else if( iMap == WD_33AIDA )
	{
		return( GlobalText[1850]);
	}
	else if( iMap == WD_37KANTURU_1ST )
	{
		return( GlobalText[2177]);
	}
	else if( iMap == WD_38KANTURU_2ND )
	{
		return( GlobalText[2178]);
	}
	else if( iMap == WD_39KANTURU_3RD )
	{
		return( GlobalText[2179]);
	}
	else if( iMap == WD_40AREA_FOR_GM)
	{
		return( GlobalText[2324]);
	}
	else if( iMap == WD_51HOME_6TH_CHAR)
	{
		return( GlobalText[1853]);
	}
#ifdef CSK_RAKLION_BOSS
	else if(iMap == WD_57ICECITY)
	{
		return( GlobalText[1855]);	// 1855 "��Ŭ����"
	}
	else if(iMap == WD_58ICECITY_BOSS)
	{
		return( GlobalText[1856]);	// 1856 "��ȭ��"
	}
#endif // CSK_RAKLION_BOSS

	
    if ( battleCastle::InBattleCastle( iMap )==true )
    {
        return ( GlobalText[669] );
    }
    if ( iMap == WD_31HUNTING_GROUND )
    {
        return ( GlobalText[59] );
    }
    if ( InChaosCastle( iMap )==true )
    {
        return ( GlobalText[57] );
    }
    if ( InHellas( iMap )==true )
    {
		if (InHiddenHellas( iMap) == true)
			return ( GlobalText[1852] );
        return ( GlobalText[58] );
    }
	if ( InBloodCastle( iMap ) == true )
	{
		return ( GlobalText[56] );
	}
	if ( iMap==WD_10HEAVEN )
	{
		return ( GlobalText[55+iMap-WD_10HEAVEN]);
	}
	if ( iMap==32 )
	{
		return ( GlobalText[39]);
	}
	if (SEASON3A::CGM3rdChangeUp::Instance().IsBalgasBarrackMap())
		return GlobalText[1678];
	else if (SEASON3A::CGM3rdChangeUp::Instance().IsBalgasRefugeMap())
		return GlobalText[1679];
	if( g_CursedTemple->IsCursedTemple() )
	{
		return ( GlobalText[2369] );
	}
	if( iMap == WD_51HOME_6TH_CHAR )
	{
		return ( GlobalText[1853] );		// 1853 "��������"
	}
	if( iMap == WD_56MAP_SWAMP_OF_QUIET )
	{
		return ( GlobalText[1854] );		// 1854 "����� ��"
	}
#ifdef YDG_ADD_MAP_SANTA_TOWN
	if( iMap == WD_62SANTA_TOWN )
	{
		return ( GlobalText[2611] );		// 2611 "��Ÿ�� ����"
	}
#endif	// YDG_ADD_MAP_SANTA_TOWN
#ifdef YDG_ADD_MAP_DUEL_ARENA
	if( iMap == WD_64DUELARENA)
	{
		return ( GlobalText[2703] );		// 2703 "������"
	}
#endif	// YDG_ADD_MAP_DUEL_ARENA
#ifdef PBG_ADD_PKFIELD
	if( iMap == WD_63PK_FIELD)
	{
		return (GlobalText[2686]);			// 2686 "��ī����"
	}
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER1
	if( iMap == WD_65DOPPLEGANGER1)
	{
		return (GlobalText[3057]);
	}
#endif	// YDG_ADD_MAP_DOPPELGANGER1
#ifdef YDG_ADD_MAP_DOPPELGANGER2
	if( iMap == WD_66DOPPLEGANGER2)
	{
		return (GlobalText[3057]);
	}
#endif	// YDG_ADD_MAP_DOPPELGANGER2
#ifdef YDG_ADD_MAP_DOPPELGANGER3
	if( iMap == WD_67DOPPLEGANGER3)
	{
		return (GlobalText[3057]);
	}
#endif	// YDG_ADD_MAP_DOPPELGANGER3
#ifdef YDG_ADD_MAP_DOPPELGANGER4
	if( iMap == WD_68DOPPLEGANGER4)
	{
		return (GlobalText[3057]);
	}
#endif	// YDG_ADD_MAP_DOPPELGANGER4
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN1
	if( iMap == WD_69EMPIREGUARDIAN1)
	{
		return (GlobalText[2806]);
	}
#endif //LDK_ADD_MAP_EMPIREGUARDIAN1
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN2
	if( iMap == WD_70EMPIREGUARDIAN2)
	{
		return (GlobalText[2806]);
	}
#endif //LDS_ADD_MAP_EMPIREGUARDIAN2
#ifdef LDK_ADD_MAP_EMPIREGUARDIAN3
	if( iMap == WD_71EMPIREGUARDIAN3)
	{
		return (GlobalText[2806]);
	}
#endif //LDK_ADD_MAP_EMPIREGUARDIAN3
#ifdef LDS_ADD_MAP_EMPIREGUARDIAN4
	if( iMap == WD_72EMPIREGUARDIAN4)
	{
		return (GlobalText[2806]);
	}
#endif //LDS_ADD_MAP_EMPIREGUARDIAN4
#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
	if( iMap == WD_79UNITEDMARKETPLACE )
	{
		return (GlobalText[3017]);
	}
#endif // LDS_ADD_MAP_UNITEDMARKETPLACE
#ifdef ASG_ADD_MAP_KARUTAN
	if (iMap == WD_80KARUTAN1 || iMap == WD_81KARUTAN2)
		return (GlobalText[3285]);
#endif	// ASG_ADD_MAP_KARUTAN
	
	return ( GlobalText[30+iMap] );
}

#ifdef ASG_ADD_GENS_SYSTEM
// ���������ΰ�?
bool IsStrifeMap(int nMapIndex)
{
	bool bStrifeMap = false;

	if (BLUE_MU::IsBlueMuServer())	// �κ� ����ȭ �����ΰ�?
	{
		ENUM_WORLD aeStrife[5] = { WD_7ATLANSE, WD_33AIDA, WD_37KANTURU_1ST, WD_56MAP_SWAMP_OF_QUIET, WD_63PK_FIELD };
		int i;
		for (i = 0; i < 5; ++i)
		{
			if (aeStrife[i] == nMapIndex)
			{
				bStrifeMap = true;
				break;
			}
		}
	}
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	else if (!g_ServerListManager->IsNonPvP())	// PVP �����ΰ�?
#else // KJH_ADD_SERVER_LIST_SYSTEM
	else if (!::IsNonPvpServer(ServerSelectHi, ServerLocalSelect))	// PVP �����ΰ�?
#endif // KJH_ADD_SERVER_LIST_SYSTEM
	{
		ENUM_WORLD aeStrife[1] = { WD_63PK_FIELD };
		int i;
		for (i = 0; i < 1; ++i)
		{
			if (aeStrife[i] == nMapIndex)
			{
				bStrifeMap = true;
				break;
			}
		}
	}

	return bStrifeMap;
}
#endif	// ASG_ADD_GENS_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// ��帶ũ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

unsigned int MarkColor[16];

void CreateGuildMark( int nMarkIndex, bool blend )
{
	BITMAP_t *b = &Bitmaps[BITMAP_GUILD];
#ifdef _VS2008PORTING
	int Width,Height;
#else // _VS2008PORTING
	int i,j,Width,Height;
#endif // _VS2008PORTING
	Width  = (int)b->Width;
	Height = (int)b->Height;
	BYTE *Buffer = b->Buffer;
    int alpha = 128;
    if( blend )
    {
        alpha = 0;
    }

#ifdef _VS2008PORTING
	for(int i=0;i<16;i++)
#else // _VS2008PORTING
	for(i=0;i<16;i++)
#endif // _VS2008PORTING
	{
		switch(i)
		{
		case 0 :MarkColor[i] = (alpha<<24)+(0<<16)+(  0<<8)+(  0);break;
		case 1 :MarkColor[i] = (255<<24)+(  0<<16)+(  0<<8)+(  0);break;
		case 2 :MarkColor[i] = (255<<24)+(128<<16)+(128<<8)+(128);break;
		case 3 :MarkColor[i] = (255<<24)+(255<<16)+(255<<8)+(255);break;
		case 4 :MarkColor[i] = (255<<24)+(  0<<16)+(  0<<8)+(255);break;//��
		case 5 :MarkColor[i] = (255<<24)+(  0<<16)+(128<<8)+(255);break;//
		case 6 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(255);break;//��
		case 7 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(128);break;//
		case 8 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(  0);break;//��
		case 9 :MarkColor[i] = (255<<24)+(128<<16)+(255<<8)+(  0);break;//
		case 10:MarkColor[i] = (255<<24)+(255<<16)+(255<<8)+(  0);break;//û
		case 11:MarkColor[i] = (255<<24)+(255<<16)+(128<<8)+(  0);break;//
		case 12:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(  0);break;//��
		case 13:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(128);break;//
		case 14:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(255);break;//��
		case 15:MarkColor[i] = (255<<24)+(128<<16)+(  0<<8)+(255);break;//
		}
	}
	BYTE *MarkBuffer = GuildMark[nMarkIndex].Mark;
#ifdef _VS2008PORTING
	for(int i=0;i<Height;i++)
	{
		for(int j=0;j<Width;j++)
		{
			*((unsigned int *)(Buffer)) = MarkColor[MarkBuffer[0]];
			Buffer += 4;
			MarkBuffer++;
		}
	}
#else // _VS2008PORTING
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			*((unsigned int *)(Buffer)) = MarkColor[MarkBuffer[0]];
			Buffer += 4;
			MarkBuffer++;
		}
	}
#endif // _VS2008PORTING
	glBindTexture(GL_TEXTURE_2D,b->TextureNumber);

    glTexImage2D(GL_TEXTURE_2D,0,b->Components,Width,Height,0,GL_RGBA,GL_UNSIGNED_BYTE,b->Buffer);
}


void CreateCastleMark ( int Type, BYTE* buffer, bool blend )
{
    if ( buffer==NULL ) return;

	BITMAP_t *b = &Bitmaps[Type];
#ifdef _VS2008PORTING
	int Width,Height;
#else // _VS2008PORTING
	int i,j,Width,Height;
#endif // _VS2008PORTING
	Width  = (int)b->Width;
	Height = (int)b->Height;
	BYTE* Buffer = b->Buffer;

    int alpha = 128;
    if( blend )
    {
        alpha = 0;
    }

#ifdef _VS2008PORTING
	for(int i=0;i<16;i++)
#else // _VS2008PORTING
	for(i=0;i<16;i++)
#endif // _VS2008PORTING
	{
		switch(i)
		{
		case 0 :MarkColor[i] = (alpha<<24)+(0<<16)+(  0<<8)+(  0);break;
		case 1 :MarkColor[i] = (255<<24)+(  0<<16)+(  0<<8)+(  0);break;
		case 2 :MarkColor[i] = (255<<24)+(128<<16)+(128<<8)+(128);break;
		case 3 :MarkColor[i] = (255<<24)+(255<<16)+(255<<8)+(255);break;
		case 4 :MarkColor[i] = (255<<24)+(  0<<16)+(  0<<8)+(255);break;//��
		case 5 :MarkColor[i] = (255<<24)+(  0<<16)+(128<<8)+(255);break;//
		case 6 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(255);break;//��
		case 7 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(128);break;//
		case 8 :MarkColor[i] = (255<<24)+(  0<<16)+(255<<8)+(  0);break;//��
		case 9 :MarkColor[i] = (255<<24)+(128<<16)+(255<<8)+(  0);break;//
		case 10:MarkColor[i] = (255<<24)+(255<<16)+(255<<8)+(  0);break;//û
		case 11:MarkColor[i] = (255<<24)+(255<<16)+(128<<8)+(  0);break;//
		case 12:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(  0);break;//��
		case 13:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(128);break;//
		case 14:MarkColor[i] = (255<<24)+(255<<16)+(  0<<8)+(255);break;//��
		case 15:MarkColor[i] = (255<<24)+(128<<16)+(  0<<8)+(255);break;//
		}
	}
	BYTE MarkBuffer[32*32];

    int offset = 0;
#ifdef _VS2008PORTING
	for ( int i=0; i<32; ++i )
	{
		for ( int j=0; j<32; ++j )
		{
			offset = (j/4)+((i/4)*8);
			MarkBuffer[j+(i*32)] = buffer[offset];
		}
	}
#else // _VS2008PORTING
    for ( i=0; i<32; ++i )
    {
        for ( j=0; j<32; ++j )
        {
            offset = (j/4)+((i/4)*8);
            MarkBuffer[j+(i*32)] = buffer[offset];
        }
    }
#endif // _VS2008PORTING

    offset = 0;
    int offset2 = 0;
#ifdef _VS2008PORTING
	for ( int i=0; i<Height; ++i )
	{
		for ( int j=0; j<Width; ++j )
#else // _VS2008PORTING
    for ( i=0; i<Height; ++i )
	{
        for ( j=0; j<Width; ++j )
#endif // _VS2008PORTING
		{
            if ( j>=(Width/2-16) && j<(Width/2+16) && i>=(Height/2-16) && i<(Height/2+16) )
            {
			    *((unsigned int *)(Buffer+offset)) = MarkColor[MarkBuffer[offset2]];
                offset2++;
            }
            else if ( j<3 || j>(Width-4) || i<10 || i>(Height-10) )
            {
			    *((unsigned int *)(Buffer+offset)) = (255<<24)+(  0<<16)+((int)(50+i/100.f*160)<<8)+(50+i/100.f*255);
            }
            else
            {
			    *((unsigned int *)(Buffer+offset)) = (255<<24)+(  i<<16)+(i<<8)+(i);
            }
            offset += 4;
		}
	}
    glBindTexture(GL_TEXTURE_2D,b->TextureNumber);

    glTexImage2D(GL_TEXTURE_2D,0,3,Width,Height,0,GL_RGBA,GL_UNSIGNED_BYTE,b->Buffer);
}


///////////////////////////////////////////////////////////////////////////////
// ��帶ũ �׸��� Į�� �ڽ� �ϳ� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderGuildColor(float x,float y,int SizeX,int SizeY,int Index)
{
	RenderBitmap(BITMAP_INVENTORY+18,x-1,y-1,(float)SizeX+2,(float)SizeY+2,0.f,0.f,SizeX/32.f,SizeY/30.f);

	BITMAP_t *b = &Bitmaps[BITMAP_GUILD];
#ifdef _VS2008PORTING
	int Width,Height;
#else // _VS2008PORTING
	int i,j,Width,Height;
#endif // _VS2008PORTING
	Width  = (int)b->Width;
	Height = (int)b->Height;
	BYTE *Buffer = b->Buffer;
	unsigned int Color = MarkColor[Index];
#ifdef _VS2008PORTING
	if(Index==0)
	{
		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				*((unsigned int *)(Buffer)) = 255<<24;
				Buffer += 4;
			}
		}
		Color = (255<<24)+(128<<16)+(128<<8)+(128);
		Buffer = b->Buffer;
		for(int i=0;i<8;i++)
		{
			*((unsigned int *)(Buffer)) = Color;
			Buffer += 8*4+4;
		}
		Buffer = b->Buffer+7*4;
		for(int i=0;i<8;i++)
		{
			*((unsigned int *)(Buffer)) = Color;
			Buffer += 8*4-4;
		}
	}
	else
	{
		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				*((unsigned int *)(Buffer)) = Color;
				Buffer += 4;
			}
		}
	}
#else // _VS2008PORTING
	if(Index==0)
	{
		for(i=0;i<Height;i++)
		{
			for(j=0;j<Width;j++)
			{
				*((unsigned int *)(Buffer)) = 255<<24;
				Buffer += 4;
			}
		}
		Color = (255<<24)+(128<<16)+(128<<8)+(128);
     	Buffer = b->Buffer;
		for(i=0;i<8;i++)
		{
			*((unsigned int *)(Buffer)) = Color;
			Buffer += 8*4+4;
		}
     	Buffer = b->Buffer+7*4;
		for(i=0;i<8;i++)
		{
			*((unsigned int *)(Buffer)) = Color;
			Buffer += 8*4-4;
		}
	}
	else
	{
		for(i=0;i<Height;i++)
		{
			for(j=0;j<Width;j++)
			{
				*((unsigned int *)(Buffer)) = Color;
				Buffer += 4;
			}
		}
	}
#endif // _VS2008PORTING
	glBindTexture(GL_TEXTURE_2D,b->TextureNumber);

    glTexImage2D(GL_TEXTURE_2D,0,b->Components,Width,Height,0,GL_RGBA,GL_UNSIGNED_BYTE,b->Buffer);
    RenderBitmap(BITMAP_GUILD,x,y,(float)SizeX,(float)SizeY);
}

///////////////////////////////////////////////////////////////////////////////
// ��� ����Ʈâ �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderGuildList(int StartX,int StartY)
{
	GuildListStartX = StartX;
	GuildListStartY = StartY;

	glColor3f(1.f,1.f,1.f);

	DisableAlphaBlend();
	float x,y,Width,Height;
	Width=190.f;Height=256.f;x=(float)StartX;y=(float)StartY;
    RenderBitmap(BITMAP_INVENTORY  ,x,y,Width,Height,0.f,0.f,Width/256.f,Height/256.f);
	Width=190.f;Height=177.f;x=(float)StartX;y=(float)StartY+256;
    RenderBitmap(BITMAP_INVENTORY+1,x,y,Width,Height,0.f,0.f,Width/256.f,Height/256.f);

	EnableAlphaTest();

	g_pRenderText->SetBgColor(20, 20, 20, 255);
	g_pRenderText->SetTextColor(220, 220, 220, 255);
	g_pRenderText->SetFont(g_hFontBold);

	char Text[100];
	if(Hero->GuildMarkIndex == -1)
		sprintf(Text,GlobalText[180]);
	else
		sprintf(Text,"%s (Score:%d)",GuildMark[Hero->GuildMarkIndex].GuildName,GuildTotalScore);

	g_pRenderText->RenderText(StartX+95-60,StartY+12,Text,120*WindowWidth/640,true,3);

	g_pRenderText->SetBgColor(0);
    g_pRenderText->SetTextColor(230, 230, 230, 255);
	g_pRenderText->SetFont(g_hFont);

	if(g_nGuildMemberCount == 0)
	{
		g_pRenderText->RenderText(StartX+20,StartY+50 ,GlobalText[185]);
		g_pRenderText->RenderText(StartX+20,StartY+65 ,GlobalText[186]);
		g_pRenderText->RenderText(StartX+20,StartY+80 ,GlobalText[187]);
	}
	// ������
	g_pRenderText->SetBgColor(0, 0, 0, 128);
	g_pRenderText->SetTextColor(100, 255, 200, 255);
	g_pRenderText->RenderText(StartX+( int)Width/2,StartY+44,g_GuildNotice[0], 0 ,0, RT3_WRITE_CENTER);
	g_pRenderText->RenderText(StartX+( int)Width/2,StartY+58,g_GuildNotice[1], 0 ,0, RT3_WRITE_CENTER);

#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int yGuildStart = 72;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int Number = g_nGuildMemberCount;

	if(g_nGuildMemberCount >= MAX_GUILD_LINE)
      	Number = MAX_GUILD_LINE;
}

//#define MAX_LENGTH_CMB	( 26)
#define NUM_LINE_CMB	( 7)

//////////////////////////////////////////////////////////////////////////
//  ���� ����â.
//////////////////////////////////////////////////////////////////////////
void RenderServerDivision ()
{
    if ( !g_pUIManager->IsOpen(INTERFACE_SERVERDIVISION) ) return;

   	float Width, Height, x, y; 

	glColor3f ( 1.f, 1.f, 1.f );
    EnableAlphaTest ();

    //  Ʋ.
    InventoryStartX = 640-190;
    InventoryStartY = 0;
    Width = 213;Height = 40;x = (float)InventoryStartX;y = (float)InventoryStartY;
	RenderInventoryInterface ( (int)x, (int)y, 1 );

	//  ��ư.
	g_pRenderText->SetBgColor(0);
	g_pRenderText->SetTextColor(255, 230, 210, 255);

    //  ���.
	g_pRenderText->SetFont(g_hFontBold);
    x = InventoryStartX+(190/2.f);
    y = 50;
    for ( int i=462; i<470; ++i )
    {
		g_pRenderText->RenderText(x, y, GlobalText[i], 0 ,0, RT3_WRITE_CENTER);
        y += 20;
    }

    //  ����.
	g_pRenderText->SetFont(g_hFontBold);
    Width = 16; Height = 16; x = (float)InventoryStartX+25;y = 240;
    if ( g_bServerDivisionAccept )
    {
		g_pRenderText->SetTextColor(212, 150, 0, 255);
        RenderBitmap(BITMAP_INVENTORY_BUTTON+11,x,y,Width,Height,0.f,0.f,24/32.f,24/32.f);
    }
    else
    {
		g_pRenderText->SetTextColor(223, 191, 103, 255);
        RenderBitmap(BITMAP_INVENTORY_BUTTON+10,x,y,Width,Height,0.f,0.f,24/32.f,24/32.f);
    }
	g_pRenderText->RenderText((int)(x+Width+3),(int)(y+5),GlobalText[447] );
	g_pRenderText->SetFont(g_hFont);
	g_pRenderText->SetTextColor(255, 230, 210, 255);

    //  ���.
    Width = 120; Height = 24; x = (float)InventoryStartX+35;y = 350;//(Width/2.f); y = 231;
    RenderBitmap(BITMAP_INTERFACE+10,(float)x,(float)y,(float)Width,(float)Height,0.f,0.f,213.f/256.f);
	g_pRenderText->RenderText((int)(x+(Width/2)),(int)(y+5),GlobalText[229], 0 ,0, RT3_WRITE_CENTER);

    //  Ȯ��.
    Width = 120; Height = 24; x = (float)InventoryStartX+35;y = 320;//(Width/2.f); y = 231;
    if ( g_bServerDivisionAccept )
        glColor3f ( 1.f, 1.f, 1.f );
    else 
        glColor3f ( 0.5f, 0.5f, 0.5f );
    RenderBitmap(BITMAP_INTERFACE+10,(float)x,(float)y,(float)Width,(float)Height,0.f,0.f,213.f/256.f);
	g_pRenderText->RenderText((int)(x+(Width/2)),(int)(y+5),GlobalText[228], 0 ,0, RT3_WRITE_CENTER);

    glColor3f( 1.f, 1.f, 1.f );
}

#ifdef CSK_FREE_TICKET
// ��������ǿ��� ���尡���� ������ ����ؼ� �������� ������ ���Ͻ����ش�.
BYTE CaculateFreeTicketLevel(int iType)
{
	// ĳ���� ����
	int iChaLevel = CharacterAttribute->Level;

	// ĳ���� �⺻ Ŭ����
	int iChaClass = GetBaseClass(Hero->Class);
	// ĳ���� ���� Ŭ����
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int iChaExClass = IsSecondClass(Hero->Class);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	int iItemLevel = 0;

	if(iType == FREETICKET_TYPE_DEVILSQUARE)
	{
		// ���˻��� ���
		if(iChaClass == CLASS_DARK)
		{
			if(iChaLevel >= 15 && iChaLevel <= 110)
			{
				iItemLevel = 0;
			}
			else if(iChaLevel >= 111 && iChaLevel <= 160)
			{
				iItemLevel = 8;
			}
			else if(iChaLevel >= 161 && iChaLevel <= 210)
			{
				iItemLevel = 16;
			}
			else if(iChaLevel >= 211 && iChaLevel <= 260)
			{
				iItemLevel = 24;
			}
			else if(iChaLevel >= 261 && iChaLevel <= 310)
			{
				iItemLevel = 32;
			}
			else if(iChaLevel >= 311 && iChaLevel <= 400)
			{
				iItemLevel = 40;
			}
		}
		// �ٸ� Ŭ������ ���
		else
		{
			if(iChaLevel >= 15 && iChaLevel <= 130)
			{
				iItemLevel = 0;
			}
			else if(iChaLevel >= 131 && iChaLevel <= 180)
			{
				iItemLevel = 8;
			}
			else if(iChaLevel >= 181 && iChaLevel <= 230)
			{
				iItemLevel = 16;
			}
			else if(iChaLevel >= 231 && iChaLevel <= 280)
			{
				iItemLevel = 24;
			}
			else if(iChaLevel >= 281 && iChaLevel <= 330)
			{
				iItemLevel = 32;
			}
			else if(iChaLevel >= 331 && iChaLevel <= 400)
			{
				iItemLevel = 40;
			}
		}

		// ����Ʈ ������ ����ؼ� ������ �ش�.
		return (iItemLevel>>3)&15;
	}
	// ����ĳ��
	else if(iType == FREETICKET_TYPE_BLOODCASTLE)
	{
		// ���˻� ���
		if(iChaClass == CLASS_DARK)
		{
			if(iChaLevel >= 15 && iChaLevel <= 60)
			{
				iItemLevel = 0;
			}
			else if(iChaLevel >= 61 && iChaLevel <= 110)
			{
				iItemLevel = 8;
			}
			else if(iChaLevel >= 111 && iChaLevel <= 160)
			{
				iItemLevel = 16;
			}
			else if(iChaLevel >= 161 && iChaLevel <= 210)
			{
				iItemLevel = 24;
			}
			else if(iChaLevel >= 211 && iChaLevel <= 260)
			{
				iItemLevel = 32;
			}
			else if(iChaLevel >= 261 && iChaLevel <= 310)
			{
				iItemLevel = 40;
			}
			else if(iChaLevel >= 311 && iChaLevel <= 400)
			{
				iItemLevel = 48;
			}
		}
		// �ٸ�Ŭ���� ���
		else
		{
			if(iChaLevel >= 15 && iChaLevel <= 80)
			{
				iItemLevel = 0;
			}
			else if(iChaLevel >= 81 && iChaLevel <= 130)
			{
				iItemLevel = 8;
			}
			else if(iChaLevel >= 131 && iChaLevel <= 180)
			{
				iItemLevel = 16;
			}
			else if(iChaLevel >= 181 && iChaLevel <= 230)
			{
				iItemLevel = 24;
			}
			else if(iChaLevel >= 231 && iChaLevel <= 280)
			{
				iItemLevel = 32;
			}
			else if(iChaLevel >= 281 && iChaLevel <= 330)
			{
				iItemLevel = 40;
			}
			else if(iChaLevel >= 331 && iChaLevel <= 400)
			{
				iItemLevel = 48;
			}
		}

#ifdef LJH_FIX_INCORRECT_SCHEDULE_FOR_BC_FREE_TICKET
		if(IsMasterLevel(Hero->Class))
			iItemLevel = 56;
#endif //LJH_FIX_INCORRECT_SCHEDULE_FOR_BC_FREE_TICKET

		// ����Ʈ ������ ����ؼ� ������ �ش�.
		return (iItemLevel>>3)&15;
	}
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	else if( iType == FREETICKET_TYPE_CURSEDTEMPLE ) {
		if( g_pCursedTempleEnterWindow->CheckEnterLevel( iItemLevel ) )
		{
			return (iItemLevel>>3)&15;
		}
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET	
#ifdef LDS_FIX_INGAMESHOPITEM_PASSCHAOSCASTLE_REQUEST	// ī����ĳ�� ���������
	else if( iType == FREETICKED_TYPE_CHAOSCASTLE ) 
	{
		if( g_pCursedTempleEnterWindow->CheckEnterLevel( iItemLevel ) )
		{
			return (iItemLevel>>3)&15;
		}
	}
#endif // LDS_FIX_INGAMESHOPITEM_PASSCHAOSCASTLE_REQUEST
	return 0;
}
#endif // CSK_FREE_TICKET

#ifdef NEW_USER_INTERFACE_UISYSTEM
const bool ChangeCodeItem( ITEM* ip, BYTE* itemdata )
{
	int Type = ConvertItemType( itemdata );

	if( Type == 0x1FFF ) 
	{
		return false;
	}
	else
	{
		ip->Type							= Type;
		ip->x								= 0;
		ip->y								= 0;
		ip->Number							= 0;
		ip->Durability						= itemdata[2];
		ip->Option1							= itemdata[3];
		ip->ExtOption						= itemdata[4];
		ip->option_380						= false;
		byte is380option					= ( ( (itemdata[5] & 0x08) << 4) >>7);
		ip->option_380						= is380option;
		ip->Jewel_Of_Harmony_Option			= (itemdata[6] & 0xf0) >> 4;
		ip->Jewel_Of_Harmony_OptionLevel	= itemdata[6] & 0x0f;

#ifdef SOCKET_SYSTEM
		// ���� ������ �ɼ� (0x00~0xF9: �ɼǰ�����ȣ, 0xFE: �� ����, 0xFF: ���� ����)
		BYTE bySocketOption[5] = { itemdata[7], itemdata[8], itemdata[9], itemdata[10], itemdata[11] };
		ip->SocketCount = MAX_SOCKETS;

		for (int i = 0; i < MAX_SOCKETS; ++i)
		{
			ip->bySocketOption[i] = bySocketOption[i];	// �������� ���� ���� ���
		}

#ifdef _VS2008PORTING
		for (int i = 0; i < MAX_SOCKETS; ++i)
#else // _VS2008PORTING
		for (i = 0; i < MAX_SOCKETS; ++i)
#endif // _VS2008PORTING
		{
			if (bySocketOption[i] == 0xFF)		// ������ ���� (DB�󿡴� 0x00 ���� �Ǿ�����)
			{
				ip->SocketCount = i;
				break;
			}
			else if (bySocketOption[i] == 0xFE)	// ������ ������� (DB�󿡴� 0xFF ���� �Ǿ�����)
			{
				ip->SocketSeedID[i] = SOCKET_EMPTY;
			}
			else	// 0x00~0xF9 ���� ���� ������ȣ�� ���, MAX_SOCKET_OPTION(50)������ ������ ������ȣ�� ǥ�� (DB�󿡴� 0x01~0xFA�� �Ǿ�����)
			{
				ip->SocketSeedID[i] = bySocketOption[i] % SEASON4A::MAX_SOCKET_OPTION;
				ip->SocketSphereLv[i] = int(bySocketOption[i] / SEASON4A::MAX_SOCKET_OPTION) + 1;
			}
		}
		if (g_SocketItemMgr.IsSocketItem(ip))	// ���� �������̸�
		{
			ip->SocketSeedSetOption = itemdata[6];	// ��ȭ�Ǻ����ɼǰ����� �õ弼Ʈ�ɼ��� ǥ����
			ip->Jewel_Of_Harmony_Option = 0;
			ip->Jewel_Of_Harmony_OptionLevel = 0;
		}
		else
		{
			ip->SocketSeedSetOption = SOCKET_EMPTY;
		}
#endif	// SOCKET_SYSTEM

		ItemConvert( ip,itemdata[1],itemdata[3],itemdata[4] );
	}

	return true;
}

const int ChangeData( ITEM* tooltipitem, const CASHSHOP_ITEMLIST& indata, vector<string>& outtextdata, vector<DWORD>& outcolordata )
{	
	string  tempstring;
	DWORD   tempstringcolor  = 0;
	int	    tempbackupmaxlen = 0;

	if( ChangeCodeItem( tooltipitem, (BYTE*)indata.s_btItemInfo ) )
	{
		tooltipitem->Durability = indata.s_btItemDuration;

		RenderItemInfo( 0, 0, tooltipitem, false, false );

		for ( int i = 0; i < ITEMINFOCOUNT; ++i )
		{
			tempstring      = TextList[i];
			tempstringcolor = TextListColor[i];

			if( tempstring.size() > 0 && TextList[i][0] != '\0' && TextList[i][0] != '\n' )
			{
				tempbackupmaxlen = Max( tempbackupmaxlen, tempstring.length() );
				outtextdata.push_back( tempstring );
				outcolordata.push_back( tempstringcolor );
			}
		}
	}

	return tempbackupmaxlen;
}

#endif //NEW_USER_INTERFACE_UISYSTEM

