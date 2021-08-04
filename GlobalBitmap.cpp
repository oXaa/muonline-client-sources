// GlobalBitmap.cpp: implementation of the CGlobalBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "GlobalBitmap.h"
#include "./Utilities/Log/ErrorReport.h"
#include "./Utilities/Log/muConsoleDebug.h"

#if defined(MR0) & defined(_DEBUG)
#include "VPManager.h"
#endif // defined(MR0) & defined(_DEBUG)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapCache::CBitmapCache() 
{
	memset(m_QuickCache, 0, sizeof(QUICK_CACHE)*NUMBER_OF_QUICK_CACHE);
}
CBitmapCache::~CBitmapCache() { Release(); }

bool CBitmapCache::Create()
{
	Release();

	//////////////////////////////////////////////////////////////////////////
	//. QuickCache ����
	DWORD dwRange = 0;

	//. ��Ÿ��
	dwRange =  BITMAP_MAPTILE_END - BITMAP_MAPTILE_BEGIN;
	m_QuickCache[QUICK_CACHE_MAPTILE].dwBitmapIndexMin = BITMAP_MAPTILE_BEGIN;
	m_QuickCache[QUICK_CACHE_MAPTILE].dwBitmapIndexMax = BITMAP_MAPTILE_END;
	m_QuickCache[QUICK_CACHE_MAPTILE].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_MAPTILE].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_MAPTILE].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. �ʱ۷���
	dwRange =  BITMAP_MAPGRASS_END - BITMAP_MAPGRASS_BEGIN;
	m_QuickCache[QUICK_CACHE_MAPGRASS].dwBitmapIndexMin = BITMAP_MAPGRASS_BEGIN;
	m_QuickCache[QUICK_CACHE_MAPGRASS].dwBitmapIndexMax = BITMAP_MAPGRASS_END;
	m_QuickCache[QUICK_CACHE_MAPGRASS].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_MAPGRASS].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_MAPGRASS].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. �ʿ���
	dwRange =  BITMAP_WATER_END - BITMAP_WATER_BEGIN;
	m_QuickCache[QUICK_CACHE_WATER].dwBitmapIndexMin = BITMAP_WATER_BEGIN;
	m_QuickCache[QUICK_CACHE_WATER].dwBitmapIndexMax = BITMAP_WATER_END;
	m_QuickCache[QUICK_CACHE_WATER].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_WATER].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_WATER].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. ���콺 Ŀ��
	dwRange = BITMAP_CURSOR_END - BITMAP_CURSOR_BEGIN;
	m_QuickCache[QUICK_CACHE_CURSOR].dwBitmapIndexMin = BITMAP_CURSOR_BEGIN;
	m_QuickCache[QUICK_CACHE_CURSOR].dwBitmapIndexMax = BITMAP_CURSOR_END;
	m_QuickCache[QUICK_CACHE_CURSOR].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_CURSOR].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_CURSOR].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. ��Ʈ
	dwRange = BITMAP_FONT_END - BITMAP_FONT_BEGIN;
	m_QuickCache[QUICK_CACHE_FONT].dwBitmapIndexMin = BITMAP_FONT_BEGIN;
	m_QuickCache[QUICK_CACHE_FONT].dwBitmapIndexMax = BITMAP_FONT_END;
	m_QuickCache[QUICK_CACHE_FONT].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_FONT].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_FONT].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. ����������
	dwRange = BITMAP_INTERFACE_NEW_MAINFRAME_END - BITMAP_INTERFACE_NEW_MAINFRAME_BEGIN;
	m_QuickCache[QUICK_CACHE_MAINFRAME].dwBitmapIndexMin = BITMAP_INTERFACE_NEW_MAINFRAME_BEGIN;
	m_QuickCache[QUICK_CACHE_MAINFRAME].dwBitmapIndexMax = BITMAP_INTERFACE_NEW_MAINFRAME_END;
	m_QuickCache[QUICK_CACHE_MAINFRAME].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_MAINFRAME].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_MAINFRAME].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//. ��ų������
	dwRange = BITMAP_INTERFACE_NEW_SKILLICON_END - BITMAP_INTERFACE_NEW_SKILLICON_BEGIN;
	m_QuickCache[QUICK_CACHE_SKILLICON].dwBitmapIndexMin = BITMAP_INTERFACE_NEW_SKILLICON_BEGIN;
	m_QuickCache[QUICK_CACHE_SKILLICON].dwBitmapIndexMax = BITMAP_INTERFACE_NEW_SKILLICON_END;
	m_QuickCache[QUICK_CACHE_SKILLICON].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_SKILLICON].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_SKILLICON].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));
	
	//. �÷��̾� �ؽ�Ʈ
	dwRange = BITMAP_PLAYER_TEXTURE_END - BITMAP_PLAYER_TEXTURE_BEGIN;
	m_QuickCache[QUICK_CACHE_PLAYER].dwBitmapIndexMin = BITMAP_PLAYER_TEXTURE_BEGIN;
	m_QuickCache[QUICK_CACHE_PLAYER].dwBitmapIndexMax = BITMAP_PLAYER_TEXTURE_END;
	m_QuickCache[QUICK_CACHE_PLAYER].dwRange = dwRange;
	m_QuickCache[QUICK_CACHE_PLAYER].ppBitmap = new BITMAP_t* [dwRange];
	memset(m_QuickCache[QUICK_CACHE_PLAYER].ppBitmap, 0, dwRange*sizeof(BITMAP_t*));

	//////////////////////////////////////////////////////////////////////////

	m_pNullBitmap = new BITMAP_t;
	memset(m_pNullBitmap, 0, sizeof(BITMAP_t));

	m_ManageTimer.SetTimer(1500);

	return true;
}
void CBitmapCache::Release()
{
	SAFE_DELETE(m_pNullBitmap);

	RemoveAll();

	for(int i=0; i<NUMBER_OF_QUICK_CACHE; i++)
	{
		if(m_QuickCache[i].ppBitmap)
			delete [] m_QuickCache[i].ppBitmap;
	}
	memset(m_QuickCache, 0, sizeof(QUICK_CACHE)*NUMBER_OF_QUICK_CACHE);
}

void CBitmapCache::Add(GLuint uiBitmapIndex, BITMAP_t* pBitmap)
{
	//. �����ϴٸ�, ��ĳ���� ����Ѵ�.
	for(int i=0; i<NUMBER_OF_QUICK_CACHE; i++)
	{
		if(uiBitmapIndex > m_QuickCache[i].dwBitmapIndexMin && uiBitmapIndex < m_QuickCache[i].dwBitmapIndexMax)
		{
			DWORD dwVI = uiBitmapIndex - m_QuickCache[i].dwBitmapIndexMin;
			if(pBitmap)
				m_QuickCache[i].ppBitmap[dwVI] = pBitmap;
			else
				m_QuickCache[i].ppBitmap[dwVI] = m_pNullBitmap;
			return;		//. ��� �Ϸ�
		}
	}
	if(pBitmap)
	{
		if(BITMAP_PLAYER_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_PLAYER_TEXTURE_END >= uiBitmapIndex)
			m_mapCachePlayer.insert(type_cache_map::value_type(uiBitmapIndex, pBitmap));
		else if(BITMAP_INTERFACE_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_INTERFACE_TEXTURE_END >= uiBitmapIndex)
			m_mapCacheInterface.insert(type_cache_map::value_type(uiBitmapIndex, pBitmap));
		else if(BITMAP_EFFECT_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_EFFECT_TEXTURE_END >= uiBitmapIndex)
			m_mapCacheEffect.insert(type_cache_map::value_type(uiBitmapIndex, pBitmap));
		else
			m_mapCacheMain.insert(type_cache_map::value_type(uiBitmapIndex, pBitmap));
	}
}
void CBitmapCache::Remove(GLuint uiBitmapIndex)
{
	//. ��ĳ���� �ִٸ� �����Ѵ�.
	for(int i=0; i<NUMBER_OF_QUICK_CACHE; i++)
	{
		if(uiBitmapIndex > m_QuickCache[i].dwBitmapIndexMin && uiBitmapIndex < m_QuickCache[i].dwBitmapIndexMax)
		{
			DWORD dwVI = uiBitmapIndex - m_QuickCache[i].dwBitmapIndexMin;
			m_QuickCache[i].ppBitmap[dwVI] = NULL;
			return;		//. ���� �Ϸ�
		}
	}

	//. ���ٸ� ��ĳ������ �˻�
	if(BITMAP_PLAYER_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_PLAYER_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCachePlayer.find(uiBitmapIndex);
		if(mi != m_mapCachePlayer.end())
			m_mapCachePlayer.erase(mi);
	}
	else if(BITMAP_INTERFACE_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_INTERFACE_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCacheInterface.find(uiBitmapIndex);
		if(mi != m_mapCacheInterface.end())
			m_mapCacheInterface.erase(mi);
	}
	else if(BITMAP_EFFECT_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_EFFECT_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCacheEffect.find(uiBitmapIndex);
		if(mi != m_mapCacheEffect.end())
			m_mapCacheEffect.erase(mi);
	}
	else
	{
		type_cache_map::iterator mi = m_mapCacheMain.find(uiBitmapIndex);
		if(mi != m_mapCacheMain.end())
			m_mapCacheMain.erase(mi);
	}
}
void CBitmapCache::RemoveAll()
{
	for(int i=0; i<NUMBER_OF_QUICK_CACHE; i++)
	{
		memset(m_QuickCache[i].ppBitmap, 0, m_QuickCache[i].dwRange*sizeof(BITMAP_t*));
	}
	m_mapCacheMain.clear();
	m_mapCachePlayer.clear();
	m_mapCacheInterface.clear();
	m_mapCacheEffect.clear();
}

size_t CBitmapCache::GetCacheSize()
{ 
	return m_mapCacheMain.size() + m_mapCachePlayer.size() + 
		m_mapCacheInterface.size() + m_mapCacheEffect.size(); 
}

void CBitmapCache::Update()
{
	m_ManageTimer.UpdateTime();

	if(m_ManageTimer.IsTime())	//. 1.5�ʿ� �ѹ�
	{
		//. Main Map Cache
		type_cache_map::iterator mi = m_mapCacheMain.begin();
		for(; mi != m_mapCacheMain.end(); )
		{
			BITMAP_t* pBitmap = (*mi).second;
			if(pBitmap->dwCallCount > 0)
			{
				pBitmap->dwCallCount = 0;
				mi++;
			}
			else
			{
				//. ������� �ʴ°͵��� ĳ������ �����Ѵ�.
				mi = m_mapCacheMain.erase(mi);
			}
		}

		//. Player Map Cache
		mi = m_mapCachePlayer.begin();
		for(; mi != m_mapCachePlayer.end(); )
		{
			BITMAP_t* pBitmap = (*mi).second;

			if(pBitmap->dwCallCount > 0)
			{
				pBitmap->dwCallCount = 0;
				mi++;
			}
			else
			{
				//. ������� �ʴ°͵��� ĳ������ �����Ѵ�.
				mi = m_mapCachePlayer.erase(mi);
			}
		}

		//. Interface Map Cache
		mi = m_mapCacheInterface.begin();
		for(; mi != m_mapCacheInterface.end(); )
		{
			BITMAP_t* pBitmap = (*mi).second;
			if(pBitmap->dwCallCount > 0)
			{
				pBitmap->dwCallCount = 0;
				mi++;
			}
			else
			{
				//. ������� �ʴ°͵��� ĳ������ �����Ѵ�.
				mi = m_mapCacheInterface.erase(mi);
			}
		}

		//. Effect Map Cache
		mi = m_mapCacheEffect.begin();
		for(; mi != m_mapCacheEffect.end(); )
		{
			BITMAP_t* pBitmap = (*mi).second;
			if(pBitmap->dwCallCount > 0)
			{
				pBitmap->dwCallCount = 0;
				mi++;
			}
			else
			{
				//. ������� �ʴ°͵��� ĳ������ �����Ѵ�.
				mi = m_mapCacheEffect.erase(mi);
			}
		}

#ifdef DEBUG_BITMAP_CACHE
		g_ConsoleDebug->Write(MCD_NORMAL, "M,P,I,E : (%d, %d, %d, %d)", m_mapCacheMain.size(), 
			m_mapCachePlayer.size(), m_mapCacheInterface.size(), m_mapCacheEffect.size());
#endif // DEBUG_BITMAP_CACHE
	}
}

bool CBitmapCache::Find(GLuint uiBitmapIndex, BITMAP_t** ppBitmap)
{
	//. ��ĳ���� �ִٸ� ã�´�.
	for(int i=0; i<NUMBER_OF_QUICK_CACHE; i++)
	{
		if(uiBitmapIndex > m_QuickCache[i].dwBitmapIndexMin && 
			uiBitmapIndex < m_QuickCache[i].dwBitmapIndexMax)
		{
			DWORD dwVI = uiBitmapIndex - m_QuickCache[i].dwBitmapIndexMin;
			if(m_QuickCache[i].ppBitmap[dwVI])
			{
				if(m_QuickCache[i].ppBitmap[dwVI] == m_pNullBitmap)	//. ã������ Null ��Ʈ���̶��
					*ppBitmap = NULL;
				else
				{
					*ppBitmap = m_QuickCache[i].ppBitmap[dwVI];
				}
				return true;
			}
			return false;
		}
	}

	//. ���ٸ� ��ĳ������ �˻�
	if(BITMAP_PLAYER_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_PLAYER_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCachePlayer.find(uiBitmapIndex);
		if(mi != m_mapCachePlayer.end())
		{
			*ppBitmap = (*mi).second;
			(*ppBitmap)->dwCallCount++;
			return true;
		}
	}
	else if(BITMAP_INTERFACE_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_INTERFACE_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCacheInterface.find(uiBitmapIndex);
		if(mi != m_mapCacheInterface.end())
		{
			*ppBitmap = (*mi).second;
			(*ppBitmap)->dwCallCount++;
			return true;
		}
	}
	else if(BITMAP_EFFECT_TEXTURE_BEGIN <= uiBitmapIndex && BITMAP_EFFECT_TEXTURE_END >= uiBitmapIndex)
	{
		type_cache_map::iterator mi = m_mapCacheEffect.find(uiBitmapIndex);
		if(mi != m_mapCacheEffect.end())
		{
			*ppBitmap = (*mi).second;
			(*ppBitmap)->dwCallCount++;
			return true;
		}
	}
	else
	{
		type_cache_map::iterator mi = m_mapCacheMain.find(uiBitmapIndex);
		if(mi != m_mapCacheMain.end())
		{
			*ppBitmap = (*mi).second;
			(*ppBitmap)->dwCallCount++;
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////////// CGlobalBitmap
CGlobalBitmap::CGlobalBitmap() 
{ 
	Init();
	m_BitmapCache.Create();

#ifdef DEBUG_BITMAP_CACHE
	m_DebugOutputTimer.SetTimer(5000);
#endif // DEBUG_BITMAP_CACHE
}
CGlobalBitmap::~CGlobalBitmap() 
{ 
	UnloadAllImages();
}
void CGlobalBitmap::Init()
{
	m_uiAlternate = 0;
	m_uiTextureIndexStream = BITMAP_NONAMED_TEXTURES_BEGIN;
	m_dwUsedTextureMemory = 0;
}

GLuint CGlobalBitmap::LoadImage(const std::string& filename, GLuint uiFilter, GLuint uiWrapMode)
{
	BITMAP_t* pBitmap = FindTexture(filename);
	if(pBitmap)
	{
		if(pBitmap->Ref > 0)
		{
			if(0 == _stricmp(pBitmap->FileName, filename.c_str()))
			{
				pBitmap->Ref++;

				return pBitmap->BitmapIndex;
			}
		}
	}
	else
	{
		GLuint uiNewTextureIndex = GenerateTextureIndex();
		if(true == LoadImage(uiNewTextureIndex, filename, uiFilter, uiWrapMode))
		{
			m_listNonamedIndex.push_back(uiNewTextureIndex);

			return uiNewTextureIndex;
		}
	}
	return BITMAP_UNKNOWN;
}
bool CGlobalBitmap::LoadImage(GLuint uiBitmapIndex, const std::string& filename, GLuint uiFilter, GLuint uiWrapMode)
{
	unsigned int UICLAMP	= GL_CLAMP;
	unsigned int UIREPEAT	= GL_REPEAT;

	if( uiWrapMode != UICLAMP && uiWrapMode != UIREPEAT )
	{
#ifdef _DEBUG
		static unsigned int	uiCnt2 = 0;
		int			iBuff;	iBuff = 0;
		
		char		szDebugOutput[256];
		
		iBuff = iBuff + sprintf( iBuff + szDebugOutput, "%d. Call No CLAMP & No REPEAT. \n", 
			uiCnt2++);
		OutputDebugString( szDebugOutput );
#endif
	}

	type_bitmap_map::iterator mi = m_mapBitmap.find(uiBitmapIndex);
	if(mi != m_mapBitmap.end())
	{
		BITMAP_t* pBitmap = (*mi).second;
		if(pBitmap->Ref > 0)
		{
#ifdef _VS2008PORTING
			if(0 == _stricmp(pBitmap->FileName, filename.c_str()))
#else // _VS2008PORTING
			if(0 == stricmp(pBitmap->FileName, filename.c_str()))
#endif // _VS2008PORTING
			{
				pBitmap->Ref++;
				return true;
			}
			else
			{
				g_ErrorReport.Write("�ε����� �����ϰų� Delete���� ����Ͽ���%s(0x%00000008X)->%s\r\n", 
					pBitmap->FileName, uiBitmapIndex, filename.c_str());
				UnloadImage(uiBitmapIndex, true);	//. ������ �����.
			}
		}
	}
	
	std::string ext;
	SplitExt(filename, ext, false);
	
#ifdef _VS2008PORTING
	if(0 == _stricmp(ext.c_str(), "jpg"))
		return OpenJpeg(uiBitmapIndex, filename, uiFilter, uiWrapMode);
	else if(0 == _stricmp(ext.c_str(), "tga"))
		return OpenTga(uiBitmapIndex, filename, uiFilter, uiWrapMode);
#else // _VS2008PORTING
	if(0 == stricmp(ext.c_str(), "jpg"))
		return OpenJpeg(uiBitmapIndex, filename, uiFilter, uiWrapMode);
	else if(0 == stricmp(ext.c_str(), "tga"))
		return OpenTga(uiBitmapIndex, filename, uiFilter, uiWrapMode);
#endif // _VS2008PORTING
	
	return false;
}
void CGlobalBitmap::UnloadImage(GLuint uiBitmapIndex, bool bForce)
{
	type_bitmap_map::iterator mi = m_mapBitmap.find(uiBitmapIndex);
	if(mi != m_mapBitmap.end())
	{
		BITMAP_t* pBitmap = (*mi).second;

#ifdef LDS_OPTIMIZE_FORLOADING
		string strKey(pBitmap->FileName), strKey_Identity;
		// Full FileName���� ���ϸ� ���� strKey_Identity�� �����´�.
		SplitFileName(strKey, strKey_Identity, true);		
		
		// string���� �� �� map::find�� ��ҹ��ڿ� ���� ������ �ϱ� ������ ���� �ҹ��ڷ� ��ȯ �Ͽ� �ش�.
		StringToLower( strKey );
		StringToLower( strKey_Identity );

#ifdef _VS2008PORTING
		type_bitmap_namemap::iterator iter_ = m_mapBitmap_Namemap.end();
#else // _VS2008PORTING
		type_bitmap_namemap::iterator iter_ = 0;
#endif // _VS2008PORTING
		
		// FullNameMap�� ���翩�� �˻� �� ����� erase �Ͽ��ش�.
		// erase ���ڰ����� map::iterator�� �־ �ǰ�, firstKey�� ���ڷ� �ص� �����ϴ�.
		// namemap ���� FileName String ����
		iter_	= m_mapBitmap_Namemap.find( strKey );
		if( iter_ != m_mapBitmap_Namemap.end() )
		{
			m_mapBitmap_Namemap.erase( strKey );
		}

		//  namemap_identity ���� FileName String ����
		iter_	= m_mapBitmap_Namemap_identity.find( strKey_Identity );
		if( iter_ != m_mapBitmap_Namemap_identity.end() )
		{
			m_mapBitmap_Namemap_identity.erase( strKey_Identity );
		}
		
#endif // LDS_OPTIMIZE_FORLOADING

		if(--pBitmap->Ref == 0 || bForce)
		{
			// OpenGL �ؽ��� ����
			glDeleteTextures( 1, &(pBitmap->TextureNumber));

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
			m_dwUsedTextureMemory -= (DWORD)(pBitmap->Width * pBitmap->Height * pBitmap->Components);
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
			m_dwUsedTextureMemory -= (pBitmap->Width*pBitmap->Height*pBitmap->Components);
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
			delete [] pBitmap->Buffer;
			delete pBitmap;
			m_mapBitmap.erase(mi);
			
			if(uiBitmapIndex >= BITMAP_NONAMED_TEXTURES_BEGIN && uiBitmapIndex <= BITMAP_NONAMED_TEXTURES_END)
			{
				m_listNonamedIndex.remove(uiBitmapIndex);	//. �ε��� ĳ������ ����
			}
			m_BitmapCache.Remove(uiBitmapIndex);	//. ��Ʈ�� ĳ������ ����
		}
	}
}
void CGlobalBitmap::UnloadAllImages()
{
#ifdef _DEBUG
	if(!m_mapBitmap.empty())
		g_ErrorReport.Write("�������� ���� ��Ʈ�� �޸�:\r\n");
#endif // _DEBUG
	
	type_bitmap_map::iterator mi = m_mapBitmap.begin();
	for(; mi != m_mapBitmap.end(); mi++)
	{
		BITMAP_t* pBitmap = (*mi).second;

#ifdef _DEBUG
		if(pBitmap->Ref > 1)
		{
			g_ErrorReport.Write("Bitmap %s(RefCount= %d)\r\n", pBitmap->FileName, pBitmap->Ref);
		}
#endif // _DEBUG
		delete [] pBitmap->Buffer;
		delete pBitmap;
	}

	m_mapBitmap.clear();
	m_listNonamedIndex.clear();		//. �ε��� ĳ�� Ŭ����
	m_BitmapCache.RemoveAll();		//. ��Ʈ�� ĳ�� Ŭ����

#ifdef LDS_OPTIMIZE_FORLOADING
	m_mapBitmap_Namemap.clear();	//. bitmap texturefullfile�� namemap Ŭ����
	m_mapBitmap_Namemap_identity.clear();  //. bitmap texturefile�� namemap Ŭ����
#endif // LDS_OPTIMIZE_FORLOADING

	Init();
}

BITMAP_t* CGlobalBitmap::GetTexture(GLuint uiBitmapIndex)
{
	BITMAP_t* pBitmap = NULL;
	if(false == m_BitmapCache.Find(uiBitmapIndex, &pBitmap))	//. ĳ���� ���ٸ�
	{
		type_bitmap_map::iterator mi = m_mapBitmap.find(uiBitmapIndex);	//. �ʿ��� ã�´�.
		if(mi != m_mapBitmap.end())
			pBitmap = (*mi).second;
		m_BitmapCache.Add(uiBitmapIndex, pBitmap);	//. ĳ���� �߰�
	}
	if(NULL == pBitmap)	//. ���� �ε������
	{
#ifdef _DEBUG
		__asm { int 3 }		//. ����� �ϼ���!!
#endif // _DEBUG
		static BITMAP_t s_Error;
		memset(&s_Error, 0, sizeof(BITMAP_t));
		strcpy(s_Error.FileName, "CGlobalBitmap::GetTexture Error!!!");
		pBitmap = &s_Error;
	}
	return pBitmap;
}
BITMAP_t* CGlobalBitmap::FindTexture(GLuint uiBitmapIndex)
{
	BITMAP_t* pBitmap = NULL;
	if(false == m_BitmapCache.Find(uiBitmapIndex, &pBitmap))	//. ĳ���� ���ٸ�
	{
		type_bitmap_map::iterator mi = m_mapBitmap.find(uiBitmapIndex);	//. �ʿ��� ã�´�.
		if(mi != m_mapBitmap.end())
			pBitmap = (*mi).second;
		if(pBitmap != NULL)
			m_BitmapCache.Add(uiBitmapIndex, pBitmap);	//. ĳ���� �߰�
	}
	return pBitmap;
}

#ifdef LDS_OPTIMIZE_FORLOADING
// firstkey(string(filename))�� �������� std::map::find�� binary search �Ͽ� secondkey���� BITMAP_t* �� ��ȯ �Ͽ��ش�.
BITMAP_t* CGlobalBitmap::FindTexture(const std::string& filename)
{
	// ��Ȯ�� �˻��� ���� find�� firstkey �� string�� ��� �ҹ��ڷ� ��ȯ �Ѵ�. insert�ÿ� ��� �ҹ��ڷ� ��ȯ�� �ȴ�.
	string strFileName( filename );
	StringToLower( strFileName );
	
	type_bitmap_namemap::iterator iter_bitmapnamemap = m_mapBitmap_Namemap.find( strFileName );
	if( iter_bitmapnamemap != m_mapBitmap_Namemap.end() )
	{			
		return (*iter_bitmapnamemap).second;
	}
				
	return NULL;
}
#else // LDS_OPTIMIZE_FORLOADING
BITMAP_t* CGlobalBitmap::FindTexture(const std::string& filename)
{
	type_bitmap_map::iterator mi = m_mapBitmap.begin();
	for(; mi != m_mapBitmap.end(); mi++)
	{
		BITMAP_t* pBitmap = (*mi).second;
		if(0 == stricmp(filename.c_str(), pBitmap->FileName)) 
			return pBitmap;
	}
	return NULL;
}
#endif // LDS_OPTIMIZE_FORLOADING


#ifdef LDS_OPTIMIZE_FORLOADING
// firstkey(string(filename))�� �������� std::map::find�� binary search �Ͽ� secondkey���� BITMAP_t* �� ��ȯ �Ͽ��ش�.
// FullFile�� �� FileName���� Split �Ͽ� firstkey�� ���� std::map(Namemap_identity)�� find�� BinarySearch �Ѵ�.
BITMAP_t* CGlobalBitmap::FindTextureByName(const std::string& name)
{
	string strFileName( name );
	StringToLower( strFileName );

	type_bitmap_namemap::iterator iter_bitmapnamemap = m_mapBitmap_Namemap_identity.find( strFileName );
	if( iter_bitmapnamemap != m_mapBitmap_Namemap_identity.end() )
	{						
		return (*iter_bitmapnamemap).second;
	}

	return NULL;
}
#else // LDS_OPTIMIZE_FORLOADING
BITMAP_t* CGlobalBitmap::FindTextureByName(const std::string& name)
{
	type_bitmap_map::iterator mi = m_mapBitmap.begin();
	for(; mi != m_mapBitmap.end(); mi++)
	{
		BITMAP_t* pBitmap = (*mi).second;
		std::string texname;
		SplitFileName(pBitmap->FileName, texname, true);
		if(0 == stricmp(texname.c_str(), name.c_str())) 
			return pBitmap;
	}
	return NULL;
}
#endif // LDS_OPTIMIZE_FORLOADING




#ifdef LDS_OPTIMIZE_FORLOADING
// std::map::find�� String�� firstkey�� �ξ� find �� ��� ������ 
// LinearSearch�� �� String�� ��� stricmp �Ͽ� �� character�� ��Ȯ�� �����ϴ�
// ����� �ƴ� �ܼ� ��� �� �̱⿡ ���� �ϳ� ���� �� �ִ� �� fail �� 
// ������ �ʵ��� ������ �� ����� ���� �Լ��� �����Ѵ�. 
BITMAP_t* CGlobalBitmap::FindTexture_Linear(const std::string& filename)
{
	type_bitmap_map::iterator mi = m_mapBitmap.begin();
	for(; mi != m_mapBitmap.end(); mi++)
	{
		BITMAP_t* pBitmap = (*mi).second;
#ifdef _VS2008PORTING
		if(0 == _stricmp(filename.c_str(), pBitmap->FileName)) 
#else // _VS2008PORTING
		if(0 == stricmp(filename.c_str(), pBitmap->FileName)) 
#endif // _VS2008PORTING
		{
			return pBitmap;
		}
	}
	
	return NULL;
}

BITMAP_t* CGlobalBitmap::FindTextureByName_Linear(const std::string& name)
{
	type_bitmap_map::iterator mi = m_mapBitmap.begin();
	for(; mi != m_mapBitmap.end(); mi++)
	{
		BITMAP_t* pBitmap = (*mi).second;
		std::string texname;
		SplitFileName(pBitmap->FileName, texname, true);
		if(0 == stricmp(texname.c_str(), name.c_str())) 
		{
			return pBitmap;
		}
	}
	
	return NULL;
}
#endif // LDS_OPTIMIZE_FORLOADING


DWORD CGlobalBitmap::GetUsedTextureMemory() const
{
	return m_dwUsedTextureMemory;
}
size_t CGlobalBitmap::GetNumberOfTexture() const
{
	return m_mapBitmap.size();
}

void CGlobalBitmap::Manage()
{
#ifdef DEBUG_BITMAP_CACHE
	m_DebugOutputTimer.UpdateTime();
	if(m_DebugOutputTimer.IsTime())
	{
		g_ConsoleDebug->Write(MCD_NORMAL, "CacheSize=%d(NumberOfTexture=%d)", m_BitmapCache.GetCacheSize(), GetNumberOfTexture());
	}
#endif // DEBUG_BITMAP_CACHE
	m_BitmapCache.Update();
}

GLuint CGlobalBitmap::GenerateTextureIndex()
{
	GLuint uiAvailableTextureIndex = FindAvailableTextureIndex(m_uiTextureIndexStream);
	if(uiAvailableTextureIndex >= BITMAP_NONAMED_TEXTURES_END)	//. ���� �ʰ���
	{
		m_uiAlternate++;
		m_uiTextureIndexStream = BITMAP_NONAMED_TEXTURES_BEGIN;
		uiAvailableTextureIndex = FindAvailableTextureIndex(m_uiTextureIndexStream);	//. ��˻�
	}
	return m_uiTextureIndexStream = uiAvailableTextureIndex;
}
GLuint CGlobalBitmap::FindAvailableTextureIndex(GLuint uiSeed)
{
	if(m_uiAlternate > 0)
	{
		type_index_list::iterator li = std::find(m_listNonamedIndex.begin(), m_listNonamedIndex.end(), uiSeed+1);
		if(li != m_listNonamedIndex.end())	//. �ִٸ�
			return FindAvailableTextureIndex(uiSeed+1);	//. ��˻�
	}
	return uiSeed+1;
}

bool CGlobalBitmap::OpenJpeg(GLuint uiBitmapIndex, const std::string& filename, GLuint uiFilter, GLuint uiWrapMode)
{
#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENJPEG, PROFILING_LOADING_OPENJPEG );
	}
#endif // DO_PROFILING_FOR_LOADING

	

	std::string filename_ozj;
	ExchangeExt(filename, "OZJ", filename_ozj);

	FILE* infile = fopen(filename_ozj.c_str(), "rb");
	if(infile == NULL) 
	{
#ifdef DO_PROFILING_FOR_LOADING
		if( g_pProfilerForLoading )
		{
			g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENJPEG );
		}
#endif // DO_PROFILING_FOR_LOADING
		return false;
	}

	fseek(infile,24,SEEK_SET);	//. Skip Dump
	
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if (setjmp(jerr.setjmp_buffer)) 
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);

#ifdef DO_PROFILING_FOR_LOADING
		if( g_pProfilerForLoading )
		{
			g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENJPEG );
		}
#endif // DO_PROFILING_FOR_LOADING

		return false;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);

	if(cinfo.output_width<=MAX_WIDTH && cinfo.output_height<=MAX_HEIGHT)
	{
#ifdef _VS2008PORTING
		int Width, Height;
		for(int i=1;i<=MAX_WIDTH;i<<=1)
		{
			Width = i;
			if(i >= (int)cinfo.output_width) break;
		}
		for(int i=1;i<=MAX_HEIGHT;i<<=1)
		{
			Height = i;
			if(i >= (int)cinfo.output_height) break;
		}
#else // _VS2008PORTING
		for(int Width=1;Width<MAX_WIDTH;Width<<=1)
		{
			if(Width >= (int)cinfo.output_width) break;
		}
		for(int Height=1;Height<MAX_HEIGHT;Height<<=1)
		{
			if(Height >= (int)cinfo.output_height) break;
		}
#endif // _VS2008PORTING

		BITMAP_t* pNewBitmap = new BITMAP_t;
		memset(pNewBitmap, 0, sizeof(BITMAP_t));

		pNewBitmap->BitmapIndex = uiBitmapIndex;
#ifdef _VS2008PORTING
		filename._Copy_s(pNewBitmap->FileName, MAX_BITMAP_FILE_NAME, MAX_BITMAP_FILE_NAME);
#else // _VS2008PORTING
		filename.copy(pNewBitmap->FileName, MAX_BITMAP_FILE_NAME);
#endif // _VS2008PORTING

		pNewBitmap->Width      = (float)Width;
		pNewBitmap->Height     = (float)Height;
		pNewBitmap->Components = 3;
		pNewBitmap->Ref = 1;
		
		size_t BufferSize = Width*Height*pNewBitmap->Components;
		pNewBitmap->Buffer = new BYTE[BufferSize];
		m_dwUsedTextureMemory += BufferSize;
		
		int offset=0;
		int row_stride = cinfo.output_width * cinfo.output_components;
		JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
		while (cinfo.output_scanline < cinfo.output_height) 
		{
#ifdef _VS2008PORTING
			if(offset+row_stride > (int)BufferSize)
#else // _VS2008PORTING
			if(offset+row_stride > BufferSize)
#endif // _VS2008PORTING
				break;

			(void) jpeg_read_scanlines(&cinfo, buffer, 1);
			memcpy(pNewBitmap->Buffer+(cinfo.output_scanline-1)*Width*3,buffer[0],row_stride);
			offset += row_stride;
		}

#ifdef LDS_OPTIMIZE_FORLOADING
		// Texture Image Open�� Bitmap_map�� ������ ������ Bitmap_namemap�� ���� �˻� Ű ���� �Ǵ� 
		// filename�� �������� Firstkey(FileName), Secondkey(BITMAP_t*) Ű�� ���� �Ѵ�.
		// ���Խ� �� FileName�� �ʼ��� �ҹ���ȭ ��Ų��.
		std::string strFileName, strFullFileName( pNewBitmap->FileName );

		StringToLower(strFullFileName);
		SplitFileName(strFullFileName, strFileName, true);

		// 1. Namemap �� �߰�. FindTexture(string) �Լ��� �˻��� Ȱ�� �ȴ�.
		m_mapBitmap_Namemap.insert( type_bitmap_namemap::value_type(strFullFileName, pNewBitmap) );

		// 2. NameMap Identity �߰�  �Ѵ�. FindTextureByName(string) �Լ��� �˻��� Ȱ�� �ȴ�.
		m_mapBitmap_Namemap_identity.insert( type_bitmap_namemap::value_type(strFileName, pNewBitmap) );
#endif // LDS_OPTIMIZE_FORLOADING

		m_mapBitmap.insert(type_bitmap_map::value_type(uiBitmapIndex, pNewBitmap));
		
		glGenTextures( 1, &(pNewBitmap->TextureNumber));

		glBindTexture(GL_TEXTURE_2D, pNewBitmap->TextureNumber);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pNewBitmap->Buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, uiFilter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, uiFilter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uiWrapMode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, uiWrapMode);
		
#if defined(LDS_MR0_OUTPUT_GLERROR_IN_BITMAPLOAD) && defined(_DEBUG)
		CheckGLError( __FILE__, __LINE__ );
#endif // LDS_MR0_OUTPUT_GLERROR_IN_BITMAPLOAD
	}
	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENJPEG );
	}
#endif // DO_PROFILING_FOR_LOADING

	return true;
}
bool CGlobalBitmap::OpenTga(GLuint uiBitmapIndex, const std::string& filename, GLuint uiFilter, GLuint uiWrapMode)
{
#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->BeginUnit( EPROFILING_LOADING_OPENTGA, PROFILING_LOADING_OPENTGA );
	}
#endif // DO_PROFILING_FOR_LOADING

	std::string filename_ozt;
	ExchangeExt(filename, "OZT", filename_ozt);

	// ���� ���°� ���н� ó��.
    FILE *fp = fopen(filename_ozt.c_str(), "rb");
    if(fp == NULL)
	{
#ifdef DO_PROFILING_FOR_LOADING
		if( g_pProfilerForLoading )
		{
			g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENTGA );
		}
#endif // DO_PROFILING_FOR_LOADING
		return false;
	}

	// ���� ũ�⸦ ����.
	fseek(fp,0,SEEK_END);
	int Size = ftell(fp);
	fseek(fp,0,SEEK_SET);

	// ������ ���� ������ ���� �޸� �Ҵ� �� ������ ����.
	unsigned char *PakBuffer = new unsigned char [Size];
	fread(PakBuffer,1,Size,fp);
	fclose(fp);
	
	// OZTȮ���� ��������� ����.
	// �ε��� 16(12 + 4)����.
    int index = 12;
	index += 4;
	// �ε��� 16�� �̹��� ����ũ��.
    short nx = *((short *)(PakBuffer+index));index+=2;
	// �ε��� 18�� �̹��� ����ũ��.
    short ny = *((short *)(PakBuffer+index));index+=2;
	// �ε��� 20�� �̹��� ��Ʈ�� color bit.(��: 32bit, 16bit)
    char bit = *((char *)(PakBuffer+index));index+=1;
	index += 1;	// ���� �ε����� 22.

	// 32bit color�� �ƴϰų� �̹��� �ִ� ũ�⸦ ������ ����.
    if(bit!=32 || nx>MAX_WIDTH || ny>MAX_HEIGHT)
	{
#ifdef KJH_FIX_ARRAY_DELETE
		SAFE_DELETE_ARRAY(PakBuffer);
#else // KJH_FIX_ARRAY_DELETE
		delete PakBuffer;
#endif // KJH_FIX_ARRAY_DELETE

#ifdef DO_PROFILING_FOR_LOADING
		if( g_pProfilerForLoading )
		{
			g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENTGA );
		}
#endif // DO_PROFILING_FOR_LOADING

		return false;
	}

	// �ؽ�ó�� ����� ���� �ؽ�ó ũ�� ����. 2�� �ڽ����� ����(<<=1)
#ifdef _VS2008PORTING
	int Width = 0, Height = 0;
	for(int i=1;i<=MAX_WIDTH;i<<=1)
	{
		Width = i;
		if(i >= nx) break;
	}
	for(int i=1;i<=MAX_HEIGHT;i<<=1)
	{
		Height = i;
		if(i >= ny) break;
	}
#else // _VS2008PORTING
	for(int Width=1;Width<MAX_WIDTH;Width<<=1)
	{
		if(Width >= nx) break;
	}
	for(int Height=1;Height<MAX_HEIGHT;Height<<=1)
	{
		if(Height >= ny) break;
	}
#endif // _VS2008PORTING

	// BITMAP_t ����ü ä��.
	BITMAP_t* pNewBitmap = new BITMAP_t;
	memset(pNewBitmap, 0, sizeof(BITMAP_t));
	
	pNewBitmap->BitmapIndex = uiBitmapIndex;
#ifdef _VS2008PORTING
	filename._Copy_s(pNewBitmap->FileName, MAX_BITMAP_FILE_NAME, MAX_BITMAP_FILE_NAME);
#else // _VS2008PORTING
	filename.copy(pNewBitmap->FileName, MAX_BITMAP_FILE_NAME);
#endif // _VS2008PORTING
	
	pNewBitmap->Width      = (float)Width;
	pNewBitmap->Height     = (float)Height;
	pNewBitmap->Components = 4;	//ARGB ���� ��� ��(4�̹Ƿ� 32bit�̸� 4byte��) 
	pNewBitmap->Ref = 1;
	
	size_t BufferSize = Width*Height*pNewBitmap->Components;
	pNewBitmap->Buffer     = (unsigned char*)new BYTE[BufferSize];
	// m_dwUsedTextureMemory�� ���ӿ� ������� �ʰ� ������ Ȯ�ο�. #define ENABLE_EDIT ����.
	m_dwUsedTextureMemory += BufferSize;

    for(int y=0;y<ny;y++)
	{
		// ���Ͽ��� �о���� ������.
        unsigned char *src = &PakBuffer[index];
		index += nx * 4;
		// �ؽ�ó ������. �ؿ������� ���� ä��.(TGA ������ Ư�� ������ ��)
		unsigned char *dst = &pNewBitmap->Buffer[(ny-1-y)*Width*pNewBitmap->Components];

		// TGA�� ��Ʈ���� ARGB������ �ٸ��Ƿ�.
		for(int x=0;x<nx;x++)
        {
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
			dst[3] = src[3];
			src += 4;
			dst += pNewBitmap->Components;
        }
	}
#ifdef KJH_FIX_ARRAY_DELETE
	SAFE_DELETE_ARRAY(PakBuffer);
#else //KJH_FIX_ARRAY_DELETE
	delete PakBuffer;
#endif // KJH_FIX_ARRAY_DELETE

#ifdef LDS_OPTIMIZE_FORLOADING
	// Texture Image Open�� Bitmap_map�� ������ ������ Bitmap_namemap�� ���� �˻� Ű ���� �Ǵ� 
	// filename�� �������� Firstkey(FileName), Secondkey(BITMAP_t*) Ű�� ���� �Ѵ�.
	// ���Խ� �� FileName�� �ʼ��� �ҹ���ȭ ��Ų��.
	std::string strFileName, strFullFileName( pNewBitmap->FileName );
	
	StringToLower(strFullFileName);
	SplitFileName(strFullFileName, strFileName, true);
	
	// 1. Namemap �� �߰�. FindTexture(string) �Լ��� �˻��� Ȱ�� �ȴ�.
	m_mapBitmap_Namemap.insert( type_bitmap_namemap::value_type(strFullFileName, pNewBitmap) );
	
	// 2. NameMap Identity �߰�  �Ѵ�. FindTextureByName(string) �Լ��� �˻��� Ȱ�� �ȴ�.
		m_mapBitmap_Namemap_identity.insert( type_bitmap_namemap::value_type(strFileName, pNewBitmap) );
#endif // LDS_OPTIMIZE_FORLOADING

	m_mapBitmap.insert(type_bitmap_map::value_type(uiBitmapIndex, pNewBitmap));
	
	glGenTextures( 1, &(pNewBitmap->TextureNumber));		// �ؽ�ó ID(pNewBitmap->TextureNumber) ����.

	glBindTexture(GL_TEXTURE_2D, pNewBitmap->TextureNumber);	// �ؽ�ó ���ε�.

	// �ؽ�ó �̹��� ����.
    glTexImage2D(GL_TEXTURE_2D, 0, 4, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pNewBitmap->Buffer);

	// �ؽ�ó ȿ�� ����.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// �ؽ�ó ���͸�.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, uiFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, uiFilter);

	// �ؽ�ó ����.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uiWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, uiWrapMode);

#if defined(LDS_MR0_OUTPUT_GLERROR_IN_BITMAPLOAD) && defined(_DEBUG)
	CheckGLError( __FILE__, __LINE__ );
#endif // LDS_MR0_OUTPUT_GLERROR_IN_BITMAPLOAD


#ifdef DO_PROFILING_FOR_LOADING
	if( g_pProfilerForLoading )
	{
		g_pProfilerForLoading->EndUnit( EPROFILING_LOADING_OPENTGA );
	}
#endif // DO_PROFILING_FOR_LOADING

	return true;
}

void CGlobalBitmap::SplitFileName(IN const std::string& filepath, OUT std::string& filename, bool bIncludeExt) 
{
	char __fname[_MAX_FNAME] = {0, };
	char __ext[_MAX_EXT] = {0, };
	_splitpath(filepath.c_str(), NULL, NULL, __fname, __ext);
	filename = __fname;
	if(bIncludeExt)
		filename += __ext;
}
void CGlobalBitmap::SplitExt(IN const std::string& filepath, OUT std::string& ext, bool bIncludeDot) 
{
	char __ext[_MAX_EXT] = {0, };
	_splitpath(filepath.c_str(), NULL, NULL, NULL, __ext);
	if(bIncludeDot) {
		ext = __ext;
	}
	else {
		if((__ext[0] == '.') && __ext[1])
			ext = __ext+1;
	}
}
void CGlobalBitmap::ExchangeExt(IN const std::string& in_filepath, IN const std::string& ext, OUT std::string& out_filepath) 
{
	char __drive[_MAX_DRIVE] = {0, };
	char __dir[_MAX_DIR] = {0, };
	char __fname[_MAX_FNAME] = {0, };
	_splitpath(in_filepath.c_str(), __drive, __dir, __fname, NULL);
	
	out_filepath = __drive;
	out_filepath += __dir;
	out_filepath += __fname;
	out_filepath += '.';
	out_filepath += ext;
}

bool CGlobalBitmap::Convert_Format(const unicode::t_string& filename)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	::_splitpath(filename.c_str(), drive, dir, fname, ext);
	
	std::string strPath = drive; strPath += dir;
	std::string strName = fname;
	
	if(_stricmp(ext, ".jpg") == 0) 
	{
		unicode::t_string strSaveName = strPath + strName + ".OZJ";
		return Save_Image(filename, strSaveName.c_str(), 24);
	}
	else if(_stricmp(ext, ".tga") == 0) 
	{
		unicode::t_string strSaveName = strPath + strName + ".OZT";
		return Save_Image(filename, strSaveName.c_str(), 4);
	}
	else if(_stricmp(ext, ".bmp") == 0) 
	{
		unicode::t_string strSaveName = strPath + strName + ".OZB";
		return Save_Image(filename, strSaveName.c_str(), 4);
	}
	else
	{
		// �̹��� ������ �ٸ��ϴ�.
	}

	return false;
}

bool CGlobalBitmap::Save_Image(const unicode::t_string& src, const unicode::t_string& dest, int cDumpHeader)
{
	FILE* fp = fopen(src.c_str(), "rb");
	if(fp == NULL) 
	{
		return false;
	}
	
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	char* pTempBuf = new char[size];
	fread(pTempBuf, 1, size, fp);
	fclose(fp);
	
	fp = fopen(dest.c_str(), "wb");
	if(fp == NULL) 
		return false;
	
	fwrite(pTempBuf, 1, cDumpHeader, fp);
	fwrite(pTempBuf, 1, size, fp);
	fclose(fp);
	
	delete [] pTempBuf;
	
	return true;
}

void CGlobalBitmap::my_error_exit(j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}


////////////////////////////////////////////////////////////////////////// CGlobalBitmap