// Base.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <afx.h>
#include "omaha\base\file_ver.h"

using namespace omaha;

void test_file_ver()
{
	FileVer ver;
	if ( !ver.Open(L"Base.exe") )
		OutputDebugString(_T("Open Base.exe faild"));
	TRACE(_T("FileDescription: %s "), ver.GetFileDescription());
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

