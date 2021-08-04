//*****************************************************************************
// File: ServerMsgWin.h
//
// Desc: interface for the CServerMsgWin class.
//		 ���� �޽��� â Ŭ����.(ĳ���� ���þ����� ���)
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_SERVERMSGWIN_H__8C6AB678_703D_4A60_B334_C30A97EEC64B__INCLUDED_)
#define AFX_SERVERMSGWIN_H__8C6AB678_703D_4A60_B334_C30A97EEC64B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinEx.h"

#define SMW_MSG_LINE_MAX	5	// �޽��� �� ��.
#define SMW_MSG_ROW_MAX		83	// ���ٿ� �ִ� ����(byte)�� + 1

class CServerMsgWin : public CWinEx
{
protected:
	char	m_aszMsg[SMW_MSG_LINE_MAX][SMW_MSG_ROW_MAX];// �޽��� ���ڿ�.
	int		m_nMsgLine;									// �޽��� �� ��.

public:
	CServerMsgWin();
	virtual ~CServerMsgWin();

	void Create();
	bool CursorInWin(int nArea);

	void AddMsg(char* pszMsg);

protected:
	void RenderControls();
};

#endif // !defined(AFX_SERVERMSGWIN_H__8C6AB678_703D_4A60_B334_C30A97EEC64B__INCLUDED_)
