//////////////////////////////////////////////////////////////////////////
//  
//  CSMapServer.cpp
//  
//  내  용 : 분산 서버를 위한 맵서버 이동 처리.
//  
//  날  짜 : 2004/11/11
//  
//  작성자 : 조규하.
//  
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//  Include.
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "wsctlc.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzAI.h"
#include "ZzzTexture.h"
#include "ZzzOpenglUtil.h"
#include "zzzOpenData.h"
#include "zzzinfomation.h"
#include "wsclientinline.h"
#include "wsctlc.h"
#include "CSMapServer.h"


//////////////////////////////////////////////////////////////////////////
//  EXTERN.
//////////////////////////////////////////////////////////////////////////
extern int  LogIn;
extern char LogInID[MAX_ID_SIZE+1];
extern int HeroKey;


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
static  CSMServer csMapServer;


//////////////////////////////////////////////////////////////////////////
//  FUNSTION
//////////////////////////////////////////////////////////////////////////
CSMServer::CSMServer ()
{
    Init ();
}


//////////////////////////////////////////////////////////////////////////
//  초기화를 한다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::Init ( void )
{
    m_bFillServerInfo = false;
    memset ( &m_vServerInfo, 0, sizeof( MServerInfo ) );
}


//////////////////////////////////////////////////////////////////////////
//  주인공의 아이디를 저장한다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::SetHeroID ( char* ID )
{
    m_strHeroID = ID;
}


//////////////////////////////////////////////////////////////////////////
//  서버 정보를 설정한다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::SetServerInfo ( MServerInfo sInfo )
{
    memcpy ( &m_vServerInfo, &sInfo, sizeof( MServerInfo) );

    m_bFillServerInfo = true;
}


//////////////////////////////////////////////////////////////////////////
//  맵서버 정보를 알려준다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::GetServerInfo ( MServerInfo& sInfo )
{
    if ( m_bFillServerInfo )
    {
        memcpy ( &sInfo, &m_vServerInfo, sizeof( MServerInfo ) );
    }
    else
    {
        memset ( &sInfo, 0, sizeof( MServerInfo ) );
    }
}


//////////////////////////////////////////////////////////////////////////
//  맵서버 아이피를 알려준다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::GetServerAddress ( char* szAddress )
{
    if ( m_bFillServerInfo )
    {
        memcpy ( szAddress, m_vServerInfo.m_szMapSvrIpAddress, sizeof( char )*16 );
    }
    else
    {
        memset ( szAddress, 0, sizeof( char )*16 );
    }
}


//////////////////////////////////////////////////////////////////////////
//  새로운 맵서버로 연결한다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::ConnectChangeMapServer ( MServerInfo sInfo )
{
    SetServerInfo ( sInfo );

    //  한번 서버에 접속후 다시 접속을 할 때만 적용된다.
    if ( m_bFillServerInfo && LogIn!=0 )
    {
        //  게임내에서 설정한 데이터 저장.
		DeleteSocket ();
        SaveOptions();
		SaveMacro("Data\\Macro.txt");

		::Sleep ( 20 );

        if ( CreateSocket( m_vServerInfo.m_szMapSvrIpAddress, m_vServerInfo.m_wMapSvrPort ) )
        {
            //  게임서버에 연결중인지 알 수 있게 한다.
            g_bGameServerConnected = TRUE;
#ifdef USE_SELFCHECKCODE
            g_byNextFuncCrcCheck = 1;
#endif
        }
    }
}


//////////////////////////////////////////////////////////////////////////
//  변경된 맵 서버의 정보를 서버와의 확인을 위해 보내준다.
//////////////////////////////////////////////////////////////////////////
void    CSMServer::SendChangeMapServer ( void )
{
    if ( m_bFillServerInfo==false || LogIn==0 ) return;

    char  CharID[MAX_ID_SIZE+1];

    strcpy ( CharID, m_strHeroID.c_str() );
//	memcpy ( CharID, m_strHeroID.c_str(), MAX_ID_SIZE );
	CharID[MAX_ID_SIZE] = NULL;

    //  이동 전에 모든 캐릭터를 제거하고 맵서버를 이동한다.
    ClearCharacters ( -1 );
    InitGame ();
    SendChangeMServer(LogInID,CharID,m_vServerInfo.m_iJoinAuthCode1,m_vServerInfo.m_iJoinAuthCode2,m_vServerInfo.m_iJoinAuthCode3,m_vServerInfo.m_iJoinAuthCode4);
}
