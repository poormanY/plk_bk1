#pragma once
#include "DisplayUnitTesterDlg.h"
#include "CommThread.h"	// Added by ClassView
#include "jtp.h"
#include "afxwin.h"

// McuDlg ��ȭ �����Դϴ�.

class McuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(McuDlg)

public:
	McuDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~McuDlg();

	virtual BOOL OnInitDialog();	// �ʱ�ȭ�ϴ� ���̾�α�

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

	CString strVersion;	// version Ȯ��
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MCU_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
		

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
	static UINT Thread_McuTest_Display(McuDlg* pDlg);//Thread�Լ�
	CButton m_button_test;
	CButton m_button_close;
	CEdit m_cedit_mcu_test;
};
