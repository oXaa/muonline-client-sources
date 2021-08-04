#include "stdafx.h"

#ifdef MR0

//////////////////////////////////////////////////////////////////////////
// 
// GLUtils.cpp : ���̴� ���������� ����ϴ� Opengl Extension ���� �Լ��� 
//
//////////////////////////////////////////////////////////////////////////

#include "GLUtils.h"


BYTE g_iEnumDriverType = GPVER_LOW;						// Driver�� �����ϴ� ���̴� Ÿ�� ����.
BYTE g_iUseDriverType = GPVER_LOW;						// �ܺο��� ������ ���̴� Ÿ�� ����.
float g_posLight[3] = { 5000.f, -5000.f, 10000.f };		// ����Ʈ ��ġ
float g_vAngleLight[3] = { 0.f, 0.f, 0.f };				// ����Ʈ ������


///////////////////////////////////////////////////////////////////////////////////////////
// OpenGL�� ���� Driver�� �����Ǵ� GL ��ɵ鿡�� �ܺο��� ã���� �ϴ� ����� �ִ��� ã���ϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
bool	InStr(char* searchStr, char* str)
{
	char* extension = NULL;
	char* endofStr = NULL;
	int idx = 0;
	endofStr = str + strlen(str);
	while(str<endofStr)
	{
		idx = strcspn(str, " ");
		if( ((int)strlen(searchStr) == idx) && (strncmp(searchStr, str, idx) == 0) )
		{
			return true;
		}
		str += (idx+1);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���� Driver�� �����ϴ� Shader Type Version�� ���� ���̴� Ÿ���� ���� �մϴ�.
///////////////////////////////////////////////////////////////////////////////////////////
void	InitExtension()
{
	char* str_extension = (char* )glGetString(GL_EXTENSIONS);
	if(!str_extension) return;
	if(InStr("GL_ARB_vertex_buffer_object", str_extension) &&
		InStr("GL_ARB_vertex_program",str_extension))
	{
		if(InStr("GL_ARB_fragment_program",str_extension))
			g_iEnumDriverType = GPVER_HIGHEST;
		else
			g_iEnumDriverType = GPVER_HIGH;
	}
	else if(InStr("GL_EXT_compiled_vertex_array", str_extension) &&
		InStr("GL_ARB_vertex_blend", str_extension) &&
		InStr("GL_ARB_multitexture", str_extension) &&
		InStr("GL_ARB_texture_env_combine", str_extension))
	{
		g_iEnumDriverType = GPVER_MIDDLE;
	}
	else
		g_iEnumDriverType = GPVER_LOW;
	
	g_iUseDriverType = g_iEnumDriverType;
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���� ���̴� Ÿ�� ���� ���� ��ȯ.
///////////////////////////////////////////////////////////////////////////////////////////
bool IsHighVersion()
{
	return (g_iUseDriverType >= GPVER_HIGH); 
}
bool IsLowVersion()
{ 
	return (g_iUseDriverType == GPVER_LOW); 
}
bool IsHighestVersion()
{
	return (g_iUseDriverType == GPVER_HIGHEST);
}

///////////////////////////////////////////////////////////////////////////////////////////
// ���� ���̴� Ÿ�� ������ ���� ����.
///////////////////////////////////////////////////////////////////////////////////////////
void SetGeneralType(unsigned char t)
{
	if(t > g_iEnumDriverType)
	{
		g_iUseDriverType = g_iEnumDriverType;
		return;
	}

	g_iUseDriverType = t;
}


#endif //MR0