///////////////////////////////////////////////////////////////////////////////
// �ε�ȭ��� ��� ����Ÿ ������ �о���̴� �Լ�
// ���, �𵨸�, �ؽ���, ����, �̹��� ���
//
// *** �Լ� ����: 4
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIControls.h"
#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzLodTerrain.h"
#include "ZzzTexture.h"
#include "ZzzOpenData.h"
#include "ZzzAI.h"
#include "ZzzInventory.h"
#include "DSPlaySound.h"
#include "wsclientinline.h"
#include "SMD.h" 
#include "./Utilities/Log/ErrorReport.h"
#include "PhysicsManager.h"
#include "CSQuest.h"
#include "GMCrywolf1st.h"
#include "CMVP1stDirection.h"
#include "CSItemOption.h"
#include "CSChaosCastle.h"
#include "GMHellas.h"
#include "GMBattleCastle.h"
#include "CComGem.h"
#include "GM_Kanturu_3rd.h"
#include "CDirection.h"
#include "PersonalShopTitleImp.h"
#include "MoveCommandData.h"
#include "UIMng.h"
#ifdef MR0
#include "EngineGate.h"
#endif //MR0
#include "Event.h"
#include "ChangeRingManager.h"
#include "NewUISystem.h"
#include "w_CursedTemple.h"
#include "CameraMove.h"
// �� ���� include
#ifdef PSW_ADD_MAPSYSTEM
#include "w_MapHeaders.h"
#endif // PSW_ADD_MAPSYSTEM
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
#include "QuestMng.h"
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
#include "ServerListManager.h"
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS
#ifdef PBG_ADD_NEWCHAR_MONK
#include "MonkSystem.h"
#endif //PBG_ADD_NEWCHAR_MONK
#ifdef LDK_ADD_SCALEFORM
#include "CGFxProcess.h"
#endif //LDK_ADD_SCALEFORM

#ifdef KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING
	#ifdef RESOURCE_GUARD
		#include "./ExternalObject/ResourceGuard/MuRGReport.h"
		#include "./ExternalObject/ResourceGuard/ResourceGuard.h"
	#endif // RESOURCE_GUARD
#endif // KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING

///////////////////////////////////////////
extern BOOL g_bUseChatListBox;
///////////////////////////////////////////

bool Flip           = false;

///////////////////////////////////////////////////////////////////////////////
// �𵨸� ����Ÿ���� �ؽ��� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenTexture(int Model,char *SubFolder, int Wrap, int Type,bool Check)	/* Check: ������!! */
{
#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENTEXTURE, PROFILING_LOADING_OPENTEXTURE );
	}
#endif // DO_PROFILING_FOR_LOADING

	BMD* pModel = &Models[Model];
	for(int i=0;i<pModel->NumMeshs;i++)
	{
		Texture_t* pTexture = &pModel->Textures[i];
		
		char szFullPath[256] = {0, };
		strcpy(szFullPath,"Data\\");
		strcat(szFullPath, SubFolder);
		strcat(szFullPath, pTexture->FileName);
		
		char __ext[_MAX_EXT] = {0, };
		_splitpath(pTexture->FileName, NULL, NULL, NULL, __ext);
		if(pTexture->FileName[0]=='s' && pTexture->FileName[1]=='k' && pTexture->FileName[2]=='i')
			pModel->IndexTexture[i] = BITMAP_SKIN;
#ifdef PBG_ADD_NEWCHAR_MONK
		else if(!strnicmp(pTexture->FileName, "level", 5))
		{
			pModel->IndexTexture[i] = BITMAP_SKIN;
		}
#else //PBG_ADD_NEWCHAR_MONK
		else if(pTexture->FileName[0]=='l' && pTexture->FileName[1]=='e' && pTexture->FileName[2]=='v' &&
			pTexture->FileName[3]=='e' && pTexture->FileName[4]=='l')
			pModel->IndexTexture[i] = BITMAP_SKIN;
#endif //PBG_ADD_NEWCHAR_MONK
		else if(pTexture->FileName[0]=='h' && pTexture->FileName[1]=='i' && pTexture->FileName[2]=='d')
			pModel->IndexTexture[i] = BITMAP_HIDE;
		else if (pTexture->FileName[0]=='h' && pTexture->FileName[1]=='a' && pTexture->FileName[2]=='i' && 
			pTexture->FileName[3]=='r' )
			pModel->IndexTexture[i] = BITMAP_HAIR;
		else if(tolower(__ext[1])=='t')
			pModel->IndexTexture[i] = Bitmaps.LoadImage(szFullPath,GL_NEAREST,Wrap);
		else if(tolower(__ext[1])=='j')
			pModel->IndexTexture[i] = Bitmaps.LoadImage(szFullPath,Type,Wrap);

		if(pModel->IndexTexture[i] == BITMAP_UNKNOWN)
		{
			//. ���ٸ�, �����̸��� �ؽ��ĸ� ã�´�.
			BITMAP_t* pBitmap = Bitmaps.FindTextureByName(pTexture->FileName);
			if(pBitmap)
			{
				Bitmaps.LoadImage(pBitmap->BitmapIndex, pBitmap->FileName);
				pModel->IndexTexture[i] = pBitmap->BitmapIndex;
			}
			else
			{
#ifdef LDS_OPTIMIZE_FORLOADING
				// ���� FindTextureByName �Լ� ���� std::map(namemap)���� �˻��� �ȵǴ� ��찡 
				// ��Ȥ �߻� �ϸ�, �̿� ��Ȯ�� �˻��� ���Ͽ� FindTextureByName_Linear �Լ��� ����
				// stricmp �� ��Ȯ�� �񱳸� �Ͽ��ش�.
				pBitmap = Bitmaps.FindTextureByName_Linear(pTexture->FileName);
				if( pBitmap )
				{
					Bitmaps.LoadImage(pBitmap->BitmapIndex, pBitmap->FileName);
					pModel->IndexTexture[i] = pBitmap->BitmapIndex;	
				}
				else
#endif // LDS_OPTIMIZE_FORLOADING
				{
					char szErrorMsg[256] = {0, };
					sprintf(szErrorMsg, "OpenTexture Failed: %s of %s", szFullPath, pModel->Name);
#ifdef FOR_WORK
					PopUpErrorCheckMsgBox(szErrorMsg);
#else // FOR_WORK
					PopUpErrorCheckMsgBox(szErrorMsg, true);
#endif // FOR_WORK
					break;
				}
				
			}
		}
	}


#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENTEXTURE );
	}
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// �𵨸� ����Ÿ �о���̴� �Լ�(�Ķ���� ������ �б�)
///////////////////////////////////////////////////////////////////////////////

void OpenModel(int Type,char *Dir,char *ModelFileName,...)
{
	char ModelName[100];
	char AnimationName[20][100];
	strcpy(ModelName,Dir);
	strcat(ModelName,ModelFileName);

    va_list Marker;
	va_start(Marker,ModelFileName);
	int AnimationCount = 0;
	while( 1 )
	{
		char *Temp = va_arg(Marker,char*);
		if(Temp==NULL || strcmp(Temp,"end")==NULL)
		{
			break;
		}
		else
		{
			strcpy(AnimationName[AnimationCount],Dir);
			strcat(AnimationName[AnimationCount],Temp);
			AnimationCount++;
		}
	}
	if(AnimationCount == 0)
	{
     	OpenSMDModel(Type,ModelName,1,Flip);
     	OpenSMDAnimation(Type,ModelName);
	}
	else
	{
     	OpenSMDModel(Type,ModelName,AnimationCount,Flip);
		for(int i=0;i<AnimationCount;i++)
		{
			bool Walk = false;
			if(i==MONSTER01_WALK || i==MONSTER01_RUN) Walk = true;
			OpenSMDAnimation(Type,AnimationName[i],Walk);
		}
	}
	va_end(Marker);

	Flip = false;
}

///////////////////////////////////////////////////////////////////////////////
// �𵨸� ����Ÿ �о���̴� �Լ�(��ȣ������ �б�)
///////////////////////////////////////////////////////////////////////////////

void OpenModels(int Model,char *FileName,int i)
{
	char Name[64];
	if(i < 10)
     	sprintf(Name,"%s0%d.smd",FileName,i);
	else
     	sprintf(Name,"%s%d.smd",FileName,i);
	OpenSMDModel(Model,Name);
   	OpenSMDAnimation(Model,Name);
}

///////////////////////////////////////////////////////////////////////////////
// �𵨸� ����Ÿ �аų� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void AccessModel(int Type,char *Dir,char *FileName,int i)
{
	/*
	if(MODEL_HELPER+15 == Type)
		int a = 0;
*/
#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_ACCESSMODEL, PROFILING_LOADING_ACCESSMODEL );
	}
#endif // DO_PROFILING_FOR_LOADING
	
	char Name[64];
	if(i == -1)
     	sprintf(Name,"%s.bmd",FileName);
	else if(i < 10)
     	sprintf(Name,"%s0%d.bmd",FileName,i);
	else
     	sprintf(Name,"%s%d.bmd",FileName,i);

    bool Success = false;

#ifdef LDS_ADD_SET_BMDMODELSEQUENCE_
	Models[Type].m_iBMDSeqID = Type;
#endif // LDS_ADD_SET_BMDMODELSEQUENCE_
	
	Success = Models[Type].Open2(Dir,Name);

#ifdef MR0
	ModelManager::Convert(Type, true);
#endif//MR0

#ifdef KJW_ADD_LOG_WHEN_FAIL_LODING_MODEL
	if( Success == false )
	{
		char ModelName[64];
		strcpy( ModelName, Dir );
		strcat( ModelName, Name );
		g_ErrorReport.Write( "< %s file does not exist. > \r\n", ModelName );
	}
#endif / /KJW_ADD_LOG_WHEN_FAIL_LODING_MODEL

    if ( Success==false && ( strcmp(FileName,"Monster")==NULL || strcmp(FileName,"Player")==NULL || strcmp(FileName,"PlayerTest")==NULL || strcmp(FileName,"Angel")==NULL ) )
    {	// ������ - strcmp(FileName,"Angel")==NULL �߰� (ī���� ĳ�� ���� ������ ��� �ε� �ȵɶ� ���� ó�� �߰�)
		char Text[256];
    	sprintf(Text,"%s file does not exist.",Name );
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
    }

#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_ACCESSMODEL );
	}
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��� �𵨸� ����Ÿ ��ü�� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenPlayers()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENPLAYERS, PROFILING_LOADING_OPENPLAYERS );
#endif // DO_PROFILING_FOR_LOADING

	ModelsDump = new BMD [MAX_MODELS+1024];
	Models = ModelsDump + ( rand() % 1024);
	ZeroMemory( Models, MAX_MODELS * sizeof ( BMD));

#ifndef _VS2008PORTING			// #ifndef
	int i;
#endif // _VS2008PORTING

#ifdef 	USE_PLAYERTEST_BMD
	AccessModel(MODEL_PLAYER,"Data\\Player\\","PlayerTest");
#else
	AccessModel(MODEL_PLAYER,"Data\\Player\\","Player");
#endif
	
#ifdef CSK_HACK_TEST
// 	for(i=0; i<Models[MODEL_PLAYER].NumActions; ++i)
// 	{
// 		g_ConsoleDebugLog->log("���ϸ��̼��ε��� : %d | ���ϸ��̼������Ӽ� : %d\n", i, Models[MODEL_PLAYER].Actions[i].NumAnimationKeys);
// 	}
#endif // CSK_HACK_TEST

	if(Models[MODEL_PLAYER].NumMeshs > 0)
	{
		g_ErrorReport.Write( "Player.bmd file error.\r\n");
		MessageBox(g_hWnd,"Player.bmd file error!!!",NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}

#ifdef _VS2008PORTING
	for (int i = 0; i < MAX_CLASS; ++i)
#else // _VS2008PORTING
	for (i = 0; i < MAX_CLASS; ++i)
#endif // _VS2008PORTING
	{
	// �⺻ ��Ų �� ����Ÿ
		AccessModel(MODEL_BODY_HELM  +i, "Data\\Player\\", "HelmClass" , i+1);
		AccessModel(MODEL_BODY_ARMOR +i, "Data\\Player\\", "ArmorClass", i+1);
		AccessModel(MODEL_BODY_PANTS +i, "Data\\Player\\", "PantClass" , i+1);
		AccessModel(MODEL_BODY_GLOVES+i, "Data\\Player\\", "GloveClass", i+1);
		AccessModel(MODEL_BODY_BOOTS +i, "Data\\Player\\", "BootClass" , i+1);
	// 2�� ���� ��Ų �� ����Ÿ
		if (CLASS_DARK != i && CLASS_DARK_LORD != i
#ifdef PBG_ADD_NEWCHAR_MONK
			&& (CLASS_RAGEFIGHTER != i)
#endif //PBG_ADD_NEWCHAR_MONK
			)
		{
			AccessModel(MODEL_BODY_HELM  +MAX_CLASS+i, "Data\\Player\\", "HelmClass2" , i+1);
    		AccessModel(MODEL_BODY_ARMOR +MAX_CLASS+i, "Data\\Player\\", "ArmorClass2", i+1);
    		AccessModel(MODEL_BODY_PANTS +MAX_CLASS+i, "Data\\Player\\", "PantClass2" , i+1);
    		AccessModel(MODEL_BODY_GLOVES+MAX_CLASS+i, "Data\\Player\\", "GloveClass2", i+1);
    		AccessModel(MODEL_BODY_BOOTS +MAX_CLASS+i, "Data\\Player\\", "BootClass2" , i+1);
		}
	// 3�� ���� ��Ų �� ����Ÿ
		AccessModel(MODEL_BODY_HELM  +(MAX_CLASS*2)+i, "Data\\Player\\", "HelmClass3" , i+1);
    	AccessModel(MODEL_BODY_ARMOR +(MAX_CLASS*2)+i, "Data\\Player\\", "ArmorClass3", i+1);
    	AccessModel(MODEL_BODY_PANTS +(MAX_CLASS*2)+i, "Data\\Player\\", "PantClass3" , i+1);
    	AccessModel(MODEL_BODY_GLOVES+(MAX_CLASS*2)+i, "Data\\Player\\", "GloveClass3", i+1);
    	AccessModel(MODEL_BODY_BOOTS +(MAX_CLASS*2)+i, "Data\\Player\\", "BootClass3" , i+1);
	}

#ifdef _VS2008PORTING
	for(int i=0;i<10;i++)
#else // _VS2008PORTING
	for(i=0;i<10;i++)
#endif // _VS2008PORTING
	{
		AccessModel(MODEL_HELM  +i,"Data\\Player\\","HelmMale" ,i+1);
		AccessModel(MODEL_ARMOR +i,"Data\\Player\\","ArmorMale",i+1);
		AccessModel(MODEL_PANTS +i,"Data\\Player\\","PantMale" ,i+1);
		AccessModel(MODEL_GLOVES+i,"Data\\Player\\","GloveMale",i+1);
		AccessModel(MODEL_BOOTS +i,"Data\\Player\\","BootMale" ,i+1);
	}
#ifdef _VS2008PORTING
	for(int i=0;i<5;i++)
#else // _VS2008PORTING
	for(i=0;i<5;i++)
#endif // _VS2008PORTING
	{
		AccessModel(MODEL_HELM  +i+10,"Data\\Player\\","HelmElf",i+1);
		AccessModel(MODEL_ARMOR +i+10,"Data\\Player\\","ArmorElf",i+1);
		AccessModel(MODEL_PANTS +i+10,"Data\\Player\\","PantElf" ,i+1);
		AccessModel(MODEL_GLOVES+i+10,"Data\\Player\\","GloveElf",i+1);
		AccessModel(MODEL_BOOTS +i+10,"Data\\Player\\","BootElf" ,i+1);

	}
	AccessModel(MODEL_ARMOR +15,"Data\\Player\\","ArmorMale",16);
	AccessModel(MODEL_PANTS +15,"Data\\Player\\","PantMale" ,16);
	AccessModel(MODEL_GLOVES+15,"Data\\Player\\","GloveMale",16);
	AccessModel(MODEL_BOOTS +15,"Data\\Player\\","BootMale" ,16);

	AccessModel(MODEL_HELM  +16,"Data\\Player\\","HelmMale" ,17);
	AccessModel(MODEL_ARMOR +16,"Data\\Player\\","ArmorMale",17);
	AccessModel(MODEL_PANTS +16,"Data\\Player\\","PantMale" ,17);
	AccessModel(MODEL_GLOVES+16,"Data\\Player\\","GloveMale",17);
	AccessModel(MODEL_BOOTS +16,"Data\\Player\\","BootMale" ,17);

	AccessModel ( MODEL_MASK_HELM+0, "Data\\Player\\", "MaskHelmMale", 1 );
	AccessModel ( MODEL_MASK_HELM+5, "Data\\Player\\", "MaskHelmMale", 6 );
	AccessModel ( MODEL_MASK_HELM+6, "Data\\Player\\", "MaskHelmMale", 7 );
	AccessModel ( MODEL_MASK_HELM+8, "Data\\Player\\", "MaskHelmMale", 9 );
	AccessModel ( MODEL_MASK_HELM+9, "Data\\Player\\", "MaskHelmMale", 10 );

#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {   
        //  ��ũ �Ǵн� ~ ���� ���̵�.
		if ( 18+i==20 )
		{
			AccessModel( MODEL_HELM  +17+i, "Data\\Player\\", "HelmMaleTest", 18+i );
			AccessModel( MODEL_ARMOR +17+i, "Data\\Player\\", "ArmorMaleTest",18+i );
			AccessModel( MODEL_PANTS +17+i, "Data\\Player\\", "PantMaleTest", 18+i );
			AccessModel( MODEL_GLOVES+17+i, "Data\\Player\\", "GloveMaleTest",18+i );
			AccessModel( MODEL_BOOTS +17+i, "Data\\Player\\", "BootMaleTest", 18+i );
		}
		else
		{
			if( i<3 )
			{
				AccessModel( MODEL_HELM  +17+i, "Data\\Player\\", "HelmMale",  18+i );
			}
			AccessModel( MODEL_ARMOR +17+i, "Data\\Player\\", "ArmorMale",18+i );
			if ( 18+i == 19)
			{
				AccessModel( MODEL_PANTS +17+i, "Data\\Player\\", "t_PantMale", 18+i );
			}
			else
			{
				AccessModel( MODEL_PANTS +17+i, "Data\\Player\\", "PantMale", 18+i );
			}
			AccessModel( MODEL_GLOVES+17+i, "Data\\Player\\", "GloveMale",18+i );
			AccessModel( MODEL_BOOTS +17+i, "Data\\Player\\", "BootMale", 18+i );
		}
	}

    //  �߰� ����.
#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        if ( i!=2 ) //  2�� ���˻�.
        {
            AccessModel( MODEL_HELM+21+i, "Data\\Player\\", "HelmMale", 22+i );
        }
		AccessModel( MODEL_ARMOR+21+i, "Data\\Player\\", "ArmorMale",22+i );
		AccessModel( MODEL_PANTS+21+i, "Data\\Player\\", "PantMale", 22+i );
		AccessModel( MODEL_GLOVES+21+i,"Data\\Player\\", "GloveMale",22+i );
		AccessModel( MODEL_BOOTS+21+i, "Data\\Player\\", "BootMale", 22+i );
    }

    //  ��ũ�ε�
#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
		AccessModel( MODEL_HELM  +25+i, "Data\\Player\\", "HelmMale", 26+i );
		AccessModel( MODEL_ARMOR +25+i, "Data\\Player\\", "ArmorMale",26+i );
		AccessModel( MODEL_PANTS +25+i, "Data\\Player\\", "PantMale", 26+i );
		AccessModel( MODEL_GLOVES+25+i, "Data\\Player\\", "GloveMale",26+i );
		AccessModel( MODEL_BOOTS +25+i, "Data\\Player\\", "BootMale", 26+i );
    }

	//(���ʴ��) ����, �渶����, ����, ���˻�, ��ũ�ε� �߰� ��Ʈ����
#ifdef _VS2008PORTING
	for(int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for(i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		AccessModel( MODEL_ARMOR +29+i, "Data\\Player\\", "HDK_ArmorMale",i+1);
		AccessModel( MODEL_PANTS +29+i, "Data\\Player\\", "HDK_PantMale",i+1);
		AccessModel( MODEL_GLOVES+29+i, "Data\\Player\\", "HDK_GloveMale",i+1);
		AccessModel( MODEL_BOOTS +29+i, "Data\\Player\\", "HDK_BootMale",i+1);
	}

	//���˻�� �����ϰ� ������ �߰�
	AccessModel( MODEL_HELM +29, "Data\\Player\\", "HDK_HelmMale", 1);
	AccessModel( MODEL_HELM +30, "Data\\Player\\", "HDK_HelmMale", 2);
	AccessModel( MODEL_HELM +31, "Data\\Player\\", "HDK_HelmMale", 3);
	AccessModel( MODEL_HELM +33, "Data\\Player\\", "HDK_HelmMale", 5);
	
	//$ ũ���̿��� ��Ʈ���� �� ����Ÿ
#ifdef _VS2008PORTING
	for(int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for(i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		AccessModel( MODEL_ARMOR +34+i, "Data\\Player\\", "CW_ArmorMale",i+1);
		AccessModel( MODEL_PANTS +34+i, "Data\\Player\\", "CW_PantMale",i+1);
		AccessModel( MODEL_GLOVES+34+i, "Data\\Player\\", "CW_GloveMale",i+1);
		AccessModel( MODEL_BOOTS +34+i, "Data\\Player\\", "CW_BootMale",i+1);
	}

	//���˻�� �����ϰ� ������ �߰�
	AccessModel( MODEL_HELM +34, "Data\\Player\\", "CW_HelmMale", 1);
	AccessModel( MODEL_HELM +35, "Data\\Player\\", "CW_HelmMale", 2);
	AccessModel( MODEL_HELM +36, "Data\\Player\\", "CW_HelmMale", 3);
	AccessModel( MODEL_HELM +38, "Data\\Player\\", "CW_HelmMale", 5);
	
	// ���̿÷����� ~ ���ͳ��� ��Ʈ
#ifdef _VS2008PORTING
    for (int i = 0; i < 6; ++i)
#else // _VS2008PORTING
    for (i = 0; i < 6; ++i)
#endif // _VS2008PORTING
    {
		::AccessModel(MODEL_HELM  +39+i, "Data\\Player\\", "HelmMale", 40+i);
		::AccessModel(MODEL_ARMOR +39+i, "Data\\Player\\", "ArmorMale",40+i);
		::AccessModel(MODEL_PANTS +39+i, "Data\\Player\\", "PantMale", 40+i);
		::AccessModel(MODEL_GLOVES+39+i, "Data\\Player\\", "GloveMale",40+i);
		::AccessModel(MODEL_BOOTS +39+i, "Data\\Player\\", "BootMale", 40+i);
    }

	// ��ȯ����� ����, ��ũ �ø��� ��.
#ifdef _VS2008PORTING
	for (int i = 0; i < MODEL_ITEM_COMMON_NUM; ++i)
#else // _VS2008PORTING
	for (i = 0; i < MODEL_ITEM_COMMON_NUM; ++i)
#endif // _VS2008PORTING
	{
		::AccessModel(MODEL_HELM2  +i, "Data\\Player\\", "HelmElfC" , i+1);
		::AccessModel(MODEL_ARMOR2 +i, "Data\\Player\\", "ArmorElfC", i+1);
		::AccessModel(MODEL_PANTS2 +i, "Data\\Player\\", "PantElfC" , i+1);
		::AccessModel(MODEL_GLOVES2+i, "Data\\Player\\", "GloveElfC", i+1);
		::AccessModel(MODEL_BOOTS2 +i, "Data\\Player\\", "BootElfC" , i+1);
	}

#ifdef ADD_SOCKET_ITEM
	// 45 "Ƽź(����)"
	// 46 "�극�̺�(����)"
	// 47 "����(���˻�)"
	// 48 "��Ʈ����(���˻�)"
	// 49 "������(����)"
	// 50 "�����(����)"
	// 51 "�п�(��ũ�ε�)"
	// 52 "�ϵ���(�渶����)"
	// 53 "��ť����(��ȯ����)"
	
	// ����
#ifdef _VS2008PORTING
	for(int i=45 ; i<=53 ; i++)
#else // _VS2008PORTING
	for( i=45 ; i<=53 ; i++)
#endif // _VS2008PORTING
	{
		if( i==47 || i== 48)
			continue;		// ���˻���������
		AccessModel( MODEL_HELM+i, "Data\\Player\\", "HelmMale", i+1);
	} // for()
	
	// ����/����/�尩/����
#ifdef _VS2008PORTING
	for(int i=45 ; i<=53 ; i++)
#else // _VS2008PORTING
	for( i=45 ; i<=53 ; i++)
#endif // _VS2008PORTING
	{	
		AccessModel(MODEL_ARMOR+i, "Data\\Player\\", "ArmorMale", i+1);
		AccessModel(MODEL_PANTS+i, "Data\\Player\\", "PantMale", i+1);
		AccessModel(MODEL_GLOVES+i, "Data\\Player\\", "GloveMale", i+1);
		AccessModel(MODEL_BOOTS+i, "Data\\Player\\", "BootMale", i+1);
	} // for()
#endif // ADD_SOCKET_ITEM

#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef _VS2008PORTING
	for (int i = 0; i<MODEL_ITEM_COMMONCNT_RAGEFIGHTER; ++i)
#else // _VS2008PORTING
	for (i = 0; i<MODEL_ITEM_COMMONCNT_RAGEFIGHTER; ++i)
#endif // _VS2008PORTING
	{
		::AccessModel(MODEL_HELM_MONK  +i, "Data\\Player\\", "HelmMonk" , i+1);
		::AccessModel(MODEL_ARMOR_MONK +i, "Data\\Player\\", "ArmorMonk", i+1);
		::AccessModel(MODEL_PANTS_MONK +i, "Data\\Player\\", "PantMonk" , i+1);
		::AccessModel(MODEL_BOOTS_MONK +i, "Data\\Player\\", "BootMonk" , i+1);
	}
#ifdef _VS2008PORTING
	for(int i=0; i<3; ++i)
#else //_VS2008PORTING
	for(i=0; i<3; ++i)
#endif //_VS2008PORTING
	{
		// ��ũ �尩�� ����
		::AccessModel(MODEL_HELM  +59+i, "Data\\Player\\", "HelmMale", 60+i);
		::AccessModel(MODEL_ARMOR +59+i, "Data\\Player\\", "ArmorMale",60+i);
		::AccessModel(MODEL_PANTS +59+i, "Data\\Player\\", "PantMale", 60+i);
		::AccessModel(MODEL_BOOTS +59+i, "Data\\Player\\", "BootMale", 60+i);
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

	// �ѹ� �����ؾ� �߰��� �ٲ�� �� ������ �� �ִ�.
	{
		CPhysicsClothMesh *pCloth = new CPhysicsClothMesh [1];
		pCloth[0].Create( &Hero->Object, 2, 17, 0.0f, 0.0f, 0.0f, 5, 8, 45.0f, 85.0f, BITMAP_PANTS_G_SOUL, BITMAP_PANTS_G_SOUL, PCT_MASK_ALPHA | PCT_HEAVY | PCT_STICKED, MODEL_PANTS+18);
		delete [] pCloth;
	}


#ifdef _VS2008PORTING
	for(int i=0;i<1;i++)
#else // _VS2008PORTING
	for(i=0;i<1;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SHADOW_BODY+i,"Data\\Player\\","Shadow",i+1);

	Models[MODEL_PLAYER].BoneHead    = 20;
	Models[MODEL_PLAYER].BoneFoot[0] = 6;
	Models[MODEL_PLAYER].BoneFoot[1] = 13;
	
	//���ϸ��̼� �ӵ� ����
#ifdef _VS2008PORTING
	for(int i=PLAYER_STOP_MALE;i<=PLAYER_STOP_RIDE_WEAPON;i++)
#else // _VS2008PORTING
	for(i=PLAYER_STOP_MALE;i<=PLAYER_STOP_RIDE_WEAPON;i++)
#endif // _VS2008PORTING
	    Models[MODEL_PLAYER].Actions[i].PlaySpeed = 0.28f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_SWORD         ].PlaySpeed = 0.26f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_TWO_HAND_SWORD].PlaySpeed = 0.24f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_SPEAR		   ].PlaySpeed = 0.24f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_BOW		   ].PlaySpeed = 0.22f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_CROSSBOW      ].PlaySpeed = 0.22f;
#ifdef YDG_FIX_ALICE_ANIMATIONS
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_SUMMONER].PlaySpeed = 0.24f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_WAND].PlaySpeed = 0.30f;
#else	// YDG_FIX_ALICE_ANIMATIONS
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_SUMMONER].PlaySpeed = 0.16f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_WAND].PlaySpeed = 0.13f;
#endif	// YDG_FIX_ALICE_ANIMATIONS

#ifdef _VS2008PORTING
	for(int i=PLAYER_WALK_MALE;i<=PLAYER_RUN_RIDE_WEAPON;i++)
#else // _VS2008PORTING
	for(i=PLAYER_WALK_MALE;i<=PLAYER_RUN_RIDE_WEAPON;i++)
#endif // _VS2008PORTING
	    Models[MODEL_PLAYER].Actions[i].PlaySpeed = 0.3f;
#ifdef YDG_FIX_ALICE_ANIMATIONS
	Models[MODEL_PLAYER].Actions[PLAYER_WALK_WAND].PlaySpeed = 0.44f;
	Models[MODEL_PLAYER].Actions[PLAYER_RUN_WAND].PlaySpeed = 0.76f;
#else	// YDG_FIX_ALICE_ANIMATIONS
    Models[MODEL_PLAYER].Actions[PLAYER_WALK_WAND].PlaySpeed = 0.22f;
	Models[MODEL_PLAYER].Actions[PLAYER_RUN_WAND].PlaySpeed = 0.42f;
#endif	// YDG_FIX_ALICE_ANIMATIONS
    Models[MODEL_PLAYER].Actions[PLAYER_WALK_SWIM].PlaySpeed = 0.35f;
    Models[MODEL_PLAYER].Actions[PLAYER_RUN_SWIM ].PlaySpeed = 0.35f;

#ifdef _VS2008PORTING
	for(int i=PLAYER_DEFENSE1;i<=PLAYER_SHOCK;i++)
#else // _VS2008PORTING
	for(i=PLAYER_DEFENSE1;i<=PLAYER_SHOCK;i++)
#endif // _VS2008PORTING
	    Models[MODEL_PLAYER].Actions[i].PlaySpeed = 0.32f;
#ifdef _VS2008PORTING
	for(int i=PLAYER_DIE1;i<=PLAYER_DIE2;i++)
#else // _VS2008PORTING
	for(i=PLAYER_DIE1;i<=PLAYER_DIE2;i++)
#endif // _VS2008PORTING
	    Models[MODEL_PLAYER].Actions[i].PlaySpeed = 0.45f;
#ifdef _VS2008PORTING
	for(int i=PLAYER_SIT1;i<MAX_PLAYER_ACTION;i++)
#else // _VS2008PORTING
	for(i=PLAYER_SIT1;i<MAX_PLAYER_ACTION;i++)
#endif // _VS2008PORTING
	    Models[MODEL_PLAYER].Actions[i].PlaySpeed = 0.4f;
	Models[MODEL_PLAYER].Actions[PLAYER_SHOCK              ].PlaySpeed = 0.4f;
	Models[MODEL_PLAYER].Actions[PLAYER_SEE1               ].PlaySpeed = 0.28f;
	Models[MODEL_PLAYER].Actions[PLAYER_SEE_FEMALE1        ].PlaySpeed = 0.28f;
	Models[MODEL_PLAYER].Actions[PLAYER_HEALING1           ].PlaySpeed = 0.2f;
	Models[MODEL_PLAYER].Actions[PLAYER_HEALING_FEMALE1    ].PlaySpeed = 0.2f;

	Models[MODEL_PLAYER].Actions[PLAYER_JACK_1].PlaySpeed = 0.38f;
	Models[MODEL_PLAYER].Actions[PLAYER_JACK_2].PlaySpeed = 0.38f;
	
	Models[MODEL_PLAYER].Actions[PLAYER_SANTA_1].PlaySpeed = 0.34f;
	Models[MODEL_PLAYER].Actions[PLAYER_SANTA_2].PlaySpeed = 0.30f;

	Models[MODEL_PLAYER].Actions[PLAYER_SKILL_RIDER].PlaySpeed      = 0.2f;
	Models[MODEL_PLAYER].Actions[PLAYER_SKILL_RIDER_FLY].PlaySpeed  = 0.2f;

	Models[MODEL_PLAYER].Actions[PLAYER_STOP_TWO_HAND_SWORD_TWO].PlaySpeed	= 0.24f;
	Models[MODEL_PLAYER].Actions[PLAYER_WALK_TWO_HAND_SWORD_TWO].PlaySpeed	= 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_RUN_TWO_HAND_SWORD_TWO].PlaySpeed	= 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_TWO_HAND_SWORD_TWO].PlaySpeed= 0.24f;

	//Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_ONETOONE    ].PlaySpeed = 0.30f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_ONETOONE    ].PlaySpeed = 0.45f;
	
	Models[MODEL_PLAYER].Actions[PLAYER_DIE1   ].Loop = true;
	Models[MODEL_PLAYER].Actions[PLAYER_DIE2   ].Loop = true;
	Models[MODEL_PLAYER].Actions[PLAYER_COME_UP].Loop = true;

	Models[MODEL_PLAYER].Actions[PLAYER_SKILL_HELL_BEGIN].Loop = true;

    Models[MODEL_PLAYER].Actions[PLAYER_DARKLORD_STAND].PlaySpeed           = 0.3f;
    Models[MODEL_PLAYER].Actions[PLAYER_DARKLORD_WALK].PlaySpeed            = 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_STOP_RIDE_HORSE].PlaySpeed          = 0.3f;
    Models[MODEL_PLAYER].Actions[PLAYER_RUN_RIDE_HORSE].PlaySpeed           = 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_STRIKE].PlaySpeed            = 0.2f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_TELEPORT].PlaySpeed          = 0.28f;

    Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_RIDE_STRIKE].PlaySpeed       = 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_RIDE_TELEPORT].PlaySpeed     = 0.3f;
    Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_RIDE_HORSE_SWORD].PlaySpeed  = 0.28f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_RIDE_ATTACK_FLASH].PlaySpeed = 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_RIDE_ATTACK_MAGIC].PlaySpeed = 0.3f;
    Models[MODEL_PLAYER].Actions[PLAYER_ATTACK_DARKHORSE].PlaySpeed         = 0.2f;

	Models[MODEL_PLAYER].Actions[PLAYER_IDLE1_DARKHORSE].PlaySpeed          = 1.0f;
	Models[MODEL_PLAYER].Actions[PLAYER_IDLE2_DARKHORSE].PlaySpeed          = 1.0f;	
	
	//^ �渱 ĳ���� ���ϸ��̼� �ӵ� ����
#ifdef _VS2008PORTING
	for(int i=PLAYER_FENRIR_ATTACK; i<=PLAYER_FENRIR_WALK_ONE_LEFT; i++)
#else // _VS2008PORTING
	for(i=PLAYER_FENRIR_ATTACK; i<=PLAYER_FENRIR_WALK_ONE_LEFT; i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.45f;
	}
#ifdef _VS2008PORTING
	for(int i=PLAYER_FENRIR_RUN; i<=PLAYER_FENRIR_RUN_ONE_LEFT_ELF; i++)
#else // _VS2008PORTING
	for(i=PLAYER_FENRIR_RUN; i<=PLAYER_FENRIR_RUN_ONE_LEFT_ELF; i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.71f;	
	}
#ifdef _VS2008PORTING
	for(int i=PLAYER_FENRIR_STAND; i<=PLAYER_FENRIR_STAND_ONE_LEFT; i++)
#else // _VS2008PORTING
	for(i=PLAYER_FENRIR_STAND; i<=PLAYER_FENRIR_STAND_ONE_LEFT; i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.4f;
	}
	
	Models[MODEL_PLAYER].Actions[PLAYER_FENRIR_ATTACK_MAGIC].PlaySpeed = 0.30f;
    Models[MODEL_PLAYER].Actions[PLAYER_FENRIR_ATTACK_DARKLORD_STRIKE].PlaySpeed = 0.3f;
	Models[MODEL_PLAYER].Actions[PLAYER_FENRIR_ATTACK_DARKLORD_TELEPORT].PlaySpeed = 0.3f;
    Models[MODEL_PLAYER].Actions[PLAYER_FENRIR_ATTACK_DARKLORD_SWORD].PlaySpeed = 0.28f;
	Models[MODEL_PLAYER].Actions[PLAYER_FENRIR_ATTACK_DARKLORD_FLASH].PlaySpeed = 0.3f;

    Models[MODEL_PLAYER].Actions[PLAYER_HIGH_SHOCK].PlaySpeed         = 0.3f;

#ifdef PBG_ADD_NEWCHAR_MONK_ANI
#ifdef _VS2008PORTING
	for(int i=PLAYER_RAGE_FENRIR; i<=PLAYER_RAGE_FENRIR_ATTACK_RIGHT; i++)
#else // _VS2008PORTING
	for(i=PLAYER_RAGE_FENRIR; i<=PLAYER_RAGE_FENRIR_ATTACK_RIGHT; i++)
#endif // _VS2008PORTING
	{
		if(i>=PLAYER_RAGE_FENRIR_TWO_SWORD && i<= PLAYER_RAGE_FENRIR_ONE_LEFT)
			Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.225f;
		else
			Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.45f;
	}
#ifdef _VS2008PORTING
	for(int i=PLAYER_RAGE_FENRIR_STAND_TWO_SWORD; i<=PLAYER_RAGE_FENRIR_STAND_ONE_LEFT; i++)
#else // _VS2008PORTING
	for(i=PLAYER_RAGE_FENRIR_STAND_TWO_SWORD; i<=PLAYER_RAGE_FENRIR_STAND_ONE_LEFT; i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.2f;
	}
	Models[MODEL_PLAYER].Actions[PLAYER_RAGE_FENRIR_STAND].PlaySpeed = 0.21f;
#ifdef _VS2008PORTING
	for(int i=PLAYER_RAGE_FENRIR_RUN; i<=PLAYER_RAGE_FENRIR_RUN_ONE_LEFT; i++)
#else // _VS2008PORTING
	for(i=PLAYER_RAGE_FENRIR_RUN; i<=PLAYER_RAGE_FENRIR_RUN_ONE_LEFT; i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_PLAYER].Actions[i].PlaySpeed		= 0.355f;
	}
	Models[MODEL_PLAYER].Actions[PLAYER_RAGE_UNI_RUN].PlaySpeed = 0.3f;
#ifndef PBG_FIX_NEWCHAR_MONK_UNIANI		//�����ÿ� ������ �ҽ�
	Models[MODEL_PLAYER].Actions[PLAYER_RAGE_UNI_ATTACK_ONE_RIGHT].PlaySpeed = 0.2f;
#endif //PBG_FIX_NEWCHAR_MONK_UNIANI	//�����ÿ� ������ �ҽ�
	Models[MODEL_PLAYER].Actions[PLAYER_RAGE_UNI_STOP_ONE_RIGHT].PlaySpeed = 0.18f;

	Models[MODEL_PLAYER].Actions[PLAYER_STOP_RAGEFIGHTER].PlaySpeed = 0.16f;
#endif //PBG_ADD_NEWCHAR_MONK_ANI
	SetAttackSpeed();
	
	// GM ���Ź��� ĳ���� �� �ε�
	AccessModel(MODEL_GM_CHARACTER, "Data\\Skill\\", "youngza");

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENPLAYERS );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// �ɸ��� �ؽ��� ��ü�� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenPlayerTextures()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENPLAYERTEXTURES, PROFILING_LOADING_OPENPLAYERTEXTURES );
#endif // DO_PROFILING_FOR_LOADING

	LoadBitmap("Player\\skin_barbarian_01.jpg",BITMAP_SKIN  );//  �渶����.
	LoadBitmap("Player\\level_man022.jpg"     ,BITMAP_SKIN+1);//  1�� ���� �渶����.
	LoadBitmap("Player\\skin_wizard_01.jpg"   ,BITMAP_SKIN+2);//  ����
	LoadBitmap("Player\\level_man01.jpg"      ,BITMAP_SKIN+3);//  1�� ���� ����.
	LoadBitmap("Player\\skin_archer_01.jpg"   ,BITMAP_SKIN+4);//  ����
	LoadBitmap("Player\\level_man033.jpg"     ,BITMAP_SKIN+5);//  1�� ���� ����.
   	LoadBitmap("Player\\skin_special_01.jpg"  ,BITMAP_SKIN+6);//  ���˻�.
	LoadBitmap("Player\\level_man02.jpg"      ,BITMAP_SKIN+8);//  ��ũ�ε�.
	LoadBitmap("Player\\hair_r.jpg"       ,BITMAP_HAIR);//  ��ũ�ε�� �Ӹ�ī��.
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	LoadBitmap("Player\\LevelClass107.jpg"   ,BITMAP_SKIN+12);//  ������������
	LoadBitmap("Player\\LevelClass207.jpg"   ,BITMAP_SKIN+13);//  ���ó���Ʈ
	LoadBitmap("Player\\LevelClass207_1.jpg" ,BITMAP_SKIN+14);//  ���ó���Ʈ���ʽ�Ų 
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

#ifdef _VS2008PORTING
	int nIndex;
	// �⺻ ��Ų �� �ؽ���
	for (int j = 0; j < 3; ++j)		// �� Ŭ���� �� �� 3���� ����.
	{
		for (int i = 0; i < MAX_CLASS; ++i)
#else // _VS2008PORTING
	int i, j, nIndex;
	// �⺻ ��Ų �� �ؽ���
	for (j = 0; j < 3; ++j)		// �� Ŭ���� �� �� 3���� ����.
	{
		for (i = 0; i < MAX_CLASS; ++i)
#endif // _VS2008PORTING

		{
			nIndex = MAX_CLASS*j+i;
			// ���˻�� ��ũ�ε� 2�� ������ ����.
			if (1 == j && (CLASS_DARK == i || CLASS_DARK_LORD == i
#ifdef PBG_ADD_NEWCHAR_MONK
				|| (CLASS_RAGEFIGHTER == i)
#endif //PBG_ADD_NEWCHAR_MONK
				))
				continue;

			OpenTexture(MODEL_BODY_HELM  +nIndex, "Player\\");
			OpenTexture(MODEL_BODY_ARMOR +nIndex, "Player\\");
			OpenTexture(MODEL_BODY_PANTS +nIndex, "Player\\");
			OpenTexture(MODEL_BODY_GLOVES+nIndex, "Player\\");
			OpenTexture(MODEL_BODY_BOOTS +nIndex, "Player\\");
		}
	}

#ifdef _VS2008PORTING
	for ( int i=0; i<17; i++ )
#else // _VS2008PORTING
	for ( i=0; i<17; i++ )
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_HELM+i  ,"Player\\");
		OpenTexture(MODEL_ARMOR+i ,"Player\\");
		OpenTexture(MODEL_PANTS+i ,"Player\\");
		OpenTexture(MODEL_GLOVES+i,"Player\\");
		OpenTexture(MODEL_BOOTS+i ,"Player\\");
	}

    //  �߰� ����.
#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        if ( i!=2 ) //   3�� ���˻�
        {
            OpenTexture ( MODEL_HELM+21+i, "Player\\" );
        }
		OpenTexture ( MODEL_ARMOR+21+i,  "Player\\" );
		OpenTexture ( MODEL_PANTS+21+i,  "Player\\" );
		OpenTexture ( MODEL_GLOVES+21+i, "Player\\" );
		OpenTexture ( MODEL_BOOTS+21+i,  "Player\\" );
    }

#ifdef _VS2008PORTING
	for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
	for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
	{
		OpenTexture ( MODEL_HELM  +25+i, "Player\\" );
		OpenTexture ( MODEL_ARMOR +25+i, "Player\\" );
		OpenTexture ( MODEL_PANTS +25+i, "Player\\" );
		OpenTexture ( MODEL_GLOVES+25+i, "Player\\" );
		OpenTexture ( MODEL_BOOTS +25+i, "Player\\" );
	}

#ifdef _VS2008PORTING
    for( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {   
        //  ��ũ �Ǵн� ~ ���� ���̵�.
	    OpenTexture(MODEL_HELM  +17+i, "Player\\");    //  
	    OpenTexture(MODEL_ARMOR +17+i, "Player\\");
	    OpenTexture(MODEL_PANTS +17+i, "Player\\");
	    OpenTexture(MODEL_GLOVES+17+i, "Player\\");
	    OpenTexture(MODEL_BOOTS +17+i, "Player\\");
    }

	OpenTexture ( MODEL_MASK_HELM+0, "Player\\" );
	OpenTexture ( MODEL_MASK_HELM+5, "Player\\" );
	OpenTexture ( MODEL_MASK_HELM+6, "Player\\" );
	OpenTexture ( MODEL_MASK_HELM+8, "Player\\" );
	OpenTexture ( MODEL_MASK_HELM+9, "Player\\" );

    OpenTexture(MODEL_SHADOW_BODY,"Player\\");
	{
		LoadBitmap("Player\\Robe01.jpg",BITMAP_ROBE);
		LoadBitmap("Player\\Robe02.jpg",BITMAP_ROBE+1);
		LoadBitmap("Player\\Robe03.tga",BITMAP_ROBE+2);
		LoadBitmap("Player\\DarklordRobe.tga",BITMAP_ROBE+7);
		LoadBitmap("Item\\msword03.tga",BITMAP_ROBE+8);		// �ĸ��� ���� ���� ���� õ
		LoadBitmap("Item\\dl_redwings02.tga",BITMAP_ROBE+9);	// ������ ���� (��ũ3��) �� õ
		LoadBitmap("Item\\dl_redwings03.tga",BITMAP_ROBE+10);	// ������ ���� (��ũ3��) ��� õ
	}

	//(���ʴ��) ����, �渶����, ����, ���˻�, ��ũ�ε� �߰� ��Ʈ����
#ifdef _VS2008PORTING
	for(int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for(i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		OpenTexture( MODEL_ARMOR+29+i, "Player\\" );
		OpenTexture( MODEL_PANTS+29+i, "Player\\" );
		OpenTexture( MODEL_GLOVES+29+i, "Player\\" );
		OpenTexture( MODEL_BOOTS+29+i, "Player\\" );
	}
	OpenTexture( MODEL_HELM+29, "Player\\");
	OpenTexture( MODEL_HELM+30, "Player\\");
	OpenTexture( MODEL_HELM+31, "Player\\");
	OpenTexture( MODEL_HELM+33, "Player\\");

	//$ ũ���̿��� ������ �ؽ���
#ifdef _VS2008PORTING
	for(int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for(i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		OpenTexture( MODEL_ARMOR+34+i,	"Player\\" );
		OpenTexture( MODEL_PANTS+34+i,	"Player\\" );
		OpenTexture( MODEL_GLOVES+34+i, "Player\\" );
		OpenTexture( MODEL_BOOTS+34+i,	"Player\\" );
	}
	OpenTexture( MODEL_HELM+34, "Player\\");
	OpenTexture( MODEL_HELM+35, "Player\\");
	OpenTexture( MODEL_HELM+36, "Player\\");
	OpenTexture( MODEL_HELM+38, "Player\\");

	char szFileName[64];
	// ���̿÷����� ~ ���ͳ��� ��Ʈ
#ifdef _VS2008PORTING
	for (int i = 0; i < 6; ++i)
#else // _VS2008PORTING
	for (i = 0; i < 6; ++i)
#endif // _VS2008PORTING
	{
		::OpenTexture(MODEL_HELM  +39+i, "Player\\" );
		::OpenTexture(MODEL_ARMOR +39+i, "Player\\" );
		::OpenTexture(MODEL_PANTS +39+i, "Player\\" );
		::OpenTexture(MODEL_GLOVES+39+i, "Player\\" );
		::OpenTexture(MODEL_BOOTS +39+i, "Player\\" );

	// �κ��丮�� �ؽ�ó.
		::sprintf(szFileName, "Player\\InvenArmorMale%d.tga", 40+i);
		::LoadBitmap(szFileName, BITMAP_INVEN_ARMOR+i);
		::sprintf(szFileName, "Player\\InvenPantsMale%d.tga", 40+i);
		::LoadBitmap(szFileName, BITMAP_INVEN_PANTS+i);
	}

// ���Ͼ����� ��Ų�ؽ��� (�κ����������ϴ� ��Ų�κ��� ������ �ؽ���, �ؽ��� ��ü��)
#ifdef ADD_SOCKET_ITEM
	::sprintf(szFileName, "Player\\Item312_Armoritem.tga");		// ����μ�Ʈ (����)
	::LoadBitmap(szFileName, BITMAP_SKIN_ARMOR_DEVINE);
	::sprintf(szFileName, "Player\\Item312_Pantitem.tga");
	::LoadBitmap(szFileName, BITMAP_SKIN_PANTS_DEVINE);
	::sprintf(szFileName, "Player\\SkinClass706_upperitem.tga");	// ��ť������Ʈ (��ȯ����)
	::LoadBitmap(szFileName, BITMAP_SKIN_ARMOR_SUCCUBUS);
	::sprintf(szFileName, "Player\\SkinClass706_loweritem.tga");
	::LoadBitmap(szFileName, BITMAP_SKIN_PANTS_SUCCUBUS);
#endif // ADD_SOCKET_ITEM

	// ��ȯ����� ����, ��ũ �ø��� �� �ؽ�ó.
#ifdef _VS2008PORTING
	for (int i = 0; i < MODEL_ITEM_COMMON_NUM; ++i)
#else // _VS2008PORTING
	for (i = 0; i < MODEL_ITEM_COMMON_NUM; ++i)
#endif // _VS2008PORTING
	{
		::OpenTexture(MODEL_HELM2  +i, "Player\\");
		::OpenTexture(MODEL_ARMOR2 +i, "Player\\");
		::OpenTexture(MODEL_PANTS2 +i, "Player\\");
		::OpenTexture(MODEL_GLOVES2+i, "Player\\");
		::OpenTexture(MODEL_BOOTS2 +i, "Player\\");
	}

#ifdef ADD_SOCKET_ITEM
	// 45 "Ƽź(����)"
	// 46 "�극�̺�(����)"
	// 47 "����(���˻�)"
	// 48 "��Ʈ����(���˻�)"
	// 49 "������(����)"
	// 50 "�����(����)"
	// 51 "�п�(��ũ�ε�)"
	// 52 "�ϵ���(�渶����)"
	// 53 "��ť����(��ȯ����)"
	
	// ����
#ifdef _VS2008PORTING
	for(int i=45 ; i<=53 ; i++)
#else // _VS2008PORTING
	for( i=45 ; i<=53 ; i++)
#endif // _VS2008PORTING
	{
		if( i==47 || i== 48)
			continue;		// ���˻���������

		OpenTexture( MODEL_HELM+i, "Player\\" );
	} // for()
	
	// ����/����/�尩/����
#ifdef _VS2008PORTING
	for(int i=45 ; i<=53 ; i++)
#else // _VS2008PORTING
	for( i=45 ; i<=53 ; i++)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_ARMOR+i, "Player\\" );
		OpenTexture(MODEL_PANTS+i, "Player\\" );
		OpenTexture(MODEL_GLOVES+i, "Player\\" );
		OpenTexture(MODEL_BOOTS+i, "Player\\" );
	} // for()
#endif // ADD_SOCKET_ITEM

	// GM ���Ź��� ĳ���� �� �ε�
	OpenTexture(MODEL_GM_CHARACTER, "Skill\\");

#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef _VS2008PORTING
	for (int i = 0; i<MODEL_ITEM_COMMONCNT_RAGEFIGHTER; ++i)
#else // _VS2008PORTING
	for (i = 0; i<MODEL_ITEM_COMMONCNT_RAGEFIGHTER; ++i)
#endif // _VS2008PORTING
	{
		::OpenTexture(MODEL_HELM_MONK  +i, "Player\\");
		::OpenTexture(MODEL_ARMOR_MONK +i, "Player\\");
		::OpenTexture(MODEL_PANTS_MONK +i, "Player\\");
		::OpenTexture(MODEL_BOOTS_MONK +i, "Player\\");
	}
#ifdef _VS2008PORTING
	for(int i=0; i<3; ++i)
#else //_VS2008PORTING
	for(i=0; i<3; ++i)
#endif //_VS2008PORTING
	{
		::OpenTexture(MODEL_HELM  +59+i, "Player\\");
		::OpenTexture(MODEL_ARMOR +59+i, "Player\\");
		::OpenTexture(MODEL_PANTS +59+i, "Player\\");
		::OpenTexture(MODEL_BOOTS +59+i, "Player\\");
	}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENPLAYERTEXTURES );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// ������ �𵨸� ����Ÿ ��ü�� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenItems()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENITEMS, PROFILING_LOADING_OPENITEMS );
#endif // DO_PROFILING_FOR_LOADING

#ifndef _VS2008PORTING				// #ifndef
	int i;
#endif // _VS2008PORTING

    //////////////////////////////////////////////////////////////////////////
    //  ��. MODEL_SWORD
    //////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
    for(int i=0;i<17;i++)
#else // _VS2008PORTING
    for(i=0;i<17;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SWORD+i ,"Data\\Item\\","Sword" ,i+1);    //  ��.

    AccessModel(MODEL_SWORD+17 ,"Data\\Item\\","Sword" ,18);    //  ��ũ�극��Ŀ.
    AccessModel(MODEL_SWORD+18 ,"Data\\Item\\","Sword" ,19);    //  ���� �극�̵�.
    AccessModel(MODEL_SWORD+19 ,"Data\\Item\\","Sword" ,20);    //  ��õ���� �����.

	AccessModel(MODEL_SWORD+20 ,"Data\\Item\\","Sword" ,21);    // ���˻� �߰���
	AccessModel(MODEL_SWORD+21 ,"Data\\Item\\","Sword" ,22);    // ��� �߰���
	AccessModel ( MODEL_SWORD+31, "Data\\Item\\", "Sword", 32 );	//	���˻� ������.

	//////////////////////////////////////////////////////////////////////////
	//	����. MODEL_AXE
	//////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
	for(int i=0;i<9;i++)
#else // _VS2008PORTING
	for(i=0;i<9;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_AXE+i   ,"Data\\Item\\","Axe"   ,i+1);    //  ����.

	//////////////////////////////////////////////////////////////////////////
	//	�б�. MODEL_MACE
	//////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
	for(int i=0;i<7;i++)
#else // _VS2008PORTING
	for(i=0;i<7;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_MACE+i  ,"Data\\Item\\","Mace"  ,i+1);    //  �б�.
	AccessModel ( MODEL_MACE+7, "Data\\Item\\", "Mace", 8 );		//	���� �б�.

	// MODEL_MACE+8,9,10,11,12
#ifdef _VS2008PORTING
	for(int i=0; i<5; i++)
#else // _VS2008PORTING
	for(i=0; i<5; i++)
#endif // _VS2008PORTING
		AccessModel( MODEL_MACE+8+i, "Data\\Item\\", "Mace", 9+i);		// ��ũ�ε� �߰�����
	
	// ��ũ�ε� ���� ����
	AccessModel( MODEL_MACE+13, "Data\\Item\\", "Saint");

	//////////////////////////////////////////////////////////////////////////
	//	â. MODEL_SPEAR
	//////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
	for(int i=0;i<10;i++)
#else // _VS2008PORTING
	for(i=0;i<10;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SPEAR+i ,"Data\\Item\\","Spear" ,i+1);    //  â.
	AccessModel ( MODEL_SPEAR+10, "Data\\Item\\", "Spear", 11 );	//	��� â.

	//////////////////////////////////////////////////////////////////////////
	//	����. MODEL_SHIELD
	//////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
	for(int i=0;i<15;i++)
#else // _VS2008PORTING
	for(i=0;i<15;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SHIELD+i,"Data\\Item\\","Shield",i+1);    //  ����.
	AccessModel ( MODEL_SHIELD+15, "Data\\Item\\", "Shield", 16 );	//	�������.
	AccessModel ( MODEL_SHIELD+16, "Data\\Item\\", "Shield", 17 );	//	��������.

    //////////////////////////////////////////////////////////////////////////
    //  ������. MODEL_STAFF
    //////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
    for(int i=0;i<9;i++)
#else // _VS2008PORTING
    for(i=0;i<9;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_STAFF+i ,"Data\\Item\\","Staff" ,i+1);    //  ������.
    AccessModel( MODEL_STAFF+9, "Data\\Item\\", "Staff", 10 );       //  �Ƿ��� ������.
    AccessModel(MODEL_STAFF+10 ,"Data\\Item\\","Staff" ,11);        //  ��õ���� ����������.
    AccessModel(MODEL_STAFF+11 ,"Data\\Item\\","Staff" ,12);        //  ����� ������
#ifdef _VS2008PORTING
	for (int i = 14; i <= 20; ++i)
#else // _VS2008PORTING
	for (i = 14; i <= 20; ++i)
#endif // _VS2008PORTING
		::AccessModel(MODEL_STAFF+i, "Data\\Item\\", "Staff", i+1);	// ��ȯ���� ��ƽ.

    //////////////////////////////////////////////////////////////////////////
    //  Ȱ. MODEL_BOW
    //////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
	for(int i=0;i<7;i++)
#else // _VS2008PORTING
	for(i=0;i<7;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_BOW+i   ,"Data\\Item\\","Bow"   ,i+1);    //  Ȱ.
#ifdef _VS2008PORTING
	for(int i=0;i<7;i++)
#else // _VS2008PORTING
	for(i=0;i<7;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_BOW+i+8 ,"Data\\Item\\","CrossBow",i+1);  //  ����.
   	AccessModel(MODEL_BOW+7 ,"Data\\Item\\","Arrows",1);            //  ȭ��.
   	AccessModel(MODEL_BOW+15,"Data\\Item\\","Arrows",2);            //  ���� ȭ��.
   	AccessModel(MODEL_BOW+16,"Data\\Item\\","CrossBow",17);         //  ����Ʈ ����.
    AccessModel( MODEL_BOW+17, "Data\\Item\\", "Bow", 18 );    //  ���� ����.
    AccessModel(MODEL_BOW+18 ,"Data\\Item\\","Bow" ,19);        //  ��õ���� ����.
	AccessModel(MODEL_BOW+19, "Data\\Item\\", "CrossBow", 20 );	//	������ ����.
	AccessModel(MODEL_BOW+20, "Data\\Item\\", "Bow", 20 );	//	���� �߰�Ȱ.

    
    //////////////////////////////////////////////////////////////////////////
    //  �����/����. MODEL_HELPER
    //////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
    for(int i=0;i<3;i++)
#else // _VS2008PORTING
    for(i=0;i<3;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_HELPER+i,"Data\\Player\\","Helper",i+1);  //  ��ź. õ��. ���ϸ���. (��).
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_HELPER+i+8,"Data\\Item\\","Ring"  ,i+1);  //  ��������. ������.

	g_ChangeRingMgr->LoadItemModel();
   	
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_HELPER+i+12,"Data\\Item\\","Necklace"  ,i+1); //  �����.
    AccessModel( MODEL_HELPER+3, "Data\\Player\\", "Helper", 4 );		//  ����Ʈ�� ��.
    AccessModel( MODEL_HELPER+4, "Data\\Item\\", "DarkHorseHorn" );     //  ��ũȣ���� ��
    AccessModel( MODEL_HELPER+31,"Data\\Item\\", "DarkHorseSoul" );     //  ��ũȣ���� ��ȥ.
#ifdef PET_SYSTEM
    AccessModel( MODEL_HELPER+5, "Data\\Item\\", "SpiritBill" );        //  ��ũ���Ǹ�
#endif// PET_SYSTEM
#ifdef DARK_WOLF
    AccessModel( MODEL_HELPER+6, "Data\\Item\\", "DarkWolfTooth" );     //  ��ũ������ �̻�.
#endif// DARK_WOLF

    AccessModel( MODEL_HELPER+21, "Data\\Item\\", "FireRing" );          //  ���ǹ���"	
    AccessModel( MODEL_HELPER+22, "Data\\Item\\", "GroundRing" );        //  ���ǹ���"	
    AccessModel( MODEL_HELPER+23, "Data\\Item\\", "WindRing" );          //  �ٶ��ǹ���"	
    AccessModel( MODEL_HELPER+24, "Data\\Item\\", "ManaRing" );          //  �����ǹ���"	
    AccessModel( MODEL_HELPER+25, "Data\\Item\\", "IceNecklace" );       //  �����Ǹ����"
    AccessModel( MODEL_HELPER+26, "Data\\Item\\", "WindNecklace" );      //  �ٶ��Ǹ����"
    AccessModel( MODEL_HELPER+27, "Data\\Item\\", "WaterNecklace" );     //  ���Ǹ����"	
    AccessModel( MODEL_HELPER+28, "Data\\Item\\", "AgNecklace" );        //  ����Ǹ����"
    AccessModel( MODEL_HELPER+29, "Data\\Item\\", "EventChaosCastle" );//  �������� ���ʼ�Ʈ.
	AccessModel( MODEL_HELPER+7,  "Data\\Item\\", "Covenant" );          //  �뺴 ��� ����.
	AccessModel( MODEL_HELPER+11, "Data\\Item\\", "SummonBook" );        //  ��ȯ �ֹ���.
    AccessModel( MODEL_EVENT+18,  "Data\\Item\\", "LifeStoneItem" );     //  ������ ����.

	//^ �渱 ������ �� �ε�
	AccessModel( MODEL_HELPER+32, "Data\\Item\\", "FR_1" );     // ���� ����
	AccessModel( MODEL_HELPER+33, "Data\\Item\\", "FR_2" );     // ������ ��ȣ
	AccessModel( MODEL_HELPER+34, "Data\\Item\\", "FR_3" );     // �ͼ��� ����
	AccessModel( MODEL_HELPER+35, "Data\\Item\\", "FR_4" );     // ���Ǹ� ����
	AccessModel( MODEL_HELPER+36, "Data\\Item\\", "FR_5" );     // �η��� ���Ǹ�
	AccessModel( MODEL_HELPER+37, "Data\\Item\\", "FR_6" );     // �渱�� ���Ǹ�

#ifdef CSK_FREE_TICKET
	// ��������� ������ �� �ε�
	AccessModel(MODEL_HELPER+46, "Data\\Item\\partCharge1\\", "entrancegray");	// ���������� ���������(ȸ��)
	AccessModel(MODEL_HELPER+47, "Data\\Item\\partCharge1\\", "entrancered");	// ����ĳ�� ���������(������)
	AccessModel(MODEL_HELPER+48, "Data\\Item\\partCharge1\\", "entrancebleu");	// Į���� ���������(�Ķ���)
#endif // CSK_FREE_TICKET
	
#ifdef CSK_CHAOS_CARD
	// ī����ī�� ������ �� �ε�
	AccessModel(MODEL_POTION+54, "Data\\Item\\partCharge1\\", "juju");	// ī����ī��
#endif // CSK_CHAOS_CARD

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	AccessModel(MODEL_HELPER+43, "Data\\Item\\", "monmark01");	// �ؿ��� ���� (����� ����)
	AccessModel(MODEL_HELPER+44, "Data\\Item\\", "monmark02");	// �ؿ��� ���� (ǳ���� ����)
	AccessModel(MODEL_HELPER+45, "Data\\Item\\", "monmark03");	// �ؿ��� ���� (������ ����)
#endif //CSK_LUCKY_SEAL	
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	AccessModel(MODEL_HELPER+43, "Data\\Item\\partCharge1\\", "monmark01");	// �ؿ��� ���� (����� ����)
	AccessModel(MODEL_HELPER+44, "Data\\Item\\partCharge1\\", "monmark02");	// �ؿ��� ���� (ǳ���� ����)
	AccessModel(MODEL_HELPER+45, "Data\\Item\\partCharge1\\", "monmark03");	// �ؿ��� ���� (������ ����)
#endif //CSK_LUCKY_SEAL	
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
	
#ifdef CSK_LUCKY_CHARM
	AccessModel(MODEL_POTION+53, "Data\\Item\\partCharge1\\", "bujuck01");	// ����� ����
#endif //CSK_LUCKY_CHARM
	
#ifdef CSK_RARE_ITEM
	// ��;����� �� �ε�
	AccessModel(MODEL_POTION+58, "Data\\Item\\partCharge1\\", "expensiveitem01");
	AccessModel(MODEL_POTION+59, "Data\\Item\\partCharge1\\", "expensiveitem02a");
	AccessModel(MODEL_POTION+60, "Data\\Item\\partCharge1\\", "expensiveitem02b");
	AccessModel(MODEL_POTION+61, "Data\\Item\\partCharge1\\", "expensiveitem03a");
	AccessModel(MODEL_POTION+62, "Data\\Item\\partCharge1\\", "expensiveitem03b");
#endif // CSK_RARE_ITEM
	
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	AccessModel(MODEL_POTION+70, "Data\\Item\\partCharge2\\", "EPotionR");
	AccessModel(MODEL_POTION+71, "Data\\Item\\partCharge2\\", "EPotionB");
#endif //PSW_ELITE_ITEM
	
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	AccessModel(MODEL_POTION+72, "Data\\Item\\partCharge2\\", "elitescroll_quick");
	AccessModel(MODEL_POTION+73, "Data\\Item\\partCharge2\\", "elitescroll_depence");
	AccessModel(MODEL_POTION+74, "Data\\Item\\partCharge2\\", "elitescroll_anger");
	AccessModel(MODEL_POTION+75, "Data\\Item\\partCharge2\\", "elitescroll_magic");
	AccessModel(MODEL_POTION+76, "Data\\Item\\partCharge2\\", "elitescroll_strenth");
	AccessModel(MODEL_POTION+77, "Data\\Item\\partCharge2\\", "elitescroll_mana");
#endif //PSW_SCROLL_ITEM

#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING	// ���� ���� 100% ����
	char	szPC6Path[24];
	sprintf( szPC6Path, "Data\\Item\\partCharge6\\" );

	// ���� ���� 100% ����
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_KNIGHT_1_CHARM, szPC6Path, "amulet_satan");	// - ��ź ��������/���� 1�� ����            
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_MAGICIAN_1_CHARM, szPC6Path, "amulet_sky");	// - õ�� ��������/����� 1�� ����            
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_ELF_1_CHARM, szPC6Path, "amulet_elf");			// - ���� ��������/������ 1�� ����            
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_SUMMONER_1_CHARM, szPC6Path, "amulet_disaster");// - ��� ��������/��ȯ����� 1�� ����        
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_DARKLORD_1_CHARM, szPC6Path, "amulet_cloak");	// - ���� ���պ���/��ũ�ε�� 1�� ����

	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_KNIGHT_2_CHARM, szPC6Path, "amulet_dragon");	// - ���� ��������/���� 2�� ����          
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_MAGICIAN_2_CHARM, szPC6Path, "amulet_soul");	// - ��ȥ ��������/����� 2�� ����            
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_ELF_2_CHARM, szPC6Path, "amulet_spirit");		// - ���� ��������/������ 2�� ����            
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_SUMMONER_2_CHARM, szPC6Path, "amulet_despair");// - ���� ��������/��ȯ����� 2�� ����        
	AccessModel(MODEL_TYPE_CHARM_MIXWING+EWS_DARKKNIGHT_2_CHARM, szPC6Path, "amulet_dark");	// - ���� ��������/���˻�� 2�� ����          
#endif // LDS_ADD_CS6_CHARM_MIX_ITEM_WING
	
#ifdef PSW_SEAL_ITEM               // �̵� ����
	AccessModel(MODEL_HELPER+59, "Data\\Item\\partCharge2\\", "sealmove");
#endif //PSW_SEAL_ITEM
	
#ifdef PSW_FRUIT_ITEM              // ���� ����
	AccessModel(MODEL_HELPER+54, "Data\\Item\\partCharge2\\", "resetfruit_power");
	AccessModel(MODEL_HELPER+55, "Data\\Item\\partCharge2\\", "resetfruit_quick");
	AccessModel(MODEL_HELPER+56, "Data\\Item\\partCharge2\\", "resetfruit_strenth");
	AccessModel(MODEL_HELPER+57, "Data\\Item\\partCharge2\\", "resetfruit_energe");
	AccessModel(MODEL_HELPER+58, "Data\\Item\\partCharge2\\", "resetfruit_command");
#endif //PSW_FRUIT_ITEM
	
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	AccessModel(MODEL_POTION+78, "Data\\Item\\partCharge2\\", "secret_power");
	AccessModel(MODEL_POTION+79, "Data\\Item\\partCharge2\\", "secret_quick");
	AccessModel(MODEL_POTION+80, "Data\\Item\\partCharge2\\", "secret_strenth");
	AccessModel(MODEL_POTION+81, "Data\\Item\\partCharge2\\", "secret_energe");
	AccessModel(MODEL_POTION+82, "Data\\Item\\partCharge2\\", "secret_command");
#endif //PSW_SECRET_ITEM
	
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	AccessModel(MODEL_HELPER+60, "Data\\Item\\partCharge2\\", "indulgence");
#endif //PSW_INDULGENCE_ITEM
	
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET // ȯ���� ��� ���� �����
	AccessModel(MODEL_HELPER+61, "Data\\Item\\partCharge2\\", "entrancepurple");
#endif //PSW_CURSEDTEMPLE_FREE_TICKET
	
#ifdef PSW_RARE_ITEM
	AccessModel(MODEL_POTION+83, "Data\\Item\\partCharge2\\", "expensiveitem04b");
#endif //PSW_RARE_ITEM
#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	AccessModel(MODEL_POTION+145, "Data\\Item\\partCharge8\\", "rareitem_ticket7");
	AccessModel(MODEL_POTION+146, "Data\\Item\\partCharge8\\", "rareitem_ticket8");
	AccessModel(MODEL_POTION+147, "Data\\Item\\partCharge8\\", "rareitem_ticket9");
	AccessModel(MODEL_POTION+148, "Data\\Item\\partCharge8\\", "rareitem_ticket10");
	AccessModel(MODEL_POTION+149, "Data\\Item\\partCharge8\\", "rareitem_ticket11");
	AccessModel(MODEL_POTION+150, "Data\\Item\\partCharge8\\", "rareitem_ticket12");
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ���ð���, �ٸ�ī, �ٸ�ī ��7�� ��������� ������ �� �ε�
	AccessModel(MODEL_HELPER+125, "Data\\Item\\partCharge8\\", "DoppelCard");	// ���ð��� ���������
	AccessModel(MODEL_HELPER+126, "Data\\Item\\partCharge8\\", "BarcaCard");	// �ٸ�ī ���������
	AccessModel(MODEL_HELPER+127, "Data\\Item\\partCharge8\\", "Barca7Card");	// �ٸ�ī ��7�� ���������
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	AccessModel(MODEL_HELPER+128, "Data\\Item\\", "HawkStatue");	// ��������
	AccessModel(MODEL_HELPER+129, "Data\\Item\\", "SheepStatue");	// �������� 
	AccessModel(MODEL_HELPER+134, "Data\\Item\\", "horseshoe");		// ����
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	AccessModel(MODEL_HELPER+130, "Data\\Item\\", "ork_cham");			// ��ũ�� (oak cham)
//	AccessModel(MODEL_HELPER+131, "Data\\Item\\", "maple_cham");		// �������� 
	AccessModel(MODEL_HELPER+132, "Data\\Item\\", "goldenork_cham");	// ����ũ��
//	AccessModel(MODEL_HELPER+132, "Data\\Item\\", "goldenmaple_cham");	// ����������
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2	

#ifdef PSW_CHARACTER_CARD			// ĳ���� ī��
	AccessModel(MODEL_POTION+91, "Data\\Item\\partCharge3\\", "alicecard");	
#endif // PSW_CHARACTER_CARD

#ifdef PSW_NEW_CHAOS_CARD			// ī����ī�� ���, ī����ī�� ����, ī����ī�� �̴�
	AccessModel(MODEL_POTION+92, "Data\\Item\\partCharge3\\", "juju");	
	AccessModel(MODEL_POTION+93, "Data\\Item\\partCharge3\\", "juju");
	AccessModel(MODEL_POTION+95, "Data\\Item\\partCharge3\\", "juju");
#endif // PSW_NEW_CHAOS_CARD

#ifdef PSW_NEW_ELITE_ITEM
	AccessModel(MODEL_POTION+94, "Data\\Item\\partCharge2\\", "EPotionR");
#endif //PSW_NEW_ELITE_ITEM

#ifdef CSK_EVENT_CHERRYBLOSSOM
	AccessModel(MODEL_POTION+84, "Data\\Item\\cherryblossom\\", "cherrybox");		// ���ɻ���
	AccessModel(MODEL_POTION+85, "Data\\Item\\cherryblossom\\", "chwine");			// ���ɼ�
	AccessModel(MODEL_POTION+86, "Data\\Item\\cherryblossom\\", "chgateaux");		// ���ɰ��
	AccessModel(MODEL_POTION+87, "Data\\Item\\cherryblossom\\", "chpetal");			// ������
	AccessModel(MODEL_POTION+88, "Data\\Item\\cherryblossom\\", "chbranche");       // ��� ����
	AccessModel(MODEL_POTION+89, "Data\\Item\\cherryblossom\\", "chbranche_red");   // ������ ����
	AccessModel(MODEL_POTION+90, "Data\\Item\\cherryblossom\\", "chbranche_yellow");// ����� ����
#endif //CSK_EVENT_CHERRYBLOSSOM

#ifdef PSW_ADD_PC4_SEALITEM
	AccessModel(MODEL_HELPER+62, "Data\\Item\\partCharge4\\", "Curemark");
	AccessModel(MODEL_HELPER+63, "Data\\Item\\partCharge4\\", "Holinessmark");
#endif //PSW_ADD_PC4_SEALITEM

#ifdef PSW_ADD_PC4_SCROLLITEM
	AccessModel(MODEL_POTION+97, "Data\\Item\\partCharge4\\", "battlescroll");
	AccessModel(MODEL_POTION+98, "Data\\Item\\partCharge4\\", "strengscroll");
#endif //PSW_ADD_PC4_SCROLLITEM

#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	AccessModel(MODEL_POTION+96, "Data\\Item\\partCharge4\\", "strengamulet");
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
    AccessModel(MODEL_HELPER+64,"Data\\Item\\partCharge4\\","demon");  //���� ����
    AccessModel(MODEL_HELPER+65,"Data\\Item\\partCharge4\\","maria");  //���� ��ȣ����
#endif //LDK_ADD_PC4_GUARDIAN

#ifdef PJH_ADD_PANDA_PET
	AccessModel(MODEL_HELPER+80,"Data\\Item\\","PandaPet");  //�����
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_RUDOLPH_PET
	AccessModel(MODEL_HELPER+67,"Data\\Item\\xmas\\","xmas_deer");  //ũ�������� �絹����
#endif //LDK_ADD_RUDOLPH_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
	AccessModel(MODEL_HELPER+106,"Data\\Item\\partcharge7\\","pet_unicorn");  //������ ��
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
	AccessModel(MODEL_HELPER+123,"Data\\Item\\","skeletonpet");		// ���̷��� ��
#endif	// YDG_ADD_SKELETON_PET
	
#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	AccessModel(MODEL_HELPER+69, "Data\\Item\\partCharge5\\", "ressurection");	// ��Ȱ�� ����
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	AccessModel(MODEL_HELPER+70, "Data\\Item\\partCharge5\\", "potalcharm");	// �̵��� ����
#endif	// YDG_ADD_CS5_PORTAL_CHARM
	
#ifdef ASG_ADD_CS6_GUARD_CHARM
	AccessModel(MODEL_HELPER+81, "Data\\Item\\partCharge6\\", "suhocham01");	// ��ȣ�Ǻ���
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	AccessModel(MODEL_HELPER+82, "Data\\Item\\partCharge6\\", "imteam_protect");// �����ۺ�ȣ����
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER 
	AccessModel(MODEL_HELPER+93, "Data\\Item\\partCharge6\\", "MasterSealA");	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER 
	AccessModel(MODEL_HELPER+94, "Data\\Item\\partCharge6\\", "MasterSealB");	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER

#ifdef YDG_ADD_HEALING_SCROLL
	AccessModel(MODEL_POTION+140, "Data\\Item\\", "strengscroll");	// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL

	AccessModel(MODEL_HELPER+49, "Data\\Item\\", "scrollpaper");		// ���� �η縶��
	AccessModel(MODEL_HELPER+50, "Data\\Item\\", "oath");				// ȯ�������� ����
	AccessModel(MODEL_HELPER+51, "Data\\Item\\", "songbl");				// ���� �η縶��

	AccessModel(MODEL_HELPER+52, "Data\\Item\\", "condolstone");	// �ܵ����� �Ҳ�
	AccessModel(MODEL_HELPER+53, "Data\\Item\\", "condolwing");		// �ܵ����� ����

#ifdef CSK_PCROOM_ITEM
	AccessModel(MODEL_POTION+55, "Data\\Item\\", "roboxgreen");		// �ʷ�ȥ���ǻ���
	AccessModel(MODEL_POTION+56, "Data\\Item\\", "roboxred");		// ����
	AccessModel(MODEL_POTION+57, "Data\\Item\\", "roboxpurple");	// ����
#endif // CSK_PCROOM_ITEM

#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	AccessModel(MODEL_HELPER+96, "Data\\Item\\", "strongmark" );	// ������ ���� ((JPN)PC�� ������)
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH

	AccessModel(MODEL_POTION+64, "Data\\Item\\", "songss");			// ���ֹ��� ����
	
	AccessModel(MODEL_POTION+65, "Data\\Item\\", "deathbeamstone");	// ����������Ʈ�ǺҲ�
	AccessModel(MODEL_POTION+66, "Data\\Item\\", "hellhorn");		// �︶�̳��ǻ�
	AccessModel(MODEL_POTION+67, "Data\\Item\\", "phoenixfeather");	// ����Ǻһ����Ǳ���
	AccessModel(MODEL_POTION+68, "Data\\Item\\", "Deye");			// �ɿ��Ǵ�����
	
#ifdef ADD_SEED_SPHERE_ITEM
	// ���� ������ ��� (�õ�, ���Ǿ�, �õ彺�Ǿ�)
#ifdef _VS2008PORTING
	for (int i = 0; i < 6; ++i)
		AccessModel(MODEL_WING+60+i, "Data\\Item\\", "s30_seed");	// �õ� 6��
	for (int i = 0; i < 5; ++i)
		AccessModel(MODEL_WING+70+i, "Data\\Item\\", "s30_sphere_body", i + 1);	// ���Ǿ� 5��
	for (int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for (i = 0; i < 6; ++i)
		AccessModel(MODEL_WING+60+i, "Data\\Item\\", "s30_seed");	// �õ� 6��
	for (i = 0; i < 5; ++i)
		AccessModel(MODEL_WING+70+i, "Data\\Item\\", "s30_sphere_body", i + 1);	// ���Ǿ� 5��
	for (i = 0; i < 5; ++i)
#endif // _VS2008PORTING
	{
		for (int j = 0; j < 6; ++j)
			AccessModel(MODEL_WING+100+i*6+j, "Data\\Item\\", "s30_sphere", i + 1);	// �õ彺�Ǿ� 30��
	}
#endif	// ADD_SEED_SPHERE_ITEM

#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	AccessModel(MODEL_HELPER+107,"Data\\Item\\partcharge7\\","FatalRing");  // ġ��������
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	AccessModel(MODEL_HELPER+104,"Data\\Item\\partcharge7\\","injang_AG");  // AG���� ����
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	AccessModel(MODEL_HELPER+105,"Data\\Item\\partcharge7\\","injang_SD");  // SD���� ����
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	AccessModel(MODEL_HELPER+103,"Data\\Item\\partcharge7\\","EXPscroll");  // ��Ƽ ����ġ ���� ������
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	AccessModel(MODEL_POTION+133,"Data\\Item\\partcharge7\\","ESDPotion");  // ����Ʈ SDȸ�� ����
#endif	// YDG_ADD_CS7_ELITE_SD_POTION
	
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
	AccessModel(MODEL_HELPER+109,"Data\\Item\\InGameShop\\","PeriodRingBlue");  // InGameShop Item : ����(�����̾�/BLUE)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
	AccessModel(MODEL_HELPER+110,"Data\\Item\\InGameShop\\","PeriodRingRed");  // InGameShop Item : ����(���/RED)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
	AccessModel(MODEL_HELPER+111,"Data\\Item\\InGameShop\\","PeriodRingYellow");  // InGameShop Item : ����(������/yellow)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
	AccessModel(MODEL_HELPER+112,"Data\\Item\\InGameShop\\","PeriodRingViolet");  // InGameShop Item : ����(�ڼ���/violet)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
	AccessModel(MODEL_HELPER+113,"Data\\Item\\InGameShop\\","necklace_red");  // InGameShop Item : �����(���/red)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
	AccessModel(MODEL_HELPER+114,"Data\\Item\\InGameShop\\","necklace_blue");  // InGameShop Item : �����(���޶���/Blue)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
	AccessModel(MODEL_HELPER+115,"Data\\Item\\InGameShop\\","necklace_green");  // InGameShop Item : �����(�����̾�/Green)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	AccessModel(MODEL_HELPER+116, "Data\\Item\\", "monmark02");	// �ű� ǳ���� ����
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	AccessModel(MODEL_WING+130,"Data\\Item\\","DarkLordRobe");	// ������ ����
 	AccessModel(MODEL_WING+131,"Data\\Item\\Ingameshop\\","alice1wing");		// ����� ����.
	AccessModel(MODEL_WING+132,"Data\\Item\\Ingameshop\\","elf_wing");			// ���� ����.
	AccessModel(MODEL_WING+133,"Data\\Item\\Ingameshop\\","angel_wing");		// õ���� ����.
	AccessModel(MODEL_WING+134,"Data\\Item\\Ingameshop\\","devil_wing");		// ��ź ����.
#endif //LDK_ADD_INGAMESHOP_SMALL_WING

#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	AccessModel(MODEL_HELPER+124, "Data\\Item\\partCharge6\\", "ChannelCard");	// ���� ä�� �����.
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET

    //////////////////////////////////////////////////////////////////////////
    //  ����/����. MODEL_POTION.
    //////////////////////////////////////////////////////////////////////////
#ifdef _VS2008PORTING
    for(int i=0;i<7;i++)
#else // _VS2008PORTING
    for(i=0;i<7;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_POTION+i,"Data\\Item\\","Potion",i+1);    //  ����.
   	AccessModel(MODEL_POTION+8 ,"Data\\Item\\","Antidote",1);       //  �ص���.
   	AccessModel(MODEL_POTION+9 ,"Data\\Item\\","Beer",1);           //  ��.
   	AccessModel(MODEL_POTION+10,"Data\\Item\\","Scroll",1);         //  ������ȯ����.
   	AccessModel(MODEL_POTION+11,"Data\\Item\\","MagicBox",1);       //  ����.
   	AccessModel(MODEL_POTION+12,"Data\\Item\\","Event",1);          //  �̺�Ʈ.
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
        AccessModel(MODEL_POTION+i+13,"Data\\Item\\","Jewel",i+1);
    AccessModel(MODEL_POTION+15,"Data\\Item\\","Gold",1);
    AccessModel(MODEL_POTION+16,"Data\\Item\\","Jewel",3);
#ifdef _VS2008PORTING
	for(int i=0;i<3;i++)
#else // _VS2008PORTING
	for(i=0;i<3;i++)
#endif // _VS2008PORTING
		AccessModel(MODEL_POTION+17+i,"Data\\Item\\","Devil",i);	// �Ǹ��� ����
	AccessModel(MODEL_POTION+20,"Data\\Item\\","Drink",0);	        // ����� ����

    AccessModel(MODEL_POTION+21,"Data\\Item\\","ConChip",0);        //  ��Ĩ.

    AccessModel(MODEL_POTION+31,"Data\\Item\\","suho",-1);        //  ��ȣ�Ǻ���
	AccessModel(MODEL_HELPER+38,"Data\\Item\\","kanneck2");        //  ������ �Ҵ�Ʈ
	AccessModel(MODEL_POTION+41,"Data\\Item\\","rs");              //  ��ȭ�� ����(����)
	AccessModel(MODEL_POTION+42,"Data\\Item\\","jos");             //  ��ȭ�� ����(����)
	AccessModel(MODEL_POTION+43,"Data\\Item\\","LowRefineStone");         //  �ϱ� ���ü�
	AccessModel(MODEL_POTION+44,"Data\\Item\\","HighRefineStone");         //  ��� ���ü�

	AccessModel(MODEL_POTION+7, "Data\\Item\\","SpecialPotion" );   //  �ູ�� ����, ��ȥ�� ����.//���ƹ���

#ifdef _VS2008PORTING
    for ( int i=0; i<4; ++i )
#else // _VS2008PORTING
    for ( i=0; i<4; ++i )
#endif // _VS2008PORTING
    {
        AccessModel(MODEL_POTION+23+i, "Data\\Item\\", "Quest", i); //  ������ �� ~ ��Ŭ.
    }
    AccessModel(MODEL_POTION+27, "Data\\Item\\", "godesteel" );     //  ����� �ݼ�.
#ifdef _VS2008PORTING
	for(int i=0; i<2; i++) 
#else // _VS2008PORTING
	for(i=0; i<2; i++) 
#endif // _VS2008PORTING
	{
		AccessModel ( MODEL_POTION+28+i, "Data\\Item\\", "HELLASITEM", i);   //  �Ҿ��������, ����� ǥ��
	}
	//�ǵ� ����
#ifdef _VS2008PORTING
	for(int i=0; i<3; ++i)
#else // _VS2008PORTING
	for(i=0; i<3; ++i)
#endif // _VS2008PORTING
		AccessModel ( MODEL_POTION+35+i, "Data\\Item\\", "sdwater", i+1);

	//���� ����
#ifdef _VS2008PORTING
	for(int i=0; i<3; ++i)
#else // _VS2008PORTING
	for(i=0; i<3; ++i)
#endif // _VS2008PORTING
		AccessModel ( MODEL_POTION+38+i, "Data\\Item\\", "megawater", i+1);
	
#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
	// �����ȭ
	AccessModel(MODEL_POTION+120,"Data\\Item\\InGameShop\\","gold_coin");
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	AccessModel(MODEL_POTION+121,"Data\\Item\\InGameShop\\","itembox_gold");
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
	AccessModel(MODEL_POTION+122,"Data\\Item\\InGameShop\\","itembox_silver");
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
	AccessModel(MODEL_POTION+123,"Data\\Item\\InGameShop\\","itembox_gold");
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
	AccessModel(MODEL_POTION+124,"Data\\Item\\InGameShop\\","itembox_silver");
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
	for(int k=0; k<6; k++)
	{
		AccessModel(MODEL_POTION+134+k,"Data\\Item\\InGameShop\\","package_money_item");
	}
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX

	AccessModel(MODEL_COMPILED_CELE,"Data\\Item\\","Jewel",1);			// �ູ�� ���� ����
	AccessModel(MODEL_COMPILED_SOUL,"Data\\Item\\","Jewel",2);			// ��ȥ�� ���� ����
#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	AccessModel(MODEL_WING+136, "Data\\Item\\", "Jewel",	3);			// ������ ���� ����
	AccessModel(MODEL_WING+137, "Data\\Item\\", "jewel",	22);		// â���� ���� ����
	AccessModel(MODEL_WING+138, "Data\\Item\\", "suho", -1);			// ��ȣ�� ���� ����
	AccessModel(MODEL_WING+139, "Data\\Item\\", "rs");					// ��ȭ�� ����(����) : ���� ����
	AccessModel(MODEL_WING+140, "Data\\Item\\", "jos");					// ��ȭ�� ����(����) : ��ȭ�� ����
	AccessModel(MODEL_WING+141, "Data\\Item\\", "Jewel", 15);			// ȥ���� ����
	AccessModel(MODEL_WING+142, "Data\\Item\\", "LowRefineStone");		// �ϱ� ���ü�
	AccessModel(MODEL_WING+143, "Data\\Item\\", "HighRefineStone");		// ��� ���ü�
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

    //////////////////////////////////////////////////////////////////////////
    //  �̺�Ʈ. MODEL_EVENT.
    //////////////////////////////////////////////////////////////////////////
    AccessModel(MODEL_EVENT+4,"Data\\Item\\","MagicBox",2);	        // ��ź�Ǻ�
	AccessModel(MODEL_EVENT+6,"Data\\Item\\","MagicBox",5);	        // ����� ��Ʈ
	AccessModel(MODEL_EVENT+7,"Data\\Item\\","Beer",2);	            // ����� �ø���
	AccessModel(MODEL_EVENT+8,"Data\\Item\\","MagicBox",6);	        // �� ����
	AccessModel(MODEL_EVENT+9,"Data\\Item\\","MagicBox",7);	        // �� ����

#ifdef PBG_ADD_SANTAINVITATION
	AccessModel(MODEL_HELPER+66, "Data\\Item\\xmas\\", "santa_village", -1);		//��Ÿ������ �ʴ���.
#endif //PBG_ADD_SANTAINVITATION

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	AccessModel(MODEL_POTION+100, "Data\\Item\\", "coin7", -1);			//����� ����
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

	g_XmasEvent->LoadXmasEventItem();

#ifdef USE_EVENT_ELDORADO
	AccessModel(MODEL_EVENT+10,"Data\\Item\\","MagicBox",8);	        // ������
#endif

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	AccessModel(MODEL_EVENT+5,"Data\\Item\\","MagicBox",4);	        // ���� �ָӴ�.
#else
	AccessModel(MODEL_EVENT+5,"Data\\Item\\","MagicBox",3);	        // ����
#endif
	
#ifdef _PVP_MURDERER_HERO_ITEM
	AccessModel(MODEL_POTION+30,"Data\\Item\\","PkHair",-1);	        // �Ӹ�ī��
#endif	// _PVP_MURDERER_HERO_ITEM

	AccessModel(MODEL_POTION+63,"Data\\Item\\", "GM", 1);				// ����
	AccessModel(MODEL_POTION+52,"Data\\Item\\", "GM", 2);				// GM��������

    AccessModel(MODEL_EVENT    ,"Data\\Item\\","Event",2);
   	AccessModel(MODEL_EVENT+1  ,"Data\\Item\\","Event",3);
	
#ifdef YDG_ADD_FIRECRACKER_ITEM
	AccessModel(MODEL_POTION+99,"Data\\Item\\XMas\\", "xmasfire", -1);				// ũ�������� ����
#endif	// YDG_ADD_FIRECRACKER_ITEM

#ifdef _VS2008PORTING
	for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
	for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        if ( i<3 )
        {
            AccessModel( MODEL_HELPER+16+i, "Data\\Item\\", "EventBloodCastle", i );   //  ��õ���� ��, ���� ��, �������.
        }
        else
        {
            AccessModel( MODEL_EVENT+11+(i-3), "Data\\Item\\", "EventBloodCastle", i );   //  ����, ��õ���� ����������, ��õ���� �����, ��õ���� ���뼮��.
        }
    }
	
	AccessModel( MODEL_EVENT+12, "Data\\Item\\", "QuestItem3RD", 0);		//. ������ ����
	AccessModel( MODEL_EVENT+13, "Data\\Item\\", "QuestItem3RD", 1);		//. ��ũ����
	AccessModel( MODEL_EVENT+14, "Data\\Item\\", "RingOfLordEvent", 0);		//. ������ ����
	AccessModel( MODEL_EVENT+15, "Data\\Item\\", "MagicRing", 0);		// �������� ����

#ifdef CHINA_MOON_CAKE
    //  �߱��϶��� ���. ( �ϴ��� �ٸ� ���󿡼��� ������� �����Ƿ� ���� ó������ �ʴ´�. ).
    AccessModel ( MODEL_EVENT+17, "Data\\Item\\", "MoonCake" );         //  �߱� �̺�Ʈ ����.
#endif// CHINA_MOON_CAKE

    AccessModel(MODEL_POTION+22, "Data\\Item\\", "jewel", 22);          //  â���� ����.
#ifdef _VS2008PORTING
    for ( int i=0; i<2; ++i )
#else // _VS2008PORTING
    for ( i=0; i<2; ++i )
#endif // _VS2008PORTING
    {
        AccessModel(MODEL_HELPER+14+i, "Data\\Item\\", "Quest", 4+i);   //  ��ũ�� ���� ~ ��Ŭ.
    }

	AccessModel ( MODEL_EVENT+16,  "Data\\Item\\", "DarkLordSleeve" );              //  ������ �Ҹ�.
	AccessModel ( MODEL_HELPER+30, "Data\\Item\\", "DarkLordRobe" );                //  ������ ����.

#ifdef _VS2008PORTING
    for(int i=0;i<3;i++)
#else // _VS2008PORTING
    for(i=0;i<3;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_WING+i,"Data\\Item\\","Wing"  ,i+1);      //  ����.

#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        AccessModel(MODEL_WING+3+i,"Data\\Item\\","Wing"  ,4+i);            //  ���� ����.
    }

#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        AccessModel(MODEL_WING+36+i,"Data\\Item\\","Wing"  ,8+i);	// 3�� ����
    }
	AccessModel ( MODEL_WING+40, "Data\\Item\\", "DarkLordRobe02" );                //  ������ ����
#ifdef ADD_ALICE_WINGS_1
#ifdef ADD_ALICE_WINGS_2
#ifdef _VS2008PORTING
	for (int i = 41; i <= 43; ++i)
#else // _VS2008PORTING
	for (i = 41; i <= 43; ++i)
#endif // _VS2008PORTING
#else	// ADD_ALICE_WINGS_2
	for (i = 41; i < 43; ++i)
#endif	// ADD_ALICE_WINGS_2
		::AccessModel(MODEL_WING+i, "Data\\Item\\", "Wing", i+1);		// ��ȯ���� ����.
#endif	// ADD_ALICE_WINGS_1

	AccessModel(MODEL_STAFF+21, "Data\\Item\\", "Book_of_Sahamutt");	// ���Ϲ�Ʈ�� å
	AccessModel(MODEL_STAFF+22, "Data\\Item\\", "Book_of_Neil");		// ���� å
#ifdef ASG_ADD_SUMMON_RARGLE
	AccessModel(MODEL_STAFF+23, "Data\\Item\\", "Book_of_Rargle");		// ����� ��.
#endif	// ASG_ADD_SUMMON_RARGLE

#ifdef _VS2008PORTING
	for(int i=0; i<9; ++i)
#else // _VS2008PORTING
	for(i=0; i<9; ++i)
#endif // _VS2008PORTING
	{
		AccessModel(MODEL_ETC+19+i, "Data\\Item\\", "rollofpaper");
	}

#ifdef _VS2008PORTING
    for(int i=0;i<13;i++)
#else // _VS2008PORTING
    for(i=0;i<13;i++)
#endif // _VS2008PORTING
	{
		if ( i+7 != 15)
	      	AccessModel(MODEL_WING+i+7,"Data\\Item\\","Gem",i+1);
	}

    AccessModel(MODEL_WING+15,"Data\\Item\\","Jewel",15);
	AccessModel(MODEL_WING+20,"Data\\Item\\","Gem", 14 );
	
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	AccessModel(MODEL_WING+44,"Data\\Item\\","Gem",6);
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	AccessModel(MODEL_WING+45,"Data\\Item\\","Gem",6);
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	AccessModel(MODEL_WING+46,"Data\\Item\\","Gem",6);
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	AccessModel(MODEL_WING+47,"Data\\Item\\","Gem",6);
#endif	// YDG_ADD_SKILL_FLAME_STRIKE

#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        AccessModel ( MODEL_WING+21+i,"Data\\Item\\","SkillScroll" );
    }
	AccessModel ( MODEL_WING+35,"Data\\Item\\","SkillScroll" );
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	AccessModel ( MODEL_WING+48,"Data\\Item\\","SkillScroll" );
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef HELLOWIN_EVENT
	AccessModel( MODEL_POTION+45,"Data\\Item\\","hobakhead");
	AccessModel( MODEL_POTION+46,"Data\\Item\\","hellowinscroll");
	AccessModel( MODEL_POTION+47,"Data\\Item\\","hellowinscroll");
	AccessModel( MODEL_POTION+48,"Data\\Item\\","hellowinscroll");
	AccessModel( MODEL_POTION+49,"Data\\Item\\","Gogi");
	AccessModel( MODEL_POTION+50,"Data\\Item\\","pumpkincup");
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	AccessModel( MODEL_POTION+32,"Data\\Item\\","giftbox_bp");
	AccessModel( MODEL_POTION+33,"Data\\Item\\","giftbox_br");
	AccessModel( MODEL_POTION+34,"Data\\Item\\","giftbox_bb");

	AccessModel( MODEL_EVENT+21,"Data\\Item\\","p03box");
	AccessModel( MODEL_EVENT+22,"Data\\Item\\","obox02");
	AccessModel( MODEL_EVENT+23,"Data\\Item\\","blue01");
#endif
	AccessModel( MODEL_WING+32,"Data\\Item\\","giftbox_r");
	AccessModel( MODEL_WING+33,"Data\\Item\\","giftbox_g");
	AccessModel( MODEL_WING+34,"Data\\Item\\","giftbox_b");
#ifdef MYSTERY_BEAD
	AccessModel(MODEL_EVENT+19,"Data\\Item\\","Bead");
	AccessModel(MODEL_EVENT+20,"Data\\Item\\","Crystal");
#endif // MYSTERY_BEAD

#ifdef _VS2008PORTING
	for(int i=0;i<19;i++)
#else // _VS2008PORTING
	for(i=0;i<19;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_ETC+i,"Data\\Item\\","Book",i+1);
	
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	AccessModel(MODEL_ETC+29,"Data\\Item\\","Book",18);
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM

#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER	// �������� ���� (������ ���� ����)
	AccessModel(MODEL_ETC+28,"Data\\Item\\","Book",18);	
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER

	AccessModel(MODEL_SWORD+22, "Data\\Item\\", "HDK_Sword");
	AccessModel(MODEL_SWORD+23, "Data\\Item\\", "HDK_Sword2");
	AccessModel(MODEL_MACE+14, "Data\\Item\\", "HDK_Mace");
	AccessModel(MODEL_BOW+21, "Data\\Item\\", "HDK_Bow");
	AccessModel(MODEL_STAFF+12, "Data\\Item\\", "HDK_Staff");
	
	AccessModel(MODEL_SWORD+24, "Data\\Item\\", "CW_Sword");	//$ ũ���� ���� �����
	AccessModel(MODEL_SWORD+25, "Data\\Item\\", "CW_Sword2");	// ���˻��
	AccessModel(MODEL_MACE+15, "Data\\Item\\", "CW_Mace");		// ��ũ�ε����
	AccessModel(MODEL_BOW+22, "Data\\Item\\", "CW_Bow");		// ����Ȱ
	AccessModel(MODEL_STAFF+13, "Data\\Item\\", "CW_Staff");	// �渶����������
	
// ���Ͼ����� �߰� (Model)
#ifdef ADD_SOCKET_ITEM
	// ��
	AccessModel(MODEL_SWORD+26, "Data\\Item\\", "Sword_27");	// �ö�������
	AccessModel(MODEL_SWORD+27, "Data\\Item\\", "Sword_28");	// �ҵ�극��Ŀ
	AccessModel(MODEL_SWORD+28, "Data\\Item\\", "Sword_29");	// ��ٽ�Ÿ��
	// �б�
	AccessModel(MODEL_MACE+16, "Data\\Item\\", "Mace_17");		// ���ν�Ʈ���̽�
	AccessModel(MODEL_MACE+17, "Data\\Item\\", "Mace_18");		// �ۼַ�Ʈ����
	// Ȱ/����
	AccessModel(MODEL_BOW+23, "Data\\Item\\", "Bow_24");		// ��ũ���ð�
	// ������
	AccessModel(MODEL_STAFF+30, "Data\\Item\\", "Staff_31");		// ���鸮������
	AccessModel(MODEL_STAFF+31, "Data\\Item\\", "Staff_32");		// �κ����˽�����
	AccessModel(MODEL_STAFF+32, "Data\\Item\\", "Staff_33");		// �ҿ�긵��
	// ����
	AccessModel(MODEL_SHIELD+17, "Data\\Item\\", "Shield_18");		// ũ�����۷θ�
	AccessModel(MODEL_SHIELD+18, "Data\\Item\\", "Shield_19");		// �����Ǵ��ǵ�
	AccessModel(MODEL_SHIELD+19, "Data\\Item\\", "Shield_20");		// ���ν�Ʈ�踮��
	AccessModel(MODEL_SHIELD+20, "Data\\Item\\", "Shield_21");		// ��������
#endif // ADD_SOCKET_ITEM

#ifdef CSK_ADD_ITEM_CROSSSHIELD
	AccessModel(MODEL_SHIELD+21, "Data\\Item\\", "crosssheild");		// ũ�ν��ǵ�
#endif // CSK_ADD_ITEM_CROSSSHIELD

#ifdef LDK_ADD_GAMBLERS_WEAPONS
	AccessModel(MODEL_BOW+24, "Data\\Item\\", "gamblebow");				// �׺� ���� Ȱ
	AccessModel(MODEL_STAFF+33, "Data\\Item\\", "gamble_wand");			// �׺� ���� ������
	AccessModel(MODEL_STAFF+34, "Data\\Item\\", "gamble_stick");		// �׺� ���� ������(��ȯ�����)
	AccessModel(MODEL_SPEAR+11, "Data\\Item\\", "gamble_scyder01");		// �׺� ���� ��
	AccessModel(MODEL_MACE+18, "Data\\Item\\", "gamble_safter01");		// �׺� ���� ����
#endif //LDK_ADD_GAMBLERS_WEAPONS

#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
	AccessModel(MODEL_HELPER+71, "Data\\Item\\", "gamble_scyderx01");	//�׺��� ��
	AccessModel(MODEL_HELPER+72, "Data\\Item\\", "gamble_wand01");		//�׺��� ������
	AccessModel(MODEL_HELPER+73, "Data\\Item\\", "gamble_bowx01");		//�׺��� ����
	AccessModel(MODEL_HELPER+74, "Data\\Item\\", "gamble_safterx01");	//�׺��� ����
 	AccessModel(MODEL_HELPER+75, "Data\\Item\\", "gamble_stickx01");	//�׺��� ��ƽ
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef PBG_ADD_CHARACTERCARD
	AccessModel(MODEL_HELPER+97, "Data\\Item\\Ingameshop\\", "charactercard");	//���˻� ĳ���� ī��
	AccessModel(MODEL_HELPER+98, "Data\\Item\\Ingameshop\\", "charactercard");	//��ũ�ε� ĳ���� ī��
	AccessModel(MODEL_POTION+91, "Data\\Item\\partCharge3\\", "alicecard");		//��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	AccessModel(MODEL_HELPER+99, "Data\\Item\\Ingameshop\\", "key");		//ĳ���� ���� ����
	AccessModel(MODEL_SLOT_LOCK, "Data\\Item\\Ingameshop\\", "lock");		//ĳ���� ���� �ڹ���
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
#ifdef PBG_MOD_SECRETITEM
	AccessModel(MODEL_HELPER+117, "Data\\Item\\Ingameshop\\", "FRpotionD");	//���ϱ�Ȱ���Ǻ��(������Ʈ �������� ���� �� �ε�)
#else //PBG_MOD_SECRETITEM
	AccessModel(MODEL_HELPER+117, "Data\\Item\\Ingameshop\\", "FRpotionA");	//���ϱ�Ȱ���Ǻ��(������Ʈ �������� ���� �� �ε�)
#endif //PBG_MOD_SECRETITEM
	AccessModel(MODEL_HELPER+118, "Data\\Item\\Ingameshop\\", "FRpotionA");	//�ϱ�Ȱ���Ǻ��
	AccessModel(MODEL_HELPER+119, "Data\\Item\\Ingameshop\\", "FRpotionB");	//�߱�Ȱ���Ǻ��
	AccessModel(MODEL_HELPER+120, "Data\\Item\\Ingameshop\\", "FRpotionC");	//���Ȱ���Ǻ��
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	AccessModel(MODEL_POTION+110, "Data\\Item\\","indication");	// ������ ǥ��
	AccessModel(MODEL_POTION+111, "Data\\Item\\","speculum");	// ������ ����
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	AccessModel(MODEL_POTION+101, "Data\\Item\\","doubt_paper");		// �ǹ�������
	AccessModel(MODEL_POTION+102, "Data\\Item\\","warrant");			// ���̿��� ��ɼ�
	AccessModel(MODEL_POTION+109, "Data\\Item\\","secromicon");			// ��ũ�ι���
	for(int c=0; c<6; c++)
	{
		AccessModel(MODEL_POTION+103+c, "Data\\Item\\","secromicon_piece");	// ��ũ�ι��� ����
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
	AccessModel(MODEL_POTION+112, "Data\\Item\\Ingameshop\\","ItemBoxKey_silver");
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
	AccessModel(MODEL_POTION+113, "Data\\Item\\Ingameshop\\","ItemBoxKey_gold");
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6	// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
	{
		for(int c=0; c<6; c++)
		{
			AccessModel(MODEL_POTION+114+c, "Data\\Item\\Ingameshop\\","primium_membership_item");	// �����̾�, ���ױ�, �����Ǿ����� ���� �� �ε�
		}
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4	// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
	{
		for(int c=0; c<4; c++)
		{
			AccessModel(MODEL_POTION+126+c, "Data\\Item\\Ingameshop\\","primium_membership_item");	// �����̾�, ���ױ�, �����Ǿ����� ���� �� �ε�
		}
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	{
		for(int c=0; c<3; c++)
		{
			AccessModel(MODEL_POTION+130+c, "Data\\Item\\Ingameshop\\","primium_membership_item");	// �����̾�, ���ױ�, �����Ǿ����� ���� �� �ε�
		}
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	{
		AccessModel(MODEL_HELPER+121, "Data\\Item\\Ingameshop\\", "entrancegreen");	// ī�����ɽ� ��������� �ε�
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef PBG_ADD_GENSRANKING
	AccessModel(MODEL_POTION+141, "Data\\Item\\", "requitalbox_red");		// ������
	AccessModel(MODEL_POTION+142, "Data\\Item\\", "requitalbox_violet");
	AccessModel(MODEL_POTION+143, "Data\\Item\\", "requitalbox_blue");
	AccessModel(MODEL_POTION+144, "Data\\Item\\", "requitalbox_wood");
#endif //PBG_ADD_GENSRANKING
#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	AccessModel(MODEL_POTION+151, "Data\\Item\\", "rollofpaper");		// 1���� �Ƿڼ�
	AccessModel(MODEL_POTION+152, "Data\\Item\\", "rollofpaper");		// 1���� �Ƿ� �Ϸ� Ȯ�μ�
	AccessModel(MODEL_POTION+153, "Data\\Item\\", "songss");			// ��Ÿ����Ʈ
	AccessModel(MODEL_POTION+154, "Data\\Item\\", "hydra_jewel");		// ĮƮ��
	AccessModel(MODEL_POTION+155, "Data\\Item\\", "tan");				// źŻ�ν��� ����
	AccessModel(MODEL_POTION+156, "Data\\Item\\", "Mace01");			// ����� �������� ������
	AccessModel(MODEL_POTION+157, "Data\\Item\\", "roboxgreen");		// �ʷϺ� ����
	AccessModel(MODEL_POTION+158, "Data\\Item\\", "roboxred");			// ������ ����
	AccessModel(MODEL_POTION+159, "Data\\Item\\", "roboxpurple");		// ����� ����
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM
#ifdef LDK_ADD_14_15_GRADE_ITEM_MODEL
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_ARMLEFT,	"Data\\Item\\", "class15_armleft");		// 14, 15��� ���� �� ����
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_ARMRIGHT,	"Data\\Item\\", "class15_armright");	// 14, 15��� ���� �� ������
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_BODYLEFT,	"Data\\Item\\", "class15_bodyleft");	// 14, 15��� ���� �� ���ʿ���
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_BODYRIGHT,	"Data\\Item\\", "class15_bodyright");	// 14, 15��� ���� �� ���ʿ�����
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_BOOTLEFT,	"Data\\Item\\", "class15_bootleft");	// 14, 15��� ���� �� �޹�
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_BOOTRIGHT,	"Data\\Item\\", "class15_bootright");	// 14, 15��� ���� �� ������
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_HEAD,		"Data\\Item\\", "class15_head");		// 14, 15��� ���� �� �Ӹ�
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_PANTLEFT,	"Data\\Item\\", "class15_pantleft");	// 14, 15��� ���� �� ��������
	AccessModel(MODEL_15GRADE_ARMOR_OBJ_PANTRIGHT,	"Data\\Item\\", "class15_pantright");	// 14, 15��� ���� �� ����������
#endif //LDK_ADD_14_15_GRADE_ITEM_MODEL
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	AccessModel(MODEL_WING+49, "Data\\Item\\", "Wing", 50);				// �����Ǹ���
	AccessModel(MODEL_WING+50, "Data\\Item\\", "Wing", 51);				// �����Ǹ���
	AccessModel(MODEL_WING+135, "Data\\Item\\", "Wing", 50);			// ���������Ǹ���
	LoadBitmap("Item\\NCcape.tga", BITMAP_NCCAPE, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Item\\monk_manto01.TGA", BITMAP_MANTO01, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Item\\monke_manto.TGA", BITMAP_MANTOE, GL_LINEAR, GL_REPEAT);
	g_CMonkSystem.LoadModelItem();
	for(int _nRollIndex=0; _nRollIndex<7; ++_nRollIndex)
		AccessModel(MODEL_ETC+30+_nRollIndex, "Data\\Item\\", "rollofpaper");		// ��ų���þ�����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

#ifdef LEM_ADD_LUCKYITEM	// LuckyItem Data AccesModel
	AccessModel(MODEL_HELPER+135, "Data\\Item\\LuckyItem\\", "LuckyCardgreen");				
	AccessModel(MODEL_HELPER+136, "Data\\Item\\LuckyItem\\", "LuckyCardgreen");		
	AccessModel(MODEL_HELPER+137, "Data\\Item\\LuckyItem\\", "LuckyCardgreen");		
	AccessModel(MODEL_HELPER+138, "Data\\Item\\LuckyItem\\", "LuckyCardgreen");		
	AccessModel(MODEL_HELPER+139, "Data\\Item\\LuckyItem\\", "LuckyCardgreen");		
	AccessModel(MODEL_HELPER+140, "Data\\Item\\LuckyItem\\", "LuckyCardred");
	AccessModel(MODEL_HELPER+141, "Data\\Item\\LuckyItem\\", "LuckyCardred");		
	AccessModel(MODEL_HELPER+142, "Data\\Item\\LuckyItem\\", "LuckyCardred");		
	AccessModel(MODEL_HELPER+143, "Data\\Item\\LuckyItem\\", "LuckyCardred");		
	AccessModel(MODEL_HELPER+144, "Data\\Item\\LuckyItem\\", "LuckyCardred");
	
	AccessModel(MODEL_POTION+160, "Data\\Item\\LuckyItem\\", "lucky_items01");
	AccessModel(MODEL_POTION+161, "Data\\Item\\LuckyItem\\", "lucky_items02");

	char	szLuckySetFileName[][50] = { "new_Helm", "new_Armor", "new_Pant", "new_Glove", "new_Boot" };
	char*	szLuckySetPath			 = { "Data\\Player\\LuckyItem\\" };
	char	szLuckySetPathName[50]	 = { "" };
	int		nIndex					 = 62;

#ifdef _VS2008PORTING
	for( int i=0; i<11; i++ )
#else // _VS2008PORTING
	for( i=0; i<11; i++ )
#endif // _VS2008PORTING
	{
		sprintf( szLuckySetPathName, "%s%d\\", szLuckySetPath, nIndex );
		if( nIndex != 71 )	AccessModel(MODEL_HELM+nIndex,	szLuckySetPathName, szLuckySetFileName[0], i+1);
							AccessModel(MODEL_ARMOR+nIndex,	szLuckySetPathName, szLuckySetFileName[1], i+1);
							AccessModel(MODEL_PANTS+nIndex,	szLuckySetPathName, szLuckySetFileName[2], i+1);
		if( nIndex != 72 )	AccessModel(MODEL_GLOVES+nIndex,szLuckySetPathName, szLuckySetFileName[3], i+1);
							AccessModel(MODEL_BOOTS+nIndex,	szLuckySetPathName, szLuckySetFileName[4], i+1);
		nIndex++;
	}
#endif // LEM_ADD_LUCKYITEM

    //  Chromeȿ���� ���� �ʴ� ���� �޽�.
    //  ������.
    Models[MODEL_SPEAR].Meshs[1].NoneBlendMesh = true;
    //  ���ǰ�.
    Models[MODEL_SWORD+10].Meshs[1].NoneBlendMesh = true;
    //  ��Ȱ�� ������.
    Models[MODEL_STAFF+6].Meshs[2].NoneBlendMesh = true;
    //  ��������.
//    Models[MODEL_AXE+4].Meshs[1].NoneBlendMesh = true;
    //  ī���� ����.
    Models[MODEL_MACE+6].Meshs[1].NoneBlendMesh = true;
	Models[MODEL_EVENT+9].Meshs[1].NoneBlendMesh = true;	// �� ����

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENITEMS );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// ������ �ؽ��� ����Ÿ ��ü�� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenItemTextures()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENITEMTEXTURES, PROFILING_LOADING_OPENITEMTEXTURES );
#endif // DO_PROFILING_FOR_LOADING
	
#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    int i;

    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        if ( i<3 )
        {
            OpenTexture( MODEL_HELPER+16+i, "Item\\" );     //  ��õ���� ��, ���� ��. �������.
        }
        else
        {
            OpenTexture( MODEL_EVENT+11+(i-3), "Item\\" );  //  ����
        }
    }
	OpenTexture( MODEL_EVENT+12, "Item\\" );				//. ������ ����
	OpenTexture( MODEL_EVENT+13, "Item\\" );				//. ��ũ����
	OpenTexture( MODEL_EVENT+14, "Item\\" );
	OpenTexture( MODEL_EVENT+15, "Item\\" );	// �������� ����

#ifdef _VS2008PORTING
    for( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        OpenTexture( MODEL_WING+3+i, "Item\\" );    //  ����. ( ������ ���� ~ ����� ���� ).
    }

#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
        OpenTexture( MODEL_WING+36+i, "Item\\" );	// 3�� ����
    }
	OpenTexture ( MODEL_WING+40, "Item\\" );		//  ������ ����

	LoadBitmap("Item\\msword01_r.jpg"     ,BITMAP_3RDWING_LAYER    ,GL_LINEAR,GL_REPEAT);	// ���� 3������ �߰��ؽ���

#ifdef ADD_ALICE_WINGS_1
#ifdef ADD_ALICE_WINGS_2
#ifdef _VS2008PORTING
	for (int i = 41; i <= 43; ++i)
#else // _VS2008PORTING
	for (i = 41; i <= 43; ++i)
#endif // _VS2008PORTING
#else	// ADD_ALICE_WINGS_2
	for (i = 41; i < 43; ++i)
#endif	// ADD_ALICE_WINGS_2
        ::OpenTexture(MODEL_WING+i, "Item\\");    // ��ȯ���� ����.
#endif	// ADD_ALICE_WINGS_1

#ifdef ASG_ADD_SUMMON_RARGLE
#ifdef _VS2008PORTING
	for (int i = 21; i <= 23; ++i)
#else // _VS2008PORTING
	for (i = 21; i <= 23; ++i)
#endif // _VS2008PORTING
		::OpenTexture(MODEL_STAFF+i, "Item\\");    // ��ȯ���� å.
#else	// ASG_ADD_SUMMON_RARGLE
	OpenTexture ( MODEL_STAFF+21, "Item\\" );		// ���Ϲ�Ʈ�� å
	OpenTexture ( MODEL_STAFF+22, "Item\\" );		// ���� å
#endif	// ASG_ADD_SUMMON_RARGLE

	// ������ �����۵� �ؽ���
#ifdef _VS2008PORTING
	for(int i=0; i<9; ++i)
#else // _VS2008PORTING
	for(i=0; i<9; ++i)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_ETC+19+i, "Item\\");
	}
	// ������ �����ۿ� ����Ʈ ȿ�� ���� ����
	LoadBitmap("Item\\rollofpaper_R.jpg", BITMAP_ROOLOFPAPER_EFFECT_R, GL_LINEAR);

    OpenTexture( MODEL_HELPER+4, "Skill\\" );       //  ��ũȣ���� ��
	OpenTexture( MODEL_HELPER+4, "Item\\" );       //  ��ũȣ���� ��
    OpenTexture( MODEL_HELPER+31, "Item\\" );       //  ��ũȣ���� ��ȥ.
#ifdef PET_SYSTEM
    OpenTexture( MODEL_HELPER+5, "Skill\\" );       //  ��ũ���Ǹ�.
	OpenTexture( MODEL_HELPER+5, "Item\\" );       //  ��ũ���Ǹ�.
#endif// PET_SYSTEM

#ifdef DARK_WOLF
    OpenTexture ( MODEL_HELPER+6, "Skill\\" );      //  ��ũ������ �̻�.
#endif// DARK_WOLF

    OpenTexture(MODEL_POTION+22, "Item\\");         //  â���� ����.

    OpenTexture(MODEL_POTION+31, "Item\\");         //  ��ȣ�� ����

	OpenTexture( MODEL_POTION+7,  "Item\\" );         //  �ູ�� ����, ��ȥ�� ����.//���ƹ���
	OpenTexture( MODEL_HELPER+7,  "Item\\" );         //  �뺴 ��� ����.
	OpenTexture( MODEL_HELPER+11, "Item\\" );         //  ��ȯ �ֹ���.
    OpenTexture( MODEL_EVENT+18,  "Monster\\" );      //  ������ ����.

#ifdef _VS2008PORTING
    for(int i=0;i<2;i++)
#else // _VS2008PORTING
    for(i=0;i<2;i++)
#endif // _VS2008PORTING
        OpenTexture(MODEL_HELPER+14+i, "Item\\");   //  ��ũ�� ���� ~ ��Ŭ.

    OpenTexture( MODEL_SWORD+17, "Item\\" );    //  ��ũ �극��Ŀ.
    OpenTexture( MODEL_SWORD+18, "Item\\" );    //  ���� ���̵�.

    OpenTexture( MODEL_STAFF+9, "Item\\" );     //  ������ ������.
    OpenTexture( MODEL_BOW+17,  "Item\\" );     //  ���� ����.

    OpenTexture( MODEL_HELPER+3, "Skill\\" );   //  �䰡�þ��� ��.

#ifdef _VS2008PORTING
    for(int i=0;i<4;i++)
#else // _VS2008PORTING
    for(i=0;i<4;i++)
#endif // _VS2008PORTING
        OpenTexture(MODEL_POTION+23+i, "Item\\");//  ������ �� ~ �������� ȥ.

    OpenTexture(MODEL_POTION+27, "Item\\");     //  ����� �ݼ�.
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
		OpenTexture(MODEL_POTION+28+i, "Item\\");     // �Ҿ���� ����, ����� ǥ��
    OpenTexture(MODEL_HELPER+29, "Npc\\");      //  �������� ���ʼ�Ʈ.
    OpenTexture( MODEL_SWORD+19, "Item\\" );    //  ��õ���� �����.
    OpenTexture( MODEL_STAFF+10, "Item\\" );    //  ��õ���� ����������.
    OpenTexture( MODEL_BOW+18,   "Item\\" );    //  ��õ���� ���뼮��.
    OpenTexture( MODEL_BOW+19,   "Item\\" );    //  �����뼮��.

    OpenTexture( MODEL_SWORD+31,  "Item\\" );	//	���˻� ������.
	OpenTexture( MODEL_SHIELD+15, "Item\\" );	//	�������.
	OpenTexture( MODEL_SHIELD+16, "Item\\" );	//	��������.
	OpenTexture( MODEL_SPEAR+10,  "Item\\" );	//	���â.
	OpenTexture( MODEL_MACE+7,	  "Item\\" );	//	���� �б�.
#ifdef _VS2008PORTING
	for(int i=0;i<17;i++)
#else // _VS2008PORTING
	for( i=0;i<17;i++)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_SWORD+i ,"Item\\");
		OpenTexture(MODEL_AXE+i   ,"Item\\");
		OpenTexture(MODEL_MACE+i  ,"Item\\");
		OpenTexture(MODEL_SPEAR+i ,"Item\\");
		OpenTexture(MODEL_STAFF+i ,"Item\\");
		OpenTexture(MODEL_SHIELD+i,"Item\\");
		OpenTexture(MODEL_BOW+i   ,"Item\\");
		OpenTexture(MODEL_HELPER+i,"Item\\");
		OpenTexture(MODEL_WING+i  ,"Item\\");
		OpenTexture(MODEL_POTION+i,"Item\\");
		OpenTexture(MODEL_ETC+i   ,"Item\\");
	}
#ifdef _VS2008PORTING
	for (int i = 14; i <= 20; ++i)
#else // _VS2008PORTING
	for (i = 14; i <= 20; ++i)
#endif // _VS2008PORTING
		::OpenTexture(MODEL_STAFF+i, "Item\\");		// ��ȯ���� ��ƽ.
#ifdef _VS2008PORTING
    for ( int i=21; i<=28; ++i )
#else // _VS2008PORTING
    for ( i=21; i<=28; ++i )
#endif // _VS2008PORTING
        OpenTexture(MODEL_HELPER+i, "Item\\");     //  �����, ������.
	//. MODEL_MACE+8,9,10,11
#ifdef _VS2008PORTING
	for(int i=0; i<5; i++)
#else // _VS2008PORTING
	for( i=0; i<5; i++)
#endif // _VS2008PORTING
		OpenTexture(MODEL_MACE+8+i, "Item\\" );		// ��ũ�ε� �߰� ����

#ifdef _VS2008PORTING
	for(int i=0; i<2; i++)
#else // _VS2008PORTING
	for(i=0; i<2; i++)
#endif // _VS2008PORTING
		OpenTexture(MODEL_SWORD+20+i, "Item\\");	//. ���˻�, ���� �߰���.
	OpenTexture(MODEL_BOW+20, "Item\\");			//. ���� �߰�Ȱ

#ifdef _VS2008PORTING
	for(int i=17;i<21;i++)
#else // _VS2008PORTING
	for( i=17;i<21;i++)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_WING+i  ,"Item\\");
	}
#ifdef _VS2008PORTING
    for ( int i=0; i<4; i++ )
#else // _VS2008PORTING
    for ( i=0; i<4; i++ )
#endif // _VS2008PORTING
    {
		OpenTexture ( MODEL_WING+21+i, "Item\\" );
    }
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	OpenTexture ( MODEL_WING+48, "Item\\" );
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	OpenTexture ( MODEL_WING+35, "Item\\" );
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	OpenTexture(MODEL_WING+44, "Item\\" );
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	OpenTexture(MODEL_WING+45, "Item\\");
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	OpenTexture(MODEL_WING+46, "Item\\" );
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	OpenTexture(MODEL_WING+47, "Item\\" );
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM
	OpenTexture(MODEL_ETC+29, "Item\\" );
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	OpenTexture( MODEL_ETC+28, "Item\\" );
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER

#ifdef _VS2008PORTING
	for( int i=17; i<19; ++i )
#else // _VS2008PORTING
	for( i=17; i<19; ++i )
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_ETC+i, "Item\\" );
	}

    OpenTexture(MODEL_ARROW      ,"Item\\Bow\\");

    OpenTexture(MODEL_EVENT+4	 ,"Item\\");	// ��ź�Ǻ�
    OpenTexture(MODEL_EVENT+5	 ,"Item\\");	// ����
	OpenTexture(MODEL_EVENT+6	 ,"Item\\");	// ����� ��Ʈ
    OpenTexture(MODEL_EVENT+7	 ,"Item\\");	// ����� �ø���
	OpenTexture(MODEL_EVENT+8	 ,"Item\\");	// �� ����
	OpenTexture(MODEL_EVENT+9	 ,"Item\\");	// �� ����
#ifdef USE_EVENT_ELDORADO
	OpenTexture(MODEL_EVENT+10	 ,"Item\\");	// ������
#endif
	OpenTexture ( MODEL_EVENT+16,  "Item\\" );  //  ������ �Ҹ�.
	OpenTexture ( MODEL_HELPER+30, "Item\\" );  //  ������ ����.

#ifdef CHINA_MOON_CAKE
	OpenTexture ( MODEL_EVENT+17,  "Item\\" );  //  �߱� �̺�Ʈ ����.
#endif// CHINA_MOON_CAKE



#ifdef _VS2008PORTING
    for(int i=0;i<3;i++)
#else // _VS2008PORTING
    for(i=0;i<3;i++)
#endif // _VS2008PORTING
		OpenTexture(MODEL_POTION+17+i	,"Item\\");	// �Ǹ��� ����

#ifdef _VS2008PORTING
    for(int i=0;i<2;i++)
#else // _VS2008PORTING
    for(i=0;i<2;i++)
#endif // _VS2008PORTING
        OpenTexture(MODEL_POTION+20+i, "Item\\"); //  �̺�ƮĨ(����).

#ifdef _PVP_MURDERER_HERO_ITEM
	OpenTexture(MODEL_POTION+30, "Item\\");		//  �Ӹ�ī��
#endif	// _PVP_MURDERER_HERO_ITEM
	
#ifdef _VS2008PORTING
	for(int i=0;i<6;++i)
#else // _VS2008PORTING
	for(i=0;i<6;++i)
#endif // _VS2008PORTING
		OpenTexture(MODEL_POTION+35+i, "Item\\");
	
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
        OpenTexture(MODEL_EVENT+i ,"Item\\");

    //OpenTexture(MODEL_GOLD01  ,"Data\\Item\\Etc\\");
    //OpenTexture(MODEL_APPLE01 ,"Data\\Item\\Etc\\");
    //OpenTexture(MODEL_BOTTLE01,"Data\\Item\\Etc\\");
	OpenTexture(MODEL_COMPILED_CELE, "Item\\");
	OpenTexture(MODEL_COMPILED_SOUL, "Item\\");

#ifdef LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX
	OpenTexture(MODEL_WING+136, "Item\\" );	// ������ ���� ����
	OpenTexture(MODEL_WING+137, "Item\\" );	// â���� ���� ����
	OpenTexture(MODEL_WING+138, "Item\\" );	// ��ȣ�� ���� ����
	OpenTexture(MODEL_WING+139, "Item\\" );	// ��ȭ�� ����(����) : ���� ����
	OpenTexture(MODEL_WING+140, "Item\\" );	// ��ȭ�� ����(����) : ��ȭ�� ����
	OpenTexture(MODEL_WING+141, "Item\\" );	// ȥ���� ����
	OpenTexture(MODEL_WING+142, "Item\\" );	// �ϱ� ���ü�
	OpenTexture(MODEL_WING+143, "Item\\" );	// ��� ���ü�
#endif // LEM_ADD_SEASON5_PART5_MINIUPDATE_JEWELMIX

	//���� Į���� �߰�����
	OpenTexture(MODEL_SWORD+22, "Item\\");
	OpenTexture(MODEL_SWORD+23, "Item\\");
	OpenTexture(MODEL_MACE+14, "Item\\");
	OpenTexture(MODEL_BOW+21, "Item\\");
	OpenTexture(MODEL_STAFF+12, "Item\\");

#ifdef HELLOWIN_EVENT
	OpenTexture(MODEL_POTION+45, "Item\\");
	OpenTexture(MODEL_POTION+46, "Item\\");
	OpenTexture(MODEL_POTION+47, "Item\\");
	OpenTexture(MODEL_POTION+48, "Item\\");
	OpenTexture(MODEL_POTION+49, "Item\\");
	OpenTexture(MODEL_POTION+50, "Item\\");
#endif //HELLOWIN_EVENT
#ifdef GIFT_BOX_EVENT
	OpenTexture(MODEL_POTION+32, "Item\\");
	OpenTexture(MODEL_POTION+33, "Item\\");
	OpenTexture(MODEL_POTION+34, "Item\\");

	OpenTexture(MODEL_EVENT+21, "Item\\");
	OpenTexture(MODEL_EVENT+22, "Item\\");
	OpenTexture(MODEL_EVENT+23, "Item\\");
#endif
	OpenTexture(MODEL_HELPER+38,"Item\\");        //  ������ ���Ʈ
	OpenTexture(MODEL_POTION+41,"Item\\");        //  ��ȭ�� ����(����)
	OpenTexture(MODEL_POTION+42,"Item\\");        //  ��ȭ�� ����(����)
	OpenTexture(MODEL_POTION+43,"Item\\");        //  �ϱ� ���ü�
	OpenTexture(MODEL_POTION+44,"Item\\");        //  ��� ���ü�
	OpenTexture(MODEL_WING+32, "Item\\");
	OpenTexture(MODEL_WING+33, "Item\\");
	OpenTexture(MODEL_WING+34, "Item\\");

#ifdef MYSTERY_BEAD
	OpenTexture(MODEL_EVENT+19, "Item\\");
	OpenTexture(MODEL_EVENT+20, "Item\\");
#endif // MYSTERY_BEAD

	OpenTexture(MODEL_SWORD+24, "Item\\");	//$ ũ���� ���� �����
	OpenTexture(MODEL_SWORD+25, "Item\\");	// ���˻��
	OpenTexture(MODEL_MACE+15, "Item\\");	// ��ũ�ε����
	OpenTexture(MODEL_BOW+22, "Item\\");	// ����Ȱ
	OpenTexture(MODEL_STAFF+13, "Item\\");	// �渶����������

	//^ �渱 ������ �ؽ��� �ҷ����̴� ��
	OpenTexture(MODEL_HELPER+32, "Item\\");	// ���� ����
	OpenTexture(MODEL_HELPER+33, "Item\\"); // ������ ��ȣ
	OpenTexture(MODEL_HELPER+34, "Item\\"); // �ͼ��� ����
	OpenTexture(MODEL_HELPER+35, "Item\\"); // ���Ǹ� ����
	OpenTexture(MODEL_HELPER+36, "Item\\"); // �η��� ���Ǹ�
	OpenTexture(MODEL_HELPER+37, "Item\\"); // �渱�� ���Ǹ�

#ifdef CSK_FREE_TICKET
	// ������ �� �ؽ��� �ε�
	OpenTexture(MODEL_HELPER+46, "Item\\partCharge1\\"); // ���������� ���������
	OpenTexture(MODEL_HELPER+47, "Item\\partCharge1\\"); // ����ĳ�� ���������
	OpenTexture(MODEL_HELPER+48, "Item\\partCharge1\\"); // Į���� ���������
#endif // CSK_FREE_TICKET
	
#ifdef CSK_CHAOS_CARD
	// ī����ī�� �� �ؽ��� �ε�
	OpenTexture(MODEL_POTION+54, "Item\\partCharge1\\");	// ī����ī��
#endif // CSK_CHAOS_CARD

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	OpenTexture(MODEL_HELPER+43, "Item\\");	// �ؿ��� ���� (����� ����)
	OpenTexture(MODEL_HELPER+44, "Item\\");	// �ؿ��� ���� (ǳ���� ����)
	OpenTexture(MODEL_HELPER+45, "Item\\");	// �ؿ��� ���� (������ ����)
#endif //CSK_LUCKY_SEAL
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	OpenTexture(MODEL_HELPER+43, "Item\\partCharge1\\");	// �ؿ��� ���� (����� ����)
	OpenTexture(MODEL_HELPER+44, "Item\\partCharge1\\");	// �ؿ��� ���� (ǳ���� ����)
	OpenTexture(MODEL_HELPER+45, "Item\\partCharge1\\");	// �ؿ��� ���� (������ ����)
#endif //CSK_LUCKY_SEAL
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN

#ifdef CSK_LUCKY_CHARM
	OpenTexture(MODEL_POTION+53, "Item\\partCharge1\\");	// ����� ����
#endif //CSK_LUCKY_CHARM
	
#ifdef CSK_RARE_ITEM
	// ��;����� �� �ؽ��� �ε�
#ifdef _VS2008PORTING
	for(int i=0; i<5; ++i)
#else // _VS2008PORTING
	for(i=0; i<5; ++i)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_POTION+58+i, "Item\\partCharge1\\");
	}
#endif // CSK_RARE_ITEM
	
#ifdef PSW_ELITE_ITEM              // ����Ʈ ����
	OpenTexture(MODEL_POTION+70, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+71, "Item\\partCharge2\\");
#endif //PSW_ELITE_ITEM
	
#ifdef PSW_SCROLL_ITEM             // ����Ʈ ��ũ��
	OpenTexture(MODEL_POTION+72, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+73, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+74, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+75, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+76, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+77, "Item\\partCharge2\\");
#endif //PSW_SCROLL_ITEM

#ifdef LDS_ADD_CS6_CHARM_MIX_ITEM_WING // ���� ���� 100% ���� 
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_KNIGHT_1_CHARM, "Item\\partCharge6\\");	// ��ź ��������/���� 1�� ����        
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_MAGICIAN_1_CHARM, "Item\\partCharge6\\");	// õ�� ��������/����� 1�� ����        
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_ELF_1_CHARM, "Item\\partCharge6\\");		// ���� ��������/������ 1�� ����        
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_SUMMONER_1_CHARM, "Item\\partCharge6\\");	// ��� ��������/��ȯ����� 1�� ����    
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_DARKLORD_1_CHARM, "Item\\partCharge6\\");	// ��ũ�ε� ��������/��ũ�ε�� 1�� ����
		
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_KNIGHT_2_CHARM, "Item\\partCharge6\\");	// ���� ��������/���� 2�� ����      
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_MAGICIAN_2_CHARM, "Item\\partCharge6\\");	// ��ȥ ��������/����� 2�� ����        
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_ELF_2_CHARM, "Item\\partCharge6\\");		// ���� ��������/������ 2�� ����        
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_SUMMONER_2_CHARM, "Item\\partCharge6\\");	// ���� ��������/��ȯ����� 2�� ����    
	OpenTexture(MODEL_TYPE_CHARM_MIXWING+EWS_DARKKNIGHT_2_CHARM, "Item\\partCharge6\\");// ���� ��������/���˻�� 2�� ����      

#endif //LDS_ADD_CS6_CHARM_MIX_ITEM_WING
#ifdef PSW_SEAL_ITEM               // �̵� ����
	OpenTexture(MODEL_HELPER+59, "Item\\partCharge2\\");
#endif //PSW_SEAL_ITEM
	
#ifdef PSW_FRUIT_ITEM              // ���� ����
	OpenTexture(MODEL_HELPER+54, "Item\\partCharge2\\");
	OpenTexture(MODEL_HELPER+55, "Item\\partCharge2\\");
	OpenTexture(MODEL_HELPER+56, "Item\\partCharge2\\");
	OpenTexture(MODEL_HELPER+57, "Item\\partCharge2\\");
	OpenTexture(MODEL_HELPER+58, "Item\\partCharge2\\");
#endif //PSW_FRUIT_ITEM
	
#ifdef PSW_SECRET_ITEM             // ��ȭ�� ���
	OpenTexture(MODEL_POTION+78, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+79, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+80, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+81, "Item\\partCharge2\\");
	OpenTexture(MODEL_POTION+82, "Item\\partCharge2\\");
#endif //PSW_SECRET_ITEM
	
#ifdef PSW_INDULGENCE_ITEM         // ���˺�
	OpenTexture(MODEL_HELPER+60, "Item\\partCharge2\\");
#endif //PSW_INDULGENCE_ITEM
	
#ifdef PSW_CURSEDTEMPLE_FREE_TICKET         // ȯ���� ��� ���� �����
	OpenTexture(MODEL_HELPER+61, "Item\\partCharge2\\");
#endif //PSW_CURSEDTEMPLE_FREE_TICKET

#ifdef PSW_CHARACTER_CARD 
	OpenTexture(MODEL_POTION+91, "Item\\partCharge3\\");	// ĳ���� ī��
#endif // PSW_CHARACTER_CARD
	
#ifdef PSW_NEW_CHAOS_CARD
	// ī����ī�� ������ �� �ε�
	OpenTexture(MODEL_POTION+92, "Item\\partCharge3\\");	// ī����ī�� ���
	OpenTexture(MODEL_POTION+93, "Item\\partCharge3\\");	// ī����ī�� ����
	OpenTexture(MODEL_POTION+95, "Item\\partCharge3\\");	// ī����ī�� �̴�
#endif // PSW_NEW_CHAOS_CARD

#ifdef PSW_NEW_ELITE_ITEM
	OpenTexture(MODEL_POTION+94, "Item\\partCharge2\\");    // ����Ʈ �߰� ġ�� ����
#endif //PSW_NEW_ELITE_ITEM

#ifdef PSW_ADD_PC4_SEALITEM
	OpenTexture(MODEL_HELPER+62, "Item\\partCharge4\\");
	OpenTexture(MODEL_HELPER+63, "Item\\partCharge4\\");
#endif //PSW_ADD_PC4_SEALITEM

#ifdef PSW_ADD_PC4_SCROLLITEM
	OpenTexture(MODEL_POTION+97, "Item\\partCharge4\\");
	OpenTexture(MODEL_POTION+98, "Item\\partCharge4\\");
#endif //PSW_ADD_PC4_SCROLLITEM

#ifdef PSW_ADD_PC4_CHAOSCHARMITEM
	OpenTexture(MODEL_POTION+96, "Item\\partCharge4\\");
#endif //PSW_ADD_PC4_CHAOSCHARMITEM

#ifdef LDK_ADD_PC4_GUARDIAN
	OpenTexture(MODEL_HELPER+64,"Item\\partCharge4\\"); 
	OpenTexture(MODEL_HELPER+65,"Item\\partCharge4\\"); 
#endif //LDK_ADD_PC4_GUARDIAN
		
#ifdef LDK_ADD_RUDOLPH_PET
	OpenTexture( MODEL_HELPER+67, "Item\\xmas\\" );	//ũ�������� �絹�� ��
#endif //LDK_ADD_RUDOLPH_PET
#ifdef PJH_ADD_PANDA_PET
	OpenTexture( MODEL_HELPER+80, "Item\\" );	//ũ�������� �絹�� ��
#endif //PJH_ADD_PANDA_PET
#ifdef LDK_ADD_CS7_UNICORN_PET
	OpenTexture(MODEL_HELPER+106,"Item\\partcharge7\\");  //������ ��
#endif //LDK_ADD_CS7_UNICORN_PET
#ifdef YDG_ADD_SKELETON_PET
	OpenTexture(MODEL_HELPER+123,"Item\\");		// ���̷��� ��
#endif	// YDG_ADD_SKELETON_PET

#ifdef PBG_ADD_SANTAINVITATION
	OpenTexture(MODEL_HELPER+66, "Item\\xmas\\");	//��Ÿ������ �ʴ���.
#endif //PBG_ADD_SANTAINVITATION

#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	OpenTexture(MODEL_POTION+100, "Item\\");			//����� ����.
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008

#ifdef YDG_ADD_CS5_REVIVAL_CHARM
	OpenTexture(MODEL_HELPER+69, "Item\\partCharge5\\");	// ��Ȱ�� ����
#endif	// YDG_ADD_CS5_REVIVAL_CHARM
#ifdef YDG_ADD_CS5_PORTAL_CHARM
	OpenTexture(MODEL_HELPER+70, "Item\\partCharge5\\");	// �̵��� ����
#endif	// YDG_ADD_CS5_PORTAL_CHARM

#ifdef ASG_ADD_CS6_GUARD_CHARM
	OpenTexture(MODEL_HELPER+81, "Item\\partCharge6\\");	// ��ȣ�Ǻ���
#endif	// ASG_ADD_CS6_GUARD_CHARM
#ifdef ASG_ADD_CS6_ITEM_GUARD_CHARM
	OpenTexture(MODEL_HELPER+82, "Item\\partCharge6\\");	// �����ۺ�ȣ����
#endif	// ASG_ADD_CS6_ITEM_GUARD_CHARM
#ifdef ASG_ADD_CS6_ASCENSION_SEAL_MASTER
	OpenTexture(MODEL_HELPER+93, "Item\\partCharge6\\");	// ��������帶����
#endif	// ASG_ADD_CS6_ASCENSION_SEAL_MASTER
#ifdef ASG_ADD_CS6_WEALTH_SEAL_MASTER
	OpenTexture(MODEL_HELPER+94, "Item\\partCharge6\\");	// ǳ�������帶����
#endif	// ASG_ADD_CS6_WEALTH_SEAL_MASTER

#ifdef YDG_ADD_HEALING_SCROLL
	OpenTexture(MODEL_POTION+140, "Item\\");	// ġ���� ��ũ��
#endif	// YDG_ADD_HEALING_SCROLL

#ifdef CSK_EVENT_CHERRYBLOSSOM
	OpenTexture(MODEL_POTION+84, "Item\\cherryblossom\\");		// ���ɻ���
	OpenTexture(MODEL_POTION+85, "Item\\cherryblossom\\");		// ���ɼ�
	OpenTexture(MODEL_POTION+86, "Item\\cherryblossom\\");		// ���ɰ��
	OpenTexture(MODEL_POTION+87, "Item\\cherryblossom\\");		// ������
	OpenTexture(MODEL_POTION+88, "Item\\cherryblossom\\");		// ��� ����
	OpenTexture(MODEL_POTION+89, "Item\\cherryblossom\\");		// ������ ����
	OpenTexture(MODEL_POTION+90, "Item\\cherryblossom\\");		// ����� ����
#endif //CSK_EVENT_CHERRYBLOSSOM

	OpenTexture(MODEL_HELPER+49, "Item\\");		// ���� �η縶��
	OpenTexture(MODEL_HELPER+50, "Item\\");		// ȯ�������� ����
	OpenTexture(MODEL_HELPER+51, "Item\\");		// ���� �η縶��

	OpenTexture(MODEL_HELPER+52, "Item\\");	// �ܵ����� �Ҳ�
	OpenTexture(MODEL_HELPER+53, "Item\\");	// �ܵ����� ����

#ifdef CSK_PCROOM_ITEM
	OpenTexture(MODEL_POTION+55, "Item\\");	// �ʷ�ȥ���ǻ���
	OpenTexture(MODEL_POTION+56, "Item\\");	// ����
	OpenTexture(MODEL_POTION+57, "Item\\");	// ����
#endif // CSK_PCROOM_ITEM
	
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	OpenTexture(MODEL_HELPER+96, "Item\\");	// ������ ���� ((JPN)PC�� ������)
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH

	OpenTexture(MODEL_POTION+64, "Item\\");	// ���� ���� ����
	
	OpenTexture(MODEL_POTION+65, "Item\\");	// ����������Ʈ�ǺҲ�
	OpenTexture(MODEL_POTION+66, "Item\\");	// �︶�̳��ǻ�
	OpenTexture(MODEL_POTION+67, "Item\\");	// ����Ǻһ����Ǳ���
	OpenTexture(MODEL_POTION+68, "Item\\");	// �ɿ��Ǵ�����

	OpenTexture(MODEL_POTION+63, "Item\\");	// ����
	OpenTexture(MODEL_POTION+52, "Item\\");	// GM ��������
	g_ChangeRingMgr->LoadItemTexture();

#ifdef YDG_ADD_FIRECRACKER_ITEM
	OpenTexture(MODEL_POTION+99, "Item\\XMas\\");	// ũ�������� ����
#endif	// YDG_ADD_FIRECRACKER_ITEM

#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	OpenTexture(MODEL_POTION+145, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 7
	OpenTexture(MODEL_POTION+146, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 8
	OpenTexture(MODEL_POTION+147, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 9
	OpenTexture(MODEL_POTION+148, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 10
	OpenTexture(MODEL_POTION+149, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 11
	OpenTexture(MODEL_POTION+150, "Item\\partCharge8\\");	// ��� ������ Ƽ�� 12
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12

#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	int n;
	for (n = 0; n < 9; ++n)
		OpenTexture(MODEL_POTION+151 + n, "Item\\");
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM

#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ������ �� �ؽ��� �ε�
	OpenTexture(MODEL_HELPER+125, "Item\\partCharge8\\"); // ���������� ���������
	OpenTexture(MODEL_HELPER+126, "Item\\partCharge8\\"); // ����ĳ�� ���������
	OpenTexture(MODEL_HELPER+127, "Item\\partCharge8\\"); // Į���� ���������
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH

#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	OpenTexture(MODEL_HELPER+128, "Item\\");	// ��������
	OpenTexture(MODEL_HELPER+129, "Item\\");	// ��������
	OpenTexture(MODEL_HELPER+134, "Item\\");	// ����
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	OpenTexture(MODEL_HELPER+130, "Item\\");	// ��ũ��
//	OpenTexture(MODEL_HELPER+131, "Item\\");	// ��������
	OpenTexture(MODEL_HELPER+132, "Item\\");	// ����ũ��
//	OpenTexture(MODEL_HELPER+133, "Item\\");	// ����������
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
//---------------------------------------------------------------------------------
// ���Ͼ����� �߰�
#ifdef ADD_SOCKET_ITEM
	// ��
	OpenTexture(MODEL_SWORD+26, "Item\\");		// �ö�������
	OpenTexture(MODEL_SWORD+27, "Item\\");		// �ҵ�극��Ŀ
	OpenTexture(MODEL_SWORD+28, "Item\\");		// ��ٽ�Ÿ��
	// �б�
	OpenTexture(MODEL_MACE+16, "Item\\");		// ���ν�Ʈ���̽�
	OpenTexture(MODEL_MACE+17, "Item\\");		// �ۼַ�Ʈ����
	// Ȱ/����
	OpenTexture(MODEL_BOW+23, "Item\\");		// ��ũ���ð�
	// ������
	OpenTexture(MODEL_STAFF+30, "Item\\");		// ���鸮������
	OpenTexture(MODEL_STAFF+31, "Item\\");		// �κ����˽�����
	OpenTexture(MODEL_STAFF+32, "Item\\");		// �ҿ�긵��
	// ����
	OpenTexture(MODEL_SHIELD+17, "Item\\");		// ũ�����۷θ�
	OpenTexture(MODEL_SHIELD+18, "Item\\");		// �����Ǵ��ǵ�
	OpenTexture(MODEL_SHIELD+19, "Item\\");		// ���ν�Ʈ�踮��
	OpenTexture(MODEL_SHIELD+20, "Item\\");		// ��������
#endif // ADD_SOCKET_ITEM

#ifdef ADD_SEED_SPHERE_ITEM
	// ���� ������ ��� (�õ�, ���Ǿ�, �õ彺�Ǿ�)
#ifdef _VS2008PORTING
	for (int i = 0; i < 6; ++i)
#else // _VS2008PORTING
	for (i = 0; i < 6; ++i)
#endif // _VS2008PORTING
		OpenTexture(MODEL_WING+60+i, "Effect\\");	// �õ� 6��
#ifdef _VS2008PORTING
	for (int i = 0; i < 5; ++i)
#else // _VS2008PORTING
	for (i = 0; i < 5; ++i)
#endif // _VS2008PORTING
		OpenTexture(MODEL_WING+70+i, "Item\\");		// ���Ǿ� 5��
#ifdef _VS2008PORTING
	for (int i = 0; i < 30; ++i)
#else // _VS2008PORTING
	for (i = 0; i < 30; ++i)
#endif // _VS2008PORTING
	{
		OpenTexture(MODEL_WING+100+i, "Effect\\");	// �õ彺�Ǿ� 30��
		OpenTexture(MODEL_WING+100+i, "Item\\");	// �õ彺�Ǿ� 30��
	}
#endif	// ADD_SEED_SPHERE_ITEM
	
#ifdef CSK_ADD_ITEM_CROSSSHIELD
	OpenTexture(MODEL_SHIELD+21, "Item\\");		// ũ�ν��ǵ�
#endif // CSK_ADD_ITEM_CROSSSHIELD

#ifdef LDK_ADD_GAMBLERS_WEAPONS
	OpenTexture(MODEL_BOW+24,   "Item\\");		// �׺� ���� Ȱ
	OpenTexture(MODEL_STAFF+33, "Item\\");		// �׺� ���� ������
	OpenTexture(MODEL_STAFF+34, "Item\\");		// �׺� ���� ������(��ȯ�����)
	OpenTexture(MODEL_SWORD+29, "Item\\");		// �׺� ���� ��
	OpenTexture(MODEL_MACE+18,  "Item\\");		// �׺� ���� ����
#endif //LDK_ADD_GAMBLERS_WEAPONS

#ifdef LDK_ADD_GAMBLE_RANDOM_ICON		// �׺� �Ǹſ� ������
	OpenTexture(MODEL_HELPER+71, "Item\\");
	OpenTexture(MODEL_HELPER+72, "Item\\");
	OpenTexture(MODEL_HELPER+73, "Item\\");
	OpenTexture(MODEL_HELPER+74, "Item\\");
	OpenTexture(MODEL_HELPER+75, "Item\\");
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
#ifdef PBG_ADD_CHARACTERCARD
	OpenTexture(MODEL_HELPER+97, "Item\\Ingameshop\\");		// ���˻� ĳ���� ī��
	OpenTexture(MODEL_HELPER+98, "Item\\Ingameshop\\");		// ��ũ�ε� ĳ���� ī��
	OpenTexture(MODEL_POTION+91, "Item\\partCharge3\\");	// ��ȯ���� ĳ���� ī��
#endif //PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERSLOT
	OpenTexture(MODEL_HELPER+99, "Item\\Ingameshop\\");		// ĳ���� ���� ����
	OpenTexture(MODEL_SLOT_LOCK, "Item\\Ingameshop\\");		// ĳ���� ���� �ڹ���
#endif //PBG_ADD_CHARACTERSLOT
#ifdef PBG_ADD_SECRETITEM
	OpenTexture(MODEL_HELPER+117, "Item\\Ingameshop\\");	//�ϱ�Ȱ���Ǻ��
	OpenTexture(MODEL_HELPER+118, "Item\\Ingameshop\\");	//�ϱ�Ȱ���Ǻ��
	OpenTexture(MODEL_HELPER+119, "Item\\Ingameshop\\");	//�߱�Ȱ���Ǻ��
	OpenTexture(MODEL_HELPER+120, "Item\\Ingameshop\\");	//���Ȱ���Ǻ��
#endif //PBG_ADD_SECRETITEM
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	OpenTexture(MODEL_POTION+110, "Item\\");
	OpenTexture(MODEL_POTION+111, "Item\\");
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	OpenTexture(MODEL_POTION+101, "Item\\");	// �ǹ�������
	OpenTexture(MODEL_POTION+102, "Item\\");	// ���̿��� ��ɼ�
	OpenTexture(MODEL_POTION+109, "Item\\");	// ��ũ�ι���
	for(int c=0; c<6; c++)
	{
		OpenTexture(MODEL_POTION+103+c, "Item\\");	// ��ũ�ι��� ����
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM

#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	OpenTexture(MODEL_HELPER+107,"Item\\partcharge7\\");  // ġ��������
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
#ifdef YDG_ADD_CS7_MAX_AG_AURA
	OpenTexture(MODEL_HELPER+104,"Item\\partcharge7\\");  // AG���� ����
#endif	// YDG_ADD_CS7_MAX_AG_AURA
#ifdef YDG_ADD_CS7_MAX_SD_AURA
	OpenTexture(MODEL_HELPER+105,"Item\\partcharge7\\");  // SD���� ����
#endif	// YDG_ADD_CS7_MAX_SD_AURA
#ifdef YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
	OpenTexture(MODEL_HELPER+103,"Item\\partcharge7\\");  // ��Ƽ ����ġ ���� ������
#endif	// YDG_ADD_CS7_PARTY_EXP_BONUS_ITEM
#ifdef YDG_ADD_CS7_ELITE_SD_POTION
	OpenTexture(MODEL_POTION+133,"Item\\partcharge7\\");  // ����Ʈ SDȸ�� ����
#endif	// YDG_ADD_CS7_ELITE_SD_POTION


#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
	OpenTexture(MODEL_HELPER+109,"Item\\InGameShop\\");  // InGameShop Item : ����(�����̾�/BLUE)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
	OpenTexture(MODEL_HELPER+110,"Item\\InGameShop\\");  // InGameShop Item : ����(���/RED)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
	OpenTexture(MODEL_HELPER+111,"Item\\InGameShop\\");  // InGameShop Item : ����(������/yellow)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
	OpenTexture(MODEL_HELPER+112,"Item\\InGameShop\\");  // InGameShop Item : ����(�ڼ���/violet)
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
	OpenTexture(MODEL_HELPER+113,"Item\\InGameShop\\");  // InGameShop Item : �����(���/red)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
	OpenTexture(MODEL_HELPER+114,"Item\\InGameShop\\");  // InGameShop Item : �����(���޶���/Blue)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
	OpenTexture(MODEL_HELPER+115,"Item\\InGameShop\\");  // InGameShop Item : �����(�����̾�/Green)
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE

#ifdef LDK_ADD_INGAMESHOP_GOBLIN_GOLD
	// �����ȭ
	OpenTexture(MODEL_POTION+120,"Item\\InGameShop\\");
#endif //LDK_ADD_INGAMESHOP_GOBLIN_GOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	OpenTexture(MODEL_POTION+121,"Item\\InGameShop\\");
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST		// ���ε� ��������
	OpenTexture(MODEL_POTION+122,"Item\\InGameShop\\");
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST				// �ݻ�����
	OpenTexture(MODEL_POTION+123,"Item\\InGameShop\\");
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST				// ��������
	OpenTexture(MODEL_POTION+124,"Item\\InGameShop\\");
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_PACKAGE_BOX				// ��Ű�� ����A-F
	for(int k=0; k<6; k++)
	{
		OpenTexture(MODEL_POTION+134+k,"Item\\InGameShop\\");
	}
	LoadBitmap("Item\\InGameShop\\membership_item_blue.jpg"		,BITMAP_PACKAGEBOX_BLUE	,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\InGameShop\\membership_item_gold.jpg"		,BITMAP_PACKAGEBOX_GOLD	,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\InGameShop\\membership_item_green.jpg"	,BITMAP_PACKAGEBOX_GREEN,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\InGameShop\\membership_item_pouple.jpg"	,BITMAP_PACKAGEBOX_PUPLE,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\InGameShop\\membership_item_red.jpg"		,BITMAP_PACKAGEBOX_RED	,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\InGameShop\\membership_item_sky.jpg"		,BITMAP_PACKAGEBOX_SKY	,GL_LINEAR,GL_REPEAT);
#endif //LDK_ADD_INGAMESHOP_PACKAGE_BOX
#ifdef LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	OpenTexture(MODEL_HELPER+116, "Item\\");	// �ű� ǳ���� ����
#endif //LDK_ADD_INGAMESHOP_NEW_WEALTH_SEAL
	
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	OpenTexture(MODEL_WING+130, "Item\\");
	for(int j=0; j<4; j++)
	{
		OpenTexture(MODEL_WING+131+j, "Item\\Ingameshop\\");
	}
#endif //LDK_ADD_INGAMESHOP_SMALL_WING

#ifdef ASG_ADD_CHARGED_CHANNEL_TICKET
	OpenTexture(MODEL_HELPER+124, "Item\\partCharge6\\");
#endif	// ASG_ADD_CHARGED_CHANNEL_TICKET

#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
	OpenTexture(MODEL_POTION+112, "Item\\Ingameshop\\");
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
	OpenTexture(MODEL_POTION+113, "Item\\Ingameshop\\");
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113

#ifdef LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
	{
		for(int k=0; k<6; k++)
		{
			OpenTexture(MODEL_POTION+114+k,"Item\\InGameShop\\");
		}

		LoadBitmap("Item\\InGameShop\\mebership_3items_green.jpg"	,BITMAP_INGAMESHOP_PRIMIUM6	,GL_LINEAR, GL_REPEAT);
	}
#endif //LDS_ADD_INGAMESHOP_ITEM_PRIMIUMSERVICE6		// �ΰ��Ә� ������ // �����̾�����6��			// MODEL_POTION+114~119
#ifdef LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
	{
		for(int k=0; k<4; k++)
		{
			OpenTexture(MODEL_POTION+126+k,"Item\\InGameShop\\");
		}

		LoadBitmap("Item\\InGameShop\\mebership_3items_red.jpg"	,BITMAP_INGAMESHOP_COMMUTERTICKET4	,GL_LINEAR, GL_REPEAT);
	}
#endif //LDS_ADD_INGAMESHOP_ITEM_COMMUTERTICKET4		// �ΰ��Ә� ������ // ���ױ�4��					// MODEL_POTION+126~129
#ifdef LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
	{
		for(int k=0; k<3; k++)
		{
			OpenTexture(MODEL_POTION+130+k,"Item\\InGameShop\\");
		}

		LoadBitmap("Item\\InGameShop\\mebership_3items_yellow.jpg"	,BITMAP_INGAMESHOP_SIZECOMMUTERTICKET3	,GL_LINEAR, GL_REPEAT);
	}
#endif //LDS_ADD_INGAMESHOP_ITEM_SIZECOMMUTERTICKET3	// �ΰ��Ә� ������ // ������3��					// MODEL_POTION+130~132
#ifdef LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
	{
		OpenTexture(MODEL_HELPER+121,"Item\\InGameShop\\");
	}
#endif // LDS_ADD_INGAMESHOP_ITEM_PASSCHAOSCASTLE		// �ΰ��Ә� ������ // ī�����ɽ� ���������		// MODEL_HELPER+121
#ifdef PBG_ADD_GENSRANKING
	for(int _index=0; _index<4; ++_index)
		OpenTexture(MODEL_POTION+141+_index, "Item\\");	// ������
#endif //PBG_ADD_GENSRANKING
#ifdef LDK_ADD_14_15_GRADE_ITEM_MODEL
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_ARMLEFT,	"Item\\");	// 14, 15��� ���� �� ����
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_ARMRIGHT,	"Item\\");	// 14, 15��� ���� �� ������
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_BODYLEFT,	"Item\\");	// 14, 15��� ���� �� ���ʿ���
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_BODYRIGHT,	"Item\\");	// 14, 15��� ���� �� ���ʿ�����
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_BOOTLEFT,	"Item\\");	// 14, 15��� ���� �� �޹�
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_BOOTRIGHT,	"Item\\");	// 14, 15��� ���� �� ������
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_HEAD,		"Item\\");	// 14, 15��� ���� �� �Ӹ�
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_PANTLEFT,	"Item\\");	// 14, 15��� ���� �� ��������
	OpenTexture(MODEL_15GRADE_ARMOR_OBJ_PANTRIGHT,	"Item\\");	// 14, 15��� ���� �� ����������
	LoadBitmap("Item\\rgb_mix.jpg"	,BITMAP_RGB_MIX	,GL_LINEAR, GL_REPEAT);
#endif //LDK_ADD_14_15_GRADE_ITEM_MODEL
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	OpenTexture(MODEL_WING+49, "Item\\");		// �����Ǹ���
	OpenTexture(MODEL_WING+50, "Item\\");		// �����Ǹ���
	OpenTexture(MODEL_WING+135, "Item\\");		// ���������Ǹ���
	g_CMonkSystem.LoadModelItemTexture();
	for(int _nRollIndex=0; _nRollIndex<7; ++_nRollIndex)
		OpenTexture(MODEL_ETC+30+_nRollIndex, "Item\\");	// ��ų���þ�����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM

#ifdef LEM_ADD_LUCKYITEM
	OpenTexture(MODEL_HELPER+135, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+136, "Item\\LuckyItem\\" );	
	OpenTexture(MODEL_HELPER+137, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+138, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+139, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+140, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+141, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+142, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+143, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_HELPER+144, "Item\\LuckyItem\\" );

	char*	szLuckySetPath			 = { "Player\\LuckyItem\\" };
	char	szLuckySetPathName[50]	 = { "" };
	int		nIndex					 = 62;

#ifdef _VS2008PORTING
	for( int i=0; i<11; i++ )
#else // _VS2008PORTING
	for( i=0; i<11; i++ )
#endif // _VS2008PORTING
	{
		sprintf( szLuckySetPathName, "%s%d\\", szLuckySetPath, nIndex );
		if( nIndex != 71 )	OpenTexture(MODEL_HELM+nIndex,	szLuckySetPathName);
							OpenTexture(MODEL_ARMOR+nIndex,	szLuckySetPathName);
							OpenTexture(MODEL_PANTS+nIndex,	szLuckySetPathName);
		if( nIndex != 72 )	OpenTexture(MODEL_GLOVES+nIndex,szLuckySetPathName);
							OpenTexture(MODEL_BOOTS+nIndex,	szLuckySetPathName);
		nIndex++;
	}
	
	OpenTexture(MODEL_POTION+160, "Item\\LuckyItem\\" );
	OpenTexture(MODEL_POTION+161, "Item\\LuckyItem\\" );

	sprintf(szLuckySetPathName, "Player\\LuckyItem\\65\\InvenArmorMale40_luck.tga");
	LoadBitmap(szLuckySetPathName, BITMAP_INVEN_ARMOR+6);
	sprintf(szLuckySetPathName, "Player\\LuckyItem\\65\\InvenPantsMale40_luck.tga");
	LoadBitmap(szLuckySetPathName, BITMAP_INVEN_PANTS+6);
	sprintf(szLuckySetPathName, "Player\\LuckyItem\\70\\InvenArmorMale41_luck.tga");
	LoadBitmap(szLuckySetPathName, BITMAP_INVEN_ARMOR+7);
	sprintf(szLuckySetPathName, "Player\\LuckyItem\\70\\InvenPantsMale41_luck.tga");
	LoadBitmap(szLuckySetPathName, BITMAP_INVEN_PANTS+7);
#endif // LEM_ADD_LUCKYITEM

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENITEMTEXTURES );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// NPC ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void DeleteNpcs()
{
	for(int i=MODEL_NPC_BEGIN;i<MODEL_NPC_END;i++)
		Models[i].Release();

#ifdef _VS2008PORTING
	for(int i=SOUND_NPC;i<SOUND_NPC_END;i++)
#else // _VS2008PORTING
	for(i=SOUND_NPC;i<SOUND_NPC_END;i++)
#endif // _VS2008PORTING
		ReleaseBuffer(i);
}

///////////////////////////////////////////////////////////////////////////////
// NPC �𵨸�, �ؽ��� ����Ÿ �о���̴� �Լ�(���ӻ󿡼� ����Ʈ�� �������� �ε�)
///////////////////////////////////////////////////////////////////////////////

void OpenNpc(int Type)
{
  	BMD *b = &Models[Type];
	if(b->NumActions > 0) return;
#ifndef _VS2008PORTING			// #ifndef
	int i;
#endif // _VS2008PORTING
	switch(Type)
	{
	case MODEL_MERCHANT_FEMALE:
		AccessModel(MODEL_MERCHANT_FEMALE,"Data\\Npc\\","Female",1);
#ifdef _VS2008PORTING
		for(int i=0;i<2;i++)
#else // _VS2008PORTING
		for(i=0;i<2;i++)
#endif // _VS2008PORTING
		{
			AccessModel(MODEL_MERCHANT_FEMALE_HEAD  +i,"Data\\Npc\\","FemaleHead"  ,i+1);
			AccessModel(MODEL_MERCHANT_FEMALE_UPPER +i,"Data\\Npc\\","FemaleUpper" ,i+1);
			AccessModel(MODEL_MERCHANT_FEMALE_LOWER +i,"Data\\Npc\\","FemaleLower" ,i+1);
			AccessModel(MODEL_MERCHANT_FEMALE_BOOTS +i,"Data\\Npc\\","FemaleBoots" ,i+1);
         	OpenTexture(MODEL_MERCHANT_FEMALE_HEAD  +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_FEMALE_UPPER +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_FEMALE_LOWER +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_FEMALE_BOOTS +i,"Npc\\");
		}
		break;
	case MODEL_MERCHANT_MAN:
		AccessModel(MODEL_MERCHANT_MAN   ,"Data\\Npc\\","Man",1);
#ifdef _VS2008PORTING
		for(int i=0;i<2;i++)
#else // _VS2008PORTING
		for(i=0;i<2;i++)
#endif // _VS2008PORTING
		{
			AccessModel(MODEL_MERCHANT_MAN_HEAD  +i,"Data\\Npc\\","ManHead"  ,i+1);
			AccessModel(MODEL_MERCHANT_MAN_UPPER +i,"Data\\Npc\\","ManUpper" ,i+1);
			AccessModel(MODEL_MERCHANT_MAN_GLOVES+i,"Data\\Npc\\","ManGloves",i+1);
			AccessModel(MODEL_MERCHANT_MAN_BOOTS +i,"Data\\Npc\\","ManBoots" ,i+1);
         	OpenTexture(MODEL_MERCHANT_MAN_HEAD  +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_MAN_UPPER +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_MAN_GLOVES+i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_MAN_BOOTS +i,"Npc\\");
		}
		break;
	case MODEL_MERCHANT_GIRL:
		AccessModel(MODEL_MERCHANT_GIRL  ,"Data\\Npc\\","Girl",1);
#ifdef _VS2008PORTING
		for(int i=0;i<2;i++)
#else // _VS2008PORTING
		for(i=0;i<2;i++)
#endif // _VS2008PORTING
		{
			AccessModel(MODEL_MERCHANT_GIRL_HEAD  +i,"Data\\Npc\\","GirlHead"  ,i+1);
			AccessModel(MODEL_MERCHANT_GIRL_UPPER +i,"Data\\Npc\\","GirlUpper" ,i+1);
			AccessModel(MODEL_MERCHANT_GIRL_LOWER +i,"Data\\Npc\\","GirlLower" ,i+1);
         	OpenTexture(MODEL_MERCHANT_GIRL_HEAD  +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_GIRL_UPPER +i,"Npc\\");
         	OpenTexture(MODEL_MERCHANT_GIRL_LOWER +i,"Npc\\");
		}
		break;
	case MODEL_SMITH:
		AccessModel(MODEL_SMITH          ,"Data\\Npc\\","Smith",1);
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_NPC       	 ,"Data\\Sound\\n��������.wav",1);
#else
		LoadWaveFile(SOUND_NPC       	 ,"Data\\Sound\\nBlackSmith.wav",1);
#endif
		break;
	case MODEL_SCIENTIST:
		AccessModel(MODEL_SCIENTIST      ,"Data\\Npc\\","Wizard",1);
		break;
	case MODEL_SNOW_MERCHANT:
		AccessModel(MODEL_SNOW_MERCHANT  ,"Data\\Npc\\","SnowMerchant",1);
		break;
	case MODEL_SNOW_SMITH:
		AccessModel(MODEL_SNOW_SMITH     ,"Data\\Npc\\","SnowSmith",1);
		break;
	case MODEL_SNOW_WIZARD:
		AccessModel(MODEL_SNOW_WIZARD    ,"Data\\Npc\\","SnowWizard",1);
		break;
	case MODEL_ELF_WIZARD:
		AccessModel(MODEL_ELF_WIZARD     ,"Data\\Npc\\","ElfWizard",1);
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_NPC        	 ,"Data\\Sound\\n����.wav",1);
#else
		LoadWaveFile(SOUND_NPC        	 ,"Data\\Sound\\nHarp.wav",1);
#endif
		break;
	case MODEL_ELF_MERCHANT:
		AccessModel(MODEL_ELF_MERCHANT   ,"Data\\Npc\\","ElfMerchant",1);
		break;
	case MODEL_MASTER:
		AccessModel(MODEL_MASTER         ,"Data\\Npc\\","Master",1);
		break;
	case MODEL_STORAGE:
		AccessModel(MODEL_STORAGE        ,"Data\\Npc\\","Storage",1);
		break;
	case MODEL_TOURNAMENT:
		AccessModel(MODEL_TOURNAMENT     ,"Data\\Npc\\","Tournament",1);
		break;
	case MODEL_MIX_NPC:
		AccessModel(MODEL_MIX_NPC        ,"Data\\Npc\\","MixNpc",1);
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_NPC+1       	 ,"Data\\Sound\\n�ͽ�.wav",1);
#else
		LoadWaveFile(SOUND_NPC+1       	 ,"Data\\Sound\\nMix.wav",1);
#endif
		break;
	case MODEL_REFINERY_NPC:
		AccessModel(MODEL_REFINERY_NPC        ,"Data\\Npc\\","os");
		OpenTexture(Type,"Npc\\");
		break;
	case MODEL_RECOVERY_NPC:
		AccessModel(MODEL_RECOVERY_NPC        ,"Data\\Npc\\","je");
		OpenTexture(Type,"Npc\\");
		break;	
	case MODEL_NPC_DEVILSQUARE:
		AccessModel(MODEL_NPC_DEVILSQUARE,"Data\\Npc\\","DevilNpc",1);
		break;

    case MODEL_NPC_SEVINA:
        AccessModel( MODEL_NPC_SEVINA, "Data\\Npc\\","Sevina",1);
        OpenTexture(Type,"Npc\\");
        break;
	case MODEL_NPC_ARCHANGEL:
        AccessModel( MODEL_NPC_ARCHANGEL, "Data\\Npc\\","BloodCastle",1);
        OpenTexture(Type,"Npc\\");
		break;
	case MODEL_NPC_ARCHANGEL_MESSENGER:
        AccessModel( MODEL_NPC_ARCHANGEL_MESSENGER, "Data\\Npc\\","BloodCastle",2);
        OpenTexture(Type,"Npc\\");
		break;

    //  ����ƽ�, �η��þ� �߰� ���� NPC
	case MODEL_DEVIAS_TRADER:
		AccessModel( MODEL_DEVIAS_TRADER, "Data\\Npc\\", "DeviasTrader", 1);
		OpenTexture(Type, "Npc\\");
		break;

#ifdef _PVP_ATTACK_GUARD
	case MODEL_ANGEL:
		AccessModel ( MODEL_ANGEL, "Data\\Player\\", "Angel" );
		OpenTexture ( MODEL_ANGEL, "Npc\\" );
		break;
#endif	// _PVP_ATTACK_GUARD
    case MODEL_NPC_BREEDER:    //  ���û� NPC.
        AccessModel ( MODEL_NPC_BREEDER, "Data\\Npc\\", "Breeder" );
        OpenTexture ( MODEL_NPC_BREEDER, "Npc\\" );
        break;
#ifdef _PVP_MURDERER_HERO_ITEM
	case MODEL_HERO_SHOP:	// ���� ����
        AccessModel ( MODEL_HERO_SHOP, "Data\\Npc\\", "HeroNpc" );
        OpenTexture ( MODEL_HERO_SHOP, "Npc\\" );
		break;
#endif	// _PVP_MURDERER_HERO_ITEM

    case MODEL_NPC_CAPATULT_ATT:
        AccessModel ( MODEL_NPC_CAPATULT_ATT, "Data\\Npc\\", "Model_Npc_Catapult_Att" );
        OpenTexture ( MODEL_NPC_CAPATULT_ATT, "Npc\\" );
        break;

    case MODEL_NPC_CAPATULT_DEF:
        AccessModel ( MODEL_NPC_CAPATULT_DEF, "Data\\Npc\\", "Model_Npc_Catapult_Def" );
        OpenTexture ( MODEL_NPC_CAPATULT_DEF, "Npc\\" );
        break;

    case MODEL_NPC_SENATUS :
        AccessModel ( MODEL_NPC_SENATUS, "Data\\Npc\\", "NpcSenatus" );
        OpenTexture ( MODEL_NPC_SENATUS, "Npc\\" );
        break;

    case MODEL_NPC_GATE_SWITCH:
        AccessModel ( MODEL_NPC_GATE_SWITCH, "Data\\Npc\\", "NpcGateSwitch" );
        OpenTexture ( MODEL_NPC_GATE_SWITCH, "Npc\\" );
        break;

    case MODEL_NPC_CROWN :
        AccessModel ( MODEL_NPC_CROWN, "Data\\Npc\\", "NpcCrown" );
        OpenTexture ( MODEL_NPC_CROWN, "Npc\\" );
        break;

    case MODEL_NPC_CHECK_FLOOR :
        AccessModel ( MODEL_NPC_CHECK_FLOOR, "Data\\Npc\\", "NpcCheckFloor" );
        OpenTexture ( MODEL_NPC_CHECK_FLOOR, "Npc\\" );
        break;

    case MODEL_NPC_CLERK :
        AccessModel ( MODEL_NPC_CLERK, "Data\\Npc\\", "NpcClerk" );
        OpenTexture ( MODEL_NPC_CLERK, "Npc\\" );
        break;

    case MODEL_NPC_BARRIER:
        AccessModel ( MODEL_NPC_BARRIER, "Data\\Npc\\", "NpcBarrier" );
        OpenTexture ( MODEL_NPC_BARRIER, "Npc\\" );
        break;
	case MODEL_NPC_SERBIS:
		AccessModel ( MODEL_NPC_SERBIS, "Data\\Npc\\", "npc_mulyak" );
		OpenTexture ( MODEL_NPC_SERBIS, "Npc\\" );
		break;
	case MODEL_KALIMA_SHOP:
		AccessModel ( MODEL_KALIMA_SHOP, "Data\\Npc\\", "kalnpc" );
		OpenTexture ( MODEL_KALIMA_SHOP, "Npc\\" );
		break;
	case MODEL_BC_NPC1:
		AccessModel(MODEL_BC_NPC1, "Data\\Npc\\", "npcpharmercy1" );
		OpenTexture(MODEL_BC_NPC1, "Npc\\" );
		AccessModel(MODEL_BC_BOX, "Data\\Npc\\", "box");
		OpenTexture(MODEL_BC_BOX, "Npc\\" );
		break;
	case MODEL_BC_NPC2:
		AccessModel(MODEL_BC_NPC2, "Data\\Npc\\", "npcpharmercy2" );
		OpenTexture(MODEL_BC_NPC2, "Npc\\" );
		AccessModel(MODEL_BC_BOX, "Data\\Npc\\", "box");
		OpenTexture(MODEL_BC_BOX, "Npc\\" );
		break;
	case MODEL_CRYWOLF_STATUE:
		AccessModel ( MODEL_CRYWOLF_STATUE, "Data\\Object35\\", "Object82" );
		OpenTexture ( MODEL_CRYWOLF_STATUE, "Object35\\" );
		break;
	case MODEL_CRYWOLF_ALTAR1:
		AccessModel ( MODEL_CRYWOLF_ALTAR1, "Data\\Object35\\", "Object57" );
		OpenTexture ( MODEL_CRYWOLF_ALTAR1, "Object35\\" );
		break;
	case MODEL_CRYWOLF_ALTAR2:
		AccessModel ( MODEL_CRYWOLF_ALTAR2, "Data\\Object35\\", "Object57" );
		OpenTexture ( MODEL_CRYWOLF_ALTAR2, "Object35\\" );
		break;
	case MODEL_CRYWOLF_ALTAR3:
		AccessModel ( MODEL_CRYWOLF_ALTAR3, "Data\\Object35\\", "Object57" );
		OpenTexture ( MODEL_CRYWOLF_ALTAR3, "Object35\\" );
		break;
	case MODEL_CRYWOLF_ALTAR4:
		AccessModel ( MODEL_CRYWOLF_ALTAR4, "Data\\Object35\\", "Object57" );
		OpenTexture ( MODEL_CRYWOLF_ALTAR4, "Object35\\" );
		break;
	case MODEL_CRYWOLF_ALTAR5:
		AccessModel ( MODEL_CRYWOLF_ALTAR5, "Data\\Object35\\", "Object57" );
		OpenTexture ( MODEL_CRYWOLF_ALTAR5, "Object35\\" );
		break;
	case MODEL_KANTURU2ND_ENTER_NPC:
		{
			AccessModel(MODEL_KANTURU2ND_ENTER_NPC, "Data\\Npc\\", "to3gate");
			OpenTexture(MODEL_KANTURU2ND_ENTER_NPC, "Npc\\");
		}
		break;
	case MODEL_SMELTING_NPC:
		AccessModel ( MODEL_SMELTING_NPC, "Data\\Npc\\", "Elpis" );
		OpenTexture ( MODEL_SMELTING_NPC, "Npc\\" );
		break;
#ifdef ADD_NPC_DEVIN
	case MODEL_NPC_DEVIN:
		AccessModel(MODEL_NPC_DEVIN, "Data\\Npc\\", "devin" );
		OpenTexture(MODEL_NPC_DEVIN, "Npc\\");
		break;
#endif	// ADD_NPC_DEVIN
	case MODEL_NPC_QUARREL:
		AccessModel(MODEL_NPC_QUARREL, "Data\\Npc\\", "WereQuarrel" );
		OpenTexture(MODEL_NPC_QUARREL, "Monster\\");
		break;
	case MODEL_NPC_CASTEL_GATE:
		AccessModel(MODEL_NPC_CASTEL_GATE, "Data\\Npc\\", "cry2doorhead" );
		OpenTexture(MODEL_NPC_CASTEL_GATE, "Npc\\");
		break;
	case MODEL_CURSEDTEMPLE_ENTER_NPC:
		AccessModel ( MODEL_CURSEDTEMPLE_ENTER_NPC, "Data\\Npc\\", "mirazu" );
		OpenTexture ( MODEL_CURSEDTEMPLE_ENTER_NPC, "Npc\\" );
		break;
	case MODEL_CURSEDTEMPLE_ALLIED_NPC:
		AccessModel ( MODEL_CURSEDTEMPLE_ALLIED_NPC, "Data\\Npc\\", "allied" );
		OpenTexture ( MODEL_CURSEDTEMPLE_ALLIED_NPC, "Npc\\" );
		break;
	case MODEL_CURSEDTEMPLE_ILLUSION_NPC:
		AccessModel ( MODEL_CURSEDTEMPLE_ILLUSION_NPC, "Data\\Npc\\", "illusion" );
		OpenTexture ( MODEL_CURSEDTEMPLE_ILLUSION_NPC, "Npc\\" );
		break;		
	case MODEL_CURSEDTEMPLE_STATUE:
		AccessModel ( MODEL_CURSEDTEMPLE_STATUE, "Data\\Npc\\", "songsom" );
		OpenTexture ( MODEL_CURSEDTEMPLE_STATUE, "Npc\\" );
		break;
	case MODEL_CURSEDTEMPLE_ALLIED_BASKET:
		AccessModel ( MODEL_CURSEDTEMPLE_ALLIED_BASKET, "Data\\Npc\\", "songko" );
		OpenTexture ( MODEL_CURSEDTEMPLE_ALLIED_BASKET, "Npc\\" );
		break;
	case MODEL_CURSEDTEMPLE_ILLUSION__BASKET:
		AccessModel ( MODEL_CURSEDTEMPLE_ILLUSION__BASKET, "Data\\Npc\\", "songk2" );
		OpenTexture ( MODEL_CURSEDTEMPLE_ILLUSION__BASKET, "Npc\\" );
		break;
	case MODEL_WEDDING_NPC:
		AccessModel ( MODEL_WEDDING_NPC, "Data\\Npc\\", "Wedding" );
		OpenTexture( MODEL_WEDDING_NPC, "Npc\\");
		break;
	case MODEL_ELBELAND_SILVIA:
		AccessModel(MODEL_ELBELAND_SILVIA, "Data\\Npc\\", "silvia" );
		OpenTexture(MODEL_ELBELAND_SILVIA, "Npc\\");
		break;
	case MODEL_ELBELAND_RHEA:
		AccessModel(MODEL_ELBELAND_RHEA, "Data\\Npc\\", "rhea" );
		OpenTexture(MODEL_ELBELAND_RHEA, "Npc\\");
		break;
	case MODEL_ELBELAND_MARCE:
		AccessModel(MODEL_ELBELAND_MARCE, "Data\\Npc\\", "marce" );
		OpenTexture(MODEL_ELBELAND_MARCE, "Npc\\");
		break;
#ifdef CSK_EVENT_CHERRYBLOSSOM
	case MODEL_NPC_CHERRYBLOSSOM:
		AccessModel(MODEL_NPC_CHERRYBLOSSOM, "Data\\Npc\\cherryblossom\\", "cherry_blossom" );
		OpenTexture(MODEL_NPC_CHERRYBLOSSOM, "Npc\\cherryblossom\\");
		break;
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef PSW_EVENT_CHERRYBLOSSOMTREE
	case MODEL_NPC_CHERRYBLOSSOMTREE:
		AccessModel(MODEL_NPC_CHERRYBLOSSOMTREE, "Data\\Npc\\cherryblossom\\", "sakuratree" );
		OpenTexture(MODEL_NPC_CHERRYBLOSSOMTREE, "Npc\\cherryblossom\\");
		break;
#endif //PSW_EVENT_CHERRYBLOSSOMTREE		
#ifdef ADD_SOCKET_MIX
	case MODEL_SEED_MASTER:
		AccessModel(MODEL_SEED_MASTER, "Data\\Npc\\", "goblinmaster" );
		OpenTexture(MODEL_SEED_MASTER, "Npc\\");
		break;
	case MODEL_SEED_INVESTIGATOR:
		AccessModel(MODEL_SEED_INVESTIGATOR, "Data\\Npc\\", "seedgoblin" );
		OpenTexture(MODEL_SEED_INVESTIGATOR, "Npc\\");
		break;
#endif	// ADD_SOCKET_MIX
#ifdef PBG_ADD_LITTLESANTA_NPC
		//��Ʋ��Ÿ NPC.8����.
	case MODEL_LITTLESANTA:
	case MODEL_LITTLESANTA+1:
	case MODEL_LITTLESANTA+2:
	case MODEL_LITTLESANTA+3:
	case MODEL_LITTLESANTA+4:	
	case MODEL_LITTLESANTA+5:
	case MODEL_LITTLESANTA+6:
	case MODEL_LITTLESANTA+7:
		{
			//�Ѱ��� �𵨵�����.
			AccessModel(MODEL_LITTLESANTA +(Type - MODEL_LITTLESANTA), "Data\\Npc\\", "xmassanta");

			int _index = 9;
			int _index_end = 14;

			//���� �ٸ� �ؽ��ĳ����� �����ִ�.������ ���δ�.
			Models[Type].Textures->FileName[_index_end] = NULL;
			for(int i=_index_end-1; i>_index; i--)
			{
				Models[Type].Textures->FileName[i] = Models[Type].Textures->FileName[i-1];
			}
			int _temp = (Type - MODEL_LITTLESANTA) +1;
			char _temp2[10] = {0,};
			itoa(_temp, _temp2, 10);
			Models[Type].Textures->FileName[_index] = _temp2[0];

			//8���� �ؽ���.
			OpenTexture(MODEL_LITTLESANTA +(Type - MODEL_LITTLESANTA), "Npc\\");
		}
		break;
#endif //PBG_ADD_LITTLESANTA_NPC
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	case MODEL_XMAS2008_SNOWMAN:
		{
			//ũ�������� ����� ���� ���� ĳ���� ��
			AccessModel(MODEL_XMAS2008_SNOWMAN,			"Data\\Item\\xmas\\", "snowman");
			AccessModel(MODEL_XMAS2008_SNOWMAN_HEAD,	"Data\\Item\\xmas\\", "snowman_die_head_model");
			AccessModel(MODEL_XMAS2008_SNOWMAN_BODY,	"Data\\Item\\xmas\\", "snowman_die_body");
			OpenTexture(MODEL_XMAS2008_SNOWMAN,			"Item\\xmas\\" );
			OpenTexture(MODEL_XMAS2008_SNOWMAN_HEAD,	"Item\\xmas\\" );
			OpenTexture(MODEL_XMAS2008_SNOWMAN_BODY,	"Item\\xmas\\" );
			
			LoadWaveFile(SOUND_XMAS_SNOWMAN_WALK_1,		"Data\\Sound\\xmas\\SnowMan_Walk01.wav");
			LoadWaveFile(SOUND_XMAS_SNOWMAN_ATTACK_1,	"Data\\Sound\\xmas\\SnowMan_Attack01.wav");
			LoadWaveFile(SOUND_XMAS_SNOWMAN_ATTACK_2,	"Data\\Sound\\xmas\\SnowMan_Attack02.wav");
			LoadWaveFile(SOUND_XMAS_SNOWMAN_DAMAGE_1,	"Data\\Sound\\xmas\\SnowMan_Damage01.wav");
			LoadWaveFile(SOUND_XMAS_SNOWMAN_DEATH_1,	"Data\\Sound\\xmas\\SnowMan_Death01.wav");
		}
		break;
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef LDK_ADD_SNOWMAN_NPC
	case MODEL_XMAS2008_SNOWMAN_NPC:
		AccessModel(MODEL_XMAS2008_SNOWMAN_NPC, "Data\\Npc\\", "snowman" );
		OpenTexture(MODEL_XMAS2008_SNOWMAN_NPC, "Npc\\");
		break;
#endif //LDK_ADD_SNOWMAN_NPC
#ifdef LDK_ADD_SANTA_NPC
	case MODEL_XMAS2008_SANTA_NPC:
		AccessModel(MODEL_XMAS2008_SANTA_NPC, "Data\\Npc\\", "npcsanta" );
		OpenTexture(MODEL_XMAS2008_SANTA_NPC, "Npc\\");
		break;
#endif //LDK_ADD_SANTA_NPC
#ifdef YDG_ADD_NEW_DUEL_NPC
	case MODEL_DUEL_NPC_TITUS:
		AccessModel(MODEL_DUEL_NPC_TITUS, "Data\\Npc\\", "titus" );
		OpenTexture(MODEL_DUEL_NPC_TITUS, "Npc\\");

		LoadWaveFile(SOUND_DUEL_NPC_IDLE_1, "Data\\Sound\\w64\\GatekeeperTitus.wav");
		break;
#endif	// YDG_ADD_NEW_DUEL_NPC
#ifdef LDK_ADD_GAMBLE_NPC_MOSS
	case MODEL_GAMBLE_NPC_MOSS:
		AccessModel(MODEL_GAMBLE_NPC_MOSS, "Data\\Npc\\", "gambler_moss" );
		OpenTexture(MODEL_GAMBLE_NPC_MOSS, "Npc\\");
		break;
#endif //LDK_ADD_GAMBLE_NPC_MOSS
#ifdef YDG_ADD_DOPPELGANGER_NPC
	case MODEL_DOPPELGANGER_NPC_LUGARD:
		AccessModel(MODEL_DOPPELGANGER_NPC_LUGARD, "Data\\Npc\\", "Lugard" );
		OpenTexture(MODEL_DOPPELGANGER_NPC_LUGARD, "Npc\\");
#ifdef YDG_ADD_DOPPELGANGER_SOUND
		LoadWaveFile(SOUND_DOPPELGANGER_LUGARD_BREATH, "Data\\Sound\\Doppelganger\\Lugard.wav");
#endif	// YDG_ADD_DOPPELGANGER_SOUND
		break;
	case MODEL_DOPPELGANGER_NPC_BOX:
		AccessModel(MODEL_DOPPELGANGER_NPC_BOX, "Data\\Npc\\", "DoppelgangerBox" );
		OpenTexture(MODEL_DOPPELGANGER_NPC_BOX, "Npc\\");
#ifdef YDG_ADD_DOPPELGANGER_SOUND
		LoadWaveFile(SOUND_DOPPELGANGER_JEWELBOX_OPEN, "Data\\Sound\\Doppelganger\\treasurebox_open.wav");
#endif	// YDG_ADD_DOPPELGANGER_SOUND
		break;
	case MODEL_DOPPELGANGER_NPC_GOLDENBOX:
		AccessModel(MODEL_DOPPELGANGER_NPC_GOLDENBOX, "Data\\Npc\\", "DoppelgangerBox" );
		OpenTexture(MODEL_DOPPELGANGER_NPC_GOLDENBOX, "Npc\\");
#ifdef YDG_ADD_DOPPELGANGER_SOUND
		LoadWaveFile(SOUND_DOPPELGANGER_JEWELBOX_OPEN, "Data\\Sound\\Doppelganger\\treasurebox_open.wav");
#endif	// YDG_ADD_DOPPELGANGER_SOUND
		break;
#endif	// YDG_ADD_DOPPELGANGER_NPC
#ifdef ASG_ADD_GENS_NPC
	case MODAL_GENS_NPC_DUPRIAN:
		AccessModel(MODAL_GENS_NPC_DUPRIAN, "Data\\Npc\\", "duprian" );
		OpenTexture(MODAL_GENS_NPC_DUPRIAN, "Npc\\");
		break;
	case MODAL_GENS_NPC_BARNERT:
		AccessModel(MODAL_GENS_NPC_BARNERT, "Data\\Npc\\", "barnert" );
		OpenTexture(MODAL_GENS_NPC_BARNERT, "Npc\\");
		break;
#endif	// ASG_ADD_GENS_NPC
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
	case MODEL_UNITEDMARKETPLACE_CHRISTIN:
		AccessModel(MODEL_UNITEDMARKETPLACE_CHRISTIN, "Data\\Npc\\", "UnitedMarketPlace_christine" );
		OpenTexture(MODEL_UNITEDMARKETPLACE_CHRISTIN, "Npc\\");
		break;
	case MODEL_UNITEDMARKETPLACE_RAUL:
		AccessModel(MODEL_UNITEDMARKETPLACE_RAUL, "Data\\Npc\\", "UnitedMarkedPlace_raul" );
		OpenTexture(MODEL_UNITEDMARKETPLACE_RAUL, "Npc\\");
		break;
	case MODEL_UNITEDMARKETPLACE_JULIA:
		AccessModel(MODEL_UNITEDMARKETPLACE_JULIA, "Data\\Npc\\", "UnitedMarkedPlace_julia" );
		OpenTexture(MODEL_UNITEDMARKETPLACE_JULIA, "Npc\\");
		break;
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
#ifdef ASG_ADD_TIME_LIMIT_QUEST_NPC
	case MODEL_TIME_LIMIT_QUEST_NPC_TERSIA:
		AccessModel(MODEL_TIME_LIMIT_QUEST_NPC_TERSIA, "Data\\Npc\\", "tersia");
		OpenTexture(MODEL_TIME_LIMIT_QUEST_NPC_TERSIA, "Npc\\");
		break;
	case MODEL_TIME_LIMIT_QUEST_NPC_BENA:
		AccessModel(MODEL_TIME_LIMIT_QUEST_NPC_BENA, "Data\\Npc\\", "bena");
		OpenTexture(MODEL_TIME_LIMIT_QUEST_NPC_BENA, "Npc\\");
		break;
	case MODEL_TIME_LIMIT_QUEST_NPC_ZAIRO:	// �׺� NPC �𽺿� ����.
		AccessModel(MODEL_TIME_LIMIT_QUEST_NPC_ZAIRO, "Data\\Npc\\", "gambler_moss");
		OpenTexture(MODEL_TIME_LIMIT_QUEST_NPC_ZAIRO, "Npc\\");
		break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST_NPC
#ifdef ASG_ADD_KARUTAN_NPC
	case MODEL_KARUTAN_NPC_REINA:	// �η����� NPC ��ȭ���� ũ����ƾ�� ����.
		AccessModel(MODEL_KARUTAN_NPC_REINA, "Data\\Npc\\", "UnitedMarketPlace_christine");
		OpenTexture(MODEL_KARUTAN_NPC_REINA, "Npc\\");
		break;
	case MODEL_KARUTAN_NPC_VOLVO:
		AccessModel(MODEL_KARUTAN_NPC_VOLVO, "Data\\Npc\\", "volvo");
		OpenTexture(MODEL_KARUTAN_NPC_VOLVO, "Npc\\");
		break;
#endif	// ASG_ADD_KARUTAN_NPC
#ifdef LEM_ADD_LUCKYITEM
	case MODEL_LUCKYITEM_NPC:
		//AccessModel(MODEL_LUCKYITEM_NPC, "Data\\Npc\\", "volvo");
		AccessModel(MODEL_LUCKYITEM_NPC, "Data\\Npc\\LuckyItem\\", "npc_burial");
		OpenTexture(MODEL_LUCKYITEM_NPC, "Npc\\LuckyItem\\");
		break;
#endif // LEM_ADD_LUCKYITEM
	}
#ifdef _VS2008PORTING
	for(int i=0;i<b->NumActions;i++)
#else // _VS2008PORTING
	for(i=0;i<b->NumActions;i++)
#endif // _VS2008PORTING
		b->Actions[i].PlaySpeed = 0.25f;
    //SetTexture(BITMAP_NPC);

    if(b->NumMeshs > 0)
    	OpenTexture(Type,"Npc\\");

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	//���� �ӵ� ����
	switch(Type)
	{
	case MODEL_XMAS2008_SNOWMAN:
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.9f;
		break;
#ifdef PJH_ADD_PANDA_CHANGERING
	case MODEL_PANDA:
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.9f;
		break;
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_DOPPELGANGER_NPC
	case MODEL_DOPPELGANGER_NPC_BOX:
		Models[Type].Actions[MONSTER01_DIE].PlaySpeed = 0.1f;
		break;
	case MODEL_DOPPELGANGER_NPC_GOLDENBOX:
		Models[Type].Actions[MONSTER01_DIE].PlaySpeed = 0.1f;
		break;
#endif	// YDG_ADD_DOPPELGANGER_NPC
#ifdef ASG_ADD_GENS_NPC
	case MODAL_GENS_NPC_DUPRIAN:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.6f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.6f;
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 1.4f;
		break;
	case MODAL_GENS_NPC_BARNERT:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.3f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 1.2f;
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
#endif	// ASG_ADD_GENS_NPC
#ifdef LDS_ADD_NPC_UNITEDMARKETPLACE
	case MODEL_UNITEDMARKETPLACE_RAUL:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.5f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.5f;
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.5f;
		break;
	case MODEL_UNITEDMARKETPLACE_JULIA:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.5f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.5f;
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.5f;
		break;
	case MODEL_UNITEDMARKETPLACE_CHRISTIN:
#ifdef ASG_ADD_KARUTAN_NPC
	case MODEL_KARUTAN_NPC_REINA:
#endif	// ASG_ADD_KARUTAN_NPC
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.5f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.6f;
		Models[Type].Actions[MONSTER01_WALK].PlaySpeed = 0.5f;
		break;
#endif // LDS_ADD_NPC_UNITEDMARKETPLACE
#ifdef ASG_ADD_TIME_LIMIT_QUEST_NPC
	case MODEL_TIME_LIMIT_QUEST_NPC_TERSIA:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.35f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.3f;
		break;
#endif	// ASG_ADD_TIME_LIMIT_QUEST_NPC
#ifdef ASG_ADD_KARUTAN_NPC
	case MODEL_KARUTAN_NPC_VOLVO:
		Models[Type].Actions[MONSTER01_STOP1].PlaySpeed = 0.2f;
		Models[Type].Actions[MONSTER01_STOP2].PlaySpeed = 0.25f;
		break;
#endif	// ASG_ADD_KARUTAN_NPC
	}
#endif //LDK_ADD_SNOWMAN_CHANGERING


//#endif
}

///////////////////////////////////////////////////////////////////////////////
// ���� ���� ����
///////////////////////////////////////////////////////////////////////////////
void SetMonsterSound(int Type,int s1,int s2,int s3,int s4,int s5, int s6=-1, int s7=-1, int s8=-1, int s9=-1, int s10=-1 )
{
	Models[Type].Sounds[0] = s1;
	Models[Type].Sounds[1] = s2;
	Models[Type].Sounds[2] = s3;
	Models[Type].Sounds[3] = s4;
	Models[Type].Sounds[4] = s5;
	Models[Type].Sounds[5] = s6;
	Models[Type].Sounds[6] = s7;
	Models[Type].Sounds[7] = s8;
	Models[Type].Sounds[8] = s9;
	Models[Type].Sounds[9] = s10;
}

///////////////////////////////////////////////////////////////////////////////
// ���� ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void DeleteMonsters()
{
	for(int i=MODEL_MONSTER01;i<MODEL_MONSTER_END;i++)
		Models[i].Release();

#ifdef _VS2008PORTING
	for(int i=SOUND_MONSTER;i<SOUND_MONSTER_END;i++)
#else // _VS2008PORTING
	for(i=SOUND_MONSTER;i<SOUND_MONSTER_END;i++)
#endif // _VS2008PORTING
		ReleaseBuffer(i);

#ifdef _VS2008PORTING
	for(int i=SOUND_ELBELAND_RABBITSTRANGE_ATTACK01;i<=SOUND_ELBELAND_ENTERATLANCE01;i++)
#else // _VS2008PORTING
	for(i=SOUND_ELBELAND_RABBITSTRANGE_ATTACK01;i<=SOUND_ELBELAND_ENTERATLANCE01;i++)
#endif // _VS2008PORTING
		ReleaseBuffer(i);
}

///////////////////////////////////////////////////////////////////////////////
// ���� ����Ÿ �о���̴� �Լ�(���ӻ󿡼� ����Ʈ�� �������� �ε�)
///////////////////////////////////////////////////////////////////////////////

void OpenMonsterModel(int Type)
{
	g_ErrorReport.Write( "OpenMonsterModel(%d)\r\n", Type);

	int Index = MODEL_MONSTER01+Type;

  	BMD *b = &Models[Index];
	if(b->NumActions > 0 || b->NumMeshs > 0) return;

	// ���� �� �ε�
	AccessModel(Index,"Data\\Monster\\","Monster",Type+1);

	if(b->NumMeshs == 0) return;

    if ( InChaosCastle()==true && Type>=70 && Type<=72 )
    {
    	OpenTexture(Index,"Npc\\");
    }
    else if ( battleCastle::InBattleCastle()==true && Type==74 )   //  ��ȣ����.
    {
        OpenTexture ( Index, "Object31\\" );
    }
    else
    {
		OpenTexture(Index,"Monster\\");
    }

	// ���� ���� �μ�ǰ �ε�
#ifdef ADD_RAKLION_MOB_ICEGIANT
	switch(Type)
	{
	case 147:	// ���̽� ���̾�Ʈ
		{
			// ���� �� ���� �𵨵�
			AccessModel(MODEL_ICE_GIANT_PART1, "Data\\Monster\\", "icegiantpart_1");
			OpenTexture(MODEL_ICE_GIANT_PART1, "Monster\\");
			AccessModel(MODEL_ICE_GIANT_PART2, "Data\\Monster\\", "icegiantpart_2");
			OpenTexture(MODEL_ICE_GIANT_PART2, "Monster\\");
			AccessModel(MODEL_ICE_GIANT_PART3, "Data\\Monster\\", "icegiantpart_3");
			OpenTexture(MODEL_ICE_GIANT_PART3, "Monster\\");
			AccessModel(MODEL_ICE_GIANT_PART4, "Data\\Monster\\", "icegiantpart_4");
			OpenTexture(MODEL_ICE_GIANT_PART4, "Monster\\");
			AccessModel(MODEL_ICE_GIANT_PART5, "Data\\Monster\\", "icegiantpart_5");
			OpenTexture(MODEL_ICE_GIANT_PART5, "Monster\\");
			AccessModel(MODEL_ICE_GIANT_PART6, "Data\\Monster\\", "icegiantpart_6");
			OpenTexture(MODEL_ICE_GIANT_PART6, "Monster\\");
		}
		break;
	}
#endif // ADD_RAKLION_MOB_ICEGIANT

	// ���� ���� �ӵ� �����ϴ� ��ġ
	b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
	b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.2f;
	b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.34f;
	b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.33f;
	b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.33f;
	b->Actions[MONSTER01_SHOCK  ].PlaySpeed = 0.5f;
	b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.55f;
	b->Actions[MONSTER01_DIE    ].Loop      = true;

	for(int j=MONSTER01_STOP1;j<MONSTER01_DIE;j++)
	{
		if(Type==3)
			b->Actions[j].PlaySpeed *= 1.2f;
		if(Type==5 || Type==25)
			b->Actions[j].PlaySpeed *= 0.7f;
		if(Type==37 || Type==42)
			b->Actions[j].PlaySpeed *= 0.4f;
	}

	switch(Type)
	{
	case 2 :b->Actions[MONSTER01_WALK].PlaySpeed = 0.7f;break;//����
	case 6 :b->Actions[MONSTER01_WALK].PlaySpeed = 0.6f;break;//����
	case 8 :b->Actions[MONSTER01_WALK].PlaySpeed = 0.7f;break;//�Ź�����
	case 9 :b->Actions[MONSTER01_WALK].PlaySpeed = 1.2f;break;//�Ź�
	case 10:b->Actions[MONSTER01_WALK].PlaySpeed = 0.28f;break;//����ũ�ӽ�
	case 12:b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;break;//����
	case 13:b->Actions[MONSTER01_WALK].PlaySpeed = 0.28f;break;//����
	case 17:b->Actions[MONSTER01_WALK].PlaySpeed = 0.5f;break;//������
	case 19:b->Actions[MONSTER01_WALK].PlaySpeed = 0.6f;break;//���
	case 20:b->Actions[MONSTER01_WALK].PlaySpeed = 0.4f;break;//����
	case 21:b->Actions[MONSTER01_WALK].PlaySpeed = 0.5f;break;//ǳ����
	case 28:b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;break;//������
	case 39:b->Actions[MONSTER01_WALK].PlaySpeed = 0.22f;break;//
	case 41:b->Actions[MONSTER01_WALK].PlaySpeed = 0.18f;break;//���̾���
	case 42:
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.35f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.35f;
		break;//źŸ�ν�
	case 44:
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.3f;
		break;//������Ʈ
    case 63:    //  �ź���.
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.1f;
        break;
    case 64:	// ��¥���
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.15f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
        break;
    case 66:    //  ������
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.1f;
        break;
    case 67:    //  ��糪��Ʈ.
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.2f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.3f;
        break;
    case 69:	// ����ĺ�
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.1f;
        break;
    case 70:	// 
    case 71:	// 
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.5f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.5f;
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
        break;
    case 72:	// 
//    case 73:	// 
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
        break;
	case 89: // �߰���
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_ATTACK3].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_ATTACK4].PlaySpeed = 0.33f;
		break;
	case 94:
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.20f;
		break;
	case 92: // ��ũ ����
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_ATTACK3].PlaySpeed = 0.33f;
		break;
	case 99:
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.37f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.37f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.15f;
		break;
	case 100:
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
		break;
	case 101:
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
	case 102:	// �������̴�
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.15f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.15f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
#ifdef CSK_FIX_AIDAMONSTER_DIESPEED
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.15f;
#endif // CSK_FIX_AIDAMONSTER_DIESPEED
		break;
#ifdef CSK_FIX_AIDAMONSTER_DIESPEED
	case 104:	// ����Ʈ��
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
		break;
#endif // CSK_FIX_AIDAMONSTER_DIESPEED
	case 105:
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.15f;
		break;
// ĭ���� ���� �ִϸ��̼� �ӵ�
	case 106:	// ����Ŀ.
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.28f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.28f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.19f;
		break;
	case 107:
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;		
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.30f;
		break;
	case 108:
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;		
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
		break;
	case 109:	// ��Ƽ�ν�.
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.3f;
		break;
	case 110:	// ���̵� ����.
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
		break;
	case 111:	// ��Ÿ��ν�.
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.27f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
	case 112:	// �ⰣƼ��.
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.26f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.26f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.21f;
		break;
	case 113:	// ������̴�.
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_SHOCK  ].PlaySpeed = 0.5f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.3f;
		break;
	case 114:	// �丣�ҳ� ���ϸ��̼� �ӵ�
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.34f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.23f;
		break;
	case 115:	// Ʈ������ ���ϸ��̼� �ӵ�
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.34f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.23f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.23f;
		break;
	case 116:	// �巡���Ǿ� ���ϸ��̼� �ӵ�
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.34f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
		break;
	case 121: // ����Ʈ�޾�
		b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.22f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.22f;
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.12f;
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.22f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK3].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK4].PlaySpeed = 0.25f;
		break;
	case 118: // ���� �޼�
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.12f;
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.12f;
	case 119: // ���� ������
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.12f;
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.12f;
	case 120: // ����
		break;
	case 122:
		b->Actions[MONSTER01_SHOCK  ].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_DIE	].PlaySpeed = 0.22f;
		break;
#ifdef PRUARIN_EVENT07_3COLORHARVEST
	case 127:	// ���䳢
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.40f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.40f;		
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.40f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.40f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.50f;
		break;
#endif // PRUARIN_EVENT07_3COLORHARVEST
#ifdef KJH_ADD_09SUMMER_EVENT
	case 154:	// '09�Ϻ� �����̺�Ʈ ��� ĳ����
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.30f;		
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.60f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.50f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.50f;
		break;
#endif // KJH_ADD_09SUMMER_EVENT
#ifdef PBG_ADD_PKFIELD
	case 157:	//���� ����
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.17f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
		}
		break;
	case 158:	//�ǻ�Ƴ� ������
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.2f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.18f;
		}
		break;
	case 159:	//����� ������
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.2f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.4f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.17f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.2f;
		}
		break;
	case 160:	//���� �ϻ���
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.5f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.17f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.4f;
		}
		break;
	case 161:	//��Ȥ�� ���� �ϻ���
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.5f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.17f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.4f;
		}
		break;
	case 162:	//��Ÿ�� ��ϰ���
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
		}
		break;
	case 163:	//������ ��ϰ���
		{
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
		}
		break;
#endif //PBG_ADD_PKFIELD
	case 128:	// �Ⱬ�� �䳢
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.28f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 129:	// ������ �䳢
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.23f;
		break;
	case 130:	// �����ΰ�
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.50f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.50f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.30f;
		break;
	case 131:	// ������ ����
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.45f;
		break;
	case 132:	// ���ֹ�����ġ
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.35;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.35f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.30f;
		break;
	case 133:	// ���۰�
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.35;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.35f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.20f;
		break;
	case 134:	// ���� �쾾
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.33f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.22f;
		break;
	case 135:	// ���� �쾾 ����
		b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.30f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.28f;
		break;
	case 136:	// ����-�촩��
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 137:	// ����-�ο�
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 138:	// ����-Ʈ����
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 139:	// ������ ��
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 140:	// ������ ����Ʈ
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.45f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 141:	// ������ ��
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
		break;
	case 142:	// ��� ������
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.20f;
		break;
	case 143:	// ��Ʈ ������
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.20f;
		break;
	case 144:	// ������ ������
		b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.20f;
		break;
#ifdef CSK_ADD_MAP_ICECITY
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 145:	// ���̽� ��Ŀ
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.6f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.35f;
		break;
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 146:	// ���̾�Ʈ �Ÿӵ�
		break;
	case 147:	// ���̽� ���̾�Ʈ
#ifdef ADD_RAKLION_MOB_ICEGIANT
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.13f;
#endif	// ADD_RAKLION_MOB_ICEGIANT
		break;
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case 148:	// ��ƾ
		b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.46f;
		break;
#endif // LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef ADD_RAKLION_IRON_KNIGHT
	case 149:	// ���̾� ����Ʈ
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.21f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.23f;
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT
	case 150:	// ������ (��������)	
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.20f;
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.35f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.18f;
		b->Actions[MONSTER01_APEAR].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK3].PlaySpeed = 0.25f;
		b->Actions[MONSTER01_ATTACK4].PlaySpeed = 0.25f;
		break;
	case 151:	// �Ŵ� �Ź̾�
	case 152:	// �Ŵ� �Ź̾�
	case 153:	// �Ŵ� �Ź̾�
		break;
#endif // CSK_ADD_MAP_ICECITY
#ifdef YDG_ADD_SANTA_MONSTER
	case 155:	// ���ֹ��� ��Ÿ
		b->Actions[MONSTER01_STOP2].PlaySpeed = 0.3f;
		b->Actions[MONSTER01_WALK].PlaySpeed = 0.29f;
		b->Actions[MONSTER01_DIE].PlaySpeed = 0.4f;
		break;
#endif	// YDG_ADD_SANTA_MONSTER
#ifdef LDS_ADD_EMPIRE_GUARDIAN	//���� ��ȣ��
	#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN	// ���� ��ȣ�� ��4   (��	  )���� ���� ���� ���̿� ī����	(504/164)
		case 164:	// ���� ��ȣ�� ��4   (��	  )���� ���� ���� ���̿� ī����	(504/164)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.38f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.20f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.40f;	// ����ȭ ����
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.38f;
			b->Actions[MONSTER01_ATTACK4].PlaySpeed =	0.38f;
			break;
	#endif //LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN			// ���� ��ȣ�� ��4   (��	  )���� ���� ���� ���̿� ī����	(504/164)
	#ifdef LDS_ADD_EG_4_MONSTER_JELINT					// ���� ��ȣ�� ��4   (��	  )���� ���̿� ���°� ����Ʈ		(505/165)
		case 165:	// ���� ��ȣ�� ��4   (��	  )���� ���̿� ���°� ����Ʈ		(505/165)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.50f;
#ifdef LDS_FIX_EG_JERINT_ATTK1_ATTK2_SPEED
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.86f;	//	0.43f
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.86f;	//	0.43f
#else // LDS_FIX_EG_JERINT_ATTK1_ATTK2_SPEED
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.43f;	//0.86f;	//	0.43f
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.43f;	//0.86f;	//	0.43f
#endif // LDS_FIX_EG_JERINT_ATTK1_ATTK2_SPEED
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.40f;	// ����ȭ ����
#ifdef LDS_FIX_EG_JERINT_ANIMATION_AND_SWORDFORCE_SPEED
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.76f;	// ����3
#else // LDS_FIX_EG_JERINT_ANIMATION_AND_SWORDFORCE_SPEED
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.43f;	// ����3
#endif // LDS_FIX_EG_JERINT_ANIMATION_AND_SWORDFORCE_SPEED
			break;
	#endif //LDS_ADD_EG_4_MONSTER_JELINT					// ���� ��ȣ�� ��4   (��	  )���� ���̿� ���°� ����Ʈ		(505/165)
	#ifdef LDK_ADD_EG_MONSTER_RAYMOND			// ���� ��ȣ�� �λ�ɰ� ���̸�� (��, ��)
		case 166:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.55f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.75f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.50f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.50f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.80f;
			break;
	#endif //LDK_ADD_EG_MONSTER_RAYMOND			// ���� ��ȣ�� �λ�ɰ� ���̸�� (��, ��)
	#ifdef LDS_ADD_EG_2_4_MONSTER_ERCANNE				// ���� ��ȣ�� ��2,4 (ȭ��,��)���� ���ְ� ����ĭ��			(507/167)
		case 167:	// ���� ��ȣ�� ��2,4 (ȭ��,��)���� ���ְ� ����ĭ��			(507/167)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.71f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.80f;	// ����ȭ ����
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.40f;	// ����3
			break;
	#endif //LDS_ADD_EG_2_4_MONSTER_ERCANNE				// ���� ��ȣ�� ��2,4 (ȭ��,��)���� ���ְ� ����ĭ��			(507/167)
	#ifdef LDK_ADD_EG_MONSTER_DEASULER			// ���� ��ȣ�� 1������ ������
		case 168:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.38f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_ATTACK4].PlaySpeed =	0.45f;
			break;
	#endif	// LDK_ADD_EG_MONSTER_DEASULER			// ���� ��ȣ�� 1������ ������
	#ifdef LDS_ADD_EG_2_MONSTER_2NDCORP_VERMONT		// ���� ��ȣ�� ��2   (ȭ,  ��)���� 2������ ����Ʈ			(509/169)
		case 169:	// ���� ��ȣ�� ��2   (ȭ,  ��)���� 2������ ����Ʈ			(509/169)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.35f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.45f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.45f;	// ����ȭ ����
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.45f;	// ����3
			
			break;
	#endif //LDS_ADD_EG_2_MONSTER_2NDCORP_VERMONT		// ���� ��ȣ�� ��2   (ȭ,  ��)���� 2������ ����Ʈ			(509/169)
	#ifdef LDK_ADD_EG_MONSTER_CATO				// ���� ��ȣ�� 3������ ī��
		case 170:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.35f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.35f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.35f;
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.40f;
			break;
	#endif	// LDK_ADD_EG_MONSTER_CATO				// ���� ��ȣ�� 3������ ī��
	#ifdef LDK_ADD_EG_MONSTER_GALLIA			// ���� ��ȣ�� 4������ ������
		case 171:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.45f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.50f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.45f;
			break;
	#endif //LDK_ADD_EG_MONSTER_GALLIA			// ���� ��ȣ�� 4������ ������
	#ifdef LDK_ADD_EG_MONSTER_QUARTERMASTER		// ���� ��ȣ�� �����屳
		case 172:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.25f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.20f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.66f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.55f;
// 			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.33f;
			break;
	#endif	// LDK_ADD_EG_MONSTER_QUARTERMASTER		// ���� ��ȣ�� �����屳
	#ifdef LDK_ADD_EG_MONSTER_DRILLMASTER		// ���� ��ȣ�� ��������
		case 173:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.25f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.20f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.36f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.40f;		// Attack3
			break;
	#endif	// LDK_ADD_EG_MONSTER_DRILLMASTER		// ���� ��ȣ�� ��������
	#ifdef LDS_ADD_EG_2_MONSTER_ARTICLECAPTAIN		// ���� ��ȣ�� ��2   (ȭ,  ��)���� ������					(514/174)
		case 174:	// ���� ��ȣ�� ��2   (ȭ,  ��)���� ������					(514/174)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.65f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.86f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.86f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.86f;	// ����3
			break;
	#endif // ���� ��ȣ�� ��2   (ȭ,  ��)���� ������					(514/174)
	#ifdef LDS_ADD_EG_2_MONSTER_GRANDWIZARD			// ���� ��ȣ�� ��2   (ȭ,  ��)���� �븶����					(515/175)
		case 175:	// ���� ��ȣ�� ��2   (ȭ,  ��)���� �븶����					(515/175)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.60f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.80f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.96f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.96f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		1.00f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
// 			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.96f;	// ����3
			break;
	#endif // ���� ��ȣ�� ��2   (ȭ,  ��)���� �븶����					(515/175)
	#ifdef LDK_ADD_EG_MONSTER_ASSASSINMASTER	// ���� ��ȣ�� �ϻ��屳
		case 176:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.25f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.20f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.20f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.38f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.38f;
			break;
	#endif	// LDK_ADD_EG_MONSTER_ASSASSINMASTER	// ���� ��ȣ�� �ϻ��屳
	#ifdef LDK_ADD_EG_MONSTER_RIDERMASTER		// ���� ��ȣ�� �⸶����
		case 177:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.37f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			break;
	#endif	// LDK_ADD_EG_MONSTER_RIDERMASTER		// ���� ��ȣ�� �⸶����
	#ifdef LDS_ADD_EG_ADDMONSTER_ACTION_GUARDIANDEFENDER_EX	// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ���к�			(518/178)
		case 178:	// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ���к�			(518/178)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.40f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.45f;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.40f;
			break;
	#endif // LDS_ADD_EG_ADDMONSTER_ACTION_GUARDIANDEFENDER_EX ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ���к�			(518/178)
	#ifdef LDS_ADD_EG_2_MONSTER_GUARDIANPRIEST		// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ġ����			(519/179)
		case 179:	// ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ġ����			(519/179)
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.80f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.80f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.80f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.80f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.80f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.40f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.40f;
			break;
	#endif // LDS_ADD_EG_2_MONSTER_GUARDIANPRIEST ���� ��ȣ�� �� 1234(������)���� ��ȣ�� ġ����			(519/179)
	#ifdef LDK_ADD_EG_MONSTER_KNIGHTS			//���� ��ȣ�� ����
		case 180:
	 		b->Actions[MONSTER01_STOP1].PlaySpeed =		0.25f;
	 		b->Actions[MONSTER01_STOP2].PlaySpeed =		0.20f;
	 		b->Actions[MONSTER01_WALK].PlaySpeed =		0.55f;
	 		b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.66f;
	 		b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.66f;
	 		b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
	 		b->Actions[MONSTER01_DIE].PlaySpeed =		0.55f;
			break;
	#endif //LDK_ADD_EG_MONSTER_KNIGHTS
	#ifdef LDK_ADD_EG_MONSTER_GUARD			//���� ��ȣ�� ȣ����
		case 181:
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.35f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.33f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.50f;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30f;
			break;
	#endif //LDK_ADD_EG_MONSTER_GUARD

#endif //LDS_ADD_EMPIRE_GUARDIAN
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
		case 189:	// ������
		case 190:	// �г��ѵ�����
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.3f;
			break;
		case 191:	// ���ð��� ������
			b->Actions[MONSTER01_STOP1].PlaySpeed = 0.25f * 2.0f;
			b->Actions[MONSTER01_STOP2].PlaySpeed = 0.2f * 2.0f;
			b->Actions[MONSTER01_WALK].PlaySpeed = 0.34f * 2.0f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.25f * 2.0f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.25f * 2.0f;
			b->Actions[MONSTER01_SHOCK].PlaySpeed = 0.5f * 2.0f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.55f * 2.0f;
			b->Actions[MONSTER01_APEAR].PlaySpeed = 0.33f * 3.0f;		// ����
			break;
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef LDK_ADD_EXTENSIONMAP_BOSS_MEDUSA
		case 192:	// ����Ǵ� �޵�� �ӽù�ȣ
			b->Actions[MONSTER01_STOP1].PlaySpeed =		0.30f;
			b->Actions[MONSTER01_STOP2].PlaySpeed =		0.30;
			b->Actions[MONSTER01_WALK].PlaySpeed =		0.30;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed =	0.30;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed =	0.30;
			b->Actions[MONSTER01_SHOCK].PlaySpeed =		0.30;
			b->Actions[MONSTER01_DIE].PlaySpeed =		0.30;
			b->Actions[MONSTER01_APEAR].PlaySpeed =		0.30;	// ����ȭ ����
			b->Actions[MONSTER01_ATTACK3].PlaySpeed =	0.30;
			break;
#endif //LDK_ADD_EXTENSIONMAP_BOSS_MEDUSA
#ifdef LDS_EXTENSIONMAP_MONSTERS_RAKLION
		case 205:	// ��ũ ���̾�Ʈ �Ÿӵ�
			break;	
		case 206:	// ��ũ ���̽� ���̾�Ʈ
			b->Actions[MONSTER01_DIE].PlaySpeed			= 0.13f;
			break;
		case 207:	// ��ũ ��ƾ
			b->Actions[MONSTER01_WALK   ].PlaySpeed		= 0.46f;
			break;
		case 208:	// ��ũ ���̾� ����Ʈ
			b->Actions[MONSTER01_WALK].PlaySpeed		= 0.25f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed		= 0.21f;
			b->Actions[MONSTER01_DIE].PlaySpeed			= 0.23f;
			break;
#endif // LDS_EXTENSIONMAP_MONSTERS_RAKLION
#ifdef LDS_EXTENSIONMAP_MONSTERS_AIDA
		case 193:	// ���� ������Ʈ ��ũ
			break;
		case 194:	// ���� �������̴�
			b->Actions[MONSTER01_STOP1  ].PlaySpeed		= 0.15f;
			b->Actions[MONSTER01_STOP2  ].PlaySpeed		= 0.15f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed		= 0.23f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed		= 0.23f;
			b->Actions[MONSTER01_WALK].PlaySpeed		= 0.3f;
			b->Actions[MONSTER01_DIE].PlaySpeed			= 0.15f;
			break;
		case 195:	// ���� ����
			b->Actions[MONSTER01_DIE].PlaySpeed			= 0.2f;
			break;
		case 196:	// ���� ��ġ��
			b->Actions[MONSTER01_DIE].PlaySpeed			= 0.2f;
			break;
#endif // LDS_EXTENSIONMAP_MONSTERS_AIDA
#ifdef LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET
		case 201:	// ����-��
			b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
			break;
		case 202:	// ���̽� ������
			b->Actions[MONSTER01_WALK ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.20f;
			break;
		case 203:	// ������ ������
			b->Actions[MONSTER01_DIE  ].PlaySpeed = 0.25f;
			break;
#endif // LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET
#ifdef LDS_EXTENSIONMAP_MONSTERS_KANTUR
		case 197:	// ����Ŀ ������
			b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.23f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.28f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.19f;
			break;
		case 198:	// ��Ÿ��ν� ������
			b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.27f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.27f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.27f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.25f;
		case 199:	// �ⰣƼ�� ������
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.26f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.26f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.21f;
			break;
		case 200:	// ������̴� ������
			b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.3f;
			b->Actions[MONSTER01_SHOCK  ].PlaySpeed = 0.5f;
			b->Actions[MONSTER01_DIE].PlaySpeed = 0.3f;
			break;
#endif // LDS_EXTENSIONMAP_MONSTERS_KANTUR
#ifdef ASG_ADD_KARUTAN_MONSTERS
		case 209:	// �͵�������
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.95f;
			break;
		case 210:	// �������ǿ�
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 1.00f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.40f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.40f;
			b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.20f;
			break;
		case 211:	// ����Ŀ��
			b->Actions[MONSTER01_STOP1  ].PlaySpeed = 0.7f;
			b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.7f;
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.6f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.8f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.8f;
			b->Actions[MONSTER01_SHOCK  ].PlaySpeed = 0.25f;
			b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.3f;
			break;
		case 212:	// ���
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.4f;
			b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.3f;
			break;
		case 213:	// ũ��Ÿ
		case 214:	// ũ������
			b->Actions[MONSTER01_WALK   ].PlaySpeed = 0.9f;
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.37f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.37f;
			b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.25f;
			break;
		case 215:	// �ܵ��
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.80f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.80f;
			break;
		case 216:	// �����ܵ��
			b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.75f;
			b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.75f;
			break;
#endif	// ASG_ADD_KARUTAN_MONSTERS
	}
	switch(Type)
	{
	case 14:
	case 31:
	case 39:
	case 40:
		b->Actions[MONSTER01_STOP2  ].Loop = true;
		break;
	}

	//  ���͵��� ȿ������ ����Ѵ�.
    int Channel = 2;
	bool Enable = true;
	switch(Type)
	{
    case 70:    //  ������. 
    case 71:
		LoadWaveFile ( SOUND_MONSTER+161, "Data\\Sound\\mOrcCapAttack1.wav", Channel, Enable );
		SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, 161, 161, -1 );
		Models[MODEL_MONSTER01+Type].BoneHead = 20;
        break;

    case 72:    //  ������. 
		LoadWaveFile ( SOUND_MONSTER+162, "Data\\Sound\\mOrcArcherAttack1.wav"  ,Channel, Enable );
		SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, 162, 162, -1 );
		Models[MODEL_MONSTER01+Type].BoneHead = 20;
        break;
	case 0:
	case 30:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER	,"Data\\Sound\\m�һ�1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+1,"Data\\Sound\\m�һ�2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+2,"Data\\Sound\\m�һ԰���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+3,"Data\\Sound\\m�һ԰���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\m�һ��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER	,"Data\\Sound\\mBull1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+1,"Data\\Sound\\mBull2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+2,"Data\\Sound\\mBullAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+3,"Data\\Sound\\mBullAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\mBullDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,0 ,1 ,2 ,3 ,4 );
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//�һ�
		break;
	case 1:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+5,"Data\\Sound\\m�Ͽ��1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+6,"Data\\Sound\\m�Ͽ��2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+7,"Data\\Sound\\m�Ͽ�����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+8,"Data\\Sound\\m�Ͽ�����2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+9,"Data\\Sound\\m�Ͽ���ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+5,"Data\\Sound\\mHound1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+6,"Data\\Sound\\mHound2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+7,"Data\\Sound\\mHoundAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+8,"Data\\Sound\\mHoundAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+9,"Data\\Sound\\mHoundDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,5 ,6 ,7 ,8 ,9 );
		Models[MODEL_MONSTER01+Type].BoneHead = 5;//�Ͽ��
		break;
	case 2:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+10,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+11,"Data\\Sound\\m��������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+12,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+10,"Data\\Sound\\mBudge1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+11,"Data\\Sound\\mBudgeAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+12,"Data\\Sound\\mBudgeDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,10,11,11,11,12);
		Models[MODEL_MONSTER01+Type].BoneHead = 7;//����
		break;
	case 9:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+13,"Data\\Sound\\m�Ź�1.wav"    ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+13,"Data\\Sound\\mSpider1.wav"    ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,13,13,13,13,13);//�Ź�
		break;
	case 3://��ũ����Ʈ
	case 29://��������Ʈ
	case 39://Ÿ��ź
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+15,"Data\\Sound\\m��ũ����Ʈ1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+16,"Data\\Sound\\m��ũ����Ʈ2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+17,"Data\\Sound\\m��ũ����Ʈ����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+18,"Data\\Sound\\m��ũ����Ʈ����2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+19,"Data\\Sound\\m��ũ����Ʈ�ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+15,"Data\\Sound\\mDarkKnight1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+16,"Data\\Sound\\mDarkKnight2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+17,"Data\\Sound\\mDarkKnightAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+18,"Data\\Sound\\mDarkKnightAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+19,"Data\\Sound\\mDarkKnightDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,15,16,17,18,19);
		if(Type==3)
       		Models[MODEL_MONSTER01+Type].BoneHead = 16;//��ũ
		else if(Type==29)
      		Models[MODEL_MONSTER01+Type].BoneHead = 20;//���� ����Ʈ
		else
      		Models[MODEL_MONSTER01+Type].BoneHead = 19;//Ÿ��ź
		break;
	case 4:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+20,"Data\\Sound\\m������1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+21,"Data\\Sound\\m������2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+22,"Data\\Sound\\m���������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+23,"Data\\Sound\\m���������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+24,"Data\\Sound\\m�������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+20,"Data\\Sound\\mWizard1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+21,"Data\\Sound\\mWizard2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+22,"Data\\Sound\\mWizardAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+23,"Data\\Sound\\mWizardAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+24,"Data\\Sound\\mWizardDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,20,21,22,23,24);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//������
		break;
	case 5:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+25,"Data\\Sound\\m���̾�Ʈ1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+26,"Data\\Sound\\m���̾�Ʈ2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+27,"Data\\Sound\\m���̾�Ʈ����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+28,"Data\\Sound\\m���̾�Ʈ����2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+29,"Data\\Sound\\m���̾�Ʈ�ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+25,"Data\\Sound\\mGiant1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+26,"Data\\Sound\\mGiant2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+27,"Data\\Sound\\mGiantAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+28,"Data\\Sound\\mGiantAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+29,"Data\\Sound\\mGiantDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,25,26,27,28,29);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//���̾�Ʈ
		break;
	case 6:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+30,"Data\\Sound\\m����1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+31,"Data\\Sound\\m����2.wav"   ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+30,"Data\\Sound\\mLarva1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+31,"Data\\Sound\\mLarva2.wav"   ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,30,31,30,31,31);//����
		break;
	case 8:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+32,"Data\\Sound\\m�ｺ���̴�1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+33,"Data\\Sound\\m�ｺ���̴�����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+34,"Data\\Sound\\m�ｺ���̴��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+32,"Data\\Sound\\mHellSpider1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+33,"Data\\Sound\\mHellSpiderAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+34,"Data\\Sound\\mHellSpiderDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,32,33,33,33,34);
		Models[MODEL_MONSTER01+Type].BoneHead = 16;//�ｺ���̴�
		break;
	case 7:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+35,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+36,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+37,"Data\\Sound\\m���ɰ���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+38,"Data\\Sound\\m���ɰ���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+39,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+35,"Data\\Sound\\mGhost1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+36,"Data\\Sound\\mGhost2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+37,"Data\\Sound\\mGhostAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+38,"Data\\Sound\\mGhostAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+39,"Data\\Sound\\mGhostDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,35,36,37,38,39);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//��Ʈ
		break;
	case 10:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+40,"Data\\Sound\\m�����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+41,"Data\\Sound\\m�����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+42,"Data\\Sound\\m����Ű���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+43,"Data\\Sound\\m����Ű���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+44,"Data\\Sound\\m������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+40,"Data\\Sound\\mOgre1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+41,"Data\\Sound\\mOgre2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+42,"Data\\Sound\\mOgreAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+43,"Data\\Sound\\mOgreAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+44,"Data\\Sound\\mOgreDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,40,41,42,43,44);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//�����
		break;
	case 11:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+45,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+46,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+47,"Data\\Sound\\m���հ���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+48,"Data\\Sound\\m���հ���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+49,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+45,"Data\\Sound\\mGorgon1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+46,"Data\\Sound\\mGorgon2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+47,"Data\\Sound\\mGorgonAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+48,"Data\\Sound\\mGorgonAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+49,"Data\\Sound\\mGorgonDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,45,46,47,48,49);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//����
		break;
	case 15:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+50,"Data\\Sound\\m��������1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+51,"Data\\Sound\\m��������2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+52,"Data\\Sound\\m���������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+50,"Data\\Sound\\mIceMonster1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+51,"Data\\Sound\\mIceMonster2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+52,"Data\\Sound\\mIceMonsterDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,50,51,50,50,52);
		Models[MODEL_MONSTER01+Type].BoneHead = 19;//����
		break;
	case 17:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+53,"Data\\Sound\\m��1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+54,"Data\\Sound\\m��2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+55,"Data\\Sound\\m���ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+53,"Data\\Sound\\mWorm1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+54,"Data\\Sound\\mWorm2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+55,"Data\\Sound\\mWormDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,53,53,55,55,55);
		break;
	case 16:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+56,"Data\\Sound\\mȣ�ӵ�1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+57,"Data\\Sound\\mȣ�ӵ�2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+58,"Data\\Sound\\mȣ�ӵ����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+59,"Data\\Sound\\mȣ�ӵ��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+56,"Data\\Sound\\mHomord1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+57,"Data\\Sound\\mHomord2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+58,"Data\\Sound\\mHomordAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+59,"Data\\Sound\\mHomordDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,56,57,58,58,59);
		break;
	case 18:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+60,"Data\\Sound\\m���̽���1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+61,"Data\\Sound\\m���̽���2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+62,"Data\\Sound\\m���̽�������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+63,"Data\\Sound\\m���̽�������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+64,"Data\\Sound\\m���̽����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+60,"Data\\Sound\\mIceQueen1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+61,"Data\\Sound\\mIceQueen2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+62,"Data\\Sound\\mIceQueenAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+63,"Data\\Sound\\mIceQueenAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+64,"Data\\Sound\\mIceQueenDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,60,61,62,63,64);
		Models[MODEL_MONSTER01+Type].BoneHead = 16;//����
		break;
	case 14:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+65,"Data\\Sound\\m�ϻ��ڰ���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+66,"Data\\Sound\\m�ϻ��ڰ���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+67,"Data\\Sound\\m�ϻ����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+65,"Data\\Sound\\mAssassinAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+66,"Data\\Sound\\mAssassinAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+67,"Data\\Sound\\mAssassinDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,-1,-1,65,66,67);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;//�ϻ���
	    b->Actions[MONSTER01_STOP2].PlaySpeed = 0.35f;
		break;
	case 12:
	case 13:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+68,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+69,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+70,"Data\\Sound\\m���ΰ���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+71,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+68,"Data\\Sound\\mYeti1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+69,"Data\\Sound\\mYeti2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+70,"Data\\Sound\\mYetiAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+71,"Data\\Sound\\mYetiDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+12,68,68,70,70,71);
		SetMonsterSound(MODEL_MONSTER01+13,68,69,70,70,71);
		Models[MODEL_MONSTER01+12].BoneHead = 20;//����
		Models[MODEL_MONSTER01+13].BoneHead = 20;//����
		break;
	case 19:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+72,"Data\\Sound\\m���1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+73,"Data\\Sound\\m���2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+74,"Data\\Sound\\m�������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+75,"Data\\Sound\\m�������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+76,"Data\\Sound\\m����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+72,"Data\\Sound\\mGoblin1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+73,"Data\\Sound\\mGoblin2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+74,"Data\\Sound\\mGoblinAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+75,"Data\\Sound\\mGoblinAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+76,"Data\\Sound\\mGoblinDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,72,73,74,75,76);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;//���
		break;
	case 20:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+77,"Data\\Sound\\m������1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+78,"Data\\Sound\\m������2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+79,"Data\\Sound\\m����������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+80,"Data\\Sound\\m����������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+81,"Data\\Sound\\m�������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+77,"Data\\Sound\\mScorpion1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+78,"Data\\Sound\\mScorpion2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+79,"Data\\Sound\\mScorpionAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+80,"Data\\Sound\\mScorpionAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+81,"Data\\Sound\\mScorpionDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,77,78,79,80,81);
		break;
	case 21:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+82,"Data\\Sound\\mǳ����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+83,"Data\\Sound\\mǳ���̰���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+84,"Data\\Sound\\mǳ�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+82,"Data\\Sound\\mBeetle1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+83,"Data\\Sound\\mBeetleAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+84,"Data\\Sound\\mBeetleDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,82,82,83,83,84);
		Models[MODEL_MONSTER01+Type].BoneHead = 5;//ǳ����
		break;
	case 22:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+85,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+86,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+87,"Data\\Sound\\m���Ͱ���1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+88,"Data\\Sound\\m���Ͱ���2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+89,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+85,"Data\\Sound\\mHunter1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+86,"Data\\Sound\\mHunter2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+87,"Data\\Sound\\mHunterAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+88,"Data\\Sound\\mHunterAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+89,"Data\\Sound\\mHunterDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,85,86,87,88,89);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;//����
		break;
	case 23:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+90,"Data\\Sound\\m���Ǳ���1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+91,"Data\\Sound\\m���Ǳ���2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+92,"Data\\Sound\\m���Ǳ�������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+93,"Data\\Sound\\m���Ǳ�������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+94,"Data\\Sound\\m���Ǳ����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+90,"Data\\Sound\\mWoodMon1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+91,"Data\\Sound\\mWoodMon2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+92,"Data\\Sound\\mWoodMonAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+93,"Data\\Sound\\mWoodMonAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+94,"Data\\Sound\\mWoodMonDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,90,91,92,93,94);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;//����
		break;
	case 24:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+95,"Data\\Sound\\m�ư�1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+96,"Data\\Sound\\m�ư�2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+97,"Data\\Sound\\m�ư����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+98,"Data\\Sound\\m�ư����2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+99,"Data\\Sound\\m�ư��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+95,"Data\\Sound\\mArgon1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+96,"Data\\Sound\\mArgon2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+97,"Data\\Sound\\mArgonAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+98,"Data\\Sound\\mArgonAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+99,"Data\\Sound\\mArgonDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,95,96,97,98,99);
		Models[MODEL_MONSTER01+Type].BoneHead = 16;//ö��
		break;
	case 25:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+100,"Data\\Sound\\m������1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+101,"Data\\Sound\\m������2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+102,"Data\\Sound\\m����������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+103,"Data\\Sound\\m����������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+104,"Data\\Sound\\m�������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+100,"Data\\Sound\\mGolem1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+101,"Data\\Sound\\mGolem2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+102,"Data\\Sound\\mGolemAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+103,"Data\\Sound\\mGolemAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+104,"Data\\Sound\\mGolemDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,100,101,102,103,104);
		Models[MODEL_MONSTER01+Type].BoneHead = 5;//��
		break;
	case 26:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+105,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+106,"Data\\Sound\\m��ź����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+107,"Data\\Sound\\m�����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+105,"Data\\Sound\\mYeti1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+106,"Data\\Sound\\mSatanAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+107,"Data\\Sound\\mYetiDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,105,105,106,106,107);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;//����
		break;
	case 27:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+108,"Data\\Sound\\m�߷�1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+109,"Data\\Sound\\m�߷�2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+110,"Data\\Sound\\m���������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+111,"Data\\Sound\\m���հ���2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+112,"Data\\Sound\\m�߷��ױ�.wav"   ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+108,"Data\\Sound\\mBalrog1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+109,"Data\\Sound\\mBalrog2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+110,"Data\\Sound\\mWizardAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+111,"Data\\Sound\\mGorgonAttack2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+112,"Data\\Sound\\mBalrogDie.wav"   ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,108,109,110,111,112);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;//�߷�
		Models[MODEL_MONSTER01+Type].StreamMesh = 1;
		break;
	case 28:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+113,"Data\\Sound\\m������1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+114,"Data\\Sound\\m������2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+115,"Data\\Sound\\m���������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+116,"Data\\Sound\\m���������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+117,"Data\\Sound\\m�������ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+113,"Data\\Sound\\mShadow1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+114,"Data\\Sound\\mShadow2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+115,"Data\\Sound\\mShadowAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+116,"Data\\Sound\\mShadowAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+117,"Data\\Sound\\mShadowDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,113,114,115,116,117);
		Models[MODEL_MONSTER01+Type].BoneHead = 5;//������
		break;
	case 31:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+123,"Data\\Sound\\m����1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+124,"Data\\Sound\\m�һ԰���1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+125,"Data\\Sound\\m�����ױ�.wav"   ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+123,"Data\\Sound\\mYeti1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+124,"Data\\Sound\\mBullAttack1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+125,"Data\\Sound\\mYetiDie.wav"   ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,123,123,124,124,125);//�巡��
		b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.5f;
		b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.7f;
		b->Actions[MONSTER01_STOP2  ].PlaySpeed = 0.8f;
		b->Actions[MONSTER01_DIE+1  ].PlaySpeed = 0.8f;
		break;
	case 32:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+126,"Data\\Sound\\m�߸�1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+127,"Data\\Sound\\m�߸�2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+128,"Data\\Sound\\m�߸�����1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+129,"Data\\Sound\\m�߸�����2.wav",Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+126,"Data\\Sound\\mBali1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+127,"Data\\Sound\\mBali2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+128,"Data\\Sound\\mBaliAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+129,"Data\\Sound\\mBaliAttack2.wav",Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,126,127,128,129,127);
		b->Actions[MONSTER01_ATTACK3].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_ATTACK4].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_APEAR  ].PlaySpeed = 0.4f;
		b->Actions[MONSTER01_RUN    ].PlaySpeed = 0.4f;
		b->BoneHead = 6;//�߸�
		break;

	case 33:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+130,"Data\\Sound\\m���Ϲ�Ʈ1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+131,"Data\\Sound\\m����1.wav"    ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+130,"Data\\Sound\\mBahamut1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+131,"Data\\Sound\\mYeti1.wav"    ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,130,130,131,131,130);//�����
		break;
	case 34:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+132,"Data\\Sound\\m���ĸ�1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+133,"Data\\Sound\\m���ĸ�2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+134,"Data\\Sound\\m�߷�1.wav"    ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+132,"Data\\Sound\\mBepar1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+133,"Data\\Sound\\mBepar2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+134,"Data\\Sound\\mBalrog1.wav"    ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,132,133,104,104,133);
        b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.5f;
        b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.5f;
		b->BoneHead = 20;//�ξ�
		break;
	case 35:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+135,"Data\\Sound\\m��Ű��1.wav"   ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+136,"Data\\Sound\\m�߸�����2.wav" ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+137,"Data\\Sound\\m��Ű���ױ�.wav",Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+135,"Data\\Sound\\mValkyrie1.wav"   ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+136,"Data\\Sound\\mBaliAttack2.wav" ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+137,"Data\\Sound\\mValkyrieDie.wav",Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,135,135,136,136,137);
		Models[MODEL_MONSTER01+Type].BoneHead = 19;//��Ű��
		break;
	case 36://���ڵ�ŷ
	case 40://����
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+138,"Data\\Sound\\m���ڵ�ŷ1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+139,"Data\\Sound\\m���ڵ�ŷ2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+140,"Data\\Sound\\m�����ױ�.wav"   ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+138,"Data\\Sound\\mLizardKing1.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+139,"Data\\Sound\\mLizardKing2.wav"  ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+140,"Data\\Sound\\mGorgonDie.wav"   ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,138,139,138,139,140);
		if(Type==36)
			Models[MODEL_MONSTER01+Type].BoneHead = 19;//���ڵ�ŷ
		else
			Models[MODEL_MONSTER01+Type].BoneHead = 6;//����
		break;
	case 37:
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+141,"Data\\Sound\\m�����1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+142,"Data\\Sound\\m��������1.wav",Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+141,"Data\\Sound\\mHydra1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+142,"Data\\Sound\\mHydraAttack1.wav",Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,141,141,142,142,141);
        b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.15f;
        b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.15f;
        b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.2f;
		break;
	case 41://���̾���
		LoadWaveFile(SOUND_MONSTER+143,"Data\\Sound\\iron1.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+144,"Data\\Sound\\iron_attack1.wav",Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,143,143,144,144,144);
		Models[MODEL_MONSTER01+Type].BoneHead = 3;
		break;
	case 42://źŸ�ν�
		LoadWaveFile(SOUND_MONSTER+145,"Data\\Sound\\jaikan1.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+146,"Data\\Sound\\jaikan2.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+147,"Data\\Sound\\jaikan_attack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+148,"Data\\Sound\\jaikan_attack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+149,"Data\\Sound\\jaikan_die.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,145,146,147,148,149);
		LoadBitmap("Monster\\bv01_2.jpg"     ,BITMAP_MONSTER_SKIN    ,GL_LINEAR,GL_REPEAT);
		LoadBitmap("Monster\\bv02_2.jpg"     ,BITMAP_MONSTER_SKIN+1  ,GL_LINEAR,GL_REPEAT);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;
		break;
	case 43://�������
		LoadWaveFile(SOUND_MONSTER+150,"Data\\Sound\\blood1.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+151,"Data\\Sound\\blood_attack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+152,"Data\\Sound\\blood_attack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+153,"Data\\Sound\\blood_die.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,150,150,151,152,153);
		Models[MODEL_MONSTER01+Type].BoneHead = 7;
		break;
	case 44://������Ʈ
		LoadWaveFile(SOUND_MONSTER+154,"Data\\Sound\\death1.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+155,"Data\\Sound\\death_attack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+156,"Data\\Sound\\death_die.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,154,154,155,155,156);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;
		break;
	case 45://����Ʈ
		LoadWaveFile(SOUND_MONSTER+157,"Data\\Sound\\mutant1.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+158,"Data\\Sound\\mutant2.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+159,"Data\\Sound\\mutant_attack1.wav",Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,157,158,159,159,159);
		Models[MODEL_MONSTER01+Type].BoneHead = 6;
		break;
	case 46://��ũ�ü�
		LoadWaveFile(SOUND_MONSTER+162,"Data\\Sound\\mOrcArcherAttack1.wav"    ,Channel,Enable);
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\m�һ��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\mBullDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type, -1, -1, 162, 162,4);
		Models[MODEL_MONSTER01+Type].BoneHead = 7;
		break;
	case 47://��ũ����
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+86,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\m�һ��ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+86,"Data\\Sound\\mHunter2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\mBullDie.wav" ,Channel,Enable);
#endif
		LoadWaveFile(SOUND_MONSTER+161,"Data\\Sound\\mOrcCapAttack1.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,86,86,161,161,4);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;
		break;
	case 48://���ֹ��� ��
		LoadWaveFile(SOUND_MONSTER+160,"Data\\Sound\\mCursedKing1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+164,"Data\\Sound\\mCursedKing2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+163,"Data\\Sound\\mCursedKingDie1.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,160,164,-1,-1,163);
		Models[MODEL_MONSTER01+Type].BoneHead = 20;
		break;
	case 52://�ߴ���
		LoadBitmap("Monster\\iui02.tga",BITMAP_ROBE+3);
		LoadBitmap("Monster\\iui03.tga",BITMAP_ROBE+5);
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		LoadWaveFile(SOUND_MONSTER+180,"Data\\Sound\\mMegaCrust1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+181,"Data\\Sound\\mMegaCrustAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+182,"Data\\Sound\\mMegaCrustDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,180,180,181,181,182);
		break;
	case 49://���б���
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		LoadWaveFile(SOUND_MONSTER+177,"Data\\Sound\\mMolt1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+178,"Data\\Sound\\mMoltAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+179,"Data\\Sound\\mMoltDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,177,177,178,178,179);
		break;
	case 50://���ڸ�
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		//LoadWaveFile(SOUND_MONSTER+174,"Data\\Sound\\mAlquamos1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+175,"Data\\Sound\\mAlquamosAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+176,"Data\\Sound\\mAlquamosDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,175,175,175,175,176);
		break;
	case 51://���ǿ���
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		LoadWaveFile(SOUND_MONSTER+171,"Data\\Sound\\mRainner1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+172,"Data\\Sound\\mRainnerAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+173,"Data\\Sound\\mRainnerDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,171,-1,172,172,173);
		break;
	case 53://��ī�罺
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		LoadWaveFile(SOUND_MONSTER+168,"Data\\Sound\\mPhantom1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+169,"Data\\Sound\\mPhantomAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+170,"Data\\Sound\\mPhantomDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,168,168,169,169,170);
		break;
	case 54://���
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		LoadWaveFile(SOUND_MONSTER+165,"Data\\Sound\\mDrakan1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+166,"Data\\Sound\\mDrakanAttack1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+167,"Data\\Sound\\mDrakanDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,165,165,166,166,167);
		break;
	case 55://�һ���
		LoadWaveFile(SOUND_MONSTER+183,"Data\\Sound\\mPhoenix1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+184,"Data\\Sound\\mPhoenix1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+185,"Data\\Sound\\mPhoenixAttack1.wav"    ,Channel,Enable);
		//LoadWaveFile(SOUND_MONSTER+186,"Data\\Sound\\mDarkPhoenixDie.wav"    ,Channel,Enable);
		SetMonsterSound(MODEL_MONSTER01+Type,183,184,185,185,-1);
	case 56://�һ��� Ÿ�� ����
		b->Actions[MONSTER01_DIE    ].PlaySpeed = 0.22f;
		//b->Actions[MONSTER01_ATTACK1].PlaySpeed = 0.01f;
		//b->Actions[MONSTER01_ATTACK2].PlaySpeed = 0.01f;
		break;
    case 62:    //  �����ذ�.
		LoadWaveFile(SOUND_MONSTER+186,"Data\\Sound\\mMagicSkull.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+187,"Data\\Sound\\mMagicSkull.wav"    ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,186,-1,-1,-1,187);
        break;  
    case 61:    //  ����.
        break;
    case 60:    //  ����.
        break;
    case 59:    //  ���ذ�����.
		LoadWaveFile(SOUND_MONSTER+4,"Data\\Sound\\mBullDie.wav" ,Channel,Enable);
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+188,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+188,"Data\\Sound\\mHunter2.wav"    ,Channel,Enable);
#endif
		LoadWaveFile(SOUND_MONSTER+189,"Data\\Sound\\mBlackSkullDie.wav" ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+190,"Data\\Sound\\mBlackSkullAttack.wav"    ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,188, -1, 190, -1, 189 );
        break;
    case 58:    //  ���̾�Ʈ����.
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+188,"Data\\Sound\\m����2.wav"    ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+188,"Data\\Sound\\mHunter2.wav"    ,Channel,Enable);
#endif
		LoadWaveFile(SOUND_MONSTER+191,"Data\\Sound\\mGhaintOrgerDie.wav" ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,188, -1, 190, -1, 191 );
        break;
    case 57:    //  �����ذ�����.
		LoadWaveFile(SOUND_MONSTER+192,"Data\\Sound\\mRedSkull.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+193,"Data\\Sound\\mRedSkullDie.wav" ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+194,"Data\\Sound\\mRedSkullAttack.wav"    ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,192, -1, 194, -1, 193 );
        break;

    case 63 :   //  �ź��� ( Death Angel )
		LoadWaveFile(SOUND_MONSTER+195,"Data\\Sound\\mDAngelIdle.wav"   ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+196,"Data\\Sound\\mDAngelAttack.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+197,"Data\\Sound\\mDAngelDeath.wav"  ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,195, 195, 196, 196, 197 );
        break;

    case 64 :   //  ����� ȯ��.
		LoadWaveFile(SOUND_MONSTER+232,"Data\\Sound\\mKundunIdle.wav"       ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+233,"Data\\Sound\\mKundunAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+234,"Data\\Sound\\mKundunAttack2.wav"	,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,232, 232, 233, 234, -1 );
        break;

	case 65 :	//  ������ ( Bloody Soldier ).
		LoadWaveFile(SOUND_MONSTER+198,"Data\\Sound\\mBSoldierIdle1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+199,"Data\\Sound\\mBSoldierIdle2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+200,"Data\\Sound\\mBSoldierAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+201,"Data\\Sound\\mBSoldierAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+202,"Data\\Sound\\mBSoldierDeath.wav"    ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,198, 199, 200, 201, 202 );
		break;

	case 66 :	//  ������ ( �̽ý� )
		LoadWaveFile(SOUND_MONSTER+203,"Data\\Sound\\mEsisIdle.wav"     ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+204,"Data\\Sound\\mEsisAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+205,"Data\\Sound\\mEsisAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+206,"Data\\Sound\\mEsisDeath.wav"    ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,203, 203, 204, 205, 206 );
		break;

    case 67 :   //  ��糪��Ʈ ( ���� ���򸮿�, �ε� ���򸮿� )
		LoadWaveFile(SOUND_MONSTER+207,"Data\\Sound\\mDsIdle1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+208,"Data\\Sound\\mDsIdle2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+209,"Data\\Sound\\mDsAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+210,"Data\\Sound\\mDsAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+211,"Data\\Sound\\mDsDeath.wav"      ,Channel,Enable);

        //  �ε弾�򸮿�.
		LoadWaveFile(SOUND_MONSTER+212,"Data\\Sound\\mLsIdle1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+213,"Data\\Sound\\mLsIdle2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+214,"Data\\Sound\\mLsAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+215,"Data\\Sound\\mLsAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+216,"Data\\Sound\\mLsDeath.wav"      ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,207, 208, 209, 210, 211, 212, 213, 214, 215, 216 );
        break;

    case 68 :   //  ��ũ��.
		LoadWaveFile(SOUND_MONSTER+217,"Data\\Sound\\mNecronIdle1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+218,"Data\\Sound\\mNecronIdle2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+219,"Data\\Sound\\mNecronAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+220,"Data\\Sound\\mNecronAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+221,"Data\\Sound\\mNecronDeath.wav"      ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,217, 218, 219, 220, 221 );
        break;

    case 69 :   //  ��� �ĺ���.
		LoadWaveFile(SOUND_MONSTER+222,"Data\\Sound\\mSvIdle1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+223,"Data\\Sound\\mSvIdle2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+224,"Data\\Sound\\mSvAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+225,"Data\\Sound\\mSvAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+226,"Data\\Sound\\mSvDeath.wav"      ,Channel,Enable);

        //  �ε弾�򸮿�.
		LoadWaveFile(SOUND_MONSTER+227,"Data\\Sound\\mLvIdle1.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+228,"Data\\Sound\\mLvIdle2.wav"      ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+229,"Data\\Sound\\mLvAttack1.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+230,"Data\\Sound\\mLvAttack2.wav"	,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+231,"Data\\Sound\\mLvDeath.wav"      ,Channel,Enable);
        //  �⺻, �⺻, ����1, ����2, �ױ�.
		SetMonsterSound(MODEL_MONSTER01+Type,222, 223, 224, 225, 226, 227, 228, 229, 230, 231 );
        break;

    case 73:   //  ����.
        LoadWaveFile ( SOUND_MONSTER+232, "Data\\Sound\\BattleCastle\\oCDoorDis.wav",    Channel, Enable );
		SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, -1, -1, 232 );
        break;

    case 86:   //  ������ ����.
		SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, -1, -1, -1 );
	    b->Actions[MONSTER01_STOP1].PlaySpeed = 0.05f;
	    b->Actions[MONSTER01_STOP2].PlaySpeed = 0.05f;
	    b->Actions[MONSTER01_WALK].PlaySpeed = 0.1f;
        break;

    case 76:   //  �ü� ���.
        LoadWaveFile ( SOUND_MONSTER+233, "Data\\Sound\\BattleCastle\\m_BowMercAttack.wav",    Channel, Enable );
        LoadWaveFile ( SOUND_MONSTER+234, "Data\\Sound\\BattleCastle\\m_BowMercDeath.wav",    Channel, Enable );
        SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, 233, 233, 234 );
        break;

    case 77:   //  â ���.
        LoadWaveFile ( SOUND_MONSTER+235, "Data\\Sound\\BattleCastle\\m_SpearMercAttack.wav",    Channel, Enable );
        LoadWaveFile ( SOUND_MONSTER+236, "Data\\Sound\\BattleCastle\\m_SpearMercDeath.wav",    Channel, Enable );
        SetMonsterSound ( MODEL_MONSTER01+Type, -1, -1, 235, 235, 236 );
        break;

    case 79:
        break;
	case 128:	// �Ⱬ�� �䳢
		LoadWaveFile ( SOUND_ELBELAND_RABBITSTRANGE_ATTACK01,		"Data\\Sound\\w52\\SE_Mon_rabbitstrange_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_RABBITSTRANGE_DEATH01,		"Data\\Sound\\w52\\SE_Mon_rabbitstrange_death01.wav", 1 );
		break;
	case 129:	// ������ �䳢
		LoadWaveFile ( SOUND_ELBELAND_RABBITUGLY_BREATH01,			"Data\\Sound\\w52\\SE_Mon_rabbitugly_breath01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_RABBITUGLY_ATTACK01,			"Data\\Sound\\w52\\SE_Mon_rabbitugly_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_RABBITUGLY_DEATH01,			"Data\\Sound\\w52\\SE_Mon_rabbitugly_death01.wav", 1 );
		break;
	case 130:	// �����ΰ�
		LoadWaveFile ( SOUND_ELBELAND_WOLFHUMAN_MOVE02,				"Data\\Sound\\w52\\SE_Mon_wolfhuman_move02.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_WOLFHUMAN_ATTACK01,			"Data\\Sound\\w52\\SE_Mon_wolfhuman_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_WOLFHUMAN_DEATH01,			"Data\\Sound\\w52\\SE_Mon_wolfhuman_death01.wav", 1 );
		break;
	case 131:	// ������ ����
		LoadWaveFile ( SOUND_ELBELAND_BUTTERFLYPOLLUTION_MOVE01,	"Data\\Sound\\w52\\SE_Mon_butterflypollution_move01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_BUTTERFLYPOLLUTION_DEATH01,	"Data\\Sound\\w52\\SE_Mon_butterflypollution_death01.wav", 1 );
		break;
	case 132:	// ���ֹ�����ġ
		LoadWaveFile ( SOUND_ELBELAND_CURSERICH_MOVE01,				"Data\\Sound\\w52\\SE_Mon_curserich_move01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_CURSERICH_ATTACK01,			"Data\\Sound\\w52\\SE_Mon_curserich_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_CURSERICH_DEATH01,			"Data\\Sound\\w52\\SE_Mon_curserich_death01.wav", 1 );
		break;
	case 133:	// ���۰�
		LoadWaveFile ( SOUND_ELBELAND_TOTEMGOLEM_MOVE01,			"Data\\Sound\\w52\\SE_Mon_totemgolem_move01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_TOTEMGOLEM_MOVE02,			"Data\\Sound\\w52\\SE_Mon_totemgolem_move02.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_TOTEMGOLEM_ATTACK01,			"Data\\Sound\\w52\\SE_Mon_totemgolem_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_TOTEMGOLEM_ATTACK02,			"Data\\Sound\\w52\\SE_Mon_totemgolem_attack02.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_TOTEMGOLEM_DEATH01,			"Data\\Sound\\w52\\SE_Mon_totemgolem_death01.wav", 1 );
		break;
	case 134:	// ���� �쾾
 		LoadWaveFile ( SOUND_ELBELAND_BEASTWOO_MOVE01,				"Data\\Sound\\w52\\SE_Mon_beastwoo_move01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_BEASTWOO_ATTACK01,			"Data\\Sound\\w52\\SE_Mon_beastwoo_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_BEASTWOO_DEATH01,				"Data\\Sound\\w52\\SE_Mon_beastwoo_death01.wav", 1 );
		break;
	case 135:	// ���� �쾾 ����
 		LoadWaveFile ( SOUND_ELBELAND_BEASTWOOLEADER_MOVE01,		"Data\\Sound\\w52\\SE_Mon_beastwooleader_move01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_BEASTWOOLEADER_ATTACK01,		"Data\\Sound\\w52\\SE_Mon_beastwooleader_attack01.wav", 1 );
		LoadWaveFile ( SOUND_ELBELAND_BEASTWOO_DEATH01,				"Data\\Sound\\w52\\SE_Mon_beastwoo_death01.wav", 1 );
		break;
	case 136:	// ����-�촩��
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_UNUS_ATTACK01,		"Data\\Sound\\w57\\Sapi-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_DEATH01,				"Data\\Sound\\w57\\Sapi-Death.wav", 1 );
		break;
	case 137:	// ����-�ο�
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_UNUS_ATTACK01,		"Data\\Sound\\w57\\Sapi-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_DEATH01,				"Data\\Sound\\w57\\Sapi-Death.wav", 1 );
		break;
	case 138:	// ����-Ʈ����
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_TRES_ATTACK01,		"Data\\Sound\\w57\\Sapi-Attack1.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SAPI_DEATH01,				"Data\\Sound\\w57\\Sapi-Death.wav", 1 );
		break;
	case 139:	// ������ ��
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_PAWN_ATTACK01,		"Data\\Sound\\w57\\ShadowPawn-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_DEATH01,			"Data\\Sound\\w57\\Shadow-Death.wav", 1 );
		break;
	case 140:	// ������ ����Ʈ
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_KNIGHT_ATTACK01,	"Data\\Sound\\w57\\ShadowKnight-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_DEATH01,			"Data\\Sound\\w57\\Shadow-Death.wav", 1 );
		break;
	case 141:	// ������ ��
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_ROOK_ATTACK01,		"Data\\Sound\\w57\\ShadowRook-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_SHADOW_DEATH01,			"Data\\Sound\\w57\\Shadow-Death.wav", 1 );
		break;
	case 142:	// ��� ������
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_THUNDER_NAIPIN_BREATH01,	"Data\\Sound\\w57\\Naipin-Thunder.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01,			"Data\\Sound\\w57\\Naipin-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_DEATH01,			"Data\\Sound\\w57\\Naipin-Death.wav", 1 );
		break;
	case 143:	// ��Ʈ ������
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_GHOST_NAIPIN_BREATH01,	"Data\\Sound\\w57\\Naipin-Ghost.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01,			"Data\\Sound\\w57\\Naipin-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_DEATH01,			"Data\\Sound\\w57\\Naipin-Death.wav", 1 );
		break;
	case 144:	// ������ ������
 		LoadWaveFile ( SOUND_SWAMPOFQUIET_BLAZE_NAIPIN_BREATH01,	"Data\\Sound\\w57\\Naipin-Blaze.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_ATTACK01,			"Data\\Sound\\w57\\Naipin-Attack.wav", 1 );
		LoadWaveFile ( SOUND_SWAMPOFQUIET_NAIPIN_DEATH01,			"Data\\Sound\\w57\\Naipin-Death.wav", 1 );
		break;
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	case 145:
		LoadWaveFile( SOUND_ELBELAND_WOLFHUMAN_DEATH01,		"Data\\Sound\\w52\\SE_Mon_wolfhuman_death01.wav", 1 );
		LoadWaveFile( SOUND_RAKLION_ICEWALKER_ATTACK,		"Data\\Sound\\w58w59\\IceWalker_attack.wav", 1 );
		LoadWaveFile( SOUND_RAKLION_ICEWALKER_MOVE,			"Data\\Sound\\w58w59\\IceWalker_move.wav", 1 );
		break;
#endif //LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef PJH_GIANT_MAMUD
#ifdef PBG_FIX_NOTSOUNDLOAD_GIANTMAMUD
	case 146:
		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_MOVE,		"Data\\Sound\\w58w59\\GiantMammoth_move.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_ATTACK,	"Data\\Sound\\w58w59\\GiantMammoth_attack.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_DEATH,		"Data\\Sound\\w58w59\\GiantMammoth_death.wav", 1 );
		break;
#else //PBG_FIX_NOTSOUNDLOAD_GIANTMAMUD
 		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_MOVE,	"Data\\Sound\\w57\\GiantMammoth_move.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_ATTACK,			"Data\\Sound\\w57\\GiantMammoth_attack.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_GIANT_MAMUD_DEATH,			"Data\\Sound\\w57\\GiantMammoth_death.wav", 1 );
#endif //PBG_FIX_NOTSOUNDLOAD_GIANTMAMUD
#endif //PJH_GIANT_MAMUD
#ifdef ADD_RAKLION_MOB_ICEGIANT
	case 147:
		LoadWaveFile ( SOUND_RAKLION_ICEGIANT_MOVE,			"Data\\Sound\\w58w59\\IceGiant_move.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_ICEGIANT_DEATH,		"Data\\Sound\\w58w59\\IceGiant_death.wav", 1 );
		break;
#endif	// ADD_RAKLION_MOB_ICEGIANT
#ifdef LDS_RAKLION_ADDMONSTER_COOLERTIN
	case 148:
		LoadWaveFile( SOUND_MONSTER+34,						"Data\\Sound\\m�ｺ���̴��ױ�.wav" ,1);
		LoadWaveFile( SOUND_RAKLION_COOLERTIN_ATTACK,		"Data\\Sound\\w58w59\\Coolertin_attack.wav", 1 );
		LoadWaveFile( SOUND_RAKLION_COOLERTIN_MOVE,			"Data\\Sound\\w58w59\\Coolertin_move.wav", 1 );
		break;
#endif //LDS_RAKLION_ADDMONSTER_COOLERTIN
#ifdef ADD_RAKLION_IRON_KNIGHT
	case 149:
		LoadWaveFile ( SOUND_RAKLION_IRON_KNIGHT_MOVE,			"Data\\Sound\\w58w59\\IronKnight_move.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_IRON_KNIGHT_ATTACK,		"Data\\Sound\\w58w59\\IronKnight_attack.wav", 1 );
		LoadWaveFile ( SOUND_MONSTER+154,						"Data\\Sound\\death1.wav", 1 );
		break;
#endif	// ADD_RAKLION_IRON_KNIGHT
#ifdef CSK_RAKLION_BOSS
	case 150:	// ������ (��������)
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_ATTACK1,		"Data\\Sound\\w58w59\\Selupan_attack1.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_ATTACK2,		"Data\\Sound\\w58w59\\Selupan_attack2.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_CURE,			"Data\\Sound\\w58w59\\Selupan_cure.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_RAGE,			"Data\\Sound\\w58w59\\Selupan_rage.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_WORD1,			"Data\\Sound\\w58w59\\Selupan_word1.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_WORD2,			"Data\\Sound\\w58w59\\Selupan_word2.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_WORD3,			"Data\\Sound\\w58w59\\Selupan_word3.wav", 1 );
		LoadWaveFile ( SOUND_RAKLION_SERUFAN_WORD4,			"Data\\Sound\\w58w59\\Selupan_word4.wav", 1 );
		break;
#endif // CSK_RAKLION_BOSS
#ifdef YDG_ADD_SANTA_MONSTER
	case 155:	// ���ֹ��� ��Ÿ
		LoadWaveFile(SOUND_XMAS_SANTA_IDLE_1, "Data\\Sound\\xmas\\DarkSanta_Idle01.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_IDLE_2, "Data\\Sound\\xmas\\DarkSanta_Idle02.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_WALK_1, "Data\\Sound\\xmas\\DarkSanta_Walk01.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_WALK_2, "Data\\Sound\\xmas\\DarkSanta_Walk02.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_ATTACK_1, "Data\\Sound\\xmas\\DarkSanta_Attack01.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_DAMAGE_1, "Data\\Sound\\xmas\\DarkSanta_Damage01.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_DAMAGE_2, "Data\\Sound\\xmas\\DarkSanta_Damage02.wav");
		LoadWaveFile(SOUND_XMAS_SANTA_DEATH_1, "Data\\Sound\\xmas\\DarkSanta_Death01.wav");
		break;
	case 156:	// ���ֹ��� ���
#ifdef KOREAN_WAV_USE
		LoadWaveFile(SOUND_MONSTER+72,"Data\\Sound\\m���1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+73,"Data\\Sound\\m���2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+74,"Data\\Sound\\m�������1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+75,"Data\\Sound\\m�������2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+76,"Data\\Sound\\m����ױ�.wav" ,Channel,Enable);
#else
		LoadWaveFile(SOUND_MONSTER+72,"Data\\Sound\\mGoblin1.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+73,"Data\\Sound\\mGoblin2.wav"    ,Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+74,"Data\\Sound\\mGoblinAttack1.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+75,"Data\\Sound\\mGoblinAttack2.wav",Channel,Enable);
		LoadWaveFile(SOUND_MONSTER+76,"Data\\Sound\\mGoblinDie.wav" ,Channel,Enable);
#endif
		SetMonsterSound(MODEL_MONSTER01+Type,72,73,74,75,76);
		break;
#endif	// YDG_ADD_SANTA_MONSTER
#ifdef PBG_ADD_PKFIELD
	case 157:	//��������
		{
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_ATTACK,"Data\\Sound\\w64\\ZombieWarrior_attack.wav");
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE01,"Data\\Sound\\w64\\ZombieWarrior_damage01.wav");
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_DAMAGE02,"Data\\Sound\\w64\\ZombieWarrior_damage02.wav");
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_DEATH,"Data\\Sound\\w64\\ZombieWarrior_death.wav");
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE01,"Data\\Sound\\w64\\ZombieWarrior_move01.wav");
			LoadWaveFile(SOUND_PKFIELD_ZOMBIEWARRIOR_MOVE02,"Data\\Sound\\w64\\ZombieWarrior_move02.wav");
		}
		break;
	case 158:	//�ǻ�Ƴ� ������
		{
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_ATTACK,"Data\\Sound\\w64\\RaisedGladiator_attack.wav");
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE01,"Data\\Sound\\w64\\RaisedGladiator_damage01.wav");
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_DAMAGE02,"Data\\Sound\\w64\\RaisedGladiator_damage02.wav");
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_DEATH,"Data\\Sound\\w64\\RaisedGladiator_death.wav");
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_MOVE01,"Data\\Sound\\w64\\RaisedGladiator_move01.wav");
			LoadWaveFile(SOUND_PKFIELD_RAISEDGLADIATOR_MOVE02,"Data\\Sound\\w64\\RaisedGladiator_move02.wav");	
		}
		break;
	case 159:	//����� ������
		{
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_ATTACK,"Data\\Sound\\w64\\AshesButcher_attack.wav");
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_DAMAGE01,"Data\\Sound\\w64\\AshesButcher_damage01.wav");
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_DAMAGE02,"Data\\Sound\\w64\\AshesButcher_damage02.wav");
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_DEATH,"Data\\Sound\\w64\\AshesButcher_death.wav");
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_MOVE01,"Data\\Sound\\w64\\AshesButcher_move01.wav");
			LoadWaveFile(SOUND_PKFIELD_ASHESBUTCHER_MOVE02,"Data\\Sound\\w64\\AshesButcher_move02.wav");
		}
		break;
	case 160:	//���� �ϻ���
		{
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_ATTACK,"Data\\Sound\\w64\\BloodAssassin_attack.wav");
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_DAMAGE01,"Data\\Sound\\w64\\BloodAssassin_damage01.wav");
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_DAMAGE02,"Data\\Sound\\w64\\BloodAssassin_damage02.wav");
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_DEDTH,"Data\\Sound\\w64\\BloodAssassin_death.wav");
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_MOVE01,"Data\\Sound\\w64\\BloodAssassin_move01.wav");
			LoadWaveFile(SOUND_PKFIELD_BLOODASSASSIN_MOVE02,"Data\\Sound\\w64\\BloodAssassin_move02.wav");
		}
		break;
	case 162:	//��ϰ���
		{
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_ATTACK01,"Data\\Sound\\w64\\BurningLavaGolem_attack01.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_ATTACK02,"Data\\Sound\\w64\\BurningLavaGolem_attack02.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_DAMAGE01,"Data\\Sound\\w64\\BurningLavaGolem_damage01.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_DAMAGE02,"Data\\Sound\\w64\\BurningLavaGolem_damage02.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_DEATH,"Data\\Sound\\w64\\BurningLavaGolem_death.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_MOVE01,"Data\\Sound\\w64\\BurningLavaGolem_move01.wav");
			LoadWaveFile(SOUND_PKFIELD_BURNINGLAVAGOLEM_MOVE02,"Data\\Sound\\w64\\BurningLavaGolem_move02.wav");
		}
		break;
#endif //PBG_ADD_PKFIELD
#ifdef YDG_ADD_DOPPELGANGER_SOUND
	case 190:	// �г��� ������
		{
			LoadWaveFile(SOUND_DOPPELGANGER_RED_BUGBEAR_ATTACK,"Data\\Sound\\Doppelganger\\Angerbutcher_attack.wav");
			LoadWaveFile(SOUND_DOPPELGANGER_RED_BUGBEAR_DEATH,"Data\\Sound\\Doppelganger\\Angerbutcher_death.wav");
		}
		break;
	case 189:	// ������
		{
			LoadWaveFile(SOUND_DOPPELGANGER_BUGBEAR_ATTACK,"Data\\Sound\\Doppelganger\\Butcher_attack.wav");
			LoadWaveFile(SOUND_DOPPELGANGER_BUGBEAR_DEATH,"Data\\Sound\\Doppelganger\\Butcher_death.wav");
		}
		break;
	case 191:	// ���ð���
		{
			LoadWaveFile(SOUND_DOPPELGANGER_SLIME_ATTACK,"Data\\Sound\\Doppelganger\\Doppelganger_attack.wav");
			LoadWaveFile(SOUND_DOPPELGANGER_SLIME_DEATH,"Data\\Sound\\Doppelganger\\Doppelganger_death.wav");
		}
		break;
#endif	// YDG_ADD_DOPPELGANGER_SOUND
#ifdef ASG_ADD_KARUTAN_MONSTERS
	case 209:	// �͵�������
		LoadWaveFile(SOUND_KARUTAN_TCSCORPION_ATTACK, "Data\\Sound\\Karutan\\ToxyChainScorpion_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_TCSCORPION_DEATH, "Data\\Sound\\Karutan\\ToxyChainScorpion_death.wav");
		LoadWaveFile(SOUND_KARUTAN_TCSCORPION_HIT, "Data\\Sound\\Karutan\\ToxyChainScorpion_hit.wav");
		break;
	case 210:	// �������ǿ�
		LoadWaveFile(SOUND_KARUTAN_BONESCORPION_ATTACK, "Data\\Sound\\Karutan\\BoneScorpion_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_BONESCORPION_DEATH, "Data\\Sound\\Karutan\\BoneScorpion_death.wav");
		LoadWaveFile(SOUND_KARUTAN_BONESCORPION_HIT, "Data\\Sound\\Karutan\\BoneScorpion_hit.wav");
		break;
	case 211:	// ����Ŀ��
		LoadWaveFile(SOUND_KARUTAN_ORCUS_MOVE1, "Data\\Sound\\Karutan\\Orcus_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_ORCUS_MOVE2, "Data\\Sound\\Karutan\\Orcus_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_ORCUS_ATTACK1, "Data\\Sound\\Karutan\\Orcus_attack_1.wav");
		LoadWaveFile(SOUND_KARUTAN_ORCUS_ATTACK2, "Data\\Sound\\Karutan\\Orcus_attack_2.wav");
		LoadWaveFile(SOUND_KARUTAN_ORCUS_DEATH, "Data\\Sound\\Karutan\\Orcus_death.wav");
		break;
	case 212:	// ���
		LoadWaveFile(SOUND_KARUTAN_GOLOCH_MOVE1, "Data\\Sound\\Karutan\\Goloch_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_GOLOCH_MOVE2, "Data\\Sound\\Karutan\\Goloch_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_GOLOCH_ATTACK, "Data\\Sound\\Karutan\\Goloch_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_GOLOCH_DEATH, "Data\\Sound\\Karutan\\Goloch_death.wav");
		break;
	case 213:	// ũ��Ÿ
		LoadWaveFile(SOUND_KARUTAN_CRYPTA_MOVE1, "Data\\Sound\\Karutan\\Crypta_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPTA_MOVE2, "Data\\Sound\\Karutan\\Crypta_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPTA_ATTACK, "Data\\Sound\\Karutan\\Crypta_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPTA_DEATH, "Data\\Sound\\Karutan\\Crypta_death.wav");
		break;
	case 214:	// ũ������
		LoadWaveFile(SOUND_KARUTAN_CRYPOS_MOVE1, "Data\\Sound\\Karutan\\Crypos_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPOS_MOVE2, "Data\\Sound\\Karutan\\Crypos_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPOS_ATTACK1, "Data\\Sound\\Karutan\\Crypos_attack_1.wav");
		LoadWaveFile(SOUND_KARUTAN_CRYPOS_ATTACK2, "Data\\Sound\\Karutan\\Crypos_attack_2.wav");
		break;
	case 215:	// �ܵ��
		LoadWaveFile(SOUND_KARUTAN_CONDRA_MOVE1, "Data\\Sound\\Karutan\\Condra_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_CONDRA_MOVE2, "Data\\Sound\\Karutan\\Condra_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_CONDRA_ATTACK, "Data\\Sound\\Karutan\\Condra_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_CONDRA_DEATH, "Data\\Sound\\Karutan\\Condra_death.wav");
		break;
	case 216:	// �����ܵ��
		LoadWaveFile(SOUND_KARUTAN_CONDRA_MOVE1, "Data\\Sound\\Karutan\\Condra_move1.wav");
		LoadWaveFile(SOUND_KARUTAN_CONDRA_MOVE2, "Data\\Sound\\Karutan\\Condra_move2.wav");
		LoadWaveFile(SOUND_KARUTAN_NARCONDRA_ATTACK, "Data\\Sound\\Karutan\\NarCondra_attack.wav");
		LoadWaveFile(SOUND_KARUTAN_CONDRA_DEATH, "Data\\Sound\\Karutan\\Condra_death.wav");
		break;
#endif	// ASG_ADD_KARUTAN_MONSTERS
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���� ����Ÿ �о���̴� �Լ�(�׽�Ʈ�� ���� ����� �ε�)
///////////////////////////////////////////////////////////////////////////////

void OpenMonsterModels()
{

}

///////////////////////////////////////////////////////////////////////////////
// ����, ��ų ����Ÿ �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenSkills()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENSKILLS, PROFILING_LOADING_OPENSKILLS );
#endif // DO_PROFILING_FOR_LOADING

	AccessModel(MODEL_ICE      ,"Data\\Skill\\","Ice",1);
	AccessModel(MODEL_ICE_SMALL,"Data\\Skill\\","Ice",2);
	AccessModel(MODEL_FIRE     ,"Data\\Skill\\","Fire",1);
	AccessModel(MODEL_POISON   ,"Data\\Skill\\","Poison",1);
	for(int i=0;i<2;i++)
     	AccessModel(MODEL_STONE1+i ,"Data\\Skill\\","Stone",i+1);
	AccessModel(MODEL_CIRCLE   ,"Data\\Skill\\","Circle",1);
	AccessModel(MODEL_CIRCLE_LIGHT,"Data\\Skill\\","Circle",2);
	AccessModel(MODEL_MAGIC1   ,"Data\\Skill\\","Magic",1);
	AccessModel(MODEL_MAGIC2   ,"Data\\Skill\\","Magic",2);
	AccessModel(MODEL_STORM    ,"Data\\Skill\\","Storm",1);
	AccessModel(MODEL_LASER    ,"Data\\Skill\\","Laser",1);
#ifdef _VS2008PORTING
	for(int i=0;i<3;i++)
#else // _VS2008PORTING
	for(i=0;i<3;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SKELETON1+i,"Data\\Skill\\","Skeleton",i+1);

	// ����Ʈ �ذ����� �� ����Ÿ �ε� �ؽ��Ĵ� �ؿ��� �ڵ����� �ε��Ѵ�.
	AccessModel(MODEL_SKELETON_PCBANG, "Data\\Skill\\", "Skeleton", 3);
	// �ҷ��� �̺�Ʈ �� ������ �� ����Ÿ �ε� �ؽ��Ĵ� �ؿ��� �ڵ����� �ε��Ѵ�.
	AccessModel(MODEL_HALLOWEEN, "Data\\Skill\\", "Jack");

	AccessModel(MODEL_HALLOWEEN_CANDY_BLUE, "Data\\Skill\\", "hcandyblue");
	AccessModel(MODEL_HALLOWEEN_CANDY_ORANGE, "Data\\Skill\\", "hcandyorange");
	AccessModel(MODEL_HALLOWEEN_CANDY_RED, "Data\\Skill\\", "hcandyred");
	AccessModel(MODEL_HALLOWEEN_CANDY_YELLOW, "Data\\Skill\\", "hcandyyellow");
	AccessModel(MODEL_HALLOWEEN_CANDY_HOBAK, "Data\\Skill\\", "hhobak");
	AccessModel(MODEL_HALLOWEEN_CANDY_STAR, "Data\\Skill\\", "hstar");
	// �� ������ �� ���÷� �ؽ��� �ε�
	LoadBitmap("Skill\\jack04.jpg", BITMAP_JACK_1);
	LoadBitmap("Skill\\jack05.jpg", BITMAP_JACK_2);
	LoadBitmap("Monster\\iui02.tga",BITMAP_ROBE+3);
	// NPC�Ӹ� ȣ��
	AccessModel(MODEL_POTION+45, "Data\\Item\\", "hobakhead");
	OpenTexture(MODEL_POTION+45, "Item\\");

	AccessModel(MODEL_CURSEDTEMPLE_ALLIED_PLAYER, "Data\\Skill\\", "unitedsoldier");
	AccessModel(MODEL_CURSEDTEMPLE_ILLUSION_PLAYER, "Data\\Skill\\", "illusionist");

	AccessModel(MODEL_WOOSISTONE, "Data\\Skill\\", "woositone");
	OpenTexture(MODEL_WOOSISTONE, "Skill\\");
	
	// �� �̺�Ʈ ������Ʈ �ε�
	g_NewYearsDayEvent->LoadModel();

	AccessModel(MODEL_SAW      ,"Data\\Skill\\","Saw",1);
#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_BONE1+i,"Data\\Skill\\","Bone",i+1);
#ifdef _VS2008PORTING
	for(int i=0;i<3;i++)
#else // _VS2008PORTING
	for(i=0;i<3;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_SNOW1+i,"Data\\Skill\\","Snow",i+1);
	AccessModel(MODEL_UNICON       ,"Data\\Skill\\","Rider",1);
    AccessModel ( MODEL_PEGASUS, "Data\\Skill\\", "Rider", 2 );
    AccessModel ( MODEL_DARK_HORSE , "Data\\Skill\\", "DarkHorse" );
	
	//^ �渱 �� ����Ÿ �ε�(�� ����Ÿ, �ؽ���)
	AccessModel(MODEL_FENRIR_BLACK, "Data\\Skill\\", "fenril_black");
	OpenTexture(MODEL_FENRIR_BLACK, "Skill\\");

	AccessModel(MODEL_FENRIR_RED, "Data\\Skill\\", "fenril_red");
	OpenTexture(MODEL_FENRIR_RED, "Skill\\");

	AccessModel(MODEL_FENRIR_BLUE, "Data\\Skill\\", "fenril_blue");
	OpenTexture(MODEL_FENRIR_BLUE, "Skill\\");

	AccessModel(MODEL_FENRIR_GOLD, "Data\\Skill\\", "fenril_gold");
	OpenTexture(MODEL_FENRIR_BLUE, "Skill\\");

#ifdef PJH_ADD_PANDA_CHANGERING
	AccessModel(MODEL_PANDA,			"Data\\Item\\", "panda");
	OpenTexture(MODEL_PANDA,			"Item\\" );
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	AccessModel(MODEL_SKELETON_CHANGED,			"Data\\Item\\", "trans_skeleton");	// ���̷��� ���Ź���
	OpenTexture(MODEL_SKELETON_CHANGED,			"Item\\" );
#endif	// YDG_ADD_SKELETON_CHANGE_RING


#ifdef PET_SYSTEM
    AccessModel ( MODEL_DARK_SPIRIT, "Data\\Skill\\", "DarkSpirit" );

	LoadBitmap( "Skill\\dkthreebody_r.jpg" , BITMAP_MONSTER_SKIN+2, GL_LINEAR, GL_REPEAT );
    
#endif// PET_SYSTEM

#ifdef DARK_WOLF
    AccessModel ( MODEL_DARK_WOLF, "Data\\Skill\\", "DarkWolf" );
#endif// DARK_WOLF

    AccessModel ( MODEL_WARCRAFT,   "Data\\Skill\\", "HellGate" );
    Models[MODEL_WARCRAFT].Actions[0].LockPositions = false;
#ifdef YDG_FIX_MEMORY_LEAK_0905
	SAFE_DELETE_ARRAY(Models[MODEL_WARCRAFT].Actions[0].Positions);
#endif	// YDG_FIX_MEMORY_LEAK_0905
    Models[MODEL_WARCRAFT].Actions[0].PlaySpeed = 0.15f;

	AccessModel(MODEL_ARROW        ,"Data\\Skill\\","Arrow",1);
	AccessModel(MODEL_ARROW_STEEL  ,"Data\\Skill\\","ArrowSteel",1);
	AccessModel(MODEL_ARROW_THUNDER,"Data\\Skill\\","ArrowThunder",1);
	AccessModel(MODEL_ARROW_LASER  ,"Data\\Skill\\","ArrowLaser",1);
	AccessModel(MODEL_ARROW_V      ,"Data\\Skill\\","ArrowV",1);
	AccessModel(MODEL_ARROW_SAW    ,"Data\\Skill\\","ArrowSaw",1);
	AccessModel(MODEL_ARROW_NATURE ,"Data\\Skill\\","ArrowNature",1);

	OpenTexture(MODEL_MAGIC_CAPSULE2	,"Skill\\");
	AccessModel(MODEL_MAGIC_CAPSULE2    ,"Data\\Skill\\","Protect",2);

	AccessModel(MODEL_ARROW_SPARK ,"Data\\Skill\\","Arrow_Spark");
	OpenTexture(MODEL_ARROW_SPARK ,"Skill\\");

	AccessModel(MODEL_DARK_SCREAM ,"Data\\Skill\\","darkfirescrem02");
	OpenTexture(MODEL_DARK_SCREAM ,"Skill\\");
	AccessModel(MODEL_DARK_SCREAM_FIRE ,"Data\\Skill\\","darkfirescrem01");
	OpenTexture(MODEL_DARK_SCREAM_FIRE ,"Skill\\");
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	AccessModel(MODEL_SUMMON		,"Data\\SKill\\","nightmaresum");
	OpenTexture(MODEL_SUMMON		,"SKill\\");
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	AccessModel(MODEL_MULTI_SHOT1 ,"Data\\Effect\\","multishot01");
	OpenTexture(MODEL_MULTI_SHOT1 ,"Effect\\");
	AccessModel(MODEL_MULTI_SHOT2 ,"Data\\Effect\\","multishot02");
	OpenTexture(MODEL_MULTI_SHOT2 ,"Effect\\");
	AccessModel(MODEL_MULTI_SHOT3 ,"Data\\Effect\\","multishot03");
	OpenTexture(MODEL_MULTI_SHOT3 ,"Effect\\");
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	AccessModel(MODEL_DESAIR		,"Data\\SKill\\","desair");
	OpenTexture(MODEL_DESAIR		,"SKill\\");
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	AccessModel(MODEL_ARROW_RING ,"Data\\Skill\\","CW_Bow_Skill");
	OpenTexture(MODEL_ARROW_RING ,"Skill\\");
	
#ifdef ADD_SOCKET_ITEM
	AccessModel(MODEL_ARROW_DARKSTINGER, "Data\\Skill\\", "sketbows_arrows");
	OpenTexture(MODEL_ARROW_DARKSTINGER, "Skill\\");
	AccessModel(MODEL_FEATHER, "Data\\Skill\\", "darkwing_hetachi");
	OpenTexture(MODEL_FEATHER, "Skill\\");
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
	AccessModel(MODEL_FEATHER_FOREIGN, "Data\\Skill\\", "darkwing_hetachi");
	OpenTexture(MODEL_FEATHER_FOREIGN, "Skill\\");
#endif //LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
#ifdef PBG_ADD_PKFIELD
	LoadBitmap("Effect\\Bugbear_R.jpg", BITMAP_BUGBEAR_R, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\pk_mon02_fire.jpg", BITMAP_PKMON01, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\pk_mon03_red.jpg" , BITMAP_PKMON02, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\pk_mon02_green.jpg", BITMAP_PKMON03, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\pk_mon03_green.jpg", BITMAP_PKMON04, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\lavagiantAa_e.jpg", BITMAP_PKMON05, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\lavagiantBa_e.jpg", BITMAP_PKMON06, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\eff_magma_red.jpg", BITMAP_LAVAGIANT_FOOTPRINT_R, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\eff_magma_violet.jpg", BITMAP_LAVAGIANT_FOOTPRINT_V, GL_LINEAR, GL_CLAMP);
#endif //PBG_ADD_PKFIELD
#ifdef PBG_ADD_RAYMOND_GUARDIANPRIEST_MONSTER_EFFECT
	LoadBitmap("Effect\\raymond_sword_R.jpg", BITMAP_RAYMOND_SWORD, GL_LINEAR, GL_REPEAT);
#endif //PBG_ADD_RAYMOND_GUARDIANPRIEST_MONSTER_EFFECT
#ifdef PBG_ADD_AURA_EFFECT
	LoadBitmap("Effect\\mist01.jpg", BITMAP_AG_ADDITION_EFFECT, GL_LINEAR, GL_REPEAT);
#endif //PBG_ADD_AURA_EFFECT
#ifdef LDK_ADD_GAMBLERS_WEAPONS
	AccessModel(MODEL_ARROW_GAMBLE, "Data\\Skill\\", "gamble_arrows01");
	OpenTexture(MODEL_ARROW_GAMBLE, "Skill\\");
#endif //LDK_ADD_GAMBLERS_WEAPONS

	OpenTexture(MODEL_SPEARSKILL		,"Skill\\");
	AccessModel(MODEL_SPEARSKILL      ,"Data\\Skill\\","RidingSpear",1);
	AccessModel(MODEL_PROTECT      ,"Data\\Skill\\","Protect",1);

#ifdef _VS2008PORTING
	for(int i=0;i<2;i++)
#else // _VS2008PORTING
	for(i=0;i<2;i++)
#endif // _VS2008PORTING
      	AccessModel(MODEL_BIG_STONE1+i,"Data\\Skill\\","BigStone",i+1);
	AccessModel(MODEL_MAGIC_CIRCLE1,"Data\\Skill\\","MagicCircle",1);
	AccessModel(MODEL_ARROW_WING   ,"Data\\Skill\\","ArrowWing",1);
	AccessModel(MODEL_ARROW_BOMB   ,"Data\\Skill\\","ArrowBomb",1);
	AccessModel(MODEL_BALL         ,"Data\\Skill\\","Ball",1);//��
	Models[MODEL_BALL].Actions[0].PlaySpeed = 0.5f;
	AccessModel(MODEL_SKILL_BLAST  ,"Data\\Skill\\","Blast",1);
	AccessModel(MODEL_SKILL_INFERNO,"Data\\Skill\\","Inferno",1);
	AccessModel(MODEL_ARROW_DOUBLE ,"Data\\Skill\\","ArrowDouble",1);

	AccessModel(MODEL_ARROW_BEST_CROSSBOW, "Data\\Skill\\", "KCross" );	//	���� ����. ȭ��.
	AccessModel(MODEL_ARROW_DRILL, "Data\\Skill\\", "Carow" );			//	�� ���� ����. ȭ��.
	AccessModel(MODEL_COMBO		 , "Data\\Skill\\", "combo" );			//	�޺� ȿ��.

    AccessModel ( MODEL_GATE+0, "Data\\Object12\\", "Gate", 1 );
    AccessModel ( MODEL_GATE+1, "Data\\Object12\\", "Gate", 2 );
    AccessModel ( MODEL_STONE_COFFIN+0, "Data\\Object12\\", "StoneCoffin", 1 );
    AccessModel ( MODEL_STONE_COFFIN+1, "Data\\Object12\\", "StoneCoffin", 2 );

#ifdef _VS2008PORTING
    for ( int i=0; i<2; ++i )
#else // _VS2008PORTING
    for ( i=0; i<2; ++i )
#endif // _VS2008PORTING
    {
        OpenTexture ( MODEL_GATE+1, "Monster\\" );
        OpenTexture ( MODEL_STONE_COFFIN+i, "Monster\\" );
    }

	AccessModel ( MODEL_AIR_FORCE, "Data\\Skill\\", "AirForce" );       //  ���� ���� ȿ��.
	AccessModel ( MODEL_WAVES    , "Data\\Skill\\", "m_Waves" );		//	���� ȿ��.
	AccessModel ( MODEL_PIERCING2, "Data\\Skill\\", "m_Piercing" );	    //	��Ʈ�� �Ǿ� ��ǰ.
	AccessModel ( MODEL_PIER_PART, "Data\\Skill\\", "PierPart" );	    //	���Ǿ� ��ǰ.
	AccessModel ( MODEL_DARKLORD_SKILL, "Data\\Skill\\", "DarkLordSkill" ); //	��ũ�ε� ������ų.
	AccessModel ( MODEL_GROUND_STONE,   "Data\\Skill\\", "groundStone" );   //  ������ų.
    Models[MODEL_GROUND_STONE].Actions[0].Loop = false;
    AccessModel ( MODEL_GROUND_STONE2,  "Data\\Skill\\", "groundStone2" );  //  ������ų.
    Models[MODEL_GROUND_STONE2].Actions[0].Loop = false;
	AccessModel ( MODEL_WATER_WAVE,     "Data\\Skill\\", "seamanFX" );      //	���Ϳ��̺�.
	AccessModel ( MODEL_SKULL,          "Data\\Skill\\", "Skull" );         //	�ذ�.
	AccessModel ( MODEL_LACEARROW,		"Data\\Skill\\", "LaceArrow");		//	���̽����ο�
	OpenTexture ( MODEL_LACEARROW,      "Item\\", GL_CLAMP );  //	�ذ�.

#ifdef TAMAJJANG
    AccessModel( MODEL_TAMAJJANG, "Data\\Skill\\","Tama",1 );
#endif
    AccessModel ( MODEL_MANY_FLAG, "Data\\Skill\\", "ManyFlag" );       //  �߱� ��ؿ��� ����ϴ� ���.
    AccessModel ( MODEL_WEBZEN_MARK, "Data\\Skill\\", "MuSign" );       //  ������ũ.
	AccessModel ( MODEL_STUN_STONE,  "Data\\Skill\\", "GroundCrystal" );        //  ��������.
	AccessModel ( MODEL_SKIN_SHELL,  "Data\\Skill\\", "skinshell" );            //  ��Ų ����.
	AccessModel ( MODEL_MANA_RUNE,   "Data\\Skill\\", "ManaRune" );             //  ���� ��.
	AccessModel ( MODEL_SKILL_JAVELIN,  "Data\\Skill\\", "Javelin" );           //	ǥâ.
	AccessModel ( MODEL_ARROW_IMPACT,   "Data\\Skill\\", "ArrowImpact" );       //  ������ �ѹ�.
	AccessModel ( MODEL_SWORD_FORCE,    "Data\\Skill\\", "SwordForce" );        //  �˽�.

    AccessModel ( MODEL_FLY_BIG_STONE1,  "Data\\Skill\\", "FlyBigStone1" );     //  �����Ⱑ ������ �� ( ������ ).
    AccessModel ( MODEL_FLY_BIG_STONE2,  "Data\\Skill\\", "FlyBigStone2" );     //  �����Ⱑ ������ �� ( ������ ).
    AccessModel ( MODEL_BIG_STONE_PART1, "Data\\Skill\\", "FlySmallStone1" );   //  �����Ⱑ ������ �� ����1.
    AccessModel ( MODEL_BIG_STONE_PART2, "Data\\Skill\\", "FlySmallStone2" );   //  �����Ⱑ ������ �� ����2.
    AccessModel ( MODEL_WALL_PART1,      "Data\\Skill\\", "WallStone1" );       //  ���� ����1.
    AccessModel ( MODEL_WALL_PART2,      "Data\\Skill\\", "WallStone2" );       //  ���� ����2.
    AccessModel ( MODEL_GATE_PART1,      "Data\\Skill\\", "GatePart1" );        //  ���� ����1.
    AccessModel ( MODEL_GATE_PART2,      "Data\\Skill\\", "GatePart2" );        //  ���� ����2.
    AccessModel ( MODEL_GATE_PART3,      "Data\\Skill\\", "GatePart3" );        //  ���� ����3.
    AccessModel ( MODEL_AURORA,          "Data\\Skill\\", "Aurora" );           //  ȸ�� ����.
    AccessModel ( MODEL_TOWER_GATE_PLANE,"Data\\Skill\\", "TowerGatePlane" );   //  �̵� ����.
	AccessModel ( MODEL_GOLEM_STONE,	"Data\\Skill\\", "golem_stone" );		// �� ����
	AccessModel ( MODEL_FISSURE,		"Data\\Skill\\", "bossrock" );			// ���� �տ�
	AccessModel ( MODEL_FISSURE_LIGHT,		"Data\\Skill\\", "bossrocklight" );			// ���� �տ� ��
    AccessModel ( MODEL_PROTECTGUILD, "Data\\Skill\\", "ProtectGuild" );       //  ��ȣõ�縶ũ.
	AccessModel(MODEL_DARK_ELF_SKILL   ,"Data\\Skill\\","elf_skill");
	AccessModel(MODEL_BALGAS_SKILL   ,"Data\\Skill\\","WaveForce");
	AccessModel(MODEL_DEATH_SPI_SKILL   ,"Data\\Skill\\","deathsp_eff");
	Models[MODEL_BALGAS_SKILL].Actions[0].Loop = false;

#ifdef TAMAJJANG
    OpenTexture(MODEL_TAMAJJANG,"Skill\\");
#endif

	OpenTexture(MODEL_DARK_ELF_SKILL,"Skill\\");
	OpenTexture(MODEL_BALGAS_SKILL,"Skill\\");
	OpenTexture(MODEL_DEATH_SPI_SKILL,"Skill\\");

    OpenTexture ( MODEL_DARK_HORSE, "Skill\\" );
#ifdef PET_SYSTEM
    OpenTexture ( MODEL_DARK_SPIRIT, "Skill\\" );
#endif// PET_SYSTEM

#ifdef DARK_WOLF
    OpenTexture ( MODEL_DARK_WOLF, "Skill\\" );
#endif// DARK_WOLF

    OpenTexture ( MODEL_WARCRAFT, "Skill\\" );
    OpenTexture ( MODEL_PEGASUS, "Skill\\" );
	OpenTexture (MODEL_SKILL_FURY_STRIKE+1,"Skill\\");
	OpenTexture (MODEL_SKILL_FURY_STRIKE+2,"Skill\\");
	OpenTexture (MODEL_SKILL_FURY_STRIKE+3,"Skill\\");
	OpenTexture (MODEL_SKILL_FURY_STRIKE+5,"Skill\\");
	OpenTexture (MODEL_SKILL_FURY_STRIKE+7,"Skill\\");
	OpenTexture (MODEL_SKILL_FURY_STRIKE+8,"Skill\\");
    OpenTexture (MODEL_WAVE, "Skill\\");
    OpenTexture (MODEL_TAIL, "Skill\\");

	OpenTexture (MODEL_WAVE_FORCE, "Skill\\" );
	OpenTexture (MODEL_BLIZZARD, "Skill\\" );

	// ũ�������� �̺�Ʈ ������Ʈ �ε�
	g_XmasEvent->LoadXmasEvent();

	OpenTexture(MODEL_ARROW_BEST_CROSSBOW, "Skill\\");
	OpenTexture (MODEL_ARROW_DRILL, "Skill\\" );			//	�� ���� ����. ȭ��.
	OpenTexture (MODEL_COMBO	  , "Skill\\" );			//	�޺� ȿ��.

	OpenTexture ( MODEL_AIR_FORCE, "Skill\\", GL_CLAMP );   //  ���� ���� ȿ��.
    OpenTexture ( MODEL_WAVES    , "Skill\\" );             //  ��Ʈ�� �Ǿ��� ���� ȿ��.
    OpenTexture ( MODEL_PIERCING2, "Skill\\" );             //  ��Ʈ�� �Ǿ� ��ǰ.
    OpenTexture ( MODEL_PIER_PART, "Skill\\" );             //  ���Ǿ� ��ǰ.
    OpenTexture ( MODEL_GROUND_STONE,   "Skill\\" );        //  ����.
    OpenTexture ( MODEL_GROUND_STONE2,  "Skill\\" );        //  ����2.
	OpenTexture ( MODEL_WATER_WAVE,     "Skill\\", GL_CLAMP );  //	���Ϳ��̺�.
	OpenTexture ( MODEL_SKULL,          "Skill\\", GL_CLAMP );  //	�ذ�.
    OpenTexture ( MODEL_MANY_FLAG,      "Skill\\" );        //  �߱� ��ؿ��� ����ϴ� ���.
    OpenTexture ( MODEL_WEBZEN_MARK,    "Skill\\" );        //  ������ũ.

    OpenTexture ( MODEL_FLY_BIG_STONE1, "Npc\\" );          //  �����Ⱑ ������ �� ( ������ ).
    OpenTexture ( MODEL_FLY_BIG_STONE2, "Skill\\" );        //  �����Ⱑ ������ �� ( ������ ).
    OpenTexture ( MODEL_BIG_STONE_PART1,"Skill\\" );        //  �����Ⱑ ������ �� ����1.
    OpenTexture ( MODEL_BIG_STONE_PART2,"Skill\\" );        //  �����Ⱑ ������ �� ����2.
    OpenTexture ( MODEL_WALL_PART1,     "Object31\\" );     //  ���� ����1.
    OpenTexture ( MODEL_WALL_PART2,     "Object31\\" );     //  ���� ����2.
    OpenTexture ( MODEL_GATE_PART1,     "Monster\\" );      //  ���� ����1. 
    OpenTexture ( MODEL_GATE_PART2,     "Monster\\" );      //  ���� ����2.
    OpenTexture ( MODEL_GATE_PART3,     "Monster\\" );      //  ���� ����3.
    OpenTexture ( MODEL_AURORA,         "Monster\\" );      //  ȸ�� ����.
    OpenTexture ( MODEL_TOWER_GATE_PLANE,"Skill\\" );       //  �̵� ����.
	OpenTexture ( MODEL_GOLEM_STONE,	"Monster\\" );		// �� ����
	OpenTexture ( MODEL_FISSURE,	"Skill\\" );			// ���� �տ�
	OpenTexture ( MODEL_FISSURE_LIGHT,	"Skill\\" );			// ���� �տ� ��
    OpenTexture ( MODEL_SKIN_SHELL, "Effect\\" );           //  ��Ų ����.
    OpenTexture ( MODEL_PROTECTGUILD,    "Item\\" );        //  ��ȣõ�縶ũ.

	AccessModel(MODEL_SKILL_FURY_STRIKE+1,"Data\\Skill\\","EarthQuake",1);
	AccessModel(MODEL_SKILL_FURY_STRIKE+2,"Data\\Skill\\","EarthQuake",2);
	AccessModel(MODEL_SKILL_FURY_STRIKE+3,"Data\\Skill\\","EarthQuake",3);
	AccessModel(MODEL_SKILL_FURY_STRIKE+5,"Data\\Skill\\","EarthQuake",5);
	AccessModel(MODEL_SKILL_FURY_STRIKE+7,"Data\\Skill\\","EarthQuake",7);
	AccessModel(MODEL_SKILL_FURY_STRIKE+8,"Data\\Skill\\","EarthQuake",8);
	AccessModel(MODEL_WAVE,"Data\\Skill\\","flashing");
	AccessModel(MODEL_TAIL,"Data\\Skill\\","tail");

	AccessModel(MODEL_SKILL_FURY_STRIKE+4,"Data\\Skill\\","EarthQuake",4);
	AccessModel(MODEL_SKILL_FURY_STRIKE+6,"Data\\Skill\\","EarthQuake",6);
    AccessModel(MODEL_PIERCING,"Data\\Skill\\","Piercing");

	AccessModel(MODEL_WAVE_FORCE,"Data\\Skill\\","WaveForce");
	AccessModel(MODEL_BLIZZARD,"Data\\Skill\\","Blizzard");

	//ȭ�� �ڵ���� ����Ʈ
	AccessModel(MODEL_ARROW_AUTOLOAD, "Data\\Skill\\", "arrowsrefill");
	OpenTexture(MODEL_ARROW_AUTOLOAD, "Effect\\");

	//ȭ�� �ڵ���� ����Ʈ
	AccessModel(MODEL_INFINITY_ARROW, "Data\\Skill\\", "arrowsre", 1);
	OpenTexture(MODEL_INFINITY_ARROW, "Skill\\");
	AccessModel(MODEL_INFINITY_ARROW1, "Data\\Skill\\", "arrowsre", 2);
	OpenTexture(MODEL_INFINITY_ARROW1, "Skill\\");
	AccessModel(MODEL_INFINITY_ARROW2, "Data\\Skill\\", "arrowsre", 3);
	OpenTexture(MODEL_INFINITY_ARROW2, "Skill\\");
	AccessModel(MODEL_INFINITY_ARROW3, "Data\\Skill\\", "arrowsre", 4);
	OpenTexture(MODEL_INFINITY_ARROW3, "Effect\\");
	AccessModel(MODEL_INFINITY_ARROW4, "Data\\Skill\\", "arrowsre", 5);
	OpenTexture(MODEL_INFINITY_ARROW4, "Skill\\");

	//�ǵ� ������ ����Ʈ
	AccessModel(MODEL_SHIELD_CRASH, "Data\\Effect\\", "atshild");
	OpenTexture(MODEL_SHIELD_CRASH, "Effect\\");

	AccessModel(MODEL_SHIELD_CRASH2, "Data\\Effect\\", "atshild2");
	OpenTexture(MODEL_SHIELD_CRASH2, "Effect\\");

	//ĭ���� - ���̾���̴� ���� ����Ʈ
	AccessModel(MODEL_IRON_RIDER_ARROW, "Data\\Effect\\", "ironobj");
	OpenTexture(MODEL_IRON_RIDER_ARROW, "Effect\\");

	AccessModel(MODEL_KENTAUROS_ARROW, "Data\\Effect\\", "cantasarrow");
	OpenTexture(MODEL_KENTAUROS_ARROW, "Effect\\");

	AccessModel(MODEL_BLADE_SKILL, "Data\\Effect\\", "bladetonedo");
	OpenTexture(MODEL_BLADE_SKILL, "Effect\\");
	
	AccessModel(MODEL_CHANGE_UP_EFF   ,"Data\\Effect\\","Change_Up_Eff");
	OpenTexture(MODEL_CHANGE_UP_EFF, "Effect\\");
	Models[MODEL_CHANGE_UP_EFF].Actions[0].PlaySpeed = 0.005f;
	AccessModel(MODEL_CHANGE_UP_NASA   ,"Data\\Effect\\","changup_nasa");
	//changup_nasa
	OpenTexture(MODEL_CHANGE_UP_NASA, "Effect\\");
	AccessModel(MODEL_CHANGE_UP_CYLINDER   ,"Data\\Effect\\","clinderlight");
	OpenTexture(MODEL_CHANGE_UP_CYLINDER, "Effect\\");

	//���� ǥ��
	AccessModel(MODEL_CURSEDTEMPLE_HOLYITEM, "Data\\Skill\\", "eventsungmul");
	OpenTexture(MODEL_CURSEDTEMPLE_HOLYITEM, "Skill\\");

	//���� ǥ��
	AccessModel(MODEL_CURSEDTEMPLE_PRODECTION_SKILL, "Data\\Skill\\", "eventshild");
	OpenTexture(MODEL_CURSEDTEMPLE_PRODECTION_SKILL, "Skill\\");

	//�ӹ� ǥ��
	AccessModel(MODEL_CURSEDTEMPLE_RESTRAINT_SKILL, "Data\\Skill\\", "eventroofe");
	OpenTexture(MODEL_CURSEDTEMPLE_RESTRAINT_SKILL, "Skill\\");
		
	// ���� ����1
	AccessModel ( MODEL_CURSEDTEMPLE_STATUE_PART1, "Data\\Npc\\", "songck1" );
	OpenTexture ( MODEL_CURSEDTEMPLE_STATUE_PART1, "Npc\\" );

	// ���� ����2
	AccessModel ( MODEL_CURSEDTEMPLE_STATUE_PART2, "Data\\Npc\\", "songck2" );
	OpenTexture ( MODEL_CURSEDTEMPLE_STATUE_PART2, "Npc\\" );
	
	AccessModel(MODEL_FENRIR_THUNDER, "Data\\Effect\\", "lightning_type01");
	OpenTexture(MODEL_FENRIR_THUNDER, "Effect\\");

#ifdef _VS2008PORTING
	for(int i=MODEL_SKILL_BEGIN;i<MODEL_SKILL_END;i++)
#else // _VS2008PORTING
	for(i=MODEL_SKILL_BEGIN;i<MODEL_SKILL_END;i++)
#endif // _VS2008PORTING
	{
        if( i==MODEL_PIERCING )
        {
            OpenTexture(i,"Skill\\");
        }
        else
            OpenTexture(i,"Skill\\");
	}

	//�����ĺ��� ����
	LoadBitmap("Skill\\flower1.tga",BITMAP_FLOWER01);
	LoadBitmap("Skill\\flower2.tga",BITMAP_FLOWER01+1);
	LoadBitmap("Skill\\flower3.tga",BITMAP_FLOWER01+2);
	
#ifdef PRUARIN_EVENT07_3COLORHARVEST
	// �߼� �̺�Ʈ ����Ʈ ������Ʈ �ε�
	AccessModel(MODEL_MOONHARVEST_GAM, "Data\\Effect\\", "chusukgam" );		// ��
	OpenTexture(MODEL_MOONHARVEST_GAM, "Effect\\");
	AccessModel(MODEL_MOONHARVEST_SONGPUEN1, "Data\\Effect\\", "chusukseung1" );	// ���� (��)
	OpenTexture(MODEL_MOONHARVEST_SONGPUEN1, "Effect\\");
	AccessModel(MODEL_MOONHARVEST_SONGPUEN2, "Data\\Effect\\", "chusukseung2" );	// ���� (��)
	OpenTexture(MODEL_MOONHARVEST_SONGPUEN2, "Effect\\");
	AccessModel(MODEL_MOONHARVEST_MOON, "Data\\Effect\\", "chysukmoon" );	// ��
	OpenTexture(MODEL_MOONHARVEST_MOON, "Effect\\");
#endif // PRUARIN_EVENT07_3COLORHARVEST
	
	AccessModel(MODEL_ALICE_BUFFSKILL_EFFECT, "Data\\Effect\\", "elshildring" );	// �ٸ��� ���� ��ų���� ����Ʈ ��
	OpenTexture(MODEL_ALICE_BUFFSKILL_EFFECT, "Effect\\");
	AccessModel(MODEL_ALICE_BUFFSKILL_EFFECT2, "Data\\Effect\\", "elshildring2" );	// �ٸ��� ���� ��ų���� ����Ʈ ��
	OpenTexture(MODEL_ALICE_BUFFSKILL_EFFECT2, "Effect\\");

	AccessModel(MODEL_SUMMONER_WRISTRING_EFFECT, "Data\\Effect\\", "ringtyperout" );	// ��ȯ�� ���� �ո� ����Ʈ
	OpenTexture(MODEL_SUMMONER_WRISTRING_EFFECT, "Effect\\");
	// ��ȯ�� �Ӹ�
	AccessModel(MODEL_SUMMONER_EQUIP_HEAD_SAHAMUTT, "Data\\Skill\\", "sahatail" );		// ���Ϲ�Ʈ ��ȯ �Ӹ�
	OpenTexture(MODEL_SUMMONER_EQUIP_HEAD_SAHAMUTT, "Skill\\");
	AccessModel(MODEL_SUMMONER_EQUIP_HEAD_NEIL, "Data\\Skill\\", "nillsohwanz" );		// �� ��ȯ �Ӹ�
	OpenTexture(MODEL_SUMMONER_EQUIP_HEAD_NEIL, "Skill\\");
#ifdef ASG_ADD_SUMMON_RARGLE
	AccessModel(MODEL_SUMMONER_EQUIP_HEAD_LAGUL, "Data\\Skill\\", "lagul_head" );		// ��� ��ȯ �Ӹ�
	OpenTexture(MODEL_SUMMONER_EQUIP_HEAD_LAGUL, "Skill\\");
#endif	// ASG_ADD_SUMMON_RARGLE
	// ���� ����Ʈ
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT1, "Data\\Effect\\", "Suhwanzin1" );		// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT1, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT11, "Data\\Effect\\", "Suhwanzin11" );		// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT11, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT111, "Data\\Effect\\", "Suhwanzin111" );	// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT111, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT2, "Data\\Effect\\", "Suhwanzin2" );		// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT2, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT22, "Data\\Effect\\", "Suhwanzin22" );		// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT22, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT222, "Data\\Effect\\", "Suhwanzin222" );	// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT222, "Effect\\");
	AccessModel(MODEL_SUMMONER_CASTING_EFFECT4, "Data\\Effect\\", "Suhwanzin4" );		// ��ȯ ���� ����Ʈ
	OpenTexture(MODEL_SUMMONER_CASTING_EFFECT4, "Effect\\");
	// ��ȯ��
	AccessModel(MODEL_SUMMONER_SUMMON_SAHAMUTT, "Data\\Skill\\", "summon_sahamutt" );		// ���Ϲ�Ʈ
	OpenTexture(MODEL_SUMMONER_SUMMON_SAHAMUTT, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL, "Data\\Skill\\", "summon_neil" );			// ��
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL, "Skill\\");
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL, "Effect\\");
#ifdef ASG_ADD_SUMMON_RARGLE
	AccessModel(MODEL_SUMMONER_SUMMON_LAGUL, "Data\\Skill\\", "summon_lagul");			// ���
	OpenTexture(MODEL_SUMMONER_SUMMON_LAGUL, "Skill\\");
#endif	// ASG_ADD_SUMMON_RARGLE
	// ��ȯ�� ��ų ����Ʈ
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_NIFE1, "Data\\Skill\\", "nelleff_nife01" );		// �� ��ų ����Ʈ Į
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_NIFE1, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_NIFE2, "Data\\Skill\\", "nelleff_nife02" );		// �� ��ų ����Ʈ Į
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_NIFE2, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_NIFE3, "Data\\Skill\\", "nelleff_nife03" );		// �� ��ų ����Ʈ Į
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_NIFE3, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_GROUND1, "Data\\Skill\\", "nell_nifegrund01" );	// �� ��ų ����Ʈ �ٴڸ� lv1
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_GROUND1, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_GROUND2, "Data\\Skill\\", "nell_nifegrund02" );	// �� ��ų ����Ʈ �ٴڸ� lv2
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_GROUND2, "Skill\\");
	AccessModel(MODEL_SUMMONER_SUMMON_NEIL_GROUND3, "Data\\Skill\\", "nell_nifegrund03" );	// �� ��ų ����Ʈ �ٴڸ� lv3
	OpenTexture(MODEL_SUMMONER_SUMMON_NEIL_GROUND3, "Skill\\");
	AccessModel(MODEL_MOVE_TARGETPOSITION_EFFECT, "Data\\Effect\\", "MoveTargetPosEffect" );	// �̵�����ġ ����Ʈ
	OpenTexture(MODEL_MOVE_TARGETPOSITION_EFFECT, "Effect\\");
	AccessModel(MODEL_EFFECT_SAPITRES_ATTACK_1, "Data\\Effect\\", "Sapiatttres" );	// ����Ʈ���� ���ó�����
	OpenTexture(MODEL_EFFECT_SAPITRES_ATTACK_1, "Effect\\");
	AccessModel(MODEL_EFFECT_SAPITRES_ATTACK_2, "Data\\Effect\\", "Sapiatttres2" );	// ����Ʈ���� ������� ���� ������
	OpenTexture(MODEL_EFFECT_SAPITRES_ATTACK_2, "Effect\\");
#ifdef CSK_RAKLION_BOSS
	AccessModel(MODEL_RAKLION_BOSS_CRACKEFFECT, "Data\\Effect\\", "knight_plancrack_grand" );
	OpenTexture(MODEL_RAKLION_BOSS_CRACKEFFECT, "Effect\\");
	AccessModel(MODEL_RAKLION_BOSS_MAGIC, "Data\\Effect\\", "serufan_magic" );
	OpenTexture(MODEL_RAKLION_BOSS_MAGIC, "Effect\\");
	//Models[MODEL_RAKLION_BOSS_MAGIC].Actions[0].PlaySpeed = 0.005f;
#endif // CSK_RAKLION_BOSS
#ifdef CSK_EVENT_CHERRYBLOSSOM
	// ���� �̺�Ʈ ����Ʈ
	AccessModel(MODEL_EFFECT_SKURA_ITEM, "Data\\Effect\\cherryblossom\\", "Skura_iteam_event" );
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef ADD_RAKLION_IRON_KNIGHT
	// ��Ŭ���� ���̾� ����Ʈ 
	AccessModel(MODEL_EFFECT_BROKEN_ICE0, "Data\\Effect\\", "ice_stone00" );
	OpenTexture(MODEL_EFFECT_BROKEN_ICE0, "Effect\\");
	AccessModel(MODEL_EFFECT_BROKEN_ICE1, "Data\\Effect\\", "ice_stone01" );
	OpenTexture(MODEL_EFFECT_BROKEN_ICE1, "Effect\\");
	AccessModel(MODEL_EFFECT_BROKEN_ICE2, "Data\\Effect\\", "ice_stone02" );
	OpenTexture(MODEL_EFFECT_BROKEN_ICE2, "Effect\\");
	AccessModel(MODEL_EFFECT_BROKEN_ICE3, "Data\\Effect\\", "ice_stone03" );
	OpenTexture(MODEL_EFFECT_BROKEN_ICE3, "Effect\\");
#endif	// ADD_RAKLION_IRON_KNIGHT
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	AccessModel(MODEL_NIGHTWATER_01, "Data\\Effect\\", "nightwater01" );
	OpenTexture(MODEL_NIGHTWATER_01, "Effect\\");
	AccessModel(MODEL_KNIGHT_PLANCRACK_A, "Data\\Effect\\", "knight_plancrack_a" );
	OpenTexture(MODEL_KNIGHT_PLANCRACK_A, "Effect\\");
	Models[MODEL_KNIGHT_PLANCRACK_A].Actions[0].PlaySpeed = 0.3f;
	AccessModel(MODEL_KNIGHT_PLANCRACK_B, "Data\\Effect\\", "knight_plancrack_b" );
	OpenTexture(MODEL_KNIGHT_PLANCRACK_B, "Effect\\");
	Models[MODEL_KNIGHT_PLANCRACK_B].Actions[0].PlaySpeed = 0.3f;
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	AccessModel(MODEL_EFFECT_FLAME_STRIKE, "Data\\Effect\\", "FlameStrike" );
	OpenTexture(MODEL_EFFECT_FLAME_STRIKE, "Effect\\");
#endif	// YDG_ADD_SKILL_FLAME_STRIKE
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER	// ��������
	AccessModel(MODEL_SWELL_OF_MAGICPOWER, "Data\\Effect\\", "magic_powerup" );
	OpenTexture(MODEL_SWELL_OF_MAGICPOWER, "Effect\\");
	AccessModel(MODEL_ARROWSRE06, "Data\\Effect\\", "arrowsre06" );
	OpenTexture(MODEL_ARROWSRE06, "Effect\\");
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	AccessModel(MODEL_DOPPELGANGER_SLIME_CHIP, "Data\\Effect\\", "slime_chip" );
	OpenTexture(MODEL_DOPPELGANGER_SLIME_CHIP, "Effect\\");
#endif	// YDG_ADD_DOPPELGANGER_MONSTER
#ifdef KJH_ADD_09SUMMER_EVENT
	AccessModel(MODEL_EFFECT_UMBRELLA_GOLD, "Data\\Effect\\", "japan_gold01" );
	OpenTexture(MODEL_EFFECT_UMBRELLA_GOLD, "Effect\\");
#endif // KJH_ADD_09SUMMER_EVENT
#ifdef LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
	AccessModel(MODEL_EMPIREGUARDIANBOSS_FRAMESTRIKE, "Data\\Effect\\", "Karanebos_sword_framestrike" );
	OpenTexture(MODEL_EMPIREGUARDIANBOSS_FRAMESTRIKE, "Effect\\");
	//Models[MODEL_EMPIREGUARDIANBOSS_FRAMESTRIKE].Actions[MONSTER01_STOP1].PlaySpeed = 3.0f;
#endif // LDS_ADD_EG_4_MONSTER_WORLDBOSS_GAIONKALEIN
#ifdef LDK_ADD_EG_MONSTER_DEASULER
	AccessModel(MODEL_DEASULER, "Data\\Monster\\", "deasther_boomerang" );
	OpenTexture(MODEL_DEASULER, "Monster\\");
#endif // LDK_ADD_EG_MONSTER_DEASULER
#ifdef PBG_ADD_AURA_EFFECT
	AccessModel(MODEL_EFFECT_SD_AURA, "Data\\Effect\\", "shield_up" );
	OpenTexture(MODEL_EFFECT_SD_AURA, "Effect\\");
#endif //PBG_ADD_AURA_EFFECT
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	AccessModel(MODEL_WOLF_HEAD_EFFECT, "Data\\Effect\\", "wolf_head_effect" );
	OpenTexture(MODEL_WOLF_HEAD_EFFECT, "Effect\\");
	LoadBitmap("Effect\\sbumb.jpg", BITMAP_SBUMB, GL_LINEAR, GL_REPEAT);
	AccessModel(MODEL_DOWN_ATTACK_DUMMY_L, "Data\\Effect\\", "down_right_punch");	//�����Ͱ� �ٲ���㤾
	OpenTexture(MODEL_DOWN_ATTACK_DUMMY_L, "Effect\\");
	AccessModel(MODEL_DOWN_ATTACK_DUMMY_R, "Data\\Effect\\", "down_left_punch");
	OpenTexture(MODEL_DOWN_ATTACK_DUMMY_R, "Effect\\");
	AccessModel(MODEL_SHOCKWAVE01, "Data\\Effect\\", "shockwave01");
	OpenTexture(MODEL_SHOCKWAVE01, "Effect\\");
	AccessModel(MODEL_SHOCKWAVE02, "Data\\Effect\\", "shockwave02");
	OpenTexture(MODEL_SHOCKWAVE02, "Effect\\");
	AccessModel(MODEL_SHOCKWAVE_SPIN01, "Data\\Effect\\", "shockwave_spin01");
	OpenTexture(MODEL_SHOCKWAVE_SPIN01, "Effect\\");
	AccessModel(MODEL_WINDFOCE, "Data\\Effect\\", "wind_foce");
	OpenTexture(MODEL_WINDFOCE, "Effect\\");
	AccessModel(MODEL_WINDFOCE_MIRROR, "Data\\Effect\\", "wind_foce_mirror");
	OpenTexture(MODEL_WINDFOCE_MIRROR, "Effect\\");
	AccessModel(MODEL_WOLF_HEAD_EFFECT2, "Data\\Effect\\", "wolf_head_effect2");
	OpenTexture(MODEL_WOLF_HEAD_EFFECT2, "skill\\");
	AccessModel(MODEL_SHOCKWAVE_GROUND01, "Data\\Effect\\", "shockwave_ground01");
	OpenTexture(MODEL_SHOCKWAVE_GROUND01, "Effect\\");
	AccessModel(MODEL_DRAGON_KICK_DUMMY, "Data\\Effect\\", "dragon_kick_dummy");
	OpenTexture(MODEL_DRAGON_KICK_DUMMY, "Effect\\");
	AccessModel(MODEL_DRAGON_LOWER_DUMMY, "Data\\Effect\\", "knight_plancrack_dragon");
	OpenTexture(MODEL_DRAGON_LOWER_DUMMY, "Effect\\");
	AccessModel(MODEL_VOLCANO_OF_MONK, "Data\\Effect\\", "volcano_of_monk");
	OpenTexture(MODEL_VOLCANO_OF_MONK, "Effect\\");
	AccessModel(MODEL_VOLCANO_STONE, "Data\\Effect\\", "volcano_stone");
	OpenTexture(MODEL_VOLCANO_STONE, "Effect\\");
	LoadBitmap("Effect\\force_Pillar.jpg", BITMAP_FORCEPILLAR, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\!SwordEff.jpg", BITMAP_SWORDEFF, GL_LINEAR, GL_REPEAT);
	LoadBitmap("Effect\\Damage1.jpg", BITMAP_DAMAGE1, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\ground_wind.jpg", BITMAP_GROUND_WIND, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\Kwave2.jpg", BITMAP_KWAVE2, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\Damage2.jpg", BITMAP_DAMAGE2, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\volcano_core.jpg", BITMAP_VOLCANO_CORE, GL_LINEAR, GL_CLAMP);
	AccessModel(MODEL_SHOCKWAVE03, "Data\\Effect\\", "shockwave03");
	OpenTexture(MODEL_SHOCKWAVE03, "Effect\\");
	LoadBitmap("Effect\\ground_smoke.tga", BITMAP_GROUND_SMOKE, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\knightSt_blue.jpg", BITMAP_KNIGHTST_BLUE, GL_LINEAR, GL_CLAMP);
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#ifdef ASG_ADD_KARUTAN_MONSTERS
	// �ܵ�� ������
	AccessModel(MODEL_CONDRA_STONE, "Data\\Monster\\", "condra_7_stone" );
	OpenTexture(MODEL_CONDRA_STONE, "Monster\\");
	AccessModel(MODEL_CONDRA_STONE1, "Data\\Monster\\", "condra_7_stone_2" );
	OpenTexture(MODEL_CONDRA_STONE1, "Monster\\");
	AccessModel(MODEL_CONDRA_STONE2, "Data\\Monster\\", "condra_7_stone_3" );
	OpenTexture(MODEL_CONDRA_STONE2, "Monster\\");
	AccessModel(MODEL_CONDRA_STONE3, "Data\\Monster\\", "condra_7_stone_4" );
	OpenTexture(MODEL_CONDRA_STONE3, "Monster\\");
	AccessModel(MODEL_CONDRA_STONE4, "Data\\Monster\\", "condra_7_stone_5" );
	OpenTexture(MODEL_CONDRA_STONE4, "Monster\\");
	AccessModel(MODEL_CONDRA_STONE5, "Data\\Monster\\", "condra_7_stone_6" );
	OpenTexture(MODEL_CONDRA_STONE5, "Monster\\");

	// �����ܵ�� ������
	AccessModel(MODEL_NARCONDRA_STONE, "Data\\Monster\\", "nar_condra_7_stone_1" );
	OpenTexture(MODEL_NARCONDRA_STONE, "Monster\\");
	AccessModel(MODEL_NARCONDRA_STONE1, "Data\\Monster\\", "nar_condra_7_stone_2" );
	OpenTexture(MODEL_NARCONDRA_STONE1, "Monster\\");
	AccessModel(MODEL_NARCONDRA_STONE2, "Data\\Monster\\", "nar_condra_7_stone_3" );
	OpenTexture(MODEL_NARCONDRA_STONE2, "Monster\\");
	AccessModel(MODEL_NARCONDRA_STONE3, "Data\\Monster\\", "nar_condra_7_stone_4" );
	OpenTexture(MODEL_NARCONDRA_STONE3, "Monster\\");
#endif	// ASG_ADD_KARUTAN_MONSTERS

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENSKILLS );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// ���� ������Ʈ ����Ÿ �о���̴� �Լ�(���ӿ��� ���� �̵��� �ε�)
///////////////////////////////////////////////////////////////////////////////

#include "ReadScript.h"

void OpenWorldModels()
{
	int i;
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	bool Temp = true;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
	
	//�����
	LoadBitmap("Object8\\drop01.jpg"     ,BITMAP_BUBBLE);
    
	switch(World)
	{
	case WD_0LORENCIA:
		AccessModel(MODEL_BIRD01		 ,"Data\\Object1\\","Bird",1);
		OpenTexture(MODEL_BIRD01		 ,"Object1\\");
		AccessModel(MODEL_FISH01		 ,"Data\\Object1\\","Fish",1);
		OpenTexture(MODEL_FISH01		 ,"Object1\\");
		break;
	case WD_1DUNGEON:
	case WD_4LOSTTOWER:
		AccessModel(MODEL_DUNGEON_STONE01,"Data\\Object2\\","DungeonStone",1);
		OpenTexture(MODEL_DUNGEON_STONE01,"Object2\\");
		AccessModel(MODEL_BAT01          ,"Data\\Object2\\","Bat",1);
		OpenTexture(MODEL_BAT01		     ,"Object2\\");
		AccessModel(MODEL_RAT01          ,"Data\\Object2\\","Rat",1);
		OpenTexture(MODEL_RAT01		     ,"Object2\\");
		break;
	case WD_2DEVIAS:
		{
			vec3_t Pos, Ang;
			AccessModel ( MODEL_NPC_SERBIS_DONKEY, "Data\\Npc\\", "obj_donkey" );
			OpenTexture ( MODEL_NPC_SERBIS_DONKEY, "Npc\\" );
			AccessModel ( MODEL_NPC_SERBIS_FLAG, "Data\\Npc\\", "obj_flag" );
			OpenTexture ( MODEL_NPC_SERBIS_FLAG, "Npc\\" );	

			Vector ( 0.f, 0.f, 0.f, Ang );
			Vector ( 0.f, 0.f, 270.f, Pos );
			Pos[0] = 191*TERRAIN_SCALE; Pos[1] = 16*TERRAIN_SCALE;
			CreateObject ( MODEL_NPC_SERBIS_DONKEY, Pos, Ang );
			Pos[0] = 191*TERRAIN_SCALE; Pos[1] = 17*TERRAIN_SCALE;
			CreateObject ( MODEL_NPC_SERBIS_FLAG, Pos, Ang );
			
#ifdef CSK_REPAIR_MAP_DEVIAS
			AccessModel(MODEL_WARP	 ,"Data\\Npc\\","warp01");
			AccessModel(MODEL_WARP2	 ,"Data\\Npc\\","warp02");
			AccessModel(MODEL_WARP3	 ,"Data\\Npc\\","warp03");
			OpenTexture(MODEL_WARP	 ,"Npc\\");
			OpenTexture(MODEL_WARP2	 ,"Npc\\");
			OpenTexture(MODEL_WARP3	 ,"Npc\\");
			Vector ( 0.f, 0.f, 10.f, Ang );
			Vector ( 0.f, 0.f, 0.f, Pos );
			Pos[0] = 53*TERRAIN_SCALE + 50.f; 
			Pos[1] = 92*TERRAIN_SCALE + 20.f;
			CreateObject ( MODEL_WARP, Pos, Ang );
#endif // CSK_REPAIR_MAP_DEVIAS
		}
		break;
	case WD_3NORIA:
		AccessModel(MODEL_BUTTERFLY01	 ,"Data\\Object1\\","Butterfly",1);
		OpenTexture(MODEL_BUTTERFLY01	 ,"Object1\\");
		AccessModel(MODEL_WARP	 ,"Data\\Npc\\","warp01");
		AccessModel(MODEL_WARP2	 ,"Data\\Npc\\","warp02");
		AccessModel(MODEL_WARP3	 ,"Data\\Npc\\","warp03");
		
		OpenTexture(MODEL_WARP	 ,"Npc\\");
		OpenTexture(MODEL_WARP2	 ,"Npc\\");
		OpenTexture(MODEL_WARP3	 ,"Npc\\");
		
		vec3_t Pos, Ang;
		Vector ( 0.f, 0.f, 10.f, Ang );
		Vector ( 0.f, 0.f, 0.f, Pos );
		Pos[0] = 223*TERRAIN_SCALE; Pos[1] = 30*TERRAIN_SCALE;
		CreateObject ( MODEL_WARP, Pos, Ang );
		break;
	case WD_5UNKNOWN:
#ifdef _VS2008PORTING
		for(int i=0;i<5;i++)
#else // _VS2008PORTING
		for(i=0;i<5;i++)
#endif // _VS2008PORTING
			AccessModel(MODEL_BIG_METEO1+i,"Data\\Object6\\","Meteo",i+1);
		AccessModel(MODEL_BOSS_HEAD,"Data\\Object6\\","BossHead",1);
		AccessModel(MODEL_PRINCESS ,"Data\\Object6\\","Princess",1);
#ifdef _VS2008PORTING
		for(int i=MODEL_BIG_METEO1;i<=MODEL_PRINCESS;i++)
#else // _VS2008PORTING
		for(i=MODEL_BIG_METEO1;i<=MODEL_PRINCESS;i++)
#endif // _VS2008PORTING
			OpenTexture(i,"Object6\\",GL_NEAREST);
		break;
	case WD_6STADIUM:
		AccessModel(MODEL_BUG01          ,"Data\\Object7\\","Bug",1);
		OpenTexture(MODEL_BUG01		     ,"Object7\\");
		break;
	case WD_7ATLANSE:
#ifdef YDG_ADD_MAP_DOPPELGANGER3
	case WD_67DOPPLEGANGER3:
#endif	// YDG_ADD_MAP_DOPPELGANGER3
#ifdef _VS2008PORTING
		for(int i=1;i<9;i++)
#else // _VS2008PORTING
		for(i=1;i<9;i++)
#endif // _VS2008PORTING
		{
			AccessModel(MODEL_FISH01+i,"Data\\Object8\\","Fish",i+1);
			OpenTexture(MODEL_FISH01+i,"Object8\\");
		}
#ifdef _VS2008PORTING
		for(int i=0;i<32;i++)
#else // _VS2008PORTING
		for(i=0;i<32;i++)
#endif // _VS2008PORTING
		{
			char FileName[100];
			if(i<10)
      			sprintf(FileName,"Object8\\wt0%d.jpg",i);
			else
      			sprintf(FileName,"Object8\\wt%d.jpg",i);

			LoadBitmap(FileName,BITMAP_WATER+i,GL_LINEAR,GL_REPEAT,false);
			
			if(i<10)
      			sprintf(FileName,"wt0%d.jpg",i);
			else
      			sprintf(FileName,"wt%d.jpg",i);
			strcpy(Bitmaps[BITMAP_WATER+i].FileName,FileName);
		}
		break;
    case WD_8TARKAN:
		LoadBitmap("Object9\\sand01.jpg"     ,BITMAP_CHROME+2    ,GL_LINEAR,GL_REPEAT);
		LoadBitmap("Object9\\sand02.jpg"     ,BITMAP_CHROME+3    ,GL_LINEAR,GL_REPEAT);
        LoadBitmap("Object9\\Impack03.jpg"   ,BITMAP_IMPACT      ,GL_LINEAR,GL_CLAMP);
		AccessModel(MODEL_BUG01+1         ,"Data\\Object9\\","Bug",2);
		OpenTexture(MODEL_BUG01+1		  ,"Object9\\");
        break;
    case WD_10HEAVEN:
		LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD ,GL_LINEAR,GL_CLAMP);
        //  ����.
		AccessModel(MODEL_CLOUD,"Data\\Object11\\","cloud");
		OpenTexture(MODEL_CLOUD,"Object11\\");
        //  ��½�̴� ����.
		LoadBitmap("Effect\\cloudLight.jpg" ,BITMAP_CLOUD+1, GL_LINEAR, GL_CLAMP);
        break;

    case WD_11BLOODCASTLE1:     //  ���� 1ĳ��.
    case WD_11BLOODCASTLE1+1:   //  ���� 2ĳ��.
    case WD_11BLOODCASTLE1+2:   //  ���� 3ĳ��.
    case WD_11BLOODCASTLE1+3:   //  ���� 4ĳ��.
    case WD_11BLOODCASTLE1+4:   //  ���� 5ĳ��.
    case WD_11BLOODCASTLE1+5:   //  ���� 6ĳ��.
    case WD_11BLOODCASTLE1+6:   //  ���� 7ĳ��.
	case WD_52BLOODCASTLE_MASTER_LEVEL:
        {
		    AccessModel ( MODEL_CROW, "Data\\Object12\\", "Crow", 1 );
		    OpenTexture ( MODEL_CROW, "Object12\\" );

            for ( int i=0; i<2; ++i )
                OpenTexture ( MODEL_GATE+i, "Monster\\" );
			
			LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD ,GL_LINEAR,GL_CLAMP);

            //  ȿ����.
		    LoadWaveFile ( SOUND_BLOODCASTLE, "Data\\Sound\\iBloodCastle.wav" , 1 );
        }
        break;
	case WD_34CRYWOLF_1ST:
		{
			AccessModel(MODEL_SCOLPION          ,"Data\\Object35\\","scorpion");
			OpenTexture(MODEL_SCOLPION		     ,"Object35\\");

			LoadBitmap( "Effect\\Map_Smoke1.jpg" ,BITMAP_CHROME+2, GL_LINEAR, GL_REPEAT );
			LoadBitmap( "Effect\\Map_Smoke2.tga" ,BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT );
			LoadBitmap("Effect\\mhoujin_R.jpg"  ,BITMAP_MAGIC_CIRCLE, GL_LINEAR, GL_CLAMP);

			AccessModel(MODEL_ARROW_TANKER	 ,"Data\\Monster\\","arrowstusk");
			OpenTexture(MODEL_ARROW_TANKER   ,"Monster\\");
			AccessModel(MODEL_ARROW_TANKER_HIT	 ,"Data\\Monster\\","arrowstusk");
			OpenTexture(MODEL_ARROW_TANKER_HIT   ,"Monster\\");

			LoadBitmap("Effect\\Impack03.jpg"			, BITMAP_EXT_LOG_IN+2);
			LoadBitmap("Logo\\chasellight.jpg"		, BITMAP_EFFECT);

			LoadWaveFile ( SOUND_CRY1ST_AMBIENT,    "Data\\Sound\\w35\\crywolf_ambi.wav", 1, true );      //  ��� ȿ����

			//�������
			LoadWaveFile ( SOUND_CRY1ST_WWOLF_MOVE1,             "Data\\Sound\\w35\\ww_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_WWOLF_MOVE2,             "Data\\Sound\\w35\\ww_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_WWOLF_ATTACK1,           "Data\\Sound\\w35\\ww_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_WWOLF_ATTACK2,           "Data\\Sound\\w35\\ww_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_WWOLF_DIE,               "Data\\Sound\\w35\\ww_death.wav", 1 );

			//��ī��Ʈ(�ٰŸ�)
			LoadWaveFile ( SOUND_CRY1ST_SCOUT1_MOVE1,           "Data\\Sound\\w35\\ww_s1_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT1_MOVE2,           "Data\\Sound\\w35\\ww_s1_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT1_ATTACK1,         "Data\\Sound\\w35\\ww_s1_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT1_ATTACK2,         "Data\\Sound\\w35\\ww_s1_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT1_DIE,             "Data\\Sound\\w35\\ww_s1_death.wav", 1 );

			//��ī��Ʈ(�߰Ÿ�)
			LoadWaveFile ( SOUND_CRY1ST_SCOUT2_MOVE1,             "Data\\Sound\\w35\\ww_s2_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT2_MOVE2,             "Data\\Sound\\w35\\ww_s2_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT2_ATTACK1,           "Data\\Sound\\w35\\ww_s2_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT2_ATTACK2,           "Data\\Sound\\w35\\ww_s2_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT2_DIE,               "Data\\Sound\\w35\\ww_s2_death.wav", 1 );

			//��ī��Ʈ(��Ÿ�)
			LoadWaveFile ( SOUND_CRY1ST_SCOUT3_MOVE1,             "Data\\Sound\\w35\\ww_s3_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT3_MOVE2,             "Data\\Sound\\w35\\ww_s3_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT3_ATTACK1,           "Data\\Sound\\w35\\ww_s3_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT3_ATTACK2,           "Data\\Sound\\w35\\ww_s3_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SCOUT3_DIE,               "Data\\Sound\\w35\\ww_s3_death.wav", 1 );

			//�Ҷ�
			LoadWaveFile ( SOUND_CRY1ST_SORAM_MOVE1,             "Data\\Sound\\w35\\soram_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SORAM_MOVE2,             "Data\\Sound\\w35\\soram_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SORAM_ATTACK1,           "Data\\Sound\\w35\\soram_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SORAM_ATTACK2,           "Data\\Sound\\w35\\soram_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_SORAM_DIE,               "Data\\Sound\\w35\\soram_death.wav", 1 );

			//�߶�
			LoadWaveFile ( SOUND_CRY1ST_BALRAM_MOVE1,             "Data\\Sound\\w35\\balram_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALRAM_MOVE2,             "Data\\Sound\\w35\\balram_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALRAM_ATTACK1,           "Data\\Sound\\w35\\balram_attack1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALRAM_ATTACK2,           "Data\\Sound\\w35\\balram_attack2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALRAM_DIE,               "Data\\Sound\\w35\\balram_death.wav", 1 );

			//�߰���
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_MOVE1,             "Data\\Sound\\w35\\balga_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_MOVE2,             "Data\\Sound\\w35\\balga_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_ATTACK1,           "Data\\Sound\\w35\\balga_at1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_ATTACK2,           "Data\\Sound\\w35\\balga_at2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_DIE,               "Data\\Sound\\w35\\balga_death.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_SKILL1,            "Data\\Sound\\w35\\balga_skill1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_BALGAS_SKILL2,            "Data\\Sound\\w35\\balga_skill2.wav", 1 );

			//��ũ����
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_MOVE1,           "Data\\Sound\\w35\\darkelf_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_MOVE2,           "Data\\Sound\\w35\\darkelf_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_ATTACK1,         "Data\\Sound\\w35\\darkelf_at1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_ATTACK2,         "Data\\Sound\\w35\\darkelf_at2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_DIE,             "Data\\Sound\\w35\\darkelf_death.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_SKILL1,          "Data\\Sound\\w35\\darkelf_skill1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DARKELF_SKILL2,          "Data\\Sound\\w35\\darkelf_skill2.wav", 1 );

			//�������Ǹ�
			LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_MOVE1,		 "Data\\Sound\\w35\\dths_idle1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_MOVE2,		 "Data\\Sound\\w35\\dths_idle2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_ATTACK1,     "Data\\Sound\\w35\\dths_at1.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_ATTACK2,     "Data\\Sound\\w35\\dths_at2.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_DIE,         "Data\\Sound\\w35\\dths_deat.wav", 1 );

			//�߸���Ÿ
			LoadWaveFile ( SOUND_CRY1ST_TANKER_ATTACK1,           "Data\\Sound\\w35\\tanker_attack.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_TANKER_DIE,			      "Data\\Sound\\w35\\tanker_death.wav", 1 );

			//��ȯȿ�� ����
			LoadWaveFile ( SOUND_CRY1ST_SUMMON,					  "Data\\Sound\\w35\\spawn_single.wav", 1 );

			//���� ���н� ����
			LoadWaveFile ( SOUND_CRY1ST_SUCCESS,				  "Data\\Sound\\w35\\CW_win.wav", 1 );
			LoadWaveFile ( SOUND_CRY1ST_FAILED,					  "Data\\Sound\\w35\\CW_lose.wav", 1 );
		}
		break;
    case WD_30BATTLECASTLE :
		LoadBitmap( "Effect\\Map_Smoke1.jpg" ,BITMAP_CHROME+2, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "Effect\\Map_Smoke2.tga" ,BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "World31\\Map1.jpg" ,BITMAP_INTERFACE_MAP+1, GL_LINEAR, GL_CLAMP );    //  ������ ����.
		LoadBitmap( "World31\\Map2.jpg" ,BITMAP_INTERFACE_MAP+2, GL_LINEAR, GL_CLAMP );    //  ������ ����.

        //  ȿ���� �ε�.
        LoadWaveFile ( SOUND_BC_AMBIENT        ,   "Data\\Sound\\BattleCastle\\aSiegeAmbi.wav", 1, true );      //  ��� ȿ���� ( ����� ).
        LoadWaveFile ( SOUND_BC_AMBIENT_BATTLE1,   "Data\\Sound\\BattleCastle\\RanAmbi1.wav", 1, true );        //  ��� ȿ���� ( ���� ).  
        LoadWaveFile ( SOUND_BC_AMBIENT_BATTLE2,   "Data\\Sound\\BattleCastle\\RanAmbi2.wav", 1, true );        //  ��� ȿ���� ( ���� ).  
        LoadWaveFile ( SOUND_BC_AMBIENT_BATTLE3,   "Data\\Sound\\BattleCastle\\RanAmbi3.wav", 1, true );        //  ��� ȿ���� ( ���� ).  
        LoadWaveFile ( SOUND_BC_AMBIENT_BATTLE4,   "Data\\Sound\\BattleCastle\\RanAmbi4.wav", 1, true );        //  ��� ȿ���� ( ���� ).  
        LoadWaveFile ( SOUND_BC_AMBIENT_BATTLE5,   "Data\\Sound\\BattleCastle\\RanAmbi5.wav", 1, true );        //  ��� ȿ���� ( ���� ).  
        LoadWaveFile ( SOUND_BC_GUARD_STONE_DIS,   "Data\\Sound\\BattleCastle\\oGuardStoneDis.wav", 1, true );  //  ��ȣ���� �ı�.         
        LoadWaveFile ( SOUND_BC_SHIELD_SPACE_DIS,  "Data\\Sound\\BattleCastle\\oProtectionDis.wav", 1, true );  //  �� �ı�.           
        LoadWaveFile ( SOUND_BC_CATAPULT_ATTACK,   "Data\\Sound\\BattleCastle\\oSWFire.wav", 1, true  );         //  �������� �߻�.         
        LoadWaveFile ( SOUND_BC_CATAPULT_HIT   ,   "Data\\Sound\\BattleCastle\\oSWHitG.wav", MAX_CHANNEL, true );//  �������� ����.
        LoadWaveFile ( SOUND_BC_WALL_HIT       ,   "Data\\Sound\\BattleCastle\\oSWHit.wav", MAX_CHANNEL, true );//  ���� ����.

        LoadWaveFile ( SOUND_BC_GATE_OPEN      ,   "Data\\Sound\\BattleCastle\\oCDoorMove.wav", 1, true  );      //  ���� �ݱ�/����
        LoadWaveFile ( SOUND_BC_GUARDIAN_ATTACK,   "Data\\Sound\\BattleCastle\\mGMercAttack.wav", 1, true  );    //  ����� ����.
        LoadWaveFile ( SOUND_BMS_STUN          ,   "Data\\Sound\\BattleCastle\\sDStun.wav", MAX_CHANNEL, true  );          //  ���� �ߵ�.             
        LoadWaveFile ( SOUND_BMS_STUN_REMOVAL  ,   "Data\\Sound\\BattleCastle\\sDStunCancel.wav", MAX_CHANNEL, true   );    //  ���� ���� �ߵ�.        
        LoadWaveFile ( SOUND_BMS_MANA          ,   "Data\\Sound\\BattleCastle\\sDSwllMana.wav", MAX_CHANNEL, true   );      //  ���� ���� �ߵ�.        
        LoadWaveFile ( SOUND_BMS_INVISIBLE     ,   "Data\\Sound\\BattleCastle\\sDTrans.wav", MAX_CHANNEL , true  );         //  ���� �ߵ�.             
        LoadWaveFile ( SOUND_BMS_VISIBLE       ,   "Data\\Sound\\BattleCastle\\sDStunCancel.wav", MAX_CHANNEL, true   );    //  ���� ����.             
        LoadWaveFile ( SOUND_BMS_MAGIC_REMOVAL ,   "Data\\Sound\\BattleCastle\\sDMagicCancel.wav", MAX_CHANNEL, true   );   //  ���� ����.             
        LoadWaveFile ( SOUND_BCS_RUSH          ,   "Data\\Sound\\BattleCastle\\sCHaveyBlow.wav", MAX_CHANNEL, true   );     //  ��� ���� ��ų.        
        LoadWaveFile ( SOUND_BCS_JAVELIN       ,   "Data\\Sound\\BattleCastle\\sCShockWave.wav", MAX_CHANNEL, true   );     //  ���� ǥâ ��ų.        
        LoadWaveFile ( SOUND_BCS_DEEP_IMPACT   ,   "Data\\Sound\\BattleCastle\\sCFireArrow.wav", MAX_CHANNEL, true  );     //  ���� ����Ʈ ��.        
        LoadWaveFile ( SOUND_BCS_DEATH_CANON   ,   "Data\\Sound\\BattleCastle\\sCMW.wav", MAX_CHANNEL, true  );            //  ���˻� ������.         
        LoadWaveFile ( SOUND_BCS_ONE_FLASH     ,   "Data\\Sound\\BattleCastle\\sCColdAttack.wav", MAX_CHANNEL, true  );    //  ���˻� �ϼ�.           
        LoadWaveFile ( SOUND_BCS_SPACE_SPLIT   ,   "Data\\Sound\\BattleCastle\\sCDarkAttack.wav", MAX_CHANNEL, true  );    //  ��ũ�ε� ���� ������.  
        LoadWaveFile ( SOUND_BCS_BRAND_OF_SKILL,   "Data\\Sound\\BattleCastle\\sCDarkAssist.wav", 1, true  );    //  ��ũ�ε� ���� ��ų.    
        break;

	case WD_31HUNTING_GROUND:
		//. �ݵ�� �ڽ� : 2004/11/05
		AccessModel(MODEL_BUTTERFLY01	 ,"Data\\Object1\\","Butterfly",1);
		OpenTexture(MODEL_BUTTERFLY01	 ,"Object1\\");

		LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD ,GL_LINEAR,GL_CLAMP);
		LoadBitmap("Monster\\bossmap1_R.jpg"	  ,BITMAP_HGBOSS_PATTERN ,GL_LINEAR,GL_CLAMP);
		LoadBitmap("Monster\\bosswing.tga",BITMAP_HGBOSS_WING  ,GL_NEAREST,GL_REPEAT);
		LoadBitmap("Skill\\bossrock1_R.JPG" ,BITMAP_FISSURE_FIRE ,GL_LINEAR,GL_CLAMP);

		LoadWaveFile ( SOUND_BC_HUNTINGGROUND_AMBIENT,    "Data\\Sound\\w31\\aW31.wav", 1, true );      //  ��� ȿ����

		LoadWaveFile ( SOUND_BC_AXEWARRIOR_MOVE1,         "Data\\Sound\\w31\\mAWidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_AXEWARRIOR_MOVE2,         "Data\\Sound\\w31\\mAWidle2.wav", 1 );
		LoadWaveFile ( SOUND_BC_AXEWARRIOR_ATTACK1,       "Data\\Sound\\w31\\mAWattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_AXEWARRIOR_ATTACK2,       "Data\\Sound\\w31\\mAWattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_AXEWARRIOR_DIE,	          "Data\\Sound\\w31\\mAWdeath.wav", 1 );
		LoadWaveFile ( SOUND_BC_LIZARDWARRIOR_MOVE1,      "Data\\Sound\\w31\\mLWidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_LIZARDWARRIOR_MOVE2,      "Data\\Sound\\w31\\mLWidle2.wav", 1 );
		LoadWaveFile ( SOUND_BC_LIZARDWARRIOR_ATTACK1,    "Data\\Sound\\w31\\mLWattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_LIZARDWARRIOR_ATTACK2,    "Data\\Sound\\w31\\mLWattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_LIZARDWARRIOR_DIE,        "Data\\Sound\\w31\\mLWdeath.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_MOVE1,      "Data\\Sound\\w31\\mPGidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_MOVE2,      "Data\\Sound\\w31\\mPGidle2.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_ATTACK1,    "Data\\Sound\\w31\\mPGattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_ATTACK2,    "Data\\Sound\\w31\\mPGattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_ATTACK3,    "Data\\Sound\\w31\\mPGeff1.wav", 1 );
		LoadWaveFile ( SOUND_BC_POISONGOLEM_DIE,        "Data\\Sound\\w31\\mPGdeath.wav", 1 );
		LoadWaveFile ( SOUND_BC_QUEENBEE_MOVE1,           "Data\\Sound\\w31\\mQBidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_QUEENBEE_MOVE2,           "Data\\Sound\\w31\\mQBidle2.wav", 1 );
		LoadWaveFile ( SOUND_BC_QUEENBEE_ATTACK1,         "Data\\Sound\\w31\\mQBattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_QUEENBEE_ATTACK2,         "Data\\Sound\\w31\\mQBattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_QUEENBEE_DIE,             "Data\\Sound\\w31\\mQBdeath.wav", 1 );
		LoadWaveFile ( SOUND_BC_FIREGOLEM_MOVE1,           "Data\\Sound\\w31\\mFGidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_FIREGOLEM_MOVE2,           "Data\\Sound\\w31\\mFGidle2.wav", 1 );
		LoadWaveFile ( SOUND_BC_FIREGOLEM_ATTACK1,         "Data\\Sound\\w31\\mFGattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_FIREGOLEM_ATTACK2,         "Data\\Sound\\w31\\mFGattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_FIREGOLEM_DIE,             "Data\\Sound\\w31\\mFGdeath.wav", 1 );
		LoadWaveFile ( SOUND_BC_EROHIM_ENTER,           "Data\\Sound\\w31\\mELOidle1.wav", 1 );
		LoadWaveFile ( SOUND_BC_EROHIM_ATTACK1,         "Data\\Sound\\w31\\mELOattack1.wav", 1 );
		LoadWaveFile ( SOUND_BC_EROHIM_ATTACK2,         "Data\\Sound\\w31\\mELOattack2.wav", 1 );
		LoadWaveFile ( SOUND_BC_EROHIM_ATTACK3,         "Data\\Sound\\w31\\mELOeff1.wav", 1 );
		LoadWaveFile ( SOUND_BC_EROHIM_DIE,             "Data\\Sound\\w31\\mELOdeath.wav", 1 );
		break;
	case WD_33AIDA:
		AccessModel(MODEL_BUTTERFLY01	 ,"Data\\Object1\\","Butterfly",1);
		OpenTexture(MODEL_BUTTERFLY01	 ,"Object1\\");
		AccessModel(MODEL_TREE_ATTACK	 ,"Data\\Object34\\","tree_eff");
		OpenTexture(MODEL_TREE_ATTACK	 ,"Object34\\");
		AccessModel(MODEL_BUG01+1         ,"Data\\Object9\\","Bug",2);
		OpenTexture(MODEL_BUG01+1		  ,"Object9\\");

		LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD ,GL_LINEAR,GL_CLAMP);

		LoadWaveFile ( SOUND_AIDA_AMBIENT,    "Data\\Sound\\w34\\aida_ambi.wav", 1, true );      //  ��� ȿ����
		//����
		LoadWaveFile ( SOUND_AIDA_BLUEGOLEM_MOVE1,             "Data\\Sound\\w34\\bg_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_BLUEGOLEM_MOVE2,             "Data\\Sound\\w34\\bg_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_BLUEGOLEM_ATTACK1,           "Data\\Sound\\w34\\bg_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_BLUEGOLEM_ATTACK2,           "Data\\Sound\\w34\\bg_attack2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_BLUEGOLEM_DIE,               "Data\\Sound\\w34\\bg_death.wav", 1 );

		//�������̴�
		LoadWaveFile ( SOUND_AIDA_DEATHRAIDER_MOVE1,           "Data\\Sound\\w34\\dr_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHRAIDER_MOVE2,           "Data\\Sound\\w34\\dr_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHRAIDER_ATTACK1,         "Data\\Sound\\w34\\dr_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHRAIDER_ATTACK2,         "Data\\Sound\\w34\\dr_attack2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHRAIDER_DIE,             "Data\\Sound\\w34\\dr_death.wav", 1 );

		//����Ʈ��
		LoadWaveFile ( SOUND_AIDA_DEATHTREE_MOVE1,             "Data\\Sound\\w34\\dt_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHTREE_MOVE2,             "Data\\Sound\\w34\\dt_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHTREE_ATTACK1,           "Data\\Sound\\w34\\dt_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHTREE_ATTACK2,           "Data\\Sound\\w34\\dt_attack2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_DEATHTREE_DIE,               "Data\\Sound\\w34\\dt_death.wav", 1 );

		//������Ʈ��ũ
		LoadWaveFile ( SOUND_AIDA_FORESTORC_MOVE1,             "Data\\Sound\\w34\\fo_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_FORESTORC_MOVE2,             "Data\\Sound\\w34\\fo_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_FORESTORC_ATTACK1,           "Data\\Sound\\w34\\fo_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_FORESTORC_ATTACK2,           "Data\\Sound\\w34\\fo_attack2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_FORESTORC_DIE,               "Data\\Sound\\w34\\fo_death.wav", 1 );

		//�︶�̳�
		LoadWaveFile ( SOUND_AIDA_HELL_MOVE1,				   "Data\\Sound\\w34\\hm_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_HELL_MOVE2,				   "Data\\Sound\\w34\\hm_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_HELL_ATTACK1,			  	   "Data\\Sound\\w34\\hm_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_HELL_ATTACK2,			  	   "Data\\Sound\\w34\\hm_firelay.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_HELL_ATTACK3,			  	   "Data\\Sound\\w34\\hm_bloodywind.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_HELL_DIE,					   "Data\\Sound\\w34\\hm_death.wav", 1 );

		//��ġ��
		LoadWaveFile ( SOUND_AIDA_WITCHQUEEN_MOVE1,            "Data\\Sound\\w34\\wq_idle1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_WITCHQUEEN_MOVE2,            "Data\\Sound\\w34\\wq_idle2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_WITCHQUEEN_ATTACK1,          "Data\\Sound\\w34\\wq_attack1.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_WITCHQUEEN_ATTACK2,          "Data\\Sound\\w34\\wq_attack2.wav", 1 );
		LoadWaveFile ( SOUND_AIDA_WITCHQUEEN_DIE,              "Data\\Sound\\w34\\wq_death.wav", 1 );
		LoadWaveFile ( SOUND_CHAOS_THUNDER01,				   "Data\\Sound\\eElec1.wav", 1 );
		LoadWaveFile ( SOUND_CHAOS_THUNDER02,				   "Data\\Sound\\eElec2.wav", 1 );
		
		break;

#ifdef YDG_ADD_MAP_DOPPELGANGER4
	case WD_68DOPPLEGANGER4:
		LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD,GL_LINEAR,GL_CLAMP);
		LoadBitmap("effect\\water.jpg", BITMAP_TWINTAIL_WATER, GL_LINEAR, GL_CLAMP);
#endif	// YDG_ADD_MAP_DOPPELGANGER4
	case WD_37KANTURU_1ST:
		AccessModel(MODEL_BUTTERFLY01	 ,"Data\\Object1\\","Butterfly",1);
		OpenTexture(MODEL_BUTTERFLY01	 ,"Object1\\");

		// ��� ȿ����.
		LoadWaveFile(SOUND_KANTURU_1ST_BG_WATERFALL,	"Data\\Sound\\w37\\kan_ruin_waterfall.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BG_ELEC,			"Data\\Sound\\w37\\kan_ruin_elec.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BG_WHEEL,		"Data\\Sound\\w37\\kan_ruin_wheel.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BG_PLANT,		"Data\\Sound\\w37\\kan_ruin_plant.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BG_GLOBAL,		"Data\\Sound\\w37\\kan_ruin_global.wav", 1);

		// ����Ŀ.
		LoadWaveFile(SOUND_KANTURU_1ST_BER_MOVE1,		"Data\\Sound\\w37\\ber_idle-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BER_MOVE2,		"Data\\Sound\\w37\\ber_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BER_ATTACK1,		"Data\\Sound\\w37\\ber_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BER_ATTACK2,		"Data\\Sound\\w37\\ber_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BER_DIE,			"Data\\Sound\\w37\\ber_death.wav", 1);

		// �ⰣƼ��.
		LoadWaveFile(SOUND_KANTURU_1ST_GIGAN_MOVE1,		"Data\\Sound\\w37\\gigan_idle-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GIGAN_ATTACK1,	"Data\\Sound\\w37\\gigan_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GIGAN_ATTACK2,	"Data\\Sound\\w37\\gigan_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GIGAN_DIE,		"Data\\Sound\\w37\\gigan_death.wav", 1);

		// ������̴�.
		LoadWaveFile(SOUND_KANTURU_1ST_GENO_MOVE1,		"Data\\Sound\\w37\\geno_idle-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GENO_MOVE2,		"Data\\Sound\\w37\\geno_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GENO_ATTACK1,	"Data\\Sound\\w37\\geno_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GENO_ATTACK2,	"Data\\Sound\\w37\\geno_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_GENO_DIE,		"Data\\Sound\\w37\\geno_death.wav", 1);

		LoadWaveFile(SOUND_KANTURU_1ST_KENTA_MOVE1		, "Data\\Sound\\w37\\kenta_idle-01.wav", 1);				
		LoadWaveFile(SOUND_KANTURU_1ST_KENTA_MOVE2		, "Data\\Sound\\w37\\kenta_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_KENTA_ATTACK1	, "Data\\Sound\\w37\\kenta_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_KENTA_ATTACK2	, "Data\\Sound\\w37\\kenta_skill-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_KENTA_DIE		, "Data\\Sound\\w37\\kenta_death.wav", 1);

		LoadWaveFile(SOUND_KANTURU_1ST_BLADE_MOVE1	,	  "Data\\Sound\\w37\\blade_idle-01.wav", 1);					
		LoadWaveFile(SOUND_KANTURU_1ST_BLADE_MOVE2	,		"Data\\Sound\\w37\\blade_idle-02.wav", 1);				
		LoadWaveFile(SOUND_KANTURU_1ST_BLADE_ATTACK1	,"Data\\Sound\\w37\\blade_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BLADE_ATTACK2	,"Data\\Sound\\w37\\blade_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_BLADE_DIE		,"Data\\Sound\\w37\\blade_death.wav", 1);

		LoadWaveFile(SOUND_KANTURU_1ST_SATI_MOVE1	,"Data\\Sound\\w37\\sati_idle-01.wav", 1);					
		LoadWaveFile(SOUND_KANTURU_1ST_SATI_MOVE2	,"Data\\Sound\\w37\\sati_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SATI_ATTACK1	,"Data\\Sound\\w37\\sati_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SATI_ATTACK2	,"Data\\Sound\\w37\\sati_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SATI_DIE		,"Data\\Sound\\w37\\sati_death.wav", 1);
		
		//���ø��� ����
		LoadWaveFile(SOUND_KANTURU_1ST_SWOLF_MOVE1	,"Data\\Sound\\w37\\swolf_idle-01.wav", 1);					
		LoadWaveFile(SOUND_KANTURU_1ST_SWOLF_MOVE2	,"Data\\Sound\\w37\\swolf_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SWOLF_ATTACK1	,"Data\\Sound\\w37\\swolf_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SWOLF_ATTACK2	,"Data\\Sound\\w37\\swolf_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_SWOLF_DIE		,"Data\\Sound\\w37\\swolf_death.wav", 1);

		//���̾� ���̴�
		LoadWaveFile(SOUND_KANTURU_1ST_IR_MOVE1	,"Data\\Sound\\w37\\ir_idle-01.wav", 1);					
		LoadWaveFile(SOUND_KANTURU_1ST_IR_MOVE2	,"Data\\Sound\\w37\\ir_idle-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_IR_ATTACK1	,"Data\\Sound\\w37\\ir_attack-01.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_IR_ATTACK2	,"Data\\Sound\\w37\\ir_attack-02.wav", 1);
		LoadWaveFile(SOUND_KANTURU_1ST_IR_DIE		,"Data\\Sound\\w37\\ir_death.wav", 1);		

		break;

	case WD_38KANTURU_2ND:
		{
			g_TrapCanon.Open_TrapCanon();

			AccessModel(MODEL_STORM2		,"Data\\SKill\\","boswind");
			OpenTexture(MODEL_STORM2		,"SKill\\");
			AccessModel(MODEL_STORM3		,"Data\\Skill\\","mayatonedo");
			OpenTexture(MODEL_STORM3		,"Skill\\");

			LoadBitmap("Object39\\k_effect_01.JPG"		, BITMAP_KANTURU_2ND_EFFECT1, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Npc\\khs_kan2gate001.jpg"	, BITMAP_KANTURU_2ND_NPC1, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Npc\\khs_kan2gate003.jpg"	, BITMAP_KANTURU_2ND_NPC2, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Npc\\khs_kan2gate004.jpg"	, BITMAP_KANTURU_2ND_NPC3, GL_LINEAR, GL_CLAMP);
			
			// ����
			// ȯ�� ����
			LoadWaveFile(SOUND_KANTURU_2ND_MAPSOUND_GEAR,		"Data\\Sound\\w38\\kan_relic_gear.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_MAPSOUND_INCUBATOR,	"Data\\Sound\\w38\\kan_relic_incubator.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_MAPSOUND_HOLE,		"Data\\Sound\\w38\\kan_relic_hole.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_MAPSOUND_GLOBAL,		"Data\\Sound\\w38\\kan_relic_global.wav", 1);
			
			// �丣�ҳ�
			LoadWaveFile(SOUND_KANTURU_2ND_PERSO_MOVE1,		"Data\\Sound\\w38\\perso_idle-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_PERSO_MOVE2,		"Data\\Sound\\w38\\perso_idle-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_PERSO_ATTACK1,	"Data\\Sound\\w38\\perso_attack-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_PERSO_ATTACK2,	"Data\\Sound\\w38\\perso_attack-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_PERSO_DIE,		"Data\\Sound\\w38\\perso_death.wav", 1);

			// Ʈ������.
			LoadWaveFile(SOUND_KANTURU_2ND_TWIN_MOVE1,		"Data\\Sound\\w38\\twin_idle-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_TWIN_MOVE2,		"Data\\Sound\\w38\\twin_idle-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_TWIN_ATTACK1,	"Data\\Sound\\w38\\twin_attack-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_TWIN_ATTACK2,	"Data\\Sound\\w38\\twin_attack-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_TWIN_DIE,		"Data\\Sound\\w38\\twin_death.wav", 1);

			// �巹���Ǿ�.
			LoadWaveFile(SOUND_KANTURU_2ND_DRED_MOVE1,		"Data\\Sound\\w38\\dred_idle-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_DRED_MOVE2,		"Data\\Sound\\w38\\dred_idle-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_DRED_ATTACK1,	"Data\\Sound\\w38\\dred_attack-01.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_DRED_ATTACK2,	"Data\\Sound\\w38\\dred_attack-02.wav", 1);
			LoadWaveFile(SOUND_KANTURU_2ND_DRED_DIE,		"Data\\Sound\\w38\\dred_death.wav", 1);
		}
		break;
	case WD_39KANTURU_3RD:
		{
			LoadBitmap("Monster\\nightmare_R.jpg"			, BITMAP_NIGHTMARE_EFFECT1, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Monster\\nightmaresward_R.jpg"	, BITMAP_NIGHTMARE_EFFECT2, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Monster\\nightmare_cloth.tga"		, BITMAP_NIGHTMARE_ROBE);
			LoadBitmap("Object40\\maya01_R.jpg"			, BITMAP_MAYA_BODY, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Object40\\Mtowereffe.JPG"			, BITMAP_KANTURU3RD_OBJECT, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\bluering0001_R.jpg"		, BITMAP_ENERGY_RING, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\bluewave0001_R.jpg"		, BITMAP_ENERGY_FIELD, GL_LINEAR, GL_CLAMP);

			AccessModel(MODEL_STORM2		,"Data\\SKill\\","boswind");
			OpenTexture(MODEL_STORM2		,"SKill\\");
#ifndef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			AccessModel(MODEL_SUMMON		,"Data\\SKill\\","nightmaresum");
			OpenTexture(MODEL_SUMMON		,"SKill\\");
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			AccessModel(MODEL_STORM3		,"Data\\Skill\\","mayatonedo");
			OpenTexture(MODEL_STORM3		,"Skill\\");
			AccessModel(MODEL_MAYASTAR		,"Data\\Skill\\","arrowsre05");
			OpenTexture(MODEL_MAYASTAR		,"Skill\\");
			AccessModel(MODEL_MAYASTONE1	,"Data\\Skill\\","mayastone01");
			OpenTexture(MODEL_MAYASTONE1	,"Skill\\");
			AccessModel(MODEL_MAYASTONE2	,"Data\\Skill\\","mayastone02");
			OpenTexture(MODEL_MAYASTONE2	,"Skill\\");
			AccessModel(MODEL_MAYASTONE3	,"Data\\Skill\\","mayastone03");
			OpenTexture(MODEL_MAYASTONE3	,"Skill\\");
			AccessModel(MODEL_MAYASTONE4	,"Data\\Skill\\","mayastone04");
			OpenTexture(MODEL_MAYASTONE4	,"Skill\\");
			AccessModel(MODEL_MAYASTONE5	,"Data\\Skill\\","mayastone05");
			OpenTexture(MODEL_MAYASTONE5	,"Skill\\");
			AccessModel(MODEL_MAYASTONEFIRE	,"Data\\Skill\\","mayastonebluefire");
			OpenTexture(MODEL_MAYASTONEFIRE	,"Skill\\");
			AccessModel(MODEL_MAYAHANDSKILL	,"Data\\Skill\\","hendlight02");
			OpenTexture(MODEL_MAYAHANDSKILL	,"Skill\\");


			// ����
			LoadWaveFile ( SOUND_KANTURU_3RD_MAYA_INTRO,          "Data\\Sound\\w39\\maya_intro.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAYA_END,            "Data\\Sound\\w39\\maya_death.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAYA_STORM,          "Data\\Sound\\w39\\maya_storm.wav", 1 );

			// ���߼�
			LoadWaveFile ( SOUND_KANTURU_3RD_MAYAHAND_ATTACK1,    "Data\\Sound\\w39\\maya_hand_attack-01.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAYAHAND_ATTACK2,	  "Data\\Sound\\w39\\maya_hand_attack-02.wav", 1 );

			// ����Ʈ�޾�
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_INTRO,     "Data\\Sound\\w39\\nightmare_intro.wav", 1 );

			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_ATT1,     "Data\\Sound\\w39\\nightmare_attack-01.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_ATT2,     "Data\\Sound\\w39\\nightmare_skill-01", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_ATT3,     "Data\\Sound\\w39\\nightmare_skill-02", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_ATT4,     "Data\\Sound\\w39\\nightmare_skill-03", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_DIE,      "Data\\Sound\\w39\\nightmare_death.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_IDLE1,    "Data\\Sound\\w39\\nightmare_idle-01.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_IDLE2,    "Data\\Sound\\w39\\nightmare_idle-02.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_NIGHTMARE_TELE,     "Data\\Sound\\w39\\nightmare_tele.wav", 1 );


			// ĭ����3�� ������Ʈ ȿ����
			LoadWaveFile ( SOUND_KANTURU_3RD_MAP_SOUND01,          "Data\\Sound\\w39\\kan_boss_crystal.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAP_SOUND02,          "Data\\Sound\\w39\\kan_boss_disfield.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAP_SOUND03,          "Data\\Sound\\w39\\kan_boss_field.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAP_SOUND04,          "Data\\Sound\\w39\\kan_boss_gear.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_MAP_SOUND05,          "Data\\Sound\\w39\\kan_boss_incubator.wav", 1 );
			LoadWaveFile ( SOUND_KANTURU_3RD_AMBIENT,			   "Data\\Sound\\w39\\kan_boss_global.wav", 1 );
		}
		break;
	case WD_45CURSEDTEMPLE_LV1:
	case WD_45CURSEDTEMPLE_LV2:
	case WD_45CURSEDTEMPLE_LV3:	
	case WD_45CURSEDTEMPLE_LV4:	
	case WD_45CURSEDTEMPLE_LV5:	
	case WD_45CURSEDTEMPLE_LV6:
		{
			LoadBitmap("Effect\\clouds.jpg", BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\clud64.jpg", BITMAP_CLUD64, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\ghosteffect01.jpg", BITMAP_GHOST_CLOUD1, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\ghosteffect02.jpg", BITMAP_GHOST_CLOUD2, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\torchfire.jpg", BITMAP_TORCH_FIRE, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\clouds2.jpg", BITMAP_EVENT_CLOUD, GL_LINEAR, GL_CLAMP);
			
			//EFFECT
			AccessModel(MODEL_FALL_STONE_EFFECT, "Data\\Object47\\", "Stoneeffec");
			OpenTexture(MODEL_FALL_STONE_EFFECT, "Object47\\");

			//game system sound
			LoadWaveFile ( SOUND_CURSEDTEMPLE_GAMESYSTEM1,     "Data\\Sound\\w47\\cursedtemple_start01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_GAMESYSTEM2,     "Data\\Sound\\w47\\cursedtemple_statue01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_GAMESYSTEM3,     "Data\\Sound\\w47\\cursedtemple_holy01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_GAMESYSTEM4,     "Data\\Sound\\w47\\cursedtemple_score01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_GAMESYSTEM5,     "Data\\Sound\\w47\\cursedtemple_end01.wav", 1 );

			//moster 1 - 2 effect sound
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER1_IDLE,   "Data\\Sound\\w47\\cursedtemple_idle01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER_MOVE,    "Data\\Sound\\w47\\cursedtemple_move01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER1_DAMAGE, "Data\\Sound\\w47\\cursedtemple_damage01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER1_DEATH,  "Data\\Sound\\w47\\cursedtemple_death01.wav", 1 );

			//moster 3 effect sound
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER2_IDLE,    "Data\\Sound\\w47\\cursedtemple_idle02.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER2_ATTACK, "Data\\Sound\\w47\\cursedtemple_Attack01.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER2_DAMAGE,	"Data\\Sound\\w47\\cursedtemple_damage02.wav", 1 );
			LoadWaveFile ( SOUND_CURSEDTEMPLE_MONSTER2_DEATH,	"Data\\Sound\\w47\\cursedtemple_death02.wav", 1 );
		}
		break;
	case WD_41CHANGEUP3RD_1ST:
		LoadBitmap("Effect\\clouds.jpg" , BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\firered.jpg" , BITMAP_FIRE_RED, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\FireSnuff.jpg", BITMAP_FIRE_SNUFF, GL_LINEAR, GL_CLAMP);      //  �Ҿ�.
		
		// ��� ȿ����.
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_CAGE1,			"Data\\Sound\\w42\\cage01.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_CAGE2,			"Data\\Sound\\w42\\cage02.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_VOLCANO,		"Data\\Sound\\w42\\volcano.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_FIREPILLAR,		"Data\\Sound\\w42\\firepillar.wav", 1);
		//�߶�
		LoadWaveFile ( SOUND_CRY1ST_BALRAM_MOVE1,             "Data\\Sound\\w35\\balram_idle1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_BALRAM_MOVE2,             "Data\\Sound\\w35\\balram_idle2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_BALRAM_ATTACK1,           "Data\\Sound\\w35\\balram_attack1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_BALRAM_ATTACK2,           "Data\\Sound\\w35\\balram_attack2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_BALRAM_DIE,               "Data\\Sound\\w35\\balram_death.wav", 1 );
		//�������Ǹ�
		LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_MOVE1,		 "Data\\Sound\\w35\\dths_idle1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_MOVE2,		 "Data\\Sound\\w35\\dths_idle2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_ATTACK1,     "Data\\Sound\\w35\\dths_at1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_ATTACK2,     "Data\\Sound\\w35\\dths_at2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_DEATHSPIRIT_DIE,         "Data\\Sound\\w35\\dths_deat.wav", 1 );
		//�Ҷ�
		LoadWaveFile ( SOUND_CRY1ST_SORAM_MOVE1,             "Data\\Sound\\w35\\soram_idle1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_SORAM_MOVE2,             "Data\\Sound\\w35\\soram_idle2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_SORAM_ATTACK1,           "Data\\Sound\\w35\\soram_attack1.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_SORAM_ATTACK2,           "Data\\Sound\\w35\\soram_attack2.wav", 1 );
		LoadWaveFile ( SOUND_CRY1ST_SORAM_DIE,               "Data\\Sound\\w35\\soram_death.wav", 1 );
		break;
	case WD_42CHANGEUP3RD_2ND:
		LoadBitmap("Effect\\clouds.jpg" , BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\firered.jpg" , BITMAP_FIRE_RED, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\FireSnuff.jpg", BITMAP_FIRE_SNUFF, GL_LINEAR, GL_CLAMP);      //  �Ҿ�.

		// ��� ȿ����.
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_CAGE1,			"Data\\Sound\\w42\\cage01.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_CAGE2,			"Data\\Sound\\w42\\cage02.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_VOLCANO,		"Data\\Sound\\w42\\volcano.wav", 1);
		LoadWaveFile(SOUND_3RD_CHANGE_UP_BG_FIREPILLAR,		"Data\\Sound\\w42\\firepillar.wav", 1);
		break;
#ifndef PJH_NEW_SERVER_SELECT_MAP
	case WD_77NEW_LOGIN_SCENE:
	case WD_78NEW_CHARACTER_SCENE:
		if(World == WD_77NEW_LOGIN_SCENE)
		{
			LoadBitmap("Logo\\New_Login_Back01.jpg"         ,BITMAP_LOG_IN+9);
			LoadBitmap("Logo\\New_Login_Back02.jpg"         ,BITMAP_LOG_IN+10);
			LoadBitmap("World78\\bg_b_05.jpg" ,BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT );	// ȭ�� �帮��
			LoadBitmap("World78\\bg_b_08.jpg" ,BITMAP_CHROME+4, GL_LINEAR, GL_REPEAT );	// ȭ�� �帮��
			LoadBitmap("Logo\\MU-logo.tga"         ,BITMAP_LOG_IN+16, GL_LINEAR);
			LoadBitmap("Logo\\MU-logo_g.jpg", BITMAP_LOG_IN+17, GL_LINEAR);

			// ���� �̸� �о����
			OpenMonsterModel(129);
			OpenMonsterModel(130);
			OpenMonsterModel(131);
			OpenMonsterModel(133);
			OpenMonsterModel(135);
		}
		else
		{
			LoadBitmap("Logo\\sos3sky01.jpg"         ,BITMAP_LOG_IN+9);
			LoadBitmap("Logo\\sos3sky02.jpg"         ,BITMAP_LOG_IN+10);
		}
#endif //PJH_NEW_SERVER_SELECT_MAP
		// �̾ 51�� �� �����͵� �д´�.
	case WD_51HOME_6TH_CHAR:
		LoadBitmap("Effect\\clouds.jpg" , BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\Map_Smoke1.jpg"     ,BITMAP_CHROME+2    ,GL_LINEAR,GL_REPEAT);
		AccessModel(MODEL_EAGLE			 ,"Data\\Object52\\","sos3bi01");
		OpenTexture(MODEL_EAGLE			 ,"Object52\\");
		if (World == WD_51HOME_6TH_CHAR)
		{
			AccessModel(MODEL_MAP_TORNADO	 ,"Data\\Object52\\","typhoonall");
			OpenTexture(MODEL_MAP_TORNADO	 ,"Object52\\");

			AccessModel(MODEL_TOTEMGOLEM_PART1	 ,"Data\\Monster\\","totemhead");
			OpenTexture(MODEL_TOTEMGOLEM_PART1	 ,"Monster\\");
			AccessModel(MODEL_TOTEMGOLEM_PART2	 ,"Data\\Monster\\","totembody");
			OpenTexture(MODEL_TOTEMGOLEM_PART2	 ,"Monster\\");
			AccessModel(MODEL_TOTEMGOLEM_PART3	 ,"Data\\Monster\\","totemleft");
			OpenTexture(MODEL_TOTEMGOLEM_PART3	 ,"Monster\\");
			AccessModel(MODEL_TOTEMGOLEM_PART4	 ,"Data\\Monster\\","totemright");
			OpenTexture(MODEL_TOTEMGOLEM_PART4	 ,"Monster\\");
			AccessModel(MODEL_TOTEMGOLEM_PART5	 ,"Data\\Monster\\","totemleg");
			OpenTexture(MODEL_TOTEMGOLEM_PART5	 ,"Monster\\");
			AccessModel(MODEL_TOTEMGOLEM_PART6	 ,"Data\\Monster\\","totemleg2");
			OpenTexture(MODEL_TOTEMGOLEM_PART6	 ,"Monster\\");

			LoadWaveFile ( SOUND_ELBELAND_VILLAGEPROTECTION01,			"Data\\Sound\\w52\\SE_Obj_villageprotection01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_WATERFALLSMALL01,				"Data\\Sound\\w52\\SE_Obj_waterfallsmall01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_WATERWAY01,					"Data\\Sound\\w52\\SE_Obj_waterway01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_ENTERDEVIAS01,				"Data\\Sound\\w52\\SE_Obj_enterdevias01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_WATERSMALL01,					"Data\\Sound\\w52\\SE_Obj_watersmall01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_RAVINE01,						"Data\\Sound\\w52\\SE_Amb_ravine01.wav", 1 );
			LoadWaveFile ( SOUND_ELBELAND_ENTERATLANCE01,				"Data\\Sound\\w52\\SE_Amb_enteratlance01.wav", 1 );
		}
		break;
#ifdef YDG_ADD_MAP_DOPPELGANGER2
	case WD_66DOPPLEGANGER2:
		{
			LoadBitmap("Effect\\clouds.jpg", BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\FireSnuff.jpg", BITMAP_FIRE_SNUFF, GL_LINEAR, GL_CLAMP);
			LoadBitmap("Effect\\WATERFALL2.jpg" ,BITMAP_CHROME3 ,GL_LINEAR,GL_CLAMP);
			LoadBitmap("Effect\\clud64.jpg", BITMAP_CLUD64, GL_LINEAR, GL_CLAMP);
		}
		break;
#endif	// YDG_ADD_MAP_DOPPELGANGER2
#ifdef PBG_ADD_PKFIELD
	case WD_63PK_FIELD:
		{
			AccessModel(MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_HEAD,"Data\\Monster\\","pk_manhead_green");		//�ϻ��� �׸� �Ӹ�
			OpenTexture(MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_HEAD,"Monster\\");

			AccessModel(MODEL_PKFIELD_ASSASSIN_EFFECT_RED_HEAD,"Data\\Monster\\","pk_manhead_red");			//�ϻ��� ���� �Ӹ�
			OpenTexture(MODEL_PKFIELD_ASSASSIN_EFFECT_RED_HEAD,"Monster\\");

			AccessModel(MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_BODY,"Data\\Monster\\","assassin_dieg");		//�ϻ��� �׸� ��
			OpenTexture(MODEL_PKFIELD_ASSASSIN_EFFECT_GREEN_BODY,"Monster\\");
			
			AccessModel(MODEL_PKFIELD_ASSASSIN_EFFECT_RED_BODY,"Data\\Monster\\","assassin_dier");			//�ϻ��� ���� ��
			OpenTexture(MODEL_PKFIELD_ASSASSIN_EFFECT_RED_BODY,"Monster\\");
		}
		break;
#endif //PBG_ADD_PKFIELD
	case WD_56MAP_SWAMP_OF_QUIET:
		LoadBitmap( "Effect\\Map_Smoke1.jpg" ,BITMAP_CHROME+2, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "Effect\\Map_Smoke2.tga" ,BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "Monster\\red_shadows.jpg" ,BITMAP_SHADOW_PAWN_RED, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "Monster\\blue_shadows.jpg" ,BITMAP_SHADOW_KINGHT_BLUE, GL_LINEAR, GL_REPEAT );
		LoadBitmap( "Monster\\green_shadows.jpg" ,BITMAP_SHADOW_ROOK_GREEN, GL_LINEAR, GL_REPEAT );

		AccessModel(MODEL_SHADOW_PAWN_ANKLE_LEFT	 ,"Data\\Monster\\","shadow_pawn_7_ankle_left");
		OpenTexture(MODEL_SHADOW_PAWN_ANKLE_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_ANKLE_RIGHT	 ,"Data\\Monster\\","shadow_pawn_7_ankle_right");
		OpenTexture(MODEL_SHADOW_PAWN_ANKLE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_BELT			 ,"Data\\Monster\\","shadow_pawn_7_belt");
		OpenTexture(MODEL_SHADOW_PAWN_BELT			 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_CHEST			 ,"Data\\Monster\\","shadow_pawn_7_chest");
		OpenTexture(MODEL_SHADOW_PAWN_CHEST			 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_HELMET		 ,"Data\\Monster\\","shadow_pawn_7_helmet");
		OpenTexture(MODEL_SHADOW_PAWN_HELMET		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_KNEE_LEFT		 ,"Data\\Monster\\","shadow_pawn_7_knee_left");
		OpenTexture(MODEL_SHADOW_PAWN_KNEE_LEFT		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_KNEE_RIGHT	 ,"Data\\Monster\\","shadow_pawn_7_knee_right");
		OpenTexture(MODEL_SHADOW_PAWN_KNEE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_WRIST_LEFT	 ,"Data\\Monster\\","shadow_pawn_7_wrist_left");
		OpenTexture(MODEL_SHADOW_PAWN_WRIST_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_PAWN_WRIST_RIGHT	 ,"Data\\Monster\\","shadow_pawn_7_wrist_right");
		OpenTexture(MODEL_SHADOW_PAWN_WRIST_RIGHT	 ,"Monster\\");

		AccessModel(MODEL_SHADOW_KNIGHT_ANKLE_LEFT	 ,"Data\\Monster\\","shadow_knight_7_ankle_left");
		OpenTexture(MODEL_SHADOW_KNIGHT_ANKLE_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_ANKLE_RIGHT	 ,"Data\\Monster\\","shadow_knight_7_ankle_right");
		OpenTexture(MODEL_SHADOW_KNIGHT_ANKLE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_BELT		 ,"Data\\Monster\\","shadow_knight_7_belt");
		OpenTexture(MODEL_SHADOW_KNIGHT_BELT		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_CHEST		 ,"Data\\Monster\\","shadow_knight_7_chest");
		OpenTexture(MODEL_SHADOW_KNIGHT_CHEST		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_HELMET		 ,"Data\\Monster\\","shadow_knight_7_helmet");
		OpenTexture(MODEL_SHADOW_KNIGHT_HELMET		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_KNEE_LEFT	 ,"Data\\Monster\\","shadow_knight_7_knee_left");
		OpenTexture(MODEL_SHADOW_KNIGHT_KNEE_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_KNEE_RIGHT	 ,"Data\\Monster\\","shadow_knight_7_knee_right");
		OpenTexture(MODEL_SHADOW_KNIGHT_KNEE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_WRIST_LEFT	 ,"Data\\Monster\\","shadow_knight_7_wrist_left");
		OpenTexture(MODEL_SHADOW_KNIGHT_WRIST_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_KNIGHT_WRIST_RIGHT	 ,"Data\\Monster\\","shadow_knight_7_wrist_right");
		OpenTexture(MODEL_SHADOW_KNIGHT_WRIST_RIGHT	 ,"Monster\\");

		AccessModel(MODEL_SHADOW_ROOK_ANKLE_LEFT	 ,"Data\\Monster\\","shadow_rock_7_ankle_left");
		OpenTexture(MODEL_SHADOW_ROOK_ANKLE_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_ANKLE_RIGHT	 ,"Data\\Monster\\","shadow_rock_7_ankle_right");
		OpenTexture(MODEL_SHADOW_ROOK_ANKLE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_BELT			 ,"Data\\Monster\\","shadow_rock_7_belt");
		OpenTexture(MODEL_SHADOW_ROOK_BELT			 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_CHEST			 ,"Data\\Monster\\","shadow_rock_7_chest");
		OpenTexture(MODEL_SHADOW_ROOK_CHEST			 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_HELMET		 ,"Data\\Monster\\","shadow_rock_7_helmet");
		OpenTexture(MODEL_SHADOW_ROOK_HELMET		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_KNEE_LEFT		 ,"Data\\Monster\\","shadow_rock_7_knee_left");
		OpenTexture(MODEL_SHADOW_ROOK_KNEE_LEFT		 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_KNEE_RIGHT	 ,"Data\\Monster\\","shadow_rock_7_knee_right");
		OpenTexture(MODEL_SHADOW_ROOK_KNEE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_WRIST_LEFT	 ,"Data\\Monster\\","shadow_rock_7_wrist_left");
		OpenTexture(MODEL_SHADOW_ROOK_WRIST_LEFT	 ,"Monster\\");
		AccessModel(MODEL_SHADOW_ROOK_WRIST_RIGHT	 ,"Data\\Monster\\","shadow_rock_7_wrist_right");
		OpenTexture(MODEL_SHADOW_ROOK_WRIST_RIGHT	 ,"Monster\\");

#ifdef LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET
		AccessModel(MODEL_EX01_SHADOW_MASTER_ANKLE_LEFT	 ,"Data\\Monster\\","ex01shadow_rock_7_ankle_left");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_ANKLE_LEFT	 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_ANKLE_RIGHT	 ,"Data\\Monster\\","ex01shadow_rock_7_ankle_right");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_ANKLE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_BELT			 ,"Data\\Monster\\","ex01shadow_rock_7_belt");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_BELT			 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_CHEST			 ,"Data\\Monster\\","ex01shadow_rock_7_chest");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_CHEST			 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_HELMET		 ,"Data\\Monster\\","ex01shadow_rock_7_helmet");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_HELMET		 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_KNEE_LEFT		 ,"Data\\Monster\\","ex01shadow_rock_7_knee_left");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_KNEE_LEFT		 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_KNEE_RIGHT	 ,"Data\\Monster\\","ex01shadow_rock_7_knee_right");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_KNEE_RIGHT	 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_WRIST_LEFT	 ,"Data\\Monster\\","ex01shadow_rock_7_wrist_left");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_WRIST_LEFT	 ,"Monster\\");
		AccessModel(MODEL_EX01_SHADOW_MASTER_WRIST_RIGHT	 ,"Data\\Monster\\","ex01shadow_rock_7_wrist_right");
		OpenTexture(MODEL_EX01_SHADOW_MASTER_WRIST_RIGHT	 ,"Monster\\");
#endif // LDS_EXTENSIONMAP_MONSTERS_SWAMPOFQUIET

		break;
#ifdef YDG_ADD_MAP_DOPPELGANGER1
	case WD_65DOPPLEGANGER1:	// ��Ŭ���� ���̽�
		LoadBitmap("Effect\\clouds.jpg", BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\Map_Smoke1.jpg", BITMAP_CHROME+2, GL_LINEAR, GL_REPEAT);
		LoadBitmap("Object9\\sand02.jpg", BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT);
		LoadBitmap("Effect\\Chrome08.jpg", BITMAP_CHROME8, GL_LINEAR, GL_CLAMP);
		break;
#endif	// YDG_ADD_MAP_DOPPELGANGER1
#ifdef CSK_ADD_MAP_ICECITY
	case WD_57ICECITY:
	case WD_58ICECITY_BOSS:	
		LoadBitmap("Effect\\Map_Smoke1.jpg", BITMAP_CHROME+2, GL_LINEAR, GL_REPEAT);
		LoadBitmap("Object9\\sand02.jpg", BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT);
		LoadBitmap("Effect\\Chrome08.jpg", BITMAP_CHROME8, GL_LINEAR, GL_CLAMP);
		
		AccessModel(MODEL_FALL_STONE_EFFECT, "Data\\Object47\\", "Stoneeffec");
		OpenTexture(MODEL_FALL_STONE_EFFECT, "Object47\\");

		AccessModel(MODEL_WARP	 ,"Data\\Npc\\","warp01");
		AccessModel(MODEL_WARP2	 ,"Data\\Npc\\","warp02");
		AccessModel(MODEL_WARP3	 ,"Data\\Npc\\","warp03");
		OpenTexture(MODEL_WARP	 ,"Npc\\");
		OpenTexture(MODEL_WARP2	 ,"Npc\\");
		OpenTexture(MODEL_WARP3	 ,"Npc\\");

		AccessModel(MODEL_WARP4  ,"Data\\Npc\\","warp01");
		AccessModel(MODEL_WARP5	 ,"Data\\Npc\\","warp02");
		AccessModel(MODEL_WARP6	 ,"Data\\Npc\\","warp03");
		OpenTexture(MODEL_WARP4  ,"Npc\\");
		OpenTexture(MODEL_WARP5	 ,"Npc\\");
		OpenTexture(MODEL_WARP6	 ,"Npc\\");
		
		AccessModel(MODEL_SUMMON ,"Data\\SKill\\", "nightmaresum");
		OpenTexture(MODEL_SUMMON ,"SKill\\");
		AccessModel(MODEL_STORM2		,"Data\\SKill\\","boswind");
		OpenTexture(MODEL_STORM2		,"SKill\\");

		LoadWaveFile ( SOUND_KANTURU_3RD_MAYAHAND_ATTACK2,	  "Data\\Sound\\w39\\maya_hand_attack-02.wav", 1 );

		vec3_t vPos, vAngle;
		if(World == WD_57ICECITY)
		{
			Vector ( 0.f, 0.f, 35.f, vAngle );
			Vector ( 0.f, 0.f, 0.f, vPos );
			vPos[0] = 162*TERRAIN_SCALE; 
			vPos[1] = 83*TERRAIN_SCALE;
			CreateObject ( MODEL_WARP, vPos, vAngle );
			
			Vector ( 0.f, 0.f, 80.f, vAngle );
			Vector ( 0.f, 0.f, 0.f, vPos );
			vPos[0] = 171*TERRAIN_SCALE; 
			vPos[1] = 24*TERRAIN_SCALE;
			CreateObject ( MODEL_WARP4, vPos, vAngle );
		}
		else if(World == WD_58ICECITY_BOSS)
		{
			Vector ( 0.f, 0.f, 85.f, vAngle );
			Vector ( 0.f, 0.f, 0.f, vPos );
			vPos[0] = 169*TERRAIN_SCALE; 
			vPos[1] = 24*TERRAIN_SCALE;
			CreateObject ( MODEL_WARP4, vPos, vAngle );

			Vector ( 0.f, 0.f, 85.f, vAngle );
			Vector ( 0.f, 0.f, 0.f, vPos );
			vPos[0] = 170*TERRAIN_SCALE; 
			vPos[1] = 24*TERRAIN_SCALE;
			CreateObject ( MODEL_WARP4, vPos, vAngle );
		}
		break;
#endif // CSK_ADD_MAP_ICECITY	
#ifdef LDS_ADD_EMPIRE_GUARDIAN
	case WD_69EMPIREGUARDIAN1:
	case WD_70EMPIREGUARDIAN2:
	case WD_71EMPIREGUARDIAN3:
	case WD_72EMPIREGUARDIAN4:
 		AccessModel(MODEL_PROJECTILE ,"Data\\Effect\\","choarms_06");
 		OpenTexture(MODEL_PROJECTILE ,"Effect\\");

		//���� �ı��� ����Ʈ
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE01 ,"Data\\Effect\\","piece01_01");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE02 ,"Data\\Effect\\","piece01_02");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE03 ,"Data\\Effect\\","piece01_03");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE04 ,"Data\\Effect\\","piece01_04");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE05 ,"Data\\Effect\\","piece01_05");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE06 ,"Data\\Effect\\","piece01_06");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE07 ,"Data\\Effect\\","piece01_07");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE08 ,"Data\\Effect\\","piece01_08");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE09 ,"Data\\Effect\\","newdoor_break_01");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE01 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE02 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE03 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE04 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE05 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE06 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE07 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE08 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE09 ,"Effect\\");

		//���� �ı��� ����Ʈ
		AccessModel(MODEL_STATUE_CRUSH_EFFECT_PIECE01 ,"Data\\Effect\\","NpcGagoil_Crack01");
		AccessModel(MODEL_STATUE_CRUSH_EFFECT_PIECE02 ,"Data\\Effect\\","NpcGagoil_Crack02");
		AccessModel(MODEL_STATUE_CRUSH_EFFECT_PIECE03 ,"Data\\Effect\\","NpcGagoil_Crack03");
		AccessModel(MODEL_STATUE_CRUSH_EFFECT_PIECE04 ,"Data\\Effect\\","NpcGagoil_Ruin");
		OpenTexture(MODEL_STATUE_CRUSH_EFFECT_PIECE01 ,"Effect\\");
		OpenTexture(MODEL_STATUE_CRUSH_EFFECT_PIECE02 ,"Effect\\");
		OpenTexture(MODEL_STATUE_CRUSH_EFFECT_PIECE03 ,"Effect\\");
		OpenTexture(MODEL_STATUE_CRUSH_EFFECT_PIECE04 ,"Effect\\");
		
		//�ָ��� ���� �ı��� ����Ʈ
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE10 ,"Data\\Effect\\","sojghmoon02");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE11 ,"Data\\Effect\\","sojghmj01");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE12 ,"Data\\Effect\\","sojghmj02");
		AccessModel(MODEL_DOOR_CRUSH_EFFECT_PIECE13 ,"Data\\Effect\\","sojghmj03");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE10 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE11 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE12 ,"Effect\\");
		OpenTexture(MODEL_DOOR_CRUSH_EFFECT_PIECE13 ,"Effect\\");

		LoadBitmap("Effect\\clouds.jpg", BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);
		LoadBitmap("Effect\\flare.jpg", BITMAP_FLARE, GL_LINEAR,GL_CLAMP);
		LoadBitmap("Effect\\Map_Smoke1.jpg", BITMAP_CHROME+2, GL_LINEAR,GL_REPEAT);

		// ���� �� ȯ�� ����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_WEATHER_RAIN,"Data\\Sound\\w69w70w71w72\\ImperialGuardianFort_out1.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_WEATHER_FOG,"Data\\Sound\\w69w70w71w72\\ImperialGuardianFort_out2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_WEATHER_STORM,"Data\\Sound\\w69w70w71w72\\ImperialGuardianFort_out3.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_INDOOR_SOUND,"Data\\Sound\\w69w70w71w72\\ImperialGuardianFort_in.wav");

		//������ȣ�� ���� ���̿� ī����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_MOVE,"Data\\Sound\\w69w70w71w72\\GaionKalein_move.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_RAGE,"Data\\Sound\\w69w70w71w72\\GaionKalein_rage.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_BOSS_GAION_MONSTER_DEATH,"Data\\Sound\\w69w70w71w72\\GrandWizard_death.wav");
		//������ȣ�� ���°� ����Ʈ
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK01,"Data\\Sound\\w69w70w71w72\\Jelint_attack1.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_ATTACK03,"Data\\Sound\\w69w70w71w72\\Jelint_attack3.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE01,"Data\\Sound\\w69w70w71w72\\Jelint_move01.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_MOVE02,"Data\\Sound\\w69w70w71w72\\Jelint_move02.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_RAGE,"Data\\Sound\\w69w70w71w72\\Jelint_rage.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_JERINT_MONSTER_DEATH,"Data\\Sound\\w69w70w71w72\\Jelint_death.wav");
		//������ȣ�� �λ�ɰ� ���̸��
		LoadWaveFile(SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_ATTACK02,"Data\\Sound\\w69w70w71w72\\Raymond_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_RAYMOND_MONSTER_RAGE,"Data\\Sound\\w69w70w71w72\\Raymond_rage.wav");
		//������ȣ�� ���ְ� ����ĭ��
		LoadWaveFile(SOUND_EMPIREGUARDIAN_ERCANNE_MONSTER_ATTACK03,"Data\\Sound\\w69w70w71w72\\Ercanne_attack3.wav");
		//������ȣ�� 1������ ������
		LoadWaveFile(SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK02,"Data\\Sound\\w69w70w71w72\\1Deasuler_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_1CORP_DEASULER_MONSTER_ATTACK03,"Data\\Sound\\w69w70w71w72\\1Deasuler_attack3.wav");
		//������ȣ�� 2������ ����Ʈ
		LoadWaveFile(SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK01,"Data\\Sound\\w69w70w71w72\\2Vermont_attack1.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_ATTACK02,"Data\\Sound\\w69w70w71w72\\2Vermont_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_2CORP_VERMONT_MONSTER_DEATH,"Data\\Sound\\w69w70w71w72\\2Vermont_death.wav");
		//������ȣ�� 3������ ī��
		LoadWaveFile(SOUND_EMPIREGUARDIAN_3CORP_CATO_ATTACK02,"Data\\Sound\\w69w70w71w72\\3Cato_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_3CORP_CATO_MOVE,"Data\\Sound\\w69w70w71w72\\3Cato_move.wav");
		//������ȣ�� 4������ ������
		LoadWaveFile(SOUND_EMPIREGUARDIAN_4CORP_GALLIA_ATTACK02,"Data\\Sound\\w69w70w71w72\\4Gallia_attack2.wav");
		//������ȣ�� �����屳
		LoadWaveFile(SOUND_EMPIREGUARDIAN_QUATERMASTER_ATTACK02,"Data\\Sound\\w69w70w71w72\\QuaterMaster_attack2.wav");
		//������ȣ�� ��������
		LoadWaveFile(SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK01,"Data\\Sound\\w69w70w71w72\\CombatMaster_attack1.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK02,"Data\\Sound\\w69w70w71w72\\CombatMaster_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_COMBATMASTER_ATTACK03,"Data\\Sound\\w69w70w71w72\\CombatMaster_attack3.wav");
		//������ȣ�� �븶����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_GRANDWIZARD_DEATH,"Data\\Sound\\w69w70w71w72\\GrandWizard_death.wav");
		//������ȣ�� �ϻ����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_ASSASSINMASTER_DEATH,"Data\\Sound\\w69w70w71w72\\AssassinMaster_Death.wav");
		//������ȣ�� �⸶����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK01,"Data\\Sound\\w69w70w71w72\\CavalryLeader_attack1.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_CAVALRYLEADER_ATTACK02,"Data\\Sound\\w69w70w71w72\\CavalryLeader_attack2.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE01,"Data\\Sound\\w69w70w71w72\\CavalryLeader_move01.wav");
		LoadWaveFile(SOUND_EMPIREGUARDIAN_CAVALRYLEADER_MOVE02,"Data\\Sound\\w69w70w71w72\\CavalryLeader_move02.wav");
		//������ȣ�� ���к�
		LoadWaveFile(SOUND_EMPIREGUARDIAN_DEFENDER_ATTACK02,"Data\\Sound\\w69w70w71w72\\GrandWizard_death.wav");
		//������ȣ�� ġ����
		LoadWaveFile(SOUND_EMPIREGUARDIAN_PRIEST_STOP,"Data\\Sound\\w69w70w71w72\\Priest_stay.wav");
		break;
#endif	// LDS_ADD_EMPIRE_GUARDIAN
#ifdef PJH_NEW_SERVER_SELECT_MAP
	case WD_73NEW_LOGIN_SCENE:
	case WD_74NEW_CHARACTER_SCENE:
		{
#ifdef PBG_ADD_MUBLUE_LOGO
			// ����
			LoadBitmap("Logo\\MuBlue_logo.tga", BITMAP_LOG_IN+16, GL_LINEAR);
			LoadBitmap("Logo\\MuBlue_logo_g.jpg", BITMAP_LOG_IN+17, GL_LINEAR);
#else //PBG_ADD_MUBLUE_LOGO
			LoadBitmap("Logo\\MU-logo.tga", BITMAP_LOG_IN+16, GL_LINEAR);
			LoadBitmap("Logo\\MU-logo_g.jpg", BITMAP_LOG_IN+17, GL_LINEAR);
#endif //PBG_ADD_MUBLUE_LOGO
		}
		break;
#endif //PJH_NEW_SERVER_SELECT_MAP
	case WD_55LOGINSCENE:
		AccessModel(MODEL_DRAGON	 ,"Data\\Object56\\","Dragon");
		OpenTexture(MODEL_DRAGON	 ,"Object56\\");

		Vector ( 0.f, 0.f, 0.f, Ang );
		Vector ( 0.f, 0.f, 0.f, Pos );
		Pos[0] = 56*TERRAIN_SCALE; Pos[1] = 230*TERRAIN_SCALE;
		CreateObject ( MODEL_DRAGON, Pos, Ang );
		break;

#ifdef ASG_ADD_KARUTAN_MONSTERS
	case WD_80KARUTAN1:
	case WD_81KARUTAN2:
		LoadBitmap("Object9\\sand02.jpg", BITMAP_CHROME+3, GL_LINEAR, GL_REPEAT);
		LoadBitmap("Effect\\clouds.jpg", BITMAP_CLOUD, GL_LINEAR, GL_CLAMP);

		// �ܵ�� ���� �� ����Ʈ ��
		AccessModel(MODEL_CONDRA_ARM_L	, "Data\\Monster\\", "condra_7_arm_left");
		OpenTexture(MODEL_CONDRA_ARM_L	, "Monster\\");
		AccessModel(MODEL_CONDRA_ARM_L2	, "Data\\Monster\\", "condra_7_arm_left_2");
		OpenTexture(MODEL_CONDRA_ARM_L2	, "Monster\\");
		AccessModel(MODEL_CONDRA_SHOULDER, "Data\\Monster\\", "condra_7_shoulder_right");
		OpenTexture(MODEL_CONDRA_SHOULDER, "Monster\\");
		AccessModel(MODEL_CONDRA_ARM_R	, "Data\\Monster\\", "condra_7_arm_right");
		OpenTexture(MODEL_CONDRA_ARM_R	, "Monster\\");
		AccessModel(MODEL_CONDRA_ARM_R2	, "Data\\Monster\\", "condra_7_arm_right_2");
		OpenTexture(MODEL_CONDRA_ARM_R2	, "Monster\\");
		AccessModel(MODEL_CONDRA_CONE_L	, "Data\\Monster\\", "condra_7_cone_left");
		OpenTexture(MODEL_CONDRA_CONE_L	, "Monster\\");
		AccessModel(MODEL_CONDRA_CONE_R	, "Data\\Monster\\", "condra_7_cone_right");
		OpenTexture(MODEL_CONDRA_CONE_R	, "Monster\\");
		AccessModel(MODEL_CONDRA_PELVIS	, "Data\\Monster\\", "condra_7_pelvis");
		OpenTexture(MODEL_CONDRA_PELVIS	, "Monster\\");
		AccessModel(MODEL_CONDRA_STOMACH, "Data\\Monster\\", "condra_7_stomach");
		OpenTexture(MODEL_CONDRA_STOMACH, "Monster\\");
		AccessModel(MODEL_CONDRA_NECK	, "Data\\Monster\\", "condra_7_neck");
		OpenTexture(MODEL_CONDRA_NECK	, "Monster\\");
		
		// �����ܵ�� ���� �� ����Ʈ ��
		AccessModel(MODEL_NARCONDRA_ARM_L	, "Data\\Monster\\", "nar_condra_7_arm_left");
		OpenTexture(MODEL_NARCONDRA_ARM_L	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_ARM_L2	, "Data\\Monster\\", "nar_condra_7_arm_left_2");
		OpenTexture(MODEL_NARCONDRA_ARM_L2	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_SHOULDER_L, "Data\\Monster\\", "nar_condra_7_shoulder_left");
		OpenTexture(MODEL_NARCONDRA_SHOULDER_L, "Monster\\");
		AccessModel(MODEL_NARCONDRA_SHOULDER_R, "Data\\Monster\\", "nar_condra_7_shoulder_right");
		OpenTexture(MODEL_NARCONDRA_SHOULDER_R, "Monster\\");
		AccessModel(MODEL_NARCONDRA_ARM_R	, "Data\\Monster\\", "nar_condra_7_arm_right");
		OpenTexture(MODEL_NARCONDRA_ARM_R	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_ARM_R2	, "Data\\Monster\\", "nar_condra_7_arm_right_2");
		OpenTexture(MODEL_NARCONDRA_ARM_R2	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_ARM_R3	, "Data\\Monster\\", "nar_condra_7_arm_right_3");
		OpenTexture(MODEL_NARCONDRA_ARM_R3	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_1	, "Data\\Monster\\", "nar_condra_7_cone_1");
		OpenTexture(MODEL_NARCONDRA_CONE_1	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_2	, "Data\\Monster\\", "nar_condra_7_cone_2");
		OpenTexture(MODEL_NARCONDRA_CONE_2	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_3	, "Data\\Monster\\", "nar_condra_7_cone_3");
		OpenTexture(MODEL_NARCONDRA_CONE_3	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_4	, "Data\\Monster\\", "nar_condra_7_cone_4");
		OpenTexture(MODEL_NARCONDRA_CONE_4	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_5	, "Data\\Monster\\", "nar_condra_7_cone_5");
		OpenTexture(MODEL_NARCONDRA_CONE_5	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_CONE_6	, "Data\\Monster\\", "nar_condra_7_cone_6");
		OpenTexture(MODEL_NARCONDRA_CONE_6	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_PELVIS	, "Data\\Monster\\", "nar_condra_7_pelvis");
		OpenTexture(MODEL_NARCONDRA_PELVIS	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_STOMACH	, "Data\\Monster\\", "nar_condra_7_stomach");
		OpenTexture(MODEL_NARCONDRA_STOMACH	, "Monster\\");
		AccessModel(MODEL_NARCONDRA_NECK	, "Data\\Monster\\", "nar_condra_7_neck");
		OpenTexture(MODEL_NARCONDRA_NECK	, "Monster\\");

		LoadWaveFile(SOUND_KARUTAN_DESERT_ENV, "Data\\Sound\\Karutan\\Karutan_desert_env.wav", 1 );
		LoadWaveFile(SOUND_KARUTAN_INSECT_ENV, "Data\\Sound\\Karutan\\Karutan_insect_env.wav", 1 );
		LoadWaveFile(SOUND_KARUTAN_KARDAMAHAL_ENV, "Data\\Sound\\Karutan\\Kardamahal_entrance_env.wav", 1 );
		break;
#endif	// ASG_ADD_KARUTAN_MONSTERS
	}

    if ( InChaosCastle()==true )
    {
        AccessModel ( MODEL_ANGEL, "Data\\Player\\", "Angel" );
        OpenTexture ( MODEL_ANGEL, "Npc\\" );

		LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD,GL_LINEAR,GL_CLAMP);

        //  ȿ����.
		LoadWaveFile ( SOUND_CHAOSCASTLE, "Data\\Sound\\iChaosCastle.wav" , 1 );
    }
	
    if ( InHellas() )
    {
		LoadBitmap( "Object25\\water1.tga", BITMAP_MAPTILE, GL_LINEAR, GL_REPEAT,false);
		LoadBitmap( "Object25\\water2.jpg", BITMAP_MAPTILE+1, GL_NEAREST, GL_CLAMP );

        // ��� ������
        AccessModel(MODEL_CUNDUN_PART1		 ,"Data\\Monster\\","cd71a",-1);
        OpenTexture(MODEL_CUNDUN_PART1		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART2		 ,"Data\\Monster\\","cd71b",-1);
        OpenTexture(MODEL_CUNDUN_PART2		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART3		 ,"Data\\Monster\\","cd71c",-1);
        OpenTexture(MODEL_CUNDUN_PART3		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART4		 ,"Data\\Monster\\","cd71d",-1);
        OpenTexture(MODEL_CUNDUN_PART4		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART5		 ,"Data\\Monster\\","cd71e",-1);
        OpenTexture(MODEL_CUNDUN_PART5		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART6		 ,"Data\\Monster\\","cd71f",-1);
        OpenTexture(MODEL_CUNDUN_PART6		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART7		 ,"Data\\Monster\\","cd71g",-1);
        OpenTexture(MODEL_CUNDUN_PART7		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_PART8		 ,"Data\\Monster\\","cd71h",-1);
        OpenTexture(MODEL_CUNDUN_PART8		 ,"Monster\\");
        AccessModel(MODEL_CUNDUN_DRAGON_HEAD ,"Data\\Skill\\","dragonhead",-1);
        OpenTexture(MODEL_CUNDUN_DRAGON_HEAD ,"Skill\\");
        AccessModel(MODEL_CUNDUN_PHOENIX	 ,"Data\\Skill\\","phoenix",-1);
        OpenTexture(MODEL_CUNDUN_PHOENIX	 ,"Skill\\");
        AccessModel(MODEL_CUNDUN_GHOST		 ,"Data\\Monster\\","cundun_gone",-1);
        OpenTexture(MODEL_CUNDUN_GHOST		 ,"Monster\\");
        Models[MODEL_CUNDUN_PART6].Actions[0].Loop = false;
        Models[MODEL_CUNDUN_PART6].Actions[0].PlaySpeed = 0.13f;
        Models[MODEL_CUNDUN_PART7].Actions[0].Loop = false;
        Models[MODEL_CUNDUN_PART7].Actions[0].PlaySpeed = 0.13f;
        Models[MODEL_CUNDUN_PHOENIX].Actions[0].Loop = true;
        Models[MODEL_CUNDUN_GHOST].Actions[0].Loop = false;

        //  ȿ���� �ε�.
        LoadWaveFile ( SOUND_KALIMA_AMBIENT,        "Data\\Sound\\aKalima.wav", 1 );
        LoadWaveFile ( SOUND_KALIMA_AMBIENT2,       "Data\\Sound\\aKalima01.wav", 1 );
        LoadWaveFile ( SOUND_KALIMA_AMBIENT3,       "Data\\Sound\\aKalima02.wav", 1 );
        LoadWaveFile ( SOUND_KALIMA_WATER_FALL,     "Data\\Sound\\aKalimaWaterFall.wav", 3 );
        LoadWaveFile ( SOUND_KALIMA_FALLING_STONE,  "Data\\Sound\\aKalimaStone.wav", 3 );
        LoadWaveFile ( SOUND_DEATH_BUBBLE,          "Data\\Sound\\mDeathBubble.wav", 1 );

        LoadWaveFile ( SOUND_KUNDUN_AMBIENT1,       "Data\\Sound\\mKundunAmbient1.wav", 1 );
        LoadWaveFile ( SOUND_KUNDUN_AMBIENT2,       "Data\\Sound\\mKundunAmbient2.wav", 1 );
        LoadWaveFile ( SOUND_KUNDUN_ROAR,           "Data\\Sound\\mKundunRoar.wav", 1 );
        LoadWaveFile ( SOUND_KUNDUN_SIGHT,          "Data\\Sound\\mKundunSight.wav", 1 );
        LoadWaveFile ( SOUND_KUNDUN_SHUDDER,        "Data\\Sound\\mKundunShudder.wav", 1 );
        LoadWaveFile ( SOUND_KUNDUN_DESTROY,        "Data\\Sound\\mKundunDestory.wav", 1 );

        LoadWaveFile ( SOUND_SKILL_SKULL,           "Data\\Sound\\eSkull.wav", 1 );
        LoadWaveFile ( SOUND_GREAT_POISON,          "Data\\Sound\\eGreatPoison.wav", 1 );
        LoadWaveFile ( SOUND_GREAT_SHIELD,          "Data\\Sound\\eGreatShield.wav", 1 );
    }

    if ( World!=WD_7ATLANSE )
    {
#ifdef _VS2008PORTING
	    for ( int i=0; i<32; i++ )
#else // _VS2008PORTING
	    for ( i=0; i<32; i++ )
#endif // _VS2008PORTING
	    {
		    char FileName[100];
		    if(i<10)
      		    sprintf(FileName,"Object8\\wt0%d.jpg",i);
		    else
      		    sprintf(FileName,"Object8\\wt%d.jpg",i);
			
			LoadBitmap(FileName,BITMAP_WATER+i,GL_LINEAR,GL_REPEAT,false);
		}
    }
	
	LoadBitmap( "Object8\\light01.jpg", BITMAP_SHINES, GL_LINEAR, GL_REPEAT);
	
	if(World==0)
	{
		for(i=0;i<13;i++)
			AccessModel(MODEL_TREE01 +i,"Data\\Object1\\","Tree",i+1);
		for(i=0;i<8;i++)
			AccessModel(MODEL_GRASS01+i,"Data\\Object1\\","Grass",i+1);
		for(i=0;i<5;i++)
			AccessModel(MODEL_STONE01+i,"Data\\Object1\\","Stone",i+1);
		
		for(i=0;i<3;i++)
			AccessModel(MODEL_STONE_STATUE01+i,"Data\\Object1\\","StoneStatue",i+1);
		AccessModel(MODEL_STEEL_STATUE,"Data\\Object1\\","SteelStatue",1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_TOMB01+i,"Data\\Object1\\","Tomb",i+1);
		for(i=0;i<2;i++)
			AccessModel(MODEL_FIRE_LIGHT01+i,"Data\\Object1\\","FireLight",i+1);
		AccessModel(MODEL_BONFIRE,"Data\\Object1\\","Bonfire",1);
		AccessModel(MODEL_DUNGEON_GATE,"Data\\Object1\\","DoungeonGate",1);
		AccessModel(MODEL_TREASURE_DRUM ,"Data\\Object1\\","TreasureDrum",1);
		AccessModel(MODEL_TREASURE_CHEST,"Data\\Object1\\","TreasureChest",1);
		AccessModel(MODEL_SHIP,"Data\\Object1\\","Ship",1);
		
		for(i=0;i<6;i++)
			AccessModel(MODEL_STONE_WALL01+i,"Data\\Object1\\","StoneWall",i+1);
		for(i=0;i<4;i++)
			AccessModel(MODEL_MU_WALL01+i,"Data\\Object1\\","StoneMuWall",i+1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_STEEL_WALL01+i,"Data\\Object1\\","SteelWall",i+1);
		AccessModel(MODEL_STEEL_DOOR,"Data\\Object1\\","SteelDoor",1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_CANNON01+i,"Data\\Object1\\","Cannon",i+1);
		AccessModel(MODEL_BRIDGE,"Data\\Object1\\","Bridge",1);
		for(i=0;i<4;i++)
			AccessModel(MODEL_FENCE01+i,"Data\\Object1\\","Fence",i+1);
		AccessModel(MODEL_BRIDGE_STONE,"Data\\Object1\\","BridgeStone",1);
		
		AccessModel(MODEL_STREET_LIGHT,"Data\\Object1\\","StreetLight",1);
		AccessModel(MODEL_CURTAIN,"Data\\Object1\\","Curtain",1);
		for(i=0;i<4;i++)
			AccessModel(MODEL_CARRIAGE01+i,"Data\\Object1\\","Carriage",i+1);
		for(i=0;i<2;i++)
			AccessModel(MODEL_STRAW01+i,"Data\\Object1\\","Straw",i+1);
		for(i=0;i<2;i++)
			AccessModel(MODEL_SIGN01+i,"Data\\Object1\\","Sign",i+1);
		for(i=0;i<2;i++)
			AccessModel(MODEL_MERCHANT_ANIMAL01  +i,"Data\\Object1\\","MerchantAnimal",i+1);
		AccessModel(MODEL_WATERSPOUT,"Data\\Object1\\","Waterspout",1);
		for(i=0;i<4;i++)
			AccessModel(MODEL_WELL01+i,"Data\\Object1\\","Well",i+1);
		AccessModel(MODEL_HANGING,"Data\\Object1\\","Hanging",1);
		
		for(i=0;i<5;i++)
			AccessModel(MODEL_HOUSE01+i,"Data\\Object1\\","House",i+1);
		AccessModel(MODEL_TENT,"Data\\Object1\\","Tent",1);
		AccessModel(MODEL_STAIR,"Data\\Object1\\","Stair",1);
		
		for(i=0;i<6;i++)
			AccessModel(MODEL_HOUSE_WALL01+i,"Data\\Object1\\","HouseWall",i+1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_HOUSE_ETC01+i,"Data\\Object1\\","HouseEtc",i+1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_LIGHT01+i,"Data\\Object1\\","Light",i+1);
		AccessModel(MODEL_POSE_BOX,"Data\\Object1\\","PoseBox",1);
		
		for(i=0;i<7;i++)
			AccessModel(MODEL_FURNITURE01+i,"Data\\Object1\\","Furniture",i+1);
		AccessModel(MODEL_CANDLE,"Data\\Object1\\","Candle",1);
		for(i=0;i<3;i++)
			AccessModel(MODEL_BEER01+i,"Data\\Object1\\","Beer",i+1);

#ifdef _PVP_MURDERER_HERO_ITEM
		AccessModel(MODEL_HERO_GUARD,"Data\\Object1\\","heroNpcSide",-1);
		AccessModel(MODEL_HERO_CHAIR,"Data\\Object1\\","heroNpcchair",-1);
		AccessModel(MODEL_MURDERER_DOG,"Data\\Object1\\","bigwolf",-1);
		OpenTexture(MODEL_HERO_GUARD,"Npc\\" );

		for(i=MODEL_WORLD_OBJECT;i<MAX_WORLD_OBJECTS;i++)
		{
			if (i != MODEL_HERO_GUARD)
				OpenTexture(i,"Object1\\" );
		}
#else	// _PVP_MURDERER_HERO_ITEM
		for(i=MODEL_WORLD_OBJECT;i<MAX_WORLD_OBJECTS;i++)
			OpenTexture(i,"Object1\\" );
#endif	// _PVP_MURDERER_HERO_ITEM
    }
    else
	{
		char DirName[32];
        int iMapWorld = World+1;	// �� ������ �������� �� ������ �ε��� + 1 �̴�.

        if ( InBloodCastle() == true )
        {
            iMapWorld = WD_11BLOODCASTLE1+1;
        }
        else if ( InChaosCastle() == true )
        {
            iMapWorld = WD_18CHAOS_CASTLE+1;
        }
        else if ( InHellas() == true )
        {
            iMapWorld = WD_24HELLAS+1;
        }
		else if( g_CursedTemple->IsCursedTemple() )
		{
			iMapWorld = WD_45CURSEDTEMPLE_LV1 + 2;
		}

		sprintf(DirName,"Data\\Object%d\\",iMapWorld);
		for(i=MODEL_WORLD_OBJECT;i<MAX_WORLD_OBJECTS;i++)
			AccessModel(i,DirName,"Object",i+1);

		sprintf(DirName,"Object%d\\",iMapWorld);
		for(i=MODEL_WORLD_OBJECT;i<MAX_WORLD_OBJECTS;i++)
		{
			OpenTexture( i, DirName );
		}
		
		if(World == WD_1DUNGEON)	// ����
		{
			Models[40].Actions[1].PlaySpeed = 0.4f;
		}
        else if(World == WD_8TARKAN)	// Ÿ��ĭ
        {
            Models[11].StreamMesh = 0;  //  ���� �� ����.
            Models[12].StreamMesh = 0;  //  �𷡴�.
            Models[13].StreamMesh = 0;  //  ������.
            Models[73].StreamMesh = 0;  //  ��� �帣��2.
            Models[75].StreamMesh = 0;  //  ��� �帣��3.
            Models[79].StreamMesh = 0;  //  ��� �帣��4.
        }
		if (World == WD_51HOME_6TH_CHAR 
#ifndef PJH_NEW_SERVER_SELECT_MAP
			|| World == WD_77NEW_LOGIN_SCENE 
			|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
			)
		{
			Models[MODEL_EAGLE].Actions[0].PlaySpeed = 0.5f;
			if (World == WD_51HOME_6TH_CHAR)
			{
				Models[MODEL_MAP_TORNADO].Actions[0].PlaySpeed = 0.1f;
			}
		}
#ifdef CSK_ADD_MAP_ICECITY
		else if(World == WD_57ICECITY)
		{
			// ��� ��� �ڼ�
			Models[16].Actions[0].PlaySpeed = 0.8f;
			Models[16].Actions[1].PlaySpeed = 0.8f;
			
			// ��� ���, �޸��� �ڼ�
			Models[17].Actions[0].PlaySpeed = 0.8f;
			Models[17].Actions[1].PlaySpeed = 0.8f;
			Models[17].Actions[2].PlaySpeed = 1.f;
			Models[17].Actions[3].PlaySpeed = 1.f;
			
			Models[68].Actions[0].PlaySpeed = 0.05f;
		}
#endif // CSK_ADD_MAP_ICECITY
#ifdef ASG_ADD_MAP_KARUTAN
		else if (IsKarutanMap())
		{
			Models[66].Actions[0].PlaySpeed = 0.15f;
			Models[66].Actions[1].PlaySpeed = 0.15f;
			
			Models[107].Actions[0].PlaySpeed = 5.f;
		}
#endif	// ASG_ADD_MAP_KARUTAN
	}
}

///////////////////////////////////////////////////////////////////////////////
// ���� �ٴ� ����Ÿ �о���̴� �Լ�(���ӿ��� ���� �̵��� �ε�)
///////////////////////////////////////////////////////////////////////////////

void OpenWorld(int Map)
{
	if(Map == 32 && World == 32)
	//����������(5,6)�߰��ÿ� �ʹ�ȣ 33�� ����������(1,2,3,4)�ϰ� ������ ���̰� �ʹ�ȣ�� 
	//�ٲ� ���°���̴�. �׷��� �ʹ�ȣ 10��(����������(1,2,3,4))���� ������ �����ش�.
	{
		Map = World = 9;
	}


	DeleteObjects();
	DeleteNpcs();
	DeleteMonsters();
	if(SceneFlag != CHARACTER_SCENE)
	{
		ClearItems();
		ClearCharacters(HeroKey);
	}
	RemoveAllShopTitleExceptHero();

	g_Direction.Init();					// �� �̵��� ������� �ʱ�ȭ 
	g_Direction.HeroFallingDownInit();	// �� �̵��� ������� �ʱ�ȭ
	g_Direction.DeleteMonster();
	M39Kanturu3rd::Kanturu3rdInit();
	g_Direction.m_CKanturu.m_iKanturuState = 0; // --;
	g_Direction.m_CKanturu.m_iMayaState = 0;
	g_Direction.m_CKanturu.m_iNightmareState = 0;

    OpenWorldModels();

	char FileName[64];
	char WorldName[32];
    int  iMapWorld = World+1;

    if ( InBloodCastle() == true )
    {
        iMapWorld = WD_11BLOODCASTLE1+1;
    }
    else if ( InHellas() == true )
    {
        iMapWorld = WD_24HELLAS+1;
    }
    else if ( InChaosCastle()==true )
    {
        iMapWorld = WD_18CHAOS_CASTLE+1;
    }
	else if( g_CursedTemple->IsCursedTemple() )
	{
		iMapWorld = WD_45CURSEDTEMPLE_LV1 + 2;
	}

    battleCastle::Init ();

	sprintf ( WorldName, "World%d", iMapWorld );
	{
#if defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
		if(World == WD_2DEVIAS)
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.map", WorldName, iMapWorld);
		}
		else
#endif	// defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
#ifdef ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
		if (World == WD_33AIDA)
			sprintf(FileName, "Data\\%s\\EncTerraintest%d.map", WorldName, iMapWorld);
		else
#endif	// ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
#ifdef CHAOSCASTLE_MAP_FOR_TESTSERVER
		if (InChaosCastle())
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.map", WorldName, iMapWorld);
		}
		else
#endif	// CHAOSCASTLE_MAP_FOR_TESTSERVER
#ifdef KJH_EXTENSIONMAP_FOR_TESTSERVER
		if( (World == WD_33AIDA) || (World == WD_37KANTURU_1ST) || (World == WD_56MAP_SWAMP_OF_QUIET) || (World == WD_57ICECITY))
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.map", WorldName, iMapWorld);
		}
		else
#endif // KJH_EXTENSIONMAP_FOR_TESTSERVER
#ifdef KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
		if( (World == WD_10HEAVEN) )
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.map", WorldName, iMapWorld);
		}
		else
#endif // KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
		{
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.map", WorldName, iMapWorld);
		}
	}

	int iResult = OpenTerrainMapping ( FileName );

	if ( iMapWorld != iResult && -1 != iResult)
	{
		char Text[256];
   		sprintf(Text,"%s file corrupted.",FileName);
		g_ErrorReport.Write( Text);
		g_ErrorReport.Write( "\r\n");
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}

#ifdef PJH_NEW_SERVER_SELECT_MAP
	if (World == WD_73NEW_LOGIN_SCENE)
#else
	if (World == WD_77NEW_LOGIN_SCENE)
#endif //PJH_NEW_SERVER_SELECT_MAP
	{
		sprintf(FileName,"Data\\%s\\CWScript%d.cws",WorldName, iMapWorld);
		CCameraMove::GetInstancePtr()->LoadCameraWalkScript(FileName);
	}

	int CryWolfState = M34CryWolf1st::IsCryWolf1stMVPStart();

    if ( battleCastle::InBattleCastle() )
    {
        if ( battleCastle::IsBattleCastleStart() ) //  ������.
        {
            //  �Ӽ�.
	        sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld*10+2 );
        }
        else                        //  ������.
        {
            //  �Ӽ�.
	        sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld );
        }
    }
    else

	if (World==WD_34CRYWOLF_1ST)
	{
		switch( CryWolfState )
		{
		case CRYWOLF_OCCUPATION_STATE_PEACE:    // ��ȭ����
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld);
			break;
		case CRYWOLF_OCCUPATION_STATE_OCCUPIED: // ���ɻ���
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld*10+1);
			break;
		case CRYWOLF_OCCUPATION_STATE_WAR:		// �������
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld*10+2);
			break;
		}
	}
	else if (World == WD_39KANTURU_3RD)
	{
		if(M39Kanturu3rd::IsSuccessBattle())
		{
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld*10+1);
		}
		else
		{
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld);
		}
	}
	else
    {
#if defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
		if(World == WD_2DEVIAS)
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.att", WorldName, iMapWorld);
		}
		else
#endif	// defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
#ifdef ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
		if (World == WD_33AIDA)
			sprintf(FileName, "Data\\%s\\EncTerraintest%d.att", WorldName, iMapWorld);
		else
#endif	// ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
#ifdef CHAOSCASTLE_MAP_FOR_TESTSERVER
		if (InChaosCastle())
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.att", WorldName, iMapWorld);
		}
		else
#endif	// CHAOSCASTLE_MAP_FOR_TESTSERVER
#ifdef KJH_EXTENSIONMAP_FOR_TESTSERVER
		if( (World == WD_33AIDA) || (World == WD_37KANTURU_1ST) || (World == WD_56MAP_SWAMP_OF_QUIET) || (World == WD_57ICECITY))
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.att", WorldName, iMapWorld);
		}
		else
#endif // KJH_EXTENSIONMAP_FOR_TESTSERVER
#ifdef KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
		if( (World == WD_10HEAVEN) )
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.att", WorldName, iMapWorld);
		}
		else
#endif // KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
		{
			sprintf ( FileName, "Data\\%s\\EncTerrain%d.att", WorldName, iMapWorld );   
		}
    }
	iResult = OpenTerrainAttribute ( FileName);
	if ( iMapWorld != iResult && -1 != iResult)
	{
		char Text[256];
   		sprintf(Text,"%s file corrupted.",FileName);
		g_ErrorReport.Write( Text);
		g_ErrorReport.Write( "\r\n");
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}

	{
#if defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
		if(World == WD_2DEVIAS)
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.obj", WorldName, iMapWorld);
		}
		else
#endif	// defined DEVIAS_XMAS_END_LOADFIX_FOR_TESTSERVER
#ifdef ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
		if (World == WD_33AIDA)
			sprintf(FileName, "Data\\%s\\EncTerraintest%d.obj", WorldName, iMapWorld);
		else
#endif	// ASG_ADD_AIDA_KARUTAN_GATE_FOR_TESTSERVER
#ifdef CHAOSCASTLE_MAP_FOR_TESTSERVER
		if (InChaosCastle())
		{
			sprintf ( FileName, "Data\\%s\\EncTerraintest%d.obj", WorldName, iMapWorld);
		}
		else
#endif	// CHAOSCASTLE_MAP_FOR_TESTSERVER
#ifdef KJH_EXTENSIONMAP_FOR_TESTSERVER
			if( (World == WD_33AIDA) || (World == WD_37KANTURU_1ST) || (World == WD_56MAP_SWAMP_OF_QUIET) || (World == WD_57ICECITY))
			{
				sprintf ( FileName, "Data\\%s\\EncTerraintest%d.obj", WorldName, iMapWorld);
			}
			else
#endif // KJH_EXTENSIONMAP_FOR_TESTSERVER
#ifdef KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
			if( (World == WD_10HEAVEN) )
			{
				sprintf ( FileName, "Data\\%s\\EncTerraintest%d.obj", WorldName, iMapWorld);
			}
			else
#endif // KJH_FIX_ICARUS_MAP_ATTRIBUTE_FOR_TESTSERVER
		{
			sprintf(FileName,"Data\\%s\\EncTerrain%d.obj",WorldName, iMapWorld);
		}
	}

	iResult = OpenObjectsEnc ( FileName);
	if ( iMapWorld != iResult && -1 != iResult)
	{
		char Text[256];
   		sprintf(Text,"%s file corrupted.",FileName);
		g_ErrorReport.Write( Text);
		g_ErrorReport.Write( "\r\n");
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}

	// ���� ���̰� �ε�
	sprintf(FileName,"%s\\TerrainHeight.bmp",WorldName);
	if(IsTerrainHeightExtMap(World) == true)
	{
		CreateTerrain(FileName, true);
	}
	else
	{
		CreateTerrain(FileName);
	}

	// ���� ���� �ε�
    if ( battleCastle::InBattleCastle() )
    {
        if ( battleCastle::IsBattleCastleStart() ) //  ������.
        {
    	    sprintf(FileName,"%s\\TerrainLight2.jpg",WorldName);
        }
        else//  ������.
        {
	        sprintf(FileName,"%s\\TerrainLight.jpg",WorldName);
        }
    }
    else
	if (World==WD_34CRYWOLF_1ST)
	{
		switch( CryWolfState )
		{
		case CRYWOLF_OCCUPATION_STATE_PEACE:    // ��ȭ����
			sprintf ( FileName, "%s\\TerrainLight.jpg", WorldName);
			break;
		case CRYWOLF_OCCUPATION_STATE_OCCUPIED: // ���ɻ���
			sprintf ( FileName, "%s\\TerrainLight1.jpg", WorldName);
			break;
		case CRYWOLF_OCCUPATION_STATE_WAR:		// �������
			sprintf ( FileName, "%s\\TerrainLight2.jpg", WorldName);
			break;
		}
	}
	else
	{
	    sprintf(FileName,"%s\\TerrainLight.jpg",WorldName);
	}

	OpenTerrainLight(FileName);

    if ( CreateWaterTerrain( World )==false )
    {
	    sprintf (FileName,"%s\\TileGrass01.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE   ,GL_NEAREST,GL_REPEAT, false);
	    sprintf (FileName,"%s\\TileGrass02.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+1 ,GL_NEAREST,GL_REPEAT, false);
		if(World == WD_51HOME_6TH_CHAR 
#ifndef PJH_NEW_SERVER_SELECT_MAP
			|| World == WD_77NEW_LOGIN_SCENE 
			|| World == WD_78NEW_CHARACTER_SCENE
#endif //PJH_NEW_SERVER_SELECT_MAP
			)
		{
			sprintf (FileName,"%s\\AlphaTileGround01.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+2  ,GL_NEAREST,GL_REPEAT,false);
		}
		else
		{
			sprintf (FileName,"%s\\TileGround01.jpg",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+2 ,GL_NEAREST,GL_REPEAT, false);
		}
		
		if(World == WD_39KANTURU_3RD)
		{
			sprintf (FileName,"%s\\AlphaTileGround02.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+3  ,GL_NEAREST,GL_REPEAT,false);
		}
		else
		{
			sprintf (FileName,"%s\\TileGround02.jpg",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+3 ,GL_NEAREST,GL_REPEAT,false);
		}
		if( g_CursedTemple->IsCursedTemple() )
		{
			sprintf (FileName,"%s\\AlphaTileGround03.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+4  ,GL_NEAREST,GL_REPEAT,false);
		}
		else
		{
			sprintf (FileName,"%s\\TileGround03.jpg",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+4 ,GL_NEAREST,GL_REPEAT,false);
		}

	    sprintf (FileName,"%s\\TileWater01.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+5 ,GL_NEAREST,GL_REPEAT,false);
	    sprintf (FileName,"%s\\TileWood01.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+6 ,GL_NEAREST,GL_REPEAT,false);
	    sprintf (FileName,"%s\\TileRock01.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+7 ,GL_NEAREST,GL_REPEAT,false);
	    sprintf (FileName,"%s\\TileRock02.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+8 ,GL_NEAREST,GL_REPEAT,false);
	    sprintf (FileName,"%s\\TileRock03.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+9 ,GL_NEAREST,GL_REPEAT,false);
#ifdef PJH_NEW_SERVER_SELECT_MAP
		if(World == WD_73NEW_LOGIN_SCENE || World == WD_74NEW_CHARACTER_SCENE)
		{
			sprintf(FileName,"%s\\AlphaTile01.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+10,GL_NEAREST,GL_REPEAT,false);
		}
		else
		{
#endif //PJH_NEW_SERVER_SELECT_MAP
	    sprintf (FileName,"%s\\TileRock04.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+10,GL_NEAREST,GL_REPEAT,false);
#ifdef PJH_NEW_SERVER_SELECT_MAP
		}
#endif //PJH_NEW_SERVER_SELECT_MAP
#ifdef PBG_ADD_PKFIELD
		if(IsPKField()
#ifdef YDG_ADD_MAP_DOPPELGANGER2
			|| IsDoppelGanger2()
#endif	// YDG_ADD_MAP_DOPPELGANGER2
			)
		{
		//	sprintf(FileName,"%s\\song_lava1.jpg",WorldName);
		//	LoadBitmap(FileName,BITMAP_MAPTILE+11,GL_NEAREST,GL_REPEAT,false);
			LoadBitmap("Object64\\song_lava1.jpg", BITMAP_MAPTILE+11,GL_NEAREST,GL_REPEAT,false);
		}
		else
#endif //PBG_ADD_PKFIELD
		{
			sprintf (FileName,"%s\\TileRock05.jpg",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+11,GL_NEAREST,GL_REPEAT,false);
		}
#ifdef ASG_ADD_MAP_KARUTAN
		if (IsKarutanMap())
		{
			sprintf(FileName,"%s\\AlphaTile01.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+12,GL_NEAREST,GL_REPEAT,false);
		}
		else
		{
#endif	// ASG_ADD_MAP_KARUTAN
			sprintf (FileName,"%s\\TileRock06.jpg",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+12,GL_NEAREST,GL_REPEAT,false);
#ifdef ASG_ADD_MAP_KARUTAN
		}
#endif	// ASG_ADD_MAP_KARUTAN
	    sprintf (FileName,"%s\\TileRock07.jpg",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPTILE+13,GL_NEAREST,GL_REPEAT,false);

		for(int i = 1; i <= 16; i++)
		{
			if(i >= 10)
				sprintf (FileName,"%s\\ExtTile%d.jpg",WorldName, i);
			else
				sprintf (FileName,"%s\\ExtTile0%d.jpg",WorldName, i);
			LoadBitmap(FileName,BITMAP_MAPTILE+13+i ,GL_NEAREST,GL_REPEAT,false);
		}
#ifdef PBG_ADD_PKFIELD
		if(IsPKField()
#ifdef YDG_ADD_MAP_DOPPELGANGER2
			|| IsDoppelGanger2()
#endif	// YDG_ADD_MAP_DOPPELGANGER2
			)
		{
			sprintf(FileName,"%s\\TileGrass01_R.jpg",WorldName);
			LoadBitmap(FileName, BITMAP_MAPGRASS, GL_LINEAR, GL_REPEAT,false);
		}
		else
#endif //PBG_ADD_PKFIELD
		{
			sprintf (FileName,"%s\\TileGrass01.tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPGRASS  ,GL_NEAREST,GL_REPEAT,false);
		}

	    sprintf (FileName,"%s\\TileGrass02.tga",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPGRASS+1,GL_NEAREST,GL_REPEAT,false);
	    sprintf (FileName,"%s\\TileGrass03.tga",WorldName);
	    LoadBitmap(FileName,BITMAP_MAPGRASS+2,GL_NEAREST,GL_REPEAT,false);

        sprintf(FileName,"%s\\leaf01.tga" ,WorldName);
	    LoadBitmap(FileName,BITMAP_LEAF1          ,GL_NEAREST,GL_CLAMP,false);
	    sprintf(FileName,"%s\\leaf01.jpg" ,WorldName);
	    LoadBitmap(FileName,BITMAP_LEAF1          ,GL_NEAREST,GL_CLAMP,false);
	    sprintf(FileName,"%s\\leaf02.jpg" ,WorldName);
	    LoadBitmap(FileName,BITMAP_LEAF2          ,GL_NEAREST,GL_CLAMP,false);

		if(M34CryWolf1st::IsCyrWolf1st()==true)
		{
			sprintf(FileName,"%s\\rain011.tga" ,"World1");
			LoadBitmap(FileName,BITMAP_RAIN           ,GL_NEAREST,GL_CLAMP,false);
		}
		else
		{
			sprintf(FileName,"%s\\rain01.tga" ,"World1");
			LoadBitmap(FileName,BITMAP_RAIN           ,GL_NEAREST,GL_CLAMP,false);
		}
	    sprintf(FileName,"%s\\rain02.tga" ,"World1");
	    LoadBitmap(FileName,BITMAP_RAIN_CIRCLE    ,GL_NEAREST,GL_CLAMP,false);
	    sprintf(FileName,"%s\\rain03.tga" ,"World10");
	    LoadBitmap(FileName,BITMAP_RAIN_CIRCLE+1  ,GL_NEAREST,GL_CLAMP,false);

#ifdef LDS_ADD_EMPIRE_GUARDIAN
		if( IsEmpireGuardian1() || IsEmpireGuardian2() || IsEmpireGuardian3() || IsEmpireGuardian4())		
		{
			sprintf(FileName,"%s\\AlphaTile01.Tga",WorldName);
			LoadBitmap(FileName,BITMAP_MAPTILE+10,GL_NEAREST,GL_REPEAT,false);
		}
#endif // LDS_ADD_EMPIRE_GUARDIAN

    }

#ifdef PJH_ADD_MINIMAP
	if(iMapWorld != 74 && iMapWorld != 75)	//�α���â�� ĳ���� ����â.
	{
		g_pNewUIMiniMap->UnloadImages();
		g_pNewUIMiniMap->LoadImages(WorldName);
	}
#endif //PJH_ADD_MINIMAP

#ifdef MR0
	
#ifdef MR0_NEWRENDERING_EFFECTS_SPRITES
	if(EngineGate::IsOn()) 
		SpriteManager::ClearSub();
#endif // MR0_NEWRENDERING_EFFECTS_SPRITES

#endif //MR0
}

///////////////////////////////////////////////////////////////////////////////
// ���� �ٴ� ����Ÿ �����ϴ� �Լ�(�����Ϳ����� ���)
///////////////////////////////////////////////////////////////////////////////

void SaveWorld(int World)
{
	char WorldName[32];
	char FileName[64];
	sprintf(WorldName,"World%d",World);

	sprintf(FileName,"Data2\\%s\\TerrainLight.jpg",WorldName);
    SaveTerrainLight(FileName);
	sprintf(FileName,"Data2\\%s\\TerrainHeight.bmp",WorldName);
    SaveTerrainHeight(FileName);
	sprintf(FileName,"Data\\%s\\Terrain.map",WorldName);
	SaveTerrainMapping(FileName,World);
	sprintf(FileName,"Data\\%s\\Terrain.att",WorldName);
	SaveTerrainAttribute(FileName,World);
	sprintf(FileName,"Data\\%s\\Terrain.obj",WorldName);
	SaveObjects(FileName,World);
}

///////////////////////////////////////////////////////////////////////////////
// ���ӿ� �ʿ��� �̹��� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenImages()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENIMAGES, PROFILING_LOADING_OPENIMAGES );
#endif // DO_PROFILING_FOR_LOADING

	//skill
#ifndef KJH_ADD_SKILLICON_RENEWAL				// #ifndef
	LoadBitmap("Interface\\Skill.jpg"          ,BITMAP_SKILL_INTERFACE);
	LoadBitmap("Interface\\Skill2.jpg"        ,BITMAP_SKILL_INTERFACE+1);
#endif // KJH_ADD_SKILLICON_RENEWAL
	LoadBitmap("Interface\\command.jpg"       ,BITMAP_SKILL_INTERFACE+2);
	LoadBitmap("Interface\\Item_Back01.jpg"    ,BITMAP_INVENTORY  );
	LoadBitmap("Interface\\Item_Money.jpg"     ,BITMAP_INVENTORY+11);
	LoadBitmap("Interface\\Item_box.jpg"       ,BITMAP_INVENTORY+17);
	LoadBitmap("Interface\\InventoryBox2.jpg"  ,BITMAP_INVENTORY+18);
	LoadBitmap("Interface\\Trading_line.jpg"   ,BITMAP_INVENTORY+19);
	LoadBitmap("Interface\\exit_01.jpg"     ,BITMAP_INVENTORY_BUTTON);
	LoadBitmap("Interface\\exit_02.jpg"     ,BITMAP_INVENTORY_BUTTON+1);
	LoadBitmap("Interface\\accept_box01.jpg",BITMAP_INVENTORY_BUTTON+10);
	LoadBitmap("Interface\\accept_box02.jpg",BITMAP_INVENTORY_BUTTON+11);
	LoadBitmap("Interface\\mix_button1.jpg" ,BITMAP_INVENTORY_BUTTON+12);
	LoadBitmap("Interface\\mix_button2.jpg" ,BITMAP_INVENTORY_BUTTON+13);
	LoadBitmap("Interface\\lock_01.jpg" ,BITMAP_INVENTORY_BUTTON+14);
	LoadBitmap("Interface\\lock_02.jpg" ,BITMAP_INVENTORY_BUTTON+15);
	LoadBitmap("Interface\\lock_03.jpg" ,BITMAP_INVENTORY_BUTTON+16);
	LoadBitmap("Interface\\lock_04.jpg" ,BITMAP_INVENTORY_BUTTON+17);
	LoadBitmap("Interface\\guild.tga",BITMAP_GUILD);

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENIMAGES );
#endif // DO_PROFILING_FOR_LOADING
}

///////////////////////////////////////////////////////////////////////////////
// ���� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenSounds()
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENSOUNDS, PROFILING_LOADING_OPENSOUNDS );
#endif // DO_PROFILING_FOR_LOADING

	bool Enable3DSound = true;

	//ambient
#ifdef KOREAN_WAV_USE
    LoadWaveFile(SOUND_WIND01			,"Data\\Sound\\a�ٶ�.wav",1);
    LoadWaveFile(SOUND_RAIN01			,"Data\\Sound\\a��.wav",1);
    LoadWaveFile(SOUND_DUNGEON01		,"Data\\Sound\\a����.wav",1);
    LoadWaveFile(SOUND_FOREST01			,"Data\\Sound\\a��.wav",1);
    LoadWaveFile(SOUND_TOWER01		    ,"Data\\Sound\\až.wav",1);
    LoadWaveFile(SOUND_WATER01		    ,"Data\\Sound\\a��.wav",1);
    LoadWaveFile(SOUND_DESERT01		    ,"Data\\Sound\\desert.wav",1);
    LoadWaveFile(SOUND_HUMAN_WALK_GROUND,"Data\\Sound\\p�ȱ�(��).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_GRASS	,"Data\\Sound\\p�ȱ�(Ǯ).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_SNOW	,"Data\\Sound\\p�ȱ�(��).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_SWIM	,"Data\\Sound\\p����.wav",2);

	LoadWaveFile(SOUND_BIRD01			,"Data\\Sound\\a��1.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_BIRD02			,"Data\\Sound\\a��2.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_BAT01			,"Data\\Sound\\a����.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_RAT01			,"Data\\Sound\\a��.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_TRAP01			,"Data\\Sound\\a��â��.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_DOOR01			,"Data\\Sound\\a��.wav",1);
    LoadWaveFile(SOUND_DOOR02			,"Data\\Sound\\a����.wav",1);

	LoadWaveFile(SOUND_BIRD01			,"Data\\Sound\\aBird1.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_BIRD02			,"Data\\Sound\\aBird2.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_BAT01			,"Data\\Sound\\aBat.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_RAT01			,"Data\\Sound\\aMouse.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_TRAP01			,"Data\\Sound\\aGrate.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_DOOR01			,"Data\\Sound\\aDoor.wav",1);
    LoadWaveFile(SOUND_DOOR02			,"Data\\Sound\\aCastleDoor.wav",1);

    LoadWaveFile(SOUND_HEAVEN01         ,"Data\\Sound\\aHeaven.wav",1);
    LoadWaveFile(SOUND_THUNDERS01       ,"Data\\Sound\\aThunder01.wav",1);
    LoadWaveFile(SOUND_THUNDERS02       ,"Data\\Sound\\aThunder02.wav",1);
    LoadWaveFile(SOUND_THUNDERS03       ,"Data\\Sound\\aThunder03.wav",1);

	//attack
    LoadWaveFile(SOUND_BRANDISH_SWORD01 ,"Data\\Sound\\e�����ֵθ���1.wav",2); 
    LoadWaveFile(SOUND_BRANDISH_SWORD02 ,"Data\\Sound\\e�����ֵθ���2.wav",2); 
    LoadWaveFile(SOUND_BRANDISH_SWORD03 ,"Data\\Sound\\e�������ֵθ���.wav",2); 
    LoadWaveFile(SOUND_BOW01	        ,"Data\\Sound\\eȰ.wav",2);
    LoadWaveFile(SOUND_CROSSBOW01	    ,"Data\\Sound\\e����.wav",2);
    LoadWaveFile(SOUND_MIX01	        ,"Data\\Sound\\e�ͽ�.wav",2);

	//player
    LoadWaveFile(SOUND_DRINK01     	    ,"Data\\Sound\\p���ñ�.wav",1);
    LoadWaveFile(SOUND_EAT_APPLE01  	,"Data\\Sound\\p����Ա�.wav",1);
    LoadWaveFile(SOUND_HEART           	,"Data\\Sound\\p����Ҹ�.wav",1);
    LoadWaveFile(SOUND_GET_ENERGY      	,"Data\\Sound\\p������.wav",1);
    LoadWaveFile(SOUND_HUMAN_SCREAM01	,"Data\\Sound\\p���ں��1.wav",2); 
    LoadWaveFile(SOUND_HUMAN_SCREAM02	,"Data\\Sound\\p���ں��2.wav",2);
    LoadWaveFile(SOUND_HUMAN_SCREAM03	,"Data\\Sound\\p���ں��3.wav",2);
    LoadWaveFile(SOUND_HUMAN_SCREAM04	,"Data\\Sound\\p�����ױ�.wav",2);
    LoadWaveFile(SOUND_FEMALE_SCREAM01	,"Data\\Sound\\p���ں��1.wav",2); 
    LoadWaveFile(SOUND_FEMALE_SCREAM02	,"Data\\Sound\\p���ں��2.wav",2);

    LoadWaveFile(SOUND_DROP_ITEM01	    ,"Data\\Sound\\p�����۶���Ʈ����.wav",1); 
    LoadWaveFile(SOUND_DROP_GOLD01      ,"Data\\Sound\\p��ȭ����Ʈ����.wav",1); 
    LoadWaveFile(SOUND_JEWEL01	      	,"Data\\Sound\\e����.wav",1); 
    LoadWaveFile(SOUND_GET_ITEM01		,"Data\\Sound\\p�����۰�����.wav",1); 
    //LoadWaveFile(SOUND_SHOUT01    		,"Data\\Sound\\p����.wav",1); 

	//skill
    LoadWaveFile(SOUND_SKILL_DEFENSE    ,"Data\\Sound\\s������.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD1     ,"Data\\Sound\\s���系�����.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD2     ,"Data\\Sound\\s�������.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD3     ,"Data\\Sound\\s����÷�ġ��.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD4     ,"Data\\Sound\\s���絹��ġ��.wav",1);
	LoadWaveFile(SOUND_MONSTER+116      ,"Data\\Sound\\m���������1.wav",1);

    LoadWaveFile(SOUND_STORM            ,"Data\\Sound\\s����̵�.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_EVIL             ,"Data\\Sound\\s��ȥ.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_MAGIC            ,"Data\\Sound\\s����.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_HELLFIRE         ,"Data\\Sound\\s�����̾�.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_ICE              ,"Data\\Sound\\s����.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_FLAME            ,"Data\\Sound\\s�ұ��.wav",2,Enable3DSound);
    //LoadWaveFile(SOUND_FLASH            ,"Data\\Sound\\m��������1.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_FLASH            ,"Data\\Sound\\s������÷���.wav",2,Enable3DSound);

    LoadWaveFile(SOUND_BREAK01	      	,"Data\\Sound\\e�μ���.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_EXPLOTION01		,"Data\\Sound\\e����.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_METEORITE01		,"Data\\Sound\\e���������.wav",2,Enable3DSound); 
    //LoadWaveFile(SOUND_METEORITE02	    ,"Data\\Sound\\e����.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_THUNDER01		,"Data\\Sound\\e����.wav",1,Enable3DSound); 

    LoadWaveFile(SOUND_BONE1	     	,"Data\\Sound\\m�ذ�1.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_BONE2    		,"Data\\Sound\\m�ذ�2.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_ASSASSIN		    ,"Data\\Sound\\m�ϻ���1.wav",1,Enable3DSound);
#else
    LoadWaveFile(SOUND_WIND01			,"Data\\Sound\\aWind.wav",1);
    LoadWaveFile(SOUND_RAIN01			,"Data\\Sound\\aRain.wav",1);
    LoadWaveFile(SOUND_DUNGEON01		,"Data\\Sound\\aDungeon.wav",1);
    LoadWaveFile(SOUND_FOREST01			,"Data\\Sound\\aForest.wav",1);
    LoadWaveFile(SOUND_TOWER01		    ,"Data\\Sound\\aTower.wav",1);
    LoadWaveFile(SOUND_WATER01		    ,"Data\\Sound\\aWater.wav",1);
    LoadWaveFile(SOUND_DESERT01		    ,"Data\\Sound\\desert.wav",1);
    //LoadWaveFile(SOUND_BOSS01		    ,"Data\\Sound\\a���.wav",1);
    LoadWaveFile(SOUND_HUMAN_WALK_GROUND,"Data\\Sound\\pWalk(Soil).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_GRASS	,"Data\\Sound\\pWalk(Grass).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_SNOW	,"Data\\Sound\\pWalk(Snow).wav",2);
    LoadWaveFile(SOUND_HUMAN_WALK_SWIM	,"Data\\Sound\\pSwim.wav",2);

	LoadWaveFile(SOUND_BIRD01			,"Data\\Sound\\aBird1.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_BIRD02			,"Data\\Sound\\aBird2.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_BAT01			,"Data\\Sound\\aBat.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_RAT01			,"Data\\Sound\\aMouse.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_TRAP01			,"Data\\Sound\\aGrate.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_DOOR01			,"Data\\Sound\\aDoor.wav",1);
    LoadWaveFile(SOUND_DOOR02			,"Data\\Sound\\aCastleDoor.wav",1);

    LoadWaveFile(SOUND_HEAVEN01         ,"Data\\Sound\\aHeaven.wav",1);
    LoadWaveFile(SOUND_THUNDERS01       ,"Data\\Sound\\aThunder01.wav",1);
    LoadWaveFile(SOUND_THUNDERS02       ,"Data\\Sound\\aThunder02.wav",1);
    LoadWaveFile(SOUND_THUNDERS03       ,"Data\\Sound\\aThunder03.wav",1);

	//attack
    LoadWaveFile(SOUND_BRANDISH_SWORD01 ,"Data\\Sound\\eSwingWeapon1.wav",2); 
    LoadWaveFile(SOUND_BRANDISH_SWORD02 ,"Data\\Sound\\eSwingWeapon2.wav",2); 
    LoadWaveFile(SOUND_BRANDISH_SWORD03 ,"Data\\Sound\\eSwingLightSword.wav",2); 
    LoadWaveFile(SOUND_BOW01	        ,"Data\\Sound\\eBow.wav",2);
    LoadWaveFile(SOUND_CROSSBOW01	    ,"Data\\Sound\\eCrossbow.wav",2);
    LoadWaveFile(SOUND_MIX01	        ,"Data\\Sound\\eMix.wav",2);

	//player
    LoadWaveFile(SOUND_DRINK01     	    ,"Data\\Sound\\pDrink.wav",1);
    LoadWaveFile(SOUND_EAT_APPLE01  	,"Data\\Sound\\pEatApple.wav",1);
    LoadWaveFile(SOUND_HEART           	,"Data\\Sound\\pHeartBeat.wav",1);
    LoadWaveFile(SOUND_GET_ENERGY      	,"Data\\Sound\\pEnergy.wav",1);
    LoadWaveFile(SOUND_HUMAN_SCREAM01	,"Data\\Sound\\pMaleScream1.wav",2); 
    LoadWaveFile(SOUND_HUMAN_SCREAM02	,"Data\\Sound\\pMaleScream2.wav",2);
    LoadWaveFile(SOUND_HUMAN_SCREAM03	,"Data\\Sound\\pMaleScream3.wav",2);
    LoadWaveFile(SOUND_HUMAN_SCREAM04	,"Data\\Sound\\pMaleDie.wav",2);
    LoadWaveFile(SOUND_FEMALE_SCREAM01	,"Data\\Sound\\pFemaleScream1.wav",2); 
    LoadWaveFile(SOUND_FEMALE_SCREAM02	,"Data\\Sound\\pFemaleScream2.wav",2);

    LoadWaveFile(SOUND_DROP_ITEM01	    ,"Data\\Sound\\pDropItem.wav",1); 
    LoadWaveFile(SOUND_DROP_GOLD01      ,"Data\\Sound\\pDropMoney.wav",1); 
    LoadWaveFile(SOUND_JEWEL01	      	,"Data\\Sound\\eGem.wav",1); 
    LoadWaveFile(SOUND_GET_ITEM01		,"Data\\Sound\\pGetItem.wav",1); 
    //LoadWaveFile(SOUND_SHOUT01    		,"Data\\Sound\\p����.wav",1); 

	//skill
    LoadWaveFile(SOUND_SKILL_DEFENSE    ,"Data\\Sound\\sKnightDefense.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD1     ,"Data\\Sound\\sKnightSkill1.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD2     ,"Data\\Sound\\sKnightSkill2.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD3     ,"Data\\Sound\\sKnightSkill3.wav",1);
    LoadWaveFile(SOUND_SKILL_SWORD4     ,"Data\\Sound\\sKnightSkill4.wav",1);
	LoadWaveFile(SOUND_MONSTER+116      ,"Data\\Sound\\mShadowAttack1.wav",1);

    LoadWaveFile(SOUND_STORM            ,"Data\\Sound\\sTornado.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_EVIL             ,"Data\\Sound\\sEvil.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_MAGIC            ,"Data\\Sound\\sMagic.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_HELLFIRE         ,"Data\\Sound\\sHellFire.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_ICE              ,"Data\\Sound\\sIce.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_FLAME            ,"Data\\Sound\\sFlame.wav",2,Enable3DSound);
    //LoadWaveFile(SOUND_FLASH            ,"Data\\Sound\\m��������1.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_FLASH            ,"Data\\Sound\\sAquaFlash.wav",2,Enable3DSound);

    LoadWaveFile(SOUND_BREAK01	      	,"Data\\Sound\\eBreak.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_EXPLOTION01		,"Data\\Sound\\eExplosion.wav",1,Enable3DSound); 
    LoadWaveFile(SOUND_METEORITE01		,"Data\\Sound\\eMeteorite.wav",2,Enable3DSound); 
    //LoadWaveFile(SOUND_METEORITE02	    ,"Data\\Sound\\e����.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_THUNDER01		,"Data\\Sound\\eThunder.wav",1,Enable3DSound); 

    LoadWaveFile(SOUND_BONE1	     	,"Data\\Sound\\mBone1.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_BONE2    		,"Data\\Sound\\mBone2.wav",2,Enable3DSound);
    LoadWaveFile(SOUND_ASSASSIN		    ,"Data\\Sound\\mAssassin1.wav",1,Enable3DSound);
#endif

	////////// �ѱ�/�ܱ� ���뿵�� /////////////////////////////////////////////////////////

	LoadWaveFile(SOUND_ATTACK01			,"Data\\Sound\\eMeleeHit1.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+1     	,"Data\\Sound\\eMeleeHit2.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+2		,"Data\\Sound\\eMeleeHit3.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+3		,"Data\\Sound\\eMeleeHit4.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+4		,"Data\\Sound\\eMeleeHit5.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+5		,"Data\\Sound\\eMissileHit1.wav",2); 
    LoadWaveFile(SOUND_ATTACK01+6		,"Data\\Sound\\eMissileHit2.wav",2); 
	LoadWaveFile(SOUND_ATTACK01+7		,"Data\\Sound\\eMissileHit3.wav",2);
	LoadWaveFile(SOUND_ATTACK01+8		,"Data\\Sound\\eMissileHit4.wav",2);

    LoadWaveFile(SOUND_FIRECRACKER1	    ,"Data\\Sound\\eFirecracker1.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_FIRECRACKER2	    ,"Data\\Sound\\eFirecracker2.wav",1,Enable3DSound);
    LoadWaveFile(SOUND_MEDAL	        ,"Data\\Sound\\eMedal.wav",1,Enable3DSound);
	LoadWaveFile(SOUND_PHOENIXEXP		,"Data\\Sound\\ePhoenixExp.wav",1,Enable3DSound);
//	LoadWaveFile(SOUND_PHOENIXFIRE		,"Data\\Sound\\ePhoenixFire.wav",1,Enable3DSound);

#ifdef TAMAJJANG
    LoadWaveFile( SOUND_TAMAJJANG1,      "Data\\Sound\\aTamajjang1.wav", 1, Enable3DSound );
    LoadWaveFile( SOUND_TAMAJJANG2,      "Data\\Sound\\aTamajjang2.wav", 1, Enable3DSound );
#endif

    LoadWaveFile(SOUND_RIDINGSPEAR		,"Data\\Sound\\eRidingSpear.wav",1);
	LoadWaveFile(SOUND_RAIDSHOOT		,"Data\\Sound\\eRaidShoot.wav",1);
	LoadWaveFile(SOUND_SWELLLIFE		,"Data\\Sound\\eSwellLife.wav",1);
	LoadWaveFile(SOUND_PIERCING			,"Data\\Sound\\ePiercing.wav",1);
	LoadWaveFile(SOUND_ICEARROW			,"Data\\Sound\\eIceArrow.wav",1);
	LoadWaveFile(SOUND_TELEKINESIS		,"Data\\Sound\\eTelekinesis.wav",1);
	LoadWaveFile(SOUND_SOULBARRIER      ,"Data\\Sound\\eSoulBarrier.wav",1);
	LoadWaveFile(SOUND_BLOODATTACK      ,"Data\\Sound\\eBloodAttack.wav",1);

	LoadWaveFile(SOUND_HIT_GATE         ,"Data\\Sound\\eHitGate.wav",1);
	LoadWaveFile(SOUND_HIT_GATE2        ,"Data\\Sound\\eHitGate2.wav",1);
	LoadWaveFile(SOUND_HIT_CRISTAL      ,"Data\\Sound\\eHitCristal.wav",1);
	LoadWaveFile(SOUND_DOWN_GATE        ,"Data\\Sound\\eDownGate.wav",1);
	LoadWaveFile(SOUND_CROW             ,"Data\\Sound\\eCrow.wav",1);

	LoadWaveFile ( SOUND_DEATH_POISON1, "Data\\Sound\\eBlastPoison_1.wav", 2 );
	LoadWaveFile ( SOUND_DEATH_POISON2, "Data\\Sound\\eBlastPoison_2.wav", 2 );
	LoadWaveFile ( SOUND_SUDDEN_ICE1  , "Data\\Sound\\eSuddenIce_1.wav", 2 );
	LoadWaveFile ( SOUND_SUDDEN_ICE2  , "Data\\Sound\\eSuddenIce_2.wav", 2 );
	LoadWaveFile ( SOUND_NUKE1		  , "Data\\Sound\\eHellFire2_1.wav", 1 );
	LoadWaveFile ( SOUND_NUKE2		  , "Data\\Sound\\eHellFire2_2.wav", 1 );
	LoadWaveFile ( SOUND_COMBO		  , "Data\\Sound\\eCombo.wav", 1 );
	LoadWaveFile ( SOUND_FURY_STRIKE1 , "Data\\Sound\\eRageBlow_1.wav", 1 );
	LoadWaveFile ( SOUND_FURY_STRIKE2 , "Data\\Sound\\eRageBlow_2.wav", 1 );
	LoadWaveFile ( SOUND_FURY_STRIKE3 , "Data\\Sound\\eRageBlow_3.wav", 1 );
	LoadWaveFile ( SOUND_LEVEL_UP	  , "Data\\Sound\\pLevelUp.wav", 1 );
	LoadWaveFile ( SOUND_CHANGE_UP	  , "Data\\Sound\\nMalonSkillMaster.wav", 1 );

	LoadWaveFile ( SOUND_CHAOS_ENVIR,       "Data\\Sound\\aChaos.wav", 1 );
	LoadWaveFile ( SOUND_CHAOS_END,         "Data\\Sound\\aChaosEnd.wav", 1 );
	LoadWaveFile ( SOUND_CHAOS_FALLING,     "Data\\Sound\\pMaleScream.wav", 1 );
	LoadWaveFile ( SOUND_CHAOS_FALLING_STONE,"Data\\Sound\\eWallFall.wav", 1 );
	LoadWaveFile ( SOUND_CHAOS_MOB_BOOM01,  "Data\\Sound\\eMonsterBoom1.wav", 2 );
	LoadWaveFile ( SOUND_CHAOS_MOB_BOOM02,  "Data\\Sound\\eMonsterBoom2.wav", 2 );
	LoadWaveFile ( SOUND_CHAOS_THUNDER01,   "Data\\Sound\\eElec1.wav", 1 );
	LoadWaveFile ( SOUND_CHAOS_THUNDER02,   "Data\\Sound\\eElec2.wav", 1 );

    LoadWaveFile ( SOUND_RUN_DARK_HORSE_1,      "Data\\Sound\\pHorseStep1.wav", 1 );
    LoadWaveFile ( SOUND_RUN_DARK_HORSE_2,      "Data\\Sound\\pHorseStep2.wav", 1 );
    LoadWaveFile ( SOUND_RUN_DARK_HORSE_3,      "Data\\Sound\\pHorseStep3.wav", 1 );
    LoadWaveFile ( SOUND_DARKLORD_PAIN,         "Data\\Sound\\pDarkPain.wav", 1 );
    LoadWaveFile ( SOUND_DARKLORD_DEAD,         "Data\\Sound\\pDarkDeath.wav", 1 );
    LoadWaveFile ( SOUND_ATTACK_SPEAR,          "Data\\Sound\\sDarkSpear.wav", 1 );
    LoadWaveFile ( SOUND_ATTACK_FIRE_BUST,      "Data\\Sound\\eFirebust.wav", 1 );
    LoadWaveFile ( SOUND_ATTACK_FIRE_BUST_EXP,  "Data\\Sound\\eFirebustBoom.wav", 1 );
    LoadWaveFile ( SOUND_PART_TELEPORT,         "Data\\Sound\\eSummon.wav", 1 );
    LoadWaveFile ( SOUND_ELEC_STRIKE,           "Data\\Sound\\sDarkElecSpike.wav", 1 );
    LoadWaveFile ( SOUND_ELEC_STRIKE_READY,     "Data\\Sound\\sDarkElecSpikeReady.wav", 1 );
    LoadWaveFile ( SOUND_EARTH_QUAKE,           "Data\\Sound\\sDarkEarthQuake.wav", 1 );
    LoadWaveFile ( SOUND_CRITICAL,              "Data\\Sound\\sDarkCritical.wav", 1 );
    LoadWaveFile ( SOUND_DSPIRIT_MISSILE,       "Data\\Sound\\DSpirit_Missile.wav", 4 );
    LoadWaveFile ( SOUND_DSPIRIT_SHOUT,         "Data\\Sound\\DSpirit_Shout.wav", 1 );
    LoadWaveFile ( SOUND_DSPIRIT_RUSH,          "Data\\Sound\\DSpirit_Rush.wav", 3 );
	
	//^ �渱 ���� ����
	LoadWaveFile ( SOUND_FENRIR_RUN_1,		"Data\\Sound\\pW_run-01.wav",	1 );	// �渱 �޸��� ���� 1
	LoadWaveFile ( SOUND_FENRIR_RUN_2,      "Data\\Sound\\pW_run-02.wav",	1 );	// �渱 �޸��� ���� 2
	LoadWaveFile ( SOUND_FENRIR_RUN_3,      "Data\\Sound\\pW_run-03.wav",	1 );	// �渱 �޸��� ���� 3
	LoadWaveFile ( SOUND_FENRIR_WALK_1,     "Data\\Sound\\pW_step-01.wav",	1 );	// �渱 �ȱ� ���� 1
	LoadWaveFile ( SOUND_FENRIR_WALK_2,     "Data\\Sound\\pW_step-02.wav",	1 );	// �渱 �ȱ� ���� 2
	LoadWaveFile ( SOUND_FENRIR_DEATH,		"Data\\Sound\\pWdeath.wav",		1 );	// �渱 �ױ� ����
	LoadWaveFile ( SOUND_FENRIR_IDLE_1,     "Data\\Sound\\pWidle1.wav",		1 );	// �渱 ���� ���� 1
	LoadWaveFile ( SOUND_FENRIR_IDLE_2,     "Data\\Sound\\pWidle2.wav",		1 );	// �渱 ���� ���� 2
	LoadWaveFile ( SOUND_FENRIR_DAMAGE_1,   "Data\\Sound\\pWpain1.wav",		1 );	// �渱 ������ ���� 1
	LoadWaveFile ( SOUND_FENRIR_DAMAGE_1,   "Data\\Sound\\pWpain2.wav",		1 );	// �渱 ������ ���� 2
	LoadWaveFile ( SOUND_FENRIR_SKILL,		"Data\\Sound\\pWskill.wav",		1 );	// �渱 ��ų ����
	LoadWaveFile(SOUND_JEWEL02,				"Data\\Sound\\Jewel_Sound.wav",1);	// ���� �������� �Ҹ�

#ifdef WORLDCUP_ADD
	LoadWaveFile ( SOUND_WORLDCUP_RND1,	"Data\\Sound\\handclap-01.wav",	1 );			
	LoadWaveFile ( SOUND_WORLDCUP_RND2,	"Data\\Sound\\handclap-02.wav",	1 );		
	LoadWaveFile ( SOUND_WORLDCUP_RND3,	"Data\\Sound\\handclap-03.wav",	1 );		
	LoadWaveFile ( SOUND_WORLDCUP_RND4,	"Data\\Sound\\handclap-04.wav",	1 );		
	LoadWaveFile ( SOUND_WORLDCUP_RND5,	"Data\\Sound\\handclap-05.wav",	1 );		
	LoadWaveFile ( SOUND_WORLDCUP_RND6,	"Data\\Sound\\handclap-06.wav",	1 );		
#endif

	LoadWaveFile ( SOUND_KUNDUN_ITEM_SOUND,	"Data\\Sound\\kundunitem.wav",	1 );

	g_XmasEvent->LoadXmasEventSound();
	g_NewYearsDayEvent->LoadSound();
	
	LoadWaveFile ( SOUND_SHIELDCLASH,	"Data\\Sound\\shieldclash.wav",	1 );
	LoadWaveFile ( SOUND_INFINITYARROW,	"Data\\Sound\\infinityArrow.wav",	1 );
	//SOUND_FIRE_SCREAM
	LoadWaveFile ( SOUND_FIRE_SCREAM,	"Data\\Sound\\Darklord_firescream.wav",	1 );

#ifdef PRUARIN_EVENT07_3COLORHARVEST
	LoadWaveFile ( SOUND_MOONRABBIT_WALK,		"Data\\Sound\\SE_Ev_rabbit_walk.wav",	1 );
	LoadWaveFile ( SOUND_MOONRABBIT_DAMAGE,		"Data\\Sound\\SE_Ev_rabbit_damage.wav", 1 );
	LoadWaveFile ( SOUND_MOONRABBIT_DEAD,		"Data\\Sound\\SE_Ev_rabbit_death.wav", 1 );
	LoadWaveFile ( SOUND_MOONRABBIT_EXPLOSION,	"Data\\Sound\\SE_Ev_rabbit_Explosion.wav", 1 );
#endif // PRUARIN_EVENT07_3COLORHARVEST

//	LoadWaveFile(SOUND_SUMMON_CASTING,		"Data\\Sound\\eSummon.wav"	,1);	// ��ȯ �Ҹ�
	LoadWaveFile(SOUND_SUMMON_SAHAMUTT,		"Data\\Sound\\SE_Ch_summoner_skill05_explosion01.wav"	,1);	// ������ �Ҹ�
	LoadWaveFile(SOUND_SUMMON_EXPLOSION,	"Data\\Sound\\SE_Ch_summoner_skill05_explosion03.wav"	,1);	// ������ ���� �Ҹ�
	LoadWaveFile(SOUND_SUMMON_NEIL,			"Data\\Sound\\SE_Ch_summoner_skill06_requiem01.wav"		,1);	// �� �Ҹ�
	LoadWaveFile(SOUND_SUMMON_REQUIEM,		"Data\\Sound\\SE_Ch_summoner_skill06_requiem02.wav"		,1);	// �� ���� �Ҹ�
#ifdef ASG_ADD_SUMMON_RARGLE_SOUND
	LoadWaveFile(SOUND_SUMMOM_RARGLE, "Data\\Sound\\Rargle.wav", 1);	// ��ȯ�� ���.
#endif	// ASG_ADD_SUMMON_RARGLE_SOUND
	LoadWaveFile(SOUND_SUMMON_SKILL_LIGHTORB,	"Data\\Sound\\SE_Ch_summoner_skill01_lightningof.wav"	,1);
	LoadWaveFile(SOUND_SUMMON_SKILL_SLEEP,		"Data\\Sound\\SE_Ch_summoner_skill03_sleep.wav"			,1);
	LoadWaveFile(SOUND_SUMMON_SKILL_BLIND,		"Data\\Sound\\SE_Ch_summoner_skill04_blind.wav"			,1);
	LoadWaveFile(SOUND_SUMMON_SKILL_THORNS,		"Data\\Sound\\SE_Ch_summoner_skill02_ssonze.wav"		,1);
	LoadWaveFile(SOUND_SKILL_CHAIN_LIGHTNING,	"Data\\Sound\\SE_Ch_summoner_skill08_chainlightning.wav",1);
	LoadWaveFile(SOUND_SKILL_DRAIN_LIFE,		"Data\\Sound\\SE_Ch_summoner_skill07_lifedrain.wav"		,1);
	LoadWaveFile(SOUND_SKILL_WEAKNESS, "Data\\Sound\\SE_Ch_summoner_weakness.wav", 1);
	LoadWaveFile(SOUND_SKILL_ENERVATION, "Data\\Sound\\SE_Ch_summoner_innovation.wav", 1);
#ifdef ASG_ADD_SKILL_BERSERKER_SOUND
	LoadWaveFile(SOUND_SKILL_BERSERKER, "Data\\Sound\\Berserker.wav", 1);	// ����Ŀ ��ų.
#endif	// ASG_ADD_SKILL_BERSERKER_SOUND
#ifdef CSK_EVENT_CHERRYBLOSSOM
	LoadWaveFile(SOUND_CHERRYBLOSSOM_EFFECT0, "Data\\Sound\\cherryblossom\\Eve_CherryBlossoms01.wav");
	LoadWaveFile(SOUND_CHERRYBLOSSOM_EFFECT1, "Data\\Sound\\cherryblossom\\Eve_CherryBlossoms02.wav");
#endif //CSK_EVENT_CHERRYBLOSSOM

#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
	LoadWaveFile(SOUND_SKILL_BLOWOFDESTRUCTION, "Data\\Sound\\BLOW_OF_DESTRUCTION.wav");
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION_SOUND
	
#ifdef YDG_ADD_SKILL_FLAME_STRIKE_SOUND
	LoadWaveFile(SOUND_SKILL_FLAME_STRIKE, "Data\\Sound\\flame_strike.wav");
#endif	// YDG_ADD_SKILL_FLAME_STRIKE_SOUND
#ifdef YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
	LoadWaveFile(SOUND_SKILL_GIGANTIC_STORM, "Data\\Sound\\gigantic_storm.wav");
#endif	// YDG_ADD_SKILL_GIGANTIC_STORM_SOUND
#ifdef YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND
	LoadWaveFile(SOUND_SKILL_LIGHTNING_SHOCK, "Data\\Sound\\lightning_shock.wav");
#endif	// YDG_ADD_SKILL_LIGHTNING_SHOCK_SOUND

#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND
	LoadWaveFile(SOUND_SKILL_SWELL_OF_MAGICPOWER, "Data\\Sound\\SwellofMagicPower.wav");	// �������� (������)
#endif	// KJH_ADD_SKILL_SWELL_OF_MAGICPOWER_SOUND

#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
	LoadWaveFile(SOUND_SKILL_MULTI_SHOT, "Data\\Sound\\multi_shot.wav");	//��Ƽ��
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	LoadWaveFile(SOUND_SKILL_RECOVER, "Data\\Sound\\recover.wav");	//ȹ��
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	LoadWaveFile(SOUND_SKILL_CAOTIC, "Data\\Sound\\caotic.wav");	//��ũ�ε� �űԽ�ų
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC	

#ifdef YDG_ADD_FIRECRACKER_ITEM
	LoadWaveFile(SOUND_XMAS_FIRECRACKER, "Data\\Sound\\xmas\\Christmas_Fireworks01.wav");
#endif	// YDG_ADD_FIRECRACKER_ITEM

#ifdef KJH_ADD_09SUMMER_EVENT
	g_09SummerEvent->LoadSound();
#endif // KJH_ADD_09SUMMER_EVENT

#ifdef PBG_ADD_NEWCHAR_MONK
	LoadWaveFile(SOUND_RAGESKILL_THRUST, "Data\\Sound\\Ragefighter\\Rage_Thrust.wav");
	LoadWaveFile(SOUND_RAGESKILL_THRUST_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Thrust_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_STAMP, "Data\\Sound\\Ragefighter\\Rage_Stamp.wav");
	LoadWaveFile(SOUND_RAGESKILL_STAMP_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Stamp_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_GIANTSWING, "Data\\Sound\\Ragefighter\\Rage_Giantswing.wav");
	LoadWaveFile(SOUND_RAGESKILL_GIANTSWING_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Giantswing_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_DARKSIDE, "Data\\Sound\\Ragefighter\\Rage_Darkside.wav");
	LoadWaveFile(SOUND_RAGESKILL_DARKSIDE_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Darkside_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_DRAGONLOWER, "Data\\Sound\\Ragefighter\\Rage_Dragonlower.wav");
	LoadWaveFile(SOUND_RAGESKILL_DRAGONLOWER_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Dragonlower_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_DRAGONKICK, "Data\\Sound\\Ragefighter\\Rage_Dragonkick.wav");
	LoadWaveFile(SOUND_RAGESKILL_DRAGONKICK_ATTACK, "Data\\Sound\\Ragefighter\\Rage_Dragonkick_Att.wav");
	LoadWaveFile(SOUND_RAGESKILL_BUFF_1, "Data\\Sound\\Ragefighter\\Rage_Buff_1.wav");
	LoadWaveFile(SOUND_RAGESKILL_BUFF_2, "Data\\Sound\\Ragefighter\\Rage_Buff_2.wav");
#endif //PBG_ADD_NEWCHAR_MONK

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENSOUNDS );
#endif // DO_PROFILING_FOR_LOADING
}
///////////////////////////////////////////////////////////////////////////////
// ��Ʈ DIB �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ��Ʈ �ؽ��� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

extern int	g_iRenderTextType;

void OpenFont()
{
   	InitPath();

    LoadBitmap("Interface\\FontInput.tga"     ,BITMAP_FONT    ,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Interface\\FontTest.tga"      ,BITMAP_FONT+1  );
	LoadBitmap("Interface\\Hit.tga"			,BITMAP_FONT_HIT,GL_NEAREST,GL_CLAMP);

	g_pRenderText->Create(0, g_hDC);	//. ���߿� ���׷��̵� �ؼ� Ÿ�� �Ѱ��ٰ�
}

///////////////////////////////////////////////////////////////////////////////
// ��ũ�� �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void SaveMacro(char *FileName)
{
	FILE *fp = fopen(FileName,"wt");
	for(int i=0;i<10;i++)
	{
		fprintf(fp,"%s\n",MacroText[i]);
	}
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////
// ��ũ�� �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenMacro(char *FileName)
{
	FILE *fp = fopen(FileName,"rt");
	if(fp == NULL) return;
	for(int i=0;i<10;i++)
	{
		fscanf(fp,"%s",MacroText[i]);
	}
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////
// ��ų��Ű ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void SaveOptions()
{
#ifdef CSK_FIX_SKILLHOTKEY_PACKET

	// 0 ~ 19 skill hotkey
	BYTE options[30] = { 0x00, };

	int iSkillType = -1;
	for(int i=0; i<10; ++i)
	{
#ifdef LDK_ADD_SCALEFORM
		//gfxui ���� ���� ui ��� ����
		if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
		{
			iSkillType = g_pMainFrame->GetSkillHotKey(i);
		}
		else 
		{
			iSkillType = GFxProcess::GetInstancePtr()->GetSkillHotKey( i == 0 ? 10 : i);
		}
#else //LDK_ADD_SCALEFORM
		iSkillType = g_pMainFrame->GetSkillHotKey(i);
#endif //LDK_ADD_SCALEFORM
		int iIndex = i * 2;
		if(iSkillType != -1)
		{
			
			options[iIndex] = HIBYTE(CharacterAttribute->Skill[iSkillType]);
			options[iIndex+1] = LOBYTE(CharacterAttribute->Skill[iSkillType]);
		}
		else
		{
			options[iIndex] = 0xff;
			options[iIndex+1] = 0xff;
		}
	}

	// 20
	// �ڵ����� On/Off.
	if( g_pOption->IsAutoAttack() )
	{
		options[20] |= AUTOATTACK_ON;
	}
	else
	{
		options[20] |= AUTOATTACK_OFF;
    }

	// �ӼӸ� On/Off.
	if(g_pOption->IsWhisperSound())
	{
		options[20] |= WHISPER_SOUND_ON;
	}
	else
	{
		options[20] |= WHISPER_SOUND_OFF;
    }

	//  ������ �ɼ�.
	if(g_pOption->IsSlideHelp() == false)
	{
		options[20] |= SLIDE_HELP_OFF;
    }

	// 21 ~ 23
	// q, w, e, r ������ ����Ű	
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
	int iItemType = 0;

#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_Q);
	}
	else 
	{
		iItemType = GFxProcess::GetInstancePtr()->GetItemHotKey(SEASON3B::HOTKEY_Q);
	}
#else //LDK_ADD_SCALEFORM
	iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_Q);
#endif //LDK_ADD_SCALEFORM
	if( iItemType != -1 ) {
		options[21] = static_cast<BYTE>((iItemType - ITEM_POTION) & 0xFF);
	}
	else {
		options[21] = 0xFF;
	}

#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_W);
	}
	else 
	{
		iItemType = GFxProcess::GetInstancePtr()->GetItemHotKey(SEASON3B::HOTKEY_W);
	}
#else //LDK_ADD_SCALEFORM
	iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_W);
#endif //LDK_ADD_SCALEFORM
	if( iItemType != -1 ) {
		options[22] = static_cast<BYTE>((iItemType - ITEM_POTION) & 0xFF);
	}
	else {
		options[22] = 0xFF;
	}

#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_E);
	}
	else 
	{
		iItemType = GFxProcess::GetInstancePtr()->GetItemHotKey(SEASON3B::HOTKEY_E);
	}
#else //LDK_ADD_SCALEFORM
	iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_E);
#endif //LDK_ADD_SCALEFORM
	if( iItemType != -1 ) {
		options[23] = static_cast<BYTE>((iItemType - ITEM_POTION) & 0xFF);
	}
	else {
		options[23] = 0xFF;
	}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
	options[21] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_Q) - ITEM_POTION;
	options[22] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_W) - ITEM_POTION;
	options[23] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_E) - ITEM_POTION;
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING

	// 24
	BYTE wChatListBoxSize = g_pChatListBox->GetNumberOfLines(g_pChatListBox->GetCurrentMsgType()) / 3;
	if (g_bUseChatListBox == FALSE) 
		wChatListBoxSize = 0;
	BYTE wChatListBoxBackAlpha = g_pChatListBox->GetBackAlpha() * 10;
	options[24] = wChatListBoxSize << 4 | wChatListBoxBackAlpha;

	// 25 ~ 29
#ifdef KJH_FIX_ITEMHOTKEYINFO_CASTING
#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_R);
	}
	else 
	{
		iItemType = GFxProcess::GetInstancePtr()->GetItemHotKey(SEASON3B::HOTKEY_R);
	}
#else //LDK_ADD_SCALEFORM
	iItemType = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_R);
#endif //LDK_ADD_SCALEFORM
	if( iItemType != -1 ) {
		options[25] = (BYTE)((iItemType - ITEM_POTION) & 0xFF);
	}
	else {
		options[25] = 0xFF;
	}
#else // KJH_FIX_ITEMHOTKEYINFO_CASTING
	options[25] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_R) - ITEM_POTION;
#endif // KJH_FIX_ITEMHOTKEYINFO_CASTING

#ifdef LDK_ADD_SCALEFORM
	//gfxui ���� ���� ui ��� ����
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 0)
	{
		options[26] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_Q);
		options[27] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_W);
		options[28] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_E);
		options[29] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_R);
	}
	else 
	{
		options[26] = GFxProcess::GetInstancePtr()->GetItemHotKeyLevel(SEASON3B::HOTKEY_Q);
		options[27] = GFxProcess::GetInstancePtr()->GetItemHotKeyLevel(SEASON3B::HOTKEY_W);
		options[28] = GFxProcess::GetInstancePtr()->GetItemHotKeyLevel(SEASON3B::HOTKEY_E);
		options[29] = GFxProcess::GetInstancePtr()->GetItemHotKeyLevel(SEASON3B::HOTKEY_R);
	}
#else //LDK_ADD_SCALEFORM
	options[26] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_Q);
	options[27] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_W);
	options[28] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_E);
	options[29] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_R);
#endif //LDK_ADD_SCALEFORM

	//  �����͸� ������.
	SendRequestHotKey (options);

#else // CSK_FIX_SKILLHOTKEY_PACKET

	// 0~9 : hotkey, 
	// 10 : autoattack/trade, 
	// 11~13 : qwe key item.
	// 14 : chat
	// 15 : r key item

	BYTE options[20] = { 0x00, };
	
	int iSkillType = -1;
	for(int i=0; i<10; ++i)
	{
		iSkillType = g_pMainFrame->GetSkillHotKey(i);
		if(iSkillType != -1)
		{
			options[i] = CharacterAttribute->Skill[iSkillType];
		}
		else
		{
			options[i] = 0xff;
		}
	}

    //  �ڵ����� On/Off.
	if ( g_pOption->IsAutoAttack() )
    {
        options[10] |= AUTOATTACK_ON;
    }
    else
    {
        options[10] |= AUTOATTACK_OFF;
    }

    //  �ӼӸ� On/Off.
	if(g_pOption->IsWhisperSound())
    {
        options[10] |= WHISPER_SOUND_ON;
    }
    else
    {
        options[10] |= WHISPER_SOUND_OFF;
    }

    //  ������ �ɼ�.
	if(g_pOption->IsSlideHelp() == false)
    {
        options[10] |= SLIDE_HELP_OFF;
    }

	// q, w, e, r ������ ����Ű
	options[11] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_Q) - ITEM_POTION;
	options[12] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_W) - ITEM_POTION;
	options[13] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_E) - ITEM_POTION;

	//  ä��â ����
#ifdef KJH_FIX_UI_CHAT_MESSAGE
	BYTE wChatListBoxSize = g_pChatListBox->GetNumberOfLines(g_pChatListBox->GetCurrentMsgType()) / 3;
#else // KJH_FIX_UI_CHAT_MESSAGE			// ������ �� ������ �ϴ� �ҽ�
	BYTE wChatListBoxSize = g_pChatListBox->GetNumberOfLines() / 3;
#endif // KJH_FIX_UI_CHAT_MESSAGE			// ������ �� ������ �ϴ� �ҽ�

	if (g_bUseChatListBox == FALSE) wChatListBoxSize = 0;
	BYTE wChatListBoxBackAlpha = g_pChatListBox->GetBackAlpha() * 10;

	options[14] = wChatListBoxSize << 4 | wChatListBoxBackAlpha;

	options[15] = g_pMainFrame->GetItemHotKey(SEASON3B::HOTKEY_R) - ITEM_POTION;
	options[16] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_Q);
	options[17] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_W);
	options[18] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_E);
	options[19] = g_pMainFrame->GetItemHotKeyLevel(SEASON3B::HOTKEY_R);

	//  �����͸� ������.
	SendRequestHotKey (options);

#endif // CSK_FIX_SKILLHOTKEY_PACKET

}

///////////////////////////////////////////////////////////////////////////////
// �����Է¹޴� ���� �ʿ��� ����Ÿ �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenLogoSceneData()
{
#ifndef PJH_NEW_SERVER_SELECT_MAP
	AccessModel(MODEL_LOGO+2,"Data\\Logo\\","Logo",3);
    OpenTexture(MODEL_LOGO+2,"Logo\\",GL_REPEAT, GL_LINEAR);
#endif //PJH_NEW_SERVER_SELECT_MAP
	//image
	::LoadBitmap("Interface\\cha_bt.tga", BITMAP_LOG_IN);				// �����׷� ��ư.
	::LoadBitmap("Interface\\server_b2_all.tga", BITMAP_LOG_IN+1);		// ���� ��ư.
	::LoadBitmap("Interface\\server_b2_loding.jpg", BITMAP_LOG_IN+2);	// ���� ȥ�� ������.
	::LoadBitmap("Interface\\server_deco_all.tga", BITMAP_LOG_IN+3);	// �����׷� ��ư ���.
	::LoadBitmap("Interface\\server_menu_b_all.tga", BITMAP_LOG_IN+4);	// �޴� ��ư.
	::LoadBitmap("Interface\\server_credit_b_all.tga", BITMAP_LOG_IN+5);// ũ���� ��ư.
	::LoadBitmap("Interface\\deco.tga", BITMAP_LOG_IN+6);				// ũ���� ��ư ���.
	::LoadBitmap("Interface\\login_back.tga", BITMAP_LOG_IN+7);		// �α��� â ���.
	::LoadBitmap("Interface\\login_me.tga", BITMAP_LOG_IN+8);			// �α��� â �Է� ����.
	::LoadBitmap("Interface\\server_ex03.tga", BITMAP_LOG_IN+11, GL_NEAREST, GL_REPEAT);		// ���� ���� ��� �߾�.
	::LoadBitmap("Interface\\server_ex01.tga", BITMAP_LOG_IN+12);		// ���� ���� ��� ����.
	::LoadBitmap("Interface\\server_ex02.jpg", BITMAP_LOG_IN+13, GL_NEAREST, GL_REPEAT);		// ���� ���� ��� �¿�.
	::LoadBitmap("Interface\\cr_mu_lo.tga", BITMAP_LOG_IN+14, GL_LINEAR);// ũ���� â �ϴ� �� �ΰ�.
#ifdef MOVIE_DIRECTSHOW
	::LoadBitmap("Interface\\movie_b_all.tga", BITMAP_LOG_IN+15);// ������ ��ư.
#endif	// MOVIE_DIRECTSHOW

}

///////////////////////////////////////////////////////////////////////////////
// �����Է¹޴� ���� �ʿ��� ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReleaseLogoSceneData()
{
#ifdef _VS2008PORTING
	for (int i = BITMAP_LOG_IN; i <= BITMAP_LOG_IN_END; ++i)
		::DeleteBitmap(i);
	for(int i=BITMAP_TEMP;i<BITMAP_TEMP+30;i++)
		DeleteBitmap(i);
#else // _VS2008PORTING
	int i;

	for (i = BITMAP_LOG_IN; i <= BITMAP_LOG_IN_END; ++i)
		::DeleteBitmap(i);
	for(i=BITMAP_TEMP;i<BITMAP_TEMP+30;i++)
     	DeleteBitmap(i);
#endif // _VS2008PORTING

	DeleteObjects();
	
	ClearCharacters();
}

///////////////////////////////////////////////////////////////////////////////
// ĳ���� �����ϴ� ���� �ʿ��� ����Ÿ �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////

void OpenCharacterSceneData()
{
	LoadBitmap("Interface\\cha_id.tga", BITMAP_LOG_IN);			// ĳ���� �̸� �Էºκ�.
	LoadBitmap("Interface\\cha_bt.tga", BITMAP_LOG_IN+1);		// ĳ���� ���� ��ư.
	LoadBitmap("Interface\\deco.tga", BITMAP_LOG_IN+2);			// �� �޴� ������ ���.
	LoadBitmap("Interface\\b_create.tga", BITMAP_LOG_IN+3);		// ĳ���� ���� ��ư.
	LoadBitmap("Interface\\server_menu_b_all.tga", BITMAP_LOG_IN+4);// �޴� ��ư.
	LoadBitmap("Interface\\b_connect.tga", BITMAP_LOG_IN+5);		// ���ӽ��� ��ư.
	LoadBitmap("Interface\\b_delete.tga", BITMAP_LOG_IN+6);		// ĳ���� ���� ��ư.
	LoadBitmap("Interface\\character_ex.tga", BITMAP_LOG_IN+7);	// ĳ���� ���� ǳ��.
	::LoadBitmap("Interface\\server_ex03.tga", BITMAP_LOG_IN+11, GL_NEAREST, GL_REPEAT);		// ���� �޽��� â ��� �߾�.
	::LoadBitmap("Interface\\server_ex01.tga", BITMAP_LOG_IN+12);		// ���� �޽��� â ��� ����.
	::LoadBitmap("Interface\\server_ex02.jpg", BITMAP_LOG_IN+13, GL_NEAREST, GL_REPEAT);		// ���� �޽��� â ��� �¿�.
	LoadBitmap("Effect\\Impack03.jpg"			, BITMAP_EXT_LOG_IN+2);
	LoadBitmap("Logo\\chasellight.jpg"		, BITMAP_EFFECT);
    
	int Class = MAX_CLASS;

	for(int i=4;i<5;i++)
      	AccessModel(MODEL_LOGO+i,"Data\\Logo\\","Logo",i+1);

#ifdef _VS2008PORTING
	for(int i=0;i<Class;i++)
#else // _VS2008PORTING
	for(i=0;i<Class;i++)
#endif // _VS2008PORTING
     	AccessModel(MODEL_FACE+i,"Data\\Logo\\","NewFace",i+1);
	
#ifdef _VS2008PORTING
	for(int i=4;i<5;i++)
#else // _VS2008PORTING
	for(i=4;i<5;i++)
#endif // _VS2008PORTING
     	OpenTexture(MODEL_LOGO+i,"Logo\\", GL_REPEAT, GL_LINEAR);
#ifdef _VS2008PORTING
	for(int i=0;i<Class;i++)
#else // _VS2008PORTING
	for(i=0;i<Class;i++)
#endif // _VS2008PORTING
     	OpenTexture(MODEL_FACE+i,"Logo\\");

#ifdef _VS2008PORTING
	for(int i=0;i<Class;i++)
#else // _VS2008PORTING
	for(i=0;i<Class;i++)
#endif // _VS2008PORTING
	{
		Models[MODEL_FACE+i].Actions[0].PlaySpeed = 0.3f;
		Models[MODEL_FACE+i].Actions[1].PlaySpeed = 0.3f;
	}
	// ��ȯ������ �� ���� �ִϸ��̼� �ӵ��� �ٸ�.
	Models[MODEL_FACE+CLASS_SUMMONER].Actions[0].PlaySpeed = 0.25f;
}

///////////////////////////////////////////////////////////////////////////////
// ĳ���� �����ϴ� ���� �ʿ��� ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReleaseCharacterSceneData()
{
#ifdef _VS2008PORTING
	for (int i = BITMAP_LOG_IN; i <= BITMAP_LOG_IN_END; ++i)
		::DeleteBitmap(i);

	for(int i=BITMAP_TEMP;i<BITMAP_EXT_LOG_IN + 7;i++)
		DeleteBitmap(i);
#else // _VS2008PORTING
	int i;
	for (i = BITMAP_LOG_IN; i <= BITMAP_LOG_IN_END; ++i)
		::DeleteBitmap(i);

	for(i=BITMAP_TEMP;i<BITMAP_EXT_LOG_IN + 7;i++)
     	DeleteBitmap(i);
#endif // _VS2008PORTING

	DeleteObjects();

#ifdef _VS2008PORTING
	for(int i=0;i<MAX_CLASS;i++)
#else // _VS2008PORTING
	for(i=0;i<MAX_CLASS;i++)
#endif // _VS2008PORTING
		Models[MODEL_FACE+i].Release();

	ClearCharacters();
}

///////////////////////////////////////////////////////////////////////////////
// �⺻������ �ʿ��� �������� ����Ÿ �о���̴� �Լ�
///////////////////////////////////////////////////////////////////////////////
void OpenBasicData(HDC hDC)
{
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENBASICDATA, PROFILING_LOADING_OPENBASICDATA );
#endif // DO_PROFILING_FOR_LOADING

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_PRELOADS, PROFILING_LOADING_PRELOADS );
#endif // DO_PROFILING_FOR_LOADING

	CUIMng& rUIMng = CUIMng::Instance();	// ���� �߰��� UI�Ŵ����� �ν��Ͻ��� ����.

	rUIMng.RenderTitleSceneUI(hDC, 0, 11);

	// =======================================================================================
	// 1. �⺻ Interface �̹��� �� ���ҽ���
	// =======================================================================================
	LoadBitmap("Interface\\Cursor.tga"           ,BITMAP_CURSOR  ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorPush.tga"       ,BITMAP_CURSOR+1,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorAttack.tga"     ,BITMAP_CURSOR+2,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorGet.tga"        ,BITMAP_CURSOR+3,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorTalk.tga"       ,BITMAP_CURSOR+4,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorRepair.tga"     ,BITMAP_CURSOR+5,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorLeanAgainst.tga",BITMAP_CURSOR+6,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorSitDown.tga"    ,BITMAP_CURSOR+7,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\CursorDontMove.tga"   ,BITMAP_CURSOR+8,GL_LINEAR,GL_CLAMP);	
	//interface
	LoadBitmap("Interface\\ok.jpg"             ,BITMAP_INTERFACE+11);
	LoadBitmap("Interface\\ok2.jpg"            ,BITMAP_INTERFACE+12);
	LoadBitmap("Interface\\cancel.jpg"         ,BITMAP_INTERFACE+13);
	LoadBitmap("Interface\\cancel2.jpg"        ,BITMAP_INTERFACE+14);
	LoadBitmap("Interface\\win_titlebar.jpg"	 ,BITMAP_INTERFACE_EX+8);
	LoadBitmap("Interface\\win_button.tga"		 ,BITMAP_INTERFACE_EX+9);
	LoadBitmap("Interface\\win_size.jpg"		 ,BITMAP_INTERFACE_EX+10);
	LoadBitmap("Interface\\win_resize.tga"		 ,BITMAP_INTERFACE_EX+11);
	LoadBitmap("Interface\\win_scrollbar.jpg"	 ,BITMAP_INTERFACE_EX+12);
	LoadBitmap("Interface\\win_check.tga"		 ,BITMAP_INTERFACE_EX+13);
	LoadBitmap("Interface\\win_mail.tga"		 ,BITMAP_INTERFACE_EX+14);
	LoadBitmap("Interface\\win_mark.tga"		 ,BITMAP_INTERFACE_EX+15);
	LoadBitmap("Interface\\win_letter.jpg"	 ,BITMAP_INTERFACE_EX+16);
	LoadBitmap("Interface\\win_man.jpg"		 ,BITMAP_INTERFACE_EX+17);
	LoadBitmap("Interface\\win_push.jpg"		 ,BITMAP_INTERFACE_EX+18);
	LoadBitmap("Interface\\win_question.tga"	 ,BITMAP_INTERFACE_EX+20);
	LoadBitmap("Local\\Webzenlogo.jpg"	 ,BITMAP_INTERFACE_EX+22);

#ifdef DUEL_SYSTEM
	LoadWaveFile(SOUND_OPEN_DUELWINDOW,	"Data\\Sound\\iDuelWindow.wav", 1);
	LoadWaveFile(SOUND_START_DUEL,	"Data\\Sound\\iDuelStart.wav", 1);
#endif // DUEL_SYSTEM
	

#ifdef NEW_USER_INTERFACE_RESOURCEFILE
	int count = 0;
	//BITMAP_NEWUI_SHOP_LEFTBT = 9
	LoadBitmap("Interface\\partCharge1\\LeftBt\\Deco0.tga", BITMAP_NEWUI_SHOP_LEFTBT );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\Deco1.tga", BITMAP_NEWUI_SHOP_LEFTBT+1 );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\Deco2.tga", BITMAP_NEWUI_SHOP_LEFTBT+2 );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\Deco3.tga", BITMAP_NEWUI_SHOP_LEFTBT+3 );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\Deco4.tga", BITMAP_NEWUI_SHOP_LEFTBT+4 );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\LeftMenuBT0.tga", BITMAP_NEWUI_SHOP_LEFTBT+5 );	
	LoadBitmap("Interface\\partCharge1\\LeftBt\\LeftMenuBT1.tga", BITMAP_NEWUI_SHOP_LEFTBT+6 );
	LoadBitmap("Interface\\partCharge1\\LeftBt\\TopMenuTabBT0.tga", BITMAP_NEWUI_SHOP_LEFTBT+7 );	
	LoadBitmap("Interface\\partCharge1\\LeftBt\\TopMenuTabBT1.tga", BITMAP_NEWUI_SHOP_LEFTBT+8 );
	
	//BITMAP_NEWUI_SHOP_LEFTDISPLAYBT = 17
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Buy0.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Buy1.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+1 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Buy2.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+2 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Cash0.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+3 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Cash1.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+4 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Cash2.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+5 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\ItemBackPanel.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+6 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\MiniInventoryPanel.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+7 );
	for ( count = 8; count < 14; ++count )
	{
		string filename = ( format( "Interface\\partCharge1\\ShopDisplay\\page%1%.tga" ) % (count-8) ).str();
		LoadBitmap( const_cast<char*>(filename.c_str()), BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+count );
	}
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\New.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+14 );	
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Hot.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+15 );
	LoadBitmap("Interface\\partCharge1\\ShopDisplay\\Sale.tga", BITMAP_NEWUI_SHOP_LEFTDISPLAYBT+16 );
	
	//BITMAP_NEWUI_SHOP_RIGHTBT = 5
	LoadBitmap("Interface\\partCharge1\\RightBt\\InventoryPanel0.tga", BITMAP_NEWUI_SHOP_RIGHTBT );
	LoadBitmap("Interface\\partCharge1\\RightBt\\InventoryPanel1.tga", BITMAP_NEWUI_SHOP_RIGHTBT+1 );
	LoadBitmap("Interface\\partCharge1\\RightBt\\Return0.tga", BITMAP_NEWUI_SHOP_RIGHTBT+2 );
	LoadBitmap("Interface\\partCharge1\\RightBt\\Return1.tga", BITMAP_NEWUI_SHOP_RIGHTBT+3 );
	LoadBitmap("Interface\\partCharge1\\RightBt\\Return2.tga", BITMAP_NEWUI_SHOP_RIGHTBT+4 );
	
	//BITMAP_NEWUI_SHOP_FRAMESHOPBT = 1
	//LoadBitmap("Interface\\partCharge1\\menu_cashshop.OZJ", BITMAP_NEWUI_SHOP_FRAMESHOPBT );
	
	//BITMAP_NEWUI_SHOP_MAINBACKPANEL = 14
	for( count = 0; count < 14; ++count )
	{
		string filename = ( format( "Interface\\partCharge1\\MainBackPanel\\backpanel%1%.tga" ) % count ).str();
		LoadBitmap( const_cast<char*>(filename.c_str()), 
			BITMAP_NEWUI_SHOP_MAINBACKPANEL+count 
			);
	}
	
	//BITMAP_NEWUI_SHOP_SUBBACKPANEL = 8
	for( count = 0; count < 8; ++count )
	{
		string filename = ( format( "Interface\\partCharge1\\SubBackPanel\\shopback%1%.tga" ) % count ).str();
		LoadBitmap( const_cast<char*>(filename.c_str()), 
			BITMAP_NEWUI_SHOP_SUBBACKPANEL+count 
			);
	}
#endif //NEW_USER_INTERFACE_RESOURCEFILE

	LoadBitmap("Interface\\CursorID.tga",	BITMAP_INTERFACE_EX+29);        //  �߰� Ŀ�� ���̵�.
	LoadBitmap("Interface\\bar.jpg"			,BITMAP_INTERFACE+23);
	LoadBitmap("Interface\\back1.jpg"			,BITMAP_INTERFACE+24);
	LoadBitmap("Interface\\back2.jpg"			,BITMAP_INTERFACE+25);
	LoadBitmap("Interface\\back3.jpg"			,BITMAP_INTERFACE+26);

	// =======================================================================================
	// /������� 1. �⺻ Interface �̹��� �� ���ҽ���
	// =======================================================================================

	//effect
	// =======================================================================================
	// 2. Effect Images��
	// =======================================================================================
	LoadBitmap("Effect\\Fire01.jpg"		,BITMAP_FIRE      ,GL_LINEAR,GL_CLAMP);			// GM3rdChangeUp, GMCrywolf1st,GMHellas,Kanturu 3rd
	LoadBitmap("Effect\\Fire02.jpg"		,BITMAP_FIRE+1    ,GL_LINEAR,GL_CLAMP);			// GM3rdChangeUp, GMCrywolf1st,GMHellas,Kanturu 3rd
	LoadBitmap("Effect\\Fire03.jpg"		,BITMAP_FIRE+2    ,GL_LINEAR,GL_CLAMP);			// GM3rdChangeUp, GMCrywolf1st,GMHellas,Kanturu 3rd
	LoadBitmap("Effect\\PoundingBall.jpg"		,BITMAP_POUNDING_BALL,GL_LINEAR,GL_CLAMP); // Kanturu 2nd
	LoadBitmap( "Effect\\fi01.jpg"		,BITMAP_ADV_SMOKE,  GL_LINEAR, GL_CLAMP );		// GM 3rd ChangeUp, CryingWolf2nd
	LoadBitmap( "Effect\\fi02.tga"	    ,BITMAP_ADV_SMOKE+1,GL_LINEAR, GL_CLAMP );		// GM 3rd ChangeUp, CryingWolf2nd
	LoadBitmap( "Effect\\fantaF.jpg"		,BITMAP_TRUE_FIRE,  GL_LINEAR, GL_CLAMP );	// GM Aida, GMBattleCastle, ....
	LoadBitmap( "Effect\\fantaB.jpg"		,BITMAP_TRUE_BLUE,  GL_LINEAR, GL_CLAMP );  // 
	LoadBitmap( "Effect\\JointSpirit02.jpg" ,BITMAP_JOINT_SPIRIT2  ,GL_LINEAR,GL_CLAMP);
	LoadBitmap( "Effect\\Piercing.jpg" , BITMAP_PIERCING, GL_LINEAR, GL_REPEAT );    //  
	LoadBitmap( "Monster\\iui06.jpg",    BITMAP_ROBE+6 );                            //  ��� ����Ʈ �Ӹ�ī��.
	LoadBitmap( "Effect\\Magic_b.jpg",   BITMAP_MAGIC_EMBLEM );                      //  ��������.
	LoadBitmap("Player\\dark3chima3.tga", BITMAP_DARKLOAD_SKIRT_3RD, GL_LINEAR, GL_CLAMP);
    LoadBitmap( "Player\\kaa.tga",       BITMAP_DARK_LOAD_SKIRT,  GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\ShockWave.jpg", BITMAP_SHOCK_WAVE, GL_LINEAR );             //  
    LoadBitmap("Effect\\Flame01.jpg"		,BITMAP_FLAME     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\flare01.jpg"	    ,BITMAP_LIGHT      ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Magic_Ground1.jpg",BITMAP_MAGIC      ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Magic_Ground2.jpg",BITMAP_MAGIC+1    ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Magic_Circle1.jpg",BITMAP_MAGIC+2    ,GL_LINEAR);
#ifdef ASG_ADD_INFLUENCE_GROUND_EFFECT
	LoadBitmap("Effect\\guild_ring01.jpg", BITMAP_OUR_INFLUENCE_GROUND, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\enemy_ring02.jpg", BITMAP_ENEMY_INFLUENCE_GROUND, GL_LINEAR, GL_CLAMP);
#endif	// ASG_ADD_INFLUENCE_GROUND_EFFECT
	LoadBitmap("Effect\\Spark02.jpg"  	,BITMAP_SPARK     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Spark03.jpg"  	,BITMAP_SPARK+1   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\smoke01.jpg"	    ,BITMAP_SMOKE     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\smoke02.tga"	    ,BITMAP_SMOKE+1   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\smoke05.tga"	    ,BITMAP_SMOKE+4   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\blood01.tga"      ,BITMAP_BLOOD     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\blood.tga"        ,BITMAP_BLOOD+1   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Explotion01.jpg"  ,BITMAP_EXPLOTION ,GL_LINEAR,GL_CLAMP);
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
	LoadBitmap("Skill\\twlighthik01.jpg"  ,BITMAP_TWLIGHT ,GL_LINEAR,GL_CLAMP);
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
	LoadBitmap("Skill\\2line_gost.jpg"  ,BITMAP_2LINE_GHOST ,GL_LINEAR,GL_CLAMP);
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
#ifdef CSK_RAKLION_BOSS
	LoadBitmap("Effect\\damage01mono.jpg", BITMAP_DAMAGE_01_MONO, GL_LINEAR, GL_CLAMP);
#endif // CSK_RAKLION_BOSS
#ifdef CSK_ADD_SKILL_BLOWOFDESTRUCTION
	LoadBitmap("Effect\\SwordEff_mono.jpg", BITMAP_SWORD_EFFECT_MONO, GL_LINEAR, GL_CLAMP);
#endif // CSK_ADD_SKILL_BLOWOFDESTRUCTION
#ifdef YDG_ADD_SKILL_FLAME_STRIKE
	LoadBitmap("Effect\\flamestani.jpg", BITMAP_FLAMESTANI, GL_LINEAR, GL_CLAMP);
#endif	// YDG_ADD_SKILL_FLAME_STRIKE

	LoadBitmap("Effect\\Spark.jpg", BITMAP_SPARK+2, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\firehik02.jpg"  ,BITMAP_FIRE_CURSEDLICH ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Monster\\totemgolem_leaf.tga",BITMAP_LEAF_TOTEMGOLEM ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\empact01.jpg"  ,BITMAP_SUMMON_IMPACT ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\loungexflow.jpg" ,BITMAP_SUMMON_SAHAMUTT_EXPLOSION ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\gostmark01.jpg"  , BITMAP_DRAIN_LIFE_GHOST ,GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\mzine_typer2.jpg", BITMAP_MAGIC_ZIN, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\shiny05.jpg", BITMAP_SHINY+6, GL_LINEAR, GL_CLAMP);
#ifdef ASG_ADD_SKILL_BERSERKER
	LoadBitmap("Effect\\hikorora.jpg", BITMAP_ORORA, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\lightmarks.jpg", BITMAP_LIGHT_MARKS, GL_LINEAR, GL_CLAMP);
#endif	// ASG_ADD_SKILL_BERSERKER
	LoadBitmap("Effect\\cursorpin01.jpg"  , BITMAP_TARGET_POSITION_EFFECT1 ,GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\cursorpin02.jpg"  , BITMAP_TARGET_POSITION_EFFECT2 ,GL_LINEAR, GL_CLAMP);
	LoadBitmap( "Effect\\smokelines01.jpg" ,BITMAP_SMOKELINE1, GL_LINEAR, GL_REPEAT );
	LoadBitmap( "Effect\\smokelines02.jpg" ,BITMAP_SMOKELINE2, GL_LINEAR, GL_REPEAT );
	LoadBitmap( "Effect\\smokelines03.jpg" ,BITMAP_SMOKELINE3, GL_LINEAR, GL_REPEAT );
	LoadBitmap( "Effect\\lighting_mega01.jpg" ,BITMAP_LIGHTNING_MEGA1, GL_LINEAR, GL_REPEAT );
	LoadBitmap( "Effect\\lighting_mega02.jpg" ,BITMAP_LIGHTNING_MEGA2, GL_LINEAR, GL_REPEAT );
	LoadBitmap( "Effect\\lighting_mega03.jpg" ,BITMAP_LIGHTNING_MEGA3, GL_LINEAR, GL_REPEAT );
	LoadBitmap("Effect\\firehik01.jpg"  ,BITMAP_FIRE_HIK1 ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\firehik03.jpg"  ,BITMAP_FIRE_HIK3 ,GL_LINEAR,GL_CLAMP);
#ifdef CSK_ADD_MAP_ICECITY
	LoadBitmap("Effect\\firehik_mono01.jpg", BITMAP_FIRE_HIK1_MONO, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\firehik_mono02.jpg", BITMAP_FIRE_HIK2_MONO, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\firehik_mono03.jpg", BITMAP_FIRE_HIK3_MONO, GL_LINEAR, GL_CLAMP);
#endif // CSK_ADD_MAP_ICECITY
#ifdef LDS_RAKLION_ADDMONSTER_ICEWALKER
	LoadBitmap("Effect\\clouds3.jpg", BITMAP_RAKLION_CLOUDS, GL_LINEAR, GL_CLAMP);	// ��Ŭ���� ���̽���Ŀ ���� ����Ʈ �ؽ���
#endif // LDS_RAKLION_ADDMONSTER_ICEWALKER
#ifdef ADD_RAKLION_IRON_KNIGHT
	// ��Ŭ���� ���� ���̿� ����Ʈ
	LoadBitmap("Monster\\icenightlight.jpg", BITMAP_IRONKNIGHT_BODY_BRIGHT, GL_LINEAR, GL_CLAMP);
#endif	// ADD_RAKLION_IRON_KNIGHT

	g_XmasEvent->LoadXmasEventEffect();

	LoadBitmap("Skill\\younghtest1.tga", BITMAP_GM_HAIR_1);
	LoadBitmap("Skill\\younghtest3.tga", BITMAP_GM_HAIR_3);
	LoadBitmap("Skill\\gmmzine.jpg", BITMAP_GM_AURORA, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\explotion01mono.jpg"  ,BITMAP_EXPLOTION_MONO  ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\Success_kantru.tga" ,BITMAP_KANTURU_SUCCESS ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\Failure_kantru.tga" ,BITMAP_KANTURU_FAILED  ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Interface\\MonsterCount.tga"   ,BITMAP_KANTURU_COUNTER ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Clud64.jpg",	BITMAP_CLUD64,	GL_LINEAR,	GL_CLAMP);
	LoadBitmap("Effect\\clouds.jpg"	  ,BITMAP_CLOUD,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Skill\\SwordEff.jpg"	    ,BITMAP_BLUE_BLUR     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Impack03.jpg"   ,BITMAP_IMPACT      ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\ScolTail.jpg"  ,BITMAP_SCOLPION_TAIL  ,GL_LINEAR);
	LoadBitmap( "Effect\\FireSnuff.jpg"       , BITMAP_FIRE_SNUFF,    GL_LINEAR, GL_CLAMP );      //  �Ҿ�.
	LoadBitmap("Effect\\coll.jpg"	,BITMAP_SPOT_WATER,GL_LINEAR, GL_CLAMP );
	LoadBitmap("Effect\\BowE.jpg"	,BITMAP_DS_EFFECT,GL_LINEAR, GL_CLAMP );
	LoadBitmap("Effect\\Shockwave.jpg"	,BITMAP_DS_SHOCK,GL_LINEAR, GL_CLAMP );
	LoadBitmap("Effect\\DinoE.jpg"  ,BITMAP_EXPLOTION+1,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Shiny01.jpg"      ,BITMAP_SHINY     ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Shiny02.jpg"     	,BITMAP_SHINY+1   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Shiny03.jpg"     	,BITMAP_SHINY+2   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\eye01.jpg"     	,BITMAP_SHINY+3   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\ring.jpg"     	,BITMAP_SHINY+4   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Shiny04.jpg", BITMAP_SHINY+5, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\Chrome01.jpg"     ,BITMAP_CHROME     ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Effect\\blur01.jpg"       ,BITMAP_BLUR      ,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\bab2.jpg"          ,BITMAP_CHROME+1  ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Effect\\motion_blur.jpg"  ,BITMAP_BLUR+1     ,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\motion_blur_r.jpg",BITMAP_BLUR+2     ,GL_NEAREST,GL_CLAMP);
#ifdef PBG_ADD_PKFIELD
	LoadBitmap("Effect\\motion_mono.jpg",	BITMAP_BLUR+3, GL_NEAREST,GL_CLAMP);
#endif //PBG_ADD_PKFIELD
#ifdef LDS_ADD_EMPIRE_GUARDIAN
	LoadBitmap("Effect\\motion_blur_r3.jpg",BITMAP_BLUR+6   ,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\gra.jpg",BITMAP_BLUR+7				,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\spinmark01.jpg",BITMAP_BLUR+8		,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\flamestani.jpg", BITMAP_BLUR+9		,GL_LINEAR, GL_CLAMP);	// ����Ʈ ����2�� �˱� ���
	LoadBitmap("Effect\\sword_blur.jpg", BITMAP_BLUR+10		,GL_LINEAR, GL_CLAMP);	// ���̿� ����Ʈ ���� �˱� ���
	LoadBitmap("Effect\\joint_sword_red.jpg", BITMAP_BLUR+11,GL_LINEAR, GL_CLAMP);	// ���̿� ���� �˱� ���
	LoadBitmap("Effect\\motion_blur_r2.jpg", BITMAP_BLUR+12,GL_LINEAR, GL_CLAMP);	// ���̿� ���� �˱� ��� 2
	LoadBitmap("Effect\\motion_blur_r3.jpg", BITMAP_BLUR+13,GL_LINEAR, GL_CLAMP);	// ���̿� ���� �˱� ��� 2
#endif //LDS_ADD_EMPIRE_GUARDIAN
	LoadBitmap("Effect\\blur02.jpg"       ,BITMAP_BLUR2      ,GL_NEAREST,GL_CLAMP); //	2004/12/13 : �ܻ�ȿ�� �߰� �ؽ�ó
	LoadBitmap("Effect\\lightning2.jpg"	,BITMAP_LIGHTNING+1,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Thunder01.jpg"     ,BITMAP_ENERGY        ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Effect\\Spark01.jpg"	     ,BITMAP_JOINT_SPARK   ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\JointThunder01.jpg",BITMAP_JOINT_THUNDER ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Effect\\JointSpirit01.jpg" ,BITMAP_JOINT_SPIRIT  ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\JointLaser01.jpg"  ,BITMAP_JOINT_ENERGY  ,GL_LINEAR);
	LoadBitmap("Effect\\JointEnergy01.jpg" ,BITMAP_JOINT_HEALING ,GL_LINEAR);
	LoadBitmap("Effect\\JointLaser02.jpg"  ,BITMAP_JOINT_LASER+1 ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Monster\\iui03.jpg"  ,BITMAP_JANUSEXT ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Monster\\magic_H.tga"  ,BITMAP_PHO_R_HAIR ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Item\\t_lower_14m.tga"  ,BITMAP_PANTS_G_SOUL ,GL_LINEAR,GL_REPEAT);
	LoadBitmap("Skill\\Skull.jpg"  ,BITMAP_SKULL,GL_NEAREST);
	LoadBitmap("Effect\\motion_blur_r2.jpg"  ,BITMAP_JOINT_FORCE ,GL_LINEAR,GL_REPEAT);
    LoadBitmap("Effect\\Fire04.jpg"   ,BITMAP_FIRECRACKER,	GL_LINEAR);
    //  2002/12/04 - ������ ȿ��.
	LoadBitmap("Effect\\Flare.jpg"     	,BITMAP_FLARE,  GL_LINEAR,GL_CLAMP);

	LoadBitmap("Effect\\Chrome02.jpg"     ,BITMAP_CHROME2,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\Chrome03.jpg"     ,BITMAP_CHROME3,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\Chrome06.jpg"     ,BITMAP_CHROME6,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\Chrome07.jpg"     ,BITMAP_CHROME7,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\energy01.jpg"     ,BITMAP_CHROME_ENERGY,GL_NEAREST,GL_CLAMP);
	LoadBitmap("Effect\\energy02.jpg"     ,BITMAP_CHROME_ENERGY2,GL_LINEAR,GL_CLAMP);


#ifdef DEVIAS_XMAS_EVENT
	LoadBitmap("Effect\\Chrome08.jpg"		,BITMAP_CHROME8, GL_NEAREST, GL_CLAMP);
#endif //DEVIAS_XMAS_EVENT

#ifdef PJH_NEW_CHROME
	LoadBitmap("Effect\\2.jpg"     ,BITMAP_CHROME9,GL_LINEAR,GL_REPEAT);
#endif //PJH_NEW_CHROME
#ifdef YDG_ADD_FIRECRACKER_ITEM
	LoadBitmap("Effect\\firecracker0001.jpg"	,BITMAP_FIRECRACKER0001, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0002.jpg"	,BITMAP_FIRECRACKER0002, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0003.jpg"	,BITMAP_FIRECRACKER0003, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0004.jpg"	,BITMAP_FIRECRACKER0004, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0005.jpg"	,BITMAP_FIRECRACKER0005, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0006.jpg"	,BITMAP_FIRECRACKER0006, GL_NEAREST, GL_CLAMP);
	LoadBitmap("Effect\\firecracker0007.jpg"	,BITMAP_FIRECRACKER0007, GL_NEAREST, GL_CLAMP);
#endif	// YDG_ADD_FIRECRACKER_ITEM
#ifdef LDS_ADD_EMPIRE_GUARDIAN
#ifdef LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
	LoadBitmap("Effect\\Shiny05.jpg"     	,BITMAP_SHINY+6   ,GL_LINEAR,GL_CLAMP);
#else // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
	LoadBitmap("Effect\\Shiny05.jpg"     	,BITMAP_SHINY+5   ,GL_LINEAR,GL_CLAMP);
#endif // LDS_FIX_ACCESS_INDEXNUMBER_ALREADY_LOADTEXTURE
#endif // LDS_ADD_EMPIRE_GUARDIAN

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	LoadBitmap("Effect\\bujuckline.jpg", BITMAP_LUCKY_SEAL_EFFECT, GL_LINEAR, GL_CLAMP);
#endif // CSK_LUCKY_SEAL
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	LoadBitmap("Effect\\partCharge1\\bujuckline.jpg", BITMAP_LUCKY_SEAL_EFFECT, GL_LINEAR, GL_CLAMP);
#endif // CSK_LUCKY_SEAL
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN

	LoadBitmap("Item\\nfm03.jpg"			,BITMAP_BLUECHROME,GL_NEAREST,GL_REPEAT);		// ���� ���� ��Ȯ��
	LoadBitmap("Effect\\flareBlue.jpg"     	,BITMAP_FLARE_BLUE,  GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\NSkill.jpg"     	,BITMAP_FLARE_FORCE,  GL_LINEAR,GL_CLAMP);
    LoadBitmap("Effect\\Flare02.jpg"      ,BITMAP_FLARE+1, GL_LINEAR,GL_REPEAT);  //  �� ȿ��.
	LoadBitmap("Monster\\King11.jpg", BITMAP_WHITE_WIZARD, GL_LINEAR, GL_CLAMP);	// �鸶���� ��	// ���ֹ�����
	LoadBitmap("Monster\\Kni000.jpg", BITMAP_DEST_ORC_WAR0, GL_LINEAR, GL_CLAMP);	// �ı��� ��ũ ����0
	LoadBitmap("Monster\\Kni011.jpg", BITMAP_DEST_ORC_WAR1, GL_LINEAR, GL_CLAMP);	// �ı��� ��ũ ����1
	LoadBitmap("Monster\\Kni022.jpg", BITMAP_DEST_ORC_WAR2, GL_LINEAR, GL_CLAMP);	// �ı��� ��ũ ����2
	LoadBitmap( "Skill\\pinkWave.jpg"     	, BITMAP_PINK_WAVE,     GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\flareRed.jpg"     	, BITMAP_FLARE_RED,     GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\Fire05.jpg"		    , BITMAP_FIRE+3,        GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\Hole.jpg"           , BITMAP_HOLE,          GL_LINEAR, GL_REPEAT );	    //  Ȧ. ( �������� ���� ).
//	LoadBitmap( "Monster\\mop011.jpg"        , BITMAP_OTHER_SKIN,    GL_LINEAR, GL_REPEAT );     //  Į���� ���� ��� ���� ��Ų.
	LoadBitmap( "Effect\\WATERFALL1.jpg"		, BITMAP_WATERFALL_1,   GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\WATERFALL2.jpg"		, BITMAP_WATERFALL_2,   GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\WATERFALL3.jpg"	    , BITMAP_WATERFALL_3,   GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\WATERFALL4.jpg"	    , BITMAP_WATERFALL_4,   GL_LINEAR, GL_CLAMP );
	LoadBitmap( "Effect\\WATERFALL5.jpg"		, BITMAP_WATERFALL_5,   GL_LINEAR, GL_CLAMP );
	/*
	LoadBitmap("Interface\\in_bar.tga"		, BITMAP_MVP_INTERFACE, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_bar2.jpg"		, BITMAP_MVP_INTERFACE + 1, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_deco.tga"		, BITMAP_MVP_INTERFACE + 2, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main.tga"		, BITMAP_MVP_INTERFACE + 3, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_icon_bal1.tga"		, BITMAP_MVP_INTERFACE + 4, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_icon_dl1.tga"		, BITMAP_MVP_INTERFACE + 5, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_icon_dl2.tga"		, BITMAP_MVP_INTERFACE + 6, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_number1.tga"		, BITMAP_MVP_INTERFACE + 7, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_number2.tga"		, BITMAP_MVP_INTERFACE + 8, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main2.tga"		, BITMAP_MVP_INTERFACE + 9, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_failure.tga"		, BITMAP_MVP_INTERFACE + 10, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_success.tga"		, BITMAP_MVP_INTERFACE + 11, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\t_main.tga"		, BITMAP_MVP_INTERFACE + 12, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_no1.tga"		, BITMAP_MVP_INTERFACE + 13, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_no2.tga"		, BITMAP_MVP_INTERFACE + 14, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_no3.tga"		, BITMAP_MVP_INTERFACE + 15, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_ok1.tga"		, BITMAP_MVP_INTERFACE + 16, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_ok2.tga"		, BITMAP_MVP_INTERFACE + 17, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_ok3.tga"		, BITMAP_MVP_INTERFACE + 18, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_yes1.tga"		, BITMAP_MVP_INTERFACE + 19, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_yes2.tga"		, BITMAP_MVP_INTERFACE + 20, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_b_yes3.tga"		, BITMAP_MVP_INTERFACE + 21, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_main.tga"		, BITMAP_MVP_INTERFACE + 22, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_number1_1.tga"		, BITMAP_MVP_INTERFACE + 23, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_number2_1.tga"		, BITMAP_MVP_INTERFACE + 24, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\in_main_number0_2.tga"		, BITMAP_MVP_INTERFACE + 25, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_table.tga"		, BITMAP_MVP_INTERFACE + 26, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_rank.tga"		, BITMAP_MVP_INTERFACE + 27, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_D.tga"		, BITMAP_MVP_INTERFACE + 28, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_C.tga"		, BITMAP_MVP_INTERFACE + 29, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_B.tga"		, BITMAP_MVP_INTERFACE + 30, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_A.tga"		, BITMAP_MVP_INTERFACE + 31, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_S.tga"		, BITMAP_MVP_INTERFACE + 32, GL_LINEAR, GL_CLAMP);
	//icon_Rank_0
	LoadBitmap("Interface\\icon_Rank_0.tga"		, BITMAP_MVP_INTERFACE + 33, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_1.tga"		, BITMAP_MVP_INTERFACE + 34, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_2.tga"		, BITMAP_MVP_INTERFACE + 35, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_3.tga"		, BITMAP_MVP_INTERFACE + 36, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_4.tga"		, BITMAP_MVP_INTERFACE + 37, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_5.tga"		, BITMAP_MVP_INTERFACE + 38, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_6.tga"		, BITMAP_MVP_INTERFACE + 39, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_7.tga"		, BITMAP_MVP_INTERFACE + 40, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_8.tga"		, BITMAP_MVP_INTERFACE + 41, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_9.tga"		, BITMAP_MVP_INTERFACE + 42, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\icon_Rank_exp.tga"		, BITMAP_MVP_INTERFACE + 43, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Interface\\m_main_rank.tga"		, BITMAP_MVP_INTERFACE + 44, GL_LINEAR, GL_CLAMP);
	*/
	//m_main_rank
	//icon_Rank_exp
	LoadBitmap( "Interface\\BattleSkill.tga"	, BITMAP_INTERFACE_EX+34 );             //  ��Ʋ ������ ��ų �������̽�.
	LoadBitmap( "Effect\\Flashing.jpg"        , BITMAP_FLASH, GL_LINEAR, GL_CLAMP );  //  ����ȿ��.
	LoadBitmap( "Interface\\senatusmap.jpg"	, BITMAP_INTERFACE_EX+35 );             // ������ ��ü�̴��̹���
	LoadBitmap( "Interface\\gate_button2.jpg"	, BITMAP_INTERFACE_EX+36 );             // ������ư(����)
	LoadBitmap( "Interface\\gate_button1.jpg"	, BITMAP_INTERFACE_EX+37 );             // ������ư(����)
	LoadBitmap( "Interface\\suho_button2.jpg"	, BITMAP_INTERFACE_EX+38 );             // �����ư(����)
	LoadBitmap( "Interface\\suho_button1.jpg"	, BITMAP_INTERFACE_EX+39 );             // �����ư(����)
	LoadBitmap( "Interface\\DoorCL.jpg"	    , BITMAP_INTERFACE_EX+40 );             //  ���� ��ħ.
	LoadBitmap( "Interface\\DoorOP.jpg"	    , BITMAP_INTERFACE_EX+41 );             //  ���� ����.
    //OpenJpeg( "Effect\\FireSnuff.jpg"       , BITMAP_FIRE_SNUFF,    GL_LINEAR, GL_CLAMP );      //  �Ҿ�.
	LoadBitmap( "Object31\\Flag.tga"          , BITMAP_INTERFACE_MAP+0, GL_LINEAR, GL_CLAMP );    //  �� ���.
	LoadBitmap( "Interface\\CursorAttack2.tga", BITMAP_CURSOR2 );                                 //  ������������ ���� ǥ��.
	LoadBitmap( "Effect\\Cratered.tga"	    , BITMAP_CRATER );                      //  ���� ����.
	LoadBitmap( "Effect\\FormationMark.tga"	, BITMAP_FORMATION_MARK );              //  ���� ��ũ.
    LoadBitmap( "Effect\\Plus.tga"	        , BITMAP_PLUS );                        //  
	//^ �渱 ����Ʈ ����(�ؽ���)
	LoadBitmap("Effect\\eff_lighting.jpg" , BITMAP_FENRIR_THUNDER);
	LoadBitmap("Effect\\eff_lightinga01.jpg" , BITMAP_FENRIR_FOOT_THUNDER1);
	LoadBitmap("Effect\\eff_lightinga02.jpg" , BITMAP_FENRIR_FOOT_THUNDER2);
	LoadBitmap("Effect\\eff_lightinga03.jpg" , BITMAP_FENRIR_FOOT_THUNDER3);
	LoadBitmap("Effect\\eff_lightinga04.jpg" , BITMAP_FENRIR_FOOT_THUNDER4);
	LoadBitmap("Effect\\eff_lightinga05.jpg" , BITMAP_FENRIR_FOOT_THUNDER5);
	LoadBitmap( "Interface\\Progress_Back.jpg",BITMAP_INTERFACE_EX+42 );				// �˾�â�� ���α׷����� ���
	LoadBitmap( "Interface\\Progress.jpg"     ,BITMAP_INTERFACE_EX+43 );				// �˾�â�� ���α׷�����
	LoadBitmap( "Effect\\Inferno.jpg"         , BITMAP_INFERNO,       GL_LINEAR, GL_CLAMP );      //  ȭ��.
	LoadBitmap( "Effect\\Lava.jpg"            , BITMAP_LAVA,          GL_LINEAR, GL_CLAMP );      //  ���.
	LoadBitmap( "Interface\\frame.tga",       BITMAP_INTERFACE_MAP+3 );   //  ������ ���� Ʋ.
	LoadBitmap( "Interface\\i_attack.tga",    BITMAP_INTERFACE_MAP+4 );   //  ���� ������.
	LoadBitmap( "Interface\\i_defense.tga",   BITMAP_INTERFACE_MAP+5 );   //  ��� ������.
	LoadBitmap( "Interface\\i_wait.tga",      BITMAP_INTERFACE_MAP+6 );   //  ��� ������.
	LoadBitmap( "Interface\\b_command01.jpg", BITMAP_INTERFACE_MAP+8 );   //  ���â ��.
	LoadBitmap( "Interface\\b_command02.jpg", BITMAP_INTERFACE_MAP+9 );   //  ���â ����.
	LoadBitmap( "Interface\\b_group02.jpg",   BITMAP_INTERFACE_MAP+10);   //  �׷�â ��.
	LoadBitmap( "Interface\\b_zoomout01.jpg", BITMAP_INTERFACE_MAP+11);   //  ���.
	LoadBitmap( "Interface\\hourglass.tga",   BITMAP_INTERFACE_MAP+7 );   //  �ð�â.
	LoadBitmap( "Interface\\dot.tga",         BITMAP_INTERFACE_EX+44 );   //  ��
	LoadBitmap("Object9\\Impack03.jpg"   ,BITMAP_LIGHT+1      ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Monster\\buserbody_r.jpg", BITMAP_BERSERK_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\busersword_r.jpg", BITMAP_BERSERK_WP_EFFECT, GL_LINEAR, GL_CLAMP);
//	LoadBitmap("Monster\\gigantiscorn_R.jpg", BITMAP_GIGANTIS_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\bladeeff2_r.jpg", BITMAP_BLADEHUNTER_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\illumi_R.jpg", BITMAP_TWINTAIL_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\prsona_R.jpg", BITMAP_PRSONA_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\prsonass_R.jpg", BITMAP_PRSONA_EFFECT2, GL_LINEAR, GL_CLAMP);
	LoadBitmap("effect\\water.jpg", BITMAP_TWINTAIL_WATER, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Effect\\cra_04.jpg"   ,BITMAP_LIGHT+2      ,GL_LINEAR,GL_CLAMP);
	LoadBitmap("Effect\\Impack01.jpg"		,BITMAP_LIGHT+3,	GL_LINEAR,GL_CLAMP);	//$ ũ���̿��� ���˻�� ȿ��
	::LoadBitmap("Interface\\message_ok_b_all.tga", BITMAP_BUTTON);		// OK ��ư.
	::LoadBitmap("Interface\\loding_cancel_b_all.tga", BITMAP_BUTTON+1);   // Cancel ��ư.
	::LoadBitmap("Interface\\message_close_b_all.tga", BITMAP_BUTTON+2);   // Close ��ư.
	::LoadBitmap("Interface\\message_back.tga", BITMAP_MESSAGE_WIN);		// �޽��� â.
	::LoadBitmap("Interface\\delete_secret_number.tga", BITMAP_MSG_WIN_INPUT);// �Է� �׵θ�.
	::LoadBitmap("Interface\\op1_stone.jpg", BITMAP_SYS_WIN, GL_NEAREST, GL_REPEAT);// �ý��۸޴�â �߾�.
	::LoadBitmap("Interface\\op1_back1.tga", BITMAP_SYS_WIN+1);			// �ý��۸޴�â ��.
	::LoadBitmap("Interface\\op1_back2.tga", BITMAP_SYS_WIN+2);			// �ý��۸޴�â ��.
	::LoadBitmap("Interface\\op1_back3.jpg", BITMAP_SYS_WIN+3, GL_NEAREST, GL_REPEAT);// �ý��۸޴�â ��.
	::LoadBitmap("Interface\\op1_back4.jpg", BITMAP_SYS_WIN+4, GL_NEAREST, GL_REPEAT);// �ý��۸޴�â ��.
	::LoadBitmap("Interface\\op1_b_all.tga", BITMAP_TEXT_BTN);				// �ؽ�Ʈ ��ư.
	::LoadBitmap("Interface\\op2_back1.tga", BITMAP_OPTION_WIN);			// �ɼ�â.
	::LoadBitmap("Interface\\op2_ch.tga", BITMAP_CHECK_BTN);				// üũ ��ư.
	::LoadBitmap("Interface\\op2_volume3.tga", BITMAP_SLIDER);				// �����̴� ��.
	::LoadBitmap("Interface\\op2_volume2.jpg", BITMAP_SLIDER+1, GL_NEAREST, GL_REPEAT);// �����̴� ������.
	::LoadBitmap("Interface\\op2_volume1.tga", BITMAP_SLIDER+2);			// �����̴� ���.
	::LoadBitmap("Effect\\clouds2.jpg", BITMAP_EVENT_CLOUD, GL_LINEAR, GL_CLAMP);			// ��ȯ���� ���⿡ ����.
	LoadBitmap("Effect\\pin_lights.jpg", BITMAP_PIN_LIGHT, GL_LINEAR, GL_CLAMP);
#ifdef LDK_ADD_EG_MONSTER_DEASULER
	LoadBitmap("Monster\\deasuler_cloth.tga", BITMAP_DEASULER_CLOTH, GL_LINEAR, GL_CLAMP);
#endif //LDK_ADD_EG_MONSTER_DEASULER

#ifdef ADD_SOCKET_ITEM
	LoadBitmap("Item\\soketmagic_stape02.jpg", BITMAP_SOCKETSTAFF, GL_LINEAR, GL_CLAMP);	// �κ����˽����� ����Ʈ �ؽ���
	LoadBitmap("Effect\\lightmarks.jpg", BITMAP_LIGHTMARKS, GL_LINEAR, GL_CLAMP);			// ��ٽ�Ÿ��, �극�̺�ҵ� ����Ʈ �ؽ���
#endif // ADD_SOCKET_ITEM
#ifdef LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE
	LoadBitmap("Effect\\lightmarks.jpg", BITMAP_LIGHTMARKS_FOREIGN, GL_LINEAR, GL_CLAMP);			// ��ȣ ���� ����Ʈ �ؽ���
#endif //LDK_ADD_PC4_GUARDIAN_EFFECT_IMAGE

	// Ÿ��Ŭ ȭ�鿡�� �ε� �������� 1/10��ŭ ǥ��.
	rUIMng.RenderTitleSceneUI(hDC, 1, 11);

#ifdef CSK_FREE_TICKET
	// ��������� ������ ����Ʈ ȿ�� �� �ؽ��� �ε�
	::LoadBitmap("Item\\partCharge1\\entrance_R.jpg", BITMAP_FREETICKET_R, GL_LINEAR, GL_CLAMP);
#endif // CSK_FREE_TICKET
#ifdef CSK_CHAOS_CARD
	// ī����ī�� ������ ����Ʈ ȿ�� �� �ؽ��� �ε�
	::LoadBitmap("Item\\partCharge1\\juju_R.jpg", BITMAP_CHAOSCARD_R, GL_LINEAR, GL_CLAMP);
#endif // CSK_CHAOS_CARD

#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	::LoadBitmap("Item\\monmark01a.jpg", BITMAP_LUCKY_SEAL_EFFECT43, GL_LINEAR, GL_CLAMP);// ����� ���� (����� ����)
	::LoadBitmap("Item\\monmark02a.jpg", BITMAP_LUCKY_SEAL_EFFECT44, GL_LINEAR, GL_CLAMP);// ����� ���� (ǳ���� ����)
	::LoadBitmap("Item\\monmark03a.jpg", BITMAP_LUCKY_SEAL_EFFECT45, GL_LINEAR, GL_CLAMP);// ����� ���� (������ ����)
#endif //CSK_LUCKY_SEAL
#else //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#ifdef CSK_LUCKY_SEAL
	::LoadBitmap("Item\\partCharge1\\monmark01a.jpg", BITMAP_LUCKY_SEAL_EFFECT43, GL_LINEAR, GL_CLAMP);// ����� ���� (����� ����)
	::LoadBitmap("Item\\partCharge1\\monmark02a.jpg", BITMAP_LUCKY_SEAL_EFFECT44, GL_LINEAR, GL_CLAMP);// ����� ���� (ǳ���� ����)
	::LoadBitmap("Item\\partCharge1\\monmark03a.jpg", BITMAP_LUCKY_SEAL_EFFECT45, GL_LINEAR, GL_CLAMP);// ����� ���� (������ ����)
#endif //CSK_LUCKY_SEAL
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN

#ifdef CSK_LUCKY_CHARM
	::LoadBitmap("Item\\partCharge1\\bujuck01alpa.jpg", BITMAP_LUCKY_CHARM_EFFECT53, GL_LINEAR, GL_CLAMP);// ����� ����
#endif //CSK_LUCKY_CHARM
#ifdef CSK_RARE_ITEM
	// ��;����� ����Ʈ ȿ�� �� �ؽ��� �ε�
	::LoadBitmap("Item\\partCharge1\\expensiveitem01_R.jpg", BITMAP_RAREITEM1_R, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Item\\partCharge1\\expensiveitem02a_R.jpg", BITMAP_RAREITEM2_R, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Item\\partCharge1\\expensiveitem02b_R.jpg", BITMAP_RAREITEM3_R, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Item\\partCharge1\\expensiveitem03a_R.jpg", BITMAP_RAREITEM4_R, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Item\\partCharge1\\expensiveitem03b_R.jpg", BITMAP_RAREITEM5_R, GL_LINEAR, GL_CLAMP);
#endif // CSK_RARE_ITEM
#if defined PSW_CHARACTER_CARD || defined PBG_ADD_CHARACTERCARD
	::LoadBitmap("Item\\partCharge3\\alicecard_R.tga", BITMAP_CHARACTERCARD_R, GL_LINEAR, GL_CLAMP);	// ĳ���� ī��(��ȯ����)
#endif // defined PSW_CHARACTER_CARD || defined PBG_ADD_CHARACTERCARD
#ifdef PBG_ADD_CHARACTERCARD
	::LoadBitmap("Item\\Ingameshop\\kacama_R.jpg", BITMAP_CHARACTERCARD_R_MA, GL_LINEAR, GL_CLAMP);	// ĳ���� ī��(���˻�)
	::LoadBitmap("Item\\Ingameshop\\kacada_R.jpg", BITMAP_CHARACTERCARD_R_DA, GL_LINEAR, GL_CLAMP);	// ĳ���� ī��(��ũ�ε�)
#endif //PBG_ADD_CHARACTERCARD
#ifdef PSW_NEW_CHAOS_CARD
	::LoadBitmap("Item\\partCharge3\\jujug_R.jpg", BITMAP_NEWCHAOSCARD_GOLD_R, GL_LINEAR, GL_CLAMP);	// ī����ī�� ���
	::LoadBitmap("Item\\partCharge3\\jujul_R.jpg", BITMAP_NEWCHAOSCARD_RARE_R, GL_LINEAR, GL_CLAMP);	// ī����ī�� ����
	::LoadBitmap("Item\\partCharge3\\jujum_R.jpg", BITMAP_NEWCHAOSCARD_MINI_R, GL_LINEAR, GL_CLAMP);	// ī����ī�� �̴�
#endif // PSW_NEW_CHAOS_CARD       
#ifdef CSK_EVENT_CHERRYBLOSSOM
	// ������ 
	::LoadBitmap("Effect\\cherryblossom\\sakuras01.jpg", BITMAP_CHERRYBLOSSOM_EVENT_PETAL, GL_LINEAR, GL_CLAMP);
	// ����
	::LoadBitmap("Effect\\cherryblossom\\sakuras02.jpg", BITMAP_CHERRYBLOSSOM_EVENT_FLOWER, GL_LINEAR, GL_CLAMP);
#endif // CSK_EVENT_CHERRYBLOSSOM
	::LoadBitmap("Object39\\k_effect_01.JPG", BITMAP_KANTURU_2ND_EFFECT1, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Item\\deathbeamstone_R.jpg", BITMAP_ITEM_EFFECT_DBSTONE_R, GL_LINEAR, GL_CLAMP);	// ������ ����Ʈ �Ҳ� ������ ����Ʈ.
	::LoadBitmap("Item\\hellhorn_R.jpg", BITMAP_ITEM_EFFECT_HELLHORN_R, GL_LINEAR, GL_CLAMP);	// �� ���̳� �� ������ ����Ʈ.
	::LoadBitmap("Item\\phoenixfeather_R.tga", BITMAP_ITEM_EFFECT_PFEATHER_R, GL_LINEAR, GL_CLAMP);	// ����� �һ��� ���� ������ ����Ʈ.
	::LoadBitmap("Item\\Deye_R.jpg", BITMAP_ITEM_EFFECT_DEYE_R, GL_LINEAR, GL_CLAMP);	// �ɿ��Ǵ����� ������ ����Ʈ.
	::LoadBitmap("Item\\wing3chaking2.jpg", BITMAP_ITEM_NIGHT_3RDWING_R, GL_LINEAR, GL_CLAMP);	// ���� 3������ ����Ʈ

	LoadBitmap("NPC\\lumi.jpg", BITMAP_CURSEDTEMPLE_NPC_MESH_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("item\\songko2_R.jpg", BITMAP_CURSEDTEMPLE_HOLYITEM_MESH_EFFECT, GL_LINEAR, GL_CLAMP);
	LoadBitmap("skill\\unitedsoldier_wing.tga", BITMAP_CURSEDTEMPLE_ALLIED_PHYSICSCLOTH);
	LoadBitmap("skill\\illusionistcloth.tga", BITMAP_CURSEDTEMPLE_ILLUSION_PHYSICSCLOTH);
	LoadBitmap("effect\\masker.jpg", BITMAP_CURSEDTEMPLE_EFFECT_MASKER, GL_LINEAR, GL_CLAMP);
	LoadBitmap("effect\\wind01.jpg",BITMAP_CURSEDTEMPLE_EFFECT_WIND, GL_LINEAR, GL_CLAMP );
	::LoadBitmap("Interface\\menu01_new2_SD.jpg" ,BITMAP_INTERFACE_EX+46);

#ifdef ASG_ADD_GENS_SYSTEM
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	string strFileName = "Local\\" + g_strSelectedML + "\\ImgsMapName\\MapNameAddStrife.tga";
	::LoadBitmap(strFileName.c_str(), BITMAP_INTERFACE_EX+47);	// ���̸� ��ܿ� ������ ��������.
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	::LoadBitmap("Interface\\MapNameAddStrife.tga", BITMAP_INTERFACE_EX+47);	// ���̸� ��ܿ� ������ ��������.
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#endif	// ASG_ADD_GENS_SYSTEM

#ifdef ASG_ADD_GENS_MARK
#ifdef PBG_FIX_GENSREWARDNOTREG
	::LoadBitmap("Interface\\Gens_mark_D_new.tga", BITMAP_GENS_MARK_DUPRIAN);	// �׼� �������� ���� ���ϸ� ����
	::LoadBitmap("Interface\\Gens_mark_V_new.tga", BITMAP_GENS_MARK_BARNERT);
#else //PBG_FIX_GENSREWARDNOTREG
	::LoadBitmap("Interface\\Gens_mark_D.tga", BITMAP_GENS_MARK_DUPRIAN);	// �ս� �������� ��ũ.
	::LoadBitmap("Interface\\Gens_mark_V.tga", BITMAP_GENS_MARK_BARNERT);	// �ս� �ٳ׸�Ʈ ��ũ.
#endif //PBG_FIX_GENSREWARDNOTREG
#endif	// ASG_ADD_GENS_MARK

#ifdef CSK_ADD_MAP_ICECITY

#ifdef LDS_FIX_GLPARAM_SWAPMODE_BITMAP
	LoadBitmap("Monster\\serufanarm_R.jpg", BITMAP_SERUFAN_ARM_R, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Monster\\serufanwand_R.jpg", BITMAP_SERUFAN_WAND_R, GL_LINEAR, GL_CLAMP);
#else // LDS_FIX_GLPARAM_SWAPMODE_BITMAP
	LoadBitmap("Monster\\serufanarm_R.jpg", BITMAP_SERUFAN_ARM_R, GL_LINEAR, GL_LINEAR);
	LoadBitmap("Monster\\serufanwand_R.jpg", BITMAP_SERUFAN_WAND_R, GL_LINEAR, GL_LINEAR);
#endif // LDS_FIX_GLPARAM_SWAPMODE_BITMAP

#endif // CSK_ADD_MAP_ICECITY

#ifdef YDG_ADD_SANTA_MONSTER
	#ifdef LDS_FIX_GLPARAM_SWAPMODE_BITMAP
	LoadBitmap("npc\\santa.jpg", BITMAP_GOOD_SANTA, GL_LINEAR, GL_CLAMP);
	LoadBitmap("npc\\santa_baggage.jpg", BITMAP_GOOD_SANTA_BAGGAGE, GL_LINEAR, GL_CLAMP);
	#else // LDS_FIX_GLPARAM_SWAPMODE_BITMAP
	LoadBitmap("npc\\santa.jpg", BITMAP_GOOD_SANTA, GL_LINEAR, GL_LINEAR);
	LoadBitmap("npc\\santa_baggage.jpg", BITMAP_GOOD_SANTA_BAGGAGE, GL_LINEAR, GL_LINEAR);
	#endif // LDS_FIX_GLPARAM_SWAPMODE_BITMAP
#endif	// YDG_ADD_SANTA_MONSTER

#ifdef PJH_ADD_PANDA_CHANGERING	
	#ifdef LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("Item\\pandabody_R.jpg", BITMAP_PANDABODY_R, GL_LINEAR, GL_CLAMP);
	#else // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("Item\\pandabody_R.jpg", BITMAP_PANDABODY_R, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
	#endif // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_DOPPELGANGER_MONSTER
	#ifdef LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("Monster\\DGicewalker_body.jpg", BITMAP_DOPPELGANGER_ICEWALKER0, GL_LINEAR, GL_CLAMP);	
		LoadBitmap("Monster\\DGicewalker_R.jpg", BITMAP_DOPPELGANGER_ICEWALKER1, GL_LINEAR, GL_CLAMP);	
		LoadBitmap("Monster\\Snake1.jpg", BITMAP_DOPPELGANGER_SNAKE01, GL_LINEAR, GL_CLAMP);	
	#else // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("Monster\\DGicewalker_body.jpg", BITMAP_DOPPELGANGER_ICEWALKER0, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
		LoadBitmap("Monster\\DGicewalker_R.jpg", BITMAP_DOPPELGANGER_ICEWALKER1, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
		LoadBitmap("Monster\\Snake1.jpg", BITMAP_DOPPELGANGER_SNAKE01, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
	#endif // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
#endif	// YDG_ADD_DOPPELGANGER_MONSTER

#ifdef YDG_ADD_DOPPELGANGER_NPC
	#ifdef LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("NPC\\goldboit.jpg", BITMAP_DOPPELGANGER_GOLDENBOX1, GL_LINEAR, GL_CLAMP);	// OPENGL_ERROR�߻�
		LoadBitmap("NPC\\goldline.jpg", BITMAP_DOPPELGANGER_GOLDENBOX2, GL_LINEAR, GL_CLAMP);	// OPENGL_ERROR�߻�
	#else // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
		LoadBitmap("NPC\\goldboit.jpg", BITMAP_DOPPELGANGER_GOLDENBOX1, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
		LoadBitmap("NPC\\goldline.jpg", BITMAP_DOPPELGANGER_GOLDENBOX2, GL_LINEAR, GL_LINEAR);	// OPENGL_ERROR�߻�
	#endif // LDS_FIX_GLERROR_WRONG_WRAPMODEPARAMETER
#endif	// YDG_ADD_DOPPELGANGER_NPC

#ifdef LDS_ADD_RESOURCE_FLARERED
	//BITMAP_LIGHT_RED
	LoadBitmap("effect\\flare01_red.jpg", BITMAP_LIGHT_RED, GL_LINEAR, GL_CLAMP );
#endif // LDS_ADD_RESOURCE_FLARERED

#ifdef KJH_ADD_09SUMMER_EVENT
	LoadBitmap("effect\\gra.jpg", BITMAP_GRA, GL_LINEAR, GL_CLAMP );
	LoadBitmap("effect\\ring_of_gradation.jpg", BITMAP_RING_OF_GRADATION, GL_LINEAR, GL_CLAMP );
#endif // KJH_ADD_09SUMMER_EVENT

#ifdef PBG_ADD_INGAMESHOPMSGBOX
	LoadBitmap("Interface\\InGameShop\\ingame_pack_check.tga", BITMAP_IGS_CHECK_BUTTON, GL_LINEAR);		//üũ��ư
#endif //PBG_ADD_INGAMESHOPMSGBOX
#ifdef LDK_ADD_EG_MONSTER_ASSASSINMASTER
	LoadBitmap("Monster\\AssassinLeader_body_R.jpg"	, BITMAP_ASSASSIN_EFFECT1, GL_LINEAR, GL_CLAMP);
#endif //LDK_ADD_EG_MONSTER_ASSASSINMASTER

#ifdef LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX
	LoadBitmap("Player\\lower2_15m.tga"  ,BITMAP_PANTS_B_SOUL_PHYSIQMESH ,GL_LINEAR, GL_REPEAT);	
#endif // LDS_MR0_MOD_PATIALPHYSIQMODEL_PHYSICPROCESS_FIX

#ifdef LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_7_body.jpg", BITMAP_RAREITEM7, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_8_body.jpg", BITMAP_RAREITEM8, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_9_body.jpg", BITMAP_RAREITEM9, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_10_body.jpg", BITMAP_RAREITEM10, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_11_body.jpg", BITMAP_RAREITEM11, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\rareitem_ticket_12_body.jpg", BITMAP_RAREITEM12, GL_LINEAR, GL_CLAMP);
#endif //LJH_ADD_RARE_ITEM_TICKET_FROM_7_TO_12
	
#ifdef LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	// ���ð���, �ٸ�ī, �ٸ�ī ��7�� ��������� ������ ����Ʈ ȿ�� �� �ؽ��� �ε�
	LoadBitmap("Item\\partCharge8\\DoppelCard.jpg", BITMAP_DOPPLEGANGGER_FREETICKET, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\BarcaCard.jpg", BITMAP_BARCA_FREETICKET, GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\partCharge8\\Barca7Card.jpg", BITMAP_BARCA7TH_FREETICKET, GL_LINEAR, GL_CLAMP);
#endif //LJH_ADD_FREE_TICKET_FOR_DOPPELGANGGER_BARCA_BARCA_7TH
	
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	// ��ũ��, ��������, ����ũ��, ���������� ���̾�ȿ��
	LoadBitmap("Item\\ork_cham_R.jpg",				BITMAP_ORK_CHAM_LAYER_R,			GL_LINEAR, GL_CLAMP);
	//LoadBitmap("Item\\maple_cham_R.jpg",			BITMAP_MAPLE_CHAM_LAYER_R,			GL_LINEAR, GL_CLAMP);
	LoadBitmap("Item\\goldenork_cham_R.jpg",		BITMAP_GOLDEN_ORK_CHAM_LAYER_R,		GL_LINEAR, GL_CLAMP);
	//LoadBitmap("Item\\goldenmaple_cham_R.jpg",	BITMAP_GOLDEN_MAPLE_CHAM_LAYER_R,	GL_LINEAR, GL_CLAMP);
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2

#ifdef ASG_ADD_KARUTAN_MONSTERS
	::LoadBitmap("Monster\\BoneSE.jpg", BITMAP_BONE_SCORPION_SKIN_EFFECT, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\KryptaBall2.jpg", BITMAP_KRYPTA_BALL_EFFECT, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\bora_golem_effect.jpg", BITMAP_CONDRA_SKIN_EFFECT, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\bora_golem2_effect.jpg", BITMAP_CONDRA_SKIN_EFFECT2, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\king_golem01_effect.jpg", BITMAP_NARCONDRA_SKIN_EFFECT, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\king_golem02_effect.jpg", BITMAP_NARCONDRA_SKIN_EFFECT2, GL_LINEAR, GL_CLAMP);
	::LoadBitmap("Monster\\king_golem03_effect.jpg", BITMAP_NARCONDRA_SKIN_EFFECT3, GL_LINEAR, GL_CLAMP);
#endif	// ASG_ADD_KARUTAN_MONSTERS

#ifdef ASG_ADD_KARUTAN_NPC
	::LoadBitmap("NPC\\voloE.jpg", BITMAP_VOLO_SKIN_EFFECT, GL_LINEAR, GL_CLAMP);
#endif	// ASG_ADD_KARUTAN_NPC

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_PRELOADS );
#endif // DO_PROFILING_FOR_LOADING

	OpenPlayers();

#ifdef KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING
	#if defined RESOURCE_GUARD && !defined FOR_WORK
		char szModuleFileName[256];
		ResourceGuard::CResourceGuard RG101;
		CMuRGReport MuRGReport;
		RG101.AddReportObj(&MuRGReport);
	#ifdef _TEST_SERVER
		sprintf(szModuleFileName, "data\\local\\Gameguardtest.csr");
	#else  // _TEST_SERVER
		sprintf(szModuleFileName, "data\\local\\Gameguard.csr");
	#endif // _TEST_SERVER
		if(!RG101.CheckIntegrityResourceChecksumFile(szModuleFileName))
		{
			g_ErrorReport.Write("> ResourceGuard Error!!\r\n");
			SendMessage(g_hWnd,WM_DESTROY,0,0);
		}
	#endif // defined RESOURCE_GUARD && !defined FOR_WORK
#endif // KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING
	// Ÿ��Ŭ ȭ�鿡�� �ε� �������� 2/10��ŭ ǥ��.
	rUIMng.RenderTitleSceneUI(hDC, 2, 11);

    OpenPlayerTextures();
	rUIMng.RenderTitleSceneUI(hDC, 3, 11);

    OpenItems();
	rUIMng.RenderTitleSceneUI(hDC, 4, 11);

    OpenItemTextures();
	rUIMng.RenderTitleSceneUI(hDC, 5, 11);

    OpenSkills();
	rUIMng.RenderTitleSceneUI(hDC, 6, 11);

	OpenImages();
	rUIMng.RenderTitleSceneUI(hDC, 7, 11);

    OpenSounds();
	rUIMng.RenderTitleSceneUI(hDC, 8, 11);

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_POSTLOADS, PROFILING_LOADING_POSTLOADS );
#endif // DO_PROFILING_FOR_LOADING

	char Text[100];

#ifdef ASG_ADD_SERVER_LIST_SCRIPTS
	g_ServerListManager->LoadServerListScript();
#endif	// ASG_ADD_SERVER_LIST_SCRIPTS


#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Dialog 
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_DIALOGTEST_BMD
	sprintf(Text, "Data\\Local\\%s\\Dialogtest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\Dialog_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif//USE_DIALOGTEST_BMD
	OpenDialogFile(Text);

////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Item
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_ITEMTEST_BMD
	sprintf(Text, "Data\\Local\\%s\\ItemTest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\Item_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif
	OpenItemScript(Text);

////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Movereq
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_MOVEREQTEST_BMD
	sprintf(Text, "Data\\Local\\%s\\movereqtest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\movereq_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif // USE_MOVEREQTEST_BMD
	SEASON3B::CMoveCommandData::OpenMoveReqScript(Text);
	
////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: NpcName
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _TEST_SERVER
	sprintf(Text, "Data\\Local\\%s\\NpcNameTest_%s.txt", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\NpcName_%s.txt", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif// _TEST_SERVER
   	OpenMonsterScript(Text);
	
////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Quest
////////////////////////////////////////////////////////////////////////////////////////////////
//  ����Ʈ ������ �д´�.
#ifdef USE_QUESTTEST_BMD
	sprintf(Text, "Data\\Local\\%s\\Questtest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\Quest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif//USE_QUESTTEST_BMD
	g_csQuest.OpenQuestScript (Text);

////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Skill
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef  USE_SKILLTEST_BMD
	sprintf(Text, "Data\\Local\\%s\\Skilltest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text, "Data\\Local\\%s\\Skill_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif
	OpenSkillScript(Text);

////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: SocketItem
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_SOCKETITEM_TEST_BMD
	sprintf(Text, "Data\\Local\\%s\\SocketItemTest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else	// USE_SOCKETITEM_TEST_BMD
	sprintf(Text, "Data\\Local\\%s\\SocketItem_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif	// USE_SOCKETITEM_TEST_BMD
	g_SocketItemMgr.OpenSocketItemScript(Text);

////////////////////////////////////////////////////////////////////////////////////////////////
// �ε�: Text
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	OpenTextData();		//. Text.bmd, Testtest.bmd�� �д´�.
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

///////////////////////////////////////////////////////////////////////////////////////////////
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#ifdef USE_DIALOGTEST_BMD
	OpenDialogFile("Data\\Local\\Dialogtest.bmd");
#else
	OpenDialogFile("Data\\Local\\Dialog.bmd");
#endif//USE_DIALOGTEST_BMD

#ifdef USE_ITEMTEST_BMD
    OpenItemScript ("Data\\Local\\ItemTest.bmd");
#else
    OpenItemScript ("Data\\Local\\Item.bmd");
#endif

#ifdef USE_MOVEREQTEST_BMD
	SEASON3B::CMoveCommandData::OpenMoveReqScript("Data\\Local\\movereqtest.bmd");
#else
	SEASON3B::CMoveCommandData::OpenMoveReqScript("Data\\Local\\movereq.bmd");
#endif // USE_MOVEREQTEST_BMD
	
#ifdef _TEST_SERVER
   	sprintf(Text,     "Data\\Local\\NpcNameTest(%s).txt",Language);
#else
   	sprintf(Text,     "Data\\Local\\NpcName(%s).txt",Language);
#endif// _TEST_SERVER
   	OpenMonsterScript(Text);

	//  ����Ʈ ������ �д´�.
#ifdef USE_QUESTTEST_BMD
    g_csQuest.OpenQuestScript ( "Data\\Local\\Questtest.bmd" );
#else
    g_csQuest.OpenQuestScript ( "Data\\Local\\Quest.bmd" );
#endif//USE_QUESTTEST_BMD

#ifdef  USE_SKILLTEST_BMD
	OpenSkillScript("Data\\Local\\Skilltest.bmd");
#else
	OpenSkillScript("Data\\Local\\Skill.bmd");
#endif

#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#ifdef USE_SET_ITEMTEST_BMD
	g_csItemOption.OpenItemSetScript ( true );
#else
	g_csItemOption.OpenItemSetScript ( false );
#endif// USE_SET_ITEMTEST_BMD

#ifdef ASG_ADD_NEW_QUEST_SYSTEM
	g_QuestMng.LoadQuestScript();
#endif	// ASG_ADD_NEW_QUEST_SYSTEM



#ifdef USE_GATETEST_BMD
	OpenGateScript ("Data\\GateTest.bmd");
#else
	OpenGateScript ("Data\\Gate.bmd");
#endif
	//OpenGateScript ("Data\\GateTest.bmd");

#ifdef USE_FILTER_TEST_BMD
	OpenFilterFile ("Data\\Local\\Filtertest.bmd");
#else //USE_FILTER_TEST_BMD
	OpenFilterFile ("Data\\Local\\Filter.bmd");
#endif //USE_FILTER_TEST_BMD

	OpenNameFilterFile ("Data\\Local\\FilterName.bmd");

//#ifdef ADD_MONSTER_SKILL
#ifdef USE_MONSTERSKILLTEST_BMD
	OpenMonsterSkillScript ("Data\\Local\\MonsterSkillTest.bmd");
#else
	OpenMonsterSkillScript ("Data\\Local\\MonsterSkill.bmd");
#endif
//#endif

#ifdef USE_MASTERTREE_BMD
	g_pMasterLevelInterface->OpenMasterLevel("Data\\Local\\MasterSKillTreetest.bmd");
#else
	g_pMasterLevelInterface->OpenMasterLevel("Data\\Local\\MasterSKillTree.bmd");
#endif  //USE_MASTERTREE_BMD

#ifdef KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING
	#if defined RESOURCE_GUARD && !defined FOR_WORK
		if(!RG101.CheckIntegrityResourceChecksumFile(szModuleFileName))
		{
			g_ErrorReport.Write("> ResourceGuard Error!!\r\n");
			SendMessage(g_hWnd,WM_DESTROY,0,0);
		}
	#endif // defined RESOURCE_GUARD && !defined FOR_WORK
#endif KJH_ADD_CHECK_RESOURCE_GUARD_BEFORE_LOADING

	rUIMng.RenderTitleSceneUI(hDC, 9, 11);

#ifdef KOREAN_WAV_USE
	LoadWaveFile(SOUND_TITLE01			,"Data\\Sound\\iŸ��Ʋ.wav",1); 
	LoadWaveFile(SOUND_MENU01			,"Data\\Sound\\i��ư������.wav",2); 
	LoadWaveFile(SOUND_CLICK01			,"Data\\Sound\\i��ưŬ��.wav",1); 
	LoadWaveFile(SOUND_ERROR01			,"Data\\Sound\\i��ư����.wav",1); 
	LoadWaveFile(SOUND_INTERFACE01		,"Data\\Sound\\iâ����.wav",1);
#else
	LoadWaveFile(SOUND_TITLE01			,"Data\\Sound\\iTitle.wav",1); 
	LoadWaveFile(SOUND_MENU01			,"Data\\Sound\\iButtonMove.wav",2); 
	LoadWaveFile(SOUND_CLICK01			,"Data\\Sound\\iButtonClick.wav",1); 
	LoadWaveFile(SOUND_ERROR01			,"Data\\Sound\\iButtonError.wav",1); 
	LoadWaveFile(SOUND_INTERFACE01		,"Data\\Sound\\iCreateWindow.wav",1);
#endif

    LoadWaveFile(SOUND_REPAIR           ,"Data\\Sound\\iRepair.wav",1);
    LoadWaveFile(SOUND_WHISPER          ,"Data\\Sound\\iWhisper.wav",1);

	LoadWaveFile(SOUND_FRIEND_CHAT_ALERT ,"Data\\Sound\\iFMSGAlert.wav",1);
	LoadWaveFile(SOUND_FRIEND_MAIL_ALERT ,"Data\\Sound\\iFMailAlert.wav",1);
	LoadWaveFile(SOUND_FRIEND_LOGIN_ALERT,"Data\\Sound\\iFLogInAlert.wav",1);

	LoadWaveFile(SOUND_RING_EVENT_READY ,"Data\\Sound\\iEvent3min.wav",1);
	LoadWaveFile(SOUND_RING_EVENT_START ,"Data\\Sound\\iEventStart.wav",1);
	LoadWaveFile(SOUND_RING_EVENT_END   ,"Data\\Sound\\iEventEnd.wav",1);

	rUIMng.RenderTitleSceneUI(hDC, 10, 11);

#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_POSTLOADS );
#endif // DO_PROFILING_FOR_LOADING
	
#ifdef DO_PROFILING_FOR_LOADING
	g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENBASICDATA );
#endif // DO_PROFILING_FOR_LOADING
}

void OpenTextData()
{
	//���ӳ����� ���̴� �ؽ�Ʈ�� �о����
	char Text[100];

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef USE_TEXTTEST_BMD
	sprintf(Text,"Data\\Local\\%s\\Texttest_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#else
	sprintf(Text,"Data\\Local\\%s\\Text_%s.bmd", g_strSelectedML.c_str(), g_strSelectedML.c_str());
#endif
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef USE_TEXTTEST_BMD
	sprintf(Text,"Data\\Local\\Texttest.bmd");
#else
	sprintf(Text,"Data\\Local\\Text.bmd");
#endif
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
		GlobalText.Load(Text, CGlobalText::LD_SOUTH_KOREA_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_JAPANESE
		GlobalText.Load(Text, CGlobalText::LD_JAPAN_A_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_CHINESE
		GlobalText.Load(Text, CGlobalText::LD_CHINA_A_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_VIETNAMESE
		GlobalText.Load(Text, CGlobalText::LD_VIETNAM_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_PHILIPPINES
		GlobalText.Load(Text, CGlobalText::LD_PHILIPPINES_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		GlobalText.Load(Text, CGlobalText::LD_USA_CANADA_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#elif SELECTED_LANGUAGE == LANGUAGE_TAIWANESE
		GlobalText.Load(Text, CGlobalText::LD_TAIWAN_TEXTS|CGlobalText::LD_FOREIGN_TEXTS);
	#endif // SELECTED_LANGUAGE == LANGUAGE_KOREAN

	OpenMacro("Data\\Macro.txt");
}

///////////////////////////////////////////////////////////////////////////////
// ���ξ����� �ʿ��� ����Ÿ �����ϴ� �Լ�
///////////////////////////////////////////////////////////////////////////////

void ReleaseMainData()
{
	DeleteObjects();
	DeleteNpcs();
	DeleteMonsters();
	ClearItems();
	ClearCharacters();
}


void ConvertSoundFileName( void)
{
#ifdef WAV_CONVERT
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	char *lpszSoundFiles[][2] =
	{
		{"a�ٶ�.wav","aWind.wav"},
		{"a��.wav","aRain.wav"},
		{"a����.wav","aDungeon.wav"},
		{"a��.wav","aForest.wav"},
		{"až.wav","aTower.wav"},
		{"a��.wav","aWater.wav"},
		{"p�ȱ�(��).wav","pWalk(Soil).wav"},
		{"p�ȱ�(Ǯ).wav","pWalk(Grass).wav"},
		{"p�ȱ�(��).wav","pWalk(Snow).wav"},
		{"p����.wav","pSwim.wav"},
		{"a��1.wav","aBird1.wav"}, 
		{"a��2.wav","aBird2.wav"},
		{"a����.wav","aBat.wav"},
		{"a��.wav","aMouse.wav"},
		{"a��â��.wav","aGrate.wav"},
		{"a��.wav","aDoor.wav"},
		{"a����.wav","aCastleDoor.wav"},
		{"eª��Ÿ��1.wav","eShortBlow1.wav"},
		{"eª��Ÿ��2.wav","eShortBlow2.wav"},
		{"eª��Ÿ��3.wav","eShortBlow3.wav"}, 
		{"eŸ��1.wav","eBlow1.wav"}, 
		{"eŸ��2.wav","eBlow2.wav"}, 
		{"eŸ��3.wav","eBlow3.wav"}, 
		{"eŸ��4.wav","eBlow4.wav"}, 
		{"e�����ֵθ���1.wav","eSwingWeapon1.wav"},
		{"e�����ֵθ���2.wav","eSwingWeapon2.wav"},
		{"e�������ֵθ���.wav","eSwingLightSword.wav"}, 
		{"eȰ.wav","eBow.wav"},
		{"e����.wav","eCrossbow.wav"},
		{"e�ͽ�.wav","eMix.wav"},
		{"p���ñ�.wav","pDrink.wav"},
		{"p����Ա�.wav","pEatApple.wav"},
		{"p����Ҹ�.wav","pHeartBeat.wav"},
		{"p������.wav","pEnergy.wav"},
		{"p���ں��1.wav","pMaleScream1.wav"},
		{"p���ں��2.wav","pMaleScream2.wav"},
		{"p���ں��3.wav","pMaleScream3.wav"},
		{"p�����ױ�.wav","pMaleDie.wav"},
		{"p���ں��1.wav","pFemaleScream1.wav"},
		{"p���ں��2.wav","pFemaleScream2.wav"},
		{"p�����۶���Ʈ����.wav","pDropItem.wav"}, 
		{"p��ȭ����Ʈ����.wav","pDropMoney.wav"}, 
		{"e����.wav","eGem.wav"}, 
		{"p�����۰�����.wav","pGetItem.wav"}, 
		{"s������.wav","sKnightDefense.wav"},
		{"s���系�����.wav","sKnightSkill1.wav"},
		{"s�������.wav","sKnightSkill2.wav"},
		{"s����÷�ġ��.wav","sKnightSkill3.wav"},
		{"s���絹��ġ��.wav","sKnightSkill4.wav"},
		{"m���������1.wav","mShadowAttack1.wav"},
		{"s����̵�.wav","sTornado.wav"},
		{"s��ȥ.wav","sEvil.wav"},
		{"s����.wav","sMagic.wav"},
		{"s�����̾�.wav","sHellFire.wav"},
		{"s����.wav","sIce.wav"},
		{"s�ұ��.wav","sFlame.wav"},
		{"s������÷���.wav","sAquaFlash.wav"},
		{"e�μ���.wav","eBreak.wav"}, 
		{"e����.wav","eExplosion.wav"}, 
		{"e���������.wav","eMeteorite.wav"}, 
		{"e����.wav","eThunder.wav"}, 
		{"m�ذ�1.wav","mBone1.wav"},
		{"m�ذ�2.wav","mBone2.wav"},
		{"m�ϻ���1.wav","mAssassin1.wav"},
		{"n��������.wav","nBlackSmith.wav"},
		{"n����.wav","nHarp.wav"},
		{"n�ͽ�.wav","nMix.wav"},
		{"m�һ�1.wav","mBull1.wav"},
		{"m�һ�2.wav","mBull2.wav"},
		{"m�һ԰���1.wav","mBullAttack1.wav"},
		{"m�һ԰���2.wav","mBullAttack2.wav"},
		{"m�һ��ױ�.wav","mBullDie.wav"},
		{"m�Ͽ��1.wav","mHound1.wav"},
		{"m�Ͽ��2.wav","mHound2.wav"},
		{"m�Ͽ�����1.wav","mHoundAttack1.wav"},
		{"m�Ͽ�����2.wav","mHoundAttack2.wav"},
		{"m�Ͽ���ױ�.wav","mHoundDie.wav"},
		{"m����1.wav",    "mBudge1.wav"},
		{"m��������1.wav","mBudgeAttack1.wav"},
		{"m�����ױ�.wav","mBudgeDie.wav"},
		{"m�Ź�1.wav","mSpider1.wav"},
		{"m��ũ����Ʈ1.wav",    "mDarkKnight1.wav"},
		{"m��ũ����Ʈ2.wav","mDarkKnight2.wav"},
		{"m��ũ����Ʈ����1.wav","mDarkKnightAttack1.wav"},
		{"m��ũ����Ʈ����2.wav","mDarkKnightAttack2.wav"},
		{"m��ũ����Ʈ�ױ�.wav","mDarkKnightDie.wav"},
		{"m������1.wav",    "mWizard1.wav"},
		{"m������2.wav","mWizard2.wav"},
		{"m���������1.wav","mWizardAttack1.wav"},
		{"m���������2.wav","mWizardAttack2.wav"},
		{"m�������ױ�.wav","mWizardDie.wav"},
		{"m���̾�Ʈ1.wav",    "mGiant1.wav"},
		{"m���̾�Ʈ2.wav","mGiant2.wav"},
		{"m���̾�Ʈ����1.wav","mGiantAttack1.wav"},
		{"m���̾�Ʈ����2.wav","mGiantAttack2.wav"},
		{"m���̾�Ʈ�ױ�.wav","mGiantDie.wav"},
		{"m����1.wav","mLarva1.wav"},
		{"m����2.wav","mLarva2.wav"},
		{"m�ｺ���̴�1.wav",    "mHellSpider1.wav"},
		{"m�ｺ���̴�����1.wav","mHellSpiderAttack1.wav"},
		{"m�ｺ���̴��ױ�.wav","mHellSpiderDie.wav"},
		{"m����1.wav",    "mGhost1.wav"},
		{"m����2.wav","mGhost2.wav"},
		{"m���ɰ���1.wav","mGhostAttack1.wav"},
		{"m���ɰ���2.wav","mGhostAttack2.wav"},
		{"m�����ױ�.wav","mGhostDie.wav"},
		{"m�����1.wav",    "mOgre1.wav"},
		{"m�����2.wav","mOgre2.wav"},
		{"m����Ű���1.wav","mOgreAttack1.wav"},
		{"m����Ű���2.wav","mOgreAttack2.wav"},
		{"m������ױ�.wav","mOgreDie.wav"},
		{"m����1.wav",    "mGorgon1.wav"},
		{"m����2.wav","mGorgon2.wav"},
		{"m���հ���1.wav","mGorgonAttack1.wav"},
		{"m���հ���2.wav","mGorgonAttack2.wav"},
		{"m�����ױ�.wav","mGorgonDie.wav"},
		{"m��������1.wav",   "mIceMonster1.wav"},
		{"m��������2.wav","mIceMonster2.wav"},
		{"m���������ױ�.wav","mIceMonsterDie.wav"},
		{"m��1.wav",   "mWorm1.wav"},
		{"m��2.wav","mWorm2.wav"},
		{"m���ױ�.wav","mWormDie.wav"},
		{"mȣ�ӵ�1.wav",    "mHomord1.wav"},
		{"mȣ�ӵ�2.wav","mHomord2.wav"},
		{"mȣ�ӵ����1.wav","mHomordAttack1.wav"},
		{"mȣ�ӵ��ױ�.wav","mHomordDie.wav"},
		{"m���̽���1.wav",    "mIceQueen1.wav"},
		{"m���̽���2.wav","mIceQueen2.wav"},
		{"m���̽�������1.wav","mIceQueenAttack1.wav"},
		{"m���̽�������2.wav","mIceQueenAttack2.wav"},
		{"m���̽����ױ�.wav","mIceQueenDie.wav"},
		{"m�ϻ��ڰ���1.wav","mAssassinAttack1.wav"},
		{"m�ϻ��ڰ���2.wav","mAssassinAttack2.wav"},
		{"m�ϻ����ױ�.wav","mAssassinDie.wav"},
		{"m����1.wav",    "mYeti1.wav"},
		{"m����2.wav","mYeti2.wav"},
		{"m���ΰ���1.wav","mYetiAttack1.wav"},
		{"m�����ױ�.wav","mYetiDie.wav"},
		{"m���1.wav",    "mGoblin1.wav"},
		{"m���2.wav","mGoblin2.wav"},
		{"m�������1.wav","mGoblinAttack1.wav"},
		{"m�������2.wav","mGoblinAttack2.wav"},
		{"m����ױ�.wav","mGoblinDie.wav"},
		{"m������1.wav",    "mScorpion1.wav"},
		{"m������2.wav","mScorpion2.wav"},
		{"m����������1.wav","mScorpionAttack1.wav"},
		{"m����������2.wav","mScorpionAttack2.wav"},
		{"m�������ױ�.wav","mScorpionDie.wav"},
		{"mǳ����1.wav",    "mBeetle1.wav"},
		{"mǳ���̰���1.wav","mBeetleAttack1.wav"},
		{"mǳ�����ױ�.wav","mBeetleDie.wav"},
		{"m����1.wav",    "mHunter1.wav"},
		{"m����2.wav","mHunter2.wav"},
		{"m���Ͱ���1.wav","mHunterAttack1.wav"},
		{"m���Ͱ���2.wav","mHunterAttack2.wav"},
		{"m�����ױ�.wav","mHunterDie.wav"},
		{"m���Ǳ���1.wav",    "mWoodMon1.wav"},
		{"m���Ǳ���2.wav","mWoodMon2.wav"},
		{"m���Ǳ�������1.wav","mWoodMonAttack1.wav"},
		{"m���Ǳ�������2.wav","mWoodMonAttack2.wav"},
		{"m���Ǳ����ױ�.wav","mWoodMonDie.wav"},
		{"m�ư�1.wav",    "mArgon1.wav"},
		{"m�ư�2.wav","mArgon2.wav"},
		{"m�ư����1.wav","mArgonAttack1.wav"},
		{"m�ư����2.wav","mArgonAttack2.wav"},
		{"m�ư��ױ�.wav","mArgonDie.wav"},
		{"m������1.wav",    "mGolem1.wav"},
		{"m������2.wav","mGolem2.wav"},
		{"m����������1.wav","mGolemAttack1.wav"},
		{"m����������2.wav","mGolemAttack2.wav"},
		{"m�������ױ�.wav","mGolemDie.wav"},
		{"m����1.wav",    "mYeti1.wav"},
		{"m��ź����1.wav","mSatanAttack1.wav"},
		{"m�����ױ�.wav","mYetiDie.wav"},
		{"m�߷�1.wav",      "mBalrog1.wav"},
		{"m�߷�2.wav","mBalrog2.wav"},
		{"m���������2.wav","mWizardAttack2.wav"},
		{"m���հ���2.wav","mGorgonAttack2.wav"},
		{"m�߷��ױ�.wav","mBalrogDie.wav"},
		{"m������1.wav",    "mShadow1.wav"},
		{"m������2.wav","mShadow2.wav"},
		{"m���������1.wav","mShadowAttack1.wav"},
		{"m���������2.wav","mShadowAttack2.wav"},
		{"m�������ױ�.wav","mShadowDie.wav"},
		{"m����1.wav",    "mYeti1.wav"},
		{"m�һ԰���1.wav","mBullAttack1.wav"},
		{"m�����ױ�.wav","mYetiDie.wav"},
		{"m�߸�1.wav",    "mBali1.wav"},
		{"m�߸�2.wav","mBali2.wav"},
		{"m�߸�����1.wav","mBaliAttack1.wav"},
		{"m�߸�����2.wav","mBaliAttack2.wav"},
		{"m���Ϲ�Ʈ1.wav","mBahamut1.wav"},
		{"m����1.wav","mYeti1.wav"},
		{"m���ĸ�1.wav","mBepar1.wav"},
		{"m���ĸ�2.wav","mBepar2.wav"},
		{"m�߷�1.wav","mBalrog1.wav"},
		{"m��Ű��1.wav",   "mValkyrie1.wav"},
		{"m��Ű���ױ�.wav","mValkyrieDie.wav"},
		{"m���ڵ�ŷ1.wav","mLizardKing1.wav"},
		{"m���ڵ�ŷ2.wav","mLizardKing2.wav"},
		{"m�����1.wav",    "mHydra1.wav"},
		{"m��������1.wav","mHydraAttack1.wav"},
		{"m�һ��ױ�.wav","mBullDie.wav"},
		{"m����2.wav",   "mHunter2.wav"},
		{"iŸ��Ʋ.wav",    "iTitle.wav"},
		{"i��ư������.wav","iButtonMove.wav"},
		{"i��ưŬ��.wav","iButtonClick.wav"},
		{"i��ư����.wav","iButtonError.wav"},
		{"iâ����.wav","iCreateWindow.wav"},
	};
	char lpszFile[2][MAX_PATH];
	int iCount = sizeof ( lpszSoundFiles) / sizeof ( lpszSoundFiles[0]);
	for ( int i = 0; i < iCount; ++i)
	{
		wsprintf( lpszFile[0], "Data\\Sound\\%s", lpszSoundFiles[i][0]);
		if ( i == 0)
		{	// ù���� a�ٶ�.wav �� �����Ҷ��� �Ѵ�.
			if ( 0xFFFFFFFF == GetFileAttributes( lpszFile[0]))
			{
				break;
			}
		}
		wsprintf( lpszFile[1], "Data\\Sound\\%s", lpszSoundFiles[i][1]);
		MoveFile( lpszFile[0], lpszFile[1]);
	}
	char *lpszBgmFiles[][2] =
	{
		{"����.mp3","Pub.mp3"},
		{"���׸�.mp3","MuTheme.mp3"},
		{"����.mp3","Church.mp3"},
		{"����ƽ�.mp3","Devias.mp3"},
		{"�븮��.mp3","Noria.mp3"},
		{"����.mp3","Dungeon.mp3"}
	};
	iCount = sizeof ( lpszBgmFiles) / sizeof ( lpszBgmFiles[0]);
#ifdef _VS2008PORTING
	for ( int i = 0; i < iCount; ++i)
#else // _VS2008PORTING
	for ( i = 0; i < iCount; ++i)
#endif // _VS2008PORTING
	{
		wsprintf( lpszFile[0], "Data\\Music\\%s", lpszBgmFiles[i][0]);
		if ( i == 0)
		{	// ù���� ����.mp3 �� �����Ҷ��� �Ѵ�.
			if ( 0xFFFFFFFF == GetFileAttributes( lpszFile[0]))
			{
				break;
			}
		}
		wsprintf( lpszFile[1], "Data\\Music\\%s", lpszBgmFiles[i][1]);
		MoveFile( lpszFile[0], lpszFile[1]);
	}
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
#endif
}
