
#ifdef NEW_USER_INTERFACE_FONT

//*****************************************************************************
// File: TextBitmap.h
//
// Desc: interface for the CTextBitmap class.
//		 ���ڸ� �� ��Ʈ��, ��Ʈ ���� Ŭ����. Singleton ����.
//
// producer: Ahn Sang-Kyu (2007. 2. 6)
//*****************************************************************************

#if !defined(AFX_TEXTBITMAP_H__B29A08B3_BF8F_4C9D_BA9C_23A24AC4C0A5__INCLUDED_)
#define AFX_TEXTBITMAP_H__B29A08B3_BF8F_4C9D_BA9C_23A24AC4C0A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>

using namespace std;

#define	TB_WIDTH			1024	// ��Ʈ���� �ʺ�.
#define TB_HEIGHT			32		// ��Ʈ���� ����.

enum TEXT_STYLE { TS_NORMAL, TS_SHADOW, TS_OUTLINE };

class CTextBitmap  
{
friend class CText;

	// ��Ʈ ���� ����ü.
	struct SFontInfo
	{
		HFONT	hFont;				// ��Ʈ �ڵ�.
		int		nCharMaxWidth;		// ���� �ִ� �ʺ�.
	};

	typedef map<string, SFontInfo> FontMap;
	typedef FontMap::iterator FontMapItor;

protected:
	HDC		m_hDC;						// DC �ڵ�.
	HBITMAP	m_hBitmap;					// ��Ʈ�� �ڵ�.
	WORD*	m_pwBitmap;					// ��Ʈ���� ������.
	FontMap	m_mapFont;					// ��Ʈ ���� ��.
	char	m_szSelFont[LF_FACESIZE];	// ���õ� ��Ʈ �̸�.
	int		m_nSelFontHeight;			// ���õ� ��Ʈ ����.(�ȼ� ����)
	
protected:
	CTextBitmap();

public:
	virtual ~CTextBitmap();

	static CTextBitmap& Instance();
	void Create();
	void Release();

protected:
// ���� �Լ����� CText Ŭ���������� �����.
	int AddFont(LPCTSTR lpszFace, int nHeight);
	void SelFont(LPCTSTR lpszFace, int nHeight);
	int TextOut(LPCTSTR lpszText, COLORREF crColor, TEXT_STYLE eStyle,
		COLORREF crStyleColor);
	WORD* GetBitmap() const { return m_pwBitmap; }
};

#endif // !defined(AFX_TEXTBITMAP_H__B29A08B3_BF8F_4C9D_BA9C_23A24AC4C0A5__INCLUDED_)

#endif //NEW_USER_INTERFACE_FONT