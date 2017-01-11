// CExpressImgDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "R7EOLvs2010.h"
#include "y_ExpressImgDlg.h"
#include "afxdialogex.h"
#include "y_wm_user.h"
#include "y_Color.h"

// CExpressImgDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CExpressImgDlg, CDialogEx)

CExpressImgDlg::CExpressImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExpressImgDlg::IDD, pParent)
{

}

CExpressImgDlg::~CExpressImgDlg()
{

}

void CExpressImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExpressImgDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CExpressImgDlg �޽��� ó�����Դϴ�.

BOOL CExpressImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//Ÿ�̸� ����
    SetTimer(TIMER_EXPRESS_IMG, 100, 0);
	
	m_nCurrPos = 0;
	m_tImageShowCompleted = 0;
	m_nImgView = CALIBRATION;
	m_nPreImgView = CALIBRATION;

	m_nVanish = 90;						// Vanish ��
	m_nLaneWidth = 12;					// ���� ����
	m_nLaneMovement = 30;				// ���� �̵���
	m_nLaneLColor = YELLOW;				// ���� ���� ����
	m_nLaneRColor = WHITE;				// ������ ���� ����

	CreateExpressImg();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CExpressImgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	int nSequence = 25;	// �ִ� 25�� �̵�

	switch(nIDEvent)
	{
	// Ÿ�̸Ӹ� �̿��Ͽ� ������ ���� ���ϴ� ������ ��ü �̹����� ǥ���Ѵ�.
	case TIMER_EXPRESS_IMG :

		if ( m_nPreImgView != m_nImgView )
		{
			m_nCurrPos = 0;
			m_tImageShowCompleted = 0;
			m_nPreImgView = m_nImgView;
		}
		else
		{
			if (m_nCurrPos > nSequence)
			{
				m_tImageShowCompleted = 1;
			}
			else
			{
				DrawALL(&dc, m_nImgView);
			}
		}		
		break;
	default :

		break;
	}


	CDialogEx::OnTimer(nIDEvent);
}


BOOL CExpressImgDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CExpressImgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	DrawALL(&dc,  m_nImgView);
}

void CExpressImgDlg::DrawALL(CDC *pDC, int PartNum)
{
	int CenterX, CenterY;
	int ScreenWidth = rtWholeScreenSize.right - rtWholeScreenSize.left;
	int ScreenHeight = rtWholeScreenSize.bottom - rtWholeScreenSize.top;

	/////////////////////////////////////////////////////////////////
	//ȭ�� ������ ����
	//ȭ�� DC�� ȣȯ���ִ� �޸� DC�� ����
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(pDC);

	//ȭ�� DC�� ȣȯ���ִ� �޸� ��Ʈ���� ����
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(pDC, ScreenWidth, ScreenHeight);

	//�޸� DC�� �޸� ��Ʈ���� ����
	CBitmap *pOldBitmap = (CBitmap*)BufferDC.SelectObject(&bmpBuffer);
	/////////////////////////////////////////////////////////////////

	GetDisplaySpace(rtSubScreenSize);
	
    CenterX	= (rtSubScreenSize.right + rtSubScreenSize.left) / 2;
	CenterY = (rtSubScreenSize.bottom + rtSubScreenSize.top) / 2;

	switch ( PartNum )
	{
	//������ �̹���
	case CALIBRATION :
		// ���� ��
        theDraw.Draw_Line(&BufferDC, rtSubScreenSize.left, CenterY  , rtSubScreenSize.right, CenterY  , WHITE);

		// ���� ��
        theDraw.Draw_Line(&BufferDC, CenterX  , rtSubScreenSize.top, CenterX  , rtSubScreenSize.bottom, WHITE);

        pDC->BitBlt(rtWholeScreenSize.left, rtWholeScreenSize.top, ScreenWidth, ScreenHeight, &BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, SRCCOPY);
        BufferDC.SelectObject(pOldBitmap);
		break;
	case LDW_DETECT :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		m_nCurrPos++;
		break;
	case LDW_WARN_R :
		DrawLine_Sub (&BufferDC, m_nLaneMovement * (-1));	//�̵���
		m_nCurrPos++;
		break;
	case LDW_WARN_L :
		DrawLine_Sub (&BufferDC, m_nLaneMovement);	//�̵���
		m_nCurrPos++;
		break;
	case FCW_CAR_DETECT :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 0, IDB_BITMAP_REALCAR01);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_WARN :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 4, 0, IDB_BITMAP_REALCAR01);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_DETECT :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 35, IDB_BITMAP_REALCAR01BRAKE);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_WARN :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, -3, 35, IDB_BITMAP_REALCAR01);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case LDW_DETECT_NIGHT :
		DrawLineNight_Sub (&BufferDC, 0);	//�̵���
		m_nCurrPos++;
		break;
	case LDW_WARN_L_NIGHT :
		DrawLineNight_Sub (&BufferDC, m_nLaneMovement * (-1));	//�̵���
		m_nCurrPos++;
		break;
	case LDW_WARN_R_NIGHT :
		DrawLineNight_Sub (&BufferDC, m_nLaneMovement);	//�̵���
		m_nCurrPos++;
		break;
	case FCW_CAR_DETECT_NIGHT :
		DrawLineNight_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 0, IDB_BITMAP_REALCAR01BRAKE);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_WARN_NIGHT :
		DrawLineNight_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 4, 0, IDB_BITMAP_REALCAR01BRAKE);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_DETECT_NIGHT :
		DrawLineNight_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 35, IDB_BITMAP_REALCAR01BRAKE);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_WARN_NIGHT :
		DrawLineNight_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, -3, 35, IDB_BITMAP_REALCAR01BRAKE);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_DETECT2 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 0, IDB_BITMAP_REALCAR02);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_WARN2 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 4, 0, IDB_BITMAP_REALCAR02);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_DETECT2 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 35, IDB_BITMAP_REALCAR02);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_WARN2 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, -3, 35, IDB_BITMAP_REALCAR02);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_DETECT3 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 0, IDB_BITMAP_REALCAR03);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCW_CAR_WARN3 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 4, 0, IDB_BITMAP_REALCAR03);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_DETECT3 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, 0, 35, IDB_BITMAP_REALCAR03);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	case FCDA_CAR_WARN3 :
		DrawLine_Sub (&BufferDC, 0);	//�̵���
		Vehicle_Sub (&BufferDC, -3, 35, IDB_BITMAP_REALCAR03);	//�̵���, �ʱ�ũ��
		m_nCurrPos++;
		break;
	default :

		break;
	}


	//�޸� ��Ʈ�ʿ� �׷��� ������ ȭ������ ����
	pDC->BitBlt(rtWholeScreenSize.left, rtWholeScreenSize.top, ScreenWidth, ScreenHeight, &BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, SRCCOPY);

	//DC ����
	BufferDC.SelectObject(pOldBitmap);
}

// �̹��� ���� ���� ������ ������ 0, �ٸ��� 1�� ����
BOOL CExpressImgDlg::ImgSet(_ImgView ImgNum)
{
	m_nImgView = ImgNum;

	if ( m_nImgView == m_nPreImgView )	return 0;
	else								return 1;
}

BOOL CExpressImgDlg::ImgSet_Vanish(int vanish)
{
	// vanish ��
	if (vanish < 0) return 0;
	//if ( (vanish < 0) || (vanish > rtWholeScreenSize.bottom) ) return 0;

	m_nVanish = vanish;
	return 1;
}
BOOL CExpressImgDlg::ImgSet_LandWidth(int laneWidth)
{
	// ���� ����
	if ( (laneWidth < 0) || ( laneWidth > (rtSubScreenSize.right - rtSubScreenSize.left)/2) ) return 0;

	m_nLaneWidth = laneWidth;
	return 1;
}
BOOL CExpressImgDlg::ImgSet_LaneMovemnet(int laneMove)
{
	// ���� �̵���
	if ( laneMove < 0 )		return 0;

	m_nLaneMovement = laneMove;
	return 1;
}
BOOL CExpressImgDlg::ImgSet_LaneLColor(COLORREF color)
{
	m_nLaneLColor = color;

	return 1;
}
BOOL CExpressImgDlg::ImgSet_LaneRColor(COLORREF color)
{
	m_nLaneRColor = color;

	return 1;
}


// ���������� �ػ󵵸� Ȯ��
// 320 * 240�� ������ ���÷��̸� �ϱ� ���Ͽ� �����¿��� ��ǥ���� ����
void CExpressImgDlg::GetDisplaySpace(CRect &rt)
{
    int nH, nW, nRate;
    CRect oRect;

    ::GetClientRect(this->m_hWnd, &rtWholeScreenSize);

    oRect = rtWholeScreenSize;

    nW = oRect.right  / 320;
    nH = oRect.bottom / 240;

    nRate = (nH < nW)? nH: nW;
    oRect.right  = 320 * nRate;
    oRect.bottom = 240 * nRate;

    nW = (rtWholeScreenSize.right  - oRect.right ) / 2;
    nH = (rtWholeScreenSize.bottom - oRect.bottom) / 2;

    oRect.left	 += nW;
	oRect.right	 += nW;

    // oRect.top    += (nH - 8*nRate);
    // oRect.bottom += (nH - 8*nRate);

    rt = oRect;
}

// ���̾�α� ����� ����̹��� �޸� ����.
BOOL CExpressImgDlg::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// Ÿ�̸� ����
	KillTimer(TIMER_EXPRESS_IMG);

	if(m_pbmBack)
	{
		DeleteObject(m_pbmBack);
	}

	return CDialogEx::DestroyWindow();
}



BOOL CExpressImgDlg::CreateExpressImg()
{
    if (::GetSystemMetrics(SM_CMONITORS) < 2) // ����� ���� ���ϱ�
    {
		// ����Ͱ� �ϳ��� ���
		int nMainLeft   = ::GetSystemMetrics(SM_XVIRTUALSCREEN); // ���� ���� ����� X ��ǥ
		int nMainTop    = ::GetSystemMetrics(SM_YVIRTUALSCREEN); // ���� ���� ����� Y ��ǥ
		int nMainWidth  = ::GetSystemMetrics(SM_CXSCREEN);		 // ���� ����� ��ü ����
		int nMainHeight = ::GetSystemMetrics(SM_CYSCREEN);		 // ���� ����� ��ü ����

		MoveWindow(nMainLeft, nMainTop, nMainWidth, nMainHeight);
		
		return false;
    }

    // ���� ����� ����� ���̾�α� ���
    HMONITOR    hMonitorThis, hMonitorTarget;
    MONITORINFO oMonitorThis, oMonitorTarget;
    POINT oPoint;

    // ���� �������� ����� ��ġ ���ϱ�
    hMonitorThis = ::MonitorFromWindow( this->GetSafeHwnd(), MONITOR_DEFAULTTONEAREST );

    oMonitorThis.cbSize = sizeof(MONITORINFO);
    ::GetMonitorInfo(hMonitorThis, &oMonitorThis);

    // Ÿ�� �������� ����� ��ġ ���ϱ�
    if (oMonitorThis.rcMonitor.left != 0)
    {
        // ���� ������� ���� ����Ϳ� ��ġ�� �ִ�.
        // ���� Ÿ�� ������� �� �����(0, 0)�� �����Ѵ�.
        oPoint.x = 0; oPoint.y = 0;
        hMonitorTarget = ::MonitorFromPoint(oPoint, MONITOR_DEFAULTTONEAREST);
        oMonitorTarget.cbSize = sizeof(MONITORINFO);
        ::GetMonitorInfo(hMonitorTarget, &oMonitorTarget);
    }
    else
    {
        // ���� ������� �� ����Ϳ� ��ġ�� �ִ�.
        // ���� ����Ͱ� ���ʿ� �ִ��� �����ʿ� �ִ��� Ȯ���ؾ� �Ѵ�.
        oPoint.x = -1; oPoint.y = 0;
        hMonitorTarget = ::MonitorFromPoint(oPoint, MONITOR_DEFAULTTONULL);
        if (hMonitorTarget <= 0)
        {
            oPoint.x = oMonitorThis.rcMonitor.right+1; oPoint.y = 0;
            hMonitorTarget = ::MonitorFromPoint(oPoint, MONITOR_DEFAULTTONULL);
        }
        oMonitorTarget.cbSize = sizeof(MONITORINFO);
        ::GetMonitorInfo(hMonitorTarget, &oMonitorTarget);
    }

    MoveWindow(oMonitorTarget.rcMonitor.left,
                     oMonitorTarget.rcMonitor.top,
                     oMonitorTarget.rcMonitor.right  - oMonitorTarget.rcMonitor.left,
                     oMonitorTarget.rcMonitor.bottom - oMonitorTarget.rcMonitor.top );

    return true;
}

// PostNcDestroy()�� ��ȭ���ڰ� ������ �Ҹ�� �Ŀ� ȣ��Ǳ� ������ �����ϰ� ������ �� �ִ�.
void CExpressImgDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;

	//CDialogEx::PostNcDestroy();
}


void CExpressImgDlg::DrawLine_Sub (CDC *BufferDC, int GapMovement)
{
    CPoint arPoint[5];
	
	// 320 * 240�� ������ ���÷��̸� �ϱ� ���Ͽ� �����¿��� ��ǥ���� ����
    double scaleX = (double)(rtSubScreenSize.right  - rtSubScreenSize.left)   / 320.0;
	double scaleY = (double)(rtSubScreenSize.bottom - rtSubScreenSize.top)    / 240.0;

	int VanishY   = rtSubScreenSize.top + (int)(scaleY * m_nVanish) + 240;
	int LineWidth = (int)(scaleX * m_nLaneWidth);
	int CenterX   = (rtSubScreenSize.right + rtSubScreenSize.left) / 2;
	
    int offset = (int)(scaleX * 5);
    int offset2 = (int)(scaleX * 5);

    // ���� (���� �Ʒ�)
    theDraw.DrawBox (BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, rtWholeScreenSize.right, rtWholeScreenSize.bottom, GREY_ROAD);

    //���� ����
    arPoint[0].x = CenterX+5; 
    arPoint[0].y = VanishY;

    arPoint[1].x = rtWholeScreenSize.left-offset2 + GapMovement*m_nCurrPos; 
    arPoint[1].y = rtWholeScreenSize.bottom;

    arPoint[2].x = rtWholeScreenSize.left-(offset2+LineWidth) + GapMovement*m_nCurrPos; 
    arPoint[2].y = rtWholeScreenSize.bottom;

    arPoint[3].x = CenterX-5; 
    arPoint[3].y = VanishY;

    arPoint[4] = arPoint[0];
    theDraw.Draw_Rgn(BufferDC, arPoint, 4, m_nLaneLColor);
    
    //���� ����
    arPoint[0].x = CenterX-5; 
    arPoint[0].y = VanishY;

    arPoint[1].x = rtWholeScreenSize.right+offset + GapMovement*m_nCurrPos; 
    arPoint[1].y = rtWholeScreenSize.bottom;
    
	arPoint[2].x = rtWholeScreenSize.right+(offset+LineWidth) + GapMovement*m_nCurrPos; 
    arPoint[2].y = rtWholeScreenSize.bottom;
    
	arPoint[3].x = CenterX+5; 
    arPoint[3].y = VanishY;
    
	arPoint[4] = arPoint[0];
    theDraw.Draw_Rgn(BufferDC, arPoint, 4, m_nLaneRColor);
    
	// �ϴ� (���� ��)
    theDraw.DrawBox (BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, rtWholeScreenSize.right, VanishY, SKY);
}

COLORREF CExpressImgDlg::RGBtoDark(COLORREF rgb)
{
	COLORREF darkrgb;
	DWORD red, green, blue;
	
	red		= rgb & 0xFF0000;
	green	= rgb & 0x00FF00;
	blue	= rgb & 0x0000FF;

	darkrgb = (red>>1 & 0xFF0000) | (green>>1 & 0x00FF00) | (blue>>1 & 0x0000FF);
	
	return darkrgb;
}



void CExpressImgDlg::DrawLineNight_Sub (CDC *BufferDC, int GapMovement)
{
    CPoint arPoint[5];
	
	// 320 * 240�� ������ ���÷��̸� �ϱ� ���Ͽ� �����¿��� ��ǥ���� ����
    double scaleX = (double)(rtSubScreenSize.right  - rtSubScreenSize.left)   / 320.0;
	double scaleY = (double)(rtSubScreenSize.bottom - rtSubScreenSize.top)    / 240.0;

	int VanishY   = rtSubScreenSize.top + (int)(scaleY * m_nVanish) + 240;
	int LineWidth = (int)(scaleX * m_nLaneWidth);
	int CenterX   = (rtSubScreenSize.right + rtSubScreenSize.left) / 2;
	
    int offset = (int)(scaleX * 5);
    int offset2 = (int)(scaleX * 5);

    // ���� (���� �Ʒ�)
    theDraw.DrawBox (BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, rtWholeScreenSize.right, rtWholeScreenSize.bottom, RGBtoDark(GREY_ROAD));

    //���� ����
    arPoint[0].x = CenterX+5; 
    arPoint[0].y = VanishY;

    arPoint[1].x = rtWholeScreenSize.left-offset2 + GapMovement*m_nCurrPos; 
    arPoint[1].y = rtWholeScreenSize.bottom;

    arPoint[2].x = rtWholeScreenSize.left-(offset2+LineWidth) + GapMovement*m_nCurrPos; 
    arPoint[2].y = rtWholeScreenSize.bottom;

    arPoint[3].x = CenterX-5; 
    arPoint[3].y = VanishY;

    arPoint[4] = arPoint[0];
    theDraw.Draw_Rgn(BufferDC, arPoint, 4, RGBtoDark(m_nLaneLColor));
    
    //���� ����
    arPoint[0].x = CenterX-5; 
    arPoint[0].y = VanishY;

    arPoint[1].x = rtWholeScreenSize.right+offset + GapMovement*m_nCurrPos; 
    arPoint[1].y = rtWholeScreenSize.bottom;
    
	arPoint[2].x = rtWholeScreenSize.right+(offset+LineWidth) + GapMovement*m_nCurrPos; 
    arPoint[2].y = rtWholeScreenSize.bottom;
    
	arPoint[3].x = CenterX+5; 
    arPoint[3].y = VanishY;
    
	arPoint[4] = arPoint[0];
    theDraw.Draw_Rgn(BufferDC, arPoint, 4, RGBtoDark(m_nLaneRColor));
    
	// �ϴ� (���� ��)
    theDraw.DrawBox (BufferDC, rtWholeScreenSize.left, rtWholeScreenSize.top, rtWholeScreenSize.right, VanishY, BLACK);
}

void CExpressImgDlg::Vehicle_Sub (CDC *BufferDC, int GapMovement, int nInitSize, int CAR_BITMAP)
{
	CDC MemDC;
	CBitmap bmp;

	double scale = (double)(rtSubScreenSize.right - rtSubScreenSize.left)/320.0;
	double scaleH = (double)(rtSubScreenSize.bottom - rtSubScreenSize.top)/320.0;
	int CenterX	= (rtSubScreenSize.right + rtSubScreenSize.left) / 2;
	int CenterY = rtSubScreenSize.top + (int)(scale*m_nVanish) + 240;

	MemDC.CreateCompatibleDC(BufferDC);
	bmp.LoadBitmap(CAR_BITMAP);
	MemDC.SelectObject(&bmp);
	if ( (CAR_BITMAP == IDB_BITMAP_REALCAR01) || (CAR_BITMAP == IDB_BITMAP_REALCAR01BRAKE) )
	{
		BufferDC->StretchBlt(CenterX-((89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0))/2), CenterY, 100 + 100 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0), 89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0)/1.0, &MemDC, 0, 0, 200, 200, SRCCOPY);	
	}
	else if ( CAR_BITMAP == IDB_BITMAP_REALCAR02 )
	{
		//CenterY -= 50;
		BufferDC->StretchBlt(CenterX-((89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0))/2), CenterY, 100 + 100 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0), 89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0), &MemDC, 0, 0, 200, 250, SRCCOPY);	
	}
	else if ( CAR_BITMAP == IDB_BITMAP_REALCAR03 )
	{
		BufferDC->StretchBlt(CenterX-((89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0))/2), CenterY, 100 + 100 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0), 89 + 89 * ((nInitSize + (GapMovement/2)*m_nCurrPos)/10.0), &MemDC, 0, 0, 200, 200, SRCCOPY);	
	}
		
	bmp.DeleteObject();
	MemDC.DeleteDC();
}