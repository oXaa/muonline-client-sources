// GM_Raklion.h: interface for the CGM_Raklion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GM_RAKLION_H__00399A9C_5F21_4784_B501_278DE4C74A81__INCLUDED_)
#define AFX_GM_RAKLION_H__00399A9C_5F21_4784_B501_278DE4C74A81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CSK_ADD_MAP_ICECITY

class BMD;

#include "w_BaseMap.h"
#include "./Time/Timer.h"

namespace SEASON4A
{
	BoostSmartPointer( CGM_Raklion );
	class CGM_Raklion : public BaseMap  
	{
	public:
		enum RAKLION_STATE			// ��Ŭ���� ��ü ���� ������
		{
			RAKLION_STATE_IDLE				= 0,	// ��Ŭ���� ������ ��� ����(�׻� ��� �����̴�)
			RAKLION_STATE_NOTIFY_1			= 1,	// �������� �Ź̾��� ������.(Ŭ���̾�Ʈ�� �޽��� ����)
			RAKLION_STATE_STANDBY			= 2,	// ���� ������ ������ ���� ������
			RAKLION_STATE_NOTIFY_2			= 3,	// ���� �޽��� ���(�������� �����Ͽ����ϴ�.)
			RAKLION_STATE_READY				= 4,	// �������� �غ� - ���� ���� �� ���� ��ų �ߵ�
			RAKLION_STATE_START_BATTLE		= 5,	// ������ ���� ���� - ������ ���� �� 5�а��� ���� �����̴�
			RAKLION_STATE_NOTIFY_3			= 6,	// ���� �޽��� ���(��Ŭ���� �������� �������ϴ�.)
			RAKLION_STATE_CLOSE_DOOR		= 7,	// ������ ���� ���� - ������ ���� ���·� ����
			RAKLION_STATE_ALL_USER_DIE		= 8,	// �������� ������ ��� ���� ����
			RAKLION_STATE_NOTIFY_4			= 9,	// ���� �޽��� ���(������ ����) - 5�а� ���
			RAKLION_STATE_END				= 10,	// ���� ���� - ������ �ٽ� ����
			RAKLION_STATE_DETAIL_STATE		= 11,	// �����ǰ��� ������ ���� ���¸� ������ ���� ��
			RAKLION_STATE_MAX				= 12,
		};

		enum RAKLION_BATTLE_OF_SELUPAN_PATTERN				// ������ ���� ������
		{
			BATTLE_OF_SELUPAN_NONE					= 0,	// �������� ���°� �ƴ�(������ ���� ����)
			BATTLE_OF_SELUPAN_STANDBY				= 1,	// �������� �غ� ����
			BATTLE_OF_SELUPAN_PATTERN_1				= 2,	// ������ ���� 1�ܰ�
			BATTLE_OF_SELUPAN_PATTERN_2				= 3,	// ������ ���� 2�ܰ�(����ȭ 1�ܰ�)
			BATTLE_OF_SELUPAN_PATTERN_3				= 4,	// ������ ���� 3�ܰ�(����ȭ 2�ܰ�)
			BATTLE_OF_SELUPAN_PATTERN_4				= 5,	// ������ ���� 4�ܰ�(����ȭ 2�ܰ�)
			BATTLE_OF_SELUPAN_PATTERN_5				= 6,	// ������ ���� 5�ܰ�(����ȭ 3�ܰ�)
			BATTLE_OF_SELUPAN_PATTERN_6				= 7,	// ������ ���� 6�ܰ�(����ȭ 4�ܰ�)
			BATTLE_OF_SELUPAN_PATTERN_7				= 8,	// ������ ���� 7�ܰ�(����ȭ 4�ܰ�)
			BATTLE_OF_SELUPAN_DIE					= 9,	// �������� �׾���.
			BATTLE_OF_SELUPAN_MAX					= 10,	// �������� �ִ� ���� ��
		};

	public:
		static CGM_RaklionPtr Make();
		virtual ~CGM_Raklion();

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

	//-----------------------------------------------------------------------------------------------

	private:
		CGM_Raklion();
		
		// ���� ������
		bool RenderMonster(OBJECT* o, BMD* b, bool ExtraMon = 0);

		void SetBossMonsterAction(CHARACTER* c, OBJECT* o);

	public:
		// �ʿ� �� ������ �ϴ� ȿ��
		bool CreateSnow( PARTICLE* o );
		// ȭ�� ��ü�� ������ ȿ��
		void RenderBaseSmoke();
		// ������ ���� ���� ����
		void SetState(BYTE byState, BYTE byDetailState);
		// ��Ŭ���� �����ʿ� �� �� �ִ°�?
		bool CanGoBossMap();
		// ��Ŭ���� �����ʿ� �� �� �ֳ� ������ �������ִ� �Լ�
		void SetCanGoBossMap();
		// ��Ŭ���� ������ ���� ����
		void SetEffect();
		// ��Ŭ���� ������ ���� ������Ʈ
		void MoveEffect();
		// ��Ŭ���� ������ ���� ����Ʈ �߻� �Լ�
		void CreateMapEffect();
	
	private:
		CTimer2 m_Timer;			// ������ ����� Ÿ�̸�
		BYTE m_byState;				// ������ ���� ����
		BYTE m_byDetailState;		// ������ ���� ���λ���
		bool m_bCanGoBossMap;		// �����ʿ� �� �� �ִ� �����ΰ�? �� �� ������ true, ������ false
		bool m_bVisualEffect;		// ������ ���� ���̴°� ���� ����
		bool m_bMusicBossMap;		// ������ BGM �÷��� ��Ű�°�?
		bool m_bBossHeightMove;		// ���� ���� ���̰� ������״°� ����ó�� ����.
	};
}

// ��Ŭ����(����)�� �ΰ�?
extern bool IsIceCity();
	
#endif // CSK_ADD_MAP_ICECITY

#endif // !defined(AFX_GM_RAKLION_H__00399A9C_5F21_4784_B501_278DE4C74A81__INCLUDED_)
