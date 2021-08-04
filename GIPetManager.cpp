//////////////////////////////////////////////////////////////////////////
//  
//  ��  �� : GIPetManager
//
//  ��  �� : �ְ���.
//
//  ��  ¥ : 2004.03.29.
//
//  �ۼ��� : �� �� ��.
//  
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef PET_SYSTEM

//////////////////////////////////////////////////////////////////////////
//  INCLUDE.
//////////////////////////////////////////////////////////////////////////
#include "PersonalShopTitleImp.h"
#include "CSPetSystem.h"
#include "UIManager.h"
#include "zzzlodterrain.h"
#include "zzzAi.h"
#include "ZzzOpenglUtil.h"
#include "zzzInfomation.h"
#include "zzzBmd.h"
#include "zzzObject.h"
#include "zzztexture.h"
#include "zzzCharacter.h"
#include "zzzscene.h"
#include "zzzinfomation.h"
#include "zzzInterface.h"
#include "zzzinventory.h"
#include "wsclientinline.h"
#include "CSChaosCastle.h"
#include "CSQuest.h"
#include "GIPetManager.h"
#include "npcBreeder.h"

#ifdef LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
#include "ZzzEffect.h"
#endif // LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER

//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
extern  bool    SkillEnable;
extern	char    TextList[30][100];
extern	int     TextListColor[30];
extern	int     TextBold[30];
extern  float   g_fScreenRate_x;	// ��
extern  float   g_fScreenRate_y;
extern  int     CheckX;
extern  int     CheckY;
extern  int     CheckSkill;

namespace giPetManager
{
    //////////////////////////////////////////////////////////////////////////
    //  Global Variable
    //////////////////////////////////////////////////////////////////////////
    static  BYTE    g_byTabBar = 0;    
    static  DWORD   g_iRenderItemIndexBackup = 0;
    static  ITEM    g_RenderItemInfoBackup;// = { 0, };
                     
    static  const   BYTE    g_byCommandNum = 4;

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
    static  PET_INFO        g_PetInfo[PET_TYPE_END];// = { 0, };
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM									//## �ҽ����� �����.


    //////////////////////////////////////////////////////////////////////////
    //  FUNCTION.
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //  PET�޴���.
    //////////////////////////////////////////////////////////////////////////
    
    void    InitPetManager ( void )
    {
        g_byTabBar = 0;
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
		gs_PetInfo.m_dwPetType = PET_TYPE_NONE;
#else //KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
        ZeroMemory ( &g_PetInfo, sizeof( PET_INFO )*PET_TYPE_END );
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM									//## �ҽ����� �����.
    }

    //////////////////////////////////////////////////////////////////////////
    //  �ش� ĳ������ ��ũ ���Ǹ��� �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    void    CreatePetDarkSpirit ( CHARACTER*c )
    {
        DeletePet ( c );

        if ( InChaosCastle()==true ) return;

        CSPetSystem* pPet = new CSPetDarkSpirit ( c );
        c->m_pPet = (void *)pPet;
    }

    
    //////////////////////////////////////////////////////////////////////////
    //  
    //////////////////////////////////////////////////////////////////////////
    void    CreatePetDarkSpirit_Now ( CHARACTER* c )
    {
        if ( c->Weapon[1].Type==MODEL_HELPER+5 )
        {
            DeletePet ( c );
            CSPetSystem* pPet = new CSPetDarkSpirit ( c );
            c->m_pPet = (void *)pPet;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    //  �ֵ��� �̵� ó��.
    //////////////////////////////////////////////////////////////////////////
    void    MovePet ( CHARACTER*c )
    {
        if ( c->m_pPet!=NULL )
        {
            CSPetSystem* pPet = (CSPetSystem*)c->m_pPet;
            pPet->MovePet ();
        }
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    //  ���� ȭ�鿡 ����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    void    RenderPet ( CHARACTER* c )
    {
		OBJECT* o    = &c->Object;
        if ( c->m_pPet!=NULL )
        {
            CSPetSystem* pPet = (CSPetSystem*)c->m_pPet;

			if( g_isCharacterBuff(o,eBuff_Cloaking) )
			{
				pPet->RenderPet (10); //�������̴�...
			}
			else
			{
#ifdef PBG_FIX_DARKPET_RENDER
				ITEM* pEquipmentItemSlot = &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT];
				PET_INFO* pPetInfo = giPetManager::GetPetInfo(pEquipmentItemSlot);
				pPet->SetPetInfo(pPetInfo);
				//pPet->SetPetInfo((PET_INFO*)c->m_pPet);
#endif //PBG_FIX_DARKPET_RENDER
				pPet->RenderPet ();
			}
        }
    }


    //////////////////////////////////////////////////////////////////////////
    //  ��� ����Ʈ���� ���� ����� ã�´�.
    //////////////////////////////////////////////////////////////////////////
    bool    SelectPetCommand ( void )
    {
        if ( GetBaseClass(Hero->Class)!=CLASS_DARK_LORD ) 
			return false;
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
		if(SEASON3B::IsPress(VK_SHIFT) == TRUE)
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
        if ( HIBYTE(GetAsyncKeyState(VK_SHIFT) )==128 )
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
        {
		    for ( int i=0; i<(AT_PET_COMMAND_END-AT_PET_COMMAND_DEFAULT); i++ )
            {
#ifdef KWAK_FIX_KEY_STATE_RUNTIME_ERR
				if(SEASON3B::IsRepeat('1' + i) == TRUE)
				//if(GetAsyncKeyState('1' + i))
#else // KWAK_FIX_KEY_STATE_RUNTIME_ERR
      		    if ( HIBYTE( GetAsyncKeyState('1'+i) ) ) 
#endif // KWAK_FIX_KEY_STATE_RUNTIME_ERR
                {
                    Hero->CurrentSkill = AT_PET_COMMAND_DEFAULT+i;
                    return true;
                }
            }
        }
        return false;
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� Ŀ�ǵ� ����Ʈ�� �����ش�.
    //////////////////////////////////////////////////////////////////////////
    void    MovePetCommand ( CHARACTER* c )
    {
        //  ���� �����Ѵٸ�.
        if ( c->m_pPet!=NULL )
        {
			int SkillCount = 0;
            int Width, Height, x, y;
			for ( int i=AT_PET_COMMAND_DEFAULT; i<AT_PET_COMMAND_END; i++ )
			{
				Width=32; Height=36; x=320-(AT_PET_COMMAND_END-AT_PET_COMMAND_DEFAULT)*Width/2+SkillCount*Width; y=330;
				SkillCount++;

                if ( MouseX>=x && MouseX<x+Width && MouseY>=y && MouseY<y+Height )
                {
                    CheckSkill = i;
                    CheckX = x+Width/2;
                    CheckY = y;
                    MouseOnWindow = true;
                    if ( MouseLButtonPush )
                    {
                        MouseLButtonPush = false;
                        Hero->CurrentSkill = i;
                        SkillEnable = false;
                        PlayBuffer(SOUND_CLICK01);
                        MouseUpdateTime = 0;
                        MouseUpdateTimeMax = 6;
                    }
                }
			}
        }
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���õ� Ŀ�ǵ带 ������ �˸���.
    //////////////////////////////////////////////////////////////////////////
    bool    SendPetCommand ( CHARACTER* c, int Index )
    {
        if ( c->m_pPet!=NULL )
        {
            if ( MouseRButtonPush || MouseRButton )
            {
                if ( Index>=AT_PET_COMMAND_DEFAULT && Index<AT_PET_COMMAND_END )
                {
                    CSPetSystem* pPet = (CSPetSystem*)c->m_pPet;

                    if ( Index==AT_PET_COMMAND_TARGET )
                    {
                        if ( CheckAttack() )
                        {
                            CHARACTER* tc = &CharactersClient[SelectedCharacter];
                            if ( SelectedCharacter!=-1 && ( tc->Object.Kind==KIND_MONSTER || tc->Object.Kind==KIND_PLAYER ) )
                            {
                                SendRequestPetCommand ( pPet->GetPetType(), Index-AT_PET_COMMAND_DEFAULT, tc->Key );
                            }
                        }
                    }
                    else
                    {
                        SendRequestPetCommand ( pPet->GetPetType(), Index-AT_PET_COMMAND_DEFAULT, 0xffff );
                    }
                    MouseRButtonPop = false;
                    MouseRButtonPush= false;
                    MouseRButton	= false;
                    
                    MouseRButtonPress = 0;
                    return true;
                }
            }
        }
        return false;
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� ����� �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    void    SetPetCommand ( CHARACTER* c, int Key, BYTE Cmd )
    {
        if ( c->m_pPet!=NULL )
        {
            CSPetSystem* pPet = (CSPetSystem*)c->m_pPet;
            pPet->SetCommand ( Key, Cmd );
        }
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� ����� ������.
    //////////////////////////////////////////////////////////////////////////
    void    SetAttack ( CHARACTER* c, int Key, int attackType )
    {
        if ( c->m_pPet!=NULL )
        {
            CSPetSystem* pPet = (CSPetSystem*)c->m_pPet;
            pPet->SetAttack ( Key, attackType );
        }
    }


    //////////////////////////////////////////////////////////////////////////
    //  �� ��� ������ �Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    bool    RenderPetCmdInfo ( int sx, int sy, int Type )
    {
        if ( Type<AT_PET_COMMAND_DEFAULT || Type>=AT_PET_COMMAND_END ) return false;

        int  TextNum = 0;
        int  SkipNum = 0;
        
        if ( GetBaseClass(Hero->Class)==CLASS_DARK_LORD )
        {
            int cmdType = Type-AT_PET_COMMAND_DEFAULT;

        	TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = true;
            sprintf ( TextList[TextNum], GlobalText[1219+cmdType] ); TextNum++; SkipNum++;
            
        	TextListColor[TextNum] = TEXT_COLOR_WHITE;
        	sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
        	sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
            switch ( cmdType )
            {
            case PET_CMD_DEFAULT : sprintf ( TextList[TextNum], GlobalText[1223] ); TextNum++; SkipNum++; break;
            case PET_CMD_RANDOM  : sprintf ( TextList[TextNum], GlobalText[1224] ); TextNum++; SkipNum++; break;
            case PET_CMD_OWNER   : sprintf ( TextList[TextNum], GlobalText[1225] ); TextNum++; SkipNum++; break;
            case PET_CMD_TARGET  : sprintf ( TextList[TextNum], GlobalText[1226] ); TextNum++; SkipNum++; break;
            }
            
            SIZE TextSize = {0, 0};	
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
            int Height = (int)( ((TextNum - SkipNum) * TextSize.cy + SkipNum * TextSize.cy / 2) / g_fScreenRate_y );
            sy -= Height;
            
            RenderTipTextList(sx,sy,TextNum,0);
            return true;
        }
        return false;
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    //  �ش� ĳ������ ���� �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
    void DeletePet( CHARACTER* c )
    {
        if( c->m_pPet!=NULL )
        {
#ifdef LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
			if( c->m_pPet != NULL )
			{
				int iObjectType = ((CSPetSystem *)c->m_pPet)->GetObjectType();
				TerminateOwnerEffectObject( iObjectType );	
			}
			
			delete ((CSPetSystem *)c->m_pPet);
			c->m_pPet = NULL;
#else // LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
	#ifdef YDG_DARK_SPIRIT_CRASH_BECAUSEOF_FIX_MEMORY_LEAK
				c->m_pPet = NULL;
	#else	// YDG_DARK_SPIRIT_CRASH_BECAUSEOF_FIX_MEMORY_LEAK
	#ifdef YDG_FIX_MEMORY_LEAK_0905
				delete ((CSPetSystem *)c->m_pPet);
				c->m_pPet = NULL;
	#else	// YDG_FIX_MEMORY_LEAK_0905
				delete c->m_pPet;
				c->m_pPet = NULL;
	#endif	// YDG_FIX_MEMORY_LEAK_0905
	#endif	// YDG_DARK_SPIRIT_CRASH_BECAUSEOF_FIX_MEMORY_LEAK
#endif // LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
        }
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� ��û�� ���� ������ ��� ������ �ʱ�ȭ.
    //////////////////////////////////////////////////////////////////////////
    void    InitItemBackup( void )
    {
        ZeroMemory ( &g_RenderItemInfoBackup, sizeof( ITEM ) );
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
		gs_PetInfo.m_dwPetType = PET_TYPE_NONE;
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
    }


    //////////////////////////////////////////////////////////////////////////
    //  ���� ������ �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	bool RequestPetInfo(int sx, int sy, ITEM* pItem)
	{
		DWORD itemIndex = MAKELONG ( sx, sy );
		if ( gs_PetInfo.m_dwPetType == PET_TYPE_NONE || g_iRenderItemIndexBackup!=itemIndex 
			|| g_RenderItemInfoBackup.Type != pItem->Type || g_RenderItemInfoBackup.Level!=pItem->Level )
		{
			g_iRenderItemIndexBackup = itemIndex;
			g_RenderItemInfoBackup.Type = pItem->Type;
			g_RenderItemInfoBackup.Level= pItem->Level;
			
			BYTE PetType = PET_TYPE_DARK_SPIRIT;
			if ( pItem->Type==ITEM_HELPER+4 )
			{
				PetType = PET_TYPE_DARK_HORSE;
			}
			
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			int iInvenType = 0, iItemIndex = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			int iInvenType, iItemIndex;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			if((iItemIndex = g_pMyInventory->GetPointedItemIndex()) != -1)
			{
				iInvenType = 0; // �ڱ� �κ��丮
			}
			else if((iItemIndex = g_pMyShopInventory->GetPointedItemIndex()) != -1)
			{
				iInvenType = 0; // �ڱ� �ǸŻ���
			}
			else if((iItemIndex = g_pStorageInventory->GetPointedItemIndex()) != -1)
			{
				iInvenType = 1; // â��
			}
			else if((iItemIndex = g_pTrade->GetPointedItemIndexMyInven()) != -1)
			{
				iInvenType = 2; // �ŷ�â(��)
			}
			else if((iItemIndex = g_pTrade->GetPointedItemIndexYourInven()) != -1)
			{
				iInvenType = 3; // �ŷ�â(��)
			}
			else if((iItemIndex = g_pMixInventory->GetPointedItemIndex()) != -1)
			{
				iInvenType = 4; // ����
			}
			else if((iItemIndex = g_pPurchaseShopInventory->GetPointedItemIndex()) != -1)
			{
				iInvenType = 5; // ���Ż���
			}
			else if((iItemIndex = g_pNPCShop->GetPointedItemIndex()) != -1)
			{
				iInvenType = 6; // NPC����
			}
			SendRequestPetInfo( PetType, iInvenType, iItemIndex );

			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------------------
	// SetPetInfo
	// �� ���� ����
	void SetPetInfo( BYTE InvType, BYTE InvPos, PET_INFO* pPetinfo )
	{
		// ������ �� ��� (�� ����â�� ������ Data)
		CalcPetInfo(pPetinfo);
		
		// hero�� ������ �� ����ó��
		// [InvType] - 0:�κ��丮, 254:������, 255:�����ٿ�
		if( (InvType == 0) || (InvType==254) || (InvType==255) )
		{
			// �ɸ��Ϳ� ������ ��ũȣ��, ��ũ���Ǹ�
			if( (InvPos == EQUIPMENT_HELPER) || (InvPos == EQUIPMENT_WEAPON_LEFT) )
			{
				PET_INFO* pHeroPetInfo = Hero->GetEquipedPetInfo(pPetinfo->m_dwPetType);
				memcpy(pHeroPetInfo, pPetinfo, sizeof(PET_INFO));

				// ���� ��/�ٿ� ����Ʈ ó��
				if( pPetinfo->m_dwPetType == PET_TYPE_DARK_SPIRIT )
				{
					if( Hero->m_pPet == NULL )
						return;

					// ��ũ���Ǹ��̶��, CSPetSystem�� PetInfo Pointer ����
					((CSPetSystem*)Hero->m_pPet)->SetPetInfo( pHeroPetInfo );
					
					// ������, ���� �ٿ� ȿ��.
					if( InvType==254 )         //  ������.
					{
						((CSPetSystem*)Hero->m_pPet)->Eff_LevelUp();
					}
					else if( InvType==255 )    //  �����ٿ�.
					{
						((CSPetSystem*)Hero->m_pPet)->Eff_LevelDown();
					}
				}
				else if( pPetinfo->m_dwPetType == PET_TYPE_DARK_HORSE )
				{
					// ������, ���� �ٿ� ȿ��.
					if ( InvType==254 || InvType==255 )    //  254:������ 255:�����ٿ�.
					{
						Hero->Object.ExtState = InvType-253;
					}
					
					// ������ ������ �����Ѵ�.
					SetPetItemConvert( &CharacterMachine->Equipment[EQUIPMENT_HELPER], pHeroPetInfo);
				}

				// �ɸ��� ���� ���
				CharacterMachine->CalculateAll();
				
				//return;
			}
		}

		// Tooltip Render�� ������
		memcpy( &gs_PetInfo, pPetinfo, sizeof(PET_INFO) );
	}

	//-------------------------------------------------------------------------------------
	// GetPetInfo
	// �� ���� ��������
	PET_INFO* GetPetInfo(ITEM* pItem)
	{		
		if( pItem == &CharacterMachine->Equipment[EQUIPMENT_HELPER] )				// ������ ��ũȣ��
		{
			return Hero->GetEquipedPetInfo(PET_TYPE_DARK_HORSE);
		}
		else if(pItem == &CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT])		// ������ ��ũ���Ǹ�
		{
			return Hero->GetEquipedPetInfo(PET_TYPE_DARK_SPIRIT);
		}
		
		// �������� ���� �� ������.
		return &gs_PetInfo;
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM														//## �ҽ����� �����
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	void	SetPetInfo ( BYTE InvType, BYTE Index, const PET_INFO& Petinfo )
    {
		if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PET))
        {
            //  ��ũ���Ǹ�.
			if ( Hero->m_pPet!=NULL && Petinfo.m_dwPetType==PET_TYPE_DARK_SPIRIT )
            {
                CSPetSystem* pPet = (CSPetSystem*)Hero->m_pPet;
                pPet->CalcPetInformation ( Petinfo );
            }
            g_PetInfo[Petinfo.m_dwPetType].m_wLevel = Petinfo.m_wLevel;
			g_PetInfo[Petinfo.m_dwPetType].m_wLife  = Petinfo.m_wLife;
            g_PetInfo[Petinfo.m_dwPetType].m_dwExp1 = Petinfo.m_dwExp1;

            CalcPetInfo ( Petinfo.m_dwPetType );
        }
        else
        {
			g_PetInfo[Petinfo.m_dwPetType].m_wLevel = Petinfo.m_wLevel;
            g_PetInfo[Petinfo.m_dwPetType].m_wLife  = Petinfo.m_wLife;
            g_PetInfo[Petinfo.m_dwPetType].m_dwExp1 = Petinfo.m_dwExp1;

			CalcPetInfo ( Petinfo.m_dwPetType );

            //  
            if ( InvType==0 || InvType==254 || InvType==255 ) 
            {
				if ( Petinfo.m_dwPetType==PET_TYPE_DARK_SPIRIT && Index==EQUIPMENT_WEAPON_LEFT ) //  ��ũ���Ǹ�.
                {
                    if ( Hero->m_pPet!=NULL )
                    {
                        CSPetSystem* pPet = (CSPetSystem*)Hero->m_pPet;
						pPet->CalcPetInformation ( Petinfo );

                        //  ������, ���� �ٿ� ȿ��.
                        if ( InvType==254 )         //  ������.
                        {
                            pPet->Eff_LevelUp ();
                        }
                        else if ( InvType==255 )    //  �����ٿ�.
                        {
                            pPet->Eff_LevelDown ();
                        }
                    }
                }
                else if ( Petinfo.m_dwPetType==PET_TYPE_DARK_HORSE && Index==EQUIPMENT_HELPER ) //  ��ũȣ��.
                {
					g_PetInfo[Petinfo.m_dwPetType].m_wLevel = Petinfo.m_wLevel;
					g_PetInfo[Petinfo.m_dwPetType].m_wLife  = Petinfo.m_wLife;
					g_PetInfo[Petinfo.m_dwPetType].m_dwExp1 = Petinfo.m_dwExp1;
                    
                    //  ������, ���� �ٿ� ȿ��.
                    if ( InvType==254 || InvType==255 )    //  254:������ 255:�����ٿ�.
                    {
                        Hero->Object.ExtState = InvType-253;
                    }
                    CalcPetInfo ( Petinfo.m_dwPetType );

                    //  ������ ������ �ٽ� �����Ѵ�.
                    ItemConvert ( &CharacterMachine->Equipment[EQUIPMENT_HELPER] );
                }
            }
        }
    }
#else // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER			// ������ �� ������ �ϴ� �ҽ�
    //////////////////////////////////////////////////////////////////////////
    //  ���� ������ �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
	void    SetPetInfo ( BYTE PetType, BYTE InvType, BYTE Index, BYTE Level, int exp )
    {
		if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PET))
        {
            //  ��ũ���Ǹ�.
            if ( Hero->m_pPet!=NULL && PetType==PET_TYPE_DARK_SPIRIT )
            {
                CSPetSystem* pPet = (CSPetSystem*)Hero->m_pPet;
                pPet->CalcPetInformation ( Level, exp );
            }
            g_PetInfo[PetType].m_wLevel = Level;
			g_PetInfo[PetType].m_wLife  = CharacterMachine->Equipment[Index].Durability;
            g_PetInfo[PetType].m_dwExp1 = exp;

            CalcPetInfo ( PetType );
        }
        else
        {
			g_PetInfo[PetType].m_wLevel = Level;
            g_PetInfo[PetType].m_wLife  = g_pMyInventory->GetDurabilityPointedItem();
            g_PetInfo[PetType].m_dwExp1 = exp;
            
            CalcPetInfo ( PetType );

            //  
            if ( InvType==0 || InvType==254 || InvType==255 ) 
            {
                if ( PetType==PET_TYPE_DARK_SPIRIT && Index==EQUIPMENT_WEAPON_LEFT ) //  ��ũ���Ǹ�.
                {
                    if ( Hero->m_pPet!=NULL )
                    {
                        CSPetSystem* pPet = (CSPetSystem*)Hero->m_pPet;
                        pPet->CalcPetInformation ( Level, exp );

                        //  ������, ���� �ٿ� ȿ��.
                        if ( InvType==254 )         //  ������.
                        {
                            pPet->Eff_LevelUp ();
                        }
                        else if ( InvType==255 )    //  �����ٿ�.
                        {
                            pPet->Eff_LevelDown ();
                        }
                    }
                }
                else if ( PetType==PET_TYPE_DARK_HORSE && Index==EQUIPMENT_HELPER ) //  ��ũȣ��.
                {
                    g_PetInfo[PetType].m_wLevel = Level;
                    g_PetInfo[PetType].m_wLife  = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
                    g_PetInfo[PetType].m_dwExp1 = exp;
                    
                    //  ������, ���� �ٿ� ȿ��.
                    if ( InvType==254 || InvType==255 )    //  254:������ 255:�����ٿ�.
                    {
                        Hero->Object.ExtState = InvType-253;
                    }
                    CalcPetInfo ( PetType );

                    //  ������ ������ �ٽ� �����Ѵ�.
                    ItemConvert( &CharacterMachine->Equipment[EQUIPMENT_HELPER] );
                }
            }
        }
    }

#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER			// ������ �� ������ �ϴ� �ҽ�
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM																//## �ҽ����� �����

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM																	//## �ҽ����� �����
	void	GetPetInfo(PET_INFO &PetInfo, short type)
	{
		PetInfo = g_PetInfo[421-type];
	}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM																//## �ҽ����� �����
	
    //////////////////////////////////////////////////////////////////////////
    //  ������ ���.
    //////////////////////////////////////////////////////////////////////////
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
    void CalcPetInfo( PET_INFO* pPetInfo )
    {
        int Charisma = CharacterAttribute->Charisma+CharacterAttribute->AddCharisma;
        int Strength = CharacterAttribute->Strength+CharacterAttribute->AddStrength;

        int Level = pPetInfo->m_wLevel+1;

        switch ( pPetInfo->m_dwPetType )
        {
        case PET_TYPE_DARK_SPIRIT: //  ��ũ���Ǹ�.
            pPetInfo->m_dwExp2      = ((10+Level)*Level*Level*Level*100);
            pPetInfo->m_wDamageMin  = (180+(pPetInfo->m_wLevel*15)+(Charisma/8));
            pPetInfo->m_wDamageMax  = (200+(pPetInfo->m_wLevel*15)+(Charisma/4));
            pPetInfo->m_wAttackSpeed= (20+(pPetInfo->m_wLevel*4/5)+(Charisma/50));
            pPetInfo->m_wAttackSuccess = (1000+pPetInfo->m_wLevel)+(pPetInfo->m_wLevel*15);
            break;

        case PET_TYPE_DARK_HORSE: //  ��ũȣ��.
            pPetInfo->m_dwExp2      = ((10+Level)*Level*Level*Level*100);
            pPetInfo->m_wDamageMin  = (Strength/10)+(Charisma/10)+(pPetInfo->m_wLevel*5);
            pPetInfo->m_wDamageMax  = pPetInfo->m_wDamageMin+(pPetInfo->m_wDamageMin/2);
            pPetInfo->m_wAttackSpeed= (20+(pPetInfo->m_wLevel*4/5)+(Charisma/50));
            pPetInfo->m_wAttackSuccess = (1000+pPetInfo->m_wLevel)+(pPetInfo->m_wLevel*15);
            break;
        }
    }
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
    void    CalcPetInfo ( BYTE petType )
    {
        int Charisma = CharacterAttribute->Charisma+CharacterAttribute->AddCharisma;
        int Strength = CharacterAttribute->Strength+CharacterAttribute->AddStrength;

        int Level = g_PetInfo[petType].m_wLevel+1;

        switch ( petType )
        {
        case 0: //  ��ũ���Ǹ�.
            g_PetInfo[petType].m_dwExp2      = ((10+Level)*Level*Level*Level*100);
            g_PetInfo[petType].m_wDamageMin  = (180+(g_PetInfo[petType].m_wLevel*15)+(Charisma/8));
            g_PetInfo[petType].m_wDamageMax  = (200+(g_PetInfo[petType].m_wLevel*15)+(Charisma/4));
            g_PetInfo[petType].m_wAttackSpeed= (20+(g_PetInfo[petType].m_wLevel*4/5)+(Charisma/50));
            g_PetInfo[petType].m_wAttackSuccess = (1000+g_PetInfo[petType].m_wLevel)+(g_PetInfo[petType].m_wLevel*15);
            break;

        case 1: //  ��ũȣ��.
            g_PetInfo[petType].m_dwExp2      = ((10+Level)*Level*Level*Level*100);
            g_PetInfo[petType].m_wDamageMin  = (Strength/10)+(Charisma/10)+(g_PetInfo[petType].m_wLevel*5);
            g_PetInfo[petType].m_wDamageMax  = g_PetInfo[petType].m_wDamageMin+(g_PetInfo[petType].m_wDamageMin/2);
            g_PetInfo[petType].m_wAttackSpeed= (20+(g_PetInfo[petType].m_wLevel*4/5)+(Charisma/50));
            g_PetInfo[petType].m_wAttackSuccess = (1000+g_PetInfo[petType].m_wLevel)+(g_PetInfo[petType].m_wLevel*15);
            break;
        }
    }
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM


    //////////////////////////////////////////////////////////////////////////
    //  ������ ������ �����Ѵ�.
    //////////////////////////////////////////////////////////////////////////
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
    void SetPetItemConvert(ITEM* ip, PET_INFO* pPetInfo)
    {
		// ��ũȣ��
        if ( ip->Type==ITEM_HELPER+4 )
        {
            //  ���� ����.
            int Index = 0;
            for ( int i=0; i<ip->SpecialNum; ++i )
            {
                if ( ip->Special[i]==AT_SET_OPTION_IMPROVE_DEFENCE )
                {
                    Index = i;
                    break;
                }
            }

            if ( Index==0 )
            {
                ip->SpecialValue[ip->SpecialNum] = (5+(CharacterAttribute->Dexterity/20)+pPetInfo->m_wLevel*2);
                ip->Special[ip->SpecialNum] = AT_SET_OPTION_IMPROVE_DEFENCE;ip->SpecialNum++;
            }
            else
            {
                ip->SpecialValue[Index] = (5+(CharacterAttribute->Dexterity/20)+pPetInfo->m_wLevel*2);
                ip->Special[Index] = AT_SET_OPTION_IMPROVE_DEFENCE;
            }
        }
    }
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
    void    ItemConvert ( ITEM* ip )
    {
        if ( ip->Type==ITEM_HELPER+4 )
        {
            //  ���� ����.
            int Index = 0;
            for ( int i=0; i<ip->SpecialNum; ++i )
            {
                if ( ip->Special[i]==AT_SET_OPTION_IMPROVE_DEFENCE )
                {
                    Index = i;
                    break;
                }
            }

            if ( Index==0 )
            {
                ip->SpecialValue[ip->SpecialNum] = (5+(CharacterAttribute->Dexterity/20)+g_PetInfo[PET_TYPE_DARK_HORSE].m_wLevel*2);
                ip->Special[ip->SpecialNum] = AT_SET_OPTION_IMPROVE_DEFENCE;ip->SpecialNum++;
            }
            else
            {
                ip->SpecialValue[Index] = (5+(CharacterAttribute->Dexterity/20)+g_PetInfo[PET_TYPE_DARK_HORSE].m_wLevel*2);
                ip->Special[Index] = AT_SET_OPTION_IMPROVE_DEFENCE;
            }
        }
    }
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM


    //////////////////////////////////////////////////////////////////////////
    //  ������ ���� ����.
    //////////////////////////////////////////////////////////////////////////
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
    DWORD GetPetItemValue( PET_INFO* pPetInfo )
    {
        DWORD dwGold = 0;

		if( pPetInfo->m_dwPetType == -1 )
			return dwGold;

        switch ( pPetInfo->m_dwPetType )
        {
        case PET_TYPE_DARK_HORSE:       //  ��ũȣ��.
            dwGold = pPetInfo->m_wLevel*2000000;
            break;

        case PET_TYPE_DARK_SPIRIT:      //  ��ũ���Ǹ�.
			dwGold = pPetInfo->m_wLevel*1000000;
            break;
        }

        return dwGold;
    }
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
    DWORD   ItemValue ( PET_TYPE pType )
    {
        DWORD gold = 0;
        switch ( pType )
        {
        case PET_TYPE_DARK_HORSE:       //  ��ũȣ��.
#ifdef PBG_FIX_REPAIRGOLD_DARKPAT
			SendRequestPetInfo(PET_TYPE_DARK_HORSE, 0, g_pMyInventory->GetPointedItemIndex());
#endif //PBG_FIX_REPAIRGOLD_DARKPAT
            gold = g_PetInfo[pType].m_wLevel*2000000;
            break;

        case PET_TYPE_DARK_SPIRIT:      //  ��ũ���Ǹ�.
#ifdef PBG_FIX_REPAIRGOLD_DARKPAT
			SendRequestPetInfo(PET_TYPE_DARK_SPIRIT, 0, g_pMyInventory->GetPointedItemIndex());
#endif //PBG_FIX_REPAIRGOLD_DARKPAT
			gold = g_PetInfo[pType].m_wLevel*1000000;
            break;
        }
        return gold;
    }
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM

    
    //////////////////////////////////////////////////////////////////////////
    //  �� �������� ������ ǥ���Ѵ�.
    //////////////////////////////////////////////////////////////////////////
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	bool RenderPetItemInfo( int sx, int sy, ITEM* pItem, int iInvenType )
	{
		// �������� PetInfo�� ��û �� �� gs_PetInfo�� Render

		PET_INFO* pPetInfo = GetPetInfo( pItem );

		if( pPetInfo->m_dwPetType == PET_TYPE_NONE )
			return false;
		
		int TextNum = 0;
		int SkipNum = 0;
		int RequireLevel = 0;
		int RequireCharisma = 0;
		
		//  �������� ������ ǥ���Ѵ�.
		if ( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) )
		{
			char  Text[100];
			DWORD Gold = ( GetPetItemValue( &giPetManager::gs_PetInfo ) / 3 );
			Gold = Gold/100*100;
			
			ConvertGold( Gold,Text );
			sprintf ( TextList[TextNum], GlobalText[63], Text );
			
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
			TextBold[TextNum] = true;
			TextNum++;
			sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
		}
		else if( (iInvenType == SEASON3B::TOOLTIP_TYPE_MY_SHOP) || (iInvenType == SEASON3B::TOOLTIP_TYPE_PURCHASE_SHOP) )
		{
			//. ��ϵ� ��ǰ�� �ѿ����� ����Ѵ�
			int price = 0;
			int indexInv = (MAX_EQUIPMENT + MAX_INVENTORY)+(pItem->y*COL_PERSONALSHOP_INVEN)+pItem->x;
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
				if(((int)gold < price) && (g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE))
#else // _VS2008PORTING
				if(gold < price && g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE)
#endif // _VS2008PORTING
				{
					TextListColor[TextNum] = TEXT_COLOR_RED;
					TextBold[TextNum] = true;
					// [423] : "���� �����մϴ�."
					sprintf(TextList[TextNum], GlobalText[423]);
					TextNum++;
					sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
				}
			}
			else if(g_IsPurchaseShop == PSHOPWNDTYPE_SALE)			// ���ݼ���
			{
				TextListColor[TextNum] = TEXT_COLOR_RED;
				TextBold[TextNum] = true;
				// [1101] : "��Ŭ������ ���ݼ�������"
				sprintf(TextList[TextNum], GlobalText[1101]);
				TextNum++;
				sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
			}	
		}
		
		TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = true;
		if ( pItem->Type==ITEM_HELPER+4 )      //  ��ũȣ��.
		{
			RequireLevel = (218+(pPetInfo->m_wLevel*2));
			RequireCharisma = 0;

			// [1187] : "��ũȣ��"
			sprintf ( TextList[TextNum], GlobalText[1187] ); TextNum++; SkipNum++;		
		}
		else if ( pItem->Type==ITEM_HELPER+5 ) //  ��ũ���Ǹ�.
		{
			RequireCharisma = (185+(pPetInfo->m_wLevel*15));

			// [1214] : "��ũ���Ǹ�"
			sprintf ( TextList[TextNum], GlobalText[1214] ); TextNum++; SkipNum++;		
		}
		
		TextListColor[TextNum] = TEXT_COLOR_WHITE;
		sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
		sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
		
		// [201] : "����ġ: %u/%u"
		sprintf ( TextList[TextNum], GlobalText[201], pPetInfo->m_dwExp1, pPetInfo->m_dwExp2 ); TextNum++; SkipNum++;	
		// [368] : "����"
		sprintf ( TextList[TextNum], "%s : %d", GlobalText[368], pPetInfo->m_wLevel ); TextNum++; SkipNum++;				
		
		if ( pItem->Type==ITEM_HELPER+5 )	// ��ũ���Ǹ� ����
		{
			// [203] : "���ݷ�(��): %d~%d (%d)"
			sprintf ( TextList[TextNum], GlobalText[203], pPetInfo->m_wDamageMin, pPetInfo->m_wDamageMax, pPetInfo->m_wAttackSuccess ); TextNum++; SkipNum++;
			// [64] : "���ݼӵ�: %d"
			sprintf ( TextList[TextNum], GlobalText[64], pPetInfo->m_wAttackSpeed ); TextNum++; SkipNum++;
		}
		// [70] : "����: %d"
		sprintf ( TextList[TextNum], GlobalText[70], pPetInfo->m_wLife ); TextNum++; SkipNum++;

		if ( pItem->Type==ITEM_HELPER+4 )	// ��ũȣ�� ����
		{
			// [76] : "��� ������ ����: %d"
			sprintf ( TextList[TextNum], GlobalText[76], RequireLevel );
			
			if ( CharacterAttribute->Level < RequireLevel )
			{
				TextListColor[TextNum] = TEXT_COLOR_RED;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf ( TextList[TextNum], GlobalText[74], RequireLevel-CharacterAttribute->Level );
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
		else if ( pItem->Type==ITEM_HELPER+5 )		// ��ũ���Ǹ�����
		{
			// [698] : "��� ������ ���: %d"
			sprintf ( TextList[TextNum], GlobalText[698], RequireCharisma );
			
			WORD Charisma;
			Charisma = CharacterAttribute->Charisma + CharacterAttribute->AddCharisma;
			
			if ( Charisma<RequireCharisma )
			{
				TextListColor[TextNum] = TEXT_COLOR_RED;
				TextBold[TextNum] = false;
				TextNum++;
				sprintf ( TextList[TextNum], GlobalText[74], RequireCharisma-Charisma );
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

		sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
#ifdef KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
		if ( GetBaseClass(Hero->Class) == CLASS_DARK_LORD )
			TextListColor[TextNum] = TEXT_COLOR_WHITE;
		else
			TextListColor[TextNum] = TEXT_COLOR_DARKRED;
#else // KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
		TextListColor[TextNum] = TEXT_COLOR_DARKRED;
#endif // KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
		// [61] : "%s ��� ����"
		// [24] : "��ũ�ε�"
		sprintf ( TextList[TextNum], GlobalText[61], GlobalText[24] ); TextNum++; SkipNum++;
		
		//---------------------------------------------------------
		//  �ɼ����.
		for ( int i=0; i<pItem->SpecialNum; ++i )
		{
			SetPetItemConvert(pItem, &gs_PetInfo);
			GetSpecialOptionText( pItem->Type, TextList[TextNum], pItem->Special[i], pItem->SpecialValue[i], 0 );
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;TextNum++; SkipNum++;
		}
		
		//  ��ũȣ������ �ɼ�. ( ȭ�鿡 ǥ�ø� ).
		if( pItem->Type==ITEM_HELPER+4 )
		{
			// [744] : "%d%% ������ ���"
			sprintf ( TextList[TextNum], GlobalText[744], (30+pPetInfo->m_wLevel)/2 ); 
			TextListColor[TextNum] = TEXT_COLOR_BLUE; TextNum++; SkipNum++;

			// [1188] : "���� ���� �Ÿ� %d����"
			sprintf ( TextList[TextNum], GlobalText[1188], 2 );
			TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false;TextNum++;
		}
		
		SIZE TextSize = {0, 0};	
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		int Height = (int)( ((TextNum - SkipNum) * TextSize.cy + SkipNum * TextSize.cy / 2) / g_fScreenRate_y );
		if(sy-Height >= 0)
			sy -= Height;
		
		bool isrendertooltip = true;
#ifdef NEW_USER_INTERFACE_SHELL
		isrendertooltip = g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_PARTCHARGE_SHOP ) ? false : true;
#endif //NEW_USER_INTERFACE_SHELL
		
		if( isrendertooltip )
		{
			RenderTipTextList(sx,sy,TextNum,0);
		}
		
		return true;
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
    bool    RenderPetItemInfo ( int sx, int sy, ITEM* ip, bool Sell )
    {
		// ��ũ��ȣ��/��ũ���Ǹ�
        if ( ip->Type==ITEM_HELPER+4 || ip->Type==ITEM_HELPER+5 ) 
        {
			// ���� �����۰� g_iRenderItemIndexBackup ����� �������� �ٸ���
			// (�������� �������� �ѹ��� ���� �� ����Ⱦ����۰� ���Ͽ� �ٸ��� ������ �״�� ���)
            DWORD itemIndex = MAKELONG ( sx, sy );
            if ( g_iRenderItemIndexBackup!=itemIndex || g_RenderItemInfoBackup.Type != ip->Type || g_RenderItemInfoBackup.Level!=ip->Level )
            {
                g_iRenderItemIndexBackup = itemIndex;
                g_RenderItemInfoBackup.Type = ip->Type;
                g_RenderItemInfoBackup.Level= ip->Level;
            
                BYTE PetType = 0;
                if ( ip->Type==ITEM_HELPER+4 )
                {
                    PetType = 1;
                }
            
				int iInvenType, iItemIndex;
				if((iItemIndex = g_pMyInventory->GetPointedItemIndex()) != -1)
				{
					iInvenType = 0; // �ڱ� �κ��丮
				}
				else if((iItemIndex = g_pMyShopInventory->GetPointedItemIndex()) != -1)
				{
					iInvenType = 0; // �ڱ� �ǸŻ���
				}
				else if((iItemIndex = g_pStorageInventory->GetPointedItemIndex()) != -1)
				{
					iInvenType = 1; // â��
				}
				else if((iItemIndex = g_pTrade->GetPointedItemIndexMyInven()) != -1)
				{
					iInvenType = 2; // �ŷ�â(��)
				}
				else if((iItemIndex = g_pTrade->GetPointedItemIndexYourInven()) != -1)
				{
					iInvenType = 3; // �ŷ�â(��)
				}
				else if((iItemIndex = g_pMixInventory->GetPointedItemIndex()) != -1)
				{
					iInvenType = 4; // ����
				}
				else if((iItemIndex = g_pPurchaseShopInventory->GetPointedItemIndex()) != -1)
				{
					iInvenType = 5; // ���Ż���
				}
				else if((iItemIndex = g_pNPCShop->GetPointedItemIndex()) != -1)
				{
					iInvenType = 6; // NPC����
				}
				SendRequestPetInfo( PetType, iInvenType, iItemIndex );
            }
            else
            {
                int TextNum = 0;
                int SkipNum = 0;
                int RequireLevel = 0;
                int RequireCharisma = 0;
                //  
                BYTE PetType = 0;
                if ( ip->Type==ITEM_HELPER+4 )
                {
                    PetType = 1;
                }
                CalcPetInfo ( PetType );

                //  �������� ������ ǥ���Ѵ�.
				if ( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_NPCSHOP) )
                {
                    char  Text[100];
                    DWORD Gold = ( giPetManager::ItemValue ( (PET_TYPE)PetType ) / 3 );
					Gold = Gold/100*100;

                    ConvertGold( Gold,Text );
				    sprintf ( TextList[TextNum], GlobalText[63], Text );

                    TextListColor[TextNum] = TEXT_COLOR_WHITE;
                    TextBold[TextNum] = true;
                    TextNum++;
                    sprintf(TextList[TextNum],"\n");TextNum++;SkipNum++;
                }
				else if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_MYSHOP_INVENTORY) 
					|| g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_PURCHASESHOP_INVENTORY))
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
							if(((int)gold < price) && (g_IsPurchaseShop == PSHOPWNDTYPE_PURCHASE))
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

                TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = true;
                if ( ip->Type==ITEM_HELPER+4 )      //  ��ũȣ��.
                {
                    RequireLevel = (218+(g_PetInfo[PetType].m_wLevel*2));
					RequireCharisma = 0;
                    sprintf ( TextList[TextNum], GlobalText[1187] ); TextNum++; SkipNum++;
                }
                else if ( ip->Type==ITEM_HELPER+5 ) //  ��ũ���Ǹ�.
                {
					RequireCharisma = (185+(g_PetInfo[PetType].m_wLevel*15));
					// 1214 "��ũ���Ǹ�"
                    sprintf ( TextList[TextNum], GlobalText[1214] ); TextNum++; SkipNum++;
                }
                
                TextListColor[TextNum] = TEXT_COLOR_WHITE;
                sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
                sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
                
				// 201 "����ġ: %u/%u"
                sprintf ( TextList[TextNum], GlobalText[201], g_PetInfo[PetType].m_dwExp1, g_PetInfo[PetType].m_dwExp2 ); TextNum++; SkipNum++;
                // 368 "����"
                sprintf ( TextList[TextNum], "%s : %d", GlobalText[368], g_PetInfo[PetType].m_wLevel ); TextNum++; SkipNum++;
				
                if ( ip->Type==ITEM_HELPER+5 )
                {
                    // 203 "���ݷ�(��): %d~%d (%d)"
                    sprintf ( TextList[TextNum], GlobalText[203], g_PetInfo[PetType].m_wDamageMin, g_PetInfo[PetType].m_wDamageMax, g_PetInfo[PetType].m_wAttackSuccess ); TextNum++; SkipNum++;
                    // 64 "���ݼӵ�: %d"
                    sprintf ( TextList[TextNum], GlobalText[64], g_PetInfo[PetType].m_wAttackSpeed ); TextNum++; SkipNum++;
                }
                // 70 "����: %d"
                sprintf ( TextList[TextNum], GlobalText[70], g_PetInfo[PetType].m_wLife ); TextNum++; SkipNum++;
                //  �䱸����.
                if ( PetType!=0 && RequireLevel>0 )
                {
                    sprintf ( TextList[TextNum], GlobalText[76], RequireLevel );
                    
                    
                    if ( CharacterAttribute->Level < RequireLevel )
                    {
                        TextListColor[TextNum] = TEXT_COLOR_RED;
                        TextBold[TextNum] = false;
                        TextNum++;
                        sprintf ( TextList[TextNum], GlobalText[74], RequireLevel-CharacterAttribute->Level );
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
                //  �䱸���.
                if ( RequireCharisma>0 )
                {
                    sprintf ( TextList[TextNum], GlobalText[698], RequireCharisma );
                    
                    
                    WORD Charisma;
                    Charisma = CharacterAttribute->Charisma + CharacterAttribute->AddCharisma;
                    
                    if ( Charisma<RequireCharisma )
                    {
                        TextListColor[TextNum] = TEXT_COLOR_RED;
                        TextBold[TextNum] = false;
                        TextNum++;
                        sprintf ( TextList[TextNum], GlobalText[74], RequireCharisma-Charisma );
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
                {
                    //  ��ũ�ε�.
                    sprintf ( TextList[TextNum], "\n" ); TextNum++; SkipNum++;
#ifdef KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
					if ( GetBaseClass(Hero->Class) == CLASS_DARK_LORD )
						TextListColor[TextNum] = TEXT_COLOR_WHITE;
					else
						TextListColor[TextNum] = TEXT_COLOR_DARKRED;
#else // KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
					TextListColor[TextNum] = TEXT_COLOR_DARKRED;
#endif // KJH_FIX_WOPS_K33695_EQUIPABLE_DARKLOAD_PET_ITEM
                    sprintf ( TextList[TextNum], GlobalText[61], GlobalText[24] ); TextNum++; SkipNum++;
                }
				
                //  �ɼ����.
				for ( int i=0; i<ip->SpecialNum; ++i )
				{
					ItemConvert(ip);  //������ - ���� ���۽� ������ ���� ����ϰ� �������� �޾Ƽ� ���� ��Ȯ���� ���� �ٽ� �ѹ� ���
                    GetSpecialOptionText ( ip->Type, TextList[TextNum], ip->Special[i], ip->SpecialValue[i], 0 );
       	            TextListColor[TextNum] = TEXT_COLOR_BLUE;
					TextBold[TextNum] = false;TextNum++; SkipNum++;
                }
				
                //  ��ũȣ������ �ɼ�. ( ȭ�鿡 ǥ�ø� ).
                if ( ip->Type==ITEM_HELPER+4 )
                {
                    //  ������ ���.
                    sprintf ( TextList[TextNum], GlobalText[744], (30+g_PetInfo[PetType].m_wLevel)/2 ); 
                    TextListColor[TextNum] = TEXT_COLOR_BLUE; TextNum++; SkipNum++;
                    //  ���� �Ÿ� ����.
					sprintf ( TextList[TextNum], GlobalText[1188], 2 );     //  ���� ���� �Ÿ� ����.
					TextListColor[TextNum] = TEXT_COLOR_BLUE; TextBold[TextNum] = false;TextNum++;
                }
                
                SIZE TextSize = {0, 0};	
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
				unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), TextList[0], 1, &TextSize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
                int Height = (int)( ((TextNum - SkipNum) * TextSize.cy + SkipNum * TextSize.cy / 2) / g_fScreenRate_y );
                if(sy-Height >= 0)
                    sy -= Height;
                
				bool isrendertooltip = true;
#ifdef NEW_USER_INTERFACE_SHELL
				isrendertooltip = g_pNewUISystem->IsVisible( SEASON3B::INTERFACE_PARTCHARGE_SHOP ) ? false : true;
#endif //NEW_USER_INTERFACE_SHELL
				
				if( isrendertooltip )
				{
					RenderTipTextList(sx,sy,TextNum,0);
				}
            }
            return true;
        }
        return false;
        
	}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM								//## �ҽ����� �����.
	
}
#endif	// PET_SYSTEM
