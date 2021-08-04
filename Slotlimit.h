// Slotlimit.h: interface for the CSlotlimit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOTLIMIT_H__72458006_723F_4246_AA14_5454298A5A5A__INCLUDED_)
#define AFX_SLOTLIMIT_H__72458006_723F_4246_AA14_5454298A5A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef PBG_ADD_CHARACTERSLOT
class CSlotlimit
{
	enum CHAR_ATTRIBUTE
	{
		// ��ĳ���� ���� �´� ��ġ��
 		POS_FIRST_X = 8282,
 		POS_FIRST_Y = 19845,
 		POS_FIRST_ANGLE = 35,

		POS_SECOND_X = 8133,
		POS_SECOND_Y = 19645,
		POS_SECOND_ANGLE = 60,

		POS_THIRD_X = 8046,
		POS_THIRD_Y = 19400,
		POS_THIRD_ANGLE = 75,

		POS_FOURTH_X = 7986,
		POS_FOURTH_Y = 19145,
		POS_FOURTH_ANGLE = 90,		

		POS_FIFTH_X = 8008,
		POS_FIFTH_Y = 18885,
		POS_FIFTH_ANGLE = 115,

		SLOTCNT_MAX = 5, // 4,
		CHARCNT_MAX = 5,
	};

	bool	m_bSlotEnable[SLOTCNT_MAX];
	vec3_t	m_vPos[SLOTCNT_MAX];		// [0],[1]��°�� ��ǥ�� ����ϰ� [2]��°�� rotation����Ѵ�
	int		m_nCharacterCnt;			// ĳ���͸� �����Ҽ� �ִ°���====�⺻ ī��Ʈ 3
public:
	CSlotlimit();
	~CSlotlimit();

	static CSlotlimit* GetInstance();

	void Init();
	// �����ɼ� �ִ� ĳ����
	void SetCharacterCnt(int _Value);
	int GetCharacterCnt();
	// �ڹ��踦 ä������ ����
	int GetDisableSlot();
	// disable�� �� ����
	void SetSlotEnable(int _Value);
	// �ε��� ��°�� Ȱ��ȭ ����
	BOOL GetIsSlotEnable(int _Index);
	// �ڹ��谡 ä������ ���� ������ �Է��Ѵ�
	void SetSlotPosition();
	// �ڹ��跣��
	void CreateSlotLock();
};

#define g_SlotLimit	CSlotlimit::GetInstance()

#endif //PBG_ADD_CHARACTERSLOT
#endif // !defined(AFX_SLOTLIMIT_H__72458006_723F_4246_AA14_5454298A5A5A__INCLUDED_)
