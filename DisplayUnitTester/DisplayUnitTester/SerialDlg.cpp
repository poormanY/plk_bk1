// SerialDlg.cpp : ���� �����Դϴ�.
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



// SerialDlg ��ȭ �����Դϴ�.

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


// CDisplayUnitTesterDlg �޽��� ó����
BOOL SerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	static int idx;

	// �ָ���, ��ġ �귯���� ���������.
    m_brush_black.CreateSolidBrush(BLACK);
    m_brush_black_hatch.CreateHatchBrush(HS_DIAGCROSS, BLUEGRAY);

	// �⺻ ��Ʈ ��� ���� ��
	m_iSerialPort = 0;
	m_iBaudRate = 1;
	m_iDataBit = 3;
	m_iStopBit = 0;
	m_iParity = 0;

	// ��Ʈ ��� �޺� �ڽ� ��
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
				
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ClearOperationTxT();
	m_edit_serial_operation.ReplaceSel(_T(""));
	m_edit_serial_operation.LineScroll( m_edit_serial_operation.GetLineCount() );

	//WriteOperationTxT(_T("Clear Operation"));
}
void SerialDlg::OnBnClickedButtonClearSnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ClearSndMsgTxT();

	WriteOperationTxT(_T("Clear Send Msg"));
}
void SerialDlg::OnBnClickedButtonClearRcv()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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


// SerialDlg �޽��� ó�����Դϴ�.
void SerialDlg::OnDropdownComboPortName()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HKEY hKey;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM�� �ø�����Ʈ ��ȣ���� ��ϵǾ� ����.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	TCHAR szData[100], szName[100];
	DWORD index = 0, dwSize=100, dwSize2=100, dwType = REG_SZ;
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	// reset content of combobox
	m_combo_port_name.ResetContent();

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

		//Port Number
		m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(CString(szData));
		// ��Ʈ�� ���� ���� ��쿡�� ��Ʈ�� ���� ����
		if ( m_ComuPort.m_bConnected == FALSE )
		{
			if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
			{
				// ��Ʈ�� ���µ� �����ߴٸ�
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString stText;
	DWORD dwThreadID;

	UpdateData(true);

	m_combo_port_name.GetLBText(m_combo_port_name.GetCurSel(), stText);
	m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(stText);
	m_iBaudRate = m_combo_port_baud.GetCurSel();
	m_iDataBit = m_combo_port_data_bit.GetCurSel();
	m_iStopBit = m_combo_port_stop_bit.GetCurSel();
	m_iParity = m_combo_port_parity.GetCurSel();

	// ��Ʈ�� ���� ���� ��쿡�� ��Ʈ�� ���� ����
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
		{
			// ��Ʈ�� ���µ� �����ߴٸ�
			if ( m_ComuPort.m_bConnected == TRUE )
			{				
				stText.Format(_T("Open Port : COM%d"),m_iSerialPort+1);
				WriteOperationTxT(stText);
				DisablePortComboBox();

				//--> ��Ʈ ���� ������ ����.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

// ��Ʈ�� �����ϰ�, ���� ������ ������.
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
   
   while (pDlg->m_ComuPort.m_bConnected)//��Ʈ�� ����Ǹ� ���� ������ ��
   {
	   iSize =  (pDlg->m_ComuPort.m_QueueRead).GetSize();
	   rcvSize += iSize;
	   while ( iSize ) //��Ʈ�� ���� ������ ����
	   {
		   if ( pDlg->m_ComuPort.m_bConnected == false ) break;
			pDlg->UpdateData(TRUE);
			rcvStatus = 1;
					
			for ( i = 0; i < iSize; i++ ) //���� ���� ��ŭ �����͸� �о� �� JTP ��������
			{
				if ( pDlg->m_ComuPort.m_bConnected == false ) break;

				(pDlg->m_ComuPort.m_QueueRead).GetByte(&aByte);//ť���� ������ �Ѱ��� �о��

				// ������ �����͸� Hex ������ �������� Ascii ������ ��������
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

			// ���� ������ ���̸� Operationâ�� ���
			stText.Format(_T("Receive %d Characters"),rcvSize);
			pDlg->WriteOperationTxT(stText);
			
			rcvSize = 0;
			rcvStatus = 0;
		}

		GetSystemTime(&st_cur);
		st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
		if ( st_diff >= 3 ) //3���̻� ������ ���� �ÿ�
		{
			
		}
   }
   pDlg->UpdateData(TRUE);
   pDlg->UpdateData(FALSE);
   
   return TRUE;
}

void SerialDlg::OnBnClickedButtonSnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int sndSize = 0, idx = 0;
	CString stText;
	CString sndData, sndByte;
	BYTE *pbDataBuff;

	// ��Ʈ�� ���µ� �����ߴٸ�
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
		// F0 AA 54 41 48 55 01 00 00 00 00 00 12 41 F0 55 ���÷��� Ȯ�ο�
		m_ComuPort.WriteComm(pbDataBuff, sndSize);
		stText.Format(_T("Send %d Characters"),sndSize);
		WriteOperationTxT(stText);
		
		free(pbDataBuff);
	}
}


void SerialDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


HBRUSH SerialDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

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
		// �б� ���� ��Ʈ��
		case CTLCOLOR_STATIC:
		{
			if(pWnd->GetDlgCtrlID() == IDC_EDIT_SERIAL_OPERATION)
			{
				// ������ ����� �׷��ְ� �Ǹ� ������ ��ġ�귯�� ������ ���ڵ� �κ���
                // ��� �簢���� �׷����� �ȴ�.
                // �̸� �����ֱ� ���Ͽ�, ���׸��� ����� �����Ѵ�. TRANSPARENT
                pDC->SetBkMode(TRANSPARENT);

				// ����Ʈ ��Ʈ�� ������ ���� �Ŀ�
                // �귯���� ��ĥ���ش�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		// ����Ʈ �ڽ��� �ִ� ���� �����Ѵ�. 
		UpdateData(TRUE);
		wFile.WriteString(m_edit_serial_rcv_str);
		// �����Ѵ�. 
		wFile.Close();
	}
}


void SerialDlg::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		// ����Ʈ �ڽ��� �ִ� ���� �ҷ��´�. 
		UpdateData(TRUE);
		while ( rFile.ReadString(str) )
		{
			m_edit_serial_snd_str += (str + _T("\r\n"));
		}
		UpdateData(FALSE);
		// �����Ѵ�. 
		rFile.Close();
	}
}
