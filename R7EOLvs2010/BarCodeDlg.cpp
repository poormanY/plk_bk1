// BarCodeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "R7EOLvs2010.h"
#include "BarCodeDlg.h"
#include "afxdialogex.h"

#include "SettingDlg.h"
#include "y_LogManage.h"
#include "y_BarcodeMgt.h"
#include "y_Debugging.h"
#include "y_Color.h"
#include "y_IoBoardMgt.h"

#define TIMER_BARCODE1 8001
#define TIMER_BARCODE2 8002
static CBarcodeMgt* pBarCode1 = NULL;		// Barcode1 Ŭ����
static CBarcodeMgt* pBarCode2 = NULL;		// Barcode2 Ŭ����
static CIoBoardMgt *pBarIoBoard = NULL;		// IO Board Ŭ����

static signed short preBarcodeCount1 = 0;
static signed short preBarcodeCount2 = 0;

// BarCodeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(BarCodeDlg, CDialogEx)

BarCodeDlg::BarCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(BarCodeDlg::IDD, pParent)
{

}

BarCodeDlg::~BarCodeDlg()
{
}

void BarCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BAR1_OPEN, m_btn_bar1_open);
	DDX_Control(pDX, IDC_BUTTON_BAR2_OPEN, m_btn_bar2_open);
	DDX_Control(pDX, IDOK, m_btn_close);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btn_save);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_btn_load);
	DDX_Control(pDX, IDC_LIST_BAR1, m_list_bar1);
	DDX_Control(pDX, IDC_LIST_BAR2, m_list_bar2);
	DDX_Control(pDX, IDC_EDIT_BAR1_PORT, m_edit_bar1_port);
	DDX_Control(pDX, IDC_EDIT_BAR2_PORT, m_edit_bar2_port);
	DDX_Control(pDX, IDC_EDIT_BAR1_CONNECT, m_edit_bar1_connect);
	DDX_Control(pDX, IDC_EDIT_BAR2_CONNECT, m_edit_bar2_connect);
	DDX_Control(pDX, IDC_BUTTON_BAR1_CLR, m_btn_bar1_clr);
	DDX_Control(pDX, IDC_BUTTON_BAR2_CLR, m_btn_bar2_clr);
}


BEGIN_MESSAGE_MAP(BarCodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BAR1_OPEN, &BarCodeDlg::OnBnClickedButtonBar1Open)
	ON_BN_CLICKED(IDC_BUTTON_BAR2_OPEN, &BarCodeDlg::OnBnClickedButtonBar2Open)
	ON_BN_CLICKED(IDOK, &BarCodeDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BAR1_CLR, &BarCodeDlg::OnBnClickedButtonBar1Clr)
	ON_BN_CLICKED(IDC_BUTTON_BAR2_CLR, &BarCodeDlg::OnBnClickedButtonBar2Clr)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// BarCodeDlg �޽��� ó�����Դϴ�.


BOOL BarCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// Port �ʱ�ȭ
	CString strBar1Com;
	CString strBar2Com;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strBar1Com = pEolSetting->ReadSetting(COM_BAR1);
	strBar2Com = pEolSetting->ReadSetting(COM_BAR2);
	delete pEolSetting;
    pEolSetting = NULL;
	// Port Number
	m_edit_bar1_port.SetText(BLACK, GREEN, strBar1Com, UPDATE_ON);
	m_edit_bar2_port.SetText(BLACK, GREEN, strBar2Com, UPDATE_ON);
	// Port Connect
	m_edit_bar1_connect.SetText(BLACK, GREEN, _T("Not Connected"), UPDATE_ON);
	m_edit_bar2_connect.SetText(BLACK, GREEN, _T("Not Connected"), UPDATE_ON);

	// Button Skin
	// LoadBitmap(������ ������(U), ������ ��(D), ��Ŀ���� ������(F), ��Ȱ��ȭ(X));
    m_btn_bar1_open.LoadBitmaps(IDB_BITMAP_BAR1_OPEN, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR1_OPEN, IDB_BITMAP_BAR1_OPEN);
    m_btn_bar1_open.SizeToContent(); // �̹����� �°� ��ư ����� ����
	m_btn_bar2_open.LoadBitmaps(IDB_BITMAP_BAR2_OPEN, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR2_OPEN, IDB_BITMAP_BAR2_OPEN);
    m_btn_bar2_open.SizeToContent();
	m_btn_close.LoadBitmaps(IDB_BITMAP_BAR_CLOSE, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR_CLOSE, IDB_BITMAP_BAR_CLOSE);
    m_btn_close.SizeToContent();
	m_btn_save.LoadBitmaps(IDB_BITMAP_BAR_SAVE, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR_SAVE, IDB_BITMAP_BAR_SAVE);
    m_btn_save.SizeToContent();
	m_btn_load.LoadBitmaps(IDB_BITMAP_BAR_LOAD, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR_LOAD, IDB_BITMAP_BAR_LOAD);
    m_btn_load.SizeToContent();
	m_btn_bar1_clr.LoadBitmaps(IDB_BITMAP_BAR1_CLR, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR1_CLR, IDB_BITMAP_BAR1_CLR);
    m_btn_bar1_clr.SizeToContent();
	m_btn_bar2_clr.LoadBitmaps(IDB_BITMAP_BAR2_CLR, IDB_BITMAP_BLACKBTN, IDB_BITMAP_BAR2_CLR, IDB_BITMAP_BAR2_CLR);
    m_btn_bar2_clr.SizeToContent();

	// ����Ʈ �ʱ�ȭ
	m_list_bar1.DeleteAllItems();
	m_list_bar2.DeleteAllItems();
	// ����Ʈ ��Ÿ�� ����
	//LVS_EX_FULLROWSELECT  : �������� ������ �� �� �� ��ü�� ������Ų��.
	//LVS_EX_GRIDLINES      : �� �����ۿ� ��輱�� �׷��ش�.
	//LVS_EX_CHECKBOXES     : �� �����ۿ� Check Box�� ǥ���� �ش�.
	//LVS_EX_HEADERDRAGDROP : �÷� ����� �巡�� �����ν� �÷��� ������ �ٲ� �� �ְ� ���ش�.
	m_list_bar1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_bar2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// ����Ʈ Ÿ��Ʋ ����
	m_list_bar1.InsertColumn(0, _T("��ȣ"), LVCFMT_CENTER, 50, -1);
	m_list_bar1.InsertColumn(1, _T("���ڵ� ��ȣ"), LVCFMT_CENTER, 215, -1);
	m_list_bar2.InsertColumn(0, _T("��ȣ"), LVCFMT_CENTER, 50, -1);
	m_list_bar2.InsertColumn(1, _T("���ڵ� ��ȣ"), LVCFMT_CENTER, 215, -1);
	
	// ����Ʈ ��Ʈ�� ����� �����ϰ� �Ѵ�.
	m_list_bar1.SetBkColor(TRANSPARENT);
	m_list_bar1.SetTextBkColor(TRANSPARENT);
    m_list_bar1.SetTextColor(GREEN);
	
	m_list_bar2.SetBkColor(TRANSPARENT);
	m_list_bar2.SetTextBkColor(TRANSPARENT);
	m_list_bar2.SetTextColor(GREEN);

	// IO Board Open for switching on scanner
	OpenIoBoard();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void BarCodeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}

void BarCodeDlg::DrawDoubleBuffering(void)
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
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);		// ���� ���
																	// PATCOPY(����), BLACKNESS(����), WHITENESS(���), DSTINVERT(�������)

	///////////////////////////////////////////////
	// �޸� DC�� ��Ʈ�� �׸���
	///////////////////////////////////////////////
	CBitmap bmpZebra;
	bmpZebra.LoadBitmap(IDB_BITMAP_ZEBRACODE3);	// ��Ʈ�� �ε�
	MemDC.SelectObject(&bmpZebra);

	BITMAP bmpZebraSize;						// ��Ʈ�� ������Ʈ
    bmpZebra.GetObject(sizeof(BITMAP), &bmpZebraSize);	// ��Ʈ�� ������ ��� (bmpZebraSize.bmWidth, bmpZebraSize.bmHeight)

	// StretchBlt (
	//	HDC hdcDest  : �̹����� ����� ��ġ�� �ڵ�
	//  nXOriginDest : �̹����� ����� x ��ǥ
	//  nYOriginDest : �̹����� ����� y ��ǥ
	//  nWidthDest   : ����� �̹����� �ʺ�
	//  nHeightDest  : ����� �̹����� ����
	//                (hdcSrc�κ��� ���� �̹����� �� �ʺ�� ���̿� �°� �̹��� ũ�⸦ �����մϴ�)
	//  hDcSrc       : �̹����� �ڵ�
	//  nXOriginSrc  : ������ �̹����� ���������� x ��ǥ
	//  nOriginSrc   : ������ �̹����� ���������� y ��ǥ 
	//                (������ ��ġ�κ��� nWidthSrc, nHeightSrc��ŭ �̹����� �߶�ɴϴ�)
	//  nWidthSrc    : ���� �̹����κ��� �ش� ũ�⸸ŭ �߶� �̹����� �ʺ�
	//  nHeightSrc   : ���� �̹����κ��� �ش� ũ�⸸ŭ �߶� �̹����� ����
	//                (�� ũ�⸸ŭ ���� �̹������� �߶󳻾� nWidthDest, nHeightDest�� ũ�⿡ �°� �̹��� ũ�⸦ �����մϴ�)
	//  dwRop        : �̹����� ��� ���
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bmpZebraSize.bmWidth, bmpZebraSize.bmHeight, SRCCOPY);

	// ���� �޸� �� ��Ʈ�� ����
	MemDC.SelectObject(pOldBitmap);
    MemDC.DeleteDC();
}


void BarCodeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strBarCode;
	CString strListPos;
	int nListPos;
	static int nBar1ScanCnt = 0;
	static int nBar2ScanCnt = 0;
	
	if ( nIDEvent == TIMER_BARCODE1 )
	{
		// IO Board -> Scan on
		Bar1ScanON();

		if (pBarCode1->GetCount() > preBarcodeCount1)
		{
			// ���� ���ڵ� ī��Ʈ�� �������� ��
			preBarcodeCount1 = pBarCode1->GetCount();

			// ���ο� ���ڵ� ��
			strBarCode = "";
			strBarCode = (LPCSTR)pBarCode1->GetDataAt(preBarcodeCount1-1);

			// ����Ʈ ������ ����
			nListPos = m_list_bar1.GetItemCount();
			strListPos.Format( _T("%d"), (nListPos+1) );

			// ����Ʈ ��ȣ��
			m_list_bar1.InsertItem(nListPos, strListPos);
			// PCB ���ڵ� ��
			m_list_bar1.SetItem(nListPos, 1, LVIF_TEXT, strBarCode, 0, 0, 0, NULL );

			// ListBox ��Ʈ�� �ڵ� ��ũ��
			m_list_bar1.SendMessage(WM_VSCROLL, SB_BOTTOM);

			// IO Board -> Scan off
			// ���ڵ带 ���� �Ŀ��� OFF -> ON ���� �ʿ�
			Bar1ScanOFF();
			nBar1ScanCnt = 0;
		}
		else
		{
			nBar1ScanCnt++;	// per100ms

			// 30�ʰ� ���ڵ带 ���� ���ϸ� OFF -> ON ���� �ʿ�
			if ( nBar1ScanCnt > 30 )
			{
				Bar1ScanOFF();
				nBar1ScanCnt = 0;
			}
		}
	}
	else if ( nIDEvent == TIMER_BARCODE2 )
	{
		// IO Board -> Scan on
		Bar2ScanON();

		if (pBarCode2->GetCount() > preBarcodeCount2)
		{
			// ���� ���ڵ� ī��Ʈ�� �������� ��
			preBarcodeCount2 = pBarCode2->GetCount();

			// ���ο� ���ڵ� ��
			strBarCode = "";
			strBarCode = (LPCSTR)pBarCode2->GetDataAt(preBarcodeCount2-1);

			// ����Ʈ ������ ����
			nListPos = m_list_bar2.GetItemCount();
			strListPos.Format( _T("%d"), (nListPos+1) );

			// ����Ʈ ��ȣ��
			m_list_bar2.InsertItem(nListPos, strListPos);
			// PCB ���ڵ� ��
			m_list_bar2.SetItem(nListPos, 1, LVIF_TEXT, strBarCode, 0, 0, 0, NULL );
								
			// ListBox ��Ʈ�� �ڵ� ��ũ��
			m_list_bar2.SendMessage(WM_VSCROLL, SB_BOTTOM);

			// IO Board -> Scan off
			// ���ڵ带 ���� �Ŀ��� OFF -> ON ���� �ʿ�
			Bar2ScanOFF();
			nBar2ScanCnt = 0;
		}
		else
		{
			nBar2ScanCnt++;	// per100ms

			// 30�ʰ� ���ڵ带 ���� ���ϸ� OFF -> ON ���� �ʿ�
			if ( nBar2ScanCnt > 30 )
			{
				Bar2ScanOFF();
				nBar2ScanCnt = 0;
			}
		}
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


void BarCodeDlg::Barcode1Close()
{
	if ( pBarCode1 != NULL )
	{
		KillTimer(TIMER_BARCODE1);

		pBarCode1->Close();
		pBarCode1->DelAllData();
		delete pBarCode1;
		pBarCode1 = NULL;

		// ���ڵ� ���� �ʱ�ȭ
		preBarcodeCount1 = 0;

		// Port Connect
		m_edit_bar1_connect.SetText(BLACK, GREEN, _T("Not Connected"), UPDATE_ON);

		// ��ĳ�� �ʱ�ȭ
		Bar1ScanOFF();

		dp("Barcode1 Close\n");
	}
}
void BarCodeDlg::Barcode2Close()
{
	if ( pBarCode2 != NULL )
	{
		KillTimer(TIMER_BARCODE2);

		pBarCode2->Close();
		pBarCode2->DelAllData();
		delete pBarCode2;
		pBarCode2 = NULL;

		// ���ڵ� ���� �ʱ�ȭ
		preBarcodeCount2 = 0;

		// Port Connect
		m_edit_bar2_connect.SetText(BLACK, GREEN, _T("Not Connected"), UPDATE_ON);

		// ��ĳ�� �ʱ�ȭ
		Bar2ScanOFF();

		dp("Barcode2 Close\n");
	}
}

void BarCodeDlg::OnBnClickedButtonBar1Open()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ��Ʈ �ҷ�����
	CString strBar1Com;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strBar1Com = pEolSetting->ReadSetting(COM_BAR1);
	delete pEolSetting;
    pEolSetting = NULL;

	m_edit_bar1_port.SetText(BLACK, GREEN, strBar1Com, UPDATE_ON);
	
	if ( pBarCode1 == NULL )
	{
		// ���ڵ� �ʱ�ȭ
		pBarCode1 = new CBarcodeMgt;

		if (pBarCode1->Open((CStringA)strBar1Com) == true)
		{
			dp("Barcode1 : %s Open Success\n", (CStringA)strBar1Com);

			// ���ڵ� Thread ����
			pBarCode1->Thread_Begin();
			// ���ڵ� Ÿ�̸� ����
			SetTimer(TIMER_BARCODE1, 100, NULL);

			// Port Connect
			m_edit_bar1_connect.SetText(GREEN, BLACK, _T("Connected"), UPDATE_ON);
		}
		else
		{
			dp("Barcode1 : %s Open Fail\n", (CStringA)strBar1Com);

			Barcode1Close();
		}
	}
	else
	{
		Barcode1Close();
	}
}

void BarCodeDlg::OnBnClickedButtonBar2Open()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ��Ʈ �ҷ�����
	CString strBar2Com;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strBar2Com = pEolSetting->ReadSetting(COM_BAR2);
	delete pEolSetting;
    pEolSetting = NULL;

	m_edit_bar2_port.SetText(BLACK, GREEN, strBar2Com, UPDATE_ON);

	if ( pBarCode2 == NULL )
	{
		// ���ڵ� �ʱ�ȭ
		pBarCode2 = new CBarcodeMgt;

		if (pBarCode2->Open((CStringA)strBar2Com) == true)
		{
			dp("Barcode2 : %s Open Success\n", (CStringA)strBar2Com);

			// ���ڵ� Thread ����
			pBarCode2->Thread_Begin();
			// ���ڵ� Ÿ�̸� ����
			SetTimer(TIMER_BARCODE2, 100, NULL);

			// Port Connect
			m_edit_bar2_connect.SetText(GREEN, BLACK, _T("Connected"), UPDATE_ON);
		}
		else
		{
			dp("Barcode2 : %s Open Fail\n", (CStringA)strBar2Com);

			Barcode2Close();
		}
	}
	else
	{
		Barcode2Close();
	}
}

void BarCodeDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();

	// ���ڵ� ����
	Barcode1Close();
	Barcode2Close();
	// IO ����
	CloseIoBoard();
}

void BarCodeDlg::OnBnClickedButtonBar1Clr()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ��� ������ �����
	m_list_bar1.DeleteAllItems();
	
	dp("Clear Barcode1\n");
}


void BarCodeDlg::OnBnClickedButtonBar2Clr()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ��� ������ �����
	m_list_bar2.DeleteAllItems();
	
	dp("Clear Barcode2\n");
}

HBRUSH BarCodeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	switch(nCtlColor)
    {
		// ����Ʈ �ڽ�
		case CTLCOLOR_EDIT:
		{
			// �ؽ�Ʈ ����� �����ϰ� �Ѵ�.
			pDC->SetBkMode(TRANSPARENT);
			// �ؽ�Ʈ�� ������ �����Ѵ�.
			pDC->SetTextColor(GREEN);
			// ����Ʈ ��Ʈ���� ����� �����ϰ� �Ѵ�.
			pDC->SelectStockObject(NULL_BRUSH);
			return NULL;
		}
		// �б� ���� ��Ʈ��
		case CTLCOLOR_STATIC:
        {
			// �ؽ�Ʈ ����� �����ϰ� �Ѵ�.
			pDC->SetBkMode(TRANSPARENT);
			// �ؽ�Ʈ�� ������ �����Ѵ�.
			pDC->SetTextColor(GREEN);
			// ����Ʈ ��Ʈ���� ����� �����ϰ� �Ѵ�.
			pDC->SelectStockObject(NULL_BRUSH);
			return NULL;
		}
    }
	
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


// SerialDlg �޽��� ó�����Դϴ�.
BOOL BarCodeDlg::OpenIoBoard()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pBarIoBoard = new CIoBoardMgt;
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
	
    if (pBarIoBoard == NULL)
    {
        return false;
    }

	if (pBarIoBoard->Open(pbIoBdCom) == false)
    {
        dp("[%s] IO Board Open Fail!\n",pbIoBdCom);

		CloseIoBoard();
        return false;
    }
		

	strIoBdProduct = _T("KM ");
    if (pBarIoBoard->TransferMsg("$01GA001\r") == false)
    {
        dp("[%s] IO Board communication error!!\n", pbIoBdCom);

		CloseIoBoard();
        return false;
    }
	else
	{
		strIoBdProduct += (pBarIoBoard->GetMsg()+9);
	}

	strIoBdProduct += _T(" Ver ");
    if (strcmp(pBarIoBoard->GetMsg()+9, "6050") != 0)
    {
        dp("[%s] IO Board model %s error!\n",pbIoBdCom, pBarIoBoard->GetMsg()+9);

		CloseIoBoard();
        return false;
    }
	else
	{
		strIoBdProduct += (pBarIoBoard->GetMsg()+9);
	}
		
	delete pbIoBdCom;
	pbIoBdCom= NULL;

	// ��ĳ�� �ʱ�ȭ
	Bar1ScanOFF();
	Bar2ScanOFF();

	return true;
}

BOOL BarCodeDlg::CloseIoBoard()
{
	if (pBarIoBoard == NULL)
    {
        return false;
    }

	// ��ĳ�� �ʱ�ȭ
	Bar1ScanOFF();
	Bar2ScanOFF();

	delete pBarIoBoard;
    pBarIoBoard = NULL;
	dp("IO Board Close\n");

	return true;
}

BOOL BarCodeDlg::Bar1ScanON()
{
	if (pBarIoBoard == NULL)
    {
        return false;
    }

	pBarIoBoard->PutOutBit(_BIT_OUT_BARCODE1, true);

	return true;
}
BOOL BarCodeDlg::Bar1ScanOFF()
{
	if (pBarIoBoard == NULL)
    {
        return false;
    }

	pBarIoBoard->PutOutBit(_BIT_OUT_BARCODE1, false);

	return true;
}
BOOL BarCodeDlg::Bar2ScanON()
{
	if (pBarIoBoard == NULL)
    {
        return false;
    }

	pBarIoBoard->PutOutBit(_BIT_OUT_BARCODE2, true);

	return true;
}
BOOL BarCodeDlg::Bar2ScanOFF()
{
	if (pBarIoBoard == NULL)
    {
        return false;
    }

	pBarIoBoard->PutOutBit(_BIT_OUT_BARCODE2, false);

	return true;
}

BOOL BarCodeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//CDC *pDC = GetDC();		// ���� DC ���
	CRect rect;
	GetClientRect(rect);	// ���� â ������ ���

	CDC MemDC;				// �޸� DC
	CBitmap *pOldBitmap;	// �޸� DC�� ��Ʈ��
	CBitmap bmp;			// ���� DC ������ ��Ʈ��

	MemDC.CreateCompatibleDC(pDC);									// �޸� DC�� ���� DC�� ���� ��ġ
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());	// ��Ʈ�ʰ� ���� DC�� ���� ��ġ 
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);				// �޸� DC�� ��Ʈ�� ����
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);		// ���� ���
																	// PATCOPY(����), BLACKNESS(����), WHITENESS(���), DSTINVERT(�������)

	///////////////////////////////////////////////
	// �޸� DC�� ��Ʈ�� �׸���
	///////////////////////////////////////////////
	CBitmap bmpZebra;
	bmpZebra.LoadBitmap(IDB_BITMAP_ZEBRACODE3);	// ��Ʈ�� �ε�
	MemDC.SelectObject(&bmpZebra);

	BITMAP bmpZebraSize;						// ��Ʈ�� ������Ʈ
    bmpZebra.GetObject(sizeof(BITMAP), &bmpZebraSize);	// ��Ʈ�� ������ ��� (bmpZebraSize.bmWidth, bmpZebraSize.bmHeight)

	// StretchBlt (
	//	HDC hdcDest  : �̹����� ����� ��ġ�� �ڵ�
	//  nXOriginDest : �̹����� ����� x ��ǥ
	//  nYOriginDest : �̹����� ����� y ��ǥ
	//  nWidthDest   : ����� �̹����� �ʺ�
	//  nHeightDest  : ����� �̹����� ����
	//                (hdcSrc�κ��� ���� �̹����� �� �ʺ�� ���̿� �°� �̹��� ũ�⸦ �����մϴ�)
	//  hDcSrc       : �̹����� �ڵ�
	//  nXOriginSrc  : ������ �̹����� ���������� x ��ǥ
	//  nOriginSrc   : ������ �̹����� ���������� y ��ǥ 
	//                (������ ��ġ�κ��� nWidthSrc, nHeightSrc��ŭ �̹����� �߶�ɴϴ�)
	//  nWidthSrc    : ���� �̹����κ��� �ش� ũ�⸸ŭ �߶� �̹����� �ʺ�
	//  nHeightSrc   : ���� �̹����κ��� �ش� ũ�⸸ŭ �߶� �̹����� ����
	//                (�� ũ�⸸ŭ ���� �̹������� �߶󳻾� nWidthDest, nHeightDest�� ũ�⿡ �°� �̹��� ũ�⸦ �����մϴ�)
	//  dwRop        : �̹����� ��� ���
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bmpZebraSize.bmWidth, bmpZebraSize.bmHeight, SRCCOPY);

	// ���� �޸� �� ��Ʈ�� ����
	MemDC.SelectObject(pOldBitmap);
    MemDC.DeleteDC();
	return true;

	return CDialogEx::OnEraseBkgnd(pDC);
}
