#pragma once

#include "y_Draw.h"

// CExpressImgDlg ��ȭ �����Դϴ�.

class CExpressImgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpressImgDlg)

public:
	CExpressImgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CExpressImgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EXPRESS_IMG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CRect rtSubScreenSize, rtWholeScreenSize;	// ȭ�� ũ��
	CDraw theDraw;								// �̹����� �׸��� ���� Ŭ���� ȣ��
	CBitmap* m_pbmBack;							// ����̹��� �޸�
	int m_nImgView;								// �̹��� ���� ��ȣ
	int m_nPreImgView;							// ���� �̹��� ��ȣ
	int m_tImageShowCompleted;					// �����̵� �ִϸ��̼��� �Ϸ�Ǿ����� üũ
	int m_nCurrPos;								// �̹��� �̵� ���� ����
	////////////////////
	// ADAS Draw Data
	int m_nVanish;							// Vanish ��
	int m_nLaneWidth;						// ���� ����
	int m_nLaneMovement;					// ���� �̵���
	COLORREF m_nLaneLColor;					// �������� ����
	COLORREF m_nLaneRColor;					// �������� ����

	BOOL CreateExpressImg();				// ����� ������ ���� �� ���� ����� ����� ���̾�α� ǥ��
	void GetDisplaySpace(CRect &rt);		// ���� ������� �ػ󵵸� Ȯ��
	void DrawALL(CDC *pDC, int PartNum);	// ��ü �׸��� �׸�
	void DrawLine_Sub (CDC *BufferDC, int GapMovement); // ADAS ����
	void DrawLineNight_Sub (CDC *BufferDC, int GapMovement);
	void Vehicle_Sub (CDC *BufferDC, int GapMovement, int nInitSize, int CAR_BITMAP);	// ADAS ��

	COLORREF RGBtoDark(COLORREF rgb);
public:
	enum _ImgView
	{
		CALIBRATION = 0,
		LDW_DETECT = 1,
		LDW_WARN_L,
		LDW_WARN_R,
		FCW_CAR_DETECT,
		FCW_CAR_WARN,
		FCDA_CAR_DETECT,
		FCDA_CAR_WARN,
		LDW_DETECT_NIGHT = 51,
		LDW_WARN_L_NIGHT,
		LDW_WARN_R_NIGHT,
		FCW_CAR_DETECT_NIGHT,
		FCW_CAR_WARN_NIGHT,
		FCDA_CAR_DETECT_NIGHT,
		FCDA_CAR_WARN_NIGHT
	};
	BOOL ImgSet(_ImgView ImgNum);			// �̹��� ���� ���� ������ ������ 0, �ٸ��� 1�� ����
	BOOL ImgSet_Vanish(int vanish);			// vanish ��
	BOOL ImgSet_LandWidth(int laneWidth);	// ���� ����
	BOOL ImgSet_LaneMovemnet(int laneMove);	// ���� �̵���
	BOOL ImgSet_LaneLColor(COLORREF color);	// �������� ����
	BOOL ImgSet_LaneRColor(COLORREF color);	// �������� ����

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PostNcDestroy();
};
