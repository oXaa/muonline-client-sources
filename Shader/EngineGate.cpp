#include "stdafx.h"

#ifdef MR0

//////////////////////////////////////////////////////////////////////////
// 
// EngineGate.cpp : ���̴� ������ ���� ������ �ӽ�, �޴��� �ʱ�ȭ, �޸� ��ȯ ó��
//
//////////////////////////////////////////////////////////////////////////

#include "EngineGate.h"
#include <io.h>

using namespace ModelManager;

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� ���� ������ ����� ����. // �׽�Ʈ��
///////////////////////////////////////////////////////////////////////////////////////////
namespace EngineGate
{
	//������ �ɼǰ���
	bool m_bIsOn = false;
	bool m_bRenderWater = false;

	void OpenRendererConf();
	void ExpCurrentConf();

	const std::string cStrExpFn = "CurMR.txt";
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� Ÿ�� ���� ���Ͽ��� �о���� �������� ���� �ϵ��� ����
///////////////////////////////////////////////////////////////////////////////////////////
void EngineGate::OpenRendererConf()
{
	std::string nConfig;
	char szTemp[MAX_PATH] = { 0, };
	
	GetModuleFileName(NULL, szTemp, MAX_PATH);
	nConfig = szTemp;
	nConfig = nConfig.substr(0, nConfig.rfind('\\')+1);
	nConfig += "mrconfig.cfg";

	if(_access(nConfig.c_str(), 0) == -1)
		return;

	GetPrivateProfileString("General", "Type", "", szTemp, 11, nConfig.c_str());
	SetGeneralType(atoi(szTemp));
	GetPrivateProfileString ("General", "Water", "", szTemp, 11, nConfig.c_str());
	if(atoi(szTemp) != 0) m_bRenderWater = true;
	else m_bRenderWater = false;
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� Ÿ�� ���� ���Ϸ� ��� CurMR.txt ����
///////////////////////////////////////////////////////////////////////////////////////////
void EngineGate::ExpCurrentConf()
{
	FILE* fp = fopen(cStrExpFn.c_str(), "wt");
	fprintf(fp, "Used Driver Type:%d\n", g_iUseDriverType);
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� ��ũ��Ʈ ������, ���̴� ���� �ӽ� �ʱ�ȭ
///////////////////////////////////////////////////////////////////////////////////////////
void EngineGate::Init()
{
	// 1. ���� �ý���(�׷���ī��)�� �����ϴ� PixelShader, VertexShader ������ ���� ���̴� �ܰ�(g_iUseDriverType) �ڵ� ����.
	InitExtension();
	
	// 2. mfconfig.cfg���̴� ���� ���Ϸκ��� ���̴� �ܰ�(g_iUseDriverType)�� �缳��.
	OpenRendererConf();

#ifdef LDS_MR0_FORDEBUG_MESHALLWAYS_VSTYPE

	// 3. ���� ���̴� ���� ���� ���� - �׽�Ʈ �뵵.
#ifdef LDS_MR0_MOD_SET_LOWRENDERER_INIT
	//g_iUseDriverType = GPVER_LOW;
	g_iUseDriverType = GPVER_HIGH;
#else // LDS_MR0_MOD_SET_LOWRENDERER_INIT
	if( g_iUseDriverType == GPVER_HIGHEST )		// ** FragmentShader ���� ���� �̱���
	{
		g_iUseDriverType = GPVER_HIGH;
	}
#endif // LDS_MR0_MOD_LOWRENDERER_SETFORINTIALIZE

#endif // LDS_MR0_FORDEBUG_MESHALLWAYS_VSTYPE

	// 4. ���̴� ���� �ܰ迡 ���� (���ؽ� ���̴� �ӽ�or ����׸�Ʈ ���̴� �ӽ�)������ �ʱ�ȭ
	if(g_iUseDriverType == GPVER_HIGH)			// VertexShaderRendererMachine
	{
		g_Renderer = new CVBOShaderMachine;
		m_bIsOn = true;
	}
	else if(g_iUseDriverType == GPVER_HIGHEST)	// PixelShaderRendererMachine
	{
		g_Renderer = new CVBOPixelShaderMachine;
		m_bIsOn = true;
	}
	else
	{
		m_bIsOn = false;
		ExpCurrentConf();
		return;
	}
	
	// 5. ���̴� ��ũ��Ʈ �� ���̴� �ؽ��� ������.
	VPManager::Init();

	// 6. ���� �޴��� �ӽ� �ʱ�ȭ.
	ModelManager::Init();

#ifdef MR0_NEWRENDERING_EFFECTS_SPRITES
	//��������Ʈ �Ŵ��� �ʱ�ȭ
	SpriteManager::Init();
#endif // MR0_NEWRENDERING_EFFECTS_SPRITES

	// 7. CurMR.txt���Ϸ� ���� ������ ���. // FOR DEBUG
	ExpCurrentConf();
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� �������� �Ѱ� ����.
///////////////////////////////////////////////////////////////////////////////////////////
bool EngineGate::IsOn() { return m_bIsOn; }

#ifdef LDS_MR0_ADD_VBOMANAGER_SETONOFF
void EngineGate::SetOn( bool bSetOn )
{
	// ���� ���̴� ������ Low ��, �̹� ���̴� �������� ���� �����Ƿ� ���� �� �ʿ� ����.
	if(g_iUseDriverType < GPVER_HIGH)
	{
		return;
	}

	m_bIsOn = bSetOn;
}
#endif // LDS_MR0_ADD_VBOMANAGER_SETONOFF

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� �ӽ� �޸� ��ȯ ó�� : ���� �޽� �޴��� �ӽ�, ���̴� �����Ϸ� ��Ŀ �޴���, ���̴� �ӽ� �޸� ��ȯ.
///////////////////////////////////////////////////////////////////////////////////////////
void EngineGate::UnInit()
{
#ifdef MR0_NEWRENDERING_EFFECTS_SPRITES
	SpriteManager::UnInit();
#endif // MR0_NEWRENDERING_EFFECTS_SPRITES

	// ���̴� ���� �޴��� �ӽ� �޸� ��ȯ.
	ModelManager::UnInit();

	// �����ϵ� ���̴� ��Ŀ OpenGL ��ɾ ���� �޸� ��ȯ.
	VPManager::Uninit();

	// MR0 ���̴� �ӽ� �޸� ��ȯ : ���ؽ����̴� �ӽ� �Ǵ� �ȼ����̴� �ӽ�
	if(g_Renderer) 
	{
		delete g_Renderer;
		g_Renderer = NULL;
	}
}

#endif //MR0
