
// DisplayUnitTesterDlg.h : 헤더 파일
//
#pragma once
#include "CommThread.h"	// Added by ClassView
#include "afxwin.h"

// CDisplayUnitTesterDlg 대화 상자
class CDisplayUnitTesterDlg : public CDialogEx
{
// 생성입니다.
public:
	CDisplayUnitTesterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DISPLAYUNITTESTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
public:	
	CCommThread m_ComuPort;
	int		m_iStopBit;
	int		m_iSerialPort;
	int		m_iParity;
	int		m_iDataBit;
	int		m_iBaudRate;

	CString byIndexComPort(int xPort);// 포트이름 받기
	int toIdxComPort(CString PortName);// 포트번호 받기(param : 포트이름)
	DWORD byIndexBaud(int xBaud);// 전송률 받기
	BYTE byIndexData(int xData);//데이터 비트 받기
	BYTE byIndexStop(int xStop);// 스톱비트 받기 
	BYTE byIndexParity(int xParity);// 펠리티 받기
	CString StrChckPortOPen(CString strPortName, int iBaudRate, int iDataBit, int iStopBit, int iParity); // 열린Port의 경우 OPEN, 닫힌Port의 경우 Connected를 리턴
private:

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
