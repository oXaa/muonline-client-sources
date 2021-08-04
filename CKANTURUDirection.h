#ifndef _KANTURUDIRECTION_H_
#define _KANTURUDIRECTION_H_

//////////////////////////////////////////////////////////////////////////
// 
//  ��  �� : ĭ����3�� ����
//  
//  ��  ¥ : 2006�� 7�� 3��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

class CKanturuDirection
{
public:
	int		m_iKanturuState;		// LHJ - ĭ���� ���� ��
	int		m_iMayaState;			// LHJ - ĭ���� ���� ���� ���� ���� ��
	int		m_iNightmareState;		// LHJ - ĭ���� ����Ʈ�޾� �������� ���� ��
	bool	m_bKanturuDirection;	// LHJ - ĭ���� ���� ����
	

	CKanturuDirection();
	virtual ~CKanturuDirection(); 

	void Init();											// LHJ - ĭ���� �ʱ�ȭ
	bool IsKanturuDirection();								// LHJ - ĭ���� ���� ���� ����
	bool IsKanturu3rdTimer();								// LHJ - ĭ���� ����� ���ýð� ǥ�� üũ
	bool IsMayaScene();										// LHJ - ���� ���� �� ���� ���� üũ
	void GetKanturuAllState(BYTE State, BYTE DetailState);	// LHJ - ĭ���� ��ü ����
	void KanturuAllDirection();								// LHJ - ĭ���� ��ü ����
	bool GetMayaExplotion();								// LHJ - ĭ�������� ���� �״� �������� �ƴ��� �Ѱ���
	void SetMayaExplotion(bool MayaDie);					// LHJ - ĭ�������� ���� �״� ������ �������� ���� �� ������
	bool GetMayaAppear();									// LHJ - ĭ�������� ���� ���� �������� �ƴ��� �Ѱ���
	void SetMayaAppear(bool MayaDie);						// LHJ - ĭ�������� ���� ���� ������ �������� ���� �� ������

private:
	bool	m_bMayaDie;				// LHJ - ĭ���� ���߰� �״� ����
	bool	m_bMayaAppear;			// LHJ - ĭ���� ���߰� �ö� ���� ����
	bool	m_bDirectionEnd;		// LHJ - ĭ���� ������ �������� ���� 

	void GetKanturuMayaState(BYTE DetailState);				// LHJ - ������ ���� ĭ���� ���� ���� �޴´�
	void GetKanturuNightmareState(BYTE DetailState);		// LHJ - ������ ���� ĭ���� ���� ���� �޴´�
	
	void KanturuMayaDirection();		// LHJ - ĭ���� ���� ����
		void Move1stDirection();
			void Direction1st0();
			void Direction1st1();
		void Move2ndDirection();
			void Direction2nd0();
			void Direction2nd1();
			void Direction2nd2();

	void KanturuNightmareDirection();	// LHJ - ĭ���� ����Ʈ�޾� ����
		void Move3rdDirection();
			void Direction3rd0();
			void Direction3rd1();
		void Move4thDirection();
			void Direction4th0();
			void Direction4th1();
};

#endif //_KANTURUDIRECTION_H_