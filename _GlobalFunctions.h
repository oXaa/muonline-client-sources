#ifndef _GLOBAL_FUNCTIONS_H
#define _GLOBAL_FUNCTIONS_H

#include "ZzzScene.h"
#ifndef KJH_ADD_SERVER_LIST_SYSTEM		// #ifndef
// �׽�Ʈ �����ΰ�?
inline bool IsTestServer()
{
	// 559 "�׽�Ʈ"
	return 0 == ::strcmp(ServerList[ServerSelectHi].Name, GlobalText[559]) ? true : false;
}
#endif // KJH_ADD_SERVER_LIST_SYSTEM

#include "w_BuffStateSystem.h"

class BuffStateSystem;
class BuffScriptLoader;
class BuffTimeControl;
class BuffStateValueControl;

extern BuffStateSystemPtr			g_BuffSystem;

BuffScriptLoader& TheBuffInfo();

BuffStateSystem& TheBuffStateSystem();

BuffTimeControl& TheBuffTimeControl();

BuffStateValueControl& TheBuffStateValueControl();

//Character Buff
// ������ �ִ��� ������ �Ǵ�..
#define g_isNotCharacterBuff( o ) \
	o->m_BuffMap.isBuff()

// � ������ �ִ��� ������ �Ǵ�..( ���� )
#define g_isCharacterBuff( o, bufftype ) \
	o->m_BuffMap.isBuff( bufftype )

// � ������ �ִ��� ������ �Ǵ�..( ����Ʈ )
#define g_isCharacterBufflist( o, bufftypelist ) \
	o->m_BuffMap.isBuff( bufftypelist )

// ��ū���� �������� ������ �Ǵ� ����
#define g_TokenCharacterBuff( o, bufftype ) \
	o->m_BuffMap.TokenBuff( bufftype )

// � ������ ��ø �Ǵ�..
#define g_CharacterBuffCount( o, bufftype ) \
	o->m_BuffMap.GetBuffCount( bufftype )

// ��� ������ �ɷ��ִ��� 
#define g_CharacterBuffSize( o ) \
	o->m_BuffMap.GetBuffSize()

// ���� �ε����� ���������� ���� �´�.
#define g_CharacterBuff( o, iterindex ) \
	o->m_BuffMap.GetBuff( iterindex )

// ���� ���
#define g_CharacterRegisterBuff( o, bufftype ) \
	o->m_BuffMap.RegisterBuff( bufftype )

// ����Ʈ�� ���� ���
#define g_CharacterRegisterBufflist( o, bufftypelist ) \
	o->m_BuffMap.RegisterBuff( bufftypelist )

// ���� ����
#define g_CharacterUnRegisterBuff( o, bufftype ) \
	o->m_BuffMap.UnRegisterBuff( bufftype )

// ����Ʈ�� ���� ����
#define g_CharacterUnRegisterBuffList( o, bufftypelist ) \
	o->m_BuffMap.UnRegisterBuff( bufftypelist )

// ���� ī��
#define g_CharacterCopyBuff( outObj, inObj ) \
	outObj->m_BuffMap.m_Buff = inObj->m_BuffMap.m_Buff

// ��ü ���� ����
#define g_CharacterClearBuff( o ) \
	o->m_BuffMap.ClearBuff()

//TheBuffInfo
#define g_BuffInfo( buff ) \
	TheBuffInfo().GetBuffinfo( buff )

#define g_IsBuffClass( buff ) \
	TheBuffInfo().IsBuffClass( buff )

//TheBuffTimeControl
#define g_RegisterBuffTime( bufftype, curbufftime ) \
	TheBuffTimeControl().RegisterBuffTime( bufftype, curbufftime )

#define g_UnRegisterBuffTime( bufftype ) \
	TheBuffTimeControl().UnRegisterBuffTime( bufftype )

#define g_BuffStringTime( bufftype, timeText ) \
	TheBuffTimeControl().GetBuffStringTime( bufftype, timeText )

#define g_StringTime( time, timeText, issecond ) \
	TheBuffTimeControl().GetStringTime( time, timeText, issecond )

//TheBuffStateValueControl
#define g_BuffStateValue( type ) \
	TheBuffStateValueControl().GetValue( type )

#define g_BuffToolTipString( outstr, type ) \
	TheBuffStateValueControl().GetBuffInfoString( outstr, type )

#define g_BuffStateValueString( outstr, type ) \
	TheBuffStateValueControl().GetBuffValueString( outstr, type )

#ifdef IMPORTANCE_DATA

#include "ImportanceData.h"

//////////////////////////////////////////////////GateAttribute//////////////////////////////////////////////////////////////
inline
const GATE_ATTRIBUTE& TheGateAttRibute_const( int index )
{
	if( index <= MAX_GATES ) assert( 0 );
	return g_ImportanceData.GetGateAttribute( index );
}

inline
GATE_ATTRIBUTE&	TheGateAttRibute( int index )
{
	if( index <= MAX_GATES ) assert( 0 );
	return g_ImportanceData.GetGateAttribute( index );
}	

//////////////////////////////////////////////////SkillAttribute//////////////////////////////////////////////////////////////
inline
const SKILL_ATTRIBUTE& TheSkillAttribute_const( int index )
{
	if( index <= MAX_SKILLS ) assert( 0 );
	return g_ImportanceData.GetSkillAttribute( index );
}	

inline
SKILL_ATTRIBUTE&	TheSkillAttribute( int index )
{
	if( index <= MAX_SKILLS ) assert( 0 );
	return g_ImportanceData.GetSkillAttribute( index );
}

//////////////////////////////////////////////////SkillAttribute//////////////////////////////////////////////////////////////
inline
const CHARACTER& TheCharacter_const( int index )
{
	if( index <= MAX_CHARACTERS_CLIENT ) assert( 0 );
	return g_ImportanceData.GetCharacterClient( index );
}	

inline
CHARACTER&	TheCharacter( int index )
{
	if( index <= MAX_CHARACTERS_CLIENT ) assert( 0 );
	return g_ImportanceData.GetCharacterClient( index );
}

//////////////////////////////////////////////////CharacterMachine//////////////////////////////////////////////////////////////
inline
const CHARACTER_MACHINE& TheCharacterMachine_const()
{
	assert( g_ImportanceData.GetCharacterMachine().expired() );
	return *g_ImportanceData.GetCharacterMachine().lock();
}

inline
const CHARACTER_MACHINE& TheCharacterMachine()
{
	assert( g_ImportanceData.GetCharacterMachine().expired() );
	return *g_ImportanceData.GetCharacterMachine().lock();
}

/////////////////////////////////////////////////CharacterAttribute//////////////////////////////////////////////////////////////
inline
const CHARACTER_ATTRIBUTE& TheCharacterAttribute_const()
{
	//����� expired�� �˻� �� �ʿ䰡 ����.
	return *g_ImportanceData.GetCharaterAttribute().lock();
}

inline
CHARACTER_ATTRIBUTE& TheCharacterAttribute()
{
	//����� expired�� �˻� �� �ʿ䰡 ����.
	return *g_ImportanceData.GetCharaterAttribute().lock();
}

#endif //IMPORTANCE_DATA

inline unsigned long RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{ return (r)+(g<<8)+(b<<16)+(a<<24); }
inline unsigned char GetAlpha(unsigned long rgba)
{ return ((rgba) >> 24); }
inline unsigned char GetRed(unsigned long rgba)
{ return ((rgba) & 0xff); }
inline unsigned char GetGreen(unsigned long rgba)
{ return (((rgba) >> 8) & 0xff); }
inline unsigned char GetBlue(unsigned long rgba)
{ return (((rgba) >> 16) & 0xff); }

#ifdef NEW_COMMANDS
//math
inline 
void SinCos( float fRadians, float& fSin, float& fCos ) {
    float s, c;
    __asm fld fRadians
		__asm fsincos
		__asm fstp c
		__asm fstp s
		
		fSin = s;
    fCos = c;
}

inline
int Min( int fA, int fB ) {
	return (fA < fB) ? fA : fB;
}

inline
int Max( int fA, int fB ) {
	return (fA > fB) ? fA : fB;
}
#endif //NEW_COMMANDS

#ifdef NEW_USER_INTERFACE_FUNCTIONS

#include "w_Shell.h"

class Shell;
class BuildSystem;
class ClientInfoBuilder;
class GameInfoBuilder;
class ServerProxySystem;
class InputProxy;
class GameServerProxy;
class ShopServerProxy;
class ClientSystem;
class input::InputSystem;
class ui::UISystem;

const string UISHOPFRAMENAME             = "ShopModule";
const string UIMESSAGEBOXFRAME_NAME      = "MessageBox";

//�ӽ÷� ����
//-.-;;;
extern ShellPtr			g_shell;

Shell& TheShell();

BuildSystem& TheBuildSystem();

ClientInfoBuilder& TheClientInfoBuilder();

GameInfoBuilder& TheGameInfoBuilder();

ServerProxySystem& TheSerProxySystem();

InputProxy&	TheInputProxy();

GameServerProxy& TheGameServerProxy();

ShopServerProxy& TheShopServerProxy();

input::InputSystem& TheInputSystem();

ui::UISystem& TheUISystem();

ClientSystem& TheClientSystem();

#define MessageBoxMake( messageboxdata ) \
{ \
	TheClientSystem().RegisterMessageBoxModule( messageboxdata );\
}

#define MessageBoxClear \
{ \
	TheClientSystem().UnregisterModule( Module::eMessageBox ); \
	TheUISystem().SubFrame( UIMESSAGEBOXFRAME_NAME ); \
}

#define ShopMake( type ) \
{ \
	TheShopServerProxy().ChangeShopType( type ); \
	TheClientSystem().RegisterModule( Module::eShop_Top ); \
	TheClientSystem().RegisterModule( Module::eShop_Left ); \
	TheClientSystem().RegisterModule( Module::eShop_Middle ); \
	TheClientSystem().RegisterModule( Module::eShop_Right ); \
}

#define ShopClear \
{ \
	TheClientSystem().UnregisterModule( Module::eShop_Left ); \
	TheClientSystem().UnregisterModule( Module::eShop_Middle ); \
	TheClientSystem().UnregisterModule( Module::eShop_Right ); \
	TheClientSystem().UnregisterModule( Module::eShop_Top ); \
	TheUISystem().SubFrame( UISHOPFRAMENAME ); \
}


#endif //NEW_USER_INTERFACE_FUNCTIONS

#ifdef PBG_FIX_SKILL_DEMENDCONDITION
namespace SKILLCONDITION
{
	//���������� �䱸�ϴ� �Ϳ��� �ش��� �Ѵ�. �׿ܴ� �˻���� �����Ѵ�.
	typedef struct DemendConditionInfo
	{
		WORD SkillType;			//��ųŸ��
	//	char SkillName[100];	//��ų�̸�
		
		// �䱸 ����
		WORD SkillLevel;		//����
		WORD SkillStrength;		//��
		WORD SkillDexterity;	//��ø
		WORD SkillVitality;		//ü��
		WORD SkillEnergy;		//������	(���� ��͸� ����Ѵ�.)
		WORD SkillCharisma;		//���
		
		DemendConditionInfo() : SkillType( 0 ), SkillLevel( 0 ), SkillStrength( 0 ),
			SkillDexterity( 0 ), SkillVitality( 0 ), SkillEnergy( 0 ), SkillCharisma( 0 )
		{
	//		ZeroMemory( SkillName, 100 );
		}
		BOOL operator<=(const DemendConditionInfo& rhs) const
		{
			return SkillStrength <= rhs.SkillStrength && SkillDexterity <= rhs.SkillDexterity &&
			SkillVitality <= rhs.SkillVitality && SkillEnergy <= rhs.SkillEnergy && SkillCharisma <= rhs.SkillCharisma;
		}
	}DemendConditionInfo;
	
	BOOL skillVScharactorCheck( const DemendConditionInfo& basicInfo, const DemendConditionInfo& heroInfo );
	BOOL DemendConditionCheckSkill(WORD skilltype);
}
#endif //PBG_FIX_SKILL_DEMENDCONDITION

#ifdef CSK_DEBUG_RENDER_BOUNDINGBOX
extern bool g_bRenderBoundingBox;
#endif // CSK_DEBUG_RENDER_BOUNDINGBOX

#if defined PBG_ADD_MU_LOGO || defined LJH_MOD_TO_USE_ISBLUEMUSERVER_FUNC
// ���� �ΰ� ���� ��缷 (�ҽ� �и��۾����� ���������� ��缷�ΰ� ���θ� Ȯ��)
namespace BLUE_MU
{
	BOOL IsBlueMuServer();
	extern bool g_bIsBlue_MU_Server;
}
#endif //defined PBG_ADD_MU_LOGO || defined LJH_MOD_TO_USE_ISBLUEMUSERVER_FUNC

#ifdef KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL
int MasterSkillToBaseSkillIndex(int iMasterSkillIndex);
#endif // KJH_MOD_BTS184_REQUIRE_STAT_WHEN_SPELL_SKILL

#ifdef KWAK_ADD_TRACE_FUNC
inline void __TraceF(const TCHAR* pFmt, ...)
{
#ifdef _DEBUG
	TCHAR	szMsg[4096];
	va_list	pArgList;
	
	//===================================================================
	// va_start macro (defined in STDARG.H)
	//===================================================================
	va_start(pArgList, pFmt);
	_vsntprintf(szMsg, sizeof(szMsg) / sizeof(TCHAR), pFmt, pArgList);
	
	//===================================================================
	// pArgList �� �ʱ�ȭ
	//===================================================================
	va_end(pArgList);
	
	//===================================================================
	// Debug â�� �޽��� ���
	//===================================================================
	OutputDebugString(szMsg);
#endif // _DEBUG
}
#endif // KWAK_ADD_TRACE_FUNC

#endif	// _GLOBAL_FUNCTIONS_H