// NPGameGuardHandle.h: interface for the CNPGameGuardHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPGAMEGUARDHANDLE_H__B48EB0DA_BD1E_4DF7_82BC_62989273759B__INCLUDED_)
#define AFX_NPGAMEGUARDHANDLE_H__B48EB0DA_BD1E_4DF7_82BC_62989273759B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef PBG_MOD_GAMEGUARD_HANDLE
class CNPGameGuardHandle  
{
	enum {
		MAX_TEXT = 50,
	};
public:
	CNPGameGuardHandle();
	virtual ~CNPGameGuardHandle();

	static CNPGameGuardHandle* GetInstance();

	// ĳ���� ��������
	void SetCharacterInfo(char* _Name, char* _Hack);
	char* GetCharacterName();
	char* GetCharacterHack();

	// ���� ��뿩��
	void SetNPHack(BOOL _IsHack);
	BOOL IsNPHack();

	// Ÿ��üũ
	bool CheckTime();
	// �ٹ߰�����(ĳ������â����) ����������
	bool CheckDestroyWin();
	// �޽��� �ڽ�����
	void SetDestroyMsg(bool _bDestroyMsg);
	BOOL GetDestroyMsg();
	// ���Ӱ��� �����޽��� �ε��� ����
	void SetErrorMsgIndex(DWORD _nMsgIndex);
	DWORD GetErrorMsgIndex();
private:
	const int m_iTime;
	int m_nRandTime;
	DWORD m_dwNPGameCurrTime;
	BOOL m_bHack;
	BOOL m_bDestroyMsg;
	int m_nStandardTime;
	DWORD m_dwErrorMsgIndex;

	char m_szCharName[MAX_TEXT];
	char m_szHackName[MAX_TEXT];

	void Init();
	void Destroy();
};

#define g_NPGameGuardHandle	CNPGameGuardHandle::GetInstance()

#endif //PBG_MOD_GAMEGUARD_HANDLE
#endif // !defined(AFX_NPGAMEGUARDHANDLE_H__B48EB0DA_BD1E_4DF7_82BC_62989273759B__INCLUDED_)
