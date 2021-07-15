#pragma once
 /**
 * @file		StringOper.h
 * @brief		�ַ������������ࡣ����ÿ�����ṩ��asc��unicode�汾
 * @author		duanqiang
 * @date		2017/03/19
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <stdint.h>

//����Ҫע��windowsʹ�õ�utf-16,  mac linux�õ�utf-32
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
		* @brief     �ָ�ascii�ַ���
		* @note      
		* @returns   �ָ���
		* @param[in] const std::string & strSrc ԭʼ�ַ���
		* @param[in] std::vector<char> vectSplitChar �ָ��ַ������ַ�
		* @param[in] bool bCMode ָ���ַ����Ƿ��� '\0'��β
		* @code      
		* @endcode    
		* @since     2020/08/18
	*/
	static std::vector<std::string> StringSplitAsc(const std::string &strSrc, std::vector<char> vectSplitChar);



	/**
		* @brief     �ָ�unicode�ַ���
		* @note      
		* @returns   �ָ���
		* @param[in] strSrcv ԭʼ�ַ���
		* @param[in] vectSplitChar  �ָ��ַ������ַ�
		* @param[in] bCMode ָ���ַ����Ƿ��� '\0'��β
		* @code      
		* @endcode    
		* @since     2020/08/18
	*/
	static std::vector<std::wstring> StringSplitUni(const std::wstring &strSrc, std::vector<UNI_CHAR_KEYWORD> vectSplitChar);


	/**
		* @brief     ��ascii�ַ���תΪ��д
		* @note      
		* @returns   ת����Ľ��
		* @param[in] strSrc ������ַ���
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string ToUpperCaseAsc(std::string strSrc);



	/**
		* @brief     ��unicode�ַ���תΪ��д
		* @note      
		* @returns   ת����Ľ��
		* @param[in] strSrc ������ַ���
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring ToUpperCaseUni(std::wstring strSrc);


	/**
		* @brief     ��ascii�ַ���תΪСд
		* @note      
		* @returns   ת����Ľ��
		* @param[in] strSrc ������ַ���
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string ToLowerCaseAsc(std::string strSrc);



	/**
		* @brief     ��unicode�ַ���תΪСд
		* @note      
		* @returns   ת����Ľ��
		* @param[in] strSrc ������ַ���
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring ToLowerCaseUni(std::wstring strSrc);


	/**
		* @brief     �ж�asc�ַ����Ƿ���ǰ׺��ͷ
		* @note      
		* @returns   bool
		* @param[in] strSrc ԭʼ�ַ���
		* @param[in] strPrefix ƥ�䴮
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool StartWithAsc(const std::string &strSrc, const std::string &strPrefix);

	/**
		* @brief     �ж�unicode�ַ����Ƿ���ǰ׺��ͷ
		* @note      
		* @returns   ƥ��ɹ�Ϊture, ƥ��ʧ��Ϊfalse 
		* @param[in] strSrc ԭʼ�ַ���
		* @param[in] strPrefix ƥ�䴮
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool StartWithUni(const std::wstring &strSrc, const std::wstring &strPrefix);

	/**
		* @brief     �ж�asc�ַ����Ƿ���ǰ׺��β
		* @note      
		* @returns   ƥ��ɹ�Ϊture, ƥ��ʧ��Ϊfalse 
		* @param[in] strSrc ԭʼ�ַ���
		* @param[in] strSufffix ƥ�䴮
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool EndWithAsc(const std::string &strSrc, const std::string &strSufffix);

	/**
		* @brief     �ж�unicode�ַ����Ƿ���ǰ׺��β
		* @note      
		* @returns   ƥ��ɹ�Ϊture, ƥ��ʧ��Ϊfalse 
		* @param[in] strSrc ԭʼ�ַ���
		* @param[in] strSufffix ƥ�䴮
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static bool EndWithUni(const std::wstring &strSrc, const std::wstring &strSufffix);


	/**
		* @brief     ��ʽ��ascii�ַ���
		* @note      
		* @returns   ����ascii�ַ���
		* @param[in] fmt ��ʽ����
		* @param[in] ... ����
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::string FormatAsc(const char *fmt, ...);

	/**
		* @brief     ��ʽ��unicode�ַ���
		* @note      
		* @returns   ����unicode�ַ���
		* @param[in] fmt ��ʽ����
		* @param[in] ... ����
		* @code      
		* @endcode    
		* @since     2020/08/19
	*/
	static std::wstring FormatUni(const UNI_CHAR_KEYWORD *fmt, ...);


	/**
		* @brief     ȥ��ascii��߿ո�
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string LeftTrimAsc(const std::string strSrc);


	/**
		* @brief     ȥ��ascii�ұ߿ո�
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string RightTrimAsc(const std::string strSrc);


	/**
		* @brief     ȥ��unicode��߿ո�
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring LeftTrimUni(const std::wstring strSrc);


	/**
		* @brief      ȥ��unicode�ұ߿ո�
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring RightTrimUni(const std::wstring strSrc);



	/**
		* @brief     ȥ��ascii���߿ո�
		* @note      
		* @returns   std::string
		* @param[in] const std::string strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::string TrimAsc(const std::string strSrc);



	/**
		* @brief      ȥ��unicode���߿ո�
		* @note      
		* @returns   std::wstring
		* @param[in] const std::wstring strSrc
		* @code      
		* @endcode    
		* @since     2020/08/28
	*/
	static std::wstring TrimUni(const std::wstring strSrc);


	/**
		* @brief     �������ascii�ַ�����ֻҪ��һ���ַ��ҵ�,�򷵻�.��Ҫ���ڲ��Ҷ�������β������������ļ�·����β������\,Ҳ������/
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
		* @brief     �������unicode�ַ�����ֻҪ��һ���ַ��ҵ�,�򷵻�.��Ҫ���ڲ��Ҷ�������β������������ļ�·����β������\,Ҳ������/
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
		* @brief     ascii�ַ��������滻
		* @note      
		* @returns   �滻���
		* @param[in] strSrc �滻��ԭʼ�ַ���
		* @param[in] strObj �滻��Ŀ�괮
		* @param[in] strReplace �滻�Ľ����
		* @code
		* @endcode
		* @since     2020/12/08
	*/
	static std::string ReplaceAsc(std::string strSrc, std::string strObj, std::string strReplace);

	/**
	* @brief     unicode�ַ��������滻
	* @note
	* @returns   �滻���
	* @param[in] strSrc �滻��ԭʼ�ַ���
	* @param[in] strObj �滻��Ŀ�괮
	* @param[in] strReplace �滻�Ľ����
	* @code
	* @endcode
	* @since     2020/12/08
	*/
	static std::wstring ReplaceUni(std::wstring strSrc, std::wstring strObj, std::wstring strReplace);


	/**
		* @brief     �ж�ASCII�ַ����Ƿ�ȫ��������
		* @note      
		* @returns   trueȫ�������֣�����false
		* @param[in] strSrc
		* @code      
		* @endcode    
		* @since     2021/07/01
	*/
	static bool IsDigitalAsc(const std::string &strSrc);


	/**
		* @brief     �ж�UNICODE�ַ����Ƿ�ȫ��������
		* @note      
		* @returns   trueȫ�������֣�����false
		* @param[in] strSrc
		* @code      
		* @endcode    
		* @since     2021/07/01
	*/
	static bool IsDigitalUni(const std::wstring &strSrc);

	/**
		* @brief    ��std;:string�ַ���,���ͬʱ֧��C/C++������ʽ���ַ���
		* @note     ����c++��string��֧�ִ�Ŷ��������ݵġ���͵����� �ַ���abcd'\0' ��abcd �����ǲ�ͬ�ġ��˺�����ͨ��ģ��C++�ַ����������⽫Ԥ���ռ�����������ǰ��˵����ͬһ���ַ���
		* @returns   std::string
		* @param[in] const std::string & strSrc
		* @code      
		* @endcode    
		* @since     2021/07/02
	*/
	static std::string  CppAndCStrAsc(const std::string & strSrc);

	/**
		* @brief     ��std;:wstring�ַ���,���ͬʱ֧��C/C++������ʽ���ַ���
		* @note      ����c++��string��֧�ִ�Ŷ��������ݵġ���͵����� �ַ���abcd'\0' ��abcd �����ǲ�ͬ�ġ��˺�����ͨ��ģ��C++�ַ����������⽫Ԥ���ռ�����������ǰ��˵����ͬһ���ַ���
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

