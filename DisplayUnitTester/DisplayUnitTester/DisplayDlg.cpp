// DisplayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "DisplayDlg.h"
#include "afxdialogex.h"
#include "jtp.h"
#include "display.h"
#include "Color.h"
#include "wm_user.h"
#include <direct.h>   //getcwd

#define DISPLAY_COMM_CYCLE 0	// 10ms

#define FACTORY_VER
//#define _DEBUG

// DisplayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(DisplayDlg, CDialogEx)

DisplayDlg::DisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DisplayDlg::IDD, pParent)
	, m_edit_input_button(0)
	, m_check_device_on(TRUE)
	, m_check_install_mode(FALSE)
	, m_check_device_error(FALSE)
	, m_check_display_on(TRUE)
	, m_check_brake(FALSE)
	, m_check_turn_left(FALSE)
	, m_check_turn_right(FALSE)
	, m_check_recording(FALSE)
	, m_check_lane_detect(FALSE)
	, m_check_ldw_left(FALSE)
	, m_check_ldw_right(FALSE)
	, m_check_hmw_detect(FALSE)
	, m_check_hmw_warn(FALSE)
	, m_check_fcw_warn(FALSE)
	, m_check_vb_warn(FALSE)
	, m_check_fcda_run(FALSE)
	, m_check_fcda_detect(FALSE)
	, m_check_fcda_alarm(FALSE)
	, m_check_pd_detect(FALSE)
	, m_check_pd_warn(FALSE)
	, m_check_hba_on(FALSE)
	, m_check_hba_warn(FALSE)
	, m_radio_day(1)
	, m_edt_ttt(0)
	, m_edt_tsr_speed(0)
	, m_edt_tsr_overspeed(0)
	, m_edit_display_version(_T(""))
	, m_edit_set_version(_T("v.2.2.6"))
	, m_check_ldw_no_dispaly(FALSE)
	, m_check_ldw_error(FALSE)
	, m_check_signal_en(FALSE)
	, m_check_hmw_warn2(FALSE)
	, m_check_hmw_warn3(FALSE)
{
}

DisplayDlg::~DisplayDlg()
{
}

void DisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_CONNECT, m_progConnect);
	DDX_Control(pDX, IDC_COMBO_PORT_NUM, m_combo_PortNum);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_button_connect);
	DDX_Text(pDX, IDC_EDIT_BUTTON_STATE, m_edit_input_button);

	DDX_Check(pDX, IDC_CHECK_DEVICE_ON, m_check_device_on);
	DDX_Check(pDX, IDC_CHECK_INSTALL_MODE, m_check_install_mode);
	DDX_Check(pDX, IDC_CHECK_DEVICE_ERROR, m_check_device_error);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_ON, m_check_display_on);
	DDX_Check(pDX, IDC_CHECK_BRAKE, m_check_brake);
	DDX_Check(pDX, IDC_CHECK_TURN_LEFT, m_check_turn_left);
	DDX_Check(pDX, IDC_CHECK_TURN_RIGHT, m_check_turn_right);
	DDX_Check(pDX, IDC_CHECK_RECORDING, m_check_recording);
	DDX_Check(pDX, IDC_CHECK_LDW_DETECT, m_check_lane_detect);
	DDX_Check(pDX, IDC_CHECK_LDW_LEFT, m_check_ldw_left);
	DDX_Check(pDX, IDC_CHECK_LDW_RIGHT, m_check_ldw_right);
	DDX_Check(pDX, IDC_CHECK_HMW_DETECT, m_check_hmw_detect);
	DDX_Check(pDX, IDC_CHECK_HMW_WARN, m_check_hmw_warn);
	DDX_Check(pDX, IDC_CHECK_FCW_WARN, m_check_fcw_warn);
	DDX_Check(pDX, IDC_CHECK_VB_WARN, m_check_vb_warn);
	DDX_Check(pDX, IDC_CHECK_FCDA_RUN, m_check_fcda_run);
	DDX_Check(pDX, IDC_CHECK_FCDA_DETECT, m_check_fcda_detect);
	DDX_Check(pDX, IDC_CHECK_FCDA_ALARM, m_check_fcda_alarm);
	DDX_Check(pDX, IDC_CHECK_PD_DETECT, m_check_pd_detect);
	DDX_Check(pDX, IDC_CHECK_PD_WARN, m_check_pd_warn);
	DDX_Check(pDX, IDC_CHECK_HBA_ON, m_check_hba_on);
	DDX_Check(pDX, IDC_CHECK_HBA_WARN, m_check_hba_warn);
	DDX_Check(pDX, IDC_CHECK_LDW_NO_DISPLAY, m_check_ldw_no_dispaly);
	DDX_Check(pDX, IDC_CHECK_LDW_ERROR, m_check_ldw_error);
	DDX_Check(pDX, IDC_CHECK_SIGNAL_ENABLE, m_check_signal_en);
	DDX_Radio(pDX, IDC_RADIO1, m_radio_day);
	DDX_Text(pDX, IDC_EDIT_TTT, m_edt_ttt);
	DDX_Text(pDX, IDC_EDIT_TSR_SPEED, m_edt_tsr_speed);
	DDX_Text(pDX, IDC_EDIT_OVER_SPEED, m_edt_tsr_overspeed);
	DDX_Text(pDX, IDC_EDIT_SET_VERSION, m_edit_set_version);

	DDX_Control(pDX, IDC_EDIT_NOTICE, m_edit_notice);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_button_test);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_VERSION, m_edit_display_version);
	DDX_Check(pDX, IDC_CHECK_HMW_WARN2, m_check_hmw_warn2);
	DDX_Check(pDX, IDC_CHECK_HMW_WARN3, m_check_hmw_warn3);
}


BEGIN_MESSAGE_MAP(DisplayDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_SEARCH, &DisplayDlg::OnBnClickedButtonDisplayConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &DisplayDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &DisplayDlg::OnBnClickedButtonTest)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, OnBnClickedRadio)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &DisplayDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// DisplayDlg 메시지 처리기입니다.
// 초기값 설정
BOOL DisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 기본 포트 통신 설정 값
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;
#ifndef _DEBUG
	// Create a smooth child progress control.
	m_progConnect.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH, CRect(100,65,200,90), this, IDC_PROGRESS_CONNECT);
	m_progConnect.SetRange(0,100);//진행바의 전체폭을 결정
	m_progConnect.SetStep(10);//진행바의 진행폭을 결정
#endif
	// Comport 콤보 박스
	int comportIdx = 0;
	CString comportNum;
	for (comportIdx = 1; comportIdx < 11; comportIdx++)
	{
		comportNum.Format(_T("COM%d"),comportIdx);
		m_combo_PortNum.AddString(comportNum);
	}
	m_combo_PortNum.SetCurSel(0);	//텍스트 선택
	// notice 에디터 박스
	UpdateData(TRUE);
	
    LOGFONT oLogFont;
    GetFont()->GetLogFont(&oLogFont);
    oLogFont.lfHeight = -30;					//글자 크기
    m_edit_notice.SetLogFont(&oLogFont);
    m_edit_notice.SetBgColor(YELLOW);		//백그라운드 색
    m_edit_notice.SetTextColor(RGB(0,0,0));	// 글자 색
    m_edit_notice.SetTextFormat(DT_CENTER|DT_VCENTER);
	m_edit_notice.m_strMsg = "Not Connected";
	m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
	UpdateData(FALSE);
	// ADAS Data 초기값 설정
	m_check_device_on = 1;
	m_check_install_mode = 0;
	m_check_device_error = 0;
	m_check_display_on = 1;
	m_check_brake = 0;
	m_check_turn_left = 0;
	m_check_turn_right = 0;
	m_check_recording = 0;
	m_check_lane_detect = 0;
	m_check_ldw_left = 0;
	m_check_ldw_right = 0;
	m_check_hmw_detect = 0;
	m_check_hmw_warn = 0;
	m_check_hmw_warn2 = 0;
	m_check_hmw_warn3 = 0;
	m_check_fcw_warn = 0;
	m_check_vb_warn = 0;
	m_check_fcda_run = 0;
	m_check_fcda_detect = 0;
	m_check_fcda_alarm = 0;
	m_check_pd_detect = 0;
	m_check_pd_warn = 0;
	m_check_hba_on = 0;
	m_check_hba_warn = 0;
	m_radio_day = 1;
	m_edt_ttt = 0;
	m_edt_tsr_speed = 0;
	m_edt_tsr_overspeed = 0;
	m_edit_set_version = "v.2.2.6";
	UpdateData(FALSE);
	// Test 버튼 초기 설정 비활성화
	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE); //활성화 상태


	// Setup
	FILE *pFile;
    char  szData[256];
	CString strFileName;
	char m_szPath[_MAX_PATH];
	char m_szExt[_MAX_EXT];
	char m_szFname[_MAX_FNAME];
	char m_szDir[_MAX_DIR];
	char m_szDrive[_MAX_DRIVE];
    char *pstrBuffer = NULL;
	CString strFactoryVer;
 
    pstrBuffer = getcwd( m_szPath, _MAX_PATH );
	_splitpath(m_szPath, m_szDrive, m_szDir, m_szFname, m_szExt);

    strFileName  = m_szPath;
    strFileName += "\\DisplayUnitTester.ini";

    pFile = fopen((CStringA)strFileName, "rt");
    if (pFile == NULL)
    {
        return false;
    }
	fscanf(pFile, "DISPlAY_VERSION     = %s\n", szData); m_DisplayVersion       = szData;
	fscanf(pFile, "FACTORY_FIRMWARE    = %s\n", szData); strFactoryVer       = szData;

	m_edit_set_version = m_DisplayVersion;

	fclose(pFile);

	if ( strFactoryVer == "1" )
	{
		GetDlgItem(IDC_CHECK_DEVICE_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_INSTALL_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEVICE_ERROR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DISPLAY_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_BRAKE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_TURN_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_TURN_RIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_RECORDING)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LDW_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LDW_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LDW_RIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HMW_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HMW_WARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HMW_WARN2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HMW_WARN3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FCW_WARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_VB_WARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FCDA_RUN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FCDA_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FCDA_ALARM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PD_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PD_WARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HBA_ON)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HBA_WARN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LDW_NO_DISPLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LDW_ERROR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SIGNAL_ENABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TTT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TSR_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OVER_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_VERSION)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	return TRUE;
}

BOOL DisplayDlg::BoolChckPortOPen_Jtp(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity)
{
	BOOL Result = FALSE;
	BYTE aByte = 0x00; //데이터를 저장할 변수
	int i = 0, iSize = 0;
	SYSTEMTIME st_pre, st_cur;
	WORD st_diff = 0;

	// 포트가 닫혀 있을 경우에만 포트를 열기 위해
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(strPortName, pDisplayUnitTesterDlg->byIndexBaud(iBaudRate), pDisplayUnitTesterDlg->byIndexData(iDataBit), pDisplayUnitTesterDlg->byIndexStop(iStopBit), pDisplayUnitTesterDlg->byIndexParity(iParity)) ==TRUE)
		{
			// 포트를 여는데 성공했다면
			if ( m_ComuPort.m_bConnected == TRUE )
			{
				GetSystemTime(&st_pre);
				while(1)
				{
					GetSystemTime(&st_cur);
					st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
					// 3초 간 검사
					if ( st_diff >= 3 )
					{
						break;
					}


					iSize =  (m_ComuPort.m_QueueRead).GetSize(); //포트로 들어온 데이터 갯수
												 //SetCommState에 설정된 내용 때문에 거의 8개씩 들어옴					
					for ( i = 0; i < iSize; i++ ) //들어온 갯수 만큼 데이터를 읽어 와 JTP 프로토콜
					{
						(m_ComuPort.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴							
						if ( m_Jtp.JTP_Frame_Get(aByte) == TRUE )
						{
							Result = TRUE;
						}
					}
				}
			}
		}
	}
	m_ComuPort.ClosePort();
	
	return Result;
}


void DisplayDlg::OnBnClickedButtonDisplayConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL Connect_Display = FALSE;
	HKEY hKey;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM에 시리얼포트 번호들이 등록되어 있음.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	TCHAR szData[100], szName[100];
	DWORD index = 0, dwSize=100, dwSize2 = 100, dwType = REG_SZ;
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));
#ifndef _DEBUG
	m_progConnect.SetPos(0);//진행바의 위치를 직접 선언
	m_progConnect.StepIt();//진행폭만큼 전진
#endif
	//hKey - 레지스터키 핸들  
    //index - 값을 가져올 인덱스.. 다수의 값이 있을 경우 필요  
    //szName - 항목값이 저장될 배열  
    //dwSize - 배열의 크기  
    while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))  
    {
		index++;
#ifndef _DEBUG
		m_progConnect.StepIt();//진행폭만큼 전진
#endif
        //szName-레지터스터 항목의 이름  
        //dwType-항목의 타입, 여기에서는 널로 끝나는 문자열  
        //szData-항목값이 저장될 배열  
        //dwSize2-배열의 크기
        RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		//Port 연결 여부 + 데이터가 Jtp 프로토콜 형식인지 확인
		if ( BoolChckPortOPen_Jtp(CString(szData), m_iBaudRate, m_iDataBit, m_iStopBit, m_iParity) == TRUE )
		{
			//Jtp Display 프로토콜 형식인지 확인
			if ( m_Jtp.JTP_Valid_Chk_Display(m_Jtp.jtpBuff) == _JTP_RESP_OK )
			{
				m_iSerialPort = pDisplayUnitTesterDlg->toIdxComPort(CString(szData));
				Connect_Display = TRUE;
				break;
			}
		}		    
        memset(szData, 0x00, sizeof(szData));  
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;  
        dwSize2 = 100;  
    }    
    RegCloseKey(hKey);
#ifndef _DEBUG
	m_progConnect.SetPos(100);//진행바의 위치를 직접 선언
#endif

	if ( Connect_Display == TRUE )
	{
		m_combo_PortNum.SetCurSel(m_iSerialPort);	//텍스트 선택
		m_edit_notice.m_strMsg = "Display Ready";
		m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
	}
	else
	{
		m_edit_notice.m_strMsg = "Not Connected";
		m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
		AfxMessageBox(_T("No Connected Display module"));
	}
}



// 포트를 감시하고, 읽힌 내용이 있으면.
UINT DisplayDlg::Thread_JTP_Display(DisplayDlg* pDlg)
{
   int i = 0, iSize = 0;
   int sndSize = 0;
   BYTE aByte;
   CString strButton = _T("");
   HUB_INFO *pHubInfo;
   SYSTEMTIME st_pre, st_cur;
   WORD st_diff = 0;

   GetSystemTime(&st_pre);
   GetSystemTime(&st_cur);
   
   pDlg->m_edit_display_version = _T("");
   pDlg->UpdateData(FALSE);

   while (pDlg->m_ComuPort.m_bConnected)//포트가 연결되면 무한 루프에 들어감
   {
 		iSize =  (pDlg->m_ComuPort.m_QueueRead).GetSize(); //포트로 들어온 데이터 갯수
													//SetCommState에 설정된 내용 때문에 거의 8개씩 들어옴					
		for ( i = 0; i < iSize; i++ ) //들어온 갯수 만큼 데이터를 읽어 와 JTP 프로토콜
		{
			(pDlg->m_ComuPort.m_QueueRead).GetByte(&aByte);//큐에서 데이터 한개를 읽어옴							
			if ( pDlg->m_Jtp.JTP_Frame_Get(aByte) == TRUE )
			{
				GetSystemTime(&st_pre);
				if ( (pDlg->m_Jtp.JTP_RCV_Command(pDlg->m_Jtp.jtpBuff)) == CMD_SEND_ADAS )
				{
					pDlg->UpdateData(TRUE);
					pDlg->m_edit_input_button = pDlg->m_Jtp.JTP_Display_Get_Button(pDlg->m_Jtp.jtpBuff);
					strButton.Format(_T("%d"), pDlg->m_edit_input_button);
					pDlg->GetDlgItem(IDC_EDIT_BUTTON_STATE)->SetWindowTextW(strButton);
					switch( pDlg->m_edit_input_button )
					{
					case BTN_DEFAULT:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(FALSE); //활성화 상태
						break;
					case FUNC_OFF:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(TRUE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(FALSE); //활성화 상태
						break;
					case VOL_UP:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(TRUE); //활성화 상태
						break;
					case VOL_DOWN:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(TRUE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(FALSE); //활성화 상태
						break;
					case VOL_UPnDOWN:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(TRUE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(TRUE); //활성화 상태
						break;
					default:
						pDlg->GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
						pDlg->GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(FALSE); //활성화 상태
						break;
					}

					// Display에서 데이터를 받으면 현재 ADAS데이터를 Display에 송신한다.
					pHubInfo = new HUB_INFO;
					memset((void *)pHubInfo, 0, sizeof(HUB_INFO));				

					if(pDlg->m_check_device_on)		pHubInfo->bDeviceState |= DEVICE_ON;
					if(pDlg->m_check_install_mode)	pHubInfo->bDeviceState |= DEVICE_INSTALL_MODE;
					if(pDlg->m_check_device_error)	pHubInfo->bDeviceState |= DEVICE_ERROR;
					if(pDlg->m_check_display_on)	pHubInfo->bDisplayModuleState |= DISPLAY_ON;
					if(pDlg->m_check_signal_en)		pHubInfo->bSignal |= ADAS_SIGNAL_DISPLAY;
					if(pDlg->m_check_brake)			pHubInfo->bSignal |= ADAS_BRAKE_ON;
					if(pDlg->m_check_turn_left)		pHubInfo->bSignal |= ADAS_TURN_LEFT_ON;
					if(pDlg->m_check_turn_right)	pHubInfo->bSignal |= ADAS_TURN_RIGHT_ON;
					if(pDlg->m_check_recording)		pHubInfo->bSignal |= ADAS_MODE_SAVING;
					if(pDlg->m_check_lane_detect)	pHubInfo->bLaneDetectState |= ADAS_LANE_DETECT;
					if(pDlg->m_check_ldw_left)		pHubInfo->bLaneDetectState |= ADAS_LANE_LEFT_WARN;
					if(pDlg->m_check_ldw_right)		pHubInfo->bLaneDetectState |= ADAS_LANE_RIGHT_WARN;
					if(pDlg->m_check_ldw_no_dispaly) pHubInfo->bLaneDetectState |= ADAS_LANE_NO_DISPLAY_DETECT;
					if(pDlg->m_check_ldw_error)		pHubInfo->bLaneDetectState |= ADAS_LANE_ERROR;
					if(pDlg->m_check_hmw_detect)	pHubInfo->uFcwState |= ADAS_FCW_HMW_DETECT;
					if(pDlg->m_check_hmw_warn)		pHubInfo->uFcwState |= ADAS_FCW_HMW_WARN;
					if(pDlg->m_check_hmw_warn2)		pHubInfo->uFcwState |= ADAS_FCW_HMW_WARN2;
					if(pDlg->m_check_hmw_warn3)		pHubInfo->uFcwState |= ADAS_FCW_HMW_WARN3;
					if(pDlg->m_check_fcw_warn)		pHubInfo->uFcwState |= ADAS_FCW_FCW_WARN;
					if(pDlg->m_check_vb_warn)		pHubInfo->uFcwState |= ADAS_FCW_VB_WARN;
					if(pDlg->m_check_fcda_run)		pHubInfo->uFcwState |= ADAS_FCDA_RUNNING;
					if(pDlg->m_check_fcda_detect)	pHubInfo->uFcwState |= ADAS_FCDA_DETECT;
					if(pDlg->m_check_fcda_alarm)	pHubInfo->uFcwState |= ADAS_FCDA_WARN;
					if(pDlg->m_check_pd_detect)		pHubInfo->bPdState |= ADAS_PD_DETECT;
					if(pDlg->m_check_pd_warn)		pHubInfo->bPdState |= ADAS_PD_WARN;
					if(pDlg->m_check_hba_on)		pHubInfo->bHBA |= ADAS_HBA_ON;
					if(pDlg->m_check_hba_warn)		pHubInfo->bHBA |= ADAS_HBA_OFF;
					if(pDlg->m_radio_day)			pHubInfo->bSignal |= ADAS_MODE_DAY_NIGHT;
					// TTT 값
					if(pDlg->m_edt_ttt == 0)		pHubInfo->uHmwTTT = 0x8000;
					else							pHubInfo->uHmwTTT = (pDlg->m_edt_ttt & 0xFFFF);
					// TSR 표지판 인식값
					pHubInfo->uTSR = (pDlg->m_edt_tsr_speed & ADAS_TSR_KPH);
					// TSR 오버 스피드 값
					pHubInfo->bTsrOverSpd = (pDlg->m_edt_tsr_overspeed & 0xFF);

					// WATEX 데이터 프로토콜
					if ( pDlg->m_edit_set_version == _T("WATEX") )
					{
						sndSize = pDlg->m_Jtp.JTP_Send_Data_Hub_to_Display(pHubInfo);
						pDlg->m_ComuPort.WriteComm(pDlg->m_Jtp.jtpSndBuff, sndSize);
					}
					// ADAS 데이터 프로토콜
					else if ( pDlg->m_edit_display_version != "")
					{
						sndSize = pDlg->m_Jtp.JTP_Send_Data_Hub_to_Display(pHubInfo);
						pDlg->m_ComuPort.WriteComm(pDlg->m_Jtp.jtpSndBuff, sndSize);
					}
					// 버전 체크 프로토콜
					else
					{
						sndSize = pDlg->m_Jtp.JTP_Send_Ready_Hub_to_Display(pHubInfo);
						pDlg->m_ComuPort.WriteComm(pDlg->m_Jtp.jtpSndBuff, sndSize);
					}

					delete[] pHubInfo;
				}
				else if ( (pDlg->m_Jtp.JTP_RCV_Command(pDlg->m_Jtp.jtpBuff)) == CMD_READY )
				{
					pDlg->m_edit_display_version = pDlg->m_Jtp.JTP_Display_Get_Version(pDlg->m_Jtp.jtpBuff);
					pDlg->UpdateData(FALSE);
				}
			}
		}
		Sleep(DISPLAY_COMM_CYCLE);

		GetSystemTime(&st_cur);
		st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
		if ( st_diff >= 2 ) //2초이상 응답이 없을 시에
		{
			pDlg->m_edit_set_version = pDlg->m_DisplayVersion;
			pDlg->m_Jtp.jtpCommOk = 0;
			pDlg->m_edit_display_version = _T("");
			pDlg->UpdateData(FALSE);
		}

   }
   pDlg->m_hThread_JtpDisplay = NULL;

   return TRUE;
}


void DisplayDlg::OnBnClickedButtonConnect_Connect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL Connect_Display = FALSE;
	DWORD dwThreadID;

	m_iSerialPort = m_combo_PortNum.GetCurSel();
	//Port 연결 여부 + 데이터가 Jtp 프로토콜 형식인지 확인
	if ( BoolChckPortOPen_Jtp(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), m_iBaudRate, m_iDataBit, m_iStopBit, m_iParity) == TRUE )
	{
		//Jtp Display 프로토콜 형식인지 확인
		if ( m_Jtp.JTP_Valid_Chk_Display(m_Jtp.jtpBuff) == _JTP_RESP_OK )
		{
			Connect_Display = TRUE;
		}
	}

	if ( Connect_Display == TRUE )
	{
		// 포트가 닫혀 있을 경우에만 포트를 열기 위해
		if ( m_ComuPort.m_bConnected == FALSE )
		{
			if ( m_ComuPort.OpenPort(pDisplayUnitTesterDlg->byIndexComPort(m_iSerialPort), pDisplayUnitTesterDlg->byIndexBaud(m_iBaudRate), pDisplayUnitTesterDlg->byIndexData(m_iDataBit), pDisplayUnitTesterDlg->byIndexStop(m_iStopBit), pDisplayUnitTesterDlg->byIndexParity(m_iParity)) ==TRUE)
			{
				// 포트를 여는데 성공했다면
				if ( m_ComuPort.m_bConnected == TRUE )
				{
					//--> 포트 감시 쓰레드 생성.
					m_hThread_JtpDisplay = NULL;
					m_hThread_JtpDisplay = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_JTP_Display, this, 0, &dwThreadID);

					if (m_hThread_JtpDisplay == NULL)
					{
						AfxMessageBox(_T("Thread JTP Display Failed!"));
					}
					else
					{
						UpdateData();
						m_edit_notice.m_strMsg = "Connected";
						m_button_connect.SetWindowTextW(_T("Disconnect"));

						GetDlgItem(IDC_COMBO_PORT_NUM)->EnableWindow(FALSE);
						GetDlgItem(IDOK)->EnableWindow(FALSE);
						GetDlgItem(IDC_BUTTON_DISPLAY_SEARCH)->EnableWindow(FALSE); //활성화 상태
						GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE); //활성화 상태
						m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
						UpdateData(FALSE);
					}
				}
			}
		}
	}
	else
	{
		AfxMessageBox(_T("No Connected Display module"));
	}
}

void DisplayDlg::OnBnClickedButtonConnect_Disconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ComuPort.ClosePort();
}

void DisplayDlg::OnBnClickedButtonConnect()
{
	CString strBtnText;
	m_button_connect.GetWindowTextW(strBtnText);

	if ( strBtnText == "Connect" )
	{
		OnBnClickedButtonConnect_Connect();
	}
	else if ( strBtnText == "Disconnect" )
	{
		OnBnClickedButtonConnect_Disconnect();
		m_button_connect.SetWindowTextW(_T("Connect"));

		UpdateData(TRUE);
		m_edit_input_button = 0;
		GetDlgItem(IDC_COMBO_PORT_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DISPLAY_SEARCH)->EnableWindow(TRUE); //활성화 상태
		GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE); //활성화 상태
		m_hThread_TestDisplay = NULL;//Close Test Thread

		GetDlgItem(IDC_BUTTON_VOL_DOWN)->EnableWindow(FALSE); //활성화 상태
		GetDlgItem(IDC_BUTTON_FUNC_OFF)->EnableWindow(FALSE); //활성화 상태
		GetDlgItem(IDC_BUTTON_VOL_UP)->EnableWindow(FALSE); //활성화 상태

		m_edit_notice.m_strMsg = "Not Connected";
		m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
		UpdateData(FALSE);
	}
}

typedef enum
{
	Test_Start = 0,
	Test_Check_Version,
	Test_Input_Button1,
	Test_Input_Button2,
	Test_Input_Button3,
	Test_Input_Button4,
	Test_Output_Install_Mode,
	Test_End,
}TEST_STEP;

UINT DisplayDlg::Thread_Test_Display(DisplayDlg* pDlg)
{
	int TestStep = Test_Start;
	int notice_write = 0;
	int LedTest = 0;
	
	while ( pDlg->m_hThread_TestDisplay != NULL )
	{
		pDlg->UpdateData(TRUE);
		// WATEX 데이터 프로토콜
		if ( pDlg->m_edit_set_version == _T("WATEX") )
		{
			switch(TestStep)
			{
			case Test_Start:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Test Ready";
					pDlg->m_edit_notice.m_strMsg = "검사 준비";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}
				pDlg->m_check_display_on = 1;
				pDlg->m_check_device_on = 1;
				pDlg->UpdateData(FALSE);

				if ( pDlg->m_Jtp.jtpCommOk == 1 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Check_Version:
				TestStep++;
			case Test_Input_Button1:
				TestStep++;
			case Test_Input_Button2:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Volume Up";
					pDlg->m_edit_notice.m_strMsg = "오른쪽 버튼";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 2 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button3:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Volume Down";
					pDlg->m_edit_notice.m_strMsg = "왼쪽 버튼";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 3 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button4:
				TestStep++;
				break;
			case Test_Output_Install_Mode:
				if ( notice_write == 0 )
				{					
					if ( LedTest == 0 )
					{
						pDlg->m_check_hmw_warn2 = 0;
						pDlg->m_check_hmw_warn3 = 1;
						pDlg->UpdateData(FALSE);
					}
					else if ( LedTest == 1 )
					{
						pDlg->m_check_hmw_warn2 = 0;
						pDlg->m_check_hmw_warn3 = 1;
						pDlg->UpdateData(FALSE);
					}
					else
					{
						pDlg->m_check_hmw_warn2 = 0;
						pDlg->m_check_hmw_warn3 = 1;
						pDlg->UpdateData(FALSE);
					}
					pDlg->m_edt_ttt+=10;
					pDlg->UpdateData(FALSE);

					LedTest++;
					LedTest %= 3;

					//pDlg->m_edit_notice.m_strMsg = "LED Check";
					pDlg->m_edit_notice.m_strMsg = "LED 확인";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				Sleep(200);

				break;
			}
		}
		else
		{
			switch(TestStep)
			{
			case Test_Start:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Test Ready";
					pDlg->m_edit_notice.m_strMsg = "검사 준비";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}
				pDlg->m_check_display_on = 1;
				pDlg->m_check_device_on = 1;
				pDlg->m_check_device_error = 1;
				pDlg->UpdateData(FALSE);

				if ( pDlg->m_Jtp.jtpCommOk == 1 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Check_Version:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Check Version\n";
					pDlg->m_edit_notice.m_strMsg = "버전 확인\n";
					pDlg->UpdateData(TRUE);
					pDlg->m_edit_notice.m_strMsg += pDlg->m_edit_set_version;
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				if ( pDlg->m_edit_display_version == pDlg->m_edit_set_version )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button1:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Func Off";
					pDlg->m_edit_notice.m_strMsg = "가운데 버튼";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 1 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button2:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Volume Up";
					pDlg->m_edit_notice.m_strMsg = "오른쪽 버튼";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 2 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button3:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Volume Down";
					pDlg->m_edit_notice.m_strMsg = "왼쪽 버튼";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 3 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Input_Button4:
				if ( notice_write == 0 )
				{
					notice_write = 1;
					//pDlg->m_edit_notice.m_strMsg = "Install Mode";
					pDlg->m_edit_notice.m_strMsg = "왼쪽 + 오른쪽";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				pDlg->UpdateData(TRUE);
				if ( pDlg->m_edit_input_button == 4 )
				{
					notice_write = 0;
					TestStep++;
				}
				break;
			case Test_Output_Install_Mode:
				if ( notice_write == 0 )
				{
					if ( LedTest == 0 )
					{
						pDlg->m_check_device_error = 1;

						pDlg->UpdateData(FALSE);
					}
					else if ( LedTest == 1 )
					{
						pDlg->m_check_device_error = 0;
						pDlg->m_check_install_mode = 0;
						pDlg->m_check_ldw_error = 1;
						pDlg->m_check_lane_detect = 0;
						pDlg->m_check_hmw_detect = 1;
						pDlg->m_check_hmw_warn = 0;
						pDlg->m_check_pd_detect = 1;
						pDlg->m_check_pd_warn = 0;
						pDlg->m_check_signal_en = 1;
						pDlg->m_check_brake = 1;
						pDlg->m_check_recording = 1;
						pDlg->m_radio_day = 1;
						pDlg->m_edt_ttt = 8800;		
						pDlg->UpdateData(FALSE);
					}
					else
					{
						pDlg->m_check_device_error = 0;
						pDlg->m_check_install_mode = 0;
						pDlg->m_check_ldw_error = 0;
						pDlg->m_check_lane_detect = 1;
						pDlg->m_check_hmw_detect = 0;
						pDlg->m_check_hmw_warn = 1;
						pDlg->m_check_pd_detect = 0;
						pDlg->m_check_pd_warn = 1;
						pDlg->m_check_signal_en = 1;
						pDlg->m_check_brake = 1;
						pDlg->m_check_recording = 1;
						pDlg->m_radio_day = 1;
						pDlg->m_edt_ttt = 8800;
						pDlg->UpdateData(FALSE);
					}
					LedTest++;
					LedTest %= 3;

					//pDlg->m_edit_notice.m_strMsg = "LED Check";
					pDlg->m_edit_notice.m_strMsg = "LED 확인";
					pDlg->m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
				}

				Sleep(2000);

				break;
			}
		}

		if ( pDlg->m_Jtp.jtpCommOk == 0 )
		{
			TestStep = Test_Start;
			notice_write = 0;
		}
		Sleep(1);
	}

	pDlg->m_button_test.SetWindowTextW(_T("Test"));
	pDlg->m_hThread_TestDisplay = NULL;
	return TRUE;
}

void DisplayDlg::OnBnClickedButtonTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DWORD dwThreadID;
	CString strBtnText;
	m_button_test.GetWindowTextW(strBtnText);

	if ( strBtnText == "Test" )
	{
		m_button_test.SetWindowTextW(_T("Testing"));

		// 테스트 쓰레드 생성
		m_hThread_TestDisplay = NULL;
		m_hThread_TestDisplay = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_Test_Display, this, 0, &dwThreadID);

		if (m_hThread_TestDisplay == NULL)
		{
			AfxMessageBox(_T("Test Thread Failed!"));
		}
	}
	else if ( strBtnText == "Testing" )
	{
		m_button_test.SetWindowTextW(_T("Test"));

		//Close Test Thread
		m_hThread_TestDisplay = NULL;
	}
}

void DisplayDlg::OnBnClickedRadio(UINT msg)
{
	UpdateData(TRUE);

	switch(m_radio_day)
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

void DisplayDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strBtnText;
	m_button_connect.GetWindowTextW(strBtnText);

	if ( strBtnText == "Disconnect" )
	{
		OnBnClickedButtonConnect_Disconnect();
	}

	CDialogEx::OnOK();
}
