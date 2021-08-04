#include "stdafx.h"
#include "MixMgr.h"
#include "./Utilities/Log/ErrorReport.h"
#include "UIManager.h"
#include "ZzzInventory.h"
#include "CSItemOption.h"
#include "UIJewelHarmony.h"
#ifdef ADD_SOCKET_MIX
#include "SocketSystem.h"
#endif	// ADD_SOCKET_MIX

using namespace SEASON3A;

/*+++++++++++++++++++++++++++++++++++++
    FUNCTIONS.
+++++++++++++++++++++++++++++++++++++*/
static BYTE bBuxCode[3] = {0xfc,0xcf,0xab};

static void BuxConvert(BYTE *Buffer,int Size)
{
	for(int i=0;i<Size;i++)
		Buffer[i] ^= bBuxCode[i%3];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMixRecipeMgr g_MixRecipeMgr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMixItem::Reset()
{
	m_sType = 0;
	m_iLevel = 0;
	m_iOption = 0;
	m_iDurability = 0;
	m_dwSpecialItem = 0;
	m_b380AddedItem = FALSE;
	m_bFenrirAddedItem = FALSE;
	m_bIsCharmItem = FALSE;
#ifdef PSW_ADD_MIX_CHAOSCHARM
	m_bIsChaosCharmItem = FALSE;
#endif //PSW_ADD_MIX_CHAOSCHARM	
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
	m_bIsJewelItem = FALSE;
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
	m_wHarmonyOption = 0;
	m_wHarmonyOptionLevel = 0;
	m_bMixLuck = FALSE;
	m_bIsEquipment = FALSE;
	m_bIsWing = FALSE;
	m_bIsUpgradedWing = FALSE;
	m_bIs3rdUpgradedWing = FALSE;
#ifdef ADD_SOCKET_MIX
	m_bySocketCount = 0;
	for (int i = 0; i < MAX_SOCKETS; ++i)
	{
		m_bySocketSeedID[i] = SOCKET_EMPTY;
		m_bySocketSphereLv[i] = 0;
	}
#endif	// ADD_SOCKET_MIX
	m_bCanStack = FALSE;
	m_dwMixValue = 0;
	m_iCount = 0;
	m_iTestCount = 0;
}

void CMixItem::SetItem(ITEM * pItem, DWORD dwMixValue)
{
	Reset();
	
	m_sType = pItem->Type;
	m_iLevel = ((pItem->Level>>3) & 15);
	m_iDurability = pItem->Durability;
	for (int i = 0; i < pItem->SpecialNum; i++)
	{
		switch ( pItem->Special[i])
		{
		case AT_IMPROVE_MAGIC:
		case AT_IMPROVE_CURSE:	// �߰� ���ַ�
		case AT_IMPROVE_DAMAGE:
		case AT_IMPROVE_DEFENSE:
		case AT_IMPROVE_BLOCKING:
			m_iOption = pItem->SpecialValue[i];		// �߰� ���ݷ� �� �ɼ�
			break;
		case AT_LIFE_REGENERATION:
			m_iOption = pItem->SpecialValue[i] * 4;		// ���� �ڵ� ȸ�� �ɼ� (*4 �ؼ� �ٸ� �ɼǰ� ������)
			break;
		case AT_LUCK:
			m_bMixLuck = TRUE;						// ���
			break;
		}
	}
	if ((pItem->Option1 & 63) > 0) m_dwSpecialItem |= RCP_SP_EXCELLENT;	// ������Ʈ
	if (pItem->RequireLevel >= 380) m_dwSpecialItem |= RCP_SP_ADD380ITEM;	// �䱸 ���� 380 �̻��� ���
	if ((pItem->ExtOption % 0x04) == EXT_A_SET_OPTION || (pItem->ExtOption % 0x04) == EXT_B_SET_OPTION) m_dwSpecialItem |= RCP_SP_SETITEM;	// ��Ʈ ������
	m_b380AddedItem = pItem->option_380;					// 380 �ɼ��� �̹� �߰��� ���������� ����

	if (pItem->Type >= ITEM_SWORD && pItem->Type <= ITEM_BOOTS+MAX_ITEM_INDEX-1)	// ��� ���������� �˻�
		m_bIsEquipment = TRUE;

	if (pItem->Type == ITEM_HELPER+37 && pItem->Option1 != 0)
		m_bFenrirAddedItem = TRUE;

	if (pItem->Type == ITEM_POTION+53)	// ����� �������� �˻�
		m_bIsCharmItem = TRUE;

#ifdef PSW_ADD_MIX_CHAOSCHARM
	if( pItem->Type == ITEM_POTION+96 )  //  ī���� �������� �˻�
		m_bIsChaosCharmItem = TRUE;
#endif //PSW_ADD_MIX_CHAOSCHARM

#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
	if(pItem->Type == ITEM_WING+15		// ȥ���Ǻ���
		|| pItem->Type == ITEM_WING+30		// �ູ�Ǻ��� ����
		|| pItem->Type == ITEM_WING+31		// ��ȥ�Ǻ��� ����
		|| pItem->Type == ITEM_POTION+13	// �ູ�Ǻ���
		|| pItem->Type == ITEM_POTION+14	// ��ȥ�Ǻ���
		|| pItem->Type == ITEM_POTION+16	// �����Ǻ���
		|| pItem->Type == ITEM_POTION+22	// â���Ǻ���
		|| pItem->Type == ITEM_POTION+31	// ��ȣ����
		|| pItem->Type == ITEM_POTION+42	// ��ȭ�Ǻ���
		)	// ���� ���������� �˻� (��,��,ȥ,â,��,��,��,������)
		m_bIsJewelItem = TRUE;
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE

#ifdef ADD_SOCKET_MIX
	m_bySocketCount = pItem->SocketCount;
	if (m_bySocketCount > 0)	// ���� ���������� �˻�
	{
		m_dwSpecialItem |= RCP_SP_SOCKETITEM;
		for (int i = 0; i < MAX_SOCKETS; ++i)
		{
			m_bySocketSeedID[i] = pItem->SocketSeedID[i];
			m_bySocketSphereLv[i] = pItem->SocketSphereLv[i];
		}
#ifdef YDG_FIX_SOCKETITEM_ISNOT_380ITEM
		m_dwSpecialItem ^= RCP_SP_ADD380ITEM;	// ���Ͼ������� 380 �������� �ƴϴ�
#endif	// YDG_FIX_SOCKETITEM_ISNOT_380ITEM
	}
	m_bySeedSphereID = g_SocketItemMgr.GetSeedShpereSeedID(pItem);
#endif	// ADD_SOCKET_MIX

	if (pItem->Jewel_Of_Harmony_Option > 0)
	{
		m_dwSpecialItem |= RCP_SP_HARMONY;	// ��ȭ�� ���� ���õ� ������
		m_wHarmonyOption = pItem->Jewel_Of_Harmony_Option;
		m_wHarmonyOptionLevel = pItem->Jewel_Of_Harmony_OptionLevel;
	}

	switch(pItem->Type)		// �������� �˻�
	{
	case ITEM_WING:			// ��������
	case ITEM_WING+1:		// õ������
	case ITEM_WING+2:		// ��ź����
#ifdef ADD_ALICE_WINGS_1
	case ITEM_WING+41:		// ����ǳ���
#endif	// ADD_ALICE_WINGS_1
		m_bIsWing = TRUE;
		break;
	case ITEM_WING+3:		// ���ɳ���
	case ITEM_WING+4:		// ��ȥ����
	case ITEM_WING+5:		// ���ﳯ��
	case ITEM_WING+6:		// ���泯��
	case ITEM_HELPER+30:	// ������ ����
#ifdef ADD_ALICE_WINGS_1
	case ITEM_WING+42:		// �����ǳ���
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+49:		// �����Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		m_bIsUpgradedWing = TRUE;
		break;
	case ITEM_WING+36:		// ��ǳ�ǳ���
	case ITEM_WING+37:		// �ð��ǳ���
	case ITEM_WING+38:		// ȯ���ǳ���
	case ITEM_WING+39:		// �ĸ��ǳ���
	case ITEM_WING+40:		// �����Ǹ���
#ifdef ADD_ALICE_WINGS_1
	case ITEM_WING+43:		// �����ǳ���
#endif	// ADD_ALICE_WINGS_1
#ifdef PBG_ADD_NEWCHAR_MONK_ITEM
	case ITEM_WING+50:		//�����Ǹ���
#endif //PBG_ADD_NEWCHAR_MONK_ITEM
		m_bIs3rdUpgradedWing = TRUE;
	}
#ifdef YDG_FIX_WING_MIX_RATE
	if (m_bIsWing || m_bIsUpgradedWing || m_bIs3rdUpgradedWing)
	{
		if (m_dwSpecialItem & RCP_SP_EXCELLENT)
			m_dwSpecialItem ^= RCP_SP_EXCELLENT;	// ������ ���� ����
	}
#endif	// YDG_FIX_WING_MIX_RATE
	switch(pItem->Type)		// ������ ������ ���������� �˻�
	{
	case ITEM_POTION+3:		// ūġ�Ṱ��
	case ITEM_POTION+38:	// ���� ���չ���
	case ITEM_POTION+39:	// �߰� ���չ���
	case ITEM_POTION+53:	// ����� ����
#ifdef CSK_EVENT_CHERRYBLOSSOM
	case ITEM_POTION+88:	// �Ͼ� ���ɰ���
	case ITEM_POTION+89:	// ���� ���ɰ���
	case ITEM_POTION+90:	// Ȳ�� ���ɰ���
#endif	// CSK_EVENT_CHERRYBLOSSOM
#ifdef KJH_PBG_ADD_SEVEN_EVENT_2008
	case ITEM_POTION+100:	//����� ����
#endif //KJH_PBG_ADD_SEVEN_EVENT_2008
		m_bCanStack = TRUE;
		break;
	}
	m_dwMixValue = dwMixValue;

	if (m_bCanStack == TRUE) m_iCount = m_iDurability;
	else m_iCount = 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CMixItemInventory::AddItem(ITEM * pItem)
{
//#define PJH_REPAIR_MIX  
#ifdef PJH_REPAIR_MIX
	BOOL bFind = TRUE;
#else
	BOOL bFind = FALSE;
#endif

	for (int i = 0; i < m_iNumMixItems; ++i)
	{
		if (m_MixItems[i] == pItem)	// �ߺ� ������
		{
			bFind = TRUE;
			m_MixItems[i].m_dwMixValue += EvaluateMixItemValue(pItem);
			if (m_MixItems[i].m_bCanStack == TRUE)
			{
				m_MixItems[i].m_iCount += pItem->Durability;
			}
			else
			{
				++m_MixItems[i].m_iCount;
			}
			break;
		}
	}
	if (bFind == FALSE)
	{
		// ������ �߰�
		m_MixItems[m_iNumMixItems++].SetItem(pItem, EvaluateMixItemValue(pItem));
	}

	return 0;
}

DWORD CMixItemInventory::EvaluateMixItemValue(ITEM * pItem)
{
	DWORD dwMixValue = 0;
	switch (pItem->Type)
	{
	case ITEM_WING+15:		// ȥ��
		dwMixValue = 40000;	//  810000
		break;
	case ITEM_POTION+13:	// �༮
		dwMixValue = 100000;	//  9000000
		break;
	case ITEM_POTION+14:	// ����
		dwMixValue = 70000;	//  6000000
		break;
	case ITEM_POTION+22:	// â��
		dwMixValue = 450000;	//  36000000
		break;
	case ITEM_POTION+16:	// ������ ����
		dwMixValue = 0;
		break;
	case ITEM_POTION+31:	//  ��ȣ����.
	default:
		dwMixValue = ItemValue(pItem, 0);
		break;
	}
	return dwMixValue;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMixRecipes::Reset()
{
	ClearCheckRecipeResult();
	std::vector<MIX_RECIPE *>::iterator iter;
	for (iter = m_Recipes.begin(); iter != m_Recipes.end(); ++iter)
	{
		if (*iter != NULL)
		{
			delete *iter;
			*iter = NULL;
		}
	}
	m_Recipes.clear();
}

void CMixRecipes::AddRecipe(MIX_RECIPE * pMixRecipe)
{
	if (pMixRecipe != NULL)
		m_Recipes.push_back(pMixRecipe);
}

BOOL CMixRecipes::IsMixSource(ITEM * pItem)
{
	CMixItem mixitem;
	mixitem.SetItem(pItem, 0);

#ifdef LEM_ADD_LUCKYITEM	// ��Ű������ ȯ���� �ǰ� [lem_2010.9.8]
	if( Check_LuckyItem( pItem->Type ) && g_MixRecipeMgr.GetMixInventoryType() != MIXTYPE_JERRIDON )	return FALSE;
#endif // LEM_ADD_LUCKYITEM

	if (IsCharmItem(mixitem))		// ����� ���� ������
	{
		if ((GetCurRecipe() == NULL || GetCurRecipe()->m_bCharmOption == 'A')
			&& m_wTotalCharmBonus + mixitem.m_iCount <= 10)	// ����� ���� Ȯ���� �ִ� 10%�� �����Ѵ�
		{
			return TRUE;
		}
	}

#ifdef PSW_ADD_MIX_CHAOSCHARM
	if( IsChaosCharmItem(mixitem)) {
		if ((GetCurRecipe() == NULL || GetCurRecipe()->m_bCharmOption == 'A')
			&& m_wTotalChaosCharmCount < 1) 
		{
			return TRUE;
		}
	}
#endif //PSW_ADD_MIX_CHAOSCHARM

	for (std::vector<MIX_RECIPE *>::iterator iter = m_Recipes.begin(); iter != m_Recipes.end(); ++iter)
	{
		// ���� ����� �� ��Ȳ�� �������� ��
		for (int j = 0; j < (*iter)->m_iNumMixSoruces; ++j)
		{
			if (m_wTotalCharmBonus > 0 && (*iter)->m_bCharmOption != 'A')
			{
				continue;	// ����� ������ �ö� �������� ����� ���� ���Ұ� ������ �� �� ����.
			}
			if (CheckItem((*iter)->m_MixSources[j], mixitem)
				&& !((*iter)->m_bMixOption == 'B' && IsChaosItem(mixitem))
				&& !((*iter)->m_bMixOption == 'C' && Is380AddedItem(mixitem))
				&& !((*iter)->m_bMixOption == 'D' && IsFenrirAddedItem(mixitem))
				&& !((*iter)->m_bMixOption == 'E' && !IsUpgradableItem(mixitem))
				&& !((*iter)->m_bMixOption == 'G' && !IsSourceOfRefiningStone(mixitem))
				)	// ���� ��� ����� �ϳ��� ���Եǳ�
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CMixRecipes::ClearCheckRecipeResult()
{
	m_iCurMixIndex = 0;
	m_iMostSimilarMixIndex = 0;
	m_iSuccessRate = 0;
	m_dwRequiredZen = 0;
	m_bFindMixLuckItem = FALSE;
	m_dwTotalItemValue = 0;
	m_dwExcellentItemValue = 0;
	m_dwEquipmentItemValue = 0;
	m_dwWingItemValue = 0;
	m_dwSetItemValue = 0;
	m_iFirstItemLevel = 0;
	m_iFirstItemType = 0;
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
	m_dwTotalNonJewelItemValue = 0;
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
#ifdef ADD_SOCKET_MIX
	m_byFirstItemSocketCount = 0;
	for (int i = 0; i < MAX_SOCKETS; ++i)
	{
		m_byFirstItemSocketSeedID[i] = SOCKET_EMPTY;
		m_byFirstItemSocketSphereLv[i] = 0;
	}
#endif	// ADD_SOCKET_MIX
	m_wTotalCharmBonus = 0;
}

int CMixRecipes::CheckRecipe(int iNumMixItems, CMixItem * pMixItems)	// ������ �κ� ������ ���� ����� ���Ͽ� ��� ��ȯ
{
	m_iCurMixIndex = 0;

#ifdef ADD_SOCKET_MIX
#ifdef KJW_FIX_SOCKET_INFORMATION
	m_byFirstItemSocketCount = 0;
#endif // KJW_FIX_SOCKET_INFORMATION
#endif	// ADD_SOCKET_MIX

	std::vector<MIX_RECIPE *>::iterator iter;
	for (iter = m_Recipes.begin(); iter != m_Recipes.end(); ++iter)
	{
		for (int i = 0; i < iNumMixItems; ++i)
		{
			pMixItems[i].m_iTestCount = pMixItems[i].m_iCount;	// �˻�� ī��Ʈ ������ �ʱ�ȭ
		}
		if (CheckRecipeSub(iter, iNumMixItems, pMixItems) == TRUE)	// ���� ����
		{
			m_iCurMixIndex = (*iter)->m_iMixIndex + 1;
			EvaluateMixItems(iNumMixItems, pMixItems);
			CalcCharmBonusRate(iNumMixItems, pMixItems);
			CalcMixRate(iNumMixItems, pMixItems);	// ���� ���� Ȯ�� ���
			CalcMixReqZen(iNumMixItems, pMixItems);	// ���� �ʿ� �� ���
			return GetCurRecipe()->m_iMixID;	    // ���� ��ȣ�� ��ȯ�ؾ��Ѵ�
		}
		else
		{
			m_iSuccessRate = 0;
			m_dwRequiredZen = 0;
		}
	}
	return (-1);
}

BOOL CMixRecipes::CheckRecipeSub(std::vector<MIX_RECIPE *>::iterator iter, int iNumMixItems, CMixItem * pMixItems)
{
	BOOL bFind = FALSE;
	int iMixRecipeTest[MAX_MIX_SOURCES];	// ���� ��Ằ�� ������ ��ġ ��
	memset(iMixRecipeTest, 0, sizeof(int) * MAX_MIX_SOURCES);

#ifdef ADD_SOCKET_MIX
#ifndef KJW_FIX_SOCKET_INFORMATION
	m_byFirstItemSocketCount = 0;
#endif // KJW_FIX_SOCKET_INFORMATION
#endif	// ADD_SOCKET_MIX

	// ���� ����� �� ��Ȳ�� �������� �κ��� ���� ������ ������ ����, ������ �κ����� ����� ��� ���Ѵ�
	for (int j = 0; j < (*iter)->m_iNumMixSoruces; ++j)
	{
		if (!IsOptionItem((*iter)->m_MixSources[j])) bFind = FALSE;
		for (int i = 0; i < iNumMixItems; ++i)
		{
			// ��ᰡ ��ġ�ϰ�, �ܷ��� �ְ�, ���� ���� ��Ằ ��ġ���� �� ����� �ܷ��� �ִ� �������� ������쿡
			if (CheckItem((*iter)->m_MixSources[j], pMixItems[i]) && pMixItems[i].m_iTestCount > 0 &&
				(*iter)->m_MixSources[j].m_iCountMax >= iMixRecipeTest[j] + pMixItems[i].m_iTestCount
#ifdef YDG_FIX_SOCKET_ATTACH_CONDITION
				&& !((*iter)->m_bMixOption == 'H' && IsSourceOfAttachSeedSphereToArmor(pMixItems[i]))	// ���������� ���Ǿ����� ����
				&& !((*iter)->m_bMixOption == 'I' && IsSourceOfAttachSeedSphereToWeapon(pMixItems[i]))
#endif	// YDG_FIX_SOCKET_ATTACH_CONDITION
				)
			{
				if (pMixItems[i].m_iTestCount >= (*iter)->m_MixSources[j].m_iCountMax)
				{
					iMixRecipeTest[j] += (*iter)->m_MixSources[j].m_iCountMax;
					pMixItems[i].m_iTestCount -= (*iter)->m_MixSources[j].m_iCountMax;	// �ִ�ġ��ŭ ������ �ִ�ġ�� ���ش�.
				}
				else
				{
					iMixRecipeTest[j] += pMixItems[i].m_iTestCount;
					pMixItems[i].m_iTestCount = 0;	// �ƴϸ� �ִ¸�ŭ �� ������.
				}
				bFind = TRUE;	// �������� ã�Ҵ�
				if (j == 0)
				{
					m_iFirstItemLevel = pMixItems[i].m_iLevel;	// ù��° �������̸� �������� ���� ����
					m_iFirstItemType = pMixItems[i].m_sType;
#ifdef ADD_SOCKET_MIX
					m_byFirstItemSocketCount = pMixItems[i].m_bySocketCount;	// ù��° �������̸� ���� ���� ����
					if (m_byFirstItemSocketCount > 0)
					{
						for (int k = 0; k < MAX_SOCKETS; ++k)
						{
							m_byFirstItemSocketSeedID[k] = pMixItems[i].m_bySocketSeedID[k];
							m_byFirstItemSocketSphereLv[k] = pMixItems[i].m_bySocketSphereLv[k];
						}
					}
#endif	// ADD_SOCKET_MIX
				}
			}
		}
		if (bFind == FALSE || (*iter)->m_MixSources[j].m_iCountMin > iMixRecipeTest[j])		// �ʿ��� �������� ��ã�ų� ��ᰡ ���ڸ��� ����
		{
			return FALSE;
		}
	}
	// ���� ��ᰡ ������ �ȵȴ�.
	for (int i = 0; i < iNumMixItems; ++i)
	{
		if (pMixItems[i].m_iTestCount > 0)
		{
			if (pMixItems[i].m_bIsCharmItem && (*iter)->m_bCharmOption == 'A');	// ����� ������ �־ �������.
			else
#ifdef PSW_ADD_MIX_CHAOSCHARM
			if(pMixItems[i].m_bIsChaosCharmItem && (*iter)->m_bChaosCharmOption == 'A'); // ī���� ������ �־ �������.
			else
#endif //PSW_ADD_MIX_CHAOSCHARM
				return FALSE;	// �ش� ���տ� �ʿ���� �������� �ִ�.
		}
	}
	return TRUE;	// �������� ��Ȯ�ϰ� �����Ѵ�.
}

int CMixRecipes::CheckRecipeSimilarity(int iNumMixItems, CMixItem * pMixItems)
{
	if (iNumMixItems == 0 && m_Recipes.size() == 1)	// ���� ����� �ϳ����϶��� �������� �ø��� �ʾƵ� ������ �����ش�.
	{
		m_iMostSimilarMixIndex = 1;
		for (int i = 0; i < (*m_Recipes.begin())->m_iNumMixSoruces; ++i)
		{
			m_iMostSimilarMixSourceTest[i] = (*m_Recipes.begin())->m_MixSources[0].m_iCountMax;
		}
		return m_iMostSimilarMixIndex;
	}

	int iMostSimiliarRecipe = 0;	// ���� ������ ���չ� �ε���
	int iMostSimiliarityPoint = 0;	// ���� ������ ���չ� ���絵 ����
	memset(m_iMostSimilarMixSourceTest, 0, sizeof(int) * MAX_MIX_SOURCES);
	memset(m_iMixSourceTest, 0, sizeof(int) * MAX_MIX_SOURCES);

	int iSimilarityPoint;			// ���絵 ����
	for (std::vector<MIX_RECIPE *>::iterator iter = m_Recipes.begin(); iter != m_Recipes.end(); ++iter)
	{
		memset(m_iMixSourceTest, 0, sizeof(int) * MAX_MIX_SOURCES);
		for (int i = 0; i < (*iter)->m_iNumMixSoruces; ++i)
			m_iMixSourceTest[i] = (*iter)->m_MixSources[i].m_iCountMax;	// ���չ� ���� �˻�� ī��Ʈ ������ �ʱ�ȭ
#ifdef _VS2008PORTING
		for (int i = 0; i < iNumMixItems; ++i)
#else // _VS2008PORTING
		for (i = 0; i < iNumMixItems; ++i)
#endif // _VS2008PORTING
			pMixItems[i].m_iTestCount = pMixItems[i].m_iCount;	// �˻�� ī��Ʈ ������ �ʱ�ȭ

		iSimilarityPoint = CheckRecipeSimilaritySub(iter, iNumMixItems, pMixItems);
		if (iSimilarityPoint == 1 && m_Recipes.size() > 1) iSimilarityPoint = 0;	// ȥ���� �ִ°�� ����
		if (iSimilarityPoint > iMostSimiliarityPoint ||
			(iSimilarityPoint == iMostSimiliarityPoint && iSimilarityPoint > 0 && m_iCurMixIndex == (*iter)->m_iMixIndex + 1))
		{
			// �߸��� �������� ������ �����ؾ��Ѵ�.
			iMostSimiliarityPoint = iSimilarityPoint;
			iMostSimiliarRecipe = (*iter)->m_iMixIndex + 1;
			memset(m_iMostSimilarMixSourceTest, 0, sizeof(int) * MAX_MIX_SOURCES);
			for (int i = 0; i < (*iter)->m_iNumMixSoruces; ++i)
			{
				m_iMostSimilarMixSourceTest[i] = m_iMixSourceTest[i];
			}
		}
	}
	m_iMostSimilarMixIndex = iMostSimiliarRecipe;
	return iMostSimiliarRecipe;
}

int CMixRecipes::CheckRecipeSimilaritySub(std::vector<MIX_RECIPE *>::iterator iter, int iNumMixItems, CMixItem * pMixItems)
{
	int iFindTotalPoint = 0;
	int iFindPoint = 0;
	// ���� ����� �� ��Ȳ�� �������� �κ��� ���� ������ ������ ���絵 ��ȯ
	for (int j = 0; j < (*iter)->m_iNumMixSoruces; ++j)
	{
		for (int i = 0; i < iNumMixItems; ++i)
		{
			if (CheckItem((*iter)->m_MixSources[j], pMixItems[i]) && pMixItems[i].m_iTestCount > 0
#ifdef YDG_FIX_SOCKET_ATTACH_CONDITION
				&& !((*iter)->m_bMixOption == 'H' && IsSourceOfAttachSeedSphereToArmor(pMixItems[i]))	// ���������� ���Ǿ����� ����
				&& !((*iter)->m_bMixOption == 'I' && IsSourceOfAttachSeedSphereToWeapon(pMixItems[i]))
#endif	// YDG_FIX_SOCKET_ATTACH_CONDITION
				)	// ���� ���
			{
				if (IsChaosJewel(pMixItems[i])) iFindPoint = 1;	// ȥ���� 1��
 				else if ((*iter)->m_MixSources[j].m_iCountMax < pMixItems[i].m_iTestCount) iFindPoint = 1;	// ������ ���չ����� ������ 0��
				else if (j == 0) iFindPoint = 10;	// ù��°�� ��ġ�ϸ� ���絵 ���ʽ� 10��
				else if (j == 1) iFindPoint = 5;	// �ι�°�� ��ġ�ϸ� ���絵 ���ʽ� 5��
				//else if (IsOptionItem((*iter)->m_MixSources[j])) iFindPoint = 2;	// �ɼ� �������� 0��
				else iFindPoint = 3;	// �������� 2��

				iFindTotalPoint += iFindPoint;

 				if (pMixItems[i].m_iTestCount > 0 && m_iMixSourceTest[j] > 0)
				{
					m_iMixSourceTest[j] -= pMixItems[i].m_iTestCount;
					pMixItems[i].m_iTestCount -= (*iter)->m_MixSources[j].m_iCountMax;	// �ִ�ġ�� ���ش�.
				}
			}
		}
	}
	for (int i = 0; i < iNumMixItems; ++i)
	{
		if (pMixItems[i].m_iTestCount > 0)
		{
			if (pMixItems[i].m_bIsCharmItem && (*iter)->m_bCharmOption == 'A');	// ����� ������ �־ �������.
			else
#ifdef PSW_ADD_MIX_CHAOSCHARM
			if (pMixItems[i].m_bIsChaosCharmItem && (*iter)->m_bChaosCharmOption == 'A'); // ī���� ������ �־ �������.
			else
#endif //PSW_ADD_MIX_CHAOSCHARM
				return 0;	// �ش� ���տ� �ʿ���� �������� �ִ�.
		}
	}
	return iFindTotalPoint;
}

bool CMixRecipes::CheckItem(MIX_RECIPE_ITEM & rItem, CMixItem & rSource)
{
	if (rItem.m_sTypeMin <= rSource.m_sType && rItem.m_sTypeMax >= rSource.m_sType &&
		rItem.m_iLevelMin <= rSource.m_iLevel && rItem.m_iLevelMax >= rSource.m_iLevel &&
		rItem.m_iDurabilityMin <= rSource.m_iDurability && rItem.m_iDurabilityMax >= rSource.m_iDurability &&
		rItem.m_iOptionMin <= rSource.m_iOption && rItem.m_iOptionMax >= rSource.m_iOption &&
		(rItem.m_dwSpecialItem & RCP_SP_EXCELLENT) <= (rSource.m_dwSpecialItem & RCP_SP_EXCELLENT) &&
		(rItem.m_dwSpecialItem & RCP_SP_ADD380ITEM) <= (rSource.m_dwSpecialItem & RCP_SP_ADD380ITEM) &&
		(rItem.m_dwSpecialItem & RCP_SP_SETITEM) <= (rSource.m_dwSpecialItem & RCP_SP_SETITEM)
		&& (rItem.m_dwSpecialItem & RCP_SP_HARMONY) <= (rSource.m_dwSpecialItem & RCP_SP_HARMONY)
#ifdef ADD_SOCKET_MIX
		&& (rItem.m_dwSpecialItem & RCP_SP_SOCKETITEM) <= (rSource.m_dwSpecialItem & RCP_SP_SOCKETITEM)
#endif	// ADD_SOCKET_MIX
		)
	{
		return true;
	}
	return false;
}

MIX_RECIPE * CMixRecipes::GetCurRecipe()
{
	if (m_iCurMixIndex == 0) return NULL;
	return m_Recipes[m_iCurMixIndex - 1];
}

MIX_RECIPE * CMixRecipes::GetMostSimilarRecipe()
{
	if (m_iMostSimilarMixIndex == 0) return NULL;
	return m_Recipes[m_iMostSimilarMixIndex - 1];
}

int CMixRecipes::GetCurMixID()
{
	if (m_iCurMixIndex == 0) return 0;
	return m_Recipes[m_iCurMixIndex - 1]->m_iMixID;
}

BOOL CMixRecipes::GetCurRecipeName(unicode::t_char * pszNameOut, int iNameLine)
{
	if (!IsReadyToMix())
	{
		if (iNameLine == 1)
		{
			switch(g_MixRecipeMgr.GetMixInventoryType())
			{
			case MIXTYPE_TRAINER:
				unicode::_sprintf (pszNameOut, GlobalText[1213], GlobalText[1212]);	// ��Ȱ�� ������ ������
				break;
			case MIXTYPE_OSBOURNE:
				unicode::_sprintf (pszNameOut, GlobalText[1213], GlobalText[2061]);	// ���ÿ� ������ ������
				break;
			case MIXTYPE_JERRIDON:
				unicode::_sprintf (pszNameOut, GlobalText[1213], GlobalText[2062]);	// ���ÿ� ������ ������
				break;
			case MIXTYPE_ELPIS:
				unicode::_sprintf (pszNameOut, GlobalText[1213], GlobalText[2063]);	// ������ ������ ������
				break;
			default:
				unicode::_sprintf (pszNameOut, "%s", GlobalText[601]);
				break;
			}
			return TRUE;
		}
		else return FALSE;
	}
	return GetRecipeName(GetCurRecipe(), pszNameOut, iNameLine, FALSE);
}

BOOL CMixRecipes::GetRecipeName(MIX_RECIPE * pRecipe, unicode::t_char * pszNameOut, int iNameLine, BOOL bSimilarRecipe)
{
	if (pRecipe == NULL) return FALSE;
	if (iNameLine > 2 || iNameLine < 1) return FALSE;
	if (pRecipe->m_bMixOption == 'C')	// 380 �ɼ�
	{
		vector<std::string> optionTextlist;
		// 380�������� Ÿ�Կ� ���� �ٸ� �ɼ��� �ٴ´�.
		g_pItemAddOptioninfo->GetItemAddOtioninfoText(optionTextlist, m_iFirstItemType);
		if (optionTextlist.empty() || bSimilarRecipe)
		{
			if (iNameLine == 1)
			{
				unicode::_sprintf (pszNameOut, "%s", GlobalText[2194]);
				return TRUE;
			}
			return FALSE;
		}
		assert(optionTextlist.size() == 2 && "�ɼ��� 2������ ��");
		if (iNameLine == 1)
		{
			unicode::_strcpy(pszNameOut, optionTextlist[0].c_str());
			return TRUE;
		}
		else if (iNameLine == 2)
		{
			unicode::_strcpy(pszNameOut, optionTextlist[1].c_str());
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		if (iNameLine == 1)
		{
			if (pRecipe->m_iMixName[1] == 0)
				unicode::_sprintf (pszNameOut, "%s", GlobalText[pRecipe->m_iMixName[0]]);
			else if (pRecipe->m_iMixName[2] == 0)
				unicode::_sprintf (pszNameOut, "%s %s", GlobalText[pRecipe->m_iMixName[0]], GlobalText[pRecipe->m_iMixName[1]]);
			else
				unicode::_sprintf (pszNameOut, "%s %s %s", GlobalText[pRecipe->m_iMixName[0]],
					GlobalText[pRecipe->m_iMixName[1]], GlobalText[pRecipe->m_iMixName[2]]);
			return TRUE;
		}
		return FALSE;
	}
}

BOOL CMixRecipes::GetCurRecipeDesc(unicode::t_char * pszDescOut, int iDescLine)
{
	if (iDescLine > 3 || iDescLine < 1) return FALSE;
	if (GetCurRecipe() == NULL) return FALSE;
	if (GetCurRecipe()->m_iMixDesc[iDescLine - 1] > 0)
		unicode::_strcpy(pszDescOut, GlobalText[GetCurRecipe()->m_iMixDesc[iDescLine - 1]]);
	else
		return FALSE;
	return TRUE;
}

BOOL CMixRecipes::GetMostSimilarRecipeName(unicode::t_char * pszNameOut, int iNameLine)
{
	return GetRecipeName(GetMostSimilarRecipe(), pszNameOut, iNameLine, TRUE);
}

BOOL CMixRecipes::GetRecipeAdvice(unicode::t_char * pszAdviceOut, int iAdivceLine)
{
	if (GetMostSimilarRecipe() == NULL) return FALSE;
	if (iAdivceLine > 3 || iAdivceLine < 1) return FALSE;

	if (GetMostSimilarRecipe()->m_iMixAdvice[iAdivceLine - 1] > 0)
		unicode::_strcpy(pszAdviceOut, GlobalText[GetMostSimilarRecipe()->m_iMixAdvice[iAdivceLine - 1]]);
	else
		return FALSE;
	return TRUE;
}

int CMixRecipes::GetSourceName(int iItemNum, unicode::t_char * pszNameOut, int iNumMixItems, CMixItem * pMixItems)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(iNumMixItems < 0)	return MIX_SOURCE_ERROR;
	if(pMixItems == NULL)	return MIX_SOURCE_ERROR;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	if (GetMostSimilarRecipe() == NULL) return MIX_SOURCE_ERROR;
	if (iItemNum >= GetMostSimilarRecipe()->m_iNumMixSoruces) return MIX_SOURCE_ERROR;

	MIX_RECIPE_ITEM * pMixRecipeItem = &GetMostSimilarRecipe()->m_MixSources[iItemNum];

	unicode::t_char szTempName[100];
	GetItemName(pMixRecipeItem->m_sTypeMin, pMixRecipeItem->m_iLevelMin, szTempName);

	// ���� �̸� ������
 	if (pMixRecipeItem->m_sTypeMin == pMixRecipeItem->m_sTypeMax &&
		(pMixRecipeItem->m_iLevelMin == pMixRecipeItem->m_iLevelMax || (pMixRecipeItem->m_iLevelMin == 0 && pMixRecipeItem->m_iLevelMax == 255)) &&
		(pMixRecipeItem->m_iOptionMin == pMixRecipeItem->m_iOptionMax || (pMixRecipeItem->m_iOptionMin == 0 && pMixRecipeItem->m_iOptionMax == 255)))
	{
		// ������ ������
		if (pMixRecipeItem->m_iDurabilityMin == pMixRecipeItem->m_iDurabilityMax)
			unicode::_sprintf(szTempName, "%s(%d)", szTempName, pMixRecipeItem->m_iDurabilityMin);
	}
	else	// ���� �̸� ������
	{
		// ������ �̸�
		if (pMixRecipeItem->m_dwSpecialItem & RCP_SP_ADD380ITEM)
			unicode::_sprintf(szTempName, GlobalText[2335]);	// "380���� ������"
		else if (pMixRecipeItem->m_sTypeMin == 0 && pMixRecipeItem->m_sTypeMax == ITEM_BOOTS+MAX_ITEM_INDEX-1)
			unicode::_sprintf(szTempName, GlobalText[2336]);	// "��������"
		else if (pMixRecipeItem->m_sTypeMin == 0 && pMixRecipeItem->m_sTypeMax == ITEM_HELPER+MAX_ITEM_INDEX-1)
			unicode::_sprintf(szTempName, GlobalText[2336]);	// "��������" ��������
		else if (pMixRecipeItem->m_sTypeMin == 0 && pMixRecipeItem->m_sTypeMax == ITEM_STAFF+MAX_ITEM_INDEX-1)
			unicode::_sprintf(szTempName, GlobalText[2337]);	// "���������"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_SHIELD && pMixRecipeItem->m_sTypeMax == ITEM_BOOTS+MAX_ITEM_INDEX-1)
			unicode::_sprintf(szTempName, GlobalText[2338]);	// "��������"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING && pMixRecipeItem->m_sTypeMax == ITEM_WING+2)
			unicode::_sprintf(szTempName, GlobalText[2339]);	// "1������"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+3 && pMixRecipeItem->m_sTypeMax == ITEM_WING+6)
			unicode::_sprintf(szTempName, GlobalText[2348]);	// "2������"
#ifdef ADD_ALICE_WINGS_1
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+41 && pMixRecipeItem->m_sTypeMax == ITEM_WING+41)
			unicode::_sprintf(szTempName, GlobalText[2339]);	// "1������"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+42 && pMixRecipeItem->m_sTypeMax == ITEM_WING+42)
			unicode::_sprintf(szTempName, GlobalText[2348]);	// "2������"
#endif	// ADD_ALICE_WINGS_1
		else if (pMixRecipeItem->m_sTypeMin == pMixRecipeItem->m_sTypeMax &&
			(pMixRecipeItem->m_sTypeMin == ITEM_MACE+6 || pMixRecipeItem->m_sTypeMin == ITEM_BOW+6 || pMixRecipeItem->m_sTypeMin == ITEM_STAFF+7))
			unicode::_sprintf(szTempName, GlobalText[2340]);	// "ī��������"
#ifdef ADD_SOCKET_MIX
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+60 && pMixRecipeItem->m_sTypeMax == ITEM_WING+65)
			unicode::_sprintf(szTempName, GlobalText[2680]);	// "�õ�"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+70 && pMixRecipeItem->m_sTypeMax == ITEM_WING+74)
			unicode::_sprintf(szTempName, GlobalText[2681]);	// "���Ǿ�"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+100 && pMixRecipeItem->m_sTypeMax == ITEM_WING+129)
			unicode::_sprintf(szTempName, GlobalText[2682]);	// "�õ� ���Ǿ�"
#ifdef YDG_FIX_SOCKET_ATTACH_CONDITION
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+100 && pMixRecipeItem->m_sTypeMax == ITEM_WING+128)
			unicode::_sprintf(szTempName, "%s (%s)", GlobalText[2682], GlobalText[2684]);	// "�õ� ���Ǿ� (��,����,����)"
		else if (pMixRecipeItem->m_sTypeMin == ITEM_WING+101 && pMixRecipeItem->m_sTypeMax == ITEM_WING+129)
			unicode::_sprintf(szTempName, "%s (%s)", GlobalText[2682], GlobalText[2685]);	// "�õ� ���Ǿ� (��,�ٶ�)"
#endif	// YDG_FIX_SOCKET_ATTACH_CONDITION
#endif	// ADD_SOCKET_MIX
		else
		{
			// �̸��� ����
			int iNameLen = unicode::_strlen(szTempName);
			for (int j = 1; j <= 3 && iNameLen - j - 1 >= 0; ++j)
				if (szTempName[iNameLen - j] == '+') szTempName[iNameLen - j - 1] = '\0';	// ���� �߶����
		}
		// ������ ������
		if (pMixRecipeItem->m_iDurabilityMin == pMixRecipeItem->m_iDurabilityMax)
			unicode::_sprintf(szTempName, "%s(%d)", szTempName, pMixRecipeItem->m_iDurabilityMin);
		// ������ ����
		if (pMixRecipeItem->m_iLevelMin == 0 && pMixRecipeItem->m_iLevelMax == 255);	// ��� ���� ����
		else if (pMixRecipeItem->m_iLevelMin == pMixRecipeItem->m_iLevelMax)	// ���� ����
			unicode::_sprintf(szTempName, "%s +%d", szTempName, pMixRecipeItem->m_iLevelMin);
		else if (pMixRecipeItem->m_iLevelMin == 0)	// max���� ����
			unicode::_sprintf(szTempName, "%s +%d%s", szTempName, pMixRecipeItem->m_iLevelMax, GlobalText[2342]);	// "����"
		else if (pMixRecipeItem->m_iLevelMax == 255)	// min���� �̻�
			unicode::_sprintf(szTempName, "%s +%d%s", szTempName, pMixRecipeItem->m_iLevelMin, GlobalText[2341]);	// "�̻�"
		else
			unicode::_sprintf(szTempName, "%s +%d~%d", szTempName, pMixRecipeItem->m_iLevelMin, pMixRecipeItem->m_iLevelMax);
		// ������ �ɼ�
		if (pMixRecipeItem->m_iOptionMin == 0 && pMixRecipeItem->m_iOptionMax == 255);	// ��� �ɼ� ����
		else if (pMixRecipeItem->m_iOptionMin == pMixRecipeItem->m_iOptionMax)	// ���� �ɼ�
			unicode::_sprintf(szTempName, "%s +%d%s", szTempName, pMixRecipeItem->m_iOptionMin, GlobalText[2343]);	// "�ɼ�"
		else if (pMixRecipeItem->m_iOptionMin == 0)	// max�ɼ� ����
			unicode::_sprintf(szTempName, "%s +%d%s%s", szTempName, pMixRecipeItem->m_iOptionMax, GlobalText[2343], GlobalText[2342]);	// "�ɼ�""����"
		else if (pMixRecipeItem->m_iOptionMax == 255)	// min�ɼ� �̻�
			unicode::_sprintf(szTempName, "%s +%d%s%s", szTempName, pMixRecipeItem->m_iOptionMin, GlobalText[2343], GlobalText[2341]);	// "�ɼ�""�̻�"
		else
			unicode::_sprintf(szTempName, "%s +%d~%d%s", szTempName, pMixRecipeItem->m_iOptionMin, pMixRecipeItem->m_iOptionMax, GlobalText[2343]);	// "�ɼ�"
	}
	// ������ ����
	if (pMixRecipeItem->m_iCountMin == 0 && pMixRecipeItem->m_iCountMax == 255)	// ��� ���� ����
		unicode::_sprintf(szTempName, "%s (%s)", szTempName, GlobalText[2344]);	// "Ȯ������"
	else if (pMixRecipeItem->m_iCountMin == pMixRecipeItem->m_iCountMax)	// ���� ����
		unicode::_sprintf(szTempName, "%s %d%s", szTempName, pMixRecipeItem->m_iCountMin, GlobalText[2345]);	// "��"
	else if (pMixRecipeItem->m_iCountMin == 0)	// max���� ����
		unicode::_sprintf(szTempName, "%s %d%s %s", szTempName, pMixRecipeItem->m_iCountMax, GlobalText[2345], GlobalText[2342]);	// "��""����"
	else if (pMixRecipeItem->m_iCountMax == 255)	// min���� �̻�
		unicode::_sprintf(szTempName, "%s %d%s %s", szTempName, pMixRecipeItem->m_iCountMin, GlobalText[2345], GlobalText[2341]);	// "��""�̻�"
	else
		unicode::_sprintf(szTempName, "%s %d~%d%s", szTempName, pMixRecipeItem->m_iCountMin, pMixRecipeItem->m_iCountMax, GlobalText[2345]);	// "��"

	// ������Ʈ+��Ʈ ���ξ�
	BOOL bPreName = FALSE;
	if (pMixRecipeItem->m_dwSpecialItem & RCP_SP_EXCELLENT)
	{
		unicode::_sprintf(pszNameOut, "%s %s", GlobalText[620], szTempName);	// ������Ʈ
		bPreName = TRUE;
	}
	if (pMixRecipeItem->m_dwSpecialItem & RCP_SP_SETITEM)
	{
		unicode::_sprintf(pszNameOut, "%s %s", GlobalText[1089], szTempName);	// ��Ʈ
		bPreName = TRUE;
	}
	if (pMixRecipeItem->m_dwSpecialItem & RCP_SP_HARMONY)
	{
#ifdef SOCKET_SYSTEM
		unicode::_sprintf(pszNameOut, "%s %s", GlobalText[1550], szTempName);	// ��ȭ�� ������
#else	// SOCKET_SYSTEM
		unicode::_sprintf(pszNameOut, "%s %s", GlobalText[2061], szTempName);	// ���õ� ������
#endif	// SOCKET_SYSTEM
		bPreName = TRUE;
	}
#ifdef ADD_SOCKET_MIX
	if (pMixRecipeItem->m_dwSpecialItem & RCP_SP_SOCKETITEM)
	{
		unicode::_sprintf(pszNameOut, "%s %s", GlobalText[2650], szTempName);	// ���� ������
		bPreName = TRUE;
	}
#endif	// ADD_SOCKET_MIX
	if (bPreName == FALSE)
	{
		unicode::_strcpy(pszNameOut ,szTempName);
	}

	if (g_MixRecipeMgr.IsMixInit())
	{
		if (pMixRecipeItem->m_iCountMin == 0) return MIX_SOURCE_PARTIALLY;
		else return MIX_SOURCE_NO;
	}

	if (m_iMostSimilarMixSourceTest[iItemNum] == 0)	// ��� ��ġ
		return MIX_SOURCE_YES;
	else if (m_iMostSimilarMixSourceTest[iItemNum] < pMixRecipeItem->m_iCountMax)	// �ɼ� ��� ��ġ or �κ� ��ġ
	{
		if (pMixRecipeItem->m_iCountMin <= 1) return MIX_SOURCE_YES;
		else return MIX_SOURCE_PARTIALLY;
	}
	else	// ��� ����
	{
		if (pMixRecipeItem->m_iCountMin == 0) return MIX_SOURCE_PARTIALLY;
		else return MIX_SOURCE_NO;
	}
}

void CMixRecipes::EvaluateMixItems(int iNumMixItems, CMixItem * pMixItems)
{
	m_bFindMixLuckItem = FALSE;
	m_dwTotalItemValue = 0;
	m_dwExcellentItemValue = 0;
	m_dwEquipmentItemValue = 0;
	m_dwWingItemValue = 0;
	m_dwSetItemValue = 0;
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
	m_dwTotalNonJewelItemValue = 0;
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
	for (int i = 0; i < iNumMixItems; ++i)
	{
		if (pMixItems[i].m_bMixLuck == TRUE) m_bFindMixLuckItem = TRUE;	// ��� �ɼ� Ȯ��
		if (pMixItems[i].m_dwSpecialItem & RCP_SP_EXCELLENT) m_dwExcellentItemValue += pMixItems[i].m_dwMixValue;	// ���۰���
		if (pMixItems[i].m_bIsEquipment == TRUE) m_dwEquipmentItemValue += pMixItems[i].m_dwMixValue;	// ����/�� ����
		if (pMixItems[i].m_bIsWing == TRUE) m_dwWingItemValue += pMixItems[i].m_dwMixValue;	// ���� ����
		if (pMixItems[i].m_dwSpecialItem & RCP_SP_SETITEM) m_dwSetItemValue += pMixItems[i].m_dwMixValue;	// ��Ʈ������ ����
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
		if (pMixItems[i].m_bIsJewelItem == FALSE) m_dwTotalNonJewelItemValue += pMixItems[i].m_dwMixValue;	// �����ƴ� ������ ��ü ����
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
		m_dwTotalItemValue += pMixItems[i].m_dwMixValue;	// ��ü ����
	}
}

void CMixRecipes::CalcCharmBonusRate(int iNumMixItems, CMixItem * pMixItems)
{
	m_wTotalCharmBonus = 0;
	for (int i = 0; i < iNumMixItems; ++i)
	{
		if (pMixItems[i].m_bIsCharmItem == TRUE) m_wTotalCharmBonus += pMixItems[i].m_iCount;	// ����� ���� Ȯ�� ��
	}
}

#ifdef PSW_ADD_MIX_CHAOSCHARM
void CMixRecipes::CalcChaosCharmCount(int iNumMixItems, CMixItem * pMixItems)
{
	m_wTotalChaosCharmCount = 0;
	for (int i = 0; i < iNumMixItems; ++i)
	{
		if (pMixItems[i].m_bIsChaosCharmItem == TRUE) m_wTotalChaosCharmCount += 1;
	}
}
#endif //PSW_ADD_MIX_CHAOSCHARM

// ���ս� ���� Ȯ�� ���
void CMixRecipes::CalcMixRate(int iNumMixItems, CMixItem * pMixItems)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(iNumMixItems < 0)	return;
	if(pMixItems == NULL)	return;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	m_iSuccessRate = 0;
	if (GetCurRecipe() == NULL) return;

	m_pMixRates = GetCurRecipe()->m_RateToken;
	m_iMixRateIter = 0;
	m_iSuccessRate = (int)MixrateAddSub();

	if (m_iSuccessRate > GetCurRecipe()->m_iSuccessRate)
	{
		m_iSuccessRate = GetCurRecipe()->m_iSuccessRate;	// �ִ�Ȯ��
	}
	if (GetCurRecipe()->m_bCharmOption == 'A')	// ����� ����
	{
		m_iSuccessRate += m_wTotalCharmBonus;
	}
	if (m_iSuccessRate > 100)
	{
		m_iSuccessRate = 100;
	}
}

float CMixRecipes::MixrateAddSub()
{
	float fLvalue = 0;
	while(1)
	{
		if (m_iMixRateIter >= GetCurRecipe()->m_iNumRateData || m_pMixRates[m_iMixRateIter].op == MRCP_RP)	// ������ ��, �ݴ� ��ȣ
		{
			return fLvalue;
		}
		switch(m_pMixRates[m_iMixRateIter].op)
		{
		case MRCP_ADD:
			++m_iMixRateIter;
			fLvalue += MixrateMulDiv();
			break;
		case MRCP_SUB:
 			++m_iMixRateIter;
			fLvalue -= MixrateMulDiv();
			break;
		default:
			fLvalue = MixrateMulDiv();	// ������ ù��
			break;
		};
	}
}

float CMixRecipes::MixrateMulDiv()
{
	float fLvalue = 0;
	while(1)
	{
		if (m_iMixRateIter >= GetCurRecipe()->m_iNumRateData || m_pMixRates[m_iMixRateIter].op == MRCP_RP)	// ������ ��, �ݴ� ��ȣ
		{
			return fLvalue;
		}
		switch(m_pMixRates[m_iMixRateIter].op)
		{
		case MRCP_ADD:
		case MRCP_SUB:
			return fLvalue;
		case MRCP_MUL:
 			++m_iMixRateIter;
			fLvalue *= MixrateFactor();
 			break;
		case MRCP_DIV:
			++m_iMixRateIter;
			fLvalue /= MixrateFactor();
 			break;
		default:
			fLvalue = MixrateFactor();	// ������ ù��
 			break;
		};
	}
}

float CMixRecipes::MixrateFactor()
{
	float fValue = 0;
	switch(m_pMixRates[m_iMixRateIter].op)
	{
	case MRCP_LP:
		++m_iMixRateIter;
		fValue = MixrateAddSub();
		break;
	case MRCP_INT:
		++m_iMixRateIter;
		if (m_pMixRates[m_iMixRateIter].op != MRCP_LP) assert(!"��������");
		++m_iMixRateIter;	// ( ��ŵ
		fValue = int(MixrateAddSub());
		break;
	case MRCP_NUMBER:
		fValue = (float)m_pMixRates[m_iMixRateIter].value;	// ��� ��
		break;
	case MRCP_MAXRATE:	// ��ũ��Ʈ�� �ִ� Ȯ��
		fValue = GetCurRecipe()->m_iSuccessRate;
		break;
	case MRCP_ITEM:			// ����â ������ ���� ����
		fValue = m_dwTotalItemValue;
		break;
	case MRCP_WING:			// ����â ���� ���� ����
		fValue = m_dwWingItemValue;
		break;
	case MRCP_EXCELLENT:		// ����â ���� ���� ����
		fValue = m_dwExcellentItemValue;
		break;
	case MRCP_EQUIP:			// ����â ����+�� ���� ����
		fValue = m_dwEquipmentItemValue;
		break;
	case MRCP_SET:			// ����â ��Ʈ������ ���� ����
		fValue = m_dwSetItemValue;
		break;
	case MRCP_LUCKOPT:		// �������� ��� �ɼ� ���ʽ� ��
		if (m_bFindMixLuckItem) fValue = 25;
		else fValue = 0;
		break;
	case MRCP_LEVEL1:		// ���� ���� ù��° �������� ���� (1~13)
		fValue = m_iFirstItemLevel;
		break;
#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
	case MRCP_NONJEWELITEM:	// ���������� ������ ����â ������ ���� ���� (��,��,ȥ,â,��,��,��,������)
		fValue = m_dwTotalNonJewelItemValue;
		break;
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE
	}
	++m_iMixRateIter;
	return fValue;
}

void CMixRecipes::CalcMixReqZen(int iNumMixItems, CMixItem * pMixItems)
{
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
	if(iNumMixItems < 0)	return;
	if(pMixItems == NULL)	return;
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	// ���ս� �ʿ� ��
	//	�ʿ� �� Ÿ�� A: [���� �ݾ�]
	//	�ʿ� �� Ÿ�� B: [Ȯ��] * 10,000��
	//	�ʿ� �� Ÿ�� C: [���� �ݾ�] (����� �ݾ�)
	//	�ʿ� �� Ÿ�� D: [���÷����� ���� ���þ����� ȯ�� ���̺� �̿�]
	m_dwRequiredZen = 0;
	if (GetCurRecipe() == NULL) return;
	switch(GetCurRecipe()->m_bRequiredZenType)
	{
	case 'A':
	case 'C':	// ��½ÿ� ����� �������� ǥ��
		m_dwRequiredZen = GetCurRecipe()->m_dwRequiredZen;
		break;
	case 'B':
		m_dwRequiredZen = m_iSuccessRate * GetCurRecipe()->m_dwRequiredZen;
		break;
	case 'D':
		{
			// ��ȭ�� ���� ���� ������ ȯ�� ���� ����
			int iItemType = 0;
			if( ITEM_SWORD <= pMixItems[0].m_sType && ITEM_STAFF > pMixItems[0].m_sType )
			{
				iItemType = SI_Weapon;
			}
			else if( ITEM_STAFF <= pMixItems[0].m_sType && ITEM_SHIELD > pMixItems[0].m_sType )
			{
				iItemType = SI_Staff;
			}
			else if( ITEM_SHIELD <= pMixItems[0].m_sType && ITEM_WING > pMixItems[0].m_sType )
			{
				iItemType = SI_Defense;
			}
			m_dwRequiredZen = g_pUIJewelHarmonyinfo->GetHarmonyJewelOptionInfo(iItemType,
				pMixItems[0].m_wHarmonyOption ).Zen[pMixItems[0].m_wHarmonyOptionLevel];
		}
		break;
	default:
		break;
	}
}

// ���տɼ� ���� �˻��
BOOL CMixRecipes::IsChaosItem(CMixItem & rSource)
{
	if (rSource.m_sType == ITEM_MACE+6 || rSource.m_sType == ITEM_BOW+6 || rSource.m_sType == ITEM_STAFF+7) return TRUE;
	return FALSE;
}

BOOL CMixRecipes::IsChaosJewel(CMixItem & rSource)
{
	if (rSource.m_sType == ITEM_WING+15) return TRUE;
	return FALSE;
}

BOOL CMixRecipes::Is380AddedItem(CMixItem & rSource)
{
	return rSource.m_b380AddedItem;
}

BOOL CMixRecipes::IsFenrirAddedItem(CMixItem & rSource)
{
	return rSource.m_bFenrirAddedItem;
}

BOOL CMixRecipes::IsUpgradableItem(CMixItem & rSource)
{
	return (rSource.m_bIsEquipment || rSource.m_bIsWing || rSource.m_bIsUpgradedWing || rSource.m_bIs3rdUpgradedWing);
}

BOOL CMixRecipes::IsSourceOfRefiningStone(CMixItem & rSource)
{
	if (rSource.m_iLevel < 4)
	{
		switch(rSource.m_sType)
		{
		case ITEM_SWORD+0: case ITEM_SWORD+1: case ITEM_SWORD+2: case ITEM_SWORD+4:
		case ITEM_AXE+0: case ITEM_AXE+1: case ITEM_AXE+2:
		case ITEM_MACE+0: case ITEM_MACE+1: case ITEM_MACE+2:
		case ITEM_SPEAR+1: case ITEM_SPEAR+2: case ITEM_SPEAR+3: case ITEM_SPEAR+5: case ITEM_SPEAR+6:
		case ITEM_BOW+0: case ITEM_BOW+1: case ITEM_BOW+2: case ITEM_BOW+3:
		case ITEM_BOW+8: case ITEM_BOW+9: case ITEM_BOW+10: case ITEM_BOW+11:
		case ITEM_STAFF+0: case ITEM_STAFF+1: case ITEM_STAFF+2:
		case ITEM_SHIELD+0: case ITEM_SHIELD+1: case ITEM_SHIELD+2: case ITEM_SHIELD+3: case ITEM_SHIELD+4:
		case ITEM_SHIELD+6: case ITEM_SHIELD+7: case ITEM_SHIELD+9: case ITEM_SHIELD+10:
		case ITEM_HELM+0: case ITEM_HELM+2: case ITEM_HELM+4: case ITEM_HELM+5: case ITEM_HELM+6:
		case ITEM_HELM+7: case ITEM_HELM+8: case ITEM_HELM+10: case ITEM_HELM+11: case ITEM_HELM+12:
		case ITEM_ARMOR+0: case ITEM_ARMOR+2: case ITEM_ARMOR+4: case ITEM_ARMOR+5: case ITEM_ARMOR+6:
		case ITEM_ARMOR+7: case ITEM_ARMOR+8: case ITEM_ARMOR+10: case ITEM_ARMOR+11: case ITEM_ARMOR+12:
		case ITEM_PANTS+0: case ITEM_PANTS+2: case ITEM_PANTS+4: case ITEM_PANTS+5: case ITEM_PANTS+6:
		case ITEM_PANTS+7: case ITEM_PANTS+8: case ITEM_PANTS+10: case ITEM_PANTS+11: case ITEM_PANTS+12:
		case ITEM_GLOVES+0: case ITEM_GLOVES+2: case ITEM_GLOVES+4: case ITEM_GLOVES+5: case ITEM_GLOVES+6:
		case ITEM_GLOVES+7: case ITEM_GLOVES+8: case ITEM_GLOVES+10: case ITEM_GLOVES+11: case ITEM_GLOVES+12:
		case ITEM_BOOTS+0: case ITEM_BOOTS+2: case ITEM_BOOTS+4: case ITEM_BOOTS+5: case ITEM_BOOTS+6:
		case ITEM_BOOTS+7: case ITEM_BOOTS+8: case ITEM_BOOTS+10: case ITEM_BOOTS+11: case ITEM_BOOTS+12:
			return FALSE;
		}
	}
	return TRUE;
}

#ifdef YDG_FIX_SOCKET_ATTACH_CONDITION
BOOL CMixRecipes::IsSourceOfAttachSeedSphereToWeapon(CMixItem & rSource)
{
	if (rSource.m_sType >= ITEM_WING+100 && rSource.m_sType <= ITEM_WING+129)
	{
		int iSeedSphereType = rSource.m_sType - ITEM_WING;

		// �� ���� ���� �Ӽ��� ITEM_WING+100, 102 �� ¦���ε����̴�
		if (iSeedSphereType % 2 == 0) return TRUE;
	}
	return FALSE;
}

BOOL CMixRecipes::IsSourceOfAttachSeedSphereToArmor(CMixItem & rSource)
{
	if (rSource.m_sType >= ITEM_WING+100 && rSource.m_sType <= ITEM_WING+129)
	{
		int iSeedSphereType = rSource.m_sType - ITEM_WING;

		// �� �ٶ� �� �Ӽ��� ITEM_WING+101, 103 �� Ȧ���ε����̴�
		if (iSeedSphereType % 2 == 1) return TRUE;
	}
	return FALSE;
}
#endif	// YDG_FIX_SOCKET_ATTACH_CONDITION

BOOL CMixRecipes::IsCharmItem(CMixItem & rSource)
{
	return rSource.m_bIsCharmItem;
}

#ifdef PSW_ADD_MIX_CHAOSCHARM
BOOL CMixRecipes::IsChaosCharmItem(CMixItem & rSource)
{
	return rSource.m_bIsChaosCharmItem;
}
#endif //PSW_ADD_MIX_CHAOSCHARM

#ifdef YDG_FIX_SOCKETSPHERE_MIXRATE
BOOL CMixRecipes::IsJewelItem(CMixItem & rSource)
{
	return rSource.m_bIsJewelItem;
}
#endif	// YDG_FIX_SOCKETSPHERE_MIXRATE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMixRecipeMgr::OpenRecipeFile(const unicode::t_char * szFileName)	// mix.bmd�� �о���δ�.
{
	int i, j;
	for (j = 0; j < MAX_MIX_TYPES; ++j)
	{
		m_MixRecipe[j].Reset();
	}

	FILE *fp = fopen(szFileName,"rb");
	if(fp == NULL)
	{
		unicode::t_char Text[256];
    	unicode::_sprintf(Text,"%s - File not exist.",szFileName);
		g_ErrorReport.Write( Text);
		MessageBox(g_hWnd,Text,NULL,MB_OK);
		SendMessage(g_hWnd,WM_DESTROY,0,0);
		exit(0);
	}

	int iNumMixRecipes[MAX_MIX_TYPES];
	int iSize = sizeof(int) * MAX_MIX_TYPES;
	fread(iNumMixRecipes, iSize, 1, fp);	// �� ���� ��� ��
	BuxConvert((BYTE*)iNumMixRecipes, iSize);

	iSize = sizeof(MIX_RECIPE);
	for (j = 0; j < MAX_MIX_TYPES; ++j)
	{
#ifdef SOCKET_SYSTEM
#ifdef LJH_MOD_EXTENDING_NUM_OF_MIX_RECIPES_FROM_100_TO_1000 
		if (feof(fp) || iNumMixRecipes[j] > 1000)
#else  //LJH_MOD_EXTENDING_NUM_OF_MIX_RECIPES_FROM_100_TO_1000
		if (feof(fp) || iNumMixRecipes[j] > 100)
#endif //LJH_MOD_EXTENDING_NUM_OF_MIX_RECIPES_FROM_100_TO_1000
		{
			//assert(!"���������� mix.bmd�Դϴ�. �ֽ� mix.bmd�� �´��� Ȯ���ϼ���!");
			unicode::t_char Text[256];
    		unicode::_sprintf(Text,"%s - Version not matched.",szFileName);
			g_ErrorReport.Write( Text);
			MessageBox(g_hWnd,Text,NULL,MB_OK);
			SendMessage(g_hWnd,WM_DESTROY,0,0);
			fclose(fp);
			exit(0);
		}
#endif	// SOCKET_SYSTEM
		for (i = 0; i < iNumMixRecipes[j]; ++i)
		{
			MIX_RECIPE * pMixRecipe = new MIX_RECIPE;
			fread(pMixRecipe, iSize, 1, fp);
			BuxConvert((BYTE*)pMixRecipe, iSize);
			m_MixRecipe[j].AddRecipe(pMixRecipe);
		}
	}
	fclose(fp);
}

int CMixRecipeMgr::GetMixInventoryType()
{
	assert(m_iMixType >= MIXTYPE_GOBLIN_NORMAL && m_iMixType < MAX_MIX_TYPES && "���ǵ��� ���� ����â");
	return m_iMixType;
}

int CMixRecipeMgr::GetMixInventoryEquipmentIndex()
{
	switch(GetMixInventoryType())
	{
	case SEASON3A::MIXTYPE_GOBLIN_NORMAL:
	case SEASON3A::MIXTYPE_GOBLIN_CHAOSITEM:
	case SEASON3A::MIXTYPE_GOBLIN_ADD380:
		return REQUEST_EQUIPMENT_CHAOS_MIX;
	case SEASON3A::MIXTYPE_CASTLE_SENIOR:
		return REQUEST_EQUIPMENT_CHAOS_MIX;
	case SEASON3A::MIXTYPE_TRAINER:
		return REQUEST_EQUIPMENT_TRAINER_MIX;
	case SEASON3A::MIXTYPE_OSBOURNE:
		return REQUEST_EQUIPMENT_OSBOURNE_MIX;
	case SEASON3A::MIXTYPE_JERRIDON:
		return REQUEST_EQUIPMENT_JERRIDON_MIX;
	case SEASON3A::MIXTYPE_ELPIS:
		return REQUEST_EQUIPMENT_ELPIS_MIX;
#ifdef ADD_GLOBAL_MIX_MAR08
	case SEASON3A::MIXTYPE_CHAOS_CARD:
		return REQUEST_EQUIPMENT_CHAOS_CARD_MIX;
	case SEASON3A::MIXTYPE_CHERRYBLOSSOM:
		return REQUEST_EQUIPMENT_CHERRYBLOSSOM_MIX;
#endif //ADD_GLOBAL_MIX_MAR08
#ifdef ADD_SOCKET_MIX
	case SEASON3A::MIXTYPE_EXTRACT_SEED:
		return REQUEST_EQUIPMENT_EXTRACT_SEED_MIX;
	case SEASON3A::MIXTYPE_SEED_SPHERE:
		return REQUEST_EQUIPMENT_SEED_SPHERE_MIX;
	case SEASON3A::MIXTYPE_ATTACH_SOCKET:
		return REQUEST_EQUIPMENT_ATTACH_SOCKET_MIX;
	case SEASON3A::MIXTYPE_DETACH_SOCKET:
		return REQUEST_EQUIPMENT_DETACH_SOCKET_MIX;
#endif	// ADD_SOCKET_MIX
	default:
		assert(!"���ǵ��� ���� ���� â");
		return REQUEST_EQUIPMENT_CHAOS_MIX;
	}
}

void CMixRecipeMgr::ResetMixItemInventory()
{
	m_MixItemInventory.Reset();
}

void CMixRecipeMgr::AddItemToMixItemInventory(ITEM * pItem)
{
	m_MixItemInventory.AddItem(pItem);
}

void CMixRecipeMgr::CheckMixInventory()
{
	if (m_MixItemInventory.GetNumMixItems() == 0) m_bIsMixInit = TRUE;
	else m_bIsMixInit = FALSE;

	// ���� ���ǰ� ���Ѵ�.
	CheckRecipe(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
	CheckRecipeSimilarity(m_MixItemInventory.GetNumMixItems(), m_MixItemInventory.GetMixItems());
}

#ifdef ADD_SOCKET_MIX
int CMixRecipeMgr::GetSeedSphereID(int iOrder)
{
	int iCurrOrder = 0;
	CMixItem * pItems = m_MixItemInventory.GetMixItems();
	for (int i = 0; i < m_MixItemInventory.GetNumMixItems(); ++i)
	{
		if (pItems[i].m_bySeedSphereID != SOCKET_EMPTY)	// �õ彺�Ǿ��
		{
			if (iCurrOrder == iOrder)
			{
				return pItems[i].m_bySeedSphereID;
			}
			else
			{
				++iCurrOrder;
			}
		}
	}
	return SOCKET_EMPTY;
}
#endif	// ADD_SOCKET_MIX
