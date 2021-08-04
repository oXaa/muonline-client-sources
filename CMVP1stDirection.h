#ifndef _MVP1STDIRECTION_H_
#define _MVP1STDIRECTION_H_

//////////////////////////////////////////////////////////////////////////
// 
//  ��  �� : ũ���̿��� 1�� ���̵� MVP ����
//  
//  ��  ¥ : 2005�� 11�� 14��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#include "Singleton.h"

class CMVP1STDirection
{
private:
	bool	m_bTimerCheck;					// ũ���̿��� ��������� 5���� �ð��� �ش�

	void IsCryWolfDirectionTimer();			// ũ���̿��� ���� ������ 5���� ������ ��

	void MoveBeginDirection();				// ũ���̿��� ���� ����
		void BeginDirection0();				// ũ���̿��� ���۽� ���� �κ�
		void BeginDirection1();
		void BeginDirection2();
		void BeginDirection3();
		void BeginDirection4();
		void BeginDirection5();
public:
	int		m_iCryWolfState;				// ũ���̿��� ����

	CMVP1STDirection();
	virtual ~CMVP1STDirection(); 

	void Init();
	void GetCryWolfState(BYTE CryWolfState);	// ũ���̿��� ���°� �޾ƿ�
	bool IsCryWolfDirection();					// ũ���̿��� ���� �����ΰ� üũ
	void CryWolfDirection();					// ũ���̿��� ���¸� ������ ���� �޾ƿ� ����,�� �����϶� ����

};

#endif //_MVP1STINTERFACE_H_