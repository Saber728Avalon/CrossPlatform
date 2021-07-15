#pragma once
 /**
 * @file		DuanThread.h
 * @brief		��ƽ̨��װ���������̣߳��������߳�
 * @author		duanqiang
 * @date		2020/09/21
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


#include <iostream>
#include "CommFunction.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <process.h>
#elif defined(__linux__)
    #include <pthread.h>
#elif defined(__APPLE__)
    #include <pthread.h>
#else
#endif

typedef enum tag_DuanThreadState
{
    DuanThreadStateInit,
    DuanThreadStateRun,
    DuanThreadStateStop,
    DuanThreadStateSuspend
}  DuanThreadState;

template<typename _FUNC, typename _PARAM>
class CDuanThread
{
public:
    
    /**
    	* @brief     ��ʼ���߳�
    	* @note      
    	* @returns   
    	* @param[in] func �Լ����̺߳��� ����������typedef void (*pFunc)(void *pVoid);
    	* @param[in] param ��������Ľṹ��
    	* @param[in] bAutoDelete ��������־������ǹ¶��̣߳�������֮��Ͳ��ܵ��߳�,Ϊtrue�� ��Ҫ�Լ������������ڣ���Ϊfalse
    	* @code      
		*	CDuanThread<void*, struct xxxx> *pxxx = new CDuanThread<void*, struct xxxx>((void *)Runnable, xxx, true)
    	* @endcode    
    	* @since     2020/09/21
    */
    CDuanThread(_FUNC func, _PARAM param, bool bAutoDelete){
        m_func = func;
        m_param = param;
        m_state = DuanThreadStateInit;
        m_bAutoDelete = bAutoDelete;

#if defined(_WIN32) || defined(_WIN64)
#elif defined(__linux__)
        m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;
        m_pthreadCond = PTHREAD_COND_INITIALIZER;
#elif defined(__APPLE__)

#else
#endif
    }
	~CDuanThread() 
    {
#if defined(_WIN32) || defined(_WIN64)
        _endthread();
#elif defined(__linux__)
#elif defined(__APPLE__)
        
#else
#endif
       
    }

	
    /**
    	* @brief     �߳̿�ʼ���С�����֮���Բ��ڹ���֮������ִ�С�����Ϊ�˿���֧���̳߳�
    	* @note      
    	* @returns   void
    	* @code      
    	* @endcode    
    	* @since     2020/09/21
    */
    void Start()
    {
#if defined(_WIN32) || defined(_WIN64)
        m_pid = _beginthread(StartThread, 0, (void*)this);
#elif defined(__linux__)
        pthread_create(&m_pid, NULL, StartThread, (void*)this);
#elif defined(__APPLE__)
        pthread_create(&m_pid, NULL, StartThread, (void*)this);
#else
#endif
    }

    
    /**
    	* @brief     �ȴ��߳̽���
    	* @note      ���������������ͬʱʹ��
    	* @returns   void
    	* @code      
    	* @endcode    
    	* @since     2020/09/21
    */
    void Join()
    {
        while (DuanThreadStateStop != m_state)
        {
            DQSleep(100);
        }
    }

	
    /**
    	* @brief     �����߳�
    	* @note      
    	* @returns   void
    	* @code      
    	* @endcode    
    	* @since     2020/09/21
    */
    void Suspend()
    {
        if (DuanThreadStateRun != m_state)
        {
            return;
        }

#if defined(_WIN32) || defined(_WIN64)
        SuspendThread(m_pid);
#elif defined(__linux__)
        pthread_mutex_lock(&m_pthreadMutex);
        pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
        pthread_mutex_unlock(&m_pthreadMutex);
#elif defined(__APPLE__)
        pthread_mutex_lock(&m_pthreadMutex);
        pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
        pthread_mutex_unlock(&m_pthreadMutex);
#else
#endif
        m_state = DuanThreadStateSuspend;
    }


    /**
    	* @brief     �ָ̻߳�����
    	* @note      
    	* @returns   void
    	* @code      
    	* @endcode    
    	* @since     2020/09/21
    */
    void Resume()
    {
        if (DuanThreadStateSuspend != m_state)
        {
            return;
        }
#if defined(_WIN32) || defined(_WIN64)
        ResumeThread(m_pid);
#elif defined(__linux__)
        pthread_mutex_lock(&m_pthreadMutex);
        pthread_cond_signal(&m_pthreadCond);
        pthread_mutex_unlock(&m_pthreadMutex);
#elif defined(__APPLE__)
        pthread_mutex_lock(&m_pthreadMutex);
        pthread_cond_signal(&m_pthreadCond);
        pthread_mutex_unlock(&m_pthreadMutex);
#else
#endif
        if (DuanThreadStateInit != m_state && DuanThreadState::DuanThreadStateStop != m_state)
        {
            m_state = DuanThreadStateRun;
        }
    }


    /**
    	* @brief     ǿ�ƽ����߳�
    	* @note      
    	* @returns   void
    	* @code      
    	* @endcode    
    	* @since     2020/09/21
    */
    void Terminate()
    {
#if defined(_WIN32) || defined(_WIN64)
        TerminateThread(m_pid, 0);
#elif defined(__linux__)
        pthread_cancel(m_pid);
#elif defined(__APPLE__)
        pthread_cancel(m_pid);
#else
#endif
    }

		/**
		* @brief     �õ���ǰ�̵߳�״̬
		* @note      
		* @returns   DuanThreadState
		* @code      
		* @endcode    
		* @since     2021/01/06
	*/
	DuanThreadState GetThreadState() 
	{
		return m_state;
	}

private:

    void DeleteThis() {delete this;}

#if defined(_WIN32) || defined(_WIN64)
    static void StartThread(void* param)
#elif defined(__linux__)
    static void* StartThread(void* param)
#elif defined(__APPLE__)
    static void* StartThread(void* param)
#else
#endif
    {
        CDuanThread *pThread = (CDuanThread *)param;
        typedef void (*TempFunc)(_PARAM param);
        TempFunc tmpFunc = (TempFunc)pThread->m_func;
        
        pThread->m_state = DuanThreadStateRun;
        try
        {
            tmpFunc(pThread->m_param);
        }
        catch (...)
        {
        }
       
        
       
        pThread->m_state = DuanThreadStateStop;
		//�������֮�󣬲��ܽ����κβ�������Ϊ��������Ѿ�������
        if (true == pThread->m_bAutoDelete)
        {
            pThread->DeleteThis();
        }
      

#if defined(_WIN32) || defined(_WIN64)
       
#elif defined(__linux__)
        return NULL;
#elif defined(__APPLE__)
        return NULL;
#else
#endif
    };




private:

#if defined(_WIN32) || defined(_WIN64)
    uintptr_t m_pid;
#elif defined(__linux__)
    pthread_t m_pid;
    pthread_mutex_t m_pthreadMutex;
    pthread_cond_t m_pthreadCond;
#elif defined(__APPLE__)
    pthread_t m_pid;
    pthread_mutex_t m_pthreadMutex;
    pthread_cond_t m_pthreadCond;
#else
#endif
	
	_PARAM m_param;
	_FUNC m_func;
    DuanThreadState m_state;
    bool m_bAutoDelete;
};

