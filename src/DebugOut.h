#pragma once
#include <iostream>

void DebugOutInfo(std::string strInfo);
//void DebugOutInfoW(std::wstring strInfo);

//int  MywPrintf(const wchar_t *pFormat, ...);

int  MyPrintf(const char *pFormat, ...);


#if !defined(NDEBUG)
	#define DebugOut(xxxx) DebugOutInfo(xxxx)
#else
	#define DebugOut(xxxx) DebugOutInfo(xxxx)
#endif