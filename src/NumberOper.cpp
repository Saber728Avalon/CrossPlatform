#include "NumberOper.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>

NumberOper::NumberOper()
{
}


std::string NumberOper::as_string(const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	int nLen = vsnprintf(nullptr, 0, fmt, vl);
	va_end(vl);

	std::string strBuf;
	strBuf.reserve(nLen + 2);
	strBuf.resize(nLen);//¨°¨°?a¡ã¨¹o?¨¢?¨°???\0
	if (strBuf.size() != nLen)
	{
		return std::string();
	}
	memset((void *)strBuf.data(), 0, (strBuf.size() + 2) * sizeof(char));

	va_start(vl, fmt);
	vsnprintf(&strBuf[0], nLen + 1, fmt, vl);
	va_end(vl);

	return strBuf;
}


std::wstring NumberOper::as_string(const NO_UNI_CHAR_KEYWORD *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	int nLen = vswprintf(nullptr, 0, fmt, vl);
	va_end(vl);

	std::wstring strBuf;
	strBuf.reserve(nLen + 2);
	strBuf.resize(nLen);
	if (strBuf.size() != nLen)
	{
		return std::wstring();
	}
	memset((void *)strBuf.data(), 0, (strBuf.size() + 2) * sizeof(NO_UNI_CHAR_KEYWORD));

	va_start(vl, fmt);
	vswprintf(&strBuf[0], nLen + 1, fmt, vl);
	va_end(vl);

	return strBuf;
}


NumberOper::~NumberOper()
{
}


std::string NumberOper::Int32ToStr(int32_t nNumber)
{
	return as_string("%d", nNumber);
}


std::string NumberOper::Int64ToStr(int64_t nNumber)
{
	return as_string("%lld", nNumber);
}


std::string NumberOper::Uint32ToStr(uint32_t unNumber)
{
	return as_string("%u", unNumber);
}

std::string NumberOper::Uint64ToStr(uint64_t un64Number)
{
	return as_string("%llu", un64Number);
}

std::string NumberOper::FloatToStr(float fFloat)
{
	return as_string("%f", fFloat);
}

std::string NumberOper::DoubleToStr(double fFloat)
{
	return as_string("%lf", fFloat);
}

std::string NumberOper::Uint32To16Str(uint32_t unNumber)
{
	return as_string("%X", unNumber);
}

std::string NumberOper::Uint64To16Str(uint64_t un64Number)
{
	return as_string("%llX", un64Number);
}

std::string NumberOper::Uint32To8Str(uint32_t unNumber)
{
	return as_string("%o", unNumber);
}

std::string NumberOper::Uint64To8Str(uint64_t un64Number)
{
	return as_string("%llo", un64Number);
}

std::string NumberOper::Uint32To2Str(uint32_t unNumber)
{
#define BUF_SIZE 64
	char chBuf[BUF_SIZE] = { 0 };
	uint32_t unSize = sizeof(uint32_t) * 8;
	uint32_t  i = unSize;
	for (uint32_t unI = unNumber; i >= 0 && unI > 0; )
	{
		uint8_t un8Tmp = unI & 0x01;
		if (0 == un8Tmp)
		{
			chBuf[i] = '0';
		}
		else
		{
			chBuf[i] = '1';
		}
		unI = unI >> 1;
		i--;
	}

	std::string strRst = &chBuf[i + 1];
	return std::move(strRst);
}

std::string NumberOper::Uint64To2Str(uint64_t un64Number)
{
#define BUF_SIZE 80
	char chBuf[BUF_SIZE] = { 0 };
	uint64_t unSize = sizeof(uint64_t) * 8;
	uint64_t  i = unSize;
	for (uint64_t unI = un64Number; i >= 0 && unI > 0; )
	{
		uint8_t un8Tmp = unI & 0x01;
		if (0 == un8Tmp)
		{
			chBuf[i] = '0';
		}
		else
		{
			chBuf[i] = '1';
		}
		unI = unI >> 1;
		i--;
	}

	std::string strRst = &chBuf[i + 1];
	return std::move(strRst);
}


int32_t NumberOper::StrToInt32(std::string strRst)
{
	return atoi(strRst.c_str());
}

uint32_t NumberOper::StrToUint32(std::string strRst)
{
	char *pPos = NULL;
	return strtoul(strRst.c_str(), &pPos, 10);
}

int64_t NumberOper::StrToInt64(std::string strRst)
{
#if defined(_WIN32) || defined(_WIN64)
	return _strtoi64(strRst.c_str(), NULL, 10);
#else
	return strtoimax(strRst.c_str(), &chTmpPos, 1o);
#endif
}

uint64_t NumberOper::StrToUint64(std::string strRst)
{
	char *chTmpPos = NULL;
	
#if _MSC_VER<=1800
	return _strtoi64(strRst.c_str(), &chTmpPos, 0);
#else
	return strtoull(strRst.c_str(), &chTmpPos, 0);
#endif
}

uint32_t NumberOper::Str16ToUint32(std::string strRst)
{
	char *chTmpPos = NULL;
#if _MSC_VER<=1800
	return strtoul(strRst.c_str(), NULL, 16);
#else
	return strtoull(strRst.c_str(), &chTmpPos, 16);
#endif
}



uint64_t NumberOper::Str16ToUint64(std::string strRst)
{
	char *chTmpPos = NULL;
#if _MSC_VER<=1800
	return strtoul(strRst.c_str(), NULL, 16);
#else
	return strtoull(strRst.c_str(), &chTmpPos, 16);
#endif
}


uint32_t NumberOper::Str8ToUnt32(std::string strRst)
{
	char *chTmpPos = NULL;
#if defined(_WIN32) || defined(_WIN64)
	#if _MSC_VER<=1800
		return _strtoi64(strRst.c_str(), &chTmpPos, 8);
	#else
		return strtoull(strRst.c_str(), &chTmpPos, 8);
	#endif
#else
	return strtoull(strRst.c_str(), &chTmpPos, 8);
#endif
}