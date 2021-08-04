// NewUIDuelWatchMainFrameWindow.h: interface for the CNewUIDuelWatchMainFrameWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWUIDUELWATCHMAINFRAMEWINDOW_H__A1E5647D_BE3D_4A3B_825A_464B5D3100C1__INCLUDED_)
#define AFX_NEWUIDUELWATCHMAINFRAMEWINDOW_H__A1E5647D_BE3D_4A3B_825A_464B5D3100C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef YDG_ADD_NEW_DUEL_WATCH_BUFF

#include "NewUIBase.h"
#include "NewUIButton.h"
#include "NewUIMessageBox.h"
#include "NewUI3DRenderMng.h"
#include "NewUIMyInventory.h"

namespace SEASON3B
{
	class CNewUIDuelWatchMainFrameWindow : public CNewUIObj, public INewUI3DRenderObj
	{
	public:
		enum IMAGE_LIST
		{
			IMAGE_DUELWATCH_MAINFRAME_BACK1 = BITMAP_BUFFWATCH_MAINFRAME_BEGIN,
			IMAGE_DUELWATCH_MAINFRAME_BACK2,
			IMAGE_DUELWATCH_MAINFRAME_BACK3,
			IMAGE_DUELWATCH_MAINFRAME_SCORE,
			IMAGE_DUELWATCH_MAINFRAME_HP_GAUGE,
			IMAGE_DUELWATCH_MAINFRAME_SD_GAUGE,
			IMAGE_DUELWATCH_MAINFRAME_HP_GAUGE_FX,
			IMAGE_DUELWATCH_MAINFRAME_SD_GAUGE_FX,
			IMAGE_INVENTORY_EXIT_BTN = CNewUIMyInventory::IMAGE_INVENTORY_EXIT_BTN,
		};
	private:
		CNewUIManager*		m_pNewUIMng;
		CNewUI3DRenderMng*	m_pNewUI3DRenderMng;

		CNewUIButton m_BtnExit;			// �ݱ� ��ư
		
		BOOL m_bHasHPReceived;	// HP �ʱ�����ΰ�
		float m_fPrevHPRate1;
		float m_fPrevHPRate2;
		float m_fPrevSDRate1;
		float m_fPrevSDRate2;
		float m_fLastHPRate1;
		float m_fLastHPRate2;
		float m_fLastSDRate1;
		float m_fLastSDRate2;
		float m_fReceivedHPRate1;
		float m_fReceivedHPRate2;
		float m_fReceivedSDRate1;
		float m_fReceivedSDRate2;

	public:
		CNewUIDuelWatchMainFrameWindow();
		virtual ~CNewUIDuelWatchMainFrameWindow();

		bool Create(CNewUIManager* pNewUIMng, CNewUI3DRenderMng* pNewUI3DRenderMng);
		void Release();
		
		void SetPos(int x, int y);
		
		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Update();
		bool Render();
		void Render3D();

		bool IsVisible() const;

		void OpeningProcess();
		void ClosingProcess();

		float GetLayerDepth();	//. 5.0f

	private:
		void LoadImages();
		void UnloadImages();

		void RenderFrame();
		bool BtnProcess();
	};
}
#endif	// YDG_ADD_NEW_DUEL_WATCH_BUFF

#endif // !defined(AFX_NEWUIDUELWATCHMAINFRAMEWINDOW_H__A1E5647D_BE3D_4A3B_825A_464B5D3100C1__INCLUDED_)
