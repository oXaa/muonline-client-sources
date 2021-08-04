// w_CustomRadioButton.h: interface for the CustomRadioButton class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_UISYSTEM

#if !defined(AFX_W_CUSTOMRADIOBUTTON_H__D500FC92_128D_4EA7_BB1F_A132873BA2E1__INCLUDED_)
#define AFX_W_CUSTOMRADIOBUTTON_H__D500FC92_128D_4EA7_BB1F_A132873BA2E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "w_RadioButton.h"
#include "w_ImageUnit.h"
#include "w_UIWnd.h"

/*
  // �׷����� ���� ����
  ui::RadioButton::GroupPtr groupRadioButton( new ui::RadioButton::Group );

  for( int i = 0; i < 3; ++i ) 
  {
	// ���� �Ҷ� radioButton �̸��� �ʿ� �ϴ�.
	CustomRadioButtonPtr radioButton( new CustomRadioButton( ( format( "radioButton%1%" ) % i ).str() ) );
	// �׸� �̹��� �ε����� �־� ��� �Ѵ�.
	// �׸��� ������ �̹����� �ʿ�� �Ѵ�.
	radioButton->SetImageIndex( BITMAP_NEWUI_SHOP_SUBBACKPANEL+5 );
	// ��ǥ ( �θ��� ��� ��ǥ )
	radioButton->Move( ( frame->GetSize() / 2 ) - ( Coord( 800, 600 ) / 2 ) + shopleftbackpanelpos[i] );
	// �׸� �̹����� ũ��
	radioButton->Resize( Dim( 10, 10 ) );
	// �׷쿡 ��� �ϱ�
	radioButton->RegisterGroup( groupRadioButton, radioButton );
	// �θ� ���̱�
	shopframpanel->AddChild( radioButton );

     // �׷쿡 ��� �� ��ư�� ����� Ȱ��ȭ �Ҳ��� �̴�
	 if( i == 0 ) {
		radioButton->BasicChangeFrame();
	 }
  }
*/

namespace ui
{
	BoostSmartPointer( CustomRadioButton );
	class CustomRadioButton : public RadioButton
	{
	public:
		enum RadioButtonState
		{ 
			eRadioButton_Up,
			eRadioButton_Down,

			eRadioButton_StateCount
		};

	public:
		CustomRadioButton( const string& name );
		virtual ~CustomRadioButton(void);

		void MakeImage( const int bitmapindex );
		void SetImageIndex( const int bitmapindex );
		void SetRadioButtonName( const string& buttonname, const Coord& pos, BYTE type );
		
		void BasicChangeFrame();
		void UpChangeFrame();

	protected:
		virtual void DrawImage();
		virtual void OnMove( const Coord& pos );
		virtual void OnResize( const Dim& dim );

		virtual void OnSelect();
		virtual void OnDeselect();

		virtual void OnMouseOver();
		virtual void OnMouseOut();

	private:
		void Initialize();
		void Destroy();
		void ChangeFrame( int index );

	private:
		struct RadioButtonImage 
		{
			image::ImageUnitPtr				s_Image;

			RadioButtonImage()
			{ 
				s_Image = image::ImageUnit::Make(); 
			}

			~RadioButtonImage()
			{
				if( s_Image ) s_Image.reset(); 
			}

			void SetImageIndex( const int bitmapindex )
			{
				if( s_Image ) s_Image->SetImageIndex( bitmapindex );
			}

			void SetPosition( const Coord& pos )
			{
				if( s_Image ) s_Image->SetPosition( pos );
			}
			
			void SetSize( const Dim& size )
			{
				if( s_Image ) s_Image->SetSize( size );
			}

			void SetDraw( bool isdraw )
			{
				if( s_Image ) s_Image->SetDraw( isdraw );
			}
			
			const Dim& GetSize()
			{
				assert(s_Image);
				return s_Image->GetSize();
			}

			void Draw()
			{
				if( s_Image ) s_Image->Draw();
			}
		};

	private:
		vector< BoostSmart_Ptr(RadioButtonImage) >	m_RadioButtonImage;
	};

};

#endif // !defined(AFX_W_CUSTOMRADIOBUTTON_H__D500FC92_128D_4EA7_BB1F_A132873BA2E1__INCLUDED_)

#endif //NEW_USER_INTERFACE_UISYSTEM
