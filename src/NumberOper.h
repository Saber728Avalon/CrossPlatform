#pragma once
 /**
 * @file		NumberOper.h
 * @brief封装		对数字的常见操作
 * @author		duanqiang
 * @date		2020/12/08
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <stdint.h>

 //这里要注意windows使用的utf-16,  mac linux用的utf-32
#ifdef _WIN32
#define NO_UNI_CHAR_KEYWORD wchar_t
#elif defined(__APPLE__)
#define NO_UNI_CHAR_KEYWORD wchar_t
#elif defined(__linux__)
#define NO_UNI_CHAR_KEYWORD wchar_t
#elif defined(__unix__)
#define NO_UNI_CHAR_KEYWORD wchar_t
#else
#pragma error "Not Support"
#endif

namespace CP
{


	class NumberOper
	{
	public:
		~NumberOper();


		/************************************************************************/
		/* 常见数组转10进制字符串                                               */
		/************************************************************************/
		static std::string Int32ToStr(int32_t nNumber);
		static std::string Int64ToStr(int64_t nNumber);
		static std::string Uint32ToStr(uint32_t unNumber);
		static std::string Uint64ToStr(uint64_t un64Number);
		static std::string FloatToStr(float fFloat);
		static std::string DoubleToStr(double fFloat);

		/************************************************************************/
		/* 常见数组转16进制字符串                                               */
		/************************************************************************/
		static std::string Uint32To16Str(uint32_t unNumber);
		static std::string Uint64To16Str(uint64_t un64Number);

		/************************************************************************/
		/* 常见数组转8进制字符串                                               */
		/************************************************************************/
		static std::string Uint32To8Str(uint32_t unNumber);
		static std::string Uint64To8Str(uint64_t un64Number);

		/************************************************************************/
		/* 常见数组转2进制字符串                                               */
		/************************************************************************/
		static std::string Uint32To2Str(uint32_t unNumber);
		static std::string Uint64To2Str(uint64_t un64Number);

		/************************************************************************/
		/* 常见10进制字符串转数字                                               */
		/************************************************************************/
		static int32_t StrToInt32(std::string strRst);
		static uint32_t StrToUint32(std::string strRst);
		static int64_t StrToInt64(std::string strRst);
		static uint64_t StrToUint64(std::string strRst);


		/************************************************************************/
		/* 常见16进制字符串转数字                                               */
		/************************************************************************/
		static uint32_t Str16ToUint32(std::string strRst);
		static uint64_t Str16ToUint64(std::string strRst);

		/************************************************************************/
		/* 常见8 进制字符串转数字                                               */
		/************************************************************************/
		static uint32_t Str8ToUnt32(std::string strRst);


	private:
		NumberOper();

		/**
		* @brief     as_string
		* @note      
		* @returns   std::string
		* @param[in] const char * fmt
		* @param[in] ...
		* @code      
		* @endcode    
		* @since     2021/09/09
		*/
		static std::string as_string(const char *fmt, ...);
		static std::wstring as_string(const NO_UNI_CHAR_KEYWORD *fmt, ...);
	};
}
