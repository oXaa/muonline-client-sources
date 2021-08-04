//*****************************************************************************
// File: UIMng.h
//
// Desc: interface for the CUIMng class.
//		 ���� ����� UI �Ŵ��� Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_UIMNG_H__9C8B9D12_9584_47C7_8F6E_6E9F402ACB65__INCLUDED_)
#define AFX_UIMNG_H__9C8B9D12_9584_47C7_8F6E_6E9F402ACB65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PList.h"

#include "MsgWin.h"
#include "SysMenuWin.h"
#include "OptionWin.h"
#include "LoginMainWin.h"
#include "ServerSelWin.h"
#include "LoginWin.h"
#include "CreditWin.h"
#include "CharSelMainWin.h"
#include "CharMakeWin.h"
#include "CharInfoBalloonMng.h"
#include "ServerMsgWin.h"
#ifdef LJH_ADD_ONETIME_PASSWORD
#include "OneTimePassword.h"
#endif //LJH_ADD_ONETIME_PASSWORD


// m_nScene�� �� ����.
#define	UIM_SCENE_NONE			0		// �� ����.
#define	UIM_SCENE_TITLE			1		// Ÿ��Ʋ ��.
#define UIM_SCENE_LOGIN			2		// �α��� ��.
#define	UIM_SCENE_LOADING		3		// �ε� ��.
#define	UIM_SCENE_CHARACTER		4		// ĳ���� ���� ��.
#define	UIM_SCENE_MAIN			5		// �� ���� ��.

class CSprite;
class CGaugeBar;
class CWin;
class CLoadingScene;

class CUIMng  
{
public:
// ����
	CMsgWin			m_MsgWin;			// �޽��� â.
	CSysMenuWin		m_SysMenuWin;		// �ý��� �޴� â.
	COptionWin		m_OptionWin;		// �ɼ� â.

// �α��� ��
	CLoginMainWin	m_LoginMainWin;		// �α��� �� ���� �޴�.
	CServerSelWin	m_ServerSelWin;		// ���� ���� â.
	CLoginWin		m_LoginWin;			// �α��� â.
	CCreditWin		m_CreditWin;		// ũ���� â.
#ifdef LJH_ADD_LOCALIZED_BTNS
	CMsgWin			m_LocalizedYESNOMsgWin;				// (localized)��, �ƴϿ� �޽��� â
	CMsgWin			m_LocalizedConfirmCancelMsgWin;		// (localized)Ȯ��, ��� �޽��� â
#endif //LJH_ADD_LOCALIZED_BTNS
#ifdef LJH_ADD_ONETIME_PASSWORD
	COneTimePassword	m_OneTimePasswordWin;	// ��Ÿ�� �н����� â.
#endif //LJH_ADD_ONETIME_PASSWORD


// ĳ���� ���� ��.
	CCharSelMainWin	m_CharSelMainWin;	// ĳ���� ���� �� ���� �޴�.
	CCharMakeWin	m_CharMakeWin;		// ĳ���� ���� â.
	CCharInfoBalloonMng	m_CharInfoBalloonMng;// ĳ���� ���� ��ǳ�� �Ŵ���.
	CServerMsgWin	m_ServerMsgWin;		// ���� �޽��� ������.

// �ε� ��
	CLoadingScene*	m_pLoadingScene;	// �ε� ��.

protected:
// Ÿ��Ʋ ��
	CSprite*		m_asprTitle;		// ��������Ʈ��.
	CGaugeBar*		m_pgbLoding;		// �ε� ��������.

	// m_WinList�� �� Class���� ������ ��� �����찡 ���. ���� ���̴� �Ⱥ���
	//�� ��� m_WinList�� ����Ǿ� ����. list ���� ����� ���̴� ���� Ȱ��ȭ ��
	//���� ����. �� Ȱ��ȭ ������� �� �ϳ��̰ų� ����.
	CPList			m_WinList;			// ������ ����Ʈ.
	bool			m_bCursorOnUI;		// UI ���� Ŀ���� �ִ°�?
	bool			m_bBlockCharMove;	// ĳ���� �̵��� ���°�?(�����Կ��� �������� ������ �̿�)
	int				m_nScene;			// ��.
	bool			m_bWinActive;		// true�̸� m_WinList�� head �����찡 Active(��Ŀ��).
	bool			m_bSysMenuWinShow;	// �ý��� �޴� â�� �������� �Ǵ°�?
										//(ESCŰ ����̹Ƿ� �߰�)

// �α��� ��
#ifdef MOVIE_DIRECTSHOW
	bool			m_bMoving;			// �α��� ������ ���� �÷��� ������ �˻�
#endif // MOVIE_DIRECTSHOW

public:
	virtual ~CUIMng();

	static CUIMng& Instance();

// Ÿ��Ʋ �� �κ�.
	void CreateTitleSceneUI();
	void ReleaseTitleSceneUI();
	void RenderTitleSceneUI(HDC hDC, DWORD dwNow, DWORD dwTotal);
// ~Ÿ��Ʋ �� �κ�.

	void Create();
	void Release();
	void CreateLoginScene();
	void CreateCharacterScene();
	void CreateMainScene();
	void Update(double dDeltaTick);
	void Render();

	void ShowWin(CWin* pWin);
	void HideWin(CWin* pWin);

	bool IsCursorOnUI() { return m_bCursorOnUI; }	// UI ���� Ŀ���� �ִ°�?
	void PopUpMsgWin(int nMsgCode, char* pszMsg = NULL);
	void AddServerMsg(char* pszMsg);
	void CloseMsgWin() { HideWin(&m_MsgWin); }
	void SetSysMenuWinShow(bool bShow) { m_bSysMenuWinShow = bShow; }
	bool IsSysMenuWinShow() { return m_bSysMenuWinShow; };	// �ý��� �޴� â�� �������� �Ǵ°�?

#ifdef MOVIE_DIRECTSHOW
	void SetMoving(bool bMoving) { m_bMoving = bMoving; };
	bool IsMoving() { return m_bMoving; };
#endif // MOVIE_DIRECTSHOW

protected:
	CUIMng();

	void RemoveWinList();
	CWin* SetActiveWin(CWin* pWin);
	void CheckDockWin();
	bool SetDockWinPosition(CWin* pMoveWin, int nDockX, int nDockY);
};

#endif // !defined(AFX_UIMNG_H__9C8B9D12_9584_47C7_8F6E_6E9F402ACB65__INCLUDED_)
