#pragma once
#include <iostream>
#include <memory>
#include <queue>
#if _MSC_VER >= 1700
#include <stdint.h>
#include <mutex>
#else
#include "CMutex.h"
#endif

namespace Duan
{
	template<class T>
	class CBaseSafeQueue
	{
	public:
		void Push(std::shared_ptr<T> ptrMsg)
		{
			std::lock_guard<std::mutex> lockGuard(m_mutex);
			if (NULL == ptrMsg)
			{
				return;
			}

			m_ptrMsgQueue.push(ptrMsg);
		}

		std::shared_ptr<T> Pop()
		{
			std::lock_guard<std::mutex> lockGuard(m_mutex);
			if (m_ptrMsgQueue.size() <= 0)
			{
				return NULL;
			}
			std::shared_ptr<T> ptrMsg = m_ptrMsgQueue.front();
			m_ptrMsgQueue.pop();
			return ptrMsg;
		}

		int GetCount()
		{
			return m_ptrMsgQueue.size();
		}

	private:
		std::queue<std::shared_ptr<T>> m_ptrMsgQueue;
		std::mutex m_mutex;
	};
}


