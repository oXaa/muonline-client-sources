#pragma once

#ifdef NEW_STRUCTS

//////////////////////////////////////////////////////////////////////////
// [�ش� �ڵ�]
//////////////////////////////////////////////////////////////////////////

typedef struct _HEAD2
{
	BYTE c;			// �������� �ڵ�
	BYTE size;		// �������� ũ��( ��� ũ�� ���� )
	BYTE headcode;	// �������� ����
	BYTE subcode;	// ���� �������� ����

} PBMSG_HEAD2, * LPPBMSG_HEAD2;

//////////////////////////////////////////////////////////////////////////
// [ĳ���� ������ ����] 
//////////////////////////////////////////////////////////////////////////

#pragma pack(1)

typedef struct _CASHSHOP_ITEMLIST
{
	DWORD				s_dwItemGuid;						// �Ǹ� ������ȣ 1
	BYTE				s_btCategoryCode;					// �� �ڵ� 1
	BYTE				s_btItemDuration;					// ������ (����)
	BYTE				s_btItemSaleRatio;				    // ���η� 1
	WORD				s_wItemPrice;						// ���� 1
	BYTE				s_btSpecialOption;				    // Ư�� �ɼ� (�ű�, ��Ʈ ������) 1
	BYTE				s_btItemInfo[ITEM_BUFFER_SIZE];	    // ������ ������ Ŭ���̾�Ʈ�� ���� �� 7 ����Ʈ �������� ��ȯ
	DWORD				s_itemTime;							// �Ⱓ�� ������ ������ �־���. ������ 255 �ۿ� �� ��..--;;;;

	_CASHSHOP_ITEMLIST() : s_dwItemGuid(0), s_btCategoryCode(0),
		                   s_btItemSaleRatio(0), s_wItemPrice(0),
						   s_btSpecialOption(0), s_itemTime(0)
	
	{
		for( int i = 0; i < ITEM_BUFFER_SIZE; ++i )
		{
			s_btItemInfo[i] = 0;
		}
	}

	// 16����Ʈ
} CASHSHOP_ITEMLIST, *LPCASHSHOP_ITEMLIST;

//////////////////////////////////////////////////////////////////////////
// [ĳ���� ���� ��û ���] 0xF5, 0x02
//////////////////////////////////////////////////////////////////////////

typedef struct _PMSG_ANS_CASHSHOPOPEN
{
	PBMSG_HEAD2			s_head;

	BYTE				s_btResult;				             // ĳ�� �� ���� ��û ��� ( 0:����, 1:�ٸ� �������̽� ��� ��, 2:ĳ������ ������ �� ����, 3:�غ���� ����, 4:��Ʈ��ũ ���� )
} PMSG_ANS_CASHSHOPOPEN, *LPPMSG_ANS_CASHSHOPOPEN;

//////////////////////////////////////////////////////////////////////////
// [ĳ�� ����Ʈ �ܷ� ��û ���] 0xF5, 0x04
//////////////////////////////////////////////////////////////////////////

typedef struct _PMSG_ANS_CASHPOINT
{
	PBMSG_HEAD2			s_head;
	int					s_iCashPoint;				              // ĳ�� �ܷ�
} PMSG_ANS_CASHPOINT, *LPPMSG_ANS_CASHPOINT;

//////////////////////////////////////////////////////////////////////////
// [ĳ�� ������ ����Ʈ ��û ���] 0xF5, 0x06
//////////////////////////////////////////////////////////////////////////

typedef struct _PMSG_ANS_CASHITEMLIST
{
	PBMSG_HEAD2						s_head;
	BYTE							s_btCategoryIndex;		  // ������ ����Ʈ ī�װ�
	BYTE							s_btPageIndex;			  // ������ �ε���
	BYTE							s_btItemCount;			  // �ش� �������� ������ ī��Ʈ
	CASHSHOP_ITEMLIST				s_ItemInfo[MAX_CASHITEM_LIST_PER_PAGE];	// ������ ����Ʈ (�� ������)
	// 151����Ʈ
} PMSG_ANS_CASHITEMLIST, *LPPMSG_ANS_CASHITEMLIST;

//////////////////////////////////////////////////////////////////////////
// [ĳ�� ������ ���� ��û ���] 0xF5, 0x08
//////////////////////////////////////////////////////////////////////////

typedef struct _PMSG_ANS_CASHITEM_BUY
{
	PBMSG_HEAD2						s_head;
	BYTE							s_btResult;				   // ������ ���� ���
	// 1:����, 0:ĳ�� �ܷ� ����, 2:��Ÿ ����
} PMSG_ANS_CASHITEM_BUY, *LPPMSG_ANS_CASHITEM_BUY;

#ifdef PSW_CHARACTER_CARD
//////////////////////////////////////////////////////////////////////////
// [���� ĳ�������� ����] 0xDE, 0x00
//////////////////////////////////////////////////////////////////////////
typedef struct _PMSG_ANS_ACCOUNTINFO
{
	PBMSG_HEAD2		s_head;
	BYTE			s_bSummoner;	// ��ȯ���� ĳ���� ī�� �̿� ��/��
} PMSG_ANS_ACCOUNTINFO, *LPPMSG_ANS_ACCOUNTINFO;
//////////////////////////////////////////////////////////////////////////
// [���� ĳ�������� ���� ���] 0xDE, 0x01
//////////////////////////////////////////////////////////////////////////
typedef struct _PMSG_ANS_SETACCOUNTINFO
{
	PBMSG_HEAD2	s_head;
	BYTE		s_bResult;
} PMSG_ANS_SETACCOUNTINFO, *LPPMSG_ANS_SETACCOUNTINFO;

#endif // PSW_CHARACTER_CARD

///////////////////////////////////////////////////////////////////////////
//Client Code[ ���� ī�װ� ]
///////////////////////////////////////////////////////////////////////////

typedef struct _SHOPCATEGORY
{
	int     s_ShopType;
	int		s_HighCategory;                                    // ���� ī�װ� ��ġ
	int		s_LowCategory;                                     // ���� ī�װ� ��ġ
	char	s_ButtonName[STRUCTSMEMBERNAME];                   // ��ư �̸�

	_SHOPCATEGORY() : s_ShopType( -1 ), s_HighCategory( -1 ), s_LowCategory( -1 )
	{
		memset( &s_ButtonName, 0, sizeof(char)*STRUCTSMEMBERNAME );
	}
} SHOPCATEGORY;

typedef struct _SHOPCATEGORY_UNICODE
{
	int     s_ShopType;
	int		s_HighCategory;                                    // ���� ī�װ� ��ġ
	int		s_LowCategory;                                     // ���� ī�װ� ��ġ
	wchar_t	s_ButtonName[STRUCTSMEMBERNAME];                   // ��ư �̸�

	_SHOPCATEGORY_UNICODE() : s_ShopType( -1 ), s_HighCategory( -1 ), s_LowCategory( -1 )
	{
		memset( &s_ButtonName, 0, sizeof(wchar_t)*STRUCTSMEMBERNAME );
	}
} SHOPCATEGORY_UNICODE;




///////////////////////////////////////////////////////////////////////////
//Client Code[ ���� ������ ]
///////////////////////////////////////////////////////////////////////////

typedef struct _SHOPCATEGORYITEM
{
	WORD    s_bShoplistCode;     // ���� ���� :      ( 0 ) �Ϲ� ����, ( 1 ) �κ� ����ȭ ����
	WORD	s_HighCategory;	     // ���� ī�װ� ��ġ
	WORD	s_LowCategory;       // ���� ī�װ� ��ġ

	WORD	s_bItemCodeType;     // ������ ���� Ÿ��  MAX_ITEM_TYPE  = 16��
	WORD	s_bItemCodeIndex;    // ������ ���� Ÿ��  MAX_ITEM_INDEX = 512��

	WORD	s_bItemCode;		 // ������ �ڵ�	( ShopServer���� ������ )
	WORD	s_bItemCodeLevel;    // ������ ����
	WORD	s_btAddOption;       // �Ϲ� �ɼ�
	WORD	s_btExOption;        // ���� �ɼ�

	WORD    s_wNeedMoney;

	_SHOPCATEGORYITEM() : s_bShoplistCode(-1), s_HighCategory(-1), s_LowCategory(-1), s_bItemCode( -1 ), s_bItemCodeType(-1), s_bItemCodeIndex(-1),
					     s_bItemCodeLevel(-1), s_btAddOption(-1), s_btExOption(-1), s_wNeedMoney(-1) {}
} SHOPCATEGORYITEM;

typedef struct _MESSAGEBOXHANDLER
{
    virtual ~_MESSAGEBOXHANDLER() = 0{}
    virtual void OnMessageBox_OK( int id ){}
    virtual void OnMessageBox_YES( int id ){}
    virtual void OnMessageBox_NO( int id ){}
    virtual void OnMessageBox_CANCEL( int id ){}
} MESSAGEBOXHANDLER;

typedef struct _MESSAGEBOXDATA 
{
	weak_ptr<MESSAGEBOXHANDLER>		s_handler;
	eMessageBoxType					s_type;
	list<string>					s_message;
	int								s_id;
	bool							s_bModal;

	_MESSAGEBOXDATA() : s_type(), s_bModal( false ), s_id( -1 ) {}
} MESSAGEBOXDATA;

typedef list<SHOPCATEGORY>										ShopCategory_List;
typedef list<SHOPCATEGORY_UNICODE>								ShopCategory_Unicode_List;
typedef list<SHOPCATEGORYITEM>									ShopCategoryItem_List;
typedef list<CASHSHOP_ITEMLIST>									ShopCashShopItem_List;

typedef map< eHighCategoryType, ShopCategory_List >				ShopCategory_Map;
typedef map< eHighCategoryType, ShopCategory_Unicode_List >     ShopCategory_Unicode_Map;
typedef map< WORD, SHOPCATEGORYITEM >							ShopCategoryItem_Map;
typedef map< WORD, SHOPCATEGORYITEM >							ShopMyCartItem_Map;
typedef map< WORD, CASHSHOP_ITEMLIST >							ChashShopMyCartItem_Map;;

typedef map< WORD, ShopCategoryItem_List >						ShopPageItem_Map;
typedef map< eLowCategoryType, ShopPageItem_Map >				ShopItem_Map;

typedef map< WORD, ShopCashShopItem_List >						ShopChashShopPageItem_Map;
typedef map< eLowCategoryType, ShopChashShopPageItem_Map >		ShopChashShopItem_Map;

#pragma pack()

#endif //NEW_STRUCTS
