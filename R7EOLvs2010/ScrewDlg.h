#pragma once


// ScrewDlg ��ȭ �����Դϴ�.

class ScrewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScrewDlg)

public:
	ScrewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ScrewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SCREW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
