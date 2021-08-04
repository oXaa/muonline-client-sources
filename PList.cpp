//*****************************************************************************
// File: PList.cpp
//
// Desc: Implementation of the CPList class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "PList.h"

//*****************************************************************************
// Name: ������, �Ҹ��� ����
//*****************************************************************************
CPList::CPList()
{
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = NULL;
}

CPList::~CPList()
{
	RemoveAll();
}

// Name: Head/Tail Access �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : GetHead()\n
// �Լ� ���� : head�� ���� ����.
//*****************************************************************************/
void* CPList::GetHead() const
{ 
	if (NULL == m_pNodeHead)	// node�� ������ NULL ����.
		return NULL;

	return m_pNodeHead->data;		
}
/**
//*****************************************************************************
// �Լ� �̸� : GetTail()\n
// �Լ� ���� : Tail�� ���� ����.
//*****************************************************************************/
void* CPList::GetTail() const
{
	if (NULL == m_pNodeTail)	// node�� ������ NULL ����.
		return NULL;

	return m_pNodeTail->data;
}

// Name: Operations �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : RemoveHead()\n
// �Լ� ���� : Head�� �޸𸮿��� ���� �� �� ���� ����.
//*****************************************************************************/
void* CPList::RemoveHead()
{
	if (NULL == m_pNodeHead)			// node�� ������ NULL ����.
		return NULL;

	if (::IsBadReadPtr(m_pNodeHead, sizeof(NODE)))	// m_pNodeHead�� �޸𸮿�
		return NULL;								//������ NULL ����.

	NODE* pOldNode = m_pNodeHead;		// pOldNode�� m_pNodeHead�� ���� �ּ�.
	void* returnValue = pOldNode->data;	// head�� ���� returnValue��.
	m_pNodeHead = pOldNode->pNext;		// �ι�° node�� �ּҸ� m_pNodeHead�� ���.
	if (m_pNodeHead != NULL)			// node�� �� �̻��̶��.
		m_pNodeHead->pPrev = NULL;		// head�� ������ ���̹Ƿ�.
	else								// node�� �ϳ����ٸ�.
		m_pNodeTail = NULL;				// node�� �ϳ��� ���� ���̹Ƿ�.
	FreeNode(pOldNode);					// ���� head�� �����.

	return returnValue;					// ���� head�� ���� return.
}
/**
//*****************************************************************************
// �Լ� �̸� : RemoveTail()\n
// �Լ� ���� : Tail�� �޸𸮿��� ���� �� �� ���� ����.
//*****************************************************************************/
void* CPList::RemoveTail()
{
	if (NULL == m_pNodeTail)
		return NULL;

	if (::IsBadReadPtr(m_pNodeTail, sizeof(NODE)))
		return NULL;

	NODE* pOldNode = m_pNodeTail;
	void* returnValue = pOldNode->data;
	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);

	return returnValue;
}
/**
//*****************************************************************************
// �Լ� �̸� : AddHead()\n
// �Լ� ���� : Head�� ���ο� ���� �����ϰ� �� position ����.\n
// �Ű� ���� : newElement	: ���ο� ��.
//*****************************************************************************/
NODE* CPList::AddHead(void* newElement)
{
	// pPrev�� NULL�̰� pNext�� m_pNodeHead�� �� ��� ����.
	NODE* pNewNode = NewNode(NULL, m_pNodeHead);
	pNewNode->data = newElement;		// �� ��忡 ���ο� ���� �ִ´�.
	if (m_pNodeHead != NULL)			// ��� �ִ� list�� �ƴ϶��.
		m_pNodeHead->pPrev = pNewNode;	//m_pNodeHead->pPrev�� �� ��� ����.
	else								// ��� �ִ� list���.
		m_pNodeTail = pNewNode;			// �� ��带 tail��.
	m_pNodeHead = pNewNode;				// �� ��带 head��.

	return pNewNode;					// �� ��� ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : AddTail()\n
// �Լ� ���� : Tail�� ���ο� ���� �����ϰ� �� position ����.\n
// �Ű� ���� : newElement	: ���ο� ��.
//*****************************************************************************/
NODE* CPList::AddTail(void* newElement)
{
	NODE* pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;

	return pNewNode;
}
/**
//*****************************************************************************
// �Լ� �̸� : AddHead()\n
// �Լ� ���� : Head�� ���ο� list�� ����.\n
// �Ű� ���� : pNewList	: ������ CPList ��ü�� ������.
//*****************************************************************************/
BOOL CPList::AddHead(CPList* pNewList)
{
	if (NULL == pNewList)	// ���� list�� �ּҰ� NULL�̸�.
		return FALSE;		// ����.

	// ���� list�� tail�� �ּ� pos�� ����.
	NODE* pos = pNewList->GetTailPosition();
	while (pos != NULL)					// ���� list�� head���� �ݺ�.
		AddHead(pNewList->GetPrev(pos));// ���� list�� �� list�� ���δ�.

	return TRUE;					
}
/**
//*****************************************************************************
// �Լ� �̸� : AddTail()\n
// �Լ� ���� : Tail�� ���ο� list�� ����.\n
// �Ű� ���� : pNewList	: ������ CPList ��ü�� ������.
//*****************************************************************************/
BOOL CPList::AddTail(CPList* pNewList)
{
	if (NULL == pNewList)
		return FALSE;

	NODE* pos = pNewList->GetHeadPosition();
	while (pos != NULL)
		AddTail(pNewList->GetNext(pos));

	return TRUE;
}
/**
//*****************************************************************************
// �Լ� �̸� : RemoveAll()\n
// �Լ� ���� : list�� ��� �޸𸮸� ����.
//*****************************************************************************/
void CPList::RemoveAll()
{
	NODE* pNode;
	while (NULL != m_pNodeHead)	// m_pNodeHead�� NULL�� �ƴ� ������ �ݺ�.
	{
		pNode = m_pNodeHead;
		// �� ���� ����� �ּҸ� m_pNodeHead�� �ִ´�.
		m_pNodeHead = m_pNodeHead->pNext;
		delete pNode;			// ���� head�� �����.
	}
	m_pNodeTail = NULL;			// ������ ��� �ʱ�ȭ.
	m_nCount = 0;
}

// Name: Iteration �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : GetNext()\n
// �Լ� ���� : rPosition�� ���� position���� �ٲ�� ���� rPosition�� �� ����.\n
// �Ű� ���� : rPosition	: ���� position.
//							  �Լ� ���� �Ŀ� ���� position���� �ٲ�.
//*****************************************************************************/
void* CPList::GetNext(NODE*& rPosition) const
{
	NODE* pNode = rPosition;
	if (::IsBadReadPtr(pNode, sizeof(NODE)))	// pNode�� �޸𸮿� ������.
		return NULL;							// NULL ����.

	rPosition = pNode->pNext;					// ���� ����� �ּ� ����.

	return pNode->data;							// �� ����� �� ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : GetPrev()\n
// �Լ� ���� : rPosition�� ���� position���� �ٲ�� ������ rPosition�� �� ����.\n
// �Ű� ���� : rPosition	: ���� position.
//							  �Լ� ���� �Ŀ� ���� position���� �ٲ�.
//*****************************************************************************/
void* CPList::GetPrev(NODE*& rPosition) const
{
	NODE* pNode = rPosition;
	if (::IsBadReadPtr(pNode, sizeof(NODE)))	// pNode�� �޸𸮿� ������.
		return NULL;

	rPosition = pNode->pPrev;

	return pNode->data;
}

// Name: Retrieval/Modification �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : GetAt()\n
// �Լ� ���� : position�� ���� ����.\n
// �Ű� ���� : position	: ��� ���� ���� position.
//*****************************************************************************/
void* CPList::GetAt(NODE* position) const
{ 
	NODE* pNode = position;
	if (::IsBadReadPtr(pNode, sizeof(NODE)))	// pNode�� �޸𸮿� ������.
		return NULL;							// NULL ����.

	return pNode->data;							// �� node �� ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : SetAt()\n
// �Լ� ���� : position�� ���� ����.\n
// �Ű� ���� : position	: �����ϰ� ���� ���� position.
//*****************************************************************************/
BOOL CPList::SetAt(NODE* pos, void* newElement)
{ 
	NODE* pNode = pos;
	if (::IsBadReadPtr(pNode, sizeof(NODE)))	// pNode�� �޸𸮿� ������.
		return FALSE;							// ����.

	pNode->data = newElement;					// �� ���� �� node�� ����.

	return TRUE;
}
/**
//*****************************************************************************
// �Լ� �̸� : RemoveAt()\n
// �Լ� ���� : position�� ���� ����\n
// �Ű� ���� : position	: �����ϰ� ���� ���� position.
//*****************************************************************************/
BOOL CPList::RemoveAt(NODE* position)
{
	NODE* pOldNode = position;
	if (::IsBadReadPtr(pOldNode, sizeof(NODE)))	// pOldNode�� �޸𸮿� ������.
		return FALSE;							// ����.

	if (pOldNode == m_pNodeHead)				// �� ������ head���.
		// m_pNodeHead�� �� �������� ���� node�� ����Ű�� ��.
		m_pNodeHead = pOldNode->pNext;
	else										// �� ������ head�� �ƴ϶��.
	{
		// pOldNode->pPrev�� �޸𸮿� ������ ����.
		if (::IsBadReadPtr(pOldNode->pPrev, sizeof(NODE)))
			return FALSE;
		pOldNode->pPrev->pNext = pOldNode->pNext;// �� node�� ���� node�� ����.
	}

	if (pOldNode == m_pNodeTail)				// �� ������ tail�̶��.
		// m_pNodeTail�� �� �������� �� node�� ����Ű�� ��.
		m_pNodeTail = pOldNode->pPrev;
	else										// �� ������ tail�� �ƴ϶��.
	{
		// pOldNode->pNext�� �޸𸮿� ������ ����.
		if (::IsBadReadPtr(pOldNode->pNext, sizeof(NODE)))
			return FALSE;
		pOldNode->pNext->pPrev = pOldNode->pPrev;// ���� node�� �� ���� ����.
	}
	FreeNode(pOldNode);							// �� ��� ����.

	return TRUE;
}

// Name: Insertion �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : InsertBefore()\n
// �Լ� ���� : position ���� ���ο� �� ���� �� ���ο� ���� position ����.\n
// �Ű� ���� : position		: ���� position.\n
//			   newElement	: ������ ��.
//*****************************************************************************/
NODE* CPList::InsertBefore(NODE* position, void* newElement)
{
	if (position == NULL)		// ù��° ���ڰ� NULL�̸�.
		//  �ι�° ������ ���� Head �տ� ���̰�, ���� ����� �ּ� ����.
		return AddHead(newElement);

	NODE* pOldNode = position;
	// pPrev�� �� �������� ���ּ��̰�, pNext�� �� ������ �ּ��� �� ��� ����.
	NODE* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
	pNewNode->data = newElement;				// �� ��忡 ���ο� �� ����.
	if (pOldNode->pPrev != NULL)				// �� ��尡 head�� �ƴϸ�.
		pOldNode->pPrev->pNext = pNewNode;		// ���� ��带 �� ��忡 ����.
	else										// �� ��尡 head�̸�.
		m_pNodeHead = pNewNode;					// �� ��尡 haed�� ��.
	pOldNode->pPrev = pNewNode;					// �� ���� ����� ����.

	return pNewNode;							// ������� �ּ� ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : InsertAfter()\n
// �Լ� ���� : position �ڿ� ���ο� �� ���� �� ���ο� ���� position ����.\n
// �Ű� ���� : position		: ���� position.\n
//			   newElement	: ������ ��.
//*****************************************************************************/
NODE* CPList::InsertAfter(NODE* position, void* newElement)
{
	if (position == NULL)		// ù��° ���ڰ� NULL�̸�.
		// �ι�° ������ ���� Tail �ڿ� ���̰�, ���� ����� �ּ� ����.
		return AddTail(newElement);

	NODE* pOldNode = position;
	NODE* pNewNode = NewNode(pOldNode, pOldNode->pNext);
	pNewNode->data = newElement;
	if (pOldNode->pNext != NULL)
		pOldNode->pNext->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	pOldNode->pNext = pNewNode;

	return pNewNode;
}
/**
//*****************************************************************************
// �Լ� �̸� : Swap()\n
// �Լ� ���� : �� position�� ���� �¹ٲ�.\n
// �Ű� ���� : pNode1	: �¹ٲ� ���� position.\n
//			   pNode2	: �¹ٲ� ���� position.
//*****************************************************************************/
void CPList::Swap(NODE* pNode1, NODE* pNode2)
{
	if (pNode1 == NULL || pNode2 == NULL)
		return;

	void* temp;
	temp = pNode1->data;
	pNode1->data = pNode2->data;
	pNode2->data = temp;
}

// Name: Searching �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : Find()\n
// �Լ� ���� : searchValue�� startAfter�� position ���� ã��.
//			   ã�Ҵٸ� �� position ����. �� ã�Ҵٸ� NULL�� ����.\n
// �Ű� ���� : searchValue	: ã�� ��.\n
//			   startAfter	: ���� position. NULL�̸� Head ���� ã��.
//							  (�⺻���� NULL.)
//*****************************************************************************/
NODE* CPList::Find(void* searchValue, NODE* startAfter) const
{
	NODE* pNode = startAfter;
	if (pNode == NULL)				// �ι�° ���ڰ� NULL�̸� Head ���� ã�´�.
		pNode = m_pNodeHead;
	else
	{
		if (::IsBadReadPtr(pNode, sizeof(NODE)))	// pNode�� �޸𸮿� ������.
			return NULL;							// NULL ����.

		// �ι�° ���ڰ� NULL�� �ƴϸ� �� ���� ������ ã�´�.
		pNode = pNode->pNext;
	}
	// ���õ� ��� ���� ���ʷ� ������ �˻�.
	for (; pNode != NULL; pNode = pNode->pNext)
		if (pNode->data == searchValue)				// ���� ã����.
			return pNode;							// �� ��� �ּ� ����.

	return NULL;									// �� ã���� NULL ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : FindIndex()\n
// �Լ� ���� : head���� nIndex��° position ����.\n
// �Ű� ���� : nIndex	: ã�� position�� �ε���.
//*****************************************************************************/
NODE* CPList::FindIndex(int nIndex) const
{
	// ���ڰ� ��� �� �̻��̰ų� ������ �� NULL ����.
	if (nIndex >= m_nCount || nIndex < 0)
		return NULL;

	NODE* pNode = m_pNodeHead;						// head����.
	while (nIndex--)								// ���ʷ� ���� ��ŭ.
		pNode = pNode->pNext;						// ��带 �̵��ؼ�.

	return pNode;									// �� ��� ����.
}

// Name: Node Construction/Destruction �Լ� ����
/**
//*****************************************************************************
// �Լ� �̸� : NewNode()\n
// �Լ� ���� : �� ��� ���� ���� �� �� position ����.\n
// �Ű� ���� : pPrev	: ���� position.\n
//			   pNext	: ���� position.
//*****************************************************************************/
NODE* CPList::NewNode(NODE* pPrev, NODE* pNext)
{
	NODE* pNode = new NODE;			// ��� ����ü ũ�� ��ŭ �޸� ���� �Ҵ�.
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;						// list�� �� ���� 1����.
	pNode->data = NULL;				// �� ����� �� �ʱ�ȭ.

	return pNode;					// �� ��� �ּ� ����.
}
/**
//*****************************************************************************
// �Լ� �̸� : FreeNode()\n
// �Լ� ���� : �� position�� �޸� ����.\n
// �Ű� ���� : pNode	: ������ position.
//*****************************************************************************/
void CPList::FreeNode(NODE* pNode)
{
	delete pNode;					// ��� ����.
	m_nCount--;						// list�� �� ���� 1����.
	if (m_nCount == 0)				// list�� ��尡 �ϳ��� ������.
		RemoveAll();
}
