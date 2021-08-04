//*****************************************************************************
// File: Sprite.h
//
// Desc: interface for the CSprite class.
//		 ��������Ʈ Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_SPRITE_H__1696B800_F6E1_4AB2_AA02_F67BBA8EFD2E__INCLUDED_)
#define AFX_SPRITE_H__1696B800_F6E1_4AB2_AA02_F67BBA8EFD2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZzzTexture.h"
#include "UIBaseDef.h"

// ũ�� ������ ����.
#define	SPR_SIZING_DATUMS_LT	0x00	// Left, Top	(2���� : 00)
#define	SPR_SIZING_DATUMS_LB	0x01	// Left, Bottom	(2���� : 01)
#define	SPR_SIZING_DATUMS_RT	0x02	// Right, Top	(2���� : 10)
#define	SPR_SIZING_DATUMS_RB	0x03	// Right, Bottom(2���� : 11)
#define	IS_SIZING_DATUMS_R(v)	(v & 0x02)	// ���� �����ΰ�?
#define	IS_SIZING_DATUMS_B(v)	(v & 0x01)	// �Ʒ� �����ΰ�?

class CSprite  
{
protected:
	float		m_fScrHeight;		// ��ũ�� �ȼ� ����.
	// OpenGL�� Y���� �Ʒ��� ������ ���� �����ϹǷ� �ʿ�.

	BITMAP_t*	m_pTexture;
	int			m_nTexID;			// �ؽ�ó ID.
	float		m_fOrgWidth;		// ������ �ʺ�.
	float		m_fOrgHeight;		// ������ ����.

	SScrCoord	m_aScrCoord[POS_MAX];	// ���ý��� ��ũ�� ��ǥ.
	STexCoord	m_aTexCoord[POS_MAX];	// ���ý��� �ý�ó ��ǥ.
	float		m_fDatumX;			// X ������.(���콺 Ŀ���� Hot spot ����)
	float		m_fDatumY;			// Y ������.

// ��������Ʈ ��.
	BYTE		m_byAlpha;
	BYTE		m_byRed;
	BYTE		m_byGreen;
	BYTE		m_byBlue;

// Animation ����.
	int			m_nMaxFrame;		// �� ������ ����.
	int			m_nNowFrame;		// ���� ������(���) ��ȣ.
	int			m_nStartFrame;		// ���� ������(���) ��ȣ.
	int			m_nEndFrame;		// �� ������(���) ��ȣ.
	STexCoord*	m_aFrameTexCoord;	// �� ������ �ؽ�ó ��ǥ �迭.
	bool		m_bRepeat;			// Animation �ݺ� ����.
	double		m_dDelayTime;		// ������ �� ���� �ð�.(�и���)
	double		m_dDeltaTickSum;	// Update() ȣ�⶧ ���� DeltaTick �հ�.

	float		m_fScaleX;			// X Ȯ��, ��� ����.(���� ��ǥ�� ��ȭ ����)
	float		m_fScaleY;			// Y Ȯ��, ��� ����.(���� ��ǥ�� ��ȭ ����)
	bool		m_bTile;			// Ÿ�ϸ� ����.
	int			m_nSizingDatums;	// ũ�� ������ ����.(SPR_SIZING_DATUMS_LT ��)
	bool		m_bShow;			// �����ִ°�?

//	char	m_szToolTip[SPR_TT_MAX_LEN + 1];	// ������ ������ ����.

public:
	CSprite();
	virtual ~CSprite();

	void Release();
	void Create(int nOrgWidth, int nOrgHeight, int nTexID = -1,
		int nMaxFrame = 0, SFrameCoord* aFrameCoord = NULL, int nDatumX = 0,
		int nDatumY = 0, bool bTile = false,
		int nSizingDatums = SPR_SIZING_DATUMS_LT, float fScaleX = 1.0f,
		float fScaleY = 1.0f);
	void Create(SImgInfo* pImgInfo, int nDatumX = 0, int nDatumY = 0,
		bool bTile = false, int nSizingDatums = SPR_SIZING_DATUMS_LT,
		float fScaleX = 1.0f, float fScaleY = 1.0f);
	void SetPosition(int nXCoord, int nYCoord, CHANGE_PRAM eChangedPram = XY);
	int GetXPos(){ return (int)m_aScrCoord[LT].fX; }
	int GetYPos(){ return int(m_fScrHeight - m_aScrCoord[LT].fY); }
	void SetSize(int nWidth, int nHeight, CHANGE_PRAM eChangedPram = XY);
	int GetWidth(){ return int(m_aScrCoord[RT].fX - m_aScrCoord[LT].fX); }
	int GetHeight(){ return int(m_aScrCoord[LT].fY - m_aScrCoord[LB].fY); }
	int GetTexID(){ return m_nTexID; };
	int GetTexWidth() 
	{ 
		return -1 < m_nTexID ? (int)m_pTexture->Width : 0; 
	}
	int GetTexHeight() 
	{ 
		return -1 < m_nTexID ? (int)m_pTexture->Height : 0; 
	}
	
	float GetScaleX() { return m_fScaleX; }
	float GetScaleY() { return m_fScaleY; }
	void Show(bool bShow = true) { m_bShow = bShow; }
	bool IsShow() { return m_bShow; }
	int GetSizingDatums() { return m_nSizingDatums; }
	BOOL PtInSprite(long lXPos, long lYPos);
	BOOL CursorInObject();
	void SetAlpha(BYTE byAlpha) { m_byAlpha = byAlpha; }
	BYTE GetAlpha() { return m_byAlpha; }
	void SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
	{ m_byRed = byRed;	m_byGreen = byGreen;	m_byBlue = byBlue; }
	void SetAction(int nStartFrame, int nEndFrame, double dDelayTime = 0.0,
		bool bRepeat = true);
	void SetNowFrame(int nFrame);
	void Update(double dDeltaTick = 0.0);
	void Render();
};

#endif // !defined(AFX_SPRITE_H__1696B800_F6E1_4AB2_AA02_F67BBA8EFD2E__INCLUDED_)
