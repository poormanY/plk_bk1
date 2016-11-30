
// DisplayUnitTesterDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "DisplayUnitTesterDlg.h"
#include "afxdialogex.h"
#include "DisplayDlg.h"
#include "JtpDlg.h"
#include "PcanDlg.h"
#include "SerialDlg.h"
#include "McuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 HWND hCommWnd;
// CDisplayUnitTesterDlg ��ȭ ����


CDisplayUnitTesterDlg::CDisplayUnitTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisplayUnitTesterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDisplayUnitTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COM, listBoxCom);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboComport);
}

BEGIN_MESSAGE_MAP(CDisplayUnitTesterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COM_SEARCH, &CDisplayUnitTesterDlg::OnBnClickedButtonComSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COM, &CDisplayUnitTesterDlg::OnClickListCom)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY, &CDisplayUnitTesterDlg::OnBnClickedButtonDisplay)
	ON_BN_CLICKED(IDC_BUTTON_JTP_PROTOCOL, &CDisplayUnitTesterDlg::OnBnClickedButtonJtpProtocol)
	ON_BN_CLICKED(IDC_BUTTON_PCAN, &CDisplayUnitTesterDlg::OnBnClickedButtonPcan)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL_COMM, &CDisplayUnitTesterDlg::OnBnClickedButtonSerialComm)
	ON_BN_CLICKED(IDC_BUTTON_MCU, &CDisplayUnitTesterDlg::OnBnClickedButtonMcu)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CDisplayUnitTesterDlg �޽��� ó����
BOOL CDisplayUnitTesterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �⺻ ��Ʈ ��� ���� ��
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;
	// ����Ʈ �ڽ� �׸�
	listBoxCom.InsertColumn(0, _T("Comport")    , LVCFMT_CENTER, 70);
	listBoxCom.InsertColumn(1, _T("Device Name"), LVCFMT_CENTER, 300);
    listBoxCom.InsertColumn(2, _T("Status")     , LVCFMT_CENTER, 100);
    listBoxCom.SetExtendedStyle(listBoxCom.GetExtendedStyle()|LVS_EX_GRIDLINES);
	// Comport �޺� �ڽ�
	int comportIdx = 0;
	CString comportNum;
	for (comportIdx = 1; comportIdx < 11; comportIdx++)
	{
		comportNum.Format(_T("COM%d"),comportIdx);
		m_comboComport.AddString(comportNum);
	}
	m_comboComport.SetCurSel(0);	//�ؽ�Ʈ ����
				
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}


int CDisplayUnitTesterDlg::PaintBitmapOnWindow(int IDB_BitmapNum, int nWidth, int nHeight)
{
	// ���ҽ��� ��ϵ� ��Ʈ�� ���
	CClientDC WinDC(this);   // Ŭ���̾�Ʈ�� DC�� �޾ƿ´�.
	CDC memDC_O, memDC_N;                // �޸𸮿� �����ϱ� ���ؼ� DC�� �����Ѵ�.
	CBitmap bitmap_O, bitmap_N;
	BITMAP bmpInfo;

	memDC_O.CreateCompatibleDC(&WinDC);   //   Ŭ���̾�Ʈ DC�� �ּҰ��� �Ѱ��ش�.
	memDC_N.CreateCompatibleDC(&WinDC); 

	bitmap_O.LoadBitmap(IDB_BitmapNum) ;    //  ���ҽ��� �ҷ��´�.
	bitmap_O.GetBitmap(&bmpInfo);        // ��Ʈ�� ��ü�� �޾ƿͼ�, ��Ʈ�� ������ �� �� �ִ�.

	//CBitmap Size Change bitmap_O -> bitmap_N
	//bitmap_O : �����̹���,   bitmap_N : ������ ��ȯ�� ������ ����
	memDC_O.SelectObject (&bitmap_O);
	bitmap_N.CreateCompatibleBitmap (&memDC_O, nWidth, nHeight); //������ �̹��� ��, ����
	memDC_N.SelectObject (&bitmap_N);
	memDC_N.StretchBlt (0, 0, nWidth, nHeight, &memDC_O,0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	// nSrc:  bitmap �����̹��� ��, ����

	CBitmap *pOldBitmap = ( CBitmap * ) memDC_N.SelectObject(&bitmap_N) ;

	//BOOL CDC::BitBlt( int x, int y, int nWidth, int nHeight, CDC* pSrcDC, int xSrc, int ySrc, DWORD dwRop );
	// hDC:��Ʈ���� ����� DC
	// X,Y,nWidth,nHeight:��Ʈ���� ����� ��ġ�� �»�� ��ǥ�� ��, ����, �� ���� ���� ��ǥ���̴�.
	// HSrcDC:����� ��Ʈ���� ������ �ִ� DC. ���� dwROP�� �ҽ��� �ʿ���� ���̶�� NULL�� �� ���� �ִ�.
	// XSrc,YSrc:����� ��Ʈ���� ���� ��� ��ǥ�̸� ����ó�� ���������� ���� ��ǥ���̴�. 
	//�� ���� 0�� ��� ��ü ��Ʈ���� �����Ѵ�. 
	//������� ���� ���̴� ����ó�� nWidth, nHeight�� ����ȴ�.
	// dwROP:ROP�ڵ�, �� �귯���� �����, ����ó�� ��Ʈ�� ������ �� ����� ����� �����Ѵ�. 
	//��� 256���� ������ ���� ������ ������ �ǹ̸� ���� ���� ���� 15���̸� ��ũ�� ����� ���ǵǾ� �ִ�. 
	//�� ���� ROP�ڵ尡 �ʿ��� ��쿡�� ����� ���� ����ؾ� �Ѵ�. 
	//�Ʒ� ǥ���� S�� ����� (Source), D�� ����ó(Destination), P�� ����(Pattern, �� �귯��)�� �ǹ��Ѵ�. 
	//    SRCCOPY�� ���� ����ϴ� �ڵ��̴�. �������� �����ϰ� �ٽ� �׸��ٴ� ���̴�.
	WinDC.BitBlt(0, 0, nWidth, nHeight, &memDC_N, 0, 0, SRCCOPY);
 
	memDC_N.SelectObject(pOldBitmap);

	return 0;
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDisplayUnitTesterDlg::OnPaint()
{	
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}

	// ���ȭ�� BITMAP���� ä���
	CRect winRect;
	GetClientRect(winRect);
	PaintBitmapOnWindow(IDB_PlkLog, winRect.Width(), winRect.Height());
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDisplayUnitTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CDisplayUnitTesterDlg::byIndexComPort(int xPort)
{
	CString PortName;
	switch(xPort)
	{
		case 0:		PortName = "COM1"; 			break;
			
		case 1:		PortName = "COM2";			break;

		case 2:		PortName = "COM3"; 			break;
		
		case 3:		PortName = "COM4";			break;
			
		case 4:		PortName = "\\\\.\\COM5"; 	break;
			
		case 5:		PortName = "\\\\.\\COM6";	break;
			
		case 6:		PortName = "\\\\.\\COM7"; 	break;
			
		case 7:		PortName = "\\\\.\\COM8";	break;
		
		case 8:		PortName = "\\\\.\\COM9"; 	break;
			
		case 9:		PortName = "\\\\.\\COM10";	break;

		case 10:	PortName = "\\\\.\\COM11";	break;

		case 11:	PortName = "\\\\.\\COM12";	break;

		case 12:	PortName = "\\\\.\\COM13";	break;

		case 13:	PortName = "\\\\.\\COM14";	break;

		case 14:	PortName = "\\\\.\\COM15";	break;

		case 15:	PortName = "\\\\.\\COM16";	break;

		case 16:	PortName = "\\\\.\\COM17";	break;

		case 17:	PortName = "\\\\.\\COM18";	break;

		case 18:	PortName = "\\\\.\\COM19";	break;

		case 19:	PortName = "\\\\.\\COM20";	break;
	}


	
	return PortName;
}

int CDisplayUnitTesterDlg::toIdxComPort(CString PortName)
{
	int xPort;

	if ( PortName == "COM1" )
	{
		xPort = 0;
	}
	else if ( PortName == "COM2" )
	{
		xPort = 1;
	}
	else if ( PortName == "COM3" )
	{
		xPort = 2;
	}
	else if ( PortName == "COM4" )
	{
		xPort = 3;
	}
	else if ( PortName == "COM5" )
	{
		xPort = 4;
	}
	else if ( PortName == "COM6" )
	{
		xPort = 5;
	}
	else if ( PortName == "COM7" )
	{
		xPort = 6;
	}
	else if ( PortName == "COM8" )
	{
		xPort = 7;
	}
	else if ( PortName == "COM9" )
	{
		xPort = 8;
	}
	else if ( PortName == "COM10" )
	{
		xPort = 9;
	}
	else if ( PortName == "COM11" )
	{
		xPort = 10;
	}
	else if ( PortName == "COM12" )
	{
		xPort = 11;
	}
	else if ( PortName == "COM13" )
	{
		xPort = 12;
	}
	else if ( PortName == "COM14" )
	{
		xPort = 13;
	}
	else if ( PortName == "COM16" )
	{
		xPort = 15;
	}
	else if ( PortName == "COM17" )
	{
		xPort = 16;
	}
	else if ( PortName == "COM18" )
	{
		xPort = 17;
	}
	else if ( PortName == "COM19" )
	{
		xPort = 18;
	}
	else if ( PortName == "COM20" )
	{
		xPort = 19;
	}

	return xPort;
}

DWORD CDisplayUnitTesterDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud;
	switch(xBaud)
	{
		case 0:		dwBaud = CBR_4800;		break;
			
		case 1:		dwBaud = CBR_9600;		break;
	
		case 2:		dwBaud = CBR_14400;		break;
	
		case 3:		dwBaud = CBR_19200;		break;
	
		case 4:		dwBaud = CBR_38400;		break;
	
		case 5:		dwBaud = CBR_56000;		break;
	
		case 6:		dwBaud = CBR_57600;		break;
	
		case 7:		dwBaud = CBR_115200;	break;
	}

	return dwBaud;
}


BYTE CDisplayUnitTesterDlg::byIndexData(int xData)
{
	BYTE byData;
	switch(xData)
	{
		case 0 :	byData = 5;			break;
	
		case 1 :	byData = 6;			break;
		
		case 2 :	byData = 7;			break;
		
		case 3 :	byData = 8;			break;
	}
	return byData;
}

BYTE CDisplayUnitTesterDlg::byIndexStop(int xStop)
{
	BYTE byStop;
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

BYTE CDisplayUnitTesterDlg::byIndexParity(int xParity)
{
	BYTE byParity;
	switch(xParity)
	{
	case 0 :	byParity = NOPARITY;	break;
	
	case 1 :	byParity = ODDPARITY;	break;
	
	case 2 :	byParity = EVENPARITY;	break;
	}

	return byParity;
}

CString CDisplayUnitTesterDlg::StrChckPortOPen(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity)
{
	CString Result = _T("Connected");

	// ��Ʈ�� ���� ���� ��쿡�� ��Ʈ�� ���� ����
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(strPortName, byIndexBaud(iBaudRate), byIndexData(iDataBit), byIndexStop(iStopBit), byIndexParity(iParity)) ==TRUE)
		{
			// ��Ʈ�� ���µ� �����ߴٸ�
			if ( m_ComuPort.m_bConnected == TRUE )
			{
				Result = _T("OPEN");
				m_ComuPort.ClosePort();
			}
		}
	}
	
	return Result;
}


void CDisplayUnitTesterDlg::OnBnClickedButtonComSearch()
{
	listBoxCom.DeleteAllItems();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HKEY hKey, hKey2;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	CString lpSubKey2 = _T("SYSTEM\\ControlSet001\\Control\\Class\\{4D36E978-E325-11CE-BFC1-08002BE10318}");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM�� �ø�����Ʈ ��ȣ���� ��ϵǾ� ����.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	int nListPos = 0;
	TCHAR szData[100], szName[100];
	DWORD index = 0, index2 = 0, dwSize=100, dwSize2 = 100, dwType = REG_SZ;
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	//hKey - ��������Ű �ڵ�  
    //index - ���� ������ �ε���.. �ټ��� ���� ���� ��� �ʿ�  
    //szName - �׸��� ����� �迭  
    //dwSize - �迭�� ũ��  
    while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))  
    {
		index++;  
    
        //szName-�����ͽ��� �׸��� �̸�  
        //dwType-�׸��� Ÿ��, ���⿡���� �η� ������ ���ڿ�  
        //szData-�׸��� ����� �迭  
        //dwSize2-�迭�� ũ��
        RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		//Port ��ȣ
        listBoxCom.InsertItem(nListPos,(CString(szData)));
		//���� ����
		listBoxCom.SetItemText(nListPos,2,StrChckPortOPen(CString(szData), m_iBaudRate, m_iDataBit, m_iStopBit, m_iParity));

		lpSubKey2.Format(_T("SYSTEM\\ControlSet001\\Control\\Class\\{4D36E978-E325-11CE-BFC1-08002BE10318}\\000%d"),toIdxComPort(CString(szData)));
		RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey2, &hKey2);

		memset(szData, 0x00, sizeof(szData));  
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;
        dwSize2 = 100;
		index2 = 0;
		while (ERROR_SUCCESS == RegEnumValue(hKey2, index2, szName, &dwSize, NULL, NULL, NULL, NULL))  
		{
			index2++;

			if ( CString(szName) == "DriverDesc" )
			{
				//����̹� �̸�
				RegQueryValueEx(hKey2, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
				listBoxCom.SetItemText(nListPos,1,(CString(szData)));

				break;
			}
			memset(szData, 0x00, sizeof(szData));  
			memset(szName, 0x00, sizeof(szName));
			dwSize = 100;  
			dwSize2 = 100; 
		}
		RegCloseKey(hKey2);

		nListPos++;
    
        memset(szData, 0x00, sizeof(szData));  
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;  
        dwSize2 = 100;
    }
    
    RegCloseKey(hKey);

}


void CDisplayUnitTesterDlg::OnClickListCom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = pNMItemActivate->iItem; // Ŭ���� �������� �ε��� ����
	CString PortName;
     
    if(index >= 0 && index < listBoxCom.GetItemCount()) // ǥ�õ� �����۵��߿� Ŭ���� �Ʒ� �ڵ� ���� 
    {
        // do somthing
		PortName = listBoxCom.GetItemText(index, 0);
		m_comboComport.SetCurSel(toIdxComPort(PortName));	//Comport ����
    }
 
	*pResult = 0;
}


void CDisplayUnitTesterDlg::OnBnClickedButtonDisplay()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DisplayDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonJtpProtocol()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	JtpDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonPcan()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	PcanDlg dlg;
	dlg.DoModal();
}

void CDisplayUnitTesterDlg::OnBnClickedButtonSerialComm()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SerialDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonMcu()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	McuDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect winRect;
	GetClientRect(winRect);

	lpMMI->ptMinTrackSize = CPoint(650, 420);
	lpMMI->ptMaxTrackSize = CPoint(650, 420);
    
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
