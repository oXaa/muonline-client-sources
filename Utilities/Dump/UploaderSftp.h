#pragma once 

#include "Uploader.h"

/**
 * @class CUploaderSftp 
 *
 * SFTP ������ �����ϱ� ���� Ŭ�����̴�. 
 */
class CUploaderSftp : public CUploader
{
public:
	CUploaderSftp(LPCTSTR szUrl, int nPort, LPCTSTR szId, LPCTSTR szPassword, int nUploadCount);
	~CUploaderSftp();

	/**
	 * ���� ������ ���� ���Ϸ� �����Ѵ�.
	 * 
	 * ���ϸ��� ��Ʈ �������� �����Ǿ�� �Ѵ�. ����/����Ʈ ��ο� ���� �׷���.
	 * ��) UploadFTP( "c:\\Mu\\dump.dmp", "/Mu/crash_ABFFAABCDEDD.dmp" );
	 *
	 * ��ü ��θ� ����ϸ� ȯ���� Ÿ�� �ʱ� ������ ���� �������̴�. 
	 *
	 * ���� ������ ������ ���������� ������. ����, �ߺ����� �ʵ��� ���ϸ� ������ �ؾ� �� 
	 * crash_MAC_TIME.dmp �������� ����� �� ���� �� (IP�� ���� �����Ǹ� �ߺ� ����. ���� �� ī�� �ּҰ� ����)
	 *
	 * TODO: ���� ���� ������ �ݿ��Ͽ� CrashHandler.cpp ������ ��. 
	 */
	int	UploadFTP(LPCTSTR szLocalFile, LPCTSTR szServerFile);
};


	
