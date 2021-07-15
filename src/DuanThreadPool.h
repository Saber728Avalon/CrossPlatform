#pragma once
 /**
 * @file		TransDataHttps.h
 * @brief		�̳߳ع�����,ע���������е��̴߳�����������typedef void (*pFunc)(void *pVoid);
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
		* @note      ע������ֻ�Ǹ������̳߳صĹ�����������Ҫ��ͬһ��������̳߳ش����������/�̳߳��е��߳��˳�����Ҫ���̺߳��������Լ�ʵ��
		* @returns   void
		* @param[in] nMinThreadCount,�̳߳���С���߳�����,ע���������޽��̳߳ء�������û���߳������ߵ�.
		* @param[in] func �̴߳�����.�ú���������typedef void (*pFunc)(void *pVoid)��������ʽ�ĺ���
		* @param[in] param ���߳����洫��Ĳ���
		* @code   
		*      void Func(void *pVoid) {.....} //�̴߳�����
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
		* @brief     �ȴ����е��̺߳����������
		* @note      ע�⣬�ú����ڲ�ֻ���ж��߳����е�״̬��������ô�����̵߳��˳���Ҫ�Լ����̺߳���ʵ�����Լ�ʵ��
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
		* @brief     ����һ���߳�
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
		* @brief     �Ƴ�һ���߳�
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
		* @brief     �õ��̳߳صĴ�С
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

