//*****************************************************************************
// File: UsefulDef.cpp
//
// Desc: ������ ���� ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include <windows.h>
#include "UsefulDef.h"
#include "UIControls.h"

#ifdef ASG_ADD_NEW_DIVIDE_STRING
extern float g_fScreenRate_x;

//*****************************************************************************
// �Լ� �̸� : ReduceStringByPixel()
// �Լ� ���� : ���ڿ�(lpszSrc)�� �ʺ� nPixel���� ũ�� nPixel ��ŭ �߶󳻰� ��
//			  ����ǥ'...'�� ���δ�.
// ��     �� : GetTextExtentPoint()�Լ��� ���� ������ �� �Լ� ȣ�� ���� ���ϴ�
//			  ��Ʈ�� �����ϴ� ���� ����.
// �Ű� ���� : lpszDst		: ���� ���ڿ�.
//			   nDstSize		: alpszDst ���ڿ��� ũ��.
//			   lpszSrc		: ��� ���ڿ�.
//			   nPixel		: ���ϴ� �ȼ� ��.
// ��ȯ ��	 : ������ǥ�� �ٴ´ٸ� true.
//*****************************************************************************
bool ReduceStringByPixel(LPTSTR lpszDst, int nDstSize, LPCTSTR lpszSrc, int nPixel)
{
	// ���� �ؽ�Ʈ�� ���� �ȼ� ũ�⸦ ����.
	SIZE size;
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), lpszSrc, lstrlen(lpszSrc), &size);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), lpszSrc, lstrlen(lpszSrc), &size);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	int nSrcWidth = int(size.cx / g_fScreenRate_x);

	// ���ϴ� �ȼ� ũ��(nPixelPerLine)���� ���ų� ������ �׳� �����ϰ� ����.
	if (nSrcWidth <= nPixel)
	{
		::strncpy(lpszDst, lpszSrc, nDstSize - 1);
		lpszDst[nDstSize - 1] = '\0';
		return false;
	}

	// ũ�� ���ϴ� �ȼ� ũ�� - 6 ��ŭ �߶󳻰� "..."�� ���̰� ����.
	::CutText3(lpszSrc, lpszDst, nPixel - 6, 1, nDstSize);
	::strcat(lpszDst, "...");

	return true;
}

//*****************************************************************************
// �Լ� �̸� : DivideStringByPixel()
// �Լ� ���� : ���ڿ�(lpszSrc)�� �� �ٿ� nPixelPerLine �ȼ� ��ŭ ��������
//			  ������ alpszDst�� ����. ���� ��� �� �� ����.
//			   ���ڿ�(lpszSrc)���� ';'�� ������ ���� �������� �ѱ�.
// ��     �� : CutText3()�Լ� �ȿ��� GetTextExtentPoint()�Լ��� ���� ������ ��
//			  �ϴ� �ȼ��� ������ �ʹٸ� �� �Լ� ȣ�� ���� ���ϴ� ��Ʈ�� ������
//			  �� ���� ����.
// �Ű� ���� : alpszDst		: ������ ������ ���ڿ� �迭�� �ּ�.
//			   nDstRow		: alpszDst �迭�� ��� �Ǵ� ���� �ټ�.
//			   nDstColumn	: alpszDst �迭�� ����.
//			   lpszSrc		: ���� ���ڿ� ������.
//			   nPixelPerLine: ���ٴ� �ȼ� ��.
//			   bSpaceInsert	: ù ���� ù ĭ�� ������ �ִ´ٸ� true.(�⺻�� true)
// ��ȯ ��	 : ���� ���ڿ� �� ��. nDstRow���� ���ų� ���� ���� ��ȯ.
//*****************************************************************************
#if defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
int DivideStringByPixel(LPTSTR alpszDst, int nDstRow, int nDstColumn, LPCTSTR lpszSrc,
						int nPixelPerLine, bool bSpaceInsert, const char szNewlineChar)
#else // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
int DivideStringByPixel(LPTSTR alpszDst, int nDstRow, int nDstColumn, LPCTSTR lpszSrc,
						int nPixelPerLine, bool bSpaceInsert)
#endif // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
{
	if (NULL == alpszDst || 0 >= nDstRow || 0 >= nDstColumn || NULL == lpszSrc || 16 > nPixelPerLine)
		return 0;

	char szWorkSrc[1024];
	::strcpy(szWorkSrc, lpszSrc);

	char szWorkToken[1024];
	int nLine = 0;

#if defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
	char* pszToken = ::strtok(szWorkSrc, &szNewlineChar);
#else // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
	char* pszToken = ::strtok(szWorkSrc, ";");
#endif // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
	while (pszToken != NULL)
	{
		if (bSpaceInsert)
		{
			::sprintf(szWorkToken, " %s", pszToken);
			nLine += ::CutText3(szWorkToken, alpszDst + nLine * nDstColumn, nPixelPerLine,
				nDstRow, nDstColumn);
		}
		else
		{
			nLine += ::CutText3(pszToken, alpszDst + nLine * nDstColumn, nPixelPerLine,
				nDstRow, nDstColumn);
		}
#if defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
		pszToken = ::strtok(NULL, &szNewlineChar);
#else // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
		pszToken = ::strtok(NULL, ";");
#endif // defined KJH_ADD_INGAMESHOP_UI_SYSTEM || defined LJH_MOD_TO_USE_DIVIDESTRINGBYPIXEL_FUNC
	}

	return nLine;
}

//*****************************************************************************
// �Լ� �̸� : DivideString()
// �Լ� ���� : ���ڿ�(lpszSrc)�� �� �ٿ� ���ڼ��� nDstColumn -1 ��ŭ ��������
//			  ������ alpszDst�� ����. ���� ��� �� �� ����.
//			   ���ڿ�(lpszSrc)���� '/'�� ������ ���� �������� �ѱ�.
// �Ű� ���� : alpszDst		: ������ ������ ���ڿ� �迭�� �ּ�.
//			   nDstRow		: alpszDst �迭�� ��� �Ǵ� ���� �ټ�.
//			   nDstColumn	: alpszDst �迭�� ����.
//			   lpszSrc		: ���� ���ڿ� ������.
// ��ȯ ��	 : ���� ���ڿ� �� ��. nDstRow���� ���ų� ���� ���� ��ȯ.
//*****************************************************************************
int DivideString(LPTSTR alpszDst, int nDstRow, int nDstColumn, LPCTSTR lpszSrc)
{
	if (NULL == lpszSrc)
		return 0;

	int nSrcLen = ::strlen(lpszSrc);	// ���� ���ڿ� ��ü ����.
	if (0 == nSrcLen)
		return 0;

	int nSrcPos = 0;			// ���� ���ڿ�(lpszSrc)���� �˻����� Byte ��ġ.
	int nDstStart = 0;			// ������ ���ڿ� ���� ��ġ.
	int nDstLen = 1;			// ������ ���ڿ� ����.
	int nLineCount = 0;			// �ټ�.
	
	while (TRUE)
	{
		if (0x80 & lpszSrc[nSrcPos])	// Ȯ�� �ڵ��ΰ�?
		{
			// Ȯ���ڵ��̸� 2Byte�̹Ƿ� ++.
			++nSrcPos;
			++nDstLen;
		}

		// '/'�����̸� '/'���� �������� ������ ���� �ٷ�.
		if ('/' == lpszSrc[nSrcPos])
		{
			::strncpy(alpszDst + nLineCount * nDstColumn, lpszSrc + nDstStart, nDstLen - 1);
			++nLineCount;
			nDstStart = nSrcPos + 1;
			nDstLen = 0;
		}
		// �� ���� ���� �� Ȯ�� �ڵ尡 �߸��°�?
		else if (nDstLen >= nDstColumn)
		{
			// �߸��� �ʰ� ��ġ ����.
			nSrcPos -= 2;
			nDstLen -= 2;
			::strncpy(alpszDst + nLineCount * nDstColumn, lpszSrc + nDstStart, nDstLen);
			++nLineCount;
			nDstStart = nSrcPos + 1;
			nDstLen = 0;
		}
		// ���� ���ڿ� ���ΰ�?
		else if (nSrcPos == nSrcLen - 1)
		{
			::strncpy(alpszDst + nLineCount * nDstColumn, lpszSrc + nDstStart, nDstLen);
			break;
		}
		// �� ���� ���� �� �ִ°�?
		else if (nDstLen == nDstColumn - 1)
		{
			::strncpy(alpszDst + nLineCount * nDstColumn, lpszSrc + nDstStart, nDstLen);
			++nLineCount;
			nDstStart = nSrcPos + 1;
			nDstLen = 0;
		}

		// ���� �ټ��ΰ�?
		if (nDstRow == nLineCount)
			break;
		
		++nSrcPos;
		++nDstLen;
	}
	
	return nLineCount + 1;
}
#else	// ASG_ADD_NEW_DIVIDE_STRING
//*****************************************************************************
// �Լ� �̸� : DivideString()
// �Լ� ���� : ���ڿ�(lpszSrc)�� �� �ٿ� ���ڼ��� nBytePerLine ��ŭ �������� ��
//			  ���� alpszDst�� ����. ���� ��� �� �� ����.
//			   alpszDst �迭 ������ ���� ������ �۰ų� ���ƾ� ������ ���� ����.
// �Ű� ���� : lpszSrc		: ���� ���ڿ� ������.
//			   nBytePerLine	: �� �ٿ� �� ���ڷ� ���� ���ΰ�.
//			   alpszDst		: ������ ������ ���ڿ� �������� �迭.
//*****************************************************************************
int DivideString(LPCTSTR lpszSrc, int nBytePerLine, LPTSTR* alpszDst)
{
	int nSrcPos = 0;			// ���� ���ڿ�(lpszSrc)���� �˻����� Byte ��ġ.
	int nSrcLen = ::strlen(lpszSrc);	// ���� ���ڿ� ��ü ����.
	int nDstStart = 0;			// ������ ���ڿ� ���� ��ġ.
	int nDstLen = 1;			// ������ ���ڿ� ����.
	int nLineCount = 0;			// �� ��.

	while (TRUE)
	{
		if (0x80 & lpszSrc[nSrcPos])	// Ȯ�� �ڵ��ΰ�?
		{
			// Ȯ���ڵ��̸� 2Byte�̹Ƿ� ++.
			nSrcPos++;
			nDstLen++;
		}

		// �� ���� ���� �� Ȯ�� �ڵ尡 �߸��°�?
		if (nDstLen > nBytePerLine)
		{
			// �߸��� �ʰ� ��ġ ����.
			nSrcPos -= 2;
			nDstLen -= 2;
			::strncpy(alpszDst[nLineCount], lpszSrc + nDstStart, nDstLen);
			nLineCount++;
			nDstStart = nSrcPos + 1;
			nDstLen = 0;
		}
		// ���� ���ڿ� ���ΰ�?
		else if (nSrcPos == nSrcLen - 1)
		{
			::strncpy(alpszDst[nLineCount], lpszSrc + nDstStart, nDstLen);
			break;
		}
		// �� ���� ���� �� �ִ°�?
		else if (nDstLen == nBytePerLine)
		{
			::strncpy(alpszDst[nLineCount], lpszSrc + nDstStart, nDstLen);
			nLineCount++;
			nDstStart = nSrcPos + 1;
			nDstLen = 0;
		}

		nSrcPos++;
		nDstLen++;
	}

	return nLineCount + 1;
}
#endif	// ASG_ADD_NEW_DIVIDE_STRING

// ������ ��(NULL ��)�� Ȯ�� �ڵ��� NULL�� �־��༭ ���� ����.
// ���� �����̸� FALSE ����.
BOOL CheckErrString(LPTSTR lpszTarget)
{
	int i = 0;
	int nLen = ::strlen(lpszTarget);
	while (i < nLen)	// ���ڿ� ���� �ƴϸ� �ݺ�.
	{
		if (0x80 & lpszTarget[i])	// Ȯ�� �ڵ��ΰ�?
		{
			if (i == nLen - 1)		// ������ ���ΰ�?(NULL ��)
			{
				lpszTarget[i] = NULL;
				return FALSE;
			}
			else
				++i;
		}
		++i;
	}

	return TRUE;
}
