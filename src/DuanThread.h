#pragma once
 /**
 * @file		DuanThread.h
 * @brief		跨平台封装创建挂起线程，结束线线程
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
    	* @brief     初始化线程
    	* @note      
    	* @returns   
    	* @param[in] func 自己的线程函数 函数必须是typedef void (*pFunc)(void *pVoid);
    	* @param[in] param 传入参数的结构体
    	* @param[in] bAutoDelete 自析构标志。如果是孤儿线程，即创建之后就不管的线程,为true。 需要自己管理生命周期，则为false
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
    	* @brief     线程开始运行。这里之所以不在构造之后立即执行。就是为了可以支持线程池
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
    	* @brief     等待线程结束
    	* @note      这个和自析构不能同时使用
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
    	* @brief     挂起线程
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
    	* @brief     线程恢复运行
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
    	* @brief     强制结束线程
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
		* @brief     得到当前线程的状态
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
		//这个函数之后，不能进行任何操作。因为对象可能已经析构了
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

