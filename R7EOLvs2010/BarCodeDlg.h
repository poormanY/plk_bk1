#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "y_EditBox.h"

// BarCodeDlg ��ȭ �����Դϴ�.

class BarCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BarCodeDlg)

public:
	BarCodeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~BarCodeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	void DrawDoubleBuffering(void);		// ������۸�

	void Barcode1Close();
	void Barcode2Close();
	BOOL OpenIoBoard();
	BOOL CloseIoBoard();
	BOOL Bar1ScanON();
	BOOL Bar1ScanOFF();
	BOOL Bar2ScanON();
	BOOL Bar2ScanOFF();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonBar1Open();
	afx_msg void OnBnClickedButtonBar2Open();
	CBitmapButton m_btn_bar1_open;
	CBitmapButton m_btn_bar2_open;
	CBitmapButton m_btn_close;
	CBitmapButton m_btn_save;
	CBitmapButton m_btn_load;
	CBitmapButton m_btn_bar1_clr;
	CBitmapButton m_btn_bar2_clr;
	afx_msg void OnBnClickedOk();
	CListCtrl m_list_bar1;
	CListCtrl m_list_bar2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CEditBox m_edit_bar1_port;
	CEditBox m_edit_bar2_port;
	CEditBox m_edit_bar1_connect;
	CEditBox m_edit_bar2_connect;
	afx_msg void OnBnClickedButtonBar1Clr();
	afx_msg void OnBnClickedButtonBar2Clr();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
