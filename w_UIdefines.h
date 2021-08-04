#pragma once

#ifdef NEW_USER_INTERFACE_UISYSTEM

typedef struct _UISCRIPT
{
	//�θ�
	string			s_ParentFrameName;
	vector<string>	s_ParentWndName;

	//�������̸�
	string		s_UiName;
	int			s_UiID;	

	//�̹��� ����Ÿ
	string		s_UiImgFileName;
	int			s_UIImgIndex;

	//��ǥ �� ũ��
	Coord		s_Position;
	Dim			s_Size;

	_UISCRIPT() : s_UiID( -1 ), s_UIImgIndex( -1 ){}

} UISCRIPT;

#define CLIENTINTERFACEMODULEMAKEFUNC( classname, type ) \
	class classname; \
		public: \
			static BoostSmart_Ptr<classname> Make( type );

#define UIMAKERDECLARE \
	public: \
		static void MakeUI( UISCRIPT& uiscriptdata, ui::UIWnd& parentWnd );

#define UIMAKER( classname, uidata, parentWnd ) \
	class classname; \
{ \
	classname::MakeUI( uidata, parentWnd ); \
}

#endif //NEW_USER_INTERFACE_UISYSTEM
