//*****************************************************************************
// File: Sprite.cpp
//
// Desc: implementation of the CSprite class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "Sprite.h"

#include "Input.h"

#include "ZzzOpenglUtil.h"

#include <crtdbg.h>		// _ASSERT() ���.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSprite::CSprite()
{
	m_aFrameTexCoord = NULL;
	m_pTexture = NULL;
}

CSprite::~CSprite()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : ���� �Ҵ��� �޸� ����.
//*****************************************************************************
void CSprite::Release()
{
	m_pTexture = NULL;
	SAFE_DELETE_ARRAY(m_aFrameTexCoord);
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ��������Ʈ�� ����.
//			   nTexID ���� �����̸� �ؽ�ó�� ���� ��������Ʈ�� ������.
//			   �ִϸ��̼��� ���� �ؽ�ó�� Ư�� �κ����� �����Ϸ��� nMaxFrame��
//			  1�� �ְ� aAniTexCoord�� �ؽ�ó ��ġ�� �ּҸ� ������ ��.
//			   fScaleX, fScaleY�� 1.0f�� �ػ� ���� �ȼ� ����.
//			   800 * 600 ���� ��ǥ�� ��� fScaleX�� '������ ���� ũ�� / 800'��
//			  fScaleY�� '������ ���� ũ�� / 600'�� �־��ָ� ��. �̶� ���ý���
//			  ��ũ�� ��ǥ(m_aScrCoord[])�� 800 * 600 ���� ��ǥ�� ��.
// �Ű� ���� : nOrgWidth	: �ؽ�ó �� �������� �ȼ� �ʺ�.
//			   nOrgHeight	: �ؽ�ó �� �������� �ȼ� ����.
//			   nTexID		: �ؽ�ó ID.(�⺻�� -1)
//			   nMaxFrame	: �� ������ ��.(�⺻�� 0)
//							(aFrameCoord�� NULL�� ��� nMaxFrame�� ���õ�.)
//			   aFrameCoord	: �� �������� �ؽ�ó ���� �ȼ� ��ǥ �迭.(�⺻��
//							 NULL)
//			   nDatumX		: ������X. (���콺 Ŀ�� Hot spot����.�⺻�� 0)
//			   nDatumY		: ������Y. (���콺 Ŀ�� Hot spot����.�⺻�� 0)
//			   bTile		: Ÿ�ϸ� ����.(�⺻�� false)
//			   nSizingDatums: ũ�� ���� �� ����.(�⺻�� SPR_SIZING_DATUMS_LT)
//							(�� : ���� ���� -> SPR_SIZING_DATUMS_RB)
//			   fScaleX		: X Ȯ��, ��� ����.
//							(���� ��ǥ�� ��ȭ ����. �⺻�� 1.0f)
//			   fScaleY		: Y Ȯ��, ��� ����.
//							(���� ��ǥ�� ��ȭ ����. �⺻�� 1.0f)
//*****************************************************************************
void CSprite::Create(int nOrgWidth, int nOrgHeight, int nTexID, int nMaxFrame,
					 SFrameCoord* aFrameCoord, int nDatumX, int nDatumY,
					 bool bTile, int nSizingDatums, float fScaleX,
					 float fScaleY)
{
	// ���� Release()�� ȣ������ �ʰ� Create()�� �� ȣ���� ��� �޸𸮰� �����
	//�� ���� �����ϱ� ����.
	Release();

	m_fOrgWidth = (float)nOrgWidth;
	m_fOrgHeight = (float)nOrgHeight;
	m_nTexID = nTexID;
	m_pTexture = Bitmaps.FindTexture(m_nTexID);

	m_fScrHeight = (float)WindowHeight / fScaleY;

	// ���ý��� ��ũ�� ��ǥ �ʱ�ȭ.
	m_aScrCoord[LT].fX = 0.0f;
	m_aScrCoord[LT].fY = m_fScrHeight;
	m_aScrCoord[LB].fX = 0.0f;
	m_aScrCoord[LB].fY = m_fScrHeight - m_fOrgHeight;
	m_aScrCoord[RB].fX = m_fOrgWidth;
	m_aScrCoord[RB].fY = m_fScrHeight - m_fOrgHeight;
	m_aScrCoord[RT].fX = m_fOrgWidth;
	m_aScrCoord[RT].fY = m_fScrHeight;

	m_nNowFrame = -1;	// �Ʒ� SetNowFrame(0) ������ �� ��ġ���� �ʱ�ȭ.

	if (-1 < m_nTexID)	// �ؽ�ó�� ���� ��.
	{
		// �ؽ�ó ��ǥ �ʱ�ȭ.
		// 0.5f�� ���͸��� ��輱�� ������ ���� �������ش�.
		m_aTexCoord[LT].fTU = 0.5f / m_pTexture->Width;
		m_aTexCoord[LT].fTV = 0.5f / m_pTexture->Height;
		m_aTexCoord[LB].fTU = 0.5f / m_pTexture->Width;
		m_aTexCoord[LB].fTV = (m_fOrgHeight - 0.5f) / m_pTexture->Height;
		m_aTexCoord[RB].fTU = (m_fOrgWidth - 0.5f) / m_pTexture->Width;
		m_aTexCoord[RB].fTV = (m_fOrgHeight - 0.5f) / m_pTexture->Height;
		m_aTexCoord[RT].fTU = (m_fOrgWidth - 0.5f) / m_pTexture->Width;
		m_aTexCoord[RT].fTV = 0.5f / m_pTexture->Height;

		// �ִϸ��̼��� ��쳪 �ؽ�ó Ư�� ��ġ �����϶�.
		if (NULL != aFrameCoord)
		{
			_ASSERT(0 < nMaxFrame);

			m_nMaxFrame = nMaxFrame;

			m_aFrameTexCoord = new STexCoord[m_nMaxFrame];

			for (int i = 0; i < m_nMaxFrame; ++i)
			{
				// 0.5f�� ���͸��� ��輱�� ������ ���� �������ش�.
				m_aFrameTexCoord[i].fTU = ((float)aFrameCoord[i].nX + 0.5f)
					/ m_pTexture->Width;
				m_aFrameTexCoord[i].fTV = ((float)aFrameCoord[i].nY + 0.5f)
					/ m_pTexture->Height;
			}

			m_nStartFrame = m_nEndFrame = 0;
			SetNowFrame(0);		// 0 ��° ���������� �ʱ�ȭ��.

			// �ִϸ��̼��� ��쳪 �ؽ�ó Ư�� ��ġ ������ ���� Ÿ�ϸ��� ��
			//�� ����.
			m_bTile = false;
		}
		else	// �ؽ�ó ��ǥ 0, 0 ��ġ�϶�.
		{
			m_nMaxFrame = 0;
			m_nStartFrame = m_nEndFrame = -1;
			m_bTile = bTile;
		}
	}
	else				// �ؽ�ó�� ���� ��.
	{
		::memset(m_aTexCoord, 0, sizeof(STexCoord) * POS_MAX);

		m_nMaxFrame = 0;
		m_nStartFrame = m_nEndFrame = -1;
		m_bTile = false;
	}

	m_byAlpha = m_byRed = m_byGreen = m_byBlue = 255;

	m_fDatumX = (float)nDatumX;
	m_fDatumY = (float)nDatumY;

	m_bRepeat = false;
	m_dDelayTime = m_dDeltaTickSum = 0.0;
	m_nSizingDatums = nSizingDatums;
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
	m_bShow = false;
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ��������Ʈ�� ����.
//			   �̹��� ������ �� ��� ��� �Ұ���.(�ִϸ��̼� �Ұ�)
//			   pImgInfo->nTexID ���� �����̸� �ؽ�ó�� ���� ��������Ʈ�� ������.
//			  (�̶� pImgInfo->nX�� pImgInfo->nY ���� 0, 0�̾�� ��)
//			   �ִϸ��̼��� ���� �ؽ�ó�� Ư�� �κ����� �����Ϸ��� pImgInfo->nX
//			  �� pImgInfo->nY�� �ؽ�ó �� �̹��� ���� �ȼ� ��ǥ�� ������ ��.
//			   fScaleX, fScaleY�� 1.0f�� �ػ� ���� �ȼ� ����.
//			   800 * 600 ���� ��ǥ�� ��� fScaleX�� '������ ���� ũ�� / 800'��
//			  fScaleY�� '������ ���� ũ�� / 600'�� �־��ָ� ��. �̶� ���ý���
//			  ��ũ�� ��ǥ(m_aScrCoord[])�� 800 * 600 ���� ��ǥ�� ��.
// �Ű� ���� : pImgInfo		: �ؽ�ó �� �̹��� ����.
//			   nDatumX		: ������X. (���콺 Ŀ�� Hot spot����.�⺻�� 0)
//			   nDatumY		: ������Y. (���콺 Ŀ�� Hot spot����.�⺻�� 0)
//			   bTile		: Ÿ�ϸ� ����.(�⺻�� false)
//			   nSizingDatums: ũ�� ���� �� ����.(�⺻�� SPR_SIZING_DATUMS_LT)
//							(�� : ���� ���� -> SPR_SIZING_DATUMS_RB)
//			   fScaleX		: X Ȯ��, ��� ����.
//							(���� ��ǥ�� ��ȭ ����. �⺻�� 1.0f)
//			   fScaleY		: Y Ȯ��, ��� ����.
//							(���� ��ǥ�� ��ȭ ����. �⺻�� 1.0f)
//*****************************************************************************
void CSprite::Create(SImgInfo* pImgInfo, int nDatumX, int nDatumY, bool bTile,
					 int nSizingDatums, float fScaleX, float fScaleY)
{
	// �ؽ�ó �� �̹��� ��ǥ�� 0, 0�� ���.
	if (pImgInfo->nX == 0 && pImgInfo->nY == 0)
		Create(pImgInfo->nWidth, pImgInfo->nHeight, pImgInfo->nTexID, 0, NULL,
			nDatumX, nDatumY, bTile, nSizingDatums, fScaleX, fScaleY);
	// �ؽ�ó �� �̹��� ��ǥ�� 0, 0�� �ƴ� Ư�� ��ġ�� ���.
	else
	{
		SFrameCoord frameCoord = { pImgInfo->nX, pImgInfo->nY };
		Create(pImgInfo->nWidth, pImgInfo->nHeight, pImgInfo->nTexID, 1,
			&frameCoord, nDatumX, nDatumY, bTile, nSizingDatums, fScaleX,
			fScaleY);
	}
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : ��������Ʈ�� �̵�.
// �Ű� ���� : nXCoord		: X��ǥ.(��ũ�� ��ǥ.)
//			   nYCoord		: Y��ǥ.(��ũ�� ��ǥ.)
//			   eChangedPram	: ������ �Ķ����.
//							  ���� ���ڸ� X�� X��ǥ��, Y�� Y��ǥ��, XY�� XY ��
//							 ǥ�� ����.(�⺻�� XY)
//*****************************************************************************
void CSprite::SetPosition(int nXCoord, int nYCoord, CHANGE_PRAM eChangedPram)
{
	// ���ؽ� ��ǥ ����. eChangedPram ���� XY��� �Ʒ��� 2�� if�� ��� ��.
	if (eChangedPram & X)	// X��ǥ�� �ٲٴ°�? 
	{
		// �̸� ������ �ʺ� ����.
		float fWidth = m_aScrCoord[RT].fX - m_aScrCoord[LT].fX;

		// ũ������ ������ �������ΰ�?
		if (IS_SIZING_DATUMS_R(m_nSizingDatums))
		{
			// ������ �������� �������� �þ� ���ٸ�, ��������Ʈ ������ ������
			//nDatumX�� ��������Ʈ ������ ������ ��°��� ����.
			// �̶� nXCoord ���� ��������Ʈ ������ ���� �ȴ�.
			m_aScrCoord[RT].fX = m_aScrCoord[RB].fX
				= (float)nXCoord + m_fOrgWidth - m_fDatumX;
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX
				= m_aScrCoord[RT].fX - fWidth;
		}
		else
		{
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX
				= (float)nXCoord - m_fDatumX;
			m_aScrCoord[RT].fX = m_aScrCoord[RB].fX
				= m_aScrCoord[LT].fX + fWidth;
		}
	}	

	if (eChangedPram & Y)	// Y��ǥ�� �ٲٴ°�?
	{
		// �̸� ������ ���̸� ����.
		float fHeight = m_aScrCoord[LT].fY - m_aScrCoord[LB].fY;

		// ũ������ ������ �Ʒ��ΰ�?
		if (IS_SIZING_DATUMS_B(m_nSizingDatums))
		{
			m_aScrCoord[LB].fY = m_aScrCoord[RB].fY =
				m_fScrHeight - (float)nYCoord - m_fOrgHeight + m_fDatumY;

			m_aScrCoord[LT].fY = m_aScrCoord[RT].fY
				= m_aScrCoord[LB].fY + fHeight;
		}
		else
		{
			m_aScrCoord[LT].fY = m_aScrCoord[RT].fY
				= m_fScrHeight - (float)nYCoord + m_fDatumY;
			m_aScrCoord[LB].fY = m_aScrCoord[RB].fY
				= m_aScrCoord[LT].fY - fHeight;
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : SetSize()
// �Լ� ���� : ũ������ �������� ��������Ʈ�� ũ�� ����.
// �Ű� ���� : nWidth		: �ʺ�.(�ȼ� ����.)
//			   nHeight		: ����.(�ȼ� ����.)
//			   eChangedPram	: ������ �Ķ����. X�� �ʺ�, Y�� ���̸�, XY�� ��
//							 �� ����.(�⺻�� XY)
//*****************************************************************************
void CSprite::SetSize(int nWidth, int nHeight, CHANGE_PRAM eChangedPram)
{
	// eChangedPram ���� XY��� �Ʒ��� 2�� if�� ��� ��.
	if (eChangedPram & X)	// ���� ũ�� �����ΰ�?
	{
		// ũ������ ������ �������ΰ�?
		if (IS_SIZING_DATUMS_R(m_nSizingDatums))
		{
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX
				= m_aScrCoord[RT].fX - (float)nWidth;
			if (m_bTile)	// Ÿ�ϸ�.
				m_aTexCoord[LT].fTU = m_aTexCoord[LB].fTU
					= m_aTexCoord[RT].fTU - nWidth / m_pTexture->Width;
		}
		else
		{
			m_aScrCoord[RT].fX = m_aScrCoord[RB].fX
				= m_aScrCoord[LT].fX + (float)nWidth;
			if (m_bTile)	// Ÿ�ϸ�.
				m_aTexCoord[RT].fTU = m_aTexCoord[RB].fTU
					= nWidth / m_pTexture->Width;
		}
	}
	if (eChangedPram & Y)	// ���� ũ�� �����ΰ�?
	{
		// ũ������ ������ �Ʒ����ΰ�?
		if (IS_SIZING_DATUMS_B(m_nSizingDatums))
		{
			m_aScrCoord[LT].fY = m_aScrCoord[RT].fY
				= m_aScrCoord[LB].fY + (float)nHeight;
			if (m_bTile)	// Ÿ�ϸ�.
				m_aTexCoord[LT].fTV = m_aTexCoord[RT].fTV
					= m_aTexCoord[LB].fTV - nHeight / m_pTexture->Height;
		}
		else
		{
			m_aScrCoord[LB].fY = m_aScrCoord[RB].fY
				= m_aScrCoord[LT].fY - (float)nHeight;
			if (m_bTile)	// Ÿ�ϸ�.
				m_aTexCoord[LB].fTV = m_aTexCoord[RB].fTV
					= nHeight / m_pTexture->Height;
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : PtInSprite()
// �Լ� ���� : ��������Ʈ �ȿ� �˻��� ���� ������ TRUE, ������ FALSE�� ����.
// �Ű� ���� : lXPos	: �˻��� ���� X��ǥ.
//			   lYPos	: �˻��� ���� Y��ǥ.
//*****************************************************************************
BOOL CSprite::PtInSprite(long lXPos, long lYPos)
{
	if (!m_bShow)	// �������� �ʴ´ٸ� �Ǵ����� �ʰ� ������ FALSE ����.
		return FALSE;

	// �˻��� �� ����ü(pt) �ʱ�ȭ.
	POINT pt = { lXPos, lYPos };

	RECT rc = {
		long(m_aScrCoord[LT].fX * m_fScaleX),
		long((m_fScrHeight - m_aScrCoord[LT].fY) * m_fScaleY),
		long(m_aScrCoord[RB].fX * m_fScaleX),
		long((m_fScrHeight - m_aScrCoord[RB].fY) * m_fScaleY)
	};

	// rc�ȿ� pt�� �ִ°�?
	return ::PtInRect(&rc, pt);
}

//*****************************************************************************
// �Լ� �̸� : CursorInObject()
// �Լ� ���� : ��������Ʈ �ȿ� ���콺 Ŀ���� ������ TRUE, ������ FALSE�� ����.
//*****************************************************************************
BOOL CSprite::CursorInObject()
{
	CInput& rInput = CInput::Instance();

	return PtInSprite(rInput.GetCursorX(), rInput.GetCursorY());
}

//*****************************************************************************
// �Լ� �̸� : SetAction()
// �Լ� ���� : ���� ������ ��ȣ�� ������ ������ ��ȣ�� �����Ͽ� ���ʷ� �ִϸ���
//			  �� ��Ŵ. ���� ������ ��ȣ�� ������ ������ ��ȣ�� ���ٸ� �� ������
//			  �� ������.(�̶� ���Ŀ� Update()�� ȣ��Ǿ�� ��.)
// �Ű� ���� : nStartFrame	: ���� ������ ��ȣ.
//			   nEndFrame	: ������ ������ ��ȣ.
//			   dDelayTime	: ������ �� ���� �ð�.(�⺻�� 0.0)
//			   bRepeat		: Animation �ݺ� ����.(�⺻�� true)
//*****************************************************************************
void CSprite::SetAction(int nStartFrame, int nEndFrame, double dDelayTime,
						bool bRepeat)
{
	if (1 >= m_nMaxFrame)	// �ִϸ��̼��� ���� ���.
		return;

	_ASSERT(nStartFrame <= nEndFrame && nStartFrame >= 0
		&& nEndFrame < m_nMaxFrame);

	m_nStartFrame = m_nNowFrame = nStartFrame;
	m_nEndFrame = nEndFrame;
	m_bRepeat = bRepeat;
	m_dDelayTime = dDelayTime;
}

//*****************************************************************************
// �Լ� �̸� : SetNowFrame()
// �Լ� ���� : ���� �������� nFrame���� �ٲ�.
// �Ű� ���� : nFrame	: �ٲ� ������ ��ȣ.(0 �̻��� ��)
//*****************************************************************************
void CSprite::SetNowFrame(int nFrame)
{
	// �ִϸ��̼��� ���ų� �����ӹ�ȣ�� ������.
	if (NULL == m_aFrameTexCoord || nFrame == m_nNowFrame)
		return;

//	_ASSERT(nFrame >= m_nStartFrame && nFrame <= m_nEndFrame);

	// �ִϸ��̼� ������ �����.
	if (nFrame < m_nStartFrame || nFrame > m_nEndFrame)
		return;

	m_nNowFrame = nFrame;

	float fTUWidth = m_aTexCoord[RT].fTU - m_aTexCoord[LT].fTU;
	float fTVHeight = m_aTexCoord[LB].fTV - m_aTexCoord[LT].fTV;

	m_aTexCoord[LT] = m_aFrameTexCoord[m_nNowFrame];

	m_aTexCoord[RT].fTU = m_aFrameTexCoord[m_nNowFrame].fTU + fTUWidth;
	m_aTexCoord[RT].fTV = m_aFrameTexCoord[m_nNowFrame].fTV;

	m_aTexCoord[LB].fTU = m_aFrameTexCoord[m_nNowFrame].fTU;
	m_aTexCoord[LB].fTV = m_aFrameTexCoord[m_nNowFrame].fTV + fTVHeight;

	m_aTexCoord[RB].fTU = m_aTexCoord[RT].fTU;
	m_aTexCoord[RB].fTV = m_aTexCoord[LB].fTV;
}

//*****************************************************************************
// �Լ� �̸� : Update()
// �Լ� ���� : m_dDelayTime��ŭ �ð��� ������ ���� ���������� �ٲ�.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//							  (�⺻��: 0.0)
//*****************************************************************************
void CSprite::Update(double dDeltaTick)
{
	if (!m_bShow)	// �������� ���� ��� return.
		return;

	if (1 >= m_nMaxFrame)	// �ִϸ��̼��� ���� ���.
		return;

	m_dDeltaTickSum += dDeltaTick;

	// m_dDelayTime��ŭ �ð��� �����°�?
	if (m_dDeltaTickSum >= m_dDelayTime)
	{
		int nFrame = m_nNowFrame;

		if (m_bRepeat)	// �ݺ��ΰ�?
			// ���� �������� ������Ű�� �̰��� ������ ������ ���� ũ�� ���� ��
			//�������� ��ȯ.
			nFrame = ++nFrame > m_nEndFrame ? m_nStartFrame : nFrame;
		else			// �ݺ��� �ƴϸ�.
			// ���� �������� ������Ű�� �̰��� ������ ������ ���� ũ�� ������
			//���������� ����.
			nFrame = ++nFrame > m_nEndFrame ? m_nEndFrame : nFrame;

		SetNowFrame(nFrame);

		m_dDeltaTickSum = 0.0;
	}
	// �� Ŭ���������� �� ������ ���� ������ ������ ���� ����. �Ļ� Ŭ������
	//CCursor Ŭ���������� SetPosition()�� ȣ���ؼ� ������ ������ ��.
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ����.
//*****************************************************************************
void CSprite::Render()
{
	if (!m_bShow)
		return;

	if (-1 < m_nTexID)	// �ؽ�ó�� �ִ� ���.
	{
		// TextureEnable�� ��¿ �� ���� ����� �̤�.
		if (!TextureEnable) 
		{
			TextureEnable = true;
			::glEnable(GL_TEXTURE_2D);
		}

		BindTexture(m_nTexID);

		::glBegin(GL_TRIANGLE_FAN);

		::glColor4ub(m_byRed, m_byGreen, m_byBlue, m_byAlpha);

		for (int i = LT; i < POS_MAX; ++i)
		{
			::glTexCoord2f(m_aTexCoord[i].fTU, m_aTexCoord[i].fTV);
			::glVertex2f(m_aScrCoord[i].fX * m_fScaleX,
				m_aScrCoord[i].fY * m_fScaleY);
		}

		::glEnd();
	}
	else				// �ؽ�ó�� ���� ���.
	{
//		::DisableTexture();	// �̤� ����ϱ� �Ⱦ���.
		if (TextureEnable) 
		{
			TextureEnable = false;
			::glDisable(GL_TEXTURE_2D);
		}

		::glBegin(GL_TRIANGLE_FAN);

		::glColor4ub(m_byRed, m_byGreen, m_byBlue, m_byAlpha);
		for (int i = LT; i < POS_MAX; ++i)
			::glVertex2f(m_aScrCoord[i].fX * m_fScaleX,
				m_aScrCoord[i].fY * m_fScaleY);

		::glEnd();
	}
}