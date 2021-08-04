// w_CompositedPanel.h: interface for the CompositedPanel class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_UISYSTEM

#if !defined(AFX_W_COMPOSITEDPANEL_H__48C4D2EA_FFE8_4CCD_A0AA_A493383B8F15__INCLUDED_)
#define AFX_W_COMPOSITEDPANEL_H__48C4D2EA_FFE8_4CCD_A0AA_A493383B8F15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "w_ImageUnit.h"
#include "w_UIWnd.h"

//Make�� ������ ����.
//��ũ�� �ٵ� ���� �̿��ؼ� ���鵵�� �غ���.
/*
    // ���� �Ҷ� Panel �̸�, Panel Ÿ�� �ΰ��� ���ڰ� �ʿ� �ϴ�.
	ui::CompositedPanelPtr shopsubbackpanel( new ui::CompositedPanel( ( format( "shopsubbackpanel%1%" ) % i ).str(), ui::ePanel_Piece_One ) );
	// ���̵� �ֱ�
	shopsubbackpanel->SetID(10);
	// �׸� �̹��� �ε����� �־� ��� �Ѵ�.
	shopsubbackpanel->SetImageIndex( BITMAP_NEWUI_SHOP_SUBBACKPANEL+5 );
	// ��ǥ ( �θ��� ��� ��ǥ )
	shopsubbackpanel->Move( ( frame->GetSize() / 2 ) - ( Coord( 800, 600 ) / 2 ) + shopleftbackpanelpos[i] );
	// �׸� �̹����� ũ��
	shopsubbackpanel->Resize( shopleftbackpanelsize[i] );
    // ��ǲ �̺�Ʈ�� ��� �� �� �ִ�. handler�� ShopRightModule this ������ �̴�.
	shopsubbackpanel->RegisterHandler( ui::eEvent_LButtonClick, handler, &ShopRightModule::OnExitClk );
	// �׸��� ��ġ
	shopsubbackpanel->SetUVRect( Rect( 0, 0, 203, 256 ) );
	// �θ� ���̱�
	shopframpanel->AddChild( shopsubbackpanel );
*/

namespace ui
{
	BoostSmartPointer( CompositedPanel );
	class CompositedPanel : public UIWnd
	{
	public:
/*             ePieceFullType
    	 _____________________________
		|         |         |         |	
		|   Top   |   Top   |   Top   |
		|   left  |  Center |  Right  |
		|         |         |         |
		|_________|_________|_________|
		|         |         |         |
		|  Middle |  Middle | Middle  |
        |   left  |  Center |  Right  |
		|         |         |         |
		|_________|_________|_________|
		|         |         |         |
		| Bottom  |  Bottom | Bottom  |
	    |   left  |  Center |  Right  |
		|         |         |         |
		|_________|_________|_________|

  9���� ���� ũ�� �̹����� ū �̹����� �Ѹ���.
  Center���� ��� �̹����� ���� �ؼ� �׷�����.
  �뵵�� ��� ȭ�� ���� ū �̹���

*/
		enum ePieceFullType
		{
			//top
			ePiece_TopLeft,         //���� ����
			ePiece_TopCenter,       //���� �߰�
			ePiece_TopRight,        //���� ������
			//middle
			ePiece_MiddleLeft,      //�߰� ����
			ePiece_MiddleCenter,    //�߰� �߰�
			ePiece_MiddleRight,     //�߰� ������
			//bottom
			ePiece_BottomLeft,      //���� ����
			ePiece_BottomCenter,    //���� �߰�
			ePiece_BottomRight,     //���� ������
			//count
			ePieceTypeCount,
		};

/*             ePieceWhThree
    	 _____________________________
		|         |         |         |	
		|   Top   |   Top   |   Top   |
		|   left  |  Center |  Right  |
		|         |         |         |
		|_________|_________|_________|


  3���� ���� ũ�� �̹����� ū �̹����� �Ѹ���.
  Center���� ��� �̹����� ���� �ؼ� �׷�����.
  �뵵�� ��ũ�ѹ�, �������� ���

*/

		enum ePieceWhThree
		{ 
			ePiece_wLeft,			//���� ����
			ePiece_wCenter,         //���� �߰�
			ePiece_wRight,          //���� ������
			//count
			ePieceTypewCount,
		};

/*             ePieceHtThree
    			 _________
				|         |
				|   Top   |
				|   left  |
				|         |
				|_________|
				|         |
				|  Middle |
				|   left  |
				|         |
				|_________|
				|         |
				| Bottom  |
				|   left  |
				|         |
				|_________|

  3���� ���� ũ�� �̹����� ū �̹����� �Ѹ���.
  Center���� ��� �̹����� ���� �ؼ� �׷�����.
  �뵵�� ��ũ�ѹ�, �������� ���

*/
		enum ePieceHtThree
		{ 
			ePiece_hTop,			//���� ����
			ePiece_hCenter,			//���� �߰�
			ePiece_hBottom,			//���� ������
			//count
			ePieceTypehCount,
		};

/*             ePieceFullType
    	 _____________________________
		|							  |	
		|							  |
		|							  |
		|							  |
		|							  |
		|							  |
		|							  |
        |							  |
		|							  |
		|							  |
		|							  |
		|							  |
	    |							  |
		|							  |
		|_____________________________|

  ������ �̹����� �Ѹ���.
  �뵵�� ��� ȭ�� ���� ���� �̹���
*/
		enum ePieceOne
		{
			ePiece_oCenter,			//�߰�
			//count
			ePieceTypeoCount,
		};

	public:
		void SetImageIndex( const int bitmapindex );
		CompositedPanel( const string& uiName, ePanelType type = ePanel_Piece_Full );
		virtual ~CompositedPanel();

	public:
		void SetUVRect( const Rect& uvrect );

	private:
		void CalculateImageRect();
		void MakeImage( const int count );
		void Initialize( ePanelType type );
		void Destroy();

	protected:
		virtual void OnMove( const Coord& pos );
		virtual void OnResize( const Dim& dim );
		virtual void DrawImage();

	private:
		typedef vector< image::ImageUnitPtr >							Image_Vector;

	private:
		Image_Vector													m_Image;
		ePanelType														m_ePanelType;
		int																m_iSubPanelType;
		Color															m_Color;
	};
};

#endif // !defined(AFX_W_COMPOSITEDPANEL_H__48C4D2EA_FFE8_4CCD_A0AA_A493383B8F15__INCLUDED_)

#endif //NEW_USER_INTERFACE_UISYSTEM