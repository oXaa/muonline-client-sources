// NewUIPartyListWindow.cpp: implementation of the CNewUIPartyInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NewUIPartyListWindow.h"
#include "NewUISystem.h"
#include "wsclientinline.h"
#include "ZzzInventory.h"

using namespace SEASON3B;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewUIPartyListWindow::CNewUIPartyListWindow()
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
	m_bActive = false;
	m_iVal = 24;
	m_iLimitUserIDHeight[0] = 48;
	m_iLimitUserIDHeight[1] = 58;
	m_iSelectedCharacter = -1;
	
	for( int i=0 ; i<MAX_PARTYS ; i++ )
	{
		m_iPartyListBGColor[ i ]  = PARTY_LIST_BGCOLOR_DEFAULT;
		m_bPartyMemberoutofSight[ i ] = false;
	}
}

CNewUIPartyListWindow::~CNewUIPartyListWindow()
{
	Release();
}

//---------------------------------------------------------------------------------------------
// Create
bool CNewUIPartyListWindow::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if( NULL == pNewUIMng )
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj( SEASON3B::INTERFACE_PARTY_INFO_WINDOW, this );		// �������̽� ������Ʈ ���
	
	SetPos(x, y);
	
	LoadImages();
	
	// Exit Party Button Initialize
	for( int i=0 ; i<MAX_PARTYS ; i++ )
	{	
		int iVal = i*m_iVal;		// �ε����� ���� ����(y�� ��ġ)
		m_BtnPartyExit[i].ChangeButtonImgState( true, IMAGE_PARTY_LIST_EXIT );
		m_BtnPartyExit[i].ChangeButtonInfo( m_Pos.x+63, m_Pos.y+3+iVal, 11, 11 );
	}	

	Show( true );
	
	return true;
}

//---------------------------------------------------------------------------------------------
// Release
void CNewUIPartyListWindow::Release()
{
	UnloadImages();
	
	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj( this );
		m_pNewUIMng = NULL;
	}
}

//---------------------------------------------------------------------------------------------
// SetPos
void CNewUIPartyListWindow::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	
	for( int i=0 ; i<MAX_PARTYS ; i++ )
	{	
		int iVal = i*m_iVal;		// �ε����� ���� ����(y�� ��ġ)
		m_BtnPartyExit[i].ChangeButtonInfo( m_Pos.x+63, m_Pos.y+3+iVal, 11, 11 );
	}
}

void CNewUIPartyListWindow::SetPos(int x)
{
	SetPos(x - (PARTY_LIST_WINDOW_WIDTH+2), m_Pos.y);
}

int CNewUIPartyListWindow::GetSelectedCharacter()
{
	if( m_iSelectedCharacter == -1 )
		return -1;
	
	return Party[m_iSelectedCharacter].index;
}

//---------------------------------------------------------------------------------------------
// SetListBGColor
// * zzzInterface() �� �����ɶ� ���� �ӽ÷� ���
void CNewUIPartyListWindow::SetListBGColor( )
{
	for( int i=0 ; i<PartyNumber ; i++)
	{	
		m_iPartyListBGColor[ i ] = PARTY_LIST_BGCOLOR_DEFAULT;
		
		if( Party[i].index == -1 )			// ���ΰ� ĳ���� �þ� �ۿ� �ִ°�
		{
			m_iPartyListBGColor[ i ] = PARTY_LIST_BGCOLOR_RED;
		}
		
		if( Party[i].index>-1 )		// ���� ��� ������ 
		{
			m_iPartyListBGColor[ i ]  = PARTY_LIST_BGCOLOR_GREEN;
		}
	}
}

//---------------------------------------------------------------------------------------------
// BtnProcess
bool CNewUIPartyListWindow::BtnProcess()
{
	m_iSelectedCharacter = -1;
	// ��Ƽ�̴�â (�׻� Render)
	for( int i=0 ; i<PartyNumber ; i++ )
	{	
		int iVal = i*m_iVal;		// �ε����� ���� ����(y�� ��ġ)		
		
		// X ��ư�� �������� ó��
		if( !strcmp( Party[0].Name, Hero->ID ) || !strcmp( Party[i].Name, Hero->ID ) )		// �ڽ��� ��Ƽ���϶�, �ڽŰ� Ÿ�� ����
		{
			if( m_BtnPartyExit[i].UpdateMouseEvent() )
			{
				g_pPartyInfoWindow->LeaveParty( i );
				return true;
			}
		}
		
		// �ɸ��ͼ���
		if( CheckMouseIn( m_Pos.x, m_Pos.y+iVal, PARTY_LIST_WINDOW_WIDTH, PARTY_LIST_WINDOW_HEIGHT) )
		{
			m_iSelectedCharacter = i;

#ifdef PSW_FIX_PARTYLISTSELECTCHARACTER
			if( SelectedCharacter==-1) {
				CHARACTER *c = &CharactersClient[Party[i].index];
				if( c && c != Hero ) {
					CreateChat ( c->ID, "", c );
				}
			}
#endif //PSW_FIX_PARTYLISTSELECTCHARACTER

			if( SelectCharacterInPartyList(	&Party[i] ) )	
			{
				return true;
			}
		}
	}
	
	return false;
}

//---------------------------------------------------------------------------------------------
// UpdateMouseEvent
bool CNewUIPartyListWindow::UpdateMouseEvent()
{
	if( !m_bActive )
		return true;
	
	// ��ư ó��
	if( true == BtnProcess() )	// ó���� �Ϸ� �Ǿ��ٸ�
		return false;
	
	// ��Ƽ â �� ���� Ŭ���� ���� UIó�� �� �̵� �Ұ�
	// ( #include "NewUICommon" )
	if( PartyNumber > 0 )
	{
		int iHeight = (PARTY_LIST_WINDOW_HEIGHT*PartyNumber) + (4*(PartyNumber-1));
		if( CheckMouseIn(m_Pos.x, m_Pos.y, PARTY_LIST_WINDOW_WIDTH, iHeight) )
		{
			return false;
		}
	}
	
	return true;
}

//---------------------------------------------------------------------------------------------
// UpdateKeyEvent
bool CNewUIPartyListWindow::UpdateKeyEvent()
{
	return true;
}

//---------------------------------------------------------------------------------------------
// Update
bool CNewUIPartyListWindow::Update()
{
	if( PartyNumber <= 0 )
	{
		m_bActive = false;
		return true;
	}
	
	m_bActive = true;
	
	for( int i=0 ; i<PartyNumber ; i++)
	{	
/*	// �ܺο��� �Լ� ȣ��( zzzInterface()�� �����Ǹ� �ּ�ó�� ���� )
		m_iPartyListBGColor[ i ] = PARTY_LIST_BGCOLOR_DEFAULT;

		if( Party[i].index == -1 )			// ���ΰ� ĳ���� �þ� �ۿ� �ִ°�
		{
			m_iPartyListBGColor[ i ] = PARTY_LIST_BGCOLOR_RED;
		}
		
		if( Party[i].index>-1 && (Party[i].state&STATE_DEFENSE)==STATE_DEFENSE)		// ���� ��� ������ 
		{
			m_iPartyListBGColor[ i ]  = PARTY_LIST_BGCOLOR_GREEN;
		}
*/
		
		// index �ʱ�ȭ
		// zzzInterface�� SelectObjects() �ȿ��� index�� ���Է�
		Party[ i ].index = -2;
	}
	
	return true;
}

//---------------------------------------------------------------------------------------------
// Render
bool CNewUIPartyListWindow::Render()
{
	if( !m_bActive )		// ��Ƽ���� ������ �� ����
		return true;

	// ��Ƽ�� �Ӹ��� HP�� ����
	//RenderPartyHPOnHead();
	
	EnableAlphaTest();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	
	g_pRenderText->SetFont( g_hFont );
	g_pRenderText->SetTextColor( 255, 255, 255, 255 );
	g_pRenderText->SetBgColor( 0, 0, 0, 0 );
	
	for( int i=0 ; i<PartyNumber ; i++)
	{	
		int iVal = i*m_iVal;		// �ε����� ���� ����(y�� ��ġ)
		
		// ���
		glColor4f ( 0.f, 0.f, 0.f, 0.9f );								// ������
		RenderColor( float(m_Pos.x+2), float(m_Pos.y+2+iVal), PARTY_LIST_WINDOW_WIDTH-3, PARTY_LIST_WINDOW_HEIGHT-6 );
		EnableAlphaTest();
		
		// ��Ƽ���� ȭ�� ������ ��������
		if( Party[i].index == -1 )
		{
			glColor4f ( 0.3f, 0.f, 0.f, 0.5f );						// +������
			RenderColor( m_Pos.x+2, m_Pos.y+2+iVal, PARTY_LIST_WINDOW_WIDTH-3, PARTY_LIST_WINDOW_HEIGHT-6 );
			EnableAlphaTest();
		}
		else
		{	
			if( Party[i].index >= 0 && Party[i].index < MAX_CHARACTERS_CLIENT )
			{
				CHARACTER* pChar = &CharactersClient[Party[i].index];
				OBJECT* pObj = &pChar->Object;
				
				// ���� ��� ������ �޾�����
				if(g_isCharacterBuff(pObj, eBuff_Defense) == true)
				{
					glColor4f ( 0.2f, 1.f, 0.2f, 0.2f );					// +������
					RenderColor( m_Pos.x+2, m_Pos.y+2+iVal, PARTY_LIST_WINDOW_WIDTH-3, PARTY_LIST_WINDOW_HEIGHT-6 );
					EnableAlphaTest();
				}
			}
			// �̴� ��Ƽâ�� ���콺 ������
			if( m_iSelectedCharacter != -1 && m_iSelectedCharacter == i )	// ���콺�� ���ý�
			{
				glColor4f ( 0.4f, 0.4f, 0.4f, 0.7f );						// +ȸ�����
				RenderColor( m_Pos.x+2, m_Pos.y+2+iVal, PARTY_LIST_WINDOW_WIDTH-3, PARTY_LIST_WINDOW_HEIGHT-6 );
				EnableAlphaTest();
			}
		}
		
		EndRenderColor();

		// ����̹��� ����
		RenderImage( IMAGE_PARTY_LIST_BACK, m_Pos.x, m_Pos.y+iVal, PARTY_LIST_WINDOW_WIDTH, PARTY_LIST_WINDOW_HEIGHT );
			
		if( i==0 ) // ��Ƽ���϶� 
		{	
			if( Party[i].index == -1 )		// ȭ�鿡 �������� ����
			{
				g_pRenderText->SetTextColor( RGBA( 128, 75, 11, 255 ) );		
			}
			else
			{
				g_pRenderText->SetTextColor( RGBA( 255, 148, 22, 255 ) );
			}
			
			// ����� ǥ�� ���
			RenderImage( IMAGE_PARTY_LIST_FLAG, m_Pos.x+53, m_Pos.y+3, 9, 10 );
			g_pRenderText->RenderText( m_Pos.x+4, m_Pos.y+4+iVal, Party[i].Name, m_iLimitUserIDHeight[0], 0, RT3_SORT_LEFT );
		}
		else		// ��Ƽ���� �ƴҶ� 
		{
			if( Party[i].index == -1 )		// ȭ�鿡 �������� ����
			{
				g_pRenderText->SetTextColor( RGBA( 128, 128, 128, 255 ) );
			}
			else
			{
				g_pRenderText->SetTextColor( RGBA( 255, 255, 255, 255 ) );		// ���� ����
			}
			g_pRenderText->RenderText( m_Pos.x+4, m_Pos.y+4+iVal, Party[i].Name, m_iLimitUserIDHeight[1], 0, RT3_SORT_LEFT );
		}
		
		// ID ( ��Ƽ��-��Ȳ��, ��Ƽ��-��� )
			
		// HPUI_Bar
		int iStepHP = min( 10, Party[i].stepHP );
		float fLife = ((float)iStepHP/(float)10)*(float)PARTY_LIST_HP_BAR_WIDTH;
		RenderImage(IMAGE_PARTY_LIST_HPBAR, m_Pos.x+4, m_Pos.y+16+iVal, fLife, 3);
		
		// ��Ƽ���� ������ ��ư( ��Ƽ���϶���, ��Ƽ���� �ƴҶ��� �ڽŸ� ����)
		if( !strcmp( Party[0].Name, Hero->ID ) || !strcmp( Party[i].Name, Hero->ID ) )
		{
			m_BtnPartyExit[i].Render();
		}
	}
	
	DisableAlphaBlend();
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//  ��Ƽ���� HP �� ȭ�鿡 �����ش�.
///////////////////////////////////////////////////////////////////////////////
void SEASON3B::CNewUIPartyListWindow::RenderPartyHPOnHead( )
{
    if ( PartyNumber<=0 ) 
		return;

    float   Width = 38.f;
    char    Text[100];

    //  ����� �̸����� ã�´�.
    //  �������� index�� ã�´�.
    for ( int j=0; j<PartyNumber; ++j )
    {
		PARTY_t *p = &Party[j];

        if (p->index<=-1) continue;  //  ȭ�鿡 ������ �ʴ� ĳ����.

        CHARACTER*  c = &CharactersClient[p->index];
	    OBJECT*     o = &c->Object;
	    vec3_t      Position;
	    int         ScreenX, ScreenY;

	    Vector ( o->Position[0], o->Position[1], o->Position[2]+o->BoundingBoxMax[2]+100.f, Position );
		
		BeginOpengl();
		Projection ( Position, &ScreenX, &ScreenY );
		EndOpengl();

        ScreenX -= (int)(Width/2);

        //  ���콺�� �˻縦 �Ѵ�.
	    if((MouseX>=ScreenX && MouseX<ScreenX+Width && MouseY>=ScreenY-2 && MouseY<ScreenY+6))
	    {
		    sprintf ( Text,"HP : %d0%%", p->stepHP );
			g_pRenderText->SetTextColor(255, 230, 210, 255);
		    g_pRenderText->RenderText(ScreenX, ScreenY-6, Text);
	    }
        //  10�ܰ�� ǥ���Ѵ�. 
	    EnableAlphaTest ();
   	    glColor4f ( 0.f, 0.f, 0.f, 0.5f );
	    RenderColor ( (float)(ScreenX+1), (float)(ScreenY+1), Width+4.f, 5.f );

	    EnableAlphaBlend ();
	    glColor3f ( 0.2f, 0.0f, 0.0f );
	    RenderColor ( (float)ScreenX, (float)ScreenY, Width+4.f, 5.f );

        glColor3f ( 50.f/255.f, 10/255.f, 0.f );
	    RenderColor ( (float)(ScreenX+2), (float)(ScreenY+2), Width, 1.f );

        int stepHP = min ( 10, p->stepHP );

        glColor3f ( 250.f/255.f, 10/255.f, 0.f );
        for ( int k=0; k<stepHP; ++k )   //  HP�� ǥ���Ѵ�.
        {
	        RenderColor ( (float)(ScreenX+2+(k*4)), (float)(ScreenY+2), 3.f, 2.f );
        }
	    DisableAlphaBlend();
    }
	DisableAlphaBlend();
	glColor3f(1.f,1.f,1.f);
}

//---------------------------------------------------------------------------------------------
// GetLayerDepth
float CNewUIPartyListWindow::GetLayerDepth()
{
	return 5.4f;
}

//---------------------------------------------------------------------------------------------
// OpenningProcess
void CNewUIPartyListWindow::OpenningProcess()
{
	
}

//---------------------------------------------------------------------------------------------
// ClosingProcess
void CNewUIPartyListWindow::ClosingProcess()
{
	
}

//---------------------------------------------------------------------------------------------
// SelectCharacterInPartyList
bool CNewUIPartyListWindow::SelectCharacterInPartyList( PARTY_t* pMember )
{
	/* 
		* Index
		* -1 : ȭ�鿡 �������� �ʴ´�.
		* -2 : default	
		* -3 : �ڱ� �ڽ�(?)
		* 0�̻� : SelectCharacter��
	*/
	
    int HeroClass = GetBaseClass( Hero->Class );
	
	//  (����, ����) �� ���ؼ� ����������.
	if ( HeroClass==CLASS_ELF 
		|| HeroClass==CLASS_WIZARD 
		|| HeroClass == CLASS_SUMMONER		// ��ȯ����
		)
	{
		int Skill = CharacterAttribute->Skill[Hero->CurrentSkill];
		
		//  ����, ���ݷ�, ü�� ���, �����̵�, �ֹٸ����� ��ų�� ���.
		if ( Skill==AT_SKILL_HEALING 
			|| Skill==AT_SKILL_DEFENSE 
#ifdef PJH_SEASON4_MASTER_RANK4
			|| (AT_SKILL_DEF_POWER_UP <= Skill && Skill <= AT_SKILL_DEF_POWER_UP+4)
			|| (AT_SKILL_ATT_POWER_UP <= Skill && Skill <= AT_SKILL_ATT_POWER_UP+4)
#endif //PJH_SEASON4_MASTER_RANK4
			|| Skill==AT_SKILL_ATTACK 
			|| Skill==AT_SKILL_TELEPORT_B 
			|| Skill==AT_SKILL_WIZARDDEFENSE 
			|| (AT_SKILL_HEAL_UP <= Skill && Skill <= AT_SKILL_HEAL_UP+4)
			|| (AT_SKILL_SOUL_UP <= Skill && Skill <= AT_SKILL_SOUL_UP+4)
			|| Skill == AT_SKILL_ALICE_THORNS		// ��ȯ���� ���� ��ų(�������ݻ�)
#ifdef PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			|| Skill == AT_SKILL_RECOVER
#endif //PJH_SEASON4_SPRITE_NEW_SKILL_RECOVER
			)
		{
			//  Ŀ���� �ش�Ǵ� ĳ���� ����.
			SelectedCharacter = pMember->index;
			return true;	
		}
	}

	return false;
}


//---------------------------------------------------------------------------------------------
// LoadImages
void CNewUIPartyListWindow::LoadImages()
{
	LoadBitmap("Interface\\newui_party_flag.tga", IMAGE_PARTY_LIST_FLAG, GL_LINEAR);
	LoadBitmap("Interface\\newui_party_x.tga", IMAGE_PARTY_LIST_EXIT, GL_LINEAR);
	
	// ��Ƽ �̴�â���
	LoadBitmap("Interface\\newui_party_back.tga", IMAGE_PARTY_LIST_BACK, GL_LINEAR);
	
	// HPBar
	LoadBitmap( "Interface\\newui_party_hpbar.jpg", IMAGE_PARTY_LIST_HPBAR, GL_LINEAR );
}

//---------------------------------------------------------------------------------------------
// UnloadImages
void CNewUIPartyListWindow::UnloadImages()
{
	DeleteBitmap(IMAGE_PARTY_LIST_FLAG);
	DeleteBitmap(IMAGE_PARTY_LIST_EXIT);
	
	// ��Ƽ�̴�â ���
	DeleteBitmap(IMAGE_PARTY_LIST_BACK);
	
	// HPBar
	DeleteBitmap( IMAGE_PARTY_LIST_HPBAR );
}
