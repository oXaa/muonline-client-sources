//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <process.h>
#include "zzzscene.h"


#ifdef NP_GAME_GUARD

#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "wsclientinline.h"

#include "npGameGuard.h"

#ifdef PBG_MOD_GAMEGUARD_HANDLE
#include "NPGameGuardHandle.h"
#endif //PBG_MOD_GAMEGUARD_HANDLE
///////////////////////////////////////
//  Extern.
///////////////////////////////////////
extern  CNPGameLib*  g_pnpGL;     //  nProtect Game Guard Lib.
extern  HWND        g_hWnd;     //  Main Window Handle.

extern  void CreateWhisper(char *ID,char *Text,int Type);



///////////////////////////////////////
//  npGameGuard.
///////////////////////////////////////
namespace npGameGuard
{
///////////////////////////////////////
//  Function.
///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//  Func    : init 
//
//  �Ķ����: HWND hWnd             -   ���� ������ �ڵ�.
//            char* strGameName     -   ���� �̸�.
//
//  ����    : ���� ������ �ڵ� ���� �� nProtect Game Guard�� �ʱ�ȭ.
//////////////////////////////////////////////////////////////////////////
bool    init ( void )
{
	if(g_pnpGL == NULL)
		return false;

	DWORD	dwResult = g_pnpGL->Init();

    if ( dwResult!=NPGAMEMON_SUCCESS )
    {
        showErrorMessage ( NULL, dwResult );

        return false;
    }
#ifdef GAMEGUARD_AUTH25
	SetCallbackToGameMon(NPGameMonCallback);
#endif //GAMEGUARD_AUTH25
    return true;
}


//////////////////////////////////////////////////////////////////////////
//  ���� ������ �ڵ��� ���Ӱ��忡 �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
void    SetHwnd ( HWND hWnd )
{
	if(g_pnpGL != NULL)
		g_pnpGL->SetHwnd( hWnd );
}


//////////////////////////////////////////////////////////////////////////
//  Func    : loginID
//
//  �Ķ����: char* strID           - ����� ���̵�.
//
//  ����    : �α��� �ϴ� ������� ���̵� GameMon�� �뺸�Ѵ�.
//////////////////////////////////////////////////////////////////////////
void    loginID ( char* strID )
{
	if(g_pnpGL == NULL)
		return;
	
    if ( !SendUserIDToGameMon( strID ) )
    {
        //  ���� ����.
        CloseHack ( g_hWnd, true );
    }

#ifdef _DEBUG
    TCHAR msg[128];
    wsprintf ( msg, "ID:%s�� GameMon���� �˸���.", strID );
    MessageBox ( g_hWnd, msg, "�˸�", MB_OK );
#endif
}


//////////////////////////////////////////////////////////////////////////
//  Func    : CheckGameMon
//  
//  ����    : nProtect�� GameMon���� ��� ���¸� �˻��Ͽ� ��� ���� ����
//            ��� ������ ���� 
//////////////////////////////////////////////////////////////////////////
void    CheckGameMon ( void )
{
	if(g_pnpGL == NULL)
	{
#ifdef CSK_FIX_GAMEGUARD_CHECK
		CloseHack ( g_hWnd, true );
#endif // CSK_FIX_GAMEGUARD_CHECK

		return;
	}
	
#ifdef _DEBUG
	g_pChatListBox->AddText("nProtect", "GameMon���� ��� ���� �˻�", SEASON3B::TYPE_SYSTEM_MESSAGE);	
#endif

	if ( g_pnpGL->Check()!=NPGAMEMON_SUCCESS )
    {
        //  GameMon���� ��� ����.
        //MessageBox ( g_hWnd, GlobalText[791], "Error", MB_OK );

        //  ���� ����.
        CloseHack ( g_hWnd, true );
    }
}


//////////////////////////////////////////////////////////////////////////
//  Func    : showErrorMessage
//
//  �Ķ����: HWND  hWnd            - ���� ������ �ڵ�.
//            DWORD dwResult        - ���� �޽��� ��.
//
//  ����    : ������� �ش�Ǵ� ���� �޽����� �����ش�.
//////////////////////////////////////////////////////////////////////////
void    showErrorMessage ( HWND hWnd, DWORD dwResult )
{
    bool    bShow = true;
    TCHAR   msg[256];

    switch ( dwResult )
    {
	case NPGMUP_ERROR_DOWNCFG:	// ������Ʈ ����
	case NPGMUP_ERROR_ABORT:
	case NPGMUP_ERROR_CONNECT:
		wsprintf ( msg, GlobalText[800], dwResult );
		break;
	case NPGAMEMON_ERROR_GAME_EXIST:	//- "������ �ߺ� ����Ǿ��ų� ���Ӱ��尡 �̹� ���� �� �Դϴ�. ���� ���� �� �ٽ� �����غ��ñ� �ٶ��ϴ�."
		wsprintf ( msg, GlobalText[795], dwResult );
		break;
	case NPGAMEMON_ERROR_ILLEGAL_PRG:	//- "�ҹ� ���α׷��� �߰ߵǾ����ϴ�. ���ʿ��� ���α׷��� ������ �� �ٽ� �����غ��ñ� �ٶ��ϴ�."
		wsprintf ( msg, GlobalText[796], dwResult );
		break;
	case NPGAMEMON_ERROR_CRYPTOAPI:	//- "�������� �Ϻ� �ý��� ������ �ջ�Ǿ����ϴ�. ���ͳ� �ͽ��÷η�(IE)�� �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�."
		wsprintf ( msg, GlobalText[797], dwResult );
		break;
	case NPGAMEMON_ERROR_EXECUTE:	//- "���Ӱ��� ���࿡ �����߽��ϴ�. ���Ӱ��� �¾� ������ �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�."
		wsprintf ( msg, GlobalText[798], dwResult );
		break;

    case    NPGAMEMON_ERROR_EXIST :         // GameMon Already Exist
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_CREATE :        // GameGuard Directory Create Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_NPSCAN :        // npscan.dll Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_AUTH_INI :      // .ini Authentication Fail
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_AUTH_NPGMUP :   // npgmup.dll Authentication Fail
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_AUTH_GAMEMON :  // GameMon.exe Authentication Fail
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_AUTH_NEWUP :    // npgmup.dll.new Auth Fail
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_DECRYPT :       // .ini File Decryption Fail
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_CORRUPT_INI :   // Corrupt ini file Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_CORRUPT_INI2 :  // Not match GameName in ini file Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_NFOUND_INI :    // ini File not Found
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_NFOUND_NPGMUP : // npgmup.dll not found
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_NFOUND_NEWUP :  // npgmup.dll.new not found
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_COMM :          // Communication Init Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    /*case    NPGAMEMON_ERROR_EXECUTE :       // GameMon Execute Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;*/

    case    NPGAMEMON_ERROR_NPGMUP :        // npgmup.dll Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_MOVE_INI :      // Move ini Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_MOVE_NEWUP :    // Move npgmup.dll.new Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_GAMEMON :       // GameMon Init Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_SPEEDCHECK :    // SpeedCheck Init Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    case    NPGAMEMON_ERROR_GAMEGUARD :     // GameGuard Init Error
        wsprintf ( msg, GlobalText[792], dwResult );
        break;

    default :
        //bShow = false;
        wsprintf ( msg, GlobalText[792], dwResult );
        break;
    }

    if ( bShow )
    {
        TCHAR   msg2[256];
        wsprintf ( msg2, "GameGuard Error : %lu", dwResult );

        MessageBox ( NULL, msg, msg2, MB_OK );
    }
}

}


//////////////////////////////////////////////////////////////////////////
//  Func    : NPGameMonCallBack
//////////////////////////////////////////////////////////////////////////
#ifdef GAMEGUARD_AUTH25
BOOL    CALLBACK NPGameMonCallback ( DWORD dwMsg, DWORD dwArg )
#else
bool    CALLBACK NPGameMonCallback ( DWORD dwMsg, DWORD dwArg )
#endif //GAMEGUARD_AUTH25
{
    TCHAR msg[128];
	int   x = 640/2; 
    int   y = 50;

    switch ( dwMsg )
    {
	case NPGAMEMON_GAMEHACK_DOUBT:	//"�����̳� ���Ӱ��尡 �����Ǿ����ϴ�.";
		MessageBox ( g_hWnd, GlobalText[799], "Error", MB_OK );

        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return false;

#ifdef GG_SERVER_AUTH
	case NPGAMEMON_CHECK_CSAUTH:
#ifdef _DEBUG
		char str[256];
		wsprintf( str, "NPGAMEMON_CHECK_CSAUTH - ��� ������ %x", dwArg);
		g_pChatListBox->AddText("", str, SEASON3B::TYPE_SYSTEM_MESSAGE);
#endif	// _DEBUG
#ifdef NP_LOG
		g_ErrorReport.Write("NPGameMonCallback() NPGAMEMON_CHECK_CSAUTH: SendAuth( %x)\r\n", dwArg);	
#endif	// NP_LOG
		SendAuth( dwArg);
		return true;
#endif	// GG_SERVER_AUTH

#ifdef NPROTECT_AUTH2
	case NPGAMEMON_CHECK_CSAUTH2:
		GG_AUTH_DATA AuthData;
		memcpy(&AuthData, (const void*)dwArg, sizeof(GG_AUTH_DATA));
#ifdef _DEBUG
		wsprintf( str, "NPGAMEMON_CHECK_CSAUTH2 - Index = %X, Value1=%X, Value2=%X, Value3 = %X", AuthData.dwIndex,
			AuthData.dwValue1, AuthData.dwValue2, AuthData.dwValue3);
		g_pChatListBox->AddText("", str, SEASON3B::TYPE_SYSTEM_MESSAGE);
#endif	// _DEBUG
#ifdef NP_LOG
		g_ErrorReport.Write("NPGameMonCallback() NPGAMEMON_CHECK_CSAUTH2: SendAuth() - Index=%X, Value1=%X, Value2=%X, Value3=%X\r\n",
			AuthData.dwIndex, AuthData.dwValue1, AuthData.dwValue2, AuthData.dwValue3);
#endif	// NP_LOG
		SendAuth( AuthData);
		return true;
#endif // NPROTECT_AUTH2
		
    case NPGAMEMON_COMM_ERROR :
    case NPGAMEMON_COMM_CLOSE :
        wsprintf ( msg, GlobalText[792], dwMsg );
        MessageBox ( g_hWnd, msg, "Error", MB_OK );

        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return false;

    case NPGAMEMON_INIT_ERROR :
        wsprintf ( msg, GlobalText[792], dwArg );
        MessageBox ( g_hWnd, msg, "Error", MB_OK );

#ifdef FOR_WORK
        npGameGuard::showErrorMessage ( g_hWnd, dwArg );
#endif
        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return false;

    case NPGAMEMON_SPEEDHACK :
        MessageBox ( g_hWnd, GlobalText[793], "Error", MB_OK );

#ifdef FOR_WORK
        npGameGuard::showErrorMessage ( g_hWnd, dwArg );
#endif
        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return false;

    case NPGAMEMON_GAMEHACK_KILLED :
        wsprintf ( msg, GlobalText[794], dwMsg );
        MessageBox ( g_hWnd, msg, "Error", MB_OK );

		
#ifdef FOR_WORK
        npGameGuard::showErrorMessage ( g_hWnd, dwArg );
#endif
        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return true;

    case NPGAMEMON_GAMEHACK_DETECT :
#ifdef PBG_MOD_GAMEGUARD_HANDLE
		// �����α׷� �߻��� Ŭ���̾�Ʈ �ٷ� �������� �ʴ´�
		if(!g_NPGameGuardHandle->IsNPHack())
		{
			g_NPGameGuardHandle->SetNPHack(true);
			g_NPGameGuardHandle->SetErrorMsgIndex(dwArg);
		}
#else //PBG_MOD_GAMEGUARD_HANDLE
        wsprintf ( msg, GlobalText[794], dwMsg );
        MessageBox ( g_hWnd, msg, "Error", MB_OK );

#ifdef FOR_WORK
        npGameGuard::showErrorMessage ( g_hWnd, dwArg );
#endif
#endif //PBG_MOD_GAMEGUARD_HANDLE
        //  ���� ����.
        CloseHack ( g_hWnd, true );
        return false;
    }

    return true;
}

#endif