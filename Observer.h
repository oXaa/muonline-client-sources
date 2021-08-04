//*****************************************************************************
// File: Observer.h
//
// Desc: interface for the CObserver, CSubject class.
//		 ������, ������Ʈ Ŭ����.(������ ����)
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#if !defined(AFX_OBSERVER_H__D77AB996_491E_44AD_AE54_179DE70DFC3B__INCLUDED_)
#define AFX_OBSERVER_H__D77AB996_491E_44AD_AE54_179DE70DFC3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*****************************************************************************
// CObserver
// ��ť��Ʈ/�� ������ ���� �����ϸ� ��.
//*****************************************************************************

class CSubject;

class CObserver  
{
public:
	virtual ~CObserver();

	// CSubject::Notify()���� UpdateData()�� ȣ��.
	virtual void UpdateData(CSubject* pChangedSubject) = 0;

protected:
	CObserver();
};


//*****************************************************************************
// CSubject
// ��ť��Ʈ/�� ������ ��ť��Ʈ��� �����ϸ� ��.
//*****************************************************************************

#include "PList.h"

class CSubject  
{
public:
	virtual ~CSubject();

	virtual void Attach(CObserver* pObserver);
	virtual void Detach(CObserver* pObserver);
	virtual void Notify();

protected:
	CSubject();

private:
	CPList m_ObserverList;	// ������ Ŭ���� ��ӹ��� ������Ʈ���� ������ ����Ʈ.
};

#endif // !defined(AFX_OBSERVER_H__D77AB996_491E_44AD_AE54_179DE70DFC3B__INCLUDED_)
