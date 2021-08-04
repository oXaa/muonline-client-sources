// NewUIRegistrationLuckyCoin.h: interface for the CNewUIRegistrationLuckyCoin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWUIREGISTRATIONLUCKYCOIN_H__14342688_43E6_4EA9_BB5B_BBC4B0DAC7C9__INCLUDED_)
#define AFX_NEWUIREGISTRATIONLUCKYCOIN_H__14342688_43E6_4EA9_BB5B_BBC4B0DAC7C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008

#include "NewUIBase.h"
#include "NewUIManager.h"
#include "NewUIMessageBox.h"
#include "NewUIMyInventory.h"
#include "NewUICommonMessageBox.h"
#include "ZzzInventory.h"

namespace SEASON3B
{
	class CNewUIRegistrationLuckyCoin : public CNewUIObj
	{
	public:
		enum IMAGE_LIST
		{
			//UI�̹���
			IMAGE_BACK = CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,
			IMAGE_TOP = CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP2,	
			IMAGE_LEFT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,
			IMAGE_RIGHT = CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,
			IMAGE_BOTTOM = CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,
			//��ư�̹����� ���(�ݱ�,���)
			IMAGE_CLOSE_REGIST = CNewUIMessageBoxMng::IMAGE_MSGBOX_BTN_EMPTY_SMALL,
		};
		
	private:
		enum
		{
			//��üâ�� ũ��.
			LUCKYCOIN_REG_WIDTH = 190,
			LUCKYCOIN_REG_HEIGHT = 429,
		};
		
	public:
		CNewUIRegistrationLuckyCoin();
		virtual ~CNewUIRegistrationLuckyCoin();

		//UI�޴��� ��� �� �ε�
		bool Create(CNewUIManager* pNewUIMng, int x, int y);

		void SetPos(int x, int y);
		const POINT& GetPos() { return m_Pos; }
		
		bool Render();
		bool Update();
		//���콺����
		bool UpdateMouseEvent();
		//Ű����
		bool UpdateKeyEvent();

		//��ư����
		bool BtnProcess();
		void SetBtnInfo();

		float GetLayerDepth()
		{
			return 4.2f;
		}
		
		//��ϰ���
		const int& GetRegistCount() { return m_RegistCount; }

		//��� �����Է�
		void SetRegistCount(int nRegistCount) { m_RegistCount = nRegistCount; }

		//���� ȸ���ϱ�.
		bool GetItemRotation() { return m_ItemAngle; }
		void SetItemRotation(bool _bInput) { m_ItemAngle = _bInput; }

		//��Ϲ�ư unlock������
		void LockLuckyCoinRegBtn();
		void UnLockLuckyCoinRegBtn();

		//����������� ���μ���
		void OpeningProcess();
		void ClosingProcess();

		void Release();
		
	private:
		void LoadImages();
		void UnloadImages();

		//��ü ������
		void RenderFrame();
		//�ؽ�Ʈ ���
		void RenderTexts();
		//��ư�׸���
		void RenderButtons();
		//���۱׸���
		void RenderLuckyCoin();

	private:
		CNewUIManager* m_pNewUIMng;
		POINT m_Pos;
		ITEM* m_CoinItem;
		//�������̽��� �׷��� ������
		bool m_ItemAngle;
		//��ư�� ũ��
		float m_width, m_height;
		//��ϰ���
		int m_RegistCount;
		//�ݱ��ư
		CNewUIButton m_CloseButton;
		//��Ϲ�ư
		CNewUIButton m_RegistButton;
	};
}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

#endif // !defined(AFX_NEWUIREGISTRATIONLUCKYCOIN_H__14342688_43E6_4EA9_BB5B_BBC4B0DAC7C9__INCLUDED_)
