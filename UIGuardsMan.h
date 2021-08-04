//////////////////////////////////////////////////////////////////////////
//  
//  UIGuardsMan.h
//  
//  ��  �� : ������ �������̽�
//  
//  ��  ¥ : 2004�� 11�� 12��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIGUARDSMAN_H__076768BF_F97F_4B80_B84C_ADFFD37F4E39__INCLUDED_)
#define AFX_UIGUARDSMAN_H__076768BF_F97F_4B80_B84C_ADFFD37F4E39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUIGuardsMan  
{
public:
	CUIGuardsMan();
	virtual ~CUIGuardsMan();

protected:
	enum
	{
		BC_REQ_LEVEL = 200,			// ������ �����ϱ� ���� �ּ� ����
		BC_REQ_MEMBERCOUNT = 20		// ������ �����ϱ� ���� �ּ� ����ο�
	};
	enum REG_STATUS
	{
		REG_STATUS_NONE = 0,
		REG_STATUS_REG = 1
	};
	REG_STATUS	m_eRegStatus;		// ��ϻ���
	DWORD		m_dwRegMark;

public:
	bool IsSufficentDeclareLevel();	// ���� ��û ���� �������� �˻�
	bool HasRegistered() { return (m_eRegStatus == REG_STATUS_REG); }	// ���� ��û �����ΰ�
	void SetRegStatus( BYTE byStatus ) { m_eRegStatus = (REG_STATUS)byStatus; }	// ���� ��û ���� ������Ʈ (�����κ���)

	DWORD GetRegMarkCount() { return m_dwRegMark; }	// ��ϵ� ǥ���� ��
	void SetMarkCount( DWORD dwMarkCount ) { m_dwRegMark = dwMarkCount; }	// ��ϵ� ǥ���� �� ������Ʈ (�����κ���)

	DWORD GetMyMarkCount();		// �����ϰ� �ִ� ǥ���� ��
	int GetMyMarkSlotIndex();	// �����ϰ� �ִ� ù��° ǥ���� �κ��丮 �ε���
};

extern CUIGuardsMan g_GuardsMan;

#endif // !defined(AFX_UIGUARDSMAN_H__076768BF_F97F_4B80_B84C_ADFFD37F4E39__INCLUDED_)
