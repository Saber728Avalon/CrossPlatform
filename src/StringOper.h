#pragma once
 /**
 * @file		StringOper.h
 * @brief		字符串操作函数类。对于每个都提供了asc和unicode版本
 * @author		duanqiang
 * @date		2017/03/19
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <stdint.h>

//这里要注意windows使用的utf-16,  mac linux用的utf-32
#ifdef _WIN32
#define UNI_CHAR_KEYWORD wchar_t
#elif defined(__APPLE__)
#define UNI_CHAR_KEYWORD wchar_t
#elif defined(__linux__)
#define UNI_CHAR_KEYWORD wchar_t
#elif defined(__unix__)
#define UNI_CHAR_KEYWORD short
#else
#pragma error "Not Support"
#endif

class StringOper
{
public:
	~StringOper();


	/**
		* @brief     分割ascii字符串
		* @note      
		* @returns   分割结果
		* @param[in] const std::string & strSrc 原始字符串
		* @param[in] std::vector<char> vectSplitChar 分割字符串的字符
		* @param[in] bool bCMode 指定字符串是否用 '\0'结尾
		* @code      
		* @endcode    
		* @since     2020/08/18
	*/
	static std::vector<std::string> StringSplitAsc(const std::string &strSrc, std::vector<char> vectSplitChar);



	/**
		* @brief     分割unicode字符串
		* @note      
		* @returns   分割结果
		* @param[in] strSrcv 原始字符串
		* @param[in] vectSplitChar  分割字符串的字符
		* @param[in] bCMode 指定字符串是否用 '\0'结尾
		* @code      
		* @endcode    
		* @since     2020/08/18
	*/
	static std::vector<std::wstring> StringSplitUni(const std::wstring &strSrc, std::vector<UNI_CHAR_KEYWORD> vectSplitChar);


	/**
		* @brief     将ascii字符串转为大写
		* @note      
		* @returns   转换后的结果
		* @param[in] strSrc 输入的字符串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string ToUpperCaseAsc(std::string strSrc);



	/**
		* @brief     将unicode字符串转为大写
		* @note      
		* @returns   转换后的结果
		* @param[in] strSrc 输入的字符串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring ToUpperCaseUni(std::wstring strSrc);


	/**
		* @brief     将ascii字符串转为小写
		* @note      
		* @returns   转换后的结果
		* @param[in] strSrc 输入的字符串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string ToLowerCaseAsc(std::string strSrc);



	/**
		* @brief     将unicode字符串转为小写
		* @note      
		* @returns   转换后的结果
		* @param[in] strSrc 输入的字符串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring ToLowerCaseUni(std::wstring strSrc);


	/**
		* @brief     判断asc字符串是否以前缀开头
		* @note      
		* @returns   bool
		* @param[in] strSrc 原始字符串
		* @param[in] strPrefix 匹配串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool StartWithAsc(const std::string &strSrc, const std::string &strPrefix);

	/**
		* @brief     判断unicode字符串是否以前缀开头
		* @note      
		* @returns   匹配成功为ture, 匹配失败为false 
		* @param[in] strSrc 原始字符串
		* @param[in] strPrefix 匹配串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool StartWithUni(const std::wstring &strSrc, const std::wstring &strPrefix);

	/**
		* @brief     判断asc字符串是否以前缀结尾
		* @note      
		* @returns   匹配成功为ture, 匹配失败为false 
		* @param[in] strSrc 原始字符串
		* @param[in] strSufffix 匹配串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool EndWithAsc(const std::string &strSrc, const std::string &strSufffix);

	/**
		* @brief     判断unicode字符串是否以前缀结尾
		* @note      
		* @returns   匹配成功为ture, 匹配失败为false 
		* @param[in] strSrc 原始字符串
		* @param[in] strSufffix 匹配串
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool EndWithUni(const std::wstring &strSrc, const std::wstring &strSufffix);


	/**
		* @brief     格式化ascii字符串
		* @note      
		* @returns   返回ascii字符串
		* @param[in] fmt 格式化串
		* @param[in] ... 参数
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string FormatAsc(const char *fmt, ...);

	/**
		* @brief     格式化unicode字符串
		* @note      
		* @returns   返回unicode字符串
		* @param[in] fmt 格式化串
		* @param[in] ... 参数
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring FormatUni(const UNI_CHAR_KEYWORD *fmt, ...);


	/**
		* @brief     去掉ascii左边空格
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string LeftTrimAsc(const std::string strSrc);


	/**
		* @brief     去掉ascii右边空格
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string RightTrimAsc(const std::string strSrc);


	/**
		* @brief     去掉unicode左边空格
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring LeftTrimUni(const std::wstring strSrc);


	/**
		* @brief      去掉unicode右边空格
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring RightTrimUni(const std::wstring strSrc);



	/**
		* @brief     去掉ascii两边空格
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string TrimAsc(const std::string strSrc);



	/**
		* @brief      去掉unicode两边空格
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring TrimUni(const std::wstring strSrc);


	/**
		* @brief     反向查找ascii字符串，只要有一个字符找到,则返回.主要用于查找多个多个结尾的情况。比如文件路径结尾可能是\,也可能是/
		* @note      
		* @returns   uint32_t
		* @param[in] const std::string strSrc
		* @param[in] const std::string strObj
		* @code      
		* @endcode    
		* @since     2020/09/21
	*/
	static int RFindOrStringAsc(const std::string strSrc, const std::string strObj);


	/**
		* @brief     反向查找unicode字符串，只要有一个字符找到,则返回.主要用于查找多个多个结尾的情况。比如文件路径结尾可能是\,也可能是/
		* @note      
		* @returns   uint32_t
		* @param[in] const std::wstring strSrc
		* @param[in] const std::wstring strObj
		* @code      
		* @endcode    
		* @since     2020/09/21
	*/
	static int RFindOrStringUni(const std::wstring strSrc, const std::wstring strObj);
	
	
	/**
		* @brief     ascii字符串进行替换
		* @note      
		* @returns   替换结果
		* @param[in] strSrc 替换的原始字符串
		* @param[in] strObj 替换的目标串
		* @param[in] strReplace 替换的结果串
		* @code
		* @endcode
		* @since     2020/12/08
	*/
	static std::string ReplaceAsc(std::string strSrc, std::string strObj, std::string strReplace);

	/**
	* @brief     unicode字符串进行替换
	* @note
	* @returns   替换结果
	* @param[in] strSrc 替换的原始字符串
	* @param[in] strObj 替换的目标串
	* @param[in] strReplace 替换的结果串
	* @code
	* @endcode
	* @since     2020/12/08
	*/
	static std::wstring ReplaceUni(std::wstring strSrc, std::wstring strObj, std::wstring strReplace);


	/**
		* @brief     判断ASCII字符串是否全部是数字
		* @note      
		* @returns   true全部是数字，否则false
		* @param[in] strSrc
		* @code      
		* @endcode    
		* @since     2021/07/01
	*/
	static bool IsDigitalAsc(const std::string &strSrc);


	/**
		* @brief     判断UNICODE字符串是否全部是数字
		* @note      
		* @returns   true全部是数字，否则false
		* @param[in] strSrc
		* @code      
		* @endcode    
		* @since     2021/07/01
	*/
	static bool IsDigitalUni(const std::wstring &strSrc);

	/**
		* @brief    将std;:string字符串,变成同时支持C/C++两个形式的字符串
		* @note     由于c++的string是支持存放二进制数据的。这就导致了 字符串abcd'\0' 和abcd 二者是不同的。此函数，通过模仿C++字符串处理。故意将预留空间变大。用来保持前面说的是同一个字符串
		* @returns   std::string
		* @param[in] const std::string & strSrc
		* @code      
		* @endcode    
		* @since     2021/07/02
	*/
	static std::string  CppAndCStrAsc(const std::string & strSrc);

	/**
		* @brief     将std;:wstring字符串,变成同时支持C/C++两个形式的字符串
		* @note      由于c++的string是支持存放二进制数据的。这就导致了 字符串abcd'\0' 和abcd 二者是不同的。此函数，通过模仿C++字符串处理。故意将预留空间变大。用来保持前面说的是同一个字符串
		* @returns   std::wstring
		* @param[in] const std::wstring & strSrc
		* @code      
		* @endcode    
		* @since     2021/07/02
	*/
	static std::wstring  CppAndCStrUni(const std::wstring & strSrc);
private:
	StringOper();
};

