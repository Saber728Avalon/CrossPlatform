#include <stdio.h>
#include <iostream>
#include <LoadLib.h>
#include <DebugOut.h>
#include <DuanAssert.h>
#include <DuanThread.h>
#include <FileUtils.h>
#include <EncodeChange.h>
#include "StringOper.h"
#include "NumberOper.h"
#include "BaseFactory.h"
#include "Any.h"
#include "SafeSTL.h"
#include "DuanAssert.h"

#include "endian.h"

#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif

typedef void(*pCalllTest)();

void TestLoadLib()
{
	char chBuf[1024] = { 0 };
	getcwd(chBuf, 256);
	std::string strPath = chBuf;

#ifdef _WIN32
	strPath = strPath + "/" + "TestLib";
	strPath = strPath + ".dll";
#elif __linux
	strPath = strPath + "/" + "libTestLib";
	strPath = strPath + ".so";
#elif __APPLE__
	strPath = strPath + "/" + "libTestLib";
	strPath = strPath + ".dylib";
#else
#error "not support"
#endif

#ifdef _WIN32
	LOAD_LIB_HANDLE module = PW_LoadLib(strPath.c_str(), LOAD_FLAGS::CHARACTER_ASCII);
#else
	LOAD_LIB_HANDLE module = PW_LoadLib(strPath.c_str(), LOAD_FLAGS::PR_LD_NOW);
#endif
	assert(NULL != module);
	pCalllTest func = (pCalllTest)PW_FindSymbolInLib(module, "CalllTest");
	func();

	PW_UnloadLib(module);
}

void TestDebugOut()
{
	DebugOut("-------info------------");
}

void TestThread()
{

}

void TestFile()
{
	FileUtils::CreateDirs("D:/crt11/11/122/33/44/55");
	FileUtils::FileCopy("D:/crt/ClientConfigUI70U.dll", "D:/crt/cryptocme2.dll0000");
	FileUtils::DirCopy("D:/crt", "D:/crt11");
}

void GBKUf8()
{
	//gbk to utf8
	char pszBuf[] = { 0xB4, 0xBA, 0xC3, 0xDF, 0xb2, 0xbb, 0xBE, 0xF5, 0xCF, 0xFE, 0x0, 0x0 };
	std::string strutf8 = CodeTransformUtility::GetUtf8Code(pszBuf, sizeof(pszBuf));

	std::string strGBK = CodeTransformUtility::GetGbkCode((char *)strutf8.data(), strutf8.size());
	return;
}

void TestString()
{
	std::wstring strSrc1 = L"1234567890";
	std::wstring strSrc2 = L"456";
	std::wstring strSrc3 = L"XXXXXXXXXXXXXXXX";
	std::wstring strRst = StringOper::ReplaceUni(strSrc1, strSrc2, strSrc3);
	return;

}

void TestNo()
{
	std::string str = NumberOper::Int32To16Str(1234);
	std::string str1 = NumberOper::Int64ToStr(1234);

	uint32_t nxx = NumberOper::StrToInt32("12345");
	uint64_t nxxxx1 = NumberOper::StrToInt64("12345678");


	uint32_t ntt = NumberOper::Str16ToUint32("0x12345678");

	uint32_t ntt2 = NumberOper::Str8ToInt32("012345678");
	return;
}

class TestXX
{
public :
	TestXX() { printf("TestXX()"); }

	TestXX(int) { printf("TestXX(int)"); }
	void Show() { printf("123145565\n"); }
};

void TestAny()
{
	TestXX test;
	duan::Any any(test);
	duan::Any_Cast<TestXX>(any).Show();

	std::vector<duan::Any> vectTmp;
	vectTmp.push_back(10);
	vectTmp.push_back(11.11);
	vectTmp.push_back(std::string("abcdefg"));
	vectTmp.push_back(TestXX(123));

	for (auto item : vectTmp)
	{
		printf( "%s \n", item.type().c_str());
	}
}



int main(int argc, char *argv[])
{
	//TestLoadLib();
	//TestDebugOut();
	//TestFile();
	//GBKUf8();
	//TestString();

	//TestFactory();
	//TestReflect();
	

	uint16_t x1 = 0x1234;
	uint32_t x2 = 0x12345678;
	uint64_t x3 = 0x123456789ABCDEF;

	uint16_t x4;
	x4 = htobe16(x1);
	x4 = be16toh(x1);
	x4 = le16toh(x1);
	x4 = htole16(x1);

	uint32_t x5;
	x5 = htobe32(x1);
	x5 = be32toh(x1);
	x5 = le32toh(x1);
	x5 = htole32(x1);

	uint64_t x6;
	x6 = htobe64(x3);
	x6 = be64toh(x3);
	x6 = le64toh(x3);
	x6 = htole64(x3);

	//TestNo();
	return 0;
}