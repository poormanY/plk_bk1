// SerialDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "SerialDlg.h"
#include "afxdialogex.h"
#include "def_var.h"
#include "Color.h"


#define MAX_PORT_BAUD	8
#define MAX_DATA_BIT	4
#define MAX_STOP_BIT	2
#define MAX_PARITY		3
#define MAX_TYPE_SND	2
#define MAX_TYPE_RCV	2

static CString arstPortBaud[MAX_PORT_BAUD] = {_T("4800"), _T("9600"), _T("14400"), _T("19200"),
											_T("38400"), _T("56000"), _T("57600"), _T("115200")};
static CString arstDataBit[MAX_DATA_BIT] = {_T("5"), _T("6"), _T("7"), _T("8")};
static CString arstStopBit[MAX_STOP_BIT] = {_T("1"), _T("2")};
static CString arstParity[MAX_PARITY] = {_T("NONE"), _T("ODD"), _T("EVEN")};
static CString arstTypeSnd[MAX_TYPE_SND] = {_T("HEX"), _T("ASCII")};
static CString arstTypeRcv[MAX_TYPE_RCV] = {_T("HEX"), _T("ASCII")};



// SerialDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(SerialDlg, CDialogEx)

SerialDlg::SerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SerialDlg::IDD, pParent)
	, m_edit_serial_rcv_str(_T(""))
	, m_edit_serial_snd_str(_T(""))
{

}

SerialDlg::~SerialDlg()
{
}

void SerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT_NAME, m_combo_port_name);
	DDX_Control(pDX, IDC_COMBO_PORT_BAUD, m_combo_port_baud);
	DDX_Control(pDX, IDC_COMBO_PORT_DATA_BIT, m_combo_port_data_bit);
	DDX_Control(pDX, IDC_COMBO_PORT_STOP_BIT, m_combo_port_stop_bit);
	DDX_Control(pDX, IDC_COMBO_PORT_PARITY, m_combo_port_parity);
	DDX_Control(pDX, IDC_COMBO_TYPE_SND, m_combo_type_snd);
	DDX_Control(pDX, IDC_COMBO_TYPE_RCV, m_combo_type_rcv);
	DDX_Control(pDX, IDC_EDIT_SERIAL_RCV, m_edit_serial_rcv);
	DDX_Control(pDX, IDC_EDIT_SERIAL_OPERATION, m_edit_serial_operation);
	DDX_Control(pDX, IDC_EDIT_SERIAL_SND, m_edit_serial_snd);
	DDX_Text(pDX, IDC_EDIT_SERIAL_RCV, m_edit_serial_rcv_str);
	DDX_Text(pDX, IDC_EDIT_SERIAL_SND, m_edit_serial_snd_str);
}


BEGIN_MESSAGE_MAP(SerialDlg, CDialogEx)

	ON_CBN_DROPDOWN(IDC_COMBO_PORT_NAME, &SerialDlg::OnDropdownComboPortName)
	ON_BN_CLICKED(IDC_BUTTON_PORT_OPEN, &SerialDlg::OnBnClickedButtonPortOpen)
	ON_BN_CLICKED(IDC_BUTTON_PORT_CLOSE, &SerialDlg::OnBnClickedButtonPortClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_OPERATION, &SerialDlg::OnBnClickedButtonClearOperation)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_SND, &SerialDlg::OnBnClickedButtonClearSnd)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RCV, &SerialDlg::OnBnClickedButtonClearRcv)
	ON_BN_CLICKED(IDC_BUTTON_SND, &SerialDlg::OnBnClickedButtonSnd)
	ON_BN_CLICKED(IDOK, &SerialDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SerialDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &SerialDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CDisplayUnitTesterDlg 메시지 처리기
BOOL SerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	static int idx;

	// 솔리드, 해치 브러쉬를 각각만든다.
    m_brush_black.CreateSolidBrush(BLACK);
    m_brush_black_hatch.CreateHatchBrush(HS_DIAGCROSS, BLUEGRAY);

	// 기본 포트 통신 설정 값
	m_iSerialPort = 0;
	m_iBaudRate = 1;
	m_iDataBit = 3;
	m_iStopBit = 0;
	m_iParity = 0;

	// 포트 통신 콤보 박스 값
	for ( idx = 0; idx < MAX_PORT_BAUD; idx++ )
	{
		m_combo_port_baud.AddString(arstPortBaud[idx]);
	}
	m_combo_port_baud.SetCurSel(m_iBaudRate);

	for ( idx = 0; idx < MAX_DATA_BIT; idx++ )
	{
		m_combo_port_data_bit.AddString(arstDataBit[idx]);
	}
	m_combo_port_data_bit.SetCurSel(m_iDataBit);

	for ( idx = 0; idx < MAX_STOP_BIT; idx++ )
	{
		m_combo_port_stop_bit.AddString(arstStopBit[idx]);
	}
	m_combo_port_stop_bit.SetCurSel(0);

	for ( idx = 0; idx < MAX_PARITY; idx++ )
	{
		m_combo_port_parity.AddString(arstParity[idx]);
	}
	m_combo_port_parity.SetCurSel(0);

	for ( idx = 0; idx < MAX_TYPE_SND; idx++ )
	{
		m_combo_type_snd.AddString(arstTypeSnd[idx]);
	}
	m_combo_type_snd.SetCurSel(0);

	for ( idx = 0; idx < MAX_TYPE_RCV; idx++ )
	{
		m_combo_type_rcv.AddString(arstTypeRcv[idx]);
	}
	m_combo_type_rcv.SetCurSel(0);
				
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void SerialDlg::ClearOperationTxT(void)
{
	m_edit_serial_operation.SetSel(0, -1, TRUE);
	m_edit_serial_operation.Clear();
}
void SerialDlg::ClearRcvMsgTxT(void)
{
	m_edit_serial_rcv.SetSel(0, -1, TRUE);
	m_edit_serial_rcv.Clear();
}
void SerialDlg::ClearSndMsgTxT(void)
{
	m_edit_serial_snd.SetSel(0, -1, TRUE);
	m_edit_serial_snd.Clear();
}

void SerialDlg::OnBnClickedButtonClearOperation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ClearOperationTxT();
	m_edit_serial_operation.ReplaceSel(_T(""));
	m_edit_serial_operation.LineScroll( m_edit_serial_operation.GetLineCount() );

	//WriteOperationTxT(_T("Clear Operation"));
}
void SerialDlg::OnBnClickedButtonClearSnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ClearSndMsgTxT();

	WriteOperationTxT(_T("Clear Send Msg"));
}
void SerialDlg::OnBnClickedButtonClearRcv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ClearRcvMsgTxT();
	m_edit_serial_rcv.ReplaceSel(_T(""));
	m_edit_serial_rcv.LineScroll( m_edit_serial_operation.GetLineCount() );

	WriteOperationTxT(_T("Clear Receive Msg"));
}


void SerialDlg::WriteOperationTxT(CString txt)
{
	m_edit_serial_operation.ReplaceSel(txt);
	m_edit_serial_operation.ReplaceSel(_T("\r\n"));
	m_edit_serial_operation.LineScroll( m_edit_serial_operation.GetLineCount() );
}

void SerialDlg::WriteRcvMsgTxT(CString txt)
{
	m_edit_serial_rcv.ReplaceSel(txt);
	m_edit_serial_rcv.LineScroll( m_edit_serial_operation.GetLineCount() );
}


// SerialDlg 메시지 처리기입니다.
void SerialDlg::OnDropdownComboPortName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HKEY hKey;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM에 시리얼포트 번호들이 등록되어 있음.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	TCHAR szData[100], szName[100];
	DWORD index = 0, dwSize=100, dwSize2=100, dwType = REG_SZ;
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	// reset content of combobox
	m_combo_port_name.ResetContent();

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

		//Port Number
		m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(CString(szData));
		// 포트가 닫혀 있을 경우에만 포트를 열기 위해
		if ( m_ComuPort.m_bConnected == FALSE )
		{
			if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
			{
				// 포트를 여는데 성공했다면
				if ( m_ComuPort.m_bConnected == TRUE )
				{
					m_combo_port_name.AddString(CString(szData));
					m_ComuPort.ClosePort();
				}
			}
		}

		
        memset(szData, 0x00, sizeof(szData));  
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;  
        dwSize2 = 100;
    }
	RegCloseKey(hKey);
	m_combo_port_name.SetCurSel(0);	//combo box select content
}

void SerialDlg::DisablePortComboBox(void)
{
	GetDlgItem(IDC_COMBO_PORT_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PORT_BAUD)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PORT_DATA_BIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PORT_STOP_BIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PORT_PARITY)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}
void SerialDlg::EnablePortComboBox(void)
{
	GetDlgItem(IDC_COMBO_PORT_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_PORT_BAUD)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_PORT_DATA_BIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_PORT_STOP_BIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_PORT_PARITY)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void SerialDlg::OnBnClickedButtonPortOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString stText;
	DWORD dwThreadID;

	UpdateData(true);

	m_combo_port_name.GetLBText(m_combo_port_name.GetCurSel(), stText);
	m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(stText);
	m_iBaudRate = m_combo_port_baud.GetCurSel();
	m_iDataBit = m_combo_port_data_bit.GetCurSel();
	m_iStopBit = m_combo_port_stop_bit.GetCurSel();
	m_iParity = m_combo_port_parity.GetCurSel();

	// 포트가 닫혀 있을 경우에만 포트를 열기 위해
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
		{
			// 포트를 여는데 성공했다면
			if ( m_ComuPort.m_bConnected == TRUE )
			{				
				stText.Format(_T("Open Port : COM%d"),m_iSerialPort+1);
				WriteOperationTxT(stText);
				DisablePortComboBox();

				//--> 포트 감시 쓰레드 생성.
				m_hThread_SerialProc = NULL;
				m_hThread_SerialProc = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_Serial_Display, this, 0, &dwThreadID);

			}
			else
			{
				stText.Format(_T("Fail Port : COM%d"),m_iSerialPort+1);
				WriteOperationTxT(stText);
				AfxMessageBox(stText);
			}
		}
		else
		{
			stText.Format(_T("Fail Port : COM%d"),m_iSerialPort+1);
			WriteOperationTxT(stText);
			AfxMessageBox(stText);
		}
	}
	else
	{
		stText.Format(_T("Already COM%d Open"),m_iSerialPort+1);
		WriteOperationTxT(stText);
		AfxMessageBox(stText);
	}

}

void SerialDlg::OnBnClickedButtonPortClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString stText;

	if ( m_ComuPort.m_bConnected == TRUE )
	{
		m_ComuPort.ClosePort();
		stText.Format(_T("COM%d Close"),m_iSerialPort+1);
		WriteOperationTxT(stText);
		EnablePortComboBox();
	}
}

CString SerialDlg::ByteToHex(BYTE aByte)
{
	CString aHex = _T("");

	aHex.Format(_T("%02X"), aByte);

	return aHex;
}
CString SerialDlg::ByteToAscii(BYTE aByte)
{
	CString aAscii = _T("");

	aAscii.Format(_T("%c"), aByte);

	return aAscii;
}

BYTE SerialDlg::HexTo8Bits(CString aHex)
{
	BYTE a8Bits = 0;

	if		( aHex == _T("0") )	a8Bits = 0;
	else if ( aHex == _T("1") )	a8Bits = 1;
	else if ( aHex == _T("2") )	a8Bits = 2;
	else if ( aHex == _T("3") )	a8Bits = 3;
	else if ( aHex == _T("4") )	a8Bits = 4;
	else if ( aHex == _T("5") )	a8Bits = 5;
	else if ( aHex == _T("6") )	a8Bits = 6;
	else if ( aHex == _T("7") )	a8Bits = 7;
	else if ( aHex == _T("8") )	a8Bits = 8;
	else if ( aHex == _T("9") )	a8Bits = 9;
	else if ( aHex == _T("A") || aHex == _T("a") )	a8Bits = 10;
	else if ( aHex == _T("B") || aHex == _T("b") )	a8Bits = 11;
	else if ( aHex == _T("C") || aHex == _T("c") )	a8Bits = 12;
	else if ( aHex == _T("D") || aHex == _T("d") )	a8Bits = 13;
	else if ( aHex == _T("E") || aHex == _T("e") )	a8Bits = 14;
	else if ( aHex == _T("F") || aHex == _T("f") )	a8Bits = 15;

	return a8Bits;
}
BYTE SerialDlg::HexToByte(CString aHex)
{
	BYTE aByte = 0;

	if ( aHex.GetLength() == 1 )
	{
		aByte = HexTo8Bits(aHex.Left(1));
	}
	else
	{
		aByte = (HexTo8Bits(aHex.Left(1)) * 16) 
				+  HexTo8Bits(aHex.Right(1));
	}

	return aByte;
}
BYTE SerialDlg::AsciiToByte(CString aAscii)
{
	BYTE aByte = 0;
	
	aByte = aAscii[0];
	
	return aByte;
}

// 포트를 감시하고, 읽힌 내용이 있으면.
UINT SerialDlg::Thread_Serial_Display(SerialDlg* pDlg)
{
   int i = 0, iSize = 0;
   int rcvStatus = 0, rcvSize = 0;
   U16 datalen = 0, idx = 0;
   U16 data = 0x0000; 
   BYTE aByte;
   CString stRcvByte;
   CString stText, rcvData;
   SYSTEMTIME st_pre, st_cur;
   WORD st_diff = 0;

   GetSystemTime(&st_pre);
   GetSystemTime(&st_cur);
   
   while (pDlg->m_ComuPort.m_bConnected)//포트가 연결되면 무한 루프에 들어감
   {
	   iSize =  (pDlg->m_ComuPort.m_QueueRead).GetSize();
	   rcvSize += iSize;
	   while ( iSize ) //포트로 들어온 데이터 갯수
	   {
		   if ( pDlg->m_ComuPort.m_bConnected == false ) break;
			pDlg->UpdateData(TRUE);
			rcvStatus = 1;
					
			for ( i = 0; i < iSize; i++ ) //들어온 갯수 만큼 데이터를 읽어 와 JTP 프로토콜
			{
				if ( pDlg->m_ComuPort.m_bConnected == false ) break;

				(pDlg->m_ComuPort.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴

				// 들어오는 데이터를 Hex 값으로 보여줄지 Ascii 값으로 보여줄지
				if ( pDlg->m_combo_type_rcv.GetCurSel() == 0 )
				{
					stRcvByte = pDlg->ByteToHex(aByte);
					pDlg->WriteRcvMsgTxT(stRcvByte);
					stRcvByte.Format(_T(" "));
					pDlg->WriteRcvMsgTxT(stRcvByte);
				}
				else if ( pDlg->m_combo_type_rcv.GetCurSel() == 1 )
				{
					stRcvByte = pDlg->ByteToAscii(aByte);
					pDlg->WriteRcvMsgTxT(stRcvByte);
				}

			}
			iSize =  (pDlg->m_ComuPort.m_QueueRead).GetSize();
			rcvSize += iSize;
	   }
	   Sleep(100);
		
		if ( rcvStatus == 1 )
		{
			stRcvByte.Format(_T("\r\n"));
			pDlg->WriteRcvMsgTxT(stRcvByte);

			// 받은 데이터 길이를 Operation창에 띄움
			stText.Format(_T("Receive %d Characters"),rcvSize);
			pDlg->WriteOperationTxT(stText);
			
			rcvSize = 0;
			rcvStatus = 0;
		}

		GetSystemTime(&st_cur);
		st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
		if ( st_diff >= 3 ) //3초이상 응답이 없을 시에
		{
			
		}
   }
   pDlg->UpdateData(TRUE);
   pDlg->UpdateData(FALSE);
   
   return TRUE;
}

void SerialDlg::OnBnClickedButtonSnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sndSize = 0, idx = 0;
	CString stText;
	CString sndData, sndByte;
	BYTE *pbDataBuff;

	// 포트를 여는데 성공했다면
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		UpdateData(TRUE);
		
		m_edit_serial_snd.GetWindowTextW(sndData);
		sndData.Replace(_T(" "), NULL);
		sndData.Replace(_T("\r\n"), NULL);
		sndSize = sndData.GetLength();

		if ( m_combo_type_snd.GetCurSel() == 0 )
		{
			if ( sndSize%2 == 0 )	sndSize = sndSize/2;
			else					sndSize = sndSize/2 + 1;

			pbDataBuff = (BYTE *)malloc(sizeof(BYTE) * sndSize);

			for (idx = 0; idx < sndSize; idx++)
			{
				pbDataBuff[idx] = HexToByte(sndData.Mid(idx*2, 2));
			}
		}
		else if ( m_combo_type_snd.GetCurSel() == 1 )
		{
			pbDataBuff = (BYTE *)malloc(sizeof(BYTE) * sndSize);

			for (idx = 0; idx < sndSize; idx++)
			{
				pbDataBuff[idx] = AsciiToByte(sndData.Mid(idx, 1));
			}
		}
		// F0 AA 54 41 48 55 01 00 00 00 00 00 12 41 F0 55 디스플레이 확인용
		m_ComuPort.WriteComm(pbDataBuff, sndSize);
		stText.Format(_T("Send %d Characters"),sndSize);
		WriteOperationTxT(stText);
		
		free(pbDataBuff);
	}
}


void SerialDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


HBRUSH SerialDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	 switch(nCtlColor)
    {
		case CTLCOLOR_EDIT:
		{
			if(pWnd->GetDlgCtrlID() == IDC_EDIT_SERIAL_SND)
			{
				pDC->SetTextColor(WHITE);
				pDC->SetBkColor(BLACK);
				return m_brush_black;
			}
		}
		break;
		// 읽기 전용 컨트롤
		case CTLCOLOR_STATIC:
		{
			if(pWnd->GetDlgCtrlID() == IDC_EDIT_SERIAL_OPERATION)
			{
				// 글자의 배경을 그려주게 되면 바탕의 해치브러쉬 영역에 글자뒷 부분은
                // 녹색 사각형이 그려지게 된다.
                // 이를 막아주기 위하여, 배경그리는 기능을 제거한다. TRANSPARENT
                pDC->SetBkMode(TRANSPARENT);

				// 에디트 컨트롤 영역을 구한 후에
                // 브러쉬로 색칠해준다.
				pDC->SetTextColor(LTGREEN);
				pDC->SetBkColor(BLACK);

                CRect rc;
                GetDlgItem(IDC_EDIT_SERIAL_OPERATION)->GetWindowRect(rc);
                ScreenToClient(rc);
                pDC->FillRect(rc, &m_brush_black_hatch);
				
				return m_brush_black_hatch;
			}
			else if(pWnd->GetDlgCtrlID() == IDC_EDIT_SERIAL_RCV)
			{
				pDC->SetTextColor(WHITE);
				pDC->SetBkColor(BLACK);
				return m_brush_black;
			}
		}
		break;
		
    }


	return hbr;
}


void SerialDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString m_strPath;
	CStdioFile wFile;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		if (m_strPath.Right(4) != ".txt")
		{
			m_strPath += ".txt";
		}
		wFile.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText, &ex);
		// 에디트 박스에 있는 것을 저장한다. 
		UpdateData(TRUE);
		wFile.WriteString(m_edit_serial_rcv_str);
		// 종료한다. 
		wFile.Close();
	}
}


void SerialDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString m_strPath, str;
	CStdioFile rFile;
	CFileException ex;
	CFileDialog dlg(TRUE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		if (m_strPath.Right(4) != ".txt")
		{
			m_strPath += ".txt";
		}
		rFile.Open(m_strPath, CFile::modeReadWrite | CFile::typeText, &ex);
		// 에디트 박스에 있는 것을 불러온다. 
		UpdateData(TRUE);
		while ( rFile.ReadString(str) )
		{
			m_edit_serial_snd_str += (str + _T("\r\n"));
		}
		UpdateData(FALSE);
		// 종료한다. 
		rFile.Close();
	}
}
