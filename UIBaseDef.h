//*****************************************************************************
// File: UIBaseDef.h
//
// Desc: UI �⺻ ���� ����.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#ifndef _UI_BASE_DEF_H_
#define _UI_BASE_DEF_H_

#include "UsefulDef.h"

// ���� ����.
// DWORD Ÿ��.
#define	CLRDW_WHITE			ARGB(255, 255, 255, 255)// ���.
#define CLRDW_BR_GRAY		ARGB(255, 226, 226, 226)// ���� ȸ��.
#define CLRDW_GRAY			ARGB(255, 119, 119, 119)// ȸ��.
#define CLRDW_YELLOW		ARGB(255, 255, 255, 121)// �����.
#define CLRDW_BR_YELLOW		ARGB(255, 255, 238, 193)// ���� �����.
#define CLRDW_BR_ORANGE		ARGB(255, 255, 217, 39)	// ���� ��������.
#define CLRDW_ORANGE		ARGB(255, 255, 180, 0)	// ��������.
#define CLRDW_DARKYELLOW	ARGB(255, 255, 255, 0)	// ���� �����
// COLORREF Ÿ��.
#define	CLRREF_WHITE		RGB(240, 240, 240)		// ���.
#define	CLRREF_BR_GRAY		RGB(210, 210, 210)		// ���� ȸ��.
#define	CLRREF_GRAY			RGB(127, 127, 127)		// ȸ��.
#define	CLRREF_BLACK		RGB(  0,   0,   0)		// ������.
#define	CLRREF_RED			RGB(252,  60,  60)		// ������.
#define	CLRREF_BR_RED		RGB(252, 128, 128)		// ���� ������.
#define	CLRREF_ORANGE		RGB(220, 170, 100)		// ��Ȳ��.
#define	CLRREF_YELLOW		RGB(210, 210, 100)		// �����.
#define	CLRREF_BR_YELLOW	RGB(240, 240, 170)		// ���� �����.
#define	CLRREF_GREEN		RGB(100, 230, 100)		// �ʷϻ�.
#define	CLRREF_DK_BLUE		RGB( 50,  40, 255)		// ��ο� �Ķ���.
#define	CLRREF_BLUE			RGB(101,  89, 255)		// �Ķ���.
#define	CLRREF_BR_BLUE		RGB(168, 148, 255)		// ���� �Ķ���.
#define	CLRREF_VIOLET		RGB(210, 100, 210)		// �����.
#define	CLRREF_BR_OCHER		RGB(250, 225, 200)		// ���� Ȳ���.

// ���ؽ� ��ġ. (�»�, ����, ����, ���, �ִ밪. GL_TRIANGLE_FAN ���� ����.)
enum VERTEX_POS { LT, LB, RB, RT, POS_MAX };
/// ������ �Ű� ����.
enum CHANGE_PRAM { X = 1, Y, XY };

struct SScrCoord	// ��ũ�� ��ǥ.
{
	float	fX, fY;
};

struct STexCoord	// �ؽ�ó ��ǥ.
{
	float	fTU, fTV;
};

struct SFrameCoord	// �ý�ó ���� ������ ���� �ȼ� ��ǥ.
{
	int		nX, nY;
};

struct SImgInfo		// �̹��� ����.
{
	int		nTexID;				// �ؽ�ó ID.
	int		nX, nY;				// �ؽ�ó ���� �̹��� ��ġ.
	int		nWidth, nHeight;	// �ؽ�ó ���� �̹��� ũ��.
};

#endif // _UI_BASE_DEF_H_