// ChangeRingManager.h: interface for the CChangeRingManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANGERINGMANAGER_H__ABB6CFCF_B65B_48BB_B54B_73685EE2E30A__INCLUDED_)
#define AFX_CHANGERINGMANAGER_H__ABB6CFCF_B65B_48BB_B54B_73685EE2E30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChangeRingManager  
{
public:
	CChangeRingManager();
	virtual ~CChangeRingManager();
	static CChangeRingManager* GetInstance() { static CChangeRingManager s_Instance; return &s_Instance; }
	
	// ���Ź��� �� ����Ÿ �ε��ϴ� �Լ�
	void LoadItemModel();

	// ���Ź��� �� �ؽ��� �ε��ϴ� �Լ�
	void LoadItemTexture();

	// ��ũ�ε� �Ӹ� �Ⱥ��̰� ����ó�� ���ִ� �Լ�
	bool CheckDarkLordHair(int iType);

	// ���˻� ���� �Ⱥ��̰� ����ó�� ���ִ� �Լ�
	bool CheckDarkCloak(int iClass, int iType);

	// ĭ����3���� ������ ����ó��
	bool CheckChangeRing(short RingType);

	// �����ȵǰ� ����ó��
	bool CheckRepair(int iType);

	// ���Ź��� �����ϸ� �̵����ϴ� �� ������ ����ó�� ���ִ� �Լ�
	bool CheckMoveMap(short sLeftRingType, short sRightRingType);
	
	// ���Ź��� ����� ��ī�罺�� �̵����ϰ� �ϴ� �Լ� (��ī�罺�� �ش�)
#ifdef KJH_FIX_MOVE_ICARUS_EQUIPED_PANDA_CHANGE_RING
	bool CheckBanMoveIcarusMap(short sLeftRingType, short sRightRingType);
#endif // KJH_FIX_MOVE_ICARUS_EQUIPED_PANDA_CHANGE_RING

};

#define g_ChangeRingMgr CChangeRingManager::GetInstance()

#endif // !defined(AFX_CHANGERINGMANAGER_H__ABB6CFCF_B65B_48BB_B54B_73685EE2E30A__INCLUDED_)
