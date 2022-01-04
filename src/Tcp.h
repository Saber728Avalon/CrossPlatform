// Tcp.h: interface for the CTcp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCP_H__C1EE53E6_1984_4560_BEAB_FE04B0EE3698__INCLUDED_)
#define AFX_TCP_H__C1EE53E6_1984_4560_BEAB_FE04B0EE3698__INCLUDED_

#ifdef _MSC_VER

#include <winsock2.h>
#include <stdio.h>

#endif


//���ͳ�ʱ
#define ERROR_TIME_OUT -2



//�����׽���ʧ��
#define SOCKET_CREATE_FAIL -1

//����Ŀ��IPʧ��
#define CONNECT_FAIL -1
//����Ŀ��IP�ɹ�
#define CONNECT_SUCCESS 1


//����������ʧ��
#define CREATE_SERVER_BIND_FAIL -1
//����������ʧ��
#define CREATE_SERVER_LISTEN_FAIL -2
//�����������ɹ�
#define CREATE_SERVER_SUCCESS 1

//�������ݰ�ʱ�����ݰ�Ϊ��
#define SENDDATA_ERROR_NO_INFO -1
//�������ݰ�ʧ��
#define SENDDATA_ERROR_FAIL -2
//�������ݰ��ɹ�
#define SENDDATA_SUCCESS 1


//�õ����ݰ�ʧ��
#define RECVDATA_ERROR_FAIL -1
//���ܵ������ݰ�Ϊ��
#define RECVDATA_NO_DATA 0
//�������ݰ��ɹ�
#define RECVDATA_SUCCESS 1

//��������������ʧ��
#define SERVER_ACCEPT_FAIL 0
//�������������ӳɹ�
#define SERVER_ACCEPT_SUCCESS 1


//�����ļ�ʧ��
#define SENDFILE_FAIL 0
//�����ļ��ɹ�
#define SENDFILE_SUCCESS 1


//�����ļ�ʧ��
#define RECVFILE_FAIL 0
//�����ļ��ɹ�
#define RECVFILE_SUCCESS 1



typedef unsigned int SOCKET;

class CTcp  
{
public:
	CTcp();
	virtual ~CTcp();

	//���ó�ʱ
	void InitSocket(unsigned int unTimeOut);

	//�������ݰ�
	int Send( char *dataBuffer, int nSize);

	//�������ݰ�
	int Recv(char *dataBuffer, int nSize);

	//����
	int ConnectServer(char *pszIP, int nPort);

	//���������� nPort:�󶨵Ķ˿� bSync:�Ƿ��첽���� pszBindIP:�󶨶�Ӧ��IP(�������ʱ�����ǿ���ָ��ĳ������)
	int CreateServer(int nPort, bool bSync, char *pszBindIP);

	//���������׽���
	int AcceptConnect();

	//��Ϊ����˽����׽���ʱ�򣬴������ݡ�
	void SetSocket(SOCKET s);;

	//�����ļ�
	int SendFile(char *pszFilePath);

	//�����ļ�
	int RecvFile(char *pszFilePath);

	

private:

	//��ӡTcpͨѶ����־
	void WriteLog(char *pszErrorMsg);

	//�����׽���
	SOCKET CreateSocket();

	//��������,��װ���е�ϵͳ�ķ�������
	int SendData(char *dataBuffer, int nSize);
	
	//��������,��װ���е�ϵͳ�Ľ�������
	int RecvData(char *dataBuffer, int nSize);
	

	unsigned int m_nTimeOut;//����ϵͳ��ʱ��ʱ�䳤��
	
	SOCKET m_nSocket;//����õ��׽��֣��������ͻ��߽�������
	SOCKET m_nListenSocket;//�������������׽���
};

#endif // !defined(AFX_TCP_H__C1EE53E6_1984_4560_BEAB_FE04B0EE3698__INCLUDED_)
