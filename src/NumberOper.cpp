#include "NumberOper.h"
#include <string.h>
#include <stdlib.h>


NumberOper::NumberOper()
{
}


NumberOper::~NumberOper()
{
}


std::string NumberOper::Int32ToStr(int32_t nNumber)
{
	char chTmpBuf[64] = { 0 };
	sprintf(chTmpBuf, "%d", nNumber);
	std::string strRst = chTmpBuf;
	return strRst;
}

std::string NumberOper::Int32To16Str(int32_t nNumber)
{
	char chTmpBuf[64] = { 0 };
	sprintf(chTmpBuf, "0x%X", nNumber);
	std::string strRst = chTmpBuf;
	return strRst;
}

std::string NumberOper::Int64ToStr(int64_t nNumber)
{
	char chTmpBuf[64] = { 0 };
	sprintf(chTmpBuf, "%lld", nNumber);
	std::string strRst = chTmpBuf;
	return strRst;
}

int32_t NumberOper::StrToInt32(std::string strRst)
{
	return atoi(strRst.c_str());
}

uint64_t NumberOper::StrToInt64(std::string strRst)
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

uint32_t NumberOper::StrToUint32(std::string strRst)
{
	return atoi(strRst.c_str());
}

uint32_t NumberOper::Str8ToInt32(std::string strRst)
{
	char *chTmpPos = NULL;
#if _MSC_VER<=1800
	return _strtoi64(strRst.c_str(), &chTmpPos, 0);
#else
	return strtoull(strRst.c_str(), &chTmpPos, 0);
#endif
}