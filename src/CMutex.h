#pragma once
 /**
 * @file		CMutex.h
 * @brief		VS2013֮�µİ汾�ǲ�֧��std::mutex.��װ����࣬���ڵ�ʹ��vs2010ʱ�򣬿��Ա���std::mutex.����ע�ⲻҪȥ��c++11�е����ࡣ
 *				����Ͳ��ܿ�ƽ̨����.ע������ļ�ֻ����VC����ʹ��,��Ҫ��Ϊ��VC�汾����������
 * @author		duanqiang
 * @date		2020/12/16
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


#include <iostream> 

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#if _MSC_VER < 1700

namespace std{

	class mutex 
	{
	public:
		mutex();
		mutex(const TCHAR *mutexName, LPSECURITY_ATTRIBUTES lpsaAttributes);
		mutex(const mutex& b);
		virtual ~mutex();
		mutex & operator=(const mutex&b)
		{
			return *this;
		}
		void lock();
		bool try_lock();
		long TryLockFor(const unsigned int dwMilliSecond);
		void unlock();
		bool IsMutexAbandoned()
		{
			return m_isMutexAbandoned;
		}
	private:
		/// Mutex
		HANDLE m_mutex;
		/// Creation Security Info
		LPSECURITY_ATTRIBUTES m_lpsaAttributes;
		/// Flag for whether this mutex is abandoned or not.
		bool m_isMutexAbandoned;
	};


	template<typename T>
	class lock_guard
	{
	public:
		lock_guard::lock_guard(mutex &mt)
			:m_mutex(mt)
		{
			m_mutex.lock();
		}

		~lock_guard()
		{
			m_mutex.unlock();
		}
	private:
		T &m_mutex;
	};
}
#endif

#else
#endif