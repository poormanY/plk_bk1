// McuDlg.cpp : ���� �����Դϴ�.
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

#define CSTRING_TEST_READY _T("�˻� �����")
#define CSTRING_TEST_ING   _T("�˻� ��")
#define CSTRING_TEST_PASS  _T("�˻� ����")
#define CSTRING_TEST_FAIL  _T("�˻� ����")

// McuDlg ��ȭ �����Դϴ�.

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

// JtpDlg �޽��� ó�����Դϴ�.
// �ʱⰪ ����
BOOL McuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �⺻ ��Ʈ ��� ���� ��
	m_iStopBit = 0;
	m_iSerialPort = 0;
	m_iParity = 0;
	m_iDataBit = 3;
	m_iBaudRate = 1;

	// �ʱ� ���� ��
	m_radio_mcu = 0;

	// �˻� ȭ��
	McuTestBG_Color = WHITE;
	McuTestText_Color = BLACK;
	m_edit_mcu_test = CSTRING_TEST_READY;

	// ���� ��Ʈ ����
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
                               _T("����") ); // lpszFacename 
	GetDlgItem( IDC_EDIT_MCU_TEST )->SetFont( &g_editFont );
	g_editFont.Detach();

	// ����Ʈ �ڽ� ���� �ο��ϱ�
	CRect r;
    // ���� ������ �ο��ϰ��� �ϴ� ����Ʈ ��Ʈ���� �⺻ ���������� �о�ɴϴ�.
    m_cedit_mcu_test.GetRect(r); 
    // ��/�� ������ �ο��մϴ�.
    //r.left += 5;
    //r.right -= 5;
    // ��/�� ������ �ο��մϴ�.
    r.top += 50;
    r.bottom -= 0;
	// ����� ������ �ش� ����Ʈ ��Ʈ�ѿ� �����մϴ�.
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


// McuDlg �޽��� ó�����Դϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL Connect_MCU = FALSE;
	HKEY hKey;
	CString lpSubKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM�� �ø�����Ʈ ��ȣ���� ��ϵǾ� ����.  
	RegOpenKey(HKEY_LOCAL_MACHINE, lpSubKey, &hKey);
	TCHAR szData[100], szName[100];
	DWORD index = 0, dwSize=100, dwSize2 = 100, dwType = REG_SZ;
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
		//Port ���� ���� + �����Ͱ� Jtp �������� �������� Ȯ��
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

		// �˻� ȭ��
		pDlg->McuTestBG_Color = GREEN;
		pDlg->McuTestText_Color = BLACK;
		pDlg->m_edit_mcu_test = CSTRING_TEST_PASS;
		pDlg->UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("FAIL"));

		// �˻� ȭ��
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;

	// ��Ʈ�� ���µ� �����ߴٸ�
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

		// ������ ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;

	// ��Ʈ�� ���µ� �����ߴٸ�
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

		// ������ ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 chkSum = 0;
	int sndSize = 0, idx = 0;
	U08 *pTxData;
	OPX_STATIC_INFO *opx_static_info;

	// HIGHT ��ȣȭ
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
	
	// ��Ʈ�� ���µ� �����ߴٸ�
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

		// ������ ����
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
	BYTE aByte = 0x00; //�����͸� ������ ����
	int i = 0, iSize = 0;
	SYSTEMTIME st_pre, st_cur;
	WORD st_diff = 0;
	VERSION_INFO *pVersion;
	MCU_STATIC_INFO *mcu_static_info;
	BYTE *DataBuff;

	// ��Ʈ�� ���� ���� ��쿡�� ��Ʈ�� ���� ����
	if ( m_ComuPort.m_bConnected == FALSE )
	{
		if ( m_ComuPort.OpenPort(strPortName, pDisplayUnitTesterDlg->byIndexBaud(iBaudRate), pDisplayUnitTesterDlg->byIndexData(iDataBit), pDisplayUnitTesterDlg->byIndexStop(iStopBit), pDisplayUnitTesterDlg->byIndexParity(iParity)) ==TRUE)
		{
			// ��Ʈ�� ���µ� �����ߴٸ�
			if ( m_ComuPort.m_bConnected == TRUE )
			{
				GetSystemTime(&st_pre);
				while( Result != TRUE )
				{
					GetSystemTime(&st_cur);
					st_diff = (st_cur.wSecond >= st_pre.wSecond)? (st_cur.wSecond - st_pre.wSecond) : (60 + st_pre.wSecond - st_cur.wSecond);
					// 3�� �� �˻�
					if ( st_diff >= 3 )
					{
						break;
					}
					
					if ( iSize == 0 )
					{
						// ���� Ȯ�� Ŀ�ǵ带 �۽�
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

					iSize =  (m_ComuPort.m_QueueRead).GetSize(); //��Ʈ�� ���� ������ ����
												 //SetCommState�� ������ ���� ������ ���� 8���� ����
					for ( i = 0; i < iSize; i++ ) //���� ���� ��ŭ �����͸� �о� �� JTP ��������
					{
						(m_ComuPort.m_QueueRead).GetByte(&aByte);//ť���� ������ �Ѱ��� �о��
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
	// �˻� ȭ��
	McuTestStatus_Testing();

	//--> MCU Test ȭ�� ������ ����.
	DWORD dwThreadID; 
	m_hThread_McuTest = NULL;
	m_hThread_McuTest = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_McuTest_Display, this, 0, &dwThreadID);

}

 
HBRUSH McuDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	 switch(nCtlColor)
    {
        case CTLCOLOR_EDIT:
        {

        }
        break;
        // �б� ���� ��Ʈ��
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
