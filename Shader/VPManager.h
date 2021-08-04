#ifndef __VPMANAGER_H__
#define __VPMANAGER_H__

//////////////////////////////////////////////////////////////////////////
// 
// VPManager.h : ���̴� �ҽ� Parsing, ������ �� ����
//
//////////////////////////////////////////////////////////////////////////

#include "StlDefinition.h"
//Texture-> ���ҽ��� OpenTexture�Լ����� �����̸����� Ű�� �Ͽ� �о���δ�.
//�𵨺���� ��� AttachTexture���� �����Ѵ�. 
#define MAX_ENV_PARAMS	196	//���̴� ���� ����

#include <map>

#define UNSIGNEDINT_NOFIND		65535*32

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� ���α׷� �����̳� : OpenGL�� �����ϵ� Shader Script�� 
///////////////////////////////////////////////////////////////////////////////////////////
typedef std::map<unsigned int, unsigned int>	mapRegisterGenValues;		// First Key Index, Second Key Value

extern mapRegisterGenValues	m_mapRegisterGen_VPS;			// �����ϵ� ���̴� �����̳� : ���ؽ� ���̴�
extern mapRegisterGenValues	m_mapRegisterGen_FPS;			// �����ϵ� ���̴� �����̳� : �ȼ� ���̴�
extern mapRegisterGenValues	m_mapRegisterGen_VPSP;			// �����ϵ� ���̴� �����̳� : Ư���� ��Ȳ�� ����ϴ� ���̴�(����� ShadowMap���� �׸��� ���� �� ���.)


///////////////////////////////////////////////////////////////////////////////////////////
// OpenGL�Լ� ��� ���� OpenGL���� ���� �߻��ϴ� ��� ������ ���� �մϴ�. 
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
inline int CheckGLError( const char *file, int line)
{
    GLenum glErr;
    int retCode = 0, iLimitGLError = 0; 
    while ( ((glErr=glGetError()) != GL_NO_ERROR) && (iLimitGLError < 2) )
    {
		char	szOutputError[512];

        switch(glErr)
        {
        case GL_INVALID_ENUM:		// ���ġ ���� ���� �� ����.
            sprintf(szOutputError, "GL_INVALID_ENUM error in File %s at line: %d\n", file, line);
            break;
        case GL_INVALID_VALUE:		// 
            sprintf(szOutputError, "GL_INVALID_VALUE error in File %s at line: %d\n", file, line);
            break;
        case GL_INVALID_OPERATION:	// �߸��� ������ �ѱ��
            sprintf(szOutputError, "GL_INVALID_OPERATION error in File %s at line: %d\n", file, line);
            break;	
        case GL_STACK_OVERFLOW:		// GLPushMatrix(), GLPopMatrix()�� ���� OpenGL���� Stack�� ���� ��ĥ��.
            sprintf(szOutputError, "GL_STACK_OVERFLOW error in File %s at line: %d\n", file, line);
            break;
        case GL_STACK_UNDERFLOW:	// GLPushMatrix(), GLPopMatrix()�� ���� OpenGL���� Stack�� ���� ���ڶ���.
            sprintf(szOutputError, "GL_STACK_UNDERFLOW error in File %s at line: %d\n", file, line);
            break;
        case GL_OUT_OF_MEMORY:		// GL ġ������ ���� �� �޸� ���� ����.
            sprintf(szOutputError, "GL_OUT_OF_MEMORY error in File %s at line: %d\n", file, line);
            break;
        default:
            sprintf(szOutputError, "UNKNOWN ERROR in File %s at line: %d\n", file, line);
        }
		++iLimitGLError;

#ifdef CONSOLE_DEBUG
 		g_ConsoleDebug->Write( MCD_NORMAL, szOutputError );
#endif // CONSOLE_DEBUG
		
 		g_ErrorReport.Write( szOutputError );
#ifdef KWAK_ADD_TRACE_FUNC
		__TraceF(TEXT("%s"), szOutputError);
#endif // KWAK_ADD_TRACE_FUNC

//		MessageBox( NULL, szOutputError, "Critical Error", MB_OK );
    }
    return retCode;
}

#endif // _DEBUG

#ifdef LDS_MR0_ADD_ENCRYPTION_ALLSHADERSCRIPT

///////////////////////////////////////////////////////////////////////////////////////////
// ���ڿ��� Ư�� ���ڿ��� �������� Split �Ͽ��ִ� Ŭ����.
///////////////////////////////////////////////////////////////////////////////////////////
#include <string>

class CStringSplitor
{	
private:
	string m_strSplitor;
	
private:
	BOOL ExtractSpotLeftBuffer_Ascending__( const char *szFullStr,		// Param1:szFullStr ���ڿ� ���� ���� �������� ���������� Param3:szFineValues�� ã�Ƴ��� ã�� �Ǹ� �� ���� ���ڿ��� ��ȯ.
		char *szReturnBuffer,									
		const char *szFindValues,
		const int iSkipDegree,
		BOOL bExceptionSpot = TRUE );
	
public:
	
	bool		SplitString( string& strSrc, vector<string>	&vecStr );	// Param1:strSrc�� SplitStr�� �������� Split�Ͽ� Param2:vecStr �� ���� �Ͽ� ��ȯ.
	void		SetStrSplit( string strSplitStr )						// Split �����ڸ� ����.
	{
		m_strSplitor = strSplitStr;
	}
	
public:
	CStringSplitor( string strSplitor )
	{
		m_strSplitor = strSplitor;
	}
	
	~CStringSplitor()
	{
	}
};
#endif // LDS_MR0_ADD_ENCRYPTION_ALLSHADERSCRIPT

// MR0:MODIFY
#ifdef LDS_MR0_FORDEBUG_USERRESPOND_BEINGVPMANAGERENABLE
namespace VPManager
{
	static bool	n_bEnabled;
	inline bool	beingEnable()
	{
		return n_bEnabled;
	}
}
#endif // LDS_MR0_FORDEBUG_USERRESPOND_BEINGVPMANAGERENABLE


///////////////////////////////////////////////////////////////////////////////////////////
// ��� ���̴� ������ �ѱ�� ���� �Լ��� ����. Shader Parameter Process
///////////////////////////////////////////////////////////////////////////////////////////
namespace VPManager
{
	// �����ϵ� ���̴��� �̸� �����ϵ� �����Ϸ����� ã�� ��ȯ. ���ؽ� ���̴� ����.
	inline unsigned int	GetGlGenValue_VPS( unsigned int uiIndex )
	{
		mapRegisterGenValues::iterator	iter = m_mapRegisterGen_VPS.find( uiIndex );

		if( iter != m_mapRegisterGen_VPS.end() )
		{
			return (unsigned int)iter->second;
		}
		
		return UNSIGNEDINT_NOFIND;
	}

	// �����ϵ� ���̴��� �̸� �����ϵ� �����Ϸ����� ã�� ��ȯ. �ȼ� ���̴� ����.
	inline unsigned int	GetGlGenValue_FPS( unsigned int uiIndex )
	{
		mapRegisterGenValues::iterator	iter = m_mapRegisterGen_FPS.find( uiIndex );
		
		if( iter != m_mapRegisterGen_FPS.end() )
		{
			return (unsigned int)iter->second;
		}
		
		return UNSIGNEDINT_NOFIND;
	}

	// �����ϵ� ���̴��� �̸� �����ϵ� �����Ϸ����� ã�� ��ȯ. Ư�� ���̴� ����.
	inline unsigned int	GetGlGenValue_VPSP( unsigned int uiIndex )
	{
		mapRegisterGenValues::iterator	iter = m_mapRegisterGen_VPSP.find( uiIndex );
		
		if( iter != m_mapRegisterGen_VPSP.end() )
		{
			return (unsigned int)iter->second;
		}
		
		return UNSIGNEDINT_NOFIND;
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	// 1. ���̴� ��ũ��Ʈ�� ��� �ҷ��� GL �Լ��� ������ �մϴ�. 
	// 2. ���̴��������� ����� ��� ����Ʈ �ؽ��ĸ� ��� �մϴ�.
	///////////////////////////////////////////////////////////////////////////////////////////
	void Init();		// ���̴� ��ũ��Ʈ Parsing & GL Compile & ShaderContainer ���. 
	void Uninit();
	void Disable();
	void Enable();

	void DisableFP();	// �����׸�Ʈ ���α׷��� �� Ȱ��ȭ��Ų��.
	void EnableFP();	// �����׸�Ʈ ���α׷��� Ȱ��ȭ��Ų��.

	void SetShaderCategory(bool isVertex);	//0 : Vertex Program, 1 : Fragment Program
	
	//��� ����
	bool SetLocalParam4f(unsigned int idx, float x, float y, float z, float w = 0.f);
	bool SetLocalParam4fv(unsigned int idx, const float* v);
	bool SetLocalParamMatrix(unsigned int idx, float (*Matrix)[4]);
	bool SetEnvParam4f(unsigned int idx, float x, float y, float z, float w = 0.f);
	bool SetEnvParam4fv(unsigned int idx, const float* v);
	bool SetEnvParamMatrix(unsigned int idx, float (*Matrix)[4]);
	bool GetLocalParam4fv(unsigned int idx, float* v);
	bool GetEnvParam4fv(unsigned int idx, float* v);

	// GPU�� �ѱ�� �Ķ���� ��� �ִ� �뷮 ���� (Local Param, Env Param)
	unsigned int  GetMaxLocalParams();
	unsigned int  GetMaxEnvParams();
	void SetRatioEnvLocal(unsigned int maxEnv);
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� �ҽ� ���ձ�. ���̴� ȿ�� Ÿ�� ����.
///////////////////////////////////////////////////////////////////////////////////////////
namespace VPManager
{
	//�⺻  Vertex Transform ���̴� Ÿ�Ե�
	typedef enum _MixShaderVT_NOBONE_t
	{
		MIXSHADER_VT_NOBONE_DEFAULT = 0,
		MIXSHADER_VT_NOBONE_ALL

	}MixShaderVT_NOBONE_t;
	
	typedef enum _MixShaderVT_ONELINK_t
	{
		MIXSHADER_VT_ONELINK_DEFAULT = 0,
		MIXSHADER_VT_ONELINK_ALL

	}MixShaderVT_ONELINK_t;

	typedef enum _MixShaderVT_TWOLINK_t
	{
		MIXSHADER_VT_TWOLINK_DEFAULT = 0,
		MIXSHADER_VT_TWOLINK_ALL

	}MixShaderVT_TWOLINK_t;
	
	typedef enum _MixShaderNT_t
	{
		MIXSHADER_NT_DEFAULT = 0,				//�� �� ����
		MIXSHADER_NT_TRANSFORM,					//�ִϸ��̼��� �����Ų��.
		MIXSHADER_NT_ALL

	}MixShaderNT_t;

	typedef enum _MixShaderCT_t
	{
		MIXSHADER_CT_DEFAULT = 0,				//�÷��� ���
		MIXSHADER_CT_AMBIENT,					//�����Ʈ�� ����
		MIXSHADER_CT_DIFFUSE,					//��ǻ�� ����Ʈ ���
		MIXSHADER_CT_DIRECTIONAL,				//���⼺ ���� ���
		MIXSHADER_CT_DOUBLE,					//�� ������ ������ ���� ���

		MIXSHADER_CT_ALL

	}MixShaderCT_t;

	typedef enum _MixShaderTT_DEF_t
	{
		MIXSHADER_TT_DEF_SINGLE_TEXTURE = 0,	//�̱� �ؽ����� ��, �⺻ �ؽ��� ���
		MIXSHADER_TT_DEF_TWO_TEXTURE,			//2-Texture�� �� �⺻ �ؽ��� ���

		MIXSHADER_TT_DEF_ALL
		
	}MixShaderTT_DEF_t;

	// m_matConstants[1] ~ m_matConstants[10] : 
	//	1:	MIXSHADER_TT_BLENDMESH		// (Param1:BlendTextureUV��)
	//	2:	MIXSHADER_TT_CHROME1		// (Param1:WorldTime, Param2:����� ����ġ �� �¼�)
	//	3:	MIXSHADER_TT_CHROME2		// (Param1:WorldTime, Param2:����� ����ġ �� �¼�)
	//	4:	MIXSHADER_TT_CHROME3		// (Param1:����� ����ġ �� �¼�)
	//	5:	MIXSHADER_TT_CHROME4		// (Param1:WorldTime, Param2:BlendTextureUV, Param3:����� ����ġ �� �¼�)
	//	6:	MIXSHADER_TT_CHROME5		// (Param1:WorldTime, Param2:����� ����ġ �� �¼�)
	//	7:	MIXSHADER_TT_METAL			// (Param1:����� ����ġ �� �¼�), Texture = BITMAP_SHINY
	//	8:	MIXSHADER_TT_OIL			// (Param1:BlendTextureUV)
	//	9:	MIXSHADER_TT_CHROME6		// (Param1:WorldTime)
	//	10: MIXSHADER_TT_WAVE			// (Param1:BlendTextureUV)		// �̻��
	typedef enum _MixShaderTT_t
	{
		MIXSHADER_TT_NONE	 = 0,
		MIXSHADER_TT_BLENDMESH,
		MIXSHADER_TT_CHROME1,				//���� �ؽ��� ����Ʈ
		MIXSHADER_TT_CHROME2,
		MIXSHADER_TT_CHROME3,
		MIXSHADER_TT_CHROME4,
		MIXSHADER_TT_CHROME5,
		MIXSHADER_TT_METAL,
		MIXSHADER_TT_OIL,
		MIXSHADER_TT_CHROME6,
		MIXSHADER_TT_WAVE,					// 10

		MIXSHADER_TT_ALL
	}MixShaderTT_t;

	typedef enum _SpecialVP_t
	{
		SPVP_BODYSHADOW = 0,	//�׸��� ���̴�
		SPVP_SPRITE,			//��������Ʈ ����
		SPVP_WATER,				//�÷��� ���� ������

		SPVP_ALL
	}SpecialVP_t;


	// Fragment Shader �� Program ����.
	typedef enum _FragmentShader_t
	{
		FRAGMENT_ST_DEFAULT = 0,
		FRAGMENT_ST_DEFAULT_NOFOG,
		FRAGMENT_ST_NONLIGHT_DEFAULT,
		FRAGMENT_ST_NONLIGHT_NOFOG_DEFAULT,

		FRAGMENT_MT_DEFAULT,
		FRAGMENT_MT_BRIGHT,
		FRAGMENT_MT_DARK,
		FRAGMENT_MT_LIGHTMAP,

		FRAGMENT_MT_NONLIGHT_DEFAULT,
		FRAGMENT_MT_NONLIGHT_BRIGHT,
		FRAGMENT_MT_NONLIGHT_DARK,
		FRAGMENT_MT_NONLIGHT_LIGHTMAP,

		FRAGMENT_MT_REPLACE,

		FRAGMENT_ALL
	}FragmentShader_t;

	
	void	SelectVProgram(int iProgram);		//���ؽ� ���α׷�(���̴�) �� �����Ѵ�.
	void	SelectVPSProgram(int iProgram);		//Ư���� ���ؽ� ���α׷��� �����Ѵ�. 
	void	SelectFProgram(int iProgram);		//�����׸�Ʈ ���α׷��� �����Ѵ�.

	//Chrome���� ����Ʈ ���, �˻�
	bool	RegisterTextureEffect(int iflag, int iTex, int iProgram);	// ���̴��� ����� �� ȿ�� ���� �ؽ��ĸ� �Է�. (ex. RENDER_CHROME, RENDER_CHROME1, RENDER_CHROME2,,,)
	void	GetTextureEffect(int iFlag, int& outTex, int& outProgram);	// ȿ���� ����ϴ� �ؽ��Ŀ� ���̴� ���α׷� �� ����.
}

#endif // __VPMANAGER_H__