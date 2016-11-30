#pragma once
#include "DisplayUnitTesterDlg.h"
#include "CommThread.h"	// Added by ClassView
#include "jtp.h"
#include "afxwin.h"

// McuDlg 대화 상자입니다.

class McuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(McuDlg)

public:
	McuDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~McuDlg();

	virtual BOOL OnInitDialog();	// 초기화하는 다이얼로그

	CDisplayUnitTesterDlg* pDisplayUnitTesterDlg;
	BOOL BoolChckPortOPen_Jtp(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity);
	void SendCheckMcuVersion_R7();
	void SendCheckMcuVersion_OPX();
	void SendCheckMcuVersion_Display();

	void McuTestStatus_Ready(void);
	void McuTestStatus_Testing(void);

	CJtp m_Jtp;
	CCommThread m_ComuPort;

	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

	CString strVersion;	// version 확인
	
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MCU_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
		

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	int m_radio_mcu;
	afx_msg void OnBnClickedRadio(UINT msg);
	CString m_edit_mcu_version;
	CString m_edit_mcu_test;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_brush_mcu_test;
	COLORREF McuTestBG_Color;
	COLORREF McuTestText_Color;

	HANDLE m_hThread_McuTest;//Thread Handler
	static UINT Thread_McuTest_Display(McuDlg* pDlg);//Thread함수
	CButton m_button_test;
	CButton m_button_close;
	CEdit m_cedit_mcu_test;
};
