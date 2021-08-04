///////////////////////////////////////////////////////////////////////////////
// ��� ������Ʈ ���� �Լ�
// ��� ������Ʈ Open, Save
// ��� ������Ʈ, ��ƼŬ, ��, ����� ����� ������ ó�� �� ������
//
// *** �Լ� ����: 3
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzLodTerrain.h"
#include "ZzzTexture.h"
#include "ZzzAI.h"
#include "ZzzInterface.h"
#include "ZzzInventory.h"
#include "ZzzEffect.h"
#include "ZzzScene.h"
#include "ZzzOpenData.h"
#include "DSPlaySound.h"
#include "wsclientinline.h"
#include "SideHair.h"
#include "PhysicsManager.h"
#include "GOBoid.h"
#include "CSparts.h"
#include "CSItemOption.h"
#include "CSChaosCastle.h"
#include "GMHellas.h"

#include "GMBattleCastle.h"
#include "GMHuntingGround.h"
#ifdef CRYINGWOLF_2NDMVP
#include "GMCryingWolf2nd.h"
#endif // CRYINGWOLF_2NDMVP
#include "GMAida.h"
#include "GMCryWolf1st.h"

#include "GM_Kanturu_1st.h"
#include "UIManager.h"
#include "GM_Kanturu_2nd.h"
#include "GM_Kanturu_3rd.h"
#include "CDirection.h"

#include "CComGem.h"

#include "GM3rdChangeUp.h"

#ifdef PRUARIN_EVENT07_3COLORHARVEST
#include "BoneManager.h"
#endif // PRUARIN_EVENT07_3COLORHARVEST

#include "GMNewTown.h"
#include "w_CursedTemple.h"
#include "GMSwampOfQuiet.h"

// �� ���� include
#ifdef PSW_ADD_MAPSYSTEM
#include "w_MapHeaders.h"
#endif // PSW_ADD_MAPSYSTEM
#ifdef PBG_ADD_NEWCHAR_MONK
#include "MonkSystem.h"
#endif //PBG_ADD_NEWCHAR_MONK

//////////////////////////////////////////////////////////////////////////
//  ���� ������� �ʴ� ����.
//////////////////////////////////////////////////////////////////////////
#ifdef ANTIHACKING_ENABLE
#include "proc.h"
#endif

#ifdef USE_SHADOWVOLUME
#include "ShadowVolume.h"
#endif
//////////////////////////////////////////////////////////////////////////

extern vec3_t VertexTransform[MAX_MESH][MAX_VERTICES];
extern vec3_t LightTransform[MAX_MESH][MAX_VERTICES];

int          g_iTotalObj = 0;
OBJECT_BLOCK ObjectBlock [256];
#ifdef MR0
AUTOOBJ		Boids		[MAX_BOIDS];
AUTOOBJ		Fishs		[MAX_FISHS];
AUTOOBJ		Butterfles	[MAX_BUTTERFLES];
#else
OBJECT       Boids		 [MAX_BOIDS];
OBJECT       Fishs		 [MAX_FISHS];
OBJECT       Butterfles  [MAX_BUTTERFLES];
#endif //MR0 
OPERATE      Operates    [MAX_OPERATES];
int   World = -1;
float EarthQuake;


static  int g_iThunderTime = 0;
        int g_iActionObjectType = -1;
        int g_iActionWorld = -1;
        int g_iActionTime  = -1;
        float g_fActionObjectVelocity = -1;

//////////////////////////////////////////////////////////////////////////
//  ������Ʈ ����ó��.
//////////////////////////////////////////////////////////////////////////
void ClearActionObject ()
{
    g_iActionObjectType = -1;
    g_iActionWorld = -1;
    g_iActionTime  = -1;
    g_fActionObjectVelocity = -1;
}

void SetActionObject ( int iWorld, int iType, int iLifeTime, int iVel )
{
    g_iActionWorld      = iWorld;
    g_iActionObjectType = iType;
    g_iActionTime       = iLifeTime;
    g_fActionObjectVelocity = (float)iVel;
}

void ActionObject ( OBJECT* o )
{
    if ( g_iActionWorld<0 )     return;
    if ( g_iActionObjectType<0 )return;
    if ( g_iActionTime<0 )      return;

    //  ������ ��.
    if ( World==g_iActionWorld )
    {
        //  ������ ���߾ �ǹ��� ����Ʈ����.
        if ( MoveChaosCastleAllObject( o ) ) return;
        {
            vec3_t  Position, Light;

            Vector ( 1.f, 1.f, 1.f, Light );
            if ( o->Type==g_iActionObjectType || o->Type==9 || o->Type==10 )     //  ���� �ٸ� ����.
            {
                if ( o->Type==9 )
                {
                    if ( g_iActionTime==0 )
                    {
                        o->HiddenMesh = -1;
                        o->PKKey = 4;
                    }
                }
                else if ( o->Type==10 )
                {
                    if ( g_iActionTime==0 )
                    {
                        o->HiddenMesh = -1;
                        o->PKKey = 4;
                    }
                }
                else if ( o->Type==g_iActionObjectType ) //  ���� �ٸ� ����.
                {
                    if ( g_iActionTime==20 )
                    {
                        o->Angle[0] = 35.f;
                        o->HiddenMesh = -1;

                        PlayBuffer ( SOUND_DOWN_GATE );
                    }

                    if ( g_iActionTime>=0 )
                    {
                        o->Angle[0] += g_fActionObjectVelocity;
                        g_fActionObjectVelocity += 1.5f;

                        if ( o->Angle[0]>=90.f )
                        {
                            o->Angle[0] -= g_iActionTime;
                            g_fActionObjectVelocity = 2.f;

					        VectorCopy ( o->Position, Position );

                            if ( o->Angle[0]==80 )
                            {
                                for ( int i=0; i<10; ++i )
                                {
                                    Position[0] = o->Position[0] + (rand()%300-150.f);
                                    Position[1] = o->Position[1] - (rand()%20+600.f);
                                    CreateParticle(BITMAP_SMOKE+1,Position,o->Angle,o->Light);
                                }
                            }
                        }
                        if ( g_iActionTime==0 )
                        {
                            o->HiddenMesh = -2;
                            o->Angle[0] = 90.f;
                            ClearActionObject ();

                            AddTerrainAttributeRange ( 13, 70, 3, 6, TW_NOGROUND, false );  //  ����.
                        }
                    }
                }
            }
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// ������Ʈ �浹 üũ
///////////////////////////////////////////////////////////////////////////////

OBJECT *CollisionDetectObjects(OBJECT *PickObject)
{
	OBJECT *Object = NULL;
	InitCollisionDetectLineToFace();
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if(o->Live && o->Visible && o->Alpha>=0.01f)
					{
						//if(o != PickObject)
						{
							BMD *b = &Models[o->Type];
							b->BodyScale     = o->Scale;
							b->CurrentAction = o->CurrentAction;
							VectorCopy(o->Position,b->BodyOrigin);
							b->Animation(BoneTransform,o->AnimationFrame,o->PriorAnimationFrame,o->PriorAction,o->Angle,o->HeadAngle,false,false);
							b->Transform(BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,true);
							if(CollisionDetectLineToOBB(MousePosition,MouseTarget,o->OBB))
							{
								if(b->CollisionDetectLineToMesh(MousePosition,MouseTarget))
								{
									Object = o;
									//return Object;
								}
							}
						}
					}
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}
	return Object;
}

///////////////////////////////////////////////////////////////////////////////
// ������Ʈ ������
///////////////////////////////////////////////////////////////////////////////

void BodyLight(OBJECT *o,BMD *b)
{
	if ( o->Type == MODEL_MONSTER01+55)
	{
		Vector( .6f, .6f, .6f, b->BodyLight);
		return;
	}
    if ( o->Type==MODEL_PROTECT )
    {
        float Luminosity = sinf( WorldTime*0.003f )*0.5f+0.5f;
        Vector( Luminosity, Luminosity, Luminosity, b->BodyLight );
        return;
    }

	b->LightEnable    = o->LightEnable;
	if(o->LightEnable)
	{
		vec3_t Light;
		RequestTerrainLight(o->Position[0],o->Position[1],Light);
		VectorAdd(Light,o->Light,b->BodyLight);
	}
	else
	{
		vec3_t Light;
		RequestTerrainLight(o->Position[0],o->Position[1],Light);
		VectorScale(Light,0.1f,Light);
		VectorAdd(Light,o->Light,b->BodyLight);
	}
}

extern float BoneScale;


//////////////////////////////////////////////////////////////////////////
//  ������Ʈ�� ȭ�鿡 ǥ���ϱ� ���� �ִϸ��̼ǰ� ��ȯ�� �Ѵ�.
//////////////////////////////////////////////////////////////////////////
bool Calc_RenderObject(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
    if(InChaosCastle() == true && Hero->Object.m_bActionStart == true)
    {
        o->Alpha -= 0.15f;
    }

	if(o->Alpha < 0.01f)
	{
		return false;
	}
	
	BMD *b = &Models[o->Type];
	b->BodyHeight = 0.f;
	b->ContrastEnable = o->ContrastEnable;
	BodyLight(o,b);
	b->BodyScale = o->Scale;
	b->CurrentAction = o->CurrentAction;
	VectorCopy(o->Position,b->BodyOrigin);

    if ( o->Type==MODEL_MONSTER01+61 ) //  ����.
    {
        vec3_t Position;
		VectorCopy(o->Position,Position);

        Position[1] += 60.f;
		VectorCopy(Position,b->BodyOrigin);
    }
    else if ( o->Type==MODEL_MONSTER01+60 ) //  ũ����Ż.
    {
        vec3_t Position;
		VectorCopy(o->Position,Position);

        Position[1] += 120.f;
		VectorCopy(Position,b->BodyOrigin);
    }

	if(o->Owner != NULL)
	{
		if(g_isCharacterBuff(o->Owner, eDeBuff_Stun)
			|| g_isCharacterBuff(o->Owner, eDeBuff_Sleep) )	
		{
			o->AnimationFrame = 0.f;
		}
	}

	if(o->EnableBoneMatrix)
	{
		b->Animation(o->BoneTransform,o->AnimationFrame,o->PriorAnimationFrame,o->PriorAction,o->Angle,o->HeadAngle,false,!Translate);
	}
	else
	{
        b->Animation(BoneTransform,o->AnimationFrame,o->PriorAnimationFrame,o->PriorAction,o->Angle,o->HeadAngle,false,!Translate );
	}

	BoneScale = 1.f;
	if(3==Select)
	{
		BoneScale = 1.4f;
	}
	else if(2==Select)
	{
		BoneScale = 1.2f;
	}
	else if(1==Select)
	{
      	b->LightEnable = false;
			
	    if(InChaosCastle() == true || o->Kind != KIND_NPC )
		{
			Vector(0.1f,0.01f,0.f,b->BodyLight);
			if(o->Type == MODEL_MONSTER01+32)
			{
		     	BoneScale = 1.2f;
			}
			else
			{
				BoneScale = 1.f + (0.1f / o->Scale);
			}
	        if( o->m_fEdgeScale != 1.2f)
	        {
	            BoneScale = o->m_fEdgeScale;
	        }
		}
		else
		{
			Vector(0.02f,0.1f,0.f,b->BodyLight);
			BoneScale = 1.2f;
	        BoneScale = o->m_fEdgeScale;
		}
		float Scale = BoneScale;
	    RenderPartObjectEdge(b, o, RENDER_BRIGHT, Translate, Scale);
		
	    if(InChaosCastle() == true || o->Kind != KIND_NPC)
		{
			Vector(0.7f,0.07f,0.f,b->BodyLight);
			if(o->Type == MODEL_MONSTER01+32)
			{
		     	BoneScale = 1.08f;
			}
			else
			{
		     	BoneScale = 1.f + (0.04f / o->Scale);
			}
	        if(o->m_fEdgeScale != 1.2f)
	        {
	            BoneScale = maxf(o->m_fEdgeScale - 0.04f, 1.01f);
	        }
		}
		else
		{
			Vector(0.16f,0.7f,0.f,b->BodyLight);
			BoneScale = 1.08f;
	        BoneScale = maxf(o->m_fEdgeScale - 0.12f, 1.01f);
		}

	    Scale = BoneScale;
	    RenderPartObjectEdge(b, o, RENDER_BRIGHT, Translate, Scale);
		BodyLight(o,b);
		BoneScale = 1.f;
	}

	if(o->EnableBoneMatrix)
	{
		b->Transform(o->BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,Translate);
	}
	else
	{
		b->Transform(BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,Translate);
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////
//  ������Ʈ�� ȭ�鿡 ǥ���ϱ� ���� �ִϸ��̼��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////
bool Calc_ObjectAnimation ( OBJECT* o, bool Translate, int Select )
{
    if ( InChaosCastle()==true && Hero->Object.m_bActionStart )
    {
        o->Alpha -= 0.15f;
    }

	if(o->Alpha < 0.01f) return false;
	
	BMD *b = &Models[o->Type];
	b->BodyHeight     = 0.f;
	b->ContrastEnable = o->ContrastEnable;
	BodyLight(o,b);
	b->BodyScale     = o->Scale;
	b->CurrentAction = o->CurrentAction;
	VectorCopy(o->Position,b->BodyOrigin);

	if ( o->EnableBoneMatrix )
	{
		b->Animation ( o->BoneTransform, o->AnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle, false, !Translate );
	}
	else
	{
        b->Animation ( BoneTransform, o->AnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle, false, !Translate );
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
void Draw_RenderObject(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
	BMD *b = &Models[o->Type];
	bool View = true;


#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif //MR0

    if((EditFlag!=EDIT_NONE) || (EditFlag==EDIT_NONE&&o->HiddenMesh!=-2))
	{
		if(ExtraMon == 10)
		{
			float Alpha = 0.5f;

			for ( int i=0; i<MAX_CHARACTERS_CLIENT; ++i )
			{
				CHARACTER *c = &CharactersClient[i];
				OBJECT *oa = &c->Object;
				OBJECT *ob = o->Owner;
				

				if(oa == ob)
				{
					if ( c!=Hero && battleCastle::IsBattleCastleStart()==true && g_isCharacterBuff(ob, eBuff_Cloaking) )
					{

						if ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK )
						{
							if(!( c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK || c->EtcPart==PARTS_ATTACK_TEAM_MARK ))
							{
								View = false;
								break;
							}
						}
						else
						if ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK2 )
						{
							if(!( c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK2 || c->EtcPart==PARTS_ATTACK_TEAM_MARK2 ))
							{
								View = false;
								break;
							}
						}
						else
						if ( Hero->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3 || Hero->EtcPart==PARTS_ATTACK_TEAM_MARK3 )
						{
							if(!( c->EtcPart==PARTS_ATTACK_KING_TEAM_MARK3 || c->EtcPart==PARTS_ATTACK_TEAM_MARK3 ))
							{
								View = false;
								break;
							}
						}
						else
						if ( Hero->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || Hero->EtcPart==PARTS_DEFENSE_TEAM_MARK )
						{
							if(!( c->EtcPart==PARTS_DEFENSE_KING_TEAM_MARK || c->EtcPart==PARTS_DEFENSE_TEAM_MARK ))
							{
								View = false;
								break;
							}
						}
					}
				}
			}

			if(View == true)
			{
				Vector ( 1.f, 1.f, 1.f, b->BodyLight );
				for(int i = 0; i < Models[o->Type].NumMeshs; i++)
					b->RenderMesh(i,RENDER_BRIGHT|RENDER_CHROME5, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU*8.f, o->BlendMeshTexCoordV*2.f,BITMAP_CHROME2 );

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
				ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
			}

			return;
		}
		if ( World == WD_10HEAVEN)	// õ��
		{
			if ( o->Type==MODEL_MONSTER01+31)
			{	// �巡�� �˰�
				Vector(0.02f,0.05f,0.15f,b->BodyLight);
			}
		}
		if ( InDevilSquare() )	// �Ǹ��� ���忡
		{
			if ( o->Type==MODEL_MONSTER01+18)
			{	// ���̽��� �Ӱ�
				Vector(0.0f,0.3f,1.0f,b->BodyLight);
			}
		}
		if ( ExtraMon && o->Type==MODEL_MONSTER01+27)
		{	// �߷�2
			Vector(0.0f,0.0f,1.0f,b->BodyLight);
		}

        if(o->RenderType==RENDER_DARK)//��Ӹ�(�ǷɸӸ�)
		{
			b->RenderBody(RENDER_TEXTURE|RENDER_DARK,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else if( o->Type == MODEL_CHANGE_UP_EFF )
		{
			if(o->SubType == 0 || o->SubType == 1)
			{
				Vector(0.1f,0.4f,0.6f,b->BodyLight);
			}
			else
			{
				Vector(0.1f,0.2f,0.9f,b->BodyLight);
			}
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if( o->Type == MODEL_CHANGE_UP_NASA)
		{
			Vector(0.5f,0.5f,0.9f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if( o->Type == MODEL_CHANGE_UP_CYLINDER)
		{
			Vector(0.4f,0.5f,1.f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
		else if (o->Type == MODEL_SUMMON)
		{
//			Vector(0.4f,0.5f,1.f,b->BodyLight);
//			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			if(!M39Kanturu3rd::IsInKanturu3rd())
			{
				VectorCopy ( o->Light,b->BodyLight )
				b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				b->RenderMesh ( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				b->RenderMesh ( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				Vector ( 1.f, 1.f, 1.f, b->BodyLight );
			}
		}
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef LDK_ADD_EG_MONSTER_DEASULER
		else if( o->Type == MODEL_DEASULER)
		{
			b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			Vector ( 0.3f, 0.4f, 1.0f, b->BodyLight );
			b->RenderMesh ( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		}
		else if (o->Type == MODEL_MONSTER01+168)
		{
			MoveEye(o, b, 14, 15, 71,72,73,74);
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			float fLumi = (sinf(WorldTime*0.003f) + 1.f) * 0.35f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX


			if ( !o->m_pCloth)
			{
				CPhysicsCloth *pCloth = new CPhysicsCloth [1];
				pCloth[0].Create( o, 10, 0.0f, -10.0f, 0.0f, 5, 12, 150.0f, 190.0f, BITMAP_DEASULER_CLOTH, BITMAP_DEASULER_CLOTH, PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED | PCT_SHORT_SHOULDER);
				pCloth[0].AddCollisionSphere( 50.0f, -140.0f, -20.0f, 30.0f, 2);
				o->m_pCloth = ( void*)pCloth;
				o->m_byNumCloth = 1;
			}
			CPhysicsCloth *pCloth = ( CPhysicsCloth*)o->m_pCloth;
			if ( !pCloth[0].Move2( 0.005f, 5))
			{
				CHARACTER *c = &CharactersClient[o->PKKey];
				DeleteCloth( c, o);
			}
			else
			{
				pCloth[0].Render();
			}

			Vector ( 1.f, 1.f, 1.f, b->BodyLight );
			b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh ( 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh ( 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				
			if(o->CurrentAction != MONSTER01_ATTACK2 || o->AnimationFrame < 2.5f)
			{
				b->RenderMesh ( 3, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				Vector ( 0.4f, 0.5f, 1.0f, b->BodyLight );
				b->RenderMesh ( 4, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			}
		}
#ifdef LDK_ADD_EG_MONSTER_ASSASSINMASTER
		else
		if (o->Type == MODEL_MONSTER01+176)
		{
			float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.35f;

			Vector ( 1.f, 1.f, 1.f, b->BodyLight );
			b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh ( 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh ( 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

			Vector ( fLumi, fLumi, fLumi, b->BodyLight );
			b->RenderMesh ( 0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_ASSASSIN_EFFECT1 );
		}
#endif //LDK_ADD_EG_MONSTER_ASSASSINMASTER
#endif //LDK_ADD_EG_MONSTER_DEASULER
#ifdef CSK_RAKLION_BOSS
		else if(o->Type == MODEL_RAKLION_BOSS_CRACKEFFECT)
		{
			float fLumi = o->Alpha;
			Vector(o->Light[0]*fLumi,o->Light[1]*fLumi,o->Light[2]*fLumi,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_RAKLION_BOSS_MAGIC)
		{
			float fLumi = o->Alpha;
			Vector(o->Light[0]*fLumi,o->Light[1]*fLumi,o->Light[2]*fLumi,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
#endif // CSK_RAKLION_BOSS
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
		else if(o->Type == MODEL_NIGHTWATER_01)
		{
			float fLumi = o->Alpha;
			Vector(o->Light[0]*fLumi,o->Light[1]*fLumi,o->Light[2]*fLumi,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else if(o->Type == MODEL_KNIGHT_PLANCRACK_A)
		{
			float fLumi = o->Alpha;
			Vector(o->Light[0]*fLumi,o->Light[1]*fLumi,o->Light[2]*fLumi,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,-(int)WorldTime%2000*0.0001f);
		}
		else if(o->Type == MODEL_KNIGHT_PLANCRACK_B)
		{
			float fLumi = o->Alpha;
			Vector(o->Light[0]*fLumi,o->Light[1]*fLumi,o->Light[2]*fLumi,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,-(int)WorldTime%2000*0.0001f);
		}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
		else if(o->Type == MODEL_ALICE_BUFFSKILL_EFFECT || o->Type == MODEL_ALICE_BUFFSKILL_EFFECT2)
		{
			if(o->SubType == 1)
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_DARK,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
			else
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
		}
		else if(o->Type==MODEL_CURSEDTEMPLE_HOLYITEM)
		{
			vec3_t Light;
			float fLuminosity = (float)sinf((WorldTime)*0.0002f)*0.002f;
			Vector(0.9f, 0.4f, 0.4f, Light);
			CreateSprite(BITMAP_LIGHT,o->Position,3.f,Light,o, 0.0f, 0);	// flare01.jpg
			Vector(0.9f, 0.6f, 0.6f, Light);
			CreateSprite(BITMAP_POUNDING_BALL,o->Position,0.9f+fLuminosity,Light,NULL,(WorldTime/10.0f));
			CreateParticle(BITMAP_POUNDING_BALL,o->Position,o->Angle,Light, 2, 0.1f, o );

			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 0);
			b->RenderMesh(0, RENDER_TEXTURE,0.7f,0,o->BlendMeshLight*3.f,o->BlendMeshTexCoordU,-WorldTime*0.004f);
		}
		else if(o->Type==MODEL_CURSEDTEMPLE_PRODECTION_SKILL)
		{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			float fLuminosity = (float)sinf((WorldTime)*0.002f)*0.2f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
			Vector( 0.3f, 0.3f, 1.0f, b->BodyLight);
			VectorCopy( o->Angle, b->BodyAngle );
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU, -WorldTime*0.0004f);
		}
		else if(o->Type==MODEL_CURSEDTEMPLE_RESTRAINT_SKILL)
		{
			float fLuminosity = (float)sinf((WorldTime)*0.0002f)*0.002f;
			b->RenderMesh(0,RENDER_TEXTURE,0.7f,0,0.35f+fLuminosity,-WorldTime*0.0004f, WorldTime*0.0004f );
		}
 		else if ( g_CursedTemple->IsCursedTemple() == true 
			&& (o->Type == 32 || o->Type == 39 || o->Type == 41 || o->Type == 46 || o->Type == 62
				|| o->Type == 67 || o->Type == 68 || o->Type == 64 || o->Type == 65 || o->Type == 66 || o->Type == 80) 
				)
		{
			if(o->Type == 32)
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->StreamMesh = 2;
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight, -(int)WorldTime%4000*0.00025f, o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight, -(int)WorldTime%5000*0.0002f, o->BlendMeshTexCoordV);
				b->StreamMesh = -1;
			}
			else if(o->Type == 39 || o->Type == 41)
			{
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			}
			else if(o->Type == 46)
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			}
			else if(o->Type == 62)
			{
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight);

				vec3_t vPos, vRelativePos, vLight;
				Vector(0.f, 0.f, 0.f, vPos);
				Vector(6.f, 5.f, 2.f, vRelativePos);
				Vector(1.f, 1.f, 1.f, vLight);
				float fLumi = sinf(WorldTime*0.001f)*0.5f+0.5f;
				b->TransformPosition(BoneTransform[22], vRelativePos, vPos);
				Vector(1.f, 0.5f, 0.5f, vLight);
				CreateSprite(BITMAP_SHINY+1, vPos, 1.5f+fLumi/2.f, vLight, NULL);
				Vector(6.f, -5.f, 2.f, vRelativePos);
				b->TransformPosition(BoneTransform[23], vRelativePos, vPos);
				Vector(1.f, 0.5f, 0.5f, vLight);
				CreateSprite(BITMAP_SHINY+1, vPos, 1.5f+fLumi/2.f, vLight, NULL);

				if(rand()%5 == 0)
				{
					Vector(0.f, 0.f, 0.f, vRelativePos);
					b->TransformPosition(BoneTransform[20], vRelativePos, vPos);
					Vector(1.f, 1.f, 1.f, vLight);
					CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight);
				}
			}
			else if(o->Type == 67)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			}
			else if(o->Type == 68)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			}
			else if(o->Type == 64 || o->Type == 65 || o->Type == 66 || o->Type == 80)
			{
				o->m_bRenderAfterCharacter = true;
			}
		}
#ifdef CSK_EVENT_CHERRYBLOSSOM
		else if(o->Type==MODEL_EFFECT_SKURA_ITEM)
		{
			b->RenderBody(RENDER_COLOR,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
#endif //CSK_EVENT_CHERRYBLOSSOM	
		else if(o->Type==MODEL_MONSTER01+26)//����
		{
		    Vector(0.4f,0.6f,1.f,b->BodyLight);
			b->StreamMesh = 0;
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
		    Vector(1.f,1.f,1.f,b->BodyLight);
			b->StreamMesh = -1;
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
        else if ( o->Type==MODEL_PEGASUS )	// ����Ʈ
        {
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
        }
        else if ( o->Type==MODEL_SKIN_SHELL )
        {
            if ( o->SubType==0 )
            {
                VectorCopy ( o->Light, b->BodyLight );
			    b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh, BITMAP_CHROME );
            }
            else if ( o->SubType==1 )
            {
                Vector ( 0.1f, 0.5f, 1.f, b->BodyLight );
			    b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh, BITMAP_CHROME );
            }
        }
        else if ( o->Type==MODEL_STUN_STONE )
        {
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
			
			Vector ( 1.f, 1.f, 1.f, b->BodyLight );
      		b->RenderBody ( RENDER_CHROME, 0.5f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU*5.f, o->BlendMeshTexCoordV*2.f, -1, BITMAP_CHROME );
        }
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
        else if ( o->Type==MODEL_DARK_HORSE && o->SubType == 1)
		{
			// ���ð��� ��ũȣ��
			if (World == WD_65DOPPLEGANGER1)
			{
				//Vector(0.2f, 0.2f, 0.2f, b->BodyLight);
				o->Alpha = 0.7f;
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else
			{
				Vector(0.2f, 0.2f, 0.2f, b->BodyLight);
				b->RenderBody(RENDER_BRIGHT|RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
		}
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
        else if ( o->Type==MODEL_DARK_HORSE )
        {
			Vector(1.f,1.f,1.f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

			Vector(1.f,0.8f,0.3f,b->BodyLight);
			b->RenderMesh(12, RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(13, RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(14, RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->RenderMesh(15, RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

				//  �׸��� ��´�.
			if ( World!=WD_10HEAVEN && InHellas()==false )
			{
				if(!g_Direction.m_CKanturu.IsMayaScene())
				{
					EnableAlphaTest();

					if ( World==WD_7ATLANSE )
					{
						glColor4f(0.f,0.f,0.f,0.2f);
					}
					else
					{
   						glColor4f(0.f,0.f,0.f,0.7f);
					}
					b->RenderBodyShadow ( -1, -1, 8, 9 );
				}
			}
        }
		//^ �渱 �� ������
		else if(o->Type == MODEL_FENRIR_BLACK || o->Type == MODEL_FENRIR_BLUE || o->Type == MODEL_FENRIR_RED
			|| o->Type == MODEL_FENRIR_GOLD
			)
		{
			vec3_t vLight, vPos, vPosition;
			float fLuminosity = (float)sinf((WorldTime)*0.002f)*0.2f;

			b->BeginRender(1.f);

			b->BodyLight[0] = 1.0f;
			b->BodyLight[1] = 1.0f;
			b->BodyLight[2] = 1.0f;

			if(o->Type == MODEL_FENRIR_GOLD)
			{
				b->StreamMesh = 0;

				b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				b->RenderMesh ( 0, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				b->RenderMesh ( 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

				if(o->CurrentAction == FENRIR_ATTACK_SKILL)
				{
					// �ο��� �������� spark03
					Vector ( 1.0f, 0.0f, 0.0f, vLight );
					Vector ( (float)(rand()%10-10)*0.5f, 0.f, (float)(rand()%40-20)*0.5f, vPos );
					b->TransformPosition ( BoneTransform[14], vPos, vPosition, false );	// ��
					CreateParticle(BITMAP_SPARK+1, vPosition, o->Angle, vLight, 15, 0.7f+(fLuminosity*0.05f));
				}

				b->StreamMesh = -1;
			}
			else
			{
				b->StreamMesh = 0;

				b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				b->RenderMesh ( 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				if(o->CurrentAction == FENRIR_ATTACK_SKILL)
				{
					b->BodyLight[0] = 1.0f;
					b->BodyLight[1] = 1.0f;
					b->BodyLight[2] = 1.0f;

					b->RenderMesh ( 1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);

					// �ο��� �������� spark03
					Vector ( 1.0f, 0.0f, 0.0f, vLight );
					Vector ( (float)(rand()%10-10)*0.5f, 0.f, (float)(rand()%40-20)*0.5f, vPos );
					b->TransformPosition ( BoneTransform[14], vPos, vPosition, false );	// ��
					CreateParticle(BITMAP_SPARK+1, vPosition, o->Angle, vLight, 15, 0.7f+(fLuminosity*0.05f));
				}
				b->StreamMesh = -1;
			}

			b->EndRender();
			
			//^ �渱 �׸��� ������
			if (World != WD_10HEAVEN && InHellas() == FALSE)
			{
				if(!g_Direction.m_CKanturu.IsMayaScene())
				{
					EnableAlphaTest();

					if ( World==WD_7ATLANSE )
					{
						glColor4f(0.f,0.f,0.f,0.2f);
					}
					else
					{
   						glColor4f(0.f,0.f,0.f,0.7f);
					}

					b->RenderBodyShadow();
				}
			}

			// ���� flare01
			Vector ( 0.9f+fLuminosity, 0.2f+(fLuminosity*0.5f), 0.1f+(fLuminosity*0.5f), vLight );
			Vector ( 50.f, 2.f, 11.f, vPos );
			b->TransformPosition ( BoneTransform[11], vPos, vPosition, false );	// ���ʴ�
			CreateSprite ( BITMAP_LIGHT, vPosition, 0.5f+(fLuminosity*0.1f), vLight, o);
			CreateSprite ( BITMAP_LIGHT, vPosition, 0.5f+(fLuminosity*0.1f), vLight, o);
			Vector ( 50.f, 2.f, -11.f, vPos );
			b->TransformPosition ( BoneTransform[11], vPos, vPosition, false );	// �����ʴ�
			CreateSprite ( BITMAP_LIGHT, vPosition, 0.5f+(fLuminosity*0.1f), vLight, o);
			CreateSprite ( BITMAP_LIGHT, vPosition, 0.5f+(fLuminosity*0.1f), vLight, o);

			// �Ծȿ� flare01
			Vector ( 1.0f, 0.3f, 0.2f, vLight );
			Vector ( 40.f, 15.f, 0.f, vPos );
			b->TransformPosition ( BoneTransform[13], vPos, vPosition, false );	// �Ծ�
			CreateSprite ( BITMAP_LIGHT, vPosition, 1.5f, vLight, o);
			CreateSprite ( BITMAP_LIGHT, vPosition, 1.0f, vLight, o);

			// �� ������ ����
			int iSubType = 0;
			if(o->Type == MODEL_FENRIR_RED)
			{
				Vector ( 0.8f, 0.0f, 0.0f, vLight );
				iSubType = 1;	// ����
			}
			else if(o->Type == MODEL_FENRIR_BLUE)
			{
				Vector ( 0.1f, 0.1f, 0.8f, vLight );
				iSubType = 2;	// ���
			}
			else if(o->Type == MODEL_FENRIR_GOLD)
			{
				Vector ( 0.8f, 0.8f, 0.1f, vLight );
				iSubType = 4;	// ���
			}
			else 
			{
				Vector ( 1.0f, 1.0f, 0.2f, vLight );
				iSubType = 3;	// ����
			}
			CreateEffect(MODEL_FENRIR_THUNDER, o->Position, o->Angle, vLight, 0, o);
			CreateEffect(MODEL_FENRIR_THUNDER, o->Position, o->Angle, vLight, 0, o);

			// 4�߹ٴ� ����
			Vector(1.0f, 1.0f, 1.0f, vLight);
			if(o->CurrentAction == FENRIR_WALK)
			{
				if(o->AnimationFrame >= 0.0f && o->AnimationFrame <= 1.5f)
				{
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[22], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[28], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[36], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[44], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� ������
				}
			}
			else if(o->CurrentAction == FENRIR_RUN)
			{
				if ( o->AnimationFrame>1.f && o->AnimationFrame<=1.4f )	// �չ�
                {
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[22], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[28], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
                }
                else if ( o->AnimationFrame>4.8f && o->AnimationFrame<=5.2f )	 // �޹�
                {
                    Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[36], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� �޹�
					Vector(0.0f, 0.0f, 0.0f, vPos);
					b->TransformPosition ( BoneTransform[44], vPos, vPosition, false );
					CreateEffect(MODEL_FENRIR_FOOT_THUNDER, vPosition, o->Angle, vLight, iSubType, o);	// �� ������
                }
			}
		}
		else if ( o->Type >= MODEL_FACE && 
#ifdef PBG_ADD_NEWCHAR_MONK
			o->Type <= MODEL_FACE+6
#else //PBG_ADD_NEWCHAR_MONK
			o->Type <= MODEL_FACE+5 
#endif //PBG_ADD_NEWCHAR_MONK
			)           //  ĳ���� ����â�� ������ ��ũ�ε��� ���� ��.
        {
			Vector(4.8f,4.8f,4.8f,b->BodyLight);
      		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			Vector(1.f,1.f,1.f,b->BodyLight);
        }
        else if ( o->Type==MODEL_DARKLORD_SKILL )
        {
            VectorCopy ( o->Light,b->BodyLight );
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
        }
#ifdef PET_SYSTEM
        else if ( o->Type==MODEL_DARK_SPIRIT )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            b->BeginRender(o->Alpha);
            b->RenderMesh ( 3, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
            if ( o->WeaponLevel>=40 )
            {
                b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                Vector ( 0.3f, 0.6f, 1.f, b->BodyLight );                
                b->RenderMesh ( 0, RENDER_CHROME|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                Vector(1.f,1.f,1.f,b->BodyLight);
                b->RenderMesh ( 3, RENDER_BRIGHT|RENDER_TEXTURE, o->Alpha, 3, sinf(WorldTime*0.001f), o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_MONSTER_SKIN+2 );
            }
            else if ( o->WeaponLevel>=20 )
            {
                b->RenderMesh ( 1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
            }
            else
            {
                b->RenderMesh ( 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
            }
            b->EndRender();

            if ( World!=WD_10HEAVEN && InHellas()==false )
            {
				if(!g_Direction.m_CKanturu.IsMayaScene())
				{
					vec3_t Position;
					EnableAlphaTest();

					if ( World==WD_7ATLANSE )
					{
						glColor4f(0.f,0.f,0.f,0.2f);
					}
					else
					{
						glColor4f(0.f,0.f,0.f,1.f);
					}
					VectorCopy(o->Position,Position);
					Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
					VectorCopy(Position,b->BodyOrigin);
					b->RenderBodyShadow();
				}
            }
        }
#endif	// PET_SYSTEM
#ifdef DARK_WOLF
        else if ( o->Type==MODEL_DARK_WOLF )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            b->BeginRender(o->Alpha);
            b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
            if ( o->WeaponLevel>=40 )
            {
            }
            else if ( o->WeaponLevel>=20 )
            {
            }
            else
            {
            }
            b->EndRender();

            if ( World!=WD_10HEAVEN && InHellas()==false )
            {
                vec3_t Position;
			    EnableAlphaTest();

                if ( World==WD_7ATLANSE )
                {
			        glColor4f(0.f,0.f,0.f,0.2f);
                }
                else
                {
			        glColor4f(0.f,0.f,0.f,1.f);
                }
			    VectorCopy(o->Position,Position);
			    Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
			    VectorCopy(Position,b->BodyOrigin);
			    b->RenderBodyShadow();
            }
        }
#endif// DARK_WOLF	
		else if(World==WD_0LORENCIA && o->Type==MODEL_WATERSPOUT)//�м���
		{
			b->BeginRender(o->Alpha);
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,3,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			b->EndRender();
		}
		else if(World==WD_4LOSTTOWER && (o->Type==23||o->Type==19||o->Type==20||o->Type==3||o->Type==4))
		{
			vec3_t Light,p;
			float Luminosity;
			Luminosity = (float)(rand()%2+6)*0.1f;
			Vector(Luminosity*0.4f,Luminosity*0.8f,Luminosity*1.f,Light);
			Vector(0.f,0.f,0.f,p);
			if(o->Type==23)
			{
     			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type==19||o->Type==20)
			{
				VectorCopy(b->BodyLight,Light);
				Vector(1.f,0.2f,0.1f,b->BodyLight);
				b->StreamMesh = 2;
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
				VectorCopy(Light,b->BodyLight);
				b->StreamMesh = -1;
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type==3||o->Type==4)
			{
				VectorCopy(b->BodyLight,Light);
				Vector(1.f,0.2f,0.1f,b->BodyLight);
				b->StreamMesh = 1;
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
				VectorCopy(Light,b->BodyLight);
				b->StreamMesh = -1;
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
		}
        //  Ư�� ���� ������Ʈ�� ũ��ȿ���� �ش�.
		else if(World==WD_8TARKAN && (o->Type==81))   //  ���� ��¦��.
		{
			b->BeginRender(o->Alpha);
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			b->RenderMesh(0,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
			b->EndRender();
		}
        else if ( InBloodCastle() == true && ( o->Type==28 || o->Type==29 ) )
        {   
            //  õ���, õ�����.
            //  �׸��� ȿ��.
			b->BeginRender(o->Alpha);
      		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			b->EndRender();

            EnableAlphaTest();

            vec3_t Position;

			glColor4f(0.f,0.f,0.f,1.f);
			VectorCopy(o->Position,Position);
			Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
			VectorCopy(Position,b->BodyOrigin);
            o->HiddenMesh = 2;
			b->RenderBodyShadow(o->BlendMesh,o->HiddenMesh);
            o->HiddenMesh = -1;
        }
		else if( World == WD_3NORIA && o->Type==MODEL_WARP3)
		{
			b->BodyLight[0] = 0.8f;
			b->BodyLight[1] = 0.8f;
			b->BodyLight[2] = 0.8f;

			b->StreamMesh = 0;
			b->RenderMesh ( 0, RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->StreamMesh = -1;
		}
		else if( World == WD_55LOGINSCENE && o->Type == 90 )
		{
			b->BodyLight[0] = 1.0f;
			b->BodyLight[1] = 1.0f;
			b->BodyLight[2] = 1.0f;

			o->Alpha = 1.0f;
			o->BlendMeshLight = 1.0f;
			b->StreamMesh = 0;
			b->RenderMesh ( 0, RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->StreamMesh = -1;
		}
		else
		{
#ifdef LDK_ADD_SNOWMAN_CHANGERING
			BOOL bIsRendered = TRUE;
#endif	// LDK_ADD_SNOWMAN_CHANGERING
			if(g_isCharacterBuff(o, eDeBuff_Poison) && g_isCharacterBuff(o, eDeBuff_Freeze))
			{
			    Vector(0.3f,1.f,0.8f,b->BodyLight);
			}
			else if( g_isCharacterBuff(o, eDeBuff_Poison) )
			{
			    Vector(0.3f,1.f,0.5f,b->BodyLight);
			}
			else if( g_isCharacterBuff(o, eDeBuff_Freeze) )
			{
			    Vector(0.3f,0.5f,1.f,b->BodyLight);
			}
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
			else if(g_isCharacterBuff(o, eDeBuff_BlowOfDestruction))
			{
				Vector(0.3f,0.5f,1.f,b->BodyLight);
			}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION	

            //  ���� ����, ��Ű���� �������� ������ �ɶ� �� ���� �������ش�.
            if ( o->Type==MODEL_MONSTER01+35 || o->Type==MODEL_MONSTER01+15 || o->Type==MODEL_MONSTER01+50 || o->Type==MODEL_MONSTER01+51 )
            {
                if ( o->Alpha==1.0f && o->BlendMeshLight==0.05f )
                {
                    o->BlendMeshLight = 1.0f;
                }
            }

            if ( RenderHellasObjectMesh( o, b ) ) {}
            else
            if ( battleCastle::RenderBattleCastleObjectMesh( o, b ) ) {}
            else
			if( M31HuntingGround::RenderHuntingGroundObjectMesh(o, b, ExtraMon) ) {}
			else
#ifdef CRYINGWOLF_2NDMVP
			if( M34CryingWolf2nd::RenderCryingWolf2ndObjectMesh(o, b) ) {}
			else
#endif // CRYINGWOLF_2NDMVP
			if( M33Aida::RenderAidaObjectMesh(o, b, ExtraMon) ) {}
			else if( M34CryWolf1st::RenderCryWolf1stObjectMesh(o, b, ExtraMon) ) {}
			else if( M37Kanturu1st::RenderKanturu1stObjectMesh(o, b) ) {}
			else if( M38Kanturu2nd::Render_Kanturu2nd_ObjectMesh(o, b) ) {}
			else if( M39Kanturu3rd::RenderKanturu3rdObjectMesh(o, b, ExtraMon) ) {}
			else if( SEASON3A::CGM3rdChangeUp::Instance().RenderObjectMesh(o, b) ) {}
			else if( g_CursedTemple->RenderObjectMesh(o, b, ExtraMon) ) {}
			else if ( SEASON3B::GMNewTown::RenderObject(o, b, ExtraMon) ) {}
			else if ( SEASON3C::GMSwampOfQuiet::RenderObject(o, b, ExtraMon) ) {}
#ifdef PSW_ADD_MAPSYSTEM
			else if( TheMapProcess().RenderObjectMesh( o, b ) ) {}
#endif //PSW_ADD_MAPSYSTEM
			else
			if(o->Type == MODEL_KALIMA_SHOP)
			{
				Vector(1.f,1.f,1.f,b->BodyLight);
				float Luminosity = sinf( WorldTime*0.002f)*0.3f+0.6f;
				b->BeginRender(o->Alpha);
				b->RenderMesh(4,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				vec3_t Position,Light,p,Angle;
//				Vector(0.2f,0.5f,0.2f,Light);	//���
				Vector(0.4f,0.2f,0.4f,Light);	//�����
                Vector ( 30.f, 40.f, 0.f, p );
                b->TransformPosition ( o->BoneTransform[3], p, Position);

				VectorAdd( Position, o->Position, Position);
				CreateSprite ( BITMAP_LIGHT, Position, Luminosity+3.5f, Light, o,50.f );

                Vector ( 0.f, 0.f, 0.f, p );
                b->TransformPosition ( o->BoneTransform[21], p, Position);
				VectorAdd( Position, o->Position, Position);
				CreateSprite ( BITMAP_LIGHT, Position, Luminosity+3.5f, Light, o,50.f );

				Vector ( 0.f, 0.f, 0.f, Angle );
				Vector(1.f,1.f,1.f,Light);	//�����
				VectorCopy(o->Position, Position);
				Position[0] += 40.f;
				Position[1] += 30.f;
				Position[2] -= 90.f;
				CreateParticle ( BITMAP_SMOKE, Position, Angle, Light, 11, 0.4f);

				VectorCopy(o->Position, Position);
				Position[0] -= 40.f;
				Position[1] -= 30.f;
				Position[2] -= 90.f;
				CreateParticle ( BITMAP_SMOKE, Position, Angle, Light, 11, 0.4f);
				b->EndRender();
			}
			else
			if (o->Type == MODEL_NPC_QUARREL)
			{
				Vector(0.5f,0.5f,0.8f,b->BodyLight);
				b->BeginRender(o->Alpha);
				for(int i = 0; i < Models[o->Type].NumMeshs; i++)
				{
					b->RenderMesh(i,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(i,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
				}
				b->EndRender();
			}
			else
#ifdef ADD_SOCKET_MIX
			if (o->Type == MODEL_SEED_MASTER)	// �õ帶����
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				float fLumi = (sinf(WorldTime*0.001f) + 1.0f) * 0.2f + 0.0f;
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,fLumi,1,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
			else
#endif	// ADD_SOCKET_MIX
#ifdef LOREN_RAVINE_EVENT
			///test...����Ʈ...������
			if(o->Type == MODEL_MONSTER01+45)
			{
				if(ExtraMon)
				{
					Vector(1.f,1.f,1.f,b->BodyLight);
//					Vector(0.7f,0.5f,0.8f,b->BodyLight);
					b->BeginRender(o->Alpha);
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(0,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(1,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
					b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(2,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
					b->EndRender();
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
			else
#endif // LOREN_RAVINE_EVENT
			if(o->Type==MODEL_MONSTER01+42 && o->SubType==1)//����
			{
				b->BeginRender(o->Alpha);
           		float Light = sinf(WorldTime*0.002f)*0.01f+1.f;
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,Light,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_MONSTER_SKIN+1);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,Light,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_MONSTER_SKIN);
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,Light,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,Light,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->EndRender();
			}
			else if(o->Type==MODEL_MONSTER01+62)	// �����ذ�
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,2,1.0f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
            else if( o->Type==MODEL_MONSTER01+49 )  //  ���б���
			{
				b->BeginRender(o->Alpha);
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->EndRender();
				CSideHair *pSideHair = new CSideHair;
				pSideHair->Create( VertexTransform, b, o);
				pSideHair->Render( VertexTransform, LightTransform);
				pSideHair->Destroy();
			}
            else if( o->Type==MODEL_MONSTER01+54 )  //  ��� ����ٲٱ�
            {
				if ( ExtraMon)
				{
					Vector( .1f, 0.1f, 0.1f,b->BodyLight);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
					Vector( 1.0f, 0.1f, 0.1f,b->BodyLight);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
		    else if( o->Type==MODEL_MONSTER01+46 )   //  ��ũ�ü�->�ı��� ��ũ �ü�. ����ٲٱ�
			{
				if ( ExtraMon)
				{
					Vector( 1.0f, 1.0f, 1.0f,b->BodyLight);
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR0);
//					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR1);
					b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR2);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
		    else if( o->Type==MODEL_MONSTER01+47 )   //  ��ũ����->�ı��� ��ũ ����. ����ٲٱ�
			{
				if ( ExtraMon)
				{
					Vector( 1.0f, 1.0f, 1.0f,b->BodyLight);
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR1);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR0);
					//b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DEST_ORC_WAR2);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
		    else if( o->Type==MODEL_MONSTER01+48 )   //  ���ֹ�����->�鸶����. ����ٲٱ�
			{
				if ( ExtraMon)
				{
					Vector( 1.0f, 1.0f, 1.0f,b->BodyLight);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,BITMAP_WHITE_WIZARD);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
            else if( o->Type==MODEL_MONSTER01+52 )  //  ����ũ����Ʈ
            {
				if(ExtraMon == 0)
				{
					float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
					Vector(Luminosity+0.5f,0.3f-Luminosity*0.5f,-Luminosity*0.5f+0.5f,b->BodyLight);
					//Vector(1.f,1.f,1.f,b->BodyLight);
					//if ( c->Dead == 0)
					{	// �׾����� �ȻѸ��� ����
						b->StreamMesh = 0;
						Vector(.4f,.3f,.5f,b->BodyLight);
						b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_JANUSEXT);
						Vector(.5f,.5f,.5f,b->BodyLight);
						b->StreamMesh = -1;
					}
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
				else
				if(ExtraMon == 301)
				{
//					b->BodyScale     = o->Scale + (o->Scale/1.0f);
//					Vector(0.7f,0.5f,0.8f,b->BodyLight);
					Vector(1.f,1.f,1.f,b->BodyLight);
					b->BeginRender(o->Alpha);
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(0,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(1,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME);
					b->EndRender();
				}
				else
				//Vector(.7f,.2f,.2f,b->BodyLight);
				{	// �ް�ũ����Ʈ2	// ����ٲٱ�
					Vector(0.1f,1.0f,.8f,b->BodyLight);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					//Vector( 0.1f, sinf(WorldTime*0.002f)*0.5f+0.5f, sinf(WorldTime*0.00173f)*0.5f+0.5f,b->BodyLight);
				}
            }
            else if( o->Type==MODEL_MONSTER01+53 )  //  ��ī�罺.
            {
                float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
		        Vector(Luminosity+0.5f,0.3f-Luminosity*0.5f,-Luminosity*0.5f+0.5f,b->BodyLight);
		        //Vector(1.f,1.f,1.f,b->BodyLight);
				Vector(.9f,.8f,1.0f,b->BodyLight);
		        b->RenderBody(RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		        Vector(1.f,1.f,1.f,b->BodyLight);
				//Vector(.7f,.2f,.2f,b->BodyLight);
		        b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            }
			else if( o->Type==MODEL_MONSTER01+51)	//	���ǿ���
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,-1);
				//b->RenderMesh(1,RENDER_TEXTURE|RENDER_PONG|RENDER_WAVE,1.0f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_WAVE,0.5f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_WAVE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}

#ifdef PRUARIN_EVENT07_3COLORHARVEST
			else if( o->Type == MODEL_MONSTER01+127 )	// ���䳢
			{			
				b->RenderBody(RENDER_TEXTURE, o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if( o->Type == MODEL_MOONHARVEST_MOON )	// �� (���䳢 �״� ����Ʈ)
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if( o->Type == MODEL_MOONHARVEST_GAM )	// �� (���䳢 �״� ����Ʈ)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if( o->Type == MODEL_MOONHARVEST_SONGPUEN1 )	// ����-��� (���䳢 �״� ����Ʈ)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if( o->Type == MODEL_MOONHARVEST_SONGPUEN2 )	// ����-��� (���䳢 �״� ����Ʈ)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif // PRUARIN_EVENT07_3COLORHARVEST
#ifdef CSK_EVENT_CHERRYBLOSSOM
			else if( o->Type==MODEL_NPC_CHERRYBLOSSOM )
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,2.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_CHROME7,0.25f,o->BlendMesh,1.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderBody(RENDER_TEXTURE,0.8f,o->BlendMesh,2.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,0);
			}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_EVENT_CHERRYBLOSSOMTREE
			else if( o->Type==MODEL_NPC_CHERRYBLOSSOMTREE )
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif //PSW_EVENT_CHERRYBLOSSOMTREE			

			else if(o->Type==MODEL_MONSTER01+56)	// �һ��� ź ����
			{
				b->StreamMesh = 0;
				Vector(1.f,1.0f,1.0f,b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
				b->StreamMesh = -1;
				Vector(.6f,.6f,.6f,b->BodyLight);
      			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
            else if ( o->Type==MODEL_MONSTER01+60 )     //  ����.
            {
                if (  o->CurrentAction==MONSTER01_DIE || 
					( MoveSceneFrame - o->InitialSceneFrame) < 25
					)
                {
					if ( o->CurrentAction==MONSTER01_DIE)
					{
						o->Live = false;
					}

                    PlayBuffer(SOUND_HIT_GATE2);
                    b->RenderMeshEffect ( 0, MODEL_STONE_COFFIN );
                }
                else
                {
      			    b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		            Vector(1.f,1.f,1.f,b->BodyLight);
		            b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
		            Vector(0.3f,0.3f,1.f,b->BodyLight);
		            b->RenderBody(RENDER_BRIGHT|RENDER_METAL,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
                }
            }
            else if ( o->Type==MODEL_MONSTER01+61 && o->CurrentAction==MONSTER01_DIE ) //  ����.
            {
                o->Live = false;

                PlayBuffer(SOUND_HIT_GATE2);
                b->RenderMeshEffect ( 0, MODEL_GATE );
            }
            else if ( o->Type==MODEL_STONE_COFFIN || o->Type==MODEL_STONE_COFFIN+1 )
            {
                if ( o->SubType==2 || o->SubType==3 )
                {
                    if ( o->SubType==2  )
                    {
                        Vector(0.1f,0.3f,0.6f,b->BodyLight);
                    }
                    else
                    {
		                Vector(0.1f,0.6f,0.3f,b->BodyLight);
                    }
		            b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
                }
                else
                {
      			    b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		            Vector(1.f,1.f,1.f,b->BodyLight);
		            b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
		            Vector(0.3f,0.3f,1.f,b->BodyLight);
		            b->RenderBody(RENDER_BRIGHT|RENDER_METAL,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
                }
            }
            else if ( o->Type==MODEL_FLY_BIG_STONE1 )
            {
                if ( o->HiddenMesh==99 && o->Visible )
                {
                    o->HiddenMesh = -2;
                    b->RenderMeshEffect ( 0, MODEL_BIG_STONE_PART1 );
                }
                else
                {
                    Vector ( 1.f, 1.f, 1.f, b->BodyLight );
                    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                    if ( o->SubType<=1 )
                    {
                        Vector ( 1.0f, 0.2f, 0.1f, b->BodyLight );
                        b->RenderBody ( RENDER_CHROME|RENDER_BRIGHT, o->Alpha, o->BlendMesh, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                    }
                }
            }
            else if ( o->Type==MODEL_FLY_BIG_STONE2 )
            {
                if ( o->HiddenMesh==99 && o->Visible )
                {
                    o->HiddenMesh = -2;
                    b->RenderMeshEffect ( 0, MODEL_BIG_STONE_PART2 );
                }
                else
                {
                    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                }
            }
            else if ( o->Type==MODEL_BIG_STONE_PART1 || o->Type==MODEL_BIG_STONE_PART2 )
            {
                if ( o->SubType==1 )
                {
                    Vector ( 1.f, 1.f, 1.f, b->BodyLight );
                    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                    Vector ( 1.0f, 0.2f, 0.1f, b->BodyLight );
                    b->RenderBody ( RENDER_CHROME|RENDER_BRIGHT, o->Alpha, o->BlendMesh, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                    Vector ( 1.f, 1.f, 1.f, b->BodyLight );
                }
				else if ( o->SubType==2 || o->SubType==3)
				{	//. ���� �ٲ۴�.
					Vector(0.5f,1.0f,0.3f,b->BodyLight);
					b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
					Vector(1.f,1.f,1.f,b->BodyLight);
				}
                else
                {
                    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
                }
            }
            else if ( o->Type==MODEL_WALL_PART1 || o->Type==MODEL_WALL_PART2 )
            {
                b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
            }
            else if ( o->Type==MODEL_MONSTER01+70 || o->Type==MODEL_MONSTER01+71 )
            {
      			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            }
            else if ( o->Type==MODEL_COMBO && o->SubType==1 )   //  ��Ʈ�� �Ǿ�.
			{	// ���� �Ѹ���
      			b->RenderBody(RENDER_TEXTURE|o->RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
            else if ( o->Type==MODEL_CIRCLE_LIGHT && ( o->SubType==3 || o->SubType==4 ) )
            {
		        Vector ( 0.1f, 0.1f, 10.f, b->BodyLight );
      			b->RenderBody ( RENDER_TEXTURE|o->RenderType , o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
		        Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            }
            else if ( o->Type==MODEL_CIRCLE && ( o->SubType==2 || o->SubType==3 ) )
            {
		        Vector ( 0.5f, 0.5f, 1.f, b->BodyLight );
      			b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh, BITMAP_MAGIC_EMBLEM );
		        Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            }

#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
			else if(o->Type == MODEL_MULTI_SHOT1||o->Type == MODEL_MULTI_SHOT2||o->Type == MODEL_MULTI_SHOT3)
			{
//				Vector ( 0.7f, 0.7f, 1.f, b->BodyLight );
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody ( RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
			}
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
			else if(o->Type == MODEL_DESAIR)
			{
				Vector(1.f,1.f,1.f,o->Light);
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody ( RENDER_TEXTURE|RENDER_DARK, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
			}
#endif //SKILL_DEBUG
			else if(o->Type == MODEL_DARK_SCREAM)
			{
                b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
   			}
			else if(o->Type == MODEL_DARK_SCREAM_FIRE)
			{
				b->RenderBody ( RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
			}
			else if(o->Type == MODEL_ARROW_SPARK)
			{
                b->RenderBody ( RENDER_TEXTURE|RENDER_CHROME5|RENDER_BRIGHT, o->Alpha, o->BlendMesh, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
   			}
            else if ( o->Type==MODEL_SKULL )
            {
                Vector ( 1.f, 0.6f, 0.3f, b->BodyLight );   //  ������.
      			b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
                
                //  �Ժ����� ���� ���� �Ѵ�. 
				vec3_t Light, p;

                //  ���� ��ġ�� ����Ѵ�.
                Vector ( 0.f, 0.f, 0.f, p );
                b->TransformPosition ( BoneTransform[2], p, o->EyeLeft, false );
                b->TransformPosition ( BoneTransform[3], p, o->EyeRight, false );

                Vector ( 1.f, 0.f, 0.f, Light );
                CreateSprite ( BITMAP_LIGHT, o->EyeLeft, 1.f, Light, o );
                CreateSprite ( BITMAP_LIGHT, o->EyeRight, 1.f, Light, o );
                Vector ( 0.5f, 0.5f, 0.5f, Light );
                CreateSprite ( BITMAP_SHINY+1, o->EyeLeft, 0.5f, Light, o, (float)(rand()%360) );
                CreateSprite ( BITMAP_SHINY+1, o->EyeRight, 0.5f, Light, o, (float)(rand()%360) );
            }
            else if ( o->Type==MODEL_WAVES )
            {
                if ( o->SubType==3 )
      			    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, -1, BITMAP_PINK_WAVE );
                else if ( o->SubType==4 || o->SubType==5 )
      			    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, -1, BITMAP_PINK_WAVE );
                else
      			    b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
            }
            else if ( o->Type==MODEL_PROTECTGUILD )
            {
		        Vector ( 0.4f, 0.6f, 1.f, b->BodyLight );
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh );
           }
            else if ( o->Type==MODEL_WEBZEN_MARK )
            {
		        Vector ( 1.f, 1.f, 1.f, b->BodyLight );
      			b->RenderBody ( RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		        Vector ( 1.f, 0.5f, 0.f, b->BodyLight );
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            }
            else if ( o->Type==MODEL_MANA_RUNE && o->SubType==0 )
            {
		        Vector ( 0.3f, 0.6f, 1.f, b->BodyLight );
      			b->RenderBody ( RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            }
            else if ( o->Type==MODEL_SKILL_JAVELIN )
            {
		        Vector ( 1.f, 0.6f, 0.3f, b->BodyLight );
      			b->RenderBody ( RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
            }
            else if ( o->Type==MODEL_MAGIC_CAPSULE2 && o->SubType==1 )
            {
				b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME4,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
      			b->RenderBody ( RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            }
			else if ( o->Type==MODEL_ARROW_AUTOLOAD)
			{
				vec3_t Light, p1, p2;
				VectorCopy(o->Light, b->BodyLight);
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				float fScale = 5.5f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				Vector(0.f, 0.f, 0.f, p1);
				Vector(1.0f, 0.8f, 0.3f, Light);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				
				if(o->LifeTime > 15)
				{
					b->TransformPosition(BoneTransform[1], p1, p2);
					CreateParticle(BITMAP_LIGHT+1, p2, o->Angle, Light, 5, 0.6f);
					b->TransformPosition(BoneTransform[3], p1, p2);
					CreateParticle(BITMAP_LIGHT+1, p2, o->Angle, Light, 5, 0.8f);
				}
			}
			else if ( o->Type == MODEL_INFINITY_ARROW)
			{
				vec3_t p1, p2;
				Vector(0.f, 0.f, 0.f, p1);
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				float Luminosity = sinf( WorldTime*0.002f)*0.3f+0.6f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				for(int idx = 1; idx <= 9; ++idx)
				{
					if(idx == 5) continue;
					b->TransformPosition( BoneTransform[idx], p1, p2);
					CreateJoint ( BITMAP_FLARE+1, p2, o->Position, o->Angle, 16, o, 20.f );
				}
			}
			else if ( o->Type >= MODEL_INFINITY_ARROW && o->Type <= MODEL_INFINITY_ARROW4)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if (o->Type==MODEL_SHIELD_CRASH || o->Type == MODEL_SHIELD_CRASH2)
			{
				VectorCopy(o->Light, b->BodyLight);
	      		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);				
			}
			else if (o->Type==MODEL_IRON_RIDER_ARROW)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if (o->Type==MODEL_BLADE_SKILL)
			{
				VectorCopy(o->Light, b->BodyLight);
				for(int abc = 0; abc < 3; abc++)
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if (o->Type==MODEL_KENTAUROS_ARROW)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_XMAS_EVENT_EARRING)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,-WorldTime*0.0002f,o->BlendMeshTexCoordV, BITMAP_CHROME);	
				vec3_t vPos, vRelativePos, vLight;
				Vector(1.f, 1.f, 1.f, vLight);
				Vector(18.f, 0.f, 6.f, vRelativePos);
				b->TransformPosition(BoneTransform[0],vRelativePos,vPos,true);
				float fLumi = (sinf(WorldTime*0.004f) + 1.0f) * 0.05f;
				Vector(0.8f+fLumi, 0.8f+fLumi, 0.3f+fLumi, o->Light);
				CreateSprite(BITMAP_LIGHT, vPos, 0.4f, o->Light, o, 0.5f);
				if(rand()%15 == 8)
				{
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 5, 0.5f);
				}
				Vector(-18.f, 0.f, 6.f, vRelativePos);
				b->TransformPosition(BoneTransform[0],vRelativePos,vPos,true);
				CreateSprite(BITMAP_LIGHT, vPos, 0.4f, o->Light, o, 0.5f);
				if(rand()%15 == 11)
				{
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 5, 0.5f);
				}
			}
			else if(o->Type == MODEL_XMAS_EVENT_ICEHEART)
			{
				b->StreamMesh = 0;
				Vector(1.f, 0.4f ,0.4f, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,-(int)WorldTime%2000*0.0005f, o->BlendMeshTexCoordV, o->HiddenMesh);
				b->StreamMesh = -1;
			}
			else if(o->Type == MODEL_ARROW_BEST_CROSSBOW)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_NEWYEARSDAY_EVENT_PIG)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				Vector(1.0f, 0.4f, 0.2f, b->BodyLight);
				b->RenderBody(RENDER_CHROME3|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				Vector(1.0f, 1.f, 1.f, b->BodyLight);
			}
			else if(o->Type == MODEL_FENRIR_THUNDER)
			{
				if(o->SubType == 1)
				{
					VectorCopy(o->Light, b->BodyLight);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					Vector(1.f, 1.f, 1.f, b->BodyLight);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
			else if (o->Type==MODEL_MAP_TORNADO)
			{
	      		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
			}
			else if (o->Type>=MODEL_SUMMONER_CASTING_EFFECT1 && o->Type<=MODEL_SUMMONER_CASTING_EFFECT4)
			{
	      		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
			}
			else if (o->Type==MODEL_SUMMONER_SUMMON_SAHAMUTT)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
	      		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME7,o->Alpha,o->BlendMesh,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
			}
			else if (o->Type==MODEL_SUMMONER_SUMMON_NEIL)
			{
				if (o->Alpha < 0.7f)
				{
					b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
					b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,2,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
				}
				else
				{
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
					b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
				}
				Vector(1.0f, 0.0f, 0.0f, b->BodyLight);
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,1,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);

				vec3_t  vPos, vRelative, vLight;
				Vector(0.0f, 0.0f, 0.0f, vRelative);
				Vector(1.0f, 0.0f, 0.0f, vLight);
				for (int i = 51; i <= 59; ++i)
				{
					b->TransformPosition(BoneTransform[i], vRelative, vPos, false);
					CreateSprite ( BITMAP_LIGHT, vPos, 1.0f, vLight, o);
				}

				// �˱�
				float Start_Frame = 0.f;
				float End_Frame = 10.0f;
				if(o->AnimationFrame >= Start_Frame && o->AnimationFrame <= End_Frame && o->CurrentAction == 0)
				{
					vec3_t  Light;
					Vector(1.0f, 0.0f, 0.0f, Light);

					vec3_t StartPos, StartRelative;
					vec3_t EndPos, EndRelative;
					
					float fActionSpeed = o->Velocity;
					float fSpeedPerFrame = fActionSpeed/10.f;
					float fAnimationFrame = o->AnimationFrame - fActionSpeed;
					for(int i=0; i<10; i++) 
					{
						b->Animation(BoneTransform, fAnimationFrame, o->PriorAnimationFrame, o->PriorAction, o->Angle, o->HeadAngle);

						Vector(0.f, 0.f, 0.f, StartRelative);
						Vector(0.f, 0.f, 0.f, EndRelative);

						b->TransformPosition(BoneTransform[51], StartRelative, StartPos, false);
						b->TransformPosition(BoneTransform[59], EndRelative, EndPos, false);
						CreateObjectBlur(o, StartPos, EndPos, Light, 2);
						
						fAnimationFrame += fSpeedPerFrame;
					}
				}
			}
			else if (o->Type>=MODEL_SUMMONER_SUMMON_NEIL_NIFE1 && o->Type<=MODEL_SUMMONER_SUMMON_NEIL_NIFE3)
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
				Vector(1.0f, 0.0f, 0.0f, b->BodyLight);
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
			}
			else if (o->Type>=MODEL_SUMMONER_SUMMON_NEIL_GROUND1 && o->Type<=MODEL_SUMMONER_SUMMON_NEIL_GROUND3)
			{
	      		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
	      		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->Alpha,-WorldTime*0.001f,o->BlendMeshTexCoordV,-1);
			}
#ifdef ASG_ADD_SUMMON_RARGLE
			else if (o->Type == MODEL_SUMMONER_SUMMON_LAGUL)
			{
				// �����ϰ� ����.
				// RENDER_BRIGHT���� ���İ� ������ BlendMesh,float BlendMeshLight ���ڿ� ������ ���� �־�� ��.
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
	      		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->Alpha,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1);
			}
#endif	// ASG_ADD_SUMMON_RARGLE
#ifdef ADD_RAKLION_IRON_KNIGHT
			else if (o->Type>=MODEL_EFFECT_BROKEN_ICE0 && o->Type<=MODEL_EFFECT_BROKEN_ICE3)
			{
				VectorCopy(o->Light, b->BodyLight);
	      		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif	// ADD_RAKLION_IRON_KNIGHT
			else if( o->Type == MODEL_MOVE_TARGETPOSITION_EFFECT )
			{
				Vector(1.0f, 0.7f, 0.3f, b->BodyLight);
				b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight);
			}
#ifdef ADD_SOCKET_ITEM
			else if( o->Type == MODEL_ARROW_DARKSTINGER )
			{
 				b->BodyLight[0] = 0.7f;
 				b->BodyLight[1] = 0.7f;
 				b->BodyLight[2] = 0.9f;
				
				b->RenderMesh(0, RENDER_TEXTURE,o->Alpha, 0, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);

				b->BodyLight[0] = 0.3f;
 				b->BodyLight[1] = 0.4f;
 				b->BodyLight[2] = 0.9f;
				b->RenderMesh(1, RENDER_TEXTURE,o->Alpha, 1, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);

				// �ǵ�����
				b->BodyLight[0] = 1.0f;
 				b->BodyLight[1] = 1.0f;
 				b->BodyLight[2] = 1.0f;
			}
			else if( o->Type == MODEL_FEATHER )
			{
				if(o->SubType == 2 || o->SubType == 3)
					b->RenderBody(RENDER_TEXTURE|RENDER_DARK,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				else
					b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, 0, o->Alpha, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);	
			}
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_GAMBLERS_WEAPONS
			else if( o->Type == MODEL_ARROW_GAMBLE )
			{
				b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, o->Alpha, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
			}
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef LDK_ADD_PC4_GUARDIAN
			else if( o->Type == MODEL_HELPER+64  ) //����
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha ,o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
				//b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_DEMONWING_R);
			}
			else if( o->Type == MODEL_HELPER+65 ) //��ȣ����
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDK_ADD_SNOWMAN_CHANGERING
			else
			{
				bIsRendered = FALSE;
			}

			if (bIsRendered == TRUE)
			{
				// �̹� �׸����� �н�
			}
			else if( o->Type == MODEL_XMAS2008_SNOWMAN )
			{
				if( o->CurrentAction == MONSTER01_DIE )
				{
					if (o->LifeTime == 100)
					{
						o->LifeTime = 90;	// �ѹ��� ����
						o->m_bRenderShadow = false;
						
						vec3_t vRelativePos, vWorldPos, Light;
						Vector(1.0f,1.0f,1.0f,Light);
						Vector(0.f, 0.f, 0.f, vRelativePos);
						
						b->TransformPosition(o->BoneTransform[7], vRelativePos, vWorldPos, true);
						CreateEffect(MODEL_XMAS2008_SNOWMAN_HEAD,vWorldPos,o->Angle,Light,0,o,0,0);	// �Ӹ�

						CreateEffect(MODEL_XMAS2008_SNOWMAN_BODY,o->Position,o->Angle,Light,0,o,0,0);	// ����
					}
				}
				else
				{
					vec3_t vRelativePos, vWorldPos, Light;
					Vector(0.f, 0.f, 0.f, vRelativePos);
					Vector(0.8f, 0.8f, 0.9f, Light);
										
					b->TransformPosition(o->BoneTransform[7], vRelativePos, vWorldPos, true); //�Ӹ�
					CreateSprite(BITMAP_LIGHT, vWorldPos, 6.0f, Light, o);
					CreateSprite(BITMAP_LIGHT, vWorldPos, 4.0f, Light, o);
					
					b->TransformPosition(o->BoneTransform[34], vRelativePos, vWorldPos, true); //�����
					CreateParticle(BITMAP_SHINY, vWorldPos, o->Angle, Light, 7 );
					Vector(1.0f, 0.8f, 0.2f, Light);
					CreateSprite(BITMAP_LIGHT, vWorldPos, 2.0f, Light, o);

					if( o->CurrentAction == MONSTER01_WALK )
					{
						vRelativePos[0] = o->Position[0] + sinf( ((rand()%360) * 6.12) ) * 40.0f;
						vRelativePos[1] = o->Position[1] + sinf( ((rand()%360) * 6.12) ) * 40.0f;
						vRelativePos[2] = o->Position[2];
						CreateParticle(BITMAP_SMOKE, vRelativePos, o->Angle, o->Light); //�� ��
					}

					b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ��
					b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
					b->RenderMesh(3, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ������
					b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
				}
			}
			else if( o->Type == MODEL_XMAS2008_SNOWMAN_BODY )
			{
				b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ��
				b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
				b->RenderMesh(3, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ������
				b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
			}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
			else if( o->Type == MODEL_FEATHER_FOREIGN )
			{
				if(o->SubType == 2 || o->SubType == 3)
					b->RenderBody(RENDER_TEXTURE|RENDER_DARK,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				else
					b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, 0, o->Alpha, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);	
			}
#endif //LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
			else if( o->Type == MODEL_SWELL_OF_MAGICPOWER )
			{
				o->BlendMesh = 0;
				Vector(0.7f, 0.4f, 0.9f, b->BodyLight);

				if( o->LifeTime <= 20 )
				{
					o->BlendMeshLight *= 0.86f;
				}
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if( o->Type == MODEL_ARROWSRE06 )
			{
				o->BlendMesh = 0;
				VectorCopy( o->Light, b->BodyLight );
				//Vector(0.7f, 0.2f, 0.9f, b->BodyLight);
				if( o->LifeTime <= 10 )
				{
					o->BlendMeshLight *= 0.8f;
				}
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef LDK_ADD_SNOWMAN_NPC
			else if( o->Type == MODEL_XMAS2008_SNOWMAN_NPC )
			{
				vec3_t vRelativePos, vWorldPos, Light;
				Vector(0.f, 0.f, 0.f, vRelativePos);
				Vector(0.8f, 0.8f, 0.9f, Light);
				
				b->TransformPosition(o->BoneTransform[7], vRelativePos, vWorldPos, true); //�Ӹ�
				CreateSprite(BITMAP_LIGHT, vWorldPos, 6.0f, Light, o);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 4.0f, Light, o);
				
				b->TransformPosition(o->BoneTransform[34], vRelativePos, vWorldPos, true); //�����
				CreateParticle(BITMAP_SHINY, vWorldPos, o->Angle, Light, 7 );
				Vector(1.0f, 0.8f, 0.2f, Light);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 2.0f, Light, o);

				b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ��
				b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
				b->RenderMesh(3, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//Ʈ������
				b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);//����
			}
#endif //LDK_ADD_SNOWMAN_NPC
#ifdef LDK_ADD_SANTA_NPC
			else if( o->Type == MODEL_XMAS2008_SANTA_NPC )
			{
				vec3_t vRelativePos, vWorldPos, Light;
				Vector(0.f, 0.f, 0.f, vRelativePos);

				b->TransformPosition(o->BoneTransform[4], vRelativePos, vWorldPos, true); //�ı�
				Vector(1.0f, 0.8f, 0.2f, Light);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 8.0f, Light, o);

				b->TransformPosition(o->BoneTransform[13], vRelativePos, vWorldPos, true); //����1
				Vector(1.0f, 0.4f, 0.0f, Light);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 5.0f, Light, o);

				b->TransformPosition(o->BoneTransform[38], vRelativePos, vWorldPos, true); //��
				Vector(1.0f, 0.8f, 0.2f, Light);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 2.0f, Light, o);

				vRelativePos[1] = 17.0f;
				b->TransformPosition(o->BoneTransform[53], vRelativePos, vWorldPos, true); //�ٸ�
				Vector(1.0f, 0.4f, 0.0f, Light);
				RenderAurora(BITMAP_LIGHTMARKS, RENDER_BRIGHT, vWorldPos[0], vWorldPos[1], 2.0f, 2.0f, Light);

				b->TransformPosition(o->BoneTransform[58], vRelativePos, vWorldPos, true); //�ٸ�
				Vector(1.0f, 0.4f, 0.0f, Light);
				RenderAurora(BITMAP_LIGHTMARKS, RENDER_BRIGHT, vWorldPos[0], vWorldPos[1], 2.0f, 2.0f, Light);

				//ȭȯ
				Vector(0.f, 0.f, 0.f, vRelativePos);
				int temp[11] = { 39, 41, 43, 44, 46, 49, 40, 42, 45, 47, 48 };
           		float fCos1 = cosf( WorldTime*0.002f );
           		float fCos2 = sinf( WorldTime*0.002f );
				float fSize = 0.0f;
				for(int i=0; i<11; i++)
				{
					b->TransformPosition(o->BoneTransform[temp[i]], vRelativePos, vWorldPos, true);

					if(i < 6)
					{
						Vector(1.0f, 0.9f, 0.3f, Light);
						fSize = 0.7f * fCos1;
					}
					else
					{
						Vector(1.0f, 0.5f, 0.5f, Light);
						fSize = 0.7f * fCos2;
					}
					CreateSprite(BITMAP_LIGHT, vWorldPos, fSize, Light, o);
				}

				float fScale = 0.0f;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				int _tempTime = 0;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				switch( o->CurrentAction )
				{
				case 1: //������
 					vRelativePos[0] = 20+(rand()%500-250)*0.1f;
 					vRelativePos[1] = (rand()%300-150)*0.1f;
					b->TransformPosition(o->BoneTransform[16], vRelativePos, vWorldPos, true); //��

					Vector((rand()%90+10)*0.01f, (rand()%90+10)*0.01f, (rand()%90+10)*0.01f, Light);
					fScale = (rand()%5+5)*0.1f;
					CreateParticle(BITMAP_LIGHT, vWorldPos, o->Angle, Light, 13, fScale, o);
					CreateParticle(BITMAP_LIGHT, vWorldPos, o->Angle, Light, 13, fScale, o);
					CreateParticle(BITMAP_LIGHT, vWorldPos, o->Angle, Light, 13, fScale, o);
					CreateParticle(BITMAP_SHINY, vWorldPos, o->Angle, Light, 7 );

					Vector(1.0f, 0.8f, 0.2f, Light);
					Vector(0.f, 0.f, 0.f, vRelativePos);
					b->TransformPosition(o->BoneTransform[16], vRelativePos, vWorldPos, true); //��
					CreateSprite(BITMAP_LIGHT, vWorldPos, 2.5f, Light, o);
					break;
				case 2: //����
					Vector(150.0f, 0.0f, 0.0f, vRelativePos);
					b->TransformPosition(o->BoneTransform[6], vRelativePos, vWorldPos, true); //��
					Vector(0.8f, 0.8f, 0.9f, Light);

					if(o->AnimationFrame < 1) o->AI = 0;
#ifdef YDG_ADD_FIRECRACKER_ITEM
					if( o->AI == 0&&o->AnimationFrame > 1 )
					{
						o->AI = 1;
						CreateSprite(BITMAP_LIGHT, vWorldPos, 0.5f, Light, o);
						CreateSprite(BITMAP_DS_SHOCK, vWorldPos, 0.15f, Light, o);
						CreateEffect(BITMAP_FIRECRACKER0002,vWorldPos,o->Angle,Light,o->Skill);

						//CreateJoint(BITMAP_JOINT_SPIRIT, o->Position, o->Position, o->Angle, 25, o, 1.f, -1, 0 );
					}
#endif	// YDG_ADD_FIRECRACKER_ITEM
					break;
				}

				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif //LDK_ADD_SANTA_NPC
#ifdef YDG_ADD_SANTA_MONSTER
			else if( o->Type==MODEL_MONSTER01+155)	// ���ֹ��� ��Ÿ
			{
				if (o->CurrentAction == MONSTER01_DIE)
				{
					vec3_t vLight;
					Vector(1.0 * o->Alpha, 0.8 * o->Alpha, 0.5 * o->Alpha, vLight);
					vec3_t vPosition;
					Vector(o->Position[0], o->Position[1], o->Position[2] + 200, vPosition);

					if (o->AnimationFrame >= 13)//11
					{
						o->Angle[2] = 45;
						if (o->AI != 0)
						{
							o->AI -= 1;
							vec3_t vPos, Position;
							Vector(o->Position[0], o->Position[1], o->Position[2] + 250, vPos);
							
							// ����ũ
							vec3_t vLight;
							Vector(0.7f, 0.3f, 0.0f, vLight);
							for( int i=0 ; i<30 ; i++)
							{
								// �����°�
								CreateParticle(BITMAP_SPARK+1, vPos, o->Angle, vLight, 27 );
							}				
#ifdef _VS2008PORTING
							for( int i=0 ; i<20 ; i++ )
#else // _VS2008PORTING
							for( i=0 ; i<20 ; i++ )
#endif // _VS2008PORTING
							{
								// ������ �������°�
								CreateParticle(BITMAP_SPARK+1, vPos, o->Angle, vLight, 28 );
							}
							
							// ��½
							Vector(vPos[0]+(rand()%100-50), vPos[1]+(rand()%100-50),
								vPos[2], Position);
							CreateSprite(BITMAP_DS_SHOCK, Position, rand()%10*0.1f+1.5f, o->Light, o);

							// ��
#ifdef _VS2008PORTING
							for(int i=0 ; i<60 ; i++ )
#else // _VS2008PORTING
							for( i=0 ; i<60 ; i++ )
#endif // _VS2008PORTING
							{
								Vector(0.3f+(rand()%700)*0.001f, 0.3f+(rand()%700)*0.001f, 0.3f+(rand()%700)*0.001f, vLight);
								CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 9 );
							}

							vPos[2] += 50;
#ifdef _VS2008PORTING
							for (int i = 0; i < 3; ++i)
#else // _VS2008PORTING
							for ( i = 0; i < 3; ++i)
#endif // _VS2008PORTING
							{
								CreateEffect(MODEL_HALLOWEEN_CANDY_STAR, vPos, o->Angle, vLight, 1);
								CreateEffect(rand()%4+MODEL_XMAS_EVENT_BOX, vPos, o->Angle, vLight, 0, o);
								CreateEffect(rand()%4+MODEL_XMAS_EVENT_BOX, vPos, o->Angle, vLight, 0, o);
							}
						}

						b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOOD_SANTA);
						b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOOD_SANTA_BAGGAGE);
						b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

						CreateSprite(BITMAP_LIGHT,vPosition,5.5f,vLight,o);
					}
					else if (o->AnimationFrame >= 9)//9
					{
						o->AI = 3;
						o->Alpha = 1.0f;

						o->Angle[2] += 40.0f;
						
						float fFade = (13.0f - o->AnimationFrame) / (13.0f - 9.0f);
						b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOOD_SANTA);
						b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOOD_SANTA_BAGGAGE);
						b->RenderMesh(2, RENDER_TEXTURE,1.0f-fFade,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

						b->RenderMesh(0, RENDER_TEXTURE,fFade,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
						b->RenderMesh(1, RENDER_TEXTURE,fFade,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

						CreateSprite(BITMAP_LIGHT,vPosition,5.5f,vLight,o);

						// ����
						if (o->WeaponLevel == 0)
						{
							o->WeaponLevel = 1;
							o->Position[0] = o->StartPosition[0] + (rand()%20+20)*0.1f;
							o->Position[1] = o->StartPosition[1] + (rand()%20+20)*0.1f;
						}
						else
						{
							o->WeaponLevel = 0;
							o->Position[0] = o->StartPosition[0] - (rand()%20+20)*0.1f;
							o->Position[1] = o->StartPosition[1] - (rand()%20+20)*0.1f;
						}
					}
					else
					{
						if (o->AI == 4 && o->AnimationFrame >= 3)
						{
							vec3_t Angle = { 0.0f, 0.0f, 0.0f};
							vec3_t Position;
							for (int i = 0; i < 36; ++i)
							{
								Vector(0.f,0.f,(float)(rand()%360),Angle);
								Position[0] = o->Position[0] + rand()%200-100;
								Position[1] = o->Position[1] + rand()%200-100;
								Position[2] = o->Position[2];
								
								CreateJoint(BITMAP_FLARE,Position,Position,Angle,2,NULL,40);
							}
							o->AI = 3;
						}
						b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
						b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
						// �� ����� ����

						// ����
						if (o->WeaponLevel == 0)
						{
							o->WeaponLevel = 1;
							o->Position[0] = o->StartPosition[0] + (rand()%40+40)*0.1f;
							o->Position[1] = o->StartPosition[1] + (rand()%40+40)*0.1f;
						}
						else
						{
							o->WeaponLevel = 0;
							o->Position[0] = o->StartPosition[0] - (rand()%40+40)*0.1f;
							o->Position[1] = o->StartPosition[1] - (rand()%40+40)*0.1f;
						}
					}
				}
				else
				{
					VectorCopy(o->Position, o->StartPosition);
					o->WeaponLevel = 0;
					o->AI = 4;
					b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
#endif	// YDG_ADD_SANTA_MONSTER
#ifdef PBG_ADD_LITTLESANTA_NPC
			else if(o->Type >= MODEL_LITTLESANTA && o->Type <= MODEL_LITTLESANTA_END)
			{
				//npc�ֺ������� ����Ʈ ȸ���� �δ� ����
 				float fLumi = (sinf(WorldTime*0.004f) + 1.2f) * 0.5f + 0.1f;
				float Rotation = (float)((int)(WorldTime*0.1f)%360);
				// ȿ�� ������
				vec3_t vWorldPos, vLight;

				switch(o->Type)
				{
				case MODEL_LITTLESANTA:		//��
					Vector(0.5f, 0.5f, 0.0f, vLight);
					break;
				case MODEL_LITTLESANTA+1:	//��
					Vector(0.3f, 0.8f, 0.4f, vLight);
					break;
				case MODEL_LITTLESANTA+2:	//��
					Vector(0.8f, 0.1f, 0.1f, vLight);
					break;
				case MODEL_LITTLESANTA+3:	//��
					Vector(0.3f, 0.3f, 0.8f, vLight);
					break;
				case MODEL_LITTLESANTA+4:	//��
					Vector(0.9f, 0.9f, 0.9f, vLight);
					break;
				case MODEL_LITTLESANTA+5:	//��
					Vector(0.9f, 0.9f, 0.9f, vLight);
					break;
				case MODEL_LITTLESANTA+6:	//��
					Vector(0.8f, 0.4f, 0.0f, vLight);
					break;
				case MODEL_LITTLESANTA+7:	//��
					Vector(0.9f, 0.5f, 0.7f, vLight);
					break;
				default:
					break;
				}
				//�� 17 20�� �ٿ� �ݴϴ�.
				b->TransformByObjectBone(vWorldPos, o, 17);	// Bip01 spine�� �ٿ��ش�.
				CreateSprite(BITMAP_LIGHTMARKS, vWorldPos, 0.7f, vLight, o, Rotation);	//scale 0.7
				CreateSprite(BITMAP_LIGHTMARKS, vWorldPos, 1.3f, vLight, o, Rotation);	//scale 1.3
				
				b->TransformByObjectBone(vWorldPos, o, 20);	// Bip01 head�� �ٿ��ش�.
				CreateSprite(BITMAP_LIGHTMARKS, vWorldPos, 0.7f, vLight, o, Rotation);	//scale 0.7
				CreateSprite(BITMAP_LIGHTMARKS, vWorldPos, 1.3f, vLight, o, Rotation);	//scale 1.3
	
				// �ٴ�ȿ��
				//2.0ū�� ����
				RenderAurora(BITMAP_LIGHTMARKS, RENDER_BRIGHT, o->Position[0], o->Position[1], 2.0f+fLumi, 2.0f+fLumi, vLight);
				//0.5������ ����
				RenderAurora(BITMAP_LIGHTMARKS, RENDER_BRIGHT, o->Position[0], o->Position[1], 0.5f+fLumi, 0.5+fLumi, vLight);

				//�ϴ÷� �ö󰡴� ��ƼŬ
				// impack01.jpg ȿ��
				if(rand()%50 <= 5)
				{
					CreateParticle(BITMAP_LIGHT+3, o->Position, o->Angle, vLight, 0, 1.0f);
				}

				// �� ������
				b->RenderBody(RENDER_TEXTURE,0.9f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				//�ٵ��� ��⸦ 50%�� ����
				Vector(b->BodyLight[0]*0.5f, b->BodyLight[0]*0.5f, b->BodyLight[0]*0.5f, b->BodyLight);
				b->RenderBody(RENDER_BRIGHT|RENDER_TEXTURE,0.9f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
#endif // PBG_ADD_LITTLESANTA_NPC
#ifdef YDG_ADD_NEW_DUEL_NPC
			else if (o->Type == MODEL_DUEL_NPC_TITUS)	// ������ ������ NPC Ÿ������
			{
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(4,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0001f);

				int iBones[] = { 9, 45, 23, 11 };
				vec3_t vLight, vPos, vRelative;
				Vector(1.0f, 1.0f, 1.0f, vLight);
				vec3_t vLightFire;
				Vector(1.0f, 0.2f, 0.0f, vLightFire);
				for (int i = 0; i < 4; ++i)
				{
					float fScale = 1.0f;
					if (i == 0)
					{
						b->TransformByObjectBone(vPos, o, iBones[i]);
						CreateSprite(BITMAP_LIGHT, vPos, 3.0f, vLightFire, o);

						fScale = 0.8f;
						Vector((rand()%10-5)*1.0f, (rand()%10-5)*1.0f, (rand()%10-5)*1.0f, vRelative);
						b->TransformByObjectBone(vPos, o, iBones[i], vRelative);

					}
					else
					{
						b->TransformByObjectBone(vPos, o, iBones[i]);
						CreateSprite(BITMAP_LIGHT, vPos, 2.0f, vLightFire, o);

						fScale = 0.6f;
						Vector((rand()%10-5)*1.0f, (rand()%10-5)*1.0f, (rand()%10-5)*1.0f, vRelative);
						b->TransformByObjectBone(vPos, o, iBones[i], vRelative);
					}
// 					if (rand()%10==0)	// ����
// 					{
// 						Vector(1.0f, 1.0f, 1.0f, vLight);
// 						CreateParticle(BITMAP_SMOKE,vPos,o->Angle,vLight,5,fScale*0.5f, o );
// 					}
					// ������ �� �����!!
 					switch(rand()%3)
					{
					case 0:
						CreateParticle(BITMAP_FIRE_HIK1,vPos,o->Angle,vLight,3,fScale);	// ��
						break;
					case 1:
						CreateParticle(BITMAP_FIRE_CURSEDLICH,vPos,o->Angle,vLight,7,fScale);	// ��
						break;
					case 2:
						CreateParticle(BITMAP_FIRE_HIK3,vPos,o->Angle,vLight,3,fScale);	// ��
						break;
					}
				}
			}
#endif	// YDG_ADD_NEW_DUEL_NPC
#ifdef LDK_ADD_GAMBLE_NPC_MOSS
#ifdef ASG_ADD_TIME_LIMIT_QUEST_NPC
			else if(o->Type == MODEL_GAMBLE_NPC_MOSS || o->Type == MODEL_TIME_LIMIT_QUEST_NPC_ZAIRO) // �׺� ���� ��, �����̻��� ���̷�
#else	// ASG_ADD_TIME_LIMIT_QUEST_NPC
			else if(o->Type == MODEL_GAMBLE_NPC_MOSS) //�׺� ���� ��
#endif	// ASG_ADD_TIME_LIMIT_QUEST_NPC
			{
				vec3_t vRelativePos, vWorldPos, Light;
				Vector(0.f, 0.f, 0.f, vRelativePos);

				//������ ����
				Vector(0.8f, 0.8f, 0.8f, Light);
				b->TransformPosition(o->BoneTransform[41], vRelativePos, vWorldPos, true);
				CreateParticle(BITMAP_SMOKELINE1+rand()%3,vWorldPos,o->Angle,Light,1,0.6f,o);
				CreateParticle(BITMAP_CLUD64,vWorldPos,o->Angle,Light,6,0.6f,o);
 
				//�Ӹ� ����
				Vector(0.5f, 0.5f, 0.5f, Light);
				b->TransformPosition(o->BoneTransform[55], vRelativePos, vWorldPos, true);
				CreateSprite(BITMAP_LIGHT, vWorldPos, 2.0f, Light, o);

 				b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
			}
#endif //LDK_ADD_GAMBLE_NPC_MOSS
#ifdef YDG_ADD_DOPPELGANGER_NPC
			else if(o->Type == MODEL_DOPPELGANGER_NPC_LUGARD)	// ���ð��� NPC �簡��
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(4,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				// ����
				Vector(1.0f, 1.0f, 1.0f, b->BodyLight);
				b->RenderMesh(5,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(5,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,5,0.1f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
			else if(o->Type == MODEL_DOPPELGANGER_NPC_BOX || o->Type == MODEL_DOPPELGANGER_NPC_GOLDENBOX)	// ���ð��� �������, �����������
			{
				if (o->CurrentAction == MONSTER01_DIE)
				{
					o->Alpha = (10 - o->AnimationFrame) * 0.1f;

					if (o->AnimationFrame > 9)
						o->AnimationFrame = 9;
				}

				if(o->Type == MODEL_DOPPELGANGER_NPC_BOX)
				{
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
				else if(o->Type == MODEL_DOPPELGANGER_NPC_GOLDENBOX)	// ���ð��� �����������
				{
					b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DOPPELGANGER_GOLDENBOX2);
					b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DOPPELGANGER_GOLDENBOX1);
					b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME7,0.5f,1,0.3f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}

				if (o->CurrentAction == MONSTER01_DIE && o->AnimationFrame > 1 && o->AnimationFrame < 9)
				{
					vec3_t vPos, vLight;
					// ����
					for (int i = 0; i < 1; ++i)
					{
						// ����
						vPos[0] = o->Position[0] + rand()%120-60;
						vPos[1] = o->Position[1] + rand()%120-60;
						vPos[2] = o->Position[2];
						Vector(0.3f, 0.3f, 0.3f, vLight);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 54, 2.0f);
						Vector(0.3f, 0.3f, 0.3f, vLight);
						CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 66, 2.0f, o);
					}

					// ���ٱ�
					if (rand()%2 == 0)
					{
						vPos[0] = o->Position[0] + rand()%80-40;
						vPos[1] = o->Position[1] + rand()%80-40;
						vPos[2] = o->Position[2] + rand()%50+10;
						Vector(0.2f, 0.5f, 1.0f, vLight);
						CreateParticle(BITMAP_PIN_LIGHT, vPos, o->Angle, vLight, 2, 1.0f, o);
						vPos[2] = o->Position[2] + rand()%50+10;
						Vector(1.0f, 0.8f, 0.5f, vLight);
						CreateParticle(BITMAP_PIN_LIGHT, vPos, o->Angle, vLight, 3, 0.2f, o);
					}

					// �� ��ƼŬ
					Vector(0.9f, 0.7f, 0.0f, vLight);
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 3, 0.5f, o);
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 3, 0.5f, o);

					// �� ����Ʈ
					vPos[0] = o->Position[0];
					vPos[1] = o->Position[1];
					if (o->Type == MODEL_DOPPELGANGER_NPC_GOLDENBOX)
						vPos[2] = o->Position[2] + 80;
					else
						vPos[2] = o->Position[2] + 50;
					Vector(1.0f, 1.0f, 1.0f, vLight);
					float fRot = (WorldTime*0.0006f) * 360.0f;
					CreateSprite(BITMAP_DS_EFFECT, vPos, 2.5f, vLight, o, fRot);
					Vector(0.9f, 0.7f, 0.0f, vLight);
#ifdef LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
					CreateSprite(BITMAP_SHINY+6, vPos, 0.8f, vLight, o, -fRot);
#else // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
					CreateSprite(BITMAP_SHINY+5, vPos, 0.8f, vLight, o, -fRot);
#endif // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
		           	float fLight = (sinf(WorldTime*0.01f)+1.0f)*0.5f*0.9f+0.1f;
					Vector(1.0f*fLight, 1.0f*fLight, 1.0f*fLight, vLight);
					CreateSprite(BITMAP_FLARE, vPos, 1.5f, vLight, o);
				}
			}
#endif	// YDG_ADD_DOPPELGANGER_NPC
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
			else if(o->Type == MODEL_DOPPELGANGER_SLIME_CHIP)
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef PBG_ADD_CHARACTERSLOT
			else if(o->Type == MODEL_SLOT_LOCK)					// �ڹ���
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(0,RENDER_CHROME6|RENDER_BRIGHT,o->Alpha*0.4f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef KJH_ADD_09SUMMER_EVENT
			else if( o->Type == MODEL_MONSTER01+154 )
			{
				if( o->CurrentAction == MONSTER01_DIE )		// ��� ����
				{ 
					Vector(1.0f,0.6f,0.9f,b->BodyLight);
					o->m_bRenderShadow = false;
					b->RenderBody(RENDER_TEXTURE,o->Alpha,-2,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
					vec3_t vOriBodyLight;
					VectorCopy(b->BodyLight, vOriBodyLight);
					Vector(1.0f,0.6f,0.5f,b->BodyLight);
					b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					VectorCopy(vOriBodyLight, b->BodyLight);
				}
			}
			else if(o->Type == MODEL_EFFECT_UMBRELLA_GOLD)
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
#endif // KJH_ADD_09SUMMER_EVENT
#ifdef PBG_ADD_AURA_EFFECT
			else if(o->Type == MODEL_EFFECT_SD_AURA)
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU, WorldTime*0.0006f);
			}
#endif //PBG_ADD_AURA_EFFECT
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
			else if(o->Type == MODEL_UNITEDMARKETPLACE_CHRISTIN)	// ���ս��� ũ����ƾ
			{				
				// ���� �Ѹ���
      			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_UNITEDMARKETPLACE_RAUL)	// ���ս��� ���
			{
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(4,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(5,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(6,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(7,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(8,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(9,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(10,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(11,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(12,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(13,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				b->RenderMesh(14,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				
				// ���� �Ѹ���
//				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_UNITEDMARKETPLACE_JULIA)	// ���ս��� �ٸ���
			{	
				vec3_t vRelativePos, vWorldPos, Light;
				Vector(0.f, 0.f, 0.f, vRelativePos);
				float fScale = 0.0f;
				
				// �Ǹ��δ� ȿ��
				if (o->CurrentAction == 0 && rand()%5==0)
				{
					Vector(0.f, 0.f, 0.f, vWorldPos);
					Vector((rand()%90+10)*0.01f, (rand()%90+10)*0.01f, (rand()%90+10)*0.01f, Light);
					fScale = (rand()%5+5)*0.1f;
					Vector(0.f, 0.f, 0.f, vRelativePos);
					vRelativePos[0] = -5+(rand()%1000-500)*0.01f;
					vRelativePos[1] = (rand()%300-150)*0.01f;
					b->TransformPosition(o->BoneTransform[127],vRelativePos,vWorldPos,true);
					CreateParticle(BITMAP_LIGHT, vWorldPos, o->Angle, Light, 13, fScale, o);
					CreateParticle(BITMAP_LIGHT, vWorldPos, o->Angle, Light, 12, fScale*0.1f, o);
				}
				
 				// �η°� �� ����
 				Vector(0.f, 0.f, 0.f, vRelativePos);
 				Vector(0.f, 0.f, 0.f, vWorldPos);
 				Vector(1.0f, 1.0f, 1.0f, Light);
				b->TransformPosition(o->BoneTransform[71], vRelativePos, vWorldPos, true);
 				CreateSprite(BITMAP_LIGHT, vWorldPos, 3.0f, Light, o);

 				vec3_t	vLight;
 				float fLight = (sinf(WorldTime*0.001f)+1.0f)*0.5f*0.9f+0.4f;
 				Vector(1.0f*fLight, 1.0f*fLight, 1.0f*fLight, vLight);
 				CreateSprite(BITMAP_FLARE, vWorldPos, 1.5f, vLight, o);

				// ���� �Ѹ���
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
#ifdef ASG_ADD_TIME_LIMIT_QUEST_NPC
			else if(o->Type == MODEL_TIME_LIMIT_QUEST_NPC_TERSIA)	// �������� �׸��þ�
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha*0.4f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_NPC
			
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ NPC
			else if (o->Type == MODEL_LUCKYITEM_NPC)	
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha*0.4f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			}
#endif // LEM_ADD_LUCKYITEM
#ifdef ASG_ADD_KARUTAN_NPC
			else if(o->Type == MODEL_KARUTAN_NPC_VOLVO)	// ������� ����
			{
				b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight,
					o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
				float fLumi = (sinf(WorldTime*0.001f)+1.0f)*0.45f+0.1f;
				b->RenderMesh(0, RENDER_TEXTURE | RENDER_BRIGHT, o->Alpha, 0, fLumi,
					o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_VOLO_SKIN_EFFECT);
			}
#endif	// ASG_ADD_KARUTAN_NPC
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			else if(o->Type == MODEL_WOLF_HEAD_EFFECT2)
			{
				float _BlendLight = o->BlendMeshLight;
				Vector(0.4f, 0.4f, 0.6f, o->Light);
				VectorCopy(o->Light, b->BodyLight);
				VectorScale(b->BodyLight, 0.3f, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,_BlendLight*0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type==MODEL_SHOCKWAVE01)
			{
				if(o->SubType==1)
				{
					VectorCopy(o->Light, b->BodyLight);
					VectorScale(b->BodyLight, 5.0f, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DAMAGE2);
				}
				else if(o->SubType==2)
				{
					VectorCopy(o->Light, b->BodyLight);
					VectorScale(b->BodyLight, 15.0f, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
				else if(o->SubType==3)
				{
					VectorCopy(o->Light, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DAMAGE2);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DAMAGE2);
				}
				else if(o->SubType==4 || o->SubType==5)
				{
					VectorCopy(o->Light, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_DAMAGE2);
				}
				else
				{
					VectorCopy(o->Light, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
			}
			else if(o->Type==MODEL_SHOCKWAVE02)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type==MODEL_SHOCKWAVE_SPIN01)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh, BITMAP_DAMAGE1);
			}
			else if(o->Type == MODEL_DRAGON_KICK_DUMMY || o->Type==MODEL_DOWN_ATTACK_DUMMY_L 
				|| o->Type==MODEL_DOWN_ATTACK_DUMMY_R || o->Type==MODEL_WOLF_HEAD_EFFECT)
			{
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_WINDFOCE)
			{
				VectorCopy(o->Light, b->BodyLight);
				VectorScale(b->BodyLight, 6.0f, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_WINDFOCE_MIRROR)
			{
				VectorCopy(o->Light, b->BodyLight);
				VectorScale(b->BodyLight, 6.0f, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_SHOCKWAVE_GROUND01)
			{
				if(o->SubType==1)
				{
					VectorCopy(o->Light, b->BodyLight);
					VectorScale(b->BodyLight, 6.0f, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_KWAVE2);
				}
				else
				{
					VectorCopy(o->Light, b->BodyLight);
					VectorScale(b->BodyLight, 6.0f, b->BodyLight);
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
			}
			else if(o->Type == MODEL_DRAGON_LOWER_DUMMY)
			{
				Vector(1.0f, 0.8f, 0.2f, o->Light);
				VectorCopy(o->Light, b->BodyLight);
				VectorScale(b->BodyLight, o->Alpha, b->BodyLight);
				// grandmark2.jpg
				b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,-(int)WorldTime%2000*0.0001f);
				b->RenderMesh(2, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,2,o->BlendMeshLight,o->BlendMeshTexCoordU,-(int)WorldTime%2000*0.0001f);
				
				Vector(1.0f, 0.2f, 0.1f, o->Light);
				VectorCopy(o->Light, b->BodyLight);
				VectorScale(b->BodyLight, o->Alpha, b->BodyLight);
				// lines2.jpg
				b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,-(int)WorldTime%2000*0.0001f);
			}
			else if(o->Type == MODEL_VOLCANO_OF_MONK)
			{
				if(o->SubType == 1)
				{
					VectorCopy(o->Light, b->BodyLight);
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_VOLCANO_CORE);
				}
			}
			else if(o->Type == MODEL_VOLCANO_STONE)
			{
				VectorCopy(o->Light, b->BodyLight);
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
			else if(o->Type == MODEL_SWORD_FORCE)
			{
				if(o->SubType==2 || o->SubType==3)
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh, BITMAP_KNIGHTST_BLUE);
				}
				else
				{
					b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				}
			}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
//---------------------------------------------------------------------------------------
// �⺻ Render
			else
			{	// ���� �Ѹ���
      			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
//---------------------------------------------------------------------------------------
			if( g_isCharacterBuff(o, eDeBuff_Freeze) )
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,-2,1.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
			else if(g_isCharacterBuff(o, eDeBuff_BlowOfDestruction))
			{
#ifdef YDG_FIX_BLOWOFDESTRUCTION_EFFECT_BUG
				Vector(0.3f,0.5f,1.f,b->BodyLight);
#endif	// YDG_FIX_BLOWOFDESTRUCTION_EFFECT_BUG
				b->RenderBody(RENDER_TEXTURE,o->Alpha,-2,1.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
			}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION


			if(o->Type==MODEL_MONSTER01+37)//�����
			{
				b->BeginRender(o->Alpha);
           		float Light = sinf(WorldTime*0.002f)*0.3f+0.5f;
				b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,0,Light,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,b->IndexTexture[6]);
           		float TexCoord = (float)((int)WorldTime%100)*0.01f;
				b->RenderMesh(3,RENDER_CHROME|RENDER_BRIGHT,o->Alpha,3,Light,o->BlendMeshTexCoordU,-TexCoord);
				b->EndRender();
			}
			if (o->Type == MODEL_NPC_ARCHANGEL_MESSENGER || o->Type == MODEL_NPC_ARCHANGEL)	// ��õ���� ����
			{
				b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight);
			}
			if ( o->Type==MODEL_ARROW_DRILL )
			{
				vec3_t Position, p, Light;

				Vector(1.f,0.6f,0.4f,Light);
				Vector(0.f,0.f,0.f,p);
				b->TransformPosition(BoneTransform[1],p,Position);
				CreateSprite ( BITMAP_SHINY+1, Position, (float)(sinf(WorldTime*0.002f)*0.3f+1.3f), Light, o, (float)(rand()%360) );
				CreateSprite ( BITMAP_LIGHT, Position, 1.5f, Light, o, 90.f );
				CreateSprite ( BITMAP_SHINY+1, Position, (float)(sinf(WorldTime*0.002f)*0.3f+1.3f), Light, o, (float)(rand()%360) );
				CreateParticle ( BITMAP_SPARK, Position, o->Angle, Light );
			}
			if(o->Type == MODEL_ARROW_TANKER_HIT || o->Type ==MODEL_ARROW_TANKER)
			{
				b->BodyLight[0] = 1.0f;
				b->BodyLight[1] = 1.0f;
				b->BodyLight[2] = 1.0f;

				b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,-2,1.f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

				vec3_t p1, p2;
				BMD* b = &Models[o->Type];
				
				Vector(1.0f, 1.0f, 1.0f, o->Light);
				Vector(0.0f, 1.5f, 0.0f, p1);
				b->TransformPosition(BoneTransform[2], p1, p2);
				CreateParticle(BITMAP_FIRE+1,o->Position,o->Angle,o->Light, 8, o->Scale-0.4f, o );
				CreateParticle(BITMAP_FIRE+1,o->Position,o->Angle,o->Light, 8, o->Scale-0.4f, o );
				CreateParticle(BITMAP_SMOKE,o->Position,o->Angle,o->Light, 38, o->Scale, o );
				Vector(1.0f, 0.4f, 0.0f, o->Light);
      			CreateParticle(BITMAP_FIRE+1,o->Position,o->Angle,o->Light, 9, o->Scale-0.4f, o );

				for(int i = 0; i < 10; i++)
				{
					Vector(1.0f-(i*0.1f), 0.4f-(i*0.04f), 0.0f, o->Light);
					Vector(15.0f*i, 1.5f, 0.0f, p1);
					b->TransformPosition(BoneTransform[1], p1, p2);
					CreateSprite(BITMAP_SPARK+1, p2, 3.0f+(i*0.9f), o->Light, o);
				}
			}
		}
	}

#ifdef USE_SHADOWVOLUME
	if ( World != WD_10HEAVEN)
	{
		//�ɸ���
		CShadowVolume *pShadowVolume = new CShadowVolume;
		pShadowVolume->Create( VertexTransform, b, o);
		InsertShadowVolume( pShadowVolume);
	}
#endif

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
}

#ifdef MR0
void RenderObject(OBJECT *o,bool Translate,int Select, int ExtraMon)
{	
	if(Calc_RenderObject( o, Translate,Select, ExtraMon))
	{
		Draw_RenderObject( o, Translate,Select, ExtraMon);
	}
}

#else

void RenderObject(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
 	if(Calc_RenderObject( o, Translate,Select, ExtraMon) == false)
 	{
 		return;
 	}
	Draw_RenderObject( o, Translate,Select, ExtraMon);
}

#endif //MR0

void RenderObject_AfterImage(OBJECT* o, bool Translate, int Select, int ExtraMon)
{
	float fAnimationFrame = o->AnimationFrame;
	float fAni1, fAni2;

	fAni1 = fAnimationFrame - 1.4f;
	fAni2 = fAnimationFrame - 0.7f;
	if(fAni1 > 0.0f)
	{
		o->Alpha = 0.2f;
		o->AnimationFrame = fAni1;
		RenderObject(o, Translate, Select, 0);
	}
	if(fAni2 > 0.0f)
	{
		o->Alpha = 0.6f;
		o->AnimationFrame = fAni2;
		RenderObject(o, Translate, Select, 0);
	}

	o->Alpha = 1.0f;
	o->AnimationFrame = fAnimationFrame;
	RenderObject(o, Translate, Select, 0);
}

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
void RenderCharacter_AfterImage(CHARACTER* pCha, PART_t *pPart, bool Translate, int Select, float AniInterval1, float AniInterval2)
{
	OBJECT* pObj = &pCha->Object;
	float fAnimationFrame = pObj->AnimationFrame;
	float fAni1, fAni2;
	int Type = pPart->Type;

	fAni1 = (float)(fAnimationFrame - AniInterval1);
  	fAni2 = (float)(fAnimationFrame - AniInterval2);

	vec3_t vPos, vStartPos, vOrgPos;
	VectorCopy(pObj->Position, vOrgPos);
	VectorCopy(pObj->Position, vPos);
	VectorCopy(pObj->StartPosition, vStartPos);
	VectorSubtract(vPos, vStartPos, vPos);
	float fDis = fAni1/Models[pObj->Type].Actions[pObj->CurrentAction].NumAnimationKeys;

	if(fAni1 > 0.0f)
	{
		pObj->Alpha = 0.3f;
		pObj->AnimationFrame = fAni1;
		VectorScale(vPos, fDis, vPos);
		VectorAdd(vStartPos, vPos, vPos);
		VectorCopy(vPos, pObj->Position);
		Calc_ObjectAnimation(pObj, Translate, Select);
		RenderPartObject(pObj,Type,pPart,pCha->Light,pObj->Alpha,pPart->Level<<3,pPart->Option1,pPart->ExtOption,false,false,Translate,Select);
	}

	VectorCopy(vOrgPos, vPos);
	VectorCopy(pObj->StartPosition, vStartPos);
	VectorSubtract(vPos, vStartPos, vPos);
	if(fAni2 > 0.0f)
	{
		fDis = fAni2/Models[pObj->Type].Actions[pObj->CurrentAction].NumAnimationKeys;
		pObj->Alpha = 0.5f;
		pObj->AnimationFrame = fAni2;
		VectorScale(vPos, fDis, vPos);
		VectorAdd(vStartPos, vPos, vPos);
		VectorCopy(vPos, pObj->Position);
		Calc_ObjectAnimation(pObj, Translate, Select);
		RenderPartObject(pObj,Type,pPart,pCha->Light,pObj->Alpha,pPart->Level<<3,pPart->Option1,pPart->ExtOption,false,false,Translate,Select);
	}

	VectorCopy(vOrgPos, pObj->Position);
	pObj->Alpha = 1.0f;
	pObj->AnimationFrame = fAnimationFrame;
	Calc_ObjectAnimation(pObj, Translate, Select);
	RenderPartObject(pObj,Type,pPart,pCha->Light,pObj->Alpha,pPart->Level<<3,pPart->Option1,pPart->ExtOption,false,false,Translate,Select);
}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

///////////////////////////////////////////////////////////////////////////////
// Ȯ��/���.
///////////////////////////////////////////////////////////////////////////////
/*
void RenderTransformObject(OBJECT *o,bool Translate)
{
	if(o->Alpha < 0.01f) return;
	
	BMD *b = &Models[o->Type];
	b->BodyHeight     = 0.f;
	b->ContrastEnable = o->ContrastEnable;
	BodyLight(o,b);
	b->BodyScale     = o->Scale;
	b->CurrentAction = o->CurrentAction;
	VectorCopy(o->Position,b->BodyOrigin);

	b->BodyScale     = 1.f;
	b->Animation(BoneTransform,o->AnimationFrame,o->PriorAnimationFrame,o->PriorAction,o->Angle,o->HeadAngle);
	b->Transform(BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB);

    b->BodyScale     = o->Scale;
    b->RenderTransformBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
}
*/

///////////////////////////////////////////////////////////////////////////////
// ���忡 �ִ� ��� ������Ʈ���� �ð����� ȿ�� ������
///////////////////////////////////////////////////////////////////////////////

void RenderObjectVisual(OBJECT *o)
{
	BMD *b = &Models[o->Type];
	vec3_t p,Position;
	vec3_t Light;
  	float Luminosity = (float)(rand()%30+70)*0.01f;
#ifdef _VS2008PORTING
	int Bitmap;
#else // _VS2008PORTING
	int i,Bitmap;
#endif // _VS2008PORTING
	float Scale;
	float Rotation;
	Vector ( 0.f, 0.f, 0.f, p );
	switch ( World )
	{
	case WD_0LORENCIA:
		switch(o->Type)
		{
		case MODEL_WATERSPOUT:
			o->BlendMeshLight = 1.f;
			o->BlendMeshTexCoordV = -(int)WorldTime%1000 * 0.001f;
			if(rand()%2==0)
			{
				Vector((float)(rand()%32-16),-20.f,(float)(rand()%32-16),p);
				b->TransformPosition(BoneTransform[1],p,Position);
				CreateParticle(BITMAP_SMOKE,Position,o->Angle,o->Light);
				Vector((float)(rand()%32-16),-80.f,(float)(rand()%32-16),p);
				b->TransformPosition(BoneTransform[4],p,Position);
				CreateParticle(BITMAP_SMOKE,Position,o->Angle,o->Light);
			}
			break;
		case MODEL_MERCHANT_ANIMAL01:
			Scale = Luminosity*5.f;
			Vector(Luminosity*0.6f,Luminosity*0.3f,Luminosity*0.1f,Light);
			b->TransformPosition(BoneTransform[48],Position,p);
			CreateSprite(BITMAP_LIGHT,p,Scale,Light,o);
			b->TransformPosition(BoneTransform[57],Position,p);
			CreateSprite(BITMAP_LIGHT,p,Scale,Light,o);
			/*b->TransformPosition(BoneTransform[51],Position,p);
			CreateSprite(BITMAP_LIGHT,p,Scale,Light,o);
			b->TransformPosition(BoneTransform[54],Position,p);
			CreateSprite(BITMAP_LIGHT,p,Scale,Light,o);*/
			break;
		}
    	break;
	case WD_2DEVIAS:
		switch(o->Type)
		{
		case 100:
			Vector(Luminosity*1.f,Luminosity*1.f,Luminosity*1.f,Light);
			Rotation = (float)((int)(WorldTime*0.1f)%360);
         	Vector(0.f,0.f,150.f,p);
			b->TransformPosition(BoneTransform[0],p,Position);
			CreateSprite(BITMAP_LIGHTNING+1,Position,2.5f,Light,o,Rotation);
			CreateSprite(BITMAP_LIGHTNING+1,Position,2.5f,Light,o,-Rotation);
			break;
		case 103:		//. Sleddog
			if(b->CurrentAnimationFrame == b->Actions[o->CurrentAction].NumAnimationKeys-1){
				if(rand()%32==0)
					SetAction(o, 1);
				else
					SetAction(o, 0);
			}
			break;
#ifdef DEVIAS_XMAS_EVENT2007
		case 110:
			{
				b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
				Vector ( 1.f, 1.0f, 1.f, b->BodyLight );
				b->RenderMesh ( 0, RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			}
			break;
#endif	// DEVIAS_XMAS_EVENT2007
#ifdef DEVIAS_XMAS_EVENT
		case 105:
			{
				Vector ( 1.f, 1.0f, 1.f, b->BodyLight );
				b->RenderMesh ( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
				b->RenderMesh ( 0, RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			}
			break;
		case 106:
			{
				Vector ( 1.0f, 1.0f, 1.0f, b->BodyLight );
				b->RenderMesh ( 3, RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHROME8);
			}
			break;
#endif //DEVIAS_XMAS_EVENT			
		}
    	break;
	case WD_3NORIA:
		switch(o->Type)
		{
		case 9:
			Vector(Luminosity*0.4f,Luminosity*0.7f,Luminosity*1.f,Light);
			b->TransformPosition(BoneTransform[1],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.5f,Light,o);
			break;
		case 35:
			Vector(Luminosity*0.4f,Luminosity*0.7f,Luminosity*1.f,Light);
			b->TransformPosition(BoneTransform[3],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.5f,Light,o);
			break;
		case 1:
			Vector(Luminosity*0.4f,Luminosity*0.7f,Luminosity*1.f,Light);
			b->TransformPosition(BoneTransform[2],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,0.5f,Light,o);
			b->TransformPosition(BoneTransform[4],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,0.5f,Light,o);
			b->TransformPosition(BoneTransform[6],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,0.5f,Light,o);
			break;
		case 17:
			Vector(Luminosity*0.4f,Luminosity*0.7f,Luminosity*1.f,Light);
			b->TransformPosition(BoneTransform[4],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.f,Light,o);
			b->TransformPosition(BoneTransform[7],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.f,Light,o);
			b->TransformPosition(BoneTransform[10],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.f,Light,o);
			b->TransformPosition(BoneTransform[13],p,Position);
			CreateSprite(BITMAP_LIGHT,Position,1.f,Light,o);
			break;
		case 39:
			Vector(Luminosity*0.4f,Luminosity*0.8f,Luminosity*1.f,Light);
			Rotation = (float)((int)(WorldTime*0.1f)%360);
			b->TransformPosition(BoneTransform[57],p,Position);
			CreateSprite(BITMAP_LIGHTNING+1,Position,1.f,Light,o,Rotation);
			CreateSprite(BITMAP_LIGHTNING+1,Position,1.f,Light,o,-Rotation);

			Vector(1.f,1.f,1.f,Light);
#ifdef _VS2008PORTING
			for(int i=61;i<=65;i++)
#else // _VS2008PORTING
			for(i=61;i<=65;i++)
#endif // _VS2008PORTING
			{
        		b->TransformPosition(BoneTransform[i],p,Position);
       			CreateSprite(BITMAP_LIGHT,Position,1.f,Light,o);
				if(rand()%32==0)
				{
					CreateParticle(BITMAP_SHINY,Position,o->Angle,Light);
					CreateParticle(BITMAP_SHINY,Position,o->Angle,Light,1);
				}
			}
       		b->TransformPosition(BoneTransform[58],p,Position);
			if(rand()%8==0)
			{
				vec3_t Angle;
#ifdef _VS2008PORTING
				for(int i=0;i<8;i++)
#else // _VS2008PORTING
				for(i=0;i<8;i++)
#endif // _VS2008PORTING
				{
					Vector((float)(rand()%60+60),90.f+50.f,(float)(rand()%30),Angle);
					CreateJoint(BITMAP_JOINT_SPARK,Position,Position,Angle);
					CreateParticle(BITMAP_SPARK,Position,Angle,Light);
				}
			}
			break;
		}
    	break;
	case WD_4LOSTTOWER:
		switch(o->Type)
		{
		case 19:
		case 20:
			if(o->Type==19)
			{
				Bitmap = BITMAP_MAGIC+1;
				Vector(Luminosity*1.f,Luminosity*0.2f,Luminosity*0.f,Light);
			}
			else
			{
				Bitmap = BITMAP_LIGHTNING+1;
				Vector(Luminosity*0.4f,Luminosity*0.8f,Luminosity*1.f,Light);
			}
			Rotation = (float)((int)(WorldTime*0.1f)%360);
			b->TransformPosition(BoneTransform[15],p,Position);
			CreateSprite(Bitmap,Position,0.3f,Light,o,Rotation);
			CreateSprite(Bitmap,Position,0.3f,Light,o,-Rotation);
			b->TransformPosition(BoneTransform[19],p,Position);
			CreateSprite(Bitmap,Position,0.3f,Light,o,Rotation);
			CreateSprite(Bitmap,Position,0.3f,Light,o,-Rotation);
			b->TransformPosition(BoneTransform[21],p,Position);
			CreateSprite(Bitmap,Position,1.5f,Light,o,Rotation);
			CreateSprite(Bitmap,Position,1.5f,Light,o,-Rotation);
			break;
		case 40:
			Vector(Luminosity*1.f,Luminosity*1.f,Luminosity*1.f,Light);
			Rotation = (float)((int)(WorldTime*0.1f)%360);
			VectorCopy( o->Position, Position);
         	Vector(0.f,0.f,260.f,p);
			VectorAdd( Position, p, Position);
			CreateSprite(BITMAP_LIGHTNING+1,Position,2.5f,Light,o,Rotation);
			CreateSprite(BITMAP_LIGHTNING+1,Position,2.5f,Light,o,-Rotation);
			/*{
				//Vector(1.f,1.f,1.f,Light);
				Vector(0.f,0.f,1.f,Light);
				for ( int j = 0; j < 2; ++j)
				{
					for ( int i = 0; i < 3; ++i)
					{
						VectorCopy( o->Position, Position);
						Position[0] += ( float)( 2 * i - 2) / 2.f * 100.f + ( float)( rand() % 31 - 15);
						Position[1] += ( float)( 2 * j - 1) / 1.f * 70.f-80.f + ( float)( rand() % 31 - 15);
						VectorCopy( Position, p);
						p[2] += 300.f;
						CreateJoint(BITMAP_JOINT_LASER+1,Position,p,o->Angle,0,o,50.f);
					}
				}
			}*/
			break;
		}
	case WD_6STADIUM:
		switch(o->Type)
		{
		case 9:
			Scale = Luminosity*5.f;
			Vector(Luminosity*0.6f,Luminosity*0.3f,Luminosity*0.1f,Light);
			b->TransformPosition(BoneTransform[1],Position,p);
			CreateSprite(BITMAP_LIGHT,p,Scale,Light,o);
			break;
		}
    	break;
	case WD_8TARKAN:
		switch(o->Type)
		{
// rozy ĸ�������̶�� ������Ʈ�� ����. ��ũȣ�� Ÿ�� BITMAP_SPARK+1 ��������Ʈ �߻� ����.
/*        case 0:    //  �ν� ����.
            Luminosity = (float)sinf(WorldTime*0.002f)*0.3f+0.7f;

			Scale = Luminosity*5.f;
			Vector(Luminosity/1.7f,Luminosity,Luminosity,Light);
			b->TransformPosition(BoneTransform[6],p,Position);
			CreateSprite(BITMAP_SPARK+1,Position,Scale,Light,o);
            break;
			*/
        case 60 :   //  ���� �ڽ�.
			if ( o->HiddenMesh!=-2 )
			{
				for ( int i=0; i<20; ++i )
				{
					CreateParticle ( BITMAP_SMOKE, o->Position, o->Angle, o->Light, 6, o->Scale );
				}
			}
            o->HiddenMesh = -2;
            break;

        case 63:    //  Ǫ����.
            Luminosity = (float)sinf((WorldTime+(o->Angle[2]*5))*0.002f)*0.3f+0.7f;

			Scale = Luminosity*1.5f;
			Vector(Luminosity/1.7f,Luminosity,Luminosity,Light);
			b->TransformPosition(BoneTransform[2],p,Position);
			CreateSprite(BITMAP_IMPACT,Position,Scale,Light,o);
            break;

        case 64:    //  ������.
            Luminosity = (float)sinf((WorldTime+(o->Angle[2]*5))*0.002f)*0.3f+0.7f;

			Scale = Luminosity*1.5f;
			Vector(Luminosity,Luminosity*0.32f,Luminosity*0.32f,Light);
			b->TransformPosition(BoneTransform[2],p,Position);
			CreateSprite(BITMAP_IMPACT,Position,Scale,Light,o);
            break;

        case 70 :   //  ����ڽ�2.
            o->HiddenMesh = -2;
            if ( rand()%5==0 )
                CreateParticle ( BITMAP_SMOKE, o->Position, o->Angle, o->Light, 7, o->Scale );
            break;

        case 76 :   //  ����ڽ�3.
            o->HiddenMesh = -2;
            {
                bool Smoke = false;

                if ( ((int)WorldTime%5000)>4500 ) Smoke = true;
                //  �Ա�.
			    if ( Smoke )
				    CreateParticle(BITMAP_SMOKE,o->Position,o->Angle,o->Light, 4, o->Scale);
            }
            break;
/*
		case 78:
			Vector(0.f,0.f,0.f,p);
          	Models[o->Type].TransformPosition(BoneTransform[7],p,o->EyeLeft);
          	Models[o->Type].TransformPosition(BoneTransform[8],p,o->EyeRight);
			for(int i=0;i<b->NumBones;i++)
			{
				b->TransformPosition(BoneTransform[i],p,Position);
				CreateParticle(BITMAP_SMOKE,Position,o->Angle,Light,4);
			}
			break;
*/
        case 83:    //  ����+������.
            o->HiddenMesh = -2;
            {
                bool Smoke = false;
                int  inter = (int)o->Angle[2]*10;
                int  timing = (int)WorldTime%10000;

                if ( timing>3500+inter && timing<4000+inter ) Smoke = true;
			    if ( Smoke )
                {
    			    Vector(1.f,1.f,1.f,Light);

                    //  ��.
    				CreateParticle(BITMAP_SMOKE,o->Position,o->Angle,o->Light, 8, o->Scale);
                    if ( rand()%3==0 )
                    {
                        Position[0] = o->Position[0]+(rand()%128-64);
                        Position[1] = o->Position[1]+(rand()%128-64);
                        Position[2] = o->Position[2];
                        //  �򿬱�.
    				    CreateParticle(BITMAP_SMOKE,Position,o->Angle,o->Light, 4, o->Scale*0.5f);

                        //  ������.
                        CreateEffect(MODEL_STONE1+rand()%2,o->Position,o->Angle,o->Light);
                    }
                }
            }
            break;
		}
		break;
	case WD_9DEVILSQUARE:
		switch(o->Type)
		{
		case 2:
			Vector(1.f,1.f,1.f,Light);
        	Vector(-15.f,0.f,0.f,p);
			if(rand()%4==0)
			{
				b->TransformPosition(BoneTransform[23],p,Position);
				CreateParticle(BITMAP_RAIN_CIRCLE+1,Position,o->Angle,Light);
			}
			if(rand()%4==0)
			{
				b->TransformPosition(BoneTransform[31],p,Position);
				CreateParticle(BITMAP_RAIN_CIRCLE+1,Position,o->Angle,Light);
			}
        	Vector(-15.f,0.f,0.f,p);
			b->TransformPosition(BoneTransform[23],p,Position);
			CreateParticle(BITMAP_RAIN_CIRCLE+1,Position,o->Angle,Light);
			break;
		}
		break;
    case WD_10HEAVEN:
        switch(o->Type)
        {
        case    0 : //  ���� 1.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<20; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 0, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    1 : //  ���� 2.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<20; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 1, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    2 : //  ���� 3.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<20; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 2, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    3 : //  ���� 4.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<10; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 3, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    4 : //  ���� 5.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<10; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 4, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    5 : //  ���� 6.
			if ( o->HiddenMesh!=-2 )
			{
                vec3_t  Light;
                Vector(0.1f,0.1f,0.1f,Light);
				for ( int i=0; i<10; ++i )
				{
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 5, o->Scale, o );
				}
			}
            o->HiddenMesh = -2;
            break;

        case    10:
            {
                Vector(0.f,0.f,0.f,p);
				b->TransformPosition(BoneTransform[3],p,Position);

                Vector(1.f,1.f,1.f,Light);
                CreateParticle( BITMAP_LIGHT, Position, o->Angle, Light, 0, 1.f);
            }
        case    6 :
        case    7 :
        case    8 :
        case    9 :
        case    11:
        case    12:
        case    13:
        case    14:
        case    15:
//            o->BlendMeshLight = sinf(WorldTime*0.002f)*1.f;
//            o->BlendMesh = -2;
//            o->HiddenMesh= -99;
            break;
        }
        break;

    case WD_11BLOODCASTLE1:
    case WD_11BLOODCASTLE1+1:
    case WD_11BLOODCASTLE1+2:
    case WD_11BLOODCASTLE1+3:
    case WD_11BLOODCASTLE1+4:
    case WD_11BLOODCASTLE1+5:
    case WD_11BLOODCASTLE1+6:
	case WD_52BLOODCASTLE_MASTER_LEVEL:
        switch ( o->Type )
        {
        case 11 :   //  ����01.smd
            {
                char indexLight[7] = { 1, 2, 4, 6, 9, 10, 11 };

                Luminosity = sinf ( (o->Angle[2]*20+WorldTime)*0.001f )*0.5f + 0.5f;
                Vector ( Luminosity*1.f, Luminosity*0.5f, 0.f, Light );

                for ( int i=0; i<7; ++i )
                {
                    Vector ( 0.f, 0.f, 2.f, p );
                    b->TransformPosition ( BoneTransform[indexLight[i]], p, Position );
                    CreateSprite ( BITMAP_LIGHT, Position, 0.5f, Light, o );
                }
            }
            break;
        case 13 :   //  ��02.smd
            Luminosity = sinf ( WorldTime*0.001f )*0.3f + 0.7f;
            Vector ( Luminosity, Luminosity, Luminosity, Light );
            Vector ( 0.f, 0.f, 0.f, p );
            b->TransformPosition ( BoneTransform[3], p, Position );
            CreateSprite ( BITMAP_FLARE, Position, Luminosity+0.5f, Light, o );
            break;
        case 37:    //  �׽�Ʈ.
            Vector ( 1.f, 1.f, 1.f, Light );
            if(rand()%2==0)
                if((int)((o->Timer++)+2)%4==0)
                {
                    CreateParticle ( BITMAP_ADV_SMOKE+1, o->Position, o->Angle, Light );
                    CreateParticle ( BITMAP_ADV_SMOKE, o->Position, o->Angle, Light, 0 ); //������
                }
            if(rand()%2==0)
                if((int)(o->Timer++)%4==0)
                {
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 6 );
                    CreateParticle ( BITMAP_ADV_SMOKE, o->Position, o->Angle, Light, 1 ); //ū��

                    Vector ( 1.f, 0.8f, 0.8f, Light );
                    CreateParticle ( BITMAP_FLARE, o->Position, o->Angle, Light, 4, 0.19f, NULL );
                }
            break;
        }
        break;
	case WD_55LOGINSCENE:
		{
			switch(o->Type)
			{
			case 84:  //  �Ȱ� ȿ�� - �����U���� �帣�� ������
				if(rand()%5 == 0)
					CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 10, o->Scale, o );
				break;
			case 90:
			case 86:   //  �ҿ뵹��
				break;
			case 89:   //  ���׿�
				{
					int iTimeCheck = (int)WorldTime%8000;

					if(iTimeCheck >= 7950)
					{
						Vector(o->Position[0]+rand()%2048 - 1024,o->Position[1]+rand()%2048 - 1024,o->Position[2]+3000+rand()%600,Position);
						CreateEffect(MODEL_FIRE,Position,o->Angle,o->Light, 9);
					}
				}
				break;
			}
		}
    default :
        if ( RenderChaosCastleVisual( o, b ) ) return;  //  ī���� ĳ��.
        if ( RenderHellasVisual( o, b ) ) return;       //  ���.
        if ( battleCastle::RenderBattleCastleVisual(    o, b ) ) return;
		if( M31HuntingGround::RenderHuntingGroundObjectVisual(o, b) ) return;	//. ���� �����
#ifdef CRYINGWOLF_2NDMVP
		if( M34CryingWolf2nd::RenderCryingWolf2ndObjectVisual(o, b) ) return;	//. ũ���̿��� ������
#endif // CRYINGWOLF_2NDMVP
		if( M33Aida::RenderAidaObjectVisual(o, b) ) return;	// ���̴�
		if( M34CryWolf1st::RenderCryWolf1stObjectVisual(o, b) ) return;	//. ũ���̿��� ������
		if (M37Kanturu1st::RenderKanturu1stObjectVisual(o, b))	// ĭ���� 1��.
			return;
		if(M38Kanturu2nd::Render_Kanturu2nd_ObjectVisual(o, b)) return;	// ĭ���� 2��
		if( M39Kanturu3rd::RenderKanturu3rdObjectVisual(o, b) ) return;	// ĭ���� 3��
		if (SEASON3A::CGM3rdChangeUp::Instance().RenderObjectVisual(o, b)) return;
		if( g_CursedTemple->RenderObjectVisual( o, b ) ) return;
		if( SEASON3B::GMNewTown::RenderObjectVisual( o, b ) ) return;
		if( SEASON3C::GMSwampOfQuiet::RenderObjectVisual( o, b ) ) return;
#ifdef PSW_ADD_MAPSYSTEM
		if( TheMapProcess().RenderObjectVisual( o, b ) == true ) return;
#endif //PSW_ADD_MAPSYSTEM
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���忡 �ִ� ��� ������Ʈ�� ������
///////////////////////////////////////////////////////////////////////////////

void RenderObjects()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_RENDER_OBJECTS, PROFILING_RENDER_OBJECTS );
#endif // DO_PROFILING
#ifdef MR0
	VPManager::Enable();
#endif //MR0

    float   range = 0.f;
    if( World==WD_10HEAVEN )
    {
	    range = -10.f;
    }

	if(Time_Effect > 40)
		Time_Effect = 0;
	Time_Effect++;
	
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			ob->Visible = TestFrustrum2D((float)(i*16+8),(float)(j*16+8),-180.f);
			if(g_Direction.m_CKanturu.IsMayaScene()
				|| World == WD_51HOME_6TH_CHAR	// ��� ������Ʈ�� �ø� ������ ���� ������ �׷��ش�
#ifdef PJH_NEW_SERVER_SELECT_MAP
				|| World == WD_73NEW_LOGIN_SCENE
				|| World == WD_74NEW_CHARACTER_SCENE
#else //PJH_NEW_SERVER_SELECT_MAP
				|| World == WD_77NEW_LOGIN_SCENE
				|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef CSK_ADD_MAP_ICECITY	
				|| IsIceCity()
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
				|| IsPKField()
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER2
				|| IsDoppelGanger2()
#endif	// YDG_ADD_MAP_DOPPELGANGER2
				)
			{
				OBJECT *o  = ob->Head;

				while(1)
				{
					if(o != NULL)
					{
						if(g_Direction.m_CKanturu.IsMayaScene() && (o->Type == 0 || o->Type == MODEL_STORM2))
						{
							RenderObject(o);
							RenderObjectVisual(o);
						}
						else 
#ifdef PJH_NEW_SERVER_SELECT_MAP
						if(World == WD_73NEW_LOGIN_SCENE)
						{
							float fDistance_x = CameraPosition[0] - o->Position[0];
							float fDistance_y = CameraPosition[1] - o->Position[1];
							float fDistance = sqrtf(fDistance_x * fDistance_x + fDistance_y * fDistance_y);
							float fDis = 2000.0f;

							// ���̿� �ܻ�� û�ڽ�
							if(((o->Type>=122 && o->Type<=124) || (o->Type==159) || (o->Type==126) || (o->Type==129) || (o->Type==127)) && 
								TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-500.f) && fDistance < fDis*2.0f)
							{
								if (o->BlendMeshLight < 1.0f)
									o->BlendMeshLight += 0.03f;
								else
									o->BlendMeshLight = 1.0f;

 								if (o->AlphaTarget < 1.0f)
 									o->AlphaTarget += 0.03f;
								else
									o->AlphaTarget = 1.0f;

 								RenderObject(o);
 								RenderObjectVisual(o);
							}
							else if(TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-500.f) && fDistance < fDis
#ifdef PBG_FIX_RENDEROBJ_MAXINDEX
								// �� max ������ �ʰ��� �κ��� ȣ��ȴ�, �ִ밹���� Ȯ�� �ϴ���.(MAX_WORLD_OBJECTS���� delete�ȵ�)
								// �ϴ� 160 �̻� ��� ����� ���°� ���Ƽ� ���� Ȯ��
								&& o->Type <= MAX_WORLD_OBJECTS
#endif //PBG_FIX_RENDEROBJ_MAXINDEX
								) // �ø� ����ȭ ������ �κС�
							{
 								if (o->AlphaTarget < 1.0f)
 									o->AlphaTarget += 0.03f;
								else
									o->AlphaTarget = 1.0f;

 								RenderObject(o);
 								RenderObjectVisual(o);
							}
							else if (o->AlphaTarget != 0 && fDistance > fDis)
							{
								o->BlendMeshLight = 0.0f;
								o->Alpha = 0.0f;
								o->AlphaTarget = 0.0f;
							}
						}
#else	// PJH_NEW_SERVER_SELECT_MAP
						if(World == WD_77NEW_LOGIN_SCENE)
						{
							float fDistance_x = CameraPosition[0] - o->Position[0];
							float fDistance_y = CameraPosition[1] - o->Position[1];
							float fDistance = sqrtf(fDistance_x * fDistance_x + fDistance_y * fDistance_y);

							if (((o->Type>=5 && o->Type<=14) || (o->Type>=87 && o->Type<=88) || (o->Type == 4 || o->Type == 129))
								&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-500.f) && fDistance < 5000.f) // �ø� ����ȭ ������ �κС�
							{
 								if (o->AlphaTarget < 1.0f)
 									o->AlphaTarget += 0.03f;
								else
									o->AlphaTarget = 1.0f;

								// ������ LightEnable Mesh ������, ������������ Syncronization�� ���� Disable ó���մϴ�.
#ifdef LDS_MR0_MODIFY_LOGINSCENE_SHADOWPROBLEM
								o->LightEnable = false;
#endif // LDS_MR0_MODIFY_LOGINSCENE_SHADOWPROBLEM

								RenderObject(o);
								RenderObjectVisual(o);
							}
							else if (o->Type == 130
								|| (TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-500.f) && fDistance < 4500.f)) // �ø� ����ȭ ������ �κС�
							{
								if (o->BlendMeshLight < 1.0f)
									o->BlendMeshLight += 0.03f;
								else
									o->BlendMeshLight = 1.0f;

 								if (o->AlphaTarget < 1.0f)
 									o->AlphaTarget += 0.03f;
								else
									o->AlphaTarget = 1.0f;

								RenderObject(o);
								RenderObjectVisual(o);
							}
							else if (o->AlphaTarget != 0 && fDistance > 2000.f)
							{
								o->BlendMeshLight = 0.0f;
								o->Alpha = 0.0f;
								o->AlphaTarget = 0.0f;
							}
						}
#endif //PJH_NEW_SERVER_SELECT_MAP
						else if((World == WD_51HOME_6TH_CHAR	// ��������
#ifndef PJH_NEW_SERVER_SELECT_MAP
							|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
							) &&
							((o->Type>=5 && o->Type<=14) || (o->Type>=87 && o->Type<=88) || (o->Type == 4 || o->Type == 129))	// ����, ����
							&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-400.f))	// �ø� ����ȭ ������ �κС�
						{
							// ������ LightEnable Mesh ������, ������������ Syncronization�� ���� Disable ó���մϴ�.
#ifdef LDS_MR0_MODIFY_LOGINSCENE_SHADOWPROBLEM
							if( o->Type>=5 && o->Type<=14 )	// ������ �Ȱ� �ؽ��Ŀ� �����ϱ� ���� ������ ��.
							{
								o->LightEnable = false;	
							}
#endif // LDS_MR0_MODIFY_LOGINSCENE_SHADOWPROBLEM
							
							// �ø� ������ ���� ������ �׸�
							RenderObject(o);
							RenderObjectVisual(o);
						}
#ifdef PJH_NEW_SERVER_SELECT_MAP
						//û�ڽ��� �� ��
						else if((World == WD_74NEW_CHARACTER_SCENE) && (o->Type==129 || o->Type==98))
						{
 							RenderObject(o);
 							RenderObjectVisual(o);
						}
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef CSK_ADD_MAP_ICECITY	
						else if((World == WD_57ICECITY || World == WD_58ICECITY_BOSS)
							&& (o->Type == 30 || o->Type == 31) 
							&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f)) 
						{
							// �ø� ������ ���� ������ �׸�
							RenderObject(o);
							RenderObjectVisual(o);
						}
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
						else if(IsPKField() && (o->Type == 16 || o->Type == 67 || o->Type == 68)
							&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f)) 
						{
							// �ø� ������ ���� ������ �׸�
							RenderObject(o);
							RenderObjectVisual(o);
						}
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER2
						else if(IsDoppelGanger2() && (o->Type == 16 || o->Type == 67 || o->Type == 68)
							&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f)) 
						{
							// �ø� ������ ���� ������ �׸�
							RenderObject(o);
							RenderObjectVisual(o);
						}
#endif	// YDG_ADD_MAP_DOPPELGANGER2

						if(o->Next == NULL)
							break;
						else
							o = o->Next;
					}
					else
						break;
				}
			}

			if(ob->Visible || CameraTopViewEnable)
			{
     			OBJECT *o  = ob->Head;
				while(1)
				{
					if(o != NULL) 
					{
						if(o->Live)
						{
							o->Visible = TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,o->CollisionRange+range);
							// �ø� ������ ���� ������ �׸� ������Ʈ�� �׸��� �ʴ´�.
							if ((World == WD_51HOME_6TH_CHAR 
#ifndef PJH_NEW_SERVER_SELECT_MAP
								|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
								) &&
								((o->Type>=5 && o->Type<=14) || (o->Type>=87 && o->Type<=88) || (o->Type == 4 || o->Type == 129)));
							else
#ifdef CSK_ADD_MAP_ICECITY	
							if((World == WD_57ICECITY || World == WD_58ICECITY_BOSS) && (o->Type == 30 || o->Type == 31 || o->Type == 76));
							else
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
							if((IsPKField()
#ifdef YDG_ADD_MAP_DOPPELGANGER2
								|| IsDoppelGanger2())
#else YDG_ADD_MAP_DOPPELGANGER2
								)
#endif	// YDG_ADD_MAP_DOPPELGANGER2
								&& (o->Type == 16 || o->Type == 67 || o->Type == 68));
							else
#endif //PBG_ADD_PKFIELD
#ifdef PJH_NEW_SERVER_SELECT_MAP
							if(World == WD_73NEW_LOGIN_SCENE);
#else
							if (World == WD_77NEW_LOGIN_SCENE);
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef PJH_NEW_SERVER_SELECT_MAP
							else if((World == WD_74NEW_CHARACTER_SCENE) && (o->Type == 129 || o->Type==98));
#endif //PJH_NEW_SERVER_SELECT_MAP
							else
							if(o->Visible || CameraTopViewEnable)
							{
								bool Success = false;
      							if ( World==WD_2DEVIAS && o->Type==100 )	// �ν�Ʈ Ÿ�� �Ա�
								{
									int Level;
									if ( GetBaseClass(Hero->Class)==CLASS_DARK || GetBaseClass(Hero->Class)==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK
										|| GetBaseClass(Hero->Class)==CLASS_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK
										)
										Level = 50*2/3;
									else
									    Level = 50;
									if(CharacterAttribute->Level>=Level)
						     			Success = true;
								}
								else
									Success = true;
								if(Success)
								{
									RenderObject(o);
									RenderObjectVisual(o);
								}
							}

#ifdef CSK_DEBUG_RENDER_BOUNDINGBOX
							if(o->Visible == true && g_bRenderBoundingBox == true)
							{
								RenderBoundingBox(o);
							}
#endif // CSK_DEBUG_RENDER_BOUNDINGBOX
						}

						if(o->Next == NULL) break;
						o = o->Next;
					}
					else break;
				}
			}
		}
	}
#ifdef MR0
	VPManager::Disable();
#endif //MR0

#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_RENDER_OBJECTS );
#endif // DO_PROFILING	
}

#ifdef MR0
void RenderObject_AfterCharacter(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
	if(Calc_RenderObject(o, Translate,Select, ExtraMon))
		Draw_RenderObject_AfterCharacter(o, Translate, Select, ExtraMon);
}

#else

void RenderObject_AfterCharacter(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
	if(Calc_RenderObject(o, Translate,Select, ExtraMon) == false)
	{
		return;
	}
	Draw_RenderObject_AfterCharacter(o, Translate, Select, ExtraMon);
}
#endif //MR0

void Draw_RenderObject_AfterCharacter(OBJECT *o,bool Translate,int Select, int ExtraMon)
{
	BMD *b = &Models[o->Type];

#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif //MR0

    if ((EditFlag != EDIT_NONE) || (EditFlag==EDIT_NONE && o->HiddenMesh != -2))
	{
		M37Kanturu1st::RenderKanturu1stAfterObjectMesh(o, b);
		M38Kanturu2nd::Render_Kanturu2nd_AfterObjectMesh(o, b);
		M39Kanturu3rd::RenderKanturu3rdAfterObjectMesh(o, b);
		SEASON3A::CGM3rdChangeUp::Instance().RenderAfterObjectMesh(o, b);
		g_CursedTemple->RenderObject_AfterCharacter(o, b);
		SEASON3B::GMNewTown::RenderObjectAfterCharacter(o, b);
		SEASON3C::GMSwampOfQuiet::RenderObjectAfterCharacter(o, b);

#ifdef PSW_ADD_MAPSYSTEM
		TheMapProcess().RenderAfterObjectMesh( o, b );
#endif //PSW_ADD_MAPSYSTEM
	}

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
}

void RenderObjects_AfterCharacter()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_RENDER_OBJECTS_AFTERCHARACTER, PROFILING_RENDER_OBJECTS_AFTERCHARACTER );
#endif // DO_PROFILING
	// ���忡�� �ѹ� �ɷ��ְ�
	if( !(World == WD_37KANTURU_1ST || World == WD_38KANTURU_2ND || World == WD_39KANTURU_3RD
		|| World == WD_40AREA_FOR_GM
		|| World == WD_41CHANGEUP3RD_1ST
		|| World == WD_42CHANGEUP3RD_2ND
		|| g_CursedTemple->IsCursedTemple()

		|| World == WD_51HOME_6TH_CHAR 
#ifndef PJH_NEW_SERVER_SELECT_MAP
		|| World == WD_77NEW_LOGIN_SCENE 
		|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
		|| World == WD_56MAP_SWAMP_OF_QUIET
#ifdef CSK_ADD_MAP_ICECITY	
		|| IsIceCity()
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
		|| IsPKField()
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER1
		|| IsDoppelGanger1()
#endif	// YDG_ADD_MAP_DOPPELGANGER1
#ifdef YDG_ADD_MAP_DOPPELGANGER2
		|| IsDoppelGanger2()
#endif	// YDG_ADD_MAP_DOPPELGANGER2
#ifdef YDG_ADD_MAP_DOPPELGANGER3
		|| IsDoppelGanger3()
#endif	// YDG_ADD_MAP_DOPPELGANGER3
#ifdef YDG_ADD_MAP_DOPPELGANGER4
		|| IsDoppelGanger4()
#endif	// YDG_ADD_MAP_DOPPELGANGER4
#ifdef LDS_ADD_MAP_UNITEDMARKETPLACE
		|| IsUnitedMarketPlace()
#endif	// LDS_ADD_MAP_UNITEDMARKETPLACE
#ifdef ASG_ADD_MAP_KARUTAN
		|| IsKarutanMap()
#endif	// ASG_ADD_MAP_KARUTAN
		) )
		return;

#ifdef MR0
	VPManager::Enable();
#endif //MR0
	
	float   range = 0.f;
    if( World==WD_10HEAVEN )
    {
	    range = -10.f;
    }
	
	if(Time_Effect > 40)
		Time_Effect = 0;
	Time_Effect++;
	
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			ob->Visible = TestFrustrum2D((float)(i*16+8),(float)(j*16+8),-180.f);
		
			if(g_Direction.m_CKanturu.IsMayaScene())
			{
				OBJECT *o  = ob->Head;

				while(1)
				{
					if(o != NULL)
					{
						if(o->Type == MODEL_STORM3)
						{
							RenderObject_AfterCharacter(o);
						}

						if(o->Next == NULL)
							break;
						else
							o = o->Next;
					}
					else
						break;
				}
			}

			if(World == WD_51HOME_6TH_CHAR	// ��� ������Ʈ�� �ø� ������ ���� ������ �׷��ش� (aftercharacter)
#ifndef PJH_NEW_SERVER_SELECT_MAP
				|| World == WD_77NEW_LOGIN_SCENE
				|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef CSK_ADD_MAP_ICECITY	
				|| IsIceCity()
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
				|| IsPKField()
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER2
				|| IsDoppelGanger2()
#endif	// YDG_ADD_MAP_DOPPELGANGER2
				)
			{
				OBJECT *o  = ob->Head;

				while(1)
				{
					if(o != NULL)
					{
						if(World == WD_51HOME_6TH_CHAR &&
							(o->Type==89)	// ������ ��
							&& TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-400.f))	// �ø� ����ȭ ������ �κС�
						{
							RenderObject_AfterCharacter(o);
						}
#ifdef CSK_ADD_MAP_ICECITY	
						else if((World == WD_57ICECITY || World == WD_58ICECITY_BOSS) && o->Type == 76 && TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f))
						{
							RenderObject_AfterCharacter(o);
						}
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
						else if(IsPKField() && (o->Type == 16 || o->Type == 67 || o->Type == 68) && TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f))
						{
							RenderObject_AfterCharacter(o);
						}
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER2
						else if(IsDoppelGanger2() && (o->Type == 16 || o->Type == 67 || o->Type == 68) && TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,-600.f))
						{
							RenderObject_AfterCharacter(o);
						}
#endif	// YDG_ADD_MAP_DOPPELGANGER2
						if(o->Next == NULL)
							break;
						else
							o = o->Next;
					}
					else
						break;
				}
			}
			
			if(ob->Visible || CameraTopViewEnable)
			{
     			OBJECT *o  = ob->Head;
				while(1)
				{
					if(o != NULL) 
					{
						if(o->Live && o->m_bRenderAfterCharacter == true)	// m_bRenderAfterCharacter �� ������ true�ΰ͸�
						{
							o->Visible = TestFrustrum2D(o->Position[0]*0.01f,o->Position[1]*0.01f,o->CollisionRange+range);
							// �ø� ������ ���� ������ �׸� ������Ʈ�� �׸��� �ʴ´�.
							if ((World == WD_51HOME_6TH_CHAR
#ifndef PJH_NEW_SERVER_SELECT_MAP
								|| World == WD_77NEW_LOGIN_SCENE 
								|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
								) && (o->Type==89));
							else
#ifdef CSK_ADD_MAP_ICECITY	
							// �ø� ������ ���� ������ �׸� ������Ʈ�� �׸��� �ʴ´�.
							if(IsIceCity() && o->Type == 76);
							else
#endif // CSK_ADD_MAP_ICECITY
#ifdef PBG_ADD_PKFIELD
							if(IsPKField() && (o->Type == 16 || o->Type == 67 || o->Type == 68));
							else
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_MAP_DOPPELGANGER2
							if(IsDoppelGanger2() && (o->Type == 16 || o->Type == 67 || o->Type == 68));
							else
#endif	// YDG_ADD_MAP_DOPPELGANGER2
							if(o->Visible || CameraTopViewEnable)
							{
								bool Success = false;
      							if ( World==WD_2DEVIAS && o->Type==100 )
								{
									int Level;

									if ( GetBaseClass(Hero->Class)==CLASS_DARK || GetBaseClass(Hero->Class)==CLASS_DARK_LORD 
#ifdef PBG_ADD_NEWCHAR_MONK
										|| GetBaseClass(Hero->Class)==CLASS_RAGEFIGHTER
#endif //PBG_ADD_NEWCHAR_MONK
										)
										Level = 80*2/3;
									else
									    Level = 80;
									if(CharacterAttribute->Level>=Level)
						     			Success = true;
								}
								else
									Success = true;
								if(Success)
								{
									RenderObject_AfterCharacter(o);
								}
							}
						}
						if(o->Next == NULL) break;
						o = o->Next;
					}
					else break;
				}
			}
		}
	}
#ifdef MR0
	VPManager::Disable();
#endif //MR0
#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_RENDER_OBJECTS_AFTERCHARACTER );
#endif // DO_PROFILING
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ ó��
///////////////////////////////////////////////////////////////////////////////

extern int CameraWalkCut;
extern int CurrentCameraCount;

void MoveObject(OBJECT *o)
{
	if(World == 9)
	{
		if((int)WorldTime%4000 < 1000)
		if(rand()%100==0)
		{
			float Luminosity = (float)(rand()%12+4)*0.1f;
			vec3_t Light;
			Vector(Luminosity*0.2f,Luminosity*0.3f,Luminosity*0.5f,Light);
			AddTerrainLight(Hero->Object.Position[0]+rand()%1200-600,
				Hero->Object.Position[1]+rand()%1200-600,
				Light,12,PrimaryTerrainLight);
			//PlayBuffer(SOUND_THUNDER01);
		}
		PlayBuffer(SOUND_RAIN01,NULL,true);
	}
	if(World == 0)
	{
		if(o->Type==MODEL_HOUSE_WALL01+4 || o->Type==MODEL_HOUSE_WALL01+5)
		{
			if(HeroTile==4)
				o->AlphaTarget = 0.f;
			else
				o->AlphaTarget = 1.f;
		}
#ifdef _PVP_MURDERER_HERO_ITEM
		else if(o->Type==MODEL_MURDERER_DOG)	// pk ���� �� ���� ���� 2��
		{
			if (o->PriorAnimationFrame > o->AnimationFrame)
			{
				if (rand() % 10 == 0 && o->CurrentAction != MONSTER01_STOP2)
					o->CurrentAction = MONSTER01_STOP2;
				else
					o->CurrentAction = MONSTER01_STOP1;
			}
		}
#endif	// _PVP_MURDERER_HERO_ITEM
	}
	if(World == 2)
	{
		if(o->Type==81 || o->Type==82 || o->Type==96 || o->Type==98 || o->Type==99)
		{
			if(HeroTile==3 || HeroTile>=10)
				o->AlphaTarget = 0.f;
			else
				o->AlphaTarget = 1.f;
		}
	}
	Alpha(o);
	if(o->Alpha < 0.01f) return;
	BMD *b = &Models[o->Type];
	b->CurrentAction = o->CurrentAction;

	//	�ִϸ��̼� �ӵ� ����.
	float fSpeed = o->Velocity;
	if ( World==WD_8TARKAN )	//	Ÿ��ĭ
	{
		switch ( o->Type )
		{
		case 8 :
			fSpeed *= 4.0f;
			break;
		}
	}
#ifndef PJH_NEW_SERVER_SELECT_MAP
	else if(World == WD_78NEW_CHARACTER_SCENE)
	{
		if( o->Type == 4 )
		{
			if(o->CurrentAction == 0)
			{
				fSpeed *= 2.2f;
			}
			else
			{	
				fSpeed *= 2.0f;
			}

			if(SEASON3B::GMNewTown::IsCheckMouseIn() == true)
			{
				if(o->CurrentAction == 0)
				{
					fSpeed *= 2.0f;
				}
				else
				{	
					fSpeed *= 3.0f;
				}
			}
		}
	}
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef CSK_ADD_MAP_ICECITY
	else if(IsIceCity() && (o->Type == 16 || o->Type == 17 || o->Type == 68))
	{
		fSpeed = b->Actions[o->CurrentAction].PlaySpeed;
	}
#endif // CSK_ADD_MAP_ICECITY
#ifdef ASG_ADD_MAP_KARUTAN
	else if (IsKarutanMap() && (o->Type == 66 || o->Type == 107))
	{
		fSpeed = b->Actions[o->CurrentAction].PlaySpeed;
	}
#endif	// ASG_ADD_MAP_KARUTAN

	b->PlayAnimation(&o->AnimationFrame,&o->PriorAnimationFrame,&o->PriorAction,fSpeed,o->Position,o->Angle);

	vec3_t p;
	vec3_t Light;
	float Luminosity;
	Vector(0.f,0.f,0.f,p);
	if(SceneFlag==LOG_IN_SCENE || SceneFlag==CHARACTER_SCENE)
	{
		switch(o->Type)
		{
		case MODEL_LOGO:
			o->BlendMeshTexCoordV = -((int)WorldTime%4000*0.00025f);
			break;
		case MODEL_WAVEBYSHIP:
			o->BlendMeshTexCoordV = -((int)WorldTime%4000*0.00025f);
			break;
		case MODEL_MUGAME:
			if(CameraWalkCut==0)
				Luminosity = CurrentCameraCount*0.02f;
			else
			{
				Luminosity = 1.5f;
				/*if(CameraWalkCut==1 && CurrentCameraCount==0)
				{
				for(int i=0;i<100;i++)
				{
				Vector((float)(rand()%200-100),(float)(rand()%40-20),(float)(rand()%200-100),Position);
				VectorAdd(Position,o->Position,Position);
				Vector(1.f,1.f,1.f,Light);
				CreateParticle(BITMAP_SPARK,Position,o->Angle,Light);
				}
			}*/
			}
			Vector(Luminosity*1.f,Luminosity*1.f,Luminosity*1.f,o->Light);
			o->BlendMeshLight = Luminosity;
			break;
		}
	}
	
    switch(World)
	{
	case WD_0LORENCIA:
		switch(o->Type)
		{
		case MODEL_HOUSE01+3:
		case MODEL_HOUSE01+4:
			o->BlendMeshTexCoordV = -(int)WorldTime%1000 * 0.001f;
			break;
		case MODEL_HOUSE01+2:
		case MODEL_HOUSE_WALL01+1:
			o->BlendMeshLight = (float)(rand()%4+4)*0.1f;
			break;
		case MODEL_LIGHT01:
			CreateFire(0,o,0.f,0.f,0.f);
			o->HiddenMesh = -2;
			break;
		case MODEL_LIGHT01+1:
			CreateFire(1,o,0.f,0.f,0.f);
			o->HiddenMesh = -2;
			break;
		case MODEL_LIGHT01+2:
			CreateFire(2,o,0.f,0.f,0.f);
			o->HiddenMesh = -2;
			break;
		case MODEL_BRIDGE:
			CreateFire(0,o,90.f,-200.f,30.f);
			CreateFire(0,o,90.f, 200.f,30.f);
			break;
		case MODEL_DUNGEON_GATE:
			CreateFire(0,o,-150.f,-150.f,140.f);
			CreateFire(0,o, 150.f,-150.f,140.f);
			break;
		case MODEL_FIRE_LIGHT01:
			CreateFire(0,o,0.f,0.f,200.f);
			break;
		case MODEL_FIRE_LIGHT01+1:
			CreateFire(0,o,0.f,-30.f,60.f);
			break;
		case MODEL_STREET_LIGHT:
			Luminosity = (float)(rand()%2+6)*0.1f;
			Vector(Luminosity,Luminosity*0.8f,Luminosity*0.6f,Light);
			AddTerrainLight(o->Position[0],o->Position[1],Light,3,PrimaryTerrainLight);
			break;
		case MODEL_BONFIRE:
			CreateFire(0,o,0.f,0.f,60.f);
			o->BlendMeshLight = (float)(rand()%6+4)*0.1f;
			//CreateBonfire(o->Position,o->Angle);
			break;
			/*	case MODEL_FIREPLACE01:
			CreateFire(0,o,0.f,0.f,60.f);
			//CreateBonfire(o->Position,o->Angle);
			break;
			case MODEL_DOOR_WOOD01:
			case MODEL_DOOR_STEEL01:
			{
			vec3_t Range;
			VectorSubtract(Hero->Object.Position,o->Position,Range);
			float Distance = Range[0]*Range[0]+Range[1]*Range[1];
			if(Distance <= 120.f*120.f)
			{
			o->Direction[2] = (120.f+(Hero->Object.Position[1]-o->Position[1]))*0.6f;
			}
			o->Angle[2] = TurnAngle2(o->Angle[2],o->Direction[2],FarAngle(o->Angle[2],o->Direction[2])*0.1f);
			if(FarAngle(o->Angle[2],o->Direction[2]) < absf(o->Direction[2])*0.2f)
			o->Direction[2] = -o->Direction[2] * 0.2f;
			break;
		}*/
		case MODEL_CANDLE:
			Luminosity = (float)(rand()%4+3)*0.1f;
			Vector(Luminosity,Luminosity*0.6f,Luminosity*0.2f,Light);
			AddTerrainLight(o->Position[0],o->Position[1],Light,3,PrimaryTerrainLight);
			break;
			/*case MODEL_GOLD01:
			Vector(0.f,-15.f,25.f,p);
			CreateShiny(o,p);
			break;*/
		case MODEL_SIGN01+1:
			Vector(50.f,-10.f,120.f,p);
			//CreateShiny(o,p);
			break;
			/*case MODEL_STONE_WALL01+3:
			o->Live = false;
			break;*/
		}
		break;
	case WD_1DUNGEON:
		switch(o->Type)
		{
		case 52:
			if(rand()%3==0)
				CreateEffect(MODEL_DUNGEON_STONE01,o->Position,o->Angle,o->Light);
				//CreateEffect(MODEL_STONE1,o->Position,o->Angle,o->Light);
			o->HiddenMesh = -2;
			break;
		case 22:
		case 23:
		case 24:
			Models[o->Type].StreamMesh = 1;
			o->BlendMeshTexCoordV = -(float)((int)WorldTime%1000)*0.001f;
			break;
		case 41:
			CreateFire(0,o,0.f,-30.f,240.f);
			break;
		case 42:
			CreateFire(0,o,0.f,0.f,190.f);
			break;
		case 39:
		case 40:
		case 51:
			o->HiddenMesh = -2;
			break;
		}
		break;
	case WD_2DEVIAS:
		switch(o->Type)
		{
		case 78:
			o->BlendMeshLight = (float)(rand()%4+4)*0.1f;
			break;
		case 30:	//. ���
			{
				vec3_t Position;
				Position[0] = o->Position[0];
				Position[1] = o->Position[1];
				Position[2] = o->Position[2] + 160.f;
				CreateParticle(BITMAP_TRUE_FIRE, Position, o->Angle,
					o->Light, 0, o->Scale);
				CreateParticle(BITMAP_SMOKE, Position, o->Angle,
					o->Light, 21, 0.5f+((rand()%9)*0.1f));
			}
			break;
		case 66:	//. ��ں�
			CreateFire(0,o,0.f,0.f,50.f);
			break;
		case 86:
		case 20:
		case 65:
		case 88:
			if(EditFlag == EDIT_NONE)
			{
				float dx = Hero->Object.Position[0]-o->HeadTargetAngle[0];
				float dy = Hero->Object.Position[1]-o->HeadTargetAngle[1];
				float Distance = sqrtf(dx*dx+dy*dy);
				if(Distance < 200.f)
				{
					if(o->Type==86)
					{
						if(o->Angle[2]==90.f)
							o->Position[1] = o->HeadTargetAngle[1]+(200.f-Distance)*2.f;
						if(o->Angle[2]==270.f)
							o->Position[1] = o->HeadTargetAngle[1]-(200.f-Distance)*2.f;
						if(o->Angle[2]==0.f)
							o->Position[0] = o->HeadTargetAngle[0]+(200.f-Distance)*2.f;
						if(o->Angle[2]==180.f)
							o->Position[0] = o->HeadTargetAngle[0]-(200.f-Distance)*2.f;
                     	PlayBuffer(SOUND_DOOR02);
					}
					else
					{
						if(o->HeadAngle[2]==90.f)
							o->Angle[2] = 30.f-(200.f-Distance)*0.5f;
						if(o->HeadAngle[2]==270.f)
							o->Angle[2] = 330.f+(200.f-Distance)*0.5f;
						if(o->HeadAngle[2]==0.f)
							o->Angle[2] = 300.f-(200.f-Distance)*0.5f;
						if(o->HeadAngle[2]==180.f)
							o->Angle[2] = 240.f+(200.f-Distance)*0.5f;
                     	PlayBuffer(SOUND_DOOR01);
					}
				}
				else
				{
					o->Angle[2] = TurnAngle2(o->Angle[2],o->HeadAngle[2],10.f);
					o->Position[0] += (o->HeadTargetAngle[0]-o->Position[0])*0.2f;
					o->Position[1] += (o->HeadTargetAngle[1]-o->Position[1])*0.2f;
				}
			}
			break;
		}
		break;
	case WD_3NORIA:
		switch(o->Type)
		{
		case MODEL_WARP:
			vec3_t Position; 
			Vector(o->Position[0], o->Position[1]-50.f,o->Position[2]+350.f, Position);
			Vector(0.5f, 0.5f, 0.5f, Light);
			CreateParticle(BITMAP_SPARK+1, Position, o->Angle, Light, 9, 1.4f);
			break;
		case 18:
			o->BlendMeshTexCoordV = (int)WorldTime%1000 * 0.001f;
			break;
		case 39:
			o->BlendMesh = 1;
			break;
		case 41:
			o->BlendMesh = 0;
			o->BlendMeshTexCoordV = (int)WorldTime%2000 * 0.0005f;
			break;
		case 42:
			Models[o->Type].StreamMesh = 0;
			o->BlendMeshTexCoordU = -(float)((int)WorldTime%500)*0.002f;
			break;
		case 43:
			Models[o->Type].StreamMesh = 0;
			o->BlendMeshTexCoordU = (float)((int)WorldTime%500)*0.002f;
			break;
		}
		break;
	case WD_4LOSTTOWER:
		switch(o->Type)
		{
		case 38:
		case 39:
			CheckSkull(o);
			break;
		case 3:
		case 4:
			o->BlendMeshTexCoordU = -(int)WorldTime%1000 * 0.001f;
			break;
		case 19:
		case 20:
			o->BlendMesh = 4;
			o->BlendMeshTexCoordU = -(int)WorldTime%1000 * 0.001f;
			break;
		case 18:
			o->BlendMesh = 1;
			break;
		case 23:
			o->BlendMesh = 1;
			//b->TransformPosition(BoneTransform[1],p,Position);
			//CreateSprite(BITMAP_LIGHT,Position,2.f,Light,o);
			break;
		case 24:
			o->HiddenMesh = -2;
			if(rand()%64==0)
				CreateEffect(BITMAP_FLAME,o->Position,o->Angle,o->Light);
			//o->BlendMeshTexCoordV = (int)WorldTime%1000 * 0.001f;
			break;
		case 25:
			o->HiddenMesh = -2;
			break;
		}
		break;
	case WD_5UNKNOWN:
		switch(o->Type)
		{
		case 2:
			o->BlendMesh = 0;
			break;
		case 3:
			o->BlendMesh = 0;
			o->BlendMeshLight = (float)(rand()%4+6)*0.1f;
			break;
		}
		break;
	case WD_6STADIUM:
		switch(o->Type)
		{
		case 21:
			o->BlendMesh = 3;
			o->BlendMeshTexCoordV = -(int)WorldTime%1000 * 0.001f;
			break;
		case 38:
			o->HiddenMesh = -2;
			break;
		}
		break;
	case WD_7ATLANSE:
		switch(o->Type)
		{
		case 22:
			o->HiddenMesh = -2;
			o->Timer += 0.1f;
			if(o->Timer > 10.f)
				o->Timer = 0.f;
			if(o->Timer > 5.f)
     			CreateParticle(BITMAP_BUBBLE,o->Position,o->Angle,o->Light);
			break;
		case 23:
			o->BlendMesh = 0;
			//o->BlendMeshLight = o->Light[1]+1.f;
       		o->BlendMeshLight = sinf(WorldTime*0.002f)*0.3f+0.5f;
			break;
		case 32:
		case 34:
			o->BlendMesh = 1;
       		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.5f+0.5f;
			break;
		case 38:
			o->BlendMesh = 0;
       		//o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
			break;
		case 40:
			o->BlendMesh = 0;
       		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.5f;
			o->Velocity = 0.05f;
			break;
		}
		break;
	case WD_8TARKAN:
		switch(o->Type)
		{
        case 2:    //  Ǫ���� �� �����̱�.
			o->BlendMesh = 0;
			o->BlendMeshTexCoordU = -(int)WorldTime%1000 * 0.001f;
            break;

        case 4:    //  ������� �Һ�.
            {
                float   sine = (float)sinf(WorldTime*0.002f)*0.35f+0.65f;
			    o->BlendMesh = 0;
			    o->BlendMeshLight = sine;
    			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0001f;
			    
                Luminosity = sine;
			    Vector ( Luminosity, Luminosity, Luminosity, Light );
			    AddTerrainLight ( o->Position[0], o->Position[1], Light, 3, PrimaryTerrainLight );
            }
            break;

        case 7:    //  ���.
            {
                //  ������Ʈ�� ȸ�� ���� ���� ������� Ÿ�̹��� �ٲ��.
                float   sine = (float)sinf((WorldTime+(o->Angle[2]*100))*0.002f)*0.35f+0.65f;

                o->BlendMesh = 0;
			    o->BlendMeshLight = sine;
			    
                Luminosity = sine;
			    Vector ( Luminosity, Luminosity*0.6f, Luminosity*0.2f, Light );
			    AddTerrainLight ( o->Position[0], o->Position[1], Light, 3, PrimaryTerrainLight );
            }
            break;

        case 11:    //  ���� �� ����.
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
            break;

        case 12:    //  �𷡴�.
			o->BlendMeshTexCoordU = -(int)WorldTime%50000 * 0.00005f;
			o->BlendMeshTexCoordV = -(int)WorldTime%50000 * 0.00005f;
            break;

        case 13:    //  �� ����.
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
			break;

        case 61:    //  ��Ϲ���.
            o->BlendMesh = 1;
			o->BlendMeshTexCoordV = -(int)WorldTime%1000 * 0.001f;

            Luminosity = (float)sinf(WorldTime*0.002f)*0.35f+0.65f;
			Vector ( Luminosity, Luminosity*0.6f, Luminosity*0.2f, Light );
			AddTerrainLight ( o->Position[0], o->Position[1], Light, 2, PrimaryTerrainLight );
            break;

        case 63:    //  ������.
        case 64:    //  �Ķ���.
            o->HiddenMesh = -2;
            break;

        case 65:    //  ���� ��Ϲ���.
        case 66:    //
            o->BlendMesh = 1;
			o->BlendMeshTexCoordV = -(int)WorldTime%1000 * 0.001f;

            Luminosity = (float)sinf(WorldTime*0.002f)*0.35f+0.65f;
			Vector ( Luminosity, Luminosity*0.6f, Luminosity*0.2f, Light );
			AddTerrainLight ( o->Position[0], o->Position[1], Light, 2, PrimaryTerrainLight );
            break;

        case 72:    //  ��� ����.
            o->BlendMesh = 0;
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
			break;

        case 73:    //  ��� ����2.
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
            break;

        case 75:    //  ��� ����3
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
            break;

        case 79:    //  ��� �帣��
			o->BlendMeshTexCoordV = -(int)WorldTime%10000 * 0.0002f;
            break;

        case 82:    //  �޺�.
            o->BlendMesh = 0;
			Vector ( 1.0f, 1.0f, 1.0f, o->Light );
            break;
        }
		break;

    case WD_10HEAVEN:
        break;

    case WD_11BLOODCASTLE1:
    case WD_11BLOODCASTLE1+1:
    case WD_11BLOODCASTLE1+2:
    case WD_11BLOODCASTLE1+3:
    case WD_11BLOODCASTLE1+4:
    case WD_11BLOODCASTLE1+5:
    case WD_11BLOODCASTLE1+6:
	case WD_52BLOODCASTLE_MASTER_LEVEL:
        switch ( o->Type )
        {
        case 9:
        case 10:
            if ( o->PKKey!=4 )
                o->HiddenMesh = -2;
            break;
        }
        break;
	case WD_55LOGINSCENE:
		{
			switch(o->Type)
			{
			case 84:
			case 85:
			case 87:
			case 89:
				o->HiddenMesh = -2;
				break;
			case 90:
			case 86: // �ҿ뵹��
				if(o->Type == 90)
				{
					o->Alpha = 1.0f;
					Vector(1.0f, 1.0f, 1.0f, o->Light);
					o->Angle[2] -= 0.23f;
				}
				else
				{
					o->Alpha = 0.2f;
					o->Angle[2] -= 0.6f;
					Vector(1.0f, 0.0f, 0.0f, o->Light);
				}

#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				float fTemp1 = sinf(WorldTime*0.001f)*0.2 + 0.6f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				o->BlendMesh = -2;
				break;
			}
			break;
		}
    default :
        if ( MoveHellasVisual( o )==true ) return;
        if ( battleCastle::MoveBattleCastleVisual( o )==true ) return;
		if( M31HuntingGround::MoveHuntingGroundObject(o) ) return;
#ifdef CRYINGWOLF_2NDMVP
		if( M34CryingWolf2nd::MoveCryingWolf2ndObject(o) ) return;
#endif // CRYINGWOLF_2NDMVP
		if( M33Aida::MoveAidaObject(o) ) return;
		if( M34CryWolf1st::MoveCryWolf1stObject(o) ) return;
		if (M37Kanturu1st::MoveKanturu1stObject(o))	// ĭ���� 1��.
			return;
		if(M38Kanturu2nd::Move_Kanturu2nd_Object(o)) return; // ĭ���� 2��
		if( M39Kanturu3rd::MoveKanturu3rdObject(o) ) return;
		if (SEASON3A::CGM3rdChangeUp::Instance().MoveObject(o)) return;
		if( g_CursedTemple->MoveObject(o)) return;
		if( SEASON3B::GMNewTown::MoveObject(o) ) return;
		if( SEASON3C::GMSwampOfQuiet::MoveObject(o) ) return;
#ifdef PSW_ADD_MAPSYSTEM
		if( TheMapProcess().MoveObject( o ) ) return;
#endif //PSW_ADD_MAPSYSTEM
        break;
    }
}


static  int visibleObject = 0;

//////////////////////////////////////////////////////////////////////////
//  MoveHeavenThunder
//  õ���� �ϴÿ� ������ ģ��.
//////////////////////////////////////////////////////////////////////////
int MoveHeavenThunder ( void )
{
    int     objectCount=0;
    float   Luminosity;
    vec3_t  Light;

    //  ����ģ��.
    if ( (rand()%50)==0 )
    {
        vec3_t  position, Angle;

        position[0] = Hero->Object.Position[0]+rand()%300-150.f;
        position[1] = Hero->Object.Position[1];
        position[2] = Hero->Object.Position[2]+rand()%300-150.f;

        Luminosity = (float)(rand()%4+4)*0.05f;
		Vector(Luminosity*0.3f,Luminosity*0.3f,Luminosity*0.081f,Light);
		AddTerrainLight(position[0],position[1],Light,2,PrimaryTerrainLight);
        Vector(0.f,0.f,0.f,Angle);
        CreateEffect(MODEL_CLOUD,Hero->Object.Position,Angle,Light);

        //  ������Ʈ�� �����Ѵ�.
        if( visibleObject )
        {
            objectCount = rand()%visibleObject;
        }

        //  Ŀ�ٶ� ����.
        if ( (rand()%5)==0 )
        {
			float Matrix1[3][4];
			float Matrix2[3][4];
            vec3_t  pos, position, position2, angle;
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			vec3_t vTempPos;
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS

            Vector(0.f,0.f,-45.f,angle);
			AngleMatrix(angle,Matrix1);
			
            switch( rand()%4 )
            {
            case 0:
                Vector(-400.f,-1000.f,0.f,position);
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorCopy(position, vTempPos);
				VectorRotate(vTempPos,Matrix1,position);
#else // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			    VectorRotate(position,Matrix1,position);
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorAdd(Hero->Object.Position,position,pos);

                Vector(0.f,0.f,240.f,angle);
			    AngleMatrix(angle,Matrix2);
			    Vector(-200.f,-1000.f,0.f,position);
                break;

            case 1:
			    Vector(-300.f,-400.f,0.f,position);
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorCopy(position, vTempPos);
				VectorRotate(vTempPos,Matrix1,position);
#else // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			    VectorRotate(position,Matrix1,position);
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorSubtract(Hero->Object.Position,position,pos);

                Vector(0.f,0.f,210.f,angle);
			    AngleMatrix(angle,Matrix2);
			    Vector(-500.f,-1000.f,0.f,position);
                break;

            case 2:
                Vector(-200.f,-400.f,0.f,position);
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorCopy(position, vTempPos);
				VectorRotate(vTempPos,Matrix1,position);
#else // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			    VectorRotate(position,Matrix1,position);
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorAdd(Hero->Object.Position,position,pos);

                Vector(0.f,0.f,235.f,angle);
			    AngleMatrix(angle,Matrix2);
			    Vector(-1000.f,-1500.f,0.f,position);
                break;

            case 3:
                Vector(-200.f,400.f,0.f,position);
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorCopy(position, vTempPos);
				VectorRotate(vTempPos,Matrix1,position);
#else // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			    VectorRotate(position,Matrix1,position);
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
				VectorAdd(Hero->Object.Position,position,pos);

                Vector(0.f,0.f,200.f,angle);
			    AngleMatrix(angle,Matrix2);
			    Vector(-600.f,-1200.f,0.f,position);
                break;
            }
#ifdef KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			VectorCopy(position, vTempPos);
			VectorRotate(vTempPos,Matrix2,position);
#else // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
			VectorRotate(position,Matrix2,position);
#endif // KJH_FIX_THUNDER_EFFECT_IN_IKARUS
            VectorSubtract(pos,position,position2);
			VectorAdd(pos,position,position);
            position[2] -= 300.f;
            position2[2] -= 300.f;
            angle[2] = 0;
            CreateJoint(BITMAP_JOINT_THUNDER+1,position,position2,angle,0,NULL,40.f+rand()%10);
            CreateJoint(BITMAP_JOINT_THUNDER+1,position,position2,angle,0,NULL,40.f+rand()%10);
        }
    }

    return objectCount;
}


//////////////////////////////////////////////////////////////////////////
//  �ʻ��� ��ü���� ȿ�� ����.
//////////////////////////////////////////////////////////////////////////
void MoveObjectSetting ( int& objCount )
{
    if ( MoveChaosCastleObjectSetting( objCount, visibleObject ) )                  return;     //  ī���� ĳ��.
    if ( MoveHellasObjectSetting( objCount, visibleObject ) )                       return;     //  ���.
    if ( battleCastle::MoveBattleCastleObjectSetting( objCount, visibleObject ) )   return;     //  ������.

    if( World==WD_10HEAVEN )
    {
        objCount = MoveHeavenThunder ();
    
        // ��� ȿ��
		if ( 0 == ( rand() % 10))
		{
			vec3_t Position;
			Vector ( Hero->Object.Position[0]+(float)(rand()%5000-2500),
				     Hero->Object.Position[1]+(float)(rand()%5000-2500),
				     Hero->Object.Position[2]-1000.f, Position );
			vec3_t Light = { 1.f, 1.f, 1.f};
			vec3_t Angle = { 0.f, 0.f, 0.f};
			CreateEffect ( BITMAP_LIGHT, Position, Angle, Light );
		}
        return;
    }
    else if ( InBloodCastle() == true )
    {
        vec3_t Position, Angle;
        vec3_t  Light;
        
        Vector ( 0.f, 0.f, 0.f, Angle );
        Vector ( 1.f, 1.f, 1.f, Light );

		Vector( Hero->Object.Position[0]+(float)(rand()%900-300),
			    Hero->Object.Position[1]+(float)(rand()%900-300),
			    Hero->Object.Position[2]+rand()%50+250.f, Position );

        if ( (rand()%4)==0 )
        {
            CreateParticle ( BITMAP_FLARE, Position, Angle, Light, 3, 0.19f, NULL );
        }
        return;
    }
}


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////

void    MoveObjectOnEffect ( OBJECT* o, int& objCount, int& visObject )
{
    vec3_t  Light;
    if ( World==WD_10HEAVEN )
    {
        visObject++;
        if ( objCount )
        {
            if( (rand()%10)==0 && o->Type>=0 && o->Type<=5 )
            {
                Vector(rand()%10/50.f,rand()%10/50.f,rand()%10/50.f,Light);
                CreateSprite(BITMAP_CLOUD+1,o->Position,0.5f,Light,&Hero->Object);
                CreateJoint(BITMAP_JOINT_THUNDER,o->Position,o->Position,o->Angle,6,o,rand()%20+10.f);
                CreateJoint(BITMAP_JOINT_THUNDER,o->Position,o->Position,o->Angle,6,o,rand()%20+10.f);
            }
            else
            {
                visObject--;
            }
        }
    }
    else
    {
        if ( MoveChaosCastleObject( o, objCount, visObject ) )  return;
        if ( battleCastle::MoveBattleCastleObject( o, objCount, visObject ) )   return;
    }
    
}


//////////////////////////////////////////////////////////////////////////
//  MoveObjects
//  �ʿ� �����ϴ� ������Ʈ ó��
//////////////////////////////////////////////////////////////////////////
void MoveObjects()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_MOVE_OBJECTS, PROFILING_MOVE_OBJECTS );
#endif // DO_PROFILING	
    int     objectCount = 0;

    //  �ʻ��� ��ü���� ȿ�� ����.
    MoveObjectSetting ( objectCount );

    //  ������Ʈ�� ó��.
    visibleObject = 0;
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			if(ob->Visible)
			{
				OBJECT *o  = ob->Head;
				while(1)
				{
					if(o != NULL) 
					{
						if(o->Live && o->Visible)
						{
							MoveObject(o);
                            //
                            MoveObjectOnEffect ( o, objectCount, visibleObject );
                            //  ������Ʈ ����.
                            ActionObject ( o );
						}
						if(o->Next == NULL) break;
						o = o->Next;
					}
					else break;
				}
			}
			else
			{
				OBJECT *o  = ob->Head;
				while(1)
				{
					if(o != NULL) 
					{
                        //  ������Ʈ ����.
                        if ( o->Live )
                        {
                            ActionObject ( o );
                        }
						o->Visible = false;
						if(o->Next == NULL) break;
						o = o->Next;
					}
					else break;
				}
			}
		}
	}
    g_iActionTime--;
#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_MOVE_OBJECTS );
#endif // DO_PROFILING	
}

///////////////////////////////////////////////////////////////////////////////
// ��� ������Ʈ �߿� �۵��Ǵ� ������Ʈ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void CreateOperate(OBJECT *Owner)
{
	for(int i=0;i<MAX_OPERATES;i++)
	{
		OPERATE *o = &Operates[i];
		if(!o->Live)
		{
			o->Live = true;
			o->Owner = Owner;
        	return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

OBJECT *CreateObject(int Type,vec3_t Position,vec3_t Angle,float Scale)
{
	int i = (int)(Position[0]/(16*TERRAIN_SCALE));
	int j = (int)(Position[1]/(16*TERRAIN_SCALE));
	if(i<0 || j<0 || i>=16 || j>=16) return NULL;

	BYTE Block = i*16+j;
	OBJECT_BLOCK *ob = &ObjectBlock[Block];
	OBJECT       *o  = new OBJECT;

	o->Initialize();

	if(ob->Head == NULL)
	{
		o->Prior = NULL;
		o->Next  = NULL;
		ob->Head = o;
		ob->Tail = o;
	}
	else
	{
		ob->Tail->Next = o;
		o->Prior       = ob->Tail;
		o->Next        = NULL;
		ob->Tail       = o;
	}
	o->Live                = true;
	o->Visible             = false;
	o->AlphaEnable         = false;
	o->LightEnable         = true;
	o->ContrastEnable      = false;
	o->EnableBoneMatrix    = false;

    o->m_bCollisionCheck   = false;

	o->Type                = Type;
	o->Scale               = Scale;
	o->Alpha               = 1.f;
	o->AlphaTarget         = 1.f;
	o->Velocity            = 0.16f;
	o->ShadowScale         = 50.f;
	o->HiddenMesh          = -1;
	o->CurrentAction       = 0;
	o->PriorAction         = 0;
	o->AnimationFrame      = 0.f;
	o->PriorAnimationFrame = 0.f;
	o->Block               = Block;
	o->BlendMesh           = -1;
	o->BlendMeshLight      = 1.f;
	o->BlendMeshTexCoordU  = 0.f;
	o->BlendMeshTexCoordV  = 0.f;
	g_CharacterClearBuff(o);
	o->CollisionRange      = -30.f;
	o->Timer               = 0.f;
#if defined PCROOM_EVENT
	o->m_bpcroom		   = FALSE;
#endif //PCROOM_EVENT
	o->m_bRenderAfterCharacter	=	false;
	
	VectorCopy(Position,o->Position);
	VectorCopy(Position,o->StartPosition);
	VectorCopy(Angle,o->Angle);
	Vector(0.f,0.f,0.f,o->Light);
	Vector(0.f,0.f,0.f,o->HeadAngle);
	Vector(0.f,0.f,0.f,o->Direction);
   	Vector(-40.f,-40.f,0.f ,o->BoundingBoxMin);
   	Vector( 40.f, 40.f,80.f,o->BoundingBoxMax);
	if(SceneFlag==LOG_IN_SCENE || SceneFlag==CHARACTER_SCENE)
	{
		switch(Type)
		{
		case MODEL_SHIP:
			o->Scale = 0.8f;
			Vector(0.2f,0.2f,0.2f,o->Light);
			o->LightEnable = true;
			break;
		case MODEL_WAVEBYSHIP:
			o->Scale = 0.8f;
			o->BlendMesh = 0;
			o->BlendMeshLight = 1.f;
			Vector(1.f,1.f,1.f,o->Light);
			break;
		case MODEL_MUGAME:
			o->Scale = 2.2f;
			o->BlendMesh = 1;
			o->LightEnable = false;
			break;
		case MODEL_LOGO:
			o->BlendMesh = 1;
			o->BlendMeshLight = 1.f;
			o->Scale = 5.f;
			o->Scale = 0.044f;
			Vector(1.f,1.f,1.f,o->Light);
			o->LightEnable = false;
			break;
		case MODEL_LOGOSUN:
			o->Scale = 3.f;
			o->BlendMesh = 0;
			Vector(0.5f,0.5f,0.5f,o->Light);
			break;
		case MODEL_LOGO+4:
			o->BlendMesh = 10;
			Vector(1.f,1.f,1.f,o->Light);
			break;
		case MODEL_DRAGON:
			o->HiddenMesh = -2;
			Vector(1.f,1.f,1.f,o->Light);
			CreateEffect(MODEL_DRAGON,o->Position,o->Angle, o->Light, 0, o, -1, 0, 0, 0, 1.6f);
			break;
		}
	}
	switch(World)
	{
	case WD_0LORENCIA:
		switch(Type)
		{
		case MODEL_BRIDGE:
			o->CollisionRange = -50.f;
			break;
		case MODEL_HOUSE01+2://smith
			o->BlendMesh = 4;
			break;
		case MODEL_HOUSE01+3:
			o->BlendMesh = 8;
			break;
		case MODEL_HOUSE01+4:
			o->BlendMesh = 2;
			break;
		case MODEL_HOUSE_WALL01+1:
			o->BlendMesh = 4;
			break;
		case MODEL_WATERSPOUT:
			o->BlendMesh = 3;
			break;
		case MODEL_BONFIRE:
			o->BlendMesh = 1;
			break;
		case MODEL_CARRIAGE01:
			o->BlendMesh = 2;
			break;
		case MODEL_TREE01:
		case MODEL_TREE01+1:
			//case MODEL_TREE01+10:
			Vector(-150.f,-150.f,0.f  ,o->BoundingBoxMin);
			Vector( 150.f, 150.f,500.f,o->BoundingBoxMax);
			o->Velocity = 1.f/o->Scale*0.4f;
			//o->AlphaEnable = true;
			break;
		case MODEL_STREET_LIGHT:
			o->BlendMesh = 1;
			o->Velocity = 0.3f;
			break;
		case MODEL_CANDLE:
			o->BlendMesh = 1;
			o->Velocity = 0.3f;
			break;
		case MODEL_TREASURE_CHEST:
			o->Velocity = 0.f;
			break;
		case MODEL_SIGN01:
		case MODEL_SIGN01+1:
			o->Velocity = 0.3f;
			//CreateNpc(o);
			break;
		case MODEL_POSE_BOX:
			CreateOperate(o);
			Vector( 40.f, 40.f,160.f,o->BoundingBoxMax);
			o->HiddenMesh = -2;
			break;
		case MODEL_TREE01+6:
		case MODEL_FURNITURE01+5:
		case MODEL_FURNITURE01+6:
			CreateOperate(o);
			break;
		}
		break;
	case WD_1DUNGEON:
		switch(Type)
		{
		case 59:
			CreateOperate(o);
			break;
		case 60:
			CreateOperate(o);
			Vector( 40.f, 40.f,160.f,o->BoundingBoxMax);
			o->HiddenMesh = -2;
			break;
		}
		break;
	case WD_2DEVIAS:
		switch(Type)
		{
#ifdef CSK_REPAIR_MAP_DEVIAS
		case MODEL_WARP:
			{
				vec3_t Position;
				Vector(o->Position[0], o->Position[1],o->Position[2]+360.f, Position);
				CreateEffect(MODEL_WARP, Position, o->Angle, o->Light, 1);
				
				Vector(o->Position[0], o->Position[1]+4.0f,o->Position[2]+360.f, Position);
				CreateEffect(MODEL_WARP2, Position, o->Angle, o->Light, 1);
				
				Vector(o->Position[0], o->Position[1]+20.0f,o->Position[2]+360.f, Position);
				CreateEffect(MODEL_WARP3, Position, o->Angle, o->Light, 1);
			}
			break;
#endif // CSK_REPAIR_MAP_DEVIAS
		case 22:
		case 25:
		case 40:
		case 45:
		case 55:
		case 73:
			CreateOperate(o);
			break;
		case 91:
			CreateOperate(o);
			Vector( 40.f, 40.f,160.f,o->BoundingBoxMax);
			o->HiddenMesh = -2;
			break;
		case 19:
		case 92:
		case 93:
			o->BlendMesh = 0;
			break;
		case 54:
		case 56:
			o->BlendMesh = 1;
			break;
		case 78:
			o->BlendMesh = 3;
			break;
		case 20:
		case 65:
		case 88:
		case 86:
		    o->Angle[2] = (float)((int)o->Angle[2]%360);
			VectorCopy(o->Angle,o->HeadAngle);
			VectorCopy(o->Position,o->HeadTargetAngle);
			break;
		case 100:
			o->HiddenMesh = -2;
			break;
		}
		break;
		case WD_3NORIA:
			switch(Type)
			{
			case MODEL_WARP:
				{
					vec3_t Position;
					Vector(o->Position[0], o->Position[1],o->Position[2]+350.f, Position);
					CreateEffect(MODEL_WARP, Position, o->Angle, o->Light);
					
					Vector(o->Position[0], o->Position[1]+4.0f,o->Position[2]+350.f, Position);
					CreateEffect(MODEL_WARP2, Position, o->Angle, o->Light);
					
					Vector(o->Position[0], o->Position[1]+8.0f,o->Position[2]+350.f, Position);
					CreateEffect(MODEL_WARP, Position, o->Angle, o->Light);
					
					Vector(o->Position[0], o->Position[1]+12.0f,o->Position[2]+350.f, Position);
					CreateEffect(MODEL_WARP2, Position, o->Angle, o->Light);
					
					Vector(o->Position[0], o->Position[1]+20.0f,o->Position[2]+350.f, Position);
					CreateEffect(MODEL_WARP3, Position, o->Angle, o->Light);
				}
			break;
		case 8:
			CreateOperate(o);
			break;
		case 1:
			o->BlendMesh = 1;
			break;
		case 9:
			o->BlendMesh = 3;
			break;
		case 38:
			CreateOperate(o);
			o->HiddenMesh = -2;
			break;
		case 17:
		case 37:
			o->BlendMesh = 0;
			break;
		case 19:
			o->BlendMesh = 0;
			break;
		case 18:
			o->BlendMesh = 2;
			break;
		}
		break;
	case WD_7ATLANSE:
		switch(Type)
		{
		case 39:
			CreateOperate(o);
			o->HiddenMesh = -2;
			break;
		}
		break;
	case WD_8TARKAN:
		switch(Type)
		{
		case 78:
			CreateOperate(o);
			//CreateJoint(BITMAP_JOINT_ENERGY,o->Position,o->Position,o->Angle,2,o,30.f);
			//CreateJoint(BITMAP_JOINT_ENERGY,o->Position,o->Position,o->Angle,3,o,30.f);
			break;
		}
		break;
	case WD_55LOGINSCENE:
		{
			switch(Type)
			{
			case 90:
			case 86:
				o->Position[0] = 8600.0f;
				o->Position[1] = 25000.0f;
				if(Type == 90)
				{
					o->Scale = 110.0f;
					o->Position[2] = 5000.0f;
				}
				else
				{
					o->Scale = 60.0f;
					o->Position[2] = 5000.0f;
				}
				Vector(0.0f, 0.0f, 0.0f, o->Angle);
				break;
			}
			break;
		}
    default :
        {
            if ( CreateChaosCastleObject( o )==true ) return o;     //  ī���� ĳ��.
            if ( CreateHellasObject( o )==true ) return o;          //  ���.
            battleCastle::CreateBattleCastleObject( o );
			M31HuntingGround::CreateHuntingGroundObject(o);			//. ���� �����
#ifdef CRYINGWOLF_2NDMVP
			M34CryingWolf2nd::CreateCryingWolf2ndObject(o);			//. ũ���̿��� ������
#endif // CRYINGWOLF_2NDMVP
			M33Aida::CreateAidaObject(o);							//  ���̴�
			M34CryWolf1st::CreateCryWolf1stObject(o);				//. ũ���̿��� ������
			M37Kanturu1st::CreateKanturu1stObject(o);				//. ĭ���� 1��
			M38Kanturu2nd::Create_Kanturu2nd_Object(o);				// ĭ���� 2��
			M39Kanturu3rd::CreateKanturu3rdObject(o);				//. ĭ���� 3��
			SEASON3A::CGM3rdChangeUp::Instance().CreateBalgasBarrackObject(o);
			SEASON3A::CGM3rdChangeUp::Instance().CreateBalgasRefugeObject(o);
			g_CursedTemple->CreateObject(o);
			SEASON3B::GMNewTown::CreateObject(o);
			SEASON3C::GMSwampOfQuiet::CreateObject(o);
#ifdef PSW_ADD_MAPSYSTEM
			TheMapProcess().CreateObject( o );
#endif //PSW_ADD_MAPSYSTEM
        }
        break;
    }
#if defined MR0 || defined OBJECT_ID
	if(o->m_iID == 0) o->m_iID = GenID();
#endif //MR0
	return o;
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ ����� �Լ�
///////////////////////////////////////////////////////////////////////////////

void DeleteObject(OBJECT *o,OBJECT_BLOCK *ob)
{
	if(o != NULL)
	{
		OBJECT *Next  = o->Next;
		OBJECT *Prior = o->Prior;
		if(Next != NULL) 
		{
			if(Prior != NULL)						  //o -> O -> o
			{
				Prior->Next = o->Next;
				Next->Prior = o->Prior;
			}
			else									 //O -> o
			{
				Next->Prior = NULL;
				ob->Head = Next;
			}
		}
		else
		{
			if(Prior != NULL)						  //o -> O
			{
				Prior->Next = NULL;
				ob->Tail = Prior;
			}
			else									  //O
			{
				ob->Head = NULL;
				ob->Tail = NULL;
			}
		}
		SAFE_DELETE( o );
	}
}
///////////////////////////////////////////////////////////////////////////////
// ��� ��� ������Ʈ�� Ÿ�Ժ��� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

//�� �ȿ��� Ÿ�Ժ��� ������Ʈ�� �����Ѵ�.
typedef std::vector<OBJECT* > ObjectPtrVec_t; 
typedef std::map<int, ObjectPtrVec_t> SortObj_t;
void SortInBlockByType()
{
	SortObj_t sortMap;
	for(int i = 0; i <16; ++i)
	{
		for(int j = 0; j < 16; ++j)
		{
			OBJECT_BLOCK* ob = &ObjectBlock[i*16+j];
			OBJECT* o = ob->Head;
			while(1)
			{
				if(o == NULL) break;
				sortMap[o->Type].push_back(o);			
				o = o->Next;
			}

			o = ob->Head;
			for(SortObj_t::iterator iter = sortMap.begin(); iter != sortMap.end(); ++iter)
			{
				ObjectPtrVec_t& rObjectVec = iter->second;
				for(ObjectPtrVec_t::iterator iter2 = rObjectVec.begin(); iter2 != rObjectVec.end(); ++iter2)
				{
					o = *iter2;
					o = o->Next;
				}
			}

			sortMap.clear();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ��� ������Ʈ ����� �Լ�
///////////////////////////////////////////////////////////////////////////////

void DeleteObjects()
{
	for(int i=MODEL_WORLD_OBJECT;i<MAX_WORLD_OBJECTS;i++)
	{
		Models[i].Release();
	}

#ifdef _VS2008PORTING
	for(int i=0;i<16;i++)
#else // _VS2008PORTING
	for(i=0;i<16;i++)
#endif // _VS2008PORTING
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT *o  = ob->Tail;
			while(1)
			{
				if(o != NULL) 
				{
					OBJECT *Temp = o->Prior;
					DeleteObject(o,ob);
					if(Temp == NULL) break;
					o = Temp;
				}
				else break;
			}
			ob->Head = NULL;
			ob->Tail = NULL;
		}
	}

#ifdef _VS2008PORTING
	for(int i=BITMAP_MAPTILE;i<=BITMAP_RAIN_CIRCLE;i++)
#else // _VS2008PORTING
	for(i=BITMAP_MAPTILE;i<=BITMAP_RAIN_CIRCLE;i++)
#endif // _VS2008PORTING
	{
     	DeleteBitmap(i);
	}

#ifdef _VS2008PORTING
	for(int i=0;i<MAX_SPRITES;i++)
		Sprites[i].Live = false;
	for(int i=0;i<MAX_BOIDS;i++)
		Boids[i].Live = false;
	for(int i=0;i<MAX_FISHS;i++)
		Fishs[i].Live = false;
	for(int i=0;i<MAX_LEAVES;i++)
		Leaves[i].Live = false;
	for(int i=0;i<MAX_PARTICLES;i++)
		Particles[i].Live = false;
	for(int i=0;i<MAX_POINTS;i++)
		Points[i].Live = false;
	for(int i=0;i<MAX_JOINTS;i++)
		Joints[i].Live = false;
	for(int i=0;i<MAX_OPERATES;i++)
		Operates[i].Live = false;
	for(int i=0;i<MAX_EFFECTS;i++)
		Effects[i].Live = false;
#else // _VS2008PORTING
	for(i=0;i<MAX_SPRITES;i++)
		Sprites[i].Live = false;
	for(i=0;i<MAX_BOIDS;i++)
		Boids[i].Live = false;
	for(i=0;i<MAX_FISHS;i++)
		Fishs[i].Live = false;
	for(i=0;i<MAX_LEAVES;i++)
		Leaves[i].Live = false;
	for(i=0;i<MAX_PARTICLES;i++)
		Particles[i].Live = false;
	for(i=0;i<MAX_POINTS;i++)
		Points[i].Live = false;
	for(i=0;i<MAX_JOINTS;i++)
		Joints[i].Live = false;
	for(i=0;i<MAX_OPERATES;i++)
		Operates[i].Live = false;
	for(i=0;i<MAX_EFFECTS;i++)
		Effects[i].Live = false;
#endif // _VS2008PORTING

}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ Ÿ�� ������ ����� �Լ�
///////////////////////////////////////////////////////////////////////////////

void DeleteObjectTile(int x,int y)
{
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL && o != (OBJECT *)0xdddddddd) 
				{
					if(o->Live && (int)(o->Position[0]/TERRAIN_SCALE)==x && (int)(o->Position[1]/TERRAIN_SCALE)==y)
    					DeleteObject(o,ob);
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

int OpenObjects(char *FileName)
{
    FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s file not found.",FileName);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return ( -1);
	}
	fseek(fp,0,SEEK_END);
	int EncBytes = ftell(fp);
	fseek(fp,0,SEEK_SET);
    unsigned char *EncData = new unsigned char[EncBytes];
	fread(EncData,1,EncBytes,fp);
	fclose(fp);

	unsigned char *Data = EncData;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int DataBytes = EncBytes;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

	int DataPtr = 0;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	DataPtr+=1;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	BYTE Version = *((BYTE *)(Data+DataPtr));DataPtr+=1;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int iMapNumber = 0;
	short Count = *((short *)(Data+DataPtr));DataPtr+=2;
	for(int i=0;i<Count;i++)
	{
		vec3_t Position;
		vec3_t Angle;
     	short Type = *((short *)(Data+DataPtr));DataPtr+=2;
       	memcpy(Position,Data+DataPtr,sizeof(vec3_t));DataPtr+=sizeof(vec3_t);
       	memcpy(Angle   ,Data+DataPtr,sizeof(vec3_t));DataPtr+=sizeof(vec3_t);
     	float Scale = *((float *)(Data+DataPtr));DataPtr+=4;
		CreateObject(Type,Position,Angle,Scale);
	}
	delete [] Data;

//Object Ÿ������ �������Ǵ� �͵��� ID�� �̸� ����
#if defined MR0 || defined OBJECT_ID
	SortInBlockByType();

	for(i=0;i<MAX_SPRITES;i++)
		Sprites[i].m_iID = GenID();
	for(i=0;i<MAX_BOIDS;i++)
		Boids[i].m_iID = GenID();
	for(i=0;i<MAX_FISHS;i++)
		Fishs[i].m_iID = GenID();
	for(i=0;i<MAX_EFFECTS;i++)
		Effects[i].m_iID = GenID();

#endif //MR0

	fclose(fp);
    return iMapNumber;
}

int OpenObjectsEnc(char *FileName)
{
    FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s file not found.",FileName);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return ( -1);
	}
	fseek(fp,0,SEEK_END);
	int EncBytes = ftell(fp);
	fseek(fp,0,SEEK_SET);
    unsigned char *EncData = new unsigned char[EncBytes];
	fread(EncData,1,EncBytes,fp);
	fclose(fp);

	// ��ȣȭ �� �� Ǯ��
	int DataBytes = MapFileDecrypt( NULL, EncData, EncBytes);	//
	unsigned char *Data = new unsigned char[DataBytes];		//
	MapFileDecrypt( Data, EncData, EncBytes);	//
	delete [] EncData;		//

	int DataPtr = 0;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	DataPtr+=1;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	BYTE Version = *((BYTE *)(Data+DataPtr));DataPtr+=1;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int iMapNumber = ( int)*((BYTE *)(Data+DataPtr));DataPtr+=1;
	short Count = *((short *)(Data+DataPtr));DataPtr+=2;
    g_iTotalObj = Count;
	for(int i=0;i<Count;i++)
	{
		vec3_t Position;
		vec3_t Angle;
     	short Type = *((short *)(Data+DataPtr));DataPtr+=2;
       	memcpy(Position,Data+DataPtr,sizeof(vec3_t));DataPtr+=sizeof(vec3_t);
       	memcpy(Angle   ,Data+DataPtr,sizeof(vec3_t));DataPtr+=sizeof(vec3_t);
     	float Scale = *((float *)(Data+DataPtr));DataPtr+=4;
		CreateObject(Type,Position,Angle,Scale);
	}
	delete [] Data;

//Object Ÿ������ �������Ǵ� �͵��� ID�� �̸� ����
#if defined MR0 || defined OBJECT_ID
	SortInBlockByType();

	for(i=0;i<MAX_SPRITES;i++)
		Sprites[i].m_iID = GenID();
	for(i=0;i<MAX_BOIDS;i++)
		Boids[i].m_iID = GenID();
	for(i=0;i<MAX_FISHS;i++)
		Fishs[i].m_iID = GenID();
	for(i=0;i<MAX_EFFECTS;i++)
		Effects[i].m_iID = GenID();

#endif //MR0

	fclose(fp);
    return iMapNumber;
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������Ʈ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

bool SaveObjects(char *FileName, int iMapNumber)
{
	FILE *fp = fopen(FileName,"wb");
	
	short ObjectCount = 0;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	int CounterPoint = 3;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	BYTE Version = 0;
    fwrite(&Version,sizeof(BYTE),1,fp);
	fwrite(&iMapNumber,1,1,fp);
	fseek(fp,4,SEEK_SET);
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if(o->Live)
					{
						fwrite(&o->Type   ,2             ,1,fp);
						fwrite(o->Position,sizeof(vec3_t),1,fp);
						fwrite(o->Angle   ,sizeof(vec3_t),1,fp);
						fwrite(&o->Scale  ,sizeof(float ),1,fp);
					}
    				ObjectCount++;
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}
	int EndPoint = ftell(fp);
	fseek(fp,2,SEEK_SET);
	fwrite(&ObjectCount,2,1,fp);
	fseek(fp,EndPoint,SEEK_SET);

	fclose(fp);

	// ��ȣȭ
	{
		fp = fopen(FileName,"rb");
		fseek(fp,0,SEEK_END);
		int EncBytes = ftell(fp);	//
		fseek(fp,0,SEEK_SET);
		unsigned char *EncData = new unsigned char[EncBytes];	//
		fread(EncData,1,EncBytes,fp);	//
		fclose(fp);

		// ��ȣȭ ��Ű��
		int DataBytes = MapFileEncrypt( NULL, EncData, EncBytes);	//
		unsigned char *Data = new unsigned char[DataBytes];		//
		MapFileEncrypt( Data, EncData, EncBytes);	//
		delete [] EncData;		//

		// ��ȣȭ ����
		fp = fopen(FileName,"wb");
		fwrite( Data, DataBytes, 1, fp);
		fclose( fp);
		delete [] Data;
	}
    return true;
}

void SaveTrapObjects(char *FileName)
{
	FILE *fp = fopen(FileName,"wt");
    fprintf(fp,"0\n");
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if((World==WD_1DUNGEON && (o->Type==39||o->Type==40||o->Type==51)) ||
						(World==WD_4LOSTTOWER && (o->Type==25)))
					{
						int Type = 0;
						switch(o->Type)
						{
						case 39:Type = 100;break;
						case 40:Type = 101;break;
						case 51:Type = 102;break;
						case 25:Type = 103;break;
						}
						fprintf(fp,"%4d %4d 0 %4d %4d %4d\n",Type,World,(BYTE)(o->Position[0]/TERRAIN_SCALE),(BYTE)(o->Position[1]/TERRAIN_SCALE),(BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8);
					}
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}
    fprintf(fp,"end\n");
	fclose(fp);
}


//////////////////////////////////////////////////////////////////////////
//  �������� ǥ���Ѵ�.
//////////////////////////////////////////////////////////////////////////
OBJECT  g_CloudsLow;
void    RenderCloudLowLevel ( int index, int Type )
{
	OBJECT* o = &g_CloudsLow;

    o->Alpha = 1.f;
	o->Live  = true;
	o->Type  = Type;
	o->SubType = 0;
	o->Scale = 10.f;
	
    if(o->LifeTime!=10)
    {
        Vector(0.f,0.f,0.f,o->StartPosition);
        Vector(0.f,0.f,0.f,o->Position);
    }
    o->LifeTime = 10;

	Vector(0.f,0.f,0.f,o->Angle);
	Vector(0.f,0.f,0.f,o->HeadAngle);
	Vector(0.f,0.f,0.f,o->HeadTargetAngle);

    o->EnableBoneMatrix  = false;
	o->CurrentAction     = 0;
    o->PriorAction       = 0;
	o->AnimationFrame    = 1.f;
	o->PriorAnimationFrame = 1.f;

    o->BlendMeshLight    = 1.f;
    o->LightEnable       = true;

    o->HiddenMesh = -1;


    if( index!=0 )
    {
        //  ������ �帣�� ������ �����Ѵ�.
        vec3_t  delPosition;

        //  �Ÿ� ���� ���Ѵ�.
        delPosition[0] = ( Hero->Object.Position[0] - o->Position[0] );
        delPosition[1] = ( Hero->Object.Position[1] - o->Position[1] );
        delPosition[2] = 0.f;

        //  ȸ���� ��Ų��.
		float Matrix[3][4];
        vec3_t angle;

        Vector(0.f,0.f,-45.f,angle);
		AngleMatrix(angle,Matrix);
		VectorRotate(delPosition,Matrix,delPosition);
/*
        if ( delPosition[0]!=0 && delPosition[1]!=0 && delPosition[0]>-200 && delPosition[0]<200 && delPosition[1]>-200 && delPosition[1]<200 )
        {
            if(index==1)
            {
                o->StartPosition[0] += (delPosition[0])/1000.f;
                o->StartPosition[1] += (-delPosition[1])/1000.f;
            }
            else
            {
                o->StartPosition[0] -= (delPosition[0])/1000.f;
                o->StartPosition[1] -= (-delPosition[1])/1000.f;
            }
        }
*/

        if(index==1)
        {
            o->StartPosition[0] -= sinf(WorldTime*0.0002f)*0.001f;//0.001f;
            o->StartPosition[1] += cosf(WorldTime*0.0002f)*0.001f;//0.001f;
        }
        else
        {
            o->StartPosition[0] += sinf(WorldTime*0.0002f)*0.001f;//0.001f;
            o->StartPosition[1] -= cosf(WorldTime*0.0002f)*0.001f;//0.001f;
        }

        if(index==1)
        {
            o->BlendMesh = -1;
        }
        else
        {
            o->BlendMeshLight = 1.f;
            o->BlendMesh = 0;
        }
	    o->BlendMeshTexCoordU = o->StartPosition[0];
        o->BlendMeshTexCoordV = o->StartPosition[1];
        Vector(Hero->Object.Position[0], Hero->Object.Position[1], Hero->Object.Position[2]-150.f+(index*20), o->Position );

        RenderObject(o);
    }
}

///////////////////////////////////////////////////////////////////////////////
// ������ ��� ������ ����� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ClearItems()
{
	for(int i=0;i<MAX_ITEMS;i++)
	{
		OBJECT *o = &Items[i].Object;
		o->Live = false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ �Ӽ� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ItemObjectAttribute(OBJECT *o)
{
	Vector(0.3f,0.3f,0.3f,o->Light);
   	o->LightEnable = true;
	o->AlphaEnable    = false;
	o->EnableShadow   = false;
	o->Velocity	      = 0.f;
	o->CollisionRange = 50.f;
	o->PriorAnimationFrame = 0.f;
	o->AnimationFrame = 0.f;
	o->PriorAction    = 0;
	o->CurrentAction  = 0;
	o->HiddenMesh     = -1;
	o->Gravity        = 0.f;
	o->Alpha          = 1.f;
	o->BlendMesh      = -1;
	o->BlendMeshLight = 1.f;
	o->BlendMeshTexCoordU = 0.f;
	o->BlendMeshTexCoordV = 0.f;
	o->HiddenMesh     = -1;
	o->Scale          = 0.8f;
	g_CharacterClearBuff(o);
	if(o->Type>=MODEL_SPEAR && o->Type<=MODEL_STAFF+13)
		o->Scale = 0.7f;
	switch(o->Type)
	{
	case MODEL_BOW+16://
		o->BlendMesh = -2;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.2f+0.9f;
		break;
	case MODEL_STAFF+8://
		o->BlendMesh = -2;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.2f+0.9f;
    	//o->BlendMeshTexCoordU = (float)((int)(WorldTime)%2000)*0.0005f;
		break;
	case MODEL_STAFF+7://����������
		o->BlendMesh = 1;
		o->BlendMeshLight = (float)(rand()%11)*0.1f;
		break;
	case MODEL_STAFF+6://��Ȱ��������
		o->BlendMesh = -2;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	case MODEL_BOW+6://�ְ�Ȱ
	case MODEL_BOW+13://
	case MODEL_BOW+14://
		o->BlendMesh = -2;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
    case MODEL_PANTS+24 :   //. ���� �߰�����
    case MODEL_HELM+24 :    //. ���� �߰����
        o->BlendMeshLight = sinf( WorldTime*0.001f )*0.4f+0.6f;
		break;
	case MODEL_STAFF+11:
        o->BlendMesh = 2;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	case MODEL_MACE+4://
		o->BlendMesh = 1;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.2f+0.8f;
		break;
	case MODEL_MACE+5://
		o->BlendMesh = 0;
		break;
	case MODEL_MACE+6://�巡�ﵵ��
		o->BlendMesh = 1;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	case MODEL_SPEAR+9://��
    	o->BlendMeshTexCoordV = -(float)((int)(WorldTime)%2000)*0.0005f;
		break;
	case MODEL_SHIELD+14://����
		o->BlendMesh = 1;
		o->BlendMeshTexCoordU = (float)(rand()%10)*0.1f;
		o->BlendMeshTexCoordV = (float)(rand()%10)*0.1f;
		break;
	case MODEL_SHIELD+16:
		o->HiddenMesh = 2;
		break;
	case MODEL_MACE+7:
		o->HiddenMesh = 2;
		break;
	case MODEL_SWORD+31:
		o->HiddenMesh = 2;
		break;
	case MODEL_SPEAR+10:
		o->HiddenMesh = 1;
		break;
	case MODEL_STAFF+9:
		o->BlendMesh = 1;
		break;
	case MODEL_STAFF+5://����
		o->BlendMesh = 2;
		o->BlendMeshTexCoordU = (float)(rand()%10)*0.1f;
		o->BlendMeshTexCoordV = (float)(rand()%10)*0.1f;
		break;
	case MODEL_ETC:
     	o->Scale = 0.7f;
		break;
	case MODEL_POTION+1:
     	o->Scale = 1.f;
		break;
    case MODEL_POTION+21:
        o->Scale = 0.5f;
        break;
#ifdef _PVP_MURDERER_HERO_ITEM
    case MODEL_POTION+30:
        o->Scale = 0.5f;
        break;
#endif	// _PVP_MURDERER_HERO_ITEM
	case MODEL_SWORD+14:
		o->BlendMesh = 1;
		o->BlendMeshTexCoordU = (float)(rand()%10)*0.1f;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	case MODEL_SWORD+10:
    case MODEL_SPEAR:
		o->BlendMesh = 1;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	case MODEL_SWORD+5:
	case MODEL_SWORD+13:
		o->BlendMesh = 1;
		break;
	case MODEL_STAFF:
		o->BlendMesh = 2;
		break;
	case MODEL_HELPER:
		o->BlendMesh = 1;
		break;
    case MODEL_WING+3:
        o->Scale = 0.5f;
		o->BlendMesh = 0;
    case MODEL_WING+4:
    case MODEL_WING+5:
    case MODEL_WING+6:
        break;
	case MODEL_WING:
	case MODEL_WING+8:
	case MODEL_WING+9:
	case MODEL_WING+10:
	case MODEL_WING+11:
	case MODEL_WING+20:
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING
	case MODEL_WING+132:
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
		o->BlendMesh = 0;
		break;
	case MODEL_SHIELD+11:
	case MODEL_SHIELD+12:
	case MODEL_SHIELD+13:
		o->BlendMesh = 1;
		o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ���� ������ ���� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ItemAngle(OBJECT *o)
{
	Vector(0.f,0.f,-45.f,o->Angle);

	if(o->Type>=MODEL_SWORD && o->Type<MODEL_AXE+MAX_ITEM_INDEX)
	{
		o->Angle[0] = 60.f;
		if(o->Type == MODEL_SWORD+19)
			o->Scale = 0.7f;
	}
	else if(o->Type == MODEL_BOW+20 || o->Type == MODEL_BOW+21 || o->Type == MODEL_BOW+22)
	{
		o->Angle[0] = 0.f;
		o->Angle[1] = 0.f;
	}
	else if((o->Type>=MODEL_BOW+8  && o->Type<MODEL_BOW+17) || 
		    (o->Type>=MODEL_BOW+18 && o->Type<MODEL_BOW+20))  //  ����.
	{
		o->Angle[0] = 90.f;
		o->Angle[1] = 0.f;
	}
	else if(o->Type>=MODEL_MACE && o->Type<MODEL_STAFF+MAX_ITEM_INDEX)
	{
		o->Angle[0] = 0.f;
		o->Angle[1] = 270.f;
	}
	else if(o->Type>=MODEL_SHIELD && o->Type<MODEL_SHIELD+MAX_ITEM_INDEX)
	{
		o->Angle[1] = 270.f;
		o->Angle[2] = 270.f - 45.f;
	}
	else if(MODEL_HELM+39 <= o->Type && MODEL_HELM+44 >= o->Type)
	{
		o->Scale = 1.5f;
		o->Angle[2] = 45.f;
	}
	else if(o->Type>=MODEL_ARMOR && o->Type<MODEL_GLOVES+MAX_ITEM_INDEX
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| o->Type == MODEL_POTION+155	// źŻ�ν��� ����
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
		o->Angle[0] = 270.f;
	else if ( o->Type>=MODEL_WING+32 && o->Type<=MODEL_WING+34)
	{
		o->Scale = 0.3f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if (o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ� 
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.6f;
	}
	else if (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.6f;
	}
	else if (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129)	// �õ彺�Ǿ�
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.6f;
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(o->Type == MODEL_WING+49)
	{
		o->Angle[0] = 270.0f;
		o->Angle[1] = 180.0f;
		o->Angle[2] = 45.0f;
        o->Scale    = 0.7f;
    }
	else if(o->Type == MODEL_WING+50)
	{
		o->Angle[0] = 250.0f;
		o->Angle[1] = 180.0f;
		o->Angle[2] = 45.0f;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef HELLOWIN_EVENT
	else if ( o->Type==MODEL_POTION+45)
	{
		o->Scale = 0.9f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
	else if ( o->Type>=MODEL_POTION+46 && o->Type<=MODEL_POTION+48)
	{
		o->Scale = 0.7f;
		o->Angle[0] = 90.f;
	}
	else if ( o->Type==MODEL_POTION+49)
	{
		o->Scale = 0.9f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
	else if ( o->Type==MODEL_POTION+50)
	{
		o->Scale = 0.26f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	else if ( o->Type>=MODEL_POTION+32 && o->Type<=MODEL_POTION+34)
	{
		o->Scale = 0.7f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
	else if ( o->Type>=MODEL_EVENT+21 && o->Type<=MODEL_EVENT+23)
	{
		o->Scale = 0.7f;
		o->Angle[0] = 0.f;
		o->Angle[2] = 90.f;
	}
#endif //GIFT_BOX_EVENT
#ifdef CSK_FREE_TICKET
	// ����������� ���� ���� �� ������ �����ϰ� ����
	else if(o->Type >= MODEL_HELPER+46 && o->Type <= MODEL_HELPER+48)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
	// ī����ī�� ���� ���� �� ������ �����ϰ� ����
	else if(o->Type == MODEL_POTION+54)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
	// ���� ���� �� ������ �����ϰ� ����
	else if(o->Type == MODEL_POTION+58)
	{
		o->Scale = 0.3f;
		o->Angle[2] = 90.f;
	}
	else if(o->Type == MODEL_POTION+59 || o->Type == MODEL_POTION+60)
	{
		o->Scale = 0.3f;
		o->Angle[0] = 90.f;
		o->Angle[1] = 90.f;
	}
	else if(o->Type == MODEL_POTION+61 || o->Type == MODEL_POTION+62)
	{
		o->Scale = 0.3f;
		o->Angle[0] = 90.f;
	}
#endif // CSK_RARE_ITEM
#ifdef CSK_LUCKY_CHARM
	else if( o->Type == MODEL_POTION+53 )// ����� ����
	{
		o->Scale = 0.2f;
		o->Angle[2] = 90.f;
	}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
	else if( o->Type == MODEL_HELPER+43 || o->Type == MODEL_HELPER+44 || o->Type == MODEL_HELPER+45 )
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif //CSK_LUCKY_SEAL
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	else if( o->Type >= MODEL_POTION+70 && o->Type <= MODEL_POTION+71 )
	{
		o->Scale = 0.6f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	else if( o->Type >= MODEL_POTION+72 && o->Type <= MODEL_POTION+77 )
	{
		o->Scale = 0.5f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
	else if( o->Type == MODEL_HELPER+59 )
	{
		o->Scale = 0.2f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
	else if( o->Type >= MODEL_HELPER+54 && o->Type <= MODEL_HELPER+58 )
	{
		o->Scale = 0.7f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	else if( o->Type >= MODEL_POTION+78 && o->Type <= MODEL_POTION+82 )
	{
		o->Scale = 0.5f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	else if( o->Type == MODEL_HELPER+60 )
	{
		o->Scale = 1.5f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_INDULGENCE_ITEM
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	else if( o->Type == MODEL_HELPER+61 )
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
	else if( o->Type == MODEL_POTION+83)
	{
		o->Scale = 0.3f;
		o->Angle[0] = 90.f;
	}
#endif //PSW_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	else if(o->Type >= MODEL_POTION+145 && o->Type <= MODEL_POTION+150)
	{
		o->Scale = 0.3f;
		o->Angle[0] = 90.f;
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ���ð���, �ٸ�ī, �ٸ�ī ��7�� ���������
	else if(o->Type >= MODEL_HELPER+125 && o->Type <= MODEL_HELPER+127)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH

#ifdef PSW_CHARACTER_CARD
	// ī����ī�� ���� ���� �� ������ �����ϰ� ����
	else if(o->Type == MODEL_POTION+91)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
	// ī����ī�� ���� ���� �� ������ �����ϰ� ����
	else if(o->Type == MODEL_POTION+92)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
	else if(o->Type == MODEL_POTION+93)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
	else if(o->Type == MODEL_POTION+95) // ī����ī�� �̴�
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
	else if( o->Type == MODEL_POTION+94 ) // ����Ʈ �߰� ġ�� ����
	{
		o->Scale = 0.6f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
	else if( o->Type == MODEL_POTION+84 )  // ���ɻ���
	{
		o->Scale = 0.8f;
		o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+85 )  // ���ɼ�
	{
		o->Scale = 0.9f;
		o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+86 )  // ���ɰ��
	{
		o->Scale = 0.7f;
		o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+87 )  // ������
	{
		o->Scale = 1.3f;
		o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+88 )  // ��� ����
	{
		o->Scale = 0.7f;
		o->Angle[0] = 180.f;
		o->Angle[1] = 180.f;
		//o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+89 )  // ������ ����
	{
		o->Scale = 0.7f;
		o->Angle[0] = 30.f;
		o->Angle[2] = 90.f;
	}
	else if( o->Type == MODEL_POTION+90 )  // ����� ����
	{
		o->Scale = 0.7f;
		o->Angle[0] = 30.f;
		o->Angle[2] = 90.f;
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
	else if(o->Type >= MODEL_HELPER+62 && o->Type <= MODEL_HELPER+63)
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
	else if(o->Type >= MODEL_POTION+97 && o->Type <= MODEL_POTION+98)
	{
		o->Scale = 0.5f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef YDG_ADD_HEALING_SCROLL
	else if(o->Type == MODEL_POTION+140)	// ġ���� ��ũ��
	{
		o->Scale = 0.5f;
		o->Angle[2] = 90.f;
	}
#endif	// YDG_ADD_HEALING_SCROLL
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	else if( o->Type == MODEL_POTION+96 ) 
	{
		o->Scale = 0.2f;
		o->Angle[2] = 90.f;
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
	else if( o->Type >= MODEL_HELPER+64 && o->Type <= MODEL_HELPER+65 )
	{
#ifdef LDK_MOD_GUARDIAN_DROP_RESIZE
		switch(o->Type)
		{
		case MODEL_HELPER+64: o->Scale = 0.21f; break;
		case MODEL_HELPER+65: o->Scale = 0.5f; break;
		}
#else //LDK_MOD_GUARDIAN_DROP_RESIZE
		o->Scale = 1.4f;
#endif //LDK_MOD_GUARDIAN_DROP_RESIZE
		o->Angle[2] = 70.f;
	}
#endif //LDK_ADD_PC4_GUARDIAN		
#ifdef CSK_PCROOM_ITEM
	else if(o->Type >= MODEL_POTION+55 && o->Type <= MODEL_POTION+57
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| o->Type >= MODEL_POTION+157 && o->Type <= MODEL_POTION+159
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.3f;
	}
#endif // CSK_PCROOM_ITEM
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	else if(o->Type == MODEL_HELPER+96)
	{
		o->Angle[0] = 90.f;
		o->Angle[1] = 0.f;
		o->Angle[2] = 0.f;
		o->Scale = 1.0f;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH	
	else if(o->Type == MODEL_HELPER+49)
	{
		o->Angle[0] = 90.f;
		o->Angle[1] = 0.f;
		o->Scale = 0.3f;
	}
	else if(o->Type == MODEL_HELPER+50)
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.6f;
	}
	else if(o->Type == MODEL_HELPER+51)
	{
		o->Angle[0] = 90.f;
		o->Scale = 0.45f;
	}
	else if(o->Type == MODEL_POTION+64
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| o->Type == MODEL_POTION+153
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
	{
		o->Angle[0] = 0.f;
		o->Scale = 0.8f;
	}
	else if(o->Type == MODEL_HELPER+52)
	{
		o->Angle[0] = 0.f;
		o->Scale = 1.2f;
	}
	else if(o->Type == MODEL_HELPER+53)
	{
		o->Angle[0] = 0.f;
		o->Scale = 1.2f;
	}
	else if(o->Type == MODEL_POTION+65)
	{
		o->Angle[0] = 90.f;
		o->Scale = 0.6f;
	}
	else if(o->Type == MODEL_POTION+66)
	{
		o->Angle[0] = 90.f;
		o->Scale = 0.8f;
	}
	else if(o->Type == MODEL_POTION+67)
	{
		o->Angle[0] = 270.f;
		o->Scale = 0.8f;
	}
	else if (o->Type == MODEL_POTION+68)
	{
		o->Angle[2] = -135.f;
		o->Scale = 0.6f;
	}
	else if(o->Type==MODEL_EVENT+4)	// ��ź�Ǻ�
	{
		o->Angle[0] = 90.f;
	}
	else if(o->Type==MODEL_EVENT+8 || o->Type==MODEL_EVENT+9)	// �� ����, �� ����
	{
		o->Angle[0] = 270.f;
		o->Angle[2] = 45.f;
	}
#ifdef USE_EVENT_ELDORADO
	else if(o->Type==MODEL_EVENT+10)	// ������
	{
		o->Scale    = .2f;
	}
#endif
	else if(o->Type==MODEL_EVENT+5)	// ����. ���� �ָӴ�
	{
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
        o->Angle[0] = 0.f;
        o->Angle[2] = 45.f;
        o->Scale    = 1.1f;
#else
		o->Angle[0] = 90.f;
#endif
	}
#ifdef CHINA_MOON_CAKE
    else if ( o->Type==MODEL_EVENT+17 )     //  �߱� ����.
    {
		o->Angle[0] = 270.f;
		o->Angle[2] = 45.f;
    }
#endif// CHINA_MOON_CAKE
    else if ( o->Type==MODEL_POTION+23 )//  �����Ǽ�.
    {
        o->Angle[1] = 45.f;
        o->Angle[2] = 45.f;
    }
    else if ( o->Type==MODEL_POTION+24 )//  �η�����.
    {
        o->Angle[2] = 45.f;
    }
    else if ( ( o->Type>=MODEL_POTION+25 && o->Type<MODEL_POTION+27) || o->Type == MODEL_HELPER+14) //  �����Ǵ���, ��������ȥ. ��ũ�Ǳ���.
    {
        o->Angle[2] = 45.f;
    }
	else if(o->Type==MODEL_POTION+17)	// �Ǹ��� ��
	{
		o->Angle[0] = 90.f;
	}
	else if(o->Type==MODEL_POTION+63)	// ����
	{
		o->Angle[0] = 70.f;
		o->Scale = 1.5f;
	}
#ifdef YDG_ADD_FIRECRACKER_ITEM
	else if(o->Type==MODEL_POTION+99)	// ũ�������� ����
	{
		o->Angle[0] = 70.f;
		o->Angle[2] = 0.f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_FIRECRACKER_ITEM
	else if(o->Type==MODEL_POTION+52)	// GM ��������
	{
		o->Angle[2] = -10.f;
		o->Scale = 0.4f;
	}
	else if(o->Type==MODEL_POTION+18)	// �Ǹ��� ����
	{
		o->Angle[0] = o->Angle[2] = 270.f;
	}
	else if(o->Type==MODEL_POTION+19)	// �Ǹ��� ���� �ʴ��
	{
		o->Angle[0] = 270.f;
		o->Angle[2] = 90.f;
	}
#ifdef _PVP_MURDERER_HERO_ITEM
    else if(o->Type==MODEL_POTION+30)	// �Ӹ�ī��
	{
		o->Angle[0] = 90.f;
		o->Angle[2] = 70.f;
	}
#endif	// _PVP_MURDERER_HERO_ITEM
	else if(o->Type == MODEL_POTION+29)	//. ����� ǥ��
	{
		o->Angle[0] = 90.f;
		o->Angle[2] = 70.f;
	}
#ifdef MYSTERY_BEAD
	else if(o->Type == MODEL_EVENT+19)	//. �ź��� ����
	{
		o->Scale = 0.7f;
	}
#endif // MYSTERY_BEAD
	else if(o->Type == MODEL_EVENT+11)	//. ����
	{
		o->Angle[0] = 115.f;
		o->Angle[1] = 75.f;
		o->Angle[2] = 8.f;
		o->Scale = 0.4f;
	}
#ifdef MYSTERY_BEAD
	else if(o->Type == MODEL_EVENT+20)	//. ������
	{
		o->Angle[0] = 15.f;
		o->Angle[1] = 75.f;
		o->Angle[2] = 98.f;
		o->Scale = 0.68f;
	}
#endif // MYSTERY_BEAD
	else if(o->Type == MODEL_HELPER+16 || o->Type == MODEL_HELPER+17)	//. ��õ���� ��, ���� ��
	{
		o->Angle[0] = -45.f;
		o->Angle[1] = -5.f;
		o->Angle[2] = 18.f;
		o->Scale = 0.48f;
	}
	else if(o->Type == MODEL_HELPER+18)	//. �������
	{
		o->Angle[0] = 165.f;
		o->Angle[1] = -168.f;
		o->Angle[2] = 198.f;
		o->Scale = 0.48f;
	}
    else if ( o->Type==MODEL_HELPER+30 )//  ����.
    {
        o->Angle[0] = -45.f;
        o->Angle[1] = 0.f;
        o->Angle[2] = 45.f;
        o->Scale    = 0.5f;
    }
    else if ( o->Type==MODEL_EVENT+16 ) //  ������ �Ҹ�.
    {
		o->Angle[2] = 45.f;
        o->Scale    = 0.5f;
    }
	else if(o->Type==MODEL_EVENT+12)	//. ������ ����
	{
		o->Angle[0] = 160.f;
		o->Angle[1] = -183.f;
		o->Angle[2] = 198.f;
		o->Scale = 0.38f;
	}
	else if(o->Type==MODEL_EVENT+13)	//. ��ũ����
	{
		o->Angle[0] = 160.f;
		o->Angle[1] = -183.f;
		o->Angle[2] = 198.f;
		o->Scale = 0.54f;
	}
    else if(o->Type==MODEL_POTION+21)
    {
		o->Angle[0] = 270.f;
		o->Angle[2] = 90.f;
    }
	else if(o->Type==MODEL_EVENT+7)	// ����� �ø���
	{
		o->Angle[2] = 45.f;
	}
	else if(o->Type==MODEL_POTION+20)	// ����� ����
	{
		o->Angle[2] = 45.f;
	}
    else if ( o->Type>=MODEL_HELPER+21 && o->Type<=MODEL_HELPER+24 )
    {
		o->Angle[2] = 20.f;
    }
	//^ �渱 ���� ���϶� ������, ���� ����
	else if(o->Type == MODEL_HELPER+33)	// ������ ��ȣ
	{
		o->Angle[2] = 45.f;
		o->Scale = 1.2f;
	}
	else if(o->Type == MODEL_HELPER+34) // �ͼ��� ����
	{
		o->Angle[0] = 90.f;
	}
	else if(o->Type == MODEL_HELPER+35) // ���Ǹ� ����
	{
		o->Angle[2] = 90.f;
	}
	else if(o->Type == MODEL_HELPER+36) // �η��� ���Ǹ�
	{
		o->Angle[2] = 90.f;
		o->Scale = 1.3f;
	}
	else if(o->Type == MODEL_HELPER+37)	// �渱�� ���Ǹ�
	{
		o->Angle[2] = 180.f;
	}
	else if( o->Type == MODEL_POTION+16 )
	{
		o->Angle[0] = 270.f;
		o->Angle[2] = 90.f - 45.f;
	}
	else if( o->Type == MODEL_POTION+42 )
	{
		o->Angle[0] = 270.f;
		o->Angle[2] = -15.f;
		o->Scale = 1.3f;
	}
	else if( o->Type == MODEL_POTION+43 || o->Type == MODEL_POTION+44 )
	{
		o->Angle[0] = 270.f;
		o->Angle[2] = -15.f;
		o->Scale = 1.0f;
	}
	else if(o->Type >= MODEL_ETC+19 && o->Type <= MODEL_ETC+27
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
		|| o->Type == MODEL_POTION+151 || o->Type == MODEL_POTION+152	// 1���� �Ƿڼ�, 1���� �Ƿ� �Ϸ� Ȯ�μ�
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
		)
	{
		o->Angle[0] = 270.f;
		o->Scale = 0.8f;
	}
#ifdef PBG_ADD_SANTAINVITATION
	//��Ÿ������ �ʴ���.
	else if(o->Type == MODEL_HELPER+66 )
	{
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	//����� ����
	else if(o->Type == MODEL_POTION+100)
	{
		o->Angle[0] = 180.0f;
	//	o->Angle[2] = 0.0f;
		o->Scale = 1.0f;
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// ���� ���� 100% ���� ����
	else if( o->Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN && 
		o->Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END )
	{
		o->Scale = 0.5f;
		o->Angle[2] = 90.f;
	}
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef PBG_ADD_CHARACTERCARD
	// ���� ��ũ ��ȯ���� ī��
	else if(o->Type == MODEL_HELPER+97 || o->Type == MODEL_HELPER+98 || o->Type == MODEL_POTION+91)
	{
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	else if(o->Type == MODEL_HELPER+99)
	{
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
	//Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
	else if(o->Type >= MODEL_HELPER+117 && o->Type <= MODEL_HELPER+120)
	{
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	// ������ ǥ��, ������ ����
	else if(o->Type == MODEL_POTION+110 || o->Type == MODEL_POTION+111)
	{
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	else if(o->Type == MODEL_HELPER+107)
	{
		// ġ��������
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	else if(o->Type == MODEL_HELPER+104)
	{
		// AG���� ����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	else if(o->Type == MODEL_HELPER+105)
	{
		// SD���� ����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	else if(o->Type == MODEL_HELPER+103)
	{
		// ��Ƽ ����ġ ���� ������
		o->Angle[0] = 0.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	else if(o->Type == MODEL_POTION+133)
	{
		// ����Ʈ SDȸ�� ����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	else if(o->Type == MODEL_HELPER+109)
	{
		// �ű� �����̾�(Ǫ����)��
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
	else if(o->Type == MODEL_HELPER+110)
	{
		// �ű� ���(������)��
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ		// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	else if(o->Type == MODEL_HELPER+111)
	{
		// �ű� ������(��Ȳ)��
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	else if(o->Type == MODEL_HELPER+112)
	{
		// �ű� �ڼ���(�����)��
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY		// �ű� ���(������) �����	// MODEL_HELPER+113
	else if(o->Type == MODEL_HELPER+113)
	{
		// �ű� ���(������) �����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD	// �ű� ���޶���(Ǫ��) �����	// MODEL_HELPER+114
	else if(o->Type == MODEL_HELPER+114)
	{
		// �ű� ���޶���(Ǫ��) �����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115
	else if(o->Type == MODEL_HELPER+115)
	{
		// �ű� �����̾�(���) �����
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
	else if(o->Type == MODEL_POTION+112)
	{
		// �ű� Ű(�ǹ�)
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_KEYSILVER	// �ű� Ű(�ǹ�)	// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD	// �ű� Ű(���)	// MODEL_POTION+113
	else if(o->Type == MODEL_POTION+113)
	{
		// �ű� Ű(���)
		o->Angle[0] = 270.0f;
		o->Scale = 1.0f;
	}
#endif	// LDS_ADD_INGAMESHOP_ITEM_KEYGOLD	// �ű� Ű(���)	// MODEL_POTION+113
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL // �ű� ǳ���� ����
	else if( o->Type == MODEL_HELPER+116 )
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	else if( o->Type == MODEL_HELPER+121 )
	{
		o->Scale = 0.5f;
		o->Angle[0] = 90.f;
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef YDG_ADD_SKELETON_PET
	else if (o->Type == MODEL_HELPER+123)	// ���̷�����
	{
		o->Scale = 0.4f;
		o->Angle[0] = 30.f;
	}
#endif	// YDG_ADD_SKELETON_PET
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(o->Type >= MODEL_HELM+59 && o->Type <= MODEL_HELM+59+2)
	{
		o->Scale = 1.0f;
		o->Angle[2] = 45.0f;
	}
	else if(o->Type>=MODEL_ETC+30 && o->Type<=MODEL_ETC+36)
	{
		o->Angle[0] = 270.f;
		o->Scale = 0.8f;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else if(o->Type>=MODEL_WING && o->Type<MODEL_WING+MAX_ITEM_INDEX)
	{
		{
			o->Angle[0] = 270.f;
			o->Angle[2] = 90.f - 45.f;
		}
	}
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �ٴڿ� ������ ������ ������ ���� [lem_2010.9.7]
	else if( o->Type >= MODEL_HELPER+135 && o->Type <= MODEL_HELPER+145 )	// ��Ű������ Ƽ��
	{
		o->Scale = 0.2f;
		o->Angle[0] = 90.f;
	}
	else if(  o->Type == MODEL_POTION+160 || o->Type == MODEL_POTION+161 )	// ����� ����, ������ ����
	{
		o->Scale = 0.2f;
		o->Angle[0] = 90.f;
	}
	else if( Check_LuckyItem( o->Type -MODEL_ITEM ) )
	{
		o->Angle[0] = 250.0f;
		o->Angle[1] = 180.0f;
		o->Angle[2] = 45.0f;
	}
#endif // LEM_ADD_LUCKYITEM
	else
	{
		o->Angle[0] = 0.f;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ���� ������ �������� �ٴڿ� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void CreateItem(ITEM_t *ip,BYTE *Item,vec3_t Position,int CreateFlag)
{
	int Type = ConvertItemType(Item);
	ITEM *n = &ip->Item;
	n->Type = Type;
	if(Type==ITEM_POTION+15)//��
	{
    	n->Level	  = (Item[1]<<16)+(Item[2]<<8)+(Item[4]);
      	n->Durability = 0;
		n->Option1    = 0;
		if(CreateFlag)
			PlayBuffer(SOUND_DROP_GOLD01);
	}
	else//������
	{
		n->Level	  = Item[1];
		n->Durability = Item[2];
		n->Option1    = Item[3];
        n->ExtOption  = Item[4];
		n->option_380 = false;
		BYTE b = ( ( (Item[5] & 0x08) << 4) >>7);
		n->option_380 = b;

		if(CreateFlag)
		{
			// ������ �������� ������ �Ҹ�
			if(Type==ITEM_POTION+13 || Type==ITEM_POTION+14 ||  Type==ITEM_POTION+16 || Type==ITEM_WING+15 || Type==ITEM_POTION+22 || Type==ITEM_POTION+31)
				PlayBuffer(SOUND_JEWEL01,&ip->Object);
			else if(Type == ITEM_POTION+41)
				PlayBuffer(SOUND_JEWEL02,&ip->Object);
			else
				PlayBuffer(SOUND_DROP_ITEM01,&ip->Object);
		}
	}

	OBJECT *o = &ip->Object;
#if defined MR0 || defined OBJECT_ID
	if(o->m_iID == 0) o->m_iID = GenID();
#endif //MR0
	o->Live			  = true;
	o->Type			  = MODEL_SWORD+Type;
	o->SubType        = 1;
	if ( Type == (int)( ITEM_POTION+11))	// ����ǻ���/��ź�Ǻ�/����/���� �ָӴ�./����� ��Ʈ/�� ����/�� ����
	{
		switch ( ( n->Level >> 3))
		{
		case 1:
			o->Type = MODEL_EVENT+4;
			break;
		case 2:
			o->Type = MODEL_EVENT+5;
			break;
		case 3:
			o->Type = MODEL_EVENT+6;
			break;
		case 5:
			o->Type = MODEL_EVENT+8;
			break;
		case 6:
			o->Type = MODEL_EVENT+9;
			break;
#ifdef USE_EVENT_ELDORADO
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			o->Type = MODEL_EVENT+10;
			break;
#endif
		case 13:
			o->Type = MODEL_EVENT+6;
#ifdef NEW_YEAR_BAG_EVENT
		case 14:
		case 15:
			o->Type = MODEL_EVENT+5;
#else
    #ifdef CHINA_MOON_CAKE
		case 14:
			o->Type = MODEL_EVENT+17;
    #endif	//  CHINA_MOON_CAKE
#endif// NEW_YEAR_BAG_EVENT
		}
	}

#ifdef HELLOWIN_EVENT
	if ( Type >= ITEM_POTION+46 && Type <= ITEM_POTION+48)
	{
		o->Type = MODEL_ITEM+Type;
	}
#endif // HELLOWIN_EVENT

#ifdef GIFT_BOX_EVENT
	if ( Type >= ITEM_POTION+32 && Type <= ITEM_POTION+34)
	{
		if( (n->Level >> 3) == 1)
		{
			int Num = Type - (ITEM_POTION+32);
			o->Type = MODEL_EVENT+21+Num;
		}
	}
#endif
#ifdef ANNIVERSARY_EVENT
	if ( Type == (int)( ITEM_POTION+20))	// ����� ����
	{
		switch ( ( n->Level >> 3))
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			o->Type = MODEL_POTION+11;
			break;
		}
	}
#endif	// ANNIVERSARY_EVENT
#ifdef MYSTERY_BEAD
	else if( Type == ITEM_WING+26)
	{
		switch ( ( n->Level >> 3))
		{
		case 0:		//. �ź��� ����
			o->Type = MODEL_EVENT+19;
			break;
		case 1:		//. ��������
			o->Type = MODEL_EVENT+20;
			break;
		case 2:		//. Ǫ������
			o->Type = MODEL_EVENT+20;
			break;
		case 3:		//. ��������
			o->Type = MODEL_EVENT+20;
			break;
		case 4:		//. ��������
			o->Type = MODEL_POTION+11;
			break;
		case 5:
			o->Type = MODEL_POTION+11;
			break;
		}
	}
#endif // MYSTERY_BEAD
    //  0:����, 1:����, 2:������ ��
    else if ( Type==(int)(ITEM_POTION+21) )
    {
        switch ( (n->Level>>3) )
        {
        case 1: //  ����.
        case 2: //  ������ ��.
            o->Type = MODEL_EVENT+11;
            break;
        }
    }
	//. 0:��õ���� ����������. 1:��õ���� �����, 2:��õ���� ���뼮��.
    else if ( Type==(int)(ITEM_HELPER+19) )
    {
        switch ( (n->Level>>3) )
        {
        case 0: //  ��õ���� ����������.
            o->Type = MODEL_STAFF+10;
            n->Level = 0;
            break;
        case 1: //  ��õ���� �����.
            o->Type = MODEL_SWORD+19;
            n->Level = 0;
            break;
        case 2: //  ��õ���� ���뼮��.
            o->Type = MODEL_BOW+18;
            n->Level = 0;
            break;
		}
	}
	else if ( Type==ITEM_POTION+23 )		//. ������ ����
	{
		switch( (n->Level>>3) )
		{
		case 1:
			o->Type = MODEL_EVENT+12;
			break;
		}
	}
	else if ( Type==ITEM_POTION+24 )		//. ��ũ����
	{
		switch( (n->Level>>3) )
		{
		case 1:
			o->Type = MODEL_EVENT+13;
			break;
		}
	}
	else if ( Type == ITEM_HELPER+20 )
	{
		switch( (n->Level>>3) )
		{
		case 0:
			o->Type = MODEL_EVENT+15;
			break;
		case 1:
#ifdef FRIEND_EVENT
        case 2:
#endif// FRIEND_EVENT;
        case 3:
			o->Type = MODEL_EVENT+14;
			break;
		}
	}
	else if ( Type == (int)( ITEM_POTION+9))	// ����� �ø���
	{
		switch ( ( n->Level >> 3))
		{
		case 1:
			o->Type = MODEL_EVENT+7;
			break;
		}
	}
    else if ( Type==ITEM_HELPER+14 && (n->Level>>3)==1 )    //  ������ �Ҹ�.
    {
        o->Type = MODEL_EVENT+16;
    }
    else if ( Type==ITEM_HELPER+11 && (n->Level>>3)==1 )    //  ������ ����.
    {
        o->Type = MODEL_EVENT+18;
    }
	else if ( Type== ITEM_POTION+41 )
	{
		o->Type = MODEL_POTION+41;
	}
	else if ( Type== ITEM_POTION+42 )
	{
		o->Type = MODEL_POTION+42;
	}
	else if ( Type== ITEM_POTION+43 )
	{
		o->Type = MODEL_POTION+43;
	}
	else if ( Type== ITEM_POTION+44 )
	{
		o->Type = MODEL_POTION+44;
	}
	ItemObjectAttribute(o);
	Vector(-30.f,-30.f,-30.f,o->BoundingBoxMin);
	Vector( 30.f, 30.f, 30.f,o->BoundingBoxMax);
	VectorCopy(Position,o->Position);
	if(CreateFlag)
	{
		if ( o->Type == MODEL_EVENT+8 || o->Type == MODEL_EVENT+9)
		{
			short  scale = 55;
			vec3_t Angle;
			vec3_t light;
			Vector( 1.f, 1.f, 1.f, light );
			Vector( 0.f, 0.f, 0.f, Angle);
			vec3_t NewPosition;
			VectorCopy( Position, NewPosition);
			NewPosition[2] = RequestTerrainHeight( Position[0], Position[1] ) + 3;
			CreateEffect(MODEL_SKILL_FURY_STRIKE+6,NewPosition,Angle,light,0,o,scale);
			CreateEffect(MODEL_SKILL_FURY_STRIKE+4,NewPosition,Angle,light,0,o,scale);
			//CreateEffect(MODEL_SKILL_FURY_STRIKE+5,NewPosition,Angle,light,0,o,scale);

     		o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]) + 3.f;
     		o->Gravity     = 50.f;
		}
		else
		{
     		o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]) + 180.f;
     		o->Gravity     = 20.f;
		}
	}
	else
	{
     	o->Position[2] = RequestTerrainHeight(o->Position[0],o->Position[1]);
	}

	ItemAngle(o);
}

///////////////////////////////////////////////////////////////////////////////
// ������ ���� ���� ������ ��¦�̴� ó���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void CreateShiny(OBJECT *o)
{
	vec3_t p,Position;
	if(o->SubType++%48==0)
	{
		float Matrix[3][4];
		AngleMatrix(o->Angle,Matrix);
		Vector((float)(rand()%32+16),0.f,(float)(rand()%32+16),p);
		VectorRotate(p,Matrix,Position);
		VectorAdd(o->Position,Position,Position);
		vec3_t Light;
		Vector(1.f,1.f,1.f,Light);

		CreateParticle(BITMAP_SHINY,Position,o->Angle,Light);
		CreateParticle(BITMAP_SHINY,Position,o->Angle,Light,1);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ ó���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void MoveItems()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_MOVE_ITEMS, PROFILING_MOVE_ITEMS );
#endif // DO_PROFILING	
	for(int i=0;i<MAX_ITEMS;i++)
	{
		OBJECT *o = &Items[i].Object;
		if(o->Live)
		{
			o->Position[2] += o->Gravity;
			o->Gravity -= 6.f;
			float Height = RequestTerrainHeight(o->Position[0],o->Position[1]) + 30.f;
			if(o->Type>=MODEL_SWORD && o->Type<MODEL_STAFF+MAX_ITEM_INDEX)
				Height += 40.f;
			if(o->Position[2] <= Height)
			{
      			o->Position[2] = Height;
             	ItemAngle(o);
			}
			else
			{
				if(o->Type>=MODEL_SHIELD && o->Type<MODEL_SHIELD+MAX_ITEM_INDEX)
					o->Angle[1] = -o->Gravity*10.f;
				else
					o->Angle[0] = -o->Gravity*10.f;
			}
            CreateShiny(o);
		}
	}

#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_MOVE_ITEMS );
#endif // DO_PROFILING
}

///////////////////////////////////////////////////////////////////////////////
// ������ ���� ������ ������������ ���̸� ó���ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ItemHeight(int Type,BMD *b)
{
	if(Type >= MODEL_HELM && Type<MODEL_HELM+MAX_ITEM_INDEX)
		b->BodyHeight = -160.f;
	else if(Type >= MODEL_ARMOR && Type<MODEL_ARMOR+MAX_ITEM_INDEX)
		b->BodyHeight = -100.f;
	else if(Type >= MODEL_GLOVES && Type<MODEL_GLOVES+MAX_ITEM_INDEX)
		b->BodyHeight = -70.f;
	else if(Type >= MODEL_PANTS && Type<MODEL_PANTS+MAX_ITEM_INDEX)
		b->BodyHeight = -50.f;
	else if(Type >= MODEL_BOOTS && Type<MODEL_BOOTS+MAX_ITEM_INDEX)
		b->BodyHeight = 0.f;
	else
		b->BodyHeight = 0.f;
}

///////////////////////////////////////////////////////////////////////////////
// ���� ���� �����۵� �������ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderItems()
{
#ifdef DO_PROFILING
	g_pProfiler->BeginUnit( EPROFILING_RENDER_ITEMS, PROFILING_RENDER_ITEMS );
#endif // DO_PROFILING	
#ifdef MR0
	VPManager::Enable();
#endif //MR0
	for(int i=0;i<MAX_ITEMS;i++)
	{
		OBJECT *o = &Items[i].Object;
		if(o->Live)
		{
#ifdef DYNAMIC_FRUSTRUM
			CFrustrum* pFrus = FindFrustrum(o->m_iID);
			if(pFrus) pFrus->Test(o->Position, 400.f);
			else o->Visible = TestFrustrum(o->Position,400.f);
#else
        	o->Visible = TestFrustrum(o->Position,400.f);
#endif //DYNAMIC_FRUSTRUM
			if(o->Visible)
			{
				int Type = o->Type;
				if(o->Type>=MODEL_HELM && o->Type<MODEL_BOOTS+MAX_ITEM_INDEX)
					Type = MODEL_PLAYER;
            	else if(o->Type==MODEL_POTION+12)//�̹�Ʈ ������
				{
                   	int Level = (Items[i].Item.Level>>3)&15;
					if(Level==0)
			    		Type = MODEL_EVENT;
					else if(Level==2)
			    		Type = MODEL_EVENT+1;
				}
				BMD *b = &Models[Type];
				b->CurrentAction = 0;
              	b->Skin          = GetBaseClass(Hero->Class);
             	b->CurrentAction = o->CurrentAction;
				VectorCopy(o->Position,b->BodyOrigin);
				ItemHeight(o->Type,b);
               	b->Animation(BoneTransform,o->AnimationFrame,o->PriorAnimationFrame,o->PriorAction,o->Angle,o->HeadAngle,false,false);

				if(o->Type>=MODEL_HELM && o->Type<MODEL_BOOTS+MAX_ITEM_INDEX)
					Type = o->Type;
				b = &Models[Type];
				vec3_t Light;
				RequestTerrainLight(o->Position[0],o->Position[1],Light);
				VectorAdd(Light,o->Light,Light);
				if(o->Type == MODEL_POTION+15)  //  �� �׸���.
				{
					vec3_t Temp;
					VectorCopy(o->Position,Temp);
					int Count = (int)sqrtf((float)Items[i].Item.Level)/2;//50
					if(Count < 3) Count = 3;
					if(Count > 80) Count = 80;
					for(int j=1;j<Count;j++)
					{
						vec3_t Angle;
						float Matrix[3][4];
						vec3_t p,Position;
						Vector(0.f,0.f,(float)(RandomTable[(i*20+j)%100]%360),Angle);
						Vector((float)(RandomTable[(i+j)%100]%(Count+20)),0.f,0.f,p);
						AngleMatrix(Angle,Matrix);
						VectorRotate(p,Matrix,Position);
						VectorAdd(Temp,Position,o->Position);
                        RenderPartObject(o,o->Type,NULL,Light,o->Alpha,Items[i].Item.Level,Items[i].Item.Option1,Items[i].Item.ExtOption,true,true,true);
					}
					VectorCopy(Temp,o->Position);
				}
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				else if(o->Type == MODEL_WING+50)
				{
					Vector(1.0f,1.0f,1.0f,Light);
				}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

				vec3_t vBackup;
				VectorCopy( o->Position, vBackup);
				if ( World == WD_10HEAVEN)
				{	// �εս�
					o->Position[2] += 10.0f * ( float)sinf( ( float)( i * 1237 + WorldTime)*0.002f);
				}
				else if ( World == WD_39KANTURU_3RD && g_Direction.m_CKanturu.IsMayaScene())
				{
					o->Position[2] += 10.0f * ( float)sinf( ( float)( i * 1237 + WorldTime)*0.002f);
				}
                else if ( InHellas()==true )
                {
					o->Position[2] = GetWaterTerrain ( o->Position[0], o->Position[1] )+180;
                }

                RenderPartObject(o,o->Type,NULL,Light,o->Alpha,Items[i].Item.Level,Items[i].Item.Option1,Items[i].Item.ExtOption,true,true,true);
				VectorCopy( vBackup, o->Position);

				vec3_t Position;
				VectorCopy(o->Position,Position);
				Position[2] += 30.f;
				int ScreenX,ScreenY;
				Projection(Position,&ScreenX,&ScreenY);
				o->ScreenX = ScreenX;
				o->ScreenY = ScreenY;
			}
		}
	}
#ifdef MR0
	VPManager::Disable();	// ????
#endif //MR0

#ifdef DO_PROFILING
	g_pProfiler->EndUnit( EPROFILING_RENDER_ITEMS );
#endif // DO_PROFILING
}

///////////////////////////////////////////////////////////////////////////////
// ������ Į�� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void PartObjectColor(int Type,float Alpha,float Bright,vec3_t Light,bool ExtraMon)
{
	// Į�� 0���� �ʱ�ȭ
	int Color = 0;

	if(ExtraMon && ( Type==MODEL_MONSTER01+27 || Type==MODEL_SPEAR+9))	// �߷�2
	{
		Color = 8;
	}
	else if(Type==MODEL_MONSTER01+27 || Type==MODEL_SPEAR+9)//�߷�
	{
		Color = 1;
	}
	else if(Type==MODEL_MONSTER01+35 || Type==MODEL_BOW+5 || Type==MODEL_BOW+13)//�����
	{
		Color = 5;
	}
	else if(Type==MODEL_SWORD+14 || Type==MODEL_STAFF+5 || ( Type>=MODEL_POTION+25 && Type<MODEL_POTION+27 ) )//����, ������ ����, ��������ȥ.
	{
		Color = 2;
	}
    else if(Type==MODEL_BOW+17 || Type==MODEL_BOW+19)	//  Ȧ�� ����Ʈ ����. ������ ����.
    {
        Color = 9;
    }
    else if( Type==MODEL_WING+14 )  //  �ִ� ����� ���� ��ų ����.
    {
        Color = 2;
    }
	else if( Type==MODEL_BOW+18 )	//	��õ���� ���� ����.
	{
		Color = 10;
	}
    else if ( Type==MODEL_STAFF+9 ) //  ������ ������.
    {
        Color = 5;
    }
	else if ( Type==MODEL_SWORD+31 )	//	
	{
		Color = 10;
	}
	else if ( Type==MODEL_SHIELD+16 )	//	
	{
		Color = 6;
	}
	else if ( Type==MODEL_SPEAR+10 )
	{
		Color = 9;
	}
	else if ( Type==MODEL_MACE+8 )
	{
		Color = 9;
	}
	else if ( Type==MODEL_MACE+9 )
	{
		Color = 10;
	}
	else if ( Type==MODEL_MACE+10 )
	{
		Color = 12;
	}
	else if(Type == MODEL_SWORD+20)		//. ���� �߰���
	{
		Color = 10;
	}
	else if(Type == MODEL_SWORD+21)		//. ���˻� �߰���
	{
		Color = 5;
	}
	else if(Type == MODEL_BOW+20)		//. ���� �߰�Ȱ
	{
		Color = 16;
	}
	else if(Type == MODEL_STAFF+11)		// ����� ������
	{
		Color = 17;	// 5,6
	}
	else if ( Type==MODEL_MACE+12 )     //  ��ũ�ε� ���� 5.
    {
		Color = 16;	// 5,6
    }
	else if(Type == MODEL_SWORD+22)
	{
		Color = 18;
	}
	else if(Type == MODEL_STAFF+12)
	{
		Color = 19;
	}
	else if(Type == MODEL_BOW+21)
	{
		Color = 20;
	}
	else if(Type == MODEL_SWORD+23)
	{
		Color = 23;
	}
	else if(Type == MODEL_MACE+14)
	{
		Color = 22;
	}
	//$ ũ���̿��� ������
	else if(Type == MODEL_SWORD+24)	// ����
	{
		Color = 24;
	}
	else if(Type == MODEL_STAFF+13)	// �渶����
	{
		Color = 25;
	}
	else if(Type == MODEL_BOW+22)	// ����
	{
		Color = 26;
	}
	else if(Type == MODEL_MACE+15)	// ��ũ�ε�
	{
		Color = 28;
	}
	else if(Type == MODEL_SWORD+25)	// ���˻�
	{
		Color = 27;
	}
	else if (Type == MODEL_STAFF+14)
		Color = 24;
	else if (Type == MODEL_STAFF+15)
		Color = 15;
	else if (Type == MODEL_STAFF+16)
		Color = 1;
	else if (Type == MODEL_STAFF+17)
		Color = 3;
	else if (Type == MODEL_STAFF+18)
		Color = 30;
	else if (Type == MODEL_STAFF+19)
		Color = 21;
	else if (Type == MODEL_STAFF+20)
#ifdef ASG_ADD_ETERNALWING_STICK_EFFECT
		Color = 34;
#else	// ASG_ADD_ETERNALWING_STICK_EFFECT
		Color = 5;
#endif	// ASG_ADD_ETERNALWING_STICK_EFFECT
	else if (Type == MODEL_STAFF+22)
		Color = 1;
#ifdef ADD_SOCKET_ITEM
	else if( Type == MODEL_SWORD+28 )		// ��ٽ�Ÿ��
		Color = 8;
	else if( Type == MODEL_STAFF+30 )		// ���鸮������
		Color = 1;
	else if( Type == MODEL_STAFF+31 )		// �κ����˽�����
		Color = 19;
	else if( Type == MODEL_MACE+17 )		// �ۼַ�Ʈ����
		Color = 40;
	else if( Type == MODEL_SHIELD+19 )		// ���ν�Ʈ�踮��
		Color = 29;
	else if( Type == MODEL_BOW+23 )			// ��ũ���ð�
		Color = 35;
	else if( Type == MODEL_SHIELD+20 )		// ��������
		Color = 36;
#endif // ADD_SOCKET_ITEM
#ifdef CSK_ADD_ITEM_CROSSSHIELD
 	else if(Type == MODEL_SHIELD+21)		// ũ�ν��ǵ�
 		Color = 30;
#endif // CSK_ADD_ITEM_CROSSSHIELD
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	else if(Type == MODEL_SPEAR+11)		//�׺� ���� ��
		Color = 20;
	else if(Type == MODEL_STAFF+33)		//�׺� ���� ������
		Color = 43;
	else if(Type == MODEL_STAFF+34)		//�׺� ���� ��ƽ
		Color = 5;
	else if(Type == MODEL_MACE+18)		//�׺� ���� ����
		Color = 5;
	else if(Type == MODEL_BOW+24)		//�׺� ���� Ȱ
		Color = 36;
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+32)		// �巹��ٿ
		Color = 16;
	else if(g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+33)		// Ÿ�̰���Ŭ��
		Color = 42;
	else if(g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+34)		// �����Ǳ۷���
		Color = 18;
	else if(Type == MODEL_ARMORINVEN_60)
		Color = 16;
	else if(Type == MODEL_ARMORINVEN_61)
		Color = 42;
	else if(Type == MODEL_ARMORINVEN_62)
		Color = 18;
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else//  if ( Type<MODEL_WING )
	{
		int ItemType = Type-MODEL_ITEM;
		if(ItemType/MAX_ITEM_INDEX>=7 && ItemType/MAX_ITEM_INDEX<=11)
		{
			switch(ItemType%MAX_ITEM_INDEX)
			{
#ifdef PJH_NEW_CHROME
			case 7 :Color=44;break;//����ũ��
#endif //PJH_NEW_CHROME
			case 1 :Color=1;break;//��
			case 9 :Color=2;break;//ö��
			case 12:Color=2;break;//�ٶ�
			case 3 :Color=3;break;//����
			case 13:Color=4;break;//����
			case 4 :Color=5;break;//��
			case 14:Color=5;break;//��ȣ
			case 6 :Color=6;break;//���
			case 15:Color=7;break;//��Ʋ����
            case 16:Color=10;break;//������.
            case 17:Color=9;break;//�Ǵн�.
            case 18:Color=5;break;//�ҿ︶����.
            case 19:Color=9;break;//����.
            case 20:Color=9;break;//�������̵�.
			case 21:Color=16;break;	//. ���
			case 22:Color=17;break; //. �渶����.
            case 23:Color=11;break; //. ���˻�.
			case 24:Color=16;break;	//. ����
            case 25:Color=11;break;// ��ũ�ε�1.
            case 26:Color=12;break;// ��ũ�ε�2.
            case 27:Color=10;break;// ��ũ�ε�3.
            case 28:Color=15;break;// ��ũ�ε�4.
			case 29:Color=18;break;// ���� Į���� ������(����)
			case 30:Color=19;break;// ���� Į���� ������(�渶����)
			case 31:Color=20;break;// ���� Į���� ������(����)
			case 32:Color=21;break;// ���� Į���� ������(���˻�)
			case 33:Color=22;break;// ���� Į���� ������(��ũ�ε�)
			//$ ũ���̿��� ������
			case 34:Color=24;break;	// ����				
			case 35:Color=25;break;	// �渶����
			case 36:Color=26;break;	// ����
			case 37:Color=27;break;	// ���˻�
			case 38:Color=28;break;	// ��ũ�ε�
			// ��ȯ���� �� ������(39~44)
			case 39:Color=29;break;
			case 40:Color=30;break;
			case 41:Color=31;break;
			case 42:Color=32;break;
			case 43:Color=33;break;
			case 44:Color=34;break;
#ifdef ADD_SOCKET_ITEM
			case 45:Color=36;break;		// Ƽź��Ʈ (����)
#ifdef KJH_MODIFY_SOCKET_ITEM_COLOR
			case 46:Color=42;break;		// �극�̺��Ʈ (����)
#else // KJH_MODIFY_SOCKET_ITEM_COLOR
			case 46:Color=0;break;	
#endif // KJH_MODIFY_SOCKET_ITEM_COLOR
			case 47:Color=37;break;		// ���Ҽ�Ʈ (���˻�)
			case 48:Color=1;break;		// ��Ʈ���̼�Ʈ (���˻�)
			case 49:Color=35;break;		// �����˼�Ʈ (����)
			case 50:Color=39;break;		// ����μ�Ʈ (����)
			case 51:Color=40;break;		// �пռ�Ʈ (��ũ�ε�)
			case 52:Color=36;break;		// �ϵ�����Ʈ (�渶����)
			case 53:Color=41;break;		// ��ť������Ʈ (��ȯ����)	
#endif // ADD_SOCKET_ITEM
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			case 59:Color=16;break;		// ������������ ��
			case 60:Color=42;break;		// �������ϵ�
			case 61:Color=18;break;		// �Ǿ�̱׷κ�
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			}
		}
	}
	Bright *= Alpha;
	switch(Color)
	{
	case 0:Vector(Bright*1.0f,Bright*0.5f,Bright*0.0f,Light);break;//�Ϲ�
	case 1:Vector(Bright*1.0f,Bright*0.2f,Bright*0.0f,Light);break;//��
	case 2:Vector(Bright*0.0f,Bright*0.5f,Bright*1.0f,Light);break;//ö��
	case 3:Vector(Bright*0.0f,Bright*0.5f,Bright*1.0f,Light);break;//����
	case 4:Vector(Bright*0.0f,Bright*0.8f,Bright*0.4f,Light);break;//����
	case 5:Vector(Bright*1.0f,Bright*1.0f,Bright*1.0f,Light);break;//��ȣ
	case 6:Vector(Bright*0.6f,Bright*0.8f,Bright*0.4f,Light);break;//���
	case 7:Vector(Bright*0.9f,Bright*0.8f,Bright*1.0f,Light);break;//��Ʋ����
	case 8:Vector(Bright*0.8f,Bright*0.8f,Bright*1.0f,Light);break;				// ��ٽ�Ÿ��
    case 9:Vector(Bright*0.5f,Bright*0.5f,Bright*0.8f,Light);break;//�Ǵн�.
    case 10:Vector(Bright*0.75f,Bright*0.65f,Bright*0.5f,Light);break;//������.
	case 11:Vector(Bright*0.35f,Bright*0.35f,Bright*0.6f,Light);break;//
	case 12:Vector(Bright*0.47f,Bright*0.67f,Bright*0.6f,Light);break;//��ũ�ε�2
	case 13:Vector(Bright*0.0f,Bright*0.3f,Bright*0.6f,Light);break;//����
	case 14:Vector(Bright*0.65f,Bright*0.65f,Bright*0.55f,Light);break;// ����߰�����
    case 15:Vector(Bright*0.2f,Bright*0.3f,Bright*0.6f,Light);break;// ��ũ�ε�4
	case 16:Vector(Bright*0.8f,Bright*0.46f,Bright*0.25f,Light);break;// �����߰�����
    case 17:Vector(Bright*0.65f,Bright*0.45f,Bright*0.3f,Light);break;//�渶����.
    case 18:Vector(Bright*0.5f,Bright*0.4f,Bright*0.3f,Light);break;//���� Į���� ������(����)
    case 19:Vector(Bright*0.37f,Bright*0.37f,Bright*1.0f,Light);break;//���� Į���� ������(�渶����), �κ����� ������
    case 20:Vector(Bright*0.3f,Bright*0.7f,Bright*0.3f,Light);break;//���� Į���� ������(����)
    case 21:Vector(Bright*0.5f,Bright*0.4f,Bright*1.0f,Light);break;//���� Į���� ������(���˻�)
    case 22:Vector(Bright*0.45f,Bright*0.45f,Bright*0.23f,Light);break;//���� Į���� ������(��ũ�ε�)
    case 23:Vector(Bright*0.3f,Bright*0.3f,Bright*0.45f,Light);break;//���� Į���� ������(���˻� ����)
	//$ũ���̿��� ������
	case 24:Vector(Bright*0.6f,Bright*0.5f,Bright*0.2f,Light);break;	// ����
    case 25:Vector(Bright*0.6f,Bright*0.6f,Bright*0.6f,Light);break;	// �渶����
    case 26:Vector(Bright*0.3f,Bright*0.7f,Bright*0.3f,Light);break;	// ����
    case 27:Vector(Bright*0.5f,Bright*0.6f,Bright*0.7f,Light);break;	// ��ũ�ε�
    case 28:Vector(Bright*0.45f,Bright*0.45f,Bright*0.23f,Light);break;	// ���˻�
	// ��ȯ���� �� ������ (29~34)
	case 29:Vector(Bright*0.2f,Bright*0.7f,Bright*0.3f,Light);break;
	case 30:Vector(Bright*0.7f,Bright*0.3f,Bright*0.3f,Light);break;
	case 31:Vector(Bright*0.7f,Bright*0.5f,Bright*0.3f,Light);break;
	case 32:Vector(Bright*0.5f,Bright*0.2f,Bright*0.7f,Light);break;
	case 33:Vector(Bright*0.8f,Bright*0.4f,Bright*0.6f,Light);break;
	case 34:Vector(Bright*0.6f,Bright*0.4f,Bright*0.8f,Light);break;
#ifdef ADD_SOCKET_ITEM
#ifdef KJH_MODIFY_SOCKET_ITEM_COLOR
	case 35:Vector(Bright*0.7f,Bright*0.4f,Bright*0.4f,Light);break;		// �����˼�Ʈ
#else // KJH_MODIFY_SOCKET_ITEM_COLOR
	case 35:Vector(Bright*0.95f,Bright*0.6f,Bright*0.6f,Light);break;
#endif // KJH_MODIFY_SOCKET_ITEM_COLOR
	case 36:Vector(Bright*0.5f,Bright*0.5f,Bright*0.7f,Light);break;
	case 37:Vector(Bright*0.7f,Bright*0.5f,Bright*0.7f,Light);break;
	case 38:Vector(Bright*0.2f,Bright*0.4f,Bright*0.7f,Light);break;
#ifdef KJH_MODIFY_SOCKET_ITEM_COLOR
	case 39:Vector(Bright*0.3f,Bright*0.6f,Bright*0.4f,Light);break;		// ����μ�Ʈ
	case 40:Vector(Bright*0.7f,Bright*0.2f,Bright*0.2f,Light);break;		// �пռ�Ʈ
#else // KJH_MODIFY_SOCKET_ITEM_COLOR
	case 39:Vector(Bright*0.5f,Bright*0.8f,Bright*0.6f,Light);break;
	case 40:Vector(Bright*0.9f,Bright*0.5f,Bright*0.5f,Light);break;
#endif // KJH_MODIFY_SOCKET_ITEM_COLOR
	case 41:Vector(Bright*0.7f,Bright*0.2f,Bright*0.7f,Light);break;
#ifdef KJH_MODIFY_SOCKET_ITEM_COLOR
	case 42:Vector(Bright*0.8f,Bright*0.4f,Bright*0.0f,Light);break;		// �극�̺��Ʈ
#endif // KJH_MODIFY_SOCKET_ITEM_COLOR
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	case 43:Vector(Bright*0.8f,Bright*0.6f,Bright*0.2f,Light);break;		// �� ���
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef PJH_NEW_CHROME
	case 44:	//�ΰ�
		Vector(Bright*0.8f,Bright*0.7f,Bright*0.4f,Light);
		break;		// �� ���
#endif //PJH_NEW_CHROME
	}
}


void PartObjectColor2(int Type,float Alpha,float Bright,vec3_t Light,bool ExtraMon)
{
	int Color = 0;
	if(Type==MODEL_BOW+5 || Type==MODEL_BOW+13)
	{
		Color = 2;
	}
	else if(Type==MODEL_SWORD+14 || Type==MODEL_STAFF+5)//����
	{
		Color = 2;
	}
    else if(Type==MODEL_SWORD+18)   //  ���� ���̵�.
    {
        Color = 0;
    }
    else if ( Type==MODEL_BOW+17 )  //  ���� ����.
    {
        Color = 0;
    }
    else if ( Type==MODEL_STAFF+9 ) //  ������ ������.
    {
        Color = 0;
    }
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type == MODEL_ARMORINVEN_60
		|| Type == MODEL_ARMORINVEN_61
		|| Type == MODEL_ARMORINVEN_62)
	{
		Color = 0;
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else
	{
		int ItemType = Type-MODEL_ITEM;
		if(ItemType/MAX_ITEM_INDEX>=7 && ItemType/MAX_ITEM_INDEX<=11)
		{
			switch(ItemType%MAX_ITEM_INDEX)
			{
            case 0 :Color=0;break;  //  û��.      
            case 1 :Color=0;break;  //  ����.    
            case 2 :Color=0;break;  //  �е�.      
            case 3 :Color=0;break;  //  ����.      
            case 4 :Color=1;break;  //  ��.        
            case 5 :Color=0;break;  //  ����.      
            case 6 :Color=0;break;  //  ���.      
            case 7 :Color=0;break;  //  ����ũ��.  
//			case 7 :Color=44;break;  //  ����ũ��.  
            case 8 :Color=0;break;  //  Ȳ��.      
            case 9 :Color=0;break;  //  ö��.      
            case 10:Color=0;break; //  ����.      
            case 11:Color=0;break; //  ��ũ.      
            case 12:Color=0;break; //  �ٶ�.      
            case 13:Color=0;break; //  ����.      
            case 14:Color=1;break; //  ��ȣ.      
            case 15:Color=1;break; //  ��Ʋ����.  
            case 16:Color=0;break; //  ������.
            case 17:Color=1;break; //  �Ǵн�.
            case 18:Color=2;break; //   �ҿ︶����.
            case 19:Color=0;break; //  Ȧ�����Ǹ�.
			case 21:Color=3;break; //  ����߰�����.
			// ��ȯ���� �� ������ (39~44)
			case 39:Color=1;break;
			case 40:Color=1;break;
			case 41:Color=1;break;
			case 42:Color=1;break;
			case 43:Color=2;break;
			case 44:Color=3;break;
#ifdef ADD_SOCKET_ITEM
			case 45:Color=0;break;
#endif // ADD_SOCKET_ITEM
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			case 59:Color=0;break;	// ��ũ�������̾�
			case 60:Color=0;break;	// �������ϵ�
			case 61:Color=0;break;	// �Ǿ�̱׷κ�
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			}
		}
	}
	Bright *= Alpha;
	switch(Color)
	{
	case 0: Vector(Bright*1.0f*Light[0],Bright*1.0f*Light[1],Bright*1.0f*Light[2],Light);break;    //  
	case 1: Vector(Bright*1.0f*Light[0],Bright*0.5f*Light[1],Bright*0.0f*Light[2],Light);break;    //  
	case 2: Vector(Bright*0.0f*Light[0],Bright*0.5f*Light[1],Bright*1.0f*Light[2],Light);break;    //
	case 3: Vector(1.f, 1.f, 1.f,Light);	//
	}
}

void PartObjectColor3(int Type,float Alpha,float Bright,vec3_t Light,bool ExtraMon)
{
	int Color = 0;
	int ItemType = Type-MODEL_ITEM;

	if(ItemType/MAX_ITEM_INDEX>=7 && ItemType/MAX_ITEM_INDEX<=11)
	{
		switch(ItemType%MAX_ITEM_INDEX)
		{
        case 0 :Color=0;break;  //  û��.      
        case 1 :Color=0;break;  //  ����.    
        case 2 :Color=0;break;  //  �е�.      
        case 3 :Color=1;break;  //  ����.      
        case 4 :Color=0;break;  //  ��.        
        case 5 :Color=0;break;  //  ����.      
        case 6 :Color=0;break;  //  ���.      
        case 7 :Color=0;break;  //  ����ũ��.  
//		case 7 :Color=44;break;  //  ����ũ��.  
        case 8 :Color=0;break;  //  Ȳ��.      
        case 9 :Color=1;break;  //  ö��.      
        case 10:Color=0;break; //  ����.      
        case 11:Color=0;break; //  ��ũ.      
        case 12:Color=0;break; //  �ٶ�.      
        case 13:Color=0;break; //  ����.      
        case 14:Color=0;break; //  ��ȣ.      
        case 15:Color=0;break; //  ��Ʋ����.  
        case 16:Color=0;break; //  ������.
        case 17:Color=1;break; //  �Ǵн�.
        case 18:Color=0;break; //   �ҿ︶����.
        case 19:Color=0;break; //  Ȧ�����Ǹ�.
		}
	}
	switch(Color)
	{
	case 0: Vector(0.1f,0.6f,1.0f,Light);break;    //  
	case 1: Vector(1.f,0.7f,0.2f,Light);break;    // 
	}
}

///////////////////////////////////////////////////////////////////////////////
// ������ �ϳ��� ��ü�� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void RenderPartObjectBody(BMD *b,OBJECT *o,int Type,float Alpha,int RenderType)
{
	int		nIndex;
	int		nNum;

	nIndex = int((o->Type+1-MODEL_ITEM)/ 512.0f);
	nNum = (o->Type-MODEL_ITEM)%512;

#ifdef YDG_FIX_ELSEIF_BLOCK_BREAK_AT_RENDER_PART_OBJECT_BODY_FUNC
	BOOL bIsNotRendered = FALSE;	// if������ �ѷ� �ɰ��� ���� �˻��ϱ� ���� ����, ó���� �ȱ׸��� TRUEó��
#endif	// YDG_FIX_ELSEIF_BLOCK_BREAK_AT_RENDER_PART_OBJECT_BODY_FUNC
	if((Type==MODEL_ARMOR+15 || Type==MODEL_GLOVES+15 || Type==MODEL_PANTS+15 || Type==MODEL_BOOTS+15)   //  ��Ʋ���� ���� ȿ��.
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
	)
	{
		b->RenderBody(RENDER_TEXTURE|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#ifndef YDG_ADD_DOPPELGANGER_MONSTER
	// Test
	else if( Type==MODEL_HELM+1)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, -1);
	}
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#

    else if ( Type==MODEL_ARMOR+20 || Type==MODEL_GLOVES+20 || Type==MODEL_PANTS+20 || Type==MODEL_BOOTS+20 )	// ����ȣũ ���� ȿ��
    {
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
        Vector(0.85f*Light[0],0.85f*Light[1],1.2f*Light[2],b->BodyLight);
		b->RenderBody(RENDER_TEXTURE|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		VectorCopy(Light, b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
    }
    else if( Type==MODEL_WING+6 )    //  ���˻� ( ����� ���� ).
    {
        Vector(0.8f,0.6f,1.f,b->BodyLight);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
    }	
	else if(Type == MODEL_WING+36)	// ���� 3�� ����
	{
		Vector(1.f,0.7f,0.5f,b->BodyLight);
		glColor3fv(b->BodyLight);
		b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float fU = 0.f;
		static int s_iTexAni = 0;
		s_iTexAni++;
		if(s_iTexAni > 15)
			s_iTexAni = 0;
		fU = (s_iTexAni / 4) * 0.25f;
		Vector(0.9f, 0.6f, 0.3f, b->BodyLight);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,fU,o->BlendMeshTexCoordV,o->HiddenMesh);
		Vector(1.f, 1.f, 1.f, b->BodyLight);
	}
// 	else if( Type==MODEL_WING+37 )	// �ð�����(����)
//     {
// 		Vector(1.f,1.f,1.f,b->BodyLight);
// 		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
//     }
	else if(Type == MODEL_WING+39)	// �ĸ곯��(���˻�)
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		glColor3fv(b->BodyLight);
		b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		float Luminosity = absf(sinf(WorldTime*0.001f))*0.3f;
		Vector(0.1f + Luminosity, 0.1f + Luminosity, 0.1f + Luminosity, b->BodyLight);
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		Luminosity = absf(sinf(WorldTime*0.001f))*0.8f;
		Vector(0.0f + Luminosity, 0.0f + Luminosity, 0.0f + Luminosity, b->BodyLight);
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_3RDWING_LAYER);
	}
	else if (Type == MODEL_WING+40)	// �����Ǹ���(��ũ�ε�)
	{
		if (b->BodyLight[0] == 1 && b->BodyLight[1] == 1 && b->BodyLight[2] == 1)	// �κ��丮
		{
			Vector(1.f,1.f,1.f,b->BodyLight);
			glColor3fv(b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else		// �� �׸�
		{
			Vector(1.f,1.f,1.f,b->BodyLight);
			glColor3fv(b->BodyLight);
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
	}
#ifdef ADD_ALICE_WINGS_1
	else if (Type == MODEL_WING+42)	// �����ǳ���(��ȯ���� 2�� ����)
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		glColor3fv(b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME6, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif	// ADD_ALICE_WINGS_1
#ifdef ADD_ALICE_WINGS_2
	else if (Type == MODEL_WING+43)	// �����ǳ���(��ȯ���� 3�� ����)
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		glColor3fv(b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif	// ADD_ALICE_WINGS_2
    else if ( Type==MODEL_SWORD+19 )	// ��õ���� ����� ȿ��
    {
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_METAL,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_LIGHTMAP|RENDER_TEXTURE,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0001f,BITMAP_CHROME);
		b->RenderMesh(1,RENDER_TEXTURE,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
    }
    else if ( Type==MODEL_STAFF+10 )	// ��õ���� ���� ������ ȿ��
    {
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_METAL,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_LIGHTMAP|RENDER_TEXTURE,1.f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,-WorldTime*0.0001f,BITMAP_CHROME);
		b->RenderMesh(1,RENDER_TEXTURE,Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
    }				    
    else if ( Type==MODEL_BOW+18 )	// ��õ���� ���� ���� ȿ��
    {
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_METAL,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_LIGHTMAP|RENDER_TEXTURE,1.f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,-WorldTime*0.0001f,BITMAP_CHROME);
		b->RenderMesh(1,RENDER_TEXTURE,Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
    }
	else if ( Type==MODEL_MACE+13 ) // ��õ���� ���� ���� ȿ��
	{
		b->RenderMesh(0,RENDER_TEXTURE,Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_LIGHTMAP|RENDER_TEXTURE,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,-WorldTime*0.0001f,BITMAP_CHROME);
	}
	else if ( Type==MODEL_BOW+19 )	// �׷���Ʈ ���� ���� ȿ��
	{
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
		Vector(0.8f*Light[0],0.f,0.8f*Light[2],b->BodyLight);
		b->RenderMesh(0,RENDER_LIGHTMAP|RENDER_TEXTURE,1.f,0,o->BlendMeshLight,-WorldTime*0.0002f,o->BlendMeshTexCoordV,BITMAP_CHROME);
		VectorCopy(Light, b->BodyLight);
		b->RenderMesh(0,RENDER_CHROME|RENDER_BRIGHT,1.f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME+1);
		VectorCopy(Light, b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
	else if(Type == MODEL_POTION+45)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);	
		b->RenderMesh(1, RENDER_DARK|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,-WorldTime*0.0002f,o->BlendMeshTexCoordV, BITMAP_CHROME);	
		
		vec3_t vPos, vRelativePos;
		Vector(0.f, 0.f, 0.f, vRelativePos);
		b->TransformPosition(BoneTransform[8],vRelativePos,vPos,true);
		float fLumi = (sinf(WorldTime*0.004f) + 1.0f) * 0.05f;
		Vector(0.8f+fLumi, 0.8f+fLumi, 0.3f+fLumi, o->Light);
		CreateSprite(BITMAP_LIGHT, vPos, 1.5f, o->Light, o, 0.5f);
		b->TransformPosition(BoneTransform[10],vRelativePos,vPos,true);
		CreateSprite(BITMAP_LIGHT, vPos, 0.5f, o->Light, o, 0.5f);
		b->TransformPosition(BoneTransform[11],vRelativePos,vPos,true);
		CreateSprite(BITMAP_LIGHT, vPos, 0.5f, o->Light, o, 0.5f);
	}
	else if(o->Type >= MODEL_ETC+19 && o->Type <= MODEL_ETC+27)
	{	
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float fLumi = (sinf(WorldTime*0.0015f) + 1.0f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh, BITMAP_ROOLOFPAPER_EFFECT_R);
	}
	else if ( Type==MODEL_SWORD+31
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)	// ������ε� ȿ��
	{
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
		b->BeginRender(1.f);
		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(3,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,sinf(WorldTime*0.01f),1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_CHROME|RENDER_TEXTURE, 1.f, 0,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.001f,BITMAP_CHROME);

		float Luminosity = sinf( WorldTime*0.001f )*0.5f+0.5f;
        Vector(Light[0]*Luminosity,Light[0]*Luminosity,Light[0]*Luminosity,b->BodyLight);
		b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,1.f,2,o->BlendMeshLight,WorldTime*0.0001f,-WorldTime*0.0005f);
		b->EndRender();
	}
	else if ( Type==MODEL_SPEAR+10 )	// ���ｺ�Ǿ� ȿ��
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1,RENDER_TEXTURE,1.f,1,o->BlendMeshLight,WorldTime*0.0001f,WorldTime*0.0005f);
	}
	else if ( Type==MODEL_MACE+7 )	// ������Ż ���̽� ȿ��
	{
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

		float time = WorldTime*0.001f;
		float Luminosity = sinf( time )*0.5f+0.3f;
        Vector(Light[0]*Luminosity,Light[0]*Luminosity,Light[0]*Luminosity,b->BodyLight);
		b->RenderMesh(2,RENDER_TEXTURE,1.f,2,o->BlendMeshLight,time,-WorldTime*0.0005f);
	}
    else if ( Type==MODEL_HELPER+4 )    //  ��ũȣ�� ������.
    {
		b->RenderBody ( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		Vector ( 0.8f, 0.4f, 0.1f, b->BodyLight );
		b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
    }
    else if ( Type==MODEL_HELPER+5 )    //  ��ũ���Ǹ� ������.
    {
		b->RenderBody ( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		Vector ( 0.3f, 0.8f, 1.f, b->BodyLight );
		b->RenderMesh ( 0, RENDER_BRIGHT|RENDER_CHROME, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
    }
	else if ( Type==MODEL_MACE+8 )		//. ��ũ�ε������01
	{
        o->BlendMeshLight = sinf( WorldTime*0.001f )*0.6f+0.4f;
		b->BeginRender(1.f);
        b->RenderBody ( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
        b->RenderMesh ( 0, RENDER_TEXTURE, Alpha, 0, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
		b->EndRender();
	}
	else if ( Type==MODEL_MACE+9 )		//. ��ũ�ε������02
	{
		b->RenderBody ( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
		Vector ( 0.1f, 0.3f, 1.f, b->BodyLight );
        o->BlendMesh = 0;
        o->BlendMeshLight = sinf( WorldTime*0.001f )*0.6f+0.4f;
		b->RenderMesh ( 0, RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		Vector ( 0.6f, 0.8f, 1.f, b->BodyLight );
        o->BlendMesh = 1;
        o->BlendMeshLight = 1.f;
		b->RenderMesh ( 1, RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, WorldTime*0.0003f, BITMAP_CHROME );
	}
#ifdef ADD_SOCKET_ITEM
	else if( Type == MODEL_SWORD+26 )	// �ö�������
	{
		// ��ü ������
		//b->RenderBody( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, 5 );	

		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		b->RenderMesh( 2, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		o->BlendMesh = 1;
		Vector(1.f, 0.f, 0.2f, b->BodyLight);
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		Vector(1.f, 1.f, 1.f, b->BodyLight);
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		b->RenderMesh( 3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		b->RenderMesh( 4, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		float fV;
		fV = (((int)(WorldTime*0.05)%16)/4)*0.25f;
		b->RenderMesh( 5, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 5, o->BlendMeshLight, o->BlendMeshTexCoordU, fV );
	}
	else if( Type == MODEL_SWORD+27 )	// �ҵ�극��Ŀ
	{
		// ��ü ������
		b->RenderBody( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	

		// Į���κ�
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SWORD+28 )	// ��ٽ�Ÿ��
	{
		// ��ü ������
		b->RenderBody( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

		// Į�չص��̿� ���������κ�
		o->BlendMesh = 1;
		o->BlendMeshLight = sinf( WorldTime*0.001f )*0.6f+0.4f;    // ���̵���/�ƿ� (0.4~1.0)
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			
	}
	else if( Type == MODEL_MACE+16 )	// ���ν�Ʈ���̽�
	{
		// ��ü ������
		b->RenderBody( RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, 1 );
		// �պκ� (GRA.JPG)
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// �պκ� (GRA.JPG)
		b->RenderMesh( 3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// �����̱��� (bloodbone02.JPG)
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_STAFF+30 )	// ���鸮������
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	

		// Į�� �����Ʈ
		o->BlendMesh = 1;
		o->BlendMeshLight = 1.f;
		Vector(1.f, 0.5f, 0.5f, b->BodyLight);
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_STAFF+31 )	// �κ����˽�����
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		// Į�� �����Ʈ
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		
		// �ؽ��� ���̵� ��/�ƿ� ȿ��
		o->BlendMesh = 0;
		o->BlendMeshLight = fabs(sinf( WorldTime*0.001f ))+0.1f;
		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SOCKETSTAFF );
		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SOCKETSTAFF );
		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_SOCKETSTAFF );
	}
	else if( Type == MODEL_STAFF+32 )	// �ҿ�긵��
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		// ���� (agnecklace.JPG)
		b->RenderMesh( 0, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// �� ����(bloodbone02.JPG)
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// Į���κ� ����(devileye.jpg)
		b->RenderMesh( 3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		b->RenderMesh( 3, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SHIELD+17 )	// ũ�����۷θ�
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// ������ (flareRed.jpg)
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		// Į�� (gra.jpg)
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SHIELD+18 )	// �����Ǵ��ǵ�
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, 1 );

		// ���� ������ �κ�
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SHIELD+19 )	// ���ν�Ʈ�踮��
	{
		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

		// ���п� �����ִ±���
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

		// �������
		o->BlendMesh = 2;
 		o->BlendMeshLight = absf((sinf( WorldTime*0.001f )));	// ���̵���/�ƿ�
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SHIELD+20 )	// �����ǵ�
	{
		// ��ü ������
		b->RenderBody( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );

		// ���� ������ �κ�
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
#endif // ADD_SOCKET_ITEM
#ifdef CSK_ADD_ITEM_CROSSSHIELD
	else if(Type == MODEL_SHIELD+21)	// ũ�ν��ǵ�
	{
		glColor3f(1.f, 1.f, 1.f);
		b->RenderMesh( 0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		b->StreamMesh = 1;
		b->RenderMesh( 1, RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, -(int)WorldTime%2000*0.0005f );
		b->RenderMesh( 2, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
#endif // CSK_ADD_ITEM_CROSSSHIELD
#ifdef CSK_PCROOM_ITEM
	else if(Type >= MODEL_POTION+55 && Type <= MODEL_POTION+57)
	{
		//Vector(0.1f, 0.1f, 0.1f, b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME2,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		//b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif // CSK_PCROOM_ITEM
	else if(o->Type == MODEL_HELPER+49)
	{
		float sine = float(sinf(WorldTime*0.002f)*0.3f)+0.7f;
		b->RenderBody(RenderType,0.7f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,4,sine,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 0);
	}
	else if(o->Type == MODEL_HELPER+50)
	{
		float sine = float(sinf(WorldTime*0.00004f)*0.15f)+0.5f;
		b->RenderBody(RenderType,1.f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,0);
		b->RenderBody(RenderType,1.f,0.5f,sine,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
	}
	else if(o->Type == MODEL_HELPER+51)
	{
		float sine = float(sinf(WorldTime*0.002f)*0.3f)+0.7f;
		b->RenderBody(RenderType,0.7f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 0);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,sine,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
	}
	else if(Type == MODEL_POTION+64)
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fLumi = (sinf(WorldTime*0.001f) + 1.5f) * 0.25f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float PlaySpeed = 0.f;
		PlaySpeed = b->Actions[b->CurrentAction].PlaySpeed; 

		b->PlayAnimation(&o->AnimationFrame,&o->PriorAnimationFrame,&o->PriorAction,2.f/7.f,o->Position,o->Angle);
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight*1.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,Alpha,o->BlendMesh,o->BlendMeshLight/4.0f,WorldTime*0.005f,-WorldTime*0.005f,0);

		vec3_t Light;
		vec3_t vRelativePos, vWorldPos;
		Vector(0.f, 0.f, 0.f, vRelativePos);
		Vector(1.f, 0.f, 0.0f, Light);

		b->TransformPosition(BoneTransform[1], vRelativePos, vWorldPos, true);
		CreateSprite(BITMAP_LIGHT, vWorldPos, 3.f, Light, o, 0.f);
	}
	else if(o->Type == MODEL_HELPER+52)
	{
		b->RenderBody(RENDER_TEXTURE,0.9,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(o->Type == MODEL_HELPER+53)
	{
		b->RenderBody(RENDER_TEXTURE,0.9,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if (o->Type ==MODEL_POTION+65)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,
			o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi,
			o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_ITEM_EFFECT_DBSTONE_R);
	}
	else if (o->Type ==MODEL_POTION+66)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,
			o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi,
			o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_ITEM_EFFECT_HELLHORN_R);
	}
	else if (o->Type ==MODEL_POTION+67)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,
			o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi,
			o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_ITEM_EFFECT_PFEATHER_R);
	}
	else if (o->Type ==MODEL_POTION+68)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,
			o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.4f;
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, 1, fLumi,
			o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_ITEM_EFFECT_DEYE_R);
		b->RenderMesh(1, RENDER_CHROME|RENDER_BRIGHT, 0.2f, -1,
			o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#ifdef CSK_FREE_TICKET
	// ��������� ������ ȿ�� ó��
	else if(Type >= MODEL_HELPER+46 && Type <= MODEL_HELPER+48)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_FREETICKET_R);
	}
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
	// ī����ī�� ������ ȿ�� ó��
	else if(Type == MODEL_POTION+54)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHAOSCARD_R);
	}
#endif // CSK_CHAOS_CARD
#ifdef CSK_RARE_ITEM
	// ��;����� ȿ�� ó��
	else if(Type == MODEL_POTION+58)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM1_R);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_POTION+59)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM2_R);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_POTION+60)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM3_R);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_POTION+61)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM4_R);
	}
	else if(Type == MODEL_POTION+62)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM5_R);
	}
#endif // CSK_RARE_ITEM
#ifdef CSK_LUCKY_CHARM
	else if( o->Type == MODEL_POTION+53 )// ����� ����
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_LUCKY_CHARM_EFFECT53);
	}
#endif //CSK_LUCKY_CHARM
#ifdef CSK_LUCKY_SEAL
	else if( o->Type == MODEL_HELPER+43
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		|| o->Type == MODEL_HELPER+93	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
		)
	{
		float fLumi = (sinf(WorldTime*0.001f) + 1.5f) * 0.25f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_LUCKY_SEAL_EFFECT43);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if( o->Type == MODEL_HELPER+44
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
		|| o->Type == MODEL_HELPER+94	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL // �ű� ǳ���� ����
		|| o->Type == MODEL_HELPER+116
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
		)
	{
		float fLumi = (sinf(WorldTime*0.001f) + 1.5f) * 0.25f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_LUCKY_SEAL_EFFECT44);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if( o->Type == MODEL_HELPER+45 )
	{
		float fLumi = (sinf(WorldTime*0.001f) + 1.5f) * 0.25f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_LUCKY_SEAL_EFFECT45);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif //CSK_LUCKY_SEAL	
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	else if( o->Type >= MODEL_POTION+70 && o->Type <= MODEL_POTION+71 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0, RENDER_CHROME4, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif //PSW_ELITE_ITEM
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	else if( o->Type >= MODEL_POTION+72 && o->Type <= MODEL_POTION+77 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_SCROLL_ITEM
#ifdef PSW_SEAL_ITEM               // �̵� ����
	else if( o->Type == MODEL_HELPER+59 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_SEAL_ITEM
#ifdef PSW_FRUIT_ITEM              // ���� ����
	else if( o->Type >= MODEL_HELPER+54 && o->Type <= MODEL_HELPER+58 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_FRUIT_ITEM
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	else if( o->Type >= MODEL_POTION+78 && o->Type <= MODEL_POTION+82 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_SECRET_ITEM
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	else if( o->Type == MODEL_HELPER+60 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_INDULGENCE_ITEM

#ifdef PSW_CURSEDTEMPLE_FREE_TICKET
	else if( o->Type == MODEL_HELPER+61 )
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_FREETICKET_R);
	}
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
#ifdef PSW_RARE_ITEM
	else if( o->Type == MODEL_POTION+83)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM5_R);
	}
#endif //PSW_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	else if(o->Type == MODEL_POTION+145)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM7);
	}
	else if(o->Type == MODEL_POTION+146)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM8);
	}
	else if(o->Type == MODEL_POTION+147)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM9);
	}
	else if(o->Type == MODEL_POTION+148)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM10);
	}
	else if(o->Type == MODEL_POTION+149)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM11);
	}
	else if(o->Type == MODEL_POTION+150)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_RAREITEM12);
	}
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ���ð��� ��������� ������ ȿ�� ó��
	else if(Type == MODEL_HELPER+125)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_DOPPLEGANGGER_FREETICKET);
	}
	// �ٸ�ī ��������� ������ ȿ�� ó��
	else if(Type == MODEL_HELPER+126)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_BARCA_FREETICKET);
	}
	// �ٸ�ī ��7�� ��������� ������ ȿ�� ó��
	else if(Type == MODEL_HELPER+127)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_BARCA7TH_FREETICKET);
	}
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef PSW_CHARACTER_CARD 
	else if(Type == MODEL_POTION+91) // ĳ���� ī��
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_CHARACTERCARD_R);
	}
#endif // PSW_CHARACTER_CARD
#ifdef PSW_NEW_CHAOS_CARD
	else if(Type == MODEL_POTION+92) // ī����ī�� ���
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_NEWCHAOSCARD_GOLD_R);
	}
	else if(Type == MODEL_POTION+93) // ī����ī�� ����
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_NEWCHAOSCARD_RARE_R);
	}
	else if(Type == MODEL_POTION+95) // ī����ī�� �̴�
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_NEWCHAOSCARD_MINI_R);
	}
#endif // PSW_NEW_CHAOS_CARD
#ifdef PSW_NEW_ELITE_ITEM
	else if(Type == MODEL_POTION+94) // ����Ʈ �߰� ġ�� ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //PSW_NEW_ELITE_ITEM
#ifdef CSK_EVENT_CHERRYBLOSSOM
	// ȿ���� �� ��� �� ��� �� ������,,
	else if( Type==MODEL_POTION+84 )  // ���ɻ���
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+85 )  // ���ɼ�
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+86 )  // ���ɰ��
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+87 )  // ������
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+88 )  // ��� ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+89 )  // ������ ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type==MODEL_POTION+90 )  // ����� ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_ADD_PC4_SEALITEM
	else if(Type >= MODEL_HELPER+62 && Type <= MODEL_HELPER+63)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_ADD_PC4_SEALITEM
#ifdef PSW_ADD_PC4_SCROLLITEM
	else if(Type >= MODEL_POTION+97 && Type <= MODEL_POTION+98)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_ADD_PC4_SCROLLITEM
#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	else if( Type == MODEL_POTION+96 ) 
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		float fLumi = (sinf(WorldTime*0.0015f) + 1.5f) * 0.5f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif //PSW_ADD_PC4_CHAOSCHARMITEM
#ifdef LDK_ADD_PC4_GUARDIAN
	else if( Type == MODEL_HELPER+64  ) //����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
	}
	else if( Type == MODEL_HELPER+65 ) //��ȣ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
	}
#endif //LDK_ADD_PC4_GUARDIAN	
	else if( Type==MODEL_MACE+10
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)		//. ��ũ�ε������03
	{
        float Luminosity = WorldTime*0.0005f;

        o->HiddenMesh = 2; 
        o->BlendMesh  = 2;
        o->BlendMeshLight = 1.f;
		b->BeginRender(1.f);
		b->RenderBody ( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
		b->RenderMesh ( 2, RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, Luminosity, Luminosity );
		b->EndRender();
	}
	else if ( Type==MODEL_MACE+11 )		//. ��ũ�ε������04
	{
        o->BlendMeshLight = 1.f;
        o->BlendMeshTexCoordU = WorldTime*0.0008f;
		b->RenderBody ( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
        o->BlendMeshLight = sinf( WorldTime*0.001f )*0.3f+0.7f;
        b->RenderMesh ( 1, RENDER_BRIGHT|RENDER_CHROME, Alpha, 0, o->BlendMeshLight, 0.f, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_SWORD+20)		//. ���� �߰���
	{
//		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

		float Luminosity = sinf(WorldTime*0.0008f)*0.7f+0.5f;
		b->RenderMesh(2,RENDER_TEXTURE,Alpha,2,Luminosity,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		//. ��
		glColor3f(0.43f,0.14f,0.6f);

		b->RenderMesh(3,RENDER_BRIGHT|RENDER_CHROME,Alpha,3,o->BlendMeshLight,WorldTime*0.0001f,WorldTime*0.0005f);
		glColor3f(1.f,1.f,1.f);
	}
	else if(Type == MODEL_SWORD+21)		//. ���˻� �߰���
	{
//		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_TEXTURE,1.f,0,o->BlendMeshLight,WorldTime*0.0005f,WorldTime*0.0005f);
		o->HiddenMesh = 0;
		b->StreamMesh = 1;
		b->RenderMesh(1,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0005f);
	}
/*	else if(Type==MODEL_ARMOR+21 || Type==MODEL_GLOVES+21 || Type==MODEL_PANTS+21 || Type==MODEL_BOOTS+21 || Type==MODEL_HELM+21)   //  ����߰� ����
	{	//. ��� �߰�����
		//float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
		//Vector(0.9f+Luminosity*0.1f,Luminosity+0.4f-Luminosity*0.25f,Luminosity+0.1f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME3,0.3f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
	}*/
	else if(Type==MODEL_ARMOR+23 || Type==MODEL_GLOVES+23 || Type==MODEL_PANTS+23 || Type==MODEL_BOOTS+23 )
	{	//. ���˻� �߰�����
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
		Vector(Light[0]*0.3f,Light[1]*0.8f,Light[1]*1.f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		VectorCopy(Light,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
	else if(Type == MODEL_BOW+21 || Type == MODEL_STAFF+12 || Type == MODEL_MACE+14 || Type == MODEL_SWORD+22)
	{
		b->BeginRender(1.0f);

		b->StreamMesh = 0;
		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		if(Type == MODEL_SWORD+22)
		{
			b->BodyLight[0] = 1.0f;
			b->BodyLight[1] = 0.7f;
			b->BodyLight[2] = 0.4f;
			b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,(int)WorldTime%4000*0.0004f - 0.7f, o->BlendMeshTexCoordV, BITMAP_CHROME7);
			b->BodyLight[0] = 0.7f;
			b->BodyLight[1] = 0.7f;
			b->BodyLight[2] = 0.7f;
		}
		else if(Type == MODEL_STAFF+12)
			b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,(int)WorldTime%2000*0.0002f - 0.3f, (int)WorldTime%2000*0.0002f - 0.3f, BITMAP_CHROME_ENERGY);
		else
			b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,(int)WorldTime%4000*0.0002f - 0.3f, (int)WorldTime%4000*0.0002f - 0.3f, BITMAP_CHROME6);
		b->StreamMesh = -1;

		b->EndRender();
	}
	else if(Type == MODEL_SWORD+23)
	{
		b->RenderBody(RENDER_TEXTURE,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordU);
		float Luminosity = sinf(WorldTime*0.0015f)*0.03f + 0.3f;
		Vector(Luminosity,Luminosity,Luminosity+0.1f,b->BodyLight);
		b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,-2,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordU);

		o->Alpha = 0.5f;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        float Luminosity4 = sinf(WorldTime*0.0025f)*0.5f + 0.7f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		Vector(0.4f,0.4f,0.8f,b->BodyLight);
		b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,-2,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordU);
	}
	else if(Type == MODEL_ARMOR+31)
	{
		if(b->HideSkin == true)
		{
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);	
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);	
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);	
		}
	}
	else if(Type == MODEL_PANTS+31)
	{
		if(b->HideSkin == true)
		{
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);	
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);	
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);	
		}	
	}
	else if(Type == MODEL_SWORD+25)		//ũ���̿��� ���˻��
	{
		o->HiddenMesh = 1;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(1,RENDER_TEXTURE,0.5f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_LAVA);
		//b->RenderMesh(1,RENDER_TEXTURE,0.5f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,0.7f,1,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0009f);
	}
	else if(Type == MODEL_MACE+15)	//ũ���̿��� ��ũ�ε����
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_BOW+22)	// ����Ȱ
	{
		o->HiddenMesh = 1;
		// ��ä
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
		// ��� �κ�
		b->RenderMesh(1,RENDER_TEXTURE,1.0f,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		// ��ȫ��
		b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,1.0f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT|RENDER_CHROME5,0.5f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_STAFF+13)	// �渶���� ������
	{
		o->HiddenMesh = 1;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,1.0f,1,o->BlendMeshLight,WorldTime*0.0009f,WorldTime*0.0009f);
	}
	else if(Type == MODEL_ARMOR+36)	// ��������
	{
		if(b->HideSkin == true)
		{
			b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	else if(Type == MODEL_PANTS+36)
	{
		if(b->HideSkin == true)
		{
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	else if(Type == MODEL_GLOVES+36)
	{
		if(b->HideSkin == true)
		{
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	// ��ȯ���� ����� �����丮 � ���� �� ��, �Ӹ�ī���� �������� �ȵǹǷ� ������ ���� ���� ó��.
	// ��ȯ����� �Ӹ� ������Ʈ ������ �ٸ� ĳ���Ϳ� Ʋ��.
	else if (MODEL_HELM+39 <= Type && MODEL_HELM+44 >= Type
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)
	{
		if (b->HideSkin)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			int anMesh[6] = { 2, 1, 0, 2, 1, 2 };	// ������ �ؽ�ó ��ȣ �迭.(���̿÷����� ~ ���ͳ��� ��� ����)
			b->RenderMesh(anMesh[Type-(MODEL_HELM+39)], RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);		
	}

	else if (MODEL_ARMOR+39 <= Type && MODEL_ARMOR+44 >= Type
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)
	{
		if (b->HideSkin)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			int nTexture = Type - (MODEL_ARMOR+39);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_INVEN_ARMOR+nTexture);
			for (int i = 1; i < b->NumMeshs; ++i)
				b->RenderMesh(i, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
	else if (MODEL_PANTS+39 <= Type && MODEL_PANTS+44 >= Type
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)
	{
		if (b->HideSkin)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			int nTexture = Type - (MODEL_PANTS+39);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_INVEN_PANTS+nTexture);
			for (int i = 1; i < b->NumMeshs; ++i)
				b->RenderMesh(i, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
	else if (MODEL_GLOVES+44 == Type)	// ���ͳ����尩.
	{
		if (b->HideSkin)
		{
			::glColor3fv(b->BodyLight);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
#ifdef PBG_ADD_CHARACTERCARD
	//���� ��ũ ��ȯ���� ī��
	else if(MODEL_HELPER+97 == Type || MODEL_HELPER+98 == Type || MODEL_POTION+91 == Type)
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.4f;
		int _R_Type=0;
		switch(Type)
		{
		case MODEL_HELPER+97:			// ���˻� ī��
			_R_Type = BITMAP_CHARACTERCARD_R_MA;
			break;
		case MODEL_HELPER+98:			// ��ũ�ε� ī��
			_R_Type = BITMAP_CHARACTERCARD_R_DA;
			break;
		case MODEL_POTION+91:			// ��ȯ���� ī��
			_R_Type = BITMAP_CHARACTERCARD_R;
			break;
		default:
			break;
		}
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, _R_Type);
	}
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	else if(MODEL_HELPER+99 == Type)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
	//Ȱ���Ǻ��(���ϱ�/�ϱ�/�߱�/���)
	else if(MODEL_HELPER+117 <= Type && MODEL_HELPER+120 >= Type)
	{
#ifndef PBG_MOD_SECRETITEM
		if(Type == MODEL_HELPER+117)
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
#endif //PBG_MOD_SECRETITEM
		{
			b->RenderMesh(1, RENDER_CHROME6|RENDER_BRIGHT, o->Alpha*0.5f, 1, o->BlendMeshLight*0.1f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, 0, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		}
	}
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_FIX_ELSEIF_BLOCK_BREAK_AT_RENDER_PART_OBJECT_BODY_FUNC
	else
	{
		bIsNotRendered = TRUE;
	}
	// if-else�� �ʹ� ���Ƽ� �ɰ���
	// �� ���� else �߰����� ������!!!!!
	if (bIsNotRendered == FALSE);	// �̹� �׸� �̹����� �׸��� �ʴ´�.
#endif	// YDG_FIX_ELSEIF_BLOCK_BREAK_AT_RENDER_PART_OBJECT_BODY_FUNC
#ifdef ADD_SOCKET_ITEM
	// �����(����)/��ť����(��ȯ����) ���ʰ� ������ �κ��丮����Render�� Texture�� ��ü�Ѵ�.
	// - �� �����۵��� �޽ð� ������������ �ʾұ� ���� 
	//   ���������� �޽ø� �����⿡�� �������� �ʹ� �����ϰ� ���������ϱ� ������ 
	//   �ϳ��� �޽÷� ����� �κ��丮���� �ؽ��ĸ� ��ü �ϴ¹������ ó��

	// ����� ����/����, ��ť���� ����/����
	else if ( Type==MODEL_ARMOR+50 || Type==MODEL_PANTS+50 || Type==MODEL_ARMOR+53 || Type==MODEL_PANTS+53)
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int nTexture = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int nTexture;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		switch( Type )
		{
		case MODEL_ARMOR+50:	nTexture = BITMAP_SKIN_ARMOR_DEVINE; break;
		case MODEL_PANTS+50:	nTexture = BITMAP_SKIN_PANTS_DEVINE; break;
		case MODEL_ARMOR+53:	nTexture = BITMAP_SKIN_ARMOR_SUCCUBUS; break;
		case MODEL_PANTS+53:	nTexture = BITMAP_SKIN_PANTS_SUCCUBUS; break;
		}
		if (b->HideSkin)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, nTexture);
			for (int i = 1; i < b->NumMeshs; ++i)
			{
				b->RenderMesh(i, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			}
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		}
	}

	// �޽� �����

	// �������︧
	else if( Type == MODEL_HELM+49 )
	{
		if(b->HideSkin == true)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}	
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	// �����˰���
	else if( Type == MODEL_ARMOR+49 )
	{
		if(b->HideSkin == true)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}	
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	// ����� ��Ʈ
	else if( Type == MODEL_HELM+50 )
	{
		if(b->HideSkin == true)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}	
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
	// ��ť���� ��Ʈ
	else if( Type == MODEL_HELM+53 )
	{
		if(b->HideSkin == true)
		{
			::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
			b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}	
		else
		{
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, o->HiddenMesh);		
		}
	}
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	else if(Type == MODEL_SPEAR+11)		//�׺� ���� ��
	{
		::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
		b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(4,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(5,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		
		//��ü
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,0.4f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		//Į��
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,0.8f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_MACE+18)	//�׺� ���� ����
	{
		::glColor3fv(b->BodyLight);	// �κ��丮 â���� +ȿ�� ����.
		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(3,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(4,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(5,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(6,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		//���� �Ӹ� ���� �κ�
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,0.5f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //LDK_ADD_GAMBLERS_WEAPONS
	else if(Type==MODEL_BOW+20)			//. ���� �߰�Ȱ
	{
		float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
		b->BeginRender(1.f);
		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(0,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(2,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(6,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		//. ����
		b->RenderMesh(3,RENDER_TEXTURE,1.f,3,Luminosity,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		//. ����
		b->RenderMesh(4,RENDER_TEXTURE,1.f,4,Luminosity,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		//. �ݹ���
		glColor3f(1.f,1.f,1.f);
		b->RenderMesh(5,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		
        b->EndRender ();
	}
	else if(Type==MODEL_POTION+28)		//. �Ҿ���� ����
	{
		glColor3f(1.f,1.f,1.f);
		Models[o->Type].StreamMesh = 1;
		b->RenderMesh(1,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0005f);
		Models[o->Type].StreamMesh = -1;
		b->RenderMesh(0,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type==MODEL_POTION+29)		//. ����� ǥ��
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		b->StreamMesh = 1;
		b->RenderMesh(1,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.0005f);
		b->StreamMesh = -1;

		Vector(1.f,0.5f,0.f,b->BodyLight);
		static float fMeshLight = 0.500f;
		static float fAdd = 0.01f;
		if(fMeshLight > 1.f) {
			fMeshLight = 1.00f;
			fAdd = -0.01f;
		}
		if(fMeshLight < 0.01f) {
			fMeshLight = 0.01f;
			fAdd = 0.01f;
		}
		b->RenderMesh(2,RENDER_TEXTURE,1.0f,2,fMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		fMeshLight += fAdd;

		glColor3f(1.f,1.f,1.f);
		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderMesh(0,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_CHROME|RENDER_BRIGHT,0.3f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if (Type == MODEL_STAFF+11)	// ����� ������
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		b->RenderMesh(1,RENDER_CHROME|RENDER_BRIGHT,Alpha,1, 0.2f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );

        glColor3f ( 1.f, 1.f, 1.f );
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,Alpha,0,sinf(WorldTime*0.005f),o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		b->RenderMesh(0,RENDER_CHROME4|RENDER_BRIGHT,Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
	}
	else if (Type == MODEL_STAFF+18)	// ����н�ƽ
	{
		b->RenderBody(RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, 1, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if (Type == MODEL_STAFF+19)	// ���������ƽ
	{
		b->RenderBody(RenderType, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		float fLumi = (sinf(WorldTime*0.002f) + 0.5f) * 0.5f;
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, 1, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
    else if ( Type==MODEL_MACE+12 )     //  ��ũ�ε� ����5.
    {
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		b->RenderMesh ( 1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, 1, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		b->RenderMesh ( 3, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, 3, 1.f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
    }
	else if ( Type==MODEL_SHIELD+15
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		&& !(RenderType & RENDER_DOPPELGANGER)
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
		)	// �׷��� �ҿ� ���� ȿ��
	{
		b->BeginRender(1.f);

		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
        Vector(Light[0]*0.3f,Light[1]*0.3f,Light[2]*0.3f,b->BodyLight);
		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(2,RENDER_COLOR, 1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		VectorCopy(Light, b->BodyLight);
		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(2,RENDER_CHROME|RENDER_BRIGHT, 1.f,2,o->BlendMeshLight,o->BlendMeshTexCoordU,WorldTime*0.01f,BITMAP_CHROME);
		b->RenderMesh(0,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,1.f, 1,o->BlendMeshLight,(float)(rand()%10)*0.1f,(float)(rand()%10)*0.1f);

		float Luminosity = sinf( WorldTime*0.001f )*0.4f+0.6f;
        Vector(Light[0]*Luminosity,Light[0]*Luminosity,Light[0]*Luminosity,b->BodyLight);
		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,1.f,2,o->BlendMeshLight,WorldTime*0.0001f,WorldTime*0.0005f);
		b->EndRender();
	}
	else if ( Type==MODEL_SHIELD+16 )	// ������Ż ���� ȿ��
	{
		b->BeginRender(1.f);
		glColor4f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2], 0.8f);
		b->RenderMesh(1,RENDER_TEXTURE,0.8f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		glColor4f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2], 0.5f);
		b->RenderMesh(3,RENDER_TEXTURE,0.5f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		glColor3f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2]);
		b->RenderMesh(0,RENDER_TEXTURE,1.f,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(2,RENDER_TEXTURE,1.f, 2,o->BlendMeshLight,WorldTime*0.0005f,o->BlendMeshTexCoordV);
		b->RenderMesh(3,RENDER_TEXTURE,1.f, 3,o->BlendMeshLight,(float)(rand()%10)*0.1f,(float)(rand()%10)*0.1f);
		b->EndRender();
	}
	else if (Type == MODEL_BOW+3 && (RenderType&RENDER_EXTRA))	// �ı��� ��ũ�ü� Ȱ �� �˰�
	{
		RenderType -= RENDER_EXTRA;
		Vector(0.1f,0.1f,0.1f,b->BodyLight);
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
    else if ( Type==MODEL_ANGEL && b->NumMeshs )
    {
		b->RenderBody ( RENDER_TEXTURE, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        if ( RenderType&RENDER_CHROME )
        {
            Vector ( 0.75f, 0.55f, 0.5f, b->BodyLight );
		    b->RenderMesh ( 0, RENDER_CHROME4|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
		    b->RenderMesh ( 0, RENDER_CHROME|RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        }
    }
    else if ( Type==MODEL_POTION+7 )    //  ����� ����.//���ƹ���
    {
        b->BeginRender( 1.f );
        if ( o->HiddenMesh==1 )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            b->RenderMesh ( 0, RENDER_TEXTURE, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
            Vector ( 0.1f, 0.5f, 1.f, b->BodyLight );
            b->RenderMesh ( 0, RENDER_METAL|RENDER_BRIGHT, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
            b->RenderMesh ( 0, RENDER_CHROME|RENDER_BRIGHT, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        }
        else if ( o->HiddenMesh==0 )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            b->RenderMesh ( 1, RENDER_TEXTURE, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
            Vector ( 0.1f, 0.5f, 1.f, b->BodyLight );
            b->RenderMesh ( 1, RENDER_METAL|RENDER_BRIGHT, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
            b->RenderMesh ( 1, RENDER_CHROME|RENDER_BRIGHT, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        }
        b->EndRender ();
    }
    else if ( Type==MODEL_HELPER+7 )    //  ��� ����.
    {
        b->BeginRender( 1.f );
        if ( o->HiddenMesh==1 )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            b->RenderMesh ( 0, RENDER_TEXTURE, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        }
        else if ( o->HiddenMesh==0 )
        {
            glColor3f ( 1.f, 1.f, 1.f );
            Vector ( 1.f, 1.f, 1.f, b->BodyLight );
            b->RenderMesh ( 1, RENDER_TEXTURE, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        }
        b->EndRender ();
    }
    else if ( Type==MODEL_HELPER+11 )   //  �ֹ���.
    {
        b->BeginRender( 1.f );
        glColor3f ( 1.f, 1.f, 1.f );
        Vector ( 1.f, 1.f, 1.f, b->BodyLight );
        b->RenderMesh ( 0, RENDER_TEXTURE, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        Vector ( 0.f, 0.5f, 1.f, b->BodyLight );
        b->RenderMesh ( 1, RENDER_CHROME|RENDER_BRIGHT, 1.f, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
        b->EndRender ();
    }
	else if ( Type==MODEL_BOW+7 || Type==MODEL_BOW+15)
	{
		if( g_isCharacterBuff(o, eBuff_InfinityArrow) )
		{
			Vector(1.f, 0.8f, 0.2f, b->BodyLight);
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			b->RenderBody(RENDER_CHROME|RENDER_BRIGHT,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		}
		else
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		}
	}
#if defined PCROOM_EVENT
	else if (o->m_bpcroom == TRUE 
		&& (Type == MODEL_HELM+9 || Type == MODEL_ARMOR+9 || Type == MODEL_PANTS+9
		|| Type == MODEL_GLOVES+9 || Type == MODEL_BOOTS+9)
		)
	{
			if(Type == MODEL_ARMOR+9)
			{
				vec3_t EndRelative, EndPos;
				Vector(0.f, 0.f, 0.f, EndRelative);

				b->TransformPosition(o->BoneTransform[0],EndRelative,EndPos,true);

				Vector(0.4f, 0.6f, 0.8f, o->Light);
				CreateSprite(BITMAP_LIGHT, EndPos, 6.0f, o->Light, o, 0.5f);

				float Luminosity;
				Luminosity = sinf(WorldTime*0.05f)*0.4f+0.9f;
				Vector(Luminosity*0.3f,Luminosity*0.5f,Luminosity*0.8f,o->Light);
				CreateSprite(BITMAP_LIGHT, EndPos, 2.0f, o->Light, o);
			}

			vec3_t Light;
			VectorCopy(b->BodyLight, Light);
			Vector(0.9f, 0.7f, 1.0f, b->BodyLight);

			
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_FENRIR_THUNDER);
			b->RenderMesh(0,RENDER_BRIGHT|RENDER_METAL,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_FENRIR_THUNDER);
			VectorCopy(Light, b->BodyLight);
	}
#endif	// PCROOM_EVENT
	else if( Type == MODEL_POTION+42 || Type == MODEL_POTION+43 || Type == MODEL_POTION+44 )
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if ( Type >= MODEL_WING+60 && Type <= MODEL_WING+65)	// �õ�
	{
		int iCategoryIndex = Type - (MODEL_WING+60) + 1;
		switch(iCategoryIndex)
		{
		case 1:	// 0~9
			Vector(0.9f, 0.1f, 0.2f, b->BodyLight);
			break;
		case 2:	// 10~15
			Vector(0.4f, 0.5f, 1.0f, b->BodyLight);
			break;
		case 3:	// 16~20
			Vector(1.0f, 1.0f, 1.0f, b->BodyLight);
			break;
		case 4:	// 21~28
			Vector(0.4f, 1.0f, 0.6f, b->BodyLight);
			break;
		case 5:	// 29~33
			Vector(1.0f, 0.8f, 0.4f, b->BodyLight);
			break;
		case 6:	// 34~40
			Vector(1.0f, 0.4f, 1.0f, b->BodyLight);
			break;
		}
	    b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	    b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
	else if ( Type >= MODEL_WING+100 && Type <= MODEL_WING+129)	// �õ� ���Ǿ�
	{
 		b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		
		int iCategoryIndex = (Type - (MODEL_WING+100)) % 6 + 1;
		switch(iCategoryIndex)
		{
		case 1:	// 0~9
			Vector(0.9f, 0.1f, 0.2f, b->BodyLight);
			break;
		case 2:	// 10~15
			Vector(0.4f, 0.5f, 1.0f, b->BodyLight);
			break;
		case 3:	// 16~20
			Vector(1.0f, 1.0f, 1.0f, b->BodyLight);
			break;
		case 4:	// 21~28
			Vector(0.4f, 1.0f, 0.6f, b->BodyLight);
			break;
		case 5:	// 29~33
			Vector(1.0f, 0.8f, 0.4f, b->BodyLight);
			break;
		case 6:	// 34~40
			Vector(1.0f, 0.4f, 1.0f, b->BodyLight);
			break;
		}
	    b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
	    b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
	//�׺� ���� ������ __ �� ��ȣ ���� �ؾߵ�
	else if ( Type==MODEL_HELPER+71 || Type==MODEL_HELPER+72 || Type==MODEL_HELPER+73 || Type==MODEL_HELPER+74 || Type==MODEL_HELPER+75)
	{
		int _angle = int(b->BodyAngle[1])%360;
		float _meshLight1;
		if( 0 < _angle && _angle <= 180 )
		{
			_meshLight1 = 0.2f - (sinf(Q_PI*(_angle)/180.0f) * 0.2f);
		}
		else 
		{
			_meshLight1 = 0.2f;
		}
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, 0.35f, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 1, _meshLight1, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		b->RenderMesh(2, RENDER_TEXTURE, o->Alpha, 2, _meshLight1, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
#endif //LDK_ADD_GAMBLE_RANDOM_ICON

	// ����Ʈ �ذ����� �� ������
	else if(o->Kind==KIND_PLAYER && o->Type==MODEL_PLAYER && o->SubType==MODEL_SKELETON_PCBANG)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		vec3_t Light;
		VectorCopy(b->BodyLight, Light);
		Vector(0.9f, 0.8f, 1.0f, b->BodyLight);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_FENRIR_THUNDER);
		b->RenderBody(RENDER_BRIGHT|RENDER_METAL,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_FENRIR_THUNDER);
		VectorCopy(Light, b->BodyLight);
	}
	else if( o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_CURSEDTEMPLE_ALLIED_PLAYER )
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 1);

		if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint) || g_isCharacterBuff(o, eBuff_CursedTempleProdection) )
		{
			vec3_t vRelativePos, vtaWorldPos, Light;
			Vector(0.4f, 0.4f, 0.8f, Light);
			Vector(0.f, 0.f, 0.f, vRelativePos);

			if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint) )
			{
				float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
				b->RenderMesh(1, RENDER_TEXTURE,0.4f+Luminosity,0,o->BlendMeshLight*Luminosity,-WorldTime*0.0005f,WorldTime*0.0005f);
			}

			int boneindex[15] = {1, 2, 17, 18, 19, 20, 44, 25, 27, 34, 37, 3, 5, 10, 12 }; 
			
			for ( int j = 0; j < 15; ++j )
			{
				b->TransformPosition(o->BoneTransform[boneindex[j]],vRelativePos,vtaWorldPos,true);
				CreateSprite(BITMAP_LIGHT,vtaWorldPos,1.3f,Light,o);
			}
		}

		if(o->m_pCloth == NULL)
		{
			int iTex = BITMAP_CURSEDTEMPLE_ALLIED_PHYSICSCLOTH;
			CPhysicsCloth *pCloth = new CPhysicsCloth [1];
			pCloth[0].Create( o, 19, 0.0f, 8.0f, 0.0f, 10, 10, 140.0f, 140.0f, iTex, iTex, PCT_CURVED | PCT_SHORT_SHOULDER | PCT_MASK_ALPHA );
			o->m_pCloth = ( void*)pCloth;
			o->m_byNumCloth = 1;			
		}
		CPhysicsCloth *pCloth = (CPhysicsCloth*)o->m_pCloth;
		if(pCloth)
		{
			float Flag = 0.005f;

			if( g_isCharacterBuff(o, eDeBuff_Stun) || g_isCharacterBuff(o, eDeBuff_Sleep) ) 
			{
				Flag = 0.0f;
			}

			for( int k = 0; k < o->m_byNumCloth; ++k )
			{
				if(pCloth[k].Move2( Flag, 5) == FALSE)
				{
					DeleteCloth(NULL, o);
				}
				else
				{
					pCloth[k].Render();
				}
			}
		}
	}
	else if( o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_CURSEDTEMPLE_ILLUSION_PLAYER )
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 2);

		if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint) || g_isCharacterBuff(o, eBuff_CursedTempleProdection) )
		{
			vec3_t vRelativePos, vtaWorldPos, Light;
			Vector(0.4f, 0.4f, 0.8f, Light);
			Vector(0.f, 0.f, 0.f, vRelativePos);

			if( g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint) )
			{
				float Luminosity = sinf(WorldTime*0.002f)*0.3f+0.5f;
				b->RenderMesh(2, RENDER_TEXTURE,0.4f+Luminosity,0,o->BlendMeshLight*Luminosity,-WorldTime*0.0005f,WorldTime*0.0005f);
			}

			int boneindex[15] = {1, 2, 17, 18, 19, 20, 44, 25, 27, 34, 37, 3, 5, 10, 12 }; 
			
			for ( int j = 0; j < 15; ++j )
			{
				b->TransformPosition(o->BoneTransform[boneindex[j]],vRelativePos,vtaWorldPos,true);
				CreateSprite(BITMAP_LIGHT,vtaWorldPos,1.3f,Light,o);
			}
		}

		if(o->m_pCloth == NULL)
		{
			int iTex = BITMAP_CURSEDTEMPLE_ILLUSION_PHYSICSCLOTH;
			CPhysicsCloth* pCloth = new CPhysicsCloth[2];
			pCloth[0].Create(o, 20, -4.0f, 5.0f, 0.0f, 10, 20, 17.0f, 100.0f, iTex, iTex, PCT_SHAPE_HALLOWEEN | PCT_ELASTIC_HALLOWEEN | PCT_MASK_ALPHA);
			o->m_pCloth = (void*)pCloth;
			o->m_byNumCloth = 1;			
		}
		CPhysicsCloth *pCloth = (CPhysicsCloth*)o->m_pCloth;
		if(pCloth)
		{
			float Flag = 0.005f;

			if( g_isCharacterBuff(o, eDeBuff_Stun) || g_isCharacterBuff(o, eDeBuff_Sleep) ) 
			{
				Flag = 0.0f;
			}

			for (int k = 0; k < o->m_byNumCloth; ++k)
			{
				if(pCloth[k].Move2( Flag, 5) == FALSE)
				{
					DeleteCloth(NULL, o);
				}
				else
				{
					pCloth[k].Render();
				}
			}
		}
	}
	else if(o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_HALLOWEEN)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		// �к� ȿ��
		vec3_t vLight;
		Vector(1.f, 1.f, 1.f, vLight);
		vec3_t vPos, vRelativePos;
		Vector(6.f, 6.f, 0.f, vRelativePos);
		VectorCopy(o->Position,b->BodyOrigin);
		b->TransformPosition(o->BoneTransform[20], vRelativePos, vPos, true);
		vPos[2] += 36.f;
		if(rand()%2 == 0)
		{
			CreateParticle(BITMAP_TRUE_FIRE, vPos, o->Angle, vLight, 8, 0.5f, o);
		}
		CreateParticle(BITMAP_TRUE_FIRE, vPos, o->Angle, vLight, 9, 0.5f, o);
		// flare01
		vPos[2] -= 5.0f;
		float fLumi;
		fLumi = (float)(rand()%5+10) * 0.1f;
		Vector(fLumi+0.5f, fLumi*0.3f+0.1f, 0.f, vLight);
		CreateSprite(BITMAP_LIGHT, vPos, 1.0f+fLumi*0.1f, vLight, o);
		// shiny01
		if(rand()%8 == 0)
		{
			vPos[2] -= 10.0f;
			fLumi = (float)(rand()%100) * 0.01f;
			vLight[0] = fLumi;
			fLumi = (float)(rand()%100) * 0.01f;
			vLight[1] = fLumi;
			fLumi = (float)(rand()%100) * 0.01f;
			vLight[2] = fLumi;
			CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 4, 0.8f);
		}

		// ����Ʈ
		if(o->CurrentAction == PLAYER_JACK_1)
		{
			int iAnimationFrame = (int)o->AnimationFrame;

			if(iAnimationFrame == 2 || iAnimationFrame == 9)
			{
				Vector(1.f, 1.f, 1.f, vLight);
				vPos[2] -= 20.f;
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 0, 0.6f);
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 0, 0.6f);
				for(int i=0; i<20; ++i)
				{
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[0] = fLumi;
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[1] = fLumi;
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[2] = fLumi;
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 4, 0.8f);
				}
				o->m_iAnimation++;
			}

			if(o->m_iAnimation >= 40 && iAnimationFrame == 9)
			{
				Vector(1.f, 1.f, 1.f, vLight);
				CreateEffect(MODEL_HALLOWEEN_EX, vPos, o->Angle, vLight, 0);
				vPos[2] -= 40.f;
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 1);
				SetAction(o, PLAYER_SHOCK);
				SendRequestAction(PLAYER_SHOCK,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				o->m_iAnimation = 0;
			}

			float fStageG, fStageB;
			fStageG = 0.8f - ((o->m_iAnimation / 40.f) * 0.8f);
			if(fStageG < 0.2f)
			{
				fStageG = 0.2f;
			}
			fStageB = 0.8f - ((o->m_iAnimation / 40.f) * 0.9f);
			if(fStageB < 0.1f)
			{
				fStageB = 0.1f;
			}
			VectorCopy(b->BodyLight, vLight);
			Vector(1.f, fStageG, fStageB, b->BodyLight);
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			VectorCopy(vLight, b->BodyLight);
		}
		else if(o->CurrentAction == PLAYER_JACK_2)
		{
			int iAnimationFrame = (int)o->AnimationFrame;

			if(iAnimationFrame == 10 || iAnimationFrame == 19)
			{
				Vector(1.f, 1.f, 1.f, vLight);
				vPos[2] -= 20.f;
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 0, 0.6f);
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 0, 0.6f);
				for(int i=0; i<20; ++i)
				{
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[0] = fLumi;
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[1] = fLumi;
					fLumi = (float)(rand()%100) * 0.01f;
					vLight[2] = fLumi;
					CreateParticle(BITMAP_SHINY, vPos, o->Angle, vLight, 4, 0.8f);
				}
				o->m_iAnimation++;
			}

			if(o->m_iAnimation >= 40 && iAnimationFrame == 19)
			{
				Vector(1.f, 1.f, 1.f, vLight);
				CreateEffect(MODEL_HALLOWEEN_EX, vPos, o->Angle, vLight, 0);
				vPos[2] -= 40.f;
				CreateParticle(BITMAP_SPARK+2, vPos, o->Angle, vLight, 1);
				SetAction(o, PLAYER_SHOCK);
				SendRequestAction(PLAYER_SHOCK,((BYTE)((o->Angle[2]+22.5f)/360.f*8.f+1.f)%8));
				o->m_iAnimation = 0;
			}

			float fStageG, fStageB;
			fStageG = 0.8f - ((o->m_iAnimation / 40.f) * 0.8f);
			if(fStageG < 0.2f)
			{
				fStageG = 0.2f;
			}
			fStageB = 0.8f - ((o->m_iAnimation / 40.f) * 0.9f);
			if(fStageB < 0.1f)
			{
				fStageB = 0.1f;
			}
			VectorCopy(b->BodyLight, vLight);
			Vector(1.f, fStageG, fStageB, b->BodyLight);
			b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			VectorCopy(vLight, b->BodyLight);
		}

		// ���÷�//3������
		if(o->m_pCloth == NULL)
		{
			int iTex = BITMAP_ROBE+3;
			CPhysicsCloth* pCloth = new CPhysicsCloth[1];
			pCloth[0].Create(o, 19, 0.0f, 10.0f, 0.0f, 10, 20, 30.0f, 200.0f, iTex, iTex, PCT_SHAPE_HALLOWEEN | PCT_ELASTIC_HALLOWEEN | PCT_MASK_ALPHA);
			o->m_pCloth = (void*)pCloth;
			o->m_byNumCloth = 1;
		}
		CPhysicsCloth *pCloth = (CPhysicsCloth*)o->m_pCloth;
		if(pCloth)
		{
			if(pCloth[0].Move2( 0.005f, 5) == FALSE)
			{
				DeleteCloth(NULL, o);
			}
			else
			{
				pCloth[0].Render();
			}
		}
	}
#ifdef PJH_ADD_PANDA_CHANGERING
	
	else if(o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_PANDA)
	{
		vec3_t Light;
		vec3_t vPos;

		Vector(1.f,0.6f,0.2f,Light);
		if(rand()%100 == 0)
		{
			CreateEffect( MODEL_ARROWSRE06, vPos, o->Angle, Light, 2, o, 0,0,0,0,1.f );
			CreateEffect( MODEL_ARROWSRE06, vPos, o->Angle, Light, 2, o, 1,0,0,0,1.f );
		}

		float fLumi = (sinf(WorldTime*0.002f) + 1.f) * 0.5f;
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 1,fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_PANDABODY_R);
		b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(3, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

		int iAnimationFrame = (int)o->AnimationFrame;
#ifdef _VS2008PORTING
		static int iPriorAnimationFrame = 0;
#else // _VS2008PORTING
		static iPriorAnimationFrame = 0;
#endif // _VS2008PORTING
		iPriorAnimationFrame = iAnimationFrame;
	}
#endif //PJH_ADD_PANDA_CHANGERING
	else if(o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_XMAS_EVENT_CHANGE_GIRL)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		int iAnimationFrame = (int)o->AnimationFrame;
#ifdef _VS2008PORTING
		static int iPriorAnimationFrame = 0;
#else // _VS2008PORTING
		static iPriorAnimationFrame = 0;
#endif // _VS2008PORTING

		if(o->CurrentAction == PLAYER_SANTA_1)
		{
			if(iAnimationFrame == 4 || iAnimationFrame == 8 || iAnimationFrame == 12)
			{
				int iEffectType = rand()%4 + MODEL_XMAS_EVENT_BOX;
				vec3_t vPos;
				vec3_t vLight;
				Vector(1.f, 1.f, 1.f, vLight);
				VectorCopy(o->Position, vPos);
				vPos[2] += 230.f;
				for(int i=0; i<2; ++i)
				{
					CreateEffect(iEffectType, vPos, o->Angle, o->Light);
					CreateParticle(BITMAP_SPARK+1, vPos, o->Angle, o->Light, 20, 1.f);
				}
#ifdef _VS2008PORTING
				for(int i=0; i<5; ++i)
#else // _VS2008PORTING
				for(i=0; i<5; ++i)
#endif // _VS2008PORTING
				{
					CreateParticle(BITMAP_SPARK+1, vPos, o->Angle, vLight, 20, 1.f);
				}
			}
			if(iAnimationFrame >= 19 && iPriorAnimationFrame != iAnimationFrame)
			{
				o->m_iAnimation++;
			}
		}
		else if(o->CurrentAction == PLAYER_SANTA_2)
		{
			vec3_t vPos, vLight;
			VectorCopy(o->Position, vPos);
			vPos[2] += 230;
			Vector(1.f, 1.f, 1.f, vLight);
			CreateParticle(BITMAP_SPARK+1, vPos, o->Angle, vLight, 20, 1.f);
			CreateParticle(BITMAP_SMOKE, vPos, o->Angle, vLight, 4, 2.0f);
			if(rand()%6 == 0)
			{
				CreateParticle(BITMAP_SNOW_EFFECT_1,vPos,o->Angle,vLight, 0, 0.3f);
			}
			if(rand()%3 == 0)
			{
				CreateParticle(BITMAP_SNOW_EFFECT_2,vPos,o->Angle,vLight, 0, 0.5f);
			}

			if(iAnimationFrame >= 14 && iPriorAnimationFrame != iAnimationFrame)
			{
				o->m_iAnimation++;
				DeleteEffect(MODEL_XMAS_EVENT_ICEHEART, NULL);
				DeleteParticle(BITMAP_DS_EFFECT);
				DeleteParticle(BITMAP_LIGHT);
			}
		}

		iPriorAnimationFrame = iAnimationFrame;
	}
	else if(o->SubType == MODEL_XMAS_EVENT_CHA_DEER)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float fLumi = (sinf(WorldTime*0.002f) + 1.f) * 0.5f;
		b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_BLOOD+1);
		b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_BLOOD+1);
		b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,1,fLumi,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_BLOOD+1);
	}
	else if(o->Kind == KIND_PLAYER && o->Type == MODEL_PLAYER && o->SubType == MODEL_GM_CHARACTER)
	{
		o->HiddenMesh = 2;
		b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(2,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

		vec3_t vRelativePos, vPos, vLight, vLight2;
		float fLight;
		fLight = sinf(WorldTime*0.08f)*0.2f+0.2f;
		
		Vector(0.f, 0.3f, 1.2f, vLight);
		Vector(0.3f+fLight, 0.f+fLight, 0.1f+fLight, vLight2);

		Vector(0.f, 0.f, -7.5f, vRelativePos);
		b->TransformPosition(o->BoneTransform[26], vRelativePos, vPos, true);
		CreateSprite(BITMAP_SHINY+1, vPos, 0.9f, vLight, o, -WorldTime*0.08f);
		CreateSprite(BITMAP_LIGHT+3, vPos, 0.8f, vLight2, o, WorldTime*0.3f);

		Vector(0.f, 0.f, 7.5f, vRelativePos);
		b->TransformPosition(o->BoneTransform[35], vRelativePos, vPos, true);
		CreateSprite(BITMAP_SHINY+1, vPos, 0.9f, vLight, o, WorldTime*0.08f);
		CreateSprite(BITMAP_LIGHT+3, vPos, 0.8f, vLight2, o, -WorldTime*0.3f);

		Vector(-5.f, 2.5f, 0.f, vRelativePos);
		b->TransformPosition(o->BoneTransform[5], vRelativePos, vPos, true);
		CreateSprite(BITMAP_SHINY+1, vPos, 0.9f, vLight, o, -WorldTime*0.08f);
		CreateSprite(BITMAP_LIGHT+3, vPos, 0.8f, vLight2, o, WorldTime*0.3f);

		b->TransformPosition(o->BoneTransform[12], vRelativePos, vPos, true);
		CreateSprite(BITMAP_SHINY+1, vPos, 0.9f, vLight, o, -WorldTime*0.08f);
		CreateSprite(BITMAP_LIGHT+3, vPos, 0.8f, vLight2, o, WorldTime*0.3f);
	}
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	else if ( Type == MODEL_HELPER+69 )	// ��Ȱ�� ����
	{
	    b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float Luminosity = (sinf(WorldTime*0.003f)+1)*0.3f+0.3f;
	    b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,Luminosity,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	else if ( Type == MODEL_HELPER+70 )	// �̵��� ����
	{
	    b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	    b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	    b->RenderMesh(1, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif	// YDG_ADD_CS5_PORTAL_CHARM
#ifdef ASG_ADD_CS6_GUARD_CHARM
	else if (Type == MODEL_HELPER+81)	// ��ȣ�Ǻ���
	{
		b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(0, RENDER_BRIGHT|RENDER_CHROME, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);		
	}
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	else if (Type == MODEL_HELPER+82)	// �����ۺ�ȣ����
	{
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef PBG_ADD_SANTAINVITATION
	else if ( Type == MODEL_HELPER+66 )	// ��Ÿ������ �ʴ���
	{
		//�ܰ��������� ũ�� ȿ���� �ش�.
 		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
 		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME4,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	
		//���� ���׶����� ��⸦ ��Ӱ� �ߴٰ� ��� �ߴٰ�.	0.6~0.8���̸� �Դٰ���.(0.1->0.3Ƽ�� �ȳ�.)
		float Luminosity = (sinf(WorldTime*0.003f)+1)*0.3f+0.6f;
		b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,Luminosity,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //PBG_ADD_SANTAINVITATION
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	else if(Type == MODEL_POTION+100)	//����� ����
	{
		//�޽��Ѱ�¥��..
		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING
	else if( o->Type >= MODEL_TYPE_CHARM_MIXWING+EWS_BEGIN 
		&& o->Type <= MODEL_TYPE_CHARM_MIXWING+EWS_END ) // ���� ���� 100% ���� ����
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH		// ������ ���� (�Ϻ� 6�� ������)
	else if(Type == MODEL_HELPER+96)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	else if(Type == MODEL_HELPER+107)	// ġ��������
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
 		b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	else if(Type == MODEL_HELPER+104)
	{
		// AG���� ����
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,0.2f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	else if(Type == MODEL_HELPER+105)
	{
		// SD���� ����
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,0.2f,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#if defined(LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST) 
	else if( o->Type >= MODEL_HELPER+109 && o->Type <= MODEL_HELPER+112 )	// InGameShop ���� ������ : ���� (�����̾�, ���, ������, �ڼ���)
	{	
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
 		b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ) || defined(LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST) 
#if defined(LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD) || defined(LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE) // �ű� ���(������) �����	// MODEL_HELPER+113
	else if( o->Type >= MODEL_HELPER+113 && o->Type <= MODEL_HELPER+115 )// InGameShop ���� ������ : ����� (�����̾�, ���, ���޶���)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
 		b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE	// �ű� �����̾�(���) �����	// MODEL_HELPER+115	
#if defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD) // Ű(�ǹ�), Ű(���)
	else if( o->Type >= MODEL_POTION+112 && o->Type <= MODEL_POTION+113 )// InGameShop ���� ������ : Ű(�ǹ�), Ű(���)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // defined(LDS_ADD_INGAMESHOP_ITEM_KEYSILVER) || defined(LDS_ADD_INGAMESHOP_ITEM_KEYGOLD) // Ű(�ǹ�), Ű(���)
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD //�����ȭ
	else if( o->Type == MODEL_POTION+120 )
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#if defined LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST || defined LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST // ��� �ݻ�����, ��������
	else if( o->Type == MODEL_POTION+121 || o->Type == MODEL_POTION+122 )
	{
		// 0 �ڹ���
		// 1 �ݼ� �׵θ�
		// 2 ���� �κ�
		// 3 ��罽
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //defined LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST || defined LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#if defined LDK_ADD_INGAMESHOP_GOLD_CHEST || defined LDK_ADD_INGAMESHOP_SILVER_CHEST // �ݻ�����, ��������
	else if( o->Type == MODEL_POTION+123 || o->Type == MODEL_POTION+124 )
	{
		// 0 �ڹ���
		// 1 �ݼ� �׵θ�
		// 2 ���� �κ�
		// 3 ��罽
		b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(2,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //defined LDK_ADD_INGAMESHOP_GOLD_CHEST || defined LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING
	else if (o->Type == MODEL_WING+130) //���� ������ ����
	{
		if (b->BodyLight[0] == 1 && b->BodyLight[1] == 1 && b->BodyLight[2] == 1)	// �κ��丮
		{
			Vector(1.f,1.f,1.f,b->BodyLight);
			glColor3fv(b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
	}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
	else if( o->Type == MODEL_POTION+134 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_RED);
	}
	else if( o->Type == MODEL_POTION+135 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_BLUE);
	}
	else if( o->Type == MODEL_POTION+136 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_GOLD);
	}
	else if( o->Type == MODEL_POTION+137 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_GREEN);
	}
	else if( o->Type == MODEL_POTION+138 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_PUPLE);
	}
	else if( o->Type == MODEL_POTION+139 )
	{
		//b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_PACKAGEBOX_SKY);
	}
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
	else if( o->Type >= MODEL_POTION+114 && o->Type <= MODEL_POTION+119 )
	{
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_INGAMESHOP_PRIMIUM6);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
	else if( o->Type >= MODEL_POTION+126 && o->Type <= MODEL_POTION+129 )
	{
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_INGAMESHOP_COMMUTERTICKET4);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	else if( o->Type >= MODEL_POTION+130 && o->Type <= MODEL_POTION+132 )
	{
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, BITMAP_INGAMESHOP_SIZECOMMUTERTICKET3);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	else if( o->Type == MODEL_HELPER+121 )
	{
		float fLumi = (sinf(WorldTime*0.0015f) + 1.2f) * 0.3f;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, BITMAP_FREETICKET_R);
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE	// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
	else if( Type == MODEL_PANTS +18 )				// Hero::�渶���� ���ҿ� ����, �׷���ҿ� ���� ��.
	{
		if( o->Type == MODEL_PANTS +18 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderMesh(0,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			b->RenderMesh(1,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);		
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type == MODEL_PANTS +22 )
	{
		if( o->Type == MODEL_PANTS +22 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderMesh(0,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
			b->RenderMesh(1,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);	
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
#ifdef PBG_ADD_GENSRANKING
	else if(Type >= MODEL_POTION+141 && Type <= MODEL_POTION+144)
	{
		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //PBG_ADD_GENSRANKING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	else if (Type == MODEL_HELPER+122)	// ���̷��� ���Ź���
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,0.5f,0, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#ifdef LDK_ADD_14_15_GRADE_ITEM_MODEL
	else if(o->Type == MODEL_15GRADE_ARMOR_OBJ_ARMLEFT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_ARMRIGHT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_BODYLEFT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_BODYRIGHT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_BOOTLEFT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_BOOTRIGHT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_HEAD ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_PANTLEFT ||
			o->Type == MODEL_15GRADE_ARMOR_OBJ_PANTRIGHT )
	{
		float fLight,texCoordU;

		fLight = 0.8f - absf( sinf ( WorldTime*0.0018f ) * 0.5f);
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,fLight-0.1f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		texCoordU = absf( sinf ( WorldTime*0.0005f ));
		b->RenderMesh(0,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,fLight-0.3f,texCoordU,o->BlendMeshTexCoordV,BITMAP_RGB_MIX);		
 		b->RenderMesh(0,RENDER_TEXTURE|RENDER_CHROME4,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //LDK_ADD_14_15_GRADE_ITEM_MODEL
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	else if( Type == MODEL_HELPER+128 || Type == MODEL_HELPER+129 )	// ��������
	{
		float fEyeBlinkingTime = sinf(WorldTime*0.005f)+1;
		
		b->RenderBody(RENDER_TEXTURE,1.0f,o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderMesh(0,RENDER_BRIGHT|RENDER_CHROME,0.3f, o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1, fEyeBlinkingTime,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	else if( Type >= MODEL_HELPER+130 && Type <= MODEL_HELPER+133 )	// ��ũ��, ����ũ��, ��������, ����������
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		glColor3fv(b->BodyLight);
		b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		float Luminosity = absf(sinf(WorldTime*0.001f))*0.3f;
		Vector(0.1f + Luminosity, 0.1f + Luminosity, 0.1f + Luminosity, b->BodyLight);
		b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		Luminosity = absf(sinf(WorldTime*0.001f))*0.8f;
		Vector(0.0f + Luminosity, 0.0f + Luminosity, 0.0f + Luminosity, b->BodyLight);
		
		switch(Type)
		{
			case MODEL_HELPER+130:	// ��ũ��
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_ORK_CHAM_LAYER_R);
				break;
			case MODEL_HELPER+131:	// ��������
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_MAPLE_CHAM_LAYER_R);
				break;
			case MODEL_HELPER+132:	// ����ũ��
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOLDEN_ORK_CHAM_LAYER_R);
				break;
			case MODEL_HELPER+133:	// ����������
				b->RenderMesh(1,RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_GOLDEN_MAPLE_CHAM_LAYER_R);
				break;
			default:
				break;
		}
	}
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type == MODEL_WING+49 || Type == MODEL_WING+135)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_WING+50)
	{
		if(b->BodyLight[0] == 1 && b->BodyLight[1] == 1 && b->BodyLight[2] == 1)
		{
			Vector(1.f,1.f,1.f,b->BodyLight);
			glColor3fv(b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else
		{
			Vector(1.f,1.f,1.f,b->BodyLight);
			glColor3fv(b->BodyLight);
			b->RenderMesh(0,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
	}
	else if(Type == MODEL_HELM+59 || Type == MODEL_HELM+60)
	{
		if(b->HideSkin)
		{
			::glColor3fv(b->BodyLight);
			b->RenderMesh(1, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
	else if(Type == MODEL_HELM+61)
	{
		if(b->HideSkin)
		{
			::glColor3fv(b->BodyLight);
			b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);
	}
	else if((g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+32)		// �巹��ٿ
		|| (g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+33)		// Ÿ�̰���Ŭ��
		|| (g_CMonkSystem.EqualItemModelType(Type) == MODEL_SWORD+34))		// �Ǿ���÷��̵�
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	}
	else if(Type>=MODEL_ETC+30 && Type<=MODEL_ETC+36)
	{
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		float fLumi = (sinf(WorldTime*0.0015f) + 1.0f) * 0.5f;
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT, o->Alpha, 0, fLumi, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh, BITMAP_ROOLOFPAPER_EFFECT_R);
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef PBG_ADD_NEWCHAR_MONK
	else if(Type == MODEL_BODY_ARMOR+(MAX_CLASS*2)+CLASS_RAGEFIGHTER || Type == MODEL_BODY_PANTS+(MAX_CLASS*2)+CLASS_RAGEFIGHTER
		|| Type == MODEL_BODY_GLOVES+(MAX_CLASS*2)+CLASS_RAGEFIGHTER || Type == MODEL_BODY_BOOTS+(MAX_CLASS*2)+CLASS_RAGEFIGHTER)
	{
		const char* pSkinTextureName = "LevelClass207_1";
		int nLen = strlen(pSkinTextureName);
		for(int i=0; i<b->NumMeshs; ++i)
		{
			Texture_t* pTexture = &b->Textures[i];
			int SkinTexture = (!strnicmp(pTexture->FileName, pSkinTextureName, nLen)) ? BITMAP_SKIN+14 : -1;
			b->RenderMesh(i,RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, SkinTexture);
		}
	}
#endif //PBG_ADD_NEWCHAR_MONK
#ifdef LEM_ADD_LUCKYITEM		// ��Ű������ ������
	else if( Check_LuckyItem( Type, -MODEL_ITEM ) )
 	{
		bool	bHide	= false;
		int		nIndex	= 0;
		if		( Type == MODEL_HELM+65 )	nIndex = 2;
		else if ( Type == MODEL_HELM+70 )	nIndex = 1;
		if( nIndex > 0 )					bHide = true;

		
		if( bHide )
		{
			b->RenderMesh( nIndex, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
		}
		else if( b->HideSkin )
		{
			if		( Type == MODEL_ARMOR+65 )	nIndex = BITMAP_INVEN_ARMOR+6;
			else if ( Type == MODEL_ARMOR+70 )	nIndex = BITMAP_INVEN_ARMOR+7;
			else if ( Type == MODEL_PANTS+65 )	nIndex = BITMAP_INVEN_PANTS+6;
			else if ( Type == MODEL_PANTS+70 )	nIndex = BITMAP_INVEN_PANTS+7;

			if( nIndex > 0 )
			{
				b->RenderMesh(0, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, nIndex );
				for (int i = 1; i < b->NumMeshs; ++i)
					b->RenderMesh(i, RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
			}
			else	b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);	
		}
		else
		{
			b->RenderBody(RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh);	
		}
	}
#endif // LEM_ADD_LUCKYITEM
	else
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
}

#ifdef CSK_ADD_GOLDCORPS_EVENT
void RenderPartObjectBodyColor(BMD *b,OBJECT *o,int Type,float Alpha,int RenderType,float Bright,int Texture, int iMonsterIndex)
#else // CSK_ADD_GOLDCORPS_EVENT
void RenderPartObjectBodyColor(BMD *b,OBJECT *o,int Type,float Alpha,int RenderType,float Bright,int Texture)
#endif // CSK_ADD_GOLDCORPS_EVENT
{
#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif //MR0

#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	if(Type >= MODEL_HELM_MONK && Type <= MODEL_BOOTS_MONK + MODEL_ITEM_COMMONCNT_RAGEFIGHTER)
		Type = g_CMonkSystem.OrginalTypeCommonItemMonk(Type);
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

	if((RenderType&RENDER_LIGHTMAP) == RENDER_LIGHTMAP)
	{
        Vector(1.f,1.f,1.f,b->BodyLight);
	}
    else if(Type==MODEL_MONSTER01+54)   //  ���. ����ٲٱ�
    {
		if ( RenderType&RENDER_EXTRA)
		{
			RenderType-=RENDER_EXTRA;
			Vector(1.f,0.1f,0.1f,b->BodyLight);
		}
		else
		{
			Vector(0.2f,0.2f,0.8f,b->BodyLight);
			//Vector(1.0f,0.5f,0.0f,b->BodyLight);
		}
    }
#ifdef CSK_ADD_GOLDCORPS_EVENT
#ifdef KJH_FIX_GOLD_RABBIT_INDEX
	else if(iMonsterIndex >= 493 && iMonsterIndex <= 502)
#else // KJH_FIX_GOLD_RABBIT_INDEX
	else if(iMonsterIndex >= 492 && iMonsterIndex <= 501)
#endif // KJH_FIX_GOLD_RABBIT_INDEX
	{
		// ���ο� �ٵ����Ʈ ����
		if(iMonsterIndex == 495)
		{
			Vector(1.0f, 0.8f, 0.0f, b->BodyLight);
		}
		else if(iMonsterIndex == 496)
		{
			Vector(1.0f, 0.6f, 0.0f, b->BodyLight);
		}
		else if(iMonsterIndex == 499)
		{
			Vector(1.0f, 0.5f, 0.0f, b->BodyLight);
		}
		else if(iMonsterIndex == 501)
		{
			Vector(1.0f, 0.5f, 0.0f, b->BodyLight);
		}
		else
		{
			Vector(1.f, 0.6f, 0.1f, b->BodyLight);
		}
	}
#endif // CSK_ADD_GOLDCORPS_EVENT
	else
	{	//. Į�����
		PartObjectColor(Type,Alpha,Bright,b->BodyLight, (RenderType&RENDER_EXTRA) ? true : false );
	}

	if ( Type==MODEL_MACE+7 )
	{
		o->HiddenMesh = 2;
	}

	if(Type==MODEL_STAFF+5)//������
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,Texture);
	else if(Type == MODEL_SWORD+20)		//. ���� �߰���
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,Texture);
	else if(Type == MODEL_SWORD+21)		//. ���˻� �߰���
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,0,Texture);
	else if ( Type==MODEL_SWORD+31 || Type==MODEL_SPEAR+10 || Type==MODEL_MACE+7 || Type==MODEL_SHIELD+16 )
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,Texture);
	else if ( Type>=MODEL_MACE+8 && Type<=MODEL_MACE+13 )
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,Texture);
#ifdef ADD_SOCKET_ITEM
	else if( Type == MODEL_SWORD+26 )	// �ö�������
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV, 5 );
	}
	else if( Type == MODEL_SWORD+27 )	// �ҵ�극��Ŀ
	{
		// Į������
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_SWORD+28 )	// ��ٽ�Ÿ��
	{
		// 2�� �޽� �κи� ����(Į���κ�)
		//* RenderType = RENDER_BRIGHT|RENDER_CHROME
 		b->RenderMesh( 2, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_STAFF+30 )	// ���鸮������
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);

		// Į���κ�
		o->BlendMesh =1;
		Vector(1.f, 1.f, 1.f, b->BodyLight);
		b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_STAFF+32 )	// �ҿ�긵��
	{
		// Į���κ� (soketel_soulbringer.jpg)
		b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
 	else if( Type == MODEL_SHIELD+19 )	// ���ν�Ʈ�踮��
 	{
 		// ���ڰ� �κ�
 		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
 	}
	else if( Type == MODEL_SHIELD+20 )	// �����ǵ�
	{
		// �Һ��� ���ºκ�
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_HELM+49 )		// ������ �︧
	{
		b->RenderMesh(0,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type == MODEL_HELM+50 )		// ����� �︧
	{
		b->RenderMesh(1,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type == MODEL_HELM+53 )		// ��ť���� �︧
	{
		b->RenderMesh(2,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // ADD_SOCKET_ITEM
#ifdef CSK_ADD_ITEM_CROSSSHIELD
	else if(Type == MODEL_SHIELD+21)
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
#endif // CSK_ADD_ITEM_CROSSSHIELD
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	else if(Type == MODEL_SPEAR+11)		//�׺� ���� ��
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
		b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_STAFF+33)		//�׺� ���� ������
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_STAFF+34)		//�׺� ���� ��ƽ
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_MACE+18)		//�׺� ���� ����
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if(Type == MODEL_BOW+24)		//�׺� ���� Ȱ
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
#endif //LDK_ADD_GAMBLERS_WEAPONS
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
	else if(Type == MODEL_PANTS +18)	// ���� �׷���ҿ� ���� ���� ó��	// �κ��丮â ������ // �۾���.
	{
		if( o->Type == MODEL_PANTS +18 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );		
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_PANTS +22)	// ���� ���ҿ� ���� ���� ó��
	{
		if( o->Type == MODEL_PANTS +22 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		}
		else
		{
			b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );		
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type >= MODEL_SWORD+32 && Type <= MODEL_SWORD+34)		// ��ũ���
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_HELM+59 || Type == MODEL_HELM+60)
	{
		::glColor3fv(b->BodyLight);
		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_HELM+61)
	{
		::glColor3fv(b->BodyLight);
		b->RenderMesh(0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+59)
	{
 		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+60)
	{
		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+61)
	{
		b->RenderMesh(0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
	}

	if ( Type==MODEL_MACE+7 )
	{
		o->HiddenMesh = -1;
	}

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
}

void RenderPartObjectBodyColor2(BMD *b,OBJECT *o,int Type,float Alpha,int RenderType,float Bright,int Texture)
{
#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif //MR0
	
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	if(Type >= MODEL_HELM_MONK && Type <= MODEL_BOOTS_MONK + MODEL_ITEM_COMMONCNT_RAGEFIGHTER)
		Type = g_CMonkSystem.OrginalTypeCommonItemMonk(Type);
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

	if((RenderType&RENDER_LIGHTMAP) == RENDER_LIGHTMAP)
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
	}
    else if ( (RenderType&RENDER_CHROME3)==RENDER_CHROME3 )
    {
        PartObjectColor3(Type,Alpha,Bright,b->BodyLight, (RenderType&RENDER_EXTRA) ? true : false );
    }
	else
	{	//. Į�����
		PartObjectColor2(Type,Alpha,Bright,b->BodyLight, (RenderType&RENDER_EXTRA) ? true : false );
	}
	if(Type==MODEL_STAFF+5)//������
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,Texture);
	else if (Type == MODEL_SWORD+20)		//. ���� �߰���
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,Texture);
	else if (Type == MODEL_SWORD+21)
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,0,Texture);
	else if (Type==MODEL_SHIELD+15 || Type==MODEL_SHIELD+16)
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
	else if(Type==MODEL_HELPER+50)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1,Texture);
	}
	else if (Type==MODEL_POTION+64)
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,0,Texture);
	}
#ifdef ADD_SOCKET_ITEM
	else if( Type == MODEL_SWORD+26 )		// �ö�������
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,5,Texture);
	}
	else if( Type == MODEL_SHIELD+19 )	// ���ν�Ʈ�踮��
	{
		b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
	}
	else if( Type == MODEL_HELM+49 )		// ������ �︧
	{
		b->RenderMesh(0,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type == MODEL_HELM+50 )		// ����� �︧
	{
		b->RenderMesh(1,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if( Type == MODEL_HELM+53 )		// ��ť���� �︧
	{
		b->RenderMesh(2,RenderType,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
#endif // ADD_SOCKET_ITEM
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
	else if(Type == MODEL_PANTS +18)	// ���� �׷���ҿ� ���� ���� ó��
	{
		if( o->Type == MODEL_PANTS +18 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
		}
		else
		{
			b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );		
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
	}
	else if(Type == MODEL_PANTS +22)	// ���� ���ҿ� ���� ���� ó��
	{
		if( o->Type == MODEL_PANTS +22 )
		{
			b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
		}
		else
		{
			b->RenderMesh( 0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );
			b->RenderMesh( 1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV );	
		}

//		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
	}
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(Type >= MODEL_SWORD+32 && Type <= MODEL_SWORD+34)		// ��ũ���
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_HELM+59 || Type == MODEL_HELM+60)
	{
		::glColor3fv(b->BodyLight);
		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_HELM+61)
	{
		::glColor3fv(b->BodyLight);
		b->RenderMesh(0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+59)
	{
		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+60)
	{
		b->RenderMesh(1, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
	else if(Type == MODEL_ARMOR+61)
	{
		b->RenderMesh(0, RenderType, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else
	{
		b->RenderBody(RenderType,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,Texture);
	}

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
}

#ifdef LDK_ADD_14_15_GRADE_ITEM_MODEL
///////////////////////////////////////////////////////////////////////////////
// 14, 15 ���� ȿ�� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////
#define MAX_GRADE_OBJ 2 //�������� �ٴ� obj�� �߰��Ǹ� �÷��ּ���.
void NextGradeObjectRender(CHARACTER *c)
{
	int weaponIndex;
	int weaponIndex2;
	BMD *b = &Models[c->Object.Type];
	vec3_t vRelativePos, vPos, vLight;
	float fLight2,fScale;
	int Level;
	PART_t *w;

	//����
	for(int i=0; i<2; i++)
	{
		w = &c->Weapon[i];
		Level = w->Level;
		if( Level < 15 || w->Type == -1) continue;

		if(MODEL_BOW <= w->Type && w->Type <MODEL_STAFF)
		{
			weaponIndex = 27; //������ : ����
			weaponIndex2 = 28; //������ : �޼�
		}
		else
		{
			weaponIndex = (i == 0 ? 27 : 36); //������ : ����
			weaponIndex2 = (i == 0 ? 28 : 37); //������ : �޼�
		}

		switch(Level)
		{
		case 15:
			{
				// ��
				Vector(0.0f, 0.0f, 0.0f, vRelativePos);
				b->TransformByObjectBone(vPos, &c->Object, weaponIndex, vRelativePos);
				Vector(1.0f, 0.6f, 0.0f, vLight);
				CreateSprite( BITMAP_LIGHT, vPos, 0.6f, vLight, &c->Object );
				
				Vector(10.0f, 0.0f, 0.0f, vRelativePos);
				b->TransformByObjectBone(vPos, &c->Object, weaponIndex, vRelativePos);
				Vector(1.0f, 0.6f, 0.0f, vLight);
				CreateSprite( BITMAP_LIGHT, vPos, 0.6f, vLight, &c->Object );
				
				Vector(20.0f, 0.0f, 0.0f, vRelativePos);
				b->TransformByObjectBone(vPos, &c->Object, weaponIndex, vRelativePos);
				Vector(1.0f, 0.6f, 0.0f, vLight);
				CreateSprite( BITMAP_LIGHT, vPos, 0.6f, vLight, &c->Object );
				
				// ��
				Vector(10.0f, 0.0f, 0.0f, vRelativePos);
				b->TransformByObjectBone(vPos, &c->Object, weaponIndex2, vRelativePos);
				
				fLight2 = absf( sinf ( WorldTime*0.002f ));
				Vector(0.7f*fLight2+0.3f, 0.1f*fLight2+0.1f, 0.0f, vLight);
 				CreateSprite(BITMAP_MAGIC, vPos, 0.35f, vLight, &c->Object); //�� �׵θ�
				
				Vector(1.0f, 1.0f, 1.0f, vLight);
				fScale = (float)(rand()%60)*0.01f;
				CreateSprite( BITMAP_FLARE_RED, vPos, 0.6f*fScale+0.4f, vLight, &c->Object );

				Vector(1.0f, 0.2f, 0.0f, vLight);
				fScale = (float)(rand()%80+10)*0.01f*1.0f;
				CreateParticle(BITMAP_LIGHTNING_MEGA1+rand()%3,vPos,c->Object.Angle,vLight,0, fScale);	// ����
			}break;
		}//switch

	} //for

	//��
	int bornIndex[MAX_GRADE_OBJ]; // left, right;
	int gradeType[MAX_GRADE_OBJ]; // left, right;
	
	for(int k=0; k<MAX_BODYPART; k++)
	{
		w = &c->BodyPart[k];
		Level = w->Level;
		
		if( k == 0 ) continue; //����
		if( Level < 15 || w->Type == -1) continue;

		switch( k )
		{
		case 1://MODEL_HELM <= w->Type && w->Type < MODEL_ARMOR 15��� ���� �� ����
			{
				bornIndex[0] = 20;
				bornIndex[1] = -1;
				gradeType[0] = MODEL_15GRADE_ARMOR_OBJ_HEAD;
				gradeType[1] = -1;
			}break;
		case 2:// MODEL_ARMOR <= w->Type && w->Type < MODEL_PANTS 15��� ���� �� ����
			{
				bornIndex[0] = 35;
				bornIndex[1] = 26;
				gradeType[0] = MODEL_15GRADE_ARMOR_OBJ_BODYLEFT;
				gradeType[1] = MODEL_15GRADE_ARMOR_OBJ_BODYRIGHT;
			}break;
		case 3://MODEL_PANTS <= w->Type && w->Type < MODEL_GLOVES) 15��� ���� �� ����
			{
				bornIndex[0] = 3;
				bornIndex[1] = 10;
				gradeType[0] = MODEL_15GRADE_ARMOR_OBJ_PANTLEFT;
				gradeType[1] = MODEL_15GRADE_ARMOR_OBJ_PANTRIGHT;
			}break;
		case 4://MODEL_GLOVES <= w->Type && w->Type < MODEL_BOOTS 15��� ���� �� �尩
			{
				bornIndex[0] = 36;
				bornIndex[1] = 27;
				gradeType[0] = MODEL_15GRADE_ARMOR_OBJ_ARMLEFT;
				gradeType[1] = MODEL_15GRADE_ARMOR_OBJ_ARMRIGHT;
			}break;
		case 5://MODEL_BOOTS <= w->Type && w->Type < MODEL_WING 15��� ���� �� ����
			{
				bornIndex[0] = 4;
				bornIndex[1] = 11;
				gradeType[0] = MODEL_15GRADE_ARMOR_OBJ_BOOTLEFT;
				gradeType[1] = MODEL_15GRADE_ARMOR_OBJ_BOOTRIGHT;
			}break;
		default:
			bornIndex[0] = -1;
			bornIndex[1] = -1;
			gradeType[0] = -1;
			gradeType[1] = -1;
			break;
		}

		OBJECT *o = &c->Object;

		for(int m=0; m<MAX_GRADE_OBJ; m++)
		{
			if(gradeType[m] == -1) continue;
			
			switch(Level)
			{
			case 15: // +15
				{
					// �� ��ũ
					w->LinkBone = bornIndex[m];
					RenderLinkObject(0.f, 0.f, 0.f, c, w, gradeType[m], 0, 0, true, true);

					// ����Ʈ
					b->TransformByBoneMatrix(vPos, BoneTransform[0], o->Position);
					
					fLight2 = absf( sinf ( WorldTime*0.01f ));
					Vector(0.2f*fLight2, 0.4f*fLight2, 1.0f*fLight2, vLight);
					CreateSprite(BITMAP_MAGIC, vPos, 0.12f, vLight, o);
					
					Vector(0.4f, 0.7f, 1.0f, vLight);
#ifdef LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
					CreateSprite(BITMAP_SHINY+6, vPos, 0.4f, vLight, o);
#else // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
					CreateSprite(BITMAP_SHINY+5, vPos, 0.4f, vLight, o);
#endif // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
					
					Vector(0.1f, 0.3f, 1.0f, vLight);
					CreateSprite(BITMAP_PIN_LIGHT, vPos, 0.6f, vLight, o, 90.0f);
				}break;
			}
		}

	} //for
}
#endif //LDK_ADD_14_15_GRADE_ITEM_MODEL

///////////////////////////////////////////////////////////////////////////////
// �������� ���� �ٸ� ȿ���� �������� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

extern float g_Luminosity;

void RenderPartObjectEffect(OBJECT *o,int Type,vec3_t Light,float Alpha,int ItemLevel,int Option1,int ExtOption,int Select,int RenderType)
{	
	int Level = (ItemLevel>>3)&15;
	if ( RenderType & RENDER_WAVE)
	{
		Level = 0;
	}
	BMD *b = &Models[Type];

    if ( o->EnableShadow==true )
    {
		if(World == 7)
		{
			EnableAlphaTest();
			glColor4f(0.f,0.f,0.f,0.2f);
		}
		else
		{
			DisableAlphaBlend();
			glColor3f(0.f,0.f,0.f);
		}
#ifdef USE_SHADOWVOLUME
		//�ɸ���
		//CShadowVolume *pShadowVolume = new CShadowVolume;
		//pShadowVolume->Create( VertexTransform, b, o);
		//InsertShadowVolume( pShadowVolume);
#else
        bool bRenderShadow = true;

        if ( InHellas() )
        {
            bRenderShadow = false;
        }

		if ( WD_10HEAVEN == World || o->m_bySkillCount==3 || g_Direction.m_CKanturu.IsMayaScene() )
        {
            bRenderShadow = false;
        }

		if( g_isCharacterBuff(o, eBuff_Cloaking ) )
        {
            bRenderShadow = false;
        }

		
		if ( bRenderShadow )
		{
            //  �׸��ڸ� ������, ������ �����Ѵ�.
			if ( o->m_bRenderShadow )    //  10FPS�̻��� ������ �׸��ڸ� ǥ���Ѵ�.
		    {
				// MR0 Renderer�� ShadowMiss Define 
#ifdef LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH		// LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
				ModelManager::SetTargetObject(o);
#endif // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH

#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
				int iHiddenMesh = o->HiddenMesh;

				if( o->Type == MODEL_MONSTER01+116 )
				{
					iHiddenMesh = 2;
				}
				else if(o->Type == MODEL_MONSTER01+164 )	// ���� ��ȣ�� ���̿� ī������ ������ �׸��� ��� ��ŵ.
				{
					iHiddenMesh = 0;
				}
				
				b->RenderBodyShadow(o->BlendMesh,iHiddenMesh);
				
#else // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
				if(o->Type == MODEL_MONSTER01+116)
				{
					b->RenderBodyShadow(o->BlendMesh, 2);	
				}
				else
				{
					b->RenderBodyShadow(o->BlendMesh,o->HiddenMesh);
				}
#endif // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
				
#ifdef LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH		// LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
				ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
            }
		}
        return;
    }
#endif


	switch(Type)
	{
    case MODEL_HELPER+3:Level = 8;break;	// ����Ʈ
	// ���Ź��� ���� �Է�
	case MODEL_HELPER+39:Level = 13;break;	// ����Ʈ �ذ����� ���Ź���
	case MODEL_HELPER+40:Level = 13;break;	// �ҷ��� �̺�Ʈ ���Ź���
	case MODEL_HELPER+41:Level = 13;break;	// ũ�������� �̺�Ʈ ���Ź���
	case MODEL_POTION+51:Level = 13;break;	// ũ���������� ��
	case MODEL_HELPER+42:Level = 13;break;	// GM ���Ź��� ���� 13
#ifdef CSK_PCROOM_ITEM
	//case MODEL_POTION+55:Level = 8;break;
#endif // CSK_PCROOM_ITEM
	case MODEL_HELPER+10:Level = 8;break;	// ���Ź���
    case MODEL_HELPER+30:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case MODEL_WING+49:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		Level = 0;break;   // ������ ����.
    case MODEL_EVENT+16: Level = 0;break;   // ������ �Ҹ�.
	case MODEL_POTION+13:	// �ູ�Ǻ���
	case MODEL_POTION+14:	// ��ȥ�Ǻ���
	case MODEL_POTION+16:	// �����Ǻ���
	case MODEL_POTION+31:	// ��ȣ�Ǻ���
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	case MODEL_WING+136:	// ������ ���� ����
	case MODEL_WING+138:	// ��ȣ�� ���� ����
	case MODEL_WING+141:	// ȥ���� ���� ����

#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	case MODEL_COMPILED_CELE:
	case MODEL_COMPILED_SOUL:
	case MODEL_WING+15:Level = 8;break;	// ȥ���Ǻ���
	case MODEL_WING+36:
	case MODEL_WING+37:
	case MODEL_WING+38:
	case MODEL_WING+39:
	case MODEL_WING+40:
#ifdef ADD_ALICE_WINGS_1
	case MODEL_WING+41:
    case MODEL_WING+42:
    case MODEL_WING+43:
#endif	// ADD_ALICE_WINGS_1
    case MODEL_WING+3:
    case MODEL_WING+4:
    case MODEL_WING+5:
    case MODEL_WING+6:
	case MODEL_WING:
	case MODEL_WING+1:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case MODEL_WING+50:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	case MODEL_WING+2:Level = 0;break;	//����
	case MODEL_WING+7:Level = 9;break;	//ȸ�������ⱸ��
	case MODEL_WING+11:Level = 0;break;	//��ȯ����
    case MODEL_WING+12: //��ų����
    case MODEL_WING+13:
    case MODEL_WING+16:
    case MODEL_WING+17:
    case MODEL_WING+18:
    case MODEL_WING+19:
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	case MODEL_WING+44:	// �ı����ϰݱ���
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	case MODEL_WING+45:	// ��Ƽ�� ����
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	case MODEL_WING+46:	// ȸ�� ����
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	case MODEL_WING+47:
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
		{
			Level = 9;
			break;
		}
    case MODEL_WING+14:
		Level = 9;
		break;
	case MODEL_POTION+12:
		Level = 8;
		break;//�̹�Ʈ ������
	case MODEL_POTION+17://�Ǹ��� ��
	case MODEL_POTION+18://�Ǹ��� ����
	case MODEL_POTION+19://���������� �ʴ��
		{
			if(Level <= 6)
			{
				Level *= 2;
			}
			else
			{
				Level = 13;
			}
		}
		break;
	case MODEL_POTION+20:Level = 9;break;//����� ����
    case MODEL_POTION+22:Level = 8;break;//â���� ����.
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX	// â���� ���� ����
	case MODEL_WING+137:Level = 8;break;
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
    case MODEL_POTION+25:Level = 8;break;//�����Ǵ���.
    case MODEL_POTION+26:Level = 8;break;//��������ȥ.
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	case MODEL_WING+139:
	case MODEL_WING+140:
	case MODEL_WING+142:
	case MODEL_WING+143:
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	case MODEL_POTION+41:
		Level = 0;break;//��ȭ�Ǻ���(����)
	case MODEL_POTION+42:
		Level = 0;break;//��ȭ�Ǻ���(����)
	case MODEL_POTION+43:
		Level = 0;break;//�ϱ� ���ü�
	case MODEL_POTION+44:
		Level = 0;break;//��� ���ü�
	case MODEL_HELPER+50:
	case MODEL_POTION+64:
		Level = 0;break;
	case MODEL_HELPER+52:
	case MODEL_HELPER+53:
		Level = 0;break;
	case MODEL_EVENT+4:Level = 0;break;//����ǻ���/��ź�Ǻ�
	case MODEL_EVENT+6:
		if (Level == 13)	// ��ũ�ε��� ����
		{
			Level = 13;
		}
		else
		{
			Level = 9;
		}
		break;//����� ��Ʈ
	case MODEL_EVENT+7:Level = 0;break;//����� �ø���
	case MODEL_EVENT+8:Level = 0;break;//�� ����
	case MODEL_EVENT+9:Level = 8;break;//�� ����
#ifdef _PVP_ADD_MOVE_SCROLL
	case MODEL_POTION+10:Level = 0;break;//�̵�����
#endif	// _PVP_ADD_MOVE_SCROLL
    case MODEL_EVENT+5: //  ������ �ָӴ�/����.
        {
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
            Level = 9;
#else
            Level = 0;
#endif
        }
        break;
#ifdef USE_EVENT_ELDORADO
	case MODEL_EVENT+10:
		Level = (Level - 8) * 2 + 1;
		break;	// ������
#endif
#ifdef ANNIVERSARY_EVENT
	case MODEL_POTION+11:
		if (Level >= 1 && Level <= 5) Level = 7;
        else Level = 9;
		break;
#endif	// ANNIVERSARY_EVENT
    case MODEL_EVENT+11:
        Level--;
        break;
	case MODEL_EVENT+12:	//. ������ ����
		Level = 0;
		break;
	case MODEL_EVENT+13:	//. ��ũ����
		Level = 0;
		break;
	case MODEL_EVENT+14:	//. ������ ����
		Level += 7;
		break;
	case MODEL_EVENT+15:	// �������� ����
		Level = 8;
		break;
#ifdef CHINA_MOON_CAKE
    case MODEL_EVENT+17:
		Level = 0;
        break;
#endif	//  CHINA_MOON_CAKE
	case MODEL_EVENT:
	case MODEL_EVENT+1:Level = 8;break;//�̹�Ʈ ������
    case MODEL_BOW+7: Level>=1?Level=Level*2+1:Level=0;break;   //  �߰� ���ݷ� ����ȭ��.
    case MODEL_BOW+15:Level>=1?Level=Level*2+1:Level=0;break;   //  �߰� ���ݷ� ȭ��.
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	case MODEL_HELPER+134:
		Level = 13;
		break;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	}

#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif // MR0

	if(g_pOption->GetRenderLevel() < 4)
	{
		Level = min( Level, g_pOption->GetRenderLevel() * 2 + 5 );
	}

	if(o->Type==MODEL_SPEAR+9)//�߷��ǳ�
	{
		Vector(0.5f,0.5f,1.5f,b->BodyLight);
		b->StreamMesh = 0;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
		b->StreamMesh = -1;
	}
    else if ( o->Type==MODEL_POTION+27 )    //  ����� �ݼ�.
    {
        Vector(1.f,1.f,1.f,b->BodyLight);
		b->StreamMesh = 0;
        b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
        if ( Level==1 )
        {
        }
        else if ( Level==2 )
        {
		    b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
            Vector(0.75f,0.65f,0.5f,b->BodyLight);
		    b->RenderMesh(1, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME );
        }
        else if ( Level==3 )
        {
		    b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
    		b->RenderMesh(2, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
            Vector(0.75f,0.65f,0.5f,b->BodyLight);
		    b->RenderMesh(1, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME );
		    b->RenderMesh(2, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,BITMAP_CHROME );
        }
		b->StreamMesh = -1;

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
	else if ( o->Type==MODEL_POTION+63 )    // ����
	{
		b->StreamMesh = 0;
        o->BlendMeshLight = 1.f;
		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderMesh(0, RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		Vector(1.f,0.f,0.f,b->BodyLight);
		b->LightEnable = true;
		b->RenderMesh(1, RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
        b->RenderMesh(1, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->StreamMesh = -1;

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
	}
	else if (o->Type == MODEL_POTION+52 )	//. GM ��������
	{
		Vector(1.f,1.f,1.f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		b->LightEnable = true;
		Vector(0.1f,0.6f,0.4f,b->BodyLight);
		o->Alpha = 0.5f;
        b->RenderMesh(0, RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
	}
#ifdef FRIEND_EVENT
    else if ( o->Type==MODEL_EVENT+11 && Level==1 )    //  ������ ��.
    {
        Vector(0.3f,0.8f,1.f,b->BodyLight);
        b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
        Vector(1.f,0.8f,0.3f,b->BodyLight);
        b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
#endif// FRIEND_EVENT
#ifdef MYSTERY_BEAD
	else if ( o->Type==MODEL_EVENT+19)			//. �ź��Ǳ���
	{
		Vector(sinf ( WorldTime*0.002f )*0.2f+0.5f,sinf ( WorldTime*0.001f )*0.1f+0.6f,sinf ( WorldTime*0.001f )*0.3f+0.4f,b->BodyLight);
        b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
		Vector(0.1f,0.4f,0.1f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
	}
	else if( o->Type==MODEL_EVENT+20)			//. ������
	{
		switch(Level)
		{
		case 1:		//. ��������
			Vector(0.8f,0.2f,0.1f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			Vector(0.8f,0.2f,0.1f,b->BodyLight);
			b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			break;
		case 2:		//. Ǫ������
			Vector(0.5f,0.4f,0.8f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			Vector(0.5f,0.4f,0.8f,b->BodyLight);
			b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			break;
		case 3:		//. ��������
			Vector(0.2f,0.2f,0.2f,b->BodyLight);
			b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			Vector(0.4f,0.4f,0.4f,b->BodyLight);
			b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
			break;
		}

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		return;
	}
#endif // MYSTERY_BEAD
    else if ( o->Type==MODEL_EVENT+14 && Level==9 )    //  ������ ����
    {
        Vector(0.3f,0.8f,1.f,b->BodyLight);
        b->RenderBody(RENDER_TEXTURE,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );
        Vector(1.f,0.8f,0.3f,b->BodyLight);
        b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,-1,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV );

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
    else if ( (o->Type>=MODEL_WING+21 && o->Type<=MODEL_WING+24) 
		|| o->Type==MODEL_WING+35 
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		|| (o->Type==MODEL_WING+48)
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
		)    //  ��ũ�ε� ��ũ��.
    {
		
    	b->BeginRender(o->Alpha);
     	glColor3f ( 1.f, 1.f, 1.f );
        o->BlendMeshLight = 1.f;
        b->RenderMesh ( 0, RENDER_TEXTURE, Alpha, -1, o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
        o->BlendMeshLight = sinf ( WorldTime*0.001f )*0.5f+0.5f;
        b->RenderMesh ( 1, RENDER_BRIGHT|RENDER_TEXTURE, Alpha, 1, o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
        b->RenderMesh ( 2, RENDER_BRIGHT|RENDER_TEXTURE, Alpha, 2, 1-o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
        b->EndRender();

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		
        return;
    }
    else if ( o->Type==MODEL_HELPER+31 )    //  ��ȥ.
    {
		b->RenderBody(RENDER_TEXTURE,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
        switch ( Level )
        {
        case 0: //  ��ũȣ���� ��ȥ.
            b->RenderMesh ( 0, RENDER_BRIGHT|RENDER_TEXTURE,Alpha, 0,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            break;

        case 1: //  ��ũ���Ǹ��� ��ȥ.
            Vector ( 0.3f, 0.8f, 1.f, b->BodyLight );
            b->RenderMesh ( 0, RENDER_BRIGHT|RENDER_TEXTURE,Alpha, 0, o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
            break;
        }

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
	else if(o->Type >= MODEL_POTION && o->Type <= MODEL_POTION+6)
	{
		if(Level > 0)
			Level = 7;
	}
#ifdef ADD_SEED_SPHERE_ITEM
	else if ((o->Type >= MODEL_WING+60 && o->Type <= MODEL_WING+65)	// �õ�
		|| (o->Type >= MODEL_WING+70 && o->Type <= MODEL_WING+74)	// ���Ǿ�
		|| (o->Type >= MODEL_WING+100 && o->Type <= MODEL_WING+129))	// �õ彺�Ǿ�
	{
		Level = 0;
	}
#endif	// ADD_SEED_SPHERE_ITEM
#ifdef _PVP_MURDERER_HERO_ITEM
	else if(o->Type == MODEL_POTION+30)
	{
		switch ( Level )
		{

		case 0 : Vector(0.4f,0.5f,0.5f,b->BodyLight); break;  //  �渶����
		case 1 : Vector(0.0f,0.0f,0.0f,b->BodyLight); break;  //  ����
		case 2 : Vector(0.5f,0.4f,0.1f,b->BodyLight); break;  //  ����
		case 3 : Vector(0.4f,0.06f,0.08f,b->BodyLight); break;  //  ���˻�
		case 4 : Vector(0.1f,0.1f,0.1f,b->BodyLight); break;  //  ��ũ�ε�
		case 5 : Vector(0.4f,0.5f,0.5f,b->BodyLight); break;  //  �ҿ︶����
		case 6 : Vector(0.4f,0.2f,0.0f,b->BodyLight); break;  //  ���̵峪��Ʈ
		case 7 : Vector(0.7f,0.6f,0.1f,b->BodyLight); break;  //  �����
		}
		Level = 0;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		Vector(b->BodyLight[0]*0.5f, b->BodyLight[0]*0.5f, b->BodyLight[0]*0.5f, b->BodyLight);
		b->RenderBody(RENDER_BRIGHT|RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,1);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		return;
	}
#endif	// _PVP_MURDERER_HERO_ITEM
    else if( o->Type==MODEL_HELPER+15 )     //  ������Ʈ ����.
    {
        switch ( Level )
        {
        case 0 : Vector(0.0f,0.5f,1.0f,b->BodyLight); break;  //  ������.
        case 1 : Vector(1.0f,0.2f,0.0f,b->BodyLight); break;  //  ü��.
        case 2 : Vector(1.0f,0.8f,0.0f,b->BodyLight); break;  //  ��ø.
        case 3 : Vector(0.6f,0.8f,0.4f,b->BodyLight); break;  //  ��.
        }
		b->RenderBody(RENDER_METAL,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);
		b->RenderBody(RENDER_BRIGHT|RENDER_CHROME,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME+1);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
	else if(o->Type == MODEL_EVENT+11)	//. ���� ȿ��
	{
		Vector(0.9f,0.9f,0.9f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_CHROME|RENDER_BRIGHT,0.5f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,-1,BITMAP_CHROME+1);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		return;
	}
#ifdef NEW_YEAR_BAG_EVENT
    else if ( Type==MODEL_EVENT+5 && ((ItemLevel>>3)&15)==14 )
    {
		Vector(0.2f,0.3f,0.5f,b->BodyLight);
		b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
        Vector(0.1f,0.3f,1.f,b->BodyLight);
		b->RenderBody(RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderBody(RENDER_METAL|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
    else if ( Type==MODEL_EVENT+5 && ((ItemLevel>>3)&15)==15 )
    {
		Vector(0.5f,0.3f,0.2f,b->BodyLight);
		b->RenderBody ( RENDER_TEXTURE, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
        Vector(1.f,0.3f,0.1f,b->BodyLight);
		b->RenderBody(RENDER_CHROME|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
		b->RenderBody(RENDER_METAL|RENDER_BRIGHT,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
        return;
    }
#endif// NEW_YEAR_BAG_EVENT
	else if(o->Type == MODEL_HELPER+17)		//. ���庻
	{
		Vector(.9f,.1f,.1f,b->BodyLight);
		o->BlendMeshTexCoordU = sinf( World*0.0001f );
		o->BlendMeshTexCoordV = -WorldTime*0.0005f;
		Models[o->Type].StreamMesh = 0;
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME);
		Models[o->Type].StreamMesh = -1;
		Vector(.9f,.9f,.9f,b->BodyLight);
		b->RenderBody(RENDER_TEXTURE,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		return;
	}
	else if(o->Type == MODEL_HELPER+18)		//. ������� ȿ��
	{
		Vector(0.8f, 0.8f, 0.8f,b->BodyLight);
		float sine = float(sinf(WorldTime*0.002f)*0.3f)+0.7f;

		b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,1.0f,0,sine,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT

		return;
	}
	else if( o->Type==MODEL_EVENT+12)	// ������ ���� ȿ��
	{
        float Luminosity = (float)sinf((WorldTime)*0.002f)*0.35f+0.65f;
        vec3_t p,Position,EffLight;
		Vector ( 0.f, 0.f, 15.f, p );

		float Scale = Luminosity*0.8f+2.f;
		Vector(Luminosity*0.32f,Luminosity*0.32f,Luminosity*2.f,EffLight);

        b->TransformPosition(BoneTransform[0],p,Position);
		VectorAdd(Position, o->Position, Position);

		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);
	}
	else if(o->Type == MODEL_EVENT+6 && Level == 13)	// ��ũ�ε��� ����
	{
		Vector(0.4f, 0.6f, 1.0f,b->BodyLight);
		b->RenderBody(RENDER_COLOR,1.0f,0,1.0f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		b->RenderBody(RENDER_CHROME|RENDER_BRIGHT,1.0f,0,1.0f,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);

#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
		ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
		return;
	}
	else if( o->Type==MODEL_EVENT+13 )	//. ��ũ���� ȿ��
	{
		float Luminosity = (float)sinf((WorldTime)*0.002f)*0.35f+0.65f;
        vec3_t p,Position,EffLight;
		Vector ( 0.f, -5.f, -15.f, p );

		float Scale = Luminosity*0.8f+2.5f;
		Vector(Luminosity*2.f,Luminosity*0.32f,Luminosity*0.32f,EffLight);

		b->StreamMesh = 0;
		o->BlendMeshTexCoordV = (int)-WorldTime%4000 * 0.00025f;

        b->TransformPosition(BoneTransform[0],p,Position);
		VectorAdd(Position, o->Position, Position);

		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);
	}
	else if( o->Type==MODEL_POTION+17 ) //  �Ǹ��� �� ȿ��
	{
        float   sine = (float)sinf(WorldTime*0.002f)*10.f+15.65f;

        o->BlendMesh = 1;
		o->BlendMeshLight = sine;
		o->BlendMeshTexCoordV = (int)WorldTime%2000 * 0.0005f;
        o->Alpha = 2.0f;
		
        float Luminosity = sine;
		Vector ( Luminosity/5.0f, Luminosity/5.0f, Luminosity/5.0f, o->Light );
	}
	else if(o->Type==MODEL_POTION+18)//�Ǹ��� ���� ȿ��
	{	//  ������Ʈ�� ȸ�� ���� ���� ������� Ÿ�̹��� �ٲ��.
        float Luminosity = (float)sinf((WorldTime)*0.002f)*0.35f+0.65f;
        vec3_t p,Position,EffLight;
		Vector ( 0.f, 0.f, 0.f, p );

		float Scale = Luminosity*0.8f;
		Vector(Luminosity*2,Luminosity*0.32f,Luminosity*0.32f,EffLight);
		
        b->TransformPosition(BoneTransform[1],p,Position);
		VectorAdd(Position, o->Position, Position);
		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);

		b->TransformPosition(BoneTransform[2],p,Position);
		VectorAdd(Position, o->Position, Position);
		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);
	}
	else if(o->Type==MODEL_POTION+19)//�Ǹ��� ���� �ʴ�� ȿ��
	{
        float Luminosity = (float)sinf((WorldTime)*0.002f)*0.35f+0.65f;
		vec3_t p,Position,EffLight;
		Vector ( 0.f, 0.f, 0.f, p );

        float Scale = Luminosity*0.8f;
		Vector(Luminosity*2,Luminosity*0.32f,Luminosity*0.32f,EffLight);
		
        b->TransformPosition(BoneTransform[9],p,Position);
		VectorAdd(Position, o->Position, Position);
		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);

		b->TransformPosition(BoneTransform[10],p,Position);
		VectorAdd(Position, o->Position, Position);
		CreateSprite(BITMAP_SPARK+1,Position,Scale,EffLight,o);
	}
    else if(o->Type==MODEL_POTION+21)//��(Ĩ).
    {
        float Luminosity = (float)sinf((WorldTime)*0.002f)*0.25f+0.75f;
		vec3_t EffLight;
		
        Vector(Luminosity*1.f,Luminosity*0.5f,Luminosity*0.f,EffLight);
		CreateSprite(BITMAP_SPARK+1,o->Position,2.5f,EffLight,o);
    }
    else if( o->Type==MODEL_WING+5 )    //  ���   ( ���� ���� ).
    {
        o->BlendMeshLight = (float)(sinf(WorldTime*0.001f)+1.f)/4.f;
    }
    else if( o->Type==MODEL_WING+4 )    //  ����   ( ��ȥ�� ���� ).
    {
        o->BlendMeshLight = (float)sinf(WorldTime*0.001f)+1.1f;
    }
    else if ( Type==MODEL_PANTS+24 || Type==MODEL_HELM+24 )   //. ���� �߰�����
    {
        o->BlendMeshLight = sinf( WorldTime*0.001f )*0.4f+0.6f;
    }
	else if ( o->Type==MODEL_STAFF+11 )                             //  ��� ������.
    {
        o->BlendMeshLight = sinf(WorldTime*0.004f)*0.3f+0.7f;
    }
	else if ( Type==MODEL_HELM+19 || Type==MODEL_GLOVES+19 || Type==MODEL_BOOTS+19 )
	{
		o->BlendMeshLight = 1.f;
	}
    else if ( Type==MODEL_POTION+7 )    //  ����� ����.//���ƹ���
    {
        switch ( Level )
        {
        case 0: o->HiddenMesh = 1; break;
        case 1: o->HiddenMesh = 0; break;
        }
    }
    else if ( Type==MODEL_HELPER+7 )    //  ��๮��
    {
        switch ( Level )
        {
        case 0: o->HiddenMesh = 1; break;
        case 1: o->HiddenMesh = 0; break;
        }
    }
    else if ( Type==MODEL_HELPER+11 )   //  ����� �ֹ���.
    {
        o->HiddenMesh = 1;
    }
    else if ( Type==MODEL_EVENT+18 )    //  ������ ����.
    {
        o->BlendMesh = 1;
    }
    else if( o->Type==MODEL_WING+6 )    //  ���˻� ( ����� ���� ).
    {
#ifndef _VS2008PORTING			// #ifndef
        int     i;
#endif // _VS2008PORTING
        vec3_t  posCenter, p, Position, Light;
        float   Scale = sinf(WorldTime*0.004f)*0.3f+0.3f;

        Scale = ( Scale*10.f ) + 20.f;

        Vector ( 0.6f, 0.3f, 0.8f, Light );

        Vector ( 0.f, 0.f, 0.f, p );

        //  ����.
#ifdef _VS2008PORTING
        for ( int i=0; i<5; ++i )
#else // _VS2008PORTING
        for ( i=0; i<5; ++i )
#endif // _VS2008PORTING
        {
            b->TransformPosition(BoneTransform[22-i],p,posCenter,true);
            b->TransformPosition(BoneTransform[30-i],p,Position,true);
            CreateJoint ( BITMAP_JOINT_THUNDER, Position, posCenter, o->Angle, 14, o, Scale );
            CreateJoint ( BITMAP_JOINT_SPIRIT, posCenter, Position, o->Angle, 4, o, Scale+5 );
		    CreateSprite( BITMAP_FLARE_BLUE,posCenter,Scale/28.f,Light,o );
        }

        //  ������.
#ifdef _VS2008PORTING
        for ( int i=0; i<5; ++i )
#else // _VS2008PORTING
        for ( i=0; i<5; ++i )
#endif // _VS2008PORTING
        {
            b->TransformPosition(BoneTransform[7-i],p,posCenter,true);
            b->TransformPosition(BoneTransform[11+i],p,Position,true);
            CreateJoint ( BITMAP_JOINT_THUNDER, Position, posCenter, o->Angle, 14, o, Scale );
            CreateJoint ( BITMAP_JOINT_SPIRIT, posCenter, Position, o->Angle, 4, o, Scale+5 );
		    CreateSprite(BITMAP_FLARE_BLUE,posCenter,Scale/28.f,Light,o);
        }
    }
	else if(Type == MODEL_WING+36)	// ���� 3������
	{
		vec3_t vRelativePos, vPos, vLight;
		Vector(0.f, 0.f, 0.f, vRelativePos);
		Vector(0.f, 0.f, 0.f, vPos);
		Vector(0.f, 0.f, 0.f, vLight);

		// ���� ����Ʈ
		float fLuminosity = absf(sinf(WorldTime*0.0004f))*0.4f;
		Vector(0.5f + fLuminosity, 0.5f + fLuminosity, 0.5f + fLuminosity, vLight);
		int iBone[] = { 9, 20, 19, 10, 18,
						28, 27, 36, 35, 38, 
						37, 53, 48, 62, 70, 
						72, 71, 78, 79, 80, 
						87, 90, 91, 106, 102};
		float fScale = 0.f;

		for(int i=0; i<25; ++i)
		{
			b->TransformPosition(BoneTransform[iBone[i]], vRelativePos, vPos, true);
			fScale = 0.5f;// (rand()%10) * 0.05f + 0.3f;
			CreateSprite(BITMAP_CLUD64, vPos, fScale, vLight, o, WorldTime*0.01f, 1);
		}

		// ���� ����Ʈ
		int iBoneThunder[] = { 11, 21, 29, 63, 81, 89 };
		if(rand()%2 == 0)
		{
#ifdef _VS2008PORTING
			for(int i=0; i<6; ++i)
#else // _VS2008PORTING
			for(i=0; i<6; ++i)
#endif // _VS2008PORTING
			{
				b->TransformPosition(BoneTransform[iBoneThunder[i]], vRelativePos, vPos, true);
				if(rand()%20 == 0)
				{
					Vector(0.6f, 0.6f, 0.9f, vLight);
					CreateEffect(MODEL_FENRIR_THUNDER, vPos, o->Angle, vLight, 1, o);
				}
			}
		}

		// �Һ�
		int iBoneLight[] = {64, 61, 69, 77, 86, 
							98, 97, 99, 104, 103, 
							105, 12, 8, 17, 26, 
							34, 52, 44, 51, 50, 
							49, 45 };

		fScale = absf(sinf(WorldTime*0.003f))*0.2f;
#ifdef _VS2008PORTING
		for(int i=0; i<22; ++i)
#else // _VS2008PORTING
		for(i=0; i<22; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iBoneLight[i]],vRelativePos,vPos,true);
			if(iBoneLight[i] == 12 || iBoneLight[i] == 64 || iBoneLight[i] == 98 || iBoneLight[i] == 52)
			{
				Vector(0.9f, 0.0f, 0.0f, vLight);
				CreateSprite(BITMAP_LIGHT, vPos, fScale+1.4f, vLight, o);
			}
			else
			{
				Vector(0.8f, 0.5f, 0.2f, vLight);
				CreateSprite(BITMAP_LIGHT, vPos, fScale+0.3f, vLight, o);
			}
		}
	}
	else if(Type == MODEL_WING+37)	// �ð�����(����)
	{
		vec3_t  p, Position, Light;
		Vector ( 0.f, 0.f, 0.f, p );
		float Scale = absf(sinf(WorldTime*0.003f))*0.2f;
		float Luminosity = absf(sinf(WorldTime*0.003f))*0.3f;

		// �� �Һ�
		Vector ( 0.5f + Luminosity, 0.5f + Luminosity, 0.6f + Luminosity, Light );
		//int iRedFlarePos[] = { 25, 32, 53, 15, 9, 35 };
		int iRedFlarePos[] = { 24, 31, 15, 8, 53, 35 };
		for (int i = 0; i < 6; ++i)
		{
			b->TransformPosition(BoneTransform[iRedFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_LIGHT,Position,Scale+1.3f,Light,o);
		}
		// �׸���� �Һ�
		Vector ( 0.1f, 0.1f, 0.9f, Light );
		//int iGreenFlarePos[] = { 23, 22, 24, 34, 5, 31, 14, 12, 27, 8, 6, 7, 16, 13, 56, 37, 58, 40, 39, 38 };
		int iGreenFlarePos[] = { 22, 23, 25, 29, 30, 28, 32, 13, 16, 14, 12, 9, 7, 6, 57, 58, 40, 39 };
#ifdef _VS2008PORTING
		for (int i = 0; i < 18; ++i)
#else // _VS2008PORTING
		for (i = 0; i < 18; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iGreenFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_LIGHT,Position,Scale+1.5f,Light,o);
		}
		int iGreenFlarePos2[] = { 56, 38, 51, 45 };
#ifdef _VS2008PORTING
		for (int i = 0; i < 4; ++i)
#else // _VS2008PORTING
		for (i = 0; i < 4; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iGreenFlarePos2[i]],p,Position,true);
			CreateSprite(BITMAP_LIGHT,Position,Scale+0.5f,Light,o);
		}
	}
	else if(Type == MODEL_WING+38)	// ȯ���ǳ���(����)
	{
		vec3_t  p, Position, Light;
		Vector ( 0.f, 0.f, 0.f, p );
		float Scale = absf(sinf(WorldTime*0.002f))*0.2f;
		float Luminosity = absf(sinf(WorldTime*0.002f))*0.4f;

		// ���� �Һ�
		Vector ( 0.5f + Luminosity, 0.0f + Luminosity, 0.0f + Luminosity, Light );
		int iRedFlarePos[] = { 5, 6, 7, 8, 18, 19, 23, 24, 25, 27, 37, 38 };
		for (int i = 0; i < 12; ++i)
		{
			b->TransformPosition(BoneTransform[iRedFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+0.6f,Light,o);
		}
		// �ʷ� �Һ�
		Vector ( 0.0f + Luminosity, 0.5f + Luminosity, 0.0f + Luminosity, Light );
		int iGreenFlarePos[] = { 4, 9, 13, 14, 26, 32, 31, 33 };
#ifdef _VS2008PORTING
		for (int i = 0; i < 8; ++i)
#else // _VS2008PORTING
		for (i = 0; i < 8; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iGreenFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_LIGHT,Position,1.3f,Light,o);
		}
		// ������
		Vector ( 1.0f, 1.0f, 1.0f, Light );
		float fLumi = (sinf(WorldTime*0.004f) + 1.0f) * 0.05f;
		Vector(0.8f+fLumi, 0.8f+fLumi, 0.3f+fLumi, Light);
		CreateSprite(BITMAP_LIGHT, Position, 0.4f, Light, o, 0.5f);
		if(rand()%15 >= 8)
		{
			b->TransformPosition(BoneTransform[13],p,Position,true);
			CreateParticle(BITMAP_SHINY, Position, o->Angle, Light, 5, 0.5f);
			b->TransformPosition(BoneTransform[31],p,Position,true);
			CreateParticle(BITMAP_SHINY, Position, o->Angle, Light, 5, 0.5f);
		}
	}
	else if(Type == MODEL_WING+39)	// �ĸ곯��(���˻�)
	{
		vec3_t  p, Position, Light;
		Vector ( 0.f, 0.f, 0.f, p );
		float Scale = absf(sinf(WorldTime*0.003f))*0.2f;
		float Luminosity = absf(sinf(WorldTime*0.003f))*0.3f;

		// �� �Һ�
		Vector ( 0.7f + Luminosity, 0.5f + Luminosity, 0.8f + Luminosity, Light );
		int iRedFlarePos[] = { 6, 15, 24, 56, 47, 38 };
		for (int i = 0; i < 6; ++i)
		{
			b->TransformPosition(BoneTransform[iRedFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_LIGHT,Position,Scale+1.5f,Light,o);
		}
		// ����
		Vector ( 0.6f, 0.4f, 0.7f, Light );
		int iSparkPos[] = { 7, 16, 25, 57, 48, 39,
							11, 22, 31, 63, 54, 40, 
							10, 21, 30, 62, 53, 41,
							9, 20, 29, 61, 52, 42,
							8, 19, 28, 60, 51, 43,
							18, 27, 59, 50,
							17, 26, 58, 49 };
		int iNumParticle = 1;
#ifdef _VS2008PORTING
		for (int i = 0; i < 6; ++i)
#else // _VS2008PORTING
		for (i = 0; i < 6; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iSparkPos[i]],p,Position,true);
			for (int j = 0; j < iNumParticle; ++j)
				CreateParticle(BITMAP_CHROME_ENERGY2,Position,o->Angle,Light, 0, 0.1f);
		}
#ifdef _VS2008PORTING
		for (int i = 6; i < 18; ++i)
#else // _VS2008PORTING
		for (i = 6; i < 18; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iSparkPos[i]],p,Position,true);
			for (int j = 0; j < iNumParticle; ++j)
				CreateParticle(BITMAP_CHROME_ENERGY2,Position,o->Angle,Light, 0, 0.3f);
		}
#ifdef _VS2008PORTING
		for (int i = 18; i < 30; ++i)
#else // _VS2008PORTING
		for (i = 18; i < 30; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iSparkPos[i]],p,Position,true);
			for (int j = 0; j < iNumParticle; ++j)
				CreateParticle(BITMAP_CHROME_ENERGY2,Position,o->Angle,Light, 0, 0.5f);
		}
#ifdef _VS2008PORTING
		for (int i = 30; i < 38; ++i)
#else // _VS2008PORTING
		for (i = 30; i < 38; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iSparkPos[i]],p,Position,true);
			for (int j = 0; j < iNumParticle; ++j)
				CreateParticle(BITMAP_CHROME_ENERGY2,Position,o->Angle,Light, 0, 0.7f);
		}
	}
#ifdef ADD_ALICE_WINGS_2
	else if(Type == MODEL_WING+43)	//�����ǳ���(��ȯ����)
	{
		vec3_t  p, Position, Light;
		Vector ( 0.f, 0.f, 0.f, p );
		float Scale = absf(sinf(WorldTime*0.002f))*0.2f;
		float Luminosity = absf(sinf(WorldTime*0.002f))*0.4f;

		// ����� �Һ�
		Vector ( (1.0f + Luminosity)/2.f, (0.7f + Luminosity)/2.f, (0.2f + Luminosity)/2.f, Light );
		int iFlarePos0[] = { 7, 30, 31, 43, 8, 20 };
#ifdef _VS2008PORTING
		int icnt;
		for (icnt = 0; icnt < 2; ++icnt)
		{
			b->TransformPosition(BoneTransform[iFlarePos0[icnt]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+2.0f,Light,o);
		}
		Vector ( (1.0f + Luminosity)/4.f, (0.7f + Luminosity)/4.f, (0.2f + Luminosity)/4.f, Light );
		for (; icnt < 6; ++icnt)
		{
			b->TransformPosition(BoneTransform[iFlarePos0[icnt]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+0.5f,Light,o);
		}
#else // _VS2008PORTING
		for (int i = 0; i < 2; ++i)
		{
			b->TransformPosition(BoneTransform[iFlarePos0[i]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+2.0f,Light,o);
		}
		Vector ( (1.0f + Luminosity)/4.f, (0.7f + Luminosity)/4.f, (0.2f + Luminosity)/4.f, Light );
		for (; i < 6; ++i)
		{
			b->TransformPosition(BoneTransform[iFlarePos0[i]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+0.5f,Light,o);
		}
#endif // _VS2008PORTING
		// ����� �Һ�
		Vector ( (0.5f + Luminosity)/2.f, (0.1f + Luminosity)/2.f, (0.4f + Luminosity)/2.f, Light );
		int iGreenFlarePos[] = { 29, 38, 42, 19, 15, 6 };
#ifdef _VS2008PORTING
		for (int i = 0; i < 6; ++i)
#else // _VS2008PORTING
		for (i = 0; i < 6; ++i)
#endif // _VS2008PORTING
		{
			b->TransformPosition(BoneTransform[iGreenFlarePos[i]],p,Position,true);
			CreateSprite(BITMAP_FLARE,Position,Scale+2.0f,Light,o);
		}
	}
#endif	// ADD_ALICE_WINGS_2

	if(!o->EnableShadow)
	{
		float Luminosity = 1.f;
#ifdef PJH_NEW_CHROME
		if(ExtOption > MAX_MODELS)
		{
			VectorCopy(Light,b->BodyLight);
			RenderPartObjectBody(b,o,Type,Alpha,RenderType);
//			b->RenderBody(RENDER_BRIGHT|RENDER_CHROME8,1.f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh,BITMAP_CHROME9);
			//-(int)WorldTime%10000*0.0001f
			Vector(1.f,1.f,1.f,b->BodyLight);
			b->RenderBody(RENDER_BRIGHT|RENDER_CHROME8,1.f,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,(int)WorldTime%10000*0.0003f,o->HiddenMesh,BITMAP_CHROME9);
		}
		else
#endif //PJH_NEW_CHROME

		if( g_isCharacterBuff(o, eBuff_Cloaking) )
        {
            Alpha = 0.5f;
			Vector ( 1.f, 1.f, 1.f, b->BodyLight );
      		b->RenderBody ( RENDER_BRIGHT|RENDER_CHROME5, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU*8.f, o->BlendMeshTexCoordV*2.f, -1, BITMAP_CHROME2 );
        }
		else if( g_isCharacterBuff(o, eDeBuff_Poison) && g_isCharacterBuff(o, eDeBuff_Freeze) )
		{
			Vector(Luminosity*0.3f,Luminosity*1.f,Luminosity*1.f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}

#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
		else if(g_isCharacterBuff(o, eDeBuff_BlowOfDestruction))
		{
			Vector(Luminosity*0.3f,Luminosity*1.f,Luminosity*1.f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
		else if( g_isCharacterBuff(o, eDeBuff_Poison) )
		{
			Vector(Luminosity*0.3f,Luminosity*1.f,Luminosity*0.5f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
		else if( g_isCharacterBuff(o, eDeBuff_Stun) )
		{
			DeleteEffect(BITMAP_SKULL,o,5);
			CreateEffect(BITMAP_SKULL,o->Position,o->Angle,Light,5,o);
			Vector(Luminosity*0.f,Luminosity*0.f,Luminosity*1.0f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
		else if(g_isCharacterBuff(o, eDeBuff_Freeze))	
		{
			Vector(Luminosity*0.3f,Luminosity*0.5f,Luminosity*1.f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}

#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
		else if(g_isCharacterBuff(o, eDeBuff_BlowOfDestruction))
		{
			Vector(Luminosity*0.3f,Luminosity*0.5f,Luminosity*1.f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION

		else if (g_isCharacterBuff(o, eDeBuff_Harden) )
        {
			Vector(Luminosity*0.3f,Luminosity*0.5f,Luminosity*1.f,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
        }
		else if(Level < 3 || o->Type == MODEL_POTION+15)
		{
			if( o->Type == MODEL_POTION+64 )
			{
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
				RenderPartObjectBodyColor2(b,o,Type,0.5f,RENDER_TEXTURE|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),0.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}
			else if( o->Type == MODEL_HELPER+50 )
			{
				VectorCopy(Light,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
				RenderPartObjectBodyColor2(b,o,Type,1.5f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}
			else if( o->Type == MODEL_POTION+42 || o->Type ==  MODEL_HELPER+38 ) 
			{
				VectorCopy(Light,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);

				RenderPartObjectBodyColor2(b,o,Type,1.5f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}
			else
#ifdef CSK_LUCKY_SEAL
			if( o->Type == MODEL_HELPER+43
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
				|| o->Type == MODEL_HELPER+93	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
				)
			{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				float fLumi = (sinf(WorldTime*0.001f) + 1.5f) * 0.25f;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
				Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
				RenderPartObjectBodyColor2(b,o,Type,1.5f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}
			else if( o->Type == MODEL_HELPER+44
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
				|| o->Type == MODEL_HELPER+94	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL // �ű� ǳ���� ����
				|| o->Type == MODEL_HELPER+116
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
				)
			{
				Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
				RenderPartObjectBodyColor2(b,o,Type,1.5f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}
			else if( o->Type == MODEL_HELPER+45 )
			{
				Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
				RenderPartObjectBodyColor2(b,o,Type,1.5f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.5f);
	    		RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			}	
			else
#endif //CSK_LUCKY_SEAL
			{
				VectorCopy(Light,b->BodyLight);
				RenderPartObjectBody(b,o,Type,Alpha,RenderType);
			}    
		}
        else if(Level < 5)
		{
			vec3_t l;
			Vector(g_Luminosity,g_Luminosity*0.6f,g_Luminosity*0.6f,l);
			VectorMul(l,Light,b->BodyLight);
			RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
		else if(Level < 7)
		{
			vec3_t l;
			Vector(g_Luminosity*0.5f,g_Luminosity*0.7f,g_Luminosity,l);
			VectorMul(l,Light,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
		}
		else if(g_pOption->GetRenderLevel())
        {
			//�ΰ�
		    if(Level < 8 && g_pOption->GetRenderLevel() >= 1)  //  +7
		    {
			    Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT,1.f);
		    }
		    else if(Level < 9 && g_pOption->GetRenderLevel() >= 1)  //  +8
		    {
			    Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);	
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT,1.f);
		    }
            else if(Level < 10 && g_pOption->GetRenderLevel() >= 2) //  +9
            {
                Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
	    	    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
		    else if(Level < 11 && g_pOption->GetRenderLevel() >= 2) //  +10
		    {
			    Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
	    	    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
		    }
            else if(Level < 12 && g_pOption->GetRenderLevel() >= 3) //  +11
            {
			    Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
	    	    RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
	    	    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
            else if(Level < 13 && g_pOption->GetRenderLevel() >= 3) //  +12
            {
			    Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
	    	    RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
	    	    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
            else if(Level < 14 && g_pOption->GetRenderLevel() >= 4) //  +13
            {
			    Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
                RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
			    RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
				RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
#ifdef LDK_ADD_14_15_GRADE_ITEM_RENDERING
            else if(Level < 15 && g_pOption->GetRenderLevel() >= 4) //  +14
            {
				Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
                RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
				RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
				RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
            else if(Level < 16 && g_pOption->GetRenderLevel() >= 4) //  +15
            {
				Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
                RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
				RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
				RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
            }
#endif //LDK_ADD_14_15_GRADE_ITEM_RENDERING
            else
            {
				VectorCopy(Light,b->BodyLight);
                RenderPartObjectBody(b,o,Type,Alpha,RenderType);
            }
        }
        else
        {
			VectorCopy(Light,b->BodyLight);
            RenderPartObjectBody(b,o,Type,Alpha,RenderType);
        }


		if(g_pOption->GetRenderLevel() == 0) 
		{
#ifdef LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT		
			ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MOD_SYNCHRONIZE_SETRARGETOBJECT
			return;
		}
        
        if ( !g_isCharacterBuff(o, eDeBuff_Harden) && !g_isCharacterBuff(o, eBuff_Cloaking) 
		  && !g_isCharacterBuff(o, eDeBuff_CursedTempleRestraint)
		   )
        {
            //  �׼���Ʈ ������. ���� ����.
		    if ( (Option1&63)>0 && ( o->Type<MODEL_WING || o->Type>MODEL_WING+6 ) && o->Type!=MODEL_HELPER+30
#ifdef ADD_ALICE_WINGS_1
				&& (o->Type<MODEL_WING+36 || o->Type>MODEL_WING+43)
#else	// ADD_ALICE_WINGS_1
				&& ( o->Type<MODEL_WING+36 || o->Type>MODEL_WING+40 )
#endif	// ADD_ALICE_WINGS_1
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
				&& ( o->Type < MODEL_WING+130 || MODEL_WING+134 < o->Type )
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				&& !(o->Type>=MODEL_WING+49 && o->Type<=MODEL_WING+50)
				&& (o->Type!=MODEL_WING+135)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				)
		    {
				Luminosity = sinf(WorldTime*0.002f)*0.5f+0.5f;
				Vector(Luminosity,Luminosity*0.3f,1.f-Luminosity,b->BodyLight);
				Alpha = 1.f;
				// ��ȯ���� ����� �����丮 � ���� �� ��, �Ӹ�ī���� �������� �ȵǹǷ� ������ ���� ���� ó��.
				// ��ȯ����� �Ӹ� ������Ʈ ������ �ٸ� ĳ���Ϳ� Ʋ��.
				if (b->HideSkin && MODEL_HELM+39 <= o->Type && MODEL_HELM+44 >= o->Type)
				{
					int anMesh[6] = { 2, 1, 0, 2, 1, 2 };	// ������ �ؽ�ó ��ȣ �迭.(���̿÷����� ~ ���ͳ��� ��� ����)
					b->RenderMesh(anMesh[o->Type-(MODEL_HELM+39)], RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX	// �׼���Ʈ ȿ��
				else if( Type == MODEL_PANTS +18 ||	// �׷���ҿ� ���� // �׼���Ʈ ȿ���� ���� �޵����� �̹� PhysicManager���� Render�ϹǷ� ���� Skip ó��.
						 Type == MODEL_PANTS +22 )	// ���ҿ� ����
				{
					b->RenderMesh ( 0, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
					b->RenderMesh ( 1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );					
				}
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				else if(Type == MODEL_HELM+59 || Type == MODEL_HELM+60)
				{
					b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
				else if(Type == MODEL_HELM+61)
				{
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
				else if(Type == MODEL_ARMOR+59)
				{
					b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
				else if(Type == MODEL_ARMOR+60)
				{
					b->RenderMesh(1, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
				else if(Type == MODEL_ARMOR+61)
				{
					b->RenderMesh(0, RENDER_TEXTURE|RENDER_BRIGHT, Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV);
				}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				else
				{
					b->RenderBody(RENDER_TEXTURE|RENDER_BRIGHT,Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV);
				}
		    }
            //  ��Ʈ �ɼ�.
            else if ( ((ExtOption%0x04)==EXT_A_SET_OPTION || (ExtOption%0x04)==EXT_B_SET_OPTION )
#ifdef PJH_NEW_CHROME
				&& ExtOption <= MAX_MODELS
#endif //PJH_NEW_CHROME
				)
            {
			    Alpha = sinf(WorldTime*0.001f)*0.5f+0.4f;
                if ( Alpha<=0.01f )
                {
                    b->renderCount = rand()%100;
                }
    	    	RenderPartObjectBodyColor2(b,o,Type,Alpha,RENDER_CHROME3|RENDER_BRIGHT,1.f);
            }
        }

#ifdef USE_SHADOWVOLUME
		if ( World != WD_10HEAVEN)
		{
			//�ɸ���
			CShadowVolume *pShadowVolume = new CShadowVolume;
			pShadowVolume->Create( VertexTransform, b, o);
			InsertShadowVolume( pShadowVolume);
		}
#endif

	}
#ifndef CAMERA_TEST
	else
	{
		if(World == 7)
		{
			EnableAlphaTest();
			glColor4f(0.f,0.f,0.f,0.2f);
		}
		else
		{
			DisableAlphaBlend();
			glColor3f(0.f,0.f,0.f);
		}
#ifdef USE_SHADOWVOLUME
		//�ɸ���
		//CShadowVolume *pShadowVolume = new CShadowVolume;
		//pShadowVolume->Create( VertexTransform, b, o);
		//InsertShadowVolume( pShadowVolume);
#else
        bool bRenderShadow = true;

        if ( InHellas() )
        {
            bRenderShadow = false;
        }

		if ( WD_10HEAVEN == World || o->m_bySkillCount==3 || g_Direction.m_CKanturu.IsMayaScene() )
        {
            bRenderShadow = false;
        }

		if( g_isCharacterBuff(o, eBuff_Cloaking ) )
        {
            bRenderShadow = false;
        }

        if ( bRenderShadow )
		{
            //  �׸��ڸ� ������, ������ �����Ѵ�.
            bRenderShadow = o->m_bRenderShadow;
            if ( bRenderShadow )
		    {
                b->RenderBodyShadow(o->BlendMesh,o->HiddenMesh);
            }
		}
#endif
	}
#endif

#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif // MR0
}

///////////////////////////////////////////////////////////////////////////////
// ���ý� �������� �׵θ��� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

extern float BoneScale;

void RenderPartObjectEdge(BMD *b,OBJECT *o,int Flag,bool Translate,float Scale)
{
	if( g_isCharacterBuff(o, eBuff_Cloaking) )
    {
        return;
    }

	b->LightEnable = false;
	
	BoneScale = Scale;
	if(o->EnableBoneMatrix == 1)
	{
		b->Transform(o->BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,Translate);
	}
	else
	{
		b->Transform(BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB);
	}

#ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE		// LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
	ModelManager::SetTargetObject(o);
#endif // LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
	
    if(o->Type == MODEL_WARCRAFT)
    {
    	b->BeginRender(o->Alpha);
		if ( o->Alpha >= 0.99f)
		{
     		glColor3fv(b->BodyLight);
		}
		else
		{
			glColor4f(b->BodyLight[0],b->BodyLight[1],b->BodyLight[2],o->Alpha);
		}
	    b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
    	b->EndRender();
    }
	else if(o->Type == MODEL_MONSTER01+114)		// �丣�ҳ� ���� ����
	{
		glColor3fv(b->BodyLight);
	    b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	    b->RenderMesh ( 1, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	}
	else if(o->Type == MODEL_MONSTER01+116)		// �巹���Ǿ� ���� ����
	{
		glColor3fv(b->BodyLight);
	    b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	    b->RenderMesh ( 1, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	}
	else if(o->Type == MODEL_MONSTER01+121)		// ����Ʈ�޾� ǳ�� ����
	{
		glColor3fv(b->BodyLight);
	    b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	    b->RenderMesh ( 2, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	    b->RenderMesh ( 3, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
	}
#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
	else if(b->m_iBMDSeqID == MODEL_PANTS +18 )	// �׷���ҿ����, ���ҿ���� // ����� ������.	// �Ƿ翧 ���� ������
	{
		if( o->Type == MODEL_PANTS +18 )	// �� ��ü �� ���.
		{
			b->RenderBody(Flag,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else	// ���� Hero�� ���ӵ� ���.
		{
			b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
			b->RenderMesh ( 1, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
		}
	}
	else if(b->m_iBMDSeqID == MODEL_PANTS +22)	// �׷���ҿ����, ���ҿ���� // ����� ������.
	{
		if( o->Type == MODEL_PANTS +22 )	// �� ��ü �� ���.
		{
			b->RenderBody(Flag,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
		}
		else	// ���� Hero�� ���ӵ� ���.
		{
			b->RenderMesh ( 0, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
			b->RenderMesh ( 1, Flag, o->Alpha, o->BlendMesh, o->BlendMeshLight, o->BlendMeshTexCoordU, o->BlendMeshTexCoordV, o->HiddenMesh );
		}
	}
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
    else
    {
        b->RenderBody(Flag,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
    }
	
#ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE		// LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
	ModelManager::SetTargetObject(NULL);
#endif // LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE

	BoneScale = 1.f;
}

void RenderPartObjectEdge2(BMD *b, OBJECT* o, int Flag,bool Translate,float Scale, OBB_t* OBB )
{
#ifdef MR0
	ModelManager::SetTargetObject(o);
#endif //MR0
    vec3_t tmp;

	b->LightEnable = false;
	
	BoneScale = Scale;
	b->Transform(BoneTransform,tmp,tmp,OBB, Translate);
	b->RenderBody(Flag,o->Alpha,o->BlendMesh,o->BlendMeshLight,o->BlendMeshTexCoordU,o->BlendMeshTexCoordV,o->HiddenMesh);
	
	BoneScale = 1.f;
#ifdef MR0
	ModelManager::SetTargetObject(NULL);
#endif //MR0
}

void RenderPartObjectEdgeLight(BMD* b, OBJECT* o, int Flag, bool Translate, float Scale )
{
    float Luminosity = sinf( WorldTime*0.001f )*0.5f+0.5f;
    Vector( Luminosity*1.f, Luminosity*0.8f, Luminosity*0.3f, b->BodyLight );
	RenderPartObjectEdge(b,o,Flag,Translate,Scale);
}

///////////////////////////////////////////////////////////////////////////////
// �������� �ϳ��� ������ �ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void BodyLight(OBJECT *o,BMD *b);

void RenderPartObject(OBJECT *o,int Type,void *p2,vec3_t Light,float Alpha,int ItemLevel,int Option1,int ExtOption,bool GlobalTransform,bool HideSkin,bool Translate,int Select,int RenderType)
{
	// ���İ��� 0.01�� �����̸� �ȱ׸���.
	if(Alpha <= 0.01f) 
	{
		return;
	}

	PART_t *p = ( PART_t*)p2;
	
	//�̺�Ʈ ������(��Ʈ)
	if(Type == MODEL_POTION+12)	
	{
     	int Level = (ItemLevel>>3)&15;

		if(Level == 0)
		{
	     	Type = MODEL_EVENT;
		}
		else if(Level == 2)
		{
	     	Type = MODEL_EVENT+1;
		}
	}

	BMD *b = &Models[Type];
	b->HideSkin       = HideSkin;
	b->BodyScale      = o->Scale;
	b->ContrastEnable = o->ContrastEnable;
	b->LightEnable    = o->LightEnable;
	VectorCopy(o->Position,b->BodyOrigin);

	BoneScale = 1.f;
	if(3==Select)
	{
		BoneScale = 1.4f;
	}
	else if(2==Select)
	{
		BoneScale = 1.2f;
	}
	else if(1==Select)
	{		
        float Scale = 1.2f;
        Scale = o->m_fEdgeScale;
		if(o->Kind == KIND_NPC)
		{
			Vector(0.02f,0.1f,0.f,b->BodyLight);
		}
		else
		{
			// MR0�� ��� PlayerCharacter���� �� Silhouette�� ������ � ������ Ʋ���� �̸� �����մϴ�.
#ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
			// VBO VertexShader ������ ��� �Ƿ翧(���콺 �����ɸ��Ϳ� ���� �ı� �� ȿ��) �� ������ �ʿ�.
			if(IsHighestVersion() == true)		// GPU ����
			{
				Vector(0.1f,0.08f,0.f,b->BodyLight);
			}
			else if(IsHighVersion() == true)	// GPU ����
			{
				Vector(0.1f,0.08f,0.f,b->BodyLight);
			}
			else	// Low�� ó�� �մϴ�. GPU������ ����.
			{
				Vector(0.1f,0.03f,0.f,b->BodyLight);
			}
#else // LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
			Vector(0.1f,0.03f,0.f,b->BodyLight);
#endif // LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
		}

        if ( InChaosCastle() )
        {
			Vector(0.1f,0.01f,0.f,b->BodyLight);
			Scale = 1.f + 0.1f/o->Scale;
        }

		RenderPartObjectEdge(b,o,RENDER_BRIGHT,Translate,Scale);
		if(o->Kind == KIND_NPC)
		{
			Vector(0.16f,0.7f,0.f,b->BodyLight);
		}
		else
		{
			// MR0�� ��� PlayerCharacter���� �� Silhouette�� ������ � ������ Ʋ���� �̸� �����մϴ�.
#ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
			// VBO VertexShader ������ ��� �Ƿ翧(���콺 �����ɸ��Ϳ� ���� �ı� �� ȿ��) �� ������ �ʿ�.
			if(IsHighestVersion() == true)		// GPU ����
			{
				Vector(0.1f,0.08f,0.f,b->BodyLight);
			}
			else if(IsHighVersion() == true)	// GPU ����
			{
				Vector(0.1f,0.08f,0.f,b->BodyLight);
			}
			else	// Low�� ó�� �մϴ�. GPU������ ����.
			{
				Vector(0.1f,0.03f,0.f,b->BodyLight);
			}
#else // #ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
			Vector(0.7f,0.2f,0.f,b->BodyLight);
#endif // #ifdef LDS_MR0_MODIFY_TRANSFORMSCALE_FORSILHOUETTE
		}

        if ( InChaosCastle() )
        {
			Vector(0.7f,0.07f,0.f,b->BodyLight);
			Scale = 1.f + 0.04f/o->Scale + 0.02f;
        }
		RenderPartObjectEdge(b,o,RENDER_BRIGHT,Translate,Scale-0.02f);
	}
	BodyLight(o,b);

	if(GlobalTransform)
	{
     	b->Transform(BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,Translate);
	}
	else
    {
     	b->Transform(o->BoneTransform,o->BoundingBoxMin,o->BoundingBoxMax,&o->OBB,Translate);
    }

#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX		// �κ� �����޽��� �� �����޽� ��ü�� ó��
	if(p && 
		(	Type == MODEL_PANTS+18 ||		// ���� �׷���ҿ� ����
			Type == MODEL_PANTS+19 ||
			Type == MODEL_PANTS+22 )		// ���� ���ҿ� ����
			)
	{		
		if( !p->m_pCloth[0] )
		{
			int numCloth = 0;		// ���� �� ����
			
			// 1. �빰�� �� ����
			CPhysicsCloth *pCloth[2] = { NULL, NULL };
			
			switch(Type)
			{
			case MODEL_PANTS+18:	// ���� �׷���ҿ� ����
				{
					numCloth = 1;
					pCloth[0] = new CPhysicsCloth;
					pCloth[0]->Create( o, 17, 0.0f, 9.0f, 7.0f, 5, 8, 45.0f, 85.0f, 
						BITMAP_PANTS_G_SOUL, 
						BITMAP_PANTS_G_SOUL, 
						PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED | PCT_SHORT_SHOULDER, MODEL_PANTS+18, 2 );
					pCloth[0]->AddCollisionSphere( 0.0f, -15.0f, -20.0f, 30.0f, 2);
				}
				break;
			case MODEL_PANTS+19:
				{
					numCloth = 0;
				}
				break;
			case MODEL_PANTS+22:	// ���� ���ҿ� ����
				{
					numCloth = 1;
					pCloth[0] = new CPhysicsCloth;
					pCloth[0]->Create( o, 17, 0.0f, 9.0f, 7.0f, 7, 5, 50.0f, 100.0f, 
						BITMAP_PANTS_B_SOUL_PHYSIQMESH, 
						BITMAP_PANTS_B_SOUL_PHYSIQMESH, 
						PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED | PCT_SHORT_SHOULDER,MODEL_PANTS+18, 2 );
					pCloth[0]->AddCollisionSphere( 0.0f, -15.0f, -20.0f, 30.0f, 2);
				}
				break;
			}	// switch(Type)
			
			p->m_byNumCloth = numCloth;
			p->m_pCloth[0] = ( void*)pCloth[0];
			p->m_pCloth[1] = ( void*)pCloth[1];
		}	
		else	// if ( !c->Object.m_pCloth)
		{
			for ( int i=0; i<p->m_byNumCloth; i++ )
			{	
				CPhysicsCloth *pCloth = (CPhysicsCloth*)p->m_pCloth[i];
				
				float Flag = 0.005f;
				if( g_isCharacterBuff(o, eDeBuff_Stun ) 
					|| g_isCharacterBuff(o, eDeBuff_Sleep ) )
				{
					Flag = 0.0f;
				}
				
				if ( pCloth[i].GetOwner() == NULL)	// ������ �κ��̸� �׸��� �ʰ� ����Ѵ�.
				{
					continue;
				}
				else
				{
					if ( !pCloth[i].Move2( Flag, 5))
					{
						DeleteCloth(NULL, o, p);
					}
					else	// if ( !pCloth[i].Move2( Flag, 5))
					{
						int iPhysiqMesh = -1;

						switch( Type )
						{
						case MODEL_PANTS+18:	// ���� �׷���ҿ� ����	
						case MODEL_PANTS+22:	// ���� ���ҿ� ����
							{
								iPhysiqMesh = 2;
							}
							break;
						}

						vec3_t		v3LightPhysicMesh;
						if(g_pOption->GetRenderLevel())
						{
							int iItemLevel = (ItemLevel>>3)&15;

							if(iItemLevel < 8 && g_pOption->GetRenderLevel() >= 1)  //  +7
							{
								//Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT,1.f);

								Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT, true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 9 && g_pOption->GetRenderLevel() >= 1)  //  +8
							{
								//Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT,1.f);

								Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT, true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 10 && g_pOption->GetRenderLevel() >= 2) //  +9
							{
								//Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);

								Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
								//pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 11 && g_pOption->GetRenderLevel() >= 2) //  +10
							{
								//Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);

								Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
								//pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 12 && g_pOption->GetRenderLevel() >= 3) //  +11
							{
								//Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								
								Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, 1.0f );
								//pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 13 && g_pOption->GetRenderLevel() >= 3) //  +12
							{
								//Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);

								Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME2|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, 1.0f );
								//pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
							}
							else if(iItemLevel < 14 && g_pOption->GetRenderLevel() >= 4) //  +13
							{
								//Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);
								//RenderPartObjectBodyColor2(b,o,Type,1.f,RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);
								//RenderPartObjectBodyColor(b,o,Type,Alpha,RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),1.f);

								Vector(Light[0]*0.9f,Light[1]*0.9f,Light[2]*0.9f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME4|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, 1.0f );
								//pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_METAL|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, Alpha );
							}
							else
							{
								//VectorCopy(Light,b->BodyLight);
								//RenderPartObjectBody(b,o,Type,Alpha,RenderType);

								Vector(Light[0]*0.8f,Light[1]*0.8f,Light[2]*0.8f,v3LightPhysicMesh);
								pCloth[i].Render( &v3LightPhysicMesh);
								pCloth[i].Render_MappingOption( *b, iPhysiqMesh, RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA), true, v3LightPhysicMesh, -1, 1.0f );
							}
						}	// if(g_pOption->GetRenderLevel())

						// �׼���Ʈ ȿ���� ���� ó��
						if((Option1&63)>0)
						{
							float fLuminosity = sinf(WorldTime*0.002f)*0.5f+0.5f;
							Vector(fLuminosity,fLuminosity*0.3f,1.f-fLuminosity,v3LightPhysicMesh);

							pCloth[i].Render_MappingOption( *b, iPhysiqMesh, 
												RENDER_CHROME|RENDER_BRIGHT|(RenderType&RENDER_EXTRA),
												true, v3LightPhysicMesh, -1, 1.0f, 1.0f, false );
						}

					}	// if ( !pCloth[i].Move2( Flag, 5))

				}
			} // for ( int i=0; i<p->m_byNumCloth; i++ )
		} // if( p->m_pCloth[0] ) 
	}
#else // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX	
    //  ��� �����ۿ� õȿ�� ���̱�.
	if(p)
	{
		int iCloth = 0;
		switch ( Type)
		{
		case MODEL_PANTS+18:
			iCloth = 1;
			break;

        case MODEL_PANTS+19:
			iCloth = 2;
			break;

        case MODEL_PANTS+22:
            iCloth = 3;
            break;
		}

		if ( !p->m_pCloth[0] && iCloth > 0)
		{
			int iCount = 1;
			CPhysicsClothMesh *pCloth[2] = { NULL, NULL};
			switch ( iCloth)
			{
			case 1:
				pCloth[0] = new CPhysicsClothMesh;
				pCloth[0]->Create( o, 2, 17, 0.0f, 9.0f, 7.0f, 5, 8, 45.0f, 85.0f, BITMAP_PANTS_G_SOUL, BITMAP_PANTS_G_SOUL, PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED | PCT_SHORT_SHOULDER, Type);
				pCloth[0]->AddCollisionSphere( 0.0f, -15.0f, -20.0f, 30.0f, 2);
				break;
			case 2:
				iCount = 1;
				pCloth[0] = new CPhysicsClothMesh;
				pCloth[0]->Create( o, 3, 2, PCT_OPT_CORRECTEDFORCE | PCT_HEAVY, Type);
				pCloth[0]->AddCollisionSphere( 0.0f, 0.0f, -15.0f, 22.0f, 2);
				pCloth[0]->AddCollisionSphere( 0.0f, 0.0f, -27.0f, 23.0f, 2);
				pCloth[0]->AddCollisionSphere( 0.0f, 0.0f, -40.0f, 24.0f, 2);
				pCloth[0]->AddCollisionSphere( 0.0f, 0.0f, -54.0f, 25.0f, 2);
				pCloth[0]->AddCollisionSphere( 0.0f, 0.0f, -69.0f, 26.0f, 2);
				break;
            case 3:
				pCloth[0] = new CPhysicsClothMesh;
        		pCloth[0]->Create( o, 2, 17, 0.0f, 9.0f, 7.0f, 7, 5, 50.0f, 100.0f, b->IndexTexture[b->Meshs[2].Texture], b->IndexTexture[b->Meshs[2].Texture], PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED | PCT_SHORT_SHOULDER, Type);
				pCloth[0]->AddCollisionSphere( 0.0f, -15.0f, -20.0f, 30.0f, 2);
                break;
			}
			p->m_byNumCloth = iCount;
			p->m_pCloth[0] = ( void*)pCloth[0];
			p->m_pCloth[1] = ( void*)pCloth[1];
		}

		if ( p->m_pCloth[0])
		{
			if ( iCloth > 0)
			{
				for ( int i = 0; i < p->m_byNumCloth; ++i)
				{
					CPhysicsCloth *pCloth = ( CPhysicsCloth*)p->m_pCloth[i];
					if ( !pCloth->Move2( 0.005f, 5))
					{
						DeleteCloth( NULL, o, p);
					}
					else
					{
						pCloth->Render();
					}
				}
			}
			else if ( iCloth == 0)
			{	// õ ���ֱ�
				DeleteCloth( NULL, o, p);
			}
		}
	}

#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX

#ifdef PJH_NEW_CHROME
	if(ExtOption > MAX_MODELS)
	{
		RenderPartObjectEffect(o,Type,Light,Alpha,ItemLevel,Option1,MAX_MODELS + 1,Select,RenderType);
	}
	else
#endif //PJH_NEW_CHROME

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!g_CMonkSystem.RageFighterEffect(o, Type))
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	RenderPartObjectEffect(o,Type,Light,Alpha,ItemLevel,Option1,ExtOption,Select,RenderType);
}


///////////////////////////////////////////////////////////////////////////////
// ���� �׸��� ó��(����� ������ ����)
///////////////////////////////////////////////////////////////////////////////

float AmbientShadowAngle = 180.f;

void CopyShadowAngle(OBJECT *o,BMD *b)
{
   	/*VectorCopy(o->ShadowAngle,b->ShadowAngle);
	if(o->ShadowAlpha >= 0.5f)
	{
	}
	else
	{
		b->ShadowAngle[2] = AmbientShadowAngle;
	}*/
}

void InitShadowAngle()
{
	/*for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if(o->Live && o->Visible)
					{
						o->Distance = 9999.f*9999.f;
						o->ShadowAlpha = 0.f;
					}
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}*/
}

void ShadowAngle(OBJECT *Owner)
{
	/*for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if(o->Live && o->Visible)
					{
						vec3_t Range;
						VectorSubtract(Owner->Position,o->Position,Range);
						float Distance = Range[0]*Range[0]+Range[1]*Range[1];
						if(Distance<=400.f*400.f && o->Distance>Distance)
						{
							o->Distance = Distance;
							o->ShadowAlpha = (400.f*400.f-Distance)/(400.f*400.f);
							o->ShadowAngle[2] = 360.f-CreateAngle(o->Position[0],o->Position[1],Owner->Position[0],Owner->Position[1]);
						}
					}
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}*/
}

void CreateShadowAngle()
{
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			OBJECT_BLOCK *ob = &ObjectBlock[i*16+j];
			OBJECT       *o  = ob->Head;
			while(1)
			{
				if(o != NULL) 
				{
					if(o->Live)
					{
						o->Visible = true;
						ShadowAngle(o);
					}
					if(o->Next == NULL) break;
					o = o->Next;
				}
				else break;
			}
		}
	}
}

void RenderObjectShadow()
{
}

bool IsPartyMemberBuff( int partyindex, eBuffState buffstate )
{
	return false;
}

bool isPartyMemberBuff( int partyindex )
{
	return false;
}

#ifdef CSK_DEBUG_RENDER_BOUNDINGBOX
void RenderBoundingBox(OBJECT* pObj)
{
	EnableAlphaBlend();
	glPushMatrix();
	
	float Matrix[3][4];
	AngleMatrix(pObj->Angle, Matrix);
	Matrix[0][3] = pObj->Position[0];
	Matrix[1][3] = pObj->Position[1];
	Matrix[2][3] = pObj->Position[2];
	
	vec3_t BoundingVertices[8];
	Vector(pObj->BoundingBoxMax[0], pObj->BoundingBoxMax[1], pObj->BoundingBoxMax[2], BoundingVertices[0]);
	Vector(pObj->BoundingBoxMax[0], pObj->BoundingBoxMax[1], pObj->BoundingBoxMin[2], BoundingVertices[1]);
	Vector(pObj->BoundingBoxMax[0], pObj->BoundingBoxMin[1], pObj->BoundingBoxMax[2], BoundingVertices[2]);
	Vector(pObj->BoundingBoxMax[0], pObj->BoundingBoxMin[1], pObj->BoundingBoxMin[2], BoundingVertices[3]);
	Vector(pObj->BoundingBoxMin[0], pObj->BoundingBoxMax[1], pObj->BoundingBoxMax[2], BoundingVertices[4]);
	Vector(pObj->BoundingBoxMin[0], pObj->BoundingBoxMax[1], pObj->BoundingBoxMin[2], BoundingVertices[5]);
	Vector(pObj->BoundingBoxMin[0], pObj->BoundingBoxMin[1], pObj->BoundingBoxMax[2], BoundingVertices[6]);
	Vector(pObj->BoundingBoxMin[0], pObj->BoundingBoxMin[1], pObj->BoundingBoxMin[2], BoundingVertices[7]);
	
	vec3_t TransformVertices[8];
	for(int j=0;j<8;j++)
	{
		VectorTransform(BoundingVertices[j],Matrix,TransformVertices[j]);
	}
	
	//glBegin(GL_QUADS);
	glBegin(GL_LINES);
	glColor3f(0.2f,0.2f,0.2f);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[7]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[6]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[4]);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[5]);
	
	glColor3f(0.2f,0.2f,0.2f);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[0]);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[2]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[3]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[1]);
	
	glColor3f(0.6f,0.6f,0.6f);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[7]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[3]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[2]);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[6]);
	
	glColor3f(0.6f,0.6f,0.6f);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[0]);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[1]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[5]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[4]);
	
	glColor3f(0.4f,0.4f,0.4f);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[7]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[5]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[1]);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[3]);
	
	glColor3f(0.4f,0.4f,0.4f);
	glTexCoord2f( 0.0F, 1.0F); glVertex3fv(TransformVertices[0]);
	glTexCoord2f( 1.0F, 1.0F); glVertex3fv(TransformVertices[4]);
	glTexCoord2f( 1.0F, 0.0F); glVertex3fv(TransformVertices[6]);
	glTexCoord2f( 0.0F, 0.0F); glVertex3fv(TransformVertices[2]);
	glEnd();
	
	glPopMatrix();
}
#endif // CSK_DEBUG_RENDER_BOUNDINGBOX
