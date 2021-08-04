
#ifndef _GMCRYINGWOLF2ND_H_
#define _GMCRYINGWOLF2ND_H_

//. soyaviper

#ifdef CRYINGWOLF_2NDMVP

namespace M34CryingWolf2nd {		//. ũ���̿��� ������
	bool IsCyringWolf2nd();
//	bool IsInCryingWolfSection(const vec3_t Position);

	//. ������Ʈ
	bool CreateCryingWolf2ndObject(OBJECT* pObject);
	bool MoveCryingWolf2ndObject(OBJECT* pObject);
	bool RenderCryingWolf2ndObjectVisual(OBJECT* pObject, BMD* pModel);
	bool RenderCryingWolf2ndObjectMesh(OBJECT* pObject, BMD* pModel);
	
	//. ����
	CHARACTER* CreateCryingWolf2ndMonster(int iType, int PosX, int PosY, int Key);

	bool MoveCryingWolf2ndMonsterVisual(OBJECT* pObject, BMD* pModel);
	bool RenderCryingWolf2ndMonsterObjectMesh(OBJECT* pObject, BMD* pModel);
	bool RenderCryingWolf2ndMonsterVisual(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel);

	void MoveCryingWolf2ndBlurEffect(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel);
	
	bool AttackEffectCryingWolf2ndMonster(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel);
//	bool SetCurrentActionCryingWolf2ndMonster(CHARACTER* pCharacter, OBJECT* pObject);
}

#endif // CRYINGWOLF_2NDMVP


#endif // _GMCRYINGWOLF2ND_H_