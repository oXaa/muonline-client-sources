// GM_Raklion.cpp: implementation of the CGM_Raklion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef CSK_ADD_MAP_ICECITY

#include "GM_Raklion.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzAI.h"
#include "ZzzEffect.h"
#include "ZzzOpenData.h"
#ifdef PJH_GIANT_MAMUD	//cpjh
#include "BoneManager.h"
#endif //#ifdef PJH_GIANT_MAMUD
#include "ZzzLodTerrain.h"
#include "./Utilities/Log/muConsoleDebug.h"
#include "w_MapHeaders.h"
#include "DSPlaySound.h"

using namespace SEASON4A;

extern char* g_lpszMp3[NUM_MUSIC];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGM_RaklionPtr CGM_Raklion::Make()
{
	CGM_RaklionPtr raklion( new CGM_Raklion );
	raklion->Init();
	return raklion;
}

CGM_Raklion::CGM_Raklion() : m_bCanGoBossMap(true)
{	
	m_byState = RAKLION_STATE_IDLE;
	m_byDetailState = BATTLE_OF_SELUPAN_NONE;
	m_Timer.SetTimer(0);
	m_bVisualEffect = false;
	m_bMusicBossMap = false;
	m_bBossHeightMove = false;
}

CGM_Raklion::~CGM_Raklion()
{
	Destroy();
}

void CGM_Raklion::Init()
{

}

void CGM_Raklion::Destroy()
{

}

bool CGM_Raklion::CreateObject(OBJECT* o)
{
	switch(o->Type)
	{
	// ��Ŭ���¿��� ����ž���� ���� ���� ����Ʈ�Դϴ�.
	// ����ž ���� ���� ���� ����Ʈ �츮�� OK
	case MODEL_WARP:
		{
			/*
			vec3_t Position;
			Vector(o->Position[0], o->Position[1],o->Position[2]+650.f, Position);
			CreateEffect(MODEL_WARP, Position, o->Angle, o->Light, 1);
			
			Vector(o->Position[0], o->Position[1]+4.0f,o->Position[2]+650.f, Position);
			CreateEffect(MODEL_WARP2, Position, o->Angle, o->Light, 1);
			
			Vector(o->Position[0], o->Position[1]+20.0f,o->Position[2]+650.f, Position);
			CreateEffect(MODEL_WARP3, Position, o->Angle, o->Light, 1);
			*/
		}
		return true;
	case MODEL_WARP4:
		{
			vec3_t Position;
			Vector(o->Position[0], o->Position[1]-40.f,o->Position[2]+520.f, Position);
			CreateEffect(MODEL_WARP4, Position, o->Angle, o->Light, 1);
			
			Vector(o->Position[0], o->Position[1]-36.f,o->Position[2]+520.f, Position);
			CreateEffect(MODEL_WARP5, Position, o->Angle, o->Light, 1);
			
			Vector(o->Position[0], o->Position[1]-20.f,o->Position[2]+520.f, Position);
			CreateEffect(MODEL_WARP6, Position, o->Angle, o->Light, 1);
		}
		return true;
	}

	return false;
}

CHARACTER* CGM_Raklion::CreateMonster(int iType, int PosX, int PosY, int Key)
{
	CHARACTER* pCharacter = NULL;
	switch (iType)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 454:	// ���̽� ��Ŀ
		OpenMonsterModel(145);
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01+145, PosX, PosY);
		strcpy(pCharacter->ID, "���̽� ��Ŀ");
		//pCharacter->Object.Scale = 1.0f;
		pCharacter->Object.Scale = 1.2f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER

#ifdef PJH_GIANT_MAMUD	//cpjh
	case 455:	// ���̾�Ʈ �Ÿӵ�
		OpenMonsterModel(146);
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01+146, PosX, PosY);
		strcpy(pCharacter->ID, "���̾�Ʈ �Ÿӵ�");
		pCharacter->Object.Scale = 1.7f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL",45 );
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL_1",6 );
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL_2", 7);
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_1",3 );
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_2",4 );
		BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_3", 5);
		break;
#endif //PJH_GIANT_MAMUD

#ifdef ADD_RAKLION_MOB_ICEGIANT
	case 456:	// ���̽� ���̾�Ʈ
		OpenMonsterModel(147);
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01+147, PosX, PosY);
		strcpy(pCharacter->ID, "���̽� ���̾�Ʈ");
		pCharacter->Object.Scale = 1.0f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		pCharacter->Object.LifeTime = 100;	// �״� ���ۿ��� �� ���� �����ϱ� ���� ������ ������ ��� LifeTime ���.
		break;
#endif	// ADD_RAKLION_MOB_ICEGIANT

#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN	
	case 457:	// ��ƾ
		OpenMonsterModel(148);
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01+148, PosX, PosY);
		strcpy(pCharacter->ID, "��ƾ");
		pCharacter->Object.Scale = 1.0f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN

#ifdef ADD_RAKLION_IRON_KNIGHT
	case 458:	// ���̾� ����Ʈ
		OpenMonsterModel(149);
		pCharacter = CreateCharacter(Key, MODEL_MONSTER01+149, PosX, PosY);
		strcpy(pCharacter->ID, "���̾� ����Ʈ");
		pCharacter->Object.Scale = 1.5f;
		pCharacter->Weapon[0].Type = -1;
		pCharacter->Weapon[1].Type = -1;
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT

	case 459:	// ������ (��������)
		{
			OpenMonsterModel(150);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+150, PosX, PosY);
			strcpy(pCharacter->ID, "������");
			pCharacter->Object.Scale = 2.0f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			
			// ù ���� ��ų�� ���� ���� �Ǵ� �� �Ⱥ����ֱ� ���� �ӽ÷� ��ġ ����
			// ��ų ������ ���Ž��� ��
			if(m_byState >= RAKLION_STATE_STANDBY && m_byState <= RAKLION_STATE_READY)
			{
#ifdef CONSOLE_DEBUG
				g_ConsoleDebug->Write(MCD_NORMAL, "���� ������ġ�� 1000 ����");
#endif // CONSOLE_DEBUG	
				pCharacter->Object.Position[2] = 1000.f;
				m_bBossHeightMove = true;
			}
		}
		break;
	case 460:	// �Ŵ� �Ź̾�
		{
			OpenMonsterModel(151);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+151, PosX, PosY);
			strcpy(pCharacter->ID, "�Ŵ� �Ź̾�");
			pCharacter->Object.Scale = 0.3f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			pCharacter->Object.EnableShadow = false;
			pCharacter->Object.m_bRenderShadow = false;
		}
		break;
	case 461:	// �Ŵ� �Ź̾�
		{
			OpenMonsterModel(152);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+152, PosX, PosY);
			strcpy(pCharacter->ID, "�Ŵ� �Ź̾�");
			pCharacter->Object.Scale = 0.3f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			pCharacter->Object.EnableShadow = false;
			pCharacter->Object.m_bRenderShadow = false;
		}
		break;
	case 462:	// �Ŵ� �Ź̾�
		{
			OpenMonsterModel(153);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+153, PosX, PosY);
			strcpy(pCharacter->ID, "�Ŵ� �Ź̾�");
			pCharacter->Object.Scale = 0.3f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			pCharacter->Object.EnableShadow = false;
			pCharacter->Object.m_bRenderShadow = false;
		}
		break;

#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	case 562: // Ȯ��� ���� : ��ũ �޸ӵ�
		{
			OpenMonsterModel(205);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+205, PosX, PosY);
			strcpy(pCharacter->ID, "��ũ ���̾�Ʈ �Ÿӵ�");
			//pCharacter->Object.Scale = 1.7f;
			pCharacter->Object.Scale = 1.9f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL",45 );
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL_1",6 );
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_TAIL_2", 7);
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_1", 3 );
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_2", 4 );
			BoneManager::RegisterBone(pCharacter, "GIANT_MAMUD_BIP_SPAIN_3", 5);
		}
		break;
	case 563: // Ȯ��� ���� : ��ũ ���̾�Ʈ
		{
			OpenMonsterModel(206);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+206, PosX, PosY);
			strcpy(pCharacter->ID, "��ũ ���̾�Ʈ");
			//pCharacter->Object.Scale = 1.0f;
			pCharacter->Object.Scale = 1.1f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
			pCharacter->Object.LifeTime = 100;	// �״� ���ۿ��� �� ���� �����ϱ� ���� ������ ������ ��� LifeTime ���.
		}
		break;
	
	case 564: // Ȯ��� ���� : ��ũ ��ƾ
		{
			OpenMonsterModel(207);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+207, PosX, PosY);
			strcpy(pCharacter->ID, "��ũ ��ƾ");
			//pCharacter->Object.Scale = 1.0f;
			pCharacter->Object.Scale = 1.3f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
		}
		break;
	case 565: // Ȯ��� ���� : ��ũ ���̾� ����Ʈ
		{
			OpenMonsterModel(208);
			pCharacter = CreateCharacter(Key, MODEL_MONSTER01+208, PosX, PosY);
			strcpy(pCharacter->ID, "��ũ ���̾� ����Ʈ");
			//pCharacter->Object.Scale = 1.5f;
			pCharacter->Object.Scale = 1.8f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;			
		}
		break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}

	return pCharacter;
}

bool CGM_Raklion::MoveObject(OBJECT* o)
{
	if(IsIceCity() == false)
		return false;

	switch(o->Type)
	{
	case 22:
		{
			o->BlendMeshLight = (float)sinf(WorldTime*0.001f)+1.0f;
			return true;
		}
		break;
	case 70:	// �����Ķ���
	case 80:
		{
			o->HiddenMesh = -2;
			return true;
		}
		break;
	}

	MoveEffect();

	return false;
}

bool CGM_Raklion::MoveMonsterVisual(OBJECT* o, BMD* b)
{
	if(IsIceCity() == false)
		return false;

	switch(o->Type)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER	
	case MODEL_MONSTER01+145:	// ���̽���Ŀ
		{			
			switch( o->CurrentAction )
			{
			case MONSTER01_ATTACK2:
				{
					if( o->AnimationFrame > 4.4f && o->AnimationFrame < 4.7f )
					{
						//const float OFFSETLEN = 250.0f, POS_HEIGHT = 220.0f;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
						const float OFFSETLEN	= 70.0f;
						const float POS_HEIGHT	= 240.0f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
						const float ANG_REVISION = 20.0f;
						
						// ��ġ ������ �ʿ��� ��� 
						vec3_t v3Pos, v3Ang_, v3BasisPos;
						
						//vec3_t v3Dir_, v3Dir;
						//float  matRotation[3][4];
						
						// a. Bipad Header�� ��ġ ���� �����´�.
						b->TransformByObjectBone( v3BasisPos, o, 8 );
						
						// b. Position ���� �� ���� Position ���� �κ�..
						VectorCopy( v3BasisPos, v3Pos );
						/*
						VectorCopy( o->Position, v3Pos );
						Vector( 0.0f, -1.0f, 0.0f, v3Dir_ );
						
						  AngleMatrix( o->Angle, matRotation );
						  VectorRotate( v3Dir_, matRotation, v3Dir );
						  
							v3Pos[0] = v3BasisPos[0] + ( v3Dir[0] * OFFSETLEN );
							v3Pos[1] = v3BasisPos[1] + ( v3Dir[1] * OFFSETLEN );
							v3Pos[2] = v3BasisPos[2] + ( v3Dir[2] * OFFSETLEN ); // POS_HEIGHT;
							v3Pos[2] = v3BasisPos[2] + POS_HEIGHT;				// Position ���� 
						*/
						// b. Position ���� �κ�..
						
						// c. ���� ���� �κ�.
						VectorCopy( o->Angle, v3Ang_ );
						v3Ang_[0] = v3Ang_[0] + ANG_REVISION;
						// c. ���� ���� �κ�.
						
						// d. Effect ȣ�� �κ�..
						CreateEffect( MODEL_STREAMOFICEBREATH, v3Pos, o->Angle, o->Light, 0, 0, -1, 0, 0, 0, 0.2f, -1 );	
					}
				}
				break;
			case MONSTER01_DIE:
				{
					vec3_t vPos, vRelative;
					Vector(0.f, 0.f, 0.f, vRelative);
					
					float Scale = 3.5f;
					Vector(1.f, 1.f, 1.f, o->Light);
					b->TransformByObjectBone( vPos, o, 6 );
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
					b->TransformByObjectBone( vPos, o, 79 );
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
				}
				break;
			default:
				{
					
				}
				break;
			} // switch( o->CurrentAction )	
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef PJH_GIANT_MAMUD	//cpjh
	case MODEL_MONSTER01+146:	//���̾�Ʈ �޸ӵ� 
		{
			float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			float fSpeedPerFrame = fActionSpeed/10.f;
			float fAnimationFrame = o->AnimationFrame - fActionSpeed;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			vec3_t Light;
			vec3_t EndPos, EndRelative;
			Vector ( 1.f, 1.f, 1.f, Light );


			if(o->CurrentAction == MONSTER01_ATTACK2)
			{
				if(o->AnimationFrame >= 8.0f && o->AnimationFrame < (8.0f + fActionSpeed))
				{
					Vector(0.0f,  0.0f, 0.0f, EndRelative);
					b->TransformPosition(o->BoneTransform[28],EndRelative,EndPos,true);
					Vector( 0.7f, 0.7f, 1.f, Light );
					CreateParticle(BITMAP_CLUD64, EndPos, o->Angle, Light, 7, 2.0f);
					CreateParticle(BITMAP_CLUD64, EndPos, o->Angle, Light, 7, 2.0f);
					Vector ( 0.9f, 0.9f, 0.9f, Light );
					CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,8 );
					CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,13 );
					CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,13 );

					for(int iu = 0; iu < 60; iu++)
					{
						Vector ( 0.4f, 0.8f, 0.9f, Light );
						CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,EndPos,o->Angle,Light,0);
					}
				}
			}
			else
			{
				vec3_t vPos, vRelative;
				Vector(0.f, 0.f, 0.f, vRelative);
				if(o->CurrentAction == MONSTER01_DIE)
				{
					float Scale = 3.5f;
					Vector(1.f, 1.f, 1.f, o->Light);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL_1", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL_2", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_1", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_2", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
					BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_3", vRelative, vPos);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
				}
			}
			/*
			else
			if(o->CurrentAction == MONSTER01_WALK || o->CurrentAction == MONSTER01_RUN)
			{
				if(rand()%10==0) {
					CreateParticle ( BITMAP_SMOKE+1, o->Position, o->Angle, Light );
				}
			}
			*/
		}
		break;
#endif //PJH_GIANT_MAMUD
	case MODEL_MONSTER01+147:	// ���̽����̾�Ʈ
		{

		}
		break;
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case MODEL_MONSTER01+148:	// ��ƾ
		{
			if( o->AnimationFrame >= 1.7f && o->AnimationFrame <= 2.0f )
			{
				switch(o->CurrentAction)
				{
				case MONSTER01_ATTACK1:
					{
						const float fSize = 1.0f;
						vec3_t vLight, vPos;
						BMD *b = &Models[o->Type];
						
						Vector(0.4f, 0.6f, 1.0f, vLight);
						b->TransformByObjectBone(vPos, o, 19);
						CreateEffect( MODEL_1_STREAMBREATHFIRE, 
							vPos, 
							o->Angle, 
							vLight, 
							0, 0, -1, 0, 0, 0, fSize, -1 );	
					}
					break;
				case MONSTER01_ATTACK2:
					{
						const float fSize = 1.0f;
						vec3_t vLight, vPos;
						BMD *b = &Models[o->Type];
						
						Vector(0.0f, 0.9f, 0.1f, vLight);
						b->TransformByObjectBone(vPos, o, 19);
						CreateEffect( MODEL_1_STREAMBREATHFIRE, 
							vPos, 
							o->Angle, 
							vLight, 
							0, 0, -1, 0, 0, 0, fSize, -1 );		
					}
					break;
				} // switch(o->CurrentAction)
			} // if( o->AnimationFrame >= 1.7f && o->AnimationFrame <= 2.0f )

			if( o->AnimationFrame <= 8.0f )
			{
				switch( o->CurrentAction )
				{
				case MONSTER01_DIE:
					{
						vec3_t vPos, vLight;
						
						// ��ȿ��
						if(rand()%3 != 0)
						{
							for(int i=0; i<b->NumBones; ++i)
							{
								b->TransformByObjectBone(vPos, o, i);
								if(rand()%5 == 0)
								{
									Vector(0.0f, 1.f, 0.2f, vLight);
									CreateParticle(BITMAP_WATERFALL_5, vPos, o->Angle, vLight, 8, 2.0f);
								}
								if(rand()%5 == 0)
								{
									Vector(0.1f, 1.f, 0.1f, vLight);
									CreateParticle(BITMAP_WATERFALL_3, vPos, o->Angle, vLight, 8, 2.5f);
								}
							}
						}
						
						if(rand()%3 == 0)
						{
							// ����ȿ��
							VectorCopy(o->Position, vPos);
							vPos[0] += (float)(rand()%200-100);
							vPos[1] += (float)(rand()%200-100);
							Vector(1.0f, 1.f, 1.f, vLight);
							CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 1, 0.5f );
							CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 24, 1.25f );
							
							// �ٴ�ȿ��
							VectorCopy(o->Position, vPos);
							vPos[0] += (float)(rand()%250-125);
							vPos[1] += (float)(rand()%250-125);
							Vector(0.1f, 1.0f, 0.1f, vLight);
							CreateEffect(BITMAP_CLOUD, vPos, o->Angle, vLight, 0, NULL, -1, 0, 0, 0, 1.0f);
							
							// ����ũ
							Vector(1.0f, 1.0f, 1.0f, vLight);
							vPos[2] += 50.f;
							CreateParticle ( BITMAP_SPARK+1,  vPos, o->Angle, vLight, 5, 0.75f );
						}
						
					} // case MONSTER01_DIE:
					break;
				} // switch(o->CurrentAction)
			}
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+149:	// ���̾� ����Ʈ
		{
			
		}
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+150:	// ������ (��������)
		{
			if(o->CurrentAction == MONSTER01_ATTACK1)
			{
				vec3_t vLight, vPos;

				if(o->AnimationFrame >= 3.7f && o->AnimationFrame <= 4.f)
				{
					// ������ ȿ��
					Vector(0.2f, 0.4f, 1.f, vLight);
					VectorCopy(o->Position, vPos);
					vPos[1] += 30.f;
					CreateEffect(MODEL_RAKLION_BOSS_MAGIC, vPos, o->Angle, vLight, 0, o, -1, 0, 0, 0, 1.5f );

					// ���� �������� ȿ��
					Vector(0.2f, 0.4f, 1.f, vLight);
					for(int i=0; i<20; ++i)
					{
						vPos[0] = Hero->Object.Position[0] + (float)(rand()%20-10)*80.0f+500.0f;
						vPos[1] = Hero->Object.Position[1] + (float)(rand()%20-10)*80.0f+200.0f;
						vPos[2] = Hero->Object.Position[2] + 300.0f+(float)(rand()%10)*100.0f;
						float fScale = 1.0f + (rand()%10) / 5.0f;
						int iIndex = MODEL_EFFECT_BROKEN_ICE1;
						if(rand()%2 == 0)
						{
							iIndex = MODEL_EFFECT_BROKEN_ICE3;
						}
						CreateEffect(iIndex, vPos, o->Angle, vLight, 1, NULL, -1, 0, 0, 0, fScale);
					}
				}
			}
			else if(o->CurrentAction == MONSTER01_ATTACK2)
			{
				vec3_t vLight, vPos, vAngle;
				
				// �м�ȿ��
				Vector(0.0f, 0.9f, 0.1f, vLight);
				b->TransformByObjectBone(vPos, o, 0);
				CreateParticle ( BITMAP_WATERFALL_3, vPos, o->Angle, vLight, 11, 2.f );
				// ����
				CreateParticle ( BITMAP_SMOKE, vPos, o->Angle, vLight, 52, 2.f );

				if(o->AnimationFrame >= 6.8f && o->AnimationFrame <= 7.f)
				{
					// �� 5�� �߻�
					float Matrix[3][4];
					vec3_t vDirection, vDirection2;
					VectorCopy(o->Position, vPos);
					vPos[2] += 100.f;
					float fAngle = 0.f;
					Vector ( 0.f, 0.f, 0.f, vAngle );
					for(int i=0; i<5; ++i)
					{
						Vector ( 0.f, 20.f, 0.f, vDirection );
						fAngle = o->Angle[2] + 150.f + i*20.f;
						Vector ( 0.f, 0.f, fAngle, vAngle );
						AngleMatrix ( vAngle, Matrix );
						VectorRotate ( vDirection, Matrix, vDirection2 );
						CreateEffect( MODEL_MOONHARVEST_MOON, vPos, vDirection2, vLight, 1, NULL, -1, 0, 0, 0, 0.4f );
					}
				}
			}
			else if(o->CurrentAction == MONSTER01_ATTACK3)
			{
				vec3_t vLight, vPos, vAngle, vPos2;
				float Matrix[3][4];

				Vector(0.3f, 0.5f, 1.f, vLight);
				
				if(o->AnimationFrame >= 6.6f && o->AnimationFrame <= 7.f)
				{
					// ������ ������ ȿ��
					CreateEffect(BITMAP_DAMAGE_01_MONO, o->Position, o->Angle, vLight, 0);

					// 3���� �ұ�� ����Ʈ
					for(int i=0; i<3; ++i)
					{
						Vector ( 0.f, 200.f, 0.f, vPos );
						Vector ( 0.f, 0.f, (i*120.f), vAngle );
						AngleMatrix ( vAngle, Matrix );
						VectorRotate ( vPos, Matrix, vPos2 );
						VectorAdd ( vPos2, o->Position, vPos2 );
						CreateEffect(BITMAP_FIRE_HIK2_MONO, vPos2, o->Angle, vLight, 0, o );
					}

					// ������ �ұ��
					Vector(0.0f, 0.0f, 1.f, vLight);
					CreateEffect(BITMAP_FIRE_HIK2_MONO, o->Position, o->Angle, vLight, 1, o );

					// �� �������� ȿ��
					Vector(0.1f, 0.2f, 1.f, vLight);
					CreateEffect(MODEL_RAKLION_BOSS_CRACKEFFECT, o->Position, o->Angle, vLight, 0, o, -1, 0, 0, 0, 2.f);
				}
			}
			else if(o->CurrentAction == MONSTER01_APEAR)
			{
				vec3_t vLight, vPos, vAngle, vPos2;
				float Matrix[3][4];
				float fScale = 1.f;

				if(o->AnimationFrame <= 3.f)
				{
					Vector(0.3f, 0.5f, 1.f, vLight);
					
					for(int i=0; i<1; ++i)
					{
						// ū ���� ������ �������� ����Ʈ
						VectorCopy(o->Position, vPos);
						vPos[0] += (rand()%2000 - 1000.f);
						vPos[1] += (rand()%2000 - 1000.f);
						vPos[2] = 500.f + rand()%100;
						
						fScale = 2.0f + (rand()%20) / 5.0f;
						int iIndex = MODEL_EFFECT_BROKEN_ICE1;
						
						CreateEffect(iIndex, vPos, o->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
						
						VectorCopy(o->Position, vPos);
						vPos[0] += (rand()%2000 - 1000.f);
						vPos[1] += (rand()%2000 - 1000.f);
						vPos[2] = 500.f + rand()%100;
						
						fScale = 0.5f + (rand()%10) / 5.0f;
						iIndex = MODEL_EFFECT_BROKEN_ICE3;
						
						CreateEffect(iIndex, vPos, o->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);

						// ū ������ �������� ����Ʈ
						VectorCopy(o->Position, vPos);
						vPos[0] += (rand()%2000 - 1000.f);
						vPos[1] += (rand()%2000 - 1000.f);
						vPos[2] = 500.f + rand()%100;

						Vector(1.f, 0.8f, 0.8f, vLight);
						fScale = 0.05f + (rand()%10) / 20.0f;
						CreateEffect(MODEL_FALL_STONE_EFFECT, vPos, o->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);

						Vector(0.7f, 0.7f, 0.8f, vLight);
						vPos[0] += (float)(rand()%80-40);
						vPos[1] += (float)(rand()%80-40);
						CreateParticle(BITMAP_WATERFALL_3+(rand()%2), vPos, o->Angle, vLight, 2 );
					}
				}

				if(o->AnimationFrame >= 5.f && o->AnimationFrame <= 7.f)
				{
					// ȭ�� ���� ȿ��
					EarthQuake = (float)(rand()%4-2)*1.0f;
					
					if(o->AnimationFrame >= 5.6f && o->AnimationFrame <= 6.1f)
					{
						Vector(0.3f, 0.5f, 1.f, vLight);

						// ������ ������ ȿ��
						CreateEffect(BITMAP_DAMAGE_01_MONO, o->Position, o->Angle, vLight, 0);
						
						// 3���� �ұ�� ����Ʈ
						for(int i=0; i<3; ++i)
						{
							Vector ( 0.f, 200.f, 0.f, vPos );
							Vector ( 0.f, 0.f, (i*120.f), vAngle );
							AngleMatrix ( vAngle, Matrix );
							VectorRotate ( vPos, Matrix, vPos2 );
							VectorAdd ( vPos2, o->Position, vPos2 );
							CreateEffect(BITMAP_FIRE_HIK2_MONO, vPos2, o->Angle, vLight, 0, o );
						}
						
						// ������ �ұ��
						Vector(0.0f, 0.0f, 1.f, vLight);
						CreateEffect(BITMAP_FIRE_HIK2_MONO, o->Position, o->Angle, vLight, 1, o );
						
						// �� �������� ȿ��
						Vector(0.1f, 0.2f, 1.f, vLight);
						CreateEffect(MODEL_RAKLION_BOSS_CRACKEFFECT, o->Position, o->Angle, vLight, 0, o, -1, 0, 0, 0, 2.f);

						PlayBuffer(SOUND_KANTURU_3RD_MAYAHAND_ATTACK2);
					}
				}
				else
				{
					EarthQuake = 0.f;
				}
			}
			else if(o->CurrentAction == MONSTER01_DIE && o->AnimationFrame <= 8.f)
			{
				vec3_t vPos, vLight;

				// ��ȿ��
				if(rand()%3 != 0)
				{
					for(int i=0; i<b->NumBones; ++i)
					{
						b->TransformByObjectBone(vPos, o, i);
						if(rand()%5 == 0)
						{
							Vector(0.0f, 1.f, 0.2f, vLight);
							CreateParticle(BITMAP_WATERFALL_5, vPos, o->Angle, vLight, 8, 2.0f);
						}
						if(rand()%5 == 0)
						{
							Vector(0.1f, 1.f, 0.1f, vLight);
							CreateParticle(BITMAP_WATERFALL_3, vPos, o->Angle, vLight, 8, 2.5f);
						}
					}
				}

				if(rand()%3 == 0)
				{
					// ����ȿ��
					VectorCopy(o->Position, vPos);
					vPos[0] += (float)(rand()%400-200);
					vPos[1] += (float)(rand()%400-200);
					Vector(1.0f, 1.f, 1.f, vLight);
					CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 1, 1.f );
					CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 24, 2.5f );
					
					// �ٴ�ȿ��
					VectorCopy(o->Position, vPos);
					vPos[0] += (float)(rand()%500-250);
					vPos[1] += (float)(rand()%500-250);
					Vector(0.1f, 1.0f, 0.1f, vLight);
					CreateEffect(BITMAP_CLOUD, vPos, o->Angle, vLight, 0, NULL, -1, 0, 0, 0, 2.0f);
					
					// ����ũ
					Vector(1.0f, 1.0f, 1.0f, vLight);
					vPos[2] += 50.f;
					CreateParticle ( BITMAP_SPARK+1,  vPos, o->Angle, vLight, 5, 1.5f );
				}
			}
			
			// ����ȭ �ܰ�
			if(m_byDetailState >= BATTLE_OF_SELUPAN_PATTERN_3 && m_byDetailState <= BATTLE_OF_SELUPAN_PATTERN_7)
			{
				vec3_t vLight;
				float fScale = 1.0f;
				if(m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_3 || m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_4)
				{
					fScale = 0.5f;
				}
				else if(m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_5)
				{
					fScale = 1.0f;
				}
				else if(m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_6 || m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_7)
				{
					fScale = 1.5f;
				}
				
				Vector(1.0f, 0.1f, 0.1f, vLight);
				for(int k=0; k<1; ++k)
				{
					if(rand()%2 == 0)
					{	
						vec3_t vPos1, vPos2;
						b->TransformByObjectBone(vPos1, o, 34);
						CreateParticle(BITMAP_SMOKE,vPos1,o->Angle,vLight,50,fScale);	// ����
						CreateParticle(BITMAP_SMOKELINE1+rand()%3,vPos1,o->Angle,vLight,0,fScale);	// 3�� ����
						
						b->TransformByObjectBone(vPos2, o, 52);
						CreateParticle(BITMAP_SMOKE,vPos2,o->Angle,vLight,50,fScale);	// ����
						CreateParticle(BITMAP_SMOKELINE1+rand()%3,vPos2,o->Angle,vLight,0,fScale);	// 3�� ����

						if(m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_6 || m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_7)
						{
							CreateParticle(BITMAP_FIRE_HIK1_MONO,vPos1,o->Angle,vLight,0,o->Scale);
							CreateParticle(BITMAP_FIRE_HIK1_MONO,vPos2,o->Angle,vLight,0,o->Scale);
						}
					}
				}
			}
		}
		break;
	case MODEL_MONSTER01+151:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+152:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+153:	// �Ŵ� �Ź̾�
		{
			if(o->CurrentAction == MONSTER01_DIE && o->AnimationFrame <= 12.f)
			{
				vec3_t vPos, vLight;

				for(int i=0; i<1; ++i)
				{
					VectorCopy(o->Position, vPos);

					if(i == 0)	
					{
						vPos[0] += 100.f;
					}
					else if(i == 1)
					{
						vPos[0] += 100.f;
						vPos[1] += 100.f;
					}
					
					vPos[0] += rand()%60 - 30.f;
					vPos[1] += rand()%60 - 30.f;
					vPos[2] += rand()%20 - 10.f;
					Vector(0.2f, 0.4f, 1.0f, vLight);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 11, 1.2f);

					// �ٴ�ȿ��
					if(rand()%2 == 0)
					{
						VectorCopy(o->Position, vPos);
						vPos[0] += (float)(rand()%200-100);
						vPos[1] += (float)(rand()%200-100);
						Vector(0.2f, 0.4f, 1.0f, vLight);
						CreateEffect(BITMAP_CLOUD, vPos, o->Angle, vLight, 0, NULL, -1, 0, 0, 0, 1.0f);
					}
				}
			}
		}
		break;	
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION	// Ȯ��� ���͵�
		case MODEL_MONSTER01+205:	// ��ũ ���̾�Ʈ �޸ӵ�
			{
				float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				float fSpeedPerFrame = fActionSpeed/10.f;
				float fAnimationFrame = o->AnimationFrame - fActionSpeed;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				vec3_t Light;
				vec3_t EndPos, EndRelative;
				Vector ( 1.f, 1.f, 1.f, Light );


				if(o->CurrentAction == MONSTER01_ATTACK2)
				{
					if(o->AnimationFrame >= 8.0f && o->AnimationFrame < (8.0f + fActionSpeed))
					{
						Vector(0.0f,  0.0f, 0.0f, EndRelative);
						b->TransformPosition(o->BoneTransform[28],EndRelative,EndPos,true);
						Vector( 0.7f, 0.7f, 1.f, Light );
						CreateParticle(BITMAP_CLUD64, EndPos, o->Angle, Light, 7, 2.0f);
						CreateParticle(BITMAP_CLUD64, EndPos, o->Angle, Light, 7, 2.0f);
						Vector ( 0.9f, 0.9f, 0.9f, Light );
						CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,8 );
						CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,13 );
						CreateEffect ( BITMAP_SHOCK_WAVE, EndPos, o->Angle, Light,13 );

						for(int iu = 0; iu < 60; iu++)
						{
							Vector ( 0.4f, 0.8f, 0.9f, Light );
							CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,EndPos,o->Angle,Light,0);
						}
					}
				}
				else
				{
					vec3_t vPos, vRelative;
					Vector(0.f, 0.f, 0.f, vRelative);
					if(o->CurrentAction == MONSTER01_DIE)
					{
						float Scale = 3.5f;
						Vector(1.f, 1.f, 1.f, o->Light);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL_1", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_TAIL_2", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_1", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_2", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 53, Scale);
						BoneManager::GetBonePosition(o, "GIANT_MAMUD_BIP_SPAIN_3", vRelative, vPos);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, o->Light, 3, Scale);
					}
				}
				/*
				else
				if(o->CurrentAction == MONSTER01_WALK || o->CurrentAction == MONSTER01_RUN)
				{
					if(rand()%10==0) {
						CreateParticle ( BITMAP_SMOKE+1, o->Position, o->Angle, Light );
					}
				}
				*/
			}
			break;
		case MODEL_MONSTER01+206:	// ��ũ ���̾�Ʈ 
			{

			}
			break;
		case MODEL_MONSTER01+207:	// ��ũ ��ƾ
			{
				if( o->AnimationFrame >= 1.7f && o->AnimationFrame <= 2.0f )
				{
					switch(o->CurrentAction)
					{
					case MONSTER01_ATTACK1:
						{
							const float fSize = 1.0f;
							vec3_t vLight, vPos;
							BMD *b = &Models[o->Type];
							
							Vector(0.4f, 0.6f, 1.0f, vLight);
							b->TransformByObjectBone(vPos, o, 19);
							CreateEffect( MODEL_1_STREAMBREATHFIRE, 
								vPos, 
								o->Angle, 
								vLight, 
								0, 0, -1, 0, 0, 0, fSize, -1 );	
						}
						break;
					case MONSTER01_ATTACK2:
						{
							const float fSize = 1.0f;
							vec3_t vLight, vPos;
							BMD *b = &Models[o->Type];
							
							Vector(0.0f, 0.9f, 0.1f, vLight);
							b->TransformByObjectBone(vPos, o, 19);
							CreateEffect( MODEL_1_STREAMBREATHFIRE, 
								vPos, 
								o->Angle, 
								vLight, 
								0, 0, -1, 0, 0, 0, fSize, -1 );		
						}
						break;
					} // switch(o->CurrentAction)
				} // if( o->AnimationFrame >= 1.7f && o->AnimationFrame <= 2.0f )
				
				if( o->AnimationFrame <= 8.0f )
				{
					switch( o->CurrentAction )
					{
					case MONSTER01_DIE:
						{
							vec3_t vPos, vLight;
							
							// ��ȿ��
							if(rand()%3 != 0)
							{
								for(int i=0; i<b->NumBones; ++i)
								{
									b->TransformByObjectBone(vPos, o, i);
									if(rand()%5 == 0)
									{
										Vector(0.0f, 1.f, 0.2f, vLight);
										CreateParticle(BITMAP_WATERFALL_5, vPos, o->Angle, vLight, 8, 2.0f);
									}
									if(rand()%5 == 0)
									{
										Vector(0.1f, 1.f, 0.1f, vLight);
										CreateParticle(BITMAP_WATERFALL_3, vPos, o->Angle, vLight, 8, 2.5f);
									}
								}
							}
							
							if(rand()%3 == 0)
							{
								// ����ȿ��
								VectorCopy(o->Position, vPos);
								vPos[0] += (float)(rand()%200-100);
								vPos[1] += (float)(rand()%200-100);
								Vector(1.0f, 1.f, 1.f, vLight);
								CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 1, 0.5f );
								CreateParticle ( BITMAP_SMOKE,  vPos, o->Angle, vLight, 24, 1.25f );
								
								// �ٴ�ȿ��
								VectorCopy(o->Position, vPos);
								vPos[0] += (float)(rand()%250-125);
								vPos[1] += (float)(rand()%250-125);
								Vector(0.1f, 1.0f, 0.1f, vLight);
								CreateEffect(BITMAP_CLOUD, vPos, o->Angle, vLight, 0, NULL, -1, 0, 0, 0, 1.0f);
								
								// ����ũ
								Vector(1.0f, 1.0f, 1.0f, vLight);
								vPos[2] += 50.f;
								CreateParticle ( BITMAP_SPARK+1,  vPos, o->Angle, vLight, 5, 0.75f );
							}
							
						} // case MONSTER01_DIE:
						break;
					} // switch(o->CurrentAction)
				}
			}
			break;
		case MODEL_MONSTER01+208:	// ��ũ ���̾� ����Ʈ
			{

			}
			break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}

	return false;
}

void CGM_Raklion::MoveBlurEffect(CHARACTER* c, OBJECT* o, BMD* b)
{
	//int iType = MODEL_MONSTER01+455;

	switch(o->Type)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+145:	// ���̽� ��Ŀ
		{
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+146:	// ���̾�Ʈ �Ÿӵ�
		{
		}
		break;
	case MODEL_MONSTER01+147:	// ���̽� ���̾�Ʈ
#ifdef ADD_RAKLION_MOB_ICEGIANT
		{
			float Start_Frame = 3.f;
			float End_Frame = 8.0f;
			if((o->AnimationFrame >= Start_Frame && o->AnimationFrame <= End_Frame && o->CurrentAction == MONSTER01_ATTACK1) 
				|| (o->AnimationFrame >= Start_Frame && o->AnimationFrame <= End_Frame && o->CurrentAction == MONSTER01_ATTACK2))
			{
				vec3_t  Light;
				Vector(1.0f, 1.2f, 2.f, Light);
				
				vec3_t StartPos, StartRelative;
				vec3_t EndPos, EndRelative;
				
				float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
				float fSpeedPerFrame = fActionSpeed/10.f;
				float fAnimationFrame = o->AnimationFrame - fActionSpeed;
				for(int i=0; i<10; i++) 
				{
					b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);
					
					Vector(0.f, 0.f, 0.f, StartRelative);
					Vector(0.f, 0.f, 0.f, EndRelative);
					
					b->TransformPosition(BoneTransform[35], StartRelative, StartPos, false);
					b->TransformPosition(BoneTransform[36], EndRelative, EndPos, false);
					CreateBlur(c, StartPos, EndPos, Light, 0);
					
					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
#endif	// ADD_RAKLION_MOB_ICEGIANT	
		break;
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN	
	case MODEL_MONSTER01+148:	// ��ƾ
		{
			
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+149:	// ���̾� ����Ʈ
		{
			// RenderMonsterVisual() �Լ��� �Ű���.
			// ��� ���ۿ��� �˱Ⱑ ������ �ϱ� ���ؼ�
		}
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+150:	// ������ (��������)
		{
			// RenderMonsterVisual() �Լ��� �Ű���.
			// ��� ���ۿ��� �˱Ⱑ ������ �ϱ� ���ؼ�
		}
		break;
	case MODEL_MONSTER01+151:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+152:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+153:	// �Ŵ� �Ź̾�
		{
			
		}
		break;	
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	case MODEL_MONSTER01+205:	// ��ũ ���̾�Ʈ �޸ӵ�
		{
			
		}
		break;
	case MODEL_MONSTER01+206:	// ��ũ ���̽� ���̾�Ʈ
		{
			float Start_Frame = 3.f;
			float End_Frame = 8.0f;
			if((o->AnimationFrame >= Start_Frame && o->AnimationFrame <= End_Frame && o->CurrentAction == MONSTER01_ATTACK1) 
				|| (o->AnimationFrame >= Start_Frame && o->AnimationFrame <= End_Frame && o->CurrentAction == MONSTER01_ATTACK2))
			{
				vec3_t  Light;
				Vector(1.0f, 1.2f, 2.f, Light);
				
				vec3_t StartPos, StartRelative;
				vec3_t EndPos, EndRelative;
				
				float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
				float fSpeedPerFrame = fActionSpeed/10.f;
				float fAnimationFrame = o->AnimationFrame - fActionSpeed;
				for(int i=0; i<10; i++) 
				{
					b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);
					
					Vector(0.f, 0.f, 0.f, StartRelative);
					Vector(0.f, 0.f, 0.f, EndRelative);
					
					b->TransformPosition(BoneTransform[35], StartRelative, StartPos, false);
					b->TransformPosition(BoneTransform[36], EndRelative, EndPos, false);
					CreateBlur(c, StartPos, EndPos, Light, 0);
					
					fAnimationFrame += fSpeedPerFrame;
				}
			}
		} // case MODEL_MONSTER01+456:	// ��ũ ���̽� ���̾�Ʈ
		break;
	case MODEL_MONSTER01+208:	// ��ũ ���̾� ����Ʈ
		{
			
		}
		break;
	case MODEL_MONSTER01+207:	// ��ũ ��ƾ
		{
			
		}
		break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}
}

bool CGM_Raklion::RenderObjectMesh(OBJECT* o, BMD* b, bool ExtraMon)
{
	if(IsIceCity() == false)
		return false;

	if(o->Type >= 6 && o->Type <= 12 )
	{
		extern float IntensityTransform[MAX_MESH][MAX_VERTICES];
		for(int i = 0; i < b->NumMeshs; i++)
		{
			Mesh_t *m = &b->Meshs[i];
			for(int j = 0; j < m->NumNormals; j++)
			{
				IntensityTransform[i][j] = 0.5f;
			}
		}
		Vector(1.0f, 1.0f, 1.0f, o->Light);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		return true;
	}
	else if(o->Type == 16)
	{
		if(o->AnimationFrame >= 19)	// ����ڼ�
		{
			SetAction(o, rand()%2);
		}
		
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		return true;
	}
	else if(o->Type == 17)
	{
		if(o->CurrentAction >= 0 && o->CurrentAction <= 1 && o->AnimationFrame >= 19)	// ����ڼ�
		{
			int iAniIndex = rand()%100;
			
			if(iAniIndex < 90)
			{
				if(iAniIndex%2 == 0)
					SetAction(o, 0);
				else
					SetAction(o, 1);
			}
			else
			{
				if(iAniIndex%2 == 0)
					SetAction(o, 2);
				else
					SetAction(o, 3);
			}
		}
		else if(o->CurrentAction == 2 && o->AnimationFrame >= 97)
		{
			SetAction(o, rand()%2);
		}
		else if(o->CurrentAction == 3 && o->AnimationFrame >= 98)
		{
			SetAction(o, rand()%2);
		}
		
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		return true;
	}
	else if(o->Type == 19)
	{
		if(o->CurrentAction == 0)
		{
			vec3_t vRelativePos, vWorldPos, vLight;
			Vector(0, 0, 0, vRelativePos);
			Vector(1.f, 1.f, 1.f, vLight);
			
			if((o->AnimationFrame >= 2 && o->AnimationFrame <= 5))
			{
				for(int i=0; i<b->NumBones; ++i)
				{
					b->TransformPosition(BoneTransform[i],vRelativePos,vWorldPos,false);
					CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				}
			}
			else if(o->AnimationFrame >= 11 && o->AnimationFrame <= 12)
			{
				b->TransformPosition(BoneTransform[6],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				b->TransformPosition(BoneTransform[7],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				b->TransformPosition(BoneTransform[8],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
			}
			else if(o->AnimationFrame >= 13 && o->AnimationFrame <= 14)
			{
				b->TransformPosition(BoneTransform[9],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				b->TransformPosition(BoneTransform[10],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				b->TransformPosition(BoneTransform[11],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
			}
			else if(o->AnimationFrame >= 15 && o->AnimationFrame <= 17)
			{
				for(int i=12; i<20; ++i)
				{
					b->TransformPosition(BoneTransform[i],vRelativePos,vWorldPos,false);
					CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				}
			}
			else if(o->AnimationFrame >= 19.5f)
			{
				o->CurrentAction = 1;
			}
			
			
			for(int i=0; i<b->NumBones; ++i)
			{
				b->TransformPosition(BoneTransform[i],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 8, 1.5f);
			}
		}
		else if(o->CurrentAction == 1)
		{
			if(rand()%40 == 30)
			{
				o->CurrentAction = 0;
			}
		}
		
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		return true;
	}
	else if(o->Type == 20)
	{
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_CHROME2|RENDER_DARK,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_CHROME8);
		b->RenderMesh(1, RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_CHROME8);
		
		if(o->CurrentAction == 0)
		{
			vec3_t vRelativePos, vWorldPos, vLight;
			Vector(0, 0, 0, vRelativePos);
			Vector ( 1.f, 1.f, 1.f, vLight );
			
			// �Ӹ�
			b->TransformPosition(BoneTransform[5],vRelativePos,vWorldPos,false);
			CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 8, 2.f );
			
			if(o->AnimationFrame <= 8)
			{
				// �Ӹ�
				b->TransformPosition(BoneTransform[6],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 8, 1.5f );
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7, 0.1f );
				
			}
			
			if(o->AnimationFrame >= 12)
			{
				// �԰�
				b->TransformPosition(BoneTransform[6],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 8, 2.f );
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7, 0.1f );
			}
			
			if(o->AnimationFrame <= 15)
			{
				// ����
				b->TransformPosition(BoneTransform[8],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 9, 2.f );
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7, 0.1f );
				
				b->TransformPosition(BoneTransform[11],vRelativePos,vWorldPos,false);
				CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 9, 2.f );
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7, 0.1f );
			}
			
			if(o->AnimationFrame >= 19)
			{
				o->CurrentAction = 1;
			}
		}
		else if(o->CurrentAction == 1)
		{
			if(rand()%40 == 25)
			{
				o->CurrentAction = 0;
			}
		}

		return true;
	}
	else if(o->Type == 21)
	{
		// ���� ���� ���ϸ��̼� �����̰�
		if(o->CurrentAction == 0)
		{
			if(o->AnimationFrame >= 4 && o->AnimationFrame <= 8)
			{
				vec3_t vRelativePos, vWorldPos, vLight;
				Vector(0, 0, 0, vRelativePos);
				Vector(1.f, 1.f, 1.f, vLight);
				// �Ծ� �� 
				b->TransformPosition(BoneTransform[7],vRelativePos,vWorldPos,false);
				// �� ����Ʈ
				CreateParticle ( BITMAP_WATERFALL_3, vWorldPos, o->Angle, vLight, 9, 0.5f );
				CreateParticle ( BITMAP_WATERFALL_5, vWorldPos, o->Angle, vLight, 7 );
				
				// 7, 16, 17, 21, 22
				// ���� ����Ʈ
				b->TransformPosition(BoneTransform[7],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 1.f);
				b->TransformPosition(BoneTransform[16],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.5f);
				b->TransformPosition(BoneTransform[17],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.7f);
				b->TransformPosition(BoneTransform[20],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.3f);
				b->TransformPosition(BoneTransform[21],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.3f);
				b->TransformPosition(BoneTransform[22],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.5f);
				b->TransformPosition(BoneTransform[23],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.3f);
				b->TransformPosition(BoneTransform[24],vRelativePos,vWorldPos,false);
				CreateParticle(BITMAP_WATERFALL_2, vWorldPos, o->Angle, vLight, 5, 0.3f);
			}
			
			if(o->AnimationFrame >= 19.f)
			{
				o->CurrentAction = 1;
			}
		}
		else if(o->CurrentAction == 1)
		{
			if(rand()%40 == 19)
			{
				o->CurrentAction = 0;
			}
		}

		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		return true;
	}
	else if(o->Type == 46 || o->Type == 53 || o->Type == 76)
	{
		o->m_bRenderAfterCharacter = true;

		return true;
	}
	else if(o->Type == 57)
	{
		vec3_t vRelativePos, vWorldPos;
		Vector(0, 0, 0, vRelativePos);
		b->TransformPosition(BoneTransform[1],vRelativePos,vWorldPos,false);
		vec3_t vLight;
		Vector(1.0f, 1.0f, 1.0f, vLight);
		//CreateEffect(BITMAP_GATHERING,vWorldPos,o->Angle,vLight,3,o);

		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

		return true;
	}
	else if(o->Type == 68 || o->Type == 69 || o->Type == 71)
	{
		float fLumi = (sinf(WorldTime*0.001f) + 1.f) * 0.5f + 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,0,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);		

		return true;
	}
	else if(o->Type == MODEL_WARP || o->Type == MODEL_WARP2 || o->Type == MODEL_WARP3)
	{
		b->BodyLight[0] = 1.0f;
		b->BodyLight[1] = 1.0f;
		b->BodyLight[2] = 1.0f;
		o->BlendMeshLight = 1.0f;
		
		if(o->Type == MODEL_WARP)
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_WARP2)
		{
			b->RenderBody(RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_WARP3)
		{
			b->RenderMesh ( 0, RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		}

		return true;
	}
	else if(o->Type == MODEL_WARP4 || o->Type == MODEL_WARP5 || o->Type == MODEL_WARP6)
	{
		// ���� ��Ŭ���� �����ʿ� �� �� �ִ� ���¶�� ������ �ϰ�
		// ��Ŭ���� �����ʿ� �� �� ���� ���¶�� ������ ���Ѵ�.
		if(m_bCanGoBossMap == false)
		{
			return true;
		}
		
		b->BodyLight[0] = 0.5f;
		b->BodyLight[1] = 0.6f;
		b->BodyLight[2] = 1.0f;
		o->BlendMeshLight = 0.8f;
		
		if(o->Type == MODEL_WARP4)
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_WARP5)
		{
			b->RenderBody(RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_WARP6)
		{
			b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		}

		return true;
	}
	else if(o->Type == 82)	// ���� ����Ʈ ������Ʈ
	{
		if(m_bCanGoBossMap == false)
		{
			o->AnimationFrame = 0;
			o->PriorAnimationFrame = 0;
		}

		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

		return true;
	}
	else if( (o->Type >= MODEL_MONSTER01+145 && o->Type <= MODEL_MONSTER01+153)
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION	// Ȯ��� �߰� ���͵�
		|| o->Type == MODEL_MONSTER01+205
		|| o->Type == MODEL_MONSTER01+206 
		|| o->Type == MODEL_MONSTER01+208 
		|| o->Type == MODEL_MONSTER01+207
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
		)
	{
		RenderMonster(o, b, ExtraMon);

		return true;
	}

	return false;
}

bool CGM_Raklion::RenderMonster(OBJECT* o, BMD* b, bool ExtraMon)
{
	switch(o->Type)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+145:	// ���̽���Ŀ
		{
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

			return true;
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef PJH_GIANT_MAMUD
	case MODEL_MONSTER01+146:	// ���̾�Ʈ�Ÿӵ�
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

			//b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			//b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			//b->RenderMesh(2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);

			b->RenderMesh(1, RENDER_CHROME6|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			
			return true;
		}
		break;
		
#endif // PJH_GIANT_MAMUD	

#ifdef ADD_RAKLION_MOB_ICEGIANT	
	case MODEL_MONSTER01+147:	// ���̽� ���̾�Ʈ
		if (o->CurrentAction != MONSTER01_DIE)
		{
			Vector(1.0f, 1.0f, 1.0f, b->BodyLight);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME7, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(3, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);

			return true;
		}
		break;
#endif	// ADD_RAKLION_MOB_ICEGIANT

#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case MODEL_MONSTER01+148:	// ��ƾ
		{
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			
			return true;
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN

#ifdef ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+149:	// ���̾� ����Ʈ
		if (o->CurrentAction == MONSTER01_DIE)
		{
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else
		{
			float fLumi = (sinf(WorldTime*0.01f) + 1.0f) * 0.4f + 0.2f;
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_IRONKNIGHT_BODY_BRIGHT);
			b->RenderMesh(1, RENDER_TEXTURE,0.4f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,0.7f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_CHROME|RENDER_BRIGHT,0.5f,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}

		return true;

#endif	// ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+150:	// ������ (��������)
		{
			// ��ü
			//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	
			// ����
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			// ����
			b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			// ����
			b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			// �Ӹ�ī��
			b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			// ����
			b->RenderMesh(4, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			// ���� �ȿ� ����
			b->RenderMesh(5, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,5,o->BlendMeshLight,(int)WorldTime%10000*0.0002f,(int)WorldTime%10000*0.0002f,o->HiddenMesh);
			
			// ȿ�� �κ�
			float fLumi2 = (sinf(WorldTime*0.002f) + 1.f) * 0.5f;
			// ����
			b->RenderMesh(4, RENDER_TEXTURE|RENDER_CHROME4|RENDER_BRIGHT, o->Alpha, o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			// ����
			b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi2, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SERUFAN_ARM_R);
			b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi2, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SERUFAN_ARM_R);
			b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi2, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SERUFAN_ARM_R);
			b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi2, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SERUFAN_ARM_R);

			if(m_byDetailState >= BATTLE_OF_SELUPAN_PATTERN_2)
			{
				// ���� ũ��
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_CHROME6|RENDER_BRIGHT, o->Alpha, o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_MAGIC_EMBLEM);
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_CHROME4|RENDER_BRIGHT, o->Alpha, o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			}
			
			// �Ӹ�ī��
			b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

			return true;
		}
		break;
	case MODEL_MONSTER01+151:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+152:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+153:	// �Ŵ� �Ź̾�
		{
			if(o->CurrentAction == MONSTER01_DIE)
			{
				float fBlendLight = 20.f - o->AnimationFrame;
				fBlendLight /= 15;
				vec3_t vOriginPos;
				VectorCopy(o->Position, vOriginPos);

				for(int i=0; i<3; ++i)
				{
					if(i == 0)
					{
						if(o->Type == MODEL_MONSTER01+151)
							o->Position[0] += 60;		
						else
							o->Position[0] += 100;
					}
					else if(i == 1)
					{
						if(o->Type == MODEL_MONSTER01+151)
							o->Position[1] += 60;		
						else
							o->Position[1] += 100;
					}
					else
					{
						VectorCopy(vOriginPos, o->Position);
					}

					Calc_RenderObject(o, true, false, 0);
					b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,3,fBlendLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}

				//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else
			{
				//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				
				vec3_t vOriginPos;
				VectorCopy(o->Position, vOriginPos);

				for(int i=0; i<3; ++i)
				{
					if(i == 0)
					{
						if(o->Type == MODEL_MONSTER01+151)
							o->Position[0] += 60;		
						else
							o->Position[0] += 100;
					}
					else if(i == 1)
					{
						if(o->Type == MODEL_MONSTER01+151)
							o->Position[1] += 60;		
						else
							o->Position[1] += 100;
					}
					else
					{
						VectorCopy(vOriginPos, o->Position);
					}

					Calc_RenderObject(o, true, false, 0);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

					// �߱� ȿ��
					vec3_t vPos, vLight;
					float fLumi = (sinf(WorldTime*0.004f) + 1.2f) * 0.5f + 0.1f;
					Vector(0.1f*fLumi, 0.6f*fLumi, 0.7f*fLumi, vLight);
					if(o->Type == MODEL_MONSTER01+151)
					{
						b->TransformByObjectBone(vPos, o, 57);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
					}
					else if(o->Type == MODEL_MONSTER01+152)
					{
						b->TransformByObjectBone(vPos, o, 95);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
						b->TransformByObjectBone(vPos, o, 115);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
					}
					else
					{
						b->TransformByObjectBone(vPos, o, 95);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
						b->TransformByObjectBone(vPos, o, 115);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
						b->TransformByObjectBone(vPos, o, 173);
						CreateSprite(BITMAP_LIGHT, vPos, 3.f, vLight, o);
						if(rand()%100 == 0)
							CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 33, 1.f);
					}
				}
			}
			
			return true;
		}
		break;
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	case MODEL_MONSTER01+205:	// ��ũ ���̾�Ʈ�Ÿӵ�
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_CHROME6|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			
			return true;
		}
		break;
	case MODEL_MONSTER01+206:	// ��ũ ���̽� ���̾�Ʈ
		{
			if (o->CurrentAction != MONSTER01_DIE)
			{
				Vector(1.0f, 1.0f, 1.0f, b->BodyLight);
				b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME7, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(3, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh(3, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				
				return true;
			}
		}
		break;
	case MODEL_MONSTER01+207:	// ��ũ ��ƾ
		{
			b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		break;
	case MODEL_MONSTER01+208:	// ��ũ ���̾� ����Ʈ
		{
			if (o->CurrentAction == MONSTER01_DIE)
			{
				b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else
			{
				float fLumi = (sinf(WorldTime*0.01f) + 1.0f) * 0.4f + 0.2f;
				b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_IRONKNIGHT_BODY_BRIGHT);
				b->RenderMesh(1, RENDER_TEXTURE,0.4f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,0.7f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(1, RENDER_CHROME|RENDER_BRIGHT,0.5f,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			
			return true;
		}
		break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION

	}

	return false;
}

bool CGM_Raklion::RenderObjectVisual( OBJECT* o, BMD* b )
{
	switch(o->Type)
	{
	case 70:		// �����Ķ��ҹڽ�
		{
			vec3_t vLight;
			Vector(0.1f, 0.4f, 1.0f, vLight);
			// ������ �� �����!!
			switch(rand()%3)
			{
			case 0:
				CreateParticle(BITMAP_FIRE_HIK1_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��
				break;
			case 1:
				CreateParticle(BITMAP_FIRE_HIK2_MONO,o->Position,o->Angle,vLight,6,o->Scale);	// ��
				break;
			case 2:
				CreateParticle(BITMAP_FIRE_HIK3_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��
				break;
			}
			// ������ �� �����!!
			CreateParticle(BITMAP_FIRE_HIK1_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��

			return true;
		}
		break;
	case 80:		// ���󻡰��ҹڽ�
		{
			vec3_t vLight;
			Vector(0.7f, 0.2f, 0.1f, vLight);
			// ������ �� �����!!
			switch(rand()%3)
			{
			case 0:
				CreateParticle(BITMAP_FIRE_HIK1_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��
				break;
			case 1:
				CreateParticle(BITMAP_FIRE_HIK2_MONO,o->Position,o->Angle,vLight,6,o->Scale);	// ��
				break;
			case 2:
				CreateParticle(BITMAP_FIRE_HIK3_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��
				break;
			}
			// ������ �� �����!!
			CreateParticle(BITMAP_FIRE_HIK1_MONO,o->Position,o->Angle,vLight,2,o->Scale);	// ��

			return true;
		}
		break;
	}
	
	return false;
}

bool CGM_Raklion::RenderMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b)
{
	vec3_t vPos, vRelative, vLight;

	switch(o->Type)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+145:	// ���̽���Ŀ
		{

		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+146:	// ���̾�Ʈ �Ÿӵ�
		{
			
		}
		break;
	case MODEL_MONSTER01+147:	// ���̽� ���̾�Ʈ
#ifdef ADD_RAKLION_MOB_ICEGIANT
		if (o->CurrentAction == MONSTER01_ATTACK2 && o->AnimationFrame > 7.4f && o->AnimationFrame < 7.7f)
		{
			CreateInferno(o->Position, 5);
		}
		else if (o->CurrentAction == MONSTER01_DIE && o->LifeTime == 100)
		{
			const int nBonesCount = 8;
			int iBones[nBonesCount] = { 4, 7, 10, 22, 39, 44, 12, 24 };
			for (int i = 0; i < nBonesCount; ++i)
			{
				Vector(0.3f, 0.6f, 1.0f, vLight);
				
				b->TransformByObjectBone(vPos, o, iBones[i]);
				for (int j = 0; j < 12; ++j)
					CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,vPos,o->Angle,vLight,0);
			}

			o->LifeTime = 90;	// �� ���� ����(������ ������ ��� o->LifeTime ���)
			o->m_bRenderShadow = false;
			
			Vector(1.0f, 1.0f, 1.0f,vLight);
			
			b->TransformByObjectBone(vPos, o, 5);
			CreateEffect(MODEL_ICE_GIANT_PART1,vPos,o->Angle,vLight,0,o,0,0);
			b->TransformByObjectBone(vPos, o, 3);
			CreateEffect(MODEL_ICE_GIANT_PART2,vPos,o->Angle,vLight,0,o,0,0);
			b->TransformByObjectBone(vPos, o, 11);
			CreateEffect(MODEL_ICE_GIANT_PART3,vPos,o->Angle,vLight,0,o,0,0);
			b->TransformByObjectBone(vPos, o, 23);
			CreateEffect(MODEL_ICE_GIANT_PART4,vPos,o->Angle,vLight,0,o,0,0);
			b->TransformByObjectBone(vPos, o, 39);
			CreateEffect(MODEL_ICE_GIANT_PART5,vPos,o->Angle,vLight,0,o,0,0);
			b->TransformByObjectBone(vPos, o, 45);
			CreateEffect(MODEL_ICE_GIANT_PART6,vPos,o->Angle,vLight,0,o,0,0);
		}
#endif	// ADD_RAKLION_MOB_ICEGIANT
		break;
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case MODEL_MONSTER01+148:	// ��ƾ
		{
			
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+149:	// ���̾� ����Ʈ
		{
			// �� �����ӿ� �˱�
			vec3_t  Light;
			Vector(1.0f, 1.2f, 2.f, Light);

			vec3_t StartPos, StartRelative;
			vec3_t EndPos, EndRelative;
			
			float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
			float fSpeedPerFrame = fActionSpeed/10.f;
			float fAnimationFrame = o->AnimationFrame - fActionSpeed;
			for(int i=0; i<10; i++) 
			{
				b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);

				Vector(0.f, 0.f, 0.f, StartRelative);
				Vector(0.f, 0.f, 0.f, EndRelative);

				b->TransformPosition(BoneTransform[35], StartRelative, StartPos, false);
				b->TransformPosition(BoneTransform[36], EndRelative, EndPos, false);
				CreateBlur(c, StartPos, EndPos, Light, 3);
				
				fAnimationFrame += fSpeedPerFrame;
			}

			// �⺻ ���� ����Ʈ
			int iBones[] = { 20, 37, 45, 51 };
#ifdef _VS2008PORTING
			for (int i = 0; i < 4; ++i)
#else // _VS2008PORTING
			for (i = 0; i < 4; ++i)
#endif // _VS2008PORTING
			{
				if (rand()%6 > 0) continue;

				if (rand()%3 > 0)
				{
					Vector(0.3f, 0.6f, 1.0f, vLight);
				}
				else
				{
					Vector(0.8f, 0.8f, 0.8f, vLight);
				}

				b->TransformByObjectBone(vPos, o, iBones[i]);
				CreateParticle(BITMAP_SMOKE,vPos,o->Angle,vLight,50,1.0f);	// ����
				CreateParticle(BITMAP_SMOKELINE1+rand()%3,vPos,o->Angle,vLight,2,0.8f);	// 3�� ����
			}

			if (o->CurrentAction == MONSTER01_ATTACK2)
			{
				extern int g_iLimitAttackTime;

	// 			if ( 8 == c->AttackTime)
	// 			{
	// 				PlayBuffer(SOUND_SKILL_SWORD2);
	// 			}

				if ( 2 <= c->AttackTime && c->AttackTime <= 8)
				{	// �� ������
					for ( int j = 0; j < 3; ++j)
					{
						vec3_t CurPos;
						VectorCopy( o->Position, CurPos);
						CurPos[2] += 120.0f;
						vec3_t TempPos;
						GetNearRandomPos( CurPos, 300, TempPos);
						float fDistance = 1400.0f;
						TempPos[0] += -fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
						TempPos[1] += fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
						CreateJoint( MODEL_SPEARSKILL, TempPos, TempPos, o->Angle, 2, o, 40.0f);
					}
				}
				if ( c->AttackTime <= 8)
				{	// �� ���� �� ��ġ
					vec3_t Position2 = { 0.0f, 0.0f, 0.0f};
					b->TransformPosition(o->BoneTransform[26],Position2,o->m_vPosSword,true);

					float fDistance = 300.0f;
					o->m_vPosSword[0] += fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
					o->m_vPosSword[1] += -fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
				}
				if ( 6 <= c->AttackTime && c->AttackTime <= 12)
				{	// ���� �����
					vec3_t Position;
					vec3_t Position2 = { 0.0f, 0.0f, 0.0f};

					b->TransformPosition(o->BoneTransform[26],Position2,Position,true);

					float fDistance = 100.0f + ( float)( c->AttackTime - 8) * 10.0f;
					Position[0] += fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
					Position[1] += -fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
					vec3_t Light = { 1.0f, 1.0f, 1.0f};
					CreateEffect( MODEL_SPEAR, Position, o->Angle, Light, 1, o);
	// 				CreateEffect( MODEL_SPEAR, Position, o->Angle, Light, 1, o);

					if(c->TargetCharacter != -1)
					{
						CHARACTER *tc = &CharactersClient[c->TargetCharacter];
						if ( c->TargetCharacter != -1)
						{
							OBJECT *to = &tc->Object;
							if ( 10 <= c->AttackTime && to->Live)
							{
								to->m_byHurtByOneToOne = 35;
							}
						}
					}
				}
				if ( c->AttackTime>=12 )
				{
					c->AttackTime = g_iLimitAttackTime;
					
					CreateEffect ( MODEL_COMBO, o->Position, o->Angle, o->Light );
	//				PlayBuffer(SOUND_COMBO);
				}
			}
			else if (o->CurrentAction == MONSTER01_DIE && o->AnimationFrame < 1.0f)
			{
				int iBones[] = { 20, 37, 45, 51 };
				for (int i = 0; i < 4; ++i)
				{
					Vector(0.3f, 0.5f, 1.0f, vLight);

					b->TransformByObjectBone(vPos, o, iBones[i]);
					for (int j = 0; j < 6; ++j)
						CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,vPos,o->Angle,vLight,0);
				}
			}
		}
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+150:	// ������ (��������)
		{
			// �˱� ȿ��
			vec3_t  Light;
			Vector(1.0f, 1.2f, 2.f, Light);
			
			vec3_t StartPos, StartRelative;
			vec3_t EndPos, EndRelative;
			
			float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
			float fSpeedPerFrame = fActionSpeed/10.f;
			float fAnimationFrame = o->AnimationFrame - fActionSpeed;
			for(int i=0; i<10; i++) 
			{
				b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);
				
				Vector(0.f, 0.f, 0.f, StartRelative);
				Vector(0.f, 0.f, 0.f, EndRelative);
				
				b->TransformPosition(BoneTransform[69], StartRelative, StartPos, false);
				b->TransformPosition(BoneTransform[73], EndRelative, EndPos, false);
				CreateBlur(c, StartPos, EndPos, Light, 0);
				
				fAnimationFrame += fSpeedPerFrame;
			}

			// ����Ʈ ����
			VectorCopy(o->Position, b->BodyOrigin);
			Vector(0.0f, 0.0f, 0.0f, vRelative);

			float fLumi1 = (sinf(WorldTime*0.004f) + 1.f) * 0.25f;
			float fLumi2 = (sinf(WorldTime*0.004f) + 1.f) * 0.2f;

			// �Ӹ�
			Vector(0.3f+fLumi1, 0.6f+fLumi1, 1.0f+fLumi1, vLight);
			Vector(0.0f, 10.0f, 0.0f, vRelative);
			b->TransformByObjectBone(vPos, o, 9, vRelative);
			// flare01.jpg
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f+fLumi2, vLight, o);
			CreateSprite(BITMAP_LIGHT, vPos, 2.0f+fLumi2, vLight, o);
			CreateSprite(BITMAP_LIGHT, vPos, 3.0f+fLumi2, vLight, o);

			// ������
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			fLumi1 = (sinf(WorldTime*0.004f) + 1.f) * 0.1f;
			Vector(0.1f+fLumi1, 0.2f+fLumi1, 1.0f+fLumi1, vLight);
			Vector(0.0f, 0.0f, 0.0f, vRelative);
			b->TransformByObjectBone(vPos, o, 70);
			// flare01.jpg
			CreateSprite(BITMAP_LIGHT, vPos, 2.1f+fLumi2, vLight, o, (int)WorldTime*0.08f);
			// shiny05.jpg
			CreateSprite(BITMAP_SHINY+6, vPos, 1.8f+fLumi2, vLight, o);

			Vector(0.0f, 0.0f, 0.0f, vRelative);
			b->TransformByObjectBone(vPos, o, 74);
			// flare01.jpg
			CreateSprite(BITMAP_LIGHT, vPos, 2.1f+fLumi2, vLight, o, (int)WorldTime*0.08f);
			// shiny05.jpg
			CreateSprite(BITMAP_SHINY+6, vPos, 1.8f+fLumi2, vLight, o);

			b->TransformByObjectBone(vPos, o, 71);
			// clouds2.jpg
			CreateSprite(BITMAP_EVENT_CLOUD, vPos, 0.6f,vLight,o,-(int)WorldTime*0.1f);	
			CreateSprite(BITMAP_EVENT_CLOUD, vPos, 0.40f,vLight,o,-(int)WorldTime*0.2f);	
			// flare01.jpg
			CreateSprite(BITMAP_LIGHT, vPos, 2.3f+fLumi2, vLight, o);
			// Shiny02.jpg
			CreateSprite(BITMAP_SHINY+1, vPos, 2.3f+fLumi2, vLight, o, (int)WorldTime*0.08f);
			// shiny05.jpg
			CreateSprite(BITMAP_SHINY+6, vPos, 2.3f+fLumi2, vLight, o, (int)WorldTime*0.15f);
			// ������� ������ ��ƼŬ
			CreateParticle( BITMAP_SPARK+1, vPos, o->Angle, vLight, 11, 1.5f );

			b->TransformByObjectBone(vPos, o, 72);
			// flare01.jpg
			CreateSprite(BITMAP_LIGHT, vPos, 1.8f+fLumi2, vLight, o);
			// shiny05.jpg
			CreateSprite(BITMAP_SHINY+6, vPos, 1.3f+fLumi2, vLight, o);

			return true;
		}
		break;
	case MODEL_MONSTER01+151:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+152:	// �Ŵ� �Ź̾�
	case MODEL_MONSTER01+153:	// �Ŵ� �Ź̾�
		{
			return true;
		}
		break;
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	case MODEL_MONSTER01+205:	// ��ũ ���̾�Ʈ �޸ӵ�
		{

		}
		break;
	case MODEL_MONSTER01+206:	// ��ũ ���̽� ���̾�Ʈ
		{
			if (o->CurrentAction == MONSTER01_ATTACK2 && o->AnimationFrame > 7.4f && o->AnimationFrame < 7.7f)
			{
				CreateInferno(o->Position, 5);
			}
			else if (o->CurrentAction == MONSTER01_DIE && o->LifeTime == 100)
			{
				const int nBonesCount = 8;
				int iBones[nBonesCount] = { 4, 7, 10, 22, 39, 44, 12, 24 };
				for (int i = 0; i < nBonesCount; ++i)
				{
					Vector(0.3f, 0.6f, 1.0f, vLight);
					
					b->TransformByObjectBone(vPos, o, iBones[i]);
					for (int j = 0; j < 12; ++j)
						CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,vPos,o->Angle,vLight,0);
				}
				
				o->LifeTime = 90;	// �� ���� ����(������ ������ ��� o->LifeTime ���)
				o->m_bRenderShadow = false;
				
				Vector(1.0f, 1.0f, 1.0f,vLight);
				
				b->TransformByObjectBone(vPos, o, 5);
				CreateEffect(MODEL_ICE_GIANT_PART1,vPos,o->Angle,vLight,0,o,0,0);
				b->TransformByObjectBone(vPos, o, 3);
				CreateEffect(MODEL_ICE_GIANT_PART2,vPos,o->Angle,vLight,0,o,0,0);
				b->TransformByObjectBone(vPos, o, 11);
				CreateEffect(MODEL_ICE_GIANT_PART3,vPos,o->Angle,vLight,0,o,0,0);
				b->TransformByObjectBone(vPos, o, 23);
				CreateEffect(MODEL_ICE_GIANT_PART4,vPos,o->Angle,vLight,0,o,0,0);
				b->TransformByObjectBone(vPos, o, 39);
				CreateEffect(MODEL_ICE_GIANT_PART5,vPos,o->Angle,vLight,0,o,0,0);
				b->TransformByObjectBone(vPos, o, 45);
				CreateEffect(MODEL_ICE_GIANT_PART6,vPos,o->Angle,vLight,0,o,0,0);
			}
		}
		break;
	case MODEL_MONSTER01+208:	// ��ũ ���̾� ����Ʈ
		{
			// �� �����ӿ� �˱�
			vec3_t  Light;
			Vector(1.0f, 1.2f, 2.f, Light);

			vec3_t StartPos, StartRelative;
			vec3_t EndPos, EndRelative;
			
			float fActionSpeed = b->Actions[o->CurrentAction].PlaySpeed;
			float fSpeedPerFrame = fActionSpeed/10.f;
			float fAnimationFrame = o->AnimationFrame - fActionSpeed;
			for(int i=0; i<10; i++) 
			{
				b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);

				Vector(0.f, 0.f, 0.f, StartRelative);
				Vector(0.f, 0.f, 0.f, EndRelative);

				b->TransformPosition(BoneTransform[35], StartRelative, StartPos, false);
				b->TransformPosition(BoneTransform[36], EndRelative, EndPos, false);
				CreateBlur(c, StartPos, EndPos, Light, 3);
				
				fAnimationFrame += fSpeedPerFrame;
			}

			// �⺻ ���� ����Ʈ
			int iBones[] = { 20, 37, 45, 51 };
#ifdef _VS2008PORTING
			for (int i = 0; i < 4; ++i)
#else // _VS2008PORTING
			for (i = 0; i < 4; ++i)
#endif // _VS2008PORTING
			{
				if (rand()%6 > 0) continue;

				if (rand()%3 > 0)
				{
					Vector(0.3f, 0.6f, 1.0f, vLight);
				}
				else
				{
					Vector(0.8f, 0.8f, 0.8f, vLight);
				}

				b->TransformByObjectBone(vPos, o, iBones[i]);
				CreateParticle(BITMAP_SMOKE,vPos,o->Angle,vLight,50,1.0f);	// ����
				CreateParticle(BITMAP_SMOKELINE1+rand()%3,vPos,o->Angle,vLight,2,0.8f);	// 3�� ����
			}

			if (o->CurrentAction == MONSTER01_ATTACK2)
			{
				extern int g_iLimitAttackTime;

	// 			if ( 8 == c->AttackTime)
	// 			{
	// 				PlayBuffer(SOUND_SKILL_SWORD2);
	// 			}

				if ( 2 <= c->AttackTime && c->AttackTime <= 8)
				{	// �� ������
					for ( int j = 0; j < 3; ++j)
					{
						vec3_t CurPos;
						VectorCopy( o->Position, CurPos);
						CurPos[2] += 120.0f;
						vec3_t TempPos;
						GetNearRandomPos( CurPos, 300, TempPos);
						float fDistance = 1400.0f;
						TempPos[0] += -fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
						TempPos[1] += fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
						CreateJoint( MODEL_SPEARSKILL, TempPos, TempPos, o->Angle, 2, o, 40.0f);
					}
				}
				if ( c->AttackTime <= 8)
				{	// �� ���� �� ��ġ
					vec3_t Position2 = { 0.0f, 0.0f, 0.0f};
					b->TransformPosition(o->BoneTransform[26],Position2,o->m_vPosSword,true);

					float fDistance = 300.0f;
					o->m_vPosSword[0] += fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
					o->m_vPosSword[1] += -fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
				}
				if ( 6 <= c->AttackTime && c->AttackTime <= 12)
				{	// ���� �����
					vec3_t Position;
					vec3_t Position2 = { 0.0f, 0.0f, 0.0f};

					b->TransformPosition(o->BoneTransform[26],Position2,Position,true);

					float fDistance = 100.0f + ( float)( c->AttackTime - 8) * 10.0f;
					Position[0] += fDistance * sinf( o->Angle[2]*Q_PI/180.0f);
					Position[1] += -fDistance * cosf( o->Angle[2]*Q_PI/180.0f);
					vec3_t Light = { 1.0f, 1.0f, 1.0f};
					CreateEffect( MODEL_SPEAR, Position, o->Angle, Light, 1, o);
	// 				CreateEffect( MODEL_SPEAR, Position, o->Angle, Light, 1, o);

					if(c->TargetCharacter != -1)
					{
						CHARACTER *tc = &CharactersClient[c->TargetCharacter];
						if ( c->TargetCharacter != -1)
						{
							OBJECT *to = &tc->Object;
							if ( 10 <= c->AttackTime && to->Live)
							{
								to->m_byHurtByOneToOne = 35;
							}
						}
					}
				}
				if ( c->AttackTime>=12 )
				{
					c->AttackTime = g_iLimitAttackTime;
					
					CreateEffect ( MODEL_COMBO, o->Position, o->Angle, o->Light );
	//				PlayBuffer(SOUND_COMBO);
				}
			}
			else if (o->CurrentAction == MONSTER01_DIE && o->AnimationFrame < 1.0f)
			{
				int iBones[] = { 20, 37, 45, 51 };
				for (int i = 0; i < 4; ++i)
				{
					Vector(0.3f, 0.5f, 1.0f, vLight);

					b->TransformByObjectBone(vPos, o, iBones[i]);
					for (int j = 0; j < 6; ++j)
						CreateEffect(MODEL_EFFECT_BROKEN_ICE0+rand()%3,vPos,o->Angle,vLight,0);
				}
			}
		}
		break;
	case MODEL_MONSTER01+207:	// ��ũ ��ƾ
		{

		}
		break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}

	return true;
}

void CGM_Raklion::RenderAfterObjectMesh(OBJECT* o, BMD* b, bool ExtraMon)
{
	if(o->Type == 46 || o->Type == 53)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
	else if(o->Type == 76)
	{
		float R, G, B;
		R = (float)sinf(WorldTime*0.002f) * 0.2f + 0.5f;
		G = (float)sinf(WorldTime*0.0015f) * 0.2f + 0.5f;
		B = (float)sinf(WorldTime*0.0014f) * 0.2f + 0.5f;
		Vector(R, G, B, o->Light);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
}

bool CGM_Raklion::CreateSnow( PARTICLE* o )
{
	if(IsIceCity() == false)
		return false;

	o->Type = BITMAP_LEAF1;
	o->Scale = (float)(rand()%10+3);
	if(rand()%10 == 0)
	{
		o->Scale = (float)(rand()%3+10);
	}

	Vector(Hero->Object.Position[0]+(float)(rand()%1600-800),
		Hero->Object.Position[1]+(float)(rand()%1400-500),
		Hero->Object.Position[2]+(float)(rand()%200+200),
		o->Position);
	Vector(-(float)(rand()%30+50),0.f,0.f,o->Angle);
	vec3_t Velocity;
	Vector(0.f,0.f,-(float)(rand()%20+30),Velocity);
	float Matrix[3][4];
	AngleMatrix(o->Angle,Matrix);
	VectorRotate(Velocity,Matrix,o->Velocity);
	
	return true;
}

void CGM_Raklion::RenderBaseSmoke()
{
	EnableAlphaBlend();
	glColor3f(0.4f,0.4f,0.45f);
	float WindX2 = (float)((int)WorldTime%100000)*0.0006f; 
	float WindY2 = -(float)((int)WorldTime%100000)*0.0006f; 
	RenderBitmapUV(BITMAP_CHROME+3,0.f,0.f,640.f,480.f-45.f,WindX2,WindY2,3.0f,2.0f);
	float WindX = (float)((int)WorldTime%100000)*0.0001f; 
	RenderBitmapUV(BITMAP_CHROME+2,0.f,0.f,640.f,480.f-45.f,WindX,0.f,0.3f,0.3f);
}

bool IsIceCity()
{
	if(World >= WD_57ICECITY && World <= WD_58ICECITY_BOSS)
	{
		return true;
	}
#ifdef YDG_ADD_MAP_DOPPELGANGER1
	else if(World == WD_65DOPPLEGANGER1)	// ��Ŭ���� ���̽�
	{
		return true;
	}
#endif	// YDG_ADD_MAP_DOPPELGANGER1
		
	return false;
}

bool CGM_Raklion::SetCurrentActionMonster(CHARACTER* c, OBJECT* o)
{
	if(IsIceCity() == false)
		return false;

	
	switch(c->MonsterIndex) 
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 454:	// ���̽� ��Ŀ
		{
			if (c->MonsterSkill == 29)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
			}
			return true;
		}
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 455:	// ���̾�Ʈ �Ÿӵ�
		{
			if (c->MonsterSkill == 30)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
			}
			return true;
		}
		break;
#ifdef ADD_RAKLION_MOB_ICEGIANT
	case 456:	// ���̽� ���̾�Ʈ
		{
			if (c->MonsterSkill == 31)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
			}
			return true;
		}
		break;
#endif	// ADD_RAKLION_MOB_ICEGIANT
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case 457:	// ��ƾ
		{
			if (c->MonsterSkill == 32)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
			}
			return true;
		}
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
	case 458:	// ���̾� ����Ʈ
		{
			if (c->MonsterSkill == 33)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
			}
			return true;
		}
		break;
	case 459:	// ������ (��������)
		{
			SetBossMonsterAction(c, o);
			return true;
		}
		break;
	case 460:	// �Ŵ� �Ź̾�
	case 461:	// �Ŵ� �Ź̾�
	case 462:	// �Ŵ� �Ź̾�	
		{
			return false;
		}
		break;
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
	case 562:	// ��ũ ���̾�Ʈ �޸ӵ�
		{
			if (c->MonsterSkill == ATMON_SKILL_EX_DARKMEMUD_ATTACKSKILL)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
				c->MonsterSkill = -1;
			}
			return true;
		}
		break;
	case 563:	// ��ũ ���̽� ���̾�Ʈ
		{
			if (c->MonsterSkill == ATMON_SKILL_EX_DARKGIANT_ATTACKSKILL)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
				c->MonsterSkill = -1;
			}
			return true;
		}
		break;
	case 565:	// ��ũ ���̾� ����Ʈ
		{
			if (c->MonsterSkill == ATMON_SKILL_EX_DARKAIONNIGHT_ATTACKSKILL)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
				c->MonsterSkill = -1;
			}
			return true;
		}
		break;
	case 564:	// ��ũ ��ƾ
		{
			if (c->MonsterSkill == ATMON_SKILL_EX_DARKCOOLERTIN_ATTACKSKILL)
			{
				SetAction(o, MONSTER01_ATTACK2);
				c->MonsterSkill = -1;	// ��ų ���ݰ� �Ϲ� ������ �ִ� ��� ��ų ���� �� �ʱ�ȭ �ؾߵ�.
			}
			else
			{
				SetAction(o, MONSTER01_ATTACK1);
				c->MonsterSkill = -1;
			}
			return true;
		}
		break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}
	
	return false;
}

void CGM_Raklion::SetBossMonsterAction(CHARACTER* c, OBJECT* o)
{
	if(c->MonsterSkill == 37 
		|| !(c->MonsterSkill >= 34 && c->MonsterSkill <= 42)
		|| m_bBossHeightMove == true)
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ġ ����");
#endif // CONSOLE_DEBUG		
		// ���彺ų�� ��ġ ���� ������
		c->Object.Position[2] = RequestTerrainHeight(o->Position[0], o->Position[1]);
		m_bBossHeightMove = false;
	}

	if(c->MonsterSkill == 34)	// ������
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ������");
#endif // CONSOLE_DEBUG	
		SetAction(o, MONSTER01_ATTACK2);	
	}
	else if(c->MonsterSkill == 35)	// �ñ���ǳ
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : �ñ���ǳ");
#endif // CONSOLE_DEBUG		
		SetAction(o, MONSTER01_ATTACK1);	
	}
	else if(c->MonsterSkill == 36)	// �ñ����
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : �ñ����");
#endif // CONSOLE_DEBUG	
		SetAction(o, MONSTER01_ATTACK3);	
	}
	else if(c->MonsterSkill == 37)	// ����(���� ��ų)
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ����");
#endif // CONSOLE_DEBUG		
		
		SetAction(o, MONSTER01_APEAR);
	}
	else if(c->MonsterSkill == 38)	// ��ȯ
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ��ȯ");
#endif // CONSOLE_DEBUG		
		SetAction(o, MONSTER01_ATTACK4);
		PlayBuffer(SOUND_RAKLION_SERUFAN_WORD4);
	}
	else if(c->MonsterSkill == 39)	// ġ��
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ġ��");
#endif // CONSOLE_DEBUG	
		SetAction(o, MONSTER01_ATTACK4);
		PlayBuffer(SOUND_RAKLION_SERUFAN_CURE);
		
		// ġ�� ����Ʈ
		vec3_t vLight, vPos, vAngle;
		Vector(1.f, 1.f, 1.f, vLight);
		for(int i=0; i<20; ++i)
		{
			Vector(0.f, 0.f, rand()%360, vAngle);
			VectorCopy( o->Position, vPos);
			vPos[0] += rand()%400-200;
			vPos[1] += rand()%400-200;
			vPos[2] -= 100.f;
			CreateJoint(BITMAP_FLARE, vPos, vPos, vAngle, 2, NULL, 40);
		}
		
		Vector(1.f, 0.5f, 0.1f, vLight);
		CreateEffect(BITMAP_MAGIC+1, o->Position, o->Angle, vLight, 13, o, -1, 0, 0, 0, 8.f);
		CreateEffect(BITMAP_MAGIC+1, o->Position, o->Angle, vLight, 13, o, -1, 0, 0, 0, 8.f);
	}
	else if(c->MonsterSkill == 40) // �󸮱�
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : freeze");
#endif // CONSOLE_DEBUG		
		SetAction(o, MONSTER01_ATTACK4);
		PlayBuffer(SOUND_RAKLION_SERUFAN_WORD3);
	}
	else if(c->MonsterSkill == 41) // �����̵�
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : �����̵�");
#endif // CONSOLE_DEBUG	
	}
	else if(c->MonsterSkill == 42) // ����
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ����");
#endif // CONSOLE_DEBUG	
		SetAction(o, MONSTER01_ATTACK4);
		
		vec3_t vLight;
		Vector( 0.3f, 0.2f, 0.1f, vLight );
		CreateEffect(MODEL_STORM2, o->Position, o->Angle, vLight, 1, NULL, -1, 0, 0, 0, 1.6f);
		CreateEffect(MODEL_SUMMON, o->Position, o->Angle, vLight, 3);
	}
	else
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "������ų : ��Ÿ");
#endif // CONSOLE_DEBUG		
		SetAction(o, MONSTER01_ATTACK4);
	}
}

bool CGM_Raklion::AttackEffectMonster(CHARACTER* c, OBJECT* o, BMD* b)
{
	if(IsIceCity() == false)
		return false;

	switch(c->MonsterIndex) 
	{
	case 454:
	case 455:
	case 456:
	case 457:
	case 458:
	case 459:	// ������ (��������)
	case 460:	// �Ŵ� �Ź̾�
	case 461:	// �Ŵ� �Ź̾�
	case 462:	// �Ŵ� �Ź̾�
		break;
	}

	return false;
}


// ���� ����
bool CGM_Raklion::PlayMonsterSound(OBJECT* o) 
{
	if(IsIceCity() == false)
		return false;
	
	float fDis_x, fDis_y;
	fDis_x = o->Position[0] - Hero->Object.Position[0];
	fDis_y = o->Position[1] - Hero->Object.Position[1];
	float fDistance = sqrtf(fDis_x*fDis_x+fDis_y*fDis_y);
	
	if (fDistance > 500.0f) 
		return true;

	switch(o->Type)
	{
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case MODEL_MONSTER01+145:		// Ice Walker
		if( MONSTER01_ATTACK1 == o->CurrentAction || MONSTER01_ATTACK2 == o->CurrentAction)
		{
			PlayBuffer( SOUND_RAKLION_ICEWALKER_ATTACK );
		}
		else if( MONSTER01_WALK == o->CurrentAction )
		{
			if (rand() % 20 == 0)
			{
				PlayBuffer( SOUND_RAKLION_ICEWALKER_MOVE );
			}
		}
		else if( MONSTER01_DIE == o->CurrentAction )
		{
			{
				PlayBuffer( SOUND_ELBELAND_WOLFHUMAN_DEATH01 );
			}
		}
		return true;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef PJH_GIANT_MAMUD
		case MODEL_MONSTER01+146:	// ���̾�Ʈ �Ÿӵ�
		if( MONSTER01_ATTACK1 == o->CurrentAction || MONSTER01_ATTACK2 == o->CurrentAction)
		{
			PlayBuffer( SOUND_RAKLION_GIANT_MAMUD_ATTACK );
		}
		else
		if (o->CurrentAction == MONSTER01_WALK)
		{
			if (rand() % 100 == 0)
			{
				PlayBuffer(SOUND_RAKLION_GIANT_MAMUD_MOVE);
			}
		}
		else 
		if(o->CurrentAction == MONSTER01_DIE)
		{
			PlayBuffer(SOUND_RAKLION_GIANT_MAMUD_DEATH);
		}
		return true;
#endif //#ifdef PJH_GIANT_MAMUD
#ifdef ADD_RAKLION_MOB_ICEGIANT
	case MODEL_MONSTER01+147:	// ���̽� ���̾�Ʈ
		if (o->CurrentAction == MONSTER01_WALK)
		{
			if (rand() % 100 == 0)
			{
				PlayBuffer(SOUND_RAKLION_ICEGIANT_MOVE);
			}
		}
		else if(o->CurrentAction == MONSTER01_DIE)
		{
			PlayBuffer(SOUND_RAKLION_ICEGIANT_DEATH);
		}
		return true;
#endif	// ADD_RAKLION_MOB_ICEGIANT
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case MODEL_MONSTER01+148:		// ��ƾ
		if( MONSTER01_ATTACK1 == o->CurrentAction || MONSTER01_ATTACK2 == o->CurrentAction)
		{
			PlayBuffer( SOUND_RAKLION_COOLERTIN_ATTACK );
		}
		else if( MONSTER01_WALK == o->CurrentAction )
		{
			if (rand() % 20 == 0)
			{
				PlayBuffer( SOUND_RAKLION_COOLERTIN_MOVE );
			}
		}
		else if( MONSTER01_DIE == o->CurrentAction )
		{
			{
				PlayBuffer( SOUND_MONSTER+34 );
			}
		}

		return true;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN

#ifdef ADD_RAKLION_IRON_KNIGHT
	case MODEL_MONSTER01+149:	// ���̾� ����Ʈ
		if(o->CurrentAction == MONSTER01_ATTACK1 || o->CurrentAction == MONSTER01_ATTACK2)
		{
			// ����
			PlayBuffer(SOUND_RAKLION_IRON_KNIGHT_ATTACK);
		}
		else if(o->CurrentAction == MONSTER01_STOP1 || o->CurrentAction == MONSTER01_STOP2 || o->CurrentAction == MONSTER01_WALK)
		{
			// ������
			PlayBuffer(SOUND_RAKLION_IRON_KNIGHT_MOVE);
		}
		else if(o->CurrentAction == MONSTER01_DIE)
		{
			// �����
			PlayBuffer(SOUND_MONSTER+154);
		}
		return true;
#endif	// ADD_RAKLION_IRON_KNIGHT

	case MODEL_MONSTER01+150:	// ������ (��������)
		if(o->CurrentAction == MONSTER01_ATTACK1 || o->CurrentAction == MONSTER01_ATTACK2)
		{
			// �ñ���ǳ, ������
			PlayBuffer(SOUND_RAKLION_SERUFAN_ATTACK1);
		}
		else if(o->CurrentAction == MONSTER01_ATTACK3)
		{
			// �ñ����
			PlayBuffer(SOUND_RAKLION_SERUFAN_ATTACK2);
		}
		else if(o->CurrentAction == MONSTER01_DIE)
		{
			// �����
			PlayBuffer(SOUND_RAKLION_SERUFAN_WORD2);
		}
		return true;
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
		case MODEL_MONSTER01+205:	// ��ũ ���̾�Ʈ �Ÿӵ�
			if( MONSTER01_ATTACK1 == o->CurrentAction || MONSTER01_ATTACK2 == o->CurrentAction)
			{
				PlayBuffer( SOUND_RAKLION_GIANT_MAMUD_ATTACK );
			}
			else if (o->CurrentAction == MONSTER01_WALK)
			{
				if (rand() % 100 == 0)
				{
					PlayBuffer(SOUND_RAKLION_GIANT_MAMUD_MOVE);
				}
			}
			else if(o->CurrentAction == MONSTER01_DIE)
			{
				PlayBuffer(SOUND_RAKLION_GIANT_MAMUD_DEATH);
			}
		return true;
		case MODEL_MONSTER01+206:	// ��ũ ���̽� ���̾�Ʈ
			if (o->CurrentAction == MONSTER01_WALK)
			{
				if (rand() % 100 == 0)
				{
					PlayBuffer(SOUND_RAKLION_ICEGIANT_MOVE);
				}
			}
			else if(o->CurrentAction == MONSTER01_DIE)
			{
				PlayBuffer(SOUND_RAKLION_ICEGIANT_DEATH);
			}
		return true;
		case MODEL_MONSTER01+208:	// ��ũ ���̾� ����Ʈ
			if(o->CurrentAction == MONSTER01_ATTACK1 || o->CurrentAction == MONSTER01_ATTACK2)
			{
				// ����
				PlayBuffer(SOUND_RAKLION_IRON_KNIGHT_ATTACK);
			}
			else if(o->CurrentAction == MONSTER01_STOP1 || o->CurrentAction == MONSTER01_STOP2 || o->CurrentAction == MONSTER01_WALK)
			{
				// ������
				PlayBuffer(SOUND_RAKLION_IRON_KNIGHT_MOVE);
			}
			else if(o->CurrentAction == MONSTER01_DIE)
			{
				// �����
				PlayBuffer(SOUND_MONSTER+154);
			}
		return true;
		case MODEL_MONSTER01+207:		// ��ƾ
			if( MONSTER01_ATTACK1 == o->CurrentAction || MONSTER01_ATTACK2 == o->CurrentAction)
			{
				PlayBuffer( SOUND_RAKLION_COOLERTIN_ATTACK );
			}
			else if( MONSTER01_WALK == o->CurrentAction )
			{
				if (rand() % 20 == 0)
				{
					PlayBuffer( SOUND_RAKLION_COOLERTIN_MOVE );
				}
			}
			else if( MONSTER01_DIE == o->CurrentAction )
			{
				{
					PlayBuffer( SOUND_MONSTER+34 );
				}
			}
			
		return true;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
	}

	return false; 
}

// ������Ʈ ����
void CGM_Raklion::PlayObjectSound(OBJECT* o)
{
	
}

bool CGM_Raklion::CanGoBossMap()
{
	return m_bCanGoBossMap;
}

void CGM_Raklion::SetCanGoBossMap()
{
	if(m_byState <= RAKLION_STATE_NOTIFY_3)
	{
		m_bCanGoBossMap = true;
	}
	else
	{
		m_bCanGoBossMap = false;
	}
}

void CGM_Raklion::SetState(BYTE byState, BYTE byDetailState)
{
	if(byState == RAKLION_STATE_DETAIL_STATE)
	{
		m_byDetailState = byDetailState;
		
		if(m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_2 || m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_3 
			|| m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_5 || m_byDetailState == BATTLE_OF_SELUPAN_PATTERN_6)
		{
			// ����ȭ ����
			PlayBuffer(SOUND_RAKLION_SERUFAN_RAGE);
		}
		
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "��Ŭ���� ���λ��� : %d", m_byDetailState);
#endif // CONSOLE_DEBUG
	}
	else
	{
		m_byState = byState;
		
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "��Ŭ���� ���� : %d", m_byState);
#endif // CONSOLE_DEBUG	

		if(m_byState == RAKLION_STATE_NOTIFY_1 || m_byState ==RAKLION_STATE_STANDBY)
		{
			// �ϴÿ��� ������ ���� �������� ȿ����
			PlayBuffer(SOUND_WIND01);
		}
		else if(m_byState == RAKLION_STATE_READY)
		{
			// ���� ���� ����
			PlayBuffer(SOUND_RAKLION_SERUFAN_WORD1);

			// ������ BGM ����
			m_bMusicBossMap = true;
		}
		else if(m_byState == RAKLION_STATE_END)
		{
			m_bMusicBossMap = false;
		}
		
		// ������ ����Ʈ ����
		SetCanGoBossMap();
		
		// ������ ���� ����
		SetEffect();	
	}
}

void CGM_Raklion::SetEffect()
{
	if(m_byState == RAKLION_STATE_NOTIFY_1)
	{
		// 1�ʰ� ����
		m_Timer.SetTimer(500);
		m_bVisualEffect = true;
	}
	else if(m_byState == RAKLION_STATE_STANDBY)
	{
		// 2�ʰ� ����
		m_Timer.SetTimer(1000);
		m_bVisualEffect = true;
	}
}

void CGM_Raklion::MoveEffect()
{
	if(m_bVisualEffect == false)
	{
		return;
	}

	if(m_byState <= RAKLION_STATE_STANDBY)
	{
		m_Timer.UpdateTime();

		if(m_Timer.IsTime() == true)
		{
			m_Timer.ResetTimer();
			m_bVisualEffect = false;

			if(m_byState == RAKLION_STATE_STANDBY)
			{
				// ȭ�� ���� ȿ�� ����
				EarthQuake = 0.f;
			}
		}
		else
		{
			if(rand()%2 == 0)
			{
				CreateMapEffect();
			}
		}
	}
	else
	{
#ifdef CONSOLE_DEBUG
		g_ConsoleDebug->Write(MCD_NORMAL, "RAKLION_STATE_NOTIFY_1(���ܹ߻�)");
#endif // CONSOLE_DEBUG		
		m_Timer.ResetTimer();
		m_bVisualEffect = false;
		EarthQuake = 0.f;
	}
}

void CGM_Raklion::CreateMapEffect()
{
	// �Ź̾��� �Ѹ��� ������ �� ���߿��� �����̳� ������ �������� ����Ʈ ó�� 
	if(m_byState <= RAKLION_STATE_NOTIFY_1)
	{
		float fScale = 1.f;
		vec3_t vPos, vLight;
		OBJECT* pObject = &Hero->Object;

		for(int i=0; i<5; ++i)
		{
			// ���� ���� ������ �������� ����Ʈ
			Vector(1.f, 1.0f, 1.0f, vLight);
			VectorCopy(pObject->Position, vPos);
			vPos[0] += (rand()%1600 - 800.f);
			vPos[1] += (rand()%1600 - 800.f);
			vPos[2] = 600.f + rand()%100;
			
			fScale = 2.0f + (rand()%20) / 5.0f;
			int iIndex = MODEL_EFFECT_BROKEN_ICE0;
			
			CreateEffect(iIndex, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
			
			VectorCopy(pObject->Position, vPos);
			vPos[0] += (rand()%1600 - 800.f);
			vPos[1] += (rand()%1600 - 800.f);
			vPos[2] = 600.f + rand()%100;
			
			fScale = 0.5f + (rand()%10) / 5.0f;
			iIndex = MODEL_EFFECT_BROKEN_ICE2;
			
			CreateEffect(iIndex, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
			
			// ���� ������ �������� ����Ʈ
			VectorCopy(pObject->Position, vPos);
			vPos[0] += (rand()%1600 - 800.f);
			vPos[1] += (rand()%1600 - 800.f);
			vPos[2] = 600.f + rand()%100;
			
			Vector(1.f, 0.8f, 0.8f, vLight);
			fScale = 0.005f + (rand()%10) / 200.0f;
			CreateEffect(MODEL_FALL_STONE_EFFECT, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
			
			// ���� �������� ȿ��
			Vector(0.4f, 0.4f, 0.5f, vLight);
			fScale = 0.5f + (rand()%10) / 20.0f;
			for(int k=0; k<3; ++k)
			{
				VectorCopy(pObject->Position, vPos);
				vPos[0] += (rand()%1000 - 500.f);
				vPos[1] += (rand()%1000 - 500.f);
				vPos[2] = 760.f + rand()%150;
				fScale = 0.2f + (rand()%20) / 40.0f;
				CreateParticle(BITMAP_WATERFALL_3+(rand()%2), vPos, pObject->Angle, vLight, 13, fScale );
			}
		}
	}
	// ������ �� ������ ���� ���� �� ���� ����
	else if(m_byState == RAKLION_STATE_STANDBY)
	{
		vec3_t vPos, vLight;
		float fScale = 1.f;
		OBJECT* pObject = &Hero->Object;
		Vector(0.3f, 0.5f, 1.f, vLight);

		// ȭ�� ���� ȿ��
		EarthQuake = (float)(rand()%2-2)*0.5f;	

		// ū ���� ������ �������� ����Ʈ
		VectorCopy(pObject->Position, vPos);
		vPos[0] += (rand()%2000 - 1000.f);
		vPos[1] += (rand()%2000 - 1000.f);
		vPos[2] = 500.f + rand()%100;
		
		fScale = 2.0f + (rand()%20) / 5.0f;
		int iIndex = MODEL_EFFECT_BROKEN_ICE1;
		
		CreateEffect(iIndex, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
		
		VectorCopy(pObject->Position, vPos);
		vPos[0] += (rand()%2000 - 1000.f);
		vPos[1] += (rand()%2000 - 1000.f);
		vPos[2] = 500.f + rand()%100;
		
		fScale = 0.5f + (rand()%10) / 5.0f;
		iIndex = MODEL_EFFECT_BROKEN_ICE3;
		
		CreateEffect(iIndex, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);

		// ū ������ �������� ����Ʈ
		VectorCopy(pObject->Position, vPos);
		vPos[0] += (rand()%2000 - 1000.f);
		vPos[1] += (rand()%2000 - 1000.f);
		vPos[2] = 500.f + rand()%100;

		Vector(1.f, 0.8f, 0.8f, vLight);
		fScale = 0.05f + (rand()%10) / 20.0f;
		CreateEffect(MODEL_FALL_STONE_EFFECT, vPos, pObject->Angle, vLight, 2, NULL, -1, 0, 0, 0, fScale);
	}
}

void CGM_Raklion::PlayBGM()
{
	if(World == WD_57ICECITY)
	{
		PlayMp3(g_lpszMp3[MUSIC_RAKLION]);
	}
	else
	{
		StopMp3(g_lpszMp3[MUSIC_RAKLION]);
	}

	if(World == WD_58ICECITY_BOSS && m_bMusicBossMap == true)
	{
		PlayMp3(g_lpszMp3[MUSIC_RAKLION_BOSS]);
	}
	else
	{
		StopMp3(g_lpszMp3[MUSIC_RAKLION_BOSS]);
	}
}

#endif // CSK_ADD_MAP_ICECITY
