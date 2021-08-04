//*****************************************************************************
// File: CreditWin.h
//
// Desc: interface for the CCreditWin class.
//		 ũ���� â Ŭ����.(ȭ�� ��ü ũ����.)
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_CREDITWIN_H__9D392798_811A_46FE_918B_7753E6BA35D0__INCLUDED_)
#define AFX_CREDITWIN_H__9D392798_811A_46FE_918B_7753E6BA35D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"
#include "Button.h"

#define	CRW_SPR_PIC_L			0	// �Ϸ���Ʈ ��.
#define	CRW_SPR_PIC_R			1	// �Ϸ���Ʈ ��.
									//(�ϳ��� �Ϸ���Ʈ�� �¿�� ������ ����.)
#define	CRW_SPR_DECO			2	// ���� �ϴ� ���.
#define	CRW_SPR_LOGO			3	// �߾� �ϴ� �� �ΰ�.
#define CRW_SPR_TXT_HIDE0		4	// 1°�� ���� ������.
#define CRW_SPR_TXT_HIDE1		5	// 2°�� ���� ������.
#define CRW_SPR_TXT_HIDE2		6	// 3°�� ���� ������.
#define	CRW_SPR_MAX				7

#define CRW_ILLUST_MAX			8	// �Ϸ���Ʈ �ִ� ����.

#define	CRW_NAME_MAX			32	// �̸� �Ǵ� �μ� ���ڿ� �޸� ����.
#define	CRW_ITEM_MAX			400	// �̸� �Ǵ� �μ� �׸� �ִ� ����.

#define	CRW_INDEX_DEPARTMENT	0	// �μ�.
#define	CRW_INDEX_TEAM			1	// ��.
#define	CRW_INDEX_NAME			2	// �̸�.
#define	CRW_INDEX_NAME0			2	// �̸�0.
#define	CRW_INDEX_NAME1			3	// �̸�1.
#define	CRW_INDEX_NAME2			4	// �̸�2.
#define	CRW_INDEX_NAME3			5	// �̸�3.
#define	CRW_INDEX_MAX			6

class CCreditWin : public CWin  
{
	// �Ⱥ���, ��Ÿ��, ����, �����.
	enum SHOW_STATE { HIDE, FADEIN, SHOW, FADEOUT };

	struct SCreditItem					// ũ���� �׸�.
	{
		BYTE	byClass;				// �� ��ġ.(1~3°��, 0�̸� ũ���� ����.)
		char	szName[CRW_NAME_MAX];	// �׸�(�̸�, �μ� ��) ���ڿ�.
	};

protected:
	CSprite		m_aSpr[CRW_SPR_MAX];	// ��������Ʈ.
	CButton		m_btnClose;				// �ݱ� ��ư.

// �Ϸ���Ʈ ����.
	SHOW_STATE	m_eIllustState;			// ���� �Ϸ���Ʈ ����.
	double		m_dIllustDeltaTickSum;	// �Ϸ���Ʈ SHOW������ �� �帥 �ð�.
	BYTE		m_byIllust;				// ���� �Ϸ���Ʈ ��ȣ.
	char*		m_apszIllustPath[CRW_ILLUST_MAX][2];// �Ϸ���Ʈ ���.

// �ؽ�Ʈ ����.
	HFONT		m_hFont;				// ��Ʈ�ڵ�.
	SCreditItem	m_aCredit[CRW_ITEM_MAX];// ���Ϸκ��� �о���� ũ���� ����.
	int			m_nNowIndex;			// m_aCredit[]�� �ε���.
	int			m_nNameCount;			// ���� 3��°�ٿ� �����ְ� �ִ� �׸� ����.
	int			m_anTextIndex[CRW_INDEX_MAX];// ���� �� ��ġ���� �����ְ� �ִ� �׸� �ε���.
	SHOW_STATE	m_aeTextState[CRW_INDEX_NAME + 1];//�� ���� ����.
	double		m_dTextDeltaTickSum;	// 3��°�� SHOW������ �� �帥 �ð�.

public:
	CCreditWin();
	virtual ~CCreditWin();

	void Create();
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	void SetPosition();
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void SetPosition(int nXCoord, int nYCoord);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	void Show(bool bShow);
	bool CursorInWin(int nArea);

protected:
	void PreRelease();
	void UpdateWhileActive(double dDeltaTick);
	void RenderControls();

	void CloseWin();
	void Init();
	void LoadIllust();
	void AnimationIllust(double dDeltaTick);
	void LoadText();
	void SetTextIndex();
	void AnimationText(int nClass, double dDeltaTick);
};

#endif // !defined(AFX_CREDITWIN_H__9D392798_811A_46FE_918B_7753E6BA35D0__INCLUDED_)
