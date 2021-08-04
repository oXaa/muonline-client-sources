//////////////////////////////////////////////////////////////////////////
//  
//  UIManager.cpp
//  
//  ��  �� : UI ���� ���� ���ִ� Ŭ����
//  
//  ��  ¥ : 2004�� 11�� 09��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//						 												//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZzzOpenglUtil.h"
#include "ZzzTexture.h"
#include "ZzzInfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzLodTerrain.h"
#include "ZzzInventory.h"
#include "wsclientinline.h"
#include "CSQuest.h"
#include "npcBreeder.h"
#include "CSItemOption.h"
#include "CSChaosCastle.h"
#include "GIPetManager.h"
#include "PersonalShopTitleImp.h"
#include "npcGateSwitch.h"
#include "CComGem.h"
#include "GM_Kanturu_2nd.h"
#ifndef KJH_DEL_PC_ROOM_SYSTEM		// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
#include "PCRoomPoint.h"
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
#include "NewUICustomMessageBox.h"
#include "NewUINPCShop.h"
#include "MixMgr.h"

//////////////////////////////////////////////////////////////////////////
//						 												//
//////////////////////////////////////////////////////////////////////////

extern int g_iKeyPadEnable;
extern int g_iChatInputType;
extern DWORD g_dwMouseUseUIID;

CUIGateKeeper*				g_pUIGateKeeper = NULL;
JewelHarmonyInfo*			g_pUIJewelHarmonyinfo = NULL;
ItemAddOptioninfo*			g_pItemAddOptioninfo = NULL;
CUIPopup*					g_pUIPopup = NULL;

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;

extern int   ShopInventoryStartX;
extern int   ShopInventoryStartY;

extern bool g_bTradeEndByOppenent;

bool HeroInventoryEnable       = false; //  ĳ���� ���â.
bool GuildListEnable           = false; //  ��� ����Ʈ.
bool EnableGuildInterface      = false; //  
bool StorageInventoryEnable    = false; //  â��.
bool MixInventoryEnable        = false; //  ���ձ�.
bool g_bPersonalShopWnd		   = false;
bool g_bServerDivisionEnable   = false; //  ��������â.

//////////////////////////////////////////////////////////////////////////
//						 												//
//////////////////////////////////////////////////////////////////////////

CUIManager::CUIManager()
{
	g_pUIGateKeeper				= new CUIGateKeeper;
	g_pUIPopup					= new CUIPopup;
	g_pUIJewelHarmonyinfo       = JewelHarmonyInfo::MakeInfo();
	g_pItemAddOptioninfo		= ItemAddOptioninfo::MakeInfo();

	Init();
}

CUIManager::~CUIManager()
{
	SAFE_DELETE( g_pItemAddOptioninfo );
	SAFE_DELETE( g_pUIJewelHarmonyinfo );
	SAFE_DELETE( g_pUIGateKeeper );
	SAFE_DELETE( g_pUIPopup );
}

void CUIManager::Init()
{
	g_pUIPopup->Init();
#ifdef PET_SYSTEM
    giPetManager::InitPetManager ();
#endif// PET_SYSTEM
	ClearPersonalShop();
}

POINT CUIManager::RenderWindowBase( int nHeight, int nOriginY )
{
	int nWidth = 213;

    EnableAlphaBlend3();
	glColor4f( 1.0f, 1.0f, 1.0f, 0.8f );

	float fPosX = 320 - nWidth/2;
	float fPosY;
	if( nOriginY == -1 )
	{
		fPosY = 130 - nHeight/2;
		if( fPosY < 40.0f )		fPosY = 40.0f;
	}
	else
		fPosY = nOriginY;
	POINT ptPos = { fPosX, fPosY };

	// ���ʿܰ� �׸���
	RenderBitmap( BITMAP_INTERFACE+22, fPosX, fPosY, nWidth, 5, 0.f, 0.f, nWidth/256.f, 5.f/8.f );
	fPosY += 5;

	// ����κ� 40 ������ �׸��� (��Ʈ��ũ�⶧��)
	int nBodyHeight = nHeight - 10;		// ���γ��̿��� ���Ʒ� �ܰ��� �� ũ��
	int nPatternCount = nBodyHeight / 40;
	for( int i=0; i<nPatternCount; ++i )
	{
		RenderBitmap( BITMAP_INTERFACE+21, fPosX, fPosY, nWidth, 40, 0.f, 0.f, nWidth/256.f, 40.f/64.f );
		fPosY += 40;
	}
	// ���� �κ� �׸��� (�������� ��Ʈ���� �߶� �׸���)
	if( nBodyHeight > nPatternCount*40 )
	{
		float fRate = (float)( nBodyHeight-nPatternCount*40 ) / 40.0f;
		RenderBitmap( BITMAP_INTERFACE+21, fPosX, fPosY, nWidth, 40*fRate, 0.f, 0.f, nWidth/256.f, (40.f/64.f)*fRate );
		fPosY += 40*fRate;
	}

	// �Ʒ��ʿܰ� �׸���
	RenderBitmap( BITMAP_INTERFACE+22, fPosX, fPosY, nWidth, 5, 0.f, 0.f, nWidth/256.f, 5.f/8.f );

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	DisableAlphaBlend();

	return ptPos;
}

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // #ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
bool CUIManager::PressKey( int nKey )
{
	return false;
}
#endif // #ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING

bool CUIManager::IsInputEnable()
{
	// ������ �Է�â �̻��� �̰͸��� üũ�ؼ� ��� ��ȯ
	if( InputEnable || GuildInputEnable || (g_pUIPopup->GetPopupID() != 0 && g_pUIPopup->IsInputEnable()) )
		return true;
	if( GetFocus() == g_hWnd )
		return false;
	return true;
}

void CUIManager::UpdateInput()
{
}

void CUIManager::Render()
{

}

void CUIManager::CloseAll()
{
	// ��� â �ݱ�
	for( DWORD dwInterface=INTERFACE_FRIEND ; dwInterface<INTERFACE_MAX_COUNT ; ++dwInterface )
	{
		if( g_pUIManager->IsOpen( dwInterface ) )
		{
			Close( dwInterface );
		}
	}

	g_pUIPopup->CancelPopup();
}

bool CUIManager::CloseInterface( list<DWORD>& dwInterfaceFlag, DWORD dwExtraData )
{
	return true;
}

bool CUIManager::IsOpen( DWORD dwInterface )
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	bool bOpen = false;

	if( dwInterface == 0 )
	{
		for( DWORD dwInterface=INTERFACE_FRIEND ; dwInterface<INTERFACE_MAX_COUNT ; ++dwInterface )
		{
			if( IsOpen( dwInterface ) )
				bOpen = true;
		}
	}

	switch( dwInterface )
	{
	case INTERFACE_INVENTORY:				bOpen = HeroInventoryEnable;		break;
	case INTERFACE_STORAGE:					bOpen = StorageInventoryEnable;		break;
	case INTERFACE_PERSONALSHOPSALE:	
	case INTERFACE_PERSONALSHOPPURCHASE:	bOpen = g_bPersonalShopWnd;			break;
	case INTERFACE_SERVERDIVISION:			bOpen = g_bServerDivisionEnable;	break;
	default:								bOpen = false;						break;
	}
	return bOpen;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	if( dwInterface == 0 )
	{
		for( DWORD dwInterface=INTERFACE_FRIEND ; dwInterface<INTERFACE_MAX_COUNT ; ++dwInterface )
		{
			if( IsOpen( dwInterface ) )
				return true;
		}
	}

	switch( dwInterface )
	{
	case INTERFACE_INVENTORY:
		return HeroInventoryEnable;
	case INTERFACE_STORAGE:
		return StorageInventoryEnable;
	case INTERFACE_PERSONALSHOPSALE:
	case INTERFACE_PERSONALSHOPPURCHASE:
		return g_bPersonalShopWnd;
	case INTERFACE_SERVERDIVISION:
		return g_bServerDivisionEnable;
	default:
		return false;
	}
	return false;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
}

bool CUIManager::IsCanOpen( DWORD dwInterfaceFlag )
{
	return true;
}

void CUIManager::GetInterfaceAll( list<DWORD>& outflag )
{
	for ( DWORD flag = INTERFACE_FRIEND; flag < INTERFACE_MAX_COUNT; ++flag )
	{
		outflag.push_back( flag );
	}
}

void CUIManager::GetInsertInterface( list<DWORD>& outflag, DWORD insertflag )
{
	outflag.push_back( insertflag );
}

void CUIManager::GetDeleteInterface( list<DWORD>& outflag, DWORD deleteflag )
{
	for ( list<DWORD>::iterator iter = outflag.begin(); iter != outflag.end(); )
	{
		list<DWORD>::iterator Tempiter = iter;
		++iter;
		DWORD Tempflag = *Tempiter;

		if( Tempflag == deleteflag )
		{
			outflag.erase( Tempiter );
		}
	}
}

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
bool CUIManager::Open( DWORD dwInterface )
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
bool CUIManager::Open( DWORD dwInterface, DWORD dwExtraData )
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	if( IsOpen(INTERFACE_REFINERYINFO) )
		return false;
	if( IsOpen( dwInterface ) )
		return false;
	if( IsCanOpen( dwInterface ) == false)
		return false;
	if( LogOut == true) 
		return false;
	
	list<DWORD> closeinterfaceflag;
	// �ڱ��ڽ��� ������ ��� �������̽�
	GetInterfaceAll( closeinterfaceflag );
	GetDeleteInterface( closeinterfaceflag, dwInterface );
	// ���� ������ ������°� ����.
	GetDeleteInterface( closeinterfaceflag, INTERFACE_FRIEND );

	switch( dwInterface )
	{
	case INTERFACE_INVENTORY:							//## ��������ʴ� UI
		{
			bool bResult = CloseInterface( closeinterfaceflag );
			if( bResult )
			{
				HeroInventoryEnable = true;
#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM												//## �ҽ����� �����.
				//�κ��丮�� �� ������ �� ���� ������ �䱸�Ѵ�.
				if(GetBaseClass(Hero->Class)==CLASS_DARK_LORD)
				{
					SendRequestPetInfo ( 0, 0, EQUIPMENT_WEAPON_LEFT );
					SendRequestPetInfo ( 1, 0, EQUIPMENT_HELPER );
				}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
			}
		}
		break;
	case INTERFACE_PERSONALSHOPSALE:
		{
			// ���� ������ ������°� ����.
			GetDeleteInterface( closeinterfaceflag, INTERFACE_INVENTORY );

			bool bResult = CloseInterface( closeinterfaceflag );
			if( bResult )
			{
				Open( INTERFACE_INVENTORY );

				if(g_iPShopWndType != PSHOPWNDTYPE_NONE) {
					g_ErrorReport.Write("@ OpenPersonalShop : SendRequestInventory\n");
					SendRequestInventory();		//. Ȥ�� ���������� �𸣴� �κ��� ���� �޾ƿ´�
				}

				//. �ν��Ͻ��� �������� ���� �����Ѵ�
				//. �ν��Ͻ��� �̹� �ִٸ� return false;
				CreatePersonalItemTable();

				g_bPersonalShopWnd = true;
				g_iPShopWndType = PSHOPWNDTYPE_SALE;
			}
		}
		break;
	case INTERFACE_PERSONALSHOPPURCHASE:
		{
			bool bResult = CloseInterface( closeinterfaceflag );
			if( bResult )
			{
				Open( INTERFACE_INVENTORY );

				if(g_iPShopWndType != PSHOPWNDTYPE_NONE) {
					g_ErrorReport.Write("@ OpenPersonalShop : SendRequestInventory\n");
					SendRequestInventory();		//. Ȥ�� ���������� �𸣴� �κ��� ���� �޾ƿ´�
				}

				//. �ν��Ͻ��� �������� ���� �����Ѵ�
				//. �ν��Ͻ��� �̹� �ִٸ� return false;
				CreatePersonalItemTable();

				g_bPersonalShopWnd = true;
				g_iPShopWndType = PSHOPWNDTYPE_PURCHASE;
			}
		}
		break;
	case INTERFACE_SERVERDIVISION:
		{
			bool bResult = CloseInterface( closeinterfaceflag );
			if( bResult )
			{
				g_bServerDivisionEnable = true;
				g_bServerDivisionAccept = false;
			}
		}
		break;
	default:
		return false;
	}

	PlayBuffer(SOUND_CLICK01);
	PlayBuffer(SOUND_INTERFACE01);

	return true;
}

bool CUIManager::Close( DWORD dwInterface, DWORD dwExtraData )
{
	if( !IsOpen( dwInterface ) )		return false;

	// ���� ������ �Ұ͵��� �����Ѵ�.
	switch( dwInterface )
	{
	case INTERFACE_INVENTORY:
		{
			bool bResult = true;
			if( bResult )
			{
				list<DWORD> closeinterfaceflag;

				GetInsertInterface( closeinterfaceflag, INTERFACE_TRADE );
				GetInsertInterface( closeinterfaceflag, INTERFACE_STORAGE );
				GetInsertInterface( closeinterfaceflag, INTERFACE_GUILDSTORAGE );
				GetInsertInterface( closeinterfaceflag, INTERFACE_MIXINVENTORY );
				GetInsertInterface( closeinterfaceflag, INTERFACE_PERSONALSHOPSALE );
				GetInsertInterface( closeinterfaceflag, INTERFACE_NPCBREEDER );
				GetInsertInterface( closeinterfaceflag, INTERFACE_NPCSHOP );
				GetInsertInterface( closeinterfaceflag, INTERFACE_SENATUS );
				GetInsertInterface( closeinterfaceflag, INTERFACE_REFINERY );	
				bResult = CloseInterface( closeinterfaceflag, dwExtraData );
				if( bResult )
				{
					list<DWORD> closeflag;
					GetInsertInterface( closeflag, dwInterface );
					CloseInterface( closeflag, dwExtraData );
				}
			}
		}
		break;
	case INTERFACE_STORAGE:
	case INTERFACE_GUILDSTORAGE:
	case INTERFACE_MIXINVENTORY:
	case INTERFACE_TRADE:
	case INTERFACE_NPCBREEDER:
	case INTERFACE_NPCSHOP:
	case INTERFACE_GUARDSMAN:
		{
			list<DWORD> closeinterfaceflag;
			GetInsertInterface( closeinterfaceflag, dwInterface );
			bool bResult = CloseInterface( closeinterfaceflag, dwExtraData );
			if( bResult )
			{
				list<DWORD> closeflag;
				GetInsertInterface( closeflag, INTERFACE_INVENTORY );
				CloseInterface( closeflag, dwExtraData );
			}
		}
		break;
	default:
		{
			list<DWORD> closeinterfaceflag;
			GetInsertInterface( closeinterfaceflag, dwInterface );	
			CloseInterface( closeinterfaceflag, dwExtraData );
		}
		break;
	}

	PlayBuffer(SOUND_CLICK01);
	PlayBuffer(SOUND_INTERFACE01);

	return true;
}
