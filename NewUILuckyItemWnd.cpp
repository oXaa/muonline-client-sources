// NewUILuckyItemWnd.cpp: implementation of the CNewUILuckyItemWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef LEM_ADD_LUCKYITEM

#include "NewUILuckyItemWnd.h"
#include "NewUISystem.h"
#include "NewUICustomMessageBox.h"
#include "ZzzBMD.h"
#include "ZzzEffect.h"
#include "ZzzObject.h"
#include "ZzzInventory.h"
#include "ZzzInterface.h"
#include "ZzzInfomation.h"
#include "ZzzCharacter.h"
#include "wsclientinline.h"
#include "DSPlaySound.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace SEASON3B;
CNewUILuckyItemWnd::CNewUILuckyItemWnd()
{
	memset( m_szSubject, 0, 255 );
	m_eType				= eLuckyItemType_None;
	m_nMixEffectTimer	= 0;
}

CNewUILuckyItemWnd::~CNewUILuckyItemWnd()
{
#ifdef LEM_FIX_LUCKYITEM_UICLASS_SAFEDELETE
	Release();
#endif // LEM_FIX_LUCKYITEM_UICLASS_SAFEDELETE
}

void CNewUILuckyItemWnd::SetFrame( void )
{
	float	fLineY		= m_ptPos.y + m_sImgList[eFrame_T].s_fHgt;
	float	fBottomY	= fLineY + m_sImgList[eFrame_L].s_fHgt;
	float	fLineX_R	= m_ptPos.x + m_fSizeX - m_sImgList[eFrame_L].s_fWid;

	for ( int i=0; i< eFrame_END; i++ )
	{
		m_sFrame[i].s_Img	= m_sImgList[i];
	}

	m_sFrame[eFrame_BG].s_ptPos		= m_ptPos;
	m_sFrame[eFrame_T].s_ptPos		= m_ptPos;

	m_sFrame[eFrame_L].s_ptPos.x	= m_ptPos.x;
	m_sFrame[eFrame_L].s_ptPos.y	= fLineY;

	m_sFrame[eFrame_R].s_ptPos.x	= fLineX_R;
	m_sFrame[eFrame_R].s_ptPos.y	= fLineY;

	m_sFrame[eFrame_B].s_ptPos.x	= m_ptPos.x;
	m_sFrame[eFrame_B].s_ptPos.y	= fBottomY;
}


int CNewUILuckyItemWnd::GetLuckyItemRate( int _nType )
{
	if( _nType == eLuckyItemType_Trade )		return 100;
	if( _nType == eLuckyItemType_Refinery )	return 50;

	return 0;
}


void CNewUILuckyItemWnd::Render_Frame( void )
{
	int	i=0;
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	unicode::t_char szText[256] = { 0, };
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

	for( i=0; i< eFrame_END; i++ )
	{
		RenderImage( m_sFrame[i].s_Img.s_nImgIndex, m_sFrame[i].s_ptPos.x, m_sFrame[i].s_ptPos.y, m_sFrame[i].s_Img.s_fWid, m_sFrame[i].s_Img.s_fHgt);
	}

	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->SetTextColor(255, 255, 255, 255);
	g_pRenderText->SetBgColor(0, 0, 0, 0);
	g_pRenderText->RenderText(m_ptPos.x, m_ptPos.y + 18.0f, m_szSubject, m_fSizeX, 0, RT3_SORT_CENTER);

	if( m_eEnd != eLuckyItem_End )	
	{
		m_BtnMix.Render();
	}
	else							
	{
		g_pNewUI3DRenderMng->RenderUI2DEffect(INVENTORY_CAMERA_Z_ORDER, UI2DEffectCallback, this, 0, 0);
	}
	
	float fTextY = m_ptPos.y + 18.0f + 190;
	for( i=0; i< m_nTextMaxLine; i++ )
	{
		if( m_sText[i].s_nTextIndex < 0 )	break;
		if( m_sText[i].s_nTextIndex == 0 )	continue;

		g_pRenderText->SetFont(g_hFont);
		g_pRenderText->SetTextColor( m_sText[i].s_dwColor );
		g_pRenderText->RenderText(m_ptPos.x +10, fTextY + 11.0f*i, GlobalText[m_sText[i].s_nTextIndex], m_fSizeX-20, 0, m_sText[i].s_nLine);
	}

	
}

int CNewUILuckyItemWnd::SetWndAction( eLUCKYITEM _eType )
{
	m_eWndAction = _eType;
	switch( m_eType )
	{
		case eLuckyItemType_Trade:
			if( m_eWndAction		== eLuckyItem_Move )	return 15;
			else if( m_eWndAction	== eLuckyItem_Act )		return 51;
		break;
		case eLuckyItemType_Refinery:
			if( m_eWndAction		== eLuckyItem_Move )	return 16;
			else if( m_eWndAction	== eLuckyItem_Act )		return 52;
		break;
	}

	return -1;
}

//----------------------------------------------------------------------------------------
// Function: 인벤 반짝이 효과
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.10.6]-
void CNewUILuckyItemWnd::UI2DEffectCallback(LPVOID pClass, DWORD dwParamA, DWORD dwParamB)
{
	if(pClass)
	{
		CNewUILuckyItemWnd* pInventory = (CNewUILuckyItemWnd*)pClass;
		pInventory->RenderMixEffect();
	}
}

void CNewUILuckyItemWnd::RenderMixEffect()
{
	if (m_nMixEffectTimer <= 0)
	{
		return;
	}
	else
	{
		--m_nMixEffectTimer;
	}
	
#ifdef MR0
	VPManager::Disable();
#endif //MR0
	EnableAlphaBlend();
#ifdef _VS2008PORTING
	for (int i = 0; i < (int)m_pNewInventoryCtrl->GetNumberOfItems(); ++i)
#else // _VS2008PORTING
		for (int i = 0; i < m_pNewInventoryCtrl->GetNumberOfItems(); ++i)
#endif // _VS2008PORTING
		{
			int iWidth = ItemAttribute[m_pNewInventoryCtrl->GetItem(i)->Type].Width;
			int iHeight = ItemAttribute[m_pNewInventoryCtrl->GetItem(i)->Type].Height;
			
			for (int h = 0; h < iHeight; ++h)
			{
				for (int w = 0; w < iWidth; ++w)
				{
					glColor3f((float)(rand()%6+6)*0.1f,(float)(rand()%4+4)*0.1f,0.2f);
					float Rotate = (float)((int)(WorldTime)%100)*20.f;
					float Scale = 5.f+(rand()%10);
					float x = m_pNewInventoryCtrl->GetPos().x + 
						(m_pNewInventoryCtrl->GetItem(i)->x + w) * INVENTORY_SQUARE_WIDTH +
						(rand()%INVENTORY_SQUARE_WIDTH);
					float y = m_pNewInventoryCtrl->GetPos().y + 
						(m_pNewInventoryCtrl->GetItem(i)->y + h) * INVENTORY_SQUARE_WIDTH +
						(rand()%INVENTORY_SQUARE_WIDTH);
					RenderBitmapRotate(BITMAP_SHINY  ,x,y,Scale,Scale,0);
					RenderBitmapRotate(BITMAP_SHINY  ,x,y,Scale,Scale,Rotate);
					RenderBitmapRotate(BITMAP_SHINY+1,x,y,Scale*3.f,Scale*3.f,Rotate);
					RenderBitmapRotate(BITMAP_LIGHT,x,y,Scale*6.f,Scale*6.f,0);
				}
			}
		}
		DisableAlphaBlend();
#ifdef MR0
		VPManager::Enable();
#endif //MR0
}

//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.7]-
void CNewUILuckyItemWnd::GetResult( BYTE _byResult, int _nIndex, BYTE* _pbyItemPacket )
{
	int		nDefault	= -1;
	int		nMessage	= nDefault;
	int		nPlaySound	= nDefault;
	int		nAddInven	= -1;
	bool	bInitInven	= false;

	// 인벤 컨트롤 초기화
	SEASON3B::CNewUIInventoryCtrl::DeletePickedItem();

	switch( m_eWndAction )
	{
		case eLuckyItem_Move:
			bInitInven	= true;
			nAddInven	= _nIndex;
		break;
		case eLuckyItem_Act:
			if( _byResult == 1 )
			{
				bInitInven			= true;
				nAddInven			= _nIndex;
				nPlaySound			= SOUND_JEWEL01;
				m_nMixEffectTimer	= 50;
			}
			else
			{
				if( m_eType == eLuckyItemType_Trade )
				{
					nMessage = 	3303;
				}
				else if( m_eType == eLuckyItemType_Refinery )	
				{
					bInitInven	= true;
				}
			}

			// 럭키아이템 대화창 종료!
			m_eEnd = eLuckyItem_End;
			SetFrame_Text( m_eEnd );
		break;
	}

	
	if( nMessage > nDefault )	g_pChatListBox->AddText("", GlobalText[nMessage], SEASON3B::TYPE_ERROR_MESSAGE);	
	if( nPlaySound > nDefault )	PlayBuffer(nPlaySound);
	if( bInitInven )			g_pLuckyItemWnd->Process_InventoryCtrl_DeleteItem(-1);
	if( nAddInven > nDefault )	Process_InventoryCtrl_InsertItem( nAddInven, _pbyItemPacket );

	m_eWndAction	= eLuckyItem_None;
}
//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
void CNewUILuckyItemWnd::LoadImg( void )
{
	float	fSizeX	= m_fSizeX;					// 프레임 넓이
	float	fSizeY	= m_fSizeY;					// 프레임 높이
	float	fTop	= 64.0f;					// 프레임 제목 텝 *
	float	fBottom	= 45.0f;					// 프레임 하단 텝 *
	float	fLineX	= 21.0f;					// 프레임 라인 넓이 *
	float	fLineY	= fSizeY - fTop - fBottom;	// 프레임 라인 높이

	char*	szFileName[] = { "Interface\\newui_msgbox_back.jpg", 
							 "Interface\\newui_item_back04.tga", 
							 "Interface\\newui_item_back02-L.tga", 
							 "Interface\\newui_item_back02-R.tga", 
							 "Interface\\newui_item_back03.tga",
							 "Interface\\newui_bt_mix.tga",
							};

	m_sImgList[eFrame_BG].Set		( CNewUIMessageBoxMng::IMAGE_MSGBOX_BACK,			fSizeX, fSizeY );
	m_sImgList[eFrame_T].Set		( CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP2,		fSizeX, fTop );
	m_sImgList[eFrame_L].Set		( CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT,		fLineX, fLineY );
	m_sImgList[eFrame_R].Set		( CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT,	fLineX, fLineY );
	m_sImgList[eFrame_B].Set		( CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM,	fSizeX, fBottom );
	m_sImgList[eImgList_MixBtn].Set	( BITMAP_INTERFACE_NEW_MIXINVENTORY_BEGIN,	44.0f, 35.0f );

 	for( int i=0; i< eImgList_END; i++ )
 	{
		LoadBitmap( szFileName[i], m_sImgList[i].s_nImgIndex, GL_LINEAR);	
 	}
}
//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
bool CNewUILuckyItemWnd::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if(NULL == pNewUIMng || NULL == g_pNewUI3DRenderMng || NULL == g_pNewItemMng)
		return false;
	
 	m_pNewUIMng = pNewUIMng;
 	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_LUCKYITEMWND, this);

	m_pNewInventoryCtrl = new CNewUIInventoryCtrl;
	if(false == m_pNewInventoryCtrl->Create(g_pNewUI3DRenderMng, g_pNewItemMng, this, x+15, y+110, 8, 4))
	{
		SAFE_DELETE(m_pNewInventoryCtrl);
		return false;
	}
	m_pNewInventoryCtrl->GetSquareColorNormal(m_fInvenClr);
	m_pNewInventoryCtrl->GetSquareColorWarning(m_fInvenClrWarning);

	SetPos( x, y );
	SetSize( 190.0f, 429.0f );
	LoadImg();
	SetFrame();

	float	fWidth	= 0.0f;
	float	fHeight = 0.0f;


	fWidth	= m_sImgList[eImgList_MixBtn].s_fWid;
	fHeight	= m_sImgList[eImgList_MixBtn].s_fHgt;
	m_BtnMix.ChangeButtonImgState(true, m_sImgList[eImgList_MixBtn].s_nImgIndex, false);
	m_BtnMix.ChangeButtonInfo( m_ptPos.x+ (m_fSizeX - fWidth)*0.5f, m_ptPos.y+380, fWidth, fHeight);

	for( int i=0; i< LUCKYITEMMAXLINE; i++ )	
	{
		m_sText[i].s_nTextIndex	= -1;
		m_sText[i].s_dwColor	= 0;
		m_sText[i].s_nLine		= false;
	}

 	Show(false);
	
	return true;
}

//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
void CNewUILuckyItemWnd::Release()
{
#ifdef LEM_FIX_LUCKYITEM_UICLASS_SAFEDELETE
	SAFE_DELETE(m_pNewInventoryCtrl);
#endif // LEM_FIX_LUCKYITEM_UICLASS_SAFEDELETE
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}


//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
void CNewUILuckyItemWnd::OpeningProcess( void )
{
	// 텍스트 인덱스 초기화 [lem_2010.9.2]
	for( int i=0; i< LUCKYITEMMAXLINE; i++ )	
	{
		m_sText[i].s_nTextIndex	= -1;
		m_sText[i].s_dwColor	= 0;
		m_sText[i].s_nLine		= false;
	}
	m_nTextMaxLine	= 0;
	m_eEnd	= eLuckyItem_None;
	switch( m_eType )
	{
		case eLuckyItemType_Trade:
			unicode::_sprintf( m_szSubject, "%s", GlobalText[3288]);
			AddText(3291, 0xFF0000FF, RT3_SORT_LEFT ), AddText(0), AddText(0), AddText(3292), AddText(3293), AddText(3294);
			AddText(0), AddText(0);
			AddText(2223, 0xFF00FFFF);
			AddText(0);
			AddText(3295, 0xFF0000FF), AddText(3296, 0xFF0000FF);
			m_BtnMix.ChangeToolTipText(GlobalText[591], true); // 조합
		break;
		case eLuckyItemType_Refinery:
			unicode::_sprintf( m_szSubject, "%s", GlobalText[3289]);
			AddText(2346, 0xFF0000FF, RT3_SORT_LEFT ), AddText(0), AddText(0);
			AddText(3300), AddText(3301);
			AddText(0), AddText(0), AddText(0);
			AddText(3302, 0xFF0000FF);
			m_BtnMix.ChangeToolTipText(GlobalText[2061], true); // 제련
		break;
	}
}

void CNewUILuckyItemWnd::SetFrame_Text( eLUCKYITEM _eType )
{
	switch( _eType )
	{
		case eLuckyItem_End:
			// 텍스트 인덱스 초기화 [lem_2010.9.2]
			for( int i=0; i< LUCKYITEMMAXLINE; i++ )	
			{
				m_sText[i].s_nTextIndex	= -1;
				m_sText[i].s_dwColor	= 0;
				m_sText[i].s_nLine		= false;
			}
			m_nTextMaxLine	= 0;
			AddText(0);
			if( m_eType == eLuckyItemType_Trade )			AddText(1888);
			else if( m_eType == eLuckyItemType_Refinery )	{}
		break;
	}
}

void CNewUILuckyItemWnd::AddText( int _nGlobalTextIndex, DWORD _dwColor, int _nLine )
{
	if( m_nTextMaxLine >= LUCKYITEMMAXLINE )	return;
	m_sText[m_nTextMaxLine].s_nTextIndex	= _nGlobalTextIndex;
	m_sText[m_nTextMaxLine].s_dwColor		= _dwColor;
	m_sText[m_nTextMaxLine].s_nLine			= _nLine;
	m_nTextMaxLine++;
}

bool CNewUILuckyItemWnd::ClosingProcess( void )
{
	if ( GetInventoryCtrl()->GetNumberOfItems() > 0 || CNewUIInventoryCtrl::GetPickedItem() != NULL)
	{
		// 조합창에 아이템이 있으면 창을 닫을 수 없다
		g_pChatListBox->AddText("", GlobalText[593], SEASON3B::TYPE_ERROR_MESSAGE);
		return false;
 	}

	SendRequestMixExit();
	m_eType = eLuckyItemType_None;
	return true;
}

bool CNewUILuckyItemWnd::Process_InventoryCtrl_InsertItem(int iIndex, BYTE* pbyItemPacket)
{
	if(m_pNewInventoryCtrl)
		return m_pNewInventoryCtrl->AddItem(iIndex, pbyItemPacket);
	return false;
}

void CNewUILuckyItemWnd::Process_InventoryCtrl_DeleteItem(int iIndex)
{
	if(m_pNewInventoryCtrl)
	{
		if( iIndex == -1 )
		{
			m_pNewInventoryCtrl->RemoveAllItems();
			return;
		}
		ITEM* pItem = m_pNewInventoryCtrl->FindItem(iIndex);
		if(pItem != NULL)
			m_pNewInventoryCtrl->RemoveItem(pItem);
	}
}
//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.7]-
bool CNewUILuckyItemWnd::Check_LuckyItem_InWnd( void )
{
	if( GetInventoryCtrl()->GetNumberOfItems() > 0 )	return true;
	return false;
}
//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.7]-
bool CNewUILuckyItemWnd::Check_LuckyItem( ITEM* _pItem )
{
	switch( m_eType )
	{
		case eLuckyItemType_Trade:
			if( Check_LuckyItem_Trade( _pItem ) )		return true;
		break;
		case eLuckyItemType_Refinery:
			if( Check_LuckyItem_Refinery( _pItem ) )	return true;
		break;
	}

	return false;
}

bool CNewUILuckyItemWnd::Check_LuckyItem_Trade( ITEM* _pItem )
{
	if( _pItem->Type >= ITEM_HELPER+135 && _pItem->Type <= ITEM_HELPER+145 )		return true;
	
	return false;
}

bool CNewUILuckyItemWnd::Check_LuckyItem_Refinery( ITEM* _pItem )
{
	if	   ( _pItem->Type >= ITEM_ARMOR+62 && _pItem->Type <= ITEM_ARMOR+72 )		return true;
	else if( _pItem->Type >= ITEM_HELM+62 && _pItem->Type <= ITEM_HELM+72 )		return true;
	else if( _pItem->Type >= ITEM_BOOTS+62 && _pItem->Type <= ITEM_BOOTS+72 )		return true;
	else if( _pItem->Type >= ITEM_GLOVES+62 && _pItem->Type <= ITEM_GLOVES+72 )	return true;
	else if( _pItem->Type >= ITEM_PANTS+62 && _pItem->Type <= ITEM_PANTS+72 )		return true;
	
	return false;
}
//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.6]-
bool CNewUILuckyItemWnd::Process_InventoryCtrl( void )
{
	CNewUIPickedItem* pPickedItem = CNewUIInventoryCtrl::GetPickedItem();
	if( !m_pNewInventoryCtrl )	return false;
	if( !pPickedItem )			return false;

	ITEM*	pItemObj	= pPickedItem->GetItem();
	bool	bAct		= Check_LuckyItem( pItemObj );
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	float	fInvenClr[3]= { 0, };
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

	if( !bAct || Check_LuckyItem_InWnd() )
	{
		// 럭키아이템과 상관없은 템이 올라오면 인벤 비활성 처리 후 리턴.
		m_pNewInventoryCtrl->SetSquareColorNormal(m_fInvenClrWarning[0], m_fInvenClrWarning[1], m_fInvenClrWarning[2] );
		return false;
	}

	if ( pPickedItem->GetOwnerInventory() == g_pMyInventory->GetInventoryCtrl())	// 인벤토리에서 조합창으로
	{
		if (SEASON3B::IsPress(VK_LBUTTON))
		{
			int iSourceIndex = pPickedItem->GetSourceLinealPos();
			int iTargetIndex = pPickedItem->GetTargetLinealPos(m_pNewInventoryCtrl);
			if(iTargetIndex != -1 && m_pNewInventoryCtrl->CanMove(iTargetIndex, pItemObj))
			{
				int		nMoveIndex	= SetWndAction( eLuckyItem_Move );
				if(SendRequestEquipmentItem(REQUEST_EQUIPMENT_INVENTORY, MAX_EQUIPMENT_INDEX+iSourceIndex, pItemObj, nMoveIndex, iTargetIndex))
				return true;
			}
		}
	}
	else if(pPickedItem->GetOwnerInventory() == m_pNewInventoryCtrl)	// 조합창에서 조합창으로	
	{
		if (SEASON3B::IsPress(VK_LBUTTON))
		{
			int iSourceIndex = pPickedItem->GetSourceLinealPos();
			int iTargetIndex = pPickedItem->GetTargetLinealPos(m_pNewInventoryCtrl);
			if(iTargetIndex != -1 && m_pNewInventoryCtrl->CanMove(iTargetIndex, pItemObj))
			{
				int		nMoveIndex	= SetWndAction( eLuckyItem_Move );
				if(SendRequestEquipmentItem(nMoveIndex, iSourceIndex,	pItemObj, nMoveIndex, iTargetIndex))
				{
					return true;
				}
			}
		}
	}

	// InventoryCtrl Background Color
	m_pNewInventoryCtrl->SetSquareColorNormal(m_fInvenClr[0], m_fInvenClr[1], m_fInvenClr[2] );
	return false;
}

CNewUIInventoryCtrl* CNewUILuckyItemWnd::GetInventoryCtrl() const
{ return m_pNewInventoryCtrl; }

//----------------------------------------------------------------------------------------
// Function: 
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.6]-
bool CNewUILuckyItemWnd::Process_BTN_Action( void )
{
	if( !m_BtnMix.UpdateMouseEvent() )							
		return false;

	if( m_eEnd == eLuckyItem_End )								
		return false;

	if( CNewUIInventoryCtrl::GetPickedItem() )					
		return false;

	// 조합/제련 창에 아이템이 아무것도 없을 때
	if( !Check_LuckyItem_InWnd() )
	{
		g_pChatListBox->AddText("", GlobalText[1817], SEASON3B::TYPE_ERROR_MESSAGE);
		return false;
	}
	if( !Check_LuckyItem( m_pNewInventoryCtrl->GetItem(0) ) )
	{
		g_pChatListBox->AddText("", GlobalText[1812], SEASON3B::TYPE_ERROR_MESSAGE);
		return false;
	}
#ifdef LEM_FIX_LUCKYITEM_SLOTCHECK
	if( g_pMyInventory->FindEmptySlot(4,4) == -1 )
#else // LEM_FIX_LUCKYITEM_SLOTCHECK
	if( g_pMyInventory->GetInventoryCtrl()->FindEmptySlot(4,4) == -1 )
#endif // LEM_FIX_LUCKYITEM_SLOTCHECK
	{
		g_pChatListBox->AddText("", GlobalText[1815], SEASON3B::TYPE_ERROR_MESSAGE);
		return false;
	}

	SEASON3B::CreateMessageBox(MSGBOX_LAYOUT_CLASS(SEASON3B::CLuckyItemMsgBoxLayout));
	return true;
}

//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
bool CNewUILuckyItemWnd::UpdateMouseEvent( void )
{
	if(m_pNewInventoryCtrl && false == m_pNewInventoryCtrl->UpdateMouseEvent())
		return false;
	Process_InventoryCtrl();
	
	POINT ptExitBtn1 = { m_ptPos.x+169, m_ptPos.y+7 };
	
	//. Exit1 버튼 (기본처리)
	if(SEASON3B::IsPress(VK_LBUTTON) && CheckMouseIn(ptExitBtn1.x, ptExitBtn1.y, 13, 12))
	{
		g_pNewUISystem->Hide(SEASON3B::INTERFACE_LUCKYITEMWND);
	}
	
	// 조합 버튼
	Process_BTN_Action();
	
	//. 인벤토리 내의 영역 클릭시 하위 UI처리 및 이동 불가
	if(CheckMouseIn(m_ptPos.x, m_ptPos.y, m_fSizeX, m_fSizeY))
	{
		if(SEASON3B::IsPress(VK_RBUTTON))
		{
			MouseRButton = false;
			MouseRButtonPop = false;
			MouseRButtonPush = false;
			return false;
		}
		
		if(SEASON3B::IsNone(VK_LBUTTON) == false)
		{
			return false;
		}
	}
	
	return true;
}
//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
bool CNewUILuckyItemWnd::UpdateKeyEvent( void )
{
	return true;
}
//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
bool CNewUILuckyItemWnd::Update( void )
{
	if(m_pNewInventoryCtrl && false == m_pNewInventoryCtrl->Update())	
		return false;
	
	return true;
}
//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
bool CNewUILuckyItemWnd::Render( void )
{
	EnableAlphaTest();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	
	Render_Frame();
	
	if(m_pNewInventoryCtrl)		
		m_pNewInventoryCtrl->Render();

	DisableAlphaBlend();
	
	return true;
}
//----------------------------------------------------------------------------------------
// Function: [Virtual]
// Input   :  
// Output  : 
//------------------------------------------------------------------------[lem_2010.9.1]-
float CNewUILuckyItemWnd::GetLayerDepth( void )
{	
	return 3.4f;
}

#endif // LEM_ADD_LUCKYITEM