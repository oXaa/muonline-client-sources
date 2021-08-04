#pragma once

#ifdef LDS_ADD_DEBUGINGMODULES_FOR_PROFILING

#include <WTypes.h>

#include "Profiler_define.h"

#define MAX_PROFILESAMPLENAME	( 64)

#define NULL_KEY				( 99999999 )

enum EREQUEST_TYPE { EREQUEST_NULL = -1,
EREQUEST_LIVE, 
EREQUEST_KILL };

class CProfiler_Unit  
{
public:
	CProfiler_Unit();
	CProfiler_Unit( unsigned int, 
		char *szProfileUnitName, 
		EPROFILESORTING_TYPE eProfileSorting_Type = EPROFILESORTING_INDEX,
		BOOL bLive = TRUE, 
		unsigned int uiDegree = 0 );
	virtual ~CProfiler_Unit();
	void ClearUnit( void);
	
public:
	unsigned int key;
	bool (CProfiler_Unit::*m_funcSortModule_Ascending) ( const CProfiler_Unit& other );
	bool (CProfiler_Unit::*m_funcSortModule_Descending) ( const CProfiler_Unit& other );

	bool sort_key_ascending(const CProfiler_Unit& other)
	{
		return key < other.key;
	}

	bool sort_key_descending(const CProfiler_Unit& other)
	{
		return key > other.key;
	}

	bool sort_percentage_ascending(const CProfiler_Unit& other)
	{
		return m_fTotalPercentage < other.m_fTotalPercentage;
	}

	bool sort_percentage_descending(const CProfiler_Unit& other)
	{
		return m_fTotalPercentage > other.m_fTotalPercentage;
	}

	bool operator < (const CProfiler_Unit& other) const
	{
		return (this->*m_funcSortModule_Ascending)( other );
	}

	bool operator > (const CProfiler_Unit& other) const
	{
		return (this->*m_funcSortModule_Descending)( other );
	}

protected:
	char m_lpszName[MAX_PROFILESAMPLENAME];
	
	/// @name ��� ����
	LONGLONG m_llStartTick;			///< �ѹ� üũ�ϴ� ������ ����
	LONGLONG m_llSumTime;			///< ���� ��� ���� ���� �� ��
	LONGLONG m_llSumTime_GrandTotal;///< ��������� ����ġ �� ��
	
	/// @name �����ϴ� %
	float m_fLatestPercentage;
	float m_fMaxPercentage;
	float m_fMinPercentage;
	float m_fTotalPercentage;
	
	float m_fAve_ms;			// �� �����ӵ��� ȣ��ð����
	float m_fAve_ms_GrandTotal;
	
	unsigned long m_ulAve_tick;
	unsigned long m_ulAve_tick_GrandTotal;
	
	/// @name ȣ�� ȸ��
	unsigned long m_ulCountInFrame;		///< �� ������ ���� ȣ��� ȸ��
	unsigned long m_ulCountInFrame_Grand;	// ��������� �� ȣ��� ȸ��
	
	unsigned long m_ulLatestCount;		///< �ֱ��� ȣ�� ȸ��
	
	/// @Request Start, End
	BOOL m_bLive;
	BOOL m_bSuccessStart;
	EREQUEST_TYPE m_eRequestType;
	
	/// @Output
	unsigned int m_uiDegree;
	
private:
	void SetLivePseudo();
	
public:

	void SetSortingType( EPROFILESORTING_TYPE eProfileSorting_Type = EPROFILESORTING_INDEX );
	
	void SetRequest( EREQUEST_TYPE eRequest ) { m_eRequestType = eRequest; };
	
	/// @Request Start, End
	BOOL GetLive() { return m_bLive; };
	void SetLive( BOOL bLive ) { m_bLive = bLive; };
	
	
	void BeginUnit_( LONGLONG llTick );
	void EndUnit_( LONGLONG llTick);	
	
	BOOL CheckName( char *lpszName);
	char* GetName( void)	{ return ( m_lpszName); }
	
	void GenerateResult( const LONGLONG &llLastestTotalTime, const LONGLONG &llGrandTotalTime, const LONGLONG &llTickPerMS );
	void GetResult_Percentage( float *pfLatestPercentage, float *pfMaxPercentage, float *pfMinPercentage, float *pfTotalPercentage);
	void GetResult_StatisticAve( float *pfAve_ms, 
		unsigned long *pulAve_tick, 
		float *pfAve_ms_GrandTotal,
		unsigned long *pulAve_tick_GrandTotal );
	
	void CProfiler_Unit::GetResult_AllProperty( unsigned int uiKey, 
		float *pfLatestPercentage, 
		float *pfMaxPercentage, 
		float *pfMinPercentage, 
		float *pfTotalPercentage,
		float *pfAve_ms, 
		unsigned long *pulAve_tick, 
		float *pfAve_ms_GrandTotal, 
		unsigned long *pulAve_tick_GrandTotal );
	
	void FillBlankBuffer( char *szSrcBuffer, const unsigned int uiMaxBuffer );

	void GetResultText_( char *lpszText );
	void GetResultText_Average( char *lpszText );
	void GetResultText_Average_Total( char *lpszText, OUTPUT_OPTION iRequestOutputOption = OUTPUT_OPTION_DEFAULT );
};


#endif // LDS_ADD_DEBUGINGMODULES_FOR_PROFILING