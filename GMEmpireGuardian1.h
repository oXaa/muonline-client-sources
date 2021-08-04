// GMEmpireGuardian1.h: interface for the GMEmpireGuardian1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMEMPIREGUARDIAN1_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_)
#define AFX_GMEMPIREGUARDIAN1_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LDK_ADD_MAP_EMPIREGUARDIAN1

#include "w_BaseMap.h"

BoostSmartPointer( GMEmpireGuardian1 );

class GMEmpireGuardian1 : public BaseMap
{
public:
	static GMEmpireGuardian1Ptr Make();
	virtual ~GMEmpireGuardian1();

public:	// Object
	// ������Ʈ ����
	virtual bool CreateObject(OBJECT* o);
	// ������Ʈ ���μ���
	virtual bool MoveObject(OBJECT* o);
	// ������Ʈ ����Ʈ
	virtual bool RenderObjectVisual(OBJECT* o, BMD* b);
	// ������Ʈ ����
	virtual bool RenderObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);
	// �� ���� ������Ʈ ����Ʈ
	virtual void RenderAfterObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);
	// �� ���� ȭ�� �տ� ������ ȿ��
	virtual void RenderFrontSideVisual();

	// ���� ������
	bool RenderMonster(OBJECT* o, BMD* b, bool ExtraMon = 0);
	
public:	// Character
	// ���� ����
	virtual CHARACTER* CreateMonster(int iType, int PosX, int PosY, int Key);
	// ����(NPC) ���μ���
	virtual bool MoveMonsterVisual(OBJECT* o, BMD* b);
	// ���� ��ų �� ����Ʈ
	virtual void MoveBlurEffect(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( �Ϲ� )	
	virtual bool RenderMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);
	// ���� ����Ʈ ( ��ų )
	virtual bool AttackEffectMonster(CHARACTER* c, OBJECT* o, BMD* b);
	// ��ų �ִϸ��̼� ���� �Լ�
	virtual bool SetCurrentActionMonster(CHARACTER* c, OBJECT* o);
	
	// ����(NPC) ���μ���
	bool MoveMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);

public: // Sound
	// ���� ����
	virtual bool PlayMonsterSound(OBJECT* o);
	// ������Ʈ ����
	virtual void PlayObjectSound(OBJECT* o);
	// �������
	void PlayBGM();

public:
	void Init();
	void Destroy();

public: //Weather
	enum WEATHER_TYPE					// ������ ����
	{
		WEATHER_SUN		= 0,
		WEATHER_RAIN	= 1,	
		WEATHER_FOG		= 2,
		WEATHER_STORM	= 3,
	};

	bool CreateRain( PARTICLE* o );

	void SetWeather(int weather) { m_iWeather = weather; }
	int GetWeather() { return m_iWeather; }

private:
	int m_iWeather;

	// ���ͺ� ����ȭ ����
private:
	bool m_bCurrentIsRage_Raymond;			// �λ�ɰ� ���̸���� ����ȭ ���� ����.
	bool m_bCurrentIsRage_Ercanne;			// ���ְ� ����ĭ���� ����ȭ ���� ����.
	bool m_bCurrentIsRage_Daesuler;			// 1�� �������� ����ȭ ���� ����.
	bool m_bCurrentIsRage_Gallia;			// 4�� �������� ����ȭ ���� ����.

protected:
	GMEmpireGuardian1();
};


// ������ȣ�� �������� �ܺο��� �ľ��� �����ϵ��� 1,2,3,4 ���� �Ѱ� üũ �ϵ��� �մϴ�.
#ifdef LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL
extern bool IsEmpireGuardian();
#endif // LDS_FIX_SKILLKEY_DISABLE_WHERE_EG_ALLTELESKILL

extern bool IsEmpireGuardian1();

#endif	// LDK_ADD_MAP_EMPIREGUARDIAN1

#endif // !defined(AFX_GMEMPIREGUARDIAN1_H__26010684_3099_4F4C_8A33_26FF2281BB35__INCLUDED_)
