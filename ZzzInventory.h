#ifndef __ZZZINVENTORY_H__
#define __ZZZINVENTORY_H__

const enum _COLUMN_TYPE
{
	_COLUMN_TYPE_LEVEL = 0, 
	_COLUMN_TYPE_CAN_EQUIP,
	_COLUMN_TYPE_ATTMIN,
	_COLUMN_TYPE_ATTMAX,
	_COLUMN_TYPE_MAGIC,
#ifdef CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
	_COLUMN_TYPE_CURSE,		// ���ַ�
#endif // CSK_FIX_WOPS_K28219_ITEM_EXPLANATION
    _COLUMN_TYPE_PET_ATTACK, 
	_COLUMN_TYPE_DEFENCE,
	_COLUMN_TYPE_DEFRATE,
	_COLUMN_TYPE_REQSTR,
	_COLUMN_TYPE_REQDEX,
	_COLUMN_TYPE_REQENG,
	_COLUMN_TYPE_A_SET,
	_COLUMN_TYPE_B_SET,
	_COLUMN_TYPE_REQCHA,
	_COLUMN_TYPE_REQVIT,
	_COLUMN_TYPE_REQNLV
};

const enum ITEMSETOPTION
{
	eITEM_PERSONALSHOP = 0,
	eITEM_STORE,
	eITEM_TRADE,
	eITEM_DROP,
	eITEM_SELL,
	eITEM_REPAIR,
	eITEM_END
};

struct sItemAct 
{
	int		s_nItemIndex;
	bool	s_bType[eITEM_END];
};

const enum SKILL_TOOLTIP_RENDER_POINT
{
	STRP_NONE = 0,
	STRP_TOPLEFT,
	STRP_TOPCENTER,
	STRP_TOPRIGHT,
	STRP_LEFTCENTER,
	STRP_CENTER,
	STRP_RIGHTCENTER,
	STRP_BOTTOMLEFT,
	STRP_BOTTOMCENTER,
	STRP_BOOTOMRIGHT
};

// ��������

extern int		g_nTaxRate;
extern int		g_nChaosTaxRate;

extern const int iMaxLevel;

///////////////////////////////////////////////////////////////////////////////
// guild
///////////////////////////////////////////////////////////////////////////////

extern char         g_GuildNotice[3][128];
extern GUILD_LIST_t GuildList[MAX_GUILDS];
extern int          g_nGuildMemberCount;
extern int          GuildListPage;
extern MARK_t		GuildMark[MAX_MARKS];
extern int			SelectMarkColor;
extern int			GuildPlayerKey;
extern int			GuildNumber;
extern int			GuildTotalScore;

extern int AllRepairGold;

//////////////////////////////////////////////////////////////////////////
// text ����
//////////////////////////////////////////////////////////////////////////
extern char TextList[30][100];
extern int TextListColor[30];
extern int TextBold[30];
extern SIZE Size[30];

///////////////////////////////////////////////////////////////////////////////
// party
///////////////////////////////////////////////////////////////////////////////

extern PARTY_t Party[MAX_PARTYS];
extern int     PartyKey;
extern int     PartyNumber;

///////////////////////////////////////////////////////////////////////////////
// inventory
///////////////////////////////////////////////////////////////////////////////

extern ITEM Inventory         [MAX_INVENTORY];
extern ITEM ShopInventory     [MAX_SHOP_INVENTORY];
extern int  InventoryType;
extern ITEM g_PersonalShopInven[MAX_PERSONALSHOP_INVEN];
extern ITEM g_PersonalShopBackup[MAX_PERSONALSHOP_INVEN];
extern bool g_bEnablePersonalShop;
extern int g_iPShopWndType;
extern POINT g_ptPersonalShop;
extern int g_iPersonalShopMsgType;
extern char g_szPersonalShopTitle[64];
extern CHARACTER g_PersonalShopSeller;

#ifndef YDG_ADD_NEW_DUEL_SYSTEM		// �����Ҷ� �����ؾ� ��
#ifdef DUEL_SYSTEM
extern bool g_bEnableDuel;
extern int g_iDuelPlayerIndex;
extern char g_szDuelPlayerID[24];
extern int g_iMyPlayerScore;
extern int g_iDuelPlayerScore;
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM	// �����Ҷ� �����ؾ� ��
extern bool EnableRenderInventory;
extern int  g_bEventChipDialogEnable;
extern int  g_shEventChipCount;
extern short g_shMutoNumber[3];
extern bool g_bServerDivisionAccept;

#ifdef SCRATCH_TICKET
extern char g_strGiftName[64];
#endif //SCRATCH_TICKET

extern bool RepairShop;
extern int  RepairEnable;
extern int AskYesOrNo; //  Ȯ��â(1-�ȱ�, 2-ī���� ����)
#ifdef KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
extern char OkYesOrNo;		//  Ȯ��â�� Ȯ��
#else // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX
extern BYTE OkYesOrNo;    //  Ȯ��â�� Ȯ��
#endif // KWAK_FIX_COMPILE_LEVEL4_WARNING_EX

extern int  SommonTable[];
extern int  StorageGoldFlag;
extern ITEM *SrcInventory;
extern int  SrcInventoryIndex;
extern int  DstInventoryIndex;
extern int  CheckSkill;
extern ITEM *CheckInventory;
extern ITEM *CheckInvenParent;
extern BYTE BuyItem[4];
extern int  EnableUse;
extern bool EquipmentItem;
extern BYTE g_byItemUseType;	//: ���� ��� �뵵 0x00 ���Ȼ��� 0x01 ���Ȱ���
extern char	g_lpszKeyPadInput[2][MAX_KEYPADINPUT + 1];

//////////////////////////////////////////////////////////////////////////
//  ī���� ����.
//////////////////////////////////////////////////////////////////////////

const char* GetMapName( int iMap);
#ifdef ASG_ADD_GENS_SYSTEM
bool IsStrifeMap(int nMapIndex);
#endif	// ASG_ADD_GENS_SYSTEM
void CreateShiny(OBJECT *o);
void ClearInventory();
void CreateShopInventory();
bool CheckEmptyInventory(ITEM *Inv,int InvWidth,int InvHeight);
#ifdef  AUTO_CHANGE_ITEM
void AutoEquipmentChange( int sx, int sy, ITEM* Inv, int InvWidth, int InvHeight );
#endif // AUTO_CHANGE_ITEM

int CompareItem(ITEM item1, ITEM item2);
#ifdef KJH_MOD_BTS191_GOLD_FLOATING_NUMBER
void ConvertGold(double dGold, unicode::t_char* szText, int iDecimals = 0);
#else // KJH_MOD_BTS191_GOLD_FLOATING_NUMBER
void ConvertGold(DWORD Gold,unicode::t_char* Text);
#endif // KJH_MOD_BTS191_GOLD_FLOATING_NUMBER
#ifdef YDG_FIX_CATLE_MONEY_INT64_TYPE_CRASH
void ConvertGold64(__int64 Gold,unicode::t_char* Text);
#endif	// YDG_FIX_CATLE_MONEY_INT64_TYPE_CRASH
void ConvertTaxGold(DWORD Gold,char *Text);
void ConvertChaosTaxGold(DWORD Gold,char *Text);
int  ConvertRepairGold(int Gold,int Durability, int MaxDurability, short Type, char *Text);
void RepairAllGold ( void );
WORD calcMaxDurability ( const ITEM* ip, ITEM_ATTRIBUTE *p, int Level );
void RenderTipTextList(const int sx, const int sy, int TextNum, int Tab, 
						int iSort = RT3_SORT_CENTER, int iRenderPoint = STRP_NONE, BOOL bUseBG = TRUE);
// ������ ��밡�ɿ��� �Ǵ�
bool IsCanUseItem();
// �ŷ���û ���ɻ��� �Ǵ�
bool IsCanTrade();
//  Party.
void InitPartyList ();
void OpenPersonalShop(int iType);
void ClosePersonalShop();
void ClearPersonalShop();
bool IsExistUndecidedPrice();
void OpenPersonalShopMsgWnd(int iMsgType);
bool IsCorrectShopTitle(const char* szShopTitle);

#ifndef YDG_ADD_NEW_DUEL_SYSTEM		// �����Ҷ� �����ؾ� ��
#ifdef DUEL_SYSTEM
void ClearDuelWindow();
#endif // DUEL_SYSTEM
#endif	// YDG_ADD_NEW_DUEL_SYSTEM	// �����Ҷ� �����ؾ� ��

void CreateGuildMark( int nMarkIndex, bool blend=true );
void RenderGuildColor(float x,float y,int SizeX,int SizeY,int Index);
void CreateCastleMark ( int Type, BYTE* buffer=NULL, bool blend=true );

// �������� ������ �ϴ� �Լ�
void RenderItem3D(float sx,float sy,float Width,float Height,int Type,int Level,int Option1,int ExtOption,bool PickUp=false);
void RenderObjectScreen(int Type,int ItemLevel,int Option1,int ExtOption,vec3_t Target,int Select,bool PickUp);
//	ĳ������ ���ݷ��� ����Ѵ�.
bool GetAttackDamage ( int* iMinDamage, int* iMaxDamage );
void GetItemName ( int iType, int iLevel, char* Text );
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
void GetSpecialOptionText ( int Type, char* Text, WORD Option, BYTE Value, int iMana );
#else //PBG_ADD_NEWCHAR_MONK_SKILL
void GetSpecialOptionText ( int Type, char* Text, BYTE Option, BYTE Value, int iMana );
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
#ifdef ASG_ADD_NEW_QUEST_SYSTEM
void RenderItemInfo(int sx,int sy,ITEM *ip,bool Sell, int Inventype = 0, bool bItemTextListBoxUse = false);
#else	// ASG_ADD_NEW_QUEST_SYSTEM
void RenderItemInfo(int sx,int sy,ITEM *ip,bool Sell, int Inventype = 0);
#endif	// ASG_ADD_NEW_QUEST_SYSTEM
void RenderRepairInfo(int sz, int sy, ITEM* ip, bool Sell);
void RenderSkillInfo(int sx,int sy,int Type,int SkillNum = 0, int iRenderPoint = STRP_NONE);
void RequireClass(ITEM_ATTRIBUTE *p);
bool IsRequireClassRenderItem(const short sType);
unsigned int getGoldColor ( DWORD Gold );

#if defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
// �κ�����ȭ ������ ǰ��
bool IsPartChargeItem(ITEM* pItem);
#endif //defined(PSW_PARTCHARGE_ITEM1) || defined(LDK_ADD_CASHSHOP_FUNC)
// �������� ǰ�� ����Ʈ ����
bool IsHighValueItem(ITEM* pItem);
// ���λ��� �ŷ����� ������ ǰ��
bool IsPersonalShopBan(ITEM* pItem);
// ��ȯ �ŷ����� ������ ǰ��
bool IsTradeBan(ITEM* pItem);
// ������ ���� ������ ǰ��
bool IsDropBan(ITEM* pItem);
#ifdef LEM_FIX_ITEMSET_FROMJAPAN	// IsItemSet_FromJapan�Լ� ��� ���� [lem_2010.8.19]
int IsItemSet_FromJapan( ITEM* _pItem, int _nType );
#endif	// LEM_FIX_ITEMSET_FROMJAPAN [lem_2010.8.19]
// ����â������ ���� ������ ǰ��
bool IsStoreBan(ITEM* pItem);
// �����Ǹ� ���� ������ ǰ��
bool IsSellingBan(ITEM* pItem);
// ���� ���� ������ ǰ��
bool IsRepairBan(ITEM* pItem);
// ���� ������ ǰ��
bool IsWingItem(ITEM* pItem);

void ComputeItemInfo(int iHelpItem);
void RenderHelpCategory(int iColumnType, int Pos_x, int Pos_y);
void RenderHelpLine(int iColumnType, const char * pPrintStyle, int & TabSpace, const char * pGapText = NULL, int Pos_y = 0, int iType=0);
void RenderItemName(int i,OBJECT *o,int ItemLevel,int ItemOption,int ItemExtOption,bool Sort);

#ifdef CSK_FREE_TICKET
BYTE CaculateFreeTicketLevel(int iType);
#endif //CSK_FREE_TICKET

#ifdef NEW_USER_INTERFACE_SHELL
const bool ChangeCodeItem( ITEM* ip, BYTE* itemdata );
const int ChangeData( ITEM* tooltipitem, const CASHSHOP_ITEMLIST& indata, vector<string>& outtextdata, vector<DWORD>& outcolordata );
#endif //NEW_USER_INTERFACE_SHELL

#ifdef LEM_ADD_LUCKYITEM
bool Check_ItemAction( ITEM* _pItem, ITEMSETOPTION _eAction, bool _bType = false );
bool Check_LuckyItem( int _nIndex, int _nType = 0 );
sItemAct Set_ItemActOption( int _nIndex, int _nOption );
#endif // LEM_ADD_LUCKYITEM
#ifdef KJH_FIX_SELL_LUCKYITEM
bool IsLuckySetItem( int iType );
#endif // KJH_FIX_SELL_LUCKYITEM

#endif //__ZZZINVENTORY_H__
