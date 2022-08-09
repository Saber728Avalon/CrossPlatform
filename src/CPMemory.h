 /**
 * @file		CPMemory.h
 * @brief		��Ҫ��װ���ڴ�������ͷš�ʵ���ڴ�й©���
 * @author		duanqiang
 * @date		2022/02/13
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */
#pragma  once

#include <iostream>
#include <new>
#include <map>
#define  _USE_CP_MEMORY 1

#if defined(_USE_CP_MEMORY)



template<typename T>
T * CP_MEMORY_NEW()
{
	T *pT = NULL;
	void *pMem = NULL;
	try
	{
		pMem = operator new (sizeof(T));
		if (NULL == pMem)
		{
			return pT;
		}
		pT = new(pMem) T ();//placement new. ��new��C++��׼new.�����ܱ��Զ���汾���.���������ڴ棬ֻ����ָ��λ�õ��ú��ʵĹ��캯��
	} 
	catch(...)
	{
		if (NULL != pMem)
		{
			delete pMem;
			pMem = NULL;
		}
	}
	return pT;
}


template<typename T, typename Param1>
T * CP_MEMORY_NEW(Param1 param1)
{
	T *pT = NULL;
	void *pMem = NULL;
	try
	{
		pMem = operator new (sizeof(T));
		if (NULL == pMem)
		{
			return pT;
		}
		pT = new(pMem) T (param1);//placement new. ��new��C++��׼new.�����ܱ��Զ���汾���.���������ڴ棬ֻ����ָ��λ�õ��ú��ʵĹ��캯��
	} 
	catch(...)
	{
		if (NULL != pMem)
		{
			delete pMem;
			pMem = NULL;
		}
	}
	return pT;
}

template<typename T, typename Param1, typename Param2>
T * CP_MEMORY_NEW(Param1 param1, Param2 param2)
{
	T *pT = NULL;
	void *pMem = NULL;
	try
	{
		pMem = operator new (sizeof(T));
		if (NULL == pMem)
		{
			return pT;
		}
		pT = new(pMem) T (param1, param2);//placement new. ��new��C++��׼new.�����ܱ��Զ���汾���.���������ڴ棬ֻ����ָ��λ�õ��ú��ʵĹ��캯��
	} 
	catch(...)
	{
		if (NULL != pMem)
		{
			delete pMem;
			pMem = NULL;
		}
	}
	return pT;
}

#if !defined(NDEBUG)

struct CPMemInfo
{
	int nSize;
	std::string strInfo;
};


/**
	* @brief     ���ؼ�¼�ڴ������Ϣ��ȫ��map
	* @note      
	* @returns   std::map<void *, CPMemInfo>&
	* @code      
	* @endcode    
	* @since     2022/02/13
*/
std::map<void *, CPMemInfo>& GetDetectMap();


/**
	* @brief     ���û���ͷŵ��ڴ�
	* @note      
	* @returns   void
	* @code      
	* @endcode    
	* @since     2022/02/13
*/
void DumpCPMemInfo();

/**
	* @brief     ����new
	* @note      
	* @returns   void
	* @code      
	* @endcode    
	* @since     2022/02/13
*/
static void* operator new(size_t size, const char *file, int line)
{
	CPMemInfo memInfo;
	char chInfoBuf[512];

	void *pMem = operator new (size);
	if (NULL == pMem)
	{
		return NULL;
	}
	std::map<void *, CPMemInfo>& mapDetect = GetDetectMap();
	_snprintf_s(chInfoBuf, 512, (char *)"%s (%d)", file, line);

	memInfo.nSize = size;
	memInfo.strInfo = chInfoBuf;
	mapDetect[pMem]  = memInfo;
	return pMem;
}


/**
	* @brief     ����ʵ��malloc
	* @note      
	* @returns   void*
	* @param[in] size_t size
	* @param[in] const char * file
	* @param[in] int line
	* @code      
	* @endcode    
	* @since     2022/02/13
*/
static void* CPMalloc(size_t size, const char *file, int line)
{
	static std::map<void *, CPMemInfo> s_map;
	CPMemInfo memInfo;
	char chInfoBuf[512];

	void *pMem =  malloc(size);
	if (NULL == pMem)
	{
		return NULL;
	}
	std::map<void *, CPMemInfo>& mapDetect = GetDetectMap();
	_snprintf_s(chInfoBuf, 512, (char *)"%s (%d)", file, line);

	memInfo.nSize = size;
	memInfo.strInfo = chInfoBuf;
	mapDetect[pMem]  = memInfo;
	return pMem;
}

/**
	* @brief     ����ʵ��malloc
	* @note      
	* @returns   void*
	* @param[in] size_t size
	* @param[in] const char * file
	* @param[in] int line
	* @code      
	* @endcode    
	* @since     2022/02/13
*/
static void* CPCalloc(size_t count, size_t size, const char *file, int line)
{
	static std::map<void *, CPMemInfo> s_map;
	CPMemInfo memInfo;
	char chInfoBuf[512];
	int nCount = 0;

	nCount = count * size;
	void *pMem =  malloc(nCount);
	if (NULL == pMem)
	{
		return NULL;
	}
	std::map<void *, CPMemInfo>& mapDetect = GetDetectMap();
	_snprintf_s(chInfoBuf, 512, (char *)"%s (%d)", file, line);

	memInfo.nSize = nCount;
	memInfo.strInfo = chInfoBuf;
	mapDetect[pMem]  = memInfo;
	return pMem;
}

//����delete
static void operator delete(void *pMem)
{
	std::map<void *, CPMemInfo>& mapDetect = GetDetectMap();
	auto iter = mapDetect.find(pMem);
	if (iter != mapDetect.end())
	{
		mapDetect.erase(iter);
	}
	free(pMem);
}

//����delete
static void operator delete[](void *pMem)
{
	std::map<void *, CPMemInfo>& mapDetect = GetDetectMap();
	auto iter = mapDetect.find(pMem);
	if (iter != mapDetect.end())
	{
		mapDetect.erase(iter);
	}
	free(pMem);
}

#define new new(__FILE__, __LINE__)
#define malloc(xxx) CPMalloc(xxx, __FILE__, __LINE__)
#define calloc(xxx, yyy) CPCalloc(xxx, yyy, __FILE__, __LINE__)

#endif

#endif