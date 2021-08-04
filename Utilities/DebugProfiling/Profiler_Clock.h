// Profiler_Clock.h: interface for the CProfiler_Clock class.
//
//////////////////////////////////////////////////////////////////////

#ifdef LDS_ADD_DEBUGINGMODULES_FOR_PROFILING

#if !defined(AFX_PROFILER_CLOCK_H__D0EAE5F8_6D19_4487_AF5A_6C764507B973__INCLUDED_)
#define AFX_PROFILER_CLOCK_H__D0EAE5F8_6D19_4487_AF5A_6C764507B973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wtypes.h>

#include <assert.h>

#include "debugSingleton_.h"


#define CFS_MOVE		( 0x0001)
#define CFS_RENDER		( 0x0002)


class CProfiler_Clock : public CdebugSingleton_<CProfiler_Clock>
{
public:
	CProfiler_Clock();
	virtual ~CProfiler_Clock();
	virtual void Clear( void);

	/// @name ��е� tick ���
public:
	virtual LONGLONG GetCustomTick() const
	{
		//DWORD dwLow, dwHigh;
		//_asm
		//{
		//	rdtsc
		//	mov dwLow, eax
		//	mov dwHigh, edx
		//}
		//return ( ( ( unsigned __int64)dwHigh << 32) | ( unsigned __int64)dwLow);
		LARGE_INTEGER liCounter;
		QueryPerformanceCounter( &liCounter);
		return ( ( UINT64)liCounter.QuadPart);
	}

	/// @name ��е� tick �� ���� tick �� ���� ����
protected:
	LONGLONG m_llMeasureCustomTick;
	DWORD m_dwMeasureTick;
public:
	virtual void BeginMeasureTick( void);
	virtual void EndMeasureTick( void);
	virtual void AutoMeasure( DWORD dwMillisecond);	///< EndMeasure ����, ���� �ð��� ������ �ڵ����� ���

	/// @name ��е� tick �̿��ϱ�
protected:
	BOOL m_bCustomTickMeasured;	///< measure �Ϸ�
	LONGLONG m_llCustomTickPerMillisecond;	///< 1 ms �� ƽ
public:
	virtual BOOL IsMeasureComplete() const { return ( m_bCustomTickMeasured); }
	virtual LONGLONG GetCustomTickPerMillisecond() const { return ( m_llCustomTickPerMillisecond); }
	virtual DWORD CustomTick2Millisecond( LONGLONG llTick) const
	{
		return ( ( DWORD)( llTick / m_llCustomTickPerMillisecond));
	}
	virtual LONGLONG Millisecond2CustomTick( DWORD dwTick) const
	{
		return ( dwTick * m_llCustomTickPerMillisecond);
	}
	virtual DWORD GetCurrentTick() const	///< GetTickCount ��� �̿� ���� (��, ���� ������ �ȿ����� ������ �ʴ´�.)
	{
		return ( ( DWORD)( m_llLatestFrameTick / m_llCustomTickPerMillisecond));
	}
	virtual DWORD GetTickCount() const	///< GetTickCount ��� �̿� ���� (��, ���� ������ �ȿ����� ���Ѵ�.)
	{
		return ( ( DWORD)( GetCustomTick() / m_llCustomTickPerMillisecond));
	}

	/// @name Frame skipping
protected:
	LONGLONG m_llLatestFrameTick;	///< �ֱ� �������� tick
	DWORD m_dwLatestFrameMoveTick;	///< CheckFrameSkipping �� ��� move �� ��� �ֱ� tick ����
	DWORD m_dwLatestRenderTick;		///< �ֱٿ� render �� tick ���� (render ���� move �� �Ǵ� ��� ����)
	int m_iFramePerSecond;			///< ��� �ʴ� ������
	BOOL m_bEnableRenderOnly;		///< Render �� �ϴ� ��쵵 �ְ� �� ������ ����
	long m_lFrameCount;				///< ������ ����
	int m_iMinFramePerSecond;
	BOOL m_bFixedFrame;
	DWORD m_dwBaseTick;
	BOOL m_bUpdateClock;

public:
	// �ʴ� ������ ����
	virtual BOOL SetFramePerSecond( int iMaxFramePerSecond, BOOL bEnableRenderOnly = TRUE, 
		int iMinFramePerSecond = 0, BOOL bFixedFrame = TRUE);	///< Move ���� fps ����

	//virtual BOOL New_SetFramePerSecond( int iMinFramePerSecond, int iMaxFramePerSecond, BOOL bEnableRenderOnly = TRUE);
	virtual int GetFramePerSecond() const	{ return ( m_iFramePerSecond); }
	virtual WORD CheckFrameSkipping( DWORD *pdwTick);	///< Move �� Render �� �� �� �ִ� �� ���
	virtual void Reset( void);
	virtual long GetFrameCount() const	{ return ( m_lFrameCount); }

	// add 2006.6.9 by koma0
	//{
	virtual DWORD GetFrameMoveTick() const { return GetPassTick( m_dwLatestFrameMoveTick, m_dwBaseTick); }
	virtual DWORD GetRenderTick() const 
	{ 
		// fix 2007.8.17 by koma0
		// x_Clock�� ������� ���� �� RenderTick���� GetCurrentTick
		return ( m_bUpdateClock) ? GetPassTick( m_dwLatestRenderTick, m_dwBaseTick) : GetTickCount();
	}
protected:
	enum { TICK_MAXVALUE = 0xffffffff };
	DWORD GetPassTick( DWORD dwTickTo, DWORD dwTickFrom) const
	{
		return ( dwTickTo < dwTickFrom) ? TICK_MAXVALUE - ( dwTickFrom - dwTickTo) : dwTickTo - dwTickFrom;
	}
	//}

};

#endif // !defined(AFX_PROFILER_CLOCK_H__D0EAE5F8_6D19_4487_AF5A_6C764507B973__INCLUDED_)

#endif // LDS_ADD_DEBUGINGMODULES_FOR_PROFILING