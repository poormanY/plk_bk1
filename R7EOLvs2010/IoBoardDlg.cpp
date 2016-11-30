// IoBoardDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "R7EOLvs2010.h"
#include "IoBoardDlg.h"
#include "afxdialogex.h"
#include "y_Color.h"
#include "y_Debugging.h"
#include "y_wm_user.h"

#include "y_LogManage.h"
#include "SettingDlg.h"

// IoBoardDlg ��ȭ �����Դϴ�.
static CIoBoardMgt *m_IoBoard = NULL;		// IO Board Ŭ����


IMPLEMENT_DYNAMIC(IoBoardDlg, CDialogEx)

IoBoardDlg::IoBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IoBoardDlg::IDD, pParent)
{

}

IoBoardDlg::~IoBoardDlg()
{
}

void IoBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUT0, m_cbutton_out0);
	DDX_Control(pDX, IDC_OUT1, m_cbutton_out1);
	DDX_Control(pDX, IDC_OUT2, m_cbutton_out2);
	DDX_Control(pDX, IDC_OUT3, m_cbutton_out3);
	DDX_Control(pDX, IDC_OUT4, m_cbutton_out4);
	DDX_Control(pDX, IDC_OUT5, m_cbutton_out5);
	DDX_Control(pDX, IDC_OUT6, m_cbutton_out6);
	DDX_Control(pDX, IDC_OUT7, m_cbutton_out7);
	DDX_Control(pDX, IDC_OUT8, m_cbutton_out8);
	DDX_Control(pDX, IDC_OUT9, m_cbutton_out9);
	DDX_Control(pDX, IDC_OUT10,m_cbutton_out10);
	DDX_Control(pDX, IDC_OUT11,m_cbutton_out11);
	DDX_Control(pDX, IDC_OUT12,m_cbutton_out12);
	DDX_Control(pDX, IDC_OUT13,m_cbutton_out13);
	DDX_Control(pDX, IDC_OUT14,m_cbutton_out14);
	DDX_Control(pDX, IDC_OUT15,m_cbutton_out15);

	DDX_Control(pDX, IDC_IN0, m_cbutton_in0);
	DDX_Control(pDX, IDC_IN1, m_cbutton_in1);
	DDX_Control(pDX, IDC_IN2, m_cbutton_in2);
	DDX_Control(pDX, IDC_IN3, m_cbutton_in3);
	DDX_Control(pDX, IDC_IN4, m_cbutton_in4);
	DDX_Control(pDX, IDC_IN5, m_cbutton_in5);
	DDX_Control(pDX, IDC_IN6, m_cbutton_in6);
	DDX_Control(pDX, IDC_IN7, m_cbutton_in7);
	DDX_Control(pDX, IDC_IN8, m_cbutton_in8);
	DDX_Control(pDX, IDC_IN9, m_cbutton_in9);
	DDX_Control(pDX, IDC_IN10,m_cbutton_in10);
	DDX_Control(pDX, IDC_IN11,m_cbutton_in11);
	DDX_Control(pDX, IDC_IN12,m_cbutton_in12);
	DDX_Control(pDX, IDC_IN13,m_cbutton_in13);
	DDX_Control(pDX, IDC_IN14,m_cbutton_in14);
	DDX_Control(pDX, IDC_IN15,m_cbutton_in15);

	DDX_Control(pDX, IDC_BUTTON_IO_CONNECT, m_cbutton_io_connect);
	DDX_Control(pDX, IDOK, m_cbtmbtn_io_close);
	DDX_Control(pDX, IDC_EDIT_IO_PORT, m_edit_io_port);
	DDX_Control(pDX, IDC_EDIT_IO_BD_NAME, m_edit_io_bd_name);
}


BEGIN_MESSAGE_MAP(IoBoardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(_WM_IO_THREAD_UPDATE_IN, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) OnIoThreadMsgUpdate_IN)
	ON_MESSAGE(_WM_IO_THREAD_UPDATE_OUT, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) OnIoThreadMsgUpdate_OUT)
	ON_MESSAGE(_WM_IO_THREAD_UPDATE_END, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) OnIoThreadMsgUpdate_END)

	ON_BN_CLICKED(IDC_OUT0, &IoBoardDlg::OnBnClickedOut0)
	ON_BN_CLICKED(IDC_OUT1, &IoBoardDlg::OnBnClickedOut1)
	ON_BN_CLICKED(IDC_OUT2, &IoBoardDlg::OnBnClickedOut2)
	ON_BN_CLICKED(IDC_OUT3, &IoBoardDlg::OnBnClickedOut3)
	ON_BN_CLICKED(IDC_OUT4, &IoBoardDlg::OnBnClickedOut4)
	ON_BN_CLICKED(IDC_OUT5, &IoBoardDlg::OnBnClickedOut5)
	ON_BN_CLICKED(IDC_OUT6, &IoBoardDlg::OnBnClickedOut6)
	ON_BN_CLICKED(IDC_OUT7, &IoBoardDlg::OnBnClickedOut7)
	ON_BN_CLICKED(IDC_OUT8, &IoBoardDlg::OnBnClickedOut8)
	ON_BN_CLICKED(IDC_OUT9, &IoBoardDlg::OnBnClickedOut9)
	ON_BN_CLICKED(IDC_OUT10, &IoBoardDlg::OnBnClickedOut10)
	ON_BN_CLICKED(IDC_OUT11, &IoBoardDlg::OnBnClickedOut11)
	ON_BN_CLICKED(IDC_OUT12, &IoBoardDlg::OnBnClickedOut12)
	ON_BN_CLICKED(IDC_OUT13, &IoBoardDlg::OnBnClickedOut13)
	ON_BN_CLICKED(IDC_OUT14, &IoBoardDlg::OnBnClickedOut14)
	ON_BN_CLICKED(IDC_OUT15, &IoBoardDlg::OnBnClickedOut15)

	ON_BN_CLICKED(IDC_IN0, &IoBoardDlg::OnBnClickedIn0)
	ON_BN_CLICKED(IDC_IN1, &IoBoardDlg::OnBnClickedIn1)
	ON_BN_CLICKED(IDC_IN2, &IoBoardDlg::OnBnClickedIn2)
	ON_BN_CLICKED(IDC_IN3, &IoBoardDlg::OnBnClickedIn3)
	ON_BN_CLICKED(IDC_IN4, &IoBoardDlg::OnBnClickedIn4)
	ON_BN_CLICKED(IDC_IN5, &IoBoardDlg::OnBnClickedIn5)
	ON_BN_CLICKED(IDC_IN6, &IoBoardDlg::OnBnClickedIn6)
	ON_BN_CLICKED(IDC_IN7, &IoBoardDlg::OnBnClickedIn7)
	ON_BN_CLICKED(IDC_IN8, &IoBoardDlg::OnBnClickedIn8)
	ON_BN_CLICKED(IDC_IN9, &IoBoardDlg::OnBnClickedIn9)
	ON_BN_CLICKED(IDC_IN10, &IoBoardDlg::OnBnClickedIn10)
	ON_BN_CLICKED(IDC_IN11, &IoBoardDlg::OnBnClickedIn11)
	ON_BN_CLICKED(IDC_IN12, &IoBoardDlg::OnBnClickedIn12)
	ON_BN_CLICKED(IDC_IN13, &IoBoardDlg::OnBnClickedIn13)
	ON_BN_CLICKED(IDC_IN14, &IoBoardDlg::OnBnClickedIn14)
	ON_BN_CLICKED(IDC_IN15, &IoBoardDlg::OnBnClickedIn15)

	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_IO_CONNECT, &IoBoardDlg::OnBnClickedButtonIoConnect)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// IoBoardDlg �޽��� ó�����Դϴ�.


BOOL IoBoardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	// ���� �ʱ�ȭ
	m_nBtnConnect = 0; // ���� ���� (1:Connect, 0:Not Connect)
	uInPort  = 0xFFFF;	// IO Inport Data
	uOutPort = 0x0000;	// IO Outport Data
	m_bThreadStatus_Run = 0;

	// Ÿ��Ʋ ����
	// ���� ��Ʈ ����
	CFont titleFont;
	titleFont.CreateFont( 14, // nHeight 
						   0, // nWidth 
						   0,  // nEscapement 
						   0,  // nOrientation 
						   1,  // nWeight 
						   0,  // bItalic 
						   0,  // bUnderline 
						   0,  // cStrikeOut 
						   0,  // nCharSet 
						   OUT_DEFAULT_PRECIS,          // nOutPrecision 
						   0,                           // nClipPrecision 
						   DEFAULT_QUALITY,             // nQuality
						   DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
						   _T("����") ); // lpszFacename 
	GetDlgItem( IDC_STATIC_IO_BD_TITLE )->SetFont( &titleFont );
	titleFont.Detach();

	// ��ư ��Ų ������
	// LoadBitmap(������ ������(U), ������ ��(D), ��Ŀ���� ������(F), ��Ȱ��ȭ(X));
	// (ex.  m_btn.LoadBitmaps(IDB_BTN_U, IDB_BTN_D, IDB_BTN_F, IDB_BTN_X) )
	m_cbtmbtn_io_close.LoadBitmaps(IDB_BITMAP_CLOSE_F, IDB_BITMAP_CLOSE, IDB_BITMAP_CLOSE_F, IDB_BITMAP_CLOSE_X);
	m_cbtmbtn_io_close.SizeToContent();	

	m_cbutton_io_connect.LoadBitmaps(IDB_BITMAP_START_F, IDB_BITMAP_START, IDB_BITMAP_START_F, IDB_BITMAP_START_X);
	m_cbutton_io_connect.SizeToContent();

	// ����Ʈ �ڽ� ���� �� �ʱ�ȭ
	m_edit_io_port.SetTextString(_T("Not Connected"));
	m_edit_io_port.SetBgColor(BLACK);
	m_edit_io_port.SetTextColor(WHITE);

	m_edit_io_bd_name.SetTextString(_T(""));
	m_edit_io_bd_name.SetTextFormat(DT_CENTER | DT_VCENTER);	// �¿�/���� ����
	m_edit_io_bd_name.SetBgColor(BLACK);
	m_edit_io_bd_name.SetTextColor(WHITE);

	// ��ư ���� �� �ʱ�ȭ
	m_cbutton_out0.SetTextString(_T("OUT 0"));	// ����
	CButtonClickedOn(&m_cbutton_out0, 0);		// chk = 1, ��ư ����
	m_cbutton_out1.SetTextString(_T("OUT 1"));
	CButtonClickedOn(&m_cbutton_out1, 0);
	m_cbutton_out2.SetTextString(_T("OUT 2"));
	CButtonClickedOn(&m_cbutton_out2, 0);
	m_cbutton_out3.SetTextString(_T("OUT 3"));
	CButtonClickedOn(&m_cbutton_out3, 0);
	m_cbutton_out4.SetTextString(_T("OUT 4"));
	CButtonClickedOn(&m_cbutton_out4, 0);
	m_cbutton_out5.SetTextString(_T("OUT 5"));
	CButtonClickedOn(&m_cbutton_out5, 0);
	m_cbutton_out6.SetTextString(_T("OUT 6"));
	CButtonClickedOn(&m_cbutton_out6, 0);
	m_cbutton_out7.SetTextString(_T("OUT 7"));
	CButtonClickedOn(&m_cbutton_out7, 0);
	m_cbutton_out8.SetTextString(_T("OUT 8"));
	CButtonClickedOn(&m_cbutton_out8, 0);
	m_cbutton_out9.SetTextString(_T("OUT 9"));
	CButtonClickedOn(&m_cbutton_out9, 0);
	m_cbutton_out10.SetTextString(_T("OUT 10"));
	CButtonClickedOn(&m_cbutton_out10, 0);
	m_cbutton_out11.SetTextString(_T("OUT 11"));
	CButtonClickedOn(&m_cbutton_out11, 0);
	m_cbutton_out12.SetTextString(_T("OUT 12"));
	CButtonClickedOn(&m_cbutton_out12, 0);
	m_cbutton_out13.SetTextString(_T("OUT 13"));
	CButtonClickedOn(&m_cbutton_out13, 0);
	m_cbutton_out14.SetTextString(_T("OUT 14"));
	CButtonClickedOn(&m_cbutton_out14, 0);
	m_cbutton_out15.SetTextString(_T("OUT 15"));
	CButtonClickedOn(&m_cbutton_out15, 0);

	m_cbutton_in0.SetTextString(_T("IN 0"));	// ����
	CButtonClickedOn(&m_cbutton_in0, 0);		// chk = 1, ��ư ����
	m_cbutton_in1.SetTextString(_T("IN 1"));
	CButtonClickedOn(&m_cbutton_in1, 0);
	m_cbutton_in2.SetTextString(_T("IN 2"));
	CButtonClickedOn(&m_cbutton_in2, 0);
	m_cbutton_in3.SetTextString(_T("IN 3"));
	CButtonClickedOn(&m_cbutton_in3, 0);
	m_cbutton_in4.SetTextString(_T("IN 4"));
	CButtonClickedOn(&m_cbutton_in4, 0);
	m_cbutton_in5.SetTextString(_T("IN 5"));
	CButtonClickedOn(&m_cbutton_in5, 0);
	m_cbutton_in6.SetTextString(_T("IN 6"));
	CButtonClickedOn(&m_cbutton_in6, 0);
	m_cbutton_in7.SetTextString(_T("IN 7"));
	CButtonClickedOn(&m_cbutton_in7, 0);
	m_cbutton_in8.SetTextString(_T("IN 8"));
	CButtonClickedOn(&m_cbutton_in8, 0);
	m_cbutton_in9.SetTextString(_T("IN 9"));
	CButtonClickedOn(&m_cbutton_in9, 0);
	m_cbutton_in10.SetTextString(_T("IN 10"));
	CButtonClickedOn(&m_cbutton_in10, 0);
	m_cbutton_in11.SetTextString(_T("IN 11"));
	CButtonClickedOn(&m_cbutton_in11, 0);
	m_cbutton_in12.SetTextString(_T("IN 12"));
	CButtonClickedOn(&m_cbutton_in12, 0);
	m_cbutton_in13.SetTextString(_T("IN 13"));
	CButtonClickedOn(&m_cbutton_in13, 0);
	m_cbutton_in14.SetTextString(_T("IN 14"));
	CButtonClickedOn(&m_cbutton_in14, 0);
	m_cbutton_in15.SetTextString(_T("IN 15"));
	CButtonClickedOn(&m_cbutton_in15, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void IoBoardDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

}

void IoBoardDlg::CButtonClickedOn(CEditBox *Btn, int On)
{
	if ( On == 1 )
	{
		Btn->SetTextColor(BLACK);
		Btn->SetBgColor(GREEN);
	}
	else
	{
		Btn->SetTextColor(WHITE);
		Btn->SetBgColor(RED);
	}
	Btn->SetTextFormat(DT_CENTER | DT_VCENTER);	// �¿�/���� ����
	//Btn->PostMessageW(_WM_THREAD_UPDATE);
}



void IoBoardDlg::OnBnClickedOut0()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT0); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out0, chk);
m_cbutton_out0.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut1()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT1); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out1, chk);
m_cbutton_out1.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut2()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT2); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out2, chk);
m_cbutton_out2.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut3()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT3); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out3, chk);
m_cbutton_out3.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut4()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT4); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out4, chk);
m_cbutton_out4.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut5()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT5); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out5, chk);
m_cbutton_out5.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut6()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT6); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out6, chk);
m_cbutton_out6.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut7()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT7); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out7, chk);
m_cbutton_out7.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut8()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT8); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out8, chk);
m_cbutton_out8.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut9()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT9); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out9, chk);
m_cbutton_out9.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut10()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT10); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out10, chk);
m_cbutton_out10.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut11()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT11); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out11, chk);
m_cbutton_out11.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut12()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT12); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out12, chk);
m_cbutton_out12.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut13()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT13); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out13, chk);
m_cbutton_out13.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut14()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT14); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out14, chk);
m_cbutton_out14.PostMessageW(_WM_THREAD_UPDATE);
}
void IoBoardDlg::OnBnClickedOut15()
{
BOOL chk = IsDlgButtonChecked(IDC_OUT15); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_out15, chk);
m_cbutton_out15.PostMessageW(_WM_THREAD_UPDATE);
}

void IoBoardDlg::OnBnClickedIn0()
{
BOOL chk = IsDlgButtonChecked(IDC_IN0); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in0, chk);
}
void IoBoardDlg::OnBnClickedIn1()
{
BOOL chk = IsDlgButtonChecked(IDC_IN1); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in1, chk);
}
void IoBoardDlg::OnBnClickedIn2()
{
BOOL chk = IsDlgButtonChecked(IDC_IN2); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in2, chk);
}
void IoBoardDlg::OnBnClickedIn3()
{
BOOL chk = IsDlgButtonChecked(IDC_IN3); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in3, chk);
}
void IoBoardDlg::OnBnClickedIn4()
{
BOOL chk = IsDlgButtonChecked(IDC_IN4); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in4, chk);
}
void IoBoardDlg::OnBnClickedIn5()
{
BOOL chk = IsDlgButtonChecked(IDC_IN5); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in5, chk);
}
void IoBoardDlg::OnBnClickedIn6()
{
BOOL chk = IsDlgButtonChecked(IDC_IN6); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in6, chk);
}
void IoBoardDlg::OnBnClickedIn7()
{
BOOL chk = IsDlgButtonChecked(IDC_IN7); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in7, chk);
}
void IoBoardDlg::OnBnClickedIn8()
{
BOOL chk = IsDlgButtonChecked(IDC_IN8); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in8, chk);
}
void IoBoardDlg::OnBnClickedIn9()
{
BOOL chk = IsDlgButtonChecked(IDC_IN9); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in9, chk);
}
void IoBoardDlg::OnBnClickedIn10()
{
BOOL chk = IsDlgButtonChecked(IDC_IN10); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in10, chk);
}
void IoBoardDlg::OnBnClickedIn11()
{
BOOL chk = IsDlgButtonChecked(IDC_IN11); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in11, chk);
}
void IoBoardDlg::OnBnClickedIn12()
{
BOOL chk = IsDlgButtonChecked(IDC_IN12); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in12, chk);
}
void IoBoardDlg::OnBnClickedIn13()
{
BOOL chk = IsDlgButtonChecked(IDC_IN13); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in13, chk);
}
void IoBoardDlg::OnBnClickedIn14()
{
BOOL chk = IsDlgButtonChecked(IDC_IN14); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in14, chk);
}
void IoBoardDlg::OnBnClickedIn15()
{
BOOL chk = IsDlgButtonChecked(IDC_IN15); // üũ �Ǿ��ִ��� �˾ƺ���
CButtonClickedOn(&m_cbutton_in15, chk);
}

HBRUSH IoBoardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	switch(nCtlColor)
    {
        // �б� ���� ��Ʈ��
        case CTLCOLOR_STATIC:
        {
			pDC->SetTextColor(GREEN);
			pDC->SetBkColor(BLACK);
        }
        break;
    }

	return hbr;
}

void IoBoardDlg::DrawDoubleBuffering(void)
{
	CDC *pDC = GetDC();		// ���� DC ���
	CRect rect;
	GetClientRect(rect);	// ���� â ������ ���

	CDC MemDC;				// �޸� DC
	CBitmap *pOldBitmap;	// �޸� DC�� ��Ʈ��
	CBitmap bmp;			// ���� DC ������ ��Ʈ��

	MemDC.CreateCompatibleDC(pDC);									// �޸� DC�� ���� DC�� ���� ��ġ
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());	// ��Ʈ�ʰ� ���� DC�� ���� ��ġ 
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);				// �޸� DC�� ��Ʈ�� ����
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);		// ���� ���
																	// PATCOPY(����), BLACKNESS(����), WHITENESS(���), DSTINVERT(�������)

	// �޸� DC�� �׸���
	m_DrawIOBD->Draw_Line(&MemDC, 0, 70, rect.Width(), 70, RED);
    
	// �޸� DC�� ���� DC�� ����
	pDC->BitBlt(0, 0, rect.Width(),rect.Height(), &MemDC, 0,0,SRCCOPY);

	// ���� �޸� �� ��Ʈ�� ����
	MemDC.SelectObject(pOldBitmap);
    MemDC.DeleteDC();
}

// SerialDlg �޽��� ó�����Դϴ�.
BOOL IoBoardDlg::OpenIoBoard()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_IoBoard = new CIoBoardMgt;
	CString strIoBdProduct;

	// ��Ʈ �ҷ�����
	CString strIoBdCom;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strIoBdCom = pEolSetting->ReadSetting(COM_IO);
	delete pEolSetting;
    pEolSetting = NULL;

	char *pbIoBdCom = new char[strIoBdCom.GetLength()+1];
	strcpy(pbIoBdCom, CT2A(strIoBdCom));
	pbIoBdCom[strIoBdCom.GetLength()] = '\0';
	
	
    if (m_IoBoard == NULL)
    {
        return false;
    }

	if (m_IoBoard->Open(pbIoBdCom) == false)
    {
        dp("[%s] Open Fail!\n",pbIoBdCom);
        return false;
    }
		

	strIoBdProduct = _T("KM ");
    if (m_IoBoard->TransferMsg("$01GA001\r") == false)
    {
        dp("[%s] IO Board communication error!!\n", pbIoBdCom);
        return false;
    }
	else
	{
		strIoBdProduct += (m_IoBoard->GetMsg()+9);
	}

	strIoBdProduct += _T(" Ver ");
    if (strcmp(m_IoBoard->GetMsg()+9, "6050") != 0)
    {
        dp("[%s] IO Board model %s error!\n",pbIoBdCom, m_IoBoard->GetMsg()+9);
        return false;
    }
	else
	{
		strIoBdProduct += (m_IoBoard->GetMsg()+9);
	}

	// IO Board �𵨸�, ��ǰ��, ver ǥ��
	m_edit_io_bd_name.SetTextString(strIoBdProduct);
	m_edit_io_bd_name.PostMessageW(_WM_THREAD_UPDATE);


	
	delete pbIoBdCom;
	pbIoBdCom= NULL;

	return true;
}

BOOL IoBoardDlg::CloseIoBoard()
{
	if (m_IoBoard == NULL)
    {
        return false;
    }

	delete m_IoBoard;
    m_IoBoard = NULL;
	dp("IO Board Close\n");

	return true;
}


void IoBoardDlg::OnBnClickedButtonIoConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if ( m_nBtnConnect == 0 )
	{
		OnBnClickedButtonIoConnect_Start();

	}
	else
	{
		OnBnClickedButtonIoConnect_End();
	}

}

void IoBoardDlg::OnBnClickedButtonIoConnect_Start()
{
	GetDlgItem(IDOK)->EnableWindow(FALSE);	// Close ��Ȱ��ȭ
	GetDlgItem(IDC_BUTTON_IO_CONNECT)->EnableWindow(FALSE); // Connect ��ư ��Ȱ��ȭ
	m_cbutton_io_connect.LoadBitmaps(IDB_BITMAP_STOP_F, IDB_BITMAP_STOP, IDB_BITMAP_STOP_F, IDB_BITMAP_STOP_X);
	m_cbutton_io_connect.SizeToContent();

	m_hThread_IoBoard = NULL;
	// ��Ʈ �޺��ڽ� �ʱ�ȭ
	if ( OpenIoBoard() == TRUE )
	{
		dp("IO Board Open Success!\n");

		m_nBtnConnect = 1;

		// IO Board ���� ����
		m_edit_io_port.SetTextString(_T("Connected"));
		m_edit_io_port.PostMessageW(_WM_THREAD_UPDATE);

		//--> ��Ʈ ���� ������ ����
		DWORD dwThreadID;
		m_hThread_IoBoard = NULL;
		m_hThread_IoBoard = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Thread_IoBoard_Running, this, 0, &dwThreadID);
	}
	else
	{
		dp("IO Board Open Fail!\n");

		OnBnClickedButtonIoConnect_End();
	}

	UpdateData(FALSE);

	GetDlgItem(IDC_BUTTON_IO_CONNECT)->EnableWindow(TRUE); // Connect ��ư Ȱ��ȭ
}

void IoBoardDlg::OnBnClickedButtonIoConnect_End()
{
	m_nBtnConnect = 0;

	GetDlgItem(IDC_BUTTON_IO_CONNECT)->EnableWindow(FALSE); // Connect ��ư ��Ȱ��ȭ
	m_cbutton_io_connect.LoadBitmaps(IDB_BITMAP_START_F, IDB_BITMAP_START, IDB_BITMAP_START_F, IDB_BITMAP_START_X);
	m_cbutton_io_connect.SizeToContent();

	// IO Board �𵨸�, ��ǰ��, ver ǥ��
	m_edit_io_bd_name.SetTextString(_T(""));
	m_edit_io_bd_name.PostMessageW(_WM_THREAD_UPDATE);
	// IO Board ���� ����
	m_edit_io_port.SetTextString(_T("Not Connected"));
	m_edit_io_port.PostMessageW(_WM_THREAD_UPDATE);

	UpdateData(FALSE);

	// Thread �� ���� ������ ��ٸ���.
	while ( m_bThreadStatus_Run == 1 )
	{
		dp("m_bThreadStatus_Run : %d\n", m_bThreadStatus_Run);
		Sleep(200);
	}

	CloseIoBoard();
	GetDlgItem(IDOK)->EnableWindow(TRUE);	// Close Ȱ��ȭ
	GetDlgItem(IDC_BUTTON_IO_CONNECT)->EnableWindow(TRUE); // Connect ��ư Ȱ��ȭ
}



UINT IoBoardDlg::Thread_IoBoard_Running(IoBoardDlg* pDlg)
{
	U16 uOldInPort = 0xFFFF;
	U16 uOldOutPort = 0x0000;

	dp("- IO Board Thread Open -\n");

	pDlg->m_bThreadStatus_Run = 1;
	////////////////////////////////////////////
	// �Է� ��Ʈ
	pDlg->uInPort = m_IoBoard->GetInPort();
	uOldInPort = pDlg->uInPort;
	pDlg->PostMessageW(_WM_IO_THREAD_UPDATE_IN);
	dp("uInPort <--- %4X\n", pDlg->uInPort);
	
	////////////////////////////////////////////
	// ��� ��Ʈ
	pDlg->PostMessageW(_WM_IO_THREAD_UPDATE_OUT);
	uOldOutPort = pDlg->uOutPort;
	m_IoBoard->PutOutPort(pDlg->uOutPort);
	dp("uOutPort ---> %4X\n", pDlg->uOutPort);
	
	while(pDlg->m_nBtnConnect == 1)
	{
		////////////////////////////////////////////
		// �Է� ��Ʈ
		pDlg->uInPort = m_IoBoard->GetInPort();
		dp("uInPort : %4X\n", pDlg->uInPort);
		// �Է� ��Ʈ�� ��ȭ�� ���� ��쿡��, ���̾�α׸� ����
		if ( uOldInPort != pDlg->uInPort )
		{
			uOldInPort = pDlg->uInPort;
			pDlg->PostMessageW(_WM_IO_THREAD_UPDATE_IN);
			dp("uInPort <--- %4X\n", pDlg->uInPort);
		}
		
		////////////////////////////////////////////
		// ��� ��Ʈ
		pDlg->PostMessageW(_WM_IO_THREAD_UPDATE_OUT);
		dp("uOutPort : %4X\n", pDlg->uOutPort);
		// ��� ��Ʈ�� ��ȭ�� ���� ��쿡��, IO Board�� ������ �۽�
		if ( uOldOutPort != pDlg->uOutPort )
		{
			uOldOutPort = pDlg->uOutPort;
			m_IoBoard->PutOutPort(pDlg->uOutPort);
			dp("uOutPort ---> %4X\n", pDlg->uOutPort);
		}

		Sleep(200);
	}
	pDlg->m_bThreadStatus_Run = 0;
	pDlg->PostMessageW(_WM_IO_THREAD_UPDATE_END);
	dp("- IO Board Thread Close -\n");

	return true;
}

LRESULT IoBoardDlg::OnIoThreadMsgUpdate_IN(WPARAM a_wParam, LPARAM a_lParam)
{
	int nInputBit[16];
	int CHK_BIT = 0x0001;
	int nIdxBit;

	UpdateData(TRUE);

	for ( nIdxBit = 0; nIdxBit < 16; nIdxBit++ )
	{
		nInputBit[nIdxBit] = (uInPort & CHK_BIT)? 1 : 0;
		CHK_BIT <<= 1;
	}
	CButtonClickedOn( &m_cbutton_in0, nInputBit[0] );
	m_cbutton_in0.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in1, nInputBit[1] );
	m_cbutton_in1.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in2, nInputBit[2] );
	m_cbutton_in2.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in3, nInputBit[3] );
	m_cbutton_in3.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in4, nInputBit[4] );
	m_cbutton_in4.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in5, nInputBit[5] );
	m_cbutton_in5.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in6, nInputBit[6] );
	m_cbutton_in6.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in7, nInputBit[7] );
	m_cbutton_in7.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in8, nInputBit[8] );
	m_cbutton_in8.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in9, nInputBit[9] );
	m_cbutton_in9.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in10, nInputBit[10] );
	m_cbutton_in10.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in11, nInputBit[11] );
	m_cbutton_in11.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in12, nInputBit[12] );
	m_cbutton_in12.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in13, nInputBit[13] );
	m_cbutton_in13.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in14, nInputBit[14] );
	m_cbutton_in14.PostMessageW(_WM_THREAD_UPDATE);
	CButtonClickedOn( &m_cbutton_in15, nInputBit[15] );
	m_cbutton_in15.PostMessageW(_WM_THREAD_UPDATE);

    UpdateData(FALSE);

	return 0;
}

LRESULT IoBoardDlg::OnIoThreadMsgUpdate_OUT(WPARAM a_wParam, LPARAM a_lParam)
{
	unsigned short int uOut = 0x0000;
	unsigned short int OUT_BIT = 0x0001;

	UpdateData(TRUE);

	// üũ �Ǿ��ִ��� �˾ƺ���
	if(IsDlgButtonChecked(IDC_OUT0))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT1))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT2))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT3))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT4))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT5))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT6))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT7))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT8))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT9))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT10))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT11))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT12))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT13))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT14))	uOut |= OUT_BIT;	OUT_BIT<<=1;
	if(IsDlgButtonChecked(IDC_OUT15))	uOut |= OUT_BIT;	OUT_BIT<<=1;

	uOutPort = uOut;
	
	UpdateData(FALSE);

	return 0;
}

LRESULT IoBoardDlg::OnIoThreadMsgUpdate_END(WPARAM a_wParam, LPARAM a_lParam)
{
	UpdateData(TRUE);

	m_bThreadStatus_Run = 0;
	dp("[MSG END] m_bThreadStatus_Run : %d\n",m_bThreadStatus_Run);

	UpdateData(FALSE);

	return 0;
}

BOOL IoBoardDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect( rect, BLACK );
 
    return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
