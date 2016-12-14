
// DevelopeNoteDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DevelopeNote.h"
#include "DevelopeNoteDlg.h"
#include "afxdialogex.h"

#include "../Library/y_Color.h"
#include "y_LogManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLogManage		SaveLogManage;	// �׽�Ʈ �α� ���

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDevelopeNoteDlg ��ȭ ����




CDevelopeNoteDlg::CDevelopeNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevelopeNoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDevelopeNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO4, m_combo_userName);
	DDX_Control(pDX, IDC_EDIT2, m_edit_userName);
	DDX_Control(pDX, IDC_COMBO3, m_combo_projectName);
	DDX_Control(pDX, IDC_EDIT3, m_edit_projectName);
	DDX_Control(pDX, IDC_EDIT4, m_edit_data1);
	DDX_Control(pDX, IDC_EDIT5, m_edit_data2);
	DDX_Control(pDX, IDC_EDIT6, m_edit_data3);
	DDX_Control(pDX, IDC_EDIT7, m_edit_data4);
	DDX_Control(pDX, IDC_EDIT8, m_edit_data5);
	DDX_Control(pDX, IDC_EDIT9, m_edit_data6);
	DDX_Control(pDX, IDC_EDIT10, m_edit_data7);
	DDX_Control(pDX, IDC_EDIT11, m_edit_attach_fileName);
	DDX_Control(pDX, IDC_BUTTON3, m_cbtn_hwnote);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetime_date);
}

BEGIN_MESSAGE_MAP(CDevelopeNoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO4, &CDevelopeNoteDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDevelopeNoteDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &CDevelopeNoteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDevelopeNoteDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CDevelopeNoteDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &CDevelopeNoteDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDevelopeNoteDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDevelopeNoteDlg �޽��� ó����

BOOL CDevelopeNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SaveLogManage.SetFilePath(_T("DevelopeNote.ini"));

	// HW NOTE �̹��� �ΰ�
	m_cbtn_hwnote.LoadBitmaps(IDB_BMP_HWNOTE, IDB_BMP_HWNOTE, IDB_BMP_HWNOTE, IDB_BMP_HWNOTE);
    m_cbtn_hwnote.SizeToContent(); // �̹����� �°� ��ư ����� ����

	// ���� ��¥ ǥ��
	CTime   oTime;
	CString strTime;
	
	// ������Ʈ �̸� �޺� �ڽ�
	int nProjectNum = 0;
	CString strValue;
	CString strProjectNum, strProjectIdx, strProjectName;
	
	strProjectIdx = _T("Project0");
	while ( (strValue=SaveLogManage.ReadSetting(strProjectIdx)) != _T("") )
	{
		m_combo_projectName.AddString(strValue);

		nProjectNum++;
		strProjectNum.Format(_T("%d"), nProjectNum);
		strProjectIdx = _T("Project") + strProjectNum;
	}	
	//m_combo_projectName.SetCurSel(0);
	// ����� �޺� �ڽ�
	int nUserNum = 0;
	CString strUserNum, strUserIdx, strUserName;
	
	strUserIdx = _T("User0");
	while ( (strValue=SaveLogManage.ReadSetting(strUserIdx)) != _T("") )
	{
		m_combo_userName.AddString(strValue);

		nUserNum++;
		strUserNum.Format(_T("%d"), nUserNum);
		strUserIdx = _T("User") + strUserNum;
	}
	//m_combo_userName.SetCurSel(0);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CDevelopeNoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDevelopeNoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDevelopeNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CDevelopeNoteDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect( rect, SOFT_BLUE );
 
    return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CDevelopeNoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch(nCtlColor)
    {
        // �б� ���� ��Ʈ��
        case CTLCOLOR_STATIC:
        {
            pDC->SetTextColor(BLACK);
            pDC->SetBkColor(SOFT_BLUE);
        }
        break;
    }

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CDevelopeNoteDlg::OnCbnSelchangeCombo4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strUserName;
	int nIdx;

	nIdx = m_combo_userName.GetCurSel();
	m_combo_userName.GetLBText(nIdx, strUserName);

	m_edit_userName.SetWindowTextW(strUserName);
}


void CDevelopeNoteDlg::OnCbnSelchangeCombo3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strProjectName;
	int nIdx;

	nIdx = m_combo_projectName.GetCurSel();
	m_combo_projectName.GetLBText(nIdx, strProjectName);

	m_edit_projectName.SetWindowTextW(strProjectName);
}

// ���� ���� �Լ�
void CDevelopeNoteDlg::FileSave(CString filePath, CString fileContents)
{
    FILE *pf;
 
    pf = fopen((CStringA)filePath, "w");
    if (pf != NULL)
    {
        fprintf(pf, (CStringA)fileContents);
        fclose(pf);
    }
 
}

CString CDevelopeNoteDlg::GetFileFolderPath(CString path)
{
	int idx, len;
	
	len = path.GetLength();
	idx = path.ReverseFind(_T('\\'));
	path.Delete(idx+1,len-idx-1);

	return path;
}


void CDevelopeNoteDlg::OnBnClickedButton1()
{
	CString strFilePath, strProjectName, strDate, strUserName;
	int msgRes;
	CTime date;
	
	m_edit_projectName.GetWindowTextW(strProjectName);

	m_datetime_date.GetTime(date);
	strDate = date.Format("%Y%m%d");

	m_edit_userName.GetWindowTextW(strUserName);
	strFilePath = (strProjectName + _T("_") + strDate + _T("_") + strUserName);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� ����
    // ���� ���� �޺��ڽ��� ����� Ȯ���� ���͸� �����Ѵ�. (*.*, *.txt)
    // Ȯ���� ������ ù��° �κ��� �޺��ڽ��� ��µ� ���ڿ��� ����ϸ�,
    // �ι�° �κ��� ���� ���̾�α׿� ��µ� ���ϵ��� Ȯ���ڸ� ����Ѵ�.
    // ���ϴ� Ȯ���� ���͸� �Ʒ��� ���� " | " �����ڸ� �̿��Ͽ� �������� ����� �� ������
    // ���ڿ��� ������ �ݵ�� �����ڰ� ��õǾ�� �Ѵ�.
    //char name_filter[] = "All Files (*.*)|*.*|txt Files (*.txt)|*.txt|";
	CString name_filter = _T("All Files (*.*)|*.*|txt Files (*.txt)|*.txt|");
  
    // FALSE -> �����ȭ����
    // "txt" -> ����ڰ� Ȯ���� ���� ���ϸ� �Է������� �ڵ����� �߰��� Ȯ���ڸ��̴�.
    // ��, tipssoft ������ �Է��ϸ� tipssoft.txt��� �Է��ѰͰ� �����ϰ� �ϰ� ������ ����Ѵ�.
    // "*.txt" �����̸��� �Է��ϴ� ����Ʈ �ڽ��� ��µ� �⺻ ���ڿ��̴�. 
    // OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT -> ���� ��ȭ���ڿ� �߰������� ����� �Ӽ�
    // name_filter -> ���� ���� �޺��ڽ��� ����� ���������� ����ִ� �޸��� �ּ��̴�.
    CFileDialog ins_dlg(FALSE, _T("txt"), strFilePath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
                                                    OFN_NOCHANGEDIR, name_filter, NULL);
 
    // ���� ���� �޺��ڽ��� ������ ���͵� �߿��� 2��° �׸�(*.txt)�� �����Ѵ�.
    ins_dlg.m_ofn.nFilterIndex = 2;
  
    // ���̾�α׸� ����.

    if(ins_dlg.DoModal() == IDOK)
    {
        CDevelopeNoteDlg *fm;
        CString fp; // file path
        CString fc; // file contents
		CString fn; // file name
		CString ff; // file folder
		CString fcUnit, fcFileOriginPath, fcFileCopyPath, fcFileName;
		CString strMsg;
		CTime date;
                 
        fm = new CDevelopeNoteDlg;
        fp = ins_dlg.GetPathName(); // ���� ��θ� ����
		fn = ins_dlg.GetFileName(); // ���� �̸��� ����
		ff = GetFileFolderPath(fp); // ���� ��θ� ����

		// ���� ���� ����
		fc = _T("");		
		fc += _T("/////////////////////////////////////////////////\n");
		fc += _T("// ������Ʈ : ");
		m_edit_projectName.GetWindowTextW(fcUnit);
		fc += fcUnit;
		fc += _T("\n//   �ۼ��� : ");
		m_edit_userName.GetWindowTextW(fcUnit);
		fc += fcUnit;
		fc += _T("\n//     ��¥ : ");
		m_datetime_date.GetTime(date);
		fcUnit = date.Format("%Y%m%d");
		fc += fcUnit;
		fc += _T("\n/////////////////////////////////////////////////\n");

		fc += _T("<================== �ҷ� ���� ==================>\n");
		m_edit_data1.GetWindowTextW(fcUnit);
		fc += fcUnit;

		fc += _T("\n<================== ���� ���� ==================>\n");
		m_edit_data2.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== �䱸 ���� ==================>\n");
		m_edit_data3.GetWindowTextW(fcUnit);
		fc += fcUnit;

		fc += _T("\n<================== ���� ��� ==================>\n");
		m_edit_data4.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== ���� ��� ==================>\n");
		m_edit_data5.GetWindowTextW(fcUnit);
		fc += fcUnit;
				
		fc += _T("\n\n<================== �ذ� ��� ==================>\n");
		m_edit_data6.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== ÷�� ���� ==================>\n");
		m_edit_data7.GetWindowTextW(fcFileOriginPath);
		fc += fcFileOriginPath;
		// ÷�� ������ �ش� ��ο� ����
		m_edit_attach_fileName.GetWindowTextW(fcFileName);
		fcFileCopyPath = ff + fcFileName;
		BOOL bSuccess = CopyFile(fcFileOriginPath, fcFileCopyPath, TRUE);
		if ( !bSuccess )
		{
			msgRes = AfxMessageBox(_T("÷�� ������ �̹� ���� �մϴ�.\n����ðڽ��ϱ�?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
			if ( msgRes == IDOK )
			{
				bSuccess = CopyFile(fcFileOriginPath, fcFileCopyPath, FALSE);				
				if ( !bSuccess )
				{
					AfxMessageBox(_T("÷�� ���� ���翡 �����Ͽ����ϴ�."), MB_OK | MB_ICONSTOP);
				}				
			}
		}

        // ������ ���� ��ο� ����Ʈ �ڽ��� ������ �����Ѵ�.
        fm->FileSave(fp, fc);
        
        delete fm;
        fm = NULL;

		msgRes = AfxMessageBox(_T("�����Ͽ����ϴ�.\r\n���α׷��� �����Ͻðڽ��ϱ�?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
		if ( msgRes == IDOK )
		{
			CDialogEx::OnOK();
		}
    }
}


void CDevelopeNoteDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� ����
    // ���� ���� �޺��ڽ��� ����� Ȯ���� ���͸� �����Ѵ�. (*.*, *.txt)
    // Ȯ���� ������ ù��° �κ��� �޺��ڽ��� ��µ� ���ڿ��� ����ϸ�,
    // �ι�° �κ��� ���� ���̾�α׿� ��µ� ���ϵ��� Ȯ���ڸ� ����Ѵ�.
    // ���ϴ� Ȯ���� ���͸� �Ʒ��� ���� " | " �����ڸ� �̿��Ͽ� �������� ����� �� ������
    // ���ڿ��� ������ �ݵ�� �����ڰ� ��õǾ�� �Ѵ�.
    //char name_filter[] = "All Files (*.*)|*.*|txt Files (*.txt)|*.txt|";
	CString name_filter = _T("All Files (*.*)|*.*|");
  
    // FALSE -> �����ȭ����
    // "txt" -> ����ڰ� Ȯ���� ���� ���ϸ� �Է������� �ڵ����� �߰��� Ȯ���ڸ��̴�.
    // ��, tipssoft ������ �Է��ϸ� tipssoft.txt��� �Է��ѰͰ� �����ϰ� �ϰ� ������ ����Ѵ�.
    // "*.txt" �����̸��� �Է��ϴ� ����Ʈ �ڽ��� ��µ� �⺻ ���ڿ��̴�. 
    // OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT -> ���� ��ȭ���ڿ� �߰������� ����� �Ӽ�
    // name_filter -> ���� ���� �޺��ڽ��� ����� ���������� ����ִ� �޸��� �ּ��̴�.
    CFileDialog ins_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, name_filter, NULL);
 
    // ���� ���� �޺��ڽ��� ������ ���͵� �߿��� 2��° �׸�(*.txt)�� �����Ѵ�.
    ins_dlg.m_ofn.nFilterIndex = 2;
  
    // ���̾�α׸� ����.

    if(ins_dlg.DoModal() == IDOK)
    {
        CDevelopeNoteDlg *fm;
        CString fp; // file path
        CString fc; // file contents
		CString fn; // fine name
		CString fcUnit;
                 
        fm = new CDevelopeNoteDlg;
        fp = ins_dlg.GetPathName(); // ���� ��θ� ����
		fn = ins_dlg.GetFileName(); // ���� �̸��� ����
		
		m_edit_data7.SetWindowTextW(fp);
		m_edit_attach_fileName.SetWindowTextW(fn);
        delete fm;
        fm = NULL;
    }
}


BOOL CDevelopeNoteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�
	const int EnterInputGap = 100; //100ms
	static int  EnterTick = 0;
	int EnterGap;
	
	// ESC Key input
	if(pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	if(pMsg->wParam == VK_RETURN)
	{		
		EnterGap = GetTickCount() - EnterTick;

		// ���� Ű�� EnterInputGap �ð� ���� �������� ���� ���
		if ( GetTickCount() - EnterTick < EnterInputGap )
		{			
			return TRUE;
		}

		if (GetDlgItem(IDC_EDIT4) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT4);
			int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		else if (GetDlgItem(IDC_EDIT5) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT5);
            int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		else if (GetDlgItem(IDC_EDIT6) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT6);
            int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		else if (GetDlgItem(IDC_EDIT7) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT7);
            int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		else if (GetDlgItem(IDC_EDIT8) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT8);
            int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		else if (GetDlgItem(IDC_EDIT9) == GetFocus())
		{
            CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT9);
            int nLen = edit->GetWindowTextLength();
            edit->SetSel( nLen, nLen );
            edit->ReplaceSel( _T("\r\n") );
        }
		
		EnterTick = GetTickCount();
		return TRUE;
	}
	
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDevelopeNoteDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTxt;
	BOOL bTxtChanged = 0;
	int msgRes;
	
	while (1)
	{
		m_edit_data1.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data2.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data3.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data4.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data5.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data6.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}

		m_edit_data7.GetWindowTextW(strTxt);
		strTxt.Replace(_T(" "), _T(""));
		strTxt.Replace(_T("\r\n"), _T(""));
		if (strTxt != _T(""))
		{
			bTxtChanged = 1;
			break;
		}
		break;
	}

	if (bTxtChanged == 1 )
	{
		msgRes = AfxMessageBox(_T("�������� �ʰ� �����Ͻðڽ��ϱ�?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
		if ( msgRes == 1 )
		{
			CDialogEx::OnCancel();
		}
	}
	else
	{
		CDialogEx::OnCancel();
	}
}


void CDevelopeNoteDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nProjectNum = 0;
	BOOL bValueExist = FALSE;
	CString strProjectNum, strProjectIdx, strValue, strProjectName;
	
	// ProjectName �������
	m_edit_projectName.GetWindowTextW(strProjectName);
	strProjectName.Replace(_T(" "), _T(""));
	strProjectName.Replace(_T("\r\n"), _T(""));

	strProjectIdx = _T("Project0");
	while ( (strValue=SaveLogManage.ReadSetting(strProjectIdx)) != _T("") )
	{
		if ( strProjectName == strValue )
		{
			bValueExist = TRUE;
			break;
		}

		nProjectNum++;
		strProjectNum.Format(_T("%d"), nProjectNum);
		strProjectIdx = _T("Project") + strProjectNum;
	}

	if ( (bValueExist == FALSE) && (strProjectName != _T("")) )
	{
		SaveLogManage.WriteSetting(strProjectIdx, strProjectName);
		m_combo_projectName.AddString(strProjectName);
	}
}


void CDevelopeNoteDlg::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nUserNum = 0;
	BOOL bValueExist = FALSE;
	CString strUserNum, strUserIdx, strValue, strUserName;
	
	// ProjectName �������
	m_edit_userName.GetWindowTextW(strUserName);
	strUserName.Replace(_T(" "), _T(""));
	strUserName.Replace(_T("\r\n"), _T(""));

	strUserIdx = _T("User0");
	while ( (strValue=SaveLogManage.ReadSetting(strUserIdx)) != _T("") )
	{
		if ( strUserName == strValue )
		{
			bValueExist = TRUE;
			break;
		}

		nUserNum++;
		strUserNum.Format(_T("%d"), nUserNum);
		strUserIdx = _T("User") + strUserNum;
	}

	if ( (bValueExist == FALSE) && (strUserName != _T("")) )
	{
		SaveLogManage.WriteSetting(strUserIdx, strUserName);
		m_combo_userName.AddString(strUserName);
	}
}
