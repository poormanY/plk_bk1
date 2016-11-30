
// DisplayUnitTesterDlg.cpp : 구현 파일
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
// CDisplayUnitTesterDlg 대화 상자


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


// CDisplayUnitTesterDlg 메시지 처리기
BOOL CDisplayUnitTesterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 기본 포트 통신 설정 값
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;
	// 리스트 박스 항목
	listBoxCom.InsertColumn(0, _T("Comport")    , LVCFMT_CENTER, 70);
	listBoxCom.InsertColumn(1, _T("Device Name"), LVCFMT_CENTER, 300);
    listBoxCom.InsertColumn(2, _T("Status")     , LVCFMT_CENTER, 100);
    listBoxCom.SetExtendedStyle(listBoxCom.GetExtendedStyle()|LVS_EX_GRIDLINES);
	// Comport 콤보 박스
	int comportIdx = 0;
	CString comportNum;
	for (comportIdx = 1; comportIdx < 11; comportIdx++)
	{
		comportNum.Format(_T("COM%d"),comportIdx);
		m_comboComport.AddString(comportNum);
	}
	m_comboComport.SetCurSel(0);	//텍스트 선택
				
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


int CDisplayUnitTesterDlg::PaintBitmapOnWindow(int IDB_BitmapNum, int nWidth, int nHeight)
{
	// 리소스로 등록된 비트맵 출력
	CClientDC WinDC(this);   // 클라이언트의 DC를 받아온다.
	CDC memDC_O, memDC_N;                // 메모리에 상주하기 위해서 DC를 생성한다.
	CBitmap bitmap_O, bitmap_N;
	BITMAP bmpInfo;

	memDC_O.CreateCompatibleDC(&WinDC);   //   클라이언트 DC의 주소값을 넘겨준다.
	memDC_N.CreateCompatibleDC(&WinDC); 

	bitmap_O.LoadBitmap(IDB_BitmapNum) ;    //  리소스를 불러온다.
	bitmap_O.GetBitmap(&bmpInfo);        // 비트맵 객체에 받아와서, 비트맵 정보를 알 수 있다.

	//CBitmap Size Change bitmap_O -> bitmap_N
	//bitmap_O : 원본이미지,   bitmap_N : 사이즈 변환후 저장할 변수
	memDC_O.SelectObject (&bitmap_O);
	bitmap_N.CreateCompatibleBitmap (&memDC_O, nWidth, nHeight); //변경할 이미지 폭, 높이
	memDC_N.SelectObject (&bitmap_N);
	memDC_N.StretchBlt (0, 0, nWidth, nHeight, &memDC_O,0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	// nSrc:  bitmap 원본이미지 폭, 높이

	CBitmap *pOldBitmap = ( CBitmap * ) memDC_N.SelectObject(&bitmap_N) ;

	//BOOL CDC::BitBlt( int x, int y, int nWidth, int nHeight, CDC* pSrcDC, int xSrc, int ySrc, DWORD dwRop );
	// hDC:비트맵이 복사될 DC
	// X,Y,nWidth,nHeight:비트맵이 복사될 위치의 좌상단 좌표와 폭, 넓이, 이 값은 논리적 좌표값이다.
	// HSrcDC:복사될 비트맵을 가지고 있는 DC. 만약 dwROP가 소스가 필요없는 값이라면 NULL이 될 수도 있다.
	// XSrc,YSrc:복사될 비트맵의 좌측 상단 좌표이며 복사처와 마찬가지로 논리적 좌표값이다. 
	//이 값이 0일 경우 전체 비트맵을 복사한다. 
	//복사원의 폭과 높이는 복사처의 nWidth, nHeight가 적용된다.
	// dwROP:ROP코드, 즉 브러쉬와 복사원, 복사처의 비트맵 색상이 논리 연산될 방법을 지정한다. 
	//모두 256개의 가능한 값이 있지만 실제로 의미를 갖는 없은 다음 15개이며 매크로 상수가 정의되어 있다. 
	//이 외의 ROP코드가 필요할 경우에는 상수를 직접 사용해야 한다. 
	//아래 표에서 S는 복사원 (Source), D는 복사처(Destination), P는 패턴(Pattern, 즉 브러쉬)를 의미한다. 
	//    SRCCOPY는 흔히 사용하는 코드이다. 기존값을 무시하고 다시 그린다는 뜻이다.
	WinDC.BitBlt(0, 0, nWidth, nHeight, &memDC_N, 0, 0, SRCCOPY);
 
	memDC_N.SelectObject(pOldBitmap);

	return 0;
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDisplayUnitTesterDlg::OnPaint()
{	
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}

	// 배경화면 BITMAP으로 채우기
	CRect winRect;
	GetClientRect(winRect);
	PaintBitmapOnWindow(IDB_PlkLog, winRect.Width(), winRect.Height());
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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

	// 포트가 닫혀 있을 경우에만 포트를 열기 위해
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(strPortName, byIndexBaud(iBaudRate), byIndexData(iDataBit), byIndexStop(iStopBit), byIndexParity(iParity)) ==TRUE)
		{
			// 포트를 여는데 성공했다면
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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HKEY hKey, hKey2;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	CString lpSubKey2 = _T("SYSTEM\\ControlSet001\\Control\\Class\\{4D36E978-E325-11CE-BFC1-08002BE10318}");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM에 시리얼포트 번호들이 등록되어 있음.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	int nListPos = 0;
	TCHAR szData[100], szName[100];
	DWORD index = 0, index2 = 0, dwSize=100, dwSize2 = 100, dwType = REG_SZ;
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	//hKey - 레지스터키 핸들  
    //index - 값을 가져올 인덱스.. 다수의 값이 있을 경우 필요  
    //szName - 항목값이 저장될 배열  
    //dwSize - 배열의 크기  
    while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))  
    {
		index++;  
    
        //szName-레지터스터 항목의 이름  
        //dwType-항목의 타입, 여기에서는 널로 끝나는 문자열  
        //szData-항목값이 저장될 배열  
        //dwSize2-배열의 크기
        RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		//Port 번호
        listBoxCom.InsertItem(nListPos,(CString(szData)));
		//연결 여부
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
				//드라이버 이름
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = pNMItemActivate->iItem; // 클릭한 아이템의 인덱스 얻어옴
	CString PortName;
     
    if(index >= 0 && index < listBoxCom.GetItemCount()) // 표시된 아이템들중에 클릭시 아래 코드 실행 
    {
        // do somthing
		PortName = listBoxCom.GetItemText(index, 0);
		m_comboComport.SetCurSel(toIdxComPort(PortName));	//Comport 선택
    }
 
	*pResult = 0;
}


void CDisplayUnitTesterDlg::OnBnClickedButtonDisplay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DisplayDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonJtpProtocol()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JtpDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonPcan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PcanDlg dlg;
	dlg.DoModal();
}

void CDisplayUnitTesterDlg::OnBnClickedButtonSerialComm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SerialDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnBnClickedButtonMcu()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	McuDlg dlg;
	dlg.DoModal();
}


void CDisplayUnitTesterDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect winRect;
	GetClientRect(winRect);

	lpMMI->ptMinTrackSize = CPoint(650, 420);
	lpMMI->ptMaxTrackSize = CPoint(650, 420);
    
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
