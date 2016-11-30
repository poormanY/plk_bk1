#pragma once
#include "DisplayUnitTesterDlg.h"
#include "CommThread.h"	// Added by ClassView
#include "jtp.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TextStatic.h"

// DisplayDlg 대화 상자입니다.

class DisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DisplayDlg)

public:
	DisplayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~DisplayDlg();

	CDisplayUnitTesterDlg* pDisplayUnitTesterDlg;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DISPLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();	// 초기화하는 다이얼로그

	HANDLE m_hThread_JtpDisplay;//Thread Handler
	HANDLE m_hThread_TestDisplay;//Thread Handler
	static UINT Thread_JTP_Display(DisplayDlg* pDlg);//Thread함수
	static UINT Thread_Test_Display(DisplayDlg* pDlg);//Test Thread함수
	
	CJtp m_Jtp;
	CCommThread m_ComuPort;
	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

	BOOL DisplayDlg::BoolChckPortOPen_Jtp(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity);
	
	afx_msg void OnBnClickedButtonDisplayConnect();
	CProgressCtrl m_progConnect;
	CComboBox m_combo_PortNum;
	void OnBnClickedButtonConnect_Connect();
	void OnBnClickedButtonConnect_Disconnect();
	afx_msg void OnBnClickedButtonConnect();
	CButton m_button_connect;
	int m_edit_input_button;
	afx_msg void OnBnClickedButtonTest();
	BOOL m_check_device_on;
	BOOL m_check_install_mode;
	BOOL m_check_device_error;
	BOOL m_check_display_on;
	BOOL m_check_brake;
	BOOL m_check_turn_left;
	BOOL m_check_turn_right;
	BOOL m_check_recording;
	BOOL m_check_lane_detect;
	BOOL m_check_ldw_left;
	BOOL m_check_ldw_right;
	BOOL m_check_ldw_no_dispaly;
	BOOL m_check_ldw_error;
	BOOL m_check_hmw_detect;
	BOOL m_check_hmw_warn;
	BOOL m_check_fcw_warn;
	BOOL m_check_vb_warn;
	BOOL m_check_fcda_run;
	BOOL m_check_fcda_detect;
	BOOL m_check_fcda_alarm;
	BOOL m_check_pd_detect;
	BOOL m_check_pd_warn;
	BOOL m_check_hba_on;
	BOOL m_check_hba_warn;
	int m_radio_day;
	afx_msg void OnBnClickedRadio(UINT msg);
	int m_edt_ttt;
	int m_edt_tsr_speed;
	int m_edt_tsr_overspeed;
	afx_msg void OnBnClickedOk();
	CTextStatic m_edit_notice;
	CButton m_button_test;
	CString m_edit_display_version;
	CString m_edit_set_version;
	CString m_DisplayVersion;
	BOOL m_check_signal_en;

private :
public:
	BOOL m_check_hmw_warn2;
	BOOL m_check_hmw_warn3;
};
