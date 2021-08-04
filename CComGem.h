#ifndef _COMGEM_H_
#define _COMGEM_H_

//////////////////////////////////////////////////////////////////////////
// 
//  ��  �� : �༮, ���� ���� NPC
//  
//  ��  ¥ : 2005�� 2�� 14��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////
#include "UIManager.h"

typedef std::pair<int, BYTE> INTBYTEPAIR;

namespace COMGEM
{
	//�۾����
	//UI�� ����ʿ� ���� �ʿ���� �Լ��� ������ �����Ѵ�.
	//�κ��丮���� ��ȿ�� �������� ã�Ƴ��� �Լ��� �����Ѵ�.

	//Data
	extern	BOOL	m_bType;	//0 : ����, 1 : ��ü
	extern	char	m_cGemType; //0 : �༮,	1 : ����,	-1 : �̼���
	extern	char	m_cComType;	//����Ÿ��, 10��, 20��, 30��
	extern	BYTE	m_cCount;	//�κ�â�� �ö� �ִ� ������ ����
	extern	int		m_iValue;	//���� ���
	extern	BYTE	m_cPercent;	//���� Ȯ��
	extern	char	m_cState;	//â�� ���
	extern	char	m_cErr;		//�߻� ���� Ÿ��
	extern	CUIUnmixgemList	m_UnmixTarList;

	void	Init();
	void	Exit();
	void	GetBack();
	void	RenderUnMixList();	//��ü�� ���� ����Ʈ �׸��� �Լ�
	void	MoveUnMixList();	//��ä�� ���� ����Ʈ ó��
	void	CalcGen();			//�ݾ� ��� �Լ�
	int		CalcItemValue(const ITEM*);	//�� �� �������� ��������
	char	CalcCompiledCount(const ITEM*); //�� ���� �����Ǿ� �ִ��� ����
	int		CalcEmptyInv();				//���� �� �κ��� �� ������ �� �� �ִ��� üũ
	char	CheckOneItem(const ITEM*);	//�� ���� �������� �˻��ؼ� � ���������� ����
	bool	CheckMyInvValid();			//�� �κ� �˻��ؼ� �����ڵ� ����
	bool	CheckInv();					//���� �˻�

	//���� ��ü�� New Interface
	bool	FindWantedList();			//�� �κ��丮���� ���õ� ������ ������ �ε����� ã�Ƽ� �����Ѵ�.
	void	ResetWantedList();			//â�� �����Ѵ�.
	void	SelectFromList(int iIndex, int iLevel);
	int		GetUnMixGemLevel();			//��ü�� ������ ���� ����

	//������ ���
	void	SendReqMix();
	void	SendReqUnMix();
	void	ProcessCSAction();

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	void	SetJewelList( void );
	int		GetJewelRequireCount( int i );
	int		GetJewelIndex( int _nJewel, int _nType );
	int		Check_Jewel( int _nJewel, int _nType = 0, bool _bModel=false );		// ���� ����/������ ������ ���������� üũ
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

	//�ζ��ε�
	inline	void	SetMode(BOOL mode)	{ m_bType = mode; }		//����-��ü ��ȯ
	inline	void	SetGem(char gem)	{ m_cGemType = gem; }	//���� ���� ����
	inline	void	SetComType(char type)	{ m_cComType = type; }	//���� ���� ����
	inline	void	SetState(char state)	{ m_cState = state; }	//���� ����
	inline	void	SetError(char err)	{ m_cErr = err; }
	inline	char	GetError()	{ return m_cErr; }
	inline	bool	isComMode() { return (m_bType == ATTACH); }

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// �������� ���� �������� �˻��Ѵ�. (2010.10.28)
	__inline int	Check_Jewel_Unit( int _nJewel, bool _bModel = false )	{ return Check_Jewel(_nJewel, 1, _bModel); }	// ���� ���տ� ���̴� ��ǰ �����ΰ�
	__inline int	Check_Jewel_Com( int _nJewel, bool _bModel = false )	{ return Check_Jewel(_nJewel, 2, _bModel); }	// ���� ���տ� ���̴� ���� �����ΰ�
	__inline bool	isCompiledGem(const ITEM* p)							{ return ( Check_Jewel_Com(p->Type) != NOGEM ? true: false); }
#else // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	inline	bool	isCompiledGem(const ITEM* p) { return ( CheckOneItem(p) >= COMCELE); }
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	inline	bool	isAble() { return (m_cState == STATE_READY); }

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
}

#endif //_COMGEM_H_