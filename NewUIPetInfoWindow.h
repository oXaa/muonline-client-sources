// NewUIPetInformation.h: interface for the CNewUIPetInfoWindow class.
//
//
// ��  �� : �� ����â �������̽�
//
// �ۼ��� : Pruarin
//
// ������¥ : 2007.7.11(��)
//
////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWUIPETINFORMATION_H__A1B6EB0C_4F9F_4285_B89A_7BB680BF84D6__INCLUDED_)
#define AFX_NEWUIPETINFORMATION_H__A1B6EB0C_4F9F_4285_B89A_7BB680BF84D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NewUIBase.h"
#include "NewUIButton.h"
#include "NewUIMessageBox.h"
#include "NewUIMyInventory.h"
#include "NewUIInventoryctrl.h"
#include "NewUIGuildInfoWindow.h"
#include "NewUIMainFrameWindow.h"

namespace SEASON3B
{
	// CNewUIPetInfoWindow
	class CNewUIPetInfoWindow : public CNewUIObj  
	{
	//-------------------------------------------------------------------------
	// image List
	public:
		enum IMAGE_LIST
		{
			// �⺻â (Reference)
			IMAGE_PETINFO_BACK = CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,			//. newui_msgbox_back.jpg
			IMAGE_PETINFO_TOP = CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP2,		//. newui_item_back04.tga	(190,64)
			IMAGE_PETINFO_LEFT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,		//. newui_item_back02-l.tga	(21,320)
			IMAGE_PETINFO_RIGHT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,	//. newui_item_back02-r.tga	(21,320)
			IMAGE_PETINFO_BOTTOM = CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,	//. newui_item_back03.tga	(190,45)
			IMAGE_PETINFO_BTN_EXIT = CNewUIMyInventory::IMAGE_INVENTORY_EXIT_BTN,	//. newui_exit_00.tga
			
			// �� ��ư (Reference)
			IMAGE_PETINFO_TAB_BUTTON = CNewUIGuildInfoWindow::IMAGE_GUILDINFO_TAB_BUTTON,	//. newui_guild_tab04.tga (56,44,h22)

			// Skill_Image (Reference)
			IMAGE_PETINFO_SKILL = CNewUISkillList::IMAGE_COMMAND,				//. newui_command.jpg
			IMAGE_PETINFO_SKILLBOX = CNewUISkillList::IMAGE_SKILLBOX,			//. newui_skillbox.jpg (32,38)

			// ���̺� �ۼ�
			IMAGE_PETINFO_TABLE_TOP_LEFT = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_TOP_LEFT,			//. newui_item_table01(L).tga (14,14)
			IMAGE_PETINFO_TABLE_TOP_RIGHT = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_TOP_RIGHT,		//. newui_item_table01(R).tga (14,14)
			IMAGE_PETINFO_TABLE_BOTTOM_LEFT = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_BOTTOM_LEFT,	//. newui_item_table02(L).tga (14,14)
			IMAGE_PETINFO_TABLE_BOTTOM_RIGHT = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_BOTTOM_RIGHT,	//. newui_item_table02(R).tga (14,14)
			IMAGE_PETINFO_TABLE_TOP_PIXEL = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_TOP_PIXEL,		//. newui_item_table03(up).tga (1, 14)
			IMAGE_PETINFO_TABLE_BOTTOM_PIXEL = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_BOTTOM_PIXEL,	//. newui_item_table03(dw).tga (1,14)
			IMAGE_PETINFO_TABLE_LEFT_PIXEL = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_LEFT_PIXEL,		//. newui_item_table03(L).tga (14,1)
			IMAGE_PETINFO_TABLE_RIGHT_PIXEL = CNewUIInventoryCtrl::IMAGE_ITEM_TABLE_RIGHT_PIXEL,	//. newui_item_table03(R).tga (14,1)

			// PetLifeBar (Original)
			IMAGE_PETINFO_LIFEBAR = BITMAP_INTERFACE_NEW_PETINFO_WINDOW_BEGIN,			//. newui_pet_lifebar01.jpg (151,12)
			IMAGE_PETINFO_LIFE,															//. newui_Pet_lifebar02.jpg (1,8)
		};	
		
	// enum
	private:
		enum
		{
			PETINFOWINDOW_WIDTH = 190,
			PETINFOWINDOW_HEIGHT = 429,
		};
		
		enum CUR_OPEN_TAB_BUTTON
		{	
			TAB_TYPE_DARKHORSE = 0,
			TAB_TYPE_DARKSPIRIT
		};
		
		enum EVENT_STATE
		{
			EVENT_NONE = 0,
			EVENT_EXIT_BTN_HOVER,		//. ���� �ϴܿ� �ִ�
			EVENT_EXIT_BTN_HOLDING
		};
		
	private:
		CNewUIManager*				m_pNewUIMng;
		CNewUIRadioGroupButton		m_BtnTab;
		CNewUIButton				m_BtnExit;
		POINT						m_Pos;

		int							m_iNumCurOpenTab;		// ���� �����ִ� �ǹ�ư��ȣ

		EVENT_STATE					m_EventState;			// ��ư �̺�Ʈ ó��

#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
		PET_INFO					m_sPetInfo;				// �����κ��� �޴� ������
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM									//## �ҽ����� �����.
		int							m_aiDamage[2];			// �� ���� ������ 
		float						m_fAddDamagePercent;	// �߰� ������ �ۼ�Ƽ��
#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM										//## �ҽ����� �����.
		bool						m_bEquipedDarkHorse;	// ��ũȣ�� ���� üũ
		bool						m_bEquipedDarkSpirit;	// ��ũ���Ǹ� ���� üũ
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM									//## �ҽ����� �����.

	public:
		CNewUIPetInfoWindow();
		virtual ~CNewUIPetInfoWindow();


		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();

		bool BtnProcess();
		
		float GetLayerDepth();	//. 2.3f
		
#ifndef KJH_FIX_DARKLOAD_PET_SYSTEM													//## �ҽ����� �����.
		bool UpdatePetInfo();
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM												//## �ҽ����� �����.
		void OpenningProcess();
		void ClosingProcess();
		
	private:
		void LoadImages();
		void UnloadImages();
		
		void InitButtons( );
		void RenderGroupBox( int iPosX, int iPosY, int iWidth, int iHeight, int iTitleWidth=60, int iTitleHeight=20 );
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
		void CalcDamage( int iNumTapButton );
		bool RenderDarkHorseInfo( PET_INFO* pPetInfo );
		bool RenderDarkSpiritInfo( PET_INFO* pPetInfo );
#else // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
		bool GetPetInfo( PET_INFO& sPetinfo, int iPetType, int iEquipmentIndex, int iItemType );
		void RequestPetInfo();
		bool RenderDarkHorseInfo();
		bool RenderDarkSpiritInfo();
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM											//## �ҽ����� �����.
		bool RenderToolTip();
	};


}

#endif // !defined(AFX_NEWUIPETINFORMATION_H__A1B6EB0C_4F9F_4285_B89A_7BB680BF84D6__INCLUDED_)
	

