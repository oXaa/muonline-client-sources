//*****************************************************************************
// File: PList.h
//
// Desc: Pointer list class header file.
//		 ������ ����Ʈ Ŭ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#ifndef _PLIST_H_
#define _PLIST_H_

#include <windows.h>

//*****************************************************************************
// Name: NODE struct
// Desc: ���� ���� ������ ����Ʈ�� ��� ����ü ����.
//*****************************************************************************
struct NODE
{
	NODE* pNext;						///< �� ��� �ּ�.						
	NODE* pPrev;						///< �� ��� �ּ�.
	void* data;							///< �ڷ�.
};

//*****************************************************************************
// Name: CPList Class
// Desc: ������ ����Ʈ Ŭ���� ����.
//*****************************************************************************
class CPList
{
public:
	CPList();							// ������.
	~CPList();							// �Ҹ���.

// Head/Tail Access
	void* GetHead() const;				///< head�� ���� ���ϴ� �Լ�.
	void* GetTail() const;				///< tail�� ���� ���ϴ� �Լ�.

// Operations
	void* RemoveHead();					///< Head�� �޸𸮿��� �����ϴ� �Լ�.
	void* RemoveTail();					///< Tail�� �޸𸮿��� �����ϴ� �Լ�.
	NODE* AddHead(void* newElement);	///< head�� ���ο� ���, ���� �����ϴ� �Լ�.
	NODE* AddTail(void* newElement);	///< tail�� ���ο� ���, ���� �����ϴ� �Լ�.
	BOOL AddHead(CPList* pNewList);		///< head�� ���ο� list �����ϴ� �Լ�.
	BOOL AddTail(CPList* pNewList);		///< tail�� ���ο� list �����ϴ� �Լ�.
	void RemoveAll();					///< list�� ��� �޸𸮸� �����ϴ� �Լ�.

// Iteration
	/// head�� position�� ���ϴ� �Լ�.
	NODE* GetHeadPosition() const { return m_pNodeHead; }
	/// tail�� position�� ���ϴ� �Լ�.
	NODE* GetTailPosition() const { return m_pNodeTail; }
	void* GetNext(NODE*& rPosition) const;///<�� node �� ����, ���� ��� �ּҷ�.
    void* GetPrev(NODE*& rPosition) const;///<�� node �� ����, ���� ��� �ּҷ�.

// Retrieval/Modification
	void* GetAt(NODE* position) const;	///< �� node ���� ���ϴ� �Լ�.
	BOOL SetAt(NODE* pos, void* newElement);///< �� ��ġ���� ���ο� ���� set.
	BOOL RemoveAt(NODE* position);		///< �� ��ġ�� ���� �����ϴ� �Լ�.

// Insertion
	/// �� ��ġ �տ� ���ο� ���, �� ����.
	NODE* InsertBefore(NODE* position, void* newElement);
	///<�� ��ġ ���� ���ο� ���, �� ����.
	NODE* InsertAfter(NODE* position, void* newElement);

// Swap
	void Swap(NODE* pNode1, NODE* pNode2);	///< ���� �Լ�.

// Searching
	/// ã�� ���� �ּҸ� ���ϴ� �Լ�.
	NODE* Find(void* searchValue, NODE* startAfter = NULL) const;
	NODE* FindIndex(int nIndex) const;	///< head���� nIndex��° �ּ� ����.

// Status 
	int GetCount() const { return m_nCount; }		///< node�� ������ ���ϴ� �Լ�.
	BOOL IsEmpty() const { return 0 == m_nCount; }	///< list�� ����°�?

protected:
// Data Member
	NODE*	m_pNodeHead;				///< head node �ּ�.
	NODE*	m_pNodeTail;				///< tail node �ּ�.
	int		m_nCount;					///< �� node ��.

// Node Construction/Destruction
	NODE* NewNode(NODE* pPrev, NODE* pNext);///< �� ��� ���� ���� �Լ�.
	void FreeNode(NODE* pNode);			///< ��� ���� �Լ�.
};

#endif