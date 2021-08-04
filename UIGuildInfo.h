//////////////////////////////////////////////////////////////////////////
//  
//  UIGuildInfo.h
//  
//  ��  �� : ������� �������̽� ( G Ű �Է½� )
//  
//  ��  ¥ : 2004�� 11�� 09��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIGUILDINFO_H__EC7AE059_4458_4AA3_A31E_C893AEFDECD2__INCLUDED_)
#define AFX_UIGUILDINFO_H__EC7AE059_4458_4AA3_A31E_C893AEFDECD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "UIWindows.h"


class CUIManager;
class CUIGuildInfo;
class CUIGuildMaster;

extern int s_nTargetFireMemberIndex;

// �������
enum GUILD_STATUS
{
	G_NONE			= (BYTE)-1,
	G_PERSON		= 0,
	G_MASTER		= 128,
	G_SUB_MASTER	= 64,
	G_BATTLE_MASTER	= 32
};
// ���Ÿ��
enum GUILD_TYPE
{
	GT_NORMAL		= 0x00,		// �Ϲݱ��
	GT_ANGEL		= 0x01		// ��ȣõ����
};
// ������
enum GUILD_RELATIONSHIP
{
	GR_NONE			= 0x00,		// ���迲��
	GR_UNION		= 0x01,		// ��忬��
	GR_UNIONMASTER	= 0x04,		// ��忬�ո�����
	GR_RIVAL		= 0x02,		// ������
	GR_RIVALUNION	= 0x08		// �������忬��
};

// ��� ����â
class CUIGuildInfo : public CUIControl
{
public:
	CUIGuildInfo();
	virtual ~CUIGuildInfo();

protected:
	bool			m_bOpened;
	int				m_nCurrentTab;		// ���� �� ( 0: ���, 1:����, 2:��忬�� )

	BOOL			m_bRequestUnionList;	// ���ո���Ʈ��û�ߴ��� ���� (â�ݱ������� �ѹ���)

	char			m_szRivalGuildName[MAX_GUILDNAME+1];

	CUINewGuildMemberListBox	m_GuildMemberListBox;
	CUIGuildNoticeListBox		m_GuildNoticeListBox;
	CUIUnionGuildListBox		m_UnionListBox;

	DWORD			m_dwPopupID;

	// ��� - ��ü/Ż�� ��ư
	CUIButton		m_BreakUpGuildButton;

	// ���� - ��å, ����, ���� ��ư
	CUIButton		m_AppointButton;
	CUIButton		m_DisbandButton;
	CUIButton		m_FireButton;

	// ���� - ��ü/Ż��
	CUIButton		m_BreakUnionButton;

	// ���� - ����
	CUIButton		m_BanUnionButton;
	
protected:
	BOOL IsGuildMaster()	{ return ( Hero->GuildStatus == G_MASTER ); }			// �渶�ΰ�
	BOOL IsSubGuildMaster()	{ return ( Hero->GuildStatus == G_SUB_MASTER ); }		// �α渶�ΰ�
	BOOL IsBattleMaster()	{ return ( Hero->GuildStatus == G_BATTLE_MASTER ); }	// ��Ʋ�������ΰ�

	int GetGuildMemberIndex( char* szName );
	const char* GetGuildMasterName();
	const char* GetSubGuildMasterName();
	const char* GetBattleMasterName();

	// �� �������̽����� ��� �˾��� �ݴ´�.
	void CloseMyPopup();
	
	// ���
	void DoGuildInfoTabMouseAction();
	void RenderGuildInfoTab();

	// ����
	void DoGuildMemberTabMouseAction();
	void RenderGuildMemberTab();

	// ��忬��
	void DoGuildUnionMouseAction();
	void RenderGuildUnionTab();

public:
	void SetRivalGuildName( char* szName );

	void AddGuildNotice( char* szText );		// ������ �߰�
	void ClearGuildLog();

	void AddMemberList( GUILD_LIST_t* pInfo );
	void ClearMemberList();

	void AddUnionList( BYTE* pGuildMark, char* szGuildName, int nMemberCount );
	int GetUnionCount();
	void ClearUnionList();

	virtual BOOL DoMouseAction();
	virtual void Render();
	void Open();
	bool IsOpen();
	virtual void Close();
};

void    UseBattleMasterSkill ( void );

#endif // !defined(AFX_UIGUILDINFO_H__EC7AE059_4458_4AA3_A31E_C893AEFDECD2__INCLUDED_)
