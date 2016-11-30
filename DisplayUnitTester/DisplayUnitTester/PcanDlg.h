#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// PcanDlg 대화 상자입니다.

class PcanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PcanDlg)

public:
	PcanDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~PcanDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PCAN_PROTOCOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();	// 초기화하는 다이얼로그

	void OnThreadMsgStart(WPARAM a_wParam, LPARAM a_lParam);// Thread Start
	void OnThreadMsgEnd(WPARAM a_wParam, LPARAM a_lParam);	// Thread End
	CWinThread * m_pThreadPcanMain;							// pThread

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPcanStart();
	afx_msg void OnBnClickedCheckCanStart();
	BOOL m_check_can_start;
	CListCtrl m_list_pcan;
};
