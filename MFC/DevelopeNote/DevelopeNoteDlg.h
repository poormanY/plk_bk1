
// DevelopeNoteDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CDevelopeNoteDlg ��ȭ ����
class CDevelopeNoteDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDevelopeNoteDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEVELOPENOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_edit_date;
	CComboBox m_combo_userName;
	afx_msg void OnCbnSelchangeCombo4();
	CEdit m_edit_userName;
	CComboBox m_combo_projectName;
	CEdit m_edit_projectName;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton1();

	void FileSave(CString filePath, CString fileContents);
	CString GetFileFolderPath(CString path);

	CEdit m_edit_data1;
	CEdit m_edit_data2;
	CEdit m_edit_data3;
	CEdit m_edit_data4;
	CEdit m_edit_data5;
	CEdit m_edit_data6;
	CEdit m_edit_data7;
	afx_msg void OnBnClickedButton2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
	CEdit m_edit_attach_fileName;
	CBitmapButton m_cbtn_hwnote;
	CDateTimeCtrl m_datetime_date;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
