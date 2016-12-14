
// DevelopeNoteDlg.cpp : 구현 파일
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

CLogManage		SaveLogManage;	// 테스트 로그 기록

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CDevelopeNoteDlg 대화 상자




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


// CDevelopeNoteDlg 메시지 처리기

BOOL CDevelopeNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SaveLogManage.SetFilePath(_T("DevelopeNote.ini"));

	// HW NOTE 이미지 로고
	m_cbtn_hwnote.LoadBitmaps(IDB_BMP_HWNOTE, IDB_BMP_HWNOTE, IDB_BMP_HWNOTE, IDB_BMP_HWNOTE);
    m_cbtn_hwnote.SizeToContent(); // 이미지에 맞게 버튼 사이즈를 조정

	// 현재 날짜 표시
	CTime   oTime;
	CString strTime;
	
	// 프로젝트 이름 콤보 박스
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
	// 사용자 콤보 박스
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDevelopeNoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDevelopeNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CDevelopeNoteDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect( rect, SOFT_BLUE );
 
    return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CDevelopeNoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch(nCtlColor)
    {
        // 읽기 전용 컨트롤
        case CTLCOLOR_STATIC:
        {
            pDC->SetTextColor(BLACK);
            pDC->SetBkColor(SOFT_BLUE);
        }
        break;
    }

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CDevelopeNoteDlg::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strUserName;
	int nIdx;

	nIdx = m_combo_userName.GetCurSel();
	m_combo_userName.GetLBText(nIdx, strUserName);

	m_edit_userName.SetWindowTextW(strUserName);
}


void CDevelopeNoteDlg::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strProjectName;
	int nIdx;

	nIdx = m_combo_projectName.GetCurSel();
	m_combo_projectName.GetLBText(nIdx, strProjectName);

	m_edit_projectName.SetWindowTextW(strProjectName);
}

// 파일 저장 함수
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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 파일 저장
    // 파일 형식 콤보박스에 등록할 확장자 필터를 정의한다. (*.*, *.txt)
    // 확장자 필터의 첫번째 부분은 콤보박스에 출력될 문자열을 명시하며,
    // 두번째 부분은 파일 다이얼로그에 출력될 파일들의 확장자를 명시한다.
    // 원하는 확장자 필터를 아래와 같이 " | " 구분자를 이용하여 여러개를 등록할 수 있으며
    // 문자열의 끝에는 반드시 구분자가 명시되어야 한다.
    //char name_filter[] = "All Files (*.*)|*.*|txt Files (*.txt)|*.txt|";
	CString name_filter = _T("All Files (*.*)|*.*|txt Files (*.txt)|*.txt|");
  
    // FALSE -> 저장대화상자
    // "txt" -> 사용자가 확장자 없이 파일명만 입력했을때 자동으로 추가될 확장자명이다.
    // 즉, tipssoft 까지만 입력하면 tipssoft.txt라고 입력한것과 동일하게 하고 싶을때 사용한다.
    // "*.txt" 파일이름을 입력하는 에디트 박스에 출력될 기본 문자열이다. 
    // OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT -> 파일 대화상자에 추가적으로 사용할 속성
    // name_filter -> 파일 형식 콤보박스에 등록할 필터정보를 담고있는 메모리의 주소이다.
    CFileDialog ins_dlg(FALSE, _T("txt"), strFilePath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
                                                    OFN_NOCHANGEDIR, name_filter, NULL);
 
    // 파일 형식 콤보박스에 나열된 필터들 중에서 2번째 항목(*.txt)을 선택한다.
    ins_dlg.m_ofn.nFilterIndex = 2;
  
    // 다이얼로그를 띄운다.

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
        fp = ins_dlg.GetPathName(); // 파일 경로를 지정
		fn = ins_dlg.GetFileName(); // 파일 이름을 지정
		ff = GetFileFolderPath(fp); // 폴더 경로를 지정

		// 파일 내용 저장
		fc = _T("");		
		fc += _T("/////////////////////////////////////////////////\n");
		fc += _T("// 프로젝트 : ");
		m_edit_projectName.GetWindowTextW(fcUnit);
		fc += fcUnit;
		fc += _T("\n//   작성자 : ");
		m_edit_userName.GetWindowTextW(fcUnit);
		fc += fcUnit;
		fc += _T("\n//     날짜 : ");
		m_datetime_date.GetTime(date);
		fcUnit = date.Format("%Y%m%d");
		fc += fcUnit;
		fc += _T("\n/////////////////////////////////////////////////\n");

		fc += _T("<================== 불량 현상 ==================>\n");
		m_edit_data1.GetWindowTextW(fcUnit);
		fc += fcUnit;

		fc += _T("\n<================== 추정 원인 ==================>\n");
		m_edit_data2.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== 요구 사항 ==================>\n");
		m_edit_data3.GetWindowTextW(fcUnit);
		fc += fcUnit;

		fc += _T("\n<================== 적용 방법 ==================>\n");
		m_edit_data4.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== 검토 결과 ==================>\n");
		m_edit_data5.GetWindowTextW(fcUnit);
		fc += fcUnit;
				
		fc += _T("\n\n<================== 해결 방법 ==================>\n");
		m_edit_data6.GetWindowTextW(fcUnit);
		fc += fcUnit;
		
		fc += _T("\n\n<================== 첨부 파일 ==================>\n");
		m_edit_data7.GetWindowTextW(fcFileOriginPath);
		fc += fcFileOriginPath;
		// 첨부 파일을 해당 경로에 복사
		m_edit_attach_fileName.GetWindowTextW(fcFileName);
		fcFileCopyPath = ff + fcFileName;
		BOOL bSuccess = CopyFile(fcFileOriginPath, fcFileCopyPath, TRUE);
		if ( !bSuccess )
		{
			msgRes = AfxMessageBox(_T("첨부 파일이 이미 존재 합니다.\n덮어쓰시겠습니까?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
			if ( msgRes == IDOK )
			{
				bSuccess = CopyFile(fcFileOriginPath, fcFileCopyPath, FALSE);				
				if ( !bSuccess )
				{
					AfxMessageBox(_T("첨부 파일 복사에 실패하였습니다."), MB_OK | MB_ICONSTOP);
				}				
			}
		}

        // 선택한 파일 경로에 에디트 박스의 내용을 저장한다.
        fm->FileSave(fp, fc);
        
        delete fm;
        fm = NULL;

		msgRes = AfxMessageBox(_T("저장하였습니다.\r\n프로그램을 종료하시겠습니까?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
		if ( msgRes == IDOK )
		{
			CDialogEx::OnOK();
		}
    }
}


void CDevelopeNoteDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 파일 저장
    // 파일 형식 콤보박스에 등록할 확장자 필터를 정의한다. (*.*, *.txt)
    // 확장자 필터의 첫번째 부분은 콤보박스에 출력될 문자열을 명시하며,
    // 두번째 부분은 파일 다이얼로그에 출력될 파일들의 확장자를 명시한다.
    // 원하는 확장자 필터를 아래와 같이 " | " 구분자를 이용하여 여러개를 등록할 수 있으며
    // 문자열의 끝에는 반드시 구분자가 명시되어야 한다.
    //char name_filter[] = "All Files (*.*)|*.*|txt Files (*.txt)|*.txt|";
	CString name_filter = _T("All Files (*.*)|*.*|");
  
    // FALSE -> 저장대화상자
    // "txt" -> 사용자가 확장자 없이 파일명만 입력했을때 자동으로 추가될 확장자명이다.
    // 즉, tipssoft 까지만 입력하면 tipssoft.txt라고 입력한것과 동일하게 하고 싶을때 사용한다.
    // "*.txt" 파일이름을 입력하는 에디트 박스에 출력될 기본 문자열이다. 
    // OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT -> 파일 대화상자에 추가적으로 사용할 속성
    // name_filter -> 파일 형식 콤보박스에 등록할 필터정보를 담고있는 메모리의 주소이다.
    CFileDialog ins_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, name_filter, NULL);
 
    // 파일 형식 콤보박스에 나열된 필터들 중에서 2번째 항목(*.txt)을 선택한다.
    ins_dlg.m_ofn.nFilterIndex = 2;
  
    // 다이얼로그를 띄운다.

    if(ins_dlg.DoModal() == IDOK)
    {
        CDevelopeNoteDlg *fm;
        CString fp; // file path
        CString fc; // file contents
		CString fn; // fine name
		CString fcUnit;
                 
        fm = new CDevelopeNoteDlg;
        fp = ins_dlg.GetPathName(); // 파일 경로를 지정
		fn = ins_dlg.GetFileName(); // 파일 이름을 지정
		
		m_edit_data7.SetWindowTextW(fp);
		m_edit_attach_fileName.SetWindowTextW(fn);
        delete fm;
        fm = NULL;
    }
}


BOOL CDevelopeNoteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다
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

		// 엔터 키가 EnterInputGap 시간 내에 연속으로 들어올 경우
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		msgRes = AfxMessageBox(_T("저장하지 않고 종료하시겠습니까?"), MB_OKCANCEL | MB_ICONEXCLAMATION);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nProjectNum = 0;
	BOOL bValueExist = FALSE;
	CString strProjectNum, strProjectIdx, strValue, strProjectName;
	
	// ProjectName 갖어오기
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nUserNum = 0;
	BOOL bValueExist = FALSE;
	CString strUserNum, strUserIdx, strValue, strUserName;
	
	// ProjectName 갖어오기
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
