#pragma once
 /**
 * @file		一些C++常用的跨平台函数
 * @brief		文件说明
 * @author		duanqiang
 * @date		2018/05/20
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdint.h>
//#include <chrono>

#if defined(_WIN32) || defined(_WIN64)
	#include <objbase.h>

#elif defined(__ANDROID__)
	#include <stdlib.h>
	#include <stdint.h>
	#include <jni.h>
#elif defined(__linux__)
	#include <uuid/uuid.h>
	#include <limits.h>
#else
	#include <uuid/uuid.h>
#endif// _WIN32 || _WIN64

#ifdef SendMessage
	#undef SendMessage
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define DQ_MAX_PATH MAX_PATH
	#if defined(_UNICODE)
		#define DQStr(XXXX) L##XXXX
	#else
		#define DQStr(XXXX) XXXX
	#endif
#elif defined(__linux__)
	#define DQStr(XXXX) XXXX
	#define DQ_MAX_PATH PATH_MAX
#else
	#define DQStr(XXXX) XXXX
#define DQ_MAX_PATH 256
#endif

/*
* 循环右移，适用于32bit程序
*/
#define ROR32(no, bit) (((no) >> ((bit)%0x20)) | ((no) << (0x20 - ((bit)%0x20))))

/*
* 循环左移，适用于32bit程序
*/
#define ROL32(no, bit) (((no) << ((bit)%0x20)) | ((no) >> (0x20 - ((bit)%0x20))))


/**
	* @brief     安全释放内存
	* @note      
	* @returns   void
	* @param[in] p 输入的指针
	* @code      
	* @endcode    
	* @since     2015/09/14
*/
template<typename T>
inline void safe_delete(T &p)
{
	//delete NULL 指针式合法的  不用判断
	delete [] p;
	p = NULL;
}



/**
	* @brief     跨平台生成UUID
	* @note      
	* @returns   std::string
	* @code      
	* @endcode    
	* @since     2018/05/20
*/
static std::string DQCreateUUID()
{
	std::string strUUID;
#if defined(_WIN32) || defined(_WIN64)
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	if (S_OK == hr)
	{
		char chBuf[64] = { 0 };
		sprintf(chBuf, "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X"
			, guid.Data1, guid.Data2, guid.Data3
			, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3]
			, guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);
			strUUID = chBuf;
	}

#elif defined(__ANDROID__)
	//srand(time(NULL));
	//const char dec2hex[16 + 1] = "0123456789abcdef";
	//for (int i = 0; i < 32; i++)
	//{
	//	char randChar = rand() % 16;
	//	strUUID += dec2hex[randChar];
	//}
	char chBuf[64] = { 0 };
	sprintf(chBuf, "%lld", std::clock());
	strUUID = chBuf;
#else
	uuid_t uu;
	char chBuf[64] = { 0 };
	uuid_generate(uu);
	uuid_unparse(uu, chBuf);
	strUUID = chBuf;
#endif

	return strUUID;
}



/**
	* @brief     二进制数据用十六进制字符串表示
	* @note      注意：这里返回的是小写字符
	* @returns   std::string
	* @param[in] std::string binData
	* @code      
	* @endcode    
	* @since     2020/09/01
*/
static std::string BinToHex(std::string binData)
{
	const char dec2hex[16 + 1] = "0123456789abcdef";
	std::string strResultHex;
	for (uint32_t i = 0; i < binData.size(); i++)
	{
		strResultHex += dec2hex[(binData[i] >> 4) & 15];
		strResultHex += dec2hex[binData[i] & 15];
	}

	return strResultHex;
}



/**
	* @brief     16进制数转2进制数据.
	* @note      支持大小写
	* @returns   std::string
	* @param[in] std::string hexData
	* @code      
	* @endcode    
	* @since     2020/09/01
*/
static std::string HexToBin(std::string hexData)
{
	const char dec2hex[16 + 1] = "0123456789abcdef";
	std::string binResult;

	if (0 != (hexData.size() % 2))
	{
		return binResult;
	}
	binResult.resize(hexData.size() / 2);
	for (uint32_t i = 0; i < hexData.size(); i += 2)
	{
		unsigned char char1 = 0, char2 = 0;
		if (hexData[i] >= '0' && hexData[i] <= '9')
		{
			char1 = hexData[i] - '0';
		}
		else if (hexData[i] >= 'A' && hexData[i] <= 'F')
		{
			char1 = hexData[i] - 'A' + 10;
		}
		else if (hexData[i] >= 'a' && hexData[i] <= 'f')
		{
			char1 = hexData[i] - 'a' + 10;
		}
		else
		{
			return std::string();
		}

		if (hexData[i + 1] >= '0' && hexData[i + 1] <= '9')
		{
			char2 = hexData[i + 1] - '0';
		}
		else if (hexData[i + 1] >= 'A' && hexData[i + 1] <= 'F')
		{
			char2 = hexData[i + 1] - 'A' + 10;
		}
		else if (hexData[i + 1] >= 'a' && hexData[i + 1] <= 'f')
		{
			char2 = hexData[i + 1] - 'a' + 10;
		}
		else
		{
			return std::string();
		}

		unsigned char tmpChar = (char1 << 4) | char2;
		binResult[i / 2] = tmpChar;
	}
	return binResult;
}



/**
	* @brief     跨平台的睡眠函数
	* @note      
	* @returns   void
	* @param[in] uint32_t unSleep
	* @code      
	* @endcode    
	* @since     2020/09/21
*/
static void DQSleep(uint32_t unSleep)
{
#if defined(_WIN32) || defined(_WIN64)
	Sleep(unSleep);
#elif defined(__linux__)
	struct timespec slptm;
	slptm.tv_sec = unSleep / 1000;
    slptm.tv_nsec = 1000 * 1000 * (unSleep % 1000);
	nanosleep(&slptm, NULL); //因为这个单位是纳秒
#elif defined(__APPLE__)
	struct timespec slptm;
	slptm.tv_sec = unSleep / 1000;
	slptm.tv_nsec = 1000 * 1000 * (unSleep % 1000);
	nanosleep(&slptm, NULL); //因为这个单位是纳秒
#else 
#error "Not Support";
#endif
	

	return;
}

/**
	* @brief     得到零时目录
	* @note      
	* @returns   std::string
	* @code      
	* @endcode    
	* @since     2021/08/18
*/
static std::string DQGetTempPath()
{
	std::string strRst;
#if defined(_WIN32) || defined(_WIN64)
	char chBuf[MAX_PATH] = {0};
	GetTempPath(MAX_PATH, chBuf);
	strRst = chBuf;
#elif defined(__linux__)
	strRst = "/tmp/";
#elif defined(__APPLE__)
	strRst = "/tmp/";
#else 
#error "Not Support";
#endif
	return strRst;
}