#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

//////////////////////////////////////////////////////////////////////////
// 
// ModelManager.h : �޽� �����̳�, ���̴� �޴���, BMD���� VBOMESH��ȯ ��� ����.
//
//////////////////////////////////////////////////////////////////////////

#include "GLUtils.h"
#include "StlDefinition.h"

unsigned int		GenID();		//���� �� ��ҵ鿡 ���� ID�Լ�

///////////////////////////////////////////////////////////////////////////////////////////
// Post Effect : ��Ȥ BMD::Open2 ���� Exporting �� �޽��� ���ǵ� Post Effect �� ó��.
///////////////////////////////////////////////////////////////////////////////////////////
typedef struct _EffectScrip
{
	unsigned int	m_tShader;		//����Ʈ ���̴� ����
	int				m_iTex;			//�ؽ��İ�
	float			m_fAlpha;		//�޽��� ���İ� (����ä���� �ִ� ��츸 )
	vec3_t			m_vColor3f;		//�޽� BodyLight�� �������� ����
	char			m_strTexName[MAX_PATH];

	_EffectScrip() : m_tShader(0), m_iTex(0), m_fAlpha(0.f) 
	{
		Vector(0.f,0.f,0.f, m_vColor3f);
		strcpy(m_strTexName, "");
	}
	_EffectScrip(int iShader, int iTex, float fAlpha, vec3_t vColor3f) :
		m_tShader(iShader), m_iTex(iTex), m_fAlpha(fAlpha)
	{
		VectorCopy(vColor3f, m_vColor3f);
		strcpy(m_strTexName, "");
	}
	_EffectScrip(const _EffectScrip& r)
	{
		m_tShader = r.m_tShader;
		m_iTex = r.m_iTex;
		m_fAlpha = r.m_fAlpha;
		VectorCopy(r.m_vColor3f, m_vColor3f);
		strcpy(m_strTexName, r.m_strTexName);
	}
	_EffectScrip& operator=(const _EffectScrip& r)
	{
		m_tShader = r.m_tShader;
		m_iTex = r.m_iTex;
		m_fAlpha = r.m_fAlpha;
		VectorCopy(r.m_vColor3f, m_vColor3f);
		strcpy(m_strTexName, r.m_strTexName);
		return *this;
	}
} EffectScrip_t;
typedef std::vector<EffectScrip_t> EffectScripVec_t;

///////////////////////////////////////////////////////////////////////////////////////////
// �� Ÿ��. ���̴� ���������� ���Ǵ� Vertex ��ü�� ����. BMD���� VBOMesh�� ��ȯ �Լ� ����. 
///////////////////////////////////////////////////////////////////////////////////////////
namespace ModelManager
{
	typedef struct _nv2
	{
		float x, y;
		_nv2() : x(0.f), y(0.f) {}
	}nv2;

	typedef struct _nv3
	{
		float x, y, z;
		_nv3() : x(0.f), y(0.f), z(0.f) {}
	}nv3;

	typedef struct _nv4
	{
		float x, y, z, w;
		_nv4() : x(0.f), y(0.f), z(0.f), w(0.f){}
	}nv4;

	typedef struct _nv34
	{
		nv4	l1, l2, l3;
		_nv34() {}
		_nv34(float (*Matrix)[4]){
			memcpy(&l1.x, Matrix, sizeof(float) * 12);
		}
		_nv34(const float* v){
			memcpy(&l1.x, v, sizeof(float) * 12);
		}
	}nv34;

	typedef struct _nv44
	{
		nv4	l1, l2, l3, l4;
		_nv44() {}
		_nv44(float (*Matrix)[4]){
			memcpy(&l1.x, Matrix, sizeof(float) * 16);
		}
		_nv44(const float* v){
			memcpy(&l1.x, v, sizeof(float) * 16);
		}
	}nv44;

	typedef std::vector<nv34> MatrixVector;
	typedef std::vector<nv4> Vector4Vec;
	typedef std::vector<nv3> Vector3Vec;
	typedef std::vector<nv2> Vector2Vec;

	void				Init();			// �޽� �ӽ��� �ʱ�ȭ �մϴ�.
	void				UnInit();		// �޽� �ӽ��� �޸𸮹�ȯ �մϴ�.

#ifdef LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
										// BMD���� ���� �޽��� VBO�޽��� ��ȯ �մϴ�. ID���� �� Upload����
	void				Convert(unsigned int iModel, bool bDelOldMesh = true, bool bValidationCheckForDebug = false);	
#else // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
	void				Convert(unsigned int iModel, bool bDelOldMesh = true);		
#endif // LDS_MR0_FORDEBUG_VERIFYCONVERTMESH
										// �� �����Ϳ� �Լ� - ��� �޽��� �⺻ ����Ʈ (�ؽ��� ) �� ���մϴ�.
	void				AttachDefaultEffect(unsigned int iModel);
										// �� �����Ϳ� �Լ� - �޽��� ����Ʈ (�ؽ��� )������ �����ɴϴ�.			
	unsigned int		GetEffectCount(unsigned int ModelID, unsigned int MeshID);	
										
										// ��(BMD Models[MAX_MODEL])�� �ϳ���ü�� �̸��� ���� �մϴ�. 
	void				SetModelName(unsigned int i, const std::string& n);			

										// ��(BMD Models[MAX_MODEL])�� �ϳ���ü�� ���ϸ��̼� ������ �����ɴϴ�.
	int					GetActionCount(unsigned int i);	

										// ��(BMD Models[MAX_MODEL])�� �ϳ���ü�� �޽� ������ �����ɴϴ�.
	int					GetMeshCount(unsigned int i);

										// ��(BMD Models[MAX_MODEL])�� �ϳ���ü�� ������ �����ɴϴ�.
	char				GetModelVersion(unsigned int i);							
} // namespace ModelManager

///////////////////////////////////////////////////////////////////////////////////////////
// Immediate Mesh ������ ���� (���� ������Ʈ��, ���� �ӽ�) (���⼭ Immediate Mesh�� ���� ������ �޽� �ν��Ͻ��� ��Ī)
///////////////////////////////////////////////////////////////////////////////////////////
class BMD;
class CRenderMachine;
namespace ModelManager
{
	// �ϳ��� �޽� ������ ����. (���� �ؽ��ķ� �������� �������� �޽��� ����.)
	typedef struct _MeshRender_t
	{
		BMD*		m_pSourceBMD;		// Immediate Render�޽��� �����ϴ� ���� ��.
		int			m_iMesh;			// Immediate Render�޽��� �ε��� ��ȣ.
		int			m_iTex;				// Immediate Render�޽��� Texture ��ȣ.
		int			m_iFlag;			// Texture���� �ο��� RenderState ����. RENDERBRIGHT�� ����. (ex. rNew.m_iFlag&RENDER_BRIGHT )
		int			m_iNumConst;		// Immediate ��Ȳ�� ���� Shader���� �ѱ� Parameter Index (ex. Local Parameter Index �Ǵ� Environment Parameter Index�� ������ ���̴����� ���� ���ڴ� ���̴� ��ũ��Ʈ�� �̸� ���ǵ� �Ķ������ �ε����� ���߾�� �մϴ�.)
		bool		m_bUseFixedVP;		// Immediate ��Ȳ�� ���� �޽��� Ư���� ���̴��� �̿��� ������ ����. (���� Ư���� ���̴��� ShadowMap�� �̿��� �Ǳ׸��� ȿ�� �Դϴ�.)
		bool		m_bLight;			// Immediate ��Ȳ�� ���� �޽��� ��ȿ�� ����.
		int			m_iVProgram;		// ���� ���õ� ���ؽ� ���μ���. (ex. ������ ��������, ���ؽ� ������ �������� ��.)
		int			m_iPProgram;		// ���� ���õ� �ȼ� ���μ���. m_iVProgram�� �����ϸ�, ���� ���� ���.
		float		m_fAlpha;			// Immediate ��Ȳ�� ���� �޽��� ���� ��.
		nv3			m_vColor;			// Immediate ��Ȳ�� ���� �޽��� Color ��.
		Vector4Vec	m_matConstants;		// ���̴��� �ѱ� ��� �Ķ���� ����.
										// 1. 
										// 1. Local+World+View Mat (Vec4*3 STL::Vector) : ���� Animation�� ���� Matrix�� ���̴����� ���ؽ����� ���ϵ��� ��û.

#ifdef LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
public:
		void UnInit()
		{
			m_matConstants.clear();		// Shader Parameter Table �ʱ�ȭ.
		}
#endif // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER

public:	
		_MeshRender_t()
		{
			m_pSourceBMD = NULL;
			m_iMesh = m_iTex = m_iFlag = -1;
			m_iNumConst = 0;
			m_bUseFixedVP = false;
			m_bLight = false;
			m_iVProgram = m_iPProgram = -1;
			m_fAlpha = 1.f;
			m_vColor.x = m_vColor.y = m_vColor.z = 1.f;
			m_matConstants.reserve(10);					// ���̴����� �Ѱ��� �Ķ���� ���̺��� 10�� �����صӴϴ�.
		}
	}MeshRender_t;
	typedef std::vector<MeshRender_t> MeshRenderVector_t;

///////////////////////////////////////////////////////////////////////////////////////////
// Immediate Mode�� �׸� ��� RenderMesh �޴��� Ŭ����.
///////////////////////////////////////////////////////////////////////////////////////////
	class CMeshMachine
	{
	private:
		MeshRenderVector_t	m_Data;					// MeshRender_t ���� �޽� �����̳�
		bool				m_bLock;				// ���� �׷��� �ܰ踦 Locking.
		bool				m_bOn;					// ���� �޴��� �ӽ��� ON OFF ����.
		bool				m_bTransop;				// Transform�Լ� �ܰ迡�� BodyOrigin�ݿ� ����.
		vec3_t				m_vLightPosOrg;			// ���� ���� ���� Light��ǥ.
		vec3_t				m_vLightDirOrg;			// ���� ���� ���� Light����.
		vec3_t				m_vLightPos;			// ��ü���� ����� Light ��ġ.
		vec3_t				m_vLightDir;			// ��ü���� ����� Light ����.
		
		CMeshMachine(const CMeshMachine& );
		CMeshMachine& operator=(const CMeshMachine& );

		bool IsAlphaNoUseType(int iType);			// ���������Ʈ,ũ��3,4,5,7�ǰ��� ���� �̻��.

													// ���̴� �Ķ���� ���� ���̺� mat 1~10 ����.
		void MakeConst(int iTexType, int iLightType, bool bAlphaNoUse,	
			float BlendMeshTexCoordU, float BlendMeshTexCoordV, MeshRender_t& r);	

	public:
		CMeshMachine();
		~CMeshMachine();

		void ProcessLight(bool bHighLight = false, bool bBattleCastle = false);		// ������ ���� ������ ����. (���� �ϵ��ڵ� ����)
		inline bool bEnabled() { return m_bOn; }									// ���� �޴��� �ӽ� ��뿩��.
		inline void Toggle(bool b) { m_bOn = b; }									// ���� �޴��� �ӽ� ��뿩�� ����.
		inline void Lock(bool b) { m_bLock = b; }									// ���� �޴��� �׷����� ������ Locking��� �̳� ����� Ư���� ����� ����.
		inline void	SetTransOp(bool b) { m_bTransop = b; }							// Transform������ ���̴� ����, CPU���� ���� ����. 
		inline bool GetTransOp() { return m_bTransop;}								// ��ȯ :         " 
		inline void SetLightPos(vec3_t vPos, vec3_t vDir) { VectorCopy(vPos, m_vLightPos); VectorCopy(vDir, m_vLightDir); }	// ����Ʈ ��ġ�� ���� �����̳� ���� �̻��.
		void AddRender(BMD* pSource, int i,int RenderFlag,
						float Alpha,int BlendMesh, float BlendMeshLight,			// �׷��� �޽��� ���� �޴��� �ӽ� �����̳ʿ� �߰�.
						float BlendMeshTexCoordU,float BlendMeshTexCoordV,int MeshTexture);	
		void Flush();																// �޽��� ������ GPU�� �Ѱ� ������ ��û.
#ifdef LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
		void UnInit();
#endif // LDS_MR0_ADD_WHENSHUTDOWN_UNINIT_MODELMANAGER
	};	
} // namespace ModelManager


//////////////////////////////////////////////////////////////////////////
// ������ �޴��� �ӽ� �۷ι� ���� ��ü
//////////////////////////////////////////////////////////////////////////
extern ModelManager::CMeshMachine* g_pMeshMachine;									

//////////////////////////////////////////////////////////////////////////

#ifdef MR0_NEWRENDERING_EFFECTS_SPRITES
//////////////////////////////////////////////////////////////////////////
// Sprite Sorting �ؼ� �׸��� �Լ�
//////////////////////////////////////////////////////////////////////////
namespace SpriteManager
{
	typedef struct _SpriteV
	{
		float u,v;
		unsigned char r,g,b,a;
		float x,y,z;
		
		_SpriteV() : u(0.f), v(0.f), 
			r(255), g(255), b(255), a(255), 
			x(0.f), y(0.f), z(0.f) {}
	}SpriteVertex;

	//��������Ʈ ��������� �ɼǵ�
	enum RenderEnvEnum_t
	{
		ENABLE_TEXTURE =	0x00000001,
		ENABLE_ALPHATEST =	0x00000002,
		ENABLE_CULL =		0x00000004,
		ENABLE_DEPTHTEST =	0x00000008,
		ENABLE_DEPTHMASK =	0x00000010,
		ENABLE_FOG =		0x00000020,
		ENABLE_ALPHAMODE =	0x00000080,

		ENABLE_ALPHAMODE1 =	0x00000100,
		ENABLE_ALPHAMODE2 =	0x00000200,
		ENABLE_ALPHAMODE3 =	0x00000400,
		ENABLE_ALPHAMODE4 =	0x00000800,
		ENABLE_ALPHAMODE5 =	0x00001000,
		ENABLE_ALPHAMODE6 =	0x00002000,

		ENABLE_ALPHAMODEMASK = 0xFFFFFF00,
	};

	//������ ����
	typedef std::vector<SpriteVertex> SprVertexData_t;
	
	//���� �� (������ - �ε�������)
	typedef std::map<int, UShortVector> IntSortMap_t;

	//���� ��(�ؽ��� - ����Ÿ�� - �ε���)
	typedef std::map<int, IntSortMap_t> SprSortMap_t;

	//��������Ʈ �����̳� Ÿ��
	typedef struct _SprPartition
	{
		SprVertexData_t m_vData;
		SprSortMap_t m_sortData;

		unsigned int m_iVBO;
		unsigned int m_iIBO;

		_SprPartition() { m_iIBO = 0; m_iVBO = 0;}
	}SprPartition;

	typedef std::vector<SprPartition>  SprContainer;

	//��������Ʈ �ý��� �ʱ�ȭ
	void Init();

	//��������Ʈ �ý��� ����
	void UnInit();

	//��������Ʈ �ý��ۿ� ���� ��������Ʈ�� ����� ���ΰ�?
	void Toggle(bool);

	//���� ��������Ʈ �ý����� ���� �ִ°�?
	bool IsOn();

	//�ؽ���-���ؽ� �� �߰�
	bool RegisterQuad(int itex, vec3_t vPos, float fWidth, float fHeight, 
		vec3_t vLight, float fRot, 
		float u, float v, float uWidth, float vHeight);

	//�����̳� �ʱ�ȭ
	void Clear();

	//���������� ���ߴٴ��� ���� �� ȣ��
	void ClearSub();

	//Partition ���� �����Ѵ�.
	void SetRenderPartition(unsigned int);
	
	//���� ����
	void SetBlender(int);
	void AddBlenderOption(int);
	void DelBlenderOption(int);

	//��������Ʈ ������ ���ΰ�?
	bool IsPreDraw();

	//��������Ʈ �״� ���̴�.
	bool IsWorking();

	//���� Ÿ�Ժ��� ���� ����
	void DoBlendByType(int);

	//��Ƽ�Ǻ��� ���δٽ� �׸���.
	void RenderAll();
}
#endif // MR0_NEWRENDERING_EFFECTS_SPRITES


#endif //__MODEL_MANAGER_H__