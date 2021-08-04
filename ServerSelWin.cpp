//*****************************************************************************
// File: ServerSelWin.cpp
//
// Desc: implementation of the CServerSelWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "ServerSelWin.h"
#include "Input.h"
#include "UIMng.h"

#ifndef KJH_ADD_SERVER_LIST_SYSTEM				// #ifndef
#include "ZzzScene.h"	// ServerList ���� ���� ����.
#endif // KJH_ADD_SERVER_LIST_SYSTEM
#include "local.h"
#include "ZzzOpenglUtil.h"

#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "wsclientinline.h"
#include "UIControls.h"
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
#include "GameCensorship.h"
#include "ServerListManager.h"
#endif // KJH_ADD_SERVER_LIST_SYSTEM

#define	SSW_GAP_WIDTH	28		// ���� �׷� ��ư�� ���� ��ư�� �� �ʺ�.
#define	SSW_GAP_HEIGHT	5		// ���� ��ư�� �׽�Ʈ ���� �׷� ��ư�� �� ����.
#define	SSW_GB_POS_X	16		// ȥ�⵵ ������ ���� ��ư���κ����� X ��ġ.
#define	SSW_GB_POS_Y	19		// ȥ�⵵ ������ ���� ��ư���κ����� Y ��ġ.

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;
#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
extern int ServerSelectHi;
extern int ServerLocalSelect;
#endif // KJH_ADD_SERVER_LIST_SYSTEM

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
using namespace SEASON3A;
#endif // KJH_ADD_SERVER_LIST_SYSTEM

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerSelWin::CServerSelWin()
{

}

CServerSelWin::~CServerSelWin()
{

}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ���� ���� â ����.
//*****************************************************************************
void CServerSelWin::Create()
{
// �⺻ ������ ����.
	CWin::Create(0, 0, -2);

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	m_iSelectServerBtnIndex = -1;

	int i;
	// ���� �׷� ��ư ����. (21��)
	for (i = 0; i < SSW_SERVER_G_MAX; ++i)
	{
		m_aServerGroupBtn[i].Create(SERVER_GROUP_BTN_WIDTH, SERVER_GROUP_BTN_HEIGHT, BITMAP_LOG_IN, 4, 2, 1, -1, 3);
		CWin::RegisterButton(&m_aServerGroupBtn[i]);
	}

	// ���� ��ư, ���� ȥ�� ������ ����. (�����׷�� 16��)
	for (i = 0; i < SSW_SERVER_MAX; ++i)
	{
		// ������ư
		m_aServerBtn[i].Create(SERVER_BTN_WIDTH, SERVER_BTN_HEIGHT, BITMAP_LOG_IN+1, 3, 2, 1);
		CWin::RegisterButton(&m_aServerBtn[i]);

		// ����ȥ�������
		m_aServerGauge[i].Create(160, 4, BITMAP_LOG_IN+2);				
	}

	// ��� ��������Ʈ �¿� ����.
	SImgInfo aiiDeco[2] = 
	{
		{ BITMAP_LOG_IN+3, 0, 0, 68, 95 },
		{ BITMAP_LOG_IN+3, 68, 0, 68, 95 }
	};
	m_aBtnDeco[0].Create(&aiiDeco[0], 8, 19);	// ��
	m_aBtnDeco[1].Create(&aiiDeco[1], 60, 19);	// ��

	// ȭ��ǥ ��������Ʈ �¿� ����.
	SImgInfo aiiArrow[2] = 
	{
		{ BITMAP_LOG_IN+3, 136, 0, 23, 29 },
		{ BITMAP_LOG_IN+3, 136, 30, 23, 29 }
	};
	m_aArrowDeco[0].Create(&aiiArrow[0], 1, 2);	// ��
	m_aArrowDeco[1].Create(&aiiArrow[1], 23, 2);	// ��
	
	// ���� ���� ��� ����.
	SImgInfo aiiDescBg[WE_BG_MAX] = 
	{
		{ BITMAP_LOG_IN+11, 0, 0, 4, 4 },	// �߾�
		{ BITMAP_LOG_IN+12, 0, 0, 512, 6 },	// ��
		{ BITMAP_LOG_IN+12, 0, 6, 512, 6 },	// ��
		{ BITMAP_LOG_IN+13, 0, 0, 3, 4 },	// ��
		{ BITMAP_LOG_IN+13, 3, 0, 3, 4 }	// ��
	};
	m_winDescription.Create(aiiDescBg, 1, 10);
	m_winDescription.SetLine(10);

	// ������ ������ ����.
	CWin::SetSize((SERVER_GROUP_BTN_WIDTH + SSW_GAP_WIDTH) * 2 +SERVER_BTN_WIDTH, 
					SERVER_BTN_HEIGHT*SSW_SERVER_MAX + SSW_GAP_HEIGHT*2 + SERVER_GROUP_BTN_HEIGHT+m_winDescription.GetHeight());

#else // KJH_ADD_SERVER_LIST_SYSTEM
	int i;
// ���� �׷� ��ư ����. (21��)
	for (i = 0; i < SSW_SERVER_G_MAX; ++i)
	{
		m_abtnServerG[i].Create(108, 26, BITMAP_LOG_IN, 4, 2, 1, -1, 3);
		CWin::RegisterButton(&m_abtnServerG[i]);
	}
// ���� ��ư, ���� ȥ�� ������ ����. (�����׷�� 16��)
	for (i = 0; i < SSW_SERVER_MAX; ++i)
	{
		m_abtnServer[i].Create(193, 26, BITMAP_LOG_IN+1, 3, 2, 1);	// ������ư
		CWin::RegisterButton(&m_abtnServer[i]);
		m_agbServer[i].Create(160, 4, BITMAP_LOG_IN+2);				// ����ȥ�������
	}

	// ��� ��������Ʈ �¿� ����.
	SImgInfo aiiDeco[2] = 
	{
		{ BITMAP_LOG_IN+3, 0, 0, 68, 95 },
		{ BITMAP_LOG_IN+3, 68, 0, 68, 95 }
	};
	m_asprDeco[0].Create(&aiiDeco[0], 8, 19);	// ��
	m_asprDeco[1].Create(&aiiDeco[1], 60, 19);	// ��
	// ȭ��ǥ ��������Ʈ �¿� ����.
	SImgInfo aiiArrow[2] = 
	{
		{ BITMAP_LOG_IN+3, 136, 0, 23, 29 },
		{ BITMAP_LOG_IN+3, 136, 30, 23, 29 }
	};
	m_asprArrow[0].Create(&aiiArrow[0], 1, 2);	// ��
	m_asprArrow[1].Create(&aiiArrow[1], 23, 2);	// ��
	
	// ���� ���� ��� ����.
	SImgInfo aiiDescBg[WE_BG_MAX] = 
	{
		{ BITMAP_LOG_IN+11, 0, 0, 4, 4 },	// �߾�
		{ BITMAP_LOG_IN+12, 0, 0, 512, 6 },	// ��
		{ BITMAP_LOG_IN+12, 0, 6, 512, 6 },	// ��
		{ BITMAP_LOG_IN+13, 0, 0, 3, 4 },	// ��
		{ BITMAP_LOG_IN+13, 3, 0, 3, 4 }	// ��
	};
	m_winDescBg.Create(aiiDescBg, 1, 10);
	m_winDescBg.SetLine(10);

// ������ ������ ����.
	CWin::SetSize(
		(m_abtnServerG[0].GetWidth() + SSW_GAP_WIDTH) * 2
		+ m_abtnServer[0].GetWidth(),
		m_abtnServer[0].GetHeight() * SSW_SERVER_MAX + SSW_GAP_HEIGHT * 2
		+ m_abtnServerG[0].GetHeight() + m_winDescBg.GetHeight());

	::memset(m_aszDesc, 0, sizeof(char) * SSW_DESC_LINE_MAX * SSW_DESC_ROW_MAX);

	m_nSelServerG = -1;
	m_nServerGCount = 0;
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void CServerSelWin::PreRelease()
{
	int i;

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	for (i = 0; i < SSW_SERVER_MAX; ++i)
	{
		m_aServerGauge[i].Release();
	}
	
	for (i = 0; i < 2; ++i)
	{
		m_aBtnDeco[i].Release();
		m_aArrowDeco[i].Release();
	}
	
	m_winDescription.Release();
#else // KJH_ADD_SERVER_LIST_SYSTEM
	for (i = 0; i < SSW_SERVER_MAX; ++i)
		m_agbServer[i].Release();

	for (i = 0; i < 2; ++i)
	{
		m_asprDeco[i].Release();
		m_asprArrow[i].Release();
	}

	m_winDescBg.Release();
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void CServerSelWin::SetPosition(int nXCoord, int nYCoord)
{
	CWin::SetPosition(nXCoord, nYCoord);

#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	int nServerGBtnWidth = m_aServerGroupBtn[0].GetWidth();	// ���� �׷� ��ư �ʺ�.
	int nServerGBtnHeight = m_aServerGroupBtn[0].GetHeight();// ���� �׷� ��ư ����.
	int nServerBtnWidth = m_aServerBtn[0].GetWidth();	// ���� ��ư �ʺ�.
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	int nServerBtnHeight = m_aServerBtn[0].GetHeight();	// ���� ��ư ����.
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
	int nDescGgHeight = m_winDescription.GetHeight();
	int nBtnPosY;
	int i;
	
	// ���� �׷� ��ư.
	// ���� �׷� ��ư Y ��ġ ������.
	int nServerGBtnBasePosY = nYCoord + CWin::GetHeight()
		- (nServerGBtnHeight * 11 + SSW_GAP_HEIGHT * 2 + nDescGgHeight);
	// ������ ���� �׷� ��ư X ��ġ.
	int nRServerGBtnPosX = nXCoord + nServerGBtnWidth
		+ nServerBtnWidth + (SSW_GAP_WIDTH * 2);
	
	// �׽�Ʈ ���� ��ư.
	int icntServreGroup = 0;
	m_aServerGroupBtn[icntServreGroup++].SetPosition( nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
								nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT - nDescGgHeight);

	// ���� ���� �׷� ��ư.
	for (i=0 ; i<SSW_LEFT_SERVER_G_MAX; i++)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;	
		m_aServerGroupBtn[icntServreGroup++].SetPosition(nXCoord, nBtnPosY);
	}

	// ���� ���� �׷� ��ư.
	for (i=0 ; i<SSW_RIGHT_SERVER_G_MAX; i++)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		m_aServerGroupBtn[icntServreGroup++].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}

	// ���� ���� ���.
	m_winDescription.SetPosition( nXCoord - ((m_winDescription.GetWidth() - CWin::GetWidth()) / 2),
							nYCoord + CWin::GetHeight() - m_winDescription.GetHeight());	

	// ��� ��������Ʈ.
	m_aBtnDeco[0].SetPosition(m_aServerGroupBtn[1].GetXPos(),
								m_aServerGroupBtn[1].GetYPos());
	m_aBtnDeco[1].SetPosition(m_aServerGroupBtn[SSW_LEFT_SERVER_G_MAX+1].GetXPos() + SERVER_GROUP_BTN_WIDTH,
								m_aServerGroupBtn[SSW_LEFT_SERVER_G_MAX+1].GetYPos());

#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
	int a = m_aServerGroupBtn[1].GetXPos();
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING

#else // KJH_ADD_SERVER_LIST_SYSTEM
	int nServerGBtnWidth = m_abtnServerG[0].GetWidth();	// ���� �׷� ��ư �ʺ�.
	int nServerGBtnHeight = m_abtnServerG[0].GetHeight();// ���� �׷� ��ư ����.
	int nServerBtnWidth = m_abtnServer[0].GetWidth();	// ���� ��ư �ʺ�.
	int nServerBtnHeight = m_abtnServer[0].GetHeight();	// ���� ��ư ����.
	int nDescGgHeight = m_winDescBg.GetHeight();
	int i, nBtnPosY;
	
	// ���� �׷� ��ư.
	// ���� �׷� ��ư Y ��ġ ������.
	int nServerGBtnBasePosY = nYCoord + CWin::GetHeight()
		- (nServerGBtnHeight * 11 + SSW_GAP_HEIGHT * 2 + nDescGgHeight);
	// ������ ���� �׷� ��ư X ��ġ.
	int nRServerGBtnPosX = nXCoord + nServerGBtnWidth
		+ nServerBtnWidth + (SSW_GAP_WIDTH * 2);

#if defined PJH_NEW_SERVER_ADD
	for (i = 0; i < 7; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i].SetPosition(nXCoord, nBtnPosY);
	}

	for (i = 0; i < 6; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i + 7].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}
	// �׽�Ʈ ���� ��ư.
	m_abtnServerG[13].SetPosition(
		nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
		nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT
		- nDescGgHeight);
#elif defined PJH_FINAL_VIEW_SERVER_LIST2
	for (i = 0; i < 6; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i].SetPosition(nXCoord, nBtnPosY);
		m_abtnServerG[i + 6].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}

	// �׽�Ʈ ���� ��ư.
	m_abtnServerG[12].SetPosition(
		nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
		nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT
		- nDescGgHeight);
#elif defined PJH_FINAL_VIEW_SERVER_LIST
	for (i = 0; i < 7; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i].SetPosition(nXCoord, nBtnPosY);
	}

	for (i = 0; i < 8; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i + 7].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}
	// �׽�Ʈ ���� ��ư.
	m_abtnServerG[15].SetPosition(
		nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
		nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT
		- nDescGgHeight);
#elif defined PJH_SEMI_FINAL_VIEW_SERVER_LIST
	for (i = 0; i < 4; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i].SetPosition(nXCoord, nBtnPosY);
	}

	for (i = 0; i < 6; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i + 4].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}
	// �׽�Ʈ ���� ��ư.
	m_abtnServerG[10].SetPosition(
		nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
		nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT
		- nDescGgHeight);
#else //PJH_SEMI_FINAL_VIEW_SERVER_LIST
	for (i = 0; i < 10; ++i)
	{
		nBtnPosY = nServerGBtnBasePosY + nServerGBtnHeight * i;
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i].SetPosition(nXCoord, nBtnPosY);
		// ���� ���� �׷� ��ư.
		m_abtnServerG[i + 10].SetPosition(nRServerGBtnPosX, nBtnPosY);
	}
	// �׽�Ʈ ���� ��ư.
	m_abtnServerG[20].SetPosition(
		nXCoord + (CWin::GetWidth() - nServerGBtnWidth) / 2,
		nYCoord + CWin::GetHeight() - nServerGBtnHeight - SSW_GAP_HEIGHT
		- nDescGgHeight);
#endif //PJH_NEW_SERVER_ADD
// ��� ��������Ʈ.
	m_asprDeco[0].SetPosition(m_abtnServerG[0].GetXPos(),
		m_abtnServerG[0].GetYPos());
#if defined PJH_FINAL_VIEW_SERVER_LIST
	m_asprDeco[1].SetPosition(m_abtnServerG[7].GetXPos() + nServerGBtnWidth,
		m_abtnServerG[7].GetYPos());
#elif defined PJH_SEMI_FINAL_VIEW_SERVER_LIST
	m_asprDeco[1].SetPosition(m_abtnServerG[4].GetXPos() + nServerGBtnWidth,
		m_abtnServerG[4].GetYPos());
#elif defined PJH_FINAL_VIEW_SERVER_LIST2
	m_asprDeco[1].SetPosition(m_abtnServerG[6].GetXPos() + nServerGBtnWidth,
		m_abtnServerG[6].GetYPos());
#elif defined PJH_NEW_SERVER_ADD
	m_asprDeco[1].SetPosition(m_abtnServerG[7].GetXPos() + nServerGBtnWidth,
		m_abtnServerG[7].GetYPos());
#endif //#ifdef PJH_VIEW_NEW_SERVER_LIST

	SetServerBtnPosition();		// ���� ��ư.
	SetArrowSpritePosition();	// ȭ��ǥ ��������Ʈ.

	m_winDescBg.SetPosition(
		nXCoord - ((m_winDescBg.GetWidth() - CWin::GetWidth()) / 2),
		nYCoord + CWin::GetHeight() - nDescGgHeight);	// ���� ���� ���.
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : SetServerBtnPosition()
// �Լ� ���� : ���� ��ư�� ��ġ ����.
//*****************************************************************************
void CServerSelWin::SetServerBtnPosition()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	if( m_iSelectServerBtnIndex == -1 )
		return;

	// ���� ��ư X ��ġ.
	int nServerBtnPosX = m_aServerGroupBtn[1].GetXPos() + m_aServerGroupBtn[0].GetWidth() + SSW_GAP_WIDTH;
	
	int nServerBtnHeight = m_aServerBtn[0].GetHeight();
	// ���� ���� �׷� ��ư ���� ��.
	int nLServerGBtnHeightSum = m_aServerGroupBtn[1].GetHeight() * 10;
	// ���õ� �׷��� ���� ��ư ���� ��.
	int nServerBtnHeightSum = nServerBtnHeight * m_icntServer;
	// ���� ���� �׷� ��ư �ֻ��� ��ġ. 
	int nLServerGBtnTop = m_aServerGroupBtn[1].GetYPos();
	
	// ���� ��ư Y ������.
	int nServerBtnBasePosY = nLServerGBtnHeightSum > nServerBtnHeightSum
		? nLServerGBtnTop : nLServerGBtnTop - (nServerBtnHeightSum - nLServerGBtnHeightSum);
	
	// ��� ���� ��ư�� ȥ�⵵ ������ �� ��ġ ����.
	for (int i = 0; i < m_pSelectServerGroup->GetServerSize(); i++)
	{
		m_aServerBtn[i].SetPosition( nServerBtnPosX, nServerBtnBasePosY + nServerBtnHeight * i);
		m_aServerGauge[i].SetPosition(m_aServerBtn[i].GetXPos() + SSW_GB_POS_X, m_aServerBtn[i].GetYPos() + SSW_GB_POS_Y);
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM
	// ���� �׷� ������ ���� ��쿣 ��ġ ���� �ʿ� ����.
	if (m_nSelServerG < 0 || m_nSelServerG >= SSW_SERVER_G_MAX)
		return;

	// ���� ��ư X ��ġ.
	int nServerBtnPosX = m_abtnServerG[0].GetXPos() + m_abtnServerG[0].GetWidth()
		+ SSW_GAP_WIDTH;

	int nServerBtnHeight = m_abtnServer[0].GetHeight();
	// ���� ���� �׷� ��ư ���� ��.
	int nLServerGBtnHeightSum = m_abtnServerG[0].GetHeight() * 10;
	// ���õ� �׷��� ���� ��ư ���� ��.
	int nServerBtnHeightSum
		= nServerBtnHeight * ServerList[m_anServerListIndex[m_nSelServerG]].Number;
	// ���� ���� �׷� ��ư �ֻ��� ��ġ. 
	int nLServerGBtnTop = m_abtnServerG[0].GetYPos();

	// ���� ��ư Y ������.
	int nServerBtnBasePosY = nLServerGBtnHeightSum > nServerBtnHeightSum
		? nLServerGBtnTop
		: nLServerGBtnTop - (nServerBtnHeightSum - nLServerGBtnHeightSum);

	// ��� ���� ��ư�� ȥ�⵵ ������ �� ��ġ ����.
	for (int i = 0; i < SSW_SERVER_MAX; ++i)
	{
		m_abtnServer[i].SetPosition(
			nServerBtnPosX, nServerBtnBasePosY + nServerBtnHeight * i);
		m_agbServer[i].SetPosition(m_abtnServer[i].GetXPos() + SSW_GB_POS_X,
			m_abtnServer[i].GetYPos() + SSW_GB_POS_Y);
	}
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : SetArrowSpritePosition()
// �Լ� ���� : ȭ��ǥ ��������Ʈ ��ġ ����.
//*****************************************************************************
void CServerSelWin::SetArrowSpritePosition()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	if( m_iSelectServerBtnIndex == -1 )
		return;
	
	if((m_iSelectServerBtnIndex >= 0 ) && (m_iSelectServerBtnIndex <= SSW_LEFT_SERVER_G_MAX))
	{
		m_aArrowDeco[0].SetPosition(m_aServerGroupBtn[m_iSelectServerBtnIndex].GetXPos() + SERVER_GROUP_BTN_WIDTH,
									m_aServerGroupBtn[m_iSelectServerBtnIndex].GetYPos());
	}
	else if((m_iSelectServerBtnIndex > SSW_LEFT_SERVER_G_MAX ) && (m_iSelectServerBtnIndex < SSW_SERVER_G_MAX))
	{
		m_aArrowDeco[1].SetPosition(m_aServerGroupBtn[m_iSelectServerBtnIndex].GetXPos(),
									m_aServerGroupBtn[m_iSelectServerBtnIndex].GetYPos());
	}

#else // KJH_ADD_SERVER_LIST_SYSTEM
	// ���� �׷� ������ ���� ��쳪 �׽�Ʈ ������ ���� �Ǿ��� ��� ��ġ ���� ��
	//�� ����.
	if (m_nSelServerG < 0 || m_nSelServerG >= SSW_SERVER_G_MAX - 1)
		return;
#if defined PJH_SEMI_FINAL_VIEW_SERVER_LIST
	if (m_nSelServerG < 4)	// ���� ���� �׷� ��ư ������ ���.
		m_asprArrow[0].SetPosition(m_abtnServerG[m_nSelServerG].GetXPos()
			+ m_abtnServerG[m_nSelServerG].GetWidth(),
			m_abtnServerG[m_nSelServerG].GetYPos());
#elif defined PJH_FINAL_VIEW_SERVER_LIST2
	if (m_nSelServerG < 6)	// ���� ���� �׷� ��ư ������ ���.
		m_asprArrow[0].SetPosition(m_abtnServerG[m_nSelServerG].GetXPos()
			+ m_abtnServerG[m_nSelServerG].GetWidth(),
			m_abtnServerG[m_nSelServerG].GetYPos());
#elif defined PJH_NEW_SERVER_ADD
	if (m_nSelServerG < 7)	// ���� ���� �׷� ��ư ������ ���.
		m_asprArrow[0].SetPosition(m_abtnServerG[m_nSelServerG].GetXPos()
			+ m_abtnServerG[m_nSelServerG].GetWidth(),
			m_abtnServerG[m_nSelServerG].GetYPos());
#else
	if (m_nSelServerG < 10)	// ���� ���� �׷� ��ư ������ ���.
		m_asprArrow[0].SetPosition(m_abtnServerG[m_nSelServerG].GetXPos()
			+ m_abtnServerG[m_nSelServerG].GetWidth(),
			m_abtnServerG[m_nSelServerG].GetYPos());
#endif //#ifdef PJH_SEMI_FINAL_VIEW_SERVER_LIST
	else					// ���� ���� �׷� ��ư ������ ���.
		m_asprArrow[1].SetPosition(m_abtnServerG[m_nSelServerG].GetXPos(),
			m_abtnServerG[m_nSelServerG].GetYPos());
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : UpdateDisplay()
// �Լ� ���� : ������ ������ â�� �ݿ���.
//*****************************************************************************
void CServerSelWin::UpdateDisplay()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	// Release
	m_pSelectServerGroup = NULL;
	m_icntServerGroup = 0;
	m_icntServer = 0;
	m_icntLeftServerGroup = 0;
	m_icntRightServerGroup = 0;
	m_bTestServerBtn = false;

	DWORD adwServerGBtnClr[BTN_IMG_MAX] =
	{
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0,
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0
	};

#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	DWORD adwServerBtnClr[4][4] =
	{
		{ CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0 },	// PVP ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_YELLOW, CLRDW_YELLOW, CLRDW_BR_YELLOW, 0 },	// Non-PVP ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_ORANGE, CLRDW_ORANGE, CLRDW_BR_ORANGE, 0 },	// ���� PVP ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_ORANGE, CLRDW_ORANGE, CLRDW_BR_ORANGE, 0 },	// ���� Non-PVP ���� ��ư �ؽ�Ʈ ��.
	};
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
	DWORD adwServerBtnClr[2][4] =
	{
		// �Ϲ� ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0 },
		// Non-PVP ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_YELLOW, CLRDW_YELLOW, CLRDW_YELLOW, 0 }
	};
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL

	m_icntServerGroup = g_ServerListManager->GetServerGroupSize();		// ���� �׷� ����

	if( m_icntServerGroup < 1 )
		return;

	CServerGroup* pServerGroup = NULL;

	g_ServerListManager->SetFirst();

	// ������ ����
	while( g_ServerListManager->GetNext(pServerGroup) )
	{
		if( pServerGroup->m_iWidthPos == CServerGroup::SBP_CENTER )	// �׽�Ʈ ����
		{
			if( m_bTestServerBtn == true )
				continue;

			// �׽�Ʈ ���� ��ư. (�߾� �Ʒ�)
			m_aServerGroupBtn[0].SetText(pServerGroup->m_szName, adwServerGBtnClr);
			pServerGroup->m_iBtnPos = 0;
			m_bTestServerBtn = true;
		}
		else if( pServerGroup->m_iWidthPos == CServerGroup::SBP_LEFT )
		{
			if( m_icntLeftServerGroup >= SSW_LEFT_SERVER_G_MAX )
				continue;

			// ���� ���� �׷� ��ư.
			m_aServerGroupBtn[m_icntLeftServerGroup+1].SetText(pServerGroup->m_szName, adwServerGBtnClr);
			pServerGroup->m_iBtnPos = m_icntLeftServerGroup+1;

			m_icntLeftServerGroup++;
		}
		else if( pServerGroup->m_iWidthPos == CServerGroup::SBP_RIGHT )
		{
			if( m_icntRightServerGroup >= SSW_RIGHT_SERVER_G_MAX )
				continue;

			// ���� ���� �׷� ��ư.
			m_aServerGroupBtn[SSW_LEFT_SERVER_G_MAX+m_icntRightServerGroup+1].SetText(pServerGroup->m_szName, adwServerGBtnClr);
			pServerGroup->m_iBtnPos = SSW_LEFT_SERVER_G_MAX+m_icntRightServerGroup+1;

			m_icntRightServerGroup++;
		}	
	}

	ShowServerGBtns();
	ShowDecoSprite();

	memset(m_szDescription, 0, sizeof(char) * SSW_DESC_LINE_MAX * SSW_DESC_ROW_MAX);
	
	// ���� ���� �׷��� ���õǾ��°�
	if( m_iSelectServerBtnIndex != -1)
	{
		m_pSelectServerGroup = g_ServerListManager->GetServerGroupByBtnPos(m_iSelectServerBtnIndex);
	}

	// ���� ������ ������ return
	if( m_pSelectServerGroup == NULL )
#ifdef ASG_MOD_SERVER_LIST_CHANGE_MSG
	{
		// ���������� �ִٸ� ���� ����â�� ������.
		if (0 != ::strlen(g_ServerListManager->GetNotice()))
		{
			::SeparateTextIntoLines(g_ServerListManager->GetNotice(), m_szDescription[0],
				SSW_DESC_LINE_MAX, SSW_DESC_ROW_MAX);
			m_winDescription.Show(CWin::m_bShow);
		}
		return;
	}
#else	// ASG_MOD_SERVER_LIST_CHANGE_MSG
		return;
#endif	// ASG_MOD_SERVER_LIST_CHANGE_MSG

	// ���� ���ý� ���� ����Ʈ ����
	m_icntServer = m_pSelectServerGroup->GetServerSize();

	if( m_icntServer < 1)
		return;

	CServerInfo* pServerInfo = NULL;

	m_pSelectServerGroup->SetFirst();

	int icntServer = 0;
	while(m_pSelectServerGroup->GetNext(pServerInfo))
	{
		// ���� ��ư �ؽ�Ʈ ����.
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		m_aServerBtn[icntServer].SetText(
			pServerInfo->m_bName, adwServerBtnClr[pServerInfo->m_byNonPvP]);
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		if( pServerInfo->m_bNonPvP == true )		// NonPvP
		{
			m_aServerBtn[icntServer].SetText(pServerInfo->m_bName, adwServerBtnClr[1]);
		}
		else
		{
			m_aServerBtn[icntServer].SetText(pServerInfo->m_bName, adwServerBtnClr[0]);
		}
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
		
		// ���� ȥ�⵵ ������ ����.
		m_aServerGauge[icntServer].SetValue(pServerInfo->m_iPercent, 100);

		icntServer++;
	}

	// ���� ���� ����.
	::SeparateTextIntoLines(m_pSelectServerGroup->m_szDescription, m_szDescription[0], SSW_DESC_LINE_MAX, SSW_DESC_ROW_MAX);

	// ȭ��ǥ ��������Ʈ �� ���� ��ư�� ��ġ ������ �����ֱ� ����.
	SetArrowSpritePosition();
	SetServerBtnPosition();
	
	ShowArrowSprite();
	ShowServerBtns();

	
#else // KJH_ADD_SERVER_LIST_SYSTEM

	int i, j;
// ���� �׷� ��ư.
	// �ؽ�Ʈ ����.
	DWORD adwServerGBtnClr[BTN_IMG_MAX] =
	{
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0,
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0
	};
	// ���� �׷� ��ư �ؽ�Ʈ ����.

	::memset(m_anServerListIndex, 0, sizeof(int) * SSW_SERVER_G_MAX);

	for (i = 0, j = 0; i < MAX_SERVER_HI && j < SSW_SERVER_G_MAX; ++i)
	{
		if (ServerList[i].Number > 0)
		{
			m_abtnServerG[j].SetText(ServerList[i].Name, adwServerGBtnClr);
			m_anServerListIndex[j] = i;
			++j;
		}
		else
			continue;
	}
	m_nServerGCount = j;

	ShowServerGBtns();
	ShowDecoSprite();

	::memset(m_aszDesc, 0, sizeof(char) * SSW_DESC_LINE_MAX * SSW_DESC_ROW_MAX);
// ���� ��ư�� ȥ�⵵ ������ ��.
	// ���õ� �׷��� ���� ��ư.
	if (m_nSelServerG < 0 || m_nSelServerG >= SSW_SERVER_G_MAX)
		return;

#if defined PJH_FINAL_VIEW_SERVER_LIST || defined PJH_SEMI_FINAL_VIEW_SERVER_LIST || defined PJH_FINAL_VIEW_SERVER_LIST2 || defined PJH_NEW_SERVER_ADD
#else
	// ���� ���� ����.
	::SeparateTextIntoLines(GlobalText[1717 + m_nSelServerG], m_aszDesc[0],
		SSW_DESC_LINE_MAX, SSW_DESC_ROW_MAX);
#endif //defined PJH_FINAL_VIEW_SERVER_LIST || defined PJH_SEMI_FINAL_VIEW_SERVER_LIST
	// ���õ� ���� �׷� ����.
	SERVER_LIST_t* pSelServerGInfo
		= &ServerList[m_anServerListIndex[m_nSelServerG]];

#if defined PJH_FINAL_VIEW_SERVER_LIST || defined PJH_SEMI_FINAL_VIEW_SERVER_LIST || defined PJH_FINAL_VIEW_SERVER_LIST2 || defined PJH_NEW_SERVER_ADD
	int Set_Server = 1717;

	for(int Server_Num = 0; Server_Num < 11; Server_Num++)
	{
		if(strcmp(pSelServerGInfo->Name,GlobalText[540 + Server_Num]) == 0)
		{
			Set_Server += 19 - Server_Num;
			break;
		}
	}

	if(strcmp(pSelServerGInfo->Name,GlobalText[557]) == 0)
	{
		Set_Server += 8;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[558]) == 0)
	{
		Set_Server += 7;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[552]) == 0)
	{
		Set_Server += 6;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[551]) == 0)
	{
		Set_Server += 5;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[553]) == 0)
	{
		Set_Server += 4;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[554]) == 0)
	{
		Set_Server += 3;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[555]) == 0)
	{
		Set_Server += 2;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[556]) == 0)
	{
		Set_Server += 1;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[559]) == 0)
	{
		Set_Server += 20;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1875]) == 0)
	{
		Set_Server += 161;	// 1717+161=1878
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1874]) == 0)
	{
		Set_Server += 160;	// 1717+160=1877
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1829]) == 0)
	{
		Set_Server += 0;
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1875]) == 0)
	{
		Set_Server += 161;	// 1717+161=1878
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1874]) == 0)
	{
		Set_Server += 160;	// 1717+160=1877
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1873]) == 0)
	{
		Set_Server += 159;	// 1717+159=1876
	}
#if defined PJH_FINAL_VIEW_SERVER_LIST2 || defined PJH_NEW_SERVER_ADD
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1272]) == 0)	//�ǹ�
	{
		Set_Server -= 443;	// 1717-443=1274
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1273]) == 0)	//����
	{
		Set_Server -= 442;	// 1717-442=1275
	}
#endif //PJH_FINAL_VIEW_SERVER_LIST2
#ifdef PJH_NEW_SERVER_ADD
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[728]) == 0)	//�η�
	{
		Set_Server -= 988;	// 1717-988=729
	}
#endif //PJH_NEW_SERVER_ADD
#ifdef PJH_USER_VERSION_SERVER_LIST
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1879]) == 0)	//����4ü�輭��
	{
		Set_Server += 163;	// 1717+163=1880
	}
	else
	if(strcmp(pSelServerGInfo->Name,GlobalText[1881]) == 0)	//����4ü�輭��
	{
		Set_Server += 165;	// 1717+165=1882
	}
#endif //PJH_USER_VERSION_SERVER_LIST
	::SeparateTextIntoLines(GlobalText[Set_Server], m_aszDesc[0],
		SSW_DESC_LINE_MAX, SSW_DESC_ROW_MAX);
#endif //defined PJH_FINAL_VIEW_SERVER_LIST || defined PJH_SEMI_FINAL_VIEW_SERVER_LIST





	int nServer;			// ��ư�� ǥ�õ� ���� ��ȣ.
	char szNonPVP[16];		// "(Non-PVP)" �Ǵ� NULL.
	int nGlobalText;		// "����", "(Full)", "�غ���" �� �ϳ�.
	char szServerName[128];	// ���� ��ư �ؽ�Ʈ.
	DWORD adwServerBtnClr[2][4] =
	{
		// �Ϲ� ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, 0 },
		// Non-PVP ���� ��ư �ؽ�Ʈ ��.
		{ CLRDW_YELLOW, CLRDW_YELLOW, CLRDW_YELLOW, 0 }
	};
	// adwServerBtnClr[0] �Ǵ� adwServerBtnClr[1]�� �ּ�.
	DWORD* pdwServerBtnClr;

	// ���� �׷� ���� ���� ������ 1���̸� ���� ��ư �ؽ�Ʈ�� 1�̶� ���ڰ� ���
	//���� �ȵǹǷ� if������ ����.
	if (pSelServerGInfo->Number > 1)// ���� �׷� ���� ���� ������ 1������ ū��?
	{
		// ���õ� ���� �׷��� ���� ���� ��ŭ �ݺ�.
		for (i = 0; i < pSelServerGInfo->Number; ++i)
		{
			nServer = pSelServerGInfo->Server[i].Index % 20 + 1;

			if (::IsNonPvpServer(m_anServerListIndex[m_nSelServerG], nServer))
			{
				::strcpy(szNonPVP, "(Non-PVP)");
				pdwServerBtnClr = adwServerBtnClr[1];
			}
			else
			{
				::memset(szNonPVP, 0, sizeof(char) * 16);
				pdwServerBtnClr = adwServerBtnClr[0];
			}

			if (pSelServerGInfo->Server[i].Percent >= 128)
				nGlobalText = 560;	// "�غ���"
			else if(pSelServerGInfo->Server[i].Percent >= 100)
				nGlobalText = 561;	// "(Full)"
			else
				nGlobalText = 562;	// "����"

#if defined	ADD_EXPERIENCE_SERVER
			// �׽�Ʈ �����̰�, ���� ��ȣ�� 10 �̻� �̸�.
			if (0 == ::strcmp(pSelServerGInfo->Name, GlobalText[559])
				&& nServer >= 10)
				::sprintf(szServerName, "%s-%d %s", GlobalText[1699],
					nServer - 9, GlobalText[nGlobalText]);	// ����2ü��(PC��)
			else
#elif defined ADD_EVENT_SERVER_NAME
			// �׽�Ʈ �����̰�, ���� ��ȣ�� 6 �̻� �̸�.
			if (0 == ::strcmp(pSelServerGInfo->Name, GlobalText[559])
				&& nServer >= 6)
				::sprintf(szServerName, "%s-%d %s", GlobalText[19],
					nServer - 5, GlobalText[nGlobalText]);	// �̺�Ʈ
			else
#endif	// ADD_EXPERIENCE_SERVER	ADD_EVENT_SERVER_NAME
				::sprintf(szServerName, "%s-%d%s %s", pSelServerGInfo->Name,
					nServer, szNonPVP, GlobalText[nGlobalText]);

			// ���� ��ư �ؽ�Ʈ ����.
			m_abtnServer[i].SetText(szServerName, pdwServerBtnClr);
			// ���� ȥ�⵵ ������ ����.
			m_agbServer[i].SetValue(pSelServerGInfo->Server[i].Percent, 100);
		}
	}
	else	// ���� �׷� ���� ���� ������ 1���ΰ�?
	{
		nServer = pSelServerGInfo->Server[0].Index % 20 + 1;
			
		if (::IsNonPvpServer(m_anServerListIndex[m_nSelServerG], nServer))
		{
			::strcpy(szNonPVP, "(Non-PVP)");
			pdwServerBtnClr = adwServerBtnClr[1];
		}
		else
		{
			::memset(szNonPVP, 0, sizeof(char) * 16);
			pdwServerBtnClr = adwServerBtnClr[0];
		}

		if (pSelServerGInfo->Server[0].Percent >= 128)
			nGlobalText = 560;	// "�غ���"
		else if(pSelServerGInfo->Server[0].Percent >= 100)
			nGlobalText = 561;	// "(Full)"
		else
			nGlobalText = 562;	// "����"

#if defined	ADD_EXPERIENCE_SERVER
		// �׽�Ʈ �����̰�, ���� ��ȣ�� 10 �̻� �̸�.
		if (0 == ::strcmp(pSelServerGInfo->Name, GlobalText[559])
			&& nServer >= 10)
			::sprintf(szServerName, "%s %s",
				GlobalText[1699], GlobalText[nGlobalText]);	// ����2ü��(PC��)
		else
#elif defined ADD_EVENT_SERVER_NAME
		// �׽�Ʈ �����̰�, ���� ��ȣ�� 6 �̻� �̸�.
		if (0 == ::strcmp(pSelServerGInfo->Name, GlobalText[559])
			&& nServer >= 6)
			::sprintf(szServerName, "%s %s",
				GlobalText[19], GlobalText[nGlobalText]);	// �̺�Ʈ
		else
#endif	// ADD_EXPERIENCE_SERVER	ADD_EVENT_SERVER_NAME
			::sprintf(szServerName, "%s%s %s",
				pSelServerGInfo->Name, szNonPVP, GlobalText[nGlobalText]);

		// ���� ��ư �ؽ�Ʈ ����.
		m_abtnServer[0].SetText(szServerName, pdwServerBtnClr);
		// ���� ȥ�⵵ ������ ����.
		m_agbServer[0].SetValue(pSelServerGInfo->Server[0].Percent, 100);
	}

	// ȭ��ǥ ��������Ʈ �� ���� ��ư�� ��ġ ������ �����ֱ� ����.
	SetArrowSpritePosition();
	SetServerBtnPosition();

	ShowArrowSprite();
	ShowServerBtns();

#endif KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� �����ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CServerSelWin::Show(bool bShow)
{
	CWin::Show(bShow);

#ifndef KJH_ADD_SERVER_LIST_SYSTEM			// #ifndef
	ShowServerGBtns();
	ShowDecoSprite();
	ShowArrowSprite();
	ShowServerBtns();

	if (m_nSelServerG > -1)
		m_winDescBg.Show(bShow);
	else
		m_winDescBg.Show(false);
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : ShowServerGBtns()
// �Լ� ���� : �����׷� ��ư���� �����ְų� �Ⱥ��̰���.
//*****************************************************************************
void CServerSelWin::ShowServerGBtns()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	int i;

	// �߾�
	if( m_bTestServerBtn == true )
	{
		m_aServerGroupBtn[0].Show(CWin::m_bShow);
	}
	else
	{
		m_aServerGroupBtn[0].Show(false);
	}

	// ����
	for (i = 1 ; i < m_icntLeftServerGroup+1 ; i++)
	{
		m_aServerGroupBtn[i].Show(CWin::m_bShow);
	}
	for (; i < SSW_LEFT_SERVER_G_MAX; ++i)
	{
		m_aServerGroupBtn[i].Show(false);
	}

	// ����
	for (i = SSW_LEFT_SERVER_G_MAX+1 ; i < SSW_RIGHT_SERVER_G_MAX+1+m_icntRightServerGroup ; i++)
	{
		m_aServerGroupBtn[i].Show(CWin::m_bShow);
	}
	for (; i < SSW_SERVER_G_MAX; i++)
	{
		m_aServerGroupBtn[i].Show(false);
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM
	int i;
	for (i = 0; i < m_nServerGCount; ++i)
		m_abtnServerG[i].Show(CWin::m_bShow);
	for (; i < SSW_SERVER_G_MAX; ++i)
		m_abtnServerG[i].Show(false);
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : ShowDecoSprite()
// �Լ� ���� : ��� ��������Ʈ���� �����ְų� �Ⱥ��̰���.
//*****************************************************************************
void CServerSelWin::ShowDecoSprite()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	// ������ư ����
	if( m_icntLeftServerGroup > 0 )
	{
		m_aBtnDeco[0].Show(CWin::m_bShow);
	}
	else
	{
		m_aBtnDeco[0].Show(false);
	}

	// ���� ��ư ����
	if( m_icntRightServerGroup > 0 )
	{
		m_aBtnDeco[1].Show(CWin::m_bShow);
	}
	else
	{
		m_aBtnDeco[1].Show(false);
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM
	// ���� ���ڷ��̼� ��������Ʈ.
	m_asprDeco[0].Show(CWin::m_bShow);

	// ������ ���ڷ��̼� ��������Ʈ.
	if (m_nServerGCount > 10)	// ���� �׷� ������ 10�� �̻��̸�.
		m_asprDeco[1].Show(CWin::m_bShow);
	else
		m_asprDeco[1].Show(false);
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : ShowArrowSprite()
// �Լ� ���� : ȭ��ǥ ��������Ʈ�� �����ְų� �Ⱥ��̰���.
//*****************************************************************************
void CServerSelWin::ShowArrowSprite()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	if((m_iSelectServerBtnIndex >= 0 ) && (m_iSelectServerBtnIndex <= SSW_LEFT_SERVER_G_MAX))
	{
		m_aArrowDeco[0].Show(CWin::m_bShow);
		m_aArrowDeco[1].Show(false);
	}
	else if((m_iSelectServerBtnIndex > SSW_LEFT_SERVER_G_MAX ) && (m_iSelectServerBtnIndex < SSW_SERVER_G_MAX))
	{
		m_aArrowDeco[0].Show(false);
		m_aArrowDeco[1].Show(CWin::m_bShow);
	}
	else
	{
		m_aArrowDeco[0].Show(false);
		m_aArrowDeco[1].Show(false);
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM
	bool bLeftShow = false, bRightShow = false;
	if (m_nSelServerG > -1 && m_nSelServerG < SSW_SERVER_G_MAX - 1)
	{
#if defined PJH_SEMI_FINAL_VIEW_SERVER_LIST
		if (m_nSelServerG < 4)
			bLeftShow = CWin::m_bShow;
#elif defined PJH_FINAL_VIEW_SERVER_LIST2
		if (m_nSelServerG < 6)
			bLeftShow = CWin::m_bShow;
#elif defined PJH_NEW_SERVER_ADD
		if (m_nSelServerG < 7)
			bLeftShow = CWin::m_bShow;
#else
		if (m_nSelServerG < 10)
			bLeftShow = CWin::m_bShow;
#endif //#ifdef PJH_SEMI_FINAL_VIEW_SERVER_LIST
		else
			bRightShow = CWin::m_bShow;
	}
	m_asprArrow[0].Show(bLeftShow);
	m_asprArrow[1].Show(bRightShow);
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : ShowServerBtns()
// �Լ� ���� : �����׷� ���� ���� ��ư���� �����ְų� �Ⱥ��̰���.
//*****************************************************************************
void CServerSelWin::ShowServerBtns()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	// ���õ� ���� �׷��� ������ �׸��� ����.
	if (m_iSelectServerBtnIndex == -1)
	{
		m_winDescription.Show(false);
		return;
	}
	
	int i;
	for (i = 0 ; i < m_icntServer ; i++)
	{
		m_aServerBtn[i].Show(CWin::m_bShow);
		m_aServerGauge[i].Show(CWin::m_bShow);
	}
	for ( ; i < SSW_SERVER_MAX; i++)
	{
		m_aServerBtn[i].Show(false);
		m_aServerGauge[i].Show(false);
	}

	m_winDescription.Show(CWin::m_bShow);	
#else // KJH_ADD_SERVER_LIST_SYSTEM
	// ���õ� ���� �׷��� ������ �׸��� ����.
	if (m_nSelServerG < 0 || m_nSelServerG >= SSW_SERVER_G_MAX)
		return;

	int i;
	for (i = 0; i < ServerList[m_anServerListIndex[m_nSelServerG]].Number; ++i)
	{
		m_abtnServer[i].Show(CWin::m_bShow);
		m_agbServer[i].Show(CWin::m_bShow);
	}
	for (; i < SSW_SERVER_MAX; ++i)
	{
		m_abtnServer[i].Show(false);
		m_agbServer[i].Show(false);
	}
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool CServerSelWin::CursorInWin(int nArea)
{
	if (!CWin::m_bShow)		// ������ �ʴ´ٸ� ó������ ����.
		return false;

	switch (nArea)
	{
	case WA_MOVE:
		return false;	// �̵� ������ ����.(�̵��� ����)
	}

	return CWin::CursorInWin(nArea);
}

//*****************************************************************************
// �Լ� �̸� : UpdateWhileActive()
// �Լ� ���� : ��Ƽ���� ���� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CServerSelWin::UpdateWhileActive()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CServerSelWin::UpdateWhileActive(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	int i;

	// ���� �׷� ��ư ó��.
	for( i=0 ; i<SSW_SERVER_G_MAX ; i++ )
	{
		if (m_aServerGroupBtn[i].IsClick())
		{
			if(m_iSelectServerBtnIndex != -1 )
			{
				m_aServerGroupBtn[m_iSelectServerBtnIndex].SetCheck(false);
			}

			m_aServerGroupBtn[i].SetCheck(true);
			m_iSelectServerBtnIndex = i;
			
			// ���� ������ ���� ����Ʈ ��û.
			// �������� ������ ���� ::ReceiveServerList()��.
		#ifdef PKD_ADD_ENHANCED_ENCRYPTION
			SendRequestServerList2();
		#else
			SendRequestServerList();
		#endif // PKD_ADD_ENHANCED_ENCRYPTION
		}
	}

	if( m_pSelectServerGroup == NULL )
		return ;

	// ���� ��ư ó��.
	CServerInfo* pServerInfo = NULL;
	for( i=0 ; i<m_icntServer ; i++ )
	{
		if (m_aServerBtn[i].IsClick())	// ���� ��ư�� Ŭ���ߴ°�?
		{
			pServerInfo = m_pSelectServerGroup->GetServerInfo(i);

			if( pServerInfo == NULL )
				return;

			if (pServerInfo->m_iPercent < 100)		// ���� �����ΰ�?
			{
				// ���� Ŭ�� ����. ������ ���� �ּҸ� �䱸�� �� �����Ƿ�.
				CUIMng::Instance().HideWin(this);
				
				// ���� ������ ������ ���� ���� �ּ� ��û.
				// �������� ������ ���� ::ReceiveServerConnect() �Ǵ�
				//::ReceiveServerConnectBusy()��.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
				SendRequestServerAddress2(pServerInfo->m_iConnectIndex);
#else
				SendRequestServerAddress(pServerInfo->m_iConnectIndex);
#endif
				
				// ���� ���ÿ� ���� ���� ����
				int iCensorshipIndex = CGameCensorship::STATE_12;

				if( m_pSelectServerGroup->m_bPvPServer == true )
				{
					iCensorshipIndex = CGameCensorship::STATE_18;
				}
				else
				{
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
					if (0x01 & pServerInfo->m_byNonPvP)
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
					if(pServerInfo->m_bNonPvP == false)
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
					{
						iCensorshipIndex = CGameCensorship::STATE_15;
					}
				}

				bool bTestServer = false;
				if( m_pSelectServerGroup->m_iSequence == 0 )
				{
					bTestServer = true;
				}

				// ���õ� ������ ������ ����
#ifdef ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
				g_ServerListManager->SetSelectServerInfo(m_pSelectServerGroup->m_szName,
					pServerInfo->m_iIndex, iCensorshipIndex, pServerInfo->m_byNonPvP, bTestServer);
#else	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
				g_ServerListManager->SetSelectServerInfo(m_pSelectServerGroup->m_szName, pServerInfo->m_iIndex, 
															iCensorshipIndex, pServerInfo->m_bNonPvP, bTestServer);
#endif	// ASG_MOD_SERVER_LIST_ADD_CHARGED_CHANNEL
				
				break;
			}
			else if (pServerInfo->m_iPercent < 128)	// ������ ��ȭ �����ΰ�?
			{
				// �޽��� �����츦 ������.
				CUIMng::Instance().PopUpMsgWin(MESSAGE_SERVER_BUSY);
			}
		}
	}
#else KJH_ADD_SERVER_LIST_SYSTEM
	// ���� �׷� ��ư ó��.
	int i, j;
	for (i = 0; i < SSW_SERVER_G_MAX; ++i)
	{
		if (m_abtnServerG[i].IsClick())
		{
			// ���� ��ư ���� ����.
			for (j = 0; j < SSW_SERVER_G_MAX; ++j)
				m_abtnServerG[j].SetCheck(false);
			m_abtnServerG[i].SetCheck(true);

			m_nSelServerG = i;
			// ���� ������ ���� ����Ʈ ��û.
			// �������� ������ ���� ::ReceiveServerList()��.
#ifdef PKD_ADD_ENHANCED_ENCRYPTION
			SendRequestServerList2();
#else
			SendRequestServerList();
#endif // PKD_ADD_ENHANCED_ENCRYPTION
			g_ErrorReport.Write( "> Server group selected - %d\r\n",
				m_anServerListIndex[m_nSelServerG]);

			break;
		}
	}

	// ���� ��ư ó��.
	SERVER_t* pSelServerInfo;	// ���õ� ���� ����.
	for (i = 0; i < SSW_SERVER_MAX; ++i)
	{
		if (m_abtnServer[i].IsClick())	// ���� ��ư�� Ŭ���ߴ°�?
		{
			pSelServerInfo
				= &ServerList[m_anServerListIndex[m_nSelServerG]].Server[i];

			if (pSelServerInfo->Percent < 100)		// ���� �����ΰ�?
			{
				// ���� Ŭ�� ����. ������ ���� �ּҸ� �䱸�� �� �����Ƿ�.
				CUIMng::Instance().HideWin(this);

				// ���� ������ ������ ���� ���� �ּ� ��û.
				// �������� ������ ���� ::ReceiveServerConnect() �Ǵ�
				//::ReceiveServerConnectBusy()��.

#ifdef PKD_ADD_ENHANCED_ENCRYPTION
				SendRequestServerAddress2(pSelServerInfo->Index);
#else
				SendRequestServerAddress(pSelServerInfo->Index);
#endif // PKD_ADD_ENHANCED_ENCRYPTION

				int nServer = pSelServerInfo->Index % 20 + 1;
				g_ErrorReport.Write( "> Server selected - %s-%d : %d-%d\r\n",
					ServerList[m_anServerListIndex[m_nSelServerG]].Name,
					nServer, m_anServerListIndex[m_nSelServerG], i);

				// �÷��̾� ĳ���� ����â�� ���� ������ ����ϹǷ�.
				ServerSelectHi = m_anServerListIndex[m_nSelServerG];
				ServerLocalSelect = nServer;

				break;
			}
			else if (pSelServerInfo->Percent < 128)	// ������ ��ȭ �����ΰ�?
				// �޽��� �����츦 ������.
				CUIMng::Instance().PopUpMsgWin(MESSAGE_SERVER_BUSY);
		}
	}
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void CServerSelWin::RenderControls()
{
#ifdef KJH_ADD_SERVER_LIST_SYSTEM
	int i = 0;
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	m_winDescription.Render();
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
	
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->SetBgColor(0);
	
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	for (i = 0; i < 2; ++i)
	{
 		m_aBtnDeco[i].Render();
 		m_aArrowDeco[i].Render();
		g_pRenderText->RenderText(int((m_winDescription.GetXPos() + 11) / g_fScreenRate_x),
			int((m_winDescription.GetYPos() + 12 + i * 20) / g_fScreenRate_y),
			m_szDescription[i]);
	}
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN
	
	CWin::RenderButtons();
	
	if( m_pSelectServerGroup != NULL )
	{
		for (i=0 ; i<m_icntServer; i++)
		{
			m_aServerGauge[i].Render();
		}

		// PvP �����̸� 18�� �̿밡 ǥ��
		if( m_pSelectServerGroup->m_bPvPServer == true )
		{
#if SELECTED_LANGUAGE != LANGUAGE_CHINESE		
#ifdef PBG_ADD_MU_LOGO
			// ���ο� ��濡 ���� ������ ��� �Ǳ� ���� ������κ���
			g_pRenderText->SetTextColor(ARGB(255, 255, 255, 255));
#else //PBG_ADD_MU_LOGO
			g_pRenderText->SetTextColor(ARGB(255, 0, 0, 0));
#endif //PBG_ADD_MU_LOGO
			g_pRenderText->RenderText(90, 164 - 60, GlobalText[565]);
			g_pRenderText->RenderText(90, 164 - 45, GlobalText[566]);
			g_pRenderText->RenderText(90, 164 - 30, GlobalText[567]);
#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
		}
	}
#else // KJH_ADD_SERVER_LIST_SYSTEM

	int i = 0;
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	m_winDescBg.Render();
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN

	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->SetBgColor(0);
	
#if SELECTED_LANGUAGE == LANGUAGE_KOREAN
	for (i = 0; i < 2; ++i)
	{
		m_asprDeco[i].Render();
		m_asprArrow[i].Render();
		g_pRenderText->RenderText(int((m_winDescBg.GetXPos() + 11) / g_fScreenRate_x),
			int((m_winDescBg.GetYPos() + 12 + i * 20) / g_fScreenRate_y),
			m_aszDesc[i]);
	}
#endif //SELECTED_LANGUAGE == LANGUAGE_KOREAN

	CWin::RenderButtons();

	for (i = 0; i < SSW_SERVER_MAX; ++i)
		m_agbServer[i].Render();

	// ���õ� ���� �׷� �̸��� "����(New)"�̸� 18�� �̿밡 �޽��� ǥ��.
	if (::strcmp(ServerList[m_anServerListIndex[m_nSelServerG]].Name,
		GlobalText[1829]) == NULL
#ifdef PJH_NEW_SERVER_ADD
		||
		::strcmp(ServerList[m_anServerListIndex[m_nSelServerG]].Name,
		GlobalText[728]) == NULL		// �η�
#endif //PJH_NEW_SERVER_ADD
		)
	{
#if SELECTED_LANGUAGE != LANGUAGE_CHINESE		
#ifdef PBG_ADD_MU_LOGO
		// ���ο� ��濡 ���� ������ ��� �Ǳ� ���� ������κ���
		g_pRenderText->SetTextColor(ARGB(255, 255, 255, 255));
#else //PBG_ADD_MU_LOGO
		g_pRenderText->SetTextColor(ARGB(255, 0, 0, 0));
#endif //PBG_ADD_MU_LOGO
		g_pRenderText->RenderText(90, 164 - 60, GlobalText[565]);
		g_pRenderText->RenderText(90, 164 - 45, GlobalText[566]);
		g_pRenderText->RenderText(90, 164 - 30, GlobalText[567]);
#endif //SELECTED_LANGUAGE != LANGUAGE_CHINESE
	}
#endif // KJH_ADD_SERVER_LIST_SYSTEM
}