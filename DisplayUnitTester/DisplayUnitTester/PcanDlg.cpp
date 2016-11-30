// PcanDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayUnitTester.h"
#include "PcanDlg.h"
#include "afxdialogex.h"
#include "JDEFINE.H"
#include "wm_user.h"

PcanDlg		*pPcanDlg = NULL;
extern UINT				PcanMainThread(LPVOID pParam);
extern TOF				tMainThreadStop;

// PcanDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(PcanDlg, CDialogEx)

PcanDlg::PcanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PcanDlg::IDD, pParent)
	, m_check_can_start(FALSE)
{

}

PcanDlg::~PcanDlg()
{
}

void PcanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CAN_START, m_check_can_start);
	DDX_Control(pDX, IDC_LIST_PCAN, m_list_pcan);
}


BEGIN_MESSAGE_MAP(PcanDlg, CDialogEx)

	ON_MESSAGE(_WM_PCAN_THREAD_START , (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM,LPARAM))OnThreadMsgStart ) // Thread Start msg
	ON_MESSAGE(_WM_PCAN_THREAD_END , (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM,LPARAM))OnThreadMsgEnd ) // Thread End msg
	ON_BN_CLICKED(IDC_CHECK_CAN_START, &PcanDlg::OnBnClickedCheckCanStart)
END_MESSAGE_MAP()


// PcanDlg 메시지 처리기입니다.
BOOL PcanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		
	m_list_pcan.InsertColumn(0, _T("Number"), LVCFMT_CENTER  , 50);
	m_list_pcan.InsertColumn(1, _T("CAN-ID"), LVCFMT_CENTER  , 80);
	m_list_pcan.InsertColumn(2, _T("DLC"), LVCFMT_CENTER  , 50);
	m_list_pcan.InsertColumn(3, _T("Type")  , LVCFMT_CENTER, 80);
    m_list_pcan.InsertColumn(4, _T("Data")  , LVCFMT_CENTER, 150);
    m_list_pcan.InsertColumn(5, _T("Cycle Time")  , LVCFMT_CENTER, 80);
    m_list_pcan.InsertColumn(6, _T("Count")    , LVCFMT_CENTER,  90);
    m_list_pcan.SetExtendedStyle(m_list_pcan.GetExtendedStyle()|LVS_EX_GRIDLINES);

	int itemNum = 0;
	CString strNum;	
	for ( itemNum = 0; itemNum < 16; itemNum++ )
	{
		strNum.Format(_T("%d"),itemNum+1);
		m_list_pcan.InsertItem(itemNum, strNum);
	}
	
	pPcanDlg = this;

	return true;
}

void PcanDlg::OnThreadMsgStart(WPARAM a_wParam, LPARAM a_lParam)
{
	tMainThreadStop = false;
	m_pThreadPcanMain = AfxBeginThread(PcanMainThread, this);
}

void PcanDlg::OnThreadMsgEnd(WPARAM a_wParam, LPARAM a_lParam)
{
	tMainThreadStop = true;
}

void PcanDlg::OnBnClickedCheckCanStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if (m_check_can_start == TRUE) {
		SetDlgItemText(IDC_CHECK_CAN_START, _T("CAN CLOSE"));
		PostMessage(_WM_PCAN_THREAD_START);
	}
	else {
		SetDlgItemText(IDC_CHECK_CAN_START, _T("CAN START"));
		PostMessage(_WM_PCAN_THREAD_END);
	}
}
