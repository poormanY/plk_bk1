// JtpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "JtpDlg.h"
#include "afxdialogex.h"
#include "Color.h"
#include "wm_user.h"

// JtpDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(JtpDlg, CDialogEx)

JtpDlg::JtpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(JtpDlg::IDD, pParent)
	, m_edit_header(_T(""))
	, m_edit_tgtid(_T(""))
	, m_edit_srcid(_T(""))
	, m_edit_cmd(_T(""))
	, m_edit_para(_T(""))
	, m_edit_datalen(_T(""))
	, m_edit_chksum(_T(""))
	, m_edit_footer(_T(""))
	, m_edit_data1(_T(""))
	, m_edit_data2(_T(""))
	, m_edit_data3(_T(""))
	, m_edit_data4(_T(""))
	, m_edit_data5(_T(""))
	, m_edit_data6(_T(""))
	, m_edit_data7(_T(""))
	, m_edit_data8(_T(""))
	, m_edit_out_header(_T(""))
	, m_edit_out_tgtid(_T(""))
	, m_edit_out_srcid(_T(""))
	, m_edit_out_cmd(_T(""))
	, m_edit_out_para(_T(""))
	, m_edit_out_datalen(_T(""))
	, m_edit_out_chksum(_T(""))
	, m_edit_out_footer(_T(""))
	, m_edit_out_data1(_T(""))
	, m_edit_out_data2(_T(""))
	, m_edit_out_data3(_T(""))
	, m_edit_out_data4(_T(""))
	, m_edit_out_data5(_T(""))
	, m_edit_out_data6(_T(""))
	, m_edit_out_data7(_T(""))
	, m_edit_out_data8(_T(""))
	, m_check_continue(FALSE)
{

}

JtpDlg::~JtpDlg()
{
}

void JtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT_NUM, m_combo_port_num);
	DDX_Control(pDX, IDC_BUTTON_PORT_OPEN, m_button_port_open);
	DDX_Text(pDX, IDC_EDIT_HEADER, m_edit_header);
	DDX_Text(pDX, IDC_EDIT_TGTID, m_edit_tgtid);
	DDX_Text(pDX, IDC_EDIT_SRCID, m_edit_srcid);
	DDX_Text(pDX, IDC_EDIT_CMD, m_edit_cmd);
	DDX_Text(pDX, IDC_EDIT_PARA, m_edit_para);
	DDX_Text(pDX, IDC_EDIT_DATALEN, m_edit_datalen);
	DDX_Text(pDX, IDC_EDIT_CHKSUM, m_edit_chksum);
	DDX_Text(pDX, IDC_EDIT_FOOTER, m_edit_footer);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_edit_data1);
	DDX_Text(pDX, IDC_EDIT_DATA2, m_edit_data2);
	DDX_Text(pDX, IDC_EDIT_DATA3, m_edit_data3);
	DDX_Text(pDX, IDC_EDIT_DATA4, m_edit_data4);
	DDX_Text(pDX, IDC_EDIT_DATA5, m_edit_data5);
	DDX_Text(pDX, IDC_EDIT_DATA6, m_edit_data6);
	DDX_Text(pDX, IDC_EDIT_DATA7, m_edit_data7);
	DDX_Text(pDX, IDC_EDIT_DATA8, m_edit_data8);
	DDX_Control(pDX, IDC_EDIT_COMM_STATUS, m_edit_comm_status);
	DDX_Text(pDX, IDC_EDIT_HEADER2, m_edit_out_header);
	DDX_Text(pDX, IDC_EDIT_TGTID2, m_edit_out_tgtid);
	DDX_Text(pDX, IDC_EDIT_SRCID2, m_edit_out_srcid);
	DDX_Text(pDX, IDC_EDIT_CMD2, m_edit_out_cmd);
	DDX_Text(pDX, IDC_EDIT_PARA2, m_edit_out_para);
	DDX_Text(pDX, IDC_EDIT_DATALEN2, m_edit_out_datalen);
	DDX_Text(pDX, IDC_EDIT_CHKSUM2, m_edit_out_chksum);
	DDX_Text(pDX, IDC_EDIT_FOOTER2, m_edit_out_footer);
	DDX_Text(pDX, IDC_EDIT_DATA21, m_edit_out_data1);
	DDX_Text(pDX, IDC_EDIT_DATA22, m_edit_out_data2);
	DDX_Text(pDX, IDC_EDIT_DATA23, m_edit_out_data3);
	DDX_Text(pDX, IDC_EDIT_DATA24, m_edit_out_data4);
	DDX_Text(pDX, IDC_EDIT_DATA25, m_edit_out_data5);
	DDX_Text(pDX, IDC_EDIT_DATA26, m_edit_out_data6);
	DDX_Text(pDX, IDC_EDIT_DATA27, m_edit_out_data7);
	DDX_Text(pDX, IDC_EDIT_DATA28, m_edit_out_data8);
	DDX_Check(pDX, IDC_CHECK_CONTINUE, m_check_continue);
}


BEGIN_MESSAGE_MAP(JtpDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO_PORT_NUM, &JtpDlg::OnDropdownComboPortNum)
	ON_BN_CLICKED(IDC_BUTTON_PORT_OPEN, &JtpDlg::OnBnClickedButtonPortOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &JtpDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDOK_EXIT, &JtpDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_BUTTON_CHKSUM, &JtpDlg::OnBnClickedButtonChksum)
END_MESSAGE_MAP()


// JtpDlg 메시지 처리기입니다.
// 초기값 설정
BOOL JtpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 기본 포트 통신 설정 값
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;
	// 통신 상태 표시줄	
    m_edit_comm_status.SetBgColor(YELLOW);		//백그라운드 색
    m_edit_comm_status.SetTextColor(BLACK);	// 글자 색
    m_edit_comm_status.SetTextFormat(DT_CENTER|DT_VCENTER);
	m_edit_comm_status.m_strMsg = "Not Connected";
	m_edit_comm_status.PostMessageW(_WM_THREAD_UPDATE);
	// 송신 데이터 초기 값 설정
	m_edit_out_header.Format(_T("%04X"), JTP_HEAD_VALUE);
	m_edit_out_tgtid.Format(_T("%04X"), JTP_ID_TACO);
	m_edit_out_srcid.Format(_T("%04X"), JTP_ID_HUB);
	m_edit_out_cmd.Format(_T("%04X"), CMD_READY);
	m_edit_out_para.Format(_T("%04X"), _JTP_RESP_OK);
	m_edit_out_datalen.Format(_T("%04X"), 0x0000);
	m_edit_out_chksum.Format(_T("%04X"), 0x4112);
	m_edit_out_footer.Format(_T("%04X"), JTP_FOOT_VALUE);
	m_edit_out_data1.Format(_T("%04X"), 0x0000);
	m_edit_out_data2.Format(_T("%04X"), 0x0000);
	m_edit_out_data3.Format(_T("%04X"), 0x0000);
	m_edit_out_data4.Format(_T("%04X"), 0x0000);
	m_edit_out_data5.Format(_T("%04X"), 0x0000);
	m_edit_out_data6.Format(_T("%04X"),  0x0000);
	m_edit_out_data7.Format(_T("%04X"), 0x0000);
	m_edit_out_data8.Format(_T("%04X"), 0x0000);
	
	// init port number on combobox
	OnDropdownComboPortNum();

	UpdateData(FALSE);

	return TRUE;
}


int JtpDlg::ConvertHexToInt(CString stHex)
{
	int hexValue = 0;
	int idx = 0, hexLen = 0;
	CString aHex;

	hexLen = stHex.GetLength();
	
	for ( idx = 0; idx < hexLen; idx++ )
	{
		hexValue <<= 4; // *=16
		
		aHex = stHex.Mid( idx, 1);
		if ( aHex == "0" )		hexValue += 0;
		else if ( aHex == "1" )	hexValue += 1;
		else if ( aHex == "2" )	hexValue += 2;
		else if ( aHex == "3" )	hexValue += 3;
		else if ( aHex == "4" )	hexValue += 4;
		else if ( aHex == "5" )	hexValue += 5;
		else if ( aHex == "6" )	hexValue += 6;
		else if ( aHex == "7" )	hexValue += 7;
		else if ( aHex == "8" )	hexValue += 8;
		else if ( aHex == "9" )	hexValue += 9;
		else if ( aHex == "A" )	hexValue += 10;
		else if ( aHex == "B" )	hexValue += 11;
		else if ( aHex == "C" )	hexValue += 12;
		else if ( aHex == "D" )	hexValue += 13;
		else if ( aHex == "E" )	hexValue += 14;
		else if ( aHex == "F" )	hexValue += 15;
	}

	return hexValue;
}


void JtpDlg::OnDropdownComboPortNum()
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
	m_combo_port_num.ResetContent();

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
					m_combo_port_num.AddString(CString(szData));
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
	m_combo_port_num.SetCurSel(0);	//combo box select content
}

// 포트를 감시하고, 읽힌 내용이 있으면.
UINT JtpDlg::Thread_JTP_Protocol(JtpDlg* pDlg)
{
   int i = 0, iSize = 0;
   int sndSize = 0;
   U16 datalen = 0, idx = 0;
   U16 data = 0x0000; 
   BYTE aByte;
   JTP_FRAME *pJtpFrame;
   U16 *pJtpBuff;
   SYSTEMTIME st_pre, st_cur;
   WORD st_diff = 0;

   GetSystemTime(&st_pre);
   GetSystemTime(&st_cur);
   
   while (pDlg->m_ComuPort.m_bConnected)//포트가 연결되면 무한 루프에 들어감
   {
	   pDlg->UpdateData(TRUE);
 		iSize =  (pDlg->m_ComuPort.m_QueueRead).GetSize(); //포트로 들어온 데이터 갯수
													//SetCommState에 설정된 내용 때문에 거의 8개씩 들어옴					
		for ( i = 0; i < iSize; i++ ) //들어온 갯수 만큼 데이터를 읽어 와 JTP 프로토콜
		{
			(pDlg->m_ComuPort.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴							
			if ( pDlg->m_Jtp.JTP_Frame_Get(aByte) == TRUE )
			{
				GetSystemTime(&st_pre);
				

				pJtpFrame = (JTP_FRAME *)pDlg->m_Jtp.jtpBuff;
				pJtpBuff = (U16 *)pDlg->m_Jtp.jtpBuff;

				pDlg->m_edit_header.Format(_T("%04X"),pJtpFrame->uHeader);
				pDlg->m_edit_tgtid.Format(_T("%04X"),pJtpFrame->uTgtId);
				pDlg->m_edit_srcid.Format(_T("%04X"),pJtpFrame->uSrcId);
				pDlg->m_edit_cmd.Format(_T("%04X"),pJtpFrame->uCommand);
				pDlg->m_edit_para.Format(_T("%04X"),pJtpFrame->uParam);
				pDlg->m_edit_datalen.Format(_T("%04X"),pJtpFrame->uDataLen);

				// 데이터 표시
				pDlg->m_edit_data1.Format(_T(""));
				pDlg->m_edit_data2.Format(_T(""));
				pDlg->m_edit_data3.Format(_T(""));
				pDlg->m_edit_data4.Format(_T(""));
				pDlg->m_edit_data5.Format(_T(""));
				pDlg->m_edit_data6.Format(_T(""));
				pDlg->m_edit_data7.Format(_T(""));
				pDlg->m_edit_data8.Format(_T(""));
								
				datalen = pJtpFrame->uDataLen;
				for(idx = 0; idx < datalen/2; idx++)
				{
					data = pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx];
					switch(idx)
					{
					case 0:
						pDlg->m_edit_data1.Format(_T("%04X"),data);
						break;
					case 1:
						pDlg->m_edit_data2.Format(_T("%04X"),data);
						break;
					case 2:
						pDlg->m_edit_data3.Format(_T("%04X"),data);
						break;
					case 3:
						pDlg->m_edit_data4.Format(_T("%04X"),data);
						break;
					case 4:
						pDlg->m_edit_data5.Format(_T("%04X"),data);
						break;
					case 5:
						pDlg->m_edit_data6.Format(_T("%04X"),data);
						break;
					case 6:
						pDlg->m_edit_data7.Format(_T("%04X"),data);
						break;
					case 7:
						pDlg->m_edit_data8.Format(_T("%04X"),data);
						break;
					default:
						break;
					}
				}
				data = pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx];
				pDlg->m_edit_chksum.Format(_T("%04X"),data);
				data = pJtpBuff[sizeof(JTP_FRAME)/2 - 1 + idx];
				pDlg->m_edit_footer.Format(_T("%04X"),data);


				// 통신 상태 표시줄	
				pDlg->m_edit_comm_status.SetBgColor(GREEN);		//백그라운드 색
				pDlg->m_edit_comm_status.m_strMsg = "Connected";
				pDlg->m_edit_comm_status.PostMessageW(_WM_THREAD_UPDATE);
				pDlg->UpdateData(FALSE);
			}
		}
		Sleep(200);

		GetSystemTime(&st_cur);
		st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
		if ( st_diff >= 3 ) //3초이상 응답이 없을 시에
		{
			pDlg->m_Jtp.jtpCommOk = 0;


			// 통신 상태 표시줄	
			pDlg->m_edit_comm_status.SetBgColor(YELLOW);		//백그라운드 색
			pDlg->m_edit_comm_status.m_strMsg = "Not Connected";
			pDlg->m_edit_comm_status.PostMessageW(_WM_THREAD_UPDATE);
			pDlg->UpdateData(FALSE);
		}

   }
   pDlg->m_hThread_JtpProc = NULL;
   // 통신 상태 표시줄
   pDlg->m_edit_comm_status.SetBgColor(YELLOW);		//백그라운드 색
   pDlg->m_edit_comm_status.m_strMsg = "Not Connected";
   pDlg->m_edit_comm_status.PostMessageW(_WM_THREAD_UPDATE);
   pDlg->UpdateData(FALSE);


   return TRUE;
}

BOOL JtpDlg::OnBnClickedButtonPortOpen_Open()
{
	BOOL ret = FALSE;
	CString stPortNum = _T("");
	DWORD dwThreadID;

	m_combo_port_num.GetLBText(m_combo_port_num.GetCurSel(), stPortNum);
	m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(stPortNum);
	if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
	{
		// 포트를 여는데 성공했다면
		if ( m_ComuPort.m_bConnected == TRUE )
		{
			//--> 포트 감시 쓰레드 생성.
			m_hThread_JtpProc = NULL;
			m_hThread_JtpProc = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_JTP_Protocol, this, 0, &dwThreadID);

			GetDlgItem(IDOK_EXIT)->EnableWindow(FALSE); //활성화 상태
			GetDlgItem(IDC_COMBO_PORT_NUM)->EnableWindow(FALSE); //활성화 상태
			m_button_port_open.SetWindowTextW(_T("Close"));
			ret = TRUE;
		}
	}


	return ret;
}

BOOL JtpDlg::OnBnClickedButtonPortOpen_Close()
{
	BOOL ret = FALSE;

	m_hThread_JtpProc = NULL;//Close Test Thread
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		m_ComuPort.ClosePort();
		ret = TRUE;
	}
	GetDlgItem(IDOK_EXIT)->EnableWindow(TRUE); //활성화 상태
	GetDlgItem(IDC_COMBO_PORT_NUM)->EnableWindow(TRUE); //활성화 상태
	m_button_port_open.SetWindowTextW(_T("Open"));

	return ret;
}

void JtpDlg::OnBnClickedButtonPortOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString stBtnText;
	m_button_port_open.GetWindowTextW(stBtnText);

	if ( stBtnText == "Open" )
	{
		OnBnClickedButtonPortOpen_Open();

	}
	else if ( stBtnText == "Close" )
	{
		OnBnClickedButtonPortOpen_Close();

	}

}


void JtpDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;

	// 포트를 여는데 성공했다면
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		UpdateData(TRUE);

		pJtpFrame = (JTP_FRAME *)m_Jtp.jtpSndBuff;
		pJtpBuff = (U16 *)m_Jtp.jtpSndBuff;

		pJtpFrame->uHeader = ConvertHexToInt(m_edit_out_header);
		pJtpFrame->uTgtId =  ConvertHexToInt(m_edit_out_tgtid);
		pJtpFrame->uSrcId =  ConvertHexToInt(m_edit_out_srcid);
		pJtpFrame->uParam =  ConvertHexToInt(m_edit_out_para);
		pJtpFrame->uCommand =  ConvertHexToInt(m_edit_out_cmd);
		pJtpFrame->uDataLen =  ConvertHexToInt(m_edit_out_datalen);

		// 데이터 복사
		for(idx = 0; idx < ConvertHexToInt(m_edit_out_datalen)/2; idx++)
		{
			switch(idx)
			{
			case 0:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data1);
				break;
			case 1:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data2);
				break;
			case 2:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data3);
				break;
			case 3:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data4);
				break;
			case 4:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data5);
				break;
			case 5:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data6);
				break;
			case 6:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data7);
				break;
			case 7:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data8);
				break;
			default:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			}
		}
		chkSum = m_Jtp.JTP_Calc_Chksum(m_Jtp.jtpSndBuff);
		m_edit_out_chksum.Format(_T("%04X"), chkSum);
		
		pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_chksum);
		pJtpBuff[sizeof(JTP_FRAME)/2 - 1 + idx] = ConvertHexToInt(m_edit_out_footer);

		sndSize = sizeof(JTP_FRAME) + ConvertHexToInt(m_edit_out_datalen);
		m_ComuPort.WriteComm(m_Jtp.jtpSndBuff, sndSize);

		UpdateData(FALSE);
	}
}

void JtpDlg::OnBnClickedExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CDialogEx::OnOK();
}


void JtpDlg::OnBnClickedButtonChksum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;
		
	UpdateData(TRUE);

	pJtpFrame = (JTP_FRAME *)m_Jtp.jtpSndBuff;
	pJtpBuff = (U16 *)m_Jtp.jtpSndBuff;

	pJtpFrame->uHeader = ConvertHexToInt(m_edit_out_header);
	pJtpFrame->uTgtId =  ConvertHexToInt(m_edit_out_tgtid);
	pJtpFrame->uSrcId =  ConvertHexToInt(m_edit_out_srcid);
	pJtpFrame->uParam =  ConvertHexToInt(m_edit_out_para);
	pJtpFrame->uCommand =  ConvertHexToInt(m_edit_out_cmd);
	pJtpFrame->uDataLen =  ConvertHexToInt(m_edit_out_datalen);

	// 데이터 복사
	for(idx = 0; idx < ConvertHexToInt(m_edit_out_datalen)/2; idx++)
	{
		switch(idx)
		{
		case 0:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data1);
			break;
		case 1:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data2);
			break;
		case 2:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data3);
			break;
		case 3:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data4);
			break;
		case 4:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data5);
			break;
		case 5:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data6);
			break;
		case 6:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data7);
			break;
		case 7:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = ConvertHexToInt(m_edit_out_data8);
			break;
		default:
			pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
			break;
		}
	}
	chkSum = m_Jtp.JTP_Calc_Chksum(m_Jtp.jtpSndBuff);
	m_edit_out_chksum.Format(_T("%04X"), chkSum);
		
	UpdateData(FALSE);

}
