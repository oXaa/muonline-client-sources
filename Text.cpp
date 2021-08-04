//*****************************************************************************
// File: Text.cpp
//
// Desc: implementation of the CText class.
//
// producer: Ahn Sang-Kyu (2007. 2. 6)
//*****************************************************************************

#include "stdafx.h"
#include "Text.h"
#include <crtdbg.h>  // _ASSERT() ���.

#ifdef NEW_USER_INTERFACE_FONT

extern bool TextureEnable;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText() : m_pwTexImg(NULL)
{
}

CText::~CText()
{
	Release();
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : �ؽ�ó �� ���ؽ� ���� �� ������ ��� �ʱ�ȭ.
//			   �����ϸ� nFontHeight + eStyle ���� 16�� ���� �ʰ� ����. �Ѵ´ٸ�
//			  �ؽ�ó ���̰� 32�� �ǹǷ� 2�谡 �Ǿ������.
// �Ű� ���� : lpszFont		: ��Ʈ �̸� ���ڿ�.
//			   nFontHeight	: ��Ʈ ����.(�ȼ� ����)
//							  �ݵ�� �� ���̷� ��Ÿ���� �ʴ´ٴ� ���� ��������.
//							�� ���� ���� Ŭ���� ������ �۰� ���� �� �ִ�.
//			   nTextMaxLen	: Text �ִ� ���� ����.
//							  �ּҷ� �����ִ� ���� ����. �� ���� ���� �ؽ�ó ũ
//							�Ⱑ �����ȴ�.
//			   eStyle		: TS_NORMAL, TS_SHADOW, TS_OUTLINE �� �ϳ�.
//							(�⺻���� TS_SHADOW).
//							  Text�� �ʺ�, ���̰� TS_SHADOW�� 1�ȼ�, TS_OUTLINE
//							�� 2�ȼ� �þ.
//			   eType		: TT_NORMAL, TT_MONEY, TT_PASSWORD �� �ϳ�.
//							(�⺻�� TT_NORMAL)
//							  TT_MONEY�� 3�ڸ� ���� ','�� ������, TT_PASSWORD��
//							� ���ڿ��� ���� �ֵ� '*'�� ��������. m_szText��
//							������ ��ȭ����.
//*****************************************************************************
void CText::Create(LPCTSTR lpszFont, int nFontHeight, int nTextMaxLen,
				   TEXT_STYLE eStyle, TEXT_TYPE eType)
{
	// �ؽ�ó�� ���̴� �ִ� TB_HEIGHT�̹Ƿ� nFontHeight�� ����.
	//eStyle�� ���� ������ �� �Լ� ���� ����.
	_ASSERT(0 < nFontHeight && TB_HEIGHT >= nFontHeight + eStyle);

	// �ؽ�Ʈ ��Ʈ�� ������Ʈ�� ��Ʈ�� �߰��ϰ�, ���� �ִ� �ʺ� ����.
	//���� ��Ʈ, ũ���� ���� �ִ� �ʺ� ����.
	CTextBitmap& rTextBitmap = CTextBitmap::Instance();
	m_nCharMaxWidth = rTextBitmap.AddFont(lpszFont, nFontHeight);

// �ؽ�ó �ʺ� ���ϱ�.
	// �ִ� ���� �� ��ŭ ǥ���ϱ� ���� �ּ����� �ؽ�ó �ʺ�.
	int nTempWidth = nTextMaxLen * m_nCharMaxWidth + eStyle;
	// �ؽ�ó �ʺ� 8���� ��� ����(��� ����Ʈ)�Ͽ� �ִ� ��Ʈ�� ũ��
	//(TB_WIDTH)���� �ּ����� �ؽ�ó �ʺ�� ���Ͽ� ����.
	for (m_nTexWidth = 8; m_nTexWidth < TB_WIDTH; m_nTexWidth <<= 1)
		if (m_nTexWidth >= nTempWidth)
			break;
// �ؽ�ó ���� ���ϱ�.
	m_nTexHeight = 16 >= nFontHeight + eStyle ? 16 : 32;

	Release();		// �ؽ�ó�� ������ ����.

// �ؽ�ó ����.
	m_pwTexImg = new WORD[m_nTexWidth * m_nTexHeight];
	::memset(m_pwTexImg, 0, m_nTexWidth * m_nTexHeight * sizeof(WORD));

	::glGenTextures(1, &m_uiTexID);				// �ؽ�ó ID ����.
	::glBindTexture(GL_TEXTURE_2D, m_uiTexID);	// �ؽ�ó ���ε�.
	// �ؽ�ó �̹��� ����. R(5bit)G(5bit)B(5bit)A(1bit)�� 16��Ʈ �÷���.
	// ó���ӵ��� ���� �޸� ũ��� ���� �ؽ�Ʈ�� 32��Ʈ �÷����� ����� �ʿ�
	//�� ���ٴ� �Ǵ�.
	::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5_A1, m_nTexWidth, m_nTexHeight, 0,
		GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, m_pwTexImg);
// �ؽ�ó ȿ�� ����.
//	::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// �ؽ�ó ���͸�.
//	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	::strcpy(m_szFont, lpszFont);		// ��Ʈ �̸� ����.
	m_nFontHeight = nFontHeight;		// ��Ʈ ���� ����.
	// �ؽ�Ʈ �ִ� ���̴� �ؽ�ó ������ ������� �ȵ�.
	int nTempLen = m_nTexWidth / m_nCharMaxWidth;
	m_nTextMaxLen = nTempLen > nTextMaxLen ? nTextMaxLen : nTempLen;
	SetTextColor(RGB(255, 255, 255));	// �ؽ�Ʈ �÷�.
	m_eStyle = eStyle;					// �ؽ�Ʈ ��Ÿ��.
	m_eType = eType;					// �ؽ�Ʈ Ÿ��.
	m_byAlign = TA_LEFT;				// �ؽ�Ʈ ���� ���.
	m_bShow = false;
	::memset(m_szText, 0, TEXT_MAX_LEN + 1);// ������ ���ڿ�.
	m_nTextWidth = 0;
	m_nDatumX = 0;

// ���ؽ� ����.
	// ���ý��� ��ũ�� ��ǥ �ʱ�ȭ.
	m_aScrCoord[LT].fX = 0.0f;
	m_aScrCoord[LT].fY = (float)WindowHeight;
	m_aScrCoord[LB].fX = 0.0f;
	m_aScrCoord[LB].fY = float(WindowHeight - m_nTexHeight);
	m_aScrCoord[RB].fX = (float)m_nTexWidth;
	m_aScrCoord[RB].fY = float(WindowHeight - m_nTexHeight);
	m_aScrCoord[RT].fX = (float)m_nTexWidth;
	m_aScrCoord[RT].fY = (float)WindowHeight;

	// �ؽ�ó ��ǥ �ʱ�ȭ.
	m_aTexCoord[LT].fTU = 0.0f;
	m_aTexCoord[LT].fTV = 0.0f;
	m_aTexCoord[LB].fTU = 0.0f;
	m_aTexCoord[LB].fTV = 1.0f;
	m_aTexCoord[RB].fTU = 1.0f;
	m_aTexCoord[RB].fTV = 1.0f;
	m_aTexCoord[RT].fTU = 1.0f;
	m_aTexCoord[RT].fTV = 0.0f;

/*	m_aTexCoord[LT].fTU = 0.5f / float(m_nTexWidth);
	m_aTexCoord[LT].fTV = 0.5f / float(TB_HEIGHT);
	m_aTexCoord[LB].fTU = 0.5f / float(m_nTexWidth);
	m_aTexCoord[LB].fTV = 1.0f - 0.5f / float(TB_HEIGHT);
	m_aTexCoord[RB].fTU = 1.0f - 0.5f / float(m_nTexWidth);
	m_aTexCoord[RB].fTV = 1.0f - 0.5f / float(TB_HEIGHT);
	m_aTexCoord[RT].fTU = 1.0f - 0.5f / float(m_nTexWidth);
	m_aTexCoord[RT].fTV = 0.5f / float(TB_HEIGHT);
*/
	m_byAlpha = m_byRed = m_byGreen = m_byBlue = 255;
}

//*****************************************************************************
// �Լ� �̸� : Release()
// �Լ� ���� : �ؽ�ó�� ������ ����.
//*****************************************************************************
void CText::Release()
{
	if (m_pwTexImg)
	{
		::glDeleteTextures(1, &m_uiTexID);
		delete [] m_pwTexImg;
		m_pwTexImg = NULL;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetSize()
// �Լ� ���� : ���ؽ� �簢�� ũ�� ����.
// �Ű� ���� : nWidth	: ���ؽ� �簢�� �ʺ�.
//			   nHeight	: ���ؽ� �簢�� ����.
//*****************************************************************************
/*void CText::SetSize(int nWidth, int nHeight)
{
	m_nWidth = m_nTexWidth > nWidth ? nWidth : m_nTexWidth;
	m_aTLVertex[1].x = m_aTLVertex[3].x = m_aTLVertex[0].x + m_nWidth;
	m_aTLVertex[1].tu = m_aTLVertex[3].tu
		= (float)m_nWidth / (float)m_nTexWidth;

	m_nHeight = TB_HEIGHT > nHeight ? nHeight : TB_HEIGHT;
	m_aTLVertex[2].y = m_aTLVertex[3].y = m_aTLVertex[0].y + m_nHeight;
	m_aTLVertex[2].tv = m_aTLVertex[3].tv
		= (float)m_nHeight / (float)TB_HEIGHT;
}
*/
//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : ���ؽ� �簢�� ��ġ ����.
// �Ű� ���� : nXCoord		: X��ǥ.
//			   nYCoord		: Y��ǥ.
//			   eChangedPram	: ������ �Ķ����.
//							  ���� ���ڸ� X�� X��ǥ��, Y�� Y��ǥ��, XY�� XY ��
//							 ǥ�� ����.(�⺻�� XY)
//*****************************************************************************
void CText::SetPosition(int nXCoord, int nYCoord, CHANGE_PRAM eChangedPram)
{
	// ���ؽ� ��ǥ ����. eChangedPram ���� XY��� �Ʒ��� 2�� if�� ��� ��.
	if (eChangedPram & X)	// X��ǥ�� �ٲٴ°�? 
	{
		// �̸� ������ �ʺ� ����.
		float fWidth = m_aScrCoord[RT].fX - m_aScrCoord[LT].fX;

		m_nDatumX = nXCoord;

		switch (m_byAlign)
		{
		case TA_CENTER:
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX
				= (float)(m_nDatumX - m_nTextWidth / 2);
			break;

		case TA_RIGHT:
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX
				= (float)(m_nDatumX - m_nTextWidth);
			break;

		default:
			m_aScrCoord[LT].fX = m_aScrCoord[LB].fX = (float)m_nDatumX;
		}

		m_aScrCoord[RT].fX = m_aScrCoord[RB].fX = m_aScrCoord[LT].fX + fWidth;
	}

	if (eChangedPram & Y)	// Y��ǥ�� �ٲٴ°�?
	{
		// �̸� ������ ���̸� ����.
		float fHeight = m_aScrCoord[LT].fY - m_aScrCoord[LB].fY;

		m_aScrCoord[LT].fY = m_aScrCoord[RT].fY = float(WindowHeight - nYCoord);
		m_aScrCoord[LB].fY = m_aScrCoord[RB].fY = m_aScrCoord[LT].fY - fHeight;
	}
}

//*****************************************************************************
// �Լ� �̸� : SetText()
// �Լ� ���� : ���ڿ��� ��Ʈ�ʿ� ���� �ؽ�ó�� ����.
// �Ű� ���� : lpszText	: ǥ���� ���ڿ�.
//*****************************************************************************
void CText::SetText(LPCTSTR lpszText)
{
//	_ASSERT(::strlen(lpszText) <= TEXT_MAX_LEN);

	if (TT_MONEY == m_eType)	// ��� ���°� �� Ÿ���̶��.
	{
		char szMoney[TEXT_MAX_LEN + 1];
		*szMoney = 0;	// �ʱ�ȭ.
		// �Ű������� �� Ÿ��(3�ڸ�����','�� ����)���� ������.
		NUMBERFMT nFmt = { 0, 0, 3, ".", ",", 1 };
		::GetNumberFormat(NULL, NULL, lpszText, &nFmt, szMoney,
			TEXT_MAX_LEN + 1);

		// �ִ� ���� �� ��ŭ�� ���Ͽ� �ؽ�Ʈ�� ������ �ʾҴٸ� �׳� ����.
		if (0 == strncmp(m_szText, szMoney, m_nTextMaxLen))
			return;
		// �ִ� ���� �� ��ŭ�� m_szText�� ����.
		::strncpy(m_szText, szMoney, m_nTextMaxLen);
	}
	else
	{
		// �ִ� ���� �� ��ŭ�� ���Ͽ� �ؽ�Ʈ�� ������ �ʾҴٸ� �׳� ����.
		if (0 == strncmp(m_szText, lpszText, m_nTextMaxLen))
			return;
		// �ִ� ���� �� ��ŭ�� m_szText�� ����.
		::strncpy(m_szText, lpszText, m_nTextMaxLen);
	}

	// ���� �� ���� ��Ʈ �̸��� ũ��� ��Ʈ ����.
	CTextBitmap& rTextBitmap = CTextBitmap::Instance();
	rTextBitmap.SelFont(m_szFont, m_nFontHeight);

	if (TT_PASSWORD == m_eType)	// ��ȣ �Է��ΰ�?
	{
		// ��Ʈ�ʿ� '*'�� ���� �� ��ŭ ��� �ȼ� �ʺ� ����.
		char szAsterisk[TEXT_MAX_LEN + 1];
		::strcpy(szAsterisk, m_szText);
		::_strset(szAsterisk, '*');
		m_nTextWidth = rTextBitmap.TextOut(
			szAsterisk, m_crTextColor, m_eStyle, m_crStyleColor);
	}
	else
		// ��Ʈ�ʿ� ���ڿ��� ���� ���ڿ� �ȼ� �ʺ� ����.
		m_nTextWidth = rTextBitmap.TextOut(
			m_szText, m_crTextColor, m_eStyle, m_crStyleColor);

// ��Ʈ���� �ؽ�ó�� ī��.
	// ��Ʈ�ʿ��� ������ ���� ��ġ.
	WORD* pwSrc = rTextBitmap.GetBitmap();
	WORD* pwDst = m_pwTexImg;			// �ؽ�ó �̹����� ����� ���� ��ġ.
	// �Ʒ� �ڵ尡 nLockWidth = m_nTextWidth �̶�� ǥ�õ� ���ڿ��� ���� ����
	//�ʺ� ���� ��쿡�� �� ���� ��ŭ ���� �ؽ�Ʈ�� ���̰� �ǹǷ� �ȵ�.
	int nLockWidth = m_nTextMaxLen * m_nCharMaxWidth;	// ������ �ʺ�.
	// �Ʒ� glTexSubImage2D()�Լ��� ���������� �ؽ�ó �̹����� 32bit�� ī���ϴ�
	//�� �ϴ�. �׷� ������ ���⼭ ���� �ؽ�ó �̹����� 16bit�÷��̹Ƿ�
	//nLockWidth�� Ȧ���� ���� �� �ȼ��� �и��� �ȴ�. ���� nLockWidth�� Ȧ��
	//�� ���� nLockWidth�� 1���� �����־� ¦���� ����� �׷� ������ ���´�. ��
	//��ó �̹����� 32bit�̶�� �̷� �۾��� ���ʿ��� ���ϴ�.
	int nSrcNextLineGap
		= nLockWidth % 2 ? TB_WIDTH - ++nLockWidth : TB_WIDTH - nLockWidth;
	int nLockHeight = m_nFontHeight + m_eStyle;

	::memset(pwDst, 0, nLockWidth * nLockHeight * sizeof(WORD));
	int x, y;
	for (y = 0; y < nLockHeight; ++y)	// �ؽ�Ʈ ���� ��ŭ �ݺ�.
    {
		for (x = 0; x < nLockWidth; ++x)// ������ �ʺ� ��ŭ �ݺ�.
        {
			if (*pwSrc)				// ���� ������.
			{
				 *pwSrc <<= 1;		// ���İ� �ڸ��� �� ������ bit�̹Ƿ�.
				 *pwSrc |= 0x0001;	// ���İ� ����.(���İ��� 0�̸� �Ⱥ��̹Ƿ�)
				 *pwDst = *pwSrc;	// ����.
			}
			++pwDst;
			++pwSrc;
        }
		pwSrc += nSrcNextLineGap;				// ���� �ȼ� ��������.
		// �ؽ�ó �̹����� pwDst�� �Ʒ� glTexSubImage2D()�Լ����� nLockWidth��
		//�˸� �˾Ƽ� �̹����� ����(����)�����ֱ� ������ ���� �ȼ� �������� ��
		//���ϴ� �ڵ�(�� : pwDst += nDstNextLineGap;)�� �ʿ䰡 ����.
    }

	::glBindTexture(GL_TEXTURE_2D, m_uiTexID);	// �ؽ�ó ���ε�.
	// �ٲ� �ؽ�ó �̹����� �ٽ� ����.
	::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, nLockWidth, nLockHeight,
		GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, m_pwTexImg);

// �ý�Ʈ ������ TA_RIGHT�̰ų� TA_CENTER�� ���� �ٽ� ��ġ�� �����.
	if (TA_RIGHT == m_byAlign || TA_CENTER == m_byAlign)
		SetPosition(m_nDatumX, 0, X);
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ������ ����.
//*****************************************************************************
void CText::Render()
{
	if (m_bShow)	// �����شٸ� ������ ��.
	{
		// TextureEnable�� ��¿ �� ���� ����� �̤�.
		if (!TextureEnable) 
		{
			TextureEnable = true;
			::glEnable(GL_TEXTURE_2D);
		}

//		::EnableAlphaTest();

		::glBindTexture(GL_TEXTURE_2D, m_uiTexID);

		::glBegin(GL_TRIANGLE_FAN);
		::glColor4ub(m_byRed, m_byGreen, m_byBlue, m_byAlpha);
		for (int i = LT; i < POS_MAX; ++i)
		{
			::glTexCoord2f(m_aTexCoord[i].fTU, m_aTexCoord[i].fTV);
			::glVertex2f(m_aScrCoord[i].fX, m_aScrCoord[i].fY);
		}
		::glEnd();
	}
}

#endif //NEW_USER_INTERFACE_FONT