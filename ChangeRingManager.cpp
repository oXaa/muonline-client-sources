// ChangeRingManager.cpp: implementation of the CChangeRingManager class.
//
//////////////////////////////////////////////////////////////////////

// common
#include "stdafx.h"
#include "ZzzTexture.h"
#include "ZzzOpenData.h"
#include "ZzzBMD.h"
#include "ZzzCharacter.h"
#include "ChangeRingManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChangeRingManager::CChangeRingManager()
{

}

CChangeRingManager::~CChangeRingManager()
{

}

void CChangeRingManager::LoadItemModel()
{
	AccessModel(MODEL_HELPER+10,"Data\\Item\\","Ring"  ,1);         //  ���� ����.

	// ����Ʈ �ذ����� ���� �� ����Ÿ �ε�
	AccessModel(MODEL_HELPER+39,"Data\\Item\\","Ring"  ,1);         //  ����Ʈ �ذ����� ���Ź���

	// �ҷ��� �̺�Ʈ ���� ���� �� ����Ÿ �ε�
	AccessModel(MODEL_HELPER+40,"Data\\Item\\","Ring"  ,1);         //  �� ������ ���Ź���

	// ũ�������� �̺�Ʈ ���� ���� �� ����Ÿ �ε�
	AccessModel(MODEL_HELPER+41,"Data\\Item\\","Ring"  ,1);         //  ��Ÿ�� ���Ź���

	// GM ���� ���� �� ����Ÿ �ε�
	AccessModel(MODEL_HELPER+42,"Data\\Item\\","Ring"  ,1);         //  GM ���Ź���

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ũ�������� ������� ���� ���� ����Ÿ �ε�
	AccessModel(MODEL_HELPER+68,"Data\\Item\\xmas\\","xmasring");			//  ����� ���Ź���
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
	AccessModel(MODEL_HELPER+76,"Data\\Item\\","PandaPetRing");
#endif //PJH_ADD_PANDA_CHANGERING
	
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	AccessModel(MODEL_HELPER+122, "Data\\Item\\", "SkeletonRing");	// ���̷��� ���Ź���
#endif	// YDG_ADD_SKELETON_CHANGE_RING
}

void CChangeRingManager::LoadItemTexture()
{
	OpenTexture(MODEL_HELPER+39, "Item\\"); // ����Ʈ �ذ����� ���Ź���

	OpenTexture(MODEL_HELPER+41, "Item\\"); // ��Ÿ ���Ź���

	OpenTexture(MODEL_HELPER+40, "Item\\"); // �� ������ ���Ź���

	OpenTexture(MODEL_HELPER+42, "Item\\"); // GM ���Ź���

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ũ�������� ����� ���� ���� ����Ÿ �ε�
	OpenTexture(MODEL_HELPER+68, "Item\\xmas\\");			//  ����� ���Ź���
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
	OpenTexture(MODEL_HELPER+76, "Item\\");			//  ����� ���Ź���
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	OpenTexture(MODEL_HELPER+122, "Item\\");	// ���̷��� ���Ź���
#endif	// YDG_ADD_SKELETON_CHANGE_RING
}

bool CChangeRingManager::CheckDarkLordHair(int iType)
{
	// �ذ񺯽Ź����� �����ϸ� ��ũ�ε� �Ӹ� �Ⱥ��̰� ����
	if((iType >= MODEL_SKELETON1 && iType <= MODEL_SKELETON3) || iType == MODEL_SKELETON_PCBANG)
	{
		return true;
	}
	// �ҷ��� �̺�Ʈ ���Ź��� �����ϸ� ��ũ�ε� �Ӹ� �Ⱥ��̰� ��
	if(iType == MODEL_HALLOWEEN)
	{
		return true;
	}
	// ũ�������� �̺�Ʈ ���Ź��� �����ϸ� ��ũ�ε� �Ӹ� �Ⱥ��̰� ��
	if(iType == MODEL_XMAS_EVENT_CHANGE_GIRL)
	{
		return true;
	}
	// GMĳ������ ���(���� ����) ��ũ�ε� �Ӹ� �Ⱥ��̰� ��.
	if(iType == MODEL_GM_CHARACTER)
	{
		return true;
	}
	// ȯ����� ĳ���� ���̸� ��ũ�ε� �Ӹ� �Ⱥ��̰� ��.
	if(iType == MODEL_CURSEDTEMPLE_ALLIED_PLAYER || iType == MODEL_CURSEDTEMPLE_ILLUSION_PLAYER)
	{
		return true;
	}

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ����� ĳ���� ���̸� ��ũ�ε� �Ӹ� �Ⱥ��̰� ��.
	if(iType == MODEL_XMAS2008_SNOWMAN)
	{
		return true;
	}
#endif //LDK_ADD_SNOWMAN_CHANGERING

#ifdef PJH_ADD_PANDA_CHANGERING
	if(iType == MODEL_PANDA)
	{
		return true;
	}
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	if (iType == MODEL_SKELETON_CHANGED)	// ���̷��� ���Ź���
	{
		return true;
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING

	return false;
}

bool CChangeRingManager::CheckDarkCloak(int iClass, int iType)
{
	// ĳ���Ͱ� ���˻��̰�
	if(GetCharacterClass(iClass) == CLASS_DARK)
	{
		// �ҷ��� �̺�Ʈ ���Ź��� �����ϸ� ���˻� ���� �Ⱥ��̰� ����
		if(iType == MODEL_HALLOWEEN)
		{
			return true;
		}

		// ��Ÿ ���Ź��� �����ϸ� ���˻� ���� �Ⱥ��̰�
		if(iType == MODEL_XMAS_EVENT_CHANGE_GIRL)
		{
			return true;
		}

		// GM ���Ź��� �����ϸ� ���˻� ���� �Ⱥ��̰�
		if(iType == MODEL_GM_CHARACTER)
		{
			return true;
		}

#ifdef LDK_ADD_SNOWMAN_CHANGERING
		// ����� ���Ź��� �����ϸ� ���˻� ���� �Ⱥ��̰�
	 	if(iType == MODEL_XMAS2008_SNOWMAN)
	 	{
	 		return true;
	 	}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
	 	if(iType == MODEL_PANDA)
	 	{
	 		return true;
	 	}
#endif //PJH_ADD_PANDA_CHANGERING
#ifdef YDG_ADD_SKELETON_CHANGE_RING
		if (iType == MODEL_SKELETON_CHANGED)	// ���̷��� ���Ź���
		{
			return true;
		}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
	}

	return false;
}

bool CChangeRingManager::CheckChangeRing(short RingType)
{
	// ���Ź����� ������ ���
	if(RingType == ITEM_HELPER+10)
	{
		return true;
	}
	// �̺�Ʈ �ذ� ���� ���� �����ϸ� ĭ���� 3���� ������ ���� ó��
	if(RingType == ITEM_HELPER+39)
	{
		return true;
	}
	// �ҷ��� �̺�Ʈ ȣ�ں��Ź��� �����ϸ� ĭ���� 3���� ������ ���� ó��
	if(RingType == ITEM_HELPER+40)
	{
		return true;
	}
	// ũ�������� �̺�Ʈ ��Ÿ���Ź��� �����ϸ� ĭ���� 3���� ������ ���� ó��
	if(RingType == ITEM_HELPER+41)
	{	
		return true;
	}
	// GM ���Ź��� �����ϸ� ĭ���� 3���� ������ ���� ó��
	if(RingType == ITEM_HELPER+42)
	{	
		return true;
	}

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ��������Ź��� �����ϸ� ĭ���� 3���� ������ ���� ó��
 	if(RingType == ITEM_HELPER+68)
 	{
 		return true;
 	}
#endif //LDK_ADD_SNOWMAN_CHANGERING

#ifdef PJH_ADD_PANDA_CHANGERING
 	if(RingType == ITEM_HELPER+76)
 	{
 		return true;
 	}
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	if (RingType == ITEM_HELPER+122)	// ���̷��� ���Ź���
	{
		return true;
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING

	return false;
}

bool CChangeRingManager::CheckRepair(int iType)
{
	// �Ϲ� ���Ź��� ���� ���� �Ⱥ��̰� ���� ó��
	if(iType == ITEM_HELPER+10)
	{
		return true;
	}
	// �ǽù� �̺�Ʈ ���Ź��� 
	if(iType == ITEM_HELPER+39)
	{
		return true;
	}
	// �ҷ��� �̺�Ʈ ���Ź��� ���� ���� �Ⱥ��̰� ���� ó��
	if(iType == ITEM_HELPER+40)
	{
		return true;
	}
	// ũ�������� �̺�Ʈ ���Ź��� ���� ���� �Ⱥ��̰� ���� ó��
	if(iType == ITEM_HELPER+41)
	{
		return true;
	}
	// GM ���Ź��� ���� ���� �Ⱥ��̰� ���� ó��
	if(iType == ITEM_HELPER+42)
	{
		return true;
	}

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ��������Ź��� ���� ���� �Ⱥ��̰� ���� ó��
 	if(iType == ITEM_HELPER+68)
 	{
 		return true;
 	}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
 	if(iType == ITEM_HELPER+76)
 	{
 		return true;
 	}
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	if (iType == ITEM_HELPER+122)	// ���̷��� ���Ź���
	{
		return true;
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING

	return false;
}

bool CChangeRingManager::CheckMoveMap(short sLeftRingType, short sRightRingType)
{
	if(sLeftRingType == ITEM_HELPER+10 || sRightRingType == ITEM_HELPER+10)
	{
		return true;
	}
	// ����Ʈ �ذ����� ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+39 || sRightRingType == ITEM_HELPER+39)
	{
		return true;
	}
	//CSK : �ҷ��� �̺�Ʈ ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+40 || sRightRingType == ITEM_HELPER+40)
	{
		return true;
	}
	// ũ�������� �̺�Ʈ ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+41 || sRightRingType == ITEM_HELPER+41)
	{
		return true;
	}
	// GM ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+42 || sRightRingType == ITEM_HELPER+42)
	{
		return true;
	}

#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ��������Ź��� �����ϸ� �� �̸� ������ ó��
 	if(sLeftRingType == ITEM_HELPER+68 || sRightRingType == ITEM_HELPER+68)
 	{
 		return true;
 	}
#endif //LDK_ADD_SNOWMAN_CHANGERING
#ifdef PJH_ADD_PANDA_CHANGERING
 	if(sLeftRingType == ITEM_HELPER+76 || sRightRingType == ITEM_HELPER+76)
 	{
 		return true;
 	}
#endif //PJH_ADD_PANDA_CHANGERING

#ifdef YDG_ADD_SKELETON_CHANGE_RING
	if (sLeftRingType == ITEM_HELPER+122 || sRightRingType == ITEM_HELPER+122)	// ���̷��� ���Ź���
	{
		return true;
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING

	return false;
}

#ifdef KJH_FIX_MOVE_ICARUS_EQUIPED_PANDA_CHANGE_RING
bool CChangeRingManager::CheckBanMoveIcarusMap(short sLeftRingType, short sRightRingType)
{
	if(sLeftRingType == ITEM_HELPER+10 || sRightRingType == ITEM_HELPER+10)
	{
		return true;
	}
	// ����Ʈ �ذ����� ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+39 || sRightRingType == ITEM_HELPER+39)
	{
		return true;
	}
	//CSK : �ҷ��� �̺�Ʈ ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+40 || sRightRingType == ITEM_HELPER+40)
	{
		return true;
	}
	// ũ�������� �̺�Ʈ ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+41 || sRightRingType == ITEM_HELPER+41)
	{
		return true;
	}
	// GM ���Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+42 || sRightRingType == ITEM_HELPER+42)
	{
		return true;
	}
	
#ifdef LDK_ADD_SNOWMAN_CHANGERING
	// ��������Ź��� �����ϸ� �� �̸� ������ ó��
	if(sLeftRingType == ITEM_HELPER+68 || sRightRingType == ITEM_HELPER+68)
	{
		return true;
	}
#endif //LDK_ADD_SNOWMAN_CHANGERING

#ifndef YDG_FIX_MOVE_ICARUS_EQUIPED_SKELETON_CHANGE_RING	// �����Ҷ� �����Һκ�
#ifdef YDG_ADD_SKELETON_CHANGE_RING
	if (sLeftRingType == ITEM_HELPER+122 || sRightRingType == ITEM_HELPER+122)	// ���̷��� ���Ź���
	{
		return true;
	}
#endif	// YDG_ADD_SKELETON_CHANGE_RING
#endif	// YDG_FIX_MOVE_ICARUS_EQUIPED_SKELETON_CHANGE_RING	// �����Ҷ� �����Һκ�

	return false;
}
#endif // KJH_FIX_MOVE_ICARUS_EQUIPED_PANDA_CHANGE_RING

