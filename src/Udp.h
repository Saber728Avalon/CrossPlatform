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

//���ͳ�ʱ
#define UDP_ERROR_TIME_OUT -2

//�����׽���ʧ��
#define UDP_SOCKET_CREATE_FAIL -1


//����������ʧ��
#define UDP_CREATE_SERVER_BIND_FAIL -1
//����������ʧ��
#define UDP_CREATE_SERVER_LISTEN_FAIL -2
//�����������ɹ�
#define UDP_CREATE_SERVER_SUCCESS 1


//�õ����ݰ�ʧ��
#define UDP_RECVDATA_ERROR_FAIL -1
//���ܵ������ݰ�Ϊ��
#define UDP_RECVDATA_NO_DATA 0
//�������ݰ��ɹ�
#define UDP_RECVDATA_SUCCESS 1


//�������ݰ�ʱ�����ݰ�Ϊ��
#define UDP_SENDDATA_ERROR_NO_INFO -1
//�������ݰ�ʧ��
#define UDP_SENDDATA_ERROR_FAIL -2
//�������ݰ��ɹ�
#define UDP_SENDDATA_SUCCESS 1


typedef unsigned int SOCKET;

class CUdp
{
public:
	CUdp();
	~CUdp();

	//���ó�ʱ
	void InitSocket(unsigned int unTimeOut);

	//�������ݰ�
	int Send( char *dataBuffer, int nSize, char *pszIP, int nPort);

	//�������ݰ�
	int Recv(char *dataBuffer, int nSize, char *pszIP);

	//���������� nPort:�󶨵Ķ˿� bSync:�Ƿ��첽���� pszBindIP:�󶨶�Ӧ��IP(�������ʱ�����ǿ���ָ��ĳ������)
	int CreateServer(int nPort, bool bSync, char *pszBindIP);


private:
		//��ӡTcpͨѶ����־
	void WriteLog(char *pszErrorMsg);

	//�����׽���
	SOCKET CreateSocket();

	//��������,��װ���е�ϵͳ�ķ�������
	int SendData(char *dataBuffer, int nSize, char *pszIP, int nPort);
	
	//��������,��װ���е�ϵͳ�Ľ�������
	int RecvData(char *dataBuffer, int nSize, char *pszIP);
	

	unsigned int m_nTimeOut;//����ϵͳ��ʱ��ʱ�䳤��
	
	SOCKET m_nSocket;//����õ��׽��֣��������ͻ��߽�������
	SOCKET m_nListenSocket;//�������������׽���
};

#endif