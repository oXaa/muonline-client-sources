///////////////////////////////////////////////////////////////////////////////
// ���ӿ� �ʿ��� �ؽ�Ʈ�� ����� �������� ���� ����Ÿ�� �о����
// ������, ��ų, ����Ʈ, �� ���͸�, ����, �ɸ��� ���� �б�
// ���ݷ�, ����, ���� ��� ��� �Լ�
//
// *** �Լ� ����: 2
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZzzInfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzScene.h"
#include "ZzzInterface.h"
#include "ReadScript.h"
#include "zzzInventory.h"
#include "zzzopenglutil.h"
#include "./Utilities/Log/ErrorReport.h"
#include "zzzLodTerrain.h"

#ifdef ANTIHACKING_ENABLE
#include "proc.h"
#endif
#include "CSItemOption.h"
#ifdef PET_SYSTEM
#include "GIPetManager.h"
#endif// PET_SYSTEM

#include "GMHellas.h"
#include "CComGem.h"
#ifndef KJH_DEL_PC_ROOM_SYSTEM		// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
#include "PCRoomPoint.h" 
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM
#include "NewUIInventoryCtrl.h"
#ifdef SOCKET_SYSTEM
#include "SocketSystem.h"
#endif	// SOCKET_SYSTEM
#include "NewUISystem.h"

CLASS_ATTRIBUTE     ClassAttribute[MAX_CLASS];
MONSTER_SCRIPT      MonsterScript [MAX_MONSTER];
GATE_ATTRIBUTE      *GateAttribute = NULL;
SKILL_ATTRIBUTE     *SkillAttribute = NULL;
ITEM_ATTRIBUTE      *ItemAttribute = NULL;
CHARACTER_MACHINE   *CharacterMachine = NULL;
CHARACTER_ATTRIBUTE *CharacterAttribute = NULL;


#ifdef STATE_LIMIT_TIME
static  int     g_iWorldStateTime = 0;
static  DWORD   g_dwWorldStateBack= 0;
#endif// STATE_LIMIT_TIME


static BYTE bBuxCode[3] = {0xfc,0xcf,0xab};
static void BuxConvert(BYTE *Buffer,int Size)
{
	for(int i=0;i<Size;i++)
		Buffer[i] ^= bBuxCode[i%3];
}

extern int GetMoveReqZenFromMCB(const char * pszTargetName);

///////////////////////////////////////////////////////////////////////////////
// text
///////////////////////////////////////////////////////////////////////////////

CGlobalText GlobalText;

void SaveTextFile(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	
	int Size = MAX_GLOBAL_TEXT_STRING;
	BYTE *Buffer = new BYTE [Size];
	for(int i=0;i<MAX_TEXTS;i++)
	{
		memcpy(Buffer,GlobalText[i],Size);
		BuxConvert(Buffer,Size);
		fwrite(Buffer,Size,1,fp);
	}
	delete [] Buffer;
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////
// server list
///////////////////////////////////////////////////////////////////////////////

#ifndef KJH_ADD_SERVER_LIST_SYSTEM				// #ifndef
void OpenServerListScript(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;

	Token = (*GetToken)();ServerNumber = (int)TokenNumber;
	for(int i=0;i<ServerNumber;i++)
	{
		Token = (*GetToken)();strcpy(ServerList[i].Name,TokenString);
		Token = (*GetToken)();ServerList[i].Number = (int)TokenNumber;
	}
	
	int NumberHi = 0;
	int NumberLow = 0;
	while(true)
	{
		SERVER_t *s = &ServerList[NumberHi].Server[NumberLow];
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
		strcpy(s->IP,TokenString);
		Token = (*GetToken)();s->Port = (int)TokenNumber;
		NumberLow++;
		if(NumberLow >= ServerList[NumberHi].Number)
		{
			NumberHi ++;
			NumberLow = 0;
		}
	}
	fclose(SMDFile);
}

void SaveServerListFile(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = sizeof(SERVER_LIST_t);
	BYTE *Buffer = new BYTE [Size];
	memcpy(Buffer,&ServerNumber,1);
	BuxConvert(Buffer,1);
	fwrite(Buffer,1,1,fp);
	for(int i=0;i<ServerNumber;i++)
	{
		memcpy(Buffer,&ServerList[i],Size);
		BuxConvert(Buffer,Size);
		fwrite(Buffer,Size,1,fp);
	}
	delete [] Buffer;
	fclose(fp);
}
void OpenServerListFile(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
		sprintf(Text,"%s - File not exist.\r\n",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}
	
	int Size = sizeof(SERVER_LIST_t);
	BYTE *Buffer = new BYTE [Size];
	fread(Buffer,1,1,fp);
	BuxConvert(Buffer,1);
	//memcpy(&ServerNumber,Buffer,1);
	for(int i=0;i<ServerNumber;i++)
	{
		fread(Buffer,Size,1,fp);
		BuxConvert(Buffer,Size);
		memcpy(&ServerList[i],Buffer,Size);
	}
	delete [] Buffer;
	fclose(fp);
}
#endif // KJH_ADD_SERVER_LIST_SYSTEM



///////////////////////////////////////////////////////////////////////////////
// filter
// ����(10.06.21) �Ʒ� �ΰ��� �Լ��� ����ϰ� ����
//		void OpenFilterFile(char *FileName)
//		void OpenNameFilterFile(char *FileName)
///////////////////////////////////////////////////////////////////////////////

char AbuseFilter[MAX_FILTERS][20];
char AbuseNameFilter[MAX_NAMEFILTERS][20];
int  AbuseFilterNumber = 0;
int  AbuseNameFilterNumber = 0;

void OpenFilterFileText(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		strcpy(AbuseFilter[AbuseFilterNumber],TokenString);
		AbuseFilterNumber++;
	}
	fclose(SMDFile);
}

void SaveFilterFile(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = 20;
	BYTE *Buffer = new BYTE [Size*MAX_FILTERS];
	BYTE *pSeek = Buffer;
	for(int i=0;i<MAX_FILTERS;i++)
	{
		memcpy(pSeek,AbuseFilter[i],Size);
		BuxConvert(pSeek,Size);
		pSeek += Size;
	}
	DWORD dwCheckSum = GenerateCheckSum2( Buffer, Size*MAX_FILTERS, 0x3E7D);
	fwrite(Buffer,Size*MAX_FILTERS,1,fp);
	fwrite(&dwCheckSum,sizeof ( DWORD),1,fp);
	delete [] Buffer;
	fclose(fp);
}

void OpenFilterFile(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}
	/*int Size = 20;
	BYTE *Buffer = new BYTE [Size];
	for(int i=0;i<MAX_FILTERS;i++)
	{
		fread(Buffer,Size,1,fp);
		BuxConvert(Buffer,Size);
		memcpy(AbuseFilter[i],Buffer,Size);
        if(AbuseFilter[i][0] == NULL)
		{
			AbuseFilterNumber = i;
			break;
		}
	}*/

	int Size = 20;
	BYTE *Buffer = new BYTE [Size*MAX_FILTERS];
	fread(Buffer,Size*MAX_FILTERS,1,fp);
	DWORD dwCheckSum;
	fread(&dwCheckSum,sizeof ( DWORD),1,fp);
	fclose(fp);
	if ( dwCheckSum != GenerateCheckSum2( Buffer, Size*MAX_FILTERS, 0x3E7D))
	{
		char Text[256];
    	sprintf(Text,"%s - File corrupted.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
	else
	{
		BYTE *pSeek = Buffer;
		for(int i=0;i<MAX_FILTERS;i++)
		{
			BuxConvert(pSeek,Size);
			memcpy(AbuseFilter[i],pSeek,Size);
			if(AbuseFilter[i][0] == NULL)
			{
				AbuseFilterNumber = i;
				break;
			}
			pSeek += Size;
		}
	}

	delete [] Buffer;
	//fclose(fp);
}

void OpenNameFilterFileText(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		strcpy(AbuseNameFilter[AbuseNameFilterNumber],TokenString);
		AbuseNameFilterNumber++;
	}
	fclose(SMDFile);
}

void SaveNameFilterFile(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = 20;
	BYTE *Buffer = new BYTE [Size*MAX_FILTERS];
	BYTE *pSeek = Buffer;
	for(int i=0;i<MAX_FILTERS;i++)
	{
		memcpy(pSeek,AbuseNameFilter[i],Size);
		BuxConvert(pSeek,Size);
		pSeek += Size;
	}
	DWORD dwCheckSum = GenerateCheckSum2( Buffer, Size*MAX_FILTERS, 0x2BC1);
	fwrite(Buffer,Size*MAX_FILTERS,1,fp);
	fwrite(&dwCheckSum,sizeof ( DWORD),1,fp);
	delete [] Buffer;
	fclose(fp);
}

void OpenNameFilterFile(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}
	int Size = 20;
	BYTE *Buffer = new BYTE [Size*MAX_NAMEFILTERS];
	
	fread(Buffer,Size*MAX_NAMEFILTERS,1,fp);
	
	DWORD dwCheckSum;
	fread(&dwCheckSum,sizeof ( DWORD),1,fp);
	fclose(fp);
	if ( dwCheckSum != GenerateCheckSum2( Buffer, Size*MAX_NAMEFILTERS, 0x2BC1))
	{
		char Text[256];
    	sprintf(Text,"%s - File corrupted.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
	else
	{
		BYTE *pSeek = Buffer;
		for(int i=0;i<MAX_NAMEFILTERS;i++)
		{
			BuxConvert(pSeek,Size);
			memcpy(AbuseNameFilter[i],pSeek,Size);
			if(AbuseNameFilter[i][0] == NULL)
			{
				AbuseNameFilterNumber = i;
				break;
			}
			pSeek += Size;
		}
	}
	delete [] Buffer;
}


///////////////////////////////////////////////////////////////////////////////
// gate
///////////////////////////////////////////////////////////////////////////////

void OpenGateScriptText(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
		if(Token == NUMBER)
		{
			int Index = (int)TokenNumber;
			GATE_ATTRIBUTE *p = &GateAttribute[Index];
			
			Token = (*GetToken)();p->Flag   = (int)TokenNumber;
			Token = (*GetToken)();p->Map    = (int)TokenNumber;
			Token = (*GetToken)();p->x1     = (int)TokenNumber;
			Token = (*GetToken)();p->y1     = (int)TokenNumber;
			Token = (*GetToken)();p->x2     = (int)TokenNumber;
			Token = (*GetToken)();p->y2     = (int)TokenNumber;
			Token = (*GetToken)();p->Target = (int)TokenNumber;
			Token = (*GetToken)();p->Angle  = (int)TokenNumber;
			Token = (*GetToken)();p->Level  = (int)TokenNumber;
		}
	}
	fclose(SMDFile);
}

void SaveGateScript(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = sizeof(GATE_ATTRIBUTE);
	BYTE *Buffer = new BYTE [Size];
	for(int i=0;i<MAX_GATES;i++)
	{
		memcpy(Buffer,&GateAttribute[i],Size);
        BuxConvert(Buffer,Size);
    	fwrite(Buffer,Size,1,fp);
	}
	delete [] Buffer;
	fclose(fp);
}

void OpenGateScript(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp != NULL)
	{
		int Size = sizeof(GATE_ATTRIBUTE);
		BYTE *Buffer = new BYTE [Size];
		for(int i=0;i<MAX_GATES;i++)
		{
			fread(Buffer,Size,1,fp);
            BuxConvert(Buffer,Size);
			memcpy(&GateAttribute[i],Buffer,Size);
		}
		delete [] Buffer;
		fclose(fp);
	}
	else
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
}

//#ifdef ADD_MONSTER_SKILL
void OpenMonsterSkillScript(char *FileName)
{
	// -1������ ��簪�� �ʱ�ȭ
	memset(MonsterSkill, -1, sizeof(Script_Skill));

	FILE *fp = fopen(FileName, "rb");
	if(fp != NULL)
	{
		int Size = (sizeof(Script_Skill) + sizeof(int));
		BYTE *Buffer = new BYTE [Size];
		int FileCount = 0;
		fread(&FileCount,sizeof(int),1,fp);
		for(int i=0;i<FileCount;i++)
		{
			fread(Buffer,Size,1,fp);
            BuxConvert(Buffer,Size);
			int dummy = -1;
			int Seek = 0;
			memcpy(&dummy,Buffer + Seek,sizeof(int));
			Seek += sizeof(int);
#ifdef CSK_FIX_MONSTERSKILL
			memcpy(MonsterSkill[dummy].Skill_Num,Buffer + Seek,sizeof(int)*MAX_MONSTERSKILL_NUM);
			Seek += (sizeof(int)*MAX_MONSTERSKILL_NUM);
#else // CSK_FIX_MONSTERSKILL
			memcpy(MonsterSkill[dummy].Skill_Num,Buffer + Seek,sizeof(int)*5);
			Seek += (sizeof(int)*5);
#endif // CSK_FIX_MONSTERSKILL
			memcpy(&MonsterSkill[dummy].Slot,Buffer + Seek,sizeof(int));
		}
		delete [] Buffer;
		fclose(fp);
	}
	else
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
}
//#endif
///////////////////////////////////////////////////////////////////////////////
// skill
///////////////////////////////////////////////////////////////////////////////

void OpenNpcScript(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
		if(Token == NUMBER)
		{
			int Type,x,y,Dir;
			Type = (int)TokenNumber;
			Token = (*GetToken)();x   = (int)TokenNumber;
			Token = (*GetToken)();y   = (int)TokenNumber;
			Token = (*GetToken)();Dir = (int)TokenNumber;
		}
	}
	fclose(SMDFile);
}

void OpenSkillScriptText(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
		if(Token == NUMBER)
		{
			int Index = (int)TokenNumber;
			SKILL_ATTRIBUTE *p = &SkillAttribute[Index];
			
			Token = (*GetToken)();strcpy(p->Name,TokenString);
			Token = (*GetToken)();p->Level    = (int)TokenNumber;
			Token = (*GetToken)();p->Damage   = (int)TokenNumber;
			Token = (*GetToken)();p->Mana     = (int)TokenNumber;
			Token = (*GetToken)();p->AbilityGuage = (int)TokenNumber;
			Token = (*GetToken)();p->Distance = (int)TokenNumber;
			Token = (*GetToken)();p->Energy = (int)TokenNumber;
			Token = (*GetToken)();
			Token = (*GetToken)();
			Token = (*GetToken)();
			Token = (*GetToken)();
		}
	}
	fclose(SMDFile);
}

void SaveSkillScript(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = sizeof(SKILL_ATTRIBUTE);
	BYTE *Buffer = new BYTE [Size*MAX_SKILLS];
	BYTE *pSeek = Buffer;
	for(int i=0;i<MAX_SKILLS;i++)
	{
		memcpy(pSeek,&SkillAttribute[i],Size);
        BuxConvert(pSeek,Size);

		pSeek += Size;
	}
   	fwrite(Buffer,Size*MAX_SKILLS,1,fp);
	DWORD dwCheckSum = GenerateCheckSum2( Buffer, Size*MAX_SKILLS, 0x5A18);
   	fwrite(&dwCheckSum, sizeof( DWORD),1,fp);
	delete [] Buffer;
	fclose(fp);
}

void OpenSkillScript(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp != NULL)
	{
		int Size = sizeof(SKILL_ATTRIBUTE);
		// �б�
		BYTE *Buffer = new BYTE [Size*MAX_SKILLS];
		fread(Buffer,Size*MAX_SKILLS,1,fp);
		// crc üũ
		DWORD dwCheckSum;
		fread(&dwCheckSum,sizeof ( DWORD),1,fp);
		fclose(fp);
		if ( dwCheckSum != GenerateCheckSum2( Buffer, Size*MAX_SKILLS, 0x5A18))
		{
			char Text[256];
    		sprintf(Text,"%s - File corrupted.",FileName);
			g_ErrorReport.Write( Text);
			MessageBox(g_hWnd,Text,NULL,MB_OK);
			SendMessage(g_hWnd,WM_DESTROY,0,0);
		}
		else
		{
			BYTE *pSeek = Buffer;
			for(int i=0;i<MAX_SKILLS;i++)
			{

				BuxConvert(pSeek,Size);
				memcpy(&SkillAttribute[i],pSeek,Size);

				pSeek += Size;
			}
		}
		delete [] Buffer;
	}
	else
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
}

#ifdef LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER	// LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER
BOOL IsValidateSkillIdx( INT iSkillIdx )
{
	if( iSkillIdx >= MAX_SKILLS || iSkillIdx < 0 )
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL IsCorrectSkillType( INT iSkillSeq, eTypeSkill iSkillTypeIdx )
{
	if ( IsValidateSkillIdx( iSkillSeq ) == FALSE )
	{
		return FALSE;
	}
	
	SKILL_ATTRIBUTE &CurSkillAttribute = SkillAttribute[iSkillSeq];
	
	if( CurSkillAttribute.TypeSkill == (BYTE)iSkillTypeIdx )
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL IsCorrectSkillType_FrendlySkill( INT iSkillSeq )
{
	return IsCorrectSkillType( iSkillSeq, eTypeSkill_FrendlySkill );
}

BOOL IsCorrectSkillType_Buff( INT iSkillSeq )
{
	return IsCorrectSkillType( iSkillSeq, eTypeSkill_Buff );
}

BOOL IsCorrectSkillType_DeBuff( INT iSkillSeq )
{
	return IsCorrectSkillType( iSkillSeq, eTypeSkill_DeBuff );	
}

BOOL IsCorrectSkillType_CommonAttack( INT iSkillSeq )
{
	return IsCorrectSkillType( iSkillSeq, eTypeSkill_CommonAttack );
}

#endif // LDS_FIX_APPLYSKILLTYPE_AND_CURSEDTEMPLEWRONGPARTYMEMBER

///////////////////////////////////////////////////////////////////////////////
// dialog
///////////////////////////////////////////////////////////////////////////////


int g_iCurrentDialog = -1;
DIALOG_SCRIPT g_DialogScript[MAX_DIALOG];

void OpenDialogFileText(char *FileName)
{
	ZeroMemory( g_DialogScript, MAX_DIALOG * sizeof ( DIALOG_SCRIPT));

	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NUMBER)
		{
			int Index = (int)TokenNumber;
			Token = (*GetToken)();
			strcpy( g_DialogScript[Index].m_lpszText, TokenString);

			g_DialogScript[Index].m_iNumAnswer = 0;
			while(true)
			{
				Token = (*GetToken)();
				int Link = (int)TokenNumber;
				if(Token==NAME && strcmp("end",TokenString)==NULL) break;
				g_DialogScript[Index].m_iLinkForAnswer[g_DialogScript[Index].m_iNumAnswer] = Link;
				Token = (*GetToken)();
				int Return = (int)TokenNumber;
				g_DialogScript[Index].m_iReturnForAnswer[g_DialogScript[Index].m_iNumAnswer] = Return;
				Token = (*GetToken)();
				strcpy( g_DialogScript[Index].m_lpszAnswer[g_DialogScript[Index].m_iNumAnswer], TokenString);

				g_DialogScript[Index].m_iNumAnswer++;
			}
			g_DialogScript[Index].m_iLinkForAnswer[g_DialogScript[Index].m_iNumAnswer] = -1;
		}
	}
	fclose(SMDFile);
}

void SaveDialogFile(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = sizeof ( DIALOG_SCRIPT);
	BYTE *Buffer = new BYTE [Size];
	for(int i=0;i<MAX_DIALOG;i++)
	{
		memcpy(Buffer,&g_DialogScript[i],Size);
		BuxConvert(Buffer,Size);
		fwrite(Buffer,Size,1,fp);
	}
	delete [] Buffer;
	fclose(fp);
}

void OpenDialogFile(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp == NULL)
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}
	int Size = sizeof ( DIALOG_SCRIPT);
	BYTE *Buffer = new BYTE [Size];
	for(int i=0;i<MAX_DIALOG;i++)
	{
		fread(Buffer,Size,1,fp);
		BuxConvert(Buffer,Size);
		memcpy(&g_DialogScript[i],Buffer,Size);
	}
	delete [] Buffer;
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////
// item
///////////////////////////////////////////////////////////////////////////////

int ConvertItemType(BYTE *Item)
{
	int ret = 0;
	ret = Item[0]+(Item[3]&128)*2+ (Item[5]&240)*32;
	return ret;
}

void OpenItemScriptText(char *FileName)	// 0.1 ( 2003.01.08)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NUMBER)
		{
			int Type = (int)TokenNumber;
			while(true)
			{
				Token = (*GetToken)();
				int Index = (int)TokenNumber;
				if(Token==NAME && strcmp("end",TokenString)==NULL) break;
				int iItemIndex = Type*MAX_ITEM_INDEX+Index;
               	ITEM_ATTRIBUTE *p = &ItemAttribute[iItemIndex];
				memset(p,0,sizeof(ITEM_ATTRIBUTE));

				Token = (*GetToken)();p->Width  = (int)TokenNumber;
				Token = (*GetToken)();p->Height = (int)TokenNumber;
				Token = (*GetToken)();//�ø���
				Token = (*GetToken)();//�ɼ�
				Token = (*GetToken)();//����
				Token = (*GetToken)();strcpy(p->Name,TokenString);
				if(Type>=0 && Type<=5)
				{
					Token = (*GetToken)();p->Level	      	  = (int)TokenNumber;
					Token = (*GetToken)();p->DamageMin		  = (int)TokenNumber;
					Token = (*GetToken)();p->DamageMax		  = (int)TokenNumber;
					Token = (*GetToken)();p->WeaponSpeed	  = (int)TokenNumber;
					Token = (*GetToken)();p->Durability       = (int)TokenNumber;
					Token = (*GetToken)();p->MagicDur        = (int)TokenNumber;
					Token = (*GetToken)();p->RequireStrength  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireDexterity = (int)TokenNumber;
					if(p->Width >= 2) p->TwoHand = true;
				}
				if(Type>=6 && Type<=11)
				{
      				Token = (*GetToken)();p->Level            = (int)TokenNumber;
					if(Type==6)
					{
						Token = (*GetToken)();p->Defense      = (int)TokenNumber;
						Token = (*GetToken)();p->SuccessfulBlocking = (int)TokenNumber;
					}
					else if(Type>=7 && Type<=9)
					{
						Token = (*GetToken)();p->Defense      = (int)TokenNumber;
						Token = (*GetToken)();p->MagicDefense = (int)TokenNumber;
					}
					else if(Type==10)
					{
						Token = (*GetToken)();p->Defense      = (int)TokenNumber;
						Token = (*GetToken)();p->WeaponSpeed  = (int)TokenNumber;
					}
					else if(Type==11)
					{
						Token = (*GetToken)();p->Defense      = (int)TokenNumber;
						Token = (*GetToken)();p->WalkSpeed    = (int)TokenNumber;
					}
					Token = (*GetToken)();p->Durability		  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireLevel		  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireStrength  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireDexterity = (int)TokenNumber;
				}
				if(Type==12)
				{
      				Token = (*GetToken)();p->Level         = (int)TokenNumber;
					Token = (*GetToken)();p->Defense       = (int)TokenNumber;
					Token = (*GetToken)();p->Durability	   = (int)TokenNumber;
      				Token = (*GetToken)();p->RequireLevel  = (int)TokenNumber;
      				Token = (*GetToken)();p->RequireEnergy = (int)TokenNumber;
					Token = (*GetToken)();p->RequireStrength = (int)TokenNumber;
					Token = (*GetToken)();p->RequireDexterity = (int)TokenNumber;
				}
				if(Type==13)
				{
      				Token = (*GetToken)();p->Level          = (int)TokenNumber;
      				Token = (*GetToken)();p->Durability     = (int)TokenNumber;
					Token = (*GetToken)();p->Resistance[0]  = (int)TokenNumber;
					Token = (*GetToken)();p->Resistance[1]  = (int)TokenNumber;
					Token = (*GetToken)();p->Resistance[2]  = (int)TokenNumber;
					Token = (*GetToken)();p->Resistance[3]  = (int)TokenNumber;
					p->RequireLevel = p->Level;
				}
				if(Type==14)
				{
					Token = (*GetToken)();p->Value = (int)TokenNumber;
      				Token = (*GetToken)();p->Level = (int)TokenNumber;
				}
				if(Type==15)
				{
      				Token = (*GetToken)();p->Level         = (int)TokenNumber;
					Token = (*GetToken)();p->RequireLevel = (int)TokenNumber;
      				Token = (*GetToken)();p->RequireEnergy = (int)TokenNumber;
                    p->DamageMin = p->Level;
                    p->DamageMax = p->Level+p->Level/2;
				}
				//��� Ŭ����
				if(Type<=13 || Type==15)
				{
					Token = (*GetToken)();p->RequireClass[0]  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireClass[1]  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireClass[2]  = (int)TokenNumber;
					Token = (*GetToken)();p->RequireClass[3]  = (int)TokenNumber;
				}
			}
		}
	}
	fclose(SMDFile);
	/*for(int i=0;i<MAX_ITEM_INDEX/2;i++)
	{
		memcpy(&ItemAttribute[ITEM_ARMOR+i+MAX_ITEM_INDEX/2],&ItemAttribute[ITEM_ARMOR+i],sizeof(ITEM_ATTRIBUTE));
		memcpy(&ItemAttribute[ITEM_PANTS+i+MAX_ITEM_INDEX/2],&ItemAttribute[ITEM_PANTS+i],sizeof(ITEM_ATTRIBUTE));
		memcpy(&ItemAttribute[ITEM_GLOVE+i+MAX_ITEM_INDEX/2],&ItemAttribute[ITEM_GLOVE+i],sizeof(ITEM_ATTRIBUTE));
		memcpy(&ItemAttribute[ITEM_BOOTS +i+MAX_ITEM_INDEX/2],&ItemAttribute[ITEM_BOOTS +i],sizeof(ITEM_ATTRIBUTE));
	}*/
}

void SaveItemScript(char *FileName)
{
	FILE *fp = fopen(FileName,"wb");
	int Size = sizeof(ITEM_ATTRIBUTE);
	BYTE *Buffer = new BYTE [Size*MAX_ITEM];
	BYTE *pSeek = Buffer;
	for(int i=0;i<MAX_ITEM;i++)
	{
   		memcpy(pSeek,&ItemAttribute[i],Size);
        BuxConvert(pSeek,Size);

		pSeek += Size;
	}
   	fwrite(Buffer,Size*MAX_ITEM,1,fp);
	DWORD dwCheckSum = GenerateCheckSum2( Buffer, Size*MAX_ITEM, 0xE2F1);
   	fwrite(&dwCheckSum, sizeof( DWORD),1,fp);
	delete [] Buffer;
	fclose(fp);
}

void OpenItemScript(char *FileName)
{
	FILE *fp = fopen(FileName,"rb");
	if(fp != NULL)
	{
		int Size = sizeof(ITEM_ATTRIBUTE);
		// �б�
		BYTE *Buffer = new BYTE [Size*MAX_ITEM];
		fread(Buffer,Size*MAX_ITEM,1,fp);
		// crc üũ
		DWORD dwCheckSum;
		fread(&dwCheckSum,sizeof ( DWORD),1,fp);
		fclose(fp);
		if ( dwCheckSum != GenerateCheckSum2( Buffer, Size*MAX_ITEM, 0xE2F1))
		{
			char Text[256];
    		sprintf(Text,"%s - File corrupted.",FileName);
			g_ErrorReport.Write( Text);
			MessageBox(g_hWnd,Text,NULL,MB_OK);
			SendMessage(g_hWnd,WM_DESTROY,0,0);
		}
		else
		{
			BYTE *pSeek = Buffer;
			for(int i=0;i<MAX_ITEM;i++)
			{
				BuxConvert(pSeek,Size);
				memcpy(&ItemAttribute[i],pSeek,Size);
				pSeek += Size;
			}
		}
		delete [] Buffer;
	}
	else
	{
		char Text[256];
    	sprintf(Text,"%s - File not exist.",FileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
	}
}

void PrintItem(char *FileName)
{
	FILE *fp = fopen(FileName,"wt");
    fprintf(fp,"                �̸�  �ּҰ��ݷ� �ִ���ݷ� ���� ����� �ʿ��� �ʿ��ø �ʿ信����\n");
	//fprintf(fp,"                �̸�    ī��������Ȯ��\n");
	bool Excellent = true;
	for(int i=0;i<16*MAX_ITEM_INDEX;i++)
	{
		if ( ( i & 0x1FF) == 0)
		{
			fprintf(fp, "------------------------------------------------------------------------------------------------------\n");
		}
        ITEM_ATTRIBUTE *p = &ItemAttribute[i];
		if(p->Name[0] != NULL)
		{
			int Plus;
			if(i >= 12*MAX_ITEM_INDEX)
				Plus = 1;
			else
				Plus = 10;
			for(int j=0;j<Plus;j++)
			{
				int Level = j;
				int RequireStrength = 0;
				int RequireDexterity = 0;
				int RequireEnergy = 0;
				int DamageMin = p->DamageMin;
				int DamageMax = p->DamageMax;
				int Defense   = p->Defense;
				int SuccessfulBlocking = p->SuccessfulBlocking;
				if(DamageMin > 0)
				{
					if(Excellent)
					{
						if(p->Level)
							DamageMin += p->DamageMin*25/p->Level+5;
					}
					DamageMin += Level*3;
				}
				if(DamageMax > 0)
				{
					if(Excellent)
					{
						if(p->Level)
							DamageMax += p->DamageMin*25/p->Level+5;
					}
					DamageMax += Level*3;
				}
				if(Defense   > 0)
				{
					if(i>=ITEM_SHIELD && i<ITEM_SHIELD+MAX_ITEM_INDEX)
					{
						Defense += Level;
					}
					else
					{
       					if(Excellent)
						{
							if(p->Level)
								Defense    += p->Defense*12/p->Level+4+p->Level/5;
						}
						Defense += Level*3;
					}
				}
				if(SuccessfulBlocking > 0)
				{
     				if(Excellent)
					{
						if(p->Level)
							SuccessfulBlocking += p->SuccessfulBlocking*25/p->Level+5;
					}
					SuccessfulBlocking += Level*3;
				}
				int ItemLevel = p->Level;
     	 		if(Excellent)
              		ItemLevel = p->Level + 25;
				if(p->RequireStrength)
					RequireStrength  = 20+p->RequireStrength *(ItemLevel+Level*3)*3/100;
				else
					RequireStrength  = 0;
				if(p->RequireDexterity)
					RequireDexterity = 20+p->RequireDexterity*(ItemLevel+Level*3)*3/100;
				else
					RequireDexterity = 0;
				if(p->RequireEnergy)
				{
					RequireEnergy    = 20+p->RequireEnergy   *(ItemLevel+Level*3)*4/10;
				}
				else
				{
					RequireEnergy    = 0;
				}
				if(i>=ITEM_STAFF && i<ITEM_STAFF*MAX_ITEM_INDEX)
				{
             		DamageMin = DamageMin/2+Level*2;
             		DamageMax = 0;
				}
				ITEM ip;
				ip.Type       = i;
       			ItemConvert(&ip,j<<3,Excellent,0);

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
				ItemValue( &ip, 0);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
				int iValue = ItemValue( &ip, 0);
				int iRate = min( iValue / 20000, 100);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
				if(j==0)
     				fprintf(fp,"%20s %8d %8d %8d %8d %8d %8d %8d %8d %8d\n",p->Name,DamageMin,DamageMax,Defense, SuccessfulBlocking,RequireStrength,RequireDexterity,RequireEnergy,p->WeaponSpeed,ItemValue(&ip));
     				//fprintf(fp,"%20s %4d%%",p->Name, iRate);
				else
     				fprintf(fp,"%17s +%d %8d %8d %8d %8d %8d %8d %8d %8d %8d\n","",Level,DamageMin,DamageMax,Defense,SuccessfulBlocking,RequireStrength,RequireDexterity,RequireEnergy,p->WeaponSpeed,ItemValue(&ip));
					//fprintf(fp,"%4d%%<+%d>",iRate,Level);
			}
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}


//////////////////////////////////////////////////////////////////////////
//	������ �ش�Ǵ� ��ų �ε����� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
BYTE getSkillIndexByBook ( int Type )
{
	int SkillIndex = Type-ITEM_ETC+1;
	switch ( SkillIndex )
	{
	case 17: SkillIndex = AT_SKILL_BLAST_POISON; break;
	case 18: SkillIndex = AT_SKILL_BLAST_FREEZE; break;
	case 19: SkillIndex = AT_SKILL_BLAST_HELL;   break;
	}

	return SkillIndex;
}

#ifdef CSK_FIX_EPSOLUTESEPTER
// ���� �������ΰ�?
bool IsCepterItem(int iType)
{
	if( (iType >= ITEM_MACE+8 && iType <= ITEM_MACE+15)
		|| iType == ITEM_MACE+17
#ifdef LDK_ADD_GAMBLERS_WEAPONS
		|| iType == ITEM_MACE+18
#endif //LDK_ADD_GAMBLERS_WEAPONS
		)
	{
		return true;
	}

	return false;
}

#endif // CSK_FIX_EPSOLUTESEPTER

//////////////////////////////////////////////////////////////////////////
//	������ ������ �Է��Ѵ�.
//////////////////////////////////////////////////////////////////////////
void ItemConvert(ITEM *ip,BYTE Attribute1,BYTE Attribute2, BYTE Attribute3 )
{
	// Attribute1 - [��ų][����][����][����][����][���][�ɼ�][�ɼ�]
	// Attribute2 - [----][�ɼ�][����][����][����][����][����][����]
	// Attribute3 - [�̸�][----][----][----][��Ʈ][��Ʈ][��Ʈ][��Ʈ]
	ip->Level = Attribute1;
	int     Level = (Attribute1>>3)&15;
    int     excel = Attribute2&63;
    int     excelWing = excel;
	int     excelAddValue = 0;
    bool    bExtOption = false;

    if ( ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )	// ������ ���� ~ ������ ����
		|| ( ip->Type >= ITEM_WING+36 && ip->Type <= ITEM_WING+40 )	// 3�� ������
#ifdef ADD_ALICE_WINGS_1
		|| (ip->Type >= ITEM_WING+42 && ip->Type <= ITEM_WING+43)	// ��ȯ���� 2,3�� ����.
#endif	// ADD_ALICE_WINGS_1
		|| ip->Type==ITEM_SWORD+19	// ��õ���� �����
		|| ip->Type==ITEM_BOW+18	// ��õ���� ���뼮��	
		|| ip->Type==ITEM_STAFF+10	// ��õ���� ����������
		|| ip->Type==ITEM_MACE+13	// ��õ���� �������
		|| ip->Type == ITEM_HELPER+30 // ������ ����
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
		|| ( ITEM_WING+130 <= ip->Type && ip->Type <= ITEM_WING+134 )
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (ip->Type >= ITEM_WING+49 && ip->Type <= ITEM_WING+50)	// �����������ͳ���
		|| (ip->Type == ITEM_WING+135)	// ���������Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		) 
    {
        excel = 0;
    }
	
    if ( (Attribute3%0x4)==EXT_A_SET_OPTION || (Attribute3%0x4)==EXT_B_SET_OPTION )    //  ��Ʈ ������.
    {
        excel = 1;
        bExtOption = true;
    }

	ITEM_ATTRIBUTE *p = &ItemAttribute[ip->Type];
	ip->TwoHand            = p->TwoHand;
	ip->WeaponSpeed        = p->WeaponSpeed;
    ip->DamageMin          = p->DamageMin;
	ip->DamageMax		   = p->DamageMax;
	ip->SuccessfulBlocking = p->SuccessfulBlocking;
	ip->Defense            = p->Defense;
	ip->MagicDefense       = p->MagicDefense;
	ip->WalkSpeed          = p->WalkSpeed;
	ip->MagicPower		   = p->MagicPower;

    int setItemDropLevel = p->Level+30;

	//	�׼���Ʈ ī���� �������� ���� ��ġ.
	if ( ip->Type==ITEM_MACE+6 )	// ī������ ���� ����
	{
		excelAddValue = 15;
	}
	else if ( ip->Type==ITEM_BOW+6 )	// ī���������ĺ���
	{
		excelAddValue = 30;
	}
	else if ( ip->Type==ITEM_STAFF+7 )	// ī���� ����������
	{
		excelAddValue = 25;
	}

	if ( p->DamageMin>0 )
	{
        //  �׼���Ʈ �������� ���.
		if ( excel>0 )
		{
			if ( p->Level )
            {
                if ( excelAddValue )
					ip->DamageMin += excelAddValue;
				else
					ip->DamageMin += p->DamageMin*25/p->Level+5;
            }
		}
        if ( bExtOption )    //  ��Ʈ ������.
        {
            ip->DamageMin += 5+(setItemDropLevel/40);
        }
        ip->DamageMin     += (min(9,Level)*3);	// ~ +9������
		switch(Level - 9)
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->DamageMin += 9;	// +15 ������
		case 5: ip->DamageMin += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->DamageMin += 7;	// +13 ������
		case 3: ip->DamageMin += 6;	// +12 ������
		case 2: ip->DamageMin += 5;	// +11 ������
		case 1: ip->DamageMin += 4;	// +10 ������
		default: break;
		};
	}
	if ( p->DamageMax>0 )
	{
        //  �׼���Ʈ �������� ���.
		if ( excel>0 )
		{
			if ( p->Level )
            {
                if ( excelAddValue )
					ip->DamageMax += excelAddValue;
				else
					ip->DamageMax += p->DamageMin*25/p->Level+5;
            }
		}
        if ( bExtOption )    //  ��Ʈ ������.
        {
            ip->DamageMax += 5+(setItemDropLevel/40);
        }
        ip->DamageMax     += (min(9,Level)*3);	// ~ +9������
		switch ( Level-9 )
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->DamageMax += 9;	// +15 ������
		case 5: ip->DamageMax += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->DamageMax += 7;	// +13 ������
		case 3: ip->DamageMax += 6;	// +12 ������
		case 2: ip->DamageMax += 5;	// +11 ������
		case 1: ip->DamageMax += 4;	// +10 ������
		default: break;
		};
	}
	if ( p->MagicPower>0 )
	{
        //  �׼���Ʈ �������� ���.
		if ( excel>0 )
		{
			if ( p->Level )
            {
				if ( excelAddValue )
					ip->MagicPower += excelAddValue;
				else
					ip->MagicPower += p->MagicPower*25/p->Level+5;
            }
		}
        if ( bExtOption )    //  ��Ʈ ������.
        {
            ip->MagicPower += 2+(setItemDropLevel/60);
        }
        ip->MagicPower += (min(9,Level)*3);	// ~ +9������
		switch ( Level-9 )
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->MagicPower += 9;	// +15 ������
		case 5: ip->MagicPower += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->MagicPower += 7;	// +13 ������
		case 3: ip->MagicPower += 6;	// +12 ������
		case 2: ip->MagicPower += 5;	// +11 ������
		case 1: ip->MagicPower += 4;	// +10 ������
		default: break;
		};
		
		ip->MagicPower /= 2;
		
		//  ���Ͱ� �ƴ� ��쿡��.
#ifdef CSK_FIX_EPSOLUTESEPTER
		if(IsCepterItem(ip->Type) == false)
#else // CSK_FIX_EPSOLUTESEPTER
		if ( ip->Type<ITEM_MACE+8 || ip->Type>ITEM_MACE+15 )
#endif // CSK_FIX_EPSOLUTESEPTER
		{
            ip->MagicPower += Level*2;
		}
	}

	if ( p->SuccessfulBlocking>0 )
	{
        //  �׼���Ʈ �������� ���.
		if(excel> 0)
		{
			if(p->Level)
				ip->SuccessfulBlocking += p->SuccessfulBlocking*25/p->Level+5;
		}
        ip->SuccessfulBlocking += (min(9,Level)*3);	// ~ +9������
		switch(Level - 9)
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->SuccessfulBlocking += 9;	// +15 ������
		case 5: ip->SuccessfulBlocking += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->SuccessfulBlocking += 7;	// +13 ������
		case 3: ip->SuccessfulBlocking += 6;	// +12 ������
		case 2: ip->SuccessfulBlocking += 5;	// +11 ������
		case 1: ip->SuccessfulBlocking += 4;	// +10 ������
		default: break;
		};
	}
#ifdef PBG_MOD_NEWCHAR_MONK_WING_2
	if(ip->Type==ITEM_HELPER+30)
	{
		////////////////////////////////////////////////////////////////////
		// �����ɼǱ�ȹ���� (�ε��� ���� �Ұ���)
		// 13�ε��� �������� defense �� ���� �����ϳ��� Ȯ���ϱ⿣ ����
		// ���� : 15 + (���䷹�� * 2) ��Ÿ �����ɼ��� �ϴ� �ҽ�Ȯ�� ���
		////////////////////////////////////////////////////////////////////
		p->Defense = 15;
		ip->Defense = 15;
	}
#endif //PBG_MOD_NEWCHAR_MONK_WING_2
	if ( p->Defense>0 )
	{
		if(ip->Type>=ITEM_SHIELD && ip->Type<ITEM_SHIELD+MAX_ITEM_INDEX)
		{
     		ip->Defense            += Level;
            if ( bExtOption )    //  ��Ʈ ������.
            {
                ip->Defense = ip->Defense+(ip->Defense*20/setItemDropLevel+2);
            }
		}
		else
		{
            //  �׼���Ʈ �������� ���.
    		if(excel> 0)
			{
				if(p->Level)
      				ip->Defense    += p->Defense*12/p->Level+4+p->Level/5;
			}
            if ( bExtOption )    //  ��Ʈ ������.
            {
                ip->Defense = ip->Defense+(ip->Defense*3/setItemDropLevel+2+setItemDropLevel/30);
            }

            //  õ�� �߰� ����.
#ifdef ADD_ALICE_WINGS_1
			if ((ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6) || ip->Type == ITEM_WING+42)
#else	// ADD_ALICE_WINGS_1
            if ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )
#endif	// ADD_ALICE_WINGS_1
            {
                ip->Defense     += (min(9,Level)*2);	// ~ +9������
            }
            else if ( ip->Type==ITEM_HELPER+30 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				|| ip->Type==ITEM_WING+49				// ������ ����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				)        //  ������ ����.
            {
                ip->Defense     += ( min( 9, Level )*2 );	// ~ +9������
            }
#ifdef ADD_ALICE_WINGS_1
			else if ((ip->Type >= ITEM_WING+36 && ip->Type <= ITEM_WING+40) || ip->Type == ITEM_WING+43
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				|| (ip->Type == ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				)	// 3�� ������
#else	// ADD_ALICE_WINGS_1
			else if ( ip->Type >= ITEM_WING+36 && ip->Type <= ITEM_WING+40 )	// 3�� ������
#endif	// ADD_ALICE_WINGS_1
			{
                ip->Defense     += (min(9,Level)*4);	// ~ +9������
			}
            else
            {
                ip->Defense     += (min(9,Level)*3);	// ~ +9������
            }
#ifdef ADD_ALICE_WINGS_1
			if ((ip->Type >= ITEM_WING+36 && ip->Type <= ITEM_WING+40) || ip->Type == ITEM_WING+43
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				|| ip->Type == ITEM_WING+50	//�����Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				)	// 3�� ������
#else	// ADD_ALICE_WINGS_1
			if ( ip->Type >= ITEM_WING+36 && ip->Type <= ITEM_WING+40 )	// 3�� ������
#endif	// ADD_ALICE_WINGS_1
			{
				switch(Level - 9)
				{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 6: ip->Defense += 10;	// +15 ������
				case 5: ip->Defense += 9;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 4: ip->Defense += 8;	// +13 ������
				case 3: ip->Defense += 7;	// +12 ������
				case 2: ip->Defense += 6;	// +11 ������
				case 1: ip->Defense += 5;	// +10 ������
				default: break;
				};
			}
			else
			{
				switch(Level - 9)
				{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 6: ip->Defense += 9;	// +15 ������
				case 5: ip->Defense += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
				case 4: ip->Defense += 7;	// +13 ������
				case 3: ip->Defense += 6;	// +12 ������
				case 2: ip->Defense += 5;	// +11 ������
				case 1: ip->Defense += 4;	// +10 ������
				default: break;
				};
			}
		}
	}
	if ( p->MagicDefense>0 )
    {
        ip->MagicDefense += (min(9,Level)*3);	// ~ +9������
		switch(Level - 9)
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->MagicDefense += 9;	// +15 ������
		case 5: ip->MagicDefense += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->MagicDefense += 7;	// +13 ������
		case 3: ip->MagicDefense += 6;	// +12 ������
		case 2: ip->MagicDefense += 5;	// +11 ������
		case 1: ip->MagicDefense += 4;	// +10 ������
		default: break;
		};
    }

	////////�ʿ� �ɷ�ġ/////////////////////////////////////////////////////////////////////////////
	
	//  �Ϲ� �������� ���
	int ItemLevel = p->Level;
    //  �׼���Ʈ �������� ���.
    if( excel )	ItemLevel = p->Level + 25;
	//  ��Ʈ �������� ���
	else if( bExtOption ) ItemLevel = p->Level + 30;

	//  �䱸 ����.
    int addValue = 4;
#ifdef ADD_ALICE_WINGS_1
	if ((ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6) || ip->Type == ITEM_WING+42)
#else	// ADD_ALICE_WINGS_1
	if ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )
#endif	// ADD_ALICE_WINGS_1
    {
        addValue = 5;
    }

	if(p->RequireLevel && ((ip->Type >= ITEM_SWORD && ip->Type < ITEM_WING)
		|| (ip->Type == ITEM_HELPER+37)	//^ �渱 ������ �Ӽ� ����
#ifdef ADD_ALICE_WINGS_1
		|| (ip->Type >= ITEM_WING+7 && ip->Type <= ITEM_WING+40)
		|| (ip->Type >= ITEM_WING+43 && ip->Type < ITEM_HELPER)
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		&& (ip->Type != ITEM_WING+49)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		))
#else	// ADD_ALICE_WINGS_1
		|| (ip->Type >= ITEM_WING+7 && ip->Type <= ITEM_HELPER)))     //����
#endif	// ADD_ALICE_WINGS_1
		ip->RequireLevel = p->RequireLevel;
	else if (p->RequireLevel && ((ip->Type >= ITEM_WING && ip->Type <= ITEM_WING+7)
#ifdef ADD_ALICE_WINGS_1
		|| (ip->Type >= ITEM_WING+41 && ip->Type <= ITEM_WING+42)
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| (ip->Type == ITEM_WING+49)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		|| ip->Type >= ITEM_HELPER))
     	ip->RequireLevel = p->RequireLevel+Level*addValue;//����,�����;
	else
		ip->RequireLevel = 0;


    if(p->RequireStrength)   //��
		ip->RequireStrength  = 20+(p->RequireStrength)*(ItemLevel+Level*3)*3/100;
	else	ip->RequireStrength  = 0;

	if(p->RequireDexterity)  //��ø
		ip->RequireDexterity = 20+(p->RequireDexterity)*(ItemLevel+Level*3)*3/100;
	else	ip->RequireDexterity = 0;

	if(p->RequireVitality)  //ü��
		ip->RequireVitality = 20+(p->RequireVitality)*(ItemLevel+Level*3)*3/100;
	else	ip->RequireVitality = 0;

	if(p->RequireEnergy)  //������
	{
		if (ip->Type >= ITEM_STAFF+21 && ip->Type <= ITEM_STAFF+29)	// ��ȯ���� ���� �䱸�������� ����
		{
			ip->RequireEnergy = 20+(p->RequireEnergy)*(ItemLevel+Level*1)*3/100;
		}
		else
	
// p->RequireLevel : ������ ���� �䱸ġ
// p->RequireEnergy : ������ ������ �䱸ġ
// ip->RequireEnergy : ���� ������ �䱸ġ (���Ȱ�)
#ifdef KJH_FIX_LEARN_SKILL_ITEM_REQUIRE_STAT_CALC
		// ���� �䱸ġ�� 0�̸� ���� ����� ����.
		// skill.txt ���� ���� ������ �����䱸ġ�� ������ ���� ���, ����ó�� ��.
		// �䱸ġ ����� �ڵ忡 �� �־�� �ϴ��� �ǹ�.. ��ġ��!!!!
		if((p->RequireLevel > 0) && (ip->Type >= ITEM_ETC && ip->Type < ITEM_ETC+MAX_ITEM_INDEX) )	// ����
		{
			ip->RequireEnergy = 20+(p->RequireEnergy)*(p->RequireLevel)*4/100;
		}
		else
#endif // KJH_FIX_LEARN_SKILL_ITEM_REQUIRE_STAT_CALC
 
		{
			ip->RequireEnergy = 20+(p->RequireEnergy)*(ItemLevel+Level*3)*4/100;
		}
	}
	else
	{
		ip->RequireEnergy = 0;
	}

	if(p->RequireCharisma)  //���
		ip->RequireCharisma = 20+(p->RequireCharisma)*(ItemLevel+Level*3)*3/100;
	else	ip->RequireCharisma = 0;

    //  ��ȯ ���� �䱸 ��������.
    if(ip->Type==ITEM_WING+11)
    {
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		WORD Energy = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        WORD Energy;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        switch(Level)
        {
		case 0:Energy = 30;break;
		case 1:Energy = 60;break;
		case 2:Energy = 90;break;
		case 3:Energy = 130;break;
		case 4:Energy = 170;break;
		case 5:Energy = 210;break;
		case 6:Energy = 300;break;
#ifdef ADD_ELF_SUMMON
		case 7:Energy = 500;break;
#endif // ADD_ELF_SUMMON
        }
        ip->RequireEnergy = Energy;
    }

    if ( p->RequireCharisma )
    {
        //  ��ũ���Ǹ��� �䱸 ���.
        if ( ip->Type==MODEL_HELPER+5 )
            ip->RequireCharisma = (185+(p->RequireCharisma*15));
        else
            ip->RequireCharisma = p->RequireCharisma;
    }

	if ( ip->Type==ITEM_HELPER+10 )//   ���Ź���
	{
		if ( Level<=2 )
			ip->RequireLevel = 20;
		else
			ip->RequireLevel = 50;
	}

    //  �׼���Ʈ.
	if( (ip->Type >= ITEM_HELM+29 && ip->Type <= ITEM_HELM+33) ||
		(ip->Type >= ITEM_ARMOR+29 && ip->Type <= ITEM_ARMOR+33) ||
		(ip->Type >= ITEM_PANTS+29 && ip->Type <= ITEM_PANTS+33) ||
		(ip->Type >= ITEM_GLOVES+29 && ip->Type <= ITEM_GLOVES+33) ||
		(ip->Type >= ITEM_BOOTS+29 && ip->Type <= ITEM_BOOTS+33)  ||
		ip->Type == ITEM_SWORD+22 ||
		ip->Type == ITEM_SWORD+23 ||
		ip->Type == ITEM_STAFF+12 ||
		ip->Type == ITEM_BOW+21 ||
		ip->Type == ITEM_MACE+14
#ifdef ASG_ADD_STORMBLITZ_380ITEM
		|| ITEM_STAFF+19 == ip->Type
		|| ITEM_HELM+43 == ip->Type
		|| ITEM_ARMOR+43 == ip->Type
		|| ITEM_PANTS+43 == ip->Type
		|| ITEM_GLOVES+43 == ip->Type
		|| ITEM_BOOTS+43 == ip->Type
#endif	// ASG_ADD_STORMBLITZ_380ITEM
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ �䱸���� ����ó�� excel
		|| Check_LuckyItem( ip->Type )
#endif // LEM_ADD_LUCKYITEM
		)
	{
		excel = 0;
	}

	if ( excel>0 )
	{
		if(ip->RequireLevel > 0 && ip->Type != ITEM_HELPER+37)	//^ �渱 ������ �Ӽ� ����
      		ip->RequireLevel += 20;
	}

	ip->SpecialNum = 0;
    //  �߰� ����.
#ifdef ADD_ALICE_WINGS_1
	if ((ip->Type >= ITEM_WING+3 && ip->Type <= ITEM_WING+6) || ip->Type == ITEM_WING+42)
#else	// ADD_ALICE_WINGS_1
    if ( ip->Type>=ITEM_WING+3 && ip->Type<=ITEM_WING+6 )
#endif	// ADD_ALICE_WINGS_1
    {
        if ( excelWing&0x01 )           //  �ִ� HP+50����.
        {
			ip->SpecialValue[ip->SpecialNum] = 50+Level*5;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_HP_MAX;ip->SpecialNum++;
        }
        if ( (excelWing>>1)&0x01 )      //  �ִ� MP+50����.
        {
			ip->SpecialValue[ip->SpecialNum] = 50+Level*5;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_MP_MAX;ip->SpecialNum++;
        }
        if ( (excelWing>>2)&0x01 )      //  3% Ȯ���� ���� ���� ���� ����.     ???  ������ HP -> MP�� �ս�.
        {
			ip->SpecialValue[ip->SpecialNum] = 3;
			ip->Special[ip->SpecialNum] = AT_ONE_PERCENT_DAMAGE;ip->SpecialNum++;
        }
        //  ������� �ʴ� �ڵ�.
        if ( (excelWing>>3)&0x01 )      //  AG ����.
        {
			ip->SpecialValue[ip->SpecialNum] = 50;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_AG_MAX;ip->SpecialNum++;
        }
        if ( (excelWing>>4)&0x01 )      //  ���ݼӵ� ����.
        {
			ip->SpecialValue[ip->SpecialNum] = 5;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
        }
    }
    else if ( ip->Type==ITEM_HELPER+30 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| ip->Type==ITEM_WING+49
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)        //  ������ ����.
    {
#ifndef PBG_MOD_NEWCHAR_MONK_WING_2			//�����ҽÿ� ������ �ҽ�
		/////////////////////////////////////////////////////////////////////
		// ���� ���� �����Ǹ���/������ ���並 �ٸ� ���� ó�� �ɼ��� ���� �ϰ�
		// �������� ��ġ�� �����Ѵ�- ��ȹ�ǵ�
		/////////////////////////////////////////////////////////////////////
        //  ���� ����.
		int Cal = 0;
		if(Level <= 9)
			Cal = Level;
		else
			Cal = 9;
		ip->SpecialValue[ip->SpecialNum] = 15+Cal*2;
		switch(Level - 9)
		{
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 6: ip->SpecialValue[ip->SpecialNum] += 9;	// +15 ������
		case 5: ip->SpecialValue[ip->SpecialNum] += 8;	// +14 ������
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
		case 4: ip->SpecialValue[ip->SpecialNum] += 7;	// +13 ������
		case 3: ip->SpecialValue[ip->SpecialNum] += 6;	// +12 ������
		case 2: ip->SpecialValue[ip->SpecialNum] += 5;	// +11 ������
		case 1: ip->SpecialValue[ip->SpecialNum] += 4;	// +10 ������
		default: break;
		};
#ifdef PBG_MOD_NEWCHAR_MONK_WING
		if(ip->Type!=ITEM_WING+49)
		{
#endif //PBG_MOD_NEWCHAR_MONK_WING
		ip->Special[ip->SpecialNum] = AT_SET_OPTION_IMPROVE_DEFENCE; ip->SpecialNum++;
#ifdef PBG_MOD_NEWCHAR_MONK_WING
		}
#endif //PBG_MOD_NEWCHAR_MONK_WING

        //  ������ ����.
		ip->SpecialValue[ip->SpecialNum] = 20+Level*2;
		ip->Special[ip->SpecialNum] = AT_SET_OPTION_IMPROVE_DAMAGE; ip->SpecialNum++;
#endif //PBG_MOD_NEWCHAR_MONK_WING_2			//�����ҽÿ� ������ �ҽ�
        if ( excelWing&0x01 )           //  �ִ� HP+50����.
        {
			ip->SpecialValue[ip->SpecialNum] = 50+Level*5;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_HP_MAX;ip->SpecialNum++;
        }
        
        if ( (excelWing>>1)&0x01 )      //  �ִ� MP+50����.
        {
			ip->SpecialValue[ip->SpecialNum] = 50+Level*5;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_MP_MAX;ip->SpecialNum++;
        }
        
        if ( (excelWing>>2)&0x01 )      //  1% Ȯ���� ���� ���� ���� ����.     ???  ������ HP -> MP�� �ս�.
        {
			ip->SpecialValue[ip->SpecialNum] = 3;
			ip->Special[ip->SpecialNum] = AT_ONE_PERCENT_DAMAGE;ip->SpecialNum++;
        }
        
        if ( (excelWing>>3)&0x01 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			&& (ip->Type != ITEM_WING+49)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)      //  ��� ����.
        {
		    ip->SpecialValue[ip->SpecialNum] = 10+Level*5;
		    ip->Special[ip->SpecialNum] = AT_SET_OPTION_IMPROVE_CHARISMA; ip->SpecialNum++;
        }
    }
#ifdef ADD_ALICE_WINGS_1
	else if ((ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40) || ip->Type == ITEM_WING+43
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| (ip->Type == ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)	// 3�� ����
#else	// ADD_ALICE_WINGS_1
	else if ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )	// 3�� ����
#endif	// ADD_ALICE_WINGS_1
    {
        if ( excelWing&0x01 )           //  %5 Ȯ���� �� ���� ����
        {
			ip->SpecialValue[ip->SpecialNum] = 5;
			ip->Special[ip->SpecialNum] = AT_ONE_PERCENT_DAMAGE;ip->SpecialNum++;
        }
        if ( (excelWing>>1)&0x01 )      //  5% Ȯ���� �� ���ݷ� 50% ������
        {
			ip->SpecialValue[ip->SpecialNum] = 5;
			ip->Special[ip->SpecialNum] = AT_DAMAGE_REFLECTION;ip->SpecialNum++;
        }
        if ( (excelWing>>2)&0x01 )      //  5% Ȯ���� ���� ���� 100% ���� ȸ��
        {
			ip->SpecialValue[ip->SpecialNum] = 5;
			ip->Special[ip->SpecialNum] = AT_RECOVER_FULL_LIFE;ip->SpecialNum++;
        }
        if ( (excelWing>>3)&0x01 )      //  5% Ȯ���� ���� ���� 100% ���� ȸ��
        {
			ip->SpecialValue[ip->SpecialNum] = 5;
			ip->Special[ip->SpecialNum] = AT_RECOVER_FULL_MANA;ip->SpecialNum++;
        }
    }
	//�ɼ�1(��ų) 1/6
	if((Attribute1>>7)&1)
	{        
        //  ��ų ����.
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		if ( p->m_wSkillIndex!=0 )
#else //PBG_ADD_NEWCHAR_MONK_SKILL
        if ( p->m_bySkillIndex!=0 )
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
        {
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			ip->Special[ip->SpecialNum] = p->m_wSkillIndex; ip->SpecialNum++;
#else //PBG_ADD_NEWCHAR_MONK_SKILL
            ip->Special[ip->SpecialNum] = p->m_bySkillIndex; ip->SpecialNum++;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
        }
    }
	//�ɼ�2(���) 1/10
	if((Attribute1>>2)&1)
	{
		if(ip->Type>=ITEM_SWORD && ip->Type<ITEM_BOOTS+MAX_ITEM_INDEX)
		{
			if(ip->Type!=ITEM_BOW+7 && ip->Type!=ITEM_BOW+15)
			{
     			ip->Special[ip->SpecialNum] = AT_LUCK;ip->SpecialNum++;
			}
		}
#ifdef ADD_ALICE_WINGS_1
		if ((ip->Type>=ITEM_WING && ip->Type<=ITEM_WING+6) || (ip->Type>=ITEM_WING+41 && ip->Type<=ITEM_WING+42))
#else	// ADD_ALICE_WINGS_1
		if(ip->Type>=ITEM_WING && ip->Type<=ITEM_WING+6)
#endif	// ADD_ALICE_WINGS_1
		{
   			ip->Special[ip->SpecialNum] = AT_LUCK;ip->SpecialNum++;
		}
        if ( ip->Type==ITEM_HELPER+30 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| ip->Type==ITEM_WING+49
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			) //  ������ ����.
        {
   			ip->Special[ip->SpecialNum] = AT_LUCK;ip->SpecialNum++;
        }
#ifdef ADD_ALICE_WINGS_1
		if (( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40) || ip->Type==ITEM_WING+43
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| (ip->Type==ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)	// 3�� ����
#else	// ADD_ALICE_WINGS_1
		if ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )	// 3�� ����
#endif	// ADD_ALICE_WINGS_1
        {
   			ip->Special[ip->SpecialNum] = AT_LUCK;ip->SpecialNum++;
        }
	}
	//�ɼ�3(�߰�����Ʈ) 1/8 1/10 1/14
	int Option3 = ((Attribute1)&3) + ((Attribute2)&64)/64*4;
	if(Option3)
	{
        //  ����Ʈ.
        if ( ip->Type==ITEM_HELPER+3 )
        {
            if ( Option3&0x01 )         //  �߰� ������ ���.
            {
				ip->SpecialValue[ip->SpecialNum] = 5;
				ip->Special[ip->SpecialNum] = AT_DAMAGE_ABSORB;ip->SpecialNum++;
            }
            if ( (Option3>>1)&0x01 )    //  �ִ� AG +50 ����.
            {
				ip->SpecialValue[ip->SpecialNum] = 50;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_AG_MAX;ip->SpecialNum++;
            }
            if ( (Option3>>2)&0x01 )    //  ���� �ӵ� 5 ����.
            {
   			    ip->SpecialValue[ip->SpecialNum] = 5;
			    ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
            }
        }
        else
        {
	        if(ip->Type>=ITEM_SWORD && ip->Type<ITEM_BOW+MAX_ITEM_INDEX)
		    {
			    if(ip->Type!=ITEM_BOW+7 && ip->Type!=ITEM_BOW+15)
			    {
				    ip->SpecialValue[ip->SpecialNum] = Option3*4;
				    ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				    ip->RequireStrength += Option3*5;
			    }
		    }
			if(ip->Type>=ITEM_STAFF && ip->Type<ITEM_STAFF+MAX_ITEM_INDEX)
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3*4;
				if (ip->Type>=ITEM_STAFF+21 && ip->Type<=ITEM_STAFF+29)	// ��ȯ���� ��ȯ��å.
					ip->Special[ip->SpecialNum] = AT_IMPROVE_CURSE;
				else
					ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;
				ip->SpecialNum++;
                ip->RequireStrength += Option3*5;
		    }
		    if(ip->Type>=ITEM_SHIELD && ip->Type<ITEM_SHIELD+MAX_ITEM_INDEX)
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3*5;
			    ip->Special[ip->SpecialNum] = AT_IMPROVE_BLOCKING;ip->SpecialNum++;
			    ip->RequireStrength += Option3*5;
		    }
		    if(ip->Type>=ITEM_HELM && ip->Type<ITEM_BOOTS+MAX_ITEM_INDEX)
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3*4;
			    ip->Special[ip->SpecialNum] = AT_IMPROVE_DEFENSE;ip->SpecialNum++;
			    ip->RequireStrength += Option3*5;
		    }
		    if(ip->Type>=ITEM_HELPER+8 && ip->Type<ITEM_HELPER+MAX_ITEM_INDEX && ip->Type!=ITEM_HELPER+30 )//����,�����
		    {
                if ( ip->Type==ITEM_HELPER+24 )    //  �������� ����.
                {
                    ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAX_MANA;ip->SpecialNum++;
                }
                else if ( ip->Type==ITEM_HELPER+28 )    //  ����� �����.
                {
                    ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAX_AG;ip->SpecialNum++;
                }
                else
                {
                    ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
                }
            }
	        if(ip->Type==ITEM_WING)//����
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3;
			    ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
		    }
#ifdef ADD_ALICE_WINGS_1
			else if (ip->Type==ITEM_WING+1 || ip->Type==ITEM_WING+41)	//õ��, ����ǳ���
#else	// ADD_ALICE_WINGS_1
			else if(ip->Type==ITEM_WING+1)//õ��
#endif	// ADD_ALICE_WINGS_1
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3*4;
			    ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
		    }
            else if(ip->Type==ITEM_WING+2)//��ź
		    {
			    ip->SpecialValue[ip->SpecialNum] = Option3*4;
			    ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
		    }
            else if ( ip->Type==ITEM_WING+3 )   //  ������ ����.
            {
                if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
                }
                else
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3*4;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
                }
            }
            else if ( ip->Type==ITEM_WING+4 )   //  ������ ����.
            {
                if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3*4;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
                }
                else
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
                }
            }
            else if ( ip->Type==ITEM_WING+5 )   //  ������ ����.
            {
                if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3*4;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
                }
                else
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
                }
            }
            else if ( ip->Type==ITEM_WING+6 )   //  ������ ����.
            {
                if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3*4;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
                }
                else
                {
			        ip->SpecialValue[ip->SpecialNum] = Option3*4;
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
                }
            }
            else if ( ip->Type==ITEM_HELPER+30 ) //  ������ ����.
			{
				ip->SpecialValue[ip->SpecialNum] = Option3*4;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
			}
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			else if(ip->Type==ITEM_WING+49)
			{
				if((excelWing>>5)&0x01)
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				}
				else
				{
					ip->SpecialValue[ip->SpecialNum] = Option3;
					ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
#ifdef ADD_ALICE_WINGS_1
			else if (ip->Type == ITEM_WING+42)	// �����ǳ���.
			{
				ip->SpecialValue[ip->SpecialNum] = Option3*4;
				if ((excelWing>>5)&0x01)    //  �׼���Ʈ�� ?��° bit�� ���϶�.
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;
                else
			        ip->Special[ip->SpecialNum] = AT_IMPROVE_CURSE;
				ip->SpecialNum++;
			}
#endif	// ADD_ALICE_WINGS_1
			else if ( ip->Type==ITEM_WING+36 )   //  ��ǳ�� ����
			{
				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DEFENSE;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
			else if ( ip->Type==ITEM_WING+37 )   //  �ð��� ����
			{
				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DEFENSE;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
			else if ( ip->Type==ITEM_WING+38 )   //  ȯ���� ����
			{
				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DEFENSE;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
			else if ( ip->Type==ITEM_WING+39 )   //  �ĸ��� ����
			{
				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
			else if ( ip->Type==ITEM_WING+40 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
				|| (ip->Type==ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
				) //  ������ ����
			{
 				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_DEFENSE;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
#ifdef ADD_ALICE_WINGS_2
			else if (ip->Type == ITEM_WING+43)	// ������ ����
			{
 				if ( (excelWing>>4)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC;ip->SpecialNum++;
				}
				else if ( (excelWing>>5)&0x01 )    //  �׼���Ʈ�� ?��° bit�� ���϶�.
				{
					ip->SpecialValue[ip->SpecialNum] = Option3*4;
					ip->Special[ip->SpecialNum] = AT_IMPROVE_CURSE;ip->SpecialNum++;
				}
				else
				{
			        ip->SpecialValue[ip->SpecialNum] = Option3;
			        ip->Special[ip->SpecialNum] = AT_LIFE_REGENERATION;ip->SpecialNum++;
				}
			}
#endif	// ADD_ALICE_WINGS_2
        }
    }
    if ( ip->Type==ITEM_HELPER+4 ) //  ��ũȣ��.
    {
        //  ��ũȣ�� �ɼ� ����.
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
        giPetManager::SetPetItemConvert( ip, giPetManager::GetPetInfo(ip) );
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
        giPetManager::ItemConvert ( ip );
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
    }

    //  ��� ����.
	if((ip->Type>=ITEM_SHIELD && ip->Type<ITEM_BOOTS+MAX_ITEM_INDEX) ||//��
	    (ip->Type>=ITEM_HELPER+8 && ip->Type<=ITEM_HELPER+9)
       || (ip->Type>=ITEM_HELPER+21 && ip->Type<=ITEM_HELPER+24))       //  �߰� ����.
	{
      	//��������
		if((Attribute2>>5)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_LIFE;ip->SpecialNum++;
		}	
		//��������
		if((Attribute2>>4)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_MANA;ip->SpecialNum++;
		}	
		//����������
		if((Attribute2>>3)&1)
		{
			ip->Special[ip->SpecialNum] = AT_DECREASE_DAMAGE;ip->SpecialNum++;
		}	
		//�������ݻ�
		if((Attribute2>>2)&1)
		{
			ip->Special[ip->SpecialNum] = AT_REFLECTION_DAMAGE;ip->SpecialNum++;
		}	
		//������
		if((Attribute2>>1)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_BLOCKING_PERCENT;ip->SpecialNum++;
		}	
		//ȹ��������
		if((Attribute2)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_GAIN_GOLD;ip->SpecialNum++;
		}	
	}
    //  ���ݷ� ����.
	if((ip->Type>=ITEM_SWORD && ip->Type<ITEM_STAFF+MAX_ITEM_INDEX) ||  //  ����.
       (ip->Type>=ITEM_HELPER+12 && ip->Type<=ITEM_HELPER+13)           //  �����.
       || (ip->Type>=ITEM_HELPER+25 && ip->Type<=ITEM_HELPER+28))       //  �߰� �����
	{
      	//������뷮����
		if((Attribute2>>5)&1)
		{
			ip->Special[ip->SpecialNum] = AT_EXCELLENT_DAMAGE;ip->SpecialNum++;
		}	
		if ( (ip->Type>=ITEM_STAFF && ip->Type<ITEM_STAFF+MAX_ITEM_INDEX) ||//������
			 (ip->Type==ITEM_HELPER+12)
           || ( ip->Type==ITEM_HELPER+25 || ip->Type==ITEM_HELPER+27 ))     //  �߰� �����.
		{
			//��������(����)
			if((Attribute2>>4)&1)
			{
     			ip->SpecialValue[ip->SpecialNum] = CharacterAttribute->Level/20;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC_LEVEL;ip->SpecialNum++;
			}	
			//��������(�ۼ�Ʈ)
			if((Attribute2>>3)&1)
			{
		   		ip->SpecialValue[ip->SpecialNum] = 2;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC_PERCENT;ip->SpecialNum++;
			}	
		}
		else
		{
			//���ݷ�����(����)
			if((Attribute2>>4)&1)
			{
     			ip->SpecialValue[ip->SpecialNum] = CharacterAttribute->Level/20;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE_LEVEL;ip->SpecialNum++;
			}	
			//���ݷ�����(�ۼ�Ʈ)
			if((Attribute2>>3)&1)
			{
		   		ip->SpecialValue[ip->SpecialNum] = 2;
				ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE_PERCENT;ip->SpecialNum++;
			}	
		}
		//���ݼӵ�
		if((Attribute2>>2)&1)
		{
   			ip->SpecialValue[ip->SpecialNum] = 7;
			ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
		}	
		//ȹ���������
		if((Attribute2>>1)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_GAIN_LIFE;ip->SpecialNum++;
		}	
		//ȹ�渶������
		if((Attribute2)&1)
		{
			ip->Special[ip->SpecialNum] = AT_IMPROVE_GAIN_MANA;ip->SpecialNum++;
		}	
	}
 	if (ip->Type == ITEM_HELPER+20 )
	{
        switch ( Level )
        {
        case 0:
            // �������� ���� �ɼ�
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC_PERCENT;ip->SpecialNum++;
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE_PERCENT;ip->SpecialNum++;
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
            break;

        case 3:
            // �������� ���� �ɼ�
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC_PERCENT;ip->SpecialNum++;
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE_PERCENT;ip->SpecialNum++;
            ip->SpecialValue[ip->SpecialNum] = 10;
            ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
            break;
        }
	}
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
	if(ip->Type == ITEM_HELPER+107)		// ġ��������
	{
        ip->SpecialValue[ip->SpecialNum] = 15;
        ip->Special[ip->SpecialNum] = AT_IMPROVE_MAGIC_PERCENT;ip->SpecialNum++;
        ip->SpecialValue[ip->SpecialNum] = 15;
        ip->Special[ip->SpecialNum] = AT_IMPROVE_DAMAGE_PERCENT;ip->SpecialNum++;
        ip->SpecialValue[ip->SpecialNum] = 10;
        ip->Special[ip->SpecialNum] = AT_IMPROVE_ATTACK_SPEED;ip->SpecialNum++;
	}
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING

	//part
	if(ip->Type>=ITEM_BOW && ip->Type<ITEM_BOW+8 || ip->Type==ITEM_BOW+17 )
		ip->Part = EQUIPMENT_WEAPON_LEFT;
	if(ip->Type>=ITEM_STAFF+21 && ip->Type<=ITEM_STAFF+29)
		ip->Part = EQUIPMENT_WEAPON_LEFT;
	else if(ip->Type>=ITEM_SWORD && ip->Type<ITEM_STAFF+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_WEAPON_RIGHT;
	else if(ip->Type>=ITEM_SHIELD && ip->Type<ITEM_SHIELD+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_WEAPON_LEFT;
	else if(ip->Type>=ITEM_HELM && ip->Type<ITEM_HELM+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_HELM;
	else if(ip->Type>=ITEM_ARMOR && ip->Type<ITEM_ARMOR+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_ARMOR;
	else if(ip->Type>=ITEM_PANTS && ip->Type<ITEM_PANTS+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_PANTS;
	else if(ip->Type>=ITEM_GLOVES && ip->Type<ITEM_GLOVES+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_GLOVES;
	else if(ip->Type>=ITEM_BOOTS && ip->Type<ITEM_BOOTS+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_BOOTS;
	else if(ip->Type>=ITEM_WING && ip->Type<ITEM_WING+7)
		ip->Part = EQUIPMENT_WING;
#ifdef ADD_ALICE_WINGS_1
	else if(ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+43)
#else	// ADD_ALICE_WINGS_1
	else if(ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40)
#endif	// ADD_ALICE_WINGS_1
		ip->Part = EQUIPMENT_WING;
#ifdef PET_SYSTEM
	else if(ip->Type==ITEM_HELPER+5)
		ip->Part = EQUIPMENT_WEAPON_LEFT;
#endif// PET_SYSTEM
#ifdef DARK_WOLF
    else if ( ip->Type==ITEM_HELPER+6 )
		ip->Part = EQUIPMENT_WEAPON_LEFT;
#endif// DARK_WOLF
	else if(ip->Type>=ITEM_HELPER && ip->Type<ITEM_HELPER+8)
		ip->Part = EQUIPMENT_HELPER;
    else if((ip->Type>=ITEM_HELPER+8 && ip->Type<ITEM_HELPER+12) || (ip->Type == ITEM_HELPER+20 && Level == 0)
		|| (ip->Type == ITEM_HELPER+20 && Level == 3)
		)
		ip->Part = EQUIPMENT_RING_RIGHT;
    else if( ip->Type>=ITEM_HELPER+21 && ip->Type<=ITEM_HELPER+24 )
		ip->Part = EQUIPMENT_RING_RIGHT;
    else if( ip->Type>=ITEM_HELPER+25 && ip->Type<=ITEM_HELPER+28 )
		ip->Part = EQUIPMENT_AMULET;
	else if(ip->Type>=ITEM_HELPER+12 && ip->Type<ITEM_HELPER+MAX_ITEM_INDEX)
		ip->Part = EQUIPMENT_AMULET;
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	else if(ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)
		ip->Part = EQUIPMENT_WING;
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
	else 
		ip->Part = -1;
}

//  ������ �ȱ�/��� ����.
int ItemValue(ITEM *ip,int goldType)
{
	if(ip->Type == -1) return 0;

	ITEM_ATTRIBUTE *p = &ItemAttribute[ip->Type];

	__int64 Gold = 0;

    //  ����, ���� ���� ����.
	if ( p->iZen!=0 )
	{
		Gold = p->iZen;
		
		if( goldType )  //  �ȱ�. ����.
		{
			Gold = Gold/3;
		}

		if(Gold >= 1000)
			Gold = Gold/100*100;
		else if(Gold >= 100)
			Gold = Gold/10*10;

		return (int)Gold;
	}
	
	int Type = ip->Type / MAX_ITEM_INDEX;
	int Level = (ip->Level>>3)&15;
	bool Excellent = false;
	for(int i=0;i<ip->SpecialNum;i++)
	{
		switch(ip->Special[i])
		{
		case AT_IMPROVE_LIFE:          
		case AT_IMPROVE_MANA:          
		case AT_DECREASE_DAMAGE:       
		case AT_REFLECTION_DAMAGE:   
		case AT_IMPROVE_BLOCKING_PERCENT:         
		case AT_IMPROVE_GAIN_GOLD:     
		case AT_EXCELLENT_DAMAGE:   
		case AT_IMPROVE_DAMAGE_LEVEL:  
		case AT_IMPROVE_DAMAGE_PERCENT:
		case AT_IMPROVE_MAGIC_LEVEL:   
		case AT_IMPROVE_MAGIC_PERCENT: 
		case AT_IMPROVE_ATTACK_SPEED:  
		case AT_IMPROVE_GAIN_LIFE:     
		case AT_IMPROVE_GAIN_MANA:     
			Excellent = true;
			break;
		}
	}
	int Level2 = p->Level+Level*3;
	if(Excellent)
		Level2 += 25;

	if(ip->Type==ITEM_BOW+7)        //  ���� ȭ��.
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int sellMoney = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        int sellMoney;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

        switch ( Level )
        {
        case    0 :
            sellMoney = 100;
            break;
        case    1 :
            sellMoney = 1400;
            break;
        case    2 :
            sellMoney = 2200;
            break;
#ifdef ASG_ADD_ELF_ARROW_PLUS3
		case    3 :
            sellMoney = 3000;
            break;
#endif	// ASG_ADD_ELF_ARROW_PLUS3
        }
		if(p->Durability > 0)
     		Gold = (sellMoney*ip->Durability/p->Durability);//+(170*(Level*2));
	}
	else if(ip->Type==ITEM_BOW+15)  //  ȭ��.
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		int sellMoney = 0;
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
        int sellMoney;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

        switch ( Level )
        {
        case    0 :
            sellMoney = 70;
            break;
        case    1 :
            sellMoney = 1200;
            break;
        case    2 :
            sellMoney = 2000;
            break;
#ifdef ASG_ADD_ELF_ARROW_PLUS3
		case    3 :
            sellMoney = 2800;
            break;
#endif	// ASG_ADD_ELF_ARROW_PLUS3
        }
		if(p->Durability > 0)
     		Gold = (sellMoney*ip->Durability/p->Durability);//+(80*(Level*2));
	}
	else if(COMGEM::isCompiledGem(ip))
	{
		Gold = COMGEM::CalcItemValue(ip);
	}
	else if(ip->Type==ITEM_POTION+13)//�ູ�� ����
	{
    	Gold = 9000000;
	}
	else if(ip->Type==ITEM_POTION+14)//������ ����
	{
    	Gold = 6000000;
	}
	else if(ip->Type==ITEM_WING+15)//ȥ���� ����
	{
    	Gold = 810000;
	}
    else if(ip->Type==ITEM_POTION+16)// ������ ����.
    {
        Gold = 45000000;
    }
    else if(ip->Type==ITEM_POTION+22)// â���� ����.
    {
        Gold = 36000000;
    }
#ifdef PBG_ADD_GENSRANKING
	else if(ip->Type == ITEM_POTION+141)	//�����º�����
	{
		Gold = 224000*3;
	}
	else if(ip->Type == ITEM_POTION+142)	//���õȺ�����
	{
		Gold = 182000*3;
	}
	else if(ip->Type == ITEM_POTION+143)	//ö��������
	{
		Gold = 157000*3;
	}
	else if(ip->Type == ITEM_POTION+144)	//����������
	{
		Gold = 121000*3;
	}
#endif //PBG_ADD_GENSRANKING

    else if(ip->Type==ITEM_HELPER+14)   //  ��ũ�� ����.
    {
        switch ( Level )
        {
        case 0: Gold = 180000;  break;  //  ��ũ�� ����.
        case 1: Gold = 7500000; break;  //  ������ ����.
        }
    }
	else if(ip->Type==ITEM_HELPER+3)	// ����Ʈ
	{
        Gold = 960000;
        for(int i=0;i<ip->SpecialNum;i++)
		{
			switch(ip->Special[i])
            {
			case AT_DAMAGE_ABSORB:  
            case AT_IMPROVE_AG_MAX:
            case AT_IMPROVE_ATTACK_SPEED:
				Gold += 300000;
				break;
            }
        }
	}
    else if(ip->Type==ITEM_HELPER+15)   //  ������Ʈ ��/�� ����.
    {
        Gold = 33000000;
    }
#ifdef KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
    else if ( ip->Type==ITEM_HELPER+16 || ip->Type==ITEM_HELPER+17 )    //  ��õ���� ��, ���� ��.
    {
        switch ( Level )
        {
        case 1: Gold = 10000; break;
        case 2: Gold = 50000; break;
        case 3: Gold = 100000; break;
        case 4: Gold = 300000; break;
        case 5: Gold = 500000; break;
        case 6: Gold = 800000; break;
		case 7: Gold = 1000000; break;
		case 8: Gold = 1200000; break;
		default:
			Gold = 0;
        }
	}
#else // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
    else if ( ip->Type==ITEM_HELPER+16 || ip->Type==ITEM_HELPER+17 )    //  ��õ���� ��, ���� ��.
    {
        switch ( Level )
        {
        case 1: Gold = 5000; break;
        case 2: Gold = 7000; break;
        case 3: Gold = 10000; break;
        case 4: Gold = 13000; break;
        case 5: Gold = 16000; break;
        case 6: Gold = 20000; break;
		case 7: Gold = 25000; break;
		case 8: Gold = 30000; break;
		default:
			Gold = 0;
        }
		Gold *= 3;   
	}
#endif // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
    else if ( ip->Type==ITEM_HELPER+18 )    //  �������.
    {
		Gold = 200000 + 20000 * ( Level - 1);
		if ( Level == 1)
		{
			Gold = 50000;
		}
        Gold *= 3;
    }
	else if ( ip->Type==ITEM_POTION+28 )    //  �о���� ����.
	{
		Gold = 200000*3;
	}
    else if ( ip->Type==ITEM_POTION+29 )    //  ����� ǥ��.
    {
        Gold = ( ip->Durability*10000 )*3;
    }
#ifdef YDG_ADD_DOPPELGANGER_ITEM
	else if ( ip->Type==ITEM_POTION+111 )    //  �����Ǹ���
	{
		Gold = 200000*3;
	}
    else if ( ip->Type==ITEM_POTION+110 )    //  ������ ǥ��
    {
        Gold = ( ip->Durability*10000 )*3;
    }
#endif	// YDG_ADD_DOPPELGANGER_ITEM
#ifdef LDK_ADD_EMPIREGUARDIAN_ITEM
	else if( ITEM_POTION+102 == ip->Type )
	{
		Gold = 10000*3;
	}
	else if( ITEM_POTION+109 == ip->Type )	//���̿��Ǹ�ɼ�, ��ũ�ι��� 
	{
		Gold = 10000*3;
	}
	else if( ITEM_POTION+101 == ip->Type || ITEM_POTION+103 <= ip->Type && ip->Type <= ITEM_POTION+108 )	//�ǹ�������, ��ũ�ι��� ����
	{
        Gold = ( ip->Durability*10000 )*3;
	}
#endif //LDK_ADD_EMPIREGUARDIAN_ITEM
#ifdef MYSTERY_BEAD
	else if ( ip->Type==ITEM_WING+26 )    //  �ź��Ǳ��� �ǸŰ���
	{
		if(Level == 0)
			Gold = 20000*3;
	}
#endif // MYSTERY_BEAD
    else if ( ip->Type==ITEM_HELPER+29 )    //  ��������Ʈ ( ī���� ĳ�� ���� ������ ).
    {
        Gold = 5000;
    }
#ifdef LENA_EXCHANGE_ZEN
    else if(ip->Type==ITEM_POTION+21)
	{	//. 0 : ����, 1 : ����, 2 : �����ǵ�, 3 : ������ǥ��
		if(Level == 0)
			Gold = 9000;
    }
#endif
#ifdef BLOODCASTLE_2ND_PATCH
	else if(ip->Type==ITEM_POTION+21)
	{	//. 0 : ����, 1 : ����, 2 : �����ǵ�, 3 : ������ǥ��
		if(Level == 0)
			Gold = 9000;
		else if(Level == 1)
			Gold = 9000;
#ifdef FRIENDLYSTONE_EXCHANGE_ZEN
		else if(Level == 2)
			Gold = 3000*3;
#endif // FRIENDLYSTONE_EXCHANGE_ZEN
		else if(Level == 3)
		{
			Gold = ip->Durability * 3900;
		}
	}
#endif // BLOODCASTLE_2ND_PATCH
#ifdef KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
	else if(ip->Type==ITEM_POTION+17)// �Ǹ��� ��
	{
		int iValue[8] = {30000, 10000, 50000, 100000, 300000, 500000, 800000, 1000000};
		Gold = iValue[min( max( 0, Level), 7)];
	}
	else if(ip->Type==ITEM_POTION+18)// �Ǹ��� ����
	{
		int iValue[8] = {30000, 15000, 75000, 150000, 450000, 750000, 1200000, 1500000};
		Gold = iValue[min( max( 0, Level), 7)];
	}
	else if(ip->Type==ITEM_POTION+19)// �������� �ʴ��
	{
		int iValue[8] = {120000, 60000, 84000, 120000, 180000, 240000, 300000, 180000};
		Gold = iValue[min( max( 0, Level), 7)];
	}
#else // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
	else if(ip->Type==ITEM_POTION+17)// �Ǹ��� ��
	{
		int iValue[7] = {30000, 15000, 21000, 30000, 45000, 60000, 75000};
		Gold = iValue[min( max( 0, Level), 6)];
	}
	else if(ip->Type==ITEM_POTION+18)// �Ǹ��� ����
	{
		int iValue[7] = {30000, 15000, 21000, 30000, 45000, 60000, 75000};
		Gold = iValue[min( max( 0, Level), 6)];
	}
	else if(ip->Type==ITEM_POTION+19)// �������� �ʴ��
	{
		int iValue[5] = { 120000, 60000, 84000, 120000, 180000};
		Gold = iValue[min( max( 0, Level), 4)];
	}
#endif // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
#ifdef KJH_FIX_20080910_NPCSHOP_PRICE
    else if (ip->Type==ITEM_HELPER+49 || ip->Type==ITEM_HELPER+50 || ip->Type==ITEM_HELPER+51)	// �����η縶��, ȯ�������Ǽ���, ���ǵη縶��
    {
        switch ( Level )
        {
        case 1: Gold = 500000; break;
        case 2: Gold = 600000; break;
        case 3: Gold = 800000; break;
        case 4: Gold = 1000000; break;
        case 5: Gold = 1200000; break;
        case 6: Gold = 1400000; break;
		default:
			Gold = 3000*3;
        }
	}
#endif // KJH_FIX_20080910_NPCSHOP_PRICE
	else if(ip->Type==ITEM_POTION+23 || ip->Type==ITEM_POTION+24 || ip->Type==ITEM_POTION+25 || ip->Type==ITEM_POTION+26
		|| ip->Type==ITEM_POTION+65 || ip->Type==ITEM_POTION+66 || ip->Type==ITEM_POTION+67 || ip->Type==ITEM_POTION+68
		)	// ���� ����Ʈ ������
	{
		Gold = 9000;
	}
	else if(ip->Type==ITEM_POTION+9 && Level == 1)// ����� �ø���
	{
		Gold = 1000;
	}
	else if(ip->Type==ITEM_POTION+20)	// ����� ����
	{
		Gold = 900;
	}
	else if(ip->Type == ITEM_POTION+51)	// ũ���������� ��
	{
		Gold = 200000;
	}
	else if(ip->Type == ITEM_POTION+63)	// ����
	{
		Gold = 200000;
	}
	else if(ip->Type == ITEM_POTION+52)	// GM ��������
	{
		Gold = 33*3;
	}
	else if(ip->Type==ITEM_POTION+10)	// �̵�����
	{
#ifdef _PVP_ADD_MOVE_SCROLL
		switch (Level)
		{
		case 0: Gold = 750; break;
		case 1: Gold = GetMoveReqZenFromMCB("Lorencia") * 0.9f; break;		//  �η��þ�
		case 2: Gold = GetMoveReqZenFromMCB("Noria") * 0.9f; break;		//  �븮��
		case 3: Gold = GetMoveReqZenFromMCB("Devias") * 0.9f; break;		//  ����ƽ�
		case 4: Gold = GetMoveReqZenFromMCB("Dungeon") * 0.9f; break;		//  ����
		case 5: Gold = GetMoveReqZenFromMCB("Atlans") * 0.9f; break;		//  ��Ʋ����
		case 6: Gold = GetMoveReqZenFromMCB("LostTower") * 0.9f; break;	//  �ν�ƮŸ��
		case 7: Gold = GetMoveReqZenFromMCB("Tarkan") * 0.9f; break;		//  Ÿ��ĭ
		case 8: Gold = GetMoveReqZenFromMCB("Icarus") * 0.9f; break;		//  ��ī�罺
		default: Gold = 750; break;
		};
#else	// _PVP_ADD_MOVE_SCROLL
		Gold = 750;
#endif	// _PVP_ADD_MOVE_SCROLL
	}
#ifdef _PVP_MURDERER_HERO_ITEM
	else if(ip->Type==ITEM_POTION+30)	// �������θ�¡ǥ
	{
		Gold = 3000;
	}
#endif	// _PVP_MURDERER_HERO_ITEM
    else if ( ip->Type==ITEM_POTION+31 )// ��ȣ�Ǻ���
    {
        Gold = 60000000;
    }
    else if ( ip->Type==ITEM_POTION+7 ) //  ���м� ����.//���ƹ���
    {
        switch ( Level )
        {
			//2100000
			//1500000
        case 0: Gold = 900000*ip->Durability; break;
        case 1: Gold = 450000*ip->Durability; break;
        }
    }
    else if ( ip->Type==ITEM_HELPER+7 ) //  �뺴.
    {
        switch ( Level )
        {
		case 0: Gold =  1500000; break;
        case 1: Gold =  1200000; break;		        
        }
    }
    else if ( ip->Type==ITEM_HELPER+11 )
    {
        switch ( Level )
        {
        case 0: Gold = 100000; break;
        case 1: Gold = 2400000; break;
        }
    }
	else if(ip->Type >= ITEM_POTION+35 && ip->Type <= ITEM_POTION+37)
	{
		switch(ip->Type)
		{
			case ITEM_POTION+35:
				Gold = 2000;
				break;
			case ITEM_POTION+36:
				Gold = 4000;
				break;
			case ITEM_POTION+37:
				Gold = 6000;
				break;
		}
		Gold *= ip->Durability;
	}
	else if(ip->Type >= ITEM_POTION+38 && ip->Type <= ITEM_POTION+40)
	{
		switch(ip->Type)
		{
			case ITEM_POTION+38:
				Gold = 2500;
				break;
			case ITEM_POTION+39:
				Gold = 5000;
				break;
			case ITEM_POTION+40:
				Gold = 7500;
				break;
		}
		Gold *= ip->Durability;
	}
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	else if( ip->Type == ITEM_POTION+100 )
	{
		Gold = 100*3;
		Gold *= ip->Durability;
	}
#endif // KJH_PBG_ADD_SEVEN_EVENT_2008
#ifdef PBG_FIX_GOLD_CHERRYBLOSSOMTREE
	else if( ip->Type == ITEM_POTION+90  || ip->Type == ITEM_POTION+85 || ip->Type == ITEM_POTION+86 || ip->Type == ITEM_POTION+87)
	{
		Gold = 300;
		Gold *= ip->Durability;
	}
#endif //PBG_FIX_GOLD_CHERRYBLOSSOMTREE

	else if(p->Value > 0)
	{
		Gold = p->Value*p->Value*10/12;

#ifdef CSK_FIX_POTION_VALUE
		if(ip->Type == ITEM_POTION+3 || ip->Type == ITEM_POTION+6)	
		{
			// ūġ�Ṱ��, ū�������� ���� 1500���� �ϵ��ڵ����� �ٲ�޶�� ��
			// ��ũ��Ʈ�� value ���� �ٲٸ� ������ 1500 ���� ���÷��� �Ҽ����� ���� �ϵ��ڵ����� ��
			Gold = 1500;	
		}
#endif // CSK_FIX_POTION_VALUE

		if(ip->Type>=ITEM_POTION && ip->Type<=ITEM_POTION+8)	//����
		{
			if(Level > 0)
#ifdef KJW_FIX_CHINESE_POTION_PRICE
				Gold *= (__int64)pow((double)2,(double)Level);
#else // KJW_FIX_CHINESE_POTION_PRICE
	#ifdef CHINESE_PRICERISE
				Gold *= (__int64)pow((double)3,(double)Level);
	#else
				Gold *= (__int64)pow((double)2,(double)Level);
	#endif	// CHINESE_PRICERISE
#endif // KJW_FIX_CHINESE_POTION_PRICE

#ifdef KJH_FIX_POTION_PRICE
			Gold = Gold/10*10;
			Gold *= (__int64)ip->Durability;

			if( goldType )  //  �ȱ�. ����.
            {
				Gold = Gold/3;
				Gold = Gold/10*10;
            }
			return (int)Gold;
#else // KJH_FIX_POTION_PRICE
			Gold *= ip->Durability;
            if( goldType )  //  �ȱ�. ����.
            {
		        Gold = Gold/3;
            }
            Gold = Gold/10*10;
			return (int)Gold;
#endif // KJH_FIX_POTION_PRICE
		}
	}
	else if (ip->Type==ITEM_HELPER+20)	// �������� ����
	{
		if (Level == 0)
#ifdef LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
			Gold = 3000;
#else //LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
			Gold = 30000;
#endif //LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
		else if (Level == 1)
			Gold = 0;
	}
	else if (ip->Type==ITEM_HELPER+52 || ip->Type==ITEM_HELPER+53)	// �ܵ����� ����,�Ҳ�
	{
		Gold = 3000000;
	}
    else if ( ip->Type==ITEM_HELPER+31 )    //  ��ȥ.
    {
        switch ( Level )
        {
        case 0 : Gold = 10000000*3; break;    //  ��ũȣ��.
        case 1 : Gold = 5000000*3;  break;    //  ��ũ���Ǹ�.
        }
    }
	else if( ( ( Type==12 && (ip->Type>ITEM_WING+6
#ifdef ADD_ALICE_WINGS_1
		&& !(ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+43)
#else	// ADD_ALICE_WINGS_1
		&& !( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40)
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		&& (ip->Type!=ITEM_WING+50)
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		) ) || Type==13 || Type==15 ) )//12(����,����) 13(��ź,����) 15(����), ����Ʈ ����.
	{
		Gold = 100+Level2*Level2*Level2;
#ifdef _VS2008PORTING
		for(int i=0;i<ip->SpecialNum;i++)
#else // _VS2008PORTING
		for(i=0;i<ip->SpecialNum;i++)
#endif // _VS2008PORTING
		{
			switch(ip->Special[i])
			{
			case AT_LIFE_REGENERATION:
				Gold += Gold*ip->SpecialValue[i];
				break;
			}
		}
	}
#ifdef YDG_FIX_LUCKY_CHARM_VALUE_TO_0
	else if (ip->Type == ITEM_POTION+53)	// ����Ǻ���
	{
		Gold = 0;
	}
#endif	// YDG_FIX_LUCKY_CHARM_VALUE_TO_0
	else
	{
        switch(Level)     //+�����ϼ��� ����ġ ����
        {
        case 5:Level2 += 4;break;
        case 6:Level2 += 10;break;
        case 7:Level2 += 25;break;
        case 8:Level2 += 45;break;
        case 9:Level2 += 65;break;
        case 10:Level2 += 95;break;	// +10
        case 11:Level2 += 135;break;
        case 12:Level2 += 185;break;
        case 13:Level2 += 245;break;
#ifdef LDK_ADD_14_15_GRADE_ITEM_VALUE
		// ������ 14 15 �Ǹűݾ� �߰�
        case 14:Level2 += 305;break;
        case 15:Level2 += 365;break; // �Ѱ� ����ġ ���̻� ���ø�
#endif //LDK_ADD_14_15_GRADE_ITEM_VALUE
        }
        //  ����, ����.
	    if( ( Type==12 && ip->Type<=ITEM_WING+6) || ip->Type==ITEM_HELPER+30 
#ifdef ADD_ALICE_WINGS_1
			|| (ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+43)	// 3������, ��ȯ���� ����.
#else	// ADD_ALICE_WINGS_1
			|| ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )	// 3������
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
			|| (ip->Type==ITEM_WING+50)	// ������ ������ ����
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
			)
        {
            Gold = 40000000+((40+Level2)*Level2*Level2*11);
        }
        else
        {
		    Gold = 100+(40+Level2)*Level2*Level2/8;
        }
		if(Type>=0 && Type<=6) //�����϶�
		{
			if(!p->TwoHand) //�Ѽչ����϶� 80%
				Gold = Gold*80/100;
		}
		for(int i=0;i<ip->SpecialNum;i++)
		{
			switch(ip->Special[i])
			{
			case AT_SKILL_BLOCKING:
			case AT_SKILL_SWORD1:
			case AT_SKILL_SWORD2:
			case AT_SKILL_SWORD3:
			case AT_SKILL_SWORD4:
			case AT_SKILL_SWORD5:
			case AT_SKILL_MANY_ARROW_UP:
			case AT_SKILL_MANY_ARROW_UP+1:
			case AT_SKILL_MANY_ARROW_UP+2:
			case AT_SKILL_MANY_ARROW_UP+3:
			case AT_SKILL_MANY_ARROW_UP+4:
			case AT_SKILL_CROSSBOW:
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			case AT_SKILL_RECOVER:
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
#ifdef PJH_SEASON4_DARK_NEW_SKILL_CAOTIC
			case AT_SKILL_GAOTIC:
#endif //PJH_SEASON4_DARK_NEW_SKILL_CAOTIC			case AT_SKILL_BLAST_POISON:
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
			case AT_SKILL_MULTI_SHOT:
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_MULTI_SHOT
#ifdef PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_POWER_SLASH_UP:
			case AT_SKILL_POWER_SLASH_UP+1:
			case AT_SKILL_POWER_SLASH_UP+2:
			case AT_SKILL_POWER_SLASH_UP+3:
			case AT_SKILL_POWER_SLASH_UP+4:
#endif //PJH_SEASON4_MASTER_RANK4
			case AT_SKILL_ICE_BLADE:
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
			case AT_SKILL_THRUST:
			case AT_SKILL_STAMP:
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
				Gold += ( DWORD)( ( float)Gold*1.5f);
				break;
			case AT_IMPROVE_DAMAGE:
			case AT_IMPROVE_MAGIC:
			case AT_IMPROVE_CURSE:
			case AT_IMPROVE_DEFENSE:
			case AT_LIFE_REGENERATION:
                if ( ( Type==12 && ip->Type<=ITEM_WING+6 )
#ifdef ADD_ALICE_WINGS_1
					|| (ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+43)	// 3������, ��ȯ���� ����.
#else	// ADD_ALICE_WINGS_1
					|| ( ip->Type>=ITEM_WING+36 && ip->Type<=ITEM_WING+40 )	// 3������
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
					|| (ip->Type>=ITEM_WING+49 && ip->Type<=ITEM_WING+50)	// �����������ͳ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
					)    //  ����.
                {
					int iOption = ip->SpecialValue[i];
					if ( AT_LIFE_REGENERATION == ip->Special[i])
					{
						iOption *= 4;
					}
				    switch(iOption)
				    {
				    case 4 :Gold += ( __int64)( ( double)Gold* 6/10);break;
				    case 8 :Gold += ( __int64)( ( double)Gold*14/10);break;
				    case 12:Gold += ( __int64)( ( double)Gold*28/10);break;
				    case 16:Gold += ( __int64)( ( double)Gold*56/10);break;
				    }
                }
                else
                {
				    switch(ip->SpecialValue[i])
				    {
				    case 4 :Gold += ( __int64)( ( double)Gold* 6/10);break;
				    case 8 :Gold += ( __int64)( ( double)Gold*14/10);break;
				    case 12:Gold += ( __int64)( ( double)Gold*28/10);break;
				    case 16:Gold += ( __int64)( ( double)Gold*56/10);break;
				    }
                }
				break;
			case AT_IMPROVE_BLOCKING:
				switch(ip->SpecialValue[i])
				{
				case 5 :Gold += ( __int64)( ( double)Gold* 6/10);break;
				case 10:Gold += ( __int64)( ( double)Gold*14/10);break;
				case 15:Gold += ( __int64)( ( double)Gold*28/10);break;
				case 20:Gold += ( __int64)( ( double)Gold*56/10);break;
				}
				break;
			case AT_LUCK:
				Gold += ( __int64)( ( double)Gold*25/100);
				break;
			case AT_IMPROVE_LIFE:          
			case AT_IMPROVE_MANA:          
			case AT_DECREASE_DAMAGE:       
			case AT_REFLECTION_DAMAGE:     
			case AT_IMPROVE_BLOCKING_PERCENT:         
			case AT_IMPROVE_GAIN_GOLD:     
			case AT_EXCELLENT_DAMAGE:   
			case AT_IMPROVE_DAMAGE_LEVEL:  
			case AT_IMPROVE_DAMAGE_PERCENT:
			case AT_IMPROVE_MAGIC_LEVEL:   
			case AT_IMPROVE_MAGIC_PERCENT: 
			case AT_IMPROVE_GAIN_LIFE:     
			case AT_IMPROVE_GAIN_MANA:     
			case AT_IMPROVE_ATTACK_SPEED:  
				Gold += Gold;
				break;

                //  ����Ʈ.
            case AT_IMPROVE_EVADE:
				Gold += Gold;
				break;

                //  �߰� ����.
            case AT_IMPROVE_HP_MAX :
            case AT_IMPROVE_MP_MAX :
            case AT_ONE_PERCENT_DAMAGE :  
            case AT_IMPROVE_AG_MAX :
            case AT_DAMAGE_ABSORB : 
			case AT_DAMAGE_REFLECTION:	// [����� ������ �������� ������ ���] 5% Ȯ���� �� ���ݷ� 50% ������
			case AT_RECOVER_FULL_LIFE:	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��
			case AT_RECOVER_FULL_MANA:	// [����� ������ �������� ������ ���] 5% Ȯ���� ���� ���� 100% ���� ȸ��
				Gold += ( __int64)( ( double)Gold*25/100);
                break;
			}
		}
#ifdef SOCKET_SYSTEM
		// ���� ������ ���� ���ʽ�
		Gold += g_SocketItemMgr.CalcSocketBonusItemValue(ip, Gold);
#endif	// SOCKET_SYSTEM
	}
	Gold = min(Gold,3000000000);

#ifdef YDG_FIX_REPAIR_COST_ADJUST_TO_SERVER_SETTING
	if (goldType == 2)	// ���� ���İ� �°� �����ÿ��� ���ڸ� ������ ���
	{
		if(Gold >= 1000)
		{
			Gold = (Gold / 100) * 100;
		}
		else if(Gold >= 100)
		{
			Gold = (Gold / 10) * 10;
		}
	}
#endif	// YDG_FIX_REPAIR_COST_ADJUST_TO_SERVER_SETTING

	if( goldType )  //  �ȱ�. ����.
	{
		Gold = Gold/3;
	}

	//^ �渱 ������ ���� �Ǹ� ����(/3 ���ϱ� ���ؼ� �̰��� ��ġ)
	if(ip->Type == ITEM_HELPER+32)	// ���� ����(������ ����*����)
		Gold = ip->Durability*50;
	else if(ip->Type == ITEM_HELPER+33)	// ������ ��ȣ
		Gold = ip->Durability*100;
	else if(ip->Type == ITEM_HELPER+34)	// �ͼ��� ����
		Gold = ip->Durability*1000;
	else if(ip->Type == ITEM_HELPER+35)	// ���Ǹ� ����
		Gold = ip->Durability*10000;
	else if(ip->Type == ITEM_HELPER+36)	// �η��� ���Ǹ�
		Gold = 30000;
	else if(ip->Type == ITEM_HELPER+37)	// �渱�� ���Ǹ�
		Gold = 50000;
#ifndef KJH_FIX_20080910_NPCSHOP_PRICE		// #ifndef		������ �� ������ �ϴ� �ҽ�
#ifdef KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
    else if (ip->Type==ITEM_HELPER+49 || ip->Type==ITEM_HELPER+50 || ip->Type==ITEM_HELPER+51)	// �����η縶��, ȯ�������Ǽ���, ���ǵη縶��
    {
        switch ( Level )
        {
        case 1: Gold = 500000; break;
        case 2: Gold = 600000; break;
        case 3: Gold = 800000; break;
        case 4: Gold = 1000000; break;
        case 5: Gold = 1200000; break;
        case 6: Gold = 1400000; break;
		default:
			Gold = 3000*3;
        }
	}
#else // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
	else if (ip->Type==ITEM_HELPER+49 || ip->Type==ITEM_HELPER+50 || ip->Type==ITEM_HELPER+51)	// �����η縶��,ȯ�������Ǽ���,���ǵη縶��
	{
		Gold = 3000;
	}
#endif // KJH_FIX_WOPS_K26602_NPCSHOP_ITEM_PRICE_AS_MASTERLEVEL
#endif // KJH_FIX_20080910_NPCSHOP_PRICE		// #ifndef		������ �� ������ �ϴ� �ҽ�

#ifndef KJH_DEL_PC_ROOM_SYSTEM		// #ifndef
#ifdef ADD_PCROOM_POINT_SYSTEM
	// PC�� ����Ʈ �����ΰ�?
	if (CPCRoomPtSys::Instance().IsPCRoomPointShopMode())
	{
		switch(ip->Type)
		{
#ifdef ADD_EVENT_PCROOM_POINT_HALF
			
	#ifdef CSK_LUCKY_SEAL	// �ؿܿ� Ʋ��.
		case ITEM_HELPER+43:
			Gold = 12;
			break;
		case ITEM_HELPER+44:
			Gold = 18;
			break;
		case ITEM_HELPER+45:
			Gold = 12;
			break;
	#endif	//  CSK_LUCKY_SEAL
	#ifdef CSK_PCROOM_ITEM
		case ITEM_POTION+55:
			Gold = 12;
			break;
		case ITEM_POTION+56:
			Gold = 18;
			break;
		case ITEM_POTION+57:
			Gold = 24;
			break;
	#endif // CSK_PCROOM_ITEM
	#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		case ITEM_HELPER+96:		// ������ ����
			Gold = 16;
			break;
	#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
			
#else	// ADD_EVENT_PCROOM_POINT_HALF
			
	#ifdef ASG_PCROOM_POINT_SYSTEM_MODIFY
			
	  #ifdef CSK_LUCKY_SEAL	// �ؿܿ� Ʋ��.
		case ITEM_HELPER+43:
			Gold = 6;
			break;
		case ITEM_HELPER+44:
			Gold = 9;
			break;
		case ITEM_HELPER+45:
			Gold = 15;
			break;
	  #endif	//  CSK_LUCKY_SEAL
	  #ifdef CSK_PCROOM_ITEM
		case ITEM_POTION+55:
			Gold = 9;
			break;
		case ITEM_POTION+56:
			Gold = 15;
			break;
		case ITEM_POTION+57:
			Gold = 30;
			break;
	  #endif // CSK_PCROOM_ITEM
	  #ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		case ITEM_HELPER+96:		// ������ ����
			Gold = 32;
			break;
	  #endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
			
	#else	// ASG_PCROOM_POINT_SYSTEM_MODIFY	
	  #ifdef CSK_LUCKY_SEAL	// �ؿܿ� Ʋ��.
		case ITEM_HELPER+43:
			Gold = 24;
			break;
		case ITEM_HELPER+44:
			Gold = 36;
			break;
		case ITEM_HELPER+45:
			Gold = 24;
			break;
	  #endif	//  CSK_LUCKY_SEAL
	  #ifdef CSK_PCROOM_ITEM
		case ITEM_POTION+55:
			Gold = 24;
			break;
		case ITEM_POTION+56:
			Gold = 36;
			break;
		case ITEM_POTION+57:
			Gold = 48;
			break;
	  #endif // CSK_PCROOM_ITEM
	  #ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
		case ITEM_HELPER+96:		// ������ ����
			Gold = 32;
			break;
	  #endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
	
	#endif	// ASG_PCROOM_POINT_SYSTEM_MODIFY
#endif	// ADD_EVENT_PCROOM_POINT_HALF
		}
	}
	else	// PC�� ����Ʈ ������ �ƴ�.
	{
		switch(ip->Type)
		{
#ifdef CSK_PCROOM_ITEM
		case ITEM_POTION+55:
		case ITEM_POTION+56:
		case ITEM_POTION+57:
			Gold = 3000;	// �Ϲ� �������� �� ���� ����.
			break;
#endif // CSK_PCROOM_ITEM
		}
	}
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif // KJH_DEL_PC_ROOM_SYSTEM

#ifdef HELLOWIN_EVENT
	if(ip->Type >= ITEM_POTION+45 && ip->Type <= ITEM_POTION+50)
	{
		Gold = ip->Durability*50;
	}
#endif // HELLOWIN_EVENT

#ifdef ASG_ADD_TIME_LIMIT_QUEST_ITEM
	switch (ip->Type)
	{
	case ITEM_POTION+153:
	case ITEM_POTION+154:
	case ITEM_POTION+155:
	case ITEM_POTION+156:
		Gold = ip->Durability*1000;
		break;
	case ITEM_POTION+157:
	case ITEM_POTION+158:
	case ITEM_POTION+159:
		Gold = 10000;
		break;
	}
#endif	// ASG_ADD_TIME_LIMIT_QUEST_ITEM 
	
#ifdef LDK_ADD_GAMBLE_RANDOM_ICON
	if( ip->Type == ITEM_HELPER+71 || ip->Type == ITEM_HELPER+72 || ip->Type == ITEM_HELPER+73 || ip->Type == ITEM_HELPER+74 ||ip->Type == ITEM_HELPER+75 )	// �׺� ������
	{
#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		Gold = 2000000;
#else	// SELECTED_LANGUAGE == LANGUAGE_ENGLISH
#ifdef LDK_MOD_GAMBLE_SUMMER_SALE_EVENT
		Gold = 500000; // ���� �̺�Ʈ�� 50% ����
#else //LDK_MOD_GAMBLE_SUMMER_SALE_EVENT
		Gold = 1000000; //npc ���ο� ���� ������ ����
#endif //LDK_MOD_GAMBLE_SUMMER_SALE_EVENT
#endif	// SELECTED_LANGUAGE == LANGUAGE_ENGLISH
	}
#endif //LDK_ADD_GAMBLE_RANDOM_ICON
	
    //  ��ũȣ��, ��ũ���Ǹ��� /3�� ���� �ʴ´�.
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	if( (ip->Type == ITEM_HELPER+4) || (ip->Type == ITEM_HELPER+5) )
	{		
		PET_INFO* pPetInfo = giPetManager::GetPetInfo( ip );

		if( pPetInfo->m_dwPetType == PET_TYPE_NONE )
			return -1;

		Gold = giPetManager::GetPetItemValue( pPetInfo );
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
    switch ( ip->Type )
    {
    case ITEM_HELPER+4 :    //  ��ũȣ��.
        Gold = giPetManager::ItemValue ( PET_TYPE_DARK_HORSE );
        break;

    case ITEM_HELPER+5 :    //  ��ũ���Ǹ�.
        Gold = giPetManager::ItemValue ( PET_TYPE_DARK_SPIRIT );
        break;

#ifdef DARK_WOLF
    case ITEM_HELPER+6 :    //  ��ũ����.
        Gold = giPetManager::ItemValue ( PET_TYPE_DARK_WOLF );
        break;  
#endif// DARK_WOLF
	}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
 
#ifdef LDK_MOD_PREMIUMITEM_SELL
	switch(ip->Type)
	{
#ifdef LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
		//���� ���� ��
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
	case ITEM_POTION+112:
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
	case ITEM_POTION+113:
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	case ITEM_POTION+121:
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST	// ���ε� ��������
	case ITEM_POTION+122:
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST			// �ݻ�����
	case ITEM_POTION+123:
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST			// ��������
	case ITEM_POTION+124:
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef PJH_ADD_PANDA_PET
	case ITEM_HELPER+80:  //�����
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
	case ITEM_HELPER+76:  //������Ź���
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef LDK_ADD_PC4_GUARDIAN
	case ITEM_HELPER+64:  //���� ����
	case ITEM_HELPER+65:  //���� ��ȣ����
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE	// �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	case ITEM_HELPER+109:
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY		// �ű� ���(������)��		// MODEL_HELPER+110
	case ITEM_HELPER+110:
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ	// �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	case ITEM_HELPER+111:
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST	// �ű� �ڼ���(�����)��	// MODEL_HELPER+112
	case ITEM_HELPER+112:
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY	// �ű� ���(������) �����	// MODEL_HELPER+113
	case ITEM_HELPER+113:
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
	case ITEM_HELPER+114:
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
	case ITEM_HELPER+115:
		Gold = 1000;
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115		

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	case ITEM_HELPER+122:	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
	case ITEM_HELPER+123:	// ���̷��� ��
		Gold = 2000;
		break;
#endif //YDG_ADD_SKELETON_PET

#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	case ITEM_WING+130:
	case ITEM_WING+131:
	case ITEM_WING+132:
	case ITEM_WING+133:
	case ITEM_WING+134:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+135:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		Gold = 80;
		break;
#endif //LDK_ADD_INGAMESHOP_SMALL_WING

#else //LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
		//���� ���� ��
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
	case ITEM_POTION+112: Gold = 10000; break;
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
	case ITEM_POTION+113: Gold = 10000; break;
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	case ITEM_POTION+121:	Gold = 10000; break;
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST	// ���ε� ��������
	case ITEM_POTION+122:	Gold = 10000; break;
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST			// �ݻ�����
	case ITEM_POTION+123:	Gold = 10000; break;
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST			// ��������
	case ITEM_POTION+124:	Gold = 10000; break;
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	case ITEM_WING+130:
	case ITEM_WING+131:
	case ITEM_WING+132:
	case ITEM_WING+133:
	case ITEM_WING+134:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+135:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		Gold = 10000;
		break;
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef PJH_ADD_PANDA_PET
	case ITEM_HELPER+80:  //�����
		Gold = 10000;
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
	case ITEM_HELPER+76:  //������Ź���
		Gold = 10000;
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	case ITEM_HELPER+122:	// ���̷��� ���Ź���
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
	case ITEM_HELPER+123:	// ���̷��� ��
#endif //YDG_ADD_SKELETON_PET
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	case ITEM_HELPER+128:	// ��������
	case ITEM_HELPER+129:	// ��������
	case ITEM_HELPER+134:	// ����
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	case ITEM_HELPER+130:	// �ű� ��ũ��
	case ITEM_HELPER+131:	// �ű� ��������
	case ITEM_HELPER+132:	// �ű� ����ũ��
	case ITEM_HELPER+133:	// ����������
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2

#ifdef LDK_ADD_PC4_GUARDIAN
	case ITEM_HELPER+64:  //���� ����
	case ITEM_HELPER+65:  //���� ��ȣ����
		Gold = 10000;
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	case ITEM_HELPER+109:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
	case ITEM_HELPER+110:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	case ITEM_HELPER+111:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	case ITEM_HELPER+112:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
	case ITEM_HELPER+113:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
	case ITEM_HELPER+114:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
	case ITEM_HELPER+115:
		{
			Gold = 10000;
		}
		break;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115		
#endif //LDK_MOD_INGAMESHOP_ITEM_CHANGE_VALUE
	}
#endif //LDK_MOD_PREMIUMITEM_SELL

	// CSK��������
	// ������ �ȵǴ� ���ǵ��� ���⿡ ����ó�� ��. (goto EXIT_CALCULATE; �� ������)
    //  ������ �ʿ��� �������� �� ����� �� ������ ���� �ȸ��� �����̴�.
	//. item filtering
#ifdef CSK_PCROOM_ITEM
	if(ip->Type >= ITEM_POTION+55 && ip->Type <= ITEM_POTION+57)
	{
		goto EXIT_CALCULATE;
	}
#endif // CSK_PCROOM_ITEM
	
#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	if(ip->Type == ITEM_HELPER+96)
	{
		goto EXIT_CALCULATE;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH	

	if( ip->Type == ITEM_HELPER+10 || ip->Type == ITEM_HELPER+20 || ip->Type == ITEM_HELPER+29
#ifdef MYSTERY_BEAD
		|| ip->Type == ITEM_WING+26
#endif // MYSTERAY_BEAD
		)
		goto EXIT_CALCULATE;
	if( ip->Type == ITEM_BOW+7 || ip->Type == ITEM_BOW+15 || ip->Type >= ITEM_POTION )
		goto EXIT_CALCULATE;
	if( ip->Type >= ITEM_WING+7 && ip->Type <= ITEM_WING+19 )	//. ���� ���͸�
		goto EXIT_CALCULATE;
	if( (ip->Type >= ITEM_HELPER+14 && ip->Type <= ITEM_HELPER+19) || ip->Type==ITEM_POTION+21 )
		goto EXIT_CALCULATE;
	if( ip->Type==ITEM_POTION+7 || ip->Type==ITEM_HELPER+7 || ip->Type==ITEM_HELPER+11 )//���ƹ���
		goto EXIT_CALCULATE;
#ifdef KJH_FIX_20080910_NPCSHOP_PRICE
	if( (ip->Type>=ITEM_HELPER+49) && (ip->Type<=ITEM_HELPER+51))		// �����η縶��, ȯ�������Ǽ���, ���ǵη縶��
		goto EXIT_CALCULATE;
#endif // KJH_FIX_20080910_NPCSHOP_PRICE

#ifdef LDK_MOD_PREMIUMITEM_SELL
	switch(ip->Type)
	{
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYSILVER			// �ΰ��Ә� ������ // �ű� Ű(�ǹ�)				// MODEL_POTION+112
	case ITEM_POTION+112:	goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYSILVER
#ifdef LDS_ADD_INGAMESHOP_ITEM_KEYGOLD				// �ΰ��Ә� ������ // �ű� Ű(���)				// MODEL_POTION+113
	case ITEM_POTION+113:	goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_KEYGOLD
#ifdef LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST		// ���ε� �ݻ�����
	case ITEM_POTION+121:	goto EXIT_CALCULATE;
#endif //LDK_ADD_INGAMESHOP_LOCKED_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST	// ���ε� ��������
	case ITEM_POTION+122:	goto EXIT_CALCULATE;
#endif //LDK_ADD_INGAMESHOP_LOCKED_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_GOLD_CHEST			// �ݻ�����
	case ITEM_POTION+123:	goto EXIT_CALCULATE;
#endif //LDK_ADD_INGAMESHOP_GOLD_CHEST
#ifdef LDK_ADD_INGAMESHOP_SILVER_CHEST			// ��������
	case ITEM_POTION+124:	goto EXIT_CALCULATE;
#endif //LDK_ADD_INGAMESHOP_SILVER_CHEST
#ifdef LDK_ADD_INGAMESHOP_SMALL_WING			// �Ⱓ�� ���� ����(����, �糯, �䳯, õ��, �糯)
	case ITEM_WING+130:
	case ITEM_WING+131:
	case ITEM_WING+132:
	case ITEM_WING+133:
	case ITEM_WING+134:
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+135:
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		goto EXIT_CALCULATE;
#endif //LDK_ADD_INGAMESHOP_SMALL_WING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	case ITEM_HELPER+122:	// ���̷��� ���Ź���
		goto EXIT_CALCULATE;
#endif //YDG_ADD_SKELETON_CHANGE_RING
#ifdef YDG_ADD_SKELETON_PET
	case ITEM_HELPER+123:	// ���̷��� ��
		goto EXIT_CALCULATE;
#endif //YDG_ADD_SKELETON_PET
#ifdef PJH_ADD_PANDA_PET
	case ITEM_HELPER+80:  //�����
		goto EXIT_CALCULATE;
#endif //PJH_ADD_PANDA_PET
#ifdef PJH_ADD_PANDA_CHANGERING
	case ITEM_HELPER+76:  //������Ź���
		goto EXIT_CALCULATE;
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef LDK_ADD_PC4_GUARDIAN
	case ITEM_HELPER+64:  //���� ����
	case ITEM_HELPER+65:  //���� ��ȣ����
		goto EXIT_CALCULATE;
#endif //LDK_ADD_PC4_GUARDIAN
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
	case ITEM_HELPER+109:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(Ǫ����)��	// MODEL_HELPER+109
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
	case ITEM_HELPER+110:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGRUBY			// �ΰ��Ә� ������ // �ű� ���(������)��		// MODEL_HELPER+110
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
	case ITEM_HELPER+111:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGTOPAZ			// �ΰ��Ә� ������ // �ű� ������(��Ȳ)��		// MODEL_HELPER+111
#ifdef LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
	case ITEM_HELPER+112:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_RINGAMETHYST		// �ΰ��Ә� ������ // �ű� �ڼ���(�����)��		// MODEL_HELPER+112
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
	case ITEM_HELPER+113:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETRUBY			// �ΰ��Ә� ������ // �ű� ���(������) �����	// MODEL_HELPER+113
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
	case ITEM_HELPER+114:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETEMERALD		// �ΰ��Ә� ������ // �ű� ���޶���(Ǫ��) �����// MODEL_HELPER+114
#ifdef LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
	case ITEM_HELPER+115:
		goto EXIT_CALCULATE;
#endif // LDS_ADD_INGAMESHOP_ITEM_AMULETSAPPHIRE		// �ΰ��Ә� ������ // �ű� �����̾�(���) �����// MODEL_HELPER+115
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
	case ITEM_HELPER+128:
	case ITEM_HELPER+129:
	case ITEM_HELPER+134:
		goto EXIT_CALCULATE;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM
#ifdef LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	case ITEM_HELPER+130:	// �ű� ��ũ��
	case ITEM_HELPER+131:	// �ű� ��������
	case ITEM_HELPER+132:	// �ű� ����ũ��
	case ITEM_HELPER+133:	// ����������
		goto EXIT_CALCULATE;
#endif //LJH_ADD_ITEMS_EQUIPPED_FROM_INVENTORY_SYSTEM_PART_2
	}
#endif //LDK_MOD_PREMIUMITEM_SELL

	if(goldType==1 && !(ip->Type >= ITEM_HELPER+32 && ip->Type <= ITEM_HELPER+37))	//^ �渱 ������ ����
    {
        //  ��������� ����Ѵ�.
//        char Text[100];
        //int repairGold = ConvertRepairGold(Gold,ip->Durability, p->Durability, ip->Type, Text);
		DWORD maxDurability = calcMaxDurability ( ip, p, Level );
		float persent = 1.f - ( (float)ip->Durability / (float)maxDurability);
        DWORD repairGold = (DWORD)(Gold * 0.6f * persent);

		if(ip->Type == ITEM_HELPER+31)
			repairGold = 0;
	
        Gold -= repairGold;
    }
EXIT_CALCULATE:

	if(Gold >= 1000)
	{
		Gold = (Gold / 100) * 100;
	}
	else if(Gold >= 100)
	{
		Gold = (Gold / 10) * 10;
	}
#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ ������ �ϳ� //  ��������� ����Ѵ�. ( ���ܽ�Ű��! )
	if( Check_LuckyItem( ip->Type ) )	Gold = 0;
#endif // LEM_ADD_LUCKYITEM
	
	return (int)Gold;
}

#ifndef KJH_DEL_PC_ROOM_SYSTEM			// #ifndef
#ifndef ASG_PCROOM_POINT_SYSTEM_MODIFY		// ������ ����.
#ifdef ADD_PCROOM_POINT_SYSTEM
// ������ ���� ���� ����Ʈ ����.
int GetItemBuyingTermsPoint(ITEM* pItem)
{
	int nPoint = 0;

	return nPoint;
}
#endif	// ADD_PCROOM_POINT_SYSTEM
#endif	// ASG_PCROOM_POINT_SYSTEM_MODIFY	// ������ ����.
#endif // KJH_DEL_PC_ROOM_SYSTEM

/*	�̻�� �Լ��� �ּ�ó�� (����)
int ItemValueOld(ITEM *ip,int goldType)
{
	if(ip->Type == -1) return 0;

	ITEM_ATTRIBUTE *p = &ItemAttribute[ip->Type];

	int Gold = 0;
	int Type = ip->Type / MAX_ITEM_INDEX;
	int Level = (ip->Level>>3)&15;
	bool Excellent = false;
	for(int i=0;i<ip->SpecialNum;i++)
	{
		switch(ip->Special[i])
		{
		case AT_IMPROVE_LIFE:          
		case AT_IMPROVE_MANA:          
		case AT_DECREASE_DAMAGE:       
		case AT_REFLECTION_DAMAGE:     
		case AT_IMPROVE_BLOCKING_PERCENT:         
		case AT_IMPROVE_GAIN_GOLD:     
		case AT_EXCELLENT_DAMAGE:   
		case AT_IMPROVE_DAMAGE_LEVEL:  
		case AT_IMPROVE_DAMAGE_PERCENT:
		case AT_IMPROVE_MAGIC_LEVEL:   
		case AT_IMPROVE_MAGIC_PERCENT: 
		case AT_IMPROVE_ATTACK_SPEED:  
		case AT_IMPROVE_GAIN_LIFE:     
		case AT_IMPROVE_GAIN_MANA:     
			Excellent = true;
			break;
		}
	}
	int Level2 = p->Level+Level*3;
	if(Excellent)
		Level2 += 25;

	if(ip->Type==ITEM_BOW+7)        //  ���� ȭ��.
	{
        int sellMoney;

        switch ( Level )
        {
        case    0 :
            sellMoney = 100;
            break;
        case    1 :
            sellMoney = 1400;
            break;
        case    2 :
            sellMoney = 2200;
            break;
        }
		if(p->Durability > 0)
     		Gold = (sellMoney*ip->Durability/p->Durability);//+(170*(Level*2));
	}
	else if(ip->Type==ITEM_BOW+15)  //  ȭ��.
	{
        int sellMoney;

        switch ( Level )
        {
        case    0 :
            sellMoney = 70;
            break;
        case    1 :
            sellMoney = 1200;
            break;
        case    2 :
            sellMoney = 2000;
            break;
        }
		if(p->Durability > 0)
     		Gold = (sellMoney*ip->Durability/p->Durability);//+(80*(Level*2));
	}
	else if(ip->Type==ITEM_POTION+13)//��
	{
    	Gold = 100000;
	}
	else if(ip->Type==ITEM_POTION+14)//��
	{
    	Gold = 70000;
	}
	else if(ip->Type==ITEM_WING+15)//ȥ��
	{
    	Gold = 40000;
	}
    else if(ip->Type==ITEM_POTION+16)// ������ ����.
    {
        Gold = 210000;
    }
    else if(ip->Type==ITEM_POTION+22)// â���� ����.
    {
        Gold = 18000000;
    }
    else if(ip->Type==ITEM_HELPER+14)   //  ��ũ�� ����.
    {
        Gold = 180000;
    }
	else if(ip->Type==ITEM_HELPER+3)	// ����Ʈ
	{
        Gold = 960000;
        for(int i=0;i<ip->SpecialNum;i++)
		{
			switch(ip->Special[i])
            {
			case AT_DAMAGE_ABSORB:  
            case AT_IMPROVE_AG_MAX:
            case AT_IMPROVE_ATTACK_SPEED:
				Gold += 300000;
				break;
            }
        }
	}
    else if ( ip->Type==ITEM_HELPER+4 ) //  ��ũȣ��
    {
        Gold = 33000000;
    }
    else if(ip->Type==ITEM_HELPER+15)   //  ������Ʈ ��/�� ����.
    {
        Gold = 33000000;
    }
#ifdef LENA_EXCHANGE_ZEN
    else if(ip->Type==ITEM_POTION+21)
    {
        Gold = 9000;
    }
#endif
	else if(ip->Type==ITEM_POTION+17)// �Ǹ��� ��
	{
		int iValue[5] = { 30000, 15000, 21000, 30000, 45000};
		Gold = iValue[min( max( 0, Level), 4)];
	}
	else if(ip->Type==ITEM_POTION+18)// �Ǹ��� ����
	{
		int iValue[5] = { 30000, 15000, 21000, 30000, 45000};
		Gold = iValue[min( max( 0, Level), 4)];
	}
	else if(ip->Type==ITEM_POTION+19)// �������� �ʴ��
	{
		int iValue[5] = { 120000, 60000, 84000, 120000, 180000};
		Gold = iValue[min( max( 0, Level), 4)];
	}
	else if(ip->Type==ITEM_POTION+9 && Level == 1)// ����� �ø���
	{
		Gold = 1000;
	}
	else if(ip->Type==ITEM_POTION+20)	// ����� ����
	{
		Gold = 900;
	}
	else if(p->Value > 0)//����
	{
		Gold = p->Value*p->Value*10/12;
		if(ip->Type>=ITEM_POTION && ip->Type<=ITEM_POTION+8)
          	Gold *= ip->Durability;
	}
	else if( ( ( Type==12 && ip->Type>ITEM_WING+6) || Type==13 || Type==15 ) )//12(����,����) 13(��ź,����) 15(����), ����Ʈ ����.
	{
		Gold = 100+Level2*Level2*Level2;
        for(i=0;i<ip->SpecialNum;i++)
		{
			switch(ip->Special[i])
			{
			case AT_LIFE_REGENERATION:
				Gold += Gold*ip->SpecialValue[i];
				break;
			}
		}
	}
	else
	{
		switch(Level)     //+�����ϼ��� ����ġ ����
		{
		case 5:Level2 += 4;break;
		case 6:Level2 += 10;break;
		case 7:Level2 += 25;break;
		case 8:Level2 += 45;break;
		case 9:Level2 += 65;break;
		case 10:Level2 += 95;break;	// +10
		case 11:Level2 += 135;break;
		}
        //  ����.
	    if( ( Type==12 && ip->Type<=ITEM_WING+6) )
        {
            Gold = 40000000+((40+Level2)*Level2*Level2*11);
        }
        else
        {
		    Gold = 100+(40+Level2)*Level2*Level2/8;
        }
		if(Type>=0 && Type<=6) //�����϶�
		{
			if(!p->TwoHand) //�Ѽչ����϶� 80%
				Gold = Gold*80/100;
		}
        for(int i=0;i<ip->SpecialNum;i++)
		{
			switch(ip->Special[i])
			{
			case AT_SKILL_BLOCKING:
			case AT_SKILL_SWORD1:
			case AT_SKILL_SWORD2:
			case AT_SKILL_SWORD3:
			case AT_SKILL_SWORD4:
			case AT_SKILL_SWORD5:
			case AT_SKILL_CROSSBOW:
			case AT_SKILL_ICE_BLADE:
				Gold += ( int)( ( float)Gold*1.5f);
				break;
			case AT_IMPROVE_DAMAGE:
			case AT_IMPROVE_MAGIC:
			case AT_IMPROVE_DEFENSE:
                if ( Type==12 && ip->Type<=ITEM_WING+6 )    //  ����.
                {
				    switch(ip->SpecialValue[i])
				    {
				    case 4 :Gold += ( int)( ( float)Gold* 3/10);break;
				    case 8 :Gold += ( int)( ( float)Gold* 6/10);break;
				    case 12:Gold += ( int)( ( float)Gold*10/10);break;
				    case 16:Gold += ( int)( ( float)Gold*20/10);break;
				    }
                }
                else
                {
				    switch(ip->SpecialValue[i])
				    {
				    case 4 :Gold += ( int)( ( float)Gold* 6/10);break;
				    case 8 :Gold += ( int)( ( float)Gold*14/10);break;
				    case 12:Gold += ( int)( ( float)Gold*28/10);break;
				    case 16:Gold += ( int)( ( float)Gold*56/10);break;
				    }
                }
				break;
			case AT_IMPROVE_BLOCKING:
				switch(ip->SpecialValue[i])
				{
				case 5 :Gold += ( int)( ( float)Gold* 6/10);break;
				case 10:Gold += ( int)( ( float)Gold*14/10);break;
				case 15:Gold += ( int)( ( float)Gold*28/10);break;
				case 20:Gold += ( int)( ( float)Gold*56/10);break;
				}
				break;
			case AT_LUCK:
				Gold += ( int)( ( float)Gold*25/100);
				break;
			case AT_IMPROVE_LIFE:          
			case AT_IMPROVE_MANA:          
			case AT_DECREASE_DAMAGE:       
			case AT_REFLECTION_DAMAGE:     
			case AT_IMPROVE_BLOCKING_PERCENT:         
			case AT_IMPROVE_GAIN_GOLD:     
			case AT_EXCELLENT_DAMAGE:   
			case AT_IMPROVE_DAMAGE_LEVEL:  
			case AT_IMPROVE_DAMAGE_PERCENT:
			case AT_IMPROVE_MAGIC_LEVEL:   
			case AT_IMPROVE_MAGIC_PERCENT: 
			case AT_IMPROVE_GAIN_LIFE:     
			case AT_IMPROVE_GAIN_MANA:     
            case AT_IMPROVE_HP_MAX :
            case AT_IMPROVE_MP_MAX :
            case AT_ONE_PERCENT_DAMAGE :  
			case AT_IMPROVE_ATTACK_SPEED:  
            case AT_IMPROVE_AG_MAX :
            case AT_IMPROVE_EVADE:
				Gold += Gold;
				break;
			}
		}
	}
    if( goldType )  //  �ȱ�. ����.
    {
	    Gold = Gold/3;
    }

    //  ������ �ʿ��� �������� �� ����� �� ������ ���� �ȸ��� �����̴�.
    if(goldType==1 && 
     ((ip->Type<ITEM_POTION  && ip->Type!=ITEM_HELPER+10) &&
       ip->Type!=ITEM_BOW+7  && ip->Type!=ITEM_BOW+15      &&
      (ip->Type<ITEM_WING || ip->Type>ITEM_WING+6) &&   //  ����.
		ip->Type != ITEM_HELPER+29 &&
      (ip->Type!=ITEM_HELPER && ip->Type!=ITEM_HELPER+1 && ip->Type!=ITEM_HELPER+2 && ip->Type!=ITEM_HELPER+3 && ip->Type!=ITEM_HELPER+15) ) )
    {
        //  ��������� ����Ѵ�.
		int maxDurability = calcMaxDurability ( ip, p, Level );
		float   persent = 1.f - ( (float)ip->Durability / (float)maxDurability);
        int repairGold = (int)(Gold * 0.6f * persent);

        Gold -= repairGold;
    }

	if(Gold >= 1000)
		Gold = Gold/100*100;
	else if(Gold >= 100)
		Gold = Gold/10*10;
	return Gold;
}
*/

#ifdef PSW_BUGFIX_REQUIREEQUIPITEM

bool IsRequireEquipItem(ITEM* pItem)
{
	if(pItem == NULL){
		return false;
	}
	
	ITEM_ATTRIBUTE* pItemAttr = &ItemAttribute[pItem->Type];
	
	bool bEquipable = false;
	
	///////////////////////////////////���� ������ Ŭ���� üũ///////////////////////////////////
	
	//. ���� ʦ
	if( pItemAttr->RequireClass[GetBaseClass(Hero->Class)] ){
		bEquipable = true; 
	}
	//. ������ ��� ����, ������ ���� ʦ
	else if (GetBaseClass(Hero->Class) == CLASS_DARK && pItemAttr->RequireClass[CLASS_WIZARD] 
		&& pItemAttr->RequireClass[CLASS_KNIGHT]) {
		bEquipable = true; 
	}
	
	// �����ܰ踦 �˻��ؼ� 
	BYTE byFirstClass = GetBaseClass(Hero->Class);
	BYTE byStepClass = GetStepClass(Hero->Class);
	if( pItemAttr->RequireClass[byFirstClass] > byStepClass)
	{
		return false;
	}
	
	if(bEquipable == false)
		return false;
	
	///////////////////////////////////�䱸 �ɷ�ġ üũ///////////////////////////////////////
	
	WORD wStrength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
	WORD wDexterity = CharacterAttribute->Dexterity + CharacterAttribute->AddDexterity;
	WORD wEnergy = CharacterAttribute->Energy + CharacterAttribute->AddEnergy;
	WORD wVitality = CharacterAttribute->Vitality + CharacterAttribute->AddVitality;
	WORD wCharisma = CharacterAttribute->Charisma + CharacterAttribute->AddCharisma;
	WORD wLevel = CharacterAttribute->Level;
	
	int iItemLevel = (pItem->Level>>3)&15;
	
	int iDecNeedStrength = 0, iDecNeedDex = 0;

	extern JewelHarmonyInfo*   g_pUIJewelHarmonyinfo;
	if( iItemLevel >= pItem->Jewel_Of_Harmony_OptionLevel )
	{
		StrengthenCapability SC;
		g_pUIJewelHarmonyinfo->GetStrengthenCapability( &SC, pItem, 0 );
		
		if( SC.SI_isNB ) 
		{
			iDecNeedStrength = SC.SI_NB.SI_force;
			iDecNeedDex      = SC.SI_NB.SI_activity;
		}
	}
	
	if ( pItem->RequireStrength - iDecNeedStrength > wStrength )
		return false;    //  �䱸������ ������ ����.
	if ( pItem->RequireDexterity - iDecNeedDex > wDexterity )
		return false;    //  �䱸��ø���� ������ ����.
	if ( pItem->RequireEnergy > wEnergy )
		return false;    //  �䱸���������� ������ ����.
	if ( pItem->RequireVitality > wVitality )
		return false;    //  �䱸ü�º��� ������ ����.
	if( pItem->RequireCharisma > wCharisma )
		return false;    //  �䱸��ֺ��� ������ ����.
	if( pItem->RequireLevel > wLevel )
		return false;    //  �䱸�������� ������ ����.
	
	/////////////////////////////////////////��� ����//////////////////////////////////////////
	
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	if(pItem->Type == ITEM_HELPER+5 )			// ��ũ���Ǹ�		   
	{
		PET_INFO* pPetInfo = giPetManager::GetPetInfo( pItem );
		WORD wRequireCharisma = (185+(pPetInfo->m_wLevel*15));
		if( wRequireCharisma > wCharisma ) {
			return false;	//  �䱸��ֺ��� ������ ����.
		}
	}
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
	PET_INFO petInfo;
	giPetManager::GetPetInfo(petInfo, pItem->Type);
	WORD wRequireCharisma = (185+(petInfo.m_wLevel*15));		// ������ - ��ũȣ��, ���Ǹ� �䱸 �������

	// ������ - ��ũ ���Ǹ� �϶� �䱸����� ������ ����
	if(pItem->Type == 421 )		   
	{
		if( wRequireCharisma > wCharisma ) {
			return false;	//  �䱸��ֺ��� ������ ����.
		}
	}
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
	
	return bEquipable;
}

#endif //PSW_BUGFIX_REQUIREEQUIPITEM

// �߰�������
void PlusSpecial(WORD *Value,int Special,ITEM *Item)
{
	if(Item->Type == -1) {
		return;
	}

#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	if( IsRequireEquipItem(Item) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	{
		for(int i=0;i<Item->SpecialNum;i++)
		{
			//  �������� 0�̸��� �������� �ɷ��� ���� ���Ѵ�.
			if(Item->Special[i] == Special && Item->Durability!=0)
				*Value += Item->SpecialValue[i];
		}
	}
}

// �߰� +% ������
void PlusSpecialPercent(WORD *Value,int Special,ITEM *Item,WORD Percent)
{
	if(Item->Type == -1) return;

#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	if( IsRequireEquipItem(Item) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	{
		for(int i=0;i<Item->SpecialNum;i++)
		{
			if(Item->Special[i] == Special && Item->Durability!=0 )
				*Value += *Value*Percent/100;
		}
	}
}

void PlusSpecialPercent2(WORD *Value,int Special,ITEM *Item)
{
	if(Item->Type == -1) return;

#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	if( IsRequireEquipItem(Item) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SPECIALOPTION
	{
		for(int i=0;i<Item->SpecialNum;i++)
		{
			if(Item->Special[i] == Special && Item->Durability!=0 )
				*Value += (unsigned short)(*Value*(Item->SpecialValue[i]/100.f));
		}
	}
}

WORD ItemDefense(ITEM *Item)
{
	if(Item->Type == -1) return 0;
	WORD Defense = Item->Defense;
	PlusSpecial(&Defense,AT_IMPROVE_DEFENSE,Item);
	return Defense;
}

WORD ItemMagicDefense(ITEM *Item)
{
	if(Item->Type == -1) return 0;
	WORD MagicDefense = Item->MagicDefense;
	//PlusSpecial(&MagicDefense,PLUS_MAGIC_DEFENSE,Item);
	return MagicDefense;
}

WORD ItemWalkSpeed(ITEM *Item)
{
	if(Item->Type == -1) return 0;
	WORD WalkSpeed = Item->WalkSpeed;
	//PlusSpecial(&WalkSpeed,PLUS_WALK_SPEED,Item);
	return WalkSpeed;
}


///////////////////////////////////////////////////////////////////////////////
// monster
///////////////////////////////////////////////////////////////////////////////

extern int HeroKey;
int EditMonsterNumber = 0;
int MonsterKey = 0;

void OpenMonsters(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	Token = (*GetToken)();
	while(true)
	{
		Token = (*GetToken)();int Monster = (int)TokenNumber;
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
		Token = (*GetToken)();
		Token = (*GetToken)();
		Token = (*GetToken)();int x = (int)TokenNumber;
		Token = (*GetToken)();int y = (int)TokenNumber;
		Token = (*GetToken)();
		if(MonsterKey == HeroKey) MonsterKey++;
        CHARACTER *c = CreateMonster(Monster,x,y,MonsterKey++);
		if(c != NULL)
			c->Object.Kind = KIND_EDIT;
	}
	fclose(SMDFile);
}

void OpenMonsterScript(char *FileName)
{
	if((SMDFile=fopen(FileName,"rb")) == NULL)	return;
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();//��ȣ
		if(Token == END) break;
		if(Token == NAME && strcmp("end",TokenString)==NULL) break;
        MONSTER_SCRIPT *m = &MonsterScript[EditMonsterNumber++];
		m->Type = (int)TokenNumber;
		Token = (*GetToken)();
		Token = (*GetToken)();strcpy(m->Name,TokenString);
		//Token = (*GetToken)();m->Level = (int)TokenNumber;
		//for(int i=0;i<23;i++) Token = (*GetToken)();
	}
	fclose(SMDFile);
}

//////////////////////////////////////////////////////////////////////////
//  ������ �̸��� �˾Ƴ���.
//////////////////////////////////////////////////////////////////////////
char*   getMonsterName ( int type )
{
    for ( int i=0; i<MAX_MONSTER; ++i )
    {
        if ( MonsterScript[i].Type==type )
        {
            return MonsterScript[i].Name;
        }
    }
    return NULL;
}

void MonsterConvert(MONSTER *m,int Level)
{
	MONSTER_SCRIPT    *p            = &MonsterScript[m->Type];
	MONSTER_ATTRIBUTE *c            = &p->Attribute;
	m->Level                        = Level;
	m->Attribute.AttackSpeed        = c->AttackSpeed;
    m->Attribute.AttackDamageMin    = c->AttackDamageMin   /2+c->AttackDamageMin   /2*(m->Level)/9;
	m->Attribute.AttackDamageMax	= c->AttackDamageMax   /2+c->AttackDamageMax   /2*(m->Level)/9;
	m->Attribute.Defense            = c->Defense           /2+c->Defense           /2*(m->Level)/9;
	m->Attribute.AttackRating       = c->AttackRating      /2+c->AttackRating      /2*(m->Level)/9;
	m->Attribute.SuccessfulBlocking = c->SuccessfulBlocking/2+c->SuccessfulBlocking/2*(m->Level)/9;
}

///////////////////////////////////////////////////////////////////////////////
// class
///////////////////////////////////////////////////////////////////////////////

void CreateClassAttribute(int Class,int Strength,int Dexterity,int Vitality,int Energy,int Life,int Mana,int LevelLife,int LevelMana,int VitalityToLife,int EnergyToMana)
{
	CLASS_ATTRIBUTE *c = &ClassAttribute[Class];
	c->Strength		  = Strength;
	c->Dexterity	  = Dexterity;
	c->Vitality		  = Vitality;
	c->Energy		  = Energy;
	c->Life           = Life;
	c->Mana           = Mana;
	c->LevelLife	  = LevelLife;
	c->LevelMana	  = LevelMana;
	c->VitalityToLife = VitalityToLife;
	c->EnergyToMana   = EnergyToMana;
	c->Shield		  =  0;
}

void CreateClassAttributes()
{
	CreateClassAttribute( 0, 18, 18, 15, 30,	  80, 60,	  1, 2, 1, 2 );	//������
	CreateClassAttribute( 1, 28, 20, 25, 10,	 110, 20,	  2, 1, 2, 1 );	//����
	CreateClassAttribute( 2, 50, 50, 50, 30,	 110, 30,	 110, 30, 6, 3 );	//����
	CreateClassAttribute( 3, 30, 30, 30, 30,	 120, 80,	  1, 1, 2, 2 );	//�����
	CreateClassAttribute( 4, 30, 30, 30, 30,	 120, 80,	  1, 1, 2, 2 );	//��ũ�ε�
	CreateClassAttribute( 5, 50, 50, 50, 30,	 110, 30,	 110, 30, 6, 3 );	// ������
#ifdef PBG_ADD_NEWCHAR_MONK
	CreateClassAttribute( 6, 32, 27, 25, 20,	 100, 40,	 /*������ => */1, 3, 1, 1);	// ��ũ
#endif //PBG_ADD_NEWCHAR_MONK
}

///////////////////////////////////////////////////////////////////////////////
// Durability Percent Calc.
///////////////////////////////////////////////////////////////////////////////
float CalcDurabilityPercent ( BYTE dur, BYTE maxDur, int Level, int option, int ExtOption )
{
    int maxDurability = maxDur;
    for( int i=0; i<((Level>>3)&15); i++ )
    {
        if(i>=4)
        {
            maxDurability+=2;
        }
        else
        {
            maxDurability++;
        }
    }

    if ( (ExtOption%0x04)==EXT_A_SET_OPTION || (ExtOption%0x04)==EXT_B_SET_OPTION )    //  ��Ʈ ������.
    {
        maxDurability+=20;
    }
    else if((option&63) > 0 )
    {
        maxDurability+=15;
    }

    float   durP = 1.f - (dur/(float)maxDurability);

    if( durP>0.8f )
    {
        return  0.5f;
    }
    else
    if( durP>0.7f )
    {
        return  0.3f;
    }
    else
    if( durP>0.5f )
    {
        return  0.2f;
    }
    else
    {
        return  0.f;
    }
    return 0.f;
}


///////////////////////////////////////////////////////////////////////////////
// character machine
///////////////////////////////////////////////////////////////////////////////

void CHARACTER_MACHINE::Init()
{
    CreateClassAttributes();
	for(int i=0;i<MAX_EQUIPMENT;i++)
	{
		Equipment[i].Type = -1;
	}
	Gold = 0;
	StorageGold = 0;
	PacketSerial = 0;
	InfinityArrowAdditionalMana = 0;
}

void CHARACTER_MACHINE::InitAddValue ()
{
	Character.AddStrength	= 0;
	Character.AddDexterity  = 0;
	Character.AddVitality	= 0;
	Character.AddEnergy		= 0;
    Character.AddCharisma   = 0;
	Character.AddLifeMax	= 0;
	Character.AddManaMax	= 0;
}

void CHARACTER_MACHINE::SetCharacter(BYTE Class)
{
	CLASS_ATTRIBUTE *c  = &ClassAttribute[Class];
	Character.Class	    = Class;
	Character.Level	    = 1;
	Character.Strength	= c->Strength;
	Character.Dexterity = c->Dexterity;
	Character.Vitality	= c->Vitality;
	Character.Energy	= c->Energy;
	Character.Life      = c->Life;
	Character.Mana      = c->Mana;
	Character.LifeMax   = c->Life;
	Character.ManaMax   = c->Mana;
	Character.Shield	= c->Shield;
	Character.ShieldMax = c->Shield;

	InitAddValue ();
	hanguo_check5();

	for(int j=0;j<MAX_SKILLS;j++)
	{
		Character.Skill[j] = 0;
	}
}

void CHARACTER_MACHINE::InputEnemyAttribute(MONSTER *e)
{
	memcpy(&Enemy,e,sizeof(MONSTER));
}

void CHARACTER_MACHINE::CalculateDamage()
{
    WORD    DamageMin, DamageMax;

	ITEM *Right  = &Equipment[EQUIPMENT_WEAPON_RIGHT];
	ITEM *Left   = &Equipment[EQUIPMENT_WEAPON_LEFT];
	ITEM *Amulet = &Equipment[EQUIPMENT_AMULET];
	ITEM *RRing  = &Equipment[EQUIPMENT_RING_RIGHT];
	ITEM *LRing  = &Equipment[EQUIPMENT_RING_LEFT];

	WORD Strength, Dexterity, Energy;

	Strength = Character.Strength + Character.AddStrength;
	Dexterity= Character.Dexterity+ Character.AddDexterity;
	Energy	 = Character.Energy   + Character.AddEnergy;
#ifdef PBG_ADD_NEWCHAR_MONK
	WORD Vitality = Character.Vitality + Character.AddVitality;
#endif //PBG_ADD_NEWCHAR_MONK

#ifndef ASG_FIX_PICK_ITEM_FROM_INVEN	// ������ ����.
	// �������� �� ���
	SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
	// �κ��丮���� �� ���ΰ�?
	if ( pPickedItem && pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())
	{	
		ITEM* pItemObj = pPickedItem->GetItem();

		switch ( pPickedItem->GetSourceLinealPos() ) {
		case EQUIPMENT_WEAPON_RIGHT:
			Right = pItemObj;
			break;
		case EQUIPMENT_WEAPON_LEFT:
			Left = pItemObj;
			break;
		case EQUIPMENT_AMULET:
			Amulet = pItemObj;
			break;
		case EQUIPMENT_RING_RIGHT:
			RRing = pItemObj;
			break;
		case EQUIPMENT_RING_LEFT:
			LRing = pItemObj;
			break;
		}
	}
#endif	// ASG_FIX_PICK_ITEM_FROM_INVEN

    int CharacterClass = GetBaseClass ( Character.Class );

    //  �������� 0�̸��� �� ��� �����ߴٰ� �ν����� �ʴ´�.
 #ifdef ADD_SOCKET_ITEM
     if( ((GetEquipedBowType(Left) == BOWTYPE_BOW) && (Left->Durability != 0))
		|| ((GetEquipedBowType(Right) == BOWTYPE_CROSSBOW) && (Right->Durability != 0))
		)
 #else // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
    if( (Right->Type>=ITEM_BOW+8  && Right->Type<ITEM_BOW+15 && Right->Durability!=0 ) ||
		(((Left->Type>=ITEM_BOW   && Left->Type<ITEM_BOW+7 ) || Left->Type==ITEM_BOW+17
		|| Left->Type==ITEM_BOW+20 || Left->Type==ITEM_BOW+21 || Left->Type==ITEM_BOW+22
		) && Left->Durability!=0 ) || 
        (Right->Type>=ITEM_BOW+16 && Right->Type<ITEM_BOW+MAX_ITEM_INDEX && Right->Durability!=0 ) )
#endif // ADD_SOCKET_ITEM				// ������ �� ������ �ϴ� �ҽ�
	{	
		Character.AttackDamageMinRight = Dexterity/7 + Strength/14;
		Character.AttackDamageMaxRight = Dexterity/4 + Strength/8;
		Character.AttackDamageMinLeft  = Dexterity/7 + Strength/14;
		Character.AttackDamageMaxLeft  = Dexterity/4 + Strength/8;
	}
	else
	{
        switch ( CharacterClass )
        {
        case CLASS_ELF:
			Character.AttackDamageMinRight = (Strength+Dexterity)/7;
			Character.AttackDamageMaxRight = (Strength+Dexterity)/4;
			Character.AttackDamageMinLeft  = (Strength+Dexterity)/7;
			Character.AttackDamageMaxLeft  = (Strength+Dexterity)/4;
            break;

        case CLASS_KNIGHT:
            {
                int minValue = 7;
                int maxValue = 4;
                
                minValue = 6; maxValue = 4;

                Character.AttackDamageMinRight = Strength/minValue;
                Character.AttackDamageMaxRight = Strength/maxValue;
                Character.AttackDamageMinLeft  = Strength/minValue;
                Character.AttackDamageMaxLeft  = Strength/maxValue;
            }
            break;

        case CLASS_DARK:
            {
                int minValue[2] = { 7, 10 };
                int maxValue[2] = { 4, 5 };
                
                minValue[0] = 6; minValue[1] = 12;
				maxValue[0] = 4; maxValue[1] = 9;

                Character.AttackDamageMinRight = (Strength/minValue[0])+Energy/minValue[1];
                Character.AttackDamageMaxRight = (Strength/maxValue[0])+Energy/maxValue[1];
                Character.AttackDamageMinLeft  = (Strength/minValue[0])+Energy/minValue[1];
                Character.AttackDamageMaxLeft  = (Strength/maxValue[0])+Energy/maxValue[1];
            }
            break;
        case CLASS_DARK_LORD:
			Character.AttackDamageMinRight = Strength/7+Energy/14;
			Character.AttackDamageMaxRight = Strength/5+Energy/10;
			Character.AttackDamageMinLeft  = Strength/7+Energy/14;
			Character.AttackDamageMaxLeft  = Strength/5+Energy/10;
            break;
			
		case CLASS_SUMMONER:
			Character.AttackDamageMinRight = (Strength+Dexterity)/7;
			Character.AttackDamageMaxRight = (Strength+Dexterity)/4;
			Character.AttackDamageMinLeft  = (Strength+Dexterity)/7;
			Character.AttackDamageMaxLeft  = (Strength+Dexterity)/4;
			break;
#ifdef PBG_ADD_NEWCHAR_MONK
		case CLASS_RAGEFIGHTER:
			{
			Character.AttackDamageMinRight = Strength/7 + Vitality/15;
			Character.AttackDamageMaxRight = Strength/5 + Vitality/12;
			Character.AttackDamageMinLeft  = Strength/7 + Vitality/15;
			Character.AttackDamageMaxLeft  = Strength/5 + Vitality/12;
			}
			break;
#endif //PBG_ADD_NEWCHAR_MONK
        default :
			Character.AttackDamageMinRight = Strength/8;
			Character.AttackDamageMaxRight = Strength/4;
			Character.AttackDamageMinLeft  = Strength/8;
			Character.AttackDamageMaxLeft  = Strength/4;
            break;
        }
	}

    //  ����.
    if ( Equipment[EQUIPMENT_WING].Type!=-1 )
    {
        //  �����¿� ���� ���ݷ� ����.
        ITEM_ATTRIBUTE *p = &ItemAttribute[Equipment[EQUIPMENT_WING].Type];
        if ( p->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
			&& IsRequireEquipItem(&Equipment[EQUIPMENT_WING])
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE
			)
        {
            float   percent = CalcDurabilityPercent(Equipment[EQUIPMENT_WING].Durability,p->Durability,Equipment[EQUIPMENT_WING].Level,0,0);//Equipment[EQUIPMENT_WING].Option1);
            
            DamageMin = 0; DamageMax = 0;
            PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,&Equipment[EQUIPMENT_WING]);
            PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,&Equipment[EQUIPMENT_WING]);
            
            DamageMin = DamageMin - (WORD)(DamageMin*percent);
            DamageMax = DamageMax - (WORD)(DamageMax*percent);
            
            Character.AttackDamageMinRight += DamageMin;
            Character.AttackDamageMaxRight += DamageMax;
            Character.AttackDamageMinLeft  += DamageMin;
            Character.AttackDamageMaxLeft  += DamageMax;
        }
    }

	// ������
    //  �������� 0�� �ƴҶ��� ����.
	if ( Right->Type!=-1 && Right->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		&& IsRequireEquipItem( Right )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE
		)
	{
        //  �����¿� ���� ���ݷ� ����.
        ITEM_ATTRIBUTE *p = &ItemAttribute[Right->Type];
        float   percent = CalcDurabilityPercent(Right->Durability,p->Durability,Right->Level,Right->Option1,Right->ExtOption);

        //  ������ ���ݷ�.
        DamageMin = Right->DamageMin;
        DamageMax = Right->DamageMax;

		// �߰����ݷ� �ɼ�
		PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,Right);
		PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,Right);

        DamageMin = DamageMin - (WORD)(DamageMin*percent);
        DamageMax = DamageMax - (WORD)(DamageMax*percent);

		//	�������� ���ݷ� ����.
		if ( Right->Type>=ITEM_STAFF && Right->Type<=ITEM_STAFF+MAX_ITEM_INDEX )
		{
			Character.AttackDamageMinLeft += (WORD)(DamageMin);
			Character.AttackDamageMaxLeft += (WORD)(DamageMax);
		}
		else
		{
			Character.AttackDamageMinRight += DamageMin;
			Character.AttackDamageMaxRight += DamageMax;
		}

        //  �׼���Ʈ.
		PlusSpecial(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_LEVEL,Right);
		PlusSpecial(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_LEVEL,Right);
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,Right,2);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,Right,2);
	}

	// �޼�
    if ( Left->Type!=-1 && Left->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		&& IsRequireEquipItem( Left )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE	
		)
	{
        //  �����¿� ���� ���ݷ� ����.
        ITEM_ATTRIBUTE *p = &ItemAttribute[Left->Type];
        float   percent = CalcDurabilityPercent(Left->Durability,p->Durability,Left->Level,Left->Option1,Left->ExtOption);

        //  ������ ���ݷ�.
        DamageMin = Left->DamageMin;
        DamageMax = Left->DamageMax;

		PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,Left);
		PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,Left);

        DamageMin = DamageMin - (WORD)(DamageMin*percent);
        DamageMax = DamageMax - (WORD)(DamageMax*percent);

		//	�������� ���ݷ� ����.
		if ( Left->Type>=ITEM_STAFF && Left->Type<=ITEM_STAFF+MAX_ITEM_INDEX )
		{
			Character.AttackDamageMinLeft += (WORD)(DamageMin);
			Character.AttackDamageMaxLeft += (WORD)(DamageMax);
		}
		else
		{
			Character.AttackDamageMinLeft += DamageMin;
			Character.AttackDamageMaxLeft += DamageMax;
		}

        //  �׼���Ʈ.
		PlusSpecial(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_LEVEL,Left);
		PlusSpecial(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_LEVEL,Left);
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,Left,2);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,Left,2);
	}

    //  ���� ����� �׼���Ʈ ����.
    if ( Amulet->Type!=-1 && Amulet->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		&& IsRequireEquipItem( Amulet )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE	
		)
	{
        //  ������.
		PlusSpecial(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_LEVEL,Amulet);
		PlusSpecial(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_LEVEL,Amulet);
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,Amulet,2);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,Amulet,2);

        //  �޼�.
		PlusSpecial(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_LEVEL,Amulet);
		PlusSpecial(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_LEVEL,Amulet);
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,Amulet,2);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,Amulet,2);
	}
	// �������� ����
    if ( RRing->Type!=-1 && RRing->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		&& IsRequireEquipItem( RRing )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE	
		)
	{
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
        //  ������.
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,RRing,RRing->SpecialValue[1]);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,RRing,RRing->SpecialValue[1]);

        //  �޼�.
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,RRing,RRing->SpecialValue[1]);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,RRing,RRing->SpecialValue[1]);
#else	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
        //  ������.
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,RRing,10);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,RRing,10);

        //  �޼�.
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,RRing,10);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,RRing,10);
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
	}
    if ( LRing->Type!=-1 && LRing->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		&& IsRequireEquipItem( LRing )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE	
		)
	{
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
        //  ������.
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,LRing,LRing->SpecialValue[1]);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,LRing,LRing->SpecialValue[1]);

        //  �޼�.
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,LRing,LRing->SpecialValue[1]);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,LRing,LRing->SpecialValue[1]);
#else	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
        //  ������.
		PlusSpecialPercent(&Character.AttackDamageMinRight,AT_IMPROVE_DAMAGE_PERCENT,LRing,10);
		PlusSpecialPercent(&Character.AttackDamageMaxRight,AT_IMPROVE_DAMAGE_PERCENT,LRing,10);

        //  �޼�.
		PlusSpecialPercent(&Character.AttackDamageMinLeft,AT_IMPROVE_DAMAGE_PERCENT,LRing,10);
		PlusSpecialPercent(&Character.AttackDamageMaxLeft,AT_IMPROVE_DAMAGE_PERCENT,LRing,10);
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
	}

	//	��Ʈ �ɼ��� �����Ѵ�.
    WORD    Damage = 0;
	
	
#ifdef LDS_FIX_SETITEM_WRONG_CALCULATION_IMPROVEATTACKVALUE		//  ��Ʈ �ɼ� ���� �� ���뿩�� flag table �� �ʱ�ȭ �Ѵ�.
	memset ( g_csItemOption.m_bySetOptionListOnOff, 0, sizeof( BYTE )* 16 );
#endif // LDS_FIX_SETITEM_WRONG_CALCULATION_IMPROVEATTACKVALUE

	g_csItemOption.PlusSpecial ( &Damage,  AT_SET_OPTION_IMPROVE_ATTACK_MIN );	//	�ּ� ���ݷ� ����.
    Character.AttackDamageMinLeft += Damage;
    Character.AttackDamageMinRight+= Damage;

    Damage = 0;
    g_csItemOption.PlusSpecial ( &Damage,  AT_SET_OPTION_IMPROVE_ATTACK_MAX );	//	�ִ� ���ݷ� ����.
    Character.AttackDamageMaxLeft += Damage;
    Character.AttackDamageMaxRight+= Damage;

    Damage = 0;
	g_csItemOption.PlusSpecialLevel ( &Damage, Dexterity, AT_SET_OPTION_IMPROVE_ATTACK_1 );	//	Ư�� ĳ���� ���ݷ� ���� ��ø��/60		
    Character.AttackDamageMinRight += Damage;
    Character.AttackDamageMaxRight += Damage;
    Character.AttackDamageMinLeft  += Damage;
    Character.AttackDamageMaxLeft  += Damage;
	
    Damage = 0;
	g_csItemOption.PlusSpecialLevel ( &Damage, Strength, AT_SET_OPTION_IMPROVE_ATTACK_2 );	//	Ư�� ĳ���� ���ݷ� ���� ��/50		    
    Character.AttackDamageMinRight += Damage;
    Character.AttackDamageMaxRight += Damage;
    Character.AttackDamageMinLeft  += Damage;
    Character.AttackDamageMaxLeft  += Damage;

    //  ȭ�쿡 ���� �߰� ���ݷ�.
    if ( ( Right->Type>=ITEM_BOW && Right->Type<ITEM_BOW+MAX_ITEM_INDEX ) &&
         ( Left->Type>=ITEM_BOW && Left->Type<ITEM_BOW+MAX_ITEM_INDEX ) 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE 
		 && IsRequireEquipItem( Right ) && IsRequireEquipItem( Left ) 
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DAMAGE	
		 )
    {
        int LLevel = ((Left->Level>>3)&15);
        int RLevel = ((Right->Level>>3)&15);

        //  ARROW�� LEVEL�� 1�̸��� ���ݷ� ����. ���ݷ�3% + 1 ����.
        if ( Left->Type==ITEM_BOW+7 && LLevel>=1 )
        {
            Character.AttackDamageMinRight += (WORD)(Character.AttackDamageMinRight*((LLevel*2+1)*0.01f)+1);
            Character.AttackDamageMaxRight += (WORD)(Character.AttackDamageMaxRight*((LLevel*2+1)*0.01f)+1);
        }
        else
        if ( Right->Type==ITEM_BOW+15 && RLevel>=1 )
        {
            Character.AttackDamageMinLeft += (WORD)(Character.AttackDamageMinLeft*((RLevel*2+1)*0.01f)+1);
            Character.AttackDamageMaxLeft += (WORD)(Character.AttackDamageMaxLeft*((RLevel*2+1)*0.01f)+1);
        }
    }
#ifdef PSW_SCROLL_ITEM
	if(g_isCharacterBuff((&Hero->Object), eBuff_EliteScroll3))  // �г��� ��ũ��
	{
			ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 74);
			Character.AttackDamageMinRight += Item_data.m_byValue1;
			Character.AttackDamageMaxRight += Item_data.m_byValue1;
			Character.AttackDamageMinLeft  += Item_data.m_byValue1;
			Character.AttackDamageMaxLeft  += Item_data.m_byValue1;
	}
#endif// PSW_SCROLL_ITEM
#ifdef HELLOWIN_EVENT
	if(g_isCharacterBuff((&Hero->Object), eBuff_Hellowin2)) // ��������� �г�
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 47);
		Character.AttackDamageMinRight += Item_data.m_byValue1;
		Character.AttackDamageMaxRight += Item_data.m_byValue1;
		Character.AttackDamageMinLeft  += Item_data.m_byValue1;
		Character.AttackDamageMaxLeft  += Item_data.m_byValue1;
	}
#endif //HELLOWIN_EVENT
#ifdef CSK_EVENT_CHERRYBLOSSOM
	if(g_isCharacterBuff((&Hero->Object), eBuff_CherryBlossom_Petal))  // ���ɲ���
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 87);
		Character.AttackDamageMinRight += Item_data.m_byValue1;
		Character.AttackDamageMaxRight += Item_data.m_byValue1;
		Character.AttackDamageMinLeft  += Item_data.m_byValue1;
		Character.AttackDamageMaxLeft  += Item_data.m_byValue1;
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef ADD_SOCKET_STATUS_BONUS
	Character.AttackDamageMinRight += g_SocketItemMgr.m_StatusBonus.m_iAttackDamageMinBonus;
	Character.AttackDamageMaxRight += g_SocketItemMgr.m_StatusBonus.m_iAttackDamageMaxBonus;
	Character.AttackDamageMinLeft  += g_SocketItemMgr.m_StatusBonus.m_iAttackDamageMinBonus;
	Character.AttackDamageMaxLeft  += g_SocketItemMgr.m_StatusBonus.m_iAttackDamageMaxBonus;
#endif	// ADD_SOCKET_STATUS_BONUS
#ifdef PBG_ADD_SANTABUFF
	if(g_isCharacterBuff((&Hero->Object), eBuff_BlessingOfXmax))	//ũ���������� �ູ
	{
		int _Temp = 0;
		_Temp = Character.Level / 3 +45;

		Character.AttackDamageMinRight += _Temp;
		Character.AttackDamageMaxRight += _Temp;
		Character.AttackDamageMinLeft += _Temp;
		Character.AttackDamageMaxLeft += _Temp;
	}

	if(g_isCharacterBuff((&Hero->Object), eBuff_StrengthOfSanta))	//��Ÿ�� ��ȭ
	{
		int _Temp = 30;
		
		Character.AttackDamageMinRight += _Temp;
		Character.AttackDamageMaxRight += _Temp;
		Character.AttackDamageMinLeft += _Temp;
		Character.AttackDamageMaxLeft += _Temp;

	}
#endif //PBG_ADD_SANTABUFF

#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	if(g_isCharacterBuff((&Hero->Object), eBuff_StrongCharm))	// ������ ���� (PC�� ������)	// ������ ������ ���ݷ� + 50 
	{
		int _Temp = 50;
		
		Character.AttackDamageMinRight += _Temp;
		Character.AttackDamageMaxRight += _Temp;
		Character.AttackDamageMinLeft += _Temp;
		Character.AttackDamageMaxLeft += _Temp;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH
}

void CHARACTER_MACHINE::CalculateCriticalDamage()
{
	Character.CriticalDamage = 0;
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_WEAPON_RIGHT]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_WEAPON_LEFT]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_HELM  ]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_ARMOR ]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_PANTS ]);
    PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_GLOVES]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_BOOTS ]);
	PlusSpecial(&Character.CriticalDamage,AT_LUCK,&Equipment[EQUIPMENT_WING  ]);
}

void CHARACTER_MACHINE::CalculateMagicDamage()
{
	WORD Energy;
	Energy	 = Character.Energy   + Character.AddEnergy;  
	Character.MagicDamageMin = Energy/9;
	Character.MagicDamageMax = Energy/4;

	ITEM* Right  = &Equipment[EQUIPMENT_WEAPON_RIGHT];
#ifdef KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
	ITEM* Left	= &Equipment[EQUIPMENT_WEAPON_LEFT];
#endif // KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
	ITEM* Amulet = &Equipment[EQUIPMENT_AMULET];
	ITEM* RRing  = &Equipment[EQUIPMENT_RING_RIGHT];
	ITEM* LRing  = &Equipment[EQUIPMENT_RING_LEFT];

#ifndef ASG_FIX_PICK_ITEM_FROM_INVEN	// ������ ����.
	// �������� �� ���
	SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
	// �κ��丮���� �� ���ΰ�?
	if ( pPickedItem && pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())
	{	
		ITEM* pItemObj = pPickedItem->GetItem();
		
		switch ( pPickedItem->GetSourceLinealPos() ) {
		case EQUIPMENT_WEAPON_RIGHT:
			Right = pItemObj;
			break;
#ifdef KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
		case EQUIPMENT_WEAPON_LEFT:
			Left = pItemObj;
			break;
#endif // KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
		case EQUIPMENT_AMULET:
			Amulet = pItemObj;
			break;
		case EQUIPMENT_RING_RIGHT:
			RRing = pItemObj;
			break;
		case EQUIPMENT_RING_LEFT:
			LRing = pItemObj;
			break;
		}
	}
#endif	// ASG_FIX_PICK_ITEM_FROM_INVEN

    float   percent;
    WORD    DamageMin = 0;
    WORD    DamageMax = 0;

	// ����
    if ( Equipment[EQUIPMENT_WING].Type!=-1 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& Equipment[EQUIPMENT_WING].Durability!=0 && IsRequireEquipItem( &Equipment[EQUIPMENT_WING] )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		)
    {
        //  �����¿� ���� ���ݷ� ����.
        ITEM_ATTRIBUTE *p = &ItemAttribute[Equipment[EQUIPMENT_WING].Type];
        ITEM *ipWing = &Equipment[EQUIPMENT_WING];
        percent = CalcDurabilityPercent(ipWing->Durability,p->Durability,ipWing->Level,0);//ipWing->Option1);

        DamageMin = 0;
        DamageMax = 0;
	    PlusSpecial(&DamageMin,AT_IMPROVE_MAGIC,&Equipment[EQUIPMENT_WING]);
	    PlusSpecial(&DamageMax,AT_IMPROVE_MAGIC,&Equipment[EQUIPMENT_WING]);

        DamageMin = DamageMin - (WORD)(DamageMin*percent);
        DamageMax = DamageMax - (WORD)(DamageMax*percent);

        Character.MagicDamageMin += DamageMin;
        Character.MagicDamageMax += DamageMax;
    }

	// ������ �ɼ� �˻�
    if ( Right->Type!=-1 && Right->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( Right )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE	
		)
	{
        ITEM_ATTRIBUTE *p = &ItemAttribute[Right->Type];
        percent = CalcDurabilityPercent(Right->Durability,p->Durability,Right->Level,Right->Option1,Right->ExtOption);
        DamageMin = 0; DamageMax = 0;
		//	���˻� ������
		// �߰����ݷ� �ɼ� (���˻����� �߰����ݷ¿ɼ��� �߰����µ� �÷��ش�.)
		if ( Right->Type==ITEM_SWORD+21 
			|| Right->Type==ITEM_SWORD+31 
			|| Right->Type==ITEM_SWORD+23
			|| Right->Type==ITEM_SWORD+25
#ifdef KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
 			|| Right->Type==ITEM_SWORD+28
#endif // KJH_FIX_RUNE_BASTARD_SWORD_TOOLTIP
			) // ������ - 2005.9.5 ITEM_SWORD+23 �߰�
		{
			PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,Right);
			PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,Right);
		}
		else
		{
			PlusSpecial(&DamageMin,AT_IMPROVE_MAGIC,Right);
			PlusSpecial(&DamageMax,AT_IMPROVE_MAGIC,Right);
		}

		Character.MagicDamageMin += DamageMin - (WORD)(DamageMin*percent);
		Character.MagicDamageMax += DamageMax - (WORD)(DamageMax*percent);

		// �׼���Ʈ �ɼ�
        PlusSpecial(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_LEVEL,Right);
		PlusSpecial(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_LEVEL,Right);
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,Right,2);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,Right,2);
	}

#ifdef PBG_FIX_SHIELD_MAGICDAMAGE
	// �޼� �ɼ� �˻�
    if ( Left->Type!=-1 && Left->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( Left )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE	
		)
	{
		// ��ȯ������ �޼��� CalculateCurseDamage()���� ��� 
		if (CLASS_SUMMONER != GetBaseClass(Character.Class))	
		{
			ITEM_ATTRIBUTE *p = &ItemAttribute[Left->Type];
			percent = CalcDurabilityPercent(Left->Durability,p->Durability,Left->Level,Left->Option1,Left->ExtOption);
			DamageMin = 0; DamageMax = 0;
			
			if( Left->Type >= ITEM_SWORD && Left->Type < ITEM_SHIELD )
			{
				//	���˻� ������
				// �߰����ݷ� �ɼ� (���˻����� �߰����ݷ¿ɼ��� �߰����µ� �÷��ش�.)
				// (�ٸ����˻����� �μհ��̶� �˻��� �ӿ䰡 ����)
				if ( Left->Type==ITEM_SWORD+28 ) 
				{
					PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,Left);
					PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,Left);
				}
				else
				{
					PlusSpecial(&DamageMin,AT_IMPROVE_MAGIC,Left);
					PlusSpecial(&DamageMax,AT_IMPROVE_MAGIC,Left);
				}
				
				if (GetBaseClass(Character.Class) != CLASS_DARK	// ���˻��� �޼� ����� ���¿� ������ ���� ���Ѵ� (��������)
					)
				{
					Character.MagicDamageMin += DamageMin - (WORD)(DamageMin*percent);
					Character.MagicDamageMax += DamageMax - (WORD)(DamageMax*percent);
				}
				
				// �׼���Ʈ �ɼ�
				PlusSpecial(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_LEVEL,Left);
				PlusSpecial(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_LEVEL,Left);
				PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,Left,2);
				PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,Left,2);
			}
		}
	}
#else // PBG_FIX_SHIELD_MAGICDAMAGE
#ifdef KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
	// �޼� �ɼ� �˻�
    if ( Left->Type!=-1 && Left->Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( Left )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE	
		)
	{
		// ��ȯ������ �޼��� CalculateCurseDamage()���� ��� 
		if (CLASS_SUMMONER != GetBaseClass(Character.Class))	
		{
			ITEM_ATTRIBUTE *p = &ItemAttribute[Left->Type];
			percent = CalcDurabilityPercent(Left->Durability,p->Durability,Left->Level,Left->Option1,Left->ExtOption);
			DamageMin = 0; DamageMax = 0;
			
			//	���˻� ������
			// �߰����ݷ� �ɼ� (���˻����� �߰����ݷ¿ɼ��� �߰����µ� �÷��ش�.)
			// (�ٸ����˻����� �μհ��̶� �˻��� �ӿ䰡 ����)
			if ( Right->Type==ITEM_SWORD+28
				) 
			{
				PlusSpecial(&DamageMin,AT_IMPROVE_DAMAGE,Right);
				PlusSpecial(&DamageMax,AT_IMPROVE_DAMAGE,Right);
			}
			else
			{
				PlusSpecial(&DamageMin,AT_IMPROVE_MAGIC,Right);
				PlusSpecial(&DamageMax,AT_IMPROVE_MAGIC,Right);
			}
			
#ifdef YDG_FIX_LEFTHAND_MAGICDAMAGE
			if (GetBaseClass(Character.Class) != CLASS_DARK	// ���˻��� �޼� ����� ���¿� ������ ���� ���Ѵ� (��������)
			)
#endif	// YDG_FIX_LEFTHAND_MAGICDAMAGE
			{
				Character.MagicDamageMin += DamageMin - (WORD)(DamageMin*percent);
				Character.MagicDamageMax += DamageMax - (WORD)(DamageMax*percent);
			}
			
			// �׼���Ʈ �ɼ�
			PlusSpecial(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_LEVEL,Left);
			PlusSpecial(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_LEVEL,Left);
			PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,Left,2);
			PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,Left,2);
		}
	}
#endif // KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
#endif // PBG_FIX_SHIELD_MAGICDAMAGE

	// �����
    if ( Amulet->Type!=-1 && Amulet->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( Amulet )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE		
		)
	{
		PlusSpecial(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_LEVEL,Amulet);
		PlusSpecial(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_LEVEL,Amulet);
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,Amulet,2);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,Amulet,2);
	}
	// �������� ����
    if ( RRing->Type!=-1 && RRing->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( RRing )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		)
	{
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,RRing,RRing->SpecialValue[0]);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,RRing,RRing->SpecialValue[0]);
#else	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,RRing,10);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,RRing,10);
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
	}
    if ( LRing->Type!=-1 && LRing->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		&& IsRequireEquipItem( LRing )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDAMAGE
		)
	{
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,LRing,LRing->SpecialValue[0]);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,LRing,LRing->SpecialValue[0]);
#else	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
		PlusSpecialPercent(&Character.MagicDamageMin,AT_IMPROVE_MAGIC_PERCENT,LRing,10);
		PlusSpecialPercent(&Character.MagicDamageMax,AT_IMPROVE_MAGIC_PERCENT,LRing,10);
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
	}

	//	��Ʈ �ɼ��� �����Ѵ�.
	WORD MagicDamage = 0;

    MagicDamage = 0;
    g_csItemOption.PlusSpecialLevel ( &MagicDamage, Energy, AT_SET_OPTION_IMPROVE_MAGIC );	//	Ư�� ĳ���� ���� ���� ������/70
	Character.MagicDamageMin += MagicDamage;
	Character.MagicDamageMax += MagicDamage;

#ifdef PSW_SCROLL_ITEM
	if( g_isCharacterBuff((&Hero->Object), eBuff_EliteScroll4) )
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 75);
		Character.MagicDamageMin += Item_data.m_byValue1;
		Character.MagicDamageMax += Item_data.m_byValue1;
	}
#endif //PSW_SCROLL_ITEM
	if(g_isCharacterBuff((&Hero->Object), eBuff_Hellowin2)) // ��������� �г�
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 47);
		Character.MagicDamageMin += Item_data.m_byValue1;
		Character.MagicDamageMax += Item_data.m_byValue1;
	}
#ifdef CSK_EVENT_CHERRYBLOSSOM
	if(g_isCharacterBuff((&Hero->Object), eBuff_CherryBlossom_Petal))  // ���ɲ���
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 87);
		Character.MagicDamageMin += Item_data.m_byValue1;
		Character.MagicDamageMax += Item_data.m_byValue1;
	}
#endif //CSK_EVENT_CHERRYBLOSSOM
#ifdef KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
	if(g_isCharacterBuff((&Hero->Object), eBuff_SwellOfMagicPower))  // ��������
	{
		int iAdd_MP = (CharacterAttribute->Energy/9)*0.2f;
		Character.MagicDamageMin += iAdd_MP;
	}
#endif // KJH_ADD_SKILL_SWELL_OF_MAGICPOWER
#ifdef ADD_SOCKET_STATUS_BONUS
	Character.MagicDamageMin += g_SocketItemMgr.m_StatusBonus.m_iSkillAttackDamageBonus;
	Character.MagicDamageMax += g_SocketItemMgr.m_StatusBonus.m_iSkillAttackDamageBonus;
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
	Character.MagicDamageMin += g_SocketItemMgr.m_StatusBonus.m_iMagicPowerMinBonus;
	Character.MagicDamageMax += g_SocketItemMgr.m_StatusBonus.m_iMagicPowerMaxBonus;
#else	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
	Character.MagicDamageMin += g_SocketItemMgr.m_StatusBonus.m_iMagicPowerBonus;
	Character.MagicDamageMax += g_SocketItemMgr.m_StatusBonus.m_iMagicPowerBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
#endif	// ADD_SOCKET_STATUS_BONUS
#ifdef YDG_ADD_SANTABUFF_MAGIC_DAMAGE
	if(g_isCharacterBuff((&Hero->Object), eBuff_StrengthOfSanta))	//��Ÿ�� ��ȭ
	{
		int _Temp = 30;

		Character.MagicDamageMin += _Temp;
		Character.MagicDamageMax += _Temp;
	}
#endif //YDG_ADD_SANTABUFF_MAGIC_DAMAGE
}

// ���ַ� ������ ���.
void CHARACTER_MACHINE::CalculateCurseDamage()
{
	if (CLASS_SUMMONER != GetBaseClass(Character.Class))	// ��ȯ���縸 ���ַ��� �ʿ��ϴ�.
		return;

	WORD wEnergy = Character.Energy + Character.AddEnergy;  
	Character.CurseDamageMin = wEnergy / 9;
	Character.CurseDamageMax = wEnergy / 4;

	// ����
	ITEM* pEquipWing = &Equipment[EQUIPMENT_WING];
    if (pEquipWing->Type != -1
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_CURSEDAMAGE
		&& IsRequireEquipItem( pEquipWing )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_CURSEDAMAGE		
		)
    {
        ITEM_ATTRIBUTE* pAttribute = &ItemAttribute[pEquipWing->Type];
		WORD wDamageMin = 0;
		WORD wDamageMax = 0;

		// �߰� ���ַ� ���.
		::PlusSpecial(&wDamageMin, AT_IMPROVE_CURSE, pEquipWing);
		::PlusSpecial(&wDamageMax, AT_IMPROVE_CURSE, pEquipWing);

		// �����¿� ���� ���ݷ� ����.
        float fPercent = ::CalcDurabilityPercent(pEquipWing->Durability,
			pAttribute->Durability, pEquipWing->Level, 0);
        wDamageMin -= WORD(wDamageMin * fPercent);
        wDamageMax -= WORD(wDamageMax * fPercent);

        Character.CurseDamageMin += wDamageMin;
        Character.CurseDamageMax += wDamageMax;
    }

	// ��ȯ��
	ITEM* pEquipLeft = &Equipment[EQUIPMENT_WEAPON_LEFT];
	if (pEquipLeft->Type != -1 && pEquipLeft->Durability != 0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_CURSEDAMAGE
		&& IsRequireEquipItem( pEquipLeft )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_CURSEDAMAGE
		)
	{
        ITEM_ATTRIBUTE* pAttribute = &ItemAttribute[pEquipLeft->Type];
		WORD wDamageMin = 0;
		WORD wDamageMax = 0;

		// �߰� ���ַ� ���.
		::PlusSpecial(&wDamageMin, AT_IMPROVE_CURSE, pEquipLeft);
		::PlusSpecial(&wDamageMax, AT_IMPROVE_CURSE, pEquipLeft);
		
		// �����¿� ���� ���ݷ� ����.
		float fPercent = CalcDurabilityPercent(pEquipLeft->Durability,
			pAttribute->Durability, pEquipLeft->Level, pEquipLeft->Option1,
			pEquipLeft->ExtOption);

        Character.CurseDamageMin += wDamageMin - WORD(wDamageMin * fPercent);
        Character.CurseDamageMax += wDamageMax - WORD(wDamageMax * fPercent);

#ifdef KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
		// �׼���Ʈ �ɼ�
		PlusSpecial(&Character.CurseDamageMin,AT_IMPROVE_MAGIC_LEVEL,pEquipLeft);
		PlusSpecial(&Character.CurseDamageMax,AT_IMPROVE_MAGIC_LEVEL,pEquipLeft);
		PlusSpecialPercent(&Character.CurseDamageMin,AT_IMPROVE_MAGIC_PERCENT,pEquipLeft,2);
		PlusSpecialPercent(&Character.CurseDamageMax,AT_IMPROVE_MAGIC_PERCENT,pEquipLeft,2);
#endif // KJH_FIX_WOPS_K27580_EQUIPED_SUMMONING_ITEM
	}
#ifdef YDG_ADD_SANTABUFF_MAGIC_DAMAGE
	if(g_isCharacterBuff((&Hero->Object), eBuff_StrengthOfSanta))	//��Ÿ�� ��ȭ
	{
		int _Temp = 30;

		Character.CurseDamageMin += _Temp;
		Character.CurseDamageMax += _Temp;
	}
#endif //YDG_ADD_SANTABUFF_MAGIC_DAMAGE
}

void CHARACTER_MACHINE::CalculateAttackRating()
{
	WORD Strength, Dexterity, Charisma;

	Strength = Character.Strength + Character.AddStrength;
	Dexterity= Character.Dexterity+ Character.AddDexterity;
    Charisma = Character.Charisma + Character.AddCharisma;

    //  ���� ������.
    if ( GetBaseClass( Character.Class )==CLASS_DARK_LORD )
	    Character.AttackRating  = ((Character.Level*5)+(Dexterity*5)/2)+(Strength/6)+(Charisma/10);
#ifdef PBG_ADD_NEWCHAR_MONK
	else if(GetBaseClass( Character.Class )==CLASS_RAGEFIGHTER)
	{
		Character.AttackRating = ((Character.Level*3)+(Dexterity*5)/4)+(Strength/6);
	}
#endif //PBG_ADD_NEWCHAR_MONK
    else
	    Character.AttackRating  = ((Character.Level*5)+(Dexterity*3)/2)+(Strength/4);

	//	��Ʈ �ɼ��� �����Ѵ�.
	g_csItemOption.PlusSpecial ( &Character.AttackRating, AT_SET_OPTION_IMPROVE_ATTACKING_PERCENT );	//	���� ������ ����

#ifdef ADD_SOCKET_STATUS_BONUS
	Character.AttackRating += g_SocketItemMgr.m_StatusBonus.m_iAttackRateBonus;
#endif	// ADD_SOCKET_STATUS_BONUS
}

void CHARACTER_MACHINE::CalculateAttackRatingPK()
{
	WORD Dexterity;
	Dexterity= Character.Dexterity+ Character.AddDexterity;
    int CharacterClass = GetBaseClass ( Character.Class );

	float tmpf = 0.f;
	switch(CharacterClass)
	{
		case CLASS_KNIGHT:
			tmpf = (float)Character.Level * 3 + (float)Dexterity * 4.5f;
			break;
		case CLASS_DARK_LORD:
			tmpf = (float)Character.Level * 3 + (float)Dexterity * 4.f;
			break;
		case CLASS_ELF:
			tmpf = (float)Character.Level * 3 + (float)Dexterity * 0.6f;
			break;		
		case CLASS_DARK:
		case CLASS_SUMMONER:
			tmpf = (float)Character.Level * 3 + (float)Dexterity * 3.5f;
			break;
		case CLASS_WIZARD:
			tmpf = (float)Character.Level * 3 + (float)Dexterity * 4.f;
			break;
#ifdef PBG_ADD_NEWCHAR_MONK
		case CLASS_RAGEFIGHTER:
			tmpf = (float)Character.Level * 2.6f + (float)Dexterity * 3.6f;
			break;
#endif //PBG_ADD_NEWCHAR_MONK
	}

	Character.AttackRatingPK = (WORD)tmpf;

#ifndef YDG_FIX_SOCKET_BALANCE_PATCH
#ifdef ADD_SOCKET_STATUS_BONUS
	Character.AttackRatingPK += g_SocketItemMgr.m_StatusBonus.m_iPvPAttackRateBonus;
#endif	// ADD_SOCKET_STATUS_BONUS
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
}

void CHARACTER_MACHINE::CalculateAttackSpeed()
{
	WORD Dexterity;
	///////////////////////////////////////////// ĳ���� �⺻ ��ø ��� /////////////////////////////////////////////
	Dexterity= Character.Dexterity+ Character.AddDexterity;

    int CharacterClass = GetBaseClass ( Character.Class );

	if ( CharacterClass==CLASS_ELF )    //  ����.
    {
		Character.AttackSpeed = Dexterity/50;
        Character.MagicSpeed = Dexterity/50;
    }
	else if ( CharacterClass==CLASS_KNIGHT || CharacterClass==CLASS_DARK )  //  20 --> 18  ���. ���˻�.
    {
        Character.AttackSpeed = Dexterity/15;
        Character.MagicSpeed = Dexterity/20;
    }
	
    else if ( CharacterClass==CLASS_DARK_LORD )
    {
		Character.AttackSpeed = Dexterity/10;
        Character.MagicSpeed = Dexterity/10;
    }
	else if (CharacterClass == CLASS_SUMMONER)
    {
		Character.AttackSpeed = Dexterity/20;
        Character.MagicSpeed = Dexterity/20;
    }
#ifdef PBG_ADD_NEWCHAR_MONK
	else if(CharacterClass == CLASS_RAGEFIGHTER)
	{
		Character.AttackSpeed = Dexterity/9;
        Character.MagicSpeed = Dexterity/9;
	}
#endif //PBG_ADD_NEWCHAR_MONK
	else  //  ����.
    {
        Character.AttackSpeed = Dexterity/20;
        Character.MagicSpeed = Dexterity/10;
    }
	///////////////////////////////////////////// ĳ���Ϳ� ������ ������ /////////////////////////////////////////////
	ITEM *r = &Equipment[EQUIPMENT_WEAPON_RIGHT];
	ITEM *l = &Equipment[EQUIPMENT_WEAPON_LEFT ];
	ITEM *g = &Equipment[EQUIPMENT_GLOVES      ];
	ITEM *rl = &Equipment[EQUIPMENT_RING_LEFT   ];
	ITEM *rr = &Equipment[EQUIPMENT_RING_RIGHT  ];
#ifdef LDK_ADD_PC4_GUARDIAN
	ITEM *phelper = &Equipment[EQUIPMENT_HELPER  ];
#endif //LDK_ADD_PC4_GUARDIAN

	SEASON3B::CNewUIPickedItem* pPickedItem = SEASON3B::CNewUIInventoryCtrl::GetPickedItem();
	if(pPickedItem && pPickedItem->GetOwnerInventory() == NULL)	// ���â�� Owner�� NULL�̴�.
	{	
		// �������� �� ���
		ITEM* pItem = pPickedItem->GetItem();
		
		if( pItem )
		{
			int iSourceIndex = pPickedItem->GetSourceLinealPos();
			switch(iSourceIndex)
			{
			case EQUIPMENT_WEAPON_RIGHT:
				r = pItem;
				break;
			case EQUIPMENT_WEAPON_LEFT:
				l = pItem;
				break;
			case EQUIPMENT_GLOVES:
				g = pItem;
				break;
			case EQUIPMENT_RING_LEFT:
				rl = pItem;
				break;
			case EQUIPMENT_RING_RIGHT:
				rr = pItem;
				break;

#ifdef LDK_ADD_PC4_GUARDIAN
			case EQUIPMENT_HELPER:
				phelper = pItem;
				break;
#endif //LDK_ADD_PC4_GUARDIAN
			}
		}
	}

	bool Right		= false;
	bool Left		= false;
	bool Glove		= false;
	bool RingRight	= false;
	bool RingLeft	= false;
#ifdef LDK_ADD_PC4_GUARDIAN
	bool Helper     = false;
#endif //LDK_ADD_PC4_GUARDIAN
    if((r->Type!=ITEM_BOW+7 && r->Type!=ITEM_BOW+15 ) && r->Type>=ITEM_SWORD && r->Type<ITEM_STAFF+MAX_ITEM_INDEX) {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(r) && r->Durability!=0 )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
			Right = true;
		}
	}

    if((l->Type!=ITEM_BOW+7 && l->Type!=ITEM_BOW+15 ) && l->Type>=ITEM_SWORD && l->Type<ITEM_STAFF+MAX_ITEM_INDEX) {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(l) && l->Durability!=0 )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
			Left = true;
		}
	}

	if(g->Durability!=0 && g->Type != -1) {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(g) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
			Glove = true;
		}
	}

    if ( rl->Durability!=0 &&
		(rl->Type == ITEM_HELPER+20
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		|| rl->Type == ITEM_HELPER+107		// ġ�� ��������
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
		) )
    {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(rl) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
#ifdef LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
			if(false == rl->bPeriodItem || false == rl->bExpiredPeriod)
			{
				switch ( rl->Level>>3 )
				{
				case 0:
				case 3:
					RingRight = true;
					break;
				}
			}
#else // LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
			switch ( rl->Level>>3 )
			{
			case 0:
			case 3:
				RingRight = true;
				break;
			}
#endif // LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
		}
    }

    if ( rr->Durability!=0 && (rr->Type == ITEM_HELPER+20
#ifdef YDG_ADD_CS7_CRITICAL_MAGIC_RING
		|| rr->Type == ITEM_HELPER+107		// ġ�� ��������
#endif	// YDG_ADD_CS7_CRITICAL_MAGIC_RING
		) ) {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(rr) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
#ifdef LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
			if(false == rr->bPeriodItem || false == rr->bExpiredPeriod)
			{
				switch ( rr->Level>>3 )
				{
				case 0:
				case 3:
					RingLeft = true;
					break;
				}
			}
#else // LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
			switch ( rr->Level>>3 )
			{
			case 0:
			case 3:
				RingLeft = true;
				break;
			}
#endif // LDK_FIX_EQUIPED_EXPIREDPERIOD_RING_EXCEPTION
		}
    }

#ifdef LDK_ADD_PC4_GUARDIAN
	if( phelper->Durability != 0 && 
		(phelper->Type == ITEM_HELPER+64
#ifdef YDG_ADD_SKELETON_PET
		|| phelper->Type == ITEM_HELPER+123	// ���̷��� ��
#endif	// YDG_ADD_SKELETON_PET
		)
		)
	{
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		if( IsRequireEquipItem(phelper) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_ATTACKSPEED
		{
#ifdef LDK_MOD_PC4_GUARDIAN_EXPIREDPERIOD_NOTPRINT_INFO
			//����� �Ⱓ�� �������̸� ��� ����
			if(false == phelper->bPeriodItem || false == phelper->bExpiredPeriod)
			{
				Helper = true;
			}
#else //LDK_MOD_PC4_GUARDIAN_EXPIREDPERIOD_NOTPRINT_INFO
			Helper = true;
#endif //LDK_MOD_PC4_GUARDIAN_EXPIREDPERIOD_NOTPRINT_INFO
		}
	}
#endif //LDK_ADD_PC4_GUARDIAN

    int RightWeaponSpeed = r->WeaponSpeed;
    int LeftWeaponSpeed  = l->WeaponSpeed;

    if ( r->Durability<=0 ) RightWeaponSpeed = 0;
    if ( l->Durability<=0 ) LeftWeaponSpeed = 0;

    if(Right && Left)
    {
     	Character.AttackSpeed += (RightWeaponSpeed+LeftWeaponSpeed)/2;
     	Character.MagicSpeed += (RightWeaponSpeed+LeftWeaponSpeed)/2;
    }
	else if(Right)
    {
        Character.AttackSpeed += RightWeaponSpeed;
        Character.MagicSpeed += RightWeaponSpeed;
    }
	else if(Left)
    {
        Character.AttackSpeed += LeftWeaponSpeed;
        Character.MagicSpeed += LeftWeaponSpeed;
    }
	
	if(RingRight)	// �������� ���� ȿ��
    {
        Character.AttackSpeed += 10;
        Character.MagicSpeed += 10;
		CharacterAttribute->Ability |= ABILITY_FAST_ATTACK_RING;
    }
	else if(RingLeft)	// �������� ���� ȿ��
    {
        Character.AttackSpeed += 10;
        Character.MagicSpeed += 10;
		CharacterAttribute->Ability |= ABILITY_FAST_ATTACK_RING;
    }
	else if (CharacterAttribute->Ability & ABILITY_FAST_ATTACK_RING)
	{
		CharacterAttribute->Ability &= (~ABILITY_FAST_ATTACK_RING);
	}

    //  �尩 �ӵ�.
	if(Glove)
    {
        Character.AttackSpeed += g->WeaponSpeed;
        Character.MagicSpeed += g->WeaponSpeed;
    }

#ifdef LDK_ADD_PC4_GUARDIAN
	if(Helper)
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_HELPER+64);
        Character.AttackSpeed += Item_data.m_byValue2;
        Character.MagicSpeed += Item_data.m_byValue2;
	}
#endif //LDK_ADD_PC4_GUARDIAN

#ifdef YDG_ADD_SKELETON_PET
	if(Helper)	// ���̷��� ��
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_HELPER+123);
        Character.AttackSpeed += Item_data.m_byValue2;
        Character.MagicSpeed += Item_data.m_byValue2;
	}
#endif	// YDG_ADD_SKELETON_PET

	if(Character.Ability & ABILITY_FAST_ATTACK_SPEED)
    {
        Character.AttackSpeed += 20;
        Character.MagicSpeed += 20;
    }
	else if ( Character.Ability&ABILITY_FAST_ATTACK_SPEED2 )	//. ��ȥ�� ���� ���� ����
    {
        Character.AttackSpeed += 20;
        Character.MagicSpeed += 20;
    }
#ifdef LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
	ITEM *Amulet = &Equipment[EQUIPMENT_AMULET];
	
#ifdef LDK_FIX_EQUIPED_EXPIREDPERIOD_AMULET_EXCEPTION
	//����� �Ⱓ�� �������̸� ��� ����
	if( (false == Amulet->bPeriodItem || false == Amulet->bExpiredPeriod)
		&& Amulet->Type == ITEM_HELPER + 114 )
#else //LDK_FIX_EQUIPED_EXPIREDPERIOD_AMULET_EXCEPTION
	if( Amulet->Type == ITEM_HELPER + 114 )		// AMULETEMERALD
#endif //LDK_FIX_EQUIPED_EXPIREDPERIOD_AMULET_EXCEPTION
	{
		//�������� +7
		int _Temp = 7;
		
		Character.AttackSpeed += _Temp;
		Character.MagicSpeed += _Temp;
		//Character.AttackSpeed += Amulet->WeaponSpeed;	// �������� �Ѿ���� ��? ���� Ȯ�λ���.
		//Character.MagicSpeed += Amulet->WeaponSpeed;
	}
#endif // LDS_MOD_INGAMESHOPITEM_RING_AMULET_CHARACTERATTR
	
	///////////////////////////////////////// ĳ���� ���� ( ���� ) ///////////////////////////////////////// 
#ifdef PSW_SCROLL_ITEM
	if(g_isCharacterBuff((&Hero->Object), eBuff_EliteScroll1))  // �ż��� ��ũ��
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 72);
		Character.AttackSpeed += Item_data.m_byValue1;
		Character.MagicSpeed += Item_data.m_byValue1;
	}
#endif// PSW_SCROLL_ITEM
#ifdef HELLOWIN_EVENT
	if(g_isCharacterBuff((&Hero->Object), eBuff_Hellowin1))	// ��������� �ູ
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 46);
		Character.AttackSpeed += Item_data.m_byValue1;
		Character.MagicSpeed += Item_data.m_byValue1;
	}
#endif //HELLOWIN_EVENT
#ifdef PBG_ADD_SANTABUFF
	if(g_isCharacterBuff((&Hero->Object), eBuff_QuickOfSanta))	//��Ÿ�� �ż�
	{
		//�������� +15
		int _Temp = 15;
		Character.AttackSpeed += _Temp;
		Character.MagicSpeed += _Temp;
	}
#endif //PBG_ADD_SANTABUFF

	///////////////////////////////////////////// ������Ʈ �ɼ� ///////////////////////////////////////////// 
	// ���� ���ǵ� ���� ��� ������Ʈ �ɼǿ� ���ǵ� ���� �ɼ��� ������ ������ �ɼǰ��� �ι����� ����.
	// ���������� �������� ���鶧 ������Ʈ �ɼ��� �����ְ� �� ���� �ܰ��� ĳ���� ���� ����� �Ҷ� �� �ϹǷ�
	// �����ɼ��� ���� 7������ ������ ������ 14 Ŭ�� 7�� ���� �ȴ�.
	PlusSpecial(&Character.AttackSpeed,AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_WEAPON_RIGHT]);
	PlusSpecial(&Character.MagicSpeed, AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_WEAPON_RIGHT]);
	PlusSpecial(&Character.AttackSpeed,AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_WEAPON_LEFT]);
	PlusSpecial(&Character.MagicSpeed, AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_WEAPON_LEFT]);
	PlusSpecial(&Character.AttackSpeed,AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_AMULET]);
	PlusSpecial(&Character.MagicSpeed, AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_AMULET]);
	PlusSpecial(&Character.AttackSpeed, AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_HELPER]);
	PlusSpecial(&Character.MagicSpeed, AT_IMPROVE_ATTACK_SPEED,&Equipment[EQUIPMENT_HELPER]);
	///////////////////////////////////////////// ���� ������ /////////////////////////////////////////////
#ifdef ADD_SOCKET_STATUS_BONUS
	Character.AttackSpeed += g_SocketItemMgr.m_StatusBonus.m_iAttackSpeedBonus;
	Character.MagicSpeed += g_SocketItemMgr.m_StatusBonus.m_iAttackSpeedBonus;
#endif	// ADD_SOCKET_STATUS_BONUS
	///////////////////////////////////////////// ���� ������ /////////////////////////////////////////////
}

void CHARACTER_MACHINE::CalculateSuccessfulBlockingPK()
{
	WORD Dexterity;
	Dexterity= Character.Dexterity+ Character.AddDexterity;
    int CharacterClass = GetBaseClass ( Character.Class );

	float tmpf = 0.f;
	switch(CharacterClass)
	{
		case CLASS_KNIGHT:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.5f;
			break;
		case CLASS_DARK_LORD:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.5f;
			break;
		case CLASS_ELF:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.1f;
			break;		
		case CLASS_DARK:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.25f;
			break;
		case CLASS_WIZARD:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.25f;
			break;
		case CLASS_SUMMONER:
			tmpf = (float)Character.Level * 2 + (float)Dexterity * 0.5f;
			break;
#ifdef PBG_ADD_NEWCHAR_MONK
		case CLASS_RAGEFIGHTER:
			tmpf = (float)Character.Level * 1.5f + (float)Dexterity * 0.2f;
			break;
#endif //PBG_ADD_NEWCHAR_MONK
	}
	Character.SuccessfulBlockingPK = (WORD)tmpf;
	hanguo_check3();
}

// ����� ��� �Լ�
void CHARACTER_MACHINE::CalculateSuccessfulBlocking()
{
	WORD Dexterity;

	// ĳ������ ��ø�� + �߰� ��ø���� ���Ѵ�.
	Dexterity= Character.Dexterity+ Character.AddDexterity;

    int CharacterClass = GetBaseClass ( Character.Class );

	if (CharacterClass==CLASS_ELF || CharacterClass==CLASS_SUMMONER)
	{
		// ����, ��ȯ����� ���� ��ø���� / 4 �� �Է�
        Character.SuccessfulBlocking = Dexterity/4;
	}
    else if ( CharacterClass==CLASS_DARK_LORD )
	{
		// ��ũ�ε�� ���� ��ø���� / 7 �� ����
        Character.SuccessfulBlocking = Dexterity/7;
	}
#ifdef PBG_ADD_NEWCHAR_MONK
	else if(CharacterClass==CLASS_RAGEFIGHTER)
	{
		Character.SuccessfulBlocking = Dexterity/10;
	}
#endif //PBG_ADD_NEWCHAR_MONK
	else
	{
		// ���, �渶����, ������ ���� ��ø���� / 3 �� ����
      	Character.SuccessfulBlocking = Dexterity/3;
	}

	// ���� ���Ⱑ �������� 0�� �ƴ϶��
	ITEM* Left = &Equipment[EQUIPMENT_WEAPON_LEFT];
    if ( Left->Type!=-1 && Left->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING
		&& IsRequireEquipItem( Left )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING	
		)
	{
        ITEM_ATTRIBUTE* p = &ItemAttribute[Left->Type];
        float percent = CalcDurabilityPercent(Left->Durability,p->Durability,Left->Level,Left->Option1,Left->ExtOption);

        WORD SuccessBlocking = 0;
        SuccessBlocking = Left->SuccessfulBlocking - (WORD)(Left->SuccessfulBlocking*percent);

		// ���� ������ ������ �����ְ�
		Character.SuccessfulBlocking += SuccessBlocking;
        
        SuccessBlocking = 0;
        PlusSpecial(&SuccessBlocking,AT_IMPROVE_BLOCKING,Left);

		// ���� ���⿡ �߰� ������� �ִٸ� ���� �����ش�.
        Character.SuccessfulBlocking += SuccessBlocking - (WORD)(SuccessBlocking*percent);

		// ���� ���⿡ ��� �������� �ִٸ� ����ؼ� �����ش�.
        PlusSpecialPercent(&Character.SuccessfulBlocking,AT_IMPROVE_BLOCKING_PERCENT,Left,10);
	}

	// �ٸ� ���鿡�� ��� �������� �ִٸ� ����ؼ� �����ش�.
	// �۸�
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_HELM],10 );
	// ����
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_ARMOR],10 );
	// ����
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_PANTS],10 );
	// �尩
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_GLOVES],10 );
	// �Ź�
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_BOOTS],10 );
	// ���� ����
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_RING_LEFT],10 );
	// ���� ������
    PlusSpecialPercent ( &Character.SuccessfulBlocking, AT_IMPROVE_BLOCKING_PERCENT, &Equipment[EQUIPMENT_RING_RIGHT],10 );
	hanguo_check3();

#ifdef ADD_SOCKET_STATUS_BONUS

#ifndef YDG_FIX_SOCKET_SHIELD_BONUS	// �����Ҷ� �����ؾ���
	// ���� ���Ⱑ �������� 0�� �ƴ϶��
    if ( Left->Type!=-1 && Left->Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING
		&& IsRequireEquipItem( Left )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING	
		)
	{
		// ���������������� ����ȴ�
		Character.SuccessfulBlocking += g_SocketItemMgr.m_StatusBonus.m_iShieldDefenceBonus;
	}
#endif	// YDG_FIX_SOCKET_SHIELD_BONUS

#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
	Character.SuccessfulBlocking *= g_SocketItemMgr.m_StatusBonus.m_fDefenceRateBonus;
#else	// YDG_FIX_SOCKET_BALANCE_PATCH
#ifdef YDG_FIX_SOCKET_ITEM_DEFENCE_RATE_BONUS
	Character.SuccessfulBlocking *= 1.0f + g_SocketItemMgr.m_StatusBonus.m_iDefenceRateBonus * 0.01f;
#else	// YDG_FIX_SOCKET_ITEM_DEFENCE_RATE_BONUS
	Character.SuccessfulBlocking += g_SocketItemMgr.m_StatusBonus.m_iDefenceRateBonus;
#endif	// YDG_FIX_SOCKET_ITEM_DEFENCE_RATE_BONUS
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
#endif	// ADD_SOCKET_STATUS_BONUS
}

void CHARACTER_MACHINE::CalculateDefense()
{
	WORD Dexterity, Vitality;

	Dexterity= Character.Dexterity+ Character.AddDexterity;
    Vitality = Character.Vitality + Character.AddVitality;

    int CharacterClass = GetBaseClass ( Character.Class );

	if ( CharacterClass==CLASS_ELF )
    {
        Character.Defense  = Dexterity/10;
    }
	else if (CharacterClass==CLASS_KNIGHT || CharacterClass==CLASS_SUMMONER)
    {
        Character.Defense  = Dexterity/3;
    }
	else if ( CharacterClass==CLASS_WIZARD )
    {
        Character.Defense  = Dexterity/4;
    }
	else if ( CharacterClass==CLASS_DARK_LORD )
    {
        Character.Defense  = Dexterity/7;
    }
#ifdef PBG_ADD_NEWCHAR_MONK
	else if ( CharacterClass==CLASS_RAGEFIGHTER )
    {
        Character.Defense  = Dexterity/8;
    }
#endif //PBG_ADD_NEWCHAR_MONK
	else
    {
		// ���˻� / ��ũ
        Character.Defense  = Dexterity/5;
    }

    WORD    Defense = 0;
    for( int i=EQUIPMENT_WEAPON_LEFT; i<=EQUIPMENT_WING; ++i )
    {
        if( Equipment[i].Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE	
			&& IsRequireEquipItem(&Equipment[i])
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE
			)
        {
            WORD defense = ItemDefense(&Equipment[i]);

            //  �����¿� ���� ���ݷ� ����.
            ITEM_ATTRIBUTE *p = &ItemAttribute[Equipment[i].Type];
            float percent;
            if ( i==EQUIPMENT_WING )
            {
                //  ����.
                percent = CalcDurabilityPercent(Equipment[i].Durability,p->Durability,Equipment[i].Level,0);//Equipment[i].Option1);
            }
            else
            {
                percent = CalcDurabilityPercent(Equipment[i].Durability,p->Durability,Equipment[i].Level,Equipment[i].Option1,Equipment[i].ExtOption);
            }

            defense -= (WORD)(defense*percent);

            Defense += defense;
        }
    }
    Character.Defense += Defense;

    //  +10, +11�� ��� �߰� ����.
    if ( g_bAddDefense )
    {
        float addDefense = 0.f;
        switch ( EquipmentLevelSet )
        {
        case 10:
            addDefense = 0.05f;
            break;
        case 11:
            addDefense = 0.1f;
            break;
        case 12:
            addDefense = 0.15f;
            break;
        case 13:
            addDefense = 0.2f;
            break;
#ifdef LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
        case 14:
            addDefense = 0.25f;
            break;
        case 15:
            addDefense = 0.3f;
            break;
#endif //LDK_ADD_14_15_GRADE_ITEM_HELP_INFO
        }
        Character.Defense += (WORD)(Character.Defense*addDefense);
    }

#ifdef PSW_SCROLL_ITEM
	if(g_isCharacterBuff((&Hero->Object), eBuff_EliteScroll2))  // ����� ��ũ��
	{
		const ITEM_ADD_OPTION& Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 73);
		Character.Defense += (WORD)Item_data.m_byValue1;
	}
#endif// PSW_SCROLL_ITEM
#ifdef HELLOWIN_EVENT
	if(g_isCharacterBuff((&Hero->Object), eBuff_Hellowin3)) // ��������� ��ħ
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 48);
		Character.Defense += (WORD)Item_data.m_byValue1;
	}
#endif //HELLOWIN_EVENT
#ifdef PBG_ADD_SANTABUFF
	if(g_isCharacterBuff((&Hero->Object), eBuff_BlessingOfXmax))	//ũ���������� �ູ
	{
		int _Temp = 0;
		_Temp = Character.Level / 5 + 50;
		
		Character.Defense += _Temp;
	}

	if(g_isCharacterBuff((&Hero->Object), eBuff_DefenseOfSanta))	//��Ÿ�� ���
	{
		int _Temp = 100;
		Character.Defense += _Temp;
	}
#endif //PBG_ADD_SANTABUFF

#ifdef LDS_ADD_PCROOM_ITEM_JPN_6TH
	if(g_isCharacterBuff((&Hero->Object), eBuff_StrongCharm))		//������ ����(PC�� ������)
	{
		int _Temp = 60;
		Character.Defense += _Temp;
	}
#endif // LDS_ADD_PCROOM_ITEM_JPN_6TH

	//	��Ʈ �ɼ��� �����Ѵ�.
    g_csItemOption.PlusSpecial ( &Character.Defense, AT_SET_OPTION_IMPROVE_DEFENCE );         //	���� ����

	g_csItemOption.PlusSpecialLevel ( &Character.Defense, Dexterity, AT_SET_OPTION_IMPROVE_DEFENCE_3 );         //	Ư�� ĳ���� ���� ���� ��ø��/50	
	g_csItemOption.PlusSpecialLevel ( &Character.Defense, Vitality, AT_SET_OPTION_IMPROVE_DEFENCE_4 );          //	Ư�� ĳ���� ���� ���� ü��/40		    

    if ( Equipment[EQUIPMENT_WEAPON_LEFT].Type>=ITEM_SHIELD && Equipment[EQUIPMENT_WEAPON_LEFT].Type<ITEM_SHIELD+MAX_ITEM_INDEX )
    {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE
		if( IsRequireEquipItem( &Equipment[EQUIPMENT_WEAPON_LEFT]) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE
		{
			g_csItemOption.PlusSpecialPercent ( &Character.Defense, AT_SET_OPTION_IMPROVE_SHIELD_DEFENCE );         //	���� ���� ���� 5% ����
		}
    }

    PlusSpecial ( &Character.Defense, AT_SET_OPTION_IMPROVE_DEFENCE, &Equipment[EQUIPMENT_HELPER] );
    if ( Equipment[EQUIPMENT_WING].Type==ITEM_HELPER+30 
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
		|| Equipment[EQUIPMENT_WING].Type==ITEM_WING+49
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		)   //  ����.
    {
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE
		if( IsRequireEquipItem( &Equipment[EQUIPMENT_WING]) )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_DEFENSE
		{
			PlusSpecial ( &Character.Defense, AT_SET_OPTION_IMPROVE_DEFENCE, &Equipment[EQUIPMENT_WING] );
		}
    }

#ifdef ADD_SOCKET_STATUS_BONUS
	Character.Defense += g_SocketItemMgr.m_StatusBonus.m_iDefenceBonus;
#endif	// ADD_SOCKET_STATUS_BONUS

#ifdef YDG_FIX_SOCKET_SHIELD_BONUS
	// ���� ���Ⱑ �������� 0�� �ƴ϶��
    if ( Equipment[EQUIPMENT_WEAPON_LEFT].Type!=-1 && Equipment[EQUIPMENT_WEAPON_LEFT].Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING
		&& IsRequireEquipItem( Equipment[EQUIPMENT_WEAPON_LEFT] )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SUCCESSFULBLOCKING	
		)
	{
		// ���������������� ����ȴ�
		Character.Defense += Equipment[EQUIPMENT_WEAPON_LEFT].Defense * g_SocketItemMgr.m_StatusBonus.m_iShieldDefenceBonus * 0.01f;
	}
#endif	// YDG_FIX_SOCKET_SHIELD_BONUS
}

void CHARACTER_MACHINE::CalculateMagicDefense()
{
    for( int i=EQUIPMENT_HELM; i<=EQUIPMENT_WING; ++i )
    {
        if( Equipment[i].Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDEFENSE
			&& IsRequireEquipItem( &Equipment[i] )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_MAGICDEFENSE
			)
        {
            Character.MagicDefense  = ItemMagicDefense(&Equipment[i]);
        }
    }
//	Character.MagicDefense  = ItemMagicDefense(&Equipment[EQUIPMENT_HELM]);
//	Character.MagicDefense += ItemMagicDefense(&Equipment[EQUIPMENT_ARMOR]);
//	Character.MagicDefense += ItemMagicDefense(&Equipment[EQUIPMENT_PANTS]);
//	Character.MagicDefense += ItemMagicDefense(&Equipment[EQUIPMENT_GLOVES]);
//	Character.MagicDefense += ItemMagicDefense(&Equipment[EQUIPMENT_BOOTS]);
//	Character.MagicDefense += ItemMagicDefense(&Equipment[EQUIPMENT_WING]);
}

void CHARACTER_MACHINE::CalculateWalkSpeed()
{
    if( Equipment[EQUIPMENT_BOOTS].Durability!=0
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_WALKSPEED
		&& IsRequireEquipItem( &Equipment[EQUIPMENT_BOOTS] )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_WALKSPEED
		)
    {
	    Character.WalkSpeed  = ItemWalkSpeed(&Equipment[EQUIPMENT_BOOTS]);
    }

    if( Equipment[EQUIPMENT_WING].Durability!=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_WALKSPEED
		&& IsRequireEquipItem( &Equipment[EQUIPMENT_WING] )
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_WALKSPEED
		)
    {
	    Character.WalkSpeed += ItemWalkSpeed(&Equipment[EQUIPMENT_WING]);
    }
}

//(10+l)*l/4
//(4+l)*l*l*20
void CHARACTER_MACHINE::CalculateNextExperince()
{
	// ������ ���� ����̴ϱ�
	// ���� ����ġ�� ��������ġ�� �ʱ�ȭ
	Character.Experience = Character.NextExperince;

	// ���� ����ġ ���� ������
	Character.NextExperince = (9+Character.Level)*(Character.Level)*(Character.Level)*10;

    if ( Character.Level > 255 )
    {
        int LevelOver_N = Character.Level - 255;
        Character.NextExperince += (9+LevelOver_N)*LevelOver_N*LevelOver_N*1000;
    }
}

void CHARACTER_MACHINE::CalulateMasterLevelNextExperience()
{
	// ������ ���� ����̴ϱ�
	// ���� ����ġ�� ��������ġ�� �ʱ�ȭ
	Master_Level_Data.lMasterLevel_Experince = Master_Level_Data.lNext_MasterLevel_Experince;

	__int64 iTotalLevel = CharacterAttribute->Level + Master_Level_Data.nMLevel + 1;	// ���շ���
	__int64 iTOverLevel = iTotalLevel - 255;		// 255���� �̻� ���� ����
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	__int64 iBaseExperience = 0;					// ���� �ʱ� ����ġ
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	
	__int64 iData_Master =	// A
		(
		(
		(__int64)9 + (__int64)iTotalLevel
		)
		* (__int64)iTotalLevel
		* (__int64)iTotalLevel
		* (__int64)10
		)
		+
		(
		(
		(__int64)9 + (__int64)iTOverLevel
		)
		* (__int64)iTOverLevel
		* (__int64)iTOverLevel
		* (__int64)1000
		);

	Master_Level_Data.lNext_MasterLevel_Experince = ( iData_Master - (__int64)3892250000 ) / (__int64)2;	// B
}

bool CHARACTER_MACHINE::IsZeroDurability()
{
    for ( int i=EQUIPMENT_WEAPON_RIGHT; i<MAX_EQUIPMENT; ++i )
    {
        if ( Equipment[i].Durability==0 )
        {
            return  true;
        }
    }

    return  false;
}

#ifdef PSW_SECRET_ITEM
void CHARACTER_MACHINE::CalculateBasicState()
{
	if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion1)) // ��
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 78);
		Character.AddStrength += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion2)) // ��ø
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 79);
		Character.AddDexterity += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion3)) // ü��
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 80);
		Character.AddVitality += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion4)) // ������
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 81);
		Character.AddEnergy += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion5)) // ���
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 82);
		Character.AddCharisma += (WORD)Item_data.m_byValue1;
	}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(g_isCharacterBuff((&Hero->Object), eBuff_Hp_up_Ourforces))
	{
#ifdef PBG_MOD_RAGEFIGHTERSOUND
		WORD _AddStat = (WORD)(30+(WORD)((Character.Energy-132)/10));
#else //PBG_MOD_RAGEFIGHTERSOUND
		WORD _AddStat = (WORD)(30+(WORD)((Character.Energy-380)/10));
#endif //PBG_MOD_RAGEFIGHTERSOUND
		if(_AddStat > 200)
		{
			_AddStat = 200;
		}
		Character.AddVitality += _AddStat;
	}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#ifndef YDG_FIX_DOUBLE_SOCKETITEM_BONUS
#ifdef SOCKET_SYSTEM
	// ���� ��Ʈ �ɼ��� �˻��Ѵ�.
	g_SocketItemMgr.CheckSocketSetOption();
	g_SocketItemMgr.CalcSocketStatusBonus();
	CharacterMachine->Character.AddStrength  += g_SocketItemMgr.m_StatusBonus.m_iStrengthBonus;
	CharacterMachine->Character.AddDexterity += g_SocketItemMgr.m_StatusBonus.m_iDexterityBonus;
	CharacterMachine->Character.AddVitality  += g_SocketItemMgr.m_StatusBonus.m_iVitalityBonus;
	CharacterMachine->Character.AddEnergy    += g_SocketItemMgr.m_StatusBonus.m_iEnergyBonus;
#endif	// SOCKET_SYSTEM
#endif	// YDG_FIX_DOUBLE_SOCKETITEM_BONUS
}

#endif //PSW_SECRET_ITEM


#ifdef LDS_FIX_APPLY_BUFF_STATEVALUES_WHEN_CALCULATE_CHARACTERSTATE_WITH_SETITEM
void CHARACTER_MACHINE::getAllAddStateOnlyExValues( int &iAddStrengthExValues, 
												int &iAddDexterityExValues, 
												int &iAddVitalityExValues,
												int &iAddEnergyExValues, 
												int &iAddCharismaExValues )
{
	if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion1)) // ��
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 78);
		iAddStrengthExValues += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion2)) // ��ø
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 79);
		iAddDexterityExValues += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion3)) // ü��
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 80);
		iAddVitalityExValues += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion4)) // ������
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 81);
		iAddEnergyExValues += (WORD)Item_data.m_byValue1;
	}
	else if(g_isCharacterBuff((&Hero->Object), eBuff_SecretPotion5)) // ���
	{
		ITEM_ADD_OPTION Item_data = g_pItemAddOptioninfo->GetItemAddOtioninfo(ITEM_POTION + 82);
		iAddCharismaExValues += (WORD)Item_data.m_byValue1;
	}
	
#ifdef SOCKET_SYSTEM
	// ���� ��Ʈ �ɼ��� �˻��Ѵ�. �̹� ������ ���� ������ ��� �Լ��� �ѹ� ȣ�� �Ͽ����Ƿ� ���δ� ����.
	//g_SocketItemMgr.CheckSocketSetOption();
	//g_SocketItemMgr.CalcSocketStatusBonus();
	iAddStrengthExValues  += g_SocketItemMgr.m_StatusBonus.m_iStrengthBonus;
	iAddDexterityExValues += g_SocketItemMgr.m_StatusBonus.m_iDexterityBonus;
	iAddVitalityExValues  += g_SocketItemMgr.m_StatusBonus.m_iVitalityBonus;
	iAddEnergyExValues    += g_SocketItemMgr.m_StatusBonus.m_iEnergyBonus;
#endif	// SOCKET_SYSTEM
}
#endif // LDS_FIX_APPLY_BUFF_STATEVALUES_WHEN_CALCULATE_CHARACTERSTATE_WITH_SETITEM



#ifdef ANTIHACKING_ENABLE
extern BOOL g_bNewFrame;
#endif //ANTIHACKING_ENABLE

void CHARACTER_MACHINE::CalculateAll()
{
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM

	// ĳ���� add ���� �ʱ�ȭ
	InitAddValue ();

#ifdef PSW_SECRET_ITEM
	// ���� ȿ���� �߿� �⺻ ������ �÷� �ٰ��� ������ ���⼭ �Ѵ�. 
	// SOCKET_SYSTEM define �߰� �Ǿ�����.
	CalculateBasicState();
#endif //PSW_SECRET_ITEM

	//	�������� ���ŵǾ��ٸ� �ٽ� ��Ʈ �ɼ��� �˻��Ѵ�.
	//	ĳ���� ����â�� ���������.
	g_csItemOption.CheckItemSetOptions ();
	g_csItemOption.ClearListOnOff();
 
#else //PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM           // ���� �ؾ� �� �ڵ�

#if defined PSW_SECRET_ITEM && defined LDK_FIX_USE_SECRET_ITEM_TO_SETITEM_OPTION_BUG
	// ��� ����� add�� ����.
	// ���� ȿ���� �߿� �⺻ ������ �÷� �ٰ��� ������ ���⼭ �Ѵ�. 
	// SOCKET_SYSTEM define �߰� �Ǿ�����.
	CalculateBasicState();
#endif //PSW_SECRET_ITEM

	//	�������� ���ŵǾ��ٸ� �ٽ� ��Ʈ �ɼ��� �˻��Ѵ�.
	//	ĳ���� ����â�� ���������.
	g_csItemOption.CheckItemSetOptions ();
	g_csItemOption.ClearListOnOff();
	// ĳ���� add ���� �ʱ�ȭ
	InitAddValue ();

#ifdef SOCKET_SYSTEM
	// ���� ��Ʈ �ɼ��� �˻��Ѵ�.
	g_SocketItemMgr.CheckSocketSetOption();
	g_SocketItemMgr.CalcSocketStatusBonus();
	CharacterMachine->Character.AddStrength  += g_SocketItemMgr.m_StatusBonus.m_iStrengthBonus;
	CharacterMachine->Character.AddDexterity += g_SocketItemMgr.m_StatusBonus.m_iDexterityBonus;
	CharacterMachine->Character.AddVitality  += g_SocketItemMgr.m_StatusBonus.m_iVitalityBonus;
	CharacterMachine->Character.AddEnergy    += g_SocketItemMgr.m_StatusBonus.m_iEnergyBonus;
#endif	// SOCKET_SYSTEM
 
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM           // ���� �ؾ� �� �ڵ�
#ifdef PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION
	CalculateBasicState();
#endif //PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION

	// ��Ʈ ������ �� �ɼ� ���� �κ� ����
	// ============================================================================== >
	// ���� �������� ���뿡 ���� ��� ���� ��ġ ���� ��� ����, �̴� 
	// ��Ʈ �������� ������ �ִ� ��Ʈ �ɼ� �� �⺻ �ɼ� ���� ��ġ�� ���Ե˴ϴ�.
#ifdef LDS_FIX_WRONG_CALCULATEEQUIPEDITEMOPTIONVALUE
	WORD	wAddStrength, wAddDexterity, wAddEnergy, wAddVitality,
		wStrengthResult, wDexterityResult, wEnergyResult, wVitalityResult;
	wAddStrength = wAddDexterity = wAddEnergy = wAddVitality = 0;
	wStrengthResult = wDexterityResult = wEnergyResult = wVitalityResult = 0;

	// ��Ʈ �ɼ� ��ġ�� "���" ��ġ�� �ݿ� �մϴ�.
#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	WORD wAddCharisma, wCharismaResult; 
	wAddCharisma = wCharismaResult = 0;
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	
	// ��Ʈ �ɼ� ��ġ�� �߰��� �߰� ���� ��ġ���� �����ɴϴ�.	// 1.���� �ɷ�ġ 2. ���� ������ �ɷ�ġ ����
#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	g_csItemOption.getAllAddStateOnlyAddValue( &wAddStrength, &wAddDexterity, &wAddEnergy, &wAddVitality, &wAddCharisma );
#else // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	g_csItemOption.getAllAddStateOnlyAddValue( &wAddStrength, &wAddDexterity, &wAddEnergy, &wAddVitality );
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	
	// ��Ʈ �����۵鿡 ���� ������ �䱸 ��ġ ������� 
#ifdef LDS_FIX_APPLY_BUFF_STATEVALUES_WHEN_CALCULATE_CHARACTERSTATE_WITH_SETITEM
	int iAddStrengthByExValues, iAddDexterityByExValues, 
		iAddEnergyByExValues, iAddVitalityByExValues, 
		iAddCharismaExValues;

	iAddStrengthByExValues = iAddDexterityByExValues 
		= iAddEnergyByExValues = iAddVitalityByExValues = iAddCharismaExValues = 0;

	getAllAddStateOnlyExValues( iAddStrengthByExValues, 
								iAddDexterityByExValues, 
								iAddVitalityByExValues, 
								iAddEnergyByExValues, 
								iAddCharismaExValues );

	wAddStrength	+= iAddStrengthByExValues;
	wAddDexterity	+= iAddDexterityByExValues;
	wAddEnergy		+= iAddEnergyByExValues;
	wAddVitality	+= iAddVitalityByExValues;
#endif // LDS_FIX_APPLY_BUFF_STATEVALUES_WHEN_CALCULATE_CHARACTERSTATE_WITH_SETITEM

	// �ɸ����� �⺻ ���� ��ġ�� �߰� ���� ��ġ�� ���Ͽ� ������ ����� ��� ���� ��ġ�� �����մϴ�.
	wStrengthResult		= CharacterMachine->Character.Strength + wAddStrength;
	wDexterityResult	= CharacterMachine->Character.Dexterity + wAddDexterity;
	wEnergyResult		= CharacterMachine->Character.Energy + wAddEnergy;
	wVitalityResult		= CharacterMachine->Character.Vitality + wAddVitality;

	// ��ũ�ε常�� ���� "���" ��ġ ���� ��� ���� ��ġ�� �����մϴ�.
#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	wCharismaResult		= CharacterMachine->Character.Charisma + wAddCharisma;
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION

	
	// ��Ʈ ���� �ݿ��� ��ġ���� ������ �䱸��ġ�� ���Ǵ� ��ġ ������ �Ǵ��Ͽ� 
	// �� �����ۺ� ���� ��ġ�� �ٽ� ���� �� ���� �մϴ�.
#ifdef LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	g_csItemOption.getAllAddOptionStatesbyCompare( &Character.AddStrength, 
									&Character.AddDexterity, &Character.AddEnergy, &Character.AddVitality, &Character.AddCharisma, 
									wStrengthResult, wDexterityResult, wEnergyResult, wVitalityResult, wCharismaResult );
#else // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	g_csItemOption.getAllAddOptionStatesbyCompare( &Character.AddStrength, 
									&Character.AddDexterity, &Character.AddEnergy, &Character.AddVitality,
									wStrengthResult, wDexterityResult, wEnergyResult, wVitalityResult );
#endif // LDS_ADD_CHARISMAVALUE_TOITEMOPTION
	
#else // LDS_FIX_WRONG_CALCULATEEQUIPEDITEMOPTIONVALUE
	// ��Ʈ ������ �Ϲ� �ɼ�( ��� �پ� �ִ� �ɼ� )
    for ( int i=EQUIPMENT_WEAPON_RIGHT; i<MAX_EQUIPMENT; ++i )
    {
    	ITEM* item = &Equipment[i];

        if ( item->Durability<=0 
#ifdef PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM
			|| IsRequireEquipItem( item ) == false
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM			
			) 
		{
			continue;
		}

        WORD Result = 0;
		// Result*5 = 5�� �� �ϴ� ������ �⺻ ������ 5���� ����
        switch ( g_csItemOption.GetDefaultOptionValue( item, &Result ) )
        {
        case SET_OPTION_STRENGTH:
            Character.AddStrength += Result*5;
            break;

        case SET_OPTION_DEXTERITY:
            Character.AddDexterity += Result*5;
            break;

        case SET_OPTION_ENERGY:
            Character.AddEnergy += Result*5;
            break;

        case SET_OPTION_VITALITY:
            Character.AddVitality += Result*5;
            break;
        }
    }

	// ��Ʈ ������ ��Ʈ �ɼ�( ��Ʈ ������ � �̻��� ���� ���� ��� �߻� �ϴ� �ɼ� )
	g_csItemOption.GetSpecial ( &Character.AddStrength, AT_SET_OPTION_IMPROVE_STRENGTH );	    //	�� ����
	g_csItemOption.GetSpecial ( &Character.AddDexterity, AT_SET_OPTION_IMPROVE_DEXTERITY );	    //	��ø�� ����
	g_csItemOption.GetSpecial ( &Character.AddEnergy, AT_SET_OPTION_IMPROVE_ENERGY );		    //	������ ����
	g_csItemOption.GetSpecial ( &Character.AddVitality, AT_SET_OPTION_IMPROVE_VITALITY );	    //	ü�� ����
	g_csItemOption.GetSpecial ( &Character.AddCharisma, AT_SET_OPTION_IMPROVE_CHARISMA );	    //	��� ����
#endif // LDS_FIX_WRONG_CALCULATEEQUIPEDITEMOPTIONVALUE
	
#ifdef YDG_FIX_SETITEM_REQUIRED_STATUS_BUG
	// ���� ������ �����ϱ� ���� ��Ʈ ������ �ɼ� �˻縦 �ѹ� �� ���ش�
#ifdef YDG_FIX_SETITEM_REQUIRED_STATUS_SECRET_POTION
#ifndef PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION
	CalculateBasicState();
#endif //PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION
#endif	// YDG_FIX_SETITEM_REQUIRED_STATUS_SECRET_POTION
	g_csItemOption.CheckItemSetOptions ();
#endif	// YDG_FIX_SETITEM_REQUIRED_STATUS_BUG

	// ��Ʈ ������ �� �ɼ� ���� �κ� ��
	// ============================================================================== <

    //  ���信 �ش�Ǵ� ����� ������Ų��.
	if ( (CharacterMachine->Equipment[EQUIPMENT_WING].Type+MODEL_ITEM)==MODEL_HELPER+30)
    {
        PlusSpecial ( &Character.AddCharisma, AT_SET_OPTION_IMPROVE_CHARISMA, &CharacterMachine->Equipment[EQUIPMENT_WING] );
    }

#ifdef	LJH_FIX_NOT_CALCULATED_BUFF
	// ���� ȿ���� �߿� �⺻ ������ �÷� �ٰ��� ������ ���⼭ �Ѵ�. 
	CalculateBasicState();
#else	//LJH_FIX_NOT_CALCULATED_BUFF
#ifndef PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM  // ���� �ؾ� �� �ڵ�
#ifdef PSW_SECRET_ITEM
#ifndef PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION
	// ���� ȿ���� �߿� �⺻ ������ �÷� �ٰ��� ������ ���⼭ �Ѵ�. 
	CalculateBasicState();
#endif //PBG_FIX_SETOPTION_CALCULATE_SECRET_POTION
#endif //PSW_SECRET_ITEM
#endif //PSW_BUGFIX_REQUIREEQUIPITEM_SETITEM // ���� �ؾ� �� �ڵ�
#endif	//LJH_FIX_NOT_CALCULATED_BUFF

	///// PSW_BUGFIX_REQUIREEQUIPITEM ////
	// ��� ���� �ϰ� �ִ��� ������ ����� 
	// �䱸 ������ �� ���� ��� ������ 
	// ����� ȿ���� ���� ���� �ʴ´�

	CalculateDamage();				// ����( ��Ʈ �ɼ��� ���� )
	CalculateMagicDamage();			// ����( ��Ʈ �ɼ��� ���� )
	CalculateCurseDamage();			// ����
	CalculateAttackRating();		// ���� �� �ʿ� ����
	CalculateAttackSpeed();			// ����
	CalculateSuccessfulBlocking();  // ����
	CalculateDefense();             // ����
	CalculateMagicDefense();        // ����
	CalculateWalkSpeed();           // ����
	//CalculateNextExperince();
	CalculateSuccessfulBlockingPK(); // ���� �� �ʿ� ����
	CalculateAttackRatingPK();       // ���� �� �ʿ� ����

	///// PSW_BUGFIX_REQUIREEQUIPITEM ////


	MONSTER_ATTRIBUTE *c   = &Enemy.Attribute;
	FinalAttackDamageRight = AttackDamageRight - c->Defense;
	FinalAttackDamageLeft  = AttackDamageLeft  - c->Defense;
	int EnemyAttackDamage  = c->AttackDamageMin + rand()%(c->AttackDamageMax-c->AttackDamageMin+1);
	FinalHitPoint          = EnemyAttackDamage - Character.Defense;
	FinalAttackRating      = Character.AttackRating - c->SuccessfulBlocking;
	FinalDefenseRating     = Character.SuccessfulBlocking - c->AttackRating;

#ifdef ANTIHACKING_ENABLE
	// üũ �ڵ�
	if ( g_bNewFrame)
	{
		switch ( GetTickCount() % 5000)
		{
		case 1321:
			hanguo_check4();
			break;
		case 4321:
			hanguo_check2();
			break;
		}
	}
#endif //ANTIHACKING_ENABLE

	if(FinalAttackDamageRight < 0)
		FinalAttackDamageRight = 0;
	if(FinalAttackDamageLeft < 0)
		FinalAttackDamageLeft = 0;
	if(FinalHitPoint < 0)
		FinalHitPoint = 0;
	if(FinalAttackRating < 0)
		FinalAttackRating = 0;
	else if(FinalAttackRating > 100)
		FinalAttackRating = 100;
	if(FinalDefenseRating < 0)
		FinalDefenseRating = 0;
	else if(FinalDefenseRating > 100)
		FinalDefenseRating = 100;
	if(rand()%100 < FinalAttackRating)
		FinalSuccessAttack = true;
	else
		FinalSuccessAttack = false;
	if(rand()%100 < FinalDefenseRating)
		FinalSuccessDefense = true;
	else
		FinalSuccessDefense = false;
}

void CHARACTER_MACHINE::GetMagicSkillDamage( int iType, int *piMinDamage, int *piMaxDamage)
{
	// ��ȯ�� ��ų�� ���ַ°� ����.
	if (AT_SKILL_SUMMON_EXPLOSION <= iType && iType <= AT_SKILL_SUMMON_REQUIEM)
	{
		*piMinDamage = Character.MagicDamageMin;
		*piMaxDamage = Character.MagicDamageMax;
		return;
	}


	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];
	
    int Damage = p->Damage;

	*piMinDamage = Character.MagicDamageMin+Damage;
	*piMaxDamage = Character.MagicDamageMax+Damage+Damage/2;

#ifdef YDG_FIX_MAGIC_DAMAGE_CALC_ORDER
	Damage = 0;
	g_csItemOption.PlusSpecial ( (WORD*)&Damage,  AT_SET_OPTION_IMPROVE_MAGIC_POWER );	//	���� ���� ����
	if(Damage != 0)
	{
		float fratio = 1.f + (float)Damage/100.f;
		*piMinDamage *= fratio;
		*piMaxDamage *= fratio;
	}

    Damage = 0;
    g_csItemOption.ClearListOnOff();
    g_csItemOption.PlusMastery ( &Damage, p->MasteryType );
    g_csItemOption.PlusSpecial ( (WORD*)&Damage,  AT_SET_OPTION_IMPROVE_SKILL_ATTACK );	//	��ų ���ݷ� ����.
    *piMinDamage += Damage;
    *piMaxDamage += Damage;
#else	// YDG_FIX_MAGIC_DAMAGE_CALC_ORDER
    Damage = 0;
    g_csItemOption.ClearListOnOff();
    g_csItemOption.PlusMastery ( &Damage, p->MasteryType );
    g_csItemOption.PlusSpecial ( (WORD*)&Damage,  AT_SET_OPTION_IMPROVE_SKILL_ATTACK );	//	��ų ���ݷ� ����.
    *piMinDamage += Damage;
    *piMaxDamage += Damage;
	
	Damage = 0;
	g_csItemOption.PlusSpecial ( (WORD*)&Damage,  AT_SET_OPTION_IMPROVE_MAGIC_POWER );	//	���� ���� ����
	if(Damage != 0)
	{
		float fratio = 1.f + (float)Damage/100.f;
		*piMinDamage *= fratio;
		*piMaxDamage *= fratio;
	}
#endif	// YDG_FIX_MAGIC_DAMAGE_CALC_ORDER
}

// ���ַ� ��ų ������.
void CHARACTER_MACHINE::GetCurseSkillDamage(int iType, int *piMinDamage, int *piMaxDamage)
{
	if (CLASS_SUMMONER != GetBaseClass(Character.Class))	// ��ȯ���縸 ���ַ��� �ʿ��ϴ�.
		return;

	// ��ȯ�� ��ų�� ���ַ°� ����.
	if (AT_SKILL_SUMMON_EXPLOSION <= iType && iType <= AT_SKILL_SUMMON_REQUIEM)
	{
		SKILL_ATTRIBUTE *p = &SkillAttribute[iType];
		*piMinDamage = Character.CurseDamageMin+p->Damage;
		*piMaxDamage = Character.CurseDamageMax+p->Damage+p->Damage/2;
	}
	else
	{
		*piMinDamage = Character.CurseDamageMin;
		*piMaxDamage = Character.CurseDamageMax;
	}
}

void CHARACTER_MACHINE::GetSkillDamage( int iType, int *piMinDamage, int *piMaxDamage)
{

	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];
	
    int Damage = p->Damage;

	*piMinDamage = Damage;
	*piMaxDamage = Damage+Damage/2;

    Damage = 0;
    //  ��Ʈ �ɼ� ����.
    g_csItemOption.ClearListOnOff();
    g_csItemOption.PlusMastery ( &Damage, p->MasteryType );
    g_csItemOption.PlusSpecial ( (WORD*)&Damage,  AT_SET_OPTION_IMPROVE_SKILL_ATTACK );	//	��ų ���ݷ� ����.
    *piMinDamage += Damage;
    *piMaxDamage += Damage;

}

BYTE CHARACTER_MACHINE::GetSkillMasteryType ( int iType )
{
    BYTE MasteryType = 255;
    SKILL_ATTRIBUTE* p = &SkillAttribute[iType];

    MasteryType = p->MasteryType;

    return MasteryType;
}

// ��ų Ÿ���� ������ ��ų�� ���� �������� �Ѱ��ش�.
void GetSkillInformation( int iType, int iLevel, char *lpszName, int *piMana, int *piDistance, int *piSkillMana)
{

	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];
	if ( lpszName)
	{
#ifdef USE_SKILL_LEVEL
		if ( iLevel == 0)
		{
			strcpy( lpszName, p->Name);
		}
		else
		{
			sprintf( lpszName, "%s +%d", p->Name, iLevel);
		}
#else
		strcpy( lpszName, p->Name);
#endif
	}
	if ( piMana)
	{
		*piMana = p->Mana;
	}
	if ( piDistance)
	{
		*piDistance = p->Distance;
	}
	if (piSkillMana)
	{
		*piSkillMana = p->AbilityGuage;
	}

}

void GetSkillInformation_Energy(int iType, int *piEnergy)
{

	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];

	if(piEnergy)
	{
		if(p->Energy == 0)
		{
			*piEnergy = 0;
		}
		else
		{
			*piEnergy = 20 + (p->Energy*p->Level*4/100);

			if( iType == AT_SKILL_SUMMON_EXPLOSION || iType == AT_SKILL_SUMMON_REQUIEM ){
				*piEnergy = 20 + (p->Energy*p->Level*3/100);
			}

#ifdef PSW_BUGFIX_CLASS_KNIGHT_REQUIRESKILL
			if( GetBaseClass ( Hero->Class ) == CLASS_KNIGHT ) {
				*piEnergy = 10 + (p->Energy*p->Level*4/100);
			}
#endif //PSW_BUGFIX_CLASS_KNIGHT_REQUIRESKILL
		}
	}

}

void GetSkillInformation_Charisma(int iType, int *piCharisma)
{
	
	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];

	if(piCharisma)
	{
		*piCharisma = p->Charisma;
	}

}

void GetSkillInformation_Damage(int iType, int *piDamage)
{
	
	SKILL_ATTRIBUTE *p = &SkillAttribute[iType];

	if(piDamage)
	{
		*piDamage = p->Damage;
	}

}

//////////////////////////////////////////////////////////////////////////
//  ��ų�� �Ÿ��� �˷��ش�.
//////////////////////////////////////////////////////////////////////////
float GetSkillDistance(int Index, CHARACTER* c)
{
    float Distance = (float)( SkillAttribute[Index].Distance );

	if( Index == AT_SKILL_BLOW_UP + 4 ) 
	{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
		if(Distance != 3)
			int aaa = 0;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	}

    if(c != NULL)
    {
        // ��ũ�ε��� ��� ��ũȣ���� ���� ���� �Ÿ� +2�� ���ش�.
        if(c->Helper.Type == MODEL_HELPER+4)
		{
            Distance += 2;
		}
    }

    return Distance;
}

//////////////////////////////////////////////////////////////////////////
//  ���� ����ϴ� ��ų�� �ߵ��Ҽ� �ִ��� �˻��Ѵ�. ( ��ų �����̰� ������ ���� );
//////////////////////////////////////////////////////////////////////////
bool    CheckSkillDelay ( int SkillIndex )
{
	int Skill = CharacterAttribute->Skill[SkillIndex];  //  ��ų.

    int Delay = SkillAttribute[Skill].Delay;            //  ��ų ������.

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!CheckAttack() && (Skill == AT_SKILL_GIANTSWING || Skill == AT_SKILL_DRAGON_LOWER ||
		Skill == AT_SKILL_DRAGON_KICK))
	{
		return false;
	}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
    //  ��ų �����̰� �����ϴ� ��ų.
    if ( Delay>0 )
    {
        if ( CharacterAttribute->SkillDelay[SkillIndex] > 0 )
        {
            return false;
        }

		int iCharisma;
		GetSkillInformation_Charisma(Skill, &iCharisma);	// �������Ʈ
		if(iCharisma > (CharacterAttribute->Charisma + CharacterAttribute->AddCharisma))
		{
            return false;
		}

		CharacterAttribute->SkillDelay[SkillIndex] = Delay;
    }
    return true;
}


//////////////////////////////////////////////////////////////////////////
//  ��ų �����̸� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////
void    CalcSkillDelay ( int time )
{

	//^ �渱 ��ų ����(������ ���)
	int iSkillNumber;
	iSkillNumber = CharacterAttribute->SkillNumber+2;
	iSkillNumber = min(iSkillNumber, MAX_SKILLS);

    for ( int i=0; i<iSkillNumber; ++i )
    {
		if ( CharacterAttribute->SkillDelay[i] <= 0 ) 
			continue;

        CharacterAttribute->SkillDelay[i] -= time;
        if ( CharacterAttribute->SkillDelay[i]<0 )
        {
            CharacterAttribute->SkillDelay[i] = 0;
        }
    }
	

#ifdef STATE_LIMIT_TIME
    if ( g_iWorldStateTime>0 )
    {
        g_iWorldStateTime -= time;
        if ( g_iWorldStateTime<=0 )
        {
            if ( ((Hero->Object.State&STATE_FREEZE)==STATE_FREEZE) )
                Hero->Object.State -= STATE_FREEZE;
            if ( ((Hero->Object.State&STATE_STUN)==STATE_STUN) )
                Hero->Object.State -= STATE_STUN;
            if ( ((Hero->Object.State&STATE_PARALYZE)==STATE_PARALYZE) )
                Hero->Object.State -= STATE_PARALYZE;

            g_iWorldStateTime = 0;
        }
    }
#endif// STATE_LIMIT_TIME
}


//////////////////////////////////////////////////////////////////////////
//  ���� ���ΰ��� ���� ������ ���ŵǾ����� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
#ifdef STATE_LIMIT_TIME
void    SetWorldStateTime ( DWORD State, int Time )
{
    if ( g_dwWorldStateBack!=State )
    {
        g_dwWorldStateBack = State;
        g_iWorldStateTime = Time;
    }
}
#endif// STATE_LIMIT_TIME


//////////////////////////////////////////////////////////////////////////
//  ��ų ������ ���� ǥ���Ѵ�.
//////////////////////////////////////////////////////////////////////////
void    RenderSkillDelay ( int SkillIndex, int x, int y, int Width, int Height )
{
    int Delay = CharacterAttribute->SkillDelay[SkillIndex];
    if ( Delay>0 )
    {
        int Type  = CharacterAttribute->Skill[SkillIndex];

        int MaxDelay = SkillAttribute[Type].Delay;

        float Persent = (float)(Delay/(float)MaxDelay);
        
        EnableAlphaTest ();
        glColor4f ( 1.f, 0.5f, 0.5f, 0.5f );
        float deltaH = Height*Persent;
        RenderColor ( (float)x, (float)y+Height-deltaH, (float)Width, deltaH );
        DisableAlphaBlend();
    }
}

// �渶�ΰ�
bool IsGuildMaster()
{
	return ( Hero->GuildStatus == G_MASTER );
}
// �α渶�ΰ�
bool IsSubGuildMaster()
{
	return ( Hero->GuildStatus == G_SUB_MASTER );
}		
// ��Ʋ�������ΰ�
bool IsBattleMaster()
{
	return ( Hero->GuildStatus == G_BATTLE_MASTER );
}		
