// w_ShopTopModule.h: interface for the ShopTopModule class.
//
//////////////////////////////////////////////////////////////////////

#ifdef NEW_USER_INTERFACE_CLIENTSYSTEM

#if !defined(AFX_W_SHOPTOPMODULE_H__93874584_857F_459C_A60F_4D390E590044__INCLUDED_)
#define AFX_W_SHOPTOPMODULE_H__93874584_857F_459C_A60F_4D390E590044__INCLUDED_

#include "w_UIWnd.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

BoostSmartPointer( ShopTopModule );
class ShopTopModule : public Module, public ShopServerProxyHandler
{
public:
	static ShopTopModulePtr Make( Module::eType type );
	virtual ~ShopTopModule();

public:
	//void �Լ���( ui::UIWnd& wnd( �Ķ��Ÿ�� ���� ������ ) )
	//�Լ��� On�� ���δ��� ���� Clk�� ���δ�.
	void OnHighCategoryClk( ui::UIWnd& wnd );

private:
	void Initialize( BoostWeak_Ptr(ShopTopModule) handler );
	void Destroy();
	ShopTopModule( Module::eType type );
};

#endif // !defined(AFX_W_SHOPTOPMODULE_H__93874584_857F_459C_A60F_4D390E590044__INCLUDED_)

#endif //NEW_USER_INTERFACE_CLIENTSYSTEM
