// MonkSystem.h: interface for the CMonkSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONKSYSTEM_H__BB2D80C0_92D7_4E8D_BF3E_32C643EDD764__INCLUDED_)
#define AFX_MONKSYSTEM_H__BB2D80C0_92D7_4E8D_BF3E_32C643EDD764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef PBG_ADD_NEWCHAR_MONK
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"

class CItemEqualType
{
private:
	int m_nModelType;
	int m_nSubLeftType;
	int m_nSubRightType;

public:
	CItemEqualType();
	~CItemEqualType();

	void SetModelType(int _ModelIndex, int _Left, int _Right);
	const int& GetModelType() const { return m_nModelType; }
	const int& GetSubLeftType() const { return m_nSubLeftType; }
	const int& GetSubRightType() const { return m_nSubRightType; }
};

class CDummyUnit
{
private:
	enum {
		MAX_DUMMYDISTANCE = 500,
	};
	vec3_t m_vPosition;
	vec3_t m_vStartPosition;
	vec3_t m_vTargetPosition;
	vec3_t m_vDirection;
	float m_fDisFrame;
	float m_fAniFrame;
	float m_fAlpha;
#ifdef PBG_MOD_RAGEFIGHTERSOUND
	float m_fAniFrameSpeed;
#endif //PBG_MOD_RAGEFIGHTERSOUND
public:
	CDummyUnit();
	~CDummyUnit();

	void Init(vec3_t Pos= NULL, vec3_t Target= NULL);
	void Destroy();
	bool IsDistance();
	vec_t* GetPosition();
	vec_t* GetStartPosition();
	float GetAniFrame();
	float GetAlpha();
#ifdef PBG_MOD_RAGEFIGHTERSOUND
	void CalDummyPosition(vec3_t vOutPos, float& fAni, bool bChange=false);
#else //PBG_MOD_RAGEFIGHTERSOUND
	void CalDummyPosition(vec3_t vOutPos, float& fAni);
#endif //PBG_MOD_RAGEFIGHTERSOUND
};
typedef std::map<int, CDummyUnit>	tm_DummyUnit;

typedef std::map<int, CItemEqualType>	tm_ItemEqualType;
typedef std::list<int>	list_ItemType;
typedef std::vector<WORD>	vec_DarkIndex;
typedef std::vector<int>	vec_DarkTargetIndex;

class CMonkSystem  
{
private:
	enum {
		DS_TARGET_NONE = NUMOFMON,
		MAX_REPEATEDLY = 4,
	};
	struct DamageInfo{
		int m_Damage;
		int m_DamageType;
		bool m_Double;
		//int m_ShieldDamage;
	};

	DamageInfo m_arrRepeatedly[MAX_REPEATEDLY];	// ��Ÿ���ݵ�����
	int m_nRepeatedlyCnt;

	int m_nTotalCnt;
	tm_ItemEqualType m_mapItemEqualType;
	CItemEqualType m_cItemEqualType;
	list_ItemType m_listGloveformSword;

	int m_nDarksideCnt;
	vec_DarkIndex m_DarksideIndex;
	vec_DarkTargetIndex m_DarkTargetIndex;

	enum ATTACK_FRAME
	{
		NONE_ATT = 0,
		FRAME_FIRSTATT = 1,
		FRAME_SECONDATT = 2,
	};

	float m_fFirstFrame;
	float m_fSecondFrame;
	BYTE m_btAttState;

	float m_fDistanceFrame;
	//Ÿ�ٸ�����Ż����
	int m_nDarksideEffectTotal;
	int m_nDarksideEffectAttCnt;
	// �н� ĳ���� �ִ� ������(max=2frame)
	float m_fOtherAniFrame;
	float m_fDistanceNextFrame;
	bool m_bDarkSideEffOnce;
	bool m_bDarkSideEffOnce2;
	// ���� ĳ������
	CDummyUnit m_CDummyUnit;
	tm_DummyUnit m_tmDummyUnit;
	float m_fDummyAniFrame;
	// ���� �Ѱ��� 
	int m_nDummyIndex;

	bool m_bUseEffectOnce;
	int m_nLowerEffCnt;
	
public:
	CMonkSystem();
	virtual ~CMonkSystem();

	//�۷����� �������ʱ�ȭ
	void Init();
	void Destroy();
	//�۷����� ������ ���
	void RegistItem();
	//�������� ��������� �ε���
	int GetSubItemType(int _Type, int _Left = 0);
	//��������� �ε����� ���ε��� ����
	int GetModelItemType(int _Type);
	//����� ���� ������ Ÿ�԰����
	int OrginalTypeCommonItemMonk(int _ModifyType);
	//����� ���� ������ Ÿ�԰����
	int ModifyTypeCommonItemMonk(int _OrginalType);
	//�������������� ����� ������ΰ�
	bool IsRagefighterCommonWeapon(BYTE _Class, int _Type);
	//�������������Ǳ۷κ���������(modeltype)
	bool IsSwordformGloves(int _Type);
	//���������������尩�������� ��������
	void RenderSwordformGloves(CHARACTER *_pCha, int _ModelType, int _Hand, float _Alpha, bool _Translate=false, int _Select=0);
	//�⺻ �κ��� �������̰� ����ÿ� ������ ������ ���������� �����Ѵ�
	int ModifyTypeSwordformGloves(int _ModelType, int _LeftHand);
	//���� ���¸� �ٸ� ������ ����Ÿ������ ����
	int EqualItemModelType(int _Type);
	//�۷����� ��������� �ε�
	void LoadModelItem();
	//�۷����� ��������� �ؽ��ķε�
	void LoadModelItemTexture();
	//�尩�������ǰ˱�
	void MoveBlurEffect(CHARACTER* pCha, OBJECT* pObj, BMD* pModel);
	const int GetItemCnt() const { return m_nTotalCnt; }
	//�۷�����������itemtype�ε���
	void SetSwordformGlovesItemType();
	//�۷����� ����Ÿ���ΰ�(itemtype)
	bool IsSwordformGlovesItemType(int _Type);
	//�����������͹�����������
	bool RageEquipmentWeapon(int _Index, short _ItemType);
	//��Ÿ���ݵ������޼ҵ�
	bool SetRepeatedly(int _Damage, int _DamageType, bool _Double, bool _bEndRepeatedly);
	int GetRepeatedlyDamage(int _index);
	int GetRepeatedlyDamageType(int _index);
	bool GetRepeatedlyDouble(int _index);
	int GetRepeatedlyCnt();
	//������ �ִϸ��̼�
	bool SetRageSkillAni(int _nSkill, OBJECT* _pObj);
	// �ִϸ��̼� ���߿� ������Ŷ ����ϴ� ��ų
	bool IsRageHalfwaySkillAni(int _nSkill);
	// ���� ��Ŷ���
	bool SendAttackPacket(CHARACTER* _pCha, int _nMoveTarget, int _nSkill);
	// ����Ʈ
	bool RageFighterEffect(OBJECT* _pObj, int _Type);
	// ��ũ���̵� ���� ����
	void SetDarksideTargetIndex(WORD* _pTargetIndex);
	WORD GetDarksideTargetIndex(int _nIndex);
	int GetDarksideCnt();
	void SetDarksideCnt();
	// ��ũ���̵������Ŷ
	bool SendDarksideAtt(OBJECT* _pObj);
	void InitDarksideTarget();
	// ��ũ���̵�����Ʈ����
	void DarksideRendering(CHARACTER* pCha, PART_t *pPart, bool Translate=false, int Select=0);
	// Ÿ���� ���� �������� ���� ���
	bool CalculateDarksideTrans(OBJECT* _pObj, vec3_t _vPos, float _fAni, float _fNextAni=0);
	int GetDarksideEffectTotal();
	void InitDummyCal();
	void DestroyDummy();
	void SetDummy(vec3_t pos, vec3_t startpos, int dummyindex);
#ifdef PBG_MOD_RAGEFIGHTERSOUND
	bool IsDummyRender(vec3_t vOutPos, vec3_t Target, float& fAni, int DummyIndex, bool Change=false);
#else //PBG_MOD_RAGEFIGHTERSOUND
	bool IsDummyRender(vec3_t vOutPos, vec3_t Target, float& fAni, int DummyIndex);
#endif //PBG_MOD_RAGEFIGHTERSOUND
	// ��Ÿ���ݿ� ���� �޼ҵ�
	void InitConsecutiveState(float _fFirstFrame=0, float _fSecondFrame=0, BYTE _btAttState = NONE_ATT);
	bool IsConsecutiveAtt(float _fAttFrame);
	// ����������Ʈ
	void RenderRepeatedly(int _Key, OBJECT *pObj);
	// Ż��������� ��� �Ұ����� ��ų
	bool IsRideNotUseSkill(int _nSkill, short _Type);
	// �۷����������츸 ��� ������ ��ų
	bool IsSwordformGlovesUseSkill(int _nSkill);
	// ���ΰ��� ���Ź��� ����� �Ұ����� ��ų
	bool IsChangeringNotUseSkill(short _LType, short _RType, int _LLevel, int _RLevel);
	// ����Ʈ ����
	void InitEffectOnce();
	bool GetSkillUseState();
	bool RageCreateEffect(OBJECT *_pObj, int _nSkill);
	// �ο�����Ʈ ����
	void InitLower();
	int GetLowerEffCnt();
	// �ο�Ÿ������Ʈ�� �ִ� 3��
	bool SetLowerEffEct();
};

extern CMonkSystem g_CMonkSystem;
#endif //PBG_ADD_NEWCHAR_MONK
#endif // !defined(AFX_MONKSYSTEM_H__BB2D80C0_92D7_4E8D_BF3E_32C643EDD764__INCLUDED_)