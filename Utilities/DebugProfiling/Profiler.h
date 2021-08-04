// Profiler.h: interface for the CProfiler class.
//
//////////////////////////////////////////////////////////////////////

#ifdef LDS_ADD_DEBUGINGMODULES_FOR_PROFILING

#pragma once

#include <io.h>
#include <stdio.h>

#include "Profiler_Unit.h"

#include "debugSingleton_.h"

#include "Profiler_util_.h"

#include "Profiler_FileIO_.h"

#include "DebugArray_.h"

#define DEFAULT_PROFILINGNAME TEXT( "ResultProfiling.txt" )

class CProfiler : public CdebugSingleton_<CProfiler>  
{
public:
	CProfiler();
	virtual ~CProfiler();
	void Clear( void);

private:
	CProfiler_Clock			*m_pClock;
	CProfiler_FileIO_		m_FileIO;

	char					m_szDefaultOutputFileName[512];
	char					m_szDefaultOutputResult_[8192];

	CProfiler_Unit			m_SearchKey;

protected:
	BOOL m_bFirstTime;	///< ��Ȯ���� ���� ù �������� �����Ѵ�.
	BOOL m_bProfiling;
	BOOL m_bOutputResultsWhenGenerate;

	EPROFILESORTING_TYPE
		 m_eProfileUnitsSortingtypeForOutputResultText;
	EPROFILESORTING_DIRECTION
		 m_eProfileUnitsSortingDirectionForOutputResultText;


	// @@ �ܺ� ��û ����
	BOOL m_bRequestLive;
	BOOL m_bRequestKill;
	BOOL m_bRequestReset;
	BOOL m_bRequestGenerateResult;
	BOOL m_bGenerateResultLaststFrame;

	unsigned int m_uiGenerateCnt;

	int m_iNumSample;

	util_array_::array_<CProfiler_Unit> m_arrProfileUnits;
	
	/// @name ��ü �ð�
	LONGLONG m_llTotalTickStart;
	LONGLONG m_llTotalTickEnd;
	LONGLONG m_llTotalProcessTick;
	LONGLONG m_llTotalProcessTick_Grand;

	/// @ ȣ�� Ƚ��
	unsigned long m_ulCountInFrame;
	unsigned long m_ulCountInFrame_Grand;

	LONGLONG m_llTickPerMS;

protected:
	void Initialize_();			/// �ʱ�ȭ CORE
	void InitClock_( void );	///< measure �� ���� �Ŀ� �Ұ�
	void Release_( void );
	
	void GenerateResultAll( const LONGLONG &llTotalTime, 
							const LONGLONG &llGrandTotalTime, 
							const LONGLONG &llTickPerMS );	///< ��� ����
	
	void RequestLiveAllUnits( void );
	void RequestKillAllUnits( void );

	void SetAllUnitsSortingType( EPROFILESORTING_TYPE eProfileSorting_type )
	{
		for( int i_ = 0; i_ < m_arrProfileUnits.size(); ++i_ )
		{
			m_arrProfileUnits[i_].SetSortingType( eProfileSorting_type );
		}
	}

public:
	void SetSortingTypeKey()
	{
		SetAllUnitsSortingType( EPROFILESORTING_INDEX );
	}

	void SetSortingTypeWeight()
	{
		SetAllUnitsSortingType( EPROFILESORTING_WEIGHT );
	}

	void Reset( void );			///< ��� �ʱ�ȭ

	void Initialize( BOOL bOutputResultsWhenGenerate = TRUE,
					char *szOutput			= DEFAULT_PROFILINGNAME,
					EPROFILESORTING_TYPE eSortingtypeforOutputResultData
											= EPROFILESORTING_WEIGHT,
					EPROFILESORTING_DIRECTION eSortingDirectionforOutputResultData
											= EPROFILESORTING_DIRECTION_ASCENDING,
					BOOL bPauseWithStart	= TRUE );

	void Release( void );

	// @@ ��� Profling Looping �� ���۰� ��.
	void BeginTotal( BOOL bClearAll = FALSE );
	void EndTotal( );

	// @@ �ܺ� ��û �Լ���
	BOOL IsProflingNow() 
	{
		return m_bProfiling;
	}

	void RequestGenerateResult()
	{
		m_bRequestGenerateResult = TRUE;
	}

	void RequestReset()
	{
		m_bRequestReset = TRUE;
	}

	void RequestLiveProfiling()	
	{ 
		m_bRequestLive = TRUE;
	};

	void RequestKillProfiling()		
	{ 
		m_bRequestKill = TRUE;
	};

	BOOL GetGeneratedResultText()
	{
		return m_bGenerateResultLaststFrame;
	};

	BOOL GetRequestGenerateResult()
	{
		return m_bRequestGenerateResult;
	}

	BOOL GetRequestEndProfiling()
	{
		return m_bRequestKill;
	};

	BOOL GetRequestBeginProfiling()
	{
		return m_bRequestLive;
	}

	void BeginUnit( unsigned int ikey, char *lpszName, BOOL bLive = TRUE, unsigned int uiDegree = 0 );
	void EndUnit( unsigned int iKey );

	int GetNumSample( void)	{ return ( m_iNumSample); }
	void GetResult_Percentage( unsigned int uiKey, float *pfLatestPercentage, float *pfMaxPercentage, float *pfMinPercentage, float *pfTotalPercentage);
	void GetResult_StatisticAve( unsigned int uiKey, 
									float *pfAve_ms, 
									unsigned long *pulAve_tick, 
									float *pfAve_ms_GrandTotal,
									unsigned long *pulAve_tick_GrandTotal ); 

	void GetResult_AllProperty( unsigned int uiKey, 
								float *pfLatestPercentage, float *pfMaxPercentage, float *pfMinPercentage, float *pfTotalPercentage,
								float *pfAve_ms, unsigned long *pulAve_tick, float *pfAve_ms_GrandTotal, unsigned long *pulAve_tick_GrandTotal );

	void GetResultText( unsigned int uiKey, char *lpszText );
	
	char *GetResultText_All( void);

	void OutputDefaultText( char *szDefaultFileName, 
							BOOL bOutputRates = TRUE, 
							BOOL bOutputProcessTicks = FALSE,
							BOOL bOutputCallCounts = TRUE,
							BOOL bOutputMS = TRUE);
};

#endif // LDS_ADD_DEBUGINGMODULES_FOR_PROFILING
