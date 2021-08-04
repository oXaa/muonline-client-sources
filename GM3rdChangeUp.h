// GM3rdChangeUp.h: interface for the CGM3rdChangeUp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GM3RDCHANGEUP_H__09F84DB0_6262_425E_98B4_7EB06EA595CC__INCLUDED_)
#define AFX_GM3RDCHANGEUP_H__09F84DB0_6262_425E_98B4_7EB06EA595CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BMD;

namespace SEASON3A
{
	class CGM3rdChangeUp  
	{
	protected:
		bool m_nDarkElfAppearance;	// ��ũ���� ����.

	protected:
		CGM3rdChangeUp();

	public:
		virtual ~CGM3rdChangeUp();

		static CGM3rdChangeUp& Instance();

		bool IsBalgasBarrackMap();
		bool IsBalgasRefugeMap();

		// ������Ʈ ����
		bool CreateBalgasBarrackObject(OBJECT* pObject);
		bool CreateBalgasRefugeObject(OBJECT* pObject);
		bool MoveObject(OBJECT* pObject);
		bool RenderObjectVisual(OBJECT* pObject, BMD* pModel);
		bool RenderObjectMesh(OBJECT* o, BMD* b, bool ExtraMon = 0);	// ������Ʈ ����(���� ����)
		void RenderAfterObjectMesh(OBJECT* o, BMD* b);				// ������ ������Ʈ ���� ����.

		// ������Ʈ ����
		bool CreateFireSnuff( PARTICLE* o );
		void PlayEffectSound(OBJECT* o);
		void PlayBGM();

		// ���� ����
		CHARACTER* CreateBalgasBarrackMonster(int iType, int PosX, int PosY, int Key);	// ���� ����
		bool SetCurrentActionBalgasBarrackMonster(CHARACTER* c, OBJECT* o);		// ���� ���� �׼� ����
		bool AttackEffectBalgasBarrackMonster(CHARACTER* c, OBJECT* o, BMD* b);	// ���� ���� ����Ʈ
		bool MoveBalgasBarrackMonsterVisual(CHARACTER* c,OBJECT* o, BMD* b);	// ���� ȿ�� ������Ʈ
		void MoveBalgasBarrackBlurEffect(CHARACTER* c, OBJECT* o, BMD* b);		// ���� ������ �ܻ� ó��
		bool RenderMonsterObjectMesh(OBJECT* o, BMD* b,int ExtraMon);	// ���� ������Ʈ ������
		bool RenderBalgasBarrackMonsterVisual(CHARACTER* c, OBJECT* o, BMD* b);	// ���� ȿ�� ������
	};
}

#endif // !defined(AFX_GM3RDCHANGEUP_H__09F84DB0_6262_425E_98B4_7EB06EA595CC__INCLUDED_)
