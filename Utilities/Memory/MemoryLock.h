// MemoryLock.h: interface for the CMemoryLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYLOCK_H__ED135F22_F857_4DDE_9846_52935BCE88FD__INCLUDED_)
#define AFX_MEMORYLOCK_H__ED135F22_F857_4DDE_9846_52935BCE88FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef _DEBUG
#define ML_NOCORRUPT	// �̻���� �� ���ư����� üũ�� ���� ������ �̰��� Ȱ��ȭ�Ѵ�.
#endif //_DEBUG

#ifdef _DEBUG
#define GO_DEBUG	_asm { int 3 }
#else
#define GO_DEBUG	{}
#endif


#include "HashTable.h"


#define SIZE_XOR_MEMORYLOCK	( 16)


class CMemoryLock : public CHashTable <BYTE*, void*>
{
public:
	CMemoryLock();
	virtual ~CMemoryLock();
	void Clear( void);

	virtual void Destroy( void);

protected:
	HWND m_hWnd;	// ���� �޽����� ���� ������ �ڵ�
	UINT m_uiMessage;	// �����쿡 ���� �޽���
#ifdef _DEBUG
	int m_iUsedCount;
#endif

public:
	static BYTE s_byXor[SIZE_XOR_MEMORYLOCK];

public:
	void Init( HWND hWnd, UINT uiMessage);

	template <class T>
	void Lock( T &Data)
	{
		return;
	}

	template <class T>
	void UnLock( T &Data)
	{	// ����, ���� �� ����
		return;
	}

	template <class T>
	T Get( T &Data)
	{
		return Data;
	}

	template <class T>
	void Release( T &Data)
	{
		return;
	}
	
protected:
	template <class T>
	void MakeConvertedDataAndCorrupt( BYTE *pbyDst, T &Data)
	{
		return;
	}

	template <class T>
	void RestoreConvertedData( T &Data, BYTE *pbySrc)
	{
		return;
	}

	// ���̺���� ��ġ�� �̵��ϵ��� �ϱ� ���� �κ�
protected:
	void *m_pDumpMemory;	// new �Ҷ� ��ġ�� �� ���������� �ϱ� ���� �κ�
	DWORD m_dwHashKey;	// �ؽ�Ű�� �����ص� ������ �̵��� ���� ������ ����
	BYTE **m_ppDataTableAlloc;	// �Ҵ綧�� ������ - �̰��� ���� ������ new �� ��� ���� �ϴ� ���� ������ ��� �ּҰ� ���ư��鼭 new �Ǳ� ������ �װ��� ������ �ٸ� ������ new �ؼ� random ���� �ణ �ּҸ� �����ϱ� �����̴�.
	void **m_ppKeyTableAlloc;	// �Ҵ綧�� ������
	void ResetDumpMemory( void)
	{
		return;
	}
	void RegenerateHashKey( void)
	{
		return;
	}
public:
	virtual DWORD Hash( void *pKey)
	{
		return 0;
	}
	void Reposition( void)	// ���̺� ���� ��ġ�� �ٲ��ش� ( � �͵� Lock ���� ���� ���¿����� ����)
	{
		return;
	}
};


#endif // !defined(AFX_MEMORYLOCK_H__ED135F22_F857_4DDE_9846_52935BCE88FD__INCLUDED_)
