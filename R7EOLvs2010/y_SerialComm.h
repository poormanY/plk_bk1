#ifndef Y_SERIAL_COMM_H
#define Y_SERIAL_COMM_H

#include "y_wm_user.h"

#define BUFF_SIZE			4192
#define THREAD_BUFF_SIZE	204800

//	��� Ŭ����	CCommThread 

// ��Ʈ���� �б� :
//   ��Ʈ�� �� �Ŀ� ��Ʈ�� �ڷᰡ �����ϸ� WM_COMM_READ �޽����� ���� 
//   �����쿡 ���޵ȴ�. ON_MESSAGE ��ũ�θ� �̿�, �Լ��� �����ϰ�
//   m_ReadData String�� ����� �����͸� �̿� �б�
// ��Ʈ�� ���� : WriteComm(buff, 30)�� ���� ���ۿ� �� ũ�⸦ �ǳ׸� �ȴ�.
class CQueue
{
public:
	CQueue();
	~CQueue();

	BYTE buff[BUFF_SIZE];//ť ���� ������� 4192�� ���� 
	int m_iHead, m_iTail;//ť ���ۿ� �����͸� �ְ� �� �ö� ����� ���� 
	void Clear();//���۸� �ʱ�ȭ ��Ŵ
	int GetSize();//���� ���ۿ� ����ִ� �������� size�� ����
	BOOL PutByte(BYTE b);//ť���ۿ� 1����Ʈ�� ����
	BOOL GetByte(BYTE *pb);//ť���ۿ��� 1����Ʈ�� �� ��
};


class CSerialComm
{
public:
	CSerialComm();
	~CSerialComm();

	//--------- �ܺ� ȯ�� ���� ------------------------------------//
	BOOL        check;
	HANDLE		m_hComm;				// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;			// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bConnected;			// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead, m_osWrite;	// ��Ʈ ���� Overlapped structure
	HANDLE		m_hThreadWatchComm;		// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;				// WM_COMM_READ�� �Բ� ������ �μ�.
	CQueue      m_QueueRead;			//ť����
	//--------- �ܺ� ��� �Լ� ------------------------------------//
	BOOL	OpenPort(CString strPortName, DWORD dwBaud, 
		BYTE byData, BYTE byStop, BYTE byParity ); //��Ʈ ����
	void	ClosePort();				           //��Ʈ �ݱ�
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);//��Ʈ�� ������ ����
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);//��Ʈ���� ������ �о����
	//--------- OpenPort ���� �� ��ȯ�� ---------------------------//
	CString byIndexComPort(int xPort);
	DWORD   byIndexBaud(int xBaud);
	BYTE    byIndexData(int xData);
	BYTE    byIndexStop(int xStop);
	BYTE    byIndexParity(int xParity);
	BYTE    byCode2AsciiValue(char cData);

protected:
	//--------- ���� ȯ�� ���� ------------------------------------//

	//--------- ���� ��� �Լ� ------------------------------------//
};

// Thread�� ����� �Լ� 
DWORD	ThreadWatchComm(CSerialComm* pComm);

#endif //  !Y_SERIAL_COMM_H  //