// Nprotect.cpp: implementation of the CNprotect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <process.h>
#include "zzzinfomation.h"
#include "Nprotect.h"
#include "Local.h"

//char TextFindHack[] = "findhacktest.exe";
//char TextMu[]       = "mutest.exe";
char *TextFindHack = lpszFindHackFiles[SELECTED_LANGUAGE];


BOOL GetFileVersion( char *lpszFileName, WORD *pwVersion);
// findhack üũ �Լ�
HINSTANCE m_hNprotectCheckDll;
NPROTECTCHECKCRC *g_pNprotectCheckCRC;


void CloseHack(HWND shWnd,bool Flag);
BOOL CheckFindhackCrc( void);


HINSTANCE m_hInstDll = NULL;
HINSTANCE m_hInstDll2 = NULL;

BOOL LaunchNprotect( void)
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
	int Result = spawnl(P_WAIT,TextFindHack,TextFindHack,NULL);
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
	if(Result==1024)
#else
	if(Result==1024 || Result==1025)
#endif
	{
	}
    else
	{
		//findhack����� �������� ���� ó��
		switch(Result)
		{
		case -1  :MessageBox(NULL,GlobalText[12],"Error",MB_OK);break;
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
		case 1025:MessageBox(NULL,GlobalText[16],"Error",MB_OK);break;
#endif
		case 1026:MessageBox(NULL,GlobalText[5 ],"Error",MB_OK);break;
		case 1027:MessageBox(NULL,GlobalText[6 ],"Error",MB_OK);break;
		case 1028:MessageBox(NULL,GlobalText[7 ],"Error",MB_OK);break;
		case 1029:MessageBox(NULL,GlobalText[8 ],"Error",MB_OK);break;
		case 1030:MessageBox(NULL,GlobalText[9 ],"Error",MB_OK);break;
		case 1031:MessageBox(NULL,GlobalText[15],"Error",MB_OK);break;
		default:
			char Text[256];
			sprintf(Text,GlobalText[10],Result);
			MessageBox(NULL,Text,"Error",MB_OK);
			break;
		}
		return FALSE;
	}

#endif //USE_NPROTECT
#endif
#endif
	return TRUE;
}


//��ŷ ���ܱ� ���̴� �Լ�
void KillProtect() 
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
	char *m_psName = "npmon.exe";
	if (m_hInstDll == NULL) 
	{
		m_hInstDll = LoadLibrary("nppsk.dll");
		if (m_hInstDll == NULL)
		{
			//AfxMessageBox("Can't Load Dll");
			return;
		}
		else 
		{
			//AfxMessageBox("Success Load Dll");
			int (*pFunc)(char*);
			pFunc = (int (*)(char*))GetProcAddress(m_hInstDll, "KillTask");
			if (pFunc == NULL)
			{
				//AfxMessageBox("Can't Load Funcation");
				return;
			}
			if (m_psName != "")
			{
				int temp = pFunc(m_psName);
				if (temp != 0)
				{
					//AfxMessageBox("Success Kill");
				}
				else
				{
					//AfxMessageBox("Error Kill");
				}
			}
		}
	}
	if (m_hInstDll != NULL)
	{
		if (FreeLibrary(m_hInstDll))
		{
			m_hInstDll = NULL;
			//AfxMessageBox("Free Dll");
		}				
		else
		{
			//AfxMessageBox("Can't Free Dll");
		}
	}
#endif //USE_NPROTECT
#endif
#endif
}

//��ŷ ���ܱ� ȭ���� ����Ȱ��� üũ�ϴ� �Լ�
/*bool CheckProtect() 
{
	bool Success = true;
    FILE *fp = fopen(TextFindHack,"rb");
	if(fp != NULL)
	{
		fseek(fp,0,SEEK_END);
		int Size = ftell(fp);
		fseek( fp, -4, SEEK_CUR);
		int Check;
		fread( &Check, sizeof ( int), 1, fp);
		fclose(fp);
		if(Size != Check)
		{
			Success = false;
		}
	}
	else
	{
		Success = false;
	}
	if(!Success)
	{
		MessageBox(NULL,GlobalText[2],"Error",MB_OK);
		return false;
	}
	return true;
}*/

BOOL CheckNpMonVersion( void)
{
#ifdef USE_NPROTECT
	WIN32_FIND_DATA Find;
	HANDLE hFind = FindFirstFile( "npmon.exe", &Find);
	if ( INVALID_HANDLE_VALUE != hFind)
	{
		FindClose( hFind);
		return ( FALSE);
	}

	// npmon ���� ��� ���
	char lpszNpMon[MAX_PATH];
	GetSystemDirectory( lpszNpMon, MAX_PATH);
	strcat( lpszNpMon, "\\npmon.exe");

	// ���� ���
	WORD wVersion[4];
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
	WORD wRightVersion[2][4] = { { 4, 10, 0, 44}, { 4, 10, 0, 44}};
#else
	WORD wRightVersion[2][4] = { { 4, 5, 0, 27}, { 4, 5, 0, 28}};
#endif
	GetFileVersion( lpszNpMon, wVersion);
	if ( 0 != memcmp( wVersion, wRightVersion[0], 4 * sizeof ( WORD))
		&& 0 != memcmp( wVersion, wRightVersion[1], 4 * sizeof ( WORD)))
	{
		return ( FALSE);
	}
#endif //USE_NPROTECT

	return ( TRUE);
}

BOOL CheckNpChkVersion( void)
{
#ifdef USE_NPROTECT
	WIN32_FIND_DATA Find;
	HANDLE hFind = FindFirstFile( "npchk.dll", &Find);
	if ( INVALID_HANDLE_VALUE != hFind)
	{
		FindClose( hFind);
		return ( FALSE);
	}

	// ���� ���
	WORD wVersion[4];
	WORD wRightVersion[2][4] = { { 2003, 3, 17, 1}, { 2003, 3, 17, 1}};
	GetFileVersion( "npchk.dll", wVersion);
	if ( 0 != memcmp( wVersion, wRightVersion[0], 4 * sizeof ( WORD))
		&& 0 != memcmp( wVersion, wRightVersion[1], 4 * sizeof ( WORD)))
	{
		return ( FALSE);
	}
#endif //USE_NPROTECT

	return ( TRUE);
}

bool CheckTotalNprotect( void)
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
	// 1. üũ �Լ� ��´�.
	m_hNprotectCheckDll = LoadLibrary( "npchk.dll");
	if ( !m_hNprotectCheckDll)
	{
		return false;
	}
	g_pNprotectCheckCRC = ( NPROTECTCHECKCRC*)GetProcAddress( m_hNprotectCheckDll, "CheckCRC");
	if ( !g_pNprotectCheckCRC)
	{
		return false;
	}
	// 2. findhack.exe üũ
    /*if(!CheckProtect())	// findhack ������ 4����Ʈ�� üũ
	{
		return false;
	}*/
	// 2. npmon ���� üũ
	if (!CheckNpMonVersion())	// npmon ���� üũ
	{
		return false;
	}
	// 3. findhack.exe crc üũ
	if ( !CheckFindhackCrc())
	{
		return false;
	}
	// 4. npchk.dll ���� üũ
#if SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
	if( !CheckNpChkVersion())
	{
		return false;
	}
#endif //SELECTED_LANGUAGE == LANGUAGE_TAIWANESE

#endif //USE_NPROTECT
#endif
#endif

	return true;
}

BOOL CheckFindhackCrc( void)
{
	return ( g_pNprotectCheckCRC( TextFindHack));
}

void CheckNpmonCrc( HWND hWnd)
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN	// �븸�� Ǯ��
	// npmon ���� ��� ���
	char lpszNpMon[MAX_PATH];
	GetSystemDirectory( lpszNpMon, MAX_PATH);
	strcat( lpszNpMon, "\\npmon.exe");
	if ( !g_pNprotectCheckCRC( lpszNpMon))
	{	// ����
		SetTimer( hWnd, WINDOWMINIMIZED_TIMER, 0, 0);
	}
#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN
#endif // USE_NPROTECT
#endif // NDEBUG
#endif // FOR_HACKING
}

BOOL FindNprotectWindow( void)
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
	HWND shWnd = FindWindow("TfrmNPMON", "WWW.NPROTECT.COM");
	if( !shWnd )
	{
		CloseHack(shWnd,false);
		return ( FALSE);
	}
#endif //USE_NPROTECT
#endif
#endif

	return ( TRUE);
}

void CloseNprotect( void)
{
#ifndef FOR_HACKING
#ifdef NDEBUG
#ifdef USE_NPROTECT
	HWND hWndFindHack = FindWindow( "TfrmNPMON", "WWW.NPROTECT.COM");
	PostMessage( hWndFindHack, WM_USER + 10010, 0, 0);
#endif //USE_NPROTECT
#endif
#endif
}
