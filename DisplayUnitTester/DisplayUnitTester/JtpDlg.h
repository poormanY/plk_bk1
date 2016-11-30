#pragma once
#include "afxwin.h"
#include "DisplayUnitTesterDlg.h"
#include "CommThread.h"	// Added by ClassView
#include "jtp.h"
#include "TextStatic.h"


// JtpDlg 대화 상자입니다.

class JtpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(JtpDlg)

public:
	JtpDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~JtpDlg();

	CDisplayUnitTesterDlg* pDisplayUnitTesterDlg;
	CJtp m_Jtp;
	CCommThread m_ComuPort;
	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_JTP_PROTOCOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	BOOL JtpDlg::OnBnClickedButtonPortOpen_Open();
	BOOL JtpDlg::OnBnClickedButtonPortOpen_Close();

public:
	HANDLE m_hThread_JtpProc;//Thread Handler
	static UINT Thread_JTP_Protocol(JtpDlg* pDlg);//Thread함수

	virtual BOOL OnInitDialog();	// 초기화하는 다이얼로그
	int JtpDlg::ConvertHexToInt(CString stHex); // CString Hex -> Int value

	CComboBox m_combo_port_num;
	afx_msg void OnDropdownComboPortNum();
	afx_msg void OnBnClickedButtonPortOpen();
	afx_msg void OnBnClickedButtonSend();
	CButton m_button_port_open;
	CString m_edit_header;
	CString m_edit_tgtid;
	CString m_edit_srcid;
	CString m_edit_cmd;
	CString m_edit_para;
	CString m_edit_datalen;
	CString m_edit_chksum;
	CString m_edit_footer;
	CString m_edit_data1;
	CString m_edit_data2;
	CString m_edit_data3;
	CString m_edit_data4;
	CString m_edit_data5;
	CString m_edit_data6;
	CString m_edit_data7;
	CString m_edit_data8;
	CTextStatic m_edit_comm_status;
	CString m_edit_out_header;
	CString m_edit_out_tgtid;
	CString m_edit_out_srcid;
	CString m_edit_out_cmd;
	CString m_edit_out_para;
	CString m_edit_out_datalen;
	CString m_edit_out_chksum;
	CString m_edit_out_footer;
	CString m_edit_out_data1;
	CString m_edit_out_data2;
	CString m_edit_out_data3;
	CString m_edit_out_data4;
	CString m_edit_out_data5;
	CString m_edit_out_data6;
	CString m_edit_out_data7;
	CString m_edit_out_data8;
	afx_msg void OnBnClickedExit();
	BOOL m_check_continue;
	afx_msg void OnBnClickedButtonChksum();
};
