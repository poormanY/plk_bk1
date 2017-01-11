// SettingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "R7EOLvs2010.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "R7EOLvs2010Dlg.h"
#include "y_Color.h"
#include "y_LanguagePack.h"

// SettingDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingDlg::IDD, pParent)
	, m_check_ldw_detect(FALSE)
	, m_check_ldw_warn_l(FALSE)
	, m_check_ldw_warn_r(FALSE)
	, m_check_fcw_warn(FALSE)
	, m_check_mcu_ver(FALSE)
	, m_check_sw_ver(FALSE)
	, m_check_serial_num(FALSE)
	, m_check_screw(FALSE)
	, m_check_bar1(FALSE)
	, m_check_bar2(FALSE)
	, m_check_accleration(FALSE)
	, m_check_speed_pulse(FALSE)
	, m_check_dtc_clear(FALSE)
	, m_check_io_board(FALSE)
	, m_check_ldw_warnL_winkL(FALSE)
	, m_check_ldw_warnL_winkR(FALSE)
	, m_check_ldw_warnL_winkLR(FALSE)
	, m_check_ldw_warnR_winkL(FALSE)
	, m_check_ldw_warnR_winkLR(FALSE)
	, m_check_fcda_warn(FALSE)
	, m_check_ldw_speed(FALSE)
	, m_check_fcw_speed(FALSE)
	, m_check_fcw_warn2(FALSE)
	, m_check_fcw_warn3(FALSE)
	, m_radio_language(0)
{

}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_G_COMPORT, m_static_g_comport);
	DDX_Control(pDX, IDC_EDIT_COM_IO, m_edit_com_io);
	DDX_Control(pDX, IDC_EDIT_COM_AM, m_edit_com_am);
	DDX_Control(pDX, IDC_EDIT_COM_SCREW, m_edit_com_screw);
	DDX_Control(pDX, IDC_EDIT_COM_BAR1, m_edit_com_bar1);
	DDX_Control(pDX, IDC_EDIT_COM_BAR2, m_edit_com_bar2);
	DDX_Control(pDX, IDC_EDIT_SET_FILE_PATH, m_edit_set_file_path);
	DDX_Control(pDX, IDC_STATIC_G_DRAW, m_static_g_draw);
	DDX_Control(pDX, IDC_EDIT_DRAW_VANISHY, m_edit_draw_vanishy);
	DDX_Control(pDX, IDC_EDIT_DRAW_WIDTH, m_edit_draw_width);
	DDX_Control(pDX, IDC_EDIT_DRAW_MOVE, m_edit_draw_move);
	DDX_Control(pDX, IDC_STATIC_G_TEST_PROCESS, m_static_g_test_process);
	DDX_Control(pDX, IDC_EDIT_PROC_PRODUCT_TYPE, m_edit_proc_product_type);
	DDX_Control(pDX, IDC_EDIT_PROC_SW_VER, m_edit_proc_sw_ver);
	DDX_Control(pDX, IDC_EDIT_PROC_SERIAL_NUM, m_edit_proc_serial_num);
	DDX_Control(pDX, IDC_EDIT_PROC_LDW_SPD, m_edit_proc_ldw_spd);
	DDX_Control(pDX, IDC_EDIT_PROC_FCW_SPD, m_edit_proc_fcw_spd);
	DDX_Control(pDX, IDC_EDIT_PROC_MCU_VER, m_edit_proc_mcu_ver);
	DDX_Control(pDX, IDC_STATIC_G_TESTER, m_static_g_tester);
	DDX_Control(pDX, IDC_STATIC_G_TEST_ADAS, m_static_g_test_adas);
	DDX_Control(pDX, IDC_EDIT_TESTER_NUM, m_edit_tester_num);
	DDX_Control(pDX, IDC_EDIT_TESTER1	, m_edit_tester1);
	DDX_Control(pDX, IDC_EDIT_TESTER2	, m_edit_tester2);
	DDX_Control(pDX, IDC_EDIT_TESTER3	, m_edit_tester3);
	DDX_Control(pDX, IDC_EDIT_TESTER4	, m_edit_tester4);
	DDX_Control(pDX, IDC_EDIT_TESTER5	, m_edit_tester5);
	DDX_Control(pDX, IDC_EDIT_TESTER6	, m_edit_tester6);
	DDX_Control(pDX, IDC_EDIT_TESTER7	, m_edit_tester7);
	DDX_Control(pDX, IDC_EDIT_TESTER8	, m_edit_tester8);
	DDX_Control(pDX, IDC_EDIT_TESTER9	, m_edit_tester9);
	DDX_Control(pDX, IDC_EDIT_TESTER10	, m_edit_tester10);
	DDX_Control(pDX, IDC_EDIT_TESTER11	, m_edit_tester11);
	DDX_Control(pDX, IDC_EDIT_TESTER12	, m_edit_tester12);
	DDX_Control(pDX, IDC_EDIT_TESTER13	, m_edit_tester13);
	DDX_Control(pDX, IDC_EDIT_TESTER14	, m_edit_tester14);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_LINE, m_edit_product_line);
	DDX_Check(pDX, IDC_CHECK_LDW_DETECT, m_check_ldw_detect);
	DDX_Check(pDX, IDC_CHECK_LDW_WARN_LEFT, m_check_ldw_warn_l);
	DDX_Check(pDX, IDC_CHECK_LDW_WARN_RIGHT, m_check_ldw_warn_r);
	DDX_Check(pDX, IDC_CHECK_FCW_WARN, m_check_fcw_warn);
	DDX_Check(pDX, IDC_CHECK_MCU_VER, m_check_mcu_ver);
	DDX_Check(pDX, IDC_CHECK_SW_VER, m_check_sw_ver);
	DDX_Check(pDX, IDC_CHECK_SERIAL_NUM, m_check_serial_num);
	DDX_Check(pDX, IDC_CHECK_SCREW, m_check_screw);
	DDX_Check(pDX, IDC_CHECK_BAR1, m_check_bar1);
	DDX_Check(pDX, IDC_CHECK_BAR2, m_check_bar2);
	DDX_Check(pDX, IDC_CHECK_ACCLERATION, m_check_accleration);
	DDX_Check(pDX, IDC_CHECK_SPEED_PULSE, m_check_speed_pulse);
	DDX_Check(pDX, IDC_CHECK_DTC_CLEAR, m_check_dtc_clear);
	DDX_Check(pDX, IDC_CHECK_IO_BOARD, m_check_io_board);
	DDX_Control(pDX, IDC_EDIT_LANE_L_COLOR, m_edit_lane_l_color);
	DDX_Control(pDX, IDC_EDIT_LANE_R_COLOR, m_edit_lane_r_color);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNL_WINKL, m_check_ldw_warnL_winkL);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNL_WINKR, m_check_ldw_warnL_winkR);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNL_WINKLR, m_check_ldw_warnL_winkLR);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNR_WINKL, m_check_ldw_warnR_winkL);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNR_WINKR, m_check_ldw_warnR_winkR);
	DDX_Check(pDX, IDC_CHECK_LDW_WARNR_WINKLR, m_check_ldw_warnR_winkLR);
	DDX_Check(pDX, IDC_CHECK_FCDA_WARN, m_check_fcda_warn);
	DDX_Check(pDX, IDC_CHECK_LDW_SPEED, m_check_ldw_speed);
	DDX_Check(pDX, IDC_CHECK_FCW_SPEED, m_check_fcw_speed);
	DDX_Control(pDX, IDC_STATIC_G_LOG_PATH, m_static_g_log_path);
	DDX_Control(pDX, IDC_EDIT_SET_LOG_PATH, m_edit_set_log_path);
	DDX_Control(pDX, IDC_EDIT_ADAS_ALARM_DELAY, m_edit_adas_alarm_delay);
	DDX_Check(pDX, IDC_CHECK_FCW_WARN2, m_check_fcw_warn2);
	DDX_Check(pDX, IDC_CHECK_FCW_WARN3, m_check_fcw_warn3);
	DDX_Radio(pDX, IDC_RADIO1, m_radio_language);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SettingDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &SettingDlg::OnBnClickedButtonLoad)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_SET_FILE_PATH, &SettingDlg::OnEnChangeEditSetFilePath)
	ON_EN_CHANGE(IDC_EDIT_COM_IO, &SettingDlg::OnEnChangeEditComIo)
	ON_EN_CHANGE(IDC_EDIT_COM_AM, &SettingDlg::OnEnChangeEditComAm)
	ON_EN_CHANGE(IDC_EDIT_COM_SCREW, &SettingDlg::OnEnChangeEditComScrew)
	ON_EN_CHANGE(IDC_EDIT_COM_BAR1, &SettingDlg::OnEnChangeEditComBar1)
	ON_EN_CHANGE(IDC_EDIT_COM_BAR2, &SettingDlg::OnEnChangeEditComBar2)
	ON_EN_CHANGE(IDC_EDIT_DRAW_VANISHY, &SettingDlg::OnEnChangeEditDrawVanishy)
	ON_EN_CHANGE(IDC_EDIT_DRAW_WIDTH, &SettingDlg::OnEnChangeEditDrawWidth)
	ON_EN_CHANGE(IDC_EDIT_DRAW_MOVE, &SettingDlg::OnEnChangeEditDrawMove)
	ON_BN_CLICKED(IDC_BUTTON_Default, &SettingDlg::OnBnClickedButtonDefault)
	ON_EN_CHANGE(IDC_EDIT_PROC_PRODUCT_TYPE, &SettingDlg::OnEnChangeEditProcProductType)
	ON_EN_CHANGE(IDC_EDIT_PROC_MCU_VER, &SettingDlg::OnEnChangeEditProcMcuVer)
	ON_EN_CHANGE(IDC_EDIT_PROC_SW_VER, &SettingDlg::OnEnChangeEditProcSwVer)
	ON_EN_CHANGE(IDC_EDIT_PROC_SERIAL_NUM, &SettingDlg::OnEnChangeEditProcSerialNum)
	ON_EN_CHANGE(IDC_EDIT_PROC_LDW_SPD, &SettingDlg::OnEnChangeEditProcLdwSpd)
	ON_EN_CHANGE(IDC_EDIT_PROC_FCW_SPD, &SettingDlg::OnEnChangeEditProcFcwSpd)
	ON_EN_CHANGE(IDC_EDIT_TESTER_NUM, &SettingDlg::OnEnChangeEditTesterNum)
	ON_EN_CHANGE(IDC_EDIT_TESTER1,	&SettingDlg::OnEnChangeEditTester1)
	ON_EN_CHANGE(IDC_EDIT_TESTER2,	&SettingDlg::OnEnChangeEditTester2)
	ON_EN_CHANGE(IDC_EDIT_TESTER3,	&SettingDlg::OnEnChangeEditTester3)
	ON_EN_CHANGE(IDC_EDIT_TESTER4,	&SettingDlg::OnEnChangeEditTester4)
	ON_EN_CHANGE(IDC_EDIT_TESTER5,	&SettingDlg::OnEnChangeEditTester5)
	ON_EN_CHANGE(IDC_EDIT_TESTER6,	&SettingDlg::OnEnChangeEditTester6)
	ON_EN_CHANGE(IDC_EDIT_TESTER7,	&SettingDlg::OnEnChangeEditTester7)
	ON_EN_CHANGE(IDC_EDIT_TESTER8,	&SettingDlg::OnEnChangeEditTester8)
	ON_EN_CHANGE(IDC_EDIT_TESTER9,	&SettingDlg::OnEnChangeEditTester9)
	ON_EN_CHANGE(IDC_EDIT_TESTER10,	&SettingDlg::OnEnChangeEditTester10)
	ON_EN_CHANGE(IDC_EDIT_TESTER11,	&SettingDlg::OnEnChangeEditTester11)
	ON_EN_CHANGE(IDC_EDIT_TESTER12,	&SettingDlg::OnEnChangeEditTester12)
	ON_EN_CHANGE(IDC_EDIT_TESTER13,	&SettingDlg::OnEnChangeEditTester13)
	ON_EN_CHANGE(IDC_EDIT_TESTER14,	&SettingDlg::OnEnChangeEditTester14)
	ON_BN_CLICKED(IDOK, &SettingDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_PRODUCT_LINE, &SettingDlg::OnEnChangeEditProductLine)
	ON_EN_CHANGE(IDC_EDIT_LANE_L_COLOR, &SettingDlg::OnEnChangeEditLaneLColor)
	ON_EN_CHANGE(IDC_EDIT_LANE_R_COLOR, &SettingDlg::OnEnChangeEditLaneRColor)
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_EDIT_ADAS_ALARM_DELAY, &SettingDlg::OnEnChangeEditAdasAlarmDelay)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, OnBnClickedRadio)
END_MESSAGE_MAP()


// SettingDlg �޽��� ó�����Դϴ�.


BOOL SettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	// ����/�ҷ����� ���� ���
	m_edit_set_file_path.SetText(WHITE, RED, SETTING_FILE_PATH, UPDATE_ON);
	m_edit_set_file_path.SetWindowTextW(m_edit_set_file_path.m_strMsg);

	// ��ü Static Text - OnCtlColor
	m_static_g_comport.SetText(WHITE, RED, _T("Comport Setting"), UPDATE_ON);
	m_static_g_draw.SetText(WHITE, RED, _T("Draw Setting"), UPDATE_ON);
	m_static_g_tester.SetText(WHITE, RED, _T("Tester Setting"), UPDATE_ON);
	m_static_g_test_process.SetText(WHITE, RED, _T("Process Setting"), UPDATE_ON);
	m_static_g_test_adas.SetText(WHITE, RED, _T("ADAS Setting"), UPDATE_ON);

	// ����Ʈ ����
	OnBnClickedButtonDefault();
	
	// ���Ͽ��� ���� �� �ҷ�����
	OnBnClickedButtonLoad();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void SettingDlg::OnBnClickedButtonSave()
{
	int nTesterNum;
	CString strStepEn;
	CString strLogPath;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	EolSetLog.SetFilePath(m_edit_set_file_path.m_strMsg);
	// Port ����
	EolSetLog.WriteSetting(COM_IO, m_edit_com_io.m_strMsg);
	EolSetLog.WriteSetting(COM_AM, m_edit_com_am.m_strMsg);
	EolSetLog.WriteSetting(COM_SCREW, m_edit_com_screw.m_strMsg);
	EolSetLog.WriteSetting(COM_BAR1, m_edit_com_bar1.m_strMsg);
	EolSetLog.WriteSetting(COM_BAR2, m_edit_com_bar2.m_strMsg);
	// Log File Path ����
	m_edit_set_log_path.GetWindowTextW(strLogPath);
	EolSetLog.WriteSetting(LOG_FILE_PATH, strLogPath);

	// Draw ����
	EolSetLog.WriteSetting(DRAW_VANISHY, m_edit_draw_vanishy.m_strMsg);
	EolSetLog.WriteSetting(DRAW_WIDTH, m_edit_draw_width.m_strMsg);
	EolSetLog.WriteSetting(DRAW_MOVEMENT, m_edit_draw_move.m_strMsg);
	EolSetLog.WriteSetting(DRAW_LANE_L_COLOR, m_edit_lane_l_color.m_strMsg);
	EolSetLog.WriteSetting(DRAW_LANE_R_COLOR, m_edit_lane_r_color.m_strMsg);
	// Tester ����
	EolSetLog.WriteSetting(TESTER_LINE, m_edit_product_line.m_strMsg);
	nTesterNum = _ttoi(m_edit_tester_num.m_strMsg);
	if ( (nTesterNum < 1) || (nTesterNum > TESTER_MAX) )
	{
		m_edit_tester_num.SetText(WHITE, BLACK, _T("1"), UPDATE_ON);
		m_edit_tester_num.SetWindowTextW(m_edit_tester_num.m_strMsg);
	}
	EolSetLog.WriteSetting(TESTER_NUM, m_edit_tester_num.m_strMsg);
	EolSetLog.WriteSetting(TESTER_1, 	m_edit_tester1.m_strMsg);
	EolSetLog.WriteSetting(TESTER_2,	m_edit_tester2.m_strMsg);
	EolSetLog.WriteSetting(TESTER_3,	m_edit_tester3.m_strMsg);
	EolSetLog.WriteSetting(TESTER_4,	m_edit_tester4.m_strMsg);
	EolSetLog.WriteSetting(TESTER_5,	m_edit_tester5.m_strMsg);
	EolSetLog.WriteSetting(TESTER_6,	m_edit_tester6.m_strMsg);
	EolSetLog.WriteSetting(TESTER_7,	m_edit_tester7.m_strMsg);
	EolSetLog.WriteSetting(TESTER_8,	m_edit_tester8.m_strMsg);
	EolSetLog.WriteSetting(TESTER_9,	m_edit_tester9.m_strMsg);
	EolSetLog.WriteSetting(TESTER_10,	m_edit_tester10.m_strMsg);
	EolSetLog.WriteSetting(TESTER_11,	m_edit_tester11.m_strMsg);
	EolSetLog.WriteSetting(TESTER_12,	m_edit_tester12.m_strMsg);
	EolSetLog.WriteSetting(TESTER_13,	m_edit_tester13.m_strMsg);
	EolSetLog.WriteSetting(TESTER_14,	m_edit_tester14.m_strMsg);
	// Process ����
	EolSetLog.WriteSetting(PROC_PRODUCT_TYPE, m_edit_proc_product_type.m_strMsg);
	EolSetLog.WriteSetting(PROC_MCU_VER, m_edit_proc_mcu_ver.m_strMsg);
	EolSetLog.WriteSetting(PROC_SW_VER, m_edit_proc_sw_ver.m_strMsg);
	EolSetLog.WriteSetting(PROC_SERIAL_NUM, m_edit_proc_serial_num.m_strMsg);
	EolSetLog.WriteSetting(PROC_LDW_SPD, m_edit_proc_ldw_spd.m_strMsg);
	EolSetLog.WriteSetting(PROC_FCW_SPD, m_edit_proc_fcw_spd.m_strMsg);

	// �˻��׸� ����
	strStepEn.Format(_T("%d"), m_check_mcu_ver);
	EolSetLog.WriteSetting(STEP_CHECK_MCU_VER,	strStepEn);
	strStepEn.Format(_T("%d"), m_check_sw_ver);
	EolSetLog.WriteSetting(STEP_CHECK_SW_VER, strStepEn);
	strStepEn.Format(_T("%d"), m_check_serial_num);
	EolSetLog.WriteSetting(STEP_CHECK_SERIAL_NUM, strStepEn);
	strStepEn.Format(_T("%d"), m_check_io_board);
	EolSetLog.WriteSetting(STEP_CHECK_IO_BOARD, strStepEn);
	strStepEn.Format(_T("%d"), m_check_screw);
	EolSetLog.WriteSetting(STEP_CHECK_SCREW, strStepEn);
	strStepEn.Format(_T("%d"), m_check_bar1);
	EolSetLog.WriteSetting(STEP_CHECK_BARCODE1, strStepEn);
	strStepEn.Format(_T("%d"), m_check_bar2);
	EolSetLog.WriteSetting(STEP_CHECK_BARCODE2, strStepEn);
	strStepEn.Format(_T("%d"), m_check_accleration);
	EolSetLog.WriteSetting(STEP_CHECK_ACCLERATION, strStepEn);
	strStepEn.Format(_T("%d"), m_check_speed_pulse);
	EolSetLog.WriteSetting(STEP_CHECK_SPEED_PULSE, strStepEn);
	strStepEn.Format(_T("%d"), m_check_dtc_clear);
	EolSetLog.WriteSetting(STEP_CHECK_DTC_CLEAR, strStepEn);

	strStepEn.Format(_T("%d"), m_check_ldw_speed);
	EolSetLog.WriteSetting(STEP_LDW_SPEED, strStepEn);
	strStepEn.Format(_T("%d"), m_check_fcw_speed);
	EolSetLog.WriteSetting(STEP_FCW_SPEED, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_detect);
	EolSetLog.WriteSetting(STEP_LDW_DETECT, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warn_l);
	EolSetLog.WriteSetting(STEP_LDW_WARN_L, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warn_r);
	EolSetLog.WriteSetting(STEP_LDW_WARN_R, strStepEn);
	strStepEn.Format(_T("%d"), m_check_fcw_warn);
	EolSetLog.WriteSetting(STEP_FCW_WARN,	strStepEn);
	strStepEn.Format(_T("%d"), m_check_fcw_warn2);
	EolSetLog.WriteSetting(STEP_FCW_WARN2,	strStepEn);
	strStepEn.Format(_T("%d"), m_check_fcw_warn3);
	EolSetLog.WriteSetting(STEP_FCW_WARN3,	strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnL_winkL);
	EolSetLog.WriteSetting(STEP_LDW_WARN_L_WINK_L, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnL_winkR);
	EolSetLog.WriteSetting(STEP_LDW_WARN_L_WINK_R, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnL_winkLR);
	EolSetLog.WriteSetting(STEP_LDW_WARN_L_WINK_LR, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnR_winkL);
	EolSetLog.WriteSetting(STEP_LDW_WARN_R_WINK_L, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnR_winkR);
	EolSetLog.WriteSetting(STEP_LDW_WARN_R_WINK_R, strStepEn);
	strStepEn.Format(_T("%d"), m_check_ldw_warnR_winkLR);
	EolSetLog.WriteSetting(STEP_LDW_WARN_R_WINK_LR, strStepEn);	
	strStepEn.Format(_T("%d"), m_check_fcda_warn);
	EolSetLog.WriteSetting(STEP_FCDA_WARN, strStepEn);
		
	EolSetLog.WriteSetting(STEP_ADAS_ALARM_DELAY, m_edit_adas_alarm_delay.m_strMsg);
	
	// ��� ����
	if ( m_radio_language == L_KOREAN )
	{
		EolSetLog.WriteSetting(SET_LANGUAGE, _T("KOREAN"));
	}
	else if ( m_radio_language == L_CHINESE )
	{
		EolSetLog.WriteSetting(SET_LANGUAGE, _T("CHINESE"));
	}
	else if ( m_radio_language == L_ENGLISH )
	{
		EolSetLog.WriteSetting(SET_LANGUAGE, _T("ENGLISH"));
	}
}


void SettingDlg::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	EolSetLog.SetFilePath(m_edit_set_file_path.m_strMsg);
	// Port ����
	m_edit_com_io.m_strMsg = EolSetLog.ReadSetting(COM_IO);
	m_edit_com_io.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_com_am.m_strMsg = EolSetLog.ReadSetting(COM_AM);
	m_edit_com_am.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_com_screw.m_strMsg = EolSetLog.ReadSetting(COM_SCREW);
	m_edit_com_screw.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_com_bar1.m_strMsg = EolSetLog.ReadSetting(COM_BAR1);
	m_edit_com_bar1.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_com_bar2.m_strMsg = EolSetLog.ReadSetting(COM_BAR2);
	m_edit_com_bar2.PostMessageW(_WM_THREAD_UPDATE);

	// Log File Path ����
	m_edit_set_log_path.SetWindowTextW(EolSetLog.ReadSetting(LOG_FILE_PATH));

	// Draw ����
	m_edit_draw_vanishy.m_strMsg = EolSetLog.ReadSetting(DRAW_VANISHY);
	m_edit_draw_vanishy.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_draw_width.m_strMsg = EolSetLog.ReadSetting(DRAW_WIDTH);
	m_edit_draw_width.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_draw_move.m_strMsg = EolSetLog.ReadSetting(DRAW_MOVEMENT);
	m_edit_draw_move.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_lane_l_color.m_strMsg = EolSetLog.ReadSetting(DRAW_LANE_L_COLOR);
	m_edit_lane_l_color.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_lane_r_color.m_strMsg = EolSetLog.ReadSetting(DRAW_LANE_R_COLOR);
	m_edit_lane_r_color.PostMessageW(_WM_THREAD_UPDATE);

	// Tester ����
	m_edit_tester_num.m_strMsg = EolSetLog.ReadSetting(TESTER_NUM);
	m_edit_tester_num.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester1.m_strMsg = 	EolSetLog.ReadSetting(TESTER_1);
	m_edit_tester2.m_strMsg =	EolSetLog.ReadSetting(TESTER_2);
	m_edit_tester3.m_strMsg =	EolSetLog.ReadSetting(TESTER_3);
	m_edit_tester4.m_strMsg =	EolSetLog.ReadSetting(TESTER_4);
	m_edit_tester5.m_strMsg =	EolSetLog.ReadSetting(TESTER_5);
	m_edit_tester6.m_strMsg =	EolSetLog.ReadSetting(TESTER_6);
	m_edit_tester7.m_strMsg =	EolSetLog.ReadSetting(TESTER_7);
	m_edit_tester8.m_strMsg =	EolSetLog.ReadSetting(TESTER_8);
	m_edit_tester9.m_strMsg =	EolSetLog.ReadSetting(TESTER_9);
	m_edit_tester10.m_strMsg =	EolSetLog.ReadSetting(TESTER_10);
	m_edit_tester11.m_strMsg =	EolSetLog.ReadSetting(TESTER_11);
	m_edit_tester12.m_strMsg =	EolSetLog.ReadSetting(TESTER_12);
	m_edit_tester13.m_strMsg =	EolSetLog.ReadSetting(TESTER_13);
	m_edit_tester14.m_strMsg =	EolSetLog.ReadSetting(TESTER_14);
	m_edit_product_line.m_strMsg = EolSetLog.ReadSetting(TESTER_LINE);
	m_edit_tester1.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester2.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester3.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester4.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester5.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester6.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester7.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester8.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester9.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester10.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester11.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester12.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester13.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_tester14.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_product_line.PostMessageW(_WM_THREAD_UPDATE);
	// Process ����
	m_edit_proc_product_type.m_strMsg = EolSetLog.ReadSetting(PROC_PRODUCT_TYPE);
	m_edit_proc_product_type.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_proc_mcu_ver.m_strMsg = EolSetLog.ReadSetting(PROC_MCU_VER);
	m_edit_proc_mcu_ver.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_proc_sw_ver.m_strMsg = EolSetLog.ReadSetting(PROC_SW_VER);
	m_edit_proc_sw_ver.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_proc_serial_num.m_strMsg = EolSetLog.ReadSetting(PROC_SERIAL_NUM);
	m_edit_proc_serial_num.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_proc_ldw_spd.m_strMsg = EolSetLog.ReadSetting(PROC_LDW_SPD);
	m_edit_proc_ldw_spd.PostMessageW(_WM_THREAD_UPDATE);
	m_edit_proc_fcw_spd.m_strMsg = EolSetLog.ReadSetting(PROC_FCW_SPD);
	m_edit_proc_fcw_spd.PostMessageW(_WM_THREAD_UPDATE);

	m_edit_adas_alarm_delay.m_strMsg = EolSetLog.ReadSetting(STEP_ADAS_ALARM_DELAY);
	m_edit_adas_alarm_delay.PostMessageW(_WM_THREAD_UPDATE);

	///////////////////////////////////////////////////////////////////////////
	// ����Ʈ Ű���� ����
	m_edit_com_io.SetWindowTextW(m_edit_com_io.m_strMsg);
	m_edit_com_am.SetWindowTextW(m_edit_com_am.m_strMsg);
	m_edit_com_screw.SetWindowTextW(m_edit_com_screw.m_strMsg);
	m_edit_com_bar1.SetWindowTextW(m_edit_com_bar1.m_strMsg);
	m_edit_com_bar2.SetWindowTextW(m_edit_com_bar2.m_strMsg);

	m_edit_draw_vanishy.SetWindowTextW(m_edit_draw_vanishy.m_strMsg);
	m_edit_draw_width.SetWindowTextW(m_edit_draw_width.m_strMsg);
	m_edit_draw_move.SetWindowTextW(m_edit_draw_move.m_strMsg);	
	m_edit_lane_l_color.SetWindowTextW(m_edit_lane_l_color.m_strMsg);
	m_edit_lane_r_color.SetWindowTextW(m_edit_lane_r_color.m_strMsg);

	m_edit_tester_num.SetWindowTextW(m_edit_tester_num.m_strMsg);
	m_edit_tester1.SetWindowTextW	(m_edit_tester1.m_strMsg);
	m_edit_tester2.SetWindowTextW	(m_edit_tester2.m_strMsg);
	m_edit_tester3.SetWindowTextW	(m_edit_tester3.m_strMsg);
	m_edit_tester4.SetWindowTextW	(m_edit_tester4.m_strMsg);
	m_edit_tester5.SetWindowTextW	(m_edit_tester5.m_strMsg);
	m_edit_tester6.SetWindowTextW	(m_edit_tester6.m_strMsg);
	m_edit_tester7.SetWindowTextW	(m_edit_tester7.m_strMsg);
	m_edit_tester8.SetWindowTextW	(m_edit_tester8.m_strMsg);
	m_edit_tester9.SetWindowTextW	(m_edit_tester9.m_strMsg);
	m_edit_tester10.SetWindowTextW	(m_edit_tester10.m_strMsg);
	m_edit_tester11.SetWindowTextW	(m_edit_tester11.m_strMsg);
	m_edit_tester12.SetWindowTextW	(m_edit_tester12.m_strMsg);
	m_edit_tester13.SetWindowTextW	(m_edit_tester13.m_strMsg);
	m_edit_tester14.SetWindowTextW	(m_edit_tester14.m_strMsg);
	m_edit_product_line.SetWindowTextW	(m_edit_product_line.m_strMsg);

	m_edit_proc_product_type.SetWindowTextW(m_edit_proc_product_type.m_strMsg);
	m_edit_proc_mcu_ver.SetWindowTextW(m_edit_proc_mcu_ver.m_strMsg);
	m_edit_proc_sw_ver.SetWindowTextW(m_edit_proc_sw_ver.m_strMsg);
	m_edit_proc_serial_num.SetWindowTextW(m_edit_proc_serial_num.m_strMsg);
	m_edit_proc_ldw_spd.SetWindowTextW(m_edit_proc_ldw_spd.m_strMsg);
	m_edit_proc_fcw_spd.SetWindowTextW(m_edit_proc_fcw_spd.m_strMsg);

	// �˻��׸� ������
	m_edit_adas_alarm_delay.SetWindowTextW(m_edit_adas_alarm_delay.m_strMsg);
	// �˻��׸� ����
	m_check_mcu_ver    = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_MCU_VER));
	m_check_sw_ver	   = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_SW_VER));
	m_check_serial_num = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_SERIAL_NUM));
	m_check_io_board   = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_IO_BOARD));
	m_check_screw	   = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_SCREW));
	m_check_bar1	   = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_BARCODE1));
	m_check_bar2	   = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_BARCODE2));
	m_check_accleration= _ttoi(EolSetLog.ReadSetting(STEP_CHECK_ACCLERATION));
	m_check_speed_pulse= _ttoi(EolSetLog.ReadSetting(STEP_CHECK_SPEED_PULSE));
	m_check_dtc_clear  = _ttoi(EolSetLog.ReadSetting(STEP_CHECK_DTC_CLEAR));

	m_check_ldw_speed  = _ttoi(EolSetLog.ReadSetting(STEP_LDW_SPEED));
	m_check_fcw_speed  = _ttoi(EolSetLog.ReadSetting(STEP_FCW_SPEED));
	m_check_ldw_detect = _ttoi(EolSetLog.ReadSetting(STEP_LDW_DETECT));
	m_check_ldw_warn_l = _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_L));
	m_check_ldw_warn_r = _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_R));
	m_check_fcw_warn   = _ttoi(EolSetLog.ReadSetting(STEP_FCW_WARN));
	m_check_fcw_warn2   = _ttoi(EolSetLog.ReadSetting(STEP_FCW_WARN2));
	m_check_fcw_warn3   = _ttoi(EolSetLog.ReadSetting(STEP_FCW_WARN3));
	m_check_ldw_warnL_winkL		= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_L_WINK_L));
	m_check_ldw_warnL_winkR		= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_L_WINK_R));
	m_check_ldw_warnL_winkLR	= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_L_WINK_LR));
	m_check_ldw_warnR_winkL		= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_R_WINK_L));
	m_check_ldw_warnR_winkR		= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_R_WINK_R));
	m_check_ldw_warnR_winkLR	= _ttoi(EolSetLog.ReadSetting(STEP_LDW_WARN_R_WINK_LR));
	m_check_fcda_warn			= _ttoi(EolSetLog.ReadSetting(STEP_FCDA_WARN));

	// ��� ����
	if (EolSetLog.ReadSetting(SET_LANGUAGE) == _T("KOREAN"))
	{
		m_radio_language = L_KOREAN;
	}
	else if (EolSetLog.ReadSetting(SET_LANGUAGE) == _T("CHINESE"))
	{
		m_radio_language = L_CHINESE;
	}
	else if (EolSetLog.ReadSetting(SET_LANGUAGE) == _T("ENGLISH"))
	{
		m_radio_language = L_ENGLISH;
	}

	UpdateData(FALSE);
}


void SettingDlg::OnBnClickedButtonDefault()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// Comport ����
	m_edit_com_io.SetText(WHITE, PURPLE, _T("COM3"), UPDATE_ON);
	m_edit_com_am.SetText(WHITE, PURPLE, _T("COM4"), UPDATE_ON);
	m_edit_com_screw.SetText(WHITE, PURPLE, _T("COM5"), UPDATE_ON);
	m_edit_com_bar1.SetText(WHITE, PURPLE, _T("COM6"), UPDATE_ON);
	m_edit_com_bar2.SetText(WHITE, PURPLE, _T("COM7"), UPDATE_ON);

	// Log File Path ����
	m_edit_set_log_path.SetWindowTextW(_T("D:\\LDWS_LOG\\"));

	// Draw ����
	m_edit_draw_vanishy.SetText(WHITE, DARKGREEN, _T("90"), UPDATE_ON);
	m_edit_draw_width.SetText(WHITE, DARKGREEN, _T("12"), UPDATE_ON);
	m_edit_draw_move.SetText(WHITE, DARKGREEN, _T("30"), UPDATE_ON);
	m_edit_lane_l_color.SetText(WHITE, DARKGREEN, _T("YELLOW"), UPDATE_ON);
	m_edit_lane_r_color.SetText(WHITE, DARKGREEN, _T("WHITE"), UPDATE_ON);

	// Tester ����
	m_edit_tester_num.SetText(WHITE, BLACK, _T("8"), UPDATE_ON);
	m_edit_tester1.SetText(WHITE, BLACK, _T("������"), UPDATE_ON);
	m_edit_tester2.SetText(WHITE, BLACK, _T("�����"), UPDATE_ON);
	m_edit_tester3.SetText(WHITE, BLACK, _T("�۹̼�"), UPDATE_ON);
	m_edit_tester4.SetText(WHITE, BLACK, _T("�ڻ��"), UPDATE_ON);
	m_edit_tester5.SetText(WHITE, BLACK, _T("�ڼ�"), UPDATE_ON);
	m_edit_tester6.SetText(WHITE, BLACK, _T("������"), UPDATE_ON);
	m_edit_tester7.SetText(WHITE, BLACK, _T("���⼱"), UPDATE_ON);
	m_edit_tester8.SetText(WHITE, BLACK, _T("�����"), UPDATE_ON);
	m_edit_tester9.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_tester10.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_tester11.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_tester12.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_tester13.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_tester14.SetText(WHITE, BLACK, _T("-"), UPDATE_ON);
	m_edit_product_line.SetText(WHITE, BLACK, _T("PLK_LDWS_4ȣ"), UPDATE_ON);

	// Process ����
	m_edit_proc_product_type.SetText(WHITE, DARKORANGE, _T("R7"), UPDATE_ON);
	m_edit_proc_mcu_ver.SetText(WHITE, DARKORANGE, _T("V220"), UPDATE_ON);
	m_edit_proc_sw_ver.SetText(WHITE, DARKORANGE, _T("V2.0.0"), UPDATE_ON);
	m_edit_proc_serial_num.SetText(WHITE, DARKORANGE, _T("ABC123"), UPDATE_ON);
	m_edit_proc_ldw_spd.SetText(WHITE, DARKORANGE, _T("100"), UPDATE_ON);
	m_edit_proc_fcw_spd.SetText(WHITE, DARKORANGE, _T("100"), UPDATE_ON);

	// ����Ʈ Ű���� ����
	m_edit_com_io.SetWindowTextW(m_edit_com_io.m_strMsg);
	m_edit_com_am.SetWindowTextW(m_edit_com_am.m_strMsg);
	m_edit_com_screw.SetWindowTextW(m_edit_com_screw.m_strMsg);
	m_edit_com_bar1.SetWindowTextW(m_edit_com_bar1.m_strMsg);
	m_edit_com_bar2.SetWindowTextW(m_edit_com_bar2.m_strMsg);

	m_edit_draw_vanishy.SetWindowTextW(m_edit_draw_vanishy.m_strMsg);
	m_edit_draw_width.SetWindowTextW(m_edit_draw_width.m_strMsg);
	m_edit_draw_move.SetWindowTextW(m_edit_draw_move.m_strMsg);
	m_edit_lane_l_color.SetWindowTextW(m_edit_lane_l_color.m_strMsg);
	m_edit_lane_r_color.SetWindowTextW(m_edit_lane_r_color.m_strMsg);

	m_edit_proc_product_type.SetWindowTextW(m_edit_proc_product_type.m_strMsg);
	m_edit_proc_mcu_ver.SetWindowTextW(m_edit_proc_mcu_ver.m_strMsg);
	m_edit_proc_sw_ver.SetWindowTextW(m_edit_proc_sw_ver.m_strMsg);
	m_edit_proc_serial_num.SetWindowTextW(m_edit_proc_serial_num.m_strMsg);
	m_edit_proc_ldw_spd.SetWindowTextW(m_edit_proc_ldw_spd.m_strMsg);
	m_edit_proc_fcw_spd.SetWindowTextW(m_edit_proc_fcw_spd.m_strMsg);
	
	// �׽�Ʈ �׸� ����
	m_edit_adas_alarm_delay.SetText(WHITE, RED, _T("0"), UPDATE_ON);
	m_edit_adas_alarm_delay.SetWindowTextW(m_edit_adas_alarm_delay.m_strMsg);
	//ADAS
	m_check_ldw_speed = 1;
	m_check_fcw_speed = 1;
	m_check_ldw_detect = 1;
	m_check_ldw_warn_l = 1;
	m_check_ldw_warn_r = 1;
	m_check_ldw_warnL_winkL = 0;
	m_check_ldw_warnL_winkR = 0;
	m_check_ldw_warnL_winkLR = 0;
	m_check_ldw_warnR_winkL = 0;
	m_check_ldw_warnR_winkR = 0;
	m_check_ldw_warnR_winkLR = 0;
	m_check_fcda_warn = 0;
	m_check_fcw_warn = 1;
	m_check_fcw_warn2 = 0;
	m_check_fcw_warn3 = 0;
	m_check_mcu_ver = 1;
	m_check_sw_ver = 1;
	m_check_serial_num = 1;
	m_check_io_board = 1;
	m_check_screw = 1;
	m_check_bar1 = 1;
	m_check_bar2 = 1;
	m_check_accleration= 1;
	m_check_speed_pulse= 1;
	m_check_dtc_clear  = 1;

	// ��� ����
	m_radio_language = 0;

	UpdateData(FALSE);
}

HBRUSH SettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch(nCtlColor)
    {
        // �б� ���� ��Ʈ��
        case CTLCOLOR_STATIC:
        {
			pDC->SetBkColor(WHITE);
            pDC->SetTextColor(BLACK);
        }
        break;
    }

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void SettingDlg::DrawDoubleBuffering(void)
{
    CDC *pDC = GetDC();     // ���� DC ���
    CRect rect;
    GetClientRect(rect);    // ���� â ������ ���
 
    CDC MemDC;              // �޸� DC
    CBitmap *pOldBitmap;    // �޸� DC�� ��Ʈ��
    CBitmap bmp;            // ���� DC ������ ��Ʈ��
 
    MemDC.CreateCompatibleDC(pDC);                                  // �޸� DC�� ���� DC�� ���� ��ġ
    bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());   // ��Ʈ�ʰ� ���� DC�� ���� ��ġ 
    pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);               // �޸� DC�� ��Ʈ�� ����
    MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);     // ���� ��� 
                                                                    // PATCOPY(����), BLACKNESS(����), WHITENESS(���), DSTINVERT(�������)
 
    // �� Object���� �޸� DC�� �׸���
     
    // �޸� DC�� ���� DC�� ����
    pDC->BitBlt(0, 0, rect.Width(),rect.Height(), &MemDC, 0,0,SRCCOPY);
 
    // ���� �޸� �� ��Ʈ�� ����
    MemDC.SelectObject(pOldBitmap);
    MemDC.DeleteDC();
}

void SettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void SettingDlg::OnEnChangeEditSetFilePath()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_set_file_path.GetWindowTextW(m_edit_set_file_path.m_strMsg);
	m_edit_set_file_path.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditComIo()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_com_io.GetWindowTextW(m_edit_com_io.m_strMsg);
	m_edit_com_io.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditComAm()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_com_am.GetWindowTextW(m_edit_com_am.m_strMsg);
	m_edit_com_am.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditComScrew()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_com_screw.GetWindowTextW(m_edit_com_screw.m_strMsg);
	m_edit_com_screw.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditComBar1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_com_bar1.GetWindowTextW(m_edit_com_bar1.m_strMsg);
	m_edit_com_bar1.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditComBar2()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_com_bar2.GetWindowTextW(m_edit_com_bar2.m_strMsg);
	m_edit_com_bar2.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditDrawVanishy()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_draw_vanishy.GetWindowTextW(m_edit_draw_vanishy.m_strMsg);
	m_edit_draw_vanishy.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditDrawWidth()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_draw_width.GetWindowTextW(m_edit_draw_width.m_strMsg);
	m_edit_draw_width.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditDrawMove()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_draw_move.GetWindowTextW(m_edit_draw_move.m_strMsg);
	m_edit_draw_move.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void SettingDlg::OnEnChangeEditProcProductType()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_product_type.GetWindowTextW(m_edit_proc_product_type.m_strMsg);
	m_edit_proc_product_type.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnEnChangeEditProcMcuVer()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_mcu_ver.GetWindowTextW(m_edit_proc_mcu_ver.m_strMsg);
	m_edit_proc_mcu_ver.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnEnChangeEditProcSwVer()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_sw_ver.GetWindowTextW(m_edit_proc_sw_ver.m_strMsg);
	m_edit_proc_sw_ver.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnEnChangeEditProcSerialNum()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_serial_num.GetWindowTextW(m_edit_proc_serial_num.m_strMsg);
	m_edit_proc_serial_num.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnEnChangeEditProcLdwSpd()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_ldw_spd.GetWindowTextW(m_edit_proc_ldw_spd.m_strMsg);
	m_edit_proc_ldw_spd.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnEnChangeEditProcFcwSpd()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_edit_proc_fcw_spd.GetWindowTextW(m_edit_proc_fcw_spd.m_strMsg);
	m_edit_proc_fcw_spd.PostMessageW(_WM_THREAD_UPDATE);
}

void SettingDlg::OnEnChangeEditTesterNum()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);

	m_edit_tester_num.GetWindowTextW(m_edit_tester_num.m_strMsg);
	m_edit_tester_num.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void SettingDlg::OnEnChangeEditTester1()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester1.GetWindowTextW	(m_edit_tester1.m_strMsg);							
	m_edit_tester1.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester2()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester2.GetWindowTextW	(m_edit_tester2.m_strMsg);							
	m_edit_tester2.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester3()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester3.GetWindowTextW	(m_edit_tester3.m_strMsg);							
	m_edit_tester3.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester4()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester4.GetWindowTextW	(m_edit_tester4.m_strMsg);							
	m_edit_tester4.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester5()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester5.GetWindowTextW	(m_edit_tester5.m_strMsg);							
	m_edit_tester5.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester6()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester6.GetWindowTextW	(m_edit_tester6.m_strMsg);							
	m_edit_tester6.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester7()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester7.GetWindowTextW	(m_edit_tester7.m_strMsg);							
	m_edit_tester7.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester8()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester8.GetWindowTextW	(m_edit_tester8.m_strMsg);							
	m_edit_tester8.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester9()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester9.GetWindowTextW	(m_edit_tester9.m_strMsg);							
	m_edit_tester9.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester10()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester10.GetWindowTextW	(m_edit_tester10.m_strMsg);							
	m_edit_tester10.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester11()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester11.GetWindowTextW	(m_edit_tester11.m_strMsg);							
	m_edit_tester11.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester12()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester12.GetWindowTextW	(m_edit_tester12.m_strMsg);							
	m_edit_tester12.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester13()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester13.GetWindowTextW	(m_edit_tester13.m_strMsg);							
	m_edit_tester13.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}									
void SettingDlg::OnEnChangeEditTester14()									
{									
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����								
	// CDialogEx::OnInitDialog() �Լ��� ������ 								
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������								
	// �� �˸� �޽����� ������ �ʽ��ϴ�.								
	UpdateData(TRUE);								
									
	m_edit_tester14.GetWindowTextW	(m_edit_tester14.m_strMsg);							
	m_edit_tester14.PostMessageW(_WM_THREAD_UPDATE);								
									
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.								
}


// ������ ���� �Ŀ� ���� ��, ���� ���̾�α׸� �ٽ� �ʱ�ȭ�ϴ� �޼��� ����
void SettingDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�. 
	((CR7EOLvs2010Dlg *)GetParent())->PostMessageW(_WM_MAIN_DLG_INIT);

	CDialogEx::OnOK();
}


void SettingDlg::OnEnChangeEditProductLine()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);								
									
	m_edit_product_line.GetWindowTextW	(m_edit_product_line.m_strMsg);							
	m_edit_product_line.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditLaneLColor()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);								
									
	m_edit_lane_l_color.GetWindowTextW	(m_edit_lane_l_color.m_strMsg);							
	m_edit_lane_l_color.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingDlg::OnEnChangeEditLaneRColor()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);								
									
	m_edit_lane_r_color.GetWindowTextW	(m_edit_lane_r_color.m_strMsg);							
	m_edit_lane_r_color.PostMessageW(_WM_THREAD_UPDATE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL SettingDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect( rect, SOFT_LTGREEN );
 
    return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}


void SettingDlg::OnEnChangeEditAdasAlarmDelay()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);								
									
	m_edit_adas_alarm_delay.GetWindowTextW	(m_edit_adas_alarm_delay.m_strMsg);							
	m_edit_adas_alarm_delay.PostMessageW(_WM_THREAD_UPDATE);
}


void SettingDlg::OnBnClickedRadio(UINT msg)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	switch(m_radio_language)
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
