#pragma once
 /**
 * @file		Singleton.h
 * @brief		单利模式的头文件。
 * @author		duanqiang
 * @date		2020/09/21
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <iostream>
#if _MSC_VER >= 1700
	#include <mutex>
#else
	#include "CMutex.h"
#endif


template <typename T>
class CSingleton
{
public:
	~CSingleton() {};
	CSingleton() {};


	/**
		* @brief     获取实例
		* @note      
		* @returns   T*
		* @code      
		* 类实现：
		*	class AXXXX : public CSingleton<AXXXX>
		*	{
		*	 ........
		*	}
		*
		* 使用
		* AXXXX::GetInstance()->BBBB();
		* @endcode    
		* @since     2020/09/21
	*/
	static  T* GetInstance() 
	{
		m_mutex.lock();
		if (nullptr == m_pInstance)  //判断是否第一次调用
		{
			m_pInstance = new T;
		}
		m_mutex.unlock();
		return m_pInstance;

	}

	//Singleton(const Singleton&) = delete;
	//Singleton& operator=(const Singleton&) = delete;

private:
	static T * m_pInstance;
	static std::mutex m_mutex;

	
};

template <typename T>
T* CSingleton<T>::m_pInstance = nullptr;

template <typename T>
std::mutex CSingleton<T>:: m_mutex;



