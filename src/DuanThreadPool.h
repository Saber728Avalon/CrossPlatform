#pragma once
 /**
 * @file		TransDataHttps.h
 * @brief		线程池管理类,注意这里所有的线程处理函数必须是typedef void (*pFunc)(void *pVoid);
 * @author		duanqiang
 * @date		2021/01/06
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


#include "DuanThread.h"
#include <iostream>
#include <vector>


template<typename _FUNC, typename _PARAM>
class DuanThreadPool
{
public:
	~DuanThreadPool(void){};
	DuanThreadPool() {};

	/**
		* @brief     Start
		* @note      注意这里只是负责做线程池的管理。因此如果你要做同一批任务的线程池处理，任务分配/线程池中的线程退出，都要在线程函数体中自己实现
		* @returns   void
		* @param[in] nMinThreadCount,线程池最小的线程数量,注意这里是无界线程池。所以是没有线程数上线的.
		* @param[in] func 线程处理函数.该函数必须是typedef void (*pFunc)(void *pVoid)，这种形式的函数
		* @param[in] param 往线程里面传入的参数
		* @code   
		*      void Func(void *pVoid) {.....} //线程处理函数
		*		DuanThreadPool<void*, void*> *ptr = new DuanThreadPool<void*, void*>;
		* @endcode    
		* @since     2021/01/06
	*/
	void Start(int nMinThreadCount, _FUNC func, _PARAM param)
	{
		m_nMinThread = nMinThreadCount;
		for (int i = 0; i < m_nMinThread; i++)
		{
			CDuanThread<_FUNC, _PARAM> *pTmpThread = new CDuanThread<_FUNC, _PARAM>(func, param, true);
			pTmpThread->Start();
			m_vectThreadPool.push_back(pTmpThread);
		}
	}



	/**
		* @brief     等待所有的线程函数运行完成
		* @note      注意，该函数内部只是判断线程运行的状态。所以怎么进行线程的退出，要自己在线程函数实现中自己实现
		* @returns   void
		* @code      
		* @endcode    
		* @since     2021/01/06
	*/
	void JoinAll()
	{
		while (true)
		{
			int nCountRun = 0;
			for (int i = 0; i < m_nMinThread; i++)
			{
				CDuanThread<_FUNC, _PARAM>* pTmpThread = m_vectThreadPool[i];
				if ( DuanThreadState::DuanThreadStateStop != pTmpThread->GetThreadState())
				{
					nCountRun++;
				}
			}
			if (0 == nCountRun)
			{
				break;
			}
		}
	}

	/**
		* @brief     增加一个线程
		* @note      
		* @returns   void
		* @param[in] CDuanThread<_FUNC
		* @param[in] _PARAM> * pThread
		* @code      
		* @endcode    
		* @since     2021/01/06
	*/
	void AddThread(CDuanThread<_FUNC, _PARAM> *pThread)
	{
		m_vectThreadPool.push_back(pThread);
	}


	/**
		* @brief     移除一个线程
		* @note      
		* @returns   void
		* @param[in] CDuanThread<_FUNC
		* @param[in] _PARAM> * pThread
		* @code      
		* @endcode    
		* @since     2021/01/06
	*/
	void RemoveThread(CDuanThread<_FUNC, _PARAM> *pThread)
	{
		for (auto iter = m_vectThreadPool.begin(); iter != m_vectThreadPool.end();)
		{
			CDuanThread<_FUNC, _PARAM>* pTmpThread = m_vectThreadPool[i];
			if (0 == memcmp(pTmpThread, pThread, sizeof(pThread)))
			{
				iter = m_vectThreadPool.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}



	/**
		* @brief     得到线程池的大小
		* @note      
		* @returns   uint32_t
		* @code      
		* @endcode    
		* @since     2021/02/02
	*/
	uint32_t ThreadPoolSize()
	{
		return m_vectThreadPool.size();
	}

private:
	int m_nMinThread;
	std::vector<CDuanThread<_FUNC, _PARAM>* > m_vectThreadPool;
		
};

