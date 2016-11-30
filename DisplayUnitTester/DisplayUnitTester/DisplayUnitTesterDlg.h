
// DisplayUnitTesterDlg.h : ��� ����
//
#pragma once
#include "CommThread.h"	// Added by ClassView
#include "afxwin.h"

// CDisplayUnitTesterDlg ��ȭ ����
class CDisplayUnitTesterDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDisplayUnitTesterDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DISPLAYUNITTESTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
public:	
	CCommThread m_ComuPort;
	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

	CString byIndexComPort(int xPort);// ��Ʈ�̸� �ޱ�
	int toIdxComPort(CString PortName);// ��Ʈ��ȣ �ޱ�(param : ��Ʈ�̸�)
	DWORD byIndexBaud(int xBaud);// ���۷� �ޱ�
	BYTE byIndexData(int xData);//������ ��Ʈ �ޱ�
	BYTE byIndexStop(int xStop);// �����Ʈ �ޱ� 
	BYTE byIndexParity(int xParity);// �縮Ƽ �ޱ�
	CString StrChckPortOPen(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity); // ����Port�� ��� OPEN, ����Port�� ��� Connected�� ����
private:

protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	int PaintBitmapOnWindow(int IDB_BitmapNum, int nWidth, int nHeight);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonComSearch();
	CListCtrl listBoxCom;
	afx_msg void OnClickListCom(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_comboComport;
	afx_msg void OnBnClickedButtonDisplay();
	afx_msg void OnBnClickedButtonJtpProtocol();
	afx_msg void OnBnClickedButtonDisplay2();
	afx_msg void OnBnClickedButtonPcan();
	afx_msg void OnBnClickedButtonSerialComm();
	afx_msg void OnBnClickedButtonMcu();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
