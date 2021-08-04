//*****************************************************************************
// File: OptionWin.h
//
// Desc: interface for the COptionWin class.
//		 �ɼ� â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_OPTIONWIN_H__D197E99D_D0C5_4E07_8095_68F233E7A428__INCLUDED_)
#define AFX_OPTIONWIN_H__D197E99D_D0C5_4E07_8095_68F233E7A428__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinEx.h"
#include "Button.h"
#include "Slider.h"

#define	OW_BTN_AUTO_ATTACK		0	// �ڵ�����.
#define	OW_BTN_WHISPER_ALARM	1	// �Ӹ� �˸���.
#define	OW_BTN_SLIDE_HELP		2	// �����̵� ����.
#define	OW_BTN_CLOSE			3	// �ݱ�.
#define	OW_BTN_MAX				4	// ��ư ����.

#define OW_SLD_EFFECT_VOL		0	// ȿ���� ����.
#define OW_SLD_RENDER_LV		1	// +ȿ�� ����.
#define OW_SLD_MAX				2	// �����̴� ����.

class COptionWin : public CWin  
{
protected:
	CWinEx		m_winBack;				// ���.(��� �̹����θ� ���)
	CButton		m_aBtn[OW_BTN_MAX];		// ��ư��.
	CSlider		m_aSlider[OW_SLD_MAX];	// �����̴� ��Ʈ�ѵ�.

public:
	COptionWin();
	virtual ~COptionWin();

	void Create();
	void SetPosition(int nXCoord, int nYCoord);
	void Show(bool bShow);
	bool CursorInWin(int nArea);
	void UpdateDisplay();

protected:
	void PreRelease();
	void UpdateWhileActive(double dDeltaTick);
	void RenderControls();
};

#endif // !defined(AFX_OPTIONWIN_H__D197E99D_D0C5_4E07_8095_68F233E7A428__INCLUDED_)
