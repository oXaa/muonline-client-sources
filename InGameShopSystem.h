// InGameShopSystem.h: interface for the InGameShopSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INGAMESHOPSYSTEM_H__2DF68839_DA28_44BC_B662_213BB22839CB__INCLUDED_)
#define AFX_INGAMESHOPSYSTEM_H__2DF68839_DA28_44BC_B662_213BB22839CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef KJH_ADD_INGAMESHOP_UI_SYSTEM

#ifdef KJH_MOD_LIBRARY_LINK_EACH_NATION
#include <ShopListManager.h>
#include <BannerListManager.h>
#else // KJH_MOD_LIBRARY_LINK_EACH_NATION
#include "./InGameShopSystem/ShopListManager/ShopListManager.h"				
#include "./InGameShopSystem/ShopListManager/BannerListManager.h"
#endif // KJH_MOD_LIBRARY_LINK_EACH_NATION


/* 
	// < Sequence �� Index�� ���� >
	// Sequence : Sciprt���� Category, Package, Product�� ������ȣ
	// Index : UI���� �ѹ���
*/

#define INGAMESHOP_ERROR_ZERO_SIZE		(-1)
#define INGAMESHOP_ERROR_INVALID_INDEX	(-2)

//#define INGAMESHOP_DISPLAY_ITEMLIST_SIZE		(9)		_define.h �� �ű�

//typedef std::map<int, CShopPackage>		type_mapPackage;
typedef std::list<CShopPackage>			type_listPackage;
typedef std::map<int, int>				type_mapZoneSeq;
typedef std::list<unicode::t_string>	type_listName;

class CInGameShopSystem
{
public:
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT				// #ifndef
	enum LISTBOX_INDEX
	{
		IGS_SAFEKEEPING_LISTBOX = 0,
		IGS_PRESENTBOX_LISTBOX,
		IGS_TOTAL_LISTBOX,
	};
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// ��Ű�� ��ǰ ����
	enum IGS_PACKAGE_GOODS_TYPE
	{
		IGS_GOODS_TYPE_FIXEDAMOUNT		= 135,		// ���׻�ǰ
		IGS_GOODS_TYPE_FIXEDQUANTITY	= 136,		// ������ǰ
		IGS_GOODS_TYPE_PREMIUM			= 137,		// �����̾���ǰ
		IGS_GOODS_TYPE_CONSUMPTION		= 138,		// �Ҹ𼺾�����
		IGS_GOODS_TYPE_ETERNITY			= 139,		// ������������
		IGS_GOODS_TYPE_PERIOD			= 140,		// �Ⱓ��������
		IGS_GOODS_TYPE_PREMIUM_ITEM		= 406,		// �����̾�������
		IGS_GOODS_TYPE_GOBLIN_POINT		= 515,		// �������Ʈ	
	};

	enum IGS_PACKAGE_ATTRIBUTE_TYPE
	{
		IGS_PACKAGE_ATT_TYPE_NONE	= 0,
		IGS_PACKAGE_ATT_TYPE_NAME,			// Name
		IGS_PACKAGE_ATT_TYPE_DESCRIPTION,	// Description (�󼼼���)
		IGS_PACKAGE_ATT_TYPE_PRICE,			// ����
		IGS_PACKAGE_ATT_TYPE_ITEMCODE,			// ItemCode
	};

	enum IGS_PRODUCT_ATTRIBUTE_TYPE
	{
		IGS_PRODUCT_ATT_TYPE_NONE	= 0,
		IGS_PRODUCT_ATT_TYPE_USE_LIMIT_PERIOD,	// ���Ⱓ
		IGS_PRODUCT_ATT_TYPE_AVALIABLE_PERIOD,	// ��ȿ�Ⱓ
		IGS_PRODUCT_ATT_TYPE_NUM,				// ����
		IGS_PRODUCT_ATT_TYPE_PRICE,				// ������ ����
		IGS_PRODUCT_ATT_TYPE_ITEMCODE,			// �������ڵ�
		IGS_PRODUCT_ATT_TYPE_ITEMNAME,			// ������ �̸�
		IGS_PRODUCT_ATT_TYPE_PRICE_SEQUENCE,	// Price Seq
	};

	enum IGS_ETC
	{
		IGS_LIMIT_REQUEST_EVENT_PACKAGE	= 20,	// �̺�Ʈ ��Ű�� ��û�� ���� (�̺�Ʈ�� 20�� Ŭ��)
	};

protected:
	CInGameShopSystem();
public:
	~CInGameShopSystem();

public:
	static CInGameShopSystem* GetInstance();

 	void Initalize();
// 	bool Update();
// 	bool Render();
 	void Release();

	void SetScriptVersion(int iSalesZone, int iYear, int iYearId);
	void SetBannerVersion(int iSalesZone, int iYear, int iYearId);
	bool ScriptDownload();		// �ΰ��Ӽ� ��ũ��Ʈ �ٿ�ε�
	bool BannerDownload();		// ���� ��ũ��Ʈ �ٿ�ε�

public:
	// ���� Zone, Category Setting
	bool SelectZone(int iIndex);
	bool SelectCategory(int iIndex);

	// ItemList Page����
	void BeginPage();
	void NextPage();
	void PrePage();
	int GetTotalPages();
	int GetSelectPage();

	// Zone, Category, Package ���� Get
	int GetSizeZones();
	int GetSizeCategoriesAsSelectedZone();
	int GetSizePackageAsSelectedCategory();
	int GetSizePackageAsDisplayPackage();

	// Package�� ��������
	WORD GetPackageItemCode(int iIndex);

	// Zone, Category Name Get/Set
	type_listName GetZoneName();			// Zone Name Get
	type_listName GetCategoryName();		// Category Name Get

	// Cash, Point, Mileage
	void SetTotalCash(double dTotalCash);
	void SetTotalPoint(double dTotalPoint);
	void SetTotalMileage(double dTotalMileage);
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	void SetCashCreditCard(double dCashCreditCard);		// Global Credit Cash
	void SetCashPrepaid(double dCashPrepaid);			// Global Prepaid Cash
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	double GetTotalCash();
	double GetTotalPoint();
	double GetTotalMileage();
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	double GetCashCreditCard();							// Global Credit Cash
	double GetCashPrepaid();							// Global Prepaid Cash
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	
	// Display�Ǿ��ִ� Packaged�� Pointer�� Get
	CShopPackage* GetDisplayPackage(int iIndex);		

	// Product ��������
	//void SetProductSeqFirst(int iProductSeq);
	//bool GetProductSeqNext(CShopProduct& product);

	// �� Open ��û������ ����
	void SetIsRequestShopOpenning(bool bIsRequestShopOpenning);
	bool GetIsRequestShopOpenning();

	// ������ ����
	//void SetStorageItemCnt(int iStorageIndex, int iItemCnt);
	//int	GetStorageItemCnt(int iStorageIndex);
#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT			// # ifndef
	void SetStorageItemCnt(int iItemCnt);
	int GetStorageItemCnt();
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	// Package�� ���� OUT
	bool GetPackageInfo(int iPackageSeq, int iPackageAttrType, OUT int& iValue, OUT unicode::t_char* pszText);

	// ���� ��ǰ�϶� PriceSeq�� �Ӽ������� �޾ƿ´�.
	bool GetProductInfoFromPriceSeq(int iProductSeq, int iPriceSeq, int iAttrType, 
									OUT int& iValue, OUT unicode::t_char* pszUnitName);
	bool GetProductInfoFromProductSeq(int iProductSeq, int iAttrType, OUT int& iValue, OUT unicode::t_char* pszUnitName);

	// Normal Package����
	void SetNormalPackage();
	//void SetEventPackage();

	// Event Package����
	void InitEventPackage(int iTotalEventPackage);
#ifdef KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
	void InsertEventPackage(int* pPackageSeq);
#else // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
	void InsertEventPackage(int iPackageSeq);
#endif // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE

	// Shop Open ����
	bool IsShopOpen();
	bool IsRequestEventPackge();
	void SetRequestEventPackge();

	// Banner ����
	bool IsBanner();
	unicode::t_char* GetBannerFileName();
	unicode::t_char* GetBannerURL();

	// ��ũ��Ʈ ���� ����
	CListVersionInfo GetScriptVer();
	CListVersionInfo GetBannerVer();
#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	CListVersionInfo GetCurrentScriptVer();
	CListVersionInfo GetCurrentBannerVer();
	bool IsScriptDownload();			// ��ũ��Ʈ�� �ٿ�ε� �� �� �ִ���
	bool IsBannerDownload();			// ��ʸ� �ٿ�ε� �� �� �ִ���

	// Shop Open ����
	void ShopOpenLock();
	void ShopOpenUnLock();
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

	// �����Լ���
protected:
	void InitZoneInfo();							// Zone���� ����
	void InitPackagePerPage(int iPageIndex);		// ���� �������� ��Ű�� Init

	// Zone, Category Seq Get
	int GetZoneSeqIndexByIndex(int iIndex);		// Zone SeqIndex Get
	int GetCategorySeqIndexByIndex(int iIndex);	// Category SeqIndex Get

	// Category Name Set
	void SetCategoryName();

#ifndef KJH_MOD_SHOP_SCRIPT_DOWNLOAD			// #ifndef  - ������ �� ������ �ϴ� �ҽ�
	// Shop Open ����
	void ShopOpenLock();
	void ShopOpenUnLock();
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

	bool GetProductInfo(CShopProduct* pProduct, int iAttrType, OUT int& iValue, OUT unicode::t_char* pszUnitName);

protected:
	CShopListManager		m_ShopManager;			// �ΰ��Ӽ� �Ŵ���
	CBannerListManager		m_BannerManager;		// ��� �Ŵ���

	CListVersionInfo		m_ScriptVerInfo;		// �ٿ���� ��ũ��Ʈ ��������
	CListVersionInfo		m_BannerVerInfo;		// �ٿ���� ��� ��������

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	CListVersionInfo		m_CurrentScriptVerInfo;		// ���� ��ũ��Ʈ ��������
	CListVersionInfo		m_CurrentBannerVerInfo;		// ���� ��� ��������
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
	
#ifdef KJH_MOD_INGAMESHOP_DOMAIN_EACH_NATION
	char					m_szScriptIPAddress[20];			// ��ũ��Ʈ/��� ���� IP�ּ�
	char					m_szBannerIPAddress[20];	// ��� ���� IP�ּ�
#else // KJH_MOD_INGAMESHOP_DOMAIN_EACH_NATION
	char					m_szIPAddress[20];			// ��ũ��Ʈ/��� ���� IP�ּ�
#endif // KJH_MOD_INGAMESHOP_DOMAIN_EACH_NATION
	char					m_szScriptRemotePath[MAX_TEXT_LENGTH];	// ��ũ��Ʈ ���� ���� Path 
	char					m_szScriptLocalPath[MAX_TEXT_LENGTH];	// ��ũ��Ʈ ���� �ٿ�ε� Path
	char					m_szBannerRemotePath[MAX_TEXT_LENGTH];	// ��� ���� ���� Path 
	char					m_szBannerLocalPath[MAX_TEXT_LENGTH];	// ��� ���� �ٿ�ε� Path

	CShopCategory			m_SelectedZone;			// ���� ���õǾ����ִ� Zone - Category list�� �ִ�.
 	CShopCategory			m_SelectedCategory;		// ���� ���õǾ����ִ� Category - ��Ű������ ����Ʈ�� �ִ�.
	CBannerInfo				m_BannerInfo;			// ���� ��� ����

 	int						m_iSelectedPage;		// ���� ��������ȣ

	type_mapZoneSeq			m_mapZoneSeqIndex;		// Zone�� SeqIndex
	type_listPackage		m_listDisplayPackage;	// ���� �������� ��Ű����
	type_listPackage		m_listNormalPackage;	// �Ϲ� ��Ű����
	type_listPackage		m_listEventPackage;		// �̺�Ʈ ��Ű����
	type_listPackage*		m_plistSelectPackage;		// �Ϲ�/�̺�Ʈ ��Ű��
	type_listName			m_listZoneName;			// Zone�� Name
	type_listName			m_listCategoryName;		// ���� ���õǾ����ִ� Category�� Name
	
	CShopCategoryList		*m_pCategoryList;		// Category ����Ʈ Pointer
	CShopPackageList		*m_pPackageList;		// Packege ����Ʈ Pointer
	CShopProductList		*m_pProductList;		// Product ����Ʈ Pointer

	CBannerInfoList			*m_pBannerList;			// Banner ����Ʈ Pointer
	
	double					m_dTotalCash;			// ���� ĳ��
	double					m_dTotalPoint;			// ���� ����Ʈ  (������)
	double					m_dTotalMileage;		// ���� ���ϸ��� (��� ����Ʈ)
#ifdef KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL
	double					m_dCashCreditCard;		// ���� ĳ��:�ſ�ī�� �۷ι� ��츸
	double					m_dCashPrepaid;			// ���� ĳ��:���ݰ��� �۷ι� ��츸
#endif // KJH_MOD_INGAMESHOP_GLOBAL_CASHPOINT_ONLY_GLOBAL

	bool					m_bIsRequestEventPackage;		// �̺�Ʈ ��Ű�� ������ ��û������ ����

	bool					m_bIsRequestShopOpenning;		// �� Open ��û������ ����

	bool					m_bSelectEventCategory;		// �̺�Ʈ ī�װ��� �����ߴ��� ����
	bool					m_bAbleRequestEventPackage;	// �̺�Ʈ ��Ű�� ��û �������� ����
	int						m_iCntSelectEventZone;		// �̺�Ʈ �� ���� ī��Ʈ (�̺�Ʈ ��Ű���� ������ �Ź� ��û���� �ʱ� ����)

#ifndef KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT			// #ifndef
	int						m_iStorageItemCnt;		// �������� Item�� ����
#endif // KJH_MOD_INGAMESHOP_ITEM_STORAGE_PAGE_UNIT

	int						m_iEventPackageCnt;		// �̺�Ʈ Package�� ����
	int						m_iTotalEventPackage;	// �����κ��� �ٿ�޾ƾ��� �̺�Ʈ Package�� ����
#ifdef KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
	int						m_iCurrentEventPackage;	// ������ ���� ���� Event Package
#else // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE
#ifdef KJH_MOD_INGAMESHOP_PATCH_091028
	int						m_iTotalEventPackageFindFault;	// ������ ���� ���� Event Package Index�� ��ũ��Ʈ�� ������ ���� ����
#endif // KJH_MOD_INGAMESHOP_PATCH_091028
#endif // KJH_FIX_SHOP_EVENT_CATEGORY_PAGE

	bool					m_bIsShopOpenLock;		// ShopOpen ��ױ�(��ũ��Ʈ �ε� ���н�)
	bool					m_bIsBanner;			// ��� �ε� ����
#ifdef KJH_FIX_INGAMESHOP_SCRIPTDOWN_BUG
	bool					m_bFirstScriptDownloaded;	// ���ӽ����� �ѹ��� ��ũ��Ʈ�� �ٿ�޾ƾ� �Ѵ�.
	bool					m_bFirstBannerDownloaded;
#endif // KJH_FIX_INGAMESHOP_SCRIPTDOWN_BUG
};	

#define g_InGameShopSystem CInGameShopSystem::GetInstance()

#endif // KJH_ADD_INGAMESHOP_UI_SYSTEM

#endif // !defined(AFX_INGAMESHOPSYSTEM_H__2DF68839_DA28_44BC_B662_213BB22839CB__INCLUDED_)
