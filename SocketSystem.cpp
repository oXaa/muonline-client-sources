#include "stdafx.h"
#include "SocketSystem.h"
#include "./Utilities/Log/ErrorReport.h"
#include "ZzzInventory.h"
#include "ZzzBMD.h"
#include "ZzzCharacter.h"
#include "WSclient.h"
#include "UIControls.h"

#ifdef SOCKET_SYSTEM

using namespace SEASON4A;

/*+++++++++++++++++++++++++++++++++++++
    FUNCTIONS.
+++++++++++++++++++++++++++++++++++++*/
static BYTE bBuxCode[3] = {0xfc,0xcf,0xab};

static void BuxConvert(BYTE *Buffer,int Size)
{
	for(int i=0;i<Size;i++)
		Buffer[i] ^= bBuxCode[i%3];
}

CSocketItemMgr g_SocketItemMgr;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketItemMgr::CSocketItemMgr()
{
	m_iNumEquitSetBonusOptions = 0;
	memset(m_SocketOptionInfo, 0, sizeof(SOCKET_OPTION_INFO) * MAX_SOCKET_OPTION);
	memset(&m_StatusBonus, 0, sizeof(SOCKET_OPTION_STATUS_BONUS));

// SocketItem.bmd ��ũ��Ʈ ������ zzzOpenData���� �д´�.
#ifndef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
#ifdef USE_SOCKETITEM_TEST_BMD
	OpenSocketItemScript("Data\\Local\\SocketItemTest.bmd");
#else	// USE_SOCKETITEM_TEST_BMD
	OpenSocketItemScript("Data\\Local\\SocketItem.bmd");
#endif	// USE_SOCKETITEM_TEST_BMD
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
}

CSocketItemMgr::~CSocketItemMgr()
{

}

BOOL CSocketItemMgr::IsSocketItem(const ITEM* pItem)
{
	return IsSocketItem(pItem->Type);
}

BOOL CSocketItemMgr::IsSocketItem(const OBJECT* pObject)
{
	return IsSocketItem(pObject->Type - MODEL_SWORD);
}

BOOL CSocketItemMgr::IsSocketItem(int iItemType)
{
	switch (iItemType)
	{
	case ITEM_SWORD+26:	// �ö�������
	case ITEM_SWORD+27:	// �ҵ�극��Ŀ
	case ITEM_SWORD+28:	// ��ٽ�Ÿ��
	case ITEM_MACE+16:	// ���ν�Ʈ���̽�
	case ITEM_MACE+17:	// ���ַ�Ʈ����
	case ITEM_BOW+23:	// ��ũ���ð�
	case ITEM_STAFF+30:	// ���鸮������
	case ITEM_STAFF+31:	// �κ����˽�����
	case ITEM_STAFF+32:	// �ҿ�긵��
	case ITEM_SHIELD+17:	// ũ�����۷θ�
	case ITEM_SHIELD+18:	// �����Ǵ��ǵ�
	case ITEM_SHIELD+19:	// ���ν�Ʈ�踮��
	case ITEM_SHIELD+20:	// ����ȹ���
	case ITEM_HELM+45: case ITEM_ARMOR+45: case ITEM_PANTS+45: case ITEM_GLOVES+45: case ITEM_BOOTS+45:	// Ƽź
	case ITEM_HELM+46: case ITEM_ARMOR+46: case ITEM_PANTS+46: case ITEM_GLOVES+46: case ITEM_BOOTS+46:	// �극�̺�
	case ITEM_HELM+47: case ITEM_ARMOR+47: case ITEM_PANTS+47: case ITEM_GLOVES+47: case ITEM_BOOTS+47:	// ����
	case ITEM_HELM+48: case ITEM_ARMOR+48: case ITEM_PANTS+48: case ITEM_GLOVES+48: case ITEM_BOOTS+48:	// ��Ʈ����
	case ITEM_HELM+49: case ITEM_ARMOR+49: case ITEM_PANTS+49: case ITEM_GLOVES+49: case ITEM_BOOTS+49:	// ������
	case ITEM_HELM+50: case ITEM_ARMOR+50: case ITEM_PANTS+50: case ITEM_GLOVES+50: case ITEM_BOOTS+50:	// �����
	case ITEM_HELM+51: case ITEM_ARMOR+51: case ITEM_PANTS+51: case ITEM_GLOVES+51: case ITEM_BOOTS+51:	// �п�
	case ITEM_HELM+52: case ITEM_ARMOR+52: case ITEM_PANTS+52: case ITEM_GLOVES+52: case ITEM_BOOTS+52:	// �ϵ���
	case ITEM_HELM+53: case ITEM_ARMOR+53: case ITEM_PANTS+53: case ITEM_GLOVES+53: case ITEM_BOOTS+53:	// ��ť����
		return TRUE;
	default:
		return FALSE;
	}
// 	return (pItem->SocketCount > 0);
}

int CSocketItemMgr::GetSocketCategory(int iSeedID)
{
	if (iSeedID == SOCKET_EMPTY) return SOCKET_EMPTY;

	SOCKET_OPTION_INFO * pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][iSeedID];
	return pInfo->m_iOptionCategory;
}

int CSocketItemMgr::GetSeedShpereSeedID(const ITEM* pItem)
{
	BYTE bySocketSeedID = SOCKET_EMPTY;

	if(pItem->Type >= ITEM_WING+100 && pItem->Type <= ITEM_WING+129)	// �õ彺�Ǿ�
	{
		int iCategoryIndex = (pItem->Type - (ITEM_WING+100)) % 6 + 1;
		int iLevel = (pItem->Level>>3)&15;
		switch(iCategoryIndex)
		{
		case 1:	// 0~9
			bySocketSeedID = 0 + iLevel;
			break;
		case 2:	// 10~15
			bySocketSeedID = 10 + iLevel;
			break;
		case 3:	// 16~20
			bySocketSeedID = 16 + iLevel;
			break;
		case 4:	// 21~28
			bySocketSeedID = 21 + iLevel;
			break;
		case 5:	// 29~33
			bySocketSeedID = 29 + iLevel;
			break;
		case 6:	// 34~40
			bySocketSeedID = 34 + iLevel;
			break;
		}
	}

	return bySocketSeedID;
}

#ifdef KJW_FIX_SOCKET_BONUS_BIT_OPERATION
__int64 CSocketItemMgr::CalcSocketBonusItemValue( const ITEM * pItem, __int64 iOrgGold)
#else // KJW_FIX_SOCKET_BONUS_BIT_OPERATION
int CSocketItemMgr::CalcSocketBonusItemValue( const ITEM * pItem, int iOrgGold)
#endif // KJW_FIX_SOCKET_BONUS_BIT_OPERATION
{
#ifdef KJW_FIX_SOCKET_BONUS_BIT_OPERATION
	__int64 iGoldResult = 0;
#else // KJW_FIX_SOCKET_BONUS_BIT_OPERATION
	int iGoldResult = 0;
#endif // KJW_FIX_SOCKET_BONUS_BIT_OPERATION
	
	if (IsSocketItem(pItem))
	{
		// + ���� ���� * 0.8 (0.8 ~ 4.0)
		iGoldResult += iOrgGold * (pItem->SocketCount * 0.8f);

		// + ������ �õ� ���Ǿ� ���� ����
		ITEM TempSeedSphere;
		for (int i = 0; i < pItem->SocketCount; ++i)
		{
			if (pItem->SocketSeedID[i] == SOCKET_EMPTY) continue;

			int iSeedSphereType = 0;
			if (pItem->SocketSeedID[i] >= 0 && pItem->SocketSeedID[i] <= 9) iSeedSphereType = 0;
			else if (pItem->SocketSeedID[i] >= 10 && pItem->SocketSeedID[i] <= 15) iSeedSphereType = 1;
			else if (pItem->SocketSeedID[i] >= 16 && pItem->SocketSeedID[i] <= 20) iSeedSphereType = 2;
			else if (pItem->SocketSeedID[i] >= 21 && pItem->SocketSeedID[i] <= 28) iSeedSphereType = 3;
			else if (pItem->SocketSeedID[i] >= 29 && pItem->SocketSeedID[i] <= 33) iSeedSphereType = 4;
			else if (pItem->SocketSeedID[i] >= 34 && pItem->SocketSeedID[i] <= 40) iSeedSphereType = 5;

#ifdef YDG_FIX_SOCKETITEM_SELLPRICE_BUG
			TempSeedSphere.Type = ITEM_WING+100 + (pItem->SocketSphereLv[i] - 1) * MAX_SOCKET_TYPES + iSeedSphereType;
#else	// YDG_FIX_SOCKETITEM_SELLPRICE_BUG
			TempSeedSphere.Type = ITEM_WING+100+ pItem->SocketSphereLv[i] * MAX_SPHERE_LEVEL + iSeedSphereType;
#endif	// YDG_FIX_SOCKETITEM_SELLPRICE_BUG
			iGoldResult += ItemValue(&TempSeedSphere, 0);
		}
	}

	return iGoldResult;
}

#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
int CSocketItemMgr::CalcSocketOptionValue(int iOptionType, float fOptionValue)
{
	switch(iOptionType)
	{
	case 1:	// A: +��
		return int(fOptionValue);
	case 2:	// B: +��%
		return int(fOptionValue);
	case 3:	// C: +���շ���/��
		{
			WORD wLevel;

			if(IsMasterLevel(CharacterAttribute->Class) == true)
				wLevel = CharacterAttribute->Level + Master_Level_Data.nMLevel;
			else
				wLevel = CharacterAttribute->Level;
			
			return int((float)wLevel / fOptionValue);
		}
	case 4:	// D: +�ִ����/��
		{
			WORD wLifeMax;

			if(IsMasterLevel( Hero->Class ) == true )
				wLifeMax = Master_Level_Data.wMaxLife;
			else
				wLifeMax = CharacterAttribute->LifeMax;

			return int((float)wLifeMax / fOptionValue);
		}
	case 5:	// E: +�ִ븶��/��
		{
			WORD wManaMax;
			if(IsMasterLevel( Hero->Class ) == true )
				wManaMax = Master_Level_Data.wMaxMana;
			else
				wManaMax = CharacterAttribute->ManaMax;

			return int((float)wManaMax / fOptionValue);
		}
	default:
		return 0;
	}
}

void CSocketItemMgr::CalcSocketOptionValueText(char * pszOptionValueText, int iOptionType, float fOptionValue)
{
	switch(iOptionType)
	{
	case 1:	// A: +��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue));
		break;
	case 2:	// B: +��%
		sprintf(pszOptionValueText, "+%d%%", CalcSocketOptionValue(iOptionType, fOptionValue));
		break;
	case 3:	// C: +���շ���/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue));
		break;
	case 4:	// D: +�ִ����/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue));
		break;
	case 5:	// E: +�ִ븶��/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue));
		break;
	}
}
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
int CSocketItemMgr::CalcSocketOptionValue(int iOptionType, float fOptionValue, float fSphereValue)
{
	switch(iOptionType)
	{
	case 1:	// A: +��
		return int(fOptionValue * fSphereValue);
	case 2:	// B: +��%
		return int(fOptionValue * fSphereValue);
	case 3:	// C: +���շ���/��
		{
			WORD wLevel;

			if(IsMasterLevel(CharacterAttribute->Class) == true)
				wLevel = CharacterAttribute->Level + Master_Level_Data.nMLevel;
			else
				wLevel = CharacterAttribute->Level;
			
			return int((float)wLevel / fOptionValue * fSphereValue);
		}
	case 4:	// D: +�ִ����/��
		{
			WORD wLifeMax;

			if(IsMasterLevel( Hero->Class ) == true )
				wLifeMax = Master_Level_Data.wMaxLife;
			else
				wLifeMax = CharacterAttribute->LifeMax;

			return int((float)wLifeMax / fOptionValue * fSphereValue);
		}
	case 5:	// E: +�ִ븶��/��
		{
			WORD wManaMax;

			if(IsMasterLevel( Hero->Class ) == true )
				wManaMax = Master_Level_Data.wMaxMana;
			else
				wManaMax = CharacterAttribute->ManaMax;

			return int((float)wManaMax / fOptionValue * fSphereValue);
		}
	default:
		return 0;
	}
}

void CSocketItemMgr::CalcSocketOptionValueText(char * pszOptionValueText, int iOptionType, float fOptionValue, float fSphereValue)
{
	switch(iOptionType)
	{
	case 1:	// A: +��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue, fSphereValue));
		break;
	case 2:	// B: +��%
		sprintf(pszOptionValueText, "+%d%%", CalcSocketOptionValue(iOptionType, fOptionValue, fSphereValue));
		break;
	case 3:	// C: +���շ���/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue, fSphereValue));
		break;
	case 4:	// D: +�ִ����/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue, fSphereValue));
		break;
	case 5:	// E: +�ִ븶��/��
		sprintf(pszOptionValueText, "+%d", CalcSocketOptionValue(iOptionType, fOptionValue, fSphereValue));
		break;
	}
}
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE

void CSocketItemMgr::CreateSocketOptionText(char * pszOptionText, int iSeedID, int iSphereLv)
{
	if (pszOptionText == NULL) return;

	// "���� ��ȭ", "��� ��ȭ", "���� ��ȭ", "�� ��ȭ", "���� ��ȭ", "���� ��ȭ", "����ũ �ɼ�"
	// "��", "�ٶ�", "����", "��", "����", "��", "����ũ"
	char szOptionValueText[16] = { 0, };

	SOCKET_OPTION_INFO * pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][iSeedID];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
	float fOptionValue = (float)pInfo->m_iOptionValue[iSphereLv - 1];

	CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, fOptionValue);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
	float fOptionValue = (float)pInfo->m_iOptionValue;
	float fSphereValue = m_fSphereValues[iSphereLv - 1];

	CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, fOptionValue, fSphereValue);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
	sprintf(pszOptionText, "%s(%s %s)", GlobalText[2640 + pInfo->m_iOptionCategory - 1], pInfo->m_szOptionName, szOptionValueText);
}

extern int SkipNum;

int CSocketItemMgr::AttachToolTipForSocketItem(const ITEM* pItem, int iTextNum)
{
	if (pItem->SocketCount == 0) return iTextNum;

	// ���� �ɼ� ����
	sprintf ( TextList[iTextNum], "\n" ); ++iTextNum; ++SkipNum;
	sprintf ( TextList[iTextNum], "%s %s", GlobalText[2650], GlobalText[159] );	// "����"
	TextListColor[iTextNum] = TEXT_COLOR_PURPLE; 
	TextBold[iTextNum] = false;
	++iTextNum;
	sprintf(TextList[iTextNum], "\n"); ++iTextNum; ++SkipNum;

	// ���Ϻ� �ɼ� ���
	char szOptionText[64] = { 0, };
	char szOptionValueText[16] = { 0, };
	SOCKET_OPTION_INFO * pInfo = NULL;
	for (int i = 0; i < pItem->SocketCount; ++i)
	{
		if (pItem->SocketSeedID[i] == SOCKET_EMPTY)
		{
			sprintf(szOptionText, GlobalText[2652]);	// "���������� ����"
			TextListColor[iTextNum] = TEXT_COLOR_GRAY; 
		}
		else if (pItem->SocketSeedID[i] < MAX_SOCKET_OPTION)
		{
			CreateSocketOptionText(szOptionText, pItem->SocketSeedID[i], pItem->SocketSphereLv[i]);
			TextListColor[iTextNum] = TEXT_COLOR_BLUE; 
		}
		else
		{
			assert(!"���� �ε��� ����");
		}

		sprintf(TextList[iTextNum], GlobalText[2655], i + 1, szOptionText);	// "���� %d: %s"
		TextBold[iTextNum] = false;
		++iTextNum;
	}

	// ���� ��Ʈ �ɼ�
	if (pItem->SocketSeedSetOption < MAX_SOCKET_OPTION)
	{
		sprintf(TextList[iTextNum], "\n"); ++iTextNum; ++SkipNum;

		sprintf ( TextList[iTextNum], "%s", GlobalText[2656]);	// "���ʽ� ���� �ɼ�"
		TextListColor[iTextNum] = TEXT_COLOR_PURPLE; 
		TextBold[iTextNum] = false;
		++iTextNum;
		sprintf(TextList[iTextNum], "\n"); ++iTextNum; ++SkipNum;

		pInfo = &m_SocketOptionInfo[SOT_MIX_SET_BONUS_OPTIONS][pItem->SocketSeedSetOption];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
		CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, (float)pInfo->m_iOptionValue[0]);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
		CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, (float)pInfo->m_iOptionValue, 1.0f);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
		sprintf(TextList[iTextNum], "%s %s", pInfo->m_szOptionName, szOptionValueText);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE; 
		TextBold[iTextNum] = false;
		++iTextNum;
	}
	return iTextNum;
}

int CSocketItemMgr::AttachToolTipForSeedSphereItem(const ITEM* pItem, int iTextNum)
{
	SOCKET_OPTION_INFO * pInfo = NULL;

	if(pItem->Type >= ITEM_WING+60 && pItem->Type <= ITEM_WING+65)	// �õ�
	{
		int iCategoryIndex = pItem->Type - (ITEM_WING+60) + 1;
		sprintf(TextList[iTextNum], GlobalText[2653], GlobalText[2640 + iCategoryIndex - 1]);	// "�Ӽ�: %s"
		TextListColor[iTextNum] = TEXT_COLOR_WHITE;
		TextBold[iTextNum] = false;
		++iTextNum;

		sprintf ( TextList[iTextNum], "\n" ); ++iTextNum; ++SkipNum;

		int iSocketSeedID = 0;
		int iLevel = (pItem->Level>>3)&15;
		switch(iCategoryIndex)
		{
		case 1:	// 0~9
			iSocketSeedID = 0 + iLevel;
			break;
		case 2:	// 10~15
			iSocketSeedID = 10 + iLevel;
			break;
		case 3:	// 16~20
			iSocketSeedID = 16 + iLevel;
			break;
		case 4:	// 21~28
			iSocketSeedID = 21 + iLevel;
			break;
		case 5:	// 29~33
			iSocketSeedID = 29 + iLevel;
			break;
		case 6:	// 34~40
			iSocketSeedID = 34 + iLevel;
			break;
		}
		pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][iSocketSeedID];
		sprintf(TextList[iTextNum], pInfo->m_szOptionName);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE;
		TextBold[iTextNum] = false;
		++iTextNum;
	}
	else if(pItem->Type >= ITEM_WING+70 && pItem->Type <= ITEM_WING+74)	// ���Ǿ�
	{
		int iSphereLevel = pItem->Type - (ITEM_WING+70) + 1;
		sprintf(TextList[iTextNum], GlobalText[2654], iSphereLevel);	// "���: %d"
		TextListColor[iTextNum] = TEXT_COLOR_WHITE;
		TextBold[iTextNum] = false;
		++iTextNum;
	}
	else if(pItem->Type >= ITEM_WING+100 && pItem->Type <= ITEM_WING+129)	// �õ彺�Ǿ�
	{
		int iCategoryIndex = (pItem->Type - (ITEM_WING+100)) % 6 + 1;
		sprintf(TextList[iTextNum], GlobalText[2653], GlobalText[2640 + iCategoryIndex - 1]);	// "�Ӽ�: %s"
		TextListColor[iTextNum] = TEXT_COLOR_WHITE;
		TextBold[iTextNum] = false;
		++iTextNum;

		sprintf ( TextList[iTextNum], "\n" ); ++iTextNum; ++SkipNum;

		int iSocketSeedID = 0;
		int iLevel = (pItem->Level>>3)&15;
		switch(iCategoryIndex)
		{
		case 1:	// 0~9
			iSocketSeedID = 0 + iLevel;
			break;
		case 2:	// 10~15
			iSocketSeedID = 10 + iLevel;
			break;
		case 3:	// 16~20
			iSocketSeedID = 16 + iLevel;
			break;
		case 4:	// 21~28
			iSocketSeedID = 21 + iLevel;
			break;
		case 5:	// 29~33
			iSocketSeedID = 29 + iLevel;
			break;
		case 6:	// 34~40
			iSocketSeedID = 34 + iLevel;
			break;
		}

		pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][iSocketSeedID];

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
		char szOptionText[64] = { 0, };
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
		char szOptionValueText[16] = { 0, };
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
		float fOptionValue = (float)pInfo->m_iOptionValue[(pItem->Type - (ITEM_WING+100)) / 6];
		CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, fOptionValue);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
		float fOptionValue = (float)pInfo->m_iOptionValue;
		float fSphereValue = m_fSphereValues[(pItem->Type - (ITEM_WING+100)) / 6];
		CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, fOptionValue, fSphereValue);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE

		sprintf(TextList[iTextNum], "%s %s", pInfo->m_szOptionName, szOptionValueText);
		TextListColor[iTextNum] = TEXT_COLOR_BLUE;
		TextBold[iTextNum] = false;
		++iTextNum;
	}

	return iTextNum;
}

BOOL CSocketItemMgr::IsSocketSetOptionEnabled()
{
	return (!m_EquipSetBonusList.empty());
}

void CSocketItemMgr::RenderToolTipForSocketSetOption(int iPos_x, int iPos_y)
{
	if (IsSocketSetOptionEnabled())
	{
		g_pRenderText->SetTextColor(255, 255, 255, 255);
		g_pRenderText->SetBgColor(100, 0, 0, 0);

        int PosX, PosY;

        PosX = iPos_x+95;//+60;
        PosY = iPos_y+40;

        BYTE TextNum = 0;
        BYTE SkipNum = 0;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
        BYTE setIndex = 0;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

        sprintf(TextList[TextNum], "\n"); TextListColor[TextNum] = 0; TextBold[TextNum] = false; TextNum++; SkipNum++;
        sprintf(TextList[TextNum], "\n"); TextListColor[TextNum] = 0; TextBold[TextNum] = false; TextNum++; SkipNum++;
        sprintf(TextList[TextNum], "\n"); TextListColor[TextNum] = 0; TextBold[TextNum] = false; TextNum++; SkipNum++;

		// ���� ��Ʈ �ɼ�
        sprintf (TextList[TextNum], GlobalText[2657]);	// "��Ʈ ���� �ɼ�"
		TextListColor[TextNum] = TEXT_COLOR_PURPLE;
		TextBold[TextNum] = true;
		TextNum++;

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
		char szOptionText[64] = { 0, };
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
		char szOptionValueText[16] = { 0, };
		SOCKET_OPTION_INFO * pInfo = NULL;
		for (std::deque<DWORD>::iterator iter = m_EquipSetBonusList.begin(); iter != m_EquipSetBonusList.end(); ++iter)
		{
			pInfo = &m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][*iter];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
			CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, (float)pInfo->m_iOptionValue[0]);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
			CalcSocketOptionValueText(szOptionValueText, pInfo->m_bOptionType, (float)pInfo->m_iOptionValue, 1.0f);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
			sprintf(TextList[TextNum], "%s %s", pInfo->m_szOptionName, szOptionValueText);
			TextListColor[TextNum] = TEXT_COLOR_BLUE;
			TextBold[TextNum] = false;
			TextNum++;
		}

#if SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		RenderTipTextList( PosX, PosY, TextNum, 140, RT3_SORT_CENTER );	// ���� ��Ʈ�ɼ�â ���� Ȯ��
#else	// SELECTED_LANGUAGE == LANGUAGE_ENGLISH
		RenderTipTextList( PosX, PosY, TextNum, 120, RT3_SORT_CENTER );
#endif	// SELECTED_LANGUAGE == LANGUAGE_ENGLISH
	}
}

void CSocketItemMgr::CheckSocketSetOption()
{
	m_EquipSetBonusList.clear();

	// ��� �������� �˻��ؼ� ���� ������ ������.
	int iSeedSum[6] = { 0, 0, 0, 0, 0, 0 };
	ITEM * pItem = NULL;
	SOCKET_OPTION_INFO * pInfo = NULL;

	for (int i = 0; i < MAX_EQUIPMENT; ++i)
	{
		pItem = &CharacterMachine->Equipment[i];
		for (int j = 0; j < pItem->SocketCount; ++j)
		{
			if (pItem->SocketSeedID[j] != SOCKET_EMPTY)
			{
				pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][pItem->SocketSeedID[j]];
				++iSeedSum[pInfo->m_iOptionCategory - 1];
			}
		}
	}

	// ���� ��Ʈ ���θ� �˻��Ѵ�.
#ifdef _VS2008PORTING
	for (int i = 0; i < m_iNumEquitSetBonusOptions; ++i)
	{
		int icnt = 0;
		BYTE * pbySetTest = m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_bySocketCheckInfo;
		for (int j = 0; j < 6; ++j)
		{
			icnt = j;
			if (iSeedSum[j] < pbySetTest[j]) break;
		}
		if (icnt < 6) continue;

		m_EquipSetBonusList.push_back(m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_iOptionID);
	}
#else // _VS2008PORTING
	for (i = 0; i < m_iNumEquitSetBonusOptions; ++i)
	{
		BYTE * pbySetTest = m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_bySocketCheckInfo;
		for (int j = 0; j < 6; ++j)
		{
			if (iSeedSum[j] < pbySetTest[j]) break;
		}
		if (j < 6) continue;

		m_EquipSetBonusList.push_back(m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_iOptionID);
	}
#endif // _VS2008PORTING
}

int CSocketItemMgr::GetSocketOptionValue(const ITEM * pItem, int iSocketIndex)
{
	if (pItem->SocketCount > 0 && pItem->SocketSeedID[iSocketIndex] != SOCKET_EMPTY)
	{
		SOCKET_OPTION_INFO * pInfo = NULL;
		pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][pItem->SocketSeedID[iSocketIndex]];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
		float fOptionValue = (float)pInfo->m_iOptionValue[pItem->SocketSphereLv[iSocketIndex] - 1];

		return CalcSocketOptionValue(pInfo->m_bOptionType, fOptionValue);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
		float fOptionValue = (float)pInfo->m_iOptionValue;
		float fSphereValue = m_fSphereValues[pItem->SocketSphereLv[iSocketIndex] - 1];

		return CalcSocketOptionValue(pInfo->m_bOptionType, fOptionValue, fSphereValue);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
	}
	else
	{
		return 0;
	}
}

void CSocketItemMgr::CalcSocketStatusBonus()
{
	memset(&m_StatusBonus, 0, sizeof(SOCKET_OPTION_STATUS_BONUS));
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
	m_StatusBonus.m_fDefenceRateBonus = 1.0f;	// �漺�� �ʱ�ȭ 1.0f
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

	ITEM * pItem = NULL;
	SOCKET_OPTION_INFO * pInfo = NULL;

	for (int i = 0; i < MAX_EQUIPMENT; ++i)
	{
		pItem = &CharacterMachine->Equipment[i];

		if (!IsSocketItem(pItem)) continue;
			
		for (int j = 0; j < pItem->SocketCount; ++j)
		{
			if (pItem->SocketSeedID[j] != SOCKET_EMPTY)
			{
				pInfo = &m_SocketOptionInfo[SOT_SOCKET_ITEM_OPTIONS][pItem->SocketSeedID[j]];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
				float fOptionValue = (float)pInfo->m_iOptionValue[pItem->SocketSphereLv[j] - 1];
				int iBonus = CalcSocketOptionValue(pInfo->m_bOptionType, fOptionValue);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
				float fOptionValue = (float)pInfo->m_iOptionValue;
				float fSphereValue = m_fSphereValues[pItem->SocketSphereLv[j] - 1];
				int iBonus = CalcSocketOptionValue(pInfo->m_bOptionType, fOptionValue, fSphereValue);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE

				switch(pInfo->m_iOptionID)
				{
				case SOPT_ATTACK_N_MAGIC_DAMAGE_BONUS_BY_LEVEL:		// "(������)���ݷ�/��������"
				case SOPT_ATTACK_N_MAGIC_DAMAGE_BONUS:		// "���ݷ�/��������"
					m_StatusBonus.m_iAttackDamageMinBonus += iBonus;
					m_StatusBonus.m_iAttackDamageMaxBonus += iBonus;
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					m_StatusBonus.m_iMagicPowerMinBonus += iBonus;
					m_StatusBonus.m_iMagicPowerMaxBonus += iBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					break;
				case SOPT_ATTACK_SPEED_BONUS:			// "���ݼӵ�����"
					m_StatusBonus.m_iAttackSpeedBonus += iBonus;
					break;
				case SOPT_ATTACT_N_MAGIC_DAMAGE_MAX_BONUS:	// "�ִ���ݷ�/��������"
					m_StatusBonus.m_iAttackDamageMaxBonus += iBonus;
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					m_StatusBonus.m_iMagicPowerMaxBonus += iBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					break;
				case SOPT_ATTACK_N_MAGIC_DAMAGE_MIN_BONUS:	// "�ּҰ��ݷ�/��������"
					m_StatusBonus.m_iAttackDamageMinBonus += iBonus;
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					m_StatusBonus.m_iMagicPowerMinBonus += iBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					break;
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
// 				case SOPT_DECREASE_AG_USE:				// "AG�Ҹ𷮰���"
#else YDG_FIX_SOCKET_BALANCE_PATCH
				case SOPT_SKILL_DAMAGE_BONUS:			// "��ų���ݷ�����"
					m_StatusBonus.m_iSkillAttackDamageBonus += iBonus;
					break;
				case SOPT_ATTACK_RATE_BONUS:			// "���ݼ���������"
					m_StatusBonus.m_iAttackRateBonus += iBonus;
					break;
				case SOPT_PVP_ATTACK_RATE_BONUS:		// "���ΰ��ݼ���������"
					m_StatusBonus.m_iPvPAttackRateBonus += iBonus;
					break;
				case SOPT_MAGIC_POWER_BONUS:			// "��������"
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					m_StatusBonus.m_iMagicPowerMinBonus += iBonus;
					m_StatusBonus.m_iMagicPowerMaxBonus += iBonus;
#else	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					m_StatusBonus.m_iMagicPowerBonus += iBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
					break;
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

				case SOPT_DEFENCE_RATE_BONUS:			// "����������"
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
					m_StatusBonus.m_fDefenceRateBonus *= 1.0f + iBonus * 0.01f;
#else	// YDG_FIX_SOCKET_BALANCE_PATCH
					m_StatusBonus.m_iDefenceRateBonus += iBonus;
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
					break;
				case SOPT_DEFENCE_BONUS:				// "��������"
					m_StatusBonus.m_iDefenceBonus += iBonus;
					break;
				case SOPT_SHIELD_DEFENCE_BONUS:			// "���й�������"
					m_StatusBonus.m_iShieldDefenceBonus += iBonus;
					break;
// 				case SOPT_DECREASE_DAMAGE:				// "����������"
// 				case SOPT_REFLECT_DAMAGE:				// "�������ݻ�"

// 				case SOPT_MONSTER_DEATH_LIFE_BONUS:		// "���ͻ���û�������"
// 				case SOPT_MONSTER_DEATH_MANA_BONUS:		// "���ͻ���ø�������"
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH
				case SOPT_SKILL_DAMAGE_BONUS:			// "��ų���ݷ�����"
					m_StatusBonus.m_iSkillAttackDamageBonus += iBonus;
					break;
				case SOPT_ATTACK_RATE_BONUS:			// "���ݼ���������"
					m_StatusBonus.m_iAttackRateBonus += iBonus;
					break;
// 				case SOPT_INCREASE_ITEM_DURABILITY:		// "�����۳���������"
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH
// 				case SOPT_SD_USE_RATE_BONUS:			// "SD���������" -> PvP�� �� ��� SD�� ���̴� ������ �ÿ��ش�
// 				case SOPT_IGNORE_SD_RATE_BONUS:			// "���ݽ�SD����Ȯ�����"

// 				case SOPT_LIFE_REGENERATION_BONUS:		// "�����ڵ�ȸ������"
// 				case SOPT_MAX_LIFE_BONUS:				// "�ִ��������"
// 				case SOPT_MAX_MANA_BONUS:				// "�ִ븶������"
// 				case SOPT_MANA_REGENERATION_BONUS:		// "�����ڵ�ȸ������"
// 				case SOPT_MAX_AG_BONUS:					// "�ִ�AG����"
// 				case SOPT_AG_REGENERATION_BONUS:		// "AG������"
#ifdef YDG_FIX_SOCKET_BALANCE_PATCH		// ������ �����ؾ���
// 				case SOPT_MONSTER_DEATH_ZEN_BONUS:		// "���ͻ����������"
#endif	// YDG_FIX_SOCKET_BALANCE_PATCH

// 				case SOPT_EXCELLENT_DAMAGE_BONUS:		// "������Ʈ����������"
// 				case SOPT_EXCELLENT_DAMAGE_RATE_BONUS:	// "������Ʈ������Ȯ������"
// 				case SOPT_CRITICAL_DAMAGE_BONUS:		// "ũ��Ƽ�õ���������"
// 				case SOPT_CRITICAL_DAMAGE_RATE_BONUS:	// "ũ��Ƽ�õ�����Ȯ������"

				case SOPT_STRENGTH_BONUS:				// "������"
					m_StatusBonus.m_iStrengthBonus += iBonus;
					break;
				case SOPT_DEXTERITY_BONUS:				// "��ø����"
					m_StatusBonus.m_iDexterityBonus += iBonus;
					break;
				case SOPT_VITALITY_BONUS:				// "ü������"
					m_StatusBonus.m_iVitalityBonus += iBonus;
					break;
				case SOPT_ENERGY_BONUS:					// "����������"
					m_StatusBonus.m_iEnergyBonus += iBonus;
					break;
// 				case SOPT_REQUIRED_STENGTH_BONUS:		// "�ʿ�������"
// 				case SOPT_REQUIRED_DEXTERITY_BONUS:		// "�ʿ��ø����"
				}
			}
		}
		
		if (pItem->SocketSeedSetOption != SOCKET_EMPTY)
		{
			pInfo = &m_SocketOptionInfo[SOT_MIX_SET_BONUS_OPTIONS][pItem->SocketSeedSetOption];
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
			int iBonus = CalcSocketOptionValue(pInfo->m_bOptionType, (float)pInfo->m_iOptionValue[0]);
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
			int iBonus = CalcSocketOptionValue(pInfo->m_bOptionType, (float)pInfo->m_iOptionValue, 1.0f);
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE

			switch(pInfo->m_iOptionID)
			{
			case SBOPT_ATTACK_DAMAGE_BONUS:			// "���ݷ� ���"
				m_StatusBonus.m_iAttackDamageMinBonus += iBonus;
				m_StatusBonus.m_iAttackDamageMaxBonus += iBonus;
				break;
			case SBOPT_SKILL_DAMAGE_BONUS:			// "��ų ���ݷ� ���"
			case SBOPT_SKILL_DAMAGE_BONUS_2:		// "��ų ���ݷ� ���"
				m_StatusBonus.m_iSkillAttackDamageBonus += iBonus;
				break;
			case SBOPT_MAGIC_POWER_BONUS:			// "���ݷ�/���� ���"
#ifdef YDG_FIX_SOCKET_BONUS_MAGIC_POWER_BONUS
				m_StatusBonus.m_iAttackDamageMinBonus += iBonus;
				m_StatusBonus.m_iAttackDamageMaxBonus += iBonus;
#endif	// YDG_FIX_SOCKET_BONUS_MAGIC_POWER_BONUS
#ifdef YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
				m_StatusBonus.m_iMagicPowerMinBonus += iBonus;
				m_StatusBonus.m_iMagicPowerMaxBonus += iBonus;
#else	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
				m_StatusBonus.m_iMagicPowerBonus += iBonus;
#endif	// YDG_FIX_SOCKET_MISSING_MAGIC_POWER_BONUS
				break;
			case SBOPT_DEFENCE_BONUS:				// "���� ���"
				m_StatusBonus.m_iDefenceBonus += iBonus;
				break;
//			case SBOPT_MAX_LIFE_BONUS:				// "�ִ� ���� ����"
			}
		}
	}
}

void CSocketItemMgr::OpenSocketItemScript(const unicode::t_char * szFileName)
{
	FILE *fp = fopen(szFileName,"rb");
	if(fp == NULL)
	{
		unicode::t_char Text[256];
    	unicode::_sprintf(Text,"%s - File not exist.",szFileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		return;
	}

	int iSize = sizeof(SOCKET_OPTION_INFO);
	for (int j = 0; j < MAX_SOCKET_OPTION_TYPES; ++j)
	{
		for (int i = 0; i < MAX_SOCKET_OPTION; ++i)
		{
			fread(&m_SocketOptionInfo[j][i], iSize, 1, fp);
			BuxConvert((BYTE*)&m_SocketOptionInfo[j][i], iSize);
		}
	}

#ifndef YDG_FIX_SCRIPT_LEVEL_VALUE
	iSize = sizeof(float);
	for (int i = 0; i < MAX_SPHERE_LEVEL; ++i)
	{
		fread(&m_fSphereValues[i], iSize, 1, fp);
		BuxConvert((BYTE*)&m_fSphereValues[i], iSize);
	}
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
	
	fclose(fp);

	// �˻��� ������� ��Ʈ�ɼ� ������ ���Ѵ�. (��ũ��Ʈ ���μ�)
#ifdef _VS2008PORTING
	for (int i = 0; i < MAX_SOCKET_OPTION; ++i)
	{
		m_iNumEquitSetBonusOptions = i;
		BYTE * pbySetTest = m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_bySocketCheckInfo;
		if (pbySetTest[0] + pbySetTest[1] + pbySetTest[2] + pbySetTest[3] + pbySetTest[4] + pbySetTest[5] == 0) break;
	}
#else // _VS2008PORTING
#ifdef YDG_FIX_SCRIPT_LEVEL_VALUE
	for (int i = 0; i < MAX_SOCKET_OPTION; ++i)
#else	// YDG_FIX_SCRIPT_LEVEL_VALUE
	for (i = 0; i < MAX_SOCKET_OPTION; ++i)
#endif	// YDG_FIX_SCRIPT_LEVEL_VALUE
	{
		BYTE * pbySetTest = m_SocketOptionInfo[SOT_EQUIP_SET_BONUS_OPTIONS][i].m_bySocketCheckInfo;
		if (pbySetTest[0] + pbySetTest[1] + pbySetTest[2] + pbySetTest[3] + pbySetTest[4] + pbySetTest[5] == 0) break;
	}
	m_iNumEquitSetBonusOptions = i;
#endif // _VS2008PORTING
}

#endif	// SOCKET_SYSTEM