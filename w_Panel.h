// w_Panel.h: interface for the Panel class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_UISYSTEM

#if !defined(AFX_W_PANEL_H__D0B291FA_8F36_4163_B02C_54BE645826E6__INCLUDED_)
#define AFX_W_PANEL_H__D0B291FA_8F36_4163_B02C_54BE645826E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "w_ImageUnit.h"
#include "w_UIWnd.h"

/*

// ToolTip�� ���� �׸� ���� ������� ����� �ִ�

// panel�� �̸��� �ʿ� �ϴ�.
ui::PanelPtr previewPanel( new ui::Panel("previewPanel") );
// panel�� ����, ����, ���, �Ķ� �� ���� ���� �� �ִ� ( ���� ��� �� ���̰� �ϰ� ������ ������ ��ġ�� ���� ���� �ϸ� �ȴ� )
previewPanel->SetColor( 0xff2C2C30 );
// Panel�� ���ĸ� ���� �Ѵ�. ( 1.0f ~ 0.0f )
previewPanel->ChangeOpacityByPercent( 0.0f );
previewPanel->Move( Coord( 17, 18 ) );
previewPanel->Resize( Dim( 170, 198 ) );
shoprightFrame.AddChild( previewPanel );
*/

namespace ui
{
	BoostSmartPointer( Panel );
	class Panel : public UIWnd
	{
		public:
			Panel( const string& name );
			virtual ~Panel(void);
			void    SetColor( const Color& color );

		protected:
			virtual void    DrawImage();
			virtual void    OnChangeOpacity( BYTE prevOp );

			virtual void	OnMove( const Coord& prevPos );
			virtual void	OnResize( const Dim& prevSize );
			
		private:
			void Initialize();
			void Destroy();

		private:
			Color							m_Color;
			image::ImageUnitPtr				m_Image;
	};
};

#endif // !defined(AFX_W_PANEL_H__D0B291FA_8F36_4163_B02C_54BE645826E6__INCLUDED_)

#endif //NEW_USER_INTERFACE_UISYSTEM
