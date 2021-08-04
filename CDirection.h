#ifndef _DIRECTION_H_
#define _DIRECTION_H_

//////////////////////////////////////////////////////////////////////////
// 
//  ��  �� : �� ����
//  
//  ��  ¥ : 2006�� 7�� 10��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#include <VECTOR>
#include "Singleton.h"

#include "CMVP1stDirection.h"
#include "CKANTURUDirection.h"


using namespace std;

class CDirection : public Singleton <CDirection>
{
private:
	// LHJ - ī�޶� ���� ����
	vec3_t	m_vCameraPosition;				// LHJ - ������ ���� ī�޶� ��ġ
	vec3_t	m_v1stPosition;					// LHJ - ������ ���� ó�� ��ġ ��ǥ ����
	vec3_t	m_v2ndPosition;					// LHJ - ������ ���� ������ ��ġ ��ǥ ����
	vec3_t	m_vResult;						// LHJ - ���� ī�޶� ��ġ���� ���� ������ ī�޶� ��ġ ��� ����; 

	bool	m_bCameraCheck;					// LHJ - ������ ī�޶� �̵� ���� üũ
	float	m_fCount;						// LHJ - ������ ī�޶� �̵� ����
	float	m_fLength;						// LHJ - ������ ī�޶� �̵� ���� ����
	float	m_fCameraSpeed;					// LHJ - ������ ī�޶� �̵� �ӵ�

	// LHJ - �ð� ���� ����
	bool	m_bTimeCheck;					// LHJ - �ð� ���� üũ	
	int		m_iBackupTime;					// LHJ - �ð� ���� ���
	bool	m_bStateCheck;					// LHJ - ����,�� ������ ���� ī�޶� ó�� ��ġ���� �ѹ��� �Ѱ��ֱ� ����

public:
	vector<DirectionMonster> stl_Monster;

	bool	m_bOrderExit;					// LHJ - ���� ���� üũ
	int		m_iTimeSchedule;				// LHJ - ���� ����
	int		m_CameraLevel;					// LHJ - ����� ī�޶� �� �ڷ� ���� �� �� �ִ� ������ ����
	float	m_fCameraViewFar;				// LHJ - ī�޶� �ָ� ���̴� �Ÿ� ����
	int		m_iCheckTime;					// LHJ - ������ ���� ����
	bool	m_bAction;						// LHJ - ������ ��ȯ�̳� �ൿ������ üũ
	bool	m_bDownHero;					// LHJ - �ɸ��� �Ʒ��� ������������ �������� üũ
	float	m_AngleY;						// LHJ - �ɸ��� �������� �ٶ󺸴� ������ ���� ������

	CKanturuDirection m_CKanturu;			// LHJ - ĭ���� ����
	CMVP1STDirection  m_CMVP;				// LHJ - ũ���̿��� ����


	CDirection();
	virtual ~CDirection(); 

	void Init();								// LHJ - �ʱ�ȭ
	void CloseAllWindows();						// LHJ - ��� ������ â�� �ݴ´�
	bool IsDirection();							// LHJ - ���� ���� ���� üũ	
	void CheckDirection();						// LHJ - ���¸� ������ ���� �޾ƿ� �����϶� ����
	void SetCameraPosition();					// LHJ - ������ ���� ó�� ī�޶� ��ġ ����
	int GetCameraPosition(vec3_t GetPosition);	// LHJ - ������ ���� ī�޶� ��ġ �� �Ѱ���
	bool DirectionCameraMove();					// LHJ - ������ ī�޶� �̵�
	void DeleteMonster();						// LHJ - ����� ������ ���͵� ����


	float CalculateAngle(CHARACTER* c, int x, int y, float Angle);		// LHJ - ���� ���� ���������� �̵��� ���� ���
	void CameraLevelUp();												// LHJ - ī�޶� �ڷ� ���ܼ� �� �ָ� ��
	void SetNextDirectionPosition(int x, int y, int z, float Speed);	// LHJ - Ŭ���̿��� ����� ���� ī�޶� ��ġ
	bool GetTimeCheck(int DelayTime);									// LHJ - �ð� ���� �Լ�
	void HeroFallingDownDirection();									// LHJ - �ɸ��Ͱ� �������� ����
	void HeroFallingDownInit();											// LHJ - �ɸ��Ͱ� �������°� �ʱ�ȭ
	void FaillingEffect();												// LHJ - �ɸ��Ͱ� �������� ���� ȿ��

	// LHJ - Ŭ���̿��� ����� ������ ���� ����
	void SummonCreateMonster(int Type, int x, int y, float Angle, bool NextCheck = true, bool SummonAni = true, float AniSpeed = -1.0f);
	// LHJ - Ŭ���̿��� ����� �������� ���� ������ ���� �̵�
	bool MoveCreatedMonster(int Type, int x, int y, float Angle, int Speed);
	// LHJ - Ŭ���̿��� ����� �������� ���� ������ ���� �ൿ(���ϸ��̼�)
	bool ActionCreatedMonster(int Type, int Action, int Count, bool TankerAttack = false, bool NextCheck = false);

};

#define g_Direction CDirection::GetSingleton()

#endif _DIRECTION_H_