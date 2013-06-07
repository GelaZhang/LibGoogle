// Base.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "omaha/base/encrypt.h"
#include "omaha/base/md5.h"
#include "omaha/base/firewall_product_detection.h"
#include "omaha/base/processor_type.h"
using namespace omaha;
using namespace omaha::encrypt;

void EncryptTest()
{
	char key[] = "right key";
	char data[] = "For Encrypt";
	std::vector<uint8> data_out;
	std::vector<uint8> data_D;
	if ( S_OK == EncryptData(key, strlen(key), data, strlen(data), &data_out) )
	{
		printf(" Encrypt success\n");
	}

	if ( S_OK == DecryptData(key, strlen(key), &data_out[0], data_out.size()* sizeof(uint8), &data_D) )
	{
		printf("DecryptData success\n");
		char data_str[64];
		memset(data_str, 0, 64);
		memcpy(data_str, &data_D[0], data_D.size()* sizeof(uint8));
		if ( strcmp(data, data_str) == 0 )
			printf("DecryptData done");
	}

	char wrong_key[] = "wrong key";
	if ( S_OK == DecryptData(wrong_key, strlen(wrong_key), &data_out[0], data_out.size()* sizeof(uint8), &data_D) )
	{
		printf("DecryptData success\n");
		char data_str[64];
		memset(data_str, 0, 64);
		memcpy(data_str, &data_D[0], data_D.size()* sizeof(uint8));
		if ( strcmp(data, data_str) == 0 )
			printf("DecryptData done\n");
	}
	else
	{
		printf("Wrong key decrypt faild\n");
	}

}

void CheckMD5 (char *string, TCHAR *correct_digest) {

	omaha::MD5_CTX context;
	omaha::MD5Init (&context);
	omaha::MD5Update (&context, (unsigned char *)string, strlen (string));
	unsigned char digest[16];
	omaha::MD5Final (digest, &context);

	const DWORD digest_len = 32+1;
	TCHAR digest_string[digest_len];
	digest_string[31] = '\0';
	digest_string[0] = '\0';

	for (int i = 0; i < 16; i++) {
		//SafeStrCat (digest_string, SPRINTF (_T("%02x"), digest[i]), digest_len);
		swprintf(digest_string + i * 2, L"%02x", digest[i]);
	}

	if (wcscmp(digest_string, correct_digest) == 0)
		printf("md5 success");
	else
		printf("md5 faild");
}

void TestFireWall() {
	::CoInitialize(NULL);
	CString name, version;
	HRESULT hr = firewall_detection::Detect(&name, &version);
	if (SUCCEEDED(hr)) {
		_tprintf(_T("name:%s, version: %s"), name.GetBuffer(), version.GetBuffer());
	}
	else
		_tprintf(_T("detect fail"));
	::CoUninitialize();
}
int _tmain(int argc, _TCHAR* argv[])
{
	if ( IsIntelProcessor() )
		printf("intel cpu\n");
	else
		printf("no intel\n");
	TestFireWall();
	EncryptTest();
	CheckMD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890", _T("57edf4a22be3c955ac49da2e2107b67a"));
	getchar();
	return 0;
}

