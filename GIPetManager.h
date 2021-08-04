//////////////////////////////////////////////////////////////////////////
//  
//  ��  �� : GIPetManager.
//
//  ��  �� : ���� ����.
//
//  ��  ¥ : 2004.07.01.
//
//  �ۼ��� : �� �� ��.
//  
//////////////////////////////////////////////////////////////////////////
#ifndef __CIPET_MANAGER_H__
#define __CIPET_MANAGER_H__

//////////////////////////////////////////////////////////////////////////
//  INCLUDE.
//////////////////////////////////////////////////////////////////////////
#ifdef PET_SYSTEM
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "CSPetSystem.h"


namespace giPetManager
{
    //////////////////////////////////////////////////////////////////////////
    //  EXTERN.
    //////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    //  STRUCTURE.
    //////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    //  VARIABLE
    //////////////////////////////////////////////////////////////////////////

#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	// �����ۿ� ���콺On������ ������
	static PET_INFO	gs_PetInfo;
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM


    //////////////////////////////////////////////////////////////////////////
    //  FUNCTION.
    //////////////////////////////////////////////////////////////////////////	
    void    InitPetManager ( void );
    void    CreatePetDarkSpirit (  CHARACTER*c );
    void    CreatePetDarkSpirit_Now ( CHARACTER* c );

    void    MovePet ( CHARACTER*c );
    void    RenderPet ( CHARACTER* c );
    void    DeletePet ( CHARACTER* c );

	// PetItem ����
    void    InitItemBackup ( void );
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	void SetPetInfo( BYTE InvType, BYTE InvPos, PET_INFO* pPetinfo );				// ������ ����
	PET_INFO* GetPetInfo(ITEM* pItem);												// ������ ��������
	void CalcPetInfo( PET_INFO* pPetInfo );											// ������ ���ΰ�� (����ġ, ��������)
    void SetPetItemConvert( ITEM* ip, PET_INFO* pPetInfo );							// �� ������ ����(�ɼ�) ����
	DWORD GetPetItemValue( PET_INFO* pPetInfo );														// �� ������ ���� ��������
	bool RequestPetInfo( int sx, int sy, ITEM* pItem );								// ������ ������ ��û
	bool RenderPetItemInfo( int sx, int sy, ITEM* pItem, int iInvenType );
#else // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	void	SetPetInfo ( BYTE InvType, BYTE Index, const PET_INFO& Petinfo );
#else // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    void    SetPetInfo ( BYTE PetType, BYTE InvType, BYTE Index, BYTE Level, int exp );
#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	void    CalcPetInfo ( BYTE petType );
	void    ItemConvert ( ITEM* ip );
	DWORD   ItemValue ( PET_TYPE pType );
	bool    RenderPetItemInfo ( int sx, int sy, ITEM* ip, bool Sell );
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.

	// Pet �ൿ
    bool    SelectPetCommand ( void );
    void    MovePetCommand ( CHARACTER* c );
    bool    SendPetCommand ( CHARACTER* c, int Index );
    void    SetPetCommand ( CHARACTER* c, int Key, BYTE Cmd );
    void    SetAttack ( CHARACTER* c, int Key, int attackType );  
    bool    RenderPetCmdInfo ( int sx, int sy, int Type );
#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM												//## �ҽ����� �����.			
	void	GetPetInfo(PET_INFO &PetInfo, short type);
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
}

using namespace giPetManager;

#endif// PET_SYSTEM.

#endif//