#include "stdafx.h"

#ifdef MR0

//////////////////////////////////////////////////////////////////////////
// 
// ModelManager.cpp : �޽� �����̳�, ���̴� �޴���, BMD���� VBOMESH��ȯ ��� ����.
//
//////////////////////////////////////////////////////////////////////////

#include "ModelManager.h"
#include "ZzzTexture.h" 
#include "VPManager.h"
#include "ZzzBMD.h"
#include "SMD.h"

#include "GLUtils.h"
#include "RenderMachine.h"

#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include <io.h>

using namespace ModelManager;
using namespace VPManager;
namespace ModelManager
{	
	//������� �����̳� (���Ҵ�Ǵ� ���� ������ ó��)
	Vector4Vec	g_ContanceContainer;

	//���� ���
	unsigned int c_iAniTypeOffset = MIXSHADER_NT_ALL*MIXSHADER_CT_ALL*MIXSHADER_TT_DEF_ALL*MIXSHADER_TT_ALL;
	unsigned int c_iNormTypeOffset = MIXSHADER_CT_ALL*MIXSHADER_TT_DEF_ALL* MIXSHADER_TT_ALL;
	unsigned int c_iCorTypeOffset = MIXSHADER_TT_DEF_ALL*MIXSHADER_TT_ALL;
}

namespace EngineGate
{
	extern	bool m_bIsOn;
}

///////////////////////////////////////////////////////////////////////////////////////////
// �޽� ���� �ӽ� �ʱ�ȭ // ���� Immediate Mesh�� ������ �޴��� �Դϴ�. 
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::Init()
{
	g_pMeshMachine = new CMeshMachine;
//g_ContanceContainer.reserve(100);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Immediate Mesh �� ������ ��� ������ �ӽ��� �޸� ��ȯ ó��.
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::UnInit()
{
	if(g_pMeshMachine)
	{
#ifdef LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
		g_pMeshMachine->UnInit();
#endif // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
		delete g_pMeshMachine;
		g_pMeshMachine = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD �� �޽��������� VBOMesh(���̴� ������ ���� �޽�)�� ��ȯ �մϴ�. 
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
void ModelManager::Convert(unsigned int m, bool bDelOldMesh, bool bValidationCheckForDebug)
#else // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
void ModelManager::Convert(unsigned int m, bool bDelOldMesh)
#endif // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
{
	if(!EngineGate::m_bIsOn) return;

	Models[m].m_iBMDSeqID = m;
	if(g_iUseDriverType >= GPVER_HIGH)
	{
#ifdef LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
		Models[m].ConvertMesh( bValidationCheckForDebug );
#else // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
		Models[m].ConvertMesh();
#endif // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
		Models[m].UploadVBO();
		if(bDelOldMesh)
		{
			switch(m)
			{
				// BMD �� ������ �״�� �����ؾ��ϴ� �޽��� ����. // ������ �𵨵��� ��� BMD�� ������ �޽� �����̳ʸ� ��� ���� �մϴ�.
				case 62:
				case MODEL_PANTS+18:		// �׷���ҿ� ����
				case MODEL_PANTS+19:		// Ȧ�������� ����
				case MODEL_PANTS+22:		// ���ҿ� ����
				case MODEL_STONE_COFFIN:
				case MODEL_GATE:
				case MODEL_BIG_STONE_PART1:
				case MODEL_BIG_STONE_PART2:
				case MODEL_WALL_PART1:
				case MODEL_GATE_PART2:
				case MODEL_GOLEM_STONE:
				case MODEL_SKIN_SHELL:
				case MODEL_MONSTER01+66:
#ifdef LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY
				case MODEL_HELPER+64:		// ����
				case MODEL_HELPER+65:		// ��ȣ����
				case MODEL_HELPER+67:		// �絹��
				case MODEL_HELPER+80:		// ���
				case MODEL_HELPER+106:		// ������
#endif // LDS_MR0_FIX_ALLPETOBJECT_RENDERINGPASSEDWAY
#ifdef LDS_MR0_ADD_DONTDELETE_OLDMESHSBUFFER_DARKSPIRIT
				case MODEL_DARK_SPIRIT:		// ��ũ���Ǹ� : ƽ���� ���ؽ������� ���� �Լ� RenderMeshEffect() ȣ��.
#endif // LDS_MR0_ADD_DONTDELETE_OLDMESHSBUFFER_DARKSPIRIT
				{
#ifdef LDS_MR0_ADD_SPECIFICMODEL_DOANIMATIONPROCESSING
					// ���̴� ���� ���� ���ؽ� ó���� ���� ������
					// ������ ����� ������ ���� parts ���� �޽��� ��� Shader������ �ƴ� ������ ������ CPU�����ϵ��� �մϴ�.
					switch(m)
					{
					case MODEL_PANTS+18:		// �׷���ҿ� ����	
					case MODEL_PANTS+22:		// ���ҿ� ����	//    "
						{
							Models[m].m_bProcessAnimationTMUsingPassedMothod = true;
						}
						break;
					}
#endif // LDS_MR0_ADD_SPECIFICMODEL_DOANIMATIONPROCESSING
				}
				break;
				default:
					Models[m].DelOldMesh();
					break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// MAX���� Export���� ResourceConvert�ÿ� ������ BMD ������ �����ɴϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
char ModelManager::GetModelVersion(unsigned int i) 
{ 
	return Models[i].Version; 
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD �𵨿� �̸��� �缳�� �մϴ�. ���� �Ⱦ���.
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::SetModelName(unsigned int i, const std::string& n)
{
	strcpy(Models[i].Name, n.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD ���� ���� ������ �����ɴϴ�. ".lst"���Ͽ� ���ǵ� ������ŭ
///////////////////////////////////////////////////////////////////////////////////////////
int ModelManager::GetActionCount(unsigned int i)
{ 
	return Models[i].NumActions;
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD ���� ������ �ؽ��� ������ŭ Split�� Mesh�� ������ �����ɴϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
int ModelManager::GetMeshCount(unsigned int i)
{ 
	return Models[i].NumMeshs;
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD ���� Post Effect�� Default ����.
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::AttachDefaultEffect(unsigned int iModel)
{
	BMD& rModel = Models[iModel];
	for(int i = 0; i < rModel.NumMeshs; ++i)
	{
		VBOMesh& rMesh = rModel.NewMeshs[i];
		EffectScrip_t tEffect;
		tEffect.m_fAlpha = 1.f;
		tEffect.m_iTex = -1;
		tEffect.m_tShader = RENDER_TEXTURE;
		strcpy(tEffect.m_strTexName, "");
		Vector(1.f, 1.f, 1.f, tEffect.m_vColor3f);
		rMesh.MeshEffectScript.push_back(tEffect);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// BMD �𵨿� ���ǵǾ��ִ� Post Effect�� ������ ��ȯ.
///////////////////////////////////////////////////////////////////////////////////////////
unsigned int ModelManager::GetEffectCount(unsigned int ModelID, unsigned int MeshID)
{
	BMD& rModel = Models[ModelID];
	VBOMesh& rMesh = rModel.NewMeshs[MeshID];
	return rMesh.MeshEffectScript.size();
}

//////////////////////////////////////////////////////////////////////////
// 
// Batch Rendering // Immediate Mesh�� ����
//
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
// Immediate Mesh ������ ���۰� ���Ḧ ���� �ϴ� �Լ�
//  ex)			SetTargetObject(o);		// ���� ���� // ������ ���ϰ� ���
//					RenderMesh(...);		// Immediate Mesh�� �޽� �ӽſ� ����. // ���� ȣ��� �޽� �ӽ� ���̺� ���縸 �մϴ�.
//					RenderBody(...);		//							"
//				SetTargetObject(NULL);	// ���� ���� �� ������ // �޽� �ӽſ� ����� ��� Immediate Mesh���� ���� ���̴� ������ ������ ���� ������ �ϵ��� �մϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::SetTargetObject(OBJECT* pObj)
{
	if(!EngineGate::m_bIsOn) return;

	if(pObj)
	{
		g_pMeshMachine->Lock(true);
	}
	else
	{
		g_pMeshMachine->Flush();
		g_pMeshMachine->Lock(false);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Object O ���� BMD�� ���� �ϴ°�찡 ��Ȥ �߻��Ͽ� Flag�� ������ ����.
///////////////////////////////////////////////////////////////////////////////////////////
void ModelManager::SetTargetObject_(int iFlag)
{
	if(!EngineGate::m_bIsOn) return;
	
	if(iFlag != 0)
	{
		g_pMeshMachine->Lock(true);
	}
	else
	{
		g_pMeshMachine->Flush();
		g_pMeshMachine->Lock(false);
	}
}	

//////////////////////////////////////////////////////////////////////////
// 
// Immediate Mode �� ��ġ �ý���
//
//////////////////////////////////////////////////////////////////////////

using namespace ModelManager;

CMeshMachine* g_pMeshMachine = NULL;

CMeshMachine::CMeshMachine()
{
	m_bTransop = false;
	m_Data.reserve(10);
	
#ifdef LDS_MR0_INTIALIZE_SOME_MAINVARIABLES
	m_bLock = false;
	m_bOn = true;

	memset(m_vLightPosOrg, 0, sizeof(vec3_t));		//���� ������ Light��ǥ
	memset(m_vLightDirOrg, 0, sizeof(vec3_t));
	memset(m_vLightPos, 0, sizeof(vec3_t));
	memset(m_vLightDir, 0, sizeof(vec3_t));
#endif // LDS_MR0_INTIALIZE_SOME_MAINVARIABLES
}

CMeshMachine::~CMeshMachine()
{
#ifdef LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
#else // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
	m_Data.clear();				// Immediate Mesh ���� �����̳�
#endif // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
}

///////////////////////////////////////////////////////////////////////////////////////////
// �ؽ��� ���� Ÿ���� ���� ��� ���� ��ȯ.
///////////////////////////////////////////////////////////////////////////////////////////
bool CMeshMachine::IsAlphaNoUseType(int iType)
{
	if(iType&RENDER_BRIGHT) return true;
	
	if(iType&RENDER_CHROME3) return true;
	else if(iType&RENDER_CHROME4) return true;
	else if(iType&RENDER_CHROME5) return true;
	else if(iType&RENDER_CHROME7) return true;
#ifdef PJH_NEW_CHROME
	else if(iType&RENDER_CHROME8) return true;
#endif //PJH_NEW_CHROME
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
// 0-10 ������ ���̴� �Ķ���� �����̳ʿ� �� ���� // Shader�� �ѱ�� �Ķ���ʹ� Local �Ǵ� Environment �ΰ��� �Ķ���Ͱ� ����.
///////////////////////////////////////////////////////////////////////////////////////////
void CMeshMachine::MakeConst(int iType, int iColorType, bool bAlphaNoUse,
							 float BlendMeshTexCoordU, float BlendMeshTexCoordV, MeshRender_t& r)
{
	Vector4Vec& rRegister = r.m_matConstants;

	//����Ʈ ��ġ�ϰ� ������ �⺻������ �����Ѵ�.
	r.m_iNumConst = 2;
	rRegister.push_back(nv4());								// m_matConstants[0] 0: VertexColor + VertexAlpha
	nv4* ptmp = &rRegister[rRegister.size() - 1];
	if(bAlphaNoUse)
	{
		ptmp->x = r.m_vColor.x * r.m_fAlpha; 
		ptmp->y = r.m_vColor.y * r.m_fAlpha;
		ptmp->z = r.m_vColor.z * r.m_fAlpha;
		ptmp->w = 1.f;
	}
	else
	{
		ptmp->x = r.m_vColor.x; 
		ptmp->y = r.m_vColor.y;
		ptmp->z = r.m_vColor.z;
		ptmp->w = r.m_fAlpha;
	}

	rRegister.push_back(nv4());								// m_matConstants[1] 1: Light Position or Light Dir
	ptmp = &rRegister[rRegister.size() - 1];

	if(iColorType == MIXSHADER_CT_DIRECTIONAL)
		memcpy(ptmp, m_vLightDir, sizeof(float)*3);
	else if(iColorType == MIXSHADER_CT_DIFFUSE)
		memcpy(ptmp, m_vLightPos, sizeof(float)*3);
	else
		memset(ptmp, 0, sizeof(float)*3);
	ptmp->w = 1.f;


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
	switch(iType)
	{
		case MIXSHADER_TT_BLENDMESH:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];
				
				ptmp->x = BlendMeshTexCoordU;
				ptmp->y = BlendMeshTexCoordV;
				ptmp->z = 1.f;
				ptmp->w = 0.f;
			}
			break;
		
		case MIXSHADER_TT_CHROME1:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = 1.f;
				ptmp->y = 0.f;
				ptmp->z = (int)WorldTime % 10000 * 0.0001f;
				ptmp->w = 0.f;

				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = 0.5f;
				ptmp->y = 0.5f;
				ptmp->z = 2.0f;
				ptmp->w = 1.f;
			}
			break;

		case MIXSHADER_TT_CHROME2:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];
				
				ptmp->x = 1.f;
				ptmp->y = 0.f;
				ptmp->z = 0.f;
				ptmp->w = (int)WorldTime % 5000 * 0.00024f - 0.4f;

				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = 0.8f;
				ptmp->y = 2.f;
				ptmp->z = 1.f;
				ptmp->w = 3.f;
			}
			break;

		case MIXSHADER_TT_CHROME3:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = 0.0;
				ptmp->y = -0.1f;
				ptmp->z = -0.8f;
				ptmp->w = 1.f;		
			}
			break;

		case MIXSHADER_TT_CHROME4:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = cosf(WorldTime*0.001f);
				ptmp->y = sinf(WorldTime*0.002f);
				ptmp->z = 1.f;
				ptmp->w = (int)WorldTime%10000 * 0.0001f;

				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];

				ptmp->x = BlendMeshTexCoordU;
				ptmp->y = BlendMeshTexCoordV;
				ptmp->z = 1.f;
				ptmp->w = 0.f;

				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];				

				ptmp->x = 0.5f;
				ptmp->y = 3.f;
				ptmp->z = 0.5f;
				ptmp->w = 3.f;	
			}
			break;

		case MIXSHADER_TT_CHROME5:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	

				ptmp->x = cosf(WorldTime*0.001f);
				ptmp->y = sinf(WorldTime*0.002f);
				ptmp->z = 1.f;
				ptmp->w = (int)WorldTime%10000 * 0.0001f;

				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	

				ptmp->x = 2.5f;
				ptmp->y = 1.f;
				ptmp->z = 3.f;
				ptmp->w = 5.f;
			}
			break;

		case MIXSHADER_TT_CHROME6:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	

				ptmp->x = 0.8f;
				ptmp->y = 2.f;
				ptmp->z = (int)WorldTime % 5000 * 0.00024f - 0.4f;
				ptmp->w = 0.f;

				if(r.m_iTex == -1)
					r.m_iTex = BITMAP_CHROME6;
			}
			break;

		case MIXSHADER_TT_METAL:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	

				ptmp->x = 0.5f;
				ptmp->y = 0.2f;
				ptmp->z = 0.5f;
				ptmp->w = 0.5f;

				if(r.m_iTex == -1)
					r.m_iTex = BITMAP_SHINY;
			}
			break;

		case MIXSHADER_TT_OIL:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	

				ptmp->x = BlendMeshTexCoordU;
				ptmp->y = BlendMeshTexCoordV;
				ptmp->z = 1.f;
				ptmp->w = 0.f;
			}
			break;

		//��� ����.. ���� ���� �� ��.
		case MIXSHADER_TT_WAVE:
			{
				++r.m_iNumConst;
				rRegister.push_back(nv4());
				ptmp = &rRegister[rRegister.size()-1];	
				
				ptmp->x = BlendMeshTexCoordU;
				ptmp->y = BlendMeshTexCoordV;
				ptmp->z = 1.f;
				ptmp->w = 0.f;				
			}
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// �� ƽ���� Light ������ ���� �մϴ�. // ���� �¿��� Light�� Directional Light�� ���� �ϹǷ� ���⼺ ���� ���� �Է� �մϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
void CMeshMachine::ProcessLight(bool bHighLight, bool bBattleCastle)
{
	if(bHighLight)
	{
		Vector(1.3f, 0.f, 2.f, m_vLightPosOrg);
	}
	else if (bBattleCastle)
	{
		Vector (0.5f, -1.f, 1.f, m_vLightPosOrg);
	}
	else
	{
		Vector(0.f, -1.5f, 0.f, m_vLightPosOrg);
	}

	VectorCopy(m_vLightPosOrg, m_vLightDirOrg);
//	VectorNormalize(m_vLightDirOrg);
}

///////////////////////////////////////////////////////////////////////////////////////////
// RenderMesh���� ȣ�� �Ǹ�, �׷��� �޽��� Render State�� ���� �ϰ�, ���̴� �Ķ���͵��� ���� �Ѵ���
//  MeshContainer�� ���縸 �մϴ�. ���߿� Flush���� ����� Mesh���� �ѹ��� ������ �մϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
extern int WaterTextureNumber;
void CMeshMachine::AddRender(BMD* pSource, int idx,int RenderFlag,float Alpha,int BlendMesh,
		float BlendMeshLight,float BlendMeshTexCoordU,float BlendMeshTexCoordV,int MeshTexture)
{
	VBOMesh& rMesh = pSource->NewMeshs[idx];
	Mesh_t& rOldMesh = pSource->Meshs[idx];
	
	if(RenderFlag&RENDER_BYSCRIPT)
	{
		EffectScripVec_t& rVec = rMesh.MeshEffectScript;
		EffectScripVec_t::iterator iter = rVec.begin();
		for(; iter != rVec.end(); ++iter)
		{
			m_Data.push_back(MeshRender_t());
			MeshRender_t& rNew = m_Data[m_Data.size()-1];
			EffectScrip_t& rScript = *iter;
			if(rScript.m_tShader != RENDER_TEXTURE) rNew.m_iTex = rScript.m_iTex;
			rNew.m_pSourceBMD = pSource;
			rNew.m_iMesh = idx;			
			rNew.m_iFlag = rScript.m_tShader;
			rNew.m_fAlpha = rScript.m_fAlpha;
			rNew.m_bLight = !pSource->bOffLight;
			memcpy(&rNew.m_vColor.x, rScript.m_vColor3f, sizeof(float)* 3);
			
			//�⺻���� ���� ���̴� ����
			int iAniType = 0;
			if(pSource->NumActions > 0)
			{
				iAniType = 1; //MIXSHADER_VT_ONELINK_DEFAULT
				if(rOldMesh.MeshAdditionalSkinInfo.size() > 0) iAniType = 2; //MIXSHADER_VT_TWOLINK_DEFAULT
			}
			else
				iAniType = 0; //MIXSHADER_VT_NOBONE_DEFAULT
			
			int iNormType = MIXSHADER_NT_DEFAULT;
			int iColorType = MIXSHADER_CT_AMBIENT;
			int iDefTexType = MIXSHADER_TT_DEF_SINGLE_TEXTURE;
			int iTexType = MIXSHADER_TT_NONE;
				VPManager::GetTextureEffect(rNew.m_iFlag, rNew.m_iTex, iTexType);
			if(MeshTexture != -1) rNew.m_iTex = MeshTexture;
			else if(rNew.m_iTex == -1) rNew.m_iTex = pSource->IndexTexture[rMesh.Texture];
			if(iTexType == MIXSHADER_TT_NONE)
			{
				if(rMesh.m_csTScript)
				{
					if(rMesh.m_csTScript->getStreamMesh())
					{
						iTexType = MIXSHADER_TT_BLENDMESH;
						
					}
#ifdef LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
#else // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
					else if(rMesh.m_csTScript->getNoneBlendMesh())
					{
						//�ȱ׷��� �Ǵ� �޽���.
						m_Data.pop_back();
						return;
					}
#endif // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
				}
				//����޽� �ν�1
				else if(idx == BlendMesh || idx == pSource->StreamMesh)
				{
					iTexType = MIXSHADER_TT_BLENDMESH;
					rNew.m_bLight = false;
				}

				//����޽� ����Ʈ ����
				if(BlendMesh <= -2 || rMesh.Texture == BlendMesh)
				{
					if(!(rNew.m_iFlag&RENDER_BRIGHT)) rNew.m_iFlag |= RENDER_BRIGHT;

#ifdef LDS_MR0_MODIFY_ANIMATIONMAPPING_NOANIMATED
					if (BlendMeshTexCoordU!=0.f || BlendMeshTexCoordV!=0.f)
					{
						iTexType = MIXSHADER_TT_BLENDMESH;
					}
#endif // LDS_MR0_MODIFY_ANIMATIONMAPPING_NOANIMATED

					rNew.m_vColor.x *= BlendMeshLight;	
					rNew.m_vColor.y *= BlendMeshLight;
					rNew.m_vColor.z *= BlendMeshLight;
					rNew.m_fAlpha = 1.f;
				}				
			}
			else
			{
				if(rOldMesh.NoneBlendMesh)
				{
					m_Data.pop_back();
					return;
				}
#ifdef LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
				if(rMesh.m_csTScript->getNoneBlendMesh())
				{
					//�ȱ׷��� �Ǵ� �޽���.
					m_Data.pop_back();
					return;
				}
#endif // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH

				//�ؽ�������Ʈ�� �ִ�.
				iNormType = MIXSHADER_NT_TRANSFORM;
				rNew.m_bLight = false;
			}


			//�Ϲ��� �ƴ� Ư �� ���̴��� ���� ���
			// MR0_MODIFY : rNew.m_iTex���� -1�� �Ǿ� ����� ������ �߻��Ͽ� ��ġ ����
			if(rNew.m_iFlag&RENDER_SHADOWMAP)
			{
				rNew.m_bUseFixedVP = true;
				rNew.m_bLight = true;

#ifdef LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
				rNew.m_iFlag = RENDER_COLOR|RENDER_SHADOWMAP;
#else // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
				rNew.m_iFlag = RENDER_COLOR;
#endif // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH

				rNew.m_iVProgram = SPVP_BODYSHADOW;
				
				//��� ����
				++rNew.m_iNumConst;
				rNew.m_matConstants.push_back(nv4());
				nv4* pTmp = &rNew.m_matConstants[rNew.m_matConstants.size() - 1];
				memcpy(pTmp, pSource->BodyLight, sizeof(float)*3);
				pTmp->w = 1.f;
				
				//Light �ڸ��� �׸��� ������� �ʿ��� �� �ִ´�.
				++rNew.m_iNumConst;
				rNew.m_matConstants.push_back(nv4());
				pTmp = &rNew.m_matConstants[rNew.m_matConstants.size() - 1];
				memcpy(pTmp, pSource->BodyOrigin, sizeof(float)*3);
				pTmp->w = 1.f;
				continue;
			}


			if(rNew.m_bLight)
			{
				iNormType = MIXSHADER_NT_TRANSFORM;
				iColorType = MIXSHADER_CT_DIRECTIONAL; //MIXSHADER_CT_DOUBLE�� �ϴ� �Ⱦ���.
				
				vec34_t mat;
				AngleMatrix(pSource->ShadowAngle, mat);
				VectorIRotate(m_vLightDirOrg,mat,m_vLightDir);			
			}

			MakeConst(iTexType, iColorType, IsAlphaNoUseType(RenderFlag), BlendMeshTexCoordU, BlendMeshTexCoordV, rNew);
			rNew.m_iVProgram =	iAniType * c_iAniTypeOffset +
								iNormType * c_iNormTypeOffset +
								iColorType * c_iCorTypeOffset +
								iDefTexType * (MIXSHADER_TT_ALL) +
								iTexType;			
		}
	}
	else
	{
		m_Data.push_back(MeshRender_t());
		MeshRender_t& rNew = m_Data[m_Data.size()-1];
		rNew.m_pSourceBMD = pSource;
		rNew.m_iMesh = idx;
		rNew.m_iFlag = RenderFlag;
		rNew.m_fAlpha = Alpha;
		rNew.m_bLight = !pSource->bOffLight;
		rNew.m_bLight = pSource->LightEnable;
		memcpy(&rNew.m_vColor.x, pSource->BodyLight, sizeof(float)*3);
		
		//���� ���̴� ���� ����
		int iAniType = 0;
		if(pSource->NumActions > 0)
		{
			iAniType = 1; //MIXSHADER_VT_ONELINK_DEFAULT
			if(rOldMesh.MeshAdditionalSkinInfo.size() > 0) iAniType = 2; //MIXSHADER_VT_TWOLINK_DEFAULT
		}
		else
			iAniType = 0; //MIXSHADER_VT_NOBONE_DEFAULT
		
		int iNormType = MIXSHADER_NT_DEFAULT;
		int iColorType = MIXSHADER_CT_AMBIENT;
		int iDefTexType = MIXSHADER_TT_DEF_SINGLE_TEXTURE;
		int iTexType = MIXSHADER_TT_NONE;
		int iSourceTex = pSource->IndexTexture[rMesh.Texture];

		// ���� �߰� :
		//	���� ���� 1. Texture Render Hide �� �߰� ���� 2. Shadow Render�� Texture Render�� ���� ������ Render
#ifdef LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
		if( BITMAP_HIDE == iSourceTex && RenderFlag != ( RENDER_SHADOWMAP|RENDER_TEXTURE ) )
#else // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
		if( BITMAP_HIDE == iSourceTex )
#endif // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
		{
			m_Data.pop_back();
			return;			
		}
		else if(iSourceTex == BITMAP_SKIN)
		{
			if(pSource->HideSkin)
			{
				m_Data.pop_back();
				return;
			}
			iSourceTex = BITMAP_SKIN + pSource->Skin;
		}
		else if(iSourceTex == BITMAP_WATER)
		{
			iSourceTex = BITMAP_WATER + WaterTextureNumber;
		}
		else if(iSourceTex == BITMAP_HAIR )
		{
			if(pSource->HideSkin)
			{
				m_Data.pop_back();
				return;
			}
			iSourceTex = BITMAP_HAIR+(pSource->Skin-8);
		}

		VPManager::GetTextureEffect(rNew.m_iFlag, rNew.m_iTex, iTexType);
		if(rNew.m_iTex == -1) rNew.m_iTex = iSourceTex;
		if(MeshTexture != -1) rNew.m_iTex = MeshTexture;
		if(iTexType == MIXSHADER_TT_NONE)
		{
			if(rMesh.m_csTScript)
			{
				if(rMesh.m_csTScript->getStreamMesh())
				{
					iTexType = MIXSHADER_TT_BLENDMESH;
				}
#ifdef LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
#else // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
				if(rMesh.m_csTScript)
				{
					if(rMesh.m_csTScript->getNoneBlendMesh())
					{
						//�ȱ׷��� �Ǵ� �޽���.
						m_Data.pop_back();
						return;
					}
				}
#endif // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
			}
			//����޽� �ν�1
			else if(idx == BlendMesh || idx == pSource->StreamMesh)
			{
				iTexType = MIXSHADER_TT_BLENDMESH;
				rNew.m_bLight = false;
			}

			//����޽� ����Ʈ ����
			if(BlendMesh <= -2 || rMesh.Texture == BlendMesh)
			{
				if(!(rNew.m_iFlag&RENDER_BRIGHT)) rNew.m_iFlag |= RENDER_BRIGHT;
				
#ifdef LDS_MR0_MODIFY_ANIMATIONMAPPING_NOANIMATED
				if (BlendMeshTexCoordU!=0.f || BlendMeshTexCoordV!=0.f)
				{
					iTexType = MIXSHADER_TT_BLENDMESH;
				}
#endif // LDS_MR0_MODIFY_ANIMATIONMAPPING_NOANIMATED

				rNew.m_vColor.x *= BlendMeshLight;
				rNew.m_vColor.y *= BlendMeshLight;
				rNew.m_vColor.z *= BlendMeshLight;
				rNew.m_fAlpha = 1.f;
			}
		}
		else
		{
			if(rOldMesh.NoneBlendMesh)
			{
				m_Data.pop_back();
				return;
			}
#ifdef LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
			if(rMesh.m_csTScript)
			{
				if(rMesh.m_csTScript->getNoneBlendMesh())
				{
					//�ȱ׷��� �Ǵ� �޽���.
					m_Data.pop_back();
					return;
				}
			}
#endif // LDS_MR0_MODIFY_RENDER_SKIPORNOT_WHEN_NONBLENDMESH
			
			iNormType = MIXSHADER_NT_TRANSFORM;
			rNew.m_bLight = false;
		}

		// MR0_MODIFY : rNew.m_iTex���� -1�� �Ǿ� ����� ������ �߻��Ͽ� ��ġ ����
		if(rNew.m_iFlag&RENDER_SHADOWMAP)
		{
			rNew.m_bUseFixedVP = true;
			rNew.m_bLight = true;
			
#ifdef LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
			rNew.m_iFlag = RENDER_COLOR|RENDER_SHADOWMAP;
#else // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH
			rNew.m_iFlag = RENDER_COLOR;
#endif // LDS_MR0_MODIFY_MISSRENDERSHADOW_MOSTMESH

			//rNew.m_iFlag = RENDER_COLOR;
			rNew.m_iVProgram = SPVP_BODYSHADOW;
			
			//��� ����
			++rNew.m_iNumConst;
			rNew.m_matConstants.push_back(nv4());
			nv4* pTmp = &rNew.m_matConstants[rNew.m_matConstants.size() - 1];
			memcpy(pTmp, pSource->BodyLight, sizeof(float)*3);
			pTmp->w = 1.f;
			
			//Light �ڸ��� �׸��� ������� �ʿ��� �� �ִ´�.
			++rNew.m_iNumConst;
			rNew.m_matConstants.push_back(nv4());
			pTmp = &rNew.m_matConstants[rNew.m_matConstants.size() - 1];
			memcpy(pTmp, pSource->BodyOrigin, sizeof(float)*3);
			pTmp->w = 1.f;
			return;
 		}


		if(rNew.m_bLight)
		{
			iNormType = MIXSHADER_NT_TRANSFORM;
			iColorType = MIXSHADER_CT_DIRECTIONAL; //MIXSHADER_CT_DOUBLE�� �ϴ� �Ⱦ���.
			
			vec34_t mat;
			AngleMatrix(pSource->ShadowAngle, mat);
			VectorIRotate(m_vLightDirOrg,mat,m_vLightDir);
		}

		MakeConst(iTexType,iColorType, IsAlphaNoUseType(RenderFlag), BlendMeshTexCoordU, BlendMeshTexCoordV, rNew);
		rNew.m_iVProgram =	iAniType * c_iAniTypeOffset +
							iNormType * c_iNormTypeOffset +
							iColorType * c_iCorTypeOffset +
							iDefTexType * (MIXSHADER_TT_ALL) +
							iTexType;
	}
}

void CMeshMachine::Flush()
{
	m_bLock = false;
	MeshRenderVector_t::iterator iter = m_Data.begin();
	for(; iter != m_Data.end(); ++iter)
		g_Renderer->Render(*iter);
	m_Data.resize(0);
}


#ifdef LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
void CMeshMachine::UnInit()
{
	// MR0_MODIFY : ���� stl::vector �ʱ�ȭ ����
	MeshRenderVector_t::iterator	iter;
	
	// 1. m_Data�� ���� ���� ���� ��ȯ �ϰ�,
	for( iter = m_Data.begin(); iter != m_Data.end(); ++iter ) 
	{
		MeshRender_t&		CurMeshRender = (*iter);
		CurMeshRender.UnInit();
	}
	
	// 2. m_Data ��ȯ
	m_Data.clear();
}
#endif // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER


//////////////////////////////////////////////////////////////////////////
/*
  SpriteManager
*/
//////////////////////////////////////////////////////////////////////////

#ifdef MR0_NEWRENDERING_EFFECTS_SPRITES
namespace SpriteManager
{
	bool				m_bOn = false;			//���� �ִ°�?
	bool				m_bIsDrawing = false;	//���� ����� ���ΰ�? 

	SprContainer		m_Container;

	const unsigned int	c_MaxSprite = 4000;
	unsigned int		m_iNumSpr = 0;
	unsigned int		m_iNumPartition = 5;

	int					m_iBlenderType = 0;

	bool				m_bEnabledTexture = false;
	bool				m_bEnabledCull = false;
	bool				m_bEnabledAlphaTest = false;
	bool				m_bEnabledDepthTest = false;
	bool				m_bEnabledDepthMask = false;
	bool				m_bEnabledFog = false;
	int					m_iCurrentAlphaMode = 0;


	void				InitBlender();
}

void SpriteManager::Init()
{
	m_Container.clear();
	m_iNumSpr = 0;
	
	unsigned int iBlockSize = c_MaxSprite / m_iNumPartition;
	for(unsigned int i = 0; i < m_iNumPartition; ++i)
	{
		m_Container.push_back(SprPartition());
		SprPartition& rPart = m_Container[m_Container.size()-1];
		unsigned int iBlockVertexSize = 0;
		if(i == m_iNumPartition-1)
		{
			//Ȧ�������� �������� ��츦 ���� ������ ���� ���� ����
			iBlockSize = c_MaxSprite - iBlockSize*i;
			iBlockVertexSize = iBlockSize * 4;
		}
		else
		{
			iBlockVertexSize = iBlockSize * 4;
		}

		//���� �����͸� ä���.
		rPart.m_sortData.clear();
		rPart.m_vData.reserve(iBlockVertexSize);
		for(unsigned int j = 0; j < iBlockVertexSize; ++j)
			rPart.m_vData.push_back(SpriteVertex());

		//VBO, IBO����
		glGenBuffersARB(1, &rPart.m_iVBO);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, rPart.m_iVBO);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, iBlockVertexSize * sizeof(SpriteVertex), NULL, GL_STREAM_DRAW_ARB);

		unsigned short* pTmpIndice = new unsigned short[iBlockVertexSize];
		glGenBuffersARB(1, &rPart.m_iIBO);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, rPart.m_iIBO);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, iBlockVertexSize * sizeof(unsigned short), NULL, GL_STREAM_DRAW_ARB);
		delete[] pTmpIndice;
	}
}

void SpriteManager::UnInit()
{
	Clear();
}


//�ؽ���-���ؽ� �� �߰�
bool SpriteManager::RegisterQuad(int iTex, vec3_t vPos, float fWidth, float fHeight, 
		vec3_t vLight, float fRot, 
		float u, float v, float uWidth, float vHeight)
{
	unsigned int i = 0;
	if(m_iNumSpr >= c_MaxSprite) return false;

	unsigned int iBlockSize = c_MaxSprite / m_iNumPartition;
	unsigned int iCurPart = m_iNumSpr / iBlockSize;
	SprPartition& rPart = m_Container[iCurPart];
	unsigned short iNewStartIdx = (m_iNumSpr-iCurPart*iBlockSize)*4;

	vec3_t p1;
	VectorTransform(vPos,CameraMatrix,p1);
	fWidth  *= 0.5f;
	fHeight *= 0.5f;
	
	if(fRot==0)
	{
		rPart.m_vData[iNewStartIdx].x = p1[0]-fWidth;
		rPart.m_vData[iNewStartIdx].y = p1[1]-fHeight;
		rPart.m_vData[iNewStartIdx].z = p1[2];

		rPart.m_vData[iNewStartIdx+1].x = p1[0]+fWidth;
		rPart.m_vData[iNewStartIdx+1].y = p1[1]-fHeight;
		rPart.m_vData[iNewStartIdx+1].z = p1[2];

		rPart.m_vData[iNewStartIdx+2].x = p1[0]+fWidth;
		rPart.m_vData[iNewStartIdx+2].y = p1[1]+fHeight;
		rPart.m_vData[iNewStartIdx+2].z = p1[2];

		rPart.m_vData[iNewStartIdx+3].x = p1[0]-fWidth;
		rPart.m_vData[iNewStartIdx+3].y = p1[1]+fHeight;
		rPart.m_vData[iNewStartIdx+3].z = p1[2];
	}
	else
	{
		vec3_t p[4];
		vec3_t p2[4];
		Vector(-fWidth,-fHeight, p1[2], p2[0]);
		Vector( fWidth,-fHeight, p1[2], p2[1]);
		Vector( fWidth, fHeight, p1[2], p2[2]);
		Vector(-fWidth, fHeight, p1[2], p2[3]);
		vec3_t Angle;
		Vector(0.f,0.f,fRot,Angle);
		float Matrix[3][4];
		AngleMatrix(Angle,Matrix);
		for(i = 0; i < 4; ++i) 
		{
			VectorRotate(p2[i],Matrix,p[i]);
			p[i][0] += p1[0];
			p[i][1] += p1[1];

			rPart.m_vData[iNewStartIdx+i].x = p[i][0];
			rPart.m_vData[iNewStartIdx+i].y = p[i][1];
			rPart.m_vData[iNewStartIdx+i].z = p[i][2];
		}
	}

	//�ؽ�����ǥ ����
	rPart.m_vData[iNewStartIdx].u = u;
	rPart.m_vData[iNewStartIdx].v = v+vHeight;
	rPart.m_vData[iNewStartIdx+1].u = u+uWidth;
	rPart.m_vData[iNewStartIdx+1].v = v+vHeight;
	rPart.m_vData[iNewStartIdx+2].u = u+uWidth;
	rPart.m_vData[iNewStartIdx+2].v = v;
	rPart.m_vData[iNewStartIdx+3].u = u;
	rPart.m_vData[iNewStartIdx+3].v = v;

	//Light����
	for(i = 0; i < 4; ++i)
	{
		rPart.m_vData[iNewStartIdx+i].r = unsigned char(vLight[0] * 255);
		rPart.m_vData[iNewStartIdx+i].g = unsigned char(vLight[1] * 255);
		rPart.m_vData[iNewStartIdx+i].b = unsigned char(vLight[2] * 255);

		if(iTex == BITMAP_BLOOD+1
			|| iTex == BITMAP_FONT_HIT
			|| (Bitmaps[iTex].Components==3)
			)
			rPart.m_vData[iNewStartIdx+i].a = 255;
		else
			rPart.m_vData[iNewStartIdx+i].a = rPart.m_vData[iNewStartIdx+i].r;
	}
	
	//�ؽ��ĸ� ã�´�. 
	SprSortMap_t::iterator iter_sortMap = rPart.m_sortData.find(iTex);
	if(iter_sortMap == rPart.m_sortData.end())
	{
		//������.
		UShortVector nVec;
		IntSortMap_t sortByBlender;
		for(i = 0; i < 4; ++i) nVec.push_back(iNewStartIdx+i);
		sortByBlender.insert(IntSortMap_t::value_type(m_iBlenderType, nVec));
		rPart.m_sortData.insert(SprSortMap_t::value_type(iTex, sortByBlender));
	}
	else
	{
		//����Ÿ���� ã�Ƽ� �μ�Ʈ�Ѵ�.
		IntSortMap_t& sortedIndice = iter_sortMap->second;
		IntSortMap_t::iterator iter_sortBlender = sortedIndice.find(m_iBlenderType);
		if(iter_sortBlender == sortedIndice.end())
		{
			//������ �ִ� ����Ÿ�԰��� ���� ���ο� Ÿ���̴�. 
			UShortVector nVec;
			nVec.push_back(4);
			for(i = 0; i < 4; ++i) nVec.push_back(iNewStartIdx+i);
			sortedIndice.insert(IntSortMap_t::value_type(m_iBlenderType, nVec));
		}
		else
		{
			//������ ����Ÿ�԰� ���� Ÿ���̴�. 
			UShortVector& rVec = iter_sortBlender->second;
			for(i = 0; i < 4; ++i) rVec.push_back(iNewStartIdx+i);
		}
	}
	++m_iNumSpr;
	return true;
}

//Sort���� û���Ѵ�.
void SpriteManager::Clear()
{
	SprContainer::iterator iter_container = m_Container.begin();
	for(; iter_container != m_Container.end(); ++iter_container)
	{
		SprPartition& rPart = *iter_container;
		
		// MR0_MODIFY : stl::map �� m_sortData�ʱ�ȭ�ÿ� ���� stl::vector �ʱ�ȭ �߰�
		// clear ����
		typedef std::map<int, UShortVector> IntSortMap_t;
		typedef std::map<int, IntSortMap_t> SprSortMap_t;
		SprSortMap_t m_sortData;

		SprSortMap_t::iterator	iter_SprSortMap = rPart.m_sortData.begin();
		for( ; iter_SprSortMap != rPart.m_sortData.end() ; ++iter_SprSortMap )
		{
			IntSortMap_t& Cur_mapIntSorMap = ((*iter_SprSortMap).second);
			IntSortMap_t::iterator	iter_IntSortMap = Cur_mapIntSorMap.begin();
			for( ; iter_IntSortMap != Cur_mapIntSorMap.end() ; ++iter_IntSortMap )
			{
				UShortVector& Cur_VectorShort = ((*iter_IntSortMap).second);
				Cur_VectorShort.clear();
			}
			Cur_mapIntSorMap.clear();
		}
		
		rPart.m_sortData.clear();
		rPart.m_vData.clear();
		glDeleteBuffersARB(1, &rPart.m_iVBO);
		glDeleteBuffersARB(1, &rPart.m_iIBO);
		rPart.m_iVBO = rPart.m_iVBO = 0;
	}
	m_Container.clear();
}

void SpriteManager::ClearSub()
{
	SprContainer::iterator iter_container = m_Container.begin();
	for(; iter_container != m_Container.end(); ++iter_container)
	{
		SprPartition& rPart = *iter_container;
		rPart.m_sortData.clear();
	}
}

//Partition ���� �����Ѵ�.
void SpriteManager::SetRenderPartition(unsigned int iNum)
{
	Clear();
	m_iNumPartition = iNum;
	Init();
}

void SpriteManager::SetBlender(int iBlender) { m_iBlenderType = iBlender; }
void SpriteManager::AddBlenderOption(int iBlender){ m_iBlenderType |= iBlender; }
void SpriteManager::DelBlenderOption(int iBlender){ m_iBlenderType -= iBlender; }
void SpriteManager::DoBlendByType(int iBType)
{
	if(iBType&ENABLE_TEXTURE)
	{
		if(!m_bEnabledTexture)
		{
			glEnable(GL_TEXTURE_2D);
			m_bEnabledTexture = true;
		}
	}
	else
	{
		if(m_bEnabledTexture)
		{
			glDisable(GL_TEXTURE_2D);
			m_bEnabledTexture = false;
		}
	}

	if(iBType&ENABLE_ALPHATEST)
	{
		if(!m_bEnabledAlphaTest)
		{
			glEnable(GL_ALPHA_TEST);
			m_bEnabledAlphaTest = true;
		}
	}
	else
	{
		if(m_bEnabledAlphaTest)
		{		
			glDisable(GL_ALPHA_TEST);
			m_bEnabledAlphaTest = false;
		}
	}

	if(iBType&ENABLE_CULL)
	{
		if(!m_bEnabledCull) 
		{
			glEnable(GL_CULL_FACE);
			m_bEnabledCull = true;
		}
	}
	else
	{
		if(m_bEnabledCull)
		{	
			glDisable(GL_CULL_FACE);
			m_bEnabledCull = false;
		}
	}

	if(iBType&ENABLE_DEPTHTEST)
	{
		if(!m_bEnabledDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
			m_bEnabledDepthTest = true;
		}
	}
	else
	{
		if(m_bEnabledDepthTest)
		{
			glDisable(GL_DEPTH_TEST);
			m_bEnabledDepthTest = false;
		}
	}
	
	if(iBType&ENABLE_DEPTHMASK)
	{
		if(!m_bEnabledDepthMask)	
		{
			glDepthMask(true);
			m_bEnabledDepthMask = true;
		}
	}
	else
	{
		if(m_bEnabledDepthMask)	
		{
			glDepthMask(false);
			m_bEnabledDepthMask = false;
		}
	}

	if(iBType&ENABLE_FOG)
	{
		if(!m_bEnabledFog)
		{
			glEnable(GL_FOG);
			m_bEnabledFog = true;
		}
	}
	else
	{
		if(m_bEnabledFog)
		{
			glDisable(GL_FOG);
			m_bEnabledFog = false;
		}
	}

	if(iBType&ENABLE_ALPHAMODE)
	{
		iBType = (iBType&ENABLE_ALPHAMODEMASK);
		if(iBType != m_iCurrentAlphaMode)
		{
			glEnable(GL_BLEND);
			if(iBType&ENABLE_ALPHAMODE1)
			{
				glBlendFunc(GL_ZERO,GL_SRC_COLOR);
			}
			else if(iBType&ENABLE_ALPHAMODE2)
			{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
			else if(iBType&ENABLE_ALPHAMODE3)
			{
				glBlendFunc(GL_ONE,GL_ONE);
			}
			else if(iBType&ENABLE_ALPHAMODE4)
			{
				glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_COLOR);
			}
			else if(iBType&ENABLE_ALPHAMODE5)
			{
				glBlendFunc(GL_ONE_MINUS_SRC_COLOR,GL_ONE);
			}
			else if(iBType&ENABLE_ALPHAMODE6)
			{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
			m_iCurrentAlphaMode = iBType;
		}
	}
	else
	{
		if(m_iCurrentAlphaMode)
		{
			glDisable(GL_BLEND);
			m_iCurrentAlphaMode = 0;	
		}
	}
/*
	switch(iBType)
	{
	case 0:
		DisableAlphaBlend();
		break;
	case 1:
		EnableLightMap();
		break;
	case 2:
		EnableAlphaTest();
		break;
	case 3:
		EnableAlphaBlend();
		break;
	case 4:
		EnableAlphaBlendMinus();
		break;
	case 5:
		EnableAlphaBlend2();
		break;
	case 6:
		EnableAlphaBlend3();
		break;
	}
*/
}

//��Ƽ�Ǻ��� ���δٽ� �׸���.
void SpriteManager::RenderAll()
{
	if(!EngineGate::m_bIsOn) return;
	
	m_bIsDrawing = true;
	unsigned int i,j = 0;
	InitBlender();
	for(i = 0; i < m_iNumPartition; ++i)
	{
		//���� ��������Ʈ ������ ū ������ ���̸� �׸��� �ʴ´�.
		if(i*(c_MaxSprite/m_iNumPartition) > m_iNumSpr) break;
		SprPartition& rPart = m_Container[i];

		//���ؽ� ���۸� �����Ѵ�.
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, rPart.m_iVBO);
		glInterleavedArrays(GL_T2F_C4UB_V3F, 0, NULL);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, rPart.m_vData.size()*sizeof(SpriteVertex), &rPart.m_vData[0]);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, rPart.m_iIBO);

		//sort map�� ��� ���鼭, �ε������ۿ� ���� ����, �׸���.
		SprSortMap_t::iterator iter_sortMap = rPart.m_sortData.begin();
		for(; iter_sortMap != rPart.m_sortData.end(); ++iter_sortMap)
		{
			BindTexture(iter_sortMap->first);
			IntSortMap_t& rSortByBlender = iter_sortMap->second;
			IntSortMap_t::iterator iter_SortByBlender = rSortByBlender.begin();
			for(; iter_SortByBlender != rSortByBlender.end(); ++iter_SortByBlender)
			{
				DoBlendByType(iter_SortByBlender->first);

				//���õ� �ε������ۿ� ���� �������
				UShortVector& rRawIndice = iter_SortByBlender->second;
				glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0, rRawIndice.size()*sizeof(unsigned short), &rRawIndice[0]);
				glDrawRangeElements(GL_QUADS, 0, rRawIndice.size()-1, rRawIndice.size(), GL_UNSIGNED_SHORT, NULL);
				
				rRawIndice.resize(0);
			}
		}
	}

	//���� �� �׷����� ��������Ʈ ������ �ʱ�ȭ���ش�.
	m_iNumSpr = 0;
	m_bIsDrawing = false;
}

void SpriteManager::InitBlender()
{
	m_iCurrentAlphaMode = 0;
	m_bEnabledTexture = true;
	m_bEnabledCull = true;
	m_bEnabledAlphaTest = false;
	m_bEnabledDepthTest = true;
	m_bEnabledDepthMask = true;
	m_bEnabledFog = FogEnable;
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
}

void SpriteManager::Toggle(bool b)
{
	m_bOn = b;
}

bool SpriteManager::IsOn()
{
	return m_bOn;
}

bool SpriteManager::IsPreDraw()
{
	return !m_bIsDrawing;
}

bool SpriteManager::IsWorking()
{
	return (m_bOn && !m_bIsDrawing);
}

#endif // MR0_NEWRENDERING_EFFECTS_SPRITES

#endif //MR0