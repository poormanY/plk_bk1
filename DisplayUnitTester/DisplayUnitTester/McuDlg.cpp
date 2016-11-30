// McuDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "McuDlg.h"
#include "afxdialogex.h"
#include "HIGHT_MCU.h"
#include "Color.h"

enum
{
	R7_MCU = 0,
	DISPLAY_MCU,
	OPX_MCU,
};

#define CSTRING_TEST_READY _T("검사 대기중")
#define CSTRING_TEST_ING   _T("검사 중")
#define CSTRING_TEST_PASS  _T("검사 성공")
#define CSTRING_TEST_FAIL  _T("검사 실패")

// McuDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(McuDlg, CDialogEx)

McuDlg::McuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(McuDlg::IDD, pParent)
	, m_radio_mcu(0)
	, m_edit_mcu_version(_T(""))
	, m_edit_mcu_test(_T(""))
{

}

McuDlg::~McuDlg()
{
}

void McuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio_mcu);
	DDX_Text(pDX, IDC_EDIT_MCU_VERSION, m_edit_mcu_version);
	DDX_Text(pDX, IDC_EDIT_MCU_TEST, m_edit_mcu_test);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_button_test);
	DDX_Control(pDX, IDOK, m_button_close);
	DDX_Control(pDX, IDC_EDIT_MCU_TEST, m_cedit_mcu_test);
}

// JtpDlg 메시지 처리기입니다.
// 초기값 설정
BOOL McuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 기본 포트 통신 설정 값
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;

	// 초기 선택 값
	m_radio_mcu = 0;

	// 검사 화면
	McuTestBG_Color = WHITE;
	McuTestText_Color = BLACK;
	m_edit_mcu_test = CSTRING_TEST_READY;

	// 글자 폰트 설정
	CFont g_editFont;
	g_editFont.CreateFont( 30, // nHeight 
                               0, // nWidth 
                               0, // nEscapement 
                               0, // nOrientation 
                               3, // nWeight 
                               0, // bItalic 
                               0, // bUnderline 
                               0, // cStrikeOut 
                               0, // nCharSet
                               OUT_DEFAULT_PRECIS,			// nOutPrecision 
                               0,                           // nClipPrecision 
                               DEFAULT_QUALITY,				// nQuality
                               DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
                               _T("굴림") ); // lpszFacename 
	GetDlgItem( IDC_EDIT_MCU_TEST )->SetFont( &g_editFont );
	g_editFont.Detach();

	// 에디트 박스 여백 부여하기
	CRect r;
    // 먼저 여백을 부여하고자 하는 에디트 컨트롤의 기본 여백정보를 읽어옵니다.
    m_cedit_mcu_test.GetRect(r); 
    // 좌/우 여백을 부여합니다.
    //r.left += 5;
    //r.right -= 5;
    // 상/하 여백을 부여합니다.
    r.top += 50;
    r.bottom -= 0;
	// 변경된 정보를 해당 에디트 컨트롤에 적용합니다.
    m_cedit_mcu_test.SetRect(r);


	McuTestStatus_Ready();
	UpdateData(FALSE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(McuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &McuDlg::OnBnClickedButtonTest)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, OnBnClickedRadio)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// McuDlg 메시지 처리기입니다.
void McuDlg::McuTestStatus_Ready(void)
{
	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);

	m_button_test.SetWindowTextW(_T("Test Start"));
}
void McuDlg::McuTestStatus_Testing(void)
{
	UpdateData(TRUE);

	if ( m_radio_mcu == R7_MCU )
	{
		m_edit_mcu_test = _T("R7 MCU\r\n");
	}
	else if ( m_radio_mcu == DISPLAY_MCU )
	{
		m_edit_mcu_test = _T("Display MCU\r\n");
	}
	else if ( m_radio_mcu == OPX_MCU )
	{
		m_edit_mcu_test = _T("OPX MCU\r\n");
	}

	McuTestBG_Color = YELLOW;
	McuTestText_Color = BLACK;
	m_edit_mcu_test += CSTRING_TEST_ING;

	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_button_test.SetWindowTextW(_T("Testing"));

	UpdateData(FALSE);
}



UINT McuDlg::Thread_McuTest_Display(McuDlg* pDlg)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL Connect_MCU = FALSE;
	HKEY hKey;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM에 시리얼포트 번호들이 등록되어 있음.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	TCHAR szData[100], szName[100];
	DWORD index = 0, dwSize=100, dwSize2 = 100, dwType = REG_SZ;
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
		//Port 연결 여부 + 데이터가 Jtp 프로토콜 형식인지 확인
		pDlg->strVersion = "";
		if ( pDlg->BoolChckPortOPen_Jtp(CString(szData), pDlg->m_iBaudRate, pDlg->m_iDataBit, pDlg->m_iStopBit, pDlg->m_iParity) == TRUE )
		{
			pDlg->UpdateData(TRUE);
			if ( pDlg->strVersion == pDlg->m_edit_mcu_version )
			{
				Connect_MCU = TRUE;

			}
			else
			{
				Connect_MCU = FALSE;

				AfxMessageBox(pDlg->strVersion);
			}
		}
        memset(szData, 0x00, sizeof(szData));  
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;  
        dwSize2 = 100;  
    }    
    RegCloseKey(hKey);

	if ( Connect_MCU == TRUE )
	{
		AfxMessageBox(_T("PASS"));

		// 검사 화면
		pDlg->McuTestBG_Color = GREEN;
		pDlg->McuTestText_Color = BLACK;
		pDlg->m_edit_mcu_test = CSTRING_TEST_PASS;
		pDlg->UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("FAIL"));

		// 검사 화면
		pDlg->McuTestBG_Color = RED;
		pDlg->McuTestText_Color = BLACK;
		pDlg->m_edit_mcu_test = CSTRING_TEST_FAIL;
		pDlg->UpdateData(FALSE);
	}

	pDlg->McuTestStatus_Ready();

	return TRUE;
}

void McuDlg::OnBnClickedRadio(UINT msg)
{
	UpdateData(TRUE);

	switch(m_radio_mcu)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}


void McuDlg::SendCheckMcuVersion_R7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;

	// 포트를 여는데 성공했다면
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		pJtpFrame = (JTP_FRAME *)m_Jtp.jtpSndBuff;
		pJtpBuff = (U16 *)m_Jtp.jtpSndBuff;

		pJtpFrame->uHeader = JTP_HEAD_VALUE;
		pJtpFrame->uTgtId =  JTP_ID_PIC;
		pJtpFrame->uSrcId =  JTP_ID_BLACKFIN;
		pJtpFrame->uParam =  _JTP_RESP_OK;
		pJtpFrame->uCommand =  CMD_READY;
		pJtpFrame->uDataLen =  0x0000;

		// 데이터 복사
		for(idx = 0; idx < (pJtpFrame->uDataLen)/2; idx++)
		{
			switch(idx)
			{
			case 0:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 1:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 2:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 3:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 4:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 5:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 6:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 7:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			default:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			}
		}
		chkSum = m_Jtp.JTP_Calc_Chksum(m_Jtp.jtpSndBuff);
		
		pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = chkSum;
		pJtpBuff[sizeof(JTP_FRAME)/2 - 1 + idx] = JTP_FOOT_VALUE;

		sndSize = sizeof(JTP_FRAME);
		m_ComuPort.WriteComm(m_Jtp.jtpSndBuff, sndSize);
	}
}

void McuDlg::SendCheckMcuVersion_Display()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;

	// 포트를 여는데 성공했다면
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		pJtpFrame = (JTP_FRAME *)m_Jtp.jtpSndBuff;
		pJtpBuff = (U16 *)m_Jtp.jtpSndBuff;

		pJtpFrame->uHeader = JTP_HEAD_VALUE;
		pJtpFrame->uTgtId =  JTP_ID_TACO;
		pJtpFrame->uSrcId =  JTP_ID_BLACKFIN;
		pJtpFrame->uParam =  _JTP_RESP_OK;
		pJtpFrame->uCommand =  CMD_READY;
		pJtpFrame->uDataLen =  0x0000;

		// 데이터 복사
		for(idx = 0; idx < (pJtpFrame->uDataLen)/2; idx++)
		{
			switch(idx)
			{
			case 0:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 1:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 2:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 3:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 4:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 5:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 6:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 7:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			default:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			}
		}
		chkSum = m_Jtp.JTP_Calc_Chksum(m_Jtp.jtpSndBuff);
		
		pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = chkSum;
		pJtpBuff[sizeof(JTP_FRAME)/2 - 1 + idx] = JTP_FOOT_VALUE;

		sndSize = sizeof(JTP_FRAME);
		m_ComuPort.WriteComm(m_Jtp.jtpSndBuff, sndSize);
	}
}



void McuDlg::SendCheckMcuVersion_OPX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;
	U08 *pTxData;
	OPX_STATIC_INFO *opx_static_info;

	// HIGHT 암호화
	HIGHT_KeySched(arbUserKey, arbRoundKey);

	pTxData = (U08 *)malloc(sizeof(OPX_STATIC_INFO));
	opx_static_info = (OPX_STATIC_INFO *)pTxData;

	opx_static_info->uRandomNumber = 0;
    opx_static_info->uOpxCount = 0;
	opx_static_info->uOpxVersion = 204;
    opx_static_info->uWakeUpTemperature = 55;
    opx_static_info->uWatchDogFireTime = 30;
    opx_static_info->uBplusThresholdVolt = 150;

	JTP_Encrypt(arbRoundKey, pTxData, 8);
	
	// 포트를 여는데 성공했다면
	if ( m_ComuPort.m_bConnected == TRUE )
	{
		pJtpFrame = (JTP_FRAME *)m_Jtp.jtpSndBuff;
		pJtpBuff = (U16 *)m_Jtp.jtpSndBuff;

		pJtpFrame->uHeader = JTP_HEAD_VALUE;
		pJtpFrame->uTgtId =  JTP_ID_PIC;
		pJtpFrame->uSrcId =  JTP_ID_CAM;
		pJtpFrame->uParam =  _JTP_RESP_OK;
		pJtpFrame->uCommand =  CMD_READY;
		pJtpFrame->uDataLen =  sizeof(OPX_STATIC_INFO);

		// 데이터 복사
		for(idx = 0; idx < (pJtpFrame->uDataLen)/2; idx++)
		{
			switch(idx)
			{
			case 0:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uRandomNumber;
				break;
			case 1:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uOpxCount;
				break;
			case 2:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uOpxVersion;
				break;
			case 3:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uWakeUpTemperature;
				break;
			case 4:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uWatchDogFireTime;
				break;
			case 5:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = opx_static_info->uBplusThresholdVolt;
				break;
			case 6:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			case 7:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			default:
				pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = 0x0000;
				break;
			}
		}
		chkSum = m_Jtp.JTP_Calc_Chksum(m_Jtp.jtpSndBuff);
		
		pJtpBuff[sizeof(JTP_FRAME)/2 - 2 + idx] = chkSum;
		pJtpBuff[sizeof(JTP_FRAME)/2 - 1 + idx] = JTP_FOOT_VALUE;

		sndSize = sizeof(JTP_FRAME);
		m_ComuPort.WriteComm(m_Jtp.jtpSndBuff, sndSize);

		free(pTxData);
	}
}



BOOL McuDlg::BoolChckPortOPen_Jtp(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity)
{
	BOOL Result = FALSE;
	BYTE aByte = 0x00; //데이터를 저장할 변수
	int i = 0, iSize = 0;
	SYSTEMTIME st_pre, st_cur;
	WORD st_diff = 0;
	VERSION_INFO *pVersion;
	MCU_STATIC_INFO *mcu_static_info;
	BYTE *DataBuff;

	// 포트가 닫혀 있을 경우에만 포트를 열기 위해
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(strPortName, pDisplayUnitTesterDlg->byIndexBaud(iBaudRate), pDisplayUnitTesterDlg->byIndexData(iDataBit), pDisplayUnitTesterDlg->byIndexStop(iStopBit), pDisplayUnitTesterDlg->byIndexParity(iParity)) ==TRUE)
		{
			// 포트를 여는데 성공했다면
			if ( m_ComuPort.m_bConnected == TRUE )
			{
				GetSystemTime(&st_pre);
				while( Result != TRUE )
				{
					GetSystemTime(&st_cur);
					st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
					// 3초 간 검사
					if ( st_diff >= 3 )
					{
						break;
					}
					
					if ( iSize == 0 )
					{
						// 버전 확인 커맨드를 송신
						UpdateData(TRUE);
						if ( m_radio_mcu == R7_MCU )
						{
							SendCheckMcuVersion_R7();
						}
						else if ( m_radio_mcu == DISPLAY_MCU )
						{
							SendCheckMcuVersion_Display();
						}
						else if ( m_radio_mcu == OPX_MCU )
						{
							SendCheckMcuVersion_OPX();
						}
						Sleep(200);
					}

					iSize =  (m_ComuPort.m_QueueRead).GetSize(); //포트로 들어온 데이터 갯수
												 //SetCommState에 설정된 내용 때문에 거의 8개씩 들어옴
					for ( i = 0; i < iSize; i++ ) //들어온 갯수 만큼 데이터를 읽어 와 JTP 프로토콜
					{
						(m_ComuPort.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴
						if ( m_Jtp.JTP_Frame_Get(aByte) == TRUE )
						{
							Result = TRUE;
								
							DataBuff = m_Jtp.JTP_RCV_DATA(m_Jtp.jtpBuff);
							
							if ( m_radio_mcu == R7_MCU )
							{
								pVersion = (VERSION_INFO *)DataBuff;	
								strVersion = pVersion->bVersionInfo;
							}
							else if ( m_radio_mcu == DISPLAY_MCU )
							{
								pVersion = (VERSION_INFO *)DataBuff;	
								strVersion = pVersion->bVersionInfo;
							}
							else if ( m_radio_mcu == OPX_MCU )
							{
								JTP_Decrypt(arbRoundKey, DataBuff, 8);
								mcu_static_info = (MCU_STATIC_INFO *)DataBuff;
								strVersion.Format(_T("%d"),mcu_static_info->uMcuVersion);
							}
						}
					}

				}
			}
		}
	}
	m_ComuPort.ClosePort();
	
	return Result;
}


void McuDlg::OnBnClickedButtonTest()
{
	// 검사 화면
	McuTestStatus_Testing();

	//--> MCU Test 화면 쓰레드 생성.
	DWORD dwThreadID; 
	m_hThread_McuTest = NULL;
	m_hThread_McuTest = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_McuTest_Display, this, 0, &dwThreadID);

}

 
HBRUSH McuDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	 switch(nCtlColor)
    {
        case CTLCOLOR_EDIT:
        {

        }
        break;
        // 읽기 전용 컨트롤
        case CTLCOLOR_STATIC:
        {
            if(pWnd->GetDlgCtrlID() == IDC_EDIT_MCU_TEST)
            {
                pDC->SetTextColor(McuTestText_Color);				
                pDC->SetBkColor(McuTestBG_Color);
				m_brush_mcu_test.CreateSolidBrush(McuTestBG_Color);
                return m_brush_mcu_test;
            }
        }
        break;
    }
 
 
    return hbr;
}
