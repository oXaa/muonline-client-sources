// w_BasePet.cpp: implementation of the BasePet class.
// LDK_2008/07/08
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef LDK_ADD_NEW_PETPROCESS

#include "w_BasePet.h"

#include "ZzzLodTerrain.h"
#include "ZzzObject.h"
#include "ZzzAI.h"
#include "ZzzEffect.h"

extern int World;
extern float EarthQuake;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PetObjectPtr PetObject::Make()
{
	PetObjectPtr PetObject( new PetObject );
	PetObject->Init();
	return PetObject;
}

PetObject::PetObject():
#ifdef _VS2008PORTING
m_moveType(eAction_Stand),
#else // _VS2008PORTING
m_moveType(ActionType::eAction_Stand),
#endif // _VS2008PORTING
#ifdef LDK_MOD_PETPROCESS_SYSTEM
m_oldMoveType(eAction_End),
#endif //LDK_MOD_PETPROCESS_SYSTEM
m_startTick(0),
m_targetKey(-1),
m_pOwner(NULL),
m_itemType(-1)
{
#ifdef LDK_MOD_NUMBERING_PETCREATE
	m_regstKey = 0;
#endif //LDK_MOD_NUMBERING_PETCREATE
}

PetObject::~PetObject()
{
	Release();
}

void PetObject::Init()
{
	m_obj = new OBJECT();
}

//////////////////////////////////////////////////////////////////////
// �ʱ� ���� scale�� ���
//////////////////////////////////////////////////////////////////////
void PetObject::SetScale( float scale )
{
	if ( NULL == m_obj ) return;

    m_obj->Scale = scale;
}
//////////////////////////////////////////////////////////////////////
// �ʱ� ���� blendMesh�� ���
//////////////////////////////////////////////////////////////////////
void PetObject::SetBlendMesh( int blendMesh )
{
	if ( NULL == m_obj ) return;

    m_obj->BlendMesh = blendMesh;
}

//////////////////////////////////////////////////////////////////////
// ���� : ��Ȯ���� �ʱ�ȭ �� ��ũ??
//////////////////////////////////////////////////////////////////////
bool PetObject::Create( int itemType, int modelType, vec3_t Position, CHARACTER *Owner, int SubType, int LinkBone )
{
	assert( Owner );
	if( m_obj->Live ) return FALSE;

	m_startTick = GetTickCount();

	m_pOwner = Owner;
	m_itemType = itemType;

	m_obj->Type             = modelType;
	m_obj->Live             = TRUE;
	m_obj->Visible          = FALSE;
	m_obj->LightEnable      = TRUE;
	m_obj->ContrastEnable   = FALSE;
	m_obj->AlphaEnable      = FALSE;
	m_obj->EnableBoneMatrix = FALSE;
	m_obj->Owner            = &m_pOwner->Object;
	m_obj->SubType          = SubType;
	m_obj->HiddenMesh       = -1;
	m_obj->BlendMesh        = -1;
	m_obj->BlendMeshLight   = 1.f;
    m_obj->Scale            = 0.7f;
	m_obj->LifeTime         = 30;
	m_obj->Alpha            = 0.f;
	m_obj->AlphaTarget      = 1.f;

	VectorCopy ( Position, m_obj->Position );
	VectorCopy ( m_obj->Owner->Angle, m_obj->Angle );
	Vector ( 3.f, 3.f, 3.f, m_obj->Light );

	m_obj->PriorAnimationFrame = 0.f;
	m_obj->AnimationFrame      = 0.f;
	m_obj->Velocity            = 0.5f;

#ifdef YDG_FIX_SKELETON_PET_CREATE_POSITION
	switch(m_obj->Type)
	{
	case MODEL_HELPER+123:	// ���̷��� �� �ʱ� ��ġ ����
		m_obj->Position[1] += (60.0f * Owner->Object.Scale);
		break;
	}
#endif	// YDG_FIX_SKELETON_PET_CREATE_POSITION

//  	m_obj->BoneTransform = new vec34_t [Models[modelType].NumBones];
// 
//  	BMD* b = &Models[modelType];
// 	for(int i=0; i<b->NumBones; i++)
// 	{
// 		memcpy( &m_obj->BoneTransform[i], &b->Bones[i], sizeof(Bone_t));
// 	}
// 
// 	memcpy( m_obj->BoneTransform, b, sizeof(m_obj->BoneTransform));
// 	VectorCopy(m_obj->Position,b->BodyOrigin);
// 
	return TRUE;
}
//////////////////////////////////////////////////////////////////////
// ���� : PetAction���� effect������ ���� ������.
//////////////////////////////////////////////////////////////////////
void PetObject::Release()
{
	if(NULL != m_obj)
	{
		m_obj->Live = FALSE;
		delete m_obj;
		m_obj = NULL;
	}
	
	for( ActionMap::iterator iter = m_actionMap.begin(); iter != m_actionMap.end(); iter ++ )
	{
  		BoostWeak_Ptr(PetAction) petAction = (*iter).second;

		if( petAction.expired() == FALSE ) 
		{
 			petAction.lock()->Release( m_obj, m_pOwner );
 		}
	}
	m_actionMap.clear();

	m_speedMap.clear();
}

//////////////////////////////////////////////////////////////////////
// ����
//////////////////////////////////////////////////////////////////////
void PetObject::Update(bool bForceRender)
{
	if ( !m_obj->Live || NULL == m_obj->Owner || NULL == m_obj ) return;

	if ( SceneFlag==MAIN_SCENE )
    {
      	if ( !m_obj->Owner->Live || m_obj->Owner->Kind!=KIND_PLAYER )
		{
	    	m_obj->Live = FALSE;
			return;
		}
    }

	//���� ��ɵ� ó��
	Alpha ( m_obj );

	//-----------------------------//
	DWORD tick = GetNowTick();
	UpdateModel( tick, bForceRender );
	UpdateMove( tick, bForceRender );
#ifdef LDK_ADD_NEW_PETPROCESS_ADD_SOUND
	UpdateSound( tick, bForceRender );
#endif //LDK_ADD_NEW_PETPROCESS_ADD_SOUND
}

//////////////////////////////////////////////////////////////////////
// RenderUpdate �Լ�
//////////////////////////////////////////////////////////////////////
void PetObject::Render( bool bForceRender )
{
	if(m_obj->Live)
	{
		m_obj->Visible = (bForceRender == FALSE ? TestFrustrum2D(m_obj->Position[0]*0.01f,m_obj->Position[1]*0.01f,-20.f) : TRUE);

		if(m_obj->Visible)
		{
#ifndef LDK_FIX_HIDE_PET_TO_NOT_MODEL_PLAYER //not defined 
 			if ( m_obj->Owner->Type!=MODEL_PLAYER ) return;
#endif LDK_FIX_HIDE_PET_TO_NOT_MODEL_PLAYER

			//State�� 10�̸� Draw_RenderObject�� ������ �����(Ŭ��ŷ??) ó���ϴºκ��� ����.. ��.��;;;	
			int State = g_isCharacterBuff(m_obj->Owner, eBuff_Cloaking)? 10 : 0;

#ifdef LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY
			EngineGate::SetOn( false );		// ���� ������� �׸���.
#endif // LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY

			RenderObject ( m_obj , FALSE, 0, State);

#ifdef LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY
			EngineGate::SetOn( true );
#endif // LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY
			
			// ������ ���� ����ǥ ������ ���� ���������...
			DWORD tick = GetNowTick();
			CreateEffect( tick, bForceRender );
		}
	}
}

bool PetObject::IsSameOwner( OBJECT *Owner )
{
	assert( Owner );
	
	return ( Owner == m_obj->Owner )? TRUE : FALSE;
}

bool PetObject::IsSameObject( OBJECT *Owner, int itemType )
{
	assert( Owner );

	return ( Owner == m_obj->Owner && itemType == m_itemType )? TRUE : FALSE;
}

//////////////////////////////////////////////////////////////////////
// action�� �ּҸ� ���
//////////////////////////////////////////////////////////////////////
void PetObject::SetActions( ActionType type, BoostWeak_Ptr(PetAction) action, float speed )
{
	if( action.expired() == TRUE ) return;
	
	m_actionMap.insert( make_pair( type, action ) );
	m_speedMap.insert( make_pair( type, speed ) );
}

//////////////////////////////////////////////////////////////////////
// �ൿ ���氪 ���
//////////////////////////////////////////////////////////////////////
void PetObject::SetCommand( int targetKey, ActionType cmdType )
{
	m_targetKey = targetKey;
	m_moveType = cmdType;
}

//////////////////////////////////////////////////////////////////////
// ���� MoveUpdate �Լ� : �̵��� ���ؼ��� ���� ����
//////////////////////////////////////////////////////////////////////
bool PetObject::UpdateMove( DWORD tick, bool bForceRender )
{
#ifdef LDK_MOD_PETPROCESS_SYSTEM
	if( m_oldMoveType != m_moveType )
	{
		m_oldMoveType = m_moveType;

		//speed ����
		SpeedMap::iterator iter2 = m_speedMap.find(m_moveType);
		if( iter2 == m_speedMap.end() ) return FALSE;
		
		m_obj->Velocity = (*iter2).second;
	}
#else
	//speed ����
	SpeedMap::iterator iter2 = m_speedMap.find(m_moveType);
	if( iter2 == m_speedMap.end() ) return FALSE;
	
	m_obj->Velocity = (*iter2).second;

#endif //LDK_MOD_PETPROCESS_SYSTEM

	//action ����
	ActionMap::iterator iter = m_actionMap.find(m_moveType);
	if( iter == m_actionMap.end() )
	{
		//action ����
#ifdef _VS2008PORTING
		m_moveType = eAction_Stand;
#else // _VS2008PORTING
		m_moveType = ActionType::eAction_Stand;
#endif // _VS2008PORTING
		return FALSE;
	}

  	BoostWeak_Ptr(PetAction) petAction = (*iter).second;

	if( petAction.expired() == FALSE ) 
	{
 		petAction.lock()->Move( m_obj, m_pOwner, m_targetKey, tick, bForceRender );
 	}
	
	return TRUE;
}
//////////////////////////////////////////////////////////////////////
// ���� ModelUpdate �Լ� : ���� ����� �ִϿ� ���ؼ��� ���� ����
//////////////////////////////////////////////////////////////////////
bool PetObject::UpdateModel( DWORD tick, bool bForceRender )
{
	ActionMap::iterator iter = m_actionMap.find(m_moveType);
	if( iter == m_actionMap.end() ) return FALSE;

  	BoostWeak_Ptr(PetAction) petAction = (*iter).second;

	if( petAction.expired() == FALSE ) 
	{
 		petAction.lock()->Model( m_obj, m_pOwner, m_targetKey, tick, bForceRender );
 	}

	BMD* b = &Models[m_obj->Type];
    b->CurrentAction = m_obj->CurrentAction;
   	b->PlayAnimation(&m_obj->AnimationFrame,&m_obj->PriorAnimationFrame,&m_obj->PriorAction,m_obj->Velocity,m_obj->Position,m_obj->Angle);

	return TRUE;
}

#ifdef LDK_ADD_NEW_PETPROCESS_ADD_SOUND
//////////////////////////////////////////////////////////////////////
// ���� SoundUpdate �Լ� : ���� ������ ���ؼ��� ���� ����
//////////////////////////////////////////////////////////////////////
bool PetObject::UpdateSound( DWORD tick, bool bForceRender )
{
	ActionMap::iterator iter = m_actionMap.find(m_moveType);
	if( iter == m_actionMap.end() ) return FALSE;
	
	BoostWeak_Ptr(PetAction) petAction = (*iter).second;

	if( petAction.expired() == FALSE ) 
	{
 		petAction.lock()->Sound( m_obj, m_pOwner, m_targetKey, tick, bForceRender );
	}

	return TRUE;
}
#endif //LDK_ADD_NEW_PETPROCESS_ADD_SOUND

//////////////////////////////////////////////////////////////////////
// ���� EffectUpdate �Լ� : ����Ʈ ������ ���ؼ��� ���� ����
//////////////////////////////////////////////////////////////////////
bool PetObject::CreateEffect( DWORD tick, bool bForceRender )
{
	ActionMap::iterator iter = m_actionMap.find(m_moveType);
	if( iter == m_actionMap.end() ) return FALSE;
	
	BoostWeak_Ptr(PetAction) petAction = (*iter).second;

	if( petAction.expired() == FALSE ) 
	{
 		petAction.lock()->Effect( m_obj, m_pOwner, m_targetKey, tick, bForceRender );
	}

	return TRUE;
}

#endif //LDK_ADD_NEW_PETPROCESS
