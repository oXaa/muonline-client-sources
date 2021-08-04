// NewUIButton.cpp: implementation of the CNewUIButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NewUIButton.h"
#include "UIControls.h"
#include "GlobalBitmap.h"
#include "ZzzTexture.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace
{
	void PointSet( POINT& p, int x, int y )
	{
		p.x = x; p.y = y;
	}

	void RenderText( const char* text, int x, int y, int sx, int sy, HFONT hFont, DWORD color, DWORD backcolor, int sort )
	{
		g_pRenderText->SetFont(hFont);

		DWORD backuptextcolor = g_pRenderText->GetTextColor();
		DWORD backuptextbackcolor = g_pRenderText->GetBgColor();

		g_pRenderText->SetTextColor(color);
		g_pRenderText->SetBgColor(backcolor);
		g_pRenderText->RenderText(x, y, text, sx, sy, sort);

		g_pRenderText->SetTextColor(backuptextcolor);
		g_pRenderText->SetBgColor(backuptextbackcolor);
	}
};

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// CNewUIBaseButton
//////////////////////////////////////////////////////////////////////

CNewUIBaseButton::CNewUIBaseButton() : m_Lock( false ), m_EventState( BUTTON_STATE_UP )
{
	PointSet(m_Pos, 0, 0);
	PointSet(m_Size, 0, 0);
}

CNewUIBaseButton::~CNewUIBaseButton()
{

}

void CNewUIBaseButton::SetPos( int x, int y )
{
	PointSet(m_Pos, x, y);
}

void CNewUIBaseButton::SetSize( int sx, int sy )
{
	PointSet(m_Size, sx, sy);
}

bool CNewUIBaseButton::RadioProcess()
{
	bool isMousein = CheckMouseIn(m_Pos.x, m_Pos.y, m_Size.x, m_Size.y);

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	if( isMousein )
	{
		if( SEASON3B::IsPress(VK_LBUTTON) )
		{
			if( m_EventState == BUTTON_STATE_OVER )
			{
				m_EventState = BUTTON_STATE_DOWN;
				return true;
			}
		}
		else
		{
			if( m_EventState == BUTTON_STATE_UP )
			{
				m_EventState = BUTTON_STATE_OVER;
			}
		}
	}
	else
	{
		if( m_EventState == BUTTON_STATE_OVER )
		{
			m_EventState = BUTTON_STATE_UP;
		}
	}
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	if( SEASON3B::IsPress(VK_LBUTTON) && isMousein )
	{
		if( m_EventState == BUTTON_STATE_UP )
		{
			m_EventState = BUTTON_STATE_DOWN;
			return true;
		}
		else if( m_EventState == BUTTON_STATE_DOWN )
		{
			m_EventState = BUTTON_STATE_UP;
		}
	}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE

	return false;
}

bool CNewUIBaseButton::Process()
{
	bool isMousein = CheckMouseIn(m_Pos.x, m_Pos.y, m_Size.x, m_Size.y);

	if(SEASON3B::IsNone(VK_LBUTTON) && isMousein)
	{
		m_EventState = BUTTON_STATE_OVER;
	}
	else if(SEASON3B::IsRepeat(VK_LBUTTON) && isMousein)
	{
		m_EventState = BUTTON_STATE_DOWN;
	}
	else if(SEASON3B::IsRelease(VK_LBUTTON) && isMousein) 
	{
		m_EventState = BUTTON_STATE_UP;
		return true;
	}
	else
	{
		m_EventState = BUTTON_STATE_UP;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
// CNewUIButton
//////////////////////////////////////////////////////////////////////
CNewUIButton::CNewUIButton() : CNewUIBaseButton(), m_CurImgIndex(0),
m_CurImgState(0), m_ImgWidth(0), m_ImgHeight(0), 
m_NameColor(0xFFFFFFFF), m_NameBackColor(0x00000000), 
m_CurImgColor(0xFFFFFFFF), m_TooltipTextColor(0xFFFFFFFF), m_IsTopPos(false),
#ifndef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE			// #ifndef
m_IsImgWidth( false ),
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
m_fAlpha(1.0f)
{
	Initialize();
}

CNewUIButton::~CNewUIButton()
{
	Destroy();
}

void SEASON3B::CNewUIButton::Initialize()
{
	m_hTextFont = g_hFont;
	m_hToolTipFont = g_hFont;
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	m_iMoveTextPosX = 0;
	m_iMoveTextPosY = 0;
	m_bClickEffect = false;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
}

void SEASON3B::CNewUIButton::Destroy()
{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	UnRegisterButtonState();
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
}

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void SEASON3B::CNewUIButton::ChangeButtonImgState(bool imgregister, int imgindex, bool overflg /* = false */, 
												  bool bLockImage /* = false */, bool bClickEffect /* = false  */)
{
	m_bClickEffect = bClickEffect;
	
	if( imgregister )
	{
		RegisterButtonState( BUTTON_STATE_UP, imgindex, 0 );

		if( overflg ) 
		{
			RegisterButtonState( BUTTON_STATE_OVER, imgindex, 1 );
			RegisterButtonState( BUTTON_STATE_DOWN, imgindex, 2 );
		}
		else 
		{
			RegisterButtonState( BUTTON_STATE_OVER, imgindex, 0 );
			RegisterButtonState( BUTTON_STATE_DOWN, imgindex, 1 );
		}

		if( bLockImage )
		{
			RegisterButtonState( BUTTON_STATE_LOCK, imgindex, 3 );
		}
		else 
		{
			RegisterButtonState( BUTTON_STATE_LOCK, imgindex, 0 );
		}

		ChangeImgIndex(imgindex, 0);
	}
}
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
void SEASON3B::CNewUIButton::ChangeButtonImgState(bool imgregister, int imgindex, bool overflg, bool isimgwidth, bool bClickEffect )
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
void SEASON3B::CNewUIButton::ChangeButtonImgState(bool imgregister, int imgindex, bool overflg, bool isimgwidth )
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	m_bClickEffect = bClickEffect;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	
	if( imgregister )
	{
		if( overflg ) 
		{
			RegisterButtonState( BUTTON_STATE_UP, imgindex, 0 );
			RegisterButtonState( BUTTON_STATE_OVER, imgindex, 1 );
			RegisterButtonState( BUTTON_STATE_DOWN, imgindex, 2 );
		}
		else
		{
			RegisterButtonState( BUTTON_STATE_UP, imgindex, 0 );
			RegisterButtonState( BUTTON_STATE_DOWN, imgindex, 1 );
		}
		
		ChangeImgIndex(imgindex, 0);
		ChangeImgWidth(isimgwidth);
	}
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE


void SEASON3B::CNewUIButton::ChangeButtonInfo( int x, int y, int sx, int sy )
{
	SetPos( x, y );
	SetSize( sx, sy );
}

void SEASON3B::CNewUIButton::RegisterButtonState( BUTTON_STATE eventstate, int imgindex, int btstate )
{
	ButtonInfo btinfo;
	btinfo.s_ImgIndex     = imgindex;
	btinfo.s_BTstate      = btstate;

	m_ButtonInfo.insert(make_pair(eventstate, btinfo));
}

void SEASON3B::CNewUIButton::UnRegisterButtonState()
{
	m_ButtonInfo.clear();
}

void SEASON3B::CNewUIButton::ChangeImgIndex( int imgindex, int curimgstate )
{
	m_CurImgIndex = imgindex; 
	m_CurImgState = curimgstate;

	if( m_CurImgIndex != -1 )
	{
		BITMAP_t *b = &Bitmaps[m_CurImgIndex];

		m_ImgWidth = b->Width;
		m_ImgHeight = b->Height;
	}
}

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
void SEASON3B::CNewUIButton::ChangeButtonState( BUTTON_STATE eventstate, int iButtonState )
{
	if( m_ButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_ButtonInfo.find(static_cast<int>(eventstate));
		
		if( iter != m_ButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;
			info.s_BTstate = iButtonState;
		}
	}
}

void SEASON3B::CNewUIButton::MoveTextPos(int iX, int iY)
{
	m_iMoveTextPosX = iX;
	m_iMoveTextPosY = iY;
}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

void CNewUIButton::ChangeAlpha( unsigned char fAlpha, bool isfontalph )
{
	m_CurImgColor &= ~( 0xff << 24 ); 
	m_CurImgColor |= (fAlpha << 24);

	if( isfontalph )
	{
		m_NameColor &= ~( 0xff << 24 ); 
		m_NameColor |= (fAlpha << 24);
	}
}

void CNewUIButton::ChangeAlpha( float fAlpha, bool isfontalph )
{
	m_CurImgColor &= ~( 0xff << 24 );
	m_CurImgColor |= (static_cast<unsigned char>((float)(0xff) * fAlpha) << 24);

	if( isfontalph )
	{
		m_NameColor &= ~( 0xff << 24 ); 
		m_NameColor |= (static_cast<unsigned char>((float)(0xff) * fAlpha) << 24);
	}
}

void SEASON3B::CNewUIButton::ChangeImgColor( BUTTON_STATE eventstate, unsigned int color )
{
	if( m_ButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_ButtonInfo.find(static_cast<int>(eventstate));

		if( iter != m_ButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;
			info.s_imgColor = color;
			if( GetBTState() == eventstate ) 
			{
				m_CurImgColor = color;
			}
		}
	}
}

void SEASON3B::CNewUIButton::ChangeFrame()
{
	if( m_ButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_ButtonInfo.find(static_cast<int>(GetBTState()));

		if( iter != m_ButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;

			ChangeImgIndex(info.s_ImgIndex, info.s_BTstate);

			m_CurImgColor = info.s_imgColor;
		}
	}
}

bool SEASON3B::CNewUIButton::UpdateMouseEvent()
{
	if( IsLock() )
	{
		return false;
	}

	// ���콺 �̺�Ʈ �˻�
	BUTTON_STATE backevent = GetBTState();

	bool result = Process();

	if( backevent != GetBTState() )
	{
		//�̹����� �ٲ��ش�.
		ChangeFrame();
	}

	return result;
}

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void SEASON3B::CNewUIButton::Lock()
{
	CNewUIBaseButton::Lock();
	ChangeFrame();
}

void SEASON3B::CNewUIButton::UnLock()
{
	CNewUIBaseButton::UnLock();
	ChangeFrame();
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE


#ifdef PJH_ADD_MINIMAP
bool SEASON3B::CNewUIButton::Render( bool RendOption )
#else // PJH_ADD_MINIMAP
bool SEASON3B::CNewUIButton::Render( )
#endif // PJH_ADD_MINIMAP
{
	if( m_ButtonInfo.size() != 0 )
	{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		// ��ư�̹��� ���ҽ��� ������ ���η� �۾�!
#ifdef PJH_ADD_MINIMAP
		if(RendOption == true)
		RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y,0.f,m_CurImgState*m_Size.y,36.f/64.f,(29.f/32.f)/2.f);
		else
#endif //#ifdef PJH_ADD_MINIMAP
#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
		RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0.0f, m_CurImgState*m_Size.y, m_CurImgColor);
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
		RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0.0f, m_CurImgState*m_Size.y, m_CurImgColor);
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		if( m_IsImgWidth )
		{
			RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, m_CurImgState*m_Size.x, 0.0f, m_CurImgColor);
		}
		else
		{
			RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0.0f, m_CurImgState*m_Size.y, m_CurImgColor);
		}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	}

	if( m_Name.size() != 0 )
	{
		SIZE Fontsize;
		g_pRenderText->SetFont( m_hTextFont );				// ���� : Pruarin(07.08.03)
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), m_Name.c_str(), m_Name.size(), &Fontsize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), m_Name.c_str(), m_Name.size(), &Fontsize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

		Fontsize.cx = Fontsize.cx / ((float)WindowWidth / 640);
		Fontsize.cy = Fontsize.cy / ((float)WindowHeight / 480);

		int x = m_Pos.x+((m_Size.x/2)-(Fontsize.cx/2));
		int y = m_Pos.y+((m_Size.y/2)-(Fontsize.cy/2));

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		if( (m_bClickEffect == true) && (GetBTState() == BUTTON_STATE_DOWN) )
		{
			RenderText( m_Name.c_str(), x+m_iMoveTextPosX+1, y+m_iMoveTextPosY+1, m_Size.x, 0, m_hTextFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
		}
		else
		{
			RenderText( m_Name.c_str(), x+m_iMoveTextPosX, y+m_iMoveTextPosY, m_Size.x, 0, m_hTextFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
		}
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		RenderText( m_Name.c_str(), x, y, m_Size.x, 0, m_hTextFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	}

	if( m_TooltipText.size() != 0 )
	{
		if( CheckMouseIn(m_Pos.x, m_Pos.y, m_Size.x, m_Size.y) )
		{
			SIZE Fontsize;
			g_pRenderText->SetFont( m_hToolTipFont );			// ���� : Pruarin(07.08.03)
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), m_TooltipText.c_str(), m_TooltipText.size(), &Fontsize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
			unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), m_TooltipText.c_str(), m_TooltipText.size(), &Fontsize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

			Fontsize.cx = Fontsize.cx / ((float)WindowWidth / 640);
			Fontsize.cy = Fontsize.cy / ((float)WindowHeight / 480);

			int x = m_Pos.x+((m_Size.x/2)-(Fontsize.cx/2));
			int y = m_Pos.y+m_Size.y+2;
			
#ifdef LDK_FIX_MENUPOPUP_POSITION_BUG	// ���� : LDK (2008.4.29)
			int _iTempWidth =  x + Fontsize.cx + 6;
			x = ( _iTempWidth > 640 ) ? (x - ( _iTempWidth - 640 )) : x;
#endif //LDK_FIX_MENUPOPUP_POSITION_BUG

			if( m_IsTopPos ) y = m_Pos.y-(Fontsize.cy+2);

			RenderText( m_TooltipText.c_str(), x, y, Fontsize.cx+6, 0, m_hToolTipFont, m_TooltipTextColor, RGBA(0, 0, 0, 180), RT3_SORT_CENTER );
		}
	}
	
	return true;
}

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIBaseButton::Lock()
{
	m_EventState = BUTTON_STATE_LOCK;
	m_Lock = true;
}

void CNewUIBaseButton::UnLock()
{
	m_EventState = BUTTON_STATE_UP;
	m_Lock = false;
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE

//////////////////////////////////////////////////////////////////////
// CNewUIRadioButton
//////////////////////////////////////////////////////////////////////

CNewUIRadioButton::CNewUIRadioButton() : m_NameColor(0xffB5B5B5), m_NameBackColor(0x00000000), 
m_CurImgIndex(0), m_CurImgState(0), m_ImgWidth(0), m_ImgHeight(0), m_CurImgColor(0xffffffff)
{
	Initialize();
}

CNewUIRadioButton::~CNewUIRadioButton ()
{
	Destroy();
}

void CNewUIRadioButton::Initialize()
{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	m_hTextFont		= g_hFont;
	m_bClickEffect	= false;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
	m_bLockImage	= false;
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
}

void CNewUIRadioButton::Destroy()
{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	UnRegisterButtonState();
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
}

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIRadioButton::ChangeRadioButtonImgState(int imgindex, bool bMouseOnImage, bool bLockImage, bool bClickEffect )
{
	int btState = 0;

	m_bClickEffect	= bClickEffect;
	m_bLockImage	= bLockImage;

	RegisterButtonState(BUTTON_STATE_UP, imgindex, btState++);

	if( bMouseOnImage == true )
	{
		RegisterButtonState(BUTTON_STATE_OVER, imgindex, btState++);
	}

	RegisterButtonState(BUTTON_STATE_DOWN, imgindex, btState++);

	if( bLockImage == true )
	{
		RegisterButtonState(BUTTON_STATE_LOCK, imgindex, btState++);
	}
}
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIRadioButton::ChangeRadioButtonImgState(int imgindex, bool isDown, bool bClickEffect)
{
	m_bClickEffect = bClickEffect;
	RegisterButtonState(BUTTON_STATE_UP, imgindex, 0);
	RegisterButtonState(BUTTON_STATE_DOWN, imgindex, 1);
	
	if( isDown )
	{
		ChangeFrame(BUTTON_STATE_DOWN);
	}
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioButton::ChangeRadioButtonImgState(int imgindex, bool isDown)
{
	RegisterButtonState(BUTTON_STATE_UP, imgindex, 0);
	RegisterButtonState(BUTTON_STATE_DOWN, imgindex, 1);

	if( isDown )
	{
		ChangeFrame(BUTTON_STATE_DOWN);
	}
}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

void CNewUIRadioButton::ChangeRadioButtonInfo(int x, int y, int sx, int sy)
{
	SetPos( x, y );
	SetSize( sx, sy );
}

void CNewUIRadioButton::RegisterButtonState( BUTTON_STATE eventstate, int imgindex, int btstate )
{
	ButtonInfo btinfo;
	btinfo.s_ImgIndex     = imgindex;
	btinfo.s_BTstate      = btstate;

	m_RadioButtonInfo.insert(make_pair(eventstate, btinfo));
}

void CNewUIRadioButton::UnRegisterButtonState()
{
	m_RadioButtonInfo.clear();
}

void CNewUIRadioButton::ChangeImgColor( BUTTON_STATE eventstate, unsigned int color )
{
	if( m_RadioButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_RadioButtonInfo.find(static_cast<int>(eventstate));

		if( iter != m_RadioButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;
			info.s_imgColor = color;
			if( GetBTState() == eventstate )
			{
				m_CurImgColor = color;
			}
		}
	}
}

void CNewUIRadioButton::ChangeImgIndex( int imgindex, int curimgstate )
{
	m_CurImgIndex = imgindex; 
	m_CurImgState = curimgstate;

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	if( m_CurImgIndex != -1 && m_CurImgIndex != BITMAP_UNKNOWN )
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
	if( m_CurImgIndex != -1 )
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	{
		BITMAP_t *b = &Bitmaps[m_CurImgIndex];

		m_ImgWidth = b->Width;
		m_ImgHeight = b->Height;
	}
}

void CNewUIRadioButton::ChangeFrame( BUTTON_STATE eventstate )
{
	m_EventState = eventstate;

	if( m_RadioButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_RadioButtonInfo.find(static_cast<int>(GetBTState()));

		if( iter != m_RadioButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;

			ChangeImgIndex(info.s_ImgIndex, info.s_BTstate);
			
			m_CurImgColor = info.s_imgColor;
		}
	}
	
	if( m_Name.size() != 0 )
	{
		if( GetBTState() == BUTTON_STATE_UP )
			ChangeTextColor(0xffB5B5B5);
		else
			ChangeTextColor(0xffFFFFFF);
	}
}

void CNewUIRadioButton::ChangeFrame()
{
	if( m_RadioButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_RadioButtonInfo.find(static_cast<int>(GetBTState()));

		if( iter != m_RadioButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;

			ChangeImgIndex(info.s_ImgIndex, info.s_BTstate);

			m_CurImgColor = info.s_imgColor;
		}
	}

	if( m_Name.size() != 0 )
	{
		if( GetBTState() == BUTTON_STATE_UP )
			ChangeTextColor(0xffB5B5B5);
		else
			ChangeTextColor(0xffFFFFFF);
	}
}

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioButton::ChangeButtonState( int iImgIndex, BUTTON_STATE eventstate, int iButtonState )
{
	if( m_RadioButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_RadioButtonInfo.find(static_cast<int>(eventstate));
		
		if( iter != m_RadioButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;
			info.s_ImgIndex = iImgIndex;
			info.s_BTstate = iButtonState;
		}
	}
}

void CNewUIRadioButton::ChangeButtonState(BUTTON_STATE eventstate, int iButtonState )
{
	if( m_RadioButtonInfo.size() != 0 )
	{
		ButtonStateMap::iterator iter = m_RadioButtonInfo.find(static_cast<int>(eventstate));
		
		if( iter != m_RadioButtonInfo.end() )
		{
			ButtonInfo& info = (*iter).second;
			info.s_BTstate = iButtonState;
		}
	}
}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void SEASON3B::CNewUIRadioButton::Lock()
{
	CNewUIBaseButton::Lock();
	ChangeFrame();
}

void SEASON3B::CNewUIRadioButton::UnLock()
{
	CNewUIBaseButton::UnLock();
	ChangeFrame();
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE

bool CNewUIRadioButton::UpdateMouseEvent( bool isGroupevent )
{
	if( IsLock() )
	{
		return false;
	}

	// ���콺 �̺�Ʈ �˻�
	BUTTON_STATE backevent = GetBTState();

	bool result = false;

	if( isGroupevent )
	{
		if( GetBTState() != BUTTON_STATE_DOWN )
		{
			result = RadioProcess();
			if( backevent != GetBTState() )
			{
				ChangeFrame();
			}
		}
	}
	else 
	{
		result = RadioProcess();
		if( backevent != GetBTState() )
		{
			ChangeFrame();
		}
	}

	return result;
}

bool CNewUIRadioButton::Render()
{
	if( m_RadioButtonInfo.size() != 0 )
	{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		// ��ư�̹��� ���ҽ��� ������ ���η� �۾�!
		// State�� ���� Image�� Render ���Ҷ� BITMAP Index�� BITMAP_UNKNOWN���� �����Ѵ�.
		if( m_CurImgIndex != BITMAP_UNKNOWN )	 // BITMAP Index�� �������� Render
		{
			RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0.0f, m_CurImgState*m_Size.y, m_CurImgColor);
		}
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		// �̹��� ����, ���� ũ�� �񱳷� UV���� �ٲٴ¹���� ���� �ʾ�!! (���׹߻���)
		if( m_ImgWidth < m_ImgHeight )
		{
			RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, m_CurImgState*m_Size.x, 0.0f, m_CurImgColor);
		}
		else
		{
			RenderImage(m_CurImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0.0f, m_CurImgState*m_Size.y, m_CurImgColor);
		}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	}

	if( m_Name.size() != 0 )
	{
		SIZE Fontsize;
		
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		g_pRenderText->SetFont(m_hTextFont);
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		g_pRenderText->SetFont(g_hFont);
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), m_Name.c_str(), m_Name.size(), &Fontsize);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
		unicode::_GetTextExtentPoint(g_pRenderText->GetFontDC(), m_Name.c_str(), m_Name.size(), &Fontsize);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

		Fontsize.cx = Fontsize.cx / ((float)WindowWidth / 640);
		Fontsize.cy = Fontsize.cy / ((float)WindowHeight / 480);

		int x = m_Pos.x+((m_Size.x/2)-(Fontsize.cx/2));
		int y = m_Pos.y+((m_Size.y/2)-(Fontsize.cy/2));

		// ���� : Pruarin(07.08.03)
		//RenderText( m_Name.c_str(), x, y, m_Size.x, 0, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
		if( (m_bClickEffect==true) && GetBTState()==BUTTON_STATE_DOWN)
		{
			RenderText( m_Name.c_str(), x+1, y+1, m_Size.x, 0, m_hTextFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
		}
		else
		{
			RenderText( m_Name.c_str(), x, y, m_Size.x, 0, m_hTextFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
		}
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
		RenderText( m_Name.c_str(), x, y, m_Size.x, 0, g_hFont, m_NameColor, m_NameBackColor, RT3_SORT_LEFT );
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// CNewUIRadioGroupButton
//////////////////////////////////////////////////////////////////////

CNewUIRadioGroupButton::CNewUIRadioGroupButton()
{
	Initialize();
}

CNewUIRadioGroupButton::~CNewUIRadioGroupButton()
{
	Destroy();
}

void CNewUIRadioGroupButton::Initialize()
{
#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
	m_iButtonDistance = 1;
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM
}

void CNewUIRadioGroupButton::Destroy()
{
#ifdef YDG_FIX_MEMORY_LEAK_0905
	UnRegisterRadioButton();
#endif	// YDG_FIX_MEMORY_LEAK_0905
}

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIRadioGroupButton::CreateRadioGroup(int radiocount, int imgindex, bool bFirstIndexBtnDown /* = true */, 
												bool bMouseOnImage /* = false */, bool bLockImage, bool bClickEffect /* = false  */)
{
	for( int i = 0; i < radiocount; ++i )
	{
		CNewUIRadioButton* button = new CNewUIRadioButton();

		button->ChangeRadioButtonImgState(imgindex, bMouseOnImage, bLockImage, bClickEffect);
		button->ChangeRadioButtonInfo(0,0,0,0);
		RegisterRadioButton( button );
	}

	int iCurIndex = -1;

	if( bFirstIndexBtnDown == true )
	{
		iCurIndex = 0;
	}

	ChangeFrame(iCurIndex);
	SetCurButtonIndex(iCurIndex);
}
#else // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIRadioGroupButton::CreateRadioGroup( int radiocount, int imgindex, bool bClickEffect )
{
	for( int i = 0; i < radiocount; ++i )
	{
		CNewUIRadioButton* button = new CNewUIRadioButton();

		button->ChangeRadioButtonImgState(imgindex, ((i==0)?true:false), bClickEffect);
		button->ChangeRadioButtonInfo(0,0,0,0);
		RegisterRadioButton( button );
	}
	
	SetCurButtonIndex(0);
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioGroupButton::CreateRadioGroup( int radiocount, int imgindex )
{
	for( int i = 0; i < radiocount; ++i )
	{
		CNewUIRadioButton* button = new CNewUIRadioButton();
		button->ChangeRadioButtonImgState(imgindex, ((i==0)?true:false));
		button->ChangeRadioButtonInfo(0,0,0,0);
		RegisterRadioButton( button );
	}

	SetCurButtonIndex(0);
}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioGroupButton::ChangeRadioButtonInfo(bool iswidth, int x, int y, int sx, int sy, int iDistance/* = 1*/)
{
	int i = 0;
	
	m_iButtonDistance = iDistance;
	
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
		
		if( button )
		{
			if( iswidth ) button->SetPos(x+((sx+m_iButtonDistance)*i), y);
			else button->SetPos(x, y+((sy+m_iButtonDistance)*i));
			button->SetSize( sx, sy );
		}
		
		++i;
	}
}

void CNewUIRadioGroupButton::ChangeButtonState( BUTTON_STATE eventstate, int iButtonState )
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
	
		button->ChangeButtonState(eventstate, iButtonState);

		++i;
	}
}

void CNewUIRadioGroupButton::ChangeButtonState(int iBtnIndex, int iImgIndex, BUTTON_STATE eventstate, int iButtonState)
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		if( i == iBtnIndex )
		{
			button->ChangeButtonState(iImgIndex, eventstate, iButtonState);
			return;
		}
		
		++i;
	}
}

#else // KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioGroupButton::ChangeRadioButtonInfo( bool iswidth, int x, int y, int sx, int sy )
{
	int i = 0;
	
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
		
		if( button )
		{
			if( iswidth ) button->SetPos(x+((sx+1)*i), y);
			else button->SetPos(x, y+((sy+1)*i));
			button->SetSize( sx, sy );
		}
		
		++i;
	}
}
#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

void CNewUIRadioGroupButton::ChangeRadioText( list<unicode::t_string>& textlist )
{
	list<unicode::t_string>::iterator textiter = textlist.begin();

	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		list<unicode::t_string>::iterator curtextiter = textiter;
		++textiter;
		unicode::t_string text = (*curtextiter);

		button->ChangeText( text );

		if( textiter == textlist.end() ) break;
	}
}

void CNewUIRadioGroupButton::ChangeFrame( int buttonIndex )
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
	
		if( i != buttonIndex )
		{
			button->ChangeFrame( BUTTON_STATE_UP );
		}
		else
		{
			SetCurButtonIndex(i);
			button->ChangeFrame( BUTTON_STATE_DOWN );
		}
		++i;
	}
}

// �߰� : Pruarin(07.09.03)
void CNewUIRadioGroupButton::LockButtonindex( int buttonIndex )
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		if( i == buttonIndex )
		{
			button->Lock();
			break;
		}

		++i;
	}
}

#ifdef KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE
void CNewUIRadioGroupButton::UnLockButtonIndex( int buttonIndex )
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
		
		if( i == buttonIndex )
		{
			button->UnLock();
			break;
		}
		
		++i;
	}
}
#endif // KJH_MOD_RADIOBTN_MOUSE_OVER_IMAGE

void CNewUIRadioGroupButton::RegisterRadioButton( CNewUIRadioButton* button )
{
	m_RadioList.push_back( button );
}

void CNewUIRadioGroupButton::UnRegisterRadioButton()
{
	for( RadioButtonList::reverse_iterator iter = m_RadioList.rbegin(); iter != m_RadioList.rend(); )
	{
		RadioButtonList::reverse_iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		SAFE_DELETE( button );
	}

	m_RadioList.clear();
}

int CNewUIRadioGroupButton::UpdateMouseEvent()
{
	int i = 0;
	
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		if( button->UpdateMouseEvent(true) )
		{
			ChangeFrame(i);
			return GetCurButtonIndex();
		}

		++i;
	}

	return static_cast<int>(RADIOGROUPEVENT_NONE);
}

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM
void CNewUIRadioGroupButton::SetFont( HFONT hFont )
{
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		button->SetFont(hFont);
	}
}

void CNewUIRadioGroupButton::SetFont(HFONT hFont, int iButtonIndex )
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		if( i == iButtonIndex )
		{
			button->SetFont(hFont);
			break;
		}
		
		++i;
	}
}

POINT CNewUIRadioGroupButton::GetPos(int iButtonIndex)
{
	int i = 0;
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);
		
		if( i == iButtonIndex )
		{
			return button->GetPos();
		}	
		++i;
	}

	POINT Pos;
	Pos.x = 0;
	Pos.y = 0;

	return Pos;
}

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

bool CNewUIRadioGroupButton::Render()
{
	for( RadioButtonList::iterator iter = m_RadioList.begin(); iter != m_RadioList.end(); )
	{
		RadioButtonList::iterator curiter = iter;
		++iter;
		CNewUIRadioButton* button = (*curiter);

		button->Render();
	}

	return true;
}
















