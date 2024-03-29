
#include "stdafx.h"

#include "NewUIManager.h"

#ifdef LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM
#include "./Utilities/Log/ErrorReport.h"
#endif // LDS_ADD_OUTPUTERRORLOG_WHEN_RECEIVEREFRESHPERSONALSHOPITEM

using namespace SEASON3B;

SEASON3B::CNewUIManager::CNewUIManager() 
{
	m_pActiveMouseUIObj = NULL;
	m_pActiveKeyUIObj = NULL;
#ifdef PBG_MOD_STAMINA_UI
	m_nShowUICnt =0;
#endif //PBG_MOD_STAMINA_UI
}

SEASON3B::CNewUIManager::~CNewUIManager() 
{ 
	RemoveAllUIObjs(); 
}

void SEASON3B::CNewUIManager::AddUIObj(DWORD dwKey, CNewUIObj* pUIObj)
{
	type_map_uibase::iterator mi = m_mapUI.find(dwKey);
	if(mi == m_mapUI.end())
	{
		m_vecUI.push_back(pUIObj);
		m_mapUI.insert( type_map_uibase::value_type(dwKey, pUIObj) );
	}
}

void SEASON3B::CNewUIManager::RemoveUIObj(DWORD dwKey)
{
	type_map_uibase::iterator mi = m_mapUI.find(dwKey);
	if(mi != m_mapUI.end())
	{
		type_vector_uibase::iterator vi = std::find(m_vecUI.begin(), m_vecUI.end(), (*mi).second);
		if(vi != m_vecUI.end())
		{
			m_vecUI.erase(vi);
		}
		m_mapUI.erase(mi);
	}
}

void SEASON3B::CNewUIManager::RemoveUIObj(CNewUIObj* pUIObj)
{
	type_map_uibase::iterator mi = m_mapUI.begin();
	for(; mi != m_mapUI.end(); mi++)
	{
		if((*mi).second == pUIObj)
		{
			m_mapUI.erase(mi);
			break;
		}
	}
		
	type_vector_uibase::iterator vi = std::find(m_vecUI.begin(), m_vecUI.end(), pUIObj);
	if(vi != m_vecUI.end())
	{
		m_vecUI.erase(vi);
	}
}

void SEASON3B::CNewUIManager::RemoveAllUIObjs()
{
#if defined(_DEBUG) && defined(LDS_FIX_MEMORYLEAK_WHERE_NEWUI_DEINITIALIZE)
	
	{
#ifndef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		unsigned int uiUICNT = m_vecUI.size();
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
		unsigned int uiUIManageCNT = m_mapUI.size();
		
		type_map_uibase::iterator mi = m_mapUI.begin();
		for( ; mi != m_mapUI.end(); ++mi )
		{
			DWORD dwKey = (*mi).first;
			CNewUIObj* pUIObj = (*mi).second;
			if( pUIObj != NULL )
			{
			#ifdef KWAK_ADD_TRACE_FUNC
				__TraceF(TEXT("UI클래스 컴포넌트 중 삭제 안된것(갯수:%d)이 있습니다. 종종 뮤DEAD의 원인이 됩니다. UIKEY(%d) : mapUI \n"), uiUIManageCNT, dwKey);
			#endif // KWAK_ADD_TRACE_FUNC
			}
		}
		
		type_vector_uibase::iterator vi = m_vecUI.begin();
		for( ; vi < m_vecUI.end(); ++vi )
		{
			CNewUIObj* pUIObj = (*vi);
			if( pUIObj != NULL )
			{
			#ifdef KWAK_ADD_TRACE_FUNC
				__TraceF(TEXT("UI클래스 컴포넌트 중 삭제 안된것(갯수:%d)이 있습니다. 종종 뮤DEAD의 원인이 됩니다. vecUI \n"), uiUIManageCNT);
			#endif // KWAK_ADD_TRACE_FUNC
			}
		}
	}

#endif // defined(_DEBUG) && defined(LDS_FIX_MEMORYLEAK_WHERE_NEWUI_DEINITIALIZE)
	m_vecUI.clear();
	m_mapUI.clear();
}

CNewUIObj* SEASON3B::CNewUIManager::FindUIObj(DWORD dwKey)
{
	type_map_uibase::iterator mi = m_mapUI.find(dwKey);
	if(mi != m_mapUI.end())
		return (*mi).second;
	return NULL;
}

bool SEASON3B::CNewUIManager::UpdateMouseEvent()
{
	m_pActiveMouseUIObj = NULL;

	std::sort(m_vecUI.begin(), m_vecUI.end(), CompareLayerDepthReverse);
	
	type_vector_uibase::iterator vi = m_vecUI.begin();
	vi = m_vecUI.begin();
	for(; vi != m_vecUI.end(); vi++)
	{
		if((*vi)->IsVisible()) 
		{
#ifdef LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
			CNewUIObj *obj_backup = (*vi);
			bool bResult = (*vi)->UpdateMouseEvent();
			
			type_vector_uibase::iterator vi2 = std::find(m_vecUI.begin(), m_vecUI.end(), obj_backup);
			if( vi2 != m_vecUI.end() )
			{
				vi = vi2;
			}
			else
			{
				break;
			}

			if( bResult == false )
			{
				m_pActiveMouseUIObj = *vi;
				return false;
			}
#else // LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
 			if(false == (*vi)->UpdateMouseEvent())
 			{
 				m_pActiveMouseUIObj = (*vi);
 				return false;		//. stop calling UpdateMouseEvent functions
 			}
#endif // LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
		}
	}

	return true;
}

bool SEASON3B::CNewUIManager::UpdateKeyEvent()
{
	m_pActiveKeyUIObj = NULL;
	std::sort(m_vecUI.begin(), m_vecUI.end(), CompareKeyEventOrder);
	
	type_vector_uibase::iterator vi = m_vecUI.begin();
	for(; vi != m_vecUI.end(); vi++)
	{
		HWND hRelatedWnd = (*vi)->GetRelatedWnd();
		if(NULL == hRelatedWnd)
		{
			hRelatedWnd = g_hWnd;
		}

		HWND hWnd = GetFocus();

		if((*vi)->IsEnabled() && hWnd == hRelatedWnd)
		{
#ifdef LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
			CNewUIObj *obj_backup = (*vi);
			bool bResult = (*vi)->UpdateKeyEvent();

			type_vector_uibase::iterator vi2 = std::find(m_vecUI.begin(), m_vecUI.end(), obj_backup);
			if( vi2 != m_vecUI.end() )
			{
				vi = vi2;
			}
			else
			{
				break;
			}

			if( bResult == false )
			{
				m_pActiveMouseUIObj = *vi;
				return false;
			}
#else // LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
			if(false == (*vi)->UpdateKeyEvent())
			{
				m_pActiveKeyUIObj = (*vi);
				return false;		//. stop calling UpdateKeyEvent functions
			}
#endif // LJH_FIX_DEREFERENCE_VECTOR_ITER_FOR_DELETED_UI_OBJ
		}
	}
	return true;
}

bool SEASON3B::CNewUIManager::Update()
{
	std::sort(m_vecUI.begin(),m_vecUI.end(), CompareLayerDepth);
	
	type_vector_uibase::iterator vi = m_vecUI.begin();
	for(; vi != m_vecUI.end(); vi++)
	{
		if((*vi)->IsEnabled()) 
		{
			if(false == (*vi)->Update())
			{
				return false;		//. stop calling Update functions
			}
		}
	}

	return true;
}

bool SEASON3B::CNewUIManager::Render()
{
	std::sort(m_vecUI.begin(),m_vecUI.end(), CompareLayerDepth);
	
	type_vector_uibase::iterator vi = m_vecUI.begin();
	for(; vi != m_vecUI.end(); vi++)
	{
		if((*vi)->IsVisible()) 
		{
			(*vi)->Render();

			// Render() 함수에서 false를 리턴하면 다음 객체부터 Render() 함수 호출 안하는 루틴 제거 (아직까지 사용예를 못봄)
// 			if(false == (*vi)->Render())
// 			{
// 				return false;		//. stop rendering
// 			}
		}
	}

	return true;
}

CNewUIObj* SEASON3B::CNewUIManager::GetActiveMouseUIObj()
{ 
	return m_pActiveMouseUIObj; 
}

CNewUIObj* SEASON3B::CNewUIManager::GetActiveKeyUIObj()
{ 
	return m_pActiveKeyUIObj; 
}

void SEASON3B::CNewUIManager::ResetActiveUIObj()
{
	m_pActiveMouseUIObj = NULL;
	m_pActiveKeyUIObj = NULL;
}

bool SEASON3B::CNewUIManager::IsInterfaceVisible(DWORD dwKey)
{
	CNewUIObj* pObj = FindUIObj(dwKey);
	if(NULL == pObj)
	{
		return false;
	}
	return pObj->IsVisible();
}

bool SEASON3B::CNewUIManager::IsInterfaceEnabled(DWORD dwKey)
{
	CNewUIObj* pObj = FindUIObj(dwKey);
	if(NULL == pObj)
		return false;
	return pObj->IsEnabled();
}

void SEASON3B::CNewUIManager::ShowInterface(DWORD dwKey, bool bShow/* = true*/)
{
	CNewUIObj* pObj = FindUIObj(dwKey);
	if(NULL != pObj)
		pObj->Show(bShow);
}

void SEASON3B::CNewUIManager::EnableInterface(DWORD dwKey, bool bEnable/* = true*/)
{
	CNewUIObj* pObj = FindUIObj(dwKey);
	if(NULL != pObj)
		pObj->Enable(bEnable);
}

void SEASON3B::CNewUIManager::ShowAllInterfaces(bool bShow/* = true*/)
{
	type_map_uibase::iterator mi = m_mapUI.begin();
	for(; mi != m_mapUI.end(); mi++)
		(*mi).second->Show(bShow);
}

void SEASON3B::CNewUIManager::EnableAllInterfaces(bool bEnable/* = true*/)
{
	type_map_uibase::iterator mi = m_mapUI.begin();
	for(; mi != m_mapUI.end(); mi++)
		(*mi).second->Show(bEnable);
}

bool SEASON3B::CNewUIManager::CompareLayerDepth(INewUIBase* pObj1,INewUIBase* pObj2)
{ 
	return pObj1->GetLayerDepth() < pObj2->GetLayerDepth(); 
}

bool SEASON3B::CNewUIManager::CompareLayerDepthReverse(INewUIBase* pObj1,INewUIBase* pObj2)
{ 
	return pObj1->GetLayerDepth() > pObj2->GetLayerDepth(); 
}

bool SEASON3B::CNewUIManager::CompareKeyEventOrder(INewUIBase* pObj1,INewUIBase* pObj2)
{
	return pObj1->GetKeyEventOrder() > pObj2->GetKeyEventOrder();
}

#ifdef PBG_MOD_STAMINA_UI
int SEASON3B::CNewUIManager::GetShowUICnt()
{
	int m_nShowUICnt=0;
	// 일부 특정 인터페이스가 몇개 열려있는지
	for(int i=INTERFACE_PARTY; i<INTERFACE_CHARACTER+1; ++i)
	{
		if(IsInterfaceVisible(i))
			m_nShowUICnt++;
	}
	return m_nShowUICnt;
}
#endif //PBG_MOD_STAMINA_UI
