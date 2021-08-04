#include "stdafx.h"
#include "CComGem.h"
#include "ZzzOpenglUtil.h"
#include "ZzzTexture.h"
#include "ZzzOpenData.h"
#include "ZzzEffect.h"
#include "ZzzAI.h"
#include "ZzzCharacter.h"
#include "ZzzLodTerrain.h"
#include "ZzzInterface.h"
#include "CDirection.h"
#include "wsclientinline.h"

static CDirection Direction;

CDirection::CDirection()
{
	Init();
}

CDirection::~CDirection()
{

}

void CDirection::Init()
{
	Vector(0.0f, 0.0f, 0.0f, m_vCameraPosition);
	Vector(0.0f, 0.0f, 0.0f, m_v1stPosition);
	Vector(0.0f, 0.0f, 0.0f, m_v2ndPosition);
	Vector(0.0f, 0.0f, 0.0f, m_vResult);

	m_bStateCheck = true;
	m_bCameraCheck = false;
	m_bAction = true;
	m_bTimeCheck = true;
	m_bOrderExit = false;
		
	m_bDownHero = false;

	m_fCount = 0.0f;
	m_fLength = 0.0f;
	m_fCameraSpeed = 100.0f;
	m_fCameraViewFar = 1000.0f;

	m_iCheckTime = 0;
	m_iTimeSchedule = 0;
	m_iBackupTime = 0;
	m_CameraLevel = 0;

	m_AngleY = 0.0f;

	m_CMVP.Init();
	m_CKanturu.Init();
}

void CDirection::CloseAllWindows()
{
	SEASON3B::CNewUIInventoryCtrl::BackupPickedItem();
	g_pNewUISystem->HideAll();
}

bool CDirection::IsDirection()
{
	if(World == WD_34CRYWOLF_1ST)
		return m_CMVP.IsCryWolfDirection();			// LHJ - ũ���̿��� ���� �����ΰ� üũ
	else if(World == WD_39KANTURU_3RD)
		return m_CKanturu.IsKanturuDirection();		// LHJ - ĭ���� ���� �����ΰ� üũ

	return false;
}

void CDirection::CheckDirection()
{
	m_CMVP.CryWolfDirection();			// LHJ - ũ���̿��� ���� �����̸� ���� ����
	m_CKanturu.KanturuAllDirection();	// LHJ - ĭ���� ���� �����̸� ���� ����
}

void CDirection::SetCameraPosition()
{
	if(m_bStateCheck)	// LHJ - ī�޶� �̵� �ؾ��� �������� ��ġ�� ����
	{
		if(m_iTimeSchedule == 0)	// LHJ - ���� ������ ó�� �̶��
		{
			// LHJ - �ڱ� �ɸ����� ��ġ���� ī�޶� ó�� ��ġ ���� �Ѱ��ش�
			VectorCopy(Hero->Object.Position, m_v1stPosition);
			m_iTimeSchedule++;		// LHJ - ���� ���� ������ �ѱ��
		}
		
		// LHJ - ī�޶� �̵��� �� ��ġ�� ���͸� ���Ѵ�
		VectorSubtract(m_v2ndPosition, m_v1stPosition, m_vResult);
		// LHJ - �̵��� ������ ���̸� ���Ѵ�
		m_fLength = VectorLength(m_vResult);
	}
}

int CDirection::GetCameraPosition(vec3_t GetPosition)
{
	// LHJ - ������ ���� ī�޶� ��ġ�� ����
	VectorCopy( m_vCameraPosition, GetPosition );
	// LHJ - ī�޶� ���� ���� ���� ������ �Ѱ���
	return m_CameraLevel;
}

bool CDirection::DirectionCameraMove()
{
	if(m_bCameraCheck)	// LHJ - ī�޶� �̵� �ؾ� �� ��츦 �Ǵ�
	{
		SetCameraPosition();	// LHJ - ��ġ ����
		m_bStateCheck = false;  // LHJ - ���̻� ��ġ ���� ����

		VectorNormalize(m_vResult);	// LHJ - �̵��� ���͸� ���� ���ͷ� ����
		vec3_t vTemp;

		VectorScale(m_vResult, m_fCount, vTemp);	// LHJ - �̵��� ��ŭ ���͸� ���δ� 
		VectorAdd(m_v1stPosition, vTemp, m_vCameraPosition); // LHJ - ���� ī�޶� ��ġ
		m_fCount += m_fCameraSpeed;	// LHJ - ī�޶� �̵� �ӵ��� ���Ѵ�

		if(m_fLength <= VectorLength(vTemp))	// LHJ - �� �̵� ������ �׸� �̵� ��Ŵ
		{
			VectorCopy(m_v2ndPosition, m_vCameraPosition);
			m_bAction = true;
			m_bCameraCheck = false;
			m_fCount = 0.0f;
			VectorCopy(m_v2ndPosition, m_v1stPosition);
		}
		return true;
	}

	return false;
}

void CDirection::DeleteMonster()
{
	// LHJ - ����� ������� ���� �����
	int Count = stl_Monster.size();
	
	if(Count == 0)
		return;

	for(int i = 0; i < Count; i++)
	{
		DeleteCharacter(i+NUMOFMON);
		stl_Monster.erase(stl_Monster.begin());
	}
}

float CDirection::CalculateAngle(CHARACTER* c, int x, int y, float Angle)
{
	vec3_t vTemp, vTemp2, vResult;
	float fx = (float)(x*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� x ��ǥ�� ��ȯ
	float fy = (float)(y*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� y ��ǥ�� ��ȯ

	Vector(fx, fy, 0.0f, vTemp);	// LHJ - �̵��� ��ġ
	Vector(c->Object.Position[0], c->Object.Position[1], 0.0f, vTemp2);	// LHJ - ���� ���� ��ġ
	
	VectorSubtract(vTemp2, vTemp, vResult);	// LHJ - �̵��� ����
	Vector(0.0f, 1.0f, 0.0f, vTemp2);

	VectorNormalize(vResult);	// LHJ - �������ͷ� ����

	float fAngle = acos(DotProduct(vResult, vTemp2))/3.14159*180;	// LHJ - ���� ��ġ�� �̵��� ��ġ�� ������ �������� ���

	if(vResult[0] > 0) fAngle = 360 - fAngle;	// LHJ - 180���� �� �Ѿ�°Ϳ� ���� ���� ó��

	// LHJ - ���� ������ �ѱ��
	return fAngle;
}

void CDirection::SummonCreateMonster(int Type, int x, int y, float Angle, bool NextCheck, bool SummonAni, float AniSpeed)
{
	CHARACTER* c = NULL;
	DirectionMonster DMonster = {0,	};

	DMonster.m_Index = stl_Monster.size();
	DMonster.m_bAngleCheck	= true;	// LHJ - ������ ���� ���� Ʋ �� �ֵ��� �ʱ�ȭ
	DMonster.m_iActionCheck = 0;	// LHJ - ������ ���� ���� �ʱ�ȭ

	stl_Monster.push_back(DMonster);
	
	c = CreateMonster(Type,x,y,DMonster.m_Index+NUMOFMON);	// LHJ - ���� ����
	c->Key = NUMOFMON + DMonster.m_Index++;
	c->Object.Angle[2] = Angle;	// LHJ - ó�� ������ �Ѿ�� ������ ���͸� ư��
	c->Weapon[0].Type = -1;
	c->Weapon[1].Type = -1;
	c->Object.Alpha = 0.0f;	// LHJ - 0.0f �̸� �� ������ ���̱� 1.0f�� �ٷ� ���̱�

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	int Index = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	int Index;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	
	switch(Type)
	{
	// LHJ - �̰��� �ִϸ��̼� �ӵ� ������ ���Ͽ� ����� ������ ������ �ε����� �߰��Ѵ�
	case 344: Index = MODEL_MONSTER01+91;	break;	// LHJ - �߶�
	case 341: Index = MODEL_MONSTER01+94;	break;	// LHJ - �Ҷ�
	case 440:
  	case 340: Index = MODEL_MONSTER01+92;	break;	// LHJ - ��ũ����
	case 345: Index = MODEL_MONSTER01+93;	break;	// LHJ - �������Ǹ�
	case 348: Index = MODEL_MONSTER01+99;	break;	// LHJ - ��Ŀ
	case 349: Index = MODEL_MONSTER01+89;	break;	// LHJ - �߰���
	case 361: Index = MODEL_MONSTER01+121;	break;	// LHJ - ����Ʈ �޾�
	}
	
  	BMD *b = &Models[Index];
	
	// LHJ - ������ ������ �ִϸ��̼� �ӵ� �����ϴ� �κ�
	if(AniSpeed >= 0.0f)
		b->Actions[MONSTER01_WALK].PlaySpeed = AniSpeed;

	if(SummonAni)	// LHJ - �Ѿ�� ���� ��ȯ ����Ʈ�� ������
	{
		if(Type == 361)	// LHJ - ����Ʈ �޾�
		{
			// LHJ - ����Ʈ �޾� ��ȯ �ɶ� ȸ���� ȿ��
			vec3_t Light, Angle;

			Vector ( 0.5f, 0.8f, 1.0f, Light );
			Vector(0.0f, 0.0f, 0.0f, Angle);
			CreateEffect(MODEL_STORM2,c->Object.Position, Angle, Light, 1, NULL, -1, 0, 0, 0, 1.6f);
			CreateEffect(MODEL_STORM2,c->Object.Position, Angle, Light, 1, NULL, -1, 0, 0, 0, 1.3f);
			CreateEffect(MODEL_STORM2,c->Object.Position, Angle, Light, 1, NULL, -1, 0, 0, 0, 0.7f);

			PlayBuffer ( SOUND_KANTURU_3RD_MAYA_END );
		}
		else
		{
			PlayBuffer ( SOUND_CRY1ST_SUMMON );

			vec3_t vPos;
			Vector(c->Object.Position[0]+20.0f, c->Object.Position[1]+20.0f, c->Object.Position[2], vPos);
			
			// LHJ - ���� ��ȯ ȿ�� - �ϴÿ��� ���� ��������
			CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 60.f+rand()%10 );
			CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 50.f+rand()%10 );
			CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 50.f+rand()%10 );
			CreateJoint ( BITMAP_JOINT_THUNDER+1, vPos, vPos, c->Object.Angle, 7, NULL, 60.f+rand()%10 );

			// LHJ - ���� ��ȯ ȿ�� - ���� ������ ������ ���� ����
			CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);
			CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);
			CreateParticle ( BITMAP_SMOKE+4, c->Object.Position, c->Object.Angle, c->Object.Light, 1, 5.0f);

			// LHJ - ���� ��ȯ ȿ�� - �� ��Ÿ ���鼭 ������ ���� ȿ��
			Vector(c->Object.Position[0], c->Object.Position[1], c->Object.Position[2]+120.0f, vPos);
			CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
			CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
			CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
			CreateJoint(BITMAP_JOINT_THUNDER, c->Object.Position, vPos, c->Object.Angle, 17);
		}
		
	}
	
	if(NextCheck) m_iCheckTime++;	// LHJ - NextCheck�� True�� ���� ���� �����ٷ� �ѱ�
}

bool CDirection::MoveCreatedMonster(int Index, int x, int y, float Angle, int Speed)
{
	CHARACTER *c = NULL;
	bool bNext = false;	// LHJ - ���� ����� �Ѿ���� üũ

	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)	// LHJ - �̵���ų Index ���� �˻�
	{
		c = &CharactersClient[i];	

		if(c->Object.Live && c->Key == Index+NUMOFMON)
			break;
	}

	int PresentX = (int)(c->Object.Position[0])/TERRAIN_SCALE;	// LHJ - Ÿ�� X �ε���
	int PresentY = (int)(c->Object.Position[1])/TERRAIN_SCALE;	// LHJ - Ÿ�� Y �ε���

	if(PresentX == x && PresentY == y) bNext = true;	// LHJ - ���Ͱ� ������ ���� ������ �̵� �Ϸ�� �Ǵ�
	
	if(!bNext)
	{
		int iResult = 0;

		if(stl_Monster[Index].m_bAngleCheck)
		{
			int	iAngle1 = (int)CalculateAngle(c, x, y, Angle);	// LHJ - �̵��� ��ǥ���� ���� �ٶ󺸴� ���� ���� ���
			int iAngle2 = (int)c->Object.Angle[2];				// LHJ - ���� �ɸ� ����

			if((iAngle1 - Angle) > 180)		// LHJ - ������ ���� ������ 180�� ���� ũ�� �ݴ� �������� ȸ���ϱ� ���� ������ �����
				iAngle1 = iAngle1 - 360;
			
			iResult = iAngle1 - iAngle2;	// LHJ - ���� Ʋ����� ����
			c->Blood  = false;				// LHJ - �� �ӽ� ������ �̵����� ������ �Ǵ� �Ѵ�
		}

		if(iResult <= 3 && iResult >= -3)	// LHJ - ���� �� Ʋ������ �˻� �� Ʋ������ �̵���
		{
			c->Blood = true;	// LHJ - �̵���
			stl_Monster[Index].m_bAngleCheck = false;	// LHJ - ���� ��� �׸���
		}

		if(c->Blood)	// LHJ - �̵�
		{
			c->MoveSpeed = Speed;	// LHJ - �̵� �ӵ�
			SetAction(&c->Object,MONSTER01_WALK);
			MoveCharacterPosition(c);
		}
		else			// LHJ - ���� Ʋ��
		{
			// LHJ - ���� ���� Ʋ�� ����
			if(iResult > 3 && iResult <= 180)
				c->Object.Angle[2] += 3.0f;
			else								
				c->Object.Angle[2] -= 3.0f;		// LHJ - 180�� �ʰ��� �ݴ� �������� ư��

			SetAction(&c->Object,MONSTER01_STOP1);
		}
	}
	else
	{
		c->Object.Position[0] = (float)(x*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� x ��ǥ�� ��ȯ
		c->Object.Position[1] = (float)(y*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� y ��ǥ�� ��ȯ

		stl_Monster[Index].m_bAngleCheck = true;	// LHJ - ������ ���� Ʋ�� �ֵ��� �ʱ�ȭ
		SetAction(&c->Object,MONSTER01_STOP1);		// LHJ - ���� �ൿ �ʱ�ȭ
		return true;	// LHJ - ���� �ൿ���� �Ѿ
	}

	return false;
}

bool CDirection::ActionCreatedMonster(int Index, int Action, int Count, bool TankerAttack, bool NextCheck)
{
	CHARACTER *c = NULL;
	bool bNext = false;	// LHJ - ���� ����� �Ѿ���� üũ

	for(int i=0;i<MAX_CHARACTERS_CLIENT;i++)	// LHJ - ������ �ִϸ��̼� ��ų Index ���� �˻�
	{
		c = &CharactersClient[i];	

		if(c->Object.Live && c->Key == Index+NUMOFMON) break;
	}
	
	// LHJ - ������ �ִϸ��̼� �ݺ� Ƚ���� ä������ Ȯ��
	if( stl_Monster[Index].m_iActionCheck == Count) bNext = true;

	if(!bNext)	// LHJ - �ִϸ��̼� ��Ŵ
	{
		if(c->Object.CurrentAction != Action)	// LHJ - ���� ���۰� ��ɵ� ������ ���� �ٸ���
		{
			// LHJ - ��ɵ� �������� ����
			c->Object.CurrentAction = Action;
			c->Object.AnimationFrame = 0.0f;	
			stl_Monster[Index].m_iActionCheck++;	// LHJ - ������ �ִϸ��̼� �ݺ� Ƚ��

			// LHJ - ���� ũ���̿����� ��Ŀ ������ ���� ����Ʈ ȿ�� �ѷ���
			if(TankerAttack)
				CreateEffect(MODEL_ARROW_TANKER,c->Object.Position,c->Object.Angle,c->Object.Light,1,&c->Object,c->Object.PKKey);
		}
	}
	else
	{
		if(NextCheck) 	// LHJ - ���� ���� �����ٷ� �ѱ�
		{
			stl_Monster[Index].m_iActionCheck = 0;
			m_iCheckTime++;
		}

		// LHJ - ��ɵ� �ִϸ��̼��� ������ ���� ���� ����
		if(c->Object.AnimationFrame >= 8.0f) return true;
	}

	return false;
}

void CDirection::HeroFallingDownDirection()
{
	if(!m_bDownHero)	// LHJ - �ɸ��Ͱ� �������� ������ �ƴϸ� ���� ��Ŵ
		return;

	Hero->Object.Gravity		+= 1.5f;		// LHJ - �������� ������ ���� ���� ���� ������(���ӵ�)
	Hero->Object.Angle[0]		-= 2.f;			// LHJ - �������� �ɸ��Ͱ� �ڷ� �Ѿ���� ȸ��
	Hero->Object.m_bActionStart	 = true;		// LHJ - 
	Hero->Object.Direction[1]	+= Hero->Object.Direction[0];

	if(Hero->Object.Gravity <= 2.f)				// LHJ - �������� �����ϸ� �ɸ��� Y�� ���� ����
		m_AngleY = Hero->Object.Angle[2];

	if(Hero->Object.Angle[0] <= -90.0f)			// LHJ - �ɸ��Ͱ� 90���� ������ ����� ���̻� ȸ�� �Ƚ�Ŵ
		Hero->Object.Angle[0] = -90.0f;
	
	Hero->Object.Angle[2] = m_AngleY;			// LHJ - Y�� ���� ������ ��� ��������

	if(Hero->Object.Gravity >= 150.0f)			// LHJ - ���ӵ��� 150.0f�̻����� ���� ���ϵ��� ��
		Hero->Object.Gravity = 150.0f;

	Hero->Object.Position[2] -= Hero->Object.Gravity;	// LHJ - �ɸ����� ���� ���� ���ӵ� ��ŭ ����

	FaillingEffect();	// LHJ - �ɸ��Ͱ� �������� �����϶� ���� ���� ȿ��
}

void CDirection::FaillingEffect()
{
	vec3_t Pos, Light;
	float Scale = 1.3f + rand()%10/30.0f;
	Vector(0.05f, 0.05f, 0.08f, Light);

	Pos[0] = Hero->Object.Position[0]+(float)(rand()%20-10)*70.0f;
	Pos[1] = Hero->Object.Position[1]+(float)(rand()%20-10)*70.0f;
	Pos[2] = Hero->Object.Position[2]-rand()%200-500.0f;

	CreateParticle(BITMAP_CLOUD, Pos, Hero->Object.Angle, Light, 13, Scale);

	Pos[0] = Hero->Object.Position[0]+(float)(rand()%20-10)*70.0f;
	Pos[1] = Hero->Object.Position[1]+(float)(rand()%20-10)*70.0f;
	Pos[2] = Hero->Object.Position[2]-rand()%200-500.0f;

	Vector(0.05f, 0.05f, 0.05f, Light);
	CreateParticle(BITMAP_CLOUD, Pos, Hero->Object.Angle, Light, 13, Scale);
}

void CDirection::HeroFallingDownInit()
{
	if(!m_bDownHero)
	{
		Hero->Object.m_bActionStart	= false;
		Hero->Object.Gravity = 0.0f;
		Hero->Object.Angle[0] = 0.0f;
	}
}

void CDirection::CameraLevelUp()
{
	if(m_CameraLevel < 4) m_CameraLevel++;
}

void CDirection::SetNextDirectionPosition(int x, int y, int z, float Speed)
{
	m_iCheckTime = 0;
	m_bCameraCheck =true;
	m_bStateCheck = true;
	m_fCameraSpeed = Speed;		// LHJ - �Ѿ�� ������ ī�޶� �̵� �ӵ� ����

	float fx = (float)(x*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� x ��ǥ�� ��ȯ
	float fy = (float)(y*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� y ��ǥ�� ��ȯ
	float fz = (float)(z*TERRAIN_SCALE) + 0.5f*TERRAIN_SCALE;	// LHJ - ���� y ��ǥ�� ��ȯ

	Vector(fx, fy, fz, m_v2ndPosition);	// LHJ - �̵��� ������ ����
	m_iTimeSchedule++;
}

bool CDirection::GetTimeCheck(int DelayTime)
{
	int PresentTime = timeGetTime();
	
	if(m_bTimeCheck)
	{
		m_iBackupTime = PresentTime;
		m_bTimeCheck = false;
	}

	if(m_iBackupTime+DelayTime <= PresentTime)
	{
		m_bTimeCheck = true;
		m_iCheckTime++;
		return true;
	}
	return false;
}
