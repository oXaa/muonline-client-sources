// NewUICommon.h: interface for the CNewUICommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWUICOMMON_H__0668BCBC_7537_454B_82FD_9D6BBBBDBA84__INCLUDED_)
#define AFX_NEWUICOMMON_H__0668BCBC_7537_454B_82FD_9D6BBBBDBA84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE
#include "_GlobalFunctions.h"
#endif // KJH_ADD_VS2008PORTING_ARRANGE_INCLUDE

namespace SEASON3B
{
	// �ƹ� ��ɾ��� �ؽ�Ʈ�� OK��ư�� �� �޼����ڽ� ����
	bool CreateOkMessageBox(const unicode::t_string& strMsg, DWORD dwColor = 0xffffffff, float fPriority = 3.f);

	// ���λ��� Ÿ�� ����
	int IsPurchaseShop(); 
	#define g_IsPurchaseShop SEASON3B::IsPurchaseShop()

	// ���콺 ���� �˻�
	bool CheckMouseIn(int x, int y, int width, int height);
	
	// ���� ũ�� �̹��� �״�� ���� �� ���
	void RenderImage(GLuint uiImageType, float x, float y, float width, float height);
	// ũ�� ���� ���� ����UV ������ ������ ��� ��� 
	void RenderImage(GLuint uiImageType, float x, float y, float width, float height, float su, float sv);
	void RenderImage(GLuint uiImageType, float x, float y, float width, float height, float su, float sv, DWORD color);
	void RenderImage(GLuint uiImageType, float x, float y, float width, float height, float su, float sv,float uw, float vh, DWORD color = RGBA(255,255,255,255));
	
	// ���� �̹��� ������ �Լ�
	float RenderNumber(float x, float y, int iNum, float fScale = 1.0f);
	
	// Ű�Է� ó��
	
	//. CW32KeyInput�� ����
	bool IsNone(int iVirtKey);		//. �ȴ��ȴ°�?
	bool IsRelease(int iVirtKey);	//. Ű�� �� ���� �������Ӹ�
	bool IsPress(int iVirtKey);		//. ���� ������ ù�����ӿ���
	bool IsRepeat(int iVirtKey);	//. ������ ���� ��
	
	class CNewKeyInput //. ���� ����
	{
		struct INPUTSTATEINFO 
		{
			BYTE byKeyState;
		} m_pInputInfo[256];

#ifndef ASG_FIX_ACTIVATE_APP_INPUT	// ������ ����.
		void Init();
#endif	// ASG_FIX_ACTIVATE_APP_INPUT

	public:
		enum KEY_STATE 
		{ 
			KEY_NONE=0,			
			KEY_RELEASE,		
			KEY_PRESS,			
			KEY_REPEAT			
		};
		~CNewKeyInput();
		
		static CNewKeyInput* GetInstance();
#ifdef ASG_FIX_ACTIVATE_APP_INPUT
		void Init();
#endif	// ASG_FIX_ACTIVATE_APP_INPUT
		void ScanAsyncKeyState();

		bool IsNone(int iVirtKey);
		bool IsRelease(int iVirtKey);
		bool IsPress(int iVirtKey); 
		bool IsRepeat(int iVirtKey);
		void SetKeyState(int iVirtKey, KEY_STATE KeyState);
		

	protected:
		CNewKeyInput();			//. ban to create a instance
	};
}

#define g_pNewKeyInput	SEASON3B::CNewKeyInput::GetInstance()

#endif // !defined(AFX_NEWUICOMMON_H__0668BCBC_7537_454B_82FD_9D6BBBBDBA84__INCLUDED_)
