//////////////////////////////////////////////////////////////////////////
//  
//  ��  �� : CSPetSystem.
//
//  ��  �� : ĳ���Ͱ� ��ȯ, ������ ����� �ƴ� �ֵ��� �ý���.
//           ��ũ�ε� ( ��ũ ���Ǹ� ),
//
//  ��  ¥ : 2004.03.29.
//
//  �ۼ��� : �� �� ��.
//  
//////////////////////////////////////////////////////////////////////////
#ifndef __CSPET_SYSTEM_H__
#define __CSPET_SYSTEM_H__

//////////////////////////////////////////////////////////////////////////
//  INCLUDE.
//////////////////////////////////////////////////////////////////////////
#ifdef PET_SYSTEM
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"

//////////////////////////////////////////////////////////////////////////
//  CLASS.
//////////////////////////////////////////////////////////////////////////
//  �⺻���� �ֽý���.
// Hero�� �����ϰ��ִ� �길 �ش�.
// �κ��丮�ȿ� �ִ� Pet(Item)�� �ش����� �ʴ´�.
class CSPetSystem
{
protected:
    CHARACTER*  m_PetOwner;     //  �� ����.
    CHARACTER*  m_PetTarget;    //  �� ���� ��ǥ.
    CHARACTER   m_PetCharacter; //  �� ���.
    PET_TYPE    m_PetType;      //  �� ����.
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
    PET_INFO*   m_pPetInfo;      //  �� ����
#else // KJH_FIX_DARKLOAD_PET_SYSTEM
    PET_INFO    m_PetInfo;      //  �� ����.
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM
    BYTE        m_byCommand;    //  ��ɻ���.


public :
    CSPetSystem () {};
#ifdef YDG_FIX_MEMORY_LEAK_0905
    virtual ~CSPetSystem ();
#else	// YDG_FIX_MEMORY_LEAK_0905
    virtual ~CSPetSystem () {};
#endif	// YDG_FIX_MEMORY_LEAK_0905

    PET_TYPE    GetPetType ( void ) { return m_PetType; }
#ifdef KJH_FIX_DARKLOAD_PET_SYSTEM
	void		SetPetInfo(PET_INFO* pPetInfo) {m_pPetInfo = pPetInfo;};
#endif // KJH_FIX_DARKLOAD_PET_SYSTEM

    virtual void    MovePet ( void ) = 0;
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	virtual void	CalcPetInformation ( const PET_INFO& Petinfo ) = 0;
#else // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    virtual void	CalcPetInformation ( BYTE Level, int exp ) = 0;
#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    virtual void    RenderPetInventory ( void ) = 0;
    virtual void    RenderPet ( int PetState = 0 ) = 0;

    virtual void    Eff_LevelUp ( void ) = 0;
    virtual void    Eff_LevelDown ( void ) = 0;

    void    CreatePetPointer ( int Type, unsigned char PositionX, unsigned char PositionY, float Rotation );
    bool    PlayAnimation ( OBJECT* o );

    void    MoveInventory ( void );
    void    RenderInventory ( void );

    void    SetAI ( int AI );
    void    SetCommand ( int Key, BYTE cmd );
    void    SetAttack ( int Key, int attackType );

#ifdef LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
	int		GetObjectType()
	{
		return m_PetCharacter.Object.Type;
	}
#endif // LDS_FIX_AFTER_PETDESTRUCTOR_ATTHESAMETIME_TERMINATE_EFFECTOWNER
};


//  ��ũ ���Ǹ�.
class CSPetDarkSpirit : public CSPetSystem
{
private :

public :
    CSPetDarkSpirit ( CHARACTER* c );
#ifdef YDG_FIX_MEMORY_LEAK_0905_2ND
    virtual ~CSPetDarkSpirit ( void );
#else	// YDG_FIX_MEMORY_LEAK_0905_2ND
    virtual ~CSPetDarkSpirit ( void ) {};
#endif	// YDG_FIX_MEMORY_LEAK_0905_2ND

    virtual void MovePet ( void );
#ifdef KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
	virtual void CalcPetInformation ( const PET_INFO& Petinfo );
#else // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    virtual void CalcPetInformation ( BYTE Level, int exp );
#endif // KJH_FIX_WOPS_K19787_PET_LIFE_ABNORMAL_RENDER
    virtual void RenderPetInventory ( void );
    virtual void RenderPet ( int PetState = 0 );

    virtual void Eff_LevelUp ( void );
    virtual void Eff_LevelDown ( void );

    void    AttackEffect ( CHARACTER* c, OBJECT* o );
    void    RenderCmdType ( void );
};

#endif	// PET_SYSTEM

#endif// __CSPET_SYSTEM_H__