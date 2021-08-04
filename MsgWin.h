//*****************************************************************************
// File: MsgWin.h
//
// Desc: interface for the CMsgWin class.
//		 �޽��� â Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_MSGWIN_H__4935BB60_ADC3_47E5_BA5F_832A03874FBA__INCLUDED_)
#define AFX_MSGWIN_H__4935BB60_ADC3_47E5_BA5F_832A03874FBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"

#include "Button.h"

#define	MW_MSG_LINE_MAX		2
#define	MW_MSG_ROW_MAX		52	// winmain.cpp�� nFixFontHeight�� 14�� �� 45, 13�� �� 52

#ifdef LJH_ADD_LOCALIZED_BTNS
enum MSG_WIN_TYPE		// �޽��� ������ Ÿ��.
{
	MWT_NON,			// �ƹ��͵� ����.
		MWT_BTN_CANCEL,		// ��� ��ư�� ����.
		MWT_BTN_OK,			// Ȯ�� ��ư�� ����.
		MWT_BTN_BOTH,		// Ȯ��, ��� ��ư ����.
		MWT_STR_INPUT,		// ���� �Է�.
		MWT_BTN_LOCALIZED_YESNO,			// (Localized)��, �ƴϿ� ��ư ����
		MWT_BTN_LOCALIZED_CONFIRM_CANCEL,	// (Localized)Ȯ��,��� ��ư�� ����
		MWT_BTN_LOCALIZED_CONFIRM_ONLY,		// (Localized)Ȯ�� ��ư�� ����
};
#endif //LJH_ADD_LOCALIZED_BTNS


class CMsgWin : public CWin  
{
protected:
#ifndef LJH_ADD_LOCALIZED_BTNS
	enum MSG_WIN_TYPE		// �޽��� ������ Ÿ��.
	{
		MWT_NON,			// �ƹ��͵� ����.
		MWT_BTN_CANCEL,		// ��� ��ư�� ����.
		MWT_BTN_OK,			// Ȯ�� ��ư�� ����.
		MWT_BTN_BOTH,		// Ȯ��, ��� ��ư ����.
		MWT_STR_INPUT,		// ���� �Է�.
	};
#endif  //LJH_ADD_LOCALIZED_BTNS

	CSprite			m_sprBack;		// �޽��� ������ ��� ��������Ʈ.
	CSprite			m_sprInput;		// �Է¶� ��������Ʈ.
	CButton			m_aBtn[2];		// OK, Cancel ��ư.
	char			m_aszMsg[MW_MSG_LINE_MAX][MW_MSG_ROW_MAX];	// �޽��� ���ڿ�.
	int				m_nMsgLine;		// �޽��� ���� ��.
	int				m_nMsgCode;		// �޽��� �ڵ�.
	MSG_WIN_TYPE	m_eType;		// �޽��� ������ Ÿ��.
	short			m_nGameExit;	// �������� ī��Ʈ.(-1 ~ 5)
	double			m_dDeltaTickSum;// �������� ī��Ʈ�� ���Ǵ� �ð����� ��.

public:
	CMsgWin();
	virtual ~CMsgWin();

#ifdef LJH_ADD_LOCALIZED_BTNS
	void Create(int p_iBtnType = 0);
#else  //LJH_ADD_LOCALIZED_BTNS
	void Create();
#endif //LJH_ADD_LOCALIZED_BTNS
	void SetPosition(int nXCoord, int nYCoord);
	void Show(bool bShow);
	bool CursorInWin(int nArea);
	void PopUp(int nMsgCode, char* pszMsg = NULL);

protected:
	void PreRelease();
	void UpdateWhileActive(double dDeltaTick);
	void RenderControls();

	void SetCtrlPosition();
	void SetMsg(MSG_WIN_TYPE eType, LPCTSTR lpszMsg, LPCTSTR lpszMsg2 = NULL);
	void ManageOKClick();
	void ManageCancelClick();
	void InitResidentNumInput();
	void RequestDeleteCharacter();

#ifdef LJH_ADD_ONETIME_PASSWORD
	void ClearLoginInfoFromInputBox();
	void SendingLoginInfoWOOPT();
	void ReturnToConnServerWin();
#endif //LJH_ADD_ONETIME_PASSWORD
};

#endif // !defined(AFX_MSGWIN_H__4935BB60_ADC3_47E5_BA5F_832A03874FBA__INCLUDED_)
