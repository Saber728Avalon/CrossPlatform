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

class NumberOper
{
public:
	~NumberOper();
	

	/**
		* @brief     int32 转字符串
		* @note      
		* @returns   std::string
		* @param[in] nNumber 待转换的字符串
		* @code      
		* @endcode    
		* @since     2020/12/08
	*/
	static std::string Int32ToStr(int32_t nNumber);


	/**
	* @brief     int32 转字符串
	* @note
	* @returns   std::string
	* @param[in] nNumber 待转换的字符串
	* @code
	* @endcode
	* @since     2020/12/08
	*/
	static std::string Int64ToStr(int64_t nNumber);

	/**
		* @brief     int32转16进制字符串
		* @note      
		* @returns   std::string
		* @param[in] int32_t nNumber
		* @code      
		* @endcode    
		* @since     2020/12/08
	*/
	static std::string Int32To16Str(int32_t nNumber);


	/**
		* @brief     字符串转int32数字
		* @note      
		* @returns   int32_t
		* @param[in] std::string strRst
		* @code      
		* @endcode    
		* @since     2020/12/08
	*/
	static int32_t StrToInt32(std::string strRst);

	static uint32_t StrToUint32(std::string strRst);

	/**
	* @brief     字符串转uint64数字
	* @note
	* @returns   int32_t
	* @param[in] std::string strRst
	* @code
	* @endcode
	* @since     2020/12/08
	*/
	static uint64_t StrToInt64(std::string strRst);


	/**
		* @brief     16进制字符串转uint32
		* @note      字符串以0x开头
		* @returns   int32_t
		* @param[in] std::string strRst
		* @code      
		* @endcode    
		* @since     2020/12/08
	*/
	static uint32_t Str16ToUint32(std::string strRst);


	/**
	* @brief     8进制字符串转uint32
	* @note      字符串以0开头
	* @returns   int32_t
	* @param[in] std::string strRst
	* @code
	* @endcode
	* @since     2020/12/08
	*/
	static uint32_t Str8ToInt32(std::string strRst);


private:
	NumberOper();
};

