
// R7EOLvs2010Dlg.cpp : ���� ����
//
#include "stdafx.h"
#include "R7EOLvs2010.h"
#include "R7EOLvs2010Dlg.h"
#include "afxdialogex.h"

#include "y_Color.h"
#include "y_EditBox.h"
#include "y_Debugging.h"
#include "y_LogManage.h"
#include "y_ExpressImgDlg.h"
#include "y_wm_user.h"
#include "y_ScrewCounterMgt.h"
#include "EOL_TEST_R7.h"

#include "IoBoardDlg.h"
#include "SettingDlg.h"
#include "ScrewDlg.h"
#include "BarCodeDlg.h"
#include "y_LanguagePack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_CUR_TIME 1000

CR7EOLvs2010Dlg     *pMainDlg  = NULL;	// main dialog
////////////////////////////////////////////////////////////
// EOL TEST PRODUCT TYPES
CEOL_R7 *EOL_TEST_R7;

// Serial Comm �ڵ鷯 - WM_COMM_READ �޼����� �ޱ� ���� �ʿ�!
HWND hCommWnd;

// CR7EOLvs2010Dlg ��ȭ ����

CR7EOLvs2010Dlg::CR7EOLvs2010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CR7EOLvs2010Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CR7EOLvs2010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOTICE, m_edit_notice);
	DDX_Control(pDX, IDC_BUTTON_START, m_cbutton_start);
	DDX_Control(pDX, IDC_EDIT_DRAW_NUM, m_edit_draw_num);
	DDX_Control(pDX, IDC_EDIT_TEST_TIME, m_edit_test_time);
	DDX_Control(pDX, IDC_LIST_TEST_PROCESS, m_list_test_process);
	DDX_Control(pDX, IDC_COMBO_TESTER, m_combo_tester);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_NAME, m_edit_product_name);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_LINE, m_edit_product_line);
	DDX_Control(pDX, IDC_EDIT_NOTICE2, m_edit_notice2);
	DDX_Control(pDX, IDC_EDIT_PASS_NUM, m_edit_pass_num);
	DDX_Control(pDX, IDC_EDIT_TOTAL_NUM, m_edit_total_num);
	DDX_Control(pDX, IDC_EDIT_PASS_PERCENT, m_edit_pass_percent);
	DDX_Control(pDX, IDC_EDIT_FAIL_NUM, m_edit_fail_num);
	DDX_Control(pDX, IDC_EDIT_IN_SPEED, m_edit_in_speed);
	DDX_Control(pDX, IDC_EDIT_IN_WINK_L, m_edit_in_wink_l);
	DDX_Control(pDX, IDC_EDIT_IN_WINK_R, m_edit_in_wink_r);
	DDX_Control(pDX, IDC_EDIT_OUT_LDW_DETECT_L, m_edit_out_ldw_detetc_l);
	DDX_Control(pDX, IDC_EDIT_OUT_LDW_DETECT_R, m_edit_out_m_ldw_detect_r);
	DDX_Control(pDX, IDC_EDIT_OUT_LDW_WARN_L, m_edit_out_ldw_warn_l);
	DDX_Control(pDX, IDC_EDIT_OUT_LDW_WARN_R, m_edit_out_ldw_warn_r);
	DDX_Control(pDX, IDC_EDIT_OUT_HMW, m_edit_out_hmw);
	DDX_Control(pDX, IDC_EDIT_OUT_FCW, m_edit_out_fcw);
	DDX_Control(pDX, IDOK, m_button_close);
	DDX_Control(pDX, IDC_EDIT_TOTAL_TEST, m_edit_total_test);
}

BEGIN_MESSAGE_MAP(CR7EOLvs2010Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CR7EOLvs2010Dlg::OnBnClickedButtonStart)
	ON_MESSAGE(_WM_COMM_READ , OnCommunication) // Serial Comm Function <-Msg
	ON_MESSAGE(_WM_MAIN_DLG_INIT , MsgOnInitDialog) // Dialog Init <-Msg
	ON_MESSAGE(_WM_MAIN_DLG_END , R7_EOL_Status_Ready) // Main Dialog End <-Msg
	ON_BN_CLICKED(IDC_BUTTON_VIEW_AVI, &CR7EOLvs2010Dlg::OnBnClickedButtonViewAvi)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CR7EOLvs2010Dlg::OnBnClickedButtonDraw)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON_IO_BD, &CR7EOLvs2010Dlg::OnBnClickedButtonIoBd)
	ON_BN_CLICKED(IDC_BUTTON_SCREW, &CR7EOLvs2010Dlg::OnBnClickedButtonScrew)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_TEST_PROCESS, OnCustomdrawList)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CR7EOLvs2010Dlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_BARCODE, &CR7EOLvs2010Dlg::OnBnClickedButtonBarcode)
END_MESSAGE_MAP()


// CR7EOLvs2010Dlg �޽��� ó����

BOOL CR7EOLvs2010Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	dfp();	// ����� ������ �ð� ǥ��
	UpdateData(TRUE);

	// Main Dialog
	pMainDlg = this;

	// Setting ���Ͽ��� ���� �� �ҷ�����
	CString strTester[TESTER_MAX];
	CString strNotice, strNotice2;
	int nTesterIdx, nTesterNum;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);


	// ��� ����
	if (pEolSetting->ReadSetting(SET_LANGUAGE) == _T("KOREAN"))
	{
		m_language = L_KOREAN;
	}
	else if (pEolSetting->ReadSetting(SET_LANGUAGE) == _T("CHINESE"))
	{
		m_language = L_CHINESE;
	}
	else if (pEolSetting->ReadSetting(SET_LANGUAGE) == _T("ENGLISH"))
	{
		m_language = L_ENGLISH;
	}
	// Set Language ( Korean, Chinese, English )
	EOLLanguage.SET_LANGUAE_PACK(m_language);


	strProductLine	= pEolSetting->ReadSetting(TESTER_LINE);
	strTesterNum	= pEolSetting->ReadSetting(TESTER_NUM);
	strTester[0]	= pEolSetting->ReadSetting(TESTER_1);
	strTester[1]	= pEolSetting->ReadSetting(TESTER_2);
	strTester[2]	= pEolSetting->ReadSetting(TESTER_3);
	strTester[3]	= pEolSetting->ReadSetting(TESTER_4);
	strTester[4]	= pEolSetting->ReadSetting(TESTER_5);
	strTester[5]	= pEolSetting->ReadSetting(TESTER_6);
	strTester[6]	= pEolSetting->ReadSetting(TESTER_7);
	strTester[7]	= pEolSetting->ReadSetting(TESTER_8);
	strTester[8]	= pEolSetting->ReadSetting(TESTER_9);
	strTester[9]	= pEolSetting->ReadSetting(TESTER_10);
	strTester[10]	= pEolSetting->ReadSetting(TESTER_11);
	strTester[11]	= pEolSetting->ReadSetting(TESTER_12);
	strTester[12]	= pEolSetting->ReadSetting(TESTER_13);
	strTester[13]	= pEolSetting->ReadSetting(TESTER_14);
	strProductName	= pEolSetting->ReadSetting(PROC_PRODUCT_TYPE);
	strTotalTest    = pEolSetting->ReadSetting(TOTAL_TEST_NUM);
	if ( strTotalTest == "" )	strTotalTest = _T("0");
	// �α� ���� ��� ����
	strLogPath		= pEolSetting->ReadSetting(LOG_FILE_PATH);

	// �˻��� �׸� ����
	strMcuVer		= pEolSetting->ReadSetting(PROC_MCU_VER);
	strSwVer		= pEolSetting->ReadSetting(PROC_SW_VER);

	bEnStep_McuVer     = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_MCU_VER));
	bEnStep_SwVer	   = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_SW_VER));
	bEnStep_SerialNum  = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_SERIAL_NUM));
	bEnStep_IoBoard    = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_IO_BOARD));
	bEnStep_Screw	   = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_SCREW));
	bEnStep_Bar1	   = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_BARCODE1));
	bEnStep_Bar2	   = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_BARCODE2));
	bEnStep_Accleration= _ttoi(pEolSetting->ReadSetting(STEP_CHECK_ACCLERATION));
	bEnStep_SpeedPulse = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_SPEED_PULSE));
	bEnStep_DTC_Clear  = _ttoi(pEolSetting->ReadSetting(STEP_CHECK_DTC_CLEAR));

	bEnStep_LDW_Speed = _ttoi(pEolSetting->ReadSetting(STEP_LDW_SPEED));
	bEnStep_FCW_Speed = _ttoi(pEolSetting->ReadSetting(STEP_FCW_SPEED));
	bEnStep_LDW_Detect = _ttoi(pEolSetting->ReadSetting(STEP_LDW_DETECT));
	bEnStep_LDW_Warn_L = _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_L));
	bEnStep_LDW_Warn_R = _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_R));
	bEnStep_FCW_Warn   = _ttoi(pEolSetting->ReadSetting(STEP_FCW_WARN));
	bEnStep_FCW_Warn2   = _ttoi(pEolSetting->ReadSetting(STEP_FCW_WARN2));
	bEnStep_FCW_Warn3   = _ttoi(pEolSetting->ReadSetting(STEP_FCW_WARN3));
	bEnStep_FCDA_Warn  = _ttoi(pEolSetting->ReadSetting(STEP_FCDA_WARN));
	bEnStep_LDW_WarnL_WinkL		= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_L_WINK_L));
	bEnStep_LDW_WarnL_WinkR		= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_L_WINK_R));
	bEnStep_LDW_WarnL_WinkLR	= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_L_WINK_LR));
	bEnStep_LDW_WarnR_WinkL		= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_R_WINK_L));
	bEnStep_LDW_WarnR_WinkR		= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_R_WINK_R));
	bEnStep_LDW_WarnR_WinkLR	= _ttoi(pEolSetting->ReadSetting(STEP_LDW_WARN_R_WINK_LR));

	m_nVehicleLdwSpd = _ttoi(pEolSetting->ReadSetting(PROC_LDW_SPD));
	m_nVehicleFcwSpd = _ttoi(pEolSetting->ReadSetting(PROC_FCW_SPD));

	m_nAlarmDelay = _ttoi(pEolSetting->ReadSetting(STEP_ADAS_ALARM_DELAY));

	// ����Ʈ �ڽ� ���� �� �ʱ�ȭ
	LOGFONT oLogFont;
    GetFont()->GetLogFont(&oLogFont);
    oLogFont.lfHeight = 50;

	// Notice
	m_edit_notice.SetLogFont(&oLogFont);
    m_edit_notice.SetBgColor(SOFT_BLUE);					// ��׶��� ��
    m_edit_notice.SetTextColor(GREY_ROAD);					// ���� ��
    m_edit_notice.SetTextFormat(DT_CENTER | DT_VCENTER);	// �¿�/���� ����
	strNotice = _T("PLK Technologies\r\nLDWS ") + strProductName + EOLLanguage.LP_LAST_TEST;
	m_edit_notice.SetTextString(strNotice);					// ����
	m_edit_notice.PostMessageW(_WM_THREAD_UPDATE);
	// Notice2
	m_edit_notice2.SetLogFont(&oLogFont);
    m_edit_notice2.SetBgColor(SOFT_BLUE);					// ��׶��� ��
    m_edit_notice2.SetTextColor(GREY_ROAD);					// ���� ��
    m_edit_notice2.SetTextFormat(DT_CENTER | DT_VCENTER);	// �¿�/���� ����
	strNotice2 = strProductName;
	m_edit_notice2.SetTextString(strNotice2);
	m_edit_notice2.PostMessageW(_WM_THREAD_UPDATE);

	m_edit_draw_num.SetText(SOFT_BLUE, GREY_ROAD, _T(""), UPDATE_ON);				// �׸��� ��ȣ ǥ��
	m_edit_product_line.SetText(SOFT_BLUE, GREY_ROAD, strProductLine, UPDATE_ON);	// ���� ���� ǥ��
	m_edit_product_name.SetText(SOFT_BLUE, GREY_ROAD, strProductName, UPDATE_ON);	// ��ǰ�� ǥ��

	m_edit_pass_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// ��ǰ���� ǥ��
	m_edit_fail_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// �ҷ����� ǥ��
	m_edit_total_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// ��ü���� ǥ��
	m_edit_pass_percent.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// ��ǰ���� ǥ��
	m_edit_total_test.SetText(SOFT_BLUE, GREY_ROAD, strTotalTest, UPDATE_ON);	// ��ü �׽�Ʈ ���� ǥ��

	m_edit_in_speed.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// �Է¼ӵ� ǥ��
	m_edit_in_wink_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// �Է¹������õ� ǥ��
	m_edit_in_wink_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// �Է¹������õ� ǥ��
	m_edit_out_ldw_detetc_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����ν� ǥ��
	m_edit_out_m_ldw_detect_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);	// �����ν� ǥ��
	m_edit_out_ldw_warn_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����溸 ǥ��
	m_edit_out_ldw_warn_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����溸 ǥ��
	m_edit_out_hmw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// HMW�溸 ǥ��
	m_edit_out_fcw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// FCW�溸 ǥ��

	// ����Ʈ ��Ʈ�� ���� �� �ʱ�ȭ
	// ����Ʈ ��Ʈ�� ���� ���� ���� ����
	m_list_test_process.SetBkColor(SOFT_BLUE);
	m_list_test_process.SetTextBkColor(SOFT_BLUE);
    m_list_test_process.SetTextColor(GREY_ROAD);

	// ����Ʈ ��� ������ �����
    m_list_test_process.DeleteAllItems();
    // ����Ʈ ��� �÷� �����
    while( m_list_test_process.GetHeaderCtrl()->GetItemCount() > 0 )
    {
        m_list_test_process.DeleteColumn(0);
    }
	// ����Ʈ ��Ÿ�� ����
	//LVS_EX_FULLROWSELECT  : �������� ������ �� �� �� ��ü�� ������Ų��.
	//LVS_EX_GRIDLINES      : �� �����ۿ� ��輱�� �׷��ش�.
	//LVS_EX_CHECKBOXES     : �� �����ۿ� Check Box�� ǥ���� �ش�.
	//LVS_EX_HEADERDRAGDROP : �÷� ����� �巡�� �����ν� �÷��� ������ �ٲ� �� �ְ� ���ش�.
	m_list_test_process.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// ����Ʈ Ÿ��Ʋ ����
	m_list_test_process.InsertColumn(0, EOLLanguage.LP_TEST_INDEX, LVCFMT_CENTER, 200, -1);
	m_list_test_process.InsertColumn(1, EOLLanguage.LP_TARGET, LVCFMT_CENTER, 250, -1);
	m_list_test_process.InsertColumn(2, EOLLanguage.LP_CHECK, LVCFMT_CENTER, 250, -1);
	m_list_test_process.InsertColumn(3, EOLLanguage.LP_RESULT, LVCFMT_CENTER, 100, -1);

	// �޺� �ڽ� ���� �� �ʱ�ȭ
	// �׽��� �׸�
	nTesterNum = _ttoi(strTesterNum);
	if ( (nTesterNum < 1) || (nTesterNum > TESTER_MAX) )	nTesterNum = 1;

	m_combo_tester.ResetContent();
	for ( nTesterIdx = 0; nTesterIdx < nTesterNum; nTesterIdx++ )
	{
		m_combo_tester.AddString(strTester[nTesterIdx]);
	}
	m_combo_tester.SetCurSel(0);

	// �α� ���� ����
	CTime   oTime;
	CString strTime;
	CString strPathEolLog;

	oTime = CTime::GetCurrentTime();
	strTime.Format(_T("%04d%02d%02d"), oTime.GetYear(), oTime.GetMonth(), oTime.GetDay());

	strPathEolLog = _T("EOL_") + strProductName + _T("_") + strTime + _T(".log");
	pEolSetting->SetFilePath(strPathEolLog);

	// ��޸��� ���̾�α� �ʱ�ȭ
	pImgDlg = NULL;

	// Serial Comm �ڵ鷯 - WM_COMM_READ �޼����� �ޱ� ���� �ʿ�!
	hCommWnd = m_hWnd;

	// �׽�Ʈ ���� �ð� ǥ��
	SetTimer(TIMER_CUR_TIME, 1000, NULL);

	UpdateData(FALSE);

	// Setting ���� �ݱ�
	delete pEolSetting;
    pEolSetting = NULL;


	// ���̾�α� ��� ����
	m_cbutton_start.SetWindowTextW(EOLLanguage.LP_START);
	m_button_close.SetWindowTextW(EOLLanguage.LP_CLOSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

long CR7EOLvs2010Dlg::MsgOnInitDialog(WPARAM wParam, LPARAM lParam)
{
	OnInitDialog();

	return 1;
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CR7EOLvs2010Dlg::OnPaint()
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
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CR7EOLvs2010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CR7EOLvs2010Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CTime   oTime;
	CString strTime;

	switch(nIDEvent)
	{
	// Ÿ�̸Ӹ� �̿��Ͽ� ������ ���� ���ϴ� ������ ��ü �̹����� ǥ���Ѵ�.
	case TIMER_CUR_TIME :
		oTime = CTime::GetCurrentTime();
		strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), oTime.GetYear(), oTime.GetMonth(), oTime.GetDay(), oTime.GetHour(), oTime.GetMinute(), oTime.GetSecond());
		m_edit_test_time.SetText(SOFT_BLUE, GREY_ROAD, strTime, UPDATE_ON);	// ���� ���� ǥ��
		break;
	default :

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

long CR7EOLvs2010Dlg::R7_EOL_Status_Ready(WPARAM wParam, LPARAM lParam)
{
	// Notice Edit Box ����
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
    GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BARCODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_IO_BD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SCREW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_AMMETER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DRAW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_VIEW_AVI)->EnableWindow(TRUE);

    m_cbutton_start.SetWindowTextW(EOLLanguage.LP_START);

	return 1;
}
void CR7EOLvs2010Dlg::R7_EOL_Status_Running(void)
{
	// Notice Edit Box ����
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
    GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BARCODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_IO_BD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCREW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AMMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DRAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_VIEW_AVI)->EnableWindow(FALSE);

	m_cbutton_start.SetWindowTextW(EOLLanguage.LP_PAUSE);
}

long CR7EOLvs2010Dlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);//�޴� ������ Ÿ���� �˱� ����
	CString str = _T("");
	CString result;
	BYTE aByte; //�����͸� ������ ����
	int iSize =  (m_ComuPort.m_QueueRead).GetSize(); //��Ʈ�� ���� ������ ����
												 //SetCommState�� ������ ���� ������ ���� 8���� ����
	for(int i  = 0 ; i < iSize; i++)//���� ���� ��ŭ �����͸� �о� �� ȭ�鿡 ������
	{
		(m_ComuPort.m_QueueRead).GetByte(&aByte);//ť���� ������ �Ѱ��� �о��
		dp("%2X ",aByte);
	}

	return 1;
}

void CR7EOLvs2010Dlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);//�޴� ������ Ÿ���� �˱� ����
	CString strBtnText;
	m_cbutton_start.GetWindowTextW(strBtnText);

	if ( strBtnText == EOLLanguage.LP_START )
	{
		dp("***************************** EOL PROGRAM START *****************************\n");
		R7_EOL_Status_Running();

		if ( pImgDlg != NULL)
		{
			pImgDlg->DestroyWindow( );
			pImgDlg = NULL;
		}
		pImgDlg = new CExpressImgDlg();
		pImgDlg->Create(IDD_EXPRESS_IMG_DIALOG);
		pImgDlg->ShowWindow(SW_SHOW);

		// ADAS �׸� ���� �� ����
		CLogManage	*pEolSetting;
		pEolSetting = new CLogManage;
		pEolSetting->SetFilePath(SETTING_FILE_PATH);
		CString strVanish, strLandWidth, strLaneMove, strLaneLColor, strLaneRColor;
		strVanish		= pEolSetting->ReadSetting(DRAW_VANISHY);
		strLandWidth	= pEolSetting->ReadSetting(DRAW_WIDTH);
		strLaneMove		= pEolSetting->ReadSetting(DRAW_MOVEMENT);
		strLaneLColor	= pEolSetting->ReadSetting(DRAW_LANE_L_COLOR);
		strLaneRColor	= pEolSetting->ReadSetting(DRAW_LANE_R_COLOR);
		pImgDlg->ImgSet_Vanish(_ttoi(strVanish));
		pImgDlg->ImgSet_LandWidth(_ttoi(strLandWidth));
		pImgDlg->ImgSet_LaneMovemnet(_ttoi(strLaneMove));
		pImgDlg->ImgSet_LaneLColor(CStringToRGB(strLaneLColor));
		pImgDlg->ImgSet_LaneRColor(CStringToRGB(strLaneRColor));
		delete pEolSetting;
		pEolSetting = NULL;

		// Find() R7 ���ڿ��� ���ԵǾ� �ִ��� Ȯ��, ������ -1�� return
		if ( m_edit_product_name.m_strMsg.Find(_T("R7")) != -1)
		{
			EOL_TEST_R7 = new CEOL_R7;
			EOL_TEST_R7->START_EOL_TEST();
		}
		else
		{

		}
	}
	//else if ( strBtnText == EOLLanguage.LP_PAUSE )
	else
	{
		// ��ü �׽�Ʈ ���� �����ϱ�
		CLogManage	*pEolSetting;
		pEolSetting = new CLogManage;
		pEolSetting->SetFilePath(SETTING_FILE_PATH);

		pEolSetting->WriteSetting(TOTAL_TEST_NUM , m_edit_total_test.m_strMsg);
		delete pEolSetting;
		pEolSetting = NULL;


		if ( m_edit_product_name.m_strMsg.Find(_T("R7")) != -1 )
		{
			EOL_TEST_R7->END_EOL_TEST();
		}
		else
		{
			pMainDlg->PostMessageW(_WM_MAIN_DLG_END);
		}

		if ( pImgDlg != NULL)
		{
			pImgDlg->DestroyWindow( );
			pImgDlg = NULL;
		}

		dp("***************************** EOL PROGRAM END *****************************\n");
	}
}

void CR7EOLvs2010Dlg::OnBnClickedButtonViewAvi()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

COLORREF CR7EOLvs2010Dlg::CStringToRGB(CString strColor)
{
	COLORREF rgb;

	if ( strColor == _T("YELLOW") )
	{
		rgb = YELLOW;
	}
	else if ( strColor == _T("WHITE") )
	{
		rgb = WHITE;
	}
	else if ( strColor == _T("BLACK") )
	{
		rgb = BLACK;
	}
	else if ( strColor == _T("BLUE") )
	{
		rgb = BLUE;
	}
	else if ( strColor == _T("RED") )
	{
		rgb = RED;
	}
	else if ( strColor == _T("GREEN") )
	{
		rgb = GREEN;
	}
	else if ( strColor == _T("GRAY") )
	{
		rgb = GRAY;
	}
	else
	{
		rgb = WHITE;
	}


	return rgb;
}


void CR7EOLvs2010Dlg::OnBnClickedButtonDraw()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CClientDC dc( this );
	CString strImgDrawNum;
	int		nImgDrawNum;

	// �׸� ���� �� �ҷ�����
	CString strVanish, strLandWidth, strLaneMove, strLaneLColor, strLaneRColor;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strVanish		= pEolSetting->ReadSetting(DRAW_VANISHY);
	strLandWidth	= pEolSetting->ReadSetting(DRAW_WIDTH);
	strLaneMove		= pEolSetting->ReadSetting(DRAW_MOVEMENT);
	strLaneLColor	= pEolSetting->ReadSetting(DRAW_LANE_L_COLOR);
	strLaneRColor	= pEolSetting->ReadSetting(DRAW_LANE_R_COLOR);
	delete pEolSetting;
    pEolSetting = NULL;

	// �׸� ��ȣ ������
	UpdateData(TRUE);
	m_edit_draw_num.GetWindowTextW(strImgDrawNum);
	m_edit_draw_num.SetTextString(strImgDrawNum);

	if ( strImgDrawNum == _T("") )
	{
		if ( pImgDlg != NULL )
		{
			pImgDlg->DestroyWindow( );
			pImgDlg = NULL;
		}
	}
	else
	{
		// ȭ�� ����
		if ( pImgDlg == NULL)
		{
			pImgDlg = new CExpressImgDlg();
			// �׸� ǥ��
			pImgDlg->Create(IDD_EXPRESS_IMG_DIALOG);
			pImgDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			pImgDlg->ImgSet_Vanish(_ttoi(strVanish));
			pImgDlg->ImgSet_LandWidth(_ttoi(strLandWidth));
			pImgDlg->ImgSet_LaneMovemnet(_ttoi(strLaneMove));

			pImgDlg->ImgSet_LaneLColor(CStringToRGB(strLaneLColor));
			pImgDlg->ImgSet_LaneRColor(CStringToRGB(strLaneRColor));

			// �׸� ��ȣ ������
			nImgDrawNum = _ttoi(strImgDrawNum);
			if		( nImgDrawNum == pImgDlg->CALIBRATION)		pImgDlg->ImgSet(pImgDlg->CALIBRATION);
			else if ( nImgDrawNum == pImgDlg->LDW_DETECT )		pImgDlg->ImgSet(pImgDlg->LDW_DETECT);
			else if ( nImgDrawNum == pImgDlg->LDW_WARN_L )		pImgDlg->ImgSet(pImgDlg->LDW_WARN_L);
			else if ( nImgDrawNum == pImgDlg->LDW_WARN_R )		pImgDlg->ImgSet(pImgDlg->LDW_WARN_R);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_DETECT)	pImgDlg->ImgSet(pImgDlg->FCW_CAR_DETECT);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_WARN)		pImgDlg->ImgSet(pImgDlg->FCW_CAR_WARN);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_DETECT)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_DETECT);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_WARN)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_WARN);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_DETECT2)	pImgDlg->ImgSet(pImgDlg->FCW_CAR_DETECT2);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_WARN2)		pImgDlg->ImgSet(pImgDlg->FCW_CAR_WARN2);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_DETECT2)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_DETECT2);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_WARN2)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_WARN2);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_DETECT3)	pImgDlg->ImgSet(pImgDlg->FCW_CAR_DETECT3);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_WARN3)		pImgDlg->ImgSet(pImgDlg->FCW_CAR_WARN3);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_DETECT3)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_DETECT3);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_WARN3)	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_WARN3);
			else if ( nImgDrawNum == pImgDlg->LDW_DETECT_NIGHT )		pImgDlg->ImgSet(pImgDlg->LDW_DETECT_NIGHT);
			else if ( nImgDrawNum == pImgDlg->LDW_WARN_L_NIGHT )		pImgDlg->ImgSet(pImgDlg->LDW_WARN_L_NIGHT);
			else if ( nImgDrawNum == pImgDlg->LDW_WARN_R_NIGHT )		pImgDlg->ImgSet(pImgDlg->LDW_WARN_R_NIGHT);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_DETECT_NIGHT )	pImgDlg->ImgSet(pImgDlg->FCW_CAR_DETECT_NIGHT);
			else if ( nImgDrawNum == pImgDlg->FCW_CAR_WARN_NIGHT )		pImgDlg->ImgSet(pImgDlg->FCW_CAR_WARN_NIGHT);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_DETECT_NIGHT )	pImgDlg->ImgSet(pImgDlg->FCDA_CAR_DETECT_NIGHT);
			else if ( nImgDrawNum == pImgDlg->FCDA_CAR_WARN_NIGHT )		pImgDlg->ImgSet(pImgDlg->FCDA_CAR_WARN_NIGHT);
		}
	}
}


void CR7EOLvs2010Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.

    lpMMI->ptMinTrackSize = CPoint(1280, 800);
    lpMMI->ptMaxTrackSize = CPoint(1280, 800);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CR7EOLvs2010Dlg::OnBnClickedButtonIoBd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	IoBoardDlg dlg;
	dlg.DoModal();
}

void CR7EOLvs2010Dlg::OnBnClickedButtonScrew()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ScrewDlg dlg;
	dlg.DoModal();
}

BOOL CR7EOLvs2010Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect( rect, SOFT_BLUE );

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}


// ����Ʈ ��Ʈ�� �ະ ��׶���/��Ʈ ���� ����
void CR7EOLvs2010Dlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

    // Take the default processing unless we set this to something else below.
    *pResult = CDRF_DODEFAULT;

    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.

    if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
    }
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here.
		// We'll alternate between m_back0 (pale gray-green) and m_back1 (pure white)


		*pResult = CDRF_NOTIFYPOSTPAINT;	// return this instead of CDRF_DODEFAULT

	}
	else if ( CDDS_ITEMPOSTPAINT == pLVCD->nmcd.dwDrawStage ) // control is done drawing
    {
        // If this item is selected, re-draw the icon in its normal
        // color (not blended with the highlight color)

		// see if we have an image list.  There's nothing to do if we don't

		*pResult = CDRF_SKIPDEFAULT;
	}
}

HBRUSH CR7EOLvs2010Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch(nCtlColor)
    {
		// ����Ʈ �ڽ�
        case CTLCOLOR_EDIT:
        {
            pDC->SetTextColor(GREY_ROAD);
            pDC->SetBkColor(SOFT_BLUE);
        }
        // �б� ���� ��Ʈ��
        case CTLCOLOR_STATIC:
        {
            pDC->SetTextColor(GREY_ROAD);
            pDC->SetBkColor(SOFT_BLUE);
        }
        break;
    }
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CR7EOLvs2010Dlg::OnBnClickedButtonSetting()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SettingDlg dlg;
	dlg.DoModal();
}


void CR7EOLvs2010Dlg::OnBnClickedButtonBarcode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BarCodeDlg dlg;
	dlg.DoModal();
}
