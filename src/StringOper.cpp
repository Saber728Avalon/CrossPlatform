 /**
 * @file		StringOper.cpp
 * @brief		字符串操作函数类。对于每个都提供了asc和unicode版本
 * @author		duanqiang
 * @date		2020/08/19
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include "StringOper.h"
#include <string.h>
#include <stdarg.h>




StringOper::StringOper()
{
}


StringOper::~StringOper()
{
}

std::vector<std::string> StringOper::StringSplitAsc(const std::string &strSrc, std::vector<char> vectSplitChar)
{
	std::vector<std::string> vectRet;
	std::string strTmp;
	const char *pszSrc = strSrc.c_str();

	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		bool bSplitChar = false;
		for (auto item = vectSplitChar.begin(); item != vectSplitChar.end(); item++)
		{
			if ( (*item) == pszSrc[i])
			{
				bSplitChar = true;
				
				strTmp = CppAndCStrAsc(strTmp);
				if (strTmp.length() > 0 && '\0' != strTmp[0])
				{
					vectRet.push_back(strTmp);
				}
				strTmp.clear();
				break;
			}
		}

		if (false == bSplitChar)
		{
			strTmp += pszSrc[i];
		}
	}
	if (strTmp.length() > 0 && '\0' != strTmp[0])
	{
		strTmp = CppAndCStrAsc(strTmp);
		vectRet.push_back(strTmp);
	}

	return vectRet;
}

std::vector<std::wstring> StringOper::StringSplitUni(const std::wstring &strSrc, std::vector<UNI_CHAR_KEYWORD> vectSplitChar)
{
	std::vector<std::wstring> vectRet;
	std::wstring strTmp;
	const UNI_CHAR_KEYWORD *pszSrc = strSrc.c_str();

	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		bool bSplitChar = false;
		for (auto item = vectSplitChar.begin(); item != vectSplitChar.end(); item++)
		{
			if ( (*item) == pszSrc[i])
			{
				bSplitChar = true;
				
				strTmp = CppAndCStrUni(strTmp);
				if (strTmp.length() > 0 && '\0' != strTmp[0])
				{
					vectRet.push_back(strTmp);
				}
				strTmp.clear();
				break;
			}
		}

		if (false == bSplitChar)
		{
			strTmp += pszSrc[i];
		}
	}

	if (strTmp.length() > 0 && '\0' != strTmp[0])
	{
		vectRet.push_back(strTmp);
	}

	return vectRet;
}

std::string StringOper::ToUpperCaseAsc(std::string strSrc)
{
	char *pszSrc = (char *)strSrc.c_str();
	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		if (pszSrc[i] >= 'a' && pszSrc[i] <= 'z')
		{
			pszSrc[i] -= 0x20;
		}
	}
	return strSrc;
}

std::wstring StringOper::ToUpperCaseUni(std::wstring strSrc)
{
	UNI_CHAR_KEYWORD *pszSrc = (UNI_CHAR_KEYWORD *)strSrc.c_str();
	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		if (pszSrc[i] >= UNI_CHAR_KEYWORD('a') && pszSrc[i] <= UNI_CHAR_KEYWORD('z'))
		{
			pszSrc[i] -= 0x20;
		}
	}
	return strSrc;
}

std::string StringOper::ToLowerCaseAsc(std::string strSrc)
{
	char *pszSrc = (char *)strSrc.c_str();
	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		if (pszSrc[i] >= 'A' && pszSrc[i] <= 'Z')
		{
			pszSrc[i] += 0x20;
		}
	}
	return strSrc;
}

std::wstring StringOper::ToLowerCaseUni(std::wstring strSrc)
{
	UNI_CHAR_KEYWORD *pszSrc = (UNI_CHAR_KEYWORD *)strSrc.c_str();
	int nDataLen = strSrc.length();

	for (int i = 0; i < nDataLen; i++)
	{
		if (pszSrc[i] >= UNI_CHAR_KEYWORD('A') && pszSrc[i] <= UNI_CHAR_KEYWORD('Z'))
		{
			pszSrc[i] += 0x20;
		}
	}
	return strSrc;
}

bool StringOper::StartWithAsc(const std::string &strSrc, const std::string &strPrefix)
{
	if (strSrc.length() < strPrefix.length())
	{
		return false;
	}

	int nPrefixSize = strPrefix.length();
	for (int i = 0; i < nPrefixSize; i++)
	{
		if (strSrc.at(i) != strPrefix.at(i))
		{
			return false;
		}
	}
	return true;
}

bool StringOper::StartWithUni(const std::wstring &strSrc, const std::wstring &strPrefix)
{
	if (strSrc.length() < strPrefix.length())
	{
		return false;
	}

	int nPrefixSize = strPrefix.length();
	for (int i = 0; i < nPrefixSize; i++)
	{
		if (strSrc.at(i) != strPrefix.at(i))
		{
			return false;
		}
	}
	return true;
}

bool StringOper::EndWithAsc(const std::string &strSrc, const std::string &strSufffix)
{
	if (strSrc.length() < strSufffix.length())
	{
		return false;
	}

	int nSrcLen = strSrc.length();
	int nSuffixLen = strSufffix.length();

	for (int i = 1; i <= nSuffixLen; i++)
	{
		if (strSrc.at(nSrcLen - i) != strSufffix.at(nSuffixLen - i))
		{
			return false;
		}
	}
	return true;
}

bool StringOper::EndWithUni(const std::wstring &strSrc, const std::wstring &strSufffix)
{
	if (strSrc.length() < strSufffix.length())
	{
		return false;
	}

	int nSrcLen = strSrc.length();
	int nSuffixLen = strSufffix.length();

	for (int i = 1; i <= nSuffixLen; i++)
	{
		if (strSrc.at(nSrcLen - i) != strSufffix.at(nSuffixLen - i))
		{
			return false;
		}
	}
	return true;
}

std::string StringOper::FormatAsc(const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	int nLen = vsnprintf(nullptr, 0, fmt, vl);
	va_end(vl);

	std::string strBuf(nLen + 1, '\0');

	va_start(vl, fmt);
	vsnprintf(&strBuf[0], strBuf.size(), fmt, vl);
	va_end(vl);

	strBuf = CppAndCStrAsc(strBuf);
	return strBuf;
}

std::wstring StringOper::FormatUni(const UNI_CHAR_KEYWORD *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	int nLen = vswprintf(nullptr, 0, fmt, vl);
	va_end(vl);

	std::wstring strBuf(nLen + 1, '\0');
	va_start(vl, fmt);
	vswprintf(&strBuf[0], (int)strBuf.size(), fmt, vl);
	va_end(vl);

	strBuf = CppAndCStrUni(strBuf);
	return strBuf;
}


std::string StringOper::LeftTrimAsc(const std::string strSrc)
{
	if (strSrc.empty())
	{
		return strSrc;
	}
	
	int i = 0;
	for (; i < strSrc.length(); i++)
	{
		if (' ' != strSrc.at(i))
		{
			break;
		}
	}

	return strSrc.substr(i);
}

std::string StringOper::RightTrimAsc(const std::string strSrc)
{
	if (strSrc.empty())
	{
		return strSrc;
	}
	int i = strSrc.length() - 1;
	for (; i >= 0; i--)
	{
		if (' ' != strSrc.at(i))
		{
			break;
		}
	}

	return strSrc.substr(0, i + 1);
}

std::wstring StringOper::LeftTrimUni(const std::wstring strSrc)
{
	if (strSrc.empty())
	{
		return strSrc;
	}
	
	int i = 0;
	for (; i < strSrc.length(); i++)
	{
		if (UNI_CHAR_KEYWORD(' ') != strSrc.at(i))
		{
			break;
		}
	}

	return strSrc.substr(i);
}

std::wstring StringOper::RightTrimUni(const std::wstring strSrc)
{
	if (strSrc.empty())
	{
		return strSrc;
	}
	
	int i = strSrc.length() - 1;
	for (; i >= 0; i--)
	{
		if (UNI_CHAR_KEYWORD(' ') != strSrc.at(i))
		{
			break;
		}
	}

	return strSrc.substr(0, i + 1);
}

std::string StringOper::TrimAsc(const std::string strSrc)
{
	std::string strLeftTrim = LeftTrimAsc(strSrc);

	return RightTrimAsc(strLeftTrim);
}

std::wstring StringOper::TrimUni(const std::wstring strSrc)
{
	std::wstring strLeftTrim = LeftTrimUni(strSrc);

	return RightTrimUni(strLeftTrim);
}

int StringOper::RFindOrStringAsc(const std::string strSrc, const std::string strObj)
{
	int nSrcSize = strSrc.size();
	for (int i = nSrcSize - 1; i >= 0; i--)
	{
		char tmpCh = strSrc.at(i);
		int nObjSize = strObj.size();
		for (int j = 0; j < nObjSize; j++)
		{
			if (tmpCh == strObj.at(j))
			{
				return i;
			}
		}
	}
	return -1;
}

int StringOper::RFindOrStringUni(const std::wstring strSrc, const std::wstring strObj)
{
	int nSrcSize = strSrc.size();
	for (int i = nSrcSize - 1; i >= 0; i--)
	{
		UNI_CHAR_KEYWORD tmpCh = strSrc.at(i);
		int nObjSize = strObj.size();
		for (int j = 0; j < nObjSize; j++)
		{
			if (tmpCh == strObj.at(j))
			{
				return i;
			}
		}
	}
	return -1;
}

std::string StringOper::ReplaceAsc(std::string strSrc, std::string strObj, std::string strReplace)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += strReplace.length()) 
	{
		if ((pos = strSrc.find(strObj, pos)) != std::string::npos)
			strSrc.replace(pos, strObj.length(), strReplace);
		else 
			break;
	}
	return strSrc;
}

std::wstring StringOper::ReplaceUni(std::wstring strSrc, std::wstring strObj, std::wstring strReplace)
{
	for (std::wstring::size_type pos(0); pos != std::wstring::npos; pos += strReplace.length())
	{
		if ((pos = strSrc.find(strObj, pos)) != std::string::npos)
			strSrc.replace(pos, strObj.length(), strReplace);
		else
			break;
	}
	return strSrc;
}

bool StringOper::IsDigitalAsc(const std::string &strSrc)
{
	char *pSrc = (char *)strSrc.c_str();
	if ('\0' == pSrc)
	{
		return false;
	}

	for (uint32_t i = 0; i < strSrc.size(); i++)
	{
		if ('\0' == pSrc[i])
		{
			return true;
		}
		else if (pSrc[i] >= '0' && pSrc[i] <= '9')
		{

		}
		else
		{
			return false;
		}
	}

	return true;
}

bool StringOper::IsDigitalUni(const std::wstring &strSrc)
{
	char *pSrc = (char *)strSrc.c_str();
	if ('\0' == pSrc)
	{
		return false;
	}

	for (uint32_t i = 0; i < strSrc.size(); i++)
	{
		if ('\0' == pSrc[i])
		{
			return true;
		}
		else if (pSrc[i] >= '0' && pSrc[i] <= '9')
		{

		}
		else
		{
			return false;
		}
	}

	return true;
}

std::string StringOper::CppAndCStrAsc(const std::string & strSrc)
{
	std::string strTmpDst;
	int i = 0;

	strTmpDst.reserve(strSrc.size() + 2);
	strTmpDst.resize(strSrc.size());
	unsigned char *pChTmpSrc = (unsigned char *)strSrc.data();
	unsigned char *pChTmpDst = (unsigned char *)strTmpDst.data();
	for (i = 0; i < strSrc.size(); i++)
	{
		if ('\0' == pChTmpSrc[i])
		{
			strTmpDst.resize(i);
		}
		pChTmpDst[i] = pChTmpSrc[i];
	}
	pChTmpDst[i++] = '\0';
	pChTmpDst[i++] = '\0';
	return std::move(strTmpDst);
}

std::wstring StringOper::CppAndCStrUni(const std::wstring & strSrc)
{
	std::wstring strTmpDst;
	int i = 0;

	strTmpDst.reserve(strSrc.size() + 2);
	strTmpDst.resize(strSrc.size());
	UNI_CHAR_KEYWORD *pChTmpSrc = (UNI_CHAR_KEYWORD *)strSrc.data();
	UNI_CHAR_KEYWORD *pChTmpDst = (UNI_CHAR_KEYWORD *)strTmpDst.data();
	for (i = 0; i < strSrc.size(); i++)
	{
		if ('\0' == pChTmpSrc[i])
		{
			strTmpDst.resize(i);
		}
		pChTmpDst[i] = pChTmpSrc[i];
	}
	pChTmpDst[i++] = '\0';
	pChTmpDst[i++] = '\0';
	return std::move(strTmpDst);
}


std::wstring StringOper::c2w(const char *pc)
{
	std::wstring val = L"";

	if(NULL == pc)
	{
		return val;
	}
	//size_t size_of_ch = strlen(pc)*sizeof(char);
	//size_t size_of_wc = get_wchar_size(pc);
	size_t size_of_wc;
	size_t destlen = mbstowcs(0,pc,0);
	if (destlen ==(size_t)(-1))
	{
		return val;
	}
	size_of_wc = destlen+1;
	UNI_CHAR_KEYWORD * pw  = new UNI_CHAR_KEYWORD[size_of_wc];
	mbstowcs(pw,pc,size_of_wc);
	val = pw;
	delete pw;
	return val;
}

std::string StringOper::w2c(const UNI_CHAR_KEYWORD * pw)
{
	std::string val = "";
	if(!pw)
	{
		return val;
	}

	size_t size= wcslen(pw)*sizeof(UNI_CHAR_KEYWORD);

	char *pc = NULL;
	if(!(pc = (char*)malloc(size)))
	{
		return val;
	}
	memset(pc, 0, size);
	setlocale(LC_ALL, "");
	size_t destlen = wcstombs(pc,pw,size);
	setlocale(LC_ALL, "C");
	/*转换不为空时，返回值为-1。如果为空，返回值0*/
	if (destlen ==(size_t)(0))
	{
		return val;
	}
	val = pc;
	free(pc);
	return val;
}

int StringOper::stricmp(const char *pszSrc, const char *pszDst)
{
#if defined(_WIN32) || defined(_WIN64)
	return stricmp(pszSrc, pszDst);
#elif defined(__linux__)
	return strcasecmp(pszSrc, pszDst);
#else
	const unsigned char *ua = (const unsigned char *)a;
	const unsigned char *ub = (const unsigned char *)b;

	if (((const char *)0 == a) || (const char *)0 == b)
		return int(a - b);

	while ((uc[*ua] == uc[*ub]) && ('\0' != *a))
	{
		a++;
		ua++;
		ub++;
	}

	return int(uc[*ua] - uc[*ub]);
#endif
}

int StringOper::strnicmp(const char *pszSrc, const char *pszDst, int nLen)
{

#if defined(_WIN32) || defined(_WIN64)
	return strnicmp(pszSrc, pszDst, nLen);
#elif defined(__linux__)
	return strncasecmp(pszSrc, pszDst, nLen);
#else
	const unsigned char *ua = (const unsigned char *)a;
	const unsigned char *ub = (const unsigned char *)b;

	if (((const char *)0 == a) || (const char *)0 == b)
		return int(a - b);

	while (max && (uc[*ua] == uc[*ub]) && ('\0' != *a))
	{
		a++;
		ua++;
		ub++;
		nLen--;
	}

	if (0 == max) return 0;

	return int(uc[*ua] - uc[*ub]);
#endif
}

