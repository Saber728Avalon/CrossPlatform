#include "DebugOut.h"
#if _MSC_VER < 1800 //vs2013
	#include "CMutex.h"
#else
	#include <mutex>
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif

std::mutex g_mutexDebugOut;

void DebugOutInfo(std::string strInfo)
{
	g_mutexDebugOut.lock();
#if defined(_WIN32) || defined(_WIN64)
	OutputDebugStringA(strInfo.c_str());
#else
	FILE *pDebugInfoFile = NULL;
	std::string strFilePath;
	#if defined(__APPLE__)
		strFilePath = "/tmp/debug.txt";

	#elif defined(__linux__)
		strFilePath = "/tmp/debug.txt";
	#elif defined(__ANDROID__)
		strFilePath = "/sdcard/debug.txt";
	#else
		#error "Not Support!"
	#endif
	pDebugInfoFile = fopen(strFilePath.c_str(), "ab+");

	//优先访问tmp目录	
	if (NULL == pDebugInfoFile)//当前目录不能访问
	{
		//访问当前目录
		char chBuf[1024] = { 0 };
		
		getcwd(chBuf, 1024);
		strFilePath += (chBuf);
		strFilePath = strFilePath + "/tmp";
		int nRet = mkdir(strFilePath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

		strFilePath = strFilePath + "/" + "debug.txt";
		pDebugInfoFile = fopen(strFilePath.c_str(), "ab+");
	}

	if (NULL != pDebugInfoFile)
	{
		fwrite(strInfo.c_str(), 1, strInfo.length(), pDebugInfoFile);
		fflush(pDebugInfoFile);
		fclose(pDebugInfoFile);
	}
#endif

	g_mutexDebugOut.unlock();
	return;
}




wchar_t g_wchBuf[10 * 1024];
char g_chBuf[10 * 1024];

//int  MywPrintf(const wchar_t *_Format, ...)
//{
//	int ret = -1;
//	try
//	{
//		va_list _Arglist;
//		va_start(_Arglist, _Format);
//		int _Ret = _vswprintf(g_wchBuf, _Format, _Arglist);
//		va_end(_Arglist);
//	}
//	catch (...)
//	{
//	}
//
//
//	DebugOutInfoW(g_wchBuf);
//	return ret;
//}


int  MyPrintf(const char *_Format, ...)
{
	int ret = -1;
	try
	{
		va_list _Arglist;
		va_start(_Arglist, _Format);
		int _Ret = vsprintf(g_chBuf, _Format, _Arglist);
		va_end(_Arglist);
	}
	catch (...)
	{
	}


	DebugOutInfo(g_chBuf);
	return ret;
}

