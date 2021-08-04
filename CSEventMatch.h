//////////////////////////////////////////////////////////////////////////
//  
//  CSEventMatch.h
//
//  ��  �� : �̺�Ʈ ��⿡ ���õ� ó��.
//
//  ��  ¥ : 2004/04/12
//
//  �ۼ��� : �� �� ��.
//
//////////////////////////////////////////////////////////////////////////
#ifndef __CSEVENT_MATCH_H__
#define __CSEVENT_MATCH_H__


//////////////////////////////////////////////////////////////////////////
//  INCLUDE.
//////////////////////////////////////////////////////////////////////////
#include "wsclient.h"

//////////////////////////////////////////////////////////////////////////
//  CLASS.
//////////////////////////////////////////////////////////////////////////

//  ��� ���� ó��.
//////////////////////////////////////////////////////////////////////////
class CSBaseMatch
{
protected:
    BYTE        m_byMatchEventType;
    // ī��Ʈ �ٿ�
    MATCH_TYPE  m_iMatchCountDownType;  //  �Ǹ��Ǳ���(1,2,3), ����ĳ��(4,5,6,7), ī����ĳ��(8,9,10,11)
    DWORD       m_dwMatchCountDownStart;
    BYTE        m_byMatchType;          //  ��� ����.
    int         m_iMatchTimeMax;        //  ��� �� �ð�.
    int         m_iMatchTime;           //  ��� �ð�.

    int         m_iMaxKillMonster;      //  ��ǥ ���� ��ɷ�.
    int         m_iKillMonster;         //  ����� ���ͼ�.

    // ��� ���.
    int         m_iNumResult;
    int         m_iMyResult;
    MatchResult m_MatchResult[11];

	// ���â ������
	POINT		m_PosResult;

    bool    getEqualMonster ( int addV );

    void    renderOnlyTime ( float x, float y, int MatchTime );
    
public:
    CSBaseMatch () : m_dwMatchCountDownStart(0), m_byMatchType(0), m_iMatchTimeMax(-1), m_iMatchTime(-1), m_iMaxKillMonster(-1), m_iKillMonster(-1), m_iNumResult(0), m_iMyResult(0)  
    {
        memset ( m_MatchResult, 0, sizeof( MatchResult )*11 );
    }
    virtual ~CSBaseMatch () {};

    void    clearMatchInfo ( void );
    BYTE    GetMatchEventType ( void ) { return m_byMatchEventType; }

	BYTE	GetMatchType( ) { return m_byMatchType; }
	int		GetMatchTime( ) { return m_iMatchTime; }
	int		GetMatchMaxTime( ) { return m_iMatchTimeMax; };
	int		GetNumMustKillMonster( ) { return m_iMaxKillMonster; }
	int		GetNumKillMonster( ) {return m_iKillMonster; }	
	
	void	SetPosition( int ix, int iy );
    void    StartMatchCountDown ( int iType );
    void    SetMatchInfo ( const BYTE byType, const int iMaxTime, const int iTime, const int iMaxMonster=0, const int iKillMonster=0 );

    void    RenderTime ( void );
    virtual void    RenderMatchTimes ( void ) = 0;

    virtual void    SetMatchGameCommand ( const LPPRECEIVE_MATCH_GAME_STATE data ) = 0;
    virtual void    SetMatchResult ( const int iNumDevilRank, const int iMyRank, const MatchResult *pMatchResult, const int Success=false ) = 0;
    virtual void    RenderMatchResult ( void ) = 0;
};


//////////////////////////////////////////////////////////////////////////
//  �Ǹ��� ���� ��� ���� ó��.
//////////////////////////////////////////////////////////////////////////
class CSDevilSquareMatch : public CSBaseMatch
{
private:

public:
    CSDevilSquareMatch () {};
    virtual ~CSDevilSquareMatch () {};

    virtual void    RenderMatchTimes ( void );

    virtual void    SetMatchGameCommand ( const LPPRECEIVE_MATCH_GAME_STATE data );
    virtual void    SetMatchResult ( const int iNumDevilRank, const int iMyRank, const MatchResult *pMatchResult, const int Success=false );
    virtual void    RenderMatchResult ( void );
};


class CCursedTempleMatch : public CSBaseMatch
{
private:

public:
    CCursedTempleMatch () {};
    virtual ~CCursedTempleMatch () {};

    virtual void    RenderMatchTimes ( void );

    virtual void    SetMatchGameCommand ( const LPPRECEIVE_MATCH_GAME_STATE data );
    virtual void    SetMatchResult ( const int iNumDevilRank, const int iMyRank, const MatchResult *pMatchResult, const int Success=false );
    virtual void    RenderMatchResult ( void );
};

#ifdef YDG_ADD_DOPPELGANGER_EVENT
class CDoppelGangerMatch : public CSBaseMatch
{
private:

public:
    CDoppelGangerMatch () {};
    virtual ~CDoppelGangerMatch () {};

    virtual void    RenderMatchTimes ( void ) {}

    virtual void    SetMatchGameCommand ( const LPPRECEIVE_MATCH_GAME_STATE data ) {}
    virtual void    SetMatchResult ( const int iNumDevilRank, const int iMyRank, const MatchResult *pMatchResult, const int Success=false ) {}
    virtual void    RenderMatchResult ( void ) {}
};
#endif	// YDG_ADD_DOPPELGANGER_EVENT

#endif// __CSEVENT_MATCH_H__
