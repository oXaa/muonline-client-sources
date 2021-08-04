//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//  INCLUDE.
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "UIWindows.h"
#include "ZzzOpenglUtil.h"
#include "ZzzBMD.h"
#include "zzzlodterrain.h"
#include "ZzzScene.h"
#include "MatchEvent.h"
//#include "CSEventMatch.h"
//#include "CSChaosCastle.h"

#include "w_CursedTemple.h"

//////////////////////////////////////////////////////////////////////////
//  EXTERN.
//////////////////////////////////////////////////////////////////////////
extern int g_iCustomMessageBoxButton[NUM_BUTTON_CMB][NUM_PAR_BUTTON_CMB];// ok, cancel // ��뿩��, x, y, width, height

namespace   matchEvent
{
    CSBaseMatch*    g_csMatchInfo = NULL;

//////////////////////////////////////////////////////////////////////////
//  �ش�Ǵ� �̺�Ʈ ��⸦ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
    void    CreateEventMatch ( int iWorld )
    {		
#ifdef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
		DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE

        if ( InBloodCastle() == true )   //  ����ĳ��.
        {
#ifndef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE		// !���� ���� ifndef
			DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
			g_csMatchInfo = new SEASON3B::CNewBloodCastleSystem;
        }
        else if ( InChaosCastle()==true )  //  ī����ĳ��.
        {
#ifndef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE		// !���� ���� ifndef
			DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
			g_csMatchInfo = new SEASON3B::CNewChaosCastleSystem;
        }
        else if ( InDevilSquare() )//  ����.
        {
#ifndef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE		// !���� ���� ifndef
			DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
            g_csMatchInfo = new CSDevilSquareMatch;
        }
		else if ( g_CursedTemple->IsCursedTemple() )
		{
#ifndef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE		// !���� ���� ifndef
			DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
			g_csMatchInfo = new CCursedTempleMatch;
		}
#ifdef YDG_ADD_DOPPELGANGER_EVENT
		else if (World >= WD_65DOPPLEGANGER1 && World <= WD_68DOPPLEGANGER4)
		{
#ifndef LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE		// !���� ���� ifndef
			DeleteEventMatch ();
#endif // LDS_FIX_MEMORYLEAK_WHEN_MATCHEVENT_TERMINATE
			g_csMatchInfo = new CDoppelGangerMatch;
		}
#endif	// YDG_ADD_DOPPELGANGER_EVENT
    }


//////////////////////////////////////////////////////////////////////////
//  EventMatch�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////
    void    DeleteEventMatch ( void )
    {
        if ( g_csMatchInfo!=NULL )
        {
            delete g_csMatchInfo;
            g_csMatchInfo = NULL;
        }
    }

}
