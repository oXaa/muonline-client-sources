// Event.h: interface for the CEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__8075B067_D2AB_48AC_8A39_370D3B3DD089__INCLUDED_)
#define AFX_EVENT_H__8075B067_D2AB_48AC_8A39_370D3B3DD089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ������ �̺�Ʈ ���� Ŭ������ �̰����ٰ� �����Ѵ�.

#define XMAS_EVENT_TIME		60000	// 3���� ĳ���� ���� �ִ� �ð�(1��)

class CXmasEvent
{
public:
	CXmasEvent(void);
	~CXmasEvent(void);
	
	static CXmasEvent* GetInstance() { static CXmasEvent s_Instance; return &s_Instance; }

	void LoadXmasEvent();
	void LoadXmasEventEffect();
	void LoadXmasEventItem();
	void LoadXmasEventSound();

	void CreateXmasEventEffect(CHARACTER* pCha, OBJECT *pObj, int iType);

	void GenID();

public:
	int m_iEffectID;
};

#define g_XmasEvent	CXmasEvent::GetInstance()

class CNewYearsDayEvent
{
public:
	CNewYearsDayEvent();
	~CNewYearsDayEvent();

	static CNewYearsDayEvent* GetInstance() { static CNewYearsDayEvent s_Instance; return &s_Instance; }

	void LoadModel();
	void LoadSound();

	CHARACTER* CreateMonster(int iType, int iPosX, int iPosY, int iKey);
	bool MoveMonsterVisual(CHARACTER* c,OBJECT* o, BMD* b);
};

#define g_NewYearsDayEvent	CNewYearsDayEvent::GetInstance()

#ifdef CSK_FIX_BLUELUCKYBAG_MOVECOMMAND
class CBlueLuckyBagEvent
{
public:
	CBlueLuckyBagEvent();
	virtual ~CBlueLuckyBagEvent();
	static CBlueLuckyBagEvent* GetInstance() { static CBlueLuckyBagEvent s_Instance; return &s_Instance; }

	// �Ķ����ָӴ� ����
	void StartBlueLuckyBag();
	
	void CheckTime();

	// �Ķ����ָӴ� �����ϰ��� 10�о��ΰ�?
	bool IsEnableBlueLuckyBag();

private:
	bool m_bBlueLuckyBag;
	DWORD m_dwBlueLuckyBagTime;		// �Ķ����ָӴ� �԰� ���� 10�а� ������ �ð� ����
	static const DWORD m_dwBlueLuckyBagCheckTime;
};

#define g_pBlueLuckyBagEvent	CBlueLuckyBagEvent::GetInstance()

#endif // CSK_FIX_BLUELUCKYBAG_MOVECOMMAND

#ifdef KJH_ADD_09SUMMER_EVENT
class C09SummerEvent
{
public:
	C09SummerEvent();
	~C09SummerEvent();

	static C09SummerEvent* GetInstance() { static C09SummerEvent s_Instance; return &s_Instance; }

	void LoadModel();
	void LoadSound();
	
	CHARACTER* CreateMonster(int iType, int iPosX, int iPosY, int iKey);
	bool MoveMonsterVisual(CHARACTER* c,OBJECT* o, BMD* b);
};

#define g_09SummerEvent		C09SummerEvent::GetInstance()
#endif // KJH_ADD_09SUMMER_EVENT


#endif // !defined(AFX_EVENT_H__8075B067_D2AB_48AC_8A39_370D3B3DD089__INCLUDED_)
