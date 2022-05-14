#include "FileUtils.h"
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string.h>

#if  defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
	#include <Shlwapi.h>
	#include <direct.h>
	#include <io.h>
	#include <ShlObj.h>

#if _MSC_VER <=1800
	#include <sys/stat.h>
	#include <string>
#endif
#pragma comment(lib, "Shlwapi.lib")
#else
	#include <dirent.h>
	#include <unistd.h>
	#include <sys/stat.h>
#endif// _WIN32 || _WIN64


namespace CP
{



	FileUtils::FileUtils()
	{
	}


	FileUtils::~FileUtils()
	{
	}


	DQFILE FileUtils::FileOpenAsc(const char *pszFilePath, FileMode mode)
	{
		DQFILE pFile = NULL;
		if (FileMode::readMode == mode)
		{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileA(pszFilePath
				, GENERIC_READ
				, FILE_SHARE_READ
				, NULL
				, OPEN_EXISTING
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = fopen(pszFilePath, "rb");
#endif

		}
		else if (FileMode::newWriteMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileA(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, CREATE_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = fopen(pszFilePath, "wb+");
#endif
		}
		else if (FileMode::endWriteMode == mode)
		{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileA(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, OPEN_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
			if (FileSeek(pFile, 0, SeekMode::SeekModeEnd) < 0)
			{
				return 0;
			}
#else
			pFile = fopen(pszFilePath, "ab+");
#endif
		}
		else if (FileMode::readAndWriteMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileA(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, OPEN_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = fopen(pszFilePath, "rb+");
#endif
		}
		else
		{
			return pFile;
		}
		return pFile;
	}

#if defined(_WIN32) ||defined(_WIN64)
	DQFILE FileUtils::FileOpenUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath, FileMode mode /*= FileMode::readMode*/)
	{
		DQFILE pFile = NULL;
		if (FileMode::readMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileW(pszFilePath
				, GENERIC_READ
				, FILE_SHARE_READ | FILE_SHARE_WRITE
				, NULL
				, OPEN_EXISTING
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = _wfopen(pszFilePath, L"rb");
#endif
		}
		else if (FileMode::newWriteMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileW(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, CREATE_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = _wfopen(pszFilePath, L"wb+");
#endif
		}
		else if (FileMode::endWriteMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileW(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, OPEN_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
			if (FileSeek(pFile, 0, SeekMode::SeekModeEnd) < 0)
			{
				return 0;
			}
#else
			pFile = _wfopen(pszFilePath, L"ab+");
#endif
		}
		else if (FileMode::readAndWriteMode == mode)
		{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			pFile = CreateFileW(pszFilePath
				, GENERIC_READ | GENERIC_WRITE
				, FILE_SHARE_READ
				, NULL
				, OPEN_ALWAYS
				, FILE_ATTRIBUTE_NORMAL
				, NULL);
#else
			pFile = _wfopen(pszFilePath, L"rb+");
#endif
		}
		else
		{
			return pFile;
		}
		return pFile;
	}
#else
	//#error "Not Support"
#endif

	std::string FileUtils::GetCurDir()
	{
		char chBuf[1024] = { 0 };
		std::string strFilePath;
#if defined(_WIN32) || defined(_WIN64)
		_getcwd(chBuf, 1024);
#else
		getcwd(chBuf, 1024);
#endif
		strFilePath += (chBuf);
		if (strFilePath.at(strFilePath.length() - 1) != '\\' || strFilePath.at(strFilePath.length() - 1) != '/')
		{
			strFilePath += "/";
		}

		return strFilePath;
	}


	bool FileUtils::CreateDirAsc(char *pszDir)
	{
		int nRet = 0;
#if defined(_WIN32) || defined(_WIN64)
#if defined(_USE_WIN32_API)
		nRet = !CreateDirectoryA(pszDir, NULL);
#else
		nRet = mkdir(pszDir);
#endif
#else
		nRet = mkdir(pszDir, S_IRWXU | S_IRWXG | S_IRWXO);
#endif
		return 0 == nRet;
	}

#if defined(_WIN32) || defined(_WIN64)
	bool FileUtils::CreateDirUni(FILE_UNI_CHAR_KEYWORD *pszDir)
	{
		return CreateDirectoryW(pszDir, NULL);
	}
#endif

	bool FileUtils::CreateDirsAsc(const char *pszDir)
	{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		char chBufPath[MAX_PATH] = { 0 };
		for (int i = 0; i < MAX_PATH; i++)
		{
			if ('\0' == pszDir[i])
			{
				break;
			}
			else if ('/' == pszDir[i])
			{
				chBufPath[i] = '\\';
			}
			else
			{
				chBufPath[i] = pszDir[i];
			}
		}
		int nRet = SHCreateDirectoryExA(NULL, chBufPath, NULL);
		if (ERROR_SUCCESS != nRet)
		{
			return false;
		}
		return true;
#else
		int nRet = 0;
		int nSize = strlen(pszDir);
		char *pChTmpBuf = new char[nSize];
		for (int i = 0; i < nSize; i++)
		{
			if ('\\' == pszDir[i] || '/' == pszDir[i])
			{
				memset(pChTmpBuf, 0, nSize);
				memcpy(pChTmpBuf, pszDir, i);
#if defined(_WIN32) || defined(_WIN64)
				nRet = mkdir(pChTmpBuf);
#else
				nRet = mkdir(pChTmpBuf, S_IRWXU | S_IRWXG | S_IRWXO);
#endif
			}

		}

		//避免末尾没有/就不创建目录
#if defined(_WIN32) || defined(_WIN64)
		nRet = mkdir(pszDir);
#else
		nRet = mkdir(pszDir, S_IRWXU | S_IRWXG | S_IRWXO);
#endif
		delete[] pChTmpBuf;
		pChTmpBuf = NULL;
		return 0 == nRet;
#endif
	}

#if  (defined(_WIN32) || defined(_WIN64))
	bool FileUtils::CreateDirsUni(const FILE_UNI_CHAR_KEYWORD *pszDir)
	{
		FILE_UNI_CHAR_KEYWORD chBufPath[MAX_PATH] = { 0 };
		for (int i = 0; i < MAX_PATH; i++)
		{
			if ('\0' == pszDir[i])
			{
				break;
			}
			else if ('/' == pszDir[i])
			{
				chBufPath[i] = '\\';
			}
			else
			{
				chBufPath[i] = pszDir[i];
			}
		}
		int nRet = SHCreateDirectoryExW(NULL, chBufPath, NULL);
		if (ERROR_SUCCESS != nRet)
		{
			return false;
		}
		return true;;
	}
#endif

	bool FileUtils::FileIsExistAsc(const char *pszFilePath)
	{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		return PathFileExistsA(pszFilePath);
#else
		struct stat statBuf;
		return (stat(pszFilePath, &statBuf) == 0);
#endif
	}

#if defined(_WIN32) ||defined(_WIN64)
	bool FileUtils::FileIsExistUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath)
	{
		return PathFileExistsW(pszFilePath);
	}
#else
	//#error "Not Support"
#endif

	bool FileUtils::FileDeleteAsc(const char *pszFilePath)
	{
#if  (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		return DeleteFileA(pszFilePath);
#else
		return 0 == remove(pszFilePath);
#endif
	}

#if  (defined(_WIN32) || defined(_WIN64))
	bool FileUtils::FileDeleteUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath)
	{
		return DeleteFileW(pszFilePath);
	}
#endif

	bool FileUtils::FileCopy(const char *pszSrcFilePath, const char *pszDstFilePath)
	{
		DQFILE pSrcFile = FileOpenAsc(pszSrcFilePath, FileMode::readMode);
		DQFILE pDstFile = FileOpenAsc(pszDstFilePath, FileMode::newWriteMode);
		if (NULL == pSrcFile || NULL == pDstFile)
		{
			FileClose(pSrcFile);
			FileClose(pDstFile);
			return false;
		}
		int nRead = 1;
		unsigned char chBuf[1024];
		do 
		{
			nRead = FileRead(pSrcFile, chBuf, 1024);
			FileWrite(pDstFile, chBuf, nRead);
		} while (nRead > 0);
		FileClose(pSrcFile);
		FileClose(pDstFile);
		return true;
	}

	bool FileUtils::DirCopy(const char *pszSrcDirPath, const char *pszDstDirPath)
	{
		std::string strSrcDir = pszSrcDirPath;
		if (strSrcDir.at(strSrcDir.length() - 1) != '/' && strSrcDir.at(strSrcDir.length() - 1) != '\\')
		{
			strSrcDir += "/";
		}

		std::string strDstDir = pszDstDirPath;
		if (strDstDir.at(strDstDir.length() - 1) != '/' && strDstDir.at(strDstDir.length() - 1) != '\\')
		{
			strDstDir += "/";
		}

#if defined(_WIN32) || defined(_WIN64)
		_finddata_t fileDir;
		std::string strSrcDirPoint = strSrcDir + "*";
		uint32_t nFind = _findfirst(strSrcDirPoint.c_str(), &fileDir);
		if (-1 == nFind)
		{
			return false;
		}
		do {
			if (0 == strcmp(fileDir.name, ".") || 0 == strcmp(fileDir.name, ".."))
			{
				continue;
			}

			std::string strSrcFilePath = strSrcDir + fileDir.name;
			std::string strDstFilePath = strDstDir + fileDir.name;

			if (_A_SUBDIR & fileDir.attrib)
			{
				CreateDirAsc((char *)strDstFilePath.c_str());
				DirCopy(strSrcFilePath.c_str(), strDstFilePath.c_str());
			}
			else
			{
				FileCopy(strSrcFilePath.c_str(), strDstFilePath.c_str());
			}
		} while (_findnext(nFind, &fileDir) == 0);
		_findclose(nFind);
#else
		DIR *fileDir = NULL;
		struct stat st;
		struct dirent *pDir = NULL;
		std::string strSrcDirPoint = strSrcDir;

		fileDir = opendir(strSrcDirPoint.c_str());
		if (NULL == fileDir)
		{
			return false;
		}

		while ((pDir = readdir(fileDir)) != NULL)
		{
			if (0 == strcmp(pDir->d_name, ".") || 0 == strcmp(pDir->d_name, ".."))
			{
				continue;
			}

			std::string strSrcFilePath = strSrcDir + pDir->d_name;
			std::string strDstFilePath = strDstDir + pDir->d_name;

			stat(strSrcFilePath.c_str(), &st);
			if (S_ISDIR(st.st_mode))
			{
				CreateDir((char *)strDstFilePath.c_str());
				DirCopy(strSrcFilePath.c_str(), strDstFilePath.c_str());
			}
			else
			{
				FileCopy(strSrcFilePath.c_str(), strDstFilePath.c_str());
			}
		}
		closedir(fileDir);
#endif
		return true;
	}

	int FileUtils::FileOpenAndReadAsc(const char *pszFilePath, std::string &binFileData)
	{
		DQFILE pFile = FileOpenAsc(pszFilePath, FileMode::readMode);
		if (NULL == pFile)
		{
			return -1;
		}
		uint64_t un64Size = FileSize(pFile);
		if (0 == un64Size)
		{
			FileClose(pFile);
			return -2;
		}
		binFileData.resize(un64Size);
		if (un64Size != binFileData.size())
		{
			FileClose(pFile);
			return -3;
		}

		uint32_t nRead = FileRead(pFile, (unsigned char *)binFileData.data(), un64Size);
		if (nRead != un64Size)
		{
			FileClose(pFile);
			return -4;
		}

		FileClose(pFile);
		return 0;
	}

#if defined(_WIN32) ||defined(_WIN64)
	int FileUtils::FileOpenAndReadUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath, std::string &binFileData)
	{
		DQFILE pFile = FileOpenUni(pszFilePath, FileMode::readMode);
		if (NULL == pFile)
		{
			return -1;
		}
		uint64_t un64Size = FileSize(pFile);
		if (0 == un64Size)
		{
			FileClose(pFile);
			return -2;
		}
		binFileData.resize(un64Size);
		if (un64Size != binFileData.size())
		{
			FileClose(pFile);
			return -3;
		}

		uint32_t nRead = FileRead(pFile, (unsigned char *)binFileData.data(), un64Size);
		if (nRead != un64Size)
		{
			FileClose(pFile);
			return -4;
		}

		FileClose(pFile);
		return 0;
	}
#endif

	uint32_t FileUtils::FileWrite(const DQFILE pFile, const unsigned char *pData, const uint32_t nDataLen)
	{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		DWORD dwWrite = 0;
		WriteFile(pFile, pData, nDataLen, &dwWrite, NULL);
		return dwWrite;
#else
		return fwrite(pData, 1, nDataLen, (DQFILE)pFile);
#endif
	}

	uint32_t FileUtils::FileRead(DQFILE pFile, unsigned char *pData, uint32_t nDataLen)
	{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		DWORD dwRead = 0;
		ReadFile(pFile, pData, nDataLen, &dwRead, NULL);
		return dwRead;
#else
		return fread(pData, 1, nDataLen, pFile);
#endif
	}

	uint64_t FileUtils::FileSize(DQFILE pFile)
	{
#if defined(_WIN32) || defined(_WIN64)
#if defined(_USE_WIN32_API)
		uint64_t un64FileSize = 0;
		LARGE_INTEGER largeInteger = { 0 };
		BOOL bSuc = GetFileSizeEx(pFile, &largeInteger);
		if (!bSuc)
		{
			return 0;
		}
		un64FileSize = largeInteger.QuadPart;
#else
		uint64_t nCurPos = _ftelli64(pFile);
		_fseeki64(pFile, 0L, SEEK_END);
		uint64_t un64FileSize = _ftelli64(pFile);
		_fseeki64(pFile, nCurPos, SEEK_SET);
#endif
#else
		uint64_t nCurPos = ftello(pFile);
		fseeko(pFile, 0L, SEEK_END);
		uint64_t un64FileSize = ftello(pFile);
		fseeko(pFile, nCurPos, SEEK_SET);
#endif
		return un64FileSize;
	}

	int FileUtils::FileClose(DQFILE &pFile)
	{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		int nRet = !CloseHandle(pFile);
#else
		int nRet = fclose(pFile);
#endif
		if (0 == nRet)
		{
			pFile = NULL;
		}
		return  nRet;
	}

	int FileUtils::FileSeek(DQFILE pFile, int32_t unPos, SeekMode nMode)
	{
		int nSeekMode = 0;
		if (SeekMode::SeekModeBegin == nMode)
		{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			nSeekMode = FILE_BEGIN;
#else
			nSeekMode = SEEK_SET;
#endif
			if (unPos < 0)//开始位置，这里肯定不能再往前了
			{
				return -1;
			}
		}
		else if (SeekMode::SeekModeCur == nMode)
		{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			nSeekMode = FILE_CURRENT;
#else
			nSeekMode = SEEK_CUR;
#endif
		}
		else if (SeekMode::SeekModeEnd == nMode)
		{
			if (unPos > 0)//事实上API是允许unpos>0，这代表将文件扩大.统一标准，这里不允许，避免逻辑问题
			{
				return -1;
			}
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
			nSeekMode = FILE_END;
#else
			nSeekMode = SEEK_END;
#endif
		}
		else
		{
			return -1;
		}

#if defined(_WIN32) || defined(_WIN64)
#if defined(_USE_WIN32_API)
		LARGE_INTEGER largeMove = { 0 }, largeNew = {0};
		largeMove.LowPart = unPos;
		BOOL bSuc = SetFilePointerEx(pFile, largeMove, &largeNew, nSeekMode);
		if (!bSuc)
		{
			return -1;
		}
		return 0;
#else
		return _fseeki64(pFile, unPos, nSeekMode);
#endif
#else
		return fseeko(pFile, unPos, nSeekMode);
#endif
	}

	int FileUtils::FileFlush(DQFILE pFile)
	{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		return !FlushFileBuffers(pFile);
#else
		return fflush(pFile);
#endif
	}

	int FileUtils::DirList(std::vector<std::string> &rstVect, const char* pszSrcDirPath, const char *pszExt)
	{
		std::string strSrcDir = pszSrcDirPath;
		char psz = strSrcDir.at(strSrcDir.length() - 1);
		if (strSrcDir.at(strSrcDir.length() - 1) != '/' && strSrcDir.at(strSrcDir.length() - 1) != '\\')
		{
			strSrcDir += "/";
		}
#if defined(_WIN32) || defined(_WIN64)
		_finddata_t fileDir;
		std::string strSrcDirPoint = strSrcDir + "*";
		uint32_t nFind = _findfirst(strSrcDirPoint.c_str(), &fileDir);
		if (-1 == nFind)
		{
			return 0;
		}

		int nLenExt = strlen(pszExt);
		do {
			if (0 == strcmp(fileDir.name, ".") || 0 == strcmp(fileDir.name, ".."))
			{
				continue;
			}
			std::string strSrcFilePath = strSrcDir + fileDir.name;

			if (_A_SUBDIR & fileDir.attrib)
			{
				DirList(rstVect, strSrcFilePath.c_str(), pszExt);
			}
			else
			{
				int nDNameLen = strlen(fileDir.name);
				if (nLenExt > nDNameLen)
				{
					continue;
				}
				if (0 != _stricmp(fileDir.name + nDNameLen - nLenExt, pszExt))
				{
					continue;
				}
				rstVect.push_back(strSrcFilePath);
			}
		} while (_findnext(nFind, &fileDir) == 0);
		_findclose(nFind);
#else
		DIR* fileDir = NULL;
		struct stat st;
		struct dirent* pDir = NULL;
		std::string strSrcDirPoint = strSrcDir;

		fileDir = opendir(strSrcDirPoint.c_str());
		if (NULL == fileDir)
		{
			return false;
		}

		int nLenExt = strlen(pszExt);
		while ((pDir = readdir(fileDir)) != NULL)
		{
			if (0 == strcmp(pDir->d_name, ".") || 0 == strcmp(pDir->d_name, "..") || 0 == strcmp(pDir->d_name, ".."))
			{
				continue;
			}


			std::string strSrcFilePath = strSrcDir + pDir->d_name;

			stat(strSrcFilePath.c_str(), &st);
			//链接关闭文件会崩溃
			if (S_ISLNK(st.st_mode) || S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
			{
				continue;
			}

			if (S_ISDIR(st.st_mode))
			{
				DirList(rstVect, strSrcFilePath.c_str(), pszExt);
			}
			else
			{
				if (!S_ISREG(st.st_mode))
				{
					continue;
				}
				int nDNameLen = strlen(pDir->d_name);
				if (nLenExt > nDNameLen)
				{
					continue;
				}
				if (0 != strcmp(pDir->d_name + nDNameLen - nLenExt, pszExt))
				{
					continue;
				}
				rstVect.push_back(strSrcFilePath);
			}
		}
		closedir(fileDir);
#endif
		return 0;
	}


	int FileUtils::FileRenameAsc(const char *pszOldName, const char *pszNewName)
	{
#if (defined(_WIN32) || defined(_WIN64)) && defined(_USE_WIN32_API)
		return !MoveFileA(pszOldName, pszNewName);
#else
		return rename(pszOldName, pszNewName);
#endif
	}

#if  (defined(_WIN32) || defined(_WIN64))
	int FileUtils::FileRenameUni(const FILE_UNI_CHAR_KEYWORD *pszOldName, const FILE_UNI_CHAR_KEYWORD *pszNewName)
	{
		return !MoveFileW(pszOldName, pszNewName);
	}
#endif

}