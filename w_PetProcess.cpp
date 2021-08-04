// w_PetProcess.cpp: implementation of the PetProcess class.
// LDK_2008/07/08
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef LDK_ADD_NEW_PETPROCESS

#include "w_PetActionStand.h"
#include "w_PetActionRound.h"
#include "w_PetActionDemon.h"

#include "w_PetActionCollecter.h"
#include "w_PetActionCollecter_Add.h"
#include "w_PetActionUnicorn.h"

#include "w_PetProcess.h"
#include "ReadScript.h"
#include "./Utilities/Log/ErrorReport.h"

/////////////////////////////////////////////////////////////////////
static BYTE bBuxCode[3] = {0xfc,0xcf,0xab};
static void BuxConvert(BYTE *Buffer,int Size)
{
	for(int i=0;i<Size;i++)
		Buffer[i] ^= bBuxCode[i%3];
}
//////////////////////////////////////////////////////////////////////
// Infomation class
//////////////////////////////////////////////////////////////////////
PetInfoPtr PetInfo::Make()
{
	PetInfoPtr petInfo( new PetInfo );
	return petInfo;
}

PetInfo::PetInfo():
m_scale(0.0f),
m_actions(NULL),
m_speeds(NULL),
m_count(0)
{
}

PetInfo::~PetInfo()
{
	Destroy();
}

void PetInfo::Destroy()
{
	if(NULL != m_actions)
	{
		delete [] m_actions;
	}
	m_actions = NULL;

	if(NULL != m_speeds)
	{
		delete [] m_speeds;
	}
	m_speeds = NULL;
}

void PetInfo::SetActions(int count, int *actions, float *speeds) 
{
	if(NULL == actions || 0 >= count || NULL == speeds) return;

	m_count = count;
	m_actions = new int[count]();
	memcpy(m_actions, actions, sizeof(int)*m_count);

	m_speeds = new float[count];
	memcpy(m_speeds, speeds, sizeof(int)*m_count);
}

//////////////////////////////////////////////////////////////////////
// extern
//////////////////////////////////////////////////////////////////////
PetProcessPtr g_petProcess;

PetProcess& ThePetProcess()
{
	assert( g_petProcess );
	return *g_petProcess;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PetProcessPtr PetProcess::Make()
{
	PetProcessPtr petprocess( new PetProcess );
	petprocess->Init();
	return petprocess;
}

PetProcess::PetProcess()
{
}

PetProcess::~PetProcess()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////
// ����� ActionExpress�� ActionMap�� ���
//  - ActionExpress class�� �����ÿ��� �������
//	- ���� ActionExpress�� ���ÿ��� ��� ����
//	- ��Ͻ� ���ڴ� ��ũ��Ʈ��actNum��, Ŭ���������� �Դϴ�.
//////////////////////////////////////////////////////////////////////
void PetProcess::Init()
{
	PetActionStandPtr actionStand = PetActionStand::Make();
	m_petsAction.insert( make_pair( PC4_ELF, actionStand ) ); //����
	//m_petsAction.insert( make_pair( 4, actionStand ) ); //����

	PetActionRoundPtr actionRound = PetActionRound::Make();
	m_petsAction.insert( make_pair( PC4_TEST, actionRound ) );

	PetActionDemonPtr actionTest = PetActionDemon::Make();
	m_petsAction.insert( make_pair( PC4_SATAN, actionTest ) ); //��ź

	PetActionCollecterPtr actionCollecter = PetActionCollecter::Make();
	m_petsAction.insert( make_pair( XMAS_RUDOLPH, actionCollecter ) ); //������ ������?????(��Ī : �絹�� �� ����)

#ifdef PJH_ADD_PANDA_PET
	PetActionCollecterAddPtr actionCollecter_Add = PetActionCollecterAdd::Make();
	m_petsAction.insert( make_pair( PANDA, actionCollecter_Add ) ); //������ ������?????(��Ī : �絹�� �� ����)
#endif //#ifdef PJH_ADD_PANDA_PET

#ifdef LDK_ADD_CS7_UNICORN_PET
 	PetActionUnicornPtr actionUnicorn = PetActionUnicorn::Make();
 	m_petsAction.insert( make_pair( UNICORN, actionUnicorn ) ); //������ ��
#endif //LDK_ADD_CS7_UNICORN_PET
	
#ifdef YDG_ADD_SKELETON_PET
	PetActionCollecterSkeletonPtr actionCollecter_Skeleton = PetActionCollecterSkeleton::Make();
	m_petsAction.insert( make_pair( SKELETON, actionCollecter_Skeleton ) ); // ���̷��� ��
#endif	// YDG_ADD_SKELETON_PET

	LoadData();
}

void PetProcess::Destroy()
{
	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
	{
		PetList::iterator tempiter = iter;
		++iter;
		BoostWeak_Ptr(PetObject) basepet = *tempiter;
		
		if( basepet.expired() == FALSE )
		{
			basepet.lock()->Release();
			m_petsList.erase( tempiter );
		}
	}
	m_petsList.clear();

 	m_petsAction.clear();
}

//////////////////////////////////////////////////////////////////////
// ActionMap���� key������ �˻� weakPoint�� �Ѱ���
//////////////////////////////////////////////////////////////////////
BoostWeak_Ptr(PetAction) PetProcess::Find( int key )
{
	ActionMap::iterator iter = m_petsAction.find( key );

	if( iter != m_petsAction.end() )
	{
		return (*iter).second;
	}

	BoostWeak_Ptr(PetAction) temp;
	
	return temp;
}

#ifdef LDK_MOD_NUMBERING_PETCREATE
BoostWeak_Ptr(PetObject) PetProcess::FindList( int key, PetList::iterator out_iter )
{
	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
	{
		PetList::iterator tempiter = iter;
		++iter;
		BoostWeak_Ptr(PetObject) basepet = *tempiter;
		
		if( basepet.expired() == FALSE && basepet.lock()->IsSameRegKey(key) ) 
		{
			if(out_iter != NULL)
			{
				out_iter = tempiter;
			}
			
			return basepet;
		}
	}
	
	BoostWeak_Ptr(PetObject) temp;
	
	return temp;
}

//////////////////////////////////////////////////////////////////////
// ������ PetObject�� map�� ��� : ������ �ѹ��� ���( ������� ������ ��ȣ ����)
//////////////////////////////////////////////////////////////////////
int PetProcess::Register( BoostSmart_Ptr( PetObject ) pPet, int petNum )
{
	if( 0 >= petNum || FindList(petNum).expired() == FALSE ) return FALSE;

	int temp = petNum + GetTickCount();
	pPet->SetRegKey(temp);

	m_petsList.push_back( pPet );

	return temp;
}
//////////////////////////////////////////////////////////////////////
// map�� ��ϵ� PetObject�� ���� : ���� Owner�� ���� ���� ��Ϲ�ȣ Ȯ���� ����
//////////////////////////////////////////////////////////////////////
bool PetProcess::UnRegister( CHARACTER *Owner, int petRegNum )
{
	if( NULL == Owner || -1 > petRegNum || 0 == m_petsList.size() ) return FALSE;

	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
	{
		PetList::iterator tempiter = iter;
		++iter;
		BoostWeak_Ptr(PetObject) basepet = *tempiter;
		
		if( basepet.expired() == FALSE )
		{
			 if( -1 == petRegNum )
			{
				//��ü����
				basepet.lock()->Release();
				m_petsList.erase( tempiter );
			}
			else if( basepet.lock()->IsSameOwner(&Owner->Object) && basepet.lock()->IsSameRegKey(petRegNum) )
			{
				//��������
				basepet.lock()->Release();
				m_petsList.erase( tempiter );

				return TRUE;
			}
		}
	}

	if( -1 == petRegNum ) return TRUE;

	return FALSE;
}
#else //LDK_MOD_NUMBERING_PETCREATE
//////////////////////////////////////////////////////////////////////
// ������ PetObject�� list�� ��� : ��� ���� ��ȭ �ʿ��ҵ�..
//////////////////////////////////////////////////////////////////////
void PetProcess::Register( BoostSmart_Ptr( PetObject ) pPet )
{
	m_petsList.push_back( pPet );
}
//////////////////////////////////////////////////////////////////////
// list�� ��ϵ� PetObject�� ���� : ���� Owner�� ���� ���������� �꿡���� ó�� �ʿ�..
//////////////////////////////////////////////////////////////////////
void PetProcess::UnRegister(CHARACTER *Owner, int itemType, bool isUnregistAll)
{
	if( NULL == Owner ) return;

 	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
 	{
 		PetList::iterator tempiter = iter;
 		++iter;
 		BoostWeak_Ptr(PetObject) basepet = *tempiter;
 		
 		if( basepet.expired() == FALSE ) 
		{
			if( (-1 == itemType && basepet.lock()->IsSameOwner(&Owner->Object)) 
				|| basepet.lock()->IsSameObject(&Owner->Object, itemType) )
			{
				basepet.lock()->Release();
 				m_petsList.erase( tempiter );

 				if( -1 == itemType || !isUnregistAll ) return;
 			}
 		}
 	}
}
#endif //LDK_MOD_NUMBERING_PETCREATE

//--------------------------------------------//
// �ܺ� �����Լ���
//--------------------------------------------//

//////////////////////////////////////////////////////////////////////
// ��ũ��Ʈ load �Լ� : load�� map�� ���
//////////////////////////////////////////////////////////////////////
bool PetProcess::LoadData()
{
	char FileName[100];
#ifdef USE_PET_TEST_BMD
	sprintf(FileName, "Data\\Local\\pettest.bmd");
#else	// USE_PET_TEST_BMD
	sprintf(FileName, "Data\\Local\\pet.bmd");
#endif	// USE_PET_TEST_BMD

	int _ver;
	int _array;

	FILE *fp = fopen(FileName, "rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);

		return FALSE;
	}

	fread( &_ver, sizeof(int), 1, fp );
	fread( &_array, sizeof(int), 1, fp );

	int _type;
	int _blendMesh;
	float _scale;
	int _count;
	int *_action = new int[_array];
	float *_speed = new float[_array];

	int _listSize = 0;
	fread( &_listSize, sizeof(DWORD), 1, fp );

	int Size = sizeof(int) + sizeof(int) + sizeof(float) + sizeof(int) + ((sizeof(int) + sizeof(float)) * _array);
	BYTE *Buffer = new BYTE [Size*_listSize];

	fread( Buffer,Size*_listSize,1,fp );

	DWORD dwCheckSum;
	fread(&dwCheckSum,sizeof ( DWORD),1,fp);

	if ( dwCheckSum != GenerateCheckSum2( Buffer, Size*_listSize, 0x7F1D))
	{
		char Text[256];
    	sprintf(Text,"%s - File corrupted.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		
		return FALSE;
	}
	else
	{
		BYTE *pSeek = Buffer;
		for(int i=0;i<_listSize;i++)
		{
			_type = 0;
			_scale = 0.0f;
			_blendMesh = -1;
			_count = 0;
			ZeroMemory( _action, sizeof(_action) );
			ZeroMemory( _speed, sizeof(_speed) );

			BuxConvert(pSeek,Size);

			memcpy(&_type, pSeek, sizeof(_type));
			pSeek += sizeof(_type);

			memcpy(&_blendMesh, pSeek, sizeof(_blendMesh));
			pSeek += sizeof(_blendMesh);

			memcpy(&_scale, pSeek, sizeof(_scale));
			pSeek += sizeof(_scale);
			
			memcpy(&_count, pSeek, sizeof(_count));
			pSeek += sizeof(_count);
			
			memcpy(_action, pSeek, sizeof(int)*_array);
			pSeek += sizeof(int)*_array;
			
			memcpy(_speed, pSeek, sizeof(_speed)*_array);
			pSeek += sizeof(_speed)*_array;

			//�Է�
			PetInfoPtr petInfo = PetInfo::Make();
			petInfo->SetBlendMesh( _blendMesh );
			petInfo->SetScale( _scale );
			petInfo->SetActions( _count, _action, _speed );

			m_petsInfo.insert( make_pair(ITEM_HELPER+_type, petInfo) );
		}
	}
	delete [] _action;
	delete [] _speed;
	delete [] Buffer;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// map�� ��� �Ȱ� ���� Ȯ���Ѵ�.
//////////////////////////////////////////////////////////////////////
bool PetProcess::IsPet(int itemType)
{
	//��ϵǾ��ִ�  item_number�� true
	InfoMap::iterator iter = m_petsInfo.find(itemType);
	if( iter == m_petsInfo.end() ) return FALSE;
  	
	BoostWeak_Ptr(PetInfo) petInfo = (*iter).second;
	if( petInfo.expired() ) return FALSE;

	return TRUE;
}

#ifdef LDK_MOD_NUMBERING_PETCREATE
//////////////////////////////////////////////////////////////////////
// �� ������ ���
//////////////////////////////////////////////////////////////////////
int PetProcess::CreatePet( int itemType, int modelType, vec3_t Position, CHARACTER *Owner, int SubType, int LinkBone )
{
	if ( NULL == Owner ) return 0;
	
	PetObjectPtr _tempPet = PetObject::Make();
	if( _tempPet->Create( itemType, modelType, Position, Owner, SubType, LinkBone ) )
	{
		//actions�� �ʱⰪ ����.-----------------------------//
		InfoMap::iterator iter = m_petsInfo.find(itemType);
		if( iter == m_petsInfo.end() ) return 0;
		
		BoostWeak_Ptr(PetInfo) petInfo = (*iter).second;
		
		int _count = 0;
		int *action = NULL;
		float *speed = NULL;
		if( petInfo.expired() == FALSE ) 
		{
			_count = petInfo.lock()->GetActionsCount();
			action = petInfo.lock()->GetActions();
			speed =  petInfo.lock()->GetSpeeds();
			
			_tempPet->SetScale( petInfo.lock()->GetScale() );
			_tempPet->SetBlendMesh( petInfo.lock()->GetBlendMesh() );
		}
		
		for(int i=0; i<_count; i++)
		{
			_tempPet->SetActions( (PetObject::ActionType)i, Find(action[i]), speed[i] );
		}
		//---------------------------------------------------//
		
		return Register(_tempPet, itemType);
	}
	
	return 0;
}//////////////////////////////////////////////////////////////////////
// ��ϵǾ� �ִ� �� ���� : �ܺ� ���� �Լ�
//////////////////////////////////////////////////////////////////////
bool PetProcess::DeletePet( CHARACTER *Owner, int petRegNum, bool ex )
{
	if( NULL == Owner ) return FALSE;
	
	if( TRUE == ex )
	{
		petRegNum = -1;
	}
	
	return UnRegister( Owner, petRegNum );
}
#else //LDK_MOD_NUMBERING_PETCREATE
//////////////////////////////////////////////////////////////////////
// �� ������ ���
//////////////////////////////////////////////////////////////////////
bool PetProcess::CreatePet( int itemType, int modelType, vec3_t Position, CHARACTER *Owner, int SubType, int LinkBone )
{
	if ( NULL == Owner ) return FALSE;
#ifndef LDK_FIX_HIDE_PET_TO_NOT_MODEL_PLAYER //not defined 
	if ( Owner->Object.Type != MODEL_PLAYER ) return FALSE;
#endif LDK_FIX_HIDE_PET_TO_NOT_MODEL_PLAYER

	PetObjectPtr _tempPet = PetObject::Make();
	if( _tempPet->Create( itemType, modelType, Position, Owner, SubType, LinkBone ) )
	{
		//actions�� �ʱⰪ ����.-----------------------------//
		InfoMap::iterator iter = m_petsInfo.find(itemType);
		if( iter == m_petsInfo.end() ) return FALSE;

  		BoostWeak_Ptr(PetInfo) petInfo = (*iter).second;
		
		int _count = 0;
		int *action = NULL;
		float *speed = NULL;
		if( petInfo.expired() == FALSE ) 
		{
			_count = petInfo.lock()->GetActionsCount();
 			action = petInfo.lock()->GetActions();
			speed =  petInfo.lock()->GetSpeeds();

			_tempPet->SetScale( petInfo.lock()->GetScale() );
			_tempPet->SetBlendMesh( petInfo.lock()->GetBlendMesh() );
 		}

		for(int i=0; i<_count; i++)
		{
			_tempPet->SetActions( (PetObject::ActionType)i, Find(action[i]), speed[i] );
		}
		//---------------------------------------------------//

		//list�� ���
		Register( _tempPet );
     	return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////////////
// ��ϵǾ� �ִ� �� ���� : �ܺ� ���� �Լ�
//////////////////////////////////////////////////////////////////////
void PetProcess::DeletePet(CHARACTER *Owner, int itemType, bool allDelete)
{
	if( NULL == Owner ) return;

	UnRegister( Owner, itemType, allDelete );
}
#endif //LDK_MOD_NUMBERING_PETCREATE

#ifdef LDK_MOD_NUMBERING_PETCREATE
//////////////////////////////////////////////////////////////////////
// �� �ൿ ���� �Լ� : �ѹ����� �� �ൿ ����
//////////////////////////////////////////////////////////////////////
bool PetProcess::SetCommandPet( CHARACTER *Owner, int petRegNum, int targetKey, PetObject::ActionType cmdType )
{
	if( NULL == Owner || -1 > petRegNum ) return FALSE;

	//m_petsMap ��ϵ� �� ���� ����
	if( -1 != petRegNum )
	{
		//���� �ൿ
		BoostWeak_Ptr(PetObject) petReg = FindList(petRegNum);
		if( petReg.expired() == FALSE && petReg.lock()->IsSameOwner(&Owner->Object) ) 
		{
			petReg.lock()->SetCommand( targetKey, cmdType );
			
			return TRUE;
		}
	}
	else
	{
		//��ü �ൿ
		for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
		{
			PetList::iterator tempiter = iter;
			++iter;
			BoostWeak_Ptr(PetObject) basepet = *tempiter;
			
			if( basepet.expired() == FALSE && basepet.lock()->IsSameOwner(&Owner->Object)  )
			{
				basepet.lock()->SetCommand( targetKey, cmdType );
			}
		}
		return TRUE;
	}

	return FALSE;
}
#else //LDK_MOD_NUMBERING_PETCREATE
//////////////////////////////////////////////////////////////////////
// �� �ൿ ���� �Լ� : ���� ������ ��� ��
//////////////////////////////////////////////////////////////////////
void PetProcess::SetCommandPet(CHARACTER *Owner, int targetKey, PetObject::ActionType cmdType )
{
	if( NULL == Owner ) return;

 	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
 	{
 		PetList::iterator tempiter = iter;
 		++iter;
 		BoostWeak_Ptr(PetObject) basepet = *tempiter;
 		
 		if( basepet.expired() == FALSE ) 
		{
			if( basepet.lock()->IsSameOwner(&Owner->Object) )
			{
				basepet.lock()->SetCommand( targetKey, cmdType );
			}
 		}
 	}
}
#endif //LDK_MOD_NUMBERING_PETCREATE

//////////////////////////////////////////////////////////////////////
// MoveUpdate �Լ�
//////////////////////////////////////////////////////////////////////
void PetProcess::UpdatePets()
{
 	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
 	{
 		PetList::iterator tempiter = iter;
 		++iter;
 		BoostWeak_Ptr(PetObject) basepet = *tempiter;
 		
 		if( basepet.expired() == false ) 
		{
 			basepet.lock()->Update();
 		}
 	}
}

//////////////////////////////////////////////////////////////////////
// RenderUpdate �Լ�
//////////////////////////////////////////////////////////////////////
void PetProcess::RenderPets()
{
	for( PetList::iterator iter = m_petsList.begin(); iter != m_petsList.end(); )
 	{
 		PetList::iterator tempiter = iter;
 		++iter;
 		BoostWeak_Ptr(PetObject) basepet = *tempiter;
 		
 		if( basepet.expired() == FALSE ) 
		{
			basepet.lock()->Render();
 		}
 	}
}

#endif //LDK_ADD_NEW_PETPROCESS