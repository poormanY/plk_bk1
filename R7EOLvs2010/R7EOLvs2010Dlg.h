
// R7EOLvs2010Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "y_EditBox.h"
#include "y_LogManage.h"
#include "y_SerialComm.h"
#include "y_Draw.h"
#include "y_ExpressImgDlg.h"
#include "y_LanguagePack.h"

#include "afxcmn.h"

#define PATH_EOL_LOG _T("EOL_SETTING.ini")

// CR7EOLvs2010Dlg ��ȭ ����
class CR7EOLvs2010Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CR7EOLvs2010Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_R7EOLVS2010_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON			m_hIcon;
	CSerialComm		m_ComuPort;
	CEditBox		m_edit_draw_num;
	CEditBox		m_edit_test_time;
	CEditBox		m_edit_product_name;
	CEditBox		m_edit_product_line;

	CDraw			DrawMain;

	// Serial Comm Function
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);
	// Main Dialog Init <- Msg from other Dialog
	afx_msg long MsgOnInitDialog(WPARAM wParam, LPARAM lParam);
	// CListCtrl Row/Column �� ���� �� ���ڻ� ����
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	// UI ���� �Լ�
	afx_msg long R7_EOL_Status_Ready(WPARAM wParam, LPARAM lParam);
	void R7_EOL_Status_Running(void);


	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CExpressImgDlg *pImgDlg; // ��޸��� ���̾�α�

	CLanguagePack	EOLLanguage;// ��� ����
	int m_language;
	
	CLogManage		EOLSaveLog;	// �׽�Ʈ �α� ���
	CString			strTesterNum, strProductName, strProductLine, strTotalTest;
	CString			strLogPath, strMcuVer, strSwVer;
	BOOL			bEnStep_McuVer, bEnStep_SwVer, bEnStep_SerialNum, bEnStep_IoBoard, bEnStep_Screw, bEnStep_Bar1, bEnStep_Bar2;
	BOOL			bEnStep_Accleration, bEnStep_SpeedPulse, bEnStep_DTC_Clear, bEnStep_LDW_Speed, bEnStep_FCW_Speed;
	BOOL			bEnStep_LDW_Detect, bEnStep_LDW_Warn_L, bEnStep_LDW_Warn_R, bEnStep_FCW_Warn, bEnStep_FCW_Warn2, bEnStep_FCW_Warn3, bEnStep_FCDA_Warn;
	BOOL			bEnStep_LDW_WarnL_WinkL, bEnStep_LDW_WarnL_WinkR, bEnStep_LDW_WarnL_WinkLR;
	BOOL			bEnStep_LDW_WarnR_WinkL, bEnStep_LDW_WarnR_WinkR, bEnStep_LDW_WarnR_WinkLR;
	int m_nVehicleLdwSpd;
	int m_nVehicleFcwSpd;
	int m_nAlarmDelay;

	CEditBox		m_edit_pass_num, m_edit_fail_num, m_edit_total_num, m_edit_pass_percent, m_edit_total_test;
	// ADAS ���� ���̾�α׿� ǥ��
	CEditBox m_edit_in_speed;
	CEditBox m_edit_in_wink_l;
	CEditBox m_edit_in_wink_r;
	CEditBox m_edit_out_ldw_detetc_l;
	CEditBox m_edit_out_m_ldw_detect_r;
	CEditBox m_edit_out_ldw_warn_l;
	CEditBox m_edit_out_ldw_warn_r;
	CEditBox m_edit_out_hmw;
	CEditBox m_edit_out_fcw;
	CComboBox		m_combo_tester;

	CEditBox		m_edit_notice;
	CEditBox		m_edit_notice2;

	afx_msg void OnBnClickedButtonStart();
	CButton m_cbutton_start;
	afx_msg void OnBnClickedButtonViewAvi();
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedButtonIoBd();
	afx_msg void OnBnClickedButtonScrew();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_list_test_process;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	COLORREF CStringToRGB(CString strColor);//CString -> RGB
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonBarcode();
	CButton m_button_close;
};
