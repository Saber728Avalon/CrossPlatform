#pragma once
 /**
 * @file		FileUtils.h
 * @brief		��ƽ̨����ļ��Ĳ���
 * @author		duanqiang
 * @date		2019/08/28
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdint.h>

class FileUtils
{
public:
	enum FileMode
	{
		readMode,
		newWriteMode,
		endWriteMode
	};

	~FileUtils();


	/**
		* @brief     ���ļ�
		* @note      
		* @returns   FILE*
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static FILE* FileOpenAsc(const char *pszFilePath, FileMode mode = FileMode::readMode);

#if defined(_WIN32) ||defined(_WIN64)
	static FILE* FileOpenUni(const wchar_t *pszFilePath, FileMode mode = FileMode::readMode);
#else
#error "Not Support"
#endif


	/**
		* @brief     д�ļ�
		* @note      
		* @returns   uint32_t
		* @param[in] FILE * pFile
		* @param[in] unsigned char * pData
		* @param[in] uint32_t nDataLen
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static uint32_t FileWrite(const FILE *pFile, const unsigned char *pData, const uint32_t nDataLen);


	/**
		* @brief     ���ļ�
		* @note      
		* @returns   uint32_t
		* @param[in] FILE * pFile
		* @param[in] unsigned char * pData
		* @param[in] uint32_t nDataLen
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static uint32_t FileRead(FILE *pFile, unsigned char *pData, uint32_t nDataLen);


	/**
		* @brief     ��ȡ�ļ���С
		* @note      
		* @returns   uint32_t
		* @param[in] FILE * pFile
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static uint64_t FileSize(FILE *pFile);


	/**
		* @brief     �ر��ļ�
		* @note      
		* @returns   int
		* @param[in] FILE * pFile
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static int FileClose(FILE *pFile);


	/**
		* @brief     ��ȡ��ǰ���й�����Ŀ¼,ĩβ���� /����\
		* @note      ע�⣺windows�������VS����ʱ�򣬻��޸Ĺ���Ŀ¼
		* @returns   std::string
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static std::string GetCurDir();


	/**
		* @brief     ����Ŀ¼�����linux�򴴽������û������Զ�д���е�Ŀ¼      
		* @returns   bool
		* @param[in] char * pszDir
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static bool CreateDir(char *pszDir);


	/**
		* @brief     ��������Ŀ¼�����linux�򴴽������û������Զ�д���е�Ŀ¼ 
		* @note      
		* @returns   bool
		* @param[in] char * pszDir
		* @code      
		* @endcode    
		* @since     2020/09/03
	*/
	static bool CreateDirs(char *pszDir);



	/**
		* @brief     �ж��ļ��Ƿ����
		* @note      
		* @returns   bool
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static bool FileIsExist(char *pszFilePath);


	/**
		* @brief     ɾ���ļ�
		* @note      
		* @returns   bool
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since     2020/09/01
	*/
	static bool FileDelete(const char *pszFilePath);



	/**
		* @brief     �����ļ�
		* @note      
		* @returns   bool
		* @param[in] pszSrcFilePath ԭʼ�ļ�·��
		* @param[in] pszDstFilePath Ŀ���ļ�·��
		* @code      
		* @endcode    
		* @since     2020/09/03
	*/
	static bool FileCopy(const char *pszSrcFilePath, const char *pszDstFilePath);

	/**
		* @brief     ��������Ŀ¼
		* @note      
		* @returns   bool
		* @param[in] const char * pszSrcDirPath
		* @param[in] const char * pszDstDirPath
		* @code      
		* @endcode    
		* @since     2020/09/03
	*/
	static bool DirCopy(const char *pszSrcDirPath, const char *pszDstDirPath);


	/**
		* @brief     �����ļ��С���ȡָ��Ŀ¼�£��ض���׺�����ļ�
		* @note      
		* @returns   int
		* @param[in] std::vector<std::string> & rstVect
		* @param[in] const char * pszSrcDirPath
		* @param[in] const char * pszExt
		* @code      
		* @endcode    
		* @since     2020/09/21
	*/
	static int DirList(std::vector<std::string> &rstVect, const char* pszSrcDirPath, const char *pszExt);


	/**
		* @brief     �������ļ���
		* @note      
		* @returns   int
		* @param[in] const char * pszOldName
		* @param[in] const char * pszNewName
		* @code      
		* @endcode    
		* @since     2021/01/13
	*/
	static int FileRename(const char *pszOldName, const char *pszNewName); 
private:
	FileUtils();
};

