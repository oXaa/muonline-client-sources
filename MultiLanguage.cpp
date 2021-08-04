// MultiLanguage.cpp: implementation of the CMultiLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MultiLanguage.h"

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
//////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////
CMultiLanguage* CMultiLanguage::ms_Singleton = NULL;

CMultiLanguage::CMultiLanguage(string strSelectedML)
{
	ms_Singleton = this;

	// �������� ������(���� ����)
	if (_stricmp(strSelectedML.c_str(), "ENG") == 0)
	{
		byLanguage = 0;
		iCodePage = 1252;
		iNumByteForOneCharUTF8 = 2;
	}
	else if(_stricmp(strSelectedML.c_str(), "POR") == 0)
	{	
		byLanguage = 1;
		iCodePage = 1252;
		iNumByteForOneCharUTF8 = 2;
	}
	else if(_stricmp(strSelectedML.c_str(), "SPN") == 0)
	{	
		byLanguage = 2;
		iCodePage = 1252;
		iNumByteForOneCharUTF8 = 2;
	}
	// �ٱ������� ��� �߰� �� �Ʒ��� ���� �߰�
/*
	else if(_stricmp(strSelectedML.c_str(), "KOR") == 0)
	{
		byLanguage = 3;
		iCodePage = 949;
		iNumByteForOneCharUTF8 = 3;
	}
*/
	// Default: ����
	else
	{
		byLanguage = 0;
		iCodePage = 1252;
		iNumByteForOneCharUTF8 = 2;
	}
}

BYTE CMultiLanguage::GetLanguage()
{
	return byLanguage;
}

int CMultiLanguage::GetCodePage()
{
	return iCodePage;
}

int CMultiLanguage::GetNumByteForOneCharUTF8()
{
	return iNumByteForOneCharUTF8;
}

// UTF-8�� ǥ�� ����� �̿� ���� ���� char�� UTF-8���� �ƴ��� ����
// ��ȯ��: TRUE(UTF-8), FALSE(ANSI)
BOOL CMultiLanguage::IsCharUTF8(const char* pszText)
{
    if (pszText == NULL || strlen(pszText) <= 0)
        return TRUE;
    
    const char* pbyCurr = pszText;
	BOOL        bUTF8   = TRUE;
    
	// UTF-8�� ǥ�� ����� �̿� ���� ���� char�� UTF-8���� �ƴ��� ����
    // (����)http://en.wikipedia.org/wiki/UTF-8
    while ( (*pbyCurr != 0x00) && bUTF8)
    {
        // U+0000 ~ U+007F (0 ~ 127)
        if ((*pbyCurr & 0x80) == 0x00)
        {
            pbyCurr++;
        }
        // U+0080 ~ U+07FF (128 ~ 2,047)
        else if (((*pbyCurr & 0xE0) == 0xC0) && ((*(pbyCurr+1) & 0xC0) == 0x80))
        {
            pbyCurr += 2;
        }
        // U+0800 ~ U+FFFF (2,048 ~ 65,535)
        else if (((*pbyCurr & 0xF0) == 0xE0) && ((*(pbyCurr+1) & 0xC0) == 0x80) && ((*(pbyCurr+2) & 0xC0) == 0x80))
        {
            pbyCurr += 3;
        }
        // U+10000 ~ U+10FFFF (65,536 ~ 1,114,111)
        else if (((*pbyCurr & 0xF8) == 0xF0) && 
            ((*(pbyCurr+1) & 0xC0) == 0x80) && ((*(pbyCurr+2) & 0xC0) == 0x80) && ((*(pbyCurr+3) & 0xC0) == 0x80))
        {
            pbyCurr += 4;
        }
        // not UTF-8
        else
        {
            bUTF8 = FALSE;
        }
    }
    return bUTF8;
}

// ����: �Ϲ� const char*�� wstring���� ��ȯ(lpString�� ������ ���ڷ� null�� ������ �־�� ��)
// ����: wstrDest - ��ȯ �� wstring�� ����� ����
//       lpString - ���� 
// ��ȯ ��: wstring�� length
int CMultiLanguage::ConvertCharToWideStr(wstring& wstrDest, LPCSTR lpString)
{
    wstrDest = L"";

    if (lpString == NULL || strlen(lpString) <= 0)
        return 0;

    int nLenOfWideCharStr;
	int iConversionType;
	if (strcmp(lpString, "��Ƽ �α� ����") == 0)
		iConversionType = (IsCharUTF8(lpString)) ? CP_UTF8 : 949;
	else 
		iConversionType = (IsCharUTF8(lpString)) ? CP_UTF8 : iCodePage;

    // calculate the number of characters needed to hold the wide-character version of the string.
    nLenOfWideCharStr = MultiByteToWideChar(iConversionType, 0, lpString, -1, NULL, 0);
    // memory allocation
    wchar_t* pwszStr = new wchar_t[nLenOfWideCharStr];
    
    // convert the multi-byte string to a wide-character string.
    MultiByteToWideChar(iConversionType, 0, lpString, -1, pwszStr, nLenOfWideCharStr);
    
    //assign
    wstrDest += pwszStr;
    
    // release the allocated memory.
    delete[] pwszStr;
    
    return nLenOfWideCharStr-1;     
}

// ����: �Ϲ� const wchar_t*�� string���� ��ȯ(lpwString�� ������ ���ڷ� null�� ������ �־�� ��)
// ����: pszDest - ��ȯ �� string�� ����� ����
//       lpwString - ���� 
// ��ȯ ��: string�� length
int CMultiLanguage::ConvertWideCharToStr(string& strDest, LPCWSTR lpwString, int iConversionType)
{
    strDest = "";

    if (lpwString == NULL || wcslen(lpwString) <= 0)
        return 0;

    int nLenOfWideCharStr;
    
    // calculate the number of characters needed to hold the wide-character version of the string.
    nLenOfWideCharStr = WideCharToMultiByte(iConversionType, 0, lpwString, -1, NULL, 0, 0, 0);
    // memory allocation
    char* pszStr = new char[nLenOfWideCharStr];
    
    // convert the multi-byte string to a wide-character string.
    WideCharToMultiByte(iConversionType, 0, lpwString, -1, pszStr, nLenOfWideCharStr, 0, 0);

    //assign
    strDest += pszStr;
    
    // release the allocated memory.
    delete[] pszStr;

    return nLenOfWideCharStr-1;
}
// ����: lpString�� ANSI�� ��� UTF-8�� ��ȯ�� strDest�� ����
//       lpString�� UTF-8�� ��� ANSI�� ��ȯ�� strDest�� ����
void CMultiLanguage::ConvertANSIToUTF8OrViceVersa(string& strDest, LPCSTR lpString)
{
	wstring wstrUTF16 = L"";
	int iDestType = (IsCharUTF8(lpString)) ? CP_ACP : CP_UTF8;

	ConvertCharToWideStr(wstrUTF16, lpString);
	ConvertWideCharToStr(strDest, wstrUTF16.c_str(), iDestType);
}	

// ����: wstrTarget�� ������ �ִ� ��ĭ�� �߾ӿ��� ���� ����� ��ĭ�� �ε����� ����
int	CMultiLanguage::GetClosestBlankFromCenter(const wstring wstrTarget)
{
	int iLength = wstrTarget.length();
	
	// ���� ����� space ã��
	// �ؽ�Ʈ�� ���� �ڸ���.
	wstring wstrText1 = wstrTarget.substr(iLength/2, wstring::npos);
	wstring wstrText2 = wstrTarget.substr(0, iLength/2);
	
	// ���� �ؽ�Ʈ���� ���� ���� ��ĭ�� ���� �ؽ�Ʈ���� ���� ���� ��ĭ�� ã�´�.
	int iPosLastBlankFromFirstHalf = wstrText2.find_last_of(L" ");
	int iPosFirstBlankFromSecondHalf = wstrText1.find_first_of(L" ", 1);
	int iClosestBlankFromCenter = 0;
	
	// ���Ⱑ ���� �̷���� �ؽ�Ʈ�� �׳� �������� �ڸ���.
	if (iPosLastBlankFromFirstHalf == wstring::npos && iPosFirstBlankFromSecondHalf == wstring::npos)
	{
		iClosestBlankFromCenter = iLength/2;
	}
	// �� �� �ϳ��� �ؽ�Ʈ�� ���⸦ ������ ���� ��� �� �ؽ�Ʈ�� ��ĭ�� �������� ������. 
	else if (iPosLastBlankFromFirstHalf == wstring::npos)
	{
		iClosestBlankFromCenter = iPosFirstBlankFromSecondHalf+iLength/2;
	}
	else if (iPosFirstBlankFromSecondHalf == wstring::npos)
	{
		iClosestBlankFromCenter = iPosLastBlankFromFirstHalf;
	}
	// �Ѵ� ��ĭ�� ������ ���� ��� �߰����� �� ����� ���� ��ĭ�� �������� ������.
	// �Ÿ��� ���� ��� ������ �ؽ�Ʈ�� ��ĭ�� �� �켱���� ������.
	else if (iPosFirstBlankFromSecondHalf <= iLength/2-iPosLastBlankFromFirstHalf)
	{
		iClosestBlankFromCenter = iPosFirstBlankFromSecondHalf+iLength/2;
	}
	else
	{
		iClosestBlankFromCenter = iPosLastBlankFromFirstHalf;
	}
	
	return iClosestBlankFromCenter;
}

// wchar_t Ÿ��(UTF-16)
BOOL CMultiLanguage::_GetTextExtentPoint32(HDC hdc, LPCWSTR lpString, int cbString, LPSIZE lpSize)
{
	return GetTextExtentPoint32W(hdc, lpString, cbString, lpSize); 
}

// lpString�� Encoding�� ���� ANSI�� UNICODE�� GetTextExtentPoint32 �Լ��� ȣ���Ѵ�. 
BOOL CMultiLanguage::_GetTextExtentPoint32(HDC hdc, LPCSTR lpString, int cbString, LPSIZE lpSize)
{
	wstring wstrText = L"";
	ConvertCharToWideStr(wstrText, lpString);
	
	return GetTextExtentPoint32W(hdc, wstrText.c_str(), wstrText.length(), lpSize);
}

// GetTextExtentPoint32�� ���������� ������ ��.
BOOL CMultiLanguage::_TextOut(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString)
{
	return TextOutW(hdc, nXStart, nYStart, lpString, cbString); 
}

BOOL CMultiLanguage::_TextOut(HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cbString)
{
	wstring wstrText = L"";
	ConvertCharToWideStr(wstrText, lpString);
	
	return TextOutW(hdc, nXStart, nYStart, wstrText.c_str(), wstrText.length()); 
}
	
// �������� �� �⺻ ���ڵ��� �ݰ����� ��ȯ
WPARAM CMultiLanguage::ConvertFulltoHalfWidthChar(DWORD wParam)
{
	wchar_t Char = (wchar_t)(wParam);

	// �⺻ ��ȣ �� ����, ��ҹ��� �⺻ ���ĺ�
	if (Char >= 0xFF01 && Char <= 0xFF5A) 
		wParam -= 0xFEE0;
	// ���� ����
	else if (Char == 0x3000)
		wParam = 0x0020;

	return wParam;
}

#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE