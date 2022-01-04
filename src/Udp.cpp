/************************************************************************/
/*作用： 封装用来发送或者数据包的套接字，适用于windows, linux
                                                                     */
/************************************************************************/

#include "Udp.h"

#if WINDOWS_32_ || WINDOWS_64_
	#include <winsock2.h>
	#include <stdio.h>
	#pragma comment(lib, "ws2_32.lib")
	#pragma warning(disable:4067)
#endif

#if LINUX_32_ || LINUX_64_
	#include <stdio.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <time.h>
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//生成日志时候路径
#if WINDOWS_32_ || WINDOWS_64_
static char *pLogPath = "udp.log";
#endif

#if LINUX_32_ || LINUX_64_
static char *pLogPath = "udp.log"
#endif


CUdp::CUdp(void)
{
	m_nSocket = 0;
	m_nListenSocket = 0;
	m_nTimeOut = 5000;



#if WINDOWS_32_ || WINDOWS_64_
	WSADATA wsaData;
	int nRet = 0;

	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0 )
	{
		WriteLog("[WSAStartup] fail");
	}
#endif
}


CUdp::~CUdp(void)
{
	if (m_nSocket != 0)
	{
#if WINDOWS_32_ || WINDOWS_64_
		closesocket(m_nSocket);
#endif

#if LINUX_32_ || LINUX_64_
		close(m_nSocket);
#endif
	}
	if (m_nListenSocket != 0)
	{
#if WINDOWS_32_ || WINDOWS_64_
                closesocket(m_nListenSocket);
#endif

#if LINUX_32_ || LINUX_64_
                close(m_nListenSocket);
#endif
	}

#if WINDOWS_32_ || WINDOWS_64_
		WSACleanup();
#endif
}


void CUdp::InitSocket(unsigned int unTimeOut)
{
	m_nTimeOut = unTimeOut;
}

SOCKET CUdp::CreateSocket()
{
	SOCKET nSocket = -1;
	char buffer[256];

#if WINDOWS_32_ || WINDOWS_64_
	nSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (INVALID_SOCKET == nSocket)
	{
#if _DEBUG || DEBUG

		int nErrorCode = 0;
		nErrorCode = GetLastError();

		WriteLog("[CreateSocket] fail");

		sprintf(buffer, "%s %d", " GetLastError() : ", nErrorCode);
		WriteLog(buffer);
#endif

		return UDP_SOCKET_CREATE_FAIL;
	}
#endif

#if LINUX_32_ || LINUX_64_
	nSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (-1 == nSocket)
	{
#if _DEBUG || DEBUG
		WriteLog("[CreateSocket] fail");
		sprintf(buffer, "error number:%d,  error info: %s", errno, strerror(errno));
		WriteLog(buffer);
#endif
		return UDP_SOCKET_CREATE_FAIL;
	}
#endif
	
	return nSocket;

}



int CUdp::CreateServer(int nPort, bool bSync, char *pszBindIP)
{
	int nRet;
	SOCKET nSocket;
	struct sockaddr_in addr;
	char pBuffer[256];


	nSocket = CreateSocket();
	if (UDP_SOCKET_CREATE_FAIL == nSocket)
	{
		return UDP_SOCKET_CREATE_FAIL;
	}

	addr.sin_family = AF_INET;
	if (NULL == pszBindIP)
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		addr.sin_addr.s_addr = inet_addr(pszBindIP);
	}
	addr.sin_port = htons(nPort);


	//绑定套接字
#if WINDOWS_32_ || WINDOWS_64_
	
	nRet = bind(nSocket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	
	if (SOCKET_ERROR == nRet)
	{
#if _DEBUG || DEBUG
		int nErrorCode = 0;
		nErrorCode = GetLastError();
		sprintf(pBuffer, "[CreateServer] fail on bind!port:%d", nPort);
		WriteLog(pBuffer);

		sprintf(pBuffer, " GetLastError() : %d", nErrorCode);
		WriteLog(pBuffer);
#endif
		return UDP_CREATE_SERVER_BIND_FAIL;
	}
	if (true == bSync)
	{
		int iMode = 1; // 0阻塞， 非0不阻塞
		ioctlsocket(nSocket, FIONBIO, (u_long *)&iMode);
	}
#endif


#if LINUX_32_ || LINUX_64_
	
	nRet = bind(nSocket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	
	if (-1 == nRet)
	{
#if _DEBUG || DEBUG
		sprintf(pBuffer, "[CreateServer] fail on bind!port:%d", nPort);
		WriteLog(pBuffer);
		sprintf(pBuffer, "error number:%d,  error info: %s", errno, strerror(errno));
		WriteLog(pBuffer);
#endif
		return UDP_CREATE_SERVER_BIND_FAIL;
	}

	if (true == bSync)
	{
		int flags = fcntl(nSocket, F_GETFL, 0);
		fnctl(nSocket, F_SETFL, flags | O_NONBLOCK);
	}
#endif

	//保存侦听套接字
	m_nListenSocket = nSocket;

	return UDP_CREATE_SERVER_SUCCESS;
}



int CUdp::Recv(char *dataBuffer, int nSize, char *pszIP)
{

	unsigned int nTimeSend = 0;//已经接收的时间
	int nRet = 0;	
	int nSentLength = 0;
	int nBeginTimeSend = 0;
	int nEndTimeSend = 0;
	
	if (NULL == dataBuffer)
	{
		return 0;
	}
	
	//开始接收时间
#if WINDOWS_32_ || WINDOWS_64_
	;
	nBeginTimeSend = GetTickCount();
#endif
	
#if LINUX_32_ || LINUX_64_
	;
	struct timeval te;
	gettimeofday(&te, NULL);
	nBeginTimeSend = te.tv_usec;
	
#endif

	while (1)
	{
		nRet = this->RecvData(dataBuffer, nSize, pszIP);
		
		if (nRet > 0)
		{
			return nRet;
		}
		else if (UDP_RECVDATA_NO_DATA == nRet)//接收到的数据包为空
		{
			
			//现在时间
#if WINDOWS_32_ || WINDOWS_64_
			;
			nEndTimeSend = GetTickCount();
#endif
			
#if LINUX_32_ || LINUX_64_
			;
			struct timeval te;
			gettimeofday(&te, NULL);
			nEndTimeSend = te.tv_usec;
			
#endif
			nTimeSend = nEndTimeSend - nBeginTimeSend;
			if (nTimeSend >= m_nTimeOut)
			{
				
#if DEBUG || _DEBUG
				char errorBuffer[256];
				memset(errorBuffer, '\0', 256);
				WriteLog("[Recv] Recv data time out");
#if WINDOWS_32_ || WINDOWS_64_
				sprintf(errorBuffer," Info:%d", GetLastError());
				WriteLog(errorBuffer);
#endif
#if LINUX_32_ || LINUX_64_
				sprintf(errorBuffer, "error number:%d,  error info: %s", errno, strerror(errno));
				WriteLog(errorBuffer);
#endif
#endif
				return UDP_ERROR_TIME_OUT;
			}
		}
		else
		{
			WriteLog("[Recv] unknown error");
			return UDP_RECVDATA_ERROR_FAIL;
		}
	}
}


int CUdp::RecvData(char *dataBuffer, int nSize, char *pszIP)
{
	unsigned int nReturnDataLength = -1;
	char pBuffer[256];
	struct sockaddr_in addr;
	int nLen = sizeof(addr);
	
#if WINDOWS_32_ || WINDOWS_64_
	
	nReturnDataLength = recvfrom(m_nListenSocket, dataBuffer, nSize, 0, (struct sockaddr *)&addr, &nLen);
	
	if (SOCKET_ERROR == nReturnDataLength)
	{
#if _DEBUG || DEBUG
		sprintf(pBuffer, "Recv data fail! errorcode:%d\n", WSAGetLastError());
		WriteLog(pBuffer);
#endif
		return UDP_RECVDATA_ERROR_FAIL;
	}

	if (0 == nReturnDataLength)
	{
		return UDP_RECVDATA_NO_DATA;
	}
#endif

	
#if LINUX_32_ || LINUX_64_
	
	nReturnDataLength = recvfrom(m_nListenSocket, dataBuffer, nSize, 0, (struct sockaddr *)&addr, &nLen);
	
	if (-1 == nReturnDataLength)
	{
#if _DEBUG || DEBUG
		sprintf(pBuffer, "Recv data fail!\n");
		WriteLog(pBuffer);
		sprintf(pBuffer, "error number:%d,  error info: %s", errno, strerror(errno));
		WriteLog(pBuffer);
#endif
		return UDP_RECVDATA_ERROR_FAIL;
	}
	
	if (0 == nReturnDataLength)
	{
		return UDP_RECVDATA_NO_DATA;
	}
#endif
	char *pIP = inet_ntoa(addr.sin_addr);
	memcpy(pszIP, pIP, strlen(pIP));

	return nReturnDataLength;
}


int CUdp::SendData(char *dataBuffer, int nSize, char *pszIP, int nPort)
{
	int nRet = 0;
	unsigned int byteSendSuccess = 0;
	char pBuffer[256];
	struct sockaddr_in addr;

	memset(pBuffer, '\0', 256);

	if (NULL == dataBuffer || 0 == nSize)
	{
		return UDP_SENDDATA_ERROR_NO_INFO;
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(pszIP);
	addr.sin_port = htons(nPort);

	//开始发送数据包
#if WINDOWS_32_ || WINDOWS_64_
	
	nRet = sendto(m_nSocket, dataBuffer, nSize, 0, (struct sockaddr *)&addr, sizeof(addr));
	
	if (SOCKET_ERROR == nRet)
	{
#ifdef _DEBUG || DEBUG
		int nErrorCode = 0;
		nErrorCode = GetLastError();
		sprintf(pBuffer, "Send data fail!\n");
		WriteLog(pBuffer);
		sprintf(pBuffer, "GetLastError() : %d", nErrorCode);
		WriteLog(pBuffer);

#endif
		return UDP_SENDDATA_ERROR_FAIL;
	}
#endif

#if LINUX_32_ || LINUX_64_
	
	nRet = write(m_nSocket, dataBuffer, nSize);
	
	if (-1 == nRet)
	{
#if _DEBUG || DEBUG
		sprintf(pBuffer, "Send data fail!\n");
		WriteLog(pBuffer);
		sprintf(pBuffer, "error number:%d,  error info: %s", errno, strerror(errno));
		WriteLog(pBuffer);
#endif
		return UDP_SENDDATA_ERROR_FAIL;
	}
#endif
	
	//得到实际发送的长度
	byteSendSuccess = nRet;

#if _DEBUG || DEBUG
	sprintf(pBuffer, "send data success! length: %d", byteSendSuccess);
#endif

	return byteSendSuccess;
}

int CUdp::Send(char *dataBuffer, int nSize, char *pszIP, int nPort)
{
	int nBeginTimeSend = 0;
	int nEndTimeSend = 0;
	unsigned int nTimeSend = 0;//已经发送的时间
	int nRet = 0;	
	int nSentLength = 0;

	if (NULL == dataBuffer)
	{
		return UDP_SENDDATA_ERROR_NO_INFO;
	}

//开始发送时间
#if WINDOWS_32_ || WINDOWS_64_
		;
	nBeginTimeSend = GetTickCount();
#endif
	
#if LINUX_32_ || LINUX_64_
	;
	struct timeval te;
	gettimeofday(&te, NULL);
	nBeginTimeSend = te.tv_usec;
	
#endif
	m_nSocket = CreateSocket();

	while (1)
	{
		nRet = this->SendData(dataBuffer + nSentLength, nSize, pszIP, nPort);
		nSentLength += nRet;
		if (nSentLength == nSize)
		{
			return nRet;
		}
		else
		{

			//现在时间
#if WINDOWS_32_ || WINDOWS_64_
			;
			nEndTimeSend = GetTickCount();
#endif
			
#if LINUX_32_ || LINUX_64_
			;
			struct timeval te;
			gettimeofday(&te, NULL);
			nEndTimeSend = te.tv_usec;
			
#endif
			nTimeSend = nEndTimeSend - nBeginTimeSend;
			if (nTimeSend >= m_nTimeOut)
			{

#if DEBUG || _DEBUG
				char errorBuffer[256];
				memset(errorBuffer, '\0', 256);
				WriteLog("[Send] Send data time out");
#if WINDOWS_32_ || WINDOWS_64_
				sprintf(errorBuffer," Info:%d", GetLastError());
				WriteLog(errorBuffer);
#endif
#if LINUX_32_ || LINUX_64_
				sprintf(errorBuffer, "error number:%d,  error info: %s", errno, strerror(errno));
				WriteLog(errorBuffer);
#endif
#endif
				return UDP_ERROR_TIME_OUT;
			}
		}
	}

}


void CUdp::WriteLog(char *pszErrorMsg)
{
	FILE *pFile = NULL;
	char buffer[256];
	int nLength = 0, nRet = 0;
	int nFileIsOpen = 1;
	
	pFile = fopen(pLogPath, "ab+");

	if (NULL == pFile)
	{
		return;
	}

	fseek(pFile, 0, SEEK_END);
	sprintf(buffer, " %s info: %s \n", __DATE__" at "__TIME__" ", pszErrorMsg);

	nLength = strlen(buffer);
	nRet = fwrite(buffer, 1, nLength, pFile); 

	fclose(pFile);
	return;
}

