

#include "stdafx.h"

#include "NewUIHotKey.h"
#include "NewUISystem.h"
#include "NewUICommonMessageBox.h"
#include "NewUICustomMessageBox.h"
#include "DSPlaySound.h"
#include "GMBattleCastle.h"
#include "CSChaosCastle.h"
#include "w_CursedTemple.h"
#include "ZzzInterface.h"
#include "ZzzLodTerrain.h"
#include "wsclientinline.h"
#include "ZzzEffect.h"
#ifdef PJH_CHARACTER_RENAME
#include "UIMng.h"
#endif //PJH_CHARACTER_RENAME
#ifdef CSK_HACK_TEST
#include "HackTest.h"
#endif // CSK_HACK_TEST
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
#include "InGameShopSystem.h"
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef LDK_ADD_SCALEFORM
#include "CGFxProcess.h"
#endif //LDK_ADD_SCALEFORM

#ifdef FOR_WORK
	#include "./Utilities/Log/DebugAngel.h"
#endif // FOR_WORK

using namespace SEASON3B;

SEASON3B::CNewUIHotKey::CNewUIHotKey() : m_pNewUIMng(NULL) , m_bStateGameOver(false)
{

}

SEASON3B::CNewUIHotKey::~CNewUIHotKey() 
{ 
	Release(); 
}

bool SEASON3B::CNewUIHotKey::Create(CNewUIManager* pNewUIMng)
{
	if(NULL == pNewUIMng)
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_HOTKEY, this);

	Show(true);		//. �׸��ʿ� ����
	
	return true;
}

void SEASON3B::CNewUIHotKey::Release()
{
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

bool SEASON3B::CNewUIHotKey::UpdateMouseEvent()
{
	extern int SelectedCharacter;
	
#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
	// ���� ������ ��Ŀ�ǵ�â�� ������ �ʴ´�
	if(g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch))
	{
		return true;
	}
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF

	// ��Ŀ�ǵ�â �����ư
	if(SelectedCharacter >= 0)
	{
		if(SEASON3B::IsRepeat(VK_MENU) && SEASON3B::IsRelease(VK_RBUTTON)
			&& InChaosCastle() == false						// ī����ĳ���� �ƴϰ�
			&& g_CursedTemple->IsCursedTemple() == false	// ȯ������� �ƴϸ�
			)
		{
			CHARACTER* pCha = &CharactersClient[SelectedCharacter];	
			
			if(pCha->Object.Kind != KIND_PLAYER)
			{
				return false;
			}
			
#ifdef KJH_FIX_WOPS_K22844_CHRISTMAS_TRANSFORM_RING_SUMMON_TO_COMMAND
			// ��ɾ ������� ���ƾ� �� ĳ���͵�
			if( (pCha->Object.SubType == MODEL_XMAS_EVENT_CHA_DEER)
				|| (pCha->Object.SubType == MODEL_XMAS_EVENT_CHA_SNOWMAN)
				|| (pCha->Object.SubType == MODEL_XMAS_EVENT_CHA_SSANTA)
				)
			{
				return false;
			}
#endif // KJH_FIX_WOPS_K22844_CHRISTMAS_TRANSFORM_RING_SUMMON_TO_COMMAND

#ifdef ASG_ADD_GENS_SYSTEM
			// �������������� Ÿ ���� �÷��̾��� �޴��� �߸� �ȵ�.
			if (::IsStrifeMap(World) && Hero->m_byGensInfluence != pCha->m_byGensInfluence)
				return false;
#endif	// ASG_ADD_GENS_SYSTEM
			// �Ÿ� ���
			float fPos_x = pCha->Object.Position[0] - Hero->Object.Position[0];
			float fPos_y = pCha->Object.Position[1] - Hero->Object.Position[1];
			float fDistance = sqrtf((fPos_x * fPos_x) + (fPos_y * fPos_y));
			
			if(fDistance < 300.f)
			{
				int x, y;
				x = MouseX + 10;
				y = MouseY - 50;
				if(y < 0)
				{
					y = 0;
				}
				g_pQuickCommand->OpenQuickCommand(pCha->ID, SelectedCharacter, x, y);
			}
			else
			{
				// 1388 "�Ÿ��� �־� ����� �� �����ϴ�."
				g_pChatListBox->AddText("", GlobalText[1388], SEASON3B::TYPE_ERROR_MESSAGE);
				g_pQuickCommand->CloseQuickCommand();
			}
			
			return false;
		}
	}

	return true;
}

bool SEASON3B::CNewUIHotKey::UpdateKeyEvent()
{
	if(SEASON3B::IsPress(VK_ESCAPE) == true)
	{
		if(g_MessageBox->IsEmpty())
		{
			SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CSystemMenuMsgBoxLayout));
			PlayBuffer(SOUND_CLICK01);
			return false;
		}
	}

	// �������� �����϶��� ESCŰ�� ������ ����Ű�� ���� �ʴ´�.
	if( m_bStateGameOver == true )
	{
		return false;
	}

#ifdef PJH_ADD_MINIMAP
	if(SEASON3B::IsPress(VK_TAB) == false && g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MINI_MAP) == true)
	{
		return false;
	}
#endif //PJH_ADD_MINIMAP

#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF
	// ���� ������ ESCŰ�� ������ ����Ű�� ���� �ʴ´�.
	if(g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch))
	{
		if (SEASON3B::IsPress('M') == true)		// �̵���ɸ� �����ϴ� (���� ������ ���� �Ʒ��ʿ��� ������ ����: ���� ������ �Ʒ��� 'M'ó���� ���� ���ľ���!)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_MOVEMAP);
			PlayBuffer(SOUND_CLICK01);
		}
		return false;
	}
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF

	// �����̽���Ű ������ ������ �ڵ��ݱ�
	if(AutoGetItem() == true)
	{
		return false;
	}

	// �κ��丮â ����Ű�� �Դ� â��
	if(CanUpdateKeyEventRelatedMyInventory() == true)
	{
		if(SEASON3B::IsPress('I') || SEASON3B::IsPress('V'))
		{
#ifdef YDG_FIX_NPCSHOP_SELLING_LOCK
			if (g_pNPCShop->IsSellingItem() == false)
#endif	// YDG_FIX_NPCSHOP_SELLING_LOCK
			{
				g_pNewUISystem->Toggle(SEASON3B::INTERFACE_INVENTORY);
				PlayBuffer(SOUND_CLICK01);
				return false;
			}
		}

		return true;
	}
	else if(CanUpdateKeyEvent() == false)
	{
		return true;
	}

	//. ��� �������̽� ����Ű ����
	if(SEASON3B::IsPress('F'))			// ģ��â
	{
		if(InChaosCastle() == true 
#ifndef CSK_FIX_CHAOSFRIENDWINDOW		// ������ �� ������ �ϴ� �ҽ�	
			&& g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHAOSCASTLE_TIME) == true
#endif //! CSK_FIX_CHAOSFRIENDWINDOW	// ������ �� ������ �ϴ� �ҽ�
			)
		{
			return true;
		}

		int iLevel = CharacterAttribute->Level;

		if(iLevel < 6)
		{
			if(g_pChatListBox->CheckChatRedundancy(GlobalText[1067]) == FALSE)
			{
				g_pChatListBox->AddText("",GlobalText[1067],SEASON3B::TYPE_SYSTEM_MESSAGE);	// "���� 6���� ��ģ�� ��� ����� �����մϴ�."
			}
		}
		else
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_FRIEND);
		}
		
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(SEASON3B::IsPress('I') || SEASON3B::IsPress('V'))	// �κ��丮â
	{
#ifdef YDG_FIX_NPCSHOP_SELLING_LOCK
		if (g_pNPCShop->IsSellingItem() == false)
#endif	// YDG_FIX_NPCSHOP_SELLING_LOCK
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_INVENTORY);
			PlayBuffer(SOUND_CLICK01);
			return false;
		}
	}
	else if(SEASON3B::IsPress('C'))		// ĳ��������â
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_CHARACTER);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(SEASON3B::IsPress('T'))		// ����Ʈâ
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_MYQUEST);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(SEASON3B::IsPress('P'))		// ��Ƽâ
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_PARTY);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(SEASON3B::IsPress('G'))		// �������â
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_GUILDINFO);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}

	else if(SEASON3B::IsPress('A'))
	{


#ifdef DO_PROCESS_DEBUGCAMERA	// 
		if( EDEBUGCAMERA_NONE == g_pDebugCameraManager->GetActiveCameraMode() )
		{
			if(IsMasterLevel( Hero->Class ) == true 
#ifdef KJH_FIX_WOPS_K22193_SUMMONER_MASTERSKILL_UI_ABNORMAL_TEXT
				&& GetCharacterClass(Hero->Class) != CLASS_DIMENSIONMASTER			// 2008.06.13 ����� ��ȯ���� �����ͽ�ų �Ұ�. Ǯ���� define �ּ�ó��
#endif // KJH_FIX_WOPS_K22193_SUMMONER_MASTERSKILL_UI_ABNORMAL_TEXT
#ifdef PBG_ADD_NEWCHAR_MONK
				&& GetCharacterClass(Hero->Class) != CLASS_TEMPLENIGHT
#endif //PBG_ADD_NEWCHAR_MONK
				)
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_MASTER_LEVEL);
			PlayBuffer(SOUND_CLICK01);
		}
#else // DO_PROCESS_DEBUGCAMERA	// 

		if(IsMasterLevel( Hero->Class ) == true 
#ifdef KJH_FIX_WOPS_K22193_SUMMONER_MASTERSKILL_UI_ABNORMAL_TEXT
			&& GetCharacterClass(Hero->Class) != CLASS_DIMENSIONMASTER			// 2008.06.13 ����� ��ȯ���� �����ͽ�ų �Ұ�. Ǯ���� define �ּ�ó��
#endif // KJH_FIX_WOPS_K22193_SUMMONER_MASTERSKILL_UI_ABNORMAL_TEXT
#ifdef PBG_ADD_NEWCHAR_MONK
			&& GetCharacterClass(Hero->Class) != CLASS_TEMPLENIGHT				// ���� ������ ��ųƮ�� ����
#endif //PBG_ADD_NEWCHAR_MONK
			)
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_MASTER_LEVEL);
		PlayBuffer(SOUND_CLICK01);

#endif // DO_PROCESS_DEBUGCAMERA

		return false;
	}

	
#if defined NEW_USER_INTERFACE_SHELL && !defined LDK_MOD_GLOBAL_PORTAL_CASHSHOP_BUTTON_DENY
	else if(SEASON3B::IsPress('X')) 
	{
		if( g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_PARTCHARGE_SHOP ) == false ) 
		{
			TheShopServerProxy().SetShopIn();
			return false;
		}
		else 
		{
			SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
			TheShopServerProxy().SetShopOut();
			return false;
		}
	}
#endif //NEW_USER_INTERFACE_SHELL
	else if(SEASON3B::IsPress('U'))		// ������޴�â
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_WINDOW_MENU);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(InChaosCastle() == false && SEASON3B::IsPress('D'))		// Ŀ�ǵ� â
	{
#ifdef DO_PROCESS_DEBUGCAMERA
		if( EDEBUGCAMERA_NONE == g_pDebugCameraManager->GetActiveCameraMode() )
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_COMMAND);
			PlayBuffer(SOUND_CLICK01);
		}
#else // DO_PROCESS_DEBUGCAMERA
#ifdef ASG_ADD_GENS_SYSTEM
		if (::IsStrifeMap(World))	// ���������ΰ�?
		{
			if (g_pChatListBox->CheckChatRedundancy(GlobalText[2989]) == FALSE)	// �޽��� �ߺ��� ����.(������ 2���� �̻��� �������ϴ� ���װ� ����)
				g_pChatListBox->AddText("", GlobalText[2989], SEASON3B::TYPE_SYSTEM_MESSAGE);	// "�������������� Ŀ�ǵ�â�� Ȱ��ȭ ���� �ʽ��ϴ�."
		}
		else
		{
#endif	// ASG_ADD_GENS_SYSTEM
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_COMMAND);
			PlayBuffer(SOUND_CLICK01);
#ifdef ASG_ADD_GENS_SYSTEM
		}
#endif	// ASG_ADD_GENS_SYSTEM
#endif // DO_PROCESS_DEBUGCAMERA
		
		return false;
	}
	else if(SEASON3B::IsPress(VK_F1) == true)	// ���� â
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_HELP);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
	else if(SEASON3B::IsPress('M') == true)		// �̵� ��� â
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_MOVEMAP);
		PlayBuffer(SOUND_CLICK01);

		return false;
	}
	else if(SEASON3B::IsPress(VK_TAB) == true && battleCastle::InBattleCastle() == true )
	{
		g_pNewUISystem->Toggle( SEASON3B::INTERFACE_SIEGEWARFARE );
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
#ifdef PJH_ADD_MINIMAP
	else if(SEASON3B::IsPress(VK_TAB) == true)
	{
		if(g_pNewUIMiniMap->m_bSuccess == false)
		{
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_MINI_MAP);
		}
		else
			g_pNewUISystem->Toggle( SEASON3B::INTERFACE_MINI_MAP );
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
#endif //PJH_ADD_MINIMAP

#ifdef _SHOPDEBUGMODE
	else if(SEASON3B::IsPress(VK_F8) == true)
	{
		TheUISystem().SetDebugKey( TheUISystem().IsDebugKey() ? false : true );
		return false;
	}
#endif //_SHOPDEBUGMODE
#ifdef CSK_HACK_TEST
	else if(SEASON3B::IsRepeat(VK_ADD) == true)
	{
		g_pHackTest->PlusAttackSpeed();
	}
	else if(SEASON3B::IsRepeat(VK_SUBTRACT) == true)
	{
		g_pHackTest->MinusAttackSpeed();
	}
	else if(SEASON3B::IsPress('Z') == true)
	{
		g_pHackTest->FindAllMonster();
	}
#endif // CSK_HACK_TEST
	// �ΰ��Ӽ� ����Ű - ����������
#ifdef PBG_ADD_INGAMESHOP_UI_MAINFRAME
	else if(SEASON3B::IsPress('X') == true)
	{
#ifdef FOR_WORK
		DebugAngel_Write("InGameShopStatue.Txt", "CallStack - CNewUIHotKey.UpdateKeyEvent()\r\n");
#endif // FOR_WORK
		// �ΰ��Ӽ��� ������ �ȵŴ� ����
		if(g_pInGameShop->IsInGameShopOpen() == false)
			return false;

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
		// ��ũ��Ʈ �ٿ�ε�
		if( g_InGameShopSystem->IsScriptDownload() == true )
		{
			if( g_InGameShopSystem->ScriptDownload() == false )
				return false;
		}
		
		// ��� �ٿ�ε�
		if( g_InGameShopSystem->IsBannerDownload() == true )
		{
#ifdef KJH_FIX_INGAMESHOP_INIT_BANNER
			if( g_InGameShopSystem->BannerDownload() == true )
			{
				// ��� �ʱ�ȭ
				g_pInGameShop->InitBanner(g_InGameShopSystem->GetBannerFileName(), g_InGameShopSystem->GetBannerURL());
			}
#else // KJH_FIX_INGAMESHOP_INIT_BANNER
			g_InGameShopSystem->BannerDownload();
#endif // KJH_FIX_INGAMESHOP_INIT_BANNER
		}
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

		if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == false)
		{
			// �� Open ��û�� ���°� �ƴϸ� 
			if( g_InGameShopSystem->GetIsRequestShopOpenning() == false )		
			{
				SendRequestIGS_CashShopOpen(0);		// �� Open��û
				g_InGameShopSystem->SetIsRequestShopOpenning(true);
#ifdef LDK_ADD_SCALEFORM
				if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
				{
#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
					g_pMainFrame->SetBtnState(MAINFRAME_BTN_PARTCHARGE, true);
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
				}
#else //LDK_ADD_SCALEFORM
#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
				g_pMainFrame->SetBtnState(MAINFRAME_BTN_PARTCHARGE, true);
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
#endif //LDK_ADD_SCALEFORM
			}
		}
		else
		{
			SendRequestIGS_CashShopOpen(1);		// �� Close��û
			g_pNewUISystem->Hide(SEASON3B::INTERFACE_INGAMESHOP);
		}		

		return false;
	}
#endif // PBG_ADD_INGAMESHOP_UI_MAINFRAME
#ifdef PBG_ADD_GENSRANKING
	else if(SEASON3B::IsPress('B'))				// �ս���ŷ
	{
		// �ս��� ���ԵǾ� ���� �ʴٸ� â�� ���� �ʴ´�
		if(!g_pNewUIGensRanking->SetGensInfo())
			return false;

		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_GENSRANKING);
		PlayBuffer(SOUND_CLICK01);
		return false;
	}
#endif //PBG_ADD_GENSRANKING
#ifdef YDG_ADD_DOPPELGANGER_UI
// 	else if(SEASON3B::IsPress('Z') == true)		// ���ð��� �׽�Ʈ
// 	{
// 		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_DOPPELGANGER_FRAME);
// // 		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_DOPPELGANGER_NPC);
// 		return false;
// 	}
#endif	// YDG_ADD_DOPPELGANGER_UI
#if defined LDK_TEST_MAP_EMPIREGUARDIAN
// 	else if(SEASON3B::IsPress('Z') == true)		// ui
// 	{
// 		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_EMPIREGUARDIAN_NPC);
// 		return false;
// 	}
#endif //LDK_TEST_MAP_EMPIREGUARDIAN
#ifdef LDS_ADD_TEST_UNITEDMARKETPLACE
	else if(SEASON3B::IsPress('Z') == true)		// ���ս��� �׽�Ʈ.
	{
		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_UNITEDMARKETPLACE_NPC_JULIA);
// 		g_pNewUISystem->Toggle(SEASON3B::INTERFACE_UNITEDMARKETPLACE_NPC_JULIA);
		return false;
	}
#endif // LDS_ADD_TEST_UNITEDMARKETPLACE

	return true;
}

bool SEASON3B::CNewUIHotKey::Update()
{
	return true;
}

bool SEASON3B::CNewUIHotKey::Render()
{
	return true;
}

bool SEASON3B::CNewUIHotKey::CanUpdateKeyEventRelatedMyInventory()
{
	// �κ��丮 ��Ű�� �Դ� ���(I, V)
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MIXINVENTORY)	// ����â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_TRADE)		// �ŷ�â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_STORAGE)	// â��â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP)	// NPC����
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYSHOP_INVENTORY)			// ���λ���
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY)	// ���Ż���
#ifdef LEM_ADD_LUCKYITEM
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYITEMWND)
#endif // LEM_ADD_LUCKYITEM

		)
	{
		return true;	
	}
	
	return false;
}

bool SEASON3B::CNewUIHotKey::CanUpdateKeyEvent()
{
	// �ƹ� ��Ű�� �ȸԾ�� �ϴ� â�� �̰��� �߰����ּ���.
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_KANTURU2ND_ENTERNPC)	// ĭ���� ����â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CATAPULT)			// ������ ������â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCQUEST)			// NPC����Ʈâ
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_SENATUS)			// ���ο�â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GATEKEEPER)		// �÷��� �� ������ â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GUARDSMAN)			// ���� ������ â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GATESWITCH)		// ���� ���� ����ġâ
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCGUILDMASTER)	// ��� ���� â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_BLOODCASTLE)		// ����ĳ�� ����â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DEVILSQUARE)		// �Ǹ��Ǳ��� ����â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CURSEDTEMPLE_NPC)	// ȯ���ǻ�� ����â
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MASTER_LEVEL)		// ������ ���� â
#ifdef YDG_ADD_NEW_DUEL_UI
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DUELWATCH)			// ���� ������ â
#endif	// YDG_ADD_NEW_DUEL_UI
#ifdef YDG_ADD_DOPPELGANGER_UI
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DOPPELGANGER_NPC)	// ���ð��� �簡�� â
#endif	// YDG_ADD_DOPPELGANGER_UI
#ifdef ASG_ADD_UI_NPC_DIALOGUE
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_DIALOGUE)		// NPC ��ȭ â.
#endif	// ASG_ADD_UI_NPC_DIALOGUE
#ifdef ASG_ADD_UI_QUEST_PROGRESS
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS)	// ����Ʈ ���� â(NPC�� ����)
#endif	// ASG_ADD_UI_QUEST_PROGRESS
#ifdef ASG_ADD_UI_NPC_MENU
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPC_MENU)	// NPC �޴�â.
#endif	// ASG_ADD_UI_NPC_MENU
#ifdef ASG_ADD_UI_QUEST_PROGRESS_ETC
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_QUEST_PROGRESS_ETC)// ����Ʈ ���� â(��Ÿ ������� ����)
#endif	// ASG_ADD_UI_QUEST_PROGRESS_ETC
#ifdef KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
#ifdef PSW_GOLDBOWMAN
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GOLD_BOWMAN)
#endif //PSW_GOLDBOWMAN
#ifdef PSW_EVENT_LENA
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_GOLD_BOWMAN_LENA)
#endif //PSW_EVENT_LENA	
#endif // KJH_FIX_JP0457_OPENNING_PARTCHARGE_UI
#ifdef PBG_MOD_LUCKYCOINEVENT
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_LUCKYCOIN_REGISTRATION)
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_EXCHANGE_LUCKYCOIN)
#endif //PBG_MOD_LUCKYCOINEVENT
#ifdef LDK_FIX_EMPIREGUARDIAN_UI_HOTKEY
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_EMPIREGUARDIAN_NPC)
#endif	// LDK_FIX_EMPIREGUARDIAN_UI_HOTKEY
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
		|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_UNITEDMARKETPLACE_NPC_JULIA)
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
		)
	{
		return false;
	}

	return true;
}

float SEASON3B::CNewUIHotKey::GetLayerDepth() 
{ 
	return 1.0f; 
}

float SEASON3B::CNewUIHotKey::GetKeyEventOrder() 
{ 
	return 1.0f; 
}

void SEASON3B::CNewUIHotKey::SetStateGameOver( bool bGameOver )
{
	m_bStateGameOver = bGameOver;
}

bool SEASON3B::CNewUIHotKey::IsStateGameOver()
{
	return m_bStateGameOver;
}

bool SEASON3B::CNewUIHotKey::AutoGetItem()
{
	//  ������ space�� �ڵ� �Ա�.
	if (
		CNewUIInventoryCtrl::GetPickedItem() == NULL 
		&& SEASON3B::IsPress(VK_SPACE) 
		&& g_pChatInputBox->HaveFocus() == false
		&& CheckMouseIn(0, 0, GetScreenWidth(), 429)
		)
	{
		for(int i=0; i<MAX_ITEMS; ++i)
		{
			OBJECT* pObj = &Items[i].Object;
			if(pObj->Live && pObj->Visible)
			{
				vec3_t vDir;
				VectorSubtract(pObj->Position, Hero->Object.Position, vDir);
				if(VectorLength(vDir) < 300)
				{
					Hero->MovementType = MOVEMENT_GET;
					ItemKey = i;
					g_bAutoGetItem = true;
					Action(Hero, pObj, true);
					Hero->MovementType = MOVEMENT_MOVE;
					g_bAutoGetItem = false;
					
					return true;
				}
			}
		}
	}

	return false;
}
