//*****************************************************************************
// File: CharMakeWin.cpp
//
// Desc: implementation of the CCharMakeWin class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "CharMakeWin.h"
#include "Input.h"
#include "UIMng.h"

// �ؽ�Ʈ ������ ���� #include. �̤�
#include "ZzzBMD.h"
#include "ZzzInfomation.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzOpenglUtil.h"
#include "DSPlaySound.h"
#include "ZzzAI.h"
#include "ZzzScene.h"
#include "UIControls.h"
#include "wsclientinline.h"

#define	CMW_OK		0
#define	CMW_CANCEL	1

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;
extern int g_iChatInputType;
extern CUITextInputBox* g_pSingleTextInputBox;

void MoveCharacterCamera(vec3_t Origin,vec3_t Position,vec3_t Angle);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharMakeWin::CCharMakeWin()
{

}

CCharMakeWin::~CCharMakeWin()
{

}
#ifdef PJH_CHARACTER_RENAME
void CCharMakeWin::Set_State(bool Set)
{
	ReName_Inter = Set;

	if(ReName_Inter == true)
	{
		if(SelectedHero >= 0)
		{
			m_nSelJob = GetBaseClass(CharactersClient[SelectedHero].Class);
			switch(GetBaseClass(m_nSelJob))
			{
			case CLASS_SOULMASTER:
				m_nSelJob = CLASS_WIZARD;
				break;
			case CLASS_BLADEKNIGHT:
				m_nSelJob = CLASS_KNIGHT;
				break;
			case CLASS_MUSEELF:
				m_nSelJob = CLASS_ELF;
				break;
			case CLASS_BLOODYSUMMONER:
				m_nSelJob = CLASS_SUMMONER;
				break;
			case CLASS_GRANDMASTER:
				m_nSelJob = CLASS_WIZARD;
				break;
			case CLASS_BLADEMASTER:
				m_nSelJob = CLASS_KNIGHT;
				break;
			case CLASS_HIGHELF:
				m_nSelJob = CLASS_ELF;
				break;
			case CLASS_DUELMASTER:
				m_nSelJob = CLASS_DARK;
				break;
			case CLASS_LORDEMPEROR:
				m_nSelJob = CLASS_DARK_LORD;
				break;
			case CLASS_DIMENSIONMASTER:
				m_nSelJob = CLASS_SUMMONER;
				break;
#ifdef PBG_ADD_NEWCHAR_MONK
			case CLASS_TEMPLENIGHT:
				m_nSelJob = CLASS_RAGEFIGHTER;
				break;
#endif //PBG_ADD_NEWCHAR_MONK
			};
		}


		UpdateDisplay();

		for (int i = 0; i < MAX_CLASS; ++i)
		{
			m_abtnJob[i].SetEnable(false);
		}
		m_abtnJob[m_nSelJob].SetEnable(true);
	}
	else
		UpdateDisplay();
}
#endif //#ifdef PJH_CHARACTER_RENAME

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ĳ���� ����â ����.
//*****************************************************************************
void CCharMakeWin::Create()
{
	CInput rInput = CInput::Instance();
	CWin::Create(rInput.GetScreenWidth(), rInput.GetScreenHeight());

// �ƹ��͵� �Ⱥ��̴� ��� ������.
	m_winBack.Create(454, 406, -2);

// �̸� �Է� ��� ��������Ʈ.
	m_asprBack[CMW_SPR_INPUT].Create(346, 38, BITMAP_LOG_IN);
// �ɷ�ġ ��� ��������Ʈ.
	m_asprBack[CMW_SPR_STAT].Create(108, 80);
// ���� ���� ��� ��������Ʈ.
	m_asprBack[CMW_SPR_DESC].Create(454, 51);

	int i;
	for (i = CMW_SPR_STAT; i < CMW_SPR_MAX; ++i)
	{
		m_asprBack[i].SetAlpha(143);
		m_asprBack[i].SetColor(0, 0, 0);
	}

// ���� ��ư ����.
	DWORD adwJobBtnClr[8] =
	{
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, CLRDW_GRAY,
		CLRDW_BR_GRAY, CLRDW_BR_GRAY, CLRDW_WHITE, CLRDW_GRAY
	};

	int nText;
	for (i = 0; i < MAX_CLASS; ++i)
	{
		bool isMake = true;
#ifdef PSW_CHARACTER_CARD
		if( i == CLASS_SUMMONER ) {
			isMake = TheGameServerProxy().IsCharacterCard();
		}
#endif //PSW_CHARACTER_CARD
		if( isMake == true )
		{
			m_abtnJob[i].Create(108, 26, BITMAP_LOG_IN+1, 4, 2, 1, 0, 3, 3, 3, 0);
#ifdef PBG_ADD_NEWCHAR_MONK
			int _btn_classname[MAX_CLASS] = {20, 21, 22, 23, 24, 1687, 3150};
			nText = _btn_classname[i];
#else //PBG_ADD_NEWCHAR_MONK
			nText = CLASS_SUMMONER == i ? 1687 : 20 + i;
#endif //PBG_ADD_NEWCHAR_MONK
			m_abtnJob[i].SetText(GlobalText[nText], adwJobBtnClr);
			CWin::RegisterButton(&m_abtnJob[i]);
		}
	}

// OK, CANCEL ��ư ����.
	for (i = 0; i < 2; ++i)
	{
		m_aBtn[i].Create(54, 30, BITMAP_BUTTON + i, 3, 2, 1);
		CWin::RegisterButton(&m_aBtn[i]);
	}

	::memset(m_aszJobDesc, 0,
		sizeof(char) * CMW_DESC_LINE_MAX * CMW_DESC_ROW_MAX);
	m_nDescLine = 0;

	m_nSelJob = CLASS_KNIGHT;
	m_abtnJob[m_nSelJob].SetCheck(true);

	UpdateDisplay();
}

//*****************************************************************************
// �Լ� �̸� : PreRelease()
// �Լ� ���� : ��� ��Ʈ�� ������.(��ư�� �ڵ� ����)
//*****************************************************************************
void CCharMakeWin::PreRelease()
{
	for (int i = 0; i < CMW_SPR_MAX; ++i)
		m_asprBack[i].Release();
	m_winBack.Release();
}

//*****************************************************************************
// �Լ� �̸� : SetPosition()
// �Լ� ���� : â ��ġ ����.
// �Ű� ���� : nXCoord	: ��ũ�� X��ǥ.
//			   nYCoord	: ��ũ�� Y��ǥ.
//*****************************************************************************
void CCharMakeWin::SetPosition(int nXCoord, int nYCoord)
{
	// ��� â.
	m_winBack.SetPosition(nXCoord, nYCoord);

	// ���� ���.
	int nBaseX = nXCoord + 346;
	m_asprBack[CMW_SPR_STAT].SetPosition(nBaseX, nYCoord + 24);

	// ���� ��ư.
	int i;
	int nBaseY = nYCoord + 131;
	int nBtnHeight = m_abtnJob[0].GetHeight();
	for (i = 0; i < 3; ++i)
		m_abtnJob[i].SetPosition(nBaseX, nBaseY + i * nBtnHeight);
	m_abtnJob[CLASS_SUMMONER].SetPosition(nBaseX, nBaseY + 3 * nBtnHeight);
	nBaseY = nYCoord + 246;

#ifdef PBG_ADD_NEWCHAR_MONK
	m_abtnJob[CLASS_RAGEFIGHTER].SetPosition(nBaseX, nBaseY);

	for (; i <= CLASS_DARK_LORD; ++i)
		m_abtnJob[i].SetPosition(nBaseX, nBaseY + (i - 2) * nBtnHeight);
#else //PBG_ADD_NEWCHAR_MONK
	for (; i <= CLASS_DARK_LORD; ++i)
		m_abtnJob[i].SetPosition(nBaseX, nBaseY + (i - 3) * nBtnHeight);
#endif //PBG_ADD_NEWCHAR_MONK
	// Ȯ��, ��� ��ư.
	nBaseY = nYCoord + 325;
	m_aBtn[CMW_OK].SetPosition(nBaseX, nBaseY);
	m_aBtn[CMW_CANCEL].SetPosition(nXCoord + 400, nBaseY);

	// �ý�Ʈ �Է� ���.
	m_asprBack[CMW_SPR_INPUT].SetPosition(nXCoord, nYCoord + 317);

	if (g_iChatInputType == 1)
	{
		g_pSingleTextInputBox->SetPosition(
			int((m_asprBack[CMW_SPR_INPUT].GetXPos() + 78) / g_fScreenRate_x),
			int((m_asprBack[CMW_SPR_INPUT].GetYPos() + 21) / g_fScreenRate_y));
	}

	// ���� ���� ���.
	m_asprBack[CMW_SPR_DESC].SetPosition(nXCoord, nYCoord + 355);
}

//*****************************************************************************
// �Լ� �̸� : Show()
// �Լ� ���� : â�� ���� �ְų� �Ⱥ��̰���.
// �Ű� ���� : bShow	: true�̸� ������.
//*****************************************************************************
void CCharMakeWin::Show(bool bShow)
{
	CWin::Show(bShow);

	int i;
	for (i = 0; i < CMW_SPR_MAX; ++i)
		m_asprBack[i].Show(bShow);

	for (i = 0; i < MAX_CLASS; ++i)
		m_abtnJob[i].Show(bShow);
	for (i = 0; i < 2; ++i)
		m_aBtn[i].Show(bShow);

	if (bShow)
	{
		InputTextWidth = 73;
		ClearInput();
		InputEnable = true;
		InputNumber = 1;
		InputTextMax[0] = MAX_ID_SIZE;
		if (g_iChatInputType == 1)
		{
			g_pSingleTextInputBox->SetState(UISTATE_NORMAL);
#ifdef LJH_ADD_RESTRICTION_ON_ID
			g_pSingleTextInputBox->SetOption(UIOPTION_NOLOCALIZEDCHARACTERS);
#else  //LJH_ADD_RESTRICTION_ON_ID
			g_pSingleTextInputBox->SetOption(UIOPTION_NULL);
#endif //LJH_ADD_RESTRICTION_ON_ID
			g_pSingleTextInputBox->SetBackColor(0, 0, 0, 0);
			g_pSingleTextInputBox->SetTextLimit(10);
			g_pSingleTextInputBox->GiveFocus();
		}
	}
	else
	{
		if (g_iChatInputType == 1)
		{
			g_pSingleTextInputBox->SetText(NULL);
			g_pSingleTextInputBox->SetState(UISTATE_HIDE);
		}
	}
}

//*****************************************************************************
// �Լ� �̸� : CursorInWin()
// �Լ� ���� : ������ ���� �ȿ� ���콺 Ŀ���� ��ġ�ϴ°�?
// �Ű� ���� : eArea	: �˻��� ����.(win.h�� #define ����)
//*****************************************************************************
bool CCharMakeWin::CursorInWin(int nArea)
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
// �Լ� �̸� : UpdateDisplay()
// �Լ� ���� : ������ ������ â�� �ݿ���.
//*****************************************************************************
void CCharMakeWin::UpdateDisplay()
{
	int i;

	// ���� ���� ����.
	BYTE byMaxClass = ::GetCreateMaxClass();
#ifdef PBG_ADD_NEWCHAR_MONK
	// byMaxClass�� 3�̸� ��ĳ���� ���ð���/ 2�̸� ��ũ�ε� ���ð���/
	// 1�̸� ���˻缱�ð���/ 0�̸� �⺻ 4�� ĳ���� ��������
	const int _SecondClassCnt = 3;
	int _LimitClass[_SecondClassCnt] = {CLASS_DARK_LORD, CLASS_DARK, CLASS_RAGEFIGHTER};

	for(i=0; i<=MAX_CLASS; ++i)
	{
		m_abtnJob[i].SetEnable(true);
	}
	for(i=0; i<(_SecondClassCnt-byMaxClass); ++i)
	{
		m_abtnJob[_LimitClass[i]].SetEnable(false);
	}
#else //PBG_ADD_NEWCHAR_MONK
	// byMaxClass�� 5�� ��ĳ���� ���� ����. 4�� ��ũ�ε� ���� �Ұ���,
	//3�̸� ���˻�, ��ũ�ε� ���� �Ұ���.
	for (i = 0; i <= byMaxClass - 1; ++i)
		m_abtnJob[i].SetEnable(true);
	for (; i < CLASS_SUMMONER; ++i)
		m_abtnJob[i].SetEnable(false);
#endif //PBG_ADD_NEWCHAR_MONK

#ifdef PBG_ADD_CHARACTERCARD
	for(i=0; i<CLASS_CHARACTERCARD_TOTALCNT; ++i)
	{
		// ����,��ũ,��ȯ���� ���鼭 Ȱ��ȭ���� �Ǵ�
		if(!g_CharCardEnable.bCharacterEnable[i])
			m_abtnJob[i+CLASS_DARK].SetEnable(false);
	}
#else //PBG_ADD_CHARACTERCARD
	m_abtnJob[CLASS_SUMMONER].SetEnable(true);
#endif //PBG_ADD_CHARACTERCARD

	// ��ũ�ε��̸� ���� ��� ��������Ʈ �Ʒ��� ũ�� �ø�.
	if (m_nSelJob == CLASS_DARK_LORD)
		m_asprBack[CMW_SPR_STAT].SetSize(0, 96, Y);
	else
		m_asprBack[CMW_SPR_STAT].SetSize(0, 80, Y);

	// ���� ���� �� ������.
	int nText = m_nSelJob == CLASS_SUMMONER ? 1690 : 1705 + m_nSelJob;
#ifdef PBG_ADD_NEWCHAR_MONK
	if(m_nSelJob == CLASS_RAGEFIGHTER)
		nText = 3152;
#endif //PBG_ADD_NEWCHAR_MONK
	m_nDescLine = ::SeparateTextIntoLines(GlobalText[nText], m_aszJobDesc[0],
		CMW_DESC_LINE_MAX, CMW_DESC_ROW_MAX);

	SelectCreateCharacter();
}

//*****************************************************************************
// �Լ� �̸� : UpdateWhileActive()
// �Լ� ���� : ��Ƽ���� ���� ������Ʈ.
// �Ű� ���� : dDeltaTick	: ���� Update()ȣ�� �ĺ��� ���� Update()���� �ð�.
//*****************************************************************************
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING
void CCharMakeWin::UpdateWhileActive()
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING
void CCharMakeWin::UpdateWhileActive(double dDeltaTick)
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING
{
	// ���� �׷� ��ư ó��.
	int i, j;
#ifdef PJH_CHARACTER_RENAME
	if(ReName_Inter == false)
#endif //PJH_CHARACTER_RENAME
	{
		for (i = 0; i < MAX_CLASS; ++i)
		{
			if (m_abtnJob[i].IsClick())
			{
				// ���� ��ư ���� ����.
				for (j = 0; j < MAX_CLASS; ++j)
					m_abtnJob[j].SetCheck(false);
				m_abtnJob[i].SetCheck(true);

				if (m_nSelJob == i)
					break;

				m_nSelJob = i;
				UpdateDisplay();
				break;
			}
		}
	}
	/*
SendRequestChangeName( POldName, PNewName )
	*/
#ifdef PJH_CHARACTER_RENAME
	if(ReName_Inter == false)
#endif //PJH_CHARACTER_RENAME
	{
	if (m_aBtn[CMW_OK].IsClick())		// Ȯ�� ��ư Ŭ��.
		RequestCreateCharacter();
	else if (m_aBtn[CMW_CANCEL].IsClick())
		CUIMng::Instance().HideWin(this);

	else if (CInput::Instance().IsKeyDown(VK_RETURN))
	{
		::PlayBuffer(SOUND_CLICK01);
		RequestCreateCharacter();
	}
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE))
	{
		::PlayBuffer(SOUND_CLICK01);
		CUIMng::Instance().HideWin(this);
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
	}
#ifdef PJH_CHARACTER_RENAME
	else
	if(ReName_Inter == true)
	{
	if (m_aBtn[CMW_OK].IsClick())		// Ȯ�� ��ư Ŭ��.
	{
		if (g_iChatInputType == 1)
			g_pSingleTextInputBox->GetText(InputText[0]);

		CUIMng& rUIMng = CUIMng::Instance();
		// �Էµ� �̸��� üũ.
		if (::strlen(InputText[0]) < 4)
			rUIMng.PopUpMsgWin(MESSAGE_MIN_LENGTH);
		else if(::CheckName())
			rUIMng.PopUpMsgWin(MESSAGE_ID_SPACE_ERROR);
		else if(::CheckSpecialText(InputText[0]))
			rUIMng.PopUpMsgWin(MESSAGE_SPECIAL_NAME);
		else
			SendRequestChangeName( CharactersClient[SelectedHero].ID, InputText[0] );
	}
	else if (m_aBtn[CMW_CANCEL].IsClick())
		CUIMng::Instance().HideWin(this);
	else if (CInput::Instance().IsKeyDown(VK_RETURN))
	{
		::PlayBuffer(SOUND_CLICK01);
		if (g_iChatInputType == 1)
			g_pSingleTextInputBox->GetText(InputText[0]);
		
		CUIMng& rUIMng = CUIMng::Instance();
		// �Էµ� �̸��� üũ.
		if (::strlen(InputText[0]) < 4)
			rUIMng.PopUpMsgWin(MESSAGE_MIN_LENGTH);
		else if(::CheckName())
			rUIMng.PopUpMsgWin(MESSAGE_ID_SPACE_ERROR);
		else if(::CheckSpecialText(InputText[0]))
			rUIMng.PopUpMsgWin(MESSAGE_SPECIAL_NAME);
		else
			SendRequestChangeName( CharactersClient[SelectedHero].ID, InputText[0] );
	}
	else if (CInput::Instance().IsKeyDown(VK_ESCAPE))
	{
		::PlayBuffer(SOUND_CLICK01);
		CUIMng::Instance().HideWin(this);
		CUIMng::Instance().SetSysMenuWinShow(false);
	}
	}
#endif //PJH_CHARACTER_RENAME

	UpdateCreateCharacter();	// 3D ���� ĳ���� ������Ʈ.
}

//*****************************************************************************
// �Լ� �̸� : RequestCreateCharacter()
// �Լ� ���� : ������ ������ ĳ���͸� ��û.
//*****************************************************************************
void CCharMakeWin::RequestCreateCharacter()
{
	if (g_iChatInputType == 1)
		g_pSingleTextInputBox->GetText(InputText[0]);

	CUIMng& rUIMng = CUIMng::Instance();
	// �Էµ� �̸��� üũ.
	if (::strlen(InputText[0]) < 4)
		rUIMng.PopUpMsgWin(MESSAGE_MIN_LENGTH);
    else if(::CheckName())
		rUIMng.PopUpMsgWin(MESSAGE_ID_SPACE_ERROR);
	else if(::CheckSpecialText(InputText[0]))
		rUIMng.PopUpMsgWin(MESSAGE_SPECIAL_NAME);
	else
	{
		SendRequestCreateCharacter(
			InputText[0], CharacterView.Class, CharacterView.Skin);
		rUIMng.HideWin(this);
		rUIMng.PopUpMsgWin(MESSAGE_WAIT);
	}
}

//*****************************************************************************
// �Լ� �̸� : RenderControls()
// �Լ� ���� : ���� ��Ʈ�� ����.
//*****************************************************************************
void CCharMakeWin::RenderControls()
{
	RenderCreateCharacter();	// 3D ���� ĳ���� ����.
	::EnableAlphaTest();

	int i;
	for (i = 0; i < CMW_SPR_MAX; ++i)
	{
#ifdef PJH_CHARACTER_RENAME
		if(i == CMW_SPR_STAT && ReName_Inter == true)
			continue;
#endif //PJH_CHARACTER_RENAME
		m_asprBack[i].Render();
	}
	CWin::RenderButtons();
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->SetBgColor(0);

// �ɷ�ġ.
	char* apszStat[MAX_CLASS][4] =
	{
		"18", "18", "15", "30",		// �渶����.
		"28", "20", "25", "10",		// ����.
		"22", "25", "20", "15",		// ����.
		"26", "26", "26", "26",		// ���˻�.
		"26", "20", "20", "15",		// ��ũ�ε�.
		"21", "21", "18", "23",		// ��ȯ����.
#ifdef PBG_ADD_NEWCHAR_MONK
		"32", "27", "25", "20",		// ������������
#endif //PBG_ADD_NEWCHAR_MONK
	};
	int nStatBaseX = m_asprBack[CMW_SPR_STAT].GetXPos() + 22;
	int nStatY;
	for (i = 0; i < 4; ++i)
	{
#ifdef PJH_CHARACTER_RENAME
		if(ReName_Inter == true)
			continue;
#endif //PJH_CHARACTER_RENAME		
		nStatY = int((m_asprBack[CMW_SPR_STAT].GetYPos() + 10 + i * 17)
			/ g_fScreenRate_y);

		// �ɷ�ġ ��.
		g_pRenderText->SetTextColor(CLRDW_ORANGE);
		g_pRenderText->RenderText(int((nStatBaseX + 54) / g_fScreenRate_x), nStatY,
			apszStat[m_nSelJob][i]);
		// �ɷ�ġ �̸�.
		g_pRenderText->SetTextColor(CLRDW_WHITE);
		g_pRenderText->RenderText(int(nStatBaseX / g_fScreenRate_x), nStatY,
			GlobalText[1701 + i]);
	}

	// ��ũ�ε��ϰ�츸 ��� �ɷ�ġ ǥ��.
	if (m_nSelJob == CLASS_DARK_LORD
#ifdef PJH_CHARACTER_RENAME
		&& ReName_Inter == false
#endif //PJH_CHARACTER_RENAME
		)
	{
		nStatY = int((m_asprBack[CMW_SPR_STAT].GetYPos() + 10 + 4 * 17)
			/ g_fScreenRate_y);

		// �ɷ�ġ ��.
		g_pRenderText->SetTextColor(CLRDW_ORANGE);
		g_pRenderText->RenderText(int((nStatBaseX + 54) / g_fScreenRate_x), nStatY, "25");

		// �ɷ�ġ �̸�.
		g_pRenderText->SetTextColor(CLRDW_WHITE);
		g_pRenderText->RenderText(int(nStatBaseX / g_fScreenRate_x), nStatY, GlobalText[1738]);
	}

// ���� ����.
#ifdef PJH_CHARACTER_RENAME
	if(ReName_Inter == true)
	{
		g_pRenderText->RenderText(int((m_asprBack[CMW_SPR_DESC].GetXPos() + 10) / g_fScreenRate_x),
			int((m_asprBack[CMW_SPR_DESC].GetYPos() + 12)
			/ g_fScreenRate_y), GlobalText[676]);
	}
	else
#endif //PJH_CHARACTER_RENAME
	{
		for (i = 0; i < m_nDescLine; ++i)
		{
			g_pRenderText->RenderText(int((m_asprBack[CMW_SPR_DESC].GetXPos() + 10) / g_fScreenRate_x),
				int((m_asprBack[CMW_SPR_DESC].GetYPos() + 12 + i * 19)
				/ g_fScreenRate_y), m_aszJobDesc[i]);
		}
	}

// ĳ���� �̸� �Էºκ�.
	g_pRenderText->SetFont(g_hFont);
	
	if (g_iChatInputType == 1)
		g_pSingleTextInputBox->Render();
	else if (g_iChatInputType == 0)
		::RenderInputText(
			int((m_asprBack[CMW_SPR_INPUT].GetXPos() + 78) / g_fScreenRate_x),
			int((m_asprBack[CMW_SPR_INPUT].GetYPos() + 21) / g_fScreenRate_y),
			0);
}

//*****************************************************************************
// �Լ� �̸� : SelectCreateCharacter()
// �Լ� ���� : 3D ���� ĳ���� ����.
//*****************************************************************************
void CCharMakeWin::SelectCreateCharacter()
{
	CharacterView.Class = m_nSelJob;
	CreateCharacterPointer(&CharacterView,MODEL_FACE+CharacterView.Class,0,0);
	CharacterView.Object.Kind = 0;
	SetAction(&CharacterView.Object,1);
}

//*****************************************************************************
// �Լ� �̸� : UpdateCreateCharacter()
// �Լ� ���� : 3D ���� ĳ���� ������Ʈ.
//*****************************************************************************
void CCharMakeWin::UpdateCreateCharacter()
{
	if (!CharacterAnimation(&CharacterView, &CharacterView.Object))
		SetAction(&CharacterView.Object,0);
}

//*****************************************************************************
// �Լ� �̸� : RenderCreateCharacter()
// �Լ� ���� : 3D ���� ĳ���� ����.
//*****************************************************************************
void CCharMakeWin::RenderCreateCharacter()
{
	OBJECT *o = &CharacterView.Object;
	vec3_t Position, Angle;

 	Vector(1.0f,1.0f,1.0f,o->Light);
	Vector(10,-500.f,48.f,Position);
	Vector(-90.f,0.f,0.f,Angle);
    CameraFOV = 10.f;
	MoveCharacterCamera(CharacterView.Object.Position,Position,Angle);

	BeginOpengl( m_winBack.GetXPos()/g_fScreenRate_x, m_winBack.GetYPos()/g_fScreenRate_y,
				410/g_fScreenRate_x, 335/g_fScreenRate_y );

	if (CharacterView.Class == CLASS_WIZARD)
	{
		Vector(0.f, 0.f, -40.0f, o->Angle);
		o->Scale = 5.9f;
	}
	else if (CharacterView.Class == CLASS_KNIGHT)
	{
		Vector(0.f, 0.f, -12.0f, o->Angle);
		o->Scale = 6.05f;
	}
	else if (CharacterView.Class == CLASS_ELF)
	{
		Vector(8.f, 0.f, 5.0f, o->Angle);
		o->Scale = 9.1f;
		CharacterView.Object.Position[0] += 4.8f;
	}
	else if (CharacterView.Class == CLASS_DARK)
	{
		Vector(8.f, 0.f, -13.0f, o->Angle);
		o->Scale = 6.0f;
		CharacterView.Object.Position[2] += 1.8f;
	}
	else if (CharacterView.Class == CLASS_DARK_LORD)
	{
		Vector(8.f, 0.f, -18.0f, o->Angle);
		o->Scale = 6.0f;
	}
	else if (CharacterView.Class == CLASS_SUMMONER)
	{
		Vector(2.f, 0.f, 2.0f, o->Angle);
		o->Scale = 9.1f;
		CharacterView.Object.Position[0] += 4.8f;
		CharacterView.Object.Position[2] += 4.0f;
	}
#ifdef PBG_ADD_NEWCHAR_MONK
	else if (CharacterView.Class == CLASS_RAGEFIGHTER)
	{
		o->Scale = 6.0f;
		CharacterView.Object.Position[0] += 9.8f;
		CharacterView.Object.Position[2] -= 7.5f;
	}
#endif //PBG_ADD_NEWCHAR_MONK

#ifdef MR0
	VPManager::Enable();
#endif //MR0
	RenderCharacter(&CharacterView,o);
#ifdef MR0
	VPManager::Disable();
#endif //MR0	

	glViewport2(0,0,WindowWidth,WindowHeight);

	EndOpengl();
}
