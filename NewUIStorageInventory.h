//*****************************************************************************
// File: NewUIStorageInventory.h
//
// Desc: interface for the CNewUIStorageInventory class.
//		 â��â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_NEWUISTORAGEINVENTORY_H__BD790479_EDDE_4981_9B03_A12163A58D5D__INCLUDED_)
#define AFX_NEWUISTORAGEINVENTORY_H__BD790479_EDDE_4981_9B03_A12163A58D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NewUIBase.h"
#include "NewUIInventoryCtrl.h"
#include "NewUIMessageBox.h"
#include "NewUIMyInventory.h"
#include "NewUIButton.h"

namespace SEASON3B
{
	class CNewUIStorageInventory : public CNewUIObj
	{
	public:
		enum IMAGE_LIST
		{
			IMAGE_STORAGE_BACK = CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,	// Reference
			IMAGE_STORAGE_TOP = CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP,
			IMAGE_STORAGE_LEFT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,
			IMAGE_STORAGE_RIGHT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,
			IMAGE_STORAGE_BOTTOM = CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,

			IMAGE_STORAGE_BTN_INSERT_ZEN = BITMAP_INTERFACE_NEW_STORAGE_BEGIN,
			IMAGE_STORAGE_BTN_TAKE_ZEN = BITMAP_INTERFACE_NEW_STORAGE_BEGIN + 1,
			IMAGE_STORAGE_BTN_UNLOCK = BITMAP_INTERFACE_NEW_STORAGE_BEGIN + 2,
			IMAGE_STORAGE_BTN_LOCK = BITMAP_INTERFACE_NEW_STORAGE_BEGIN + 3,

			IMAGE_STORAGE_MONEY = BITMAP_INTERFACE_NEW_STORAGE_BEGIN + 4,
		};
		
	private:
		enum
		{
			STORAGE_WIDTH = 190,
			STORAGE_HEIGHT = 429,
		};

		enum STORAGE_BUTTON
		{
			BTN_INSERT_ZEN = 0,		// �Ա�.
			BTN_TAKE_ZEN,			// ���.
			BTN_LOCK,				// ���.
			MAX_BTN
		};
		
		CNewUIManager*			m_pNewUIMng;			// UI �Ŵ���.
		POINT					m_Pos;					// â�� ��ġ.
		CNewUIButton			m_abtn[MAX_BTN];		// ��ư.
		CNewUIInventoryCtrl*	m_pNewInventoryCtrl;	// �κ��丮 ��Ʈ��.

		bool					m_bLock;				// true�� â�� ����ִ� ����.
		bool					m_bCorrectPassword;		// true�� �н����尡 �´� ����.

		bool					m_bItemAutoMove;		// ���콺 ���ư���� �������� â�� �κ��丮�� �̵��� true.
		int						m_nBackupMouseX;		// ������ �ڵ� �̵� �� ���콺 X ��ǥ ���.
		int						m_nBackupMouseY;		// ������ �ڵ� �̵� �� ���콺 Y ��ǥ ���.

	// ������� �� ������ ��й�ȣ�� ���� �����ؾ� �ǹǷ� ��Ȳ�� ����
	//m_bTakeZen�� �� ��Ȳ�� ���� �� ��ݾ� �Ǵ� �������� �ű� �κ��丮 ��ġ ���.
		bool					m_bTakeZen;				// true�� ���, false�� ������.
		int						m_nBackupTakeZen;		// ��ݵ� ��.
		int						m_nBackupInvenIndex;	// �ű� �κ��丮 ��ġ ���.
		
	public:
		CNewUIStorageInventory();
		virtual ~CNewUIStorageInventory();
		
		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();
		
		float GetLayerDepth();	//. 2.2f
		
		CNewUIInventoryCtrl* GetInventoryCtrl() const;

		bool ProcessClosing();
		bool InsertItem(int iIndex, BYTE* pbyItemPacket);
		int FindEmptySlot(ITEM* pItemObj);

		bool IsStorageLocked(){ return m_bLock; }				// â�� ��� �ִ°�?
		bool IsCorrectPassword(){ return m_bCorrectPassword; }	// �н����尡 ����� �����ΰ�?
		bool IsItemAutoMove(){ return m_bItemAutoMove; }		// ������ �ڵ� �̵��ΰ�?

		void SetBackupTakeZen(int nZen);

		void ProcessMyInvenItemAutoMove();

		void SendRequestItemToMyInven(ITEM* pItemObj, int nStorageIndex, int nInvenIndex);

		void ProcessToReceiveStorageStatus(BYTE byStatus);
		void ProcessToReceiveStorageItems(int nIndex, BYTE* pbyItemPacket);
		void ProcessStorageItemAutoMoveSuccess();
		void ProcessStorageItemAutoMoveFailure();
		
		int GetPointedItemIndex();

		void SetItemAutoMove(bool bItemAutoMove);
		
	private:
		void LoadImages();
		void UnloadImages();

		void RenderBackImage();
		void RenderText();

		void ChangeLockBtnImage();
		void DeleteAllItems();

		void LockStorage(bool bLock);
		// �ùٸ� �н������̸� bCorrectPassword�� true.
		void SetCorrectPassword(bool bCorrectPassword)
		{ m_bCorrectPassword = bCorrectPassword; }

		void InitBackupItemInfo();
		int GetBackupTakeZen(){ return m_nBackupTakeZen; }			// ����� ���� ����.
		void SetBackupInvenIndex(int nInvenIndex);
		int GetBackupInvenIndex(){ return m_nBackupInvenIndex; }	// ����� �κ��丮 �ε����� ����.

		void ProcessInventoryCtrl();
		bool ProcessBtns();
		void ProcessStorageItemAutoMove();

		void SendRequestItemToStorage(ITEM* pItemObj,
			int nInvenIndex, int nStorageIndex);
	};
}

#endif // !defined(AFX_NEWUISTORAGEINVENTORY_H__BD790479_EDDE_4981_9B03_A12163A58D5D__INCLUDED_)
