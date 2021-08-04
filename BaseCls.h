/*-*-*-*                                                   *-*-*-*/
/*-*-*-*     Base Classes Library  Ver 1.31 Release 018    *-*-*-*/
/*-*-*-*                                                   *-*-*-*/
//- BaseCls.h
//  Template Library of [[ Doubly Linked List ]] and [[ Queue ]] and [[ Stack ]] and [[ Binary Tree ]]
//	and [[ Elastic Dimension ]] and [[ Sorted Queue ]]
//  By SeongMin Hong ( 1999. 3. 18 - 2002. 4. 19)


# ifndef __BASE_CLASSES_H__
# define __BASE_CLASSES_H__



//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CNode template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//



template <class T> class CList;	// ���� ���� - CNode���� ����ϱ� ����


template <class T>
class CNode
{
	protected:
		T m_Data;	// �⺻ ������
		CNode<T>* m_pPrev;	// �տ� ��ũ�� ���
		CNode<T>* m_pNext;	// �ڿ� ��ũ�� ���

		// ���� ��� ó��
		void SetPrev( CNode<T>* pPrev)	{ m_pPrev = pPrev; }
		CNode<T>* GetPrev( void)		{ return ( m_pPrev); }

		// ���� ��� ó��
		void SetNext( CNode<T>* pNext)	{ m_pNext = pNext; }
		CNode<T>* GetNext( void)		{ return ( m_pNext); }

		friend class CList<T>;

	public:
		CNode();
		CNode( T Data);
		~CNode();
		//void* operator new( size_t stAllocate);

		// ������ ó��
		void SetData( T Data)	{ m_Data = Data; }
		T& GetData( void)		{ return ( m_Data);	}
};


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Constructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>::CNode()
{
	m_pPrev = m_pNext = NULL;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Constructor	; not tested
//
//	<< Data : ��尡 ������ ������
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>::CNode( T Data)
{
	m_Data = Data;
	m_pPrev = m_pNext = NULL;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Destructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>::~CNode()
{
}

/*template <class T>
void* CNode<T>::operator new( size_t stAllocate)
{
	return ( new char [stAllocate]);
}*/

//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CList template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//

template <class T>
class CList
{
	private:
		long m_lCount;	// Stack �ȿ� ����ִ� Node ����
		//T m_NullData;	// NULL ���Ͽ� ���� ��
		CNode<T>* m_pHead;	// Head ���
		CNode<T>* m_pTail;	// Tail ���

	public:
		CList();	// Constructor
		~CList();	// Destructor

		LONG GetCount( void)	{ return ( m_lCount); }	// Stack �ȿ� ����ִ� Node ������ ��´�.

		CNode<T>* AddHead( T NewElement);	// Head ���� �߰�
		CNode<T>* AddTail( T NewElement);	// Tail ���� �߰�
		CNode<T>* InsertBefore( CNode<T>* pNode, T NewElement);
		CNode<T>* InsertAfter( CNode<T>* pNode, T NewElement);

		T RemoveHead( void);	// Head ��� ����
		T RemoveTail( void);	// Tail ��� ����
		T RemoveNode( CNode<T>* &pNode);	// ��带 ã�Ƽ� ����
		void RemoveAll( void);	// ���� ����

		BOOL IsEmpty( void)	{ return ( m_pHead->GetNext() == m_pTail); }	// ����Ʈ�� ����ִ��� üũ

		CNode<T>* FindHead( void);	// Head ��� ã��
		CNode<T>* FindTail( void);	// Tail ��� ã��
		CNode<T>* FindNode( T SearchValue);	// SearchValue�� Data�� ���� �ִ� ��� ã��

		CNode<T>* GetPrev( CNode<T>* pNode);
		CNode<T>* GetNext( CNode<T>* pNode);
		void SetData( CNode<T>* pNode, T Data);
		T& GetData( CNode<T>* pNode);
};



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Constructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CList<T>::CList()
{
	// ����� ���Ϸ��� �����.
	m_pHead = new CNode<T>;
	m_pTail = new CNode<T>;

	// ����� ���Ϸ� ����
	m_pHead->SetNext( m_pTail);
	m_pTail->SetPrev( m_pHead);

	m_lCount = 0;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Destructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CList<T>::~CList()
{
	RemoveAll();
	delete m_pTail;
	delete m_pHead;
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	AddHead - ���ο� ���� ������ ��带 �����ؼ� Head�� ���δ�.	; not tested
//
//	<< NewElement : ���� �����Ǵ� ��尡 ���� ��
//
//	>> CNode<T>* : ���� ������ ���
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::AddHead( T NewElement)
{
	CNode<T>* pOne = new CNode<T>;

	if ( pOne == NULL)
	{	// �޸� �Ҵ��� �����ϸ�
		return ( NULL);
	}

	pOne->SetData( NewElement);

	// ���ο� ����� �ڿ� ���� �� ����
	pOne->SetNext( m_pHead->GetNext());
	( m_pHead->GetNext())->SetPrev( pOne);
	// ���ο� ����� �տ� ��� ���̱�
	pOne->SetPrev( m_pHead);
	m_pHead->SetNext( pOne);

	m_lCount++;

	return ( pOne);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	AddTail - ���ο� ���� ������ ��带 �����ؼ� Tail�� ���δ�.
//
//	<< NewElement : ���� �����Ǵ� ��尡 ���� ��
//
//	>> CNode<T>* : ���� ������ ���
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::AddTail( T NewElement)
{
	CNode<T>* pOne = new CNode<T>;

	if ( pOne == NULL)
	{	// �޸� �Ҵ��� �����ϸ�
		return ( NULL);
	}

	pOne->SetData( NewElement);

	// ���ο� ����� �տ� ���� �� ����
	pOne->SetPrev( m_pTail->GetPrev());
	( m_pTail->GetPrev())->SetNext( pOne);
	// ���ο� ����� �ڿ� ���Ϸ� ���̱�
	pOne->SetNext( m_pTail);
	m_pTail->SetPrev( pOne);

	m_lCount++;

	return ( pOne);
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	InsertBefore - ���ο� ���� ������ ��带 �����ؼ� pNode �տ� ���� �ִ´�.	; not tested
//
//	<< pNode : ���ο� ��� �ڿ� ���� ���		NewElement : ���� �����Ǵ� ��尡 ���� ��
//
//	>> CNode<T>* : ���� ������ ���
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::InsertBefore( CNode<T>* pNode, T NewElement)
{
	CNode<T>* pOne = new CNode<T>;

	if ( pOne == NULL)
	{	// �޸� �Ҵ��� �����ϸ�
		return ( NULL);
	}

	pOne->SetData( NewElement);

	// ���ο� ��� �տ� ���� ���� ����
	pOne->SetPrev( pNode->GetPrev());
	( pNode->GetPrev())->SetNext( pOne);
	// ���ο� ��� �ڿ� pNode ���̱�
	pOne->SetNext( pNode);
	pNode->SetPrev( pOne);

	m_lCount++;

	return ( pOne);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	InsertAfter - ���ο� ���� ������ ��带 �����ؼ� pNode �ڿ� ���� �ִ´�.	; not tested
//
//	<< pNode : ���ο� ��� �տ� ���� ���		NewElement : ���� �����Ǵ� ��尡 ���� ��
//
//	>> CNode<T>* : ���� ������ ���
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::InsertAfter( CNode<T>* pNode, T NewElement)
{
	CNode<T>* pOne = new CNode<T>;

	if ( pOne == NULL)
	{	// �޸� �Ҵ��� �����ϸ�
		return ( NULL);
	}

	pOne->SetData( NewElement);

	// ���ο� ��� �ڿ� ���� ���� ����
	pOne->SetNext( pNode->GetNext());
	( pNode->GetNext())->SetPrev( pOne);
	// ���ο� ��� �տ� pNode ���̱�
	pOne->SetPrev( pNode);
	pNode->SetNext( pOne);

	m_lCount++;

	return ( pOne);
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	RemoveHead - Head ��带 �����Ѵ�.	; not tested
//
//	>> T : Head ��忡 �ִ� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T CList<T>::RemoveHead( void)
{
	CNode<T>* pOne = m_pHead->GetNext();
	
	if ( pOne == m_pTail)
	{	// ����Ʈ�� ������� ������.
		T NullData;	// NULL ���Ͽ� �ʿ��� ��
		memset( &NullData, 0, sizeof( T));

		return ( NullData);
	}

	// Head�� �ִ� �� ����
	T Data = pOne->GetData();

	// ����� �ڿ� Head�� ���� ���� ���̰� ����
	( pOne->GetNext())->SetPrev( m_pHead);
	m_pHead->SetNext( pOne->GetNext());
	
	// ��� ����
	delete pOne;

	m_lCount--;

	return ( Data);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	RemoveTail - Tail ��带 �����Ѵ�.
//
//	>> T : Tail ��忡 �ִ� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T CList<T>::RemoveTail( void)
{
	CNode<T>* pOne = m_pTail->GetPrev();
	
	if ( pOne == m_pHead)
	{	// ����Ʈ�� ������� ������.
		T NullData;	// NULL ���Ͽ� �ʿ��� ��
		memset( &NullData, 0, sizeof( T));

		return ( NullData);
	}

	// Tail�� �ִ� �� ����
	T Data = pOne->GetData();

	// ���Ϸ��� �տ� Tail�� ���� ���� ���̰� ����
	( pOne->GetPrev())->SetNext( m_pTail);
	m_pTail->SetPrev( pOne->GetPrev());
	
	// ��� ����
	delete pOne;

	m_lCount--;

	return ( Data);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	RemoveNode - �ش� ��带 �����Ѵ�.	; not tested
//
//	<< &pNode : ������ ��� ( �� �����ʹ� ��尡 ���ŵ� ��, �� �ڿ� �پ��� ��带 ����Ų��.)
//
//	>> T : ��忡 �ִ� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T CList<T>::RemoveNode( CNode<T>* &pNode)
{
	if ( pNode == NULL)
	{
		T NullData;	// NULL ���Ͽ� �ʿ��� ��
		memset( &NullData, 0, sizeof( T));

		return ( NullData);
	}

	T Data = pNode->GetData();
	CNode<T>* pNextNode = pNode->GetNext();

	// pNode�� �� �� ��� ����
	( pNode->GetPrev())->SetNext( pNextNode);
	pNextNode->SetPrev( pNode->GetPrev());

	// pNode�� �����ϰ� �� �ڿ� ����� ���� ������ �Ѵ�.
	delete pNode;
	pNode = ( pNextNode != m_pTail) ? pNextNode : NULL;

	m_lCount--;

	return ( Data);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	RemoveAll - ��� ��带 �����Ѵ�.
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
void CList<T>::RemoveAll( void)
{
	// ���Ϸ��������� ��ũ�� ����
	( m_pTail->GetPrev())->SetNext( NULL);

	// Head ���� ������ ����
	CNode<T> *pToSeek, *pToDelete;

	pToDelete = pToSeek = m_pHead->GetNext();
	while ( pToSeek)
	{
		pToSeek = pToSeek->GetNext();
		delete pToDelete;
		pToDelete = pToSeek;
	}

	// ����� ���Ϸ� ���� ( ����� ���Ϸ��� ���ŵ��� �ʴ´�.)
	m_pHead->SetNext( m_pTail);
	m_pTail->SetPrev( m_pHead);

	m_lCount = 0;
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	FindHead - Head ��带 ��´�.
//
//	>> CNode<T>* : Head ����� ������
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::FindHead( void)
{
	if ( IsEmpty())
	{
		return ( NULL);
	}
	else
	{
		return ( m_pHead->GetNext());
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	FindTail - Tail ��带 ��´�.	; not tested
//
//	>> CNode<T>* : Tail ����� ������
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::FindTail( void)
{
	if( IsEmpty())
	{
		return ( NULL);
	}
	else
	{
		return ( m_pTail->GetPrev());
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	FindNode - Ư������ ������ �ִ� ��带 ã�´�.	; not tested
//
//	<< SearchValue : ã�� ���� ��尡 ������ �ִ� ��
//
//	>> CNode<T>* : �߰��� ����� ������
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::FindNode( T SearchValue)
{
	// ���Ϸ��������� ��ũ ����
	( m_pTail->GetPrev())->SetNext( NULL);

	// Head���� �˻�
	CNode<T> *pToSeek = m_pHead->GetNext();

	while( pToSeek)
	{
		if ( pToSeek->GetData() == SearchValue)
		{
			// ���Ϸ��������� ��ũ ����
			( m_pTail->GetPrev())->SetNext( m_pTail);
			return ( pToSeek);
		}

		pToSeek = pToSeek->GetNext();
	}

	// ���Ϸ��������� ��ũ ����
	( m_pTail->GetPrev())->SetNext( m_pTail);

	// ã�� ���� ��� NULL ����
	return ( NULL);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	GetPrev - ����� �տ� �ִ� ��带 ��´�.
//
//	<< pNode : ���� ���
//
//	>> CNode<T>* : ���� ����� �� ���. ������ NULL
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::GetPrev( CNode<T>* pNode)
{
	if ( m_pHead == pNode->GetPrev())
	{	// ����� ��츦 �����ؼ� ���� ��尡 ���� ������ ó��
		return ( NULL);
	}
	else
	{
		return ( pNode->GetPrev());
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	GetNext - ����� �ڿ� �ִ� ��带 ��´�.
//
//	<< pNode : ���� ���
//
//	>> CNode<T>* : ���� ����� �ڿ� �ִ� ���. ������ NULL
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CNode<T>* CList<T>::GetNext( CNode<T>* pNode)
{
	if ( m_pTail == ( pNode->GetNext()))
	{	// ���Ϸ��� ��츦 �����ؼ� ���� ��尡 ���� ������ ó��
		return ( NULL);
	}
	else
	{
		return ( pNode->GetNext());
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	SetData - ����� ���� �����Ѵ�.
//
//	<< pNode : ������ ����� ������		Data : ���� ���Ե� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
void CList<T>::SetData( CNode<T>* pNode, T Data)
{
	pNode->SetData( Data);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	GetData - ��尡 ������ �ִ� ���� ��´�. ( �������̹Ƿ� ���� Ŭ������ ��� ��� �Լ� �̿� ����)
//
//	<< pNode : ���� ����� �ϴ� ����� ������	T& : ��尡 ������ �ִ� ���� ������
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T& CList<T>::GetData( CNode<T>* pNode)
{
	if ( m_pHead == pNode || m_pTail == pNode)
	{
		T NullData;	// NULL ���Ͽ� �ʿ��� ��
		memset( &NullData, 0, sizeof( T));

		return ( NullData);
	}
	else
	{
		return ( pNode->GetData());
	}
}


//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CQueue template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//

template <class T>
class CQueue : private CList<T>
{
	public:
		CQueue();
		~CQueue();

		BOOL Insert( T NewElement);
		T Remove( void);
		void CleanUp( void);

		BOOL Find( T Element);

		LONG GetCount( void)	{ return ( CList<T>::GetCount()); }	// Stack �ȿ� ����ִ� Node ������ ��´�.
};



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Constructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CQueue<T>::CQueue() : CList<T>()
{
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Destructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CQueue<T>::~CQueue()
{
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Insert - ť�� ���ο� ���� �ִ´�.	; not tested
//
//	<< NewElement : ť�� �־��� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
BOOL CQueue<T>::Insert( T NewElement)
{
	if ( NULL == AddTail( NewElement))
	{	// �����ϸ�
		return ( FALSE);
	}

	return ( TRUE);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Remove - ť�� ����ִ� ���� ������. ( ť�� ������� NULL�� �����Ѵ�.)	; not tested
//
//	>> T : ť���� ������ ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T CQueue<T>::Remove( void)
{
	return( RemoveHead());
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	CleanUp - ť�� ����.	; not tested
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
void CQueue<T>::CleanUp( void)
{
	RemoveAll();
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Find - ť�� �ش��ϴ� ���� ����ִ��� �˻��Ѵ�.	; not tested
//
//	<< Element : �˻��� ��
//
//	>> BOOL : ť�� ���� ����ִ��� ����
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
BOOL CQueue<T>::Find( T Element)
{
	if ( NULL == FindNode( Element))
	{	// ã�� ���ϸ�
		return ( FALSE);
	}

	return ( TRUE);
}


//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CStack template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//

/*template <class T>
class CStack : private CList<T>
{
	public:
		CStack();
		~CStack();

		BOOL Push(T NewElement);
		T Pop(void);
		void CleanUp( void);

		BOOL Find( T Element);

		LONG GetCount( void)	{ return ( m_lCount); }	// Stack �ȿ� ����ִ� Node ������ ��´�.
};



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Constructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CStack<T>::CStack() : CList()
{
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Destructor
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
CStack<T>::~CStack()
{
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Push - ���ÿ� ���ο� ���� �ִ´�.	; not tested
//
//	<< NewElement : ���ÿ� �־��� ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
BOOL CStack<T>::Push( T NewElement)
{
	if ( NULL == AddTail( T))
	{	// �����ϸ�
		return ( FALSE);
	}

	return ( TRUE);
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Pop - ���ÿ� ����ִ� ���� ������. ( ������ ������� NULL�� �����Ѵ�.)	; not tested
//
//	>> T : ���ÿ��� ������ ��
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
T CStack<T>::Pop( void)
{
	return( RemoveTail());
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	CleanUp - ������ ����.	; not tested
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
void CStack<T>::CleanUp( void)
{
	RemoveAll();
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//	Find - ���ÿ� �ش��ϴ� ���� ����ִ��� �˻��Ѵ�.	; not tested
//
//	<< Element : �˻��� ��
//
//	>> BOOL : ���ÿ� ���� ����ִ��� ����
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
template <class T>
BOOL CStack<T>::Find( T Element)
{
	if ( NULL == FindNode( Element))
	{	// ã�� ���ϸ�
		return ( FALSE);
	}

	return ( TRUE);
}
*/


//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CBNode template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//


template <class T, class S> class CBTree;	// ���� ���� - CBNode���� ����ϱ� ����

template <class T, class S>
class CBNode
{
	protected:
		T m_Data;	// �⺻ ������
		S m_CompValue;	// �񱳽ÿ� ����ϴ� ��
		CBNode<T, S>* m_pLeft;		// ���� �ڽ� ���
		CBNode<T, S>* m_pRight;	// ������ �ڽ� ���
		CBNode<T, S>* m_pParent;

		void SetLeft( CBNode<T, S>* pLeft)	{ m_pLeft = pLeft; pLeft->m_pParent = this; }
		void SetRight( CBNode<T, S>* pRight) { m_pRight = pRight; pRight->m_pParent = this;  }
		CBNode<T, S>* GetLeft( void)	{ return ( m_pLeft); }
		CBNode<T, S>* GetRight( void)	{ return ( m_pRight); }
		CBNode<T, S>* GetParent( void)	{ return ( m_pParent); }

		friend class CBTree<T, S>;
		friend CBTree<T, S>& operator + ( const CBTree<T, S>& Value1, const CBTree<T, S>& Value2);

	public:

		CBNode();
		CBNode( T Data, S CompValue);
		~CBNode();

		// ������ ó��
		void SetData( T Data)	{ m_Data = Data; }
		void SetValue( S CompValue)	{ m_CompValue = CompValue; }
		T& GetData( void)		{ return ( m_Data);	}
		S GetValue( void)	{ return ( m_CompValue); }
};


template <class T, class S>
CBNode<T, S>::CBNode()
{
	m_pLeft = m_pRight = m_pParent = NULL;
}

template <class T, class S>
CBNode<T, S>::CBNode( T Data, S CompValue)
{
	m_pLeft = m_pRight = m_pParent = NULL;
	m_Data = Data;
	m_CompValue = CompValue;
}

template <class T, class S>
CBNode<T, S>::~CBNode()
{
}


//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//								CBTree template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//

template <class T, class S>		// S �� < ������ �ִ� ���̾�� �Ѵ�.
class CBTree
{
	protected:
		long m_lCount;	// List �ȿ� ����ִ� Node ����
		CBNode<T, S>* m_pHead;	// Head ���

		void RemoveFrom( CBNode<T, S>* pNode);	// ���� �� �� ����
		void CycleFrom( CBNode<T, S>* pNode, DWORD dwParam);
		void ( *m_Process)( T Data, S CompValue, DWORD dwParam);

	public:
		CBTree();	// Constructor
		CBTree( const CBTree<T, S>& RValue);	// ���� ����Ʈ����
		~CBTree();	// Destructor

		// ������ �����ε�
		CBTree<T, S>& operator = ( const CBTree<T, S>& RValue);
		friend CBTree<T, S>& operator + ( const CBTree<T, S>& Value1, const CBTree<T, S>& Value2);


		// �Ϲ� �Լ�
		CBNode<T, S>* Add( T NewElement, S CompValue);	// �߰�
		T RemoveNode( CBNode<T, S>* &pNode);	// ��带 ã�Ƽ� ����
		void RemoveAll( void);	// ���� ����

		BOOL IsEmpty( void)	{ return ( m_lCount == 0); }	// ����Ʈ�� ����ִ��� üũ
		virtual LONG GetCount( void)	{ return ( m_lCount); }	// List �ȿ� ����ִ� Node ������ ��´�.

		//CBNode<T, S>* FindNode( T SearchValue);	// SearchValue�� Data�� ���� �ִ� ��� ã��
		CBNode<T, S>* FindNode( S CompValue);	// Value�� ���� �ִ� ��� ã��

		CBNode<T, S>* FindHead( void);
		CBNode<T, S>* GetLeft( CBNode<T, S>* pNode);
		CBNode<T, S>* GetRight( CBNode<T, S>* pNode);
		CBNode<T, S>* GetParent( CBNode<T, S>* pNode);

		void SetData( CBNode<T, S>* pNode, T Data);
		T& GetData( CBNode<T, S>* pNode);
		S GetValue( CBNode<T, S>* pNode);

		void Cycle( void ( *Process)( T Data, S CompValue, DWORD dwParam), DWORD dwParam);

	protected:
		void CopyFrom( CBNode<T, S>* pNode);	// �ش� ��忡�������� ������ ���� Ʈ���� �߰���Ų��.
		void UnlinkOneBottomNode( CBNode<T, S>* &pNode);

	public:
		BOOL Optimize( void);
	protected:
		BOOL GetOptimizeList( T *pData, S *pCompValue);
		void AddDataByOptimization( T *pData, S *pCompValue, int nLeft, int nRight);
};


template <class T, class S>
CBTree<T, S>::CBTree()
{
	// ��� ���� �ʱ�ȭ
	m_lCount = 0;
	m_pHead = NULL;
}

template <class T, class S>
CBTree<T, S>::CBTree( const CBTree<T, S>& RValue)
{
	// ��� ���� �ʱ�ȭ
	m_lCount = 0;
	m_pHead = NULL;

	// ����
	if ( RValue.m_pHead)
	{
		CopyFrom( RValue.m_pHead);
	}
}

template <class T, class S>
CBTree<T, S>::~CBTree()
{
	RemoveAll();
}

template <class T, class S>
CBTree<T, S>& CBTree<T, S>::operator = ( const CBTree<T, S>& RValue)
{
	if ( &RValue == this)
	{
		return ( *this);
	}

	RemoveAll();
	if ( RValue.m_pHead)
	{
		CopyFrom( RValue.m_pHead);
	}

	return ( *this);
}

template <class T, class S>
CBTree<T, S>& operator + ( const CBTree<T, S>& Value1, const CBTree<T, S>& Value2)
{	// ���� �� ��
	CBTree<T, S> Result;
	CBTree<T, S> Left;
	CBTree<T, S> Right;
	if ( Value1.m_pHead->GetValue() <= Value2.m_pHead->GetValue())
	{
		Left = Value1;
		Right = Value2;
	}
	else
	{
		Left = Value2;
		Right = Value1;
	}

	// �Ӹ� ����
	T NullData;
	memset( &NullData, 0, sizeof( T));
	S CompValue = 0;
	if ( Left.m_pHead != NULL && Right.m_pHead != NULL)
	{
		CompValue = ( Left.m_pHead->GetValue() + Left.m_pHead->GetValue() + 1) / 2;
	}
	Result.Add( NullData, CompValue);

	// �� �� ����
	Result.m_pHead->SetLeft( Left.m_pHead);
	Result.m_pHead->SetRight( Right.m_pHead);
	Result.m_lCount = Left.m_lCount + Right.m_lCount + 1;

	// ������ ���ŵ��� �ʰ� �Ϸ��� �� �۾��� �ʿ��ϴ�.
	Left.m_pHead = NULL;
	Right.m_pHead = NULL;

	return ( CBTree<T, S>( Result));
}


template <class T, class S>
void CBTree<T, S>::CopyFrom( CBNode<T, S>* pNode)
{
	Add( pNode->GetData(), pNode->GetValue());
	if ( pNode->GetLeft())
	{
		CopyFrom( pNode->GetLeft());
	}
	if ( pNode->GetLeft())
	{
		CopyFrom( pNode->GetRight());
	}
}


template <class T, class S>
CBNode<T, S>* CBTree<T, S>::Add( T NewElement, S CompValue)
{
	if ( m_pHead == NULL)
	{	// �Ӹ��� �߰�
		m_lCount++;
		m_pHead = new CBNode<T, S>( NewElement, CompValue);

		return ( m_pHead);
	}

	CBNode<T, S>* pNode = m_pHead;
	CBNode<T, S>* pPrev = m_pHead;
	while( pNode != NULL)
	{
		if ( CompValue < pNode->GetValue())
		{
			pPrev = pNode;
			pNode = pNode->GetLeft();
		}
		else
		{
			pPrev = pNode;
			pNode = pNode->GetRight();
		}
	}

	if ( pNode == NULL)
	{	// �߰�
		m_lCount++;
		CBNode<T, S>* pOne = new CBNode<T, S>( NewElement, CompValue);

		if ( CompValue < pPrev->GetValue())
		{	// ����
			pPrev->SetLeft( pOne);
		}
		else
		{
			pPrev->SetRight( pOne);
		}

		return ( pOne);
	}
	else
	{	// ���� �����Ƿ�
		return ( pNode);
	}
}

template <class T, class S>
T CBTree<T, S>::RemoveNode( CBNode<T, S>* &pNode)
{	// ��� ���Ŵ� Ʈ�� ���� ���� �� �� ���� ( ������ )
	// ��� �� ��� ����
	T ResultData = pNode->GetData();

	// Ʈ�� ���� ������
	// ���� �ڽ��� ���� �����ʿ� �ִ� �ų� ������ �ڽ��� ���� ���ʿ� �ִ� �ɷ� �ٲ۴�.

	// 1. ��ü�� ���� ��´�.
	CBNode<T, S> *pOld = NULL;

	CBNode<T, S> *pSeek = pNode->GetLeft();
	if ( pSeek)
	{
		if ( !pNode->GetRight())
		{	// ���ʸ� ���� ���
			if ( pNode == m_pHead)
			{
				m_pHead = pSeek;
				m_pHead->m_pParent = NULL;
			}
			else
			{
				if ( pNode == pNode->GetParent()->m_pRight)
				{
					pNode->GetParent()->SetRight( pSeek);
				}
				else
				{
					pNode->GetParent()->SetLeft( pSeek);
				}
			}
			delete pNode;
			m_lCount--;
			return ( ResultData);
		}
		// �� �� ���� ���
		pOld = pSeek;
		while ( pSeek)
		{
			pOld = pSeek;
			pSeek = pSeek->GetRight();
		}

		// 2. �� ���� �����Ѵ�.
		T Data = pOld->m_Data;
		S CompValue = pOld->m_CompValue;
		//UnlinkOneBottomNode( pOld);
		RemoveNode( pOld);

		// 3. ���ַ��� ���� ���ο� ���� �־��ش�.
		pNode->m_Data = Data;
		pNode->m_CompValue = CompValue;

		return ( ResultData);
	}
	else
	{
		pSeek = pNode->GetRight();
		if ( pSeek)
		{	// �����ʸ� ���� ���
			if ( pNode == m_pHead)
			{
				m_pHead = pSeek;
				m_pHead->m_pParent = NULL;
			}
			else
			{
				if ( pNode == pNode->GetParent()->m_pRight)
				{
					pNode->GetParent()->SetRight( pSeek);
				}
				else
				{
					pNode->GetParent()->SetLeft( pSeek);
				}
			}
			delete pNode;
			m_lCount--;
			return ( ResultData);
		}
	}

	// �Ѵ� ���� ���
	UnlinkOneBottomNode( pNode);
	return ( ResultData);
}

template <class T, class S>
void CBTree<T, S>::UnlinkOneBottomNode( CBNode<T, S>* &pNode)
{
	if ( pNode->GetParent())
	{
		if ( pNode->GetParent()->GetLeft() == pNode)
		{
			pNode->GetParent()->m_pLeft = NULL;
		}
		else
		{
			pNode->GetParent()->m_pRight = NULL;
		}
	}
	else
	{
		m_pHead = NULL;
	}

	// ����
	m_lCount--;
	delete pNode;
	pNode = NULL;
}

template <class T, class S>
void CBTree<T, S>::RemoveAll( void)
{
	if ( m_pHead != NULL)
	{
		RemoveFrom( m_pHead);
		m_pHead = NULL;
	}
	m_lCount = 0;
}

template <class T, class S>
void CBTree<T, S>::RemoveFrom( CBNode<T, S>* pNode)
{
	if ( pNode->GetLeft() != NULL)
	{
		RemoveFrom( pNode->GetLeft());
	}

	if ( pNode->GetRight() != NULL)
	{
		RemoveFrom( pNode->GetRight());
	}

	RemoveNode( pNode);
}


template <class T, class S>
CBNode<T, S>* CBTree<T, S>::FindNode( S CompValue)
{
	CBNode<T, S>* pNode = m_pHead;
	while( pNode != NULL && pNode->GetValue() != CompValue)
	{
		if ( CompValue < pNode->GetValue())
		{
			pNode = pNode->GetLeft();
		}
		else
		{
			pNode = pNode->GetRight();
		}
	}

	return ( pNode);
}

template <class T, class S>
CBNode<T, S>* CBTree<T, S>::FindHead( void)
{
	return ( m_pHead);
}

template <class T, class S>
CBNode<T, S>* CBTree<T, S>::GetLeft( CBNode<T, S>* pNode)
{
	return ( pNode->GetLeft());
}

template <class T, class S>
CBNode<T, S>* CBTree<T, S>::GetRight( CBNode<T, S>* pNode)
{
	return ( pNode->GetRight());
}

template <class T, class S>
CBNode<T, S>* GetParent( CBNode<T, S>* pNode)
{
	return ( pNode->GetParent());
}

template <class T, class S>
void CBTree<T, S>::SetData( CBNode<T, S>* pNode, T Data)
{
	pNode->SetData( Data);
}

template <class T, class S>
T& CBTree<T, S>::GetData( CBNode<T, S>* pNode)
{
	return ( pNode->GetData());
}

template <class T, class S>
S CBTree<T, S>::GetValue( CBNode<T, S>* pNode)
{
	return ( pNode->GetValue());
}

template <class T, class S>
void CBTree<T, S>::Cycle( void ( *Process)( T Data, S CompValue, DWORD dwParam), DWORD dwParam)
{
	m_Process = Process;

	if ( m_pHead == NULL)
	{
		return;
	}

	if ( m_pHead->GetLeft() != NULL)
	{
		CycleFrom( m_pHead->GetLeft(), dwParam);
	}

	( *m_Process)( m_pHead->GetData(), m_pHead->GetValue(), dwParam);

	if ( m_pHead->GetRight() != NULL)
	{
		CycleFrom( m_pHead->GetRight(), dwParam);
	}
}

template <class T, class S>
void CBTree<T, S>::CycleFrom( CBNode<T, S>* pNode, DWORD dwParam)
{
	if ( pNode->GetLeft() != NULL)
	{
		CycleFrom( pNode->GetLeft(), dwParam);
	}

	( *m_Process)( pNode->GetData(), pNode->GetValue(), dwParam);

	if ( pNode->GetRight() != NULL)
	{
		CycleFrom( pNode->GetRight(), dwParam);
	}
}

template <class T, class S>
BOOL CBTree<T, S>::Optimize( void)
{
	T *pData = new T[GetCount()];
	S *pCompValue = new S[GetCount()];
	if ( !GetOptimizeList( pData, pCompValue))
	{
		delete [] pCompValue;
		delete [] pData;
		return ( FALSE);
	}

	long lCount = GetCount();
	RemoveAll();
	AddDataByOptimization( pData, pCompValue, 0, lCount);
	delete [] pCompValue;
	delete [] pData;

	return ( TRUE);
}

template <class T, class S>
void ProcessGetOptimizeList( T Data, S CompValue, DWORD dwParam)
{
	DWORD *pdwParam = ( DWORD *)dwParam;
	long *pCount = ( long*)pdwParam[0];
	T *pData = ( T *)pdwParam[1];
	S *pCompValue = ( S *)pdwParam[2];
	pData[*pCount] = Data;
	pCompValue[( *pCount)++] = CompValue;
}

template <class T, class S>
BOOL CBTree<T, S>::GetOptimizeList( T *pData, S *pCompValue)
{
	long lOptimizeCount = 0;
	DWORD dwOptimizeData[3] = { ( DWORD)&lOptimizeCount, ( DWORD)pData, ( DWORD)pCompValue};
	Cycle( ProcessGetOptimizeList, ( DWORD)dwOptimizeData);
	if ( GetCount() != lOptimizeCount)
	{
		return ( FALSE);
	}

	return ( TRUE);
}

template <class T, class S>
void CBTree<T, S>::AddDataByOptimization( T *pData, S *pCompValue, int nLeft, int nRight)
{
	if ( nLeft == nRight)
	{
		return;
	}

	Add( pData[( nLeft + nRight) / 2], pCompValue[( nLeft + nRight) / 2]);

	AddDataByOptimization( pData, pCompValue, nLeft, ( nLeft + nRight) / 2);
	AddDataByOptimization( pData, pCompValue, ( nLeft + nRight) / 2 + 1, nRight);
}


//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//
//									CList template class
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
//___________________________________________________________________________________________//
// ũ�Ⱑ �����Ӱ� �þ�� �迭

template <class T>
class CDimension
{
	protected:
		int m_nSize;
		T *m_pData;

	public:
		CDimension();	// Constructor
		~CDimension();	// Destructor

		T Set( int nIndex, T Data);
		T Get( int nIndex);

	protected:
		void CheckDimensionSize( int nIndex);
};


template <class T>
CDimension<T>::CDimension()
{
	m_nSize = 16;
	m_pData = new T [m_nSize];
}

template <class T>
CDimension<T>::~CDimension()
{
	delete [] m_pData;
}

template <class T>
T CDimension<T>::Set( int nIndex, T Data)
{
	CheckDimensionSize( nIndex);
	m_pData[nIndex] = Data;

	return ( Data);
}

template <class T>
T CDimension<T>::Get( int nIndex)
{
	CheckDimensionSize( nIndex);
	return ( m_pData[nIndex]);
}

template <class T>
void CDimension<T>::CheckDimensionSize( int nIndex)
{
	if ( nIndex >= m_nSize)
	{	// �������� ũ�⸦ �÷��ش�.
		for ( int nNewSize = m_nSize; nNewSize <= nIndex; nNewSize *= 2)
		{
		}

		// ũ�⸦ �ø� ���� ����
		T *pTempBuffer = new T [m_nSize];
		memcpy( pTempBuffer, m_pData, m_nSize * sizeof ( T));
		delete [] m_pData;
		m_pData = new T [nNewSize];
		memcpy( m_pData, pTempBuffer, m_nSize * sizeof ( T));
		m_nSize = nNewSize;
		delete [] pTempBuffer;
	}
}


# endif //__BASE_CLASSES_H__


/*-*-*-*                    End of Code                      *-*-*-*/
