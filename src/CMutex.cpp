#include "CMutex.h"
#include <ObjBase.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#if _MSC_VER < 1700

std::string DQCreateUUID()
{
	std::string strUUID;
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	char chBufFormat[] = {'%', '0', '8', 'X', '%', '0', '4', 'X', '%', '0', '4', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '%', '0', '2', 'X', '\0'};

	if (S_OK == hr)
	{
		char chBuf[64] = { 0 };
		sprintf(chBuf,  chBufFormat
			, guid.Data1, guid.Data2, guid.Data3
			, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3]
		, guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);
		strUUID = chBuf;
	}
	return strUUID;
}

namespace std
{

	mutex::mutex()
	{
		m_isMutexAbandoned=false;
		m_lpsaAttributes=NULL;
		m_mutex=CreateMutexA(m_lpsaAttributes,m_isMutexAbandoned, DQCreateUUID().c_str());
	}

	mutex::mutex(const TCHAR *mutexName, LPSECURITY_ATTRIBUTES lpsaAttributes) 
	{
		m_isMutexAbandoned=false;
		m_lpsaAttributes=lpsaAttributes;
		m_mutex=CreateMutex(lpsaAttributes,FALSE,mutexName);
	}
	mutex::mutex(const mutex& b)
	{
		m_isMutexAbandoned=false; 
		m_lpsaAttributes=b.m_lpsaAttributes;
		m_mutex=CreateMutex(m_lpsaAttributes,FALSE,NULL);
	}

	mutex::~mutex()
	{
		CloseHandle(m_mutex);
	}


	// Mutex.cpp
	void mutex::lock()
	{
		bool returnVal = true;
		unsigned long res=WaitForSingleObject(m_mutex, INFINITE);
		if(res=WAIT_ABANDONED)
		{
			m_isMutexAbandoned=true;
			returnVal=false; 
		}
		return ;
	}
	bool mutex::try_lock()
	{
		long ret=0;
		unsigned long mutexStatus= WaitForSingleObject(m_mutex,0);
		if(mutexStatus== WAIT_OBJECT_0)
			ret=1;
		else if(mutexStatus==WAIT_ABANDONED)
			m_isMutexAbandoned=true;
		return ret;
	}
	long mutex::TryLockFor(const unsigned int dwMilliSecond)
	{
		long ret=0; 
		unsigned long mutexStatus= WaitForSingleObject(m_mutex,dwMilliSecond);
		if(mutexStatus==WAIT_OBJECT_0)
			ret=1;
		else if(mutexStatus==WAIT_ABANDONED)
			m_isMutexAbandoned=true;
		return ret;
	}


	void mutex::unlock()
	{
		ReleaseMutex(m_mutex);
	} 

}

#endif


#else
#endif