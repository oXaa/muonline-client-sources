// w_ModelView.h: interface for the ModelView class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_UISYSTEM

#if !defined(AFX_W_MODELVIEW_H__5EA1C31A_E431_4AD0_B198_5AA69BE70661__INCLUDED_)
#define AFX_W_MODELVIEW_H__5EA1C31A_E431_4AD0_B198_5AA69BE70661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "w_ImageUnit.h"
#include "w_UIWnd.h"

/*
// �� ����� �̸��� �ʿ��ϴ�.( id��� ���� ���� ) 
ui::ModelViewPtr shoppreviewmodel( new ui::ModelView( "shoppreviewmodel" ) );
// �����( �ڱ� �ڽ� )�� ��� ī�� �Ѵ�.
shoppreviewmodel->CopyPlayer();
// ��ǥ ( �θ��� ��� ��ǥ )
shoppreviewmodel->Move( Coord( 0, 0 ) );
// �׸� ���� ũ��
shoppreviewmodel->Resize( Dim( 170, 198 ) );
// �θ� ���̱�
previewPanel->AddChild( shoppreviewmodel );
*/

namespace ui
{
	BoostSmartPointer( ModelView );
	class ModelView : public UIWnd 
	{
	public:
		ModelView( const string& name );
		virtual ~ModelView();

	public:
		void SetAngle( const float angle );
		void SetZoom( const float zoom );
		void CopyPlayer();

		void SetClass( BYTE byClass );
		const bool SetEquipmentItem( const CASHSHOP_ITEMLIST& eqitem );

	protected:
		virtual void DrawViewPortMesh();
		virtual void Process( int delta );

	protected:
		virtual void OnMove( const Coord& prevPos );
		virtual void OnResize( const Dim& prevSize );
		virtual void OnMouseOver();
		virtual void OnMouseOut();
		virtual void OnLButtonDown();
		virtual void OnLButtonUp();
		virtual void OnLButtonDBClk();
		virtual void OnWheelScroll( int delta );
		virtual void OnMouseMove( const Coord& coord );

	private:
		void SetAnimation( int iAnimationType );
		int SetPhotoPose(int iCurrentAni, int iMoveDir = 0);
		void Initialize();
		void Destroy();

	private:
		bool		m_MouseDowned;
		float		m_Zoom;
		float       m_Angle;
        Coord		m_PrevMousePos;

		BOOL m_bIsInitialized;

		int m_iShowType;
		int m_iCurrentAnimation;	// ���� �ൿ
		int m_iSettingAnimation;	// ������ �ൿ
		int m_iCurrentFrame;		// ���� ������
	};

	inline
	void ModelView::SetAngle( const float angle )
	{
		m_Angle -= angle;
	}

	inline
	void ModelView::SetZoom( const float zoom )
	{
		m_Zoom += zoom;
	}
};

#endif // !defined(AFX_W_MODELVIEW_H__5EA1C31A_E431_4AD0_B198_5AA69BE70661__INCLUDED_)

#endif //NEW_USER_INTERFACE_UISYSTEM