// MultiLanguage.h: interface for the CMultiLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILANGUAGE_H__01D5F840_67B5_4472_B89F_9C3EAF89107A__INCLUDED_)
#define AFX_MULTILANGUAGE_H__01D5F840_67B5_4472_B89F_9C3EAF89107A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE

class CMultiLanguage
{

private:
	static CMultiLanguage *ms_Singleton;

	BYTE byLanguage;				// ������ ����ڰ� ������ ��� ������(0:����, 1:����������, 2:�����ξ�)
	int iCodePage;					// CodePage
	int iNumByteForOneCharUTF8;		// �׳����� �� UTF-8�� ǥ���ϱ� ���� �ʿ��� byte ��

	CMultiLanguage()	{ ms_Singleton = this; };				

public:
	CMultiLanguage(string strSelectedML);
	~CMultiLanguage()	{ ms_Singleton = 0; };

	BYTE GetLanguage();				// Getters
	int GetCodePage();
	int GetNumByteForOneCharUTF8();

	BOOL IsCharUTF8(const char* pszText);
	int	 ConvertCharToWideStr(wstring& wstrDest, LPCSTR lpString);
	int  ConvertWideCharToStr(string& strDest, LPCWSTR lpwString, int iConversionType = CP_UTF8);
	void ConvertANSIToUTF8OrViceVersa(string& strDest, LPCSTR lpString);
	int	 GetClosestBlankFromCenter(const wstring wstrTarget); 
	
	WPARAM ConvertFulltoHalfWidthChar(DWORD wParam);
	// wrapper functions 
	// WIN32 APIs
	// MSDN������ GetTextExtentPoint���� �� ��Ȯ�� ����� �����ϴ� GetTextExtentPoint32 ����� ������ �����Ѵ�.
	BOOL _GetTextExtentPoint32(HDC hdc, LPCWSTR lpString, int cbString, LPSIZE lpSize);
	BOOL _GetTextExtentPoint32(HDC hdc, LPCSTR lpString, int cbString, LPSIZE lpSize);

	BOOL _TextOut(HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cbString);
	BOOL _TextOut(HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cbString);
	
	static CMultiLanguage* GetSingletonPtr() { return ms_Singleton; };
};
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#endif // !defined(AFX_MULTILANGUAGE_H__01D5F840_67B5_4472_B89F_9C3EAF89107A__INCLUDED_)
