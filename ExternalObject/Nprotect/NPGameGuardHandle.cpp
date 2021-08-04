// NPGameGuardHandle.cpp: implementation of the CNPGameGuardHandle class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#ifdef PBG_MOD_GAMEGUARD_HANDLE
#include "NPGameGuardHandle.h"
#include "npGameGuard.h"
#include "wsclientinline.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNPGameGuardHandle::CNPGameGuardHandle() : m_iTime(1000)
{
	Init();
}

CNPGameGuardHandle::~CNPGameGuardHandle()
{
	Destroy();
}

void CNPGameGuardHandle::Init()
{
	// ���� 30�ʸ� ��� �ϴ°����� �Ѵ�
	m_nStandardTime = 30;
	// +����10�ʸ� �Ѵ�
	m_nRandTime = rand()%10;
	m_dwNPGameCurrTime = 0;

	// ĳ������ ������ ����
	memset(m_szCharName, 0, sizeof(char)*MAX_TEXT);
	memset(m_szHackName, 0, sizeof(char)*MAX_TEXT);

	// �ٻ���� �ϴ�������
	m_bHack = false;
	// ���� �޽��� �ڽ�
	m_bDestroyMsg =false;
	// ���Ӱ��� ���� �޽����ε���
	m_dwErrorMsgIndex =0;
}

void CNPGameGuardHandle::Destroy()
{

}

void CNPGameGuardHandle::SetNPHack(BOOL _IsHack)
{
	m_bHack = _IsHack;

	if(m_bHack)
		m_dwNPGameCurrTime=0;	// ���� ����ϰ� �ִٸ� ī��Ʈ ����
}

BOOL CNPGameGuardHandle::IsNPHack()
{
	// ���� ����ϰ� �ִ���
	return m_bHack;	
}

void CNPGameGuardHandle::SetCharacterInfo(char* _Name, char* _Hack)
{
	// ĳ���� ����
	memcpy(m_szCharName, _Name, strlen(_Name)+1);
	memcpy(m_szHackName, _Name, strlen(_Hack)+1);
}

char* CNPGameGuardHandle::GetCharacterName()
{
	return m_szCharName;
}

char* CNPGameGuardHandle::GetCharacterHack()
{
	return m_szHackName;
}

bool CNPGameGuardHandle::CheckTime()
{
	timeBeginPeriod(1);

	static DWORD _CurrTick = timeGetTime();
	static DWORD _OldTick = 0;
	static DWORD _Cumulative = 0;

	DWORD _CurrentTimeTemp = timeGetTime();

	_CurrTick = _CurrentTimeTemp - _CurrTick;
	_Cumulative = _CurrTick + _OldTick;

	// �ʴ����θ� �˻��Ѵ�
	if(_Cumulative >= m_iTime)
	{
		_OldTick = _Cumulative - m_iTime;	
		_CurrTick = _CurrentTimeTemp;

		m_dwNPGameCurrTime++;
		return false;
	}

	_OldTick = _Cumulative;			
	_CurrTick = _CurrentTimeTemp;
	return true;

	timeEndPeriod(1);
}

void CNPGameGuardHandle::SetDestroyMsg(bool _bDestroyMsg)
{
	m_bDestroyMsg = _bDestroyMsg;
}

BOOL CNPGameGuardHandle::GetDestroyMsg()
{
	return m_bDestroyMsg;
}

void CNPGameGuardHandle::SetErrorMsgIndex(DWORD _nMsgIndex)
{
	m_dwErrorMsgIndex = _nMsgIndex;
}

DWORD CNPGameGuardHandle::GetErrorMsgIndex()
{
	return m_dwErrorMsgIndex;
}

bool CNPGameGuardHandle::CheckDestroyWin()
{
	if(IsNPHack())
	{
		// ĳ���� ����â �̻� �ð��� ������ �Ѵ�
		if(SceneFlag <= CHARACTER_SCENE)
			return false;

		// ���� �ð�+���� �ð� üũ�� ������ ����
		if(m_dwNPGameCurrTime >= m_nStandardTime + m_nRandTime)
		{
			DWORD CurrTick = timeGetTime();
			SendRequestNpDisconnect(CurrTick);
			return true;
		}
	}
	return false;
}

CNPGameGuardHandle* CNPGameGuardHandle::GetInstance()
{
	static CNPGameGuardHandle sInstance;
	return &sInstance;
}
#endif //PBG_MOD_GAMEGUARD_HANDLE
