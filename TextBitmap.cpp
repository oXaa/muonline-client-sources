//*****************************************************************************
// File: TextBitmap.cpp
//
// Desc: implementation of the CTextBitmap class.
//
// producer: Ahn Sang-Kyu (2007. 2. 6)
//*****************************************************************************

#include "stdafx.h"
#include "TextBitmap.h"
#include <crtdbg.h>  // _ASSERT() ���.

#ifdef NEW_USER_INTERFACE_FONT

extern DWORD g_dwCharSet[];
// �� ���� �´� ĳ���ͼ����� �����ؾ� ��.
// �ѱ� : HANGUL_CHARSET
// �߱� : GB2312_CHARSET
// �Ϻ� : SHIFTJIS_CHARSET
// �븸 : CHINESEBIG5_CHARSET
#define	TB_CHARSET	(g_dwCharSet[SELECTED_LANGUAGE])

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextBitmap::CTextBitmap() : m_hDC(NULL), m_hBitmap(NULL)
{
}

CTextBitmap::~CTextBitmap()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Instance()
// �Լ� ���� : ��ü�� �� �ϳ��� ����.
//			  �� Ŭ������ �����ϱ� ���� �������̽���
//*****************************************************************************
CTextBitmap& CTextBitmap::Instance()
{
	static CTextBitmap s_TextBitmap;                  
    return s_TextBitmap;
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ��Ʈ�� ���� �� �ʱ�ȭ.
//*****************************************************************************
void CTextBitmap::Create()
{
	Release();	// DC�ڵ��� ������ ����.

	m_hDC = ::CreateCompatibleDC(NULL);	// DC ����.

	// ��Ʈ�� ���� ����ü�� ��� ä���.
	BITMAPINFO bmi;
	::memset(&bmi.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       = TB_WIDTH;
	// Height�� -�� ������ ��Ʈ���� ���� �����Ǿ� ��Ÿ���� ����.
	bmi.bmiHeader.biHeight      = -TB_HEIGHT;
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount    = 16;	// 16bit Į����.

	// ��Ʈ���� �����ϰ� ��Ʈ�� �ڵ�� ��Ʈ�� ������(m_pwBitmap)�� ����.
	m_hBitmap = ::CreateDIBSection(m_hDC, &bmi, DIB_RGB_COLORS,
		(void**)&m_pwBitmap, NULL, 0);

	::SelectObject(m_hDC, m_hBitmap);		// ��Ʈ�� ����.
	// ��Ʈ�� ���� �� �����ص� ��Ʈ�� �����͸� ������ ��.

	::SetBkMode(m_hDC, TRANSPARENT);	// ��� ����.
	::SetTextAlign(m_hDC, TA_TOP);		// Text ���� ����.

	::strcpy(m_szSelFont, "");			// ���õ� ��Ʈ �̸�.
	m_nSelFontHeight = 0;				// ���õ� ��Ʈ ����.(�ȼ� ����)
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : DC, ��Ʈ��, ��Ʈ ���� �� ����.
//*****************************************************************************
void CTextBitmap::Release()
{
	if (m_hDC)
	{
		::DeleteDC(m_hDC);			// DC ����.
		m_hDC = NULL;
	}

	if (m_hBitmap)
	{
		::DeleteObject(m_hBitmap);	// ��Ʈ�� ����.
		m_hBitmap = NULL;
	}

	if (!m_mapFont.empty())
	{
		// ��Ʈ ���� �ʿ� �ִ� ��Ʈ�� ����.
		for (FontMapItor i = m_mapFont.begin(); i != m_mapFont.end(); ++i)
			::DeleteObject(i->second.hFont);

		m_mapFont.clear();			// ��Ʈ ���� �� ����.
	}
}

//*****************************************************************************
// �Լ� �̸� : AddFont()
// �Լ� ���� : ��Ʈ �ʿ� ��Ʈ �߰�. ���ϰ��� ���� �ִ� �ʺ�.(�ȼ� ����)
// �Ű� ���� : lpszFace			: ��Ʈ �̸� ���ڿ�. (�� "����")
//			   nHeight			: ��Ʈ ����.(�ȼ� ����)
//*****************************************************************************
int CTextBitmap::AddFont(LPCTSTR lpszFace, int nHeight)
{
	// ��Ʈ �k�̴� TB_HEIGHT ���Ͽ��� ��.
	_ASSERT(0 < nHeight && TB_HEIGHT >= nHeight);
	_ASSERT(m_hDC);

	// Ű(��Ʈ �̸� + ��Ʈ ����) ����.
	char szMapKey[LF_FACESIZE + 2];
	::sprintf(szMapKey, "%s%d", lpszFace, nHeight);
	// ��Ʈ�� �ʿ� �ִ��� �˻�.
	FontMapItor itor = m_mapFont.find(szMapKey);
	if (itor != m_mapFont.end())	// ������.
		return itor->second.nCharMaxWidth;
	else							// ���ٸ�.
	{
		SFontInfo fi;

	// ��Ʈ ����.
		LOGFONT lf;
		::memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = nHeight;
		lf.lfWeight = FW_MEDIUM;
		lf.lfCharSet = TB_CHARSET;
		::_tcscpy(lf.lfFaceName, _T(lpszFace));

		fi.hFont = ::CreateFontIndirect(&lf);

	// ���� ū ������ �ʺ� ����.(����, �ѱ� �� 2byte ���ڴ� ����)
		// ���� ū ������ �ʺ� ��� ���� ��Ʈ ����.
		::SelectObject(m_hDC, fi.hFont);

		// �ؿ� ��Ʈ ��쿣 TEXTMETRIC ����ü�� tmMaxCharWidth�� ����Ȯ(���ϴ�
		//ũ�⺸�� ŭ)�ϹǷ� �Ʒ��� ���� ��.
		const int nStrLen = 94;
		char szTestChars[nStrLen + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijk\
lmnopqrstuvwxyz`1234567890-=\\[];',./~!@#$%^&*()_+|{}:\"<>?";
		int anDx[nStrLen];	// �� ������ ��ġ�� ���� �� ��.
		SIZE size;			// �ʿ������ �Ʒ� �Լ����� �ݵ�� �־���� ��.
		// szTestChars[]�� �� ���� ��ġ�� ���Ͽ� anDx[]�� �־���.
		::GetTextExtentExPoint(m_hDC, szTestChars, nStrLen, 0, NULL, anDx,
			&size);
		// �ʺ� ���� ū ������ ���̸� ����.
		fi.nCharMaxWidth = anDx[0];
		int nCharTempWidth;
		for (int i = 1; i < nStrLen; ++i)
		{
			nCharTempWidth = anDx[i] - anDx[i - 1];
			if (fi.nCharMaxWidth < nCharTempWidth)
				fi.nCharMaxWidth = nCharTempWidth;
		}

	// �ʿ� ��Ʈ ���� �߰�.
		m_mapFont[szMapKey] = fi;

	// ���õ� ��Ʈ�� ���� ����.
		::strcpy(m_szSelFont, lpszFace);		// ���õ� ��Ʈ �̸�.
		m_nSelFontHeight = nHeight;				// ���õ� ��Ʈ ����.

	// ���� ��.
		return fi.nCharMaxWidth;
	}
}

//*****************************************************************************
// �Լ� �̸� : SelFont()
// �Լ� ���� : ��Ʈ ����.
// �Ű� ���� : lpszFace	: ��Ʈ �̸� ���ڿ�. (�� "����")
//			   nHeight	: ��Ʈ ����.(�ȼ� ����)
//*****************************************************************************
void CTextBitmap::SelFont(LPCTSTR lpszFace, int nHeight)
{
	// ��Ʈ �k�̴� TB_HEIGHT ���Ͽ��� ��.
	_ASSERT(0 < nHeight && TB_HEIGHT >= nHeight);
	_ASSERT(m_hDC);

	// ������ ��Ʈ �̸��� ��Ʈ ���̰� ���� ���õǾ��� �͵�� ���ٸ� return.
	if (0 == ::strcmp(m_szSelFont, lpszFace) && m_nSelFontHeight == nHeight)
		return;

	// Ű(��Ʈ �̸� + ��Ʈ ����)�� �����Ͽ� �ʿ��� �˻�.
	char szMapKey[LF_FACESIZE + 2];
	::sprintf(szMapKey, "%s%d", lpszFace, nHeight);
	FontMapItor itor = m_mapFont.find(szMapKey);
	_ASSERT(itor != m_mapFont.end());	// �ʿ� ������ �ȵ�.

	// DC�� ��Ʈ ����.
	::SelectObject(m_hDC, itor->second.hFont);

	::strcpy(m_szSelFont, lpszFace);	// ���õ� ��Ʈ �̸�.
	m_nSelFontHeight = nHeight;			// ���õ� ��Ʈ ����
}

//*****************************************************************************
// �Լ� �̸� : TextOut()
// �Լ� ���� : ��Ʈ�ʿ� ���ڸ� ��. ���ϰ��� ���ڿ��� �ȼ� �ʺ�.
// �Ű� ���� : lpszText		: �� ���ڿ�.
//			   crTextColor	: Text ��. RGB() ��ũ�� ���.
//			   eStyle		: TS_NORMAL, TS_SHADOW, TS_OUTLINE �� �ϳ�.
//			   crStyleColor	: �׸���(TS_SHADOW) �Ǵ� �ܰ���(TS_OUTLINE) ��.
//							RGB() ��ũ�� ���.
//*****************************************************************************
int CTextBitmap::TextOut(LPCTSTR lpszText, COLORREF crColor, TEXT_STYLE eStyle,
						  COLORREF crStyleColor)
{
	_ASSERT(m_hDC);

	int nStrLen = ::strlen(lpszText);	// ���ڿ� ����.
	SIZE size;

	switch (eStyle)
	{
	case TS_NORMAL :	// �׳� ����.
		// m_pwBitmap�� ���̴� TB_HEIGHT ���Ͽ��� ��.
		_ASSERT(0 < m_nSelFontHeight && TB_HEIGHT >= m_nSelFontHeight);
		// ��Ʈ�ʸ� ����.
		::memset(m_pwBitmap, 0, TB_WIDTH * m_nSelFontHeight * sizeof(WORD));

		// ��Ʈ�ʿ� ���ڸ� ��.
		::SetTextColor(m_hDC, crColor);
		::TextOut(m_hDC, 0, 0, lpszText, nStrLen);

		// ���ڿ��� �ȼ� �ʺ� ��� ����.
		::GetTextExtentPoint(m_hDC, lpszText, nStrLen, &size);
		return size.cx;

	case TS_SHADOW :	// �׸���.
		// m_pwBitmap�� ���̴� TB_HEIGHT ���Ͽ��� ��.
		_ASSERT(0 < m_nSelFontHeight && TB_HEIGHT >= m_nSelFontHeight + 1);
		// ��Ʈ�ʸ� ����. �׸��ڷ� ���� ���̰� 1�ȼ� �þ.
		::memset(m_pwBitmap, 0,
			TB_WIDTH * (m_nSelFontHeight + 1) * sizeof(WORD));

		// ��Ʈ�ʿ� �׸��� ���� ����.
		::SetTextColor(m_hDC, crStyleColor);
		::TextOut(m_hDC, 1, 1, lpszText, nStrLen);

		// ��Ʈ�ʿ� ���ڸ� ��.
		::SetTextColor(m_hDC, crColor);
		::TextOut(m_hDC, 0, 0, lpszText, nStrLen);

		// ���ڿ��� �ȼ� �ʺ� ��� ����.
		::GetTextExtentPoint(m_hDC, lpszText, nStrLen, &size);
		return size.cx + 1;

	case TS_OUTLINE :	// �ܰ���.
		// m_pwBitmap�� ���̴� TB_HEIGHT ���Ͽ��� ��.
		_ASSERT(0 < m_nSelFontHeight && TB_HEIGHT >= m_nSelFontHeight + 2);
		// ��Ʈ�ʸ� ����. �ܰ������� ���� ���̰� 2�ȼ� �þ.
		::memset(m_pwBitmap, 0,
			TB_WIDTH * (m_nSelFontHeight + 2) * sizeof(WORD));

		// ��Ʈ�ʿ� ���ڸ� 4�� �Ἥ �ܰ����� ����.
		::SetTextColor(m_hDC, crStyleColor);
		::TextOut(m_hDC, 0, 1, lpszText, nStrLen);	// ����.
		::TextOut(m_hDC, 1, 0, lpszText, nStrLen);	// ���.
		::TextOut(m_hDC, 1, 2, lpszText, nStrLen);	// �ϴ�.
		::TextOut(m_hDC, 2, 1, lpszText, nStrLen);	// ����.

		// ��Ʈ�ʿ� ���ڸ� ��.
		::SetTextColor(m_hDC, crColor);
		::TextOut(m_hDC, 1, 1, lpszText, nStrLen);

		// ���ڿ��� �ȼ� �ʺ� ��� ����.
		::GetTextExtentPoint(m_hDC, lpszText, nStrLen, &size);
		return size.cx + 2;
	}

	return 0;
}

#endif //NEW_USER_INTERFACE_FONT