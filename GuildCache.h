//////////////////////////////////////////////////////////////////////////
//  
//  GuildCache.h
//  
//  ��  �� : ������� ĳ��
//  
//  ��  ¥ : 2004�� 11�� 09��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILDCACHE_H__5B2412C7_A182_4E40_99F5_2CA896A9EE64__INCLUDED_)
#define AFX_GUILDCACHE_H__5B2412C7_A182_4E40_99F5_2CA896A9EE64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern MARK_t GuildMark[MAX_MARKS];

// ��� ���� ĳ��
class CGuildCache
{
public:
	CGuildCache();
	virtual ~CGuildCache();

protected:
	DWORD	m_dwCurrIndex;											// ����� �ε��� (0���� ����)

public:
	void Reset();													// �����̵��ϰų� �����ӽ� ȣ��

	BOOL IsExistGuildMark( int nGuildKey );							// ��帶ũ ���翩�� Ȯ��
	int GetGuildMarkIndex( int nGuildKey );							// ���Ű�� ��帶ũ �ε��� ��ȯ

	int MakeGuildMarkIndex( int nGuildKey );						// ��帶ũ ����Ȯ��
	int SetGuildMark( int nGuildKey, BYTE* UnionName, BYTE* GuildName,BYTE* Mark );		// ��帶ũ ������ ��ũ �ֱ�
};

#endif // !defined(AFX_GUILDCACHE_H__5B2412C7_A182_4E40_99F5_2CA896A9EE64__INCLUDED_)
