#ifndef __ZZZSCENE_H__
#define __ZZZSCENE_H__

#include "zzzinfomation.h"

#ifndef KJH_ADD_SERVER_LIST_SYSTEM		// #ifndef
extern int ServerSelectHi;
extern SERVER_LIST_t ServerList[MAX_SERVER_HI];
extern WORD ServerNumber;
#endif // KJH_ADD_SERVER_LIST_SYSTEM

extern int MenuStateCurrent;
extern int MenuStateNext;
extern int  SceneFlag;
#ifndef CSK_FIX_FENRIR_RUN		// ������ �� ������ �ϴ� �ҽ�	
extern BOOL g_bFenrir_Run;
extern int	g_iFenrir_Run;
#endif //! CSK_FIX_FENRIR_RUN	// ������ �� ������ �ϴ� �ҽ�
extern int  MoveSceneFrame;
//extern bool EnableEdit;
extern int  ErrorMessage;
extern bool InitServerList;
extern bool InitLogIn;
extern bool InitLoading;
extern bool InitCharacterScene;
extern bool InitMainScene;
extern bool EnableMainRender;
extern char *szServerIpAddress;
extern unsigned short g_ServerPort;
extern int g_iLengthAuthorityCode;

extern void LogInScene(HDC hDC);
extern void LoadingScene(HDC hDC);
extern void Scene(HDC Hdc);
extern bool CheckSpecialText(char *Text);
extern bool CheckName();
void    StartGame(
#ifdef PJH_CHARACTER_RENAME
			   bool IsConnect = false
#endif //#ifdef PJH_CHARACTER_RENAME
				  );

BOOL	ShowCheckBox( int num, int index, int message=MESSAGE_TRADE_CHECK );

int	SeparateTextIntoLines( const char* lpszText, char *lpszSeparated, int iMaxLine, int iLineSize);

#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
int		SearchServer(char *Name, bool extServer=false);
#endif // KJH_ADD_SERVER_LIST_SYSTEM
bool	GetTimeCheck(int DelayTime);
void	SetEffectVolumeLevel(int level);

// Ctrl + ���콺 �� �������� ����Ʈ ������ �����Ͽ��� 
// ī�޶��� CameraViewFar, CameraDistanceTarget, CameraDistance�� �����Ѵ�.
// ���� �ƹ��������� ����ϰ� ���� �ʴ� �Լ�
void    SetViewPortLevel ( int level );

// ������ �� �ִ� Ŭ������ ���� �����ϴ� �Լ�
// ReceiveCharacterList() ������ ���� ������ �޾Ƽ� g_byMaxClass ������ ����
void    SetCreateMaxClass ( BYTE MaxClass );

// ������ �� �ִ� Ŭ������ ���� ��� �Լ�
BYTE    GetCreateMaxClass ( void );

#ifdef PSW_BUGFIX_IME
bool IsEnterPressed();
void SetEnterPressed( bool enterpressed );
#endif //PSW_BUGFIX_IME

#ifdef DO_PROCESS_DEBUGCAMERA
void ProcessDebugCamera();
#endif // DO_PROCESS_DEBUGCAMERA

#endif //__ZZZSCENE_H__
