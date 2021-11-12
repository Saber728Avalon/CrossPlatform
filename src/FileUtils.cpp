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

FileUtils::FileUtils()
{
}


FileUtils::~FileUtils()
{
}


FILE* FileUtils::FileOpenAsc(const char *pszFilePath, FileMode mode)
{
	FILE *pFile = NULL;
	if (FileMode::readMode == mode)
	{
		pFile = fopen(pszFilePath, "rb");
	}
	else if (FileMode::newWriteMode == mode)
	{
		pFile = fopen(pszFilePath, "wb+");
	}
	else if (FileMode::endWriteMode == mode)
	{
		pFile = fopen(pszFilePath, "ab+");
	}
	else if (FileMode::readAndWriteMode == mode)
	{
		pFile = fopen(pszFilePath, "rb+");
	}
	else
	{
		return pFile;
	}
	return pFile;
}

#if defined(_WIN32) ||defined(_WIN64)
FILE* FileUtils::FileOpenUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath, FileMode mode /*= FileMode::readMode*/)
{
	FILE *pFile = NULL;
	if (FileMode::readMode == mode)
	{
		pFile = _wfopen(pszFilePath, L"rb");
	}
	else if (FileMode::newWriteMode == mode)
	{
		pFile = _wfopen(pszFilePath, L"wb+");
	}
	else if (FileMode::endWriteMode == mode)
	{
		pFile = _wfopen(pszFilePath, L"ab+");
	}
	else if (FileMode::readAndWriteMode == mode)
	{
		pFile = _wfopen(pszFilePath, L"rb+");
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
	getcwd(chBuf, 1024);
	strFilePath += (chBuf);
	if (strFilePath.at(strFilePath.length() - 1) != '\\' || strFilePath.at(strFilePath.length() - 1) != '/')
	{
		strFilePath += "/";
	}

	return strFilePath;
}


bool FileUtils::CreateDir(char *pszDir)
{
	int nRet = 0;
#if defined(_WIN32) || defined(_WIN64)
	nRet = mkdir(pszDir);
#else
	nRet = mkdir(pszDir, S_IRWXU | S_IRWXG | S_IRWXO);
#endif
	return 0 == nRet;
}

bool FileUtils::CreateDirs(const char *pszDir)
{
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
}

bool FileUtils::FileIsExistAsc(const char *pszFilePath)
{
	struct stat statBuf;
	return (stat(pszFilePath, &statBuf) == 0);
}

#if defined(_WIN32) ||defined(_WIN64)
bool FileUtils::FileIsExistUni(const FILE_UNI_CHAR_KEYWORD *pszFilePath)
{
	return PathFileExistsW(pszFilePath);
}
#else
//#error "Not Support"
#endif

bool FileUtils::FileDelete(const char *pszFilePath)
{
	return 0 == remove(pszFilePath);
}

bool FileUtils::FileCopy(const char *pszSrcFilePath, const char *pszDstFilePath)
{
	FILE *pSrcFile = FileOpenAsc(pszSrcFilePath, FileMode::readMode);
	FILE *pDstFile = FileOpenAsc(pszDstFilePath, FileMode::newWriteMode);
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
			CreateDir((char *)strDstFilePath.c_str());
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

int FileUtils::FileOpenAndRead(const char *pszFilePath, std::string &binFileData)
{
	FILE *pFile = FileOpenAsc(pszFilePath, FileMode::readMode);
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

uint32_t FileUtils::FileWrite(const FILE *pFile, const unsigned char *pData, const uint32_t nDataLen)
{
	return fwrite(pData, 1, nDataLen, (FILE *)pFile);
}

uint32_t FileUtils::FileRead(FILE *pFile, unsigned char *pData, uint32_t nDataLen)
{
	return fread(pData, 1, nDataLen, pFile);
}

uint64_t FileUtils::FileSize(FILE *pFile)
{
#if defined(_WIN32) || defined(_WIN64)
	uint64_t nCurPos = _ftelli64(pFile);
	_fseeki64(pFile, 0L, SEEK_END);
	uint64_t nFileSize = _ftelli64(pFile);
	_fseeki64(pFile, nCurPos, SEEK_SET);
#else
	uint64_t nCurPos = ftello(pFile);
	fseeko(pFile, 0L, SEEK_END);
	uint64_t nFileSize = ftello(pFile);
	fseeko(pFile, nCurPos, SEEK_SET);
#endif
	return nFileSize;
}

int FileUtils::FileClose(FILE *&pFile)
{
	int nRet =  fclose(pFile);
	if (0 == nRet)
	{
		pFile = NULL;
	}
	return  nRet;
}

int FileUtils::FileSeek(FILE *pFile, int32_t unPos, SeekMode nMode)
{
	int nSeekMode = 0;
	if (SeekMode::SeekModeBegin == nMode)
	{
		nSeekMode = SEEK_SET;
		if (unPos < 0)//开始位置，这里肯定不能再往前了
		{
			return -1;
		}
	}
	else if (SeekMode::SeekModeCur == nMode)
	{
		nSeekMode = SEEK_CUR;
	}
	else if (SeekMode::SeekModeEnd == nMode)
	{
		if (unPos > 0)//事实上API是允许unpos>0，这代表将文件扩大.统一标准，这里不允许，避免逻辑问题
		{
			return -1;
		}
		nSeekMode = SEEK_END;
	}
	else
	{
		return -1;
	}

#if defined(_WIN32) || defined(_WIN64)
	return _fseeki64(pFile, unPos, nSeekMode);
#else
	return fseeko(pFile, unPos, nSeekMode);
#endif
}

int FileUtils::FileFlush(FILE *pFile)
{
	return fflush(pFile);
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
			if (0 != stricmp(fileDir.name + nDNameLen - nLenExt, pszExt))
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


int FileUtils::FileRename(const char *pszOldName, const char *pszNewName)
{
	return rename(pszOldName, pszNewName);
}