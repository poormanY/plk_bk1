#pragma once
#include "CommThread.h"
#include "DisplayUnitTesterDlg.h"
#include "afxwin.h"

// SerialDlg 대화 상자입니다.

class SerialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SerialDlg)

public:
	SerialDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SerialDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SERIAL_PROTOCOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	BOOL SerialDlg::OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	HANDLE m_hThread_SerialProc;//Thread Handler
	static UINT Thread_Serial_Display(SerialDlg* pDlg);//Thread함수

	CDisplayUnitTesterDlg* pDisplayUnitTesterDlg;
	CCommThread m_ComuPort;
	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

	CBrush m_brush_black;
    CBrush m_brush_black_hatch;


	void SerialDlg::ClearOperationTxT(void);
	void SerialDlg::ClearRcvMsgTxT(void);
	void SerialDlg::ClearSndMsgTxT(void);
	void SerialDlg::WriteOperationTxT(CString txt);
	void SerialDlg::WriteRcvMsgTxT(CString txt);
	void SerialDlg::DisablePortComboBox(void);
	void SerialDlg::EnablePortComboBox(void);

	CString SerialDlg::ByteToHex(BYTE aByte);
	CString SerialDlg::ByteToAscii(BYTE aByte);
	BYTE SerialDlg::HexTo8Bits(CString aHex);
	BYTE SerialDlg::HexToByte(CString aHex);
	BYTE SerialDlg::AsciiToByte(CString aAscii);

public:
	CComboBox m_combo_port_name;
	CComboBox m_combo_port_baud;
	CComboBox m_combo_port_data_bit;
	CComboBox m_combo_port_stop_bit;
	CComboBox m_combo_port_parity;
	CComboBox m_combo_type_snd;
	CComboBox m_combo_type_rcv;
	afx_msg void OnDropdownComboPortName();
	afx_msg void OnBnClickedButtonPortOpen();
	afx_msg void OnBnClickedButtonPortClose();
	CEdit m_edit_serial_rcv;
	CEdit m_edit_serial_operation;
	CEdit m_edit_serial_snd;
	afx_msg void OnBnClickedButtonClearOperation();
	afx_msg void OnBnClickedButtonClearSnd();
	afx_msg void OnBnClickedButtonClearRcv();
	afx_msg void OnBnClickedButtonSnd();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonSave();
	CString m_edit_serial_rcv_str;
	afx_msg void OnBnClickedButtonLoad();
	CString m_edit_serial_snd_str;
};
