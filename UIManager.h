//////////////////////////////////////////////////////////////////////////
//  
//  UIManager.h
//  
//  ��  �� : UI ���� ���� ���ִ� Ŭ����
//  
//  ��  ¥ : 2004�� 11�� 09��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIMANAGER_H__2A2AD8F0_E731_4B40_AA6E_E86226026AF9__INCLUDED_)
#define AFX_UIMANAGER_H__2A2AD8F0_E731_4B40_AA6E_E86226026AF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIGuildInfo.h"
#include "UIGuildMaster.h"
#include "UISenatus.h"
#include "UIGateKeeper.h"
#include "UIPopup.h"
#include "UIJewelHarmony.h"
#include "ItemAddOptioninfo.h"
#include "GM_Kanturu_2nd.h"

//////////////////////////////////////////////////////////////////////////
//  EXTERN.
//////////////////////////////////////////////////////////////////////////
extern CUIGateKeeper*		g_pUIGateKeeper;
extern CUIPopup*			g_pUIPopup;
extern JewelHarmonyInfo*    g_pUIJewelHarmonyinfo;
extern ItemAddOptioninfo*   g_pItemAddOptioninfo;
class CUIManager;
extern CUIManager*			g_pUIManager;

enum
{
	INTERFACE_NONE = 0,
	INTERFACE_FRIEND,				
	INTERFACE_MOVEMAP,				
	INTERFACE_PARTY,					
	INTERFACE_QUEST,					
	INTERFACE_GUILDINFO,				
	INTERFACE_TRADE,					
	INTERFACE_STORAGE,				
	INTERFACE_GUILDSTORAGE,			
	INTERFACE_MIXINVENTORY,			
	INTERFACE_COMMAND,				
	INTERFACE_PET,					
	INTERFACE_PERSONALSHOPSALE,		
	INTERFACE_DEVILSQUARE,			
	INTERFACE_SERVERDIVISION,		
	INTERFACE_BLOODCASTLE,			
	INTERFACE_NPCBREEDER,			
	INTERFACE_NPCSHOP,				
	INTERFACE_PERSONALSHOPPURCHASE,	
	INTERFACE_NPCGUILDMASTER,		
	INTERFACE_GUARDSMAN,				
	INTERFACE_SENATUS,				
	INTERFACE_GATEKEEPER,			
	INTERFACE_CATAPULTATTACK,		
	INTERFACE_CATAPULTDEFENSE,		
	INTERFACE_GATESWITCH,					// ���� ���� ����ġ
	INTERFACE_CHARACTER,					// �����Ȱ� -> INTERFACE_QUEST, INTERFACE_PET
	INTERFACE_INVENTORY,					// �����Ȱ� -> INTERFACE_CHARACTER, INTERFACE_TRADE, INTERFACE_STORAGE, INTERFACE_GUILDSTORAGE, INTERFACE_MIXINVENTORY, INTERFACE_GEMINVENTORY ,INTERFACE_PERSONALSHOPSALE, INTERFACE_NPCBREEDER
	INTERFACE_REFINERY,						// �����Ȱ� -> INTERFACE_CHARACTER, INTERFACE_TRADE, INTERFACE_STORAGE, INTERFACE_GUILDSTORAGE, INTERFACE_MIXINVENTORY, INTERFACE_GEMINVENTORY ,INTERFACE_PERSONALSHOPSALE, INTERFACE_NPCBREEDER
	INTERFACE_REFINERYINFO,	
	INTERFACE_KANTURU2ND_ENTERNPC,
	INTERFACE_MAP_ENTRANCE,
	INTERFACE_MAX_COUNT,
};

class CUIManager  
{
public:
	CUIManager();
	virtual ~CUIManager();

protected:
	bool IsCanOpen( DWORD dwInterfaceFlag );		// �� �� �ִ� �������� �Ǵ�
	// ������ �÷��� �� â ��� �ݱ�
	// ���ϰ� : true  : �÷��׿� �ش�Ǵ� ��� â�� ������ (�����ִ� â�� ����)
	//			false : � â�� ������ ���ϴ� ��Ȳ�϶�..
	bool CloseInterface( list<DWORD>& dwInterfaceFlag, DWORD dwExtraData=0 );
public:
	// �ʱ�ȭ
	void Init();
	// ���������� �׸��� (���ϰ��� 640x480 ������ �����������)
	POINT RenderWindowBase( int nHeight, int nOriginY=-1 );
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // #ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	// ���ο��� ó���ϸ� TRUE ����
	bool PressKey( int nKey );
#endif // #ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	// Ű���� �Է����̸� TRUE ���� (ä�õ�)
	bool IsInputEnable();
	// �Է�ó��
	void UpdateInput();
	// ������
	void Render();
	// ��� ������â �ݱ�
	void CloseAll();
	bool IsOpen( DWORD dwInterface );						// ���� �ִ��� �Ǵ� (0�̸� �ƹ��ų� �����ִ��� �Ǵ�)
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	bool Open( DWORD dwInterface);							// ������ üũ�Ͽ� ����.
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	bool Open( DWORD dwInterface, DWORD dwExtraData=0 );	// ������ üũ�Ͽ� ����.
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	bool Close( DWORD dwInterface, DWORD dwExtraData=0 );	// ������ üũ�Ͽ� �ݴ´�.
	void GetInterfaceAll( list<DWORD>& outflag );
	void GetInsertInterface( list<DWORD>& outflag, DWORD insertflag );
	void GetDeleteInterface( list<DWORD>& outflag, DWORD deleteflag );
};


#endif // !defined(AFX_UIMANAGER_H__2A2AD8F0_E731_4B40_AA6E_E86226026AF9__INCLUDED_)
