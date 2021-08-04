//*****************************************************************************
// File: Button.cpp
//
// Desc: implementation of the CButton class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "Button.h"
#include "Input.h"

#include "ZzzOpenglUtil.h"

// �ؽ�Ʈ ������ ���� #include. �̤�
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"

#include "DSPlaySound.h"
#include "UIControls.h"

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;

CButton*	CButton::m_pBtnHeld;		// ������ ��ư�� ������.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CButton::CButton() : m_szText(NULL), m_adwTextColorMap(NULL)
{

}

CButton::~CButton()
{
	Release();
}

void CButton::Release()
{
	ReleaseText();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ��ư ����.
//			   ��ư�� ���� �ؽ�ó�� �� �̹����� ���η� �迭�Ǿ� �־����.
//			   �̹��� ��ȣ�� ������ 0����.
//			   ��ư���� Push��ư�� Check��ư�� �ִµ� Push��ư�� nDisableFrame
//			  ������ ����.
//			   üũ��ư ���δ� m_anImgMap[BTN_UP_CHECK]�� 0 �̻��̸� üũ ��ư
//			  ��.
// �Ű� ���� : nWidth			: ��ư�� �ȼ� �ʺ�.
//			   nHeight			: ��ư�� �ȼ� ����.
//			   nTexID			: �ؽ�ó ID.
//			   nMaxFrame		: �ؽ�ó ���� �̹��� ����.(�⺻�� 1)
//			   nDownFrame		: ������ ���� �̹��� ��ȣ.(�⺻�� -1)
//								  ������ ��� 0�� �̹����� ����.
//			   nActiveFrame		: ���콺 Ŀ���� ��ư ���� ������ �̹��� ��ȣ.
//								  (�⺻�� -1)
//								  ������ ��� 0�� �̹����� ����.
//			   nDisableFrame	: ��� �Ұ��� �����϶� �̹��� ��ȣ.(�⺻�� -1)
//								  ������ ��� �������� ����.
//			   nCheckUpFrame	: üũ �Ǿ��� ���ÿ� �̹��� ��ȣ.(�⺻�� -1)
//								  ������ ��� üũ ��ư�� �ƴ�.
//			   nCheckDownFrame	: üũ �Ǿ��� ������ ���� �̹��� ��ȣ.
//								  (�⺻�� -1)
//								  ������ ��� nCheckUpFrame �̹��� ���.
//			   nCheckActiveFrame: üũ �Ǿ��� ���콺 Ŀ���� ��ư ���� ������ ��
//								 ���� ��ȣ.(�⺻�� -1)
//								  ������ ��� nCheckUpFrame �̹��� ���.
//			   nCheckDisableFrame: üũ �Ǿ��� ���Ұ��� �����϶� �̹��� ��ȣ.
//								 (�⺻�� -1)
//								  ������ ��� �������� ����.
//*****************************************************************************
void CButton::Create(int nWidth, int nHeight, int nTexID, int nMaxFrame,
					 int nDownFrame, int nActiveFrame, int nDisableFrame,
					 int nCheckUpFrame, int nCheckDownFrame,
					 int nCheckActiveFrame, int nCheckDisableFrame)
{
	Release();

// ���� Ŭ���� ������Ʈ ����.
	// ��ư �ؽ�ó�� �� �������� ���η� �迭�Ǿ� ����.
	SFrameCoord* aFrameCoord = new SFrameCoord[nMaxFrame];
	for (int i = 0; i < nMaxFrame; ++i)
	{
		aFrameCoord[i].nX = 0;
		aFrameCoord[i].nY = nHeight * i;
	}

	CSprite::Create(nWidth, nHeight, nTexID, nMaxFrame, aFrameCoord);

	delete [] aFrameCoord;

	CSprite::SetAction(0, nMaxFrame - 1);	// �̹����� �ٲ� �� �ְ� ���� ����.

// ��ư ���� ���� ó��.
	// ��ư �̹��� ����.
	m_anImgMap[BTN_UP] = 0;
	m_anImgMap[BTN_DOWN] = nDownFrame > -1 ? nDownFrame : 0;
	m_anImgMap[BTN_ACTIVE] = nActiveFrame > -1 ? nActiveFrame : 0;
	m_anImgMap[BTN_DISABLE] = nDisableFrame;

	m_anImgMap[BTN_UP_CHECK] = nCheckUpFrame;
	m_anImgMap[BTN_DOWN_CHECK] = nCheckDownFrame > -1
		? nCheckDownFrame : m_anImgMap[BTN_UP_CHECK];
	m_anImgMap[BTN_ACTIVE_CHECK] = nCheckActiveFrame > -1
		? nCheckActiveFrame : m_anImgMap[BTN_UP_CHECK];
	m_anImgMap[BTN_DISABLE_CHECK] = nCheckDisableFrame;

	m_bClick = m_bCheck = false;
	m_bEnable = m_bActive = true;
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : ��ư�� ������.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CButton::Show(bool bShow)
{
	CSprite::Show(bShow);
	if (!bShow)
		m_bClick = false;
}

//*****************************************************************************
// �Լ� �̸� : CursorInObject()
// �Լ� ���� : m_bActive�� true�� �� ��ư �ȿ� ���콺 Ŀ���� ������ TRUE, ����
//			  �� FALSE�� ����.
//*****************************************************************************
BOOL CButton::CursorInObject()
{
	if (!m_bActive)
		return FALSE;

	return CSprite::CursorInObject();
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : ��ư�� �ڵ� ó�� �� ��ư �̹��� ����.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//							  (�⺻��: 0.0)
//*****************************************************************************
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CButton::Update()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CButton::Update(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	// �������� ���� ��� return.
	if (!CSprite::m_bShow)
		return;

	CInput& rInput = CInput::Instance();
	// �ؽ�Ʈ ������ RenderText3()�� ���� ��ǥ���� �־�� �ȴ�. ���� ���� ��
	//ǥ�� ��ȯ�ϴ� �������� �Ҽ��� ���ϰ� ©���Ƿ� 0.5�� �����־� ������ ����
	//��. ���� ��ư�� ������ �� �ؽ�Ʈ�� 1�ȼ� �Ʒ��� �׷��� �ϹǷ� 0.5���� +1
	//�� ���ش�. 
	m_fTextAddYPos = 0.5f;

	if (m_bEnable/* && m_bActive*/)	// ��� �����ϰ� ������ ������ �����̸�.
	{
	// ��ư ���� ���� ����.
		// ���콺 Ŀ���� ��ư ���� �ְ� ���콺 ���� ��ư�� �����°�?
		if (CursorInObject() && rInput.IsLBtnDn())
			m_pBtnHeld = this;		// ������ ��ư�� �ڽ���.

		m_bClick = false;				// m_bClick(Ŭ���ΰ�?)�� �ʱ�ȭ.
		// Ŭ���� ��ư�� ���� ������ �̷������ �ϹǷ� �Ź� ó���� �ʱ�ȭ ��.

		// ���콺 ���� ��ư�� �ô°�?
		if (rInput.IsLBtnUp())
		{
			// ���콺 Ŀ���� ��ư ���� �ְ� ������ ��ư�� �ڽ��ΰ�? (1�� if)
			if (CursorInObject() && this == m_pBtnHeld)
			{
				m_bClick = true;				// Ŭ����.

				::PlayBuffer(SOUND_CLICK01);	// Ŭ�� ����.

				if (-1 < m_anImgMap[BTN_UP_CHECK])	// üũ ��ư�ΰ�?
					m_bCheck = !m_bCheck;		// ���.
			}

			if (this == m_pBtnHeld)	// ������ ��ư�� �ڽ��ΰ�? (2�� if)
				m_pBtnHeld = NULL;	// ������ ��ư�� ����.
			// '2�� if'ó�� ������ ���� ���, ��ư�� ���� �� m_pBtnHeld��
			//�� ������ NULL�� ���Եȴ�. �̿� ���� �� ��ư�� �������� ��� �ι�
			//° ��ư�� Ŭ������ �� ù��° ��ư�� Update()���� 'm_pBtnHeld =
			//NULL'�̹Ƿ� �ι�° ��ư�� Update()���� '1�� if'�� �����ϰ� �Ǿ�
			//�ι�° ��ư�� Ŭ������ ���������� �νĵǴ� ������ �߻��ȴ�. ����
			//�� m_pBtnHeld�� this�� ���� m_pBtnHeld�� NULL�� �������ش�.
		}

	// ��ư �̹��� ����.
		// ���콺 Ŀ���� ��ư ���� �ְ� ��ư�� ����� ���� ������?
		if (CursorInObject() && NULL == m_pBtnHeld)
			if (m_bCheck)	// üũ ���¶��.
			{
				CSprite::SetNowFrame(m_anImgMap[BTN_ACTIVE_CHECK]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_ACTIVE_CHECK];
			}
			else			// üũ ���°� �ƴϸ�.
			{
				// ���� ������ Highlight�ǰ� ��ư Up�� �̹���.
				CSprite::SetNowFrame(m_anImgMap[BTN_ACTIVE]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_ACTIVE];
			}

		// ���콺 Ŀ���� ��ư ���� �ְ� ������ ��ư�� �ڽ��ΰ�?
		else if (CursorInObject() && this == m_pBtnHeld)
		{
			m_fTextAddYPos = 1.5f;	// �ؽ�Ʈ�� 1�ȼ� ������.(���� ���� +0.5f)

			if (m_bCheck)	// üũ ���¶��.
			{
				CSprite::SetNowFrame(m_anImgMap[BTN_DOWN_CHECK]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_DOWN_CHECK];
			}
			else			// üũ ���°� �ƴϸ�.
			{
				// ���� ������ Highlight�ǰ� ��ư Down�� �̹���.
				CSprite::SetNowFrame(m_anImgMap[BTN_DOWN]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_DOWN];
			}
		}

		// �� �� ����.(���콺 Ŀ���� ��ư ���� ���� ���� ����)
		else
			if (m_bCheck)	// üũ ���¶��.
			{
				CSprite::SetNowFrame(m_anImgMap[BTN_UP_CHECK]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_UP_CHECK];
			}
			else			// üũ ���°� �ƴϸ�.
			{
				// ���� ������ Highlight���� �ʰ� ��ư Up�� �̹���.
				CSprite::SetNowFrame(m_anImgMap[BTN_UP]);
				if (NULL != m_szText)
					m_dwTextColor = m_adwTextColorMap[BTN_UP];
			}
	}
	else	// ��� �Ұ����̸�.
	{
		m_bClick = false;
		if (rInput.IsLBtnUp() && this == m_pBtnHeld)
			m_pBtnHeld = NULL;	// ������ ��ư�� ����.

		if (m_bCheck)	// üũ ���¶��.
		{
			CSprite::SetNowFrame(m_anImgMap[BTN_DISABLE_CHECK]);
			if (NULL != m_szText)
				m_dwTextColor = m_adwTextColorMap[BTN_DISABLE_CHECK];
		}
		else			// üũ ���°� �ƴϸ�.
		{
			CSprite::SetNowFrame(m_anImgMap[BTN_DISABLE]);
			if (NULL != m_szText)
				m_dwTextColor = m_adwTextColorMap[BTN_DISABLE];
		}
	}

//	CSprite::Update(dDeltaTick);	// ��ư Animation.
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ��ư ����.
//*****************************************************************************
void CButton::Render()
{
	if (!CSprite::m_bShow)
		return;

	// ��� �Ұ��� ���¿��� �ش� �̹��� ��ȣ�� �����̸� ������ ����.
	if (!m_bEnable)
	{
		if (m_bCheck && m_anImgMap[BTN_DISABLE_CHECK] < 0)
			return;
		if (!m_bCheck && m_anImgMap[BTN_DISABLE] < 0)
			return;
	}

	CSprite::Render();

// �ؽ�Ʈ ����.
	if (NULL == m_szText)
		return;

	// �ؽ�Ʈ ���� ����.
	g_pRenderText->SetTextColor(m_dwTextColor);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->SetFont(g_hFixFont);

	// �ؽ�Ʈ ��� ��ǥ ����.
	SIZE size;
#ifdef LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	g_pMultiLanguage->_GetTextExtentPoint32(g_pRenderText->GetFontDC(), m_szText, ::strlen(m_szText), &size);
#else  //LJH_ADD_SUPPORTING_MULTI_LANGUAGE
	unicode::_GetTextExtentPoint32(g_pRenderText->GetFontDC(), m_szText, ::strlen(m_szText), &size);
#endif //LJH_ADD_SUPPORTING_MULTI_LANGUAGE

	float fTextRelativeYPos = ((CSprite::GetHeight() - size.cy) / 2.0f);

	// ���� �ؽ�Ʈ ���� �Լ��� ����ϹǷ� ��ǥ�� ���� ��ǥ�� ��ȯ ���־�� �Ѵ�.
	g_pRenderText->RenderText(int(CSprite::GetXPos() / g_fScreenRate_x),
		int(((float)CSprite::GetYPos() + fTextRelativeYPos) / g_fScreenRate_y
		+ m_fTextAddYPos), m_szText, CSprite::GetWidth() / g_fScreenRate_x, 0, RT3_SORT_CENTER);
}

//*****************************************************************************
// �Լ� �̸� : ReleaseText()
// �Լ� ���� : �ؽ�Ʈ ���� Release.
//*****************************************************************************
void CButton::ReleaseText()
{
	SAFE_DELETE_ARRAY(m_szText);
	SAFE_DELETE_ARRAY(m_adwTextColorMap);
}

//*****************************************************************************
// �Լ� �̸� : SetText()
// �Լ� ���� : ��ư�� �ؽ�Ʈ�� ��.
//			   ������ ARGB() �̿�. ������ DWORD Ÿ���� �迭��.
//			   üũ ��ư�� ��� ���� �迭 ũ�Ⱑ 8, �ƴѰ�� 4.
// �Ű� ���� : pszText	: ���ڿ�.
//			   adwColor	: ���� �迭 �̸�(������).
//*****************************************************************************
void CButton::SetText(const char* pszText, DWORD* adwColor)
{
	ReleaseText();

	// ���ڿ� ī��.
	m_szText = new char[::strlen(pszText) + 1];
	::strcpy(m_szText, pszText);

	// �ؽ�Ʈ �÷� ����.
	int nTextColor = -1 < m_anImgMap[BTN_UP_CHECK]	// üũ ��ư�ΰ�?
		? BTN_IMG_MAX : BTN_IMG_MAX / 2;

	// ���ڻ� �迭 ī��.
	m_adwTextColorMap = new DWORD[nTextColor];
	::memcpy(m_adwTextColorMap, adwColor, sizeof(DWORD) * nTextColor);
}