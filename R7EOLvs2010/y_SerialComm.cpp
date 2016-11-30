// Serial Communication - Comport

#include "stdafx.h"
#include "y_SerialComm.h"
////////////////
// CQueue
////////////////
void CQueue::Clear()
{
	m_iHead = 0;
	m_iTail =0;
	memset(buff,0,BUFF_SIZE);
}
CQueue::CQueue()
{
	Clear();
}
CQueue::~CQueue()
{
}
int CQueue::GetSize()
{
	return (m_iHead + BUFF_SIZE - m_iTail) % BUFF_SIZE;
}
BOOL CQueue::PutByte(BYTE b)
{
	if(GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}
BOOL CQueue::GetByte(BYTE *pb)
{
	if(GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}

////////////////
// CSerialComm
////////////////
CSerialComm::CSerialComm()
{
	//--> �ʱ�� �翬��..��Ʈ�� ������ ���� ���¿��߰���?
	m_bConnected = FALSE;
}
CSerialComm::~CSerialComm()
{
}

// ��Ʈ sPortName�� dwBaud �ӵ��� ����.
// ThreadWatchComm �Լ����� ��Ʈ�� ���� ������ �� MainWnd�� �˸���
// ���� WM_COMM_READ�޽����� ������ ���� ���� wPortID���� ���� �޴´�.
BOOL CSerialComm::OpenPort(CString strPortName, DWORD dwBaud, 
		BYTE byData, BYTE byStop, BYTE byParity )
{
	// Local ����.
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	// overlapped structure ���� �ʱ�ȭ.
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	//--> Read �̺�Ʈ ������ ����..
	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) )
	{
		return FALSE;
	}


	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	//--> Write �̺�Ʈ ������ ����..
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}

	//--> ��Ʈ�� ����..
	m_sPortName = strPortName;

	//--> ��������...RS 232 ��Ʈ ����..
	m_hComm = CreateFile( m_sPortName,
						  GENERIC_READ | GENERIC_WRITE, 0, NULL,
						  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
						  NULL);


	//--> ��Ʈ ���⿡ �����ϸ�..
	if (m_hComm == (HANDLE) -1)
	{
		//AfxMessageBox(_T("fail Port ofen"));
		return FALSE;
	}


	//===== ��Ʈ ���� ����. =====

	// EV_RXCHAR event ����...�����Ͱ� ������.. ���� �̺�Ʈ�� �߻��ϰԲ�..
	SetCommMask( m_hComm, EV_RXCHAR);

	// InQueue, OutQueue ũ�� ����.
	SetupComm( m_hComm, BUFF_SIZE, BUFF_SIZE);

	// ��Ʈ ����.
	PurgeComm( m_hComm,
			   PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout ����.
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;

	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts( m_hComm, &timeouts);

	// dcb ����.... ��Ʈ�� ��������..��� ����ϴ� DCB ����ü�� ����..
	dcb.DCBlength = sizeof(DCB);

	//--> ���� ������ �� �߿���..
	GetCommState( m_hComm, &dcb);

	//--> ���巹��Ʈ�� �ٲٰ�..
	dcb.BaudRate = dwBaud;


	//--> Data 8 Bit
	dcb.ByteSize = byData;

	//--> Noparity
	dcb.Parity = byParity;

	//--> 1 Stop Bit
	dcb.StopBits = byStop;


	//--> ��Ʈ�� ��..����������.. �����غ���..
	if( !SetCommState( m_hComm, &dcb) )
	{
		return FALSE;
	}


	// ��Ʈ ���� ������ ����.
	m_bConnected = TRUE;

	//--> ��Ʈ ���� ������ ����.
	m_hThreadWatchComm = CreateThread( NULL, 0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm,
									   this, 0, &dwThreadID);

	//--> ������ ������ �����ϸ�..
	if (! m_hThreadWatchComm)
	{
		//--> ���� ��Ʈ�� �ݰ�..
		ClosePort();
		return FALSE;
	}
	check = FALSE;

	return TRUE;
}

// ��Ʈ�� �ݴ´�.
void CSerialComm::ClosePort()
{
	//--> ������� �ʾ���.
	m_bConnected = FALSE;

	//--> ����ũ ����..
	SetCommMask( m_hComm, 0);

	//--> ��Ʈ ����.
	PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	CloseHandle(m_hComm);
	//--> �ڵ� �ݱ�
}


// ��Ʈ�� pBuff�� ������ nToWrite��ŭ ����.
// ������ ������ Byte���� �����Ѵ�.
DWORD CSerialComm::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//--> ��Ʈ�� ������� ���� �����̸�..
	if( !m_bConnected )
	{
		return 0;
	}

	//--> ���ڷ� ���� ������ ������ nToWrite ��ŭ ����.. �� ������.,dwWrite �� �ѱ�.
	if( !WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		//--> ���� ������ ���ڰ� ������ ���..
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// ���� ���ڰ� ���� �ְų� ������ ���ڰ� ���� ���� ��� Overapped IO��
			// Ư���� ���� ERROR_IO_PENDING ���� �޽����� ���޵ȴ�.
			//timeouts�� ������ �ð���ŭ ��ٷ��ش�.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	//--> ���� ��Ʈ�� ������ ������ ����..
	return dwWritten;
}


// ��Ʈ�κ��� pBuff�� nToRead��ŭ �д´�.
// ������ ������ Byte���� �����Ѵ�.
DWORD CSerialComm::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead,dwError, dwErrorFlags;
	COMSTAT comstat;

	//--- system queue�� ������ byte���� �̸� �д´�.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);

	//--> �ý��� ť���� ���� �Ÿ��� ������..
	dwRead = comstat.cbInQue;
	if(dwRead > 0)
	{
		//--> ���ۿ� �ϴ� �о���̴µ�.. ����..�о���ΰ��� ���ٸ�..
		if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead) )
		{
			//--> ���� �Ÿ��� ��������..
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	//--> ���� �о���� ������ ����.
	return dwRead;
}



// ��Ʈ�� �����ϰ�, ���� ������ ������
// m_ReadData�� ������ �ڿ� MainWnd�� �޽����� ������ Buffer�� ������
// �о��� �Ű��Ѵ�.
extern HWND hCommWnd;	// �޼����� ���� ����ó �ڵ鷯
DWORD	ThreadWatchComm(CSerialComm* pComm)
{
   DWORD           dwEvent;
   OVERLAPPED      os;
   BOOL            bOk = TRUE;
   BYTE            buff[THREAD_BUFF_SIZE];      // �б� ����
   DWORD           dwRead;  // ���� ����Ʈ��.


   // Event, OS ����.
   memset( &os, 0, sizeof(OVERLAPPED));

   //--> �̺�Ʈ ����..
   if( !(os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)) )
   {
		bOk = FALSE;
   }

   //--> �̺�Ʈ ����ũ..
   if( !SetCommMask( pComm->m_hComm, EV_RXCHAR) )
   {
	   bOk = FALSE;
   }

   //--> �̺�Ʈ��..����ũ ������ ������..
   if( !bOk )
   {
		//AfxMessageBox(_T("Error while creating ThreadWatchComm, ") + pComm->m_sPortName);
		return FALSE;
   }

   while (pComm ->m_bConnected)//��Ʈ�� ����Ǹ� ���� ������ ��
   {
 		dwEvent = 0;

        // ��Ʈ�� ���� �Ÿ��� �ö����� ��ٸ���.
        WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);


		//--> �����Ͱ� ���ŵǾ��ٴ� �޼����� �߻��ϸ�..
        if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
        {
            // ��Ʈ���� ���� �� �ִ� ��ŭ �д´�.
			//--> buff �� �޾Ƴ���..
			do
			{
				dwRead = pComm->ReadComm( buff, 2048); //���� ������ �о� ����
				if(BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for( WORD i = 0; i < dwRead; i++ )
					{
						pComm->m_QueueRead.PutByte(buff[i]);//ť ���ۿ�  ���� ������ �ֱ�
					}
				}
				else
				{
					AfxMessageBox(_T("buff full")); //ť������ ũ�⸦ �ʰ��ϸ� ��� �޽��� ����
				}
			}while(dwRead);
			::PostMessage(hCommWnd, _WM_COMM_READ, 0, 0 );//CSerialComDlg�� �����Ͱ� ���Դٴ� �޽����� ����
		}
		Sleep(0);	// ���� �����͸� ȭ�鿡 ������ �ð��� ���� ����.
					// �����͸� �������� ������ cpu�������� 100%�� �Ǿ� ȭ�鿡 �ѷ��ִ� �۾��� �� �ȵǰ�. ���������
					// ť ���ۿ� �����Ͱ� ���̰� ��
   }

  CloseHandle( os.hEvent);

   //--> ������ ���ᰡ �ǰ���?
   pComm->m_hThreadWatchComm = NULL;

   return TRUE;

}



CString CSerialComm::byIndexComPort(int xPort)
{
	CString PortName = _T("COM1");

	if (xPort < 0) return PortName;
	else if ( xPort < 5 )
	{
		// xPort:0 -> COM1
		PortName.Format(_T("COM%s"), xPort+1);
	}
	else
	{
		// xPort:4 -> \\\\.\\COM5
		PortName.Format(_T("\\\\.\\COM%s"), xPort+1);
	}

	return PortName;
}

DWORD CSerialComm::byIndexBaud(int xBaud)
{
	DWORD dwBaud = CBR_9600;
	switch(xBaud)
	{
		case 0:		dwBaud = CBR_110;		break;
		case 1:		dwBaud = CBR_300;		break;
		case 2:		dwBaud = CBR_600;		break;
		case 3:		dwBaud = CBR_1200;		break;
		case 4:		dwBaud = CBR_2400;		break;
		case 5:		dwBaud = CBR_4800;		break;
		case 6:		dwBaud = CBR_9600;		break;
		case 7:		dwBaud = CBR_14400;		break;
		case 8:		dwBaud = CBR_19200;		break;
		case 9:		dwBaud = CBR_38400;		break;
		case 10:	dwBaud = CBR_56000;		break;
		case 11:	dwBaud = CBR_57600;		break;	
		case 12:	dwBaud = CBR_115200;	break;
		case 13:	dwBaud = CBR_128000;	break;
		case 14:	dwBaud = CBR_256000;	break;
	}

	return dwBaud;
}

BYTE CSerialComm::byIndexData(int xData)
{
	BYTE byData = 8;
	switch(xData)
	{
		case 0 :	byData = 5;			break;
	
		case 1 :	byData = 6;			break;
		
		case 2 :	byData = 7;			break;
		
		case 3 :	byData = 8;			break;
	}
	return byData;
}

BYTE CSerialComm::byIndexStop(int xStop)
{
	BYTE byStop = ONESTOPBIT;
	if(xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}

BYTE CSerialComm::byIndexParity(int xParity)
{
	BYTE byParity = NOPARITY;
	switch(xParity)
	{
	case 0 :	byParity = NOPARITY;	break;
	
	case 1 :	byParity = ODDPARITY;	break;
	
	case 2 :	byParity = EVENPARITY;	break;
	}

	return byParity;
}

BYTE CSerialComm::byCode2AsciiValue(char cData)
{
	//�� �Լ��� char���ڸ� hex������ ������ �ִ� �Լ� �Դϴ�.
	BYTE byAsciiValue = 0;
	if( ( '0' <= cData ) && ( cData <='9' ) )
	{
		byAsciiValue = cData - '0';
	}
	else if( ( 'A' <= cData ) && ( cData <= 'F' ) )
	{
		byAsciiValue = (cData - 'A') + 10;
	}
	else if( ( 'a' <= cData ) && ( cData <= 'f' ) )
	{
		byAsciiValue = (cData - 'a') + 10;
	}
	else
	{
		byAsciiValue = 0;
	}
	return byAsciiValue;
}