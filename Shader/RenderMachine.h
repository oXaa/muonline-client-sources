#ifndef __RENDER_MACHINE_H__
#define __RENDER_MACHINE_H__

//////////////////////////////////////////////////////////////////////////
// 
// RenderMachine.h : ���̴� Ÿ�Ժ� ������ �ӽ� ���� (VertexShaderRenderer, Pixel Shader Renderer)
//
//////////////////////////////////////////////////////////////////////////

#ifdef MR0

#include "ModelManager.h"
#include "VPManager.h"

using namespace ModelManager;

class BMD;

//////////////////////////////////////////////////////////////////////////
// Immediate Mode�� ���� Render Mesh ����
//////////////////////////////////////////////////////////////////////////
class CRenderMachine
{
public:
	typedef enum _RENDERER_TYPE
	{
		TYPE_RDT_IMMEDIATE = 0,		//����
		TYPE_RDT_VBO,				//VBO�� ���
		TYPE_RDT_VBOVS,				//VBO�� ���ؽ� ���̴� ����
		TYPE_RDT_VBOVSPS,			//VBO�� ���ؽ�/�Ƚ����̴� ���ʴ� ���

		TYPE_RDT_ALL
	}RENDERER_TYPE;

	typedef enum _RENDERER_SUBTYPE
	{
		TYPE_RDST_IMMEDIATE = 0,	//���ۿ� �ִ� �༮���� ��� �׸���.
		TYPE_RDST_BATCH,			//���� �������� ���� ���� �״´�.
		TYPE_RDST_ALL

	}RENDERER_SUBTYPE;

	RENDERER_TYPE		m_eType;
	RENDERER_SUBTYPE	m_eSubType;

	virtual void Render(ModelManager::MeshRender_t&) = 0;		// ���� �޽� ��ü�� ���� ������ ��û.
	virtual void Transform(BMD*, float (*BoneMatrix)[3][4]) = 0;

	//��ƿ��Ƽ �Լ�
	bool IsBatchRenderer() { return (m_eSubType == TYPE_RDST_BATCH); }
	bool IsUsePixelShader() { return (m_eType >= TYPE_RDT_VBOVSPS); }
};

extern CRenderMachine*	g_Renderer;

//////////////////////////////////////////////////////////////////////////
// ���� �ӽ� : ���ؽ� ���̴� ����
//////////////////////////////////////////////////////////////////////////
class CVBOShaderMachine : public CRenderMachine
{
private:
	float*			m_pMat;

public:
	CVBOShaderMachine() : m_pMat(NULL) {m_eType = TYPE_RDT_VBOVS; m_eSubType = TYPE_RDST_IMMEDIATE;}
	~CVBOShaderMachine() { }

	void Render(ModelManager::MeshRender_t&);
	void Transform(BMD* m, float (*BoneMatrix)[3][4]);
};


//////////////////////////////////////////////////////////////////////////
// ���� �ӽ� : �ȼ� ���̴� ����
//////////////////////////////////////////////////////////////////////////
class CVBOPixelShaderMachine : public CRenderMachine
{
private:

public:
	CVBOPixelShaderMachine() {m_eType = TYPE_RDT_VBOVSPS; m_eSubType = TYPE_RDST_BATCH;}
	~CVBOPixelShaderMachine() { }

	void Render(ModelManager::MeshRender_t&) {}
	void Transform(BMD* m, float (*BoneMatrix)[3][4]) { return; }
};

//////////////////////////////////////////////////////////////////////////
// ���� �ӽ� : ���� �̻��
//////////////////////////////////////////////////////////////////////////
class CVBOMachine : public CRenderMachine
{
public:
	CVBOMachine() {m_eType = TYPE_RDT_VBO; m_eSubType = TYPE_RDST_IMMEDIATE;}

	virtual void Render(ModelManager::MeshRender_t&);
	virtual void Transform(BMD* m, float (*BoneMatrix)[3][4]);
};

//////////////////////////////////////////////////////////////////////////
// ���� �ӽ� : Original ( ���� ��� ȣȯ )
//////////////////////////////////////////////////////////////////////////
class COriginMachine : public CRenderMachine
{
public:
	COriginMachine() {m_eType = TYPE_RDT_IMMEDIATE; m_eSubType = TYPE_RDST_IMMEDIATE;}
	~COriginMachine() { }	

	virtual void Render(ModelManager::MeshRender_t&);
	virtual void Transform(BMD* m, float (*BoneMatrix)[3][4]);
};

#endif // MR0

#endif //__RENDER_MACHINE_H__