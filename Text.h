
#ifdef NEW_USER_INTERFACE_FONT

//*****************************************************************************
// File: Text.h
//
// Desc: interface for the CText class.
//		 �ؽ�Ʈ Ŭ����.
//
// producer: Ahn Sang-Kyu (2007. 2. 6)
//*****************************************************************************

#if !defined(AFX_TEXT_H__187E89A7_433E_496C_994F_0D3B2BDE8144__INCLUDED_)
#define AFX_TEXT_H__187E89A7_433E_496C_994F_0D3B2BDE8144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIBaseDef.h"
#include "TextBitmap.h"

#define	TEXT_MAX_LEN	170		// Text �ִ� ���� ��.
// "����ü" ���� 12 �������� �ִ� ǥ���� �� �ִ� ���� ��.
// "����ü" ���� 12 �̸��� ���ڸ� �˾ƺ��� �����.

enum TEXT_TYPE { TT_NORMAL, TT_MONEY, TT_PASSWORD, TT_NUMBER };

extern unsigned int WindowHeight;

class CText  
{
protected:
// �ؽ�ó.
	GLuint		m_uiTexID;				// �ؽ�ó ID.
	WORD*		m_pwTexImg;				// �ؽ�ó �̹��� ������.
	int			m_nTexWidth;			// Texture �ʺ�.
	int			m_nTexHeight;			// Texture ����.

// ���ؽ�.
	SScrCoord	m_aScrCoord[POS_MAX];	// ���ؽ��� ��ũ�� ��ǥ.
	STexCoord	m_aTexCoord[POS_MAX];	// ���ؽ��� �ؽ�ó ��ǥ.
	BYTE		m_byRed;				// ���ؽ� �÷�(R).
	BYTE		m_byGreen;				// ���ؽ� �÷�(G).
	BYTE		m_byBlue;				// ���ؽ� �÷�(B).
	BYTE		m_byAlpha;				// ���ؽ� ���İ�.

	int			m_nDatumX;				// ���Ľ� X��ǥ ������.

	char		m_szFont[LF_FACESIZE];	// ��Ʈ �̸�.
	int			m_nFontHeight;			// ��Ʈ ����.(�ȼ� ����)
	int			m_nCharMaxWidth;		// �� ���� �ִ� �ʺ�.(�ȼ� ����)
	COLORREF	m_crTextColor;			// Text ����.
	COLORREF	m_crStyleColor;			// �׸���(TS_SHADOW) �Ǵ� �ܰ���(TS_OUTLINE) ��.
	TEXT_STYLE	m_eStyle;				// TS_NORMAL, TS_SHADOW, TS_OUTLINE �� �ϳ�.
	TEXT_TYPE	m_eType;				// TT_NORMAL, TT_MONEY, TT_PASSWORD �� �ϳ�.
	BYTE		m_byAlign;				// TA_LEFT, TA_RIGHT, TA_CENTER �� �ϳ�.

	char		m_szText[TEXT_MAX_LEN + 1];// Text ����.
	int			m_nTextMaxLen;			// Text ���� ���� ��.
	int			m_nTextWidth;			// Text �ȼ� �ʺ�.

	bool		m_bShow;				// ���� ����.

public:
	CText();
	virtual ~CText();

	void Create(LPCTSTR lpszFont, int nFontHeight, int nTextMaxLen,
		TEXT_STYLE eStyle = TS_SHADOW, TEXT_TYPE eType = TT_NORMAL);
	void Release();
//	void SetSize(int nWidth, int nHeight);
	void SetPosition(int nXCoord, int nYCoord, CHANGE_PRAM eChangedPram = XY);
	int GetXPos(){ return int(m_aScrCoord[LT].fX); }	// ���� ����� �ٲ�� ���ڼ��� ���� �޶���.
	int GetYPos(){ return int(float(WindowHeight) - m_aScrCoord[LT].fY); }
	int GetWidth(){ return int(m_aScrCoord[RT].fX - m_aScrCoord[LT].fX); }
	int GetHeight(){ return int(m_aScrCoord[LT].fY - m_aScrCoord[LB].fY); }
	int GetTextWidth(){ return m_nTextWidth; }
	int GetTextHeight(){ return m_nFontHeight + m_eStyle; }

	void SetText(LPCTSTR lpszText);
	LPCTSTR GetText() const { return m_szText; }
	// Text �� ����. RGB() ��ũ�� ���.
	void SetTextColor(COLORREF crTextColor,
		COLORREF crStyleColor = RGB(30, 30, 30))
	{
		m_crTextColor = crTextColor;
		m_crStyleColor = crStyleColor;
	}
	// pcrStyleColor�� NULL�̸� pcrTextColor���� ����.
	void GetTextColor(COLORREF* pcrTextColor, COLORREF* pcrStyleColor = NULL)
	{
		*pcrTextColor = m_crTextColor;
		if (pcrStyleColor)
			*pcrStyleColor = m_crStyleColor;
	}
	void SetAlign(BYTE byAlign){ m_byAlign = byAlign; }

	void SetAlpha(BYTE byAlpha){ m_byAlpha = byAlpha; }
	BYTE GetAlpha(){ return m_byAlpha; }
	void SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)	// ���ؽ� �� ����.
	{ m_byRed = byRed;	m_byGreen = byGreen;	m_byBlue = byBlue; }

	void Show(bool bShow = true){ m_bShow = bShow; }
	bool IsShow(){ return m_bShow; }

	void Render();
};

#endif // !defined(AFX_TEXT_H__187E89A7_433E_496C_994F_0D3B2BDE8144__INCLUDED_)

#endif //NEW_USER_INTERFACE_FONT