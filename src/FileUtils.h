#pragma once
 /**
 * @file		FileUtils.h
 * @brief		跨平台针对文件的操作
 * @author		duanqiang
 * @date		2019/08/28
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdint.h>


//这里要注意windows使用的utf-16,  mac linux用的utf-32
#ifdef _WIN32
#define FILE_UNI_CHAR_KEYWORD wchar_t
#elif defined(__APPLE__)
#define FILE_UNI_CHAR_KEYWORD wchar_t
#elif defined(__linux__)
#define FILE_UNI_CHAR_KEYWORD wchar_t
#elif defined(__unix__)
#define FILE_UNI_CHAR_KEYWORD wchar_t
#else
#pragma error "Not Support"
#endif


class FileUtils
{
public:
	enum FileMode
	{
		readMode,
		newWriteMode,
		endWriteMode,
		readAndWriteMode,

		FileModeCount
	};

	enum SeekMode
	{
		SeekModeCur,
		SeekModeEnd,
		SeekModeBegin,

		SeekModeCount
	};

	~FileUtils();


	/**
		* @brief     打开文件
		* @note      
		* @returns   FILE*
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static FILE* FileOpenAsc(const char *pszFilePath, FileMode mode = FileMode::readMode);

#if defined(_WIN32) ||defined(_WIN64)
	static FILE* FileOpenUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath, FileMode mode = FileMode::readMode);
#else
//#error "Not Support"
#endif


	/**
		* @brief     写文件
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
		* @brief     读文件
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
		* @brief     获取文件大小
		* @note      
		* @returns   uint32_t
		* @param[in] FILE * pFile
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static uint64_t FileSize(FILE *pFile);


	/**
		* @brief     关闭文件
		* @note      
		* @returns   int
		* @param[in] FILE * pFile
		* @code      
		* @endcode    
		* @since      2019/08/28
	*/
	static int FileClose(FILE * &pFile);


	/**
		* @brief     移动文件浮标
		* @note      
		* @returns   成功返回0，失败返回非0
		* @param[in] FILE * pFile
		* @param[in] int32_t unPos
		* @param[in] SeekMode seekMode
		* @code      
		* @endcode    
		* @since     2021/08/18
	*/
	static int FileSeek(FILE *pFile, int32_t unPos, SeekMode seekMode);


	/**
		* @brief     将文件数据写入文件
		* @note      
		* @returns   int
		* @param[in] FILE * pFile
		* @code      
		* @endcode    
		* @since     2021/08/19
	*/
	static int FileFlush(FILE *pFile);


	/**
		* @brief     获取当前运行工作的目录,末尾包含 /或者\
		* @note      注意：windows如果属于VS调试时候，会修改工作目录
		* @returns   std::string
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static std::string GetCurDir();


	/**
		* @brief     创建目录，如果linux则创建所有用户都可以读写运行的目录      
		* @returns   bool
		* @param[in] char * pszDir
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static bool CreateDir(char *pszDir);


	/**
		* @brief     迭代创建目录，如果linux则创建所有用户都可以读写运行的目录 
		* @note      
		* @returns   bool
		* @param[in] char * pszDir
		* @code      
		* @endcode    
		* @since     2020/09/03
	*/
	static bool CreateDirs(const char *pszDir);



	/**
		* @brief     判断文件是否存在
		* @note      
		* @returns   bool
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since     2019/08/28
	*/
	static bool FileIsExistAsc(const char *pszFilePath);
#if defined(_WIN32) ||defined(_WIN64)
	static bool FileIsExistUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath);
#else
//#error "Not Support"
#endif

	/**
		* @brief     删除文件
		* @note      
		* @returns   bool
		* @param[in] char * pszFilePath
		* @code      
		* @endcode    
		* @since     2020/09/01
	*/
	static bool FileDelete(const char *pszFilePath);



	/**
		* @brief     复制文件
		* @note      
		* @returns   bool
		* @param[in] pszSrcFilePath 原始文件路径
		* @param[in] pszDstFilePath 目的文件路径
		* @code      
		* @endcode    
		* @since     2020/09/03
	*/
	static bool FileCopy(const char *pszSrcFilePath, const char *pszDstFilePath);

	/**
		* @brief     迭代复制目录
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
		* @brief     遍历文件夹。获取指定目录下，特定后缀名的文件
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
		* @brief     重命名文件名
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

class FileUtilsClose
{
public:
	FileUtilsClose(FILE *&pFile):m_pFile(pFile)
	{
	}
	~FileUtilsClose() 
	{
		if (NULL != m_pFile)
		{
			FileUtils::FileClose(m_pFile);
			m_pFile = NULL;
		}
	}

private:
	FILE* &m_pFile;
};