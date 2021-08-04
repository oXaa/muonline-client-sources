//*****************************************************************************
// File: UIMapName.h
//
// Desc: interface for the CUIMapName class.
//		 ȭ�� ����߾��� �� �̸� UI.
//
// producer: Ahn Sang-Kyu (2005. 6. 16)
//*****************************************************************************	

#if !defined(AFX_UIMAPNAME_H__6771C771_B81D_4D5C_8484_63D6961ED6C0__INCLUDED_)
#define AFX_UIMAPNAME_H__6771C771_B81D_4D5C_8484_63D6961ED6C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

typedef map<int, string> ImgPathMap;

class CUIMapName  
{
	// (�Ⱥ���, ������ ��Ÿ��, ����, ������ �����)
	enum SHOW_STATE { HIDE, FADEIN, SHOW, FADEOUT };

protected:
	ImgPathMap	m_mapImgPath;		// �̹��� ��� ���ڿ� ��.(�� ��ȣ�� Ű)
	short		m_nOldWorld;		// ���� �� ��ȣ.
	SHOW_STATE	m_eState;			// �����ֱ� ����.
	DWORD		m_dwOldTime;		// ���� ������ �ð�.
	DWORD		m_dwDeltaTickSum;	// �����Ӱ� �ð���.
	float		m_fAlpha;			// ���İ�.
#ifdef ASG_ADD_GENS_SYSTEM
	bool		m_bStrife;			// ���������̸� true;
#endif	// ASG_ADD_GENS_SYSTEM

public:
	CUIMapName();
	virtual ~CUIMapName();

	void Init();
	void ShowMapName();
	void Update();
	void Render();

protected:
	void InitImgPathMap();
};

#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
extern string g_strSelectedML;
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

#endif // !defined(AFX_UIMAPNAME_H__6771C771_B81D_4D5C_8484_63D6961ED6C0__INCLUDED_)
