// UIRefinery.h: interface for the UIRefinery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIREFINERY_H__29D29488_91BA_4EB6_AEE3_F936A9C872EE__INCLUDED_)
#define AFX_UIREFINERY_H__29D29488_91BA_4EB6_AEE3_F936A9C872EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
//////////////////////// JewelHarmony info ///////////////////////////
//////////////////////////////////////////////////////////////////////

//Ÿ�� (����, ������, ��)
#define MAXHARMONYJEWELOPTIONTYPE 3

//��ȭ ������ �ɼ�
// Ÿ�� 0 = 10 ����
// Ÿ�� 1 = 8 ������
// Ÿ�� 2 = 8 ��
#define MAXHARMONYJEWELOPTIONINDEX 10

//#define IS_BUTTON_SORT

struct HarmonyJewelOption
{
	//��ȭ �ɼ� Ÿ��
	int OptionType;
	//��ȭ �ɼ� �̸�
	char Name[60];
	//�ּ� ����
	int Minlevel;
	//������ ���� ����Ÿ
	int HarmonyJewelLevel[14];
	//ȯ���� �ʿ��� ��
	int Zen[14];

	HarmonyJewelOption() : OptionType( -1 ), Minlevel( -1 )
	{
		for( int i = 0; i < 14; ++i )
		{
			HarmonyJewelLevel[i] = -1;
			Zen[i] = -1;
		}
	}
};

//�ʿ� �� ��ø ���� ��ȭ
struct NaturalAbility
{
	//�ʿ� �� ����
	int SI_force;
	//�ʿ� ��ø ����
	int SI_activity;

	NaturalAbility() : SI_force( 0 ), SI_activity( 0 ){}
};

//���ݷ� ��ȭ
struct StrikingPower
{
	//���� ���ݷ�
	int SI_minattackpower;
	//�ִ� ���ݷ�
	int SI_maxattackpower;
	//�ִ� ����
	int SI_magicalpower;
	//������ ���
	int SI_attackpowerRate;
	//��ų ���ݷ� ���
	int SI_skillattackpower;

	StrikingPower() : SI_minattackpower(0), 
					  SI_maxattackpower(0), 
					  SI_magicalpower(0),
					  SI_attackpowerRate(0),
					  SI_skillattackpower(0){}
};

//�� ��ȭ
struct StrengthenDefense  
{
	//��ȭ�� ��
	int SI_defense;
	//��ȭ�� AG��
	int SI_AG;
	//��ȭ�� HP��
	int SI_HP;
	//����� ���
	int SI_defenseRate;

	StrengthenDefense() : SI_defense( 0 ), SI_AG( 0 ), SI_HP( 0 ), SI_defenseRate( 0 ){}
};

struct StrengthenCapability 
{
	//�ʿ� �� ��ø ���� ��ȭ
	NaturalAbility SI_NB;
	bool		   SI_isNB;

	//���ݷ� ��ȭ
	StrikingPower  SI_SP;
	bool           SI_isSP;

	//�� ��ȭ
	StrengthenDefense SI_SD;
	bool			  SI_isSD;

	StrengthenCapability() : SI_isNB( false ), SI_isSP( false ), SI_isSD( false ){}
};

enum StrengthenItem
{ 
	SI_Weapon = 0, 
	SI_Staff, 
	SI_Defense,
	SI_None,
};

typedef HarmonyJewelOption HARMONYJEWELOPTION;

//��ȭ �ý��� �� ����
class JewelHarmonyInfo
{
public:
	virtual ~JewelHarmonyInfo();
	static JewelHarmonyInfo* MakeInfo();

public:
	const StrengthenItem		GetItemType( int type );
	const HARMONYJEWELOPTION&   GetHarmonyJewelOptionInfo( int type, int option );
	void						GetStrengthenCapability( StrengthenCapability* pitemSC, const ITEM* pitem, const int index );

public:
	const bool IsHarmonyJewelOption( int type, int option );
	
private:
	JewelHarmonyInfo();
	const bool OpenJewelHarmonyInfoFile( const string& filename );

private:
	HARMONYJEWELOPTION		m_OptionData[MAXHARMONYJEWELOPTIONTYPE][MAXHARMONYJEWELOPTIONINDEX];
};

inline
const HARMONYJEWELOPTION& JewelHarmonyInfo::GetHarmonyJewelOptionInfo( int type, int option )
{
	return m_OptionData[type][option-1];//-1�� option ���� 1���� ������
}

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
extern string g_strSelectedML;
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#endif // !defined(AFX_UIREFINERY_H__29D29488_91BA_4EB6_AEE3_F936A9C872EE__INCLUDED_)
