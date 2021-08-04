#ifndef __GLUTILS_H__
#define __GLUTILS_H__


///////////////////////////////////////////////////////////////////////////////////////////
// GLUtils.h : ���̴� Ÿ�� ����.
///////////////////////////////////////////////////////////////////////////////////////////

void	InitExtension();				// Driver�� �����ϴ� ShaderType ����
bool	IsHighVersion();				// VertexShader
bool	IsHighestVersion();				// FragmentShader
bool	IsLowVersion();					// No Shader
void	SetGeneralType(unsigned char t);// Shader Render Type ����

///////////////////////////////////////////////////////////////////////////////////////////
// ���̴� Ÿ�� ����.
///////////////////////////////////////////////////////////////////////////////////////////
enum _GP_DRIVER_INFO
{
	GPVER_LOW,							// 1.1
	GPVER_MIDDLE,						// 1.1 �̻�, Vertex Blend, Complied Array
	GPVER_HIGH,							// VBO, vertex prog
	GPVER_HIGHEST,						// VBO, vertex, fragment prog					
};
extern unsigned char g_iEnumDriverType;	// Driver�� �����ϴ� Shader Type 
extern unsigned char g_iUseDriverType;	// ���� VertexShader �Ǵ� PixelShader ����

extern float g_posLight[3];				// ���� ���� ��ġ
extern float g_vAngleLight[3];			// ���� ���� ����

//WANI_COMMON ������ �ʿ���...
// �ν�Ʈ ����
//#include "WinMain.h"
//#include <gl/gl.h>
//#include <gl/glu.h>
//#include "glext.h"
//#include "wglext.h"
//#include "glprocs.h"


#endif __GLUTILS_H__