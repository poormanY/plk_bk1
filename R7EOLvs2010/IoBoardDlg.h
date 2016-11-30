#pragma once
#include "afxwin.h"
#include "afxext.h"

#include "y_EditBox.h"
#include "y_Draw.h"
#include "y_Color.h"
#include "y_IoBoardMgt.h"
#include "y_SerialComm.h"

// IoBoardDlg ��ȭ �����Դϴ�.

class IoBoardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IoBoardDlg)

public:
	IoBoardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~IoBoardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_IO_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	void IoBoardDlg::CButtonClickedOn(CEditBox *Btn, int On);	// ��ư ���� ���¿� ���� ��ȭ (On = 1, ����)
	void IoBoardDlg::DrawDoubleBuffering(void);					// ������۸� �۾� �Լ�
	BOOL IoBoardDlg::OpenIoBoard();								// IO Board Open
	BOOL IoBoardDlg::CloseIoBoard();							// IO Board Close

	CBitmap  m_Bitmap;	// ���� ���۸��� ���� ��Ʈ��

	HANDLE m_hThread_IoBoard;								// Thread Handler
	static UINT Thread_IoBoard_Running(IoBoardDlg* pDlg);	// Thread�Լ�
	BOOL m_bThreadStatus_Run;								// Thread�Լ� ���� ���� (0:����, 1:������)

	CDraw *m_DrawIOBD;			// Draw Ŭ����
	CSerialComm *m_SerialCom;	// Serial Comm Ŭ����
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnIoThreadMsgUpdate_IN(WPARAM a_wParam, LPARAM a_lParam);
	afx_msg LRESULT OnIoThreadMsgUpdate_OUT(WPARAM a_wParam, LPARAM a_lParam);
	afx_msg LRESULT OnIoThreadMsgUpdate_END(WPARAM a_wParam, LPARAM a_lParam);

	int m_nBtnConnect;			 // Connect ����
	unsigned short int uInPort;	 // IO Board �Է� ��Ʈ �� (bd -> pc)
	unsigned short int uOutPort; // IO Board ��� ��Ʈ �� (pc -> bd)

	unsigned short int GetOutPort(void); // Out Port ����� 16��Ʈ �� ���ϱ�

	CEditBox m_cbutton_out0;
	CEditBox m_cbutton_out1;
	CEditBox m_cbutton_out2;
	CEditBox m_cbutton_out3;
	CEditBox m_cbutton_out4;
	CEditBox m_cbutton_out5;
	CEditBox m_cbutton_out6;
	CEditBox m_cbutton_out7;
	CEditBox m_cbutton_out8;
	CEditBox m_cbutton_out9;
	CEditBox m_cbutton_out10;
	CEditBox m_cbutton_out11;
	CEditBox m_cbutton_out12;
	CEditBox m_cbutton_out13;
	CEditBox m_cbutton_out14;
	CEditBox m_cbutton_out15;

	CEditBox m_cbutton_in0;
	CEditBox m_cbutton_in1;
	CEditBox m_cbutton_in2;
	CEditBox m_cbutton_in3;
	CEditBox m_cbutton_in4;
	CEditBox m_cbutton_in5;
	CEditBox m_cbutton_in6;
	CEditBox m_cbutton_in7;
	CEditBox m_cbutton_in8;
	CEditBox m_cbutton_in9;
	CEditBox m_cbutton_in10;
	CEditBox m_cbutton_in11;
	CEditBox m_cbutton_in12;
	CEditBox m_cbutton_in13;
	CEditBox m_cbutton_in14;
	CEditBox m_cbutton_in15;

	afx_msg void OnBnClickedOut0();
	afx_msg void OnBnClickedOut1();
	afx_msg void OnBnClickedOut2();
	afx_msg void OnBnClickedOut3();
	afx_msg void OnBnClickedOut4();
	afx_msg void OnBnClickedOut5();
	afx_msg void OnBnClickedOut6();
	afx_msg void OnBnClickedOut7();
	afx_msg void OnBnClickedOut8();
	afx_msg void OnBnClickedOut9();
	afx_msg void OnBnClickedOut10();
	afx_msg void OnBnClickedOut11();
	afx_msg void OnBnClickedOut12();
	afx_msg void OnBnClickedOut13();
	afx_msg void OnBnClickedOut14();
	afx_msg void OnBnClickedOut15();

	afx_msg void OnBnClickedIn0();
	afx_msg void OnBnClickedIn1();
	afx_msg void OnBnClickedIn2();
	afx_msg void OnBnClickedIn3();
	afx_msg void OnBnClickedIn4();
	afx_msg void OnBnClickedIn5();
	afx_msg void OnBnClickedIn6();
	afx_msg void OnBnClickedIn7();
	afx_msg void OnBnClickedIn8();
	afx_msg void OnBnClickedIn9();
	afx_msg void OnBnClickedIn10();
	afx_msg void OnBnClickedIn11();
	afx_msg void OnBnClickedIn12();
	afx_msg void OnBnClickedIn13();
	afx_msg void OnBnClickedIn14();
	afx_msg void OnBnClickedIn15();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonIoConnect();
	void OnBnClickedButtonIoConnect_Start();
	void OnBnClickedButtonIoConnect_End();
	CBitmapButton m_cbutton_io_connect;
	CBitmapButton m_cbtmbtn_io_close;
	CEditBox m_edit_io_port;
	CEditBox m_edit_io_bd_name;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
