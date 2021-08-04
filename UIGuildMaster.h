//////////////////////////////////////////////////////////////////////////
//  
//  UIGuildMaster.h
//  
//  ��  �� : NPC ��帶���� Ŭ���� �����ִ� �������̽�
//  
//  ��  ¥ : 2004�� 11�� 09��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIGUILDMASTER_H__A1F8F21B_D41E_4688_A9E8_C5B29A6F3074__INCLUDED_)
#define AFX_UIGUILDMASTER_H__A1F8F21B_D41E_4688_A9E8_C5B29A6F3074__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIWindows.h"

class CUIManager;
class CUIGuildInfo;
class CUIGuildMaster;

enum eCurrentMode	{ MODE_NONE, MODE_CREATE_GUILD, MODE_EDIT_GUILDMARK };
enum eCurrentStep	{ STEP_MAIN, STEP_CREATE_GUILDINFO, STEP_EDIT_GUILD_MARK, STEP_CONFIRM_GUILDINFO };


// ��� ������ �������̽�
class CUIGuildMaster : public CUIControl
{
public:
	CUIGuildMaster();
	virtual ~CUIGuildMaster();

protected:
	bool			m_bOpened;
	// STEP_MAIN
	CUIButton		m_CreateGuildButton;
	CUIButton		m_EditGuildMarkButton;

	CUIButton		m_NextButton;
	CUIButton		m_PreviousButton;

	DWORD			m_dwEditGuildMarkConfirmPopup;
	DWORD			m_dwGuildRelationShipReplyPopup;

protected:
	BOOL IsValidGuildName( const char* szName );		// ��ȿ�� �������� �˻�
	BOOL IsValidGuildMark();							// ��ȿ�� ��帶ũ���� �˻�

	// ����, ���� ��ư ���������� ���� ����
	void StepPrev();
	void StepNext();

	// �� �������̽����� ��� �˾��� �ݴ´�.
	void CloseMyPopup();

// ��� �����		STEP_MAIN -> STEP_CREATE_GUILDINFO -> STEP_CONFIRM_GUILDINFO
	// ��� ����� - ����, ��ũ �Է� ( STEP_CREATE_GUILDINFO )
	void DoCreateGuildAction();
	void RenderCreateGuild();

	// ��� ����� - �������� Ȯ�� ( STEP_CONFIRM_GUILDINFO )
	void DoCreateInfoAction();
	void RenderCreateInfo();


// ��帶ũ ����	STEP_MAIN -> STEP_EDIT_GUILD_MARK -> STEP_CONFIRM_GUILDINFO
	// ��帶ũ ���� ( STEP_EDIT_GUILD_MARK )
	void DoEditGuildMarkAction();
	void RenderEditGuildMark();


// ��帶���� �ʱ�ȭ�� ( STEP_MAIN )
	void DoGuildMasterMainAction();
	void RenderGuildMasterMain();

public:
	// ������α� ��û ����
	void ReceiveGuildRelationShip( BYTE byRelationShipType, BYTE byRequestType, BYTE  byTargetUserIndexH, BYTE byTargetUserIndexL );

	virtual BOOL DoMouseAction();
	virtual void Render();
	void Open();
	bool IsOpen();
	virtual void Close();
};

#endif // !defined(AFX_UIGUILDMASTER_H__A1F8F21B_D41E_4688_A9E8_C5B29A6F3074__INCLUDED_)
