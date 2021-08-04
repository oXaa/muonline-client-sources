// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B9DB83DB_A9ZD_12D0_BFJ1_447553540000__INCLUDED_)
#define AFX_STDAFX_H__B9DB83DB_A9ZD_12D0_BFJ1_447553540000__INCLUDED_

//#define KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE

//warining
#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4800 ) 
#pragma warning( disable : 4244 )
#pragma warning( disable : 4237 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4503 ) 
#ifdef _VS2008PORTING
	#pragma warning( disable : 4819 )
	#pragma warning( disable : 4505 )		// ���� ���� ���� ���� �Լ��� ����
	#pragma warning( disable : 4100 )		// ���� ���� ���� ���� �Ű� ����
	#pragma warning( disable : 4127 )		// ���ǽ��� �����
	#pragma warning( disable : 4702 )		// ������ �� ���� �ڵ�
	//#pragma warning( disable : 4018 )
	//#pragma warning( disable : 4482 )
	//#pragma warning( disable : 4700 )
	//#pragma warning( disable : 4748 )
	//#pragma warning( disable : 4786 )	// GlobalBitmap.h ���� �Űܿ�
#endif // _VS2008PORTING

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN	

#ifdef _VS2008PORTING

	#ifndef POINTER_64
		#define POINTER_64
	#endif // POINTER_64
	
	#ifndef _USE_32BIT_TIME_T
		#define _USE_32BIT_TIME_T
	#endif //_USE_32BIT_TIME_T

	// _VS2008PORTING���� �������� ��ȭ�� CRT�Լ� ��� �ǰ� warning ����
	// (�������� ���ο� �Լ��� ���� �����Ͽ��� �Ѵ�.!!!)
	#define _CRT_SECURE_NO_DEPRECATE
	#define _CRT_NONSTDC_NO_DEPRECATE

	// Debug Iterator ���� ������ - Debug������ ���ư�.
// 	#undef _HAS_ITERATOR_DEBUGGING
// 	#define _HAS_ITERATOR_DEBUGGING 0

// #ifdef _DEBUG
// 	// Checked Iterator ���� ������ - Debug/Release ��ε��ư�(Release������ off)
// 	#undef _SECURE_SCL
// 	#define _SECURE_SCL 0
// #endif // _DEBUG
#endif // _VS2008PORTING

#ifdef _VS2008PORTING
//===================================================================
// �ҷ��� ���ϵ��� ��� ���� 3���� �Ѵ�
//===================================================================
#pragma warning( push, 3 )
#endif // _VS2008PORTING

#include <windows.h>
#ifndef KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE
//windows
#include <WinSock2.h>
#include <mmsystem.h>
#include <shellapi.h>

//c runtime
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <mbstring.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <conio.h>

//zzzai file cpp ���� ���� ����..�� ����ص� ��..
//#include <iostream.h>

// ���̺귯�� ���̴°� ����.
//stl
#ifdef _DEBUG		// Debug���
#include <string>
#include <list>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
#include <queue>
#else // _DEBUG		// Release���
#ifdef _MT			
#undef _MT
#include <string>
#include <list>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
#include <queue>
#define _MT
#else //_MT
#include <string>
#include <list>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
#include <queue>
#endif // _MT
#endif // _DEBUG

#ifdef _VS2008PORTING
//===================================================================
// �� �� ���ϵ��� ������Ʈ �ɼǿ� ������
//===================================================================
#pragma warning( pop )
#endif // _VS2008PORTING

#include <boost/smart_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/format.hpp>
#include <boost/any.hpp>
#include <boost/array.hpp>
// vc ���׷� ������ ������ �� ���� �����ٰ� �ɾ��ֵ��� ����.
//#include <boost/tokenizer.hpp>
#include <boost/pool/object_pool.hpp>

//opengl
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glaux.h>
//#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
#include <glext.h>
#include <wglext.h>
#include <glprocs.h>
// #else // KJH_MOD_LIBRARY_LINK_EACH_NATION
// #include "glext.h"
// #include "wglext.h"
// #include "glprocs.h"
// #endif // KJH_MOD_LIBRARY_LINK_EACH_NATION

//util
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)  { if(p) { delete [] (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define DIRECTINPUT_VERSION	0x0800

// namespace
using namespace std;//iosteam�̶� ���ļ�...
using namespace boost;

//patch
//winmain �Լ����� ���� �Űܰ���
#include "Winmain.h"
#include "Winmain_New.h"
#include "Winmain_New_Live.h"

#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
//----------------------------------------------------------------------------- Eng
// Eng
#if _LANGUAGE_ENG
	#include "Defined_Global.h"
//----------------------------------------------------------------------------- Tai
// Tai
#elif _LANGUAGE_TAI
	#include "Winmain_New_Foreign.h"
//----------------------------------------------------------------------------- Chs
// Chs
#elif _LANGUAGE_CHS
	#include "Winmain_New_Foreign.h"
//----------------------------------------------------------------------------- Jpn
// Jpn
#elif _LANGUAGE_JPN
	#include "Winmain_New_Foreign.h"
//----------------------------------------------------------------------------- Tha
// Tha
#elif _LANGUAGE_THA
	#include "Winmain_New_Foreign.h"
//----------------------------------------------------------------------------- Phi
// Phi
#elif _LANGUAGE_PHI
	#include "Winmain_New_Foreign.h"
//----------------------------------------------------------------------------- Vie
// Vie
#elif _LANGUAGE_VIE
	#include "Winmain_New_Foreign.h"
#endif
//-----------------------------------------------------------------------------
#else // KJH_MOD_LIBRARY_LINK_EACH_NATION
#if SELECTED_LANGUAGE != LANGUAGE_KOREAN
	#include "Winmain_New_Foreign.h"
// mix ���� ���������� �ٲٸ� �ű��...
#endif //SELECTED_LANGUAGE != LANGUAGE_KOREAN
#endif // KJH_MOD_LIBRARY_LINK_EACH_NATION

#include "Winmain_New_Event.h"

//client
#include "_define.h"
#include "_enum.h"
#include "_types.h"
#include "_struct.h"

#ifdef NEW_USER_INTERFACE

	#include "w_structs.h"
	//util
	#include "w_Coord.h"
	#include "w_Rect.h"
	#include "w_Color.h"
	#include "w_ObjectPool.h"
	#include "w_EventPublisher.h"
	#include "w_build.h"
	#include "stlutl.h"  //����..
	//input
	#include "w_InputTypes.h"
	#include "w_InputMessageHandler.h"
	//namespace
	using namespace util;
	using namespace input;
	//ui
	#include "w_UIType.h"
	#include "w_UIdefines.h"
	//client
	#include "w_Task.h"
	#include "w_Module.h"

#endif //NEW_USER_INTERFACE
	
#include "w_WindowMessageHandler.h"
#include "_GlobalFunctions.h"
#include "_TextureIndex.h"	
#include "InfoHelperFunctions.h"
#include "UIDefaultBase.h"
#include "NewUICommon.h"
#include "./Math/ZzzMathLib.h"
#include "ZzzOpenglUtil.h"

#endif // KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE		// #ifndef

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B9DB83DB_A9ZD_12D0_BFJ1_447553540000__INCLUDED_)
