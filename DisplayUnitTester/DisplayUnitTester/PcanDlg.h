#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// PcanDlg ��ȭ �����Դϴ�.

class PcanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PcanDlg)

public:
	PcanDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~PcanDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PCAN_PROTOCOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();	// �ʱ�ȭ�ϴ� ���̾�α�

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
