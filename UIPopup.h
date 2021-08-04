//  
//  UIPopup.h
//  
//  ��  �� : �˾�â ����
//  
//  ��  ¥ : 2004�� 11�� 12��
//  
//  �ۼ��� : �� �� ��
//  
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIPOPUP_H__1FD0B6C0_1EB3_4805_965C_C53A6A9A39B3__INCLUDED_)
#define AFX_UIPOPUP_H__1FD0B6C0_1EB3_4805_965C_C53A6A9A39B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// �˾�â�� ����
#define	POPUP_CUSTOM	0	// SetPopupExtraFunc �� ���� ó���Ǵ� �˾�â
#define	POPUP_OK		1	// Ȯ�� ��ư���� �̷����
#define	POPUP_OKCANCEL	2	// Ȯ��, ��� ��ư���� �̷����
#define	POPUP_YESNO		4	// ��, �ƴϿ� ��ư���� �̷����
#define	POPUP_TIMEOUT	8	// �ð������� �ڵ� �ݱ�(���հ���)
#define	POPUP_INPUT		16	// �Է°��� �޴� �˾�

// �˾�â�� �����
typedef int POPUP_RESULT;
#define	POPUP_RESULT_NONE		1
#define	POPUP_RESULT_OK			2			// Ȯ�� ��ư ����
#define	POPUP_RESULT_CANCEL		4			// ��� ��ư ����
#define	POPUP_RESULT_YES		8			// �� ��ư ����
#define	POPUP_RESULT_NO			16			// �ƴϿ� ��ư ����
#define	POPUP_RESULT_TIMEOUT	32			// �ð��ʰ�
#define	POPUP_RESULT_ESC		64			// ESC ������ ����..(÷����)

enum POPUP_ALIGN
{
	PA_CENTER,
	PA_TOP
};

#define MAX_POPUP_TEXTLINE		10
#define MAX_POPUP_TEXTLENGTH	256


class CUIPopup  
{
public:
	CUIPopup();
	virtual ~CUIPopup();

protected:
	// �˾�â�� ������� ���ϵ� �Լ�������
	int (*PopupResultFuncPointer)( POPUP_RESULT Result );
	// �˾�â�� Custom �κ��� ó���� �Լ�������
	void (*PopupUpdateInputFuncPointer)();
	void (*PopupRenderFuncPointer)();

	DWORD			m_dwPopupID;			// ���� �ε���
	int				m_nPopupTextCount;		// �˾��ؽ�Ʈ ���� ��
	char			m_szPopupText[MAX_POPUP_TEXTLINE][MAX_POPUP_TEXTLENGTH];	// �˾��ؽ�Ʈ ����
	int				m_PopupType;			// �˾�â Ÿ��
	SIZE			m_sizePopup;			// �˾�â ũ��
	POPUP_ALIGN		m_Align;				// �˾�â �ߴ� ��ġ

	char			m_szInputText[1024];	// �Է� �ؽ�Ʈ ���� (POPUP_INPUT���� ����)
	int				m_nInputSize;			// �Է�â ũ�� (POPUP_INPUT���� ����)
	int				m_nInputTextLength;		// �Է��ؽ�Ʈ �ִ���� (POPUP_INPUT���� ����)
	UIOPTIONS		m_InputOptions;			// �Է½�Ÿ�� (POPUP_INPUT���� ����)

	DWORD			m_dwPopupStartTime;		// �˾�â�� ���۵� �ð� (POPUP_TIMEOUT���� ����)
	DWORD			m_dwPopupEndTime;		// �˾�â�� ����� �ð� (POPUP_TIMEOUT���� ����)
	DWORD			m_dwPopupElapseTime;	// �˾�â�� ���ӵ� �ð� (POPUP_TIMEOUT���� ����)

	CUIButton		m_OkButton;
	CUIButton		m_CancelButton;
	CUIButton		m_YesButton;
	CUIButton		m_NoButton;

protected:
	bool CheckTimeOut();

public:
	// �ʱ�ȭ
	void Init();

	// �˾�����
	DWORD SetPopup( const char* pszText, int nLineCount, int nBufferSize, int Type, int (*ResultFunc)( POPUP_RESULT Result ), POPUP_ALIGN Align=PA_CENTER );
	// Custom �˾� (�Է°� �������� ���� ó���� ��� ����)
	void SetPopupExtraFunc( void (*InputFunc)(), void (*RenderFunc)() );

	void SetInputMode( int nSize, int nTextLength, UIOPTIONS Options );
	bool IsInputEnable();

	void SetTimeOut( DWORD dwElapseTime );

	char* GetInputText();
	DWORD GetPopupID();
	void Close();

	// �˾�â ���� �ݱ�
	void CancelPopup();

	// ���ο��� ó���ϸ� TRUE ����
	bool PressKey( int nKey );

	// �Է�ó��
	void UpdateInput();
	// ������
	void Render();
};

#endif // !defined(AFX_UIPOPUP_H__1FD0B6C0_1EB3_4805_965C_C53A6A9A39B3__INCLUDED_)
