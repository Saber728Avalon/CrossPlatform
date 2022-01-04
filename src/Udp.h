// Tcp.h: interface for the CTcp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDP_H__C1EE53E6_1984_4560_BEAB_FE04B0EE3698__INCLUDED_)
#define AFX_UDP_H__C1EE53E6_1984_4560_BEAB_FE04B0EE3698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef WINDOWS_32_

#include <winsock2.h>
#include <stdio.h>




#endif

//发送超时
#define UDP_ERROR_TIME_OUT -2

//创建套接字失败
#define UDP_SOCKET_CREATE_FAIL -1


//创建服务器失败
#define UDP_CREATE_SERVER_BIND_FAIL -1
//侦听服务器失败
#define UDP_CREATE_SERVER_LISTEN_FAIL -2
//创建服务器成功
#define UDP_CREATE_SERVER_SUCCESS 1


//得到数据包失败
#define UDP_RECVDATA_ERROR_FAIL -1
//接受到的数据包为空
#define UDP_RECVDATA_NO_DATA 0
//发送数据包成功
#define UDP_RECVDATA_SUCCESS 1


//发送数据包时候，数据包为空
#define UDP_SENDDATA_ERROR_NO_INFO -1
//发送数据包失败
#define UDP_SENDDATA_ERROR_FAIL -2
//发送数据包成功
#define UDP_SENDDATA_SUCCESS 1


typedef unsigned int SOCKET;

class CUdp
{
public:
	CUdp();
	~CUdp();

	//设置超时
	void InitSocket(unsigned int unTimeOut);

	//发送数据包
	int Send( char *dataBuffer, int nSize, char *pszIP, int nPort);

	//接受数据包
	int Recv(char *dataBuffer, int nSize, char *pszIP);

	//创建服务器 nPort:绑定的端口 bSync:是否异步侦听 pszBindIP:绑定对应的IP(多个网卡时候，我们可以指定某个网卡)
	int CreateServer(int nPort, bool bSync, char *pszBindIP);


private:
		//打印Tcp通讯的日志
	void WriteLog(char *pszErrorMsg);

	//创建套接字
	SOCKET CreateSocket();

	//发送数据,封装所有的系统的发送数据
	int SendData(char *dataBuffer, int nSize, char *pszIP, int nPort);
	
	//接受数据,封装所有的系统的接收数据
	int RecvData(char *dataBuffer, int nSize, char *pszIP);
	

	unsigned int m_nTimeOut;//保存系统超时的时间长短
	
	SOCKET m_nSocket;//保存得到套接字，用来发送或者接受数据
	SOCKET m_nListenSocket;//用来保存侦听套接字
};

#endif